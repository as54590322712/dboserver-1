#ifndef _GAMENETWORK_H
#define _GAMENETWORK_H

#include <Network.h>
#include <Config.h>
#include "GameProtocol.h"

class GameClient : public Client
{
public:
	GameClient();
	~GameClient();

	// FUNCTIONS
	void LoadSendCharacterData(sGU_AVATAR_CHAR_INFO* data);

	// PROTOCOL
	void SendGameEnterRes(sUG_GAME_ENTER_REQ* data);
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