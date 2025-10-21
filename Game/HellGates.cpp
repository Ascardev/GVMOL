#include "sinbaram\sinLinkHeader.h"
#include "./field.h"

int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
int	rsSendServerChatMessageToAllUser(int Color, char* msg, ...);
smCHAR* OpenMonsterFromName(char* szName, int x, int y, int z, rsPLAYINFO* lpPlayInfo = 0);
rsPLAYINFO* rsPlayInfo;
smCHAR* Mob = nullptr;

DWORD		dwPlayServTime = 0;

int DrawFontImage(char* lpStr, int xPos, int yPos, DWORD rgba, float fRatio);

void HellGates::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\hellsgate\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\hellsgate\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\hellsgate\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[5] = CreateTextureMaterial("game\\images\\UI\\bosshp.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[6] = CreateTextureMaterial("game\\images\\UI\\bosshp_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

char szBufferTextWindow[8092];

void LoadTextFromFile(const char* pszFile)
{
	FILE* pFile = NULL;

	ZeroMemory(szBufferTextWindow, 8092);

	fopen_s(&pFile, pszFile, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		int iSizeFile = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		if (iSizeFile > 8092)
			iSizeFile = 8092;

		fread(szBufferTextWindow, iSizeFile, 1, pFile);
		fclose(pFile);
	}

	szBufferTextWindow;
}

void HellGates::Open()
{
	if (Flag == 0)
		LoadTextFromFile("game\\npc\\hellgates_closed.txt");
	if (Flag == 1)
		LoadTextFromFile("game\\npc\\hellgates_open.txt");
	if (Flag == 2)
		LoadTextFromFile("game\\npc\\hellgates_onbattle.txt");

	fOpen = true;
}

void HellGates::RecvInformation(smTRANS_BA_INFO* ps)
{
	if (ps->Flag == 0 && Flag == 2 && StageField[lpCurPlayer->OnStageField]->FieldCode == 23)
	{
		TeleportTime = GetCurrentTime() + 20 * 1000;
		TeleportFlag = true;
	}

	Flag = ps->Flag;
	EndTime = ps->EndTime;
}

bool HellGates::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void HellGates::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void HellGates::SetTime(int CurrentTime)
{
	DWORD Time = EndTime - CurrentTime;

	PlayTime[0] = Time % 60;
	PlayTime[1] = Time / 60;
	PlayTime[1] -= Time / 3600 * 60;
}

short HellGates::GetTime()
{
	if (Flag == 1)
		return (short)((dwPlayServTime - StartOpenTime) / 1000);
	if (Flag == 2)
		return (short)((dwPlayServTime - StartBattleTime) / 1000);

	return 0;
}

void HellGates::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);
		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Portões do Inferno]", 21, &size);
		dsTextLineOut(WinX + 280 - size.cx / 2, WinY + 40, "[Portões do Inferno]", 21);
		FontType = 0;
		dsTextLineOut(WinX + 60, WinY + 80, szBufferTextWindow, strlen(szBufferTextWindow));

		if (MouseAction(WinX + 200, WinY + 400, 93, 23))
			DrawImage(Images[2], WinX + 200, WinY + 400, 93, 23);
		else
			DrawImage(Images[1], WinX + 200, WinY + 400, 93, 23);

		if (MouseAction(WinX + 300, WinY + 400, 93, 23))
			DrawImage(Images[4], WinX + 300, WinY + 400, 93, 23);
		else
			DrawImage(Images[3], WinX + 300, WinY + 400, 93, 23);
	}

	if (StageField[lpCurPlayer->OnStageField]->FieldCode == 23)
	{
		if (Flag == 1)
		{
			char szBuff[256];
			int x = (WinSizeX / 2) - 80;
			wsprintf(szBuff, "Tempo Restante: %d:%d", PlayTime[1], PlayTime[0]);
			DrawFontImage(szBuff, x, 8, D3DCOLOR_RGBA(80, 160, 255, 255), 0.7f);
		}
		else if (Flag == 2)
		{
			char szBuff[256];
			int x = (WinSizeX / 2) - 80;

			wsprintf(szBuff, "Tempo Restante: %d:%d", PlayTime[1], PlayTime[0]);
			DrawFontImage(szBuff, x, 8, D3DCOLOR_RGBA(80, 160, 255, 255), 0.7f);
		}
	}
}

void HellGates::Button()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);

		if (MouseAction(WinX + 200, WinY + 400, 80, 21))
		{
			SendRequest();
		}

		if (MouseAction(WinX + 300, WinY + 400, 80, 21))
			fOpen = false;
	}
}

void Teleport(int Field, int x, int z)
{
	int dx = 0;
	int dz = 0;
	int cnt = 0;

	CloseEachPlayer();

	WarpFieldNearPos(Field, x, z, &dx, &dz);

	lpCurPlayer->SetPosi(x, 0, z, 0, 0, 0);
	TraceCameraPosi.x = lpCurPlayer->pX;
	TraceCameraPosi.y = lpCurPlayer->pY;
	TraceCameraPosi.z = lpCurPlayer->pZ;
	TraceTargetPosi.x = lpCurPlayer->pX;
	TraceTargetPosi.y = lpCurPlayer->pY;
	TraceTargetPosi.z = lpCurPlayer->pZ;

	lpCurPlayer->OnStageField = -1;
	if (smGameStage[0])
	{
		cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
		lpCurPlayer->OnStageField = 0;
	}
	if (cnt == CLIP_OUT && smGameStage[1])
	{
		lpCurPlayer->OnStageField = 1;
	}
}

void HellGates::SendRequest()
{
	if (Flag == 1)
	{
		smTRANS_COMMAND ps;
		ps.size = sizeof(smTRANS_COMMAND);
		ps.code = smTRANSCODE_HELL_GATES;

		smWINSOCK* lpsmSock;
		lpsmSock = GetAreaServerSock();

		if (lpsmSock)
		{
			lpsmSock->Send((char*)&ps, ps.size, TRUE);
		}

		Teleport(23, -3644 * fONE, -43174 * fONE);

		fOpen = false;
	}
	else
	{
		cMessageBox.ShowMessageEvent("Os portões do inferno não estão mais abertos!");
		fOpen = false;
	}
}

void HellGates::OpenBattle()
{
	StartOpenTime = dwPlayServTime;
	OverOpenTime = dwPlayServTime + 3 * 60 * 1000;
}

void HellGates::StartBattle()
{
	StartBattleTime = dwPlayServTime;
	OverBattleTime = dwPlayServTime + 20 * 60 * 1000;
}

void HellGates::DrawHP(smCHAR* Character)
{
	if (Character->smCharInfo.wPlayClass[0] == MONSTER_CLASS_BOSS)
	{
		dsDrawTexImage(Images[5], WinSizeX / 2 - 237, 30, 473, 57, 255);
		int LifePercent = (int)(((double)Character->smCharInfo.Life[0] / (double)Character->smCharInfo.Life[1]) * 100.0);
		int LifeCurrentSize = 473 * LifePercent / 100;

		HoDrawTexImage(Images[6], WinSizeX / 2 - 237, 29, 473, 57, LifeCurrentSize, 57, 255);

		SIZE size;
		FontType = 1;
		char szBuff[5];
		wsprintf(szBuff, "%d%s", LifePercent, "%");
		GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
		dsTextLineOut(WinSizeX / 2 - 237 + 236 - size.cx / 2, 30 + 28 - size.cy / 2, szBuff, strlen(szBuff));
		FontType = 0;
	}
}

void HellGates::OnEnter(rsPLAYINFO* Player)
{
	if (Flag == 1)
	{
		Player->OnHellGates = 1;
	}
}

void HellGates::OnClose(rsPLAYINFO* Player)
{
	if (Flag == 1 || Flag == 2)
	{
		Player->OnHellGates = 0;
	}
}

void HellGates::Main()
{
	if (TeleportFlag)
	{
		if (GetCurrentTime() >= TeleportTime)
		{
			if (StageField[lpCurPlayer->OnStageField]->FieldCode == 23)
			{
				TeleportFlag = false;
				WarpField2(3);
			}
		}
	}
}

void HellGates::SendInformation(rsPLAYINFO* Player)
{
	smTRANS_BA_INFO ps;
	ps.size = sizeof(smTRANS_BA_INFO);
	ps.code = smTRANSCODE_HELL_GATES;
	ps.Flag = Flag;
	if (Flag == 1)
		ps.EndTime = (short)((OverOpenTime - StartOpenTime) / 1000);
	if (Flag == 2)
		ps.EndTime = (short)((OverBattleTime - StartBattleTime) / 1000);

	Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
}