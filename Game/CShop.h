#define MAX_TAG 4

#define TAG_ACESSORIES 1
#define TAG_PREMIUM    2
#define TAG_FUN        3

#define SUB_TAG_AMULETS    1
#define SUB_TAG_RINGS      2
#define SUB_TAG_SHELTOMS   3
#define SUB_TAG_FORCE_ORBS 4
#define SUB_TAG_COMBATS    5
#define SUB_TAG_AGING      6
#define SUB_TAG_MIXING     7
#define SUB_TAG_GOLD       8
#define SUB_TAG_CRYSTALS   9
#define SUB_TAG_PETS       10
#define SUB_TAG_COSTUMES   11

struct ITEM_COIN_SHOP
{
	int Flag;
	int SubTag;
	char szCode[32], szName[32], Description1[32], Description2[32], Dir[32];
	int Price;

	int     Width;
	int     Height;

	sITEMINFO ItemInfo;

	LPDIRECT3DTEXTURE9 Image;
};

struct PACKET_COIN_SHOP
{
	int size;
	int code;
	ITEM_COIN_SHOP item;
};

struct PACKET_COIN_SHOP_BUY
{
	int size;
	int code;
	char szCode[32];
	int  spec;
	int  cnt;
};

struct PACKET_RECV_VIP
{
	int size;
	int code;
	DWORD	dwTime_PrimeItem_VIP;
	DWORD	dwParam_PrimeItem_VIP;
};

struct PACKET_SET_CLASS {
	int size;
	int code;
	int Class;
};

struct PACKET_ITEM_CLASS {
	int size;
	int code;
	int weapon;
	int armor;
	int shield;
	int bracelets;
	int gauntlets;
	int boots;
	int ring;
	int amy;
	int shel;
	DWORD time;
};

struct PACKET_SEND_ITEM {
	int size;
	int code;
	int spec;
	int weapon;
	int result;
	sITEM sItem;
};

class CoinShop
{
public:
	static CoinShop* GetInstance() { static CoinShop instance; return &instance; };
	void SendList(rsPLAYINFO* Player);
	void SendCoin(rsPLAYINFO* Player);
	void SendBuyItem();
	void Recv(PACKET_COIN_SHOP* packet);
	void RecvCoin(smTRANS_COMMAND* packet);
	void RecvBuyItem(rsPLAYINFO* Player, PACKET_COIN_SHOP_BUY* packet);
	void RecvItemOnServer(rsPLAYINFO* Player, PACKET_SEND_ITEM* packet);
	void RecvItemOnGame(PACKET_SEND_ITEM* packet);
	void SendItemToServer();
	void Main();
	void Init();
	int   Coin;
	bool MouseAction(int x, int y, int w, int h);
	void Draw();
	void DrawText(char* Text, int x, int y, ID3DXFont* Font, D3DCOLOR Color);
	void LButton(int x, int y);
	void RButton(int x, int y);
	void ButtonScroll(short Dist);
	void DrawVipOnList(int Line, char* Name, int Price, char* Description1, char* Description2, int num, int Width, int Height, int WinX, int WinY);
	void DrawItemOnList(int Line, LPDIRECT3DTEXTURE9 Image, char* Name, int Price, char* Description1, char* Description2, int num, int Width, int Height, int WinX, int WinY);
	void DrawItemOnDetails(LPDIRECT3DTEXTURE9 Image, char* Name, int Price, int Width, int Height);
	void DrawChangeItemDetails();
	void Open() { fOpen = true; };
	void Close();
	bool IsOpen() { return fOpen; };
	int  GetCoin() { return Coin; };
	int  GetUserCoin(rsPLAYINFO* Player);
	void SubCoin(rsPLAYINFO* Player, int Coin);
	void AddCoin(rsPLAYINFO* Player, int Coin);
	sITEM* GetItem() { return &sItemChange; };
	int  GetTotalSlot();
	int  GetTotalScroll();
	int  GetTotalScroll2();
	BOOL TransferTradeCoin(rsPLAYINFO* Player, rsPLAYINFO* Player2, int nCoin);
	BOOL CheckTradeCoin(rsPLAYINFO* Player, rsPLAYINFO* Player2, TRANS_TRADEITEMS* lpTransTradeItems);
	void PlusCoin(int Coin);
	void MinusCoin(int Coin);
	void RecvPVIP(PACKET_RECV_VIP* packet);
	void RecvItemClass(PACKET_ITEM_CLASS* packet);
private:
	bool  fOpen;
	int  Scroll;
	int  Scroll2;
	int  Tag;
	int  SubTag;
	int  WinItem;
	int cImages[60];
	LPDIRECT3DTEXTURE9 bImages[20];
	int IMG_TAG[6];
	int IMG_TAGH[6];
	LPDIRECT3DTEXTURE9 IMG_SUB_TAG[44];
	LPDIRECT3DTEXTURE9 IMG_SUB_TAGH[44];
	sITEM sItemChange;
	int  SpecBox;
	int  SpecItem;
	int  ClassBox;
	int  ClassType;
	int  Counter;
	int  SelectItem;

	int WeaponClass;
	int ArmorClass;
	int ShieldClass;
	int BraceletsClass;
	int GauntletsClass;
	int BootsClass;
	int RingClass;
	int AmyClass;
	int ShelClass;
	DWORD TimeClass;
};

extern PACKET_COIN_SHOP_BUY cCPacket;
extern CoinShop cCoinShop;