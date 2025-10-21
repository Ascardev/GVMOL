#include <windows.h>
#include "..\\language.h"

#ifndef	_npGAME_GUARD

#include "nProtect.h"
#include <process.h>
#include "psapi.h"
#include "npfgmsdk.h"

class nP nPro;

#define WM_NPROTECT_EXIT_TWO  (WM_USER + 10001)

char securetext[6][20] = {
	{-103,-106,-111,-101,-105,-98,-100,-108,-47,-102,-121,-102,-1,-1,-1,-1,-6,-1,-1,-1},
	{-79,-81,-68,-73,-76,-47,-69,-77,-77,-1,120,101,0,0,0,0,5,0,0,0},
	{-68,-105,-102,-100,-108,-68,-83,-68,-1,0,-121,-102,-1,-1,-1,-1,-6,-1,-1,-1},
	{-111,-113,-110,-112,-111,-47,-102,-121,-102,-1,120,101,0,0,0,0,5,0,0,0},
	{-79,-81,-81,-84,-76,-47,-69,-77,-77,-1,-121,-102,-1,-1,-1,-1,-6,-1,-1,-1},
	{-76,-106,-109,-109,-85,-98,-116,-108,-1,0,120,101,0,0,0,0,5,0,0,0} };

char pass_char[6][20];

nP::nP()
{
}

nP::~nP()
{
}

void nP::Init()
{
	for (int j = 0; j < 6; j++) for (int i = 0; i < 20; i++) pass_char[j][i] = securetext[j][i] ^ 0xff;
}

int nP::NProtectCheck(void)
{
	nPro.Init();

	char sz_SystemFolder[256], sz_buf[256];

	GetSystemDirectory(sz_SystemFolder, 256);
	strcpy(sz_buf, sz_SystemFolder);
	strcat(sz_buf, "\\");
	strcat(sz_buf, pass_char[3]);

	if (!CheckCRC(sz_buf))
	{
		return 3;
	}
	else
		return 0;

	if (CheckCRC(pass_char[0]))
	{
		return 3;
	}
	else
		return 0;

	if (m_hInstDll == NULL)
	{
		m_hInstDll = LoadLibrary(pass_char[1]);
		if (m_hInstDll == NULL)
		{
			return 1;
		}
		else
		{
			pFunc_npchk = (bool(*)(char*))GetProcAddress(m_hInstDll, pass_char[2]);

			if (pFunc_npchk == NULL)
			{
				return  2;
			}

			if (pass_char[0] != "")
			{
				if (pFunc_npchk(pass_char[0])) {
				}
				else {
					return 3;
				}
			}
		}
	}

	if (m_hInstDll != NULL)
	{
		if (FreeLibrary(m_hInstDll)) {
			m_hInstDll = NULL;
		}
		else {
			return 4;
		}
	}
	return 0;
}

int nP::NProtectRun(void)
{
	nPro.Init();

	result = (int)spawnl(P_WAIT, pass_char[0], pass_char[0], NULL);
	SendMessage(FindWindow(NULL, "WWW.NPROTECT.COM"), WM_NPROTECT_EXIT_TWO, NULL, NULL);
	return result;
}

int nP::NProtectFree(void)
{
	nPro.Init();

	if (m_hInstDll == NULL)
	{
		m_hInstDll = LoadLibrary(pass_char[4]);
		if (m_hInstDll == NULL)
		{
			return 1;
		}
		else
		{
			pFunc_npkill = (int(*)(char*))GetProcAddress(m_hInstDll, pass_char[5]);

			if (pFunc_npkill == NULL)
			{
				return 2;
			}

			if (pass_char[3] != "")
			{
				temp = pFunc_npkill(pass_char[3]);

				if (temp != 0) {
				}
				else {
					return 5;
				}
			}
		}
	}

	if (m_hInstDll != NULL)
	{
		if (FreeLibrary(m_hInstDll)) {
			m_hInstDll = NULL;
		}
		else {
			return 4;
		}
	}
	return 0;
}

int nP::findNPMON()
{
	char findnpmon_secure[2][20] = {
	{-88,-88,-88,-47,-79,-81,-83,-80,-85,-70,-68,-85,-47,-68,-80,-78,-1,-1,-1,-1},
	{-85,-103,-115,-110,-79,-81,-78,-80,-79,-1,67,84,46,67,79,77,0,0,0,0}
	};
	char findnpmon_read[2][20];

	for (int j = 0; j < 2; j++) for (int i = 0; i < 20; i++) findnpmon_read[j][i] = findnpmon_secure[j][i] ^ 0xff;

	HWND hwnd;

	hwnd = FindWindow(findnpmon_read[1], findnpmon_read[0]);
	if (hwnd != 0) {
		return 0;
	}
	else {
		return 1;
	}

	return 0;
}

BOOL nP::CheckCRC(char* FilePath)
{
	BOOL dOutput;
	HINSTANCE m_hDll;

	if ((m_hDll = LoadLibrary("npchk.dll")) == NULL)
	{
		return FALSE;
	}

	pCheckCRC = (MYCHECKCRC*)GetProcAddress(m_hDll, "CheckCRC");
	dOutput = (*pCheckCRC)((LPTSTR)(LPCTSTR)FilePath);

	if (dOutput)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL nP::NPGetWindowsVersion()
{
	OSVERSIONINFO VersionInfo;
	BOOL Result;

	VersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	Result = GetVersionEx(&VersionInfo);

	if (Result == FALSE)
		return FALSE;

	if (VersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
		IsNT = TRUE;
	else
		IsNT = FALSE;

	return TRUE;
}

BOOL nP::NPMyLoadLibraryNPFGM()
{
	if (IsNT)
		hInstanceNPFGM = LoadLibrary(NPFGM_NT);
	else
		hInstanceNPFGM = LoadLibrary(NPFGM_9X);

	if (hInstanceNPFGM == NULL)
		return FALSE;

	if (((pEnterProtect = (EnterProtect)GetProcAddress(hInstanceNPFGM, "EnterProtect")) == NULL) ||
		((pReleaseProtect = (ReleaseProtect)GetProcAddress(hInstanceNPFGM, "ReleaseProtect")) == NULL)
		)
		return FALSE;
	else
		return TRUE;
}

BOOL nP::NPEnterProtect()
{
	if (m_bStart = pEnterProtect())
		return TRUE;
	else
		return FALSE;
}

BOOL nP::NPReleaseProtect()
{
	if (pReleaseProtect())
		return TRUE;
	else
		return FALSE;
}

BOOL nP::NPFindSICEProtect()
{
	hInstanceNPFSICE = LoadLibrary(NPFGM_NT);
	if (hInstanceNPFSICE != NULL)
	{
		if ((pnPFindSICE = (nPFindSICE)GetProcAddress(hInstanceNPFSICE, "nPFindSICE")) != NULL)
		{
			if (pnPFindSICE())
				return FALSE;
			else
				return TRUE;
		}
	}

	FreeLibrary(hInstanceNPFSICE);
	return TRUE;
}

void nP::NPFreeLib()
{
	if (m_bStart) {
		pReleaseProtect();
		FreeLibrary(hInstanceNPFGM);
	}
}

#endif