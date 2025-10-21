#include "sinbaram\sinLinkHeader.h"

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);

void LockItem::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\LockItem\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\LockItem\\button_ok.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\LockItem\\button_ok_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\LockItem\\button_close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\LockItem\\button_close_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	bImages[0] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\itembox.bmp");

	buttonImage[0] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\0.bmp");
	buttonImage[1] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\1.bmp");
	buttonImage[2] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\2.bmp");
	buttonImage[3] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\3.bmp");
	buttonImage[4] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\4.bmp");
	buttonImage[5] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\5.bmp");
	buttonImage[6] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\6.bmp");
	buttonImage[7] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\7.bmp");
	buttonImage[8] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\8.bmp");
	buttonImage[9] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\9.bmp");
	buttonImage[10] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\v.bmp");
	buttonImage[11] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\x.bmp");

	buttonImageHover[0] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\0_.bmp");
	buttonImageHover[1] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\1_.bmp");
	buttonImageHover[2] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\2_.bmp");
	buttonImageHover[3] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\3_.bmp");
	buttonImageHover[4] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\4_.bmp");
	buttonImageHover[5] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\5_.bmp");
	buttonImageHover[6] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\6_.bmp");
	buttonImageHover[7] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\7_.bmp");
	buttonImageHover[8] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\8_.bmp");
	buttonImageHover[9] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\9_.bmp");
	buttonImageHover[10] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\v_.bmp");
	buttonImageHover[11] = LoadDibSurfaceOffscreen("game\\images\\LockItem\\x_.bmp");
}

bool LockItem::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void LockItem::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void LockItem::RecvRequest(rsPLAYINFO* Player, smPACKET_LOCK* packet)
{
	if (!packet->sItem->sItemInfo.LockItem)
	{
	}
	else
	{
	}
}

void LockItem::SendRequest()
{
}

void LockItem::Button()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 165;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 331, 438);

		if (MouseAction(WinX + 180, WinY + 180, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "0");
			}
		}

		if (MouseAction(WinX + 200, WinY + 180, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "1");
			}
		}

		if (MouseAction(WinX + 220, WinY + 180, 20, 20))
		{
			if (strlen(Password) < 3)
			{
				lstrcat(Password, "2");
			}
		}

		if (MouseAction(WinX + 180, WinY + 200, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "3");
			}
		}

		if (MouseAction(WinX + 200, WinY + 200, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "4");
			}
		}

		if (MouseAction(WinX + 220, WinY + 200, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "5");
			}
		}

		if (MouseAction(WinX + 180, WinY + 220, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "6");
			}
		}

		if (MouseAction(WinX + 200, WinY + 220, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "7");
			}
		}

		if (MouseAction(WinX + 220, WinY + 220, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "8");
			}
		}

		if (MouseAction(WinX + 180, WinY + 240, 20, 20))
		{
			if (strlen(Password) < 4)
			{
				lstrcat(Password, "9");
			}
		}

		if (MouseAction(WinX + 200, WinY + 240, 20, 20))
		{
			ZeroMemory(Password, sizeof(Password));
		}

		if (MouseAction(WinX + 220, WinY + 240, 20, 20))
		{
			Password[strlen(Password) - 1] = '\0';
		}

		if (!sItem.Flag)
		{
			if (MouseItem.sItemInfo.CODE)
			{
				if (MouseAction(WinX + 90, WinY + 174, 68, 90))
				{
					MouseItem.x = WinX + 90 + 34 - (MouseItem.w / 2);
					MouseItem.y = WinY + 174 + 40 - (MouseItem.h / 2);
					memcpy(&sItem, &MouseItem, sizeof(sITEM));
					ZeroMemory(&MouseItem, sizeof(sITEM));
				}
			}
		}
		else
		{
			if (MouseAction(WinX + 90, WinY + 174, 68, 90))
			{
				sItem.x = pCursorPos.x - (sItem.w / 2);
				sItem.y = pCursorPos.y - (sItem.y / 2);
				memcpy(&MouseItem, &sItem, sizeof(sITEM));
				ZeroMemory(&sItem, sizeof(sITEM));
			}
		}

		if (MouseAction(WinX + 85, WinY + 400, 80, 21))
		{
			SendRequest();
		}

		if (MouseAction(WinX + 185, WinY + 400, 80, 21))
			Close();
	}
}

void LockItem::Open()
{
	fOpen = true;
}

void LockItem::Close()
{
	fOpen = false;
}

void LockItem::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 165;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 331, 438);
		DrawSprite(WinX + 90, WinY + 174, bImages[0], 0, 0, 68, 90);

		if (MouseAction(WinX + 90, WinY + 174, 68, 90))
		{
			if (sItem.Flag)
			{
				dsDrawColorBox(D3DCOLOR_RGBA(255, 255, 255, 128), WinX + 90, WinY + 174, 68, 90);
			}
			else if (MouseItem.Flag)
			{
				dsDrawColorBox(D3DCOLOR_RGBA(160, 235, 256, 128), WinX + 90, WinY + 174, 68, 90);
			}
		}

		if (sItem.Flag)
		{
			DrawSprite(sItem.x, sItem.y, sItem.lpItem, 0, 0, sItem.w, sItem.h);

			if (MouseAction(WinX + 90, WinY + 174, 68, 90))
			{
				sinShowItemInfoFlag = 1;
				cItem.ShowItemInfo(&sItem, 1);
			}
		}

		if (MouseAction(WinX + 180, WinY + 180, 20, 20))
			DrawSprite(WinX + 180, WinY + 180, buttonImageHover[0], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 180, WinY + 180, buttonImage[0], 0, 0, 20, 20);

		if (MouseAction(WinX + 200, WinY + 180, 20, 20))
			DrawSprite(WinX + 200, WinY + 180, buttonImageHover[1], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 200, WinY + 180, buttonImage[1], 0, 0, 20, 20);

		if (MouseAction(WinX + 220, WinY + 180, 20, 20))
			DrawSprite(WinX + 220, WinY + 180, buttonImageHover[2], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 220, WinY + 180, buttonImage[2], 0, 0, 20, 20);

		if (MouseAction(WinX + 180, WinY + 200, 20, 20))
			DrawSprite(WinX + 180, WinY + 200, buttonImageHover[3], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 180, WinY + 200, buttonImage[3], 0, 0, 20, 20);

		if (MouseAction(WinX + 200, WinY + 200, 20, 20))
			DrawSprite(WinX + 200, WinY + 200, buttonImageHover[4], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 200, WinY + 200, buttonImage[4], 0, 0, 20, 20);

		if (MouseAction(WinX + 220, WinY + 200, 20, 20))
			DrawSprite(WinX + 220, WinY + 200, buttonImageHover[5], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 220, WinY + 200, buttonImage[5], 0, 0, 20, 20);

		if (MouseAction(WinX + 180, WinY + 220, 20, 20))
			DrawSprite(WinX + 180, WinY + 220, buttonImageHover[6], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 180, WinY + 220, buttonImage[6], 0, 0, 20, 20);

		if (MouseAction(WinX + 200, WinY + 220, 20, 20))
			DrawSprite(WinX + 200, WinY + 220, buttonImageHover[7], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 200, WinY + 220, buttonImage[7], 0, 0, 20, 20);

		if (MouseAction(WinX + 220, WinY + 220, 20, 20))
			DrawSprite(WinX + 220, WinY + 220, buttonImageHover[8], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 220, WinY + 220, buttonImage[8], 0, 0, 20, 20);

		if (MouseAction(WinX + 180, WinY + 240, 20, 20))
			DrawSprite(WinX + 180, WinY + 240, buttonImageHover[9], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 180, WinY + 240, buttonImage[9], 0, 0, 20, 20);

		if (MouseAction(WinX + 200, WinY + 240, 20, 20))
			DrawSprite(WinX + 200, WinY + 240, buttonImageHover[10], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 200, WinY + 240, buttonImage[10], 0, 0, 20, 20);

		if (MouseAction(WinX + 220, WinY + 240, 20, 20))
			DrawSprite(WinX + 220, WinY + 240, buttonImageHover[11], 0, 0, 20, 20);
		else
			DrawSprite(WinX + 220, WinY + 240, buttonImage[11], 0, 0, 20, 20);

		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Trancar Item]", 15, &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 40, "[Trancar Item]", 15);
		GetFontTextExtentPoint("________________", 16, &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 284, "________________", 16);

		dsTextLineOut(WinX + 150, WinY + 278, Password, strlen(Password));
		FontType = 0;

		if (MouseAction(WinX + 85, WinY + 400, 80, 21))
			DrawImage(Images[2], WinX + 85, WinY + 400, 80, 21);
		else
			DrawImage(Images[1], WinX + 85, WinY + 400, 80, 21);

		if (MouseAction(WinX + 185, WinY + 400, 80, 21))
			DrawImage(Images[4], WinX + 185, WinY + 400, 80, 21);
		else
			DrawImage(Images[3], WinX + 185, WinY + 400, 80, 21);
	}
}