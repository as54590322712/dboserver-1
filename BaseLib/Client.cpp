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
	RecvCount++;
	if (LastPacketSize == -1) return false;
	else if (LastPacketSize >= (HEADER_SIZE + 2))
	{
		pkt->Attach(pData);
		LPPACKETHEADER header = pkt->GetPacketHeader();
		if (pEncoder) pEncoder->RxDecrypt(header);
		unsigned int pktsize = header->wPacketLen + HEADER_SIZE;
		if (LastPacketSize >= pktsize)
		{
			if (pEncoder) pEncoder->RxDecrypt(*pkt);
			pServer->OnDataReceived(this, pkt);
		}
	}
	else return false;
	return true;
}

void Client::Send(void* pData, int size)
{
	Packet* out = new Packet((unsigned char*)pData, size);
	out->GetPacketHeader()->bySequence = (BYTE)(SendCount & PACKET_MAX_SEQUENCE);
	if (pEncoder) pEncoder->TxEncrypt(*out);
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
	if (optval == 0 && res == 0)
		return true;
	return false;
}