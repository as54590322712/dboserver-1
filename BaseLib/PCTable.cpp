#include "PCTable.h"

int PCTable::Load(char* file)
{
	return LoadFile(file, sizeof(PCData));
}

PCData PCTable::GetData(BYTE Race, BYTE Class, BYTE Gender)
{
	PCData tData;
	memset(&tData, 0, sizeof(tData));
	for (unsigned int x = 0; x < datasize; x += sizeof(PCData))
	{
		std::vector<unsigned char> record(sizeof(PCData));
		memcpy(record.data(), &filedata.data()[x], sizeof(PCData));
		memcpy(&tData, record.data(), sizeof(tData));
		if ((Race == tData.Race) && (Class == tData.Class) && (Gender == tData.Gender))
			return tData;
		else memset(&tData, 0, sizeof(tData));
	}
	return tData;
}