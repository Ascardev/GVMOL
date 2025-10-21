#include "sinbaram\sinLinkHeader.h"
#include "./field.h"

int	rsSendServerChatMessageToAllUser(int Color, char* msg, ...);

rsPLAYINFO* rsPlayInfo;
time_t	tServerTime;
DWORD		dwPlayServTime = 0;
int DrawFontImage(char* lpStr, int xPos, int yPos, DWORD rgba, float fRatio);

void BattleArena::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\battlearena\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\battlearena\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\battlearena\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\battlearena\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\battlearena\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Icons[0] = LoadDibSurfaceOffscreen("game\\images\\battlearena\\icon1.png");
	Icons[1] = LoadDibSurfaceOffscreen("game\\images\\battlearena\\icon2.png");
	Icons[2] = LoadDibSurfaceOffscreen("game\\images\\battlearena\\icon3.png");
}

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

void BattleArena::Open()
{
	if (Flag == 0)
		LoadTextFromFile("game\\npc\\battlearena_closed.txt");
	if (Flag == 1)
		LoadTextFromFile("game\\npc\\battlearena_open.txt");
	if (Flag == 2)
		LoadTextFromFile("game\\npc\\battlearena_onbattle.txt");

	fOpen = true;
}

bool BattleArena::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void BattleArena::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void BattleArena::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);
		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Arena Mad Max]", 15, &size);
		dsTextLineOut(WinX + 280 - size.cx / 2, WinY + 40, "[Arena Mad Max]", 15);
		FontType = 0;
		dsTextLineOut(WinX + 60, WinY + 80, szBufferTextWindow, strlen(szBufferTextWindow));

		if (MouseAction(WinX + 200, WinY + 400, 93, 23))
			DrawImage(Images[2], WinX + 200, WinY + 400, 93, 23);
		else
			DrawImage(Images[1], WinX + 200, WinY + 400, 93, 23);

		if (MouseAction(WinX + 300, WinY + 400, 93, 23))
			DrawImage(Images[4], WinX + 300, WinY + 400, 93, 23);
		else
			DrawImage(Images[3], WinX + 300, WinY + 400, 93, 23);
	}

	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 43)
	{
		if (Flag == 1)
		{
			char szBuff[256];
			int x = (WinSizeX / 2) - 80;
			wsprintf(szBuff, "Tempo Restante: %d:%d", PlayTime[1], PlayTime[0]);
			DrawFontImage(szBuff, x, 8, D3DCOLOR_RGBA(80, 160, 255, 255), 0.7f);
		}
		else if (Flag == 2)
		{
			char szBuff[256];
			int x = (WinSizeX / 2) - 80;

			wsprintf(szBuff, "Score: %d", YourScore);
			DrawFontImage(szBuff, x + 20, 8, D3DCOLOR_RGBA(0, 255, 0, 255), 0.7f);

			wsprintf(szBuff, "Tempo Restante: %d:%d", PlayTime[1], PlayTime[0]);
			DrawFontImage(szBuff, x + 160, 8, D3DCOLOR_RGBA(80, 160, 255, 255), 0.7f);

			int y = 32;

			if (Score1)
			{
				DrawSprite(x + 170, y - 2, Icons[0], 0, 0, 20, 18);
				DrawFontImage(szName1, x + 195, y + 1, D3DCOLOR_RGBA(200, 165, 0, 255), 0.6f);
			}

			y += 18;

			if (Score2)
			{
				DrawSprite(x + 170, y - 2, Icons[1], 0, 0, 20, 18);
				DrawFontImage(szName2, x + 195, y + 1, D3DCOLOR_RGBA(158, 158, 157, 255), 0.6f);
			}

			y += 18;

			if (Score3)
			{
				DrawSprite(x + 170, y - 2, Icons[2], 0, 0, 20, 18);
				DrawFontImage(szName3, x + 195, y + 1, D3DCOLOR_RGBA(122, 103, 84, 255), 0.6f);
			}
		}
	}
}

void BattleArena::Button()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);

		if (MouseAction(WinX + 200, WinY + 400, 80, 21))
		{
			SendRequest();
		}

		if (MouseAction(WinX + 300, WinY + 400, 80, 21))
			fOpen = false;
	}
}

void BattleArena::SendRequest()
{
	if (lpCurPlayer->smCharInfo.Level < 100)
	{
		cMessageBox.ShowMessageEvent("Você não tem nível suficiente para entrar na arena!");
		return;
	}

	if (Flag == 1)
	{
		smTRANS_COMMAND ps;
		ps.size = sizeof(smTRANS_COMMAND);
		ps.code = smTRANSCODE_BATTLE_ARENA;

		smWINSOCK* lpsmSock;
		lpsmSock = GetAreaServerSock();

		if (lpsmSock)
		{
			lpsmSock->Send((char*)&ps, ps.size, TRUE);
		}

		WarpField2(43);

		fOpen = false;
	}
	else
	{
		fOpen = false;
	}
}

void BattleArena::Main()
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	if (Flag == 0)
	{
		if ((st.wHour == 10 && st.wMinute == 55) || (st.wHour == 16 && st.wMinute == 55) || (st.wHour == 22 && st.wMinute == 55))
		{
			Flag = 1;
			OpenBattle();

			if (SQL::GetInstance()->IsConnected())
			{
				SQL::GetInstance()->EnterSqlSection();
				SQL::GetInstance()->Execute("TRUNCATE TABLE [PristonDB].[dbo].[BattleArena]");
				SQL::GetInstance()->LeaveSqlSection();
			}

			rsSendServerChatMessageToAllUser(3, "> Os Portões da Arena Mad Max foram abertos!");

			for (int cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock)
				{
					SendInformation(&rsPlayInfo[cnt]);
				}
			}
		}
	}
	else if (Flag == 1)
	{
		if (OverOpenTime < dwPlayServTime)
		{
			StartBattle();
			Flag = 2;
			rsSendServerChatMessageToAllUser(3, "> Os Portões da Arena Mad Max foram fechados!");

			for (int cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock)
				{
					SendInformation(&rsPlayInfo[cnt]);
				}
			}
		}
	}
	else if (Flag == 2)
	{
		if (OverBattleTime < dwPlayServTime)
		{
			Flag = 0;
			rsSendServerChatMessageToAllUser(3, "> O Evento na Arena Mad Max acabou de terminar!");
			SendAward();

			for (int cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock)
				{
					SendInformation(&rsPlayInfo[cnt]);
				}
			}
		}
	}
}

void BattleArena::SendInformation(rsPLAYINFO* Player)
{
	smTRANS_BA_INFO ps;
	ps.size = sizeof(smTRANS_BA_INFO);
	ps.code = smTRANSCODE_BATTLE_ARENA;
	ps.Flag = Flag;
	if (Flag == 1)
		ps.EndTime = (short)((OverOpenTime - StartOpenTime) / 1000);
	if (Flag == 2)
		ps.EndTime = (short)((OverBattleTime - StartBattleTime) / 1000);

	Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
}

void BattleArena::RecvInformation(smTRANS_BA_INFO* ps)
{
	if (ps->Flag == 1 && Flag == 0)
	{
		Score1 = 0;
		Score2 = 0;
		Score3 = 0;
	}

	if (ps->Flag == 0 && Flag == 2 && StageField[lpCurPlayer->OnStageField]->FieldCode == 43)
	{
		WarpField2(3);
	}

	Flag = ps->Flag;
	EndTime = ps->EndTime;
}

void BattleArena::OpenBattle()
{
	StartOpenTime = dwPlayServTime;
	OverOpenTime = dwPlayServTime + 3 * 60 * 1000;
}

void BattleArena::StartBattle()
{
	StartBattleTime = dwPlayServTime;
	OverBattleTime = dwPlayServTime + 5 * 60 * 1000;
}

short BattleArena::GetTime()
{
	if (Flag == 1)
		return (short)((dwPlayServTime - StartOpenTime) / 1000);
	if (Flag == 2)
		return (short)((dwPlayServTime - StartBattleTime) / 1000);

	return 0;
}

void BattleArena::SetTime(int CurrentTime)
{
	DWORD Time = EndTime - CurrentTime;

	PlayTime[0] = Time % 60;
	PlayTime[1] = Time / 60;
	PlayTime[1] -= Time / 3600 * 60;
}

void BattleArena::RecvUpgrade(smTRANS_BA_SCORE* ps)
{
	lstrcpy(szName1, ps->szName1);
	lstrcpy(szName2, ps->szName2);
	lstrcpy(szName3, ps->szName3);
	Score1 = ps->Score[0];
	Score2 = ps->Score[1];
	Score3 = ps->Score[2];
}

void BattleArena::SendAward()
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT TOP 3 * FROM [PristonDB].[dbo].[BattleArena] ORDER BY Score DESC"))
		{
			int i = 0;
			char szId1[32] = "", szId2[32] = "", szId3[32] = "";
			char szName1[32] = "", szName2[32] = "", szName3[32] = "";
			int Score[3];
			while (SQL::GetInstance()->Fetch())
			{
				switch (i)
				{
				case 0:
					SQL::GetInstance()->GetDataValue(1, szId1);
					SQL::GetInstance()->GetDataValue(2, szName1);
					SQL::GetInstance()->GetDataValue(3, &Score[0]);
					rsSendServerChatMessageToAllUser(3, "> Parabéns %s, você é o campeão da Arena Mad Max e foi recompensado com 3000 Coins!", szName1);
					break;
				case 1:
					SQL::GetInstance()->GetDataValue(1, szId2);
					SQL::GetInstance()->GetDataValue(2, szName2);
					SQL::GetInstance()->GetDataValue(3, &Score[1]);
					rsSendServerChatMessageToAllUser(3, "> Parabéns %s, você é o vice-campeão da Arena Mad Max e foi recompensado com 2000 Coins!", szName2);
					break;
				case 2:
					SQL::GetInstance()->GetDataValue(1, szId3);
					SQL::GetInstance()->GetDataValue(2, szName3);
					SQL::GetInstance()->GetDataValue(3, &Score[2]);
					rsSendServerChatMessageToAllUser(3, "> Parabéns %s, você é um dos melhores guerreiros da Arena Mad Max e foi recompensado com 1000 Coins!", szName3);
					break;
				}

				i++;

				if (i > 2) break;
			}

			int Awards[3] = { 3000, 2000, 1000 };

			if (Score[0] && szId1[0])
			{
				wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", szId1);
				if (SQL::GetInstance()->Execute(szQuery))
				{
					if (SQL::GetInstance()->Fetch())
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=Coin+%d WHERE [ID]='%s'", Awards[0], szId1);
					}
					else
					{
						wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[CoinShop_Coin] ([ID],[Coin]) values('%s',%d)", szId1, Awards[0]);
					}
					SQL::GetInstance()->Execute(szQuery);
				}
			}

			if (Score[1] && szId2[0])
			{
				wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", szId2);
				if (SQL::GetInstance()->Execute(szQuery))
				{
					if (SQL::GetInstance()->Fetch())
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=Coin+%d WHERE [ID]='%s'", Awards[1], szId2);
					}
					else
					{
						wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[CoinShop_Coin] ([ID],[Coin]) values('%s',%d)", szId2, Awards[1]);
					}
					SQL::GetInstance()->Execute(szQuery);
				}
			}

			if (Score[2] && szId3[0])
			{
				wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", szId3);
				if (SQL::GetInstance()->Execute(szQuery))
				{
					if (SQL::GetInstance()->Fetch())
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=Coin+%d WHERE [ID]='%s'", Awards[2], szId3);
					}
					else
					{
						wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[CoinShop_Coin] ([ID],[Coin]) values('%s',%d)", szId3, Awards[2]);
					}
					SQL::GetInstance()->Execute(szQuery);
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void BattleArena::SendUpgrade(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT TOP 3 * FROM [PristonDB].[dbo].[BattleArena] ORDER BY Score DESC"))
		{
			int i = 0;
			smTRANS_BA_SCORE ps;
			ZeroMemory(&ps, sizeof(smTRANS_BA_SCORE));
			ps.size = sizeof(smTRANS_BA_SCORE);
			ps.code = smTRANSCODE_BATTLE_ARENA_RANKING;
			while (SQL::GetInstance()->Fetch())
			{
				switch (i)
				{
				case 0:
					SQL::GetInstance()->GetDataValue(2, ps.szName1);
					break;
				case 1:
					SQL::GetInstance()->GetDataValue(2, ps.szName2);
					break;
				case 2:
					SQL::GetInstance()->GetDataValue(2, ps.szName3);
					break;
				}

				SQL::GetInstance()->GetDataValue(3, &ps.Score[i]);
				i++;

				if (i > 2) break;
			}

			Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void BattleArena::OnBattle(rsPLAYINFO* Player, rsPLAYINFO* Player2)
{
	if (Player && Player2)
	{
		if (Player->Position.Area == 43 && Player2->Position.Area == 43)
		{
			if (Flag == 2)
			{
				Player2->BattleScore++;

				if (SQL::GetInstance()->IsConnected())
				{
					char szQuery[512];
					SQL::GetInstance()->EnterSqlSection();

					wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[BattleArena] WHERE [Name]='%s'", Player2->szName);
					if (SQL::GetInstance()->Execute(szQuery))
					{
						if (SQL::GetInstance()->Fetch())
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[BattleArena] SET Score=Score+1 WHERE [Name]='%s'", Player2->szName);
						}
						else
						{
							wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[BattleArena] ([ID],[Name],[Score]) values('%s','%s',1)", Player2->szID, Player2->szName);
						}
						SQL::GetInstance()->Execute(szQuery);
					}

					SQL::GetInstance()->LeaveSqlSection();
				}

				for (int cnt = 0; cnt < CONNECTMAX; cnt++)
				{
					if (rsPlayInfo[cnt].lpsmSock)
					{
						if (rsPlayInfo[cnt].Position.Area == 43)
						{
							SendUpgrade(&rsPlayInfo[cnt]);
						}
					}
				}
			}
		}
	}
}

void BattleArena::OnEnter(rsPLAYINFO* Player)
{
	if (Flag == 1)
	{
		if (Player->OnBattle)
		{
			return;
		}

		Player->OnBattle = 1;
		Player->BattleScore = 0;
	}
}

void BattleArena::OnClose(rsPLAYINFO* Player)
{
	if (Flag == 1)
	{
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[512];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[BattleArena] WHERE [Name]='%s'", Player->szName);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[BattleArena] WHERE [Name]='%s'", Player->szName);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}

		for (int cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if (rsPlayInfo[cnt].lpsmSock)
			{
				if (rsPlayInfo[cnt].Position.Area == 43)
				{
					SendUpgrade(&rsPlayInfo[cnt]);
				}
			}
		}
	}
}