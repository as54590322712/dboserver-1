#include "AuthNetwork.h"

AuthServer::AuthServer()
{
	if (!Start()) Logger::Log("Server ERROR!\n");
}

AuthServer::~AuthServer()
{
}

void AuthServer::OnReady()
{
	Logger::Log("Server Listening ...\n");
}

bool AuthServer::OnConnect(Client* client)
{
	Logger::Log("Client Connected\n");
	return true;
}

void AuthServer::OnDisconnect(Client* client)
{
	Logger::Log("Client Disconnected\n");
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
	case UA_LOGIN_DISCONNECT_REQ:
		{
			sAU_LOGIN_DISCONNECT_RES dRes;
			memset(&dRes, 0, sizeof(sAU_LOGIN_DISCONNECT_RES));
			dRes.OpCode = AU_LOGIN_DISCONNECT_RES;
			client->Send((unsigned char*)&dRes, sizeof(dRes));
		}
		break;
	case UA_LOGIN_REQ:
		{
			sUA_LOGIN_REQ* lReq = (sUA_LOGIN_REQ*)data;
			Logger::Log("USER: %S PASS: %S\n", lReq->UserName, lReq->PassWord);

			memcpy(client->userName, lReq->UserName, MAX_USERNAME_SIZE);
			memcpy(client->passWord, lReq->PassWord, MAX_PASSWORD_SIZE);

			sAU_LOGIN_RES lRes;
			memset(&lRes, 0, sizeof(sAU_LOGIN_RES));
			lRes.OpCode = AU_LOGIN_RES;
			lRes.AccountID = 1;
			lRes.AcLevel = 0xFFFF;
			strcpy_s((char*)lRes.AuthKey, MAX_AUTHKEY_SIZE, client->GenAuthKey());
			lRes.LastServerID = 0;
			lRes.ResultCode = AUTH_SUCCESS;
			memcpy(lRes.UserName, client->userName, MAX_USERNAME_SIZE);

			// servers
			lRes.ServerCount = 1;
			strcpy_s((char*)lRes.Servers[0].CharServerIP, MAX_SRVADDR_SIZE, "127.0.0.1");
			lRes.Servers[0].CharServerPort = 50300;
			lRes.Servers[0].Load = 0;
			client->Send((unsigned char*)&lRes, sizeof(lRes));
		}
		break;
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