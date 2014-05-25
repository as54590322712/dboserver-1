#include "AuthNetwork.h"

AuthServer::AuthServer()
{
	if (!Start()) std::cout << "Server ERROR!" << std::endl;
}

AuthServer::~AuthServer()
{
}

void AuthServer::OnReady()
{
	std::cout << "Server Listening ..." << std::endl;
}

bool AuthServer::OnConnect(Client* client)
{
	std::cout << "Client Connected" << std::endl;
	return true;
}

void AuthServer::OnDisconnect(Client* client)
{
	std::cout << "Client Disconnected" << std::endl;
}

bool AuthServer::OnDataReceived(Client* client, unsigned char* pData)
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

void AuthServer::PacketControl(AuthClient* client, unsigned char* pData)
{
	int opcode = *(unsigned short*)&pData[4];

	switch (opcode)
	{
	case UA_LOGIN_REQ:
		sUA_LOGIN_REQ* aReq = (sUA_LOGIN_REQ*)pData;
		sAU_LOGIN_RES sPacket;
		memset(&sPacket, 0, sizeof(sAU_LOGIN_RES));

		sPacket.OpCode = AU_LOGIN_RES;
		sPacket.ResultCode = 100;
		memcpy(sPacket.UserName, aReq->UserName, MAX_USERNAME_SIZE);
		strcpy_s((char*)sPacket.AuthKey, MAX_AUTHKEY_SIZE, "Dbo");
		sPacket.AccountID = 1;
		sPacket.ServerCount = 1;

		strcpy_s(sPacket.Servers[0].CharServerIP, MAX_SRVADDR_SIZE, "127.0.0.1");
		sPacket.Servers[0].CharServerPort = 50200;
		sPacket.Servers[0].Load = 0;

		sPacket.LastServerID = 0;
		sPacket.Size = sizeof(sPacket);
		sPacket.Count = client->SendCount + 1;
		sPacket.Hash = 0;
		client->Send((unsigned char*)&sPacket, sizeof(sPacket));
		break;
	}
}