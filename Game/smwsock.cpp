#define _WIN32_WINNT    0x0400
#define _WIN32_WINDOWS  0x040a

#include "nettype.hpp"

#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <process.h>

#include "smwsock.h"
#include "socketgame.h"
#include "socketserver.h"

#pragma comment( lib, "wsock32.lib" )

extern HWND hwnd;

static HWND	hMsgWnd;

#define TRANSMODE_RECV	0x0001
#define TRANSMODE_SEND	0x0002
#define TRANSMODE_DUAL	0x0003

CRITICAL_SECTION	cSocketSection;

static char szIP[16];

#define smTRANSCODE_ENCODE_PACKET	0x80010000

#define TRANS_THREAD_SEND_MAX		30
#define TRANS_THREAD_RECV_MAX		10
#define TRANS_WAIT_QUE_MAX			512
#define TRANS_WAIT_QUE_MASK			511

#define PACKET_SEND_QUE_MAX			256
#define PACKET_SEND_QUE_MASK		(PACKET_SEND_QUE_MAX-1)

smTHREAD_ROUTE smTransRecvThreads[TRANS_THREAD_RECV_MAX];
smTHREAD_ROUTE smTransSendThreads[TRANS_THREAD_SEND_MAX];

smWINSOCK* smWaitSendSocketQue[TRANS_WAIT_QUE_MAX];
smWINSOCK* smWaitRecvSocketQue[TRANS_WAIT_QUE_MAX];

int		smTransThreadMode = 0;
int		smTransTurbRcvMode = 0;

int		smTransRecvErrorCnt = 0;
int		smTransSendErrorCnt = 0;
int		smTransRecvErrorDisCnt = 0;
int		smTransSendErrorDisCnt = 0;

int		smTransClearErrorCnt = 0;
int		smRcvBuffOverCount = 0;

smWINSOCK	smWSock[CONNECTMAX];

#define _DEBUG_SOCKET

#ifdef _DEBUG_SOCKET

#include "smlib3d\\smd3d.h"
extern smCONFIG smConfig;
extern int AddChatBuff(char* szMsg);

#endif

int GetUseingSendThreadCount()
{
	int cnt;
	int Count = 0;

	for (cnt = 0; cnt < TRANS_THREAD_SEND_MAX; cnt++) {
		if (smTransSendThreads[cnt].smThreadSock) {
			Count++;
		}
	}

	return Count;
}

int GetUseingRecvThreadCount()
{
	int cnt;
	int Count = 0;

	for (cnt = 0; cnt < TRANS_THREAD_RECV_MAX; cnt++) {
		if (smTransRecvThreads[cnt].smThreadSock) {
			Count++;
		}
	}

	return Count;
}

#define TRANS_LOST_TIME		15000

char* ConvStrIP(DWORD dwIP)
{
	in_addr  ia;

	ia.S_un.S_addr = dwIP;
	lstrcpy(szIP, inet_ntoa(ia));

	return szIP;
}

char* smGetMyIp()
{
	PHOSTENT phe;
	in_addr  ia;

	phe = gethostbyname("");
	if (phe == NULL) {
		return FALSE;
	}
	ia.S_un.S_addr = ((unsigned long*)phe->h_addr)[0];
	lstrcpy(szIP, inet_ntoa(ia));

	return szIP;
}

DWORD smGetMyIp2()
{
	PHOSTENT phe;

	phe = gethostbyname("");
	if (phe == NULL) {
		return FALSE;
	}

	return ((DWORD*)phe->h_addr)[0];
}

smWINSOCK::smWINSOCK()
{
}
smWINSOCK::~smWINSOCK()
{
}

extern int ConnectPlayer(smWINSOCK* lpsmSock);

extern int DisconnectPlayer(smWINSOCK* lpsmSock);

int smWINSOCK::ReconnectSock()
{
	SOCKADDR_IN dest_sin;
	SOCKET	msock;
	int status;

	if (!sock) return FALSE;

	closesocket(sock);
	sock = 0;
	Sleep(100);

	msock = socket(AF_INET, SOCK_STREAM, 0);
	if (msock == INVALID_SOCKET) {
		return FALSE;
	}

	dest_sin.sin_family = AF_INET;
	dest_sin.sin_addr.S_un.S_addr = inet_addr(szIPAddr);
	dest_sin.sin_port = htons((u_short)dwPort);

	if (connect(msock, (PSOCKADDR)&dest_sin, sizeof(dest_sin)) == SOCKET_ERROR) {
		CloseSocket();
		return FALSE;
	}

	ConnectDirection = TRUE;

	status = WSAAsyncSelect(msock, hMsgWnd, WSA_READ, FD_READ | FD_WRITE | FD_CLOSE);

	sock = msock;
	acc_sin.sin_addr.S_un.S_addr = inet_addr(szIPAddr);

	PacketSendQueCnt = 0;
	WaitReadMessage = 0;
	PostReadMessage = 0;
	RecvPacketCount = 0;
	SendPacketCount = 0;
	RecvPacketErrorCount = 0;
	SendPacketErrorCount = 0;
	RecvPopCount = 0;
	RecvPopErrorCount = 0;
	dwLastRecvTime = GetCurrentTime();
	dwDeadLockTime = dwLastRecvTime;

	EncPacketSendCount = 0x0010;
	EncPacketRecvCount = 0;
	EncRecvPacketCnt = 0;

	return TRUE;
}

int smWINSOCK::ConnectSock(char* szIP, WORD port)
{
	SOCKADDR_IN dest_sin;
	SOCKET	msock;
	int status;

	msock = socket(AF_INET, SOCK_STREAM, 0);
	if (msock == INVALID_SOCKET) {
		return FALSE;
	}

	dest_sin.sin_family = AF_INET;
	dest_sin.sin_addr.S_un.S_addr = inet_addr(szIP);
	dest_sin.sin_port = htons((u_short)port);

	if (connect(msock, (PSOCKADDR)&dest_sin, sizeof(dest_sin)) == SOCKET_ERROR) {
		closesocket(msock);
		return FALSE;
	}

	lstrcpy(szIPAddr, szIP);
	ConnectDirection = TRUE;
	dwPort = port;

	status = WSAAsyncSelect(msock, hMsgWnd, WSA_READ, FD_READ | FD_WRITE | FD_CLOSE);

	sock = msock;
	acc_sin.sin_addr.S_un.S_addr = inet_addr(szIP);

	PacketSendQueCnt = 0;
	WaitReadMessage = 0;
	PostReadMessage = 0;
	RecvPacketCount = 0;
	SendPacketCount = 0;
	RecvPacketErrorCount = 0;
	SendPacketErrorCount = 0;
	RecvPopCount = 0;
	RecvPopErrorCount = 0;
	dwLastRecvTime = GetCurrentTime();
	dwDeadLockTime = dwLastRecvTime;

	EncPacketSendCount = 0x0010;
	EncPacketRecvCount = 0;
	EncRecvPacketCnt = 0;

	dwEncPacketCode = smTRANSCODE_ENCODE_PACKET;

#ifdef _PACKET_PASS_XOR
	bEncXor = _PACKET_PASS_XOR;
	bDecXor = _PACKET_PASS_XOR;
#else
	bEncXor = 0;
	bDecXor = 0;
#endif

	CreateTransThread(TRANSMODE_DUAL);

	int sockBufferSizeRecv;
	int sockBufferSizeSend;

	sockBufferSizeRecv = 16384;
	sockBufferSizeSend = 32768;

	setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&sockBufferSizeRecv, sizeof(sockBufferSizeRecv));
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&sockBufferSizeSend, sizeof(sockBufferSizeSend));

	return TRUE;
}

int smWINSOCK::CloseSocket()
{
	DisconnectPlayer(MyPoint);

	closesocket(sock);

	sock = 0;
	smRecvState.Sock = 0;
	smSendState.Sock = 0;

	return TRUE;
}

extern char* szNetLogFile;
extern FILE* fpNetLog;

int smWINSOCK::Send(char* SendData, int len, int ImpMode)
{
	if (lpSocketData)
	{
		lpSocketData->SendPacket((Packet*)SendData, FALSE);
		return TRUE;
	}

	return FALSE;
}

int smWINSOCK::Send2(char* SendData, int len, int ImpMode)
{
	if (lpSocketData)
	{
		lpSocketData->SendPacket((Packet*)SendData, FALSE);
		return TRUE;
	}

	return FALSE;
}

int smWINSOCK::Send3(char* SendData, int len, int ImpMode)
{
	if (lpSocketData)
	{
		lpSocketData->SendPacket((Packet*)SendData, FALSE);
		return TRUE;
	}

	return FALSE;
}

int	smWINSOCK::CheckEncRecvPacket(int RecvCount)
{
	int cnt;
	int mCnt;

	for (cnt = EncRecvPacketCnt - ENC_PACKET_REC_MAX; cnt < EncRecvPacketCnt; cnt++) {
		if (cnt >= 0) {
			mCnt = cnt & ENC_PACKET_REC_MASK;
			if (EncRecvPackets[mCnt] == RecvCount) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

int	smWINSOCK::PushEncRecvPacket(int RecvCount)
{
	int mCnt;

	mCnt = EncRecvPacketCnt & ENC_PACKET_REC_MASK;
	EncRecvPackets[mCnt] = RecvCount;
	EncRecvPacketCnt++;

	if (EncPacketRecvCount < RecvCount)
		EncPacketRecvCount = RecvCount;

	return EncRecvPacketCnt;
}

int smWINSOCK::CreateTransThread(int Mode)
{
	smRecvState.Sock = sock;
	smSendState.Sock = sock;

	ExtData1 = 0;
	lpSocketData = 0;
	ExtData3 = 0;
	ExtData4 = 0;

	return TRUE;
}

void InitGameSocket(int ThreadMode)
{
	int cnt;
	WSADATA WSAData;
	char szTemp[80];
	int status;

	hMsgWnd = hwnd;

	if ((status = WSAStartup(MAKEWORD(1, 1), &WSAData)) != 0) {
		sprintf(szTemp, "%d is the err", status);
		MessageBox(hMsgWnd, szTemp, "Error", MB_OK);
	}

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		smWSock[cnt].sock = 0;
		smWSock[cnt].MyPoint = &smWSock[cnt];
		smWSock[cnt].MyNum = cnt;
		smWSock[cnt].smRecvState.smMySock = &smWSock[cnt];
		smWSock[cnt].smSendState.smMySock = &smWSock[cnt];
	}

	if (ThreadMode)
	{
		smTransThreadMode = ThreadMode;
	}
	else
	{
		smTransThreadMode = 0;
	}

	InitializeCriticalSection(&cSocketSection);
}

smWINSOCK* smConnectSock(char* szIP, WORD port)
{
	int cnt;
	smWINSOCK* lpsmSock = 0;

	EnterCriticalSection(&cSocketSection);

	for (cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (smWSock[cnt].sock == 0)
		{
			if ((smWSock[cnt].lpSocketData = pcSocketGame->Connect(szIP, port, &smWSock[cnt])) != NULL)
				lpsmSock = &smWSock[cnt];
			break;
		}
	}

	LeaveCriticalSection(&cSocketSection);

	return lpsmSock;
}

smWINSOCK* smConnectSock3(char* szIP, WORD port)
{
	int cnt;
	smWINSOCK* lpsmSock = 0;

	if (smTransThreadMode)
	{
		for (cnt = CONNECTMAX - 1; cnt >= 0; cnt--)
		{
			if (smWSock[cnt].sock == 0)
			{
				if (smWSock[cnt].ConnectSock(szIP, port) != FALSE)
					lpsmSock = &smWSock[cnt];
				break;
			}
		}
	}
	else
	{
		for (cnt = CONNECTMAX - 1; cnt >= 0; cnt--)
		{
			if (smWSock[cnt].sock == 0)
			{
				if (smWSock[cnt].ConnectSock(szIP, port) != FALSE)
					lpsmSock = &smWSock[cnt];
				break;
			}
		}
	}

	return lpsmSock;
}

static int MsgRetryCount = 0;

int smReconnectSock(smWINSOCK* lpsmSock)
{
	int res;

	EnterCriticalSection(&cSocketSection);

	res = lpsmSock->ReconnectSock();

	LeaveCriticalSection(&cSocketSection);

	return res;
}

smWINSOCK* smConnectSock2(char* szIP, WORD port)
{
	int cnt;
	smWINSOCK* lpsmSock = 0;
	smWINSOCK* lpFindsmSock;
	DWORD	dwIP;

	EnterCriticalSection(&cSocketSection);

	dwIP = inet_addr(szIP);
	lpFindsmSock = smFindSocket2(dwIP);

	if (!lpsmSock)
	{
		if (smTransThreadMode)
		{
			for (cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (smWSock[cnt].sock == 0)
				{
					lpsmSock = &smWSock[cnt];
				}
			}
		}
		else
		{
			for (cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (smWSock[cnt].sock == 0)
				{
					if (smWSock[cnt].ConnectSock(szIP, port) != FALSE)
						lpsmSock = &smWSock[cnt];
					break;
				}
			}
		}
	}

	LeaveCriticalSection(&cSocketSection);

	return lpsmSock;
}

smWINSOCK* smFindSocket(char* szIP)
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (smWSock[cnt].sock && lstrcmpi(smWSock[cnt].szIPAddr, szIP) == 0)
			return &smWSock[cnt];
	}

	return NULL;
}

smWINSOCK* smFindSocket2(DWORD dwIP)
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (smWSock[cnt].sock && smWSock[cnt].acc_sin.sin_addr.S_un.S_addr == dwIP)
			return &smWSock[cnt];
	}

	return NULL;
}

void smEnterCSectionSocket()
{
	EnterCriticalSection(&cSocketSection);
}

void smLeaveCSectionSocket()
{
	LeaveCriticalSection(&cSocketSection);
}

static int status;
static char szBuff[128];
static SOCKADDR_IN local_sin;
static SOCKADDR_IN acc_sin;
static int acc_sin_len;

#define MAX_PENDING_CONNECTS 32
#define NO_FLAGS_SET         0
#define MY_MSG_LENGTH       80

SOCKET BindSock;

u_short BindPort = 23;

BOOL FillAddr(HWND hWnd, PSOCKADDR_IN psin, BOOL bClient);

void InitBindSock(int port)
{
}

void CloseBindSock()
{
	closesocket(BindSock);
}

BOOL FillAddr(
	HWND hWnd,
	PSOCKADDR_IN psin,
	BOOL bClient)
{
	DWORD dwSize;
	PHOSTENT phe;
	char szTemp[200];

	psin->sin_family = AF_INET;
	psin->sin_port = htons(BindPort);

	if (bClient) {
		phe = gethostbyname(szBuff);
		if (phe == NULL) {
			sprintf(szTemp, "%d is the error. Make sure '%s' is listed in the hosts file.", WSAGetLastError(), szBuff);

			MessageBox(hWnd, szTemp, "gethostbyname() failed.", MB_OK);
			return FALSE;
		}
		memcpy((char FAR*) & (psin->sin_addr), phe->h_addr,
			phe->h_length);
	}
	else {
		dwSize = sizeof(szBuff);
		gethostname(szBuff, dwSize);

		psin->sin_addr.s_addr = INADDR_ANY;
	}

	return TRUE;
}

int	EncodePacket(DWORD dwKey, DWORD PacketCnt, BYTE* lpPacket, BYTE* lpEncBuff)
{
	int cnt;
	BYTE ch;
	BYTE bNear;
	DWORD rKey, sKey;
	int	len;
	WORD wTotal;

	sKey = (dwKey << 16) | (PacketCnt & 0xFFFF);

	len = ((int*)lpPacket)[0];
	((int*)lpEncBuff)[0] = len + 8;
	((int*)lpEncBuff)[2] = sKey;

	rKey = sKey >> 4;
	rKey += len;

	bNear = (BYTE)(PacketCnt + dwKey);
	wTotal = 0;

	for (cnt = 4; cnt < len; cnt++) {
		wTotal += lpPacket[cnt];
		ch = lpPacket[cnt] ^ ((BYTE)rKey) ^ bNear;
		lpEncBuff[cnt + 8] = ch;
		rKey += cnt * (cnt >> 1);
#ifdef	_PACKET_PASS_XOR
		bNear = ch ^ _PACKET_PASS_XOR;
#else
		bNear = ch;
#endif
	}

	((int*)lpEncBuff)[1] = (dwKey & 0xFFFF0000) | wTotal;

	return TRUE;
}

DWORD DecodePacket(BYTE* lpPacket, BYTE* lpDecBuff)
{
	int cnt;
	BYTE ch;
	BYTE ch2;
	BYTE bNear;
	DWORD rKey, sKey;
	int	len;
	DWORD dwKey;
	DWORD PacketCnt;
	WORD wTotal;

	len = ((int*)lpPacket)[0] - 8;
	sKey = ((int*)lpPacket)[2];

	dwKey = sKey >> 16;
	PacketCnt = sKey & 0xFFFF;

	rKey = sKey >> 4;
	rKey += len;

	bNear = (BYTE)(PacketCnt + dwKey);
	wTotal = 0;

	((int*)lpDecBuff)[0] = len;

	for (cnt = 4; cnt < len; cnt++) {
		ch = lpPacket[cnt + 8];
		ch2 = ch;
		ch ^= ((BYTE)rKey) ^ bNear;
		lpDecBuff[cnt] = ch;
		rKey += cnt * (cnt >> 1);
#ifdef	_PACKET_PASS_XOR
		bNear = ch2 ^ _PACKET_PASS_XOR;
#else
		bNear = ch2;
#endif
		wTotal += ch;
	}

	if ((((int*)lpPacket)[1] & 0xFFFF) != wTotal)
		return NULL;

	return sKey;
}

int	EncodePacket2(DWORD dwKey, DWORD PacketCnt, BYTE* lpPacket, BYTE* lpEncBuff, BYTE bEncXor)
{
	int cnt;
	BYTE ch;
	BYTE bNear;
	DWORD rKey, sKey;
	int	len;
	WORD wTotal;

	dwKey |= smTRANSCODE_ENCODE_PACKET;
	sKey = (dwKey << 16) | (PacketCnt & 0xFFFF);

	len = ((int*)lpPacket)[0];
	((int*)lpEncBuff)[0] = len + 8;
	((int*)lpEncBuff)[2] = sKey;

	rKey = sKey >> 4;
	rKey += len;

	bNear = (BYTE)(PacketCnt + dwKey);
	wTotal = 0;

	for (cnt = 4; cnt < len; cnt++) {
		wTotal += lpPacket[cnt];
		ch = lpPacket[cnt] ^ ((BYTE)rKey) ^ bNear;
		lpEncBuff[cnt + 8] = ch;
		rKey += cnt * (cnt >> 1);
		bNear = ch ^ bEncXor;
	}

	((int*)lpEncBuff)[1] = (dwKey & 0xFFFF0000) | wTotal;

	return TRUE;
}

DWORD DecodePacket2(BYTE* lpPacket, BYTE* lpDecBuff, BYTE bDecXor)
{
	int cnt;
	BYTE ch;
	BYTE ch2;
	BYTE bNear;
	DWORD rKey, sKey;
	int	len;
	DWORD dwKey;
	DWORD PacketCnt;
	WORD wTotal;

	len = ((int*)lpPacket)[0] - 8;
	sKey = ((int*)lpPacket)[2];

	dwKey = sKey >> 16;
	PacketCnt = sKey & 0xFFFF;

	rKey = sKey >> 4;
	rKey += len;

	bNear = (BYTE)(PacketCnt + dwKey);
	wTotal = 0;

	((int*)lpDecBuff)[0] = len;

	for (cnt = 4; cnt < len; cnt++) {
		ch = lpPacket[cnt + 8];
		ch2 = ch;
		ch ^= ((BYTE)rKey) ^ bNear;
		lpDecBuff[cnt] = ch;
		rKey += cnt * (cnt >> 1);
		bNear = ch2 ^ bDecXor;
		wTotal += ch;
	}

	if ((((int*)lpPacket)[1] & 0xFFFF) != wTotal)
		return NULL;

	return sKey;
}

LPFN_EncodePacket	fnEncodePacket = 0;
LPFN_DecodePacket	fnDecodePacket = 0;
BYTE smwsock_EncodePacket_AsmCode[ENC_PACKET_ASM_SIZE];

smWINSOCK* GetFreeSock()
{
	smWINSOCK* free = NULL;

	for (int i = 0; i < CONNECTMAX; i++)
	{
		if (!smWSock[i].sock)
		{
			free = &smWSock[i];
			break;
		}
	}

	return free;
}

bool SockExists(ULONG ip)
{
	for (int i = 0; i < CONNECTMAX; i++)
	{
		if (smWSock[i].acc_sin.sin_addr.S_un.S_addr == ip && GetCurrentTime() - smWSock[i].dwDeadLockTime < 10000)
		{
			return true;
		}
	}
	return false;
}