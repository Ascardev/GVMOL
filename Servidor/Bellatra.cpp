#include "sinbaram\sinLinkHeader.h"

rsPLAYINFO* rsPlayInfo;
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
int	rsSendServerChatMessageToAllUser(int Color, char* msg, ...);

Bellatra::Bellatra()
{
}

#ifdef _W_SERVER
void Bellatra::GetClanName(const char* Nick, char* ClanName)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [ClanDB].[dbo].[UL] WHERE [ChName]='%s'", Nick);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(7, ClanName);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

int Bellatra::GetClanNamePoint(const char* ClanName)
{
	int Point = 0;
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [ClanDB].[dbo].[CL] WHERE [ClanName]='%s'", ClanName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(15, &Point);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	return Point;
}

void Bellatra::RecordClanPoint(const char* pszClanName, int iPoint, int iOldPoint)
{
	int ClanLeaderPoint = 0;
	char ClanName[32] = { 0 };

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT TOP 1 * FROM [ClanDB].[dbo].[CL] ORDER BY [Cpoint] DESC"))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, ClanName);
				SQL::GetInstance()->GetDataValue(15, &ClanLeaderPoint);
			}
		}

		wsprintf(szQuery, "UPDATE [ClanDB].[dbo].[CL] SET [Cpoint]=%d WHERE [ClanName] ='%s'", iPoint, pszClanName);

		SQL::GetInstance()->Execute(szQuery);

		SQL::GetInstance()->Execute("DELETE FROM [PristonDB].[dbo].[BellatraTeamScore]");

		SQL::GetInstance()->LeaveSqlSection();
	}

	if ((strcmp(ClanName, pszClanName) != 0) && iPoint > ClanLeaderPoint)
	{
		rsSendServerChatMessageToAllUser(3, "%s conquistaram o primeiro lugar no Bellatra com %d pontos!", pszClanName, iPoint);
	}
}
void Bellatra::UpdateClanCrownBellatra()
{
	return;
	int cnt = 0;
	int Code[3] = { 0, 0, 0 };

	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT TOP 3 * FROM [ClanDB].[dbo].[CL] ORDER BY [Cpoint] DESC"))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(9, &Code[cnt]);
				cnt++;
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
	smTRANS_COMMAND packet;
	packet.size = sizeof(smTRANS_COMMAND);
	packet.code = smTRANSCODE_UPDATE_BELLATRA;

	for (int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (rsPlayInfo[cnt].lpsmSock)
		{
			if (rsPlayInfo[cnt].dwClanCode == Code[0])
				packet.WParam = 1;
			else if (rsPlayInfo[cnt].dwClanCode == Code[1])
				packet.WParam = 2;
			else if (rsPlayInfo[cnt].dwClanCode == Code[2])
				packet.WParam = 3;
			else
				packet.WParam = 0;

			rsPlayInfo[cnt].lpsmSock->Send((char*)&packet, packet.size, TRUE);
		}
	}
}

void Bellatra::UpdateClanBellatra()
{
	char szCharName[32] = { 0 };
	char ClanName[32] = { 0 };
	char ClanName2[32] = { 0 };
	int Point = 0;
	int SODCODE = 0;
	int TotalPoint = 0;
	int SuccessUser = 0;
	int CurrentClanPoint = 0;
	int MinimalUserClanPoints = 1;
	int TotalPlayers = 0;
	char CharName2[32] = { 0 };

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512] = { 0 };
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT * FROM [PristonDB].[dbo].[BellatraTeamScore]"))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, szCharName);
				SQL::GetInstance()->GetDataValue(8, &TotalPoint);
				SQL::GetInstance()->GetDataValue(10, &SuccessUser);
				SQL::GetInstance()->GetDataValue(11, &SODCODE);

				if (TotalPoint > 0 || SuccessUser >= MinimalUserClanPoints)
				{
					GetClanName(szCharName, ClanName);
					CurrentClanPoint = GetClanNamePoint(ClanName);
					TotalPlayers = 1;
					wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[BellatraTeamScore] WHERE [SODCODE]=%d AND [TOTALPOINT]=%d AND [TOTALUSERSUCESS] =%d", SODCODE, TotalPoint, SuccessUser);
					if (SQL::GetInstance()->Execute(szQuery))
					{
						while (SQL::GetInstance()->Fetch())
						{
							CharName2[0] = '\0';

							SQL::GetInstance()->GetDataValue(2, CharName2);
							SQL::GetInstance()->GetDataValue(6, &Point);

							if (Point > 0)
							{
								GetClanName(CharName2, ClanName2);

								if (strcmp(ClanName, ClanName2) == 0)
								{
									TotalPlayers++;
								}
								else
								{
									TotalPoint -= Point;
								}
							}
						}

						if (TotalPlayers >= MinimalUserClanPoints && TotalPoint > CurrentClanPoint)
							RecordClanPoint(ClanName, TotalPoint, CurrentClanPoint);
					}
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	UpdateClanCrownBellatra();
}

int Bellatra::GetClanCodePoint(int CODECLAN)
{
	int Point = 0;
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[256];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [ClanDB].[dbo].[CL] WHERE [MIconCnt]=%d", CODECLAN);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(15, &Point);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	return Point;
}

void Bellatra::RecordPoint(rsPLAYINFO* lpPlayInfo, int Level, int SodScore, int KillCount, int TotalSodScore, int SodTotalUser, int SodTotalUserSucess, int SodCode)
{
	if (lpPlayInfo && SodScore > 0)
	{
		int ClanID = 0;
		int iID = 0;

		if (SQL::GetInstance()->IsConnected())
		{
			char szQuery[512];
			SQL::GetInstance()->EnterSqlSection();

			if (GetClanCodePoint(lpPlayInfo->dwClanCode) < TotalSodScore)
			{
				if (SodTotalUser >= 1)
				{
					wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[BellatraTeamScore] WHERE NICK='%s'", lpPlayInfo->smCharInfo.szName);
					SQL::GetInstance()->Execute(szQuery);
					wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[BellatraTeamScore] ([ID],[NICK],[JOBCODE],[NIVEL],[CLANCODE],[SCORE],[KILLS],[TOTALPOINT],[TOTALUSER],[TOTALUSERSUCESS],[SODCODE],[DATE]) VALUES ('%s','%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,GETDATE())",
						lpPlayInfo->szID, lpPlayInfo->smCharInfo.szName, lpPlayInfo->smCharInfo.JOB_CODE, lpPlayInfo->smCharInfo.Level, lpPlayInfo->dwClanCode, SodScore, KillCount, TotalSodScore, SodTotalUser, SodTotalUserSucess, SodCode);
					SQL::GetInstance()->Execute(szQuery);
				}

				wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[BellatraPersonalScore] WHERE [NICK]='%s'", lpPlayInfo->smCharInfo.szName);
				if (SQL::GetInstance()->Execute(szQuery))
				{
					if (SQL::GetInstance()->Fetch() && SodTotalUser == 1 && SodTotalUserSucess == 1)
					{
						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[BellatraPersonalScore] SET [KILLS] =%d, [SCORE] =%d, [DATE] = GETDATE()", KillCount, SodScore);
						SQL::GetInstance()->Execute(szQuery);
					}
					else if (SodTotalUser == 1 && SodTotalUserSucess == 1)
					{
						wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[BellatraPersonalScore] ([ID],[NICK],[KILLS],[SCORE],[DATE]) VALUES ('%s','%s',%d,%d,GETDATE())", lpPlayInfo->szID, lpPlayInfo->smCharInfo.szName, KillCount, SodScore);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
			}

			SQL::GetInstance()->LeaveSqlSection();
		}

		UpdateClanBellatra();
	}
}
#endif

Bellatra::~Bellatra()
{
}