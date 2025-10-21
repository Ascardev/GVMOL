#define	_LANGUAGE_BRAZIL
#define	_LANGUAGE_BRAZIL_FIELDLEVEL

#if defined (_LOG_)
#include "stdio.h"
#define MAKELOG(description)					\
{												\
	FILE *fpc_log = NULL;						\
	fpc_log = fopen(szLOG_FILENAME,"a+t");		\
	if( fpc_log != NULL )						\
	{											\
		fprintf(fpc_log,"\n %s",(description)); \
		fclose(fpc_log);						\
		fpc_log = NULL;							\
	}											\
}
#else
#define MAKELOG(desciption)
#endif

#ifdef _LANGUAGE_VEITNAM
#define	_LANGUAGE_WINDOW
#define	LOG_THE_PK
#else
#ifdef _LANGUAGE_ENGLISH
#define	_LANGUAGE_WINDOW
#else
#ifdef	_LANGUAGE_CHINESE
#define	_LANGUAGE_WINDOW
#else

#endif
#endif
#endif

#ifdef	_LANGUAGE_PHILIPIN
#define _DEATH_PANALTY
#endif

#define	ATTACK_RATE		70
#define	DEFENSE_RATE	80

#ifdef	_LANGUAGE_CHINESE
#define	_IME_ACTIVE
#endif

#define	_NEW_PARTRADE

#define	_WINMODE_DEBUG

#define	_PLAY_MORYON

#ifdef	_LANGUAGE_CHINESE
#define	_PACKET_PASS_XOR	0xAE
#endif

#ifdef	_LANGUAGE_TAIWAN
#define	_PACKET_PASS_XOR	0xCA
#endif

#ifdef	_LANGUAGE_ENGLISH
#define	_PACKET_PASS_XOR	0x5E
#endif

#ifdef	_LANGUAGE_BRAZIL
#define	_PACKET_PASS_XOR	0x6E
#endif

#ifdef	_LANGUAGE_ARGENTINA
#define	_PACKET_PASS_XOR	0x7A
#endif

#ifdef	_LANGUAGE_THAI
#define	_PACKET_PASS_XOR	0x6A
#endif

#define	_MODE_EXP64

#define	_SECURITY_UPDATE

#ifdef	_LANGUAGE_ENGLISH
#ifndef	_LANGUAGE_PHILIPIN
#endif
#define _QUEST_CHAOS_WING
#define _ON_PRIVATE_SHOP
#define _LANGUAGE_ENGLISH_NEXTUP
#define	_ON_MAP
#define	_ON_PET
#define	_CUSTOM_FONT
#endif

#ifdef	_LANGUAGE_CHINESE
#define _QUEST_CHAOS_WING
#define _ON_PRIVATE_SHOP
#define _LANGUAGE_ENGLISH_NEXTUP
#define	_ON_MAP
#define	_ON_PET
#endif

#ifdef	_LANGUAGE_THAI
#define _LANGUAGE_ENGLISH_NEXTUP
#define	_ON_MAP
#define _ON_PRIVATE_SHOP
#define	_ON_PET
#define _QUEST_CHAOS_WING
#define	_CUSTOM_FONT
#endif

#ifdef	_LANGUAGE_JAPANESE
#define _LANGUAGE_ENGLISH_NEXTUP
#define _QUEST_CHAOS_WING
#define	_ON_MAP
#define _ON_PRIVATE_SHOP
#define	_ON_PET
#endif

#ifdef	_LANGUAGE_KOREAN
#define _LANGUAGE_ENGLISH_NEXTUP
#define _QUEST_CHAOS_WING
#define	_ON_MAP
#define _ON_PRIVATE_SHOP
#define	_ON_PET
#endif

#ifdef	_LANGUAGE_BRAZIL
#define _LANGUAGE_ENGLISH_NEXTUP

#define	_ON_MAP
#define _ON_PRIVATE_SHOP
#define	_ON_PET
#endif

#ifdef	_LANGUAGE_ARGENTINA
#define _LANGUAGE_ENGLISH_NEXTUP

#define	_ON_MAP
#define _ON_PRIVATE_SHOP
#define	_ON_PET
#endif

#ifdef _LANGUAGE_VEITNAM
#define _LANGUAGE_ENGLISH_NEXTUP
#define _QUEST_CHAOS_WING
#define _ON_PRIVATE_SHOP
#define	_ON_MAP
#define	_ON_PET
#endif
