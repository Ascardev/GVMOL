#include "sinbaram\sinLinkHeader.h"

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);

void AwardItem::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\distribuidor\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\distribuidor\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\distribuidor\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\distribuidor\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\distribuidor\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[5] = CreateTextureMaterial("game\\images\\distribuidor\\left.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[6] = CreateTextureMaterial("game\\images\\distribuidor\\left_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[7] = CreateTextureMaterial("game\\images\\distribuidor\\right.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[8] = CreateTextureMaterial("game\\images\\distribuidor\\right_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	bImages[0] = LoadDibSurfaceOffscreen("game\\images\\distribuidor\\itembox.bmp");
}

bool AwardItem::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void AwardItem::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void AwardItem::SendList(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		AWARD_ITEM packet;
		int i = 0;
		ZeroMemory(&packet, sizeof(AWARD_ITEM));
		packet.code = smTRANSCODE_AWARD_ITEM;
		packet.size = sizeof(AWARD_ITEM);
		wsprintf(szQuery, "SELECT Id,ItemName,Code FROM [PristonDB].[dbo].[AwardItem_List] WHERE Character='%s'", Player->smCharInfo.szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.Id);
				SQL::GetInstance()->GetDataValue(2, packet.Name);
				SQL::GetInstance()->GetDataValue(3, packet.Code);

				Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
				i++;

				if (i >= 10) break;
			}

			if (i > 0)
			{
				smTRANS_COMMAND ps;
				ps.size = sizeof(smTRANS_COMMAND);
				ps.code = smTRANSCODE_OPEN_AWARD_ITEM;
				ps.WParam = i;
				Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void AwardItem::RecvRequest(rsPLAYINFO* Player, smTRANS_COMMAND* packet)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		char szCode[32];

		wsprintf(szQuery, "SELECT Code FROM [PristonDB].[dbo].[AwardItem_List] WHERE Character='%s' AND Id=%d", Player->smCharInfo.szName, packet->WParam);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, szCode);
				SendItemToPlayer(Player, szCode, Player->smCharInfo.JOB_CODE);
				wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[AwardItem_List] WHERE Character='%s' AND Id=%d", Player->smCharInfo.szName, packet->WParam);
				SQL::GetInstance()->Execute(szQuery);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void AwardItem::SaveItem(rsPLAYINFO* Player, char* szName, char* szCode)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[AwardItem_List] ([Character],[ItemName],[Code]) values('%s','%s','%s')", Player->smCharInfo.szName, szName, szCode);
		SQL::GetInstance()->Execute(szQuery);
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void AwardItem::RecvList(AWARD_ITEM* packet)
{
	for (int cnt = 0; cnt < 10; cnt++)
	{
		if (!RecvItem[cnt].flag)
		{
			memcpy(&RecvItem[cnt], packet, sizeof(AWARD_ITEM));
			RecvItem[cnt].flag = true;

			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (lstrcmp(sItem[j].LastCategory, RecvItem[cnt].Code) == 0)
				{
					char szFilePath[256];
					wsprintf(szFilePath, "Image\\sinImage\\Items\\%s\\it%s.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
					RecvItem[cnt].Image = LoadDibSurfaceOffscreen(szFilePath);
					RecvItem[cnt].w = sItem[j].w;
					RecvItem[cnt].h = sItem[j].h;
					break;
				}
			}

			break;
		}
	}
}















void AwardItem::SendRequest()
{
	smTRANS_COMMAND ps;
	ps.size = sizeof(smTRANS_COMMAND);
	ps.code = smTRANSCODE_AWARD_ITEM;
	ps.WParam = RecvItem[SelectItem].Id;

	smWINSOCK* lpsmSock;
	lpsmSock = GetAreaServerSock();

	if (lpsmSock)
	{
		lpsmSock->Send((char*)&ps, ps.size, TRUE);
	}

	RecvItem[SelectItem].flag = false;

	AWARD_ITEM Temp[10];
	memset(&Temp[0], 0, sizeof(AWARD_ITEM) * 10);

	for (int cnt = 0; cnt < 10; cnt++)
	{
		if (RecvItem[cnt].flag)
		{
			for (int j = 0; j < 10; j++)
			{
				if (!Temp[j].flag)
				{
					memcpy(&Temp[j], &RecvItem[cnt], sizeof(AWARD_ITEM));
					break;
				}
			}
		}
	}

	memset(&RecvItem[0], 0, sizeof(AWARD_ITEM) * 10);
	memcpy(&RecvItem[0], &Temp[0], sizeof(AWARD_ITEM) * 10);

	SelectItem = 0;
	ItemCount = 0;

	for (int cnt = 0; cnt < 10; cnt++)
	{
		if (RecvItem[cnt].flag)
		{
			ItemCount++;
		}
	}

	if (ItemCount <= 0)
	{
		fOpen = false;
	}
}

void AwardItem::Button()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 165;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 331, 438);

		if (MouseAction(WinX + 85, WinY + 400, 80, 21))
		{
			SendRequest();
		}

		if (MouseAction(WinX + 185, WinY + 400, 80, 21))
			Close();

		if (ItemCount > 1)
		{
			if (SelectItem > 0)
			{
				if (MouseAction(WinX + 101, WinY + 209, 20, 20))
					SelectItem--;
			}

			if (ItemCount > (SelectItem + 1))
			{
				if (MouseAction(WinX + 206, WinY + 209, 20, 20))
					SelectItem++;
			}
		}
	}
}

void AwardItem::Open()
{
	fOpen = true;
	SelectItem = 0;
	ItemCount = 0;

	for (int cnt = 0; cnt < 10; cnt++)
	{
		if (RecvItem[cnt].flag)
		{
			ItemCount++;
		}
	}
}

void AwardItem::Close()
{
	fOpen = false;

	for (int cnt = 0; cnt < 10; cnt++)
	{
		if (RecvItem[cnt].flag)
		{
			if (RecvItem[cnt].Image)
			{
				RecvItem[cnt].Image->Release();
				RecvItem[cnt].Image = NULL;
			}
		}
	}

	memset(&RecvItem[0], 0, sizeof(AWARD_ITEM) * 10);
}

void AwardItem::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 165;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 331, 438);
		DrawSprite(WinX + 131, WinY + 174, bImages[0], 0, 0, 68, 90);

		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Distribuidor]", 15, &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 40, "[Distribuidor]", 15);
		FontType = 0;
		GetFontTextExtentPoint(RecvItem[SelectItem].Name, strlen(RecvItem[SelectItem].Name), &size);
		SetFontTextColor(RGB(0, 255, 255));
		dsTextLineOut(WinX + 131 + 34 - size.cx / 2, WinY + 134, RecvItem[SelectItem].Name, strlen(RecvItem[SelectItem].Name));
		SetFontTextColor(RGB(255, 255, 255));
		char szBuff[256];
		wsprintf(szBuff, "Você tem %d itens disponiveis", ItemCount);
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 284, szBuff, strlen(szBuff));
		wsprintf(szBuff, "no seu distribuidor.");
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 304, szBuff, strlen(szBuff));

		if (MouseAction(WinX + 65, WinY + 400, 93, 23))
			DrawImage(Images[2], WinX + 65, WinY + 400, 93, 23);
		else
			DrawImage(Images[1], WinX + 65, WinY + 400, 93, 23);

		if (MouseAction(WinX + 175, WinY + 400, 93, 23))
			DrawImage(Images[4], WinX + 175, WinY + 400, 93, 23);
		else
			DrawImage(Images[3], WinX + 175, WinY + 400, 93, 23);

		DrawSprite(WinX + 165 - (RecvItem[SelectItem].w / 2), WinY + 219 - (RecvItem[SelectItem].h / 2), RecvItem[SelectItem].Image, 0, 0, RecvItem[SelectItem].w, RecvItem[SelectItem].h);

		if (ItemCount > 1)
		{
			if (SelectItem > 0)
			{
				if (MouseAction(WinX + 101, WinY + 209, 20, 20))
					DrawImage(Images[5], WinX + 101, WinY + 209, 20, 20);
				else
					DrawImage(Images[6], WinX + 101, WinY + 209, 20, 20);
			}

			if (ItemCount > (SelectItem + 1))
			{
				if (MouseAction(WinX + 206, WinY + 209, 20, 20))
					DrawImage(Images[7], WinX + 206, WinY + 209, 20, 20);
				else
					DrawImage(Images[8], WinX + 206, WinY + 209, 20, 20);
			}
		}
	}
}