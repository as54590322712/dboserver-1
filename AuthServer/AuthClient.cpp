#include "AuthNetwork.h"

AuthClient::AuthClient() {}

AuthClient::~AuthClient() {}

char* AuthClient::GenAuthKey()
{
	char Key[MAX_AUTHKEY_SIZE];
	sprintf_s(Key, MAX_AUTHKEY_SIZE, "%d", time(NULL));
	return (char*)&Key[0];
}

int AuthClient::GetDBAccountAcLevel()
{
	MYSQL_RES* Res;
	MYSQL_ROW Row;
	if (pServer->ServerDB->ExecuteQuery("SELECT `AcLevel` FROM account WHERE ID='%d'", AccountID))
	{
		Res = pServer->ServerDB->GetResult();
		while (Row = mysql_fetch_row(Res))
		{
			return atoi(Row[0]);
		}
	}
	else
	{
		return 0;
	}
}

BYTE AuthClient::GetDBLastServerID()
{
	MYSQL_RES* Res;
	MYSQL_ROW Row;
	if (pServer->ServerDB->ExecuteQuery("SELECT `LastServerID` FROM account WHERE ID='%d'", AccountID))
	{
		Res = pServer->ServerDB->GetResult();
		while (Row = mysql_fetch_row(Res))
		{
			return atoi(Row[0]);
		}
	}
	else
	{
		return INVALID_SERVERID;
	}
}

int AuthClient::GetDBAccountID()
{
	MYSQL_RES* Res;
	MYSQL_ROW Row;
	if (pServer->ServerDB->ExecuteQuery("SELECT `ID` FROM account WHERE userName='%S' AND passWord='%S'", userName, passWord))
	{
		Res = pServer->ServerDB->GetResult();
		while (Row = mysql_fetch_row(Res))
		{
			return atoi(Row[0]);
		}
	}
	else
	{
		return 0;
	}
}

ResultCodes AuthClient::LoginVerifyAccount()
{
	MYSQL_RES* Res;
	if (pServer->ServerDB->ExecuteQuery("SELECT * FROM account WHERE userName='%S'", userName))
	{
		Res = pServer->ServerDB->GetResult();
		if (mysql_num_rows(Res) == 0)
		{
			return AUTH_USER_NOT_FOUND;
		}
		else
		{
			if (pServer->ServerDB->ExecuteQuery("SELECT * FROM account WHERE userName='%S' AND passWord='%S'", userName, passWord))
			{
				Res = pServer->ServerDB->GetResult();
				if (mysql_num_rows(Res) == 0)
				{
					return AUTH_WRONG_PASSWORD;
				}
				else
				{
					if (pServer->ServerDB->ExecuteQuery("SELECT * FROM `account` WHERE `userName`='%S' AND `passWord`='%S' AND `State`='0'", userName, passWord))
					{
						Res = pServer->ServerDB->GetResult();
						if (mysql_num_rows(Res) == 0)
						{
							bool reconnect = false;

							for each (Client* var in pServer->Clients)
							{
								if ((wcscmp(userName, var->userName) == 0) && (sock == var->sock))
								{
									reconnect = true;
									break;
								}
							}

							if (reconnect)
							{
								if (pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '1' WHERE `ID` = '%d';", AccountID))
									return AUTH_SUCCESS;
								else
									return AUTH_DB_FAIL;
							}
							else
								return AUTH_USER_EXIST;
						}
						else
						{
							if (pServer->ServerDB->ExecuteQuery("UPDATE `account` SET `State` = '1' WHERE `ID` = '%d';", AccountID))
								return AUTH_SUCCESS;
							else
								return AUTH_DB_FAIL;
						}
					}
				}
			}
			else
			{
				return AUTH_DB_FAIL;
			}
		}
	}
	else
	{
		return AUTH_DB_FAIL;
	}
}