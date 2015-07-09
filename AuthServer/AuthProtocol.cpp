#include "AuthNetwork.h"
#include "AuthProtocol.h"

bool AuthClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();
	switch (data->wOpCode)
	{
	case UA_LOGIN_TW_REQ: SendLoginRes((sUA_LOGIN_REQ*)data); break;
	case UA_LOGIN_DISCONNECT_REQ: SendDisconnectRes((sUA_LOGIN_DISCONNECT_REQ*)data); break;

	default:
		Logger::Log("Recv Opcode [%d]: %s\n", data->wOpCode, NtlGetPacketName_UA(data->wOpCode));
		return false;
		break;
	}
	return true;
}

void AuthClient::SendCommercialNfy()
{
	sAU_COMMERCIAL_SETTING_NFY sPkt;
	sPkt.wOpCode = AU_COMMERCIAL_SETTING_NFY;
	Send(&sPkt, sizeof(sPkt));
}

void AuthClient::SendLoginRes(sUA_LOGIN_REQ* data)
{
	SendCommercialNfy();
	memcpy(userName, data->awchUserId, NTL_MAX_SIZE_USERID_UNICODE);
	memcpy(passWord, data->awchPasswd, NTL_MAX_SIZE_USERPW_UNICODE);
	AccountID = GetDBAccountID();

	sAU_LOGIN_RES lRes;
	memset(&lRes, 0, sizeof(sAU_LOGIN_RES));
	lRes.wOpCode = AU_LOGIN_RES;
	lRes.accountId = AccountID;
	memcpy(lRes.abyAuthKey, GenAuthKey(), NTL_MAX_SIZE_AUTH_KEY);
	lRes.lastServerFarmId = GetDBLastServerID();
	lRes.lastChannelId = 0; // Need to know what is, by defaul leave 8
	lRes.wResultCode = LoginVerifyAccount();
	lRes.dwAllowedFunctionForDeveloper = GetDBAccountAcLevel();
	memcpy(lRes.awchUserId, data->awchUserId, NTL_MAX_SIZE_USERID_UNICODE);

	// servers
	lRes.byServerInfoCount = pServer->ServerCfg->GetInt("CharServerList", "Count");
	for (int x = 0; x < lRes.byServerInfoCount; x++)
	{
		char snode[20];
		sprintf_s(snode, "CharServer%d", x + 1);
		memcpy(lRes.aServerInfo[x].szCharacterServerIP, pServer->ServerCfg->GetChildStr("CharServerList", snode, "IP"), NTL_MAX_LENGTH_OF_IP);
		lRes.aServerInfo[x].wCharacterServerPortForClient = pServer->ServerCfg->GetChildInt("CharServerList", snode, "Port");
		lRes.aServerInfo[x].dwLoad = 1;
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