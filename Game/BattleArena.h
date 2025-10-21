struct smTRANS_BA_INFO {
	int size;
	int code;
	int Flag;
	short EndTime;
};

class BattleArena
{
public:
	static BattleArena* GetInstance() { static BattleArena instance; return &instance; };

	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void Open();
	bool IsOpen() { return fOpen; };

	void Main();
	void OnBattle(rsPLAYINFO* Player, rsPLAYINFO* Player2);
	void OnEnter(rsPLAYINFO* Player);
	void OnClose(rsPLAYINFO* Player);
	int  GetFlag() { return Flag; };
	void SetFlag(DWORD Value) { Flag = Value; };
	void SetScore(int Score) { YourScore = Score; };

	short GetTime();
	void SetTime(int CurrentTime);
	void OpenBattle();
	void StartBattle();
	void RecvInformation(smTRANS_BA_INFO* ps);
	void SendInformation(rsPLAYINFO* Player);
	void SendUpgrade(rsPLAYINFO* Player);
	void RecvUpgrade(smTRANS_BA_SCORE* ps);
	void SendAward();
	void SendRequest();

private:
	int fOpen;
	int Flag;
	DWORD StartOpenTime;
	DWORD OverOpenTime;
	DWORD StartBattleTime;
	DWORD OverBattleTime;
	DWORD PlayTime[2];
	DWORD EndTime;
	int Images[5];
	LPDIRECT3DTEXTURE9 Icons[3];

	int  YourScore;
	char szName1[32];
	int  Score1;
	char szName2[32];
	int  Score2;
	char szName3[32];
	int  Score3;
};
