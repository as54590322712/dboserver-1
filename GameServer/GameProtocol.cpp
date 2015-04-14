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
		SendCharWorldInfoEnd();
	} break;
	case UG_SERVER_COMMAND: CheckCommand((sUG_SERVER_COMMAND*)data); break;
	case UG_CHAR_READY_FOR_COMMUNITY_SERVER_NFY: break;
	case UG_CHAR_READY_TO_SPAWN: SendCharReadySpawnReq(); break;
	case UG_CHAR_READY: SendCharReadyRes((sUG_CHAR_READY*)data); break;
	case UG_CHAR_MOVE: SendCharMove((sUG_CHAR_MOVE*)data); break;
	case UG_CHAR_DEST_MOVE: SendCharDestMove((sUG_CHAR_DEST_MOVE*)data); break;
	case UG_CHAR_CHANGE_HEADING: SendCharChangeHeading((sUG_CHAR_CHANGE_HEADING*)data); break;
	case UG_CHAR_MOVE_SYNC: SendCharMoveSync((sUG_CHAR_MOVE_SYNC*)data); break;
	case UG_CHAR_JUMP: SendCharJump((sUG_CHAR_JUMP*)data); break;
	case UG_CHAR_JUMP_END: SendCharJumpEnd(); break;
	case UG_CHAR_EXIT_REQ: SendCharExitRes(); break;
	case UG_GAME_EXIT_REQ: SendGameExitRes(); break;
	case UG_ITEM_MOVE_REQ: SendIemMoveRes((sUG_ITEM_MOVE_REQ*)data); break;
	case UG_SOCIAL_ACTION: SendSocialAction((sUG_SOCIAL_ACTION*)data); break;
	case UG_TS_CONFIRM_STEP_REQ: SendTSConfirmRes((sUG_TS_CONFIRM_STEP_REQ*)data); break;
	case UG_TUTORIAL_HINT_UPDATE_REQ: SendTutoHintUpdateRes((sUG_TUTORIAL_HINT_UPDATE_REQ*)data); break;

	//CASH/EVENT SHOPS (not working)
	case UG_SHOP_EVENTITEM_START_REQ: SendEventItemStartRes(); break;
	case UG_SHOP_EVENTITEM_END_REQ: SendEventItemEndRes(); break;
	case UG_SHOP_NETPYITEM_START_REQ: SendNetpyItemStartRes(); break;
	case UG_SHOP_NETPYITEM_END_REQ: SendNetpyItemEndRes(); break;

	// SYS PACKETS
	case SYS_ALIVE: { ResetAliveTime(); } break;
	case SYS_PING: break;
	default:
		Logger::Log("Received Opcode: %s\n", NtlGetPacketName_UG(data->wOpCode));
		return false;
		break;
	}
	return true;
}

void GameClient::SendEventItemStartRes()
{
	sGU_SHOP_EVENTITEM_START_RES sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_SHOP_NETPYITEM_START_RES;
	sPkt.byType = 0; // 0 Normal - 1 Especial Event NPC
	sPkt.wResultCode = GAME_SUCCESS;
	Send(&sPkt, sizeof(sPkt));
}

void GameClient::SendEventItemEndRes()
{
	sGU_SHOP_EVENTITEM_END_RES sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_SHOP_NETPYITEM_START_RES;
	sPkt.wResultCode = GAME_SUCCESS;
	Send(&sPkt, sizeof(sPkt));
}

void GameClient::SendNetpyItemStartRes()
{
	sGU_SHOP_NETPYITEM_START_RES sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_SHOP_NETPYITEM_START_RES;
	sPkt.byType = 0; // 0 Normal - 1 Especial Event NPC
	sPkt.wResultCode = GAME_SUCCESS;
	Send(&sPkt, sizeof(sPkt));
}

void GameClient::SendNetpyItemEndRes()
{
	sGU_SHOP_NETPYITEM_END_RES sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_SHOP_NETPYITEM_START_RES;
	sPkt.wResultCode = GAME_SUCCESS;
	Send(&sPkt, sizeof(sPkt));
}

void GameClient::SendTutoHintUpdateRes(sUG_TUTORIAL_HINT_UPDATE_REQ* pData)
{
}

void GameClient::SendSocialAction(sUG_SOCIAL_ACTION* pData)
{
	sGU_SOCIAL_ACTION sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_SOCIAL_ACTION;
	sPkt.hSubject = GetCharSerialID();
	sPkt.socialActionId = pData->socialActionId;
	pServer->GetClientManager()->SendOthers(&sPkt, sizeof(sPkt), this);
}

void GameClient::SendTSConfirmRes(sUG_TS_CONFIRM_STEP_REQ* pData)
{
	sGU_TS_CONFIRM_STEP_RES sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_TS_CONFIRM_STEP_RES;
	sPkt.byTsType = pData->byTsType;
	sPkt.dwParam = pData->dwParam;
	sPkt.tId = pData->tId;
	sPkt.tcCurId = pData->tcCurId;
	sPkt.tcNextId = pData->tcNextId;
	sPkt.wResultCode = RESULT_SUCCESS;
	Send(&sPkt, sizeof(sPkt));

	SendSystemText("Quest[%d] CurID[%d] NextID[%d] Type[%d] EvtType[%d] EvtData[%d] Param[%d]",
		pData->tId, pData->tcCurId, pData->tcNextId, pData->byTsType, pData->byEventType, pData->dwEventData, pData->dwParam);
}

void GameClient::UpdateCharObjEquips(HOBJECT hItem, BYTE byPos)
{
	sGU_UPDATE_ITEM_EQUIP sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_UPDATE_ITEM_EQUIP;
	sPkt.byPos = byPos;
	sPkt.handle = GetCharSerialID();
	GetItemBrief(sPkt.sItemBrief, hItem);
	pServer->GetObjectManager()->UpdatePcItemBrief(GetCharSerialID(), sPkt.sItemBrief, byPos);
	pServer->GetClientManager()->SendOthers(&sPkt, sizeof(sPkt), this);
}

void GameClient::SendIemMoveRes(sUG_ITEM_MOVE_REQ* pData)
{
	sGU_ITEM_MOVE_RES sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_ITEM_MOVE_RES;

	HOBJECT hSrcItem = GetInventoryItemSerialID(pData->bySrcPlace, pData->bySrcPos);
	HOBJECT hDestItem = GetInventoryItemSerialID(pData->byDestPlace, pData->byDestPos);

	if (hSrcItem != INVALID_HOBJECT)
	{
		UpdateItemInventoryPosition(hSrcItem, pData->byDestPlace, pData->byDestPos);
	}
	if (hDestItem != INVALID_HOBJECT)
	{
		UpdateItemInventoryPosition(hDestItem, pData->bySrcPlace, pData->bySrcPos);
	}

	Logger::Log("Char[%u] moving item Src[%u] [%d:%d] Dest[%u] [%d:%d]\n",
		CurrCharID, hSrcItem, pData->bySrcPlace, pData->bySrcPos, hDestItem, pData->byDestPlace, pData->byDestPos);

	sPkt.byDestPlace = pData->byDestPlace;
	sPkt.byDestPos = pData->byDestPos;
	sPkt.bySrcPlace = pData->bySrcPlace;
	sPkt.bySrcPos = pData->bySrcPos;
	sPkt.hSrcItem = hSrcItem;
	sPkt.hDestItem = hDestItem;
	sPkt.wResultCode = GAME_SUCCESS;
	Send(&sPkt, sizeof(sPkt));

	if ((pData->byDestPlace == CONTAINER_TYPE_EQUIP) && 
		((pData->byDestPos >= EQUIP_SLOT_TYPE_FIRST) && (pData->byDestPos <= EQUIP_SLOT_TYPE_LAST)))
	{
		UpdateCharObjEquips(hSrcItem, pData->byDestPos);
	}

	if ((pData->bySrcPlace == CONTAINER_TYPE_EQUIP) &&
		((pData->bySrcPos >= EQUIP_SLOT_TYPE_FIRST) && (pData->bySrcPos <= EQUIP_SLOT_TYPE_LAST)))
	{
		UpdateCharObjEquips(hDestItem, pData->bySrcPos);
	}
}

void GameClient::SendGameExitRes()
{
	sGU_GAME_EXIT_RES sRes;
	memset(&sRes, 0, sizeof(sRes));
	sRes.wOpCode = GU_CHAR_EXIT_RES;
	Send(&sRes, sizeof(sRes));
}

void GameClient::SendCharExitRes()
{
	sGU_CHAR_EXIT_RES sRes;
	memset(&sRes, 0, sizeof(sRes));
	sRes.wOpCode = GU_CHAR_EXIT_RES;
	sRes.wResultCode = GAME_SUCCESS;
	memcpy(sRes.achAuthKey, AuthKey, NTL_MAX_SIZE_AUTH_KEY);

	// servers
	sRes.byServerInfoCount = pServer->ServerCfg->GetInt("CharServerList", "Count");
	for (int x = 0; x < sRes.byServerInfoCount; x++)
	{
		char snode[20];
		sprintf_s(snode, "CharServer%d", x + 1);
		memcpy(sRes.aServerInfo[x].szCharacterServerIP, pServer->ServerCfg->GetChildStr("CharServerList", snode, "IP"), NTL_MAX_LENGTH_OF_IP);
		sRes.aServerInfo[x].wCharacterServerPortForClient = pServer->ServerCfg->GetChildInt("CharServerList", snode, "Port");
		sRes.aServerInfo[x].dwLoad = 0;
	}
	Send(&sRes, sizeof(sRes));
}

void GameClient::SendGameLeaveRes()
{
	Logger::Log("Client[%u] exist game\n", this);
	sGU_GAME_LEAVE_RES glRes;
	memset(&glRes, 0, sizeof(glRes));
	glRes.wOpCode = GU_GAME_LEAVE_RES;
	glRes.wResultCode = GAME_SUCCESS;
	Send(&glRes, sizeof(glRes));
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
	sPacket.handle = pServer->AcquireSerialID();
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
	pServer->GetClientManager()->SpawnObjects();
}

void GameClient::CheckCommand(sUG_SERVER_COMMAND* pData)
{
	GameString command(pData->awchCommand);

	Logger::Log("%s typed command: %s\n", GameString(this->charName).c_str(), command.c_str());

	std::vector<std::string> tok;
	command.GetToken(tok, ' ');

	if (tok.size() != 0 && this->isGameMaster)
	{
		if (strcmp(tok[0].c_str(), "@teste") == 0)
		{
			// TEST COMMANDS
		}
		if (strcmp(tok[0].c_str(), "@questcomplete") == 0)
		{
			if (tok.size() > 1)
			{
				QUESTID qId = atoi(tok[1].c_str());
				sGU_QUEST_FORCED_COMPLETION_NFY sPkt;
				memset(&sPkt, 0, sizeof(sPkt));
				sPkt.wOpCode = GU_QUEST_FORCED_COMPLETION_NFY;
				sPkt.questId = qId;
				Send(&sPkt, sizeof(sPkt));
			}
		}
		if (strcmp(tok[0].c_str(), "@additem") == 0)
		{
			if (tok.size() > 1)
			{
				BYTE qtd = 1;
				ITEMID item = atoi(tok[1].c_str());
				if (tok.size() == 3) qtd = atoi(tok[2].c_str());
				sGU_ITEM_CREATE sPkt = InsertNextBagSlot(item, qtd);
				Send(&sPkt, sizeof(sPkt));
			}
		}
		if (strcmp(tok[0].c_str(), "@setspeed") == 0)
		{
			if (tok.size() > 1)
			{
				float speed = (float)atof(tok[1].c_str());
				PcProfile.avatarAttribute.fLastRunSpeed = speed;
				sGU_UPDATE_CHAR_SPEED sPkt;
				memset(&sPkt, 0, sizeof(sPkt));
				sPkt.wOpCode = GU_UPDATE_CHAR_SPEED;
				sPkt.handle = GetCharSerialID();
				sPkt.fLastRunningSpeed = sPkt.fLastWalkingSpeed = speed;
				pServer->GetClientManager()->SendAll(&sPkt, sizeof(sPkt));
			}
		}
		if (strcmp(tok[0].c_str(), "@spawnmob") == 0)
		{
			if (tok.size() > 1)
			{
				SpawnTesteMob(atoi(tok[1].c_str()));
			}
		}
		if (strcmp(tok[0].c_str(), "@notice") == 0)
		{
			if (tok.size() > 1)
			{
				std::string msg = "";
				for (unsigned int i = 1; i < tok.size(); i++)
				{
					msg.append(tok[i] + " ");
				}
				SendSystemText(GameString(msg.c_str()), SERVER_TEXT_SYSNOTICE);
			}
		}
		if (strcmp(tok[0].c_str(), "@emergency") == 0)
		{
			if (tok.size() > 1)
			{
				std::string msg = "";
				for (unsigned int i = 1; i < tok.size(); i++)
				{
					msg.append(tok[i] + " ");
				}
				SendSystemText(GameString(msg.c_str()), SERVER_TEXT_EMERGENCY);
			}
		}
		if (strcmp(tok[0].c_str(), "@cashshop") == 0)
		{
			SendNetpyItemStartRes();
		}
		if (strcmp(tok[0].c_str(), "@eventshop") == 0)
		{
			SendEventItemStartRes();
		}
	}
}

void GameClient::SendCharReadyRes(sUG_CHAR_READY* pData)
{
	byAvatarType = pData->byAvatarType;
	InsertOnlineData();
	//Send(&pData, sizeof(pData));
}

void GameClient::SendCharReadySpawnReq()
{
	sGU_OBJECT_CREATE charSpawn = GetCharSpawnData();
	charSpawn.handle = CharSerialID;
	if (pServer->GetClientManager()->AddClient(this))
	{
		pServer->GetObjectManager()->AddObject(charSpawn);
		pServer->GetClientManager()->SpawnObjects();
	}
}

void GameClient::SendGameEnterRes(sUG_GAME_ENTER_REQ* data)
{
	this->CharSerialID = pServer->AcquireSerialID();
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

void GameClient::SendCharJump(sUG_CHAR_JUMP* pData)
{
	sGU_CHAR_JUMP pJump;
	memset(&pJump, 0, sizeof(pJump));
	pJump.wOpCode = GU_CHAR_JUMP;
	pJump.handle = GetCharSerialID();
	pJump.byMoveDirection = byMoveDirection;
	pJump.vCurrentHeading = pData->vCurrentHeading;
	pJump.vJumpDir = CharState.sCharStateBase.vCurDir;
	pServer->GetClientManager()->SendOthers(&pJump, sizeof(pJump), this);
}

void GameClient::SendCharJumpEnd()
{
	sGU_CHAR_JUMP_END pJEnd;
	pJEnd.handle = GetCharSerialID();
	pJEnd.wOpCode = GU_CHAR_JUMP_END;
	pServer->GetClientManager()->SendOthers(&pJEnd, sizeof(pJEnd), this);
}

void GameClient::SendCharMove(sUG_CHAR_MOVE* data)
{
	UpdatePositions(data->vCurDir, data->vCurLoc);
	pServer->GetObjectManager()->UpdateCharState(GetCharSerialID(), CharState);
	sGU_CHAR_MOVE mData;
	memset(&mData, 0, sizeof(mData));
	mData.wOpCode = GU_CHAR_MOVE;
	if (data->byAvatarType == byAvatarType)
	{
		mData.vCurDir.x = data->vCurDir.x;
		mData.vCurDir.y = 0.0f;
		mData.vCurDir.z = data->vCurDir.z;
		mData.vCurLoc.x = data->vCurLoc.x;
		mData.vCurLoc.y = data->vCurLoc.y;
		mData.vCurLoc.z = data->vCurLoc.z;
		mData.handle = CharSerialID;
		byMoveDirection = mData.byMoveDirection = data->byMoveDirection;
	}
	pServer->GetClientManager()->SendOthers(&mData, sizeof(mData), this);
}

void GameClient::SendCharDestMove(sUG_CHAR_DEST_MOVE* pData)
{
	sGU_CHAR_DEST_MOVE dMove;
	memset(&dMove, 0, sizeof(dMove));
	dMove.wOpCode = GU_CHAR_DEST_MOVE;
	if (pData->byAvatarType == byAvatarType)
	{
		dMove.vCurLoc = pData->vCurLoc;
		dMove.handle = GetCharSerialID();
		dMove.byDestLocCount = 1;
		dMove.avDestLoc[0] = pData->vDestLoc;
		dMove.dwTimeStamp = pData->dwTimeStamp;
		dMove.byMoveFlag = 0; // to do run or not
	}
	pServer->GetClientManager()->SendOthers(&dMove, sizeof(dMove), this);
}

void GameClient::SendCharMoveSync(sUG_CHAR_MOVE_SYNC* pData)
{
	UpdatePositions(pData->vCurDir, pData->vCurLoc);
	pServer->GetObjectManager()->UpdateCharState(GetCharSerialID(), CharState);
	sGU_CHAR_MOVE_SYNC cmSync;
	memset(&cmSync, 0, sizeof(cmSync));
	cmSync.wOpCode = GU_CHAR_MOVE_SYNC;
	if (pData->byAvatarType == byAvatarType)
	{
		cmSync.handle = GetCharSerialID();
		cmSync.vCurDir = pData->vCurDir;
		cmSync.vCurLoc = pData->vCurLoc;
		cmSync.dwTimeStamp = pData->dwTimeStamp;
	}
	pServer->GetClientManager()->SendOthers(&cmSync, sizeof(cmSync), this);
}

void GameClient::SendCharChangeHeading(sUG_CHAR_CHANGE_HEADING* pData)
{
	sGU_CHAR_CHANGE_HEADING pCHead;
	memset(&pCHead, 0, sizeof(pCHead));
	pCHead.wOpCode = GU_CHAR_CHANGE_HEADING;
	pCHead.handle = GetCharSerialID();
	pCHead.dwTimeStamp = pData->dwTimeStamp;
	pCHead.vNewHeading = pData->vCurrentHeading;
	pCHead.vNewLoc = pData->vCurrentPosition;
	pServer->GetClientManager()->SendOthers(&pCHead, sizeof(pCHead), this);
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

void GameClient::SendSystemText(char* szText, ...)
{
	va_list args;
	va_start(args, szText);
	char text[NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE];
	vsprintf_s(text, szText, args);
	SendSystemText(GameString(text), SERVER_TEXT_SYSTEM);
	va_end(args);
}

void GameClient::SendSystemText(GameString msg, eSERVER_TEXT_TYPE type)
{
	sGU_SYSTEM_DISPLAY_TEXT sPkt;
	memset(&sPkt, 0, sizeof(sPkt));
	sPkt.wOpCode = GU_SYSTEM_DISPLAY_TEXT;
	memcpy(sPkt.awGMChar, charName, NTL_MAX_SIZE_CHAR_NAME_UNICODE);
	sPkt.byDisplayType = type;
	sPkt.wMessageLengthInUnicode = NTL_MAX_LENGTH_OF_CHAT_MESSAGE_UNICODE;
	Logger::Log("MESSAGE LEN[%d]\n", strlen(msg.c_str()));
	memcpy(sPkt.awchMessage, msg.wc_str(), sPkt.wMessageLengthInUnicode);
	pServer->GetClientManager()->SendAll(&sPkt, sizeof(sPkt));
}