class BattleEvent
{
public:
	static BattleEvent* GetInstance() { static BattleEvent instance; return &instance; };

	void Init();
	void Draw();

	void OnBattle(rsPLAYINFO* Player, rsPLAYINFO* Player2);
	void OnEnter(rsPLAYINFO* Player);
	void OnClose(rsPLAYINFO* Player);
	int  GetFlag() { return Flag; };
	void SetFlag(DWORD Value) { Flag = Value; };
	void SetScore(int Score) { YourScore = Score; };

	void OpenBattle();
	void StartBattle();
	void RecvInformation(smTRANS_BA_INFO* ps);
	void SendInformation(rsPLAYINFO* Player);
	void SendUpgrade(rsPLAYINFO* Player);
	void RecvUpgrade(smTRANS_BA_SCORE* ps);
	void SendAward();

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
