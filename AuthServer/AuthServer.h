#ifndef _AUTHNETWORK_H
#define _AUTHNETWORK_H

#include <Network.h>

class AuthServer : public Server
{
public:
	AuthServer();
	virtual ~AuthServer();

	void OnConnect(Client* cli);
	void OnDisconnect(Client* cli);
};

#endif