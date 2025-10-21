class HellGates
{
public:
	static HellGates* GetInstance() { static HellGates instance; return &instance; };

	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void Open();
	bool IsOpen() { return fOpen; };

	void DrawHP(smCHAR* Character);
	void OnEnter(rsPLAYINFO* Player);
	void OnClose(rsPLAYINFO* Player);
	void OpenBattle();
	void StartBattle();
	void Main();
	void SetFlag(DWORD Value) { Flag = Value; };
	void SendInformation(rsPLAYINFO* Player);
	void SendAward(rsPLAYINFO* Player);
	void SendRequest();
	void RecvInformation(smTRANS_BA_INFO* ps);
	void SetTime(int CurrentTime);
	short GetTime();
	int  GetFlag() { return Flag; };

private:

	int Flag;
	int Round;
	int TeleportFlag;
	DWORD TeleportTime;
	DWORD StartOpenTime;
	DWORD OverOpenTime;
	DWORD StartBattleTime;
	DWORD OverBattleTime;
	DWORD PlayTime[2];
	DWORD EndTime;
	smCHAR* Boss;

	int fOpen;
	int Images[7];
};
