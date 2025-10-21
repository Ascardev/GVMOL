#include "sinbaram\sinLinkHeader.h"

void Loading::Init()
{
	for (int cnt = 0; cnt < 19; cnt++)
	{
		char szBuff[256];
		wsprintf(szBuff, "game\\images\\loading\\l%d.png", cnt + 1);
		Images[cnt] = CreateTextureMaterial(szBuff, 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	}

	ImageTime = 0;
	Image = 0;
}

void Loading::Main()
{
	if (ImageTime > 20)
	{
		Image++;

		if (Image >= 19)
		{
			Image = 0;
		}

		ImageTime = 0;
	}

	ImageTime += 10;
}

void Loading::Draw()
{
	int WinX = -153;
	int WinY = 12;
	dsDrawColorBox(D3DCOLOR_RGBA(0, 0, 0, 100), 20, 84, 200, 200);
	dsDrawTexImage(Images[Image], WinX, WinY, 539, 359, 255);
}