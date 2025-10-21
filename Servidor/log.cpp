#include "sinbaram\sinLinkHeader.h"
#include <strsafe.h>

void LOG(rsPLAYINFO* pcUser, char* pszLog, char* pszMessage)
{
	SYSTEMTIME sSystemTime;
	GetLocalTime(&sSystemTime);

	char szFileName[256], szErrorMessage[2048];
	if (StringCbPrintfA(szFileName, _countof(szFileName), "Logs\\[%s]%02d-%02d-%04d.log", pszLog, sSystemTime.wMonth, sSystemTime.wDay, sSystemTime.wYear) != S_OK)
		return;

	if (pcUser != NULL)
	{
		if (pcUser->lpsmSock)
			StringCbPrintfA(szErrorMessage, _countof(szErrorMessage), "@ %02d:%02d:%02d : [%s][%s][%s] -> %s\r\n", sSystemTime.wHour, sSystemTime.wMinute, sSystemTime.wSecond, pcUser->szID, pcUser->szName, pcUser->lpsmSock->szIPAddr, pszMessage);
		else
			StringCbPrintfA(szErrorMessage, _countof(szErrorMessage), "@ %02d:%02d:%02d : [%s][%s][disconnected] -> %s\r\n", sSystemTime.wHour, sSystemTime.wMinute, sSystemTime.wSecond, pcUser->szID, pcUser->szName, pszMessage);
	}
	else
		StringCbPrintfA(szErrorMessage, _countof(szErrorMessage), "@ %02d:%02d:%02d -> %s\r\n", sSystemTime.wHour, sSystemTime.wMinute, sSystemTime.wSecond, pszMessage);

	FILE* pFile;
	if (fopen_s(&pFile, szFileName, "a") == 0)
	{
		fputs(szErrorMessage, pFile);
		fclose(pFile);
	}
}

void LOGEx(rsPLAYINFO* pcUser, char* pszLog, char* pszFormat, ...)
{
	va_list vl;

	char szMessage[1024];

	va_start(vl, pszFormat);
	_vsnprintf_s(szMessage, _countof(szMessage), _TRUNCATE, pszFormat, vl);
	va_end(vl);

	LOG(pcUser, pszLog, szMessage);
}

void LOGEx(char* pszLog, char* pszFormat, ...)
{
	va_list vl;

	char szMessage[1024];

	va_start(vl, pszFormat);
	_vsnprintf_s(szMessage, _countof(szMessage), _TRUNCATE, pszFormat, vl);
	va_end(vl);

	LOG(NULL, pszLog, szMessage);
}