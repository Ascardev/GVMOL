class DailyQuest
{
public:
	static DailyQuest * GetInstance() { static DailyQuest instance; return &instance; };
	void Open(int Param) { fOpen = true; Status = Param; };
	void Close() { fOpen = false; };
	bool IsOpen() { return fOpen; };
	void Init();
	bool MouseAction(int x, int y, int w, int h);
	void Draw();
	void DrawEngLevel();
	void DrawGet();
	void DrawProgress();
	void DrawEnd();
	void DrawWait();
	void LButton(int x, int y);
	void AnalyzeProgress(rsPLAYINFO * Player, DWORD Time);
	void SendProgressState(rsPLAYINFO * Player);
	void SendUpdateState(rsPLAYINFO * Player, int Param);
	void RecvProgressState(smTRANS_COMMAND * packet);
	void RecvUpdateState(smTRANS_COMMAND * packet);
	void UpdateProgress(rsPLAYINFO * Player);
	void AddExp(rsPLAYINFO *lpPlayInfo, int Exp);
	int  GetState() { return State; }
	int  GetType() { return Type; }
	int  GetNowProgress() { return Param[0]; }
	int  GetMaxProgress() { return Param[1]; }
private:
	int fOpen;
	int State;
	int Status;
	int Type;
	int Param[2];
	int Time;
	int Mat;
	int cImages[4];
};
