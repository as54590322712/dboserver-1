#ifndef _GAMENETWORK_H
#define _GAMENETWORK_H

#include <iostream>
#include <fstream>

// BaseLib
#include <Network.h>
#include <Acceptor.h>
#include <Connector.h>
#include <Session.h>
#include <SessionFactory.h>
#include <Packet.h>
#include <Config.h>
#include <ServerApp.h>
#include <Database.h>
#include <Encoder.h>
#include <PCTable.h>
#include <SpawnTable.h>

#include "GameProtocol.h"
#include "CharacterManager.h"
#include "ObjectManager.h"

enum GAME_SESSION
{
	SESSION_CLIENT,
	SESSION_SERVER_ACTIVE,
};

const DWORD	MAX_NUMOF_GAME_CLIENT = 3;
const DWORD	MAX_NUMOF_SERVER = 1;
const DWORD	MAX_NUMOF_SESSION = MAX_NUMOF_GAME_CLIENT + MAX_NUMOF_SERVER;

class GameServer;
class GameClientFactory;

class GameClient : public Session
{
	friend class GameClientFactory;
public:
	GameClient(bool IsAliveCheck = false, bool IsOpcodeCheck = false);
	~GameClient();

	int	OnAccept();
	void OnClose();
	int	OnDispatch(Packet* pPacket);
	void Send(void* pData, int nSize);
	void Send(void* pData, int nSize, int nHandle);
	unsigned int GetCharSerialID() { return CharSerialID; };
	unsigned int GetCharID() { return CurrCharID; };
	int GetServerID() { return CurrServerID; }
	void AddSpawn(unsigned int nHandle, BYTE byType);
	void RemoveSpawn(unsigned int nHandle);
	bool FindSpawn(unsigned int nHandle, BYTE byType);
	void InsertOnlineData();
	void RemoveOnlineData();

	// Opcode Control
	bool PacketControl(Packet* pPacket);

	// FUNCTIONS
	void LoadCharacterData();
	void LoadWorldInfoData();
	unsigned int GetPCTblidx(BYTE Race, BYTE Gender, BYTE Class);
	void UpdatePositions(sVECTOR2 Dir, sVECTOR3 Loc);
	void UpdatePositions(sVECTOR3 Dir, sVECTOR3 Loc);
	int LoadItemData();
	int LoadSkillData();
	int LoadQuickslotData();
	void CalculateAtributes(PCData* pcdata);
	sGU_OBJECT_CREATE GetCharSpawnData();
	sGU_ITEM_CREATE InsertNextBagSlot(ITEMID item, BYTE qtd = 1);
	HOBJECT GetInventoryItemSerialID(BYTE byPlace, BYTE byPos);
	void UpdateItemInventoryPosition(HOBJECT hItem, BYTE byPlace, BYTE byPos);
	void GetItemBrief(sITEM_BRIEF& sBrief, HOBJECT hItem);

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
	void SendCharReadySpawnReq();
	void SendCharReadyRes(sUG_CHAR_READY* pData);
	void CheckCommand(sUG_SERVER_COMMAND* pData);
	void SendCharBuffsInfo();
	void SendAvatarWarFogInfo();
	void SendAuthkeyCommSrvRes();
	void SendGameLeaveRes();
	void SendCharDestMove(sUG_CHAR_DEST_MOVE* pData);
	void SendCharMoveSync(sUG_CHAR_MOVE_SYNC* pData);
	void SpawnTesteMob(unsigned int id);
	void SendCharJump(sUG_CHAR_JUMP* pData);
	void SendCharJumpEnd();
	void SendCharChangeHeading(sUG_CHAR_CHANGE_HEADING* pData);
	void SendCharExitRes();
	void SendGameExitRes();
	void SendIemMoveRes(sUG_ITEM_MOVE_REQ* pData);
	void UpdateCharObjEquips(HOBJECT hItem, BYTE byPos);
	void SendTSConfirmRes(sUG_TS_CONFIRM_STEP_REQ* pData);
	void SendSocialAction(sUG_SOCIAL_ACTION* pData);
	void SendTutoHintUpdateRes(sUG_TUTORIAL_HINT_UPDATE_REQ* pData);

	//CASH/EVENT SHOPS
	void SendEventItemStartRes();
	void SendEventItemEndRes();
	void SendNetpyItemStartRes();
	void SendNetpyItemEndRes();

private:
	PacketEncoder _packetEncoder;
	GameServer* pServer;

	WCHAR userName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR passWord[NTL_MAX_SIZE_USERPW_UNICODE + 1];
	WCHAR charName[NTL_MAX_SIZE_CHAR_NAME_UNICODE + 1];
	WCHAR guildName[NTL_MAX_SIZE_GUILD_NAME_IN_UNICODE + 1];
	BYTE AuthKey[NTL_MAX_SIZE_AUTH_KEY];
	int AccountID;
	BYTE LastServerID;
	DWORD AcLevel;
	BYTE CurrServerID;
	BYTE CurrChannelID;
	unsigned int CurrCharID;
	bool goCharServer;
	bool isGameMaster;
	bool TutorialMode;
	unsigned int CharSerialID;

	BYTE byMoveDirection;
	BYTE byAvatarType;

public:
	sPC_PROFILE PcProfile;
	sCHARSTATE CharState;
	sWORLD_INFO worldInfo;
	sITEM_PROFILE ItemProfile[NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM];
	sSKILL_INFO SkillInfo[NTL_MAX_PC_HAVE_SKILL];
	sQUICK_SLOT_PROFILE QuickSlotData[NTL_CHAR_QUICK_SLOT_MAX_COUNT];

private:
	std::map<unsigned int, BYTE>  objSpawn;
	typedef std::pair<unsigned int, BYTE> objSp;
};

class GameClientFactory : public SessionFactory
{
public:
	Session* CreateSession(unsigned short sessionType)
	{
		Session* pSession = NULL;
		switch (sessionType)
		{
		case SESSION_CLIENT:
		{
			pSession = new GameClient;
		}
		break;

		default:
			break;
		}
		return pSession;
	}
};

class ClientLink
{
public:
	ClientLink(GameClient* pClient) { m_pClient = pClient; }
	~ClientLink(void) {}
	GameClient* GetClient() { return m_pClient; }
protected:
	GameClient* m_pClient;
};

class GameServer : public ServerApp
{
public:
	int	OnInitApp();
	int	OnCreate();
	void OnDestroy() {}
	int	OnConfiguration(const char* ConfigFile);
	int OnCommandArgument(int argc, _TCHAR* argv[]) { return 0; }
	int	OnAppStart();

	unsigned int AcquireSerialID();

	CharacterManager* GetClientManager() { return _charManager; }
	ObjectManager* GetObjectManager() { return _objManager; }

	void AddSpawn(SpawnData data, eOBJTYPE type);

	void Run()
	{
		DWORD TickCur, TickOld = ::GetTickCount();

		while (IsRunnable())
		{
			TickCur = ::GetTickCount();
			if (TickCur - TickOld >= 10000)
			{
				TickOld = TickCur;
			}
		}
	}

private:
	Acceptor _clientAcceptor;
	CharacterManager* _charManager;
	ObjectManager* _objManager;

public:
	Config* ServerCfg;
	Database* ServerDB;
	int ServerID;
	PCTable* pcTblData;
	SpawnTable* npcspawnTblData;
	SpawnTable* mobspawnTblData;
	unsigned int m_uiSerialID;
};

#endif