class Loading
{
public:
	static Loading* GetInstance() { static Loading instance; return &instance; };
	void Init();
	void Main();
	void Draw();
private:
	int Images[19];
	DWORD ImageTime;
	int Image;
};