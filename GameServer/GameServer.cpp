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

bool GameServer::AddClient(const char* charName, GameClient* pClient)
{
	if (false == clientList.insert(CLIENTVAL(GameString(charName), pClient)).second)
		return false;
	return true;
}

void GameServer::RemoveClient(const char* charName)
{
	clientList.erase(GameString(charName));
}

bool GameServer::FindClient(const char* charName)
{
	CLIENTIT it = clientList.find(GameString(charName));
	if (it == clientList.end())
		return false;
	return true;
}

void GameServer::SendAll(void* pData, int nSize)
{
	for (CLIENTIT it = clientList.begin(); it != clientList.end(); it++)
	{
		it->second->PushPacket(pData, nSize);
	}
}

void GameServer::SendOthers(void* pData, int nSize, GameClient* pClient, bool distCheck)
{
	for (CLIENTIT it = clientList.begin(); it != clientList.end(); it++)
	{
		if (pClient->GetCharSerialID() != it->second->GetCharSerialID())
			it->second->PushPacket(pData, nSize);
	}
}

void GameServer::RecvOthers(eOpcode Opcode, GameClient* pClient, bool distCheck)
{
	for (CLIENTIT it = clientList.begin(); it != clientList.end(); it++)
	{
		if (pClient->GetCharSerialID() != it->second->GetCharSerialID())
		{
			switch (Opcode)
			{
			case GU_OBJECT_CREATE:
				{
					it->second->charSpawn.handle = it->second->GetCharSerialID();
					pClient->PushPacket(&it->second->charSpawn, sizeof(it->second->charSpawn));
				} break;
			}
		}
	}
}