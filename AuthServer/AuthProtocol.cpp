#include "AuthNetwork.h"
#include "AuthProtocol.h"

bool AuthClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();
	switch (data->wOpCode)
	{
	case UA_LOGIN_DISCONNECT_REQ: SendDisconnectRes((sUA_LOGIN_DISCONNECT_REQ*)data); break;
	case UA_LOGIN_REQ: SendLoginRes((sUA_LOGIN_REQ*)data); break;
	case 1: { sNTLPACKETHEADER reply(1); Send(&reply, sizeof(reply)); } break;
	default:
		Logger::Log("Received Opcode: %s\n", NtlGetPacketName_UA(data->wOpCode));
		return false;
		break;
	}
	return true;
}

void AuthClient::SendLoginRes(sUA_LOGIN_REQ* data)
{
	memcpy(userName, data->awchUserId, NTL_MAX_SIZE_USERID_UNICODE);
	memcpy(passWord, data->awchPasswd, NTL_MAX_SIZE_USERPW_UNICODE);
	AccountID = GetDBAccountID();

	sAU_LOGIN_RES lRes;
	memset(&lRes, 0, sizeof(sAU_LOGIN_RES));
	lRes.wOpCode = AU_LOGIN_RES;
	lRes.accountId = AccountID;
	memcpy(lRes.abyAuthKey, GenAuthKey(), NTL_MAX_SIZE_AUTH_KEY);
	lRes.lastServerFarmId = GetDBLastServerID();
	lRes.wResultCode = LoginVerifyAccount();
	lRes.dwAllowedFunctionForDeveloper = GetDBAccountAcLevel();
	memcpy(lRes.awchUserId, data->awchUserId, NTL_MAX_SIZE_USERID_UNICODE);

	// servers
	lRes.byServerInfoCount = pServer->ServerCfg->GetInt("ServerList", "Count");
	for (int x = 0; x < lRes.byServerInfoCount; x++)
	{
		char snode[20];
		sprintf_s(snode, "Server%d", x + 1);
		memcpy(lRes.aServerInfo[x].szCharacterServerIP, pServer->ServerCfg->GetChildStr("ServerList", snode, "IP"), NTL_MAX_LENGTH_OF_IP);
		lRes.aServerInfo[x].wCharacterServerPortForClient = pServer->ServerCfg->GetChildInt("ServerList", snode, "Port");
		lRes.aServerInfo[x].dwLoad = 0;
	}
	Send((unsigned char*)&lRes, sizeof(lRes));
}

void AuthClient::SendDisconnectRes(sUA_LOGIN_DISCONNECT_REQ* data)
{
	if (data->bIsEnteringCharacterServer) goCharServer = true;
	sAU_LOGIN_DISCONNECT_RES dRes;
	memset(&dRes, 0, sizeof(sAU_LOGIN_DISCONNECT_RES));
	dRes.wOpCode = AU_LOGIN_DISCONNECT_RES;
	Send((unsigned char*)&dRes, sizeof(dRes));
}