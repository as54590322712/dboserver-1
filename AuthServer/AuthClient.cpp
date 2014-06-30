#include "AuthNetwork.h"

AuthClient::AuthClient() {}

AuthClient::~AuthClient() {}

char* AuthClient::GenAuthKey()
{
	BYTE Key[MAX_AUTHKEY_SIZE];
	for (int i = 0; i < 16; i++)
	{
		srand(((unsigned int)time(NULL)) + i);
		Key[i] = rand() % 126 + 33;
	}
	return (char*)&Key[0];
}