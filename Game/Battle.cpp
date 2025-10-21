#include "sinbaram\sinLinkHeader.h"

int Battle::GetLevelByExp(int Exp)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		int Result = 0;
		char szQuery[512];
		wsprintf(szQuery, "SELECT TOP 1 Exp FROM [PristonDB].[dbo].[BattleGain_Killer] WHERE Exp >= %d ORDER BY Level DESC", Exp);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &Result);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
		return Result;
	}
}

void Battle::GetExpByCharacter(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "SELECT Exp FROM [PristonDB].[dbo].[Battle] WHERE Character=%s", Player->smCharInfo.szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &Player->BattleExp);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Battle::SaveExp(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "SELECT Exp FROM [PristonDB].[dbo].[Battle] WHERE Character=%s", Player->smCharInfo.szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Battle] SET Exp=%d WHERE Character='%s'", Player->BattleExp, Player->smCharInfo.szName);
				SQL::GetInstance()->Execute(szQuery);
			}
			else
			{
				wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[Battle] (Character,Exp) VALUES('%s',%d)", Player->smCharInfo.szName, Player->BattleExp);
				SQL::GetInstance()->Execute(szQuery);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}
int Battle::GetExpGainKiller(int LevelDifference)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		int Result = 0;
		char szQuery[512];
		wsprintf(szQuery, "SELECT TOP 1 Exp FROM [PristonDB].[dbo].[BattleGain_Killer] WHERE LevelDifference >= %d ORDER BY LevelDifference ASC", LevelDifference);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &Result);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
		return Result;
	}
}

int Battle::GetExpGainMurdered(int LevelDifference)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		int Result = 0;
		char szQuery[512];
		wsprintf(szQuery, "SELECT TOP 1 Exp FROM [PristonDB].[dbo].[BattleGain_Murdered] WHERE LevelDifference >= %d ORDER BY LevelDifference ASC", LevelDifference);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &Result);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
		return Result;
	}
}

int Battle::GetExpLoss(int BattleLevel)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		int Result = 0;
		char szQuery[512];
		wsprintf(szQuery, "SELECT TOP 1 Exp FROM [PristonDB].[dbo].[BattleGain_Killer] WHERE BattleLevel=%d", BattleLevel);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &Result);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
		return Result;
	}
}

void Battle::OnBattle(rsPLAYINFO* Killer, rsPLAYINFO* Murdered)
{
	int KillerLevel = Killer->smCharInfo.Level;
	int MurderedLevel = Murdered->smCharInfo.Level;
	int ExpGain = KillerLevel >= MurderedLevel ? GetExpGainKiller(KillerLevel - MurderedLevel) : GetExpGainMurdered(MurderedLevel - KillerLevel);
	int ExpLoss = GetExpLoss(Murdered->BattleLevel);
	Killer->BattleExp += ExpGain;
	Murdered->BattleExp -= Murdered->BattleExp > 0 ? ExpLoss : 0;
	Killer->BattleLevel = GetLevelByExp(Killer->BattleExp);
	Murdered->BattleLevel = GetLevelByExp(Murdered->BattleExp);
	Killer->Streak++;
	Murdered->Streak = 0;
	SaveExp(Killer);
	SaveExp(Murdered);
	SendBattleExp(Killer);
	SendBattleExp(Murdered);
}

void Battle::SendBattleExp(rsPLAYINFO* Player)
{
	smTRANS_COMMAND packet;
	packet.size = sizeof(smTRANS_COMMAND);
	packet.code = smTRANSCODE_BATTLE_EXP;
	packet.EParam = Player->BattleLevel;
	packet.LParam = Player->BattleExp;
	Player->lpsmSock->Send((char*)&packet, packet.size, true);
}

void Battle::RecvBattleExp(smTRANS_COMMAND* packet)
{
	Level = packet->EParam;
	Exp = packet->LParam;
}