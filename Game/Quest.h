enum EQuestID
{
	QUESTID_None = 0,
	QUESTID_150A = 5000,
	QUESTID_150B = 5001,
	QUESTID_START = 5002,
	QUESTID_GUIDE = 5003,
	NPC_ERAGONCAVE = 5004,
	NPC_SKINVIEW = 5005,
	NPC_BATTLEARENA = 5006,
	NPC_PLAYERMIGRATION = 5007,
	QUESTID_155A = 5008,
	QUESTID_160A = 5009,
	NPC_SEA_ABYSS = 5010,
	NPC_ANCIENT_WEAPON = 5011,
	NPC_HEART_FIRE = 5012,
	NPC_HELLGATES = 5013,
	NPC_AWARDITEM = 5014,
	NPC_LOCKITEM = 5015,
	NPC_PUZZLE = 5016,
	NPC_UPDATEITEM = 5017,
	QUESTID_160B = 5018,
	QUESTID_TRAJE = 5019,
	QUESTID_BOTA = 5020,
	QUESTID_AMULETO = 5021,
	NPC_NATAL = 5022,
	NPC_WORLDCUP = 5023
};

struct PACKET_QUEST
{
	int size;
	int code;
	int QuestStart_State;
	int QuestStart_Param1;
	int QuestStart_Param2;

	int QuestBota_State;
	int QuestBota_Param1;
	int QuestBota_Param2;

	int QuestAmuleto_State;
	int QuestAmuleto_Param1;
	int QuestAmuleto_Param2;
	int QuestAmuleto_Param3;
	int QuestAmuleto_Param4;

	int QuestTraje_State;
	int QuestTraje_Param1;
	int QuestTraje_Param2;

	int QuestLv150A_State;
	int QuestLv150A_Param;
	int QuestLv150A_Time;
	int QuestLv150A_Type;
	int QuestLv150B_State;
	int QuestLv150B_Param;
	int QuestLv150B_Time;
	int QuestLv155A_State;
	int QuestLv155A_Param;
	int QuestLv155A_Time;
	int QuestLv155A_Type;
	int QuestLv160A_State;
	int QuestLv160A_Param1;
	int QuestLv160A_Param2;
	int QuestLv160A_Time;
	int QuestLv160A_Type;
	int QuestLv160B_State;
	int QuestLv160B_Param;
	int QuestLv160B_Time;
	int QuestLv160B_Type;
};

class Quest
{
public:
	static Quest* GetInstance() { static Quest instance; return &instance; };

	bool MouseAction(int x, int y, int w, int h);
	void Init();
	void Main();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void DrawNPC();
	void Button();
	void RButton();
	void ButtonNPC();
	void OpenNPC(DWORD Code);
	void ActionNPC();
	bool StopCharacter();
	bool IsOpen() { return fOpen; };

	void Updater(EQuestID Quest);
	void UpdaterProgressOnServer(rsPLAYINFO* Player, smCHAR* Mob, DWORD Code);
	void UpdaterProgressOnClient(smCHAR* Mob, DWORD Code);
	void CancelProgress(rsPLAYINFO* Player, smTRANS_COMMAND* packet);
	void AnalyzeProgress(rsPLAYINFO* Player, smTRANS_COMMAND* packet);
	void SendProgress(rsPLAYINFO* Player);
	void SendCancelToServer();
	void SendProgressToServer();
	void RecvProgress(PACKET_QUEST* packet);
	void sinCheckQuest(int Param);
	void PlayerKillingOnClient();
	void PlayerKillingOnServer(rsPLAYINFO* Player);

private:
	int QuestStart_State;
	int QuestStart_Param1;
	int QuestStart_Param2;

	int QuestBota_State;
	int QuestBota_Param1;
	int QuestBota_Param2;

	int QuestAmuleto_State;
	int QuestAmuleto_Param1;
	int QuestAmuleto_Param2;
	int QuestAmuleto_Param3;
	int QuestAmuleto_Param4;

	int QuestTraje_State;
	int QuestTraje_Param1;
	int QuestTraje_Param2;

	int QuestLv150A_State;
	int QuestLv150A_Param;
	int QuestLv150A_Time;
	int QuestLv150A_Type;

	int QuestLv150B_State;
	int QuestLv150B_Param;
	int QuestLv150B_Time;

	int QuestLv155A_State;
	int QuestLv155A_Param;
	int QuestLv155A_Time;
	int QuestLv155A_Type;

	int QuestLv160A_State;
	int QuestLv160A_Param1;
	//	int QuestLv160A_Param2;
	int QuestLv160A_Time;
	int QuestLv160A_Type;

	int QuestLv160B_State;
	int QuestLv160B_Param;
	int QuestLv160B_Time;
	int QuestLv160B_Type;

	int Images[11];

	int ShowProgress, ShowProgress2, ShowProgress3, ShowProgress4, ShowProgress5, ShowProgress6, ShowProgress7, ShowProgress8, ShowProgress9;
	float Size, Opacity, FX;
	float Size2, Opacity2, FX2;
	float Size3, Opacity3, FX3;
	float Size4, Opacity4, FX4;
	float Size5, Opacity5, FX5;
	float Size6, Opacity6, FX6;
	float Size7, Opacity7, FX7;
	float Size8, Opacity8, FX8;
	float Size9, Opacity9, FX9;

	int fOpen;
	int Type;
	DWORD QuestCode;
};
