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

void GameClient::LoadWorldInfoData()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ID`='%d';", this->AccountID, this->CurrCharID))
	{
		pServer->ServerDB->Fetch();
		worldInfo.tblidx = pServer->ServerDB->getInt("worldTblidx");
		worldInfo.worldID = pServer->ServerDB->getInt("worldId");
		worldInfo.TriggerObjectOffset = 100000; // WHAT IS THIS??
		worldInfo.RuleInfo.RuleType = GAMERULE_NORMAL;
		//data->CurLoc.x = pServer->ServerDB->getDouble("PositionX") + (float)(rand() % 5);
		//data->CurLoc.y = pServer->ServerDB->getDouble("PositionY") + (float)(rand() % 5);
		//data->CurLoc.z = pServer->ServerDB->getDouble("positionZ") + (float)(rand() % 5);
	}
}

void GameClient::LoadCharacterData()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ID`='%d';", AccountID, CurrCharID))
	{
		pServer->ServerDB->Fetch();
		memset(&PcProfile, 0, sizeof(PcProfile));
		memcpy(PcProfile.Name, charToWChar(pServer->ServerDB->getString("Name")), MAX_CHARNAME_SIZE);
		PcProfile.charId = pServer->ServerDB->getInt("ID");
		PcProfile.IsGameMaster = false;
		PcProfile.Level = pServer->ServerDB->getInt("Level");
		PcProfile.CurExp = pServer->ServerDB->getInt("Exp");
		PcProfile.IsAdult = pServer->ServerDB->getBoolean("Adult");
		PcProfile.MaxExpInThisLevel = 100;
		PcProfile.TutorialHint = 1;
		PcProfile.CurEP = 10000;
		PcProfile.CurLP = 10000;
		PcProfile.CurRP = 100;
		PcProfile.Zenny = pServer->ServerDB->getInt("Money");

		PcProfile.avatarAttribute.BaseMaxEP = 10000;
		PcProfile.avatarAttribute.LastMaxEP = 10000;
		PcProfile.avatarAttribute.BaseMaxLP = 10000;
		PcProfile.avatarAttribute.LastMaxLP = 10000;
		PcProfile.avatarAttribute.BaseMaxRP = 100;
		PcProfile.avatarAttribute.LastMaxRP = 100;
		PcProfile.avatarAttribute.BaseAttackRange = 10.0f;
		PcProfile.avatarAttribute.LastAttackRange = 10.0f;
		PcProfile.avatarAttribute.BaseAttackRate = 10;
		PcProfile.avatarAttribute.LastAttackRate = 10;
		PcProfile.avatarAttribute.BaseAttackSpeedRate = 10;
		PcProfile.avatarAttribute.LastAttackSpeedRate = 10;
		PcProfile.avatarAttribute.BaseBlockRate = 10;
		PcProfile.avatarAttribute.LastBlockRate = 10;
		PcProfile.avatarAttribute.BaseCon = 255;
		PcProfile.avatarAttribute.LastCon = 255;
		PcProfile.avatarAttribute.BaseCurseSuccessRate = 10;
		PcProfile.avatarAttribute.LastCurseSuccessRate = 10;
		PcProfile.avatarAttribute.BaseCurseToleranceRate = 10;
		PcProfile.avatarAttribute.LastCurseToleranceRate = 10;
		PcProfile.avatarAttribute.BaseDex = 255;
		PcProfile.avatarAttribute.LastDex = 255;
		PcProfile.avatarAttribute.BaseDodgeRate = 10;
		PcProfile.avatarAttribute.LastDodgeRate = 10;
		PcProfile.avatarAttribute.BaseEnergyCriticalRate = 10;
		PcProfile.avatarAttribute.LastEnergyCriticalRate = 10;
		PcProfile.avatarAttribute.BaseEnergyDefence = 10;
		PcProfile.avatarAttribute.LastEnergyDefence = 10;
		PcProfile.avatarAttribute.BaseEnergyOffence = 10;
		PcProfile.avatarAttribute.LastEnergyOffence = 10;
		PcProfile.avatarAttribute.BaseEng = 255;
		PcProfile.avatarAttribute.LastEng = 255;
		PcProfile.avatarAttribute.BaseEpBattleRegen = 10;
		PcProfile.avatarAttribute.LastEpBattleRegen = 10;
		PcProfile.avatarAttribute.BaseEpRegen = 10;
		PcProfile.avatarAttribute.LastEpRegen = 10;
		PcProfile.avatarAttribute.BaseEpSitdownRegen = 10;
		PcProfile.avatarAttribute.LastEpSitdownRegen = 10;
		PcProfile.avatarAttribute.BaseFoc = 255;
		PcProfile.avatarAttribute.LastFoc = 255;
		PcProfile.avatarAttribute.BaseLpBattleRegen = 10;
		PcProfile.avatarAttribute.LastLpBattleRegen = 10;
		PcProfile.avatarAttribute.BaseLpRegen = 10;
		PcProfile.avatarAttribute.LastLpRegen = 10;
		PcProfile.avatarAttribute.BaseLpSitdownRegen = 10;
		PcProfile.avatarAttribute.LastLpSitdownRegen = 10;
		PcProfile.avatarAttribute.BasePhysicalCriticalRate = 10;
		PcProfile.avatarAttribute.LastPhysicalCriticalRate = 10;
		PcProfile.avatarAttribute.BasePhysicalDefence = 10;
		PcProfile.avatarAttribute.LastPhysicalDefence = 10;
		PcProfile.avatarAttribute.BasePhysicalOffence = 10;
		PcProfile.avatarAttribute.LastPhysicalOffence = 10;
		PcProfile.avatarAttribute.BaseRpRegen = 10;
		PcProfile.avatarAttribute.LastRpRegen = 10;
		PcProfile.avatarAttribute.BaseSol = 255;
		PcProfile.avatarAttribute.LastSol = 255;
		PcProfile.avatarAttribute.BaseStr = 255;
		PcProfile.avatarAttribute.LastStr = 255;
		PcProfile.avatarAttribute.BleedingKeepTimeDown = 2;
		PcProfile.avatarAttribute.CandyKeepTimeDown = 3;
		PcProfile.avatarAttribute.CandyToleranceRate = 10;
		PcProfile.avatarAttribute.CastingTimeChangePercent = 100;
		PcProfile.avatarAttribute.ConfuseKeepTimeDown = 1;
		PcProfile.avatarAttribute.ConfuseToleranceRate = 100;
		PcProfile.avatarAttribute.CoolTimeChangePercent = 100;
		PcProfile.avatarAttribute.CriticalBlockSuccessRate = 100;
		PcProfile.avatarAttribute.CurseBlockModeSuccessRate = 100;
		PcProfile.avatarAttribute.DotTimeChangeAbsolute = 1;
		PcProfile.avatarAttribute.DotValueChangePercent = 1;
		PcProfile.avatarAttribute.EleganceDefence = 100;
		PcProfile.avatarAttribute.EleganceOffence = 100;
		PcProfile.avatarAttribute.EnergyCriticalDamageBonusRate = 100;
		PcProfile.avatarAttribute.FunnyDefence = 100;
		PcProfile.avatarAttribute.FunnyOffence = 100;
		PcProfile.avatarAttribute.GuardRate = 100;
		PcProfile.avatarAttribute.HonestDefence = 100;
		PcProfile.avatarAttribute.HonestOffence = 100;
		PcProfile.avatarAttribute.HtbBlockModeSuccessRate = 100;
		PcProfile.avatarAttribute.ItemUpgradeBonusRate = 100;
		PcProfile.avatarAttribute.ItemUpgradeBreakBonusRate = 0;
		PcProfile.avatarAttribute.KeepTimeChangePercent = 100;
		PcProfile.avatarAttribute.KnockdownBlockModeSuccessRate = 100;
		PcProfile.avatarAttribute.ParalyzeKeepTimeDown = 100;
		PcProfile.avatarAttribute.PhysicalCriticalDamageBonusRate = 100;
		PcProfile.avatarAttribute.PoisonKeepTimeDown = 100;
		PcProfile.avatarAttribute.RequiredEpChangePercent = 100;
		PcProfile.avatarAttribute.SitDownEpRegenBonusRate = 100;
		PcProfile.avatarAttribute.SitDownLpRegenBonusRate = 100;
		PcProfile.avatarAttribute.SkillDamageBlockModeSuccessRate = 100;
		PcProfile.avatarAttribute.StomachacheKeepTimeDown = 100;
		PcProfile.avatarAttribute.StoneKeepTimeDown = 100;
		PcProfile.avatarAttribute.StoneToleranceRate = 100;
		PcProfile.avatarAttribute.StrangeDefence = 100;
		PcProfile.avatarAttribute.StrangeOffence = 100;
		PcProfile.avatarAttribute.TerrorKeepTimeDown = 100;
		PcProfile.avatarAttribute.TerrorToleranceRate = 100;
		PcProfile.avatarAttribute.WildDefence = 100;
		PcProfile.avatarAttribute.WildOffence = 100;
		PcProfile.avatarAttribute.LastRunSpeed = 10.0f;

		PcProfile.CharShape.Face = pServer->ServerDB->getInt("Face");
		PcProfile.CharShape.Hair = pServer->ServerDB->getInt("Hair");
		PcProfile.CharShape.HairColor = pServer->ServerDB->getInt("HairColor");
		PcProfile.CharShape.SkinColor = pServer->ServerDB->getInt("SkinColor");

		memset(&CharState, 0, sizeof(CharState));
		CharState.CharStateBase.ConditionFlag = 0;
		CharState.CharStateBase.FightMode = 0;
		CharState.CharStateBase.StateID = 0;
		CharState.CharStateBase.StateTime = 0;
		CharState.CharStateBase.aspectState.AspectStateBase.AspectStateId = 255;
		CharState.CharStateBase.aspectState.AspectStateDetail.GreatNamek.SourceGrade = 0;
		CharState.CharStateBase.aspectState.AspectStateDetail.Kaioken.RepeatingCount = 0;
		CharState.CharStateBase.aspectState.AspectStateDetail.Kaioken.SourceGrade = 0;
		CharState.CharStateBase.aspectState.AspectStateDetail.PureMajin.SourceGrade = 0;
		CharState.CharStateBase.aspectState.AspectStateDetail.SuperSaiyan.SourceGrade = 0;
		CharState.CharStateBase.aspectState.AspectStateDetail.Vehicle.idVehicleTblidx = 0;
		CharState.CharStateBase.aspectState.AspectStateDetail.Vehicle.IsEngineOn = 0;

		CharState.CharStateBase.CurLoc.x = pServer->ServerDB->getDouble("PositionX");
		CharState.CharStateBase.CurLoc.y = pServer->ServerDB->getDouble("PositionY");
		CharState.CharStateBase.CurLoc.z = pServer->ServerDB->getDouble("PositionZ");
		CharState.CharStateBase.CurDir.x = pServer->ServerDB->getDouble("DirectionX");
		CharState.CharStateBase.CurDir.y = pServer->ServerDB->getDouble("DirectionY");
		CharState.CharStateBase.CurDir.z = pServer->ServerDB->getDouble("DirectionZ");

		PcProfile.tblidx = this->GetPCTblidx(pServer->ServerDB->getInt("Race"), pServer->ServerDB->getInt("Gender"), pServer->ServerDB->getInt("Class"));
	}
}

