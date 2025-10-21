#include "SocketGame.h"

#pragma comment (lib, "Ws2_32.lib")

DWORD dwReconnectLoginServerCount = 0;
DWORD dwTimePacket = 0;
BOOL bCanCheckConnection = FALSE;
extern int                    iLoginServerPingID;
extern int                    iGameServerPingID;
struct PacketReceiving* SocketGame::psaPacketReceiving[100];
int SocketGame::iNextReceiver;

SocketGame* pcSocketGame = NULL;

int SocketGame::GetNumFreeSlots()
{
	int iFreeSlots = 0;
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (!sd->bInUse)
			iFreeSlots++;
	}
	return iFreeSlots;
}//ae;;ae

SocketData* SocketGame::GetFreeSocketData()
{
	SocketData* r = NULL;
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (!sd->bInUse)
		{
			sd->Init();
			r = sd;
			break;
		}
	}
	return r;
}

SocketData* SocketGame::GetSocketData(const char* pszIP, int iPort)
{
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (sd->bInUse && !lstrcmpi(sd->szIP, pszIP) && sd->iPort == iPort)
		{
			return sd;
		}
	}
	return NULL;
}

SocketData* SocketGame::Connect(const char* pszIP, int iPort, smWINSOCK* ws)
{
	SocketData* sd = NULL;
	sd = GetFreeSocketData();
	if (sd)
	{
		sd->u = ws;
		lstrcpy(ws->szIPAddr, pszIP);
		if (!sd->Connect(pszIP, iPort))
		{
			sd->UnInit();
			return NULL;
		}
	}

	return sd;
}
void SocketGame::SocketClose(SocketData* sd)
{
	if ((sd) && (sd->bInUse))
	{
		/*if (sd == SOCKETL)
			SOCKETL = NULL;
		if (sd == SOCKETG)
			SOCKETL = NULL;*/

		while (sd->bConnecting)
			Sleep(2500);
		sd->Close();
		sd->UnInit();
	}
}
#include <iostream>

void SocketGame::SocketPacket(SocketData* sd, PacketReceiving* p)
{
	pcMutex->Lock(5000);
	Packet* psPacket = (Packet*)p->baPacket;

	DWORD dwTime = GetCurrentTime();

	if (sd->u == smWsockDataServer)
	{
		dwRecvDataServerTime = dwTime;
		dwDataServ_RecvTime = dwTime;
	}

	if (sd->u == smWsockUserServer)
	{
		dwRecvUserServerTime = dwTime;
		dwUserServ_RecvTime = dwTime;
	}

	if (sd->u == smWsockExtendServer)
	{
		dwRecvExtendServerTime = dwTime;
		dwExtendServ_RecvTime = dwTime;
	}
	if (sd->u == smWsockServer)
	{
		dwRecvServerTime = dwTime;
		dwMainServ_RecvTime = dwTime;
	}

	memcpy(&sd->u->smRecvState.Buff, psPacket, psPacket->iLength);

	rsMainServer.RecvMessage(&sd->u->smRecvState);

	dwTime = GetCurrentTime();

	sd->dwTimeLastPacketReceived = GetTickCount();;
	sd->FreePacketReceiving(p);
	pcMutex->Unlock();
}

DWORD WINAPI SocketGame::ReceiveThread()
{
	return TRUE;
}
DWORD WINAPI SocketGame::Receiver(SocketData* sd)
{
	SocketGame* m = pcSocketGame;
	HWND hWnd = m->GetHWND();

	PacketReceiving* p;
	do
	{
		WaitForSingleObject(sd->hReceiveThreadSignal, INFINITE);
		if (!m->IsActive())
			break;
		while ((p = sd->ReceivePacket()) != NULL)
		{
			PostMessageA(hWnd, SWM_RECVSUCCESS, (WPARAM)sd, (LPARAM)p);
		}
		sd->bBlockSend = TRUE;
		if (m->IsActive())
		{
			if (sd->bConnected)
			{
				WNDPROC_SOCKETCLOSE(hWnd, sd->u);
			}
		}
	} while (m->IsActive());
	return TRUE;
}

DWORD WINAPI SocketGame::Sender(SocketData* sd)
{
	SocketGame* m = pcSocketGame;
	HWND hWnd = m->GetHWND();
	PacketSending* p;
	do
	{
		WaitForSingleObject(sd->hSendThreadSignal, INFINITE);
		if (!m->IsActive())
			break;
		while ((p = sd->NextPacketSending()) != NULL)
		{
			//Post Packet Message
			if (!sd->Send(p))
			{
				sd->FreePacketSending(p);
				break;
			}
			sd->FreePacketSending(p);
		}
	} while (m->IsActive());
	return TRUE;
}

void SocketGame::Init(HWND hwnd)
{
	hWnd = hwnd;
	pcMutex = new CMutex("Socket Game");
	bActive = TRUE;
	iMaxConnections = 8;

	pcaSocketData = new SocketData[iMaxConnections];

	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		sd->pcThis = sd;
		sd->bInUse = FALSE;
		sd->Prepare(25, 25);
		sd->hReceiveThread = CreateThread(NULL, KB16, (LPTHREAD_START_ROUTINE)&SocketGame::Receiver, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
		sd->hSendThread = CreateThread(NULL, KB16, (LPTHREAD_START_ROUTINE)&SocketGame::Sender, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	}
	bActive = TRUE;
}

void SocketGame::Connected()
{
	bCanCheckConnection = TRUE;
}

void SocketGame::Shutdown()
{
	bActive = FALSE;
}

void SocketGame::SendPacket(SOCKET Socket, char* packet, int size)
{
	send(Socket, packet, size, 0);
}

SocketGame::~SocketGame()
{
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		TerminateThread(sd->hReceiveThread, 0);
		TerminateThread(sd->hSendThread, 0);
	}
	DELETA(pcaSocketData);
}