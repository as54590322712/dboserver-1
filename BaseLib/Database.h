#ifndef _DATABASE_H
#define _DATABASE_H

#define CPPCONN_LIB_BUILD 1

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "mysqlcppconn-static.lib")

using namespace sql;

class Database
{
public:
	Database();
	~Database();
	bool Connect(char* host, char* database, char* user, char* password, int port);
	bool ChangeDB(char* db);
	bool ExecuteUpdate(char* Format, ...);
	bool ExecuteQuery(char* Format, ...);
	bool Fetch();
	long double getDouble(const char* index);
	bool getBoolean(const char* index);
	int getInt(const char* index);
	std::string getString(const char* index);
	size_t rowsCount();

	Connection* m_conn;
	Driver* driver;
	Statement* stmt;
	ResultSet* res;
};

#endif