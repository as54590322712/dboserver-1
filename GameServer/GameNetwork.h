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

	PCHAR_PROFILE PcProfile;
	CHARSTATE CharState;

	// FUNCTIONS
	void LoadSendCharacterData(sGU_AVATAR_CHAR_INFO* data);
	void LoadWorldInfoData(sGU_AVATAR_WORLD_INFO* data);
	unsigned int GetPCTblidx(BYTE Race, BYTE Gender, BYTE Class);

	// PROTOCOL
	void SendGameEnterRes(sUG_GAME_ENTER_REQ* data);
	void SendCharInfo();
	void SendCharInfoEnd();
	void SendCharWorldInfo();
	void SendCharWorldInfoEnd();
	void SendCharMove(sUG_CHAR_MOVE* data);
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