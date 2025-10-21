#define PSOCIAL_ACTION 0x46470000

struct PACKET_SOCIAL
{
	int size;
	int code;
	int action;
	char name[32];
	int  Class;
	int  Status;
	int  Level;
	int  Type;
};

class Social
{
public:
	static Social* GetInstance() { static Social instance; return &instance; };

	void SendList(rsPLAYINFO* Player, char* ClanName);
	void SendClanList(rsPLAYINFO* Player);
	void SendFriendList(rsPLAYINFO* player);
	void SendRefuseList(rsPLAYINFO* player);
	void AddOnFriendList(rsPLAYINFO* player, char* name);
	void DeleteOnFriendList(rsPLAYINFO* player, char* name);
	void AddOnRefuseList(rsPLAYINFO* player, char* name);
	void DeleteOnRefuseList(rsPLAYINFO* player, char* name);
	void SendAction(rsPLAYINFO* player, PACKET_SOCIAL* packet);
	int  YouAreRefuse(rsPLAYINFO* player1, rsPLAYINFO* player2);
	void UpdateStatus(char* Name);

	bool MouseAction(int x, int y, int w, int h);
	void DrawImage(int Texture, int x, int y, int w, int h, int op);
	void Init();
	void Main();
	void ButtonUp();
	void Button();
	int  StopCharacter();
	void Draw();
	bool IsOpen() { return Show; };
	bool IsMoveWindow() { return MoveWindow; };
	long GetCursorX() { return Cursor.x; };
	long GetCursorY() { return Cursor.y; };
	void  Open() { InterfaceParty.PartyPosState = PARTY_END; Show = true; };
	void  Close() { Show = false; SubTag = 0; };
	void  ClearFriendList();
	void  ClearRefuseList();
	void  ClearClanList();
	void  RecvFriendList(PACKET_SOCIAL* packet);
	void  RecvRefuseList(PACKET_SOCIAL* packet);
	void  RecvClanList(PACKET_SOCIAL* packet);
	void  RecvAction(PACKET_SOCIAL* packet);
	void  AddFriend(char* Name, int Class);
	void  DeleteFriend(char* Name);
	void  AddRefuse(char* Name);
	void  DeleteRefuse(char* Name);
	int   GetTotalClan();
	int   GetTotalFriend();
	int   GetTotalScroll();
	void  ButtonScroll(short Dist);
	void  DoubleClick();
	void  Resize();
	void  Connect(char* Name);
	void  Disconnect(char* Name);
private:
	int Images[45];
	int ImagesJob[10];
	int Show;
	float NowX;
	float MoveX;
	float MoveY;
	int ButtonU;
	int MoveWindow;
	int Opacity;
	int Tag;
	int SubTag;
	int Check;
	POINT Cursor;
	PACKET_SOCIAL FriendList[100];
	PACKET_SOCIAL RefuseList[100];
	PACKET_SOCIAL ClanList[100];
	std::vector<char*> OnlinePlayers;
	int cnt1;
	int cnt2;
	int cnt3;
	int Scroll;
};