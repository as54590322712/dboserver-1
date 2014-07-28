#include "Database.h"
#include "Def.h"
#include "Logger.h"
#include <cstdio>

Database::Database()
{
	mysql_init(&m_conn);
}

Database::~Database()
{
	mysql_shutdown(&m_conn, SHUTDOWN_DEFAULT);
}

bool Database::Connect(char* host, char* database, char* user, char* password, int port)
{
	if (mysql_real_connect(&m_conn, host, user, password, database, port, NULL, 0))
	{
		Logger::Log("Connected to Database Server (%s:%d) [%s]\n", host, port, database);
		return true;
	}
	else
	{
		Logger::Log("Cannot connect to MySQL Server (%s)\n", mysql_error(&m_conn));
		return false;
	}
}

MYSQL_RES* Database::GetResult()
{
	return mysql_store_result(&m_conn);
}

bool Database::ExecuteQuery(char* Format, ...)
{
	char szQuery[MAX_PATH];
	va_list ap;
	va_start(ap, Format);
	vsprintf_s(szQuery, Format, ap);
	va_end(ap);

	if (mysql_query(&m_conn, szQuery) == 0)
	{
		return true;
	}
	else
	{
		Logger::Log("Cannot execute Query (%s)\n", mysql_error(&m_conn));
		return false;
	}
}