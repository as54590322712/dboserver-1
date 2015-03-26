#include "CharNetwork.h"

CharClient::CharClient(bool IsAliveCheck, bool IsOpcodeCheck)
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
	pServer = (CharServer*)_GetApp();
}

CharClient::~CharClient()
{
}

int	CharClient::OnAccept()
{
	return 0;
}

void CharClient::OnClose()
{
	if (goGameServer) pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '3' WHERE `ID` = '%d';", AccountID);
	else pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '0' WHERE `ID` = '%d';", AccountID);
}

int CharClient::OnDispatch(Packet* pPacket)
{
	PacketControl(pPacket);
	//	return OnDispatch(pPacket);
	return 0;
}

void CharClient::Send(void* pData, int nSize)
{
	Packet* packet = new Packet((unsigned char*)pData, nSize);
	int rc = pServer->Send(this->GetHandle(), packet);
	if (0 != rc)
	{
		Logger::Log("Failed to send packet %d\n", rc);
	}
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

int CharClient::DBInsertCharData(CHARDATA data, NewbieData nbdata)
{
	int charid = 0;
	pServer->ServerDB->ExecuteQuery("INSERT INTO `character` \
		(`AccID`,`Name`,`Class`,`Face`,`Gender`,`Hair`,`HairColor`,`Adult`,`Level`,`NeedNameChange`,`Race`,`SkinColor`,`worldTblidx`,\
		`worldId`,`PositionX`,`PositionY`,`PositionZ`,`Money`,`MoneyBank`,`MapInfoId`,`TutorialFlag`,`ServerID`,`DirectionX`,`DirectionY`,`DirectionZ`) \
		VALUES ('%u','%S','%u','%u','%u','%u','%u','%u','%u','%u','%u','%u','%u','%u','%f','%f','%f','%u','%u','%u','%u','%u','%f','%f','%f');",
		AccountID, data.Name, data.Class, data.Face, data.Gender, data.Hair, data.HairColor, data.IsAdult, data.Level, data.NeedNameChange,
		data.Race,	data.SkinColor,	data.worldTblidx, data.worldId, data.PositionX, data.PositionY,	data.PositionZ,	data.Money,	data.MoneyBank,
		data.MapInfoId, data.TutorialFlag, CurrServerID, nbdata.spawnDir.x, nbdata.spawnDir.y, nbdata.spawnDir.z);
	if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM `character` WHERE `AccID`='%d' AND `Name`='%S';", AccountID, data.Name))
	{
		pServer->ServerDB->Fetch();
		charid = pServer->ServerDB->getInt("ID");
	}
	for (int i = 0; i < NEWBIE_ITEM_MAX; i++)
	{
		int slot = nbdata.itemSlot[i];
		if ((slot >= 0) && (slot <= 12))
			pServer->ServerDB->ExecuteQuery("INSERT INTO `inventory` (`ItemID`,`CharID`,`Slot`,`Stack`,`Place`) VALUES ('%u', '%u', '%u', '%u', '%u');",
			nbdata.itemId[i], charid, slot, nbdata.itemStack[i], CONTAINER_TYPE_EQUIP);
	}
	pServer->ServerDB->ExecuteQuery("INSERT INTO `inventory` (`ItemID`,`CharID`,`Slot`,`Stack`,`Place`) VALUES ('%u', '%u', '%u', '%u', '%u');", 19901, charid, 0, 1, CONTAINER_TYPE_BAGSLOT);
	pServer->ServerDB->ExecuteQuery("INSERT INTO `inventory` (`ItemID`,`CharID`,`Slot`,`Stack`,`Place`) VALUES ('%u', '%u', '%u', '%u', '%u');", 19905, charid, 1, 1, CONTAINER_TYPE_BAGSLOT);
	pServer->ServerDB->ExecuteQuery("INSERT INTO `inventory` (`ItemID`,`CharID`,`Slot`,`Stack`,`Place`) VALUES ('%u', '%u', '%u', '%u', '%u');", 19991, charid, 0, 1, CONTAINER_TYPE_BANKSLOT);
	// dragon balls
	//for (int i = 0; i < 7; i++)
	//	pServer->ServerDB->ExecuteQuery("INSERT INTO `inventory` (`ItemID`,`CharID`,`Slot`,`Stack`,`Place`) VALUES ('%u', '%u', '%u', '%u', '%u');", 200001 + i, charid, i, 1, CONTAINER_TYPE_BAG1);
	for (int i = 0; i < NEWBIE_MAX_QUICKSLOT_COUNT; i++)
	{
		pServer->ServerDB->ExecuteQuery("INSERT INTO `quickslot` (`CharID`,`TblID`,`Slot`,`Type`) VALUES ('%u','%u','%u','%u');",
			charid, nbdata.QuickSlotData[i].tblidx, nbdata.QuickSlotData[i].QuickSlot, nbdata.QuickSlotData[i].Type);
	}
	for (int i = 0; i < NEWBIE_SKILL_MAX; i++)
	{
		if (nbdata.SkillsIds[i] != INVALID_DWORD)
			pServer->ServerDB->ExecuteQuery("INSERT INTO `skills` (`CharID`, `SkillID`, `Slot`) VALUES ('%u','%u','%u');",
				charid, nbdata.SkillsIds[i], i + 1);
	}
	return charid;
}

int CharClient::GetDBAccCharListData(sCU_CHARACTER_INFO* outdata)
{
	try
	{
		int c = 0;
		if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `character` WHERE `AccID`='%d' AND `ServerID`='%d' LIMIT 8;", AccountID, CurrServerID))
		{
			while (pServer->ServerDB->Fetch())
			{
				outdata->CharData[c].charId = pServer->ServerDB->getInt("ID");
				memcpy(outdata->CharData[c].Name, charToWChar(pServer->ServerDB->getString("Name")), MAX_CHARNAME_SIZE);
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
		}
		for (int i = 0; i < c; i++)
		{
			if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `inventory` WHERE `CharID`='%u';", outdata->CharData[i].charId))
			{
				while (pServer->ServerDB->Fetch())
				{
					int slot = pServer->ServerDB->getInt("Slot");
					int place = pServer->ServerDB->getInt("Place");
					if (((slot >= 0) && (slot <= 12)) && place == CONTAINER_TYPE_EQUIP)
					{
						outdata->CharData[i].Item[slot].tblidx = pServer->ServerDB->getInt("ItemID");
						outdata->CharData[i].Item[slot].Rank = pServer->ServerDB->getInt("Rank");
						outdata->CharData[i].Item[slot].Grade = pServer->ServerDB->getInt("Grade");
						outdata->CharData[i].Item[slot].BattleAttribute = pServer->ServerDB->getInt("BattleAttribute");
						outdata->CharData[i].Item[slot].OptionTblidx[0] = pServer->ServerDB->getInt("Opt1");
						outdata->CharData[i].Item[slot].OptionTblidx[1] = pServer->ServerDB->getInt("Opt2");
					}
				}
			}
		}
		return c;
	}
	catch (SQLException &e) {
		Logger::Log("# ERROR #\n");
		std::cout << "\t\tSQLException in " << __FILE__ << " (" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "\t\t" << e.what() << " (MySQL error code: " << e.getErrorCode() << " SQLState: " << e.getSQLState() << std::endl;
	}
	return 0;
}