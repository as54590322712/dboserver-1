#ifndef _NETWORK_H
#define _NETWORK_H

#include <winsock2.h>
#include <thread>
#include <windows.h>
#include <winbase.h>
#include <string>
#include <process.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <exception>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <csignal>
#include <pthread.h>
#include <asio.hpp>
#include "Def.h"
#include "Packet.h"
#include "Logger.h"
#include "Config.h"
#include "Database.h"
#include "Encryption.h"

#define close closesocket
#define MAX_THREADS 65535

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "pthreadVC2.lib")

using namespace asio;
using namespace asio::ip;

class Base
{
public:
	Base() { isActive = false; sock = INVALID_SOCKET; pkt = new Packet(); pEncoder = new PacketEncoder(false); };
	virtual ~Base() {};
	SOCKET sock;
	bool isActive;
	int Opt = 1;
	Packet* pkt;
	PacketEncoder* pEncoder;
};

class Client : public Base
{
public:
	Client();
	virtual ~Client() {};
	bool ReceivingData();
	void Send(void* pData, int size);
	bool IsConnected();
	class Server* pServer;
	unsigned char pData[MAX_BUFFER_SIZE];
	unsigned int LastPacketSize;
	unsigned int RecvCount;
	unsigned int SendCount;
	sockaddr_in* addr;

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
	bool goGameServer;
};

class Server : public Base
{
	public:
		Server() {};
		virtual ~Server() {};
		bool Start();
		void Loop();
		void AddClient(SOCKET sock, sockaddr_in* addr);
		void CheckFDS(fd_set* fds);
		void HandleClients(fd_set* fds);
		void Disconnect(Client* cli);
		
		virtual Client* CreateClient();
		virtual void DeleteClient(Client* client);
		virtual void OnReady() {};
		virtual void OnServerStep() {};
		virtual bool OnConnect(Client* client) { return true; };
		virtual void OnDisconnect(Client* client) {};
		virtual bool OnDataReceived(Client* client, Packet* pData) { return true; };

		WSADATA wsData;
		int sPort = SERVER_PORT;
		sockaddr_in addrServer;
		std::vector<Client*> Clients;
		Config* ServerConfig;
		Database* ServerDB;
		int ServerID;
		pthread_t threads[MAX_THREADS];
};

void* ClientThread(void* _client);

#endif