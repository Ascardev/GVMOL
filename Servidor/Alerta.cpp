#include "sinbaram\\sinlinkheader.h"
#include "FontImage.h"
#include "Alerta.h"

void cAlerta::Init()
{
	Mat[BACKGROUND] = CreateTextureMaterial("game\\images\\Global\\Global.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

bool ShowAlert;
char AlertTXT[256];

int i = 0;
int Transp = 255;
int j = 0;

void cAlerta::Draw()
{
	int BaseX, BaseY;
	BaseX = (WinSizeX - 301) / 2;
	smScreenWidth = WinSizeX;
	smScreenHeight = WinSizeY;

	MidX = WinSizeX / 2;
	MidY = WinSizeY / 2;

	if (ShowAlert)
	{
		if (j < 45 && i < 600)
		{
			j++;
		}
		if (i >= 600)
		{
			j--;
		}

		i++;
		SIZE size;
		size = {};
		AlertTXT[strlen(AlertTXT)];
		GetFontTextExtentPoint(AlertTXT, lstrlen(AlertTXT), &size);
		HoDrawTexImage(Mat[BACKGROUND], smScreenWidth / 2 - 230, j - 55, 519, 140, 519, 140, Transp);

		wsprintf(AlertTXT, "%s", AlertTXT);
		SetTextColor(0, RGB(255, 255, 255));
		DrawFontTextNew(BaseX + (175 - (size.cx / 2)), j + 35, AlertTXT, D3DCOLOR_RGBA(255, 255, 222, 180), 1);
	}
	if (i >= 645)
	{
		ShowAlert = false;
		i = 0;
	}
}