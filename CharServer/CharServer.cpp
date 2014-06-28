#include "CharNetwork.h"
#include "CharProtocol.h"

CharServer::CharServer()
{
	this->sPort = 50300;
	if (!Start()) std::cout << "Server ERROR!" << std::endl;
}

CharServer::~CharServer()
{
}

void CharServer::OnReady()
{
	std::cout << "Server Listening ..." << std::endl;
}

bool CharServer::OnConnect(Client* client)
{
	std::cout << "Client Connected" << std::endl;
	return true;
}

void CharServer::OnDisconnect(Client* client)
{
	std::cout << "Client Disconnected" << std::endl;
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
	LPPACKETHEADER header = pData->GetPacketHeader();
	LPPACKETDATA data = (LPPACKETDATA)pData->GetPacketData();

	switch (data->wOpCode)
	{
	case UC_LOGIN_REQ:
		{
			sUC_LOGIN_REQ* lReq = (sUC_LOGIN_REQ*)data;
			sCU_LOGIN_RES lRes;
			printf("ACCID: %d SRVID: %d AUTHKEY: %s\n", lReq->accountId, lReq->serverID, lReq->AuthKey);
			memset(&lRes, 0, sizeof(sCU_LOGIN_RES));
			lRes.OpCode = CU_LOGIN_RES;
			lRes.ResultCode = 200;
			client->Send((unsigned char*)&lRes, sizeof(lRes));
		}
		break;
	case 1: break;
	default:
		{
			printf("Received Opcode: %d\n", data->wOpCode);
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