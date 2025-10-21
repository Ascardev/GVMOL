#pragma once

#include "socket.h"

#define KB16			(16ull * 1024ull)

class SocketGame
{
protected:
	HWND						hWnd;

	int							iMaxConnections;
	BOOL						bActive = FALSE;
	BOOL						bSetFull = FALSE;
	SocketData* pcaSocketData;

	CMutex* pcMutex = NULL;

public:

	int							iReconnectLCOUNT = 0;
	int							iReconnectGCOUNT = 0;
	BOOL						bLoginServerReconnect = FALSE;
	BOOL						bGameServerReconnect = FALSE;

	char						szLoginIP[32];
	int							iLoginPort;
	char						szGameIP[32];
	int							iGameServerPort;

	SocketData* pcSocketLoginOld = NULL;
	SocketData* pcSocketGameOld = NULL;

	static struct PacketReceiving* psaPacketReceiving[100];
	static int					iNextReceiver;

	HWND						GetHWND() { return hWnd; };

	BOOL						IsActive() { return bActive; };

	void						SetIPPort(const char* pszIP, int iPort);

	SocketData* GetFreeSocketData();
	int							GetNumFreeSlots();

	SocketData* GetSocketData(const char* pszIP, int iPort);

	SocketData* Connect(const char* pszIP, int iPort, smWINSOCK* ws);

	void						SocketClose(SocketData* sd);
	void						SocketPacket(SocketData* sd, struct PacketReceiving* p);

	static DWORD WINAPI			ReceiveThread();
	static DWORD WINAPI			Receiver(SocketData* sd);
	static DWORD WINAPI			Sender(SocketData* sd);

	void						Init(HWND hwnd);

	void						SendPacket(SOCKET Socket, char* packet, int size);

	void						Connected();

	void						Shutdown();

	virtual ~SocketGame();
};

extern SocketGame* pcSocketGame;