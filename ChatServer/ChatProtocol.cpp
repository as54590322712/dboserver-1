#include "ChatNetwork.h"
#include "ChatProtocol.h"

bool ChatClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();

	switch (data->wOpCode)
	{
	case 1: { sNTLPACKETHEADER reply(1); Send(&reply, sizeof(reply)); } break;
	default:
		Logger::Log("Received Opcode: %s\n", NtlGetPacketName_UT(data->wOpCode));
		return false;
		break;
	}
	return true;
}