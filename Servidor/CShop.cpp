#include "sinbaram\sinLinkHeader.h"

CoinShop cCoinShop;

sDEF_ITEMINFO* DefaultItems;
int	DefaultItemCount;
int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
int	rsAddInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);
int SaveThrowItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum);
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
int SetAgingItem(sITEMINFO* pItem, int AgingNum);
void GetRemodel(DWORD Flag, DWORD Code, SWAPITEM* Swap);
int DisconnectUser(smWINSOCK* lpsmSock);

time_t	tServerTime;

ITEM_COIN_SHOP recv_items[500];
PACKET_COIN_SHOP_BUY cCPacket;

#define MAX_TAG 6

#define TAG_ACESSORIES 1
#define TAG_DEFENSE    2
#define TAG_WEAPONS    3
#define TAG_PREMIUM    4
#define TAG_FUN        5
#define TAG_SKIN       6

#define SUB_TAG_AMULETS    1
#define SUB_TAG_RINGS      2
#define SUB_TAG_SHELTOMS   3
#define SUB_TAG_FORCE_ORBS 4
#define SUB_TAG_BRACELETS  5
#define SUB_TAG_ORBS       6
#define SUB_TAG_ARMORS     7
#define SUB_TAG_ROBES      8
#define SUB_TAG_BOOTS      9
#define SUB_TAG_GAUNTLETS  10
#define SUB_TAG_SHIELDS    11
#define SUB_TAG_AXES       12
#define SUB_TAG_CLAWS      13
#define SUB_TAG_HAMMERS    14
#define SUB_TAG_WANDS      15
#define SUB_TAG_SCYTHES    16
#define SUB_TAG_BOWS       17
#define SUB_TAG_SWORD      18
#define SUB_TAG_JAVELINS   19
#define SUB_TAG_DAGGERS    20
#define SUB_TAG_PHANTOMS   21
#define SUB_TAG_GAUNTLETS  22

#define SUB_TAG_COMBATS    23
#define SUB_TAG_AGING      24
#define SUB_TAG_MIXING     25
#define SUB_TAG_GOLD       26
#define SUB_TAG_CRYSTALS   27
#define SUB_TAG_PETS       28
#define SUB_TAG_COSTUMES   29

DWORD AllowList[77] = { sinWA1 | sin29, sinWA1 | sin18, sinWA1 | sin86, sinWA1 | sin88, sinWA1 | sin22, sinWC1 | sin28, sinWC1 | sin86,
sinWC1 | sin22, sinWH1 | sin30, sinWH1 | sin86, sinWH1 | sin23, sinWM1 | sin30, sinWM1 | sin88, sinWM1 | sin23, sinWP1 | sin29, sinWP1 | sin86,
sinWP1 | sin23, sinWS1 | sin30, sinWS1 | sin86, sinWS1 | sin24, sinWS2 | sin32, sinWS2 | sin22, sinWS2 | sin86, sinWS2 | sin88, sinWS2 | sin25,
sinWT1 | sin29, sinWT1 | sin86, sinWT1 | sin23, sinWD1 | sin28, sinWD1 | sin86, sinWD1 | sin22, sinWN1 | sin28, sinWN1 | sin86, sinWN1 | sin22,
sinWV1 | sin29, sinWV1 | sin86, sinWV1 | sin23, sinOA2 | sin27, sinOA2 | sin86, sinOA2 | sin24, sinOM1 | sin25, sinOM1 | sin24, sinOM1 | sin23,
sinDA1 | sin29, sinDA1 | sin26, sinDA1 | sin24, sinOA1 | sin30, sinOA1 | sin24, sinOA1 | sin23, sinOR2 | sin01, sinOR1 | sin24, sinOR1 | sin23,
sinOS1 | sin24, sinOS1 | sin25, sinOS1 | sin26, sinDA2 | sin29, sinDA2 | sin26, sinDA2 | sin24, sinDB1 | sin27, sinDB1 | sin86, sinDB1 | sin24,
sinDG1 | sin27, sinDG1 | sin86, sinDG1 | sin24, sinDS1 | sin24, sinDS1 | sin86, sinDS1 | sin22
};

struct psITEM {
	int		state;
	int		Serial;

	sITEMINFO	ItemInfo;
};

int srSetItemFromCodeJobCode(psITEM* lpsItem, char* szCoed, int JobCode);

void DrawTexImage(int Mat, int x, int y, int w, int h, int specular)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, specular);
}

void CoinShop::SendList(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		int i = 0;
		char szQuery[512];
		PACKET_COIN_SHOP packet;
		ZeroMemory(&packet, sizeof(PACKET_COIN_SHOP));
		packet.size = sizeof(PACKET_COIN_SHOP);
		if (packet.size >= smSOCKBUFF_SIZE) packet.size = smSOCKBUFF_SIZE;
		packet.code = smTRANSCODE_SEND_COIN_SHOP_LIST;
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_List]");
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &packet.item.SubTag);
				SQL::GetInstance()->GetDataValue(2, packet.item.szCode);
				SQL::GetInstance()->GetDataValue(3, packet.item.szName);
				SQL::GetInstance()->GetDataValue(4, packet.item.Description1);
				SQL::GetInstance()->GetDataValue(5, packet.item.Description2);
				SQL::GetInstance()->GetDataValue(6, packet.item.Dir);
				SQL::GetInstance()->GetDataValue(7, &packet.item.Price);

				psITEM* Item = new psITEM;
				int JobCode = 1;
				if (strstr("WA1", packet.item.szCode))
					JobCode = 1;
				if (strstr("WC1", packet.item.szCode))
					JobCode = 2;
				if (strstr("WH1", packet.item.szCode))
					JobCode = 2;
				if (strstr("WP1", packet.item.szCode))
					JobCode = 4;
				if (strstr("WS1", packet.item.szCode))
					JobCode = 3;
				if (strstr("WS2", packet.item.szCode))
					JobCode = 6;
				if (strstr("WM1", packet.item.szCode))
					JobCode = 7;
				if (strstr("WT1", packet.item.szCode))
					JobCode = 5;
				if (strstr("WD1", packet.item.szCode))
					JobCode = 9;
				if (strstr("WN1", packet.item.szCode))
					JobCode = 10;
				if (strstr("WV1", packet.item.szCode))
					JobCode = 11;

				if (srSetItemFromCodeJobCode(Item, packet.item.szCode, JobCode))
				{
					memcpy(&packet.item.ItemInfo, &Item->ItemInfo, sizeof(sITEMINFO));
				}

				for (int cnt2 = 0; cnt2 < MAX_ITEM; cnt2++)
				{
					if (strcmp(sItem[cnt2].LastCategory, packet.item.szCode) == 0)
					{
						packet.item.Width = sItem[cnt2].w;
						packet.item.Height = sItem[cnt2].h;
						break;
					}
				}

				Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
				i++;

				if (i > 499) break;
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void CoinShop::SendCoin(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		smTRANS_COMMAND packet;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &packet.WParam);
				packet.size = sizeof(smTRANS_COMMAND);
				packet.code = smTRANSCODE_SEND_COIN_SHOP_COIN;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);

				PACKET_ITEM_CLASS ps2;
				ps2.size = sizeof(PACKET_ITEM_CLASS);
				ps2.code = smTRANSCODE_ITEM_CLASS;
				ps2.weapon = Player->WeaponClass;
				ps2.armor = Player->ArmorClass;
				ps2.shield = Player->ShieldClass;
				ps2.bracelets = Player->BraceletsClass;
				ps2.gauntlets = Player->GauntletsClass;
				ps2.boots = Player->BootsClass;
				ps2.ring = Player->RingClass;
				ps2.amy = Player->AmyClass;
				ps2.shel = Player->ShelClass;
				ps2.time = Player->TimeClass;
				Player->lpsmSock->Send((char*)&ps2, ps2.size, TRUE);
			}
			else
			{
				packet.size = sizeof(smTRANS_COMMAND);
				packet.code = smTRANSCODE_SEND_COIN_SHOP_COIN;
				packet.WParam = 0;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);

				PACKET_ITEM_CLASS ps2;
				ps2.size = sizeof(PACKET_ITEM_CLASS);
				ps2.code = smTRANSCODE_ITEM_CLASS;
				ps2.weapon = Player->WeaponClass;
				ps2.armor = Player->ArmorClass;
				ps2.shield = Player->ShieldClass;
				ps2.bracelets = Player->BraceletsClass;
				ps2.gauntlets = Player->GauntletsClass;
				ps2.boots = Player->BootsClass;
				ps2.ring = Player->RingClass;
				ps2.amy = Player->AmyClass;
				ps2.shel = Player->ShelClass;
				ps2.time = Player->TimeClass;
				Player->lpsmSock->Send((char*)&ps2, ps2.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void CoinShop::RecvItemClass(PACKET_ITEM_CLASS* packet)
{
	WeaponClass = packet->weapon;
	ArmorClass = packet->armor;
	ShieldClass = packet->shield;
	BraceletsClass = packet->bracelets;
	GauntletsClass = packet->gauntlets;
	BootsClass = packet->boots;
	RingClass = packet->ring;
	AmyClass = packet->amy;
	ShelClass = packet->shel;
	TimeClass = packet->time;
}

void CoinShop::Recv(PACKET_COIN_SHOP* packet)
{
	for (int cnt = 0; cnt < 500; cnt++)
	{
		if (!recv_items[cnt].Flag)
		{
			char szBuff[1024];
			memcpy(&recv_items[cnt], &packet->item, sizeof(ITEM_COIN_SHOP));

			if (lstrcmpi(recv_items[cnt].szCode, "VIP") == 0)
			{
				wsprintf(szBuff, "game\\images\\coin\\VIP.bmp");
			}
			else if (strcmpi(recv_items[cnt].szCode, "VIP Elite") == 0)
			{
				wsprintf(szBuff, "game\\images\\coin\\VIPG.bmp");
			}
			else if (strcmpi(recv_items[cnt].szCode, "Class") == 0)
			{
				wsprintf(szBuff, "game\\images\\coin\\Class.bmp");
			}
			else if (strcmpi(recv_items[cnt].szCode, "Class Item") == 0)
			{
				wsprintf(szBuff, "game\\images\\coin\\ClassItem.bmp");
			}
			else wsprintf(szBuff, "image\\sinimage\\items\\%s\\it%s.bmp", recv_items[cnt].Dir, recv_items[cnt].szCode);

			recv_items[cnt].Image = LoadDibSurfaceOffscreen(szBuff);
			if (recv_items[cnt].Image)
			{
				D3DSURFACE_DESC	Temp;
				recv_items[cnt].Image->GetLevelDesc(0, &Temp);
				recv_items[cnt].Width = Temp.Width;
				recv_items[cnt].Height = Temp.Height;
			}

			recv_items[cnt].Flag = true;
			break;
		}
	}
}

void CoinShop::RecvCoin(smTRANS_COMMAND* packet)
{
	Coin = packet->WParam;
}

BOOL CoinShop::CheckTradeCoin(rsPLAYINFO* Player, rsPLAYINFO* Player2, TRANS_TRADEITEMS* lpTransTradeItems)
{
	int UserCoin = 0;
	sTRADE	sTradeCoin;

	if (!Player || !Player2) return FALSE;

	DecodeCompress(lpTransTradeItems->TradeBuff, (BYTE*)&sTradeCoin);

	return TRUE;
}

int CoinShop::GetUserCoin(rsPLAYINFO* Player)
{
	int UserCoin = 0;

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &UserCoin);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	return UserCoin;
}

void CoinShop::SubCoin(rsPLAYINFO* Player, int Coin)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=Coin-%d WHERE [ID]='%s'", Coin, Player->szID);
				SQL::GetInstance()->Execute(szQuery);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void CoinShop::AddCoin(rsPLAYINFO* Player, int Coin)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=Coin+%d WHERE [ID]='%s'", Coin, Player->szID);
				SQL::GetInstance()->Execute(szQuery);
			}
			else
			{
				wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[CoinShop_Coin] ([ID],[Coin]) values('%s',%d)", Player->szID, Coin);
				SQL::GetInstance()->Execute(szQuery);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

BOOL CoinShop::TransferTradeCoin(rsPLAYINFO* Player, rsPLAYINFO* Player2, int nCoin)
{
	if (!Player || !Player2) return FALSE;

	if (Coin < 0)
	{
		//DisconnectUser(Player->lpsmSock);
		LOGEx("TradeCoin", "1:%s to %s", Player->smCharInfo.szName, Player2->smCharInfo.szName);
		return FALSE;
	}

	if (SQL::GetInstance()->IsConnected())
	{
		int UserCoin = 0, UserCoin2 = 0, ItemPrice = 0;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &UserCoin);
			}
		}

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", Player2->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &UserCoin2);
			}
			else
			{
				wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[CoinShop_Coin] ([ID],[Coin]) values('%s',%d)", Player2->szID, 0);
				SQL::GetInstance()->Execute(szQuery);
			}
		}

		if (!UserCoin || UserCoin < nCoin)
		{
			//DisconnectUser(Player->lpsmSock);
			LOGEx("TradeCoin", "2:%s to %s", Player->smCharInfo.szName, Player2->smCharInfo.szName);
			return FALSE;
		}
		else
		{
			LOGEx(Player, "TCoin", "Transfer %d Coins to %s", nCoin, Player2->szName);
			UserCoin -= nCoin;
			UserCoin2 += nCoin;
			wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=%d WHERE [ID]='%s'", UserCoin, Player->szID);
			SQL::GetInstance()->Execute(szQuery);
			wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=%d WHERE [ID]='%s'", UserCoin2, Player2->szID);
			SQL::GetInstance()->Execute(szQuery);
			SendCoin(Player);
			SendCoin(Player2);
		}

		SQL::GetInstance()->LeaveSqlSection();
	}

	return TRUE;
}

void CoinShop::PlusCoin(int Coin)
{
	Coin += Coin;
}

void CoinShop::MinusCoin(int Coin)
{
	Coin -= Coin;
}

void CoinShop::RecvPVIP(PACKET_RECV_VIP* packet)
{
	if (packet->dwTime_PrimeItem_VIP > 0)
	{
		PVIP = packet->dwParam_PrimeItem_VIP;
		chaPremiumitem.SetVipTime(packet->dwTime_PrimeItem_VIP);
		chaPremiumitem.SetUpKeepItem(nsPremiumItem::VIP, chaPremiumitem.m_VipTime, true, UpKeepItemName[13 + PVIP], 30);
	}
}

void GetItemMixture(int MixNum, sITEM* lpsItem)
{
	int i = MixNum;
	for (int k = 0; k < 12; k++)
	{
		if (sCraftItem_Info[i].PlusElementCode[k])
		{
			switch (sCraftItem_Info[i].PlusElementCode[k])
			{
			case SIN_ADD_FIRE:
				lpsItem->sItemInfo.Resistance[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_FIRE;

				break;
			case SIN_ADD_ICE:
				lpsItem->sItemInfo.Resistance[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ICE;
				break;
			case SIN_ADD_LIGHTNING:
				lpsItem->sItemInfo.Resistance[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_LIGHTNING;
				break;

			case SIN_ADD_POISON:
				lpsItem->sItemInfo.Resistance[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_POISON;
				break;
			case SIN_ADD_BIO:
				lpsItem->sItemInfo.Resistance[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_BIO;
				break;
			case SIN_ADD_CRITICAL:
				lpsItem->sItemInfo.Critical_Hit += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_CRITICAL;
				break;
			case SIN_ADD_ATTACK_RATE:
				lpsItem->sItemInfo.Attack_Rating += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ATTACK_RATE;
				break;
			case SIN_ADD_DAMAGE_MIN:

				lpsItem->sItemInfo.Damage[0] += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MIN;
				break;

			case SIN_ADD_DAMAGE_MAX:

				lpsItem->sItemInfo.Damage[1] += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MAX;
				break;
			case SIN_ADD_ATTACK_SPEED:

				lpsItem->sItemInfo.Attack_Speed += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ATTACK_SPEED;
				break;
			case SIN_ADD_ABSORB:

				lpsItem->sItemInfo.fAbsorb += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ABSORB;
				break;
			case SIN_ADD_DEFENCE:

				lpsItem->sItemInfo.Defence += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_DEFENCE;
				break;
			case SIN_ADD_BLOCK_RATE:

				lpsItem->sItemInfo.fBlock_Rating += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_BLOCK_RATE;
				break;
			case SIN_ADD_MOVE_SPEED:

				lpsItem->sItemInfo.fSpeed += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_MOVE_SPEED;
				break;

			case SIN_ADD_LIFE:

				lpsItem->sItemInfo.fIncrease_Life += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_LIFE;
				break;

			case SIN_ADD_MANA:

				lpsItem->sItemInfo.fIncrease_Mana += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_MANA;
				break;
			case SIN_ADD_STAMINA:

				lpsItem->sItemInfo.fIncrease_Stamina += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_STAMINA;
				break;
			case SIN_ADD_LIFEREGEN:

				lpsItem->sItemInfo.fLife_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_LIFEREGEN;
				break;
			case SIN_ADD_MANAREGEN:

				lpsItem->sItemInfo.fMana_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_MANAREGEN;

				break;
			case SIN_ADD_STAMINAREGEN:

				lpsItem->sItemInfo.fStamina_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_STAMINAREGEN;

				break;
			}
		}
	}
}

void CoinShop::RecvItemOnServer(rsPLAYINFO* Player, PACKET_SEND_ITEM* packet)
{
	int ErrorFlag = 0;

	if (packet->sItem.sItemInfo.CODE)
	{
		if (rsDeleteInvenItem(Player, packet->sItem.sItemInfo.CODE,
			packet->sItem.sItemInfo.ItemHeader.Head, packet->sItem.sItemInfo.ItemHeader.dwChkSum) < 0)
		{
			ErrorFlag++;
			packet->sItem.sItemInfo.CODE = 0;
		}

		SaveThrowItem(Player, packet->sItem.sItemInfo.CODE,
			packet->sItem.sItemInfo.ItemHeader.Head, packet->sItem.sItemInfo.ItemHeader.dwChkSum);
	}

	switch (packet->sItem.sItemInfo.CODE & sinITEM_MASK2)
	{
	case sinDA1:
	case sinDA2:
	case sinDA3:
	case sinDA4:
		if (Player->ArmorClass)
			Player->ArmorClass--;
		else
			ErrorFlag++;
		break;
	case sinDS1:
	case sinOM1:
		if (Player->ShieldClass)
			Player->ShieldClass--;
		else
			ErrorFlag++;
		break;
	case sinOA2:
		if (Player->BraceletsClass)
			Player->BraceletsClass--;
		else
			ErrorFlag++;
		break;
	case sinDG1:
		if (Player->GauntletsClass)
			Player->GauntletsClass--;
		else
			ErrorFlag++;
		break;
	case sinDB1:
		if (Player->BootsClass)
			Player->BootsClass--;
		else
			ErrorFlag++;
		break;
	case sinOA1:
		if (Player->AmyClass)
			Player->AmyClass--;
		else
			ErrorFlag++;
		break;
	case sinOR1:
	case sinOR2:
		if (Player->RingClass)
			Player->RingClass--;
		else
			ErrorFlag++;
		break;
	case sinOS1:
		if (Player->ShelClass)
			Player->ShelClass--;
		else
			ErrorFlag++;
		break;
	case sinWA1:
	case sinWC1:
	case sinWH1:
	case sinWM1:
	case sinWP1:
	case sinWS1:
	case sinWS2:
	case sinWT1:
	case sinWD1:
	case sinWN1:
	case sinWV1:
		if (Player->WeaponClass)
			Player->WeaponClass--;
		else
			ErrorFlag++;
		break;
	}

	if (Player->TimeClass < tServerTime) ErrorFlag++;

	if (packet->spec <= 0 && packet->spec > 11) ErrorFlag++;

	if (!ErrorFlag)
	{
		DWORD Code = 0;
		int Kind = packet->sItem.sItemInfo.ItemKindCode;
		int AgingNum = packet->sItem.sItemInfo.ItemAgingNum[0];
		DWORD SwapFlag = packet->sItem.sItemInfo.SwapItem.Flag;
		DWORD SwapCode = packet->sItem.sItemInfo.SwapItem.Code;

		DWORD RecvCode = packet->sItem.sItemInfo.SwapItem.Flag ? packet->sItem.sItemInfo.SwapItem.Code : packet->sItem.sItemInfo.CODE;

		switch (RecvCode & sinITEM_MASK2)
		{
		case sinDA1:
		case sinDA2:
			if (packet->weapon == 1) Code += sinDA1;
			if (packet->weapon == 2) Code += sinDA2;
			Code += RecvCode & sinITEM_MASK3;
			break;
		case sinDA3:
		case sinDA4:
			if (packet->weapon == 1) Code += sinDA3;
			if (packet->weapon == 2) Code += sinDA4;
			Code += RecvCode & sinITEM_MASK3;
			break;
		case sinDS1:
		case sinOM1:
			if (packet->weapon == 1) Code += sinDS1;
			if (packet->weapon == 2) Code += sinOM1;
			Code += RecvCode & sinITEM_MASK3;
			break;
		case sinOA2:
		case sinDG1:
		case sinDB1:
		case sinOA1:
		case sinOR1:
		case sinOR2:
		case sinOS1:
			Code = RecvCode;
			break;
		case sinWA1:
		case sinWC1:
		case sinWH1:
		case sinWM1:
		case sinWP1:
		case sinWS1:
		case sinWS2:
		case sinWT1:
		case sinWD1:
		case sinWN1:
		case sinWV1:

			DWORD Dragon[11] = { sinWA1 | sin22, sinWC1 | sin22, sinWH1 | sin23, sinWM1 | sin23, sinWS1 | sin24, sinWS2 | sin25, sinWP1 | sin23, sinWT1 | sin23, sinWD1 | sin22, sinWN1 | sin22, sinWV1 | sin23 };

			DWORD Mitologic[11] = { sinWA1 | sin86, sinWC1 | sin86, sinWH1 | sin86, sinWM1 | sin86, sinWS1 | sin86, sinWS2 | sin88, sinWP1 | sin86, sinWT1 | sin86, sinWD1 | sin86, sinWN1 | sin86, sinWV1 | sin86 };

			DWORD Flame[11] = { sinWA1 | sin29, sinWC1 | sin28, sinWH1 | sin30, sinWM1 | sin30, sinWS1 | sin30, sinWS2 | sin32, sinWP1 | sin29, sinWT1 | sin29, sinWD1 | sin28, sinWN1 | sin28, sinWV1 | sin29 };

			//DWORD North[11] = {  };

			//DWORD Morghulis[14] = {  };

			for (int cnt = 0; cnt < 11; cnt++)
			{
				if (Dragon[cnt] == packet->sItem.sItemInfo.CODE || Dragon[cnt] == SwapCode)
				{
					Code = Dragon[packet->weapon - 1];
					break;
				}
			}

			for (int cnt = 0; cnt < 11; cnt++)
			{
				if (Mitologic[cnt] == packet->sItem.sItemInfo.CODE || Mitologic[cnt] == SwapCode)
				{
					Code = Mitologic[packet->weapon - 1];
					break;
				}
			}

			for (int cnt = 0; cnt < 11; cnt++)
			{
				if (Flame[cnt] == packet->sItem.sItemInfo.CODE || Flame[cnt] == SwapCode)
				{
					Code = Flame[packet->weapon - 1];
					break;
				}
			}

			//for (int cnt = 0; cnt < 11; cnt++)
			//{
			//	if (North[cnt] == packet->sItem.sItemInfo.CODE || North[cnt] == SwapCode)
			//	{
			//		Code = North[packet->weapon - 1];
			//		break;
			//	}
			//}

			//for (int cnt = 0; cnt < 11; cnt++)
			//{
			//	if (Morghulis[cnt] == packet->sItem.sItemInfo.CODE || Morghulis[cnt] == SwapCode)
			//	{
			//		Code = Morghulis[packet->weapon - 1];
			//		break;
			//	}
			//}

			break;
		}

		int Flag = 0;

		for (int cnt = 0; cnt < DefaultItemCount; cnt++)
		{
			if (DefaultItems[cnt].Item.CODE == Code && !DefaultItems[cnt].Item.UniqueItem)
			{
				CreateDefItemPerf(&packet->sItem.sItemInfo, &DefaultItems[cnt], packet->spec);
				Flag++;
				break;
			}
		}

		if (SwapFlag && Flag)
		{
			GetRemodel(SwapFlag, Code, &packet->sItem.sItemInfo.SwapItem);
			packet->sItem.sItemInfo.CODE = packet->sItem.sItemInfo.SwapItem.Code;
			packet->sItem.sItemInfo.SwapItem.Code = Code;
		}

		if (Kind == ITEM_KIND_AGING && Flag)
		{
			SetAgingItem(&packet->sItem.sItemInfo, AgingNum);
		}

		if (Kind == ITEM_KIND_CRAFT && Flag)
		{
			int MixNum = 0;

			switch (Code & sinITEM_MASK2)
			{
			case sinDA1:
			case sinDA2:
			case sinDA3:
			case sinDA4:
				switch (AgingNum)
				{
				case 10:
					MixNum = 2;
					break;
				case 13:
					MixNum = 13;
					break;
				case 1:
					MixNum = 24;
					break;
				}
				break;
			case sinDS1:
			case sinOM1:
				switch (AgingNum)
				{
				case 10:
					MixNum = 3;
					break;
				case 13:
					MixNum = 14;
					break;
				case 1:
					MixNum = 25;
					break;
				}
				break;
			case sinOA2:
				switch (AgingNum)
				{
				case 10:
					MixNum = 5;
					break;
				case 13:
					MixNum = 16;
					break;
				case 1:
					MixNum = 27;
					break;
				}
				break;
			case sinDG1:
				switch (AgingNum)
				{
				case 10:
					MixNum = 6;
					break;
				case 13:
					MixNum = 17;
					break;
				case 1:
					MixNum = 28;
					break;
				}
				break;
			case sinDB1:
				switch (AgingNum)
				{
				case 10:
					MixNum = 7;
					break;
				case 13:
					MixNum = 18;
					break;
				case 1:
					MixNum = 29;
					break;
				}
				break;
			case sinOA1:
				switch (AgingNum)
				{
				case 10:
					MixNum = 9;
					break;
				case 13:
					MixNum = 20;
					break;
				case 1:
					MixNum = 31;
					break;
				}
				break;
			case sinOR1:
			case sinOR2:
				switch (AgingNum)
				{
				case 10:
					MixNum = 8;
					break;
				case 13:
					MixNum = 19;
					break;
				case 1:
					MixNum = 30;
					break;
				}
				break;
			case sinOS1:
				switch (AgingNum)
				{
				case 10:
					MixNum = 10;
					break;
				case 13:
					MixNum = 21;
					break;
				case 1:
					MixNum = 32;
					break;
				}
				break;
			case sinWA1:
			case sinWC1:
			case sinWH1:
			case sinWM1:
			case sinWP1:
			case sinWS1:
			case sinWS2:
			case sinWT1:
				switch (AgingNum)
				{
				case 10:
					MixNum = 0;
					break;
				case 13:
					MixNum = 11;
					break;
				case 1:
					MixNum = 22;
					break;
				}
				break;

			case sinWD1:
			case sinWN1:
			case sinWV1:
				switch (AgingNum)
				{
				case 10:
					MixNum = 1;
					break;
				case 13:
					MixNum = 12;
					break;
				case 1:
					MixNum = 23;
					break;
				}
				break;
			}
			GetItemMixture(MixNum, &packet->sItem);
			packet->sItem.sItemInfo.ItemKindCode = Kind;
			packet->sItem.sItemInfo.ItemAgingNum[0] = AgingNum;
		}

		ReformItem(&packet->sItem.sItemInfo);

		rsAddInvenItem(Player, packet->sItem.sItemInfo.CODE,
			packet->sItem.sItemInfo.ItemHeader.Head, packet->sItem.sItemInfo.ItemHeader.dwChkSum);

		packet->result = true;

		char szCode1[256];
		char szCode2[256];
		itoa(packet->sItem.sItemInfo.CODE, szCode1, 16);
		itoa(Code, szCode2, 16);
		LOGEx(Player, "ChangeItem", "Changed OldCode:%s,NowCode:%s,ItemType:%d,Spec:%d", szCode1, szCode2, packet->weapon, packet->spec);
	}

	if (Player && Player->lpsmSock)
	{
		if (ErrorFlag)
		{
			ZeroMemory(&packet->sItem, sizeof(sITEM));
			packet->result = false;
		}

		Player->lpsmSock->Send2((char*)packet, packet->size, TRUE);

		PACKET_ITEM_CLASS ps2;
		ps2.size = sizeof(PACKET_ITEM_CLASS);
		ps2.code = smTRANSCODE_ITEM_CLASS;
		ps2.weapon = Player->WeaponClass;
		ps2.armor = Player->ArmorClass;
		ps2.shield = Player->ShieldClass;
		ps2.bracelets = Player->BraceletsClass;
		ps2.gauntlets = Player->GauntletsClass;
		ps2.boots = Player->BootsClass;
		ps2.ring = Player->RingClass;
		ps2.amy = Player->AmyClass;
		ps2.shel = Player->ShelClass;
		ps2.time = Player->TimeClass;
		Player->lpsmSock->Send((char*)&ps2, ps2.size, TRUE);
	}
}

void CoinShop::RecvItemOnGame(PACKET_SEND_ITEM* packet)
{
	sITEM TempItem;

	if (LoadItemImage(&packet->sItem.sItemInfo, &TempItem))
	{
		if (cInvenTory.CheckRequireItemToSet(&TempItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
			{
				sinThrowItemToFeild(&packet->sItem);
			}
		}
	}

	CheckCharForm();
	ReformCharForm();
	SendSaveMoney();
	SaveGameData();

	cInvenTory.DeleteInvenItemToServer(packet->sItem.sItemInfo.CODE, packet->sItem.sItemInfo.BackUpKey, packet->sItem.sItemInfo.BackUpChkSum);
	ZeroMemory(&sItemChange, sizeof(sITEM));

	ResetInvenItemCode();
	SaveGameData();
}

void CoinShop::SendItemToServer()
{
	if (TimeClass < GetPlayTime_T())
	{
		cMessageBox.ShowMessageEvent("Suas fichas já expiraram!");
		return;
	}

	switch (sItemChange.sItemInfo.CODE & sinITEM_MASK2)
	{
	case sinDA1:
	case sinDA2:
	case sinDA3:
	case sinDA4:
		if (ArmorClass)
			ArmorClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinDS1:
	case sinOM1:
		if (ShieldClass)
			ShieldClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinOA2:
		if (BraceletsClass)
			BraceletsClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinDG1:
		if (GauntletsClass)
			GauntletsClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinDB1:
		if (BootsClass)
			BootsClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinOA1:
		if (AmyClass)
			AmyClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinOR1:
	case sinOR2:
		if (RingClass)
			RingClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinOS1:
		if (ShelClass)
			ShelClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	case sinWA1:
	case sinWC1:
	case sinWH1:
	case sinWM1:
	case sinWP1:
	case sinWS1:
	case sinWS2:
	case sinWT1:
	case sinWD1:
	case sinWN1:
	case sinWV1:
		if (WeaponClass)
			WeaponClass--;
		else
		{
			cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
			return;
		}
		break;
	}

	PACKET_SEND_ITEM ps;
	ps.size = sizeof(PACKET_SEND_ITEM);
	ps.code = smTRANSCODE_SEND_CHANGE_ITEM;
	ps.spec = SpecItem;
	ps.weapon = ClassType;
	memcpy(&ps.sItem, &sItemChange, sizeof(sITEM));

	smWINSOCK* lpsmSock;
	lpsmSock = GetAreaServerSock();

	if (lpsmSock)
	{
		lpsmSock->Send((char*)&ps, ps.size, TRUE);
	}
}

void CoinShop::RecvBuyItem(rsPLAYINFO* Player, PACKET_COIN_SHOP_BUY* packet)
{
	if (packet->cnt < 0 && strlen(packet->szCode) > 42)
		return;

	if (SQL::GetInstance()->IsConnected())
	{
		int UserCoin = 0, ItemPrice = 0;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &UserCoin);
			}
			else
			{
				return;
			}
		}

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_List] WHERE [szCode]='%s'", packet->szCode);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(7, &ItemPrice);
			}
			else
			{
				return;
			}
		}

		ItemPrice = ItemPrice * packet->cnt;

		if (lstrcmpi(packet->szCode, "VIP") == 0 || lstrcmpi(packet->szCode, "VIP Elite") == 0)
		{
			if (Player->dwTime_PrimeItem_VIP)
			{
				PACKET_RECV_VIP packet;
				packet.size = sizeof(PACKET_RECV_VIP);
				packet.code = smTRANSCODE_RECV_VIP;
				packet.dwParam_PrimeItem_VIP = Player->dwParam_PrimeItem_VIP;
				packet.dwTime_PrimeItem_VIP = Player->dwTime_PrimeItem_VIP;
				Player->lpsmSock->Send((char*)&packet, packet.size, true);
				SQL::GetInstance()->LeaveSqlSection();
				return;
			}

			switch (packet->spec)
			{
			case 1:
				ItemPrice *= 2;
				break;
			case 2:
				ItemPrice *= 5;
				break;
			}
		}

		if (UserCoin >= ItemPrice)
		{
			int OldCoin = UserCoin;
			UserCoin -= ItemPrice;

			wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[CoinShop_Coin] SET Coin=%d WHERE [ID]='%s'", UserCoin, Player->szID);
			SQL::GetInstance()->Execute(szQuery);
			SendCoin(Player);

			if (lstrcmpi(packet->szCode, "VIP") == 0)
			{
				switch (packet->spec)
				{
				case 0:
					Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24;
					break;
				case 1:
					Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24 * 7;
					break;
				case 2:
					Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24 * 30;
					break;
				}
				Player->dwParam_PrimeItem_VIP = 1;

				PACKET_RECV_VIP packet;
				packet.size = sizeof(PACKET_RECV_VIP);
				packet.code = smTRANSCODE_RECV_VIP;
				packet.dwParam_PrimeItem_VIP = Player->dwParam_PrimeItem_VIP;
				packet.dwTime_PrimeItem_VIP = Player->dwTime_PrimeItem_VIP;
				Player->lpsmSock->Send((char*)&packet, packet.size, true);
			}
			else if (lstrcmpi(packet->szCode, "VIP Elite") == 0)
			{
				switch (packet->spec)
				{
				case 0:
					Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24;
					Player->dwTime_PrimeItem_ExpUp = 60 * 60 * 24;
					Player->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_50_EXPUP;
					break;
				case 1:
					Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24 * 7;
					Player->dwTime_PrimeItem_ExpUp = 60 * 60 * 24 * 7;
					Player->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_50_EXPUP;
					break;
				case 2:
					Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24 * 30;
					Player->dwTime_PrimeItem_ExpUp = 60 * 60 * 24 * 30;
					Player->dwPrimeItem_PackageCode = PRIME_ITEM_PACKAGE_NONE_50_EXPUP;
					break;
				}
				Player->dwParam_PrimeItem_VIP = 2;

				PACKET_RECV_VIP packet;
				packet.size = sizeof(PACKET_RECV_VIP);
				packet.code = smTRANSCODE_RECV_VIP;
				packet.dwParam_PrimeItem_VIP = Player->dwParam_PrimeItem_VIP;
				packet.dwTime_PrimeItem_VIP = Player->dwTime_PrimeItem_VIP;
				Player->lpsmSock->Send((char*)&packet, packet.size, true);
			}
			else if (lstrcmpi(packet->szCode, "Class") == 0)
			{
				PACKET_SET_CLASS ps;
				ps.size = sizeof(PACKET_SET_CLASS);
				ps.code = smTRANSCODE_SET_CLASS;
				ps.Class = packet->spec;
				Player->smCharInfo.JOB_CODE = packet->spec;

				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[Battle] SET Class=%d WHERE [Character]='%s'", packet->spec, Player->szName);
				SQL::GetInstance()->Execute(szQuery);

				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[LevelList] SET Class=%d WHERE [Character]='%s'", packet->spec, Player->szName);
				SQL::GetInstance()->Execute(szQuery);

				Player->lpsmSock->Send((char*)&ps, packet->size, TRUE);
				Player->WeaponClass = 1;
				Player->ArmorClass = 1;
				Player->ShieldClass = 1;
				Player->BraceletsClass = 1;
				Player->GauntletsClass = 1;
				Player->BootsClass = 1;
				Player->RingClass = 2;
				Player->AmyClass = 1;
				Player->ShelClass = 1;
				Player->TimeClass = ((DWORD)tServerTime) + 60 * 60 * 5;
				PACKET_ITEM_CLASS ps2;
				ps2.size = sizeof(PACKET_ITEM_CLASS);
				ps2.code = smTRANSCODE_ITEM_CLASS;
				ps2.weapon = Player->WeaponClass;
				ps2.armor = Player->ArmorClass;
				ps2.shield = Player->ShieldClass;
				ps2.bracelets = Player->BraceletsClass;
				ps2.gauntlets = Player->GauntletsClass;
				ps2.boots = Player->BootsClass;
				ps2.ring = Player->RingClass;
				ps2.amy = Player->AmyClass;
				ps2.shel = Player->ShelClass;
				ps2.time = Player->TimeClass;
				Player->lpsmSock->Send((char*)&ps2, ps2.size, TRUE);
			}
			else
			{
				for (int cnt = 0; cnt < packet->cnt; cnt++)
				{
					SendItemToPlayer(Player, packet->szCode, packet->spec);
				}
			}

			LOGEx(Player, "CShop", "Buyed szCode:%s,Quantity:%d,Spec:%d,OldCoin:%d,NowCoin:%d", packet->szCode, packet->cnt, packet->spec, OldCoin, UserCoin);
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void CoinShop::Init()
{
	IMG_TAG[0] = CreateTextureMaterial("game\\images\\coin\\tabs\\accessories.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[1] = CreateTextureMaterial("game\\images\\coin\\tabs\\defence.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[2] = CreateTextureMaterial("game\\images\\coin\\tabs\\weapons.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[3] = CreateTextureMaterial("game\\images\\coin\\tabs\\premium.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[4] = CreateTextureMaterial("game\\images\\coin\\tabs\\fun.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[5] = CreateTextureMaterial("game\\images\\coin\\tabs\\skin.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	IMG_TAGH[0] = CreateTextureMaterial("game\\images\\coin\\tabs\\accessories_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[1] = CreateTextureMaterial("game\\images\\coin\\tabs\\defence_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[2] = CreateTextureMaterial("game\\images\\coin\\tabs\\weapons_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[3] = CreateTextureMaterial("game\\images\\coin\\tabs\\premium_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[4] = CreateTextureMaterial("game\\images\\coin\\tabs\\fun_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[5] = CreateTextureMaterial("game\\images\\coin\\tabs\\skin_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	cImages[0] = CreateTextureMaterial("game\\images\\coin\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[1] = CreateTextureMaterial("game\\images\\coin\\coinshoplogo.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[2] = CreateTextureMaterial("game\\images\\coin\\button_coinholder.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[3] = CreateTextureMaterial("game\\images\\coin\\button_close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[4] = CreateTextureMaterial("game\\images\\coin\\button_close_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[15] = CreateTextureMaterial("game\\images\\coin\\line_big.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[16] = CreateTextureMaterial("game\\images\\coin\\line_small.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[17] = CreateTextureMaterial("game\\images\\coin\\window2_list.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[18] = CreateTextureMaterial("game\\images\\coin\\itemlistlogo.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[19] = CreateTextureMaterial("game\\images\\coin\\line_list.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[20] = CreateTextureMaterial("game\\images\\coin\\window2_button_close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[21] = CreateTextureMaterial("game\\images\\coin\\window2_button_close_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[23] = CreateTextureMaterial("game\\images\\coin\\window2_item.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[24] = CreateTextureMaterial("game\\images\\coin\\itemdetailslogo.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[25] = CreateTextureMaterial("game\\images\\coin\\window2_button_back.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[26] = CreateTextureMaterial("game\\images\\coin\\window2_button_back_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[27] = CreateTextureMaterial("game\\images\\coin\\window2_button_buy.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[28] = CreateTextureMaterial("game\\images\\coin\\window2_button_buy_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[29] = CreateTextureMaterial("game\\images\\coin\\spec_box.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[30] = CreateTextureMaterial("game\\images\\coin\\spec_box_on.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[31] = CreateTextureMaterial("game\\images\\coin\\spec_box_down1.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[32] = CreateTextureMaterial("game\\images\\coin\\spec_box_down2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[33] = CreateTextureMaterial("game\\images\\coin\\spec_box_down3.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[34] = CreateTextureMaterial("game\\images\\coin\\spec_box_down_select.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[35] = CreateTextureMaterial("game\\images\\coin\\spec_box_down_select_bottom.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[36] = CreateTextureMaterial("game\\images\\coin\\counter.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[37] = CreateTextureMaterial("game\\images\\coin\\counter_down.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[38] = CreateTextureMaterial("game\\images\\coin\\counter_up.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[39] = CreateTextureMaterial("game\\images\\coin\\counter_down_minreached.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[40] = CreateTextureMaterial("game\\images\\coin\\counter_up_maxreached.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[41] = CreateTextureMaterial("game\\images\\settings\\checkbox.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[42] = CreateTextureMaterial("game\\images\\settings\\checkbox_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[43] = CreateTextureMaterial("game\\images\\coin\\scrollbar_long.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[44] = CreateTextureMaterial("game\\images\\coin\\scroller.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[45] = CreateTextureMaterial("game\\images\\coin\\items\\upgrade_item.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[46] = CreateTextureMaterial("game\\images\\coin\\scrollbar.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[47] = CreateTextureMaterial("game\\images\\coin\\coin.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	bImages[0] = LoadDibSurfaceOffscreen("game\\images\\coin\\itembox.bmp");
	bImages[1] = LoadDibSurfaceOffscreen("game\\images\\coin\\WeaponToken.png");
	bImages[2] = LoadDibSurfaceOffscreen("game\\images\\coin\\ArmorToken.png");
	bImages[3] = LoadDibSurfaceOffscreen("game\\images\\coin\\ShieldToken.png");
	bImages[4] = LoadDibSurfaceOffscreen("game\\images\\coin\\BracersToken.png");
	bImages[5] = LoadDibSurfaceOffscreen("game\\images\\coin\\GlovesToken.png");
	bImages[6] = LoadDibSurfaceOffscreen("game\\images\\coin\\BootsToken.png");
	bImages[7] = LoadDibSurfaceOffscreen("game\\images\\coin\\RingToken.png");
	bImages[8] = LoadDibSurfaceOffscreen("game\\images\\coin\\AmyToken.png");
	bImages[9] = LoadDibSurfaceOffscreen("game\\images\\coin\\ShelToken.png");

	IMG_SUB_TAG[0] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\amulets.bmp");
	IMG_SUB_TAG[1] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\rings.bmp");
	IMG_SUB_TAG[2] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\sheltoms.bmp");
	IMG_SUB_TAG[3] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\forceorbs.bmp");
	IMG_SUB_TAG[4] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\brincos.bmp");
	IMG_SUB_TAG[5] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\bracelets.bmp");
	IMG_SUB_TAG[6] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\orbs.bmp");
	IMG_SUB_TAG[7] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\armors.bmp");
	IMG_SUB_TAG[8] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\robes.bmp");
	IMG_SUB_TAG[9] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\boots.bmp");
	IMG_SUB_TAG[10] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gauntlets.bmp");
	IMG_SUB_TAG[11] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\shields.bmp");
	IMG_SUB_TAG[12] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\axes.bmp");
	IMG_SUB_TAG[13] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\claws.bmp");
	IMG_SUB_TAG[14] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\hammers.bmp");
	IMG_SUB_TAG[15] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\wands.bmp");
	IMG_SUB_TAG[16] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\scythes.bmp");
	IMG_SUB_TAG[17] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\bows.bmp");
	IMG_SUB_TAG[18] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\swords.bmp");
	IMG_SUB_TAG[19] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\javelins.bmp");
	IMG_SUB_TAG[20] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\daggers.bmp");
	IMG_SUB_TAG[21] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\phantoms.bmp");
	IMG_SUB_TAG[22] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gauntlets.bmp");

	IMG_SUB_TAG[23] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\combat.bmp");
	IMG_SUB_TAG[24] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\aging.bmp");
	IMG_SUB_TAG[25] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\mixing.bmp");
	IMG_SUB_TAG[26] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gold.bmp");
	IMG_SUB_TAG[27] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\crystals.bmp");
	IMG_SUB_TAG[28] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\pets.bmp");
	IMG_SUB_TAG[29] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumes.bmp");
	IMG_SUB_TAG[30] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumesmg.bmp");
	IMG_SUB_TAG[31] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\axes.bmp");
	IMG_SUB_TAG[32] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\armors.bmp");
	IMG_SUB_TAG[33] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\shields.bmp");
	IMG_SUB_TAG[34] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\claws.bmp");
	IMG_SUB_TAG[35] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\hammers.bmp");
	IMG_SUB_TAG[36] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\wands.bmp");
	IMG_SUB_TAG[37] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\scythes.bmp");
	IMG_SUB_TAG[38] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\bows.bmp");
	IMG_SUB_TAG[39] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\swords.bmp");
	IMG_SUB_TAG[40] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\javelins.bmp");
	IMG_SUB_TAG[41] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\daggers.bmp");
	IMG_SUB_TAG[42] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\phantoms.bmp");
	IMG_SUB_TAG[43] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gauntlets.bmp");

	IMG_SUB_TAGH[0] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\amulets_.bmp");
	IMG_SUB_TAGH[1] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\rings_.bmp");
	IMG_SUB_TAGH[2] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\sheltoms_.bmp");
	IMG_SUB_TAGH[3] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\forceorbs_.bmp");
	IMG_SUB_TAGH[4] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\brincos_.bmp");
	IMG_SUB_TAGH[5] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\bracelets_.bmp");
	IMG_SUB_TAGH[6] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\orbs_.bmp");
	IMG_SUB_TAGH[7] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\armors_.bmp");
	IMG_SUB_TAGH[8] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\robes_.bmp");
	IMG_SUB_TAGH[9] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\boots_.bmp");
	IMG_SUB_TAGH[10] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gauntlets_.bmp");
	IMG_SUB_TAGH[11] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\shields_.bmp");
	IMG_SUB_TAGH[12] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\axes_.bmp");
	IMG_SUB_TAGH[13] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\claws_.bmp");
	IMG_SUB_TAGH[14] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\hammers_.bmp");
	IMG_SUB_TAGH[15] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\wands_.bmp");
	IMG_SUB_TAGH[16] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\scythes_.bmp");
	IMG_SUB_TAGH[17] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\bows_.bmp");
	IMG_SUB_TAGH[18] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\swords_.bmp");
	IMG_SUB_TAGH[19] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\javelins_.bmp");
	IMG_SUB_TAGH[20] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\daggers_.bmp");
	IMG_SUB_TAGH[21] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\phantoms_.bmp");
	IMG_SUB_TAGH[22] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gauntlets_.bmp");

	IMG_SUB_TAGH[23] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\combat_.bmp");
	IMG_SUB_TAGH[24] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\aging_.bmp");
	IMG_SUB_TAGH[25] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\mixing_.bmp");
	IMG_SUB_TAGH[26] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gold_.bmp");
	IMG_SUB_TAGH[27] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\crystals_.bmp");
	IMG_SUB_TAGH[28] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\pets_.bmp");
	IMG_SUB_TAGH[29] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumes_.bmp");
	IMG_SUB_TAGH[30] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumesmg_.bmp");
	IMG_SUB_TAGH[31] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\axes_.bmp");
	IMG_SUB_TAGH[32] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\armors_.bmp");
	IMG_SUB_TAGH[33] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\shields_.bmp");
	IMG_SUB_TAGH[34] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\claws_.bmp");
	IMG_SUB_TAGH[35] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\hammers_.bmp");
	IMG_SUB_TAGH[36] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\wands_.bmp");
	IMG_SUB_TAGH[37] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\scythes_.bmp");
	IMG_SUB_TAGH[38] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\bows_.bmp");
	IMG_SUB_TAGH[39] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\swords_.bmp");
	IMG_SUB_TAGH[40] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\javelins_.bmp");
	IMG_SUB_TAGH[41] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\daggers_.bmp");
	IMG_SUB_TAGH[42] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\phantoms_.bmp");
	IMG_SUB_TAGH[43] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\gauntlets_.bmp");

	WeaponClass = 0;
	ArmorClass = 0;
	ShieldClass = 0;
	BraceletsClass = 0;
	GauntletsClass = 0;
	BootsClass = 0;
	RingClass = 0;
	AmyClass = 0;
	ShelClass = 0;
	TimeClass = 0;
	SpecBox = 0;
	SpecItem = 0;
	Counter = 0;
	SelectItem = 0;
}

bool CoinShop::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}

void CoinShop::DrawVipOnList(int Line, char* Name, int Price, char* Description1, char* Description2, int num, int Width, int Height, int WinX, int WinY)
{
	char szBuff[256];
	wsprintf(szBuff, "Price: %d", Price);
	WinY -= (Scroll * 20);
	if (Height == 88)
	{
		if (WinY + 42 >= 142 && WinY + 42 + 88 <= 452 && MouseAction(WinX + 23, WinY + 42, 274, 88))
			dsDrawColorBox(D3DCOLOR_RGBA(255, 200, 0, 128), WinX + 23, WinY + 42, 274, 88);
	}
	else
	{
		if (WinY + 42 >= 142 && WinY + 42 + 66 <= 452 && MouseAction(WinX + 23, WinY + 42, 274, 66))
			dsDrawColorBox(D3DCOLOR_RGBA(255, 200, 0, 128), WinX + 23, WinY + 42, 274, 66);
	}

	if (WinY + 45 >= 142 && WinY + 45 + 15 <= 452)
		DrawText(Name, WinX + 78, WinY + 45, FontBold, D3DCOLOR_RGBA(255, 255, 255, 255));
	if (WinY + 45 >= 142 && WinY + 45 + 15 <= 452)
		DrawText(szBuff, WinX + 225, WinY + 45, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	if (WinY + 65 >= 142 && WinY + 65 + 15 <= 452)
		DrawText(Description1, WinX + 78, WinY + 65, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	if (WinY + 85 >= 142 && WinY + 85 + 15 <= 452)
		DrawText(Description2, WinX + 78, WinY + 85, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	if (Height == 88 || Height == 66)
	{
		if (WinY + 42 >= 142 && WinY + 42 + Height <= 452)
		{
			DrawImage(cImages[45], WinX + 32, WinY + 42, Width, Height);

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 42);
		}
		else if (WinY + 42 < 142 && 142 - WinY + 42 - Height < 88)
		{
			DrawImage(cImages[45], WinX + 32, WinY + 42 + (142 - WinY + 42 - Height), Width, Height - (142 - WinY + 42 - Height));

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 42);
		}
		else if (WinY + 42 + Height > 452 && WinY + 42 + Height - 452 < 88)
		{
			DrawImage(cImages[45], WinX + 32, WinY + 42, Width, Height - (WinY + 42 + Height - 452));

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 42);
		}
	}
	else if (Height == 44)
	{
		if (WinY + 55 >= 142 && WinY + 55 + Height <= 452)
		{
			DrawImage(cImages[45], WinX + 32, WinY + 55, Width, Height);

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 55);
		}
	}
	else
	{
		if (WinY + 65 >= 142 && WinY + 64 + Height <= 452)
		{
			DrawImage(cImages[45], WinX + 32, WinY + 64, Width, Height);

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 64);
		}
	}

	if (Height == 88)
	{
		if (WinY + 130 >= 142 && WinY + 130 + 1 <= 452)
			DrawTexImage(Line, WinX + 23, WinY + 130, 274, 1, 255);
	}
	else
	{
		if (WinY + 108 - 1 >= 142 && WinY + 108 + 1 <= 452)
			DrawTexImage(Line, WinX + 23, WinY + 108, 274, 1, 255);
	}
}

void CoinShop::DrawItemOnList(int Line, LPDIRECT3DTEXTURE9 Image, char* Name, int Price, char* Description1, char* Description2, int num, int Width, int Height, int WinX, int WinY)
{
	char szBuff[256];
	wsprintf(szBuff, "%d", Price);
	WinY -= (Scroll * 20);
	if (Height == 88)
	{
		if (WinY + 42 >= 142 && WinY + 42 + 88 <= 452 && MouseAction(WinX + 23, WinY + 42, 274, 88))
			dsDrawColorBox(D3DCOLOR_RGBA(255, 200, 0, 128), WinX + 23, WinY + 42, 274, 88);
	}
	else
	{
		if (WinY + 42 >= 142 && WinY + 42 + 66 <= 452 && MouseAction(WinX + 23, WinY + 42, 274, 66))
			dsDrawColorBox(D3DCOLOR_RGBA(255, 200, 0, 128), WinX + 23, WinY + 42, 274, 66);
	}

	if (WinY + 45 >= 142 && WinY + 45 + 15 <= 452)
		DrawText(Name, WinX + 110, WinY + 45, FontBold, D3DCOLOR_RGBA(182, 255, 0, 255));
	if (WinY + 45 >= 142 && WinY + 45 + 15 <= 452)
		HoDrawTexImage(cImages[47], WinX + 225, WinY + 46, 21, 13, 0, 0, 21, 13, 255);
	if (WinY + 45 >= 142 && WinY + 45 + 15 <= 452)
		DrawText(szBuff, WinX + 250, WinY + 45, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	if (WinY + 65 >= 142 && WinY + 65 + 15 <= 452)
		DrawText(Description1, WinX + 78, WinY + 65, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	if (WinY + 85 >= 142 && WinY + 85 + 15 <= 452)
		DrawText(Description2, WinX + 78, WinY + 85, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

	if (Height == 88 || Height == 66)
	{
		if (WinY + 42 >= 142 && WinY + 42 + Height <= 452)
		{
			DrawSprite(WinX + 32, WinY + 42, Image, 0, 0, Width, Height);

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 42);
		}
		else if (WinY + 42 < 142 && 142 - WinY + 42 - Height < 88)
		{
			DrawSprite(WinX + 32, WinY + 42 + (142 - WinY + 42 - Height), Image, 0, 0, Width, Height - (142 - WinY + 42 - Height));

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 42);
		}
		else if (WinY + 42 + Height > 452 && WinY + 42 + Height - 452 < 88)
		{
			DrawSprite(WinX + 32, WinY + 42, Image, 0, 0, Width, Height - (WinY + 42 + Height - 452));

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 42);
		}
	}
	else if (Height == 44)
	{
		if (WinY + 55 >= 142 && WinY + 55 + Height <= 452)
		{
			DrawSprite(WinX + 32, WinY + 55, Image, 0, 0, Width, Height);

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 55);
		}
	}
	else
	{
		if (WinY + 65 >= 142 && WinY + 64 + Height <= 452)
		{
			DrawSprite(WinX + 32, WinY + 64, Image, 0, 0, Width, Height);

			if (SubTag == SUB_TAG_FORCE_ORBS)
				cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 64);
		}
	}

	if (Height == 88)
	{
		if (WinY + 130 >= 142 && WinY + 130 + 1 <= 452)
			DrawTexImage(Line, WinX + 23, WinY + 130, 274, 1, 255);
	}
	else
	{
		if (WinY + 108 - 1 >= 142 && WinY + 108 + 1 <= 452)
			DrawTexImage(Line, WinX + 23, WinY + 108, 274, 1, 255);
	}
}

void CoinShop::DrawItemOnDetails(LPDIRECT3DTEXTURE9 Image, char* Name, int Price, int Width, int Height)
{
	char szBuff[256];
	int WinX = 450, WinY = 100, ItemY2 = 0, ItemY = 0, ItemSpecY = 0;
	DrawSprite(WinX + 33, WinY + 64, recv_items[SelectItem].Image, 0, 0, recv_items[SelectItem].Width, recv_items[SelectItem].Height);

	if (SubTag == SUB_TAG_FORCE_ORBS)
		cInvenTory.DrawForceOrbEffect(WinX + 33, WinY + 64);

	SIZE size;
	GetFontTextExtentPoint(recv_items[SelectItem].ItemInfo.ItemName, strlen(recv_items[SelectItem].szName), &size);

	DrawText(recv_items[SelectItem].szName, WinX + 120, WinY + 45, FontBold, D3DCOLOR_RGBA(255, 255, 255, 255));

	if (recv_items[SelectItem].ItemInfo.Damage[0] || recv_items[SelectItem].ItemInfo.Damage[1])
	{
		wsprintf(szBuff, "%s%d-%d", sinAbilityName[0], recv_items[SelectItem].ItemInfo.Damage[0], recv_items[SelectItem].ItemInfo.Damage[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Attack_Speed)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[1], recv_items[SelectItem].ItemInfo.Attack_Speed);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Shooting_Range)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[2], recv_items[SelectItem].ItemInfo.Shooting_Range);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Critical_Hit)
	{
		wsprintf(szBuff, "%s%d%s", sinAbilityName[3], recv_items[SelectItem].ItemInfo.Critical_Hit, "%");
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Defence)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[4], recv_items[SelectItem].ItemInfo.Defence);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Attack_Rating)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[5], recv_items[SelectItem].ItemInfo.Attack_Rating);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fAbsorb)
	{
		int sinAbsorb = (int)(GetItemAbsorb(&recv_items[SelectItem].ItemInfo) * 10.001f);
		int sinRightSpot = sinAbsorb % 10;
		int sinLeftSpot = (sinAbsorb - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinAbilityName[6], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fBlock_Rating)
	{
		int BlockRate = (int)(recv_items[SelectItem].ItemInfo.fBlock_Rating);
		wsprintf(szBuff, "%s%d%s", sinAbilityName[7], BlockRate, "%");
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fSpeed)
	{
		int sinSpeed = (int)(recv_items[SelectItem].ItemInfo.fSpeed * 10.001f);
		int sinRightSpot = sinSpeed % 10;
		int sinLeftSpot = (sinSpeed - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinAbilityName[8], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Durability[0] || recv_items[SelectItem].ItemInfo.Durability[1])
	{
		wsprintf(szBuff, "%s%d-%d", sinAbilityName[9], recv_items[SelectItem].ItemInfo.Durability[0], recv_items[SelectItem].ItemInfo.Durability[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Mana[0] || recv_items[SelectItem].ItemInfo.Mana[1])
	{
		wsprintf(szBuff, "%s%d-%d", sinAbilityName[10], recv_items[SelectItem].ItemInfo.Mana[0], recv_items[SelectItem].ItemInfo.Mana[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Life[0] || recv_items[SelectItem].ItemInfo.Life[1])
	{
		wsprintf(szBuff, "%s%d-%d", sinAbilityName[11], recv_items[SelectItem].ItemInfo.Life[0], recv_items[SelectItem].ItemInfo.Life[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Stamina[0] || recv_items[SelectItem].ItemInfo.Stamina[1])
	{
		wsprintf(szBuff, "%s%d-%d", sinAbilityName[12], recv_items[SelectItem].ItemInfo.Stamina[0], recv_items[SelectItem].ItemInfo.Stamina[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[0])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[13], recv_items[SelectItem].ItemInfo.Resistance[0]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[1])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[14], recv_items[SelectItem].ItemInfo.Resistance[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[2])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[15], recv_items[SelectItem].ItemInfo.Resistance[2]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[3])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[16], recv_items[SelectItem].ItemInfo.Resistance[3]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[4])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[17], recv_items[SelectItem].ItemInfo.Resistance[4]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[5])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[18], recv_items[SelectItem].ItemInfo.Resistance[5]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[6])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[19], recv_items[SelectItem].ItemInfo.Resistance[6]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Resistance[7])
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[20], recv_items[SelectItem].ItemInfo.Resistance[7]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fLife_Regen && (recv_items[SelectItem].ItemInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		int sinRegen = (int)(recv_items[SelectItem].ItemInfo.fLife_Regen * 10.001f);
		int sinRightSpot = sinRegen % 10;
		int sinLeftSpot = (sinRegen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinAbilityName[21], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fMana_Regen && (recv_items[SelectItem].ItemInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		int sinRegen = (int)(recv_items[SelectItem].ItemInfo.fMana_Regen * 10.001f);
		int sinRightSpot = sinRegen % 10;
		int sinLeftSpot = (sinRegen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinAbilityName[22], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fStamina_Regen && (recv_items[SelectItem].ItemInfo.CODE & sinITEM_MASK2) != sinFO1)
	{
		int sinRegen = (int)(recv_items[SelectItem].ItemInfo.fStamina_Regen * 10.001f);
		int sinRightSpot = sinRegen % 10;
		int sinLeftSpot = (sinRegen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinAbilityName[23], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	int AddState;
	if (recv_items[SelectItem].ItemInfo.fIncrease_Life)
	{
		AddState = (int)recv_items[SelectItem].ItemInfo.fIncrease_Life;
		wsprintf(szBuff, "%s%d", sinAbilityName[24], AddState);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fIncrease_Mana)
	{
		int AddState = (int)recv_items[SelectItem].ItemInfo.fIncrease_Mana;
		wsprintf(szBuff, "%s%d", sinAbilityName[25], AddState);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.fIncrease_Stamina)
	{
		int AddState = (int)recv_items[SelectItem].ItemInfo.fIncrease_Stamina;
		wsprintf(szBuff, "%s%d", sinAbilityName[26], AddState);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Potion_Space)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[27], recv_items[SelectItem].ItemInfo.Potion_Space);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Level)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[28], recv_items[SelectItem].ItemInfo.Level);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 207, 178, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Strength)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[29], recv_items[SelectItem].ItemInfo.Strength);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 207, 178, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Spirit)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[30], recv_items[SelectItem].ItemInfo.Spirit);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 207, 178, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Talent)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[31], recv_items[SelectItem].ItemInfo.Talent);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 207, 178, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Dexterity)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[32], recv_items[SelectItem].ItemInfo.Dexterity);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 207, 178, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Health)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[33], recv_items[SelectItem].ItemInfo.Health);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 207, 178, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Attack_Speed)
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[0], recv_items[SelectItem].ItemInfo.JobItem.Add_Attack_Speed);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Critical_Hit)
	{
		wsprintf(szBuff, "%s%d%s", sinSpecialName[1], recv_items[SelectItem].ItemInfo.JobItem.Add_Critical_Hit, "%");
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Defence)
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[2], recv_items[SelectItem].ItemInfo.JobItem.Add_Defence);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fAbsorb)
	{
		int sinAbsorb = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fAbsorb * 10.001f);
		int sinRightSpot = sinAbsorb % 10;
		int sinLeftSpot = (sinAbsorb - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[3], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fBlock_Rating)
	{
		int BlockRate = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fBlock_Rating);
		wsprintf(szBuff, "%s%d%s", sinSpecialName[4], BlockRate, "%");
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fMagic_Mastery)
	{
		int sinMagic_Mastery = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fMagic_Mastery);
		wsprintf(szBuff, "%s%d", sinSpecialName[5], sinMagic_Mastery);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fSpeed)
	{
		int sinSpeed = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fSpeed * 10.001f);
		int sinRightSpot = sinSpeed % 10;
		int sinLeftSpot = (sinSpeed - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[6], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[0])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[7], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[0]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[1])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[8], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[2]) {
		wsprintf(szBuff, "%s%d", sinSpecialName[9], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[2]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[3])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[10], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[3]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[4])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[11], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[4]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[5])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[12], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[5]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[6])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[13], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[6]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[7])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[14], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[7]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Damage[1])
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[15], recv_items[SelectItem].ItemInfo.JobItem.Lev_Damage[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Rating)
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[16], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Rating);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Shooting_Range)
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[17], recv_items[SelectItem].ItemInfo.JobItem.Add_Shooting_Range);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[0])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[18], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[0]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[1])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[19], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[2])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[20], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[2]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[3])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[21], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[3]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[4])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[22], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[4]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[5])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[23], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[5]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[6])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[24], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[6]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[7])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[25], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[7]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Life)
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[26], recv_items[SelectItem].ItemInfo.JobItem.Lev_Life);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Mana)
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[27], recv_items[SelectItem].ItemInfo.JobItem.Lev_Mana);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Per_Life_Regen)
	{
		int sinPer_Regen = (int)(recv_items[SelectItem].ItemInfo.JobItem.Per_Life_Regen * 10.001f);
		int sinRightSpot = sinPer_Regen % 10;
		int sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[28], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Per_Mana_Regen)
	{
		int sinPer_Regen = (int)(recv_items[SelectItem].ItemInfo.JobItem.Per_Mana_Regen * 10.001f);
		int sinRightSpot = sinPer_Regen % 10;
		int sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[29], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Per_Stamina_Regen)
	{
		int sinPer_Regen = (int)(recv_items[SelectItem].ItemInfo.JobItem.Per_Stamina_Regen * 10.001f);
		int sinRightSpot = sinPer_Regen % 10;
		int sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[30], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(131, 183, 0, 255));
		ItemY++;
	}

	int Count = Counter + 1;
	int TotalPrice = Price * Count;

	if (lstrcmpi(recv_items[SelectItem].szCode, "VIP") == 0 || lstrcmpi(recv_items[SelectItem].szCode, "VIP Elite") == 0)
	{
		switch (SpecItem)
		{
		case 1:
			TotalPrice *= 2;
			break;
		case 2:
			TotalPrice *= 5;
			break;
		}
	}

	wsprintf(szBuff, "TOTAL: %d", TotalPrice);

	DrawText(szBuff, WinX + 25, WinY + 280, CoinFont[0], D3DCOLOR_RGBA(255, 255, 255, 255));
	wsprintf(szBuff, "%d", Count);
	TotalPrice += Price;
	if (lstrcmpi(recv_items[SelectItem].szCode, "VIP") != 0 && lstrcmpi(recv_items[SelectItem].szCode, "VIP Elite") != 0 && lstrcmpi(recv_items[SelectItem].szCode, "Class") != 0)
	{
		HoDrawTexImage(cImages[36], WinX + 25, WinY + 315, 80.f, 26.f, 0, 0, 80.f, 26.f, 255);

		if (MouseAction(WinX + 66, WinY + 317, 18, 22))
		{
			if (Coin >= TotalPrice)
				HoDrawTexImage(cImages[38], WinX + 66, WinY + 317, 18.f, 22.f, 0, 0, 18.f, 22.f, 255);
			else
				HoDrawTexImage(cImages[40], WinX + 66, WinY + 317, 18.f, 22.f, 0, 0, 18.f, 22.f, 255);
		}

		if (MouseAction(WinX + 85, WinY + 317, 18, 22))
		{
			if (Count > 1)
				HoDrawTexImage(cImages[37], WinX + 85, WinY + 317, 18.f, 22.f, 0, 0, 18.f, 22.f, 255);
			else
				HoDrawTexImage(cImages[39], WinX + 85, WinY + 317, 18.f, 22.f, 0, 0, 18.f, 22.f, 255);
		}

		DrawText(szBuff, WinX + 49 - strlen(szBuff) * 3, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	if (SpecBox)
	{
		if (lstrcmpi(recv_items[SelectItem].szCode, "VIP") == 0 || lstrcmpi(recv_items[SelectItem].szCode, "VIP Elite") == 0)
		{
			HoDrawTexImage(cImages[31], WinX + 120, WinY + 315, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

			if (MouseAction(WinX + 120, WinY + 341, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 341, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 341, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 365, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 365, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 365, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 389, 86, 25))
				HoDrawTexImage(cImages[35], WinX + 120, WinY + 389, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);
			else
				HoDrawTexImage(cImages[33], WinX + 120, WinY + 389, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

			if (SpecItem == 0)
				DrawText("1 Day", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 1)
				DrawText("7 Day", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 2)
				DrawText("30 Day", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

			DrawText("1 Day", WinX + 130, WinY + 343, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("7 Day", WinX + 130, WinY + 368, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("30 Day", WinX + 130, WinY + 392, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
		else
		{
			HoDrawTexImage(cImages[31], WinX + 120, WinY + 315, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

			if (MouseAction(WinX + 120, WinY + 341, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 341, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 341, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 365, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 365, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 365, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 389, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 389, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 389, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 413, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 413, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 413, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 437, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 437, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 437, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 461, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 461, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 461, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 485, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 485, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 485, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 509, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 509, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 509, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 533, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 533, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 533, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 557, 86, 24))
				HoDrawTexImage(cImages[34], WinX + 120, WinY + 557, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
			else
				HoDrawTexImage(cImages[32], WinX + 120, WinY + 557, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

			if (MouseAction(WinX + 120, WinY + 581, 86, 25))
				HoDrawTexImage(cImages[35], WinX + 120, WinY + 581, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);
			else
				HoDrawTexImage(cImages[33], WinX + 120, WinY + 581, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

			if (SpecItem == 0)
				DrawText("Naked", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 1)
				DrawText("Lutador", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 2)
				DrawText("Mecânico", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 3)
				DrawText("Arqueira", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 4)
				DrawText("Pike", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 5)
				DrawText("Atalanta", WinX + 133, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 6)
				DrawText("Cavaleiro", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 7)
				DrawText("Mago", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 8)
				DrawText("Sacer", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 9)
				DrawText("Assassina", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 10)
				DrawText("Xamã", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 11)
				DrawText("Guerreira", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

			DrawText("Lutador", WinX + 136, WinY + 343, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Mecânico", WinX + 131, WinY + 368, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Arqueira", WinX + 134, WinY + 392, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Pike", WinX + 145, WinY + 416, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Atalanta", WinX + 137, WinY + 440, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Cavaleiro", WinX + 134, WinY + 464, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Mago", WinX + 143, WinY + 488, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Sacer", WinX + 143, WinY + 513, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Assassina", WinX + 134, WinY + 538, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Xamã", WinX + 143, WinY + 563, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			DrawText("Guerreira", WinX + 134, WinY + 588, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}
	else
	{
		if (lstrcmpi(recv_items[SelectItem].szCode, "VIP") == 0 || lstrcmpi(recv_items[SelectItem].szCode, "VIP Elite") == 0)
		{
			if (MouseAction(WinX + 120, WinY + 320, 86, 26))
				HoDrawTexImage(cImages[30], WinX + 120, WinY + 315, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
			else
				HoDrawTexImage(cImages[29], WinX + 120, WinY + 315, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

			if (SpecItem == 0)
				DrawText("1 Day", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 1)
				DrawText("7 Day", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 2)
				DrawText("30 Day", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
		else
		{
			if (MouseAction(WinX + 120, WinY + 320, 86, 26))
				HoDrawTexImage(cImages[30], WinX + 120, WinY + 315, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
			else
				HoDrawTexImage(cImages[29], WinX + 120, WinY + 315, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

			if (SpecItem == 0)
				DrawText("Naked", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 1)
				DrawText("Lutador", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 2)
				DrawText("Mecânico", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 3)
				DrawText("Arqueira", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 4)
				DrawText("Pike", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 5)
				DrawText("Atalanta", WinX + 133, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 6)
				DrawText("Cavaleiro", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 7)
				DrawText("Mago", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 8)
				DrawText("Sacer", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 9)
				DrawText("Assassina", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 10)
				DrawText("Xamã", WinX + 140, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (SpecItem == 11)
				DrawText("Guerreira", WinX + 130, WinY + 320, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
	}

	if (MouseAction(WinX + 220, WinY + 315, 75, 26))
		DrawImage(cImages[28], WinX + 220, WinY + 315, 75, 26);
	else
		DrawImage(cImages[27], WinX + 220, WinY + 315, 75, 26);
}

void CoinShop::DrawChangeItemDetails()
{
	int WinX = 450, WinY = 100;

	DrawSprite(WinX + 158 - 34, WinY + 181 - 120, bImages[0], 0, 0, 68, 90);

	if (MouseAction(WinX + 158 - 30, WinY + 181 - 20, 60, 90))
	{
		dsDrawTexImage(cImages[45], WinX + 158 - 30, WinY + 181 - 20, 59, 59, 255);
	}
	else
	{
		dsDrawTexImage(cImages[45], WinX + 158 - 30, WinY + 181 - 20, 59, 59, 127);
	}

	if (MouseAction(WinX + 158 - 34, WinY + 181 - 120, 68, 90))
	{
		if (sItemChange.Flag)
		{
			dsDrawColorBox(D3DCOLOR_RGBA(255, 255, 255, 128), WinX + 158 - 34, WinY + 181 - 120, 68, 90);
		}
		else if (MouseItem.Flag)
		{
			if ((MouseItem.CODE & sinITEM_MASK2) != sinDS1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinOM1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinDG1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinDB1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinOA2
				&& (MouseItem.CODE & sinITEM_MASK2) != sinOA1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinOR1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinOR2
				&& (MouseItem.CODE & sinITEM_MASK2) != sinOS1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinDA1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinDA2
				&& (MouseItem.CODE & sinITEM_MASK2) != sinDA3
				&& (MouseItem.CODE & sinITEM_MASK2) != sinDA4
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWA1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWC1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWH1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWM1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWP1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWS1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWS2
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWT1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWN1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWD1
				&& (MouseItem.CODE & sinITEM_MASK2) != sinWV1)
			{
				dsDrawColorBox(D3DCOLOR_RGBA(255, 0, 0, 128), WinX + 158 - 34, WinY + 181 - 120, 68, 90);
			}
			else
			{
				dsDrawColorBox(D3DCOLOR_RGBA(160, 235, 256, 128), WinX + 158 - 34, WinY + 181 - 120, 68, 90);
			}
		}
	}

	if (sItemChange.Flag)
	{
		DrawSprite(sItemChange.x, sItemChange.y, sItemChange.lpItem, 0, 0, sItemChange.w, sItemChange.h);

		if (MouseAction(sItemChange.x, sItemChange.y, sItemChange.w, sItemChange.h))
		{
			sinShowItemInfoFlag = 1;
			cItem.ShowItemInfo(&sItemChange, 2);
		}
	}

	DrawText("Selecione o Spec", WinX + 158 - 102, WinY + 218, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));

	if (SpecBox)
	{
		HoDrawTexImage(cImages[31], WinX + 158 - 106, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 260, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 284, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 308, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 308, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 308, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 332, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 332, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 332, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 356, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 356, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 356, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 380, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 380, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 380, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 404, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 404, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 404, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 428, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 428, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 428, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 452, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 452, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 452, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 476, 86, 24))
			HoDrawTexImage(cImages[34], WinX + 158 - 106, WinY + 476, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
		else
			HoDrawTexImage(cImages[32], WinX + 158 - 106, WinY + 476, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

		if (MouseAction(WinX + 158 - 106, WinY + 500, 86, 25))
			HoDrawTexImage(cImages[35], WinX + 158 - 106, WinY + 500, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);
		else
			HoDrawTexImage(cImages[33], WinX + 158 - 106, WinY + 500, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

		if (SpecItem == 0)
			DrawText("Naked", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 1)
			DrawText("Lutador", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 2)
			DrawText("Mecânico", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 3)
			DrawText("Arqueira", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 4)
			DrawText("Pike", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 5)
			DrawText("Atalanta", WinX + 158 - 93, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 6)
			DrawText("Cavaleiro", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 7)
			DrawText("Mago", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 8)
			DrawText("Sacer", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 9)
			DrawText("Assassina", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 10)
			DrawText("Xamã", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 11)
			DrawText("Guerreira", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

		DrawText("Lutador", WinX + 158 - 89, WinY + 262, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Mecânico", WinX + 158 - 92, WinY + 287, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Arqueira", WinX + 158 - 92, WinY + 313, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Pike", WinX + 158 - 81, WinY + 337, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Atalanta", WinX + 158 - 89, WinY + 361, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Cavaleiro", WinX + 158 - 92, WinY + 385, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Mago", WinX + 158 - 83, WinY + 409, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Sacer", WinX + 158 - 83, WinY + 433, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Assassina", WinX + 158 - 83, WinY + 457, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Xamã", WinX + 158 - 83, WinY + 481, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		DrawText("Guerreira", WinX + 158 - 83, WinY + 505, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	}
	else
	{
		if (MouseAction(WinX + 158 - 106, WinY + 231, 86, 26))
			HoDrawTexImage(cImages[30], WinX + 158 - 106, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
		else
			HoDrawTexImage(cImages[29], WinX + 158 - 106, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

		if (SpecItem == 0)
			DrawText("Naked", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 1)
			DrawText("Lutador", WinX + 158 - 93, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 2)
			DrawText("Mecânico", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 3)
			DrawText("Arqueira", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 4)
			DrawText("Pike", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 5)
			DrawText("Atalanta", WinX + 158 - 93, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 6)
			DrawText("Cavaleiro", WinX + 158 - 96, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 7)
			DrawText("Mago", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 8)
			DrawText("Sacer", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 9)
			DrawText("Assassina", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 10)
			DrawText("Xamã", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
		if (SpecItem == 11)
			DrawText("Guerreira", WinX + 158 - 86, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	DrawText("Selecione a Arma", WinX + 158 + 24, WinY + 218, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));

	if (ClassBox)
	{
		if (sItemChange.Flag)
		{
			switch (sItemChange.CODE & sinITEM_MASK2)
			{
			case sinDA1:
			case sinDA2:
			case sinDA3:
			case sinDA4:

				HoDrawTexImage(cImages[31], WinX + 158 + 20, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 260, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 284, 86, 25))
					HoDrawTexImage(cImages[35], WinX + 158 + 20, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 25.f, 255);
				else
					HoDrawTexImage(cImages[33], WinX + 158 + 20, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 25.f, 255);

				if (ClassType == 0)
					DrawText("Naked", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 1)
					DrawText("Armadura", WinX + 158 + 27, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 2)
					DrawText("Roupão", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

				DrawText("Armadura", WinX + 158 + 37, WinY + 262, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Roupão", WinX + 158 + 40, WinY + 287, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				break;
			case sinDS1:
			case sinOM1:

				HoDrawTexImage(cImages[31], WinX + 158 + 20, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 260, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 284, 86, 25))
					HoDrawTexImage(cImages[35], WinX + 158 + 20, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 25.f, 255);
				else
					HoDrawTexImage(cImages[33], WinX + 158 + 20, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 25.f, 255);

				if (ClassType == 0)
					DrawText("Naked", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 1)
					DrawText("Escudo", WinX + 158 + 27, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 2)
					DrawText("Orbital", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

				DrawText("Escudo", WinX + 158 + 37, WinY + 262, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Orbital", WinX + 158 + 40, WinY + 287, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				break;
			case sinWP1:
			case sinWT1:
			case sinWM1:
			case sinWS2:
			case sinWS1:
			case sinWH1:
			case sinWA1:
			case sinWC1:
			case sinWN1:
			case sinWD1:
			case sinWV1:

				HoDrawTexImage(cImages[31], WinX + 158 + 20, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 260, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 260, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 284, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 284, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 308, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 308, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 308, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 332, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 332, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 332, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 356, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 356, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 356, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 380, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 380, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 380, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 404, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 404, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 404, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 428, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 428, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 428, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 452, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 452, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 452, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 476, 86, 24))
					HoDrawTexImage(cImages[34], WinX + 158 + 20, WinY + 476, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);
				else
					HoDrawTexImage(cImages[32], WinX + 158 + 20, WinY + 476, 86.f, 24.f, 0, 0, 86.f, 24.f, 255);

				if (MouseAction(WinX + 158 + 20, WinY + 500, 86, 25))
					HoDrawTexImage(cImages[35], WinX + 158 + 20, WinY + 500, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);
				else
					HoDrawTexImage(cImages[33], WinX + 158 + 20, WinY + 500, 86.f, 25.f, 0, 0, 86.f, 25.f, 255);

				if (ClassType == 0)
					DrawText("Naked", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 1)
					DrawText("Machado", WinX + 158 + 33, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 2)
					DrawText("Garra", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 3)
					DrawText("Martelo", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 4)
					DrawText("Cajado", WinX + 158 + 38, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 5)
					DrawText("Arco", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 6)
					DrawText("Espada", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 7)
					DrawText("Foice", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 8)
					DrawText("Lança", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 9)
					DrawText("Adaga", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 10)
					DrawText("Phantom", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				if (ClassType == 11)
					DrawText("Punho", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

				DrawText("Machado", WinX + 158 + 37, WinY + 262, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Garra", WinX + 158 + 40, WinY + 287, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Martelo", WinX + 158 + 37, WinY + 313, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Cajado", WinX + 158 + 38, WinY + 337, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Arco", WinX + 158 + 43, WinY + 361, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Espada", WinX + 158 + 37, WinY + 385, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Foice", WinX + 158 + 40, WinY + 409, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Lança", WinX + 158 + 40, WinY + 433, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Adaga", WinX + 158 + 40, WinY + 457, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Phantom", WinX + 158 + 40, WinY + 481, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
				DrawText("Punho", WinX + 158 + 40, WinY + 505, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

				break;
			}
		}
	}
	else
	{
		if (MouseAction(WinX + 158 + 20, WinY + 231, 86, 26))
			HoDrawTexImage(cImages[30], WinX + 158 + 20, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);
		else
			HoDrawTexImage(cImages[29], WinX + 158 + 20, WinY + 234, 86.f, 26.f, 0, 0, 86.f, 26.f, 255);

		switch (sItemChange.CODE & sinITEM_MASK2)
		{
		case sinDA1:
		case sinDA2:
		case sinDA3:
		case sinDA4:
			if (ClassType == 0)
				DrawText("Naked", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 1)
				DrawText("Armadura", WinX + 158 + 27, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 2)
				DrawText("Roupão", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			break;
		case sinDS1:
		case sinOM1:
			if (ClassType == 0)
				DrawText("Naked", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 1)
				DrawText("Escudo", WinX + 158 + 27, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 2)
				DrawText("Orbital", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			break;
		case sinWP1:
		case sinWT1:
		case sinWM1:
		case sinWS2:
		case sinWS1:
		case sinWH1:
		case sinWA1:
		case sinWC1:
		case sinWN1:
		case sinWD1:
		case sinWV1:

			if (ClassType == 0)
				DrawText("Naked", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 1)
				DrawText("Machado", WinX + 158 + 33, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 2)
				DrawText("Garra", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 3)
				DrawText("Martelo", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 4)
				DrawText("Cajado", WinX + 158 + 38, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 5)
				DrawText("Arco", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 6)
				DrawText("Espada", WinX + 158 + 37, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 7)
				DrawText("Foice", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 8)
				DrawText("Lança", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 9)
				DrawText("Adaga", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 10)
				DrawText("Phantom", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			if (ClassType == 11)
				DrawText("Punho", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

			break;
		default:
			DrawText("Naked", WinX + 158 + 40, WinY + 239, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
			break;
		}
	}

	int AddX = 0;

	if (WeaponClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[1], 0, 0, 22, 22);
	AddX += 32;
	if (ArmorClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[2], 0, 0, 22, 22);
	AddX += 32;
	if (ShieldClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[3], 0, 0, 22, 22);
	AddX += 32;
	if (BraceletsClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[4], 0, 0, 22, 22);
	AddX += 32;
	if (GauntletsClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[5], 0, 0, 22, 22);
	AddX += 32;
	if (BootsClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[6], 0, 0, 22, 22);
	AddX += 32;
	if (RingClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[7], 0, 0, 22, 22);
	AddX += 32;
	if (AmyClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[8], 0, 0, 22, 22);
	AddX += 32;
	if (ShelClass) DrawSprite(WinX + 115 - 96 + AddX, WinY + 300, bImages[9], 0, 0, 22, 22);

	if (WeaponClass || ArmorClass || ShieldClass || BraceletsClass || GauntletsClass || BootsClass || RingClass || AmyClass || ShelClass)
	{
		if (TimeClass && TimeClass > GetPlayTime_T())
		{
			DWORD Time = TimeClass - GetPlayTime_T();
			UINT Days = Time / 60 / 60 / 24;
			UINT Hours = (Time / 60 / 60) % 24;
			UINT Minutes = (Time / 60) % 60;
			UINT Seconds = Time % 60;

			char szBuff[256];
			wsprintf(szBuff, "Suas fichas expiram em %02d:%02d:%02d", Hours, Minutes, Seconds);
			DrawText(szBuff, WinX + 56, WinY + 325, FontBold, D3DCOLOR_RGBA(255, 255, 255, 255));
		}
		else
		{
			DrawText("Suas fichas já expiraram!", WinX + 56, WinY + 325, FontBold, D3DCOLOR_RGBA(255, 0, 0, 128));
		}
	}
}

void CoinShop::Draw()
{
	if (fOpen)
	{
		int WinX = 80, WinY = 100;
		DrawTexImage(cImages[0], WinX, WinY, 316, 362, 255);

		DrawTexImage(cImages[46], WinX + 300, WinY + 43, 6, 256, 255);

		float Percent = (float)Scroll2;
		Percent = (Percent * 100) / (float)GetTotalScroll2();
		Percent = (256 * Percent) / 100;

		DrawTexImage(cImages[44], WinX + 299, WinY + 39 + Percent, 8, 11, 255);

		DrawTexImage(cImages[1], WinX + 15, WinY + 8, 130, 29, 255);
		DrawTexImage(cImages[2], WinX + 10, WinY + 308, 90, 46, 255);

		if (MouseAction(WinX + 215, WinY + 330, 93, 23))
			HoDrawTexImage(cImages[4], WinX + 215, WinY + 330, 93, 23, 93, 23, 255);
		else
			HoDrawTexImage(cImages[3], WinX + 215, WinY + 330, 93, 23, 93, 23, 255);

		char szBuff[256];
		wsprintf(szBuff, "%d", Coin);

		DrawText(szBuff, WinX + 56 - strlen(szBuff) * 4, WinY + 323, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

		for (int cnt = 0; cnt < MAX_TAG; cnt++)
		{
			if (MouseAction(WinX + 21, WinY + 42 + cnt * 43, 198, 42) || Tag == cnt + 1)
				HoDrawTexImage(IMG_TAGH[cnt], WinX + 21, WinY + 42 + cnt * 43, 198, 42, 198, 42, 255);
			else
				HoDrawTexImage(IMG_TAG[cnt], WinX + 21, WinY + 42 + cnt * 43, 198, 42, 198, 42, 255);

			DrawTexImage(cImages[15], WinX + 21, WinY + 84 + cnt * 43, 198, 1, 255);
		}

		int TotalSubTag = 0, Init = 0;

		switch (Tag)
		{
		case TAG_ACESSORIES:
			TotalSubTag = 5;
			break;
		case TAG_DEFENSE:
			TotalSubTag = 7;
			Init = 5;
			break;
		case TAG_WEAPONS:
			TotalSubTag = 11;
			Init = 12;
			break;
		case TAG_PREMIUM:
			TotalSubTag = 6;
			Init = 23;
			break;
		case TAG_FUN:
			TotalSubTag = 2;
			Init = 29;
			break;
		case 6:
			TotalSubTag = 13;
			Init = 31;
			break;
		}

		for (int cnt = 0; cnt < TotalSubTag; cnt++)
		{
			if (WinY + 44 + cnt * 33 - (Scroll2 * 20) >= 142 && WinY + 44 + cnt * 33 + 77 - (Scroll2 * 20) <= WinY + 44 + 7 * 33 + 77)
			{
				if (MouseAction(WinX + 220, WinY + 44 + cnt * 33 - (Scroll2 * 20), 77, 31) || SubTag == Init + cnt + 1)
					DrawSprite(WinX + 220, WinY + 44 + cnt * 33 - (Scroll2 * 20), IMG_SUB_TAGH[Init + cnt], 0, 0, 77, 31);
				else
					DrawSprite(WinX + 220, WinY + 44 + cnt * 33 - (Scroll2 * 20), IMG_SUB_TAG[Init + cnt], 0, 0, 77, 31);
			}

			if (WinY + 75 + cnt * 33 - (Scroll2 * 20) >= 142 && WinY + 75 + cnt * 33 + 1 - (Scroll2 * 20) <= WinY + 75 + 7 * 33 + 1)
				DrawTexImage(cImages[16], WinX + 220, WinY + 75 + cnt * 33 - (Scroll2 * 20), 77, 1, 255);
		}

		int cnt2 = 0;

		if (SubTag)
		{
			WinX = 450;

			if (WinItem)
			{
				DrawTexImage(cImages[23], WinX, WinY, 316, 362, 255);
				DrawTexImage(cImages[24], WinX + 15, WinY + 8, 157, 29, 255);

				if (MouseAction(WinX + 255, WinY + 13, 22, 22))
					DrawTexImage(cImages[26], WinX + 255, WinY + 13, 22, 22, 255);
				else
					DrawTexImage(cImages[25], WinX + 255, WinY + 13, 22, 22, 255);

				if (lstrcmpi(recv_items[SelectItem].szCode, "Class Item") == 0)
					DrawChangeItemDetails();
				else
					DrawItemOnDetails(recv_items[SelectItem].Image, recv_items[SelectItem].ItemInfo.ItemName, recv_items[SelectItem].Price, recv_items[SelectItem].Width, recv_items[SelectItem].Height);
			}
			else
			{
				DrawTexImage(cImages[17], WinX, WinY, 316, 362, 255);
				DrawTexImage(cImages[18], WinX + 15, WinY + 8, 115, 29, 255);
				DrawTexImage(cImages[43], WinX + 300, WinY + 43, 6, 307, 255);

				float Percent = (float)Scroll;
				Percent = (Percent * 100) / (float)GetTotalScroll();
				Percent = (307 * Percent) / 100;

				DrawTexImage(cImages[44], WinX + 299, WinY + 39 + Percent, 8, 11, 255);

				if (MouseAction(WinX + 280, WinY + 13, 22, 22))
					DrawTexImage(cImages[21], WinX + 280, WinY + 13, 22, 22, 255);
				else
					DrawTexImage(cImages[20], WinX + 280, WinY + 13, 22, 22, 255);

				for (int cnt = 0; cnt < 500; cnt++)
				{
					if (recv_items[cnt].SubTag && recv_items[cnt].SubTag == SubTag)
					{
						DrawItemOnList(cImages[19], recv_items[cnt].Image, recv_items[cnt].szName, recv_items[cnt].Price, recv_items[cnt].Description1, recv_items[cnt].Description2, cnt2, recv_items[cnt].Width, recv_items[cnt].Height, 450, WinY);

						if (recv_items[cnt].Height == 88)
							WinY += 87;
						else
							WinY += 67;
						cnt2++;
					}
				}
			}
		}
	}
}

void CoinShop::DrawText(char* Text, int x, int y, ID3DXFont* RegularFont, D3DCOLOR Color)
{
	RECT rc;
	rc.left = x;
	rc.right = x + smScreenWidth;
	rc.top = y;
	rc.bottom = y + smScreenHeight;
	RegularFont->DrawText(NULL, Text, strlen(Text), &rc, 0, Color);
}

void CoinShop::SendBuyItem()
{
	int Count = Counter + 1;

	if (sinChar->Weight[0] + (recv_items[SelectItem].ItemInfo.Weight * Count) > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return;
	}

	if (Coin < (recv_items[SelectItem].Price * Count))
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_COIN);
		return;
	}

	int Price = recv_items[SelectItem].Price;

	if (lstrcmpi(recv_items[SelectItem].szCode, "VIP") == 0)
	{
		switch (SpecItem)
		{
		case 1:
			Price *= 2;
			if (Coin < Price)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_COIN);
				return;
			}
			break;
		case 2:
			Price *= 5;
			if (Coin < Price)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_COIN);
				return;
			}
			break;
		}
	}
	else if (lstrcmpi(recv_items[SelectItem].szCode, "VIP Elite") == 0)
	{
		switch (SpecItem)
		{
		case 1:
			Price *= 2;
			if (Coin < Price)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_COIN);
				return;
			}
			break;
		case 2:
			Price *= 5;
			if (Coin < Price)
			{
				cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_COIN);
				return;
			}
			break;
		}
	}
	else if (lstrcmpi(recv_items[SelectItem].szCode, "Class") == 0)
	{
		if (SpecItem <= 0 || SpecItem > 11)
		{
			cMessageBox.ShowMessageEvent("Selecione uma Classe!");
			return;
		}
	}

	ZeroMemory(&cTPacket, sizeof(PACKET_COIN_SHOP_BUY));
	cCPacket.size = sizeof(PACKET_COIN_SHOP_BUY);
	cCPacket.code = smTRANSCODE_RECV_BUY_COIN_SHOP;
	lstrcpy(cCPacket.szCode, recv_items[SelectItem].szCode);
	cCPacket.spec = SpecItem;
	cCPacket.cnt = Count;

	cMessageBox.ShowMessage3(MESSAGE_BUY_COIN_SHOP, "Créditos");
}

void CoinShop::RButton(int x, int y)
{
	/*if (fOpen)
	{
		if (lstrcmpi(recv_items[SelectItem].szCode, "Class Item") == 0)
		{
			if (!sItemChange.Flag)
			{
				sITEM& Item = cInvenTory.InvenItem[SelectInvenItemIndex - 1];
				POINT MousePosition = { InterfaceX + Item.x + 11, Item.y + 11 };
				if (MouseAction(MousePosition.x, MousePosition.y, Item.w, Item.h))
				{
					cInvenTory.PickUpInvenItem(MousePosition.x, MousePosition.y, TRUE);
					if (MouseItem.Flag)
					{
						MouseItem.x = 450 + 158 - 34 + 34 - (MouseItem.w / 2);
						MouseItem.y = 100 + 181 - 115 + 40 - (MouseItem.h / 2);
						memcpy(&sItemChange, &MouseItem, sizeof(sITEM));
						ZeroMemory(&MouseItem, sizeof(sITEM));
					}
				}
			}
			else if (sItemChange.Flag)
			{
				if (MouseAction(sItemChange.x, sItemChange.y, sItemChange.w, sItemChange.h))
				{
					cInvenTory.LastSetInvenItem(&sItemChange, 1);
					ZeroMemory(&sItemChange, sizeof(sITEM));
				}
			}
		}
	}*/
}

void CoinShop::LButton(int x, int y)
{
	if (fOpen)
	{
		int WinX = 80, WinY = 100;

		if (lstrcmpi(recv_items[SelectItem].szCode, "Class Item") == 0)
		{
			if (!sItemChange.Flag)
			{
				if (MouseItem.sItemInfo.CODE)
				{
					if (MouseAction(450 + 158 - 34, 100 + 181 - 120, 68, 90))
					{
						if (TimeClass < GetPlayTime_T())
						{
							cMessageBox.ShowMessageEvent("Suas fichas já expiraram!");
							return;
						}

						switch (sItemChange.sItemInfo.CODE & sinITEM_MASK2)
						{
						case sinDA1:
						case sinDA2:
						case sinDA3:
						case sinDA4:
							if (!ArmorClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinDS1:
						case sinOM1:
							if (!ShieldClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinOA2:
							if (!BraceletsClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinDG1:
							if (!GauntletsClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinDB1:
							if (!BootsClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinOA1:
							if (!AmyClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinOR1:
						case sinOR2:
							if (!RingClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinOS1:
							if (!ShelClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						case sinWA1:
						case sinWC1:
						case sinWH1:
						case sinWM1:
						case sinWP1:
						case sinWS1:
						case sinWS2:
						case sinWT1:
						case sinWN1:
						case sinWD1:
						case sinWV1:
							if (!WeaponClass)
							{
								cMessageBox.ShowMessageEvent("Você não tem ficha para esse processo!");
								return;
							}
							break;
						}

						int Flag = 0;

						for (int cnt = 0; cnt < 77; cnt++)
						{
							if (AllowList[cnt] == MouseItem.sItemInfo.CODE || AllowList[cnt] == MouseItem.sItemInfo.SwapItem.Code)
							{
								Flag++;
							}
						}

						if (!Flag)
						{
							cMessageBox.ShowMessageEvent("Esse item não faz parte desse processo!");
						}
						else
						{
							MouseItem.x = 450 + 158 - 34 + 34 - (MouseItem.w / 2);
							MouseItem.y = 100 + 181 - 115 + 40 - (MouseItem.h / 2);
							memcpy(&sItemChange, &MouseItem, sizeof(sITEM));
							ZeroMemory(&MouseItem, sizeof(sITEM));
							ClassType = 0;
						}
					}
				}
			}
			else
			{
				if (MouseAction(450 + 158 - 34, 100 + 181 - 120, 68, 90))
				{
					sItemChange.x = pCursorPos.x - (sItemChange.w / 2);
					sItemChange.y = pCursorPos.y - (sItemChange.y / 2);
					memcpy(&MouseItem, &sItemChange, sizeof(sITEM));
					ZeroMemory(&sItemChange, sizeof(sITEM));
				}
			}
		}

		for (int cnt = 0; cnt < MAX_TAG; cnt++)
		{
			if (MouseAction(WinX + 21, WinY + 42 + cnt * 43, 198, 42))
			{
				Tag = cnt + 1;
				Scroll2 = 0;
			}
		}

		int TotalSubTag = 0, Init = 0;

		switch (Tag)
		{
		case TAG_ACESSORIES:
			TotalSubTag = 5;
			break;
		case TAG_DEFENSE:
			TotalSubTag = 7;
			Init = 5;
			break;
		case TAG_WEAPONS:
			TotalSubTag = 11;
			Init = 12;
			break;
		case TAG_PREMIUM:
			TotalSubTag = 6;
			Init = 23;
			break;
		case TAG_FUN:
			TotalSubTag = 2;
			Init = 29;
			break;
		case 6:
			TotalSubTag = 13;
			Init = 31;
			break;
		}

		for (int cnt = 0; cnt < TotalSubTag; cnt++)
		{
			if (MouseAction(WinX + 220, WinY + 44 + cnt * 33 - (Scroll2 * 20), 77, 32) && !WinItem)
			{
				SpecItem = 0;
				Counter = 0;
				SubTag = Init + cnt + 1;
				Scroll = 0;
			}
		}

		if (MouseAction(WinX + 230, WinY + 330, 73, 21))
			Close();

		if (SubTag)
		{
			WinX = 450;

			if (WinItem)
			{
				if (SpecBox)
				{
					if (lstrcmpi(recv_items[SelectItem].szCode, "Class Item") == 0)
					{
						if (MouseAction(WinX + 158 - 106, WinY + 260, 86, 24))
							SpecItem = 1;
						if (MouseAction(WinX + 158 - 106, WinY + 284, 86, 24))
							SpecItem = 2;
						if (MouseAction(WinX + 158 - 106, WinY + 308, 86, 24))
							SpecItem = 3;
						if (MouseAction(WinX + 158 - 106, WinY + 332, 86, 24))
							SpecItem = 4;
						if (MouseAction(WinX + 158 - 106, WinY + 356, 86, 24))
							SpecItem = 5;
						if (MouseAction(WinX + 158 - 106, WinY + 380, 86, 24))
							SpecItem = 6;
						if (MouseAction(WinX + 158 - 106, WinY + 404, 86, 24))
							SpecItem = 7;
						if (MouseAction(WinX + 158 - 106, WinY + 428, 86, 25))
							SpecItem = 8;
						if (MouseAction(WinX + 158 - 106, WinY + 452, 86, 25))
							SpecItem = 9;
						if (MouseAction(WinX + 158 - 106, WinY + 476, 86, 25))
							SpecItem = 10;
						if (MouseAction(WinX + 158 - 106, WinY + 500, 86, 25))
							SpecItem = 11;
					}
					if (lstrcmpi(recv_items[SelectItem].szCode, "VIP") == 0 || lstrcmpi(recv_items[SelectItem].szCode, "VIP Elite") == 0)
					{
						if (MouseAction(WinX + 120, WinY + 341, 86, 24))
							SpecItem = 0;
						if (MouseAction(WinX + 120, WinY + 365, 86, 24))
							SpecItem = 1;
						if (MouseAction(WinX + 120, WinY + 389, 86, 24))
							SpecItem = 2;
					}
					else
					{
						if (MouseAction(WinX + 120, WinY + 341, 86, 24))
							SpecItem = 1;
						if (MouseAction(WinX + 120, WinY + 365, 86, 24))
							SpecItem = 2;
						if (MouseAction(WinX + 120, WinY + 389, 86, 24))
							SpecItem = 3;
						if (MouseAction(WinX + 120, WinY + 413, 86, 24))
							SpecItem = 4;
						if (MouseAction(WinX + 120, WinY + 437, 86, 24))
							SpecItem = 5;
						if (MouseAction(WinX + 120, WinY + 461, 86, 24))
							SpecItem = 6;
						if (MouseAction(WinX + 120, WinY + 461, 86, 24))
							SpecItem = 6;
						if (MouseAction(WinX + 120, WinY + 485, 86, 24))
							SpecItem = 7;
						if (MouseAction(WinX + 120, WinY + 509, 86, 24))
							SpecItem = 8;
						if (MouseAction(WinX + 120, WinY + 533, 86, 24))
							SpecItem = 9;
						if (MouseAction(WinX + 120, WinY + 557, 86, 24))
							SpecItem = 10;
						if (MouseAction(WinX + 120, WinY + 581, 86, 25))
							SpecItem = 11;
					}

					SpecBox = false;
				}
				else if (ClassBox)
				{
					switch (sItemChange.CODE & sinITEM_MASK2)
					{
					case sinDA1:
					case sinDA2:
					case sinDA3:
					case sinDA4:

						if (MouseAction(WinX + 158 + 20, WinY + 260, 86, 24))
							ClassType = 1;
						if (MouseAction(WinX + 158 + 20, WinY + 284, 86, 25))
							ClassType = 2;

						break;
					case sinDS1:
					case sinOM1:

						if (MouseAction(WinX + 158 + 20, WinY + 260, 86, 24))
							ClassType = 1;
						if (MouseAction(WinX + 158 + 20, WinY + 284, 86, 25))
							ClassType = 2;

						break;
					case sinWP1:
					case sinWT1:
					case sinWM1:
					case sinWS2:
					case sinWS1:
					case sinWH1:
					case sinWA1:
					case sinWC1:
					case sinWN1:
					case sinWD1:
					case sinWV1:

						if (MouseAction(WinX + 158 + 20, WinY + 260, 86, 24))
							ClassType = 1;
						if (MouseAction(WinX + 158 + 20, WinY + 284, 86, 24))
							ClassType = 2;
						if (MouseAction(WinX + 158 + 20, WinY + 308, 86, 24))
							ClassType = 3;
						if (MouseAction(WinX + 158 + 20, WinY + 332, 86, 24))
							ClassType = 4;
						if (MouseAction(WinX + 158 + 20, WinY + 356, 86, 24))
							ClassType = 5;
						if (MouseAction(WinX + 158 + 20, WinY + 380, 86, 24))
							ClassType = 6;
						if (MouseAction(WinX + 158 + 20, WinY + 404, 86, 24))
							ClassType = 7;
						if (MouseAction(WinX + 158 + 20, WinY + 428, 86, 25))
							ClassType = 8;
						if (MouseAction(WinX + 158 + 20, WinY + 452, 86, 25))
							ClassType = 9;
						if (MouseAction(WinX + 158 + 20, WinY + 476, 86, 25))
							ClassType = 10;
						if (MouseAction(WinX + 158 + 20, WinY + 500, 86, 25))
							ClassType = 11;

						break;
					}

					ClassBox = false;
				}
				else
				{
					if (MouseAction(WinX + 255, WinY + 13, 22, 22))
					{
						if (sItemChange.Flag)
						{
							cMessageBox.ShowMessageEvent("Termine o processo antes de mudar de categoria!");
						}
						else
						{
							WinItem = 0;
						}
					}

					if (lstrcmpi(recv_items[SelectItem].szCode, "Class Item") == 0)
					{
						if (MouseAction(WinX + 158 - 106, WinY + 231, 86, 26))
						{
							if (sItemChange.Flag)
							{
								SpecBox = true;
							}
							else
							{
								cMessageBox.ShowMessageEvent("Coloque um item no processo!");
							}
						}

						if (MouseAction(WinX + 158 + 20, WinY + 231, 86, 26))
						{
							if (sItemChange.Flag)
							{
								if ((sItemChange.CODE & sinITEM_MASK2) == sinDG1 || (sItemChange.CODE & sinITEM_MASK2) == sinDB1 || (sItemChange.CODE & sinITEM_MASK2) == sinOA2
									|| (sItemChange.CODE & sinITEM_MASK2) == sinOA1 || (sItemChange.CODE & sinITEM_MASK2) == sinOR2 || (sItemChange.CODE & sinITEM_MASK2) == sinOR1 || (sItemChange.CODE & sinITEM_MASK2) == sinOS1)
								{
									cMessageBox.ShowMessageEvent("Esse requisito não faz parte desse processo!");
								}
								else
								{
									ClassBox = true;
								}
							}
							else
							{
								cMessageBox.ShowMessageEvent("Coloque um item no processo!");
							}
						}

						if (MouseAction(WinX + 158 - 30, WinY + 181 - 20, 60, 60))
						{
							if (sItemChange.Flag)
							{
								if (SpecItem)
								{
									int Flag = 0;
									switch (sItemChange.CODE & sinITEM_MASK2)
									{
									case sinDA1:
									case sinDA2:
									case sinDA3:
									case sinDA4:
										Flag++;
										break;
									case sinDS1:
									case sinOM1:
										Flag++;
										break;
									case sinWP1:
									case sinWT1:
									case sinWM1:
									case sinWS2:
									case sinWS1:
									case sinWH1:
									case sinWA1:
									case sinWC1:
									case sinWN1:
									case sinWD1:
									case sinWV1:
										Flag++;
										break;
									}

									if (Flag && !ClassType)
									{
										cMessageBox.ShowMessageEvent("Selecione a arma!");
										return;
									}

									SendItemToServer();
								}
								else
								{
									cMessageBox.ShowMessageEvent("Selecione o Spec!");
								}
							}
							else
							{
								cMessageBox.ShowMessageEvent("Coloque um item no processo!");
							}
						}
					}
					else
					{
						int Count = Counter + 1;
						int TotalPrice = (recv_items[SelectItem].Price * Count) + recv_items[SelectItem].Price;

						if (lstrcmpi(recv_items[SelectItem].szCode, "VIP") != 0 && lstrcmpi(recv_items[SelectItem].szCode, "VIP Elite") != 0 && lstrcmpi(recv_items[SelectItem].szCode, "Class") != 0)
						{
							if (MouseAction(WinX + 66, WinY + 317, 18, 22))
							{
								if (Coin >= TotalPrice)
									Counter++;
							}

							if (MouseAction(WinX + 85, WinY + 317, 18, 22))
							{
								if (Count > 1)
									Counter--;
							}
						}

						if (MouseAction(WinX + 220, WinY + 315, 75, 26))
						{
							SendBuyItem();
						}

						if (MouseAction(WinX + 120, WinY + 320, 86, 26))
						{
							SpecBox = true;
						}
					}
				}
			}
			else
			{
				int cnt2 = 0;
				for (int cnt = 0; cnt < 500; cnt++)
				{
					if (recv_items[cnt].SubTag && recv_items[cnt].SubTag == SubTag)
					{
						if (recv_items[cnt].Height == 88)
						{
							if (WinY + 42 - (Scroll * 20) >= 142 && WinY + 42 + 88 - (Scroll * 20) <= 452 && MouseAction(WinX + 23, WinY + 42 - (Scroll * 20), 274, 88))
							{
								WinItem = true;
								SelectItem = cnt;
							}
						}
						else
						{
							if (WinY + 42 - (Scroll * 20) >= 142 && WinY + 42 + 66 - (Scroll * 20) <= 452 && MouseAction(WinX + 23, WinY + 42 - (Scroll * 20), 274, 66))
							{
								WinItem = true;
								SelectItem = cnt;
							}
						}
						if (recv_items[cnt].Height == 88)
							WinY += 87;
						else
							WinY += 67;

						cnt2++;
					}
				}
			}

			if (MouseAction(WinX + 280, WinY + 13, 22, 22))
			{
				WinItem = 0;
				SubTag = 0;
			}
		}
	}
}

int CoinShop::GetTotalSlot()
{
	int result = 0;
	int size = 0;
	for (int cnt = 0; cnt < 500; cnt++)
	{
		if (recv_items[cnt].SubTag && recv_items[cnt].SubTag == SubTag)
		{
			result++;
		}
	}

	return result;
}

int CoinShop::GetTotalScroll()
{
	int WinY = 100;
	int result = 0;
	int scroll = 0;
	for (int cnt = 0; cnt < 500; cnt++)
	{
		if (recv_items[cnt].SubTag && recv_items[cnt].SubTag == SubTag)
		{
			if (recv_items[cnt].Height == 88)
				WinY += 87;
			else
				WinY += 67;

			result++;
		}
	}

	while (WinY > 392)
	{
		WinY -= 20;
		scroll++;
	}

	return scroll;
}

int CoinShop::GetTotalScroll2()
{
	int WinY = 100;
	int result = 0;
	int scroll = 0;

	int TotalSubTag = 0, Init = 0;

	switch (Tag)
	{
	case TAG_ACESSORIES:
		TotalSubTag = 5;
		break;
	case TAG_DEFENSE:
		TotalSubTag = 7;
		Init = 5;
		break;
	case TAG_WEAPONS:
		TotalSubTag = 11;
		Init = 12;
		break;
	case TAG_PREMIUM:
		TotalSubTag = 6;
		Init = 23;
		break;
	case TAG_FUN:
		TotalSubTag = 2;
		Init = 29;
		break;
	case 6:
		TotalSubTag = 13;
		Init = 31;
		break;
	}

	WinY = 100 + 44 + TotalSubTag * 33 + 77;

	while (WinY > 100 + 75 + 7 * 33 + 77)
	{
		WinY -= 20;
		scroll++;
	}

	return scroll;
}

void CoinShop::ButtonScroll(short Dist)
{
	if (fOpen)
	{
		if (MouseAction(80, 100, 316, 362))
		{
			if (Dist > 0)
			{
				if (Scroll2)
					Scroll2--;
			}
			else if (Dist < 0 && Scroll2 < GetTotalScroll2())
			{
				Scroll2++;
			}
		}
		else
		{
			if (Dist > 0)
			{
				if (Scroll)
					Scroll--;
			}
			else if (Dist < 0 && Scroll < GetTotalScroll())
			{
				Scroll++;
			}
		}
	}
}

void CoinShop::Close()
{
	if (sItemChange.Flag)
	{
		cMessageBox.ShowMessageEvent("Termine o processo antes de fechar a loja!");
		return;
	}

	fOpen = false;

	for (int cnt = 0; cnt < 500; cnt++)
	{
		if (recv_items[cnt].Flag)
		{
			if (recv_items[cnt].Image)
			{
				recv_items[cnt].Image->Release();
				recv_items[cnt].Image = NULL;
			}
		}
	}

	memset(recv_items, 0, sizeof(ITEM_COIN_SHOP) * 500);
}