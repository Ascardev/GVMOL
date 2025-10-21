#ifndef _HO_PARTY_H_
#define _HO_PARTY_H_

#define MAX_PARTY_MEMBER	6

struct hoPartyMember
{
	char	Name[256];
	DWORD	ChrCode;
	int		Life;
	int		Level;
	int     JobCode;

	POINT3D CharacterPos;
	BOOL	JangFlag;

	char	ModelName1[64];
	char	ModelName2[64];
};

#define PARTY_NONE		500
#define PARTY_START		1000
#define PARTY_PROCESS	2000
#define PARTY_END		3000

class HoParty_KTJ
{
public:
	HoParty_KTJ();
	~HoParty_KTJ();

	int									MatPartyBackGround;
	int									MatTitle[4 + 2];
	POINT								BackStartPos;
	int xLeft, xRight;

	RECT menuPos[30];
	int menuSu;
	int PmenuN, savePmenuN;
	void InitMenuSet(int menuN);

	int  questSelN;
	void quest_Progress_Clear();
	void quest_End_Clear();
	void quest_Progress_Set(char* q_name, char* f_name);
	int  qNameProgress_SU;
	void quest_End_Set(char* q_name, char* f_name);
	int  qNameEnd_SU;
	int  qNameS_ENDs, qNameE_ENDs;
	void qN_Pressf_CLEAR();

	void quest_Sel_Progress();

	int  qNameS, qNameE;
	int  qNameSelN;
	char qNameb[64][128];
	char qFnameb[64][128];

	char qNameb_E[64][128];
	char qFnameb_E[64][128];

	char q_explation[64][128];
	int  q_explationS;
	char q_explationTitle[128];

	char latestb[9][128];
	int  latestb_LOG[9 + 1];

	int fNameS, fNameE, fNameSu;
	char fNameb[100 + 1][32];
	int  fClass[100];
	int  fOn[100];
	int  fName_LOG[100 + 1];

	int dNameS, dNameE, dNameSu;
	int dNameSelN;
	char dNameb[100 + 1][32];
	int  dName_LOG[100 + 1];

	int cN_MenuN;
	int cN_Pressf;
	int cN_PressfDBL;
	int cN_PressfDBL_Where;

	void chat_PageChange(int sw);
	void chat_IDdelete();
	void chat_isLOG(char* name, int flag);

	void chat_cN_Pressf(int press);
	void chat_IDinsert(int sw, char* id, int Class = 0);

	void chatINI_read();
	void chatINI_save(int menuN);
	void chatDATA_Insert(int menuN, char* str, int Class = 0);
	void chatDATA_delete(int menuN, int num);
	void latest_Insert(char* namestr);
	int chat_IDs(int dataN, int cnt, char* id);
	void chat_WhisperPartyPlayer(int num);
	void chat_WhisperPartyPlayer_close();

	int chatbuild_INIfiles();

	void chat_changeMENU(int sw);

	hoPartyMember	PartyMember[MAX_PARTY_MEMBER];
	int				PartyMemberCount;

	int									PartyPosState;
	int									MouseDownPartyMember;

	int									MouseDownButton;

	LPDIRECT3DTEXTURE9				BmpMan[3];

	LPDIRECT3DTEXTURE9				BmpLifeBlue;
	LPDIRECT3DTEXTURE9				BmpLifeRed;

	LPDIRECT3DTEXTURE9				ToolTip[5];
	LPDIRECT3DTEXTURE9				Button[5];

	POINT								TextStartPos;

	int									MatMessageBoxBackGround;
	POINT								MessageBoxStartPos;

	char								PartyMessageBoxChrName[128];
	DWORD								PartyMessageBoxChrCode;

	LPDIRECT3DTEXTURE9				BmpMessageOk[2];
	LPDIRECT3DTEXTURE9				BmpMessageCancel[2];

	int				MessageBoxDrawCount;
	BOOL			MessageBoxOpenFlag;

	void Init();
	void Load();
	void Close();

	int	 Draw();

	int Main_menuSet(int sw);
	int	 Main(int sw);

	int  AddMember(char* memberName, DWORD chrCode, int life, int level, int jobcode);

	int AddMember(hoPartyMember* member, int cnt);
	void AddMember_memberSu(int memberSu);
	int PARTY_PLAYUPDATE(hoPartyMember* member, int cnt);
	int PARTY_RELEASE();

	int chkeckMenuN();
	void menuSet(int sw);

	void Draw_questExplane(int x, int y);
	void Init_questExplane(char* string, int sw);

	int ReadFileData(char* fname);
	void ReadFileData_moveBuf(char* savebuf, int lineLen);
};

class HoParty
{
public:
	HoParty();
	~HoParty();

	void quest_Progress_Clear();
	void quest_End_Clear();
	void quest_Progress_Set(char* q_name, char* f_name);
	void quest_End_Set(char* q_name, char* f_name);
	void qN_Pressf_CLEAR();
	void quest_Sel_Progress();

	void latest_Insert(char* namest);
	void friend_Insert(char* id, int Class);
	void chat_isLOG(char* id, int flag);
	int  chat_IDs(int dataN, int cnt, char* id);

	void Main_menuSet(int menuN);
	void chat_changeMENU(int sw);
	int chatbuild_INIfiles();

	void chat_WhisperPartyPlayer_close();

	void DrawImage(int Image, int x, int y, int w, int h);

	void InitMenuSet(int menuN);

public:
	hoPartyMember	PartyMember[MAX_PARTY_MEMBER];
	int				PartyMemberCount;

	int									PartyPosState;
	int									MouseDownPartyMember;

private:

	int									MouseDownButton;

	int									MatPartyBackGround;
	LPDIRECT3DTEXTURE9				BmpMan[3];

	LPDIRECT3DTEXTURE9				BmpLifeBlue;
	LPDIRECT3DTEXTURE9				BmpLifeRed;

	LPDIRECT3DTEXTURE9				ToolTip[5];
	LPDIRECT3DTEXTURE9				Button[5];

	POINT								BackStartPos;
	POINT								TextStartPos;

	int									MatMessageBoxBackGround;
	int LpButtonYes;
	int LpButtonYes_;
	int LpButtonNo;
	int LpButtonNo_;
	POINT								MessageBoxStartPos;

	char								PartyMessageBoxChrName[128];
	DWORD								PartyMessageBoxChrCode;

	LPDIRECT3DTEXTURE9				BmpMessageOk[2];
	LPDIRECT3DTEXTURE9				BmpMessageCancel[2];

	int				MessageBoxDrawCount;
public:
	BOOL			MessageBoxOpenFlag;

	void Init();
	void Load();
	void Close();

	int	 Draw();
	int	 Main();

	int	AddMember(char* member, DWORD chrCode, int life, int level, int jobcode);

	int	 AddMember(hoPartyMember* member, int cnt);
	void AddMember_memberSu(int memberSu);
	int  PARTY_PLAYUPDATE(hoPartyMember* member, int cnt);
	void PARTY_RELEASE();

	int SetParty(char* chrName, DWORD chrCode)
	{
		memset(PartyMessageBoxChrName, 0, sizeof(PartyMessageBoxChrName));
		wsprintf(PartyMessageBoxChrName, "%s", chrName);

		PartyMessageBoxChrCode = chrCode;
		MessageBoxOpenFlag = TRUE;

		return TRUE;
	}

	void DrawPartyMessage(int x, int y);
	void MainPartyMessage(int x, int y);
};

class HoEffectHitBoard
{
public:
	HoEffectHitBoard();
	~HoEffectHitBoard();

	float   BackPutSizeX;
	float   BackPutSizeY;
	float   BackPutAlpha;

	float  TextPutSizeX;
	float  TextPutSizeY;
	float  TextPutAlpha;

	float	CriticalPutSizeX;
	float	CriticalPutSizeY;
	float	CriticalPutAlpha;

	int MatHitBackBoard;
	int MatHitCount;

	BOOL CriticalFlag;
	char BufferNum[256];
	void Load();

	int Draw();
	int Main();

	int Start(char* num, BOOL criticalFlag = FALSE);

private:
	int StartFlag;
};

#endif
