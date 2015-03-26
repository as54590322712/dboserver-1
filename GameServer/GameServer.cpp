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