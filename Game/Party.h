class Party
{
public:

	static Party* GetInstance() { static Party instance; return &instance; };

	int                         StopCharacter();
	bool                        MouseAction(int x, int y, int w, int h);
	void						Init();
	void                        Main();
	void						Draw();
	void                        Button();
private:
	int                        Images[14];
	int                        CImages[11];
	int                        CHImages[11];
	int                        BallImages[6];
	int                        IsLeader;
	int                        IsYour;
	int                        MoveX, MoveX2;
	int                        Opacity, Opacity2;
	int                        Show, Show2;
};
