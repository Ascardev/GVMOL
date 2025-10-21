#include "sinbaram//sinLinkHeader.h"

void Challenge::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void Challenge::Main()
{
	if (Flag)
	{
		if (Opacity < 255)
		{
			Opacity += 5;
			if (Opacity == 255)
			{
				Flag = 0;
			}
		}
	}
	else
	{
		if (Opacity > 0)
		{
			Opacity -= 7.5;
			if (Opacity == 0)
			{
				Flag = 1;
			}
		}
	}
}

void Challenge::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\settings\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\challenge\\1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\challenge\\2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\challenge\\3.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\challenge\\4.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[5] = CreateTextureMaterial("game\\images\\challenge\\5.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[6] = CreateTextureMaterial("game\\images\\challenge\\6.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[7] = CreateTextureMaterial("game\\images\\challenge\\7.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[8] = CreateTextureMaterial("game\\images\\challenge\\8.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[9] = CreateTextureMaterial("game\\images\\challenge\\battle.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Flag = 0;
	Queue = 0;
	Opacity = 255;
}

void Challenge::DrawText(char* Text, int x, int y, ID3DXFont* RegularFont, D3DCOLOR Color)
{
	RECT rc;
	rc.left = x;
	rc.right = x + smScreenWidth;
	rc.top = y;
	rc.bottom = y + smScreenHeight;
	RegularFont->DrawText(NULL, Text, strlen(Text), &rc, 0, Color);
}

void Challenge::Draw()
{
	int WinX = WinSizeX / 2 - 280;
	int WinY = WinSizeY / 2 - 219;
	DrawImage(Images[0], WinX, WinY, 561, 438);

	if (Queue || MouseAction(WinX + 210, WinY + 60, 139, 74))
		dsDrawTexImage(Images[9], WinX + 210, WinY + 65, 139, 74, 255);
	else
		dsDrawTexImage(Images[9], WinX + 210, WinY + 65, 139, 74, 150);

	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 153, WinY + 153, 256, 1);
	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 153, WinY + 153, 256, 1);

	if (Queue)
		DrawText("NA FILA", WinX + 230, WinY + 170, CoinFont[0], D3DCOLOR_RGBA(255, 255, 255, (int)Opacity));

	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 6, WinY + 57, 546, 1);
	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 6, WinY + 59, 546, 1);

	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 150, WinY + 60, 1, 370);
	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 152, WinY + 60, 1, 370);

	for (int cnt = 0; cnt < 10; cnt++)
	{
		if (cnt == 8)
			DrawImage(Images[4], WinX + 8, WinY + 60 + cnt * 37, 35, 35);
		else if (cnt == 9)
			DrawImage(Images[4], WinX + 8, WinY + 60 + cnt * 37, 35, 35);
		else
			DrawImage(Images[cnt + 1], WinX + 8, WinY + 60 + cnt * 37, 35, 35);
		FontType = 1;
		dsTextLineOut(WinX + 45, WinY + 63 + cnt * 37, "Developer", 10);
		dsTextLineOut(WinX + 45, WinY + 78 + cnt * 37, "K/D:100.0%", 12);
		FontType = 0;
		dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 6, WinY + 96 + cnt * 37, 145, 1);
	}

	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 6, WinY + 133, 145, 1);

	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 411, WinY + 60, 1, 370);
	dsDrawColorBox(D3DCOLOR_RGBA(134, 98, 49, 255), WinX + 409, WinY + 60, 1, 370);
}

bool Challenge::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Challenge::Button()
{
	int WinX = WinSizeX / 2 - 280;
	int WinY = WinSizeY / 2 - 219;

	if (MouseAction(WinX + 210, WinY + 60, 139, 74))
	{
		if (Queue)
			Queue = 0;
		else
			Queue = 1;
	}
}