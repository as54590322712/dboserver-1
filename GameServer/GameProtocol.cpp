#include "GameNetwork.h"
#include "GameProtocol.h"

void GameClient::SendGameEnterRes(sUG_GAME_ENTER_REQ* data)
{
	this->AccountID = data->accountId;
	this->CurrCharID = data->charId;
	this->CurrServerID = pServer->ServerID;
	memcpy(this->AuthKey, data->AuthKey, MAX_AUTHKEY_SIZE);

	sGU_GAME_ENTER_RES geRes;
	memset(&geRes, 0, sizeof(geRes));
	geRes.OpCode = GU_GAME_ENTER_RES;
	memcpy(geRes.CommunityServerIP, pServer->ServerConfig->GetStr("ChatServer", "IP"), MAX_SRVADDR_SIZE);
	geRes.CommunityServerPort = pServer->ServerConfig->GetInt("ChatServer", "Port");
	geRes.EnterTime = time(NULL);
	geRes.ResultCode = GAME_SUCCESS;
	Send((unsigned char*)&geRes, sizeof(geRes));
}

void GameClient::SendCharInfoEnd()
{
	sGU_AVATAR_INFO_END iEnd;
	memset(&iEnd, 0, sizeof(iEnd));
	iEnd.OpCode = GU_AVATAR_INFO_END;
	Send((unsigned char*)&iEnd, sizeof(iEnd));
}

void GameClient::SendCharInfo()
{
	sGU_AVATAR_CHAR_INFO charInfo;
	memset(&charInfo, 0, sizeof(charInfo));
	charInfo.OpCode = GU_AVATAR_CHAR_INFO;
	LoadCharacterData();
	charInfo.PcProfile = PcProfile;
	charInfo.CharState = CharState;
	charInfo.CharStateSize = sizeof(CharState);
	Send((unsigned char*)&charInfo, sizeof(charInfo));
}

void GameClient::SendCharWorldInfo()
{
	sGU_AVATAR_WORLD_INFO wInfo;
	memset(&wInfo, 0, sizeof(wInfo));
	wInfo.OpCode = GU_AVATAR_WORLD_INFO;
	LoadWorldInfoData();
	wInfo.worldInfo = worldInfo;
	wInfo.CurDir = CharState.CharStateBase.CurDir;
	wInfo.CurLoc = CharState.CharStateBase.CurLoc;
	Send((unsigned char*)&wInfo, sizeof(wInfo));
}

void GameClient::SendCharWorldInfoEnd()
{
	sGU_ENTER_WORLD_COMPLETE entWorld;
	memset(&entWorld, 0, sizeof(entWorld));
	entWorld.OpCode = GU_ENTER_WORLD_COMPLETE;
	Send((unsigned char*)&entWorld, sizeof(entWorld));
}

void GameClient::SendCharMove(sUG_CHAR_MOVE* data)
{
	sGU_CHAR_MOVE mData;
	memset(&mData, 0, sizeof(mData));
	mData.OpCode = GU_CHAR_MOVE;
	mData.CurDir.x = data->CurDir.x;
	mData.CurDir.z = data->CurDir.z;
	mData.CurLoc.x = data->CurLoc.x;
	mData.CurLoc.y = data->CurLoc.y;
	mData.CurLoc.z = data->CurLoc.z;
}