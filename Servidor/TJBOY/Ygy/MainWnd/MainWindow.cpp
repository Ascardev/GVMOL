#define MAINWINDOW_CPP

#include "../YgyHeader.h"
#include "MainWindow.h"




CMainWindow::CMainWindow()
{
	Init();
	
}

CMainWindow::~CMainWindow()
{
}



VOID CMainWindow::Init()
{
	m_hMainWnd = NULL;
	g_Process = -1;
}

VOID CMainWindow::Clear()
{
	if(m_hMainWnd != NULL)
	{
		m_hMainWnd = NULL;
	}
}

BOOL CMainWindow::InitClass(HINSTANCE hInst)
{
	WNDCLASSEX wc;

	memset(&wc,0,sizeof(WNDCLASSEX));

	wc.cbSize				= sizeof(WNDCLASSEX);
	wc.cbClsExtra			= 0;
	wc.cbWndExtra			= 0;
	wc.hCursor				= LoadCursor(NULL, IDC_ARROW);
	wc.hIcon				= LoadIcon(NULL,IDI_APPLICATION);
	wc.hIconSm				= LoadIcon(NULL,IDI_APPLICATION);
	wc.hInstance			= hInst;
	wc.lpfnWndProc			= WndProc;
	wc.hbrBackground		= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.style				= CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	wc.lpszClassName		= CLASSNAME;
	wc.lpszMenuName			= NULL;

	if(!RegisterClassEx(&wc))
	{
		return FALSE;
	}	

	
	


	return TRUE;
}

BOOL CMainWindow::InitWindow(HINSTANCE hInst)
{
	int nStart_x,nStart_y;
	int nMax_Width,nMax_Height;
	DWORD m_dwWindowStyle;	

	

	

	nMax_Height = 400;
	nMax_Width =   300;

	nStart_x = 0;
	nStart_y = 0;

	m_dwWindowStyle = WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|
                          WS_MINIMIZEBOX|WS_VISIBLE;  

	
    
	g_CtrlProcess.InitRemoteProcess();
	
	m_hMainWnd = CreateWindowEx(0,CLASSNAME,WINDOWNAME,m_dwWindowStyle,
		nStart_x,nStart_y,nMax_Width, nMax_Height,NULL,NULL,hInst,0);

	if(!m_hMainWnd)
	{
		MessageBox(NULL,"It cannot create main-window","Main-Window Error",MB_OK);
		return FALSE;
	}	

	
	
	

	return TRUE;
}

char szTemp[256] = {0,};
LRESULT CMainWindow::MainWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	int i = 0;
	
	int nIndex = 0;
	switch(msg)
	{
	case WM_CREATE:		
		g_CtrlProcess.InitRmoteProcessWnd();
		g_CtrlProcess.Init();
		
		
		
		
		
		
		
		
		
		
		
		break;
	case WM_COMMAND:		
		break;
	case WM_PAINT:
		m_hDC = BeginPaint(hWnd,&ps);
		if(szTemp[0] != 0)
			Draw_Text(m_hDC,szTemp);
		EndPaint(hWnd,&ps);
		break;

	case WM_CALLMEMMAP:    
		nIndex = (int)wParam;
		if(nIndex == 20000)
		{
			g_CtrlProcess.PacketParsing();			
			InvalidateRect(hWnd,NULL,1);
			
		}
		
		break;	
	case WM_KEYDOWN:
		g_CtrlProcess.TestInputData(hWnd,wParam,lParam,szTemp);		

		break;
	case WM_CALLVCMSG:     
		memcpy(szTemp,(char*)lParam,255);
		wsprintf(szTemp,"%s",(char*)lParam);
		InvalidateRect(hWnd,NULL,1);
		
		
		break;

	case WM_SIZE:
		if( SIZE_MAXHIDE==wParam || SIZE_MINIMIZED==wParam )
        {           
            m_bActive = FALSE;
        }
        else
        {
            m_bActive = TRUE;
        }
		break;
	case WM_DESTROY: 
		break;
	case WM_CLOSE: 
		g_CtrlProcess.Clear();
		DestroyWindow(m_hMainWnd);
		PostQuitMessage(0);
		break;
	}
	

	return DefWindowProc( hWnd, msg, wParam, lParam );
	
}

int CMainWindow::Run()
{
	BOOL bGotMsg;
    MSG  msg;	
    msg.message = WM_NULL;
    PeekMessage( &msg, NULL, 0U, 0U, PM_NOREMOVE );
	

    while( WM_QUIT != msg.message  )
    {
        
        
		
        if( m_bActive )
            bGotMsg = PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE );
        else
            bGotMsg = GetMessage( &msg, NULL, 0U, 0U );

        if( bGotMsg )
        {   
            TranslateMessage( &msg );
            DispatchMessage( &msg );
            
        }       
		g_CtrlProcess.Main();
		if(Process() == -1)
			break;
    }

    return (INT)msg.wParam;
}

int  CMainWindow::Process()
{
	switch(g_Process)
	{
	case SERVER_OUT:
		goto out;
		break;
	}
	return 1;
out:
	return -1;
}
BOOL CMainWindow::Create(HINSTANCE hInst)
{
	if(InitClass(hInst) && InitWindow(hInst)) return TRUE;

	return FALSE;
}

VOID CMainWindow::Draw_Text(HDC hdc,char *msg)
{	
	TextOut(hdc,10,100,msg,lstrlen(msg));
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    return g_MainWindow.MainWindowProc( hWnd, uMsg, wParam, lParam );
}
