#ifndef _NEWBIETABLE
#define _NEWBIETABLE

#pragma once

#include "Base.h"
#include "Table.h"

#pragma pack(push, 4)
typedef struct NewbieData {
	unsigned int tblIndex;
	BYTE Race;
	BYTE Class;
	unsigned int worldId;
	unsigned int tut_worldId;
	sVECTOR3 spawnLoc;
	sVECTOR3 spawnDir;
	sVECTOR3 bindLoc;
	sVECTOR3 bindDir;
	unsigned int itemId[NTL_MAX_NEWBIE_ITEM];
	BYTE itemSlot[NTL_MAX_NEWBIE_ITEM];
	BYTE itemStack[NTL_MAX_NEWBIE_ITEM];
	unsigned int mapNameTblId;
	unsigned int SkillsIds[NTL_MAX_NEWBIE_SKILL];
	sNEWBIE_QUICKSLOT_DATA QuickSlotData[NTL_MAX_NEWBIE_QUICKSLOT_COUNT];
	BYTE defaultPortalTblId;
	unsigned int qItemTblidx1;
	BYTE QPosition1;
	BYTE QStackQuantity1;
} NewbieData;
#pragma pack(pop)

class NewbieTable : public Table
{
public:
	NewbieTable() {};
	~NewbieTable() {};
	int Load(char* file);
	NewbieData GetData(BYTE Race, BYTE Class);
};

#endif