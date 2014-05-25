#ifndef _NETWORK_H
#define _NETWORK_H

#include <winsock2.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
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
#include "Def.h"

#define close closesocket

#pragma comment(lib, "ws2_32.lib")

class Base
{
public:
	Base() { isActive = false; sock = INVALID_SOCKET; };
	virtual ~Base() {};
	SOCKET sock;
	bool isActive;
	int Opt = 1;
};

class Client : public Base
{
public:
	Client();
	virtual ~Client() {};
	bool ReceivingData();
	void Send(unsigned char* pData, int size);
	class Server* pServer;
	unsigned char pData[MAX_BUFFER_SIZE];
	int LastPacketSize;
	int RecvCount;
	int SendCount;
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
		virtual bool OnDataReceived(Client* client, unsigned char* pData) { return true; };

		WSADATA wsData;
		int sPort = SERVER_PORT;
		sockaddr_in addrServer;
		std::vector<Client*> Clients;
};

#endif