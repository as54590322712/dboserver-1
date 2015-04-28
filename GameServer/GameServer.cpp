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

	ServerID = ServerCfg->GetInt("Server", "ID");
	ChannelID = ServerCfg->GetInt("Server", "ChannelID");
	chatServerIP = ServerCfg->GetStr("ChatServer", "IP");
	chatServerPort = ServerCfg->GetInt("ChatServer", "Port");
	gameDataPath = ServerCfg->GetStr("GameData", "Path");

	m_uiSerialID = INVALID_DWORD;

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
	// TABLE CONTAINER LOAD
	Logger::Log("Loading Game Data Tables ... PLEASE WAIT\n");
	if (LoadTableData())
		Logger::Log("LOADED!\n");
	else
		return 3;//ERR_TABLE_LOAD

	// Load MOBs/NPCs Spawns
	LoadSpawns();

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

bool GameServer::LoadTableData()
{
	CNtlBitFlagManager flagManager;
	if (false == flagManager.Create(TableContainer::TABLE_COUNT)) return false;

	TableFileNameList fileNameList;
	if (false == fileNameList.Create())	return false;

	flagManager.Set(TableContainer::TABLE_WORLD);
	flagManager.Set(TableContainer::TABLE_PC);
	flagManager.Set(TableContainer::TABLE_MOB);
	flagManager.Set(TableContainer::TABLE_NPC);
	flagManager.Set(TableContainer::TABLE_ITEM);
	flagManager.Set(TableContainer::TABLE_ITEM_OPTION);
	flagManager.Set(TableContainer::TABLE_SKILL);
	flagManager.Set(TableContainer::TABLE_SYSTEM_EFFECT);
	flagManager.Set(TableContainer::TABLE_NEWBIE);
	flagManager.Set(TableContainer::TABLE_MERCHANT);
	flagManager.Set(TableContainer::TABLE_HTB_SET);
	flagManager.Set(TableContainer::TABLE_USE_ITEM);
	flagManager.Set(TableContainer::TABLE_SET_ITEM);
	flagManager.Set(TableContainer::TABLE_CHARM);
	flagManager.Set(TableContainer::TABLE_ACTION);
	flagManager.Set(TableContainer::TABLE_CHAT_COMMAND);
	flagManager.Set(TableContainer::TABLE_QUEST_ITEM);
	flagManager.Set(TableContainer::TABLE_QUEST_TEXT_DATA);
	flagManager.Set(TableContainer::TABLE_TEXT_ALL);
	flagManager.Set(TableContainer::TABLE_OBJECT);
	flagManager.Set(TableContainer::TABLE_WORLD_MAP);
	flagManager.Set(TableContainer::TABLE_LAND_MARK);
	flagManager.Set(TableContainer::TABLE_HELP);
	flagManager.Set(TableContainer::TABLE_GUIDE_HINT);
	flagManager.Set(TableContainer::TABLE_DRAGONBALL);
	flagManager.Set(TableContainer::TABLE_DRAGONBALL_REWARD);
	flagManager.Set(TableContainer::TABLE_TIMEQUEST);
	flagManager.Set(TableContainer::TABLE_BUDOKAI);
	flagManager.Set(TableContainer::TABLE_RANKBATTLE);
	flagManager.Set(TableContainer::TABLE_DIRECTION_LINK);
	flagManager.Set(TableContainer::TABLE_CHATTING_FILTER);
	flagManager.Set(TableContainer::TABLE_PORTAL);
	flagManager.Set(TableContainer::TABLE_SPEECH);
	flagManager.Set(TableContainer::TABLE_SCRIPT_LINK);
	flagManager.Set(TableContainer::TABLE_QUEST_NARRATION);
	flagManager.Set(TableContainer::TABLE_VEHICLE);
	flagManager.Set(TableContainer::TABLE_DUNGEON);
	flagManager.Set(TableContainer::TABLE_MOB_MOVE_PATTERN);
	flagManager.Set(TableContainer::TABLE_DYNAMIC_OBJECT);
	flagManager.Set(TableContainer::TABLE_ITEM_RECIPE);
	flagManager.Set(TableContainer::TABLE_ITEM_UPGRADE);
	flagManager.Set(TableContainer::TABLE_MIX_MACHINE);
	flagManager.Set(TableContainer::TABLE_DOJO);
	flagManager.Set(TableContainer::TABLE_QUEST_REWARD);
	flagManager.Set(TableContainer::TABLE_WORLD_ZONE);
	flagManager.Set(TableContainer::TABLE_NPC_SPAWN);
	flagManager.Set(TableContainer::TABLE_MOB_SPAWN);
	flagManager.Set(TableContainer::TABLE_FORMULA);
	flagManager.Set(TableContainer::TABLE_GAME_MANIA_TIME);
	flagManager.Set(TableContainer::TABLE_BASIC_DROP);
	flagManager.Set(TableContainer::TABLE_LEGENDARY_DROP);
	flagManager.Set(TableContainer::TABLE_NORMAL_DROP);
	flagManager.Set(TableContainer::TABLE_SUPERIOR_DROP);
	flagManager.Set(TableContainer::TABLE_EACH_DROP);
	flagManager.Set(TableContainer::TABLE_TYPE_DROP);
	flagManager.Set(TableContainer::TABLE_EXCELLENT_DROP);
	flagManager.Set(TableContainer::TABLE_EXP);

	fileNameList.SetFileName(TableContainer::TABLE_WORLD, "Table_World_Data");
	fileNameList.SetFileName(TableContainer::TABLE_PC, "Table_PC_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MOB, "Table_MOB_Data");
	fileNameList.SetFileName(TableContainer::TABLE_NPC, "Table_NPC_Data");
	fileNameList.SetFileName(TableContainer::TABLE_ITEM, "Table_Item_Data");
	fileNameList.SetFileName(TableContainer::TABLE_ITEM_OPTION, "Table_Item_Option_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SKILL, "Table_Skill_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SYSTEM_EFFECT, "Table_System_Effect_Data");
	fileNameList.SetFileName(TableContainer::TABLE_NEWBIE, "Table_Newbie_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MERCHANT, "Table_Merchant_Data");
	fileNameList.SetFileName(TableContainer::TABLE_HTB_SET, "Table_HTB_Set_Data");
	fileNameList.SetFileName(TableContainer::TABLE_USE_ITEM, "Table_Use_Item_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SET_ITEM, "Table_Set_Item_Data");
	fileNameList.SetFileName(TableContainer::TABLE_CHARM, "Table_Charm_Data");
	fileNameList.SetFileName(TableContainer::TABLE_ACTION, "Table_Action_Data");
	fileNameList.SetFileName(TableContainer::TABLE_CHAT_COMMAND, "Table_Chat_Command_Data");
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_ITEM, "Table_Quest_Item_Data");
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_TEXT_DATA, "Table_Quest_Text_Data");
	fileNameList.SetFileName(TableContainer::TABLE_TEXT_ALL, "Table_Text_All_Data");
	fileNameList.SetFileName(TableContainer::TABLE_OBJECT, "Table_Object");
	fileNameList.SetFileName(TableContainer::TABLE_WORLD_MAP, "Table_Worldmap_Data");
	fileNameList.SetFileName(TableContainer::TABLE_LAND_MARK, "Table_Landmark_Data");
	fileNameList.SetFileName(TableContainer::TABLE_HELP, "Table_Help_Data");
	fileNameList.SetFileName(TableContainer::TABLE_GUIDE_HINT, "Table_Guide_Hint_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DRAGONBALL, "Table_Dragon_Ball_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DRAGONBALL_REWARD, "Table_DB_Reward_Data");
	fileNameList.SetFileName(TableContainer::TABLE_TIMEQUEST, "Table_TMQ_Data");
	fileNameList.SetFileName(TableContainer::TABLE_BUDOKAI, "Table_Tenkaichibudokai_Data");
	fileNameList.SetFileName(TableContainer::TABLE_RANKBATTLE, "Table_RankBattle_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DIRECTION_LINK, "Table_Direction_Link_Data");
	fileNameList.SetFileName(TableContainer::TABLE_CHATTING_FILTER, "Table_Chatting_Filter_Data");
	fileNameList.SetFileName(TableContainer::TABLE_PORTAL, "Table_Portal_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SPEECH, "Table_NPC_Speech_Data");
	fileNameList.SetFileName(TableContainer::TABLE_SCRIPT_LINK, "Table_Script_Link_Data");
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_NARRATION, "Table_Quest_Narration_Data");
	fileNameList.SetFileName(TableContainer::TABLE_VEHICLE, "Table_Vehicle_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DUNGEON, "Table_Dungeon_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MOB_MOVE_PATTERN, "Table_Mob_Move_Pattern_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DYNAMIC_OBJECT, "Table_Dynamic_Object_Data");
	fileNameList.SetFileName(TableContainer::TABLE_ITEM_RECIPE, "Table_Item_Recipe_Data");
	fileNameList.SetFileName(TableContainer::TABLE_ITEM_UPGRADE, "Table_Item_Upgrade_Data");
	fileNameList.SetFileName(TableContainer::TABLE_MIX_MACHINE, "Table_Item_Mix_Machine_Data");
	fileNameList.SetFileName(TableContainer::TABLE_DOJO, "Table_Dojo_Data");
	fileNameList.SetFileName(TableContainer::TABLE_QUEST_REWARD, "Table_Quest_Reward_Data");
	fileNameList.SetFileName(TableContainer::TABLE_WORLD_ZONE, "Table_World_Zone_Data");
	fileNameList.SetFileName(TableContainer::TABLE_FORMULA, "TD_Formula");
	fileNameList.SetFileName(TableContainer::TABLE_GAME_MANIA_TIME, "Table_GameManiaTime_Data");
	fileNameList.SetFileName(TableContainer::TABLE_EXP, "table_exp_data");
	fileNameList.SetFileName(TableContainer::TABLE_BASIC_DROP, "table_basic_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_LEGENDARY_DROP, "table_legendary_drop_data");
	fileNameList.SetFileName(TableContainer::TABLE_SYSTEM_EFFECT, "table_system_effect_data");

	m_pTableContainer = new TableContainer();
	
	return m_pTableContainer->Create(flagManager, gameDataPath, &fileNameList, eLOADING_METHOD::LOADING_METHOD_SECURED_BINARY, GetACP(), NULL);
}

void GameServer::LoadSpawns()
{
	int count = 0;

	Logger::Log("Loading NPCs spawns ...\n");
	for (TableContainer::SPAWNTABLEIT it = GetTableContainer()->BeginNpcSpawnTable(); GetTableContainer()->EndNpcSpawnTable() != it; ++it)
	{
		count += LoadSpawns(it->first, true);
	}
	Logger::Log("Loaded %d NPCs Spawns.\n", count);
	count = 0;
	Logger::Log("Loading MOBs spawns ...\n");
	for (TableContainer::SPAWNTABLEIT it = GetTableContainer()->BeginMobSpawnTable(); GetTableContainer()->EndMobSpawnTable() != it; ++it)
	{
		count += LoadSpawns(it->first, false);
	}
	Logger::Log("Loaded %d MOBs Spawns.\n", count);
}

int GameServer::LoadSpawns(TBLIDX worldTblidx, bool bIsNpc)
{
	int count = 0;

	if (bIsNpc)
	{
		SpawnTable* pSpawnTbl = GetTableContainer()->GetNpcSpawnTable(worldTblidx);
		
		for (Table::TABLEIT it = pSpawnTbl->Begin(); it != pSpawnTbl->End(); ++it, ++count)
		{
			sSPAWN_TBLDAT* pSpawnData = (sSPAWN_TBLDAT*)it->second;
			sNPC_TBLDAT* pTblData = (sNPC_TBLDAT*)GetTableContainer()->GetNpcTable()->FindData(pSpawnData->mob_Tblidx);

			sGU_OBJECT_CREATE sPacket;
			memset(&sPacket, 0, sizeof(sGU_OBJECT_CREATE));
			sPacket.wOpCode = GU_OBJECT_CREATE;

			if (pTblData)
			{
				sPacket.handle = AcquireSerialID();
				sPacket.sObjectInfo.objType = OBJTYPE_NPC;
				sPacket.sObjectInfo.npcBrief.tblidx = pTblData->tblidx;
				sPacket.sObjectInfo.npcBrief.wCurLP = pTblData->wBasic_LP;
				sPacket.sObjectInfo.npcBrief.wMaxLP = pTblData->wBasic_LP;
				sPacket.sObjectInfo.npcBrief.wCurEP = pTblData->wBasic_EP;
				sPacket.sObjectInfo.npcBrief.wMaxEP = pTblData->wBasic_EP;
				sPacket.sObjectInfo.npcBrief.fLastWalkingSpeed = pTblData->fWalk_Speed;
				sPacket.sObjectInfo.npcBrief.fLastRunningSpeed = pTblData->fRun_Speed;
				sPacket.sObjectInfo.npcBrief.nicknameTblidx = pTblData->Name;

				sPacket.sObjectInfo.npcState.sCharStateBase.byStateID = CHARSTATE_SPAWNING;
				sPacket.sObjectInfo.npcState.sCharStateBase.bFightMode = FALSE;

				sPacket.sObjectInfo.npcState.sCharStateBase.vCurLoc.x = pSpawnData->vSpawn_Loc.x;
				sPacket.sObjectInfo.npcState.sCharStateBase.vCurLoc.y = pSpawnData->vSpawn_Loc.y;
				sPacket.sObjectInfo.npcState.sCharStateBase.vCurLoc.z = pSpawnData->vSpawn_Loc.z;

				sPacket.sObjectInfo.npcState.sCharStateBase.vCurDir.x = pSpawnData->vSpawn_Dir.x;
				sPacket.sObjectInfo.npcState.sCharStateBase.vCurDir.y = pSpawnData->vSpawn_Dir.y;
				sPacket.sObjectInfo.npcState.sCharStateBase.vCurDir.z = pSpawnData->vSpawn_Dir.z;

				ObjectInfo obj;
				obj.worldTblIdx = worldTblidx;
				obj.ObjData = sPacket;
				GetObjectManager()->AddObject(obj);
			}
		}
	}
	else
	{
		SpawnTable* pSpawnTbl = GetTableContainer()->GetMobSpawnTable(worldTblidx);
		
		for (Table::TABLEIT it = pSpawnTbl->Begin(); it != pSpawnTbl->End(); ++it, ++count)
		{
			sSPAWN_TBLDAT* pSpawnData = (sSPAWN_TBLDAT*)it->second;
			sMOB_TBLDAT* pTblData = (sMOB_TBLDAT*)GetTableContainer()->GetMobTable()->FindData(pSpawnData->mob_Tblidx);

			sGU_OBJECT_CREATE sPacket;
			memset(&sPacket, 0, sizeof(sGU_OBJECT_CREATE));
			sPacket.wOpCode = GU_OBJECT_CREATE;

			if (pTblData)
			{
				sPacket.handle = AcquireSerialID();
				sPacket.sObjectInfo.objType = OBJTYPE_MOB;
				sPacket.sObjectInfo.mobBrief.tblidx = pTblData->tblidx;
				sPacket.sObjectInfo.mobBrief.wCurLP = pTblData->wBasic_LP;
				sPacket.sObjectInfo.mobBrief.wMaxLP = pTblData->wBasic_LP;
				sPacket.sObjectInfo.mobBrief.wCurEP = pTblData->wBasic_EP;
				sPacket.sObjectInfo.mobBrief.wMaxEP = pTblData->wBasic_EP;
				sPacket.sObjectInfo.mobBrief.fLastWalkingSpeed = pTblData->fWalk_Speed;
				sPacket.sObjectInfo.mobBrief.fLastRunningSpeed = pTblData->fRun_Speed;

				sPacket.sObjectInfo.mobState.sCharStateBase.byStateID = CHARSTATE_SPAWNING;
				sPacket.sObjectInfo.mobState.sCharStateBase.bFightMode = FALSE;

				sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.x = pSpawnData->vSpawn_Loc.x;
				sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.y = pSpawnData->vSpawn_Loc.y;
				sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.z = pSpawnData->vSpawn_Loc.z;

				sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.x = pSpawnData->vSpawn_Dir.x;
				sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.y = pSpawnData->vSpawn_Dir.y;
				sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.z = pSpawnData->vSpawn_Dir.z;

				ObjectInfo obj;
				obj.worldTblIdx = worldTblidx;
				obj.ObjData = sPacket;
				GetObjectManager()->AddObject(obj);
			}
		}
	}
	return count;
}