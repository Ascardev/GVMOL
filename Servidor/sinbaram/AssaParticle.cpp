




	

#include "sinLinkHeader.h"
#include "..\\HoBaram\\HoNewParticleLinkHeader.h" 


	
#define ASSA_PARTICLE_BELT				0x50000000 
#define ASSA_PARTICLE_ROTATE_GATHER		0x50000001 
#define ASSA_PARTICLE_ROTATE_WIDE		0x50000002 
#define ASSA_PARTICLE_SPECIAL_HIT		0x50000003 
#define ASSA_PARTICLE_PIERCING			0x50000004 
#define ASSA_PARTICLE_WINDY				0x50000005 



	
int sinAssaParticleKeyDown() 
{
	
	

	POINT3D Posi = {lpCurPlayer->pX,lpCurPlayer->pY,lpCurPlayer->pZ};   

	if(sinGetKeyClick('9')){
		
		

	}
	





	return TRUE;
}



	
void sinAssaParticleProcess(cASSAEFFECT *pEffect)
{

	D3DXVECTOR3 TempVector;

	
	switch(pEffect->CODE){     
		case ASSA_PARTICLE_WINDY:
			pEffect->FACEY += 3;
			if(pEffect->Time < 10)
				pEffect->Size.w += 400;
			else
				pEffect->Size.w -= 400;

		break;
		case ASSA_PARTICLE_ROTATE_GATHER: 
			pEffect->RDistance.z -= 256;
		break;
		case ASSA_PARTICLE_ROTATE_WIDE:
			pEffect->RDistance.z += 32;
		break;
		case ASSA_PARTICLE_SPECIAL_HIT:  
			if(pEffect->ActionIndex[0] == 1){  
				pEffect->FACEY += 3;
				if(pEffect->Time < 10)
					pEffect->Size.w += 400;
				else
					pEffect->Size.w -= 400;

			}
			if(pEffect->ActionIndex[1] == 1){ 
				pEffect->Size.w +=150;
				pEffect->Size.h +=150;

			}
			if(pEffect->ActionIndex[2] ==1){
				pEffect->Gravity -=2;
				pEffect->Posi.y += pEffect->Gravity;

			}
			if(pEffect->ActionIndex[3] ==1){
				pEffect->Size.w +=50;
				pEffect->Size.h +=50;

			}
		break;
		case ASSA_PARTICLE_PIERCING:
			
			TempVector.x = pEffect->Posi.x; 
			TempVector.y = pEffect->Posi.y;
			TempVector.z = pEffect->Posi.z;
			g_NewParticleMgr.SetPos(pEffect->Face.MatNum, TempVector);
			if(pEffect->Time>= pEffect->Max_Time-11)
				g_NewParticleMgr.SetStop(pEffect->Face.MatNum);
			if(pEffect->Time < (pEffect->Max_Time-11)) 
				AssaParticle_Wave(&pEffect->Posi,"water3.tga",pEffect->Time);

		break;
	}

	
	for(int i = 0 ; i < 10 ; i++){ 
		if(pEffect->MOVECODE_Time[i]){
			if(pEffect->Time == pEffect->MOVECODE_Time[i]){
				pEffect->MOVECODE = pEffect->MOVECODE_List[i];
			}
		}
	}
}


	
int AssaParticle_SpecialHit(POINT3D *pPosi , int Time)
{
	
	for(int i = 0 ; i < 4 ; i++){                                                     
		Assa = SetAssaEffect(90,"flare.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(7000,10000); 
		cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->ActionIndex[0] = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->Time = -5*i+Time;

	}	
	
	for(int i = 0 ; i < 4 ; i++){                  
		Assa = SetAssaEffect(90,"flare.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(10000,15000);
		cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ActionIndex[0] = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->Time = -5*i+Time;
		cAssaEffect[Assa]->ZposiFlag = 1;

		
	}	

	
	for(int i = 0 ; i < 2 ; i++){                
		Assa = SetAssaEffect(70,"water2.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(3000,3001);
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->ActionIndex[1] = 1;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->Time = (i*-10)+Time;
		cAssaEffect[Assa]->ZposiFlag = 1;

	}	
	
	
	for(int i = 0 ; i < 1 ; i++){                      
		Assa = SetAssaEffect(60,"Light01.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(10000,10001);
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->Time = Time;

	}	

	
	for(int i = 0 ; i < 15 ; i++){        
		Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(128,256);
		cAssaEffect[Assa]->ActionIndex[2] =1;
		cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
		cAssaEffect[Assa]->Gravity = 50;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->ZposiFlag = 1;
	}	

	for(int i = 0 ; i < 15 ; i++){         
		Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(128,256);
		cAssaEffect[Assa]->ActionIndex[2] =1;
		cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
		cAssaEffect[Assa]->Gravity = 50;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->ZposiFlag = 1;
	}	


	return TRUE;
}
int AssaParticle_SpecialHit2(POINT3D *pPosi , int Time) 
{
	
	
	for(int i = 0 ; i < 6 ; i++){                                                      
		Assa = SetAssaEffect(50,"flare.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(10000,20000); 
		cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ZposiFlag = 1;
		cAssaEffect[Assa]->ActionIndex[0] = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->Time = -5*i+Time;


	}	
	
	for(int i = 0 ; i < 6 ; i++){                   
		Assa = SetAssaEffect(50,"flare.tga",0,pPosi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(15000,25000);
		cAssaEffect[Assa]->Size.h = GetRandomPos(500,1200); 
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->ActionIndex[0] = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->Time = -5*i+Time;
		cAssaEffect[Assa]->ZposiFlag = 1;

		
	}	

	
	for(int i = 0 ; i < 2 ; i++){                    
		Assa = SetAssaEffect(70,"water2.tga",0,pPosi,1500);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(20000,10001);
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->ActionIndex[1] = 1;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->Time = (i*-10)+Time;
		cAssaEffect[Assa]->FACE_TYPE  = ASSAFACE_WORLD;
		

	}	
	
	
	for(int i = 0 ; i < 1 ; i++){                      
		Assa = SetAssaEffect(60,"Light01.tga",0,pPosi,1500);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(20000,10001);
		cAssaEffect[Assa]->FACEY  = GetRandomPos(0,4096);
		cAssaEffect[Assa]->ActionIndex[3] = 1;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->FACE_TYPE  = ASSAFACE_WORLD;
		
		cAssaEffect[Assa]->Time = Time;

	}	

	
	for(int i = 0 ; i < 30 ; i++){        
		Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 150;
		cAssaEffect[Assa]->Face.b = 0;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(256,256*2);
		cAssaEffect[Assa]->ActionIndex[2] =1;
		cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
		cAssaEffect[Assa]->Gravity = 50;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->ZposiFlag = 1;
	}	

	for(int i = 0 ; i < 30 ; i++){         
		Assa = SetAssaEffect(100,"flare.tga",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = GetRandomPos(500,1300);
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Face.r = 255;
		cAssaEffect[Assa]->Face.g = 200;
		cAssaEffect[Assa]->Face.b = 50;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = GetRandomPos(256,256*2);
		cAssaEffect[Assa]->ActionIndex[2] =1;
		cAssaEffect[Assa]->Time = GetRandomPos(-20,0)+Time;
		cAssaEffect[Assa]->Gravity = 50;
		cAssaEffect[Assa]->CODE   = ASSA_PARTICLE_SPECIAL_HIT;
		cAssaEffect[Assa]->ZposiFlag = 1;
	}	


	return TRUE;
}



	
int AssaParticle_Stune(smCHAR *pChar)
{
	int Count = 0;
	for(int j = 0 ; j < 3 ; j++){   
		for(int i = 0 ; i < 4 ; i++){           
			Assa = SetAssaEffect(1000,"Star.tga",pChar,0,pChar->PatHeight);                
			cAssaEffect[Assa]->MOVECODE = ASSA_ROTATE | ASSA_CHAR_POSI;
			Count++;
			cAssaEffect[Assa]->RAngleSpeed = 16*3;
			cAssaEffect[Assa]->Size.h = 500+(i*220);
			cAssaEffect[Assa]->Size.w = 500+(i*220);
			cAssaEffect[Assa]->Face.Transparency = 255 - (i*25);
			AssaGetCirclePosi(cAssaEffect[Assa],256*8,16*2*(Count*6)+(j*200*3));
		}
	}
	
	return TRUE;
}


	
int AssaMakeCircle(POINT3D *pPosi , char *FileName , int Radius)
{
	int Temp = Radius/256;  
	Assa = SetAssaEffect(500,FileName,0,pPosi,3000);                         
	cAssaEffect[Assa]->Size.w = 1000;
	cAssaEffect[Assa]->RDistance.z = Radius;

	for(int i = 0 ; i < Temp ; i++){     
		cAssaEffect[Assa]->RAngle += 15*Temp;
		cAssaEffect[Assa]->RPosi.x  = GetCos[ cAssaEffect[Assa]->RAngle&ANGCLIP ] + Radius*GetSin[ cAssaEffect[Assa]->RAngle&ANGCLIP ];     
		cAssaEffect[Assa]->RPosi.z  = -GetSin[ cAssaEffect[Assa]->RAngle&ANGCLIP ] + Radius*GetCos[ cAssaEffect[Assa]->RAngle&ANGCLIP ];
		cAssaEffect[Assa]->RPosi.x >>=16;
		cAssaEffect[Assa]->RPosi.z >>=16;
		cAssaEffect[Assa]->Posi.x =  cAssaEffect[Assa]->CenterPosi.x + cAssaEffect[Assa]->RPosi.x;
		cAssaEffect[Assa]->Posi.z =  cAssaEffect[Assa]->CenterPosi.z + cAssaEffect[Assa]->RPosi.z;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->AddData(&cAssaEffect[Assa]->Posi);
		cAssaEffect[Assa]->Type = ASSATYPE_CIRCLE;
		
	}

	return Assa;
}



	
int AssaParticle_RisingBelt(POINT3D *pPosi ,char *FileName,int ContinueTime , int SpeedY )
{ 

	int Temp = 1; 
	for(int i = 0 ; i < ContinueTime * 7 ; i++){               
		if((i%7)!=0)continue; 
		Assa = SetAssaEffect(250-(SpeedY/2),FileName,0,pPosi,0);                 
		cAssaEffect[Assa]->MOVECODE = ASSA_ANGLE_ROTATE | ASSA_MOVE;
		if(Temp == -1 )Temp = 1;
		else Temp = -1; 
		cAssaEffect[Assa]->ARotateSpeed.y = GetRandomPos(30,35)*Temp; 
		cAssaEffect[Assa]->MoveSpeed.y = SpeedY;
		cAssaEffect[Assa]->AniCount = rand()%5+5;
		cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9);
	}
	return TRUE; 
}


	
int AssaParticle_RisingParticle(POINT3D *pPosi , char *FileName ,int Size ,  int ContinueTime , int Range , int Count , int SpeedY)
{
	for(int i = 0; i < ContinueTime*7 ; i++){              
		for(int j = 0; j < Count ; j++){    
		  Assa = SetAssaEffect(350-(SpeedY/2),FileName,0,pPosi,0);   
		  AssaGetAniFileMat(cAssaEffect[Assa]);
		  cAssaEffect[Assa]->AniDelayTime = GetRandomPos(4,10);
		  cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
		  cAssaEffect[Assa]->AniReverse = 1;
		  cAssaEffect[Assa]->Size.w = GetRandomPos(Size-500,Size+500);
		  cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
		  AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		  cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9)-j;

		}
	}
	return TRUE;
}



	
int AssaParticle_RisingLine(POINT3D *pPosi , char *FileName , int Size, int ContinueTime , int Range , int Count , int SpeedY)
{
	for(int i = 0; i < ContinueTime*7 ; i++){                       
		for(int j = 0; j < Count ; j++){    
		  Assa = SetAssaEffect(350-(SpeedY/2),FileName,0,pPosi,0);   
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		  cAssaEffect[Assa]->ScalePosi.y = GetRandomPos(Size*100,(Size+1)*100);
		  cAssaEffect[Assa]->Size.w = GetRandomPos(Size-500,Size+500);
		  cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
		  cAssaEffect[Assa]->Posi.y -= 50*Size; 
		  AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
		  cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9)-j;
		}
	}
	return TRUE;
}



	
int AssaParticle_RisingRotateLine(POINT3D *pPosi , char *FileName , int ContinueTime , int Range , int Count , int SpeedY)
{ 
	int Temp =1;
	for(int i = 0; i < ContinueTime*7 ; i++){                            
		for(int j = 0; j < Count ; j++){       
		  Assa = SetAssaEffect(350-(SpeedY/2),FileName,0,pPosi,0);   
		  cAssaEffect[Assa]->Size.w = 1000; 
		  cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
		  AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE;
		  if(Temp > 0 )Temp = -1;
		  else Temp = 1;
		  cAssaEffect[Assa]->RAngleSpeed = 50*Temp;
		  cAssaEffect[Assa]->RDistance.z = 256*16;
		  cAssaEffect[Assa]->Time = GetRandomPos(-10*i,-i*9)-j;
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		  cAssaEffect[Assa]->cAssaTrace->SetLength(50); 
		}
	}
	return TRUE;
}



	
int AssaParticle_Wave(POINT3D *pPosi , char *FileName ,int Size)
{
	
	
	for(int i = 0; i < 1 ; i++){                  
		Assa = SetAssaEffect(GetRandomPos(31-Size,32-Size),"star05B_03.bmp",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = 4000;
		cAssaEffect[Assa]->ReSize.w = 600;
		cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
		cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
		cAssaEffect[Assa]->FACEY = GetRandomPos(0,4096);

		
		cAssaEffect[Assa]->Face.Transparency = 255-(Size*8);
	}
	
	for(int i = 0; i < 1 ; i++){            
		Assa = SetAssaEffect(GetRandomPos(31-Size,32-Size),"twist.bmp",0,pPosi,0);       
		cAssaEffect[Assa]->Size.w = 1000;
		cAssaEffect[Assa]->ReSize.w = 600;
		cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
		cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
		cAssaEffect[Assa]->FACEY = GetRandomPos(0,4096);
		cAssaEffect[Assa]->Face.Transparency = 255-(Size*8);
		
	}

	return TRUE;
}



	
int AssaParticle_Light(POINT3D *pPosi , char *FileName ,int Size , int Height , int Time)
{
	Assa = SetAssaEffect(40,FileName,0,pPosi,Height);           
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = 25;
	cAssaEffect[Assa]->Size.w = Size;
	cAssaEffect[Assa]->ReSize.w = 600;
	cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;
	cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
	cAssaEffect[Assa]->Time = Time;
	cAssaEffect[Assa]->MOVECODE_List[0] = ASSA_DECRESIZE;
	cAssaEffect[Assa]->MOVECODE_Time[0] = 25;

	return TRUE;
}



	
int AssaParticle_RisingRotateLinePower(POINT3D *pPosi , char *FileName,int Range ,int Speed )
{ 
	
	int Temp =1;
	for(int i = 0; i < 7 ; i++){                                   
		for(int j = 0; j < 3 ; j++){           
		  Assa = SetAssaEffect(350-(Speed/2),FileName,0,pPosi,0);   
		  cAssaEffect[Assa]->Size.w = 1000; 
		  cAssaEffect[Assa]->MoveSpeed.y = Speed;
		  AssaGetCirclePosi(cAssaEffect[Assa],Range*4,GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE;
		  if(Temp > 0 )Temp = -1;
		  else Temp = 1;
		  cAssaEffect[Assa]->RAngleSpeed = 100*Temp;
		  cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4)-j;
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		  cAssaEffect[Assa]->cAssaTrace->SetLength(50); 
		  cAssaEffect[Assa]->NotFadeIn = 1;
		  
		}
	}
	return TRUE;
}


	
int AssaParticle_Spread(POINT3D *pPosi , char *FileName ) 
{
	Assa = SetAssaEffect(70,FileName,0,pPosi,0);                   
	cAssaEffect[Assa]->Size.w = 500;  
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_SPREAD;
	cAssaEffect[Assa]->RAngle = rand()%4096;
	cAssaEffect[Assa]->RDistance.z = 64;
	cAssaEffect[Assa]->Gravity = 10;
	cAssaEffect[Assa]->MoveSpeed.y = 50;
	cAssaEffect[Assa]->NotFadeIn = 1;

	return TRUE;

}



	
int AssaParticle_WideFace(POINT3D *pPosi , char *FileName , int Size)
{
	Assa = SetAssaEffect(40,FileName,0,pPosi,0);                    
	cAssaEffect[Assa]->Size.w = Size; 
	cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_WORLD;
	cAssaEffect[Assa]->MOVECODE = ASSA_INCRESIZE;
	cAssaEffect[Assa]->ReSize.w = 200;
	cAssaEffect[Assa]->ReSize.h = cAssaEffect[Assa]->ReSize.w;

	return TRUE;
}


	
int AssaParticle_Gather(POINT3D *pPosi , char *FileName ,int Range , int Speed ,int Num)
{
	
	for(int j = 0; j < Num ; j++){       
		Assa = SetAssaEffect(300,FileName,0,pPosi,0);            
		cAssaEffect[Assa]->Size.w = 1000;  
		cAssaEffect[Assa]->GatherSpeed = 20;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_GATHER;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(100); 
		cAssaEffect[Assa]->RDistance.z = GetRandomPos(Range*16,Range*16*2);
		cAssaEffect[Assa]->RAngle = GetRandomPos(0,4096);
		cAssaEffect[Assa]->StartPosi.z = cAssaEffect[Assa]->RDistance.z;
		AssaSetStartPosi(cAssaEffect[Assa]);
	}
	return TRUE;
}


	
int AssaParticle_RotateGather(POINT3D *pPosi , char *FileName , int Num)
{
	for(int i = 0; i < Num ; i++){           
		Assa = SetAssaEffect(120,FileName,0,pPosi,0);                 
		cAssaEffect[Assa]->Size.w = 1000;    
		cAssaEffect[Assa]->GatherSpeed = 30;
		cAssaEffect[Assa]->MOVECODE = ASSA_ROTATE;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->cAssaTrace->SetLength(70); 
		cAssaEffect[Assa]->RDistance.z = GetRandomPos(256*16*3 ,256*16*3);
		cAssaEffect[Assa]->RAngle = GetRandomPos(0,4096);
		cAssaEffect[Assa]->RAngleSpeed = GetRandomPos(100,150);
		cAssaEffect[Assa]->AddHeight = GetRandomPos(0,15000);
		cAssaEffect[Assa]->CODE = ASSA_PARTICLE_ROTATE_GATHER;

	}

	return TRUE;
}



	
int AssaParticle_BALLLIGHT_GATHER(POINT3D *pPosi , char *FileName )
{
	Assa = SetAssaEffect(60,FileName,0,pPosi,0);                    
	cAssaEffect[Assa]->Size.w = 500;  
	cAssaEffect[Assa]->GatherSpeed = 30;
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_GATHER;
	
	
    
	cAssaEffect[Assa]->StartPosi.z = 256*8;
	AssaSetStartPosi(cAssaEffect[Assa]);
	return TRUE;
}



	
int AssaParticle_BALLLIGHT_ROTATE(POINT3D *pPosi , char *FileName ,int Range , int Speed)
{
	Assa = SetAssaEffect(50,FileName,0,pPosi,0);                           
	cAssaEffect[Assa]->Size.w = 500;    
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = GetRandomPos(10,15);
	cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_RANDOM_ROTATE;
	
	
	cAssaEffect[Assa]->Angle.x = GetRandomPos(0,4096);
	cAssaEffect[Assa]->Angle.y = GetRandomPos(0,4096);
	cAssaEffect[Assa]->MoveSpeed.z = Range;
	cAssaEffect[Assa]->RAngleSpeed = Speed;

	return TRUE;
}


	
int AssaParticle_RisingParticleContinue(POINT3D *pPosi , char *FileName ,int Size ,int Range , int SpeedY)
{ 
	Assa = SetAssaEffect(GetRandomPos(50,70),FileName,0,pPosi,0);   
	AssaGetAniFileMat(cAssaEffect[Assa]);
	cAssaEffect[Assa]->AniDelayTime = cAssaEffect[Assa]->Max_Time/7;
	cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
	cAssaEffect[Assa]->Size.w = GetRandomPos(Size-200,Size+200);
	cAssaEffect[Assa]->MoveSpeed.y = rand()%50+SpeedY;
	AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,Range*10),GetRandomPos(0,4096));
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
	cAssaEffect[Assa]->NotFadeIn = 1;

	return TRUE;
}


	
int AssaParticle_RotateWide(POINT3D *pPosi , char *FileName ,int Range , int SpeedY )
{
	int Temp =1;
	for(int i = 0; i < 3 ; i++){                                    
		for(int j = 0; j < 3 ; j++){           
		  Assa = SetAssaEffect(120,FileName,0,pPosi,0);      
		  cAssaEffect[Assa]->Size.w = 1000; 
		  cAssaEffect[Assa]->MoveSpeed.y = SpeedY;
		  AssaGetCirclePosi(cAssaEffect[Assa],Range*4,GetRandomPos(0,4096));
		  cAssaEffect[Assa]->MOVECODE = ASSA_MOVE | ASSA_ROTATE;
		  if(Temp > 0 )Temp = -1;
		  else Temp = 1;
		  cAssaEffect[Assa]->RAngleSpeed = 100*Temp;
		  cAssaEffect[Assa]->Time = GetRandomPos(-5*i,-i*4)-j;
		  cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		  cAssaEffect[Assa]->cAssaTrace->SetLength(50); 
		  cAssaEffect[Assa]->NotFadeIn = 1;
		  cAssaEffect[Assa]->CODE = ASSA_PARTICLE_ROTATE_WIDE; 
		   
		}
	}

	return TRUE;
}


	
int AssaParticle_Wide(POINT3D *pPosi , char *FileName ,int Num , int Time)
{
	for(int i = 0 ; i < Num ; i++){
		
		Assa = SetAssaEffect(100,FileName,0,pPosi,0);             
		cAssaEffect[Assa]->Size.w = 1000; 
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_ANGLE_SPEED;
		cAssaEffect[Assa]->MoveSpeed.z = 400;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_TRACE;
		cAssaEffect[Assa]->StartPosi.z = 256*2;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->cAssaTrace->SetLength(50); 
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->Time = Time;


		
		










	}
	return TRUE;
}



	
int AssaParticle_BombGather(cASSAEFFECT *pEffect)
{
	for(int i = 0 ; i < 20 ; i++){
		Assa = SetAssaEffect(100,pEffect->szFileName,0,&pEffect->Posi,0);                   
		cAssaEffect[Assa]->Size.w = 1000;  
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_SPREAD;
		cAssaEffect[Assa]->RAngle = rand()%4096;
		cAssaEffect[Assa]->RDistance.z = 64;
		cAssaEffect[Assa]->Gravity = 10;
		cAssaEffect[Assa]->MoveSpeed.y = 50;
		cAssaEffect[Assa]->NotFadeIn = 1;
		cAssaEffect[Assa]->MOVECODE_List[0] = ASSA_MOVE_GATHER;
		cAssaEffect[Assa]->MOVECODE_Time[0] = 70;
		cAssaEffect[Assa]->GatherSpeed = 20;
		cAssaEffect[Assa]->CenterPosi = pEffect->CenterPosi;

	}
	return TRUE;
}



	
int AssaParticle_Area_Particle(POINT3D *Posi , char *FileName , int Range , int Time)
{
	for(int i = 0 ; i < 10 ; i++){ 
		Assa = SetAssaEffect(100,FileName,0,Posi,0);                   
		cAssaEffect[Assa]->Size.w = 1000;  
		AssaGetAniFileMat(cAssaEffect[Assa]);
		cAssaEffect[Assa]->AniCount = GetRandomPos(0,cAssaEffect[Assa]->AniMaxCount);
		cAssaEffect[Assa]->AniReverse = 1;
		cAssaEffect[Assa]->AniDelayTime = GetRandomPos(4,8);
		cAssaEffect[Assa]->StartPosi.z = GetRandomPos(256,256*Range*2);
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Time = Time;
	}
	return TRUE;
}



	
int AssaParticle_After_Image(POINT3D *Posi , char *FileName , int Range , int Time)
{
	
	










	
	for(int i = 0 ; i < 3 ; i++){              
		Assa = SetAssaEffect(10,"flare.tga",0,Posi,0);      
		cAssaEffect[Assa]->Size.w = GetRandomPos(6000,7000); 
		cAssaEffect[Assa]->Size.h = GetRandomPos(300,500); 
		cAssaEffect[Assa]->FACEY  = (i+1)*(4096/6);
		cAssaEffect[Assa]->NotFadeIn = 1;
		
		cAssaEffect[Assa]->Face.r = 0;
		cAssaEffect[Assa]->Face.g = 255;
		cAssaEffect[Assa]->Face.b = 255;
	}

	return TRUE;
}



	
int AssaParticle_Piercing(cASSAEFFECT *pEffect)
{
	POINT3D TempPosi; 
	
	AssaSearchWeaponPos(pEffect->pChar,&pEffect->Posi,1);           
	cAssaEffect[Assa]->Face.MatNum = g_NewParticleMgr.Start("TwistJavelin1", pEffect->Posi); 

	
	GetMoveLocation(  0, 0,256*128 , pEffect->Angle.x, ((pEffect->pChar->Angle.y&ANGCLIP)+ANGLE_180)&ANGCLIP, 0 );
	TempPosi.x = pEffect->Posi.x+GeoResult_X;
	TempPosi.y = pEffect->Posi.y;
	TempPosi.z = pEffect->Posi.z+GeoResult_Z;

	pEffect->MOVECODE = ASSA_MOVE;
	pEffect->MoveSpeed.x = (pEffect->Posi.x - TempPosi.x)/20;
	pEffect->MoveSpeed.z = (pEffect->Posi.z - TempPosi.z)/20;
	pEffect->CODE = ASSA_PARTICLE_PIERCING; 
	return TRUE;
}



	
int AssaParticle_Piercing_Aura(cASSAEFFECT *pEffect)
{

	for(int i = 0; i < 100 ; i++){            
		Assa = SetAssaEffect(100,"line.bmp",0,&pEffect->CenterPosi,0);              
		cAssaEffect[Assa]->Size.w = 250;
		cAssaEffect[Assa]->GatherSpeed = 40;
		cAssaEffect[Assa]->MOVECODE = ASSA_MOVE_GATHER;
		cAssaEffect[Assa]->FACE_TYPE = ASSAFACE_SCALE;
		cAssaEffect[Assa]->RDistance.z = GetRandomPos(256*16,256*16*2);
		cAssaEffect[Assa]->RAngle = GetRandomPos(0,4096);
		cAssaEffect[Assa]->StartPosi.z = cAssaEffect[Assa]->RDistance.z;
		AssaSetStartPosi(cAssaEffect[Assa]);
		cAssaEffect[Assa]->Time = GetRandomPos(0,-300);

		
		GetMoveLocation(  cAssaEffect[Assa]->StartPosi.x, cAssaEffect[Assa]->StartPosi.y,cAssaEffect[Assa]->StartPosi.z*2 , cAssaEffect[Assa]->Angle.x, cAssaEffect[Assa]->Angle.y, 0 );
		cAssaEffect[Assa]->ScalePosi.x = GeoResult_X/2;
		cAssaEffect[Assa]->ScalePosi.y = GeoResult_Y/2;
		cAssaEffect[Assa]->ScalePosi.z = GeoResult_Z/2;

	}

	return TRUE;
} 


	
int AssaParticle_Windy(cASSAEFFECT *pEffect)
{
	float Temp = ((float)pEffect->Time-45.0f)/15.0f;              
	
	Assa = SetAssaEffect(30,"star05Y_03.bmp",pEffect->pChar,0,0);                               
	AssaSearchWeaponPos(pEffect->pChar,&cAssaEffect[Assa]->Posi,Temp);            
	
	cAssaEffect[Assa]->Size.w = 2000; 
	cAssaEffect[Assa]->Face.Transparency = 100;
	
	
	
	

	
	








	

	if((pEffect->Time % 3) == 0 )
		AssaParticle_RisingParticleContinue(&cAssaEffect[Assa]->Posi,"star01Y_02.bmp",300,128,GetRandomPos(20,80));
	
	
	

	return TRUE;
}



	
int AssaParticle_Holy_Reflection(cASSAEFFECT *pEffect)
{
	
	Assa = SetAssaEffect(GetRandomPos(80,100),"star01M_04.bmp",0,&pEffect->Posi,0);     
	AssaSearchWeaponPos(pEffect->pChar,&cAssaEffect[Assa]->Posi,1);            
	cAssaEffect[Assa]->Size.w = GetRandomPos(500,1000);
	cAssaEffect[Assa]->MoveSpeed.y = rand()%50;
	AssaGetCirclePosi(cAssaEffect[Assa],GetRandomPos(0,64*10),GetRandomPos(0,4096));
	cAssaEffect[Assa]->MOVECODE = ASSA_MOVE;
	return TRUE;
}
