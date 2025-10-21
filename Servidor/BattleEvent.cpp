#include "sinbaram\sinLinkHeader.h"
#include "./field.h"

int	rsSendServerChatMessageToAllUser(int Color, char* msg, ...);

rsPLAYINFO* rsPlayInfo;
time_t	tServerTime;
DWORD		dwPlayServTime = 0;
int DrawFontImage(char* lpStr, int xPos, int yPos, DWORD rgba, float fRatio);

void BattleEvent::Init()
{
	Icons[0] = LoadDibSurfaceOffscreen("game\\images\\BattleArena\\icon1.png");
	Icons[1] = LoadDibSurfaceOffscreen("game\\images\\BattleArena\\icon2.png");
	Icons[2] = LoadDibSurfaceOffscreen("game\\images\\BattleArena\\icon3.png");
}

void BattleEvent::Draw()
{
	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 32)
	{
		if (Flag == 2)
		{
			char szBuff[256];
			int x = (WinSizeX / 2) - 80;
			int y = 32;

			if (Score1)
			{
				wsprintf(szBuff, "%s:%d", szName1, Score1);
				DrawSprite(x + 170, y - 2, Icons[0], 0, 0, 20, 18);
				DrawFontImage(szBuff, x + 195, y + 1, D3DCOLOR_RGBA(200, 165, 0, 255), 0.6f);
			}

			y += 18;

			if (Score2)
			{
				wsprintf(szBuff, "%s:%d", szName2, Score2);
				DrawSprite(x + 170, y - 2, Icons[1], 0, 0, 20, 18);
				DrawFontImage(szBuff, x + 195, y + 1, D3DCOLOR_RGBA(158, 158, 157, 255), 0.6f);
			}

			y += 18;

			if (Score3)
			{
				wsprintf(szBuff, "%s:%d", szName3, Score3);
				DrawSprite(x + 170, y - 2, Icons[2], 0, 0, 20, 18);
				DrawFontImage(szBuff, x + 195, y + 1, D3DCOLOR_RGBA(122, 103, 84, 255), 0.6f);
			}
		}
	}
}

void BattleEvent::SendInformation(rsPLAYINFO* Player)
{
	smTRANS_BA_INFO ps;
	ps.size = sizeof(smTRANS_BA_INFO);
	ps.code = smTRANSCODE_BATTLE_EVENT;
	ps.Flag = Flag;
	if (Flag == 1)

		ps.EndTime = (short)((OverOpenTime - StartOpenTime) / 1000);
	if (Flag == 2)
		ps.EndTime = (short)((OverBattleTime - StartBattleTime) / 1000);

	Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
}

void BattleEvent::RecvInformation(smTRANS_BA_INFO* ps)
{
	if (ps->Flag == 1 && Flag == 0)
	{
		Score1 = 0;
		Score2 = 0;
		Score3 = 0;
	}

	Flag = ps->Flag;
	EndTime = ps->EndTime;
}

void BattleEvent::OpenBattle()
{
	StartOpenTime = dwPlayServTime;
	OverOpenTime = dwPlayServTime + 5 * 60 * 1000;
}

void BattleEvent::StartBattle()
{
	StartBattleTime = dwPlayServTime;
	OverBattleTime = dwPlayServTime + 10 * 60 * 1000;
}

void BattleEvent::RecvUpgrade(smTRANS_BA_SCORE* ps)
{
	lstrcpy(szName1, ps->szName1);
	lstrcpy(szName2, ps->szName2);
	lstrcpy(szName3, ps->szName3);
	Score1 = ps->Score[0];
	Score2 = ps->Score[1];
	Score3 = ps->Score[2];
}

void BattleEvent::SendAward()
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT TOP 1 * FROM [PristonDB].[dbo].[BattleEvent] ORDER BY Score DESC"))
		{
			int i = 0;
			char szId1[32] = "";
			char szName1[32] = "";
			int Score[3];
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, szId1);
				SQL::GetInstance()->GetDataValue(2, szName1);
				SQL::GetInstance()->GetDataValue(3, &Score[0]);
				rsSendServerChatMessageToAllUser(3, "> Parabéns %s, você foi o vencedor!", szName1);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void BattleEvent::SendUpgrade(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT TOP 3 * FROM [PristonDB].[dbo].[BattleEvent] ORDER BY Score DESC"))
		{
			int i = 0;
			smTRANS_BA_SCORE ps;
			ZeroMemory(&ps, sizeof(smTRANS_BA_SCORE));
			ps.size = sizeof(smTRANS_BA_SCORE);
			ps.code = smTRANSCODE_BATTLE_EVENT_RANKING;
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

void BattleEvent::OnBattle(rsPLAYINFO* Player, rsPLAYINFO* Player2)
{
	if (Player && Player2)
	{
		if (Player->Position.Area == 32 && Player2->Position.Area == 32)
		{
			if (Flag == 2)
			{
				Player2->BattleScore++;

				if (SQL::GetInstance()->IsConnected())
				{
					char szQuery[512];
					SQL::GetInstance()->EnterSqlSection();

					wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[BattleEvent] WHERE [Name]='%s'", Player2->szName);
					if (SQL::GetInstance()->Execute(szQuery))
					{
						if (SQL::GetInstance()->Fetch())
						{
							wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[BattleEvent] SET Score=Score+1 WHERE [Name]='%s'", Player2->szName);
						}
						else
						{
							wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[BattleEvent] ([ID],[Name],[Score]) values('%s','%s',1)", Player2->szID, Player2->szName);
						}
						SQL::GetInstance()->Execute(szQuery);
					}

					SQL::GetInstance()->LeaveSqlSection();
				}

				for (int cnt = 0; cnt < CONNECTMAX; cnt++)
				{
					if (rsPlayInfo[cnt].lpsmSock)
					{
						if (rsPlayInfo[cnt].Position.Area == 32)
						{
							SendUpgrade(&rsPlayInfo[cnt]);
						}
					}
				}
			}
		}
	}
}

void BattleEvent::OnEnter(rsPLAYINFO* Player)
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

void BattleEvent::OnClose(rsPLAYINFO* Player)
{
	if (Flag == 1)
	{
		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[512];
			SQL::GetInstance()->EnterSqlSection();
			wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[BattleEvent] WHERE [Name]='%s'", Player->szName);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[BattleEvent] WHERE [Name]='%s'", Player->szName);
					SQL::GetInstance()->Execute(szQuery);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}

		for (int cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if (rsPlayInfo[cnt].lpsmSock)
			{
				if (rsPlayInfo[cnt].Position.Area == 32)
				{
					SendUpgrade(&rsPlayInfo[cnt]);
				}
			}
		}
	}
}