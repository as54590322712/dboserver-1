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
}

int	GameClient::OnAccept()
{
	return 0;
}

void GameClient::OnClose()
{
	if (goCharServer) pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '2' WHERE `ID` = '%d';", AccountID);
	else pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '0' WHERE `ID` = '%d';", AccountID);
}

int GameClient::OnDispatch(Packet* pPacket)
{
	PacketControl(pPacket);
	//	return OnDispatch(pPacket);
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

int GameClient::LoadItemData()
{
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
		pServer->ServerDB->Fetch();
		worldInfo.tblidx = pServer->ServerDB->getInt("worldTblidx");
		worldInfo.worldID = pServer->ServerDB->getInt("worldId");
		worldInfo.hTriggerObjectOffset = 100000; // WHAT IS THIS??
		worldInfo.sRuleInfo.byRuleType = GAMERULE_NORMAL;
	}
}

void GameClient::CalculateAtributes(PCData* pcdata)
{
	PcProfile.avatarAttribute.wBaseMaxEP += (pcdata->Level_Up_EP * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseMaxLP += (pcdata->Level_Up_LP * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseMaxRP += (pcdata->Level_Up_RP * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseStr += (BYTE)(pcdata->Level_Up_Str * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseDex += (BYTE)(pcdata->Level_Up_Dex * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseFoc += (BYTE)(pcdata->Level_Up_Foc * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseEng += (BYTE)(pcdata->Level_Up_Eng * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseCon += (BYTE)(pcdata->Level_Up_Con * PcProfile.byLevel);
	PcProfile.avatarAttribute.byBaseSol += (BYTE)(pcdata->Level_Up_Sol * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBasePhysicalOffence += (pcdata->Level_Up_Physical_Offence * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBasePhysicalDefence += (pcdata->Level_Up_Physical_Defence * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseEnergyOffence += (pcdata->Level_Up_Energy_Offence * PcProfile.byLevel);
	PcProfile.avatarAttribute.wBaseEnergyDefence += (pcdata->Level_Up_Energy_Defence * PcProfile.byLevel);

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
		pServer->ServerDB->Fetch();
		int Race = pServer->ServerDB->getInt("Race");
		int Class = pServer->ServerDB->getInt("Class");
		int Gender = pServer->ServerDB->getInt("Gender");
		PCData pcdata = pServer->pcTblData->GetData(Race,Class,Gender);
		Logger::Log("Loaded PC TblInfo: Idx(%u) Race(%u) Class(%u) Gender(%u)\n", pcdata.TblIndex, pcdata.Race, pcdata.Class, pcdata.Gender);
		memset(&PcProfile, 0, sizeof(PcProfile));
		memcpy(PcProfile.awchName, charToWChar(pServer->ServerDB->getString("Name")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
		memcpy(this->charName, charToWChar(pServer->ServerDB->getString("Name")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
		PcProfile.tblidx = pcdata.TblIndex;
		PcProfile.charId = pServer->ServerDB->getInt("ID");
		this->isGameMaster = PcProfile.bIsGameMaster = pServer->ServerDB->getBoolean("IsGameMaster");
		PcProfile.byLevel = pServer->ServerDB->getInt("Level");
		PcProfile.dwCurExp = pServer->ServerDB->getInt("CurExp");
		PcProfile.bIsAdult = pServer->ServerDB->getBoolean("Adult");
		PcProfile.dwMaxExpInThisLevel = 100;
		PcProfile.dwTutorialHint = pServer->ServerDB->getInt("TutorialHint");
		PcProfile.wCurEP = pServer->ServerDB->getInt("CurEP");;
		PcProfile.wCurLP = pServer->ServerDB->getInt("CurLP");;
		PcProfile.wCurRP = pcdata.Basic_RP;
		PcProfile.dwZenny = pServer->ServerDB->getInt("Money");
		PcProfile.sMarking.byCode = INVALID_MARKING_TYPE;

		PcProfile.avatarAttribute.wBaseMaxEP = pServer->ServerDB->getInt("MaxEP");
		PcProfile.avatarAttribute.wBaseMaxLP = pServer->ServerDB->getInt("MaxLP");
		PcProfile.avatarAttribute.wBaseMaxRP = pcdata.Basic_RP;
		PcProfile.avatarAttribute.byBaseStr = pcdata.Str;
		PcProfile.avatarAttribute.byBaseFoc = pcdata.Foc;
		PcProfile.avatarAttribute.byBaseSol = pcdata.Sol;
		PcProfile.avatarAttribute.byBaseDex = pcdata.Dex;
		PcProfile.avatarAttribute.byBaseCon = pcdata.Con;
		PcProfile.avatarAttribute.byBaseEng = pcdata.Eng;
		PcProfile.avatarAttribute.fBaseAttackRange = pcdata.Attack_Range;
		PcProfile.avatarAttribute.wBaseAttackRate = pcdata.Attack_Rate;
		PcProfile.avatarAttribute.wBaseAttackSpeedRate = pcdata.Attack_Speed_Rate;
		PcProfile.avatarAttribute.wBaseBlockRate = pcdata.Block_Rate;
		PcProfile.avatarAttribute.wBaseCurseSuccessRate = pcdata.Curse_Success_Rate;
		PcProfile.avatarAttribute.wBaseCurseToleranceRate = pcdata.Curse_Tolerance_Rate;
		PcProfile.avatarAttribute.wBaseDodgeRate = pcdata.Dodge_Rate;
		PcProfile.avatarAttribute.fLastRunSpeed = (PcProfile.bIsAdult) ? pcdata.Adult_Run_Speed : pcdata.Child_Run_Speed;
		CalculateAtributes(&pcdata);

		PcProfile.sPcShape.byFace = pServer->ServerDB->getInt("Face");
		PcProfile.sPcShape.byHair = pServer->ServerDB->getInt("Hair");
		PcProfile.sPcShape.byHairColor = pServer->ServerDB->getInt("HairColor");
		PcProfile.sPcShape.bySkinColor = pServer->ServerDB->getInt("SkinColor");

		memset(&CharState, 0, sizeof(CharState));
		CharState.sCharStateBase.dwConditionFlag = 0;
		CharState.sCharStateBase.bFightMode = false;
		CharState.sCharStateBase.byStateID = 0;
		CharState.sCharStateBase.dwStateTime = time(NULL);
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
	charSpawn.sObjectInfo.pcState.sCharStateBase.dwStateTime = time(NULL);
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
		memset(&charSpawn.sObjectInfo.pcBrief.sItemBrief[i], 0xFF, sizeof(sITEM_BRIEF));
	}

	for (int i = 0; i < NTL_MAX_COUNT_USER_HAVE_INVEN_ITEM; i++)
	{
		int slot = ItemProfile[i].byPos;
		if ((slot >= EQUIP_SLOT_TYPE_FIRST) && (slot <= EQUIP_SLOT_TYPE_LAST))
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

