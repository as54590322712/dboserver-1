#ifndef _CONFIG_H
#define _CONFIG_H

#include "Logger.h"

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml\tree.h>

#pragma comment(lib, "libxml2_a.lib")
#pragma comment(lib, "iconv_a.lib")
#pragma comment(lib, "zlib.lib")

class Config
{
public:
	Config(char* rootname);
	~Config();
	int GetInt(char* fieldname);
	std::string GetStr(char* fieldname);

	xmlDocPtr doc;
	xmlNodePtr root, node;
	char* rootname;
};

#endif