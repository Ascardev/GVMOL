
struct	sITEM_CREATE {
	DWORD	Head;			
	DWORD	dwVersion;		
	DWORD	dwTime;			
	DWORD	dwChkSum;		
};

struct sITEM_SPECIAL {

	
	int		Add_Absorb;				
  	int     Add_Defence;			
	float   Add_fSpeed;				
	float   Add_fBlock_Rating;		
	int     Add_Attack_Speed;		
	int     Add_Critical_Hit;		
	int     Add_Shooting_Range;		
	float   Add_fMagic_Mastery;     
	short	Add_Resistance[8];		

	

	short	Lev_Attack_Resistance[8];	
	int		Lev_Mana;				
	int		Lev_Life;				
	int     Lev_Attack_Rating;		
	short	Lev_Damage[2];			

	int		Per_Mana_Regen;			
	int		Per_Life_Regen;			
	int		Per_Stamina_Regen;		

	

	DWORD	dwTemp[32];
};


struct sITEMINFO{

	DWORD	dwSize;						
	
	sITEM_CREATE	ItemHeader;			

	short	Durability[2];				

	

	


	DWORD	CODE;				
	char	ItemName[32];		

	


	int     Weight;				
	int     Price;				

	
	int		Index;				
	int		Counter;			
	

	
	short	Resistance[8];		
	

	int		Sight;				

	DWORD	Temp0;

	


	short	Damage[2];			
	int     Shooting_Range;		
	int     Attack_Speed;		
	int     Attack_Rating;		
	int     Critical_Hit;		

	



	int		Absorb;				
  	int     Defence;			
	float   fBlock_Rating;		

	


	float     fSpeed;				

	



	int		Potion_Space;		
	
	
	float   fMagic_Mastery;     
	float   fMana_Regen;		
	float   fLife_Regen;		
	float   fStamina_Regen;	    
	float   fIncrease_Life;     
	float   fIncrease_Mana;     
	float   fIncrease_Stamina;  

	

	


	int     Level;				
	int     Strength;			
	int     Spirit;				
	int     Talent;				
	int     Dexterity;			
	int     Health;				

	


	short   Mana[2];            
	short   Life[2];            
	short   Stamina[2];         
	

	


	int		Money;				


	DWORD	dwTemp1[8];			

	DWORD	DispEffect;			

	



	DWORD			JobCodeMask;		
	sITEM_SPECIAL	JobItem;			

	DWORD	dwTemp[16];			
};


