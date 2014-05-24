#include "stdafx.h"
#include "AuthServer.h"

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

void AuthServer::OnConnect(Client* cli)
{
	std::cout << "Client Connected" << std::endl;
}

void AuthServer::OnDisconnect(Client* cli)
{
	std::cout << "Client Disconnected" << std::endl;
}

void AuthServer::OnDataReceived(Client* cli, unsigned char* pData)
{
	std::cout << "Dado recebido" << std::endl;
}