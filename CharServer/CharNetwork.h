#ifndef _CHARNETWORK_H
#define _CHARNETWORK_H

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
#include <NewbieTable.h>
#include <PCTable.h>
#include "CharProtocol.h"

enum CHAR_SESSION
{
	SESSION_CLIENT,
	SESSION_SERVER_ACTIVE,
};

const DWORD	MAX_NUMOF_GAME_CLIENT = 3;
const DWORD	MAX_NUMOF_SERVER = 1;
const DWORD	MAX_NUMOF_SESSION = MAX_NUMOF_GAME_CLIENT + MAX_NUMOF_SERVER;

class CharServer;
class CharClientFactory;

class CharClient : public Session
{
	friend class CharClientFactory;
public:
	CharClient(bool IsAliveCheck = false, bool IsOpcodeCheck = false);
	~CharClient();

	int	OnAccept();
	void OnClose();
	int	OnDispatch(Packet* pPacket);
	void Send(void* pData, int nSize);

	// Opcode Control
	bool PacketControl(Packet* pPacket);

	// DATA FUNCTIONS
	int GetDBAccCharListData(sCU_CHARACTER_INFO* outdata);
	int DBInsertCharData(sPC_SUMMARY data, NewbieData nbdata);
	eRESULTCODE CheckUsedName(WCHAR* Name);
	eRESULTCODE DBChangeCharName(WCHAR* Name, int charId);
	int GetDBAllowedRaces();
	void DBUpdateLastServer();

	// PROTOCOL FUNCTIONS
	void SendLoginResult(sUC_LOGIN_REQ* data);
	void SendServerlist(bool one);
	void SendCharLoadResult(sUC_CHARACTER_LOAD_REQ* data);
	void SendCharExitRes(sUC_CHARACTER_EXIT_REQ* data);
	void SendCharCreateRes(sUC_CHARACTER_ADD_REQ* data);
	void SendCharDelRes(sUC_CHARACTER_DEL_REQ* data);
	void SendCharDelCancelRes(sUC_CHARACTER_DEL_CANCEL_REQ* data);
	void SendCharConnWaitCheckRes(sUC_CONNECT_WAIT_CHECK_REQ* data);
	void SendCharSelectRes(sUC_CHARACTER_SELECT_REQ* data);
	void SendCharRenameRes(sUC_CHARACTER_RENAME_REQ* data);
	void SendCancelWaitReq(sUC_CONNECT_WAIT_CANCEL_REQ* data);

private:
	PacketEncoder _packetEncoder;
	CharServer* pServer;

	WCHAR userName[NTL_MAX_SIZE_USERID_UNICODE + 1];
	WCHAR passWord[NTL_MAX_SIZE_USERPW_UNICODE + 1];
	BYTE AuthKey[NTL_MAX_SIZE_AUTH_KEY];
	int AccountID;
	BYTE LastServerID;
	DWORD AcLevel;
	BYTE CurrServerID;
	BYTE CurrChannelID;
	unsigned int CurrCharID;
	bool goGameServer;
};

class CharClientFactory : public SessionFactory
{
public:
	Session* CreateSession(unsigned short sessionType)
	{
		Session* pSession = NULL;
		switch (sessionType)
		{
		case SESSION_CLIENT:
		{
			pSession = new CharClient;
		}
		break;

		default:
			break;
		}
		return pSession;
	}
};

class CharServer : public ServerApp
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
	NewbieTable* nbTblData;
	PCTable* pcTblData;
};

#endif