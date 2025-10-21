struct CRegen {
	float HP;
	float MP;
	float STM;
};

class Regen
{
public:


	void SetHP(float HP) { Character.HP = HP; };
	void SetMP(float MP) { Character.MP = MP; };
	void SetSTM(float STM) { Character.STM = STM; };

	float GetHP() { return Character.HP; };
	float GetMP() { return Character.MP; };
	float GetSTM() { return Character.STM; };

private:
	CRegen Character;
};
