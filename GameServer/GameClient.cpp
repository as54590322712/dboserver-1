#include "GameNetwork.h"

GameClient::GameClient()
{
}

GameClient::~GameClient()
{
}

unsigned int GameClient::GetPCTblidx(BYTE Race, BYTE Gender, BYTE Class)
{
	if (pServer->ServerDB->ExecuteSelect("SELECT `Tblidx` FROM `tbl_pcdata` WHERE `Race` = '%d' AND `Gender` = '%d' AND `Class` = '%d';", Race, Gender, Class))
	{
		pServer->ServerDB->Fetch();
		return pServer->ServerDB->getInt("Tblidx");
	}
	return 0xFFFFFFFF;
}

void GameClient::LoadWorldInfoData(sGU_AVATAR_WORLD_INFO* data)
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ID`='%d';", this->AccountID, this->CurrCharID))
	{
		while (pServer->ServerDB->Fetch())
		{
			data->worldInfo.tblidx = pServer->ServerDB->getInt("worldTblidx");
			data->worldInfo.worldID = pServer->ServerDB->getInt("worldId");
			data->worldInfo.TriggerObjectOffset = 100000; // WHAT IS THIS??
			data->worldInfo.RuleInfo.RuleType = GAMERULE_NORMAL;
			data->DojoCount = 0;
			data->CurLoc.x = pServer->ServerDB->getDouble("PositionX") + (float)(rand() % 5);
			data->CurLoc.y = pServer->ServerDB->getDouble("PositionY") + (float)(rand() % 5);
			data->CurLoc.z = pServer->ServerDB->getDouble("positionZ") + (float)(rand() % 5);
			data->CurDir.x = pServer->ServerDB->getDouble("DirectionX");
			data->CurDir.y = pServer->ServerDB->getDouble("DirectionY");
			data->CurDir.z = pServer->ServerDB->getDouble("DirectionZ");
		}
	}
}

void GameClient::LoadSendCharacterData(sGU_AVATAR_CHAR_INFO* data)
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ID`='%d';", this->AccountID, this->CurrCharID))
	{
		pServer->ServerDB->Fetch();
		memcpy(data->PcProfile.Name, charToWChar(pServer->ServerDB->getString("Name").c_str()), MAX_CHARNAME_SIZE);
		data->PcProfile.charId = pServer->ServerDB->getInt("ID");
		data->PcProfile.IsGameMaster = false;
		data->PcProfile.Level = 1;
		data->PcProfile.CurExp = 50;
		data->PcProfile.IsAdult = true;
		data->PcProfile.MaxExpInThisLevel = 100;
		data->PcProfile.TutorialHint = 1;
		data->PcProfile.CurEP = 10000;
		data->PcProfile.CurLP = 10000;
		data->PcProfile.CurRP = 100;
		data->PcProfile.Zenny = 100000000;

		data->PcProfile.avatarAttribute.BaseMaxEP = 10000;
		data->PcProfile.avatarAttribute.LastMaxEP = 10000;
		data->PcProfile.avatarAttribute.BaseMaxLP = 10000;
		data->PcProfile.avatarAttribute.LastMaxLP = 10000;
		data->PcProfile.avatarAttribute.BaseMaxRP = 100;
		data->PcProfile.avatarAttribute.LastMaxRP = 100;
		data->PcProfile.avatarAttribute.BaseAttackRange = 10.0f;
		data->PcProfile.avatarAttribute.LastAttackRange = 10.0f;
		data->PcProfile.avatarAttribute.BaseAttackRate = 10;
		data->PcProfile.avatarAttribute.LastAttackRate = 10;
		data->PcProfile.avatarAttribute.BaseAttackSpeedRate = 10;
		data->PcProfile.avatarAttribute.LastAttackSpeedRate = 10;
		data->PcProfile.avatarAttribute.BaseBlockRate = 10;
		data->PcProfile.avatarAttribute.LastBlockRate = 10;
		data->PcProfile.avatarAttribute.BaseCon = 255;
		data->PcProfile.avatarAttribute.LastCon = 255;
		data->PcProfile.avatarAttribute.BaseCurseSuccessRate = 10;
		data->PcProfile.avatarAttribute.LastCurseSuccessRate = 10;
		data->PcProfile.avatarAttribute.BaseCurseToleranceRate = 10;
		data->PcProfile.avatarAttribute.LastCurseToleranceRate = 10;
		data->PcProfile.avatarAttribute.BaseDex = 255;
		data->PcProfile.avatarAttribute.LastDex = 255;
		data->PcProfile.avatarAttribute.BaseDodgeRate = 10;
		data->PcProfile.avatarAttribute.LastDodgeRate = 10;
		data->PcProfile.avatarAttribute.BaseEnergyCriticalRate = 10;
		data->PcProfile.avatarAttribute.LastEnergyCriticalRate = 10;
		data->PcProfile.avatarAttribute.BaseEnergyDefence = 10;
		data->PcProfile.avatarAttribute.LastEnergyDefence = 10;
		data->PcProfile.avatarAttribute.BaseEnergyOffence = 10;
		data->PcProfile.avatarAttribute.LastEnergyOffence = 10;
		data->PcProfile.avatarAttribute.BaseEng = 255;
		data->PcProfile.avatarAttribute.LastEng = 255;
		data->PcProfile.avatarAttribute.BaseEpBattleRegen = 10;
		data->PcProfile.avatarAttribute.LastEpBattleRegen = 10;
		data->PcProfile.avatarAttribute.BaseEpRegen = 10;
		data->PcProfile.avatarAttribute.LastEpRegen = 10;
		data->PcProfile.avatarAttribute.BaseEpSitdownRegen = 10;
		data->PcProfile.avatarAttribute.LastEpSitdownRegen = 10;
		data->PcProfile.avatarAttribute.BaseFoc = 255;
		data->PcProfile.avatarAttribute.LastFoc = 255;
		data->PcProfile.avatarAttribute.BaseLpBattleRegen = 10;
		data->PcProfile.avatarAttribute.LastLpBattleRegen = 10;
		data->PcProfile.avatarAttribute.BaseLpRegen = 10;
		data->PcProfile.avatarAttribute.LastLpRegen = 10;
		data->PcProfile.avatarAttribute.BaseLpSitdownRegen = 10;
		data->PcProfile.avatarAttribute.LastLpSitdownRegen = 10;
		data->PcProfile.avatarAttribute.BasePhysicalCriticalRate = 10;
		data->PcProfile.avatarAttribute.LastPhysicalCriticalRate = 10;
		data->PcProfile.avatarAttribute.BasePhysicalDefence = 10;
		data->PcProfile.avatarAttribute.LastPhysicalDefence = 10;
		data->PcProfile.avatarAttribute.BasePhysicalOffence = 10;
		data->PcProfile.avatarAttribute.LastPhysicalOffence = 10;
		data->PcProfile.avatarAttribute.BaseRpRegen = 10;
		data->PcProfile.avatarAttribute.LastRpRegen = 10;
		data->PcProfile.avatarAttribute.BaseSol = 255;
		data->PcProfile.avatarAttribute.LastSol = 255;
		data->PcProfile.avatarAttribute.BaseStr = 255;
		data->PcProfile.avatarAttribute.LastStr = 255;
		data->PcProfile.avatarAttribute.BleedingKeepTimeDown = 2;
		data->PcProfile.avatarAttribute.CandyKeepTimeDown = 3;
		data->PcProfile.avatarAttribute.CandyToleranceRate = 10;
		data->PcProfile.avatarAttribute.CastingTimeChangePercent = 100;
		data->PcProfile.avatarAttribute.ConfuseKeepTimeDown = 1;
		data->PcProfile.avatarAttribute.ConfuseToleranceRate = 100;
		data->PcProfile.avatarAttribute.CoolTimeChangePercent = 100;
		data->PcProfile.avatarAttribute.CriticalBlockSuccessRate = 100;
		data->PcProfile.avatarAttribute.CurseBlockModeSuccessRate = 100;
		data->PcProfile.avatarAttribute.DotTimeChangeAbsolute = 1;
		data->PcProfile.avatarAttribute.DotValueChangePercent = 1;
		data->PcProfile.avatarAttribute.EleganceDefence = 100;
		data->PcProfile.avatarAttribute.EleganceOffence = 100;
		data->PcProfile.avatarAttribute.EnergyCriticalDamageBonusRate = 100;
		data->PcProfile.avatarAttribute.FunnyDefence = 100;
		data->PcProfile.avatarAttribute.FunnyOffence = 100;
		data->PcProfile.avatarAttribute.GuardRate = 100;
		data->PcProfile.avatarAttribute.HonestDefence = 100;
		data->PcProfile.avatarAttribute.HonestOffence = 100;
		data->PcProfile.avatarAttribute.HtbBlockModeSuccessRate = 100;
		data->PcProfile.avatarAttribute.ItemUpgradeBonusRate = 100;
		data->PcProfile.avatarAttribute.ItemUpgradeBreakBonusRate = 0;
		data->PcProfile.avatarAttribute.KeepTimeChangePercent = 100;
		data->PcProfile.avatarAttribute.KnockdownBlockModeSuccessRate = 100;
		data->PcProfile.avatarAttribute.ParalyzeKeepTimeDown = 100;
		data->PcProfile.avatarAttribute.PhysicalCriticalDamageBonusRate = 100;
		data->PcProfile.avatarAttribute.PoisonKeepTimeDown = 100;
		data->PcProfile.avatarAttribute.RequiredEpChangePercent = 100;
		data->PcProfile.avatarAttribute.SitDownEpRegenBonusRate = 100;
		data->PcProfile.avatarAttribute.SitDownLpRegenBonusRate = 100;
		data->PcProfile.avatarAttribute.SkillDamageBlockModeSuccessRate = 100;
		data->PcProfile.avatarAttribute.StomachacheKeepTimeDown = 100;
		data->PcProfile.avatarAttribute.StoneKeepTimeDown = 100;
		data->PcProfile.avatarAttribute.StoneToleranceRate = 100;
		data->PcProfile.avatarAttribute.StrangeDefence = 100;
		data->PcProfile.avatarAttribute.StrangeOffence = 100;
		data->PcProfile.avatarAttribute.TerrorKeepTimeDown = 100;
		data->PcProfile.avatarAttribute.TerrorToleranceRate = 100;
		data->PcProfile.avatarAttribute.WildDefence = 100;
		data->PcProfile.avatarAttribute.WildOffence = 100;
		data->PcProfile.avatarAttribute.LastRunSpeed = 10.0f;

		data->PcProfile.CharShape.Face = pServer->ServerDB->getInt("Face");
		data->PcProfile.CharShape.Hair = pServer->ServerDB->getInt("Hair");
		data->PcProfile.CharShape.HairColor = pServer->ServerDB->getInt("HairColor");
		data->PcProfile.CharShape.SkinColor = pServer->ServerDB->getInt("SkinColor");

		data->CharState.CharStateBase.ConditionFlag = 0;
		data->CharState.CharStateBase.FightMode = 0;
		data->CharState.CharStateBase.StateID = 0;
		data->CharState.CharStateBase.StateTime = 0;
		data->CharState.CharStateBase.aspectState.AspectStateBase.AspectStateId = 255;
		data->CharState.CharStateBase.aspectState.AspectStateDetail.GreatNamek.SourceGrade = 0;
		data->CharState.CharStateBase.aspectState.AspectStateDetail.Kaioken.RepeatingCount = 0;
		data->CharState.CharStateBase.aspectState.AspectStateDetail.Kaioken.SourceGrade = 0;
		data->CharState.CharStateBase.aspectState.AspectStateDetail.PureMajin.SourceGrade = 0;
		data->CharState.CharStateBase.aspectState.AspectStateDetail.SuperSaiyan.SourceGrade = 0;
		data->CharState.CharStateBase.aspectState.AspectStateDetail.Vehicle.idVehicleTblidx = 0;
		data->CharState.CharStateBase.aspectState.AspectStateDetail.Vehicle.IsEngineOn = 0;

		data->CharState.CharStateBase.CurLoc.x = pServer->ServerDB->getDouble("PositionX");
		data->CharState.CharStateBase.CurLoc.y = pServer->ServerDB->getDouble("PositionY");
		data->CharState.CharStateBase.CurLoc.z = pServer->ServerDB->getDouble("PositionZ");
		data->CharState.CharStateBase.CurDir.x = pServer->ServerDB->getDouble("DirectionX");
		data->CharState.CharStateBase.CurDir.y = pServer->ServerDB->getDouble("DirectionY");
		data->CharState.CharStateBase.CurDir.z = pServer->ServerDB->getDouble("DirectionZ");

		data->CharStateSize = sizeof(CHARSTATE_BASE);
		data->PcProfile.tblidx = this->GetPCTblidx(pServer->ServerDB->getInt("Race"), pServer->ServerDB->getInt("Gender"), pServer->ServerDB->getInt("Class"));
	}
}

