#ifndef _CHARNETWORK_H
#define _CHARNETWORK_H

#include <Network.h>

class CharClient : public Client
{
public:
	CharClient();
	~CharClient();
};

class CharServer : public Server
{
public:
	CharServer();
	~CharServer();

	void OnReady();
	bool OnConnect(Client* client);
	void OnDisconnect(Client* client);
	bool OnDataReceived(Client* client, unsigned char* pData);
	CharClient* CreateClient();
	void DeleteClient(Client* client);
	void PacketControl(CharClient* client, unsigned char* pData);
};

#endif