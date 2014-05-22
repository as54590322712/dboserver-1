#include "stdafx.h"
#include "AuthServer.h"

AuthServer::AuthServer()
{
	if (Start()) printf_s("Server is Listening\n");
}

AuthServer::~AuthServer()
{
}

void AuthServer::OnConnect(Client* cli)
{
	printf_s("Client Connected\n");
}

void AuthServer::OnDisconnect(Client* cli)
{
	printf_s("Client Disconnected\n");
}