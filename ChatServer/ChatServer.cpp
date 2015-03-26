#include "ChatNetwork.h"

int ChatServer::OnInitApp()
{
	_MaxSessionCount = MAX_NUMOF_SESSION;

	_SessionFactory = new ChatClientFactory;
	if (NULL == _SessionFactory)
	{
		return 1;//ERR_SYS_MEMORY_ALLOC_FAIL;
	}

	return 0;
}

int ChatServer::OnCreate()
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

	return 0;
}

int ChatServer::OnConfiguration(const char* ConfigFile)
{
	ServerCfg = new Config(ConfigFile);
	return 0;
}

int ChatServer::OnAppStart()
{
	Logger::Log("Server listening on %s:%d\n", _clientAcceptor.GetListenIP(), _clientAcceptor.GetListenPort());
	return 0;
}

unsigned int ChatServer::AcquireCharSerialID()
{
	if (m_uiCharSerialID++)
	{
		if (m_uiCharSerialID == INVALID_DWORD)
			m_uiCharSerialID = 0;
	}

	return m_uiCharSerialID;
}

bool ChatServer::AddClient(const char* charName, ChatClient* pClient)
{
	if (false == clientList.insert(CLIENTVAL(GameString(charName), pClient)).second)
		return false;
	return true;
}

void ChatServer::RemoveClient(const char* charName)
{
	clientList.erase(GameString(charName));
}

bool ChatServer::FindClient(const char* charName)
{
	CLIENTIT it = clientList.find(GameString(charName));
	if (it == clientList.end())
		return false;
	return true;
}

void ChatServer::SendAll(void* pData, int nSize)
{
	for (CLIENTIT it = clientList.begin(); it != clientList.end(); it++)
	{
		it->second->PushPacket(pData, nSize);
	}
}

void ChatServer::SendOthers(void* pData, int nSize, ChatClient* pClient, bool distCheck)
{
	for (CLIENTIT it = clientList.begin(); it != clientList.end(); it++)
	{
		if (pClient->GetCharSerialID() != it->second->GetCharSerialID())
			it->second->PushPacket(pData, nSize);
	}
}


void ChatServer::RecvOthers(eOpcode Opcode, ChatClient* pClient, bool distCheck)
{
	for (CLIENTIT it = clientList.begin(); it != clientList.end(); it++)
	{
		if (pClient->GetCharSerialID() != it->second->GetCharSerialID())
		{
			switch (Opcode)
			{
			default: break;
			}
		}
	}
}