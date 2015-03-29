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
#include "ChatProtocol.h"

enum CHAT_SESSION
{
	SESSION_CLIENT,
	SESSION_SERVER_ACTIVE,
};

const DWORD	MAX_NUMOF_GAME_CLIENT = 3;
const DWORD	MAX_NUMOF_SERVER = 1;
const DWORD	MAX_NUMOF_SESSION = MAX_NUMOF_GAME_CLIENT + MAX_NUMOF_SERVER;

class ChatServer;
class ChatClientFactory;

class ChatClient : public Session
{
	friend class ChatClientFactory;
public:
	ChatClient(bool IsAliveCheck = false, bool IsOpcodeCheck = false);
	~ChatClient();

	int	OnAccept();
	void OnClose();
	int	OnDispatch(Packet* pPacket);
	void Send(void* pData, int nSize);
	unsigned int GetCharSerialID() { return CharSerialID; };

	// Opcode Control
	bool PacketControl(Packet* pPacket);

private:
	PacketEncoder _packetEncoder;
	ChatServer* pServer;

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
	unsigned int CharSerialID;
};

class ChatClientFactory : public SessionFactory
{
public:
	Session* CreateSession(unsigned short sessionType)
	{
		Session* pSession = NULL;
		switch (sessionType)
		{
		case SESSION_CLIENT:
		{
			pSession = new ChatClient;
		}
		break;

		default:
			break;
		}
		return pSession;
	}
};

class ChatServer : public ServerApp
{
public:
	int	OnInitApp();
	int	OnCreate();
	void OnDestroy() {}
	int	OnConfiguration(const char* ConfigFile);
	int OnCommandArgument(int argc, _TCHAR* argv[]) { return 0; }
	int	OnAppStart();
	unsigned int AcquireCharSerialID();
	bool AddClient(const char* charName, ChatClient* pClient);
	void RemoveClient(const char* charName);
	bool FindClient(const char* charName);
	void SendAll(void* pData, int nSize);
	void SendOthers(void* pData, int nSize, ChatClient* pClient, bool distCheck = false);
	void RecvOthers(eOPCODE_TU Opcode, ChatClient* pClient, bool distCheck = false);
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
	unsigned int m_uiCharSerialID;

	typedef std::map<GameString, ChatClient*> CLENTLIST;
	typedef CLENTLIST::value_type CLIENTVAL;
	typedef CLENTLIST::iterator CLIENTIT;
	CLENTLIST clientList;
};

#endif