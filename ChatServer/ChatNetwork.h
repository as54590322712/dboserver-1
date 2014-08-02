#ifndef _CHARNETWORK_H
#define _CHARNETWORK_H

#include <Network.h>
#include <Config.h>
#include "ChatProtocol.h"

class ChatClient : public Client
{
public:
	ChatClient();
	~ChatClient();

	// PROTOCOL FUNCTIONS
};

class ChatServer : public Server
{
public:
	ChatServer();
	~ChatServer();

	void OnReady();
	bool OnConnect(Client* client);
	void OnDisconnect(Client* client);
	bool OnDataReceived(Client* client, Packet* pData);
	ChatClient* CreateClient();
	void DeleteClient(Client* client);
	void PacketControl(ChatClient* client, Packet* pData);
};

#endif