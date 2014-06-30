#ifndef _CHARNETWORK_H
#define _CHARNETWORK_H

#include <Network.h>
#include "CharProtocol.h"

class CharClient : public Client
{
public:
	CharClient();
	~CharClient();

	// PROTOCOL FUNCTIONS
	void SendLoginResult(sUC_LOGIN_REQ* data);
	void SendServerlistOne(Packet* data);
};

class CharServer : public Server
{
public:
	CharServer();
	~CharServer();

	void OnReady();
	bool OnConnect(Client* client);
	void OnDisconnect(Client* client);
	bool OnDataReceived(Client* client, Packet* pData);
	CharClient* CreateClient();
	void DeleteClient(Client* client);
	void PacketControl(CharClient* client, Packet* pData);
};

#endif