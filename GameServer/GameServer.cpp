#include "GameNetwork.h"

int GameServer::OnInitApp()
{
	_MaxSessionCount = MAX_NUMOF_SESSION;

	_SessionFactory = new GameClientFactory;
	if (NULL == _SessionFactory)
	{
		return 1;//ERR_SYS_MEMORY_ALLOC_FAIL;
	}

	return 0;
}

int GameServer::OnCreate()
{
	int rc = 0;
	rc = _clientAcceptor.Create(ServerCfg->GetStr("Server", "IP"),
		ServerCfg->GetInt("Server", "Port"),
		SESSION_CLIENT,
		MAX_NUMOF_GAME_CLIENT, 5, 2, MAX_NUMOF_GAME_CLIENT);
	if (0 != rc)
	{
		return rc;
	}

	rc = _network.Associate(&_clientAcceptor, true);
	if (0 != rc)
	{
		return rc;
	}

	_charManager = new CharacterManager();
	_charManager->Init();
	_objManager = new ObjectManager();
	_objManager->Init();

	ServerDB = new Database();
	if (!ServerDB->Connect(
		ServerCfg->GetStr("MySQL", "Host"),
		ServerCfg->GetStr("MySQL", "Database"),
		ServerCfg->GetStr("MySQL", "User"),
		ServerCfg->GetStr("MySQL", "Password"),
		ServerCfg->GetInt("MySQL", "Port")))
		return 2;//ERR_DBSERVER_CONNECT

	pcTblData = new PCTable();
	if (pcTblData->Load("..\\Tables\\table_pc_data.edf") != 0)
	{
		Logger::Log("Failed to load PC Table!\n");
		return 3;//ERR_LOADTABLE
	}

	npcspawnTblData = new SpawnTable();
	if (npcspawnTblData->Load("..\\Tables\\spawn_npc_main_world.edf") != 0)
	{
		Logger::Log("Failed to load NPC Spawn Table!\n");
		return 3;//ERR_LOADTABLE
	}

	this->ServerID = ServerCfg->GetInt("Server", "ID");

	m_uiSerialID = INVALID_DWORD;

	Logger::Log("Loading %u NPC Spawns... please wait!\n", npcspawnTblData->GetCount());
	for (int i = 1; i < (npcspawnTblData->GetCount() + 1); ++i)
	{
		AddSpawn(npcspawnTblData->GetData(i), OBJTYPE_NPC);
	}
	Logger::Log("Loaded %u NPC Spawns!\n", npcspawnTblData->GetCount());

	ServerDB->ExecuteQuery("CALL `spClearOnline`('%u');", ServerID);
	return 0;
}

int GameServer::OnConfiguration(const char* ConfigFile)
{
	ServerCfg = new Config(ConfigFile);
	return 0;
}

int GameServer::OnAppStart()
{
	Logger::Log("Server listening on %s:%d\n", _clientAcceptor.GetListenIP(), _clientAcceptor.GetListenPort());
	return 0;
}

unsigned int GameServer::AcquireSerialID()
{
	if (m_uiSerialID++)
	{
		if (m_uiSerialID == INVALID_DWORD)
			m_uiSerialID = 0;
	}

	return m_uiSerialID;
}

void GameServer::AddSpawn(SpawnData data, eOBJTYPE type)
{
	sGU_OBJECT_CREATE sPacket;
	memset(&sPacket, 0, sizeof(sGU_OBJECT_CREATE));
	sPacket.wOpCode = GU_OBJECT_CREATE;
	sPacket.handle = AcquireSerialID();
	switch (type)
	{
	case OBJTYPE_NPC:
		sPacket.sObjectInfo.objType = OBJTYPE_NPC;
		sPacket.sObjectInfo.npcBrief.tblidx = data.mob_Tblidx;
		sPacket.sObjectInfo.npcBrief.wCurLP = 100;
		sPacket.sObjectInfo.npcBrief.wMaxLP = 100;
		sPacket.sObjectInfo.npcBrief.fLastWalkingSpeed = 3.0f;
		sPacket.sObjectInfo.npcBrief.fLastRunningSpeed = 7.0f;

		sPacket.sObjectInfo.npcState.sCharStateBase.byStateID = CHARSTATE_SPAWNING;
		sPacket.sObjectInfo.npcState.sCharStateBase.bFightMode = FALSE;

		sPacket.sObjectInfo.npcState.sCharStateBase.vCurLoc.x = data.vSpawn_Loc.x;
		sPacket.sObjectInfo.npcState.sCharStateBase.vCurLoc.y = data.vSpawn_Loc.y;
		sPacket.sObjectInfo.npcState.sCharStateBase.vCurLoc.z = data.vSpawn_Loc.z;

		sPacket.sObjectInfo.npcState.sCharStateBase.vCurDir.x = data.vSpawn_Dir.x;
		sPacket.sObjectInfo.npcState.sCharStateBase.vCurDir.y = data.vSpawn_Dir.y;
		sPacket.sObjectInfo.npcState.sCharStateBase.vCurDir.z = data.vSpawn_Dir.z;
		break;
	case OBJTYPE_MOB:
		sPacket.sObjectInfo.objType = OBJTYPE_MOB;
		sPacket.sObjectInfo.mobBrief.tblidx = data.mob_Tblidx;
		sPacket.sObjectInfo.mobBrief.wCurLP = 100;
		sPacket.sObjectInfo.mobBrief.wMaxLP = 100;
		sPacket.sObjectInfo.mobBrief.fLastWalkingSpeed = 3.0f;
		sPacket.sObjectInfo.mobBrief.fLastRunningSpeed = 7.0f;

		sPacket.sObjectInfo.mobState.sCharStateBase.byStateID = CHARSTATE_SPAWNING;
		sPacket.sObjectInfo.mobState.sCharStateBase.bFightMode = FALSE;

		sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.x = data.vSpawn_Loc.x + (float)(rand() % data.bySpawn_Loc_Range);
		sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.y = data.vSpawn_Loc.y;
		sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.z = data.vSpawn_Loc.z + (float)(rand() % data.bySpawn_Loc_Range);

		sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.x = data.vSpawn_Dir.x;
		sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.y = data.vSpawn_Dir.y;
		sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.z = data.vSpawn_Dir.z;
		break;
	}
	GetObjectManager()->AddObject(sPacket);
}