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
	WORLD_INFO worldInfo;
	ITEM_PROFILE ItemProfile[MAX_INVEN_ITEMCOUNT];
	SKILL_INFO SkillInfo[MAX_PCHARSKILLS_COUNT];
	QUICK_SLOT_PROFILE QuickSlotData[CHAR_QUICK_SLOT_MAX_COUNT];
	bool TutorialMode;

	// FUNCTIONS
	void LoadCharacterData();
	void LoadWorldInfoData();
	unsigned int GetPCTblidx(BYTE Race, BYTE Gender, BYTE Class);
	void UpdatePositions(VECTORXY Dir, VECTORXYZ Loc);
	int LoadItemData();
	int LoadSkillData();
	int LoadQuickslotData();

	// PROTOCOL
	void SendGameEnterRes(sUG_GAME_ENTER_REQ* data);
	void SendCharInfo();
	void SendCharInfoEnd();
	void SendCharWorldInfo();
	void SendCharWorldInfoEnd();
	void SendCharMove(sUG_CHAR_MOVE* data);
	void SendCharItemInfo();
	void SendCharSkillInfo();
	void SendCharQuickSlotInfo();
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