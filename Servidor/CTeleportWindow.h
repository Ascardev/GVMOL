#pragma once

bool isMousePos(int x, int y, int w, int h);

class TCORE {

public:
	static TCORE* GetInstance() { static TCORE instance; return &instance; };
	void tcoreOpen() { this->Open = 1; };
	void tcoreClose() { this->Open = 0; };
	void tcoreVeriflevel(int lvl);
	void init();
	void Draw();
	void DrawImage(int Mat, int x, int y, int w, int h);
	bool MouseIn();
	enum img { JANELA, BTNTELEPORT, BTNTELEPORT_, BTNCLOSE, BTNCLOSE_, EXP, HUNT, GOLD, TOWN, SHELTONS, PVP, HUNTPVP };
	int imagens[20];
	int imgs[14];
	//enum maps{};
	bool IsOpen() { return Open; };




private:

	int Open;

};