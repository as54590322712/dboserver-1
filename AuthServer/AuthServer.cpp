#include "AuthNetwork.h"

AuthServer::AuthServer()
{
	ServerConfig = new Config("AuthServer");
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

AuthServer::~AuthServer()
{
}

void AuthServer::OnReady()
{
	Logger::Log("Server Listening on port (%d) ...\n", sPort);
}

bool AuthServer::OnConnect(Client* client)
{
	return true;
}

void AuthServer::OnDisconnect(Client* client)
{
	if (client->goCharServer) ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '2' WHERE `ID` = '%d';", client->AccountID);
	else ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '0' WHERE `ID` = '%d';", client->AccountID);
}

bool AuthServer::OnDataReceived(Client* client, Packet* pData)
{
	PacketControl((AuthClient*)client, pData);
	return true;
}

AuthClient* AuthServer::CreateClient()
{
	return new AuthClient();
}

void AuthServer::DeleteClient(Client* client)
{
	delete (AuthClient*)client;
}

void AuthServer::PacketControl(AuthClient* client, Packet* pData)
{
	LPPACKETHEADER header = pData->GetPacketHeader();
	LPPACKETDATA data = (LPPACKETDATA)pData->GetPacketData();

	switch (data->wOpCode)
	{
		case UA_LOGIN_DISCONNECT_REQ: client->SendDisconnectRes((sUA_LOGIN_DISCONNECT_REQ*)data); break;
		case UA_LOGIN_REQ: client->SendLoginRes((sUA_LOGIN_REQ*)data);  break;
		case 1: break;
		default: Logger::Log("Received Opcode: %d\n", data->wOpCode); break;
	}
}