class Battle
{
public:
	static Battle* GetInstance() { static Battle instance; return &instance; };
	void OnBattle(rsPLAYINFO* Killer, rsPLAYINFO* Murdered);
	int GetLevelByExp(int Exp);
	void GetExpByCharacter(rsPLAYINFO* Player);
	void SaveExp(rsPLAYINFO* Player);
	int GetExpGainKiller(int LevelDifference);
	int GetExpGainMurdered(int LevelDifference);
	int GetExpLoss(int BattleLevel);
	void SendBattleExp(rsPLAYINFO* Player);
	void RecvBattleExp(smTRANS_COMMAND* packet);
private:
	int Level;
	int Exp;
};
