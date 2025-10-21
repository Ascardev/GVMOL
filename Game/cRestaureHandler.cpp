#include "sinbaram/sinLinkHeader.h"
#include "cRestaureHandler.h"
#include "SrcServer/onserver.h"

cRESTAURE cRestaure;

extern int srSetItemFromLogData(psITEM* lpsItem, char* LogFileCode);

void cRESTAURE::InsertAgingFailed(rsPLAYINFO* lpPlayInfo, char* ItemName, int ItemAging, int Head, int dwChkSum)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[AgingFailed] ([PlayerID],[PlayerName],[ItemName],[ItemAging],[Head],[ChkSum],[Date]) values('%s','%s','%s',%d,%d,%d,GETDATE())", lpPlayInfo->szID, lpPlayInfo->szName, ItemName, ItemAging, Head, dwChkSum);
		SQL::GetInstance()->Execute(szQuery);
		SQL::GetInstance()->LeaveSqlSection();
	}
}

extern int CreateCommandItem(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, char* szItem);
extern int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

void cRESTAURE::RestaureItem(rsPLAYINFO* lpPlayInfo, DWORD Head, DWORD dwChkSum, int coinType, DWORD StoneCode, DWORD StoneHead, DWORD StoneSum)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		char szCode[32];

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[AgingFailed] WHERE PlayerID='%s' AND PlayerName='%s' AND Head=%d AND ChkSum=%d", lpPlayInfo->szID, lpPlayInfo->szName, Head, dwChkSum);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			char buff[255];
			wsprintf(buff, "%d@%d", Head, dwChkSum);

			psITEM psItem;
			if (srSetItemFromLogData(&psItem, buff))
			{
				bool canRestaure = false;

				int Price = 0;

				if (psItem.ItemInfo.ItemAgingNum[0] == 1)
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 2) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 3) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 4) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 5) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 6) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 7) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 8) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 9) // +10 pro +11
					Price = 1;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 10) // +10 pro +11
					Price = 100;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 11) // +10 pro +11
					Price = 200;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 12) // +11 pro +12
					Price = 300;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 13) // +12 pro +13
					Price = 500;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 14) //+13 pro +14
					Price = 600;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 15) //+14 pro +15
					Price = 700;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 16) //+15 pro +16
					Price = 800;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 17) //+16 pro +17
					Price = 900;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 18) //+17 pro +18
					Price = 1000;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 19) //+17 pro +18
					Price = 1100;
				else if (psItem.ItemInfo.ItemAgingNum[0] == 20) //+17 pro +18
					Price = 1200;
				else
					Price = 999999999;

				if (Price >= 0 && Price <= cCoinShop.GetUserCoin(lpPlayInfo))
				{
					canRestaure = true;
					cCoinShop.AddCoin(lpPlayInfo, -Price);
				}

				if (canRestaure)
				{
					if (SQL::GetInstance()->IsConnected())
					{
						char szQuery[512];
						SQL::GetInstance()->EnterSqlSection();
						wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[AgingFailed] WHERE [PlayerID]='%s' AND [PlayerName] ='%s'", lpPlayInfo->szID, lpPlayInfo->szName);
						if (SQL::GetInstance()->Execute(szQuery))
						{
							if (SQL::GetInstance()->Fetch())
							{
								wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[AgingFailed] WHERE [PlayerID]='%s' AND [PlayerName] ='%s' AND [Head] = %d AND [ChkSum] = %d", lpPlayInfo->szID, lpPlayInfo->szName, Head, dwChkSum);
								SQL::GetInstance()->Execute(szQuery);
							}
						}
						SQL::GetInstance()->LeaveSqlSection();
					}
					char buff2[255];
					wsprintf(buff2, "@%d@%d", Head, dwChkSum);
					CreateCommandItem(lpPlayInfo, lpPlayInfo, buff2);
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
	RecvGetRestaure(lpPlayInfo);
}

void cRESTAURE::RecvGetRestaure(rsPLAYINFO* lpPlayInfo)
{
	RESTAURE_LIST restaureList = {};

	cCoinShop.GetUserCoin(lpPlayInfo);

	restaureList.code = smTRANSCODE_RESTAURE_LIST;
	restaureList.size = sizeof(RESTAURE_LIST);

	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		char szCode[32];

		wsprintf(szQuery, "SELECT Head, ChkSum FROM [PristonDB].[dbo].[AgingFailed] WHERE PlayerID = '%s' AND PlayerName = '%s' ORDER BY Date DESC", lpPlayInfo->szID, lpPlayInfo->szName);

		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				DWORD Head, ChkSum;
				psITEM psItem;

				SQL::GetInstance()->GetDataValue(1, &Head);
				SQL::GetInstance()->GetDataValue(2, &ChkSum);

				char buff[500];
				wsprintf(buff, "%d@%d", Head, ChkSum);

				if (srSetItemFromLogData(&psItem, buff))
				{
					memcpy(&restaureList.ItemList[restaureList.Count].sItem, &psItem.ItemInfo, sizeof(sITEMINFO));
					restaureList.ItemList[restaureList.Count].sItem.ItemHeader.dwTime = 0;
					restaureList.ItemList[restaureList.Count].sItem.ItemHeader.dwVersion = 0;
					restaureList.ItemList[restaureList.Count].sItem.dwCreateTime = 0;

					if (psItem.ItemInfo.ItemAgingNum[0] == 1)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 2)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 3)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 4)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 5)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 6)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 7)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 8)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 9)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 10)
						restaureList.ItemList[restaureList.Count].CoinPrice = 100;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 11)
						restaureList.ItemList[restaureList.Count].CoinPrice = 200;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 12)
						restaureList.ItemList[restaureList.Count].CoinPrice = 300;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 13)
						restaureList.ItemList[restaureList.Count].CoinPrice = 500;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 14)
						restaureList.ItemList[restaureList.Count].CoinPrice = 600;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 15)
						restaureList.ItemList[restaureList.Count].CoinPrice = 700;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 16)
						restaureList.ItemList[restaureList.Count].CoinPrice = 800;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 17)
						restaureList.ItemList[restaureList.Count].CoinPrice = 900;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 18)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1000;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 19)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1100;
					else if (psItem.ItemInfo.ItemAgingNum[0] == 20)
						restaureList.ItemList[restaureList.Count].CoinPrice = 1200;
					else
						restaureList.ItemList[restaureList.Count].CoinPrice = 999999999;

					restaureList.Count++;

					if (restaureList.Count >= 15)
					{
						lpPlayInfo->lpsmSock->Send((char*)&restaureList, restaureList.size, TRUE);

						restaureList.Count = 0;
						ZeroMemory(&restaureList.ItemList, sizeof(sITEMINFO) * 15);
					}
				}
			}

			SQL::GetInstance()->LeaveSqlSection();
		}
		lpPlayInfo->lpsmSock->Send((char*)&restaureList, restaureList.size, TRUE);
	}
}