#include "CharNetwork.h"
#include "CharProtocol.h"

void CharClient::SendLoginResult(sUC_LOGIN_REQ* data)
{
	Logger::Log("-- CHAR LOGIN RESULT --\n", data->accountId, data->serverID);
	LastServerID = data->serverID;
	AccountID = data->accountId;
	memcpy(AuthKey, data->AuthKey, MAX_AUTHKEY_SIZE);

	sCU_LOGIN_RES lRes;
	memset(&lRes, 0, sizeof(sCU_LOGIN_RES));
	lRes.OpCode = CU_LOGIN_RES;
	lRes.ResultCode = CHARACTER_SUCCESS;
	lRes.RaceAllowedFlag = 255; // Opened Races at Character Creation (0 = none, 255 = all)
	Send((unsigned char*)&lRes, sizeof(lRes));
}

void CharClient::SendServerlistOne()
{
	Logger::Log("-- SERVER LIST ONE --\n");
	sCU_SERVER_FARM_INFO sinfo;
	memset(&sinfo, 0, sizeof(sCU_SERVER_FARM_INFO));
	sinfo.OpCode = CU_SERVER_FARM_INFO;
	sinfo.serverInfo.serverId = LastServerID;
	wcscpy_s(sinfo.serverInfo.ServerName, L"Beta Test");
	sinfo.serverInfo.ServerStatus = SERVERSTATUS_UP;
	sinfo.serverInfo.Load = 0;
	sinfo.serverInfo.MaxLoad = 100;
	Send((unsigned char*)&sinfo, sizeof(sinfo));

	sCU_CHARACTER_SERVERLIST_ONE_RES slone;
	memset(&slone, 0, sizeof(sCU_CHARACTER_SERVERLIST_ONE_RES));
	slone.OpCode = CU_CHARACTER_SERVERLIST_ONE_RES;
	slone.ResultCode = CHARACTER_SUCCESS;
	Send((unsigned char*)&slone, sizeof(slone));

	sCU_SERVER_CHANNEL_INFO cinfo;
	memset(&cinfo, 0, sizeof(sCU_SERVER_CHANNEL_INFO));
	cinfo.OpCode = CU_SERVER_CHANNEL_INFO;
	cinfo.Count = 1;
	cinfo.channelInfo[0].ChannelId = 0;
	cinfo.channelInfo[0].serverId = LastServerID;
	cinfo.channelInfo[0].IsVisible = true;
	cinfo.channelInfo[0].Load = 0;
	cinfo.channelInfo[0].MaxLoad = 100;
	cinfo.channelInfo[0].ServerStatus = SERVERSTATUS_UP;
	Send((unsigned char*)&cinfo, sizeof(cinfo));
}

void CharClient::SendCharLoadResult(sUC_CHARACTER_LOAD_REQ* data)
{
	Logger::Log("-- CHAR LOAD RESULT --\n");
	sCU_CHARACTER_INFO cinfo;
	memset(&cinfo, 0, sizeof(sCU_CHARACTER_INFO));
	cinfo.Count = 1;
	cinfo.OpCode = CU_CHARACTER_INFO;
	cinfo.CharData[0].charId = 1000;
	cinfo.CharData[0].Class = 0;
	cinfo.CharData[0].Face = 3;
	cinfo.CharData[0].Gender = 1;
	cinfo.CharData[0].Hair = 4;
	cinfo.CharData[0].HairColor = 2;
	cinfo.CharData[0].IsAdult = true;
	cinfo.CharData[0].Level = 1;
	cinfo.CharData[0].NeedNameChange = false;
	cinfo.CharData[0].Race = 0;
	cinfo.CharData[0].SkinColor = 0;
	wcscpy_s(cinfo.CharData[0].Name, L"Asuna");
	Send((unsigned char*)&cinfo, sizeof(cinfo));

	sCU_CHARACTER_LOAD_RES clres;
	memset(&clres, 0, sizeof(sCU_CHARACTER_LOAD_RES));
	clres.OpCode = CU_CHARACTER_LOAD_RES;
	clres.ResultCode = CHARACTER_SUCCESS;
	Send((unsigned char*)&clres, sizeof(clres));
}

void CharClient::SendCharExitRes(sUC_CHARACTER_EXIT_REQ* data)
{
	Logger::Log("-- CHARSERVER EXIT RES --\n");
	sCU_CHARACTER_EXIT_RES cexit;
	memset(&cexit, 0, sizeof(cexit));
	cexit.OpCode = CU_CHARACTER_EXIT_RES;
	cexit.ResultCode = CHARACTER_SUCCESS;
	Send((unsigned char*)&cexit, sizeof(cexit));
}