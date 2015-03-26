#include "stdafx.h"
#include "Table.h"

using namespace std;

int Table::LoadFile(char* file, unsigned int size)
{
	unsigned char padding;
	ifstream tblFile(file, ios::in | ios::binary);
	tblFile.seekg(0, ios::end);
	int fsize = (int)tblFile.tellg();
	tblFile.seekg(0, ios::beg);
	char* data = new char[fsize];
	if (tblFile && tblFile.is_open())
	{
		tblFile.read(data, fsize);
		data = Decrypt(data, fsize);
		memcpy(&datasize, data, sizeof(datasize));
		memcpy(&padding, data, sizeof(padding));
		filedata.resize(datasize);
		memcpy(filedata.data(), &data[5], datasize);
	}
	tblFile.close();
	return 0;
}