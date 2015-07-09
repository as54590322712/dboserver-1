#include "stdafx.h"
#include "Logger.h"
#include "Packet.h"

void Logger::Log(char* szText, ...)
{
	va_list args;
	va_start(args, szText);
	time_t rawtime;
	tm timeinfo;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	CONSOLECOLOR(YELLOW);
	printf(" %02d:%02d:%02d %02d-%02d ", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_min, timeinfo.tm_mday, ++timeinfo.tm_mon);
	CONSOLECOLOR(LIGHTCYAN);
	printf("> ");
	CONSOLECOLOR(LIGHTGRAY);
	vprintf_s(szText, args);
	va_end(args);
}

void Logger::SavePacket(BYTE* pData)
{
	try {
		WORD wLen = 0;
		memcpy(&wLen, &pData[0], 2);
		WORD wOpCode = 0;
		memcpy(&wOpCode, &pData[2], 2);

		if (GetFileAttributesA("./packets/") == INVALID_FILE_ATTRIBUTES)
		{
			_wmkdir(L"./packets/");
		}


		std::string filename = "";
		filename.append("./packets/packet_");
		filename.append(std::to_string(wOpCode));
		filename.append(".dat");

		std::ofstream fPacket(filename.c_str(), std::ios::out | std::ios::binary);
		fPacket.write((char*)pData, wLen + 2);
		fPacket.close();
	}
	catch (std::ofstream::failure e)
	{
		Logger::Log("Error writing packet: %s\n", e);
	}
}