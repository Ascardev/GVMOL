extern DWORD	dwExeCheckSum;
extern char		szProcessPath[256];

char* FindCracker();

char* FindCracker(TRANS_FIND_CRACKER* lpTransFindCrack);

char* FindCrackCont();

HWND WinFocusCrack();

int CheckCrackProcess(int Flag = 0);

DWORD	GetModuleCheckSum(char* szModule);

int	CheckDLL_Module();
