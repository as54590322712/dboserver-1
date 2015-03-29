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
	int allraces = 0xFF;
	if (pServer->ServerDB->ExecuteSelect("SELECT `AllowedRace` FROM account WHERE ID='%d'", AccountID))
	{
		while (pServer->ServerDB->Fetch())
		{
			allraces = pServer->ServerDB->getInt("AllowedRace");
		}
	}
	return allraces;
}

eRESULTCODE CharClient::CheckUsedName(WCHAR* Name)
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

eRESULTCODE CharClient::DBChangeCharName(WCHAR* Name, int charId)
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

int CharClient::DBInsertCharData(sPC_SUMMARY data, NewbieData nbdata)
{
	int charid = 0;
	PCData pcdata = pServer->pcTblData->GetData(data.byRace, data.byClass, data.byGender);
	// CALL `spInsertCharacter` ('AccID','ServerID','Name','Race','Class','Gender','Face','Hair','HairColor','SkinColor','Level','0','MapInfoId', 'worldTblidx', 'worldId', '0', '0', '0', 'PositionX', 'PositionY', 'PositionZ', 'DirectionX', 'DirectionY', 'DirectionZ', 'Money', 'MoneyBank', 'Marking', 'Adult', 'TutorialFlag', 'NeedNameChange', 'ToDelete', 'ChangeClass', 'IsGameMaster', 'TutorialHint', 'Reputation', 'MudosaPoint', 'SpPoint', 'CurEP', 'MaxEP', 'CurLP', 'MaxLP');
	pServer->ServerDB->ExecuteQuery(
		"CALL `spInsertCharacter` ('%u','%u','%S','%d','%d','%d','%d','%d','%d','%d','%d','0','%u','%u','%u','0','0','0','%f','%f','%f','%f','%f','%f','%u','%u','0','%d','%d','%d','0','0','0','0','0','0','0','%u','%u','%u','%u');",
		AccountID, CurrServerID, data.awchName, data.byRace, data.byClass, data.byGender, data.byFace, data.byHair, data.byHairColor, data.bySkinColor, data.byLevel, data.dwMapInfoIndex, data.worldTblidx, data.worldId, data.fPositionX, data.fPositionY,
		data.fPositionZ, nbdata.spawnDir.x, nbdata.spawnDir.y, nbdata.spawnDir.z, data.dwMoney, data.dwMoneyBank, data.bIsAdult, data.bTutorialFlag, data.bNeedNameChange, pcdata.Basic_EP, pcdata.Basic_EP, pcdata.Basic_LP, pcdata.Basic_LP);
	if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM `character` WHERE `AccID`='%d' AND `Name`='%S';", AccountID, data.awchName))
	{
		pServer->ServerDB->Fetch();
		charid = pServer->ServerDB->getInt("ID");
	}
	for (int i = 0; i < NTL_MAX_NEWBIE_ITEM; i++)
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
	for (int i = 0; i < NTL_MAX_NEWBIE_QUICKSLOT_COUNT; i++)
	{
		pServer->ServerDB->ExecuteQuery("INSERT INTO `quickslot` (`CharID`,`TblID`,`Slot`,`Type`) VALUES ('%u','%u','%u','%u');",
			charid, nbdata.QuickSlotData[i].tbilidx, nbdata.QuickSlotData[i].byQuickSlot, nbdata.QuickSlotData[i].byType);
	}
	for (int i = 0; i < NTL_MAX_NEWBIE_SKILL; i++)
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
				outdata->sPcData[c].charId = pServer->ServerDB->getInt("ID");
				memcpy(outdata->sPcData[c].awchName, charToWChar(pServer->ServerDB->getString("Name")), NTL_MAX_SIZE_CHAR_NAME_UNICODE);
				outdata->sPcData[c].byClass = pServer->ServerDB->getInt("Class");
				outdata->sPcData[c].byFace = pServer->ServerDB->getInt("Face");
				outdata->sPcData[c].byGender = pServer->ServerDB->getInt("Gender");
				outdata->sPcData[c].byHair = pServer->ServerDB->getInt("Hair");
				outdata->sPcData[c].byHairColor = pServer->ServerDB->getInt("HairColor");
				outdata->sPcData[c].bIsAdult = pServer->ServerDB->getBoolean("Adult");
				outdata->sPcData[c].byLevel = pServer->ServerDB->getInt("Level");
				outdata->sPcData[c].bNeedNameChange = pServer->ServerDB->getBoolean("NeedNameChange");
				outdata->sPcData[c].byRace = pServer->ServerDB->getInt("Race");
				outdata->sPcData[c].bySkinColor = pServer->ServerDB->getInt("SkinColor");
				outdata->sPcData[c].worldTblidx = pServer->ServerDB->getInt("worldTblidx");
				outdata->sPcData[c].worldId = pServer->ServerDB->getInt("worldId");
				outdata->sPcData[c].fPositionX = pServer->ServerDB->getFloat("PositionX");
				outdata->sPcData[c].fPositionY = pServer->ServerDB->getFloat("PositionY");
				outdata->sPcData[c].fPositionZ = pServer->ServerDB->getFloat("PositionZ");
				outdata->sPcData[c].dwMoney = pServer->ServerDB->getInt("Money");
				outdata->sPcData[c].dwMoneyBank = pServer->ServerDB->getInt("MoneyBank");
				outdata->sPcData[c].dwMapInfoIndex = pServer->ServerDB->getInt("MapInfoId");
				outdata->sPcData[c].bTutorialFlag = pServer->ServerDB->getBoolean("TutorialFlag");
				//MARKING

				// Check to delete char flag
				if (pServer->ServerDB->getBoolean("ToDelete"))
				{
					outdata->asDelData[c].charId = pServer->ServerDB->getInt("ID");
				}
				c++;
			}
		}
		for (int i = 0; i < c; i++)
		{
			for (int x = 0; x < EQUIP_SLOT_TYPE_COUNT; x++)
			{
				memset(&outdata->sPcData[i].sItem[x], 0xFF, sizeof(sITEM_SUMMARY));
			}
			if (pServer->ServerDB->ExecuteSelect("SELECT * FROM `inventory` WHERE `CharID`='%u';", outdata->sPcData[i].charId))
			{
				while (pServer->ServerDB->Fetch())
				{
					int slot = pServer->ServerDB->getInt("Slot");
					int place = pServer->ServerDB->getInt("Place");
					if (((slot >= 0) && (slot <= 12)) && place == CONTAINER_TYPE_EQUIP)
					{
						outdata->sPcData[i].sItem[slot].tblidx = pServer->ServerDB->getInt("ItemID");
						outdata->sPcData[i].sItem[slot].byRank = pServer->ServerDB->getInt("Rank");
						outdata->sPcData[i].sItem[slot].byGrade = pServer->ServerDB->getInt("Grade");
						outdata->sPcData[i].sItem[slot].byBattleAttribute = pServer->ServerDB->getInt("BattleAttribute");
						outdata->sPcData[i].sItem[slot].aOptionTblidx[0] = pServer->ServerDB->getInt("Opt1");
						outdata->sPcData[i].sItem[slot].aOptionTblidx[1] = pServer->ServerDB->getInt("Opt2");
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