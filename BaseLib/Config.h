#ifndef _CONFIG_H
#define _CONFIG_H

#pragma once

#include "Base.h"
#include "Logger.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#pragma comment(lib, "libxml2_a.lib")
#pragma comment(lib, "iconv_a.lib")
#pragma comment(lib, "zlib.lib")

class Config
{
public:
	Config(const char* rootname);
	~Config();
	int GetInt(char* fieldname);
	int GetInt(char* fieldname, char* valuename);
	char* GetStr(char* fieldname);
	char* GetStr(char* fieldname, char* valuename);
	int GetChildInt(char* child, char* fieldname);
	int GetChildInt(char* child, char* fieldname, char* valuename);
	char* GetChildStr(char* child, char* fieldname);
	char* GetChildStr(char* child, char* fieldname, char* valuename);

	xmlDocPtr doc;
	xmlNodePtr root, node;
	char* rootname;
};

#endif