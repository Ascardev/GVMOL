int sinAssaSkillEffectKeyDown();

int sinAssaSkillEffectProcess(cASSAEFFECT* pEffect);

int sinSkillEffect_Brandish(smCHAR* pChar);
int sinSkillEffect_Piercing(smCHAR* pChar);
int sinSkillEffect_RushElbow_Attack(smCHAR* pChar);
int sinSkillEffect_Piercing_Attack(smCHAR* pChar);
int sinSkillEffect_DrasticSpirit(smCHAR* pChar);
int sinSkillEffect_SoulBreaker_Attack(smCHAR* pChar);
int sinSkillEffect_SoulBreaker1(smCHAR* pChar, smCHAR* chrAttackTarget);
int sinSkillEffect_SoulBreaker2(smCHAR* pChar);
int sinSkillEffect_Saint_Blade(smCHAR* pChar);

int sinSkillEffect_Energy_Shelter(smCHAR* pChar);
int sinSkillEffect_ThirdAnima(smCHAR* pChar, smCHAR* chrAttackTarget);

int sinSkillEffect_Great_Healing(smCHAR* pChar);
int sinSkillEffect_Great_Healing_Party(smCHAR* pChar);
int sinSkillEffect_Holy_Reflection(smCHAR* pChar, int Time);
int sinSkillEffect_Holy_Reflection_Defense(smCHAR* pChar);

int sinSkillEffect_HolyMind(smCHAR* pChar, int Time);

int sinSkillEffect_Soul_Sucker(smCHAR* pChar, smCHAR* DesChar);

int sinSkillEffect_Windy(smCHAR* pChar);
int sinSkillEffect_Windy_Gather(smCHAR* pChar);

void sinSkillEffect_PowerDash_HitMonster(smCHAR* pChar);