#include "Table.h"

using namespace std;

int Table::LoadFile(char* file, unsigned int size)
{
	unsigned char padding;
	ifstream tblFile(file, ios::in | ios::binary);
	if (tblFile && tblFile.is_open())
	{
		tblFile.read((char*)&datasize, sizeof(datasize));
		tblFile.read((char*)&padding, sizeof(padding));
		vector<unsigned char> data(datasize);
		filedata.resize(datasize);
		tblFile.read((char*)data.data(), datasize);
		memcpy(filedata.data(), data.data(), datasize);
	}
	tblFile.close();
	return 0;
}