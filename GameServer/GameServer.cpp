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

	this->ServerID = ServerCfg->GetInt("Server", "ID");

	m_uiCharSerialID = INVALID_DWORD;
	m_uiNpcSerialID = INVALID_DWORD;
	m_uiTargetSerialID = INVALID_DWORD;
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
	_charManager = new CharacterManager();
	_charManager->Init();
	_objManager = new ObjectManager();
	_objManager->Init();
	return 0;
}

unsigned int GameServer::AcquireCharSerialID()
{
	if (m_uiCharSerialID++)
	{
		if (m_uiCharSerialID == INVALID_DWORD)
			m_uiCharSerialID = 0;
	}

	return m_uiCharSerialID;
}

unsigned int GameServer::AcquireNpcSerialID()
{
	if (m_uiNpcSerialID++)
	{
		if (m_uiNpcSerialID == INVALID_DWORD)
			m_uiNpcSerialID = 0;
	}

	return m_uiNpcSerialID;
}

unsigned int GameServer::AcquireTargetSerialID()
{
	if (m_uiTargetSerialID++)
	{
		if (m_uiTargetSerialID == INVALID_DWORD)
			m_uiTargetSerialID = 0;
	}

	return m_uiTargetSerialID;
}

bool GameServer::AddClient(GameClient* pClient)
{
	cList.push_back(new ClientLink(pClient));
	return true;
}

void GameServer::RemoveClient(GameClient* pClient)
{
	for (unsigned int i = 0; i < cList.size(); ++i)
	{
		if (pClient == cList.at(i)->GetClient())
			cList.erase(cList.begin() + i);
	}
}

bool GameServer::FindClient(GameClient* pClient)
{
	for (unsigned int i = 0; i < cList.size(); ++i)
	{
		if (pClient == cList.at(i)->GetClient()) return true;
	}
	return false;
}

void GameServer::SendAll(void* pData, int nSize)
{
	for (unsigned int i = 0; i < cList.size(); ++i)
	{
		cList.at(i)->GetClient()->PushPacket(pData, nSize);
	}
}

void GameServer::SendOthers(void* pData, int nSize, GameClient* pClient, bool distCheck)
{
	for (unsigned int i = 0; i < cList.size(); ++i)
	{
		if (pClient->GetHandle() != cList.at(i)->GetClient()->GetHandle())
			cList.at(i)->GetClient()->PushPacket(pData, nSize);
	}
}

void GameServer::RecvOthers(eOPCODE_GU Opcode, GameClient* pClient, bool distCheck)
{
	for (unsigned int i = 0; i < cList.size(); ++i)
	{
		if (pClient->GetHandle() != cList.at(i)->GetClient()->GetHandle())
		{
			switch (Opcode)
			{
			case GU_OBJECT_CREATE:
				{
					sGU_OBJECT_CREATE pSpawn = cList.at(i)->GetClient()->GetCharSpawnData();
					pSpawn.handle = cList.at(i)->GetClient()->GetCharSerialID();
					pClient->PushPacket(&pSpawn, sizeof(pSpawn));
				} break;
			}
		}
	}
}

void GameServer::SpawnObjects()
{
	for (unsigned int i = 0; i < cList.size(); ++i)
	{
		this->_objManager->SpawnToClient(cList.at(i)->GetClient());
	}
}