#include "..\\sinbaram\\SinLinkHeader.h"
#include "..\\HoBaram\\HoLinkHeader.h"
#include "..\\smreg.h"
#include "..\\HoBaram\\HoTextFile.h"
#include "..\\HoBaram\\HoMinMax.h"
#include "..\\HoBaram\\HoNewParticle.h"
#include "..\\HoBaram\\HoNewParticleMgr.h"

#include "..\\language.h"

#include "..\\CAutoCamera.h"
#include "..\\File\File.h"

static CAutoCamera		s_AutoCamera;

#ifdef _LANGUAGE_KOREAN
char* szJoinWebUrl = "http://www.pristontale.co.kr";
#endif

#ifdef _LANGUAGE_CHINESE
char* szJoinWebUrl = "http://www.pristontale.cn";
#endif

#ifdef _LANGUAGE_JAPANESE
char* szJoinWebUrl = "http://www.pristontale.jp";
#endif

#ifdef	_LANGUAGE_TAIWAN
char* szJoinWebUrl = "http://www.pristontale.com.tw";
#endif

#ifdef _LANGUAGE_BRAZIL
char* szJoinWebUrl = "http://www.epicpristontale.com";
#endif

#ifdef _LANGUAGE_ARGENTINA
char* szJoinWebUrl = "http://www.axeso5.com";
#endif

#ifdef	_LANGUAGE_ENGLISH
#ifdef	_LANGUAGE_PHILIPIN
char* szJoinWebUrl = "http://www.netplay.ph";
#else
char* szJoinWebUrl = "http://www.pristontale.com";
#endif
#endif

#ifdef _LANGUAGE_VEITNAM
char* szJoinWebUrl = "http://www.ptv.com.vn";
#endif

#ifdef	_LANGUAGE_THAI
char* szJoinWebUrl = "http://www.pristontale.in.th";
#endif

extern POINT3D WaveCameraPosi;
extern int	   WaveCameraFactor;
extern int	   WaveCameraTimeCount;
extern int	   WaveCameraDelay;
extern BOOL	   WaveCameraFlag;

char	UserAccount[256];
char	UserPassword[256];
HoOpening::HoOpening()
{
	Stage = NULL;
	PatCamera = NULL;

	LogoBlendValue = 0;
	LoginBlendValue = 0;

	Load();
	StartConnectServerFlag = FALSE;
	WorkState = STATE_OPENING;

	MidY = (600 / 2);
	SetWindowText(hTextWnd, NULL);

	memset(UserAccount, 0, sizeof(UserAccount));
	memset(UserPassword, 0, sizeof(UserPassword));

	TarDist = 1600 * fONE;
	CaAngle.x = 220;
	CaAngle.y = 0;
	CaAngle.z = 0;

	MouseDownServerIndex = -1;
	CameraFrame = 0;
}

HoOpening::~HoOpening()
{
	Close();
}

extern void LeIniStr(char* Section, char* Key, char* szFileIni, char* Var1);
extern int LeIniInt(char* Section, char* Key, char* szFileIni);
extern void WriteIniInt(char* Section, char* Key, char* szFileIni, DWORD Value);
extern void WriteIniStr(char* Section, char* Key, char* szFileIni, char* Value);

int HoOpening::Init()
{
	GameErrorValue = -1;
	ConnectErrorCount = 0;
	FocusWndFlag = FALSE;
	SetWindowText(hTextWnd, "");
	SendMessage(hTextWnd, EM_SETLIMITTEXT, 31, 0);

	LoginInputState = 0;
	ConnectError = ERROR_NONE;
	ServerWaitTimeCount = 0;
	StartQuitFlag = FALSE;

	WorkState = STATE_OPENING;
	StartConnectServerFlag = FALSE;
	ConnectServerSucessFlag = FALSE;

	FadeCurrentState = FADE_OUT;
	FadeNextState = FADE_OUT;

	LogoBlendValue = 0;
	LoginBlendValue = 0;
	ServerSelectBlendValue = 0;

	MidX = WinSizeX / 2;
	MidY = WinSizeY / 2;

	smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;

	SetWindowText(hTextWnd, NULL);

	memset(UserAccount, 0, sizeof(UserAccount));
	memset(UserPassword, 0, sizeof(UserPassword));

	TarDist = 1400 * fONE;

	CaAngle.x = 0;
	CaAngle.y = 0;
	CaAngle.z = 0;

	SetFade();

	smInitColorZClip(0, 0, 0);

	smRender.Color_R = 40;
	smRender.Color_G = 0;
	smRender.Color_B = -30;
	smRender.Color_A = 0;
	smRender.ClearLight();

	StopBGM();
	OpenBGM("StartImage\\Opening\\Intro.wav");
	PlayBGM();
	SetVolumeBGM(OpeningBgmVolume);

	char buf[32] = { 0 };
	LeIniStr("Game", "LastID", "game.ini", buf);

	if (buf != NULL)
	{
		memset(UserAccount, 0, sizeof(UserAccount));
		memcpy(UserAccount, buf, strlen(buf));
		LoginInputState = 1;
	}

	CurrentWorkState = STATE_OPENING;
	NextWorkState = STATE_OPENING;
	MouseDownServerIndex = -1;
	MouseDownFlag = FALSE;

	CameraFrame = 160;
	ChangeSky(1);
	//ChangeSky(0x80);

	g_NewParticleMgr.Init();
	InitAssaEffect();

	InitCinemaFadeEffect();

	smIdentityMatrix(m_CameraRotInvert);

	m_IsDrawOpening = TRUE;
	m_AutoCameraFrameTime = 50;
	m_ParticleSpawnTimeCount = 0;

	s_AutoCamera.m_Frame = 0;

	m_AddWidth = (smScreenWidth - 800) / 2;
	m_AddHeight = (smScreenHeight - 600) / 2;

	startLogoX = 100 + m_AddWidth;
	startLogoY = 63 + m_AddHeight;
	startLogoAddX = 32;
	startAccountAddX = 230;
	startAccountAddY = 290;

	POINT3D p;
	p.x = 150.0f * 256.0f;
	p.y = 256.0f * 256.0f;
	p.z = -150.0f * 256.0f;

	g_NewParticleMgr.Start("Opening", p);

	return TRUE;
}

void HoOpening::Resize()
{
	smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;

	m_AddWidth = (smScreenWidth - 800) / 2;
	m_AddHeight = (smScreenHeight - 600) / 2;

	startLogoX = 100 + m_AddWidth;
	startLogoY = 63 + m_AddHeight;
	startLogoAddX = 32;
	startAccountAddX = 230;
	startAccountAddY = 290;
}

void HoOpening::SetCameraCharPos(void)
{
	int x = 0;
	int y = 0;
	int z = (440 << FLOATNS);

	smEMATRIX eCameraRotInvert;
	smEMatrixInvert(eCameraRotInvert, s_AutoCamera.m_eCameraRotMat);

	memcpy((smEMATRIX*)&m_CameraRotInvert, &eCameraRotInvert, sizeof(smEMATRIX));
	smMatrixShift(m_CameraRotInvert, 4);

	int rx = x * m_CameraRotInvert._11 +
		y * m_CameraRotInvert._21 +
		z * m_CameraRotInvert._31;

	int ry = x * m_CameraRotInvert._12 +
		y * m_CameraRotInvert._22 +
		z * m_CameraRotInvert._32;

	int rz = x * m_CameraRotInvert._13 +
		y * m_CameraRotInvert._23 +
		z * m_CameraRotInvert._33;

	rx >>= FLOATS_EM;
	ry >>= FLOATS_EM;
	rz >>= FLOATS_EM;

	lpCurPlayer->pX = int(s_AutoCamera.m_fCameraPos_x) + rx;
	lpCurPlayer->pY = int(s_AutoCamera.m_fCameraPos_y) + ry;
	lpCurPlayer->pZ = int(s_AutoCamera.m_fCameraPos_z) + rz;
}

void HoOpening::SetParticleEffectSpawn(void)
{
}

int HoOpening::DebugModeLoadFieldInfo(void)
{
	FILE* fp = fopen("StartImage\\Opening\\OpeningField.txt", "rb");
	if (fp == NULL)
		return FALSE;

	Stage = NULL;

	//
	char* p, line[256], decode[256], strBuff[256];
	while (!feof(fp))//  feof: file end±îÁö ÀÐ¾î¶ó
	{
		if (fgets(line, 255, fp) == NULL)
		{
			fclose(fp);
			break;
		}

		p = GetWord(decode, line);

		//
		if (lstrcmp(decode, "*ÇÊµå¸í") == 0)
		{
			p = GetWord(strBuff, p);
			Stage = smSTAGE3D_ReadASE(strBuff);
			if (Stage)
				Stage->Head = TRUE;
		}
		else if (lstrcmp(decode, "*Ä«¸Þ¶ó¸í") == 0)
		{
			p = GetWord(strBuff, p);
			s_AutoCamera.ReadASE_AutoCamera(strBuff);
		}
		else if (lstrcmp(decode, "*Ä«¸Þ¶ó¼Óµµ") == 0)
		{
			p = GetWord(strBuff, p);
			m_AutoCameraFrameTime = atoi(strBuff);
		}
		else if (lstrcmp(decode, "*¿öÇÁÇÁ·¹ÀÓ") == 0)
		{
			p = GetWord(strBuff, p);
			int StFrame = atoi(strBuff);

			p = GetWord(strBuff, p);
			int EndFrame = atoi(strBuff);

			s_AutoCamera.SetWarpFrame(StFrame, EndFrame);
		}
		else if (lstrcmp(decode, "*ÁöÇü¹°Ã¼") == 0)
		{
			p = GetWord(strBuff, p);
			Stage->StageObject->AddObjectFile(strBuff);
		}
		else if (lstrcmp(decode, "*ÁöÇü¾Ö´Ï") == 0)
		{
			p = GetWord(strBuff, p);
			Stage->StageObject->AddObjectFile(strBuff, strBuff);
		}
	}

	fclose(fp);

	if (Stage == NULL)
		return FALSE;

	return TRUE;
}

int HoOpening::Load()
{
	int IsLoad = FALSE;
	PatCamera = NULL;
	ObjCamera = NULL;

	if (smConfig.DebugMode)
		IsLoad = DebugModeLoadFieldInfo();

	if (IsLoad == FALSE)
	{
		Stage = smSTAGE3D_ReadASE("StartImage\\Opening\\map\\stage.ASE");
		if (Stage)
		{
			Stage->Head = TRUE;

			s_AutoCamera.ReadASE_AutoCamera("StartImage\\Opening\\opening_camera.ASE");
			m_AutoCameraFrameTime = 50;
			s_AutoCamera.SetWarpFrame(472, 473);

			Stage->StageObject->AddObjectFile("StartImage\\Opening\\map\\st-ani02.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\map\\st-ani03.ASE");

			Stage->StageObject->AddObjectFile("StartImage\\Opening\\babel\\st-ani04.ASE", "StartImage\\Opening\\babel\\st-ani04.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_A.ASE", "StartImage\\Opening\\npc\\opening_NPC_A.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_B.ASE", "StartImage\\Opening\\npc\\opening_NPC_B.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_C.ASE", "StartImage\\Opening\\npc\\opening_NPC_C.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_D.ASE", "StartImage\\Opening\\npc\\opening_NPC_D.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_E.ASE", "StartImage\\Opening\\npc\\opening_NPC_E.ASE");
			Stage->StageObject->AddObjectFile("StartImage\\Opening\\npc\\opening_NPC_F.ASE", "StartImage\\Opening\\npc\\opening_NPC_F.ASE");
		}
	}

	if (Stage == NULL)
		return FALSE;

	smGameStage[0] = Stage;
	smGameStage[1] = NULL;

	GameLogo[0] = CreateTextureMaterial("game\\images\\Login\\background.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	GameLogo[1] = CreateTextureMaterial("game\\images\\Login\\enter.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	BlackBoxImage = CreateTextureMaterial("StartImage\\Login\\BlackBox.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);
	WhiteBoxImage = CreateTextureMaterial("StartImage\\Login\\WhiteBox.tga", 0, TRUE, FALSE, FALSE, SMMAT_BLEND_ALPHA);

	Message.Init();
	MessageBox.Init();

	ReadTextures();

	if (Stage)
	{
		Stage->smMaterialGroup->CheckMatreialTextureSwap();
	}

	return TRUE;
}

int		CaretCount = 0;
DWORD	End = 0;
extern int Client_Version;

#define	DISP_LOGIN_LEN		15

bool MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

int HoOpening::Draw()
{
	FastFade();

	smRender.SMMULT_PERSPECTIVE_HEIGHT = 0;

	m_AddWidth = (smScreenWidth - 800) / 2;
	m_AddHeight = (smScreenHeight - 600) / 2;

	startLogoX = 100 + m_AddWidth;
	startLogoY = 63 + m_AddHeight;
	startLogoAddX = 32;
	startAccountAddX = 230;
	startAccountAddY = 290;

	int x, y, z;
	int anx, any;

	int anz;

	x = int(s_AutoCamera.m_fCameraPos_x);
	y = int(s_AutoCamera.m_fCameraPos_y);
	z = int(s_AutoCamera.m_fCameraPos_z) + (WaveCameraFactor * 8);

	anx = s_AutoCamera.m_iCameraRot_x;
	any = s_AutoCamera.m_iCameraRot_y;
	anz = s_AutoCamera.m_iCameraRot_z;

	smRender.OpenCameraPosi(x, y, z, &s_AutoCamera.m_eCameraRotMat);
	DrawOpeningSky(x, y, z, anx, any, anz);

	if (CinemaFadeState != STATE_FADE_OUT)
	{
		Stage->DrawOpeningStage(x, y, z, anx, any, anz, s_AutoCamera.m_Frame);
	}

	DrawCinemaFadeEffect();

	g_NewParticleMgr.Draw(x, y, z, anx, any, anz);

	smRender.CloseCameraPosi();

	IncTextureFrame();

	int WinX = WinSizeX / 2 - 190;
	int WinY = WinSizeY / 2 - 200;

	HoDrawTexImage(GameLogo[0], WinX - 130, WinY - 50, 634, 583, 634, 583, LogoBlendValue);

	if (MouseAction(WinX + 273, WinY + 249, 91, 47))
		HoDrawTexImage(GameLogo[1], WinX + 273, WinY + 249, 91, 47, 91, 47, LogoBlendValue);

	DrawFade();

	if (CurrentWorkState == STATE_LOGIN_INPUT && NextWorkState == STATE_LOGIN_INPUT
		&& ScreenBlendValue <= 100)
	{
		if (LoginBlendValue >= 255)
		{
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));

			SetFontTextColor(RGB(255, 255, 255));

			if (Client_Version < 1000)
			{
				float Version = (float)Client_Version / 100;
				sprintf(buffer, "%s%2.2f%s", "Versão do Jogo: ", Version, "b");
			}
			else
			{
				int v1 = Client_Version / 1000;
				int v2 = (Client_Version / 10) % 100;
				int v3 = Client_Version % 10;
				wsprintf(buffer, "%s%d.%d.%d", "Versão do Jogo: ", v1, v2, v3);
			}

			dsTextLineOut(WinX + 135, WinY + 160, buffer, strlen(buffer));

			if (FocusWndFlag == FALSE)
			{
				FocusWndFlag = TRUE;
				hFocusWnd = hTextWnd;
			}

			if (StartConnectServerFlag == FALSE && ConnectError == ERROR_NONE)
			{
				if (pCursorPos.x > (startLogoX + startAccountAddX + 21) &&
					pCursorPos.x < (startLogoX + startAccountAddX + 21 + 95) &&
					pCursorPos.y >(startLogoY + startAccountAddY + 10) &&
					pCursorPos.y < (startLogoY + startAccountAddY + 10 + 14) &&
					MouseButton[0])
				{
					if (LoginInputState == 1)
					{
						LoginInputState = 0;
						SetWindowText(hFocusWnd, UserAccount);
						SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserAccount), lstrlen(UserAccount) + 1);
					}
				}

				if (pCursorPos.x > (startLogoX + startAccountAddX + 21) &&
					pCursorPos.x < (startLogoX + startAccountAddX + 21 + 95) &&
					pCursorPos.y >(startLogoY + startAccountAddY + 58) &&
					pCursorPos.y < (startLogoY + startAccountAddY + 58 + 14) &&
					MouseButton[0])
				{
					if (LoginInputState == 0)
					{
						SetIME_Mode(0);
						LoginInputState = 1;
						SetWindowText(hFocusWnd, UserPassword);
						SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserPassword), lstrlen(UserPassword) + 1);
					}
				}
			}

			if (hFocusWnd && ConnectError == ERROR_NONE && StartConnectServerFlag == FALSE)
			{
				if (LoginInputState == 0)
				{
					GetWindowText(hFocusWnd, UserAccount, sizeof(UserAccount));
					KeyFilter(UserAccount);
				}
				else if (LoginInputState == 1)
				{
					GetWindowText(hFocusWnd, UserPassword, sizeof(UserPassword));
					KeyFilter(UserPassword);
				}
			}

			if (hFocusWnd)
				SendMessage(hFocusWnd, EM_GETSEL, NULL, (LPARAM)&End);

			SetFontTextColor(RGB(255, 255, 255));

			if (hFocusWnd)
			{
				if (CaretCount < 16)
				{
					if (End > DISP_LOGIN_LEN) End = DISP_LOGIN_LEN;

					if (LoginInputState == 0)
						dsTextLineOut(startLogoX + startAccountAddX - 80 + End * 6 + 1, startLogoY + startAccountAddY + 19, "|", 1);
					else if (LoginInputState == 1)
						dsTextLineOut(startLogoX + startAccountAddX + 38 + End * 6 + 1, startLogoY + startAccountAddY + 19, "|", 1);
				}

				CaretCount++;
				if (CaretCount > 32)
					CaretCount = 0;
			}

			int sp, len;

			sp = 0;
			len = lstrlen(UserAccount);
			if (len > DISP_LOGIN_LEN) {
				sp = len - DISP_LOGIN_LEN;
				len -= sp;
			}
			dsTextLineOut(startLogoX + startAccountAddX - 80, startLogoY + startAccountAddY + 19, UserAccount + sp, len);
			len = lstrlen(UserPassword);
			if (len > DISP_LOGIN_LEN) len = DISP_LOGIN_LEN;

			for (int count = 0; count < len; count++)
				dsTextLineOut(startLogoX + startAccountAddX + 40 + count * 6, startLogoY + startAccountAddY + 20, "*", 1);
		}
	}

	if (StartConnectServerFlag && ConnectError == ERROR_NONE)
		DrawMessage(325 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[0]);

	if (ConnectError == ERROR_CONNECT)
	{
		StartConnectServerFlag = FALSE;
		DrawMessage(325 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[1]);
	}
	else if (ConnectError == ERROR_NO_ACCOUNT)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[2]);
	else if (ConnectError == ERROR_NO_PASSWORD)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[3]);
	else if (ConnectError == ERROR_NO_BETA_TESTER)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[4]);
	else if (ConnectError == ERROR_NO_ACCOUNT_IN)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[5]);
	else if (ConnectError == ERROR_NO_VERSION)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[6]);
	else if (ConnectError == ERROR_NO_LIMIT)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[7]);
	else if (ConnectError == ERROR_NO_SERVER_CONNECT)
		DrawMessage(300 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[8]);
	else if (ConnectError == ERROR_NO_USE_DATE_OVER)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[9]);
	else if (ConnectError == ERROR_NO_USE_TIME_OVER)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[10]);
	else if (ConnectError == ERROR_DELETE_ACCOUNT_NOTIFY)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[11]);
	else if (ConnectError == ERROR_SERVER_TRAFFIC_BUSY)
		DrawMessage(300 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[12]);
	else if (ConnectError == ERROR_SERVER_WAIT_MOMNENT)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[13]);
	else if (ConnectError == ERROR_THIRD_CONNECT)
		DrawMessage(310 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[14], 30);
	else if (ConnectError == ERROR_HAN_PASSWORD)
		DrawMessage(310 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[15], 30);
	else if (ConnectError == ERROR_12YEARS)
		DrawMessage(310 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[16], 30);
	else if (ConnectError == ERROR_HOMEAGREE)
		DrawMessage(310 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[17], 30);
	else if (ConnectError == ERROR_UNTIL_LOGINDENIED)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[18], 30);
	else if (ConnectError == ERROR_LOGIN_DENIED)
		DrawMessage(320 + m_AddWidth, 300 + m_AddHeight, HoTextLoginMessage[19], 30);

	return TRUE;
}

HANDLE	hHoLoginThread = 0;

DWORD WINAPI HoLoginThreadProc(void* pInfo)
{
	HoOpening* lpHoOpening = (HoOpening*)pInfo;

	if (!smWsockDataServer) {
		ConnectServer_InfoMain();

		if (smWsockDataServer)
		{
			ServerUserCharacterInfo = NULL;
			DownServerListInfo = NULL;
			ServerLoginError = NULL;
			lpHoOpening->ServerWaitTimeCount = 0;

			if (HoCommandLineFlag)
			{
				memset(UserAccount, 0, sizeof(UserAccount));
				memset(UserPassword, 0, sizeof(UserPassword));

				memcpy(UserAccount, HoCommandInfo.Id, strlen(HoCommandInfo.Id));
				memcpy(UserPassword, HoCommandInfo.Pass, strlen(HoCommandInfo.Pass));
			}
			TransUserCommand(smTRANSCODE_ID_GETUSERINFO, UserAccount, UserPassword);
		}
		else {
			lpHoOpening->ConnectError = ERROR_CONNECT;
			lpHoOpening->StartConnectServerFlag = FALSE;
		}
	}

	hHoLoginThread = 0;

	ExitThread(TRUE);
	return TRUE;
}

int HoOpening::LoginDataServer()
{
	DWORD dwHoLoginThreadId;

	if (!hHoLoginThread) {
		hHoLoginThread = CreateThread(NULL, 0, HoLoginThreadProc, this, 0, &dwHoLoginThreadId);

		PlayWav2(13 - 1);
		StartConnectServerFlag = TRUE;
		return TRUE;
	}
	return FALSE;
}

int HoOpening::LoginGameServer(int serverIndex)
{
	PlayWav2(13 - 1);
	DisconnectServer_GameMain();

	if (ConnectServer_GameMain(UserServerListInfo[serverIndex].szServerIp1,
		UserServerListInfo[serverIndex].dwServerPort1,
		UserServerListInfo[serverIndex].szServerIp2,
		UserServerListInfo[serverIndex].dwServerPort2,
		UserServerListInfo[serverIndex].szServerIp3,
		UserServerListInfo[serverIndex].dwServerPort3))
	{
		StartConnectServerFlag = TRUE;
	}
	else
		ConnectError = ERROR_CONNECT;

	return TRUE;
}

int HoOpening::KeyFilter(char* message)
{
	if (message == NULL || hFocusWnd == NULL)
		return FALSE;

	if (lstrlen(message) >= 31 && message[30] != '\t')
	{
		message[30] = 0;
		SetWindowText(hFocusWnd, 0);
		SetWindowText(hFocusWnd, message);
		SendMessage(hFocusWnd, EM_SETSEL, lstrlen(message) + 1, lstrlen(message) + 1);
	}

	for (int index = 0; index < (int)strlen(message); index++)
	{
		if (message[index] == '\t')
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, 0);

			if (LoginInputState == 0)
			{
				SetIME_Mode(0);
				LoginInputState = 1;
				SetWindowText(hFocusWnd, UserPassword);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserPassword) + 1, lstrlen(UserPassword) + 1);
			}
			else if (LoginInputState == 1)
			{
				LoginInputState = 0;
				SetWindowText(hFocusWnd, UserAccount);
				SendMessage(hTextWnd, EM_SETSEL, lstrlen(UserAccount) + 1, lstrlen(UserAccount) + 1);
			}
		}

		if (message[index] == ' ')
		{
			message[index] = 0;
			SetWindowText(hFocusWnd, message);
			SendMessage(hTextWnd, EM_SETSEL, lstrlen(message) + 1, lstrlen(message) + 1);
			break;
		}
	}

	return TRUE;
};

int HoOpening::MainFadeIn()
{
	if (FadeNextState == FADE_IN)
	{
		ScreenBlendValue -= 2;
		if (ScreenBlendValue < 0)
			ScreenBlendValue = 0;

		if (ScreenBlendValue <= 0)
		{
			ScreenBlendValue = 0;
			FadeCurrentState = FADE_IN;
			FadeNextState = FADE_IN;
		}
	}
	return TRUE;
}

int HoOpening::MainFadeOut()
{
	if (FadeNextState == FADE_OUT)
	{
		if (ScreenBlendValue < 255)
		{
			OpeningBgmVolume -= 2;
			if (OpeningBgmVolume < 0)
				OpeningBgmVolume = 0;
			ScreenBlendValue += 3;
		}

		if (ScreenBlendValue >= 255)
		{
			ScreenBlendValue = 255;
			LogoBlendValue = 255;
			LoginBlendValue = 255;
			FadeCurrentState = FADE_OUT;
			FadeNextState = FADE_OUT;
		}
	}
	return TRUE;
}

void HoOpening::InitCinemaFadeEffect()
{
	CinemaFadeOutFlag = FALSE;
	CinemaBlendValue = 0;
	CinemaFadeState = STATE_FADE_NONE;
}

void HoOpening::MainCinemaFadeEffect()
{
	if (CinemaFadeState == STATE_FADE_IN)
	{
		CinemaBlendValue += 5;
		if (CinemaBlendValue >= 255)
			CinemaBlendValue = 255;
	}

	if (CinemaFadeState == STATE_FADE_IN && CinemaBlendValue >= 255)
		CinemaFadeState = STATE_FADE_OUT;

	if (CinemaFadeState == STATE_FADE_OUT)
	{
		CinemaBlendValue -= 5;
		if (CinemaBlendValue <= 0)
			CinemaBlendValue = 0;
	}
}

void HoOpening::DrawCinemaFadeEffect()
{
	if (CinemaFadeState != STATE_FADE_NONE)
	{
		if (CinemaBlendValue >= 0 && CinemaBlendValue <= 255)
		{
			dsDrawTexImage(WhiteBoxImage, 0, 0, smScreenWidth, smScreenHeight, CinemaBlendValue);
		}
	}
}

int HoOpening::FastFade()
{
	if ((FadeNextState == FADE_IN && LoginBlendValue < 255) ||
		(FadeNextState == FADE_OUT && LoginBlendValue > 0))
	{
		static bool fastBlendFlag = false;
		for (int index = 0; index < 256; index++)
		{
			if (VRKeyBuff[index] == TRUE)
			{
				fastBlendFlag = true;
				break;
			}
		}

		if (MouseDownFlag == FALSE)
		{
			if (MouseButton[0] && fastBlendFlag == false)
			{
				fastBlendFlag = true;
				MouseDownFlag = TRUE;
			}
		}

		if (fastBlendFlag)
		{
			if (FadeNextState == FADE_IN)
			{
				if ((CurrentWorkState == STATE_OPENING &&
					NextWorkState == STATE_OPENING) ||
					(CurrentWorkState == STATE_OPENING && NextWorkState == STATE_LOGIN_INPUT))
				{
					LogoBlendValue = 255;
					ScreenBlendValue = 0;
					FadeCurrentState = FADE_IN;

					if (HoCommandLineFlag == FALSE)
					{
						LoginBlendValue = 255;
						CurrentWorkState = STATE_LOGIN_INPUT;
						NextWorkState = STATE_LOGIN_INPUT;
					}

					if (HoCommandLineFlag)
						NextWorkState = STATE_LOGIN_INPUT;
				}
			}
			else if (FadeNextState == FADE_OUT)
			{
				LogoBlendValue = 0;
				LoginBlendValue = 0;
				ScreenBlendValue = 255;
				OpeningBgmVolume = 0;
				FadeCurrentState = FADE_OUT;
			}
			fastBlendFlag = false;
		}
	}
	return TRUE;
}

int HoOpening::DrawFade()
{
	if (ScreenBlendValue >= 0 && ScreenBlendValue <= 255)
		dsDrawTexImage(BlackBoxImage, 0, 0, smScreenWidth, smScreenHeight, ScreenBlendValue);

	return TRUE;
}

int HoOpening::MainFade()
{
	if ((FadeNextState == FADE_IN) ||
		(FadeNextState == FADE_OUT))
	{
		if (FadeCurrentState != FadeNextState)
		{
			if (FadeNextState == FADE_IN)
				MainFadeIn();
			else
			{
				SetVolumeBGM(OpeningBgmVolume);
				MainFadeOut();
			}
		}
	}
	return TRUE;
}

void HoOpening::SetFade()
{
	if (FadeCurrentState == FADE_OUT)
	{
		FadeNextState = FADE_IN;
		ScreenBlendValue = 254;
		OpeningBgmVolume = 350;
	}
	else
	{
		FadeNextState = FADE_OUT;
		ScreenBlendValue = 1;
	}
}

void HoOpening::Close()
{
	if (Stage)
	{
		delete Stage;
		Stage = NULL;

		lpCurPlayer->pX = lpCurPlayer->pY = lpCurPlayer->pZ = 0;
		smGameStage[0] = NULL;
		smGameStage[1] = NULL;
	}

	if (PatCamera)
	{
		delete PatCamera;
		PatCamera = NULL;
	}

	BackColor_R = 0;
	BackColor_G = 0;
	BackColor_B = 0;

	BackColor_mR = 0;
	BackColor_mG = 0;
	BackColor_mB = 0;

	InitSky();
}

int HoOpening::Main()
{
	if (MouseButton[0] == FALSE)
	{
		MouseDownFlag = FALSE;
	}

	float timeDelta = 1.f / 70.f;
	g_NewParticleMgr.Main(0.0f, timeDelta);

	MainSky();
	m_IsDrawOpening = s_AutoCamera.FrameMain(m_AutoCameraFrameTime);
	if (m_IsDrawOpening > 1 && CinemaFadeOutFlag == FALSE)
	{
		CinemaFadeState = STATE_FADE_IN;
		CinemaFadeOutFlag = TRUE;
	}

	SetCameraCharPos();
	if (m_IsDrawOpening == 1)
		SetParticleEffectSpawn();

	MainAssaEffect();
	MainCinemaFadeEffect();

	if (WaveCameraFlag)
	{
		WaveCameraTimeCount++;

		if ((WaveCameraTimeCount > WaveCameraDelay))
		{
			WaveCameraTimeCount = 0;
			if (WaveCameraDelay > 1 && WaveCameraFactor < 40)
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f * 9.f);
			else
				WaveCameraFactor = -int((float)WaveCameraFactor / 10.f * 8.f);
		}

		if (abs(WaveCameraFactor) < 1)
		{
			WaveCameraFlag = FALSE;
			WaveCameraTimeCount = 0;
		}
	}

	if (ConnectError != ERROR_NONE)
	{
		if (ConnectErrorCount >= 160)
		{
			MouseDownServerIndex = -1;
			bool errorEndFlag = false;

			if (MouseButton[0] || MouseDblClick)
				errorEndFlag = true;

			for (int index = 0; index < 256; index++)
			{
				if (VRKeyBuff[index] == TRUE)
				{
					errorEndFlag = true;
					break;
				}
			}

			if (ConnectErrorCount >= 250)
				errorEndFlag = true;

			if (errorEndFlag)
			{
				ConnectError = ERROR_NONE;
				FocusWndFlag = FALSE;
				ConnectErrorCount = 0;
			}

			if (errorEndFlag && HoCommandLineFlag
				&& CurrentWorkState == STATE_LOGIN_INPUT
				&& NextWorkState == STATE_LOGIN_INPUT)
			{
				HoCommandLineFlag = FALSE;
				NextWorkState = STATE_LOGIN_INPUT;
				CurrentWorkState = STATE_OPENING;
				ConnectServerSucessFlag = FALSE;
				DisconnectServerFull();
			}
		}
		ConnectErrorCount++;
	}

	MainFade();

	if (CurrentWorkState == STATE_OPENING && NextWorkState == STATE_OPENING)
	{
		if (CinemaFadeState == STATE_FADE_OUT)
			NextWorkState = STATE_LOGIN_INPUT;
	}

	if (CurrentWorkState == STATE_OPENING && NextWorkState == STATE_LOGIN_INPUT)
	{
		if (FadeNextState == FADE_IN)
		{
			LogoBlendValue += 1;
			if (LogoBlendValue >= 255)
				LogoBlendValue = 255;

			if (LogoBlendValue >= 255)
			{
				if (HoCommandLineFlag)
				{
					CurrentWorkState = STATE_LOGIN_INPUT;
					LoginDataServer();
				}
				else
				{
					LoginBlendValue += 1;
					if (LoginBlendValue >= 255)
					{
						LoginBlendValue = 255;
						CurrentWorkState = STATE_LOGIN_INPUT;
					}
				}
			}
		}
	}

	if (CurrentWorkState == STATE_LOGIN_INPUT
		&& NextWorkState == STATE_LOGIN_INPUT
		&& (LoginBlendValue >= 255)
		&& (ScreenBlendValue <= 0)
		&& StartConnectServerFlag == FALSE
		&& ConnectError == ERROR_NONE)
	{
		if (FocusWndFlag && hFocusWnd == NULL
			&& ConnectServerSucessFlag == FALSE
			&& ConnectError == ERROR_NONE)
		{
			LoginDataServer();
		}

		int downFlag = -1;

		if (MouseDownFlag == FALSE)
		{
			if (MouseButton[0])
			{
				int WinX = WinSizeX / 2 - 190;
				int WinY = WinSizeY / 2 - 200;

				if (MouseAction(WinX + 273, WinY + 249, 91, 47))
					LoginDataServer();

				MouseButton[0] = false;
			}
		}
	}

	if (CurrentWorkState == STATE_SERVER_SELECT
		&& NextWorkState == STATE_SERVER_SELECT)
	{
		if (ConnectError == ERROR_NONE && !StartConnectServerFlag)
		{
			LoginGameServer(0);
		}
	}

	if (CurrentWorkState == STATE_SERVER_SELECT
		&& NextWorkState == STATE_SERVER_SELECT)
	{
		int selectHeight;
		int selectStartPosX;
		int selectStartPosY;

		if (UserServerListInfoCount != 0)
			selectHeight = 90 / UserServerListInfoCount;
		selectStartPosX = 230 + startLogoX;
		selectStartPosY = 315 + startLogoY + (selectHeight - 12) / 2;

		for (int index = 0; index < UserServerListInfoCount; index++)
		{
			if (pCursorPos.x > (selectStartPosX) && (pCursorPos.y > selectStartPosY + index * selectHeight) &&
				pCursorPos.x < (selectStartPosX + 140) && (pCursorPos.y < (selectStartPosY + index * selectHeight + 12)) &&
				ConnectError == ERROR_NONE && !StartConnectServerFlag)
			{
				if (MouseButton[0] && MouseDownFlag == FALSE)
				{
					MouseDownFlag = TRUE;
					MouseDownServerIndex = index;
					LoginGameServer(index);
				}
			}
		}
	}

	if (CurrentWorkState == STATE_SERVER_SELECT
		&& NextWorkState == STATE_SERVER_SELECT)
	{
		BOOL flag = FALSE;
		if (ConnectError == ERROR_NONE && !StartConnectServerFlag && StartQuitFlag == FALSE)
		{
			if (MouseDownFlag == FALSE)
			{
				if (MouseButton[0])
				{
					if (pCursorPos.x > (startLogoX + 230 + 32) &&
						pCursorPos.y > (startLogoY + 320 + 93) &&
						pCursorPos.x < (startLogoX + 230 + 32 + 64) &&
						pCursorPos.y < (startLogoY + 320 + 93 + 25))
					{
						flag = TRUE;
						MouseDownFlag = TRUE;
					}
				}
			}
		}

		if (!smWsockDataServer && GameErrorValue == 0)
		{
			NextWorkState = STATE_LOGIN_INPUT;
			ConnectServerSucessFlag = FALSE;
			DisconnectServerFull();
			ConnectError = ERROR_NO_SERVER_CONNECT;
		}

		if (flag)
		{
			PlayWav2(4 - 1);

			if (!HoCommandLineFlag)
			{
				FocusWndFlag = FALSE;
				NextWorkState = STATE_LOGIN_INPUT;
				CurrentWorkState = STATE_LOGIN_INPUT;
				ConnectServerSucessFlag = FALSE;
				DisconnectServerFull();
			}
			else
			{
				DisconnectServerFull();
				StartQuitFlag = TRUE;
				SetFade();
				ConnectServerSucessFlag = FALSE;
				MouseDownFlag = FALSE;
			}
		}
	}

	if (StartConnectServerFlag)
	{
		if (ConnectError != ERROR_NONE)
		{
			StartConnectServerFlag = FALSE;
			ServerWaitTimeCount = 0;
		}

		if (ServerLoginError)
		{
			if (CurrentWorkState == STATE_LOGIN_INPUT
				&& NextWorkState == STATE_LOGIN_INPUT)
				DisconnectServerFull();

			if (CurrentWorkState == STATE_SERVER_SELECT
				&& NextWorkState == STATE_SERVER_SELECT)
				DisconnectServer_GameMain();

			if (ServerLoginError->WParam == 0)
				ConnectError = ERROR_CONNECT;
			else if (ServerLoginError->WParam == -1)
				ConnectError = ERROR_NO_ACCOUNT;
			else if (ServerLoginError->WParam == -2)
				ConnectError = ERROR_NO_PASSWORD;
			else if (ServerLoginError->WParam == -3)
				ConnectError = ERROR_NO_BETA_TESTER;
			else if (ServerLoginError->WParam == -4)
				ConnectError = ERROR_NO_ACCOUNT_IN;
			else if (ServerLoginError->WParam == -5)
				ConnectError = ERROR_NO_USE_DATE_OVER;
			else if (ServerLoginError->WParam == -6)
				ConnectError = ERROR_NO_USE_TIME_OVER;
			else if (ServerLoginError->WParam == -8)
				ConnectError = ERROR_DELETE_ACCOUNT_NOTIFY;
			else if (ServerLoginError->WParam == -16)
				ConnectError = ERROR_SERVER_TRAFFIC_BUSY;
			else if (ServerLoginError->WParam == -17)
				ConnectError = ERROR_SERVER_WAIT_MOMNENT;
			else if (ServerLoginError->WParam == -18)
				ConnectError = ERROR_THIRD_CONNECT;
			else if (ServerLoginError->WParam == -19)
				ConnectError = ERROR_HAN_PASSWORD;
			else if (ServerLoginError->WParam == -12)
				ConnectError = ERROR_12YEARS;
			else if (ServerLoginError->WParam == -13)
				ConnectError = ERROR_HOMEAGREE;
			else if (ServerLoginError->WParam == -23)
				ConnectError = ERROR_UNTIL_LOGINDENIED;
			else if (ServerLoginError->WParam == -24)
				ConnectError = ERROR_LOGIN_DENIED;

			StartConnectServerFlag = FALSE;
			ServerWaitTimeCount = 0;
			ServerLoginError = NULL;
		}

		ServerWaitTimeCount++;
		if (ServerWaitTimeCount >= 3000)
		{
			ServerWaitTimeCount = 0;
			ConnectError = ERROR_CONNECT;
			StartConnectServerFlag = FALSE;
			ConnectServerSucessFlag = FALSE;
		}

		if (CurrentWorkState == STATE_LOGIN_INPUT &&
			NextWorkState == STATE_LOGIN_INPUT)
		{
			if (ServerUserCharacterInfo
				&& DownServerListInfo
				&& ConnectError == ERROR_NONE
				&& GameErrorValue == 0)
			{
#ifdef _XTRAP_GUARD_4_CLIENT
				XTrap_C_SetUserInfo(UserAccount, szConnServerName, NULL, NULL, 0);
#endif

				StartConnectServerFlag = FALSE;
				ConnectServerSucessFlag = TRUE;
				CurrentWorkState = STATE_SERVER_SELECT;
				NextWorkState = STATE_SERVER_SELECT;
				GameErrorValue = -1;
			}
		}

		if (CurrentWorkState == STATE_SERVER_SELECT
			&& NextWorkState == STATE_SERVER_SELECT)
		{
			if (ConnectError == ERROR_NONE && GameErrorValue == 0)
			{
				StartConnectServerFlag = FALSE;
				SetFade();
				NextWorkState = STATE_END;
				GameErrorValue = -1;
			}
		}

		if (GameErrorValue != 0)
		{
			if (GameErrorValue == 1)
			{
				DisconnectServerFull();
				ConnectError = ERROR_NO_VERSION;
				StartConnectServerFlag = FALSE;
				GameErrorValue = -1;
			}

			if (GameErrorValue == 2)
			{
				if (CurrentWorkState == STATE_LOGIN_INPUT
					&& NextWorkState == STATE_LOGIN_INPUT)
					DisconnectServerFull();

				if (CurrentWorkState == STATE_SERVER_SELECT
					&& NextWorkState == STATE_SERVER_SELECT)
					DisconnectServer_GameMain();

				ConnectError = ERROR_NO_LIMIT;
				StartConnectServerFlag = FALSE;
				GameErrorValue = -1;
			}
		}
	}

	if (ConnectServerSucessFlag)
	{
		if (FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT)
		{
			try
			{
				File file("game.ini");

				if (file.readInt("Game", "RememberID"))
				{
					file.write("Game", "LastID", UserAccount);
				}
			}
			catch (FileException& e)
			{
				char buffer[100] = { 0 };
				strcpy_s(buffer, sizeof(buffer), e.what());
				//Log::getInstance()->output(LOG_GAME, buffer);
			}

			SetWindowText(hTextWnd, NULL);
			SendMessage(hTextWnd, EM_SETLIMITTEXT, 80, 0);

			StopBGM();
			return 2;
		}
	}

	if (StartQuitFlag)
	{
		if (FadeCurrentState == FADE_OUT && FadeNextState == FADE_OUT)
			quit = 1;
	}

	return 1;
}