#include "sinbaram\sinLinkHeader.h"

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
sITEMINFO* FindItemFromCode(DWORD dwItemCode);
int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);
int	rsFindInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);
sDEF_ITEMINFO* PremioQuest(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode);

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

void Puzzle::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\hellsgate\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\hellsgate\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\hellsgate\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

bool Puzzle::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Puzzle::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

#define MAX_AWARD 53

void Puzzle::SendRandomItem(rsPLAYINFO* Player)
{
	switch (Player->smCharInfo.JOB_CODE)
	{
	case JOBCODE_FIGHTER:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_FIGHTER); // Ok
		break;
	case JOBCODE_MECHANICIAN:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_MECHANICIAN); // Ok
		break;
	case JOBCODE_ARCHER:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_ARCHER); // Ok
		break;
	case JOBCODE_PIKEMAN:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_PIKEMAN); // Ok
		break;
	case JOBCODE_ATALANTA:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_ATALANTA); // Ok
		break;
	case JOBCODE_KNIGHT:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_KNIGHT); // Ok
		break;
	case JOBCODE_MAGICIAN:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_MAGICIAN); // Ok
		break;
	case JOBCODE_PRIESTESS:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_PRIESTESS); // Ok
		break;
	case JOBCODE_ASSASSINE:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_ASSASSINE); // Ok
		break;
	case JOBCODE_SHAMAN:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_SHAMAN); // Ok
		break;
	case JOBCODE_MARTIAL:
		PremioQuest(Player, (sinDB1 | sin35), JOBCODE_MARTIAL); // Ok
		break;
	}
}

void Puzzle::RecvRequest(rsPLAYINFO* Player)
{
	if (rsFindInvenItem(Player, sinEV1 | sin01) &&
		rsFindInvenItem(Player, sinEV1 | sin02) &&
		rsFindInvenItem(Player, sinEV1 | sin03) &&
		rsFindInvenItem(Player, sinEV1 | sin04) &&
		rsFindInvenItem(Player, sinEV1 | sin05) &&
		rsFindInvenItem(Player, sinEV1 | sin06) &&
		rsFindInvenItem(Player, sinEV1 | sin07) &&
		rsFindInvenItem(Player, sinEV1 | sin08))
	{
		SendRandomItem(Player);
	}
}

void Puzzle::SendRequest()
{
	if (FindItemFromCode(sinEV1 | sin01) &&
		FindItemFromCode(sinEV1 | sin02) &&
		FindItemFromCode(sinEV1 | sin03) &&
		FindItemFromCode(sinEV1 | sin04) &&
		FindItemFromCode(sinEV1 | sin05) &&
		FindItemFromCode(sinEV1 | sin06) &&
		FindItemFromCode(sinEV1 | sin07) &&
		FindItemFromCode(sinEV1 | sin08))
	{
		sITEMINFO* lpItemInfo = FindItemFromCode(sinEV1 | sin01);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV1 | sin02);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV1 | sin03);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV1 | sin04);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV1 | sin05);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV1 | sin06);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV1 | sin07);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV1 | sin08);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);

		smTRANS_COMMAND ps;
		ps.size = sizeof(smTRANS_COMMAND);
		ps.code = smTRANSCODE_PUZZLE;

		smWINSOCK* lpsmSock;
		lpsmSock = GetAreaServerSock();

		if (lpsmSock)
		{
			lpsmSock->Send((char*)&ps, ps.size, TRUE);
		}

		fOpen = false;
	}
	else
	{
		fOpen = false;
	}
}

void Puzzle::Button()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;

		if (MouseAction(WinX + 200, WinY + 400, 80, 21))
		{
			SendRequest();
		}

		if (MouseAction(WinX + 300, WinY + 400, 80, 21))
			Close();
	}
}

void Puzzle::Open()
{
	if (FindItemFromCode(sinEV1 | sin01) &&
		FindItemFromCode(sinEV1 | sin02) &&
		FindItemFromCode(sinEV1 | sin03) &&
		FindItemFromCode(sinEV1 | sin04) &&
		FindItemFromCode(sinEV1 | sin05) &&
		FindItemFromCode(sinEV1 | sin06) &&
		FindItemFromCode(sinEV1 | sin07) &&
		FindItemFromCode(sinEV1 | sin08))

		LoadTextFromFile("game\\npc\\puzzle_done.txt");
	else
		LoadTextFromFile("game\\npc\\puzzle_progress.txt");

	fOpen = true;
}

void Puzzle::Close()
{
	fOpen = false;
}

void Puzzle::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);
		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Químico]", 9, &size);
		dsTextLineOut(WinX + 280 - size.cx / 2, WinY + 40, "[Químico]", 9);
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
}