#ifndef	_SMWSOCK_HEADER

#define	_SMWSOCK_HEADER

#include "nettype.hpp"

#define _PS_TALE

#ifdef _PS_TALE

#define TCP_GAMEPORT		8180

#include "language.h"

#ifdef	_LANGUAGE_KOREAN

#ifdef	_TEST_SERVER

#define TCP_SERVPORT		10009
#else
#define TCP_SERVPORT		10003
#endif

#endif

#ifdef	_LANGUAGE_CHINESE
#define TCP_SERVPORT		10004
#endif

#ifdef	_LANGUAGE_TAIWAN
#define TCP_SERVPORT		10005
#endif

#ifdef	_LANGUAGE_JAPANESE
#define TCP_SERVPORT		10006
#endif

#ifdef	_LANGUAGE_ENGLISH

#ifdef	_LANGUAGE_PHILIPIN
#define TCP_SERVPORT		10010
#else
#define TCP_SERVPORT		10007
#endif
#endif

#ifdef _LANGUAGE_VEITNAM
#define TCP_SERVPORT		10011
#endif

#ifdef _LANGUAGE_BRAZIL
#define TCP_SERVPORT		10003
#endif

#ifdef _LANGUAGE_ARGENTINA
#define TCP_SERVPORT		10014
#endif

#ifdef	_LANGUAGE_THAI
#define TCP_SERVPORT		10008
#endif

#define CONNECTMAX			64
#define	CONNECTMAX_MASK		63

#endif

#define smSOCKBUFF_SIZE 32768

extern int		smTransThreadMode;
extern int		smTransTurbRcvMode;

class smWINSOCK;

struct smTHREADSOCK {
	smWINSOCK* smMySock;

	SOCKET Sock;

	int RecvLen;
	int RecvCode;

	int BuffCnt;

	int NewData;

	DWORD dwExitThread;
	DWORD dwAcessTime;

	char Buff[smSOCKBUFF_SIZE + 256];
};

struct smTHREAD_ROUTE
{
	smTHREAD_ROUTE* MyPoint;
	int Sleep;
	int TimeOut;
	smTHREADSOCK* smThreadSock;
	DWORD dwSleepTime;

	HANDLE	hThread;
};

#define	ENC_PACKET_REC_MAX		16
#define	ENC_PACKET_REC_MASK		15

class SocketData;

class smWINSOCK {
public:
	smWINSOCK* MyPoint;
	DWORD	MyNum;

	SOCKET sock;

	void* ExtData1;
	SocketData* lpSocketData;
	void* ExtData3;
	void* ExtData4;

	smTHREADSOCK smRecvState;
	smTHREADSOCK smSendState;

	int online;
	int status;
	char szBuff[128];
	char szIPAddr[16];
	DWORD	dwPort;

	DWORD	dwLastRecvTime;
	DWORD	dwDeadLockTime;

	int	WaitReadMessage;
	int	PostReadMessage;

	int	PacketSendQueCnt;

	int	EncPacketSendCount;
	int	EncPacketRecvCount;

	int	EncRecvPackets[ENC_PACKET_REC_MAX];
	int	EncRecvPacketCnt;

	int ConnectDirection;

	SOCKADDR_IN local_sin;
	SOCKADDR_IN acc_sin;
	int acc_sin_len;

	DWORD dwRecvSusCount;

	int	RecvPacketCount;
	int	SendPacketCount;
	int	RecvPopCount;
	int	RecvPopErrorCount;
	int SendPacketErrorCount;
	int RecvPacketErrorCount;

	DWORD	dwEncPacketCode;
	BYTE	bEncXor;
	BYTE	bDecXor;

public:
	smWINSOCK();
	~smWINSOCK();

	int Send(char* SendData, int len, int ImpMode = 0);
	int Send2(char* SendData, int len, int ImpMode = 0);
	int Send3(char* SendData, int len, int ImpMode = 0);

	int	CheckEncRecvPacket(int RecvCount);
	int	PushEncRecvPacket(int RecvCount);

	int CloseSocket();

	int ReconnectSock();

	int ConnectSock(char* szIP, WORD port);

	int CreateTransThread(int Mode);
};

extern smWINSOCK	smWSock[CONNECTMAX];

#define WSA_ACCEPT			(WM_USER + 0)
#define WSA_READ			(WM_USER + 1)
#define SWM_SENDSUCCESS     (WM_USER + 10)
#define SWM_RECVSUCCESS     (WM_USER + 11)
#define SWM_MCONNECT		(WM_USER + 12)
#define SWM_MDISCONNECT		(WM_USER + 13)

extern	int	smTransRecvErrorCnt;
extern	int	smTransSendErrorCnt;
extern	int	smTransRecvErrorDisCnt;
extern	int	smTransSendErrorDisCnt;
extern	int smTransClearErrorCnt;
extern	int smRcvBuffOverCount;

void InitBindSock(int port);

void InitGameSocket(int ThreadMode = 0);

void CloseBindSock();

char* smGetMyIp();

DWORD smGetMyIp2();

char* ConvStrIP(DWORD dwIP);

smWINSOCK* smConnectSock(char* szIP, WORD port);

smWINSOCK* smConnectSock3(char* szIP, WORD port);

smWINSOCK* smConnectSock2(char* szIP, WORD port);

smWINSOCK* smFindSocket(char* szIP);

smWINSOCK* smFindSocket2(DWORD dwIP);

int smReconnectSock(smWINSOCK* lpsmSock);

int GetUseingSendThreadCount();

int GetUseingRecvThreadCount();

void smEnterCSectionSocket();

void smLeaveCSectionSocket();

DWORD DecodePacket(BYTE* lpPacket, BYTE* lpDecBuff);

int	EncodePacket(DWORD dwKey, DWORD PacketCnt, BYTE* lpPacket, BYTE* lpEncBuff);

int	EncodePacket2(DWORD dwKey, DWORD PacketCnt, BYTE* lpPacket, BYTE* lpEncBuff, BYTE bEncXor);

DWORD DecodePacket2(BYTE* lpPacket, BYTE* lpDecBuff, BYTE bDecXor);

typedef DWORD(*LPFN_EncodePacket)(DWORD dwKey, DWORD PacketCnt, BYTE* lpPacket, BYTE* lpEncBuff);
typedef DWORD(*LPFN_DecodePacket)(BYTE* lpPacket, BYTE* lpDecBuff);

extern LPFN_EncodePacket	fnEncodePacket;
extern LPFN_DecodePacket	fnDecodePacket;

#define	POS_ENC_START	0x0
#define	POS_ENC_PACCODE 0xB
#define POS_ENC_XOR		0x74

#define	POS_DEC_START	0xA0
#define	POS_DEC_XOR		0x11A

#define	ENC_PACKET_ASM_SIZE	0x150

extern BYTE smwsock_EncodePacket_AsmCode[ENC_PACKET_ASM_SIZE];

extern smWINSOCK* GetFreeSock();

extern bool SockExists(ULONG ip);

extern int ConnectPlayer(smWINSOCK* lpsmSock);
#endif
