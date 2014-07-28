#ifndef _AUTHNETWORK_H
#define _AUTHNETWORK_H

#include <Network.h>
#include <Config.h>
#include <iostream>
#include <fstream>
#include "AuthProtocol.h"

class AuthClient : public Client
{
public:
	AuthClient();
	~AuthClient();

	char* GenAuthKey();
	int GetDBAccountID();
	ResultCodes LoginVerifyAccount();

	void SendLoginRes(sUA_LOGIN_REQ* data);
	void SendDisconnectRes(sUA_LOGIN_DISCONNECT_REQ* data);
};

class AuthServer : public Server
{
public:
	AuthServer();
	~AuthServer();

	void OnReady();
	bool OnConnect(Client* client);
	void OnDisconnect(Client* client);
	bool OnDataReceived(Client* client, Packet* pData);

	AuthClient* CreateClient();
	void DeleteClient(Client* client);

	void PacketControl(AuthClient* client, Packet* pData);
};

#endif