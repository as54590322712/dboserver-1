#ifndef _AUTHNETWORK_H
#define _AUTHNETWORK_H

#include <Network.h>
#include <iostream>
#include <fstream>
#include "AuthProtocol.h"

class AuthClient : public Client
{
public:
	AuthClient();
	~AuthClient();
};

class AuthServer : public Server
{
public:
	AuthServer();
	~AuthServer();

	void OnReady();
	bool OnConnect(Client* client);
	void OnDisconnect(Client* client);
	bool OnDataReceived(Client* client, unsigned char* pData);

	AuthClient* CreateClient();
	void DeleteClient(Client* client);

	void PacketControl(AuthClient* client, unsigned char* pData);
};

#endif