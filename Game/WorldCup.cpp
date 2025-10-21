#include "sinbaram\sinLinkHeader.h"

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
sITEMINFO* FindItemFromCode(DWORD dwItemCode);
int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);
int	rsFindInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);
sDEF_ITEMINFO* PremioQuest(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode);
int rsPutItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode);

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

void WorldCup::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\hellsgate\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\hellsgate\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\hellsgate\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

bool WorldCup::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void WorldCup::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

#define MAX_AWARD 143

void WorldCup::SendRandomItem(rsPLAYINFO* Player)
{
	DWORD AwardList[MAX_AWARD] = {
	sinFO1 | sin10, sinFO1 | sin11, sinFO1 | sin12, sinFO1 | sin13, sinOS1 | sin10, sinOS1 | sin11, sinOS1 | sin12, sinOS1 | sin13, sinBI1 | sin68,
	sinCA6 | sin43,sinCA6 | sin01,sinCA6 | sin03,sinCA6 | sin07,sinOS1 | sin13,sinBI1 | sin67,sinCA1 | sin37,sinBI1 | sin66,sinOS1 | sin12,
	sinBI1 | sin43, sinBI1 | sin14, sinBI1 | sin12, sinBI1 | sin24, sinBI1 | sin25, sinBI1 | sin29, sinBI1 | sin28,sinBI1 | sin92,sinBI1 | sin91,
	sinBI2 | sin67, sinBI1 | sin20, sinBI1 | sin22, sinBI3 | sin19,sinSE1 | sin05,sinCA5 | sin25,sinCA5 | sin35,sinCA5 | sin39,
	sinBI1 | sin85, sinBI1 | sin85,sinCA6 | sin08,sinCA6 | sin16,sinCA6 | sin27,sinCA6 | sin33, sinBI1 | sin85,sinCA1 | sin45,sinOS1 | sin11,
	sinBI1 | sin61, sinBI1 | sin85, sinBI1 | sin11,sinBI1 | sin67,sinCA6 | sin15,sinCA6 | sin25,sinCA6 | sin31,sinCA6 | sin35,sinCA6 | sin39,
	sinCA1 | sin35,sinCA1 | sin43,sinCA5 | sin01,sinCA5 | sin03,sinCA5 | sin15, sinBI1 | sin29, sinBI1 | sin28,sinBI1 | sin92,sinBI1 | sin91,
	sinCA6 | sin02,sinCA6 | sin05, sinBI1 | sin11,sinBI1 | sin68, sinBI1 | sin43,sinBI1 | sin61,sinCA6 | sin37,sinCA6 | sin41,sinCA6 | sin65,
	sinBI1 | sin61, sinBI1 | sin85, sinBI1 | sin11, sinBI1 | sin65,sinOS1 | sin13,sinBI1 | sin66,sinOS1 | sin11,sinOS1 | sin13,sinOS1 | sin12,
	sinBI1 | sin43, sinBI1 | sin14, sinBI1 | sin12, sinBI1 | sin24, sinBI1 | sin25, sinBI1 | sin29, sinBI1 | sin28,sinBI1 | sin92,sinBI1 | sin91,
	sinBI2 | sin67, sinBI1 | sin20, sinBI1 | sin22, sinBI3 | sin19,sinSE1 | sin05,sinFO1 | sin10,sinFO1 | sin11,sinFO1 | sin12,sinFO1 | sin13,
	sinBI1 | sin85, sinBI1 | sin85, sinBI1 | sin11, sinBI1 | sin65, sinBI1 | sin43,sinBI1 | sin61, sinBI1 | sin85, sinBI1 | sin11,sinBI1 | sin68,
	sinBI1 | sin43, sinBI1 | sin14, sinBI1 | sin12, sinBI1 | sin24, sinBI1 | sin25, sinBI1 | sin29, sinBI1 | sin28,sinBI1 | sin92,sinBI1 | sin91,
	sinBI2 | sin67, sinBI1 | sin20, sinBI1 | sin22, sinBI3 | sin19,sinSE1 | sin05,sinFO1 | sin10,sinFO1 | sin11,sinFO1 | sin12,sinFO1 | sin13,
	sinBI1 | sin85, sinBI1 | sin85, sinBI1 | sin11,sinOS1 | sin13, sinBI1 | sin43,sinBI1 | sin61, sinBI1 | sin85, sinBI1 | sin11,sinOS1 | sin13,
	sinCA1 | sin37,sinCA5 | sin02,sinCA5 | sin16,sinOS1 | sin12, sinBI1 | sin43,sinBI1 | sin61,sinCA5 | sin27,sinCA5 | sin33,sinCA5 | sin37 };

	int Rand = rand() % MAX_AWARD;
	rsPutItem(Player, AwardList[Rand]);
}

void WorldCup::RecvRequest(rsPLAYINFO* Player)
{
	if (rsFindInvenItem(Player, sinGF1 | sin03) &&
		rsFindInvenItem(Player, sinGF1 | sin04))
	{
		SendRandomItem(Player);
	}
}

void WorldCup::SendRequest()
{
	if (FindItemFromCode(sinGF1 | sin03) &&
		FindItemFromCode(sinGF1 | sin04))
	{
		sITEMINFO* lpItemInfo = FindItemFromCode(sinGF1 | sin03);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinGF1 | sin04);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);

		smTRANS_COMMAND ps;
		ps.size = sizeof(smTRANS_COMMAND);
		ps.code = smTRANSCODE_WORLDCUP;

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

void WorldCup::Button()
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

void WorldCup::Open()
{
	if (FindItemFromCode(sinGF1 | sin03) &&
		FindItemFromCode(sinGF1 | sin04))

		LoadTextFromFile("game\\npc\\worldcup_done.txt");
	else
		LoadTextFromFile("game\\npc\\worldcup_progress.txt");

	fOpen = true;
}

void WorldCup::Close()
{
	fOpen = false;
}

void WorldCup::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);
		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[WORLD CUP 2022]", 16, &size);
		dsTextLineOut(WinX + 280 - size.cx / 2, WinY + 40, "[WORLD CUP 2022]", 16);
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