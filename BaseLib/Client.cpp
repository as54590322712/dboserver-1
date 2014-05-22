#include "Network.h"

bool Client::ReceivingData()
{
	int rc;
	ZeroMemory(&pData, MAX_BUFFER_SIZE);

	rc = recv(sock, (char*)pData, MAX_BUFFER_SIZE, 0);
	if (rc <= 0) return false;

	pServer->OnDataReceived(this, pData);

	return true;
}