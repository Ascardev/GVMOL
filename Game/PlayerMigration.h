class PlayerMigration
{
public:
	static PlayerMigration* GetInstance() { static PlayerMigration instance; return &instance; };
	void Init();
	void DrawImage(int Image, int x, int y, int w, int h);
	void Draw();
	void Button();
	bool MouseAction(int x, int y, int w, int h);
	void SendItem(rsPLAYINFO* Player, DWORD Code, int Flag, int TypeMigration);
	void SendRequest();
	void RequestItem(rsPLAYINFO* Player);
	void Recv(smTRANS_COMMAND* ps);
	void Open();
	bool IsOpen() { return fOpen; };
private:
	int Images[5];
	int fOpen;
	int TypeMigration;
};