#include "CharacterProfile.h"
#include "GameNetwork.h"

CharacterProfile::CharacterProfile()
{
	this->pServer = (GameServer*)_GetApp();
}

void CharacterProfile::Init()
{
	hSerialID = pServer->AcquireSerialID();
	byServerID = pServer->ServerID;
	byChannelID = pServer->ChannelID;
	memset(&sPcProfile, 0, sizeof(sPC_PROFILE));
	memset(&sCharState, 0, sizeof(sCHARSTATE));
	memset(&sWorldInfo, 0, sizeof(sWORLD_INFO));
}

CharacterProfile::~CharacterProfile()
{
	this->pServer = NULL;
}

void CharacterProfile::GetItemBrief(sITEM_BRIEF& sBrief, HOBJECT hItem)
{
	if (hItem == INVALID_HOBJECT)
	{
		sBrief.tblidx = INVALID_ITEMID;
	}
	else
	{
		for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
		{
			if (asItemProfile[i].handle == hItem)
			{
				sBrief.tblidx = asItemProfile[i].tblidx;
				sBrief.byBattleAttribute = asItemProfile[i].byBattleAttribute;
				sBrief.byGrade = asItemProfile[i].byGrade;
				sBrief.byRank = asItemProfile[i].byRank;
				sBrief.aOptionTblidx[0] = asItemProfile[i].aOptionTblidx[0];
				sBrief.aOptionTblidx[1] = asItemProfile[i].aOptionTblidx[1];
			}
		}
	}
}

void CharacterProfile::UpdateItemInventoryPosition(HOBJECT hItem, BYTE byPlace, BYTE byPos)
{
	pServer->ServerDB->ExecuteQuery("UPDATE `inventory` SET `Place` = '%d', `Slot` = '%d' WHERE `ID` = '%u' AND `CharID` = '%u';",
		byPlace, byPos, hItem, hCharID);
	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
	{
		if (asItemProfile[i].handle == hItem)
		{
			asItemProfile[i].byPlace = byPlace;
			asItemProfile[i].byPos = byPos;
		}
	}
}

HOBJECT CharacterProfile::GetInventoryItemSerialID(BYTE byPlace, BYTE byPos)
{
	HOBJECT ret = INVALID_HOBJECT;
	if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM `inventory` WHERE `Place` = '%d' AND `Slot` = '%d' AND `CharID` = '%u';",
		byPlace, byPos, hCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			ret = pServer->ServerDB->getInt("ID");
		}
	}
	return ret;
}

TBLIDX CharacterProfile::GetInventoryItemID(BYTE byPlace, BYTE byPos)
{
	TBLIDX ret = INVALID_TBLIDX;
	if (pServer->ServerDB->ExecuteSelect("SELECT `ItemID` FROM `inventory` WHERE `Place` = '%d' AND `Slot` = '%d' AND `CharID` = '%u';",
		byPlace, byPos, hCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			ret = pServer->ServerDB->getInt("ItemID");
		}
	}
	return ret;
}

void CharacterProfile::InsertOnlineData()
{
	pServer->ServerDB->ExecuteQuery("CALL `spInsertOnline`('%u','%u','%u','%u','%u');",
		AccountID, hCharID, byServerID, byChannelID, hSerialID);
}

void CharacterProfile::RemoveOnlineData()
{
	pServer->ServerDB->ExecuteQuery("CALL `spDeleteOnline`('%u','%u');",
		AccountID, hCharID);
}

int CharacterProfile::LoadQuickslotData()
{
	int count = 0;
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `quickslot` WHERE `CharID`='%u';", this->hCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			asQuickSlotData[count].tblidx = pServer->ServerDB->getInt("TblID");
			asQuickSlotData[count].bySlot = pServer->ServerDB->getInt("Slot");
			asQuickSlotData[count].byType = pServer->ServerDB->getInt("Type");
			asQuickSlotData[count].hItem = pServer->ServerDB->getInt("Item");
			count++;
		}
	}
	return count;
}

int CharacterProfile::LoadSkillData()
{
	int count = 0;
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `skills` WHERE `CharID`='%u';", this->hCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			asSkillInfo[count].tblidx = pServer->ServerDB->getInt("SkillID");
			asSkillInfo[count].bySlotId = pServer->ServerDB->getInt("Slot");
			asSkillInfo[count].bIsRpBonusAuto = pServer->ServerDB->getBoolean("IsRpBonusAuto");
			asSkillInfo[count].byRpBonusType = pServer->ServerDB->getInt("RpBonusType");
			asSkillInfo[count].dwTimeRemaining = pServer->ServerDB->getInt("RemainSec");
			asSkillInfo[count].nExp = pServer->ServerDB->getInt("Exp");
			count++;
		}
	}
	return count;
}

sGU_ITEM_CREATE CharacterProfile::InsertNextBagSlot(ITEMID item, BYTE qtd)
{
	sGU_ITEM_CREATE itemdata;
	memset(&itemdata, 0, sizeof(itemdata));
	HOBJECT hItem = INVALID_HOBJECT;
	int lastbagslot = 0;
	int lastbag = 1;
	bool found = false;
	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
	{
		if (asItemProfile[i].byPlace >= CONTAINER_TYPE_BAG_FIRST && asItemProfile[i].byPlace <= CONTAINER_TYPE_BAG_LAST)
		{
			if (lastbagslot < asItemProfile[i].byPos)
			{
				lastbagslot = asItemProfile[i].byPos;
				lastbag = asItemProfile[i].byPlace;
			}
		}

		if (asItemProfile[i].handle == INVALID_HOBJECT && asItemProfile[i].tblidx == INVALID_TBLIDX)
		{
			if (lastbagslot != 0) lastbagslot++;
			if (pServer->ServerDB->ExecuteSp("CALL `spInsertItem`('%u','%u','%d','%d','%d','1','100','0','0','0','0','','0','0','0');",
				item, hCharID, lastbag, lastbagslot, qtd))
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
			itemdata.sItemData.charId = hCharID;
			itemdata.sItemData.itemNo = item;
			itemdata.sItemData.byCurrentDurability = 100;
			itemdata.sItemData.byPlace = lastbag;
			itemdata.sItemData.byPosition = lastbagslot;
			itemdata.sItemData.byStackcount = qtd;
			itemdata.sItemData.byRank = 1;

			asItemProfile[i].handle = itemdata.sItemData.itemId;
			asItemProfile[i].tblidx = item;
			asItemProfile[i].byCurDur = itemdata.sItemData.byCurrentDurability;
			asItemProfile[i].byPlace = itemdata.sItemData.byPlace;
			asItemProfile[i].byPos = itemdata.sItemData.byPosition;
			asItemProfile[i].byStackcount = itemdata.sItemData.byStackcount;
			asItemProfile[i].byRank = itemdata.sItemData.byRank;
			break;
		}
	}
	return itemdata;
}

int CharacterProfile::LoadItemData()
{
	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; ++i)
	{
		asItemProfile[i].handle = INVALID_HOBJECT;
		asItemProfile[i].tblidx = INVALID_TBLIDX;
	}
	int count = 0;
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `inventory` WHERE `CharID`='%u';", hCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			asItemProfile[count].handle = pServer->ServerDB->getInt("ID");
			asItemProfile[count].tblidx = pServer->ServerDB->getInt("ItemID");
			asItemProfile[count].byPlace = pServer->ServerDB->getInt("Place");
			asItemProfile[count].byPos = pServer->ServerDB->getInt("Slot");
			asItemProfile[count].byStackcount = pServer->ServerDB->getInt("Stack");
			asItemProfile[count].byRank = pServer->ServerDB->getInt("Rank");
			asItemProfile[count].byCurDur = pServer->ServerDB->getInt("CurDur");
			asItemProfile[count].bNeedToIdentify = pServer->ServerDB->getBoolean("NeedToIdentify");
			asItemProfile[count].byGrade = pServer->ServerDB->getInt("Grade");
			asItemProfile[count].byBattleAttribute = pServer->ServerDB->getInt("BattleAttribute");
			asItemProfile[count].byRestrictType = pServer->ServerDB->getInt("RestrictType");
			memcpy(asItemProfile[count].awchMaker, charToWChar(pServer->ServerDB->getString("Maker")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
			asItemProfile[count].aOptionTblidx[0] = pServer->ServerDB->getInt("Opt1");
			asItemProfile[count].aOptionTblidx[1] = pServer->ServerDB->getInt("Opt2");
			asItemProfile[count].byDurationType = pServer->ServerDB->getInt("DurationType");
			asItemProfile[count].nUseStartTime = pServer->ServerDB->getInt("UseStartTime");
			asItemProfile[count].nUseEndTime = pServer->ServerDB->getInt("UseEndTime");
			count++;
		}
	}
	return count;
}

void CharacterProfile::UpdatePositions(sVECTOR2 Dir, sVECTOR3 Loc)
{
	sCharState.sCharStateBase.vCurLoc = Loc;
	sCharState.sCharStateBase.vCurDir.x = Dir.x;
	sCharState.sCharStateBase.vCurDir.y = 0.0f;
	sCharState.sCharStateBase.vCurDir.z = Dir.z;
	pServer->ServerDB->ExecuteQuery("CALL `spUpdatePosition`('%u', '%f', '%f', '%f');", hCharID, Loc.x, Loc.y, Loc.z);
	pServer->ServerDB->ExecuteQuery("CALL `spUpdateDirection`('%u', '%f', '%f', '%f');", hCharID, Dir.x, 0.0f, Dir.z);
}

void CharacterProfile::UpdatePositions(sVECTOR3 Dir, sVECTOR3 Loc)
{
	sCharState.sCharStateBase.vCurLoc = Loc;
	sCharState.sCharStateBase.vCurDir = Dir;
	pServer->ServerDB->ExecuteQuery("CALL `spUpdatePosition`('%u', '%f', '%f', '%f');", hCharID, Loc.x, Loc.y, Loc.z);
	pServer->ServerDB->ExecuteQuery("CALL `spUpdateDirection`('%u', '%f', '%f', '%f');", hCharID, Dir.x, Dir.y, Dir.z);
}

void CharacterProfile::LoadWorldInfoData()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ID`='%d';", AccountID, hCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			sWorldInfo.tblidx = pServer->ServerDB->getInt("worldTblidx");
			sWorldInfo.worldID = pServer->ServerDB->getInt("worldId");
			sWorldInfo.hTriggerObjectOffset = 100000; // WHAT IS THIS??
			sWorldInfo.sRuleInfo.byRuleType = GAMERULE_NORMAL;
		}
	}
}

void CharacterProfile::CalculateAtributes(sPC_TBLDAT* pcdata)
{
	sPcProfile.avatarAttribute.wBaseMaxEP += (pcdata->byLevel_Up_EP * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.wBaseMaxLP += (pcdata->byLevel_Up_LP * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.wBaseMaxRP += (pcdata->byLevel_Up_RP * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.byBaseStr += (BYTE)(pcdata->fLevel_Up_Str * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.byBaseDex += (BYTE)(pcdata->fLevel_Up_Dex * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.byBaseFoc += (BYTE)(pcdata->fLevel_Up_Foc * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.byBaseEng += (BYTE)(pcdata->fLevel_Up_Eng * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.byBaseCon += (BYTE)(pcdata->fLevel_Up_Con * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.byBaseSol += (BYTE)(pcdata->fLevel_Up_Sol * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.wBasePhysicalOffence += (pcdata->byLevel_Up_Physical_Offence * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.wBasePhysicalDefence += (pcdata->byLevel_Up_Physical_Defence * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.wBaseEnergyOffence += (pcdata->byLevel_Up_Energy_Offence * sPcProfile.byLevel);
	sPcProfile.avatarAttribute.wBaseEnergyDefence += (pcdata->byLevel_Up_Energy_Defence * sPcProfile.byLevel);

	sPcProfile.avatarAttribute.wLastMaxEP = sPcProfile.avatarAttribute.wBaseMaxEP;
	sPcProfile.avatarAttribute.wLastMaxLP = sPcProfile.avatarAttribute.wBaseMaxLP;
	sPcProfile.avatarAttribute.wLastMaxRP = sPcProfile.avatarAttribute.wBaseMaxRP;
	sPcProfile.avatarAttribute.byLastStr = sPcProfile.avatarAttribute.byBaseStr;
	sPcProfile.avatarAttribute.byLastDex = sPcProfile.avatarAttribute.byBaseDex;
	sPcProfile.avatarAttribute.byLastFoc = sPcProfile.avatarAttribute.byBaseFoc;
	sPcProfile.avatarAttribute.byLastEng = sPcProfile.avatarAttribute.byBaseEng;
	sPcProfile.avatarAttribute.byLastCon = sPcProfile.avatarAttribute.byBaseCon;
	sPcProfile.avatarAttribute.byLastSol = sPcProfile.avatarAttribute.byBaseSol;
	sPcProfile.avatarAttribute.wLastPhysicalOffence = sPcProfile.avatarAttribute.wBasePhysicalOffence;
	sPcProfile.avatarAttribute.wLastPhysicalDefence = sPcProfile.avatarAttribute.wBasePhysicalDefence;
	sPcProfile.avatarAttribute.wLastEnergyOffence = sPcProfile.avatarAttribute.wBaseEnergyOffence;
	sPcProfile.avatarAttribute.wLastEnergyDefence = sPcProfile.avatarAttribute.wBaseEnergyDefence;
}

void CharacterProfile::LoadCharacterData()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%u' AND `ID`='%u';", AccountID, hCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			byRace = pServer->ServerDB->getInt("Race");
			byClass = pServer->ServerDB->getInt("Class");
			byGender = pServer->ServerDB->getInt("Gender");
			sPC_TBLDAT pcdata = *(sPC_TBLDAT*)pServer->GetTableContainer()->GetPcTable()->GetPcTbldat(byRace, byClass, byGender);
			Logger::Log("Loaded PC TblInfo: Idx(%u) Race(%u) Class(%u) Gender(%u)\n", pcdata.tblidx, pcdata.byRace, pcdata.byClass, pcdata.byGender);
			memset(&sPcProfile, 0, sizeof(sPcProfile));
			memcpy(sPcProfile.awchName, charToWChar(pServer->ServerDB->getString("Name")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
			memcpy(wszCharName, charToWChar(pServer->ServerDB->getString("Name")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
			sPcProfile.tblidx = pcdata.tblidx;
			sPcProfile.charId = pServer->ServerDB->getInt("ID");
			this->bIsGameMaster = sPcProfile.bIsGameMaster = pServer->ServerDB->getBoolean("IsGameMaster");
			sPcProfile.byLevel = pServer->ServerDB->getInt("Level");
			sPcProfile.dwCurExp = pServer->ServerDB->getInt("CurExp");
			sPcProfile.bIsAdult = pServer->ServerDB->getBoolean("Adult");
			sPcProfile.dwMaxExpInThisLevel = 100;
			sPcProfile.dwTutorialHint = pServer->ServerDB->getInt("TutorialHint");
			sPcProfile.wCurEP = pServer->ServerDB->getInt("CurEP");;
			sPcProfile.wCurLP = pServer->ServerDB->getInt("CurLP");;
			sPcProfile.wCurRP = pcdata.wBasic_RP;
			sPcProfile.dwZenny = pServer->ServerDB->getInt("Money");
			sPcProfile.sMarking.byCode = INVALID_MARKING_TYPE;

			sPcProfile.avatarAttribute.wBaseMaxEP = pServer->ServerDB->getInt("MaxEP");
			sPcProfile.avatarAttribute.wBaseMaxLP = pServer->ServerDB->getInt("MaxLP");
			sPcProfile.avatarAttribute.wBaseMaxRP = pcdata.wBasic_RP;
			sPcProfile.avatarAttribute.byBaseStr = pcdata.byStr;
			sPcProfile.avatarAttribute.byBaseFoc = pcdata.byFoc;
			sPcProfile.avatarAttribute.byBaseSol = pcdata.bySol;
			sPcProfile.avatarAttribute.byBaseDex = pcdata.byDex;
			sPcProfile.avatarAttribute.byBaseCon = pcdata.byCon;
			sPcProfile.avatarAttribute.byBaseEng = pcdata.byEng;
			sPcProfile.avatarAttribute.fBaseAttackRange = pcdata.fAttack_Range;
			sPcProfile.avatarAttribute.wBaseAttackRate = pcdata.wAttack_Rate;
			sPcProfile.avatarAttribute.wBaseAttackSpeedRate = pcdata.wAttack_Speed_Rate;
			sPcProfile.avatarAttribute.wBaseBlockRate = pcdata.wBlock_Rate;
			sPcProfile.avatarAttribute.wBaseCurseSuccessRate = pcdata.wCurse_Success_Rate;
			sPcProfile.avatarAttribute.wBaseCurseToleranceRate = pcdata.wCurse_Tolerance_Rate;
			sPcProfile.avatarAttribute.wBaseDodgeRate = pcdata.wDodge_Rate;
			sPcProfile.avatarAttribute.fLastRunSpeed = (sPcProfile.bIsAdult) ? pcdata.fAdult_Run_Speed : pcdata.fChild_Run_Speed;
			CalculateAtributes(&pcdata);

			sPcProfile.sPcShape.byFace = pServer->ServerDB->getInt("Face");
			sPcProfile.sPcShape.byHair = pServer->ServerDB->getInt("Hair");
			sPcProfile.sPcShape.byHairColor = pServer->ServerDB->getInt("HairColor");
			sPcProfile.sPcShape.bySkinColor = pServer->ServerDB->getInt("SkinColor");

			memset(&sCharState, 0, sizeof(sCharState));
			sCharState.sCharStateBase.dwConditionFlag = 0;
			sCharState.sCharStateBase.bFightMode = false;
			sCharState.sCharStateBase.byStateID = 0;
			sCharState.sCharStateBase.dwStateTime = (DWORD)time(NULL);
			sCharState.sCharStateBase.aspectState.sAspectStateBase.byAspectStateId = ASPECTSTATE_INVALID;
			sCharState.sCharStateBase.aspectState.sAspectStateDetail.sGreatNamek.bySourceGrade = 0;
			sCharState.sCharStateBase.aspectState.sAspectStateDetail.sKaioken.bySourceGrade = 0;
			sCharState.sCharStateBase.aspectState.sAspectStateDetail.sPureMajin.bySourceGrade = 0;
			sCharState.sCharStateBase.aspectState.sAspectStateDetail.sSuperSaiyan.bySourceGrade = 0;
			sCharState.sCharStateBase.aspectState.sAspectStateDetail.sVehicle.idVehicleTblidx = 0;

			sCharState.sCharStateBase.vCurLoc.x = pServer->ServerDB->getFloat("PositionX");
			sCharState.sCharStateBase.vCurLoc.y = pServer->ServerDB->getFloat("PositionY");
			sCharState.sCharStateBase.vCurLoc.z = pServer->ServerDB->getFloat("PositionZ");
			sCharState.sCharStateBase.vCurDir.x = pServer->ServerDB->getFloat("DirectionX");
			sCharState.sCharStateBase.vCurDir.y = pServer->ServerDB->getFloat("DirectionY");
			sCharState.sCharStateBase.vCurDir.z = pServer->ServerDB->getFloat("DirectionZ");
		}
	}
}

ObjectInfo CharacterProfile::GetCharSpawnData()
{
	sGU_OBJECT_CREATE charSpawn;
	memset(&charSpawn, 0, sizeof(charSpawn));
	charSpawn.wOpCode = GU_OBJECT_CREATE;
	charSpawn.handle = GetSerialID();
	charSpawn.sObjectInfo.objType = OBJTYPE_PC;
	charSpawn.sObjectInfo.pcBrief.charId = hCharID;
	charSpawn.sObjectInfo.pcBrief.tblidx = sPcProfile.tblidx;
	charSpawn.sObjectInfo.pcBrief.byLevel = sPcProfile.byLevel;
	charSpawn.sObjectInfo.pcBrief.wAttackSpeedRate = sPcProfile.avatarAttribute.wLastAttackSpeedRate;
	charSpawn.sObjectInfo.pcBrief.wCurEP = sPcProfile.wCurEP;
	charSpawn.sObjectInfo.pcBrief.wCurLP = sPcProfile.wCurLP;
	charSpawn.sObjectInfo.pcBrief.wMaxEP = sPcProfile.avatarAttribute.wLastMaxEP;
	charSpawn.sObjectInfo.pcBrief.wMaxLP = sPcProfile.avatarAttribute.wLastMaxLP;
	charSpawn.sObjectInfo.pcBrief.fSpeed = sPcProfile.avatarAttribute.fLastRunSpeed;
	memcpy(charSpawn.sObjectInfo.pcBrief.awchName, sPcProfile.awchName, NTL_MAX_SIZE_CHAR_NAME_UNICODE);
	charSpawn.sObjectInfo.pcBrief.sMarking.byCode = INVALID_MARKING_TYPE;
	charSpawn.sObjectInfo.pcBrief.bIsAdult = sPcProfile.bIsAdult;
	memcpy(&charSpawn.sObjectInfo.pcBrief.sPcShape, &sPcProfile.sPcShape, sizeof(sPcProfile.sPcShape));
	memcpy(&charSpawn.sObjectInfo.pcState, &sCharState, sizeof(sCharState));
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
		int slot = asItemProfile[i].byPos;
		if (asItemProfile[i].byPlace == CONTAINER_TYPE_EQUIP &&
			((slot >= EQUIP_SLOT_TYPE_FIRST) && (slot <= EQUIP_SLOT_TYPE_LAST)))
		{
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].tblidx = asItemProfile[i].tblidx;
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].byBattleAttribute = asItemProfile[i].byBattleAttribute;
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].byGrade = asItemProfile[i].byGrade;
			memcpy(charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].aOptionTblidx, asItemProfile[i].aOptionTblidx, 2);
			charSpawn.sObjectInfo.pcBrief.sItemBrief[slot].byRank = asItemProfile[i].byRank;
		}
	}
	ObjectInfo obj;
	obj.worldTblIdx = sWorldInfo.tblidx;
	obj.ObjData = charSpawn;
	return obj;
}