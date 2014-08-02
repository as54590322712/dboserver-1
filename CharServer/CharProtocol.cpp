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
	char snode[20];
	sprintf_s(snode, "Server%d", LastServerID + 1);
	sCU_SERVER_FARM_INFO sinfo;
	memset(&sinfo, 0, sizeof(sCU_SERVER_FARM_INFO));
	sinfo.OpCode = CU_SERVER_FARM_INFO;
	sinfo.serverInfo.serverId = LastServerID;
	memcpy(sinfo.serverInfo.ServerName, charToWChar(pServer->ServerConfig->GetChildStr("ServerList", snode, "Name")), MAX_SERVERNAME_SIZE);
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
	cinfo.Count = GetDBAccCharListData(&cinfo);
	cinfo.OpCode = CU_CHARACTER_INFO;
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

void CharClient::SendCharCreateRes(sUC_CHARACTER_ADD_REQ* data)
{
	sCU_CHARACTER_ADD_RES Res;
	memset(&Res, 0, sizeof(Res));
	Res.OpCode = CU_CHARACTER_ADD_RES;
	Res.ResultCode = CheckUsedName(data->CharName);
	if (Res.ResultCode == CHARACTER_SUCCESS)
	{
		memcpy(Res.CharData.Name, data->CharName, MAX_CHARNAME_SIZE);
		Res.CharData.charId = rand();
		Res.CharData.Class = data->Class;
		Res.CharData.Face = data->Face;
		Res.CharData.Gender = data->Gender;
		Res.CharData.Hair = data->Hair;
		Res.CharData.HairColor = data->HairColor;
		Res.CharData.Race = data->Race;
		Res.CharData.SkinColor = data->SkinColor;
		Res.CharData.Level = 1;
		Res.CharData.MapInfoId = 1;
		Res.CharData.TutorialFlag = false;
		Res.CharData.Money = 10000;
		Res.CharData.MoneyBank = 100000;
		Res.CharData.IsAdult = false;
		Res.CharData.NeedNameChange = false;
		DBInsertCharData(Res.CharData);
	}
	Send((unsigned char*)&Res, sizeof(Res));
}