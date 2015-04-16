#ifndef _SPAWNTABLE
#define _sPAWNTABLE

#pragma once

#include "Base.h"
#include "Table.h"
#include <list>

#pragma pack(push, 4)
struct SpawnData
{
	TBLIDX			tblidx;
	TBLIDX			mob_Tblidx;

	CNtlVector		vSpawn_Loc;
	CNtlVector		vSpawn_Dir;

	BYTE			bySpawn_Loc_Range;
	BYTE			bySpawn_Quantity;
	WORD			wSpawn_Cool_Time;
	BYTE			bySpawn_Move_Type;

	BYTE			byWander_Range;
	BYTE			byMove_Range;
	BYTE			byMove_DelayTime;

	TBLIDX			path_Table_Index;
	CNtlVector		vFollowDistance;

	TBLIDX			playScript;
	TBLIDX			playScriptScene;

	TBLIDX			aiScript;
	TBLIDX			aiScriptScene;

	DWORD			dwParty_Index;
	bool			bParty_Leader;

	SPAWNGROUPID	spawnGroupId;
};
#pragma pack(pop)

class SpawnTable : public Table
{
public:
	SpawnTable() {};
	~SpawnTable() {};

	int Load(char* file);
	int GetCount();
	SpawnData GetData(unsigned int tblidx);
	void GetData(std::list<SpawnData>& sList, SPAWNGROUPID spawnGroupId);
};

#endif