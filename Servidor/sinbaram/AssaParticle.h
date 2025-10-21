




	
#ifndef _ASSAPARTICLE_HEADER_

#define _ASSAPARTICLE_HEADER_



	
void sinAssaParticleProcess(cASSAEFFECT *pEffect); 
int sinAssaParticleKeyDown();




	


int AssaParticle_Stune(smCHAR *pChar );


int AssaMakeCircle(POINT3D *pPosi , char *FileName , int Radius);


int AssaParticle_RisingBelt(POINT3D *pPosi ,char *FileName,int ContinueTime , int SpeedY );


int AssaParticle_RisingParticle(POINT3D *pPosi , char *FileName ,int Size ,  int ContinueTime , int Range , int Count , int SpeedY);


int AssaParticle_RisingLine(POINT3D *pPosi , char *FileName , int Size, int ContinueTime , int Range , int Count , int SpeedY);


int AssaParticle_RisingRotateLine(POINT3D *pPosi , char *FileName , int ContinueTime , int Range , int Count , int SpeedY);


int AssaParticle_RisingRotateLinePower(POINT3D *pPosi , char *FileName,int Range ,int Speed );


int AssaParticle_Wave(POINT3D *pPosi , char *FileName ,int Size);


int AssaParticle_Light(POINT3D *pPosi , char *FileName ,int Size , int Height , int Time);


int AssaParticle_Spread(POINT3D *pPosi , char *FileName );


int AssaParticle_WideFace(POINT3D *pPosi , char *FileName , int Size);


int AssaParticle_Gather(POINT3D *pPosi , char *FileName ,int Range , int Speed ,int Num);


int AssaParticle_RotateGather(POINT3D *pPosi , char *FileName , int Num);


int AssaParticle_BALLLIGHT_GATHER(POINT3D *pPosi , char *FileName );


int AssaParticle_BALLLIGHT_ROTATE(POINT3D *pPosi , char *FileName ,int Range , int Speed);


int AssaParticle_RisingParticleContinue(POINT3D *pPosi , char *FileName ,int Size ,int Range , int SpeedY);


int AssaParticle_RotateWide(POINT3D *pPosi , char *FileName ,int Range , int SpeedY );


int AssaParticle_Wide(POINT3D *pPosi , char *FileName ,int Num , int Time);


int AssaParticle_BombGather(cASSAEFFECT *pEffect);


int AssaParticle_Area_Particle(POINT3D *Posi , char *FileName , int Range , int Time);


int AssaParticle_SpecialHit(POINT3D *pPosi , int Time); 


int AssaParticle_After_Image(POINT3D *Posi , char *FileName , int Range , int Time);


int AssaParticle_Piercing(cASSAEFFECT *pEffect);


int AssaParticle_Piercing_Aura(cASSAEFFECT *pEffect);


int AssaParticle_SpecialHit2(POINT3D *pPosi , int Time);


int AssaParticle_Windy(cASSAEFFECT *pEffect);


int AssaParticle_Holy_Reflection(cASSAEFFECT *pEffect);
#endif
