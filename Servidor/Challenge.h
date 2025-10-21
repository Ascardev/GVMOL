struct smTRANS_CHALLENGE {
	int size;
	int code;
	char szName[32];
};

class Challenge
{
public:
	static Challenge* GetInstance() { static Challenge instance; return &instance; };

	void DrawImage(int Image, int x, int y, int w, int h);
	void Main();
	void Init();
	void DrawText(char* Text, int x, int y, ID3DXFont* RegularFont, D3DCOLOR Color);
	void Draw();
	bool Challenge::MouseAction(int x, int y, int w, int h);
	void Button();
private:

	int Images[10];
	int Flag;
	float Opacity;
	int Queue;
};