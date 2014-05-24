#ifndef _SERVER_H
#define _SERVER_H

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <Ws2tcpip.h>
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
#include <string>
#include <cstdio>
#include <exception>
#include <time.h>
#include <assert.h>
#include <math.h>
#include <vector>
#include <csignal>
#include "Def.h"

#define close closesocket

#pragma comment(lib, "ws2_32.lib")

class Base
{
public:
	Base() { isActive = false; sock = INVALID_SOCKET; };
	~Base() {};
	SOCKET sock;
	bool isActive;
	int Opt = 1;
};

class Client : public Base
{
public:
	Client() {};
	~Client() {};
	bool ReceivingData();
	class Server* pServer;
	unsigned char pData[MAX_BUFFER_SIZE];
};

class Server : public Base
{
	public:
		Server() {};
		~Server() {};
		bool Start();
		void Loop();
		void AddClient(SOCKET sock, sockaddr_in* addr);
		void CheckFDS(fd_set* fds);
		void HandleClients(fd_set* fds);
		void Disconnect(Client* cli);
		
		virtual Client* CreateClient()  { return new Client(); };
		virtual void DeleteClient(Client * cli)  { delete cli; };
		virtual void OnReady() {};
		virtual void OnServerStep() {};
		virtual void OnConnect(Client* cli) {};
		virtual void OnDisconnect(Client* cli) {};
		virtual void OnDataReceived(Client* cli, unsigned char* pData) {};

		WSADATA wsData;
		int sPort = SERVER_PORT;
		unsigned char sBuffer[MAX_BUFFER_SIZE];
		sockaddr_in addrServer;
		hostent* sHost = NULL;
		std::vector<Client*> Clients;
};

#endif