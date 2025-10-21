#include "socketserver.h"
#include <iostream>
#ifdef _W_SERVER
SocketServer* SocketServer::pcInstance = NULL;

CRITICAL_SECTION                                        sSectionAccept;
CMutex* pcSocketCloseMutex = NULL;

SocketServer::SocketServer()
{
	ZeroMemory(pcaReconnectedUsers, sizeof(smWINSOCK*) * _countof(pcaReconnectedUsers));
	sListenSocket = INVALID_SOCKET;
	iMaxConnections = 0;
	pcMutex = new CMutex();
}

SocketServer::~SocketServer()
{
	CloseHandle(hEventSocket);
}

int SocketServer::GetNumFreeSlots()
{
	int iFreeSlots = 0;

	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;

		if (!sd->bInUse)
			iFreeSlots++;
	}

	return iFreeSlots;
}

int SocketServer::GetNumUsedSlots()
{
	int iUsedSlots = 0;

	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;

		if (sd->bInUse)
			iUsedSlots++;
	}

	return iUsedSlots;
}

SocketData* SocketServer::GetFreeSocketData()
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

SocketData* SocketServer::GetSocketData(const char* pszIP, int iPort)
{
	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		if (sd->bInUse && sd->bConnected && !lstrcmpi(sd->szIP, pszIP) && sd->iPort == iPort)
			return sd;
	}
	return NULL;
}

void SocketServer::SocketAccept(smWINSOCK* s, sockaddr_in* addr)
{
	// Mutex Area
	EnterCriticalSection(&sSectionAccept);

	SocketData* sd = GetFreeSocketData();
	BOOL bAccepted = FALSE;

	if (sd && IsFull() == FALSE)
	{
		sd->Open(s, addr);

		bAccepted = TRUE;
	}

	if (!bAccepted)
	{
		if (sd)
		{
			sd->UnInit();

			sd = NULL;
		}
		closesocket(s->sock);
		s->sock = 0;
	}

	LeaveCriticalSection(&sSectionAccept);
}

extern int RecvMessage(smTHREADSOCK* SockInfo, PacketReceiving* p);
#include <iostream>
void SocketServer::SocketPacket(SocketData* sd, PacketReceiving* p)
{
	SOCKETMUTEX->Lock(5000);
	if (sd && p)
	{
		smWINSOCK* u = sd->u;
		rsPLAYINFO* ud = NULL;

		if (u)
			ud = (rsPLAYINFO*)u->ExtData1;

		if (u && (ud))
		{
			RecvMessage(&u->smRecvState, p);
			sd->dwTimeLastPacketReceived = GetTickCount();
		}
		else
		{
			WNDPROC_SOCKETCLOSE(hWnd, sd->u);
		}

		sd->FreePacketReceiving(p);
	}
	if (SOCKETMUTEX->Unlock())
	{
	}
}

void SocketServer::SocketClose(SocketData* sd)
{
	if (!pcSocketCloseMutex)
		pcSocketCloseMutex = new CMutex();

	pcSocketCloseMutex->Lock(5005);
	if (sd)
	{
		sd->u->acc_sin.sin_addr.S_un.S_addr = 0;
		sd->u->lpSocketData = 0;
		sd->u = 0;
		sd->Close();
		sd->UnInit();
	}

	pcSocketCloseMutex->Unlock();
}

void SocketServer::Load()
{
	iMaxConnections = 300;

	pcaSocketData = new SocketData[iMaxConnections];

	hEventSocket = CreateEvent(NULL, FALSE, FALSE, NULL);
	for (int i = 0; i < MAX_DENYCONNECTIONS; i++)
		saSocket[i] = INVALID_SOCKET;

	iNextSocket = 0;

	for (int i = 0; i < iMaxConnections; i++)
	{
		SocketData* sd = pcaSocketData + i;
		sd->pcThis = sd;
		sd->bInUse = FALSE;
		sd->Prepare(25, 25);
		sd->hReceiveThread = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)&SocketServer::Receiver, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
		sd->hSendThread = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)&SocketServer::Sender, sd, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	}
	bActive = TRUE;
}

DWORD WINAPI SocketServer::Sender(SocketData* sd)
{
	SocketServer* m = GetInstance();

	HWND hWnd = m->GetHWND();

	do
	{
		WaitForSingleObject(sd->hSendThreadSignal, INFINITE);

		if (!m->IsActive())
			break;

		PacketSending* p;
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

DWORD WINAPI SocketServer::Receiver(SocketData* sd)
{
	SocketServer* m = GetInstance();

	HWND hWnd = m->GetHWND();

	do
	{
		WaitForSingleObject(sd->hReceiveThreadSignal, INFINITE);

		if (!m->IsActive())
			break;

		PacketReceiving* p = 0;
		while ((p = sd->ReceivePacket()) != NULL)
		{
			PostMessageA(GetInstance()->GetHWND(), SWM_RECVSUCCESS, (WPARAM)sd, (LPARAM)p);
		}

		sd->bBlockSend = TRUE;

		if (m->IsActive())
		{
			if (sd->bConnected)
			{
				//Anti-DDoS
				if (sd->iRecvEC == 0x6A6A)
				{
					m->AddBanIP(sd->lIP);
				}

				WNDPROC_SOCKETCLOSE(m->GetHWND(), sd->u);
			}
		}
	} while (m->IsActive());

	return TRUE;
}

extern int srAcceptErrorCount;

DWORD WINAPI SocketServer::Listener(SOCKET* ls)
{
	SOCKET s = *ls;
	SocketServer* pc = GetInstance();

	sockaddr_in* sout = new sockaddr_in;
	int len = sizeof(sockaddr_in);

	while (pc->IsActive())
	{
		smWINSOCK* n = GetFreeSock();
		if (n)
		{
			if ((n->sock = accept(s, (SOCKADDR*)sout, &len)) != INVALID_SOCKET)
			{
				/*			if (!SockExists(sout->sin_addr.S_un.S_addr))
							{*/
				SendMessage(GetInstance()->GetHWND(), WSA_ACCEPT, (WPARAM)n, (LPARAM)sout);
				//}
			/*	else
				{
					n->sock = INVALID_SOCKET;
					srAcceptErrorCount++;
				}*/
			}
		}
	}
	delete sout;

	return TRUE;
}

BOOL SocketServer::AddBanIP(DWORD dwIP)
{
	pcMutex->Lock(6101);

	int iIndex = -1;

	for (int i = 0; i < MAX_BANCONNECTIONS; i++)
	{
		if (dwaIPListBan[i] != 0)
		{
			if (dwaIPListBan[i] == dwIP)
				return TRUE;
		}
		else
			iIndex = i;
	}

	if (iIndex >= 0)
		dwaIPListBan[iIndex] = dwIP;

	pcMutex->Unlock();

	return TRUE;
}

BOOL SocketServer::AddReconnectedUser(smWINSOCK* pcUser)
{
	for (int i = 0; i < MAX_RECONNECTCONNECTIONS; i++)
	{
		if (pcaReconnectedUsers[i] == NULL)
		{
			pcaReconnectedUsers[i] = pcUser;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL SocketServer::Init(HWND hwnd)
{
	hWnd = hwnd;

	SetPacketObfuscatorByte(TCP_SERVPORT);

	Listen(TCP_SERVPORT);
	return TRUE;
}
void SocketServer::Listen(int iPort)
{
	int iStatus = 0;
	// Start
	if ((iStatus = WSAStartup(MAKEWORD(2, 2), &sWsaData)) != 0)
	{
		return;
	}

	if ((sListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET)
	{
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_port = htons(iPort);

		if (::bind(sListenSocket, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
		{
			if (listen(sListenSocket, SOMAXCONN) == SOCKET_ERROR)
			{
				closesocket(sListenSocket);
				sListenSocket = INVALID_SOCKET;
				return;
			}
		}
		else
		{
			closesocket(sListenSocket);
			sListenSocket = INVALID_SOCKET;
			return;
		}
	}
	else
	{
		return;
	}

	bActive = TRUE;

	InitializeCriticalSection(&sSectionAccept);

	// Success
	hListener = CreateThread(NULL, 16384, (LPTHREAD_START_ROUTINE)Listener, &sListenSocket, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);
	Load();
}
#endif