#include "CharNetwork.h"

CharClient::CharClient()
{
}

CharClient::~CharClient()
{
}

void CharClient::DBUpdateLastServer()
{
	if (pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `LastServerID` = '%d' WHERE `ID` = '%d';", CurrServerID, AccountID))
		LastServerID = CurrServerID;
}

int CharClient::GetDBAllowedRaces()
{
	MYSQL_RES* Res;
	MYSQL_ROW Row;
	int allraces = ALLRACES;
	if (pServer->ServerDB->ExecuteQuery("SELECT `AllowedRace` FROM account WHERE ID='%d'", AccountID))
	{
		Res = pServer->ServerDB->GetResult();
		while (Row = mysql_fetch_row(Res))
		{
			allraces = atoi(Row[0]);
		}
	}
	return allraces;

}

ResultCodes CharClient::CheckUsedName(WCHAR* Name)
{
	MYSQL_RES* Res;
	if (pServer->ServerDB->ExecuteQuery("SELECT * FROM `character` WHERE `Name`='%S';", Name))
	{
		Res = pServer->ServerDB->GetResult();
		if (mysql_num_rows(Res) == 0)
			return CHARACTER_SUCCESS;
		else
			return CHARACTER_SAMENAME_EXIST;
	}
	else
		return CHARACTER_DB_QUERY_FAIL;
}

void CharClient::DBInsertCharData(CHARDATA data)
{
	pServer->ServerDB->ExecuteQuery("INSERT INTO `character` (`AccID`, `Name`, `Class`, `Face`, `Gender`, `Hair`, `HairColor`, `Adult`, `Level`, `NeedNameChange`, `Race`, `SkinColor`, `worldTblidx`, `worldId`, `PositionX`, `PositionY`, `PositionZ`, `Money`, `MoneyBank`, `MapInfoId`, `TutorialFlag`, `ServerID`) VALUES ('%d', '%S', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d');",
		AccountID,
		data.Name,
		data.Class,
		data.Face,
		data.Gender,
		data.Hair,
		data.HairColor,
		data.IsAdult,
		data.Level,
		data.NeedNameChange,
		data.Race,
		data.SkinColor,
		data.worldTblidx,
		data.worldId,
		data.PositionX,
		data.PositionY,
		data.PositionZ,
		data.Money,
		data.MoneyBank,
		data.MapInfoId,
		data.TutorialFlag,
		CurrServerID);
}

int CharClient::GetDBAccCharListData(sCU_CHARACTER_INFO* outdata)
{
	MYSQL_RES* Res;
	MYSQL_ROW Row;
	if (pServer->ServerDB->ExecuteQuery("SELECT * FROM `character` WHERE `AccID`='%d' AND `ServerID`='%d' LIMIT 8;", AccountID, CurrServerID))
	{
		Res = pServer->ServerDB->GetResult();
		int c = 0;
		while (Row = mysql_fetch_row(Res))
		{
			outdata->CharData[c].charId = atoi(Row[0]);
			memcpy(outdata->CharData[c].Name, charToWChar(Row[2]), MAX_CHARNAME_SIZE);
			outdata->CharData[c].Class = atoi(Row[3]);
			outdata->CharData[c].Face = atoi(Row[4]);
			outdata->CharData[c].Gender = atoi(Row[5]);
			outdata->CharData[c].Hair = atoi(Row[6]);
			outdata->CharData[c].HairColor = atoi(Row[7]);
			outdata->CharData[c].IsAdult = (bool)atoi(Row[8]);
			outdata->CharData[c].Level = atoi(Row[9]);
			outdata->CharData[c].NeedNameChange = (bool)atoi(Row[10]);
			outdata->CharData[c].Race = atoi(Row[11]);
			outdata->CharData[c].SkinColor = atoi(Row[12]);
			outdata->CharData[c].worldTblidx = atoi(Row[13]);
			outdata->CharData[c].worldId = atoi(Row[14]);
			outdata->CharData[c].PositionX = (float)atof(Row[15]);
			outdata->CharData[c].PositionY = (float)atof(Row[16]);
			outdata->CharData[c].PositionZ = (float)atof(Row[17]);
			outdata->CharData[c].Money = atoi(Row[18]);
			outdata->CharData[c].MoneyBank = atoi(Row[19]);
			outdata->CharData[c].MapInfoId = atoi(Row[20]);
			outdata->CharData[c].TutorialFlag = (bool)atoi(Row[21]);
			//MARKING

			// Check to delete char flag
			if (atoi(Row[23]))
			{
				outdata->CharDelData[c].charId = atoi(Row[0]);
			}
			c++;
		}
		return c;
	}
	return 0;
}