#ifndef _GAMENETWORK_H
#define _GAMENETWORK_H

#include <iostream>
#include <fstream>
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
#include "GameProtocol.h"

enum GAME_SESSION
{
	SESSION_CLIENT,
	SESSION_SERVER_ACTIVE,
};

const DWORD	MAX_NUMOF_GAME_CLIENT = 3;
const DWORD	MAX_NUMOF_SERVER = 1;
const DWORD	MAX_NUMOF_SESSION = MAX_NUMOF_GAME_CLIENT + MAX_NUMOF_SERVER;

class GameServer : public ServerApp
{
public:
	int	OnInitApp();
	int	OnCreate();
	void OnDestroy() {}
	int	OnConfiguration(const char* ConfigFile);
	int OnCommandArgument(int argc, _TCHAR* argv[]) { return 0; }
	int	OnAppStart();
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

public:
	Config* ServerCfg;
	Database* ServerDB;
	int ServerID;
	PCTable* pcTblData;
};

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

	// Opcode Control
	bool PacketControl(Packet* pPacket);

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

private:
	PacketEncoder _packetEncoder;
	GameServer* pServer;

	WCHAR userName[MAX_USERNAME_SIZE + 1];
	WCHAR passWord[MAX_PASSWORD_SIZE + 1];
	BYTE AuthKey[MAX_AUTHKEY_SIZE];
	int AccountID;
	BYTE LastServerID;
	DWORD AcLevel;
	BYTE CurrServerID;
	BYTE CurrChannelID;
	unsigned int CurrCharID;
	bool goCharServer;

	PCHAR_PROFILE PcProfile;
	CHARSTATE CharState;
	WORLD_INFO worldInfo;
	ITEM_PROFILE ItemProfile[MAX_INVEN_ITEMCOUNT];
	SKILL_INFO SkillInfo[MAX_PCHARSKILLS_COUNT];
	QUICK_SLOT_PROFILE QuickSlotData[CHAR_QUICK_SLOT_MAX_COUNT];
	bool TutorialMode;
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

#endif