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
		case 1: break;
		default:
			{
				Logger::Log("Received Opcode: %d\n", data->wOpCode);
				char filename[60];
				sprintf_s(filename, 60, "logs/packet_%x_%x.dat", data->wOpCode, header->wPacketLen);
				FILE* fp;
				fopen_s(&fp, filename, "w+");
				if (fp != NULL)
				{
					fwrite(pData, client->LastPacketSize, 1, fp);
					fclose(fp);
				}
			}
			break;
	}
}