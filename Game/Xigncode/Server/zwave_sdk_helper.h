#pragma once

#ifdef ZWAVE_SDK_HELPER_EXPORTS
#define ZWAVE_SDK_HELPER_API __declspec(dllexport)
#else
#define ZWAVE_SDK_HELPER_API __declspec(dllimport)
#endif

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#ifndef SOCKET
typedef UINT_PTR SOCKET;
#endif

#ifndef Z_RETURN
#define Z_RETURN
enum Z_RETURN
{
	Z_RTN_ERROR = -1,
	Z_RTN_NONE,
	Z_RTN_NONCLIENT,
	Z_RTN_BLACK_CODE,
	Z_RTN_SUSPICIOUS,
	Z_RTN_USERDEFINED,
	Z_RTN_RESEND
};
#endif

enum
{
	XIGNCODE_CLEAN = Z_RTN_NONE
	, XIGNCODE_NONCLIENT = Z_RTN_NONCLIENT
	, XIGNCODE_BLACKCODE = Z_RTN_BLACK_CODE
	, XIGNCODE_SUSPICIOUS = Z_RTN_SUSPICIOUS
	, XIGNCODE_USERDEFINED = Z_RTN_USERDEFINED
	, XIGNCODE_RESEND = Z_RTN_RESEND
	, XIGNCODE_TIMEOUT
};

typedef BOOL(WINAPI* FnSend)(SOCKET s, PVOID meta, LPCSTR buf, SIZE_T size);
typedef void (WINAPI* FnCallback)(SOCKET s, PVOID meta, int code, LPCTSTR report);

class IXigncodeServer
{
public:
	virtual BOOL OnBegin(LPCTSTR lic, SIZE_T blocksize = 512, LPCTSTR path = NULL) = 0;
	virtual BOOL OnEnd() = 0;
	virtual BOOL OnAccept(SOCKET s, PVOID meta) = 0;
	virtual BOOL OnDisconnect(SOCKET s) = 0;
	virtual BOOL OnRecieve(SOCKET s, LPCSTR buf, SIZE_T size) = 0;
	virtual DWORD GetRefCnt() = 0;
	virtual BOOL Release() = 0;
};

ZWAVE_SDK_HELPER_API BOOL WINAPI CreateXigncodeServer(IXigncodeServer** _interface, FnSend _pFnSend, FnCallback _pFnCallback);

typedef BOOL(WINAPI* PCREATE_XIGNCODE_SERVER)(
	IXigncodeServer** _interface
	, FnSend _pFnSend
	, FnCallback _pFnCallback
	);

inline PCREATE_XIGNCODE_SERVER LoadHelperDllW(wchar_t* pszPath)
{
	wchar_t szT[MAX_PATH];

	if (pszPath == NULL)
	{
		GetModuleFileNameW(NULL, szT, MAX_PATH);
		wchar_t* _p = wcsrchr(szT, '\\');
		if (_p++)
			*_p = 0x00;
	}
	else
		wcscpy(szT, pszPath);

	if (szT[wcslen(szT) - 1] != '\\') wcscat(szT, L"\\");
#ifdef _M_X64
	wcscat(szT, L"zwave_sdk_helper_x64.dll");
#else
	wcscat(szT, L"zwave_sdk_helper.dll");
#endif
	HMODULE h = LoadLibraryW(szT);
	if (h)
	{
		PCREATE_XIGNCODE_SERVER f = (PCREATE_XIGNCODE_SERVER)GetProcAddress(h, "CreateXigncodeServer");
		if (f) return f;
	}
	return NULL;
}

inline PCREATE_XIGNCODE_SERVER LoadHelperDllA(char* pszPath)
{
	if (pszPath == NULL) return NULL;
	size_t t = strlen(pszPath) + 1;
	wchar_t* _temp = new wchar_t[t * 2];
	MultiByteToWideChar(CP_ACP, 0, pszPath, -1, _temp, t * 2);
	PCREATE_XIGNCODE_SERVER f = LoadHelperDllW(_temp);
	delete[] _temp;
	return f;
}

#ifdef _UNICODE
#define LoadHelperDll LoadHelperDllW
#else
#define LoadHelperDll LoadHelperDllW
#endif
