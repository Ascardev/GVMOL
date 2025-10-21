#include <d3d9.h>

struct smPACKET_UPDATE_ITEM {
	int size;
	int code;
	sITEM sItem[2];
};

class UpdateItem
{
public:
	static UpdateItem* GetInstance() { static UpdateItem instance; return &instance; };

	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void Open();
	void Close();
	bool IsOpen() { return fOpen; };
	void RecvRequest(rsPLAYINFO* Player, smPACKET_UPDATE_ITEM* packet);
	void RecvRequestOnClient(smPACKET_UPDATE_ITEM* packet);
	void SendRequest();
	void SendItemList(rsPLAYINFO* Player);
	void RecvItemList(smTRANS_COMMAND* packet);
	sITEM* GetItem() { return &sItem[0]; };
	sITEM* GetStone() { return &sItem[1]; };

private:
	int fOpen;
	int Images[5];
	char Password[5];
	LPDIRECT3DTEXTURE9 bImages[2];
	std::vector<int> ItemList;
	sITEM sItem[2];
};
