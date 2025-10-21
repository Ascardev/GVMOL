class AntiCheat
{
public:
	static AntiCheat* GetInstance() { static AntiCheat instance; return &instance; };
	void Init();
	void Main();
	HANDLE hThread;
	DWORD ThreadId;
};
