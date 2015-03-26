#include "AuthNetwork.h"
#include "AuthProtocol.h"

bool AuthClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();
	switch (data->wOpCode)
	{
	case UA_LOGIN_DISCONNECT_REQ: SendDisconnectRes((sUA_LOGIN_DISCONNECT_REQ*)data); break;
	case UA_LOGIN_REQ: SendLoginRes((sUA_LOGIN_REQ*)data); break;
	case 1: { sPACKETHEADER reply(1); Send(&reply, sizeof(reply)); } break;
	default:
		Logger::Log("Received Opcode: %d\n", data->wOpCode);
		return false;
		break;
	}
	return true;
}

void AuthClient::SendLoginRes(sUA_LOGIN_REQ* data)
{
	memcpy(userName, data->UserName, MAX_USERNAME_SIZE);
	memcpy(passWord, data->PassWord, MAX_PASSWORD_SIZE);
	AccountID = GetDBAccountID();

	sAU_LOGIN_RES lRes;
	memset(&lRes, 0, sizeof(sAU_LOGIN_RES));
	lRes.OpCode = AU_LOGIN_RES;
	lRes.AccountID = AccountID;
	memcpy(lRes.AuthKey, GenAuthKey(), MAX_AUTHKEY_SIZE);
	lRes.LastServerID = GetDBLastServerID();
	lRes.ResultCode = LoginVerifyAccount();
	lRes.AcLevel = GetDBAccountAcLevel();
	memcpy(lRes.UserName, data->UserName, MAX_USERNAME_SIZE);

	// servers
	lRes.ServerCount = pServer->ServerCfg->GetInt("ServerList", "Count");
	for (int x = 0; x < lRes.ServerCount; x++)
	{
		char snode[20];
		sprintf_s(snode, "Server%d", x + 1);
		memcpy(lRes.Servers[x].CharServerIP, pServer->ServerCfg->GetChildStr("ServerList", snode, "IP"), MAX_SRVADDR_SIZE);
		lRes.Servers[x].CharServerPort = pServer->ServerCfg->GetChildInt("ServerList", snode, "Port");
		lRes.Servers[x].Load = 0;
	}
	Send((unsigned char*)&lRes, sizeof(lRes));
}

void AuthClient::SendDisconnectRes(sUA_LOGIN_DISCONNECT_REQ* data)
{
	if (data->IsEnteringCharacterServer) goCharServer = true;
	sAU_LOGIN_DISCONNECT_RES dRes;
	memset(&dRes, 0, sizeof(sAU_LOGIN_DISCONNECT_RES));
	dRes.OpCode = AU_LOGIN_DISCONNECT_RES;
	Send((unsigned char*)&dRes, sizeof(dRes));
}