#include "AuthNetwork.h"

AuthClient::AuthClient() {}

AuthClient::~AuthClient() {}

char* AuthClient::GenAuthKey()
{
	char Key[MAX_AUTHKEY_SIZE];
	sprintf_s(Key, MAX_AUTHKEY_SIZE, "%d", time(NULL));
	return (char*)&Key[0];
}

int AuthClient::GetDBAccountID()
{
	MYSQL_RES* Res;
	MYSQL_ROW Row;
	if (pServer->ServerDB->ExecuteQuery("SELECT * FROM account WHERE userName='%S' AND passWord='%S'", userName, passWord))
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
					return AUTH_SUCCESS;
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