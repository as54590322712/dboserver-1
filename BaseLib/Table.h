#ifndef _TABLE
#define _TABLE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <valarray>
#include <Crypto.h>
#include "Def.h"
#include "Logger.h"

class Table
{
public:
	Table() {};
	virtual ~Table() {};
	virtual int Load(char* file) { return 0; };
	std::vector<unsigned char> filedata;
	unsigned int datasize;
protected:
	int LoadFile(char* file, unsigned int size);
};

#endif