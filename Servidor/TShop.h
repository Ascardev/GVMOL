class TimeShop
{
public:
	static TimeShop * GetInstance() { static TimeShop instance; return &instance; };
	void SendList(rsPLAYINFO * Player);
	void SendTime(rsPLAYINFO * Player);
	void SendBuyItem();
	void Recv(PACKET_COIN_SHOP * packet);
	void RecvTime(smTRANS_COMMAND * packet);
	void RecvBuyItem(rsPLAYINFO * Player, PACKET_COIN_SHOP_BUY * packet);
	void Init();
	bool MouseAction(int x, int y, int w, int h);
	void Draw();
	void DrawText(char * Text, int x, int y, ID3DXFont * Font, D3DCOLOR Color);
	void LButton(int x, int y);
	void ButtonScroll(short Dist);
	void DrawItemOnList(int Line, LPDIRECT3DTEXTURE9 Image, char * Name, int Price, char * Description1, char * Description2, int num, int Width, int Height, int WinX, int WinY);
	void DrawItemOnDetails(LPDIRECT3DTEXTURE9 Image, char * Name, int Price, int Width, int Height);
	void Open() { fOpen = true; };
	void Close();
	bool IsOpen() { return fOpen; };
	int  GetTime() { return Time; };
	int  GetTotalScroll();
	int  GetTotalScroll2();
private:
	bool  fOpen;
	int   Time;
	int  Scroll;
	int  Scroll2;
	int  Tag;
	int  SubTag;
	int  WinItem;
	int cImages[60];
	LPDIRECT3DTEXTURE9 bImages[20];
	int IMG_TAG[MAX_TAG];
	int IMG_TAGH[MAX_TAG];
	LPDIRECT3DTEXTURE9 IMG_SUB_TAG[26];
	LPDIRECT3DTEXTURE9 IMG_SUB_TAGH[26];
	int  SpecBox;
	int  SpecItem;
	int  Counter;
	int  SelectItem;
};

extern PACKET_COIN_SHOP_BUY cTPacket;
