#include "NewbieTable.h"

int NewbieTable::Load(char* file)
{
	return LoadFile(file, sizeof(NewbieData));
}

NewbieData NewbieTable::GetData(BYTE Race, BYTE Class)
{
	NewbieData tData;
	memset(&tData, 0, sizeof(tData));
	for (unsigned int x = 0; x < datasize; x += sizeof(NewbieData))
	{
		std::vector<unsigned char> record(sizeof(NewbieData));
		memcpy(record.data(), &filedata.data()[x], sizeof(NewbieData));
		memcpy(&tData, record.data(), sizeof(tData));
		if ((Race == tData.Race) && (Class == tData.Class))
			return tData;
		else memset(&tData, 0, sizeof(tData));
	}
	return tData;
}