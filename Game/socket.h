#pragma once

#include <Windows.h>
#include "sinbaram/sinLinkHeader.h"
#include "smwsock.h"
#include "smPacket.h"

#define WNDPROC_SOCKETACCEPT( window, socket, address )		( SendMessageA( window, WSA_ACCEPT, (WPARAM)socket, (LPARAM)address ) )
#define WNDPROC_SOCKETPACKET( window, socketdata, packet )	( PostMessageA( window, SWM_RECVSUCCESS, (WPARAM)socketdata, (LPARAM)packet ) )
#define WNDPROC_SOCKETCLOSE( window, socketdata )			( PostMessageA( window, SWM_MDISCONNECT, (WPARAM)socketdata, (LPARAM)NULL ) )

#define RELEASE(p)			{ if(p != NULL) p->Release(); p = NULL;}
#define INIT(p)				{ if(p != NULL) p->Init();}
#define INITP(p, ptr)		{ if(p != NULL && ptr != NULL) p->Init(ptr);}
#define DELET(p)			{ if(p != NULL) delete p; p = NULL;}
#define DELETA(p)			{ if(p != NULL) delete[] p; p = NULL;}
#define SHUTDOWN(p)			{ if(p != NULL) p->Shutdown();}
#define ADDREF(p)			{ if(p != NULL) p->AddRef();}
#define CLEARPTR(p)			{ if(p != NULL) p->Clear();}
#define RESETPTR(p)			{ if(p != NULL) p.reset(); p = NULL;}

//Lag Grace = 10 minutes
#define MAX_LAGGRACE		1000 * 60 * 10
#define NUM_ENCKEYS			256

extern const BOOL SOCKET_NODELAY;

extern const int RCVWND_SIZE;
extern const int SNDWND_SIZE;

struct Packet //Header
{
	int	  iLength;				//Packet Length
	int	  iHeader;				//Packet Header
}; //Size = 0x08

struct PacketSending
{
	union
	{
		BOOL	  bInUse;
		UINT	  uCount;
	};
	UINT		  uSize;
	BYTE		  baPacket[smSOCKBUFF_SIZE];
};

struct PacketReceiving
{
	BOOL		  bInUse;
	BOOL		  bDelete;
	BYTE		  baPacket[smSOCKBUFF_SIZE];
	DWORD		  recvTime;
	DWORD		  recvTime2;
};

struct PacketPing : Packet
{
	DWORD	  dwTime;
	DWORD	  dwTick;
};

class SocketData
{
public:
	//Attributes
	SocketData* pcThis;

	//Status Flags
	bool				  bInUse;
	bool				  bConnecting;
	bool				  bConnected;
	bool				  bReserved;

	//This Socket Information
	SOCKET				  s;
	rsPLAYINFO* ud;
	smWINSOCK* u;

	//Remote Host
	char				  szIP[32];
	long				  lIP;
	int					  iPort;

	//Time last Received Packet
	DWORD				  dwTimeLastPacketReceived;

	//Receiving Packets
	UINT				  iDefReceivePacket;
	UINT				  iMaxReceivePacket;
	HANDLE				  hReceiveThread;
	HANDLE				  hReceiveThreadSignal;
	CMutex* pcReceiveMutex;
	UINT				  iReceiveWheel;
	PacketReceiving* psaPacketReceiving;

	//Sending Packets
	UINT				  iDefSendPacket;
	UINT				  iMaxSendPacket;
	HANDLE				  hSendEvent;
	HANDLE				  hSendThread;
	HANDLE				  hSendThreadSignal;
	CMutex* pcSendMutex;
	UINT				  iSendWheel;
	UINT				  iSendingWheel;
	PacketSending* psaPacketSending;
	BOOL				  bBlockSend;
	DWORD				  dwBulkThreadId;
	PacketSending		  sBulkPacket;

	//Encryption
	bool				  bKeySet;
	BYTE				  baKeySet[NUM_ENCKEYS];
	BYTE				  bNextKey;
	int					  iIPIndex;

	//Pinging
	bool				  bPing;
	DWORD				  dwPingTime;
	int					  iPing;

	//Counting
	UINT				  iCountIN;
	UINT				  iCountOUT;
	UINT				  iCountOUTB;

	//Error Handling
	int					  iRecvRet;
	int					  iRecvEC;
	int					  iSendRet;
	int					  iSendEC;

	BOOL				  bKeepAlive;

public:
	//Operations
	SocketData();
	~SocketData();

	void				  Prepare(UINT iMaxSendPacket, UINT iMaxReceivePacket);

	//Initializing
	void				  Init();
	void				  UnInit();

	//Connection
	bool				  Connect(const char* pszIP, int iPort);
	void				  Open(smWINSOCK* s, sockaddr_in* addr);
	void				  Close();

	//Receiving
	PacketReceiving* FreePacketReceiving();
	void				  FreePacketReceiving(PacketReceiving* pp);

	PacketReceiving* ReceivePacket();

	//Sending
	PacketSending* NextPacketSending();
	void				  FreePacketSending(PacketSending* pp);

private:
	//Inner Packet Sending Methods
	BOOL				  Send(BYTE* pbData, UINT uSize);
	BOOL				  SendData(BYTE* pbData, UINT uSize);

	//Automatic Bulk Sending
	PacketSending* FindAutomaticBulk(UINT uSizeNeeded);

public:
	//Packet Sending Method that should only be used from Sending Thread
	BOOL				  Send(PacketSending* pp);

	//Packet Sending Methods that should be used from outside
	BOOL				  SendPacket(Packet* p, BOOL bEncrypted = FALSE);
	BOOL				  SendPacketBlank(DWORD iHeader, BOOL bEncrypted = FALSE);

	//Forced Bulk Sending
	BOOL				  StartBulkSend();
	BOOL				  FlushBulkSend();
	BOOL				  StopBulkSend();

	//Encryption

	BYTE				  GetNextIPIndex();
	BYTE				  ValIPIndex(BYTE iIndex, Packet* p);

	//Getters & Setters
	void				  SetPing(int i) { iPing = i; bPing = false; }
	int					  GetPing(DWORD dwTime);
};