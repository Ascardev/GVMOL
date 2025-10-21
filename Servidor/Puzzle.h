#include <d3d9.h>

enum EBrindeID
{
	BRINDEID_None = 0,
	BRINDEID_DRAXOS = 9000,
	BRINDEID_CELESTO = 9001
};

class Puzzle
{
public:
	static Puzzle* GetInstance() { static Puzzle instance; return &instance; };

	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void Open();
	void Close();
	bool IsOpen() { return fOpen; };
	void SendRequest();
	void RecvRequest(rsPLAYINFO* Player);
	void SendRandomItem(rsPLAYINFO* Player);
	void SendRandomItem2(rsPLAYINFO* Player);

private:
	int fOpen;
	int Images[5];
	char Password[5];
	LPDIRECT3DTEXTURE9 bImages[1];
	DWORD BrindeCode;
};
