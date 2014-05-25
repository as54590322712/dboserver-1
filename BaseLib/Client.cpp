#include "Network.h"

Client::Client()
{
	pServer = NULL;
	SendCount = RecvCount = LastPacketSize = 0;
	ZeroMemory(&pData, MAX_BUFFER_SIZE);
}

bool Client::ReceivingData()
{
	ZeroMemory(&pData, MAX_BUFFER_SIZE);

	LastPacketSize = recv(sock, (char*)pData, MAX_BUFFER_SIZE, 0);
	if (LastPacketSize <= 0) return false;

	RecvCount++;
	pServer->OnDataReceived(this, pData);

	return true;
}

void Client::Send(unsigned char* pData, int size)
{
	u_long iMode = 1;
	if (ioctlsocket(sock, FIONBIO, &iMode) != 0) std::cout << "error - ioctlsocket" << std::endl;
	int retval = send(sock, (char*)pData, size, 0);
	iMode = 0;
	if (ioctlsocket(sock, FIONBIO, &iMode) != 0) std::cout << "error - ioctlsocket" << std::endl;
	SendCount++;
}