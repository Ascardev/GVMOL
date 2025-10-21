typedef struct _gamedate {
	char	UserID[30];
	char	GPCode[16];
	char	DisuseDay[30];
	char    UsePeriod[30];
	char	Guid[50];
	char	PCRno[14];
} gamedate;

typedef struct _PACKET {
	int size;
	int code;
	int OpenLiveCode;
	_gamedate jungdata;
} PACKET;

typedef struct _RPACKET {
	int size;
	int code;
	char UserID[30];
} RPACKET;

int	RecvOpenLivePacket(smWINSOCK* lpsmSock, void* Packet);
