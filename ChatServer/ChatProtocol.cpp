#include "ChatNetwork.h"
#include "ChatProtocol.h"

bool ChatClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();

	switch (data->wOpCode)
	{
	case 1: { sPACKETHEADER reply(1); Send(&reply, sizeof(reply)); } break;
	default:
		Logger::Log("Received Opcode: %d\n", data->wOpCode);
		return false;
		break;
	}
	return true;
}