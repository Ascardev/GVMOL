


UCHAR	sXTrapCS_Buf[CC4FILE_NUM][XTRAP_CC4_FILESIZE_MAP];

int rsXTrap_Init()
{
	char szDbg[512];

	FILE * fp = NULL;
	fp=fopen(szMAP1_FILE_NAME,"rb");
	if ( fp ) 
	{ 
		size_t size = 0;
		size = fread(sXTrapCS_Buf[0] , sizeof(UCHAR), XTRAP_CC4_FILESIZE_MAP , fp ); 
		fclose(fp); fp = NULL;

		sprintf(szDbg,"size1 : %d",size);
		
	}
	else
	{
		MessageBox(NULL,"map file 1","error",MB_OK);
	}

	fp = NULL;
	fp=fopen(szMAP2_FILE_NAME,"rb");
	if ( fp )
	{ 
		size_t size = 0;
		size = fread( sXTrapCS_Buf[1] , sizeof(UCHAR), XTRAP_CC4_FILESIZE_MAP , fp ); 
		fclose(fp); fp = NULL;

		sprintf(szDbg,"size2 : %d",size);
		
	}
	else
	{
		MessageBox(NULL,"map file 2","error",MB_OK);
	}
	
	unsigned long ulReturn = 0;
	ulReturn = XTrapCC_ServerInit( rsServerConfig.XTRAP_Timer, CC4FILE_NUM, (PUCHAR)sXTrapCS_Buf );	
	
	if( ulReturn == 0 )
	{
	}
	else
	{
		MessageBox( NULL, "map파일이 틀립니다.", "엑스트렙 오류", MB_ICONSTOP);
	}
	return TRUE;
}




int rsXTrap_SeedKey( rsPLAYINFO *lpPlayInfo )
{
	char szDbg[512] = {0,};
	XTRAPCS_SESSION_BUF *lpXTrapCS_Session_Buf = &lpPlayInfo->XTrapCS_Session_Buf;

	
	lpXTrapCS_Session_Buf->dwTime	= dwPlayServTime+1000*20;	

	
	if(lpXTrapCS_Session_Buf->bFirst == true)
	{	
		lpXTrapCS_Session_Buf->bFirst = false;
		XTrapCC_SessionInit( rsServerConfig.XTRAP_Timer, CC4FILE_NUM, (PUCHAR)sXTrapCS_Buf, (PUCHAR)lpXTrapCS_Session_Buf->m_SessionBuf );
		
	}

	
	unsigned long ulRet = 0;
	ulRet = XTrapCC_STEP1( (PUCHAR)lpXTrapCS_Session_Buf->m_SessionBuf, (PUCHAR)lpXTrapCS_Session_Buf->m_PacketBuf);

	
	smTRANS_XTRAP_ADDR	smTransXtrapAddr;
	memset(&smTransXtrapAddr, 0x00, sizeof(smTransXtrapAddr));

	smTransXtrapAddr.smTransCommand.size = sizeof(smTransXtrapAddr);
	smTransXtrapAddr.smTransCommand.code = smTRANSCODE_XTRAP_PACKET;
	smTransXtrapAddr.smTransCommand.WParam = XTRAP_CMD_SEEDKEY;
	memcpy(smTransXtrapAddr.PacketBuf,lpXTrapCS_Session_Buf->m_PacketBuf,sizeof(smTransXtrapAddr.PacketBuf));
	int iSendSize = lpPlayInfo->lpsmSock->Send2( (char *)&smTransXtrapAddr , smTransXtrapAddr.smTransCommand.size , TRUE );

	sprintf( szDbg, "SEND SIZE : %d", iSendSize ); 
	

	
	if( ulRet == 0 )
	{
	}
	else
	{
		smTRANS_COMMAND	smTransCommand;
		smTransCommand.WParam = 8710;
		smTransCommand.LParam = 100;
		smTransCommand.SParam = 0;
		RecordHackLogFile( lpPlayInfo, &smTransCommand );
		lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime+1000*10;		
	}


	

	
	

	
	

	
	
	
	
	
	
	

	
	


	return TRUE;
}


int rsXTrap_RecvPacket( rsPLAYINFO *lpPlayInfo , smTRANS_COMMAND *lpPacket )
{
	char szDbg[512] = {0,};

	DWORD dwTransCode = lpPacket->WParam;
	XTRAPCS_SESSION_BUF *lpXTrapCS_Session_Buf = &lpPlayInfo->XTrapCS_Session_Buf;

	sprintf( szDbg, "BUF ADDR2 : %08X", lpPlayInfo->XTrapCS_Session_Buf );
	

	if ( dwTransCode==XTRAP_CMD_UNIQKEY ) 
	{
		
		sprintf( szDbg, "RECV SIZE : %d", lpPacket->size );
		
		
		memcpy( lpXTrapCS_Session_Buf->m_PacketBuf, ((smTRANS_XTRAP_ADDR *)lpPacket)->PacketBuf , sizeof(lpXTrapCS_Session_Buf->m_PacketBuf));
		XTrapCC_STEP3( (PUCHAR)lpXTrapCS_Session_Buf->m_SessionBuf, (PUCHAR)lpXTrapCS_Session_Buf->m_PacketBuf );
	}


	return TRUE;
}
