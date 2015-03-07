#include "CharNetwork.h"

CharServer::CharServer()
{
	ServerConfig = new Config("CharServer");
	ServerDB = new Database();
	ServerDB->Connect(
		ServerConfig->GetStr("MySQL", "Host"),
		ServerConfig->GetStr("MySQL", "Database"),
		ServerConfig->GetStr("MySQL", "User"),
		ServerConfig->GetStr("MySQL", "Password"),
		ServerConfig->GetInt("MySQL", "Port"));
	this->sPort = ServerConfig->GetInt("Port");
	if (!Start()) Logger::Log("Server ERROR!\n");
}

CharServer::~CharServer()
{
}

void CharServer::OnReady()
{
	Logger::Log("Server Listening on port (%d) ...\n", sPort);
}

bool CharServer::OnConnect(Client* client)
{
	return true;
}

void CharServer::OnDisconnect(Client* client)
{
	if (client->goGameServer) ServerDB->ExecuteUpdate("UPDATE `account` SET `State` = '3' WHERE `ID` = '%d';", client->AccountID);
	else ServerDB->ExecuteUpdate("UPDATE `account` SET `State` = '0' WHERE `ID` = '%d';", client->AccountID);
}

bool CharServer::OnDataReceived(Client* client, Packet* pData)
{
	PacketControl((CharClient*)client, pData);
	return true;
}

CharClient* CharServer::CreateClient()
{
	return new CharClient();
}

void CharServer::DeleteClient(Client* client)
{
	delete (CharClient*)client;
}

void CharServer::PacketControl(CharClient* client, Packet* pData)
{
	LPPACKETDATA data = (LPPACKETDATA)pData->GetPacketData();
	switch (data->wOpCode)
	{
		case UC_LOGIN_REQ: client->SendLoginResult((sUC_LOGIN_REQ*)data); break;
		case UC_CHARACTER_SERVERLIST_REQ: client->SendServerlist(false); break;
		case UC_CHARACTER_SERVERLIST_ONE_REQ: client->SendServerlist(true); break;
		case UC_CHARACTER_LOAD_REQ: client->SendCharLoadResult((sUC_CHARACTER_LOAD_REQ*)data); break;
		case UC_CHARACTER_EXIT_REQ: client->SendCharExitRes((sUC_CHARACTER_EXIT_REQ*)data); break;
		case UC_CHARACTER_ADD_REQ: client->SendCharCreateRes((sUC_CHARACTER_ADD_REQ*)data); break;
		case UC_CHARACTER_DEL_REQ: client->SendCharDelRes((sUC_CHARACTER_DEL_REQ*)data); break;
		case UC_CHARACTER_DEL_CANCEL_REQ: client->SendCharDelCancelRes((sUC_CHARACTER_DEL_CANCEL_REQ*)data); break;
		case UC_CONNECT_WAIT_CHECK_REQ: client->SendCharConnWaitCheckRes((sUC_CONNECT_WAIT_CHECK_REQ*)data); break;
		case UC_CHARACTER_SELECT_REQ: client->SendCharSelectRes((sUC_CHARACTER_SELECT_REQ*)data); break;
		case 1: { sPACKETHEADER reply(1); client->Send(&reply, sizeof(reply)); } break;
		case 0: break;
		default: Logger::Log("Received Opcode: %d\n", data->wOpCode); break;
	}
}