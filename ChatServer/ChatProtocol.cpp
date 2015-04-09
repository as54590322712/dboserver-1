#include "ChatNetwork.h"
#include "ChatProtocol.h"

bool ChatClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();

	switch (data->wOpCode)
	{
	case UT_ENTER_CHAT: SendChatEnterRes((sUT_ENTER_CHAT*)data); break;
	case UT_CHAT_MESSAGE_SAY: SendChatSay((sUT_CHAT_MESSAGE_SAY*)data); break;

	// SYS PACKETS
	case SYS_ALIVE: { ResetAliveTime(); } break;
	case SYS_PING: break;
	default:
		Logger::Log("Received Opcode: %s\n", NtlGetPacketName_UT(data->wOpCode));
		return false;
		break;
	}
	return true;
}

void ChatClient::SendChatEnterRes(sUT_ENTER_CHAT* pData)
{
	memcpy(AuthKey, pData->abyAuthKey, NTL_MAX_SIZE_AUTH_KEY);
	AccountID = pData->accountId;
	GetCharInfo();
	sTU_ENTER_CHAT_RES pRes;
	pRes.wOpCode = TU_ENTER_CHAT_RES;
	pRes.wResultCode = CHAT_SUCCESS;
	Send(&pRes, sizeof(pRes));

	pServer->GetChatManager()->AddClient(this);
}

void ChatClient::SendChatSay(sUT_CHAT_MESSAGE_SAY* pData)
{
	GetCharInfo();
	sTU_CHAT_MESSAGE_SAY pSay;
	memset(&pSay, 0, sizeof(pSay));
	pSay.wOpCode = TU_CHAT_MESSAGE_SAY;
	pSay.hSubject = CharSerialID;
	memcpy(pSay.awchSenderCharName, charName, NTL_MAX_SIZE_CHAR_NAME_UNICODE);
	memcpy(pSay.awchMessage, pData->awchMessage, NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE);
	pSay.wMessageLengthInUnicode = pData->wMessageLengthInUnicode;
	Logger::Log("%s says: %s\n", GameString(pSay.awchSenderCharName).c_str(), GameString(pSay.awchMessage).c_str());
	pServer->GetChatManager()->SendAll(&pSay, sizeof(pSay));
}