
#ifdef _xTrap_GUARD

#include "IntNetwork.h"

#include <windows.h>

#include "XTrap.h"
#include ".\xtrapgameclient.h"

#include "..\language.h"


#pragma comment( lib, "ws2_32.lib")
#pragma comment( lib, "XTrapSrc\\XTrapIC_mt.lib" )

class CXTrapGameClient	g_XTrap;

CXTrapGameClient::CXTrapGameClient(void)
{
}

CXTrapGameClient::~CXTrapGameClient(void)
{
	XTrapWinsockEnd();
}

BOOL CXTrapGameClient::XTrap_StartUp(char *szGameTitle, char *szXTrap_MGR_ServerIP)
{
	if( szGameTitle==NULL ) 
		return false;

#ifdef __USE_XTRAP_MANAGER_LOG

	if( szXTrap_MGR_ServerIP==NULL )
		return false;

	SetXTrapMessagerIP(szXTrap_MGR_ServerIP);
#endif


#ifdef __XTRAPMODULE_H
	char	sGameName[MAX_PATH]	= {'\0',};

#ifdef _LANGUAGE_CHINESE
	DWORD	ApiVersion			= 0xA5001207;		
	DWORD	VendorCode			= 0x13026020;		
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_BRAZIL
	DWORD	ApiVersion			= 0xA5001150;		
	DWORD	VendorCode			= 0x13026220;		
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		
	DWORD	ModuleType			= 0x0FFFFFFF;
#else
#ifdef _LANGUAGE_JAPANESE
	DWORD	ApiVersion			= 0xA5001150;		
	DWORD	VendorCode			= 0x13026030;		
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_THAI
	DWORD	ApiVersion			= 0xA5001150;		
	DWORD	VendorCode			= 0x13026050;		
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_PHILIPIN
	DWORD	ApiVersion			= 0xA5001150;		
	DWORD	VendorCode			= 0x13026070;		
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		
	DWORD	ModuleType			= 0x01FFFFF2;
#else
#ifdef _LANGUAGE_VEITNAM
	DWORD	ApiVersion			= 0xA5001150;		
	DWORD	VendorCode			= 0x13026080;		
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		
	DWORD	ModuleType			= 0x01FFFFF2;
#else
	
	DWORD	ApiVersion			= 0xA5001150;		
	DWORD	VendorCode			= 0x00000010;		
	DWORD	KeyboardType		= 0x00000000;
	DWORD	PatchType			= 0x00000010;		
	DWORD	ModuleType			= 0x0FFFFFFF;
#endif
#endif
#endif
#endif
#endif
#endif
	strcpy( sGameName, szGameTitle );

#ifdef __USE_XTRAP_MANAGER_LOG
	SetXTrapMgrInfo( szXTrap_MGR_ServerIP );		
#endif



#ifdef _LANGUAGE_CHINESE 
	SetXTrapPatchHttpUrl( "Http://222.73.230.8/xtrap" );					
#else
#ifdef _LANGUAGE_BRAZIL	
	SetXTrapPatchHttpUrl( "http://download.priston.com.br/xtrap" );			
#else
#ifdef _LANGUAGE_ARGENTINA	
	SetXTrapPatchHttpUrl( "" );			
#else
#ifdef _LANGUAGE_JAPANESE	
	SetXTrapPatchHttpUrl( "http://xtrap.pristontale.jp/xtrap" );			
#else
#ifdef _LANGUAGE_PHILIPIN	
	SetXTrapPatchHttpUrl( "http://gupdate.netplay.ph/updates/X-trap" );		
#else
#ifdef _LANGUAGE_VEITNAM	
	SetXTrapPatchHttpUrl( "http://xtrap.ptv.com.vn" );						
#else
#ifdef _LANGUAGE_THAI		
	SetXTrapPatchHttpUrl( "http://patch.pt.in.th/xtrap" );					
#endif
#endif
#endif
#endif
#endif
#endif
#endif

	SetXTrapStartInfo(  sGameName,
						ApiVersion,
						VendorCode,
						KeyboardType,
						PatchType,
						ModuleType );

	XTrapStart();
	XTrapKeepAlive();
#endif




	return TRUE;
}










BOOL CXTrapGameClient::xTrapConnect(const char *szServerIP)
{ 
	if(!XTrapWinsockStart())
		return false;

	if(!ConnectXTrapMessagerServer(szServerIP))
		return false;

	return true;
}

#endif
