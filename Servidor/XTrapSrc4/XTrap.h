




#ifndef __XTRAPMODULE_H
#define __XTRAPMODULE_H





extern BOOL g_bApiMal;			
extern BOOL g_bMemoryMdl;		
extern BOOL g_bAutoMousMdl;		
extern BOOL g_bAutoKeybMdl;		
extern BOOL g_bMalMdl;			
extern BOOL g_bSpeedMdl;		
extern BOOL g_bFileMdl;			
extern BOOL g_bApiHookMdl;		
extern BOOL g_bDebugModMdl;		
extern BOOL g_bOsMdl;			
extern BOOL g_bPatchMdl;		

extern BOOL g_bMemoryCrack;		
extern BOOL g_bFileCrack;		
extern BOOL g_bApiHookCrack;	
extern BOOL g_bApiCrack;		

extern BOOL g_bStartXTrap;		
								






void XTrapStart				(IN UCHAR *pArgv);
void XTrapStart				(IN UCHAR *pArgv, IN CHAR *pXTrapPath);
void XTrapKeepAlive			();
void XTrapStop				();

void SetXTrapMgrInfo		(IN CHAR *pMgrIp);
void SetOptGameInfo			(IN CHAR *pUserName,  
										 IN CHAR *pGameServerName, 
										 IN CHAR *pCharacterName, 
									     IN CHAR *pClassName, 
										 IN long UserLevel);

void SetKeyboardModule		(HINSTANCE hInstance, BOOL bKeybdModule, LPVOID lpvReserved);






VOID XPatchStart			(IN LPSTR pArgv1, IN LPSTR pGamePath);
VOID XPatchStart			(IN LPSTR pArgv1, IN LPSTR pGamePath, IN DWORD dwTimeout);










#define XTRAP_CC4_BUFFERSIZE_COMMUNICATION_BASE		128

#define XTRAP_CC4_BUFFERSIZE_SESSION_BASE			320
#define XTRAP_CC4_BUFFERSIZE_SESSION_ADDON			80


#define XTRAP_CC4_BUFFERSIZE_SESSION				480

#define	XTRAP_CC4_FILESIZE_MAP						45000



#define XTRAP_CC_RETURN_OK					0x00000000
#define XTRAP_CC_RETURN_ERROR				0x00000001
#define XTRAP_CC_RETURN_UNKNOWN				0x00000002
#define XTRAP_CC_RETURN_INVALID_PARAMETER	0x00000003
#define XTRAP_CC_RETURN_INVALID_CRC			0x00000004
#define XTRAP_CC_RETURN_TIMEOUT				0x00000005

#define XTRAP_CC_RETURN_DETECTHACK			0x0000000F



#define	XTRAP_PROTECT_PE					0x00000001
#define	XTRAP_PROTECT_TEXT					0x00000010
#define	XTRAP_PROTECT_RDATA					0x00000100
#define	XTRAP_PROTECT_EDATA					0x00001000
#define	XTRAP_PROTECT_RSRC					0x00010000
#define	XTRAP_PROTECT_RELOC					0x00100000

#define XTRAP_PROTECT_EXCEPT_VIRUS			0x00000002



#define XTRAP_CC_MAXTIMEOUT					(int)600
#define XTRAP_CC_MINTIMEOUT					(int)100






#define		CREATEKF_OUT_SIZE		544
#define		CREATEKF_IN_SIZE		264

DWORD CreateKF			(IN char *VerHash, IN char *InBuf, OUT char *OutBuf);
DWORD CreateKFEx		(IN PUCHAR pVerHash, IN PUCHAR pInBuf, IN UCHAR CMF_Cnt, OUT PUCHAR pOutBuf);
void  SendLogToMgr		();





DWORD __cdecl XTrapCS_RecvSeedKey	(PUCHAR pSeedKey, DWORD dwMethod);
DWORD __cdecl XTrapCS_DetectCrack	();	


VOID __stdcall XTrapCS_SendUniqKey	(PUCHAR pUniqKey);






DWORD __cdecl XTrapCC_RecvSeedKey	(IN OUT PUCHAR pUserComBuf,	IN DWORD dwMethod );
DWORD __cdecl XTrapCC_DetectCrack	(IN PUCHAR pUserComBuf);






DWORD __cdecl XTrapCC_STEP2	(
					IN	PUCHAR	pPacketBuf_IN, 
					OUT	PUCHAR	pPacketBuf_OUT, 
					IN	DWORD	dwMethod				);


#endif
