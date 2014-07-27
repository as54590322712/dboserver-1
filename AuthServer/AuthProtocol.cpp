#include "AuthNetwork.h"
#include "AuthProtocol.h"

void AuthClient::SendLoginRes(sUA_LOGIN_REQ* data)
{
	Logger::Log("-- LOGIN  RESULT USER: %S PASS: %S --\n", data->UserName, data->PassWord);

	memcpy(userName, data->UserName, MAX_USERNAME_SIZE);
	memcpy(passWord, data->PassWord, MAX_PASSWORD_SIZE);

	sAU_LOGIN_RES lRes;
	memset(&lRes, 0, sizeof(sAU_LOGIN_RES));
	lRes.OpCode = AU_LOGIN_RES;
	lRes.AccountID = 10002;
	memcpy(lRes.AuthKey, GenAuthKey(), MAX_AUTHKEY_SIZE);
	lRes.LastServerID = 0;
	lRes.ResultCode = AUTH_SUCCESS;
	lRes.AcLevel = 0xFFFF;
	memcpy(lRes.UserName, data->UserName, MAX_USERNAME_SIZE);

	// servers
	lRes.ServerCount = 1;
	memcpy(lRes.Servers[0].CharServerIP, "127.0.0.1", MAX_SRVADDR_SIZE);
	lRes.Servers[0].CharServerPort = 50300;
	lRes.Servers[0].Load = 100;
	Send((unsigned char*)&lRes, sizeof(lRes));
}

void AuthClient::SendDisconnectRes(sUA_LOGIN_DISCONNECT_REQ* data)
{
	if (data->IsEnteringCharacterServer)
	{
		Logger::Log("-- DISCONNECT REQ --\n");
		sAU_LOGIN_DISCONNECT_RES dRes;
		memset(&dRes, 0, sizeof(sAU_LOGIN_DISCONNECT_RES));
		dRes.OpCode = AU_LOGIN_DISCONNECT_RES;
		Send((unsigned char*)&dRes, sizeof(dRes));
		pServer->Disconnect(this);
	}
}