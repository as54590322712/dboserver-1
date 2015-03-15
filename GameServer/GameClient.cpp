#include "GameNetwork.h"

GameClient::GameClient()
{
}

GameClient::~GameClient()
{
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
		PCData pcdata = pServer->pcTblData->GetData(pServer->ServerDB->getInt("Race"), pServer->ServerDB->getInt("Gender"), pServer->ServerDB->getInt("Class"));
		memset(&PcProfile, 0, sizeof(PcProfile));
		memcpy(PcProfile.Name, charToWChar(pServer->ServerDB->getString("Name")), MAX_CHARNAME_SIZE);
		PcProfile.tblidx = pcdata.TblIndex;
		PcProfile.charId = pServer->ServerDB->getInt("ID");
		PcProfile.IsGameMaster = false;
		PcProfile.Level = pServer->ServerDB->getInt("Level");
		PcProfile.CurExp = pServer->ServerDB->getInt("Exp");
		PcProfile.IsAdult = pServer->ServerDB->getBoolean("Adult");
		PcProfile.MaxExpInThisLevel = 100;
		PcProfile.TutorialHint = 1;
		PcProfile.CurEP = 1000;
		PcProfile.CurLP = 1000;
		PcProfile.CurRP = 100;
		PcProfile.Zenny = pServer->ServerDB->getInt("Money");

		PcProfile.avatarAttribute.BaseMaxEP = pcdata.Basic_EP + 1000;
		PcProfile.avatarAttribute.LastMaxEP = PcProfile.avatarAttribute.BaseMaxEP;
		PcProfile.avatarAttribute.BaseMaxLP = pcdata.Basic_LP + 1000;
		PcProfile.avatarAttribute.LastMaxLP = PcProfile.avatarAttribute.BaseMaxLP;
		PcProfile.avatarAttribute.BaseMaxRP = pcdata.Basic_RP + 100;
		PcProfile.avatarAttribute.LastMaxRP = PcProfile.avatarAttribute.BaseMaxRP;
		PcProfile.avatarAttribute.BaseAttackRange = pcdata.Attack_Range + 10.0f;
		PcProfile.avatarAttribute.LastAttackRange = PcProfile.avatarAttribute.BaseAttackRange;
		PcProfile.avatarAttribute.BaseAttackRate = pcdata.Attack_Rate + 10;
		PcProfile.avatarAttribute.LastAttackRate = PcProfile.avatarAttribute.BaseAttackRate;
		PcProfile.avatarAttribute.BaseAttackSpeedRate = pcdata.Attack_Speed_Rate + 10;
		PcProfile.avatarAttribute.LastAttackSpeedRate = PcProfile.avatarAttribute.BaseAttackSpeedRate;
		PcProfile.avatarAttribute.BaseBlockRate = pcdata.Block_Rate + 10;
		PcProfile.avatarAttribute.LastBlockRate = PcProfile.avatarAttribute.BaseBlockRate;
		PcProfile.avatarAttribute.BaseCon = pcdata.Con;
		PcProfile.avatarAttribute.LastCon = PcProfile.avatarAttribute.BaseCon;
		PcProfile.avatarAttribute.BaseCurseSuccessRate = pcdata.Curse_Success_Rate + 10;
		PcProfile.avatarAttribute.LastCurseSuccessRate = PcProfile.avatarAttribute.BaseCurseSuccessRate;
		PcProfile.avatarAttribute.BaseCurseToleranceRate = pcdata.Curse_Tolerance_Rate + 10;
		PcProfile.avatarAttribute.LastCurseToleranceRate = PcProfile.avatarAttribute.BaseCurseToleranceRate;
		PcProfile.avatarAttribute.BaseDex = pcdata.Dex;
		PcProfile.avatarAttribute.LastDex = PcProfile.avatarAttribute.BaseDex;
		PcProfile.avatarAttribute.BaseDodgeRate = pcdata.Dodge_Rate + 10;
		PcProfile.avatarAttribute.LastDodgeRate = PcProfile.avatarAttribute.BaseDodgeRate;
		PcProfile.avatarAttribute.BaseEnergyCriticalRate = 10;
		PcProfile.avatarAttribute.LastEnergyCriticalRate = PcProfile.avatarAttribute.BaseEnergyCriticalRate;
		PcProfile.avatarAttribute.BaseEnergyDefence = 10;
		PcProfile.avatarAttribute.LastEnergyDefence = PcProfile.avatarAttribute.BaseEnergyDefence;
		PcProfile.avatarAttribute.BaseEnergyOffence = 10;
		PcProfile.avatarAttribute.LastEnergyOffence = PcProfile.avatarAttribute.BaseEnergyOffence;
		PcProfile.avatarAttribute.BaseEng = pcdata.Eng;
		PcProfile.avatarAttribute.LastEng = PcProfile.avatarAttribute.BaseEng;
		PcProfile.avatarAttribute.BaseEpBattleRegen = 10;
		PcProfile.avatarAttribute.LastEpBattleRegen = PcProfile.avatarAttribute.BaseEpBattleRegen;
		PcProfile.avatarAttribute.BaseEpRegen = 10;
		PcProfile.avatarAttribute.LastEpRegen = PcProfile.avatarAttribute.BaseEpRegen;
		PcProfile.avatarAttribute.BaseEpSitdownRegen = 10;
		PcProfile.avatarAttribute.LastEpSitdownRegen = PcProfile.avatarAttribute.BaseEpSitdownRegen;
		PcProfile.avatarAttribute.BaseFoc = pcdata.Foc;
		PcProfile.avatarAttribute.LastFoc = PcProfile.avatarAttribute.BaseFoc;
		PcProfile.avatarAttribute.BaseLpBattleRegen = 10;
		PcProfile.avatarAttribute.LastLpBattleRegen = PcProfile.avatarAttribute.BaseLpBattleRegen;
		PcProfile.avatarAttribute.BaseLpRegen = 10;
		PcProfile.avatarAttribute.LastLpRegen = PcProfile.avatarAttribute.BaseLpRegen;
		PcProfile.avatarAttribute.BaseLpSitdownRegen = 10;
		PcProfile.avatarAttribute.LastLpSitdownRegen = PcProfile.avatarAttribute.BaseLpSitdownRegen;
		PcProfile.avatarAttribute.BasePhysicalCriticalRate = 10;
		PcProfile.avatarAttribute.LastPhysicalCriticalRate = PcProfile.avatarAttribute.BasePhysicalCriticalRate;
		PcProfile.avatarAttribute.BasePhysicalDefence = 10;
		PcProfile.avatarAttribute.LastPhysicalDefence = PcProfile.avatarAttribute.BasePhysicalDefence;
		PcProfile.avatarAttribute.BasePhysicalOffence = 10;
		PcProfile.avatarAttribute.LastPhysicalOffence = PcProfile.avatarAttribute.BasePhysicalOffence;
		PcProfile.avatarAttribute.BaseRpRegen = 10;
		PcProfile.avatarAttribute.LastRpRegen = PcProfile.avatarAttribute.BaseRpRegen;
		PcProfile.avatarAttribute.BaseSol = pcdata.Sol;
		PcProfile.avatarAttribute.LastSol = PcProfile.avatarAttribute.BaseSol;
		PcProfile.avatarAttribute.BaseStr = pcdata.Str;
		PcProfile.avatarAttribute.LastStr = PcProfile.avatarAttribute.BaseStr;

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
		PcProfile.avatarAttribute.LastRunSpeed = (PcProfile.IsAdult) ? pcdata.Adult_Run_Speed : pcdata.Child_Run_Speed;

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
	}
}

