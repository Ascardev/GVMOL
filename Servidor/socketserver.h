#pragma once

#include <windows.h>
#include "sinbaram/sinLinkHeader.h"
#include "socket.h"
#ifdef _W_SERVER

#define NUM_RESERVED_SLOTS								10

#define MAX_DENYCONNECTIONS								256
#define MAX_BANCONNECTIONS								1024
#define MAX_RECONNECTCONNECTIONS						128


#define SOCKETACCEPT(s,a)			SocketServer::GetInstance()->SocketAccept(s,a);
#define SOCKETPACKET(s,p)			SocketServer::GetInstance()->SocketPacket(s,p);
#define SOCKETCLOSE(s)				SocketServer::GetInstance()->SocketClose(s);

class SocketServer
{

protected:
	HWND												hWnd;
	WSADATA												sWsaData;
	SOCKET												sListenSocket = INVALID_SOCKET;
	int													iMaxConnections;
	BOOL												bActive = FALSE;
	BOOL												bSetFull = FALSE;
	SocketData											* pcaSocketData;
	CMutex												* pcMutex = NULL;

	HANDLE							  hEventSocket;
	SOCKET							  saSocket[MAX_DENYCONNECTIONS];
	DWORD								dwaIPListBan[MAX_BANCONNECTIONS];
	smWINSOCK						* pcaReconnectedUsers[MAX_RECONNECTCONNECTIONS];
	int								  iNextSocket;

	BYTE												bPacketObfuscatorByte = 0;
public:

	HANDLE												hListener;
	static SocketServer									* pcInstance;
	static SocketServer									* GetInstance() { return SocketServer::pcInstance; };
	CMutex												* GetMutex() { return pcMutex; };
	static void											CreateInstance() { SocketServer::pcInstance = new SocketServer(); };
	HWND												GetHWND() { return hWnd; };
	BOOL												IsActive() { return bActive; };
	BOOL												IsFull() { return bSetFull; };
	void												SetFull(BOOL b) { bSetFull = b; };

	SocketData											* GetFreeSocketData();
	int													GetNumFreeSlots();
	int													GetNumUsedSlots();

	SocketData											* GetSocketData(const char * pszIP, int iPort);

	void												SocketAccept(smWINSOCK* s, sockaddr_in * addr);
	void												SocketPacket(SocketData * sd, PacketReceiving * p);
	void												SocketClose(SocketData * sd);

	SocketServer();
	virtual ~SocketServer();

	static DWORD WINAPI									Sender(SocketData * sd);
	static DWORD WINAPI									Receiver(SocketData * sd);
	static DWORD WINAPI									Listener(SOCKET * ls);

	BOOL												AddBanIP(DWORD dwIP);
	BOOL												AddReconnectedUser(smWINSOCK * pcUser);

	void												Load();

	BOOL												Init(HWND hwnd);

	void												Listen(int iPort);

	void												OnReadHandler(SOCKET s, DWORD dwParam);

	HANDLE												GetHandleEventSocket() { return hEventSocket; }

	BYTE												GetPacketObfuscatorByte() { return bPacketObfuscatorByte; }
	void												SetPacketObfuscatorByte(BYTE b) { bPacketObfuscatorByte = b; }

};

#define SOCKETMUTEX										(SocketServer::GetInstance()->GetMutex())

#endif