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

void Client::Send(unsigned char* pData, int size)
{
	Packet* out = new Packet(pData, size, false);
	out->pHeader->bySequence = SendCount;
	u_long iMode = 1;
	if (ioctlsocket(sock, FIONBIO, &iMode) != 0) std::cout << "error - ioctlsocket" << std::endl;
	int retval = send(sock, (char*)out->GetPacketBuffer(), out->GetUsedSize(), 0);
	iMode = 0;
	if (ioctlsocket(sock, FIONBIO, &iMode) != 0) std::cout << "error - ioctlsocket" << std::endl;
	SendCount++;
}