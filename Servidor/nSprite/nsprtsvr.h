#ifndef _NSPRTSVR_H_
#define _NSPRTSVR_H_

#define NSPRITE_OK	0x0	
#define VERSION_OLD	0x1	
#define EXIST_CHEAT	0x2	

void __stdcall InitNSprtsvr();
DWORD __stdcall ParseNSpriteVersion(DWORD dwVersion);

#endif
