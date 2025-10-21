#include "sinbaram\sinLinkHeader.h"

void Party::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\party\\bar.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\party\\bar_hp.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\party\\crown_leader.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\party\\delegate_leave.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\party\\header_pr.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[5] = CreateTextureMaterial("game\\images\\party\\header_pr_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[6] = CreateTextureMaterial("game\\images\\party\\menu_header_mb.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[7] = CreateTextureMaterial("game\\images\\party\\menu_header_ld.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[8] = CreateTextureMaterial("game\\images\\party\\expand_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[9] = CreateTextureMaterial("game\\images\\party\\leave_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[10] = CreateTextureMaterial("game\\images\\party\\disband_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	CImages[0] = CreateTextureMaterial("game\\images\\party\\class_fs.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[1] = CreateTextureMaterial("game\\images\\party\\class_ms.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[2] = CreateTextureMaterial("game\\images\\party\\class_as.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[3] = CreateTextureMaterial("game\\images\\party\\class_ps.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[4] = CreateTextureMaterial("game\\images\\party\\class_ata.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[5] = CreateTextureMaterial("game\\images\\party\\class_ks.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[6] = CreateTextureMaterial("game\\images\\party\\class_mg.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[7] = CreateTextureMaterial("game\\images\\party\\class_prs.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[8] = CreateTextureMaterial("game\\images\\party\\class_ass.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[9] = CreateTextureMaterial("game\\images\\party\\class_sh.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CImages[10] = CreateTextureMaterial("game\\images\\party\\class_ma.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	CHImages[0] = CreateTextureMaterial("game\\images\\party\\class_fs_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[1] = CreateTextureMaterial("game\\images\\party\\class_ms_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[2] = CreateTextureMaterial("game\\images\\party\\class_as_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[3] = CreateTextureMaterial("game\\images\\party\\class_ps_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[4] = CreateTextureMaterial("game\\images\\party\\class_ata_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[5] = CreateTextureMaterial("game\\images\\party\\class_ks_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[6] = CreateTextureMaterial("game\\images\\party\\class_mg_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[7] = CreateTextureMaterial("game\\images\\party\\class_prs_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[8] = CreateTextureMaterial("game\\images\\party\\class_ass_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[9] = CreateTextureMaterial("game\\images\\party\\class_sh_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	CHImages[10] = CreateTextureMaterial("game\\images\\party\\class_ma_hover.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	BallImages[0] = CreateTextureMaterial("game\\images\\party\\ball_blue.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	BallImages[1] = CreateTextureMaterial("game\\images\\party\\ball_blue_str.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	BallImages[2] = CreateTextureMaterial("game\\images\\party\\ball_green.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	BallImages[3] = CreateTextureMaterial("game\\images\\party\\ball_purple.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	BallImages[4] = CreateTextureMaterial("game\\images\\party\\ball_red.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	BallImages[5] = CreateTextureMaterial("game\\images\\party\\ball_yellow.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	Show = TRUE;
	MoveX2 = -120;
}

void DrawImage(int Texture, int x, int y, int w, int h, int op)
{
	dsDrawTexImage(Texture, x, y, w - 1, h - 1, op);
}

bool Party::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Party::Main()
{
	if (InterfaceParty.PartyMemberCount)
	{
		if (!Show)
		{
			if (MoveX != -255)
			{
				MoveX -= 15;
			}

			if (Opacity != 0)
			{
				Opacity -= 15;
			}
		}
		else
		{
			if (MoveX != 0)
			{
				MoveX += 15;
			}

			if (Opacity != 255)
			{
				Opacity += 15;
			}

			if (MoveX != 0)
			{
				MoveX += 15;
			}
		}

		if (!Show2)
		{
			if (Opacity2 != 0)
			{
				Opacity2 -= 15;
			}

			if (Opacity2 == 0)
			{
				MoveX2 = -120;
			}
		}
		else
		{
			Opacity2 = 255;

			if (MoveX2 != 0)
			{
				MoveX2 += 10;
			}
		}

		for (int i = 0; i < InterfaceParty.PartyMemberCount; i++)
		{
			if (lpCurPlayer->dwObjectSerial == InterfaceParty.PartyMember[i].ChrCode)
				IsYour = i;

			if (InterfaceParty.PartyMember[i].JangFlag == TRUE)
			{
				if (lpCurPlayer->dwObjectSerial == InterfaceParty.PartyMember[i].ChrCode)
					IsLeader = TRUE;
				else
					IsLeader = FALSE;
			}
		}
	}
}

void Party::Draw()
{
	if (InterfaceParty.PartyMemberCount)
	{
		for (int cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
		{
			if (InterfaceParty.PartyMember[cnt].ChrCode)
			{
				char szBuff[256];
				DrawImage(Images[0], 14 + MoveX, 101 + cnt * 50, 165, 51, Opacity);
				DrawImage(Images[1], 33 + MoveX, 135 + cnt * 50, int((125.f / 100.f) * (float)InterfaceParty.PartyMember[cnt].Life), 6, Opacity);
				DrawImage(BallImages[cnt], 165 + MoveX, 134 + cnt * 50, 7, 7, Opacity);
				SetFontOpacity(Opacity);
				sprintf_s(szBuff, "%d", InterfaceParty.PartyMember[cnt].Level);
				SetFontTextColor(RGB(166, 150, 118));
				dsTextLineOut(40 + MoveX, 116 + cnt * 50, szBuff, strlen(szBuff));
				SetFontTextColor(RGB(255, 250, 213));
				dsTextLineOut(80 + MoveX, 116 + cnt * 50, InterfaceParty.PartyMember[cnt].Name, strlen(InterfaceParty.PartyMember[cnt].Name));
				SetFontOpacity(255);
				if (IsLeader)
				{
					if (MouseAction(1 + MoveX, 113 + cnt * 50, 40, 40) || MouseAction(14, 101 + cnt * 50, 165, 51) || MouseAction(179, 114 + cnt * 50, 26, 46))
					{
						DrawImage(CHImages[InterfaceParty.PartyMember[cnt].JobCode - 1], 1 + MoveX, 113 + cnt * 50, 40, 40, Opacity);

						if (InterfaceParty.PartyMember[cnt].JangFlag == FALSE)
							DrawImage(Images[3], 179 + MoveX, 114 + cnt * 50, 26, 46, Opacity);
					}
					else DrawImage(CImages[InterfaceParty.PartyMember[cnt].JobCode - 1], 1 + MoveX, 113 + cnt * 50, 40, 40, Opacity);
				}
				else
				{
					if (MouseAction(1 + MoveX, 113 + cnt * 50, 40, 40) || MouseAction(14, 101 + cnt * 50, 165, 51))
						DrawImage(CHImages[InterfaceParty.PartyMember[cnt].JobCode - 1], 1 + MoveX, 113 + cnt * 50, 40, 40, Opacity);
					else
						DrawImage(CImages[InterfaceParty.PartyMember[cnt].JobCode - 1], 1 + MoveX, 113 + cnt * 50, 40, 40, Opacity);
				}

				if (InterfaceParty.PartyMember[cnt].JangFlag == TRUE)
					DrawImage(Images[2], -2 + MoveX, 106 + cnt * 50, 25, 20, Opacity);
			}
		}

		if (MouseAction(0, 66, 60, 37) || MouseAction(50, 73, 76, 24))
			Show2 = true;
		else
			Show2 = false;

		if (IsLeader)
		{
			DrawImage(Images[7], 50 + MoveX2, 72, 76, 24, Opacity2);

			if (MouseAction(50 + MoveX2, 71, 25, 26))
				DrawImage(Images[8], 50 + MoveX2, 71, 25, 26, Opacity2);
			if (MouseAction(76 + MoveX2, 71, 25, 26))
				DrawImage(Images[9], 76 + MoveX2, 71, 25, 26, Opacity2);
			if (MouseAction(102 + MoveX2, 71, 25, 26))
				DrawImage(Images[10], 102 + MoveX2, 71, 25, 26, Opacity2);
		}
		else
		{
			DrawImage(Images[6], 50 + MoveX2, 72, 76, 24, Opacity2);

			if (MouseAction(50 + MoveX2, 71, 25, 26))
				DrawImage(Images[8], 50 + MoveX2, 71, 25, 26, Opacity2);
			if (MouseAction(76, 71 + MoveX2, 25, 26))
				DrawImage(Images[9], 76 + MoveX2, 71, 25, 26, Opacity2);
		}

		if (MouseAction(0, 66, 60, 37))
			DrawImage(Images[5], 0, 66, 60, 37, 255);
		else
			DrawImage(Images[4], 0, 66, 60, 37, 255);
	}
}

int	PartyButton(int Num, int Button)
{
	DWORD	dwCode;
	smTRANS_COMMAND	smTransCommand;

	if (!InterfaceParty.PartyMemberCount) return FALSE;

	dwCode = 0;

	if (Num >= 0)
		dwCode = InterfaceParty.PartyMember[Num].ChrCode;
	else
		dwCode = 0;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_PARTY_COMMAND;
	smTransCommand.WParam = dwCode;
	smTransCommand.LParam = Button;
	smTransCommand.SParam = 0;

	if (Button < 3 && InterfaceParty.PartyMember[0].ChrCode != lpCurPlayer->dwObjectSerial) {
		return FALSE;
	}

	return smWsockUserServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int Party::StopCharacter()
{
	if (InterfaceParty.PartyMemberCount)
	{
		for (int cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
		{
			if (InterfaceParty.PartyMember[cnt].ChrCode)
			{
				if (IsLeader)
				{
					if (MouseAction(1 + MoveX, 113 + cnt * 50, 40, 40) || MouseAction(14 + MoveX, 101 + cnt * 50, 165, 51) || MouseAction(179 + MoveX, 114 + cnt * 50, 26, 46))
					{
						if (InterfaceParty.PartyMember[cnt].JangFlag == FALSE)
						{
							if (MouseAction(179 + MoveX, 113 + cnt * 50, 26, 26))
								return TRUE;
							if (MouseAction(180 + MoveX, 134 + cnt * 50, 26, 26))
								return TRUE;
						}
					}
				}
			}
		}

		if (IsLeader)
		{
			if (MouseAction(50 + MoveX2, 71, 25, 26))
				return TRUE;

			if (MouseAction(76 + MoveX2, 71, 25, 26))
				return TRUE;
			if (MouseAction(102 + MoveX2, 71, 25, 26))
				return TRUE;
		}
		else
		{
			if (MouseAction(50 + MoveX2, 71, 25, 26))
				return TRUE;

			if (MouseAction(76 + MoveX2, 71, 25, 26))
				return TRUE;
		}
	}

	return FALSE;
}

void Party::Button()
{
	if (!chaPremiumitem.CheckWindowOpen()) return;

	if (InterfaceParty.PartyMemberCount)
	{
		for (int cnt = 0; cnt < InterfaceParty.PartyMemberCount; cnt++)
		{
			if (InterfaceParty.PartyMember[cnt].ChrCode)
			{
				if (IsLeader)
				{
					if (MouseAction(1 + MoveX, 113 + cnt * 50, 40, 40) || MouseAction(14 + MoveX, 101 + cnt * 50, 165, 51) || MouseAction(179 + MoveX, 114 + cnt * 50, 26, 46))
					{
						if (InterfaceParty.PartyMember[cnt].JangFlag == FALSE)
						{
							if (MouseAction(179 + MoveX, 113 + cnt * 50, 26, 26))
								PartyButton(cnt, 0);
							if (MouseAction(180 + MoveX, 134 + cnt * 50, 26, 26))
								PartyButton(cnt, 2);
						}
					}
				}
			}
		}

		if (IsLeader)
		{
			if (MouseAction(50 + MoveX2, 71, 25, 26))
			{
				if (!Show)
					Show = true;
				else
					Show = false;
			}

			if (MouseAction(76 + MoveX2, 71, 25, 26))
				PartyButton(IsYour, 3);
			if (MouseAction(102 + MoveX2, 71, 25, 26))
				PartyButton(IsYour, 1);
		}
		else
		{
			if (MouseAction(50 + MoveX2, 71, 25, 26))
			{
				if (!Show)
					Show = true;
				else
					Show = false;
			}

			if (MouseAction(76 + MoveX2, 71, 25, 26))
				PartyButton(IsYour, 3);
		}
	}
}