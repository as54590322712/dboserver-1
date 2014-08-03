#include "CharNetwork.h"
#include "CharProtocol.h"

void CharClient::SendLoginResult(sUC_LOGIN_REQ* data)
{
	CurrServerID = data->serverID;
	AccountID = data->accountId;
	memcpy(AuthKey, data->AuthKey, MAX_AUTHKEY_SIZE);

	sCU_LOGIN_RES lRes;
	memset(&lRes, 0, sizeof(sCU_LOGIN_RES));
	lRes.lastServerId = CurrServerID;
	lRes.OpCode = CU_LOGIN_RES;
	lRes.ResultCode = CHARACTER_SUCCESS;
	lRes.RaceAllowedFlag = GetDBAllowedRaces(); // Opened Races at Character Creation (0 = none, 255 = all)
	Send((unsigned char*)&lRes, sizeof(lRes));
}

void CharClient::SendServerlist()
{
	for (int i = 0; i < pServer->ServerConfig->GetInt("ServerCount"); i++)
	{
		char snode[20];
		sprintf_s(snode, "Server%d", i + 1);
		sCU_SERVER_FARM_INFO sinfo;
		memset(&sinfo, 0, sizeof(sCU_SERVER_FARM_INFO));
		sinfo.OpCode = CU_SERVER_FARM_INFO;
		sinfo.serverInfo.serverId = i;
		memcpy(sinfo.serverInfo.ServerName, charToWChar(pServer->ServerConfig->GetStr(snode, "Name")), MAX_SERVERNAME_SIZE);
		sinfo.serverInfo.ServerStatus = SERVERSTATUS_UP;
		sinfo.serverInfo.Load = 0;
		sinfo.serverInfo.MaxLoad = pServer->ServerConfig->GetInt(snode, "MaxLoad");
		Send((unsigned char*)&sinfo, sizeof(sinfo));

		sCU_SERVER_CHANNEL_INFO cinfo;
		memset(&cinfo, 0, sizeof(sCU_SERVER_CHANNEL_INFO));
		cinfo.OpCode = CU_SERVER_CHANNEL_INFO;
		cinfo.Count = pServer->ServerConfig->GetInt(snode, "Count");
		for (int x = 0; x < cinfo.Count; x++)
		{
			char cnode[20];
			sprintf_s(cnode, "Channel%d", x + 1);
			cinfo.channelInfo[x].ChannelId = x;
			cinfo.channelInfo[x].serverId = i;
			cinfo.channelInfo[x].IsVisible = true;
			cinfo.channelInfo[x].Load = x;
			cinfo.channelInfo[x].MaxLoad = pServer->ServerConfig->GetChildInt(snode, cnode, "MaxLoad");
			cinfo.channelInfo[x].ServerStatus = SERVERSTATUS_UP;
		}
		Send((unsigned char*)&cinfo, sizeof(cinfo));
	}

	sCU_CHARACTER_SERVERLIST_RES slres;
	memset(&slres, 0, sizeof(slres));
	slres.OpCode = CU_CHARACTER_SERVERLIST_RES;
	slres.ResultCode = CHARACTER_SUCCESS;
	Send((unsigned char*)&slres, sizeof(slres));
}

void CharClient::SendServerlistOne()
{
	for (int i = 0; i < pServer->ServerConfig->GetInt("ServerCount"); i++)
	{
		char snode[20];
		sprintf_s(snode, "Server%d", i + 1);
		sCU_SERVER_FARM_INFO sinfo;
		memset(&sinfo, 0, sizeof(sCU_SERVER_FARM_INFO));
		sinfo.OpCode = CU_SERVER_FARM_INFO;
		sinfo.serverInfo.serverId = i;
		memcpy(sinfo.serverInfo.ServerName, charToWChar(pServer->ServerConfig->GetStr(snode, "Name")), MAX_SERVERNAME_SIZE);
		sinfo.serverInfo.ServerStatus = SERVERSTATUS_UP;
		sinfo.serverInfo.Load = 0;
		sinfo.serverInfo.MaxLoad = pServer->ServerConfig->GetInt(snode, "MaxLoad");
		Send((unsigned char*)&sinfo, sizeof(sinfo));

		sCU_SERVER_CHANNEL_INFO cinfo;
		memset(&cinfo, 0, sizeof(sCU_SERVER_CHANNEL_INFO));
		cinfo.OpCode = CU_SERVER_CHANNEL_INFO;
		cinfo.Count = pServer->ServerConfig->GetInt(snode, "Count");
		for (int x = 0; x < cinfo.Count; x++)
		{
			char cnode[20];
			sprintf_s(cnode, "Channel%d", x + 1);
			cinfo.channelInfo[x].ChannelId = x;
			cinfo.channelInfo[x].serverId = i;
			cinfo.channelInfo[x].IsVisible = true;
			cinfo.channelInfo[x].Load = x;
			cinfo.channelInfo[x].MaxLoad = pServer->ServerConfig->GetChildInt(snode, cnode, "MaxLoad");
			cinfo.channelInfo[x].ServerStatus = SERVERSTATUS_UP;
		}
		Send((unsigned char*)&cinfo, sizeof(cinfo));
	}

	sCU_CHARACTER_SERVERLIST_ONE_RES slone;
	memset(&slone, 0, sizeof(sCU_CHARACTER_SERVERLIST_ONE_RES));
	slone.OpCode = CU_CHARACTER_SERVERLIST_ONE_RES;
	slone.ResultCode = CHARACTER_SUCCESS;
	Send((unsigned char*)&slone, sizeof(slone));
}

void CharClient::SendCharLoadResult(sUC_CHARACTER_LOAD_REQ* data)
{
	CurrServerID = data->serverId;
	AccountID = data->accountId;
	DBUpdateLastServer();

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
	if (data->IsGameMove) goGameServer = true;
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

void CharClient::SendCharDelRes(sUC_CHARACTER_DEL_REQ* data)
{
	sCU_CHARACTER_DEL_RES Res;
	memset(&Res, 0, sizeof(Res));
	Res.OpCode = CU_CHARACTER_DEL_RES;
	Res.charId = data->charId;
	if (pServer->ServerDB->ExecuteQuery("UPDATE `character` SET `ToDelete` = '1' WHERE `ID` = '%d';", Res.charId))
		Res.ResultCode = CHARACTER_SUCCESS;
	else
		Res.ResultCode = CHARACTER_DELETE_CHAR_FAIL;
	Send((unsigned char*)&Res, sizeof(Res));
}

void CharClient::SendCharDelCancelRes(sUC_CHARACTER_DEL_CANCEL_REQ* data)
{
	sCU_CHARACTER_DEL_CANCEL_RES Res;
	memset(&Res, 0, sizeof(Res));
	Res.OpCode = CU_CHARACTER_DEL_CANCEL_RES;
	Res.charId = data->charId;
	if (pServer->ServerDB->ExecuteQuery("UPDATE `character` SET `ToDelete` = '0' WHERE `ID` = '%d';", Res.charId))
		Res.ResultCode = CHARACTER_SUCCESS;
	else
		Res.ResultCode = CHARACTER_DB_QUERY_FAIL;
	Send((unsigned char*)&Res, sizeof(Res));
}