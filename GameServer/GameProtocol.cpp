#include "GameNetwork.h"
#include "GameProtocol.h"

void GameClient::SendGameEnterRes(sUG_GAME_ENTER_REQ* data)
{
	this->AccountID = data->accountId;
	this->CurrCharID = data->charId;
	this->CurrServerID = pServer->ServerID;

	sGU_GAME_ENTER_RES geRes;
	memset(&geRes, 0, sizeof(geRes));
	geRes.OpCode = GU_GAME_ENTER_RES;
	memcpy(geRes.CommunityServerIP, pServer->ServerConfig->GetStr("ChatServer", "IP"), MAX_SRVADDR_SIZE);
	geRes.CommunityServerPort = pServer->ServerConfig->GetInt("ChatServer", "Port");
	geRes.EnterTime = time(NULL);
	geRes.ResultCode = GAME_SUCCESS;
	Send((unsigned char*)&geRes, sizeof(geRes));

	// send char info
	sGU_AVATAR_CHAR_INFO charInfo;
	memset(&charInfo, 0, sizeof(charInfo));
	charInfo.OpCode = GU_AVATAR_CHAR_INFO;
	LoadSendCharacterData(&charInfo);
	Send((unsigned char*)&charInfo, sizeof(charInfo));

	sGU_AVATAR_WORLD_INFO wInfo;
	memset(&wInfo, 0, sizeof(wInfo));

	wInfo.OpCode = GU_AVATAR_WORLD_INFO;
	wInfo.worldInfo.tblidx = 1;
	wInfo.worldInfo.worldID = 1;
	wInfo.worldInfo.TriggerObjectOffset = 100000;

	wInfo.worldInfo.RuleInfo.RuleType = GAMERULE_NORMAL;

	wInfo.CurLoc.x = charInfo.CharState.CharStateBase.CurLoc.x + (float)(rand() % 5);
	wInfo.CurLoc.y = charInfo.CharState.CharStateBase.CurLoc.y + (float)(rand() % 5);
	wInfo.CurLoc.z = charInfo.CharState.CharStateBase.CurLoc.z + (float)(rand() % 5);
	wInfo.CurDir.x = charInfo.CharState.CharStateBase.CurDir.x;
	wInfo.CurDir.y = charInfo.CharState.CharStateBase.CurDir.y;
	wInfo.CurDir.z = charInfo.CharState.CharStateBase.CurDir.z;
	Send((unsigned char*)&wInfo, sizeof(wInfo));

	sGU_AVATAR_INFO_END iEnd;
	memset(&iEnd, 0, sizeof(iEnd));
	iEnd.OpCode = GU_AVATAR_INFO_END;
	Send((unsigned char*)&iEnd, sizeof(iEnd));

	sGU_ENTER_WORLD_COMPLETE entWorld;
	memset(&entWorld, 0, sizeof(entWorld));
	entWorld.OpCode = GU_ENTER_WORLD_COMPLETE;
	Send((unsigned char*)&entWorld, sizeof(entWorld));
}