#include "sinbaram\\sinlinkheader.h"
#include "HoBaram\\HoLinkHeader.h"

void DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}

void DailyQuest::Init()
{
	Mat = CreateTextureMaterial("image\\Sinimage\\skill\\keep\\QuestTimer.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[0] = CreateTextureMaterial("game\\images\\DailyQuest\\background.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[1] = CreateTextureMaterial("game\\images\\DailyQuest\\close.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[2] = CreateTextureMaterial("game\\images\\DailyQuest\\ok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[3] = CreateTextureMaterial("Image\\SinImage\\Help\\Box_Line.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

bool DailyQuest::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void DailyQuest::DrawEngLevel()
{
	char szBuff[256];
	int WinX = 90, WinY = 50;
	FontType = 1;
	wsprintf(szBuff, "Olá %s,", sinChar->szName);
	SetFontTextColor( RGB(255, 255, 255));
	dsTextLineOut(WinX + 110, WinY + 63, szBuff, strlen(szBuff));
	wsprintf(szBuff, "%s\n%s\n%s\n%s\n%s\n%s",
		"eu sinto que você ainda não é um guerreiro",
		"com os atributos necessário para este desa-",
		"fio Continue lutando e evoluindo ao atingir o",
		"nível ( x ), retorne que eu te darei um desafio",
		"que fará com que você se torne um guerreiro",
		"muito mais forte.");
	dsTextLineOut(WinX + 30, WinY + 80, szBuff, strlen(szBuff));
	wsprintf(szBuff, "%s\n%s\n%s",
		"Não se preocupe com esse detalhe, eu já",
		"fui jovem e fraco com certeza também",
		"não estava qualificado para esse desa-\n"
		"fio, continue persistindo guerreiro.");
	dsTextLineOut(WinX + 30, WinY + 190, szBuff, strlen(szBuff));
	SetFontTextColor( RGB(250, 200, 0));
	wsprintf(szBuff, "Nível necessário:80+\n");
	dsTextLineOut(WinX + 85, WinY + 280, szBuff, strlen(szBuff));
	FontType = 0;
}

void DailyQuest::DrawGet()
{

}

void DailyQuest::DrawProgress()
{

}

void DailyQuest::DrawEnd()
{

}

void DailyQuest::DrawWait()
{

}

void DailyQuest::Draw()
{
	if (fOpen)
	{
		int WinX = 90, WinY = 50;

		if (MouseAction(WinX + 72, WinY + 327, 81, 22))
			DrawImage(cImages[2], WinX, WinY, 316, 362);
		else if (MouseAction(WinX + 158, WinY + 327, 81, 22))
			DrawImage(cImages[1], WinX, WinY, 316, 362);
		else
			DrawImage(cImages[0], WinX, WinY, 316, 362);

		DrawImage(cImages[3], WinX + 8, WinY + 35, 300, 16);

		switch (Status)
		{
		case -1:
			DrawEngLevel();
			break;
		case 0:
			DrawGet();
			break;
		case 1:
			DrawProgress();
			break;
		case 2:
			DrawWait();
			break;
		}
	}
}

void DailyQuest::LButton(int x, int y)
{
	if (fOpen)
	{
		int WinX = 90, WinY = 50;

		if (MouseAction(WinX + 72, WinY + 327, 81, 22))
		{
			if (DailyQuest::GetInstance()->GetState() == 0)
			{
				cMessageBox.ShowMessage3(MESSAGE_DAILYQUEST, "deseja começar?");
			}
			else if (DailyQuest::GetInstance()->GetState() == 1 && DailyQuest::GetInstance()->GetNowProgress() == DailyQuest::GetInstance()->GetMaxProgress())
			{
				cMessageBox.ShowMessage3(MESSAGE_DAILYQUEST, "deseja finalizar?");
			}
		}

		if (MouseAction(WinX + 158, WinY + 327, 81, 22))
			Close();
	}
}

void DailyQuest::AddExp(rsPLAYINFO *lpPlayInfo, int Exp)
{
	smTRANS_COMMAND smTransCommand = {};

	smTransCommand.code = smTRANSCODE_QADDEXP;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = Exp;

	smTransCommand.SParam = (smTransCommand.WParam * 3 + smTransCommand.LParam * 13) * 2002;

	lpPlayInfo->spEXP_Out += smTransCommand.WParam;
	smTransCommand.EParam = smTransCommand.SParam^lpPlayInfo->spEXP_Out;

	lpPlayInfo->lpsmSock->Send2((char *)&smTransCommand, smTransCommand.size, TRUE);
}

void DailyQuest::AnalyzeProgress(rsPLAYINFO * Player, DWORD Time)
{
	if (Player->StateQuest == 0)
	{
		Player->StateQuest = 1;

		if (Player->smCharInfo.Level >= 100)
			Player->TypeQuest = 2;
		else if (Player->smCharInfo.Level >= 95)
			Player->TypeQuest = 1;
		else if (Player->smCharInfo.Level >= 80)
			Player->TypeQuest = 0;

		Player->ParamQuest[0] = 0;
		Player->ParamQuest[1] = 100;

		SendUpdateState(Player, 1);
	}
	else if (Player->StateQuest == 1 && Player->ParamQuest[0] == Player->ParamQuest[1]) 
	{
		Player->StateQuest = 2;
		Player->QuestTime = Time + 60 * 60 * 24;
		IniFiles ini(".\\config.ini");
		switch (Player->TypeQuest)
		{
		case 0:
			AddExp(Player, ini.ReadInt("DailyQuest_Exp", "Low"));
			break;
		case 1:
			AddExp(Player, ini.ReadInt("DailyQuest_Exp", "Medium"));
			break;
		case 2:
			AddExp(Player, ini.ReadInt("DailyQuest_Exp", "High"));
			break;
		}
		SendUpdateState(Player, 2);
	}

}

void DailyQuest::SendProgressState(rsPLAYINFO * Player)
{
	smTRANS_COMMAND packet;
	packet.size = sizeof(smTRANS_COMMAND);
	packet.code = smTRANSCODE_OPEN_QUEST_DIARY;

	if (Player->smCharInfo.Level < 80)
		packet.LParam = -1;
	else
		packet.LParam = Player->StateQuest;

	packet.WParam = Player->TypeQuest;
	packet.SParam = Player->ParamQuest[0];
	packet.EParam = Player->ParamQuest[1];

	Player->lpsmSock->Send((char*)&packet, packet.size, true);
}

void DailyQuest::SendUpdateState(rsPLAYINFO * Player, int Param)
{
	smTRANS_COMMAND packet;
	packet.size = sizeof(smTRANS_COMMAND);
	packet.code = smTRANSCODE_UPDATE_QUEST_DIARY;

	packet.LParam = Param;
	packet.WParam = Player->TypeQuest;
	packet.SParam = Player->ParamQuest[0];
	packet.EParam = Player->ParamQuest[1];

	Player->lpsmSock->Send((char*)&packet, packet.size, true);
}

void DailyQuest::RecvProgressState(smTRANS_COMMAND * packet)
{
	State = packet->LParam;
	Type = packet->WParam;
	Param[0] = packet->SParam;
	Param[1] = packet->EParam;

	
	switch (packet->LParam)
	{
	case -1:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_DIARY, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\QuestDiary_1.sin");
		break;
	case 0:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_DIARY, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\QuestDiary_2.sin");
		break;
	case 1:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_DIARY, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\QuestDiary_3.sin");
		break;
	case 2:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST_DIARY, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\QuestDiary_4.sin");
		break;
	}


	
}

void DailyQuest::RecvUpdateState(smTRANS_COMMAND * packet)
{

	switch (packet->LParam)
	{
	case 1:
		sSKILL TempSkill;
		memset(&TempSkill, 0, sizeof(sSKILL));
		TempSkill.CODE = QUEST_DIARY;
		TempSkill.UseTime = 604800;
		TempSkill.Point = 1;
		TempSkill.MatIcon = Mat;
		sinContinueSkillSet(&TempSkill);
		sinPlaySound(SIN_SOUND_EAT_POTION2);
		break;

	case 2:
		cSkill.CancelContinueSkill(QUEST_DIARY);
		break;
	}

	Type = packet->WParam;
	Param[0] = packet->SParam;
	Param[1] = packet->EParam;
}

void DailyQuest::UpdateProgress(rsPLAYINFO * Player)
{
	if (Player->StateQuest == 1)
	{
		if (Player->ParamQuest[0] < Player->ParamQuest[1])
		{
			switch (Player->TypeQuest)
			{
			case 0:
				if (Player->Position.Area == 27 || Player->Position.Area == 28)
					Player->ParamQuest[0]++;
				break;
			case 1:
				if (Player->Position.Area == 37 || Player->Position.Area == 38)
					Player->ParamQuest[0]++;
				break;
			case 2:
				if (Player->Position.Area == 40 || Player->Position.Area == 41)
					Player->ParamQuest[0]++;
				break;
			}
			SendUpdateState(Player, 0);
		}
	}
}
