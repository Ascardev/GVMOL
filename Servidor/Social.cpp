#include "sinbaram\sinLinkHeader.h"
#include "TJBOY/clanmenu/cE_CViewClanInfo.h"

extern int DrawClanMark_EachBox(LPDIRECT3DTEXTURE9 clanMark, int x, int y);

int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
int GetStatus(char* Name);
//void pUpdateStatus();

rsPLAYINFO* FindUserFromName2(char* szName);

void Social::SendList(rsPLAYINFO* Player, char* ClanName)
{
	if (!Player)
		return;

	if (SQL::GetInstance()->IsConnected())
	{
		int i = 0;
		char szQuery[256];
		char szLeader[256];
		PACKET_SOCIAL packet;
		ZeroMemory(&packet, sizeof(PACKET_SOCIAL));
		packet.size = sizeof(PACKET_SOCIAL);
		packet.code = PSOCIAL_ACTION;
		packet.action = 5;
		Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
		packet.action = 4;
		SQL::GetInstance()->EnterSqlSection();

		wsprintf(szQuery, "SELECT * FROM [ClanDB].[dbo].[CL] WHERE [ClanName]='%s'", ClanName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(6, szLeader);
			}
		}

		wsprintf(szQuery, "SELECT * FROM [ClanDB].[dbo].[UL] WHERE [ClanName]='%s'", ClanName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(4, packet.name);

				char szFile[512];
				TRANS_RECORD_DATA TransRecordData;
				GetUserDataFile(packet.name, szFile);
				ZeroMemory(&TransRecordData, sizeof(TRANS_RECORD_DATA));

				FILE* fp = fopen(szFile, "rb");
				if (fp)
				{
					fread(&TransRecordData, sizeof(TRANS_RECORD_DATA), 1, fp);
					fclose(fp);
				}

				packet.Class = TransRecordData.smCharInfo.JOB_CODE;
				packet.Level = TransRecordData.smCharInfo.Level;

				if (lstrcmpi(packet.name, szLeader) == 0)
					packet.Type = 1;
				else
					packet.Type = 0;

				Player->lpsmSock->Send((char*)&packet, packet.size, TRUE);

				i++;

				if (i > 100) break;
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::SendClanList(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512], ClanName[256], szName[32];
		wsprintf(szQuery, "SELECT * FROM [ClanDB].[dbo].[UL] WHERE [ChName]='%s'", Player->szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(7, ClanName);
				wsprintf(szQuery, "SELECT * FROM [ClanDB].[dbo].[UL] WHERE [ClanName]='%s'", ClanName);
				if (SQL::GetInstance()->Execute(szQuery))
				{
					while (SQL::GetInstance()->Fetch())
					{
						SQL::GetInstance()->GetDataValue(4, szName);
						SendList(FindUserFromName2(szName), "Revenge");
					}
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::UpdateStatus(char* Name)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[FriendList] SET Status=1 WHERE [Friend]='%s'", Name);
		SQL::GetInstance()->Execute(szQuery);
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::SendFriendList(rsPLAYINFO* player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		int i = 0;
		PACKET_SOCIAL packet;
		packet.size = sizeof(PACKET_SOCIAL);
		packet.code = PSOCIAL_ACTION;
		packet.action = 0;
		player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
		packet.action = 2;
		SQL::GetInstance()->EnterSqlSection();
		SQL::GetInstance()->Execute("UPDATE [PristonDB].[dbo].[FriendList] SET Status=0");
		//pUpdateStatus();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[FriendList] WHERE [Name]='%s' ORDER BY Status DESC", player->smCharInfo.szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, packet.name);
				SQL::GetInstance()->GetDataValue(3, &packet.Class);
				SQL::GetInstance()->GetDataValue(4, &packet.Status);
				player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
				i++;

				if (i > 100) break;
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

int Social::YouAreRefuse(rsPLAYINFO* player1, rsPLAYINFO* player2)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[RefuseList] WHERE [Name]='%s' AND [Refuse]='%s'", player1->smCharInfo.szName, player2->smCharInfo.szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				return TRUE;
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	return FALSE;
}

void Social::SendRefuseList(rsPLAYINFO* player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		int i = 0;
		PACKET_SOCIAL packet;
		packet.size = sizeof(PACKET_SOCIAL);
		packet.code = PSOCIAL_ACTION;
		packet.action = 1;
		player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
		packet.action = 3;
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[RefuseList] WHERE [Name]='%s'", player->smCharInfo.szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, packet.name);
				player->lpsmSock->Send((char*)&packet, packet.size, TRUE);
				i++;

				if (i > 100) break;
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::AddOnFriendList(rsPLAYINFO* player, char* name)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szFile[512];
		TRANS_RECORD_DATA TransRecordData;
		GetUserDataFile(name, szFile);
		ZeroMemory(&TransRecordData, sizeof(TRANS_RECORD_DATA));

		FILE* fp = fopen(szFile, "rb");
		if (fp)
		{
			fread(&TransRecordData, sizeof(TRANS_RECORD_DATA), 1, fp);
			fclose(fp);
		}
		else return;

		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[FriendList] WHERE [Name]='%s' AND [Friend]='%s'", player->smCharInfo.szName, name);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (!SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[FriendList] ([Name],[Friend],[Class],[Status]) values('%s','%s','%d',0)", player->smCharInfo.szName, name, TransRecordData.smCharInfo.JOB_CODE);
				SQL::GetInstance()->Execute(szQuery);
				rsSendServerChatMessageToUser(player, 0, "> Added %s to Friends List!", name);
				SendFriendList(player);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::DeleteOnFriendList(rsPLAYINFO* player, char* name)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[FriendList] WHERE [Name]='%s' AND [Friend]='%s'", player->smCharInfo.szName, name);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[FriendList] WHERE [Name]='%s' AND [Friend]='%s'", player->smCharInfo.szName, name);
				SQL::GetInstance()->Execute(szQuery);
				SendFriendList(player);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::AddOnRefuseList(rsPLAYINFO* player, char* name)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[RefuseList] WHERE [Name]='%s' AND [Refuse]='%s'", player->smCharInfo.szName, name);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (!SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[RefuseList] ([Name],[Refuse]) values('%s','%s')", player->smCharInfo.szName, name);
				SQL::GetInstance()->Execute(szQuery);
				rsSendServerChatMessageToUser(player, 0, "> Added %s to Blocked List!", name);
				SendRefuseList(player);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::DeleteOnRefuseList(rsPLAYINFO* player, char* name)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[RefuseList] WHERE [Name]='%s' AND [Refuse]='%s'", player->smCharInfo.szName, name);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "DELETE FROM [PristonDB].[dbo].[RefuseList] WHERE [Name]='%s' AND [Refuse]='%s'", player->smCharInfo.szName, name);
				SQL::GetInstance()->Execute(szQuery);
				SendRefuseList(player);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void Social::SendAction(rsPLAYINFO* player, PACKET_SOCIAL* packet)
{
	if (strlen(packet->name) > 32)
		return;

	switch (packet->action)
	{
	case 0:
		SendFriendList(player);
		break;
	case 1:
		SendRefuseList(player);
		break;
	case 2:
		AddOnFriendList(player, packet->name);
		break;
	case 3:
		DeleteOnFriendList(player, packet->name);
		break;
	case 4:
		AddOnRefuseList(player, packet->name);
		break;
	case 5:
		DeleteOnRefuseList(player, packet->name);
		break;
	case 6:
		SendClanList(player);
		break;
	}
}

void Social::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\social\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\social\\ClExit.png.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\social\\friend.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\social\\clan.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\social\\hover_recent.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[5] = CreateTextureMaterial("game\\images\\social\\hover_friend.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[6] = CreateTextureMaterial("game\\images\\social\\hover_block.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[7] = CreateTextureMaterial("game\\images\\social\\add.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[8] = CreateTextureMaterial("game\\images\\social\\add_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[9] = CreateTextureMaterial("game\\images\\social\\friend_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[10] = CreateTextureMaterial("game\\images\\social\\clan_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[11] = CreateTextureMaterial("game\\images\\social\\select_recent.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[12] = CreateTextureMaterial("game\\images\\social\\select_friend.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[13] = CreateTextureMaterial("game\\images\\social\\select_block.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[14] = CreateTextureMaterial("game\\images\\social\\online_icon.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[15] = CreateTextureMaterial("game\\images\\social\\add_delete.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[16] = CreateTextureMaterial("game\\images\\social\\hover_add.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[17] = CreateTextureMaterial("game\\images\\social\\hover_delete.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[18] = CreateTextureMaterial("game\\images\\social\\friend_icon.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[19] = CreateTextureMaterial("game\\images\\social\\friend_icon_off.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[20] = CreateTextureMaterial("game\\images\\social\\clan.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Images[21] = CreateTextureMaterial("game\\images\\social\\bless.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[22] = CreateTextureMaterial("game\\images\\social\\bless.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[23] = CreateTextureMaterial("game\\images\\social\\bless.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[24] = CreateTextureMaterial("game\\images\\social\\sod1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[25] = CreateTextureMaterial("game\\images\\social\\sod2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[26] = CreateTextureMaterial("game\\images\\social\\sod3.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[27] = CreateTextureMaterial("game\\images\\social\\scroll.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[28] = CreateTextureMaterial("game\\images\\social\\scroller.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[29] = CreateTextureMaterial("game\\images\\social\\friend_select.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[30] = CreateTextureMaterial("game\\images\\social\\clan_select.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[31] = CreateTextureMaterial("game\\images\\social\\recent_icon.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[32] = CreateTextureMaterial("game\\images\\social\\block_icon.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[33] = CreateTextureMaterial("game\\images\\social\\arrow_top.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[34] = CreateTextureMaterial("game\\images\\social\\arrow_top_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[35] = CreateTextureMaterial("game\\images\\social\\arrow_down.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[36] = CreateTextureMaterial("game\\images\\social\\arrow_down_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[37] = CreateTextureMaterial("game\\images\\social\\background_2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[38] = CreateTextureMaterial("game\\images\\social\\crown_leader.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[39] = CreateTextureMaterial("game\\images\\social\\crown_mb.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	ImagesJob[0] = CreateTextureMaterial("game\\images\\social\\class_fs.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[1] = CreateTextureMaterial("game\\images\\social\\class_ms.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[2] = CreateTextureMaterial("game\\images\\social\\class_as.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[3] = CreateTextureMaterial("game\\images\\social\\class_ps.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[4] = CreateTextureMaterial("game\\images\\social\\class_ata.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[5] = CreateTextureMaterial("game\\images\\social\\class_ks.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[6] = CreateTextureMaterial("game\\images\\social\\class_mg.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[7] = CreateTextureMaterial("game\\images\\social\\class_prs.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[8] = CreateTextureMaterial("game\\images\\social\\class_ass.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	ImagesJob[9] = CreateTextureMaterial("game\\images\\social\\class_sh.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	NowX = 290;
	MoveX = WinSizeX - 290;
	MoveY = WinSizeY / 2 - 553 / 2;
	Opacity = 0;
}

bool Social::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Social::DrawImage(int Texture, int x, int y, int w, int h, int op)
{
	dsDrawTexImage(Texture, x, y, w - 1, h - 1, op);
}

void Social::Main()
{
	if (!Show)
	{
		if (Opacity != 0)
		{
			Opacity -= 15;
		}
	}
	else
	{
		if (Opacity != 255)
		{
			Opacity += 15;
		}
	}
}

void Social::DoubleClick()
{
	if (Show)
	{
		int WinX = MoveX, WinY = MoveY;

		if (Tag == 0)
		{
			if (SubTag == 0)
			{
				for (int i = 0; i < 7; i++)
				{
					int strsize = strlen(InterfaceParty_KTJ.latestb[i]);
					if (strsize)
					{
						if (MouseAction(WinX + 30, WinY + 121 + i * 20, 229, 22) || Check - 1 == i && Check > 0)
							WhisperPartyPlayer(InterfaceParty_KTJ.latestb[i]);
					}
				}
			}
			else if (SubTag == 1)
			{
				for (int i = 0; i < 100; i++)
				{
					if (WinY + 121 + i * 22 - Scroll * 5 >= WinY + 115 && WinY + 121 + i * 22 - Scroll * 5 + 22 <= WinY + 458)
					{
						if (MouseAction(WinX + 30, WinY + 121 + i * 22 - Scroll * 5, 229, 22) || Check - 1 == i && Check > 0)
						{
							WhisperPartyPlayer(InterfaceParty_KTJ.fNameb[i]);
						}
					}
				}
			}
		}
		else if (Tag == 1)
		{
			for (int i = 0; i < cnt3; i++)
			{
				if (WinY + 100 + i * 17 - Scroll * 17 >= WinY + 100 && WinY + 100 + i * 17 - Scroll * 17 + 17 <= WinY + 280)
				{
					if (MouseAction(WinX + 12, WinY + 100 + i * 17 - Scroll * 17, 188, 17))
					{
						WhisperPartyPlayer(ClanList[i].name);
					}
				}
			}
		}
	}
}

void Social::ButtonUp()
{
	if (Show)
	{
		MoveWindow = false;
		ButtonU = false;
	}
}

void Social::Button()
{
	if (Show)
	{
		int WinX = MoveX, WinY = MoveY;

		if (MouseAction(WinX + 5, WinY, 245, 46))
		{
			MoveWindow = true;

			if (pRealCursorPos.x > MoveX)
				Cursor.x = pRealCursorPos.x - MoveX;
			else
				Cursor.x = MoveX - pRealCursorPos.x;

			if (pRealCursorPos.y > MoveY)
				Cursor.y = pRealCursorPos.y - MoveY;
			else
				Cursor.y = MoveY - pRealCursorPos.y;
		}

		if (MouseAction(WinX + 249, WinY + 17, 26, 26))
		{
			Show = false;
			MoveWindow = false;
		}

		if (MouseAction(WinX + 30, WinY + 52, 108, 19) && Tag != 0)
		{
			Tag = 0;
			Scroll = 0;
			MoveWindow = false;
		}

		if (MouseAction(WinX + 153, WinY + 53, 108, 19) && Tag != 1)
		{
			Tag = 1;
			Scroll = 0;
			MoveWindow = false;
		}

		if (Tag == 0)
		{
			if (MouseAction(WinX + 90, WinY + 87, 34, 28))
			{
				Check = 0;
				SubTag = 0;
				Scroll = 0;
				MoveWindow = false;
			}

			if (MouseAction(WinX + 128, WinY + 87, 34, 28))
			{
				Check = 0;
				SubTag = 1;
				Scroll = 0;
				MoveWindow = false;
			}

			if (MouseAction(WinX + 166, WinY + 87, 34, 28))
			{
				Check = 0;
				SubTag = 2;
				Scroll = 0;
				MoveWindow = false;
			}

			if (SubTag == 0)
			{
				for (int i = 0; i < 7; i++)
				{
					int strsize = strlen(InterfaceParty_KTJ.latestb[i]);
					if (strsize)
					{
						if (MouseAction(WinX + 30, WinY + 121 + i * 20, 229, 22) || Check - 1 == i && Check > 0)
						{
							Check = i + 1;
							MoveWindow = false;
						}
					}
				}
			}
			else if (SubTag == 1)
			{
				for (int i = 0; i < 100; i++)
				{
					if (WinY + 121 + i * 22 - Scroll * 5 >= WinY + 115 && WinY + 121 + i * 22 - Scroll * 5 + 22 <= WinY + 458)
					{
						if (MouseAction(WinX + 30, WinY + 121 + i * 22 - Scroll * 5, 229, 22) || Check - 1 == i && Check > 0)
						{
							Check = i + 1;
							MoveWindow = false;
						}
					}
				}

				if (MouseAction(WinX + 209, WinY + 461, 24, 24))
				{
					//AddWhisperFriend();
					MoveWindow = false;
				}

				if (MouseAction(WinX + 235, WinY + 461, 24, 24))
				{
					DeleteFriend(FriendList[Check - 1].name);
					MoveWindow = false;
				}

				int TotalScroll = GetTotalScroll();

				if (TotalScroll)
				{
					if (MouseAction(WinX + 243, WinY + 445, 12, 10))
					{
						if (Scroll < TotalScroll)
							Scroll++;
					}

					if (MouseAction(WinX + 243, WinY + 118, 12, 10))
					{
						if (Scroll)
						{
							Scroll--;
						}
					}
				}
			}
			else if (SubTag == 2)
			{
				for (int i = 0; i < cnt2; i++)
				{
					if (WinY + 121 + i * 20 - Scroll * 5 >= WinY + 115 && WinY + 121 + i * 20 - Scroll * 5 + 22 <= WinY + 458)
					{
						if (MouseAction(WinX + 30, WinY + 121 + i * 20 - Scroll * 5, 229, 22) || Check - 1 == i && Check > 0)
						{
							Check = i + 1;
							MoveWindow = false;
						}
					}
				}

				if (MouseAction(WinX + 209, WinY + 461, 24, 24))
				{
					//WhisperBlock();
					MoveWindow = false;
				}

				if (MouseAction(WinX + 235, WinY + 461, 24, 24))
				{
					DeleteRefuse(RefuseList[Check - 1].name);
					MoveWindow = false;
				}
			}
		}
		else if (Tag == 1)
		{
		}
	}
}

int Social::GetTotalClan()
{
	int result = 0;
	for (int i = 0; i < cnt3; i++)
	{
		if (ClanList[i].Status)
			result++;
	}
	return result;
}

int Social::GetTotalFriend()
{
	int result = 0;
	for (int i = 0; i < 100; i++)
	{
		if (InterfaceParty_KTJ.fClass[i])
		{
			result++;
		}
	}
	return result;
}

int Social::GetTotalScroll()
{
	int result = 0;
	int Begin = MoveY + 458;
	int End;

	if (Tag == 0)
	{
		if (SubTag == 1)
			End = MoveY + 115 + cnt1 * 22;
		else if (SubTag == 2)
			End = MoveY + 115 + cnt2 * 20;
	}
	else End = MoveY + 115 + cnt3 * 22;

	while (End > Begin)
	{
		if (Tag == 0)
		{
			if (SubTag == 1)
				End = MoveY + 115 + cnt1 * 22 - result * 5;
			else
				End = MoveY + 115 + cnt2 * 22 - result * 5;
		}
		else End = MoveY + 115 + cnt3 * 22 - result * 5;

		result++;
	}

	return result;
}

void Social::Resize()
{
	MoveX = WinSizeX - 290;
	MoveY = WinSizeY / 2 - 553 / 2;
}

void Social::Draw()
{
	int WinX = MoveX, WinY = MoveY;

	if (Show)
	{
		if (MoveWindow)
		{
			if (pRealCursorPos.x < WinSizeX && pRealCursorPos.x > 0)
			{
				MoveX = pCursorPos.x - Cursor.x;
			}

			if (pRealCursorPos.y < WinSizeY && pRealCursorPos.y > 0)
			{
				MoveY = pRealCursorPos.y - Cursor.y;
			}
		}
	}

	FontType = 1;

	if (Tag == 0)
		DrawImage(Images[0], MoveX, MoveY, 289, 503, Opacity);
	else if (Tag == 1)
		DrawImage(Images[37], MoveX, MoveY, 289, 503, Opacity);

	DrawImage(Images[2], WinX + 30, WinY + 52, 108, 19, Opacity);
	DrawImage(Images[3], WinX + 153, WinY + 53, 108, 19, Opacity);

	if (MouseAction(WinX + 249, WinY + 17, 26, 26))
		DrawImage(Images[1], WinX + 249, WinY + 17, 26, 26, Opacity);

	if (Tag == 0)
		DrawImage(Images[29], WinX + 30, WinY + 52, 108, 19, Opacity);
	if (Tag == 1)
		DrawImage(Images[30], WinX + 153, WinY + 53, 108, 19, Opacity);

	if (MouseAction(WinX + 30, WinY + 52, 108, 19) && Tag != 0)
		DrawImage(Images[9], WinX + 30, WinY + 52, 108, 19, Opacity);
	if (MouseAction(WinX + 153, WinY + 53, 108, 19) && Tag != 1)
		DrawImage(Images[10], WinX + 153, WinY + 53, 108, 19, Opacity);

	SetFontOpacity(Opacity);

	if (Tag == 0)
	{
		if (SubTag == 0)
			DrawImage(Images[11], WinX + 90, WinY + 87, 34, 28, Opacity);
		if (SubTag == 1)
			DrawImage(Images[12], WinX + 128, WinY + 87, 34, 28, Opacity);
		if (SubTag == 2)
			DrawImage(Images[13], WinX + 166, WinY + 87, 34, 28, Opacity);

		if (MouseAction(WinX + 90, WinY + 87, 34, 28) && SubTag != 0)
			DrawImage(Images[4], WinX + 90, WinY + 87, 34, 28, Opacity);
		if (MouseAction(WinX + 128, WinY + 87, 34, 28) && SubTag != 1)
			DrawImage(Images[5], WinX + 128, WinY + 87, 34, 28, Opacity);
		if (MouseAction(WinX + 166, WinY + 87, 34, 28) && SubTag != 2)
			DrawImage(Images[6], WinX + 166, WinY + 87, 34, 28, Opacity);

		SetFontTextColor(RGB(199, 191, 161));
		if (SubTag == 0)
		{
			for (int i = 0; i < 7; i++)
			{
				int strsize = strlen(InterfaceParty_KTJ.latestb[i]);
				if (strsize)
				{
					if (MouseAction(WinX + 30, WinY + 121 + i * 20, 229, 22) || Check - 1 == i && Check > 0)
						dsDrawColorBox(D3DCOLOR_RGBA(45, 39, 32, Opacity), WinX + 30, WinY + 121 + i * 20, 229, 22);

					DrawImage(Images[31], WinX + 44, WinY + 122 + i * 20, 13, 18, Opacity);
					dsTextLineOut(WinX + 67, WinY + 125 + i * 20, InterfaceParty_KTJ.latestb[i], strsize);
				}
			}
		}
		else if (SubTag == 1)
		{
			for (int i = 0; i < 100; i++)
			{
				if (InterfaceParty_KTJ.fClass[i])
				{
					if (WinY + 121 + i * 22 - Scroll * 5 >= WinY + 115 && WinY + 121 + i * 22 - Scroll * 5 + 22 <= WinY + 458)
						if (MouseAction(WinX + 30, WinY + 121 + i * 22 - Scroll * 5, 229, 22) || Check - 1 == i && Check > 0)
							dsDrawColorBox(D3DCOLOR_RGBA(45, 39, 32, Opacity), WinX + 30, WinY + 121 + i * 22 - Scroll * 5, 229, 22);

					if (WinY + 122 + i * 22 - Scroll * 5 >= WinY + 115 && WinY + 122 + i * 22 - Scroll * 5 + 20 <= WinY + 458)
					{
						if (InterfaceParty_KTJ.fOn[i])
							DrawImage(ImagesJob[InterfaceParty_KTJ.fClass[i] - 1], WinX + 36, WinY + 122 + i * 22 - Scroll * 5, 25, 20, Opacity);
						else
							DrawImage(ImagesJob[InterfaceParty_KTJ.fClass[i] - 1], WinX + 36, WinY + 122 + i * 22 - Scroll * 5, 25, 20, Opacity / 2);
					}

					if (WinY + 123 + i * 22 - Scroll * 5 >= WinY + 115 && WinY + 123 + i * 22 - Scroll * 5 + 18 <= WinY + 458)
					{
						if (InterfaceParty_KTJ.fOn[i])
							DrawImage(Images[18], WinX + 69, WinY + 123 + i * 22 - Scroll * 5, 13, 18, Opacity);
						else
							DrawImage(Images[19], WinX + 69, WinY + 123 + i * 22 - Scroll * 5, 13, 18, Opacity / 2);
					}

					if (FriendList[i].Status)
						SetFontTextColor(RGB(255, 250, 213));
					else
						SetFontTextColor(RGB(145, 133, 111));

					if (WinY + 125 + i * 22 - Scroll * 5 >= WinY + 115 && WinY + 125 + i * 22 - Scroll * 5 + 15 <= WinY + 458)
						dsTextLineOut(WinX + 92, WinY + 125 + i * 22 - Scroll * 5, InterfaceParty_KTJ.fNameb[i], strlen(InterfaceParty_KTJ.fNameb[i]));
				}
			}

			DrawImage(Images[14], WinX + 31, WinY + 464, 18, 18, Opacity);
			char szBuff[256];
			wsprintf(szBuff, "Online %d/%d", 0, GetTotalFriend());
			SetFontTextColor(RGB(142, 129, 103));
			FontType = 0;
			dsTextLineOut(WinX + 55, WinY + 467, szBuff, strlen(szBuff));
			FontType = 1;

			DrawImage(Images[15], WinX + 209, WinY + 461, 50, 24, Opacity);

			if (MouseAction(WinX + 209, WinY + 461, 24, 24))
				DrawImage(Images[16], WinX + 209, WinY + 461, 24, 24, Opacity);
			if (MouseAction(WinX + 235, WinY + 461, 24, 24))
				DrawImage(Images[17], WinX + 235, WinY + 461, 24, 24, Opacity);

			int TotalScroll = GetTotalScroll();

			if (TotalScroll)
			{
				DrawImage(Images[27], WinX + 244, WinY + 128, 10, 316, Opacity);

				float Percent = (float)Scroll;
				Percent = (Percent * 100) / (float)TotalScroll;
				Percent = (318 * Percent) / 100;

				if (MouseAction(WinX + 243, WinY + 445, 12, 10))
				{
					DrawImage(Images[36], WinX + 243, WinY + 445, 12, 10, Opacity);
				}
				else
					DrawImage(Images[35], WinX + 243, WinY + 445, 12, 10, Opacity);

				if (MouseAction(WinX + 243, WinY + 118, 12, 10))
				{
					DrawImage(Images[34], WinX + 243, WinY + 118, 12, 10, Opacity);
				}
				else
					DrawImage(Images[33], WinX + 243, WinY + 118, 12, 10, Opacity);

				DrawImage(Images[28], WinX + 243, WinY + 116 + Percent, 12, 22, Opacity);
			}
		}
		else if (SubTag == 2)
		{
			for (int i = 0; i < cnt2; i++)
			{
				if (WinY + 121 + i * 20 - Scroll * 5 >= WinY + 115 && WinY + 121 + i * 20 - Scroll * 5 + 22 <= WinY + 458)
				{
					if (MouseAction(WinX + 30, WinY + 121 + i * 20 - Scroll * 5, 229, 22) || Check - 1 == i && Check > 0)
						dsDrawColorBox(D3DCOLOR_RGBA(45, 39, 32, Opacity), WinX + 30, WinY + 121 + i * 20 - Scroll * 5, 229, 22);
				}

				if (WinY + 122 + i * 20 - Scroll * 5 >= WinY + 115 && WinY + 122 + i * 20 - Scroll * 5 + 18 <= WinY + 458)
				{
					SetFontTextColor(RGB(186, 184, 182));
					DrawImage(Images[32], WinX + 43, WinY + 122 + i * 20 - Scroll * 5, 18, 18, Opacity);
				}

				if (WinY + 124 + i * 20 - Scroll * 5 >= WinY + 115 && WinY + 124 + i * 20 - Scroll * 5 + 15 <= WinY + 458)
					dsTextLineOut(WinX + 67, WinY + 124 + i * 20 - Scroll * 5, RefuseList[i].name, strlen(RefuseList[i].name));
			}

			DrawImage(Images[15], WinX + 209, WinY + 461, 50, 24, Opacity);

			if (MouseAction(WinX + 209, WinY + 461, 24, 24))
				DrawImage(Images[16], WinX + 209, WinY + 461, 24, 24, Opacity);
			if (MouseAction(WinX + 235, WinY + 461, 24, 24))
				DrawImage(Images[17], WinX + 235, WinY + 461, 24, 24, Opacity);

			int TotalScroll = GetTotalScroll();

			if (TotalScroll)
			{
				DrawImage(Images[27], WinX + 244, WinY + 128, 10, 316, Opacity);

				float Percent = (float)Scroll;
				Percent = (Percent * 100) / (float)TotalScroll;
				Percent = (318 * Percent) / 100;

				if (MouseAction(WinX + 243, WinY + 445, 12, 10))
				{
					DrawImage(Images[36], WinX + 243, WinY + 445, 12, 10, Opacity);
				}
				else
					DrawImage(Images[35], WinX + 243, WinY + 445, 12, 10, Opacity);

				if (MouseAction(WinX + 243, WinY + 118, 12, 10))
				{
					DrawImage(Images[34], WinX + 243, WinY + 118, 12, 10, Opacity);
				}
				else
					DrawImage(Images[33], WinX + 243, WinY + 118, 12, 10, Opacity);

				DrawImage(Images[28], WinX + 243, WinY + 116 + Percent, 12, 22, Opacity);
			}
		}
	}
	else if (Tag == 1)
	{
		//DrawClanMark_EachBox(ClanInfo[chrEachMaster->ClanInfoNum].hClanMark, WinX + 32, WinY + 89);
		//DrawClanImage(WinX + 32, WinY + 89);
		SetFontTextColor(RGB(35, 20, 11));
		FontType = 1;
		//if (chrEachMaster->smCharInfo.ClassClan)
		//{
		//	//SIZE size = {};
		//	//size = {};
		//	//GetTextExtentPoint(0, ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName, lstrlen(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName), &size);

		//	SetTextColor(0, RGB(150, 255, 200));
		//	//dsTextLineOut(WinX + 83, WinY + 98, ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName, lstrlen(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName));
		//}
		//dsTextLineOut(WinX + 83, WinY + 98, ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName, lstrlen(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName));
		FontType = 0;

		//int BC = BlessCrown();
		//int Sod = SodCrown();

		/*if (BC)
			DrawImage(Images[23], WinX + 193, WinY + 95, 32, 32, Opacity);

		if (Sod == 1)
			DrawImage(Images[26], WinX + 227, WinY + 94, 32, 32, Opacity);
		else
			if (Sod == 2)
				DrawImage(Images[25], WinX + 227, WinY + 94, 32, 32, Opacity);
			else
				if (Sod == 3)
					DrawImage(Images[24], WinX + 227, WinY + 94, 32, 32, Opacity);*/

		char szBuff[256];

		for (int i = 0; i < cnt3; i++)
		{
			if (ClanList[i].Type)
				DrawImage(Images[38], WinX + 65, WinY + 161 + i * 23, 24, 23, Opacity);
			else
				DrawImage(Images[39], WinX + 65, WinY + 161 + i * 23, 24, 23, Opacity);

			DrawImage(ImagesJob[ClanList[i].Class - 1], WinX + 36, WinY + 163 + i * 22, 25, 20, Opacity);

			if (lstrcmp(lpCurPlayer->smCharInfo.szName, ClanList[i].name) == 0)
				SetFontTextColor(RGB(255, 250, 213));
			else
				SetFontTextColor(RGB(145, 133, 111));

			dsTextLineOut(WinX + 92, WinY + 165 + i * 22, ClanList[i].name, strlen(ClanList[i].name));
			wsprintf(szBuff, "%d", ClanList[i].Level);
			SetFontTextColor(RGB(145, 133, 111));
			dsTextLineOut(WinX + 215, WinY + 165 + i * 22, szBuff, strlen(szBuff));
		}

		DrawImage(Images[14], WinX + 31, WinY + 464, 18, 18, Opacity);
		wsprintf(szBuff, "Online %d/%d", GetTotalClan(), cnt3);
		SetFontTextColor(RGB(142, 129, 103));
		FontType = 0;
		dsTextLineOut(WinX + 55, WinY + 467, szBuff, strlen(szBuff));
		FontType = 1;

		int TotalScroll = GetTotalScroll();

		if (TotalScroll)
		{
			DrawImage(Images[27], WinX + 244, WinY + 128, 10, 316, Opacity);

			float Percent = (float)Scroll;
			Percent = (Percent * 100) / (float)TotalScroll;
			Percent = (318 * Percent) / 100;

			if (MouseAction(WinX + 243, WinY + 445, 12, 10))
			{
				DrawImage(Images[36], WinX + 243, WinY + 445, 12, 10, Opacity);
			}
			else
				DrawImage(Images[35], WinX + 243, WinY + 445, 12, 10, Opacity);

			if (MouseAction(WinX + 243, WinY + 118, 12, 10))
			{
				DrawImage(Images[34], WinX + 243, WinY + 118, 12, 10, Opacity);
			}
			else
				DrawImage(Images[33], WinX + 243, WinY + 118, 12, 10, Opacity);

			DrawImage(Images[28], WinX + 243, WinY + 116 + Percent, 12, 22, Opacity);
		}
	}

	FontType = 0;
	SetFontOpacity(255);
}

void  Social::ClearFriendList()
{
	ZeroMemory(FriendList, sizeof(PACKET_SOCIAL) * 100);
	cnt1 = 0;
}

void  Social::ClearRefuseList()
{
	ZeroMemory(RefuseList, sizeof(PACKET_SOCIAL) * 100);
	cnt2 = 0;
}

void  Social::ClearClanList()
{
	ZeroMemory(ClanList, sizeof(PACKET_SOCIAL) * 100);
	cnt3 = 0;
}

void  Social::RecvFriendList(PACKET_SOCIAL* packet)
{
	memcpy(&FriendList[cnt1], packet, sizeof(PACKET_SOCIAL));
	cnt1++;
}

void  Social::RecvRefuseList(PACKET_SOCIAL* packet)
{
	memcpy(&RefuseList[cnt2], packet, sizeof(PACKET_SOCIAL));
	cnt2++;
}

void  Social::RecvClanList(PACKET_SOCIAL* packet)
{
	memcpy(&ClanList[cnt3], packet, sizeof(PACKET_SOCIAL));
	cnt3++;
}

void Social::RecvAction(PACKET_SOCIAL* packet)
{
	switch (packet->action)
	{
	case 0:
		ClearFriendList();
		break;
	case 1:
		ClearRefuseList();
		break;
	case 2:
		RecvFriendList(packet);
		break;
	case 3:
		RecvRefuseList(packet);
		break;
	case 4:
		RecvClanList(packet);
		break;
	case 5:
		ClearClanList();
		break;
	}
}

void Social::AddFriend(char* Name, int Class)
{
	PACKET_SOCIAL packet;

	packet.size = sizeof(PACKET_SOCIAL);
	packet.code = PSOCIAL_ACTION;
	packet.action = 2;
	lstrcpy(packet.name, Name);
	packet.Class = Class;

	if (smWsockUserServer)
		smWsockUserServer->Send((char*)&packet, packet.size, TRUE);
}

void Social::DeleteFriend(char* Name)
{
	PACKET_SOCIAL packet;

	packet.size = sizeof(PACKET_SOCIAL);
	packet.code = PSOCIAL_ACTION;
	packet.action = 3;
	lstrcpy(packet.name, Name);

	if (smWsockUserServer)
		smWsockUserServer->Send((char*)&packet, packet.size, TRUE);
}

void Social::AddRefuse(char* Name)
{
	PACKET_SOCIAL packet;

	packet.size = sizeof(PACKET_SOCIAL);
	packet.code = PSOCIAL_ACTION;
	packet.action = 4;
	lstrcpy(packet.name, Name);

	if (smWsockUserServer)
		smWsockUserServer->Send((char*)&packet, packet.size, TRUE);
}

void Social::DeleteRefuse(char* Name)
{
	PACKET_SOCIAL packet;

	packet.size = sizeof(PACKET_SOCIAL);
	packet.code = PSOCIAL_ACTION;
	packet.action = 5;
	lstrcpy(packet.name, Name);

	if (smWsockUserServer)
		smWsockUserServer->Send((char*)&packet, packet.size, TRUE);
}

int Social::StopCharacter()
{
	if (MoveWindow)
		return TRUE;

	if (Show)
	{
		if (MouseAction(MoveX, MoveY, 289, 503))
		{
			return TRUE;
		}
	}

	return FALSE;
}
void Social::ButtonScroll(short Dist)
{
	if (Show)
	{
		if (MouseAction(MoveX, MoveY, 289, 503))
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

void Social::Connect(char* Name)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (lstrcmp(Name, InterfaceParty_KTJ.fNameb[cnt]) == 0)
		{
			InterfaceParty_KTJ.fOn[cnt] = 1;
		}
	}
}

void Social::Disconnect(char* Name)
{
	for (int cnt = 0; cnt < 100; cnt++)
	{
		if (lstrcmp(Name, InterfaceParty_KTJ.fNameb[cnt]) == 0)
		{
			InterfaceParty_KTJ.fOn[cnt] = 0;
		}
	}
}