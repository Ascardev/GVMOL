#include "sinbaram\sinLinkHeader.h"

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);

PACKET_COIN_SHOP_BUY cTPacket;

ITEM_COIN_SHOP recv_items[150];

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

void TimeShop::SendList(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		int i = 0;
		char szQuery[512];
		PACKET_COIN_SHOP packet;
		ZeroMemory(&packet, sizeof(PACKET_COIN_SHOP));
		packet.size = sizeof(PACKET_COIN_SHOP);
		if (packet.size >= smSOCKBUFF_SIZE) packet.size = smSOCKBUFF_SIZE;
		packet.code = smTRANSCODE_SEND_TIME_SHOP_LIST;
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[TimeShop_List]");
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

				if (i > 149) break;
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void TimeShop::SendTime(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		smTRANS_COMMAND packet;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[TimeShop_Time] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &packet.WParam);
				packet.size = sizeof(smTRANS_COMMAND);
				packet.code = smTRANSCODE_SEND_TIME_SHOP_TIME;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
			}
			else
			{
				packet.size = sizeof(smTRANS_COMMAND);
				packet.code = smTRANSCODE_SEND_TIME_SHOP_TIME;
				packet.WParam = 0;
				if (Player->lpsmSock)
					Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void TimeShop::Recv(PACKET_COIN_SHOP* packet)
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

void TimeShop::RecvTime(smTRANS_COMMAND* packet)
{
	Time = packet->WParam;
}

void TimeShop::RecvBuyItem(rsPLAYINFO* Player, PACKET_COIN_SHOP_BUY* packet)
{
	if (packet->cnt < 0 && strlen(packet->szCode) > 32)
		return;

	if (SQL::GetInstance()->IsConnected())
	{
		int UserTime = 0, ItemPrice = 0;
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[TimeShop_Time] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &UserTime);
			}
			else
			{
				return;
			}
		}

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[TimeShop_List] WHERE [szCode]='%s'", packet->szCode);
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

		if (UserTime >= ItemPrice)
		{
			int OldTime = UserTime;
			UserTime -= ItemPrice;
			wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[TimeShop_Time] SET Time=%d WHERE [ID]='%s'", UserTime, Player->szID);
			SQL::GetInstance()->Execute(szQuery);
			SendTime(Player);

			for (int cnt = 0; cnt < packet->cnt; cnt++)
			{
				SendItemToPlayer(Player, packet->szCode, packet->spec);
			}

			LOGEx(Player, "TShop", "Buyed szCode:%s,Quantity:%d,Spec:%d,OldTime:%d,NowTime:%d", packet->szCode, packet->cnt, packet->spec, OldTime, UserTime);
		}

		SQL::GetInstance()->LeaveSqlSection();
	}
}

void TimeShop::Init()
{
	IMG_TAG[0] = CreateTextureMaterial("game\\images\\coin\\tabs\\accessories.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[1] = CreateTextureMaterial("game\\images\\coin\\tabs\\premium.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[2] = CreateTextureMaterial("game\\images\\coin\\tabs\\fun.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAG[3] = CreateTextureMaterial("game\\images\\coin\\tabs\\skin.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	IMG_TAGH[0] = CreateTextureMaterial("game\\images\\coin\\tabs\\accessories_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[1] = CreateTextureMaterial("game\\images\\coin\\tabs\\premium_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[2] = CreateTextureMaterial("game\\images\\coin\\tabs\\fun_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	IMG_TAGH[3] = CreateTextureMaterial("game\\images\\coin\\tabs\\skin_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	cImages[0] = CreateTextureMaterial("game\\images\\coin\\window.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[1] = CreateTextureMaterial("game\\images\\coin\\logo.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
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
	cImages[47] = CreateTextureMaterial("game\\images\\coin\\time.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	IMG_SUB_TAG[0] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\amulets.bmp");
	IMG_SUB_TAG[1] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\rings.bmp");
	IMG_SUB_TAG[2] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\sheltoms.bmp");
	IMG_SUB_TAG[3] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\forceorbs.bmp");
	IMG_SUB_TAG[4] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\aging.bmp");
	IMG_SUB_TAG[5] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\mixing.bmp");
	IMG_SUB_TAG[6] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\crystals.bmp");
	IMG_SUB_TAG[7] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\pets.bmp");
	IMG_SUB_TAG[8] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumes.bmp");
	IMG_SUB_TAG[9] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumesmg.bmp");
	IMG_SUB_TAG[10] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\axes.bmp");
	IMG_SUB_TAG[11] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\armors.bmp");
	IMG_SUB_TAG[12] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\shields.bmp");
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

	IMG_SUB_TAGH[0] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\amulets_.bmp");
	IMG_SUB_TAGH[1] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\rings_.bmp");
	IMG_SUB_TAGH[2] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\sheltoms_.bmp");
	IMG_SUB_TAGH[3] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\forceorbs_.bmp");
	IMG_SUB_TAGH[4] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\aging_.bmp");
	IMG_SUB_TAGH[5] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\mixing_.bmp");
	IMG_SUB_TAGH[6] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\crystals_.bmp");
	IMG_SUB_TAGH[7] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\pets_.bmp");
	IMG_SUB_TAGH[8] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumes_.bmp");
	IMG_SUB_TAGH[9] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\costumesmg_.bmp");
	IMG_SUB_TAGH[10] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\axes_.bmp");
	IMG_SUB_TAGH[11] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\armors_.bmp");
	IMG_SUB_TAGH[12] = LoadDibSurfaceOffscreen("game\\images\\coin\\tabs\\child\\shields_.bmp");
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
}

bool TimeShop::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void TimeShop::DrawItemOnList(int Line, LPDIRECT3DTEXTURE9 Image, char* Name, int Price, char* Description1, char* Description2, int num, int Width, int Height, int WinX, int WinY)
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
		DrawText(Description1, WinX + 110, WinY + 65, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));
	if (WinY + 85 >= 142 && WinY + 85 + 15 <= 452)
		DrawText(Description2, WinX + 110, WinY + 85, RegularFont, D3DCOLOR_RGBA(255, 255, 255, 255));

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

void DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}

void TimeShop::DrawItemOnDetails(LPDIRECT3DTEXTURE9 Image, char* Name, int Price, int Width, int Height)
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
		wsprintf(szBuff, "%s%d", sinAbilityName[2], recv_items[SelectItem].ItemInfo.Attack_Speed);
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
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Strength)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[29], recv_items[SelectItem].ItemInfo.Strength);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Spirit)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[30], recv_items[SelectItem].ItemInfo.Spirit);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Talent)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[31], recv_items[SelectItem].ItemInfo.Talent);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Dexterity)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[32], recv_items[SelectItem].ItemInfo.Dexterity);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.Health)
	{
		wsprintf(szBuff, "%s%d", sinAbilityName[33], recv_items[SelectItem].ItemInfo.Health);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Attack_Speed)
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[0], recv_items[SelectItem].ItemInfo.JobItem.Add_Attack_Speed);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Critical_Hit)
	{
		wsprintf(szBuff, "%s%d%s", sinSpecialName[1], recv_items[SelectItem].ItemInfo.JobItem.Add_Critical_Hit, "%");
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Defence)
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[2], recv_items[SelectItem].ItemInfo.JobItem.Add_Defence);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fAbsorb)
	{
		int sinAbsorb = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fAbsorb * 10.001f);
		int sinRightSpot = sinAbsorb % 10;
		int sinLeftSpot = (sinAbsorb - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[3], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fBlock_Rating)
	{
		int BlockRate = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fBlock_Rating);
		wsprintf(szBuff, "%s%d%s", sinSpecialName[4], BlockRate, "%");
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fMagic_Mastery)
	{
		int sinMagic_Mastery = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fMagic_Mastery);
		wsprintf(szBuff, "%s%d", sinSpecialName[5], sinMagic_Mastery);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_fSpeed)
	{
		int sinSpeed = (int)(recv_items[SelectItem].ItemInfo.JobItem.Add_fSpeed * 10.001f);
		int sinRightSpot = sinSpeed % 10;
		int sinLeftSpot = (sinSpeed - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[6], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[0])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[7], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[0]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[1])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[8], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[2]) {
		wsprintf(szBuff, "%s%d", sinSpecialName[9], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[2]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[3])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[10], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[3]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[4])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[11], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[4]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[5])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[12], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[5]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[6])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[13], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[6]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[7])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[14], recv_items[SelectItem].ItemInfo.JobItem.Add_Resistance[7]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Damage[1])
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[15], recv_items[SelectItem].ItemInfo.JobItem.Lev_Damage[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Rating)
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[16], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Rating);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Add_Shooting_Range)
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[17], recv_items[SelectItem].ItemInfo.JobItem.Add_Shooting_Range);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[0])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[18], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[0]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[1])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[19], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[1]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[2])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[20], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[2]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[3])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[21], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[3]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[4])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[22], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[4]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[5])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[23], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[5]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[6])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[24], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[6]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[7])
	{
		wsprintf(szBuff, "%s%d", sinSpecialName[25], recv_items[SelectItem].ItemInfo.JobItem.Lev_Attack_Resistance[7]);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Life)
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[26], recv_items[SelectItem].ItemInfo.JobItem.Lev_Life);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Lev_Mana)
	{
		wsprintf(szBuff, "%sLV/%d", sinSpecialName[27], recv_items[SelectItem].ItemInfo.JobItem.Lev_Mana);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Per_Life_Regen)
	{
		int sinPer_Regen = (int)(recv_items[SelectItem].ItemInfo.JobItem.Per_Life_Regen * 10.001f);
		int sinRightSpot = sinPer_Regen % 10;
		int sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[28], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Per_Mana_Regen)
	{
		int sinPer_Regen = (int)(recv_items[SelectItem].ItemInfo.JobItem.Per_Mana_Regen * 10.001f);
		int sinRightSpot = sinPer_Regen % 10;
		int sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[29], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	if (recv_items[SelectItem].ItemInfo.JobItem.Per_Stamina_Regen)
	{
		int sinPer_Regen = (int)(recv_items[SelectItem].ItemInfo.JobItem.Per_Stamina_Regen * 10.001f);
		int sinRightSpot = sinPer_Regen % 10;
		int sinLeftSpot = (sinPer_Regen - sinRightSpot) / 10;
		wsprintf(szBuff, "%s%d.%d", sinSpecialName[30], sinLeftSpot, sinRightSpot);
		DrawText(szBuff, WinX + 120, WinY + 70 + ItemY * 13, CoinFont[1], D3DCOLOR_RGBA(255, 255, 255, 255));
		ItemY++;
	}

	int Count = Counter + 1;
	int TotalPrice = Price * Count;
	wsprintf(szBuff, "TOTAL: %d", TotalPrice);
	DrawText(szBuff, WinX + 25, WinY + 280, CoinFont[0], D3DCOLOR_RGBA(255, 255, 255, 255));
	wsprintf(szBuff, "%d", Count);
	TotalPrice += Price;

	HoDrawTexImage(cImages[36], WinX + 25, WinY + 315, 80.f, 26.f, 0, 0, 80.f, 26.f, 255);

	if (MouseAction(WinX + 66, WinY + 317, 18, 22))
	{
		if (Time >= TotalPrice)
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

	if (SpecBox)
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

	if (MouseAction(WinX + 220, WinY + 315, 75, 26))
		DrawImage(cImages[28], WinX + 220, WinY + 315, 75, 26);
	else
		DrawImage(cImages[27], WinX + 220, WinY + 315, 75, 26);
}

void TimeShop::Draw()
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
		wsprintf(szBuff, "%d", Time);

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
			TotalSubTag = 4;
			break;
		case TAG_PREMIUM:
			TotalSubTag = 4;
			Init = 4;
			break;
		case TAG_FUN:
			TotalSubTag = 2;
			Init = 8;
			break;
		case 4:
			TotalSubTag = 13;
			Init = 10;
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

				for (int cnt = 0; cnt < 150; cnt++)
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

void TimeShop::DrawText(char* Text, int x, int y, ID3DXFont* RegularFont, D3DCOLOR Color)
{
	RECT rc;
	rc.left = x;
	rc.right = x + smScreenWidth;
	rc.top = y;
	rc.bottom = y + smScreenHeight;
	RegularFont->DrawText(NULL, Text, strlen(Text), &rc, 0, Color);
}

void TimeShop::SendBuyItem()
{
	if (sinChar->Weight[0] + recv_items[SelectItem].ItemInfo.Weight > sinChar->Weight[1])
	{
		cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
		return;
	}

	int Count = Counter + 1;

	if (Time < (recv_items[SelectItem].Price * Count))
	{
		cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_TIME);
		return;
	}

	ZeroMemory(&cTPacket, sizeof(PACKET_COIN_SHOP_BUY));
	cTPacket.size = sizeof(PACKET_COIN_SHOP_BUY);
	cTPacket.code = smTRANSCODE_RECV_BUY_TIME_SHOP;
	lstrcpy(cTPacket.szCode, recv_items[SelectItem].szCode);
	cTPacket.spec = SpecItem;
	cTPacket.cnt = Count;

	cMessageBox.ShowMessage3(MESSAGE_BUY_TIME_SHOP, "Minutos");
}

void TimeShop::LButton(int x, int y)
{
	if (fOpen)
	{
		int WinX = 80, WinY = 100;

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
			TotalSubTag = 4;
			break;
		case TAG_PREMIUM:
			TotalSubTag = 4;
			Init = 4;
			break;
		case TAG_FUN:
			TotalSubTag = 2;
			Init = 8;
			break;
		case 4:
			TotalSubTag = 13;
			Init = 10;
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

					SpecBox = false;
				}
				else
				{
					if (MouseAction(WinX + 255, WinY + 13, 22, 22))
						WinItem = 0;

					int Count = Counter + 1;
					int TotalPrice = (recv_items[SelectItem].Price * Count) + recv_items[SelectItem].Price;

					if (MouseAction(WinX + 66, WinY + 317, 18, 22))
					{
						if (Time >= TotalPrice)
							Counter++;
					}

					if (MouseAction(WinX + 85, WinY + 317, 18, 22))
					{
						if (Count > 1)
							Counter--;
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
			else
			{
				int cnt2 = 0;
				for (int cnt = 0; cnt < 150; cnt++)
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

int TimeShop::GetTotalScroll()
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

void TimeShop::ButtonScroll(short Dist)
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

int TimeShop::GetTotalScroll2()
{
	int WinY = 100;
	int result = 0;
	int scroll = 0;

	int TotalSubTag = 0, Init = 0;

	switch (Tag)
	{
	case TAG_ACESSORIES:
		TotalSubTag = 4;
		break;
	case TAG_PREMIUM:
		TotalSubTag = 4;
		Init = 4;
		break;
	case TAG_FUN:
		TotalSubTag = 2;
		Init = 8;
		break;
	case 4:
		TotalSubTag = 13;
		Init = 10;
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

void TimeShop::Close()
{
	fOpen = false;

	for (int cnt = 0; cnt < 150; cnt++)
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

	memset(recv_items, 0, sizeof(ITEM_COIN_SHOP) * 150);
}