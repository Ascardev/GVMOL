#pragma once

struct smCHAR_INFO;
class rsPLAYINFO;

class Bellatra
{
public:
	virtual						~Bellatra();
	static Bellatra* GetInstance() { static Bellatra instance; return &instance; };

	void GetClanName(const char* Nick, char* ClanName);

	int GetClanNamePoint(const char* Nick);

	void RecordClanPoint(const char* pszClanName, int iPoint, int iOldPoint);

	void UpdateClanBellatra();

	void UpdateClanCrownBellatra();

	int GetClanCodePoint(int CODECLAN);

	void RecordPoint(rsPLAYINFO* lpPlayInfo, int Level, int SodScore, int KillCount, int TotalSodScore, int SodTotalUser, int SodTotalUserSucess, int SodCode);

private:
	Bellatra();
	int fOpen;
	int Param;
	int cImages[3];
};
