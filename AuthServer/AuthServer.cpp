#include "AuthServer.h"
#include <iostream>
#include <fstream>

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

bool AuthServer::OnConnect(Client* cli)
{
	std::cout << "Client Connected" << std::endl;
	return true;
}

void AuthServer::OnDisconnect(Client* cli)
{
	std::cout << "Client Disconnected" << std::endl;
}

bool AuthServer::OnDataReceived(Client* cli, unsigned char* pData)
{
	std::cout << "Dado recebido" << std::endl;
	std::fstream fh;
	char file[MAX_PATH];
	sprintf_s(file, ".\\logs\\packet_%d.bin", sizeof(pData));
	fh.open(file, std::ios::out | std::ios::binary);
	if (fh.is_open())
	{
		fh.write((char*)pData, sizeof(pData));
		fh.close();
	}
	return true;
}