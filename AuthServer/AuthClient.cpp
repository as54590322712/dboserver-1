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
	if (pServer->ServerDB->ExecuteSelect("SELECT `AcLevel` FROM account WHERE ID='%d'", AccountID))
	{
		while (pServer->ServerDB->Fetch())
		{
			return pServer->ServerDB->getInt("AcLevel");
		}
	}
	return 0;
}

BYTE AuthClient::GetDBLastServerID()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT `LastServerID` FROM account WHERE ID='%d'", AccountID))
	{
		while (pServer->ServerDB->Fetch())
		{
			return pServer->ServerDB->getInt("LastServerID");
		}
	}
	return INVALID_SERVERID;
}

int AuthClient::GetDBAccountID()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM account WHERE userName='%S' AND passWord='%S'", userName, passWord))
	{
		while (pServer->ServerDB->Fetch())
		{
			return pServer->ServerDB->getInt("ID");
		}
	}
	return 0;
}

ResultCodes AuthClient::LoginVerifyAccount()
{
	if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM account WHERE userName='%S'", userName))
	{
		pServer->ServerDB->Fetch();
		if (pServer->ServerDB->rowsCount() == 0)
		{
			return AUTH_USER_NOT_FOUND;
		}
		else
		{
			if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM account WHERE userName='%S' AND passWord='%S'", userName, passWord))
			{
				pServer->ServerDB->Fetch();
				if (pServer->ServerDB->rowsCount() == 0)
				{
					return AUTH_WRONG_PASSWORD;
				}
				else
				{
					if (pServer->ServerDB->ExecuteSelect("SELECT `ID` FROM `account` WHERE `userName`='%S' AND `passWord`='%S' AND `State`='0'", userName, passWord))
					{
						pServer->ServerDB->Fetch();
						if (pServer->ServerDB->rowsCount() == 0)
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
	return AUTH_DB_FAIL;
}