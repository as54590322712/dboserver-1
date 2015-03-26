#include "ChatNetwork.h"

ChatClient::ChatClient(bool IsAliveCheck, bool IsOpcodeCheck)
	:Session(SESSION_CLIENT)
{
	SetControlFlag(CONTROL_FLAG_USE_SEND_QUEUE);

	if (IsAliveCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_ALIVE);
	}
	if (IsOpcodeCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_OPCODE);
	}

	SetPacketEncoder(&_packetEncoder);
	pServer = (ChatServer*)_GetApp();
}

ChatClient::~ChatClient()
{
}

int	ChatClient::OnAccept()
{
	return 0;
}

void ChatClient::OnClose()
{
}

int ChatClient::OnDispatch(Packet* pPacket)
{
	PacketControl(pPacket);
	//	return OnDispatch(pPacket);
	return 0;
}

void ChatClient::Send(void* pData, int nSize)
{
	Packet* packet = new Packet((unsigned char*)pData, nSize);
	int rc = pServer->Send(this->GetHandle(), packet);
	if (0 != rc)
	{
		Logger::Log("Failed to send packet %d\n", rc);
	}
}