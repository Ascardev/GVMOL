




#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#define CLASSNAME "Voice Client"
#define WINDOWNAME "게임 시뮬레이션"





#define WM_CALLVCMSG		WM_USER+2   
#define WM_CALLMEMMAP		WM_USER+3   

typedef struct __tagCallData
{
	DWORD  dwIndex;
	char   szCallData[256];
}CALLDATA,*LPCALLDATA;

class CMainWindow
{
public:
	CMainWindow();
	~CMainWindow();
public:
	VOID		Init();
	VOID		Clear();
	BOOL		InitClass(HINSTANCE hInst);
	BOOL		InitWindow(HINSTANCE hInst);
	BOOL		Create(HINSTANCE hInst);
	int			Run();
	int         Process();
	VOID        Draw_Text(HDC hdc,char *msg);
	LRESULT		MainWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	inline      VOID Invalid(){InvalidateRect(m_hMainWnd,NULL,1);}
private:
	HWND		m_hMainWnd;
	BOOL		m_bActive; 
	int			g_Process;
	HDC         m_hDC;
	
};
#endif

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

#ifdef MAINWINDOW_CPP
class CMainWindow g_MainWindow;
#else
extern class CMainWindow g_MainWindow;
#endif


#define SERVER_OUT   0
