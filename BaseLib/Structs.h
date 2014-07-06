#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#pragma once

#include "Def.h"

enum SERVERSTATUS
{
	SERVERSTATUS_UP = 0,
	SERVERSTATUS_DOWN,
	SERVERSTATUS_LOCKED
};

enum EQUIP_SLOTTYPE
{
	EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_SUB_WEAPON,
	EQUIP_SLOT_TYPE_JACKET,
	EQUIP_SLOT_TYPE_PANTS,
	EQUIP_SLOT_TYPE_BOOTS,
	EQUIP_SLOT_TYPE_SCOUTER,
	EQUIP_SLOT_TYPE_COSTUME,
	EQUIP_SLOT_TYPE_NECKLACE,
	EQUIP_SLOT_TYPE_EARRING_1,
	EQUIP_SLOT_TYPE_EARRING_2,
	EQUIP_SLOT_TYPE_RING_1,
	EQUIP_SLOT_TYPE_RING_2,

	EQUIP_SLOT_TYPE_COUNT,
	EQUIP_SLOT_TYPE_UNKNOWN = 0xFF,

	EQUIP_SLOT_TYPE_FIRST = EQUIP_SLOT_TYPE_HAND,
	EQUIP_SLOT_TYPE_LAST = EQUIP_SLOT_TYPE_RING_2,
};

#pragma pack(1)

struct GAMESERVER_INFO
{
	GAMESERVER_INFO() :
		serverId(INVALID_SERVERID),
		ServerStatus(SERVERSTATUS_DOWN),
		MaxLoad(0),
		Load(0)
	{
		::SecureZeroMemory(ServerName, sizeof(ServerName));
	};

	BYTE serverId;
	WCHAR ServerName[MAX_SERVERNAME_SIZE + 1];
	BYTE ServerStatus;
	DWORD MaxLoad;
	DWORD Load;
};

struct GAMECHANNEL_INFO
{
	GAMECHANNEL_INFO() :
		serverId(INVALID_SERVERID),
		ChannelId(INVALID_SLOTID),
		IsVisible(true),
		ServerStatus(SERVERSTATUS_DOWN),
		MaxLoad(0),
		Load(0)
	{
	};

	BYTE serverId;
	BYTE ChannelId;
	bool IsVisible;
	BYTE ServerStatus;
	DWORD MaxLoad;
	DWORD Load;
};

struct ITEMDATA
{
	int tblidx;
	BYTE Rank;
	BYTE Grade;
	BYTE BattleAttribute;
	int OptionTblidx[MAX_ITEM_OPTION];
};

struct MARKING
{
	BYTE Code;
public:
	MARKING()
		: Code(INVALID_MARKING_TYPE)
	{
	}
};

struct DOGIDATA
{
	bool IsIntialized(bool IsDojo)
	{
		if (IsDojo)
		{
			if (INVALID_BYTE == DojoColor) return false;
			else return true;
		}
		else
		{
			if (INVALID_BYTE == GuildColor) return false;
			else return true;
		}
	}
	int guildId;
	BYTE Type;
	BYTE GuildColor;
	BYTE DojoColor;
};

struct CHARDATA
{
	int charId;
	WCHAR Name[MAX_CHARNAME_SIZE + 1];
	BYTE Race;
	BYTE Class;
	bool IsAdult;
	BYTE Gender;
	BYTE Face;
	BYTE Hair;
	BYTE HairColor;
	BYTE SkinColor;
	BYTE Level;
	int worldTblidx;
	int worldId;
	float PositionX;
	float PositionY;
	float PositionZ;
	DWORD Money;
	DWORD MoneyBank;
	ITEMDATA Item[EQUIP_SLOT_TYPE_COUNT];
	DWORD MapInfoId;
	bool TutorialFlag;
	MARKING Marking;
	bool NeedNameChange;
	DOGIDATA Dogi;
};

struct TODEL_CHARINFO
{
	int charId;
	DWORD PastTick;
};

#pragma pack()

#endif