#include "sinbaram\\sinlinkheader.h"
#include "HoBaram\\HoLinkHeader.h"
#include "field.h"

time_t	tServerTime;
int rsPutItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode);
int	rsSendMoneyToUser(rsPLAYINFO* lpPlayInfo, int Money);
sDEF_ITEMINFO* PremioQuest(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode);

char szBufferTextWindow[8092];

void LoadTextFromFile(const char* pszFile)
{
	FILE* pFile = NULL;

	ZeroMemory(szBufferTextWindow, 8092);

	fopen_s(&pFile, pszFile, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		int iSizeFile = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		if (iSizeFile > 8092)
			iSizeFile = 8092;

		fread(szBufferTextWindow, iSizeFile, 1, pFile);
		fclose(pFile);
	}

	szBufferTextWindow;
}

void Quest::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\quest\\head.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\quest\\minimizar_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\quest\\seta.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\quest\\seta_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Images[4] = CreateTextureMaterial("game\\images\\quest\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[5] = CreateTextureMaterial("game\\images\\quest\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[6] = CreateTextureMaterial("game\\images\\quest\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[7] = CreateTextureMaterial("game\\images\\quest\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[8] = CreateTextureMaterial("game\\images\\quest\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[9] = CreateTextureMaterial("game\\images\\settings\\checkbox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[10] = CreateTextureMaterial("game\\images\\settings\\checkbox_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	QuestStart_State = 0;
	QuestStart_Param1 = 0;
	QuestStart_Param2 = 0;

	QuestTraje_State = 0;
	QuestTraje_Param1 = 0;
	QuestTraje_Param2 = 0;

	QuestBota_State = 0;
	QuestBota_Param1 = 0;
	QuestBota_Param2 = 0;

	QuestAmuleto_State = 0;
	QuestAmuleto_Param1 = 0;
	QuestAmuleto_Param2 = 0;

	QuestLv150A_State = 0;
	QuestLv150A_Param = 0;
	QuestLv150A_Time = 0;
	QuestLv150B_State = 0;
	QuestLv150B_Param = 0;
	QuestLv150B_Time = 0;
}

void Quest::Main()
{
	if (ShowProgress)
	{
		if (FX > 0)
			FX -= 2.5;
		if (Opacity < 76)
			Opacity += 3;
		if (Size < 65)
			Size += 2.5;
	}
	else
	{
		if (FX < 25)
			FX += 2.5;
		if (Opacity > 0)
			Opacity -= 3;
		if (Size > 0)
			Size -= 2.5;
	}

	if (ShowProgress2)
	{
		if (FX2 > 0)
			FX2 -= 2.5;
		if (Opacity2 < 76)
			Opacity2 += 3;
		if (Size2 < 65)
			Size2 += 2.5;
	}
	else
	{
		if (FX2 < 25)
			FX2 += 2.5;
		if (Opacity2 > 0)
			Opacity2 -= 3;
		if (Size2 > 0)
			Size2 -= 2.5;
	}

	if (ShowProgress3)
	{
		if (FX3 > 0)
			FX3 -= 2.5;
		if (Opacity3 < 76)
			Opacity3 += 3;
		if (Size3 < 65)
			Size3 += 2.5;
	}
	else
	{
		if (FX3 < 25)
			FX3 += 2.5;
		if (Opacity3 > 0)
			Opacity3 -= 3;
		if (Size3 > 0)
			Size3 -= 2.5;
	}

	if (ShowProgress4)
	{
		if (FX4 > 0)
			FX4 -= 2.5;
		if (Opacity4 < 76)
			Opacity4 += 3;
		if (Size4 < 65)
			Size4 += 2.5;
	}
	else
	{
		if (FX4 < 25)
			FX4 += 2.5;
		if (Opacity4 > 0)
			Opacity4 -= 3;
		if (Size4 > 0)
			Size4 -= 2.5;
	}

	if (ShowProgress5)
	{
		if (FX5 > 0)
			FX5 -= 2.5;
		if (Opacity5 < 76)
			Opacity5 += 3;
		if (Size5 < 65)
			Size5 += 2.5;
	}
	else
	{
		if (FX5 < 25)
			FX5 += 2.5;
		if (Opacity5 > 0)
			Opacity5 -= 3;
		if (Size5 > 0)
			Size5 -= 2.5;
	}

	if (ShowProgress6)
	{
		if (FX6 > 0)
			FX6 -= 2.5;
		if (Opacity6 < 76)
			Opacity6 += 3;
		if (Size6 < 65)
			Size6 += 2.5;
	}
	else
	{
		if (FX6 < 25)
			FX6 += 2.5;
		if (Opacity6 > 0)
			Opacity6 -= 3;
		if (Size6 > 0)
			Size6 -= 2.5;
	}

	if (ShowProgress7)
	{
		if (FX7 > 0)
			FX7 -= 2.5;
		if (Opacity7 < 76)
			Opacity7 += 3;
		if (Size7 < 65)
			Size7 += 2.5;
	}
	else
	{
		if (FX7 < 25)
			FX7 += 2.5;
		if (Opacity7 > 0)
			Opacity7 -= 3;
		if (Size7 > 0)
			Size7 -= 2.5;
	}

	if (ShowProgress8)
	{
		if (FX8 > 0)
			FX8 -= 2.5;
		if (Opacity8 < 76)
			Opacity8 += 3;
		if (Size8 < 65)
			Size8 += 2.5;
	}
	else
	{
		if (FX8 < 25)
			FX8 += 2.5;
		if (Opacity8 > 0)
			Opacity8 -= 3;
		if (Size8 > 0)
			Size8 -= 2.5;
	}

	if (ShowProgress9)
	{
		if (FX9 > 0)
			FX9 -= 2.5;
		if (Opacity9 < 76)
			Opacity9 += 3;
		if (Size9 < 65)
			Size9 += 2.5;
	}
	else
	{
		if (FX9 < 25)
			FX9 += 2.5;
		if (Opacity9 > 0)
			Opacity9 -= 3;
		if (Size9 > 0)
			Size9 -= 2.5;
	}
}

bool Quest::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Quest::Draw()
{
	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 49)
		return;

	char szBuff[256];
	SIZE size;

	int BPoint = (WinSizeX - 264);
	int EPoint = 0;
	int wy = (WinSizeY / 80);

	if (WinSizeX == 800 || WinSizeX == 1024 || WinSizeX == 1280 || WinSizeX == 1400)
		EPoint = BPoint - (WinSizeX / 6);
	else if (WinSizeX == 1366 || WinSizeX == 1600 || WinSizeX == 1920)
		EPoint = BPoint - (WinSizeX / 7);
	else
		EPoint = BPoint - (WinSizeX / 8);

	if (QuestLv150A_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity), EPoint, wy + 24, 264, (int)Size);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX * 10);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 10, wy + 32 - FX, "Caçe Monstros Poderosos em Abismo do\nMar.", 42);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / %d", QuestLv150A_Param, QuestLv150A_Type ? 2000 : 1000);
		dsTextLineOut(EPoint + 30, wy + 64 - FX, szBuff, strlen(szBuff));

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, " A Infestação dos Mares", 24);
		FontType = 0;

		if (!ShowProgress)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size;
	}

	if (QuestLv150B_State && QuestLv150B_State < 6)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity2), EPoint, wy + 24, 264, (int)Size2);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);

		SetFontOpacity(255 - FX2 * 10);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 10, wy + 32 - FX2, "Caçe Monstros Poderosos pelo continente.\n", 42);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 1", QuestLv150B_Param);
		dsTextLineOut(EPoint + 30, wy + 64 - FX2, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));

		char szMob[32] = "";

		switch (QuestLv150B_State)
		{
		case 1:
			wsprintf(szMob, " Babel");
			break;
		case 2:
			wsprintf(szMob, " Tulla");
			break;
		case 3:
			wsprintf(szMob, " Draxos");
			break;
		case 4:
			wsprintf(szMob, " Greedy");
			break;
		case 5:
			wsprintf(szMob, " Midranda");
			break;
		}

		dsTextLineOut(EPoint + 30 + size.cx, wy + 64 - FX2, szMob, strlen(szMob));

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "Desafio Mortal", 15);
		FontType = 0;

		if (!ShowProgress2)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress2)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size2;
	}

	if (QuestStart_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity3), EPoint, wy + 24, 264, (int)Size3);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX3 * 10);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 50", QuestStart_Param1);
		dsTextLineOut(EPoint + 30, wy + 32 - FX3, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 30 + size.cx, wy + 32 - FX3, " Hopi", 6);

		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 20", QuestStart_Param2);
		dsTextLineOut(EPoint + 30, wy + 64 - FX3, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 30 + size.cx, wy + 64 - FX3, " Duende Macabro", 16);

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "Ponto de Ignição", 17);
		FontType = 0;

		if (!ShowProgress3)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress3)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size3;
	}

	if (QuestTraje_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity4), EPoint, wy + 24, 264, (int)Size4);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX4 * 10);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 100", QuestTraje_Param1);
		dsTextLineOut(EPoint + 30, wy + 32 - FX4, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 30 + size.cx, wy + 32 - FX4, " Grotesco", 9);

		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 70", QuestTraje_Param2);
		dsTextLineOut(EPoint + 30, wy + 64 - FX4, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 30 + size.cx, wy + 64 - FX4, " Golem de Aço", 13);

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "Teste de Força", 14);
		FontType = 0;

		if (!ShowProgress4)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress4)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size4;
	}

	if (QuestBota_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity5), EPoint, wy + 24, 264, (int)Size5);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX5 * 10);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 100", QuestBota_Param1);
		dsTextLineOut(EPoint + 30, wy + 32 - FX5, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 30 + size.cx, wy + 32 - FX5, " Seto", 5);

		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 150", QuestBota_Param2);
		dsTextLineOut(EPoint + 30, wy + 64 - FX5, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 30 + size.cx, wy + 64 - FX5, " Elite Guardian", 15);

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "Espíritos da Torre", 18);
		FontType = 0;

		if (!ShowProgress5)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress5)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size5;
	}

	if (QuestAmuleto_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity6), EPoint, wy + 24, 264, (int)Size6);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX6 * 10);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 300", QuestAmuleto_Param1);
		dsTextLineOut(EPoint + 10, wy + 32 - FX6, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 10 + size.cx, wy + 32 - FX6, " Turkan", 7);

		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 250", QuestAmuleto_Param2);
		dsTextLineOut(EPoint + 10, wy + 49 - FX6, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 10 + size.cx, wy + 49 - FX6, " Big Mama", 9);

		//SetFontTextColor(RGB(255, 220, 0));
		//wsprintf(szBuff, "%d / 700", QuestAmuleto_Param3);
		//dsTextLineOut(EPoint + 10, wy + 66 - FX6, szBuff, strlen(szBuff));
		//GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		//SetFontTextColor(RGB(207, 190, 163));
		//dsTextLineOut(EPoint + 10 + size.cx, wy + 66 - FX6, " Psychol Chief", 14);

		//SetFontTextColor(RGB(255, 220, 0));
		//wsprintf(szBuff, "%d / 800", QuestAmuleto_Param4);
		//dsTextLineOut(EPoint + 130, wy + 32 - FX6, szBuff, strlen(szBuff));
		//GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		//SetFontTextColor(RGB(207, 190, 163));
		//dsTextLineOut(EPoint + 130 + size.cx, wy + 32 - FX6, " Ogro General", 13);

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "Castigo Eterno", 14);
		FontType = 0;

		if (!ShowProgress6)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress6)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size6;
	}

	if (QuestLv155A_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity7), EPoint, wy + 24, 264, (int)Size7);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX7 * 10);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 10, wy + 32 - FX7, "Caçe Monstros Poderosos em Coração de\nFogo.", 44);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / %d", QuestLv155A_Param, QuestLv155A_Type ? 1000 : 350);
		dsTextLineOut(EPoint + 30, wy + 64 - FX7, szBuff, strlen(szBuff));

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "Invasão do Fogo", 16);
		FontType = 0;

		if (!ShowProgress7)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress7)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size7;
	}

	if (QuestLv160A_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity8), EPoint, wy + 24, 264, (int)Size8);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX8 * 10);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 50", QuestLv160A_Param1);
		dsTextLineOut(EPoint + 30, wy + 32 - FX8, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));

		switch (QuestLv160A_Type)
		{
		case 0:
			dsTextLineOut(EPoint + 30 + size.cx, wy + 32 - FX8, " Undead Enginer", 16);
			break;
		case 1:
			dsTextLineOut(EPoint + 30 + size.cx, wy + 32 - FX8, " Supreme Guardian", 20);
			break;
		case 2:
			dsTextLineOut(EPoint + 30 + size.cx, wy + 32 - FX8, " Sentinel", 16);
			break;
		case 3:
			dsTextLineOut(EPoint + 30 + size.cx, wy + 32 - FX8, " The Bomber", 16);
			break;
		}

		/*SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / 10", QuestLv160A_Param2);
		dsTextLineOut(EPoint + 30, wy + 64 - FX5, szBuff, strlen(szBuff));
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 30 + size.cx, wy + 64 - FX5, " Guerreiros Nortenhos", 22);*/

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "Artigos de Pesquisa", 20);
		FontType = 0;

		if (!ShowProgress8)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress8)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size8;
	}

	if (QuestLv160B_State == 1)
	{
		dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, (int)Opacity9), EPoint, wy + 24, 264, (int)Size9);

		HoDrawTexImage(Images[0], EPoint, wy, 264, 24, 264, 24, 255);
		SetFontOpacity(255 - FX9 * 10);
		SetFontTextColor(RGB(207, 190, 163));
		dsTextLineOut(EPoint + 10, wy + 32 - FX9, "Caçe Monstros Poderosos em Núcleo\nCongelado.", 45);
		SetFontTextColor(RGB(255, 220, 0));
		wsprintf(szBuff, "%d / %d", QuestLv160B_Param, QuestLv160B_Type ? 1500 : 500);
		dsTextLineOut(EPoint + 30, wy + 64 - FX9, szBuff, strlen(szBuff));

		SetFontOpacity(255);

		FontType = 1;
		SetFontTextColor(RGB(255, 250, 213));
		dsTextLineOut(EPoint + 30, wy + 5, "O Inverno chegou", 17);
		FontType = 0;

		if (!ShowProgress9)
			HoDrawTexImage(Images[2], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);

		if (MouseAction(EPoint, wy, 264, 24))
		{
			HoDrawTexImage(Images[1], EPoint + 249, wy + 11, 8, 2, 8, 2, 255);

			if (!ShowProgress9)
				HoDrawTexImage(Images[3], EPoint + 249, wy + 8, 8, 8, 8, 8, 255);
		}

		wy += 25 + Size9;
	}
}

void Quest::Button()
{
	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 49)
		return;

	int BPoint = (WinSizeX - 200);
	int EPoint = 0;
	int wy = (WinSizeY / 80);

	if (WinSizeX == 800 || WinSizeX == 1024 || WinSizeX == 1280 || WinSizeX == 1400)
		EPoint = BPoint - (WinSizeX / 6);
	else if (WinSizeX == 1366 || WinSizeX == 1600 || WinSizeX == 1920)
		EPoint = BPoint - (WinSizeX / 7);
	else
		EPoint = BPoint - (WinSizeX / 8);

	if (QuestLv150A_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress)
				ShowProgress = 0;
			else
				ShowProgress = 1;
		}

		wy += 25 + Size;
	}

	if (QuestLv150B_State && QuestLv150B_State < 6)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress2)
				ShowProgress2 = 0;
			else
				ShowProgress2 = 1;
		}

		wy += 25 + Size2;
	}

	if (QuestStart_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress3)
				ShowProgress3 = 0;
			else
				ShowProgress3 = 1;
		}

		wy += 25 + Size3;
	}

	if (QuestTraje_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress4)
				ShowProgress4 = 0;
			else
				ShowProgress4 = 1;
		}

		wy += 25 + Size4;
	}

	if (QuestBota_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress5)
				ShowProgress5 = 0;
			else
				ShowProgress5 = 1;
		}

		wy += 25 + Size5;
	}

	if (QuestAmuleto_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress6)
				ShowProgress6 = 0;
			else
				ShowProgress6 = 1;
		}

		wy += 25 + Size6;
	}

	if (QuestLv155A_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress7)
				ShowProgress7 = 0;
			else
				ShowProgress7 = 1;
		}

		wy += 25 + Size7;
	}

	if (QuestLv160A_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress8)
				ShowProgress8 = 0;
			else
				ShowProgress8 = 1;
		}

		wy += 25 + Size8;
	}

	if (QuestLv160B_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			if (ShowProgress9)
				ShowProgress9 = 0;
			else
				ShowProgress9 = 1;
		}

		wy += 25 + Size9;
	}
}

void Quest::RButton()
{
	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 49)
		return;

	int BPoint = (WinSizeX - 200);
	int EPoint = 0;
	int wy = (WinSizeY / 80);

	if (WinSizeX == 800 || WinSizeX == 1024 || WinSizeX == 1280 || WinSizeX == 1400)
		EPoint = BPoint - (WinSizeX / 6);
	else if (WinSizeX == 1366 || WinSizeX == 1600 || WinSizeX == 1920)
		EPoint = BPoint - (WinSizeX / 7);
	else
		EPoint = BPoint - (WinSizeX / 8);

	if (QuestLv150A_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_150A;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size;
	}

	if (QuestLv150B_State && QuestLv150B_State < 6)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_150B;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size2;
	}

	if (QuestStart_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_START;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size3;
	}

	if (QuestBota_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_BOTA;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size5;
	}

	if (QuestAmuleto_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_AMULETO;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size6;
	}

	// QUEST DE TRAJE
	if (QuestTraje_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_TRAJE;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size4;
	}

	if (QuestLv155A_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_155A;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size7;
	}

	if (QuestLv160A_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_160A;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size8;
	}

	if (QuestLv160B_State == 1)
	{
		if (MouseAction(EPoint, wy, 264, 24))
		{
			QuestCode = QUESTID_160B;
			cMessageBox.ShowMessage3(MESSAGE_CANCEL_QUEST, "Desafio");
		}

		wy += 25 + Size9;
	}
}

int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);

void Quest::UpdaterProgressOnServer(rsPLAYINFO* Player, smCHAR* Mob, DWORD Code)
{
	if (Player->Position.Area == 47)
	{
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_150A);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int Type = 0;
					SQL::GetInstance()->GetDataValue(1, &Type);

					if (Type == 1)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 2000", Player->szName, QUESTID_150A);
						SQL::GetInstance()->Execute(szQuery);
					}

					if (Type == 0 && Code == smTRANSCODE_ADDEXP)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1000", Player->szName, QUESTID_150A);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
	}

	if (Player->Position.Area == 50)
	{
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_155A);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int Type = 0;
					SQL::GetInstance()->GetDataValue(1, &Type);
					if (Type == 1)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1000", Player->szName, QUESTID_155A);
						SQL::GetInstance()->Execute(szQuery);
					}

					if (Type == 0 && Code == smTRANSCODE_ADDEXP)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 350", Player->szName, QUESTID_155A);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
	}

	if (Player->Position.Area == 51)
	{
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_160B);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int Type = 0;
					SQL::GetInstance()->GetDataValue(1, &Type);
					if (Type == 1)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1500", Player->szName, QUESTID_160B);
						SQL::GetInstance()->Execute(szQuery);
					}

					if (Type == 0 && Code == smTRANSCODE_ADDEXP)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 500", Player->szName, QUESTID_160B);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
	}

	DWORD MobCode = Mob->smCharInfo.wPlayClass[0] + 65536;

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT Character FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_START);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				if (MobCode == 90006)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 50", Player->szName, QUESTID_START);
					SQL::GetInstance()->Execute(szQuery);
				}
				else if (MobCode == 90007)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param2=Param2+1 WHERE [Character]='%s' AND [Code]=%d AND [Param2] < 20", Player->szName, QUESTID_START);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT Character FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_BOTA);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				if (MobCode == 90022)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 100", Player->szName, QUESTID_BOTA);
					SQL::GetInstance()->Execute(szQuery);
				}
				else if (MobCode == 90023)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param2=Param2+1 WHERE [Character]='%s' AND [Code]=%d AND [Param2] < 150", Player->szName, QUESTID_BOTA);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT Character FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_AMULETO);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				if (MobCode == 90024)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 300", Player->szName, QUESTID_AMULETO);
					SQL::GetInstance()->Execute(szQuery);
				}
				else if (MobCode == 90025)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param2=Param2+1 WHERE [Character]='%s' AND [Code]=%d AND [Param2] < 250", Player->szName, QUESTID_AMULETO);
					SQL::GetInstance()->Execute(szQuery);
				}
				//else if (MobCode == 90026)
				//{
				//	wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param3=Param3+1 WHERE [Character]='%s' AND [Code]=%d AND [Param2] < 700", Player->szName, QUESTID_AMULETO);
				//	SQL::GetInstance()->Execute(szQuery);
				//}
				//else if (MobCode == 90027)
				//{
				//	wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param4=Param4+1 WHERE [Character]='%s' AND [Code]=%d AND [Param2] < 800", Player->szName, QUESTID_AMULETO);
				//	SQL::GetInstance()->Execute(szQuery);
				//}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	// QUEST DE TRAJE

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT Character FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_TRAJE);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				if (MobCode == 90020)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 100", Player->szName, QUESTID_TRAJE);
					SQL::GetInstance()->Execute(szQuery);
				}
				else if (MobCode == 90021)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param2=Param2+1 WHERE [Character]='%s' AND [Code]=%d AND [Param2] < 70", Player->szName, QUESTID_TRAJE);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_160A);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				int Type = 0;
				SQL::GetInstance()->GetDataValue(1, &Type);

				switch (Type)
				{
				case 0:
					if (MobCode == 90008)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 50", Player->szName, QUESTID_160A);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				case 1:
					if (MobCode == 90009)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 50", Player->szName, QUESTID_160A);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				case 2:
					if (MobCode == 90010)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 50", Player->szName, QUESTID_160A);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				case 3:
					if (MobCode == 90011)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 50", Player->szName, QUESTID_160A);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT State FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d", Player->szName, QUESTID_150B);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				int State = 0;
				SQL::GetInstance()->GetDataValue(1, &State);

				switch (State)
				{
				case 1:
					if (MobCode == 90001)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1", Player->szName, QUESTID_150B);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				case 2:
					if (MobCode == 90002)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1", Player->szName, QUESTID_150B);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				case 3:
					if (MobCode == 90003)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1", Player->szName, QUESTID_150B);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				case 4:
					if (MobCode == 90004)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1", Player->szName, QUESTID_150B);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				case 5:
					if (MobCode == 90005)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param1=Param1+1 WHERE [Character]='%s' AND [Code]=%d AND [Param1] < 1", Player->szName, QUESTID_150B);
						SQL::GetInstance()->Execute(szQuery);
					}
					break;
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Quest::UpdaterProgressOnClient(smCHAR* Mob, DWORD Code)
{
	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 47)
	{
		if (QuestLv150A_State == 1)
		{
			if (QuestLv150A_Type == 0 && Code == smTRANSCODE_ADDEXP)
			{
				if (QuestLv150A_Param < 1000)
				{
					QuestLv150A_Param++;
				}
			}
			else if (QuestLv150A_Type == 1)
			{
				if (QuestLv150A_Param < 2000)
				{
					QuestLv150A_Param++;
				}
			}
		}
	}

	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 50)
	{
		if (QuestLv155A_State == 1)
		{
			if (QuestLv155A_Type == 0 && Code == smTRANSCODE_ADDEXP)
			{
				if (QuestLv155A_Param < 350)
				{
					QuestLv155A_Param++;
				}
			}
			else if (QuestLv155A_Type == 1)
			{
				if (QuestLv155A_Param < 1000)
				{
					QuestLv155A_Param++;
				}
			}
		}
	}

	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 51)
	{
		if (QuestLv160B_State == 1)
		{
			if (QuestLv160B_Type == 0 && Code == smTRANSCODE_ADDEXP)
			{
				if (QuestLv160B_Param < 500)
				{
					QuestLv160B_Param++;
				}
			}
			else if (QuestLv160B_Type == 1)
			{
				if (QuestLv160B_Param < 1500)
				{
					QuestLv160B_Param++;
				}
			}
		}
	}

	DWORD MobCode = Mob->smCharInfo.wPlayClass[0] + 65536;

	if (QuestLv160A_State == 1)
	{
		if (QuestLv160A_Param1 < 50)
		{
			switch (QuestLv160A_Type)
			{
			case 0:
				if (MobCode == 90008)
				{
					QuestLv160A_Param1++;
				}
				break;
			case 1:
				if (MobCode == 90009)
				{
					QuestLv160A_Param1++;
				}
				break;
			case 2:
				if (MobCode == 90010)
				{
					QuestLv160A_Param1++;
				}
				break;
			case 3:
				if (MobCode == 90011)
				{
					QuestLv160A_Param1++;
				}
				break;
			}
		}
	}

	if (QuestStart_State)
	{
		if (QuestStart_Param1 < 50)
		{
			if (MobCode == 90006)
			{
				QuestStart_Param1++;
			}
		}

		if (QuestStart_Param2 < 20)
		{
			if (MobCode == 90007)
			{
				QuestStart_Param2++;
			}
		}
	}

	if (QuestBota_State)
	{
		if (QuestBota_Param1 < 100)
		{
			if (MobCode == 90022)
			{
				QuestBota_Param1++;
			}
		}

		if (QuestBota_Param2 < 150)
		{
			if (MobCode == 90023)
			{
				QuestBota_Param2++;
			}
		}
	}

	if (QuestAmuleto_State)
	{
		if (QuestAmuleto_Param1 < 300)
		{
			if (MobCode == 90024)
			{
				QuestAmuleto_Param1++;
			}
		}

		if (QuestAmuleto_Param2 < 250)
		{
			if (MobCode == 90025)
			{
				QuestAmuleto_Param2++;
			}
		}

		//if (QuestAmuleto_Param3 < 700)
		//{
		//	if (MobCode == 90026)
		//	{
		//		QuestAmuleto_Param3++;
		//	}
		//}

		//if (QuestAmuleto_Param4 < 800)
		//{
		//	if (MobCode == 90027)
		//	{
		//		QuestAmuleto_Param4++;
		//	}
		//}
	}

	if (QuestTraje_State)
	{
		if (QuestTraje_Param1 < 100)
		{
			if (MobCode == 90020)
			{
				QuestTraje_Param1++;
			}
		}

		if (QuestTraje_Param2 < 70)
		{
			if (MobCode == 90021)
			{
				QuestTraje_Param2++;
			}
		}
	}

	switch (QuestLv150B_State)
	{
	case 1:
		if (!QuestLv150B_Param)
		{
			if (MobCode == 90001)
			{
				QuestLv150B_Param++;
			}
		}
		break;
	case 2:
		if (!QuestLv150B_Param)
		{
			if (MobCode == 90002)
			{
				QuestLv150B_Param++;
			}
		}
		break;
	case 3:
		if (!QuestLv150B_Param)
		{
			if (MobCode == 90003)
			{
				QuestLv150B_Param++;
			}
		}
		break;
	case 4:
		if (!QuestLv150B_Param)
		{
			if (MobCode == 90004)
			{
				QuestLv150B_Param++;
			}
		}
		break;
	case 5:
		if (!QuestLv150B_Param)
		{
			if (MobCode == 90005)
			{
				QuestLv150B_Param++;
			}
		}
		break;
	}
}

void Quest::Updater(EQuestID Quest)
{
	switch (Quest)
	{
	case QUESTID_START:
		if (QuestStart_State == 0)
		{
			QuestStart_State = 1;
			QuestStart_Param1 = 0;
			QuestStart_Param2 = 0;
		}
		if (QuestStart_State == 1 && QuestStart_Param1 == 50 && QuestStart_Param2 == 20)
		{
			QuestStart_State = 2;
			QuestStart_Param1 = 0;
			QuestStart_Param2 = 0;
		}
		break;

	case QUESTID_BOTA:
		if (QuestBota_State == 0 && lpCurPlayer->smCharInfo.Level >= 115)
		{
			QuestBota_State = 1;
			QuestBota_Param1 = 0;
			QuestBota_Param2 = 0;
		}
		if (QuestBota_State == 1 && QuestBota_Param1 == 100 && QuestBota_Param2 == 150)
		{
			QuestBota_State = 2;
			QuestBota_Param1 = 0;
			QuestBota_Param2 = 0;
		}
		break;

	case QUESTID_AMULETO:
		if (QuestAmuleto_State == 0 && lpCurPlayer->smCharInfo.Level >= 122)
		{
			QuestAmuleto_State = 1;
			QuestAmuleto_Param1 = 0;
			QuestAmuleto_Param2 = 0;
			/*	QuestAmuleto_Param3 = 0;
				QuestAmuleto_Param4 = 0;*/
		}
		if (QuestAmuleto_State == 1 && QuestAmuleto_Param1 == 300 && QuestAmuleto_Param2 == 250 /*&& QuestAmuleto_Param3 >= 700 && QuestAmuleto_Param4 >= 800*/)
		{
			QuestAmuleto_State = 2;
			QuestAmuleto_Param1 = 0;
			QuestAmuleto_Param2 = 0;
			/*	QuestAmuleto_Param3 = 0;
				QuestAmuleto_Param4 = 0;*/
		}
		break;

	case QUESTID_TRAJE:
		if (QuestTraje_State == 0)
		{
			QuestTraje_State = 1;
			QuestTraje_Param1 = 0;
			QuestTraje_Param2 = 0;
		}
		if (QuestTraje_State == 1 && QuestTraje_Param1 == 100 && QuestTraje_Param2 == 70)
		{
			QuestTraje_State = 2;
			QuestTraje_Param1 = 0;
			QuestTraje_Param2 = 0;
		}
		break;

	case QUESTID_160A:
		if (QuestLv160A_State == 0 && lpCurPlayer->smCharInfo.Exp >= 1000000000)
		{
			QuestLv160A_State = 1;
			QuestLv160A_Param1 = 0;
			//QuestLv160A_Param2 = 0;
		}
		else if (QuestLv155A_State == 2 && GetPlayTime_T() > QuestLv160A_Time && lpCurPlayer->smCharInfo.Level >= 125)
		{
			QuestLv160A_State = 1;
			QuestLv160A_Param1 = 0;
			//QuestLv160A_Param2 = 0;
		}
		else if (QuestLv160A_State == 1)
		{
			if (QuestLv160A_Param1 == 50 /*&& QuestLv160A_Param2 == 10*/)
			{
				QuestLv160A_State = 2;
				QuestLv160A_Time = GetPlayTime_T() + 60 * 60 * 24;
			}
		}
		break;

	case QUESTID_155A:
		if (QuestLv155A_State == 0 && lpCurPlayer->smCharInfo.Level >= 155 && lpCurPlayer->smCharInfo.Level < 160)
		{
			QuestLv155A_State = 1;
			QuestLv155A_Param = 0;
		}
		else if (QuestLv155A_State == 2 && lpCurPlayer->smCharInfo.Level >= 155 && lpCurPlayer->smCharInfo.Level < 160)
		{
			QuestLv155A_State = 1;
			QuestLv155A_Param = 0;
		}
		else if (QuestLv155A_State == 1)
		{
			if (QuestLv155A_Type == 0)
			{
				if (QuestLv155A_Param >= 350)
				{
					QuestLv155A_State = 2;
					QuestLv155A_Time = GetPlayTime_T() + 60 * 60 * 5;

					if (sinChar->Level >= 155 && sinChar->Level < 160)
					{
						CheckCharForm();
						sinChar->Level++;
						SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
						CodeXorCharInfo_Exp();
						ReformCharForm();
						haCastleSkillUseFlag = 1;
						SendPlayUpdateInfo();
					}
				}
			}
			else if (QuestLv155A_Type == 1)
			{
				if (QuestLv155A_Param >= 1000)
				{
					QuestLv155A_State = 2;
					QuestLv155A_Time = GetPlayTime_T() + 60 * 60 * 5;

					if (sinChar->Level >= 155 && sinChar->Level < 160)
					{
						CheckCharForm();
						sinChar->Level++;
						SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
						CodeXorCharInfo_Exp();
						ReformCharForm();
						haCastleSkillUseFlag = 1;
						SendPlayUpdateInfo();
					}
				}
			}
		}
		break;

	case QUESTID_160B:
		if (QuestLv160B_State == 0 && lpCurPlayer->smCharInfo.Level >= 160 && lpCurPlayer->smCharInfo.Level < 165)
		{
			QuestLv160B_State = 1;
			QuestLv160B_Param = 0;
		}
		else if (QuestLv160B_State == 2 && lpCurPlayer->smCharInfo.Level >= 160 && lpCurPlayer->smCharInfo.Level < 165)
		{
			QuestLv160B_State = 1;
			QuestLv160B_Param = 0;
		}
		else if (QuestLv160B_State == 1)
		{
			if (QuestLv160B_Type == 0)
			{
				if (QuestLv160B_Param >= 500)
				{
					QuestLv160B_State = 2;
					QuestLv160B_Time = GetPlayTime_T() + 60 * 60 * 5;

					if (sinChar->Level >= 160 && sinChar->Level < 165)
					{
						CheckCharForm();
						sinChar->Level++;
						SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
						CodeXorCharInfo_Exp();
						ReformCharForm();
						haCastleSkillUseFlag = 1;
						SendPlayUpdateInfo();
					}
				}
			}
			else if (QuestLv160B_Type == 1)
			{
				if (QuestLv160B_Param >= 1500)
				{
					QuestLv160B_State = 2;
					QuestLv160B_Time = GetPlayTime_T() + 60 * 60 * 5;

					if (sinChar->Level >= 160 && sinChar->Level < 165)
					{
						CheckCharForm();
						sinChar->Level++;
						SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
						CodeXorCharInfo_Exp();
						ReformCharForm();
						haCastleSkillUseFlag = 1;
						SendPlayUpdateInfo();
					}
				}
			}
		}
		break;

	case QUESTID_150A:
		if (QuestLv150A_State == 0 && lpCurPlayer->smCharInfo.Level >= 150 && lpCurPlayer->smCharInfo.Level < 155)
		{
			QuestLv150A_State = 1;
			QuestLv150A_Param = 0;
		}
		else if (QuestLv150A_State == 2 && lpCurPlayer->smCharInfo.Level >= 150 && lpCurPlayer->smCharInfo.Level < 155)
		{
			QuestLv150A_State = 1;
			QuestLv150A_Param = 0;
		}
		else if (QuestLv150A_State == 1)
		{
			if (QuestLv150A_Type == 0)
			{
				if (QuestLv150A_Param >= 1000)
				{
					QuestLv150A_State = 2;
					QuestLv150A_Time = GetPlayTime_T() + 60 * 60 * 24;

					if (sinChar->Level >= 150 && sinChar->Level < 155)
					{
						CheckCharForm();
						sinChar->Level++;
						SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
						CodeXorCharInfo_Exp();
						ReformCharForm();
						haCastleSkillUseFlag = 1;
						SendPlayUpdateInfo();
					}
				}
			}
			else
			{
				if (QuestLv150A_Param >= 2000)
				{
					QuestLv150A_State = 2;
					QuestLv150A_Time = GetPlayTime_T() + 60 * 60 * 24;

					if (sinChar->Level >= 150 && sinChar->Level < 125)
					{
						CheckCharForm();
						sinChar->Level++;
						SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
						CodeXorCharInfo_Exp();
						ReformCharForm();
						haCastleSkillUseFlag = 1;
						SendPlayUpdateInfo();
					}
				}
			}
		}
		break;
	case QUESTID_150B:
		if (QuestLv150B_State == 0 && lpCurPlayer->smCharInfo.Level >= 125)
		{
			QuestLv150B_State = 1;
		}
		else if (QuestLv150B_State == 6 && GetPlayTime_T() > QuestLv150B_Time && lpCurPlayer->smCharInfo.Level >= 125)
		{
			QuestLv150B_State = 1;
			QuestLv150B_Param = 0;
		}
		else if (QuestLv150B_State == 1)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 2;
			}
		}
		else if (QuestLv150B_State == 2)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 3;
			}
		}
		else if (QuestLv150B_State == 3)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 4;
			}
		}
		else if (QuestLv150B_State == 4)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 5;
			}
		}
		else if (QuestLv150B_State == 5)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 6;
				QuestLv150B_Time = GetPlayTime_T() + 60 * 60 * 24;
			}
		}
		break;
	}
}

#define MAX_AWARD 53

void Quest::CancelProgress(rsPLAYINFO* Player, smTRANS_COMMAND* packet)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
		SQL::GetInstance()->Execute(szQuery);
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Quest::AnalyzeProgress(rsPLAYINFO* Player, smTRANS_COMMAND* packet)
{
	switch (packet->WParam)
	{
	case QUESTID_START:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Param1,Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Param1 = 0;
					int Param2 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Param1);
					SQL::GetInstance()->GetDataValue(3, &Param2);

					if (State == 1 && Param1 == 50 && Param2 == 20)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2 WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);
						rsSendMoneyToUser(Player, 10000000);
						LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, 0)", Player->szName, packet->WParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;

	case QUESTID_BOTA:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Param1,Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Param1 = 0;
					int Param2 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Param1);
					SQL::GetInstance()->GetDataValue(3, &Param2);

					if (State == 1 && Param1 == 100 && Param2 == 150)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2 WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);

						switch (Player->smCharInfo.JOB_CODE)
						{
						case JOBCODE_FIGHTER:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_FIGHTER); // Ok
							break;
						case JOBCODE_MECHANICIAN:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_MECHANICIAN); // Ok
							break;
						case JOBCODE_ARCHER:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_ARCHER); // Ok
							break;
						case JOBCODE_PIKEMAN:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_PIKEMAN); // Ok
							break;
						case JOBCODE_ATALANTA:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_ATALANTA); // Ok
							break;
						case JOBCODE_KNIGHT:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_KNIGHT); // Ok
							break;
						case JOBCODE_MAGICIAN:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_MAGICIAN); // Ok
							break;
						case JOBCODE_PRIESTESS:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_PRIESTESS); // Ok
							break;
						case JOBCODE_ASSASSINE:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_ASSASSINE); // Ok
							break;
						case JOBCODE_SHAMAN:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_SHAMAN); // Ok
							break;
						case JOBCODE_MARTIAL:
							PremioQuest(Player, (sinDB1 | sin32), JOBCODE_MARTIAL); // Ok
							break;
						}
						LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, 0)", Player->szName, packet->WParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;

	case QUESTID_AMULETO:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Param1,Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Param1 = 0;
					int Param2 = 0;
					int Param3 = 0;
					int Param4 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Param1);
					SQL::GetInstance()->GetDataValue(3, &Param2);
					/*			SQL::GetInstance()->GetDataValue(4, &Param3);
								SQL::GetInstance()->GetDataValue(5, &Param4);*/

					if (State == 1 && Param1 == 300 && Param2 == 250/* && Param3 >= 700 && Param4 >= 800*/)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2 WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);

						switch (Player->smCharInfo.JOB_CODE)
						{
						case JOBCODE_FIGHTER:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_FIGHTER); // Ok
							break;
						case JOBCODE_MECHANICIAN:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_MECHANICIAN); // Ok
							break;
						case JOBCODE_ARCHER:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_ARCHER); // Ok
							break;
						case JOBCODE_PIKEMAN:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_PIKEMAN); // Ok
							break;
						case JOBCODE_ATALANTA:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_ATALANTA); // Ok
							break;
						case JOBCODE_KNIGHT:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_KNIGHT); // Ok
							break;
						case JOBCODE_MAGICIAN:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_MAGICIAN); // Ok
							break;
						case JOBCODE_PRIESTESS:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_PRIESTESS); // Ok
							break;
						case JOBCODE_ASSASSINE:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_ASSASSINE); // Ok
							break;
						case JOBCODE_SHAMAN:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_SHAMAN); // Ok
							break;
						case JOBCODE_MARTIAL:
							PremioQuest(Player, (sinOA1 | sin29), JOBCODE_MARTIAL); // Ok
							break;
						}
						LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, 0)", Player->szName, packet->WParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;

	case QUESTID_TRAJE:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Param1,Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Param1 = 0;
					int Param2 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Param1);
					SQL::GetInstance()->GetDataValue(3, &Param2);

					if (State == 1 && Param1 == 100 && Param2 == 70)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2 WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);

						switch (Player->smCharInfo.JOB_CODE)
						{
						case JOBCODE_FIGHTER:
							rsPutItem(Player, sinCA5 | sin10); // Ok
							break;
						case JOBCODE_MECHANICIAN:
							rsPutItem(Player, sinCA5 | sin10); // OK
							break;
						case JOBCODE_ARCHER:
							rsPutItem(Player, sinCA5 | sin12); // OK
							break;
						case JOBCODE_PIKEMAN:
							rsPutItem(Player, sinCA5 | sin10); // OK
							break;
						case JOBCODE_ATALANTA:
							rsPutItem(Player, sinCA5 | sin12); // OK
							break;
						case JOBCODE_KNIGHT:
							rsPutItem(Player, sinCA5 | sin10); //OK
							break;
						case JOBCODE_MAGICIAN:
							rsPutItem(Player, sinCA6 | sin10); // OK
							break;
						case JOBCODE_PRIESTESS:
							rsPutItem(Player, sinCA6 | sin12); // OK
							break;
						case JOBCODE_ASSASSINE:
							rsPutItem(Player, sinCA5 | sin12); // OK
							break;
						case JOBCODE_SHAMAN:
							rsPutItem(Player, sinCA6 | sin10); // OK
							break;
						case JOBCODE_MARTIAL:
							rsPutItem(Player, sinCA5 | sin12); // OK
							break;
						}
						LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, 0)", Player->szName, packet->WParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;
	case QUESTID_150A:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State,Param1,Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Param1 = 0;
					int Type = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Param1);
					SQL::GetInstance()->GetDataValue(3, &Type);

					if (Type == 0)
					{
						if (State == 2)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0,Type=%d  WHERE [Character]='%s' AND [Code]=%d", packet->EParam, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
						}
						else if (State == 1 && Param1 >= 1000)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2 WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
							Player->spEXP_Out = ExpLevelTable[Player->smCharInfo.Level - 1];
							LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
						}
					}
					else if (Type == 1)
					{
						if (State == 2)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0,Type=%d  WHERE [Character]='%s' AND [Code]=%d", packet->EParam, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
						}
						else if (State == 1 && Param1 >= 2000)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2 WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
							Player->spEXP_Out = ExpLevelTable[Player->smCharInfo.Level - 1];
							LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
						}
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, %d)", Player->szName, packet->WParam, packet->EParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;
	case QUESTID_150B:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Time, Param1 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Time = 0;
					int Param1 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Time);
					SQL::GetInstance()->GetDataValue(3, &Param1);

					if (State == 6 && Time < tServerTime)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0  WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);
					}
					else if (State == 5 && Param1 == 1)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=6,Time=%d WHERE [Character]='%s' AND [Code]=%d", (int)tServerTime + 60 * 60 * 24, Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);

						DWORD AwardList[MAX_AWARD] = { sinBI3 | sin01 , sinBI3 | sin07 , sinBI3 | sin13, sinBI3 | sin02, sinBI3 | sin08, sinBI3 | sin14, sinBI3 | sin03, sinBI3 | sin09,
												sinBI3 | sin15, sinBI3 | sin04, sinBI3 | sin10, sinBI3 | sin16, sinBI3 | sin05, sinBI3 | sin11, sinBI3 | sin17, sinBI2 | sin58, sinBI2 | sin59,
												sinBI2 | sin57, sinBI2 | sin86, sinBI2 | sin87, sinBI2 | sin88, sinBI3 | sin19, sinBI3 | sin13, sinCA5 | sin22, sinCA5 | sin24, sinOA1 | sin33,
												sinOR2 | sin31, sinSE1 | sin05, sinOS1 | sin18, sinWA1 | sin30, sinWC1 | sin29, sinWH1 | sin31, sinWM1 | sin31, sinWS1 | sin31, sinWS2 | sin33, sinWP1 | sin30,
												sinWT1 | sin30, sinDA3 | sin02, sinDS1 | sin28, sinDG1 | sin26, sinDB1 | sin26, sinOA2 | sin26, sinBI1 | sin65, sinBI1 | sin66, sinBI1 | sin67, sinBI1 | sin68
												, sinBI1 | sin85, sinBI1 | sin61, sinBI2 | sin58, sinBI2 | sin59, sinBI1 | sin14, sinBI1 | sin29, sinBI1 | sin92 };

						int Rand = rand() % MAX_AWARD;
						rsPutItem(Player, AwardList[Rand]);
						LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
					}
					else if (State && State < 5 && Param1 == 1)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=State + 1,Param1=0 WHERE [Character]='%s' AND [Code]=%d", Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, 0)", Player->szName, packet->WParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;
	case QUESTID_155A:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Time, Param1, Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Time = 0;
					int Param1 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Time);
					SQL::GetInstance()->GetDataValue(3, &Param1);
					SQL::GetInstance()->GetDataValue(4, &Type);

					if (Type == 0)
					{
						if (State == 2)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0,Type=%d  WHERE [Character]='%s' AND [Code]=%d", packet->EParam, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
						}

						if (State == 1 && Param1 >= 350)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2,Time=%d WHERE [Character]='%s' AND [Code]=%d", (int)tServerTime + 60 * 60 * 5, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
							Player->spEXP_Out = ExpLevelTable[Player->smCharInfo.Level - 1];
							LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
						}
					}
					else if (Type == 1)

					{
						if (State == 2)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0,Type=%d  WHERE [Character]='%s' AND [Code]=%d", packet->EParam, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
						}

						if (State == 1 && Param1 >= 1000)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2,Time=%d WHERE [Character]='%s' AND [Code]=%d", (int)tServerTime + 60 * 60 * 5, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
							Player->spEXP_Out = ExpLevelTable[Player->smCharInfo.Level - 1];
							LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
						}
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, %d)", Player->szName, packet->WParam, packet->EParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;

	case QUESTID_160B:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Time, Param1, Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Time = 0;
					int Param1 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Time);
					SQL::GetInstance()->GetDataValue(3, &Param1);
					SQL::GetInstance()->GetDataValue(4, &Type);

					if (Type == 0)
					{
						if (State == 2)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0,Type=%d  WHERE [Character]='%s' AND [Code]=%d", packet->EParam, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
						}

						if (State == 1 && Param1 >= 500)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2,Time=%d WHERE [Character]='%s' AND [Code]=%d", (int)tServerTime + 60 * 60 * 5, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
							Player->spEXP_Out = ExpLevelTable[Player->smCharInfo.Level - 1];
							LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
						}
					}
					else if (Type == 1)

					{
						if (State == 2)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0,Type=%d  WHERE [Character]='%s' AND [Code]=%d", packet->EParam, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
						}

						if (State == 1 && Param1 >= 1500)
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2,Time=%d WHERE [Character]='%s' AND [Code]=%d", (int)tServerTime + 60 * 60 * 5, Player->szName, packet->WParam);
							SQL::GetInstance()->Execute(szQuery);
							Player->spEXP_Out = ExpLevelTable[Player->smCharInfo.Level - 1];
							LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
						}
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, %d)", Player->szName, packet->WParam, packet->EParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;

	case QUESTID_160A:
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[256];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT State, Time, Param1,Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, packet->WParam);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					int State = 0;
					int Time = 0;
					int Param1 = 0;
					int Param2 = 0;

					SQL::GetInstance()->GetDataValue(1, &State);
					SQL::GetInstance()->GetDataValue(2, &Time);
					SQL::GetInstance()->GetDataValue(3, &Param1);
					SQL::GetInstance()->GetDataValue(4, &Param2);

					if (State == 2 && Time < tServerTime)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=1,Param1=0,Param2=0,Type=%d  WHERE [Character]='%s' AND [Code]=%d", packet->EParam, Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);
					}

					if (State == 1 && Param1 >= 50)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET State=2,Time=%d WHERE [Character]='%s' AND [Code]=%d", (int)tServerTime + 60 * 60 * 24, Player->szName, packet->WParam);
						SQL::GetInstance()->Execute(szQuery);

						LOGEx(Player, "Quest", "%s completed QuestCode:%d", Player->szName, packet->WParam);
					}
				}
				else
				{
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Quest] ([Character],[Code],[State],[Time],[Param1],[Param2],[Param3],[Param4],[Param5],[Type]) values('%s',%d, 1, 0, 0, 0, 0, 0, 0, %d)", Player->szName, packet->WParam, packet->EParam);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
		break;
	}
}

//void Quest::AnalyzeProgress(rsPLAYINFO* Player, smTRANS_COMMAND* packet)
//{
//	switch (packet->WParam)
//	{
//	case QUESTID_START:
//		if (Player->QuestStart_State == 0)
//		{
//			Player->QuestStart_State = 1;
//			Player->QuestStart_Param1 = 0;
//			Player->QuestStart_Param2 = 0;
//		}
//		else if (Player->QuestStart_State == 1 && Player->QuestStart_Param1 == 50 && Player->QuestStart_Param2 == 20)
//		{
//			Player->QuestStart_State = 2;
//			Player->QuestStart_Param1 = 0;
//			Player->QuestStart_Param2 = 0;
//			rsSendMoneyToUser(Player, 10000000);
//		}
//		break;
//
//	case QUESTID_155A:
//		if (Player->QuestLv155A_State == 0 && Player->smCharInfo.Level >= 155 && Player->smCharInfo.Level < 160)
//		{
//			Player->QuestLv155A_State = 1;
//			Player->QuestLv155A_Param = 0;
//		}
//		else if (Player->QuestLv155A_State == 2 && tServerTime > Player->QuestLv155A_Time&& Player->smCharInfo.Level >= 155 && Player->smCharInfo.Level < 160)
//		{
//			Player->QuestLv155A_State = 1;
//			Player->QuestLv155A_Param = 0;
//		}
//		else if (Player->QuestLv155A_State == 1)
//		{
//			if (Player->QuestLv155A_Param == 2000)
//			{
//				Player->QuestLv155A_State = 2;
//				Player->QuestLv155A_Time = ((DWORD)tServerTime) + 60 * 60 * 5;
//			}
//		}
//		break;
//
//	case QUESTID_150A:
//		if (Player->QuestLv150A_State == 0 && Player->smCharInfo.Level >= 150 && Player->smCharInfo.Level < 155)
//		{
//			Player->QuestLv150A_State = 1;
//			Player->QuestLv150A_Param = 0;
//		}
//		else if (Player->QuestLv150A_State == 2 && Player->smCharInfo.Level >= 150 && Player->smCharInfo.Level < 155)
//		{
//			Player->QuestLv150A_State = 1;
//			Player->QuestLv150A_Param = 0;
//		}
//		else if (Player->QuestLv150A_State == 1)
//		{
//			if (Player->QuestLv150A_Param >= 1000)
//			{
//				Player->QuestLv150A_State = 2;
//			}
//		}
//		break;
//	case QUESTID_150B:
//
//		if (Player->QuestLv150B_State == 0 && Player->smCharInfo.Level >= 150)
//		{
//			Player->QuestLv150B_State = 1;
//		}
//		else if (Player->QuestLv150B_State == 6 && tServerTime > Player->QuestLv150B_Time&& Player->smCharInfo.Level >= 150)
//		{
//			Player->QuestLv150B_State = 1;
//			Player->QuestLv150B_Param = 0;
//		}
//		else if (Player->QuestLv150B_State == 1)
//		{
//			if (Player->QuestLv150B_Param == 1)
//			{
//				Player->QuestLv150B_Param = 0;
//				Player->QuestLv150B_State = 2;
//			}
//		}
//		else if (Player->QuestLv150B_State == 2)
//		{
//			if (Player->QuestLv150B_Param == 1)
//			{
//				Player->QuestLv150B_Param = 0;
//				Player->QuestLv150B_State = 3;
//			}
//		}
//		else if (Player->QuestLv150B_State == 3)
//		{
//			if (Player->QuestLv150B_Param == 1)
//			{
//				Player->QuestLv150B_Param = 0;
//				Player->QuestLv150B_State = 4;
//			}
//		}
//		else if (Player->QuestLv150B_State == 4)
//		{
//			if (Player->QuestLv150B_Param == 1)
//			{
//				Player->QuestLv150B_Param = 0;
//				Player->QuestLv150B_State = 5;
//			}
//		}
//		else if (Player->QuestLv150B_State == 5)
//		{
//			if (Player->QuestLv150B_Param == 1)
//			{
//				Player->QuestLv150B_Param = 0;
//				Player->QuestLv150B_State = 6;
//				Player->QuestLv150B_Time = ((DWORD)tServerTime) + 60 * 60 * 24;
//
//				DWORD AwardList[MAX_AWARD] = { sinBI3 | sin01 , sinBI3 | sin07 , sinBI3 | sin13, sinBI3 | sin02, sinBI3 | sin08, sinBI3 | sin14, sinBI3 | sin03, sinBI3 | sin09,
//					sinBI3 | sin15, sinBI3 | sin04, sinBI3 | sin10, sinBI3 | sin16, sinBI3 | sin05, sinBI3 | sin11, sinBI3 | sin17, sinBI2 | sin58, sinBI2 | sin59,
//					sinBI2 | sin57, sinBI2 | sin86, sinBI2 | sin87, sinBI2 | sin88, sinBI3 | sin19, sinBI3 | sin13, sinCA5 | sin22, sinCA5 | sin24, sinOA1 | sin33,
//					sinOR2 | sin31, sinSE1 | sin05, sinOS1 | sin18, sinWA1 | sin30, sinWC1 | sin29, sinWH1 | sin31, sinWM1 | sin31, sinWS1 | sin31, sinWS2 | sin33, sinWP1 | sin30,
//					sinWT1 | sin30, sinDA3 | sin02, sinDS1 | sin28, sinDG1 | sin26, sinDB1 | sin26, sinOA2 | sin26, sinBI1 | sin65, sinBI1 | sin66, sinBI1 | sin67, sinBI1 | sin68
//					, sinBI1 | sin85, sinBI1 | sin61, sinBI2 | sin58, sinBI2 | sin59, sinBI1 | sin14, sinBI1 | sin29, sinBI1 | sin92 };
//
//				int Rand = rand() % MAX_AWARD;
//				rsPutItem(Player, AwardList[Rand]);
//			}
//		}
//
//		break;
//	}
//}

void Quest::SendProgress(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		PACKET_QUEST packet;
		ZeroMemory(&packet, sizeof(PACKET_QUEST));
		packet.size = sizeof(PACKET_QUEST);
		packet.code = smTRANSCODE_PROGRESS_QUEST;

		wsprintf(szQuery, "SELECT State, Param1, Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_START);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestStart_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestStart_Param1);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestStart_Param2);
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_BOTA);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestBota_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestBota_Param1);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestBota_Param2);
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_AMULETO);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestAmuleto_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestAmuleto_Param1);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestAmuleto_Param2);
				/*SQL::GetInstance()->GetDataValue(4, &packet.QuestAmuleto_Param3);
				SQL::GetInstance()->GetDataValue(5, &packet.QuestAmuleto_Param4);*/
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Param2 FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_TRAJE);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestTraje_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestTraje_Param1);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestTraje_Param2);
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Time, Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_150A);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestLv150A_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestLv150A_Param);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestLv150A_Time);
				SQL::GetInstance()->GetDataValue(4, &packet.QuestLv150A_Type);
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Time FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_150B);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestLv150B_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestLv150B_Param);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestLv150B_Time);
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Time, Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_155A);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestLv155A_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestLv155A_Param);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestLv155A_Time);
				SQL::GetInstance()->GetDataValue(4, &packet.QuestLv155A_Type);
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Param2, Time, Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_160A);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestLv160A_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestLv160A_Param1);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestLv160A_Param2);
				SQL::GetInstance()->GetDataValue(4, &packet.QuestLv160A_Time);
				SQL::GetInstance()->GetDataValue(5, &packet.QuestLv160A_Type);
			}
		}

		wsprintf(szQuery, "SELECT State, Param1, Time, Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d ", Player->szName, QUESTID_160B);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.QuestLv160B_State);
				SQL::GetInstance()->GetDataValue(2, &packet.QuestLv160B_Param);
				SQL::GetInstance()->GetDataValue(3, &packet.QuestLv160B_Time);
				SQL::GetInstance()->GetDataValue(4, &packet.QuestLv160B_Type);
			}
		}

		Player->lpsmSock->Send((char*)&packet, packet.size, true);
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Quest::RecvProgress(PACKET_QUEST* packet)
{
	QuestStart_State = packet->QuestStart_State;
	QuestStart_Param1 = packet->QuestStart_Param1;
	QuestStart_Param2 = packet->QuestStart_Param2;
	QuestBota_State = packet->QuestBota_State;
	QuestBota_Param1 = packet->QuestBota_Param1;
	QuestBota_Param2 = packet->QuestBota_Param2;
	QuestAmuleto_State = packet->QuestAmuleto_State;
	QuestAmuleto_Param1 = packet->QuestAmuleto_Param1;
	QuestAmuleto_Param2 = packet->QuestAmuleto_Param2;
	//QuestAmuleto_Param3 = packet->QuestAmuleto_Param3;
	//QuestAmuleto_Param4 = packet->QuestAmuleto_Param4;
	QuestTraje_State = packet->QuestTraje_State;
	QuestTraje_Param1 = packet->QuestTraje_Param1;
	QuestTraje_Param2 = packet->QuestTraje_Param2;
	QuestLv150A_State = packet->QuestLv150A_State;
	QuestLv150A_Param = packet->QuestLv150A_Param;
	QuestLv150A_Time = packet->QuestLv150A_Time;
	QuestLv150A_Type = packet->QuestLv150A_Type;
	QuestLv150B_State = packet->QuestLv150B_State;
	QuestLv150B_Param = packet->QuestLv150B_Param;
	QuestLv150B_Time = packet->QuestLv150B_Time;
	QuestLv155A_State = packet->QuestLv155A_State;
	QuestLv155A_Param = packet->QuestLv155A_Param;
	QuestLv155A_Time = packet->QuestLv155A_Time;
	QuestLv155A_Type = packet->QuestLv155A_Type;
	QuestLv160A_State = packet->QuestLv160A_State;
	QuestLv160A_Param1 = packet->QuestLv160A_Param1;
	//QuestLv160A_Param2 = packet->QuestLv160A_Param2;
	QuestLv160A_Time = packet->QuestLv160A_Time;
	QuestLv160A_Type = packet->QuestLv160A_Type;
	QuestLv160B_State = packet->QuestLv160B_State;
	QuestLv160B_Param = packet->QuestLv160B_Param;
	QuestLv160B_Time = packet->QuestLv160B_Time;
	QuestLv160B_Type = packet->QuestLv160B_Type;
}

void Quest::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void Quest::DrawNPC()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[4], WinX, WinY, 561, 438);
		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Desafio]", 10, &size);
		dsTextLineOut(WinX + 280 - size.cx / 2, WinY + 40, "[Desafio]", 10);
		FontType = 0;
		dsTextLineOut(WinX + 60, WinY + 80, szBufferTextWindow, strlen(szBufferTextWindow));

		if ((QuestCode == QUESTID_150A && QuestLv150A_State != 1) || (QuestCode == QUESTID_155A && QuestLv155A_State != 1) || (QuestCode == QUESTID_160B && QuestLv160B_State != 1))
		{
			if (!Type)
				DrawImage(Images[10], WinX + 200, WinY + 380, 16, 16);
			else
				DrawImage(Images[9], WinX + 200, WinY + 380, 16, 16);

			dsTextLineOut(WinX + 220, WinY + 380, "SOLO", 5);

			if (Type)
				DrawImage(Images[10], WinX + 300, WinY + 380, 16, 16);
			else
				DrawImage(Images[9], WinX + 300, WinY + 380, 16, 16);

			dsTextLineOut(WinX + 320, WinY + 380, "PARTY", 5);
		}

		if (MouseAction(WinX + 200, WinY + 400, 93, 23))
			DrawImage(Images[6], WinX + 200, WinY + 400, 93, 23);
		else
			DrawImage(Images[5], WinX + 200, WinY + 400, 93, 23);

		if (MouseAction(WinX + 300, WinY + 400, 93, 23))
			DrawImage(Images[8], WinX + 300, WinY + 400, 93, 23);
		else
			DrawImage(Images[7], WinX + 300, WinY + 400, 93, 23);
	}
}

void Quest::OpenNPC(DWORD Code)
{
	int Flag = 0;
	Type = 0;
	switch (Code)
	{
	case NPC_SEA_ABYSS:
		LoadTextFromFile("game\\npc\\sea_abyss.txt");
		Flag++;
		break;
	case NPC_ANCIENT_WEAPON:
		LoadTextFromFile("game\\npc\\ancient_weapon.txt");
		Flag++;
		break;
	case NPC_HEART_FIRE:
		LoadTextFromFile("game\\npc\\heart_fire.txt");
		Flag++;
		break;

	case QUESTID_START:
		switch (QuestStart_State)
		{
		case 0:
			LoadTextFromFile("game\\quest\\start_begin.txt");
			Flag++;
			break;
		case 1:
			if (QuestStart_Param1 < 50 || QuestStart_Param2 < 20)
				LoadTextFromFile("game\\quest\\start_progress.txt");
			else
				LoadTextFromFile("game\\quest\\start_end.txt");
			Flag++;
			break;
		}
		break;

	case QUESTID_BOTA:
		switch (QuestBota_State)
		{
		case 0:
			if (lpCurPlayer->smCharInfo.Level >= 115)
			{
				LoadTextFromFile("game\\quest\\Bota_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		case 1:
			if (QuestBota_Param1 < 100 || QuestBota_Param2 < 150)
				LoadTextFromFile("game\\quest\\Bota_progress.txt");
			else
				LoadTextFromFile("game\\quest\\Bota_end.txt");
			Flag++;
			break;
		}
		break;

	case QUESTID_AMULETO:
		switch (QuestAmuleto_State)
		{
		case 0:
			if (lpCurPlayer->smCharInfo.Level >= 122)
			{
				LoadTextFromFile("game\\quest\\Amuleto_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		case 1:
			if (QuestAmuleto_Param1 < 300 || QuestAmuleto_Param2 < 250 /*|| QuestAmuleto_Param3 < 700 || QuestAmuleto_Param4 < 800*/)
				LoadTextFromFile("game\\quest\\Amuleto_progress.txt");
			else
				LoadTextFromFile("game\\quest\\Amuleto_end.txt");
			Flag++;
			break;
		}
		break;

	case QUESTID_TRAJE:
		switch (QuestTraje_State)
		{
		case 0:
			LoadTextFromFile("game\\quest\\traje_begin.txt");
			Flag++;
			break;
		case 1:
			if (QuestTraje_Param1 < 100 || QuestTraje_Param2 < 70)
				LoadTextFromFile("game\\quest\\traje_progress.txt");
			else
				LoadTextFromFile("game\\quest\\traje_end.txt");
			Flag++;
			break;
		}
		break;

	case QUESTID_150A:
		switch (QuestLv150A_State)
		{
		case 0:
			if (lpCurPlayer->smCharInfo.Level >= 150 && lpCurPlayer->smCharInfo.Level < 155)
			{
				LoadTextFromFile("game\\quest\\lv150a_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		case 1:
			if (QuestLv150A_Type == 0)
			{
				if (QuestLv150A_Param < 1000)
				{
					LoadTextFromFile("game\\quest\\lv150a_progress.txt");
				}
				else if (QuestLv150A_Param >= 1000)
				{
					LoadTextFromFile("game\\quest\\lv150a_end.txt");
				}
			}
			else if (QuestLv150A_Type == 1)
			{
				if (QuestLv150A_Param < 2000)
				{
					LoadTextFromFile("game\\quest\\lv150a_progress.txt");
				}
				else if (QuestLv150A_Param >= 2000)
				{
					LoadTextFromFile("game\\quest\\lv150a_end.txt");
				}
			}

			Flag++;
			break;
		case 2:
			if (lpCurPlayer->smCharInfo.Level >= 150 && lpCurPlayer->smCharInfo.Level < 125)
			{
				LoadTextFromFile("game\\quest\\lv150a_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		}
		break;

	case QUESTID_150B:
		switch (QuestLv150B_State)
		{
		case 0:
			if (lpCurPlayer->smCharInfo.Level >= 125)
			{
				LoadTextFromFile("game\\quest\\lv150b_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		case 1:
			if (!QuestLv150B_Param)
			{
				LoadTextFromFile("game\\quest\\lv150b_step1.txt");
			}
			else if (QuestLv150B_Param == 1)
			{
				LoadTextFromFile("game\\quest\\lv150b_step1_.txt");
			}
			Flag++;
			break;
		case 2:
			if (!QuestLv150B_Param)
			{
				LoadTextFromFile("game\\quest\\lv150b_step2.txt");
			}
			else if (QuestLv150B_Param == 1)
			{
				LoadTextFromFile("game\\quest\\lv150b_step2_.txt");
			}
			Flag++;
			break;
		case 3:
			if (!QuestLv150B_Param)
			{
				LoadTextFromFile("game\\quest\\lv150b_step3.txt");
			}
			else if (QuestLv150B_Param == 1)
			{
				LoadTextFromFile("game\\quest\\lv150b_step3_.txt");
			}
			Flag++;
			break;
		case 4:
			if (!QuestLv150B_Param)
			{
				LoadTextFromFile("game\\quest\\lv150b_step4.txt");
			}
			else if (QuestLv150B_Param == 1)
			{
				LoadTextFromFile("game\\quest\\lv150b_step4_.txt");
			}
			Flag++;
			break;
		case 5:
			if (!QuestLv150B_Param)
			{
				LoadTextFromFile("game\\quest\\lv150b_step5.txt");
			}
			else if (QuestLv150B_Param == 1)
			{
				LoadTextFromFile("game\\quest\\lv150b_end_.txt");
			}
			Flag++;
			break;
		case 6:
			if (GetPlayTime_T() > QuestLv150B_Time)
			{
				LoadTextFromFile("game\\quest\\lv150b_begin.txt");
				Flag++;
			}
			else if (lpCurPlayer->smCharInfo.Level >= 155)
			{
				char szBuff[256];

				DWORD Time = QuestLv150B_Time - GetPlayTime_T();
				UINT Days = Time / 60 / 60 / 24;
				UINT Hours = (Time / 60 / 60) % 24;
				UINT Minutes = (Time / 60) % 60;
				UINT Seconds = Time % 60;

				wsprintf(szBuff, "Descanse um pouco guerreiro, volte daqui a %02d:%02d:%02d para fazer este desafio novamente.", Hours, Minutes, Seconds);

				cMessageBox.ShowMessageEvent(szBuff);
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		}
		break;

	case QUESTID_155A:
		switch (QuestLv155A_State)
		{
		case 0:
			if (lpCurPlayer->smCharInfo.Level >= 155 && lpCurPlayer->smCharInfo.Level < 160)
			{
				LoadTextFromFile("game\\quest\\lv155a_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		case 1:
			if (QuestLv155A_Type == 0)
			{
				if (QuestLv155A_Param < 350)
				{
					LoadTextFromFile("game\\quest\\lv155a_progress.txt");
				}
				else if (QuestLv155A_Param >= 350)
				{
					LoadTextFromFile("game\\quest\\lv155a_end.txt");
				}
			}
			else if (QuestLv155A_Type == 1)
			{
				if (QuestLv155A_Param < 1000)
				{
					LoadTextFromFile("game\\quest\\lv155a_progress.txt");
				}
				else if (QuestLv155A_Param >= 1000)
				{
					LoadTextFromFile("game\\quest\\lv155a_end.txt");
				}
			}

			Flag++;
			break;
		case 2:
			if (lpCurPlayer->smCharInfo.Level >= 155 && lpCurPlayer->smCharInfo.Level < 160)
			{
				LoadTextFromFile("game\\quest\\lv155a_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		}
		break;

	case QUESTID_160B:
		switch (QuestLv160B_State)
		{
		case 0:
			if (lpCurPlayer->smCharInfo.Level >= 160 && lpCurPlayer->smCharInfo.Level < 165)
			{
				LoadTextFromFile("game\\quest\\lv160b_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		case 1:
			if (QuestLv160B_Type == 0)
			{
				if (QuestLv160B_Param < 500)
				{
					LoadTextFromFile("game\\quest\\lv160b_progress.txt");
				}
				else if (QuestLv160B_Param >= 500)
				{
					LoadTextFromFile("game\\quest\\lv160b_end.txt");
				}
			}
			else if (QuestLv160B_Type == 1)
			{
				if (QuestLv160B_Param < 1500)
				{
					LoadTextFromFile("game\\quest\\lv160b_progress.txt");
				}
				else if (QuestLv160B_Param >= 1500)
				{
					LoadTextFromFile("game\\quest\\lv160b_end.txt");
				}
			}

			Flag++;
			break;
		case 2:
			if (lpCurPlayer->smCharInfo.Level >= 160 && lpCurPlayer->smCharInfo.Level < 165)
			{
				LoadTextFromFile("game\\quest\\lv160b_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		}
		break;

	case QUESTID_160A:
		switch (QuestLv160A_State)
		{
		case 0:
			if (lpCurPlayer->smCharInfo.Level >= 125)
			{
				LoadTextFromFile("game\\quest\\lv160a_begin.txt");
				Flag++;
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		case 1:
			if (QuestLv160A_Type == 0)
			{
				if (QuestLv160A_Param1 < 50/* || QuestLv160A_Param2 < 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_1_progress.txt");
				}
				else if (QuestLv160A_Param1 >= 50 /*&& QuestLv160A_Param2 >= 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_1_end.txt");
				}
			}
			else if (QuestLv160A_Type == 1)
			{
				if (QuestLv160A_Param1 < 50 /*|| QuestLv160A_Param2 < 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_2_progress.txt");
				}
				else if (QuestLv160A_Param1 >= 50 /*&& QuestLv160A_Param2 >= 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_2_end.txt");
				}
			}
			else if (QuestLv160A_Type == 2)
			{
				if (QuestLv160A_Param1 < 50 /*|| QuestLv160A_Param2 < 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_3_progress.txt");
				}
				else if (QuestLv160A_Param1 >= 50 /*&& QuestLv160A_Param2 >= 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_3_end.txt");
				}
			}
			else if (QuestLv160A_Type == 3)
			{
				if (QuestLv160A_Param1 < 50 /*|| QuestLv160A_Param2 < 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_4_progress.txt");
				}
				else if (QuestLv160A_Param1 >= 50 /*&& QuestLv160A_Param2 >= 10*/)
				{
					LoadTextFromFile("game\\quest\\lv160a_4_end.txt");
				}
			}

			Flag++;
			break;
		case 2:
			if (GetPlayTime_T() > QuestLv160A_Time)
			{
				LoadTextFromFile("game\\quest\\lv160a_begin.txt");
				Flag++;
			}
			else if (lpCurPlayer->smCharInfo.Level >= 125)
			{
				char szBuff[256];

				DWORD Time = QuestLv160A_Time - GetPlayTime_T();
				UINT Days = Time / 60 / 60 / 24;
				UINT Hours = (Time / 60 / 60) % 24;
				UINT Minutes = (Time / 60) % 60;
				UINT Seconds = Time % 60;

				wsprintf(szBuff, "Descanse um pouco guerreiro, volte daqui a %02d:%02d:%02d para fazer este desafio novamente.", Hours, Minutes, Seconds);
				cMessageBox.ShowMessageEvent(szBuff);
			}
			else
				cMessageBox.ShowMessageEvent("Você não tem nível suficiente para esse desafio!");
			break;
		}
		break;
	}

	if (Flag)
	{
		fOpen = true;
		QuestCode = Code;
	}
}

void Quest::SendCancelToServer()
{
	smTRANS_COMMAND	TransCommand;
	TransCommand.code = smTRANSCODE_CANCEL_QUEST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = QuestCode;

	smWINSOCK* lpsmSock;
	lpsmSock = GetAreaServerSock();

	if (lpsmSock)
	{
		lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
	}

	switch (QuestCode)
	{
	case QUESTID_150A:
		QuestLv150A_State = 0;
		QuestLv150A_Param = 0;
		QuestLv150A_Time = 0;
		QuestLv150A_Type = 0;
		break;
	case QUESTID_150B:
		QuestLv150B_State = 0;
		QuestLv150B_Param = 0;
		QuestLv150B_Time = 0;
		break;
	case QUESTID_155A:
		QuestLv155A_State = 0;
		QuestLv155A_Param = 0;
		QuestLv155A_Time = 0;
		QuestLv155A_Type = 0;
		break;
	case QUESTID_160B:
		QuestLv160B_State = 0;
		QuestLv160B_Param = 0;
		QuestLv160B_Time = 0;
		QuestLv160B_Type = 0;
		break;
	case QUESTID_160A:
		QuestLv160A_State = 0;
		QuestLv160A_Param1 = 0;
		//QuestLv160A_Param2 = 0;
		QuestLv160A_Time = 0;
		QuestLv160A_Type = 0;
		break;
	case QUESTID_START:
		QuestStart_State = 0;
		QuestStart_Param1 = 0;
		QuestStart_Param2 = 0;
		break;

	case QUESTID_BOTA:
		QuestBota_State = 0;
		QuestBota_Param1 = 0;
		QuestBota_Param2 = 0;
		break;

	case QUESTID_AMULETO:
		QuestAmuleto_State = 0;
		QuestAmuleto_Param1 = 0;
		QuestAmuleto_Param2 = 0;
		//QuestAmuleto_Param3 = 0;
		//QuestAmuleto_Param4 = 0;
		break;

		// QUEST DE TRAJE
	case QUESTID_TRAJE:
		QuestTraje_State = 0;
		QuestTraje_Param1 = 0;
		QuestTraje_Param2 = 0;
		break;
	}
}

void Quest::SendProgressToServer()
{
	smTRANS_COMMAND	TransCommand;
	TransCommand.code = smTRANSCODE_PROGRESS_QUEST;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = QuestCode;
	TransCommand.EParam = Type;

	smWINSOCK* lpsmSock;
	lpsmSock = GetAreaServerSock();

	if (lpsmSock)
	{
		lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
	}
}

void Teleport(int Field, int x, int z)
{
	int dx = 0;
	int dz = 0;
	int cnt = 0;

	CloseEachPlayer();

	WarpFieldNearPos(Field, x, z, &dx, &dz);

	lpCurPlayer->SetPosi(x, 0, z, 0, 0, 0);
	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;
	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;

	lpCurPlayer->OnStageField = -1;
	if (smGameStage[0])
	{
		cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
		lpCurPlayer->OnStageField = 0;
	}
	if (cnt == CLIP_OUT && smGameStage[1])
	{
		lpCurPlayer->OnStageField = 1;
	}
}

void Quest::ActionNPC()
{
	int x = 0;
	int z = 0;
	switch (QuestCode)
	{
	case NPC_SEA_ABYSS:
		Teleport(47, -22942 * fONE, 2704 * fONE);
		break;
	case NPC_ANCIENT_WEAPON:
		Teleport(46, 12772 * fONE, -59795 * fONE);
		break;
	case NPC_HEART_FIRE:
		Teleport(50, 27370 * fONE, -69647 * fONE);
		break;
	case QUESTID_START:
		if (QuestStart_State == 0)
		{
			QuestStart_State = 1;
			QuestStart_Param1 = 0;
			QuestStart_Param2 = 0;
		}
		if (QuestStart_State == 1 && QuestStart_Param1 == 50 && QuestStart_Param2 == 20)
		{
			QuestStart_State = 2;
			QuestStart_Param1 = 0;
			QuestStart_Param2 = 0;
		}
		break;

	case QUESTID_BOTA:
		if (QuestBota_State == 0 && lpCurPlayer->smCharInfo.Level >= 115)
		{
			QuestBota_State = 1;
			QuestBota_Param1 = 0;
			QuestBota_Param2 = 0;
		}
		if (QuestBota_State == 1 && QuestBota_Param1 == 100 && QuestBota_Param2 == 150)
		{
			QuestBota_State = 2;
			QuestBota_Param1 = 0;
			QuestBota_Param2 = 0;
		}
		break;

	case QUESTID_AMULETO:
		if (QuestAmuleto_State == 0 && lpCurPlayer->smCharInfo.Level >= 122)
		{
			QuestAmuleto_State = 1;
			QuestAmuleto_Param1 = 0;
			QuestAmuleto_Param2 = 0;
			/*		QuestAmuleto_Param3 = 0;
					QuestAmuleto_Param4 = 0;*/
		}
		if (QuestAmuleto_State == 1 && QuestAmuleto_Param1 == 300 && QuestAmuleto_Param2 == 250 /*&& QuestAmuleto_Param3 >= 700 && QuestAmuleto_Param4 >= 800*/)
		{
			QuestAmuleto_State = 2;
			QuestAmuleto_Param1 = 0;
			QuestAmuleto_Param2 = 0;
			/*	QuestAmuleto_Param3 = 0;
				QuestAmuleto_Param4 = 0;*/
		}
		break;

	case QUESTID_TRAJE:
		if (QuestTraje_State == 0)
		{
			QuestTraje_State = 1;
			QuestTraje_Param1 = 0;
			QuestTraje_Param2 = 0;
		}
		if (QuestTraje_State == 1 && QuestTraje_Param1 == 100 && QuestTraje_Param2 == 70)
		{
			QuestTraje_State = 2;
			QuestTraje_Param1 = 0;
			QuestTraje_Param2 = 0;
		}
		break;

	case QUESTID_155A:
		if (QuestLv155A_State == 0 && lpCurPlayer->smCharInfo.Level >= 155 && lpCurPlayer->smCharInfo.Level < 160)
		{
			QuestLv155A_State = 1;
			QuestLv155A_Param = 0;
			QuestLv155A_Type = Type;
		}
		else if (QuestLv155A_State == 2 && lpCurPlayer->smCharInfo.Level >= 155 && lpCurPlayer->smCharInfo.Level < 160)
		{
			QuestLv155A_State = 1;
			QuestLv155A_Param = 0;
			QuestLv155A_Type = Type;
		}
		else if (QuestLv155A_State == 1)
		{
			if (QuestLv155A_Param >= 350)
			{
				QuestLv155A_State = 2;
				QuestLv155A_Time = GetPlayTime_T() + 60 * 60 * 5;

				if (sinChar->Level >= 155 && sinChar->Level < 160)
				{
					CheckCharForm();
					sinChar->Level++;
					SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
					CodeXorCharInfo_Exp();
					ReformCharForm();
					haCastleSkillUseFlag = 1;
					SendPlayUpdateInfo();
				}
			}
		}
		break;

	case QUESTID_160B:
		if (QuestLv160B_State == 0 && lpCurPlayer->smCharInfo.Level >= 160 && lpCurPlayer->smCharInfo.Level < 165)
		{
			QuestLv160B_State = 1;
			QuestLv160B_Param = 0;
			QuestLv160B_Type = Type;
		}
		else if (QuestLv160B_State == 2 && lpCurPlayer->smCharInfo.Level >= 160 && lpCurPlayer->smCharInfo.Level < 165)
		{
			QuestLv160B_State = 1;
			QuestLv160B_Param = 0;
			QuestLv160B_Type = Type;
		}
		else if (QuestLv160B_State == 1)
		{
			if (QuestLv160B_Param >= 500)
			{
				QuestLv160B_State = 2;
				QuestLv160B_Time = GetPlayTime_T() + 60 * 60 * 5;

				if (sinChar->Level >= 160 && sinChar->Level < 165)
				{
					CheckCharForm();
					sinChar->Level++;
					SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
					CodeXorCharInfo_Exp();
					ReformCharForm();
					haCastleSkillUseFlag = 1;
					SendPlayUpdateInfo();
				}
			}
		}
		break;

	case QUESTID_160A:

		if (QuestLv160A_State == 0 && lpCurPlayer->smCharInfo.Level >= 125)
		{
			QuestLv160A_State = 1;
			QuestLv160A_Param1 = 0;
			//QuestLv160A_Param2 = 0;
			Type = rand() % 4;
			QuestLv160A_Type = Type;
		}
		else if (QuestLv160A_State == 2 && GetPlayTime_T() > QuestLv160A_Time && lpCurPlayer->smCharInfo.Level >= 125)
		{
			QuestLv160A_State = 1;
			//QuestLv160A_Param2 = 0;
			QuestLv160A_Param1 = 0;
			Type = rand() % 4;
			QuestLv160A_Type = Type;
		}
		else if (QuestLv160A_State == 1)
		{
			if (QuestLv160A_Param1 >= 50 /*&& QuestLv160A_Param2 >= 10*/)
			{
				QuestLv160A_State = 2;
				QuestLv160A_Time = GetPlayTime_T() + 60 * 60 * 24;
			}
		}
		break;

	case QUESTID_150A:
		if (QuestLv150A_State == 0 && lpCurPlayer->smCharInfo.Level >= 150 && lpCurPlayer->smCharInfo.Level < 155)
		{
			QuestLv150A_State = 1;
			QuestLv150A_Param = 0;
			QuestLv150A_Type = Type;
		}
		else if (QuestLv150A_State == 2 && lpCurPlayer->smCharInfo.Level >= 150 && lpCurPlayer->smCharInfo.Level < 155)
		{
			QuestLv150A_State = 1;
			QuestLv150A_Param = 0;
			QuestLv150A_Type = Type;
		}
		else if (QuestLv150A_State == 1)
		{
			if (QuestLv150A_Param >= 1000)
			{
				QuestLv150A_State = 2;
				QuestLv150A_Time = GetPlayTime_T() + 60 * 60 * 24;

				if (sinChar->Level >= 150 && sinChar->Level < 155)
				{
					CheckCharForm();
					sinChar->Level++;
					SetExp64(sinChar, ExpLevelTable[sinChar->Level - 1]);
					CodeXorCharInfo_Exp();
					ReformCharForm();
					haCastleSkillUseFlag = 1;
					SendPlayUpdateInfo();
				}
			}
		}
		break;
	case QUESTID_150B:
		if (QuestLv150B_State == 0 && lpCurPlayer->smCharInfo.Level >= 155)
		{
			QuestLv150B_State = 1;
		}
		else if (QuestLv150B_State == 6 && GetPlayTime_T() > QuestLv150B_Time && lpCurPlayer->smCharInfo.Level >= 155)
		{
			QuestLv150B_State = 1;
			QuestLv150B_Param = 0;
		}
		else if (QuestLv150B_State == 1)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 2;
			}
		}
		else if (QuestLv150B_State == 2)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 3;
			}
		}
		else if (QuestLv150B_State == 3)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 4;
			}
		}
		else if (QuestLv150B_State == 4)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 5;
			}
		}
		else if (QuestLv150B_State == 5)
		{
			if (QuestLv150B_Param == 1)
			{
				QuestLv150B_Param = 0;
				QuestLv150B_State = 6;
				QuestLv150B_Time = GetPlayTime_T() + 60 * 60 * 24;
			}
		}
		break;
	}

	SendProgressToServer();
	fOpen = false;
}

void Quest::ButtonNPC()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;

		if (MouseAction(WinX + 200, WinY + 400, 80, 21))
		{
			ActionNPC();
		}

		if (MouseAction(WinX + 300, WinY + 400, 80, 21))
			fOpen = false;

		if ((QuestCode == QUESTID_150A && QuestLv150A_State != 1) || (QuestCode == QUESTID_155A && QuestLv155A_State != 1) || (QuestCode == QUESTID_160B && QuestLv160B_State != 1))
		{
			if (MouseAction(WinX + 200, WinY + 380, 16, 16))
				Type = 0;
			if (MouseAction(WinX + 300, WinY + 380, 16, 16))
				Type = 1;
		}
	}
}

void Quest::PlayerKillingOnClient()
{
	if (QuestLv160A_State == 1 /*&& QuestLv160A_Param2 < 10*/)
	{
		//QuestLv160A_Param2++;
	}
}

void Quest::PlayerKillingOnServer(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT Type FROM [PristonDB].[dbo].[Quest] WHERE [Character]='%s' AND [Code]=%d AND [State]=1", Player->szName, QUESTID_160A);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Quest] SET Param2=Param2+1 WHERE [Character]='%s' AND [Code]=%d AND [Param2] < 10", Player->szName, QUESTID_160A);
				SQL::GetInstance()->Execute(szQuery);
				smTRANS_COMMAND ps;
				ps.size = sizeof(smTRANS_COMMAND);
				ps.code = smTRANSCODE_PLAYER_KILLED;
				Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Quest::sinCheckQuest(int Param)
{
	switch (Param)
	{
	case NPC_PUZZLE:
		Puzzle::GetInstance()->Open();
		break;
	case NPC_NATAL:
		Natal::GetInstance()->Open();
		break;
	case NPC_WORLDCUP:
		WorldCup::GetInstance()->Open();
		break;
	case NPC_LOCKITEM:
		LockItem::GetInstance()->Open();
		break;

	case NPC_UPDATEITEM:
		UpdateItem::GetInstance()->Open();
		break;

	case NPC_AWARDITEM:
		AwardItem::GetInstance()->Open();
		break;
	case NPC_BATTLEARENA:
		BattleArena::GetInstance()->Open();
		break;
	case NPC_HELLGATES:
		HellGates::GetInstance()->Open();
		break;
	case NPC_PLAYERMIGRATION:
		PlayerMigration::GetInstance()->Open();
		break;
	case NPC_SKINVIEW:
		SkinView::GetInstance()->OpenNPC();
		break;
	case NPC_ERAGONCAVE:
		cSinHelp.sinShowHelp(NPC_ERAGONCAVE, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "game\\npc\\eragoncave.txt");
		break;
	case QUESTID_GUIDE:
		cSinHelp.sinShowHelp(QUESTID_START, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "game\\quest\\guide.txt");
		break;
	case QUESTID_START:
	case QUESTID_BOTA:
	case QUESTID_AMULETO:
	case QUESTID_TRAJE:
	case QUESTID_150A:
	case QUESTID_150B:
	case QUESTID_155A:
	case QUESTID_160B:
	case QUESTID_160A:
	case NPC_ANCIENT_WEAPON:
	case NPC_SEA_ABYSS:
	case NPC_HEART_FIRE:
		Quest::GetInstance()->OpenNPC(Param);
		break;
	}
}

bool Quest::StopCharacter()
{
	int BPoint = (WinSizeX - 200);
	int EPoint = 0;
	int wy = (WinSizeY / 80);
	if (WinSizeX == 800 || WinSizeX == 1024 || WinSizeX == 1280 || WinSizeX == 1400)
		EPoint = BPoint - (WinSizeX / 6);
	else if (WinSizeX == 1366 || WinSizeX == 1600 || WinSizeX == 1920)
		EPoint = BPoint - (WinSizeX / 7);
	else
		EPoint = BPoint - (WinSizeX / 8);

	if (QuestLv150A_State)
	{
		if (MouseAction(EPoint, wy, 264, 24))
			return TRUE;

		wy += 25 + Size;
	}

	if (QuestLv150B_State && QuestLv150B_State < 6)
	{
		if (MouseAction(EPoint, wy, 264, 24))
			return TRUE;

		wy += 25 + Size2;
	}

	return FALSE;
}