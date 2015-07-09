#ifndef _LOGGER_H
#define _LOGGER_H

#pragma once

#include "Base.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

#define	BLACK 0
#define BLUE 1
#define GREEN 2
#define	CYAN 3
#define	RED 4
#define	MAGENTA 5
#define BROWN 6
#define	LIGHTGRAY 7
#define	DARKGRAY 8
#define	LIGHTBLUE 9
#define	LIGHTGREEN 10
#define	LIGHTCYAN 11
#define	LIGHTRED 12
#define	LIGHTMAGENTA 13
#define	YELLOW 14
#define	WHITE 15

#define CONSOLECOLOR(p) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p);

namespace Logger
{
	void Log(char* szText, ...);
	void SavePacket(BYTE* pData);
};

#endif