#include "Network.h"

Client::Client()
{
	pServer = NULL;
	SendCount = RecvCount = LastPacketSize = 0;
	ZeroMemory(&pData, MAX_BUFFER_SIZE);
	goCharServer = goGameServer = false;
}

bool Client::ReceivingData()
{
	ZeroMemory(&pData, MAX_BUFFER_SIZE);

	LastPacketSize = recv(sock, (char*)pData, MAX_BUFFER_SIZE, 0);
	if (LastPacketSize <= 0) return false;

	RecvCount++;
	pkt->Attach(pData, false);
	pServer->OnDataReceived(this, pkt);
	return true;
}

void Client::Send(void* pData, int size)
{
	Packet* out = new Packet((unsigned char*)pData, size, false);
	out->pHeader->bySequence = SendCount;
	u_long iMode = 1;
	int rc = ioctlsocket(sock, FIONBIO, &iMode);
	if (rc == SOCKET_ERROR)	std::cout << "ioctlsocket() failed" << std::endl;
	send(sock, (char*)out->GetPacketBuffer(), out->GetUsedSize(), 0);
	iMode = 0;
	rc = ioctlsocket(sock, FIONBIO, &iMode);
	if (rc == SOCKET_ERROR)	std::cout << "ioctlsocket() failed" << std::endl;
	SendCount++;
}

bool Client::IsConnected()
{
	int optval, optlen = sizeof(optval);
	int res = getsockopt(this->sock, SOL_SOCKET, SO_ERROR, (char *)&optval, &optlen);
	if (optval == 0 && res == 0) return true;
	return false;
}