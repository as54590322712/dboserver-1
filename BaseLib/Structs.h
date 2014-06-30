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

#pragma pack()

#endif