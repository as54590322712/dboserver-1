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

		printf("USER: %S, PASS: %S VER [%d.%d]\n", aReq->UserName, aReq->PassWord, aReq->hVer, aReq->lVer);

		sPacket.OpCode = AU_LOGIN_RES;
		sPacket.ResultCode = 100;
		memcpy(sPacket.UserName, aReq->UserName, MAX_USERNAME_SIZE);
		strcpy_s((char*)sPacket.AuthKey, MAX_AUTHKEY_SIZE, "Dbo");
		sPacket.AccountID = 1;
		sPacket.ServerCount = 2;
		sPacket.AcLevel = 255;

		strcpy_s(sPacket.Servers[0].CharServerIP, MAX_SRVADDR_SIZE, "127.0.0.1");
		sPacket.Servers[0].CharServerPort = 50300;
		sPacket.Servers[0].Load = 0;
		strcpy_s(sPacket.Servers[1].CharServerIP, MAX_SRVADDR_SIZE, "127.0.0.1");
		sPacket.Servers[1].CharServerPort = 50300;
		sPacket.Servers[1].Load = 0;

		sPacket.LastServerID = 1;
		sPacket.Size = sizeof(sPacket);
		sPacket.Count = client->SendCount;
		sPacket.Hash = 0;
		client->Send((unsigned char*)&sPacket, sPacket.Size);
		FILE* fp;
		fopen_s(&fp, "log.dat", "w+");
		if (fp != NULL)
		{
			fwrite(&sPacket, sizeof(sPacket), 1, fp);
			fclose(fp);
		}
		break;
	}
}