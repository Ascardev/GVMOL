#ifndef __NPGAMELIB_H__
#define __NPGAMELIB_H__

#define NPGAMEMON_UNDEFINED            1000
#define NPGAMEMON_COMM_ERROR           1001
#define NPGAMEMON_COMM_CLOSE           1002

#define NPGAMEMON_SPEEDHACK            1011
#define NPGAMEMON_GAMEHACK_KILLED      1012
#define NPGAMEMON_GAMEHACK_DETECT      1013
#define NPGAMEMON_INIT_ERROR           1014
#define NPGAMEMON_GAMEHACK_DOUBT       1015
#define NPGAMEMON_CHECK_CSAUTH         1016
#define NPGAMEMON_CHECK_CSAUTH2        1017

#define NPGAMEMON_ERROR_EXIST          110
#define NPGAMEMON_ERROR_CREATE         111
#define NPGAMEMON_ERROR_NPSCAN         112
#define NPGAMEMON_ERROR_THREAD         113
#define NPGAMEMON_ERROR_INIT           114
#define NPGAMEMON_ERROR_GAME_EXIST     115
#define NPGAMEMON_ERROR_AUTH_INI       120
#define NPGAMEMON_ERROR_AUTH_NPGMUP    121
#define NPGAMEMON_ERROR_AUTH_GAMEMON   122
#define NPGAMEMON_ERROR_AUTH_NEWUP     123
#define NPGAMEMON_ERROR_AUTH_GAMEGUARD 124
#define NPGAMEMON_ERROR_DECRYPT        130
#define NPGAMEMON_ERROR_CORRUPT_INI    141
#define NPGAMEMON_ERROR_CORRUPT_INI2   142
#define NPGAMEMON_ERROR_NFOUND_INI     150
#define NPGAMEMON_ERROR_NFOUND_NPGMUP  151
#define NPGAMEMON_ERROR_NFOUND_NEWUP   152
#define NPGAMEMON_ERROR_NFOUND_GG      153
#define NPGAMEMON_ERROR_NFOUND_GM      154
#define NPGAMEMON_ERROR_CRYPTOAPI      155
#define NPGAMEMON_ERROR_COMM           160
#define NPGAMEMON_ERROR_EXECUTE        170
#define NPGAMEMON_ERROR_EVENT          171
#define NPGAMEMON_ERROR_NPGMUP         180
#define NPGAMEMON_ERROR_MOVE_INI       191
#define NPGAMEMON_ERROR_MOVE_NEWUP     192

#define NPGAMEMON_ERROR_ILLEGAL_PRG    200

#define NPGAMEMON_ERROR_GAMEMON        210
#define NPGAMEMON_ERROR_SPEEDCHECK     220
#define NPGAMEMON_ERROR_GAMEGUARD      230

#define NPGMUP_ERROR_DOWNCFG           340
#define NPGMUP_ERROR_ABORT             350
#define NPGMUP_ERROR_AUTH              360
#define NPGMUP_ERROR_AUTH_INI          361
#define NPGMUP_ERROR_DECRYPT           370
#define NPGMUP_ERROR_CONNECT           380
#define NPGMUP_ERROR_INI               390

extern const DWORD NPGAMEMON_SUCCESS;

typedef struct _GG_AUTH_DATA
{
	DWORD dwIndex;
	DWORD dwValue1;
	DWORD dwValue2;
	DWORD dwValue3;
} GG_AUTH_DATA, * PGG_AUTH_DATA;

DWORD __cdecl CheckNPGameMon();
bool  __cdecl CloseNPGameMon();
DWORD __cdecl InitNPGameMon();
void  __cdecl SetHwndToGameMon(HWND hWnd);
DWORD __cdecl PreInitNPGameMonA(LPCSTR szGameName);
DWORD __cdecl PreInitNPGameMonW(LPCWSTR szGameName);
bool  __cdecl SendUserIDToGameMonA(LPCSTR szUserID);
bool  __cdecl SendUserIDToGameMonW(LPCWSTR szUserID);
bool  __cdecl SendCSAuthToGameMon(DWORD dwAuth);
bool  __cdecl SendCSAuth2ToGameMon(PGG_AUTH_DATA pAuth);
char* __cdecl NPDect(char* lpszString);
BOOL  __cdecl NPGuardData(LPVOID lpData, DWORD dwSize);
BOOL  __cdecl NPReleaseData(LPVOID lpData, DWORD dwSize);
LPCSTR __cdecl GetInfoFromGameMon();

#ifdef _UNICODE
#define PreInitNPGameMon      PreInitNPGameMonW
#define SendUserIDToGameMon   SendUserIDToGameMonW
#else
#define PreInitNPGameMon      PreInitNPGameMonA
#define SendUserIDToGameMon   SendUserIDToGameMonA
#endif

#ifdef __cplusplus
extern "C" {
#endif

	DWORD __cdecl InitPacketProtect(LPCTSTR lpszUserKey);
	DWORD __cdecl EncryptPacket(LPVOID lpData, DWORD dwLength);
	DWORD __cdecl DecryptPacket(LPVOID lpData, DWORD dwLength);
	DWORD __cdecl EncryptPeerPacket(LPVOID lpData, DWORD dwLength);
	DWORD __cdecl DecryptPeerPacket(LPVOID lpData, DWORD dwLength);
	DWORD __cdecl PPGetLastError();

#ifdef __cplusplus
}
#endif

bool CALLBACK NPGameMonCallback(DWORD dwMsg, DWORD dwArg);

class CNPGameLib
{
public:
	explicit CNPGameLib(LPCTSTR lpszGameName)
	{
#ifdef NO_GAMEGUARD
		return;
#endif
		PreInitNPGameMon(lpszGameName);
	}
	~CNPGameLib()
	{
#ifdef NO_GAMEGUARD
		return;
#endif
		CloseNPGameMon();
	}

public:
	DWORD Init()
	{
#ifdef NO_GAMEGUARD
		return NPGAMEMON_SUCCESS;
#endif
		return (InitNPGameMon());
	}

	void SetHwnd(HWND hWnd)
	{
#ifdef NO_GAMEGUARD
		return;
#endif
		SetHwndToGameMon(hWnd);
	}

	DWORD Check()
	{
#ifdef NO_GAMEGUARD
		return NPGAMEMON_SUCCESS;
#endif
		return (CheckNPGameMon());
	}

	DWORD Send(LPCTSTR lpszUserId)
	{
#ifdef NO_GAMEGUARD
		return NPGAMEMON_SUCCESS;
#endif
		return (SendUserIDToGameMon(lpszUserId));
	}

	LPCSTR GetInfo()
	{
#ifdef NO_GAMEGUARD
		return NULL;
#endif
		return (GetInfoFromGameMon());
	}

	DWORD Auth(DWORD dwAuth)
	{
#ifdef NO_GAMEGUARD
		return NPGAMEMON_SUCCESS;
#endif
		return (SendCSAuthToGameMon(dwAuth));
	}

	DWORD Auth2(PGG_AUTH_DATA pAuth)
	{
#ifdef NO_GAMEGUARD
		return NPGAMEMON_SUCCESS;
#endif
		return (SendCSAuth2ToGameMon(pAuth));
	}

private:

	CNPGameLib(const CNPGameLib& rhs);
	CNPGameLib& operator=(const CNPGameLib& rhs);
};

class CNPDword
{
public:
	CNPDword();

	~CNPDword();
	DWORD Get();
	void Set(DWORD dwValue);

private:
	void Guard();
	void Release();

public:
	LPDWORD m_pValue;
	DWORD m_dwSize;
};

#endif
