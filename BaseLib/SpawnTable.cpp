#include "stdafx.h"
#include "SpawnTable.h"

int SpawnTable::Load(char* file)
{
	return LoadFile(file, sizeof(SpawnData));
}

int SpawnTable::GetCount()
{
	return (datasize / sizeof(SpawnData));
}

SpawnData SpawnTable::GetData(unsigned int tblidx)
{
	SpawnData tData;
	memset(&tData, 0, sizeof(tData));
	for (unsigned int x = 0; x < datasize; x += sizeof(SpawnData))
	{
		std::vector<unsigned char> record(sizeof(SpawnData));
		memcpy(record.data(), &filedata.data()[x], sizeof(SpawnData));
		memcpy(&tData, record.data(), sizeof(tData));
		if (tblidx == tData.tblidx)
			return tData;
		else memset(&tData, 0, sizeof(tData));
	}
	return tData;
}