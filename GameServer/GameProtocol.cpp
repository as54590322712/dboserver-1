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
		SendCharQuickSlotInfo();
		SendCharInfoEnd();
	} break;
	case UG_GAME_LEAVE_REQ: break;
	case UG_ENTER_WORLD: {
		SendCharWorldInfo();
		// TO DO WORLD SPAWNS
		SendCharWorldInfoEnd();
	} break;
	case UG_CHAR_READY_TO_SPAWN: SendCharReadyRes(); break;
	case UG_CHAR_MOVE: SendCharMove((sUG_CHAR_MOVE*)data); break;
	case UG_CHAR_DEST_MOVE: break;
	case UG_CHAR_CHANGE_HEADING: break;
	case UG_CHAR_MOVE_SYNC: break;
	case 1: { sPACKETHEADER reply(1); Send(&reply, sizeof(reply)); } break;
	default:
		Logger::Log("Received Opcode: %d\n", data->wOpCode);
		return false;
		break;
	}
	return true;
}

void GameClient::SendCharReadyRes()
{
	memset(&charSpawn, 0, sizeof(charSpawn));
	charSpawn.OpCode = GU_OBJECT_CREATE;
	charSpawn.handle = CharSerialID;
	charSpawn.ObjectInfo.objType = OBJTYPE_PC;
	charSpawn.ObjectInfo.pcBrief.charId = CurrCharID;
	charSpawn.ObjectInfo.pcBrief.tblidx = PcProfile.tblidx;
	charSpawn.ObjectInfo.pcBrief.PcShape = PcProfile.CharShape;
	charSpawn.ObjectInfo.pcBrief.Level = PcProfile.Level;
	charSpawn.ObjectInfo.pcBrief.AttackSpeedRate = PcProfile.avatarAttribute.LastAttackSpeedRate;
	charSpawn.ObjectInfo.pcBrief.CurEP = PcProfile.CurEP;
	charSpawn.ObjectInfo.pcBrief.CurLP = PcProfile.CurLP;
	charSpawn.ObjectInfo.pcBrief.MaxEP = PcProfile.avatarAttribute.LastMaxEP;
	charSpawn.ObjectInfo.pcBrief.MaxLP = PcProfile.avatarAttribute.LastMaxLP;
	charSpawn.ObjectInfo.pcBrief.Speed = PcProfile.avatarAttribute.LastRunSpeed;
	memcpy(charSpawn.ObjectInfo.pcBrief.Name, PcProfile.Name, MAX_CHARNAME_SIZE);
	charSpawn.ObjectInfo.pcBrief.IsAdult = PcProfile.IsAdult;
	charSpawn.ObjectInfo.pcState = CharState;

	for (int i = 0; i < MAX_INVEN_ITEMCOUNT; i++)
	{
		int slot = ItemProfile[i].Pos;
		if (slot >= EQUIP_SLOT_TYPE_FIRST &&
			slot <= EQUIP_SLOT_TYPE_LAST)
		{
			charSpawn.ObjectInfo.pcBrief.ItemBrief[slot].tblidx = ItemProfile[i].tblidx;
			charSpawn.ObjectInfo.pcBrief.ItemBrief[slot].BattleAttribute = ItemProfile[i].BattleAttribute;
			charSpawn.ObjectInfo.pcBrief.ItemBrief[slot].Grade = ItemProfile[i].Grade;
			memcpy(charSpawn.ObjectInfo.pcBrief.ItemBrief[slot].OptionTblidx, ItemProfile[i].OptionTblidx, 2);
			charSpawn.ObjectInfo.pcBrief.ItemBrief[slot].Rank = ItemProfile[i].Rank;
		}
	}

	pServer->SendOthers(&charSpawn, sizeof(charSpawn), this);
	pServer->RecvOthers(GU_OBJECT_CREATE, this);
	pServer->AddClient(GameString(PcProfile.Name).c_str(), this);
}

void GameClient::SendGameEnterRes(sUG_GAME_ENTER_REQ* data)
{
	this->CharSerialID = pServer->AcquireCharSerialID();
	this->AccountID = data->accountId;
	this->CurrCharID = data->charId;
	this->CurrServerID = pServer->ServerID;
	this->TutorialMode = data->TutorialMode;
	memcpy(this->AuthKey, data->AuthKey, MAX_AUTHKEY_SIZE);

	Logger::Log("Client[%d] entering game (%d|%d) handle[%d]\n", this, AccountID, CurrCharID, CharSerialID);

	sGU_GAME_ENTER_RES geRes;
	memset(&geRes, 0, sizeof(geRes));
	geRes.OpCode = GU_GAME_ENTER_RES;
	memcpy(geRes.CommunityServerIP, pServer->ServerCfg->GetStr("ChatServer", "IP"), MAX_SRVADDR_SIZE);
	geRes.CommunityServerPort = pServer->ServerCfg->GetInt("ChatServer", "Port");
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
	charInfo.handle = this->CharSerialID;
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
	wInfo.CurLoc.x += (float)(rand() % 5);
	wInfo.CurLoc.y += (float)(rand() % 5);
	wInfo.CurLoc.z += (float)(rand() % 5);
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
	UpdatePositions(data->CurDir, data->CurLoc);
	sGU_CHAR_MOVE mData;
	memset(&mData, 0, sizeof(mData));
	mData.OpCode = GU_CHAR_MOVE;
	mData.CurDir.x = data->CurDir.x;
	mData.CurDir.y = 0.0f;
	mData.CurDir.z = data->CurDir.z;
	mData.CurLoc.x = data->CurLoc.x;
	mData.CurLoc.y = data->CurLoc.y;
	mData.CurLoc.z = data->CurLoc.z;
	mData.handle = CharSerialID;
	mData.MoveDirection = data->MoveDirection;
	pServer->SendOthers(&mData, sizeof(mData), this);
}

void GameClient::SendCharItemInfo()
{
	sGU_AVATAR_ITEM_INFO iInfo;
	memset(&iInfo, 0, sizeof(iInfo));
	iInfo.OpCode = GU_AVATAR_ITEM_INFO;
	iInfo.ItemCount = LoadItemData();
	memcpy(iInfo.ItemProfile, ItemProfile, sizeof(ItemProfile));
	int psize = 3;
	psize += sizeof(ITEM_PROFILE) * iInfo.ItemCount;
	Send(&iInfo, psize);
}

void GameClient::SendCharSkillInfo()
{
	sGU_AVATAR_SKILL_INFO sInfo;
	memset(&sInfo, 0, sizeof(sInfo));
	sInfo.OpCode = GU_AVATAR_SKILL_INFO;
	sInfo.SkillCount = LoadSkillData();
	memcpy(sInfo.SkillInfo, SkillInfo, sizeof(SkillInfo));
	int psize = 3;
	psize += sizeof(SKILL_INFO) * sInfo.SkillCount;
	Send(&sInfo, psize);
}

void GameClient::SendCharQuickSlotInfo()
{
	sGU_QUICK_SLOT_INFO qsInfo;
	memset(&qsInfo, 0, sizeof(qsInfo));
	qsInfo.OpCode = GU_QUICK_SLOT_INFO;
	qsInfo.QuickSlotCount = LoadQuickslotData();
	memcpy(qsInfo.QuickSlotData, QuickSlotData, sizeof(QuickSlotData));
	int psize = 3;
	psize += sizeof(QUICK_SLOT_PROFILE) * qsInfo.QuickSlotCount;
	Send(&qsInfo, psize);
}