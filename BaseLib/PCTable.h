#ifndef _PCTABLE
#define _PCTABLE

#include "Table.h"

#pragma pack(push, 4)
typedef struct PCData
{
	unsigned int TblIndex;
	WORD Basic_LP;
	WORD Basic_EP;
	WORD Basic_Physical_Defence;
	WORD Basic_Energy_Defence;
	BYTE Str;
	BYTE Con;
	BYTE Foc;
	BYTE Dex;
	BYTE Sol;
	BYTE Eng;
	float Scale;
	WORD Attack_Speed_Rate;
	BYTE Attack_Type;
	float Attack_Range;
	WORD Attack_Rate;
	WORD Dodge_Rate;
	WORD Block_Rate;
	WORD Curse_Success_Rate;
	WORD Curse_Tolerance_Rate;
	float Radius;
	WORD Basic_Aggro_Point;
	WORD dummy; // To read Race, Gender and Class correctly
	BYTE Race;
	BYTE Gender;
	BYTE Class;
	unsigned int prior_Class_Tblidx;
	DWORD Class_Bit_Flag;
	char Model_Child[33];
	char Model_Adult[33];
	float Child_Run_Speed_Origin;
	float Child_Run_Speed;
	float Adult_Run_Speed_Origin;
	float Adult_Run_Speed;
	WORD Basic_RP;
	WORD Basic_Physical_Offence;
	WORD Basic_Energy_Offence;
	BYTE Level_Up_LP;
	BYTE Level_Up_EP;
	BYTE Level_Up_RP;
	BYTE Level_Up_Physical_Offence;
	BYTE Level_Up_Physical_Defence;
	BYTE Level_Up_Energy_Offence;
	BYTE Level_Up_Energy_Defence;
	float Level_Up_Str;
	float Level_Up_Con;
	float Level_Up_Foc;
	float Level_Up_Dex;
	float Level_Up_Sol;
	float Level_Up_Eng;
} PCData;
#pragma pack(pop)

class PCTable : public Table
{
public:
	PCTable() {};
	~PCTable() {};
	int Load(char* file);
	PCData GetData(BYTE Race, BYTE Class, BYTE Gender);
};

#endif