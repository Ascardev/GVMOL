#include <d3d9.h>

struct smPACKET_LOCK {
	int size;
	int code;
	sITEM* sItem;
	char Password[5];
};

class LockItem
{
public:
	static LockItem* GetInstance() { static LockItem instance; return &instance; };

	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void Open();
	void Close();
	bool IsOpen() { return fOpen; };
	void RecvRequest(rsPLAYINFO* Player, smPACKET_LOCK* packet);
	void SendRequest();
	sITEM* GetItem() { return &sItem; };

private:
	int fOpen;
	int Images[5];
	char Password[5];
	LPDIRECT3DTEXTURE9 bImages[1];
	LPDIRECT3DTEXTURE9 buttonImage[12];
	LPDIRECT3DTEXTURE9 buttonImageHover[12];
	sITEM sItem;
};
