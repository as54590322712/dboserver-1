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
	int allraces = ALLRACES;
	if (pServer->ServerDB->ExecuteSelect("SELECT `AllowedRace` FROM account WHERE ID='%d'", AccountID))
	{
		while (pServer->ServerDB->Fetch())
		{
			allraces = pServer->ServerDB->getInt("AllowedRace");
		}
	}
	return allraces;
}

ResultCodes CharClient::CheckUsedName(WCHAR* Name)
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `Name`='%S';", Name))
	{
		pServer->ServerDB->Fetch();
		if (pServer->ServerDB->rowsCount() == 0)
			return CHARACTER_SUCCESS;
		else
			return CHARACTER_SAMENAME_EXIST;
	}
	return CHARACTER_DB_QUERY_FAIL;
}

ResultCodes CharClient::DBChangeCharName(WCHAR* Name, int charId)
{
	if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `Name`='%S';", Name))
	{
		pServer->ServerDB->Fetch();
		if (pServer->ServerDB->rowsCount() == 0)
		{
			pServer->ServerDB->ExecuteQuery("UPDATE `character` SET `Name` = '%S' WHERE `ID` = '%d';", Name, charId);
			return CHARACTER_SUCCESS;
		}
		else
			return CHARACTER_SAMENAME_EXIST;
	}
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
	try
	{
		if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ServerID`='%d' LIMIT 8;", AccountID, CurrServerID))
		{
			int c = 0;
			while (pServer->ServerDB->Fetch())
			{
				outdata->CharData[c].charId = pServer->ServerDB->getInt("ID");
				memcpy(outdata->CharData[c].Name, charToWChar(pServer->ServerDB->getString("Name").c_str()), MAX_CHARNAME_SIZE);
				outdata->CharData[c].Class = pServer->ServerDB->getInt("Class");
				outdata->CharData[c].Face = pServer->ServerDB->getInt("Face");
				outdata->CharData[c].Gender = pServer->ServerDB->getInt("Gender");
				outdata->CharData[c].Hair = pServer->ServerDB->getInt("Hair");
				outdata->CharData[c].HairColor = pServer->ServerDB->getInt("HairColor");
				outdata->CharData[c].IsAdult = pServer->ServerDB->getBoolean("Adult");
				outdata->CharData[c].Level = pServer->ServerDB->getInt("Level");
				outdata->CharData[c].NeedNameChange = pServer->ServerDB->getBoolean("NeedNameChange");
				outdata->CharData[c].Race = pServer->ServerDB->getInt("Race");
				outdata->CharData[c].SkinColor = pServer->ServerDB->getInt("SkinColor");
				outdata->CharData[c].worldTblidx = pServer->ServerDB->getInt("worldTblidx");
				outdata->CharData[c].worldId = pServer->ServerDB->getInt("worldId");
				outdata->CharData[c].PositionX = pServer->ServerDB->getDouble("PositionX");
				outdata->CharData[c].PositionY = pServer->ServerDB->getDouble("PositionY");
				outdata->CharData[c].PositionZ = pServer->ServerDB->getDouble("PositionZ");
				outdata->CharData[c].Money = pServer->ServerDB->getInt("Money");
				outdata->CharData[c].MoneyBank = pServer->ServerDB->getInt("MoneyBank");
				outdata->CharData[c].MapInfoId = pServer->ServerDB->getInt("MapInfoId");
				outdata->CharData[c].TutorialFlag = pServer->ServerDB->getBoolean("TutorialFlag");
				//MARKING

				// Check to delete char flag
				if (pServer->ServerDB->getBoolean("ToDelete"))
				{
					outdata->CharDelData[c].charId = pServer->ServerDB->getInt("ID");
				}
				c++;
			}
			return c;
		}
	}
	catch (SQLException &e) {
		Logger::Log("# ERROR #\n");
		std::cout << "\t\tSQLException in " << __FILE__ << " (" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "\t\t" << e.what() << " (MySQL error code: " << e.getErrorCode() << " SQLState: " << e.getSQLState() << std::endl;
	}
	return 0;
}