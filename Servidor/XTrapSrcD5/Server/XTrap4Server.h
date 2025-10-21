






#ifndef	__XTRAPAPI_SERVER_H
#define __XTRAPAPI_SERVER_H




#define XTRAP_CS4_COMSIZE_PACKDATA					128
#define XTRAP_CS4_BUFSIZE_SESSION					320
#define XTRAP_CS4_BUFSIZE_SESSIONADDON				80
#define	XTRAP_CS4_BUFSIZE_MAP						45000


#define XTRAP_CS4_MAXTIMEOUT						(int)600
#define XTRAP_CS4_MINTIMEOUT						(int)100


#define XTRAP_API_RETURN_OK							0x00000000
#define XTRAP_API_RETURN_ERROR						0x00000001
#define XTRAP_API_RETURN_UNKNOWN					0x00000002
#define XTRAP_API_RETURN_INVALID_PARAMETER			0x00000003
#define XTRAP_API_RETURN_INVALID_CRC				0x00000004
#define XTRAP_API_RETURN_TIMEOUT					0x00000005
#define XTRAP_API_RETURN_DETECTHACK					0x0000000F


#define	XTRAP_PROTECT_PE							0x00000001
#define	XTRAP_PROTECT_TEXT							0x00000010
#define	XTRAP_PROTECT_RDATA							0x00000100
#define	XTRAP_PROTECT_EDATA							0x00001000
#define	XTRAP_PROTECT_RSRC							0x00010000
#define	XTRAP_PROTECT_RELOC							0x00100000
#define XTRAP_PROTECT_EXCEPT_VIRUS					0x00000002


#define XTRAP_CS_MODULE_DM_TIMEOUT					0x00000001		
#define XTRAP_CS_MODULE_LOG_BUF						0x00000100		
#define XTRAP_CS_MODULE_LOG_FILE					0x00000200		


#if		defined(XTRAP4SERVER_EXPORTS)
#define XTRAPCC_API __declspec(dllexport)
#else
#define XTRAPCC_API
#endif

#if		defined(_WIN32)
#define XTRAPCC_CALLCONV __cdecl
#else
#define XTRAPCC_CALLCONV
#endif

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if		(defined(XTRAP4SERVER_EXPORTS))






XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_S_Start(
	IN	unsigned long	ulTimeOut, 
	IN	unsigned long	ulMapCount,	
	IN	const void*		pBufMap,
		void*			Reserved
	);

XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_S_SessionInit(
	IN	unsigned long	ulTimeOut,
	IN	unsigned long	ulMapCount,
	IN	const void*		pBufMap, 
	INOUT	void*		pBufSession 
	);

XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_CS_Step1( 
	INOUT	void*		pBufSession,
	OUT		void*		pBufPackData	
	);

XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_CS_Step3(
	INOUT	void*		pBufSession, 
	IN	const void*		pBufPackData	
	);






XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_S_SessionReset(
		unsigned long	ulTimeOut,
		unsigned long	ulMapCount,
		const void*		pBufMap,
		void*			pBufSession 
	);

XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_S_SetModuleOn(
		unsigned long	ulMethod
	);

XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_S_SetModuleOff(
		unsigned long	ulMethod
	);

XTRAPCC_API unsigned long XTRAPCC_CALLCONV	XTrap_S_SaveLog(
		IN	const void*		pBufSession,
		IN	unsigned long	ulMethod,
		OUT	void*			pOut,

		IN	const char*		pUserID,
		IN	const char*		pServerName,
		IN	const char*		pUserIP,
		IN	const char*		Reserved,
		IN	long			lCharacterLevel
	);

#else

typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_S_Start)			( unsigned long ulTimeOut, unsigned long ulMapCount, const void* pBufMap, void* Reserved );
typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_S_SessionInit)		( unsigned long ulTimeOut, unsigned long ulMapCount, const void* pBufMap, void* pBufSession );
typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_CS_Step1)			( void* pBufSession, void* pBufPackData );
typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_CS_Step3)			( void*	pBufSession, const void* pBufPackData );
typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_S_SessionReset)	( unsigned long ulTimeOut, unsigned long ulMapCount, const void* pBufMap, void* pBufSession );
typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_S_SetModuleOn)		( unsigned long	ulMethod );
typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_S_SetModuleOff)	( unsigned long	ulMethod );
typedef unsigned long	(XTRAPCC_CALLCONV *PFN_XTrap_S_SaveLog)			( const void* pBufSession, unsigned long ulMethod, void* pOut, const char* pUserID, const char* pServerName, const char* pUserIP, const char* Reserved, long lCharacterLevel );

extern PFN_XTrap_S_Start		XTrap_S_Start;
extern PFN_XTrap_S_SessionInit	XTrap_S_SessionInit;
extern PFN_XTrap_CS_Step1		XTrap_CS_Step1;
extern PFN_XTrap_CS_Step3		XTrap_CS_Step3;
extern PFN_XTrap_S_SessionReset	XTrap_S_SessionReset;
extern PFN_XTrap_S_SetModuleOn	XTrap_S_SetModuleOn;
extern PFN_XTrap_S_SetModuleOff	XTrap_S_SetModuleOff;
extern PFN_XTrap_S_SaveLog		XTrap_S_SaveLog;

extern unsigned long	XTrap_S_LoadDll	();		
extern unsigned long	XTrap_S_FreeDll	();		

#endif


#ifdef __cplusplus
}
#endif

#endif
