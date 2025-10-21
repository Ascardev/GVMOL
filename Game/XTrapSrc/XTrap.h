





#ifndef __XTRAPMODULE_H
#define __XTRAPMODULE_H

#define		CREATEKF_OUT_SIZE	544
#define		CREATEKF_IN_SIZE	264

extern HANDLE	g_XTrapMsgEvent;





extern char	g_sXTrapCode[MAX_PATH];		





void SetXTrapStartInfo		(CHAR *pGameName, 
										 DWORD ApiVersion, DWORD VendorCode, DWORD KeyboardType, DWORD PatchType, DWORD ModuleType);
void XTrapStart				();
void XTrapKeepAlive			();

void SetXTrapMgrInfo		(IN CHAR *pMgrIp);
void SetXTrapPatchHttpUrl	(IN CHAR *pHttpUrl);
void SetOptGameInfo			(IN CHAR *pUserName,  IN CHAR *pGameServerName, IN CHAR *pCharacterName, 
									     IN CHAR *pClassName, IN long UserLevel);

DWORD CreateKFEx			(IN  PUCHAR	pVerHash,	
										 IN  PUCHAR	pInBuf,		
										 IN	 UCHAR	CMF_Cnt,	
										 OUT PUCHAR	pOutBuf);	
void SendLogToMgr			();

void SetKeyboardModule		( HINSTANCE hInstance, BOOL bKeybdModule, LPVOID lpvReserved );

#endif
