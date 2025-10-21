#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <io.h>
#else
#include <dlfcn.h>
#include <unistd.h>
#endif

#include "XTrap4Server.h"

PFN_XTrap_S_Start			XTrap_S_Start = 0;
PFN_XTrap_S_SessionInit	XTrap_S_SessionInit = 0;
PFN_XTrap_CS_Step1			XTrap_CS_Step1 = 0;
PFN_XTrap_CS_Step3			XTrap_CS_Step3 = 0;
PFN_XTrap_S_SessionReset	XTrap_S_SessionReset = 0;
PFN_XTrap_S_SetModuleOn	XTrap_S_SetModuleOn = 0;
PFN_XTrap_S_SetModuleOff	XTrap_S_SetModuleOff = 0;
PFN_XTrap_S_SaveLog		XTrap_S_SaveLog = 0;

void* hXTrap4Server = 0;

#ifdef _WIN32

unsigned long XTrap_S_LoadDll()
{
	unsigned long	ulError = 0;
	char			sDllBinFile[] = "XTrap4Server.Dll";

	hXTrap4Server = LoadLibrary(sDllBinFile);
	if (hXTrap4Server == NULL)
	{		ulError = GetLastError();	return 0x10000000 | ulError;	}

	XTrap_S_Start = (PFN_XTrap_S_Start)GetProcAddress(hXTrap4Server, "XTrap_S_Start");
	XTrap_S_SessionInit = (PFN_XTrap_S_SessionInit)GetProcAddress(hXTrap4Server, "XTrap_S_SessionInit");
	XTrap_CS_Step1 = (PFN_XTrap_CS_Step1)GetProcAddress(hXTrap4Server, "XTrap_CS_Step1");
	XTrap_CS_Step3 = (PFN_XTrap_CS_Step3)GetProcAddress(hXTrap4Server, "XTrap_CS_Step3");
	XTrap_S_SessionReset = (PFN_XTrap_S_SessionReset)GetProcAddress(hXTrap4Server, "XTrap_S_SessionReset");
	XTrap_S_SetModuleOn = (PFN_XTrap_S_SetModuleOn)GetProcAddress(hXTrap4Server, "XTrap_S_SetModuleOn");
	XTrap_S_SetModuleOff = (PFN_XTrap_S_SetModuleOff)GetProcAddress(hXTrap4Server, "XTrap_S_SetModuleOff");
	XTrap_S_SaveLog = (PFN_XTrap_S_SaveLog)GetProcAddress(hXTrap4Server, "XTrap_S_SaveLog");

	if ((XTrap_S_Start == NULL) ||
		(XTrap_S_SessionInit == NULL) ||
		(XTrap_CS_Step1 == NULL) ||
		(XTrap_CS_Step3 == NULL) ||
		(XTrap_S_SessionReset == NULL) ||
		(XTrap_S_SetModuleOn == NULL) ||
		(XTrap_S_SetModuleOff == NULL) ||
		(XTrap_S_SetModuleOff == NULL))
	{
		return	0x20000000;
	}

	return XTRAP_API_RETURN_OK;
}

unsigned long XTrap_S_FreeDll()
{
	if (hXTrap4Server)
		FreeLibrary(hXTrap4Server);

	return XTRAP_API_RETURN_OK;
}

#else

unsigned long XTrap_S_LoadDll()
{
	unsigned long	ulError = 0;
	char			sDllBinFile[] = "./libXTrap4Server.so";

	hXTrap4Server = dlopen(sDllBinFile, RTLD_LAZY);

	if (hXTrap4Server == 0) {
		printf("dlopen error %s\n", dlerror());
		return 0x10000000 | (unsigned long)ulError;
	}

	XTrap_S_Start = (PFN_XTrap_S_Start)dlsym(hXTrap4Server, "XTrap_S_Start");
	XTrap_S_SessionInit = (PFN_XTrap_S_SessionInit)dlsym(hXTrap4Server, "XTrap_S_SessionInit");
	XTrap_CS_Step1 = (PFN_XTrap_CS_Step1)dlsym(hXTrap4Server, "XTrap_CS_Step1");
	XTrap_CS_Step3 = (PFN_XTrap_CS_Step3)dlsym(hXTrap4Server, "XTrap_CS_Step3");
	XTrap_S_SessionReset = (PFN_XTrap_S_SessionReset)dlsym(hXTrap4Server, "XTrap_S_SessionReset");
	XTrap_S_SetModuleOn = (PFN_XTrap_S_SetModuleOn)dlsym(hXTrap4Server, "XTrap_S_SetModuleOn");
	XTrap_S_SetModuleOff = (PFN_XTrap_S_SetModuleOff)dlsym(hXTrap4Server, "XTrap_S_SetModuleOff");
	XTrap_S_SaveLog = (PFN_XTrap_S_SaveLog)dlsym(hXTrap4Server, "XTrap_S_SaveLog");

	if ((XTrap_S_Start == 0) ||
		(XTrap_S_SessionInit == 0) ||
		(XTrap_CS_Step1 == 0) ||
		(XTrap_CS_Step3 == 0) ||
		(XTrap_S_SessionReset == 0) ||
		(XTrap_S_SetModuleOn == 0) ||
		(XTrap_S_SetModuleOff == 0))
	{
		return	0x20000000;
	}

	return XTRAP_API_RETURN_OK;
}

unsigned long XTrap_S_FreeDll()
{

	if (hXTrap4Server)
		dlclose(hXTrap4Server);

	return XTRAP_API_RETURN_OK;
}

#endif



unsigned long XTrap_S_LoadCMF(void* pBuf, unsigned long ulSize, unsigned long ulCount, char* pFileName, unsigned long ulMax)
{
	unsigned long	ulfcnt = 0;
	unsigned long	ulbcnt = 0;
	unsigned long	ulRead = 0;

	FILE* fi = 0;
	char	sFileName[1024] = { 0, };

	for (ulfcnt = ulMax; ulfcnt >= 0; ulfcnt--)
	{
		sprintf(sFileName, pFileName, ulfcnt);

		if (access(sFileName, 0) == 0)
		{
			fi = fopen(sFileName, "rb");
			if (fi == NULL)
				return -1;

			ulRead = fread((unsigned char*)((unsigned char*)pBuf + ulbcnt * ulSize), ulSize, 1, fi);
			if (ulRead != 1)
				return -1;

			if (fclose(fi))
				return -1;

			ulbcnt++;

			if (ulbcnt == ulCount)
				break;
		}
	}

	return 0;
}

// ex )
//
// XTrap_S_LoadCMF(g_sMapBuffer, XTRAP_CS4_BUFSIZE_MAP, 2, "map%d.cs3", 255);
//
// LOAD  map1.cs3 ~ map255.cs3 