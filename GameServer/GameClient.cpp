#include "GameNetwork.h"

GameClient::GameClient(bool IsAliveCheck, bool IsOpcodeCheck)
	:Session(SESSION_CLIENT)
{
	SetControlFlag(CONTROL_FLAG_USE_SEND_QUEUE);

	if (IsAliveCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_ALIVE);
	}
	if (IsOpcodeCheck)
	{
		SetControlFlag(CONTROL_FLAG_CHECK_OPCODE);
	}

	SetPacketEncoder(&_packetEncoder);
	pServer = (GameServer*)_GetApp();
}

GameClient::~GameClient()
{
	OnClose();
}

int	GameClient::OnAccept()
{
	return 0;
}

void GameClient::OnClose()
{
	if (goCharServer) pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '2' WHERE `ID` = '%d';", AccountID);
	else pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '0' WHERE `ID` = '%d';", AccountID);
	if (pServer->GetClientManager()->FindClient(this))
		pServer->GetClientManager()->RemoveClient(this);
	if (pServer->GetObjectManager()->FindObject(GetCharSerialID(), OBJTYPE_PC))
	{
		pServer->GetObjectManager()->RemoveObject(GetCharSerialID(), OBJTYPE_PC);
		sGU_OBJECT_DESTROY obDes;
		memset(&obDes, 0, sizeof(obDes));
		obDes.wOpCode = GU_OBJECT_DESTROY;
		obDes.handle = GetCharSerialID();
		pServer->GetClientManager()->SendOthers(&obDes, sizeof(obDes), this);
	}
	RemoveOnlineData();
}

int GameClient::OnDispatch(Packet* pPacket)
{
	PacketControl(pPacket);
	return 0;
}

void GameClient::Send(void* pData, int nSize)
{
	Send(pData, nSize, this->GetHandle());
}

void GameClient::Send(void* pData, int nSize, int nHandle)
{
	Packet* packet = new Packet((unsigned char*)pData, nSize);
	int rc = pServer->Send(nHandle, packet);
	if (0 != rc)
	{
		Logger::Log("Failed to send packet %d\n", rc);
	}
}

void GameClient::AddSpawn(unsigned int nHandle, BYTE byType)
{
	objSpawn.insert(std::make_pair(nHandle, byType));
}

void GameClient::RemoveSpawn(unsigned int nHandle)
{
	objSpawn.erase(nHandle);
}

bool GameClient::FindSpawn(unsigned int nHandle, BYTE byType)
{
	for each (objSp var in objSpawn)
	{
		if (var.first == nHandle && var.second == byType)
			return true;
	}
	return false;
}

void GameClient::GetItemBrief(sITEM_BRIEF& sBrief, HOBJECT hItem)
{
	if (hItem == INVALID_HOBJECT)
	{
		sBrief.tblidx = INVALID_ITEMID;
	}
	else
	{
		for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
		{
			if (ItemProfile[i].handle == hItem)
			{
				sBrief.tblidx = ItemProfile[i].tblidx;
				sBrief.byBattleAttribute = ItemProfile[i].byBattleAttribute;
				sBrief.byGrade = ItemProfile[i].byGrade;
				sBrief.byRank = ItemProfile[i].byRank;
				sBrief.aOptionTblidx[0] = ItemProfile[i].aOptionTblidx[0];
				sBrief.aOptionTblidx[1] = ItemProfile[i].aOptionTblidx[1];
			}
		}
	}
}

void GameClient::UpdateItemInventoryPosition(HOBJECT hItem, BYTE byPlace, BYTE byPos)
{
	pServer->ServerDB->ExecuteQuery("UPDATE `inventory` SET `Place` = '%d', `Slot` = '%d' WHERE `ID` = '%u' AND `CharID` = '%u';",
		byPlace, byPos, hItem, CurrCharID);
	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
	{
		if (ItemProfile[i].handle == hItem)
		{
			ItemProfile[i].byPlace = byPlace;
			ItemProfile[i].byPos = byPos;
		}
	}
}

HOBJECT GameClient::GetInventoryItemSerialID(BYTE byPlace, BYTE byPos)
{
	HOBJECT ret = INVALID_HOBJECT;
	if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM `inventory` WHERE `Place` = '%d' AND `Slot` = '%d' AND `CharID` = '%u';",
		byPlace, byPos, CurrCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			ret = pServer->ServerDB->getInt("ID");
		}
	}
	return ret;
}

void GameClient::InsertOnlineData()
{
	pServer->ServerDB->ExecuteQuery("CALL `spInsertOnline`('%u','%u','%u','%u','%u');",
		AccountID, CurrCharID, CurrServerID, CurrChannelID, CharSerialID);
}

void GameClient::RemoveOnlineData()
{
	pServer->ServerDB->ExecuteQuery("CALL `spDeleteOnline`('%u','%u');",
		AccountID, CurrCharID);
}

int GameClient::LoadQuickslotData()
{
	int count = 0;
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `quickslot` WHERE `CharID`='%u';", this->CurrCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			QuickSlotData[count].tblidx = pServer->ServerDB->getInt("TblID");
			QuickSlotData[count].bySlot = pServer->ServerDB->getInt("Slot");
			QuickSlotData[count].byType = pServer->ServerDB->getInt("Type");
			QuickSlotData[count].hItem = pServer->ServerDB->getInt("Item");
			count++;
		}
	}
	return count;
}

int GameClient::LoadSkillData()
{
	int count = 0;
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `skills` WHERE `CharID`='%u';", this->CurrCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			SkillInfo[count].tblidx = pServer->ServerDB->getInt("SkillID");
			SkillInfo[count].bySlotId = pServer->ServerDB->getInt("Slot");
			SkillInfo[count].bIsRpBonusAuto = pServer->ServerDB->getBoolean("IsRpBonusAuto");
			SkillInfo[count].byRpBonusType = pServer->ServerDB->getInt("RpBonusType");
			SkillInfo[count].dwTimeRemaining = pServer->ServerDB->getInt("RemainSec");
			SkillInfo[count].nExp = pServer->ServerDB->getInt("Exp");
			count++;
		}
	}
	return count;
}

sGU_ITEM_CREATE GameClient::InsertNextBagSlot(ITEMID item, BYTE qtd)
{
	sGU_ITEM_CREATE itemdata;
	memset(&itemdata, 0, sizeof(itemdata));
	HOBJECT hItem = INVALID_HOBJECT;
	int lastbagslot = 0;
	int lastbag = 1;
	bool found = false;
	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
	{
		if (ItemProfile[i].byPlace >= CONTAINER_TYPE_BAG_FIRST && ItemProfile[i].byPlace <= CONTAINER_TYPE_BAG_LAST)
		{
			if (lastbagslot < ItemProfile[i].byPos)
			{
				lastbagslot = ItemProfile[i].byPos;
				lastbag = ItemProfile[i].byPlace;
			}
		}
		
		if (ItemProfile[i].handle == INVALID_HOBJECT && ItemProfile[i].tblidx == INVALID_TBLIDX)
		{
			if (lastbagslot != 0) lastbagslot++;
			if (pServer->ServerDB->ExecuteSp("CALL `spInsertItem`('%u','%u','%d','%d','%d','1','100','0','0','0','0','','0','0','0');",
				item, CurrCharID, lastbag, lastbagslot, qtd))
			{
				do {
					pServer->ServerDB->GetResultSet();
					while (pServer->ServerDB->Fetch()) {
						hItem = pServer->ServerDB->getInt("LastID");
					}
				} while (pServer->ServerDB->GetMoreResults());
			}

			itemdata.bIsNew = true;
			itemdata.wOpCode = GU_ITEM_CREATE;
			itemdata.handle = hItem;
			itemdata.sItemData.itemId = hItem;
			itemdata.sItemData.charId = CurrCharID;
			itemdata.sItemData.itemNo = item;
			itemdata.sItemData.byCurrentDurability = 100;
			itemdata.sItemData.byPlace = lastbag;
			itemdata.sItemData.byPosition = lastbagslot;
			itemdata.sItemData.byStackcount = qtd;
			itemdata.sItemData.byRank = 1;

			ItemProfile[i].handle = itemdata.sItemData.itemId;
			ItemProfile[i].tblidx = item;
			ItemProfile[i].byCurDur = itemdata.sItemData.byCurrentDurability;
			ItemProfile[i].byPlace = itemdata.sItemData.byPlace;
			ItemProfile[i].byPos = itemdata.sItemData.byPosition;
			ItemProfile[i].byStackcount = itemdata.sItemData.byStackcount;
			ItemProfile[i].byRank = itemdata.sItemData.byRank;
			break;
		}
	}
	return itemdata;
}

int GameClient::LoadItemData()
{
	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
	{
		ItemProfile[i].handle = INVALID_HOBJECT;
		ItemProfile[i].tblidx = INVALID_TBLIDX;
	}
	int count = 0;
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `inventory` WHERE `CharID`='%u';", this->CurrCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			ItemProfile[count].handle = pServer->ServerDB->getInt("ID");
			ItemProfile[count].tblidx = pServer->ServerDB->getInt("ItemID");
			ItemProfile[count].byPlace = pServer->ServerDB->getInt("Place");
			ItemProfile[count].byPos = pServer->ServerDB->getInt("Slot");
			ItemProfile[count].byStackcount = pServer->ServerDB->getInt("Stack");
			ItemProfile[count].byRank = pServer->ServerDB->getInt("Rank");
			ItemProfile[count].byCurDur = pServer->ServerDB->getInt("CurDur");
			ItemProfile[count].bNeedToIdentify = pServer->ServerDB->getBoolean("NeedToIdentify");
			ItemProfile[count].byGrade = pServer->ServerDB->getInt("Grade");
			ItemProfile[count].byBattleAttribute = pServer->ServerDB->getInt("BattleAttribute");
			ItemProfile[count].byRestrictType = pServer->ServerDB->getInt("RestrictType");
			memcpy(ItemProfile[count].awchMaker, charToWChar(pServer->ServerDB->getString("Maker")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
			ItemProfile[count].aOptionTblidx[0] = pServer->ServerDB->getInt("Opt1");
			ItemProfile[count].aOptionTblidx[1] = pServer->ServerDB->getInt("Opt2");
			ItemProfile[count].byDurationType = pServer->ServerDB->getInt("DurationType");
			ItemProfile[count].nUseStartTime = pServer->ServerDB->getInt("UseStartTime");
			ItemProfile[count].nUseEndTime = pServer->ServerDB->getInt("UseEndTime");
			count++;
		}
	}
	return count;
}

void GameClient::UpdatePositions(sVECTOR2 Dir, sVECTOR3 Loc)
{
	CharState.sCharStateBase.vCurLoc = Loc;
	CharState.sCharStateBase.vCurDir.x = Dir.x;
	CharState.sCharStateBase.vCurDir.y = 0.0f;
	CharState.sCharStateBase.vCurDir.z = Dir.z;
	pServer->ServerDB->ExecuteQuery("CALL `spUpdatePosition`('%u', '%f', '%f', '%f');", this->CurrCharID, Loc.x, Loc.y, Loc.z);
	pServer->ServerDB->ExecuteQuery("CALL `spUpdateDirection`('%u', '%f', '%f', '%f');", this->CurrCharID, Dir.x, 0.0f, Dir.z);
}

void GameClient::UpdatePositions(sVECTOR3 Dir, sVECTOR3 Loc)
{
	CharState.sCharStateBase.vCurLoc = Loc;
	CharState.sCharStateBase.vCurDir = Dir;
	pServer->ServerDB->ExecuteQuery("CALL `spUpdatePosition`('%u', '%f', '%f', '%f');", this->CurrCharID, Loc.x, Loc.y, Loc.z);
	pServer->ServerDB->ExecuteQuery("CALL `spUpdateDirection`('%u', '%f', '%f', '%f');", this->CurrCharID, Dir.x, Dir.y, Dir.z);
}

void GameClient::LoadWorldInfoData()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ID`='%d';", this->AccountID, this->CurrCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			worldInfo.tblidx = pServer->ServerDB->getInt("worldTblidx");
			worldInfo.worldID = pServer->ServerDB->getInt("worldId");
			worldInfo.hTriggerObjectOffset = 100000; // WHAT IS THIS??
			worldInfo.sRuleInfo.byRuleType = GAMERULE_NORMAL;
		}
	}
}

void GameClient::CalculateAtributes(sPC_TBLDAT* pcdata)
{
	PcProfile.avatarAttribute.wBaseMaxEP += (pcdata->byLevel_Up_EP * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseMaxLP += (pcdata->byLevel_Up_LP * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseMaxRP += (pcdata->byLevel_Up_RP * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseStr += (BYTE)(pcdata->fLevel_Up_Str * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseDex += (BYTE)(pcdata->fLevel_Up_Dex * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseFoc += (BYTE)(pcdata->fLevel_Up_Foc * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseEng += (BYTE)(pcdata->fLevel_Up_Eng * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseCon += (BYTE)(pcdata->fLevel_Up_Con * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseSol += (BYTE)(pcdata->fLevel_Up_Sol * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBasePhysicalOffence += (pcdata->byLevel_Up_Physical_Offence * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBasePhysicalDefence += (pcdata->byLevel_Up_Physical_Defence * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseEnergyOffence += (pcdata->byLevel_Up_Energy_Offence * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseEnergyDefence += (pcdata->byLevel_Up_Energy_Defence * PcProfile.byLevel);

	PcProfile.avatarAttribute.wLastMaxEP = PcProfile.avatarAttribute.wBaseMaxEP;
	PcProfile.avatarAttribute.wLastMaxLP = PcProfile.avatarAttribute.wBaseMaxLP;
	PcProfile.avatarAttribute.wLastMaxRP = PcProfile.avatarAttribute.wBaseMaxRP;
	PcProfile.avatarAttribute.byLastStr = PcProfile.avatarAttribute.byBaseStr;
	PcProfile.avatarAttribute.byLastDex = PcProfile.avatarAttribute.byBaseDex;
	PcProfile.avatarAttribute.byLastFoc = PcProfile.avatarAttribute.byBaseFoc;
	PcProfile.avatarAttribute.byLastEng = PcProfile.avatarAttribute.byBaseEng;
	PcProfile.avatarAttribute.byLastCon = PcProfile.avatarAttribute.byBaseCon;
	PcProfile.avatarAttribute.byLastSol = PcProfile.avatarAttribute.byBaseSol;
	PcProfile.avatarAttribute.wLastPhysicalOffence = PcProfile.avatarAttribute.wBasePhysicalOffence;
	PcProfile.avatarAttribute.wLastPhysicalDefence = PcProfile.avatarAttribute.wBasePhysicalDefence;
	PcProfile.avatarAttribute.wLastEnergyOffence = PcProfile.avatarAttribute.wBaseEnergyOffence;
	PcProfile.avatarAttribute.wLastEnergyDefence = PcProfile.avatarAttribute.wBaseEnergyDefence;
}

void GameClient::LoadCharacterData()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%u' AND `ID`='%u';", AccountID, CurrCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			int Race = pServer->ServerDB->getInt("Race");
			int Class = pServer->ServerDB->getInt("Class");
			int Gender = pServer->ServerDB->getInt("Gender");
			sPC_TBLDAT pcdata = *(sPC_TBLDAT*)pServer->GetTableContainer()->GetPcTable()->GetPcTbldat(Race, Class, Gender);
			Logger::Log("Loaded PC TblInfo: Idx(%u) Race(%u) Class(%u) Gender(%u)\n", pcdata.tblidx, pcdata.byRace, pcdata.byClass, pcdata.byGender);
			memset(&PcProfile, 0, sizeof(PcProfile));
			memcpy(PcProfile.awchName, charToWChar(pServer->ServerDB->getString("Name")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
			memcpy(this->charName, charToWChar(pServer->ServerDB->getString("Name")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
			PcProfile.tblidx = pcdata.tblidx;
			PcProfile.charId = pServer->ServerDB->getInt("ID");
			this->isGameMaster = PcProfile.bIsGameMaster = pServer->ServerDB->getBoolean("IsGameMaster");
			PcProfile.byLevel = pServer->ServerDB->getInt("Level");
			PcProfile.dwCurExp = pServer->ServerDB->getInt("CurExp");
			PcProfile.bIsAdult = pServer->ServerDB->getBoolean("Adult");
			PcProfile.dwMaxExpInThisLevel = 100;
			PcProfile.dwTutorialHint = pServer->ServerDB->getInt("TutorialHint");
			PcProfile.wCurEP = pServer->ServerDB->getInt("CurEP");;
			PcProfile.wCurLP = pServer->ServerDB->getInt("CurLP");;
			PcProfile.wCurRP = pcdata.wBasic_RP;
			PcProfile.dwZenny = pServer->ServerDB->getInt("Money");
			PcProfile.sMarking.byCode = INVALID_MARKING_TYPE;

			PcProfile.avatarAttribute.wBaseMaxEP = pServer->ServerDB->getInt("MaxEP");
			PcProfile.avatarAttribute.wBaseMaxLP = pServer->ServerDB->getInt("MaxLP");
			PcProfile.avatarAttribute.wBaseMaxRP = pcdata.wBasic_RP;
			PcProfile.avatarAttribute.byBaseStr = pcdata.byStr;
			PcProfile.avatarAttribute.byBaseFoc = pcdata.byFoc;
			PcProfile.avatarAttribute.byBaseSol = pcdata.bySol;
			PcProfile.avatarAttribute.byBaseDex = pcdata.byDex;
			PcProfile.avatarAttribute.byBaseCon = pcdata.byCon;
			PcProfile.avatarAttribute.byBaseEng = pcdata.byEng;
			PcProfile.avatarAttribute.fBaseAttackRange = pcdata.fAttack_Range;
			PcProfile.avatarAttribute.wBaseAttackRate = pcdata.wAttack_Rate;
			PcProfile.avatarAttribute.wBaseAttackSpeedRate = pcdata.wAttack_Speed_Rate;
			PcProfile.avatarAttribute.wBaseBlockRate = pcdata.wBlock_Rate;
			PcProfile.avatarAttribute.wBaseCurseSuccessRate = pcdata.wCurse_Success_Rate;
			PcProfile.avatarAttribute.wBaseCurseToleranceRate = pcdata.wCurse_Tolerance_Rate;
			PcProfile.avatarAttribute.wBaseDodgeRate = pcdata.wDodge_Rate;
			PcProfile.avatarAttribute.fLastRunSpeed = (PcProfile.bIsAdult) ? pcdata.fAdult_Run_Speed : pcdata.fChild_Run_Speed;
			CalculateAtributes(&pcdata);

			PcProfile.sPcShape.byFace = pServer->ServerDB->getInt("Face");
			PcProfile.sPcShape.byHair = pServer->ServerDB->getInt("Hair");
			PcProfile.sPcShape.byHairColor = pServer->ServerDB->getInt("HairColor");
			PcProfile.sPcShape.bySkinColor = pServer->ServerDB->getInt("SkinColor");

			memset(&CharState, 0, sizeof(CharState));
			CharState.sCharStateBase.dwConditionFlag = 0;
			CharState.sCharStateBase.bFightMode = false;
			CharState.sCharStateBase.byStateID = 0;
			CharState.sCharStateBase.dwStateTime = (DWORD)time(NULL);
			CharState.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = ASPECTSTATE_INVALID;
			CharState.sCharStateBase.aspectState.sAspectStateDetail.sGreatNamek.bySourceGrade = 0;
			CharState.sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;
			CharState.sCharStateBase.aspectState.sAspectStateDetail.sPureMajin.bySourceGrade = 0;
			CharState.sCharStateBase.aspectState.sAspectStateDetail.sSuperSaiyan.bySourceGrade = 0;
			CharState.sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = 0;

			CharState.sCharStateBase.vCurLoc.x = pServer->ServerDB->getFloat("PositionX");
			CharState.sCharStateBase.vCurLoc.y = pServer->ServerDB->getFloat("PositionY");
			CharState.sCharStateBase.vCurLoc.z = pServer->ServerDB->getFloat("PositionZ");
			CharState.sCharStateBase.vCurDir.x = pServer->ServerDB->getFloat("DirectionX");
			CharState.sCharStateBase.vCurDir.y = pServer->ServerDB->getFloat("DirectionY");
			CharState.sCharStateBase.vCurDir.z = pServer->ServerDB->getFloat("DirectionZ");
		}
	}
}

sGU_OBJECT_CREATE GameClient::GetCharSpawnData()
{
	sGU_OBJECT_CREATE charSpawn;
	memset(&charSpawn, 0, sizeof(charSpawn));
	charSpawn.wOpCode = GU_OBJECT_CREATE;
	charSpawn.handle = GetCharSerialID();
	charSpawn.sObjectInfo.objType = OBJTYPE_PC;
	charSpawn.sObjectInfo.pcBrief.charId = CurrCharID;
	charSpawn.sObjectInfo.pcBrief.tblidx = PcProfile.tblidx;
	charSpawn.sObjectInfo.pcBrief.byLevel = PcProfile.byLevel;
	charSpawn.sObjectInfo.pcBrief.wAttackSpeedRate = PcProfile.avatarAttribute.wLastAttackSpeedRate;
	charSpawn.sObjectInfo.pcBrief.wCurEP = PcProfile.wCurEP;
	charSpawn.sObjectInfo.pcBrief.wCurLP = PcProfile.wCurLP;
	charSpawn.sObjectInfo.pcBrief.wMaxEP = PcProfile.avatarAttribute.wLastMaxEP;
	charSpawn.sObjectInfo.pcBrief.wMaxLP = PcProfile.avatarAttribute.wLastMaxLP;
	charSpawn.sObjectInfo.pcBrief.fSpeed = PcProfile.avatarAttribute.fLastRunSpeed;
	memcpy(charSpawn.sObjectInfo.pcBrief.awchName, PcProfile.awchName, NTL_MAX_SIZE_CHAR_NAME_UNICODE);
	charSpawn.sObjectInfo.pcBrief.sMarking.byCode = INVALID_MARKING_TYPE;
	charSpawn.sObjectInfo.pcBrief.bIsAdult = PcProfile.bIsAdult;
	memcpy(&charSpawn.sObjectInfo.pcBrief.sPcShape, &PcProfile.sPcShape, sizeof(PcProfile.sPcShape));
	memcpy(&charSpawn.sObjectInfo.pcState, &CharState, sizeof(CharState));
	charSpawn.sObjectInfo.pcState.sCharStateBase.byStateID = CHARSTATE_SPAWNING;
	charSpawn.sObjectInfo.pcState.sCharStateBase.dwStateTime = (DWORD)time(NULL);
	charSpawn.sObjectInfo.pcState.sCharStateDetail.sCharStateSpawning.byTeleportType = TELEPORT_TYPE_GAME_IN;
	charSpawn.sObjectInfo.pcState.sCharStateBase.dwConditionFlag = 0;
	charSpawn.sObjectInfo.pcState.sCharStateBase.bFightMode = false;
	charSpawn.sObjectInfo.pcState.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = ASPECTSTATE_INVALID;
	charSpawn.sObjectInfo.pcState.sCharStateBase.aspectState.sAspectStateDetail.sGreatNamek.bySourceGrade = 0;
	charSpawn.sObjectInfo.pcState.sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;
	charSpawn.sObjectInfo.pcState.sCharStateBase.aspectState.sAspectStateDetail.sPureMajin.bySourceGrade = 0;
	charSpawn.sObjectInfo.pcState.sCharStateBase.aspectState.sAspectStateDetail.sSuperSaiyan.bySourceGrade = 0;
	charSpawn.sObjectInfo.pcState.sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = 0;

	for (int i = 0; i < EQUIP_SLOT_TYPE_COUNT; i++)
	{
		charSpawn.sObjectInfo.pcBrief.sItemBrief[i].tblidx = INVALID_ITEMID;
	}

	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		int slot = ItemProfile[i].byPos;
		if (ItemProfile[i].byPlace == CONTAINER_TYPE_EQUIP &&
			((slot >= EQUIP_SLOT_TYPE_FIRST) && (slot <= EQUIP_SLOT_TYPE_LAST)))
		{
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].tblidx = ItemProfile[i].tblidx;
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].byBattleAttribute = ItemProfile[i].byBattleAttribute;
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].byGrade = ItemProfile[i].byGrade;
			memcpy(charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].aOptionTblidx, ItemProfile[i].aOptionTblidx, 2);
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].byRank = ItemProfile[i].byRank;
		}
	}
	return charSpawn;
}

