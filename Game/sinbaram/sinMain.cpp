#define _SINBARAM_TEST

#include "sinLinkHeader.h"
#include "..\CTeleportWindow.h"
#include "..\\Alerta.h"
#include "..\\cRestaureWindow.h"
#include "..\\cMixGuide.h"
#include "..\\cTarget.h"

#include "../RollDice.h"
#include "../CKillHandler.h"
#include "../field.h"

smCHAR_INFO* sinChar;
smCHAR_INFO sinCharDisplay;
int sinbaram_Stop = 0;

void sinInit()
{
	InitCursor();
	cItem.Init();
	cSkill.Init();
	cInvenTory.Init();
	cCharStatus.Init();
	cInterFace.Init();
	cShop.Init();
	cTrade.Init();
	cMessageBox.Init();
	cSin3D.Init();
	cSinHelp.Init();
	cSinWarpGate.Init();
	g_CreatePetSystem();
	cHelpPet.Init();
	cSinSod2.Init();
	cKill.Init();
	cTarget.Init();
	g_PCBang_CreatePetSystem();
	cPCBANGPet.Init();

	chaSiege.init();
	chaQuest.init();
	chaPremiumitem.init();

	void web_DB_start();

	void clanMENU_INIT(int setN);
	clanMENU_INIT(1);

	CoinShop::GetInstance()->Init();
	TimeShop::GetInstance()->Init();
	Settings::GetInstance()->Init();
	Quest::GetInstance()->Init();
	//SkinView::GetInstance()->Init();
	//Challenge::GetInstance()->Init();
	Party::GetInstance()->Init();
	PlayerMigration::GetInstance()->Init();
	BattleArena::GetInstance()->Init();
	BattleEvent::GetInstance()->Init();
	HellGates::GetInstance()->Init();
	Roulette::GetInstance()->Init();
	AwardItem::GetInstance()->Init();
	//LockItem::GetInstance()->Init();
	//Loading::GetInstance()->Init();
	Social::GetInstance()->Init();
	Puzzle::GetInstance()->Init();
	Natal::GetInstance()->Init();
	WorldCup::GetInstance()->Init();
	UpdateItem::GetInstance()->Init();
	TCORE::GetInstance()->init();
	cAlerta::GetInstance()->Init();
	cMixGuide::GetInstance()->Init();
	cRestaure.Load();

	Game::RollDice::GetInstance().Initialize();
}

DWORD dwSinTime = 0;
void sinMain()
{
	sinMouseMain();
	sinKeyClickMain();

	if (sinGetMouseButton(0) == TRUE)
		sinProc(SINLBUTTONDOWN);
	if (sinGetMouseButton(1) == TRUE)
		sinProc(SINRBUTTONDOWN);

	if (MouseButtonUpEvent == SINLBUTTONUP) {
		sinProc(SINLBUTTONUP);
		MouseButtonUpEvent = 0;
	}

	if (MouseButtonUpEvent == SINRBUTTONUP) {
		sinProc(SINRBUTTONUP);
		MouseButtonUpEvent = 0;
	}

	sinProc(SINMOUSEMOVE);

	MainSub();
	cItem.Main();
	cInterFace.Main();

	Game::RollDice::GetInstance().Update();

	cSkill.Main();
	cInvenTory.Main();
	cCharStatus.Main();
	cShop.Main();
	cTrade.Main();
	cMessageBox.Main();

	cSinHelp.Main();
	cSinWarpGate.Main();
	cHelpPet.Main();
	cSinSod2.Main();

	chaSiege.Main();
	chaQuest.Main();
	chaPremiumitem.Main();

	void ktj_imsi_clanMENU_Main();
	ktj_imsi_clanMENU_Main();

	ShowInterFace();

	cPCBANGPet.Main();

	Party::GetInstance()->Main();
	Quest::GetInstance()->Main();
	DrawDamage::GetInstance()->UpdateTime();
	DrawDamage::GetInstance()->CurUpdateTime();
	//Challenge::GetInstance()->Main();
	//SkinView::GetInstance()->Main();
	Social::GetInstance()->Main();
	Roulette::GetInstance()->Main();
	HellGates::GetInstance()->Main();

	//Loading::GetInstance()->Main();

	if (sinbaram_Stop) {
		dwSinTime++;
		if (dwSinTime >= 3 * 70) sinbaram_Stop = 0;
	}
	else dwSinTime = 0;
}

extern bool ShowAlert;
void sinDraw()
{
	Party::GetInstance()->Draw();
	Quest::GetInstance()->Draw();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	cCharStatus.Draw();

	cCharStatus.DrawCharText();

	dsDrawOffsetArray = dsARRAY_TOP;

	chaPremiumitem.DrawUp();

	if (ShowAlert)
	{
		cAlerta::GetInstance()->Draw();
	}

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	cSkill.Draw();

	dsDrawOffsetArray = dsARRAY_TOP;

	cSkill.DrawUp();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	cInvenTory.Draw();

	cInvenTory.DrawInvenText();

	dsDrawOffsetArray = dsARRAY_TOP;

	cShop.Draw();

	cShop.DrawShopText();

	cTrade.Draw();

	cTrade.DrawTradeText();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	cInterFace.Draw();

	cInterFace.DrawInterText();

	CoinShop::GetInstance()->Draw();
	PlayerMigration::GetInstance()->Draw();
	BattleArena::GetInstance()->Draw();
	BattleEvent::GetInstance()->Draw();
	HellGates::GetInstance()->Draw();
	Roulette::GetInstance()->Draw();
	AwardItem::GetInstance()->Draw();
	LockItem::GetInstance()->Draw();
	Puzzle::GetInstance()->Draw();
	Natal::GetInstance()->Draw();
	WorldCup::GetInstance()->Draw();
	UpdateItem::GetInstance()->Draw();

	Game::RollDice::GetInstance().Render();

	cItem.Draw();

	cItem.DrawItemText();

	dsDrawOffsetArray = dsARRAY_TOP;

	cSinHelp.Draw();

	cSinHelp.DrawText();

	cSinWarpGate.Draw();

	cSinWarpGate.DrawText();

	sinDrawInterEffect();

	dsDrawOffsetArray = dsARRAY_TOP;
	void ktj_imsi_clanMENU_Draw();
	ktj_imsi_clanMENU_Draw();

	dsDrawOffsetArray = dsARRAY_BOTTOM;

	sinDrawText();

	dsDrawOffsetArray = dsARRAY_TOP;

	cHelpPet.Draw();

	cHelpPet.DrawText();

	cSinSod2.Draw();

	cSinSod2.DrawText();

	chaSiege.Draw();

	chaSiege.DrawText();

	chaQuest.Draw();

	cKill.Draw();

	chaPremiumitem.Draw();

	chaPremiumitem.DrawText();

	TimeShop::GetInstance()->Draw();
	Settings::GetInstance()->Draw();
	SkinView::GetInstance()->Draw();
	Quest::GetInstance()->DrawNPC();
	//Loading::GetInstance()->Draw();
	//Challenge::GetInstance()->Draw();
	Social::GetInstance()->Draw();
	TCORE::GetInstance()->Draw();
	cMessageBox.Draw();
	cRestaure.Draw();
	cMixGuide::GetInstance()->Draw();

	cMessageBox.DrawMessageText();

	dsDrawOffsetArray = dsARRAY_TOP;
}

void sinDrawText()
{
	cSkill.DrawSkillText();
	sinTestDrawText();
	EffectTestDrawText();
}

int MsgError;
DWORD dwTime;

void sinProc(int Message)
{
	switch (Message)
	{
	case SINLBUTTONDOWN:
		if (sinbaram_Stop)return;

		if (Game::RollDice::GetInstance().LButtonDown()) break;

		cInvenTory.CheckMousePotionNumForm();
		cMessageBox.LButtonDown(pCursorPos.x, pCursorPos.y);
		cSinSod2.LButtonDown(pCursorPos.x, pCursorPos.y);
		if (sinMessageBoxShowFlag && !MyShopExpBox && !nName)return;
		cInterFace.LButtonDown(pCursorPos.x, pCursorPos.y);
		cCharStatus.LButtonDown(pCursorPos.x, pCursorPos.y);
		cInvenTory.LButtonDown(pCursorPos.x, pCursorPos.y);
		cSkill.LButtonDown(pCursorPos.x, pCursorPos.y);
		cTrade.LButtonDown(pCursorPos.x, pCursorPos.y);
		cItem.LButtonDown(pCursorPos.x, pCursorPos.y);
		cShop.LButtonDown(pCursorPos.x, pCursorPos.y);
		cSin3D.LButtonDown(pCursorPos.x, pCursorPos.y);
		cSinHelp.LButtonDown(pCursorPos.x, pCursorPos.y);
		cSinWarpGate.LButtonDown(pCursorPos.x, pCursorPos.y);
		cHelpPet.LButtonDown(pCursorPos.x, pCursorPos.y);
		cInvenTory.ReFormMousePotionNum();
		cTarget.LButtonDown();

		chaSiege.LButtonDown(pCursorPos.x, pCursorPos.y);
		chaQuest.LButtonDown(pCursorPos.x, pCursorPos.y);
		chaPremiumitem.LButtonDown(pCursorPos.x, pCursorPos.y);
		CoinShop::GetInstance()->LButton(pCursorPos.x, pCursorPos.y);
		TimeShop::GetInstance()->LButton(pCursorPos.x, pCursorPos.y);
		Settings::GetInstance()->Button();
		Quest::GetInstance()->Button();
		Quest::GetInstance()->ButtonNPC();
		//Challenge::GetInstance()->Button();
		Party::GetInstance()->Button();
		PlayerMigration::GetInstance()->Button();
		BattleArena::GetInstance()->Button();
		HellGates::GetInstance()->Button();
		Social::GetInstance()->Button();
		Roulette::GetInstance()->Button();
		LockItem::GetInstance()->Button();
		Puzzle::GetInstance()->Button();
		Natal::GetInstance()->Button();
		WorldCup::GetInstance()->Button();
		AwardItem::GetInstance()->Button();
		UpdateItem::GetInstance()->Button();
		TCORE::GetInstance()->MouseIn();
		cMixGuide::GetInstance()->Button();
		if (cRestaure.LButtonDown())
			break;
		break;
	case SINLBUTTONUP:
		if (sinbaram_Stop)return;
		cMessageBox.LButtonUp(pCursorPos.x, pCursorPos.y);
		if (sinMessageBoxShowFlag)return;
		cInterFace.LButtonUp(pCursorPos.x, pCursorPos.y);
		cCharStatus.LButtonUp(pCursorPos.x, pCursorPos.y);
		cInvenTory.LButtonUp(pCursorPos.x, pCursorPos.y);
		cShop.LButtonUp(pCursorPos.x, pCursorPos.y);
		cSkill.LButtonUp(pCursorPos.x, pCursorPos.y);
		cTrade.LButtonUp(pCursorPos.x, pCursorPos.y);
		cSin3D.LButtonUp(pCursorPos.x, pCursorPos.y);
		cSinHelp.LButtonUp(pCursorPos.x, pCursorPos.y);
		cSinWarpGate.LButtonUp(pCursorPos.x, pCursorPos.y);
		cHelpPet.LButtonUp(pCursorPos.x, pCursorPos.y);
		cSinSod2.LButtonUp(pCursorPos.x, pCursorPos.y);

		chaSiege.LButtonUp(pCursorPos.x, pCursorPos.y);
		Social::GetInstance()->ButtonUp();

		break;

	case SINRBUTTONDOWN:
		if (MyShopSendButton)return;
		if (sinbaram_Stop)return;
		cMessageBox.RButtonDown(pCursorPos.x, pCursorPos.y);
		if (sinMessageBoxShowFlag)return;
		cInterFace.RButtonDown(pCursorPos.x, pCursorPos.y);
		cCharStatus.RButtonDown(pCursorPos.x, pCursorPos.y);
		cShop.RButtonDown(pCursorPos.x, pCursorPos.y);
		cInvenTory.RButtonDown(pCursorPos.x, pCursorPos.y);
		cSkill.RButtonDown(pCursorPos.x, pCursorPos.y);
		cTrade.RButtonDown(pCursorPos.x, pCursorPos.y);
		cItem.RButtonDown(pCursorPos.x, pCursorPos.y);
		cSin3D.RButtonDown(pCursorPos.x, pCursorPos.y);
		cSinHelp.RButtonDown(pCursorPos.x, pCursorPos.y);
		cSinWarpGate.RButtonDown(pCursorPos.x, pCursorPos.y);
		cHelpPet.RButtonDown(pCursorPos.x, pCursorPos.y);
		cSinSod2.RButtonDown(pCursorPos.x, pCursorPos.y);
		chaPremiumitem.RButtonDown(pCursorPos.x, pCursorPos.y);
		CoinShop::GetInstance()->RButton(pCursorPos.x, pCursorPos.y);
		Quest::GetInstance()->RButton();
		break;

	case SINRBUTTONUP:
		if (sinbaram_Stop)return;
		cMessageBox.RButtonUp(pCursorPos.x, pCursorPos.y);
		if (sinMessageBoxShowFlag)return;
		cInterFace.RButtonUp(pCursorPos.x, pCursorPos.y);
		cCharStatus.RButtonUp(pCursorPos.x, pCursorPos.y);
		cInvenTory.RButtonUp(pCursorPos.x, pCursorPos.y);
		cShop.RButtonUp(pCursorPos.x, pCursorPos.y);
		cSkill.RButtonUp(pCursorPos.x, pCursorPos.y);
		cTrade.RButtonUp(pCursorPos.x, pCursorPos.y);
		cMessageBox.RButtonUp(pCursorPos.x, pCursorPos.y);
		cSin3D.RButtonUp(pCursorPos.x, pCursorPos.y);
		cSinHelp.RButtonUp(pCursorPos.x, pCursorPos.y);
		cSinWarpGate.RButtonUp(pCursorPos.x, pCursorPos.y);
		cHelpPet.RButtonUp(pCursorPos.x, pCursorPos.y);
		cSinSod2.RButtonUp(pCursorPos.x, pCursorPos.y);
		break;

	case SINMOUSEMOVE:

		break;

	case SINKEYDOWN:
		if (sinbaram_Stop)return;
		cMessageBox.KeyDown();
		if (sinMessageBoxShowFlag)return;

		cInterFace.KeyDown();
		cCharStatus.KeyDown();
		cInvenTory.KeyDown();
		cShop.KeyDown();
		cSkill.KeyDown();
		cTrade.KeyDown();
		cSin3D.KeyDown();
		cSinHelp.KeyDown();
		cSinWarpGate.KeyDown();
		cHelpPet.KeyDown();
		cSinSod2.KeyDown();
		chaSiege.KeyDown();

		if (sinGetKeyClick('X')) {
			cHelpPet.PetMessage("*System", 3);
			if (!ExitButtonClick)ExitButtonClick = 1;
			else ExitButtonClick = 0;
			cInterFace.CheckAllBox(SIN_SYSTEM);
		}
		if (sinGetKeyClick('R')) {
			cHelpPet.PetMessage("*RunAndWalk", 3);
			if (cInterFace.sInterFlags.RunFlag)cInterFace.sInterFlags.RunFlag = 0;
			else cInterFace.sInterFlags.RunFlag = 1;
		}
		if (sinGetKeyClick(VK_TAB)) {
			cHelpPet.PetMessage("*Mini_Map", 3);
			if (cInterFace.sInterFlags.MapOnFlag)cInterFace.sInterFlags.MapOnFlag = 0;
			else cInterFace.sInterFlags.MapOnFlag = 1;
		}
		if (sinGetKeyClick('Z')) {
			cInterFace.sInterFlags.CameraAutoFlag++;
			if (cInterFace.sInterFlags.CameraAutoFlag > 2)cInterFace.sInterFlags.CameraAutoFlag = 0;
		}
		if (sinGetKeyClick('D')) {
			cHelpPet.PetMessage("*Party", 3);

			/*if (Social::GetInstance()->IsOpen())
			{
				Social::GetInstance()->Close();
			}
			else
			{
				Social::GetInstance()->Open();
			}*/

			ShowParty();
		}

		if (sinGetKeyClick('Q'))
		{
			cHelpPet.PetMessage("*Quest", 3);
			ShowQuest();
		}

		if (sinGetKeyClick(VK_SPACE)) {
			cMessageBox.CloseMessage();
			if (!cCraftItem.OpenFlag && !cAging.OpenFlag /*&& !SmeltingItem.OpenFlag && !ManufactureItem.m_OpenFlag*/ /*|| !cMixtureReset.OpenFlag*/)
				cInterFace.CheckAllBox(SIN_ALL_CLOSE);
		}

		unsigned int stage = StageField[lpCurPlayer->OnStageField]->FieldCode;

		if (sinGetKeyClick('K'))
		{
			if (lpCurPlayer->PvP_Param)
			{
				if (GetPlayTime_T() > lpCurPlayer->PvP_Time)
				{
					lpCurPlayer->PvP_Param = false;
					AddChatBuff("Modo PvP desativado!");

					smTRANS_COMMAND	TransCommand;
					TransCommand.code = smTRANSCODE_PVP_MODE;
					TransCommand.size = sizeof(smTRANS_COMMAND);
					TransCommand.WParam = lpCurPlayer->PvP_Param;

					smWINSOCK* lpsmSock;
					lpsmSock = GetAreaServerSock();

					if (lpsmSock)
					{
						lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
					}
				}
				else if (!MsgError)
				{
					MsgError = 1;
					char szBuff[256];

					DWORD Time = lpCurPlayer->PvP_Time - GetPlayTime_T();
					UINT Days = Time / 60 / 60 / 24;
					UINT Hours = (Time / 60 / 60) % 24;
					UINT Minutes = (Time / 60) % 60;
					UINT Seconds = Time % 60;

					wsprintf(szBuff, "Aguarde %02d:%02d:%02d, para poder desativar o modo PvP.", Hours, Minutes, Seconds);
					AddChatBuff(szBuff);
				}
			}
			else
			{
				if (stage == 3 || stage == 21 || stage == 16)
				{
					AddChatBuff("> Não é Possivel Ativar Modo Pvp na cidade.", 14);
				}
				else
				{
					lpCurPlayer->PvP_Time = GetPlayTime_T() + 60 * 1;
					MsgError = 0;
					lpCurPlayer->PvP_Param = true;
					AddChatBuff("Modo PvP ativado!");

					smTRANS_COMMAND	TransCommand;
					TransCommand.code = smTRANSCODE_PVP_MODE;
					TransCommand.size = sizeof(smTRANS_COMMAND);
					TransCommand.WParam = lpCurPlayer->PvP_Param;

					smWINSOCK* lpsmSock;
					lpsmSock = GetAreaServerSock();

					if (lpsmSock)
					{
						lpsmSock->Send((char*)&TransCommand, TransCommand.size, TRUE);
					}
				}
			}
		}

		/*if (PVIP == 1)
		{
			if (sinGetKeyClick('F') && sinGetKeyClick(VK_CONTROL))
			{
				if (cShop.OpenFlag == SIN_CLOSE)cShop.OpenFlag = SIN_OPEN;
				else cShop.OpenFlag = SIN_CLOSE;
			}

			if (sinGetKeyClick('G') && sinGetKeyClick(VK_CONTROL)) {
				if (cCraftItem.OpenFlag == SIN_CLOSE)cCraftItem.OpenFlag = SIN_OPEN;
				else cCraftItem.OpenFlag = SIN_CLOSE;
			}
		}*/

		/*if (PVIP == 2)
		{
			if (sinGetKeyClick('F') && sinGetKeyClick(VK_CONTROL))
			{
				if (cShop.OpenFlag == SIN_CLOSE)cShop.OpenFlag = SIN_OPEN;
				else cShop.OpenFlag = SIN_CLOSE;
			}

			if (sinGetKeyClick('G') && sinGetKeyClick(VK_CONTROL)) {
				if (cCraftItem.OpenFlag == SIN_CLOSE)cCraftItem.OpenFlag = SIN_OPEN;
				else cCraftItem.OpenFlag = SIN_CLOSE;
			}

			if (sinGetKeyClick('H') && sinGetKeyClick(VK_CONTROL)) {
				if (cWareHouse.OpenFlag == SIN_CLOSE)cWareHouse.OpenFlag = SIN_OPEN;
				else cWareHouse.OpenFlag = SIN_CLOSE;
			}
			if (sinGetKeyClick('J') && sinGetKeyClick(VK_CONTROL)) {
				if (cAging.OpenFlag == SIN_CLOSE)cAging.OpenFlag = SIN_OPEN;
				else cAging.OpenFlag = SIN_CLOSE;
			}

			if (sinGetKeyClick('L') && sinGetKeyClick(VK_CONTROL)) {
				if (cCraftItem.ForceFlag == SIN_CLOSE)cCraftItem.ForceFlag = SIN_OPEN;
				else cCraftItem.ForceFlag = SIN_CLOSE;
			}
		}*/

		if (smConfig.DebugMode) {
			if (sinGetKeyClick('T') && sinGetKeyClick(VK_CONTROL)) {
				if (sinTestFlag)sinTestFlag = 0;
				else sinTestFlag = 1;
			}

			if (sinGetKeyClick('F') && sinGetKeyClick(VK_CONTROL)) {
				if (cShop.OpenFlag == SIN_CLOSE)cShop.OpenFlag = SIN_OPEN;
				else cShop.OpenFlag = SIN_CLOSE;
			}
			if (sinGetKeyClick('G') && sinGetKeyClick(VK_CONTROL)) {
				if (cCraftItem.OpenFlag == SIN_CLOSE)cCraftItem.OpenFlag = SIN_OPEN;
				else cCraftItem.OpenFlag = SIN_CLOSE;
			}
			if (sinGetKeyClick('H') && sinGetKeyClick(VK_CONTROL)) {
				if (cCraftItem.ForceFlag == SIN_CLOSE)cCraftItem.ForceFlag = SIN_OPEN;
				else cCraftItem.ForceFlag = SIN_CLOSE;
			}
		}
#ifdef _SINBARAM_TEST
		sinTestKey();
#endif

		break;
	}
}

void sinClose()
{
	void clanMENU_close();
	clanMENU_close();

	cInvenTory.Close();
	cCharStatus.Close();
	cInterFace.Close();
	cItem.Close();
	cSkill.Close();
	cShop.Close();
	cTrade.Close();
	cMessageBox.Close();
	cSin3D.Close();
	cSinHelp.Close();
	cSinWarpGate.Close();
	cHelpPet.Close();
	cSinSod2.Close();

	cPCBANGPet.Close();
}