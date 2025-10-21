#include "sinbaram\sinLinkHeader.h"

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
sITEMINFO* FindItemFromCode(DWORD dwItemCode);
int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);
int	rsFindInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);
//sDEF_ITEMINFO* PremioQuest(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode);
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

void Natal::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\hellsgate\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\hellsgate\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\hellsgate\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

bool Natal::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void Natal::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

#define MAX_AWARD 53

void Natal::SendRandomItem(rsPLAYINFO* Player)
{
	rsPutItem(Player, sinBI2 | sin69);
}

void Natal::RecvRequest(rsPLAYINFO* Player)
{
	if (rsFindInvenItem(Player, sinEV2 | sin01) &&
		rsFindInvenItem(Player, sinEV2 | sin02))
	{
		SendRandomItem(Player);
	}
}

void Natal::SendRequest()
{
	if (FindItemFromCode(sinEV2 | sin01) &&
		FindItemFromCode(sinEV2 | sin01))
	{
		sITEMINFO* lpItemInfo = FindItemFromCode(sinEV2 | sin01);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);
		lpItemInfo = FindItemFromCode(sinEV2 | sin02);
		cInvenTory.DeleteInvenItemToServer(lpItemInfo->CODE, lpItemInfo->ItemHeader.Head, lpItemInfo->ItemHeader.dwChkSum);

		smTRANS_COMMAND ps;
		ps.size = sizeof(smTRANS_COMMAND);
		ps.code = smTRANSCODE_NATAL;

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

void Natal::Button()
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

void Natal::Open()
{
	if (FindItemFromCode(sinEV2 | sin01) &&
		FindItemFromCode(sinEV2 | sin02))

		LoadTextFromFile("game\\npc\\natal_done.txt");
	else
		LoadTextFromFile("game\\npc\\natal_progress.txt");

	fOpen = true;
}

void Natal::Close()
{
	fOpen = false;
}

void Natal::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);
		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[MERRY CHRISTMAS]", 17, &size);
		dsTextLineOut(WinX + 280 - size.cx / 2, WinY + 40, "[MERRY CHRISTMAS]", 17);
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