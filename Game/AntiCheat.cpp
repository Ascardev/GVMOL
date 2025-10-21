#include "sinbaram\sinLinkHeader.h"
#include ".\apihook.h"
#include <TlHelp32.h>

#include <windows.h>
#include <stdio.h>
#include <Psapi.h>

typedef HANDLE(WINAPI* NewCreateThread)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, PVOID, DWORD, LPDWORD);
API_HOOK CTHook;

DWORD CheckSumSinSetLife = 0;
DWORD CheckSumSinSetMana = 0;
DWORD CheckSumSinSetStamina = 0;
DWORD CheckSumGetAttackSpeedMainFrame = 0;

DWORD dwTime = 0;

DWORD GetChecksum(DWORD Func, int size)
{
	DWORD CheckSum = 0;
	BYTE* Seila = (BYTE*)Func;
	for (int i = 0; i < size; i++)
	{
		CheckSum += Seila[i];
	}

	return CheckSum;
}

HANDLE WINAPI ProtectCT(LPSECURITY_ATTRIBUTES ThreadAttr, SIZE_T StackSize, LPTHREAD_START_ROUTINE StartAddress, PVOID Parameter, DWORD flags, LPDWORD ThreadId)
{
	DWORD TID;
	NewCreateThread fnCreateThread = (NewCreateThread)CTHook.OrigFunction;
	if (ThreadAttr == 0 && StackSize == 0 && Parameter == 0)
		return 0;
	else
		return fnCreateThread(ThreadAttr, StackSize, StartAddress, Parameter, flags, &TID);
}

DWORD ThreadId;

void MainThread()
{
	while (true)
	{
		AntiCheat::GetInstance()->Main();
	}
}

void AntiDebugger()
{
	HMODULE h = LoadLibraryA("ntdll.dll");
	if (h)
	{
		DWORD d = (DWORD)GetProcAddress(h, "DbgUiRemoteBreakin");
		if (d)
		{
			DWORD dold = 0;
			VirtualProtect((void*)d, 8, PAGE_EXECUTE_READWRITE, &dold);
			(*(DWORD*)d) = 0x6A6A6A6A;
			VirtualProtect((void*)d, 8, dold, NULL);
		}
	}
}
smWINSOCK* lpsmSock = NULL;

void AntiCheat::Init()
{
	//lpsmSock = ConnectServer_GameMain("127.0.0.1",
	//	TCP_SERVPORT,
	//	"127.0.0.1",
	//	TCP_SERVPORT,
	//	"127.0.0.1",
	//	TCP_SERVPORT);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, &ThreadId);
	InitAPIHook(&CTHook, "kernel32.dll", "CreateThread", ProtectCT);
	StartAPIHook(&CTHook);
	AntiDebugger();

	CheckSumSinSetLife = GetChecksum((DWORD)sinSetLife, 0x66);
	CheckSumSinSetMana = GetChecksum((DWORD)sinSetMana, 0x53);
	CheckSumSinSetStamina = GetChecksum((DWORD)sinSetStamina, 0x53);
	CheckSumGetAttackSpeedMainFrame = GetChecksum((DWORD)GetAttackSpeedMainFrame, 0x1F);
}

void AntiCheat::Main()
{
	if (IsDebuggerPresent())
	{
		ExitProcess(0);
	}

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnap, &pe32))
		{
			do {
				if (strstr(pe32.szExeFile, "cheatengine") || strstr(pe32.szExeFile, "OLLYDBG"))
				{
					ExitProcess(0);
				}
			} while (Process32Next(hSnap, &pe32));
		}
		CloseHandle(hSnap);
	}

	//HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	//DWORD dwModuleBaseAddress = 0;
	//if (hSnapshot != INVALID_HANDLE_VALUE)
	//{
	//	MODULEENTRY32 ModuleEntry32 = { 0 };
	//	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
	//	if (Module32First(hSnapshot, &ModuleEntry32))
	//	{
	//		do
	//		{
	//			if (!strstr(ModuleEntry32.szExePath, "Windows") && !strstr(ModuleEntry32.szExePath, "WINDOWS"))
	//			{
	//				if (lstrcmp(ModuleEntry32.szModule, "game.exe") != 0 &&
	//					lstrcmp(ModuleEntry32.szModule, "d3dx9_43.dll") != 0
	//					&& lstrcmp(ModuleEntry32.szModule, "tv_w32.dll") != 0
	//					&& lstrcmp(ModuleEntry32.szModule, "mdnsNSP.dll") != 0)
	//				{
	//				/*	smTRANS_CHAR_COMMAND2 ps;
	//					ps.size = sizeof(smTRANS_CHAR_COMMAND);
	//					ps.code = smTRANSCODE_MODULES;
	//					lstrcpy(ps.szName, ModuleEntry32.szModule);

	//					if (lpsmSock)
	//					{
	//						lpsmSock->Send((char*)&ps, ps.size, TRUE);
	//					}*/
	//				}
	//			}

	//		} while (Module32Next(hSnapshot, &ModuleEntry32));
	//	}
	//	CloseHandle(hSnapshot);
	//}

	if (CheckSumSinSetLife != GetChecksum((DWORD)sinSetLife, 0x66))
		ExitProcess(0);
	if (CheckSumSinSetMana != GetChecksum((DWORD)sinSetMana, 0x53))
		ExitProcess(0);
	if (CheckSumSinSetStamina != GetChecksum((DWORD)sinSetStamina, 0x53))
		ExitProcess(0);
	if (CheckSumGetAttackSpeedMainFrame != GetChecksum((DWORD)GetAttackSpeedMainFrame, 0x1F))
		ExitProcess(0);
}