#include "stdafx.h"
#include "Config.h"

Config::Config(const char* rname)
{
	char filename[MAX_PATH];
	sprintf_s(filename, MAX_PATH, "%sConfig.xml", rname);
	doc = xmlParseFile(filename);
	rootname = _strdup(rname);
}

Config::~Config()
{
	xmlFreeDoc(doc);
}

int Config::GetInt(char* fieldname)
{
	return GetInt(fieldname, "value");
}

int Config::GetInt(char* fieldname, char* valuename)
{
	if (doc)
	{
		root = xmlDocGetRootElement(doc);
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0){
			xmlFreeDoc(doc);
			Logger::Log("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)valuename);
				if (xres)
				{
					return atoi((const char*)xres);
					xmlFree(xres);
				}
			}
		}
		return -1;
	}
	else
	{
		Logger::Log("Error on Loading Config xml File\n");
		return -1;
	}
}

char* Config::GetStr(char* fieldname)
{
	return GetStr(fieldname, "value");
}

char* Config::GetStr(char* fieldname, char* valuename)
{
	if (doc)
	{
		root = xmlDocGetRootElement(doc);
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0){
			xmlFreeDoc(doc);
			Logger::Log("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)fieldname) == 0)
			{
				xmlChar* xres = xmlGetProp(node, (const xmlChar*)valuename);
				if (xres)
				{
					return (char*)xres;
					xmlFree(xres);
				}
			}
		}
		return "";
	}
	else
	{
		Logger::Log("Error on Loading Config xml File\n");
		return "";
	}
}

int Config::GetChildInt(char* child, char* fieldname)
{
	return GetChildInt(child, fieldname, "value");
}

int Config::GetChildInt(char* child, char* fieldname, char* valuename)
{
	if (doc)
	{
		root = xmlDocGetRootElement(doc);
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0){
			xmlFreeDoc(doc);
			Logger::Log("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)child) == 0)
			{
				xmlNodePtr cnode;
				for (cnode = node->children; cnode; cnode = cnode->next)
				{
					if (xmlStrcmp(cnode->name, (const xmlChar*)fieldname) == 0)
					{
						xmlChar* xres = xmlGetProp(cnode, (const xmlChar*)valuename);
						if (xres)
						{
							return atoi((const char*)xres);
							xmlFree(xres);
						}
					}
				}
			}
		}
		return -1;
	}
	else
	{
		Logger::Log("Error on Loading Config xml File\n");
		return -1;
	}
}

char* Config::GetChildStr(char* child, char* fieldname)
{
	return GetChildStr(child, fieldname, "value");
}

char* Config::GetChildStr(char* child, char* fieldname, char* valuename)
{
	if (doc)
	{
		root = xmlDocGetRootElement(doc);
		if (xmlStrcmp(root->name, (const xmlChar*)rootname) != 0){
			xmlFreeDoc(doc);
			Logger::Log("Error on Loading Config xml File, Root node not found (%s)\n", rootname);
		}

		for (node = root->children; node; node = node->next)
		{
			if (xmlStrcmp(node->name, (const xmlChar*)child) == 0)
			{
				xmlNodePtr cnode;
				for (cnode = node->children; cnode; cnode = cnode->next)
				{
					if (xmlStrcmp(cnode->name, (const xmlChar*)fieldname) == 0)
					{
						xmlChar* xres = xmlGetProp(cnode, (const xmlChar*)valuename);
						if (xres)
						{
							return (char*)xres;
							xmlFree(xres);
						}
					}
				}
			}
		}
		return "";
	}
	else
	{
		Logger::Log("Error on Loading Config xml File\n");
		return "";
	}
}