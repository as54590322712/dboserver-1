#include "CharNetwork.h"
#include "CharProtocol.h"

void CharClient::SendLoginResult(sUC_LOGIN_REQ* data)
{
	sCU_LOGIN_RES lRes;
	Logger::Log("ACCID: %d SRVID: %d AUTHKEY: %s\n", data->accountId, data->serverID, data->AuthKey);
	memset(&lRes, 0, sizeof(sCU_LOGIN_RES));
	lRes.OpCode = CU_LOGIN_RES;
	lRes.ResultCode = CHARACTER_SUCCESS;
	Send((unsigned char*)&lRes, sizeof(lRes));
}

void CharClient::SendServerlistOne(Packet* data)
{
}