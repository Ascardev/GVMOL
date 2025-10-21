#include "sinbaram/sinLinkHeader.h"
#include "TJBOY/clanmenu/cE_CViewClanInfo.h"
#include "cTarget.h"
#include "field.h"

extern bool isMousePos(int x, int y, int w, int h);
extern int DrawClanMark_EachBox(LPDIRECT3DTEXTURE9 clanMark, int x, int y);

cTARGET cTarget;

extern POINT3D EachCameraPos;

void cTARGET::DrawTarget()
{
	int mx = MidX;
	int my = MidY;

	MidX = ((WinSizeX - 301) / 2) + 36;
	MidY = 42 + BaseY;

	int sizeBackup = WinSizeX;
	int sizeBackupy = WinSizeY;

	WinSizeX = 800;
	WinSizeY = 600;

	SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 5;

	smRender.SMMULT_PERSPECTIVE_HEIGHT = (int)(RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT + 25.6f) * 11;

	int dist = 300 * fONE;

	d3ddev->Clear(0, 0, 2, smBackColor, 1.0f, 0);

	smCHAR_SetCameraPosi(EachCameraPos.x, EachCameraPos.y + 50, dist + EachCameraPos.z, 0, ANGLE_180, 0);

	chrEachPlayer.AttackAnger = chrEachMaster->AttackAnger;

	WORD ObjSizeBack = chrEachPlayer.smCharInfo.wPlayClass[1];
	chrEachPlayer.smCharInfo.wPlayClass[1] = 0;

	chrEachPlayer.Draw();

	chrEachPlayer.smCharInfo.wPlayClass[1] = ObjSizeBack;

	MidX = mx;
	MidY = my;

	smRender.SMSHIFT_PERSPECTIVE_WIDTH = 0;
	smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;

	WinSizeX = sizeBackup;
	WinSizeY = sizeBackupy;
	SetDxProjection((g_PI / 4.4f), WinSizeX, WinSizeY, 20.f, 4000.f);
}

void cTARGET::Init()
{
	Mat[BACKGROUND] = CreateTextureMaterial("game\\images\\Target\\targetoverlay.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETBG] = CreateTextureMaterial("game\\images\\Target\\targetbackground.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETCLAN] = CreateTextureMaterial("game\\images\\Target\\targetoverlay_Clan.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TARGETHP] = CreateTextureMaterial("game\\images\\Target\\targethp.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEDEMON] = CreateTextureMaterial("game\\images\\Target\\type\\demon.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEMECHANIC] = CreateTextureMaterial("game\\images\\Target\\type\\mechanic.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEMUTANT] = CreateTextureMaterial("game\\images\\Target\\type\\mutant.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPENORMAL] = CreateTextureMaterial("game\\images\\Target\\type\\normal.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPENPC] = CreateTextureMaterial("game\\images\\Target\\type\\npc.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEPLAYER] = CreateTextureMaterial("game\\images\\Target\\type\\player.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[TYPEUNDEAD] = CreateTextureMaterial("game\\images\\Target\\type\\undead.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MORE] = CreateTextureMaterial("game\\images\\Target\\more.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[MORE_] = CreateTextureMaterial("game\\images\\Target\\more_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[DROPTOP] = CreateTextureMaterial("game\\images\\Target\\menu\\topleft.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[DROPMID] = CreateTextureMaterial("game\\images\\Target\\menu\\middle.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[DROPBOT] = CreateTextureMaterial("game\\images\\Target\\menu\\bottom.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	/*Mat[RANKNOOB] = CreateTextureMaterial("game\\patente\\noob.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKPRATA] = CreateTextureMaterial("game\\patente\\prata.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKOURO] = CreateTextureMaterial("game\\patente\\ouro.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKMASTER] = CreateTextureMaterial("game\\patente\\master.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKGMASTER] = CreateTextureMaterial("game\\patente\\grandmaster.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RANKRMASTER] = CreateTextureMaterial("game\\patente\\royalmaster.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[OVERLAY] = CreateTextureMaterial("game\\patente\\targetoverlay_patente.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);*/
}

void cTARGET::Draw(smCHAR* lpEachPlayer)
{
	if (StageField[lpCurPlayer->OnStageField]->FieldCode != 43)
	{
		if (!cInterFace.sInterFlags.MapOnFlag)
			return;

		unsigned int stage = lpCurPlayer->OnStageField >= 0 && lpCurPlayer->OnStageField < 2 ? StageField[lpCurPlayer->OnStageField]->FieldCode : 0;
		BaseX = (WinSizeX - 301) / 2;

		if (stage == 16 || stage == 30)
			BaseY = 105;
		else
			BaseY = 3;

		if (TargetSerial != lpEachPlayer->dwObjectSerial)
		{
			if (DropDownFlag)
				OpenDropDown();

			TargetSerial = lpEachPlayer->dwObjectSerial;
		}

		dsDrawTexImage(Mat[TARGETBG], BaseX + 7, BaseY + 11, 59, 59, 255);

		DrawTarget();

		dsDrawTexImage(Mat[BACKGROUND], BaseX, BaseY, 302, 81, 255);

		float hppercent = (float)(209 * ((float)lpEachPlayer->smCharInfo.Life[0] / (float)lpEachPlayer->smCharInfo.Life[1]));
		dsDrawTexImage(Mat[TARGETHP], BaseX + 82, BaseY + 39, (int)hppercent, 12, 255);

		int type = TYPENPC;

		switch (chrEachPlayer.smCharInfo.Brood)
		{
		case smCHAR_MONSTER_MUTANT:
			type = TYPEMUTANT;
			break;

		case smCHAR_MONSTER_UNDEAD:
			type = TYPEUNDEAD;
			break;

		case smCHAR_MONSTER_DEMON:
			type = TYPEDEMON;
			break;

		case smCHAR_MONSTER_MECHANIC:
			type = TYPEMECHANIC;
			break;

		case smCHAR_MONSTER_NORMAL:
			type = TYPENORMAL;
			break;

		case smCHAR_MONSTER_USER:
			type = TYPEPLAYER;
			break;
		}

		if (chrEachPlayer.smCharInfo.State == smCHAR_STATE_NPC)
			type = TYPENPC;
		else if (chrEachPlayer.smCharInfo.State == smCHAR_STATE_USER || chrEachPlayer.PkMode_CharState == smCHAR_STATE_USER)
			type = TYPEPLAYER;

		dsDrawTexImage(Mat[type], BaseX + 63, BaseY + 34, 16, 16, 255);

		if (type == TYPEPLAYER)
		{
			if (EachTradeButton)
			{
				dsDrawTexImage(Mat[MORE], BaseX + 262, BaseY + 15, 26, 26, 255);
				if (isMousePos(BaseX + 262, BaseY + 15, 26, 26) || DropDownFlag)
					dsDrawTexImage(Mat[MORE_], BaseX + 262, BaseY + 15, 26, 26, 255);
			}

			/*dsDrawTexImage(Mat[OVERLAY], BaseX + 81, BaseY + 51, 207, 22, 255);

			if (chrEachPlayer.sBlessCastle_Damage[1] < 100)
			{
				dsDrawTexImage(Mat[RANKNOOB], BaseX + 150, BaseY + 52, 28, 21, 255);
				dsTextLineOut(BaseX + 180, BaseY + 55, "Iniciante", lstrlen("Iniciante"));
			}
			else if (chrEachPlayer.sBlessCastle_Damage[1] >= 100 && chrEachPlayer.sBlessCastle_Damage[1] < 300)
			{
				dsDrawTexImage(Mat[RANKPRATA], BaseX + 150, BaseY + 52, 28, 21, 255);
				dsTextLineOut(BaseX + 180, BaseY + 55, "Matador", lstrlen("Matador"));
			}
			else if (chrEachPlayer.sBlessCastle_Damage[1] >= 300 && chrEachPlayer.sBlessCastle_Damage[1] < 400)
			{
				dsDrawTexImage(Mat[RANKOURO], BaseX + 150, BaseY + 52, 28, 21, 255);
				dsTextLineOut(BaseX + 180, BaseY + 55, "Assassino", lstrlen("Assassino"));
			}
			else if (chrEachPlayer.sBlessCastle_Damage[1] >= 400 && chrEachPlayer.sBlessCastle_Damage[1] < 500)
			{
				dsDrawTexImage(Mat[RANKMASTER], BaseX + 150, BaseY + 52, 28, 21, 255);
				dsTextLineOut(BaseX + 180, BaseY + 55, "Mestre", lstrlen("Mestre"));
			}
			else if (chrEachPlayer.sBlessCastle_Damage[1] >= 500 && chrEachPlayer.sBlessCastle_Damage[1] < 600)
			{
				dsDrawTexImage(Mat[RANKGMASTER], BaseX + 130, BaseY + 52, 28, 21, 255);
				dsTextLineOut(BaseX + 160, BaseY + 55, "Grande Mestre", lstrlen("Grande Mestre"));
			}
			else if (chrEachPlayer.sBlessCastle_Damage[1] >= 600)
			{
				dsDrawTexImage(Mat[RANKRMASTER], BaseX + 130, BaseY + 52, 28, 21, 255);
				dsTextLineOut(BaseX + 160, BaseY + 55, "Mestre Real", lstrlen("Mestre Real"));
			}*/
		}

		if (DropDownFlag)
		{
			int count = 0;
			for (auto opt : vOptions)
			{
				if (opt.second)
				{
					if (!count)
					{
						dsDrawTexImage(Mat[DROPTOP], BaseX + 301, BaseY + 16, 95, 25, 255);
					}
					else if (count > 0 && count < vOptions.size() - 1)
					{
						dsDrawTexImage(Mat[DROPMID], BaseX + 301, BaseY + 16 + (25 * count), 95, 25, 255);
					}
					else if (count == vOptions.size() - 1)
					{
						dsDrawTexImage(Mat[DROPBOT], BaseX + 301, BaseY + 16 + (25 * count), 95, 26, 255);
					}

					count++;
				}
			}
		}

		if (chrEachPlayer.smCharInfo.ClassClan && chrEachPlayer.ClanInfoNum >= 0)
		{
			dsDrawTexImage(Mat[TARGETCLAN], BaseX + 81, BaseY - 3, 206, 22, 255);
			DrawClanMark_EachBox(ClanInfo[chrEachMaster->ClanInfoNum].hClanMark, BaseX + 99, BaseY + 2);
		}

		Text(lpEachPlayer);
	}
}

void cTARGET::Text(smCHAR* lpEachPlayer)
{
	SIZE size = {};
	char buff[255];
	wsprintf(buff, "%s - Nv.%d", lpEachPlayer->smCharInfo.szName, lpEachPlayer->smCharInfo.Level);
	GetFontTextExtentPoint(buff, lstrlen(buff), &size);

	SetFontTextColor(RGB(255, 255, 255));
	dsTextLineOut(BaseX + (185 - (size.cx / 2)), BaseY + 21, buff, lstrlen(buff));

	ZeroMemory(buff, 255);

	size = {};
	wsprintf(buff, "%d/%d", lpEachPlayer->smCharInfo.Life[0], lpEachPlayer->smCharInfo.Life[1]);
	GetFontTextExtentPoint(buff, lstrlen(buff), &size);
	dsTextLineOut(BaseX + (185 - (size.cx / 2)), BaseY + 38, buff, lstrlen(buff));

	if (DropDownFlag)
	{
		int count = 0;
		for (auto opt : vOptions)
		{
			if (opt.second)
			{
				size = {};
				GetFontTextExtentPoint(opt.second, lstrlen(opt.second), &size);

				if (isMousePos(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), size.cx, size.cy))
					SetFontTextColor(RGB(230, 180, 150));
				else
					SetFontTextColor(RGB(255, 255, 255));

				dsTextLineOut(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), opt.second, lstrlen(opt.second));
				count++;
			}
		}
	}

	if (chrEachPlayer.smCharInfo.ClassClan && chrEachPlayer.ClanInfoNum >= 0)
	{
		size = {};
		GetFontTextExtentPoint(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName, lstrlen(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName), &size);

		SetFontTextColor(RGB(150, 255, 200));
		dsTextLineOut(BaseX + 184 - (size.cx / 2), BaseY + 2, ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName, lstrlen(ClanInfo[chrEachMaster->ClanInfoNum].ClanInfoHeader.ClanName));
	}
}

bool cTARGET::LButtonDown()
{
	if (!cInterFace.sInterFlags.MapOnFlag)
		return false;

	bool result = false;

	if (MouseIn())
		result = true;
	else if (DropDownFlag)
	{
		OpenDropDown();
	}

	if (isMousePos(BaseX + 262, BaseY + 15, 26, 26))
	{
		OpenDropDown();
	}

	if (DropDownFlag)
	{
		int count = 0;
		for (auto opt : vOptions)
		{
			if (opt.second)
			{
				SIZE size = {};
				GetFontTextExtentPoint(opt.second, lstrlen(opt.second), &size);

				if (isMousePos(BaseX + 309 + ((87 - size.cx) / 2), BaseY + 16 + (count * 25) + ((25 - size.cy) / 2), size.cx, size.cy))
				{
					handleOption(opt.first);
					break;
				}
				count++;
			}
		}
	}

	return false;
}

bool cTARGET::MouseIn()
{
	return isMousePos(BaseX, BaseY, 301 + 95, 111);
}

bool cTARGET::StopMotion()
{
	if (isMousePos(BaseX + 262, BaseY + 15, 26, 26) || DropDownFlag)
		return true;

	return false;
}

void cTARGET::OpenDropDown()//
{
	if (DropDownFlag)
	{
		vOptions.clear();
		DropDownFlag = 0;
	}
	else
	{
		if (EachTradeButton)
		{
			vOptions.insert(std::pair<int, char*>(1, "Troca"));
			vOptions.insert(std::pair<int, char*>(2, "Grupo"));
			vOptions.insert(std::pair<int, char*>(3, "Adicionar"));
			if (EachTradeButtonMode)
				vOptions.insert(std::pair<int, char*>(4, "Clan"));

			DropDownFlag = 1;
		}
	}
}

extern void g_IsCheckClanMember(smCHAR* pChar);
extern char* mgRequestTrade;
extern char* mgRequestTrade2;

void cTARGET::handleOption(int code)
{
	char szBuff[500];

	switch (code)
	{
	case 1:
		if (GetTradeDistanceFromCode(chrEachMaster->dwObjectSerial) == TRUE)
		{
			SendRequestTrade(chrEachMaster->dwObjectSerial, 0);
			wsprintf(szBuff, mgRequestTrade, chrEachMaster->smCharInfo.szName);
		}
		else
		{
			wsprintf(szBuff, mgRequestTrade2, chrEachMaster->smCharInfo.szName);
		}

		AddChatBuff(szBuff);
		break;

	case 2:
		wsprintf(szBuff, "//party %s", chrEachMaster->smCharInfo.szName);
		SendChatMessageToServer(szBuff);
		break;

	case 3:
		InterfaceParty.latest_Insert(chrEachMaster->smCharInfo.szName);
		InterfaceParty.friend_Insert(chrEachMaster->smCharInfo.szName, 0);

		InterfaceParty.Main_menuSet(2);
		InterfaceParty.chat_changeMENU(1);
		if (InterfaceParty.PartyPosState == PARTY_NONE)	ShowParty();
		break;

	case 4:
		g_IsCheckClanMember(chrEachMaster);
		break;
	}

	OpenDropDown();
}