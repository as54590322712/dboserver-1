#ifndef _AUTHNETWORK_H
#define _AUTHNETWORK_H

#include <Network.h>

class AuthServer : public Server
{
public:
	AuthServer();
	virtual ~AuthServer();

	void OnReady();
	bool OnConnect(Client* client);
	void OnDisconnect(Client* client);
	bool OnDataReceived(Client* client, unsigned char* pData);
};

#endif