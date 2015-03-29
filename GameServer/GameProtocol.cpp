#include "GameNetwork.h"
#include "GameProtocol.h"

bool GameClient::PacketControl(Packet* pPacket)
{
	LPPACKETDATA data = (LPPACKETDATA)pPacket->GetPacketData();

	switch (data->wOpCode)
	{
	case UG_PING: break;
	case UG_GAME_ENTER_REQ: {
		SendGameEnterRes((sUG_GAME_ENTER_REQ*)data);
		SendCharInfo();
		SendCharItemInfo();
		SendCharSkillInfo();
		SendCharBuffsInfo();
		// HTB Info
		// Quest List
		SendCharQuickSlotInfo();
		SendCharInfoEnd();
		SendAvatarWarFogInfo();
	} break;
	case UG_GAME_LEAVE_REQ: SendGameLeaveRes(); break;
	case UG_AUTH_KEY_FOR_COMMUNITY_SERVER_REQ: SendAuthkeyCommSrvRes(); break;
	case UG_ENTER_WORLD: {
		SendCharWorldInfo();
		// TO DO WORLD SPAWNS
		SendCharWorldInfoEnd();
	} break;
	case UG_SERVER_COMMAND: CheckCommand((sUG_SERVER_COMMAND*)data); break;
	case UG_CHAR_READY_TO_SPAWN: SendCharReadySpawnReq(); break;
	case UG_CHAR_READY: SendCharReadyRes((sUG_CHAR_READY*)data); break;
	case UG_CHAR_MOVE: SendCharMove((sUG_CHAR_MOVE*)data); break;
	case UG_CHAR_DEST_MOVE: SendCharDestMove((sUG_CHAR_DEST_MOVE*)data); break;
	case UG_CHAR_CHANGE_HEADING: break;
	case UG_CHAR_MOVE_SYNC: SendCharMoveSync((sUG_CHAR_MOVE_SYNC*)data); break;
	//case UG_CHAR_EXIT_REQ: Logger::Log("---- UG_CHAR_EXIT_REQ!!!\n"); break;
	//case UG_GAME_EXIT_REQ: Logger::Log("---- UG_GAME_EXIT_REQ!!!\n"); break;
	case 1: { sNTLPACKETHEADER reply(1); Send(&reply, sizeof(reply)); } break;
	default:
		Logger::Log("Received Opcode: %s\n", NtlGetPacketName_UG(data->wOpCode));
		return false;
		break;
	}
	return true;
}

void GameClient::SendGameLeaveRes()
{
	Logger::Log("Client[%u] exist game\n", this);
	sGU_GAME_LEAVE_RES glRes;
	memset(&glRes, 0, sizeof(glRes));
	glRes.wOpCode = GU_GAME_LEAVE_RES;
	glRes.wResultCode = GAME_SUCCESS;
	Send(&glRes, sizeof(glRes));

	pServer->RemoveClient(this);
	pServer->GetObjectManager()->RemoveObject(GetCharSerialID(), OBJTYPE_PC);

	sGU_OBJECT_DESTROY obDes;
	memset(&obDes, 0, sizeof(obDes));
	obDes.wOpCode = GU_OBJECT_DESTROY;
	obDes.handle = GetCharSerialID();
	pServer->SendOthers(&obDes, sizeof(obDes), this);
}

void GameClient::SendAuthkeyCommSrvRes()
{
	sGU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES auRes;
	memset(&auRes, 0, sizeof(auRes));
	auRes.wOpCode = GU_AUTH_KEY_FOR_COMMUNITY_SERVER_RES;
	memcpy(auRes.abyAuthKey, AuthKey, NTL_MAX_SIZE_AUTH_KEY);
	auRes.wResultCode = GAME_SUCCESS;
	Send(&auRes, sizeof(auRes));
}

void GameClient::SendAvatarWarFogInfo()
{
	sGU_WAR_FOG_INFO wfInfo;
	memset(&wfInfo, 0, sizeof(wfInfo));
	wfInfo.wOpCode = GU_WAR_FOG_INFO;
	Send(&wfInfo, sizeof(wfInfo));
}

void GameClient::SendCharBuffsInfo()
{
	sGU_AVATAR_BUFF_INFO bInfo;
	memset(&bInfo, 0, sizeof(bInfo));
	bInfo.wOpCode = GU_AVATAR_BUFF_INFO;
	bInfo.byBuffCount = 0;
	Send(&bInfo, sizeof(bInfo));
}

void GameClient::SpawnTesteMob(unsigned int id)
{
	sGU_OBJECT_CREATE sPacket;
	memset(&sPacket, 0, sizeof(sGU_OBJECT_CREATE));
	sPacket.wOpCode = GU_OBJECT_CREATE;
	sPacket.handle = pServer->AcquireCharSerialID();
	sPacket.sObjectInfo.objType = OBJTYPE_MOB;
	sPacket.sObjectInfo.mobBrief.tblidx = id;
	sPacket.sObjectInfo.mobBrief.wCurLP = 100;
	sPacket.sObjectInfo.mobBrief.wMaxLP = 100;
	sPacket.sObjectInfo.mobBrief.fLastWalkingSpeed = 3.0f;
	sPacket.sObjectInfo.mobBrief.fLastRunningSpeed = 7.0f;

	sPacket.sObjectInfo.mobState.sCharStateBase.byStateID = CHARSTATE_SPAWNING;
	sPacket.sObjectInfo.mobState.sCharStateBase.bFightMode = FALSE;

	sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.x = CharState.sCharStateBase.vCurLoc.x + (float)(rand() % 5);
	sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.y = CharState.sCharStateBase.vCurLoc.y;
	sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.z = CharState.sCharStateBase.vCurLoc.z + (float)(rand() % 5);

	sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.x = 0.0f;
	sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.y = 0.0f;
	sPacket.sObjectInfo.mobState.sCharStateBase.vCurDir.z = 1.0f;

	if (sPacket.sObjectInfo.mobState.sCharStateBase.byStateID == CHARSTATE_DESTMOVE)
	{
		sPacket.sObjectInfo.mobState.sCharStateDetail.sCharStateDestMove.byDestLocCount = 1;
		sPacket.sObjectInfo.mobState.sCharStateDetail.sCharStateDestMove.avDestLoc[0].x = sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.x + 100;
		sPacket.sObjectInfo.mobState.sCharStateDetail.sCharStateDestMove.avDestLoc[0].y = sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.y;
		sPacket.sObjectInfo.mobState.sCharStateDetail.sCharStateDestMove.avDestLoc[0].z = sPacket.sObjectInfo.mobState.sCharStateBase.vCurLoc.z;
	}
	if (false == pServer->GetObjectManager()->FindObject(sPacket.handle, sPacket.sObjectInfo.objType))
		pServer->GetObjectManager()->AddObject(sPacket);
	pServer->SpawnObjects();
	//pServer->SendAll(&sPacket, sizeof(sPacket));
}

void GameClient::CheckCommand(sUG_SERVER_COMMAND* pData)
{
	GameString command(pData->awchCommand);

	Logger::Log("Typed command: %s\n", command.c_str());
	char seps[] = " ,";
	char* next = NULL;
	char* tok = strtok_s(_strdup(command.c_str()), seps, &next);

	if (tok != NULL && this->isGameMaster)
	{
		if (strcmp(tok, "@teste") == 0)
		{
			// TEST COMMANDS
			sGU_OBJECT_CREATE sPacket;
			memset(&sPacket, 0, sizeof(sGU_OBJECT_CREATE));
			sPacket.wOpCode = GU_OBJECT_CREATE;
			sPacket.handle = pServer->AcquireCharSerialID();
			sPacket.sObjectInfo.objType = OBJTYPE_PC;
			sPacket.sObjectInfo.pcBrief.byLevel = 1;
			sPacket.sObjectInfo.pcBrief.tblidx = 1;
			wcscpy_s(sPacket.sObjectInfo.pcBrief.awchName, NTL_MAX_SIZE_CHAR_NAME_UNICODE, L"Dummy");
			sPacket.sObjectInfo.pcBrief.wCurLP = 100;
			sPacket.sObjectInfo.pcBrief.wMaxLP = 100;
			sPacket.sObjectInfo.pcBrief.fSpeed = 7.0f;
			sPacket.sObjectInfo.pcBrief.sPcShape.byFace = 1;
			sPacket.sObjectInfo.pcBrief.sPcShape.byHair = 1;
			sPacket.sObjectInfo.pcBrief.sPcShape.byHairColor = 1;
			sPacket.sObjectInfo.pcBrief.sPcShape.bySkinColor = 1;

			sPacket.sObjectInfo.pcState.sCharStateBase.vCurLoc.x = CharState.sCharStateBase.vCurLoc.x + (float)(rand() % 5);
			sPacket.sObjectInfo.pcState.sCharStateBase.vCurLoc.y = CharState.sCharStateBase.vCurLoc.y;
			sPacket.sObjectInfo.pcState.sCharStateBase.vCurLoc.z = CharState.sCharStateBase.vCurLoc.z + (float)(rand() % 5);

			sPacket.sObjectInfo.pcState.sCharStateBase.vCurDir.x = 0.0f;
			sPacket.sObjectInfo.pcState.sCharStateBase.vCurDir.y = 0.0f;
			sPacket.sObjectInfo.pcState.sCharStateBase.vCurDir.z = 1.0f;

			for (int i = 0; i < EQUIP_SLOT_TYPE_COUNT; i++)
			{
				memset(&sPacket.sObjectInfo.pcBrief.sItemBrief[i], 0xFF, sizeof(sITEM_BRIEF));
			}

			if (false == pServer->GetObjectManager()->FindObject(sPacket.handle, sPacket.sObjectInfo.objType))
				pServer->GetObjectManager()->AddObject(sPacket);
			pServer->SpawnObjects();
		}
		if (strcmp(tok, "@spawnmob") == 0)
		{
			tok = strtok_s(NULL, seps, &next);
			if (tok != NULL) SpawnTesteMob(atoi(tok));
		}
	}
}

void GameClient::SendCharReadyRes(sUG_CHAR_READY* pData)
{
	Send(&pData, sizeof(pData));
}

void GameClient::SendCharReadySpawnReq()
{
	sGU_OBJECT_CREATE charSpawn = GetCharSpawnData();
	charSpawn.handle = CharSerialID;
	//pServer->SendOthers(&charSpawn, sizeof(charSpawn), this);
	//pServer->RecvOthers(GU_OBJECT_CREATE, this);
	if (pServer->AddClient(this))
	{
		pServer->GetObjectManager()->AddObject(charSpawn);
		pServer->SpawnObjects();
	}
}

void GameClient::SendGameEnterRes(sUG_GAME_ENTER_REQ* data)
{
	this->CharSerialID = pServer->AcquireCharSerialID();
	this->AccountID = data->accountId;
	this->CurrCharID = data->charId;
	this->CurrServerID = pServer->ServerID;
	this->TutorialMode = data->bTutorialMode;
	memcpy(this->AuthKey, data->abyAuthKey, NTL_MAX_SIZE_AUTH_KEY);

	Logger::Log("Client[%d] entering game (%d|%d) handle[%d]\n", this, AccountID, CurrCharID, CharSerialID);

	sGU_GAME_ENTER_RES geRes;
	memset(&geRes, 0, sizeof(geRes));
	geRes.wOpCode = GU_GAME_ENTER_RES;
	memcpy(geRes.achCommunityServerIP, pServer->ServerCfg->GetStr("ChatServer", "IP"), NTL_MAX_LENGTH_OF_IP);
	geRes.wCommunityServerPort = pServer->ServerCfg->GetInt("ChatServer", "Port");
	geRes.timeDBOEnter = time(NULL);
	geRes.wResultCode = GAME_SUCCESS;
	Send((unsigned char*)&geRes, sizeof(geRes));
}

void GameClient::SendCharInfoEnd()
{
	sGU_AVATAR_INFO_END iEnd;
	memset(&iEnd, 0, sizeof(iEnd));
	iEnd.wOpCode = GU_AVATAR_INFO_END;
	Send((unsigned char*)&iEnd, sizeof(iEnd));
}

void GameClient::SendCharInfo()
{
	sGU_AVATAR_CHAR_INFO charInfo;
	memset(&charInfo, 0, sizeof(charInfo));
	charInfo.wOpCode = GU_AVATAR_CHAR_INFO;
	LoadCharacterData();
	charInfo.handle = this->CharSerialID;
	memcpy(&charInfo.sPcProfile, &PcProfile, sizeof(PcProfile));
	memcpy(&charInfo.sCharState, &CharState, sizeof(CharState));
	charInfo.wCharStateSize = sizeof(CharState);
	Send((unsigned char*)&charInfo, sizeof(charInfo));
}

void GameClient::SendCharWorldInfo()
{
	sGU_AVATAR_WORLD_INFO wInfo;
	memset(&wInfo, 0, sizeof(wInfo));
	wInfo.wOpCode = GU_AVATAR_WORLD_INFO;
	LoadWorldInfoData();
	memcpy(&wInfo.worldInfo, &worldInfo, sizeof(worldInfo));
	wInfo.vCurDir = CharState.sCharStateBase.vCurDir;
	wInfo.vCurLoc = CharState.sCharStateBase.vCurLoc;
	wInfo.vCurLoc.x += (float)(rand() % 5);
	wInfo.vCurLoc.y += (float)(rand() % 5);
	wInfo.vCurLoc.z += (float)(rand() % 5);
	Send((unsigned char*)&wInfo, sizeof(wInfo));
}

void GameClient::SendCharWorldInfoEnd()
{
	sGU_ENTER_WORLD_COMPLETE entWorld;
	memset(&entWorld, 0, sizeof(entWorld));
	entWorld.wOpCode = GU_ENTER_WORLD_COMPLETE;
	Send((unsigned char*)&entWorld, sizeof(entWorld));
}

void GameClient::SendCharMove(sUG_CHAR_MOVE* data)
{
	UpdatePositions(data->vCurDir, data->vCurLoc);
	sGU_CHAR_MOVE mData;
	memset(&mData, 0, sizeof(mData));
	mData.wOpCode = GU_CHAR_MOVE;
	mData.vCurDir.x = data->vCurDir.x;
	mData.vCurDir.y = 0.0f;
	mData.vCurDir.z = data->vCurDir.z;
	mData.vCurLoc.x = data->vCurLoc.x;
	mData.vCurLoc.y = data->vCurLoc.y;
	mData.vCurLoc.z = data->vCurLoc.z;
	mData.handle = CharSerialID;
	mData.byMoveDirection = data->byMoveDirection;
	pServer->SendOthers(&mData, sizeof(mData), this);
}

void GameClient::SendCharDestMove(sUG_CHAR_DEST_MOVE* pData)
{
	sGU_CHAR_DEST_MOVE dMove;
	memset(&dMove, 0, sizeof(dMove));
	dMove.wOpCode = GU_CHAR_DEST_MOVE;
	dMove.vCurLoc = pData->vCurLoc;
	dMove.handle = GetCharSerialID();
	dMove.byDestLocCount = 1;
	dMove.avDestLoc[0] = pData->vDestLoc;
	dMove.dwTimeStamp = pData->dwTimeStamp;
	dMove.byMoveFlag = 13;
	pServer->SendOthers(&dMove, sizeof(dMove), this);
}

void GameClient::SendCharMoveSync(sUG_CHAR_MOVE_SYNC* pData)
{
	UpdatePositions(pData->vCurDir, pData->vCurLoc);
	sGU_CHAR_MOVE_SYNC cmSync;
	memset(&cmSync, 0, sizeof(cmSync));
	cmSync.wOpCode = GU_CHAR_MOVE_SYNC;
	cmSync.handle = GetCharSerialID();
	cmSync.vCurDir = pData->vCurDir;
	cmSync.vCurLoc = pData->vCurLoc;
	cmSync.dwTimeStamp = pData->dwTimeStamp;
	pServer->SendOthers(&cmSync, sizeof(cmSync), this);
}

void GameClient::SendCharItemInfo()
{
	sGU_AVATAR_ITEM_INFO iInfo;
	memset(&iInfo, 0, sizeof(iInfo));
	iInfo.wOpCode = GU_AVATAR_ITEM_INFO;
	iInfo.byItemCount = LoadItemData();
	memcpy(iInfo.aItemProfile, ItemProfile, sizeof(ItemProfile));
	int psize = 3;
	psize += sizeof(sITEM_PROFILE) * iInfo.byItemCount;
	Send(&iInfo, psize);
}

void GameClient::SendCharSkillInfo()
{
	sGU_AVATAR_SKILL_INFO sInfo;
	memset(&sInfo, 0, sizeof(sInfo));
	sInfo.wOpCode = GU_AVATAR_SKILL_INFO;
	sInfo.bySkillCount = LoadSkillData();
	memcpy(sInfo.aSkillInfo, SkillInfo, sizeof(SkillInfo));
	int psize = 3;
	psize += sizeof(sSKILL_INFO) * sInfo.bySkillCount;
	Send(&sInfo, psize);
}

void GameClient::SendCharQuickSlotInfo()
{
	sGU_QUICK_SLOT_INFO qsInfo;
	memset(&qsInfo, 0, sizeof(qsInfo));
	qsInfo.wOpCode = GU_QUICK_SLOT_INFO;
	qsInfo.byQuickSlotCount = LoadQuickslotData();
	memcpy(qsInfo.asQuickSlotData, QuickSlotData, sizeof(QuickSlotData));
	int psize = 3;
	psize += sizeof(sQUICK_SLOT_PROFILE) * qsInfo.byQuickSlotCount;
	Send(&qsInfo, psize);
}