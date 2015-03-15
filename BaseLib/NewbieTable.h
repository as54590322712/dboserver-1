#ifndef _NEWBIETABLE
#define _NEWBIETABLE

#include "Table.h"

#pragma pack(push, 4)
typedef struct NewbieData {
	unsigned int tblIndex;
	BYTE Race;
	BYTE Class;
	unsigned int worldId;
	unsigned int tut_worldId;
	VECTORXYZ spawnLoc;
	VECTORXYZ spawnDir;
	VECTORXYZ bindLoc;
	VECTORXYZ bindDir;
	unsigned int itemId[NEWBIE_ITEM_MAX];
	BYTE itemSlot[NEWBIE_ITEM_MAX];
	BYTE itemStack[NEWBIE_ITEM_MAX];
	unsigned int mapNameTblId;
	unsigned int SkillsIds[NEWBIE_SKILL_MAX];
	NEWBIE_QUICKSLOT_DATA QuickSlotData[NEWBIE_MAX_QUICKSLOT_COUNT];
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