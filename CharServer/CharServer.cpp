#include "CharNetwork.h"

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

bool CharServer::OnDataReceived(Client* client, unsigned char* pData)
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

void CharServer::PacketControl(CharClient* client, unsigned char* pData)
{
	int opcode = *(unsigned short*)&pData[4];
	std::cout << opcode << std::endl;
	FILE* fp;
	fopen_s(&fp, "log.dat", "a+");
	if (fp != NULL)
	{
		fwrite(pData, sizeof(pData), 1, fp);
		fclose(fp);
	}
}