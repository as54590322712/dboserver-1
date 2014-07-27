#include "Config.h"

Config::Config(char* rname)
{
	char filename[MAX_PATH];
	sprintf_s(filename, MAX_PATH, "%sConfig.xml", rname);
	doc = xmlParseFile(filename);
	rootname = rname;
}

Config::~Config()
{
	xmlFreeDoc(doc);
}

int Config::GetInt(char* fieldname)
{
	if (doc)
	{
		root = xmlDocGetRootElement(doc);
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0){
			xmlFreeDoc(doc);
			Logger::Log("Error on Loading Config.xml, Root node not found (%s)\n", rootname);
		}

		int res = 0;
		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)"value");
				res = atoi((const char*)xres);
				xmlFree(xres);
			}
		}
		return res;
	}
	else
	{
		Logger::Log("Error on Loading Config.xml\n");
		return 0;
	}
}

std::string Config::GetStr(char* fieldname)
{
	if (doc)
	{
		root = xmlDocGetRootElement(doc);
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0){
			xmlFreeDoc(doc);
			Logger::Log("Error on Loading Config.xml, Root node not found (%s)\n", rootname);
		}

		std::string res;
		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)"value");
				res.append((const char*)xres);
				xmlFree(xres);
			}
		}
		return res;
	}
	else
	{
		Logger::Log("Error on Loading Config.xml\n");
		return nullptr;
	}
}