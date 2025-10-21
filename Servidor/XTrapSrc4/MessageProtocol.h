
#ifndef _ignore_messageprotocol_h_20070126_
#define _ignore_messageprotocol_h_20070126_

#include "stdio.h"
#include <windows.h>
#include "XTrap.h"


#define		szMAP1_FILE_NAME  "map1.cs3"
#define		szMAP2_FILE_NAME  "map2.cs3"

#define CC4FILE_NUM	2											

#define	_XTRAP_DEBUG		
							
							

#define SERVER_XTRAP_DEBUG_FILE	"_ignore_xtrap_server_debug.dat"
#define	CLIENT_XTRAP_DEBUG_FILE	"_ignore_xtrap_client_debug.dat"



typedef struct _xtrap_session_buf
{
	char	m_PacketBuf[XTRAP_CC4_BUFFERSIZE_COMMUNICATION_BASE];
	char	m_SessionBuf[XTRAP_CC4_BUFFERSIZE_SESSION];
	
	DWORD	dwTime;
	bool	bFirst;
	bool	bGetTRANSPLAYDATA;
	int		KeyGenWaitCount;
	
	FILE	*m_fp;
	
	_xtrap_session_buf()
	{
		Clear();
	};

	~_xtrap_session_buf()
	{

	};

	void Clear(void)
	{
		memset(this->m_PacketBuf,0,sizeof(this->m_PacketBuf));
		memset(this->m_SessionBuf,0,sizeof(this->m_SessionBuf));
		dwTime = 0; 
		bFirst = true;	
		m_fp = 0;
		bGetTRANSPLAYDATA = false;
		KeyGenWaitCount = 0;
	};

} XTRAPCS_SESSION_BUF;				



typedef struct _xtrap_packet
{
	int		m_iSize;
	int		m_iCmd;			
	char	aData[512];	

	_xtrap_packet()
	{
		m_iCmd = 0;
		m_iSize = 0;
		ZeroMemory(aData,sizeof(aData));
	};

} XTrapPacket;


#define		XTRAP_CMD_UNIQKEY		0x44444444
#define		XTRAP_CMD_SEEDKEY		0x44446666
#define		XTRAP_CMD_DISCONNECT	0x44447777

#endif
