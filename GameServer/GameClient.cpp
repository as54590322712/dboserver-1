#include "GameNetwork.h"

GameClient::GameClient()
{
}

GameClient::~GameClient()
{
}

void GameClient::LoadSendCharacterData(sGU_AVATAR_CHAR_INFO* data)
{
	MYSQL_RES* Res;
	MYSQL_ROW Row;
	if (pServer->ServerDB->ExecuteQuery("SELECT * FROM `character` WHERE `AccID`='%d' AND `ID`='%d';", this->AccountID, this->CurrCharID))
	{
		Res = pServer->ServerDB->GetResult();
		while (Row = mysql_fetch_row(Res))
		{
			memcpy(data->PcProfile.Name, charToWChar(Row[2]), MAX_CHARNAME_SIZE);
			data->PcProfile.tblidx = 1;

			data->PcProfile.charId = atoi(Row[0]);
			data->PcProfile.IsGameMaster = true;
			data->PcProfile.Level = 1;
			data->PcProfile.CurEP = 10000;
			data->PcProfile.CurLP = 10000;
			data->PcProfile.CurRP = 0;
			data->PcProfile.Zenny = 100000000;

			data->PcProfile.avatarAttribute.BaseMaxEP = 10000;
			data->PcProfile.avatarAttribute.LastMaxEP = 10000;
			data->PcProfile.avatarAttribute.BaseMaxLP = 10000;
			data->PcProfile.avatarAttribute.LastMaxLP = 10000;
			data->PcProfile.avatarAttribute.BaseMaxRP = 100;
			data->PcProfile.avatarAttribute.LastMaxRP = 100;
			data->PcProfile.avatarAttribute.BaseAttackRange = 10.0f;
			data->PcProfile.avatarAttribute.BaseAttackRate = 10;
			data->PcProfile.avatarAttribute.BaseAttackSpeedRate = 10;
			data->PcProfile.avatarAttribute.BaseBlockRate = 10;
			data->PcProfile.avatarAttribute.BaseCon = 255;
			data->PcProfile.avatarAttribute.BaseCurseSuccessRate = 10;
			data->PcProfile.avatarAttribute.BaseCurseToleranceRate = 10;
			data->PcProfile.avatarAttribute.BaseDex = 255;
			data->PcProfile.avatarAttribute.BaseDodgeRate = 10;
			data->PcProfile.avatarAttribute.BaseEnergyCriticalRate = 10;
			data->PcProfile.avatarAttribute.BaseEnergyDefence = 10;
			data->PcProfile.avatarAttribute.BaseEnergyOffence = 10;
			data->PcProfile.avatarAttribute.BaseEng = 255;
			data->PcProfile.avatarAttribute.BaseEpBattleRegen = 10;
			data->PcProfile.avatarAttribute.BaseEpRegen = 10;
			data->PcProfile.avatarAttribute.BaseEpSitdownRegen = 10;
			data->PcProfile.avatarAttribute.BaseFoc = 255;
			data->PcProfile.avatarAttribute.BaseLpBattleRegen = 10;
			data->PcProfile.avatarAttribute.BaseLpRegen = 10;
			data->PcProfile.avatarAttribute.BaseLpSitdownRegen = 10;
			data->PcProfile.avatarAttribute.BasePhysicalCriticalRate = 10;
			data->PcProfile.avatarAttribute.BasePhysicalDefence = 10;
			data->PcProfile.avatarAttribute.BasePhysicalOffence = 10;
			data->PcProfile.avatarAttribute.BaseRpRegen = 10;
			data->PcProfile.avatarAttribute.BaseSol = 255;
			data->PcProfile.avatarAttribute.BaseStr = 255;
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

			data->PcProfile.CharShape.Face = atoi(Row[4]);
			data->PcProfile.CharShape.Hair = atoi(Row[6]);
			data->PcProfile.CharShape.HairColor = atoi(Row[7]);
			data->PcProfile.CharShape.SkinColor = atoi(Row[12]);

			data->CharState.CharStateBase.CurLoc.x = atof(Row[15]);
			data->CharState.CharStateBase.CurLoc.y = atof(Row[16]);
			data->CharState.CharStateBase.CurLoc.z = atof(Row[17]);
			data->CharState.CharStateBase.CurDir.x = 0.0f;
			data->CharState.CharStateBase.CurDir.y = 0.0f;
			data->CharState.CharStateBase.CurDir.z = 1.0f;

			data->CharStateSize = sizeof(CHARSTATE_BASE);
		}
	}
}

