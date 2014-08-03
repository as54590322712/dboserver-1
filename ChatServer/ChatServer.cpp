#include "ChatNetwork.h"

ChatServer::ChatServer()
{
	ServerConfig = new Config("ChatServer");
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

ChatServer::~ChatServer()
{
}

void ChatServer::OnReady()
{
	Logger::Log("Server Listening on port (%d) ...\n", sPort);
}

bool ChatServer::OnConnect(Client* client)
{
	return true;
}

void ChatServer::OnDisconnect(Client* client)
{
}

bool ChatServer::OnDataReceived(Client* client, Packet* pData)
{
	PacketControl((ChatClient*)client, pData);
	return true;
}

ChatClient* ChatServer::CreateClient()
{
	return new ChatClient();
}

void ChatServer::DeleteClient(Client* client)
{
	delete (ChatClient*)client;
}

void ChatServer::PacketControl(ChatClient* client, Packet* pData)
{
	LPPACKETHEADER header = pData->GetPacketHeader();
	LPPACKETDATA data = (LPPACKETDATA)pData->GetPacketData();

	switch (data->wOpCode)
	{
		case 1: break;
		default: Logger::Log("Received Opcode: %d\n", data->wOpCode); break;
	}
}