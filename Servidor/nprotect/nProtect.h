class nP
{
public:

	nP();
	~nP();

	int rn;			
	int temp;
	int result;		
	char nperrcode[10];		
	HINSTANCE m_hInstDll;	

	char test[6][20];

	bool (*pFunc_npchk)(char*);
	int (*pFunc_npkill)(char*);
	
	typedef BOOL(MYCHECKCRC)(char *);
	MYCHECKCRC *pCheckCRC;

public:

	int NProtectCheck(void);
	int NProtectRun(void);
	int NProtectFree(void);
	int findNPMON();
	BOOL CheckCRC(char * FilePath);
	void Init();


	bool m_bStart;
	bool IsNT;
	
	HINSTANCE hInstanceNPFSICE; 
	HINSTANCE hInstanceNPFGM; 

	BOOL NPGetWindowsVersion();
	BOOL NPMyLoadLibraryNPFGM();
	BOOL NPEnterProtect();
	BOOL NPReleaseProtect();
	BOOL NPFindSICEProtect();
	void NPFreeLib();
};

extern class nP nPro;
