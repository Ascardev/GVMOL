#include <d3d9.h>

struct AWARD_ITEM {
	int size;
	int code;
	int flag;
	int Id;
	char Name[32];
	char Code[4];
	LPDIRECT3DTEXTURE9 Image;
	int w;
	int h;
};

class AwardItem
{
public:
	static AwardItem* GetInstance() { static AwardItem instance; return &instance; };

	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void Open();
	void Close();
	bool IsOpen() { return fOpen; };
	void RecvRequest(rsPLAYINFO* Player, smTRANS_COMMAND* packet);
	void SendRequest();
	void SaveItem(rsPLAYINFO* Player, char* szName, char* szCode);
	void SendList(rsPLAYINFO* Player);
	void RecvList(AWARD_ITEM* packet);

private:
	int fOpen;
	int Images[9];
	LPDIRECT3DTEXTURE9 bImages[1];
	AWARD_ITEM RecvItem[10];
	int SelectItem;
	int ItemCount;
};
