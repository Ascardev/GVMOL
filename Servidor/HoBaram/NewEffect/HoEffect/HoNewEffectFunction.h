#ifndef _HO_NEW_EFFECT_FUNCTION_H_
#define _HO_NEW_EFFECT_FUNCTION_H_

#include "..\\..\\..\\smlib3d\\smd3d.h"
#include "..\\..\\..\\smwsock.h"
#include "..\\..\\..\\character.h"

void SkillMetalionImpulsionHit(smCHAR** pChar, int charCount);
void SkillMetalionCompulsion(smCHAR* pChar);
void SkillMetalionSphere(smCHAR* pChar, float time, float attackTime);
void SkillMetalionSphereDefence(POINT3D* curPos, POINT3D* desPos, bool flag = true);
void SkillMetalionGolem(smCHAR* pChar);

void SkillWarriorDestroyerBlade(smCHAR* pChar, float time);
void SkillWarriorDestroyerHit(POINT3D* pos);
void SkillWarriorBetserker(smCHAR* pChar, float time);
void SkillWarriorCycloneStrikeBlade(smCHAR* pChar, float time);
void SkillWarriorBloodyBerserker(smCHAR* pChar, float time);

void SkillLancelotAssassinEye(smCHAR* pChar, float time);
void SkillLancelotChargingStrike(smCHAR* pChar);
void SkillLancelotVague(smCHAR* pChar);

void SkillSagittarionPhoneixShot(smCHAR* pChar, POINT3D* curPos, POINT3D* desPos);
void SkillSagittarionForceOfNature1(smCHAR* pChar, float time);
void SkillSagittarionForceOfNature2(smCHAR* pChar, float time);

void SkillSaintDivinePiercing(smCHAR* pChar);
void SkillSaintGodBless(smCHAR* pChar, float time);
void SkillSwordOfUstice(smCHAR* pChar);

void SkillValhallaHallOfValhalla1(smCHAR* pChar);
void SkillValhallaXRage(POINT3D* curPos, POINT3D* desPos);
void SkillFrostJavelin(POINT3D* curPos, POINT3D* desPos);
void SkillForstJavelinAttach(smCHAR* pChar, float time);
void SkillVengeance(POINT3D* curPos, POINT3D* desPos);

void SkillCelestialGlacialSpike(smCHAR* pChar);
void SkillCelestialRegnerationField(smCHAR* pChar, float time);
void SkillCelestialMusPel(smCHAR* pChar, float time, float attackTime, int dwSkillCode);
void CelestialChainLighting(smCHAR** pChar, int count);
void SkillArchMageMeteo(POINT3D* desPos, DWORD dwSkillCode);
void SkillArchMageFireElementalHand(smCHAR* pChar);
void SkillArchMageFireElementalShot(POINT3D* curPos, POINT3D* desPos);

BOOL GetAssaCodeEffect(smCHAR* pChar, int code);

void Valento_PowerUp(smCHAR* pChar);
void Valento_Justice(smCHAR* pChar);

void ParkIncubusSummonerSkill(smCHAR* pChar);
void DevilBird_Skill(smCHAR* pChar);

void Effect_Costume_Wing(smCHAR* pChar, DWORD dwWingType);
void Effect_Costume_Wing_Stop(smCHAR* pChar, DWORD dwWingType);
void EffectTopLevel(smCHAR* pChar);
void EffectTopPvP(smCHAR* pChar);

void Skill_PikeMan_DancingReaper(smCHAR* pChar, float time);
void AssaParticle_DancingReaper(POINT3D* pPosi);
void AssaParticle_FinalSpear1(smCHAR* pDestChar);
void AssaParticle_Amplified(smCHAR* pDestChar, int liveCount);
void Skill_PikeMan_SideSpinAttack(smCHAR* pChar, float time);
void AssaParticle_Talaria_StartEffect(smCHAR* pChar);
void AssaParticle_Talaria_RemainEffect(smCHAR* pDestChar, int liveCount);
void ParkAssaParticl_GalaxyCoup1(smCHAR* pChar);
void AssaParticle_SnippyFear(POINT3D* pPosi, POINT3D* pDesti);
void AssaParticle_SummonArcuda_Effect(smCHAR* pChar);
void ParkAssaParticle_BlessingKrishna1(smCHAR* pChar);
void AssaParticle_BlessingKrishna(smCHAR* pDestChar, int liveCount);
void AssaParticle_HyperSonic(smCHAR* pChar, int maxTime);
void AssaParticle_PowerEnhance(smCHAR* pChar, int time);
void AssaParticle_RollingSmashHitEffect(POINT3D* pPosi);
void AssaParticle_RollingSmashJumpEffect(POINT3D* pPosi);
void  AssaParticle_RollingSmashDownEffect(POINT3D* pPosi);
void Skill5_Mecanician_HyperSonic(smCHAR* pChar);
void AssaParticle_Crescent_Moon(smCHAR* pDestChar);
void AssaParticle_EvadeShot(smCHAR* pDestChar);
void ParkAssaParticle_EvadeShot1(smCHAR* pChar);
void ParkAssaParticle_EvadeShot2(smCHAR* pChar);
void AssaParticle_ThunderRoop(POINT3D* pCur, POINT3D* pDest);
void AssaParticle_ThunerRoopShot(POINT3D* pPosi);
void AssaParticle_NatureSplashShot(smCHAR* pChar);
void SkillMagicianPrimaIgnis(smCHAR* pChar);
void AssaParticle_SaintBlade_HitEffect1(POINT3D* pPosi);
void AssaParticle_SaintBlade_HitEffect2(POINT3D* pPosi);
void ParkAssaParticle_Crescent_Moon1(POINT3D* pPosi);
void sinSkillEffect_CresectMoon(smCHAR* pChar);
void AssaParticle_HolyBenedicHand(smCHAR* pDestChar);
void AssaParticle_HolyBenedicShot(smCHAR* pDestChar);
void AssaParticle_HolyBenedic(smCHAR* pDestChar, int liveCount);
void AssaParticle_CircleTrap(POINT3D* pPosi, POINT3D* pDest, int type);
#endif
