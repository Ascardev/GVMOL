#pragma once

#include "sinbaram/sinLinkHeader.h"

class cKILL
{
public:
	void Init();
	void Draw();
	void recvKill(int Streak, int Class);
	void handleDeath();

private:
	LPDIRECT3DTEXTURE9 lpClass[11];
	LPDIRECT3DTEXTURE9 lpKills[9];

	enum KILLS
	{
		DOUBLEKILL = 1,
		TRIPLEKILL,
		QUADRAKILL,
		PENTAKILL,
		SHUTDOWN,
		RAMPAGE,
		UNSTOPPABLE,
		LEGENDARY,
		KILLINGSPREE,
	};

	struct SHOWKILL_INFO
	{
		int Kind;
		DWORD initTime;
		DWORD Duration;
		int Class;
	};

	SHOWKILL_INFO sKillInfo;

	int CurrentStreak;
};

extern cKILL cKill;