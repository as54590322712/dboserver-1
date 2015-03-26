#include "CharNetwork.h"
#include "CharProtocol.h"

bool CharClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();
	switch (data->wOpCode)
	{
	case UC_LOGIN_REQ: SendLoginResult((sUC_LOGIN_REQ*)data); break;
	case UC_CHARACTER_SERVERLIST_REQ: SendServerlist(false); break;
	case UC_CHARACTER_SERVERLIST_ONE_REQ: SendServerlist(true); break;
	case UC_CHARACTER_ADD_REQ: SendCharCreateRes((sUC_CHARACTER_ADD_REQ*)data); break;
	case UC_CHARACTER_DEL_REQ: SendCharDelRes((sUC_CHARACTER_DEL_REQ*)data); break;
	case UC_CHARACTER_SELECT_REQ: SendCharSelectRes((sUC_CHARACTER_SELECT_REQ*)data); break;
	case UC_CHARACTER_EXIT_REQ: SendCharExitRes((sUC_CHARACTER_EXIT_REQ*)data); break;
	case UC_CHARACTER_LOAD_REQ: SendCharLoadResult((sUC_CHARACTER_LOAD_REQ*)data); break;
	case UC_CHARACTER_DEL_CANCEL_REQ: SendCharDelCancelRes((sUC_CHARACTER_DEL_CANCEL_REQ*)data); break;
	case UC_CONNECT_WAIT_CHECK_REQ: SendCharConnWaitCheckRes((sUC_CONNECT_WAIT_CHECK_REQ*)data); break;
	case UC_CONNECT_WAIT_CANCEL_REQ: SendCancelWaitReq((sUC_CONNECT_WAIT_CANCEL_REQ*)data); break;
	case UC_CHARACTER_RENAME_REQ: SendCharRenameRes((sUC_CHARACTER_RENAME_REQ*)data); break;
	case 1: { sPACKETHEADER reply(1); Send(&reply, sizeof(reply)); } break;
	default:
		Logger::Log("Received Opcode: %d\n", data->wOpCode);
		return false;
		break;
	}
	return true;
}

void CharClient::SendLoginResult(sUC_LOGIN_REQ* data)
{
	CurrServerID = data->serverID;
	AccountID = data->accountId;
	memcpy(AuthKey, data->AuthKey, MAX_AUTHKEY_SIZE);

	Logger::Log("Client[%d] entering char server (%d)\n", this, AccountID);

	sCU_LOGIN_RES lRes;
	memset(&lRes, 0, sizeof(sCU_LOGIN_RES));
	lRes.lastServerId = CurrServerID;
	lRes.OpCode = CU_LOGIN_RES;
	lRes.ResultCode = CHARACTER_SUCCESS;
	lRes.RaceAllowedFlag = GetDBAllowedRaces();
	Send((unsigned char*)&lRes, sizeof(lRes));
}

void CharClient::SendServerlist(bool one)
{
	for (int i = 0; i < pServer->ServerCfg->GetInt("ServerCount"); i++)
	{
		char snode[20];
		sprintf_s(snode, "Server%d", i + 1);
		sCU_SERVER_FARM_INFO sinfo;
		memset(&sinfo, 0, sizeof(sCU_SERVER_FARM_INFO));
		sinfo.OpCode = CU_SERVER_FARM_INFO;
		sinfo.serverInfo.serverId = i;
		memcpy(sinfo.serverInfo.ServerName, charToWChar(pServer->ServerCfg->GetStr(snode, "Name")), MAX_SERVERNAME_SIZE);
		sinfo.serverInfo.ServerStatus = SERVERSTATUS_UP;
		sinfo.serverInfo.Load = 0;
		sinfo.serverInfo.MaxLoad = pServer->ServerCfg->GetInt(snode, "MaxLoad");
		Send((unsigned char*)&sinfo, sizeof(sinfo));
	}

	if (one)
	{
		sCU_CHARACTER_SERVERLIST_ONE_RES slone;
		memset(&slone, 0, sizeof(sCU_CHARACTER_SERVERLIST_ONE_RES));
		slone.OpCode = CU_CHARACTER_SERVERLIST_ONE_RES;
		slone.ResultCode = CHARACTER_SUCCESS;
		Send((unsigned char*)&slone, sizeof(slone));
	}
	else
	{
		sCU_CHARACTER_SERVERLIST_RES slres;
		memset(&slres, 0, sizeof(slres));
		slres.OpCode = CU_CHARACTER_SERVERLIST_RES;
		slres.ResultCode = CHARACTER_SUCCESS;
		Send((unsigned char*)&slres, sizeof(slres));
	}
}

void CharClient::SendCharLoadResult(sUC_CHARACTER_LOAD_REQ* data)
{
	CurrServerID = data->serverId;
	AccountID = data->accountId;
	DBUpdateLastServer();

	sCU_SERVER_CHANNEL_INFO cninfo;
	memset(&cninfo, 0, sizeof(sCU_SERVER_CHANNEL_INFO));
	cninfo.OpCode = CU_SERVER_CHANNEL_INFO;
	char snode[20];
	sprintf_s(snode, "Server%d", CurrServerID + 1);
	cninfo.Count = pServer->ServerCfg->GetInt(snode, "Count");
	for (int x = 0; x < cninfo.Count; x++)
	{
		char cnode[20];
		sprintf_s(cnode, "Channel%d", x + 1);
		cninfo.channelInfo[x].ChannelId = x;
		cninfo.channelInfo[x].serverId = CurrServerID;
		cninfo.channelInfo[x].IsVisible = true;
		cninfo.channelInfo[x].Load = 0;
		cninfo.channelInfo[x].MaxLoad = pServer->ServerCfg->GetChildInt(snode, cnode, "MaxLoad");
		cninfo.channelInfo[x].ServerStatus = SERVERSTATUS_UP;
	}
	Send((unsigned char*)&cninfo, sizeof(cninfo));

	sCU_CHARACTER_INFO cinfo;
	memset(&cinfo, 0, sizeof(sCU_CHARACTER_INFO));
	cinfo.Count = GetDBAccCharListData(&cinfo);
	cinfo.OpCode = CU_CHARACTER_INFO;
	Send((unsigned char*)&cinfo, sizeof(cinfo));

	Logger::Log("Loaded %d characters from client[%d] (%d)\n", cinfo.Count, this, AccountID);

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
		NewbieData nbdata = pServer->nbTblData->GetData(data->Race, data->Class);
		memcpy(Res.CharData.Name, data->CharName, MAX_CHARNAME_SIZE);
		Res.CharData.Class = data->Class;
		Res.CharData.Face = data->Face;
		Res.CharData.Gender = data->Gender;
		Res.CharData.Hair = data->Hair;
		Res.CharData.HairColor = data->HairColor;
		Res.CharData.Race = data->Race;
		Res.CharData.SkinColor = data->SkinColor;
		Res.CharData.Level = 1;
		Res.CharData.MapInfoId = nbdata.mapNameTblId;
		Res.CharData.worldId = nbdata.worldId;
		Res.CharData.worldTblidx = nbdata.worldId;
		Res.CharData.PositionX = nbdata.spawnLoc.x;
		Res.CharData.PositionY = nbdata.spawnLoc.y;
		Res.CharData.PositionZ = nbdata.spawnLoc.z;
		Res.CharData.TutorialFlag = false;
		Res.CharData.Money = 10000;
		Res.CharData.MoneyBank = 100000;
		Res.CharData.IsAdult = false;
		Res.CharData.NeedNameChange = false;
		for (int i = 0; i < NEWBIE_ITEM_MAX; i++)
		{
			int slot = nbdata.itemSlot[i];
			if ((slot >= 0) && (slot <= 12)) { 
				Res.CharData.Item[slot].tblidx = nbdata.itemId[i];
			}
		}
		Res.CharData.charId = DBInsertCharData(Res.CharData, nbdata);
	}
	Logger::Log("Client[%d] created character '%S' (%d)\n", this, Res.CharData.Name, Res.CharData.charId);
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

void CharClient::SendCharConnWaitCheckRes(sUC_CONNECT_WAIT_CHECK_REQ* data)
{
	CurrChannelID = data->ChannelId;

	sCU_CONNECT_WAIT_CHECK_RES checkRes;
	checkRes.OpCode = CU_CONNECT_WAIT_CHECK_RES;
	checkRes.ResultCode = GAME_SUCCESS;
	Send((unsigned char*)&checkRes, sizeof(checkRes));

	sCU_CONNECT_WAIT_COUNT_NFY connNfy;
	connNfy.OpCode = CU_CONNECT_WAIT_COUNT_NFY;
	connNfy.CountWaiting = 0;
	Send((unsigned char*)&connNfy, sizeof(connNfy));
}

void CharClient::SendCharSelectRes(sUC_CHARACTER_SELECT_REQ* data)
{
	CurrCharID = data->charId;
	CurrChannelID = data->ChannelId;

	sCU_CHARACTER_SELECT_RES selRes;
	memset(&selRes, 0, sizeof(selRes));
	selRes.OpCode = CU_CHARACTER_SELECT_RES;
	memcpy(selRes.AuthKey, AuthKey, MAX_AUTHKEY_SIZE);
	selRes.charId = CurrCharID;
	char snode[20], cnode[20];
	sprintf_s(snode, "Server%d", CurrServerID + 1);
	sprintf_s(cnode, "Channel%d", CurrChannelID + 1);
	memcpy(selRes.GameServerIP, pServer->ServerCfg->GetChildStr(snode, cnode, "IP"), MAX_SRVADDR_SIZE);
	selRes.GameServerPort = pServer->ServerCfg->GetChildInt(snode, cnode, "Port");
	selRes.ResultCode = CHARACTER_SUCCESS;
	Logger::Log("Client[%d] selected character (%d)\n", this, selRes.charId);
	Send((unsigned char*)&selRes, sizeof(selRes));
}

void CharClient::SendCharRenameRes(sUC_CHARACTER_RENAME_REQ* data)
{
	sCU_CHARACTER_RENAME_RES res;
	res.OpCode = CU_CHARACTER_RENAME_RES;
	res.charId = data->charId;
	res.ResultCode = DBChangeCharName(data->CharName, data->charId);
	Send(&res, sizeof(res));
}

void CharClient::SendCancelWaitReq(sUC_CONNECT_WAIT_CANCEL_REQ* data)
{
	sCU_CONNECT_WAIT_CANCEL_RES res;
	res.OpCode = CU_CONNECT_WAIT_CANCEL_RES;
	res.ResultCode = CHARACTER_SUCCESS;
	Send(&res, sizeof(res));
}