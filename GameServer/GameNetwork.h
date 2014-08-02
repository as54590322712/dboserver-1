#ifndef _CHARNETWORK_H
#define _CHARNETWORK_H

#include <Network.h>
#include <Config.h>
#include "GameProtocol.h"

class GameClient : public Client
{
public:
	GameClient();
	~GameClient();

	// PROTOCOL FUNCTIONS
};

class GameServer : public Server
{
public:
	GameServer();
	~GameServer();

	void OnReady();
	bool OnConnect(Client* client);
	void OnDisconnect(Client* client);
	bool OnDataReceived(Client* client, Packet* pData);
	GameClient* CreateClient();
	void DeleteClient(Client* client);
	void PacketControl(GameClient* client, Packet* pData);
};

#endif