#include "sinbaram\sinLinkHeader.h"

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);

void Roulette::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\roullete\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\roullete\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\roullete\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\roullete\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\roullete\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	bImages[0] = LoadDibSurfaceOffscreen("game\\images\\roullete\\itembox.bmp");
}

bool Roulette::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Roulette::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void Roulette::SendList(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		ROULETTE_ITEM packet;
		int PlayerPoint = 0;
		int i = 0;
		ZeroMemory(&packet, sizeof(AWARD_ITEM));
		packet.code = smTRANSCODE_ROULETTE_ITEM;
		packet.size = sizeof(AWARD_ITEM);
		wsprintf(szQuery, "SELECT Id,ItemName,Code FROM [PristonDB].[dbo].[Roulette_List]");
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.Id);
				SQL::GetInstance()->GetDataValue(2, packet.Name);
				SQL::GetInstance()->GetDataValue(3, packet.Code);

				Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
				i++;

				if (i >= 100) break;
			}

			wsprintf(szQuery, "SELECT Point FROM [PristonDB].[dbo].[Roulette_Point] WHERE Character='%s'", Player->szName);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					SQL::GetInstance()->GetDataValue(1, &PlayerPoint);
				}
			}

			if (i > 0)
			{
				smTRANS_COMMAND ps;
				ps.size = sizeof(smTRANS_COMMAND);
				ps.code = smTRANSCODE_OPEN_ROULETTE_ITEM;
				ps.WParam = PlayerPoint;
				Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Roulette::SendRandomItem(rsPLAYINFO* Player)
{
	int i = 0;
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		char szName[32];
		char szCode[32];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT ItemName,Code FROM [PristonDB].[dbo].[Roulette_List]");
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch()) i++;

			wsprintf(szQuery, "SELECT ItemName,Code FROM [PristonDB].[dbo].[Roulette_List]");
			if (SQL::GetInstance()->Execute(szQuery))
			{
				int Rand = rand() % i;
				i = 0;

				while (SQL::GetInstance()->Fetch())
				{
					if (Rand == i)
					{
						SQL::GetInstance()->GetDataValue(1, szName);
						SQL::GetInstance()->GetDataValue(2, szCode);
						rsSendServerChatMessageToUser(Player, 3, "Roll Ricarten> Você ganhou %s", szName);
						SendItemToPlayer(Player, szCode, 0);
						break;
					}

					i++;
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Roulette::RecvRequest(rsPLAYINFO* Player, smTRANS_COMMAND* packet)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		int Point = 0;
		wsprintf(szQuery, "SELECT Point FROM [PristonDB].[dbo].[Roulette_Point] WHERE Character='%s'", Player->szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &Point);
				if (Point >= 1)
				{
					wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Roulette_Point] SET Point=Point-1 WHERE [Character]='%s'", Player->szName);
					SQL::GetInstance()->Execute(szQuery);
					SendRandomItem(Player);
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Roulette::RecvList(ROULETTE_ITEM* packet)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (!RecvItem[cnt].flag)
		{
			memcpy(&RecvItem[cnt], packet, sizeof(ROULETTE_ITEM));
			RecvItem[cnt].flag = true;

			for (int j = 0; j < MAX_ITEM; j++)
			{
				if (lstrcmp(sItem[j].LastCategory, RecvItem[cnt].Code) == 0)
				{
					char szFilePath[256];
					wsprintf(szFilePath, "game\\images\\roullete\\TenteSorte.bmp", sItem[j].ItemFilePath, sItem[j].LastCategory);
					RecvItem[cnt].Image = LoadDibSurfaceOffscreen(szFilePath);
					RecvItem[cnt].w = 44;
					RecvItem[cnt].h = 44;
					break;
				}
			}

			break;
		}
	}
}

void Roulette::SendRequest()
{
	if (Point >= 1)
	{
		Point--;
		smTRANS_COMMAND ps;
		ps.size = sizeof(smTRANS_COMMAND);
		ps.code = smTRANSCODE_ROULETTE_ITEM;
		ps.WParam = RecvItem[SelectItem].Id;

		smWINSOCK* lpsmSock;
		lpsmSock = GetAreaServerSock();

		if (lpsmSock)
		{
			lpsmSock->Send((char*)&ps, ps.size, TRUE);
		}
	}
	else
	{
		cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
	}
}

void Roulette::Button()
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
	}
}

void Roulette::Open(smTRANS_COMMAND* packet)
{
	fOpen = true;
	Point = packet->WParam;
	ItemCount = 0;
	Opacity = 255;

	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (RecvItem[cnt].flag)
		{
			ItemCount++;
		}
	}
}

void Roulette::Close()
{
	fOpen = false;

	for (int cnt = 0; cnt < 100; cnt++)
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

	memset(&RecvItem[0], 0, sizeof(ROULETTE_ITEM) * 100);
}

void Roulette::Main()
{
	if (Opacity > 0)
	{
		Opacity -= 25;
	}
	else
	{
		Opacity = 255;
		SelectItem++;

		if (SelectItem >= (ItemCount - 1))
		{
			SelectItem = 0;
		}
	}
}

void Roulette::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 165;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 331, 438);
		DrawSprite(WinX + 131, WinY + 174, bImages[0], 0, 0, 68, 90);

		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Roleta]", 9, &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 40, "[Roleta]", 9);
		FontType = 0;
		char szBuff[256];
		wsprintf(szBuff, "Você tem %d fichas disponiveis", Point);
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 284, szBuff, strlen(szBuff));
		wsprintf(szBuff, "a roleta tem o custo de uma ficha.");
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 304, szBuff, strlen(szBuff));

		if (MouseAction(WinX + 65, WinY + 400, 93, 23))
			DrawImage(Images[2], WinX + 65, WinY + 400, 93, 23);
		else
			DrawImage(Images[1], WinX + 65, WinY + 400, 93, 23);

		if (MouseAction(WinX + 175, WinY + 400, 93, 21))
			DrawImage(Images[4], WinX + 175, WinY + 400, 93, 23);
		else
			DrawImage(Images[3], WinX + 175, WinY + 400, 93, 23);

		DrawSpriteOpacity(WinX + 165 - (RecvItem[SelectItem].w / 2), WinY + 219 - (RecvItem[SelectItem].h / 2), RecvItem[SelectItem].Image, 0, 0, RecvItem[SelectItem].w, RecvItem[SelectItem].h, Opacity, 1);
	}
}