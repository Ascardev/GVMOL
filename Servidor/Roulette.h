#include <d3d9.h>

struct ROULETTE_ITEM {
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

class Roulette
{
public:
	static Roulette* GetInstance() { static Roulette instance; return &instance; };

	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Main();
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void Open(smTRANS_COMMAND* packet);
	void Close();
	bool IsOpen() { return fOpen; };
	void RecvRequest(rsPLAYINFO* Player, smTRANS_COMMAND* packet);
	void SendRequest();
	void SendList(rsPLAYINFO* Player);
	void SendRandomItem(rsPLAYINFO* Player);
	void RecvList(ROULETTE_ITEM* packet);

private:
	int fOpen;
	int Images[5];
	LPDIRECT3DTEXTURE9 bImages[1];
	AWARD_ITEM RecvItem[100];
	int SelectItem;
	int ItemCount;
	int Opacity;
	int Point;
};
