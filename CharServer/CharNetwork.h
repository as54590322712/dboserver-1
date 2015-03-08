#ifndef _CHARNETWORK_H
#define _CHARNETWORK_H

#include <Network.h>
#include <Config.h>
#include "CharProtocol.h"

class CharClient : public Client
{
public:
	CharClient();
	~CharClient();

	int GetDBAccCharListData(sCU_CHARACTER_INFO* outdata);
	void DBInsertCharData(CHARDATA data);
	ResultCodes CheckUsedName(WCHAR* Name);
	ResultCodes DBChangeCharName(WCHAR* Name, int charId);
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