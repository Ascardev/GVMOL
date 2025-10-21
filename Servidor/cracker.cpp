#include <windows.h>
#include <process.h>

#include "smlib3d\\smd3d.h"
#include "smwsock.h"
#include "smPacket.h"
#include "cracker.h"
#include "netplay.h"

char szFindCrackName[256];
static char szWindowName[71];
static char szClassName[31];
static char szAddString[101];

DWORD	dwExeCheckSum = 0;
char	szProcessPath[256] = { 0 };

#include "language.h"

extern	int quit;

int	CrDebug = 1;

BOOL CALLBACK EnumWndProc(HWND hWnd, LPARAM lParam)
{
	char* temp_Windowname[7] = { "»ý°¢ÇÏ´Â", "Game Mas" , "GameHack" ,
							"        " , "ô¸Íöñýàò" , "½ºÇÇµåÇÙ" };
	char* temp_Classname[4] = { "#3277" , "TWME1" , "#2770" };

	char GW_tempWindowname[9];
	char GW_tempClassname[6];

	int FindFlag = 0;

	GetWindowText(hWnd, szWindowName, 71);
	GetClassName(hWnd, szClassName, 30);

	ZeroMemory(GW_tempWindowname, sizeof(9));
	ZeroMemory(GW_tempClassname, sizeof(6));

	GetWindowText(hWnd, GW_tempWindowname, 9);
	GetClassName(hWnd, GW_tempClassname, 6);

	if ((strcmp(GW_tempWindowname, temp_Windowname[0]) == 0) && (strcmp(GW_tempClassname, temp_Classname[0]) == 0))
	{
		FindFlag++;
	}

	if ((strcmp(GW_tempWindowname, temp_Windowname[2]) == 0) && (strcmp(GW_tempClassname, temp_Classname[0]) == 0))
	{
		FindFlag++;
	}

	if ((strcmp(GW_tempWindowname, temp_Windowname[3]) == 0) && (strcmp(GW_tempClassname, temp_Classname[2]) == 0))
	{
		FindFlag++;
	}

	if ((strcmp(GW_tempWindowname, temp_Windowname[4]) == 0) && (strcmp(GW_tempClassname, temp_Classname[2]) == 0))
	{
		FindFlag++;
	}

	if ((strcmp(GW_tempWindowname, temp_Windowname[5]) == 0) && (strcmp(GW_tempClassname, temp_Classname[2]) == 0))
	{
		FindFlag++;
	}

	if ((strcmp(GW_tempWindowname, temp_Windowname[1]) == 0) && (strcmp(GW_tempClassname, temp_Classname[1]) == 0))
	{
		FindFlag++;
	}

	if (FindFlag)
		lstrcpy(szFindCrackName, szWindowName);

	return(TRUE);
}

char* FindCracker()
{
	szFindCrackName[0] = 0;
	EnumWindows((WNDENUMPROC)EnumWndProc, 0);

	if (szFindCrackName[0])
		return szFindCrackName;

	return NULL;
}

TRANS_FIND_CRACKER	TransFindCracker;

BOOL CALLBACK EnumFindCrackWndProc(HWND hWnd, LPARAM lParam)
{
	int FindFlag;
	int cnt;

	char _szWindowName[71];
	char _szClassName[31];

	GetWindowText(hWnd, szWindowName, 71);
	GetClassName(hWnd, szClassName, 30);

	lstrcpy(_szWindowName, szWindowName);
	lstrcpy(_szClassName, szClassName);

	CharLower(_szWindowName);
	CharLower(_szClassName);

	for (cnt = 0; cnt < TransFindCracker.FindCounter; cnt++) {
		FindFlag = 0;

		if (TransFindCracker.CrackName[cnt].szName1[0]) {
			FindFlag = 1;
			if (strstr(_szWindowName, TransFindCracker.CrackName[cnt].szName1) != 0) {
				if (TransFindCracker.CrackName[cnt].szName2[0]) {
					if (strstr(_szWindowName, TransFindCracker.CrackName[cnt].szName2) == 0) {
						FindFlag = 0;
					}
				}
			}
			else {
				FindFlag = 0;
			}

			if (TransFindCracker.CrackName[cnt].szClass[0]) {
				if (strstr(_szClassName, TransFindCracker.CrackName[cnt].szClass) == 0) {
					FindFlag = 0;
				}
			}
		}

		if (FindFlag) {
			lstrcpy(szFindCrackName, szWindowName);
			break;
		}
	}

	return(TRUE);
}

char* FindCracker(TRANS_FIND_CRACKER* lpTransFindCrack)
{
	int cnt;

	memcpy(&TransFindCracker, lpTransFindCrack, lpTransFindCrack->size);

	for (cnt = 0; cnt < TransFindCracker.FindCounter; cnt++) {
		CharLower(TransFindCracker.CrackName[cnt].szName1);
		CharLower(TransFindCracker.CrackName[cnt].szName2);
		CharLower(TransFindCracker.CrackName[cnt].szClass);
	}

	szFindCrackName[0] = 0;
	EnumWindows((WNDENUMPROC)EnumFindCrackWndProc, 0);

	if (szFindCrackName[0])
		return szFindCrackName;

	return NULL;
}

char* FindCrackCont()
{
	if (TransFindCracker.code != smTRANSCODE_FINDCRACK)
		return NULL;

	szFindCrackName[0] = 0;
	EnumWindows((WNDENUMPROC)EnumFindCrackWndProc, 0);

	if (szFindCrackName[0])
		return szFindCrackName;

	return NULL;
}

extern HWND	hwnd;

HWND hWnd_CrackFocus = 0;
DWORD	dwTime_CrackFocus = 0;

HWND WinFocusCrack()
{
	HWND	hWnd;
	DWORD	dwTime;

	hWnd = GetForegroundWindow();
	if (hWnd != hwnd) {
		dwTime = GetCurrentTime();

		if (!hWnd_CrackFocus) {
			hWnd_CrackFocus = hWnd;
			dwTime_CrackFocus = dwTime;
		}
		else {
			if ((dwTime_CrackFocus + 5000) < dwTime) {
				return hWnd;
			}
		}
	}
	else {
		hWnd_CrackFocus = 0;
	}

	return NULL;
}

#include "tlhelp32.h"

#define	CR_NAME		-9

char CrackProcess[][16] = {
	{ 'a' + CR_NAME,'r' + CR_NAME,'t' + CR_NAME,'m' + CR_NAME,'o' + CR_NAME,'n' + CR_NAME,'e' + CR_NAME, 0 },
	{ 'p' + CR_NAME,'a' + CR_NAME,'t' + CR_NAME,'c' + CR_NAME,'h' + CR_NAME, 0 },
	{ 0,0 }
};

char MyProcess[16] = {
	'.' + CR_NAME,'e' + CR_NAME,'x' + CR_NAME,'e' + CR_NAME, 0
};

char MyProcessName[64];

int CheckProcess(char* szProcessName)
{
	char szBuff1[64];
	int nCnt = 0;
	int cnt, len;

	lstrcpy(szBuff1, szProcessName);
	CharLower(szBuff1);
	len = lstrlen(szBuff1);
	for (cnt = 0; cnt < len; cnt++)
		szBuff1[cnt] += CR_NAME;

	while (1) {
		if (!CrackProcess[nCnt][0]) break;
		if (strstr(szBuff1, CrackProcess[nCnt]) != 0) {
			return TRUE;
		}
		nCnt++;
	}

	return NULL;
}

int CheckMyProcess(char* szProcessName)
{
	int nCnt = 0;
	int cnt, len;

	lstrcpy(MyProcessName, MyProcess);

	len = lstrlen(MyProcessName);
	for (cnt = 0; cnt < len; cnt++)
		MyProcessName[cnt] -= CR_NAME;

	return TRUE;
}

int MyEnumModule98(int pid);

DWORD Check_CodeSafe(DWORD dwStartFunc);
DWORD Check_CodeSafe2();

int CheckCrackProcess(int Flag)
{
	DWORD	ProcessID;
	int FindFlag = 0;

	ProcessID = GetCurrentProcessId();

	CheckMyProcess("game.exe");

	if (Flag)
		MyEnumModule98(ProcessID);

	return FindFlag;
}

int MyEnumModule98(int pid)
{
	HANDLE hSnap;
	MODULEENTRY32 me;
	char str[256];

	str[0] = 0;

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (hSnap == (HANDLE)-1)
		return FALSE;

	me.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnap, &me)) {
		do {
			CharLower(me.szExePath);
			if (strstr(me.szExePath, MyProcessName) != 0) {
				lstrcpy(str, me.szExePath);
			}
		} while (Module32Next(hSnap, &me));
	}
	CloseHandle(hSnap);

	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	DWORD* szFileBuff;
	int		cnt;
	int		dCnt;

	if (str[0]) {
		dwExeCheckSum = 0;
		hFile = CreateFile(str, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE) {
			FileLength = GetFileSize(hFile, NULL);

			szFileBuff = new DWORD[(FileLength / 4) + 256];
			ReadFile(hFile, szFileBuff, FileLength, &dwAcess, NULL);
			CloseHandle(hFile);

			dCnt = FileLength - 0x8000;
			dCnt /= 4;

			for (cnt = 0x1000; cnt < dCnt; cnt++) {
				dwExeCheckSum += szFileBuff[cnt] | (cnt * cnt * szFileBuff[cnt]);
				dwExeCheckSum += (szFileBuff[cnt] >> 16) + (szFileBuff[cnt] << 16);
			}
			if (!dwExeCheckSum) dwExeCheckSum = 1;
			delete szFileBuff;
		}
	}
	lstrcpy(szProcessPath, str);

	return TRUE;
}

DWORD	GetModuleCheckSum(char* szModule)
{
	DWORD	ProcessID;

	HANDLE hSnap;
	MODULEENTRY32 me;
	int cnt, len;
	DWORD ChkSum = 0;
	DWORD* lpBuff;

	ProcessID = GetCurrentProcessId();

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
	if (hSnap == (HANDLE)-1)
		return FALSE;

	me.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &me)) {
		do {
			if (lstrcmpi(me.szModule, szModule) == 0) {
				lpBuff = (DWORD*)me.modBaseAddr;

				len = me.modBaseSize / sizeof(DWORD);
				for (cnt = 0; cnt < len; cnt++) {
					ChkSum += lpBuff[cnt] * (cnt & 0xFFFF);
				}
			}
		} while (Module32Next(hSnap, &me));
	}
	CloseHandle(hSnap);

	return ChkSum;
}

int	CheckDLL_Module()
{
	DWORD	ProcessID;

	HANDLE hSnap;
	MODULEENTRY32 me;
	int len, cnt;
	DWORD ChkSum = 0;

	int		FindFlag[2] = { 0,0 };

	char	szBuff[256];
	char* lpBuff;

	TRANS_CHATMESSAGE	TransChatMessage;

	if (GetSystemDirectory(szBuff, 128) == NULL) return FALSE;

	len = lstrlen(szBuff);

	szBuff[len++] = '\\';

	lpBuff = szBuff + len;

	szBuff[len++] = 'w';
	szBuff[len++] = 's';
	szBuff[len++] = 'o';
	szBuff[len++] = 'c';
	szBuff[len++] = 'k';
	szBuff[len++] = '3';
	szBuff[len++] = '2';
	szBuff[len++] = '.';
	szBuff[len++] = 'd';
	szBuff[len++] = 'l';
	szBuff[len++] = 'l';
	szBuff[len] = 0;

	ProcessID = GetCurrentProcessId();

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
	if (hSnap == (HANDLE)-1)
		return FALSE;

	me.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &me)) {
		do {
			if (lstrcmpi(me.szExePath, szBuff) == 0) {
				FindFlag[0]++;
			}
			else {
				if (lstrcmpi(lpBuff, me.szModule) == 0) {
					FindFlag[1]++;
					lstrcpy(TransChatMessage.szMessage, me.szExePath);
					len = lstrlen(TransChatMessage.szMessage);
					TransChatMessage.dwIP = len;
					for (cnt = 0; cnt < len; cnt++)
						TransChatMessage.szMessage[cnt] ^= (cnt * 0x15);
				}
			}
		} while (Module32Next(hSnap, &me));
	}
	CloseHandle(hSnap);

	if (FindFlag[0] == 1 && FindFlag[1] == 0) return TRUE;

	if (FindFlag[1] > 0 && smWsockDataServer) {
		TransChatMessage.code = smTRANSCODE_MODULE_WARNIG;
		TransChatMessage.size = TransChatMessage.dwIP + 32;
		TransChatMessage.dwObjectSerial = 0;
		smWsockDataServer->Send2((char*)&TransChatMessage, TransChatMessage.size, TRUE);
	}

	return NULL;
}

#ifdef _LANGUAGE_CHINESE
#ifndef _W_SERVER

DWORD	dwNSpriteTime = 0;
extern DWORD dwPlayTime;
extern smWINSOCK* smWsockDataServer;

#endif
#endif