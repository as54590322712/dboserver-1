#include "Logger.h"

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