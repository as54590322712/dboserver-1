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
	int size = *(unsigned short*)&pData[0];
	int opcode = *(unsigned short*)&pData[2];

	std::cout << "Receiving DATA [" << opcode << "] (" << size << ") " << client->LastPacketSize << std::endl;
	char filename[60];
	sprintf_s(filename, 60, "logs/packet_%x_%x.dat", opcode, size);
	FILE* fp;
	fopen_s(&fp, filename, "w+");
	if (fp != NULL)
	{
		fwrite(pData, client->LastPacketSize, 1, fp);
		fclose(fp);
	}
}