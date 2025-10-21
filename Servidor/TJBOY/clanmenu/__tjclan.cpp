




#define TJCLAN_CPP
#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		

#include "..\\..\\sinbaram\\SinLinkHeader.h"
#include "..\\..\\HoBaram\\HoLinkHeader.h"

#include "..\\..\\language.h"
#include "..\\..\\HoBaram\\HoTextFile.h"
#include "tjclan.h"
#include "tjscroll.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_Cjoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"




extern HWND hTextWnd;
extern HWND hFocusWnd;

extern char UserAccount[256];		
extern char	szConnServerName[16];	




#define MOUSE0() TJmb[0]


#else						

#include <windows.h>
#include <stdio.h>
#include "tjclan.h"
#include "tjscroll.h"

#include "clan_Enti.h"
#include "cE_Cmake.h"
#include "cE_chip.h"
#include "cE_user.h"
#include "cE_isclanmember.h"
#include "cE_report.h"
#include "cE_chatlist.h"
#include "cE_deletecha.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"
#include "cE_Updatecldata.h"

#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"





#define MAX_PARTY_MEMBER	6

#define PARTY_NONE		500
#define PARTY_START		1000
#define PARTY_PROCESS	2000
#define PARTY_END		3000

char UserAccount[256];		
extern char UserAccount[256];		
char szConnServerName[16];	
extern char szConnServerName[16];	

extern int MouseButton[3] ;	
extern int MouseDblClick ;		


extern HWND    g_hwnd;
extern POINT	pCursorPos;
extern HINSTANCE g_hInst;


#define MOUSE0() MouseButton[0]


#endif


int ClanCharMove=0;	
int ClanCLCharMove=0;


int  banisF[100];


void fd2( char *fmt, ...);









void clan_Mouse(int msg)
{
	switch(msg){
	case WM_LBUTTONDOWN:
		TJmb2[0] = TJmb[0] = TRUE;
		break;

	case WM_LBUTTONUP:
		TJmb2[0] = TJmb[0] = FALSE;
		break;

	case WM_RBUTTONDOWN:
		TJmb2[1] = TJmb[1] = TRUE; 
		break;

	case WM_RBUTTONUP:
		TJmb2[1] = TJmb[1] = FALSE; 
		break;

	case WM_MBUTTONDOWN:
		TJmb2[2] = TJmb[2] = TRUE; 
		break;

	case WM_MBUTTONUP:
		TJmb2[2] = TJmb[2] = FALSE; 
		break;
	}
}









void ktj_imsi_clanMENU_Main()
{
	static cnt=0;
	cnt++;
	

	int mainchk;
	
	if(cnt<10) {
		mainchk = PARTY_START;
		
	}
	else {
		mainchk = PARTY_PROCESS;
	}

	

	Interface_clanmenu.Main(mainchk );
}

void ktj_imsi_clanMENU_Draw()
{
	Interface_clanmenu.Draw();
}
		

void clanMENUinit()
{
	
	Interface_clanmenu.CLANmenu_INIT();
	
	Interface_clanmenu.CLANmenu_clanPOSITION();
}



















void clanMENU_INIT(int setN)
{	
	if(!bCheckHostNameandPort) return;



	switch(setN) {
	case -1:				
		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));

		Interface_clanmenu.CLANmenu_INIT();
		
		Interface_clanmenu.CLANmenu_clanPOSITION();
		break;


	case 0:				

		void CreateSaveData_dir();
		CreateSaveData_dir();			


		ZeroMemory(&ClanWonList,  sizeof(CLANWONLIST ));
		Interface_clanmenu.CLANmenu_INIT();

		break;

	case 1:				
	#ifdef USE_PROSTONTALE		

		cBaseMenu.Load2();
		cClanChatting.Load2();
		Interface_clanmenu.Init2();	
	

		
		Interface_clanmenu.SetUserData(UserAccount, sinChar->szName, "¾ÆÀ£", 
			sinChar->Money,500000); 

		
		
		Interface_clanmenu.CLANmenu_clanPOSITION();
		
	
	#endif
		break;
	}
}



int isDELETE_character(char *charName) 
{
	if(!bCheckHostNameandPort) return 1;		


	int web_DB_state_FLAG_WAIT();
	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	Interface_clanmenu.SetUserData(UserAccount, charName, "¾ÆÀ£", 500000   ,500000); 

	
	Interface_clanmenu.CLANmenu_clanPOSITION();
	cldata.myPosition = 0;
	while(1) {
		web_DB_main();					
		cIsClanMember.Main();			

		if(cldata.myPosition != 0) 
			break;
	}

	while(1) {
		if(web_DB_state_FLAG_WAIT() == 1) 
			break;
	}

	





	return cldata.myPosition;
}



void CLAN_MENU::Init2()
{
	#ifdef USE_PROSTONTALE		

	MatPartyBackGround =
		CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );

	

	hBox1 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox2 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox3 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox4 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hBox5 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox6 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox7 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox8 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox9 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	
	hScl_icon_tj = CreateTextureMaterial( "image\\Sinimage\\Help\\scl_icon.tga", 0, 0, 0,0, SMMAT_BLEND_ALPHA );


	cBaseMenu.copy_LoadResource2(&cIsClanMember);		
	cBaseMenu.copy_LoadResource2(&cClanChip);		
	cBaseMenu.copy_LoadResource2(&cClanUser);		
	cBaseMenu.copy_LoadResource2(&cClanMake);		
	cBaseMenu.copy_LoadResource2(&cClanReport);		
	cBaseMenu.copy_LoadResource2(&cClanChatting);		
	cBaseMenu.copy_LoadResource2(&cClanDeleteCha);		
	cBaseMenu.copy_LoadResource2(&cClanJoin);		
#endif
}

void CLAN_MENU::CLANmenu_INIT()
{
	if(!bCheckHostNameandPort) return;
	

	Init();


#ifdef  USE_PROSTONTALE

	
	
	

	
	SetUserData(UserAccount, sinChar->szName, "¾ÆÀ£", sinChar->Money,500000); 
	

	

#else
	
	strcpy(szConnServerName,"ÇÏ³ª");		
	SetUserData("yung6","À¶6","¾ÆÀ£",500000,100000);
	SetUserData("ddd","µðµðµð","¾ÆÀ£",500000,100000);
	
	
	

#endif
}








int CLAN_MENU::CLANmenu_clanPOSITION()
{
	if(!bCheckHostNameandPort) {
		cldata.myPosition = CLAN_NOCONNECT;
		return 0;
	}


	if(OpenFlag==1) return 0;		
	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;
	C_menuN = CLAN_isClanWon;
	

	menuInit(C_menuN );

	ClanCharMove = 1;			
	return 1;
}






void CLANmenu_meetNPC()	
{
	Interface_clanmenu.CLANmenu_meetNPC();	
}
int CLAN_MENU::CLANmenu_meetNPC()
{	
	if(OpenFlag==1) {
		if(C_menuN == CLAN_DISPLAY_INFO)
		{
			C_menuN = CLAN_CLOSE_END_BEFORE;									
			
		}
		return 0;		
	}

	
	C_menuN2= 0;
	OpenFlag = 1;
	joinAnswer = 0;	
	if(!bCheckHostNameandPort)
	{
		C_menuN = CLANSERVER_INSPECT_BEFORE;
		
	}
	else
	{
		C_menuN = CLAN_GO_NPCSTART;
	}
	

	

	ClanCharMove = 1;			
	return 1;
}










void CLANmenu_ChatList(int sw)	
{
	Interface_clanmenu.CLANmenu_ChatList(sw);	
}
void CLAN_MENU::CLANmenu_ChatList(int sw)
{

	if(!bCheckHostNameandPort) return;
	if(OpenFlag==1) return;
	if(bOpenChatList) return;

	ChatList_CmenuN2 = 0;

	switch(sw)
	{
	case 0: 
		
		cClanChatting.InitClanChatList();
		if(bIsReadData) ChatList_CmenuN = CLAN_DISPLAY_OPEN;
		else	ChatList_CmenuN = CHATLIST_READDATA;
		break;
	case 1: 
		cClanChatting.NoScroll();
		
		

		ChatList_CmenuN = CLAN_DISPLAY_INFO;				
		cClanChatting.menuInit(ChatList_CmenuN);

#ifdef USE_PROSTONTALE		
		
#else
	OpenFlag = 1;
	C_menuN = ChatList_CmenuN;
	
#endif


		break;
	}
}




void CLANmenu_ChatList_Main()	
{
	cClanChatting.Main();			
}
void CLANmenu_ChatList_Draw()	
{
	cClanChatting.Draw();			
}






void Updatecldata()
{
	
	g_UpdateCldata.Updatecldata();
}








void ClanJoin(char *oneClanName, char *oneChipCharid)
{
	
	Interface_clanmenu.SetJoinData(oneClanName,oneChipCharid);
	Interface_clanmenu.ClanJoin();
}



int JoinAnswer()
{
	return cClanJoin.nJoinAnswer;
}

void CLAN_MENU::ClanJoin()
{
	if(OpenFlag==1) return;
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			
	C_menuN = CLAN_JOIN_before;
	
}





void joinClanMember()
{
	Interface_clanmenu.joinClanMember();
}

void CLAN_MENU::joinClanMember()
{
	if(OpenFlag==1) return;
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			
	C_menuN = CLAN_JOIN_chip;
}







void ktj_IMSI_DELETE()
{
	
	
	CLANmenu_DeleteCha_SetCharacter(UserAccount, szConnServerName, "Çã°Æ´ö");
}




void CLANmenu_DeleteCha_SetCharacter(char *id, char *gserver, char *chaname)
{
	cClanDeleteCha.SetDeleteChaInfo(id, gserver, chaname);

	
	Interface_clanmenu.CLANmenu_DeleteCha();
}


void CLAN_MENU::CLANmenu_DeleteCha()
{
	C_menuN2 = 0;
	OpenFlag = 1;
	ClanCLCharMove = 1;			
	C_menuN = CLAN_DELETECHA_START;

	cClanDeleteCha.SetHowDeleteChaFlag();
}


int CLANmenu_DeleteCha_flag()
{
	
	
	
	
	return cClanDeleteCha.GetHowDeleteChaFlag();
}







int ReadClanInfo(DWORD dwClanNum)
{
	if(OpenFlag==1) return -1;		

	g_ViewClanInfo.SearchClan(dwClanNum);
	BOOL bFlag;
	bFlag = g_ViewClanInfo.GetFlag();  
	
	if(!bFlag)
	{
		
		g_ViewClanInfo.DownLoadClanInfo(dwClanNum);
	}
	return ClanInfo_nNum;		
}






















CLAN_MENU::CLAN_MENU()
{
	nClanWon_Num = 0;
	nScl_Bar = 0;           
	g_nClanIconNum;			
	g_HelpIconNumber = 0;    
	g_HelpDisPlay = 0;

}

CLAN_MENU::~CLAN_MENU()
{
}



POINT clanBoxPos;
POINT clanCLBoxPos;
void CLAN_MENU::Init()
{
	OpenFlag = 0;

	C_menuN = 0;
	C_menuN2 =0;

	
	
	
	
	

	BackStartPos.x = 101;
	BackStartPos.y = 114;


	
	clanBoxPos.x = BackStartPos.x;
	clanBoxPos.y = BackStartPos.y;

	
	clanCLBoxPos.x = 540+60;		
	clanCLBoxPos.y = CHATLIST_BOX_Y;


	

	ZeroMemory(szRemoveClanWon,sizeof(char)*500);	
	ZeroMemory(ClanHelpIcon,sizeof(CLANHELPICON)*CLANHELPICON_NUM);		
	ZeroMemory(cldata.szJoinClanName,sizeof(char)*64);   
	ZeroMemory(cldata.ChaName,sizeof(char)*64);  
	ZeroMemory(cldata.szJoinClanChipName,sizeof(char)*64);   
	ZeroMemory(szReconfReleaseMsg,sizeof(char)*2048);

	
	nClanWon_Num = 0;			
	nReleaseClanWon = 0;		
	membmp = new MENUBMP;
	
	

	Load();	
	cClanChatting.Load();

	
	
	cBaseMenu.Load();

	
	cIsClanMember.Init(1);
	cIsClanMember.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cIsClanMember);		

	cClanChip.Init(1);
	cClanChip.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChip);		
	cBaseMenu.SetBase(&cClanChip);

	cClanUser.Init(1);
	cClanUser.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanUser);		
	cBaseMenu.SetBase(&cClanUser);

	cClanMake.Init(1);
	cClanMake.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanMake);		

	cClanReport.Init(1);
	cClanReport.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanReport);		


	cClanChatting.Init(1);
	cClanChatting.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanChatting);		
	cBaseMenu.SetBase(&cClanChatting);


	cClanDeleteCha.Init(1);
	cClanDeleteCha.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanDeleteCha);		

	cClanJoin.Init(1);
	cClanJoin.setParent(&cBaseMenu);
	cBaseMenu.copy_LoadResource(&cClanJoin);		
	

}








void CLAN_MENU::menuInit(int num)
{
	
	cIsClanMember.menuInit(num);		
	cClanMake.menuInit(num);		
	cClanChip.menuInit(num);		
	cClanUser.menuInit(num);		
	cClanChatting.menuInit(num);
	cClanDeleteCha.menuInit(num);
	cClanJoin.menuInit(num);
}













int CLAN_MENU::chkMenu(int x, int y, RECT *r) 
{
	if(r->left <= x   &&   x<= r->right ) 
		if(r->top <= y   &&   y<= r->bottom ) 
			return 1;
	return 0;			
}
int CLAN_MENU::chkeckMenuN()
{
	int i;
	
	for(i=0; i<menuSu; i++) {
		if(  chkMenu(pCursorPos.x, pCursorPos.y, &menuPos[i])  ) {
			return i;
		}
	}
	return -1;
}






void menu_joinOpen(char *chipCharID)
{
	
}



int CLAN_MENU::menu_joinOpen(char *chipCharID)		
{
	














	return 1;
	
}


void menu_joinOpen_Chip(int isOK, char *clanWonID, char *clanWonCharID)
{
	Interface_clanmenu.menu_joinOpen_Chip(isOK, clanWonID, clanWonCharID);		
}




int CLAN_MENU::menu_joinOpen_Chip(int joinOK, char *clanWonID, char *clanWonCharID)		
{
	if(OpenFlag==1) return 0;		

	if(cldata.myPosition != 101) return 0;	

	






		C_menuN = CLAN_JOIN_chip		;	
		strcpy(cldata.clanJoinID, clanWonID);
		strcpy(cldata.clanJoinCharID, clanWonCharID);

		C_menuN2= 0;
	
	OpenFlag = 1;
	joinAnswer = 0;

	
	ClanCharMove = 1;


	return 1;
}











extern BOOL bip_port_error;
int CLAN_MENU::Main(int sw)
{
	if(bip_port_error) return 0;
	web_DB_main();					

	
	if(OpenFlag==0) return 0;		


	switch(sw) {
	case PARTY_START:				
		return 1;
	case PARTY_END:					
		return 1;
	}

	
									
	cBaseMenu.Main();				
	cIsClanMember.Main();			
	cClanReport.Main();				
	cClanMake.Main();				
	cClanChip.Main();				
	cClanUser.Main();				
	cClanJoin.Main();
#ifdef USE_PROSTONTALE		

	
#else
	cClanChatting.Main();			
#endif

	cClanDeleteCha.Main();            
	return TRUE;
}




char loadis[256] = {0,};
char loadis2[256] = {0,};
char updateis[256] = {0,};


int CLAN_MENU::Draw()
{	
	if(bip_port_error) return 0;
	
	











	








	
	
	


	

	
	if(OpenFlag==0) return 0;	


#ifndef USE_PROSTONTALE		

	window_renderINIT();			
	HDC hdc = GetDC(g_hwnd);	
	HDC sorDC;
	sorDC  = CreateCompatibleDC(hdc);
	HDC destdc=CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );
	PatBlt(destdc,0,0,800,600,PATCOPY);
	char szBuf[256];
	extern POINT	pCursorPos;
	
	
	wsprintf(szBuf,"C_menuN : %d  ,x = %d, y = %d , ÁøÇà °úÁ¤ : %d Å¬·£ ÀÌ¸§ : %s",
		C_menuN,pCursorPos.x,pCursorPos.y,nCheckDownLoad,cldata.name);
	TextOut(destdc,100,0,szBuf,lstrlen(szBuf));

	SelectObject(hdc,ClanInfo[ClanInfo_nNum].hClanMark );
	BitBlt(destdc,0,0,32,32,sorDC,0,0,SRCCOPY);
	TextOut(destdc,0,50,ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport,lstrlen(ClanInfo[ClanInfo_nNum].ClanInfoHeader.ClanReport));
	DeleteDC(destdc);
	DeleteDC(sorDC);
	ReleaseDC(g_hwnd,hdc);

#endif
	
	








	switch(C_menuN) {
	case CLANSERVER_INSPECT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();						
		break;
	case CLAN_READ_CLANMARK:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;	
	case CLAN_isCheckClanJang_Result:
	case CLAN_isCheckClanJang:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;	
	case CLAN_MAKE_is:		

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();				
		break;
	case CLANMAKE_NOMONEY:
	case CLAN_MONEY_is:		

		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();

		break;
	case CLAN_NAME_is:		
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_NONAME:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_NAME_BEING:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK_expl:		
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;
	case CLAN_INSPECTION_expl:		
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		
		break;
	case CLAN_NotMake:	
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANMAKE_DOWN_INFO:
	case CLANMAKE_READ_CLANMARK:
	case CLAN_MAKE_FINISH:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_AllEnd:	
		break;


	case CLAN_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;


	
	
	
	
	case CLAN_CHIP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
		
		
	case CLAN_REMOVE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_REMOVE_SHORTCLANWON_RESULT:		
	case CLAN_REMOVE_RESULT:
	DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_REMOVE_SHORTCLANWON:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RECONF_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_FINISH_RELEASE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANCHIP_RELEASEMESSAGE:
	case CLAN_WAREHOUSE_RIGHT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK1:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK2:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_MARK3:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_HELP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_HELP_CONTENT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	

	case ISPFLAG_CHIP:
	case CLANCHIP_MAKE_FIRSTMESSAGE: 
	case CLANCHIP_DOWN6_CLANWON:    
	case CLANCHIP_DOWN6_CLANWON_MESSAGE:
	case CLAN_NOMAKE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	
	case CLANUSER_REMOVE :
	case	CLANUSER_AUTORELEASE:
	case CLAN_USER:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	
	case CLAN_USER_NOMAKE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RECONF_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_FINISH_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLANUSER_MAKE_FIRSTMESSAGE:			
	case CLANUSER_DOWN6_CLANWON_MESSAGE:
	case CLANUSER_DOWN6_CLANWON:			
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

	
	case CLANUSER_JOIN:
	case CLAN_JOIN:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;

	case CLAN_USER_WAREHOUSE:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_USER_HELP:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_USER_HELP_CONTENT:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	

	case CLAN_DISPLAY_END:
	case CLAN_DISPLAY_OPEN:		
	case CLAN_DISPLAY_CLOSE:
	case CLAN_CLOSE_ENDING:
	case CLAN_DISPLAY_INFO:
	case CHATLIST_READDATA:	
#ifdef USE_PROSTONTALE		
		
#else
		cClanChatting.Draw();
#endif
		break;	


	case CLAN_DELETECHA_RELEASECLAN_BEFORE: 
	case CLAN_DELETECHA_RELEASECLAN:      
	case	CLAN_DELETECHA_SECESSION_BEFORE:	
	case	CLAN_DELETECHA_SECESSION:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		cClanDeleteCha.Draw();
		break;
	case CLAN_REAMMAKR_ERROR:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;
	case CLAN_RELEASE_LOADING:
	case CLAN_REMOVE_SHORTCLANWON_LOADING:
	case CLAN_REMOVE_LOADING:
	case CLAN_CHIP_ReadDATA:
	case CLAN_NPC_START:
	case CLAN_USER_ReadDATA:
	case ISPFLAG_USER:
	case CLANUSER_RELEASEMESSAGE:
	case CLANUSER_RELEASE_FLAG:
	case CLAN_RECONF_SECESSION_LOADING:
		DrawBox(BackStartPos.x,BackStartPos.y,4,5);		
		Draw_C_menuN();
		break;	
	
	}	

#ifndef USE_PROSTONTALE		
	window_renderFLIP();
#endif

	return TRUE;
}



void CLAN_MENU::Draw_C_Text(char *str, int x, int y, int sw=0)
{
#ifdef USE_PROSTONTALE		
	char strbuf[1024];

	HDC hdc;
	HFONT oldFont;
	
	

	if(hFont != NULL)
		oldFont = (HFONT)SelectObject( hdc , hFont );


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;

	while(1) {
		

		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:


			
			if(sw==2){
				SetFontTextColor( hdc, RGB(100, 100, 100));	
				
				TextOut(hdc, x+1, y+1, strbuf, lstrlen(strbuf));

				SetFontTextColor( hdc, RGB(230, 255, 240));	
				TextOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			else     {
				SetFontTextColor( hdc, RGB(230, 255, 240));	
				TextOut(hdc, x, y, strbuf, lstrlen(strbuf));
			}
			
			








			

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	

	if(sw==1) 
	{
		static cnt=0;
		cnt++;
		if(cnt<20) {
			SetFontTextColor( hdc, RGB(255, 255, 255));
			TextOut(hdc, x + (lstrlen(str)*6) , y-16, "|", 1);
		}
		if(cnt>=40) cnt=0;
	}

	if(oldFont)
		SelectObject( hdc, oldFont);
	
#else

#endif
}







int CLAN_MENU::DrawBox(int x,int y,int x_width,int y_height)
{

	isDrawClanMenu = 1;


#ifdef USE_PROSTONTALE		

	#define BOXFONTSIZE 64

	if(d3ddev == NULL)
		return FALSE;

	


	
	
	
	
	sinDrawTexImage( hBox5, (float)x+64, (float)y+32, (float)( 64+(  ( x_width-2) *32) ), (float)(   32+(  (y_height-1) *32) ),
				0,0,
				0, 0, 32, 32, 
				255);
	
	
	
	
	
	
	sinDrawTexImage( hBox1,(float) x,(float) y, (float)64, (float)32,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
	
	sinDrawTexImage( hBox3,(float)(   x+(32*x_width) +64 ), (float)y, 64, 32,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);	
	
	sinDrawTexImage( hBox7, (float)x, (float)(  y+(32*y_height) + 32 ), 64, 64 ,
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
	
	sinDrawTexImage( hBox9,(float)(   x+(32*x_width) +64 ), (float)(  y+(32*y_height) + 32  ), 64, 64,    
				(float)0,(float)0,  
				(float)0, (float)0, (float)64, (float)32,
				255);
				
	int line;
	int sx = x+64;
	int ey=  y+(32*y_height) + 32 ;
	for(line=0; line<x_width; line++) {
		
		sinDrawTexImage( hBox2, (float) sx, (float)y, 32, 32,
				(float)0,(float)0,  
				(float)0, (float)0, (float)32, (float)32,
				255);
		
		
		sinDrawTexImage( hBox8, (float)sx, (float)( ey ), 32, 64,
				0,0,
				0, 0, 32, 64,
				255);
				
		sx+=32;
	}

	int sy = y+32;
	int ex = x+(32*x_width) + 64 ;
	for(line=0; line<y_height; line++) {
		
		sinDrawTexImage( hBox4, (float)x, (float)sy, 64, 32,
				0,0,
				0, 0, 64, 32,
				255);
		
		sinDrawTexImage( hBox6,(float)ex, (float)sy, 64, 32,
				0,0,
				0, 0, 64, 32,
				255);
		sy+=32;
	}
	
	





	

	
	
	


#else



	
	



	
	BITMAP bit;
	int bx,by;
	int i;
	int nTotal_Width = 0;
	int nTotal_Height = 0;
	
	





	HDC hdc=GetDC(g_hwnd);

	HDC sorDC =CreateCompatibleDC(hdc);
	HDC destdc=CreateCompatibleDC(hdc);

	SelectObject(destdc, Dback.hb );		
	

	

















	
	SelectObject(sorDC, hBox1);
	GetObject(hBox1,sizeof(BITMAP),&bit);
	bx = bit.bmWidth;
	nTotal_Width+=bx;
	by = bit.bmHeight;	
	BitBlt(destdc,x,y,bx,by,sorDC,0,0,SRCCOPY);

	for(i=0; i< x_width; i++)
	{
		SelectObject(sorDC,hBox2);
		GetObject(hBox2,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		nTotal_Width +=bx;
		by = bit.bmHeight;
		StretchBlt(destdc,x+BOXCORNER_WIDTH+(bx*i),y,bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}

	

	SelectObject(sorDC, hBox3 );
	GetObject(hBox3,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y,bx,by,sorDC,0,0,bx,by,SRCCOPY);


    

	for(i=0; i< y_height; i++)
	{
		SelectObject(sorDC, hBox4 );
		GetObject(hBox4,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		by = bit.bmHeight;
		nTotal_Height +=by ;
		StretchBlt(destdc,x,y+BOXCORNER_HEIGHT+(by*i),bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}



	
	
	
	SelectObject(sorDC,hBox7);
	GetObject(hBox7,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;
		
	StretchBlt(destdc,x,y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);

	for(i=0; i< x_width; i++)
	{
		SelectObject(sorDC,hBox8);
		GetObject(hBox8,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;		
		by = bit.bmHeight;
		StretchBlt(destdc,x+BOXCORNER_WIDTH+(bx*i),y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}	

	
	SelectObject(sorDC,hBox9);
	GetObject(hBox9,sizeof(BITMAP),&bit);	
	bx = bit.bmWidth;
	by = bit.bmHeight;	
	StretchBlt(destdc,x+nTotal_Width,y +BOXCORNER_HEIGHT+nTotal_Height,bx,by,sorDC,0,0,bx,by,SRCCOPY);	

 
	
	for(i=0; i< y_height; i++)
	{
		SelectObject(sorDC, hBox6 );
		GetObject(hBox6,sizeof(BITMAP),&bit);	
		bx = bit.bmWidth;
		by = bit.bmHeight;		
		StretchBlt(destdc,x+nTotal_Width,y+BOXCORNER_HEIGHT+(by*i),bx,by,sorDC,0,0,bx,by,SRCCOPY);
	}


	DeleteDC(sorDC);
	DeleteDC(destdc);

	ReleaseDC(g_hwnd, hdc);


#endif

	return TRUE;
}

void CLAN_MENU::RenderMenu()
{
	











}










void CLAN_MENU::Draw_C_menuN()
{		
	cBaseMenu.Draw();
	cClanChip.Draw();	
	cClanUser.Draw();	
	cClanMake.Draw();	
	cClanReport.Draw();
#ifdef USE_PROSTONTALE		
#else
	cClanChatting.Draw();
#endif
	cClanJoin.Draw();
}


















void CLAN_MENU::SetUserData(char* id, char* chaname, char* gserver,int money, int ability)
{
	strcpy(cldata.szID,  id);
	strcpy(cldata.ChaName, chaname);
	strcpy(cldata.gserver, gserver);

	cldata.money = money;
	
	
	cldata.ability = ability;
}




void CLAN_MENU::SetJoinData(char *joinclanname, char *joinclanchip)
{
	strcpy(cldata.szJoinClanName,    joinclanname);			
	strcpy(cldata.szJoinClanChipName,joinclanchip);		
}











#ifdef USE_PROSTONTALE		

void DrawSprite_TJB(int winX ,int winY, int winxlen, int winylen, LPDIRECT3DTEXTURE9 pdds,int x, int y, int width, int height,int Bltflag)
{
	if(!pdds) return;

	
    RECT rcRect;
	RECT dRect;

	dRect.left = winX;
	dRect.right = winX+winxlen;
	dRect.top = winY;
	dRect.bottom = winY+winylen;

	rcRect.top		= 0;
	rcRect.left		= 0;
	rcRect.bottom   = 32;
	rcRect.right    = 32;


	
		

		

		
					pdds,
					&rcRect,
					DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY,
					NULL);







}
#endif




#ifdef USE_PROSTONTALE		
#else

void Draw_Text(int x, int y,char *str)
{
	HANDLE hFont,hOldFont;
	HDC hdc;	
	hdc = GetDC(g_hwnd);
    	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        HANGEUL_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "±¼¸²Ã¼" );

	hOldFont = SelectObject(hdc,hFont);
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;
	
	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:		
			
			TextOut(hdc, x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	
	

	SelectObject(hdc,hOldFont);
	DeleteObject(hFont);

	ReleaseDC(g_hwnd,hdc);
	
}
#endif



void Text_Out1(HDC hdc,int x, int y,char *str)
{
}

void Text_Out2(HDC hdc,int x, int y,char *str)
{
}

void Text_Out3(HDC hdc,int x, int y,char *str)
{
}
void Text_Out(HDC hdc,int x, int y,char *str)
{
	HANDLE hFont,hOldFont;

	
    	hFont = CreateFont( 12,
                        0,
                        0,
                        0,
						FW_NORMAL,
                        FALSE,
                        FALSE,
                        FALSE,
                        HANGEUL_CHARSET,
                        OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        DEFAULT_QUALITY,
                        VARIABLE_PITCH,
                        "±¼¸²Ã¼" );

	hOldFont = SelectObject(hdc,hFont);
	char strbuf[1024];


	ZeroMemory(strbuf, sizeof(strbuf));

	int strL = strlen(str);
	int cnt=0;
	int i=0;
	
	while(1)
	{
		strbuf[i] = str[cnt];
		cnt++;
		if(strbuf[i] == '\n')  {
			strbuf[i] =0;
			i=0;
jmp1:		
			
			TextOut(hdc, x, y, strbuf, lstrlen(strbuf));

			ZeroMemory(strbuf, sizeof(strbuf));
			y+=16;

			if(cnt>=strL) break;
		}
		else if(cnt>=strL)
		{
			goto jmp1;
		}
		else {
			i++;
		}
	}
	
	

	SelectObject(hdc,hOldFont);
	DeleteObject(hFont);
	
	
}



void CLAN_MENU::Load()
{
#ifdef USE_PROSTONTALE		

	MatPartyBackGround =
		CreateTextureMaterial( "image\\Sinimage\\Help\\party_win.tga" , 0, 0, 0,0, SMMAT_BLEND_ALPHA );
	

	

	hBox1 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxCorner.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox2 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\HelpBoxLine.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox3 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box3.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox4 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box4.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );
	hBox5 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box5.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox6 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box6.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox7 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box7.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox8 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box8.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	hBox9 = 
		CreateTextureMaterial( "image\\Sinimage\\Help\\box9.tga",  0, 0, 0,0, SMMAT_BLEND_ALPHA );

	


	


















































































#else
	

	MatPartyBackGround = (HBITMAP)LoadImage(
					NULL, 
					"image\\Sinimage\\Help\\box-test-title2.bmp",
					IMAGE_BITMAP,
					0,0,
					LR_LOADFROMFILE);



	hBox1= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox2= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box2.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox3= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box3.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox4= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box4.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox6= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box6.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox7= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box7.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hBox8= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box8.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hBox9= (HBITMAP)LoadImage(NULL,"image\\clanimage\\MessageBox\\box9.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	
	
	



	hOk_Gray= (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Ok_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);	

	hOk_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Ok_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);


	if(hOk_Yellow == NULL)
	{
		char temp[50];
		wsprintf(temp,"Num : %d",GetLastError());
	}

	hCancel_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Cancel_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hCancel_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Cancel_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hYes_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Yes_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hYes_Yellow = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_Yes_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hNo_Gray = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_No_Glay.bmp",
						IMAGE_BITMAP,	
						0,0,
						LR_LOADFROMFILE);

	hNo_Yellow =  (HBITMAP)LoadImage(NULL,"image\\Sinimage\\MessageBox\\Button_No_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);




	
	
	
	
	
	hClanName = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\Help\\box-test-title.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWareHouse[0]= (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whc.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWareHouse[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whc1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWHRight[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hWHRight[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\whr1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanMark[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\m.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanMark[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\m1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hRemove[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\r.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hRemove[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\r1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanRelease[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\cr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanRelease[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\cr1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hHelp[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\h.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hHelp[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\h1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hOut[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\o.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hOut[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\o1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	
	hSecession[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hSecession[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\s1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hIcon = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_0.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hIcon_Click = (HBITMAP)LoadImage(NULL,"image\\party\\party_man_1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hRemoveToMenu[0]= (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\Button_deport_Glay.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hRemoveToMenu[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\Button_deport_Yellow.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hClose[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\c.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hClose[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\MessageBox\\c1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	
	hHelp1 = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\chipbutton\\help1.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hButton_Box = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\msBox.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hClanTitle = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\title.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hScl_Bar = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\scl_bar.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	hScl_icon = (HBITMAP)LoadImage(NULL,"image\\Sinimage\\help\\scl_icon.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);
	
	hTxt_Remove[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_r_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Remove[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_r.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Release[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_cr_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Release[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_cr.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Mark[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_m_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Mark[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_m.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Help[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_h_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Help[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_h.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Secession[0] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_out_.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	hTxt_Secession[1] = (HBITMAP)LoadImage(NULL,"image\\clanImage\\chipbutton\\txt_out.bmp",
						IMAGE_BITMAP,
						0,0,
						LR_LOADFROMFILE);

	


	
	

#endif
}




void clanMENU_close()
{
	Interface_clanmenu.Close();
}

void CLAN_MENU::Close()
{
	#ifdef USE_PROSTONTALE		

	

















































	


	if(cldata.hClanMark) { cldata.hClanMark->Release(); cldata.hClanMark = NULL;}
	if(cldata.hClanMark16) {cldata.hClanMark16->Release(); cldata.hClanMark16 = NULL;}

	cClanChatting.Close();
	cBaseMenu.Close();


	#else

	
	DeleteObject( MatPartyBackGround );


	
	DeleteObject(hOk_Gray);
	DeleteObject(hOk_Yellow);
	DeleteObject(hCancel_Gray);
	DeleteObject(hCancel_Yellow);
	DeleteObject(hYes_Yellow);
	DeleteObject(hYes_Gray);
	DeleteObject(hNo_Gray);
	DeleteObject(hNo_Yellow);
	DeleteObject(hMark);
	DeleteObject(hClanName);
	DeleteObject(hScl_Bar);
	DeleteObject(hScl_icon);


	for(int i=0 ; i <2; i++)
	{
		DeleteObject(hWHRight[i]);
		DeleteObject(hWareHouse[i]);
		DeleteObject(hClanMark[i]);
		DeleteObject(hRemove[i]);
		DeleteObject(hClanRelease[i]);
		DeleteObject(hHelp[i]);
		DeleteObject(hOut[i]);
		DeleteObject(hClose[i]);
		DeleteObject(hSecession[i]);
		DeleteObject(hTxt_Remove[i]);
		DeleteObject(hTxt_Release[i]);
		DeleteObject(hTxt_Mark[i]);
		DeleteObject(hTxt_Help[i]);
		DeleteObject(hTxt_Secession[i]);
	}
	


	DeleteObject(hIcon);
	DeleteObject(hHelp1);



	#endif
}

void CLAN_MENU::Loading()
{
#ifdef USE_PROSTONTALE		
	Draw_C_Text(szLoading, BackStartPos.x + 80,BackStartPos.y + 90);
#else

	HDC hdc, sorDC,destdc;

	hdc = GetDC(g_hwnd);
	sorDC  = CreateCompatibleDC(hdc);
	destdc = CreateCompatibleDC(hdc);
	SelectObject(destdc, Dback.hb );		
	Text_Out(destdc,BackStartPos.x + 80,BackStartPos.y + 90 ,szLoading);

	DeleteDC(sorDC);
	DeleteDC(destdc);
	ReleaseDC(g_hwnd, hdc );
#endif

}


#ifdef USE_PROSTONTALE		

int SendClanCommandUser( smWINSOCK *lpsmSock , DWORD	dwCode , int Param1, int Param2 , CLANWONLIST *lpClanUserList , int ClanUserCount );
#endif


void SetClanWon()
{
	if(cldata.nTotalClanWonCount==0) return;

	memcpy(ClanWonList.clanWon,cldata.clanWon,sizeof(cldata.clanWon));

	

#ifdef USE_PROSTONTALE		
	
	SendClanCommandUser( smWsockDataServer , smTRANSCODE_CLAN_UPDATE  , 0,0, &ClanWonList , cldata.nTotalClanWonCount );

	
#endif

}






BOOL SearchDirectory(char *dir)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;	
	char t[50];
	wsprintf(t,"%s\\*.*",dir);
	hFind = FindFirstFile(t,&wfd);
	if(hFind == INVALID_HANDLE_VALUE)
	{		
		return FALSE;
	}	

	return TRUE;	
}

void MakeDirectory(char *dir)
{
	CreateDirectory(dir,NULL);
}


void CreateSaveData_dir()
{	
	char szTemp[100];
	if(!SearchDirectory(SAVEDATA_DIR)) MakeDirectory(SAVEDATA_DIR);
	if(!SearchDirectory(CLANDATA_DIR)) MakeDirectory(CLANDATA_DIR);

	ZeroMemory(szTemp,sizeof(szTemp));
	wsprintf(szTemp,"%s",CLANDATA_DIR);
	wsprintf(szTemp,"%s\\%s",szTemp,szConnServerName);

	if(!SearchDirectory(szTemp)) MakeDirectory(szTemp);

}



void Text_Out1()
{
}
