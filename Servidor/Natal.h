#include <d3d9.h>


class Natal
{
public:
	static Natal* GetInstance() { static Natal instance; return &instance; };

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

private:
	int fOpen;
	int Images[5];
	char Password[5];
	LPDIRECT3DTEXTURE9 bImages[1];
};
