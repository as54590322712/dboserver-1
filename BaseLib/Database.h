#ifndef _DATABASE_H
#define _DATABASE_H

#include <mysql.h>

#pragma comment(lib, "libmysql.lib")

class Database
{
public:
	Database();
	~Database();
	bool Connect(char* host, char* database, char* user, char* password, int port);
	MYSQL_RES* GetResult();
	bool ExecuteQuery(char* Format, ...);

	MYSQL m_conn;
};

#endif