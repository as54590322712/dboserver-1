#include "GameNetwork.h"

GameServer::GameServer()
{
	ServerConfig = new Config("GameServer");
	ServerDB = new Database();
	ServerDB->Connect(
		ServerConfig->GetStr("MySQL", "Host"),
		ServerConfig->GetStr("MySQL", "Database"),
		ServerConfig->GetStr("MySQL", "User"),
		ServerConfig->GetStr("MySQL", "Password"),
		ServerConfig->GetInt("MySQL", "Port"));
	this->sPort = ServerConfig->GetInt("Port");
	this->ServerID = ServerConfig->GetInt("ID");
	if (!Start()) Logger::Log("Server ERROR!\n");
}

GameServer::~GameServer()
{
}

void GameServer::OnReady()
{
	Logger::Log("Server Listening on port (%d) ...\n", sPort);
}

bool GameServer::OnConnect(Client* client)
{
	return true;
}

void GameServer::OnDisconnect(Client* client)
{
	if (client->goCharServer) ServerDB->ExecuteUpdate("UPDATE `account` SET `State` = '2' WHERE `ID` = '%d';", client->AccountID);
	else ServerDB->ExecuteUpdate("UPDATE `account` SET `State` = '0' WHERE `ID` = '%d';", client->AccountID);
}

bool GameServer::OnDataReceived(Client* client, Packet* pData)
{
	PacketControl((GameClient*)client, pData);
	return true;
}

GameClient* GameServer::CreateClient()
{
	return new GameClient();
}

void GameServer::DeleteClient(Client* client)
{
	delete (GameClient*)client;
}

void GameServer::PacketControl(GameClient* client, Packet* pData)
{
	LPPACKETHEADER header = pData->GetPacketHeader();
	LPPACKETDATA data = (LPPACKETDATA)pData->GetPacketData();

	switch (data->wOpCode)
	{
		case UG_CHAR_MOVE: break;
		case UG_CHAR_DEST_MOVE: break;
		case UG_ENTER_WORLD: { 
			client->SendCharWorldInfo();
			// TO DO WORLD SPAWNS
			client->SendCharWorldInfoEnd();
		} break;
		case UG_GAME_ENTER_REQ: {
			client->SendGameEnterRes((sUG_GAME_ENTER_REQ*)data);
			client->SendCharInfo();
			// TO DO LOAD ITEMS ETC
			client->SendCharInfoEnd();
		} break;
		case UG_PING: break;
		case 1: { sPACKETHEADER reply(1); client->Send(&reply, sizeof(reply)); } break;
		case 0: break;
		default: Logger::Log("Received Opcode: %d\n", data->wOpCode); break;
	}
}