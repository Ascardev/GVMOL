#define _WIN32_WINNT    0x0501
#define _WIN32_WINDOWS  0x040A

#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <process.h>

#include "..\\resource.h"
#include "..\\smwsock.h"
#include "..\\socketserver.h"
#include "..\\smlib3d\\smd3d.h"
#include "..\\character.h"
#include "..\\fileread.h"
#include "..\\playmain.h"
#include "..\\field.h"
#include "..\\sinbaram\\sinlinkheader.h"
#include "..\\effectsnd.h"
#include "..\\sinbaram\\sinSkill_InfoIni.h"
#include "..\\record.h"
#include "..\playsub.h"
#include "..\\Firewall.h"

#include "gamesql.h"
#include "DllServer.h"

#include "..\\language.h"

#include "sinitem.h"

#include "ClientFuncPos.h"

#include "OnServer.h"
#include "svr_Damage.h"
#include "openlive.h"

#include "svrEventSpawn.h"

#include "svrEventGame.h"

#include "..\\damage.h"

#include "..\\cRestaureHandler.h"

#include "../RollDice.h"
#include "../IO/PacketReader.h"

#define CHAT_ANGERMONSTER_MAX		2
char* szAngerMonster[CHAT_ANGERMONSTER_MAX] = { "","" };
char* szMonsterFlagMsg = "";
#define		SERVER_DOWN_MSG_COUNT	2
char* szServerDownMsg[SERVER_DOWN_MSG_COUNT] = { "", "" };
char* szSeverDownCountMsg = "";
char* srMsg_Bl_01;
char* srMsg_Bl_02;
char* srMsg_BI_03;
char* srMsg_BI_04;
char* srMsg_Bl_100;
char* srMsg_Bl_1001;
char* srMsg_Bl_101;
char* srMsg_Bl_102;
char* srMsg_011;
char* srMsg_038;
char* srMsg_300;
char* srMsg_301;
char* srMsg_400;
char* srMsg_401;
char* srItem_BB;

char* srBlessCastle_LeagueMsg_01;
char* srBlessCastle_LeagueMsg_02;
char* srBlessCastle_LeagueMsg_03;
char* srBlessCastle_LeagueMsg_04;
char* srBlessCastle_LeagueMsg_05;

char* srMsg_StartUser_PresentItem;
char* srMsg_ThanksPolling;

char* szMiniMorif;
char* szWantedMorif;

char* szMon_FireCrystal;
char* szMon_LightningCrystal;
char* szMon_IceCrystal;
char* szMon_TowerCrystal;
char* szMon_Castledoor;

char* szMon_Curse_Soldier_A;
char* szMon_Curse_Soldier_B;
char* szMon_Curse_Soldier_C;
char* szMon_Castledoor_Soldier;

char* StateInitEvent1;
char* StateInitEvent2;
char* StateInitEvent3;
char* StateInitEvent4;
char* szEvent_HopeMsg_StateInit;

#include "..\Chinese\c_TimeLimit.h"

DWORD AwardTime = 0;

#ifdef	_LANGUAGE_KOREAN

char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif
#ifdef	_LANGUAGE_CHINESE

char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif

#ifdef	_LANGUAGE_JAPANESE

char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif

#ifdef _LANGUAGE_TAIWAN

char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif

#ifdef _LANGUAGE_ENGLISH
#ifdef _LANGUAGE_PHILIPIN

char* finehack_message = "http://update.netplay.ph/pstale/WarningMsg/warning.asp?id=%s&name=%s";
#else

char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif
#endif
#ifdef _LANGUAGE_VEITNAM

char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif
#ifdef _LANGUAGE_THAI

char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif
#ifdef _LANGUAGE_BRAZIL
char* finehack_message = "http://info.pristontale.com/blackWarning/warning.asp?id=%s&name=%s";
#endif

int LogOnThread_Count;
int	LogOnThread_Process;
int LogOnThread_ProcessTime;
int LogOnThread_Sucess;

char	szLastLogInID[64];
int		LastLogInResult = 0;

int rsRefreshConfig();

HFONT	hServerFont = 0;

int		Svr_DisplayMode = 0;

char* srEventMonName1 = "Á»ºñ";

#define	srCRISTAL_MAX		20
#define MARVELCRISTAL_MAX	8
#define srKIDMONSTER_MAX	1
#define srSOD_GUARD_MONSTER_MAX	5

extern int AgingEvento;
extern int AgingPrice;

struct srCRISTAL_MONSTER {
	char* szName;
	smCHAR_INFO* lpCharInfo;
	int	RndCount;
};

const char* szItemDrops[100]{
"Chaotic Armor",
"Chaotic Robe",
"Chaotic Shield",
"Bloody Soul",
"Chaotic Bracelets",
"Chaotic Gauntlets",
"Chaotic Boots",
"Chaotic Ring",
"Chaotic Amulet",
"Chaotic Sheltom",
"Malefic Earrings",
"Chaotic Axe",
"Chaotic Axe 1H",
"Chaotic Talon",
"Chaotic Hammer",
"Chaotic Staff",
"Chaotic Scythe",
"Chaotic Wand",
"Chaotic Bow",
"Chaotic Sword",
"Chaotic Sword 1H",
"Chaotic Javelin",
"Chaotic Daggers",
"Chaotic Phantom",
"Chaotic Fists",
"Bellum",
"Enigma",
"Bellum Force",
"Ordo",
"Ordo Force",
"Poção de UP 125-128",
"Poção de UP 128-132",
"Poção de UP 132-135",
};

static int rsSOD_CRYSTAL_GUARD_MONSTER_POS[7][3] = {
		{33,		34560,		-25785},
		{33,		34200,		-26080},
		{33,		34900,		-26080},
		{33,		33745,		-28575},
		{33,		35345,		-28575},
		{33,		34135,		-30575},
		{33,		34975,		-30575}
};

struct srOPENKID_MONSTER {
	char* szParentMonName;
	char* szChildMonName;
	int	mon_Num;
	int mon_Count;
};

srOPENKID_MONSTER srOpenKidMonster[srKIDMONSTER_MAX] = {
		{szWantedMorif,		szMiniMorif,			0,		3}
};

srOPENKID_MONSTER srOpenSODCrystalGuardMonster[srSOD_GUARD_MONSTER_MAX] = {
		{szMon_FireCrystal ,		szMon_Curse_Soldier_A,		100,		10},
		{szMon_IceCrystal,			szMon_Curse_Soldier_B,		100,		10},
		{szMon_LightningCrystal,	szMon_Curse_Soldier_C,		100,		10},
		{szMon_TowerCrystal,		szMon_Curse_Soldier_B,		100,		10},
		{szMon_Castledoor,			szMon_Castledoor_Soldier,	101,		6}
};

#define	srCRISTAL_RANDOM		8
#define	srCRISTAL_CLAN			9
#define srCLAN_MONSTER_MAX		3
#define	srCRISTAL_CASTLE_START	13
#define	srCRISTAL_CASTLE_END	16

#define	srCRISTAL_SKELETON		16
#define	srCRISTAL_KAOS			17
#define	srCRISTAL_IMPERNA		18
#define srCRISTAL_EXTREME		19
#define	srCRISTAL_MARVEL_RANDOM	20
#define	srCRISTAL_G_DIVINE_CLAN			21

#define AGING_MONEY_FREE

DWORD OnlineReward_Time;

DWORD Boss;

srCRISTAL_MONSTER	srCristalMonster[srCRISTAL_MAX] = {
	{ "È£ÇÇ"				, 0 , 20	},
	{ "È©°íºí¸°"			, 0 , 20	},
	{ "µðÄÚÀÌ"			, 0 , 15	},
	{ "¹Ù°ï"				, 0 , 15	},
	{ "ÇìµåÄ¿ÅÍ"			, 0 , 15	},
	{ "ÆÄÀÌ°ï"			, 0 , 10	},
	{ "Å·È£ÇÇ"			, 0 , 5		},
	{ "ÇæÅ©"				, 0 , 0		},
	{ "·£´ý"				, 0 , 0		},
	{ "°¡µð¾È ¼¼ÀÎÆ®"		, 0 , 0		},
	{ "À¥ "				, 0 , 0		},
	{ "´ÙÅ© ½ºÆåÅÍ "		, 0 , 0		},
	{ "¾ÆÀÌ¾ð °¡µå "		, 0 , 0		},
	{ "¸®Ä«¸£ÅÙ ¹Îº´´ë"		, 0 , 0		},
	{ "¸®Ä«¸£ÅÙ °æºñ´ë"		, 0 , 0		},
	{ "ºí·¹½º¿Õ±¹ °æºñ´ë"	, 0 , 0		},

	{ "½ºÄÌ·¹Åæ Å©¸®½ºÅ»"	, 0 , 0		},
	{ "Ä«¿À½º   Å©¸®½ºÅ»"	, 0 , 0		},
	{ "ÀÎÆä¸£³ª Å©¸®½ºÅ»"	, 0 , 0		},
	{ "°¡µð¾È µð¹ÙÀÎ"		, 0 , 0		}
};

srCRISTAL_MONSTER	srCristalMonsterBoss[srCRISTAL_MAX] = {
	{ "Â¯ÇÇ"				, 0 , 20	},
	{ "¿ÍÀÏµå °íºí¸°"		, 0 , 20	},
	{ "¸Æ½Ã¸Ø µðÄÚÀÌ"		, 0 , 15	},
	{ "¹Ù¿ìÅæ"			, 0 , 15	},
	{ "º£°¡ µå¹Ì¸£"		, 0 , 15	},
	{ "Çï½Ì"				, 0 , 10	},
	{ "È£·¯ÇÇ¿Â"			, 0 , 5		},
	{ "Å¸ÀÌÇ¬"			, 0 , 0		},
	{ "·£´ý"				, 0 , 0		},
	{ "°¡µð¾È ¼¼ÀÎÆ®"		, 0 , 0		},
	{ "Ä¿ÁîÀ¥ "			, 0 , 0		},
	{ "´ÙÅ© ÆÒÅÒ "			, 0 , 0		},
	{ "ÀÌ¹ÌÆ¼¸£ °¡µå "		, 0 , 0		},
	{ "¸®Ä«¸£ÅÙ ¹Îº´´ë"		, 0 , 0		},
	{ "¸®Ä«¸£ÅÙ °æºñ´ë"		, 0 , 0		},
	{ "ºí·¹½º¿Õ±¹ °æºñ´ë"	, 0 , 0		},

	{ "½ºÄÌ·¹Åæ Å©¸®½ºÅ»"	, 0 , 0		},
	{ "Ä«¿À½º   Å©¸®½ºÅ»"	, 0 , 0		},
	{ "ÀÎÆä¸£³ª Å©¸®½ºÅ»"	, 0 , 0		},
	{ "°¡µð¾È µð¹ÙÀÎ"		, 0 , 0		}
};

srCRISTAL_MONSTER srMarvelCristalMonster[MARVELCRISTAL_MAX] = {
	{ "¹Ù°ï"				, 0 , 20	},
	{ "ÇìµåÄ¿ÅÍ"			, 0 , 20	},
	{ "ÆÄÀÌ°ï"			, 0 , 15	},
	{ "Å·È£ÇÇ"			, 0 , 15	},
	{ "ÇæÅ©"				, 0 , 12	},
	{ "À¥"				, 0 , 10	},
	{ "´ÙÅ© ½ºÆåÅÍ"		, 0 , 5		},
	{ "¾ÆÀÌ¾ð °¡µå"		, 0 , 3		}
};

srCRISTAL_MONSTER srMarvelCristalMonsterBoss[MARVELCRISTAL_MAX] = {
	{ " ¹Ù¿ìÅæ "			, 0 , 20	},
	{ " º£°¡ µå¹Ì¸£ "		, 0 , 20	},
	{ " Çï½Ì "				, 0 , 15	},
	{ " È£·¯ÇÇ¿Â "			, 0 , 15	},
	{ " Å¸ÀÌÇ¬ "			, 0 , 12	},
	{ " Ä¿ÁîÀ¥ "			, 0 , 10	},
	{ " ´ÙÅ© ÆÒÅÒ "			, 0 , 5		},
	{ " ÀÌ¹ÌÆ¼¸£ °¡µå "		, 0 , 3		}
};

#define	srSKILL_MONSTER_MAX		5

srCRISTAL_MONSTER	srSkillMonster[srSKILL_MONSTER_MAX] = {
	{ "¸ÞÅ» °í·½"		, 0 , 0	},
	{ "¿ï¹ö¸°"			, 0 , 0	},
	{ "ÆÄÀÌ¾î ¿¤·¹¸àÅ»"	, 0 , 0	},
	{ "ºí·¯µð ³ªÀÌÆ®", 0, 0	},
	{ "¾Æ¸£Äí´Ù", 0, 0	}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy[7] = {
	{ " ÄÚÅ©¸®½ºÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " ¸®Ä¡ÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ½ÎÀÌÅ¬·Ó½ºÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ¸ÞÇÍÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ºñµ¶ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " Á»ºñÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " µðÄÚÀÌÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy2[7] = {
	{ " ¹ìÇÇ¸¯ ¹îÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " ±×¸®ºìÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ÀÌºí ½º³×ÀÏÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " Å©¸³Æ®ÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ºÎ¸¶ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ¹Ù°ïÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " Å¸ÀÌÅºÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy3[7] = {
	{ " ºñºíÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " ½½·¹ÀÌ¿ÂÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ½½·¯ÅÍÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " Å¸¿ö °í·½ÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ¸Ó¹ÌÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ³ªÁîÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " À§Ä¡ÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy4[7] = {
	{ " ¹ö¼­Ä¿ÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " Å¸ÀÌÇ¬ÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ¸®ÀÚµåÆ÷Å©ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ·¥ÆäÀÌÁöÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ¾Æº§¸°ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ÀÎÅ¥¹ö½ºÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " »õµå´Ï½ºÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy5[7] = {
	{ " µð-¸Ó½ÅÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " Å·È£ÇÇÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ¿À¸Þ°¡ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " µ¥µåÁ¸ÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ¾ÆÀÌ½º °í·½ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ÄÝµå¾ÆÀÌÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " ±¼°¡¸£ÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy6[7] = {
	{ " ¹ìÇÇ¸¯ ¹îÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " ±×¸®ºìÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ÀÌºí ½º³×ÀÏÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " Å©¸³Æ®ÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ºÎ¸¶ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ¹Ù°ïÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " ¸ÓÇÉÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy7[7] = {
	{ " ºñºíÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " ½½·¹ÀÌ¿ÂÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ½½·¯ÅÍÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " Å¸¿ö °í·½ÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ¸Ó¹ÌÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ³ªÁîÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " ½½¸®¹öÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy8[7] = {
	{ " ¹ö¼­Ä¿ÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " Å¸ÀÌÇ¬ÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ¸®ÀÚµåÆ÷Å©ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ·¥ÆäÀÌÁöÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ¾Æº§¸°ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ÀÎÅ¥¹ö½ºÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " ¸ÞÆ®·ÐÀÇ ¿µÈ¥ "			, 0 , 5		}
};

srCRISTAL_MONSTER	srCristalMonsterEnemy9[7] = {
	{ " µð-¸Ó½ÅÀÇ ¿µÈ¥ "				, 0 , 20	},
	{ " Å·È£ÇÇÀÇ ¿µÈ¥ "		, 0 , 20	},
	{ " ¿À¸Þ°¡ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " µ¥µåÁ¸ÀÇ ¿µÈ¥ "			, 0 , 15	},
	{ " ¾ÆÀÌ½º °í·½ÀÇ ¿µÈ¥ "		, 0 , 15	},
	{ " ÄÝµå¾ÆÀÌÀÇ ¿µÈ¥ "				, 0 , 10	},
	{ " ±×·ÎÅ×½ºÅ©ÀÇ ¿µÈ¥ "			, 0 , 5		}
};

#define	srBC_MONSTER_MAX		4
#define	srBC_MONSTER_TOTAL		16
srCRISTAL_MONSTER	srBillingCrystalMonster[srBC_MONSTER_TOTAL] = {
	{ " ½ºÄÌ·¹Åæ ¾ÆÃ³ "     , 0 , 0	},
	{ " ½ºÄÌ·¹Åæ ·¹ÀÎÀú "	, 0 , 0	},
	{ " ½ºÄÌ·¹Åæ ¿ö¸®¾î "	, 0 , 0	},
	{ " ½ºÄÌ·¹Åæ ³ªÀÌÆ® "	, 0 , 0	},

	{ " ³ªÁî "	        , 0 , 0	},
	{ " Çìºñ °íºí¸° "	, 0 , 0	},
	{ " ½ºÆ®¶óÀÌ´õ "	, 0 , 0	},
	{ " µð-¸Ó½Å "	        , 0 , 0	},

	{ " ¶óÅõ "	        , 0 , 0	},
	{ " ±×·ÎÅ×½ºÅ© "	, 0 , 0	},
	{ " ¾ÆÀÌ¾ð ÇÇ½ºÆ® "	, 0 , 0	},
	{ " ÇÁ·Î½ºÆ® ¿¡ÀÌ¼ÇÆ® "	, 0 , 0	},

	{ " ¿À¹ÌÅ©·Ð "	        , 0 , 35	},
	{ " ½ºÆÄÀÌ´õ Æ®·çÆÛ "	, 0 , 30	},
	{ " ¸¶¿îÆ¾ "	, 0 , 20	},
	{ " ¿À¸Þ°¡ "	, 0 , 15	}
};

#define srHAMMER_MONSTER_MAX		16

std::unordered_map<DWORD, std::unordered_map<rsPLAYINFO*, DWORD>> DamageList;
smCHAR_INFO* srCharInfo_HammerMonster[srHAMMER_MONSTER_MAX];
int	srHammerMonsterCount = 0;

char* szAdminIP = "220.76.89.";
char* szAdminIP2 = "220.76.88.";

#define MYWM_NOTIFYICON		(WM_USER+140)
#define MYWM_USER_COUNT		(WM_USER+110)
#define ID_MESSTEXT		101

void TrayIconClose();
void TrayIconCreat();

int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);

int InitAll();

void RemoveAll();

INT64 Exp155 = 0;
INT64 Exp160 = 0;

CRITICAL_SECTION	cSerSection;
CMutex* pcServerMutex;
UINT  uUsersInGame;
UINT  uUnitsInGame;
static CRITICAL_SECTION	cOdbcSection;

char	szServer_DebugString[256];
DWORD	dwServer_DebugMessage;
char	szServer_DebugLastUserID[32];
char	szServer_DebugLastUserName[32];
int		Server_DebugCount;

int		rsNSpriteMode = 0;

int		rsOpenNPC_RandomPos = 0;

HWND	hDebugWnd = 0;
#define	SWM_DISPDEBUG	(WM_USER+77)

int KillDelay;

int	ServerMode = 0;
int	Server_SqlReady = 0;
int	ServerNameCode = 0;

static HINSTANCE hInst;
extern HWND hwnd;
static HWND hMsgTextWnd;
static HDC	hdc = NULL;
static int Quit = 0;
static char* szAppName = "È£¶± ¿Â¶óÀÎ °ÔÀÓ¼­¹ö";
static LONG APIENTRY WndProc(HWND, UINT, WPARAM, LPARAM);
static int WinWidth = 320;
static int WinHeight = 240;

static int WSA_RecvMsgCount = 0;

static	int AccountPerl = 100;
static	int	ShutDownFlag = 0;
static	int	ShutDownLeftTime = 0;

void rsPresentBox(rsPLAYINFO* lpPlayInfo, DWORD Code);

INT SetupDefWindow(HINSTANCE hInstance, HANDLE hPreInst, LPSTR lpszCmdParam, int nCmdShow)
{
	WNDCLASS	wndclass;

	hInst = hInstance;

	if (!hPreInst) {
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInst;
		wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SERVER_ICON));
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = "IDR_MENU1";
		wndclass.lpszClassName = szAppName;
		RegisterClass(&wndclass);
	}

	hwnd = CreateWindow(szAppName, szAppName,

		WS_SYSMENU | WS_MINIMIZEBOX | WS_MINIMIZE,
		CW_USEDEFAULT,
		CW_USEDEFAULT, WinWidth, WinHeight, NULL, NULL,
		hInst, NULL);

	HMENU	hMenu;
	hMenu = CreateMenu();
#ifndef _LANGUAGE_KOREAN
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU2));
#else
	hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
#endif

	SetMenu(hwnd, hMenu);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

#ifdef	_LANGUAGE_CHINESE
	SetWindowText(hwnd, "Hotuk GameServer [ PT_CHINESE ]");
#endif

#ifdef	_LANGUAGE_JAPANESE
	SetWindowText(hwnd, "Hotuk GameServer [ PT_JAPANESE ]");
#endif

#ifdef _LANGUAGE_TAIWAN
	SetWindowText(hwnd, "Hotuk GameServer [ PT_TAIWAN ]");
#endif

#ifdef _LANGUAGE_ENGLISH
#ifdef _LANGUAGE_PHILIPIN
	SetWindowText(hwnd, "Hotuk GameServer [ PT_PHILIPPINE ]");
#else
	SetWindowText(hwnd, "Hotuk GameServer [ PT_ENGLISH ]");
#endif
#endif
#ifdef _LANGUAGE_BRAZIL
	SetWindowText(hwnd, "Hotuk GameServer [ PT_BRAZIL ]");
#endif

#ifdef _LANGUAGE_ARGENTINA
	SetWindowText(hwnd, "Hotuk GameServer [ PT_ARGENTINA ]");
#endif

#ifdef _LANGUAGE_VEITNAM
	SetWindowText(hwnd, "Hotuk GameServer [ PT_VIETNAM ]");
#endif
#ifdef _LANGUAGE_THAI
	SetWindowText(hwnd, "Hotuk GameServer [ PT_THAILAND ]");
#endif

#ifndef _LANGUAGE_KOREAN
	AccountPerl = 40;
#endif

	TrayIconCreat();

	ServerMode = TRUE;
	szServer_DebugString[0] = 0;

	rsRefreshConfig();

	InitGameSocket(TRUE);

	InitAll();

	if (smConfig.dwServerPort)
		InitBindSock(smConfig.dwServerPort);
	else
		InitBindSock(TCP_SERVPORT);

	EnableMenuItem(GetMenu(hwnd), ID_STOP, MF_ENABLED);
	EnableMenuItem(GetMenu(hwnd), ID_START, MF_GRAYED);

	return	TRUE;
}

char szMessageBuff[256];
DWORD ListBuff[smSOCKBUFF_SIZE / 4];
int PlayerCount;

struct	rsSERVER_NOTICE {
	DWORD Counter;
	char szMessage[256];
};
rsSERVER_NOTICE	rsNoticeMessage;

extern	smWINSOCK	smWSock[CONNECTMAX];

#define DIST_AROUND_NEAR	(256*256)
#define DIST_AROUND_MIDDLE	(16*64 * 16*64)

#define CHATBUFF_MAX		1024
#define CHATBUFF_MASK		1023

#define TRANS_IPMAX			(1000/sizeof(TRANS_IPLIST))

#define AREA_USERMAX		256
#define AREA_MAX			256

#define AUTOPLAYER_MAX		2048
#define AUTOPLAYER_MASK		2047

int rsConnectUserLimit = 800;

#ifdef	_LANGUAGE_THAILOW

#define	TRANS_MAX_CHAR_LIMIT	24
#define	TRANS_MAX_USER_LIMIT	16
#else
#define	TRANS_MAX_CHAR_LIMIT	28
#define	TRANS_MAX_USER_LIMIT	18
#endif

#define	OVER_TRANS_TIME		1500

#define STAGE_MAX			10
smSTAGE3D* lpsmStage[STAGE_MAX];

DWORD		dwPlayServTime = 0;
DWORD		dwOffsetTime = 0;

#define	CHR_MONSTER_MAX		300
#define	DEF_ITEM_MAX		MAX_ITEM

#define	REOPEN_COUNT_NUM	256

#define TRANS_VIEW_LIMIT		(64*64)

#define OPEN_START_MONSTER_MAX		3

#define	STG_ITEM_WAIT_TIME		(1000*60*3)
#define	STG_ITEM_WAIT_TIME_LOW	(1000*90)

#define ITEM_SET_DIST	24

POINT	ptItemSettingPosi[8] = {
	{  0			 , -ITEM_SET_DIST },
	{  ITEM_SET_DIST , -ITEM_SET_DIST },
	{  ITEM_SET_DIST ,  0			  },
	{  ITEM_SET_DIST ,  ITEM_SET_DIST },
	{  0             ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,  ITEM_SET_DIST },
	{ -ITEM_SET_DIST ,  0             },
	{ -ITEM_SET_DIST , -ITEM_SET_DIST }
};

int	LoginServer = 0;
int	AutoPlayServer = 0;
int	UserPlayServer = 0;

int chrMonsterCnt;
int	EventMonster = 0;

#define	LIMIT_PK_LEVEL	20

int	rsHardCoreEvent = 0;
int	rsDamgeOffEvent = 0;

int	rsDamgeOffEvent1 = 0;
int	rsDamgeOffEvent2 = 0;

int rsDefenseOffEvent = 0;

int	rsCristalEvent = 0;
DWORD	dwBabelPlayTime = 0;
int		BabelPlayField = -1;

char* MonsterPath = "GameServer\\monster\\";
char* ItemPath = "GameServer\\OpenItem\\";
char* szNpcInfoPath = "GameServer\\npc\\";
char* szFieldInfoPath = "GameServer\\Field\\";
char* HackLogDirectory = "LogFile";
char* LogDirectory = "LogFile";
char* DebugLogDirectory = "LogDebug";
char* AdminLogDirectory = "LogAdmin";

char* EventLogDirectory = "EventLog";

static char* szDebugServer = "penguin-pc";
int DebugServerMode = 0;

int	DefaultItemCount;

static int	ChatBuffCnt;
static char TransTemp[1024];
static char	szChkID[32];

smCHAR_INFO* chrMonsterList;
smCHAR_MONSTER_INFO* chrMonInfoList;
rsPLAYINFO* rsPlayInfo;
static CHATBUFF* ChatBuff;
sDEF_ITEMINFO* DefaultItems;

smCHAR* chrAutoPlayer;

smCHAR_INFO* chrNpcMonsterInfo = 0;

DWORD	dwConnectCount = 0;
DWORD	rsAutoPlayTransCount = 0;

rsCURRENCY_LOG	CurrencyLog;

int ActivePlayCounter;
int	srAutoPlayCount = 0;

smCHAR* lpActiveChar;

time_t		tServerTime = 0;

char* rsRecordDataBuff = 0;

int			srAcceptErrorCount = 0;
int			srLastAcceptRsult = 0;
int			srRouteErrorCount = 0;
int			srLogFailedCount = 0;

static int			spJobCode = 0;
static int			spItemNormal = 0;
static DWORD		spJobCodeTime = 0;

static int			spTimeAdjust = 0;
static DWORD		spTimeAdjustTime = 0;

char* szLogItemDataDirectory = "LogItemData";

rsUSER_LIST_TOP10	rsUserListDamageTop10;

#ifdef _LANGUAGE_ENGLISH
#ifdef _LANGUAGE_PHILIPIN
#define	rsBLESSCASTLE_TAX_TIME			23
#else
#define	rsBLESSCASTLE_TAX_TIME			4
#endif
#else
#ifdef _LANGUAGE_VEITNAM
#define	rsBLESSCASTLE_TAX_TIME			23
#else
#define	rsBLESSCASTLE_TAX_TIME			2
#endif
#endif

rsBLESS_CASTLE		rsBlessCastle;

int rsRecvSystemInfo(rsPLAYINFO* lpPlayInfo, void* Buff);

int rsInit_SerToServer();

int	rsDisconnectSystemLine(smWINSOCK* lpsmSock);

int DisconnectUser(smWINSOCK* lpsmSock);

int SaveThrowItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum);

int rsLogAccount(rsPLAYINFO* lpPlayInfo, char* szID, char* szPassword, char* szMac, char* szPath, char* szPCName);

int rsGetLogOnQueCount();

int RecordHackLogFile(rsPLAYINFO* lpPlayInfo, void* lpTransCommand);

int RecordDebugPlayLogFile(rsPLAYINFO* lpPlayInfo);

int RecordMixItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpSrcItem, sITEMINFO* lpMixItem);

int RecordAgingItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpSrcItem, sITEMINFO* lpMixItem, int Mode);

int	InitCrackFinding();

int rsSendNetLog(rsPLAYINFO* lpPlayInfo);

int RecordCollectMoney(rsPLAYINFO* lpPlayInfo, int Money);

int RecordDeleteCharacter(char* szID, char* szIP, smCHAR_INFO* lpCharInfo);

int RecordGetHighItem(rsPLAYINFO* lpPlayInfo, struct STG_ITEMS* lpStgItem);

int rsCheckChildServer(char* szIP);

int	rsShutDown();

int RecordSmeltingItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpSmeltingItem);

int RecordManufactureItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpManufactureItem);

int RecordMixtureResetItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpMixtureResetItem);

int RecordMovieBloodyBattleItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpMovieBloodyBattleItem);

class STG_AREA;

int rsOpenEventMonster(int EventCode, int wParam, int lParam, int sParam);

int rsReOpenEventMonster(STG_AREA* lpStgArea, smCHAR* lpChar);

int rsCloseEventMonster(int EventCode);

int rsPutItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode);

int rsPutItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode);

int rsPutItemUnique(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode, DWORD dwUniqueCode);

int rsPutItem2(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpItem);

int rsCheck_ChageJob(rsPLAYINFO* lpPlayInfo, int NewCnageJob);

int CreatePresentItem(DWORD dwItemCode, STG_AREA* lpStgArea, int x, int y, int z, int count);

int rsOpenBossMonster(STG_AREA* lpStgArea, sBOSS_MONSTER* lpBossMonster);

int rsCharChanger(smCHAR* lpChar, smCHAR_INFO* lpCharInfo, smCHAR_MONSTER_INFO* lpMonInfo);

int	rsInitHardCoreEvent();

int SendOpenCollectMoney(smWINSOCK* lpsmSock);

int rsCheckHardCoreEventArea(int x, int y, int z);

int	rsTransUpdateSod(rsPLAYINFO* lpPlayInfo);

STG_AREA* FindStageField(int x, int z);
STG_AREA* FindStageFieldNum(int Field);

extern TRANS_SERVER_LIST	TransServerList;
extern rsSERVER_CONFIG		rsServerConfig;

int rsSendServerList(smWINSOCK* lpsmSock, int ClanTicket);

int rsSendDataServer(smWINSOCK* lpsmSock, void* szData);

int rsSendGameServer(smWINSOCK* lpsmSock, void* szData);

int rsSendAreaServer(smWINSOCK* lpsmSock, void* szData);

int	rsSendCommandUser(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommandEx);

int	rsRecordFixExp(rsPLAYINFO* lpPlayInfo);

int rsAddBackListID(char* szID, DWORD dwTime);

DWORD rsCheckBackListID(char* szID);

int rsResetBackList();

int rsFreekBackListID(char* szID);

int rsShowBlackList(smWINSOCK* lpsmSock, char* szID);

int RecordJobChanger(rsPLAYINFO* lpPlayInfo);

int	rsCheckBlockUserFile(char* szID);

int rsAddBlockUserFile(char* szID, char* szLog);

int rsSendGameServerExp(rsPLAYINFO* lpPlayInfo);

int	rsCheckEnableIP(DWORD dwUserIP);

int	rsCheckDisableIP(DWORD dwUserIP);

DWORD GetSwapIPCode(char* szIP);

int	rsCheckAdminIP(DWORD dwUserIP);

int	rsCheckSystemIP(DWORD dwUserIP);

int	rsCheckLoginServerIP(DWORD dwUserIP);

int	rsAddInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);

int	rsFindInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int	rsFindInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);

int	rsCheckInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode);

int	rsCheck_ItemSecCode(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int* pPotionCount);

int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo, int NewItem);

int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommandEx);

int Record_TempLogFile(char* szMessage);

int Record_BillingLogFile(rsPLAYINFO* lpPlayInfo, DWORD wParam, DWORD lParam, DWORD sParam, DWORD eParam);

int Record_DeadUser(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int RecordShutdownLog(int LogCode, int LParam, int SParam);

int rsLoadCopiedItemList();

int rsRemoveCopiedItemList();

int rsCheckCopiedItem(sITEMINFO* lpItem);

int rsCheckCopiedItem(DWORD dwCode, DWORD dwHead, DWORD dwChkSum);

int rsSend_ResultSOD(rsPLAYINFO* lpPlayInfo, int Point, int KillCount, int TotalPoint, int TotalSucessUser, int TotalUser, int ClassCode);

int	rsRecvSkillPartyUser(TRANS_PARTY_SKILL* lpTransPartySkill);

int rsRecvProcessSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsCancelSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsUpdateSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsClanUpdate(rsPLAYINFO* lpPlayInfo, TRANS_CLAN_COMMAND_USER* lpTransClanUser);

int rsRecvYahooMotion(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

rsPLAYINFO* FindUserFromName(char* szName);

int	rsPushKillMonster(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo, STG_AREA* lpStgArea);

int	rsSaveAdminCommand(rsPLAYINFO* lpPlayInfo, char* szChatCommand, int Level);

int	rsRecordAdminCommand(rsPLAYINFO* lpPlayInfo, char* szChatCommand, int Level);

int	rsCheckAdminPlayer(rsPLAYINFO* lpPlayInfo);

int rsRecvStarPoint(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsRecvSodClanCash(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsRecvGiveMoney(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsRecvPaymentMoney(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

DWORD rsOpenEventPuzzleItem(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar);

int	rsTrade_PersonalShop(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, smTRANS_COMMAND_BUFF* lpTransCommandBuff);

int	rsUseLovelyItem(rsPLAYINFO* lpPlayInfo, DWORD	dwItemCode);

int	rsMorifEventMessage(smCHAR* lpChar);

int	rsMollyWolfEventMessage(smCHAR* lpChar);

int	rsQuestMasterMessage(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo);

int	rsSantaGoblinEventMessage(smCHAR* lpChar);

int	rsChichenDayEventMessage(smCHAR* lpChar);

int rsGetQuestCommand(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int	rsSetNoticeMessage(char* szMessage);

int rsInit_Castle();

int	rsStart_CombatCastle();

int	rsEnd_CombatCastle(int DefenceFlag);

int	rsEnd_CombatCastle();

int	rsEasy_CastleMode();

int rsMain_CombatCastle();

int	rsSelectDamageClanTop10(smCHAR* lpChar, rsUSER_LIST_TOP10* lpUserListDamageTop10);

int	rsRecvBlessCastleInfoFromGameServer(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommand);

int	rsSendBlessCastleInfoToDataServer(rsPLAYINFO* lpPlayInfo);

int	rsBlessCastle_SoulFountainMain();

int rsLoadCastleInfo();

int	rsSaveCastleInfo();

int RecordBlessCastleLog(rsUSER_LIST_TOP10* lpUserListDamageTop10);

int RecordBlessCastleSetup(rsPLAYINFO* lpPlayInfo, smTRANS_BLESSCASTLE* lpBlessCastleSetup);

int rsCheck_BlessCastleClanSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsSendBlessCastleClanSkill(rsPLAYINFO* lpPlayInfo);

int	rsOpenSiegeCastleItem(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO* lpPlayInfo);

int rsCheckPlayField(rsPLAYINFO* lpPlayInfo);

int rsStartUser_PresentItem(rsPLAYINFO* lpPlayInfo);

DWORD rsLowLevelItem(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar);

int rsRecvUpdateServerParam(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int rsSendUserID_MainServer(rsPLAYINFO* lpPlayInfo);
int rsRecvUserID_MainServer(rsPLAYINFO* lpPlayInfo, smTRANS_CHAR_COMMAND2* lpTransCharCommand);

int rsRecvHackTrap(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCharCommand);

#ifdef _CHECK_MESH

int rsRecvCheckItemMesh(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);
#endif

int	rsSendCloseClient(rsPLAYINFO* lpPlayInfo);

int rsPutItem_TreasureBox(rsPLAYINFO* lpPlayInfo, DWORD Code);

int rsPutItem_CapsuleItem(rsPLAYINFO* lpPlayInfo, DWORD Code);

int rsFiltChatMsg(rsPLAYINFO* lpPlayInfo, char* szMsg, int len);
int rsRecvEventGame(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand);

int Event_UserInfo_Init(rsPLAYINFO* lpPlayInfo, WORD sTime);

#define	ITEMLOG_GET				0
#define	ITEMLOG_PUT				6
#define	ITEMLOG_MIXING			3
#define	ITEMLOG_MIXLOST			9
#define	ITEMLOG_AGING			4
#define	ITEMLOG_AGINGLOST		10
#define	ITEMLOG_AGINGUP			12
#define	ITEMLOG_BUYSHOP			5
#define	ITEMLOG_SELLSHOP		7
#define	ITEMLOG_TRADE			8
#define	ITEMLOG_USED			11
#define	ITEMLOG_EXPRESS			13
#define	ITEMLOG_GETWING			14
#define	ITEMLOG_WINGLOST		15
#define	ITEMLOG_BUYSTAR			16

#define	ITEMLOG_AGING_2UP		17
#define	ITEMLOG_AGING_2DOWN		18
#define	ITEMLOG_AGING_1DOWN		19
#define	ITEMLOG_AGING_KEEP		20

#define	ITEMLOG_PRESENT			21
#define	ITEMLOG_MYSHOP			22

#define	ITEMLOG_USE_ALCHMY		24
#define	ITEMLOG_LOST_ALCHMY		25
#define	ITEMLOG_GET_ALCHMY		26

#define	ITEMLOG_GET_RECON		27
#define	ITEMLOG_LOST_RECON		28
#define ITEMLOG_SMELTING_LOST	29
#define ITEMLOG_SMELTING_GET	30
#define ITEMLOG_MANUFACTURE_LOST 31
#define ITEMLOG_MANUFACTURE_GET 32
#define ITEMLOG_MANUFACTURE_FAIL 33
#define ITEMLOG_MIXTURE_RESET_LOST	34
#define ITEMLOG_MIXTURE_RESET_FAIL	35
#define ITEMLOG_MIXTURE_RESET_GET	36

int	rsRecord_ItemLog(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag);

int	rsRecord_ItemLog2(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag);

int	rsRecord_ItemLog_Change(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum,
	DWORD dwItemCode2, DWORD	dwHead2, DWORD dwChkSum2, int Flag);

int	rsRecord_ItemLost(rsPLAYINFO* lpPlayInfo, DWORD* lpItemCode, DWORD* lpHead, DWORD* lpChkSum, int Flag);

int	rsRecord_ItemLog_Trade(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, TRANS_TRADE_ITEMKEY* lpTransTradeItemKey);

int	rsRecord_ItemLog_Post(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwGCode, char* szTelNum, int Flag);

int rsRecord_SmeltingItemLog(rsPLAYINFO* lpPlayInfo, DWORD* lpItemCode, DWORD* lpHead, DWORD* lpChkSum, int Flag);

int rsRecord_ManufactureItemLog(rsPLAYINFO* lpPlayInfo, DWORD* lpItemCode, DWORD* lpHead, DWORD* lpChkSum, int Flag);

//int rsRecord_MixtureResetItemLog(rsPLAYINFO* lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER* pMixtureResetItem_Server, int Flag);

extern void LeIniStr(char* Section, char* Key, char* szFileIni, char* Var1);

int rsSendAreaOpenKidMonster(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar);
int rsOpenKidMonster(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand, int mon_Num);

int rsSendAreaOpenSODGuardMonster(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar);
int rsOpenSODGuardMonster(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand, int mon_Num);

struct	smTRANS_SYSTEM_COMMAND {
	int		size, code;

	int		tCode;
	DWORD	dwObjectSerial;
	DWORD	dwNameCode;
	int		x, y, z;

	DWORD	Param[32];
};

#define	smTRANS_SYSCODE_CONNECT			0x1000
#define	smTRANS_SYSCODE_KILL_MONSTER	0x1100
#define	smTRANS_SYSCODE_GET_MONEY		0x1110
#define	smTRANS_SYSCODE_GET_ITEM		0x1112
#define	smTRANS_SYSCODE_DMG_USER_LIST	0x1120
#define	smTRANS_SYSCODE_NETSTATE		0x1200
#define	smTRANS_SYSCODE_NETSUCCESS		0x1250

#define	smTRANS_SYSCODE_CONNECT_USER	0x1300
#define	smTRANS_SYSCODE_USER_FAILED		0x1302
#define	smTRANS_SYSCODE_EXP_INFO		0x1310

#define	SER_TO_SERVER_SOCKET_MAX	4
#define	SER_TO_SERVER_SOCKET_MASK	3

smWINSOCK* lpsmSock_SerToServer[SER_TO_SERVER_SOCKET_MAX] = { 0,0,0,0 };
DWORD		dwSerToSerIP = 0;
DWORD		dwSerToSer_Count = 0;
char		szSerToSerIP[32];

#define	SER_TO_LOGIN_SOCKET_MAX	16
rsPLAYINFO* lpPlayInfo_LoginServer[SER_TO_LOGIN_SOCKET_MAX] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
DWORD		dwSerToLogin_Count = 0;
DWORD		dwSerToLogin_Num = 0;

rsKILL_MONSTER_INFO	rsKillMonster_Que[srMONSTER_KILL_QUE_MAX + 10];
int	rsKillMonster_Push = 0;
int	rsKillMonster_Pop = 0;

HANDLE	hSerToServer_Thread = 0;
DWORD	dwSerToServer_ID = 0;

int	rsSystemNetCount = 0;
int	rsSystemLineConnCount = 0;
int rsSystemLineFailedCount = 0;
int rsSystemLinePlayCount = 0;

int	rsGetSystemLineCount();
int	rsSetSerToLoginLine();
int rsSendPacketToLoginLine(char* szBuff, int size);

smWINSOCK* rsFindNextSertoServerSock();
int	rsSendMoneyToSystemLine(rsPLAYINFO* lpPlayInfo, int Money);
int rsSendCharInfoToLoginServer(rsPLAYINFO* lpPlayInfo);

int	rsMonHuntCount = 0;
int	rsMonOpenCount = 0;
int	rsItemOpenCount = 0;
int	rsMoneyTotalCount = 0;
int	rsCoinTotalCount = 0;
int	rsCoinTotalCount2 = 0;
int	rsItemBuffOverCount = 0;

int	rsSendMoneyToUser(rsPLAYINFO* lpPlayInfo, int Money);

POINT3D* lprsFixedPoint = 0;

extern int	Server_LimitVersion;

int Server_AllocMemory()
{
	chrMonsterList = new	smCHAR_INFO[CHR_MONSTER_MAX];
	chrMonInfoList = new	smCHAR_MONSTER_INFO[CHR_MONSTER_MAX];
	rsPlayInfo = new	rsPLAYINFO[CONNECTMAX];
	ChatBuff = new	CHATBUFF[CHATBUFF_MAX];
	DefaultItems = new	sDEF_ITEMINFO[DEF_ITEM_MAX];
	chrAutoPlayer = new	smCHAR[AUTOPLAYER_MAX];
	pcServerMutex = new CMutex("Server", &cSerSection);
	//SQLManager::CreateInstance();
	//SQLManager::GetInstance()->Load();

#ifdef _LANGUAGE_CHINESE
	{
		ZeroMemory(DefaultItems, sizeof(sDEF_ITEMINFO) * DEF_ITEM_MAX);
	}
#endif

	ZeroMemory(chrAutoPlayer, sizeof(smCHAR) * AUTOPLAYER_MAX);

	return TRUE;
}

int Server_RemoveMemory()
{
	delete	DefaultItems;
	delete	ChatBuff;
	delete	rsPlayInfo;
	delete	chrMonInfoList;
	delete	chrMonsterList;

	return TRUE;
}

int InitAdminCommand();

int Reload = 0;

int rsRefreshConfig()
{
	return TRUE;
}

int rsLogOut(rsPLAYINFO* lpPlayInfo)
{
	int BlockTime;
	int Money;

	if (lpPlayInfo && lpPlayInfo->szID[0] && lpPlayInfo->lpsmSock) {
		if (lpPlayInfo->szName[0]) {
			Money = lpPlayInfo->ServerMoney - lpPlayInfo->WareHouseMoney;

			RecordLogSql(LOG_SQL_LOGOUT, lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->szGPCode, 1, lpPlayInfo->smCharInfo.JOB_CODE,
				GetExp64(&lpPlayInfo->smCharInfo), lpPlayInfo->smCharInfo.Level, Money);
		}

		if (rsServerConfig.PresentLevel > 0 && lpPlayInfo->spLevel_Start > 0 && rsServerConfig.PresentLevel > lpPlayInfo->CharLevelMax) {
			lpPlayInfo->smCharInfo.Level = GetLevelFromExp(GetExp64(&lpPlayInfo->smCharInfo));

			if (lpPlayInfo->spLevel_Start < rsServerConfig.PresentLevel && lpPlayInfo->smCharInfo.Level >= rsServerConfig.PresentLevel) {
				rsAddPostBox_Present(lpPlayInfo);

				rsRecord_ItemLog_Post(lpPlayInfo, 99, 0, 0, lpPlayInfo->smCharInfo.Level, 0, ITEMLOG_PRESENT);
			}
		}

		if (lpPlayInfo->BlockTime == 0x7FFFFFFF)
			BlockTime = 60 * 24 * 30 * 3;
		else
			BlockTime = lpPlayInfo->BlockTime / (60 * 1000);

		RecordGameLogSql(GAMELOG_SQL_LOGOUT, lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->szGPCode,
			lpPlayInfo->smCharInfo.JOB_CODE, lpPlayInfo->szGuid, BlockTime);

		if (lpPlayInfo->szGPCode[0]) {
			bSql_Logout(lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->szGPCode,
				lpPlayInfo->DisuseDay, lpPlayInfo->UsePeriod, lpPlayInfo->szGuid, lpPlayInfo->Bl_RNo);
		}

		if (lpPlayInfo->ClanTicketCode && lpPlayInfo->szName[0])
			bClan_UserTicket(lpPlayInfo, 1);

		rsRecordFixExp(lpPlayInfo);
	}

	if (rsServerConfig.ExpGameTimeMode) {
		if (lpPlayInfo->dwExpGameTimeCheck) {
			bSql_GetExpGameTime(lpPlayInfo, lpPlayInfo->dwExpGameTime / 1000);
		}
	}

	return TRUE;
}

int InitMonster()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szFilePath[64];

	chrMonsterCnt = 0;

	ZeroMemory(chrMonsterList, sizeof(smCHAR_INFO) * CHR_MONSTER_MAX);
	ZeroMemory(chrMonInfoList, sizeof(smCHAR_MONSTER_INFO) * CHR_MONSTER_MAX);

	lstrcpy(szFindPath, MonsterPath);
	lstrcat(szFindPath, "*.inf");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE) {
		while (1) {
			lstrcpy(szFilePath, MonsterPath);
			lstrcat(szFilePath, fd.cFileName);

			smCharDecode(szFilePath, &chrMonsterList[chrMonsterCnt], &chrMonInfoList[chrMonsterCnt], 0);

			chrMonInfoList[chrMonsterCnt].dwAutoCharCode = GetSpeedSum(chrMonsterList[chrMonsterCnt].szName);

			if (rsServerConfig.TestSeverMode) {
				chrMonsterList[chrMonsterCnt].Exp *= 4;
				chrMonInfoList[chrMonsterCnt].GetExp *= 4;
			}

			ReformCharForm(&chrMonsterList[chrMonsterCnt]);

			chrMonsterCnt++;

			if (FindNextFile(hFindHandle, &fd) == FALSE) break;
			if (chrMonsterCnt >= CHR_MONSTER_MAX) break;
		}
	}
	FindClose(hFindHandle);

	int cnt, cnt2;

	rsInitHardCoreEvent();

	for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
		if (chrMonsterList[cnt].szModelName[0]) {
			LoadOftenMeshPattern(chrMonsterList[cnt].szModelName);
		}

		if (lstrcmp(chrMonsterList[cnt].szName, srEventMonName1) == 0) {
			chrNpcMonsterInfo = &chrMonsterList[cnt];
		}

		for (cnt2 = 0; cnt2 < srCRISTAL_MAX; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonster[cnt2].szName) == 0) {
				srCristalMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}
		for (cnt2 = 0; cnt2 < srCRISTAL_MAX; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterBoss[cnt2].szName) == 0) {
				srCristalMonsterBoss[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}
		for (cnt2 = 0; cnt2 < srSKILL_MONSTER_MAX; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srSkillMonster[cnt2].szName) == 0) {
				srSkillMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}
		for (cnt2 = 0; cnt2 < srBC_MONSTER_TOTAL; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srBillingCrystalMonster[cnt2].szName) == 0) {
				srBillingCrystalMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy[cnt2].szName) == 0) {
				srCristalMonsterEnemy[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy2[cnt2].szName) == 0) {
				srCristalMonsterEnemy2[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy3[cnt2].szName) == 0) {
				srCristalMonsterEnemy3[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy4[cnt2].szName) == 0) {
				srCristalMonsterEnemy4[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy5[cnt2].szName) == 0) {
				srCristalMonsterEnemy5[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy6[cnt2].szName) == 0) {
				srCristalMonsterEnemy6[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy7[cnt2].szName) == 0) {
				srCristalMonsterEnemy7[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy8[cnt2].szName) == 0) {
				srCristalMonsterEnemy8[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < 7; cnt2++) {
			if (lstrcmp(chrMonsterList[cnt].szName, srCristalMonsterEnemy9[cnt2].szName) == 0) {
				srCristalMonsterEnemy9[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		for (cnt2 = 0; cnt2 < MARVELCRISTAL_MAX; cnt2++)
		{
			if (lstrcmp(chrMonsterList[cnt].szName, srMarvelCristalMonster[cnt2].szName) == 0)
			{
				srMarvelCristalMonster[cnt2].lpCharInfo = &chrMonsterList[cnt];
			}
		}

		if (chrMonsterList[cnt].wPlayClass[0] == MONSTER_CLASS_HAMMER) {
			if (srHammerMonsterCount < srHAMMER_MONSTER_MAX)
				srCharInfo_HammerMonster[srHammerMonsterCount++] = &chrMonsterList[cnt];
		}

		if (chrMonInfoList[cnt].szName[0] && !chrMonsterList[cnt].szName[0]) {
			lstrcpy(chrMonsterList[cnt].szName, chrMonInfoList[cnt].szName);
			chrMonInfoList[cnt].szName[0] = 0;
		}
	}

	return TRUE;
}

int ConvertMonsterNames()
{
	int cnt;

	for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
		if (chrMonInfoList[cnt].szName[0] && chrMonsterList[cnt].szName[0]) {
			lstrcpy(chrMonsterList[cnt].szName, chrMonInfoList[cnt].szName);
			chrMonInfoList[cnt].szName[0] = 0;
		}
	}

	return TRUE;
}

char* szUserModelPath = "char\\tmABCD";

int rsCheckActiveFile(char* szFile)
{
	WIN32_FIND_DATA	fd;
	HANDLE	hFindHandle;

	hFindHandle = FindFirstFile(szFile, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE) return FALSE;
	FindClose(hFindHandle);

	int cnt, len;
	char szFileName[128];

	len = lstrlen(szFile);
	memcpy(szFileName, szFile, len + 1);

	for (cnt = len - 1; cnt >= 0; cnt--) {
		if (szFileName[cnt] == '\\') {
			szFileName[cnt] = 0;
			break;
		}
	}

	if (lstrcmpi(szFileName, szUserModelPath) != 0)
		return FALSE;

	return TRUE;
}

int InitItems()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szFindPath[64];
	char	szFilePath[64];
	sDEF_ITEMINFO	DefItem;

	DefaultItemCount = 0;

	lstrcpy(szFindPath, ItemPath);
	lstrcat(szFindPath, "*.txt");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE)
	{
		while (1)
		{
			lstrcpy(szFilePath, ItemPath);
			lstrcat(szFilePath, fd.cFileName);

			DecodeItemInfo(szFilePath, &DefaultItems[DefaultItemCount]);

			memcpy(&DefItem, &DefaultItems[DefaultItemCount], sizeof(sDEF_ITEMINFO));
			SetLowerItem(&DefItem);

			DefItem.Item.BackUpKey = 0;
			DefItem.Item.BackUpChkSum = 0;
			DefItem.Item.dwCreateTime = 0;

			DefaultItems[DefaultItemCount].DefCompressDataLen =
				EecodeCompress((BYTE*)&DefItem.Item, (BYTE*)DefaultItems[DefaultItemCount].DefCompressData, sizeof(sITEMINFO));

#ifdef _LANGUAGE_CHINESE
			if (DefaultItems[DefaultItemCount].Item.CODE == 0x6010500)
			{
				for (int i = 9; i < 32; i++)
				{
					DefaultItems[DefaultItemCount].Item.ItemName[i] = 0;
				}
			}
#endif

			DefaultItemCount++;

			if (FindNextFile(hFindHandle, &fd) == FALSE) break;
			if (DefaultItemCount >= DEF_ITEM_MAX) break;
		}
	}
	FindClose(hFindHandle);

	return TRUE;
}

char* SetFieldInfoPath(char* SaveBuff, char* szFieldPath, char* InfoExt)
{
	int cnt;
	int len;
	char* szFile;

	len = lstrlen(szFieldPath);
	cnt = len - 1;

	szFile = szFieldPath;

	while (cnt > 0) {
		if (szFieldPath[cnt] == '\\') {
			szFile = &szFieldPath[cnt + 1];
			break;
		}
		cnt--;
	}

	wsprintf(SaveBuff, "%s%s.%s", szFieldInfoPath, szFile, InfoExt);

	return SaveBuff;
}

extern int AgingOkPercent[20];
extern int AgingStoneAgingOkPercent[20];

extern int SuperAgingStoneAgingFailPercent[20];
extern int SuperAgingStone1_5AgingFailPercent[20];

DWORD	dwServ_GameTimeHour;
DWORD	dwServ_NightDay;

DWORD	GetGameTimeHour()
{
	DWORD	dwTime;

	dwTime = GetCurrentTime() - dwOffsetTime;
	dwTime = (dwTime / GAME_WORLDTIME_MIN) / 60;
	dwTime = dwTime - (((int)(dwTime / 24)) * 24);

	return dwTime;
}

int rsGetUserCounter(int Counter)
{
	return Counter;
}

#define START_POINT_MAX			8
#define START_POINT_MASK		(START_POINT_MAX-1)

POINT	StartPointNpc[START_POINT_MAX] = {
	{ 1692 , -584 },
	{ 34 , -618 },
	{ -741 , 877 },
	{ 1000 , 1000 }
};

POINT	StartPoint[START_POINT_MAX] = {
	{	-1500,	-2800 },
	{	600,	-3200 },
	{	840,	-4000 },
	{	-90,	-5000 },
	{	-900,	-6500 },
	{	-1600,	-7100 },
	{	-3000,	-7200 },
	{	400,	-6100 }
};

int StartPointCnt = 0;

int	rsLoadCreateItemToHDD(psITEM* lpItem, char* szFileCode);

int	rsSaveCreateItemToHDD(psITEM* lpItem);

int	rsSaveAgingItemToHDD(sITEMINFO* lpItem);

void SendNextBoss(rsPLAYINFO* Player, int MapID);

int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	va_list vl;

	char szMessage[2048];

	va_start(vl, msg);
	_vsnprintf_s(szMessage, _countof(szMessage), _TRUNCATE, msg, vl);
	va_end(vl);

	lstrcpy(TransChatMessage.szMessage, szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = Color;
	TransChatMessage.dwObjectSerial = 0;

	if (lpPlayInfo->lpsmSock)
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	return TRUE;
}

int	rsSendServerChatMessageToAllUser(int Color, char* msg, ...)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	va_list vl;

	char szMessage[2048];

	va_start(vl, msg);
	_vsnprintf_s(szMessage, _countof(szMessage), _TRUNCATE, msg, vl);
	va_end(vl);

	lstrcpy(TransChatMessage.szMessage, szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = Color;
	TransChatMessage.dwObjectSerial = 0;

	for (int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (rsPlayInfo[cnt].lpsmSock)
		{
			rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		}
	}

	return TRUE;
}

rsPLAYINFO* srFindUserFromSerial(DWORD dwObjectSerial)
{
	int cnt;

	if (dwObjectSerial == 0) return NULL;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial == dwObjectSerial) {
			return &rsPlayInfo[cnt];
		}
	}

	return NULL;
}

smCHAR* srFindCharFromSerial(DWORD dwObjectSerial)
{
	int cnt;

	if (dwObjectSerial == 0) return NULL;

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].dwObjectSerial == dwObjectSerial &&
			chrAutoPlayer[cnt].Flag) {
			return &chrAutoPlayer[cnt];
		}
	}

	return NULL;
}

smCHAR* srFindCharFromSerial(DWORD dwObjectSerial, int AreaNum)
{
	int cnt;
	STG_AREA* lpStgArea;

	if (dwObjectSerial && AreaNum < STAGE_AREA_MAX && StageArea[AreaNum].lpStage) {
		lpStgArea = &StageArea[AreaNum];

		for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++) {
			if (lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->dwObjectSerial == dwObjectSerial) {
				return lpStgArea->lpCharMonster[cnt];
			}
		}
	}

	return NULL;
}

smCHAR* srFindEmptyChar()
{
	int cnt;

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (!chrAutoPlayer[cnt].Flag) {
			return &chrAutoPlayer[cnt];
		}
	}

	return NULL;
}

int srSetItemFromCodeJobCode(psITEM* lpsItem, char* szCoed, int JobCode)
{
	int cnt;
	DWORD dwCode;
	DWORD dwCodeMask1, dwCodeMask2;

	for (cnt = 0; cnt < MAX_ITEM; cnt++)
	{
		if (lstrcmpi(szCoed, sItem[cnt].LastCategory) == 0)
		{
			dwCode = sItem[cnt].CODE; break;
		}
	}

	if (cnt >= MAX_ITEM) return FALSE;

	for (cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if (DefaultItems[cnt].Item.CODE == dwCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt], JobCode, spItemNormal);

			if (spTimeAdjust)
			{
				dwCodeMask1 = lpsItem->ItemInfo.CODE & sinITEM_MASK2;
				dwCodeMask2 = lpsItem->ItemInfo.CODE & sinITEM_MASK3;
				if ((dwCodeMask1 == sinDA1 || dwCodeMask1 == sinDA2) && dwCodeMask2 >= sin31)
				{
					ReformItem_AdjustTime(&lpsItem->ItemInfo, spTimeAdjust);
				}

				if ((dwCodeMask1 == sinOA1 && dwCodeMask2 == sin32) || (dwCodeMask1 == sinOR2 && dwCodeMask2 == sin27) ||
					(dwCodeMask1 == sinOA1 && dwCodeMask2 == sin33) || (dwCodeMask1 == sinOR2 && dwCodeMask2 == sin28))
				{
					ReformItem_AdjustTime(&lpsItem->ItemInfo, spTimeAdjust);
				}
			}

			rsSaveCreateItemToHDD(lpsItem);
			return TRUE;
		}
	}

	return FALSE;
}

int srSetItemFromCode(psITEM* lpsItem, char* szCoed)
{
	int cnt;
	DWORD dwCode;
	DWORD dwCodeMask1, dwCodeMask2;

	for (cnt = 0; cnt < MAX_ITEM; cnt++) {
		if (lstrcmpi(szCoed, sItem[cnt].LastCategory) == 0) {
			dwCode = sItem[cnt].CODE; break;
		}
	}

	if (cnt >= MAX_ITEM) return FALSE;

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (DefaultItems[cnt].Item.CODE == dwCode && !DefaultItems[cnt].Item.UniqueItem) {
			CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt], spJobCode, spItemNormal);

			if (spTimeAdjust) {
				dwCodeMask1 = lpsItem->ItemInfo.CODE & sinITEM_MASK2;
				dwCodeMask2 = lpsItem->ItemInfo.CODE & sinITEM_MASK3;
				if ((dwCodeMask1 == sinDA1 || dwCodeMask1 == sinDA2) && dwCodeMask2 >= sin31) {
					ReformItem_AdjustTime(&lpsItem->ItemInfo, spTimeAdjust);
				}

				if ((dwCodeMask1 == sinOA1 && dwCodeMask2 == sin32) || (dwCodeMask1 == sinOR2 && dwCodeMask2 == sin27) ||
					(dwCodeMask1 == sinOA1 && dwCodeMask2 == sin33) || (dwCodeMask1 == sinOR2 && dwCodeMask2 == sin28))
				{
					ReformItem_AdjustTime(&lpsItem->ItemInfo, spTimeAdjust);
				}
			}

			rsSaveCreateItemToHDD(lpsItem);
			return TRUE;
		}
	}

	return FALSE;
}

int srSetItemFromName(psITEM* lpsItem, char* szItemName)
{
	int cnt;

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (lstrcmpi(DefaultItems[cnt].Item.ItemName, szItemName) == 0) {
			CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt], spJobCode, spItemNormal);

			rsSaveCreateItemToHDD(lpsItem);
			return TRUE;
		}
	}

	return FALSE;
}

int srSetItemFromLogData(psITEM* lpsItem, char* LogFileCode)
{
	return rsLoadCreateItemToHDD(lpsItem, LogFileCode);
}

int srLinkNpcItem(smCHAR* lpChar)
{
	int cnt, cnt2;
	DWORD	dwCode;

	for (cnt = 0; cnt < lpChar->smMonsterInfo.SellAttackItemCount; cnt++) {
		dwCode = (DWORD)lpChar->smMonsterInfo.SellAttackItem[cnt];
		lpChar->smMonsterInfo.SellAttackItem[cnt] = 0;
		for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
			if (!DefaultItems[cnt2].Item.UniqueItem && dwCode == DefaultItems[cnt2].Item.CODE) {
				lpChar->smMonsterInfo.SellAttackItem[cnt] = &DefaultItems[cnt2];
				break;
			}
		}
	}

	for (cnt = 0; cnt < lpChar->smMonsterInfo.SellDefenceItemCount; cnt++) {
		dwCode = (DWORD)lpChar->smMonsterInfo.SellDefenceItem[cnt];
		lpChar->smMonsterInfo.SellDefenceItem[cnt] = 0;
		for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
			if (!DefaultItems[cnt2].Item.UniqueItem && dwCode == DefaultItems[cnt2].Item.CODE) {
				lpChar->smMonsterInfo.SellDefenceItem[cnt] = &DefaultItems[cnt2];
				break;
			}
		}
	}

	for (cnt = 0; cnt < lpChar->smMonsterInfo.SellEtcItemCount; cnt++) {
		dwCode = (DWORD)lpChar->smMonsterInfo.SellEtcItem[cnt];
		lpChar->smMonsterInfo.SellEtcItem[cnt] = 0;
		for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
			if (!DefaultItems[cnt2].Item.UniqueItem && dwCode == DefaultItems[cnt2].Item.CODE) {
				lpChar->smMonsterInfo.SellEtcItem[cnt] = &DefaultItems[cnt2];
				break;
			}
		}
	}
	return TRUE;
}

int srGetRandomItem(psITEM* lpsItem)
{
	int	rnd;

	ZeroMemory(lpsItem, sizeof(sITEMINFO));

	if (((GetCurrentTime() >> 4) & 0x3) == 0) {
		rnd = GetRandomPos(1, 100);
		lpsItem->ItemInfo.CODE = sinGG1 | sin01;
		wsprintf(lpsItem->ItemInfo.ItemName, sinGold, rnd);
		lpsItem->ItemInfo.Money = rnd;
		ReformItem(&lpsItem->ItemInfo);
	}
	else {
		rnd = rand() % DefaultItemCount;
		if (DefaultItems[rnd].Item.UniqueItem) return FALSE;
		CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[rnd]);
	}

	return TRUE;
}

#define	OS_TRAN	(sinOS1|sin06)
#define	OS_MUKY	(sinOS1|sin07)
#define	OS_DEBI	(sinOS1|sin08)
#define	OS_ALL	(sinOS1|sin12)

DWORD	dwMorifFieldItem[] = {
	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,

	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,

	OS_TRAN,	OS_MUKY,	OS_MUKY,	OS_MUKY,

	OS_DEBI ,	OS_MUKY,	OS_MUKY,	OS_DEBI ,

	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN,

	OS_TRAN,	OS_TRAN,	OS_ALL , 	OS_ALL ,

	OS_DEBI,	OS_DEBI,	OS_ALL ,	OS_ALL ,

	OS_ALL,		OS_TRAN,	OS_TRAN,	OS_ALL,

	OS_TRAN,	OS_TRAN,	OS_TRAN,	OS_TRAN
};

int	srCheckMorifItemField(DWORD dwItemCode, STG_AREA* lpStgArea)
{
	DWORD	dwItemCodeMask = dwItemCode & sinITEM_MASK3;

	if (!lpStgArea || !lpStgArea->lpField) return FALSE;

	DWORD	dwAreaCode = lpStgArea->lpField->FieldCode;

	if (dwAreaCode >= 0 && dwAreaCode < 36) {
		if (dwMorifFieldItem[dwAreaCode] == OS_ALL && dwItemCodeMask < sin05)
			return FALSE;

		if (dwItemCodeMask > (dwMorifFieldItem[dwAreaCode] & sinITEM_MASK3))
			return FALSE;
	}

	return TRUE;
}

int srGetMonsterItem(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar, psITEM* lpsItem)
{
	int	rnd;
	int cnt, cnt2;
	int rcnt;
	DWORD dwCode;
	smCHAR_MONSTER_INFO* lpMonInfo = &lpChar->smMonsterInfo;
	STG_AREA* lpStgArea;

	ZeroMemory(lpsItem, sizeof(sITEMINFO));

	if (lpMonInfo->FallItemPerMax == 0 || lpMonInfo->FallItemCount == 0) return FALSE;

	if (rsServerConfig.Event_Mandoo) {
		rnd = rand() % 100;
		dwCode = 0;

		if (rnd < 4) {
			dwCode = (sinSP1 | sin01);
		}
		else {
			if (rnd < 6) {
				dwCode = (sinSP1 | sin02);
			}
		}

		if (dwCode) {
			for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
				if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					return TRUE;
				}
			}
		}
	}

	if (rsServerConfig.Event_ValentineDay) {
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8)) {
			rnd = rsServerConfig.Event_ValentineDay;
		}

		if (rnd < rsServerConfig.Event_ValentineDay) {
			dwCode = 0;
			rnd = rand() % 10;
			if (rnd < 7) {
				dwCode = (sinCH1 | sin01);

#ifdef _LANGUAGE_THAI_RING
				dwCode = (sinOR2 | sin01);
#endif
#ifdef _LANGUAGE_JAPANESE_RING
				dwCode = (sinOR2 | sin01);
#endif
			}
			else {
				dwCode = (sinCH1 | sin02);
#ifdef _LANGUAGE_THAI_RING
				dwCode = (sinOR2 | sin01);
#endif
#ifdef _LANGUAGE_JAPANESE_RING
				dwCode = (sinOR2 | sin01);
#endif
			}

			if (dwCode) {
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_CoupleRing)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_CoupleRing;
		}

		if (rnd < rsServerConfig.Event_CoupleRing)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin16);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_Watermelon)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_Watermelon;
		}

		if (rnd < rsServerConfig.Event_Watermelon)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin15);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_Star)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_Star;
		}

		if (rnd < rsServerConfig.Event_Star)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin26);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_Valentine)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15)
		{
			rnd = rsServerConfig.Event_Valentine;
		}

		if (rnd < rsServerConfig.Event_Valentine)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin35);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_PristonAlphabet)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_PristonAlphabet;
		}

		if (rnd < rsServerConfig.Event_PristonAlphabet)
		{
			dwCode = 0;
			rnd = rand() % 100;
			if (rnd < 15)
			{
				dwCode = (sinSP1 | sin27);
			}
			else if (rnd < 30)
			{
				dwCode = (sinSP1 | sin28);
			}
			else if (rnd < 44)
			{
				dwCode = (sinSP1 | sin29);
			}
			else if (rnd < 58)
			{
				dwCode = (sinSP1 | sin30);
			}
			else if (rnd < 72)
			{
				dwCode = (sinSP1 | sin31);
			}
			else if (rnd < 86)
			{
				dwCode = (sinSP1 | sin32);
			}
			else
				dwCode = (sinSP1 | sin33);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_WhiteContrast)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15)
		{
			rnd = rsServerConfig.Event_WhiteContrast;
		}

		if (rnd < rsServerConfig.Event_WhiteContrast)
		{
			dwCode = 0;
			rnd = rand() % 4;

			if (rnd == 0) dwCode = (sinPR2 | sin09);
			else if (rnd == 1) dwCode = (sinPR2 | sin10);
			else if (rnd == 2) dwCode = (sinPR2 | sin11);
			else dwCode = (sinDR1 | sin10);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_Candydays)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15)
		{
			rnd = rsServerConfig.Event_Candydays;
		}

		if (rnd < rsServerConfig.Event_Candydays)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin36);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_BlackSmith)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15)
		{
			rnd = rsServerConfig.Event_BlackSmith;
		}

		if (rnd < rsServerConfig.Event_BlackSmith)
		{
			dwCode = 0;
			rnd = rand() % 4;

			if (rnd == 0) dwCode = (sinPR2 | sin12);
			else if (rnd == 1) dwCode = (sinPR2 | sin13);
			else if (rnd == 2) dwCode = (sinPR2 | sin14);
			else dwCode = (sinDR1 | sin11);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_MagicalGreen)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15)
		{
			rnd = rsServerConfig.Event_MagicalGreen;
		}

		if (rnd < rsServerConfig.Event_MagicalGreen)
		{
			dwCode = 0;

			if (FieldLimitLevel_Table[lpPlayInfo->Position.Area] >= 60)
			{
				dwCode = (sinSP1 | sin38);
			}

			else
			{
				dwCode = (sinSP1 | sin37);
			}

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_TearOfKara)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15)
		{
			rnd = rsServerConfig.Event_TearOfKara;
		}

		if (rnd < rsServerConfig.Event_TearOfKara)
		{
			dwCode = 0;
			dwCode = (sinSP1 | sin39);

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_MovieBloodyBattle)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>7))
		{
			rnd = rsServerConfig.Event_PristonAlphabet;
		}

		if (rnd < rsServerConfig.Event_MovieBloodyBattle)
		{
			dwCode = 0;
			rnd = rand() % 100;
			if (rnd < 25)
			{
				dwCode = (sinSP1 | sin60);
			}
			else if (rnd < 50)
			{
				dwCode = (sinSP1 | sin61);
			}
			else if (rnd < 75)
			{
				dwCode = (sinSP1 | sin62);
			}
			else
			{
				dwCode = (sinSP1 | sin63);
			}

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_WhiteDay) {
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8)) {
			rnd = rsServerConfig.Event_WhiteDay;
		}

		if (rnd < rsServerConfig.Event_WhiteDay) {
			dwCode = 0;
			rnd = rand() % 10;
			if (rnd < 7) {
				dwCode = (sinCH1 | sin03);
			}
			else {
				dwCode = (sinCH1 | sin04);
			}

			if (dwCode) {
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_Puzzle && (rand() % 10000) < rsServerConfig.Event_Puzzle) {
		dwCode = rsOpenEventPuzzleItem(lpPlayInfo, lpChar);

		if (dwCode) {
			for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
				if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					return TRUE;
				}
			}
		}
	}

	if (rsServerConfig.Event_NineFox) {
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);
		cnt2 = rsServerConfig.Event_NineFox;

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>10)) {
			rnd = cnt2;
		}
		else {
			if (lpPlayInfo->smCharInfo.Level < 20) {
				cnt2 = (rsServerConfig.Event_NineFox * 40) / 100;
			}
			else if (lpPlayInfo->smCharInfo.Level < 40) {
				cnt2 = (rsServerConfig.Event_NineFox * 60) / 100;
			}
			else if (lpPlayInfo->smCharInfo.Level < 60) {
				cnt2 = (rsServerConfig.Event_NineFox * 80) / 100;
			}
		}

		if (rnd < cnt2) {
			if ((rand() % 2) == 0)
				dwCode = (sinGF1 | sin03);
			else
				dwCode = (sinGF1 | sin04);

			if (dwCode) {
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.EVENT_Christmas) {
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);
		cnt2 = rsServerConfig.EVENT_Christmas;

		if (cnt < 10) {
			cnt2 = rsServerConfig.EVENT_Christmas;
		}

		if (cnt < 10) {
			cnt2 = (rsServerConfig.EVENT_Christmas * 30) / 100;
		}

		if (rnd < cnt2) {
			dwCode = (sinGF1 | sin05);
			if (cnt > 10) { dwCode = 0; }

			if (dwCode) {
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (rsServerConfig.Event_GiftBox)
	{
		rnd = rand() % 10000;
		cnt = abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level);

		if (cnt > 15 || (lpChar->smCharInfo.Level < 20 && cnt>8))
		{
			rnd = rsServerConfig.Event_GiftBox;
		}

		if (rnd < rsServerConfig.Event_GiftBox)
		{
			dwCode = 0;
			if (lpChar->smCharInfo.Level >= 1 && lpChar->smCharInfo.Level < 20)
			{
				dwCode = (sinSP1 | sin10);
			}
			else if (lpChar->smCharInfo.Level >= 20 && lpChar->smCharInfo.Level < 40)
			{
				dwCode = (sinSP1 | sin09);
			}
			else if (lpChar->smCharInfo.Level >= 40 && lpChar->smCharInfo.Level < 60)
			{
				dwCode = (sinSP1 | sin08);
			}
			else if (lpChar->smCharInfo.Level >= 60 && lpChar->smCharInfo.Level < 80)
			{
				dwCode = (sinSP1 | sin07);
			}
			else if (lpChar->smCharInfo.Level >= 80 && lpChar->smCharInfo.Level < 100)
			{
				dwCode = (sinSP1 | sin06);
			}
			else if (lpChar->smCharInfo.Level >= 100)
			{
				dwCode = (sinSP1 | sin05);
			}

			if (dwCode)
			{
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++)
				{
					if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem)
					{
						CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
						return TRUE;
					}
				}
			}
		}
	}

	if (lpPlayInfo->Position.Area == rsACTION_FIELD)
	{
		rnd = rand() % 10000;

		if (rnd < 150) {
			dwCode = (sinGF1 | sin02);

			for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
				if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					return TRUE;
				}
			}
		}
	}

	dwCode = rsLowLevelItem(lpPlayInfo, lpChar);
	if (dwCode) {
		for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
			if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
				CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2], lpPlayInfo->smCharInfo.JOB_CODE);
				return TRUE;
			}
		}
	}

	rsSendAreaOpenKidMonster(lpPlayInfo, lpChar);

	if (lpPlayInfo->Position.Area == rsCASTLE_FIELD)
	{
		rsSendAreaOpenSODGuardMonster(lpPlayInfo, lpChar);
	}

	rnd = (rand() << 7) | ((GetCurrentTime() >> 2) & 0x7F);
	rnd = rnd % lpMonInfo->FallItemPerMax;

	if (!rsServerConfig.AreaServer.IP_Count) {
		if (!lpMonInfo->FallItems[0].dwItemCode && (rand() % 1000) < 10) return FALSE;
	}

	rcnt = 0;
	for (cnt = 0; cnt < lpMonInfo->FallItemCount; cnt++) {
		if (rnd >= rcnt && rnd < (rcnt + lpMonInfo->FallItems[cnt].Percentage)) {
			if (!lpMonInfo->FallItems[cnt].dwItemCode) return FALSE;

			if (lpMonInfo->FallItems[cnt].dwItemCode == (sinGG1 | sin01)) {
				rnd = GetRandomPos(lpMonInfo->FallItems[cnt].sPrice[0], lpMonInfo->FallItems[cnt].sPrice[1]);
				lpsItem->ItemInfo.CODE = sinGG1 | sin01;
				wsprintf(lpsItem->ItemInfo.ItemName, sinGold, rnd);
				lpsItem->ItemInfo.Money = rnd;
				ReformItem(&lpsItem->ItemInfo);
				rsMoneyTotalCount += rnd;
				return TRUE;
			}

			if (lpMonInfo->FallItems[cnt].dwItemCode == (sinGG1 | sin03))
			{
				rnd = GetRandomPos(lpMonInfo->FallItems[cnt].sPrice[0], lpMonInfo->FallItems[cnt].sPrice[1]);
				lpsItem->ItemInfo.CODE = sinGG1 | sin03;
				wsprintf(lpsItem->ItemInfo.ItemName, "%d Coins", rnd);
				lpsItem->ItemInfo.Money = rnd;
				ReformItem(&lpsItem->ItemInfo);
				rsCoinTotalCount += rnd;
				return TRUE;
			}

			dwCode = lpMonInfo->FallItems[cnt].dwItemCode;

			for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
				if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
					if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_NPC_MOLLYWOLF && (dwCode & sinITEM_MASK2) == sinFO1) {
						lpStgArea = (STG_AREA*)lpChar->lpExt1;
						if (lpStgArea->lpField && lpStgArea->lpField->State == FIELD_STATE_FOREST)
							return FALSE;
					}

					if (DefaultItems[cnt2].sGenDay[0] > 0) {
						if (DefaultItems[cnt2].sGenDay[0] <= DefaultItems[cnt2].sGenDay[1]) {
							return FALSE;
						}
						else {
							DefaultItems[cnt2].sGenDay[1]++;
						}
					}
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);

					rsSaveCreateItemToHDD(lpsItem);
					rsItemOpenCount++;
					return TRUE;
				}
			}
			return FALSE;
		}
		rcnt += lpMonInfo->FallItems[cnt].Percentage;
	}

	return FALSE;
}

DWORD ObjectSerialCnt = 0x2000;

DWORD GetNewObjectSerial()
{
	DWORD	code;

	code = (ObjectSerialCnt & 0x0FFFFFFF) | (rsServerConfig.ServerCode << 28);

	ObjectSerialCnt++;

	return code;
}

smCHAR_INFO* SetMonsterModelRandom(smCHAR_INFO* lpCharInfo)
{
	smCHAR_INFO* lpInfo;

	lpInfo = &chrMonsterList[(rand() % chrMonsterCnt)];
	memcpy(lpCharInfo, lpInfo, sizeof(smCHAR_INFO));

	return lpInfo;
}

STG_AREA* StageArea;

int OpenEventMonster(smCHAR_INFO* lpCharInfo, STG_AREA* lpStgArea)
{
	int cnt;
	int MonCnt;

	if (lpCharInfo->dwCharSoundCode == snCHAR_SOUND_HOPT) {
		if ((rand() % 100) > 30) return FALSE;

		MonCnt = 0;
		for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++) {
			if (lpStgArea->lpCharMonster[cnt]) {
				if (lpStgArea->lpCharMonster[cnt]->smCharInfo.dwCharSoundCode == snCHAR_SOUND_HOPYKING) {
					MonCnt++;
				}
			}
		}
		if (MonCnt >= 40) return FALSE;

		for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
			if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_HOPYKING) {
				memcpy(lpCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
				break;
			}
		}
	}

	return TRUE;
}

int	OpenEnemyMonsterFromCristal(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO* lpPlayInfo)
{
	return FALSE;
}

int	OpenMonsterFromCristal(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO* lpPlayInfo)
{
	return FALSE;
}

smCHAR* rsGetLinkChar(smCHAR* lpMasterChar)
{
	int cnt;

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag &&
			lpMasterChar != &chrAutoPlayer[cnt] &&
			chrAutoPlayer[cnt].lpLinkChar == lpMasterChar &&
			chrAutoPlayer[cnt].smCharInfo.Life[0] > 0) {
			if (!lpMasterChar->lpLinkPlayInfo || lpMasterChar->lpLinkPlayInfo == chrAutoPlayer[cnt].lpLinkPlayInfo)
				return &chrAutoPlayer[cnt];
		}
	}

	return NULL;
}

smCHAR* OpenMonsterFromSkill(DWORD SkillCode, int x, int y, int z, rsPLAYINFO* lpPlayInfo, smCHAR* lpEnemyChar)
{
	return NULL;
}

smCHAR* OpenMonster_QuestArena(rsPLAYINFO* lpPlayInfo, DWORD dwQuestCode, int Param = 0)
{
	STG_AREA* lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	int	len, cnt, pow;
	smCHAR* lpChar;
	DWORD	dwSndCode;
	int		OpenLevel = 0;

	switch (dwQuestCode) {
	case SIN_QUEST_CODE_CHANGEJOB4:
		if (lpPlayInfo->smCharInfo.JOB_CODE <= 4)
			dwSndCode = snCHAR_SOUND_NPC_SKILLMASTER;
		else
			dwSndCode = snCHAR_SOUND_NPC_MAGICMASTER;
		break;

	case HAQUEST_CODE_FURYOFPHANTOM:
		dwSndCode = snCHAR_SOUND_FURY;
		switch (Param)
		{
		case 1:
			OpenLevel = 118; break;
		case 2:
			OpenLevel = 119; break;
		case 3:
			OpenLevel = 120; break;
		}
	}

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag &&
			chrAutoPlayer[cnt].lpLinkPlayInfo == lpPlayInfo &&
			chrAutoPlayer[cnt].dwLinkObjectCode == lpPlayInfo->dwObjectSerial) {
			chrAutoPlayer[cnt].Close();
			((STG_AREA*)chrAutoPlayer[cnt].lpExt1)->MonsterCount--;
			((STG_AREA*)chrAutoPlayer[cnt].lpExt1)->DeleteMonTable(&chrAutoPlayer[cnt]);
		}
	}

	lpStgArea = &StageArea[QUEST_ARENA_FIELD];
	if (lpStgArea) {
		len = 0;

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
			if (chrMonsterList[cnt].dwCharSoundCode == dwSndCode && (OpenLevel == 0 || OpenLevel == chrMonsterList[cnt].Level)) {
				memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
				len++;
				break;
			}
		}

		if (len) {
			lpStgArea->EvnMonster = TRUE;
			lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
			if (lpChar) {
				lpChar->SetPosi(QUEST_ARENA_NPC_POS_X, 0, QUEST_ARENA_NPC_POS_Z, 0, 0, 0);
				lpChar->DistAroundDbl = 0;
				lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
				lpChar->TargetMoveCount = 0;
				lpChar->lpLinkPlayInfo = lpPlayInfo;
				lpChar->dwLinkObjectCode = lpPlayInfo->dwObjectSerial;
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 30 * 60 * 1000;

				pow = lpPlayInfo->smCharInfo.Level - 60;
				if (pow < 0) pow = 0;
				pow += pow / 2;

				lpChar->smCharInfo.Life[0] += (lpChar->smCharInfo.Life[0] * pow) / 100;
				if (lpChar->smCharInfo.Life[0] < 0 || lpChar->smCharInfo.Life[0]>30000) lpChar->smCharInfo.Life[0] = 30000;
				lpChar->smCharInfo.Life[1] = lpChar->smCharInfo.Life[0];

				lpChar->smCharInfo.Attack_Damage[0] += (lpChar->smCharInfo.Attack_Damage[0] * pow) / 100;
				lpChar->smCharInfo.Attack_Damage[1] += (lpChar->smCharInfo.Attack_Damage[1] * pow) / 100;

				lpChar->smMonsterInfo.SkillDamage[0] += (lpChar->smMonsterInfo.SkillDamage[0] * pow) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] += (lpChar->smMonsterInfo.SkillDamage[1] * pow) / 100;

				lpChar->smMonsterInfo.PotionCount += 3;

				return lpChar;
			}
		}
	}

	return NULL;
}

smCHAR* OpenMonsterFromName(char* szName, int x, int y, int z, rsPLAYINFO* lpPlayInfo = 0)
{
	STG_AREA* lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	int	len, cnt;
	smCHAR* lpChar;

	lpStgArea = FindStageField(x, z);
	if (lpStgArea) {
		len = 0;

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		if (szName && szName[0]) {
			for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
				if (lstrcmp(chrMonsterList[cnt].szName, szName) == 0) {
					memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
					len++;
					break;
				}
			}
		}

		if (len) {
			lpStgArea->EvnMonster = TRUE;
			lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
			if (lpChar) {
				lpChar->pX = x;
				lpChar->pY = y;
				lpChar->pZ = z;
				lpChar->DistAroundDbl = 0;
				lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
				lpChar->TargetMoveCount = 0;
				if (lpPlayInfo) {
					lpChar->lpMasterPlayInfo = lpPlayInfo;
					lpChar->smMonsterInfo.dwAutoCharCode = 0;

					lpChar->smCharInfo.Brood = smCHAR_MONSTER_USER;
					lstrcpy(lpChar->smCharInfo.szModelName2 + 1, lpPlayInfo->smCharInfo.szName);
					lpChar->smCharInfo.Next_Exp = lpPlayInfo->dwObjectSerial;
					lpChar->dwUpdateCharInfoTime = dwPlayServTime + 4 * 60 * 1000;
				}

				return lpChar;
			}
		}
	}

	return FALSE;
}

int rsGetMonCountFlag(smCHAR* lpChar)
{
	STG_AREA* lpStgArea;
	if (!lpChar->lpExt1) return -1;

	lpStgArea = (STG_AREA*)lpChar->lpExt1;

	return lpStgArea->StartPointMonCount[lpChar->OpenStartPostion];
}

smCHAR* rsOpenSubMonster(smCHAR* lpMainChar, DWORD dwCharSoundCode, int x, int y, int z, int MaxFlag)
{
	STG_AREA* lpStgArea;
	STG_CHAR_INFO StgCharInfo;
	int	len, cnt;
	smCHAR* lpChar;
	smCHAR_INFO* lpCharInfo;

	if (!lpMainChar->lpExt1) return FALSE;

	lpStgArea = (STG_AREA*)lpMainChar->lpExt1;

	if (lpStgArea->StartPointMonCount[lpMainChar->OpenStartPostion] >= MaxFlag) return FALSE;

	if (lpStgArea) {
		len = 0;

		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		lpCharInfo = 0;

		for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
			if (chrMonsterList[cnt].dwCharSoundCode == dwCharSoundCode) {
				memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
				len++;
				break;
			}
		}

		if (len) {
			lpChar = srFindEmptyChar();
			if (!lpChar) return NULL;

			lpChar->Init();
			lpChar->lpStage = lpMainChar->lpStage;
			lpChar->SetPosi(x, y, z, lpMainChar->Angle.x, lpMainChar->Angle.y, lpMainChar->Angle.z);

			lpChar->PosiAround.x = x;
			lpChar->PosiAround.y = lpChar->pY;
			lpChar->PosiAround.z = y;
			lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;

			lpChar->OpenStartPostion = lpMainChar->OpenStartPostion;

			lpStgArea->MonsterCount++;
			lpChar->lpExt1 = lpStgArea;
			lpChar->dwObjectSerial = GetNewObjectSerial();
			lpChar->ActionPattern = 5;
			memcpy(&lpChar->smCharInfo, &StgCharInfo.smCharInfo, sizeof(smCHAR_INFO));
			memcpy(&lpChar->smMonsterInfo, StgCharInfo.smCharInfo.lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
			lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);

			lpChar->smCharInfo.StatePoint = StgCharInfo.smCharInfo.lpMonInfo->ClassCode;

			lpChar->DistAroundDbl = 0;
			lpChar->AttackUserFlag = 0;
			lpChar->lpExt2 = 0;

			lpChar->lpExpAttackPlayInfo = 0;
			lpChar->ExpAttackLife = 0;

			lpStgArea->AddMonTable(lpChar);
			lpChar->ReopenCount = REOPEN_COUNT_NUM;
			lpChar->dwLastTransTime = dwPlayServTime;

			if (lpChar->smMonsterInfo.PotionCount) {
				if ((rand() % 100) < lpChar->smMonsterInfo.PotionPercent) {
					lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
				}
				else {
					lpChar->smMonsterInfo.PotionCount = 0;
				}
			}

#ifdef	_LANGUAGE_JAPANESE
			if (rsDamgeOffEvent)
			{
				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * ATTACK_RATE) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * ATTACK_RATE) / 100;
				if (lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * ATTACK_RATE) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * ATTACK_RATE) / 100;
				}
			}
#else

			if (rsDamgeOffEvent1)
			{
				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 75) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 75) / 100;
				if (lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 75) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 75) / 100;
				}
			}

			if (rsDamgeOffEvent2)
			{
				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 50) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 50) / 100;
				if (lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 50) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 50) / 100;
				}
			}
#endif

			if (rsDefenseOffEvent)
			{
				lpChar->smCharInfo.Defence = (lpChar->smCharInfo.Defence * DEFENSE_RATE) / 100;
			}
			rsMonOpenCount++;

			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;

			return lpChar;
		}
	}

	return FALSE;
}

POINT3D	rsHardCoreEventOpenPos[7][3] = {
	{
		{ 18967,  1154,	3055 },
		{ 19995,  1154,	2134 },
		{ 19485,  1154,	2615 }
	},
	{
		{ 20838,  1154,	3024 },
		{ 21671,  1154,	2193 },
		{ 21255,  1154,	2615 }
	},
	{
		{ 22478,  1154,	3049 },
		{ 23437,  1154,	2135 },
		{ 22948,  1154,	2615 }
	},
	{
		{ 24204,  1154,	3094 },
		{ 25173,  1154,	2135 },
		{ 24674,  1154,	2615 }
	},

	{
		{ 20509,  1621,	5284 },
		{ 21544,  1621,	4261 },
		{ 21012,  1621,	4773 }
	},
	{
		{ 22575,  1621,	5253 },
		{ 23610,  1621,	4230 },
		{ 23077,  1621,	4742 }
	},

	{
		{ 21538,  1638,	7057 },
		{ 22527,  1638,	6079 },
		{ 22018,  1638,	6569 }
	}
};

int	rsSod_RoundTable[8][2] = {
	{	0,	4	},
	{	0,	4	},
	{	0,	4	},
	{	4,	6	},
	{	4,	6	},
	{	4,	6	},
	{	6,	7	},
	{	6,	7	}
};

int	rsSod_RoundRoomTable[4][8] = {
	{	0,	0,	0,	4,	4,	4,	6,	6	},
	{	1,	1,	1,	4,	4,	4,	6,	6	},
	{	2,	2,	2,	5,	5,	5,	6,	6	},
	{	3,	3,	3,	5,	5,	5,	6,	6	}
};

int rsHardCoreEventArea[4] = { 18516 , 25715, 1541 , 7178 };

int	rsHardCoreEventInterLineZ = -32 * fONE;
int	rsHardCoreEventInterLineZ2 = -64 * fONE;
int	rsHardCoreEventPosY = (950 - 32) * fONE;
int	rsHardCoreEventOutLineZ = -600 * fONE;
int	rsHardCoreEvent_TicketHour = 4;

DWORD	dwHardCoreEvent_OutTime;

int	rsEventTicketCount;
int	rsEventTicketLevel[4];

int	rsHardCoreEventMode = 0;
int	rsHardCoreEventTimeOver = 0;

#define	rsEVENT_TICKET_LEVEL_TOTAL		549

struct	sSOD_USER {
	rsPLAYINFO* lpPlayInfo;
	DWORD		dwConnCode;
	DWORD		Temp[4];
};

#define	rsSOD_USER_MAX	120
#define	rsSOD_UPDATE_TIME	6000

sSOD_USER	rsSodUser[rsSOD_USER_MAX];
int	rsSodUserCount;
DWORD	rsTransSodTime = 0;
DWORD	dwSoD_DelayTime = 0;

int	rsSodTeamScore[4];
int	rsSodTeamRank[4];

int	rsInitHardCoreEvent()
{
	return TRUE;
}
int rsHardCoreEvent_OpenMonster(STG_AREA* lpStgArea, STG_CHAR_INFO* lpStgCharInfo)
{
	return TRUE;
}

int rsShowHardCoreEventScore(rsPLAYINFO* lpPlayInfo)
{
	return TRUE;
}

int rsCheckHardCoreEventArea(int x, int y, int z)
{
	int mx, my, mz;

	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if (y >= rsHardCoreEventOpenPos[0][0].y - 32) {
		if (rsHardCoreEventArea[0]<mx && rsHardCoreEventArea[1]>mx &&
			rsHardCoreEventArea[2]<mz && rsHardCoreEventArea[3]>mz) {
			return TRUE;
		}
	}

	return FALSE;
}

int rsGetSoD_AreaCode(int x, int y, int z)
{
	int mx, my, mz;
	int cnt;

	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if (y >= rsHardCoreEventOpenPos[0][0].y - 32) {
		if (rsHardCoreEventArea[0]<mx && rsHardCoreEventArea[1]>mx &&
			rsHardCoreEventArea[2]<mz && rsHardCoreEventArea[3]>mz) {
			for (cnt = 0; cnt < 7; cnt++) {
				if (mx > rsHardCoreEventOpenPos[cnt][0].x && mx<rsHardCoreEventOpenPos[cnt][1].x &&
					mz>rsHardCoreEventOpenPos[cnt][1].z && mz < rsHardCoreEventOpenPos[cnt][0].z) {
					return cnt;
				}
			}
		}
	}

	return -1;
}

WORD	wLastCheckDay = 0;
WORD	wLastCheckHour = 0;
WORD	wLastCheckMin = 0;
static	int EventBossMonsterFlag = 0;
DWORD	dwEventBossMonterTime = 0;
int		OpenBossTimeMin = 1;

int EventMonsterTime()
{
	SYSTEMTIME	st;

	int cnt, cnt2, cnt3;

	GetLocalTime(&st);

	EventMonster = FALSE;

	if (wLastCheckHour != st.wHour && st.wHour == rsBLESSCASTLE_TAX_TIME) {
		rsBlessCastle.Tax = rsBlessCastle.NextTax;
		rsBlessCastle.SelectedSkill = rsBlessCastle.BlessCastleSetup.ClanSkill;
	}

	if (rsServerConfig.sBlessCastle_StartTime[0] && rsServerConfig.sBlessCastle_StartTime[1]) {
		if (rsServerConfig.BlessCastleMode) {
			if (!rsBlessCastle.CastleMode && wLastCheckHour != st.wHour &&
				st.wDayOfWeek == rsServerConfig.sBlessCastle_StartTime[0] &&
				st.wHour == rsServerConfig.sBlessCastle_StartTime[1])
			{
				rsStart_CombatCastle();
			}
		}

		if (wLastCheckMin == 29 && st.wMinute == 30 &&
			st.wDayOfWeek == rsServerConfig.sBlessCastle_StartTime[0] &&
			st.wHour == rsServerConfig.sBlessCastle_StartTime[1] - 1)
		{
			rsSetNoticeMessage(srBlessCastle_LeagueMsg_04);
		}
		if (wLastCheckHour == rsServerConfig.sBlessCastle_StartTime[1] - 2 &&
			st.wDayOfWeek == rsServerConfig.sBlessCastle_StartTime[0] &&
			st.wHour == rsServerConfig.sBlessCastle_StartTime[1] - 1)
		{
			rsSetNoticeMessage(srBlessCastle_LeagueMsg_05);
		}
	}

	if (rsServerConfig.Event_HardCore == 2) {
		rsHardCoreEventMode = TRUE;
	}
	else {
		rsHardCoreEventMode = FALSE;
#ifndef		_LANGUAGE_ENGLISH
#ifdef	_LANGUAGE_JAPANESE
		if (st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			rsHardCoreEventMode = TRUE;
		}
		else {
			if (st.wHour >= 14 || st.wHour < 2) {
				rsHardCoreEventMode = TRUE;
			}
		}
#else
#ifdef _LANGUAGE_CHINESE
		if (st.wDayOfWeek >= 0 && st.wDayOfWeek <= 6)
		{
			if (st.wHour >= 20 && st.wHour < 22)
			{
				rsHardCoreEventMode = TRUE;
			}
			else
			{
				rsHardCoreEventMode = FALSE;
			}
		}
		else
		{
			rsHardCoreEventMode = FALSE;
		}

#else
#ifdef _LANGUAGE_VEITNAM
		if (st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			if (st.wHour >= 7 || st.wHour < 3)
				rsHardCoreEventMode = TRUE;
		}
		else {
			if (st.wHour >= 8 || st.wHour < 2)
				rsHardCoreEventMode = TRUE;
		}
#else
#ifdef _LANGUAGE_BRAZIL
		if (st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			rsHardCoreEventMode = TRUE;
		}
		else {
			if (st.wHour >= 14 || st.wHour < 4)
				rsHardCoreEventMode = TRUE;
		}
#else

		if (st.wHour >= 0 && st.wHour < 6) {
			rsHardCoreEventMode = TRUE;
		}
		else if (st.wHour >= 12 && st.wHour < 18) {
			rsHardCoreEventMode = TRUE;
		}
#endif
#endif
#endif
#endif
#else
#ifdef _LANGUAGE_PHILIPIN
		if (st.wHour >= 20 || st.wHour < 2)	rsHardCoreEventMode = TRUE;
		else if (st.wHour >= 13 && st.wHour < 19)		rsHardCoreEventMode = TRUE;
#else

		if (st.wHour >= 0 && st.wHour < 6) {
			rsHardCoreEventMode = TRUE;
		}
		else if (st.wHour >= 12 && st.wHour < 18) {
			rsHardCoreEventMode = TRUE;
		}
#endif
#endif
	}

#ifdef _LANGUAGE_JAPANESE

	if (rsServerConfig.Event_DamageOff) {
		rsDamgeOffEvent = TRUE;

		if (rsServerConfig.Event_DamageOff == 2) rsDamgeOffEvent = TRUE;
	}
	else
		rsDamgeOffEvent = FALSE;

#else
#ifdef _LANGUAGE_PHILIPIN

	if (rsServerConfig.Event_DamageOff1) rsDamgeOffEvent1 = TRUE;
	else  rsDamgeOffEvent1 = FALSE;

	if (rsServerConfig.Event_DamageOff2) rsDamgeOffEvent2 = TRUE;
	else  rsDamgeOffEvent2 = FALSE;
#else

	if (rsServerConfig.Event_DamageOff)
	{
		rsDamgeOffEvent = TRUE;

		if (rsServerConfig.Event_DamageOff == 2) rsDamgeOffEvent = TRUE;
	}
	else
		rsDamgeOffEvent = FALSE;
#endif
#endif

	if (rsServerConfig.Event_DamageOff1 == 2) rsDamgeOffEvent1 = TRUE;
	if (rsServerConfig.Event_DamageOff2 == 2) rsDamgeOffEvent2 = TRUE;

	if (rsServerConfig.Event_DefenseOff)
	{
		if ((st.wHour >= 0 && st.wHour < 6) || st.wHour >= 12 && st.wHour < 18)
		{
			rsDefenseOffEvent = TRUE;
		}
		else
		{
			rsDefenseOffEvent = FALSE;
		}

		if (rsServerConfig.Event_DefenseOff == 2) rsDefenseOffEvent = TRUE;
	}
	else
		rsDefenseOffEvent = FALSE;

	if (rsServerConfig.Event_Cristal)
	{
		if (st.wDayOfWeek != 0 || st.wDayOfWeek != 6)
		{
			if ((st.wHour >= 12 && st.wHour <= 23) || rsServerConfig.Event_Cristal == 2)
			{
				rsCristalEvent = TRUE;
			}
			else
			{
				rsCristalEvent = FALSE;
			}
		}
		else if (st.wDayOfWeek == 0 || st.wDayOfWeek == 6)
		{
			rsCristalEvent = TRUE;
		}
		else
		{
			rsCristalEvent = FALSE;
		}
	}
	else
		rsCristalEvent = FALSE;

	if (wLastCheckDay != st.wDay) {
		for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
			if (DefaultItems[cnt2].sGenDay[0]) {
				DefaultItems[cnt2].sGenDay[1] = 0;
			}
		}
		wLastCheckDay = st.wDay;
		OpenBossTimeMin = (rand() % 45) + 1;

		if (rsServerConfig.ExpGameTimeMode) {
			for (cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwExpGameTime)
					rsPlayInfo[cnt].dwExpGameTime = 0;
			}
		}
	}

	if (!EventBossMonsterFlag && st.wMinute == OpenBossTimeMin)
	{
		for (cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
		{
			if (StageArea[cnt].lpStage)
			{
				if (StageArea[cnt].rsMonsterList.BossMonsterCount > 0)
				{
					for (cnt2 = 0; cnt2 < StageArea[cnt].rsMonsterList.BossMonsterCount; cnt2++)
					{
						for (cnt3 = 0; cnt3 < StageArea[cnt].rsMonsterList.sBossMonsters[cnt2].OpenTimeCount; cnt3++)
						{
							if (st.wHour == StageArea[cnt].rsMonsterList.sBossMonsters[cnt2].bOpenTime[cnt3])
							{
								rsOpenBossMonster(&StageArea[cnt], &StageArea[cnt].rsMonsterList.sBossMonsters[cnt2]);
								break;
							}
						}
					}
				}
			}
		}
		EventBossMonsterFlag = TRUE;
		dwEventBossMonterTime = dwPlayServTime;
	}
	else {
		if (EventBossMonsterFlag && st.wMinute != OpenBossTimeMin) {
			EventBossMonsterFlag = 0;
		}
	}

	wLastCheckHour = st.wHour;
	wLastCheckMin = st.wMinute;

	return TRUE;
}

STG_AREA::STG_AREA()
{
	ZeroMemory(&Head, sizeof(STG_AREA));
}

int STG_AREA::Close()
{
	if (lpStageCharInfo) { delete lpStageCharInfo; lpStageCharInfo = 0; }
	if (lpStage) { delete lpStage; lpStage = 0; }

	return TRUE;
}

smTRNAS_PLAYERINFO* STG_AREA::FindCharInfoFixed(smTRNAS_PLAYERINFO* lpTransPlayerInfo)
{
	int cnt;

	if (lpTransPlayerInfo) {
		for (cnt = 0; cnt < FIX_CHAR_MAX; cnt++) {
			if (TransCharFixed[cnt].code &&
				TransCharFixed[cnt].dwObjectSerial == lpTransPlayerInfo->dwObjectSerial)
				return &TransCharFixed[cnt];
		}
	}
	else {
		for (cnt = 0; cnt < FIX_CHAR_MAX; cnt++) {
			if (TransCharFixed[cnt].code == 0) return &TransCharFixed[cnt];
		}
	}

	return NULL;
}

int STG_AREA::AddCharInfoFixed(smTRNAS_PLAYERINFO* lpTransPlayerInfo)
{
	smTRNAS_PLAYERINFO* lpFindPlayerInfo;

	lpFindPlayerInfo = FindCharInfoFixed(lpTransPlayerInfo);
	if (lpFindPlayerInfo) return FALSE;

	lpFindPlayerInfo = FindCharInfoFixed(0);
	if (lpFindPlayerInfo) {
		rsOpenNPC_RandomPos = -1;
		memcpy(lpFindPlayerInfo, lpTransPlayerInfo, sizeof(smTRNAS_PLAYERINFO));
		OpenNpc(lpFindPlayerInfo);
		SaveCharInfoFixed(szCharFixedFile);
		return TRUE;
	}

	return FALSE;
}

int STG_AREA::DeleteCharInfoFixed(smTRNAS_PLAYERINFO* lpTransPlayerInfo)
{
	smTRNAS_PLAYERINFO* lpFindPlayerInfo;
	smCHAR* lpChar;

	lpFindPlayerInfo = FindCharInfoFixed(lpTransPlayerInfo);
	if (lpFindPlayerInfo) {
		lpFindPlayerInfo->code = 0;

		lpChar = srFindCharFromSerial(lpTransPlayerInfo->dwObjectSerial);
		if (lpChar) {
			lpChar->Close();
		}
		SaveCharInfoFixed(szCharFixedFile);
		return TRUE;
	}

	return FALSE;
}

int STG_AREA::LoadCharInfoFixed(char* szFile)
{
	FILE* fp;

	fp = fopen(szFile, "rb");
	if (fp) {
		fread(TransCharFixed, sizeof(smTRNAS_PLAYERINFO) * FIX_CHAR_MAX, 1, fp);
		fclose(fp);
		return TRUE;
	}
	return FALSE;
}

int STG_AREA::SaveCharInfoFixed(char* szFile)
{
	FILE* fp;

	fp = fopen(szFile, "wb");
	if (fp) {
		fwrite(TransCharFixed, sizeof(smTRNAS_PLAYERINFO) * FIX_CHAR_MAX, 1, fp);
		fclose(fp);
	}

	return TRUE;
}

int STG_AREA::OpenNpc(smTRNAS_PLAYERINFO* lpTransPlayerInfo)
{
	smCHAR* lpChar;
	char* lpFileName;
	int dist, cnt;

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag &&
			chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC &&
			chrAutoPlayer[cnt].pX == lpTransPlayerInfo->x &&
			chrAutoPlayer[cnt].pY == lpTransPlayerInfo->y &&
			chrAutoPlayer[cnt].pZ == lpTransPlayerInfo->z) {
			return FALSE;
		}
	}

	lpChar = srFindEmptyChar();
	if (lpChar) {
		lpChar->Init();

		lpTransPlayerInfo->dwObjectSerial = GetNewObjectSerial();
		lpChar->pX = lpTransPlayerInfo->x;
		lpChar->pY = lpTransPlayerInfo->y;
		lpChar->pZ = lpTransPlayerInfo->z;
		lpChar->Angle.x = lpTransPlayerInfo->ax;
		lpChar->Angle.y = lpTransPlayerInfo->ay;
		lpChar->Angle.z = lpTransPlayerInfo->az;

		lpChar->PosiAround.x = lpTransPlayerInfo->x;
		lpChar->PosiAround.y = lpTransPlayerInfo->y;
		lpChar->PosiAround.z = lpTransPlayerInfo->z;
		lpChar->DistAroundDbl = DIST_AROUND_NEAR;

		lpChar->lpExt1 = (void*)&Head;
		lpChar->dwObjectSerial = lpTransPlayerInfo->dwObjectSerial;
		lpChar->ActionPattern = 12;
		memcpy(&lpChar->smCharInfo, &lpTransPlayerInfo->smCharInfo, sizeof(smCHAR_INFO));

		lpFileName = lpChar->smCharInfo.szModelName2;
		if (lpFileName[0]) {
			lpChar->szChatMessage[0] = 0;
			ZeroMemory(&lpChar->smMonsterInfo, sizeof(smCHAR_MONSTER_INFO));
			smCharDecode(lpFileName, &lpChar->smCharInfo, &lpChar->smMonsterInfo, lpChar->szChatMessage);

			if (rsOpenNPC_RandomPos != -1 && lpChar->smMonsterInfo.OpenCount[1]) {
				if ((rsOpenNPC_RandomPos % lpChar->smMonsterInfo.OpenCount[1]) != lpChar->smMonsterInfo.OpenCount[0]) {
					lpChar->Flag = 0;
					return FALSE;
				}
			}

			if (lpChar->smMonsterInfo.szName[0]) {
				lstrcpy(lpChar->smCharInfo.szName, lpChar->smMonsterInfo.szName);
				lpChar->smMonsterInfo.szName[0] = 0;
			}
			srLinkNpcItem(lpChar);

			dist = lpChar->smMonsterInfo.MoveRange >> FLOATNS;
			lpChar->DistAroundDbl = dist * dist;
		}

		lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);
		lpChar->lpStage = lpStage;

		if (lpChar->FindMotionCountFromCode(CHRMOTION_STATE_WALK) == 0)
		{
			lpChar->MoveSpeed = 0;
		}

		return TRUE;
	}

	return FALSE;
}

STG_ITEMS* STG_AREA::FindItem(int x, int y, int z)
{
	int cnt;

	for (cnt = 0; cnt < STG_ITEM_MAX; cnt++) {
		if (StgItems[cnt].state &&
			StgItems[cnt].x == x && StgItems[cnt].y == y && StgItems[cnt].z == z) {
			return	&StgItems[cnt];
		}
	}

	return NULL;
}

STG_ITEMS* STG_AREA::AddItem(psITEM* lpItem, int x, int y, int z, int BeginMode)
{
	int cnt, cnt2;
	STG_ITEMS* lpStgItem;
	int height;
	int dx, dz, dy;
	int ta;
	DWORD dwItem;

	for (cnt = 0; cnt < 8; cnt++) {
		ItemSettingCount++;
		dx = x + ptItemSettingPosi[ItemSettingCount & 7].x;
		dz = z + ptItemSettingPosi[ItemSettingCount & 7].y;
		dy = y << FLOATNS;

		height = lpStage->GetFloorHeight(dx << FLOATNS, dy, dz << FLOATNS, 32 * fONE);
		if (height != CLIP_OUT) {
			ta = abs(height - dy);
			if (ta < 32 * fONE) {
				lpStgItem = FindItem(x, y, z);
				if (!lpStgItem) break;
			}
		}
	}

	if (cnt < 8) {
		x = dx;
		z = dz;
		y = height >> FLOATNS;
	}

	for (cnt2 = 0; cnt2 < 2; cnt2++) {
		for (cnt = 0; cnt < STG_ITEM_MAX; cnt++) {
			if (!StgItems[cnt].state || (cnt2 && StgItems[cnt].Level == 0)) {
				StgItems[cnt].x = x;
				StgItems[cnt].y = y;
				StgItems[cnt].z = z;
				StgItems[cnt].state = TRUE;
				memcpy(&StgItems[cnt].Item, lpItem, sizeof(psITEM));

				StgItems[cnt].dwCreateTime = GetCurrentTime();
				StgItems[cnt].BeginMode = BeginMode;

				dwItem = StgItems[cnt].Item.ItemInfo.CODE & sinITEM_MASK2;

				if (dwItem == sinGG1 || dwItem == sinPL1 || dwItem == sinPS1) {
					StgItems[cnt].dwLoseTime = StgItems[cnt].dwCreateTime + STG_ITEM_WAIT_TIME_LOW;
				}
				else {
					StgItems[cnt].dwLoseTime = StgItems[cnt].dwCreateTime + STG_ITEM_WAIT_TIME;
				}

				if (dwItem != sinPM1 && dwItem != sinPL1 && dwItem != sinPS1 && dwItem != sinGG1) StgItems[cnt].Level = 1;
				else dwItem = 0;

				return	&StgItems[cnt];
			}
		}
		rsItemBuffOverCount++;
	}

	return FALSE;
}

int STG_AREA::DeleteItem(STG_ITEMS* lpStgItem)
{
	int cnt;
	int rx, rz, dist;
	smTRANS_ACITON_ITEM	TransActionItem;

	if (lpStgItem) {
		lpStgItem->state = NULL;

		TransActionItem.size = sizeof(smTRANS_ACITON_ITEM);
		TransActionItem.code = smTRANSCODE_DELITEM;
		TransActionItem.x = lpStgItem->x << FLOATNS;
		TransActionItem.y = lpStgItem->y << FLOATNS;
		TransActionItem.z = lpStgItem->z << FLOATNS;
		TransActionItem.lpStgArea = (void*)this;

		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial) {
				rx = lpStgItem->x - (rsPlayInfo[cnt].Position.x >> FLOATNS);
				rz = lpStgItem->z - (rsPlayInfo[cnt].Position.z >> FLOATNS);
				dist = rx * rx + rz * rz;
				if (dist < DIST_TRANSLEVEL_MHIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT) {
					rsPlayInfo[cnt].lpsmSock->Send((char*)&TransActionItem, TransActionItem.size, TRUE);
				}
			}
		}
	}

	return TRUE;
}

int STG_AREA::DeleteItem(int x, int y, int z)
{
	STG_ITEMS* lpStgItem;

	lpStgItem = FindItem(x, y, z);

	if (lpStgItem) {
		return DeleteItem(lpStgItem);
	}

	return FALSE;
}

int STG_AREA::SendStgItem(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_ITEMS	TransItems;
	int cnt, scnt;
	int dx, dz, dist;
	DWORD	dwCode;

	cnt = 0;
	scnt = 0;

	while (1) {
		if (scnt >= TRANS_ITEM_MAX) break;
		if (cnt >= STG_ITEM_MAX) break;

		if (StgItems[cnt].state && StgItems[cnt].Level && StgItems[cnt].dwCreateTime<dwPlayServTime &&
			(StgItems[cnt].dwLoseTime - 10000)>dwPlayServTime) {
			dx = StgItems[cnt].x - (lpPlayInfo->Position.x >> FLOATNS);
			dz = StgItems[cnt].z - (lpPlayInfo->Position.z >> FLOATNS);

			dist = dx * dx + dz * dz;

			if (dist < DIST_TRANSLEVEL_MHIGH && abs(dx) < TRANS_VIEW_LIMIT && abs(dz) < TRANS_VIEW_LIMIT) {
				dwCode = StgItems[cnt].Item.ItemInfo.CODE;

				TransItems.Items[scnt].state = StgItems[cnt].state;
				TransItems.Items[scnt].x = StgItems[cnt].x << FLOATNS;
				TransItems.Items[scnt].y = StgItems[cnt].y << FLOATNS;
				TransItems.Items[scnt].z = StgItems[cnt].z << FLOATNS;
				TransItems.Items[scnt].ItemCode = dwCode;
				TransItems.Items[scnt].lpStgArea = (void*)this;
				TransItems.Items[scnt].iClass = StgItems[cnt].Item.ItemInfo.JobCodeMask;

				dwCode = dwCode & sinITEM_MASK2;

				if (StgItems[cnt].Item.ItemInfo.PotionCount > 1 && (dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
					wsprintf(TransItems.Items[scnt].szName, "%sx%d", StgItems[cnt].Item.ItemInfo.ItemName, StgItems[cnt].Item.ItemInfo.PotionCount);
				}
				else
					lstrcpy(TransItems.Items[scnt].szName, StgItems[cnt].Item.ItemInfo.ItemName);

				if (dwCode == sinPZ1 || dwCode == sinPZ2) {
					if (StgItems[cnt].Item.ItemInfo.PotionCount < 2) {
						TransItems.Items[scnt].ItemCode = sinPZ1 | sin00;
						lstrcpy(TransItems.Items[scnt].szName, srItem_BB);
					}
				}

				scnt++;
			}
		}
		cnt++;
	}

	cnt = 0;

	while (1) {
		if (scnt >= TRANS_ITEM_MAX) break;
		if (cnt >= STG_ITEM_MAX) break;

		if (StgItems[cnt].state && !StgItems[cnt].Level && StgItems[cnt].dwCreateTime<dwPlayServTime &&
			(StgItems[cnt].dwLoseTime - 10000)>dwPlayServTime) {
			dx = StgItems[cnt].x - (lpPlayInfo->Position.x >> FLOATNS);
			dz = StgItems[cnt].z - (lpPlayInfo->Position.z >> FLOATNS);

			dist = dx * dx + dz * dz;

			if (dist < DIST_TRANSLEVEL_MHIGH && abs(dx) < TRANS_VIEW_LIMIT && abs(dz) < TRANS_VIEW_LIMIT) {
				dwCode = StgItems[cnt].Item.ItemInfo.CODE;

				TransItems.Items[scnt].state = StgItems[cnt].state;
				TransItems.Items[scnt].x = StgItems[cnt].x << FLOATNS;
				TransItems.Items[scnt].y = StgItems[cnt].y << FLOATNS;
				TransItems.Items[scnt].z = StgItems[cnt].z << FLOATNS;
				TransItems.Items[scnt].ItemCode = dwCode;
				TransItems.Items[scnt].lpStgArea = (void*)this;
				TransItems.Items[scnt].iClass = StgItems[cnt].Item.ItemInfo.JobCodeMask;

				dwCode = dwCode & sinITEM_MASK2;

				if (StgItems[cnt].Item.ItemInfo.PotionCount > 1 && (dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
					wsprintf(TransItems.Items[scnt].szName, "%sx%d", StgItems[cnt].Item.ItemInfo.ItemName, StgItems[cnt].Item.ItemInfo.PotionCount);
				}
				else
					lstrcpy(TransItems.Items[scnt].szName, StgItems[cnt].Item.ItemInfo.ItemName);

				if (dwCode == sinPZ1 || dwCode == sinPZ2) {
					if (StgItems[cnt].Item.ItemInfo.PotionCount < 2) {
						TransItems.Items[scnt].ItemCode = sinPZ1 | sin00;
						lstrcpy(TransItems.Items[scnt].szName, srItem_BB);
					}
				}

				scnt++;
			}
		}
		cnt++;
	}

	TransItems.code = smTRANSCODE_PLAYITEM;
	TransItems.size = sizeof(TRANS_ITEM) * scnt + 16;
	TransItems.state = 1;
	TransItems.Count = scnt;

	if (scnt > 0 && lpPlayInfo && lpPlayInfo->lpsmSock)
		return lpPlayInfo->lpsmSock->Send((char*)&TransItems, TransItems.size, TRUE);

	return FALSE;
}

int STG_AREA::SendStgItem(rsPLAYINFO* lpPlayInfo, STG_ITEMS* lpStgItem)
{
	smTRANS_ITEMS	TransItems;
	DWORD	dwCode;

	if (!lpStgItem->state) return FALSE;

	dwCode = lpStgItem->Item.ItemInfo.CODE;

	TransItems.Items[0].state = lpStgItem->state;
	TransItems.Items[0].x = lpStgItem->x << FLOATNS;
	TransItems.Items[0].y = lpStgItem->y << FLOATNS;
	TransItems.Items[0].z = lpStgItem->z << FLOATNS;
	TransItems.Items[0].ItemCode = dwCode;
	TransItems.Items[0].lpStgArea = (void*)this;
	TransItems.Items[0].iClass = lpStgItem->Item.ItemInfo.JobCodeMask;

	dwCode = dwCode & sinITEM_MASK2;

	if (lpStgItem->Item.ItemInfo.PotionCount > 1 && (dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
		wsprintf(TransItems.Items[0].szName, "%sx%d", lpStgItem->Item.ItemInfo.ItemName, lpStgItem->Item.ItemInfo.PotionCount);
	}
	else
		lstrcpy(TransItems.Items[0].szName, lpStgItem->Item.ItemInfo.ItemName);

	if (dwCode == sinPZ1 || dwCode == sinPZ2) {
		if (lpStgItem->Item.ItemInfo.PotionCount < 2) {
			TransItems.Items[0].ItemCode = sinPZ1 | sin00;
			lstrcpy(TransItems.Items[0].szName, srItem_BB);
		}
	}

	TransItems.code = smTRANSCODE_PLAYITEM;
	TransItems.size = sizeof(TRANS_ITEM) + 16;
	TransItems.state = 1;
	TransItems.Count = 1;

	if (lpPlayInfo && lpPlayInfo->lpsmSock)
		return lpPlayInfo->lpsmSock->Send((char*)&TransItems, TransItems.size, TRUE);

	return FALSE;
}

int STG_AREA::SendStgItemToNearUsers(STG_ITEMS* lpStgItem)
{
	int cnt;
	int rx, rz, dist;
	smTRANS_ITEMS	TransItems;
	DWORD	dwCode;

	if (lpStgItem) {
		dwCode = lpStgItem->Item.ItemInfo.CODE;

		TransItems.Items[0].state = lpStgItem->state;
		TransItems.Items[0].x = lpStgItem->x << FLOATNS;
		TransItems.Items[0].y = lpStgItem->y << FLOATNS;
		TransItems.Items[0].z = lpStgItem->z << FLOATNS;
		TransItems.Items[0].ItemCode = dwCode;
		TransItems.Items[0].lpStgArea = (void*)this;

		dwCode = dwCode & sinITEM_MASK2;

		if (lpStgItem->Item.ItemInfo.PotionCount > 1 && (dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
			wsprintf(TransItems.Items[0].szName, "%sx%d", lpStgItem->Item.ItemInfo.ItemName, lpStgItem->Item.ItemInfo.PotionCount);
		}
		else
			lstrcpy(TransItems.Items[0].szName, lpStgItem->Item.ItemInfo.ItemName);

		if (dwCode == sinPZ1 || dwCode == sinPZ2) {
			if (lpStgItem->Item.ItemInfo.PotionCount < 2) {
				TransItems.Items[0].ItemCode = sinPZ1 | sin00;
				lstrcpy(TransItems.Items[0].szName, srItem_BB);
			}
		}

		TransItems.code = smTRANSCODE_PLAYITEM;
		TransItems.size = sizeof(TRANS_ITEM) + 16;
		TransItems.state = 1;
		TransItems.Count = 1;

		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial) {
				rx = lpStgItem->x - (rsPlayInfo[cnt].Position.x >> FLOATNS);
				rz = lpStgItem->z - (rsPlayInfo[cnt].Position.z >> FLOATNS);
				dist = rx * rx + rz * rz;

				if (dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT) {
					rsPlayInfo[cnt].lpsmSock->Send((char*)&TransItems, TransItems.size, TRUE);
				}
			}
		}
	}

	return TRUE;
}

int STG_AREA::SendStgItemToPartyUsers(rsPLAYINFO* lpPlayInfo, STG_ITEMS* lpStgItem)
{
	int cnt;
	int rx, rz, dist;
	smTRANS_ITEMS	TransItems;
	DWORD	dwCode;

	if (lpStgItem && lpPlayInfo && lpPlayInfo->lpPartyMaster) {
		dwCode = lpStgItem->Item.ItemInfo.CODE;

		TransItems.Items[0].state = lpStgItem->state;
		TransItems.Items[0].x = lpStgItem->x << FLOATNS;
		TransItems.Items[0].y = lpStgItem->y << FLOATNS;
		TransItems.Items[0].z = lpStgItem->z << FLOATNS;
		TransItems.Items[0].ItemCode = dwCode;
		TransItems.Items[0].lpStgArea = (void*)this;
		TransItems.Items[0].iClass = lpStgItem->Item.ItemInfo.JobCodeMask;

		dwCode = dwCode & sinITEM_MASK2;

		if (lpStgItem->Item.ItemInfo.PotionCount > 1 && (dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
			wsprintf(TransItems.Items[0].szName, "%sx%d", lpStgItem->Item.ItemInfo.ItemName, lpStgItem->Item.ItemInfo.PotionCount);
		}
		else
			lstrcpy(TransItems.Items[0].szName, lpStgItem->Item.ItemInfo.ItemName);

		if (dwCode == sinPZ1 || dwCode == sinPZ2) {
			if (lpStgItem->Item.ItemInfo.PotionCount < 2) {
				TransItems.Items[0].ItemCode = sinPZ1 | sin00;
				lstrcpy(TransItems.Items[0].szName, srItem_BB);
			}
		}

		TransItems.code = smTRANSCODE_PLAYITEM;
		TransItems.size = sizeof(TRANS_ITEM) + 16;
		TransItems.state = 1;
		TransItems.Count = 1;

		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
				rsPlayInfo[cnt].dwPartyInfo && lpPlayInfo->lpPartyMaster == rsPlayInfo[cnt].lpPartyMaster) {
				rx = lpStgItem->x - (rsPlayInfo[cnt].Position.x >> FLOATNS);
				rz = lpStgItem->z - (rsPlayInfo[cnt].Position.z >> FLOATNS);
				dist = rx * rx + rz * rz;

				if (dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT) {
					rsPlayInfo[cnt].lpsmSock->Send((char*)&TransItems, TransItems.size, TRUE);
				}
			}
		}
	}

	return TRUE;
}

int STG_AREA::SendStgItems()
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial && (dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) < OVER_TRANS_TIME) {
			SendStgItem(&rsPlayInfo[cnt]);
		}
	}

	return TRUE;
}

int STG_AREA::SendStartPos(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_ITEMS	TransItems;
	int cnt, scnt;
	int dx, dz, dist;

	cnt = 0;
	scnt = 0;

	StartPointActiveCount = 0;
	StartPointOpenCount = 0;

	while (1) {
		if (scnt >= TRANS_ITEM_MAX) break;
		if (cnt >= STG_START_POINT_MAX) break;

		if (StartPoint[cnt].state) {
			dx = StartPoint[cnt].x - (lpPlayInfo->Position.x >> FLOATNS);
			dz = StartPoint[cnt].z - (lpPlayInfo->Position.z >> FLOATNS);

			dist = dx * dx + dz * dz;

			if (dist < DIST_TRANSLEVEL_CONNECT && abs(dx) < TRANS_VIEW_LIMIT && abs(dz) < TRANS_VIEW_LIMIT) {
				StartPointNearPlay[cnt] ++;

				if (lpPlayInfo->AdminMode >= 2) {
					TransItems.Items[scnt].state = StartPoint[cnt].state;
					TransItems.Items[scnt].x = StartPoint[cnt].x << FLOATNS;
					TransItems.Items[scnt].y = 0;
					TransItems.Items[scnt].z = StartPoint[cnt].z << FLOATNS;
					TransItems.Items[scnt].ItemCode = 0;
					TransItems.Items[scnt].lpStgArea = (void*)this;

#ifdef _LANGUAGE_KOREAN
					wsprintf(TransItems.Items[scnt].szName, szMonsterFlagMsg, cnt, StartPointMonCount[cnt]);
#else
					lstrcpy(TransItems.Items[scnt].szName, szMonsterFlagMsg);
#endif
					scnt++;
				}
			}

			if (StartPointNearPlay[cnt])	StartPointActiveCount++;
			StartPointOpenCount++;
		}

		cnt++;
	}

	if (lpPlayInfo->AdminMode >= 2) {
		TransItems.code = smTRANSCODE_PLAYITEM;
		TransItems.size = sizeof(TRANS_ITEM) * scnt + 16;
		TransItems.state = 1;
		TransItems.Count = scnt;

		if (scnt > 0 && lpPlayInfo && lpPlayInfo->lpsmSock)
			return lpPlayInfo->lpsmSock->Send((char*)&TransItems, TransItems.size, TRUE);
	}
	return TRUE;
}

int STG_AREA::LoadStartPoint(char* szFile)
{
	FILE* fp;

	fp = fopen(szFile, "rb");
	if (fp) {
		fread(StartPoint, sizeof(STG_START_POINT) * STG_START_POINT_MAX, 1, fp);
		fclose(fp);
		dwActiveMode |= 1;
	}

	return TRUE;
}

int STG_AREA::SaveStartPoint(char* szFile)
{
	FILE* fp;

	fp = fopen(szFile, "wb");
	if (fp) {
		fwrite(StartPoint, sizeof(STG_START_POINT) * STG_START_POINT_MAX, 1, fp);
		fclose(fp);
		dwActiveMode |= 1;
	}

	return TRUE;
}

int	STG_AREA::FindEmptyMonTable()
{
	int cnt;

	for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++) {
		if (lpCharMonster[cnt] == 0) return cnt;
	}

	return -1;
}

int	STG_AREA::AddMonTable(smCHAR* lpChar)
{
	int	cnt;
	int mtab;

	StartPointMonCount[lpChar->OpenStartPostion] ++;

	mtab = FindEmptyMonTable();
	if (mtab >= 0) {
		lpCharMonster[mtab] = lpChar;
		lpChar->lpExt4 = this;

		MonsterLastPoint = mtab;
		for (cnt = mtab; cnt < STG_MONSTER_MAX; cnt++) {
			if (lpCharMonster[cnt])
				MonsterLastPoint = cnt + 1;
		}
		return TRUE;
	}

	return FALSE;
}

int	STG_AREA::DeleteMonTable(smCHAR* lpChar)
{
	int cnt;

	if (StartPointMonCount[lpChar->OpenStartPostion] > 0)
		StartPointMonCount[lpChar->OpenStartPostion] --;

	for (cnt = 0; cnt < MonsterLastPoint; cnt++) {
		if (lpCharMonster[cnt] == lpChar) {
			lpCharMonster[cnt] = NULL;
			return TRUE;
		}
	}

	return FALSE;
}

smCHAR* STG_AREA::OpenMonster(STG_CHAR_INFO* lpStgCharInfo, int gGroup)
{
	smCHAR* lpChar;
	int dist;
	int x, y, z;
	int cnt;

	lpChar = srFindEmptyChar();
	if (!lpChar) return NULL;

	if (SetStartPosChar(lpChar) == TRUE) {
		MonsterCount++;
		lpChar->lpExt1 = (void*)&Head;
		lpChar->dwObjectSerial = GetNewObjectSerial();
		lpChar->ActionPattern = 5;
		memcpy(&lpChar->smCharInfo, &lpStgCharInfo->smCharInfo, sizeof(smCHAR_INFO));
		memcpy(&lpChar->smMonsterInfo, lpStgCharInfo->smCharInfo.lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
		lpChar->smMonsterInfo.Boss = Boss;
		lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);
		DamageList[lpChar->dwObjectSerial].clear();

		lpChar->smCharInfo.StatePoint = lpStgCharInfo->smCharInfo.lpMonInfo->ClassCode;

		dist = 64 * 20;
		lpChar->DistAroundDbl = dist * dist;
		lpChar->AttackUserFlag = 0;
		lpChar->lpExt2 = 0;

		lpChar->lpExpAttackPlayInfo = 0;
		lpChar->ExpAttackLife = 0;

		lpChar->Angle.y = (GetCurrentTime() << 2) & ANGCLIP;
		lpChar->SetMotionFromCode(CHRMOTION_STATE_WALK);
		lpChar->TargetMoveCount = 2;

		AddMonTable(lpChar);

		if (lprsFixedPoint)
			lpChar->ReopenCount = REOPEN_COUNT_NUM * 32;
		else
			lpChar->ReopenCount = REOPEN_COUNT_NUM;

		lpChar->dwLastTransTime = dwPlayServTime;

		if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT || lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_KELVEZU || lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_MOKOVA) {
			lpChar->UseObject_VirtualLife = lpChar->smMonsterInfo.PotionCount;
			lpChar->sObject_VirtualLife[0] = lpChar->UseObject_VirtualLife;
			lpChar->sObject_VirtualLife[1] = lpChar->UseObject_VirtualLife;
			lpChar->sObject_DisplayLife[0] = lpChar->UseObject_VirtualLife;
			lpChar->sObject_DisplayLife[1] = lpChar->UseObject_VirtualLife;
		}
		else {
			if (lpChar->smMonsterInfo.PotionCount) {
				if ((rand() % 100) < lpChar->smMonsterInfo.PotionPercent) {
					lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
				}
				else {
					lpChar->smMonsterInfo.PotionCount = 0;
				}
			}
		}

#ifdef	_LANGUAGE_JAPANESE
		if (rsDamgeOffEvent)
		{
			lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * ATTACK_RATE) / 100;
			lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * ATTACK_RATE) / 100;
			if (lpChar->smMonsterInfo.SkillDamage[0])
			{
				lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * ATTACK_RATE) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * ATTACK_RATE) / 100;
			}
		}
#else

		if (rsDamgeOffEvent1)
		{
			lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 75) / 100;
			lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 75) / 100;
			if (lpChar->smMonsterInfo.SkillDamage[0])
			{
				lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 75) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 75) / 100;
			}
		}

		if (rsDamgeOffEvent2)
		{
			lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 50) / 100;
			lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 50) / 100;
			if (lpChar->smMonsterInfo.SkillDamage[0])
			{
				lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 50) / 100;
				lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 50) / 100;
			}
		}
#endif

		if (rsDefenseOffEvent)
		{
			lpChar->smCharInfo.Defence = (lpChar->smCharInfo.Defence * DEFENSE_RATE) / 100;
		}

		if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_VAMPRICMACHINE)
		{
			lpChar->DontMoveFlag = 1;
		}

		rsMonOpenCount++;
	}
	else {
		lpChar->Close();
		return NULL;
	}

	x = lpChar->pX;
	y = lpChar->pY;
	z = lpChar->pZ;

	for (cnt = 1; cnt < gGroup; cnt++) {
		lpChar = srFindEmptyChar();
		if (!lpChar) return NULL;

		if (SetStartPosNearChar(lpChar, x, y, z) == TRUE) {
			MonsterCount++;
			lpChar->lpExt1 = (void*)&Head;
			lpChar->dwObjectSerial = GetNewObjectSerial();
			lpChar->ActionPattern = 5;
			memcpy(&lpChar->smCharInfo, &lpStgCharInfo->smCharInfo, sizeof(smCHAR_INFO));
			memcpy(&lpChar->smMonsterInfo, lpStgCharInfo->smCharInfo.lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
			lpChar->smMonsterInfo.Boss = Boss;
			lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);

			lpChar->smCharInfo.StatePoint = lpStgCharInfo->smCharInfo.lpMonInfo->ClassCode;

			dist = 64 * 20;
			lpChar->DistAroundDbl = dist * dist;
			lpChar->AttackUserFlag = 0;
			lpChar->lpExt2 = 0;

			lpChar->lpExpAttackPlayInfo = 0;
			lpChar->ExpAttackLife = 0;

			AddMonTable(lpChar);

			if (lprsFixedPoint)
				lpChar->ReopenCount = REOPEN_COUNT_NUM * 32;
			else
				lpChar->ReopenCount = REOPEN_COUNT_NUM;

			lpChar->dwLastTransTime = dwPlayServTime;

			if (lpChar->smMonsterInfo.PotionCount) {
				if ((rand() % 100) < lpChar->smMonsterInfo.PotionPercent) {
					lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
				}
				else {
					lpChar->smMonsterInfo.PotionCount = 0;
				}
			}

#ifdef	_LANGUAGE_JAPANESE
			if (rsDamgeOffEvent)
			{
				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * ATTACK_RATE) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * ATTACK_RATE) / 100;
				if (lpChar->smMonsterInfo.SkillDamage[0]) {
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * ATTACK_RATE) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * ATTACK_RATE) / 100;
				}
			}
#else

			if (rsDamgeOffEvent1)
			{
				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 75) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 75) / 100;
				if (lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 75) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 75) / 100;
				}
			}

			if (rsDamgeOffEvent2)
			{
				lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * 50) / 100;
				lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * 50) / 100;
				if (lpChar->smMonsterInfo.SkillDamage[0])
				{
					lpChar->smMonsterInfo.SkillDamage[0] = (lpChar->smMonsterInfo.SkillDamage[0] * 50) / 100;
					lpChar->smMonsterInfo.SkillDamage[1] = (lpChar->smMonsterInfo.SkillDamage[1] * 50) / 100;
				}
			}
#endif

			if (rsDefenseOffEvent)
			{
				lpChar->smCharInfo.Defence = (lpChar->smCharInfo.Defence * DEFENSE_RATE) / 100;
			}

			rsMonOpenCount++;

			if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_VAMPRICMACHINE ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR)
			{
				lpChar->DontMoveFlag = 2;
			}
		}
		else {
			lpChar->Close();
			return NULL;
		}
	}

	return lpChar;
}

int STG_AREA::SendStartPointFlag()
{
	int cnt;

	ZeroMemory(StartPointNearPlay, sizeof(int) * STG_START_POINT_MAX);

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial) {
			SendStartPos(&rsPlayInfo[cnt]);
		}
	}

	return TRUE;
}

int STG_AREA::Main()
{
	STG_CHAR_INFO StgCharInfo;
	int cnt;
	int rnd;
	int gGroup;
	DWORD	OsCode;
	smCHAR_INFO* lpCharInfo;

	Counter++;

	if (chrMonsterCnt > 0 && MonsterCount < rsMonsterList.LimitMax &&
		(Counter & rsMonsterList.OpenInterval) == 0 &&
		(lpField->FieldEvent != FIELD_EVENT_NIGHTMARE || FieldNightDay)) {
		StgCharInfo.PosiState = TRUE;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		if (rsMonsterList.Counter) {
			rnd = (rand() % rsMonsterList.PecetageCount);
			for (cnt = 0; cnt < rsMonsterList.Counter; cnt++) {
				if (rsMonsterList.rsMonster[cnt].NumOpenStart > rnd) break;
			}
			memcpy(&StgCharInfo.smCharInfo, rsMonsterList.rsMonster[cnt - 1].lpCharInfo, sizeof(smCHAR_INFO));

			if (EventMonster) {
				OpenEventMonster(&StgCharInfo.smCharInfo, this);
			}
			lpCharInfo = &StgCharInfo.smCharInfo;

			if (lpCharInfo && StgCharInfo.smCharInfo.lpMonInfo) {
				gGroup = GetRandomPos(StgCharInfo.smCharInfo.lpMonInfo->GenerateGroup[0],
					StgCharInfo.smCharInfo.lpMonInfo->GenerateGroup[1]);

				if (gGroup <= 0) gGroup = 1;

				if (Event_dwMonsterTime > dwPlayServTime && Event_MonsterPercentage > 0 && Event_lpChrMonster) {
					if ((rand() % 1000) < Event_MonsterPercentage) {
						memcpy(&StgCharInfo.smCharInfo, Event_lpChrMonster, sizeof(smCHAR_INFO));
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_Child && srHammerMonsterCount > 0)
				{
					if ((rand() % 1000) < rsServerConfig.Event_Child)
					{
						if (lpField->State == FIELD_STATE_FOREST)
						{
							for (cnt = 0; cnt < srHammerMonsterCount; cnt++)
							{
								if (srCharInfo_HammerMonster[cnt]->dwCharSoundCode == snCHAR_SOUND_HOBGOBLIN) {
									memcpy(&StgCharInfo.smCharInfo, srCharInfo_HammerMonster[cnt], sizeof(smCHAR_INFO));
									break;
								}
							}
						}
						else
							memcpy(&StgCharInfo.smCharInfo, srCharInfo_HammerMonster[rand() % srHammerMonsterCount], sizeof(smCHAR_INFO));

						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_MorifSheltom) {
					if ((rand() % 1000) < rsServerConfig.Event_MorifSheltom) {
						for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_NPC_MORIF && chrMonsterList[cnt].Level == 60) {
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_WorldCup) {
					int chrFind = 0;
					int rFind = rand() % 4;
					if ((rand() % 1000) < rsServerConfig.Event_WorldCup) {
						for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_WORLDCUP) {
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								if (chrFind == rFind) break;
								chrFind++;
							}
						}
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_MollyWolf) {
					if ((rand() % 1000) < rsServerConfig.Event_MollyWolf) {
						for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_NPC_MOLLYWOLF) {
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_Ghost) {
					if ((rand() % 1000) < rsServerConfig.Event_Ghost) {
						for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_MRGHOST && chrMonsterList[cnt].wPlayClass[0] == MONSTER_CLASS_GHOST) {
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_SantaGoblin) {
					if ((rand() % 1000) < rsServerConfig.Event_SantaGoblin) {
						for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_HOBGOBLIN && chrMonsterList[cnt].Level == 60) {
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_SummerChicken) {
					if ((rand() % 1000) < rsServerConfig.Event_SummerChicken) {
						for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_RABIE && chrMonsterList[cnt].Level >= 10 && chrMonsterList[cnt].wPlayClass[1]) {
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_WarerMelonMonster) {
					if ((rand() % 10000) < rsServerConfig.Event_WarerMelonMonster) {
						for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_WATERMELON) {
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				if (rsServerConfig.Event_Chichen_Day)
				{
					if ((rand() % 1000) < rsServerConfig.Event_Chichen_Day)
					{
						for (cnt = 0; cnt < chrMonsterCnt; cnt++)
						{
							if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_BEBECHICK)
							{
								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
								break;
							}
						}
						gGroup = 1;
					}
				}

				OpenMonster(&StgCharInfo, gGroup);
			}
		}
	}

	switch (Counter & 0x1FF) {
	case 0x80:
		SendStartPointFlag();
		break;
	case 0xC0:
		SendStgItems();
		break;
	}

	DWORD	dwTime;
	int		dist;

	dwTime = dwPlayServTime;

	for (cnt = 0; cnt < STG_ITEM_MAX; cnt++) {
		if (StgItems[cnt].state) {
			if (StgItems[cnt].dwLoseTime < dwTime) {
				StgItems[cnt].state = 0;
			}
		}
	}

	if (rsServerConfig.Event_HardCore && lpField->FieldCode == rsSOD_FIELD && rsMonsterList.Counter > 0) {
		if ((Counter & 0x3F) == 0) {
			memcpy(&StgCharInfo.smCharInfo, rsMonsterList.rsMonster[0].lpCharInfo, sizeof(smCHAR_INFO));
			rsHardCoreEvent_OpenMonster(this, &StgCharInfo);
		}
	}

	if (lpField->FieldCode == rsCASTLE_FIELD) {
		rsMain_CombatCastle();
	}

	rsEventSpawn_Main(this);

	if (FieldNightDay != dwServ_NightDay) {
		if (lpField->FieldEvent == FIELD_EVENT_NIGHTMARE) {
			if (dwServ_NightDay) {
				for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
					if (chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == this &&
						chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_NPC &&
						chrAutoPlayer[cnt].smMonsterInfo.EventNPC == 0) {
						chrAutoPlayer[cnt].Close();

						chrAutoPlayer[cnt].Flag = TRUE;

						rnd = chrAutoPlayer[cnt].smCharInfo.bUpdateInfo[0];
						OsCode = chrAutoPlayer[cnt].dwObjectSerial;

						memcpy(&chrAutoPlayer[cnt].smCharInfo, chrNpcMonsterInfo, sizeof(smCHAR_INFO));
						memcpy(&chrAutoPlayer[cnt].smMonsterInfo, chrNpcMonsterInfo->lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
						chrAutoPlayer[cnt].ActionPattern = 5;
						MonsterCount++;
						chrAutoPlayer[cnt].SetLoadPattern(chrAutoPlayer[cnt].smCharInfo.szModelName);

						dist = 64 * 20;
						chrAutoPlayer[cnt].DistAroundDbl = dist * dist;
						AddMonTable(&chrAutoPlayer[cnt]);
						chrAutoPlayer[cnt].ReopenCount = REOPEN_COUNT_NUM;
						chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_STAND);

						chrAutoPlayer[cnt].smCharInfo.bUpdateInfo[0] = rnd + 1;
						chrAutoPlayer[cnt].dwObjectSerial = OsCode;
					}
				}
			}
			else {
				for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
					if (chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == this &&
						chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY) {
						chrAutoPlayer[cnt].smCharInfo.Life[0] = 0;
						chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_DEAD);
					}
				}

				rsOpenNPC_RandomPos = rand();

				for (cnt = 0; cnt < FIX_CHAR_MAX; cnt++) {
					if (TransCharFixed[cnt].code)
						OpenNpc(&TransCharFixed[cnt]);
				}
			}
		}

		if (lpField->FieldCode == 3) {
			if (dwServ_NightDay) {
				rsCloseEventMonster(100);
				rsOpenEventMonster(100, 0, 0, 0);
			}
			else {
				rsCloseEventMonster(100);

				for (cnt = 0; cnt < FIX_CHAR_MAX; cnt++) {
					if (TransCharFixed[cnt].code && TransCharFixed[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_WOLVERLIN)
						OpenNpc(&TransCharFixed[cnt]);
				}
			}
		}

		FieldNightDay = dwServ_NightDay;
	}

	return TRUE;
}

int STG_AREA::LoadStage(char* szFile)
{
	smSTAGE3D* lpRes;
	int cnt;

	lpStage = new smSTAGE3D;
	lpRes = smSTAGE3D_ReadASE(szFile, lpStage);
	lpStage->Head = TRUE;

	if (lpRes) {
		SetFieldInfoPath(szStartPointFile, szFile, "spp");
		LoadStartPoint(szStartPointFile);

		SetFieldInfoPath(szCharFixedFile, szFile, "spc");
		if (LoadCharInfoFixed(szCharFixedFile)) {
			for (cnt = 0; cnt < FIX_CHAR_MAX; cnt++) {
				if (TransCharFixed[cnt].code)
					OpenNpc(&TransCharFixed[cnt]);
			}
			dwActiveMode |= 2;
		}

		SetFieldInfoPath(szCharMonsterFile, szFile, "spm");

		DecodeOpenMonster(szCharMonsterFile, &rsMonsterList, chrMonsterList, chrMonsterCnt);
		if (!rsMonsterList.LimitMax) rsMonsterList.LimitMax = 10;

		return TRUE;
	}

	delete lpStage;
	lpStage = 0;

	return FALSE;
}

int STG_AREA::FindStartPoint(int x, int z)
{
	int cnt;
	for (cnt = 0; cnt < STG_START_POINT_MAX; cnt++) {
		if (StartPoint[cnt].state &&
			StartPoint[cnt].x == x && StartPoint[cnt].z == z) {
			return cnt;
		}
	}

	return -1;
}

int STG_AREA::AddStartPoint(int x, int z, int state)
{
	int cnt;

	cnt = FindStartPoint(x, z);
	if (cnt >= 0) return FALSE;

	for (cnt = 0; cnt < STG_START_POINT_MAX; cnt++) {
		if (!StartPoint[cnt].state) {
			StartPoint[cnt].state = state;
			StartPoint[cnt].x = x;
			StartPoint[cnt].z = z;
			StartPointMonCount[cnt] = 0;
			SaveStartPoint(szStartPointFile);
			return TRUE;
		}
	}

	return FALSE;
}

int STG_AREA::DeleteStartPoint(int x, int z)
{
	int cnt;

	cnt = FindStartPoint(x, z);
	if (cnt >= 0) {
		StartPoint[cnt].state = 0;
		StartPointMonCount[cnt] = 0;
		SaveStartPoint(szStartPointFile);
		return TRUE;
	}
	return FALSE;
}

int STG_AREA::StartPosRandomize()
{
	int cnt;
	int end;
	int rnd;

	end = 1;

	for (cnt = STG_START_POINT_MAX - 1; cnt >= 0; cnt--) {
		if (StartPoint[cnt].state) {
			end = cnt + 1;
		}
	}

	rnd = rand() % end;

	StartPointCnt = rnd;

	return TRUE;
}

int STG_AREA::SetStartPosChar(smCHAR* lpChar)
{
	int x, y, cnt;
	int flag;

	flag = 0;

	for (cnt = StartPointCnt; cnt < STG_START_POINT_MAX; cnt++) {
		if (StartPoint[cnt].state && StartPointNearPlay[cnt] &&
			StartPointMonCount[cnt] < rsMonsterList.OpenLimit &&
			dwStartPoint_OpenTime[cnt] < dwPlayServTime) {
			x = StartPoint[cnt].x * fONE;
			y = StartPoint[cnt].z * fONE;
			StartPointCnt = cnt + 1;
			StartPointLastOpenCount = cnt;
			flag++;
			break;
		}
	}

	if (flag == 0) {
		for (cnt = 0; cnt < STG_START_POINT_MAX; cnt++) {
			if (StartPoint[cnt].state && StartPointNearPlay[cnt] &&
				StartPointMonCount[cnt] < rsMonsterList.OpenLimit &&
				dwStartPoint_OpenTime[cnt] < dwPlayServTime) {
				x = StartPoint[cnt].x * fONE;
				y = StartPoint[cnt].z * fONE;
				StartPointCnt = cnt + 1;
				StartPointLastOpenCount = cnt;
				flag++;
				break;
			}
		}
	}

	if (flag == 0 && EvnMonster) {
		EvnMonster = 0;

		for (cnt = StartPointCnt; cnt < STG_START_POINT_MAX; cnt++) {
			if (StartPoint[cnt].state && StartPointNearPlay[cnt]) {
				x = StartPoint[cnt].x * fONE;
				y = StartPoint[cnt].z * fONE;
				flag++;
				break;
			}
		}

		if (flag == 0 && StartPointCnt < STG_START_POINT_MAX) {
			for (cnt = 0; cnt < StartPointCnt; cnt++) {
				if (StartPoint[cnt].state && StartPointNearPlay[cnt]) {
					x = StartPoint[cnt].x * fONE;
					y = StartPoint[cnt].z * fONE;
					flag++;
					break;
				}
			}
		}

		if (flag == 0) {
			for (cnt = 0; cnt < STG_START_POINT_MAX; cnt++) {
				if (StartPoint[cnt].state) {
					x = StartPoint[cnt].x * fONE;
					y = StartPoint[cnt].z * fONE;
					flag++;
					break;
				}
			}
		}
	}

	if (flag > 0) {
		if (lprsFixedPoint) {
			x = lprsFixedPoint->x;
			y = lprsFixedPoint->z;
		}

		lpChar->Init();
		lpChar->lpStage = lpStage;
		lpChar->SetPosi(x, 0, y, 0, 0, 0);

		lpChar->PosiAround.x = x;
		lpChar->PosiAround.y = lpChar->pY;
		lpChar->PosiAround.z = y;
		lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;

		lpChar->OpenStartPostion = StartPointLastOpenCount;

		dwStartPoint_OpenTime[StartPointLastOpenCount] = dwPlayServTime + rsMonsterList.dwIntervalTime;

		return TRUE;
	}

	return FALSE;
}

int STG_AREA::SetStartPosNearChar(smCHAR* lpChar, int cx, int cy, int cz)
{
	int cnt;
	int height;
	int mCnt;
	int x, y, z;

	for (cnt = 0; cnt < 8; cnt++) {
		MonsterSettingCount++;
		mCnt = MonsterSettingCount & 7;

		x = cx + ptItemSettingPosi[mCnt].x * 4 * fONE;
		z = cz + ptItemSettingPosi[mCnt].y * 4 * fONE;
		y = cy;

		height = lpStage->GetFloorHeight(x, y, z, 32 * fONE);
		if (height != CLIP_OUT) {
			if (abs(height - y) < fONE * 64) break;
		}
	}

	if (cnt < 8) {
		lpChar->Init();
		lpChar->lpStage = lpStage;
		lpChar->SetPosi(x, 0, z, 0, 0, 0);
		lpChar->PosiAround.x = x;
		lpChar->PosiAround.y = lpChar->pY;
		lpChar->PosiAround.z = z;
		lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
		lpChar->OpenStartPostion = StartPointLastOpenCount;
		return TRUE;
	}

	return FALSE;
}

int STG_AREA::SetPosNearChar(smCHAR* lpChar, int cx, int cy, int cz)
{
	int cnt;
	int height;
	int mCnt;
	int x, y, z;

	for (cnt = 0; cnt < 8; cnt++) {
		MonsterSettingCount++;
		mCnt = MonsterSettingCount & 7;

		x = cx + ptItemSettingPosi[mCnt].x * 4 * fONE;
		z = cz + ptItemSettingPosi[mCnt].y * 4 * fONE;
		y = cy;

		height = lpStage->GetFloorHeight(x, y, z, 32 * fONE);
		if (height != CLIP_OUT) {
			if (abs(height - y) < fONE * 64) break;
		}
	}

	if (cnt < 8) {
		lpChar->SetPosi(x, 0, z, 0, 0, 0);
		lpChar->PosiAround.x = x;
		lpChar->PosiAround.y = lpChar->pY;
		lpChar->PosiAround.z = z;
		lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
		return TRUE;
	}

	return FALSE;
}

int SetStartPosChar(smCHAR* lpChar)
{
	int x, y, cnt;

	cnt = StartPointCnt;
	x = StartPoint[cnt].x * fONE;
	y = StartPoint[cnt].y * fONE;

	StartPointCnt++;
	if (StartPointCnt >= START_POINT_MAX) StartPointCnt = 0;

	return TRUE;
}

int srInitChar()
{
	int cnt;

	InitPatterns();

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		chrAutoPlayer[cnt].Init();
		chrAutoPlayer[cnt].lpStage = lpsmStage[1];
	}

	return TRUE;
}

int srRemoveChar()
{
	ClosePatterns();

	return TRUE;
}

STG_AREA* FindStageFieldNum(int Field)
{
	int cnt;
	int he;

	for (cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
	{
		if (StageArea[cnt].lpStage)
		{
			if (StageArea[cnt].lpField->FieldCode == Field)
			{
				return &StageArea[cnt];
			}
		}
	}

	return NULL;
}

STG_AREA* FindStageField(int x, int z)
{
	int cnt;
	int he;

	for (cnt = 0; cnt < STAGE_AREA_MAX; cnt++) {
		if (StageArea[cnt].lpStage) {
			he = StageArea[cnt].lpStage->GetHeight(x, z);
			if (he > 0) {
				return &StageArea[cnt];
			}
		}
	}

	return NULL;
}

int srReadStage()
{
	int cnt;

	InitStageLoader();
	InitField();

	cnt = 0;

	while (1) {
		if (sField[cnt].szName[0] == 0) break;

		StageArea[cnt].LoadStage(sField[cnt].szName);
		StageArea[cnt].lpField = &sField[cnt];
		cnt++;
	}

	lpsmStage[0] = StageArea[0].lpStage;
	lpsmStage[1] = StageArea[0].lpStage;

	return TRUE;
}

int srRemoveStage()
{
	return TRUE;
}

int rsSendCharInfo(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo)
{
	smTRNAS_PLAYERINFO	TransPlayerInfo;

	memcpy(&TransPlayerInfo.smCharInfo, &lpChar->smCharInfo, sizeof(smCHAR_INFO));
	TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
	TransPlayerInfo.code = smTRANSCODE_PLAYERINFO;
	TransPlayerInfo.dwObjectSerial = lpChar->dwObjectSerial;

	TransPlayerInfo.x = lpChar->pX;
	TransPlayerInfo.y = lpChar->pY;
	TransPlayerInfo.z = lpChar->pZ;

	if (!lpPlayInfo->AdminMode) {
		TransPlayerInfo.smCharInfo.Attack_Damage[0] = 1000;
		TransPlayerInfo.smCharInfo.Attack_Damage[1] = 9999;
	}

	return lpPlayInfo->lpsmSock->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
}

int rsSendPlayerInfo(rsPLAYINFO* lpSndPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	smCHAR* lpChar;
	rsPLAYINFO* lpPlayInfo;
	smTRNAS_PLAYERINFO	TransPlayerInfo;

	lpChar = srFindCharFromSerial(lpTransCommand->WParam);
	if (lpChar) {
		rsSendCharInfo(lpChar, lpSndPlayInfo);
		return TRUE;
	}

	lpPlayInfo = srFindUserFromSerial(lpTransCommand->WParam);
	if (lpPlayInfo && lpPlayInfo->dwObjectSerial && lpSndPlayInfo && lpSndPlayInfo->lpsmSock) {
		memcpy(&TransPlayerInfo.smCharInfo, &lpPlayInfo->smCharInfo, sizeof(smCHAR_INFO));

		TransPlayerInfo.size = sizeof(smTRNAS_PLAYERINFO);
		TransPlayerInfo.code = smTRANSCODE_PLAYERINFO;
		TransPlayerInfo.dwObjectSerial = lpPlayInfo->dwObjectSerial;

		TransPlayerInfo.x = lpPlayInfo->Position.x;
		TransPlayerInfo.y = lpPlayInfo->Position.y;
		TransPlayerInfo.z = lpPlayInfo->Position.z;

		return lpSndPlayInfo->lpsmSock->Send((char*)&TransPlayerInfo, TransPlayerInfo.size, TRUE);
	}

	return TRUE;
}

int rsSendPlayerInfoQuick(rsPLAYINFO* lpSndPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	smCHAR* lpChar;
	rsPLAYINFO* lpPlayInfo;
	smTRNAS_PLAYERINFO_QUICK	TransPlayerInfoQ;
	int			QuickSize;

	lpChar = srFindCharFromSerial(lpTransCommand->WParam);
	if (lpChar) {
		rsSendCharInfo(lpChar, lpSndPlayInfo);
		return TRUE;
	}

	lpPlayInfo = srFindUserFromSerial(lpTransCommand->WParam);
	if (lpPlayInfo && lpPlayInfo->dwObjectSerial && lpSndPlayInfo && lpSndPlayInfo->lpsmSock) {
		if (lpPlayInfo->smCharInfo.bUpdateInfo[0] != 0) {
			QuickSize = smCHAR_INFO_QUICK_SIZE2;
		}
		else {
			QuickSize = smCHAR_INFO_QUICK_SIZE;
		}

		memcpy(&TransPlayerInfoQ.smCharInfo, &lpPlayInfo->smCharInfo, QuickSize);
		TransPlayerInfoQ.size = sizeof(smTRNAS_PLAYERINFO_QUICK) - (sizeof(smCHAR_INFO) - QuickSize);
		TransPlayerInfoQ.code = smTRANSCODE_PLAYERINFO_Q;
		TransPlayerInfoQ.dwObjectSerial = lpPlayInfo->dwObjectSerial;
		TransPlayerInfoQ.x = lpPlayInfo->Position.x;
		TransPlayerInfoQ.y = lpPlayInfo->Position.y;
		TransPlayerInfoQ.z = lpPlayInfo->Position.z;

		return lpSndPlayInfo->lpsmSock->Send((char*)&TransPlayerInfoQ, TransPlayerInfoQ.size, TRUE);
	}

	return TRUE;
}

int srGetTotalExp(int exp, int level)
{
	if (level < 0)
	{
		level *= -1;
	}

	int result = 0;

	if (level <= 10)
	{
		result = exp;
	}
	if (level <= 20)
	{
		result = (int)(exp * 0.85);
	}
	if (level <= 30)
	{
		result = (int)(exp * 0.70);
	}
	else
	{
		result = (int)(exp * 0.55);
	}

	if (result < 0)
	{
		result = 0;
	}

	return result;
}

int rsSendTransSkillAttack(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo)
{
	TRANS_ATTACKDATA	TransAttackData;
	int	temp;

	if (lpChar->dwClanCode && lpChar->dwClanCode == lpPlayInfo->dwClanCode)
		return NULL;

	TransAttackData.code = smTRANSCODE_ATTACKDATA;
	TransAttackData.size = sizeof(TRANS_ATTACKDATA);

	TransAttackData.x = lpPlayInfo->Position.x;
	TransAttackData.y = lpPlayInfo->Position.y;
	TransAttackData.z = lpPlayInfo->Position.z;

	TransAttackData.AttackState = 0x80;

	TransAttackData.AttackSize = 32 * fONE;
	TransAttackData.Power = GetRandomPos(lpChar->smMonsterInfo.SkillDamage[0], lpChar->smMonsterInfo.SkillDamage[1]);

	TransAttackData.dwDestObjectSerial = lpChar->dwObjectSerial;
	TransAttackData.dwTarObjectSerial = lpPlayInfo->dwObjectSerial;

	TransAttackData.sRating[0] = lpChar->smCharInfo.Level;
	TransAttackData.sRating[1] = lpChar->smCharInfo.Attack_Rating;

	if (lpPlayInfo->dwSiegeItem_Scroll_Time && lpPlayInfo->dwSiegeItem_Scroll_Time < dwPlayServTime) {
		lpPlayInfo->dwSiegeItem_Scroll_Code = 0;
		lpPlayInfo->dwSiegeItem_Scroll_Time = 0;
	}
	if (lpPlayInfo->dwSiegeItem_Stone1_Time && lpPlayInfo->dwSiegeItem_Stone1_Time < dwPlayServTime) {
		lpPlayInfo->dwSiegeItem_Stone1_Code = 0;
		lpPlayInfo->dwSiegeItem_Stone1_Time = 0;
	}

	if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B) {
		TransAttackData.sRating[0] = -SKILL_PLAY_ICE_CRYSTAL;
		TransAttackData.sRating[1] = 4;
	}
	else if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G)
	{
		TransAttackData.sRating[0] = -SKILL_PLAY_LIGHTNING_CRYSTAL;
		TransAttackData.sRating[1] = 3;
	}
	else if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R) {
		TransAttackData.sRating[0] = -SKILL_PLAY_FIRE_CRYSTAL;
		TransAttackData.sRating[1] = 1;
	}

	if (lpPlayInfo->dwSiegeItem_Stone1_Code && lpPlayInfo->dwSiegeItem_Stone1_Code == lpChar->smCharInfo.dwCharSoundCode) {
		TransAttackData.Power /= 2;
		TransAttackData.sRating[0] = lpChar->smCharInfo.Level;
		TransAttackData.sRating[1] = lpChar->smCharInfo.Attack_Rating;
	}

	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBC1 | sin01)) {
		if (lpPlayInfo->Position.Area == rsCASTLE_FIELD) return FALSE;
	}
	if (lpPlayInfo->dwSiegeItem_Scroll_Code == (sinBI1 | sin05))
		return FALSE;

	if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time) {
		if (lpPlayInfo->dwSkill_PhysicalAbsorb_Time > dwPlayServTime) {
			TransAttackData.Power -= lpPlayInfo->dwSkill_PhysicalAbsorb_Param;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else {
			lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
			lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_MetalArmor_Time) {
		if (lpPlayInfo->dwSkill_MetalArmor_Time > dwPlayServTime) {
			TransAttackData.Power -= lpPlayInfo->dwSkill_MetalArmor_Param;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else {
			lpPlayInfo->dwSkill_MetalArmor_Time = 0;
			lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_HolyBody_Time) {
		if (lpPlayInfo->dwSkill_HolyBody_Time > dwPlayServTime) {
			if (lpChar->smCharInfo.Brood == smCHAR_MONSTER_UNDEAD) {
				TransAttackData.Power -= (TransAttackData.Power * lpPlayInfo->dwSkill_HolyBody_Param) / 100;
				if (TransAttackData.Power < 0) return FALSE;
			}
		}
		else {
			lpPlayInfo->dwSkill_HolyBody_Time = 0;
			lpPlayInfo->dwSkill_HolyBody_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_VirtualLife_Time) {
		if (lpPlayInfo->dwSkill_VirtualLife_Time > dwPlayServTime) {
			TransAttackData.Power -= (TransAttackData.Power * lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
			if (TransAttackData.Power < 0) return FALSE;
		}
		else {
			lpPlayInfo->dwSkill_VirtualLife_Time = 0;
			lpPlayInfo->dwSkill_VirtualLife_Param = 0;
		}
	}

	if (lpPlayInfo->dwSkill_EnergyShield_Time) {
		if (lpPlayInfo->dwSkill_EnergyShield_Time > dwPlayServTime) {
			temp = (TransAttackData.Power * lpPlayInfo->dwSkill_EnergyShield_Param) / 100;
			TransAttackData.Power -= temp;
			TransAttackData.AttackState |= (temp << 16);
			if (TransAttackData.Power < 0) return FALSE;
		}
		else {
			lpPlayInfo->dwSkill_EnergyShield_Time = 0;
			lpPlayInfo->dwSkill_EnergyShield_Param = 0;
		}
	}

	if (lpPlayInfo->dwBlessSkill_Code) {
		if (lpPlayInfo->dwBlessSkill_Code == SKILL_PLAY_BLESS_ABSORB) {
			if (lpPlayInfo->dwBlessSkill_Time > dwPlayServTime) {
				TransAttackData.Power -= lpPlayInfo->dwBlessSkill_Param;
				if (TransAttackData.Power < 0) return FALSE;
			}
			else {
				lpPlayInfo->dwBlessSkill_Code = 0;
				lpPlayInfo->dwBlessSkill_Time = 0;
			}
		}
	}

	if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CHAOSCARA && lpChar->smMonsterInfo.SkillRangeRect.left == 0 && lpChar->smMonsterInfo.SkillRangeRect.right == 0) {
		TransAttackData.sRating[0] = -SKILL_PLAY_CHAOSCARA_VAMP;
		TransAttackData.sRating[1] = 0;
	}

	TransAttackData.dwChkSum = TransAttackData.Power * 2002 +
		(TransAttackData.x * TransAttackData.y * TransAttackData.z);

	if (lpPlayInfo->lpsmSock) {
		lpPlayInfo->Send_AttackCount++;
		lpPlayInfo->Send_AttackDamage += TransAttackData.Power;

		if (rsServerConfig.CrazyPacketMode && lpPlayInfo->dwDecPacketCode &&
			lpPlayInfo->dwDecPacketTime2 < dwPlayServTime) {
			TransAttackData.code = smTRANSCODE_ATTACKDATA2;
			TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);

			if (lpPlayInfo)
				rsEncodeDamagePacket(lpPlayInfo, &TransAttackData);
		}
		else
			TransAttackData.dwDamageChkSum = dm_GetDamgeChkSum_S2V(&TransAttackData);

		return lpPlayInfo->lpsmSock->Send2((char*)&TransAttackData, TransAttackData.size, TRUE);
	}

	return NULL;
}

int rsCharChanger(smCHAR* lpChar, smCHAR_INFO* lpCharInfo, smCHAR_MONSTER_INFO* lpMonInfo)
{
	int rnd, OsCode;
	int dist;
	STG_AREA* lpStgArea;

	lpStgArea = (STG_AREA*)lpChar->lpExt1;

	lpChar->Close();
	lpChar->Flag = TRUE;

	rnd = lpChar->smCharInfo.bUpdateInfo[0];
	OsCode = lpChar->dwObjectSerial;

	memcpy(&lpChar->smCharInfo, lpCharInfo, sizeof(smCHAR_INFO));
	memcpy(&lpChar->smMonsterInfo, lpMonInfo, sizeof(smCHAR_MONSTER_INFO));
	lpChar->ActionPattern = 5;

	lpChar->SetLoadPattern(lpChar->smCharInfo.szModelName);

	dist = 64 * 30;
	lpChar->DistAroundDbl = dist * dist;
	lpChar->PosiAround.x = lpChar->pX;
	lpChar->PosiAround.z = lpChar->pZ;

	lpChar->ReopenCount = REOPEN_COUNT_NUM;
	lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
	lpChar->smCharInfo.bUpdateInfo[0] = rnd + 1;
	lpChar->dwObjectSerial = OsCode;
	lpChar->lpTargetPlayInfo = 0;
	lpChar->smCharInfo.Life[0] = lpChar->smCharInfo.Life[1];
	lpChar->smCharInfo.StatePoint = lpMonInfo->ClassCode;

	if (lpChar->smMonsterInfo.PotionCount) {
		if ((rand() % 100) < lpChar->smMonsterInfo.PotionPercent) {
			lpChar->smMonsterInfo.PotionCount = (rand() % lpChar->smMonsterInfo.PotionCount) + 1;
		}
		else {
			lpChar->smMonsterInfo.PotionCount = 0;
		}
	}

	return TRUE;
}

int	SelectDamageTop10(smCHAR* lpChar, rsUSER_LIST_TOP10* lpUserListDamageTop10)
{
	int cnt, cnt2;
	int ChkCnt;
	smWINSOCK* lpsmSock;

	if (!lpChar->lpAttackDamageList || !lpUserListDamageTop10) return FALSE;

	ZeroMemory(lpUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	for (cnt = 0; cnt < 10; cnt++) {
		ChkCnt = -1;
		for (cnt2 = 0; cnt2 < ATTACK_DAMAGE_LIST_MAX; cnt2++) {
			if (lpChar->lpAttackDamageList[cnt2].dwUserCode &&
				lpChar->lpAttackDamageList[cnt2].DamageCount > lpUserListDamageTop10->Damage[cnt]) {
				lpUserListDamageTop10->dwUserCode[cnt] = lpChar->lpAttackDamageList[cnt2].dwUserCode;
				lpUserListDamageTop10->Damage[cnt] = lpChar->lpAttackDamageList[cnt2].DamageCount;
				lpUserListDamageTop10->Counter[cnt] = lpChar->lpAttackDamageList[cnt2].Count;

				ChkCnt = cnt2;
			}
		}

		if (ChkCnt >= 0)
			lpChar->lpAttackDamageList[ChkCnt].dwUserCode = 0;
	}

	lpUserListDamageTop10->dwUpdateTime = dwPlayServTime;
	lpUserListDamageTop10->dwCharCode = lpChar->dwObjectSerial;

	lpUserListDamageTop10->code = smTRANSCODE_SYSTEM;
	lpUserListDamageTop10->size = sizeof(rsUSER_LIST_TOP10);
	lpUserListDamageTop10->tCode = smTRANS_SYSCODE_DMG_USER_LIST;
	lpUserListDamageTop10->dwObjectSerial = rsServerConfig.ServerCode;

	if (!dwSerToSerIP) return TRUE;

	lpsmSock = rsFindNextSertoServerSock();

	if (lpsmSock)
		return lpsmSock->Send((char*)lpUserListDamageTop10, lpUserListDamageTop10->size, TRUE);

	return FALSE;
}

DWORD dwSoD_ItemDropTable[8][2] = {
	{	(sinSD2 | sin01)	,	20	},
	{	(sinSD2 | sin02)	,	40	},
	{	(sinSD2 | sin03)	,	60	},
	{	(sinSD2 | sin04)	,	68	},
	{	(sinSD2 | sin05)	,	80	},
	{	(sinSD2 | sin06)	,	95	},
	{	(sinSD2 | sin07)	,	100	},
	{	0,0 }
};

int rsOpen_SodItem(smCHAR* lpChar, rsPLAYINFO* lprsPlayInfo)
{
	int rnd, cnt, cnt2;
	psITEM	psItem;
	STG_ITEMS* lpStgItem;

	rnd = rand() % 1000;
	if (rnd < 20) {
		rnd = rand() % 100;
		for (cnt = 0; cnt < 7; cnt++) {
			if (dwSoD_ItemDropTable[cnt][0] == 0) return FALSE;
			if ((DWORD)rnd < dwSoD_ItemDropTable[cnt][1]) {
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
					if (DefaultItems[cnt2].Item.CODE == dwSoD_ItemDropTable[cnt][0] && !DefaultItems[cnt2].Item.UniqueItem) {
						CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt2]);

						psItem.state = TRUE;
						lpStgItem = ((STG_AREA*)lpChar->lpExt1)->AddItem(&psItem, lpChar->pX >> FLOATNS, lpChar->pY >> FLOATNS, lpChar->pZ >> FLOATNS, TRUE);
						((STG_AREA*)lpChar->lpExt1)->SendStgItemToNearUsers(lpStgItem);

						break;
					}
				}
				return TRUE;
			}
		}
	}

	return FALSE;
}

int rsCheckEventItem(DWORD dwItemCode, rsPLAYINFO* lpPlayInfo, smCHAR* lpChar)
{
	int rnd;

	if (lpChar->smMonsterInfo.dwEvnetItem == (sinQT1 | sin13)) {
		rnd = rand() % 100;

		if (lpPlayInfo->smCharInfo.ChangeJob < 3 && rnd <= 20) {
			return TRUE;
		}
	}
	else
		return TRUE;

	return FALSE;
}

int rsOpen_MonsterItem(smCHAR* lpChar, rsPLAYINFO* lprsPlayInfo)
{
	if (lpChar->smMonsterInfo.UseRollDice)
	{
		DamageList[lpChar->dwObjectSerial].clear();
		return TRUE;
	}

	psITEM		sItem;
	psITEM* lpsItem = &sItem;
	STG_ITEMS* lpStgItem;
	smTRANS_COMMAND	smTransCommand;
	int			cnt, cnt2;
	DWORD		dwCode;

	rsPLAYINFO* lpDamagePlayInfo[10];
	int			DmgPlayUse = FALSE;

	if (rsUserListDamageTop10.dwCharCode && rsUserListDamageTop10.dwCharCode == lpChar->dwObjectSerial) {
		for (cnt = 0; cnt < 10; cnt++) {
			if (rsUserListDamageTop10.dwUserCode[cnt]) {
				lpDamagePlayInfo[cnt] = srFindUserFromSerial(rsUserListDamageTop10.dwUserCode[cnt]);
			}
			else
				lpDamagePlayInfo[cnt] = 0;
		}

#ifdef _LANGUAGE_KOREAN
#ifdef _TEST_SERVER

		TRANS_CHATMESSAGE	TransChatMessage;

		for (cnt2 = 0; cnt2 < 10; cnt2++) {
			if (lpDamagePlayInfo[cnt2] && lpDamagePlayInfo[cnt2]->AdminMode >= 3) {
				for (cnt = 0; cnt < 6; cnt++) {
					if (lpDamagePlayInfo[cnt]) {
						wsprintf(TransChatMessage.szMessage, "%s(%d)> %s ( %d  %d )",
							lpChar->smCharInfo.szName, cnt,
							lpDamagePlayInfo[cnt]->smCharInfo.szName,
							rsUserListDamageTop10.Damage[cnt],
							rsUserListDamageTop10.Counter[cnt]);

						TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 0;
						TransChatMessage.dwObjectSerial = lpDamagePlayInfo[cnt]->dwObjectSerial;
						lpDamagePlayInfo[cnt2]->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
					}
				}
			}
		}

#endif
#endif

		ZeroMemory(&rsUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));
		DmgPlayUse = TRUE;

		int	BabelHornSort[10];
		int	BabelHornSortCnt;

		BabelHornSortCnt = 2;
		BabelHornSort[0] = 0;
		BabelHornSort[1] = 1;

		for (cnt = 2; cnt < 10; cnt++) {
			for (cnt2 = 0; cnt2 < cnt; cnt2++) {
				if (lpDamagePlayInfo[cnt] && lpDamagePlayInfo[cnt]->lpsmSock &&
					lpDamagePlayInfo[cnt2] && lpDamagePlayInfo[cnt2]->lpsmSock &&
					lpDamagePlayInfo[cnt]->smCharInfo.JOB_CODE == lpDamagePlayInfo[cnt2]->smCharInfo.JOB_CODE) {
					break;
				}
			}
			if (cnt2 == cnt) {
				BabelHornSort[BabelHornSortCnt++] = cnt;
			}
		}

		if (rsServerConfig.Event_BabelHorn && lpChar->lpExt1) {
			if (BabelHornSortCnt <= 2) {
				for (cnt = 0; cnt < rsServerConfig.Event_BabelHorn; cnt++) {
					if (lpDamagePlayInfo[cnt] && lpDamagePlayInfo[cnt]->lpsmSock) {
						rsPutItem(lpDamagePlayInfo[cnt], (sinGF1 | sin02));
					}
				}
			}
			else {
				for (cnt = 0; cnt < rsServerConfig.Event_BabelHorn; cnt++) {
					if (cnt < BabelHornSortCnt) {
						cnt2 = BabelHornSort[cnt];
						if (lpDamagePlayInfo[cnt2] && lpDamagePlayInfo[cnt2]->lpsmSock) {
							rsPutItem(lpDamagePlayInfo[cnt2], (sinGF1 | sin02));
						}
					}
				}
			}
		}
	}

	if (lpChar->smMonsterInfo.dwEvnetItem) {
		if (rsCheckEventItem(lpChar->smMonsterInfo.dwEvnetItem, lprsPlayInfo, lpChar) == TRUE)
			rsPutItem(lprsPlayInfo, lpChar->smMonsterInfo.dwEvnetItem);
	}

	for (cnt = 0; cnt < lpChar->smMonsterInfo.FallItemPlusCount; cnt++) {
		if ((rand() % 10000) < lpChar->smMonsterInfo.FallItems_Plus[cnt].Percentage)
		{
			dwCode = lpChar->smMonsterInfo.FallItems_Plus[cnt].dwItemCode;
			for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
				if (DefaultItems[cnt2].Item.CODE == dwCode && !DefaultItems[cnt2].Item.UniqueItem) {
					CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt2]);
					if (rsServerConfig.Event_Potion) {
						if ((lpsItem->ItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
							lpsItem->ItemInfo.PotionCount = (rand() % rsServerConfig.Event_Potion) + 1;
						}
					}

					dwCode = (lpsItem->ItemInfo.CODE & sinITEM_MASK2);
					if (dwCode == sinMA2 || dwCode == sinQT1) {
						rsPutItem2(lprsPlayInfo, &lpsItem->ItemInfo);
						break;
					}

					dwCode = (lpsItem->ItemInfo.CODE & sinITEM_MASK2);

					if (lpChar->PartyFlag != rsHARDCORE_EVENT_FLAG || (lpsItem->ItemInfo.CODE != (sinGG1 | sin01) && (lpsItem->ItemInfo.CODE & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1)))
					{
						lpsItem->state = TRUE;
						lpStgItem = ((STG_AREA*)lpChar->lpExt1)->AddItem(lpsItem, lpChar->pX >> FLOATNS, lpChar->pY >> FLOATNS, lpChar->pZ >> FLOATNS, TRUE);

						if (lpStgItem)
						{
							if (lpChar->smMonsterInfo.AllSeeItem)
							{
								((STG_AREA*)lpChar->lpExt1)->SendStgItemToNearUsers(lpStgItem);
							}
							else
							{
								if (DmgPlayUse)
								{
									for (cnt2 = 0; cnt2 < 10; cnt2++)
									{
										if (lpDamagePlayInfo[cnt2])
										{
											((STG_AREA*)lpChar->lpExt1)->SendStgItem(lpDamagePlayInfo[cnt2], lpStgItem);
										}
									}
								}
								else
									((STG_AREA*)lpChar->lpExt1)->SendStgItem(lprsPlayInfo, lpStgItem);

								lpStgItem->dwCreateTime += 5000;
							}
						}
					}
					break;
				}
			}
		}
	}

	int FallItemMax = lpChar->smMonsterInfo.FallItemMax;

	if (FallItemMax > 0)
	{
		int	FallRandom = 0;

		if (lprsPlayInfo->dwTime_PrimeItem_X2) {
			switch (lprsPlayInfo->dwPrimeItem_PackageCode)
			{
			case PRIME_ITEM_PACKAGE_NONE:
				FallRandom = 50;
				break;
			case PRIME_ITEM_PACKAGE_BRONZE:
				FallRandom = 20;
				break;
			case PRIME_ITEM_PACKAGE_SILVER:
				FallRandom = 30;
				break;
			case PRIME_ITEM_PACKAGE_GOLD:
				FallRandom = 40;
				break;
			case PRIME_ITEM_PACKAGE_ULTRA:
				FallRandom = 50;
				break;
			case PRIME_ITEM_PACKAGE_NONE_50_EXPUP:
				FallRandom = 50;
				break;
			case PRIME_ITEM_PACKAGE_NONE_100_EXPUP:
				FallRandom = 50;
				break;
			}
		}

		if (lprsPlayInfo->TopLvL > 0)
		{
			FallRandom += 5;
		}

		if (lprsPlayInfo->dwTime_PrimeItem_HelpPet > 0)
		{
			FallRandom += 50;
		}

		if (lprsPlayInfo->Bl_RNo > 0)
			FallRandom += 50;

		if (FallRandom && (rand() % 100) < FallRandom)
		{
			FallItemMax++;
		}
	}

	if (rsServerConfig.ExpGameTimeMode == 3) {
		int giCnt = rsGetExp_GameTime(lprsPlayInfo);
		FallItemMax = (FallItemMax * giCnt) / 100;
		if (giCnt > 0 && FallItemMax == 0) {
			if ((rand() % 100) < giCnt) FallItemMax = 1;
		}
	}

	for (cnt = 0; cnt < FallItemMax; cnt++) {
		if (srGetMonsterItem(lprsPlayInfo, lpChar, lpsItem) == TRUE) {
			if (rsServerConfig.Event_Potion) {
				if ((lpsItem->ItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
					lpsItem->ItemInfo.PotionCount = (rand() % rsServerConfig.Event_Potion) + 1;
				}
			}

#ifdef _LANGUAGE_CHINESE
			if (rsServerConfig.ExpGameTimeMode == 3 && lpsItem->ItemInfo.CODE == (sinGG1 | sin01)) {
				lpsItem->ItemInfo.Money = (lpsItem->ItemInfo.Money * rsGetExp_GameTime(lprsPlayInfo)) / 100;
				if (!lpsItem->ItemInfo.Money) continue;
				ReformItem(&lpsItem->ItemInfo);
			}
#endif

			dwCode = (lpsItem->ItemInfo.CODE & sinITEM_MASK2);
			if (dwCode == sinMA2 || dwCode == sinQT1) {
				if (!lprsPlayInfo->smCharInfo.ChangeJob)
					rsPutItem2(lprsPlayInfo, &lpsItem->ItemInfo);
				else {
					if (lprsPlayInfo->smCharInfo.ChangeJob == 1 && lpsItem->ItemInfo.CODE == (sinQT1 | sin06)) {
						rsPutItem2(lprsPlayInfo, &lpsItem->ItemInfo);
					}
				}
			}
			else
			{
				if (lpChar->PartyFlag != rsHARDCORE_EVENT_FLAG || (lpsItem->ItemInfo.CODE != (sinGG1 | sin01) && (lpsItem->ItemInfo.CODE & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1)))
				{
					lpsItem->state = TRUE;
					lpStgItem = ((STG_AREA*)lpChar->lpExt1)->AddItem(lpsItem, lpChar->pX >> FLOATNS, lpChar->pY >> FLOATNS, lpChar->pZ >> FLOATNS, TRUE);

					if (lpStgItem)
					{
						if (lpChar->smMonsterInfo.AllSeeItem)
						{
							((STG_AREA*)lpChar->lpExt1)->SendStgItemToNearUsers(lpStgItem);
						}
						else
						{
							if (DmgPlayUse)
							{
								for (cnt2 = 0; cnt2 < 10; cnt2++)
								{
									if (lpDamagePlayInfo[cnt2])
									{
										((STG_AREA*)lpChar->lpExt1)->SendStgItem(lpDamagePlayInfo[cnt2], lpStgItem);
									}
								}
							}
							else
								((STG_AREA*)lpChar->lpExt1)->SendStgItem(lprsPlayInfo, lpStgItem);

							lpStgItem->dwCreateTime += 5000;
						}
					}
				}
			}
		}
	}

	DamageList[lpChar->dwObjectSerial].clear();
	return TRUE;
}

int rsOpen_MonsterExp(smCHAR* lpChar, rsPLAYINFO* lprsPlayInfo)
{
	if (lprsPlayInfo->BadPlayer) {
		int cnt = lprsPlayInfo->MonsterKillCounter;
		if (cnt > 45) cnt = 45;
		cnt = (lpChar->smMonsterInfo.GetExp * cnt) / 50;
		lpChar->smMonsterInfo.GetExp -= cnt;
	}

	int	ExpBack = 0;

	if (rsServerConfig.Event_ExpUp) {
		ExpBack = lpChar->smMonsterInfo.GetExp;

#ifdef	_LANGUAGE_PHILIPIN
		int ExpBackup;

		if (lprsPlayInfo->smCharInfo.Level < 25) ExpBackup = 400;

		else
		{
			if (rsServerConfig.Event_ExpUp >= 100 && rsServerConfig.Event_ExpUp < 200)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
			else if (rsServerConfig.Event_ExpUp >= 200 && rsServerConfig.Event_ExpUp < 300)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 200) / 100;
			else if (rsServerConfig.Event_ExpUp >= 300 && rsServerConfig.Event_ExpUp < 400)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 300) / 100;
			else if (rsServerConfig.Event_ExpUp >= 400)
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 400) / 100;

			else
				lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
		}

#else
		if (rsServerConfig.Event_ExpUp >= 100 && rsServerConfig.Event_ExpUp < 200)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
		else if (rsServerConfig.Event_ExpUp >= 200 && rsServerConfig.Event_ExpUp < 300)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 200) / 100;
		else if (rsServerConfig.Event_ExpUp >= 300 && rsServerConfig.Event_ExpUp < 400)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 300) / 100;
		else if (rsServerConfig.Event_ExpUp >= 400)
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 400) / 100;
		else
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;

#endif
	}

#ifdef _LANGUAGE_ARGENTINA
	if (rsServerConfig.Event_ExpUp_latin)
	{
		ExpBack = lpChar->smMonsterInfo.GetExp;

		if (lprsPlayInfo->smCharInfo.Level <= 20)
		{
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 200) / 100;
		}
		else if (lprsPlayInfo->smCharInfo.Level > 20 && lprsPlayInfo->smCharInfo.Level <= 30)
		{
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
		}
		else if (lprsPlayInfo->smCharInfo.Level > 80 && lprsPlayInfo->smCharInfo.Level <= 90)
		{
			lpChar->smMonsterInfo.GetExp += (lpChar->smMonsterInfo.GetExp * 100) / 100;
		}
		else
		{
			lpChar->smMonsterInfo.GetExp;
		}
	}
#endif

	if (lprsPlayInfo->dwPartyInfo) {
		if (!lprsPlayInfo->lpPartyMaster || lprsPlayInfo->lpPartyMaster->GetPartyExp(lpChar, lprsPlayInfo) == FALSE) {
			lprsPlayInfo->dwPartyInfo = PARTY_STATE_NONE;
			lprsPlayInfo->lpPartyMaster = NULL;
		}
	}
	else {
		smTRANS_EXP64 smTransEXP;
		smTransEXP.code = smTRANSCODE_ADDEXP;
		smTransEXP.size = sizeof(smTRANS_EXP64);
		smTransEXP.WParam = srGetTotalExp(lpChar->smMonsterInfo.GetExp, lprsPlayInfo->smCharInfo.Level);

		Quest::GetInstance()->UpdaterProgressOnServer(lprsPlayInfo, lpChar, smTRANSCODE_ADDEXP);

		int ExpUp = 0;

		if (lprsPlayInfo->dwTime_PrimeItem_ExpUp) {
			switch (lprsPlayInfo->dwPrimeItem_PackageCode)
			{
			case PRIME_ITEM_PACKAGE_NONE:
				ExpUp += 30;
				break;
			case PRIME_ITEM_PACKAGE_BRONZE:
				ExpUp += 10;
				break;
			case PRIME_ITEM_PACKAGE_SILVER:
				ExpUp += 20;
				break;
			case PRIME_ITEM_PACKAGE_GOLD:
				ExpUp += 30;
				break;
			case PRIME_ITEM_PACKAGE_ULTRA:
				ExpUp += 40;
				break;
			case PRIME_ITEM_PACKAGE_NONE_50_EXPUP:
				ExpUp += 50;
				break;
			case PRIME_ITEM_PACKAGE_NONE_100_EXPUP:
				ExpUp += 100;
				break;
			}
		}

		if (lprsPlayInfo->Bl_RNo > 0)
			ExpUp += 10;

		if (lprsPlayInfo->dwTime_PrimeItem_PhenixPet > 0)	// pluto Æê(ÇØ¿Ü) ¼öÁ¤
		{
			ExpUp += 10;
		}

		if (rsServerConfig.ExpGameTimeMode)
		{
			smTransEXP.WParam = (smTransEXP.WParam * rsGetExp_GameTime(lprsPlayInfo)) / 100;
		}

		if (ExpUp)
		{
			//À¯·á ¾ÆÀÌÅÛ »ç¿ëÁß ¶Ç´Â PC¹æ °¡¸ÍÁ¡ ( °æÇèÄ¡ 30% Ãß°¡ )
			smTransEXP.WParam += (smTransEXP.WParam * ExpUp) / 100;
		}

		smTransEXP.LParam = lpChar->dwObjectSerial;					//¸ó½ºÅÍ °íÀ¯¹øÈ£
		smTransEXP.SParam = (smTransEXP.WParam * 3 + smTransEXP.LParam * 13) * 2002;	//Á¶ÀÛ ¹æÁö ÇÁ·ÎÅØÅÍ ÄÚµå

		lprsPlayInfo->spEXP_Out += smTransEXP.WParam;		//³ª°£ °æÇèÄ¡ ±â·Ï
		smTransEXP.EParam = smTransEXP.SParam ^ lprsPlayInfo->spEXP_Out;

		lprsPlayInfo->lpsmSock->Send2((char*)&smTransEXP, smTransEXP.size, TRUE);
	}

	if (ExpBack)
		lpChar->smMonsterInfo.GetExp = ExpBack;

	lprsPlayInfo->MonsterKillCounter++;

	rsMonHuntCount++;
	return TRUE;
}

int rsOpen_MonsterItemExp(rsKILL_MONSTER_INFO* lpKillMonInfo)
{
	rsPLAYINFO* lprsPlayInfo;
	smCHAR	smChar;
	int		cnt;

	for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
		if (chrMonInfoList[cnt].dwAutoCharCode == lpKillMonInfo->dwAutoCharCode &&
			chrMonsterList[cnt].dwCharSoundCode == lpKillMonInfo->dwCharSoundCode) {
			memcpy(&smChar.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
			memcpy(&smChar.smMonsterInfo, &chrMonInfoList[cnt], sizeof(smCHAR_MONSTER_INFO));
			break;
		}
	}
	if (cnt >= chrMonsterCnt) return FALSE;

	if (lpKillMonInfo->PartyFlag == rsHARDCORE_EVENT_FLAG && lpKillMonInfo->dwParam[0] >= sinPM1) {
		CreatePresentItem(lpKillMonInfo->dwParam[0], &StageArea[lpKillMonInfo->Area], lpKillMonInfo->x, lpKillMonInfo->y, lpKillMonInfo->z, 3);
		return TRUE;
	}

	lprsPlayInfo = srFindUserFromSerial(lpKillMonInfo->dwUserObjectSerial);
	if (!lprsPlayInfo) return FALSE;

	smChar.pX = lpKillMonInfo->x;
	smChar.pY = lpKillMonInfo->y;
	smChar.pZ = lpKillMonInfo->z;
	smChar.dwObjectSerial = lpKillMonInfo->dwMonObjectSerial;
	smChar.PartyFlag = lpKillMonInfo->PartyFlag;
	smChar.lpExt1 = &StageArea[lpKillMonInfo->Area];
	smChar.lpExt2 = 0;
	smChar.lpExt3 = 0;
	smChar.lpExt4 = 0;

	rsOpen_MonsterItem(&smChar, lprsPlayInfo);
	rsOpen_MonsterExp(&smChar, lprsPlayInfo);
	return TRUE;
}

int srAutoCharMain(smCHAR* lpChar)
{
	return TRUE;
}

smCHAR* Serv_CheckOtherPlayPosi(int x, int y, int z)
{
	int cnt;
	int dist;
	int dx, dz;
	smCHAR* lpChar;
	STG_AREA* lpStgArea_AutoPlayer;

	lpStgArea_AutoPlayer = (STG_AREA*)lpActiveChar->lpExt1;

	if (!lpStgArea_AutoPlayer) 	return NULL;

	for (cnt = 0; cnt < lpStgArea_AutoPlayer->MonsterLastPoint; cnt++) {
		lpChar = lpStgArea_AutoPlayer->lpCharMonster[cnt];

		if (lpChar && lpActiveChar != lpChar && lpChar->smCharInfo.Life[0] > 0) {
			if ((y - 32 * fONE) < lpChar->pY && (y + 32 * fONE) > lpChar->pY) {
				dx = (lpChar->pX - x) >> FLOATNS;
				dz = (lpChar->pZ - z) >> FLOATNS;
				dist = dx * dx + dz * dz;
				if (dist < (32 * 32)) return lpChar;
			}
		}
	}

	return NULL;
}

int rsSendGameServer_PrimeItem(rsPLAYINFO* lpPlayInfo)
{
	PREMIUM_TIME	smPremiumTime;

	if (lpPlayInfo && lpPlayInfo->dwPrimeItem_NextSetTime < dwPlayServTime)
	{
		lpPlayInfo->dwPrimeItem_NextSetTime = dwPlayServTime + 1000;

		STG_AREA* lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);

		if (lpStgArea && lpStgArea->lpField->State != FIELD_STATE_VILLAGE)
		{
			if (lpPlayInfo->dwTime_PrimeItem_X2 > 0)			lpPlayInfo->dwTime_PrimeItem_X2--;
			if (lpPlayInfo->dwTime_PrimeItem_ExpUp > 0)			lpPlayInfo->dwTime_PrimeItem_ExpUp--;
			if (lpPlayInfo->dwTime_PrimeItem_VampCuspid > 0)	lpPlayInfo->dwTime_PrimeItem_VampCuspid--;
			if (lpPlayInfo->dwTime_PrimeItem_ManaRecharg > 0)	lpPlayInfo->dwTime_PrimeItem_ManaRecharg--;
			if (lpPlayInfo->dwTime_PrimeItem_MightofAwell > 0)	lpPlayInfo->dwTime_PrimeItem_MightofAwell--;
			if (lpPlayInfo->dwTime_PrimeItem_MightofAwell2 > 0) lpPlayInfo->dwTime_PrimeItem_MightofAwell2--;
			if (lpPlayInfo->dwTime_PrimeItem_ManaReduce > 0)	lpPlayInfo->dwTime_PrimeItem_ManaReduce--;
			if (lpPlayInfo->dwTime_PrimeItem_PhenixPet > 0)		lpPlayInfo->dwTime_PrimeItem_PhenixPet--;
			if (lpPlayInfo->dwTime_PrimeItem_HelpPet > 0)		lpPlayInfo->dwTime_PrimeItem_HelpPet--;
			if (lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX > 0) lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX--;
			if (lpPlayInfo->dwTime_PrimeItem_StaminaReduce > 0) lpPlayInfo->dwTime_PrimeItem_StaminaReduce--;
			if (lpPlayInfo->dwTime_PrimeItem_BigHead > 0) lpPlayInfo->dwTime_PrimeItem_BigHead--;
			if (lpPlayInfo->dwForceOrb_SaveTime > 0) lpPlayInfo->dwForceOrb_SaveTime--;

			smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
			smPremiumTime.size = sizeof(PREMIUM_TIME);
			smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
			smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
			smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
			smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
			smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
			smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
			smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
			smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
			smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
			smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
			smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
			smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;

			if (lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send2((char*)&smPremiumTime, smPremiumTime.size, TRUE);
		}
	}

	return TRUE;
}

int srAutoPlayMain()
{
	int cnt, ChrCnt;

	dwPlayTime = GetCurrentTime();

	if ((srAutoPlayCount & 3) == 0) {
		ActivePlayCounter = 0;

		for (ChrCnt = 0; ChrCnt < AUTOPLAYER_MAX; ChrCnt++) {
			if (chrAutoPlayer[ChrCnt].Flag && chrAutoPlayer[ChrCnt].MotionInfo) {
				lpActiveChar = &chrAutoPlayer[ChrCnt];
				if (chrAutoPlayer[ChrCnt].NearPlayCount || chrAutoPlayer[ChrCnt].MotionInfo->State == CHRMOTION_STATE_DEAD ||
					chrAutoPlayer[ChrCnt].smMonsterInfo.EventCode) {
					srAutoCharMain(&chrAutoPlayer[ChrCnt]);
					chrAutoPlayer[ChrCnt].NearPlayCount--;
				}
				else {
					if (lpActiveChar->smCharInfo.State == smCHAR_STATE_ENEMY && !lpActiveChar->smMonsterInfo.EventCode) {
						lpActiveChar->ReopenCount--;
						if (lpActiveChar->ReopenCount <= 0) {
							if (lpActiveChar->smMonsterInfo.Boss < dwPlayServTime)
							{
								lpActiveChar->Close();
								((STG_AREA*)lpActiveChar->lpExt1)->MonsterCount--;
								((STG_AREA*)lpActiveChar->lpExt1)->DeleteMonTable(lpActiveChar);
							}
						}
					}
				}
				ActivePlayCounter++;
			}
		}
	}

	srAutoPlayCount++;
	if ((srAutoPlayCount & 0x3F) == 0) {
		rsAutoPlayTransCount++;
	}

	for (cnt = 0; cnt < STAGE_AREA_MAX; cnt++) {
		if (StageArea[cnt].lpStage) {
			StageArea[cnt].Main();
		}
	}

	if ((srAutoPlayCount & 0x3FF) == 0) {
		dwServ_GameTimeHour = GetGameTimeHour();

		if (dwServ_GameTimeHour >= GAME_HOUR_DAY && dwServ_GameTimeHour < GAME_HOUR_DARKNESS)
			dwServ_NightDay = FALSE;
		else
			dwServ_NightDay = TRUE;
	}

	return TRUE;
}

int srTransPlayData(rsPLAYINFO* lpPlayInfo)
{
	char TransBuff[TRANS_BUFF_SIZE];
	char* lpTransBuff;
	smPLAYDATA_GROUP* lpPlayDataGroup;
	int cnt;
	smPLAYDATA* lpPlayData;
	int dist;
	int size;
	int x, z;
	int PlayDataCnt;
	smCHAR* lpChar;
	int	TransDataCount;
	int	TransOver;
	int	ClipCnt;
	int SndFlag;
	smTRANS_COMMAND* lpTransCommand;
	smTRANS_COMMAND_EX* lpTransCommandEx;
	int SoloMode = 0;

	lpPlayDataGroup = (smPLAYDATA_GROUP*)TransBuff;
	lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);

	lpPlayDataGroup->code = smTRANSCODE_PLAYDATAGROUP;

	lpPlayDataGroup->dwSendCode = 0x80000000 + (lpPlayInfo->SendPlayGroupCount & 0x00FFFFFF);

	PlayDataCnt = 0;
	TransDataCount = 0;
	SndFlag = 0;

	TransOver = lpPlayInfo->LastTransAutoPlayCount + AUTOPLAYER_MAX;

	if (lpPlayInfo->Position.Area == QUEST_ARENA_FIELD && lpPlayInfo->AdminMode <= 3) SoloMode = TRUE;

	if (lpPlayInfo->lpChrTarget) {
		lpChar = lpPlayInfo->lpChrTarget;
		if (lpChar->Flag && lpChar->dwObjectSerial == lpPlayInfo->dwTarObjSerial &&
			lpChar->srTransBuffSize) {
			x = (lpChar->pX - lpPlayInfo->Position.x) >> FLOATNS;
			z = (lpChar->pZ - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x * x + z * z;

			if (dist < DIST_TRANSLEVEL_HIGH && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
				size = ((smTRANS_PLAYDATA*)lpChar->srTransBuff)->size;
				memcpy(lpTransBuff, lpChar->srTransBuff, size);
				lpTransBuff += size;
				TransDataCount += 3;
				PlayDataCnt++;
				lpChar->NearPlayCount = 256;
			}
			else {
				lpPlayInfo->lpChrTarget = 0;
			}
		}
		else {
			lpPlayInfo->lpChrTarget = 0;
		}
	}

	for (cnt = lpPlayInfo->LastTransAutoPlayCount; cnt < TransOver; cnt++) {
		ClipCnt = cnt & AUTOPLAYER_MASK;

		if (SoloMode && chrAutoPlayer[ClipCnt].dwLinkObjectCode != lpPlayInfo->dwObjectSerial) {
			if (chrAutoPlayer[ClipCnt].smCharInfo.Brood != smCHAR_MONSTER_USER || chrAutoPlayer[ClipCnt].lpMasterPlayInfo != lpPlayInfo)
				continue;
		}

		if (chrAutoPlayer[ClipCnt].Flag && chrAutoPlayer[ClipCnt].srTransBuffSize) {
			lpChar = &chrAutoPlayer[ClipCnt];
			x = (lpChar->pX - lpPlayInfo->Position.x) >> FLOATNS;
			z = (lpChar->pZ - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x * x + z * z;

			if (dist < DIST_TRANSLEVEL_CONNECT && lpPlayInfo->lpChrTarget != lpChar &&
				abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
				size = ((smTRANS_PLAYDATA*)lpChar->srTransBuff)->size;

				if ((lpTransBuff - TransBuff + size) >= (TRANS_BUFF_SIZE - sizeof(smTRANS_COMMAND))) {
					lpPlayDataGroup->size = (lpTransBuff - TransBuff);
					lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
					lpPlayInfo->lpsmSock->Send((char*)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);

					PlayDataCnt = 0;
					lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);
					SndFlag++;
					break;
				}

				if (lpPlayInfo->Position.Area == rsCASTLE_FIELD && chrAutoPlayer[ClipCnt].DontMoveFlag) {
					if (chrAutoPlayer[ClipCnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B ||
						chrAutoPlayer[ClipCnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR)
					{
						dist = DIST_TRANSLEVEL_HIGH - 1;
					}
				}

				if (dist < DIST_TRANSLEVEL_HIGH) {
					memcpy(lpTransBuff, lpChar->srTransBuff, size);
					lpTransBuff += size;
					TransDataCount += 3;
					PlayDataCnt++;
					lpChar->NearPlayCount = 256;
					if (TransDataCount >= TRANS_MAX_CHAR_LIMIT) break;
				}
				else {
					if (lpChar->MotionInfo->State != CHRMOTION_STATE_DEAD) {
						lpPlayData = (smPLAYDATA*)lpTransBuff;

						lpPlayData->size = sizeof(smPLAYDATA);
						lpPlayData->code = smTRANSCODE_PLAYDATA1;
						lpPlayData->x = lpChar->pX;
						lpPlayData->y = lpChar->pY;
						lpPlayData->z = lpChar->pZ;

						lpPlayData->angle[0] = lpChar->Angle.x;
						lpPlayData->angle[1] = lpChar->Angle.y;
						lpPlayData->angle[2] = lpChar->Angle.z;
						lpPlayData->angle[3] = (short)lpChar->MotionInfo->State;
						lpPlayData->frame = lpChar->frame;
						lpPlayData->dwObjectSerial = lpChar->dwObjectSerial;
						lpPlayData->dwAutoCharCode = lpChar->smMonsterInfo.dwAutoCharCode;

						lpTransBuff += sizeof(smPLAYDATA);

						TransDataCount++;
						PlayDataCnt++;
						lpChar->NearPlayCount = 256;
						if (TransDataCount >= TRANS_MAX_CHAR_LIMIT) break;
					}
				}
			}
		}
	}

	if (lpPlayInfo->Position.Area == BabelPlayField && dwBabelPlayTime > dwPlayServTime) {
		lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
		lpTransCommand->code = smTRANSCODE_PLAY_COMMAND;
		lpTransCommand->size = sizeof(smTRANS_COMMAND);
		lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
		lpTransCommand->LParam = smCOMMAND_PLAY_BABEL;
		lpTransCommand->SParam = BabelPlayField;
		lpTransCommand->EParam = 0;
		lpTransBuff += sizeof(smTRANS_COMMAND);
	}

	if (lpPlayInfo->Position.Area == rsCASTLE_FIELD && StageArea[rsCASTLE_FIELD].dwActiveMode) {
		lpTransCommandEx = (smTRANS_COMMAND_EX*)lpTransBuff;
		lpTransCommandEx->code = smTRANSCODE_PLAY_COMMAND;
		lpTransCommandEx->size = sizeof(smTRANS_COMMAND_EX);
		lpTransCommandEx->WParam = lpPlayInfo->dwObjectSerial;
		lpTransCommandEx->LParam = smCOMMAND_PLAY_BELSS_CASTLE;
		lpTransCommandEx->SParam = (rsBlessCastle.CastleMode << 16) | ((rsBlessCastle.DefenceLevel) & 0xFFFF);
		lpTransCommandEx->EParam = rsBlessCastle.dwMasterClan;
		lpTransCommandEx->WxParam = ((int*)rsBlessCastle.TimeSec)[0];
		lpTransCommandEx->LxParam = ((int*)rsBlessCastle.bCrystalSolderCount)[0];
		lpTransCommandEx->SxParam = ((int*)lpPlayInfo->sBlessCastle_Damage)[0];
		lpTransCommandEx->ExParam = 0;
		lpTransBuff += sizeof(smTRANS_COMMAND_EX);

		((int*)lpPlayInfo->sBlessCastle_Damage)[0] = 0;
	}

	//if (lpPlayInfo->Position.Area == 3 || lpPlayInfo->Position.Area == 49)
	//{
	//	lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
	//	lpTransCommand->code = smTRANSCODE_PLAY_COMMAND;
	//	lpTransCommand->size = sizeof(smTRANS_COMMAND);
	//	lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
	//	lpTransCommand->LParam = smCOMMAND_PLAY_BA;
	//	lpTransCommand->SParam = rsBattleArena.Flag;
	//	lpTransCommand->EParam = rsBattleArena.Time;
	//	lpTransBuff += sizeof(smTRANS_COMMAND);
	//}

	if (lpPlayInfo->Position.Area == rsCASTLE_FIELD)
	{
		lpTransCommandEx = (smTRANS_COMMAND_EX*)lpTransBuff;
		lpTransCommandEx->code = smTRANSCODE_PLAY_COMMAND;
		lpTransCommandEx->size = sizeof(smTRANS_COMMAND_EX);
		lpTransCommandEx->WParam = lpPlayInfo->dwObjectSerial;
		lpTransCommandEx->LParam = smCOMMAND_PLAY_PVP_SCORE;
		lpTransCommandEx->SParam = lpPlayInfo->BattlePoint;
		lpTransCommandEx->EParam = lpPlayInfo->DeathPoint;
		lpTransBuff += sizeof(smTRANS_COMMAND_EX);
	}

	if (lpPlayInfo->Position.Area == 47 || lpPlayInfo->Position.Area == 9)
	{
		lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
		lpTransCommand->code = smTRANSCODE_PLAY_COMMAND;
		lpTransCommand->size = sizeof(smTRANS_COMMAND);
		lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
		lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
		lpTransCommand->SParam = lpPlayInfo->Position.Area;
		lpTransCommand->EParam = 0;
		lpTransBuff += sizeof(smTRANS_COMMAND);
	}

	if (rsServerConfig.Enable_PKField_All)
	{
		if (rsServerConfig.Enable_PKField >= 0 && StageArea[lpPlayInfo->Position.Area].dwActiveMode && lpPlayInfo->Position.Area != 3 && lpPlayInfo->Position.Area != 21)
		{
			if (lpPlayInfo->Position.Area >= 11 && lpPlayInfo->Position.Area <= 34)
			{
				lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
				lpTransCommand->code = smTRANSCODE_PLAY_COMMAND;
				lpTransCommand->size = sizeof(smTRANS_COMMAND);
				lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
				lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
				lpTransCommand->SParam = lpPlayInfo->Position.Area;
				lpTransCommand->EParam = 0;
				lpTransBuff += sizeof(smTRANS_COMMAND);
			}
		}
	}
	else
	{
		if (lpPlayInfo->Position.Area == rsServerConfig.Enable_PKField && rsServerConfig.Enable_PKField >= 0 && StageArea[rsServerConfig.Enable_PKField].dwActiveMode)
		{
			lpTransCommand = (smTRANS_COMMAND*)lpTransBuff;
			lpTransCommand->code = smTRANSCODE_PLAY_COMMAND;
			lpTransCommand->size = sizeof(smTRANS_COMMAND);
			lpTransCommand->WParam = lpPlayInfo->dwObjectSerial;
			lpTransCommand->LParam = smCOMMAND_PLAY_PK_FIELD;
			lpTransCommand->SParam = rsServerConfig.Enable_PKField;
			lpTransCommand->EParam = 0;
			lpTransBuff += sizeof(smTRANS_COMMAND);
		}
	}

	if (SndFlag == 0) {
		lpPlayDataGroup->size = (lpTransBuff - TransBuff);
		lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
		lpPlayInfo->lpsmSock->Send((char*)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);
	}

	ClipCnt = cnt & AUTOPLAYER_MASK;
	lpPlayInfo->LastTransAutoPlayCount = ClipCnt;
	lpPlayInfo->SendPlayGroupCount++;

	if ((lpPlayInfo->SendPlayGroupCount & 0x1F) == 0)
	{
		if (rsServerConfig.Event_HardCore)
		{
			if (rsCheckHardCoreEventArea(lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z) == TRUE)
			{
				if (lpPlayInfo->EventMode != rsHARDCORE_EVENT_FLAG)
				{
					lpPlayInfo->AreaOutCount++;

					if (lpPlayInfo->AreaOutCount == 10)
					{
						smTRANS_COMMAND	smTransCommand;
						smTransCommand.size = sizeof(smTRANS_COMMAND);
						smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
						smTransCommand.WParam = 1840;
						smTransCommand.SParam = lpPlayInfo->smCharInfo.Level;
						smTransCommand.LParam = 9100;
						rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
						lpPlayInfo->AreaOutCount = 0;
					}
				}
			}
		}
	}

	return TRUE;
}

#define TRANS_MAX_USER_LIMIT_OVER		(TRANS_MAX_USER_LIMIT*4)

int rsConnectViewDist = DIST_TRANSLEVEL_CONNECT;

int srTransPlayUserData(rsPLAYINFO* lpPlayInfo)
{
	char TransBuff[TRANS_BUFF_SIZE];
	char* lpTransBuff;
	smPLAYDATA_GROUP* lpPlayDataGroup;
	int cnt;
	smPLAYDATA* lpPlayData;
	int dist;
	int size;
	int x, z;
	int PlayDataCnt;
	int TransDataCount;
	int	sbCnt;

	rsPLAYINFO* lpPlayInfo2;
	TRANS_CHATMESSAGE	TransChatMessage;
	int	TransOver;
	int	ClipCnt;
	int SndFlag;
	int	ddist;
	DWORD	dwSendFrame;
	DWORD	dwRecvFrame;

	int sLen;
	int SoloMode = 0;

	lpPlayDataGroup = (smPLAYDATA_GROUP*)TransBuff;
	lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);

	lpPlayDataGroup->code = smTRANSCODE_PLAYDATAGROUP;

	lpPlayDataGroup->dwSendCode = lpPlayInfo->SendPlayGroupCount & 0x00FFFFFF;

	PlayDataCnt = 0;
	TransDataCount = 0;
	SndFlag = 0;

	if (lpPlayInfo->dwPartyInfo == PARTY_STATE_MASTER && lpPlayInfo->PartyUpdateFlag && !rsServerConfig.szLinkServerIP[0]) {
		lpPlayInfo->UpdatePartyPlayInfo();
	}

	if (lpPlayInfo->Position.Area == QUEST_ARENA_FIELD) SoloMode = TRUE;

	if (lpPlayInfo->szChatMessage[0]) {
		sLen = lstrlen(lpPlayInfo->szChatMessage) + 1;
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(lpPlayInfo->szChatMessage);
		TransChatMessage.dwObjectSerial = lpPlayInfo->dwObjectSerial;
		memcpy(TransChatMessage.szMessage, lpPlayInfo->szChatMessage, sLen);

		if (lpPlayInfo->ChatMsgMode) {
			TransChatMessage.dwIP = lpPlayInfo->ChatMsgMode;
			lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
			ddist = DIST_TRANSLEVEL_LOW;
		}
		else {
			TransChatMessage.dwIP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
			ddist = DIST_TRANSLEVEL_HIGH;
		}

		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			if (rsPlayInfo[cnt].lpsmSock && &rsPlayInfo[cnt] != lpPlayInfo && rsPlayInfo[cnt].TransInfoFlag &&
				(!SoloMode || rsPlayInfo[cnt].AdminMode >= 3)) {
				lpPlayInfo2 = &rsPlayInfo[cnt];

				x = (lpPlayInfo2->Position.x - lpPlayInfo->Position.x) >> FLOATNS;
				z = (lpPlayInfo2->Position.z - lpPlayInfo->Position.z) >> FLOATNS;
				dist = x * x + z * z;

				if (dist < ddist && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
					lpPlayInfo2->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
				}
			}
		}
		lpPlayInfo->szChatMessage[0] = 0;
	}
	else
		sLen = 0;

	if ((lpPlayInfo->dwLastMotionRecvTime + 10000) < dwPlayServTime) return FALSE;

	TransOver = lpPlayInfo->LastTransPlayUserCount + CONNECTMAX;

	for (cnt = lpPlayInfo->LastTransPlayUserCount; cnt < TransOver; cnt++) {
		ClipCnt = cnt & CONNECTMAX_MASK;

		if (rsPlayInfo[ClipCnt].lpsmSock && &rsPlayInfo[ClipCnt] != lpPlayInfo && rsPlayInfo[ClipCnt].TransInfoFlag &&
			rsPlayInfo[ClipCnt].srRecvPlayBuffCnt > 0 && !rsPlayInfo[ClipCnt].HideMode &&
			(!SoloMode || rsPlayInfo[ClipCnt].AdminMode >= 3)) {
			lpPlayInfo2 = &rsPlayInfo[ClipCnt];
			dwRecvFrame = lpPlayInfo2->srRecvPlayBuffCnt;
			dwSendFrame = lpPlayInfo->dwSendFrames[ClipCnt];

			x = (lpPlayInfo2->Position.x - lpPlayInfo->Position.x) >> FLOATNS;
			z = (lpPlayInfo2->Position.z - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x * x + z * z;

			if (dist < rsConnectViewDist && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
				if (lpPlayInfo2->PlayBuffSleep && dwSendFrame >= dwRecvFrame) {
					if (dist < DIST_TRANSLEVEL_HIGH) {
						sbCnt = srPLAYBUFF_MAX;
					}
					else {
						sbCnt = -1;
					}
				}
				else {
					if (!dwSendFrame || dwSendFrame >= dwRecvFrame) {
						sbCnt = -1;
						lpPlayInfo->dwSendFrames[ClipCnt] = dwRecvFrame;
					}
					else {
						if ((dwRecvFrame - dwSendFrame) > srPLAYBUFF_MASK)
							dwSendFrame = dwRecvFrame - srPLAYBUFF_MASK;

						sbCnt = dwSendFrame & srPLAYBUFF_MASK;
						dwSendFrame++;
						lpPlayInfo->dwSendFrames[ClipCnt] = dwSendFrame;
					}
				}

				if (sbCnt >= 0) {
					size = ((smTRANS_PLAYDATA*)lpPlayInfo2->srPlayBuff[sbCnt])->size;

					if ((lpTransBuff - TransBuff + size) >= TRANS_BUFF_SIZE) {
						lpPlayDataGroup->size = (lpTransBuff - TransBuff);
						lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
						lpPlayInfo->lpsmSock->Send((char*)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);

						PlayDataCnt = 0;
						lpTransBuff = TransBuff + sizeof(smPLAYDATA_GROUP);
						SndFlag++;
						break;
					}

					if (lpPlayInfo->BefUserPacketLoop > TRANS_MAX_USER_LIMIT_OVER &&
						dist > DIST_TRANSLEVEL_NEAR && sbCnt != srPLAYBUFF_MAX) {
						dist = DIST_TRANSLEVEL_HIGH;
					}

					if (dist < DIST_TRANSLEVEL_HIGH) {
						memcpy(lpTransBuff, lpPlayInfo2->srPlayBuff[sbCnt], size);
						lpTransBuff += size;

						if (sbCnt == srPLAYBUFF_MAX)
							TransDataCount += 2;
						else
							TransDataCount += 4;

						PlayDataCnt++;
						if (TransDataCount >= TRANS_MAX_USER_LIMIT) break;
					}
					else {
						lpPlayData = (smPLAYDATA*)lpTransBuff;

						lpPlayData->size = sizeof(smPLAYDATA);
						lpPlayData->code = smTRANSCODE_PLAYDATA1;
						lpPlayData->x = lpPlayInfo2->Position.x;
						lpPlayData->y = lpPlayInfo2->Position.y;
						lpPlayData->z = lpPlayInfo2->Position.z;

						lpPlayData->angle[0] = 0;
						lpPlayData->angle[1] = 0;
						lpPlayData->angle[2] = 0;
						lpPlayData->angle[3] = 0;
						lpPlayData->frame = 0;
						lpPlayData->dwObjectSerial = lpPlayInfo2->dwObjectSerial;
						lpPlayData->dwAutoCharCode = 0;

						lpTransBuff += sizeof(smPLAYDATA);

						TransDataCount++;
						PlayDataCnt++;
						if (TransDataCount >= TRANS_MAX_USER_LIMIT) break;
					}
				}
			}
		}

		if (cnt == CONNECTMAX) {
			lpPlayInfo->BefUserPacketLoop = lpPlayInfo->UserPacketLoop;
			lpPlayInfo->UserPacketLoop = 0;
		}
	}

	if (SndFlag == 0 && (PlayDataCnt || (lpPlayInfo->SendPlayGroupCount & 3) == 0)) {
		lpPlayDataGroup->size = (lpTransBuff - TransBuff);
		lpPlayDataGroup->PlayDataCnt = PlayDataCnt;
		lpPlayInfo->lpsmSock->Send((char*)lpPlayDataGroup, lpPlayDataGroup->size, TRUE);
	}

	ClipCnt = cnt & CONNECTMAX_MASK;
	lpPlayInfo->LastTransPlayUserCount = ClipCnt;
	lpPlayInfo->SendPlayGroupCount++;
	lpPlayInfo->UserPacketLoop += TransDataCount;

	return TRUE;
}

DWORD srAutoTransCounter = 0;

int srAutoTransPlay()
{
	int cnt;

	int start;
	DWORD	dwWaitTime;

	smTRANS_COMMAND	smTransCommand;
	char	szTempBuff[128];

	if (AutoPlayServer) {
		start = srAutoTransCounter & 0x3F;

		for (cnt = start; cnt < CONNECTMAX; cnt += 0x40) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
				(dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) < OVER_TRANS_TIME) {
				srTransPlayData(&rsPlayInfo[cnt]);

				rsSendGameServerExp(&rsPlayInfo[cnt]);
			}
		}
	}

	if (UserPlayServer) {
		start = srAutoTransCounter & 0x1F;

		for (cnt = start; cnt < CONNECTMAX; cnt += 0x20) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
				((dwPlayServTime - rsPlayInfo[cnt].dwLastRecvTime) < OVER_TRANS_TIME || rsPlayInfo[cnt].PlayBuffSleep)) {
				srTransPlayUserData(&rsPlayInfo[cnt]);
			}
		}

		if (start == 0x3F) {
			for (cnt = 0; cnt < CONNECTMAX; cnt++) {
				if (rsPlayInfo[cnt].lpsmSock) {
					if (rsPlayInfo[cnt].PlayBuffSleep != 0) {
						rsPlayInfo[cnt].PlayBuffSleep++;
					}
				}
			}
		}
	}

	for (cnt = (srAutoTransCounter & 0x1FF); cnt < CONNECTMAX; cnt += 0x200) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwLastRecvTime) {
			if (rsServerConfig.ExpGameTimeMode && rsPlayInfo[cnt].dwExpGameTimeCheck &&
				rsPlayInfo[cnt].Position.Area < STAGE_AREA_MAX && StageArea[rsPlayInfo[cnt].Position.Area].lpField)
			{
				int gTimeChk = rsPlayInfo[cnt].dwExpGameTime / (1000 * 60);
				int gTimeOld = rsPlayInfo[cnt].dwExpGameTime;

				rsPlayInfo[cnt].dwExpGameTime += (dwPlayServTime - rsPlayInfo[cnt].dwExpGameTimeCheck);

				if (rsServerConfig.ExpGameTimeMode == 3) {
					rsDispay_GameTime(&rsPlayInfo[cnt], gTimeOld);
				}

				if (rsServerConfig.ExpGameTimeMode == 2) {
					int gTime = rsPlayInfo[cnt].dwExpGameTime / (1000 * 60);
					if (gTime > (5 * 60 - 5) && gTimeChk != gTime) {
						TRANS_CHATMESSAGE	TransChatMessage;
						wsprintf(TransChatMessage.szMessage, srMsg_Bl_01, (5 * 60) - gTime);
						TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 3;
						TransChatMessage.dwObjectSerial = 0;
						rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

						if (gTime >= 5 * 60) {
							rsSendCloseClient(&rsPlayInfo[cnt]);
						}
					}
				}

				rsPlayInfo[cnt].dwExpGameTimeCheck = dwPlayServTime;
			}

			if (!rsPlayInfo[cnt].smCharInfo.dwEventTime_T)
			{
				rsPlayInfo[cnt].smCharInfo.dwEventTime_T = 0;
				rsPlayInfo[cnt].smCharInfo.SizeLevel = 1;
			}

			if (!rsPlayInfo[cnt].dwStartUser_PresentItem_Count)
			{
				rsStartUser_PresentItem(&rsPlayInfo[cnt]);
			}

			if (UserPlayServer && (rsPlayInfo[cnt].dwMacroChkTime + 60000) > dwPlayServTime) {
				if (rsPlayInfo[cnt].Position.Area < STAGE_AREA_MAX && StageArea[rsPlayInfo[cnt].Position.Area].lpField &&
					StageArea[rsPlayInfo[cnt].Position.Area].lpField->State == FIELD_STATE_VILLAGE) {
					rsPlayInfo[cnt].dwMacroAngTime = 0;
					rsPlayInfo[cnt].dwMacroTime = 0;
				}

				if (rsPlayInfo[cnt].dwMacroAngTime && rsPlayInfo[cnt].dwMacroAngTime + (60000 * 2) < dwPlayServTime) {
					rsPlayInfo[cnt].dwMacroAngTime = 0;
					rsPlayInfo[cnt].dwMacroTime = 0;
				}
				if (rsPlayInfo[cnt].dwMacroTime && rsPlayInfo[cnt].dwMacroTime + (60000 * 60) < dwPlayServTime) {
					smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
					smTransCommand.size = sizeof(smTRANS_COMMAND);
					smTransCommand.WParam = 8102;
					smTransCommand.LParam = (dwPlayServTime - rsPlayInfo[cnt].dwMacroTime) / 60000;
					smTransCommand.SParam = rsPlayInfo[cnt].Position.Area;
					smTransCommand.EParam = rsServerConfig.ServerCode;
					rsSendDataServer(rsPlayInfo[cnt].lpsmSock, &smTransCommand);

					rsPlayInfo[cnt].dwMacroAngTime = 0;
					rsPlayInfo[cnt].dwMacroTime = 0;
				}
			}

			dwWaitTime = rsPlayInfo[cnt].dwLastRecvTime + (1000 * 60 * 6);

			if (dwWaitTime < dwPlayServTime ||
				(rsPlayInfo[cnt].dwHopeDisconnectTime && rsPlayInfo[cnt].dwHopeDisconnectTime < dwPlayServTime)) {
				if (rsPlayInfo[cnt].lpsmSock) {
					wsprintf(szTempBuff, "ID( %s ) Name( %s ) IP( %s ) TimeOut Message\r\n",
						rsPlayInfo[cnt].szID, rsPlayInfo[cnt].szName, rsPlayInfo[cnt].lpsmSock->szIPAddr);

					Record_TempLogFile(szTempBuff);
				}

				DisconnectUser(rsPlayInfo[cnt].lpsmSock);
			}

			if (rsServerConfig.ClientFuncCheckMode) {
				if (rsPlayInfo[cnt].dwClientFunChk_NextTime < dwPlayServTime) {
					rsCheckClientFuncMem(&rsPlayInfo[cnt]);
					rsPlayInfo[cnt].dwClientFunChk_NextTime = dwPlayServTime + 60 * 1000;

					if (!rsPlayInfo[cnt].dwFuncChkErrorFlag) {
						if (rsPlayInfo[cnt].FuncChkFailCount1 > 10 || rsPlayInfo[cnt].FuncChkFailCount2 > 10) {
							if (rsPlayInfo[cnt].lpsmSock) {
								wsprintf(szTempBuff, "ID( %s ) Name( %s ) IP( %s ) Func Check Out Message\r\n",
									rsPlayInfo[cnt].szID, rsPlayInfo[cnt].szName, rsPlayInfo[cnt].lpsmSock->szIPAddr);
								Record_TempLogFile(szTempBuff);
							}

							DisconnectUser(rsPlayInfo[cnt].lpsmSock);
						}
						else {
							if (rsPlayInfo[cnt].ClientFunChk1_Count > 60) {
								rsPlayInfo[cnt].ClientFunChk1_Count = 0;
								rsPlayInfo[cnt].FuncChkFailCount1 = 0;
								rsPlayInfo[cnt].FuncChkSucessCount1 = 0;
							}
							if (rsPlayInfo[cnt].ClientFunChk2_Count > 80) {
								rsPlayInfo[cnt].ClientFunChk2_Count = 0;
								rsPlayInfo[cnt].FuncChkFailCount2 = 0;
								rsPlayInfo[cnt].FuncChkSucessCount2 = 0;
							}

							if ((rsPlayInfo[cnt].ClientFunChk1_Count > 10 && rsPlayInfo[cnt].FuncChkSucessCount1 < (rsPlayInfo[cnt].ClientFunChk1_Count >> 1)) ||
								(rsPlayInfo[cnt].ClientFunChk2_Count > 10 && rsPlayInfo[cnt].FuncChkSucessCount2 < (rsPlayInfo[cnt].ClientFunChk2_Count >> 1))) {
								smTransCommand.WParam = 1132;
								if (rsPlayInfo[cnt].ClientFunChk1_Count)
									smTransCommand.LParam = (rsPlayInfo[cnt].FuncChkSucessCount1 * 100) / rsPlayInfo[cnt].ClientFunChk1_Count;
								else
									smTransCommand.LParam = 0;

								if (rsPlayInfo[cnt].ClientFunChk2_Count)
									smTransCommand.SParam = (rsPlayInfo[cnt].FuncChkSucessCount2 * 100) / rsPlayInfo[cnt].ClientFunChk2_Count;
								else
									smTransCommand.SParam = 0;

								RecordHackLogFile(&rsPlayInfo[cnt], &smTransCommand);

								DisconnectUser(rsPlayInfo[cnt].lpsmSock);
							}
						}
					}
				}
			}
		}

		if (smWSock[cnt].sock && smWSock[cnt].dwLastRecvTime &&
			(smWSock[cnt].dwLastRecvTime + 1000 * 60 * 8) < dwPlayServTime) {
			wsprintf(szTempBuff, "Socket IP( %s ) TimeOut Message\r\n", smWSock[cnt].szIPAddr);
			Record_TempLogFile(szTempBuff);

			DisconnectUser(&smWSock[cnt]);
		}
	}

	srAutoTransCounter++;
	return TRUE;
}

static int srBillingCounter = 0;

static DWORD dwBillingTime = 0;

#ifdef _LANGUAGE_PHILIPIN
char* srMsg_Bl_100p = "%sYou can play until %d:%d - %d/%d/%d %s Pay2Play is Ongoing,Top up Now.";
char* srMsg_Bl_1001p = "%sYou can play until %d:0%d - %d/%d/%d %s Pay2Play is Ongoing,Top up Now.";
#endif

char* szClass[12]
{
	NULL,
	"Senhor da Guerra",
	"Furia de Metal",
	"Fênix Certeira",
	"Mestre Ceifador",
	"Rainha Valhala",
	"Paladino Templario",
	"Bruxo Arcano",
	"Arcanjo Celestial",
	"Sra. Das Sombras",
	"Senhor das Almas",
	"Mestra das Artes"
};

int srDisplayBillingTime(rsPLAYINFO* lpPlayInfo, int Add_BillingTime)
{
	int Coin = 0, Time = 0, TopLvL = 0, TopPvP = 0, Title = 0;
	int Define = 0;

	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512], szName[32];
		SQL::GetInstance()->EnterSqlSection();

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[CoinShop_Coin] WHERE [ID]='%s'", lpPlayInfo->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &Coin);
			}
		}

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[TimeShop_Time] WHERE [ID]='%s'", lpPlayInfo->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &Time);
			}
		}

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[Battle] WHERE [Character]='%s'", lpPlayInfo->szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &lpPlayInfo->BattlePoint);
				SQL::GetInstance()->GetDataValue(3, &lpPlayInfo->DeathPoint);
			}
		}

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[AccountType] WHERE [ID]='%s'", lpPlayInfo->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &Title);
			}
		}

		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[LevelList] WHERE [Character]='%s'", lpPlayInfo->szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[LevelList] SET Exp=%I64d,Class=%d,Level=%d WHERE [Character]='%s'", lpPlayInfo->spExp_Start + lpPlayInfo->spEXP_Out, lpPlayInfo->smCharInfo.JOB_CODE, lpPlayInfo->smCharInfo.Level, lpPlayInfo->szName);
			}
			else
			{
				wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[LevelList] ([Character],[Exp],[Class],[Level],[Define]) values('%s',%I64d,%d,%d,0)", lpPlayInfo->szName, lpPlayInfo->spExp_Start + lpPlayInfo->spEXP_Out, lpPlayInfo->smCharInfo.JOB_CODE, lpPlayInfo->smCharInfo.Level);
			}
			SQL::GetInstance()->Execute(szQuery);
		}

		wsprintf(szQuery, "SELECT TOP 1 * FROM [PristonDB].[dbo].[Battle] WHERE [Class]=%d ORDER BY BattlePoint DESC", lpPlayInfo->smCharInfo.JOB_CODE);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, szName);
				if (lstrcmp(szName, lpPlayInfo->szName) == 0)
				{
					TopPvP++;
				}
			}
		}

		wsprintf(szQuery, "SELECT TOP 1 * FROM [PristonDB].[dbo].[LevelList] WHERE [Class]=%d ORDER BY Level DESC, Define DESC", lpPlayInfo->smCharInfo.JOB_CODE);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, szName);
				if (lstrcmp(szName, lpPlayInfo->szName) == 0)
				{
					lpPlayInfo->TopLvL = 1;
					lpPlayInfo->Define = 1;
					TopLvL++;
				}
				else
				{
					lpPlayInfo->TopLvL = 0;
					lpPlayInfo->Define = 0;
				}
			}
		}

		SQL::GetInstance()->LeaveSqlSection();
	}

	if (TopPvP)
		rsSendServerChatMessageToAllUser(12, "O Rei PvP %s acabou de entrar.", lpPlayInfo->szName);
	if (TopLvL)
		rsSendServerChatMessageToAllUser(12, "%s: %s acabou de entrar.", szClass[lpPlayInfo->smCharInfo.JOB_CODE], lpPlayInfo->szName);

	smTRANS_TOP packet;
	packet.size = sizeof(smTRANS_TOP);
	packet.code = smTRANSCODE_TOP_PVP;
	packet.flag = TopPvP;
	lpPlayInfo->lpsmSock->Send((char*)&packet, packet.size, TRUE);

	packet.size = sizeof(smTRANS_TOP);
	packet.code = smTRANSCODE_TOP_LVL;
	packet.flag = TopLvL;
	lpPlayInfo->lpsmSock->Send((char*)&packet, packet.size, TRUE);

	rsSendServerChatMessageToUser(lpPlayInfo, 3, "Bem vindo ao PT SworD");
	rsSendServerChatMessageToUser(lpPlayInfo, 3, "ptsword.com");
	rsSendServerChatMessageToUser(lpPlayInfo, 3, "Dúvidas? Acesse nosso Discord!", OpenBossTimeMin);
	rsSendServerChatMessageToUser(lpPlayInfo, 3, "Você tem %d Coins", Coin);
	rsSendServerChatMessageToUser(lpPlayInfo, 3, "Você tem %d Time", Time);

	smTRANS_COMMAND packet2;
	packet2.size = sizeof(smTRANS_COMMAND);
	packet2.code = smTRANSCODE_SEND_COIN_SHOP_COIN;
	packet2.WParam = Coin;
	lpPlayInfo->lpsmSock->Send((char*)&packet2, packet2.size, TRUE);

	packet2.size = sizeof(smTRANS_COMMAND);
	packet2.code = smTRANSCODE_SEND_TIME_SHOP_TIME;
	packet2.WParam = Time;
	lpPlayInfo->lpsmSock->Send((char*)&packet2, packet2.size, TRUE);

	packet2.size = sizeof(smTRANS_COMMAND);
	packet2.code = smTRANSCODE_TYPE;
	packet2.SParam = Title;
	lpPlayInfo->lpsmSock->Send((char*)&packet2, packet2.size, TRUE);

	packet2.size = sizeof(smTRANS_COMMAND);
	packet2.code = smTRANSCODE_POINTS;
	packet2.SParam = lpPlayInfo->BattlePoint;
	packet2.WParam = lpPlayInfo->DeathPoint;
	lpPlayInfo->lpsmSock->Send((char*)&packet2, packet2.size, TRUE);

	PACKET_CROWN ps;
	ps.size = sizeof(PACKET_CROWN);
	ps.code = smTRANSCODE_BLESSCROWN;
	ps.Silver = GetClanCode(rsBlessCastle.ClanTop10.dwUserCode[1]);
	ps.Bronze = GetClanCode(rsBlessCastle.ClanTop10.dwUserCode[2]);
	lpPlayInfo->lpsmSock->Send((char*)&ps, ps.size, true);

	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		if (SQL::GetInstance()->Execute("SELECT * FROM [PristonDB].[dbo].[SkillDelay]"))
		{
			smTRANS_COMMAND ps;
			ps.size = sizeof(smTRANS_COMMAND);
			ps.code = smTRANSCODE_SKILL_DELAY;
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &ps.WParam);
				SQL::GetInstance()->GetDataValue(2, &ps.SParam);
				lpPlayInfo->lpsmSock->Send((char*)&ps, ps.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	PACKET_ITEM_CLASS ps2;
	ps2.size = sizeof(PACKET_ITEM_CLASS);
	ps2.code = smTRANSCODE_ITEM_CLASS;
	ps2.weapon = lpPlayInfo->WeaponClass;
	ps2.armor = lpPlayInfo->ArmorClass;
	ps2.shield = lpPlayInfo->ShieldClass;
	ps2.bracelets = lpPlayInfo->BraceletsClass;
	ps2.gauntlets = lpPlayInfo->GauntletsClass;
	ps2.boots = lpPlayInfo->BootsClass;
	ps2.ring = lpPlayInfo->RingClass;
	ps2.amy = lpPlayInfo->AmyClass;
	ps2.shel = lpPlayInfo->ShelClass;
	ps2.time = lpPlayInfo->TimeClass;
	lpPlayInfo->lpsmSock->Send((char*)&ps2, ps2.size, TRUE);

	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[PlayerMigration] WHERE [Name]='%s'", lpPlayInfo->szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			smTRANS_COMMAND ps;
			ps.size = sizeof(smTRANS_COMMAND);
			ps.code = smTRANSCODE_PLAYER_MIGRATION;
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &ps.WParam);
				lpPlayInfo->lpsmSock->Send((char*)&ps, ps.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}

	//smTRANS_CHAR_COMMAND ps3;
	//ps3.size = sizeof(smTRANS_CHAR_COMMAND);
	//ps3.code = smTRANSCODE_PLAYER_ACTION;
	//ps3.WParam = 1;
	//lstrcpy(ps3.szName, lpPlayInfo->szName);

	//smTRANS_CHAR_COMMAND ps4;
	//ps4.size = sizeof(smTRANS_CHAR_COMMAND);
	//ps4.code = smTRANSCODE_PLAYER_ACTION;
	//ps4.WParam = 1;

	//for (int cnt = 0; cnt < CONNECTMAX; cnt++)
	//{
	//	if (rsPlayInfo[cnt].lpsmSock)
	//	{
	//		rsPlayInfo[cnt].lpsmSock->Send((char*)&ps3, ps3.size, TRUE);
	//		if (lstrcmp(lpPlayInfo->szName, rsPlayInfo[cnt].szName) != 0)
	//		{
	//			lstrcpy(ps4.szName, rsPlayInfo[cnt].szName);
	//			lpPlayInfo->lpsmSock->Send((char*)&ps4, ps4.size, TRUE);
	//		}
	//	}
	//}

	BattleArena::GetInstance()->SendInformation(lpPlayInfo);
	BattleArena::GetInstance()->SendUpgrade(lpPlayInfo);

	BattleEvent::GetInstance()->SendInformation(lpPlayInfo);
	BattleEvent::GetInstance()->SendUpgrade(lpPlayInfo);

	HellGates::GetInstance()->SendInformation(lpPlayInfo);

	//Battle::GetInstance()->GetExpByCharacter(lpPlayInfo);
	//lpPlayInfo->BattleLevel = Battle::GetInstance()->GetLevelByExp(lpPlayInfo->BattleExp);
	//Battle::GetInstance()->SendBattleExp(lpPlayInfo);

	return TRUE;
}

void AddMin(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[TimeShop_Time] WHERE [ID]='%s'", Player->szID);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			if (SQL::GetInstance()->Fetch())
				wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[TimeShop_Time] SET Time=Time+1 WHERE [ID]='%s'", Player->szID);
			else
				wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[TimeShop_Time] ([ID],[Time]) values('%s',1)", Player->szID);
			SQL::GetInstance()->Execute(szQuery);
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

int  srBillingMain()
{
	int cnt;
	int Time;
	int HiddenPeriod;

	srBillingCounter++;

	for (cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
		{
			//if (rsPlayInfo[cnt].Position.Area < STAGE_AREA_MAX && StageArea[rsPlayInfo[cnt].Position.Area].lpField)
			//{
			//	if (!rsPlayInfo[cnt].dwStartUser_PresentItem_Count)
			//	{
			//		rsStartUser_PresentItem(&rsPlayInfo[cnt]);
			//	}
			//}

			rsStartUser_PresentItem(&rsPlayInfo[cnt]);

			if (rsPlayInfo[cnt].dwCountMin)
			{
				if (rsPlayInfo[cnt].dwCountMin < dwPlayServTime)
				{
					AddMin(&rsPlayInfo[cnt]);
					TimeShop::GetInstance()->SendTime(&rsPlayInfo[cnt]);
					rsPlayInfo[cnt].dwCountMin = dwPlayServTime + 1000 * 60;
				}
			}
			else
			{
				rsPlayInfo[cnt].dwCountMin = dwPlayServTime + 1000 * 60;
			}
		}
	}

	if ((srBillingCounter & 0xF) == 0) {
		cnt = (srBillingCounter >> 4) & CONNECTMAX_MASK;

		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szID[0] && rsPlayInfo[cnt].szName[0] &&
			rsPlayInfo[cnt].dwObjectSerial) {
			if (rsPlayInfo[cnt].Bl_RNo) {
				if (rsPlayInfo[cnt].Bl_RNo > 0 || ((srBillingCounter >> 4) & CONNECTMAX) == 0) {
					bSql_PCUse(&rsPlayInfo[cnt]);
				}
			}
			if (UseDLL_Expined) {
				bUrs_Expined(&rsPlayInfo[cnt]);
			}
		}
	}

	if ((srBillingCounter & 0xFFF) != 0) {
		return FALSE;
	}

	if (dwBillingTime >= dwPlayServTime)
		return FALSE;

	dwBillingTime = dwPlayServTime;

	smTRANS_COMMAND	smTransCommand;
	TRANS_CHATMESSAGE	TransChatMessage;

	smTransCommand.code = smTRANSCODE_CLOSECLIENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szID[0] && rsPlayInfo[cnt].szName[0] && rsPlayInfo[cnt].dwObjectSerial) {
			if (rsPlayInfo[cnt].dwPeriodTime2) {
				Time = rsPlayInfo[cnt].dwPeriodTime2 - tServerTime;
				if (Time < 6 * 60 && Time>0) {
					if (rsPlayInfo[cnt].dwPeriodTime != rsPlayInfo[cnt].dwPeriodTime2) {
						rsPlayInfo[cnt].dwPeriodTime = rsPlayInfo[cnt].dwPeriodTime2;
					}
					HiddenPeriod = TRUE;
				}
				else
					HiddenPeriod = FALSE;
			}
			else {
				HiddenPeriod = FALSE;
			}

			if (rsPlayInfo[cnt].DisuseDay && HiddenPeriod == FALSE) {
				Time = rsPlayInfo[cnt].DisuseDay - tServerTime;

				if (Time < 6 * 60 && Time>0) {
					if (Time < 5 * 60) {
						wsprintf(TransChatMessage.szMessage, srMsg_Bl_01, Time / 60);
						TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 3;
						TransChatMessage.dwObjectSerial = 0;
						if (rsServerConfig.DispBillingTime) rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
					}
					bSql_PCSearchReserv(&rsPlayInfo[cnt]);
				}

				if (rsPlayInfo[cnt].DisuseDay < tServerTime) {
					rsPlayInfo[cnt].lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

					Record_BillingLogFile(&rsPlayInfo[cnt], rsPlayInfo[cnt].DisuseDay, rsPlayInfo[cnt].dwPeriodTime, tServerTime, rsPlayInfo[cnt].Bl_RNo);
				}
			}

			if (rsPlayInfo[cnt].dwPeriodTime) {
				Time = rsPlayInfo[cnt].dwPeriodTime - tServerTime;

				if (Time < 6 * 60 && Time>0) {
					if (Time < 5 * 60) {
						wsprintf(TransChatMessage.szMessage, srMsg_Bl_01, Time / 60);
						TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwIP = 3;
						TransChatMessage.dwObjectSerial = 0;
						if (rsServerConfig.DispBillingTime)  rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
					}
					bSql_PCSearchReserv(&rsPlayInfo[cnt]);
				}

				if (Time <= 0) {
					rsPlayInfo[cnt].lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
					if (!HiddenPeriod) {
						Record_BillingLogFile(&rsPlayInfo[cnt], rsPlayInfo[cnt].DisuseDay, rsPlayInfo[cnt].dwPeriodTime, tServerTime, rsPlayInfo[cnt].Bl_RNo);
					}
				}
			}
		}
	}

	return TRUE;
}

void UpdateUnitStatus(rsPLAYINFO* pcUser)
{
	pcUser->sUnitStatusContainer.iHeader = smTRANSCODE_PLAYDATAGROUP;
	pcUser->sUnitStatusContainer.iCounter = pcUser->iUnitStatusCounter & 0x00FFFFFF;

	pcUser->sUnitStatusContainerM.iHeader = smTRANSCODE_PLAYDATAGROUP;
	pcUser->sUnitStatusContainerM.iCounter = (pcUser->iUnitStatusCounter & 0x00FFFFFF) - 0x80000000;

	//pcUser->sSkillStatusContainer.iHeader = PKTHDR_SkillStatusContainer;

	pcUser->iUnitStatusCounter++;

	//Priority
	if (pcUser->PlayBuffSleep != 0)
	{
		pcUser->PlayBuffSleep++;

		UINT uPriorityCounter = (pcUser->uPriorityCounter++);
		if (pcUser->uPriority < 4)
		{
			if (uPriorityCounter > 960)
			{
				pcUser->uPriority = 4;
			}
			else if (uPriorityCounter > 240)
			{
				pcUser->uPriority = 3;
			}
			else if (uPriorityCounter > 120)
			{
				pcUser->uPriority = 2;
			}
			else if (uPriorityCounter > 60)
			{
				pcUser->uPriority = 1;
			}
			else
			{
				pcUser->uPriority = 0;
			}
		}

		//AFK check
		if (uPriorityCounter > 1920)
		{
			pcUser->bAFK = TRUE;
		}
		else
		{
			pcUser->bAFK = FALSE;
		}
	}
	else
	{
		pcUser->uPriorityCounter = 0;
		pcUser->uPriority = 0;

		pcUser->bAFK = FALSE;
	}
}

void UserUpdate()
{
	static UINT iWheel = 0;

	uUsersInGame = 0;

	for (UINT i = 0; i < CONNECTMAX; i++)
	{
		if (rsPlayInfo[i].lpsmSock && rsPlayInfo[i].szID[0] && rsPlayInfo[i].szName[0] && rsPlayInfo[i].dwObjectSerial)
		{
			uUsersInGame++;

			UpdateUnitStatus(&rsPlayInfo[i]);

			if ((i % 32) == (iWheel % 32))
			{
				rsPlayInfo[i].b32 = TRUE;

				if ((i % 64) == (iWheel % 64))
				{
					rsPlayInfo[i].b64 = TRUE;
				}
				else
				{
					rsPlayInfo[i].b64 = FALSE;
				}
			}
			else
			{
				rsPlayInfo[i].b32 = FALSE;
				rsPlayInfo[i].b64 = FALSE;
			}

			if ((i % 512) == (iWheel % 512))
			{
				DWORD dwDisconnectTime = rsPlayInfo[i].dwHopeDisconnectTime;

				if (dwDisconnectTime != 0)
				{
					if (dwPlayServTime > dwDisconnectTime)
					{
						DisconnectUser(rsPlayInfo[i].lpsmSock);
					}
				}

				/*DWORD dwTimeLastPacketReceived = rsPlayInfo[i].dwLastRecvTime;

				if (dwTimeLastPacketReceived != 0)
				{
					SocketData* sd = rsPlayInfo[i].lpsmSock->lpSocketData;

					if ((sd->bKeepAlive == FALSE))
					{
						DWORD dwLag = dwPlayServTime - dwTimeLastPacketReceived;

						if (dwLag > MAX_LAGGRACE)
						{
							DisconnectUser(rsPlayInfo[i].lpsmSock);
						}
					}
				}*/
			}
		}
	}

	iWheel++;
}

void GetPTDistanceXZ(rsPLAYPOS* psCompare, rsPLAYPOS* psCompare2, int& a, int& b, int& c)
{
	int iXD = psCompare->x - psCompare2->x;
	int iZD = psCompare->z - psCompare2->z;

	iXD >>= 8;
	iZD >>= 8;

	int iXDM = iXD;
	int iZDM = iZD;

	iXDM *= iXDM;
	iZDM *= iZDM;

	a = (iXDM + iZDM);
	b = abs(iXD);
	c = abs(iZD);
}

void GetPTDistanceXZY(rsPLAYPOS* psCompare, rsPLAYPOS* psCompare2, int& a, int& b, int& c, int& d)
{
	int iXD = psCompare->x - psCompare->x;
	int iZD = psCompare->z - psCompare->y;
	int iYD = psCompare->y - psCompare->z;

	iXD >>= 8;
	iZD >>= 8;
	iYD >>= 8;

	int iXDM = iXD;
	int iZDM = iZD;
	int iYDM = iYD;

	iXDM *= iXDM;
	iZDM *= iZDM;
	iYDM *= iYDM;

	a = (iXDM + iZDM + iYDM);
	b = abs(iXD);
	c = abs(iZD);
	d = abs(iYD);
}

BOOL WithinPTDistance(rsPLAYPOS* psCompare, rsPLAYPOS* psCompare2, int iDistance)
{
	int iDistanceA, iDistanceB, iDistanceC;

	GetPTDistanceXZ(psCompare, psCompare2, iDistanceA, iDistanceB, iDistanceC);

	if ((iDistanceA < (iDistance << 8)) && (iDistanceB < 0x1000) && (iDistanceC < 0x1000))
		return TRUE;

	return FALSE;
}

BOOL CanSee(rsPLAYINFO* Player)
{
	if (Player->HideMode)
		return FALSE;

	return TRUE;
}

BOOL CanSee(smCHAR* Mob, rsPLAYINFO* Player)
{
	if (Player->Position.Area >= 0 && Player->Position.Area < 50 && Mob->lpStage)
	{
		STG_AREA* lpStgArea = &StageArea[Player->Position.Area];
		if (lpStgArea && lpStgArea)
		{
			if (lpStgArea->lpStage != Mob->lpStage)
				return FALSE;
		}
	}

	return TRUE;
}

void ClearUnitStatus(rsPLAYINFO* pcUser)
{
	if ((pcUser->sUnitStatusContainer.iAmount > 0) || (pcUser->uBufferPosition > 0))
	{
		pcUser->sUnitStatusContainer.iLength = sizeof(Packet) + sizeof(int) + sizeof(int) + pcUser->uBufferPosition;

		pcUser->lpsmSock->Send((char*)&pcUser->sUnitStatusContainer, pcUser->sUnitStatusContainer.iLength, true);

		pcUser->uBufferPosition = 0;
		pcUser->sUnitStatusContainer.iAmount = 0;
	}
}

void ClearSkillStatus(rsPLAYINFO* pcUser)
{
	if ((pcUser->sSkillStatusContainer.iAmount > 0) || (pcUser->uBufferPositionS > 0))
	{
		pcUser->sSkillStatusContainer.iLength = sizeof(Packet) + sizeof(int) + pcUser->uBufferPositionS;

		pcUser->lpsmSock->Send((char*)&pcUser->sSkillStatusContainer, pcUser->sSkillStatusContainer.iLength, true);

		pcUser->uBufferPositionS = 0;
		pcUser->sSkillStatusContainer.iAmount = 0;
	}
}

void ClearUnitStatusM(rsPLAYINFO* pcUser)
{
	if ((pcUser->sUnitStatusContainerM.iAmount > 0) || (pcUser->uBufferPositionM > 0))
	{
		pcUser->sUnitStatusContainerM.iLength = sizeof(Packet) + sizeof(int) + sizeof(int) + pcUser->uBufferPositionM;

		pcUser->lpsmSock->Send((char*)&pcUser->sUnitStatusContainerM, pcUser->sUnitStatusContainerM.iLength, true);

		pcUser->uBufferPositionM = 0;
		pcUser->sUnitStatusContainerM.iAmount = 0;
	}
}

void SendUnitStatus(rsPLAYINFO* pcUser, Packet* psPacket, BOOL bIncrementAmount)
{
	if (psPacket->iLength > 0x2038)
		return;

	UINT uFreeSpace = 0x2038 - pcUser->uBufferPosition;

	if (psPacket->iLength > uFreeSpace)
		ClearUnitStatus(pcUser);

	BYTE* buf = ((BYTE*)pcUser->sUnitStatusContainer.baBuffer) + pcUser->uBufferPosition;

	CopyMemory(buf, psPacket, psPacket->iLength);

	pcUser->uBufferPosition += psPacket->iLength;
	if (bIncrementAmount)
		pcUser->sUnitStatusContainer.iAmount++;
}

void SendUnitStatusM(rsPLAYINFO* pcUser, Packet* psPacket, BOOL bIncrementAmount)
{
	if (psPacket->iLength > 0x2038)
		return;

	UINT uFreeSpace = 0x2038 - pcUser->uBufferPositionM;

	if (psPacket->iLength > uFreeSpace)
		ClearUnitStatusM(pcUser);

	BYTE* buf = ((BYTE*)pcUser->sUnitStatusContainerM.baBuffer) + pcUser->uBufferPositionM;

	CopyMemory(buf, psPacket, psPacket->iLength);

	pcUser->uBufferPositionM += psPacket->iLength;
	if (bIncrementAmount)
		pcUser->sUnitStatusContainerM.iAmount++;
}

void SendSkillStatus(rsPLAYINFO* pcUser, Packet* psPacket, BOOL bIncrementAmount)
{
	if (psPacket->iLength > 0x1FF4)
		return;

	UINT uFreeSpace = 0x1FF4 - pcUser->uBufferPositionS;

	if (psPacket->iLength > uFreeSpace)
		ClearSkillStatus(pcUser);

	BYTE* buf = ((BYTE*)pcUser->sSkillStatusContainer.baBuffer) + pcUser->uBufferPositionS;

	CopyMemory(buf, psPacket, psPacket->iLength);

	pcUser->uBufferPositionS += psPacket->iLength;
	if (bIncrementAmount)
		pcUser->sSkillStatusContainer.iAmount++;
}

void LoopUnits(rsPLAYINFO* Player)
{
	for (UINT i = 0, j = AUTOPLAYER_MAX; i < j; i++)
	{
		if (chrAutoPlayer[i].Flag && chrAutoPlayer[i].srTransBuffSize != 0)
		{
			if (chrAutoPlayer[i].Flag && CanSee(&chrAutoPlayer[i], Player))
			{
				int iDistanceA, iDistanceB, iDistanceC;
				rsPLAYPOS pos = { 0, chrAutoPlayer[i].pX, chrAutoPlayer[i].pY, chrAutoPlayer[i].pZ };
				GetPTDistanceXZ(&pos, &Player->Position, iDistanceA, iDistanceB, iDistanceC);

				if ((iDistanceA < 1228800) && (iDistanceB < 0x1000) && (iDistanceC < 0x1000))
				{
					BOOL bForceUnitStatus = FALSE;

					if (Player->Position.Area == rsCASTLE_FIELD)
					{
						switch (chrAutoPlayer[i].smCharInfo.dwCharSoundCode)
						{
						case snCHAR_SOUND_CASTLE_DOOR:
						case snCHAR_SOUND_CASTLE_TOWER_B:
							bForceUnitStatus = TRUE;
							break;
						}
					}

					if ((bForceUnitStatus) || (iDistanceA < 921600))
					{
						if (Player->uaUpdateCounter5[i] != chrAutoPlayer[i].uLastUpdate)
						{
							SendUnitStatusM(Player, (Packet*)(chrAutoPlayer[i].srTransBuff), TRUE);
							chrAutoPlayer[i].NearPlayCount = 256;
							Player->uaUpdateCounter5[i] = chrAutoPlayer[i].uLastUpdate;
						}
					}
					else
					{
						if (chrAutoPlayer[i].MotionInfo->State != CHRMOTION_STATE_DEAD)
						{
							smPLAYDATA sMovePacket;;
							sMovePacket.size = sizeof(sMovePacket);
							sMovePacket.code = smTRANSCODE_PLAYDATA1;
							sMovePacket.dwObjectSerial = chrAutoPlayer[i].dwObjectSerial;
							sMovePacket.x = chrAutoPlayer[i].Posi.x;
							sMovePacket.y = chrAutoPlayer[i].Posi.y;
							sMovePacket.z = chrAutoPlayer[i].Posi.z;
							sMovePacket.angle[0] = chrAutoPlayer[i].Angle.x;
							sMovePacket.angle[1] = chrAutoPlayer[i].Angle.y;
							sMovePacket.angle[2] = chrAutoPlayer[i].Angle.z;
							sMovePacket.angle[3] = chrAutoPlayer[i].MotionInfo->State;
							sMovePacket.frame = chrAutoPlayer[i].frame;
							sMovePacket.dwAutoCharCode = chrAutoPlayer[i].smMonsterInfo.dwAutoCharCode;
							SendUnitStatusM(Player, (Packet*)&sMovePacket, TRUE);
							chrAutoPlayer[i].NearPlayCount = 256;
						}
					}
				}
			}
		}
	}

	if (Player->Position.Area == BabelPlayField && dwBabelPlayTime > dwPlayServTime)
	{
		smTRANS_COMMAND sPacket;
		sPacket.size = sizeof(sPacket);
		sPacket.code = smTRANSCODE_PLAY_COMMAND;
		sPacket.LParam = smCOMMAND_PLAY_BABEL;
		sPacket.WParam = Player->dwObjectSerial;
		sPacket.SParam = BabelPlayField;
		SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);
	}

	if (Player->Position.Area == rsCASTLE_FIELD)
	{
		smTRANS_COMMAND_EX sPacket;
		sPacket.size = sizeof(sPacket);
		sPacket.code = smTRANSCODE_PLAY_COMMAND;
		sPacket.LParam = smCOMMAND_PLAY_BELSS_CASTLE;
		sPacket.WParam = Player->dwObjectSerial;
		sPacket.SParam = (rsBlessCastle.CastleMode << 16) | ((rsBlessCastle.DefenceLevel) & 0xFFFF);
		sPacket.EParam = rsBlessCastle.dwMasterClan;
		sPacket.WxParam = ((int*)rsBlessCastle.TimeSec)[0];
		sPacket.LxParam = ((int*)rsBlessCastle.bCrystalSolderCount)[0];
		sPacket.SxParam = ((int*)Player->sBlessCastle_Damage)[0];
		sPacket.ExParam = 0;
		SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);

		((int*)Player->sBlessCastle_Damage)[0] = 0;
	}

	if (Player->Position.Area == 43 && (BattleArena::GetInstance()->GetFlag() == 1 || BattleArena::GetInstance()->GetFlag() == 2))
	{
		smTRANS_COMMAND_EX sPacket;
		sPacket.size = sizeof(sPacket);
		sPacket.code = smTRANSCODE_PLAY_COMMAND;
		sPacket.LParam = smCOMMAND_PLAY_BA;
		sPacket.WParam = Player->dwObjectSerial;
		sPacket.SParam = BattleArena::GetInstance()->GetTime();
		sPacket.EParam = Player->BattleScore;
		SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);
	}

	ClearUnitStatusM(Player);

	if (Player->Position.Area == 23 && (HellGates::GetInstance()->GetFlag() == 1 || HellGates::GetInstance()->GetFlag() == 2))
	{
		smTRANS_COMMAND_EX sPacket;
		sPacket.size = sizeof(sPacket);
		sPacket.code = smTRANSCODE_PLAY_COMMAND;
		sPacket.LParam = smCOMMAND_PLAY_HG;
		sPacket.WParam = Player->dwObjectSerial;
		sPacket.SParam = HellGates::GetInstance()->GetTime();
		SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);
	}

	if (Player->Position.Area == 47 || Player->Position.Area == 9 || Player->Position.Area == 43 || Player->Position.Area == 50 || Player->Position.Area == 32)
	{
		if (Player->Position.Area == 43 && BattleArena::GetInstance()->GetFlag() == 2 || (Player->Position.Area == 32 && BattleEvent::GetInstance()->GetFlag() == 2))
		{
			smTRANS_COMMAND sPacket;
			sPacket.size = sizeof(sPacket);
			sPacket.code = smTRANSCODE_PLAY_COMMAND;
			sPacket.LParam = smCOMMAND_PLAY_PK_FIELD;
			sPacket.WParam = Player->dwObjectSerial;
			sPacket.SParam = Player->Position.Area;
			SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);
		}
		else if (Player->Position.Area != 43 && Player->Position.Area != 32)
		{
			smTRANS_COMMAND sPacket;
			sPacket.size = sizeof(sPacket);
			sPacket.code = smTRANSCODE_PLAY_COMMAND;
			sPacket.LParam = smCOMMAND_PLAY_PK_FIELD;
			sPacket.WParam = Player->dwObjectSerial;
			sPacket.SParam = Player->Position.Area;
			SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);
		}
	}

	if (Player->Position.Area == rsServerConfig.Enable_PKField)
	{
		smTRANS_COMMAND sPacket;
		sPacket.size = sizeof(sPacket);
		sPacket.code = smTRANSCODE_PLAY_COMMAND;
		sPacket.LParam = smCOMMAND_PLAY_PK_FIELD;
		sPacket.WParam = Player->dwObjectSerial;
		sPacket.SParam = rsServerConfig.Enable_PKField;
		SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);
	}

	if (Player->Position.Area == rsCASTLE_FIELD)
	{
		smTRANS_COMMAND sPacket;
		sPacket.size = sizeof(sPacket);
		sPacket.code = smTRANSCODE_PLAY_COMMAND;
		sPacket.LParam = smCOMMAND_PLAY_PVP_SCORE;
		sPacket.WParam = Player->dwObjectSerial;
		sPacket.SParam = Player->BattlePoint;
		sPacket.EParam = Player->DeathPoint;
		SendUnitStatusM(Player, (Packet*)&sPacket, FALSE);
	}

	ClearUnitStatusM(Player);
}

void LoopUsers(rsPLAYINFO* Player)
{
	if (Player->dwPartyInfo == PARTY_STATE_MASTER && Player->PartyUpdateFlag)
	{
		Player->UpdatePartyPlayInfo();
	}

	BOOL bChat = Player->szChatMessage[0] != 0;

	BOOL bStatus = (Player->dwLastMotionRecvTime + 10000) >= dwPlayServTime;

	if (bChat || bStatus)
	{
		TRANS_CHATMESSAGE	TransChatMessage;

		if (bChat)
		{
			TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
			TransChatMessage.dwIP = 10;
			TransChatMessage.dwObjectSerial = Player->dwObjectSerial;
			lstrcpy(TransChatMessage.szMessage, Player->szChatMessage);
			TransChatMessage.size = 32 + lstrlen(Player->szChatMessage);
			Player->szChatMessage[0] = 0;
		}

		for (int i = 0; i < CONNECTMAX; i++)
		{
			if (rsPlayInfo[i].dwObjectSerial != Player->dwObjectSerial)
			{
				if (bChat)
				{
					if (WithinPTDistance(&rsPlayInfo[i].Position, &Player->Position, 1200))
					{
						if (rsPlayInfo[i].lpsmSock)
						{
							rsPlayInfo[i].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, true);
						}
					}
				}

				if (bStatus)
				{
					if ((rsPlayInfo[i].srRecvPlayBuffCnt > 0) && CanSee(&rsPlayInfo[i]))
					{
						UINT uOtherIndex = i;
						UINT uMyUnitStatusNumOfOther = Player->uaUpdateCounter1[uOtherIndex];
						UINT uUnitStatusNumber = rsPlayInfo[i].srRecvPlayBuffCnt;

						int iDistanceA, iDistanceB, iDistanceC;
						GetPTDistanceXZ(&rsPlayInfo[i].Position, &Player->Position, iDistanceA, iDistanceB, iDistanceC);

						if ((iDistanceA < 1228800) && (iDistanceB < 0x1000) && (iDistanceC < 0x1000))
						{
							DWORD lOtherID = rsPlayInfo[i].dwObjectSerial;
							int iOtherMovingIndex = rsPlayInfo[i].PlayBuffSleep;

							UINT uUnitStatusIndex = 0;

							if (Player->uaUpdateCounter2[uOtherIndex] == lOtherID)
							{
								if ((iOtherMovingIndex == 0) || (uMyUnitStatusNumOfOther < uUnitStatusNumber))
								{
									if ((uMyUnitStatusNumOfOther == 0) || (uMyUnitStatusNumOfOther >= uUnitStatusNumber))
									{
										Player->uaUpdateCounter1[uOtherIndex] = uUnitStatusNumber;
										continue;
									}
									else
									{
										UINT uTemp = uUnitStatusNumber - uMyUnitStatusNumOfOther;

										if (uTemp > 3)
											uMyUnitStatusNumOfOther = uUnitStatusNumber - 3;

										uUnitStatusIndex = uMyUnitStatusNumOfOther % 4;

										uMyUnitStatusNumOfOther++;

										Player->uaUpdateCounter1[uOtherIndex] = uMyUnitStatusNumOfOther;
									}
								}
								else
								{
									if (Player->uaUpdateCounter4[uOtherIndex] == 0)
									{
										if (rsPlayInfo[i].uPriority > 0)
										{
											UINT uCounter3 = (Player->uaUpdateCounter3[uOtherIndex]++);
											BOOL bContinue;
											switch (rsPlayInfo[i].uPriority)
											{
											case 1:
												if (uCounter3 > 2)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											case 2:
												if (uCounter3 > 4)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											case 3:
												if (uCounter3 > 8)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											default:
												if (uCounter3 > 12)
												{
													bContinue = FALSE;
													break;
												}

												bContinue = TRUE;
												break;
											}

											if (bContinue)
												continue;
										}
									}

									uUnitStatusIndex = 4;
								}

								Player->uaUpdateCounter3[uOtherIndex] = 0;
							}
							else
							{
								Player->uaUpdateCounter1[uOtherIndex] = uUnitStatusNumber;
								Player->uaUpdateCounter2[uOtherIndex] = lOtherID;
								Player->uaUpdateCounter3[uOtherIndex] = 0;
								Player->uaUpdateCounter4[uOtherIndex] = 4;

								uUnitStatusIndex = 4;
							}

							if ((iDistanceA < 921600) || (uUnitStatusIndex == 4))
							{
								if (Player->uaUpdateCounter4[uOtherIndex] > 0)
									Player->uaUpdateCounter4[uOtherIndex]--;

								if (rsPlayInfo[i].srPlayBuffSize[uUnitStatusIndex] != 0)
									SendUnitStatus(Player, (Packet*)(rsPlayInfo[i].srPlayBuff[uUnitStatusIndex]), TRUE);

								//SendSkillStatus(Player, &rsPlayInfo[i].sPacketSkillStatus);
							}
							else
							{
								smPLAYDATA sMovePacket;;
								sMovePacket.size = sizeof(sMovePacket);
								sMovePacket.code = smTRANSCODE_PLAYDATA1;
								sMovePacket.dwObjectSerial = rsPlayInfo[i].dwObjectSerial;
								sMovePacket.x = rsPlayInfo[i].Position.x;
								sMovePacket.y = rsPlayInfo[i].Position.y;
								sMovePacket.z = rsPlayInfo[i].Position.z;
								sMovePacket.angle[0] = 0;
								sMovePacket.angle[1] = 0;
								sMovePacket.angle[2] = 0;
								sMovePacket.angle[3] = 0;
								sMovePacket.frame = 0;
								sMovePacket.dwAutoCharCode = 0;
								SendUnitStatus(Player, (Packet*)&sMovePacket, TRUE);
							}
						}
						else
						{
							Player->uaUpdateCounter2[uOtherIndex] = 0;
						}
					}
				}
			}
		}

		ClearUnitStatus(Player);
		ClearSkillStatus(Player);
	}
}

void UserLoop()
{
	for (UINT i = 0; i < CONNECTMAX; i++)
	{
		if (rsPlayInfo[i].lpsmSock && rsPlayInfo[i].szID[0] && rsPlayInfo[i].szName[0] && rsPlayInfo[i].dwObjectSerial)
		{
			if (rsPlayInfo[i].b32)
			{
				DWORD dwTimeDifference = dwPlayServTime - rsPlayInfo[i].dwLastRecvTime;

				if (dwTimeDifference < 2500)
				{
					if (rsPlayInfo[i].b64)
					{
						LoopUnits(&rsPlayInfo[i]);
					}
				}
				LoopUsers(&rsPlayInfo[i]);
			}
		}
	}
}

void UpdateUnit(smCHAR* Monster)
{
	if (!Monster->MotionInfo)
		return;

	if ((Monster->NearPlayCount != 0) ||
		(Monster->MotionInfo->State == CHRMOTION_STATE_DEAD) ||
		(Monster->smMonsterInfo.EventCode))
	{
		srAutoCharMain(Monster);

		Monster->NearPlayCount--;
	}
	else
	{
		if (Monster->smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			Monster->ReopenCount--;

			if (Monster->ReopenCount <= 0)
			{
				if (Monster->smMonsterInfo.Boss < dwPlayServTime)
				{
					Monster->Close();
					((STG_AREA*)Monster->lpExt1)->MonsterCount--;
					((STG_AREA*)Monster->lpExt1)->DeleteMonTable(Monster);
				}
			}
		}
	}
}

void UnitUpdate()
{
	static UINT iUnitWheel = 0;
	static UINT iActiWheel = 0;

	if (iActiWheel == 0)
	{
		if ((iUnitWheel % 64) == 0)
			iActiWheel = 4;
	}
	else
		iActiWheel--;

	dwPlayTime = GetCurrentTime();
	dwPlayServTime = GetCurrentTime();
	srAutoPlayCount = iActiWheel;

	uUnitsInGame = 0;

	for (UINT i = 0; i < AUTOPLAYER_MAX; i++)
	{
		if (chrAutoPlayer[i].Flag)
		{
			uUnitsInGame++;

			if ((i % 4) == (iUnitWheel % 4))
			{
				UpdateUnit(&chrAutoPlayer[i]);

				if (iActiWheel != 0)
					chrAutoPlayer[i].uLastUpdate++;
			}
		}
	}

	iUnitWheel++;
}

void GetItemInfo(char* Code, char* Name)
{
	int i = 0;
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[RewardItem]");
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch()) i++;

			wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[RewardItem]");
			if (SQL::GetInstance()->Execute(szQuery))
			{
				int Rand = rand() % i;
				i = 0;

				while (SQL::GetInstance()->Fetch())
				{
					if (Rand == i)
					{
						SQL::GetInstance()->GetDataValue(1, Code);
						SQL::GetInstance()->GetDataValue(2, Name);
						break;
					}

					i++;
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void UpdateMap()
{
	for (int cnt = 0; cnt < STAGE_AREA_MAX; cnt++)
	{
		if (StageArea[cnt].lpStage)
		{
			StageArea[cnt].Main();
		}
	}

	dwServ_GameTimeHour = GetGameTimeHour();
	if (dwServ_GameTimeHour >= GAME_HOUR_DAY && dwServ_GameTimeHour < GAME_HOUR_DARKNESS)
		dwServ_NightDay = FALSE;
	else
		dwServ_NightDay = TRUE;

	BattleArena::GetInstance()->Main();
	HellGates::GetInstance()->Main();
}

void Loop()
{
	UserUpdate();
	UnitUpdate();
	UpdateMap();
	UserLoop();
}

void Update(float fTime)
{
	static double fTick = (1000.0f / ((double)70));
	static double fOffs = 0.0f;

	pcServerMutex->Lock(3000);

	fOffs += fTime;
	if (fOffs >= fTick)
	{
		do
		{
			Loop();

			fOffs -= fTick;
		} while (fOffs >= fTick);
	}

	pcServerMutex->Unlock();
}

static DWORD FrameSkipTimer = 0;
static DWORD fps = 70;
static DWORD FpsTime;

DWORD dwLastMemoryCount;

int srPlayMain()
{
	int cnt;

	cnt = 0;

	if (FrameSkipTimer == 0) {
		FrameSkipTimer = GetCurrentTime();
		FpsTime = 1000 / fps;
	}

	EnterCriticalSection(&cSerSection);

	while (1) {
		if (FrameSkipTimer > GetCurrentTime()) break;
		if (Quit) break;
		if (cnt > 70 * 2) {
			FrameSkipTimer = GetCurrentTime();
			break;
		}

		FrameSkipTimer += FpsTime;
		if (AutoPlayServer) srAutoPlayMain();
		srAutoTransPlay();
		if (LoginServer) srBillingMain();

		DWORD dwTime = GetCurrentTime();

		if (dwLastMemoryCount < dwTime)
		{
			SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);
			dwLastMemoryCount = dwTime + 120000;
		}

		cnt++;
	}

	LeaveCriticalSection(&cSerSection);

	return cnt;
}

int InitAll()
{
	int cnt;

	DWORD nsize = 32;
	char szServerName[32];

	ChatBuffCnt = 0;

	GetComputerName(szServerName, &nsize);
	if (lstrcmpi(szServerName, szDebugServer) == 0)
		DebugServerMode = TRUE;

	ServerNameCode = GetSpeedSum(szServerName);

	rsNoticeMessage.Counter = 0;
	rsNoticeMessage.szMessage[0] = 0;

	Server_AllocMemory();

	if (rsServerConfig.UseRecorMemory) {
		rsRecordDataBuff = new char[(srRECORD_MEMORY_SIZE + 256) * CONNECTMAX];
		if (!rsRecordDataBuff)
			MessageBox(NULL, "Error Record Memory", "Alloc Failed - Hotuk Server", MB_OK);
	}
	else {
		rsRecordDataBuff = 0;
	}

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		ZeroMemory(&rsPlayInfo[cnt], sizeof(rsPLAYINFO));
		if (rsRecordDataBuff) {
			rsPlayInfo[cnt].lpRecordDataBuff = rsRecordDataBuff + ((srRECORD_MEMORY_SIZE + 256) * cnt);
		}
	}

	InitMaterial();

	srInitChar();

	InitMonster();

	InitItems();

	LoadOftenNpc();

	InitCrackFinding();

	Stage_StepHeight = fONE * 20;

	StageArea = new STG_AREA[STAGE_AREA_MAX];
	srReadStage();

	ConvertMonsterNames();

	AutoPlayServer = rsServerConfig.AutoPlayer;

	SetTimer(hwnd, 0, 100, NULL);
	dwPlayServTime = GetCurrentTime();

	InitLogSql();

	rsResetClientFuncPos();

	rsLoadCopiedItemList();

	RecordShutdownLog(50020, 0, 0);

	rsInit_SerToServer();

	ZeroMemory(&rsUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	OpenBossTimeMin = (rand() % 45) + 1;

	rsInit_Castle();

	ZeroMemory(&CurrencyLog, sizeof(rsCURRENCY_LOG));

	return TRUE;
}

void RemoveAll()
{
	int cnt;
	smTRANS_COMMAND smTransCommand;

	RecordShutdownLog(50030, 0, 0);

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpRecordDataBuff) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szName[0]) {
				if (rsRecordMemoryBuffToFile(&rsPlayInfo[cnt], rsPlayInfo[cnt].szName, rsPlayInfo[cnt].lpRecordDataBuff) == TRUE) {
					if (lstrcmpi(rsPlayInfo[cnt].szName, ((TRANS_RECORD_DATA*)rsPlayInfo[cnt].lpRecordDataBuff)->smCharInfo.szName) != 0) {
						smTransCommand.WParam = 10002;
						smTransCommand.LParam = (DWORD)rsPlayInfo[cnt].szName;
						smTransCommand.SParam = (DWORD)((TRANS_RECORD_DATA*)rsPlayInfo[cnt].lpRecordDataBuff)->smCharInfo.szName;
						RecordHackLogFile(&rsPlayInfo[cnt], &smTransCommand);
					}

					rsSaveThrowData(&rsPlayInfo[cnt]);

					rsRecordMemoryBuff_CheckInvenItem(&rsPlayInfo[cnt], 1);
				}
			}
		}
	}
	if (rsRecordDataBuff)
		delete rsRecordDataBuff;

	rsCloseDataBase();
	CloseLogSql();

	EnterCriticalSection(&cSerSection);

	srRemoveChar();
	srRemoveStage();
	CloseMaterial();

	for (cnt = STAGE_AREA_MAX - 1; cnt >= 0; cnt--)
		StageArea[cnt].Close();

	delete StageArea;

	rsRemoveCopiedItemList();

	Server_RemoveMemory();

	LeaveCriticalSection(&cSerSection);
}

DWORD dwConnIPCheckTime = 0;

int AddNewPlayInfo(smWINSOCK* lpsmSock)
{
	int cnt, cnt2;
	DWORD	dwMyIP;
	int	SameIPCount = 0;
	smTRANS_COMMAND	TransCommand;

	dwMyIP = lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	for (cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].lpsmSock->acc_sin.sin_addr.S_un.S_addr == dwMyIP)
		{
			SameIPCount++;
		}
		else
		{
			if (rsPlayInfo[cnt].lpsmSock == 0) break;
		}
	}

	if (cnt == CONNECTMAX) return FALSE;

	if (SameIPCount > 32)
	{
		if (rsCheckSystemIP(dwMyIP) == FALSE)
		{
			//DisconnectUser(lpsmSock);

			if (abs((long)dwConnIPCheckTime - (long)dwPlayServTime) > 60 * 1000 * 3)
			{
				smTRANS_COMMAND smTransCommand;
				smTransCommand.WParam = 5000;
				smTransCommand.SParam = SameIPCount;
				smTransCommand.LParam = dwMyIP;
				RecordHackLogFile(0, &smTransCommand);
			}

			return FALSE;
		}
	}

	if (ShutDownFlag)
	{
		if (strstr(lpsmSock->szIPAddr, szAdminIP) == 0)
		{
			DisconnectUser(lpsmSock);
			return FALSE;
		}
	}

	lpsmSock->ExtData1 = (void*)&rsPlayInfo[cnt];

	rsPlayInfo[cnt].lpsmSock = lpsmSock;
	rsPlayInfo[cnt].ChatBuffCnt = ChatBuffCnt;
	rsPlayInfo[cnt].SendListCnt = 0;
	rsPlayInfo[cnt].Position.Area = 0xFFFFFFFF;
	rsPlayInfo[cnt].TransInfoFlag = FALSE;
	rsPlayInfo[cnt].SystemLine = 0;
	rsPlayInfo[cnt].CharLevelMax = 0;
	rsPlayInfo[cnt].AdminOperMode = 0;
	rsPlayInfo[cnt].dwDataError = 0;

	for (cnt2 = 0; cnt2 < srPLAYBUFF_MAX + 1; cnt2++)
		rsPlayInfo[cnt].srPlayBuffSize[cnt2] = 0;
	rsPlayInfo[cnt].srSendPlayBuffCnt = 0;
	rsPlayInfo[cnt].srRecvPlayBuffCnt = 0;
	rsPlayInfo[cnt].dwObjectSerial = 0;
	rsPlayInfo[cnt].szChatMessage[0] = 0;
	rsPlayInfo[cnt].lpRecordBase = 0;
	rsPlayInfo[cnt].lpPostBoxItem = 0;
	rsPlayInfo[cnt].PostPassFailCount = 0;

	rsPlayInfo[cnt].AdminMode = 0;
	rsPlayInfo[cnt].HideMode = 0;
	rsPlayInfo[cnt].CharLoadingCount = 0;
	rsPlayInfo[cnt].dwNoticeCount = rsNoticeMessage.Counter;

	rsPlayInfo[cnt].LastTransPlayUserCount = 0;
	rsPlayInfo[cnt].LastTransAutoPlayCount = 0;

	rsPlayInfo[cnt].UnsaveMoney = -1;
	rsPlayInfo[cnt].ThrowItemCount = 0;
	rsPlayInfo[cnt].szName[0] = 0;
	rsPlayInfo[cnt].szID[0] = 0;
	rsPlayInfo[cnt].szServerID[0] = 0;

	rsPlayInfo[cnt].dwLastRecvTime = dwPlayServTime;
	rsPlayInfo[cnt].dwLastMotionRecvTime = dwPlayServTime;

	rsPlayInfo[cnt].dwConnectCount = dwConnectCount;

	rsPlayInfo[cnt].SendPlayGroupCount = 0;

	rsPlayInfo[cnt].MonTranCount = 0;
	rsPlayInfo[cnt].CharTransCount = 0;
	rsPlayInfo[cnt].HitMonsterCount = 0;
	rsPlayInfo[cnt].UserPacketLoop = 0;
	rsPlayInfo[cnt].BefUserPacketLoop = 0;

	rsPlayInfo[cnt].lpChrTarget = 0;
	rsPlayInfo[cnt].dwTarObjSerial = 0;
	rsPlayInfo[cnt].smCharInfo.szName[0] = 0;
	rsPlayInfo[cnt].smCharInfo.Level = 0;
	rsPlayInfo[cnt].CrackWarning = 0;
	rsPlayInfo[cnt].dwTime_Disconnect = 0;
	rsPlayInfo[cnt].EventMode = 0;
	rsPlayInfo[cnt].AreaOutCount = 0;

	rsPlayInfo[cnt].dwPartyInfo = 0;
	rsPlayInfo[cnt].lpPartyMaster = 0;

	rsPlayInfo[cnt].DamagePacketCount = 0;
	rsPlayInfo[cnt].dwDamagePacketTime = 0;
	rsPlayInfo[cnt].AttackCount = 0;
	rsPlayInfo[cnt].dwAttackTime = dwPlayServTime;
	rsPlayInfo[cnt].dwConnectTime = dwPlayServTime;
	rsPlayInfo[cnt].dwRecvTimePlayBuff = 0;
	rsPlayInfo[cnt].BadPlayer = 0;
	rsPlayInfo[cnt].dwPacketAttackCount = 0;
	rsPlayInfo[cnt].dwPacketAttackTime = dwPlayServTime;

	rsPlayInfo[cnt].BlockTime = 0;
	rsPlayInfo[cnt].MonsterKillCounter = 0;
	rsPlayInfo[cnt].WhisperMode = 0;
	rsPlayInfo[cnt].Event_StarTicketLevel = 0;

	rsPlayInfo[cnt].dwClanCode = 0;
	rsPlayInfo[cnt].SucessCheck_ClanCode = 0;

	rsPlayInfo[cnt].spExp_Start = 0;
	rsPlayInfo[cnt].spMoney_Start = 0;
	rsPlayInfo[cnt].spLevel_Start = 0;

	rsPlayInfo[cnt].spExp_InOut_Total = 0;
	rsPlayInfo[cnt].spMoney_In_Total = 0;
	rsPlayInfo[cnt].spMoney_InOut_Total = 0;

	rsPlayInfo[cnt].spEXP_Out = 0;
	rsPlayInfo[cnt].spMoney_In = 0;
	rsPlayInfo[cnt].spMoney_Out = 0;
	rsPlayInfo[cnt].dwLastExpMoneyCheckTime = dwPlayServTime;
	rsPlayInfo[cnt].dwLastExpMoneyTransServer = dwPlayServTime;

	rsPlayInfo[cnt].ServerMoney = 0;
	rsPlayInfo[cnt].WareHouseMoney = 0;
	rsPlayInfo[cnt].dwNSpriteTime = 0;

	for (cnt2 = 0; cnt2 < 8; cnt2++) {
		rsPlayInfo[cnt].dwGameServerExp[cnt2] = 0;
		ZeroMemory(rsPlayInfo[cnt].RcvItemSecCodeBuff[cnt2], sizeof(int) * 16);
	}
	rsPlayInfo[cnt].SndItemSecCodeCount = 1;

	rsPlayInfo[cnt].smCharInfo.Level = 0;
	rsPlayInfo[cnt].smCharInfo.Exp = 0;
	rsPlayInfo[cnt].smCharInfo.Exp_High = 0;
	rsPlayInfo[cnt].smCharInfo.Money = 0;
	rsPlayInfo[cnt].smCharInfo.JOB_CODE = 0;

	rsPlayInfo[cnt].RecordWarningCount = 0;
	rsPlayInfo[cnt].RecordWarningExp = 0;
	rsPlayInfo[cnt].WarningCount = 0;

	rsPlayInfo[cnt].dwLastTradeChksum = 0;

	rsPlayInfo[cnt].Send_AttackCount = 0;
	rsPlayInfo[cnt].Send_AttackDamage = 0;
	rsPlayInfo[cnt].Recv_AttackCount = 0;
	rsPlayInfo[cnt].Recv_AttackDamage = 0;

	rsPlayInfo[cnt].dwHopeDisconnectTime = 0;

	rsPlayInfo[cnt].Client_Version = 0;

	rsPlayInfo[cnt].UpdateInfo_WarnigCounter = 0;

	rsPlayInfo[cnt].dwMacroTime = 0;
	rsPlayInfo[cnt].dwMacroAngTime = 0;
	rsPlayInfo[cnt].dwMacroChkTime = 0;

	rsPlayInfo[cnt].dwClientFuncChk_1 = 0;
	rsPlayInfo[cnt].dwClientFuncChk_2 = 0;
	rsPlayInfo[cnt].FuncChkFailCount1 = 0;
	rsPlayInfo[cnt].FuncChkFailCount2 = 0;
	rsPlayInfo[cnt].dwFuncChkErrorFlag = 0;
	rsPlayInfo[cnt].ClientFunChk1_Count = 0;
	rsPlayInfo[cnt].ClientFunChk2_Count = 0;
	rsPlayInfo[cnt].FuncChkSucessCount1 = 0;
	rsPlayInfo[cnt].FuncChkSucessCount2 = 0;
	rsPlayInfo[cnt].dwClientFunChk_NextTime = dwPlayServTime + 60 * 1000 * 5;

	rsPlayInfo[cnt].dwLastSaveTime = 0;

	rsPlayInfo[cnt].dwClentOS = 0;
	rsPlayInfo[cnt].dwClentModulChkSum = 0;
	rsPlayInfo[cnt].ClentModuleCount = 0;

	rsPlayInfo[cnt].szGuid[0] = 0;
	rsPlayInfo[cnt].szGPCode[0] = 0;
	rsPlayInfo[cnt].GpCode = -1;
	rsPlayInfo[cnt].GpType = -1;
	rsPlayInfo[cnt].DisuseDay = 0;
	rsPlayInfo[cnt].dwPeriodTime = 0;
	rsPlayInfo[cnt].Bl_RNo = 0;
	rsPlayInfo[cnt].Bl_Meter = 0;
	rsPlayInfo[cnt].dwPeriodTime2 = 0;

	rsPlayInfo[cnt].dwSkill_AutoMation_Time = 0;
	rsPlayInfo[cnt].dwSkill_AutoMation_Param = 0;
	rsPlayInfo[cnt].dwSkill_Maximize_Time = 0;
	rsPlayInfo[cnt].dwSkill_Maximize_Param = 0;
	rsPlayInfo[cnt].dwSkill_PhysicalAbsorb_Time = 0;
	rsPlayInfo[cnt].dwSkill_PhysicalAbsorb_Param = 0;
	rsPlayInfo[cnt].dwSkill_ExtreamShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_ExtreamShield_Param = 0;

	rsPlayInfo[cnt].dwSkill_HolyBody_Time = 0;
	rsPlayInfo[cnt].dwSkill_HolyBody_Param = 0;
	rsPlayInfo[cnt].dwSkill_HolyValor_Time = 0;
	rsPlayInfo[cnt].dwSkill_HolyValor_Param = 0;
	rsPlayInfo[cnt].dwSkill_HolyReflection_Time = 0;
	rsPlayInfo[cnt].dwSkill_HolyReflection_Param = 0;
	rsPlayInfo[cnt].dwSkill_EnchantWeapon_Time = 0;
	rsPlayInfo[cnt].dwSkill_EnchantWeapon_Param = 0;

	rsPlayInfo[cnt].dwSkill_SparkShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_MetalArmor_Param = 0;
	rsPlayInfo[cnt].dwSkill_SparkShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_SparkShield_Param = 0;

	rsPlayInfo[cnt].dwSKill_Falcon_Time = 0;
	rsPlayInfo[cnt].dwSKill_Falcon_Damage[0] = 0;
	rsPlayInfo[cnt].dwSKill_Falcon_Damage[1] = 0;

	rsPlayInfo[cnt].dwSkill_DivineInhalation_Time = 0;
	rsPlayInfo[cnt].dwSkill_DivineInhalation_Param = 0;

	rsPlayInfo[cnt].dwSkill_TriumphOfValhalla_Time = 0;
	rsPlayInfo[cnt].dwSkill_TriumphOfValhalla_Param = 0;

	rsPlayInfo[cnt].dwSkill_VirtualLife_Time = 0;
	rsPlayInfo[cnt].dwSkill_VirtualLife_Param = 0;

	rsPlayInfo[cnt].dwSkill_EnergyShield_Time = 0;
	rsPlayInfo[cnt].dwSkill_EnergyShield_Param = 0;

	rsPlayInfo[cnt].dwSkill_SpiritElemental_Time = 0;
	rsPlayInfo[cnt].dwSkill_SpiritElemental_Param = 0;

	rsPlayInfo[cnt].dwSkill_DancingSword_Time = 0;
	rsPlayInfo[cnt].dwSkill_DancingSword_Param = 0;
	rsPlayInfo[cnt].dwSkill_DancingSword_DelayTime = 0;

	rsPlayInfo[cnt].dwSkill_Vanish_Time = 0;
	rsPlayInfo[cnt].dwSkill_Vanish_Param = 0;

	rsPlayInfo[cnt].dwSkill_Compulsion_Time = 0;
	rsPlayInfo[cnt].dwSkill_Compulsion_Param = 0;

	rsPlayInfo[cnt].dwSkill_MagneticSphere_Time = 0;
	rsPlayInfo[cnt].dwSkill_MagneticSphere_Param = 0;

	rsPlayInfo[cnt].dwSkill_Berserker_Time = 0;
	rsPlayInfo[cnt].dwSkill_Berserker_Param = 0;

	rsPlayInfo[cnt].dwSkill_B_Berserker_Time = 0;
	rsPlayInfo[cnt].dwSkill_B_Berserker_Param = 0;

	rsPlayInfo[cnt].dwSkill_AssassinEye_Time = 0;
	rsPlayInfo[cnt].dwSkill_AssassinEye_Param = 0;

	rsPlayInfo[cnt].dwSkill_Tenus_Time = 0;
	rsPlayInfo[cnt].dwSkill_Tenus_Param = 0;

	rsPlayInfo[cnt].dwSkill_P_Enhence_Time = 0;
	rsPlayInfo[cnt].dwSkill_P_Enhence_Param = 0;

	rsPlayInfo[cnt].dwSkill_Vague_Time = 0;
	rsPlayInfo[cnt].dwSkill_Vague_Param = 0;

	rsPlayInfo[cnt].dwSkill_ForceOfNature_Time = 0;

	rsPlayInfo[cnt].dwSkill_GodlyShied_Time = 0;
	rsPlayInfo[cnt].dwSkill_GodlyShied_Param = 0;

	rsPlayInfo[cnt].dwSkill_GodsBless_Time = 0;
	rsPlayInfo[cnt].dwSkill_GodsBless_Param = 0;

	rsPlayInfo[cnt].dwSkill_HallOfValhalla_Time = 0;

	rsPlayInfo[cnt].dwSkill_FrostJavelin_Time = 0;
	rsPlayInfo[cnt].dwSkill_FrostJavelin_Param = 0;

	rsPlayInfo[cnt].dwSkill_RegenerationField_Time = 0;

	rsPlayInfo[cnt].dwSkill_SummonMuspell_Time = 0;
	rsPlayInfo[cnt].dwSkill_SummonMuspell_Param = 0;

	rsPlayInfo[cnt].dwSkill_ChasingHunt_Time = 0;
	rsPlayInfo[cnt].dwSkill_ChasingHunt_Param = 0;

	rsPlayInfo[cnt].dwSkill_RainMaker_Time = 0;
	rsPlayInfo[cnt].dwSkill_RainMaker_Param = 0;

	rsPlayInfo[cnt].dwSkill_Blind_Time = 0;
	rsPlayInfo[cnt].dwSkill_Blind_Param = 0;

	rsPlayInfo[cnt].dwSkill_Alas_Time = 0;
	rsPlayInfo[cnt].dwSkill_Alas_Param = 0;

	rsPlayInfo[cnt].dwSkill_HolyBenedic_Time = 0;
	rsPlayInfo[cnt].dwSkill_HolyBenedic_Param = 0;

	rsPlayInfo[cnt].dwSkill_Amplified_Time = 0;
	rsPlayInfo[cnt].dwSkill_Amplified_Param = 0;

	rsPlayInfo[cnt].dwSkill_Anima_Time = 0;
	rsPlayInfo[cnt].dwSkill_Anima_Param = 0;

	rsPlayInfo[cnt].dwSkill_PowerEnhence_Time = 0;
	rsPlayInfo[cnt].dwSkill_PowerEnhence_Param = 0;

	rsPlayInfo[cnt].dwSkill_I_Bulkup_Time = 0;
	rsPlayInfo[cnt].dwSkill_I_Bulkup_Param = 0;

	rsPlayInfo[cnt].dwCurse_Attack_Time = 0;
	rsPlayInfo[cnt].dwCurse_Defence_Time = 0;

	rsPlayInfo[cnt].dwForceOrb_Code = 0;
	rsPlayInfo[cnt].dwForceOrb_Time = 0;
	rsPlayInfo[cnt].dwForceOrb_Damage = 0;

	rsPlayInfo[cnt].dwForceOrb_SaveCode = 0;
	rsPlayInfo[cnt].dwForceOrb_SaveTime = 0;
	rsPlayInfo[cnt].dwForceOrb_SaveDamage = 0;
	rsPlayInfo[cnt].dwForceOrb_NextSetTime = 0;

	rsPlayInfo[cnt].dwLifeBooster_Code = 0;
	rsPlayInfo[cnt].dwLifeBooster_Time = 0;
	rsPlayInfo[cnt].dwLifeBooster_Data = 0;

	rsPlayInfo[cnt].dwLifeBooster_SaveCode = 0;
	rsPlayInfo[cnt].dwLifeBooster_SaveTime = 0;
	rsPlayInfo[cnt].dwLifeBooster_SaveData = 0;
	rsPlayInfo[cnt].dwLifeBooster_NextSetTime = 0;

	rsPlayInfo[cnt].dwManaBooster_Code = 0;
	rsPlayInfo[cnt].dwManaBooster_Time = 0;
	rsPlayInfo[cnt].dwManaBooster_Data = 0;

	rsPlayInfo[cnt].dwManaBooster_SaveCode = 0;
	rsPlayInfo[cnt].dwManaBooster_SaveTime = 0;
	rsPlayInfo[cnt].dwManaBooster_SaveData = 0;
	rsPlayInfo[cnt].dwManaBooster_NextSetTime = 0;

	rsPlayInfo[cnt].dwStaminaBooster_Code = 0;
	rsPlayInfo[cnt].dwStaminaBooster_Time = 0;
	rsPlayInfo[cnt].dwStaminaBooster_Data = 0;

	rsPlayInfo[cnt].dwStaminaBooster_SaveCode = 0;
	rsPlayInfo[cnt].dwStaminaBooster_SaveTime = 0;
	rsPlayInfo[cnt].dwStaminaBooster_SaveData = 0;
	rsPlayInfo[cnt].dwStaminaBooster_NextSetTime = 0;

	rsPlayInfo[cnt].dwSkillDelay_Code = 0;
	rsPlayInfo[cnt].dwSkillDelay_Time = 0;
	rsPlayInfo[cnt].dwSkillDelay_Data = 0;

	rsPlayInfo[cnt].dwSkillDelay_SaveCode = 0;
	rsPlayInfo[cnt].dwSkillDelay_SaveTime = 0;
	rsPlayInfo[cnt].dwSkillDelay_SaveData = 0;
	rsPlayInfo[cnt].dwSkillDelay_NextSetTime = 0;
	rsPlayInfo[cnt].ChatGlobal_Time = 0;

	rsPlayInfo[cnt].dwPrimeItem_NextSetTime = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_X2 = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_ExpUp = 0;

	rsPlayInfo[cnt].dwTime_PrimeItem_VampCuspid = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_VampCuspid_EX = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_ManaRecharg = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_ManaReduce = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_MightofAwell = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_MightofAwell2 = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_PhenixPet = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_HelpPet = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_StaminaReduce = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_BigHead = 0;
	rsPlayInfo[cnt].dwParam_PrimeItem_BigHead = 0;
	rsPlayInfo[cnt].dwTime_PrimeItem_VIP = 0;
	rsPlayInfo[cnt].dwParam_PrimeItem_VIP = 0;

	rsPlayInfo[cnt].dwPrimeItem_PackageCode = 0;

	rsPlayInfo[cnt].dwPCBang_Pet_AttackTime = 0;
	rsPlayInfo[cnt].dwPCBang_Pet_NextSetTime = 0;

	rsPlayInfo[cnt].lpLinkChar = 0;

	((DWORD*)rsPlayInfo[cnt].sBlessCastle_Damage)[0] = 0;

	rsPlayInfo[cnt].BattlePoint = 0;
	rsPlayInfo[cnt].DeathPoint = 0;
	rsPlayInfo[cnt].LastKill[0] = 0;

	rsPlayInfo[cnt].QuestStart_State = 0;
	rsPlayInfo[cnt].QuestStart_Param1 = 0;
	rsPlayInfo[cnt].QuestStart_Param2 = 0;

	rsPlayInfo[cnt].QuestLv150A_State = 0;
	rsPlayInfo[cnt].QuestLv150A_Param = 0;
	rsPlayInfo[cnt].QuestLv150A_Time = 0;

	rsPlayInfo[cnt].QuestLv155A_State = 0;
	rsPlayInfo[cnt].QuestLv155A_Param = 0;
	rsPlayInfo[cnt].QuestLv155A_Time = 0;

	rsPlayInfo[cnt].QuestLv150B_State = 0;
	rsPlayInfo[cnt].QuestLv150B_Param = 0;
	rsPlayInfo[cnt].QuestLv150B_Time = 0;
	rsPlayInfo[cnt].PvP_Time = 0;
	rsPlayInfo[cnt].PvP_Param = 0;
	rsPlayInfo[cnt].Checksum = 0;
	rsPlayInfo[cnt].WarehousePage = 0;

	rsPlayInfo[cnt].Streak = 0;
	rsPlayInfo[cnt].BattleLevel = 0;
	rsPlayInfo[cnt].BattleExp = 0;

	rsPlayInfo[cnt].WeaponClass = 0;
	rsPlayInfo[cnt].ArmorClass = 0;
	rsPlayInfo[cnt].ShieldClass = 0;
	rsPlayInfo[cnt].BraceletsClass = 0;
	rsPlayInfo[cnt].GauntletsClass = 0;
	rsPlayInfo[cnt].BootsClass = 0;
	rsPlayInfo[cnt].RingClass = 0;
	rsPlayInfo[cnt].AmyClass = 0;
	rsPlayInfo[cnt].ShelClass = 0;
	rsPlayInfo[cnt].TimeClass = 0;
	rsPlayInfo[cnt].OnBattle = 0;
	rsPlayInfo[cnt].OnHellGates = 0;
	rsPlayInfo[cnt].BattleScore = 0;

	rsPlayInfo[cnt].RandomMonster_Param = 0;
	rsPlayInfo[cnt].RandomMonster_Time = 0;

	rsPlayInfo[cnt].dwCheck_MasterClanTime = 0;

	rsPlayInfo[cnt].CastleMaster.Flag = 0;
	rsPlayInfo[cnt].dwBlessSkill_Code = 0;
	rsPlayInfo[cnt].dwBlessSkill_Time = 0;

	rsPlayInfo[cnt].dwSiegeItem_Scroll_Time = 0;
	rsPlayInfo[cnt].dwSiegeItem_Scroll_Code = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone1_Time = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone1_Code = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone2_Time = 0;
	rsPlayInfo[cnt].dwSiegeItem_Stone2_Code = 0;

	((DWORD*)rsPlayInfo[cnt].sLimitDamage)[0] = 0;
	((DWORD*)rsPlayInfo[cnt].sLimitCritical)[0] = 0;

	((DWORD*)rsPlayInfo[cnt].sLowLevel_PresentItem)[0] = 0;
	rsPlayInfo[cnt].dwStartUser_PresentItem_Time = 0;
	rsPlayInfo[cnt].dwStartUser_PresentItem_Count = 0;

	((DWORD*)rsPlayInfo[cnt].sCheckPlayField_Count)[0] = 0;

	rsPlayInfo[cnt].ClanTicketCode = 0;

	rsPlayInfo[cnt].dwDecPacketCode = 0;
	rsPlayInfo[cnt].dwDecPacketTime = 0;

	ZeroMemory(rsPlayInfo[cnt].dwSendFrames, CONNECTMAX * sizeof(DWORD));
	ZeroMemory(rsPlayInfo[cnt].InvenItemInfo, INVEN_ITEM_INFO_MAX * sizeof(sTHROW_ITEM_INFO));
	rsPlayInfo[cnt].OpenWarehouseInfoFlag = 0;
	rsPlayInfo[cnt].TradePotionInfoCount = 0;
	rsPlayInfo[cnt].MyShopListCount = 0;
	rsPlayInfo[cnt].dwMyShopTradeTime = 0;

	rsPlayInfo[cnt].dwTradeMsgCode = 0;
	rsPlayInfo[cnt].dwHaQuestItemCount = 0;

	rsPlayInfo[cnt].szUserExpTimeID[0] = 0;
	rsPlayInfo[cnt].szUserExpTimeName[0] = 0;
	rsPlayInfo[cnt].dwExpGameTime = 0;
	rsPlayInfo[cnt].dwExpGameTimeCheck = 0;
	rsPlayInfo[cnt].dwCountMin = 0;

	rsPlayInfo[cnt].b32 = 0;
	rsPlayInfo[cnt].b64 = 0;
	rsPlayInfo[cnt].uPriorityCounter = 0;
	rsPlayInfo[cnt].uPriority = 0;
	rsPlayInfo[cnt].bAFK = 0;
	rsPlayInfo[cnt].iUnitStatusCounter = 0;
	rsPlayInfo[cnt].uBufferPosition = 0;
	ZeroMemory(&rsPlayInfo[cnt].sUnitStatusContainer, sizeof(PacketUnitStatusContainer));
	rsPlayInfo[cnt].uBufferPositionM = 0;
	ZeroMemory(&rsPlayInfo[cnt].sUnitStatusContainerM, sizeof(PacketUnitStatusContainer));
	rsPlayInfo[cnt].uBufferPositionS = 0;
	ZeroMemory(&rsPlayInfo[cnt].sSkillStatusContainer, sizeof(PacketSkillStatusContainer));
	rsPlayInfo[cnt].uNewUnitStatus = 0;
	rsPlayInfo[cnt].uLastUnitStatus = 0;
	ZeroMemory(&rsPlayInfo[cnt].uaUpdateCounter1, 1024 * sizeof(UINT));
	ZeroMemory(&rsPlayInfo[cnt].uaUpdateCounter2, 1024 * sizeof(UINT));
	ZeroMemory(&rsPlayInfo[cnt].uaUpdateCounter3, 1024 * sizeof(USHORT));
	ZeroMemory(&rsPlayInfo[cnt].uaUpdateCounter4, 1024 * sizeof(USHORT));
	ZeroMemory(&rsPlayInfo[cnt].uaUpdateCounter5, 4096 * sizeof(UCHAR));

	if (rsPlayInfo[cnt].lpRecordDataBuff) {
		((TRANS_RECORD_DATA*)rsPlayInfo[cnt].lpRecordDataBuff)->size = 0;
		rsPlayInfo[cnt].dwRecordDataTime = dwPlayServTime;

		if (rsPlayInfo[cnt].lpRecordDataBuff != (rsRecordDataBuff + ((srRECORD_MEMORY_SIZE + 256) * cnt))) {
			TransCommand.WParam = 10007;
			TransCommand.LParam = (int)rsRecordDataBuff + ((srRECORD_MEMORY_SIZE + 256) * cnt);
			TransCommand.SParam = (int)rsPlayInfo[cnt].lpRecordDataBuff;
			RecordHackLogFile(&rsPlayInfo[cnt], &TransCommand);
		}
	}
	else
		rsPlayInfo[cnt].dwRecordDataTime = 0;

	dwConnectCount++;

	if (strstr(lpsmSock->szIPAddr, szAdminIP) != 0) rsPlayInfo[cnt].AdminIP = TRUE;
	else if (strstr(lpsmSock->szIPAddr, szAdminIP2) != 0) rsPlayInfo[cnt].AdminIP = TRUE;
	else {
		if (rsCheckAdminIP(rsPlayInfo[cnt].lpsmSock->acc_sin.sin_addr.S_un.S_addr) == TRUE)
			rsPlayInfo[cnt].AdminIP = TRUE;
		else
			rsPlayInfo[cnt].AdminIP = FALSE;
	}

	TransCommand.code = smTRANSCODE_VERSION;
	TransCommand.size = sizeof(smTRANS_COMMAND);
	TransCommand.WParam = Server_LimitVersion;
	TransCommand.LParam = 0;

	if (rsGetUserCounter(PlayerCount) >= rsConnectUserLimit) {
		if (!rsPlayInfo[cnt].AdminIP) {
			TransCommand.LParam = PlayerCount;
		}
	}

	lpsmSock->Send2((char*)&TransCommand, TransCommand.size, TRUE);

	return TRUE;
}

int IsStgArea(STG_AREA* lpStgArea)
{
	int cnt;

	for (cnt = 0; cnt < STAGE_AREA_MAX; cnt++) {
		if (lpStgArea == &StageArea[cnt])
			return TRUE;
	}
	return FALSE;
}

int	rsSendServerNoticeToUser(rsPLAYINFO* lpPlayInfo)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, srMsg_011, rsNoticeMessage.szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 3;
	TransChatMessage.dwObjectSerial = 0;

	if (lpPlayInfo->lpsmSock)
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	lpPlayInfo->dwNoticeCount = rsNoticeMessage.Counter;

	return TRUE;
}

int	rsSetNoticeMessage(char* szMessage)
{
	lstrcpy(rsNoticeMessage.szMessage, szMessage);
	rsNoticeMessage.Counter++;

	return rsNoticeMessage.Counter;
}

int	SendSaveClientData(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = smTRANSCODE_SAVECLIENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}

int	rsSendCloseClient(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = smTRANSCODE_CLOSECLIENT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}

int	rsRecordFixExp(rsPLAYINFO* lpPlayInfo)
{
	return TRUE;
}

int SaveThrowItemOver(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;
	int LowCount;
	DWORD	LowCode;
	DWORD	Code;

	if (lpPlayInfo->ThrowItemCount <= 0) return FALSE;

	LowCount = 0;
	LowCode = lpPlayInfo->ThrowItemInfo[LowCount].dwCode & sinITEM_MASK3;

	for (cnt = 1; cnt < lpPlayInfo->ThrowItemCount; cnt++) {
		Code = lpPlayInfo->ThrowItemInfo[cnt].dwCode & sinITEM_MASK3;
		if (Code < LowCode) {
			LowCode = Code;
			LowCount = cnt;
		}
	}

	lpPlayInfo->ThrowItemInfo[LowCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[LowCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[LowCount].dwSum = dwSum;

	return TRUE;
}

int SaveThrowItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) return TRUE;

	for (cnt = 0; cnt < lpPlayInfo->ThrowItemCount; cnt++) {
		if (lpPlayInfo->ThrowItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->ThrowItemInfo[cnt].dwKey == dwKey &&
			lpPlayInfo->ThrowItemInfo[cnt].dwSum == dwSum) {
			return TRUE;
		}
	}

	if (lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1) {
		return SaveThrowItemOver(lpPlayInfo, dwCode, dwKey, dwSum);
	}

	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = dwSum;

	if (lpPlayInfo->ThrowItemCount < THROW_ITEM_INFO_MAX - 1) {
		lpPlayInfo->ThrowItemCount++;

		if (lpPlayInfo->ThrowItemCount == THROW_ITEM_INFO_MAX - 32 ||
			lpPlayInfo->ThrowItemCount > THROW_ITEM_INFO_MAX - 48) {
			SendSaveClientData(lpPlayInfo);
		}
	}

	return TRUE;
}

int SaveThrowItem2(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum)
{
	int cnt;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) return TRUE;

	for (cnt = 0; cnt < lpPlayInfo->ThrowItemCount; cnt++) {
		if (lpPlayInfo->ThrowItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->ThrowItemInfo[cnt].dwKey == dwKey &&
			lpPlayInfo->ThrowItemInfo[cnt].dwSum == dwSum) {
			return TRUE;
		}
	}

	if (lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1) {
		return SaveThrowItemOver(lpPlayInfo, dwCode, dwKey, dwSum);
	}

	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = dwCode;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = dwKey;
	lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = dwSum;

	if (lpPlayInfo->ThrowItemCount < THROW_ITEM_INFO_MAX - 1) {
		lpPlayInfo->ThrowItemCount++;
	}

	return TRUE;
}

int SaveThrowItems(rsPLAYINFO* lpPlayInfo, TRANS_THROW_ITEMS* lpTransThrowItems)
{
	int cnt;

	for (cnt = 0; cnt < lpTransThrowItems->ThrowItemCount; cnt++) {
		if (lpPlayInfo->ThrowItemCount >= THROW_ITEM_INFO_MAX - 1) {
			SaveThrowItemOver(lpPlayInfo,
				lpTransThrowItems->ThrowItems[cnt].dwCode,
				lpTransThrowItems->ThrowItems[cnt].dwHead,
				lpTransThrowItems->ThrowItems[cnt].dwChkSum);
		}
		else {
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwCode = lpTransThrowItems->ThrowItems[cnt].dwCode;
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwKey = lpTransThrowItems->ThrowItems[cnt].dwHead;
			lpPlayInfo->ThrowItemInfo[lpPlayInfo->ThrowItemCount].dwSum = lpTransThrowItems->ThrowItems[cnt].dwChkSum;
			lpPlayInfo->ThrowItemCount++;
		}
	}

	return TRUE;
}

int	rsFindInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;

	if (!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++) {
		if (lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwKey == dwHead &&
			lpPlayInfo->InvenItemInfo[cnt].dwSum == dwChkSum) {
			return cnt;
		}
	}

	if (lpPlayInfo->OpenWarehouseInfoFlag) {
		for (cnt = 0; cnt < 100; cnt++) {
			if (lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwSum == dwChkSum) {
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	return -1;
}

int	rsFindInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode)
{
	int cnt;

	if (!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
	{
		if (lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode)
		{
			return cnt;
		}
	}

	if (lpPlayInfo->OpenWarehouseInfoFlag)
	{
		for (cnt = 0; cnt < 100; cnt++)
		{
			if (lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode)
			{
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	return -1;
}

int	rsCheckInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode)
{
	int cnt;

	if (!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++) {
		if (lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode) {
			return cnt;
		}
	}

	if (lpPlayInfo->OpenWarehouseInfoFlag) {
		for (cnt = 0; cnt < 100; cnt++) {
			if (lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode) {
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	return -1;
}

int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;

	if (!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++) {
		if (lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwKey == dwHead &&
			lpPlayInfo->InvenItemInfo[cnt].dwSum == dwChkSum) {
			lpPlayInfo->InvenItemInfo[cnt].dwCode = 0;
			return cnt;
		}
	}

	if (lpPlayInfo->OpenWarehouseInfoFlag) {
		for (cnt = 0; cnt < 100; cnt++) {
			if (lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwSum == dwChkSum) {
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode = 0;
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	return -1;
}

int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode)
{
	int cnt;

	if (!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++)
	{
		if (lpPlayInfo->InvenItemInfo[cnt].dwCode &&
			lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode)
		{
			lpPlayInfo->InvenItemInfo[cnt].dwCode = 0;
			return cnt;
		}
	}

	if (lpPlayInfo->OpenWarehouseInfoFlag)
	{
		for (cnt = 0; cnt < 100; cnt++)
		{
			if (lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode)
			{
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode = 0;
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	return -1;
}

int	rsAddInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int	cnt;
	int	Empty;

	if (!rsServerConfig.ServerInventoryMode) return INVEN_ITEM_INFO_MAX;

	if ((dwCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1) || dwCode == (sinGG1 | sin01)) return INVEN_ITEM_INFO_MAX;

	Empty = -1;

	for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++) {
		if (lpPlayInfo->InvenItemInfo[cnt].dwCode) {
			if (lpPlayInfo->InvenItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->InvenItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->InvenItemInfo[cnt].dwSum == dwChkSum) {
				return cnt;
			}
		}
		else {
			Empty = cnt;
		}
	}

	if (lpPlayInfo->OpenWarehouseInfoFlag) {
		for (cnt = 0; cnt < 100; cnt++) {
			if (lpPlayInfo->WareHouseItemInfo[cnt].dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwCode == dwCode &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwKey == dwHead &&
				lpPlayInfo->WareHouseItemInfo[cnt].dwSum == dwChkSum) {
				return INVEN_ITEM_INFO_MAX;
			}
		}
	}

	if (Empty >= 0) {
		lpPlayInfo->InvenItemInfo[Empty].dwCode = dwCode;
		lpPlayInfo->InvenItemInfo[Empty].dwKey = dwHead;
		lpPlayInfo->InvenItemInfo[Empty].dwSum = dwChkSum;
		return Empty;
	}

	smTRANS_COMMAND	smTransCommand;

	smTransCommand.WParam = 8050;
	smTransCommand.LParam = dwCode;
	smTransCommand.SParam = Empty;
	smTransCommand.EParam = (int)lpPlayInfo->OpenWarehouseInfoFlag;
	RecordHackLogFile(lpPlayInfo, &smTransCommand);

	return -1;
}

int rsGetServerPotion(rsPLAYINFO* lpPlayInfo, DWORD dwPotionCode)
{
	int x = -1, y = -1;

	switch (dwPotionCode) {
	case (sinPL1 | sin01):
		x = 0; y = 0;
		break;
	case (sinPL1 | sin02):
		x = 0; y = 1;
		break;
	case (sinPL1 | sin03):
		x = 0; y = 2;
		break;
	case (sinPL1 | sin04):
		x = 0; y = 3;
		break;

	case (sinPM1 | sin01):
		x = 1; y = 0;
		break;
	case (sinPM1 | sin02):
		x = 1; y = 1;
		break;
	case (sinPM1 | sin03):
		x = 1; y = 2;
		break;
	case (sinPM1 | sin04):
		x = 1; y = 3;
		break;

	case (sinPS1 | sin01):
		x = 2; y = 0;
		break;
	case (sinPS1 | sin02):
		x = 2; y = 1;
		break;
	case (sinPS1 | sin03):
		x = 2; y = 2;
		break;
	case (sinPS1 | sin04):
		x = 2; y = 3;
		break;
	}

	if (x >= 0 && y >= 0)
		return lpPlayInfo->ServerPotion[x][y];

	return 0;
}

int rsAddServerPotion(rsPLAYINFO* lpPlayInfo, DWORD dwPotionCode, int PotionCount)
{
	int Count = PotionCount;
	int x, y, pos;

	if (!rsServerConfig.PotionMonitor) return FALSE;

	x = -1;
	y = -1;
	pos = 0;

	switch (dwPotionCode) {
	case (sinPL1 | sin01):
		x = 0; y = 0;
		break;
	case (sinPL1 | sin02):
		x = 0; y = 1;
		break;
	case (sinPL1 | sin03):
		x = 0; y = 2;
		break;
	case (sinPL1 | sin04):
		x = 0; y = 3;
		break;

	case (sinPM1 | sin01):
		x = 1; y = 0;
		break;
	case (sinPM1 | sin02):
		x = 1; y = 1;
		break;
	case (sinPM1 | sin03):
		x = 1; y = 2;
		break;
	case (sinPM1 | sin04):
		x = 1; y = 3;
		break;

	case (sinPS1 | sin01):
		x = 2; y = 0;
		break;
	case (sinPS1 | sin02):
		x = 2; y = 1;
		break;
	case (sinPS1 | sin03):
		x = 2; y = 2;
		break;
	case (sinPS1 | sin04):
		x = 2; y = 3;
		break;
	}

	pos = lpPlayInfo->ServerPotion[x][y] + Count;

	if (pos < 0 && Count < 0) {
		lpPlayInfo->ServerPotion[x][y] = 0;
		return pos;
	}

	lpPlayInfo->ServerPotion[x][y] = pos;

	return pos;
}

int rsServerPotionErrorLog(rsPLAYINFO* lpPlayInfo, DWORD dwCode, int Count, int Position)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	if (lpPlayInfo->WarningCount < 3) {
		smTransCommandEx.WParam = 8810;
		smTransCommandEx.LParam = dwCode;
		smTransCommandEx.SParam = Count;
		smTransCommandEx.EParam = Position;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	return TRUE;
}

int	rsGetTradePotionInfo(rsPLAYINFO* lpPlayInfo, DWORD dwCode)
{
	int cnt;

	for (cnt = 0; cnt < lpPlayInfo->TradePotionInfoCount; cnt++) {
		if (lpPlayInfo->dwTradePotionInfo[cnt] == dwCode) {
			return TRUE;
		}
	}

	return FALSE;
}

int	rsAddTradePotionInfo(rsPLAYINFO* lpPlayInfo, DWORD	dwCode)
{
	if (lpPlayInfo->TradePotionInfoCount >= 16) return FALSE;

	if (rsGetTradePotionInfo(lpPlayInfo, dwCode) == TRUE) return TRUE;

	lpPlayInfo->dwTradePotionInfo[lpPlayInfo->TradePotionInfoCount++] = dwCode;

	return TRUE;
}

int	rsTradeInvenItem(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, TRANS_TRADE_ITEMKEY* lpTransTradeItemKey)
{
	int cnt;
	int money;
	smTRANS_COMMAND_EX	smTransCommand;
	DWORD	dwTradeCode;
	DWORD	dwTradeTime;
	int	PotionCount;

	if (!lpPlayInfo || !lpPlayInfo2) return FALSE;

	dwTradeCode = (lpTransTradeItemKey->Money * lpPlayInfo->dwObjectSerial + lpPlayInfo2->dwObjectSerial);
	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (lpTransTradeItemKey->dwItemCode[cnt]) {
			dwTradeCode += (lpTransTradeItemKey->dwItemCode[cnt] + lpTransTradeItemKey->dwItemKey[cnt] +
				lpTransTradeItemKey->dwItemSum[cnt]) * (cnt + 2);
		}
	}
	dwTradeTime = dwPlayServTime;

	if ((dwTradeTime - lpPlayInfo->dwLastTradeTime) < 8000 && lpPlayInfo->dwLastTradeChksum == dwTradeCode) {
		for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
			if (lpTransTradeItemKey->dwItemCode[cnt]) {
				if ((lpTransTradeItemKey->dwItemCode[cnt] & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1)) {
					if (rsDeleteInvenItem(lpPlayInfo,
						lpTransTradeItemKey->dwItemCode[cnt],
						lpTransTradeItemKey->dwItemKey[cnt],
						lpTransTradeItemKey->dwItemSum[cnt]) >= 0) {
						smTransCommand.WParam = 8000;
						smTransCommand.WxParam = 31;
						smTransCommand.LxParam = (int)"*TRADE CHECKING ERROR*";
						smTransCommand.LParam = lpTransTradeItemKey->dwItemCode[cnt];
						smTransCommand.SParam = lpTransTradeItemKey->dwItemKey[cnt];
						smTransCommand.EParam = lpTransTradeItemKey->dwItemSum[cnt];
						RecordHackLogFile(lpPlayInfo, &smTransCommand);
					}
				}
			}
		}
		return TRUE;
	}

	lpPlayInfo->TradePotionInfoCount = 0;

	if (lpTransTradeItemKey->Money) {
		money = lpTransTradeItemKey->Money - 193;
		if (lpPlayInfo->ServerMoney < money) {
			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 30;
			smTransCommand.SParam = lpPlayInfo->ServerMoney;
			smTransCommand.EParam = money;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			return FALSE;
		}

		lpPlayInfo->SubServerMoney(money, WHERE_TRADE);
		lpPlayInfo2->AddServerMoney(money, WHERE_TRADE);
	}

	if (lpTransTradeItemKey->Coin)
	{
		if (!CoinShop::GetInstance()->TransferTradeCoin(lpPlayInfo, lpPlayInfo2, lpTransTradeItemKey->Coin))
			return FALSE;
	}

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (lpTransTradeItemKey->dwItemCode[cnt]) {
			if ((lpTransTradeItemKey->dwItemCode[cnt] & sinITEM_MASK1) != (sinPM1 & sinITEM_MASK1)) {
				if (rsDeleteInvenItem(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt],
					lpTransTradeItemKey->dwItemKey[cnt],
					lpTransTradeItemKey->dwItemSum[cnt]) < 0) {
					smTransCommand.WParam = 8000;
					smTransCommand.WxParam = 30;
					smTransCommand.LxParam = (int)"*TRADE ITEM*";
					smTransCommand.LParam = lpTransTradeItemKey->dwItemCode[cnt];
					smTransCommand.SParam = lpTransTradeItemKey->dwItemKey[cnt];
					smTransCommand.EParam = lpTransTradeItemKey->dwItemSum[cnt];
					RecordHackLogFile(lpPlayInfo, &smTransCommand);

					lpTransTradeItemKey->dwItemKey[cnt] = 0;
				}
			}
			else {
				PotionCount = 0x5cbc ^ (lpTransTradeItemKey->dwItemSum[cnt] >> 16) ^ lpTransTradeItemKey->dwItemSum[cnt];
				PotionCount &= 0xFFFF;

				if (rsAddServerPotion(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], -PotionCount) < 0) {
					rsServerPotionErrorLog(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], -PotionCount, 100);
					return FALSE;
				}
				rsAddServerPotion(lpPlayInfo2, lpTransTradeItemKey->dwItemCode[cnt], PotionCount);

				rsAddTradePotionInfo(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt]);
			}

			if (lpTransTradeItemKey->dwItemKey[cnt]) {
				rsAddInvenItem(lpPlayInfo2, lpTransTradeItemKey->dwItemCode[cnt],
					lpTransTradeItemKey->dwItemKey[cnt],
					lpTransTradeItemKey->dwItemSum[cnt]);

				SaveThrowItem2(lpPlayInfo, lpTransTradeItemKey->dwItemCode[cnt], lpTransTradeItemKey->dwItemKey[cnt], lpTransTradeItemKey->dwItemSum[cnt]);
			}
		}
	}

	lpPlayInfo->dwLastTradeTime = dwTradeTime;
	lpPlayInfo->dwLastTradeChksum = dwTradeCode;

	rsRecord_ItemLog_Trade(lpPlayInfo, lpPlayInfo2, lpTransTradeItemKey);

	return TRUE;
}

int SendChatMessage()
{
	int cnt;
	TRANS_CHATBUFF	tChatBuff;
	rsPLAYINFO* lpPlayInfo;
	CHATBUFF* lpChatBuff;
	int len;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		lpPlayInfo = &rsPlayInfo[cnt];
		if (lpPlayInfo->lpsmSock && rsPlayInfo[cnt].dwObjectSerial && lpPlayInfo->ChatBuffCnt < ChatBuffCnt) {
			if ((ChatBuffCnt - lpPlayInfo->ChatBuffCnt) > 32) {
				lpPlayInfo->ChatBuffCnt = ChatBuffCnt - 8;
			}

			lpChatBuff = &ChatBuff[lpPlayInfo->ChatBuffCnt & CHATBUFF_MASK];

			len = sizeof(TRANS_CHATBUFF) + lstrlen(lpChatBuff->szMessage) + 1;

			tChatBuff.code = smTRANSCODE_CHATMESSAGE;
			tChatBuff.dwIP = lpChatBuff->dwIP;
			tChatBuff.size = len;
			memcpy(TransTemp, &tChatBuff, sizeof(TRANS_CHATBUFF));
			lstrcpy(TransTemp + sizeof(TRANS_CHATBUFF), lpChatBuff->szMessage);
			if (lpPlayInfo->lpsmSock->Send(TransTemp, len, TRUE) == TRUE) {
				lpPlayInfo->ChatBuffCnt++;
			}
		}
	}

	return TRUE;
}

int SendShopItemList(smWINSOCK* lpsmSock, smCHAR* lpChar)
{
	int cnt;
	char szBuff[smSOCKBUFF_SIZE];
	smTRANS_SELL_ITEM* lpTransSellItem;
	sDEF_ITEMINFO* lpDefItem;
	char* lpBuff;
	int TransLen;
	int	ItemCount;

	lpTransSellItem = (smTRANS_SELL_ITEM*)szBuff;

	lpTransSellItem->code = smTRANSCODE_SHOP_ITEMLIST;

	if (lpChar->smMonsterInfo.SellAttackItemCount) {
		ItemCount = 0;

		lpBuff = ((char*)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for (cnt = 0; cnt < lpChar->smMonsterInfo.SellAttackItemCount; cnt++) {
			lpDefItem = (sDEF_ITEMINFO*)lpChar->smMonsterInfo.SellAttackItem[cnt];
			if (lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < smSOCKBUFF_SIZE) {
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 1;
		lpTransSellItem->ItemCounter = ItemCount;
		lpsmSock->Send((char*)lpTransSellItem, lpTransSellItem->size, TRUE);
	}

	if (lpChar->smMonsterInfo.SellDefenceItemCount) {
		ItemCount = 0;

		lpBuff = ((char*)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for (cnt = 0; cnt < lpChar->smMonsterInfo.SellDefenceItemCount; cnt++) {
			lpDefItem = (sDEF_ITEMINFO*)lpChar->smMonsterInfo.SellDefenceItem[cnt];
			if (lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < smSOCKBUFF_SIZE) {
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 2;
		lpTransSellItem->ItemCounter = ItemCount;
		lpsmSock->Send((char*)lpTransSellItem, lpTransSellItem->size, TRUE);
	}

	if (lpChar->smMonsterInfo.SellEtcItemCount) {
		ItemCount = 0;

		lpBuff = ((char*)lpTransSellItem) + sizeof(smTRANS_SELL_ITEM);
		TransLen = sizeof(smTRANS_SELL_ITEM);
		for (cnt = 0; cnt < lpChar->smMonsterInfo.SellEtcItemCount; cnt++) {
			lpDefItem = (sDEF_ITEMINFO*)lpChar->smMonsterInfo.SellEtcItem[cnt];
			if (lpDefItem && (TransLen + lpDefItem->DefCompressDataLen) < smSOCKBUFF_SIZE) {
				memcpy(lpBuff, lpDefItem->DefCompressData, lpDefItem->DefCompressDataLen);
				TransLen += lpDefItem->DefCompressDataLen;
				lpBuff += lpDefItem->DefCompressDataLen;
				ItemCount++;
			}
		}
		lpTransSellItem->size = TransLen;
		lpTransSellItem->ItemKind = 3;
		lpTransSellItem->ItemCounter = ItemCount;
		lpsmSock->Send((char*)lpTransSellItem, lpTransSellItem->size, TRUE);
	}

	return TRUE;
}

int SendSkillMenu(smWINSOCK* lpsmSock, smCHAR* lpChar, int Mode)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_SKILL_MENU;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = Mode;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	if (rsServerConfig.Disable_Quest == Mode)
		smTransCommand.WParam = FALSE;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendWareHouseToClient(rsPLAYINFO* lpPlayInfo)
{
	if ((lpPlayInfo->dwDataError & rsDATA_ERROR_WAREHOUSE) != 0)
		return FALSE;

	if (lpPlayInfo->szID[0] && !lpPlayInfo->szServerID[0] && ((TRANS_RECORD_DATA*)lpPlayInfo->lpRecordDataBuff)->size > 0) {
		return rsLoadWareHouseData(lpPlayInfo);
	}

	return FALSE;
}

int SendOpenWareHouse(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_WAREHOUSE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenMixItem(smWINSOCK* lpsmSock, int MixFlag)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_MIXITEM;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = MixFlag;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenSmelting(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_SMELTING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenManufacture(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_MANUFACTURE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenCollectMoney(smWINSOCK* lpsmSock, int NPC)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_COLLECT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = NPC;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenEventGift(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_EVENTGIFT;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenGiftExpress(rsPLAYINFO* lpPlayInfo, DWORD	dwItemCode, DWORD dwPassCode_Param) {
	if (rsLoadPostBox(lpPlayInfo) == FALSE) return FALSE;
	if (!lpPlayInfo->lpPostBoxItem) return FALSE;
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpPlayInfo->PostPassFailCount >= 5) {
		lstrcpy(TransChatMessage.szMessage, srMsg_301);
		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

		return FALSE;
	}

	char	szBuff[sizeof(TRANS_POST_ITEM) + sizeof(sITEMINFO) + 64];
	TRANS_POST_ITEM* lpTransPostItem = (TRANS_POST_ITEM*)szBuff;
	sITEMINFO* lpItem = (sITEMINFO*)(szBuff + sizeof(TRANS_POST_ITEM));
	int		cnt, cnt2;
	psITEM	psItem;
	int		spJobCode;
	DWORD	dwPassCode;
	DWORD	dwFormCode;
	char* szPassCode;
	int		TempWeight = 0;		// pluto 해외 빌링 아이템 무게

	ZeroMemory(lpTransPostItem, sizeof(TRANS_POST_ITEM));

	lpTransPostItem->code = smTRANSCODE_ITEM_EXPRESS;

	if (dwItemCode) {
		spJobCode = 0;
		dwPassCode = 0;
		dwFormCode = 0;
		szPassCode = 0;

		for (cnt = 0; cnt < lpPlayInfo->lpPostBoxItem->ItemCounter; cnt++) {
			if (lpPlayInfo->lpPostBoxItem->PostItem[cnt].Flag &&
				lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode == dwItemCode &&
				(lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName[0] == '*' ||
					lstrcmpi(lpPlayInfo->szName, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName) == 0)) {
				spJobCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwJobCode;
				dwFormCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwFormCode;
				dwPassCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwPassCode;
				szPassCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].szPassCode;

				if (dwPassCode && dwPassCode != dwPassCode_Param) {
					//비밀 번호 틀림 ( 핸드폰 번호 )
					cnt = lpPlayInfo->lpPostBoxItem->ItemCounter;
					lpPlayInfo->PostPassFailCount++;

					lstrcpy(TransChatMessage.szMessage, srMsg_300);
					TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
					TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
					TransChatMessage.dwIP = 0;
					TransChatMessage.dwObjectSerial = 0;
					lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

					break;
				}

				lpPlayInfo->lpPostBoxItem->PostItem[cnt].Flag = 0;
				break;
			}
		}
		if (cnt < lpPlayInfo->lpPostBoxItem->ItemCounter) {
			lpPlayInfo->PostPassFailCount = 0;

			if (dwItemCode == (sinGG1 | sin01)) {
				lpTransPostItem->dwItemFlag = TRUE;
				ZeroMemory(lpItem, sizeof(sITEMINFO));
				lpItem->CODE = sinGG1 | sin01;
				lpItem->Money = spJobCode;
				ReformItem(lpItem);
				lpPlayInfo->AddServerMoney(spJobCode, WHERE_GIFT_EXPRESS);

				rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, 0, spJobCode, dwFormCode, szPassCode, ITEMLOG_EXPRESS);
			}
			else if (dwItemCode == (sinGG1 | sin02)) {
				lpTransPostItem->dwItemFlag = TRUE;
				ZeroMemory(lpItem, sizeof(sITEMINFO));
				lpItem->CODE = sinGG1 | sin02;
				lpItem->Money = spJobCode;
				ReformItem(lpItem);
				lpPlayInfo->dwGameServerExp[rsServerConfig.ServerCode] += spJobCode;

				rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, 0, spJobCode, dwFormCode, szPassCode, ITEMLOG_EXPRESS);
			}
			else {
				for (cnt = 0; cnt < DefaultItemCount; cnt++) {
					if (DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem) {
						CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt], spJobCode, 1);
						lpTransPostItem->dwItemFlag = TRUE;
						TempWeight = DefaultItems[cnt].Item.Weight;
						memcpy(lpItem, &psItem.ItemInfo, sizeof(sITEMINFO));

						if ((dwItemCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
							lpItem->PotionCount = spJobCode;
							rsAddServerPotion(lpPlayInfo, dwItemCode, lpItem->PotionCount);
							rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, 0, spJobCode, dwFormCode, szPassCode, ITEMLOG_EXPRESS);
						}
						else {
							rsAddInvenItem(lpPlayInfo, lpItem->CODE, lpItem->ItemHeader.Head, lpItem->ItemHeader.dwChkSum);

							rsRecord_ItemLog_Post(lpPlayInfo, lpItem->CODE, lpItem->ItemHeader.Head, lpItem->ItemHeader.dwChkSum,
								dwFormCode, szPassCode, ITEMLOG_EXPRESS);
						}

						break;
					}
				}
			}
		}

		rsSavePostBox(lpPlayInfo);
	}

	for (cnt = 0; cnt < lpPlayInfo->lpPostBoxItem->ItemCounter; cnt++) {
		if (lpPlayInfo->lpPostBoxItem->PostItem[cnt].Flag &&
			(lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName[0] == '*' ||
				lstrcmpi(lpPlayInfo->szName, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szCharName) == 0)) {
			if (lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode == (sinGG1 | sin01) ||
				lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode == (sinGG1 | sin02)) {
				lstrcpy(lpTransPostItem->szItemName, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szItemCode);	//아이템 이름
				lstrcpy(lpTransPostItem->szDoc, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szDoc);			//설명

				lpTransPostItem->dwItemCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode;
				lpTransPostItem->dwItemJobCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwJobCode;
				lpTransPostItem->dwParam[0] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[0];
				lpTransPostItem->dwParam[1] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[1];
				lpTransPostItem->dwParam[2] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[2];
				lpTransPostItem->dwParam[3] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[3];
				lpTransPostItem->Weight = TempWeight;
				break;
			}
			else {
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
					if (DefaultItems[cnt2].Item.CODE == lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode &&
						!DefaultItems[cnt2].Item.UniqueItem) {
						lstrcpy(lpTransPostItem->szItemName, DefaultItems[cnt2].Item.ItemName);				//아이템 이름
						lstrcpy(lpTransPostItem->szDoc, lpPlayInfo->lpPostBoxItem->PostItem[cnt].szDoc);	//설명

						lpTransPostItem->dwItemCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwItemCode;
						lpTransPostItem->dwItemJobCode = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwJobCode;
						lpTransPostItem->dwParam[0] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[0];
						lpTransPostItem->dwParam[1] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[1];
						lpTransPostItem->dwParam[2] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[2];
						lpTransPostItem->dwParam[3] = lpPlayInfo->lpPostBoxItem->PostItem[cnt].dwParam[3];
						lpTransPostItem->Weight = DefaultItems[cnt2].Item.Weight;
						break;
					}
				}
				if (cnt2 < DefaultItemCount) break;
			}
		}
	}

	lpTransPostItem->size = sizeof(TRANS_POST_ITEM);
	if (lpTransPostItem->dwItemFlag) lpTransPostItem->size += sizeof(sITEMINFO);

	if (lpPlayInfo->lpsmSock || (lpTransPostItem->dwItemCode || lpTransPostItem->dwItemFlag)) {
		lpPlayInfo->lpsmSock->Send2((char*)lpTransPostItem, lpTransPostItem->size, TRUE);
	}

	return TRUE;
}

int SendOpenAgingItem(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_AGING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenMixtureItemReset(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_MIXTURE_RESET;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenRemodelItem(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_REMODEL;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenCoinShop(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_COIN_SHOP;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int SendOpenTimeShop(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_TIME_SHOP;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int rsSend_BadPlayerToGameServer(smWINSOCK* lpsmSock, int BadPlayer)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_BAD_PLAYER;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = BadPlayer;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	return rsSendGameServer(lpsmSock, &smTransCommand);
}

int rsSend_PlayerKilling(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_PLAYERKILLING;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	if (lpsmSock)
		return lpsmSock->Send2((char*)&smTransCommand, sizeof(smTRANS_COMMAND), TRUE);

	return FALSE;
}

int SendOpenClanMenu(smWINSOCK* lpsmSock)
{
	smTRANS_COMMAND		smTransCommand;

	smTransCommand.code = smTRANSCODE_OPEN_CLANMENU;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = 0;
	smTransCommand.LParam = 0;
	smTransCommand.SParam = 0;

	return lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
}

int rsProcessQuest(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar, int QuestCode, int QuestParam)
{
	smTRANS_COMMAND	smTransCommand;

	if (!lpPlayInfo->lpsmSock) return FALSE;

	smTransCommand.code = smTRANSCODE_QUEST_MESSAGE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = lpChar->smMonsterInfo.QuestCode;
	smTransCommand.LParam = lpChar->smMonsterInfo.QuestParam;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	switch (QuestCode) {
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:

		if (QuestParam == 1) {
			smTransCommand.SParam = rsPutItem(lpPlayInfo, sinMA1 | sin01);
		}
		break;

	case SIN_QUEST_CODE_CHANGEJOB4:
	case HAQUEST_CODE_FURYOFPHANTOM:
		smTransCommand.WParam = QuestCode;
		smTransCommand.LParam = QuestParam;
		break;
	}

	lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}

int rsGetQuestCommand(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	DWORD dwItemCode;

	if (!lpPlayInfo->lpsmSock) return FALSE;

	switch (lpTransCommand->WParam) {
	case SIN_QUEST_CODE_LEVEL85:

		if (lpPlayInfo->smCharInfo.Level >= 85)
			rsPutItem(lpPlayInfo, sinQT1 | sin08);
		break;
	case SIN_QUEST_CODE_LEVEL90:

		if (lpPlayInfo->smCharInfo.Level >= 90)
			rsPutItem(lpPlayInfo, sinQT1 | sin07);
		break;

	case SIN_QUEST_CODE_CHANGEJOB4:
		if (lpPlayInfo->smCharInfo.Level >= 49 && lpTransCommand->LParam == QUEST_ARENA_FIELD) {
			OpenMonster_QuestArena(lpPlayInfo, SIN_QUEST_CODE_CHANGEJOB4);
		}
		break;

	case HAQUEST_CODE_FURYOFPHANTOM:
		if (lpPlayInfo->smCharInfo.Level >= 99 && lpTransCommand->LParam == QUEST_ARENA_FIELD) {
			OpenMonster_QuestArena(lpPlayInfo, HAQUEST_CODE_FURYOFPHANTOM, lpTransCommand->SParam);
		}
		break;
	}

#include "svrHaQuest.h"

	return TRUE;
}

int	rsDeleteClientItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpItem)
{
	TRANS_ITEM_CODE	TransItemCode;

	TransItemCode.code = smTRANSCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = lpItem->ItemHeader.Head;
	TransItemCode.dwChkSum = lpItem->ItemHeader.dwChkSum;
	TransItemCode.dwItemCode = lpItem->CODE;
	TransItemCode.dwTime = 0;

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		lpPlayInfo->lpsmSock->Send2((char*)&TransItemCode, TransItemCode.size, TRUE);
	}

	return TRUE;
}

int	rsDeleteClientItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	TRANS_ITEM_CODE	TransItemCode;

	TransItemCode.code = smTRANSCODE_ERRORITEM;
	TransItemCode.size = sizeof(TRANS_ITEM_CODE);
	TransItemCode.dwFlag = FALSE;
	TransItemCode.dwHead = dwHead;
	TransItemCode.dwChkSum = dwChkSum;
	TransItemCode.dwItemCode = dwCode;
	TransItemCode.dwTime = 0;

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		lpPlayInfo->lpsmSock->Send2((char*)&TransItemCode, TransItemCode.size, TRUE);
	}

	return TRUE;
}

int rsRecvAgingUpgradeItem(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo)
{
	sITEMINFO sItemInfo;

	if (CheckItemForm(&lpTransItemInfo->Item) == FALSE) return FALSE;

	if (rsDeleteInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum) < 0)
		return FALSE;

	/*if (lpTransItemInfo->Item.ItemAgingNum[0] >= 20)
		return FALSE;*/

	memcpy(&sItemInfo, &lpTransItemInfo->Item, sizeof(sITEMINFO));

	lpTransItemInfo->Item.dwCreateTime = 0;
	sinSetAgingItemIncreState(&lpTransItemInfo->Item);

	rsAddInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum);

	rsSaveAgingItemToHDD(&lpTransItemInfo->Item);

	RecordAgingItem(lpPlayInfo, &sItemInfo, &lpTransItemInfo->Item, TRUE);

	rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
		lpTransItemInfo->Item.CODE, lpTransItemInfo->Item.ItemHeader.Head, lpTransItemInfo->Item.ItemHeader.dwChkSum, ITEMLOG_AGINGUP);

	return lpPlayInfo->lpsmSock->Send2((char*)lpTransItemInfo, lpTransItemInfo->size, TRUE);
}

int rsRecvAgingItem(rsPLAYINFO* lpPlayInfo, sCRAFTITEM_SERVER* pCraftItem_Server)
{
	cAGING		ccItem;
	sITEMINFO	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int Price;
	int	QuestMode;
	int	AgingCnt, AgingLog;

	ErrorFlag = 0;

	rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_AGINGLOST);

	for (cnt = 0; cnt < 12; cnt++)
	{
		if (pCraftItem_Server->SheltomCode[cnt])
		{
			if (rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]) < 0)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 70;
				smTransCommandEx.LxParam = (int)"*AGING SHELTON*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;

				pCraftItem_Server->SheltomCode[cnt] = 0;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItemInfo, sizeof(sITEMINFO));

	if (AgingEvento == TRUE)
	{
		Price = 0;
	}
	else
	{
		Price = ((sItemInfo.ItemAgingNum[0] + 1) * sItemInfo.Price) / 2;
	}

	CurrencyLog.int64_AgingMoney += Price;

	if (rsServerConfig.ServerInventoryMode && sItemInfo.ItemKindCode != ITEM_KIND_QUEST_WEAPON)
	{
		if (lpPlayInfo->ServerMoney < Price)
		{
			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 70;
			smTransCommand.SParam = lpPlayInfo->ServerMoney;
			smTransCommand.EParam = Price;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			lpPlayInfo->SetServerMoney(0, WHERE_AGINGITEM);
			ErrorFlag++;
		}
		else
		{
			lpPlayInfo->SubServerMoney(Price, WHERE_AGINGITEM);
			lpPlayInfo->UnsaveMoney = lpPlayInfo->ServerMoney;
		}
	}

	if (CheckItemForm(&sItemInfo) == FALSE || CheckMixItem(&sItemInfo) == FALSE)
	{
		sAging_Recv.Result = FALSE;
		sAging_Recv.size = 32;
		if (lpPlayInfo && lpPlayInfo->lpsmSock)
		{
			lpPlayInfo->lpsmSock->Send2((char*)&sAging_Recv, sAging_Recv.size, TRUE);
		}

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 1;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}

	if ((sItemInfo.CODE & sinITEM_MASK2) == sinMA1)
		QuestMode = TRUE;
	else
	{
		if (lpPlayInfo->AdminMode == 10)
			QuestMode = -1;
		else
			QuestMode = FALSE;
	}

	int pedraDireto = 0;

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin73)))
	{
		pedraDireto = 1;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin74)))
	{
		pedraDireto = 2;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin75)))
	{
		pedraDireto = 3;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin76)))
	{
		pedraDireto = 4;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin77)))
	{
		pedraDireto = 5;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin78)))
	{
		pedraDireto = 6;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin79)))
	{
		pedraDireto = 7;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin80)))
	{
		pedraDireto = 8;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin81)))
	{
		pedraDireto = 9;
	}

	if ((pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin82)))
	{
		pedraDireto = 10;
	}

	if (pCraftItem_Server->A_StoneItemCode)
	{
		if ((pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin10) || pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin11) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin60) || pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin61) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin85)) &&  // Àåº° - ½´ÆÛ ¿¡ÀÌÂ¡ ½ºÅæ 1.5
			rsDeleteInvenItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode,
				pCraftItem_Server->A_StoneHead,
				pCraftItem_Server->A_StoneCheckSum) >= 0)
		{
			rsRecord_ItemLog2(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum, ITEMLOG_AGINGLOST);

			SaveThrowItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum);
		}
		else
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 70;
			smTransCommandEx.LxParam = (int)"Aging Stone";
			smTransCommandEx.LParam = pCraftItem_Server->A_StoneItemCode;
			smTransCommandEx.SParam = pCraftItem_Server->A_StoneHead;
			smTransCommandEx.EParam = pCraftItem_Server->A_StoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			pCraftItem_Server->A_StoneItemCode = 0;
		}
	}
	else
	{
		pCraftItem_Server->A_StoneItemCode = 0;
	}

	ccItem.sinRecvAgingItem(pCraftItem_Server);
	cnt = ccItem.AgingItem(QuestMode);

	if (ErrorFlag) sAging_Recv.Result = FALSE;

	if (rsDeleteInvenItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum) < 0)
	{
		sAging_Recv.size = 32;
		sAging_Recv.Result = FALSE;

		smTransCommandEx.WParam = 8000;
		smTransCommandEx.WxParam = 70;
		smTransCommandEx.LxParam = (int)sItemInfo.ItemName;
		smTransCommandEx.LParam = sItemInfo.CODE;
		smTransCommandEx.SParam = sItemInfo.ItemHeader.Head;
		smTransCommandEx.EParam = sItemInfo.ItemHeader.dwChkSum;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	sAging_Recv.code = smTRANSCODE_AGINGITEM;
	if (sAging_Recv.Result)
	{
		if (QuestMode == TRUE)
		{
			for (cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if (DefaultItems[cnt].Item.CODE == sAging_Recv.DesCraftItem.sItemInfo.CODE)
				{
					CreateDefItem(&sAging_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt]);
					break;
				}
			}
		}

		int atual;
		int age;

		switch (pedraDireto)
		{
		case 1:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 10 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;
		case 2:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 15 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 3:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 18 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 4:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 20 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 5:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 21 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 6:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 22 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 7:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 23 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 8:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 12 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 9:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 16 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;

		case 10:
			atual = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			age = 26 - atual; // PEDRA DO AGING DIRETO

			SetAgingItem(&sAging_Recv.DesCraftItem.sItemInfo, age);
			break;
		}

		ReformItem(&sAging_Recv.DesCraftItem.sItemInfo);
		sAging_Recv.size = sizeof(sITEM) + 32;

		rsAddInvenItem(lpPlayInfo, sAging_Recv.DesCraftItem.sItemInfo.CODE,
			sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.Head,
			sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum);

		if (QuestMode != TRUE)
		{
			RecordAgingItem(lpPlayInfo, &sItemInfo, &sAging_Recv.DesCraftItem.sItemInfo, FALSE);

			AgingCnt = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] - sItemInfo.ItemAgingNum[0];
			AgingLog = ITEMLOG_AGING;
			char szMsgAging[256];
			int AgeNum = 0;

			if (pedraDireto > 0) {
				AgeNum = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0];
			}
			else {
				AgeNum = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] + 1;
			}
			switch (sAging_Recv.Result)
			{
			case 4:
				AgingLog = ITEMLOG_AGING_2UP;

				if (AgeNum >= 14)
				{
					for (cnt = 0; cnt < CONNECTMAX; cnt++)
					{
						if (rsPlayInfo[cnt].lpsmSock)
						{
							rsSendServerChatMessageToUser(&rsPlayInfo[cnt], 3, "Melisandre: %s envelheceu (%s) para o [+%d] com sucesso! Parabéns!", lpPlayInfo->szName, sAging_Recv.DesCraftItem.sItemInfo.ItemName, AgeNum);
						}
					}
				}

				break;
			case 3:
				AgingLog = ITEMLOG_AGING;

				if (AgeNum >= 14)
				{
					for (cnt = 0; cnt < CONNECTMAX; cnt++)
					{
						if (rsPlayInfo[cnt].lpsmSock)
						{
							rsSendServerChatMessageToUser(&rsPlayInfo[cnt], 3, "Melisandre: %s envelheceu (%s) para o [+%d] com sucesso, Parabéns!", lpPlayInfo->szName, sAging_Recv.DesCraftItem.sItemInfo.ItemName, AgeNum);
						}
					}
				}

				break;

			case 1:
				AgingLog = ITEMLOG_AGING_1DOWN;

				if (AgeNum >= 14)
				{
					for (cnt = 0; cnt < CONNECTMAX; cnt++)
					{
						if (rsPlayInfo[cnt].lpsmSock)
						{
							rsSendServerChatMessageToUser(&rsPlayInfo[cnt], 3, "Melisandre: %s retrocedeu (%s) para o [+%d], Mais sorte na próxima vez!", lpPlayInfo->szName, sAging_Recv.DesCraftItem.sItemInfo.ItemName, AgeNum);
						}
					}
				}

				break;
			case 2:
				AgingLog = ITEMLOG_AGING_2DOWN;

				if (AgeNum >= 14)
				{
					for (cnt = 0; cnt < CONNECTMAX; cnt++)
					{
						if (rsPlayInfo[cnt].lpsmSock)
						{
							rsSendServerChatMessageToUser(&rsPlayInfo[cnt], 3, "Melisandre: %s retrocedeu (%s) para o [+%d], Mais sorte na próxima vez!", lpPlayInfo->szName, sAging_Recv.DesCraftItem.sItemInfo.ItemName, AgeNum);
						}
					}
				}

				break;
			}

			rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
				sAging_Recv.DesCraftItem.sItemInfo.CODE, sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.Head, sAging_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum, AgingLog);

			rsSaveAgingItemToHDD(&sAging_Recv.DesCraftItem.sItemInfo);
		}

		SaveThrowItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum);
	}
	else
	{
		sAging_Recv.size = 32;

		if (QuestMode != TRUE)
		{
			//lpPlayInfo->dwBrokenItemHead = sItemInfo.ItemHeader.Head;
			//lpPlayInfo->dwBrokenItemSum = sItemInfo.ItemHeader.dwChkSum;

			rsSaveAgingItemToHDD(&sItemInfo);

			RecordAgingItem(lpPlayInfo, &sItemInfo, 0, FALSE);

			rsRecord_ItemLog2(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum, ITEMLOG_AGINGLOST);
		}
	}

	if (lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send2((char*)&sAging_Recv, sAging_Recv.size, TRUE);
	}

	int AgeNum = sAging_Recv.DesCraftItem.sItemInfo.ItemAgingNum[0] + 1;

	if (!sAging_Recv.Result)
	{
		if (AgeNum >= 10)
		{
			for (cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock)
				{
					rsSendServerChatMessageToUser(&rsPlayInfo[cnt], 3, "Moriph: %s quebrou (%s) no [+%d], Mais sorte na próxima vez!", lpPlayInfo->szName, sItemInfo.ItemName, sItemInfo.ItemAgingNum[0]);
				}
			}
		}
	}

	return TRUE;
}

int rsRecvCraftItem(rsPLAYINFO* lpPlayInfo, sCRAFTITEM_SERVER* pCraftItem_Server)
{
	cCRAFTITEM	ccItem;
	sITEMINFO	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int Result;
	DWORD ItemCraftType = 0;
	int RandNum = 0;
	int ItemCnt = 0;

	DWORD dwResultItemCode = pCraftItem_Server->DesCraftItem.sItemInfo.CODE;
	DWORD dwResultItemSkinFlag = pCraftItem_Server->DesCraftItem.sItemInfo.SwapItem.Flag;
	DWORD dwResultItemSkinCode = pCraftItem_Server->DesCraftItem.sItemInfo.SwapItem.Code;
	int LinkedItem = pCraftItem_Server->DesCraftItem.sItemInfo.LinkedItem;
	int LockItem = pCraftItem_Server->DesCraftItem.sItemInfo.LockItem;

	ErrorFlag = 0;

	for (cnt = 0; cnt < 12; cnt++)
	{
		if ((pCraftItem_Server->SheltomCode[cnt] & sinITEM_MASK2) == sinSE1)
		{
			if (pCraftItem_Server->SheltomCode[cnt] == (sinSE1 | sin05))
			{
				ItemCraftType = (sinSE1 | sin05);
			}
			else
			{
				ItemCraftType = sinSE1;
			}
			break;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinPR1 | sin01))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinPR2 | sin01))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinOE1 | sin01))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinOE1 | sin02))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinPR1 | sin02))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinPR2 | sin02))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinPR1 | sin03))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinPR1 | sin04))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinPR2 | sin03))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinBI1 | sin10))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinBI1 | sin61))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinOS1 | sin20))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinOS1 | sin21))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
		else if (pCraftItem_Server->SheltomCode[cnt] == (sinBI2 | sin57))
		{
			ItemCraftType = pCraftItem_Server->SheltomCode[cnt];
			ItemCnt++;
		}
	}

	if (ItemCraftType == sinSE1 || ItemCraftType == (sinSE1 | sin05))
	{
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_LOST_RECON);
	}
	else
	{
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_MIXLOST);
	}

	for (cnt = 0; cnt < 12; cnt++)
	{
		if (pCraftItem_Server->SheltomCode[cnt])
		{
			if (rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]) < 0)
			{
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*MIXTRUE SHELTON*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;

				pCraftItem_Server->SheltomCode[cnt] = 0;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItemInfo, sizeof(sITEMINFO));

	CurrencyLog.int64_CraftMoney += sItemInfo.Price;

	if (rsServerConfig.ServerInventoryMode) {
		if (lpPlayInfo->ServerMoney < sItemInfo.Price) {
			smTransCommand.WParam = 8010;
			smTransCommand.LParam = 50;
			smTransCommand.SParam = lpPlayInfo->ServerMoney;
			smTransCommand.EParam = sItemInfo.Price;
			RecordHackLogFile(lpPlayInfo, &smTransCommand);

			lpPlayInfo->SetServerMoney(0, WHERE_CRAFTITEM);
			ErrorFlag++;
		}
		else {
			lpPlayInfo->SubServerMoney(sItemInfo.Price, WHERE_CRAFTITEM);
			lpPlayInfo->UnsaveMoney = lpPlayInfo->ServerMoney;
		}
	}

	if (CheckItemForm(&sItemInfo) == FALSE || sItemInfo.ItemKindCode != 0 || CheckMixItem(&sItemInfo) == FALSE) {
		sCraftItem_Recv.Result = FALSE;
		sCraftItem_Recv.size = 32;
		if (lpPlayInfo && lpPlayInfo->lpsmSock) {
			lpPlayInfo->lpsmSock->Send2((char*)&sCraftItem_Recv, sCraftItem_Recv.size, TRUE);
		}

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 0;
		smTransCommand.LParam = 0;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}

	if (pCraftItem_Server->A_StoneItemCode)
	{
		if ((pCraftItem_Server->A_StoneItemCode == (sinBI1 | sin90) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin46) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin47) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin48) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin49) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin50) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin51) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin52) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin53) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin54) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin55) ||
			pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin56)) &&
			rsDeleteInvenItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode,
				pCraftItem_Server->A_StoneHead,
				pCraftItem_Server->A_StoneCheckSum) >= 0)
		{
			rsRecord_ItemLog2(lpPlayInfo, pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum, ITEMLOG_LOST_RECON);

			SaveThrowItem(lpPlayInfo,
				pCraftItem_Server->A_StoneItemCode, pCraftItem_Server->A_StoneHead, pCraftItem_Server->A_StoneCheckSum);

			RandNum = GetRandomPos(1, 100);
			if (RandNum < 51)
				spJobCode = lpPlayInfo->smCharInfo.JOB_CODE;
			else
				spJobCode = lpPlayInfo->smCharInfo.JOB_CODE + 100;

			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin46))
				spJobCode = 1;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin47))
				spJobCode = 2;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin48))
				spJobCode = 3;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin49))
				spJobCode = 4;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin50))
				spJobCode = 5;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin51))
				spJobCode = 6;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin52))
				spJobCode = 7;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin53))
				spJobCode = 8;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin54))
				spJobCode = 9;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin55))
				spJobCode = 10;
			if (pCraftItem_Server->A_StoneItemCode == (sinBI2 | sin56))
				spJobCode = 11;
		}
		else {
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 70;
			smTransCommandEx.LxParam = (int)"Aging Stone";
			smTransCommandEx.LParam = pCraftItem_Server->A_StoneItemCode;
			smTransCommandEx.SParam = pCraftItem_Server->A_StoneHead;
			smTransCommandEx.EParam = pCraftItem_Server->A_StoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			pCraftItem_Server->A_StoneItemCode = 0;
		}
	}
	else {
		pCraftItem_Server->A_StoneItemCode = 0;
	}

	ccItem.sinRecvCraftItem(pCraftItem_Server);
	Result = ccItem.MixingItem();

	if (ItemCnt == 3 && pCraftItem_Server->DesCraftItem.sItemInfo.CODE == (sinOS1 | sin19))
	{
		DWORD NewCode;

		switch (ItemCraftType)
		{
		case (sinPR1 | sin01):
			NewCode = (sinPR2 | sin01);
			break;
		case (sinPR2 | sin01):
			NewCode = (sinOE1 | sin01);
			break;
		case (sinOE1 | sin01):
			NewCode = (sinOE1 | sin02);
			break;
		case (sinOE1 | sin02):
			NewCode = (sinOE1 | sin03);
			break;
		case (sinPR1 | sin02):
			NewCode = (sinPR2 | sin02);
			break;
		case (sinPR2 | sin02):
			NewCode = (sinOR1 | sin29);
			break;
		case (sinPR1 | sin03):
			NewCode = (sinPR2 | sin03);
			break;
		case (sinPR1 | sin04):
			NewCode = (sinPR2 | sin04);
			break;
		case (sinPR2 | sin03):
			NewCode = (sinOA1 | sin29);
			break;
		case (sinBI1 | sin10):
			NewCode = (sinBI1 | sin61);
			break;
		case (sinBI1 | sin61):
			NewCode = (sinBI1 | sin85);
			break;
		case (sinBI2 | sin57):
			NewCode = (sinBI2 | sin68);
			break;
		case (sinOS1 | sin20):
			NewCode = (sinOS1 | sin21);
			break;
		case (sinOS1 | sin21):
			NewCode = (sinOS1 | sin22);
			break;
		}

		for (cnt = 0; cnt < DefaultItemCount; cnt++)
		{
			if (DefaultItems[cnt].Item.CODE == NewCode && !DefaultItems[cnt].Item.UniqueItem)
			{
				if (ItemCraftType == (sinSE1 | sin05))
					CreateDefItemPerf(&sCraftItem_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt], spJobCode);
				else
					CreateDefItem(&sCraftItem_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt], spJobCode);

				sCraftItem_Recv.DesCraftItem.sItemInfo.LinkedItem = LinkedItem;
				sCraftItem_Recv.DesCraftItem.sItemInfo.LockItem = LockItem;
				break;
			}
		}

		sCraftItem_Recv.DocIndex = 2000;
		sCraftItem_Recv.Result = TRUE;
	}

	if (ErrorFlag) sCraftItem_Recv.Result = FALSE;

	if (Result == 2000)
	{
		if (dwResultItemSkinFlag != 0)
		{
			for (cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if (DefaultItems[cnt].Item.CODE == dwResultItemSkinCode && !DefaultItems[cnt].Item.UniqueItem)
				{
					if (ItemCraftType == (sinSE1 | sin05))
						CreateDefItemPerf(&sCraftItem_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt], spJobCode);
					else
						CreateDefItem(&sCraftItem_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt], spJobCode);

					sCraftItem_Recv.DesCraftItem.sItemInfo.CODE = dwResultItemCode;
					sCraftItem_Recv.DesCraftItem.sItemInfo.SwapItem.Flag = dwResultItemSkinFlag;
					sCraftItem_Recv.DesCraftItem.sItemInfo.SwapItem.Code = dwResultItemSkinCode;
					sCraftItem_Recv.DesCraftItem.sItemInfo.LinkedItem = LinkedItem;
					sCraftItem_Recv.DesCraftItem.sItemInfo.LockItem = LockItem;
					break;
				}
			}
		}
		else
		{
			for (cnt = 0; cnt < DefaultItemCount; cnt++)
			{
				if (DefaultItems[cnt].Item.CODE == sCraftItem_Recv.DesCraftItem.sItemInfo.CODE && !DefaultItems[cnt].Item.UniqueItem)
				{
					if (ItemCraftType == (sinSE1 | sin05))
						CreateDefItemPerf(&sCraftItem_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt], spJobCode);
					else
						CreateDefItem(&sCraftItem_Recv.DesCraftItem.sItemInfo, &DefaultItems[cnt], spJobCode);

					sCraftItem_Recv.DesCraftItem.sItemInfo.LinkedItem = LinkedItem;
					sCraftItem_Recv.DesCraftItem.sItemInfo.LockItem = LockItem;
					break;
				}
			}
		}
	}

	spJobCode = 0;

	sCraftItem_Recv.code = smTRANSCODE_CRAFTITEM;
	if (sCraftItem_Recv.Result == TRUE) {
		ReformItem(&sCraftItem_Recv.DesCraftItem.sItemInfo);
		sCraftItem_Recv.size = sizeof(sITEM) + 32;

		if (rsDeleteInvenItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum) >= 0) {
			rsAddInvenItem(lpPlayInfo, sCraftItem_Recv.DesCraftItem.sItemInfo.CODE,
				sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.Head,
				sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum);

			RecordMixItem(lpPlayInfo, &sItemInfo, &sCraftItem_Recv.DesCraftItem.sItemInfo);

			if (ItemCraftType == sinSE1) {
				rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
					sCraftItem_Recv.DesCraftItem.sItemInfo.CODE, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.Head, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_GET_RECON);
			}
			else {
				rsRecord_ItemLog_Change(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum,
					sCraftItem_Recv.DesCraftItem.sItemInfo.CODE, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.Head, sCraftItem_Recv.DesCraftItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_MIXING);
			}

			rsSaveAgingItemToHDD(&sCraftItem_Recv.DesCraftItem.sItemInfo);
		}
		else {
			sCraftItem_Recv.size = 32;
			sCraftItem_Recv.Result = FALSE;

			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)sItemInfo.ItemName;
			smTransCommandEx.LParam = sItemInfo.CODE;
			smTransCommandEx.SParam = sItemInfo.ItemHeader.Head;
			smTransCommandEx.EParam = sItemInfo.ItemHeader.dwChkSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
		}
		SaveThrowItem(lpPlayInfo, sItemInfo.CODE, sItemInfo.ItemHeader.Head, sItemInfo.ItemHeader.dwChkSum);
	}
	else {
		sCraftItem_Recv.size = 32;
	}

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		lpPlayInfo->lpsmSock->Send2((char*)&sCraftItem_Recv, sCraftItem_Recv.size, TRUE);
	}

	sCraftItem_Recv.DesCraftItem.sItemInfo.CODE = 0;
	sCraftItem_Recv.DesCraftItem.sItemInfo.SwapItem.Flag = 0;
	sCraftItem_Recv.DesCraftItem.sItemInfo.SwapItem.Code = 0;
	sCraftItem_Recv.DesCraftItem.sItemInfo.LinkedItem = 0;
	sCraftItem_Recv.DesCraftItem.sItemInfo.LockItem = 0;

	return TRUE;
}

//int rsRecvSmeltingItem(rsPLAYINFO* lpPlayInfo, sSMELTINGITEM_SERVER* pSmeltingItem_Server)
//{
//	CSmeltingItem ccItem;
//
//
//	smTRANS_COMMAND_EX	smTransCommandEx;
//
//	int cnt;
//	int	ErrorFlag;
//
//	DWORD ItemSmeltingType = 0;
//
//	bool bFirst_Ore = TRUE;
//	bool bOre_OK = TRUE;
//	DWORD first_Ore = 0;
//	DWORD Next_Ore = 0;
//	int ore_num = 0;
//	int crystal_num = 0;
//
//	bool bFirst_Sheltom = TRUE;
//	bool bSheltom_OK = TRUE;
//	DWORD first_Sheltom = 0;
//	DWORD Next_Sheltom = 0;
//
//	ErrorFlag = 0;
//
//
//	rsRecord_SmeltingItemLog(lpPlayInfo, pSmeltingItem_Server->SmeltingCode, pSmeltingItem_Server->Head, pSmeltingItem_Server->CheckSum, ITEMLOG_SMELTING_LOST);
//	for (cnt = 0; cnt < 3; cnt++)
//	{
//		if (pSmeltingItem_Server->SmeltingCode[cnt])
//		{
//			if ((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinPR1)
//			{
//				if (ore_num < 3)
//				{
//					ItemSmeltingType = sinPR1;
//					ore_num++;
//				}
//			}
//			else if ((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinPR2)
//			{
//				if (crystal_num < 3)
//				{
//					ItemSmeltingType = sinPR2;
//					crystal_num++;
//				}
//			}
//			else if ((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinBI1)
//			{
//				if (crystal_num < 3)
//				{
//					ItemSmeltingType = sinBI1;
//					crystal_num++;
//				}
//			}
//			else if ((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinOE1)
//			{
//				if (crystal_num < 3)
//				{
//					ItemSmeltingType = sinOE1;
//					crystal_num++;
//				}
//			}
//			else if ((pSmeltingItem_Server->SmeltingCode[cnt] & sinITEM_MASK2) == sinBI2)
//			{
//				if (crystal_num < 3)
//				{
//					ItemSmeltingType = sinBI2;
//					crystal_num++;
//				}
//			}
//			if (rsDeleteInvenItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[cnt],
//				pSmeltingItem_Server->Head[cnt], pSmeltingItem_Server->CheckSum[cnt]) < 0)
//			{
//				if (ItemSmeltingType == sinPR1)
//				{
//
//					smTransCommandEx.WParam = 8000;
//					smTransCommandEx.WxParam = 50;
//					smTransCommandEx.LxParam = (int)"*SMELTING ORE*";
//					smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[cnt];
//					smTransCommandEx.SParam = pSmeltingItem_Server->Head[cnt];
//					smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[cnt];
//					RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
//				}
//				else if (ItemSmeltingType == sinPR2)
//				{
//
//					smTransCommandEx.WParam = 8000;
//					smTransCommandEx.WxParam = 50;
//					smTransCommandEx.LxParam = (int)"*SMELTING CRYSTAL*";
//					smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[cnt];
//					smTransCommandEx.SParam = pSmeltingItem_Server->Head[cnt];
//					smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[cnt];
//					RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
//				}
//				ErrorFlag++;
//
//				pSmeltingItem_Server->SmeltingCode[cnt] = 0;
//			}
//			else
//			{
//				if (bFirst_Ore)
//				{
//					first_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
//					Next_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
//					bFirst_Ore = FALSE;
//				}
//				else
//				{
//					Next_Ore = pSmeltingItem_Server->SmeltingCode[cnt];
//				}
//				if (first_Ore != Next_Ore)
//				{
//					bOre_OK = FALSE;
//					ErrorFlag++;
//				}
//			}
//			SaveThrowItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[cnt],
//				pSmeltingItem_Server->Head[cnt], pSmeltingItem_Server->CheckSum[cnt]);
//		}
//	}
//
//	if (ItemSmeltingType == sinPR1 && ore_num != 3)
//	{
//		bOre_OK = FALSE;
//		ErrorFlag++;
//	}
//	else if (ItemSmeltingType == sinPR2 && crystal_num != 3)
//	{
//		bOre_OK = FALSE;
//		ErrorFlag++;
//	}
//	else if (ItemSmeltingType == sinBI1 && crystal_num != 3)
//	{
//		bOre_OK = FALSE;
//		ErrorFlag++;
//	}
//	else if (ItemSmeltingType == sinBI2 && crystal_num != 3)
//	{
//		bOre_OK = FALSE;
//		ErrorFlag++;
//	}
//	else if (ItemSmeltingType == sinOE1 && crystal_num != 3)
//	{
//		bOre_OK = FALSE;
//		ErrorFlag++;
//	}
//
//	if (pSmeltingItem_Server->SmeltingCode[4])
//	{
//		if (rsDeleteInvenItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[4],
//			pSmeltingItem_Server->Head[4], pSmeltingItem_Server->CheckSum[4]) < 0)
//		{
//
//			smTransCommandEx.WParam = 8000;
//			smTransCommandEx.WxParam = 50;
//			smTransCommandEx.LxParam = (int)"*SMELTING SHELTON*";
//			smTransCommandEx.LParam = pSmeltingItem_Server->SmeltingCode[4];
//			smTransCommandEx.SParam = pSmeltingItem_Server->Head[4];
//			smTransCommandEx.EParam = pSmeltingItem_Server->CheckSum[4];
//			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
//			ErrorFlag++;
//
//			pSmeltingItem_Server->SmeltingCode[4] = 0;
//		}
//		if (bFirst_Sheltom)
//		{
//			first_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
//			Next_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
//			bFirst_Sheltom = FALSE;
//		}
//		else
//		{
//			Next_Sheltom = pSmeltingItem_Server->SmeltingCode[4];
//		}
//		if (first_Sheltom != Next_Sheltom)
//		{
//			bSheltom_OK = FALSE;
//			ErrorFlag++;
//		}
//		SaveThrowItem(lpPlayInfo, pSmeltingItem_Server->SmeltingCode[4],
//			pSmeltingItem_Server->Head[4], pSmeltingItem_Server->CheckSum[4]);
//	}
//
//
//
//
//
//	DWORD code = 0;
//	if (bOre_OK && bSheltom_OK)
//	{
//		if ((Next_Ore & sinITEM_MASK2) == sinPR1)
//		{
//			if (Next_Ore == (sinPR1 | sin01) && Next_Sheltom == (sinOS1 | sin19))
//			{
//				code = (sinOE1 | sin01);
//			}
//			if (Next_Ore == (sinPR1 | sin02) && Next_Sheltom == (sinOS1 | sin19))
//			{
//				code = (sinOR1 | sin29);
//			}
//			else if (Next_Ore == (sinPR1 | sin03) && Next_Sheltom == (sinOS1 | sin19))
//			{
//				code = (sinOA1 | sin29);
//			}
//		}
//
//		else if ((Next_Ore & sinITEM_MASK2) == sinOE1)
//		{
//			if (Next_Ore == (sinOE1 | sin01) && Next_Sheltom == (sinOS1 | sin19))
//			{
//				code = (sinOE1 | sin02);
//			}
//			else if (Next_Ore == (sinOE1 | sin02) && Next_Sheltom == (sinOS1 | sin19))
//			{
//				code = (sinOE1 | sin03);
//			}
//		}
//
//		else if ((Next_Ore & sinITEM_MASK2) == sinBI2)
//		{
//			if (Next_Ore == (sinBI2 | sin57) && Next_Sheltom == (sinBI2 | sin57))
//			{
//				code = (sinBI1 | sin10);
//			}
//		}
//
//
//		else if ((Next_Ore & sinITEM_MASK2) == sinBI1)
//		{
//			if (Next_Ore == (sinBI1 | sin10) && Next_Sheltom == (sinBI2 | sin57))
//			{
//				code = (sinBI1 | sin67);
//			}
//			else if (Next_Ore == (sinBI1 | sin67) && Next_Sheltom == (sinBI1 | sin57))
//			{
//				code = (sinBI1 | sin85);
//			}
//		}
//
//		else
//		{
//			ErrorFlag++;
//		}
//
//		if (code != 0)
//		{
//			for (cnt = 0; cnt < DefaultItemCount; cnt++)
//			{
//				if (DefaultItems[cnt].Item.CODE == code)
//				{
//
//					CreateDefItem(&pSmeltingItem_Server->DesSmeltingItem.sItemInfo, &DefaultItems[cnt]);
//					break;
//				}
//			}
//		}
//
//	}
//
//	ccItem.sinRecvSmeltingItem(pSmeltingItem_Server);
//
//	if (ErrorFlag)
//	{
//		sSmeltingItem_Recv.Result = FALSE;
//	}
//	else
//	{
//		sSmeltingItem_Recv.Result = TRUE;
//	}
//
//	if (sSmeltingItem_Recv.Result == TRUE)
//	{
//		ReformItem(&sSmeltingItem_Recv.DesSmeltingItem.sItemInfo);
//		sSmeltingItem_Recv.size = sizeof(sITEM) + 32;
//
//		rsAddInvenItem(lpPlayInfo, sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.CODE,
//			sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.Head,
//			sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.dwChkSum);
//
//		rsRecord_ItemLog2(lpPlayInfo, sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.CODE, sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.Head,
//			sSmeltingItem_Recv.DesSmeltingItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_SMELTING_GET);
//
//		RecordSmeltingItem(lpPlayInfo, &sSmeltingItem_Recv.DesSmeltingItem.sItemInfo);
//
//	}
//	else
//	{
//		sSmeltingItem_Recv.size = 32;
//	}
//
//	sSmeltingItem_Recv.code = smTRANSCODE_SMELTINGITEM;
//
//	if (lpPlayInfo && lpPlayInfo->lpsmSock)
//	{
//		lpPlayInfo->lpsmSock->Send2((char*)&sSmeltingItem_Recv, sSmeltingItem_Recv.size, TRUE);
//	}
//
//	return TRUE;
//}

//int ManufactureItemInfo(rsPLAYINFO* lpPlayInfo)
//{
//
//	DWORD	dwItem = 0;
//
//
//	if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) dwItem = (sinDA2 | sin52);
//
//	else if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) dwItem = (sinDA2 | sin51);
//
//	else if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER || lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA) dwItem = (sinDA1 | sin52);
//
//	else dwItem = (sinDA1 | sin51);
//
//	DWORD CreateItemCode[176] = { (sinWA1 | sin14), (sinWC1 | sin14), (sinWH1 | sin15), (sinWP1 | sin15), (sinWS1 | sin16), (sinWS2 | sin17), (sinWT1 | sin15), (sinWM1 | sin15),
//									(sinWA1 | sin15), (sinWC1 | sin15), (sinWH1 | sin16), (sinWP1 | sin16), (sinWS1 | sin17), (sinWS2 | sin18), (sinWT1 | sin16), (sinWM1 | sin16),
//									(sinWA1 | sin16), (sinWC1 | sin16), (sinWH1 | sin17), (sinWP1 | sin17), (sinWS1 | sin18), (sinWS2 | sin19), (sinWT1 | sin17), (sinWM1 | sin17),
//									(sinWA1 | sin17), (sinWC1 | sin17), (sinWH1 | sin18), (sinWP1 | sin18), (sinWS1 | sin19), (sinWS2 | sin20), (sinWT1 | sin18), (sinWM1 | sin18),
//									(sinWA1 | sin18), (sinWC1 | sin18), (sinWH1 | sin19), (sinWP1 | sin19), (sinWS1 | sin20), (sinWS2 | sin21), (sinWT1 | sin19), (sinWM1 | sin19),
//									(sinWA1 | sin19), (sinWC1 | sin19), (sinWH1 | sin20), (sinWP1 | sin20), (sinWS1 | sin21), (sinWS2 | sin22), (sinWT1 | sin20), (sinWM1 | sin20),
//									(sinWA1 | sin21), (sinWC1 | sin21), (sinWH1 | sin22), (sinWP1 | sin22), (sinWS1 | sin23), (sinWS2 | sin24), (sinWT1 | sin22), (sinWM1 | sin22),
//									(sinWA1 | sin22), (sinWC1 | sin22), (sinWH1 | sin23), (sinWP1 | sin23), (sinWS1 | sin24), (sinWS2 | sin25), (sinWT1 | sin23), (sinWM1 | sin23),
//									0, 0, 0, 0, 0, 0, 0, 0,
//									0, 0, 0, 0, 0, 0, 0, 0,
//									0, 0, 0, 0, 0, 0, 0, 0,
//
//										(sinDA1 | sin16), (sinDA2 | sin16), (sinDS1 | sin14), (sinOM1 | sin15), (sinDG1 | sin14), (sinOA2 | sin14), (sinDB1 | sin14), 0,
//										(sinDA1 | sin17), (sinDA2 | sin17), (sinDS1 | sin15), (sinOM1 | sin16), (sinDG1 | sin15), (sinOA2 | sin15), (sinDB1 | sin15), 0,
//										(sinDA1 | sin18), (sinDA2 | sin18), (sinDS1 | sin16), (sinOM1 | sin17), (sinDG1 | sin16), (sinOA2 | sin16), (sinDB1 | sin16), 0,
//										(sinDA1 | sin19), (sinDA2 | sin19), (sinDS1 | sin17), (sinOM1 | sin18), (sinDG1 | sin17), (sinOA2 | sin17), (sinDB1 | sin17), 0,
//										(sinDA1 | sin20), (sinDA2 | sin20), (sinDS1 | sin18), (sinOM1 | sin19), (sinDG1 | sin18), (sinOA2 | sin18), (sinDB1 | sin18), 0,
//										(sinDA1 | sin21), (sinDA2 | sin21), (sinDS1 | sin19), (sinOM1 | sin20), (sinDG1 | sin19), (sinOA2 | sin19), (sinDB1 | sin19), 0,
//										(sinDA1 | sin23), (sinDA2 | sin23), (sinDS1 | sin21), (sinOM1 | sin22), (sinDG1 | sin21), (sinOA2 | sin21), (sinDB1 | sin21), 0,
//										(sinDA1 | sin24), (sinDA2 | sin24), (sinDS1 | sin22), (sinOM1 | sin23), (sinDG1 | sin22), (sinOA2 | sin22), (sinDB1 | sin22), 0,
//										0, 0, 0, 0, 0, 0, 0, 0,
//										 (sinOA1 | sin36), 0, 0, 0, 0, 0, 0, 0,
//										 dwItem, 0, 0, 0, 0, 0, 0, 0
//	};
//	int num = 0;
//	//SManufacture_ResultItemInfo_Server Item_Recv;
//	//ZeroMemory(&Item_Recv, sizeof(SManufacture_ResultItemInfo_Server));
//	Item_Recv.smTransCommand.code = smTRANSCODE_MANUFACTURE_WEIGHT_PRICE;
//	Item_Recv.smTransCommand.size = sizeof(SManufacture_ResultItemInfo_Server);
//	for (int i = 0; i < 176; i++)
//	{
//		for (int cnt = 0; cnt < DefaultItemCount; cnt++)
//		{
//			if (CreateItemCode[i] > 0 && CreateItemCode[i] == DefaultItems[cnt].Item.CODE)
//			{
//				Item_Recv.ItemCode[num] = DefaultItems[cnt].Item.CODE;
//				lstrcpy(Item_Recv.ItemName[num], DefaultItems[cnt].Item.ItemName);
//				Item_Recv.Weight[num] = DefaultItems[cnt].Item.Weight;
//				Item_Recv.Price[num] = DefaultItems[cnt].Item.Price;
//				num++;
//			}
//		}
//	}
//	if (lpPlayInfo && lpPlayInfo->lpsmSock)
//	{
//		lpPlayInfo->lpsmSock->Send2((char*)&Item_Recv, Item_Recv.smTransCommand.size, TRUE);
//	}
//	return TRUE;
//}
//
//int rsRecvManufactureItem(rsPLAYINFO* lpPlayInfo, SManufactureItem_Server* pManufactureItem_Server)
//{
//	CManufacture ccItem;
//
//	smTRANS_COMMAND_EX	smTransCommandEx;
//
//	int cnt;
//	int	ErrorFlag;
//	DWORD ItemSmeltingType = 0;
//	bool  bProbability = FALSE;
//	ErrorFlag = 0;
//
//	if (pManufactureItem_Server->RuneCode[0])
//	{
//		if (rsDeleteInvenItem(lpPlayInfo, pManufactureItem_Server->RuneCode[0],
//			pManufactureItem_Server->Head[0], pManufactureItem_Server->CheckSum[0]) < 0)
//		{
//
//			smTransCommandEx.WParam = 8000;
//			smTransCommandEx.WxParam = 50;
//			smTransCommandEx.LxParam = (int)"*Manufacture Recipe*";
//			smTransCommandEx.LParam = pManufactureItem_Server->RuneCode[0];
//			smTransCommandEx.SParam = pManufactureItem_Server->Head[0];
//			smTransCommandEx.EParam = pManufactureItem_Server->CheckSum[0];
//			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
//
//			ErrorFlag++;
//
//			pManufactureItem_Server->RuneCode[0] = 0;
//		}
//		SaveThrowItem(lpPlayInfo, pManufactureItem_Server->RuneCode[0],
//			pManufactureItem_Server->Head[0], pManufactureItem_Server->CheckSum[0]);
//	}
//
//	for (cnt = 1; cnt < 4; cnt++)
//	{
//		if (pManufactureItem_Server->RuneCode[cnt])
//		{
//			if (rsDeleteInvenItem(lpPlayInfo, pManufactureItem_Server->RuneCode[cnt],
//				pManufactureItem_Server->Head[cnt], pManufactureItem_Server->CheckSum[cnt]) < 0)
//			{
//
//				smTransCommandEx.WParam = 8000;
//				smTransCommandEx.WxParam = 50;
//				smTransCommandEx.LxParam = (int)"*Manufacture Rune*";
//				smTransCommandEx.LParam = pManufactureItem_Server->RuneCode[cnt];
//				smTransCommandEx.SParam = pManufactureItem_Server->Head[cnt];
//				smTransCommandEx.EParam = pManufactureItem_Server->CheckSum[cnt];
//				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
//
//				ErrorFlag++;
//
//				pManufactureItem_Server->RuneCode[cnt] = 0;
//			}
//			SaveThrowItem(lpPlayInfo, pManufactureItem_Server->RuneCode[cnt],
//				pManufactureItem_Server->Head[cnt], pManufactureItem_Server->CheckSum[cnt]);
//
//
//
//
//
//
//
//
//
//
//
//		}
//	}
//
//	DWORD ResultItemCode = 0;
//
//
//	if (ErrorFlag == 0)
//	{
//
//		ResultItemCode = ManufactureCheckRune(lpPlayInfo, pManufactureItem_Server->RuneCode[0], pManufactureItem_Server->RuneCode);
//		if (ResultItemCode != 0)
//		{
//			srand(time(NULL));
//#ifdef _LANGUAGE_VEITNAM
//			if ((rand() % 10) < 4)
//#else
//
//			if ((rand() % 100) < 50)
//#endif
//			{
//				for (cnt = 0; cnt < DefaultItemCount; cnt++)
//				{
//					if (DefaultItems[cnt].Item.CODE == ResultItemCode)
//					{
//
//						CreateDefItem(&pManufactureItem_Server->DesManufactureItem.sItemInfo, &DefaultItems[cnt]);
//						bProbability = TRUE;
//						break;
//					}
//				}
//			}
//			else
//			{
//				ErrorFlag++;
//			}
//		}
//		else
//		{
//			ErrorFlag++;
//		}
//	}
//	else
//	{
//		ErrorFlag++;
//	}
//	ccItem.sinRecvManufactureItem(pManufactureItem_Server);
//
//	if (bProbability)
//	{
//		g_sManufactureItem_Recv.Result = TRUE;
//	}
//
//	if (ErrorFlag)
//	{
//		g_sManufactureItem_Recv.Result = FALSE;
//	}
//
//
//	if (g_sManufactureItem_Recv.Result == TRUE)
//	{
//		ReformItem(&g_sManufactureItem_Recv.DesManufactureItem.sItemInfo);
//		g_sManufactureItem_Recv.size = sizeof(sITEM) + 32;
//
//		rsRecord_ManufactureItemLog(lpPlayInfo, pManufactureItem_Server->RuneCode, pManufactureItem_Server->Head, pManufactureItem_Server->CheckSum, ITEMLOG_MANUFACTURE_LOST);
//
//		rsAddInvenItem(lpPlayInfo, g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.CODE,
//			g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.Head,
//			g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.dwChkSum);
//
//		rsRecord_ItemLog2(lpPlayInfo, g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.CODE, g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.Head,
//			g_sManufactureItem_Recv.DesManufactureItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_MANUFACTURE_GET);
//
//
//		RecordManufactureItem(lpPlayInfo, &g_sManufactureItem_Recv.DesManufactureItem.sItemInfo);
//
//	}
//	else
//	{
//		g_sManufactureItem_Recv.size = 32;
//		rsRecord_ManufactureItemLog(lpPlayInfo, pManufactureItem_Server->RuneCode, pManufactureItem_Server->Head, pManufactureItem_Server->CheckSum, ITEMLOG_MANUFACTURE_FAIL);
//	}
//
//	g_sManufactureItem_Recv.code = smTRANSCODE_MANUFACTURE;
//
//	if (lpPlayInfo && lpPlayInfo->lpsmSock)
//	{
//		lpPlayInfo->lpsmSock->Send2((char*)&g_sManufactureItem_Recv, g_sManufactureItem_Recv.size, TRUE);
//	}
//
//	return TRUE;
//}

//int rsRecvMixtureResetItem(rsPLAYINFO* lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER* pMixtureResetItem_Server)
//{
//	cMIXTURERESET ccItem;
//	smTRANS_COMMAND_EX	smTransCommandEx;
//	int ErrorFlag = 0;
//	int MixtureResetSuccess = FALSE;
//
//
//	if (pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE)
//	{
//		if (rsDeleteInvenItem(lpPlayInfo, pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE,
//			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head,
//			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum) < 0)
//		{
//
//			smTransCommandEx.WParam = 8000;
//			smTransCommandEx.WxParam = 50;
//			smTransCommandEx.LxParam = (int)"*Mixture Reset Item*";
//			smTransCommandEx.LParam = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE;
//			smTransCommandEx.SParam = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head;
//			smTransCommandEx.EParam = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum;
//			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
//
//			ErrorFlag++;
//
//			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE = 0;
//		}
//
//		SaveThrowItem(lpPlayInfo, pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE,
//			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head,
//			pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum);
//	}
//
//
//	if (pMixtureResetItem_Server->dwMixtureResetStoneItemCode)
//	{
//		if (rsDeleteInvenItem(lpPlayInfo, pMixtureResetItem_Server->dwMixtureResetStoneItemCode,
//			pMixtureResetItem_Server->dwMixtureResetStoneHead, pMixtureResetItem_Server->dwMixtureResetStoneCheckSum) < 0)
//		{
//
//			smTransCommandEx.WParam = 8000;
//			smTransCommandEx.WxParam = 50;
//			smTransCommandEx.LxParam = (int)"*Mixture Reset Stone*";
//			smTransCommandEx.LParam = pMixtureResetItem_Server->dwMixtureResetStoneItemCode;
//			smTransCommandEx.SParam = pMixtureResetItem_Server->dwMixtureResetStoneHead;
//			smTransCommandEx.EParam = pMixtureResetItem_Server->dwMixtureResetStoneCheckSum;
//			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
//
//			ErrorFlag++;
//
//			pMixtureResetItem_Server->dwMixtureResetStoneItemCode = 0;
//		}
//
//		SaveThrowItem(lpPlayInfo, pMixtureResetItem_Server->dwMixtureResetStoneItemCode,
//			pMixtureResetItem_Server->dwMixtureResetStoneHead, pMixtureResetItem_Server->dwMixtureResetStoneCheckSum);
//	}
//
//
//	DWORD dwResultItemCode = 0;
//	DWORD dwResultItemSkinFlag = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.SwapItem.Flag;
//	DWORD dwResultItemSkinCode = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.SwapItem.Code;
//	int LinkedItem = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LinkedItem;
//	int LockItem = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LockItem;
//
//	dwResultItemCode = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE;
//
//
//
//	DWORD dwSpecialJob = 0;
//	dwSpecialJob = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.JobCodeMask;
//
//	int	i;
//	DWORD dwJobCode = 0;
//	JOB_DATA_CODE* pJobDataCode = 0;
//
//
//	for (i = 1; i < 12; i++)
//	{
//		pJobDataCode = GetJobDataCode(i, 0);
//		if (pJobDataCode->JobBitCode == dwSpecialJob)
//		{
//			dwJobCode = pJobDataCode->JobCode;
//			break;
//		}
//	}
//
//
//	if (i == 12)
//	{
//		dwJobCode = 0;
//		NotItemSpecial = 1;
//	}
//
//
//	if (ErrorFlag == 0)
//	{
//		if (dwResultItemSkinFlag != 0)
//		{
//			for (int cnt = 0; cnt < DefaultItemCount; cnt++)
//			{
//				if (DefaultItems[cnt].Item.CODE == dwResultItemSkinCode)
//				{
//					CreateDefItem(&pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo, &DefaultItems[cnt], dwJobCode);
//					pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE = dwResultItemCode;
//					pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.SwapItem.Flag = dwResultItemSkinFlag;
//					pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.SwapItem.Code = dwResultItemSkinCode;
//					pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LinkedItem = LinkedItem;
//					pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LockItem = LockItem;
//					MixtureResetSuccess = TRUE;
//					break;
//				}
//			}
//		}
//		else if (dwResultItemCode != 0)
//		{
//			for (int cnt = 0; cnt < DefaultItemCount; cnt++)
//			{
//				if (DefaultItems[cnt].Item.CODE == dwResultItemCode)
//				{
//					CreateDefItem(&pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo, &DefaultItems[cnt], dwJobCode);
//					pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LinkedItem = LinkedItem;
//					pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LockItem = LockItem;
//					MixtureResetSuccess = TRUE;
//					break;
//				}
//			}
//		}
//		else
//		{
//			ErrorFlag++;
//		}
//	}
//	else
//	{
//		ErrorFlag++;
//	}
//
//
//	ccItem.sinRecvMixtureItemReset(pMixtureResetItem_Server);
//
//
//	if (MixtureResetSuccess)
//		sMixtureReset_Recv.Result = TRUE;
//
//
//	if (ErrorFlag)
//		sMixtureReset_Recv.Result = FALSE;
//
//	if (sMixtureReset_Recv.Result == TRUE)
//	{
//		ReformItem(&sMixtureReset_Recv.DesMixtureResetItem.sItemInfo);
//		sMixtureReset_Recv.size = sizeof(sITEM) + 32;
//
//
//		rsRecord_MixtureResetItemLog(lpPlayInfo, pMixtureResetItem_Server, ITEMLOG_MIXTURE_RESET_LOST);
//
//
//		rsAddInvenItem(lpPlayInfo, sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.CODE,
//			sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.Head,
//			sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum);
//
//
//		rsRecord_ItemLog2(lpPlayInfo, sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.CODE, sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.Head,
//			sMixtureReset_Recv.DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_MIXTURE_RESET_GET);
//
//
//		RecordMixtureResetItem(lpPlayInfo, &sMixtureReset_Recv.DesMixtureResetItem.sItemInfo);
//	}
//	else
//	{
//		sMixtureReset_Recv.size = 32;
//		rsRecord_MixtureResetItemLog(lpPlayInfo, pMixtureResetItem_Server, ITEMLOG_MIXTURE_RESET_FAIL);
//	}
//
//
//	sMixtureReset_Recv.code = smTRANSCODE_MIXTURE_RESET_ITEM;
//
//	if (lpPlayInfo && lpPlayInfo->lpsmSock)
//	{
//		lpPlayInfo->lpsmSock->Send2((char*)&sMixtureReset_Recv, sMixtureReset_Recv.size, TRUE);
//	}
//
//	pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE = 0;
//	pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.SwapItem.Flag = 0;
//	pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.SwapItem.Code = 0;
//	pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LinkedItem = 0;
//	pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.LockItem = 0;
//
//	return TRUE;
//}

void GetRemodel(DWORD Flag, DWORD Code, SWAPITEM* Swap)
{
	Swap->Flag = Flag;

	switch (Code & sinITEM_MASK2)
	{
	case sinWA1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin38)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWA1 | sin32);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWA1 | sin33);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWA1 | sin34);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWA1 | sin35);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWA1 | sin36);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWA1 | sin37);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWA1 | sin16);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWA1 | sin17);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWA1 | sin10);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWA1 | sin13);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWA1 | sin20);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWA1 | sin15);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (sinWA1 | sin24);
		}
		break;
	case sinWN1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin38)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWN1 | sin09);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWN1 | sin10);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWN1 | sin11);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWN1 | sin12);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWN1 | sin13);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWN1 | sin14);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWN1 | sin15);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWN1 | sin17);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWN1 | sin25);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWN1 | sin19);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWN1 | sin20);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWN1 | sin21);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1091700);
		}
		break;
	case sinWD1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin38)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWD1 | sin07);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWD1 | sin08);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWD1 | sin09);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWD1 | sin10);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWD1 | sin11);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWD1 | sin12);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWD1 | sin13);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWD1 | sin14);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWD1 | sin15);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWD1 | sin16);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWD1 | sin17);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWD1 | sin18);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x10a1400);
		}
		break;
	case sinWV1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin38)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWV1 | sin10);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWV1 | sin11);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWV1 | sin12);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWV1 | sin13);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWV1 | sin14);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWV1 | sin15);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWV1 | sin16);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWV1 | sin17);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWV1 | sin20);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWV1 | sin21);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWV1 | sin22);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWV1 | sin25);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x10b2c00);
		}
		break;
	case sinWC1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin37)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWC1 | sin31);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWC1 | sin32);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWC1 | sin33);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWC1 | sin34);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWC1 | sin35);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWC1 | sin36);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWC1 | sin16);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWC1 | sin17);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWC1 | sin10);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWC1 | sin11);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWC1 | sin12);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWC1 | sin13);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1021800);
		}
		break;
	case sinWH1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin40)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWH1 | sin34);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWH1 | sin35);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWH1 | sin36);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWH1 | sin37);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWH1 | sin38);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWH1 | sin39);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWH1 | sin18);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWH1 | sin19);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWH1 | sin10);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWH1 | sin14);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWH1 | sin15);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWH1 | sin16);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1031900);
		}
		break;
	case sinWM1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin39)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWM1 | sin33);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWM1 | sin34);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWM1 | sin35);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWM1 | sin36);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWM1 | sin37);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWM1 | sin38);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWM1 | sin18);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWM1 | sin24);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWM1 | sin10);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWM1 | sin14);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWM1 | sin25);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWM1 | sin16);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1042d00);
		}
		break;
	case sinWP1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin38)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWP1 | sin32);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWP1 | sin33);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWP1 | sin34);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWP1 | sin35);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWP1 | sin36);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWP1 | sin37);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWP1 | sin17);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWP1 | sin18);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWP1 | sin10);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWP1 | sin11);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWP1 | sin12);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWP1 | sin13);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1051600);
		}
		break;
	case sinWS1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin39)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWS1 | sin33);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWS1 | sin34);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWS1 | sin35);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWS1 | sin36);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWS1 | sin37);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWS1 | sin38);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWS1 | sin10);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWS1 | sin20);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWS1 | sin11);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWS1 | sin12);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWS1 | sin13);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWS1 | sin14);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1062a00);
		}
		break;
	case sinWS2:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin43)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWS2 | sin35);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWS2 | sin41);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWS2 | sin42);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWS2 | sin38);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWS2 | sin39);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWS2 | sin40);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWS2 | sin19);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWS2 | sin21);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWS2 | sin13);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWS2 | sin18);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWS2 | sin15);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWS2 | sin16);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1072b00);
		}
		break;
	case sinWT1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin38)
		{
			if (Flag == (sinBI3 | sin01))
				Swap->Code = (sinWT1 | sin32);
			if (Flag == (sinBI3 | sin02))
				Swap->Code = (sinWT1 | sin33);
			if (Flag == (sinBI3 | sin03))
				Swap->Code = (sinWT1 | sin34);
			if (Flag == (sinBI3 | sin04))
				Swap->Code = (sinWT1 | sin35);
			if (Flag == (sinBI3 | sin05))
				Swap->Code = (sinWT1 | sin36);
			if (Flag == (sinBI3 | sin06))
				Swap->Code = (sinWT1 | sin37);
			if (Flag == (sinBI3 | sin20))
				Swap->Code = (sinWT1 | sin17);
			if (Flag == (sinBI3 | sin21))
				Swap->Code = (sinWT1 | sin18);
			if (Flag == (sinBI3 | sin22))
				Swap->Code = (sinWT1 | sin10);
			if (Flag == (sinBI3 | sin23))
				Swap->Code = (sinWT1 | sin11);
			if (Flag == (sinBI3 | sin24))
				Swap->Code = (sinWT1 | sin12);
			if (Flag == (sinBI3 | sin25))
				Swap->Code = (sinWT1 | sin13);
			if (Flag == (sinBI3 | sin26))
				Swap->Code = (0x1081900);
		}
		break;
	case sinDS1:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin39)
		{
			if (Flag == (sinBI3 | sin07))
				Swap->Code = (sinDS1 | sin31);
			if (Flag == (sinBI3 | sin08))
				Swap->Code = (sinDS1 | sin32);
			if (Flag == (sinBI3 | sin09))
				Swap->Code = (sinDS1 | sin33);
			if (Flag == (sinBI3 | sin10))
				Swap->Code = (sinDS1 | sin34);
			if (Flag == (sinBI3 | sin11))
				Swap->Code = (sinDS1 | sin35);
			if (Flag == (sinBI3 | sin12))
				Swap->Code = (sinDS1 | sin36);
			if (Flag == (sinBI3 | sin30))
				Swap->Code = (sinDS1 | sin19);
			if (Flag == (sinBI3 | sin31))
				Swap->Code = (sinDS1 | sin21);
			if (Flag == (sinBI3 | sin32))
				Swap->Code = (sinDS1 | sin05);
			if (Flag == (sinBI3 | sin33))
				Swap->Code = (sinDS1 | sin07);
			if (Flag == (sinBI3 | sin34))
				Swap->Code = (sinDS1 | sin09);
			if (Flag == (sinBI3 | sin35))
				Swap->Code = (sinDS1 | sin10);
			if (Flag == (sinBI3 | sin36))
				Swap->Code = (0x2040800);
		}
		break;
	case sinDA1:
	case sinDA3:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin29)
		{
			if (Flag == (sinBI3 | sin13))
				Swap->Code = (sinDA3 | sin04);
			if (Flag == (sinBI3 | sin14))
				Swap->Code = (sinDA3 | sin05);
			if (Flag == (sinBI3 | sin15))
				Swap->Code = (sinDA3 | sin06);
			if (Flag == (sinBI3 | sin16))
				Swap->Code = (sinDA3 | sin07);
			if (Flag == (sinBI3 | sin17))
				Swap->Code = (sinDA3 | sin08);
			if (Flag == (sinBI3 | sin18))
				Swap->Code = (sinDA3 | sin09);
			if (Flag == (sinBI3 | sin40))
				Swap->Code = (sinDA1 | sin18);
			if (Flag == (sinBI3 | sin41))
				Swap->Code = (sinDA1 | sin19);
			if (Flag == (sinBI3 | sin42))
				Swap->Code = (sinDA1 | sin08);
			if (Flag == (sinBI3 | sin43))
				Swap->Code = (sinDA1 | sin09);
			if (Flag == (sinBI3 | sin44))
				Swap->Code = (sinDA1 | sin10);
			if (Flag == (sinBI3 | sin45))
				Swap->Code = (sinDA1 | sin11);
		}
		break;
	case sinDA2:
	case sinDA4:
		if ((Code & sinITEM_MASK3) >= sin01 && (Code & sinITEM_MASK3) <= sin29)
		{
			if (Flag == (sinBI3 | sin13))
				Swap->Code = (sinDA4 | sin04);
			if (Flag == (sinBI3 | sin14))
				Swap->Code = (sinDA4 | sin05);
			if (Flag == (sinBI3 | sin15))
				Swap->Code = (sinDA4 | sin06);
			if (Flag == (sinBI3 | sin16))
				Swap->Code = (sinDA4 | sin07);
			if (Flag == (sinBI3 | sin17))
				Swap->Code = (sinDA4 | sin08);
			if (Flag == (sinBI3 | sin18))
				Swap->Code = (sinDA4 | sin09);
			if (Flag == (sinBI3 | sin40))
				Swap->Code = (sinDA2 | sin18);
			if (Flag == (sinBI3 | sin41))
				Swap->Code = (sinDA2 | sin19);
			if (Flag == (sinBI3 | sin42))
				Swap->Code = (sinDA2 | sin08);
			if (Flag == (sinBI3 | sin43))
				Swap->Code = (sinDA2 | sin09);
			if (Flag == (sinBI3 | sin44))
				Swap->Code = (sinDA2 | sin10);
			if (Flag == (sinBI3 | sin45))
				Swap->Code = (sinDA2 | sin11);
		}
		break;
	}
}

int rsRecvRemodelItem(rsPLAYINFO* lpPlayInfo, sREMODEL_ITEM_SERVER* pRemodelItem_Server)
{
	cREMODEL ccItem;
	smTRANS_COMMAND_EX	smTransCommandEx;
	DWORD Stone = 0;
	int ErrorFlag = 0;
	int RemodelSuccess = FALSE;

	if (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE)
	{
		if (rsDeleteInvenItem(lpPlayInfo, pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE,
			pRemodelItem_Server->DesRemodelItem.sItemInfo.ItemHeader.Head,
			pRemodelItem_Server->DesRemodelItem.sItemInfo.ItemHeader.dwChkSum) < 0)
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*Remodel Reset Item*";
			smTransCommandEx.LParam = pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE;
			smTransCommandEx.SParam = pRemodelItem_Server->DesRemodelItem.sItemInfo.ItemHeader.Head;
			smTransCommandEx.EParam = pRemodelItem_Server->DesRemodelItem.sItemInfo.ItemHeader.dwChkSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			ErrorFlag++;

			pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = 0;
		}

		SaveThrowItem(lpPlayInfo, pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE,
			pRemodelItem_Server->DesRemodelItem.sItemInfo.ItemHeader.Head,
			pRemodelItem_Server->DesRemodelItem.sItemInfo.ItemHeader.dwChkSum);
	}

	if (pRemodelItem_Server->dwRemodelStoneItemCode)
	{
		if (rsDeleteInvenItem(lpPlayInfo, pRemodelItem_Server->dwRemodelStoneItemCode,
			pRemodelItem_Server->dwRemodelStoneHead, pRemodelItem_Server->dwRemodelStoneCheckSum) < 0)
		{
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*Remodel Reset Stone*";
			smTransCommandEx.LParam = pRemodelItem_Server->dwRemodelStoneItemCode;
			smTransCommandEx.SParam = pRemodelItem_Server->dwRemodelStoneHead;
			smTransCommandEx.EParam = pRemodelItem_Server->dwRemodelStoneCheckSum;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

			ErrorFlag++;

			pRemodelItem_Server->dwRemodelStoneItemCode = 0;
		}

		SaveThrowItem(lpPlayInfo, pRemodelItem_Server->dwRemodelStoneItemCode,
			pRemodelItem_Server->dwRemodelStoneHead, pRemodelItem_Server->dwRemodelStoneCheckSum);
	}

	if ((pRemodelItem_Server->dwRemodelStoneItemCode & sinITEM_MASK2) == sinBI3)
	{
		if (!pRemodelItem_Server->DesRemodelItem.sItemInfo.SwapItem.Flag)
		{
			pRemodelItem_Server->DesRemodelItem.sItemInfo.SwapItem.Flag = pRemodelItem_Server->dwRemodelStoneItemCode;
			pRemodelItem_Server->DesRemodelItem.sItemInfo.SwapItem.Code = pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE;
		}
		else if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin19))
		{
			Stone = pRemodelItem_Server->DesRemodelItem.sItemInfo.SwapItem.Flag;
			pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = pRemodelItem_Server->DesRemodelItem.sItemInfo.SwapItem.Code;
			pRemodelItem_Server->DesRemodelItem.sItemInfo.SwapItem.Flag = 0;
			pRemodelItem_Server->DesRemodelItem.sItemInfo.SwapItem.Code = 0;
		}
	}

	switch (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK2)
	{
	case sinWA1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin38)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin32);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin33);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin37);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin16);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin17);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin20);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin15);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWA1 | sin24);
		}
		break;
	case sinWN1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin38)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin09);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin11);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin12);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin14);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin15);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin17);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin25);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin19);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin20);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWN1 | sin21);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1091700);
		}
		break;
	case sinWD1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin38)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin07);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin08);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin09);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin11);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin12);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin14);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin15);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin16);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin17);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWD1 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x10a1400);
		}
		break;
	case sinWV1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin38)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin11);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin12);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin14);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin15);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin16);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin17);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin20);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin21);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin22);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWV1 | sin25);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x10b2c00);
		}
		break;
	case sinWC1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin37)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin31);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin32);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin33);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin16);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin17);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin11);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin12);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWC1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1021800);
		}
		break;
	case sinWH1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin40)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin37);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin38);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin39);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin19);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin14);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin15);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWH1 | sin16);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1031900);
		}
		break;
	case sinWM1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin39)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin33);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin37);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin38);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin24);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin14);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin25);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWM1 | sin16);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1042d00);
		}
		break;
	case sinWP1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin38)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin32);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin33);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin37);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin17);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin11);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin12);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWP1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1051600);
		}
		break;
	case sinWS1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin39)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin33);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin37);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin38);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin20);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin11);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin12);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS1 | sin14);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1062a00);
		}
		break;
	case sinWS2:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin43)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin41);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin42);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin38);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin39);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin40);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin19);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin21);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin15);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWS2 | sin16);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1072b00);
		}
		break;
	case sinWT1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin38)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin01))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin32);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin02))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin33);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin03))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin04))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin05))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin06))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin37);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin20))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin17);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin21))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin22))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin23))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin11);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin24))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin12);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin25))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinWT1 | sin13);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin26))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x1081900);
		}
		break;
	case sinDS1:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin39)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin07))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin31);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin08))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin32);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin09))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin33);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin10))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin34);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin11))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin35);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin12))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin36);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin30))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin19);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin31))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin21);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin32))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin05);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin33))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin07);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin34))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin09);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin35))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDS1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin36))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (0x2040800);
		}
		break;
	case sinDA1:
	case sinDA3:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin29)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin13))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA3 | sin04);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin14))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA3 | sin05);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin15))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA3 | sin06);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin16))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA3 | sin07);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin17))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA3 | sin08);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin18))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA3 | sin09);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin40))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA1 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin41))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA1 | sin19);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin42))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA1 | sin08);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin43))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA1 | sin09);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin44))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA1 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin45))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA1 | sin11);
		}
		break;
	case sinDA2:
	case sinDA4:
		if ((pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) >= sin01 && (pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE & sinITEM_MASK3) <= sin29)
		{
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin13))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA4 | sin04);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin14))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA4 | sin05);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin15))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA4 | sin06);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin16))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA4 | sin07);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin17))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA4 | sin08);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin18))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA4 | sin09);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin40))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA2 | sin18);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin41))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA2 | sin19);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin42))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA2 | sin08);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin43))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA2 | sin09);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin44))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA2 | sin10);
			if (pRemodelItem_Server->dwRemodelStoneItemCode == (sinBI3 | sin45))
				pRemodelItem_Server->DesRemodelItem.sItemInfo.CODE = (sinDA2 | sin11);
		}
		break;
	}

	ccItem.sinRecvRemodelItem(pRemodelItem_Server);

	sRemodel_Recv.Result = TRUE;

	if (ErrorFlag)
		sRemodel_Recv.Result = FALSE;

	if (sRemodel_Recv.Result == TRUE)
	{
		ReformItem(&sRemodel_Recv.DesRemodelItem.sItemInfo);
		sRemodel_Recv.size = sizeof(sITEM) + 32;

		//rsRecord_RemodelItemLog(lpPlayInfo, pRemodelItem_Server, ITEMLOG_MIXTURE_RESET_LOST);

		rsAddInvenItem(lpPlayInfo, sRemodel_Recv.DesRemodelItem.sItemInfo.CODE,
			sRemodel_Recv.DesRemodelItem.sItemInfo.ItemHeader.Head,
			sRemodel_Recv.DesRemodelItem.sItemInfo.ItemHeader.dwChkSum);

		if (Stone)
		{
			rsPutItem(lpPlayInfo, Stone);
		}
		//rsRecord_ItemLog2(lpPlayInfo, sRemodel_Recv.DesRemodelItem.sItemInfo.CODE, sRemodel_Recv.DesRemodelItem.sItemInfo.ItemHeader.Head,
			//sRemodel_Recv.DesRemodelItem.sItemInfo.ItemHeader.dwChkSum, ITEMLOG_MIXTURE_RESET_GET);

		//RecordRemodelItem(lpPlayInfo, &sRemodel_Recv.DesRemodelItem.sItemInfo);
	}
	else
	{
		sRemodel_Recv.size = 32;
		//rsRecord_RemodelItemLog(lpPlayInfo, pRemodelItem_Server, ITEMLOG_MIXTURE_RESET_FAIL);
	}

	sRemodel_Recv.code = smTRANSCODE_REMODEL_ITEM;

	if (lpPlayInfo && lpPlayInfo->lpsmSock)
	{
		lpPlayInfo->lpsmSock->Send2((char*)&sRemodel_Recv, sRemodel_Recv.size, TRUE);
	}

	return TRUE;
}

int rsRecvWingItem(rsPLAYINFO* lpPlayInfo, sCRAFTITEM_SERVER* pCraftItem_Server)
{
	sITEMINFO	sItemInfo;
	smTRANS_COMMAND	smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	int cnt;
	int	ErrorFlag;
	int	PotionCount = 0;
	int result;
	int	Money;
	int	ForceMode = 0;

	ErrorFlag = 0;

	if (pCraftItem_Server->DesCraftItem.CODE == 1000)
		ForceMode = TRUE;

	if (ForceMode)
		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_LOST_ALCHMY);
	else

		rsRecord_ItemLost(lpPlayInfo, pCraftItem_Server->SheltomCode, pCraftItem_Server->Head, pCraftItem_Server->CheckSum, ITEMLOG_WINGLOST);

	for (cnt = 0; cnt < 12; cnt++) {
		if (pCraftItem_Server->SheltomCode[cnt]) {
			if (rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]) < 0) {
				smTransCommandEx.WParam = 8000;
				smTransCommandEx.WxParam = 50;
				smTransCommandEx.LxParam = (int)"*WING CRISTAL*";
				smTransCommandEx.LParam = pCraftItem_Server->SheltomCode[cnt];
				smTransCommandEx.SParam = pCraftItem_Server->Head[cnt];
				smTransCommandEx.EParam = pCraftItem_Server->CheckSum[cnt];
				RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
				ErrorFlag++;
			}

			SaveThrowItem(lpPlayInfo, pCraftItem_Server->SheltomCode[cnt],
				pCraftItem_Server->Head[cnt], pCraftItem_Server->CheckSum[cnt]);
		}
	}

	memcpy(&sItemInfo, &pCraftItem_Server->DesCraftItem.sItemInfo, sizeof(sITEMINFO));
	Money = pCraftItem_Server->Money;

	if (sItemInfo.CODE && CheckItemForm(&sItemInfo) == FALSE) {
		pCraftItem_Server->Result = FALSE;
		pCraftItem_Server->size = 32;
		if (lpPlayInfo && lpPlayInfo->lpsmSock) {
			lpPlayInfo->lpsmSock->Send2((char*)pCraftItem_Server, pCraftItem_Server->size, TRUE);
		}

		smTransCommand.WParam = 99000;
		smTransCommand.SParam = 1;
		smTransCommand.LParam = sItemInfo.CODE;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		return TRUE;
	}

	rsDeleteInvenItem(lpPlayInfo, pCraftItem_Server->DesCraftItem.sItemInfo.CODE,
		pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.Head,
		pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.dwChkSum);

	result = 0;

	if (!ErrorFlag)
		result = sinWingItemQuestServer(pCraftItem_Server, &lpPlayInfo->smCharInfo);
	else
		pCraftItem_Server->Result = FALSE;

	if (result == 0x100) {
		TRANS_ITEMINFO_GROUP	TransItemGroup;
		TRANS_ITEMINFO_GROUP2	TransItemGroup2;
		int cnt2, ItemCnt, LenSize;

		if (lpPlayInfo->ServerMoney >= Money) {
			lpPlayInfo->SubServerMoney(Money, WHERE_FORECORB);
			CurrencyLog.int64_ForceOrbMoney += Money;
		}
		else {
			smTransCommandEx.WParam = 8000;
			smTransCommandEx.WxParam = 50;
			smTransCommandEx.LxParam = (int)"*FORCE MONEY ERROR*";
			smTransCommandEx.LParam = (sinGG1 | sin01);
			smTransCommandEx.SParam = Money;
			smTransCommandEx.EParam = lpPlayInfo->ServerMoney;
			RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
			return FALSE;
		}

		ZeroMemory(&TransItemGroup2, sizeof(TRANS_ITEMINFO_GROUP2));

		ItemCnt = 0;

		for (cnt = 0; cnt < 14; cnt++) {
			if (pCraftItem_Server->SheltomCode[cnt]) {
				for (cnt2 = 0; cnt2 < DefaultItemCount; cnt2++) {
					if (DefaultItems[cnt2].Item.CODE == pCraftItem_Server->SheltomCode[cnt] && !DefaultItems[cnt2].Item.UniqueItem) {
						CreateDefItem(&TransItemGroup.sItemInfo[ItemCnt], &DefaultItems[cnt2]);

						rsAddInvenItem(lpPlayInfo, TransItemGroup.sItemInfo[ItemCnt].CODE,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.Head,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.dwChkSum);

						rsRecord_ItemLog2(lpPlayInfo,
							TransItemGroup.sItemInfo[ItemCnt].CODE,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.Head,
							TransItemGroup.sItemInfo[ItemCnt].ItemHeader.dwChkSum,
							ITEMLOG_GET_ALCHMY);

						ItemCnt++;
						break;
					}
				}
			}
		}

		LenSize = EecodeCompress((BYTE*)TransItemGroup.sItemInfo, (BYTE*)TransItemGroup2.szBuff, sizeof(sITEMINFO) * ItemCnt, sizeof(sITEMINFO) * TRANS_GROUPITEM_MAX);
		TransItemGroup2.ItemCount = ItemCnt;
		TransItemGroup2.Result = pCraftItem_Server->Result;
		TransItemGroup2.size = LenSize + TRANS_GROUPITEM_HEADER_SIZE;
		TransItemGroup2.code = smTRANSCODE_ITEM_FORCEORB;

		if (lpPlayInfo && lpPlayInfo->lpsmSock) {
			lpPlayInfo->lpsmSock->Send2((char*)&TransItemGroup2, TransItemGroup2.size, TRUE);
		}

		return TRUE;
	}

	if (pCraftItem_Server->Result == SIN_WINGRESULT_CRISTAL) {
		bSql_EventJoin(lpPlayInfo);
		pCraftItem_Server->Result = TRUE;
	}

	if (pCraftItem_Server->Result == TRUE && pCraftItem_Server->DesCraftItem.sItemInfo.CODE && !ErrorFlag) {
		if (pCraftItem_Server->DesCraftItem.sItemInfo.ItemKindCode == ITEM_KIND_QUEST_WEAPON) {
			for (cnt = 0; cnt < DefaultItemCount; cnt++) {
				if (DefaultItems[cnt].Item.CODE == pCraftItem_Server->DesCraftItem.sItemInfo.CODE && DefaultItems[cnt].Item.UniqueItem == ITEM_UNIQUE_CODE_QUEST) {
					CreateDefItem(&pCraftItem_Server->DesCraftItem.sItemInfo, &DefaultItems[cnt]);
					pCraftItem_Server->DesCraftItem.sItemInfo.ItemKindCode = ITEM_KIND_QUEST_WEAPON;
					SetChangeJob3QuestItem(&pCraftItem_Server->DesCraftItem.sItemInfo);
					break;
				}
			}
		}
		else {
			for (cnt = 0; cnt < DefaultItemCount; cnt++) {
				if (DefaultItems[cnt].Item.CODE == pCraftItem_Server->DesCraftItem.sItemInfo.CODE && !DefaultItems[cnt].Item.UniqueItem) {
					if (DefaultItems[cnt].sGenDay[0] && DefaultItems[cnt].sGenDay[1] >= DefaultItems[cnt].sGenDay[0]) {
						pCraftItem_Server->DesCraftItem.sItemInfo.CODE = (sinPM1 | sin04);
						pCraftItem_Server->DesCraftItem.sItemInfo.PotionCount = 30;

#ifdef	_TEST_SERVER
						if (lpPlayInfo->AdminMode) {
							TRANS_CHATMESSAGE	TransChatMessage;
							wsprintf(TransChatMessage.szMessage, "¿À´Ã ¹ß»ýÇÒ¼ö ÀÖ´Â ¾ÆÀÌÅÛ¼ö¸¦ ÃÊ°úÇß½À´Ï´Ù(%d/%d)",
								DefaultItems[cnt].sGenDay[1], DefaultItems[cnt].sGenDay[0]);

							TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
							TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
							TransChatMessage.dwIP = 0;
							TransChatMessage.dwObjectSerial = 0;

							lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
						}
#endif

						for (cnt = 0; cnt < DefaultItemCount; cnt++) {
							if (DefaultItems[cnt].Item.CODE == pCraftItem_Server->DesCraftItem.sItemInfo.CODE) {
								break;
							}
						}
						if (cnt >= DefaultItemCount)
							return FALSE;
					}

					DefaultItems[cnt].sGenDay[1]++;

					if ((DefaultItems[cnt].Item.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
						PotionCount = pCraftItem_Server->DesCraftItem.sItemInfo.PotionCount;
						CreateDefItem(&pCraftItem_Server->DesCraftItem.sItemInfo, &DefaultItems[cnt]);
						pCraftItem_Server->DesCraftItem.sItemInfo.PotionCount = PotionCount;

						rsAddServerPotion(lpPlayInfo, pCraftItem_Server->DesCraftItem.sItemInfo.CODE, PotionCount);
					}
					else {
						CreateDefItem(&pCraftItem_Server->DesCraftItem.sItemInfo, &DefaultItems[cnt], -1);
					}
					break;
				}
			}
		}
		if (cnt < DefaultItemCount) {
			ReformItem(&pCraftItem_Server->DesCraftItem.sItemInfo);

			rsAddInvenItem(lpPlayInfo, pCraftItem_Server->DesCraftItem.sItemInfo.CODE,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.Head,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.dwChkSum);

			rsRecord_ItemLog2(lpPlayInfo,
				pCraftItem_Server->DesCraftItem.sItemInfo.CODE,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.Head,
				pCraftItem_Server->DesCraftItem.sItemInfo.ItemHeader.dwChkSum,
				ITEMLOG_GETWING);

			pCraftItem_Server->size = sizeof(sCRAFTITEM_SERVER);
			if (lpPlayInfo && lpPlayInfo->lpsmSock) {
				lpPlayInfo->lpsmSock->Send2((char*)pCraftItem_Server, pCraftItem_Server->size, TRUE);
			}

			return TRUE;
		}
	}

	smTransCommand.WParam = 99000;
	smTransCommand.SParam = 1;
	smTransCommand.LParam = sItemInfo.CODE;
	RecordHackLogFile(lpPlayInfo, &smTransCommand);

	pCraftItem_Server->size = sizeof(sCRAFTITEM_SERVER);;
	pCraftItem_Server->Result = FALSE;

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		lpPlayInfo->lpsmSock->Send2((char*)pCraftItem_Server, pCraftItem_Server->size, TRUE);
	}

	return TRUE;
}

int	rsPlayHealing(smTRANS_COMMAND* lpTransCommand)
{
	smCHAR* lpChar;
	rsPLAYINFO* lpPlayInfo;

	lpChar = srFindCharFromSerial(lpTransCommand->SParam);
	if (lpChar) {
		if (lpChar && lpChar->smCharInfo.Life[0] > 0) {
			if (!lpChar->DontMoveFlag || lpChar->smCharInfo.dwCharSoundCode != snCHAR_SOUND_CASTLE_TOWER_B)
			{
#ifdef _LANGUAGE_PHILIPIN
				if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B
					)
					return TRUE;
#else

				if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR

					)
					return TRUE;
#endif

				lpChar->smCharInfo.Life[0] += lpTransCommand->WParam;
				if (lpChar->smCharInfo.Life[0] > lpChar->smCharInfo.Life[1])
					lpChar->smCharInfo.Life[0] = lpChar->smCharInfo.Life[1];
			}
		}
		return TRUE;
	}
	lpPlayInfo = srFindUserFromSerial(lpTransCommand->SParam);
	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		if (lpPlayInfo->dwSkill_VirtualLife_Time && lpPlayInfo->dwSkill_VirtualLife_Time > dwPlayServTime) {
			lpTransCommand->WParam -= (lpTransCommand->WParam * lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
		}

		lpPlayInfo->lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
		return TRUE;
	}

	return	FALSE;
}

int rsPlayGrandHealing(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	int cnt;
	rsPLAYINFO* lpPartyMaster;
	smTRANS_COMMAND	smTransCommand;

	if (lpPlayInfo->dwPartyInfo && lpPlayInfo->lpPartyMaster) {
		lpPartyMaster = lpPlayInfo->lpPartyMaster;

		memcpy(&smTransCommand, lpTransCommand, sizeof(smTRANS_COMMAND));

		for (cnt = 0; cnt < lpPartyMaster->PartyUserCount; cnt++) {
			if (lpPartyMaster->lpPartyPlayers[cnt] && lpPartyMaster->lpPartyPlayers[cnt]->lpsmSock) {
				if (lpPlayInfo != lpPartyMaster->lpPartyPlayers[cnt]) {
					if (lpPlayInfo->dwSkill_VirtualLife_Time && lpPlayInfo->dwSkill_VirtualLife_Time > dwPlayServTime) {
						smTransCommand.LParam = lpTransCommand->LParam;
						smTransCommand.LParam -= (lpTransCommand->LParam * lpPlayInfo->dwSkill_VirtualLife_Param) / 100;
						lpPartyMaster->lpPartyPlayers[cnt]->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
					}
					else {
						lpPartyMaster->lpPartyPlayers[cnt]->lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
					}
				}
			}
		}
	}

	return TRUE;
}

int	rsPlayWisp(smTRANS_COMMAND* lpTransCommand)
{
	smCHAR* lpChar;
	int time;
	int bio;

	lpChar = srFindCharFromSerial(lpTransCommand->SParam);
	if (lpChar)
	{
		lpChar->PlayWisp[0] = lpTransCommand->WParam;
		lpChar->PlayWisp[1] = lpTransCommand->LParam;
		return TRUE;
	}

	return FALSE;
}

int	rsPlayHolyMind(smTRANS_COMMAND* lpTransCommand)
{
	smCHAR* lpChar;
	int time;
	int bio;

	lpChar = srFindCharFromSerial(lpTransCommand->SParam);
	if (lpChar) {
		lpChar->PlayHolyMind[0] = lpTransCommand->WParam;
		lpChar->PlayHolyMind[1] = lpTransCommand->LParam;
		return TRUE;
	}

	return FALSE;
}

int rsCheck_ResulSOD(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommandEx)
{
	DWORD Code;

	Code = 0x3ea832ff;

	return Code & 0x7FFFFFFF;
}

int rsSend_ResultSOD(rsPLAYINFO* lpPlayInfo, int Point, int KillCount, int TotalPoint, int TotalSucessUser, int TotalUser, int SoDCode)
{
	smTRANS_COMMAND_EX	smTransCommand;

	smTransCommand.code = smTRANSCODE_SOD_RESULT;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = lpPlayInfo->smCharInfo.Level;
	smTransCommand.LParam = Point;
	smTransCommand.SParam = KillCount;
	smTransCommand.EParam = SoDCode;
	smTransCommand.WxParam = TotalPoint;
	smTransCommand.LxParam = TotalSucessUser;
	smTransCommand.SxParam = TotalUser;
	smTransCommand.ExParam = rsCheck_ResulSOD(lpPlayInfo, &smTransCommand);
	rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);

	return TRUE;
}

int rsCompAttackData(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	int avg1, avg2;
	smTRANS_COMMAND	smTransCommand;

	if (lpPlayInfo->Send_AttackCount > 255) {
		avg1 = lpPlayInfo->Send_AttackDamage / lpPlayInfo->Send_AttackCount;
		if (lpTransCommand->WParam)
			avg2 = (-lpTransCommand->LParam) / (-lpTransCommand->WParam);
		else
			avg2 = 0;

		if (avg1 > (((avg2 * 340) >> 8) + 16) && lpPlayInfo->WarningCount < 10) {
			smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 8110;
			smTransCommand.LParam = avg1;
			smTransCommand.SParam = avg2;
			smTransCommand.EParam = lpPlayInfo->Send_AttackCount;
			if (lpPlayInfo) {
				rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
			}
			lpPlayInfo->WarningCount++;
		}
	}

	return TRUE;
}

int CheckInvenItemPosition(rsPLAYINFO* lpPlayInfo, TRANS_USINGITEM* lpTransUsingItem)
{
	return TRUE;
}

int CheckInvenItemPosition2(rsPLAYINFO* lpPlayInfo, TRANS_USINGITEM* lpTransUsingItem)
{
	return TRUE;
}

int rsRecvRecordTradeItem(rsPLAYINFO* lpPlayInfo, TRANS_RECORD_TRADE_ITEMS* lpTransRecordTradeItems)
{
	return TRUE;
}

int rsCheckItemTempCode(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpItem)
{
	return FALSE;
}

int	rsSendItemInfoPerf(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int Aging)
{
	return TRUE;
}

int	rsCheckItemCode(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpItem)
{
	return TRUE;
}

int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommandEx)
{
	return	TRUE;
}

int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo, int NewItem)
{
	return	TRUE;
}

int	rsCheck_ItemSecCode(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum, int Money, DWORD dwSeCode_0, DWORD dwSeCode_1, DWORD dwSeCode_2, DWORD dwSeCode_3, int* pPotionCount)
{
	return	TRUE;
}

int rsRecvBuyShopItem(rsPLAYINFO* lpPlayInfo, TRANS_BUY_SHOPITEM* lpTransBuyShopItem)
{
	int money;

	int i = 0;
	bool realItem = FALSE;
	sDEF_ITEMINFO* lpDefItem = 0;

	if (lpPlayInfo->SellAttackItem && !realItem) {
		for (i = 0; i < 32; i++) {
			if (lpPlayInfo->SellAttackItem[i]) {
				lpDefItem = (sDEF_ITEMINFO*)lpPlayInfo->SellAttackItem[i];
				if (lpDefItem->Item.CODE == lpTransBuyShopItem->sItem.CODE) {
					realItem = TRUE;
					break;
				}
			}
		}
	}

	if (lpPlayInfo->SellDefenceItem && !realItem) {
		for (i = 0; i < 32; i++) {
			if (lpPlayInfo->SellDefenceItem[i]) {
				lpDefItem = (sDEF_ITEMINFO*)lpPlayInfo->SellDefenceItem[i];
				if (lpDefItem->Item.CODE == lpTransBuyShopItem->sItem.CODE) {
					realItem = TRUE;
					break;
				}
			}
		}
	}

	if (lpPlayInfo->SellEtcItem && !realItem) {
		for (i = 0; i < 32; i++) {
			if (lpPlayInfo->SellEtcItem[i]) {
				lpDefItem = (sDEF_ITEMINFO*)lpPlayInfo->SellEtcItem[i];
				if (lpDefItem->Item.CODE == lpTransBuyShopItem->sItem.CODE) {
					realItem = TRUE;
					break;
				}
			}
		}
	}

	if (!realItem) return FALSE;

	if (!rsServerConfig.ServerInventoryMode) {
		lpPlayInfo->ServerMoney = 90000000;
	}

	if (CheckItemForm(&lpTransBuyShopItem->sItem.sItemInfo) == TRUE &&
		lpTransBuyShopItem->sItem.sItemInfo.Price <= lpPlayInfo->ServerMoney &&
		lpTransBuyShopItem->sItem.sItemInfo.dwCreateTime == 0) {
		ReformItem(&lpTransBuyShopItem->sItem.sItemInfo);
		if (lpPlayInfo && lpPlayInfo->lpsmSock) {
			rsAddInvenItem(lpPlayInfo, lpTransBuyShopItem->sItem.sItemInfo.CODE,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.Head,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.dwChkSum);

			rsRecord_ItemLog(lpPlayInfo,
				lpTransBuyShopItem->sItem.sItemInfo.CODE,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.Head,
				lpTransBuyShopItem->sItem.sItemInfo.ItemHeader.dwChkSum,
				ITEMLOG_BUYSHOP);

			if (lpTransBuyShopItem->ItemCount > 0 && (lpTransBuyShopItem->sItem.sItemInfo.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
				money = lpTransBuyShopItem->sItem.sItemInfo.Price * lpTransBuyShopItem->ItemCount;
				lpPlayInfo->SubServerMoney(money, WHERE_BUY_POTION);
				rsAddServerPotion(lpPlayInfo, lpTransBuyShopItem->sItem.sItemInfo.CODE, lpTransBuyShopItem->ItemCount);

				switch ((lpTransBuyShopItem->sItem.sItemInfo.CODE & sinITEM_MASK2)) {
				case sinPL1:
					CurrencyLog.int64_ShopPotionMoney[0] += money;
					break;
				case sinPM1:
					CurrencyLog.int64_ShopPotionMoney[1] += money;
					break;
				case sinPS1:
					CurrencyLog.int64_ShopPotionMoney[2] += money;
					break;
				}
			}
			else {
				lpPlayInfo->SubServerMoney(lpTransBuyShopItem->sItem.sItemInfo.Price, WHERE_BUY_ITEM);
				CurrencyLog.int64_ShopMoney += lpTransBuyShopItem->sItem.sItemInfo.Price;
			}

			return lpPlayInfo->lpsmSock->Send2((char*)lpTransBuyShopItem, lpTransBuyShopItem->size, TRUE);
		}
	}

	if (lpTransBuyShopItem->sItem.sItemInfo.Price > lpPlayInfo->ServerMoney) {
		smTRANS_COMMAND	smTransCommand;

		smTransCommand.WParam = 8010;
		smTransCommand.LParam = 10;
		smTransCommand.SParam = lpPlayInfo->ServerMoney;
		smTransCommand.EParam = lpTransBuyShopItem->sItem.sItemInfo.Price;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);
	}

	return FALSE;
}

int rsRecvSellShopItem(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo)
{
	smTRANS_COMMAND		smTransCommand;
	smTRANS_COMMAND_EX	smTransCommandEx;

	float Dur[2];
	float Price;
	int	  Price2, PriceMax;
	int	  PriceDiv;

	if ((lpTransItemInfo->Item.CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1) || lpTransItemInfo->Item.CODE == (sinGF1 | sin01)) {
		return FALSE;
	}

	if (CheckItemForm(&lpTransItemInfo->Item) == FALSE) {
		smTransCommandEx.WParam = 8830;
		smTransCommandEx.LParam = lpTransItemInfo->Item.CODE;
		smTransCommandEx.SParam = lpTransItemInfo->Item.Price;
		smTransCommandEx.EParam = 0;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);

		return FALSE;
	}

	if (rsDeleteInvenItem(lpPlayInfo, lpTransItemInfo->Item.CODE,
		lpTransItemInfo->Item.ItemHeader.Head,
		lpTransItemInfo->Item.ItemHeader.dwChkSum) >= 0) {
		Dur[0] = lpTransItemInfo->Item.Durability[0];
		Dur[1] = lpTransItemInfo->Item.Durability[1];
		Price = (float)lpTransItemInfo->Item.Price;

		if (Dur[0] == 0)Dur[0] = 1;
		if (Dur[1] == 0)Dur[1] = 1;

#ifdef	_PLAY_MORYON
		PriceDiv = 5;
#else
		PriceDiv = 4;
#endif

		Price2 = (int)((Price * (Dur[0] / Dur[1])) + (Price - (Price * (Dur[0] / Dur[1]))) * 0.25);
		Price2 = Price2 / PriceDiv;
		PriceMax = lpTransItemInfo->Item.Price / PriceDiv;

		smTransCommand.code = smTRANSCODE_SHOP_SELLITEM;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpTransItemInfo->Item.CODE;
		smTransCommand.LParam = lpTransItemInfo->Item.ItemHeader.Head;
		smTransCommand.SParam = lpTransItemInfo->Item.ItemHeader.dwChkSum;

		if (PriceMax < Price2)
			smTransCommand.EParam = PriceMax;
		else
			smTransCommand.EParam = Price2;

		if (lpPlayInfo->lpsmSock) {
			lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
		}

		lpPlayInfo->UnsaveMoney = lpTransItemInfo->y - smTransCommand.EParam;
		lpPlayInfo->AddServerMoney(smTransCommand.EParam, WHERE_SELL_ITEM);

		SaveThrowItem(lpPlayInfo, lpTransItemInfo->Item.CODE,
			lpTransItemInfo->Item.ItemHeader.Head,
			lpTransItemInfo->Item.ItemHeader.dwChkSum);

		rsRecord_ItemLog(lpPlayInfo,
			lpTransItemInfo->Item.CODE,
			lpTransItemInfo->Item.ItemHeader.Head,
			lpTransItemInfo->Item.ItemHeader.dwChkSum,
			ITEMLOG_SELLSHOP);
	}
	else {
		smTransCommandEx.WParam = 8000;
		smTransCommandEx.WxParam = 10;
		smTransCommandEx.LxParam = (int)lpTransItemInfo->Item.ItemName;
		smTransCommandEx.LParam = lpTransItemInfo->Item.CODE;
		smTransCommandEx.SParam = lpTransItemInfo->Item.ItemHeader.Head;
		smTransCommandEx.EParam = lpTransItemInfo->Item.ItemHeader.dwChkSum;
		RecordHackLogFile(lpPlayInfo, &smTransCommandEx);
	}

	return TRUE;
}

int	rsCompareItems(sITEMINFO* lpItem1, sITEMINFO* lpItem2)
{
	if (lpItem1->CODE && lpItem1->CODE == lpItem2->CODE) {
		if (lpItem1->ItemHeader.dwTime == lpItem2->ItemHeader.dwTime &&
			lpItem1->ItemHeader.dwChkSum == lpItem2->ItemHeader.dwChkSum &&
			lpItem1->ItemHeader.Head == lpItem2->ItemHeader.Head) {
			return TRUE;
		}

		if (lpItem1->ItemHeader.dwChkSum == lpItem2->BackUpChkSum &&
			lpItem1->ItemHeader.Head == lpItem2->BackUpKey) {
			return TRUE;
		}

		if (lpItem2->ItemHeader.dwChkSum == lpItem1->BackUpChkSum &&
			lpItem2->ItemHeader.Head == lpItem1->BackUpKey) {
			return TRUE;
		}

		if (lpItem1->BackUpChkSum && lpItem1->BackUpKey &&
			lpItem2->BackUpChkSum == lpItem1->BackUpChkSum &&
			lpItem2->BackUpKey == lpItem1->BackUpKey) {
			return TRUE;
		}
	}

	return FALSE;
}

int rsCheckStgAreaItem(STG_AREA* lpStgArea, sITEMINFO* lpItem)
{
	int cnt;

	if (lpItem->CODE < sinPM1 && (lpItem->CODE & sinITEM_MASK3) >= sin08) {
		for (cnt = 0; cnt < STG_ITEM_MAX; cnt++) {
			if (lpStgArea->StgItems[cnt].state) {
				if (rsCompareItems(lpItem, &lpStgArea->StgItems[cnt].Item.ItemInfo) == TRUE) {
					lpStgArea->StgItems[cnt].state = 0;
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

int rsSendDataServer(smWINSOCK* lpsmSock, void* szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	if (!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND*)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_DATASERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send2((char*)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int rsSendGameServer(smWINSOCK* lpsmSock, void* szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	if (!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND*)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_GAMESERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send2((char*)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int rsSendAreaServer(smWINSOCK* lpsmSock, void* szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	if (!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND*)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AREASERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send2((char*)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int rsSendAGameServer(smWINSOCK* lpsmSock, void* szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	if (!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND*)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_SERVER;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send2((char*)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int rsSendAGameServer_PrimeItem2(smWINSOCK* lpsmSock, void* szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	if (!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND*)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send2((char*)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int rsSendAGameServer_PrimeItem3(smWINSOCK* lpsmSock, void* szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	if (!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND*)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send2((char*)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int rsSendAGameServer_PrimeItem4(smWINSOCK* lpsmSock, void* szData)
{
	TRANS_SEND_DATASERVER	TransSendDataServer;
	int size;

	if (!lpsmSock) return FALSE;

	size = ((smTRANS_COMMAND*)szData)->size;

	if (size > 4096 || size < 0) return FALSE;

	memcpy(TransSendDataServer.szBuff, szData, size);
	TransSendDataServer.code = smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4;
	TransSendDataServer.size = size + 16;

	return lpsmSock->Send2((char*)&TransSendDataServer, TransSendDataServer.size, TRUE);
}

int	rsCheckTotalExpMoney(rsPLAYINFO* lpPlayInfo, TRANS_TOTAL_EXPMONEY* TransTotalExpMoney)
{
	int Exp;
	int	ErrorFlag;
	smTRANS_COMMAND	smTransCommand;

	ErrorFlag = 0;

	Exp = TransTotalExpMoney->sServerExp.Total1 ^ TransTotalExpMoney->sServerExp.Total2;

	if (ErrorFlag) {
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommand.WParam = 6500;
		smTransCommand.LParam = TransTotalExpMoney->sServerExp.InputExp;
		smTransCommand.SParam = lpPlayInfo->spEXP_Out;
		smTransCommand.EParam = rsServerConfig.ServerCode;
		rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);

		if (!lpPlayInfo->dwHopeDisconnectTime) {
			lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime + 20 * 1000;
		}
	}

	lpPlayInfo->dwLastExpMoneyCheckTime = dwPlayServTime;

	return TRUE;
}

int rsSendGameServerExp(rsPLAYINFO* lpPlayInfo)
{
	return TRUE;
}

int rsRecvGameServerExp(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	return TRUE;
}

int rsReOpenEventMonster(STG_AREA* lpStgArea, smCHAR* lpChar)
{
	STG_CHAR_INFO StgCharInfo;
	int cnt;

	if (!lpChar->smMonsterInfo.EventCode || !lpStgArea) return FALSE;

	if (lpChar->smMonsterInfo.EventCode == 100 && !dwServ_NightDay)
		return FALSE;

	for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
		if (chrMonsterList[cnt].lpMonInfo->EventCode == lpChar->smMonsterInfo.EventCode &&
			chrMonsterList[cnt].lpMonInfo->EventInfo == lpChar->smMonsterInfo.EventInfo &&
			lstrcmp(chrMonsterList[cnt].szName, lpChar->smCharInfo.szName) == 0) {
			memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));
			lpStgArea->EvnMonster = TRUE;
			lpStgArea->OpenMonster(&StgCharInfo, 0);
			break;
		}
	}

	return TRUE;
}

int rsOpenEventMonster(int EventCode, int wParam, int lParam, int sParam)
{
	STG_CHAR_INFO StgCharInfo;
	STG_AREA* lpStgArea;

	int cnt;

	switch (EventCode) {
	case 100:
		for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
			if (chrMonsterList[cnt].lpMonInfo && chrMonsterList[cnt].lpMonInfo->EventCode == EventCode) {
				memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));

				lpStgArea = &StageArea[chrMonsterList[cnt].lpMonInfo->EventInfo];

				lpStgArea->EvnMonster = TRUE;
				lpStgArea->OpenMonster(&StgCharInfo, 0);
				lpStgArea->StartPosRandomize();
			}
		}
		break;

	case 110:

		break;
	}

	return FALSE;
}

int rsCloseEventMonster(int EventCode)
{
	int cnt;

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].smMonsterInfo.EventCode == EventCode) {
			if (chrAutoPlayer[cnt].MotionInfo->State != CHRMOTION_STATE_DEAD) {
				if (chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_WARP) == FALSE) {
					chrAutoPlayer[cnt].Close();
				}

				if (chrAutoPlayer[cnt].lpExt1) {
					((STG_AREA*)chrAutoPlayer[cnt].lpExt1)->MonsterCount--;
					((STG_AREA*)chrAutoPlayer[cnt].lpExt1)->DeleteMonTable(&chrAutoPlayer[cnt]);
				}
			}
			else {
				chrAutoPlayer[cnt].Close();
				if (chrAutoPlayer[cnt].lpExt1) {
					((STG_AREA*)chrAutoPlayer[cnt].lpExt1)->MonsterCount--;
					((STG_AREA*)chrAutoPlayer[cnt].lpExt1)->DeleteMonTable(&chrAutoPlayer[cnt]);
				}
			}
		}
	}

	return TRUE;
}

int SendToAll(char* Buff, int Size)
{
	for (int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (rsPlayInfo[cnt].lpsmSock)
		{
			rsPlayInfo[cnt].lpsmSock->Send(Buff, Size, TRUE);
		}
	}

	return TRUE;
}

int rsOpenBossMonster(STG_AREA* lpStgArea, sBOSS_MONSTER* lpBossMonster)
{
	if (lpStgArea && lpBossMonster && lpBossMonster->MasterMonster)
	{
		STG_CHAR_INFO StgCharInfo;
		int cnt;
		POINT3D	pos3D;
		smCHAR* lpChar;

		if (lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_BABEL &&
			lpStgArea->lpField)
		{
			if (dwBabelPlayTime > dwPlayServTime)
			{
				return FALSE;
			}

			if (lpStgArea->lpField->FieldCode == rsBABEL_FIELD)
			{
				pos3D.x = 50172 * fONE;
				pos3D.y = 0;
				pos3D.z = 13193 * fONE;
			}
			else
			{
				pos3D.x = 37086 * fONE;
				pos3D.y = 0;
				pos3D.z = 26425 * fONE;
			}

			lprsFixedPoint = &pos3D;
			BabelPlayField = lpStgArea->lpField->FieldCode;

			for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
			{
				if (lpStgArea->lpCharMonster[cnt])
				{
					if (lpStgArea->lpCharMonster[cnt]->Flag && lpStgArea->lpCharMonster[cnt]->MotionInfo->State != CHRMOTION_STATE_DEAD)
					{
						lpStgArea->lpCharMonster[cnt]->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
						lpStgArea->lpCharMonster[cnt]->PlayStunCount = 16 * 8;
					}
				}
			}
		}

		if (lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT &&
			lpStgArea->lpField && lpStgArea->lpField->FieldCode == 31)
		{
			pos3D.x = 34042 * fONE;
			pos3D.y = 0;
			pos3D.z = 36709 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_KELVEZU &&
			lpStgArea->lpField && lpStgArea->lpField->FieldCode == rsKELVEZU_FIELD)
		{
			pos3D.x = 33023 * fONE;
			pos3D.y = 0;
			pos3D.z = 52608 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_MOKOVA &&
			lpStgArea->lpField && lpStgArea->lpField->FieldCode == rsMOKOVA_FIELD)
		{
			pos3D.x = -12057 * fONE;
			pos3D.y = 0;
			pos3D.z = 13225 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpBossMonster->MasterMonster->dwCharSoundCode == snCHAR_SOUND_FURY &&
			lpStgArea->lpField && lpStgArea->lpField->FieldCode == 42)
		{
			pos3D.x = -872 * fONE;
			pos3D.y = 0;
			pos3D.z = -45168 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 21)
		{
			pos3D.x = 2145 * fONE;
			pos3D.y = 0;
			pos3D.z = 75664 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 35)
		{
			pos3D.x = 37975 * fONE;
			pos3D.y = 0;
			pos3D.z = 48525 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 37)
		{
			pos3D.x = -13771 * fONE;
			pos3D.y = 0;
			pos3D.z = -536 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 38)
		{
			pos3D.x = -11742 * fONE;
			pos3D.y = 0;
			pos3D.z = 9835 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 42)
		{
			pos3D.x = -3646 * fONE;
			pos3D.y = 0;
			pos3D.z = -46299 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 44)
		{
			pos3D.x = 19426 * fONE;
			pos3D.y = 0;
			pos3D.z = -36442 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 45)
		{
			pos3D.x = -12008 * fONE;
			pos3D.y = 0;
			pos3D.z = -59055 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 46)
		{
			pos3D.x = 12775 * fONE;
			pos3D.y = 0;
			pos3D.z = -57625 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 47)
		{
			pos3D.x = -22942 * fONE;
			pos3D.y = 0;
			pos3D.z = 5715 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 48)
		{
			pos3D.x = 198279 * fONE;
			pos3D.y = 0;
			pos3D.z = 242861 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 50)
		{
			pos3D.x = 27976 * fONE;
			pos3D.y = 0;
			pos3D.z = -67925 * fONE;
			lprsFixedPoint = &pos3D;
		}

		if (lpStgArea->lpField && lpStgArea->lpField->FieldCode == 51)
		{
			pos3D.x = -13030 * fONE;
			pos3D.y = 0;
			pos3D.z = 21711 * fONE;
			lprsFixedPoint = &pos3D;
		}

		Boss = dwPlayServTime + 60 * 1000 * 3;

		if (lpBossMonster->MasterMonster)
		{
			memcpy(&StgCharInfo.smCharInfo, lpBossMonster->MasterMonster, sizeof(smCHAR_INFO));
			lpStgArea->EvnMonster = TRUE;
			lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
			lpStgArea->StartPointCnt = lpStgArea->StartPointLastOpenCount;
		}

		if (lpBossMonster->SlaveMonster)
		{
			memcpy(&StgCharInfo.smCharInfo, lpBossMonster->SlaveMonster, sizeof(smCHAR_INFO));
			lpStgArea->EvnMonster = TRUE;
			lpStgArea->OpenMonster(&StgCharInfo, lpBossMonster->SlaveCount);
		}

		if (lprsFixedPoint)
		{
			lprsFixedPoint = 0;
			if (lpChar)
			{
				lpChar->lpAttackDamageList = new ATTACK_DAMAGE_LIST[ATTACK_DAMAGE_LIST_MAX];
				if (lpChar->lpAttackDamageList)
					ZeroMemory(lpChar->lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST) * ATTACK_DAMAGE_LIST_MAX);
			}
		}

		Boss = 0;

		char* ListMap[62] =
		{
			   "Mata das Acacias",
			   "Floresta Bamboo",
			   "Jardim da Liberdade",
			   "Ricarten",
			   "Refugio dos Ancioes",
			   "Castelo dos Perdidos",
			   "Ruinen",
			   "Terra Maldita",
			   "Terra Esquecida",
			   "Navisko",
				"Oasis",
				"C.B.A",
				"Terra Proibida",
				"Calabouco Antigo 1",
				"Calabouco Antigo 2",
				"Calabouco Antigo 3",
				"Salinha",
				"Floresta dos Espiritos",
				"Floresta das Ilusoes",
				"Vale Tranquilo",
				"Estrada dos Ventos",
				"Pillai",
				"Templo Maldito 1",
				"Templo Maldito 2",
				"Caverna dos Cogumelos",
				"Caverna das Abelhas",
				"Santuário Sombrio",
				"Estrada de Ferro",
				"Coracao de perum",
				"Eura",
				"Ultimo estagio do SOD",
				"Vale da Gallubia",
				"Quest Map",
				"Castelo Sagrado",
				"Lago da Ganancia",
				"Santuario Congelado",
				"Caverna Kelvezu",
				"Ilha Perdida",
				"Templo Perdido",
				"Bonus Stage",
				"Torre Sem Fim 1",
				"Torre Sem Fim 2",
				"Templo Maldito 3",
				"Torre Sem Fim 3",
				"Mina de Gelo",
				"Laboratorio Secreto",
				"Arma Secreta",
				"Abismo do Mar",
				"Abismo Carmesin",
				"Arena de Batalha",
				"Coração de Fogo",
				"Núcleo Congelado"
		};

		TRANS_CHATMESSAGE	TransChatMessage;
		TransChatMessage.size = sizeof(TRANS_CHATMESSAGE);
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;
		wsprintf(TransChatMessage.szMessage, "Boss> [%s] nasceu em [%s]!", lpBossMonster->MasterMonster->szName, ListMap[lpStgArea->lpField->FieldCode]);

		for (cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if (rsPlayInfo[cnt].lpsmSock && ListMap[lpStgArea->lpField->FieldCode] != nullptr)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
			}
		}

		//Alerta  na Tela
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.dwIP = 12;
		TransChatMessage.dwObjectSerial = 0;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

		for (cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if (rsPlayInfo[cnt].lpsmSock && ListMap[lpStgArea->lpField->FieldCode] != nullptr)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
			}
		}
	}

	return FALSE;
}

int	rsSendCommandUser(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommandEx)
{
	int cnt;
	int rx, rz, dist;
	int x, z;

	lpTransCommandEx->code = smTRANSCODE_COMMAND_USER;
	lpTransCommandEx->size = sizeof(smTRANS_COMMAND_EX);

	x = lpPlayInfo->Position.x;
	z = lpPlayInfo->Position.z;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial) {
			rx = (x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
			rz = (z - rsPlayInfo[cnt].Position.z) >> FLOATNS;
			dist = rx * rx + rz * rz;

			if (dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT) {
				rsPlayInfo[cnt].lpsmSock->Send((char*)lpTransCommandEx, lpTransCommandEx->size, TRUE);
			}
		}
	}

	return TRUE;
}

int	rsSendCommandUser2(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	int cnt;
	int rx, rz, dist;
	int x, z;

	x = lpPlayInfo->Position.x;
	z = lpPlayInfo->Position.z;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial) {
			rx = (x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
			rz = (z - rsPlayInfo[cnt].Position.z) >> FLOATNS;
			dist = rx * rx + rz * rz;

			if (dist < DIST_TRANSLEVEL_HIGH && abs(rx) < TRANS_VIEW_LIMIT && abs(rz) < TRANS_VIEW_LIMIT) {
				rsPlayInfo[cnt].lpsmSock->Send((char*)lpTransCommand, lpTransCommand->size, TRUE);
			}
		}
	}

	return TRUE;
}

static int rsCompString(char* src1, char* src2)
{
	int cnt;
	int len1, len2;
	int len;

	len1 = lstrlen(src1);
	len2 = lstrlen(src2);

	if (len1 < len2) len = len1;
	else len = len2;

	if (!len) return NULL;

	for (cnt = 0; cnt < len1; cnt++) {
		if (src1[cnt] == 0) break;
		if (src1[cnt] != src2[cnt]) return NULL;
	}

	return cnt;
}

char* rsGetWord(char* q, char* p)
{
	if (*p == 0) { *q = 0; return p; }

	while ((*p == 32) || (*p == 9) || (*p == 58))
	{
		p++;
	}

	while ((*p != 32) && (*p != 9) && (*p != 58) && (*p != 0))
	{
		if (*p == '\n' || *p == '\r') break;
		*q++ = *p++;
	}
	*q++ = 0;

	return p;
}

rsPLAYINFO* FindUserFromName(char* szName)
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].TransInfoFlag) {
			if (lstrcmpi(rsPlayInfo[cnt].smCharInfo.szName, szName) == 0) {
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}

rsPLAYINFO* FindUserFromName2(char* szName)
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock) {
			if (lstrcmpi(rsPlayInfo[cnt].szName, szName) == 0) {
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}

rsPLAYINFO* FindUserFromCode(DWORD dwUserCode)
{
	int cnt;

	if (dwUserCode) {
		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial == dwUserCode) {
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}

rsPLAYINFO* FindUserFromName3(char* szName)
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock) {
			if (rsPlayInfo[cnt].szName[0]) {
				if (lstrcmpi(rsPlayInfo[cnt].szName, szName) == 0) {
					return &rsPlayInfo[cnt];
				}
			}
			else {
				if (lstrcmpi(rsPlayInfo[cnt].smCharInfo.szName, szName) == 0) {
					return &rsPlayInfo[cnt];
				}
			}
		}
	}

	return NULL;
}

rsPLAYINFO* FindUserFromCodeName(char* szName, DWORD dwSpeedSum)
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock) {
			if (rsPlayInfo[cnt].dwCode_Name == dwSpeedSum && lstrcmpi(rsPlayInfo[cnt].szName, szName) == 0) {
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}

rsPLAYINFO* FindUserFromID(char* szID)
{
	int cnt;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szID[0]) {
			if (lstrcmpi(rsPlayInfo[cnt].szID, szID) == 0) {
				return &rsPlayInfo[cnt];
			}
		}
	}

	return NULL;
}

int CreatePresentItem(DWORD dwItemCode, STG_AREA* lpStgArea, int x, int y, int z, int count)
{
	psITEM			psItem;
	int				cnt;
	STG_ITEMS* lpStgItem;

	ZeroMemory(&psItem, sizeof(psITEM));

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem) {
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			psItem.state = TRUE;
			if ((psItem.ItemInfo.CODE & sinITEM_MASK2) == (sinPM1 & sinITEM_MASK2)) {
				psItem.ItemInfo.PotionCount = (rand() % count) + 1;
			}

			lpStgItem = lpStgArea->AddItem(&psItem, x >> FLOATNS, y >> FLOATNS, z >> FLOATNS, TRUE);
			lpStgItem->dwCreateTime += 5000;

			return TRUE;
		}
	}
	return FALSE;
}

int CreateCommandItem(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, char* szItem)
{
	psITEM* lpsItem;
	STG_AREA* lpStgArea;
	TRANS_ITEMINFO	TransItemInfo;
	char		szItemName[32];
	int cnt, cnt2, len;
	int val;

	val = FALSE;

	if (spJobCodeTime < dwPlayServTime) {
		spJobCode = 0;
		spItemNormal = 0;
		spJobCodeTime = 0;
	}

	if (spTimeAdjustTime < dwPlayServTime) {
		spTimeAdjustTime = 0;
		spTimeAdjust = 0;
	}

	if (lpPlayInfo->AdminMode < 4 && szItem[0] != '@') return FALSE;

	lpsItem = new psITEM;

	if (szItem[0] != '\"') {
		if (szItem[0] != '@') {
			if (srSetItemFromCode(lpsItem, szItem) == TRUE) {
				if (lpPlayInfo2) {
					if (lpPlayInfo2->lpsmSock) {
						TransItemInfo.code = smTRANSCODE_PUTITEM;
						TransItemInfo.size = sizeof(TRANS_ITEMINFO);
						memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));

						rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);

						lpPlayInfo2->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
						val = TRUE;
					}
				}
				else {
					lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);
					if (lpStgArea) {
						lpsItem->state = TRUE;
						lpStgArea->AddItem(lpsItem, lpPlayInfo->Position.x >> FLOATNS, lpPlayInfo->Position.y >> FLOATNS, lpPlayInfo->Position.z >> FLOATNS, TRUE);
						val = TRUE;
					}
				}
			}
		}
		else {
			if (srSetItemFromLogData(lpsItem, szItem + 1) == TRUE) {
				if (lpPlayInfo2) {
					if (lpPlayInfo2->lpsmSock) {
						TransItemInfo.code = smTRANSCODE_PUTITEM;
						TransItemInfo.size = sizeof(TRANS_ITEMINFO);
						memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
						rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
						lpPlayInfo2->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
						val = TRUE;
					}
				}
				else {
					lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);
					if (lpStgArea) {
						lpsItem->state = TRUE;
						lpStgArea->AddItem(lpsItem, lpPlayInfo->Position.x >> FLOATNS, lpPlayInfo->Position.y >> FLOATNS, lpPlayInfo->Position.z >> FLOATNS, TRUE);
						val = TRUE;
					}
				}
			}
		}
	}
	else {
		cnt2 = 0;
		len = lstrlen(szItem);
		for (cnt = 1; cnt < len; cnt++) {
			if (szItem[cnt] == '\"') { szItemName[cnt2] = 0; break; }
			szItemName[cnt2++] = szItem[cnt];
		}

		if (srSetItemFromName(lpsItem, szItemName) == TRUE) {
			if (lpPlayInfo2) {
				if (lpPlayInfo2->lpsmSock) {
					TransItemInfo.code = smTRANSCODE_PUTITEM;
					TransItemInfo.size = sizeof(TRANS_ITEMINFO);
					memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
					rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
					lpPlayInfo2->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
					val = TRUE;
				}
			}
			else {
				lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);
				if (lpStgArea) {
					lpsItem->state = TRUE;
					lpStgArea->AddItem(lpsItem, lpPlayInfo->Position.x >> FLOATNS, lpPlayInfo->Position.y >> FLOATNS, lpPlayInfo->Position.z >> FLOATNS, TRUE);
					val = TRUE;
				}
			}
		}
	}
	delete lpsItem;

	return val;
}

int rsPutItem_PointTicket(rsPLAYINFO* lpPlayInfo, int Price)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (DefaultItems[cnt].Item.CODE == (sinGF1 | sin01) && !DefaultItems[cnt].Item.UniqueItem) {
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			if (lpPlayInfo->lpsmSock) {
				TransItemInfo.code = smTRANSCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				TransItemInfo.Item.Price = Price;
				ReformItem(&TransItemInfo.Item);
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}

int rsCheck_ChageJob(rsPLAYINFO* lpPlayInfo, int NewCnageJob)
{
	DWORD	dwItemCode;
	psITEM	psItem;
	int cnt;

	if (lpPlayInfo->smCharInfo.ChangeJob == 1 && NewCnageJob == 2) {
		dwItemCode = sinOR2 | sin03;

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN || lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
			dwItemCode = sinOR2 | sin02;

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA || lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER)
			dwItemCode = sinOR2 | sin04;

		for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++) {
			if (lpPlayInfo->InvenItemInfo[cnt].dwCode == dwItemCode) return FALSE;
		}

		for (cnt = 0; cnt < DefaultItemCount; cnt++) {
			if (DefaultItems[cnt].Item.CODE == dwItemCode) {
				CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);
				psItem.ItemInfo.ItemKindCode = ITEM_KIND_QUEST_WEAPON;
				ReformItem(&psItem.ItemInfo);

				return rsPutItem2(lpPlayInfo, &psItem.ItemInfo);
			}
		}
	}

	return FALSE;
}

DWORD GetItemCode(char* szCode)
{
	DWORD dwCode = 0;
	for (int cnt = 0; cnt < MAX_ITEM; cnt++)
	{
		if (lstrcmpi(szCode, sItem[cnt].LastCategory) == 0)
		{
			dwCode = sItem[cnt].CODE; break;
		}
	}
	return dwCode;
}

void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec)
{
	psITEM* lpsItem;

	lpsItem = new psITEM;

	if (srSetItemFromCode(lpsItem, szCode) == TRUE)
	{
		TRANS_ITEMINFO		TransItemInfo;
		ReformItem(&lpsItem->ItemInfo);

		for (int cnt = 0; cnt < DefaultItemCount; cnt++)
		{
			if (DefaultItems[cnt].Item.CODE == lpsItem->ItemInfo.CODE && !DefaultItems[cnt].Item.UniqueItem)
			{
				CreateDefItemPerf(&lpsItem->ItemInfo, &DefaultItems[cnt], Spec);
			}
		}

		TransItemInfo.code = smTRANSCODE_PUTITEM;
		TransItemInfo.size = sizeof(TRANS_ITEMINFO);
		memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
		rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
		if (lpPlayInfo->lpsmSock)
			lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
	}
	spJobCode = 0;
	delete lpsItem;
}

int rsPutItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem) {
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			if (lpPlayInfo->lpsmSock) {
				TransItemInfo.code = smTRANSCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}

sDEF_ITEMINFO* PremioQuest(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int JobCodeItem = 0;
	int cnt;

	JobCodeItem = spJobCode;

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem) {
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt], JobCodeItem);

			if (lpPlayInfo->lpsmSock) {
				TransItemInfo.code = smTRANSCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return &DefaultItems[cnt];
		}
	}

	return NULL;
}

int rsPutItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int JobCodeItem = 0;
	int PotionCount = 0;

	if ((dwItemCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
	{
		PotionCount = spJobCode;
	}
	else
	{
		JobCodeItem = spJobCode;
	}

	for (cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if (DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt], JobCodeItem);

			psItem.ItemInfo.PotionCount = PotionCount;

			if (lpPlayInfo->lpsmSock)
			{
				TransItemInfo.code = smTRANSCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}

int rsPutItemUnique(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode, DWORD dwUniqueCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int JobCodeItem = 0;
	int PotionCount = 0;

	if ((dwItemCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
		PotionCount = spJobCode;
	}
	else {
		JobCodeItem = spJobCode;
	}

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (DefaultItems[cnt].Item.CODE == dwItemCode && DefaultItems[cnt].Item.UniqueItem == dwUniqueCode) {
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt], JobCodeItem);

			psItem.ItemInfo.PotionCount = PotionCount;

			if (lpPlayInfo->lpsmSock) {
				TransItemInfo.code = smTRANSCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}

sDEF_ITEMINFO* rsPutItem3(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;

	for (cnt = 0; cnt < DefaultItemCount; cnt++) {
		if (DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem) {
			CreateDefItem(&psItem.ItemInfo, &DefaultItems[cnt]);

			if (lpPlayInfo->lpsmSock) {
				TransItemInfo.code = smTRANSCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return &DefaultItems[cnt];
		}
	}

	return NULL;
}

int rsPutItem2(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpItem)
{
	TRANS_ITEMINFO	TransItemInfo;

	if (lpPlayInfo->lpsmSock) {
		TransItemInfo.code = smTRANSCODE_PUTITEM;
		TransItemInfo.size = sizeof(TRANS_ITEMINFO);
		memcpy(&TransItemInfo.Item, lpItem, sizeof(sITEMINFO));
		rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
		return lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
	}
	return FALSE;
}

int rsSendNetLog(rsPLAYINFO* lpPlayInfo) //ATAQUE PROXY
{
	return 0;
}

char* szAdminLogin = "»¡°£¸¶ÈÄ¶ó";
char* szAdminChar = "±è´ëÈ£¸¸¼¼";
char* szAdminMessage[4] = { 0,0,0,0 };
char* szAdminSucess[4] = { 0,0,0,0 };

int	InitCrackFinding()
{
	return TRUE;
}

int	SendFindCrack(smWINSOCK* lpsmSock)
{
	return TRUE;
}

int RecvCommand(rsPLAYINFO* lpPlayInfo, char* szChatCommand)
{
	return TRUE;
}

int SendQuickMessage(rsPLAYINFO* lpPlayInfo, char* szMessage)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "From> %s: %s", szAdminChar, szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	return TRUE;
}

int SendQuickMessage2(rsPLAYINFO* lpPlayInfo, char* szMessage)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	wsprintf(TransChatMessage.szMessage, "%s", szMessage);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	return TRUE;
}

void GetDateTime(char* pszDateTime)
{
	char szDate[9] = { 0 };
	char szTime[9] = { 0 };
	_strdate_s(szDate, 9);
	_strtime_s(szTime, 9);

	wsprintfA(pszDateTime, "%s %s", szDate, szTime);
}

int RecvMessage(smTHREADSOCK* SockInfo, PacketReceiving* p)
{
	return TRUE;
}

int MakePlayerList()
{
	int cnt;
	int ListCnt;

	PlayerCount = 0;
	ListCnt = 2;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (smWSock[cnt].sock) {
			ListBuff[ListCnt++] = smWSock[cnt].acc_sin.sin_addr.S_un.S_addr;
			PlayerCount++;
		}
	}

	ListBuff[0] = ListCnt * sizeof(DWORD);
	ListBuff[1] = smTRANSCODE_IPLIST;

	return ListBuff[0];
}

void DisplayMessage()
{
}

int Serv_ConnectPlayer(smWINSOCK* lpsmSock)
{
	for (int cnt = 0; cnt < CONNECTMAX; cnt++)
	{
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szID[0] == 0)
		{
			DisconnectUser(rsPlayInfo[cnt].lpsmSock);
			srRouteErrorCount++;
		}
	}

	EnterCriticalSection(&cSerSection);

	PlayerCount++;

	AddNewPlayInfo(lpsmSock);

	LeaveCriticalSection(&cSerSection);

	return TRUE;
}

int RecordSaveThrowData(rsPLAYINFO* lpPlayInfo)
{
	return TRUE;
}

int rsRecordCheckFile(rsPLAYINFO* lpPlayInfo)
{
	FILE* fp;
	char* lpBuff;
	char	szFile[64];
	int		result;
	smTRANS_COMMAND	smTransCommand;

	result = FALSE;

	if (!lpPlayInfo) return FALSE;
	if (!lpPlayInfo->lpRecordDataBuff || !lpPlayInfo->szID[0] || !lpPlayInfo->szName[0]) return FALSE;

	lpBuff = lpPlayInfo->lpRecordDataBuff;
	lpPlayInfo->lpRecordDataBuff = new char[sizeof(TRANS_RECORD_DATA)];
	if (lpPlayInfo->lpRecordDataBuff) {
		GetUserDataFile(lpPlayInfo->szName, szFile);
		fp = fopen(szFile, "rb");
		if (fp) {
			fread(lpPlayInfo->lpRecordDataBuff, sizeof(TRANS_RECORD_DATA), 1, fp);
			fclose(fp);

			if (((TRANS_RECORD_DATA*)lpPlayInfo->lpRecordDataBuff)->code &&
				((TRANS_RECORD_DATA*)lpPlayInfo->lpRecordDataBuff)->size > 0) {
				rsSaveThrowData(lpPlayInfo);

				rsRecordMemoryBuff_CheckInvenItem(lpPlayInfo);

				rsRecordMemoryBuffToFile(lpPlayInfo, lpPlayInfo->szName, lpPlayInfo->lpRecordDataBuff);

				smTransCommand.WParam = 8400;
				smTransCommand.LParam = ((TRANS_RECORD_DATA*)lpPlayInfo->lpRecordDataBuff)->size;
				smTransCommand.SParam = 0;
				smTransCommand.EParam = 0;
				RecordHackLogFile(lpPlayInfo, &smTransCommand);

				result = TRUE;
			}
		}
		delete	lpPlayInfo->lpRecordDataBuff;
	}
	lpPlayInfo->lpRecordDataBuff = lpBuff;

	return result;
}

int Serv_DisconnectPlayer(smWINSOCK* lpsmSock)
{
	rsPLAYINFO* tpInfo;
	int cnt;
	smTRANS_COMMAND	smTransCommand;

	if (!lpsmSock) return TRUE;

	if (!lpsmSock->sock) return TRUE;

	EnterCriticalSection(&cSerSection);

	PlayerCount--;

	tpInfo = (rsPLAYINFO*)lpsmSock->ExtData1;

	if (tpInfo)
	{
		HellGates::GetInstance()->OnClose(tpInfo);

		/*	smTRANS_CHAR_COMMAND ps3;
			ps3.size = sizeof(smTRANS_CHAR_COMMAND);
			ps3.code = smTRANSCODE_PLAYER_ACTION;
			ps3.WParam = 2;
			lstrcpy(ps3.szName, tpInfo->szName);

			for (int cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock)
				{
					rsPlayInfo[cnt].lpsmSock->Send((char*)&ps3, ps3.size, TRUE);
				}
			}*/
	}

	if (LoginServer && tpInfo) {
		dwServer_DebugMessage = 100;
		lstrcpy(szServer_DebugLastUserID, tpInfo->szID);
		lstrcpy(szServer_DebugLastUserName, tpInfo->szName);
	}
	Server_DebugCount = 100;

	if (tpInfo->lpRecordDataBuff && tpInfo->szID[0] && tpInfo->szName[0] &&
		((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->size > 0) {
		((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->smCharInfo.szName[31] = 0;
		if (lstrcmpi(((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->smCharInfo.szName, tpInfo->szName) == 0) {
			if (rsServerConfig.ServerInventoryMode) {
				Server_DebugCount = 101;

				rsSaveThrowData(tpInfo);
				Server_DebugCount = 102;

				rsRecordMemoryBuff_CheckInvenItem(tpInfo);
			}

			Server_DebugCount = 103;

			for (cnt = 0; cnt < 6; cnt++) {
				if (rsRecordMemoryBuffToFile(tpInfo, tpInfo->szName, tpInfo->lpRecordDataBuff) == TRUE) break;

				smTransCommand.WParam = 8080;
				smTransCommand.LParam = 1;
				smTransCommand.SParam = cnt;
				smTransCommand.EParam = ((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->size;
				RecordHackLogFile(tpInfo, &smTransCommand);
			}
			((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->size = 0;
		}
		else {
			smTRANS_COMMAND smTransCommand;
			smTransCommand.WParam = 10000;
			smTransCommand.LParam = (DWORD)tpInfo->smCharInfo.szName;
			smTransCommand.SParam = (DWORD)((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->smCharInfo.szName;
			RecordHackLogFile(tpInfo, &smTransCommand);
		}
	}
	else {
		rsRecordCheckFile(tpInfo);
	}

	Server_DebugCount = 104;

	tpInfo->DisconnectPartyUser();

	rsLogOut(tpInfo);

	tpInfo->lpsmSock = 0;
	if (tpInfo->lpAreaPlayInfo) {
		*tpInfo->lpAreaPlayInfo = 0;
		tpInfo->lpAreaPlayInfo = 0;
	}
	if (tpInfo->lpRecordBase) {
		delete tpInfo->lpRecordBase;
		tpInfo->lpRecordBase = 0;
	}
	if (tpInfo->lpPostBoxItem) {
		rsSavePostBox(tpInfo);
		delete	tpInfo->lpPostBoxItem;
		tpInfo->lpPostBoxItem = 0;
	}

	Server_DebugCount = 105;

	if ((tpInfo->ThrowItemCount > 0 || tpInfo->UnsaveMoney >= 0) && tpInfo->szName[0])
		RecordSaveThrowData(tpInfo);

	if (tpInfo->SystemLine) {
		rsDisconnectSystemLine(lpsmSock);
		if (tpInfo->SystemLine == 2)	rsSetSerToLoginLine();
	}

	Server_DebugCount = 190;

	LeaveCriticalSection(&cSerSection);

	return TRUE;
}

extern CRITICAL_SECTION	cSocketSection;

int DisconnectUser(smWINSOCK* lpsmSock)
{
	rsPLAYINFO* tpInfo;

	DWORD	dwExitCode;
	int SecFlag;
	int cnt;
	smTRANS_COMMAND	smTransCommand;

	if (!lpsmSock) return TRUE;

	if (!lpsmSock->sock) return TRUE;

	if (cSocketSection.OwningThread) SecFlag = FALSE;
	else SecFlag = TRUE;

	if (SecFlag) smEnterCSectionSocket();

	PlayerCount--;

	tpInfo = (rsPLAYINFO*)lpsmSock->ExtData1;

	if (tpInfo)
	{
		HellGates::GetInstance()->OnClose(tpInfo);

		smTRANS_CHAR_COMMAND ps3;
		ps3.size = sizeof(smTRANS_CHAR_COMMAND);
		ps3.code = smTRANSCODE_PLAYER_ACTION;
		ps3.WParam = 2;
		lstrcpy(ps3.szName, tpInfo->szName);

		for (int cnt = 0; cnt < CONNECTMAX; cnt++)
		{
			if (rsPlayInfo[cnt].lpsmSock)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char*)&ps3, ps3.size, TRUE);
			}
		}
	}

	if (LoginServer && tpInfo) {
		dwServer_DebugMessage = 200;
		lstrcpy(szServer_DebugLastUserID, tpInfo->szID);
		lstrcpy(szServer_DebugLastUserName, tpInfo->szName);
	}
	Server_DebugCount = 200;

	if (tpInfo && tpInfo->lpsmSock == lpsmSock) {
		if (tpInfo->lpRecordDataBuff && tpInfo->szID[0] && tpInfo->szName[0] &&
			((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->size > 0) {
			((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->smCharInfo.szName[31] = 0;

			if (lstrcmpi(((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->smCharInfo.szName, tpInfo->szName) == 0) {
				if (rsServerConfig.ServerInventoryMode) {
					Server_DebugCount = 201;

					rsSaveThrowData(tpInfo);

					Server_DebugCount = 202;

					rsRecordMemoryBuff_CheckInvenItem(tpInfo);
				}

				Server_DebugCount = 203;

				for (cnt = 0; cnt < 6; cnt++) {
					if (rsRecordMemoryBuffToFile(tpInfo, tpInfo->szName, tpInfo->lpRecordDataBuff) == TRUE) break;

					smTransCommand.WParam = 8080;
					smTransCommand.LParam = 2;
					smTransCommand.SParam = cnt;
					smTransCommand.EParam = ((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->size;
					RecordHackLogFile(tpInfo, &smTransCommand);
				}
				((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->size = 0;
			}
			else {
				smTRANS_COMMAND smTransCommand;
				smTransCommand.WParam = 10001;
				smTransCommand.LParam = (DWORD)tpInfo->smCharInfo.szName;
				smTransCommand.SParam = (DWORD)((TRANS_RECORD_DATA*)tpInfo->lpRecordDataBuff)->smCharInfo.szName;
				RecordHackLogFile(tpInfo, &smTransCommand);
			}
		}
		else {
			rsRecordCheckFile(tpInfo);
		}

		Server_DebugCount = 204;

		tpInfo->DisconnectPartyUser();

		rsLogOut(tpInfo);

		tpInfo->lpsmSock = 0;
		if (tpInfo->lpAreaPlayInfo) {
			*tpInfo->lpAreaPlayInfo = 0;
			tpInfo->lpAreaPlayInfo = 0;
		}
		if (tpInfo->lpRecordBase) {
			delete tpInfo->lpRecordBase;
			tpInfo->lpRecordBase = 0;
		}
		if (tpInfo->lpPostBoxItem) {
			rsSavePostBox(tpInfo);
			delete	tpInfo->lpPostBoxItem;
			tpInfo->lpPostBoxItem = 0;
		}

		Server_DebugCount = 205;

		if ((tpInfo->ThrowItemCount > 0 || tpInfo->UnsaveMoney >= 0) && tpInfo->szName[0])
			RecordSaveThrowData(tpInfo);

		if (tpInfo->SystemLine) {
			rsDisconnectSystemLine(lpsmSock);
			if (tpInfo->SystemLine == 2)	rsSetSerToLoginLine();
		}
	}

	Server_DebugCount = 290;

	closesocket(lpsmSock->sock);
	lpsmSock->sock = 0;

	if (SecFlag) smLeaveCSectionSocket();

	return TRUE;
}

int RecordShutdownLog(int LogCode, int LParam, int SParam)
{
	smTRANS_COMMAND smTransCommand;

	smTransCommand.WParam = LogCode;
	smTransCommand.LParam = LParam;
	smTransCommand.SParam = SParam;
	RecordHackLogFile(0, &smTransCommand);

	return TRUE;
}

DWORD dwTimeCounter = 0;

static LONG APIENTRY WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	int cnt;
	DWORD dwOldTime;

	switch (messg)
	{
	case WM_CREATE:
		hMsgTextWnd = CreateWindow("EDIT", "",
			WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY,
			16, 16,
			320 - 32, 240 - 32,
			hWnd, (HMENU)ID_MESSTEXT,
			hInst, NULL);

		MoveWindow(hMsgTextWnd, 16, 16, 320 - 32, 200 - 32, TRUE);
		ShowWindow(hMsgTextWnd, SW_SHOW);

		wsprintf(szMessageBuff, "System Initializing ( %d )", CONNECTMAX);

		SetWindowText(hMsgTextWnd, szMessageBuff);

		InitializeCriticalSection(&cSerSection);
		InitializeCriticalSection(&cOdbcSection);

		break;

	case SWM_MDISCONNECT:
		if (wParam)
			((smWINSOCK*)wParam)->CloseSocket();
		break;

	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		break;

	case WM_DESTROY:
		TrayIconClose();
		WSACleanup();
		PostQuitMessage(0);
		break;

	case 0x500:
		Update(*(double*)wParam);
		break;

	case WM_TIMER:

		dwOldTime = dwPlayServTime;

		if (dwOldTime > 0xFFFF0000 && dwPlayServTime < 0xFFFF) {
			rsShutDown();

			RecordShutdownLog(50000, dwOldTime, dwPlayServTime);
		}

		//srPlayMain();

		if ((dwTimeCounter & 0x1FF) == 0)
		{
			PlayerCount = 0;
			for (cnt = 0; cnt < CONNECTMAX; cnt++)
			{
				if (rsPlayInfo[cnt].lpsmSock)
				{
					PlayerCount++;
				}
			}

			DisplayMessage();
			EventMonsterTime();
			::time(&tServerTime);

			/*if ((dwTimeCounter & 0xFFF) == 0)
			{
				bSql_RecordCurrency();
			}*/
		}

		if ((dwTimeCounter & 0x7) == 0)
		{
			if ((dwTimeCounter & 0x3F) == 0)
			{
				rsTimeRecData();
			}
		}
		dwTimeCounter++;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_START:
		case ID_STOP:

			break;

		case ID_CONFIG:
			rsRefreshConfig();
			break;

		case ID_RELOAD_LIST:
			EnterCriticalSection(&cSerSection);
			rsLoadCopiedItemList();
			LeaveCriticalSection(&cSerSection);
			break;

		case ID_QUIT:
			if (!Quit) {
				EnterCriticalSection(&cSerSection);
				rsSaveCastleInfo();
				LeaveCriticalSection(&cSerSection);
			}
			Quit = 1;
			break;

		case ID_SHUTDOWN:

			rsShutDown();
			DisplayMessage();
			EnableMenuItem(GetMenu(hWnd), ID_SHUTDOWN, MF_GRAYED);
			break;

		case ID_VIEW_SERVERINFOMATION:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_UNCHECKED);
			Svr_DisplayMode = 0;
			DisplayMessage();
			break;

		case ID_VIEW_GAMEINFOMATION:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_UNCHECKED);
			Svr_DisplayMode = 1;
			DisplayMessage();
			break;

		case ID_VIEW_CONFIGURATION:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_CHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_UNCHECKED);
			Svr_DisplayMode = 2;
			DisplayMessage();
			break;

		case ID_VIEW_AREASERVER:
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_SERVERINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_GAMEINFOMATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_CONFIGURATION, MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), ID_VIEW_AREASERVER, MF_CHECKED);
			Svr_DisplayMode = 3;
			DisplayMessage();
			break;
		}
		break;

	case MYWM_NOTIFYICON:
		switch (lParam) {
		case WM_LBUTTONDBLCLK:
			ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
			break;
		case WM_RBUTTONDOWN:
			ShowWindow(hWnd, SW_HIDE);
			break;
		default:
			break;
		}
		break;

	case MYWM_USER_COUNT:

		return rsGetUserCounter(PlayerCount);

	default:
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;
	}
	return 0L;
}

DWORD WINAPI MyThread()
{
	HWND hWnd = hwnd;
	DWORD dwUpdateTimeInterval = 100;
	BOOL  ex = FALSE;

	LARGE_INTEGER liFrequency, liLastTick, liNewTick;
	double* fTime = new double;

	QueryPerformanceFrequency(&liFrequency);
	double dFrequency = (double)liFrequency.QuadPart;

	QueryPerformanceCounter(&liLastTick);
	while ((ex) == FALSE)
	{
		Sleep(dwUpdateTimeInterval);

		QueryPerformanceCounter(&liNewTick);
		(*fTime) = (((double)(liNewTick.QuadPart - liLastTick.QuadPart)) * 1000.0f) / dFrequency;
		liLastTick = liNewTick;

		SendMessageA(hwnd, 0x500, (WPARAM)fTime, (LPARAM)NULL);
	}

	delete fTime;

	return TRUE;
}

INT WINAPI ServerWinMain(HINSTANCE hInst, HINSTANCE hPreInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MSG Msg;

	if (!SQL::GetInstance()->Connect("PTL\\SQLEXPRESS", "sa", "#$pdl32xq"))
		ExitProcess(0);

	SetupDefWindow(hInst, hPreInst, lpCmdLine, nCmdShow);

	HANDLE hThread = CreateThread(NULL, 2 * 1024, (LPTHREAD_START_ROUTINE)MyThread, 0, STACK_SIZE_PARAM_IS_A_RESERVATION, NULL);

	while (1)
	{
		if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);

			if (Msg.message == WM_QUIT)	break;
			if (Quit != 0) break;
		}
		else {
			WaitMessage();
		}
	}

	rsSaveCastleInfo();

	if (fpNetLog) fclose(fpNetLog);

	quit = 1;

	bSql_ServerExit();

	TrayIconClose();
	CloseBindSock();

	RemoveAll();

	return Msg.wParam;
}

void TrayIconCreat()
{
	NOTIFYICONDATA tnd;
	HICON hIcon;

	tnd.cbSize = sizeof(NOTIFYICONDATA);

	tnd.hWnd = hwnd;
	tnd.uID = 99;
	tnd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	tnd.uCallbackMessage = MYWM_NOTIFYICON;

	hIcon = (HICON)LoadIcon(hInst, MAKEINTRESOURCE(IDI_SERVER_ICON));

	tnd.hIcon = hIcon;
	strcpy(tnd.szTip, "È£¶± °ÔÀÓ È£½ºÆ®");

	Shell_NotifyIcon(NIM_ADD, &tnd);

	if (hIcon)
		DestroyIcon(hIcon);
}

void TrayIconClose() {
	NOTIFYICONDATA tnd;

	tnd.cbSize = sizeof(NOTIFYICONDATA);
	tnd.hWnd = hwnd;

	tnd.uID = 99;
	Shell_NotifyIcon(NIM_DELETE, &tnd);
}

struct LOGACCOUNT_INFO {
	rsPLAYINFO* lpPlayInfo;
	DWORD		dwConnectCount;
	char		szID[256];
	char		szPassword[256];
	char		szIP[16];
	char		szMac[20];
	int			Flag;
};

LOGACCOUNT_INFO	aLogAccount;

HANDLE hLogAccountThread = 0;
DWORD dwLogAccountThreadId = 0;

#define URS_LOG_THREAD_MAX		4
HANDLE hUrsLogAccountThread[URS_LOG_THREAD_MAX];
DWORD dwUrsLogAccountThreadId[URS_LOG_THREAD_MAX];
DWORD	hUrsMutiThreadFlag = 0;

#define LOG_ACCOUNT_QUE_MAX		64
#define LOG_ACCOUNT_QUE_MASK	63

LOGACCOUNT_INFO	LogAccountQue[LOG_ACCOUNT_QUE_MAX * 2];
int	PushLogAccountQue = 0;
int	PopLogAccountQue = 0;

int rsGetLogOnQueCount()
{
	return PushLogAccountQue - PopLogAccountQue;
}

int PushLogAccount(rsPLAYINFO* lpPlayInfo, char* szID, char* szPassword, char* szIP, char* szMac)
{
	int cnt;
	int	que;

	cnt = PushLogAccountQue & LOG_ACCOUNT_QUE_MASK;
	que = PushLogAccountQue - PopLogAccountQue;

	if (que >= LOG_ACCOUNT_QUE_MAX) {
		if (hUrsMutiThreadFlag) {
			for (cnt = 0; cnt < URS_LOG_THREAD_MAX; cnt++) {
				if (hUrsLogAccountThread[cnt])
					ResumeThread(hUrsLogAccountThread[cnt]);
			}
		}
		else {
			ResumeThread(hLogAccountThread);
		}
		return FALSE;
	}

	LogAccountQue[cnt].lpPlayInfo = lpPlayInfo;
	LogAccountQue[cnt].dwConnectCount = lpPlayInfo->dwConnectCount;
	lstrcpy(LogAccountQue[cnt].szID, szID);
	lstrcpy(LogAccountQue[cnt].szPassword, szPassword);
	lstrcpy(LogAccountQue[cnt].szIP, szIP);
	lstrcpy(LogAccountQue[cnt].szMac, szMac);
	LogAccountQue[cnt].Flag = 0;

	PushLogAccountQue++;

	if (hUrsMutiThreadFlag) {
		for (cnt = 0; cnt < URS_LOG_THREAD_MAX; cnt++) {
			if (hUrsLogAccountThread[cnt])
				ResumeThread(hUrsLogAccountThread[cnt]);
		}
	}
	else {
		ResumeThread(hLogAccountThread);
	}

	return	TRUE;
}

LOGACCOUNT_INFO* PopLogAccount()
{
	int cnt;
	int que;

	cnt = PopLogAccountQue & LOG_ACCOUNT_QUE_MASK;
	que = PushLogAccountQue - PopLogAccountQue;
	if (que <= 0) return NULL;
	PopLogAccountQue++;

	return &LogAccountQue[cnt];
}

int		Th_Record_PCJungFlag = -1;
HANDLE	hRecord_PCJung_Thread = 0;

DWORD WINAPI RecordPCJung_Thread(void* pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	DWORD	dwLastTime;
	int cnt;
	JUNGIP	Record_PcJungIP;
	JUNGIP	Record_PcJungIP2;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	dwLastTime = dwTime;

	while (1) {
		if (rsServerConfig.Disable_LogIn != 2) {
			EnterCriticalSection(&cSerSection);

			Record_PcJungIP.IPCount = 0;
			Record_PcJungIP2.IPCount = 0;

			for (cnt = 0; cnt < CONNECTMAX; cnt++) {
				if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].szID[0] &&
					rsPlayInfo[cnt].GpType == 1) {
					if (rsPlayInfo[cnt].GpCode == 0) {
						if (Record_PcJungIP.IPCount < JUNGIP_MAX) {
							Record_PcJungIP.IP[Record_PcJungIP.IPCount++] =
								rsPlayInfo[cnt].lpsmSock->acc_sin.sin_addr.S_un.S_addr;
						}
					}
					if (rsPlayInfo[cnt].GpCode == 1) {
						if (Record_PcJungIP2.IPCount < JUNGIP_MAX) {
							Record_PcJungIP2.IP[Record_PcJungIP2.IPCount++] =
								rsPlayInfo[cnt].lpsmSock->acc_sin.sin_addr.S_un.S_addr;
						}
					}
				}
			}
			LeaveCriticalSection(&cSerSection);

			if (Record_PcJungIP.IPCount) {
				b_IPRecord(rsServerConfig.szServerName, &Record_PcJungIP);
			}

			if (Record_PcJungIP2.IPCount) {
				b_IPRecordTime(rsServerConfig.szServerName, &Record_PcJungIP2);
			}
		}

		Sleep(1000 * 60 * 2);
	}

	ExitThread(TRUE);
	return TRUE;
}

int OpenRecordPCJung_Thread()
{
	DWORD	dwRecordPCJungThreadID;

	if (!hRecord_PCJung_Thread) {
		hRecord_PCJung_Thread = CreateThread(NULL, 0, RecordPCJung_Thread, 0, 0, &dwRecordPCJungThreadID);
	}

	return TRUE;
}

DWORD WINAPI LogAccountThreadProc(void* pInfo)
{
	int val = 0;
	return val;
}

int rsLogAccount(rsPLAYINFO* lpPlayInfo, char* szID, char* szPassword, char* szMac, char* szPath, char* szPCName)
{
	//Log do Login
	{
		if (SQL::GetInstance()->IsConnected())
		{
			SQL::GetInstance()->EnterSqlSection();
			char szQuery[512];
			wsprintf(szQuery, "INSERT INTO [PristonDB].[dbo].[AccountLogin] ([Account],[Password],[IP],[MacAddress],[Path],[PCName],[Date]) values('%s','%s','%s','%s','%s','%s',GETDATE())", szID, szPassword, lpPlayInfo->lpsmSock->szIPAddr, szMac, szPath, szPCName);
			SQL::GetInstance()->Execute(szQuery);
			SQL::GetInstance()->LeaveSqlSection();
		}
	}

	if (!hLogAccountThread) {
		hLogAccountThread = CreateThread(NULL, 0, LogAccountThreadProc, 0, 0, &dwLogAccountThreadId);
		SetThreadPriority(hLogAccountThread, THREAD_PRIORITY_ABOVE_NORMAL);

		CreateDataServerDirectory();

		LoginServer = TRUE;

		if (!rsBlessCastle.CastleMode) rsLoadCastleInfo();
	}

	if (!hLogAccountThread) return FALSE;

	if (lpPlayInfo->lpsmSock)
		return PushLogAccount(lpPlayInfo, szID, szPassword, lpPlayInfo->lpsmSock->szIPAddr, szMac);
	else
		return FALSE;
}

int rsSendServerList(smWINSOCK* lpsmSock, int ClanTicket)
{
	if (!TransServerList.ServerCount) return FALSE;

	if (!TransServerList.code) {
		TransServerList.code = smTRANSCODE_SERVER_INFO;
		TransServerList.size = sizeof(TRANS_SERVER_LIST) -
			(sizeof(_TRANS_SERVER_INFO) * (TRANS_SERVER_MAX - (TransServerList.ServerCount + TransServerList.ClanServerCount)));
	}

	TransServerList.dwServerTime_t = tServerTime;
	TransServerList.ClanTicket = ClanTicket;

	return lpsmSock->Send2((char*)&TransServerList, TransServerList.size, TRUE);
}

int rsCheckChildServer(char* szIP)
{
	int cnt;

	for (cnt = 0; cnt < TransServerList.ServerCount; cnt++) {
		if (TransServerList.ServerInfo[cnt].szServerIp1[0]) {
			if (lstrcmp(szIP, TransServerList.ServerInfo[cnt].szServerIp1) == 0)
				return TRUE;
		}
		if (TransServerList.ServerInfo[cnt].szServerIp2[0]) {
			if (lstrcmp(szIP, TransServerList.ServerInfo[cnt].szServerIp2) == 0)
				return TRUE;
		}
		if (TransServerList.ServerInfo[cnt].szServerIp3[0]) {
			if (lstrcmp(szIP, TransServerList.ServerInfo[cnt].szServerIp3) == 0)
				return TRUE;
		}
	}

	return FALSE;
}

#define		SERVER_DOWN_MIN			8

DWORD WINAPI ShutDownThreadProc(void* pInfo)
{
	int cnt;

	TRANS_CHATMESSAGE	TransChatMessage;
	smTRANS_COMMAND		smTransCommand;
	int	rsServerDownCount = 0;
	DWORD	dwShutDownTime = GetCurrentTime() + 60 * 1000 * SERVER_DOWN_MIN;

	DWORD	dwTime;
	int		Sec, Min;
	int		SleepTime;

	bSql_ServerDown();

	while (1) {
		if (Quit) {
			ExitThread(TRUE);
			return TRUE;
		}

		dwTime = GetCurrentTime();
		Sec = (dwShutDownTime - dwTime);
		Sec /= 1000;
		if (Sec < 0) {
			break;
		}

		Min = Sec / 60;
		Sec = Sec % 60;
		ShutDownLeftTime = Min;

		if (rsServerDownCount < SERVER_DOWN_MSG_COUNT) {
			lstrcpy(TransChatMessage.szMessage, szServerDownMsg[rsServerDownCount]);
			rsServerDownCount++;
			Sleep(500);
		}
		else {
			wsprintf(TransChatMessage.szMessage, szSeverDownCountMsg, Min, Sec);
			if (Min == 0)
				Sleep(1000 * 5);
			else
				Sleep(1000 * 30);
		}

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.dwIP = 3;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwObjectSerial = 0;

		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			SleepTime = 0;
			EnterCriticalSection(&cSerSection);
			if (rsPlayInfo[cnt].lpsmSock) {
				rsPlayInfo[cnt].lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
				SleepTime = 5;
			}
			LeaveCriticalSection(&cSerSection);
			if (SleepTime > 0) Sleep(SleepTime);
			if (Quit) {
				ExitThread(TRUE);
				return TRUE;
			}
		}
	}

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		SleepTime = 0;
		EnterCriticalSection(&cSerSection);
		if (rsPlayInfo[cnt].lpsmSock) {
			smTransCommand.code = smTRANSCODE_CLOSECLIENT;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			rsPlayInfo[cnt].lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
			SleepTime = 5;
		}
		LeaveCriticalSection(&cSerSection);
		if (SleepTime > 0) Sleep(SleepTime);
		if (Quit) {
			ExitThread(TRUE);
			return TRUE;
		}
	}

	Sleep(1000 * 60);

	Quit = 1;

	ExitThread(TRUE);

	return TRUE;
}

HANDLE hShutDownThread = 0;
DWORD dwShutDownThreadId = 0;

int	rsShutDown()
{
	if (!hShutDownThread) {
		hShutDownThread = CreateThread(NULL, 0, ShutDownThreadProc, 0, 0, &dwShutDownThreadId);
		ShutDownFlag = TRUE;
		ShutDownLeftTime = SERVER_DOWN_MIN;

		RecordShutdownLog(50010, 0, 0);
		return TRUE;
	}

	return FALSE;
}

#ifdef	_LANGUAGE_KOREAN
#include "serverlog.h"
#else
#include "e_serverlog.h"
#endif

int	rsSendTransCommand(rsPLAYINFO* lpPlayInfo, DWORD	dwCode, int WParam, int LParam, int SParam, int EParam)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = dwCode;
	smTransCommand.WParam = WParam;
	smTransCommand.LParam = LParam;
	smTransCommand.SParam = SParam;
	smTransCommand.EParam = EParam;

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		return lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return FALSE;
}

int RecordHackLogFile(rsPLAYINFO* lpPlayInfo, void* lpBuff)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	smTRANS_COMMAND_EX* lpTransCommand = (smTRANS_COMMAND_EX*)lpBuff;

#ifndef	_NEW_ITEM_FORMCODE

	if (lpTransCommand->WParam == 6800) {
		return FALSE;
	}
#endif

#ifdef	_LANGUAGE_KOREAN
#ifndef _TEST_SERVER
	if (lpTransCommand->WParam == 7100) {
		return FALSE;
	}
#endif
#endif

	GetLocalTime(&st);
	wsprintf(szFileName, filenameHack, HackLogDirectory, st.wMonth, st.wDay);

	if (lpPlayInfo && lpPlayInfo->lpsmSock) {
		lpPlayInfo->szID[31] = 0; lpPlayInfo->szName[31] = 0;
		wsprintf(szBuff, "%d:%d:%d IP-( %s ) ID-( %s ) Name-( %s ) / ( %d ) - ( %d , %d )\r\n",
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->szID, lpPlayInfo->szName,
			lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
	}
	else {
		wsprintf(szBuff, "%d:%d:%d ( %d ) - ( %d , %d )\r\n", st.wHour, st.wMinute, st.wSecond, lpTransCommand->WParam, lpTransCommand->LParam, lpTransCommand->SParam);
	}

	CreateDirectory(HackLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	if (lpPlayInfo) lpPlayInfo->WarningCount++;

	return TRUE;
}

int RecordDebugPlayLogFile(rsPLAYINFO* lpPlayInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDebugLogin, DebugLogDirectory, st.wMonth, st.wDay);

	if (lpPlayInfo->szID[0]) {
		wsprintf(szBuff, msgDebugloginID,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
			lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->AdminMode);
	}
	else {
		wsprintf(szBuff, msgDebugloginIP,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->smCharInfo.szName,
			lpPlayInfo->lpsmSock->szIPAddr, lpPlayInfo->AdminMode);
	}

	CreateDirectory(DebugLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordJobChanger(rsPLAYINFO* lpPlayInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Àü¾÷)%d¿ù%dÀÏ.log", st.wMonth, st.wDay);

	wsprintf(szBuff, "ID( %s ) Name( %s ) IP( %s ) - Á÷¾÷( %d )/Àü¾÷( %d )/·¹º§( %d )\r\n",
		lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->lpsmSock->szIPAddr,
		lpPlayInfo->smCharInfo.JOB_CODE, lpPlayInfo->smCharInfo.ChangeJob, lpPlayInfo->smCharInfo.Level);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int Record_TempLogFile(char* szMessage)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	int len;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Temp)%d-%d.log", st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	wsprintf(szBuff, "%d:%d:%d - %s", st.wHour, st.wMinute, st.wSecond, szMessage);
	len = lstrlen(szBuff);
	if (szBuff[len - 1] != '\n') {
		szBuff[len] = '\r';
		szBuff[len + 1] = '\n';
		len += 2;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int Record_BillingLogFile(rsPLAYINFO* lpPlayInfo, DWORD wParam, DWORD lParam, DWORD sParam, DWORD eParam)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo || !lpPlayInfo->lpsmSock) return FALSE;

	lpPlayInfo->szID[31] = 0; lpPlayInfo->szName[31] = 0;

	GetLocalTime(&st);
	wsprintf(szFileName, "LogFile\\(Billing)%d-%d.log", st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) - DisuseDay(%d) dwPeriodTime(%d) tTime(%d) PcUse(%d)\r\n", st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->lpsmSock->szIPAddr, wParam, lParam, sParam, eParam);

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int Record_DeadUser(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock || lpPlayInfo->smCharInfo.Level < 30) return FALSE;

	GetLocalTime(&st);
#ifdef _LANGUAGE_KOREAN
	wsprintf(szFileName, "LogFile\\(Death)%d¿ù%dÀÏ.log", st.wMonth, st.wDay);
#else
	wsprintf(szFileName, "LogFile\\(Death)%d-%d.log", st.wMonth, st.wDay);
#endif

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) - Level( %d )/Area( %d )\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->lpsmSock->szIPAddr,
		lpPlayInfo->smCharInfo.Level, lpPlayInfo->Position.Area);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordMixItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpSrcItem, sITEMINFO* lpMixItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMixItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgMixItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
		lpPlayInfo->lpsmSock->szIPAddr, lpSrcItem->ItemName,
		lpSrcItem->ItemHeader.Head, lpSrcItem->ItemHeader.dwChkSum, lpSrcItem->ItemHeader.dwTime,
		lpMixItem->ItemHeader.Head, lpMixItem->ItemHeader.dwChkSum, lpMixItem->ItemHeader.dwTime);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordAgingItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpSrcItem, sITEMINFO* lpMixItem, int Mode)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	char* lpMsg;
	TRANS_CHATMESSAGE TransChatMessage;
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;

	if (!lpPlayInfo->lpsmSock) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameAgingItem, HackLogDirectory, st.wMonth, st.wDay);

	if (lpMixItem) {
		if (!Mode) lpMsg = msgAgingItem;
		else lpMsg = msgAgingUpItem;

		wsprintf(szBuff, lpMsg,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
			lpPlayInfo->lpsmSock->szIPAddr, lpSrcItem->ItemName, lpMixItem->ItemAgingNum[0],
			lpSrcItem->ItemHeader.Head, lpSrcItem->ItemHeader.dwChkSum, lpSrcItem->ItemHeader.dwTime,
			lpMixItem->ItemHeader.Head, lpMixItem->ItemHeader.dwChkSum, lpMixItem->ItemHeader.dwTime);

		/*if (!Mode)
		{
			wsprintf(TransChatMessage.szMessage, "Melisandre: %s envelheceu (%s) para o [+%d] com sucesso! Parabéns!", lpPlayInfo->szName, lpSrcItem->ItemName, lpMixItem->ItemAgingNum[0]);
		}*/
	}
	else
	{
		wsprintf(szBuff, msgAgingFailItem,
			st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
			lpPlayInfo->lpsmSock->szIPAddr, lpSrcItem->ItemName, lpSrcItem->ItemAgingNum[0],
			lpSrcItem->ItemHeader.Head, lpSrcItem->ItemHeader.dwChkSum, lpSrcItem->ItemHeader.dwTime);

		//wsprintf(TransChatMessage.szMessage, "Moriph: %s quebrou (%s) no [+%d], Mais sorte na próxima vez!", lpPlayInfo->szName, lpSrcItem->ItemName, lpSrcItem->ItemAgingNum[0]);
		cRestaure.InsertAgingFailed(lpPlayInfo, lpSrcItem->ItemName, lpSrcItem->ItemAgingNum[0], lpSrcItem->ItemHeader.Head, lpSrcItem->ItemHeader.dwChkSum);
	}

	if ((lpMixItem && lpMixItem->ItemAgingNum[0] >= 15) || lpSrcItem->ItemAgingNum[0] >= 15)
	{
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;
		//SendToAll((char*)&TransChatMessage, TransChatMessage.size);
	}

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

char* szRecordCollectDirectory = "CollMoney";

int RecordCollectMoney(rsPLAYINFO* lpPlayInfo, int Money)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		TotalMoney = 0;
	FILE* fp;

	CreateDirectory(szRecordCollectDirectory, NULL);
	GetLocalTime(&st);

	wsprintf(szFileName, filenameCollectMoney, szRecordCollectDirectory, st.wMonth, st.wDay);

	fp = fopen(szFileName, "rb");
	if (fp) {
		fread(szBuff, 256, 1, fp);
		fclose(fp);
		TotalMoney = atoi(szBuff);
	}

	TotalMoney += Money;

	fp = fopen(szFileName, "wb");
	if (fp) {
		wsprintf(szBuff, "%d", TotalMoney);
		fwrite(szBuff, lstrlen(szBuff) + 1, 1, fp);
		fclose(fp);
	}

	wsprintf(szFileName, filenameCollectMoney, szRecordCollectDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgKindPeople,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
		lpPlayInfo->lpsmSock->szIPAddr, Money, TotalMoney);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordHackLogMoney(smCHAR_INFO* lpCharInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpCharInfo) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameHackLogMoney, HackLogDirectory, st.wMonth, st.wDay);

	CreateDirectory(HackLogDirectory, NULL);

	wsprintf(szBuff, msgHackMoney,
		st.wHour, st.wMinute, st.wSecond,
		lpCharInfo->szName, lpCharInfo->Level, lpCharInfo->Money);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordGetHighItem(rsPLAYINFO* lpPlayInfo, STG_ITEMS* lpStgItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo || !lpStgItem) return FALSE;
	if (!lpStgItem->BeginMode) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameGetHighItem, HackLogDirectory, st.wMonth, st.wDay);

	CreateDirectory(HackLogDirectory, NULL);

	wsprintf(szBuff, msgHighItem,
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->smCharInfo.szName, lpPlayInfo->smCharInfo.Level,
		lpStgItem->Item.ItemInfo.ItemName,
		lpStgItem->Item.ItemInfo.CODE,
		lpStgItem->Item.ItemInfo.ItemHeader.Head,
		lpStgItem->Item.ItemInfo.ItemHeader.dwChkSum,
		lpStgItem->Item.ItemInfo.JobCodeMask,
		lpStgItem->BeginMode);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordDeleteCharacter(char* szID, char* szIP, smCHAR_INFO* lpCharInfo)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!szID || !szIP || !lpCharInfo) return FALSE;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDeleteCharacter, LogDirectory, st.wMonth, st.wDay);

	CreateDirectory(LogDirectory, NULL);

	wsprintf(szBuff, msgCharDelete1,
		st.wHour, st.wMinute, st.wSecond,
		szID, lpCharInfo->szName, szIP, lpCharInfo->Level,
		lpCharInfo->Exp, lpCharInfo->Money);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordDeleteCharacterError(char* szID, char* szName)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	GetLocalTime(&st);
	wsprintf(szFileName, filenameDeleteCharactererror, LogDirectory, st.wMonth, st.wDay);

	CreateDirectory(LogDirectory, NULL);

	wsprintf(szBuff, msgCharDelete2,
		st.wHour, st.wMinute, st.wSecond,
		szID, szName);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordBlackUser(char* szID, DWORD dwTime)
{
	return TRUE;
}

int RecordSmeltingItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpSmeltingItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameSmeltingItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgSmeltingItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
		lpPlayInfo->lpsmSock->szIPAddr, lpSmeltingItem->ItemName,
		lpSmeltingItem->ItemHeader.Head, lpSmeltingItem->ItemHeader.dwChkSum, lpSmeltingItem->ItemHeader.dwTime);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordManufactureItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpManufactureItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameManufactureItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgManufactureItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
		lpPlayInfo->lpsmSock->szIPAddr, lpManufactureItem->ItemName,
		lpManufactureItem->ItemHeader.Head, lpManufactureItem->ItemHeader.dwChkSum, lpManufactureItem->ItemHeader.dwTime);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordMixtureResetItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpMixtureResetItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMixtureResetItem, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, msgMixtureResetItem,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName,
		lpPlayInfo->lpsmSock->szIPAddr, lpMixtureResetItem->ItemName,
		lpMixtureResetItem->ItemHeader.Head, lpMixtureResetItem->ItemHeader.dwChkSum, lpMixtureResetItem->ItemHeader.dwTime);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordMovieBloodyBattleItem(rsPLAYINFO* lpPlayInfo, sITEMINFO* lpMovieBloodyBattleItem)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];

	if (!lpPlayInfo->lpsmSock)
	{
		return FALSE;
	}

	CreateDirectory(EventLogDirectory, NULL);

	GetLocalTime(&st);
	wsprintf(szFileName, filenameMovieBloodyBattleItem, EventLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, MovieBloodyBattleLog,
		st.wHour, st.wMinute, st.wSecond, lpPlayInfo->szID, lpPlayInfo->szName);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, lstrlen(szBuff), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

char* szBlackUserDir = "WhiteBird";
char* szEverBlockDir = "StoneBird";

int rsAddBlockUserFile(char* szID, char* szLog)
{
	char szBuff[256];
	FILE* fp;

	if (!rsServerConfig.ForeverBlockMode)	return FALSE;

	CreateDirectory(szEverBlockDir, NULL);

	wsprintf(szBuff, "%s\\%s.fev", szEverBlockDir, szID);

	fp = fopen(szBuff, "wb");
	if (fp) {
		fwrite(szLog, lstrlen(szLog), 1, fp);
		fclose(fp);
	}

	return TRUE;
}

int	rsCheckBlockUserFile(char* szID)
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%s.fev", szEverBlockDir, szID);

	hFindHandle = FindFirstFile(szBuff, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	FindClose(hFindHandle);
	return TRUE;
}

int ResetBlackUserFiles()
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\*.bur", szBlackUserDir);
	CreateDirectory(szBlackUserDir, NULL);

	hFindHandle = FindFirstFile(szBuff, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE) {
		FindClose(hFindHandle);
		return 0;
	}
	while (1) {
		wsprintf(szBuff, "%s\\%s", szBlackUserDir, fd.cFileName);
		DeleteFile(szBuff);
		if (FindNextFile(hFindHandle, &fd) == FALSE) break;
	}
	FindClose(hFindHandle);

	return TRUE;
}

int ResetBlackUserFiles(char* szID, DWORD dwTime)
{
	char szBuff[256];
	char szBuff2[256];
	FILE* fp;
	SYSTEMTIME	st;

	wsprintf(szBuff, "%s\\%s.bur", szBlackUserDir, szID);

	if (dwTime) {
		GetLocalTime(&st);
		wsprintf(szBuff2, msgBlackUser, st.wHour, st.wMinute, st.wSecond, szID, dwTime / (1000 * 60));
		fp = fopen(szBuff, "wb");
		if (fp) {
			fwrite(szBuff2, lstrlen(szBuff2), 1, fp);
			fclose(fp);
		}
	}
	else {
		DeleteFile(szBuff);
	}

	return TRUE;
}

int FindBlackUserFile(char* szID)
{
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char szBuff[256];

	wsprintf(szBuff, "%s\\%s.bur", szBlackUserDir, szID);

	hFindHandle = FindFirstFile(szBuff, &fd);

	if (hFindHandle == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	FindClose(hFindHandle);
	return TRUE;
}

int rsCompareCharInfo(smCHAR_INFO* cSrc, smCHAR_INFO* cDest)
{
	return TRUE;
}

struct	srBLACK_LIST {
	char	szID[32];
	DWORD	dwFreeTime;
};

#define	srBLACK_LIST_MAX	400

srBLACK_LIST	srBlackList[srBLACK_LIST_MAX];
int	rsBlackListInit = 0;

int rsAddBackListID(char* szID, DWORD dwTime)
{
	return FALSE;
}

DWORD rsCheckBackListID(char* szID)
{
	return NULL;
}

int rsFreekBackListID(char* szID)
{
	int cnt;

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		if (srBlackList[cnt].szID[0] && lstrcmpi(srBlackList[cnt].szID, szID) == 0) {
			ResetBlackUserFiles(srBlackList[cnt].szID, 0);

			srBlackList[cnt].dwFreeTime = 0;
			srBlackList[cnt].szID[0] = 0;
			return TRUE;
		}
	}

	return FALSE;
}

int rsResetBackList()
{
	int cnt;

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		srBlackList[cnt].dwFreeTime = 0;
		srBlackList[cnt].szID[0] = 0;
	}

	ResetBlackUserFiles();

	rsBlackListInit = TRUE;

	return TRUE;
}

int rsShowBlackList(smWINSOCK* lpsmSock, char* szID)
{
	TRANS_CHATMESSAGE	TransChatMessage;
	int cnt;
	int dcnt;

	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;

	dcnt = 0;

	for (cnt = 0; cnt < srBLACK_LIST_MAX; cnt++) {
		if (srBlackList[cnt].szID[0]) {
			if (!szID[0] || lstrcmpi(szID, srBlackList[cnt].szID) == 0) {
				wsprintf(TransChatMessage.szMessage, "> ID ( %s ) / ( %d )Min.", srBlackList[cnt].szID, (srBlackList[cnt].dwFreeTime - dwPlayServTime) / 60000);
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
				dcnt++;
			}
		}
	}

	wsprintf(TransChatMessage.szMessage, "> Total %d Users", dcnt);
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	return TRUE;
}

DWORD SwapIPCode(DWORD dwIP)
{
	BYTE	bIP[4];

	bIP[0] = (BYTE)(dwIP & 0xFF);
	bIP[1] = (BYTE)((dwIP >> 8) & 0xFF);
	bIP[2] = (BYTE)((dwIP >> 16) & 0xFF);
	bIP[3] = (BYTE)((dwIP >> 24) & 0xFF);

	return (bIP[0] << 24) | (bIP[1] << 16) | (bIP[2] << 8) | (bIP[3]);
}

DWORD GetSwapIPCode(char* szIP)
{
	return SwapIPCode(inet_addr(szIP));
}

int	rsCheckDisableIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.DisableIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.DisableIP[cnt][0] && dwIP <= rsServerConfig.DisableIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

int	rsCheckEnableIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.EnableIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.EnableIP[cnt][0] && dwIP <= rsServerConfig.EnableIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

int	rsCheckAdminIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.AdminIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.AdminIP[cnt][0] && dwIP <= rsServerConfig.AdminIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

int	rsCheckSystemIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.SystemIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.SystemIP[cnt][0] && dwIP <= rsServerConfig.SystemIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

int	rsCheckLoginServerIP(DWORD dwUserIP)
{
	DWORD	dwIP;
	int		cnt;

	dwIP = SwapIPCode(dwUserIP);

	for (cnt = 0; cnt < rsServerConfig.LoginServerIP_Count; cnt++) {
		if (dwIP >= rsServerConfig.LoginServerIP[cnt][0] && dwIP <= rsServerConfig.LoginServerIP[cnt][1]) {
			return TRUE;
		}
	}

	return FALSE;
}

int	rsRecord_ItemLog(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag)
{
	LogITEM	LogItem;

	if (!lpPlayInfo->lpsmSock) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!rsServerConfig.TestSeverMode && (dwItemCode & sinITEM_MASK2) != sinGP1 &&
		(dwItemCode & sinITEM_MASK2) != sinQW1 && (dwItemCode & sinITEM_MASK2) != sinOR2 &&
		(dwItemCode & sinITEM_MASK2) != sinPZ1 && (dwItemCode & sinITEM_MASK2) != sinPZ2 &&
		(dwItemCode & sinITEM_MASK2) != sinSE1 && (dwItemCode & sinITEM_MASK2) != sinBI1 &&
		(dwItemCode & sinITEM_MASK2) != sinBI2 &&
		(dwItemCode & sinITEM_MASK2) != sinGF1 && (dwItemCode & sinITEM_MASK2) != sinBC1 &&

		(dwItemCode & sinITEM_MASK2) != sinPR1 && (dwItemCode & sinITEM_MASK2) != sinPR2 &&
		(dwItemCode & sinITEM_MASK2) != sinPR3 && (dwItemCode & sinITEM_MASK2) != sinPR4 &&
		(dwItemCode & sinITEM_MASK2) != sinWR1 && (dwItemCode & sinITEM_MASK2) != sinDR1 &&

		(dwItemCode & sinITEM_MASK2) != sinSP1) {
		if (dwItemCode == (sinGG1 | sin01)) {
			if (dwHead < 10000) return FALSE;
		}
		else {
			if (dwItemCode >= sinPM1) return FALSE;
			if ((dwItemCode & sinITEM_MASK2) == sinOS1 || (dwItemCode & sinITEM_MASK2) == sinFO1) {
				if ((dwItemCode & sinITEM_MASK3) < sin05) return FALSE;
			}
			else {
				if ((dwItemCode & sinITEM_MASK3) < sin07) return FALSE;
			}
		}
	}

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

int	rsRecord_ItemLog2(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, int Flag)
{
	LogITEM	LogItem;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

int	rsRecord_ItemLog_Change(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum,
	DWORD dwItemCode2, DWORD	dwHead2, DWORD dwChkSum2, int Flag)
{
	LogITEM	LogItem;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;

	LogItem.Item[1].dwCode = dwItemCode2;
	LogItem.Item[1].dwINo[0] = dwHead2;
	LogItem.Item[1].dwINo[1] = dwChkSum2;

	LogItem.ItemCount = 2;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

int	rsRecord_ItemLost(rsPLAYINFO* lpPlayInfo, DWORD* lpItemCode, DWORD* lpHead, DWORD* lpChkSum, int Flag)
{
	LogITEM	LogItem;
	int cnt;

	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.ItemCount = 0;
	for (cnt = 0; cnt < 12; cnt++) {
		if (lpItemCode[cnt]) {
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if (LogItem.ItemCount == 0) return FALSE;

	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

int	rsRecord_ItemLog_Trade(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, TRANS_TRADE_ITEMKEY* lpTransTradeItemKey)
{
	LogITEM_TRADE	LogItem;
	int cnt;

	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));

	if (!lpPlayInfo->lpsmSock) return FALSE;
	if (!lpPlayInfo2->lpsmSock) return FALSE;

	LogItem.Flag = 8;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	lstrcpy(LogItem.TUserID, lpPlayInfo2->szID);
	lstrcpy(LogItem.TCharName, lpPlayInfo2->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.TIP = lpPlayInfo2->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	if (lpTransTradeItemKey->Money > 0)
		LogItem.Money = lpTransTradeItemKey->Money - 193;
	else
		LogItem.Money = 0;

	LogItem.ItemCount = 0;

	for (cnt = 0; cnt < MAX_TRADE_ITEM; cnt++) {
		if (lpTransTradeItemKey->dwItemCode[cnt]) {
			LogItem.Item[LogItem.ItemCount].dwCode = lpTransTradeItemKey->dwItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpTransTradeItemKey->dwItemKey[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpTransTradeItemKey->dwItemSum[cnt];
			LogItem.ItemCount++;
		}
	}
	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	return b_PushLogItemQue(2, LogItem.size, &LogItem);
}

int	rsRecord_ItemLog_MyShop(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, DWORD dwItemCode, DWORD dwHead, DWORD dwChkSum, int Price)
{
	LogITEM_TRADE	LogItem;

	if (!lpPlayInfo->lpsmSock) return FALSE;
	if (!lpPlayInfo2->lpsmSock) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));
	LogItem.Flag = ITEMLOG_MYSHOP;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	lstrcpy(LogItem.TUserID, lpPlayInfo2->szID);
	lstrcpy(LogItem.TCharName, lpPlayInfo2->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.TIP = lpPlayInfo2->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.Money = Price;

	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	b_PushLogItemQue(2, LogItem.size, &LogItem);

	ZeroMemory(&LogItem, sizeof(LogITEM_TRADE));
	LogItem.Flag = ITEMLOG_MYSHOP;
	lstrcpy(LogItem.UserID, lpPlayInfo2->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo2->szName);
	lstrcpy(LogItem.TUserID, lpPlayInfo->szID);
	lstrcpy(LogItem.TCharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo2->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.TIP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.Item[0].dwCode = dwItemCode;
	LogItem.Item[0].dwINo[0] = dwHead;
	LogItem.Item[0].dwINo[1] = dwChkSum;
	LogItem.ItemCount = 1;

	LogItem.size = sizeof(LogITEM_TRADE) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	b_PushLogItemQue(2, LogItem.size, &LogItem);

	return TRUE;
}

int	rsRecord_ItemLog_Post(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, DWORD	dwHead, DWORD dwChkSum, DWORD dwGCode, char* szTelNum, int Flag)
{
	LogGiftITEM	LogItem;

	if (!lpPlayInfo->lpsmSock) return FALSE;

	ZeroMemory(&LogItem, sizeof(LogGiftITEM));

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
	LogItem.Gitem.dwCode = dwItemCode;
	LogItem.Gitem.dwINo[0] = dwHead;
	LogItem.Gitem.dwINo[1] = dwChkSum;
	LogItem.GNo = dwGCode;
	LogItem.size = sizeof(LogGiftITEM);

	if (szTelNum && szTelNum[0]) {
		szTelNum[15] = 0;
		lstrcpy(LogItem.TEL, szTelNum);
	}

	return b_PushLogItemQue(3, LogItem.size, &LogItem);
}

int	rsRecord_SmeltingItemLog(rsPLAYINFO* lpPlayInfo, DWORD* lpItemCode, DWORD* lpHead, DWORD* lpChkSum, int Flag)
{
	LogITEM LogItem;
	int cnt;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.ItemCount = 0;
	for (cnt = 0; cnt < 5; cnt++)
	{
		if (lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if (LogItem.ItemCount == 0) return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

int	rsRecord_ManufactureItemLog(rsPLAYINFO* lpPlayInfo, DWORD* lpItemCode, DWORD* lpHead, DWORD* lpChkSum, int Flag)
{
	LogITEM LogItem;
	int cnt;
	ZeroMemory(&LogItem, sizeof(LogITEM));

	if (!lpPlayInfo->lpsmSock) return FALSE;

	LogItem.Flag = Flag;
	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;

	LogItem.ItemCount = 0;
	for (cnt = 0; cnt < 4; cnt++)
	{
		if (lpItemCode[cnt])
		{
			LogItem.Item[LogItem.ItemCount].dwCode = lpItemCode[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[0] = lpHead[cnt];
			LogItem.Item[LogItem.ItemCount].dwINo[1] = lpChkSum[cnt];
			LogItem.ItemCount++;
		}
	}

	if (LogItem.ItemCount == 0) return FALSE;
	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));

	return b_PushLogItemQue(1, LogItem.size, &LogItem);
}

////int rsRecord_MixtureResetItemLog(rsPLAYINFO * lpPlayInfo, sMIXTURE_RESET_ITEM_SERVER * pMixtureResetItem_Server, int Flag)
////{
////	LogITEM LogItem;
////	ZeroMemory(&LogItem, sizeof(LogITEM));
////
////	if (!lpPlayInfo->lpsmSock) return FALSE;
////
////	LogItem.Flag = Flag;
////	lstrcpy(LogItem.UserID, lpPlayInfo->szID);
////	lstrcpy(LogItem.CharName, lpPlayInfo->szName);
////	LogItem.IP = lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr;
////
////	LogItem.ItemCount = 0;
////
////
////	LogItem.Item[LogItem.ItemCount].dwCode = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.CODE;
////	LogItem.Item[LogItem.ItemCount].dwINo[0] = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.Head;
////	LogItem.Item[LogItem.ItemCount].dwINo[1] = pMixtureResetItem_Server->DesMixtureResetItem.sItemInfo.ItemHeader.dwChkSum;
////	LogItem.ItemCount++;
////
////
////	LogItem.Item[LogItem.ItemCount].dwCode = pMixtureResetItem_Server->dwMixtureResetStoneItemCode;
////	LogItem.Item[LogItem.ItemCount].dwINo[0] = pMixtureResetItem_Server->dwMixtureResetStoneHead;
////	LogItem.Item[LogItem.ItemCount].dwINo[1] = pMixtureResetItem_Server->dwMixtureResetStoneCheckSum;
////	LogItem.ItemCount++;
////
////	if (LogItem.ItemCount == 0) return FALSE;
////	LogItem.size = sizeof(LogITEM) - (sizeof(_LogITEM) * (32 - LogItem.ItemCount));
////
////
////	return b_PushLogItemQue(1, LogItem.size, &LogItem);
////}

int	rsSaveAgingItemToHDD(sITEMINFO* lpItem)
{
	char	szBuff[256];
	FILE* fp;

	CreateDirectory(szLogItemDataDirectory, NULL);

	wsprintf(szBuff, "%s\\%d@%d.itm", szLogItemDataDirectory, lpItem->ItemHeader.Head, lpItem->ItemHeader.dwChkSum);
	fp = fopen(szBuff, "wb");
	if (fp) {
		fwrite(lpItem, sizeof(sITEMINFO), 1, fp);
		fclose(fp);
		return TRUE;
	}

	return FALSE;
}

int	rsSaveCreateItemToHDD(psITEM* lpItem)
{
	DWORD	dwCode;
	char	szBuff[256];
	FILE* fp;

	dwCode = lpItem->ItemInfo.CODE;
	if (dwCode >= sinPM1) return FALSE;
	if ((dwCode & sinITEM_MASK2) == sinOS1) {
		if ((dwCode & sinITEM_MASK3) < sin05) return FALSE;
	}
	else {
		if ((dwCode & sinITEM_MASK3) < sin08) return FALSE;
	}

	CreateDirectory(szLogItemDataDirectory, NULL);

	wsprintf(szBuff, "%s\\%d@%d.itm", szLogItemDataDirectory, lpItem->ItemInfo.ItemHeader.Head, lpItem->ItemInfo.ItemHeader.dwChkSum);
	fp = fopen(szBuff, "wb");
	if (fp) {
		fwrite(&lpItem->ItemInfo, sizeof(sITEMINFO), 1, fp);
		fclose(fp);
		return TRUE;
	}

	return FALSE;
}

int	rsLoadCreateItemToHDD(psITEM* lpItem, char* szFileCode)
{
	FILE* fp;
	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;
	char	szBuff[256];

	wsprintf(szBuff, "%s\\%s.itm", szLogItemDataDirectory, szFileCode);

	hFindHandle = FindFirstFile(szBuff, &fd);
	if (hFindHandle != INVALID_HANDLE_VALUE) {
		FindClose(hFindHandle);

		fp = fopen(szBuff, "rb");
		if (fp) {
			fread(&lpItem->ItemInfo, sizeof(sITEMINFO), 1, fp);
			fclose(fp);
		}
		return TRUE;
	}

	return FALSE;
}

struct	sRECORD_COPIED_ITEM_HEAD {
	char	szHeader[16];
	int		TotalCount;
	int		A_ItemCount;
	int		D_ItemCount;
	int		S_ItemCount;
	int		E_ItemCount;

	int		Temp[7];
};

struct	sRECORD_COPIED_ITEM {
	DWORD	dwItemCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	DWORD	dwTemp;
};

struct sRECORD_COPIED_ITEM_FILE {
	sRECORD_COPIED_ITEM_HEAD	sHeader;
	sRECORD_COPIED_ITEM			sCopiedItem[4096];
};

sRECORD_COPIED_ITEM* lpCopiedItem_List = 0;
sRECORD_COPIED_ITEM* lpCopiedItem_Sheltom_List = 0;

int rsCopiedItem_Count = 0;
int rsCopiedItem_Sheltom_Count = 0;

int rsLoadCopiedItemList()
{
	sRECORD_COPIED_ITEM_FILE	sCopiedItems;
	FILE* fp;
	int cnt;

	rsRemoveCopiedItemList();

	fp = fopen("cpItem.dat", "rb");
	if (!fp) return FALSE;

	fread(&sCopiedItems, sizeof(sRECORD_COPIED_ITEM_FILE), 1, fp);
	fclose(fp);

	if (sCopiedItems.sHeader.TotalCount >= 4096 || sCopiedItems.sHeader.TotalCount < 0) return FALSE;

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	for (cnt = 0; cnt < sCopiedItems.sHeader.TotalCount; cnt++) {
		if ((sCopiedItems.sCopiedItem[cnt].dwItemCode & sinITEM_MASK2) == sinOS1) {
			rsCopiedItem_Sheltom_Count++;
		}
		else {
			rsCopiedItem_Count++;
		}
	}

	if (rsCopiedItem_Count) lpCopiedItem_List = new sRECORD_COPIED_ITEM[rsCopiedItem_Count];
	if (rsCopiedItem_Sheltom_Count) lpCopiedItem_Sheltom_List = new sRECORD_COPIED_ITEM[rsCopiedItem_Sheltom_Count];

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	for (cnt = 0; cnt < sCopiedItems.sHeader.TotalCount; cnt++) {
		if ((sCopiedItems.sCopiedItem[cnt].dwItemCode & sinITEM_MASK2) == sinOS1) {
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwItemCode = sCopiedItems.sCopiedItem[cnt].dwItemCode;
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwHead = sCopiedItems.sCopiedItem[cnt].dwHead;
			lpCopiedItem_Sheltom_List[rsCopiedItem_Sheltom_Count].dwChkSum = sCopiedItems.sCopiedItem[cnt].dwChkSum;
			rsCopiedItem_Sheltom_Count++;
		}
		else {
			lpCopiedItem_List[rsCopiedItem_Count].dwItemCode = sCopiedItems.sCopiedItem[cnt].dwItemCode;
			lpCopiedItem_List[rsCopiedItem_Count].dwHead = sCopiedItems.sCopiedItem[cnt].dwHead;
			lpCopiedItem_List[rsCopiedItem_Count].dwChkSum = sCopiedItems.sCopiedItem[cnt].dwChkSum;
			rsCopiedItem_Count++;
		}
	}

	return TRUE;
}

int rsRemoveCopiedItemList()
{
	if (lpCopiedItem_List) { delete lpCopiedItem_List; lpCopiedItem_List = 0; }
	if (lpCopiedItem_Sheltom_List) { delete lpCopiedItem_Sheltom_List; lpCopiedItem_Sheltom_List = 0; }

	rsCopiedItem_Sheltom_Count = 0;
	rsCopiedItem_Count = 0;

	return TRUE;
}

int rsCheckCopiedItem(DWORD dwCode, DWORD dwHead, DWORD dwChkSum)
{
	int cnt;

	if ((dwCode & sinITEM_MASK2) == sinOS1) {
		if (!lpCopiedItem_Sheltom_List || rsCopiedItem_Sheltom_Count <= 0) return FALSE;

		for (cnt = 0; cnt < rsCopiedItem_Sheltom_Count; cnt++) {
			if (dwCode == lpCopiedItem_Sheltom_List[cnt].dwItemCode &&
				dwHead == lpCopiedItem_Sheltom_List[cnt].dwHead &&
				dwChkSum == lpCopiedItem_Sheltom_List[cnt].dwChkSum) {
				return TRUE;
			}
		}
	}
	else {
		if (!lpCopiedItem_List || rsCopiedItem_Count <= 0) return FALSE;

		for (cnt = 0; cnt < rsCopiedItem_Count; cnt++) {
			if (dwCode == lpCopiedItem_List[cnt].dwItemCode &&
				dwHead == lpCopiedItem_List[cnt].dwHead &&
				dwChkSum == lpCopiedItem_List[cnt].dwChkSum) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

int rsCheckCopiedItem(sITEMINFO* lpItem)
{
	DWORD dwHead, dwChkSum;

	if (lpItem->BackUpKey && lpItem->BackUpChkSum) {
		dwHead = lpItem->BackUpKey;
		dwChkSum = lpItem->BackUpChkSum;
	}
	else {
		dwHead = lpItem->ItemHeader.Head;
		dwChkSum = lpItem->ItemHeader.dwChkSum;
	}

	return rsCheckCopiedItem(lpItem->CODE, dwHead, dwChkSum);
}

int rsUpdateSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	switch (lpTransCommand->WParam) {
	case SKILL_PLAY_METAL_GOLEM:
	case SKILL_PLAY_RECALL_WOLVERIN:
	case SKILL_PLAY_FIRE_ELEMENTAL:
	case SKILL_PLAY_R_KNIGHT:
	case SKILL_PLAY_ARCURDA:

	case SKILL_METAL_GOLEM:
	case SKILL_RECALL_WOLVERIN:
	case SKILL_FIRE_ELEMENTAL:
	case SKILL_R_KNIGHT:
	case SKILL_ARCUDA:

		if (lpPlayInfo->lpLinkChar && lpPlayInfo->lpLinkChar->dwObjectSerial == lpPlayInfo->dwLinkCharCode && lpPlayInfo->lpLinkChar->HoSkillCode) {
			lpPlayInfo->lpLinkChar->HoSkillMode = lpTransCommand->LParam;
			lpPlayInfo->lpLinkChar->lpTargetPlayInfo = 0;
			lpPlayInfo->lpLinkChar->lpTargetChar = 0;
		}
		break;
	}

	return TRUE;
}

int rsCancelSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	switch (lpTransCommand->WParam) {
	case 0:
		lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
		lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;

		lpPlayInfo->dwSkill_ExtreamShield_Time = 0;
		lpPlayInfo->dwSkill_ExtreamShield_Param = 0;

		lpPlayInfo->dwSkill_AutoMation_Time = 0;
		lpPlayInfo->dwSkill_AutoMation_Param = 0;

		lpPlayInfo->dwSkill_Maximize_Time = 0;
		lpPlayInfo->dwSkill_Maximize_Param = 0;

		lpPlayInfo->dwSkill_HolyBody_Time = 0;
		lpPlayInfo->dwSkill_HolyBody_Param = 0;

		lpPlayInfo->dwSkill_HolyValor_Time = 0;
		lpPlayInfo->dwSkill_HolyValor_Param = 0;

		lpPlayInfo->dwSkill_HolyReflection_Time = 0;
		lpPlayInfo->dwSkill_HolyReflection_Param = 0;

		lpPlayInfo->dwSkill_EnchantWeapon_Time = 0;
		lpPlayInfo->dwSkill_EnchantWeapon_Param = 0;

		lpPlayInfo->dwSkill_MetalArmor_Time = 0;
		lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		lpPlayInfo->dwSkill_SparkShield_Time = 0;
		lpPlayInfo->dwSkill_SparkShield_Param = 0;

		lpPlayInfo->dwSKill_Falcon_Time = 0;
		lpPlayInfo->dwSKill_Falcon_Damage[0] = 0;
		lpPlayInfo->dwSKill_Falcon_Damage[1] = 0;

		lpPlayInfo->dwSkill_DivineInhalation_Time = 0;
		lpPlayInfo->dwSkill_DivineInhalation_Param = 0;

		lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;
		lpPlayInfo->dwSkill_TriumphOfValhalla_Param = 0;

		lpPlayInfo->dwSkill_VirtualLife_Time = 0;
		lpPlayInfo->dwSkill_VirtualLife_Param = 0;

		lpPlayInfo->dwSkill_EnergyShield_Time = 0;
		lpPlayInfo->dwSkill_EnergyShield_Param = 0;

		lpPlayInfo->dwSkill_SpiritElemental_Time = 0;
		lpPlayInfo->dwSkill_SpiritElemental_Param = 0;

		lpPlayInfo->dwSkill_DancingSword_Time = 0;
		lpPlayInfo->dwSkill_DancingSword_Param = 0;
		lpPlayInfo->dwSkill_DancingSword_DelayTime = 0;

		lpPlayInfo->dwSkill_Vanish_Time = 0;
		lpPlayInfo->dwSkill_Vanish_Param = 0;

		lpPlayInfo->dwSkill_MagneticSphere_Time = 0;
		lpPlayInfo->dwSkill_MagneticSphere_Param = 0;

		lpPlayInfo->dwSkill_Berserker_Time = 0;
		lpPlayInfo->dwSkill_Berserker_Param = 0;

		lpPlayInfo->dwSkill_AssassinEye_Time = 0;
		lpPlayInfo->dwSkill_AssassinEye_Param = 0;

		lpPlayInfo->dwSkill_Vague_Time = 0;
		lpPlayInfo->dwSkill_Vague_Param = 0;

		lpPlayInfo->dwSkill_ForceOfNature_Time = 0;
		lpPlayInfo->wSkill_ForceOfNature_Param[0] = 0;
		lpPlayInfo->wSkill_ForceOfNature_Param[1] = 0;

		lpPlayInfo->dwSkill_GodlyShied_Time = 0;
		lpPlayInfo->dwSkill_GodlyShied_Param = 0;

		lpPlayInfo->dwSkill_GodsBless_Time = 0;
		lpPlayInfo->dwSkill_GodsBless_Param = 0;

		lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;

		lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
		lpPlayInfo->dwSkill_FrostJavelin_Param = 0;

		lpPlayInfo->dwSkill_RegenerationField_Time = 0;

		lpPlayInfo->dwSkill_SummonMuspell_Time = 0;
		lpPlayInfo->dwSkill_SummonMuspell_Param = 0;

		lpPlayInfo->dwCurse_Attack_Time = 0;
		lpPlayInfo->dwCurse_Defence_Time = 0;
		break;

	case SKILL_PLAY_HOLY_VALOR:
		lpPlayInfo->dwSkill_HolyValor_Time = 0;
		lpPlayInfo->dwSkill_HolyValor_Param = 0;
		break;

	case SKILL_PLAY_AUTOMATION:
		lpPlayInfo->dwSkill_AutoMation_Time = 0;
		lpPlayInfo->dwSkill_AutoMation_Param = 0;
		break;

	case SKILL_PLAY_MAXIMIZE:
		lpPlayInfo->dwSkill_Maximize_Time = 0;
		lpPlayInfo->dwSkill_Maximize_Param = 0;
		break;

	case SKILL_PLAY_PHYSICAL_ABSORB:
		lpPlayInfo->dwSkill_PhysicalAbsorb_Time = 0;
		lpPlayInfo->dwSkill_PhysicalAbsorb_Param = 0;
		break;

	case SKILL_PLAY_EXTREME_SHIELD:
		lpPlayInfo->dwSkill_ExtreamShield_Time = 0;
		lpPlayInfo->dwSkill_ExtreamShield_Param = 0;
		break;

	case SKILL_PLAY_FROST_JAVELIN:
		lpPlayInfo->dwSkill_FrostJavelin_Time = 0;
		lpPlayInfo->dwSkill_FrostJavelin_Param = 0;
		break;

	case SKILL_PLAY_A_MIGAL:
		lpPlayInfo->dwAdventMigal_Time = 0;
		lpPlayInfo->dwAdventMigal_Param = 0;
		break;

	case SKILL_PLAY_A_MIDRANDA:
		lpPlayInfo->dwAdventMidranda_Time = 0;
		lpPlayInfo->dwAdventMidranda_Param = 0;
		break;
	}

	return TRUE;
}

int rsProcessSkillPartyUser(rsPLAYINFO* lpPlayInfo, TRANS_PARTY_SKILL* lpTransPartySkill)
{
	int point;

	point = lpTransPartySkill->Point - 1;
	if (point < 0 || point >= 10) return FALSE;

	switch (lpTransPartySkill->dwSkillCode) {
	case SKILL_PLAY_HOLY_VALOR:

		lpPlayInfo->dwSkill_HolyValor_Time = dwPlayServTime + (Holy_Valor_Time[point] * 1000);
		lpPlayInfo->dwSkill_HolyValor_Param = Holy_Valor_Damage[point];
		return TRUE;

	case SKILL_PLAY_ALAS:
		lpPlayInfo->dwSkill_Alas_Time = dwPlayServTime + Alas_Time[point] * 1000;
		lpPlayInfo->dwSkill_Alas_Param = point;
		return TRUE;

	case SKILL_PLAY_P_ENHENCE:
		lpPlayInfo->dwSkill_P_Enhence_Time = dwPlayServTime + P_Enhence_Time[point] * 1000;
		lpPlayInfo->dwSkill_P_Enhence_Param = point;
		return TRUE;

	case SKILL_PLAY_A_MIGAL:
		lpPlayInfo->dwAdventMigal_Time = dwPlayServTime + AdventMigal_Time[point] * 1000;
		lpPlayInfo->dwAdventMigal_Param = point;
		return TRUE;

		//case SKILL_PLAY_A_MIDRANDA:
		//	lpPlayInfo->dwAdventMidranda_Time = dwPlayServTime + AdventMidranda_Time[point] * 1000;
		//	lpPlayInfo->dwAdventMidranda_Param = point;
		//	return TRUE;

	case SKILL_PLAY_VIRTUAL_LIFE:
		lpPlayInfo->dwSkill_VirtualLife_Time = dwPlayServTime + Virtual_Life_Time[point] * 1000;
		lpPlayInfo->dwSkill_VirtualLife_Param = Virtual_Life_Percent[point];
		return TRUE;
	}

	return FALSE;
}

int	rsRecvSkillPartyUser(TRANS_PARTY_SKILL* lpTransPartySkill)
{
	int cnt;
	rsPLAYINFO* lpPlayInfo;

	for (cnt = 0; cnt < PARTY_PLAYER_MAX; cnt++)
	{
		lpPlayInfo = srFindUserFromSerial(lpTransPartySkill->dwPartyUser[cnt]);
		if (lpPlayInfo && lpPlayInfo->lpsmSock)
		{
			if (rsProcessSkillPartyUser(lpPlayInfo, lpTransPartySkill) == TRUE)
			{
				lpPlayInfo->lpsmSock->Send2((char*)lpTransPartySkill, lpTransPartySkill->size, TRUE);
			}
		}
	}

	return TRUE;
}

int rsRecvProcessSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	DWORD dwSkillCode;
	int point;
	rsPLAYINFO* lpPlayInfo2;
	smTRANS_COMMAND_EX	TransCommandEx;
	int	lv;
	smCHAR* lpChar;
	int cnt, x, y, z, dist, size;

	dwSkillCode = lpTransCommand->WParam & 0xFF;
	point = (lpTransCommand->WParam >> 8) & 0xF;
	point -= 1;

	if (point < 0) point = lpTransCommand->LParam - 1;

	if (point < 0 || point >= 10) return FALSE;

	if (rsCheckSkillLevel(lpPlayInfo, dwSkillCode) == FALSE) {
		if (lpPlayInfo->WarningCount < 5 && dwSkillCode != SKILL_PLAY_RESURRECTION) {
			TransCommandEx.size = sizeof(smTRANS_COMMAND);
			TransCommandEx.code = smTRANSCODE_SET_BLACKLIST;
			TransCommandEx.WParam = 8850;
			TransCommandEx.LParam = lpPlayInfo->smCharInfo.Level;
			TransCommandEx.SParam = dwSkillCode;
			TransCommandEx.EParam = point;
			rsSendDataServer(lpPlayInfo->lpsmSock, &TransCommandEx);
			lpPlayInfo->WarningCount++;
		}
	}

	switch (dwSkillCode) {
	case SKILL_PLAY_HOLY_REFLECTION:
		if (lpPlayInfo->smCharInfo.JOB_CODE == 8) {
			lpPlayInfo->dwSkill_HolyReflection_Time = dwPlayServTime + Holy_Reflection_Time[point] * 1000;
			lpPlayInfo->dwSkill_HolyReflection_Param = Holy_Reflection_Return_Damage[point];
		}
		break;

	case SKILL_PLAY_ENCHANT_WEAPON:
		if (lpPlayInfo->smCharInfo.JOB_CODE == 7) {
			lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
			if (lpPlayInfo2 && lpPlayInfo2->lpsmSock) {
				lpPlayInfo2->dwSkill_EnchantWeapon_Time = dwPlayServTime + Enchant_Weapon_Time[point] * 1000;
				lpPlayInfo2->dwSkill_EnchantWeapon_Param = (point + 1) | (lpTransCommand->EParam << 8);
				if (lpPlayInfo2 != lpPlayInfo)
					lpPlayInfo2->lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
			}
		}
		break;

	case SKILL_PLAY_AUTOMATION:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpPlayInfo->dwSkill_AutoMation_Time = dwPlayServTime + Automation_Time[point] * 1000;
			lpPlayInfo->dwSkill_AutoMation_Param = Automation_Damage[point];
		}
		break;

	case SKILL_PLAY_MAXIMIZE:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpPlayInfo->dwSkill_Maximize_Time = dwPlayServTime + Maximize_Time[point] * 1000;
			lpPlayInfo->dwSkill_Maximize_Param = Maximize_Damage[point];
		}
		break;

	case SKILL_PLAY_PHYSICAL_ABSORB:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpPlayInfo->dwSkill_PhysicalAbsorb_Time = dwPlayServTime + P_Absorb_UseTime[point] * 1000;
			lpPlayInfo->dwSkill_PhysicalAbsorb_Param = GetRandomPos(P_Absorb[point][0], P_Absorb[point][1]);
		}
		break;

	case SKILL_PLAY_EXTREME_SHIELD:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpPlayInfo->dwSkill_ExtreamShield_Time = dwPlayServTime + E_Shield_UseTime[point] * 1000;
			lpPlayInfo->dwSkill_ExtreamShield_Param = E_Shield_BlockRate[point];
		}
		break;

	case SKILL_PLAY_HOLY_BODY:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT) {
			lpPlayInfo->dwSkill_HolyBody_Time = dwPlayServTime + HolyBody_Time[point] * 1000;
			lpPlayInfo->dwSkill_HolyBody_Param = HolyBody_Absorb[point];
		}
		break;

	case SKILL_PLAY_METAL_ARMOR:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpPlayInfo->dwSkill_MetalArmor_Time = dwPlayServTime + Metal_Armor_Time[point] * 1000;
			if (lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10) {
				lpPlayInfo->dwSkill_MetalArmor_Param = (P_Absorb[lpTransCommand->SParam - 1][0] + P_Absorb[lpTransCommand->SParam - 1][1]) / 2;
			}
			else
				lpPlayInfo->dwSkill_MetalArmor_Param = 0;
		}
		break;

	case SKILL_PLAY_SPARK_SHIELD:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpPlayInfo->dwSkill_SparkShield_Time = dwPlayServTime + Spark_Shield_Time[point] * 1000;
			if (lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10) {
				lpPlayInfo->dwSkill_SparkShield_Param = (Spark_Shield_Damage[point] * Spark_Damage[lpTransCommand->SParam - 1][0]) / 100;
				lpPlayInfo->dwSkill_SparkShield_Param <<= 16;
				lpPlayInfo->dwSkill_SparkShield_Param |= (Spark_Shield_Damage[point] * Spark_Damage[lpTransCommand->SParam - 1][1]) / 100;
			}
			else
				lpPlayInfo->dwSkill_SparkShield_Param = 0;
		}
		break;

	case SKILL_PLAY_FALCON:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER) {
			lpPlayInfo->dwSKill_Falcon_Time = dwPlayServTime + Falcon_Time[point] * 1000;
			lpPlayInfo->dwSKill_Falcon_Damage[0] = Falcon_Damage[point][0];
			lpPlayInfo->dwSKill_Falcon_Damage[1] = Falcon_Damage[point][1];
		}
		break;

	case SKILL_PLAY_GOLDEN_FALCON:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER) {
			if (lpTransCommand->SParam > 0 && lpTransCommand->SParam <= 10) {
				lpPlayInfo->dwSKill_Falcon_Time = dwPlayServTime + Golden_Falcon_Time[point] * 1000;
				lpPlayInfo->dwSKill_Falcon_Damage[0] = Falcon_Damage[lpTransCommand->SParam - 1][0];
				lpPlayInfo->dwSKill_Falcon_Damage[1] = Falcon_Damage[lpTransCommand->SParam - 1][1];
				lpPlayInfo->dwSKill_Falcon_Damage[0] = (lpPlayInfo->dwSKill_Falcon_Damage[0] * Golden_Falcon_Damage[point]) / 100;
				lpPlayInfo->dwSKill_Falcon_Damage[1] = (lpPlayInfo->dwSKill_Falcon_Damage[1] * Golden_Falcon_Damage[point]) / 100;
			}
		}
		break;

	case SKILL_PLAY_DIVINE_INHALATION:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT) {
			lpPlayInfo->dwSkill_DivineInhalation_Time = dwPlayServTime + D_Inhalation_Time[point] * 1000;
			lpPlayInfo->dwSkill_DivineInhalation_Param = point;
		}
		break;

	case SKILL_PLAY_RESURRECTION:
		if (lpTransCommand->SParam) {
			if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) {
				lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
				if (lpPlayInfo2) {
					if ((rand() % 100) < Resurrection_Percent[point]) {
						if (lpPlayInfo2 != lpPlayInfo)
							lpPlayInfo2->lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
					}
				}
			}
		}
		else {
			ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
			TransCommandEx.WParam = smCOMMNAD_USER_RESURRECTION;
			TransCommandEx.LParam = lpPlayInfo->dwObjectSerial;
			TransCommandEx.SParam = 0;
			TransCommandEx.EParam = 0;
			rsSendCommandUser(lpPlayInfo, &TransCommandEx);
		}
		break;

	case SKILL_PLAY_VIRTUAL_LIFE:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) {
			if (!lpTransCommand->SParam) {
				lpPlayInfo->dwSkill_VirtualLife_Time = dwPlayServTime + Virtual_Life_Time[point] * 1000;
				lpPlayInfo->dwSkill_VirtualLife_Param = Virtual_Life_Percent[point];
			}
			else {
				lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
				if (lpPlayInfo2 && lpPlayInfo2->dwSkill_VirtualLife_Time < dwPlayServTime) {
					lpPlayInfo2->dwSkill_VirtualLife_Time = dwPlayServTime + Virtual_Life_Time[point] * 1000;
					lpPlayInfo2->dwSkill_VirtualLife_Param = Virtual_Life_Percent[point];
					lpPlayInfo2->lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
				}
			}
		}
		break;

	case SKILL_PLAY_H_BENEDIC:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT)
		{
			if (!lpTransCommand->SParam)
			{
				lpPlayInfo->dwSkill_HolyBenedic_Time = dwPlayServTime + H_Benedic_Time[point] * 1000;
				lpPlayInfo->dwSkill_HolyBenedic_Param = H_Benedic_UndeadDamage[point];
			}
			else
			{
				lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
				if (lpPlayInfo2 && lpPlayInfo2->dwSkill_HolyBenedic_Time < dwPlayServTime)
				{
					lpPlayInfo2->dwSkill_HolyBenedic_Time = dwPlayServTime + H_Benedic_Time[point] * 1000;
					lpPlayInfo2->dwSkill_HolyBenedic_Param = H_Benedic_UndeadDamage[point];
					lpPlayInfo2->lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
				}
			}
		}
		break;
	case SKILL_PLAY_AMPLIFIED:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN)
		{
			lpPlayInfo->dwSkill_Amplified_Time = dwPlayServTime + Amplified_Time[point] * 1000;
			lpPlayInfo->dwSkill_Amplified_Param = point;
		}
		break;

	case SKILL_PLAY_I_BULKUP:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MARTIAL)
		{
			lpPlayInfo->dwSkill_I_Bulkup_Time = dwPlayServTime + Bulkup_Time[point] * 1000;
			lpPlayInfo->dwSkill_I_Bulkup_Param = Bulkup_HP[point];
		}
		break;

	case SKILL_PLAY_R_MAKER:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_SHAMAN)
		{
			lpPlayInfo->dwSkill_RainMaker_Time = dwPlayServTime + RainMaker_Time[point] * 1000;
			lpPlayInfo->dwSkill_RainMaker_Param = point;
		}
		break;

	case SKILL_PLAY_BLIND:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ASSASSINE)
		{
			lpPlayInfo->dwSkill_Blind_Time = dwPlayServTime + Blind_Time[point - 1] * 1000;
			lpPlayInfo->dwSkill_Blind_Param = point;
		}
		break;

	case SKILL_PLAY_R_KNIGHT:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_SHAMAN)
		{
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if (lpChar)
			{
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = BloodyKnight_Damage[point - 1][0];
				lpChar->smCharInfo.Attack_Damage[1] = BloodyKnight_Damage[point - 1][1];
				lpChar->smCharInfo.Attack_Rating = BloodyKnight_Hit[point];
				lpChar->smCharInfo.Defence = BloodyKnight_Defense[point];

				lpChar->smCharInfo.Life[0] = BloodyKnight_Life[point] + lpPlayInfo->smCharInfo.Strength * 2;
				lpChar->smCharInfo.Life[1] = lpChar->smCharInfo.Life[0];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;

				lpChar->smCharInfo.wPlayClass[1] = fONE + point * 15;
			}
		}
		break;

	case SKILL_PLAY_ARCURDA:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA)
		{
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if (lpChar)
			{
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = Arcuda_Damage[point - 1][0];
				lpChar->smCharInfo.Attack_Damage[1] = Arcuda_Damage[point - 1][1];
				lpChar->smCharInfo.Attack_Rating = Arcuda_Hit[point];
				lpChar->smCharInfo.Defence = Arcuda_Defense[point];

				lpChar->smCharInfo.Life[0] = Arcuda_Life[point] + lpPlayInfo->smCharInfo.Strength * 2;
				lpChar->smCharInfo.Life[1] = lpChar->smCharInfo.Life[0];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;

				lpChar->smCharInfo.wPlayClass[1] = fONE + point * 15;
			}
		}
		break;

	case SKILL_PLAY_ZENITH:

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) {
		}
		break;

	case SKILL_PLAY_ENERGY_SHIELD:

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) {
			lpPlayInfo->dwSkill_EnergyShield_Time = dwPlayServTime + Energy_Shield_Time[point] * 1000;
			lpPlayInfo->dwSkill_EnergyShield_Param = Energy_Shield_DecDamage[point];
		}
		break;

	case SKILL_PLAY_SPIRIT_ELEMENTAL:

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) {
			lpPlayInfo->dwSkill_SpiritElemental_Time = dwPlayServTime + Spirit_Elemental_Time[point] * 1000;
			lpPlayInfo->dwSkill_SpiritElemental_Param = Spirit_Elemental_Damage[point];
		}
		break;

	case SKILL_PLAY_ANIMA:

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) {
			lpPlayInfo->dwSkill_Anima_Time = dwPlayServTime + Anima_Time[point] * 1000;
			lpPlayInfo->dwSkill_Anima_Param = Anima_Damage[point];
		}
		break;

	case SKILL_PLAY_DANCING_SWORD:

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) {
			lpPlayInfo->dwSkill_DancingSword_Time = dwPlayServTime + Dancing_Sword_Time[point] * 1000;
			lpPlayInfo->dwSkill_DancingSword_Param = (lpTransCommand->SParam) | (point << 16);
			lpPlayInfo->dwSkill_DancingSword_DelayTime = 0;
		}
		break;

	case SKILL_PLAY_TRIUMPH_OF_VALHALLA:

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA) {
			if (lpPlayInfo->smCharInfo.Level > 0 && lpPlayInfo->smCharInfo.Level < CHAR_LEVEL_MAX)
				lv = lpPlayInfo->smCharInfo.Level / 4;
			else
				lv = 0;

			if (!lpTransCommand->SParam) {
				lpPlayInfo->dwSkill_TriumphOfValhalla_Time = dwPlayServTime + (T_Of_Valhalla_Time[point] * 1000);
				lpPlayInfo->dwSkill_TriumphOfValhalla_Param = T_Of_Valhalla_Damage[point] + lv;

				lpPlayInfo->dwSkill_HallOfValhalla_Time = 0;
			}
			else {
				lpPlayInfo2 = srFindUserFromSerial(lpTransCommand->SParam);
				if (lpPlayInfo2) {
					if (lpPlayInfo2->dwSkill_HallOfValhalla_Time < dwPlayServTime) {
						lpPlayInfo2->dwSkill_TriumphOfValhalla_Time = dwPlayServTime + (T_Of_Valhalla_Time[point] * 1000);
						lpPlayInfo2->dwSkill_TriumphOfValhalla_Param = (T_Of_Valhalla_Damage[point] + lv) / 2;
						lpTransCommand->EParam = lpPlayInfo->smCharInfo.Level;
						lpPlayInfo2->lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
					}
				}
			}
		}
		return TRUE;

	case SKILL_PLAY_VANISH:

		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN) {
			lpPlayInfo->dwSkill_Vanish_Time = dwPlayServTime + Vanish_Time[point] * 1000;
			lpPlayInfo->dwSkill_Vanish_Param = point;
		}
		break;

	case SKILL_PLAY_MAGNETIC_SPHERE:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpPlayInfo->dwSkill_MagneticSphere_Time = dwPlayServTime + Magnetic_Sphere_Time[point] * 1000;
			lpPlayInfo->dwSkill_MagneticSphere_Param = point;
		}
		break;

	case SKILL_PLAY_METAL_GOLEM:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN) {
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if (lpChar) {
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = Metal_Golem_Damage[point][0];
				lpChar->smCharInfo.Attack_Damage[1] = Metal_Golem_Damage[point][1];
				lpChar->smCharInfo.Attack_Rating = Metal_Golem_Hit[point];
				lpChar->smCharInfo.Defence = Metal_Golem_Defense[point];

				lpChar->smCharInfo.Life[0] = Metal_Golem_Life[point] + lpPlayInfo->smCharInfo.Strength * 2;
				lpChar->smCharInfo.Life[1] = lpChar->smCharInfo.Life[0];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;

				lpChar->smCharInfo.wPlayClass[1] = fONE + point * 15;
			}
		}
		break;

	case SKILL_PLAY_BERSERKER:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_FIGHTER) {
			lpPlayInfo->dwSkill_Berserker_Time = dwPlayServTime + Berserker_Time[point] * 1000;
			lpPlayInfo->dwSkill_Berserker_Param = point;
		}
		break;

	case SKILL_PLAY_KRISHNA:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) {
			lpPlayInfo->dwSkill_Krishna_Time = dwPlayServTime + Krishna_Time[point] * 1000;
			lpPlayInfo->dwSkill_Krishna_Param = point;
		}
		break;

	case SKILL_PLAY_B_BERSERKER:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_FIGHTER) {
			lpPlayInfo->dwSkill_B_Berserker_Time = dwPlayServTime + B_Berserker_Time[point] * 1000;
			lpPlayInfo->dwSkill_B_Berserker_Param = point;
		}
		break;

	case SKILL_PLAY_ASSASSIN_EYE:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN) {
			lpPlayInfo->dwSkill_AssassinEye_Time = dwPlayServTime + Assassin_Eye_Time[point] * 1000;
			lpPlayInfo->dwSkill_AssassinEye_Param = point;
		}
		break;

	case SKILL_PLAY_VAGUE:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN) {
			lpPlayInfo->dwSkill_Vague_Time = dwPlayServTime + Vague_Time[point] * 1000;
			lpPlayInfo->dwSkill_Vague_Param = point;
		}
		break;

	case SKILL_PLAY_RECALL_WOLVERIN:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER) {
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if (lpChar) {
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = Recall_Wolverin_Damage[point][0];
				lpChar->smCharInfo.Attack_Damage[1] = Recall_Wolverin_Damage[point][1];
				lpChar->smCharInfo.Attack_Rating = Recall_Wolverin_Hit[point];
				lpChar->smCharInfo.Defence = Recall_Wolverin_Defense[point] + lpPlayInfo->smCharInfo.Dexterity * 2;
				lpChar->smCharInfo.Life[0] = Recall_Wolverin_Life[point];
				lpChar->smCharInfo.Life[1] = Recall_Wolverin_Life[point];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;

				lpChar->smCharInfo.wPlayClass[1] = (fONE / 2) + point * 12;
			}
		}
		break;

	case SKILL_PLAY_FORCE_OF_NATURE:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER) {
			lpPlayInfo->dwSkill_ForceOfNature_Time = dwPlayServTime + Force_Of_Nature_Time[point] * 1000;
			lpPlayInfo->wSkill_ForceOfNature_Param[0] = Force_Of_Nature_AddDamage[point];
			lpPlayInfo->wSkill_ForceOfNature_Param[1] = Force_Of_Nature_FalconAddDamage[point];

			size = 300 * 300;
			for (cnt = 0; cnt < CONNECTMAX; cnt++) {
				if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
					lpPlayInfo != &rsPlayInfo[cnt] &&
					rsPlayInfo[cnt].Position.Area == lpPlayInfo->Position.Area &&
					(rsPlayInfo[cnt].Position.Area != rsCASTLE_FIELD || (rsPlayInfo[cnt].dwClanCode && rsPlayInfo[cnt].dwClanCode == lpPlayInfo->dwClanCode)))
				{
					x = (lpPlayInfo->Position.x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
					y = (lpPlayInfo->Position.y - rsPlayInfo[cnt].Position.y) >> FLOATNS;
					z = (lpPlayInfo->Position.z - rsPlayInfo[cnt].Position.z) >> FLOATNS;

					dist = x * x + z * z;
					if (dist < size && abs(y) < 80) {
						rsPlayInfo[cnt].dwSkill_ForceOfNature_Time = dwPlayServTime + Force_Of_Nature_Time[point] * 1000;
						rsPlayInfo[cnt].wSkill_ForceOfNature_Param[0] = Force_Of_Nature_AddDamage[point] / 2;
						rsPlayInfo[cnt].wSkill_ForceOfNature_Param[1] = Force_Of_Nature_FalconAddDamage[point];
						rsPlayInfo[cnt].lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
					}
				}
			}
		}
		break;

	case SKILL_PLAY_GODLY_SHIELD:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT) {
			lpPlayInfo->dwSkill_GodlyShied_Time = dwPlayServTime + Godly_Shield_Time[point] * 1000;
			lpPlayInfo->dwSkill_GodlyShied_Param = point;
		}
		break;

	case SKILL_PLAY_GODS_BLESS:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_KNIGHT) {
			lpPlayInfo->dwSkill_GodsBless_Time = dwPlayServTime + God_Bless_Time[point] * 1000;
			lpPlayInfo->dwSkill_GodsBless_Param = God_Bless_AddDamage[point];
		}
		break;

	case SKILL_PLAY_HALL_OF_VALHALLA:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA) {
			if (lpPlayInfo->smCharInfo.Level > 0 && lpPlayInfo->smCharInfo.Level < CHAR_LEVEL_MAX) {
				lv = lpPlayInfo->smCharInfo.Level / 4;
				lpTransCommand->EParam = lpPlayInfo->smCharInfo.Level;
			}
			else {
				lv = 0;
				lpTransCommand->EParam = 1;
			}

			lpPlayInfo->dwSkill_HallOfValhalla_Time = dwPlayServTime + Hall_Of_Valhalla_Time[point] * 1000;
			lpPlayInfo->wSkill_HallOfValhalla_Param[0] = Hall_Of_Valhalla_AddEvation[point];
			lpPlayInfo->wSkill_HallOfValhalla_Param[1] = T_Of_Valhalla_Damage[lpTransCommand->SParam - 1] + lv;

			lpPlayInfo->dwSkill_TriumphOfValhalla_Time = 0;

			size = 350 * 350;
			for (cnt = 0; cnt < CONNECTMAX; cnt++) {
				if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial &&
					lpPlayInfo != &rsPlayInfo[cnt] &&
					rsPlayInfo[cnt].Position.Area == lpPlayInfo->Position.Area &&
					(rsPlayInfo[cnt].Position.Area != rsCASTLE_FIELD || (rsPlayInfo[cnt].dwClanCode && rsPlayInfo[cnt].dwClanCode == lpPlayInfo->dwClanCode)))
				{
					/*int Flag = 0;

					for (int cnt = 0; cnt < 6; cnt++)
					{
						if (lpPlayInfo->dwPartyObjectCode[cnt] == rsPlayInfo[cnt].dwObjectSerial)
						{
							Flag = 1;
						}
					}

					for (int cnt = 0; cnt < 6; cnt++)
					{
						if (lpPlayInfo->dwObjectSerial == rsPlayInfo[cnt].dwPartyObjectCode[cnt])
						{
							Flag = 1;
						}
					}

					if (Flag)
					{*/
					x = (lpPlayInfo->Position.x - rsPlayInfo[cnt].Position.x) >> FLOATNS;
					y = (lpPlayInfo->Position.y - rsPlayInfo[cnt].Position.y) >> FLOATNS;
					z = (lpPlayInfo->Position.z - rsPlayInfo[cnt].Position.z) >> FLOATNS;

					dist = x * x + z * z;
					if (dist < size && abs(y) < 80) {
						if (rsPlayInfo[cnt].dwSkill_TriumphOfValhalla_Time < dwPlayServTime) {
							rsPlayInfo[cnt].dwSkill_HallOfValhalla_Time = dwPlayServTime + Hall_Of_Valhalla_Time[point] * 1000;
							rsPlayInfo[cnt].wSkill_HallOfValhalla_Param[0] = Hall_Of_Valhalla_AddEvation[point] / 2;
							rsPlayInfo[cnt].wSkill_HallOfValhalla_Param[1] = (T_Of_Valhalla_Damage[lpTransCommand->SParam - 1] + lv) / 2;
							rsPlayInfo[cnt].lpsmSock->Send2((char*)lpTransCommand, lpTransCommand->size, TRUE);
						}
					}
					/*}*/
				}
			}
		}
		break;

	case SKILL_PLAY_FROST_JAVELIN:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA) {
			lpPlayInfo->dwSkill_FrostJavelin_Time = dwPlayServTime + Frost_Javelin_Time[point] * 1000;
			lpPlayInfo->dwSkill_FrostJavelin_Param = point;
		}
		break;

	case SKILL_PLAY_REGENERATION_FIELD:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) {
			lpPlayInfo->dwSkill_RegenerationField_Time = dwPlayServTime + Regeneration_Field_Time[point] * 1000;
		}
		break;

	case SKILL_PLAY_SUMMON_MUSPELL:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) {
			lpPlayInfo->dwSkill_SummonMuspell_Time = dwPlayServTime + Summon_Muspell_Time[point] * 1000;
			lpPlayInfo->dwSkill_SummonMuspell_Param = point;
		}
		break;

	case SKILL_PLAY_RAMIEL:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) {
			lpPlayInfo->dwSkill_SummonRamiel_Time = dwPlayServTime + Summon_Ramiel_Time[point] * 1000;
			lpPlayInfo->dwSkill_SummonRamiel_Param = point;
		}
		break;

	case SKILL_PLAY_FIRE_ELEMENTAL:
		if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) {
			lpChar = OpenMonsterFromSkill(dwSkillCode, lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, lpPlayInfo, 0);
			if (lpChar) {
				lpChar->dwUpdateCharInfoTime = dwPlayServTime + 355 * 1000;
				lpChar->smCharInfo.Attack_Damage[0] = Fire_Elemental_Damage[point][0];
				lpChar->smCharInfo.Attack_Damage[1] = Fire_Elemental_Damage[point][1];
				lpChar->smCharInfo.Attack_Rating = Fire_Elemental_Hit[point];
				lpChar->smCharInfo.Life[0] = Fire_Elemental_Life[point];
				lpChar->smCharInfo.Life[1] = Fire_Elemental_Life[point];

				lpChar->sMoveStepCount[0] = 1;
				lpChar->sMoveStepCount[1] = 2;
			}
		}
		break;
	}

	return TRUE;
}

int rsProcessAttack_SkillHolyReflection(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar)
{
	int pow;
	smTRANS_COMMAND	smTransCommand;
	int rs;

	if (!lpPlayInfo->dwSkill_HolyReflection_Time) return TRUE;

	if (lpPlayInfo->dwSkill_HolyReflection_Time < dwPlayServTime) {
		lpPlayInfo->dwSkill_HolyReflection_Time = 0;
		return TRUE;
	}

	if (lpChar->smCharInfo.Brood != smCHAR_MONSTER_UNDEAD) return TRUE;

	pow = GetRandomPos(lpChar->smCharInfo.Attack_Damage[0], lpChar->smCharInfo.Attack_Damage[1]);
	pow = (pow * lpPlayInfo->dwSkill_HolyReflection_Param) / 100;
	rs = lpChar->smCharInfo.Resistance[sITEMINFO_BIONIC];
	if (rs) {
		if (rs >= 100) rs = 100;
		if (rs <= -100) rs = -100;
		pow -= ((pow * rs) / 100);
	}
	pow -= (pow * lpChar->smCharInfo.Absorption) / 100;

	if (pow > 0) {
		lpChar->smCharInfo.Life[0] -= pow;

		if (lpChar->smCharInfo.Life[0] > 0) {
		}
		else {
			lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
			lpChar->lpExt2 = (void*)lpPlayInfo;
		}
	}

	if (lpPlayInfo->lpsmSock) {
		smTransCommand.code = smTRANSCODE_PROCESS_SKILL;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = SKILL_PLAY_HOLY_REFLECTION;
		smTransCommand.LParam = pow;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}

int rsClanUpdate(rsPLAYINFO* lpPlayInfo, TRANS_CLAN_COMMAND_USER* lpTransClanUser)
{
	rsCLAN_INFOMATION	ClanInfomation;
	smTRANS_COMMAND		smTransCommand;
	int	cnt;
	rsPLAYINFO* lpPlayInfo2;

	if (RecvClanCommand(lpTransClanUser, ClanInfomation.ClanUserInfo) == TRUE) {
		ZeroMemory(&smTransCommand, sizeof(smTRANS_COMMAND));
		smTransCommand.code = smTRANSCODE_CLAN_UPDATE;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.WParam = lpPlayInfo->dwObjectSerial;

		for (cnt = 0; cnt < lpTransClanUser->UserCount; cnt++) {
			lpPlayInfo2 = FindUserFromCodeName(ClanInfomation.ClanUserInfo[cnt].szName, ClanInfomation.ClanUserInfo[cnt].dwSpeedSum);
			if (lpPlayInfo2) {
				lpPlayInfo2->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
			}
		}
	}

	return TRUE;
}

int rsRecvYahooMotion(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	int cnt;
	STG_AREA* lpStgArea;
	smCHAR* lpCharList[srCLAN_MONSTER_MAX];
	int			ClanMonCount = 0;
	int			ClanPoint;
	int			x, y, z, dist;

	if (lpPlayInfo->dwClanCode && lpPlayInfo->Position.Area >= 0 && lpPlayInfo->Position.Area < STAGE_AREA_MAX) {
		lpStgArea = &StageArea[lpPlayInfo->Position.Area];

		for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++) {
			if (lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->smCharInfo.ClassClan == lpPlayInfo->smCharInfo.ClassClan) {
				if (ClanMonCount >= srCLAN_MONSTER_MAX) break;

				x = (lpPlayInfo->Position.x - lpStgArea->lpCharMonster[cnt]->pX) >> FLOATNS;
				y = (lpPlayInfo->Position.y - lpStgArea->lpCharMonster[cnt]->pY) >> FLOATNS;
				z = (lpPlayInfo->Position.z - lpStgArea->lpCharMonster[cnt]->pZ) >> FLOATNS;
				dist = x * x + y * y + z * z;

				if (dist < DIST_TRANSLEVEL_LOW)
					lpCharList[ClanMonCount++] = lpStgArea->lpCharMonster[cnt];
			}
		}

		if (ClanMonCount) {
			ClanPoint = (lpPlayInfo->smCharInfo.Level >> 2) / ClanMonCount;
			if (ClanPoint == 0) ClanPoint = 1;

			for (cnt = 0; cnt < ClanMonCount; cnt++) {
				if (lpCharList[cnt]->smCharInfo.Life[0] > 0) {
					lpCharList[cnt]->smCharInfo.Life[0] += ClanPoint;
					if (lpCharList[cnt]->smCharInfo.Life[0] > lpCharList[cnt]->smCharInfo.Life[1])
						lpCharList[cnt]->smCharInfo.Life[0] = lpCharList[cnt]->smCharInfo.Life[1];
				}
			}
		}
	}

	return TRUE;
}

smCHAR* rsFindAroundMonster(smCHAR* lpChar, int RoundDist)
{
	STG_AREA* lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;

	ddist2 = RoundDist * RoundDist;

	lpStgArea = (STG_AREA*)lpChar->lpExt4;
	if (lpStgArea) {
		for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++) {
			if (lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt] != lpChar &&
				!lpStgArea->lpCharMonster[cnt]->PlayHolyPower[1] &&
				lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0) {
				x = (lpStgArea->lpCharMonster[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->lpCharMonster[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->lpCharMonster[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + z * z;

				if (abs(y) < 80 && dist < ddist2) {
					return lpStgArea->lpCharMonster[cnt];
				}
			}
		}
	}

	return NULL;
}

smCHAR* rsSkillDamage_AroundMonster(smCHAR* lpChar)
{
	STG_AREA* lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;
	smCHAR* lpTargetChar;

	int RoundDist = lpChar->smMonsterInfo.SkillRange;
	int	pw, pow;

	ddist2 = RoundDist * RoundDist;
	pow = GetRandomPos(lpChar->smMonsterInfo.SkillDamage[0], lpChar->smMonsterInfo.SkillDamage[1]);

	lpStgArea = (STG_AREA*)lpChar->lpExt4;
	if (lpStgArea) {
		for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++) {
			if (lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt] != lpChar && lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0) {
				x = (lpStgArea->lpCharMonster[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->lpCharMonster[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->lpCharMonster[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + z * z;

				if (abs(y) < 80 && dist < ddist2) {
					lpTargetChar = lpStgArea->lpCharMonster[cnt];

					if (lpChar->smCharInfo.ClassClan != 0 && lpChar->smCharInfo.ClassClan == lpTargetChar->smCharInfo.ClassClan) {
						pw = 0;
					}
					else {
						pw = pow;
						pw -= (pow * lpTargetChar->smCharInfo.Absorption) / 100;
					}

					if (pw > 0) {
						lpTargetChar->smCharInfo.Life[0] -= pw;
						if (lpTargetChar->smCharInfo.Life[0] <= 0) {
							lpTargetChar->smCharInfo.Life[0] = 0;
							lpTargetChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
							if (lpChar->lpMasterPlayInfo && lpChar->lpMasterPlayInfo->lpsmSock && lpChar->lpMasterPlayInfo->dwObjectSerial && lpChar->lpMasterPlayInfo->dwObjectSerial == lpChar->smCharInfo.Next_Exp) {
								lpTargetChar->lpExt2 = lpChar->lpMasterPlayInfo;
								lpTargetChar->smMonsterInfo.GetExp >>= 1;
								lpTargetChar->lpExt3 = lpChar;
							}
							else {
								if (lpChar->lpMasterPlayInfo) {
									lpChar->smCharInfo.Life[0] = 0;
									lpChar->SetMotionFromCode(CHRMOTION_STATE_DEAD);
								}
								else {
									lpChar->lpTargetChar = 0;
								}
							}
						}
						else {
							if (lpTargetChar->MotionInfo->State != CHRMOTION_STATE_DEAD) {
								lpTargetChar->SetMotionFromCode(CHRMOTION_STATE_DAMAGE);
							}
						}
					}
				}
			}
		}
	}

	return NULL;
}

smCHAR* rsSkillMonster_AroundMonster(smCHAR* lpChar, int RoundDist)
{
	STG_AREA* lpStgArea;
	int cnt;
	int x, y, z, dist;
	int ddist2;
	smCHAR* lpTargetChar;

	ddist2 = RoundDist * RoundDist;

	lpStgArea = (STG_AREA*)lpChar->lpExt4;
	if (lpStgArea) {
		for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++) {
			if (lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt] != lpChar && lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0) {
				x = (lpStgArea->lpCharMonster[cnt]->pX - lpChar->pX) >> FLOATNS;
				y = (lpStgArea->lpCharMonster[cnt]->pY - lpChar->pY) >> FLOATNS;
				z = (lpStgArea->lpCharMonster[cnt]->pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + z * z;

				if (abs(y) < 80 && dist < ddist2) {
					if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_RATOO) {
						lpTargetChar = lpStgArea->lpCharMonster[cnt];
						lpTargetChar->PlayStunCount = 0;
					}
				}
			}
		}
	}

	return NULL;
}

int	rsSendMoneyToUser(rsPLAYINFO* lpPlayInfo, int Money)
{
	TRANS_ITEMINFO	TransItemInfo;

	ZeroMemory(&TransItemInfo, sizeof(TRANS_ITEMINFO));

	TransItemInfo.code = smTRANSCODE_PUTITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	TransItemInfo.Item.CODE = (sinGG1 | sin01);
	TransItemInfo.Item.Money = Money;
	wsprintf(TransItemInfo.Item.ItemName, sinGold, Money);
	ReformItem(&TransItemInfo.Item);

	lpPlayInfo->spMoney_Out += TransItemInfo.Item.Money;
	TransItemInfo.x = dwPlayServTime;
	TransItemInfo.y = TransItemInfo.Item.ItemHeader.dwChkSum;
	TransItemInfo.z = lpPlayInfo->spMoney_Out ^ (TransItemInfo.x + TransItemInfo.y);

	rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);

	lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);

	return TRUE;
}

int	rsPutItemToSystemLine(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode)
{
	smTRANS_SYSTEM_COMMAND	TransSystemCommand;
	smWINSOCK* lpsmSock;

	ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
	TransSystemCommand.code = smTRANSCODE_SYSTEM;
	TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
	TransSystemCommand.tCode = smTRANS_SYSCODE_GET_ITEM;
	TransSystemCommand.dwObjectSerial = rsServerConfig.ServerCode;
	TransSystemCommand.Param[0] = lpPlayInfo->dwObjectSerial;
	TransSystemCommand.Param[1] = dwItemCode;

	lpsmSock = rsFindNextSertoServerSock();

	if (lpsmSock)
		return lpsmSock->Send((char*)&TransSystemCommand, TransSystemCommand.size, TRUE);

	return FALSE;
}

int	rsSendMoneyToSystemLine(rsPLAYINFO* lpPlayInfo, int Money)
{
	smTRANS_SYSTEM_COMMAND	TransSystemCommand;
	smWINSOCK* lpsmSock;

	ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
	TransSystemCommand.code = smTRANSCODE_SYSTEM;
	TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
	TransSystemCommand.tCode = smTRANS_SYSCODE_GET_MONEY;
	TransSystemCommand.dwObjectSerial = rsServerConfig.ServerCode;
	TransSystemCommand.Param[0] = lpPlayInfo->dwObjectSerial;
	TransSystemCommand.Param[1] = Money;

	lpsmSock = rsFindNextSertoServerSock();

	if (lpsmSock)
		return lpsmSock->Send((char*)&TransSystemCommand, TransSystemCommand.size, TRUE);

	return FALSE;
}

int rsSendCharInfoToLoginServer(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_CHAR_COMMAND	smTransCharCommand;

	if (!dwSerToLogin_Count) return FALSE;

	smTransCharCommand.code = smTRANSCODE_SYSTEM;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND);
	smTransCharCommand.LParam = smTRANS_SYSCODE_CONNECT_USER;
	smTransCharCommand.WParam = lpPlayInfo->dwObjectSerial;
	smTransCharCommand.SParam = lpPlayInfo->dwCode_Name;
	lstrcpy(smTransCharCommand.szName, lpPlayInfo->smCharInfo.szName);

	return rsSendPacketToLoginLine((char*)&smTransCharCommand, smTransCharCommand.size);
}

int	rsGetSystemLineCount()
{
	int cnt;
	int	LineCount = 0;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].SystemLine)
			LineCount++;
	}

	return LineCount;
}

int	rsSetSerToLoginLine()
{
	int	cnt;

	dwSerToLogin_Count = 0;
	dwSerToLogin_Num = 0;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].SystemLine == 2) {
			if (dwSerToLogin_Count >= SER_TO_LOGIN_SOCKET_MAX) break;
			lpPlayInfo_LoginServer[dwSerToLogin_Count++] = &rsPlayInfo[cnt];
		}
	}

	return dwSerToLogin_Count;
}

int rsSendPacketToLoginLine(char* szBuff, int size)
{
	if (dwSerToLogin_Count == 0) return NULL;
	if (dwSerToLogin_Num >= dwSerToLogin_Count) dwSerToLogin_Num = 0;

	if (lpPlayInfo_LoginServer[dwSerToLogin_Num]->lpsmSock && lpPlayInfo_LoginServer[dwSerToLogin_Num]->SystemLine == 2) {
		return lpPlayInfo_LoginServer[dwSerToLogin_Num++]->lpsmSock->Send(szBuff, size, TRUE);
	}

	return FALSE;
}

int rsRecvSystemInfo(rsPLAYINFO* lpPlayInfo, void* Buff)
{
	smTRANS_SYSTEM_COMMAND* lpTransSystemCommand = (smTRANS_SYSTEM_COMMAND*)Buff;
	TRANS_KILL_MONSTER_INFO* lpTransKillMonInfo = (TRANS_KILL_MONSTER_INFO*)Buff;
	rsKILL_MONSTER_INFO* lpKillMonInfo = (rsKILL_MONSTER_INFO*)((char*)Buff + sizeof(TRANS_KILL_MONSTER_INFO));
	smTRANS_CHAR_COMMAND* lpCharCommand;
	smTRANS_COMMAND			smTransCommand;

	int cnt;
	DWORD	dwTime;
	rsPLAYINFO* lprsPlayInfo;

	if (!lpPlayInfo->SystemLine) {
		if (lpTransSystemCommand->tCode == smTRANS_SYSCODE_CONNECT) {
			if (rsCheckLoginServerIP(lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr) == TRUE) {
				lpPlayInfo->SystemLine = 2;
				rsSetSerToLoginLine();
			}
			else {
				if (!rsServerConfig.SystemIP_Count || rsCheckSystemIP(lpPlayInfo->lpsmSock->acc_sin.sin_addr.S_un.S_addr) == TRUE) {
					lpPlayInfo->SystemLine = 1;
				}
			}

			rsSystemLineConnCount++;
		}
		else {
			DisconnectUser(lpPlayInfo->lpsmSock);
		}
		return TRUE;
	}

	switch (lpTransSystemCommand->tCode) {
	case smTRANS_SYSCODE_KILL_MONSTER:

		for (cnt = 0; cnt < lpTransKillMonInfo->KillInfo_Count; cnt++) {
			rsOpen_MonsterItemExp(lpKillMonInfo);
			lpKillMonInfo++;
		}
		rsSystemLinePlayCount += lpTransKillMonInfo->KillInfo_Count;
		break;

	case smTRANS_SYSCODE_GET_MONEY:

		lprsPlayInfo = srFindUserFromSerial(lpTransSystemCommand->Param[0]);
		if (lprsPlayInfo)
			rsSendMoneyToUser(lprsPlayInfo, lpTransSystemCommand->Param[1]);
		break;

	case smTRANS_SYSCODE_GET_ITEM:

		lprsPlayInfo = srFindUserFromSerial(lpTransSystemCommand->Param[0]);
		if (lprsPlayInfo)
			rsPutItem(lprsPlayInfo, lpTransSystemCommand->Param[1]);
		break;

	case smTRANS_SYSCODE_DMG_USER_LIST:

		memcpy(&rsUserListDamageTop10, Buff, sizeof(rsUSER_LIST_TOP10));
		rsUserListDamageTop10.dwUpdateTime = dwPlayServTime;
		break;

	case smTRANS_SYSCODE_CONNECT_USER:

		lpCharCommand = (smTRANS_CHAR_COMMAND*)Buff;
		lprsPlayInfo = srFindUserFromSerial(lpCharCommand->WParam);
		if (lprsPlayInfo) {
			if (lprsPlayInfo->dwCode_Name == lpCharCommand->SParam &&
				lstrcmpi(lprsPlayInfo->szName, lpCharCommand->szName) == 0) {
				return TRUE;
			}
		}

		lpCharCommand->LParam = smTRANS_SYSCODE_USER_FAILED;
		lpPlayInfo->lpsmSock->Send((char*)Buff, lpCharCommand->size, TRUE);
		break;

	case smTRANS_SYSCODE_USER_FAILED:

		lpCharCommand = (smTRANS_CHAR_COMMAND*)Buff;
		lprsPlayInfo = srFindUserFromSerial(lpCharCommand->WParam);
		if (lprsPlayInfo) {
			if (lprsPlayInfo->dwCode_Name == lpCharCommand->SParam) {
				smTransCommand.WParam = 0;

				DisconnectUser(lprsPlayInfo->lpsmSock);
			}
		}
		break;

	case smTRANS_SYSCODE_NETSTATE:

		lpTransSystemCommand->tCode = smTRANS_SYSCODE_NETSUCCESS;
		lpTransSystemCommand->Param[0] = dwPlayServTime;
		lpPlayInfo->lpsmSock->Send((char*)lpTransSystemCommand, lpTransSystemCommand->size, TRUE);

		rsSystemNetCount++;
		break;

	case smTRANS_SYSCODE_NETSUCCESS:

		lpPlayInfo->lpsmSock->dwDeadLockTime = GetCurrentTime();

		if (!dwOffsetTime)
			dwOffsetTime = dwPlayServTime - lpTransSystemCommand->Param[0];
		else {
			dwTime = dwPlayServTime - lpTransSystemCommand->Param[0];
			if (abs((double)dwTime - dwOffsetTime) > 1000 * 30) {
				dwOffsetTime = dwTime;
			}
		}
		rsSystemNetCount++;

		break;
	}

	return TRUE;
}

int	rsPushKillMonster(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo, STG_AREA* lpStgArea)
{
	int cnt;

	if (!dwSerToSerIP) return FALSE;

	if ((rsKillMonster_Push - rsKillMonster_Pop) >= srMONSTER_KILL_QUE_MASK) {
		return TRUE;
	}

	cnt = rsKillMonster_Push & srMONSTER_KILL_QUE_MASK;

	rsKillMonster_Que[cnt].dwAutoCharCode = lpChar->smMonsterInfo.dwAutoCharCode;
	rsKillMonster_Que[cnt].dwCharSoundCode = lpChar->smCharInfo.dwCharSoundCode;
	rsKillMonster_Que[cnt].dwMonObjectSerial = lpChar->dwObjectSerial;

	rsKillMonster_Que[cnt].x = lpChar->pX;
	rsKillMonster_Que[cnt].y = lpChar->pY;
	rsKillMonster_Que[cnt].z = lpChar->pZ;

	rsKillMonster_Que[cnt].PartyFlag = lpChar->PartyFlag;

	if (lpPlayInfo)
		rsKillMonster_Que[cnt].dwUserObjectSerial = lpPlayInfo->dwObjectSerial;
	else
		rsKillMonster_Que[cnt].dwUserObjectSerial = 0;

	if (lpStgArea && lpStgArea->lpField)
		rsKillMonster_Que[cnt].Area = lpStgArea->lpField->FieldCode;
	else
		rsKillMonster_Que[cnt].Area = -1;

	rsKillMonster_Que[cnt].dwParam[0] = 0;
	rsKillMonster_Que[cnt].dwParam[1] = 0;
	rsKillMonster_Que[cnt].dwParam[2] = 0;
	rsKillMonster_Que[cnt].dwParam[3] = 0;

	if (rsKillMonster_Que[cnt].PartyFlag == rsHARDCORE_EVENT_FLAG) {
		rsKillMonster_Que[cnt].dwParam[0] = lpChar->PartyParam;
	}

	rsKillMonster_Push++;

	return TRUE;
}

int	rsSendKillMonsterInfo(smWINSOCK* lpsmSock)
{
	char	szBuff[4096];
	TRANS_KILL_MONSTER_INFO* lpTransKillMonInfo = (TRANS_KILL_MONSTER_INFO*)szBuff;
	rsKILL_MONSTER_INFO* lpKillMonInfo = (rsKILL_MONSTER_INFO*)(szBuff + sizeof(TRANS_KILL_MONSTER_INFO));

	int	cnt, mCnt;

	mCnt = 0;

	while (1) {
		if (rsKillMonster_Pop == rsKillMonster_Push) break;
		if (mCnt > 48) break;

		cnt = rsKillMonster_Pop & srMONSTER_KILL_QUE_MASK;

		memcpy(lpKillMonInfo, &rsKillMonster_Que[cnt], sizeof(rsKILL_MONSTER_INFO));

		lpKillMonInfo++;
		rsKillMonster_Pop++;
		mCnt++;
	}

	if (!mCnt) return FALSE;

	lpTransKillMonInfo->size = sizeof(TRANS_KILL_MONSTER_INFO) + sizeof(rsKILL_MONSTER_INFO) * mCnt;
	lpTransKillMonInfo->code = smTRANSCODE_SYSTEM;
	lpTransKillMonInfo->tCode = smTRANS_SYSCODE_KILL_MONSTER;
	lpTransKillMonInfo->KillInfo_Count = mCnt;
	lpTransKillMonInfo->Temp[0] = 0;
	lpTransKillMonInfo->Temp[1] = 0;
	lpTransKillMonInfo->Temp[2] = 0;
	lpTransKillMonInfo->Temp[3] = 0;

	if (lpsmSock) lpsmSock->Send((char*)lpTransKillMonInfo, lpTransKillMonInfo->size, TRUE);

	return mCnt;
}

smWINSOCK* rsFindNextSertoServerSock()
{
	int cnt;
	smWINSOCK* lpsmSock;

	for (cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++) {
		lpsmSock = lpsmSock_SerToServer[(cnt + dwSerToSer_Count) & SER_TO_SERVER_SOCKET_MASK];
		if (lpsmSock) return lpsmSock;
	}

	return NULL;
}

DWORD WINAPI rsTransServerMain_Thread(void* pInfo)
{
	HANDLE	hThread;
	DWORD	dwTime;
	int		cnt;
	int		Count;
	smWINSOCK* lpsmSock;
	smTRANS_SYSTEM_COMMAND	TransSystemCommand;
	rsPLAYINFO* lpPlayInfo;

	hThread = GetCurrentThread();
	dwTime = GetCurrentTime();
	Count = 0;

	while (1) {
		Sleep(200);
		if (quit) break;
		if (!dwSerToSerIP) continue;

		EnterCriticalSection(&cSerSection);

		for (cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++) {
			if (!lpsmSock_SerToServer[cnt] || lpsmSock_SerToServer[cnt]->acc_sin.sin_addr.S_un.S_addr != dwSerToSerIP) {
				LeaveCriticalSection(&cSerSection);
				lpsmSock = smConnectSock3(szSerToSerIP, TCP_SERVPORT);
				if (quit) goto quit_thread;

				if (lpsmSock) Serv_ConnectPlayer(lpsmSock);

				EnterCriticalSection(&cSerSection);

				if (lpsmSock) {
					rsSystemLineConnCount++;

					if (lpsmSock_SerToServer[cnt]) {
						DisconnectUser(lpsmSock_SerToServer[cnt]);
					}
					lpsmSock_SerToServer[cnt] = lpsmSock;

					lpPlayInfo = (rsPLAYINFO*)lpsmSock->ExtData1;
					if (lpPlayInfo) lpPlayInfo->SystemLine = TRUE;

					ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
					TransSystemCommand.code = smTRANSCODE_SYSTEM;
					TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
					TransSystemCommand.tCode = smTRANS_SYSCODE_CONNECT;
					TransSystemCommand.dwObjectSerial = rsServerConfig.ServerCode;
					lpsmSock->Send((char*)&TransSystemCommand, TransSystemCommand.size, TRUE);
				}
			}
		}

		dwTime = GetCurrentTime();

		if ((Count & 0x1F) == 0) {
			ZeroMemory(&TransSystemCommand, sizeof(smTRANS_SYSTEM_COMMAND));
			TransSystemCommand.code = smTRANSCODE_SYSTEM;
			TransSystemCommand.size = sizeof(smTRANS_SYSTEM_COMMAND);
			TransSystemCommand.tCode = smTRANS_SYSCODE_NETSTATE;

			for (cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++) {
				if (lpsmSock_SerToServer[cnt]) {
					if ((lpsmSock_SerToServer[cnt]->dwDeadLockTime + (1000 * 45)) < dwTime) {
						DisconnectUser(lpsmSock_SerToServer[cnt]);
						lpsmSock_SerToServer[cnt] = 0;
						rsSystemLineFailedCount++;
					}
					else {
						lpsmSock_SerToServer[cnt]->Send((char*)&TransSystemCommand, TransSystemCommand.size, TRUE);
					}
				}
			}
		}

		for (cnt = 0; cnt < 32; cnt++) {
			lpsmSock = rsFindNextSertoServerSock();
			if (!lpsmSock || rsSendKillMonsterInfo(lpsmSock) == FALSE) break;
			dwSerToSer_Count++;
		}

		LeaveCriticalSection(&cSerSection);

		Count++;
	}

quit_thread:

	ExitThread(TRUE);
	return TRUE;
}

int rsInit_SerToServer()
{
	if (!dwPlayServTime) return FALSE;
	if (rsServerConfig.szLinkServerIP[0]) {
		if (!hSerToServer_Thread) {
			hSerToServer_Thread = CreateThread(NULL, 0, rsTransServerMain_Thread, 0, 0, &dwSerToServer_ID);
		}

		lstrcpy(szSerToSerIP, rsServerConfig.szLinkServerIP);
		dwSerToSerIP = inet_addr(szSerToSerIP);
	}
	else {
		dwSerToSerIP = 0;
		szSerToSerIP[0] = 0;
	}

	return TRUE;
}

int	rsDisconnectSystemLine(smWINSOCK* lpsmSock)
{
	int cnt;

	for (cnt = 0; cnt < SER_TO_SERVER_SOCKET_MAX; cnt++) {
		if (lpsmSock_SerToServer[cnt] == lpsmSock) {
			lpsmSock_SerToServer[cnt] = 0;
			return TRUE;
		}
	}

	return FALSE;
}

int	rsSaveAdminCommand(rsPLAYINFO* lpPlayInfo, char* szChatCommand, int Level)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		len;

	if (!lpPlayInfo->lpsmSock) return FALSE;

	CreateDirectory(AdminLogDirectory, NULL);

	GetLocalTime(&st);

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) AdminLv( %d )> %s\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->lpsmSock->szIPAddr, Level, szChatCommand);

	len = lstrlen(szBuff);

#ifdef _LANGUAGE_KOREAN
	wsprintf(szFileName, "%s\\(Admin)%d-%d.xog", AdminLogDirectory, st.wMonth, st.wDay);
	for (int cnt = 0; cnt < len; cnt++) {
		szBuff[cnt] = szBuff[cnt] ^ 0x55;
	}
#else
	wsprintf(szFileName, "%s\\(Admin)%d-%d.log", AdminLogDirectory, st.wMonth, st.wDay);
#endif

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int	rsRecordAdminCommand(rsPLAYINFO* lpPlayInfo, char* szChatCommand, int Level)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if (!rsServerConfig.RecordAdminCommand) return FALSE;
	if (Level > rsServerConfig.RecordAdminCommand) return FALSE;

	if (LoginServer) {
		rsSaveAdminCommand(lpPlayInfo, szChatCommand, lpPlayInfo->AdminMode);
		return TRUE;
	}

	lstrcpy(TransChatMessage.szMessage, szChatCommand);
	TransChatMessage.dwIP = lpPlayInfo->AdminMode;
	TransChatMessage.dwObjectSerial = lpPlayInfo->dwObjectSerial;
	TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
	TransChatMessage.code = smTRANSCODE_REC_ADMIN_COMMAND;

	return rsSendDataServer(lpPlayInfo->lpsmSock, &TransChatMessage);
}

int	rsCheckAdminPlayer(rsPLAYINFO* lpPlayInfo)
{
	int cnt;
	smWINSOCK* lpsmSock = lpPlayInfo->lpsmSock;

	if (!lpPlayInfo->AdminIP) {
		RecordDebugPlayLogFile(lpPlayInfo);

		if (rsServerConfig.DebugIP_Count > 0) {
			for (cnt = 0; cnt < rsServerConfig.DebugIP_Count; cnt++) {
				if (strstr(lpsmSock->szIPAddr, rsServerConfig.szDebugIP[cnt]) != 0) {
					break;
				}
			}

			if (cnt < rsServerConfig.DebugIP_Count) {
				return TRUE;
			}
			else {
				if (!lpPlayInfo->BlockTime)
					lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szID, 1000 * 60 * 60 * 24);

				DisconnectUser(lpsmSock);
				return FALSE;
			}
		}

		if (rsServerConfig.DebugID_Count > 0) {
			for (cnt = 0; cnt < rsServerConfig.DebugID_Count; cnt++) {
				if (lstrcmpi(lpPlayInfo->szID, rsServerConfig.szDebugID[cnt]) == 0) {
					break;
				}
			}

			if (cnt < rsServerConfig.DebugID_Count) {
				return TRUE;;
			}
			else {
				if (!lpPlayInfo->BlockTime)
					lpPlayInfo->BlockTime = rsAddBackListID(lpPlayInfo->szID, 1000 * 60 * 60 * 24);

				DisconnectUser(lpsmSock);
				return FALSE;
			}
		}
	}

	return TRUE;
}

int	rsClanMoneyLog(rsPLAYINFO* lpPlayInfo, int Money, int RestMoney)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	int		len;

	if (!lpPlayInfo->lpsmSock) return FALSE;

	CreateDirectory(HackLogDirectory, NULL);

	GetLocalTime(&st);

	wsprintf(szBuff, "%d:%d:%d - ID( %s ) Name( %s ) IP( %s ) Money( %d ) RestMoney( %d )\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->szID, lpPlayInfo->szName, lpPlayInfo->lpsmSock->szIPAddr, Money, RestMoney);

	len = lstrlen(szBuff);

	wsprintf(szFileName, "%s\\(ClanMoney)%d-%d.log", HackLogDirectory, st.wMonth, st.wDay);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

static int	TestStarPoint = 0;
#define	STAR_POINT_PRICE	100000

int rsRecvStarPoint(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	int cnt;
	int InvFlag;
	int	StarPoint = 0;
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpTransCommand->WParam > 0) {
		StarPoint = lpTransCommand->WParam / STAR_POINT_PRICE;

		if (lpTransCommand->LParam) {
			if (lpPlayInfo->ServerMoney < lpTransCommand->WParam) {
				return FALSE;
			}

			lpPlayInfo->SubServerMoney(lpTransCommand->WParam, WHERE_STAR_POINT);

			rsRecord_ItemLog2(lpPlayInfo, sinGG1 | sin01, lpTransCommand->WParam, 0, ITEMLOG_BUYSTAR);
		}
		else {
			InvFlag = 0;

			for (cnt = 0; cnt < INVEN_ITEM_INFO_MAX; cnt++) {
				if (lpPlayInfo->InvenItemInfo[cnt].dwCode == (sinGF1 | sin01)) {
					rsRecord_ItemLog2(lpPlayInfo, lpPlayInfo->InvenItemInfo[cnt].dwCode,
						lpPlayInfo->InvenItemInfo[cnt].dwKey, lpPlayInfo->InvenItemInfo[cnt].dwSum, ITEMLOG_BUYSTAR);

					lpPlayInfo->InvenItemInfo[cnt].dwCode = 0;
					InvFlag++;
				}
			}
			if (InvFlag == 0) return FALSE;
		}

		if (bSql_StarPoint(lpPlayInfo, StarPoint, lpTransCommand->LParam) == FALSE) {
			TestStarPoint += lpTransCommand->WParam / STAR_POINT_PRICE;
			lpTransCommand->WParam = TestStarPoint;

			if (lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send2((char*)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}

		if (StarPoint > 0) {
			TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = 0;
			wsprintf(TransChatMessage.szMessage, srMsg_400, StarPoint);
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		}
	}
	else {
		if (bSql_StarPoint(lpPlayInfo, StarPoint, lpTransCommand->LParam) == FALSE) {
			lpTransCommand->WParam = TestStarPoint;
			if (lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send2((char*)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}
	}

	return TRUE;
}

static int	TestSodClanCash = 0;

int rsRecvSodClanCash(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	int cash, kind;

	cash = lpTransCommand->WParam;
	kind = lpTransCommand->SParam;

	if (cash > 0) {
		if (bSql_ClanMoney(lpPlayInfo, cash, 1, kind) == FALSE) {
			if (lpPlayInfo->AdminMode) {
				if (TestSodClanCash < cash) {
					return FALSE;
				}

				lpPlayInfo->AddServerMoney(cash, WHERE_CLAN_MONEY);
				TestSodClanCash -= cash;

				lpTransCommand->WParam = TestSodClanCash;
				lpTransCommand->LParam = cash;

				rsClanMoneyLog(lpPlayInfo, cash, TestSodClanCash);

				if (lpPlayInfo->lpsmSock)
					lpPlayInfo->lpsmSock->Send2((char*)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
			}
		}
	}
	else {
		if (bSql_ClanMoney(lpPlayInfo, 0, 0, kind) == FALSE) {
			lpTransCommand->WParam = TestSodClanCash;
			lpTransCommand->LParam = 0;
			if (lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send2((char*)lpTransCommand, sizeof(smTRANS_COMMAND), TRUE);
		}
	}

	return TRUE;
}

int rsRecvGiveMoney(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpTransCommand->WParam > 0) {
		if (lpPlayInfo->ServerMoney < lpTransCommand->WParam) {
			return FALSE;
		}
		lpPlayInfo->SubServerMoney(lpTransCommand->WParam, WHERE_GIVE_MONEY);

		bSql_GiveMoney(lpPlayInfo, lpTransCommand->WParam);

		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
		TransChatMessage.dwIP = 0;
		TransChatMessage.dwObjectSerial = 0;
		wsprintf(TransChatMessage.szMessage, srMsg_401, lpTransCommand->WParam);
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
	}

	return TRUE;
}

int rsRecvPaymentMoney(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	if (lpTransCommand->LParam < 0 || lpTransCommand->LParam>1000000) return FALSE;

	switch (lpTransCommand->WParam) {
	case 1:
		CurrencyLog.int64_LearnSkillMoney += lpTransCommand->LParam;
		lpPlayInfo->SubServerMoney(lpTransCommand->LParam, WHERE_LEARNSKILL);
		break;
	case 2:
		CurrencyLog.int64_WarpgateMoney += lpTransCommand->LParam;
		lpPlayInfo->SubServerMoney(lpTransCommand->LParam, WHERE_WARPGATE);
		break;
	}

	return TRUE;
}

int rsEventLogOn_Sucess(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	if ((lpPlayInfo->Bl_Meter & BIMASK_BIRTHDAY_USER) != 0) {
		if (rsServerConfig.Event_ComicBirthDay == 1) {
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_COMIC_SKIN;
			smTransCommand.WParam = (rand() % 2) + 1;
			smTransCommand.LParam = 60 * 24 * 6;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = 0;
			lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
		}
	}

	if ((lpPlayInfo->Bl_Meter & BIMASK_VIP_USER) != 0) {
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_CHANGE_EVENT;
		smTransCommand.WParam = lpPlayInfo->Bl_Meter;
		smTransCommand.LParam = lpPlayInfo->Bl_RNo;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 1;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
	}

	return TRUE;
}

struct	sPUZZLE_ITEM {
	DWORD	dwItemCode;
	int		Percent;
};

sPUZZLE_ITEM	sPuzzleItem[] = {
	{	(sinPZ1 | sin01)	,	        743	},
	{	(sinPZ1 | sin02)	,	       1466	},
	{	(sinPZ1 | sin03)	,	       2170	},

	{	(sinPZ2 | sin01)	,	       2913	},
	{	(sinPZ2 | sin02)	,	       3636	},
	{	(sinPZ2 | sin03)	,	       4340	},

	{	(sinPZ1 | sin04)	,	       4990	},
	{	(sinPZ1 | sin05)	,	       5290	},
	{	(sinPZ2 | sin04)	,	       5940	},
	{	(sinPZ2 | sin05)	,	       6240	},

	{	(sinPZ1 | sin05)	,	       6590	},
	{	(sinPZ1 | sin06)	,	       6940	},
	{	(sinPZ2 | sin05)	,	       7290	},
	{	(sinPZ2 | sin06)	,	       7640 },

	{	(sinPZ1 | sin06)	,	       7940	},
	{	(sinPZ1 | sin07)	,	       8320	},
	{	(sinPZ2 | sin06)	,	       8620	},
	{	(sinPZ2 | sin07)	,	       9000	},

	{	(sinPZ1 | sin08)	,	       9500	},
	{	(sinPZ2 | sin08)	,	       10000},
	{	0,0	}
};

DWORD rsOpenEventPuzzleItem(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar)
{
	int	cnt;
	int	rnd;

	if (abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level) > 15)
		return NULL;

	if (lpChar->smCharInfo.Level < 20 && abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level)>8)
		return NULL;

	if (lpChar->PartyFlag == rsHARDCORE_EVENT_FLAG) return NULL;

	rnd = rand() % 10000;

	cnt = 0;
	while (1) {
		if (!sPuzzleItem[cnt].dwItemCode) break;

		if (rnd < sPuzzleItem[cnt].Percent)
			return sPuzzleItem[cnt].dwItemCode;

		cnt++;
	}

	return NULL;
}

int rsDebugMessageToClient(rsPLAYINFO* lpPlayInfo, char* szDmgMsg)
{
	TRANS_CHATMESSAGE	TransChatMessage;

	if (lpPlayInfo->AdminMode <= 2) return FALSE;

	lstrcpy(TransChatMessage.szMessage, szDmgMsg);
	TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
	TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
	TransChatMessage.dwIP = 0;
	TransChatMessage.dwObjectSerial = 0;
	lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

	return TRUE;
}

int	rsTrade_PersonalShop(rsPLAYINFO* lpPlayInfo, rsPLAYINFO* lpPlayInfo2, smTRANS_COMMAND_BUFF* lpTransCommandBuff)
{
	sMYSHOP_ITEM_SERVER* lpMyShopItem = (sMYSHOP_ITEM_SERVER*)lpTransCommandBuff->Buff;
	int	cnt, mCnt;
	int PotionFlag;

#ifdef _TEST_SERVER
	char szBuff[256];
#endif

	switch (lpMyShopItem->SendFlag) {
	case 1:
		if (lpMyShopItem->Price > 1000000000) return FALSE;
		if (lpPlayInfo->dwMyShopTradeTime > dwPlayServTime) {
#ifdef _TEST_SERVER

			rsDebugMessageToClient(lpPlayInfo, "> °³ÀÎ»óÁ¡ ±¸ÀÔ ´ë±â ¿À·ù");
#endif
			return FALSE;
		}

		PotionFlag = TRUE;

		if ((lpMyShopItem->CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
			if (rsGetServerPotion(lpPlayInfo2, lpMyShopItem->CODE) < (int)lpMyShopItem->sTime) {
				PotionFlag = FALSE;
			}
		}
#ifdef _TEST_SERVER

		rsDebugMessageToClient(lpPlayInfo, "> °³ÀÎ»óÁ¡ ±¸ÀÔ ½ÅÃ»");

		wsprintf(szBuff, "> °³ÀÎ»óÁ¡ ±¸ÀÔ ½ÅÃ» ( %d %d )", lpPlayInfo->dwMyShopTradeTime / 1000, dwPlayServTime / 1000);
		rsDebugMessageToClient(lpPlayInfo, szBuff);

#endif

		if (rsFindInvenItem(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum) >= 0 &&
			lpPlayInfo->ServerMoney >= (int)lpMyShopItem->Price && PotionFlag == TRUE)
		{
			lpPlayInfo->dwMyShopTradeTime = dwPlayServTime + 500;
#ifdef _TEST_SERVER

			wsprintf(szBuff, "> °³ÀÎ»óÁ¡ ±¸ÀÔ ´ë±â ( %d %d )", lpPlayInfo->dwMyShopTradeTime / 1000, dwPlayServTime / 1000);
			rsDebugMessageToClient(lpPlayInfo, szBuff);
#endif

			if (lpPlayInfo->MyShopListCount == 0) {
				ZeroMemory(lpPlayInfo->sMyShopList, sizeof(sMYSHOP_SELL_INFO) * MYSHOP_LIST_MAX);
			}
			else {
				for (cnt = 0; cnt < MYSHOP_LIST_MAX; cnt++) {
					if (lpPlayInfo->sMyShopList[cnt].dwCode &&
						lpMyShopItem->CODE == lpPlayInfo->sMyShopList[cnt].dwCode &&
						lpMyShopItem->Head == lpPlayInfo->sMyShopList[cnt].dwHead &&
						lpMyShopItem->CkSum == lpPlayInfo->sMyShopList[cnt].dwChkSum &&
						lpMyShopItem->Price == lpPlayInfo->sMyShopList[cnt].Price) {
						return TRUE;
					}
				}
			}

			mCnt = lpPlayInfo->MyShopListCount & MYSHOP_LIST_MASK;
			lpPlayInfo->sMyShopList[mCnt].dwCode = lpMyShopItem->CODE;
			lpPlayInfo->sMyShopList[mCnt].dwHead = lpMyShopItem->Head;
			lpPlayInfo->sMyShopList[mCnt].dwChkSum = lpMyShopItem->CkSum;
			lpPlayInfo->sMyShopList[mCnt].Price = lpMyShopItem->Price;
			lpPlayInfo->sMyShopList[mCnt].KindCurrency = lpMyShopItem->KindCurrency;

			lpPlayInfo->MyShopListCount++;
			return TRUE;
		}

		if (lpPlayInfo->ServerMoney >= (int)lpMyShopItem->Price) {
			lpTransCommandBuff->smTransCommand.LParam = lpPlayInfo2->dwObjectSerial;
			lpTransCommandBuff->smTransCommand.SParam = lpPlayInfo->dwObjectSerial;
			lpMyShopItem->SendFlag = 3;
			if (lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send2((char*)lpTransCommandBuff, lpTransCommandBuff->smTransCommand.size, TRUE);
		}

		return FALSE;

	case 2:
		if (lpMyShopItem->Price > 1000000000) return FALSE;

		for (cnt = 0; cnt < MYSHOP_LIST_MAX; cnt++) {
			if (lpPlayInfo2->sMyShopList[cnt].dwCode &&
				lpMyShopItem->CODE == lpPlayInfo2->sMyShopList[cnt].dwCode &&
				lpMyShopItem->Head == lpPlayInfo2->sMyShopList[cnt].dwHead &&
				lpMyShopItem->CkSum == lpPlayInfo2->sMyShopList[cnt].dwChkSum &&
				lpMyShopItem->Price == lpPlayInfo2->sMyShopList[cnt].Price)
			{
				if (lpMyShopItem->KindCurrency == 1) {
					if (CoinShop::GetInstance()->GetUserCoin(lpPlayInfo2) >= (int)lpMyShopItem->Price) {
						if ((lpMyShopItem->CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
							if (rsAddServerPotion(lpPlayInfo, lpMyShopItem->CODE, -(int)(lpMyShopItem->sTime)) < 0) {
								rsServerPotionErrorLog(lpPlayInfo, lpMyShopItem->CODE, -(int)lpMyShopItem->sTime, 310);
								return FALSE;
							}
							rsAddServerPotion(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->sTime);
						}

						if (rsDeleteInvenItem(lpPlayInfo, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum) >= 0) {
							CoinShop::GetInstance()->SubCoin(lpPlayInfo2, lpMyShopItem->Price);
							CoinShop::GetInstance()->AddCoin(lpPlayInfo, lpMyShopItem->Price);

							rsAddInvenItem(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum);

							if ((lpMyShopItem->CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
								rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2,
									lpMyShopItem->CODE, lpMyShopItem->sTime, 0,
									lpMyShopItem->Price);
							}
							else {
								rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2,
									lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum,
									lpMyShopItem->Price);
							}

							TRANS_CHATMESSAGE	TransChatMessage;
							TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
							TransChatMessage.dwIP = 6;
							wsprintf(TransChatMessage.szMessage, "%s comprou %s do vendedor %s por %d créditos", lpPlayInfo2->szName, lpMyShopItem->szName, lpPlayInfo->szName, lpMyShopItem->Price);
							TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
							TransChatMessage.dwObjectSerial = 0;
							lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
							lpPlayInfo2->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

							return TRUE;
						}
					}
				}
				else if (lpPlayInfo2->ServerMoney >= (int)lpMyShopItem->Price) {
					if ((lpMyShopItem->CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
						if (rsAddServerPotion(lpPlayInfo, lpMyShopItem->CODE, -(int)(lpMyShopItem->sTime)) < 0) {
							rsServerPotionErrorLog(lpPlayInfo, lpMyShopItem->CODE, -(int)lpMyShopItem->sTime, 310);
							return FALSE;
						}
						rsAddServerPotion(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->sTime);
					}

					if (rsDeleteInvenItem(lpPlayInfo, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum) >= 0) {
						lpPlayInfo2->SubServerMoney(lpMyShopItem->Price, WHERE_PERSONAL_SHOP);
						lpPlayInfo->AddServerMoney(lpMyShopItem->Price, WHERE_PERSONAL_SHOP);

						rsAddInvenItem(lpPlayInfo2, lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum);

						if ((lpMyShopItem->CODE & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1)) {
							rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2,
								lpMyShopItem->CODE, lpMyShopItem->sTime, 0,
								lpMyShopItem->Price);
						}
						else {
							rsRecord_ItemLog_MyShop(lpPlayInfo, lpPlayInfo2,
								lpMyShopItem->CODE, lpMyShopItem->Head, lpMyShopItem->CkSum,
								lpMyShopItem->Price);
						}

						TRANS_CHATMESSAGE	TransChatMessage;
						TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
						TransChatMessage.dwIP = 6;
						wsprintf(TransChatMessage.szMessage, "%s comprou %s do vendedor %s por %d ouro", lpPlayInfo2->szName, lpMyShopItem->szName, lpPlayInfo->szName, lpMyShopItem->Price);
						TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
						TransChatMessage.dwObjectSerial = 0;
						lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
						lpPlayInfo2->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);

						return TRUE;
					}
				}
				break;
			}
		}
		return FALSE;
	}

#ifdef _TEST_SERVER

	wsprintf(szBuff, "> °³ÀÎ»óÁ¡ ¸Þ¼¼Áö ( %d )", lpMyShopItem->SendFlag);
	rsDebugMessageToClient(lpPlayInfo2, szBuff);
#endif

	return TRUE;
}

int	rsUseLovelyItem(rsPLAYINFO* lpPlayInfo, DWORD	dwItemCode)
{
	int	JobCode;
	int Level = 0;
	smTRANS_COMMAND	smTransCommand;

	JobCode = lpPlayInfo->smCharInfo.JOB_CODE;

	switch (dwItemCode) {
	case (sinCH1 | sin01):

#ifdef _LANGUAGE_ENGLISH
		if (JobCode != JOBCODE_ATALANTA && JobCode != JOBCODE_ARCHER && JobCode != JOBCODE_PRIESTESS) return FALSE;
		Level = 10;
#else
		if (JobCode == JOBCODE_ATALANTA || JobCode == JOBCODE_ARCHER || JobCode == JOBCODE_PRIESTESS || JobCode == JOBCODE_ASSASSINE || JobCode == JOBCODE_MARTIAL) return FALSE;
		Level = 4;
#endif
		break;

	case (sinCH1 | sin02):

#ifdef _LANGUAGE_ENGLISH
		if (JobCode == JOBCODE_ATALANTA || JobCode == JOBCODE_ARCHER || JobCode == JOBCODE_PRIESTESS) return FALSE;
		Level = 10;
#else
		if (JobCode == JOBCODE_ATALANTA || JobCode == JOBCODE_ARCHER || JobCode == JOBCODE_PRIESTESS || JobCode == JOBCODE_ASSASSINE || JobCode == JOBCODE_MARTIAL) return FALSE;
		Level = 8;
#endif

		break;

	case (sinCH1 | sin03):
		if (JobCode != JOBCODE_ATALANTA && JobCode != JOBCODE_ARCHER && JobCode != JOBCODE_PRIESTESS && JobCode != JOBCODE_ASSASSINE && JobCode != JOBCODE_MARTIAL) return FALSE;
		Level = 4;
		break;

	case (sinCH1 | sin04):
		if (JobCode != JOBCODE_ATALANTA && JobCode != JOBCODE_ARCHER && JobCode != JOBCODE_PRIESTESS && JobCode != JOBCODE_ASSASSINE && JobCode != JOBCODE_MARTIAL) return FALSE;
		Level = 8;
		break;
	}

	if (Level == 0) return FALSE;

	smTransCommand.code = smTRANSCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_LOVELY_LIFE;
	smTransCommand.LParam = lpPlayInfo->dwObjectSerial;
	smTransCommand.SParam = 0;
	smTransCommand.EParam = 0;

	lpPlayInfo->dwSkill_VirtualLife_Time = dwPlayServTime + Virtual_Life_Time[Level - 1] * 1000;
	lpPlayInfo->dwSkill_VirtualLife_Param = Virtual_Life_Percent[Level - 1];
	smTransCommand.WParam |= (Level << 8);
	rsSendCommandUser2(lpPlayInfo, &smTransCommand);

	return TRUE;
}

static int	Babel_LifeRegenTable[10][2] = {
	{	1800	,	2300	},
	{	1900	,	2400	},
	{	2000	,	2550	},
	{	2150	,	2650	},
	{	2300	,	2800	},
	{	2400	,	2900	},
	{	2500	,	3000	},
	{	2600	,	3100	},
	{	2700	,	3200	},
	{	2800	,	3300	}
};

int rsGetMonsterLifeRegen(smCHAR* lpChar)
{
	int cnt;
	rsPLAYINFO* lpPlayInfo;
	STG_AREA* lpStgArea = (STG_AREA*)lpChar->lpExt1;
	int x, y, z, dist;
	int NearUserCnt;
	int dRange;
	rsPLAYINFO* lpDebugPlayInfo = 0;
	int	RegenLife;

	if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_BABEL) {
		dRange = 260 * 260;
		NearUserCnt = 0;

		for (cnt = 0; cnt < CONNECTMAX; cnt++) {
			lpPlayInfo = &rsPlayInfo[cnt];
			if (lpPlayInfo->lpsmSock && lpPlayInfo->dwObjectSerial && lpPlayInfo->Position.Area == lpStgArea->lpField->FieldCode) {
				x = (lpChar->pX - lpPlayInfo->Position.x) >> FLOATNS;
				y = (lpChar->pY - lpPlayInfo->Position.y) >> FLOATNS;
				z = (lpChar->pZ - lpPlayInfo->Position.z) >> FLOATNS;
				dist = x * x + z * z;

				if (abs(y) < 60 && dist < dRange && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
					NearUserCnt++;

					if (lpPlayInfo->AdminMode >= 3)
						lpDebugPlayInfo = lpPlayInfo;
				}
			}
		}

		cnt = 0;
		if (NearUserCnt > 6) {
			if (NearUserCnt > 15)
				cnt = 9;
			else
				cnt = NearUserCnt - 6;
		}

		if (lpChar->smCharInfo.Life[0] < (lpChar->smCharInfo.Life[1] / 5))
			RegenLife = Babel_LifeRegenTable[cnt][1];
		else
			RegenLife = Babel_LifeRegenTable[cnt][0];

#ifdef _LANGUAGE_KOREAN
		if (lpDebugPlayInfo) {
			TRANS_CHATMESSAGE	TransChatMessage;

			wsprintf(TransChatMessage.szMessage, "¹Ùº§ »ý¸í Àç»ý ( ÁÖº¯:%d¸í ) ( Àç»ý·Â:%d )", NearUserCnt, RegenLife);
			TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
			TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
			TransChatMessage.dwIP = 0;
			TransChatMessage.dwObjectSerial = 0;
			lpDebugPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		}
#endif
		return RegenLife;
	}

	return 0;
}

int rsSendRangeDamage(smCHAR* lpChar, rsPLAYINFO* lpMainPlayInfo, int Range, int SubDamgePers)
{
	int cnt;
	rsPLAYINFO* lpPlayInfo;
	STG_AREA* lpStgArea = (STG_AREA*)lpChar->lpExt1;
	int x, y, z, dist;
	int dRange = Range * Range;
	int BackDamge[2];

	int		UserCount = 0;
	rsPLAYINFO* lpUserList[16];

	int		sndUserCount = 0;
	rsPLAYINFO* lpSndUserList[128];

	if (!lpStgArea || !lpStgArea->lpField) return FALSE;

	lpUserList[UserCount++] = lpMainPlayInfo;
	lpSndUserList[sndUserCount++] = lpMainPlayInfo;

	for (cnt = 0; cnt < CONNECTMAX; cnt++) {
		lpPlayInfo = &rsPlayInfo[cnt];
		if (lpPlayInfo->lpsmSock && lpPlayInfo->dwObjectSerial && lpPlayInfo->Position.Area == lpStgArea->lpField->FieldCode && lpPlayInfo != lpMainPlayInfo) {
			x = (lpMainPlayInfo->Position.x - lpPlayInfo->Position.x) >> FLOATNS;
			y = (lpMainPlayInfo->Position.y - lpPlayInfo->Position.y) >> FLOATNS;
			z = (lpMainPlayInfo->Position.z - lpPlayInfo->Position.z) >> FLOATNS;
			dist = x * x + z * z;

			if (abs(y) < 60 && dist < dRange && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
				if (UserCount < 16)
					lpUserList[UserCount++] = lpPlayInfo;
			}

			if (dist < DIST_TRANSLEVEL_HIGH && abs(x) < TRANS_VIEW_LIMIT && abs(z) < TRANS_VIEW_LIMIT) {
				if (sndUserCount < 128)
					lpSndUserList[sndUserCount++] = lpPlayInfo;
			}
		}
	}

	BackDamge[0] = lpChar->smCharInfo.Attack_Damage[0];
	BackDamge[1] = lpChar->smCharInfo.Attack_Damage[1];

	lpChar->smCharInfo.Attack_Damage[0] = (lpChar->smCharInfo.Attack_Damage[0] * SubDamgePers) / fONE;
	lpChar->smCharInfo.Attack_Damage[1] = (lpChar->smCharInfo.Attack_Damage[1] * SubDamgePers) / fONE;

	for (cnt = 0; cnt < UserCount; cnt++) {
		if (lpUserList[cnt] != lpMainPlayInfo)
			lpChar->SendTransAttack(0, lpUserList[cnt]->lpsmSock, 0);
	}

	lpChar->smCharInfo.Attack_Damage[0] = BackDamge[0];
	lpChar->smCharInfo.Attack_Damage[1] = BackDamge[1];

	TRANS_SKIL_ATTACKDATA	TransSkillAttackData;
	ZeroMemory(&TransSkillAttackData, sizeof(TRANS_SKIL_ATTACKDATA));

	TransSkillAttackData.size = sizeof(TRANS_SKIL_ATTACKDATA) - (sizeof(DWORD) * (SKIL_ATTACK_CHAR_MAX - UserCount));
	if (UserCount > 0 && TransSkillAttackData.size > 32) {
		TransSkillAttackData.code = smTRANSCODE_ATTACK_SLASH_LIST;
		TransSkillAttackData.dwDestObjectSerial = lpChar->dwObjectSerial;
		TransSkillAttackData.TargetCount = UserCount;
		for (cnt = 0; cnt < UserCount; cnt++) {
			TransSkillAttackData.dwTarObjectSerial[cnt] = lpUserList[cnt]->dwObjectSerial;
		}
		for (cnt = 0; cnt < sndUserCount; cnt++) {
			if (lpSndUserList[cnt]->lpsmSock)
				lpSndUserList[cnt]->lpsmSock->Send2((char*)&TransSkillAttackData, TransSkillAttackData.size, TRUE);
		}
	}

	return TRUE;
}

int	rsMorifEventMessage(smCHAR* lpChar)
{
	return FALSE;
}

int	rsMollyWolfEventMessage(smCHAR* lpChar)
{
	return FALSE;
}

int	rsChichenDayEventMessage(smCHAR* lpChar)
{
	return FALSE;
}

int	rsQuestMasterMessage(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo)
{
	return FALSE;
}

int	rsSantaGoblinEventMessage(smCHAR* lpChar)
{
	return FALSE;
}

smCHAR* rsOpenCastleFieldObject(STG_AREA* lpStgArea, smCHAR_INFO* lpCharInfo, int x, int y, int z)
{
	smCHAR* lpChar;
	STG_CHAR_INFO StgCharInfo;

	if (lpStgArea) {
		StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
		StgCharInfo.smCharInfo.Life[0] = 100;
		StgCharInfo.smCharInfo.Mana[0] = 100;
		StgCharInfo.smCharInfo.Life[1] = 100;
		StgCharInfo.smCharInfo.State = TRUE;

		memcpy(&StgCharInfo.smCharInfo, lpCharInfo, sizeof(smCHAR_INFO));

		lpStgArea->EvnMonster = TRUE;
		lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
		if (lpChar) {
			lpChar->pX = x;
			lpChar->pY = y;
			lpChar->pZ = z;
			lpChar->Angle.x = 0;
			lpChar->Angle.y = 0;
			lpChar->Angle.z = 0;
			lpChar->DistAroundDbl = 0;
			lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
			lpChar->TargetMoveCount = 0;
			if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_N ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR ||
				lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_DEATHKNIGHT)
			{
				lpChar->DontMoveFlag = 2;

				if (StgCharInfo.smCharInfo.lpMonInfo && StgCharInfo.smCharInfo.lpMonInfo->PotionCount) {
					lpChar->smMonsterInfo.PotionCount = 0;

					lpChar->UseObject_VirtualLife = StgCharInfo.smCharInfo.lpMonInfo->PotionCount;
					lpChar->sObject_VirtualLife[0] = lpChar->UseObject_VirtualLife;
					lpChar->sObject_VirtualLife[1] = lpChar->UseObject_VirtualLife;
					lpChar->sObject_DisplayLife[0] = lpChar->UseObject_VirtualLife;
					lpChar->sObject_DisplayLife[1] = lpChar->UseObject_VirtualLife;
				}
			}
			else {
				lpChar->smMonsterInfo.PotionCount = StgCharInfo.smCharInfo.lpMonInfo->PotionCount;
				lpChar->PosiAround.x = x;
				lpChar->PosiAround.y = y;
				lpChar->PosiAround.z = z;
				lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
			}

			lpChar->dwClanCode = rsBlessCastle.dwMasterClan;

			return lpChar;
		}
	}

	return FALSE;
}

#include	"BlessCastle.h"

static	DWORD	dwBlessCastle_TowerRegenTime;

struct BLESS_CASTLE_OPEN_LEAUGE {
	int		GameMode;
	DWORD	dwStartTime;
	DWORD	dwEndTime;
	DWORD	dwRestartTime;
};

static BLESS_CASTLE_OPEN_LEAUGE	rsBlessCastleOpenLeauge;

int rsInit_Castle()
{
	ZeroMemory(&rsBlessCastle, sizeof(rsBLESS_CASTLE));
	ZeroMemory(&rsBlessCastleOpenLeauge, sizeof(BLESS_CASTLE_OPEN_LEAUGE));

	rsLoadCastleInfo();

	rsBlessCastle.dwSoulFountainTime = 0;
	rsBlessCastle.dwSoulFountainTime2 = 0;
	rsBlessCastle.lpAttackDamageList = 0;
	rsBlessCastle.lpChar_ValhallaTower = 0;

	ZeroMemory(&rsBlessCastle.ClanTop10, sizeof(rsUSER_LIST_TOP10));

	dwBlessCastle_TowerRegenTime = 0;

	return TRUE;
}

int rsMain_CombatCastle()
{
	int cnt;
	int DoorCount = 0;
	int	ValhallaTowerCount = 0;
	int	CrystalTowerCount = 0;
	smCHAR* lpChar;
	smCHAR* lpChar_ValhallaTower = 0;
	STG_AREA* lpStgArea = &StageArea[rsCASTLE_FIELD];
	int	UpdateFlag = 0;

	rsBlessCastle.Counter++;

	rsBlessCastle_SoulFountainMain();

	if (rsBlessCastleOpenLeauge.GameMode)
	{
		if (rsBlessCastleOpenLeauge.dwEndTime && rsBlessCastleOpenLeauge.dwEndTime < dwPlayServTime)
		{
			rsBlessCastleOpenLeauge.GameMode = 0;
		}
		else
		{
			if (!rsBlessCastle.CastleMode)
			{
				if (rsBlessCastleOpenLeauge.dwRestartTime && rsBlessCastleOpenLeauge.dwRestartTime < dwPlayServTime)
				{
					rsStart_CombatCastle();
				}
			}
		}
	}

	if (!rsBlessCastle.CastleMode)
	{
		rsBlessCastle.TimeSec[0] = 0;
		rsBlessCastle.TimeSec[1] = 0;
		return FALSE;
	}

	if (rsBlessCastle.CastleMode == 3)
	{
		if (rsBlessCastle.dwBattleOverTime < dwPlayServTime) {
			rsEnd_CombatCastle();
		}
		return TRUE;
	}

	if ((rsBlessCastle.Counter & 0x1F) == 0)
	{
		rsBlessCastle.TimeSec[0] = (short)((dwPlayServTime - rsBlessCastle.dwStartTime) / 1000);
		rsBlessCastle.TimeSec[1] = (short)((rsBlessCastle.dwBattleOverTime - rsBlessCastle.dwStartTime) / 1000);

		((DWORD*)rsBlessCastle.bCrystalSolderCount)[0] = 0;
		((DWORD*)rsBlessCastle.bCrystalTowerCount)[0] = 0;

		for (cnt = 0; cnt < STG_MONSTER_MAX; cnt++)
		{
			if (lpStgArea->lpCharMonster[cnt] && lpStgArea->lpCharMonster[cnt]->smCharInfo.Life[0] > 0) {
				lpChar = lpStgArea->lpCharMonster[cnt];
				if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR)
				{
					DoorCount++;
				}
				else if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B)
				{
					ValhallaTowerCount++;
					lpChar_ValhallaTower = lpChar;
				}
				else if (lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B ||
					lpChar->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_N)
				{
					switch (lpChar->smCharInfo.dwCharSoundCode) {
					case snCHAR_SOUND_CASTLE_CRYSTAL_R:
						if (rsBlessCastle.bCrystalTowerCount[0] < 100) rsBlessCastle.bCrystalTowerCount[0] ++;
						break;
					case snCHAR_SOUND_CASTLE_CRYSTAL_G:
						if (rsBlessCastle.bCrystalTowerCount[1] < 100) rsBlessCastle.bCrystalTowerCount[1] ++;
						break;
					case snCHAR_SOUND_CASTLE_CRYSTAL_B:
						if (rsBlessCastle.bCrystalTowerCount[2] < 100) rsBlessCastle.bCrystalTowerCount[2] ++;
						break;
					case snCHAR_SOUND_CASTLE_CRYSTAL_N:
						if (rsBlessCastle.bCrystalTowerCount[3] < 100) rsBlessCastle.bCrystalTowerCount[3] ++;
						break;
					}

					CrystalTowerCount++;

					if (rsBlessCastle.DefenceLevel == 0 &&
						rsBlessCastle.lpAttackDamageList &&
						!lpChar->lpAttackDamageList_BlessCastle)
					{
						lpChar->lpAttackDamageList_BlessCastle = rsBlessCastle.lpAttackDamageList;
					}
				}
				else if (lpChar->smCharInfo.Next_Exp)
				{
					switch (lpChar->smCharInfo.dwCharSoundCode)
					{
					case snCHAR_SOUND_CASTLE_SOLDER_A:
						if (rsBlessCastle.bCrystalSolderCount[0] < 100) rsBlessCastle.bCrystalSolderCount[0]++;
						break;
					case snCHAR_SOUND_CASTLE_SOLDER_B:
						if (rsBlessCastle.bCrystalSolderCount[1] < 100) rsBlessCastle.bCrystalSolderCount[1]++;
						break;
					case snCHAR_SOUND_CASTLE_SOLDER_C:
						if (rsBlessCastle.bCrystalSolderCount[2] < 100) rsBlessCastle.bCrystalSolderCount[2]++;
						break;
					}
				}

				lpChar->dwLastTransTime = dwPlayServTime;
				lpChar->ReopenCount = REOPEN_COUNT_NUM;
			}
		}

		if (rsBlessCastle.DefenceLevel == 0 && DoorCount == 0)
		{
			rsBlessCastle.DefenceLevel++;
		}

		if (ValhallaTowerCount == 0)
		{
			rsEnd_CombatCastle(0);

			if (rsBlessCastle.ClanTop10.dwUserCode[0])
			{
				rsBlessCastle.dwMasterClan = GetClanCode(rsBlessCastle.ClanTop10.dwUserCode[0]);
				UpdateFlag = 2;
				rsSaveCastleInfo();

				PACKET_CROWN packet;
				packet.size = sizeof(PACKET_CROWN);
				packet.code = smTRANSCODE_BLESSCROWN;
				packet.Silver = GetClanCode(rsBlessCastle.ClanTop10.dwUserCode[1]);
				packet.Bronze = GetClanCode(rsBlessCastle.ClanTop10.dwUserCode[2]);

				for (cnt = 0; cnt < CONNECTMAX; cnt++)
				{
					if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial)
					{
						rsPlayInfo[cnt].lpsmSock->Send((char*)&packet, packet.size, true);
					}
				}
			}
		}
		else if (rsBlessCastle.dwBattleOverTime < dwPlayServTime)
		{
			rsEnd_CombatCastle(1);
			UpdateFlag = 2;
			rsSaveCastleInfo();
		}

		rsBlessCastle.lpChar_ValhallaTower = lpChar_ValhallaTower;

		if (lpChar_ValhallaTower)
		{
			if (CrystalTowerCount > 0)
			{
				lpChar_ValhallaTower->smCharInfo.Life[0] = lpChar_ValhallaTower->smCharInfo.Life[1];
			}
			else
			{
				if (!lpChar_ValhallaTower->lpAttackDamageList)
				{
					if (rsBlessCastle.lpAttackDamageList)
					{
						lpChar_ValhallaTower->lpAttackDamageList = rsBlessCastle.lpAttackDamageList;
						rsBlessCastle.lpAttackDamageList = 0;
					}
					else {
						lpChar_ValhallaTower->lpAttackDamageList = new ATTACK_DAMAGE_LIST[ATTACK_DAMAGE_LIST_MAX];
						if (lpChar_ValhallaTower->lpAttackDamageList)
							ZeroMemory(lpChar_ValhallaTower->lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST) * ATTACK_DAMAGE_LIST_MAX);
					}
				}
			}

			if (rsBlessCastle.DefenceLevel)
			{
				rsSelectDamageClanTop10(lpChar_ValhallaTower, &rsBlessCastle.ClanTop10);
			}
		}
	}

	if (rsBlessCastle.ClanTop10.code)
	{
		for (cnt = (rsBlessCastle.Counter & 0x1F); cnt < CONNECTMAX; cnt += 0x20)
		{
			if (rsPlayInfo[cnt].lpsmSock && rsPlayInfo[cnt].dwObjectSerial && rsPlayInfo[cnt].Position.Area == rsCASTLE_FIELD)
			{
				rsPlayInfo[cnt].lpsmSock->Send((char*)&rsBlessCastle.ClanTop10, rsBlessCastle.ClanTop10.size, TRUE);
				if (UpdateFlag > 0)
				{
					rsSendBlessCastleInfoToDataServer(&rsPlayInfo[cnt]);
					UpdateFlag--;
				}
			}
		}
	}

	return TRUE;
}

int	rsStart_CombatCastle()
{
	int cnt;
	STG_AREA* lpStgArea = &StageArea[rsCASTLE_FIELD];
	smCHAR* lpChar;

	if (rsServerConfig.BlessCastleMode == 2) {
		rsBlessCastleOpenLeauge.GameMode = 1;
		rsBlessCastleOpenLeauge.dwStartTime = dwPlayServTime;
		rsBlessCastleOpenLeauge.dwEndTime = dwPlayServTime + 120 * 60 * 1000;
		rsServerConfig.BlessCastleMode = 1;
	}

	rsBlessCastle.CastleMode = 1;
	rsBlessCastle.Counter = 0;
	rsBlessCastle.DefenceLevel = 0;
	rsBlessCastle.dwBattleOverTime = dwPlayServTime + 120 * 60 * 1000;
	rsBlessCastle.dwStartTime = dwPlayServTime;
	rsBlessCastle.TimeSec[0] = 0;
	rsBlessCastle.TimeSec[1] = 0;

	rsBlessCastle.dwScoreLogTime = dwPlayServTime + 5 * 60 * 1000;

	if (rsBlessCastleOpenLeauge.GameMode) {
		rsBlessCastle.dwBattleOverTime = rsBlessCastleOpenLeauge.dwEndTime;
		rsBlessCastleOpenLeauge.dwRestartTime = 0;
		rsSetNoticeMessage("League");
	}

	if (!rsBlessCastle.lpAttackDamageList)
		rsBlessCastle.lpAttackDamageList = new ATTACK_DAMAGE_LIST[ATTACK_DAMAGE_LIST_MAX];
	if (rsBlessCastle.lpAttackDamageList)
		ZeroMemory(rsBlessCastle.lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST) * ATTACK_DAMAGE_LIST_MAX);

	if (rsBlessCastle.dwMasterClan == 0) {
		rsBlessCastle.BlessCastleSetup.MercenaryNum[0] = 20;
		rsBlessCastle.BlessCastleSetup.MercenaryNum[1] = 20;
		rsBlessCastle.BlessCastleSetup.MercenaryNum[2] = 20;
		rsBlessCastle.BlessCastleSetup.MercenaryNum[3] = 0;

		for (cnt = 0; cnt < 6; cnt++) {
			rsBlessCastle.BlessCastleSetup.Tower[cnt] = (rand() % 3) + 1;
		}
	}

	ZeroMemory(&rsBlessCastle.ClanTop10, sizeof(rsUSER_LIST_TOP10));

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea) {
			chrAutoPlayer[cnt].Close();
			if (lpStgArea->DeleteMonTable(&chrAutoPlayer[cnt]) == TRUE)
				lpStgArea->MonsterCount--;
		}
	}

	smCHAR_INFO* lpChar_CastleDoor = 0;
	smCHAR_INFO* lpChar_CastleTower_B = 0;
	smCHAR_INFO* lpChar_CastleCrystal_R = 0;
	smCHAR_INFO* lpChar_CastleCrystal_G = 0;
	smCHAR_INFO* lpChar_CastleCrystal_B = 0;
	smCHAR_INFO* lpChar_CastleCrystal_N = 0;
	smCHAR_INFO* lpChar_CastleSolder_A = 0;
	smCHAR_INFO* lpChar_CastleSolder_B = 0;
	smCHAR_INFO* lpChar_CastleSolder_C = 0;
	smCHAR_INFO* lpChar_SetTower = 0;

	for (cnt = 0; cnt < chrMonsterCnt; cnt++) {
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_DOOR) {
			lpChar_CastleDoor = &chrMonsterList[cnt];
		}
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B) {
			lpChar_CastleTower_B = &chrMonsterList[cnt];
		}
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_R) {
			lpChar_CastleCrystal_R = &chrMonsterList[cnt];
		}
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_G) {
			lpChar_CastleCrystal_G = &chrMonsterList[cnt];
		}
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_B) {
			lpChar_CastleCrystal_B = &chrMonsterList[cnt];
		}
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_CRYSTAL_N) {
			lpChar_CastleCrystal_N = &chrMonsterList[cnt];
		}

		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_SOLDER_A) {
			lpChar_CastleSolder_A = &chrMonsterList[cnt];
		}
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_SOLDER_B) {
			lpChar_CastleSolder_B = &chrMonsterList[cnt];
		}
		if (chrMonsterList[cnt].dwCharSoundCode == snCHAR_SOUND_CASTLE_SOLDER_C) {
			lpChar_CastleSolder_C = &chrMonsterList[cnt];
		}
	}

	if (lpChar_CastleDoor) {
		rsOpenCastleFieldObject(lpStgArea, lpChar_CastleDoor, pCastle_Door.x * fONE, pCastle_Door.z * fONE, pCastle_Door.y * fONE);
	}
	if (lpChar_CastleTower_B) {
		lpChar = rsOpenCastleFieldObject(lpStgArea, lpChar_CastleTower_B, pCastle_ValhallaTower.x * fONE, pCastle_ValhallaTower.z * fONE, pCastle_ValhallaTower.y * fONE);
	}

	cnt = 0;
	while (1)
	{
		if (pCastle_CrystalTower[cnt].x == 0) break;

		lpChar_SetTower = lpChar_CastleCrystal_N;

		switch (rsBlessCastle.BlessCastleSetup.Tower[cnt]) {
		case SIN_GURAD_CRISTAL_ICE:
			lpChar_SetTower = lpChar_CastleCrystal_B;
			break;
		case SIN_GURAD_CRISTAL_LIGHTNING:
			lpChar_SetTower = lpChar_CastleCrystal_G;
			break;
		case SIN_GURAD_CRISTAL_FIRE:
			lpChar_SetTower = lpChar_CastleCrystal_R;
			break;
		}

		if (lpChar_SetTower) {
			lpChar = rsOpenCastleFieldObject(lpStgArea, lpChar_SetTower, pCastle_CrystalTower[cnt].x * fONE, pCastle_CrystalTower[cnt].z * fONE, pCastle_CrystalTower[cnt].y * fONE);
		}
		cnt++;
	}

	for (cnt = 0; cnt < 3; cnt++) {
		if (rsBlessCastle.BlessCastleSetup.MercenaryNum[cnt] > MERCENARY_SOLDER_MAX)
			rsBlessCastle.BlessCastleSetup.MercenaryNum[cnt] = MERCENARY_SOLDER_MAX;
	}

	if (lpChar_CastleSolder_A) {
		for (cnt = 0; cnt < rsBlessCastle.BlessCastleSetup.MercenaryNum[0]; cnt++) {
			rsOpenCastleFieldObject(lpStgArea, lpChar_CastleSolder_A, PosMercenarySolder_A[cnt].x * fONE, PosMercenarySolder_A[cnt].z * fONE, PosMercenarySolder_A[cnt].y * fONE);
		}
	}

	if (lpChar_CastleSolder_B) {
		for (cnt = 0; cnt < rsBlessCastle.BlessCastleSetup.MercenaryNum[1]; cnt++) {
			rsOpenCastleFieldObject(lpStgArea, lpChar_CastleSolder_B, PosMercenarySolder_B[cnt].x * fONE, PosMercenarySolder_B[cnt].z * fONE, PosMercenarySolder_B[cnt].y * fONE);
		}
	}

	if (lpChar_CastleSolder_C) {
		for (cnt = 0; cnt < rsBlessCastle.BlessCastleSetup.MercenaryNum[2]; cnt++) {
			rsOpenCastleFieldObject(lpStgArea, lpChar_CastleSolder_C, PosMercenarySolder_C[cnt].x * fONE, PosMercenarySolder_C[cnt].z * fONE, PosMercenarySolder_C[cnt].y * fONE);
		}
	}

	rsSetNoticeMessage(srBlessCastle_LeagueMsg_02);

	return TRUE;
}

int	rsEnd_CombatCastle(int DefenceFlag)
{
	int cnt;
	STG_AREA* lpStgArea = &StageArea[rsCASTLE_FIELD];

	rsBlessCastle.CastleMode = 3;
	rsBlessCastle.dwBattleOverTime = dwPlayServTime + 5000;

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea && chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY)
		{
			if (DefenceFlag && chrAutoPlayer[cnt].smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B) {
				chrAutoPlayer[cnt].smCharInfo.Life[0] = chrAutoPlayer[cnt].smCharInfo.Life[1];
				chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_STAND);
			}
			else {
				chrAutoPlayer[cnt].smCharInfo.Life[0] = 0;
				chrAutoPlayer[cnt].SetMotionFromCode(CHRMOTION_STATE_DEAD);
			}
		}
	}

	for (cnt = 0; cnt < FIX_CHAR_MAX; cnt++) {
		if (lpStgArea->TransCharFixed[cnt].code)
			lpStgArea->OpenNpc(&lpStgArea->TransCharFixed[cnt]);
	}

	return TRUE;
}

int	rsEnd_CombatCastle()
{
	int cnt;
	STG_AREA* lpStgArea = &StageArea[rsCASTLE_FIELD];

	rsBlessCastle.CastleMode = 0;
	rsBlessCastle.TimeSec[0] = 0;
	rsBlessCastle.TimeSec[1] = 0;

	rsBlessCastle.BlessCastleSetup.MercenaryNum[0] = 0;
	rsBlessCastle.BlessCastleSetup.MercenaryNum[1] = 0;
	rsBlessCastle.BlessCastleSetup.MercenaryNum[2] = 0;
	rsBlessCastle.BlessCastleSetup.MercenaryNum[3] = 0;

	ZeroMemory(rsBlessCastle.BlessCastleSetup.Tower, sizeof(short) * 12);

	if (rsBlessCastle.lpAttackDamageList) {
		delete rsBlessCastle.lpAttackDamageList;
		rsBlessCastle.lpAttackDamageList = 0;
	}

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea) {
			chrAutoPlayer[cnt].Close();
			if (lpStgArea->DeleteMonTable(&chrAutoPlayer[cnt]) == TRUE) {
				lpStgArea->MonsterCount--;
			}
		}
	}

	for (cnt = 0; cnt < FIX_CHAR_MAX; cnt++) {
		if (lpStgArea->TransCharFixed[cnt].code)
			lpStgArea->OpenNpc(&lpStgArea->TransCharFixed[cnt]);
	}

	rsSetNoticeMessage(srBlessCastle_LeagueMsg_03);

	if (rsBlessCastleOpenLeauge.GameMode) {
		rsBlessCastleOpenLeauge.dwRestartTime = dwPlayServTime + 1000 * 60 * 3;
		if (rsBlessCastleOpenLeauge.dwRestartTime >= rsBlessCastleOpenLeauge.dwEndTime) {
			rsBlessCastleOpenLeauge.GameMode = 0;
			rsBlessCastleOpenLeauge.dwEndTime = 0;
			rsBlessCastleOpenLeauge.dwRestartTime = 0;
		}
		else {
			rsSetNoticeMessage(srBlessCastle_LeagueMsg_01);
		}
	}

	return TRUE;
}

int	rsEasy_CastleMode()
{
	int cnt;
	STG_AREA* lpStgArea = &StageArea[rsCASTLE_FIELD];

	for (cnt = 0; cnt < AUTOPLAYER_MAX; cnt++) {
		if (chrAutoPlayer[cnt].Flag && chrAutoPlayer[cnt].lpExt1 == lpStgArea && chrAutoPlayer[cnt].smCharInfo.State == smCHAR_STATE_ENEMY) {
			chrAutoPlayer[cnt].sObject_VirtualLife[0] = 0;
			chrAutoPlayer[cnt].smCharInfo.Life[0] = 1;
		}
	}

	return TRUE;
}

int rsCheck_BlessCastleClanSkill(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	DWORD Code;

	Code = 0x3ea832ff;

	return Code & 0x7FFFFFFF;
}

int rsCheck_BlessCastleTax(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommandEx)
{
	DWORD Code;

	Code = 0x3ea832ff;

	return Code & 0x7FFFFFFF;
}

int	rsSendBlessCastleInfoToDataServer(rsPLAYINFO* lpPlayInfo)
{
	return TRUE;
}

int	rsRecvBlessCastleInfoFromGameServer(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND_EX* lpTransCommand)
{
	return FALSE;
}

int rsRecvBlessCastInfo(rsPLAYINFO* lpPlayInfo, void* lpPacket)
{
	smTRANS_BLESSCASTLE* lpBlessCastleSetup = (smTRANS_BLESSCASTLE*)lpPacket;
	smTRANS_COMMAND		smTransCommand;

	switch (lpBlessCastleSetup->smTransCommand.WParam) {
	case 0:
		if (lpBlessCastleSetup->smTransCommand.SParam != rsBlessCastle.Tax) {
			smTransCommand.code = smTRANSCODE_BLESSCASTLE_TAX;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = 0;
			smTransCommand.LParam = rsBlessCastle.dwMasterClan;
			smTransCommand.SParam = rsBlessCastle.Tax;
			smTransCommand.EParam = 0;

			lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
		}
		break;

	case 1:
		if (lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan || lpPlayInfo->AdminMode > 3) {
			if (StageArea[rsCASTLE_FIELD].dwActiveMode) {
				memcpy(&rsBlessCastle.BlessCastleSetup, lpBlessCastleSetup, sizeof(smTRANS_BLESSCASTLE));

				rsBlessCastle.NextTax = rsBlessCastle.BlessCastleSetup.TaxRate;
				rsSendBlessCastleInfoToDataServer(lpPlayInfo);
				rsSaveCastleInfo();

				RecordBlessCastleSetup(lpPlayInfo, lpBlessCastleSetup);
			}
		}
		break;
	}

	return TRUE;
}

int rsSendBlessCastInfo(rsPLAYINFO* lpPlayInfo, int Mode)
{
	smTRANS_BLESSCASTLE	smTransBlessCastle;

	memcpy(&smTransBlessCastle, &rsBlessCastle.BlessCastleSetup, sizeof(smTRANS_BLESSCASTLE));

	smTransBlessCastle.smTransCommand.size = sizeof(smTRANS_BLESSCASTLE);
	smTransBlessCastle.smTransCommand.code = smTRANSCODE_BLESSCASTLE_INFO;
	smTransBlessCastle.smTransCommand.WParam = Mode;
	smTransBlessCastle.smTransCommand.LParam = 0;
	smTransBlessCastle.smTransCommand.SParam = 0;
	smTransBlessCastle.smTransCommand.EParam = 0;

	smTransBlessCastle.dwMasterClan = rsBlessCastle.dwMasterClan;
	smTransBlessCastle.Price = 0;

	switch (Mode) {
	case 1:
		if (lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan || lpPlayInfo->AdminMode) {
			if (lpPlayInfo->lpsmSock)
				lpPlayInfo->lpsmSock->Send2((char*)&smTransBlessCastle, smTransBlessCastle.smTransCommand.size, TRUE);
		}
		break;
	}

	return TRUE;
}

int	rsSelectDamageClanTop10(smCHAR* lpChar, rsUSER_LIST_TOP10* lpUserListDamageTop10)
{
	int cnt, cnt2;
	int ChkCnt;
	int	TotalDamage = 0;
	ATTACK_DAMAGE_LIST	AttackDamageList[ATTACK_DAMAGE_LIST_MAX];

	if (!lpUserListDamageTop10) return FALSE;

	ZeroMemory(lpUserListDamageTop10, sizeof(rsUSER_LIST_TOP10));

	if (lpChar->lpAttackDamageList) {
		memcpy(AttackDamageList, lpChar->lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST) * ATTACK_DAMAGE_LIST_MAX);
	}
	else if (rsBlessCastle.lpAttackDamageList) {
		memcpy(AttackDamageList, rsBlessCastle.lpAttackDamageList, sizeof(ATTACK_DAMAGE_LIST) * ATTACK_DAMAGE_LIST_MAX);
	}
	else
		return FALSE;

	for (cnt2 = 0; cnt2 < ATTACK_DAMAGE_LIST_MAX; cnt2++) {
		TotalDamage += AttackDamageList[cnt2].DamageCount;
	}

	for (cnt = 0; cnt < 10; cnt++) {
		ChkCnt = -1;
		for (cnt2 = 0; cnt2 < ATTACK_DAMAGE_LIST_MAX; cnt2++) {
			if (AttackDamageList[cnt2].dwUserCode && GetClanCode(AttackDamageList[cnt2].dwUserCode) != rsBlessCastle.dwMasterClan &&
				AttackDamageList[cnt2].DamageCount > lpUserListDamageTop10->Damage[cnt]) {
				lpUserListDamageTop10->dwUserCode[cnt] = AttackDamageList[cnt2].dwUserCode;
				lpUserListDamageTop10->Damage[cnt] = AttackDamageList[cnt2].DamageCount;
				lpUserListDamageTop10->Counter[cnt] = AttackDamageList[cnt2].Count;

				ChkCnt = cnt2;
			}
		}

		if (ChkCnt >= 0)
			AttackDamageList[ChkCnt].dwUserCode = 0;
	}

	((DWORD*)lpUserListDamageTop10->bCrystalTowerCount)[0] = ((DWORD*)rsBlessCastle.bCrystalTowerCount)[0];

	lpUserListDamageTop10->dwUpdateTime = dwPlayServTime;
	lpUserListDamageTop10->dwCharCode = lpChar->dwObjectSerial;

	lpUserListDamageTop10->code = smTRANSCODE_BLESSCASTLE_INFO;
	lpUserListDamageTop10->size = sizeof(rsUSER_LIST_TOP10);
	lpUserListDamageTop10->tCode = rsServerConfig.ServerCode;
	lpUserListDamageTop10->dwObjectSerial = 2;
	lpUserListDamageTop10->dwTotalDamage = TotalDamage;

	if (rsBlessCastle.dwScoreLogTime && rsBlessCastle.dwScoreLogTime < dwPlayServTime) {
		rsBlessCastle.dwScoreLogTime = dwPlayServTime + 5 * 60 * 1000;

		RecordBlessCastleLog(lpUserListDamageTop10);
	}

	return TRUE;
}

int	rsBlessCastle_SoulFountainMain()
{
	int cnt, mcnt, last;
	rsPLAYINFO* lpPlayInfo;
	TRANS_CHATMESSAGE	TransChatMessage;

	if (!rsBlessCastle.dwMasterClan || rsBlessCastle.CastleMode)
		return FALSE;

	if (rsBlessCastle.dwSoulFountainTime < dwPlayServTime) {
		rsBlessCastle.dwSoulFountainTime = dwPlayServTime + 60 * 1000;
		if (rsBlessCastle.SoulFountain_PotionCount < 1440)
			rsBlessCastle.SoulFountain_PotionCount++;
	}

	if (!rsBlessCastle.SoulFountain_PotionCount || rsBlessCastle.dwSoulFountainTime2 > dwPlayServTime) return FALSE;

	rsBlessCastle.dwSoulFountainTime2 = dwPlayServTime + 1000;

	last = rsBlessCastle.SoulFountain_LastUserCount + CONNECTMAX;

	for (cnt = rsBlessCastle.SoulFountain_LastUserCount + 1; cnt <= last; cnt++) {
		mcnt = cnt & CONNECTMAX_MASK;
		lpPlayInfo = &rsPlayInfo[mcnt];
		if (lpPlayInfo->lpsmSock && lpPlayInfo->dwObjectSerial && lpPlayInfo->Position.Area == rsCASTLE_FIELD) {
			if (rsBlessCastle.SoulFountain_PotionCount > 0 && lpPlayInfo->dwClanCode &&
				lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan &&
				lpPlayInfo->Position.x > CastleSoulFountain_Area[0] &&
				lpPlayInfo->Position.x<CastleSoulFountain_Area[1] &&
				lpPlayInfo->Position.z>CastleSoulFountain_Area[2] &&
				lpPlayInfo->Position.z < CastleSoulFountain_Area[3])
			{
				if (dwSerToSerIP)
					rsPutItemToSystemLine(lpPlayInfo, (sinPM1 | sin04));
				else
					rsPutItem(lpPlayInfo, (sinPM1 | sin04));

				rsBlessCastle.SoulFountain_PotionCount--;

				wsprintf(TransChatMessage.szMessage, srMsg_038, lpPlayInfo->smCharInfo.szName, rsBlessCastle.SoulFountain_PotionCount);
				TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;

				rsSendCommandUser2(lpPlayInfo, (smTRANS_COMMAND*)&TransChatMessage);

				rsBlessCastle.SoulFountain_LastUserCount = mcnt;
				break;
			}
		}
	}

	return TRUE;
}

int rsSendBlessCastleClanSkill(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND smTransCommand;

	if (lpPlayInfo->dwClanCode && lpPlayInfo->dwClanCode == rsBlessCastle.dwMasterClan) {
		if (!lpPlayInfo->SucessCheck_ClanCode) {
			bClan_GetClanMarkCode(lpPlayInfo);
		}

		if (!lpPlayInfo->CastleMaster.Flag) {
			lpPlayInfo->CastleMaster.dwCheckTime = 0;
			lpPlayInfo->CastleMaster.SelectSkill = rsBlessCastle.SelectedSkill;
			lpPlayInfo->CastleMaster.Flag = TRUE;
		}

		if (lpPlayInfo->CastleMaster.dwCheckTime < dwPlayServTime) {
			smTransCommand.code = smTRANSCODE_PROCESS_CLAN_SKILL;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.WParam = rsBlessCastle.SelectedSkill;
			smTransCommand.LParam = lpPlayInfo->dwClanCode;
			smTransCommand.SParam = 0;
			smTransCommand.EParam = rsCheck_BlessCastleClanSkill(lpPlayInfo, &smTransCommand);
			lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

			lpPlayInfo->CastleMaster.dwCheckTime = dwPlayServTime + 1000 * 60;
		}
		return TRUE;
	}
	return FALSE;
}

DWORD GetClanCode(int ClassClanCode)
{
	DWORD	dwCode, dwCode1, dwCode2;

	dwCode = ClassClanCode % 1000000;
	dwCode1 = ClassClanCode / 100000000;
	dwCode2 = dwCode1 * 100000000;

	return dwCode + dwCode2;
}

int	rsSaveCastleInfo()
{
	return FALSE;
}

int rsLoadCastleInfo()
{
	return FALSE;
}

int rsSiegeItemSucess(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.code = smTRANSCODE_PROCESS_SKILL2;
	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.WParam = SKILL_PLAY_BLESS_SIEGE_ITEM;
	smTransCommand.LParam = lpPlayInfo->dwObjectSerial;
	smTransCommand.SParam = dwItemCode;
	smTransCommand.EParam = 0;
	lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

	return TRUE;
}

int	rsOpenSiegeCastleItem(DWORD dwItemCode, int x, int y, int z, rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	switch (dwItemCode) {
	case (sinBI1 | sin05):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 2;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBI1 | sin06):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 60 * 60 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 15;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBI1 | sin07):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 60 * 60 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 15;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBI1 | sin09):

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_COMIC_SKIN;
		smTransCommand.WParam = (rand() % 2) + 1;
		smTransCommand.LParam = 60 * 60 * 3;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

		lpPlayInfo->dwTime_PrimeItem_BigHead = 60 * 60 * 3;
		return TRUE;

	case (sinBI1 | sin95):

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_COMIC_SKIN;
		smTransCommand.WParam = 1;
		smTransCommand.LParam = 60 * 60 * 3;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

		lpPlayInfo->dwTime_PrimeItem_BigHead = 60 * 60 * 3;
		lpPlayInfo->dwParam_PrimeItem_BigHead = 1;
		return TRUE;

	case (sinBI1 | sin96):

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_COMIC_SKIN;
		smTransCommand.WParam = 2;
		smTransCommand.LParam = 60 * 60 * 3;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

		lpPlayInfo->dwTime_PrimeItem_BigHead = 60 * 60 * 3;
		lpPlayInfo->dwParam_PrimeItem_BigHead = 2;
		return TRUE;

	case (sinBI1 | sin97):

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_COMIC_SKIN;
		smTransCommand.WParam = 3;
		smTransCommand.LParam = 60 * 60 * 3;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

		lpPlayInfo->dwTime_PrimeItem_BigHead = 60 * 60 * 3;
		lpPlayInfo->dwParam_PrimeItem_BigHead = 3;
		return TRUE;

	case (sinBI1 | sin98):

		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_COMIC_SKIN;
		smTransCommand.WParam = 4;
		smTransCommand.LParam = 60 * 60 * 3;
		smTransCommand.SParam = 0;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);

		lpPlayInfo->dwTime_PrimeItem_BigHead = 60 * 60 * 3;
		lpPlayInfo->dwParam_PrimeItem_BigHead = 4;
		return TRUE;

	case (sinBI1 | sin19):

		return TRUE;
	case (sinBI1 | sin20):

		return TRUE;
	case (sinBI1 | sin81):

		return TRUE;

	case (sinBI1 | sin86):

		return TRUE;
	case (sinBI1 | sin87):

		return TRUE;
	case (sinBI1 | sin88):

		return TRUE;

	case (sinBI1 | sin21):

		return TRUE;
	case (sinBI1 | sin22):

		return TRUE;
	case (sinBI1 | sin82):

		return TRUE;

	case (sinBI1 | sin12):
	case (sinBI1 | sin13):

	case (sinBI1 | sin14):
	case (sinBI1 | sin15):
	case (sinBI1 | sin78):

		return TRUE;

	case (sinBC1 | sin21):
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = dwPlayServTime + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case (sinBC1 | sin22):
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = dwPlayServTime + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case (sinBC1 | sin23):
		lpPlayInfo->dwLifeBooster_Code = dwItemCode;
		lpPlayInfo->dwLifeBooster_Time = dwPlayServTime + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwLifeBooster_Data = BoosterItem_DataPercent[0];
		return TRUE;
	case (sinBC1 | sin24):
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = dwPlayServTime + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case (sinBC1 | sin25):
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = dwPlayServTime + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case (sinBC1 | sin26):
		lpPlayInfo->dwManaBooster_Code = dwItemCode;
		lpPlayInfo->dwManaBooster_Time = dwPlayServTime + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwManaBooster_Data = BoosterItem_DataPercent[1];
		return TRUE;
	case (sinBC1 | sin27):
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = dwPlayServTime + BoosterItem_UseTime[0] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	case (sinBC1 | sin28):
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = dwPlayServTime + BoosterItem_UseTime[1] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	case (sinBC1 | sin29):
		lpPlayInfo->dwStaminaBooster_Code = dwItemCode;
		lpPlayInfo->dwStaminaBooster_Time = dwPlayServTime + BoosterItem_UseTime[2] * 1000;
		lpPlayInfo->dwStaminaBooster_Data = BoosterItem_DataPercent[2];
		return TRUE;
	}

	if (lpPlayInfo->Position.Area != rsCASTLE_FIELD)
		return FALSE;

	switch (dwItemCode) {
	case (sinBC1 | sin01):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 2;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin02):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin03):
		lpPlayInfo->dwSiegeItem_Scroll_Time = dwPlayServTime + 30 * 1000;
		lpPlayInfo->dwSiegeItem_Scroll_Code = dwItemCode;
		lpPlayInfo->dwSiegeItem_Scroll_Param = 5;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin04):
	case (sinBC1 | sin05):
		return FALSE;

	case (sinBC1 | sin06):
		lpPlayInfo->dwSiegeItem_Stone1_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_R;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin07):
		lpPlayInfo->dwSiegeItem_Stone1_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_B;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin08):
		lpPlayInfo->dwSiegeItem_Stone1_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone1_Code = snCHAR_SOUND_CASTLE_CRYSTAL_G;
		lpPlayInfo->dwSiegeItem_Stone1_Param = 50;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin09):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_FIGHTER;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin10):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_MECHANICIAN;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin11):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_PIKEMAN;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin12):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_ARCHER;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin13):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_KNIGHT;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin14):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_ATALANTA;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin15):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_MAGICIAN;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;

	case (sinBC1 | sin16):
		lpPlayInfo->dwSiegeItem_Stone2_Time = dwPlayServTime + 60 * 1000;
		lpPlayInfo->dwSiegeItem_Stone2_Code = JOBCODE_PRIESTESS;
		lpPlayInfo->dwSiegeItem_Stone2_Param = 20;
		rsSiegeItemSucess(lpPlayInfo, dwItemCode);
		return TRUE;
	}

	return TRUE;
}

int RecordBlessCastleLog(rsUSER_LIST_TOP10* lpUserListDamageTop10)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	char	szBuff2[4096];
	int cnt;

	GetLocalTime(&st);
	wsprintf(szFileName, filenameBlessCaslte, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff2, "=================== Check Time [ %d:%d:%d ] =====================\r\n",
		st.wHour, st.wMinute, st.wSecond);

	for (cnt = 0; cnt < 10; cnt++) {
		wsprintf(szBuff, "%d> ClanCode[%d] Damage:%d Count:%d \r\n",
			cnt + 1,
			lpUserListDamageTop10->dwUserCode[cnt],
			lpUserListDamageTop10->Damage[cnt],
			lpUserListDamageTop10->Damage[cnt],
			lpUserListDamageTop10->Counter[cnt]);

		lstrcat(szBuff2, szBuff);
	}

	wsprintf(szBuff, "* Tower Crystal ( %d %d %d %d )\r\n",
		lpUserListDamageTop10->bCrystalTowerCount[0],
		lpUserListDamageTop10->bCrystalTowerCount[1],
		lpUserListDamageTop10->bCrystalTowerCount[2],
		lpUserListDamageTop10->bCrystalTowerCount[3]);

	lstrcat(szBuff2, szBuff);

	if (rsBlessCastle.lpChar_ValhallaTower && rsBlessCastle.lpChar_ValhallaTower->Flag && rsBlessCastle.lpChar_ValhallaTower->smCharInfo.dwCharSoundCode == snCHAR_SOUND_CASTLE_TOWER_B) {
		wsprintf(szBuff, "* ValhallaTower ( %d:%d )/( %d/%d )\r\n",
			rsBlessCastle.lpChar_ValhallaTower->smMonsterInfo.PotionCount,
			rsBlessCastle.lpChar_ValhallaTower->smCharInfo.Life[0],

			rsBlessCastle.lpChar_ValhallaTower->sObject_DisplayLife[0],
			rsBlessCastle.lpChar_ValhallaTower->sObject_DisplayLife[1]);

		lstrcat(szBuff2, szBuff);
	}

	CreateDirectory(DebugLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff2, lstrlen(szBuff2), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int RecordBlessCastleSetup(rsPLAYINFO* lpPlayInfo, smTRANS_BLESSCASTLE* lpBlessCastleSetup)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	char	szFileName[128];
	char	szBuff[256];
	char	szBuff2[4096];

	GetLocalTime(&st);
	wsprintf(szFileName, filenameBlessCaslte, HackLogDirectory, st.wMonth, st.wDay);

	wsprintf(szBuff, "%d:%d:%d - Name(%s)/IP(%s) MasterClan(%d) Price(%d)\r\n",
		st.wHour, st.wMinute, st.wSecond,
		lpPlayInfo->smCharInfo.szName, lpPlayInfo->lpsmSock->szIPAddr,
		rsBlessCastle.dwMasterClan, lpBlessCastleSetup->Price);

	wsprintf(szBuff2, "%s=> TaxRate(%d) Tower(%d %d %d %d %d %d) Mercenary(%d %d %d) ClanSkill(%d)\r\n\r\n", szBuff,
		lpBlessCastleSetup->TaxRate,
		lpBlessCastleSetup->Tower[0], lpBlessCastleSetup->Tower[1], lpBlessCastleSetup->Tower[2],
		lpBlessCastleSetup->Tower[3], lpBlessCastleSetup->Tower[4], lpBlessCastleSetup->Tower[5],
		lpBlessCastleSetup->MercenaryNum[0], lpBlessCastleSetup->MercenaryNum[1], lpBlessCastleSetup->MercenaryNum[2],
		lpBlessCastleSetup->ClanSkill);

	CreateDirectory(DebugLogDirectory, NULL);

	hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff2, lstrlen(szBuff2), &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}

int rsFault_PlayField(rsPLAYINFO* lpPlayInfo, int height)
{
	smTRANS_COMMAND_EX	smTransCommandEx;

	lpPlayInfo->sCheckPlayField_Count[1]++;

	if (lpPlayInfo->WarningCount < 10 && lpPlayInfo->sCheckPlayField_Count[1] >= 3) {
		smTransCommandEx.size = sizeof(smTRANS_COMMAND_EX);
		smTransCommandEx.code = smTRANSCODE_SET_BLACKLIST;
		smTransCommandEx.WParam = 8860;
		smTransCommandEx.LParam = lpPlayInfo->Position.x / fONE;
		smTransCommandEx.SParam = lpPlayInfo->Position.y / fONE;
		smTransCommandEx.EParam = lpPlayInfo->Position.z / fONE;
		smTransCommandEx.WxParam = lpPlayInfo->Position.Area;
		smTransCommandEx.LxParam = height / fONE;
		smTransCommandEx.SxParam = 0;
		smTransCommandEx.ExParam = 0;

		rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommandEx);
		lpPlayInfo->WarningCount++;

		lpPlayInfo->sCheckPlayField_Count[1] = 0;
	}

	return TRUE;
}

int rsCheckPlayField(rsPLAYINFO* lpPlayInfo)
{
	if (!rsServerConfig.CheckPlayField) return TRUE;

	lpPlayInfo->sCheckPlayField_Count[0]++;

	if ((lpPlayInfo->sCheckPlayField_Count[0] & 0xF) != 0) return FALSE;

	if (lpPlayInfo->Position.Area > STAGE_AREA_MAX || lpPlayInfo->Position.Area < 0) {
		rsFault_PlayField(lpPlayInfo, 0);
		return FALSE;
	}

	STG_AREA* lpStgArea = &StageArea[lpPlayInfo->Position.Area];
	smSTAGE3D* lpStage = lpStgArea->lpStage;
	int	height;
	int heCnt;

	if (!lpStage) {
		rsFault_PlayField(lpPlayInfo, 0);
		return FALSE;
	}

	height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x, lpPlayInfo->Position.y, lpPlayInfo->Position.z, 10 * fONE);
	if (height > 0) {
		heCnt = 0;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 4 * fONE, lpPlayInfo->Position.y + 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 4 * fONE, lpPlayInfo->Position.y - 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x - 4 * fONE, lpPlayInfo->Position.y + 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x - 4 * fONE, lpPlayInfo->Position.y - 4 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;

		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 0 * fONE, lpPlayInfo->Position.y + 2 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 0 * fONE, lpPlayInfo->Position.y - 2 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x + 2 * fONE, lpPlayInfo->Position.y + 0 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;
		height = lpStage->CheckFloorFaceHeight(lpPlayInfo->Position.x - 2 * fONE, lpPlayInfo->Position.y - 0 * fONE, lpPlayInfo->Position.z, 10 * fONE);
		if (height > 0) heCnt++;

		if (heCnt >= 8) {
			rsFault_PlayField(lpPlayInfo, height);
			return FALSE;
		}
	}

	lpPlayInfo->sCheckPlayField_Count[1] = 0;

	return TRUE;
}

#define PRESENTITEM_LEVEL_MAX		4

#include "AutoDropItem.h"

DWORD rsLowLevelItem(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar)
{
	int rnd;
	int lev, job;
	int SelCnt;

	if (!lpPlayInfo->sLowLevel_PresentItem[0] || lpPlayInfo->sLowLevel_PresentItem[0] >= PRESENTITEM_LEVEL_MAX) return NULL;

	if (abs(lpPlayInfo->smCharInfo.Level - lpChar->smCharInfo.Level) > 8) return NULL;
	job = lpPlayInfo->smCharInfo.JOB_CODE - 1;
	if (job < 0 || job >= 8) return NULL;

	if (lpPlayInfo->dwCode_Name & 1)
		lev = rsPresentItem_LevelType_1[job][lpPlayInfo->sLowLevel_PresentItem[0]][0];
	else
		lev = rsPresentItem_LevelType_2[job][lpPlayInfo->sLowLevel_PresentItem[0]][0];

	if (lpPlayInfo->smCharInfo.Level < lev) return NULL;

	rnd = (lpPlayInfo->smCharInfo.Level - lev + 1) * 5;

	if ((rand() % 1000) < rnd) {
		SelCnt = lpPlayInfo->sLowLevel_PresentItem[0];

		lpPlayInfo->sLowLevel_PresentItem[0]++;

		rsUpdateServerParam(lpPlayInfo, smUPDATE_PARAM_LOWUSER_PRESENT, lpPlayInfo->sLowLevel_PresentItem[0], lpPlayInfo->sLowLevel_PresentItem[1], TRUE);

		if (lpPlayInfo->smCharInfo.Level < (lev + 10)) {
#ifdef _TEST_SERVER
			TRANS_CHATMESSAGE TransChatMessage;

			if (lpPlayInfo->AdminMode) {
				wsprintf(TransChatMessage.szMessage, "ÇÊ¿¬Àû ¾ÆÀÌÅÛ °úÀÇ ¸¸³²( %d )", SelCnt);
				TransChatMessage.code = smTRANSCODE_CHATMESSAGE;
				TransChatMessage.dwIP = 0;
				TransChatMessage.dwObjectSerial = 0;
				TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);

				lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
			}
#endif

			if (lpPlayInfo->dwCode_Name & 1)
				return rsPresentItem_LevelType_1[job][SelCnt][1];
			else
				return rsPresentItem_LevelType_2[job][SelCnt][1];
		}
	}

	return NULL;
}

int rsRecvUpdateServerParam(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	switch (lpTransCommand->WParam) {
	case smUPDATE_PARAM_LOWUSER_PRESENT:
		lpPlayInfo->sLowLevel_PresentItem[0] = lpTransCommand->LParam;
		lpPlayInfo->sLowLevel_PresentItem[1] = lpTransCommand->SParam;
		break;
	}

	return TRUE;
}

int	rsUpdateServerParam(rsPLAYINFO* lpPlayInfo, DWORD dwUpdateCode, int Param1, int Param2, int TargetMode)
{
	smTRANS_COMMAND	smTransCommand;

	smTransCommand.size = sizeof(smTRANS_COMMAND);
	smTransCommand.code = smTRANSCODE_UPDATE_SERVER_PARAM;
	smTransCommand.WParam = dwUpdateCode;
	smTransCommand.LParam = Param1;
	smTransCommand.SParam = Param2;
	smTransCommand.EParam = rsServerConfig.ServerCode;

	if (lpPlayInfo->lpsmSock) {
		if (TargetMode)
			return rsSendDataServer(lpPlayInfo->lpsmSock, &smTransCommand);
		else
			return rsSendGameServer(lpPlayInfo->lpsmSock, &smTransCommand);
	}

	return NULL;
}

int CreatePerfItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode, int spJobCode)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int JobCodeItem = 0;
	int PotionCount = 0;

	if ((dwItemCode & sinITEM_MASK1) == (sinPM1 & sinITEM_MASK1))
	{
		PotionCount = spJobCode;
	}
	else
	{
		JobCodeItem = spJobCode;
	}

	for (cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if (DefaultItems[cnt].Item.CODE == dwItemCode && !DefaultItems[cnt].Item.UniqueItem)
		{
			CreateDefItemPerf(&psItem.ItemInfo, &DefaultItems[cnt], JobCodeItem);

			psItem.ItemInfo.PotionCount = PotionCount;

			if (lpPlayInfo->lpsmSock)
			{
				TransItemInfo.code = smTRANSCODE_PUTITEM;
				TransItemInfo.size = sizeof(TRANS_ITEMINFO);
				memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
				rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
				lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
			}
			return TRUE;
		}
	}

	return TRUE;
}

int rsStartUser_PresentItem(rsPLAYINFO* lpPlayInfo)
{
	//sDEF_ITEMINFO *lpDefItem = 0;
	TRANS_CHATMESSAGE TransChatMessage;
	PREMIUM_TIME	smPremiumTime;
	smTRANS_COMMAND	smTransCommand;

	switch (lpPlayInfo->smCharInfo.JOB_CODE)
	{
	case JOBCODE_FIGHTER:
		PremioQuest(lpPlayInfo, sinWA1 | sin22, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_FIGHTER); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_FIGHTER); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Lutador!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_MECHANICIAN:
		PremioQuest(lpPlayInfo, sinWC1 | sin22, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinWH1 | sin23, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_MECHANICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_MECHANICIAN); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Mecânico!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_ARCHER:
		PremioQuest(lpPlayInfo, sinWS1 | sin24, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_ARCHER); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_ARCHER); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Arqueira!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_PIKEMAN:
		PremioQuest(lpPlayInfo, sinWP1 | sin23, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_PIKEMAN); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_PIKEMAN); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Pikeman!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_ATALANTA:
		PremioQuest(lpPlayInfo, sinWT1 | sin23, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_ATALANTA); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_ATALANTA); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Atalanta!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_KNIGHT:
		PremioQuest(lpPlayInfo, sinWS2 | sin25, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_KNIGHT); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_KNIGHT); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Cavaleiro!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_MAGICIAN:
		PremioQuest(lpPlayInfo, sinWM1 | sin23, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinDA2 | sin24, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOM1 | sin25, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_MAGICIAN); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_MAGICIAN); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Mago!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_PRIESTESS:
		PremioQuest(lpPlayInfo, sinWM1 | sin23, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinDA2 | sin24, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOM1 | sin25, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_PRIESTESS); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_PRIESTESS); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Sacer!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_ASSASSINE:
		PremioQuest(lpPlayInfo, sinWD1 | sin22, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_ASSASSINE); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_ASSASSINE); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Assassina!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_SHAMAN:
		PremioQuest(lpPlayInfo, sinWN1 | sin22, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinDA2 | sin24, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOM1 | sin25, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_SHAMAN); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_SHAMAN); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Shaman!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;
	case JOBCODE_MARTIAL:
		PremioQuest(lpPlayInfo, sinWV1 | sin23, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinDA1 | sin24, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinDS1 | sin25, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinDB1 | sin24, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinDG1 | sin24, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinOA2 | sin24, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinOE1 | sin01, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinOR1 | sin23, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinOA1 | sin23, JOBCODE_MARTIAL); // Ok
		PremioQuest(lpPlayInfo, sinOS1 | sin18, JOBCODE_MARTIAL); // Ok
		rsSendMoneyToUser(lpPlayInfo, 1000000); //1kk em gold

		lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
		lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
		lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
		lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
		lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;

		lpPlayInfo->smCharInfo.Level = 105;
		lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];

		smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
		smPremiumTime.size = sizeof(PREMIUM_TIME);
		smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
		smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
		smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
		smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
		smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
		smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
		smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
		smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
		smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
		smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
		smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
		smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
		lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);

		smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
		lpPlayInfo->dwStartUser_PresentItem_Count++;

		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		wsprintf(TransChatMessage.szMessage, "> %s recebeu itens Guerreira!", lpPlayInfo->szName);
		TransChatMessage.size = lstrlen(TransChatMessage.szMessage) + 32;
		TransChatMessage.dwIP = 10;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
		break;

		lpPlayInfo->dwStartUser_PresentItem_Count++;
		return TRUE;
	}
}

//int rsStartUser_PresentItem(rsPLAYINFO * lpPlayInfo)
//{
//	//switch (lpPlayInfo->dwStartUser_PresentItem_Count)
//	//{
//	//case 1:
//	sDEF_ITEMINFO *lpDefItem = 0;
//	TRANS_CHATMESSAGE TransChatMessage;
//
//	lpPlayInfo->dwTime_PrimeItem_VampCuspid = PRIME_ITEM_TIME_VAMPCUSPIDx2;
//	lpPlayInfo->dwTime_PrimeItem_ManaRecharg = PRIME_ITEM_TIME_MANARECHARGx2;
//	lpPlayInfo->dwTime_PrimeItem_ManaReduce = PRIME_ITEM_TIME_EXPUP;
//	lpPlayInfo->dwTime_PrimeItem_X2 = PRIME_ITEM_TIME_THIRDEYES;
//	lpPlayInfo->dwTime_PrimeItem_StaminaReduce = PRIME_ITEM_TIME_EXPUP;
//
//	lpPlayInfo->smCharInfo.Level = 90;
//	lpPlayInfo->spEXP_Out = ExpLevelTable[lpPlayInfo->smCharInfo.Level - 1];
//
//	lpDefItem = rsPutItem3(lpPlayInfo, (sinDA1 | sin23));
//	lpDefItem = rsPutItem3(lpPlayInfo, (sinDA1 | sin22));
//	rsSendMoneyToUser(lpPlayInfo, 10000);
//
//
//	if (lpDefItem)
//	{
//		wsprintf(TransChatMessage.szMessage, "Teste mensagem", lpDefItem->Item.ItemName);
//		TransChatMessage.code = smTRANSCODE_MESSAGEBOX;
//		TransChatMessage.dwIP = 0;
//		TransChatMessage.dwObjectSerial = 0;
//		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
//
//		lpPlayInfo->lpsmSock->Send((char *)&TransChatMessage, TransChatMessage.size, TRUE);
//
//		smTRANS_COMMAND	smTransCommand;
//		smTransCommand.code = smTRANSCODE_NOTICE_BOX;
//		smTransCommand.size = sizeof(smTRANS_COMMAND);
//		smTransCommand.WParam = lpDefItem->Item.CODE;
//		smTransCommand.LParam = 0;
//		smTransCommand.SParam = 0;
//		smTransCommand.EParam = 0;
//		lpPlayInfo->lpsmSock->Send2((char *)&smTransCommand, smTransCommand.size, TRUE);
//	}
//
//	PREMIUM_TIME	smPremiumTime;
//	smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
//	smPremiumTime.size = sizeof(PREMIUM_TIME);
//	smPremiumTime.ThirdEye = lpPlayInfo->dwTime_PrimeItem_X2;
//	smPremiumTime.ExpUp = lpPlayInfo->dwTime_PrimeItem_ExpUp;
//	smPremiumTime.VampCuspid = lpPlayInfo->dwTime_PrimeItem_VampCuspid;
//	smPremiumTime.ManaRecharg = lpPlayInfo->dwTime_PrimeItem_ManaRecharg;
//	smPremiumTime.MightofAwell = lpPlayInfo->dwTime_PrimeItem_MightofAwell;
//	smPremiumTime.MightofAwell2 = lpPlayInfo->dwTime_PrimeItem_MightofAwell2;
//	smPremiumTime.ManaReduce = lpPlayInfo->dwTime_PrimeItem_ManaReduce;
//	smPremiumTime.PhenixPet = lpPlayInfo->dwTime_PrimeItem_PhenixPet;
//	smPremiumTime.HelpPet = lpPlayInfo->dwTime_PrimeItem_HelpPet;
//	smPremiumTime.VampCuspidEx = lpPlayInfo->dwTime_PrimeItem_VampCuspid_EX;
//	smPremiumTime.StaminaReduce = lpPlayInfo->dwTime_PrimeItem_StaminaReduce;
//	smPremiumTime.BigHead = lpPlayInfo->dwTime_PrimeItem_BigHead;
//	lpPlayInfo->lpsmSock->Send((char*)&smPremiumTime, smPremiumTime.size, TRUE);
//
//
//	smTRANS_COMMAND	smTransCommand;
//	smTransCommand.code = smTRANSCODE_RECV_INIT_DATA;
//	smTransCommand.size = sizeof(smTRANS_COMMAND);
//	lpPlayInfo->lpsmSock->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
//	lpPlayInfo->dwStartUser_PresentItem_Count++;
//	//	break;
//	//}
//
//
//	lpPlayInfo->dwStartUser_PresentItem_Count++;
//	//lpPlayInfo->dwStartUser_PresentItem_Time = dwPlayServTime + 1000 * 1 * 1;
//
//	return TRUE;
//}

int rsSendUserID_MainServer(rsPLAYINFO* lpPlayInfo)
{
	smTRANS_CHAR_COMMAND2	smTransCharCommand;

	smTransCharCommand.code = smTRANSCODE_USER_ID;
	smTransCharCommand.size = sizeof(smTRANS_CHAR_COMMAND2);
	smTransCharCommand.WParam = 0;
	smTransCharCommand.LParam = 0;
	smTransCharCommand.SParam = 0;

	lstrcpy(smTransCharCommand.szId, lpPlayInfo->szID);
	lstrcpy(smTransCharCommand.szName, lpPlayInfo->szName);

	return rsSendGameServer(lpPlayInfo->lpsmSock, &smTransCharCommand);
}

int rsRecvUserID_MainServer(rsPLAYINFO* lpPlayInfo, smTRANS_CHAR_COMMAND2* lpTransCharCommand)
{
	lstrcpy(lpPlayInfo->szUserExpTimeID, lpTransCharCommand->szId);
	lstrcpy(lpPlayInfo->szUserExpTimeName, lpTransCharCommand->szName);

	if (lpPlayInfo->dwExpGameTimeCheck == 0)
		bSql_GetExpGameTime(lpPlayInfo, 0);

	return TRUE;
}

int rsGetExp_GameTime(rsPLAYINFO* lpPlayInfo)
{
	int gTime = lpPlayInfo->dwExpGameTime / (1000 * 60 * 60);

	if (lpPlayInfo->dwExpGameTimeCheck)
	{
		if (gTime < 3)
		{
			return 100;
		}
		else if (gTime < 5)
		{
			return 50;
		}
		return 0;
	}

	return 100;
}

int rsDispay_GameTime(rsPLAYINFO* lpPlayInfo, DWORD dwTimeOld)
{
	int gTime = lpPlayInfo->dwExpGameTime / (1000 * 60);
	int gTimeOld = dwTimeOld / (1000 * 60);
	bool	bDisplay = true;
	int	Remainder = 0;
	int	OldRemainder = 0;
	TRANS_CHATMESSAGE	TransChatMessage;
	memset(&TransChatMessage, 0, sizeof(TRANS_CHATMESSAGE));

	if (gTime >= 1 * 60 && gTimeOld < 1 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_1_00);
	}
	else if (gTime >= 2 * 60 && gTimeOld < 2 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_2_00);
	}

	else if (gTime >= 3 * 60 && gTimeOld < 3 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_3_00);
	}
	else if (gTime >= (3 * 60 + 30) && gTimeOld < (3 * 60 + 30))
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_3_30);
	}
	else if (gTime >= 4 * 60 && gTimeOld < 4 * 60)
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_4_00);
	}
	else if (gTime >= (4 * 60 + 30) && gTimeOld < (4 * 60 + 30))
	{
		wsprintf(TransChatMessage.szMessage, MSG_TL_4_30);
	}

	else if (gTime >= 5 * 60)
	{
		Remainder = gTime % 60;
		OldRemainder = gTimeOld % 60;

		wsprintf(TransChatMessage.szMessage, MSG_TL_X_00);

		if (OldRemainder < 15 && Remainder >= 15)
		{
		}
		else if (OldRemainder < 30 && Remainder >= 30)
		{
		}
		else if (OldRemainder < 45 && Remainder >= 45)
		{
		}
		else if (OldRemainder > Remainder)
		{
		}
		else
		{
			bDisplay = false;
		}
	}

	else
	{
		bDisplay = false;
	}

	if (bDisplay == true)
	{
		TransChatMessage.code = smTRANSCODE_WHISPERMESSAGE;
		TransChatMessage.size = 32 + lstrlen(TransChatMessage.szMessage);
		TransChatMessage.dwIP = 3;
		TransChatMessage.dwObjectSerial = 0;
		lpPlayInfo->lpsmSock->Send((char*)&TransChatMessage, TransChatMessage.size, TRUE);
	}

	return 0;
}

#include "HackTrap.h"

int rsRecvHackTrap(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCharCommand)
{
	smTRANS_COMMAND		smTransCommand;

	switch (lpTransCharCommand->WParam)
	{
	case 100:

		if ((rsHackTrap_FieldNPC[lpTransCharCommand->SParam] & lpTransCharCommand->LParam) == 0) {
			if (lpPlayInfo->WarningCount < 20 || rsServerConfig.TestSeverMode)
			{
				smTransCommand.WParam = 8900;
				smTransCommand.LParam = lpTransCharCommand->SParam;
				smTransCommand.SParam = lpTransCharCommand->LParam;
				RecordHackLogFile(lpPlayInfo, &smTransCommand);
			}
		}
		break;
	}

	return TRUE;
}

#ifdef _CHECK_MESH

static DWORD	dwItemMeshCode = 0;
int rsRecvCheckItemMesh(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	smTRANS_COMMAND		smTransCommand;

	if (!dwItemMeshCode) {
		dwItemMeshCode = lpTransCommand->WParam;
		return TRUE;
	}

	if (dwItemMeshCode != lpTransCommand->WParam) {
		smTransCommand.WParam = 8910;
		smTransCommand.LParam = dwItemMeshCode;
		smTransCommand.SParam = lpTransCommand->WParam;
		RecordHackLogFile(lpPlayInfo, &smTransCommand);

		lpPlayInfo->dwHopeDisconnectTime = dwPlayServTime + 60 * 1000;
	}

	return TRUE;
}
#endif

DWORD ManufactureCheckRune(rsPLAYINFO* lpPlayInfo, DWORD RecipeCode, DWORD* pRuneCode)
{
	int RuneCnt = 0;
	DWORD Arm_Armor_Code[11] = { sin01, sin02, sin03, sin04, sin05, sin06, sin07, sin08, sin09, sin10, sin11 };
	DWORD CheckRuneCode[11][8][3] = { {	{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },
										{ (sinPR3 | sin01), (sinPR3 | sin02), (sinPR4 | sin03) },
										{ (sinPR3 | sin01), (sinPR4 | sin02), (sinPR3 | sin03) },
										{ (sinPR3 | sin01), (sinPR4 | sin02), (sinPR4 | sin03) },
										{ (sinPR4 | sin01), (sinPR3 | sin02), (sinPR3 | sin03) },
										{ (sinPR4 | sin01), (sinPR3 | sin02), (sinPR4 | sin03) },
										{ (sinPR4 | sin01), (sinPR4 | sin02), (sinPR3 | sin03) },
										{ (sinPR4 | sin01), (sinPR4 | sin02), (sinPR4 | sin03) }
 },

{  { (sinPR3 | sin02), (sinPR3 | sin03), (sinPR3 | sin04) },
   { (sinPR3 | sin02), (sinPR3 | sin03), (sinPR4 | sin04) },
   { (sinPR3 | sin02), (sinPR4 | sin03), (sinPR3 | sin04) },
   { (sinPR3 | sin02), (sinPR4 | sin03), (sinPR4 | sin04) },
   { (sinPR4 | sin02), (sinPR3 | sin03), (sinPR3 | sin04) },
   { (sinPR4 | sin02), (sinPR3 | sin03), (sinPR4 | sin04) },
   { (sinPR4 | sin02), (sinPR4 | sin03), (sinPR3 | sin04) },
   { (sinPR4 | sin02), (sinPR4 | sin03), (sinPR4 | sin04) } },

{  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
   { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
   { (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
   { (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
   { (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
   { (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
   { (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
   { (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },

{  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
   { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
   { (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
   { (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
   { (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
   { (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
   { (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
   { (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },

{	{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
	{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
	{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
	{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
	{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
	{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
	{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
	{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },

{  { (sinPR3 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
	{ (sinPR3 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
	{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
	{ (sinPR3 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) },
	{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR3 | sin05) },
	{ (sinPR4 | sin03), (sinPR3 | sin04), (sinPR4 | sin05) },
	{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR3 | sin05) },
	{ (sinPR4 | sin03), (sinPR4 | sin04), (sinPR4 | sin05) } },

{  { (sinPR3 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },
	{ (sinPR3 | sin04), (sinPR3 | sin05), (sinPR4 | sin06) },
	{ (sinPR3 | sin04), (sinPR4 | sin05), (sinPR3 | sin06) },
	{ (sinPR3 | sin04), (sinPR4 | sin05), (sinPR4 | sin06) },
	{ (sinPR4 | sin04), (sinPR3 | sin05), (sinPR3 | sin06) },
	{ (sinPR4 | sin04), (sinPR3 | sin05), (sinPR4 | sin06) },
	{ (sinPR4 | sin04), (sinPR4 | sin05), (sinPR3 | sin06) },
	{ (sinPR4 | sin04), (sinPR4 | sin05), (sinPR4 | sin06) } },

{  { (sinPR3 | sin05), (sinPR3 | sin06), (sinPR3 | sin07) },
	{ (sinPR3 | sin05), (sinPR3 | sin06), (sinPR4 | sin07) },
	{ (sinPR3 | sin05), (sinPR4 | sin06), (sinPR3 | sin07) },
	{ (sinPR3 | sin05), (sinPR4 | sin06), (sinPR4 | sin07) },
	{ (sinPR4 | sin05), (sinPR3 | sin06), (sinPR3 | sin07) },
	{ (sinPR4 | sin05), (sinPR3 | sin06), (sinPR4 | sin07) },
	{ (sinPR4 | sin05), (sinPR4 | sin06), (sinPR3 | sin07) },
	{ (sinPR4 | sin05), (sinPR4 | sin06), (sinPR4 | sin07) } },

{  { (sinPR3 | sin06), (sinPR3 | sin07), (sinPR3 | sin08) },
	{ (sinPR3 | sin06), (sinPR3 | sin07), (sinPR4 | sin08) },
	{ (sinPR3 | sin06), (sinPR4 | sin07), (sinPR3 | sin08) },
	{ (sinPR3 | sin06), (sinPR4 | sin07), (sinPR4 | sin08) },
	{ (sinPR4 | sin06), (sinPR3 | sin07), (sinPR3 | sin08) },
	{ (sinPR4 | sin06), (sinPR3 | sin07), (sinPR4 | sin08) },
	{ (sinPR4 | sin06), (sinPR4 | sin07), (sinPR3 | sin08) },
	{ (sinPR4 | sin06), (sinPR4 | sin07), (sinPR4 | sin08) } },

{  { (sinPR3 | sin09), (sinPR4 | sin10), (sinPR3 | sin11) },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 } },

{  { (sinPR3 | sin12), (sinPR3 | sin13), (sinPR3 | sin14) },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 },
	{ 0,0,0 } }
	};

	DWORD	dwItem = 0;

	if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS) dwItem = (sinDA2 | sin52);

	else if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN) dwItem = (sinDA2 | sin51);

	else if (lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ARCHER || lpPlayInfo->smCharInfo.JOB_CODE == JOBCODE_ATALANTA) dwItem = (sinDA1 | sin52);

	else dwItem = (sinDA1 | sin51);

	DWORD CreateItemCode[2][11][8] = { {	{ (sinWA1 | sin14), (sinWC1 | sin14), (sinWH1 | sin15), (sinWP1 | sin15), (sinWS1 | sin16), (sinWS2 | sin17), (sinWT1 | sin15), (sinWM1 | sin15) },
											{ (sinWA1 | sin15), (sinWC1 | sin15), (sinWH1 | sin16), (sinWP1 | sin16), (sinWS1 | sin17), (sinWS2 | sin18), (sinWT1 | sin16), (sinWM1 | sin16) },
											{ (sinWA1 | sin16), (sinWC1 | sin16), (sinWH1 | sin17), (sinWP1 | sin17), (sinWS1 | sin18), (sinWS2 | sin19), (sinWT1 | sin17), (sinWM1 | sin17) },
											{ (sinWA1 | sin17), (sinWC1 | sin17), (sinWH1 | sin18), (sinWP1 | sin18), (sinWS1 | sin19), (sinWS2 | sin20), (sinWT1 | sin18), (sinWM1 | sin18) },
											{ (sinWA1 | sin18), (sinWC1 | sin18), (sinWH1 | sin19), (sinWP1 | sin19), (sinWS1 | sin20), (sinWS2 | sin21), (sinWT1 | sin19), (sinWM1 | sin19) },
											{ (sinWA1 | sin19), (sinWC1 | sin19), (sinWH1 | sin20), (sinWP1 | sin20), (sinWS1 | sin21), (sinWS2 | sin22), (sinWT1 | sin20), (sinWM1 | sin20) },
											{ (sinWA1 | sin21), (sinWC1 | sin21), (sinWH1 | sin22), (sinWP1 | sin22), (sinWS1 | sin23), (sinWS2 | sin24), (sinWT1 | sin22), (sinWM1 | sin22) },
											{ (sinWA1 | sin22), (sinWC1 | sin22), (sinWH1 | sin23), (sinWP1 | sin23), (sinWS1 | sin24), (sinWS2 | sin25), (sinWT1 | sin23), (sinWM1 | sin23) },
											{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
											{ 0, 0, 0, 0, 0, 0, 0, 0 } ,
											{ 0, 0, 0, 0, 0, 0, 0, 0}},

										{	{ (sinDA1 | sin16), (sinDA2 | sin16), (sinDS1 | sin14), (sinOM1 | sin15), (sinDG1 | sin14), (sinOA2 | sin14), (sinDB1 | sin14), 0 },
											{ (sinDA1 | sin17), (sinDA2 | sin17), (sinDS1 | sin15), (sinOM1 | sin16), (sinDG1 | sin15), (sinOA2 | sin15), (sinDB1 | sin15), 0 },
											{ (sinDA1 | sin18), (sinDA2 | sin18), (sinDS1 | sin16), (sinOM1 | sin17), (sinDG1 | sin16), (sinOA2 | sin16), (sinDB1 | sin16), 0 },
											{ (sinDA1 | sin19), (sinDA2 | sin19), (sinDS1 | sin17), (sinOM1 | sin18), (sinDG1 | sin17), (sinOA2 | sin17), (sinDB1 | sin17), 0 },
											{ (sinDA1 | sin20), (sinDA2 | sin20), (sinDS1 | sin18), (sinOM1 | sin19), (sinDG1 | sin18), (sinOA2 | sin18), (sinDB1 | sin18), 0 },
											{ (sinDA1 | sin21), (sinDA2 | sin21), (sinDS1 | sin19), (sinOM1 | sin20), (sinDG1 | sin19), (sinOA2 | sin19), (sinDB1 | sin19), 0 },
											{ (sinDA1 | sin23), (sinDA2 | sin23), (sinDS1 | sin21), (sinOM1 | sin22), (sinDG1 | sin21), (sinOA2 | sin21), (sinDB1 | sin21), 0 },
											{ (sinDA1 | sin24), (sinDA2 | sin24), (sinDS1 | sin22), (sinOM1 | sin23), (sinDG1 | sin22), (sinOA2 | sin22), (sinDB1 | sin22), 0 },
											{ 0, 0, 0, 0, 0, 0, 0, 0 },
											{ (sinOA1 | sin36), 0, 0, 0, 0, 0, 0},
											{ dwItem, 0, 0, 0, 0, 0, 0}}
	};
	if ((RecipeCode & sinITEM_MASK2) == sinWR1)
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (RecipeCode & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++)
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pRuneCode[y + 1])
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							return CreateItemCode[0][i][j];
						}
					}
				}
			}
		}
	}
	else if ((RecipeCode & sinITEM_MASK2) == sinDR1)
	{
		for (int i = 0; i < MAX_RECIPE_KIND; i++)
		{
			if (Arm_Armor_Code[i] == (RecipeCode & sinITEM_MASK3))
			{
				for (int j = 0; j < MAX_RUNE; j++)
				{
					RuneCnt = 0;
					for (int x = 0; x < 3; x++)
					{
						for (int y = 0; y < 3; y++)
						{
							if (CheckRuneCode[i][j][x] == pRuneCode[y + 1])
							{
								RuneCnt++;
								break;
							}
						}
						if (RuneCnt == 3)
						{
							if (j == 7)
							{
								int ArmorRand = 0;
								ArmorRand = rand() % 7;
								return CreateItemCode[1][i][ArmorRand];
							}
							return CreateItemCode[1][i][j];
						}
					}
				}
			}
		}
	}
	return FALSE;
}

int rsPutItem_TreasureBox(rsPLAYINFO* lpPlayInfo, DWORD Code)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int nClass = 0;
	int Randum[6][8] =
	{
		{ 2000, 2900, 1000, 1500, 1000, 100, 750, 750 },
		{ 2600, 2620, 700, 1000, 1500, 80, 750, 750 },
		{ 2750, 2400, 800, 1500, 1000, 50, 750, 750 },
		{ 2450, 2850, 500, 1500, 1000, 200, 750, 750 },
		{ 2320, 2000, 1500, 1500, 1000, 180, 750, 750 },
		{ 2850, 2000, 1000, 1500, 1000, 150, 750, 750 }
	};

	switch ((Code & sinITEM_MASK3))
	{
	case sin05:
		nClass = 0;
		break;
	case sin06:
		nClass = 1;
		break;
	case sin07:
		nClass = 2;
		break;
	case sin08:
		nClass = 3;
		break;
	case sin09:
		nClass = 4;
		break;
	case sin10:
		nClass = 5;
		break;
	}

	int CodeCount = 0;
	int RndNum = rand() % 10000;
	int RndCnt = 0;
	for (cnt = 0; cnt < 8; cnt++)
	{
		if (Randum[nClass][CodeCount])
		{
			RndCnt += Randum[nClass][cnt];
			if (RndNum < RndCnt)
			{
				CodeCount = cnt;
				break;
			}
		}
	}

	DWORD ItemCode[6][8] =
	{
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin19), (sinFO1 | sin08),(sinFO1 | sin08), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin19), (sinFO1 | sin08),(sinFO1 | sin07), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin04), (sinBI1 | sin08), (sinGP1 | sin18), (sinFO1 | sin07),(sinFO1 | sin06), (sinBI2 | sin09), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin03), (sinBI1 | sin08), (sinGP1 | sin18), (sinFO1 | sin06),(sinFO1 | sin05), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin03), (sinBI1 | sin08), (sinGP1 | sin17), (sinFO1 | sin04),(sinFO1 | sin04), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) },
		{ (sinPM1 | sin02), (sinBI1 | sin08), (sinGP1 | sin17), (sinFO1 | sin04),(sinFO1 | sin04), (sinBI2 | sin05), (sinBI1 | sin21), (sinBI1 | sin19) }
	};
	if ((Code & sinITEM_MASK2) == sinSP1)
	{
		for (int j = 0; j < DefaultItemCount; j++)
		{
			if (ItemCode[nClass][CodeCount] == DefaultItems[j].Item.CODE)
			{
				CreateDefItem(&psItem.ItemInfo, &DefaultItems[j]);
				if (CodeCount == 0)
				{
					psItem.ItemInfo.PotionCount = 10;
				}
				if (lpPlayInfo->lpsmSock)
				{
					TransItemInfo.code = smTRANSCODE_PUTITEM;
					TransItemInfo.size = sizeof(TRANS_ITEMINFO);
					memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));

					ReformItem(&TransItemInfo.Item);
					rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
					lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
				}
				return TRUE;
			}
		}
	}
	return TRUE;
}

void rsPresentBox(rsPLAYINFO* lpPlayInfo, DWORD Code)
{
	int i = 0;
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		char szCode[32];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[Artifact] WHERE Code=%d", Code);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			while (SQL::GetInstance()->Fetch()) i++;

			wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[Artifact] WHERE Code=%d", Code);
			if (SQL::GetInstance()->Execute(szQuery))
			{
				int Rand = rand() % i;
				i = 0;

				while (SQL::GetInstance()->Fetch())
				{
					if (Rand == i)
					{
						SQL::GetInstance()->GetDataValue(1, szCode);
						SendItemToPlayer(lpPlayInfo, szCode, 0);
						break;
					}

					i++;
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

int rsPutItem_CapsuleItem(rsPLAYINFO* lpPlayInfo, DWORD Code)
{
	TRANS_ITEMINFO	TransItemInfo;
	psITEM	psItem;
	int cnt;
	int nClass = 0;
	int Randum[1][12] =
	{
		{ 1000, 500, 1000,  1000,  1000,  800, 1000, 600,  1000,  1000,  800, 300}
	};

	switch ((Code & sinITEM_MASK3))
	{
	case sin34:
		nClass = 0;
		break;
	}

	int CodeCount = 0;
	int RndNum = rand() % 10000;
	int RndCnt = 0;
	for (cnt = 0; cnt < 12; cnt++)
	{
		if (Randum[nClass][CodeCount])
		{
			RndCnt += Randum[nClass][cnt];
			if (RndNum < RndCnt)
			{
				CodeCount = cnt;
				break;
			}
		}
	}

	DWORD ItemCode[1][12] =
	{
		{ (sinFO1 | sin06), (sinFO1 | sin06), (sinFO1 | sin07), (sinFO1 | sin08), (sinFO1 | sin09), (sinFO1 | sin10),
		(sinFO1 | sin25), (sinFO1 | sin25), (sinFO1 | sin26), (sinFO1 | sin27), (sinFO1 | sin28), (sinSE1 | sin01) }
	};

	if ((Code & sinITEM_MASK2) == sinSP1)
	{
		for (int j = 0; j < DefaultItemCount; j++)
		{
			if (ItemCode[nClass][CodeCount] == DefaultItems[j].Item.CODE)
			{
				CreateDefItem(&psItem.ItemInfo, &DefaultItems[j]);
				if (CodeCount == 10 || CodeCount == 11)
				{
					psItem.ItemInfo.PotionCount = 30;
				}

				if (lpPlayInfo->lpsmSock)
				{
					TransItemInfo.code = smTRANSCODE_PUTITEM;
					TransItemInfo.size = sizeof(TRANS_ITEMINFO);
					memcpy(&TransItemInfo.Item, &psItem.ItemInfo, sizeof(sITEMINFO));
					ReformItem(&TransItemInfo.Item);
					rsRegist_ItemSecCode(lpPlayInfo, &TransItemInfo, 1);
					lpPlayInfo->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);
				}
				return TRUE;
			}
		}
	}
	return TRUE;
}

int rsSendAreaOpenKidMonster(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar)
{
	int cnt2;

	for (cnt2 = 0; cnt2 < srKIDMONSTER_MAX; cnt2++)
	{
		if (lstrcmp(lpChar->smCharInfo.szName, srOpenKidMonster[cnt2].szParentMonName) == 0)
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_OPENMONSTER;
			smTransCommand.WParam = lpChar->pX;
			smTransCommand.SParam = lpChar->pY;
			smTransCommand.LParam = lpChar->pZ;
			smTransCommand.EParam = srOpenKidMonster[cnt2].mon_Num;;
			rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);

			break;
		}
	}

	return TRUE;
}

int rsOpenKidMonster(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand, int mon_Num)
{
	int x = 0;
	int z = 0;
	STG_AREA* lpStgArea;
	STG_CHAR_INFO	StgCharInfo;
	smCHAR* lpChar;

	for (int cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if (lstrcmp(chrMonsterList[cnt].szName, srOpenKidMonster[mon_Num].szChildMonName) == 0)
		{
			for (int i = 0; i < srOpenKidMonster[mon_Num].mon_Count; i++)
			{
				x = rand() % (128 * fONE);
				z = rand() % (128 * fONE);
				x -= 64 * fONE;
				z -= 64 * fONE;
				lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);

				if (lpStgArea)
				{
					StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
					StgCharInfo.smCharInfo.Life[0] = 100;
					StgCharInfo.smCharInfo.Mana[0] = 100;
					StgCharInfo.smCharInfo.Life[1] = 100;
					StgCharInfo.smCharInfo.State = TRUE;

					memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));

					lpStgArea->EvnMonster = TRUE;
					lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
					if (lpChar)
					{
						lpChar->pX = lpTransCommand->WParam + x;
						lpChar->pY = lpTransCommand->SParam;
						lpChar->pZ = lpTransCommand->LParam + z;
						lpChar->DistAroundDbl = 0;
						lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
						lpChar->TargetMoveCount = 0;

						smTRANS_COMMAND_EX	TransCommandEx;

						ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
						TransCommandEx.WParam = smCOMMNAD_USER_WARP;
						TransCommandEx.LParam = lpTransCommand->WParam + x;
						TransCommandEx.SParam = lpTransCommand->SParam;
						TransCommandEx.EParam = lpTransCommand->LParam + z;
						rsSendCommandUser(lpPlayInfo, &TransCommandEx);
					}
				}
			}
			break;
		}
	}

	return TRUE;
}

int rsSendAreaOpenSODGuardMonster(rsPLAYINFO* lpPlayInfo, smCHAR* lpChar)
{
	int cnt2;

	for (cnt2 = 0; cnt2 < srSOD_GUARD_MONSTER_MAX; cnt2++)
	{
		if (lstrcmp(lpChar->smCharInfo.szName, srOpenSODCrystalGuardMonster[cnt2].szParentMonName) == 0)
		{
			smTRANS_COMMAND smTransCommand;
			smTransCommand.size = sizeof(smTRANS_COMMAND);
			smTransCommand.code = smTRANSCODE_OPENMONSTER;
			smTransCommand.WParam = lpChar->pX;
			smTransCommand.SParam = lpChar->pY;
			smTransCommand.LParam = lpChar->pZ;
			smTransCommand.EParam = srOpenSODCrystalGuardMonster[cnt2].mon_Num;
			rsSendAreaServer(lpPlayInfo->lpsmSock, &smTransCommand);

			break;
		}
	}

	return TRUE;
}

int rsOpenSODGuardMonster(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand, int mon_Num)
{
	int x = 0;
	int z = 0;
	STG_AREA* lpStgArea;
	STG_CHAR_INFO	StgCharInfo;
	smCHAR* lpChar;
	int mon_x = 0;
	int mon_z = 0;
	int dist = 0;
	int rand_num = 0;

	if (mon_Num == 4)
	{
		rand_num = 4;
	}
	else
		rand_num = GetRandomPos(0, 2);

	for (int cnt = 0; cnt < chrMonsterCnt; cnt++)
	{
		if (lstrcmp(chrMonsterList[cnt].szName, srOpenSODCrystalGuardMonster[rand_num].szChildMonName) == 0)
		{
			for (int j = 0; j < 7; j++)
			{
				if (lpPlayInfo->Position.Area == rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][0])
				{
					mon_x = abs(lpTransCommand->WParam / fONE - rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1]);
					mon_z = abs(lpTransCommand->LParam / fONE - rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2]);
					dist = mon_x * mon_x + mon_z * mon_z;
					if (dist < 300 * 300)
					{
						for (int i = 0; i < srOpenSODCrystalGuardMonster[rand_num].mon_Count; i++)
						{
							x = rand() % (128 * fONE);
							z = rand() % (128 * fONE);
							x -= 64 * fONE;
							z -= 64 * fONE;
							lpStgArea = FindStageField(lpPlayInfo->Position.x, lpPlayInfo->Position.z);

							if (lpStgArea)
							{
								StgCharInfo.PosiState = smCHAR_STATE_ENEMY;
								StgCharInfo.smCharInfo.Life[0] = 100;
								StgCharInfo.smCharInfo.Mana[0] = 100;
								StgCharInfo.smCharInfo.Life[1] = 100;
								StgCharInfo.smCharInfo.State = TRUE;

								memcpy(&StgCharInfo.smCharInfo, &chrMonsterList[cnt], sizeof(smCHAR_INFO));

								lpStgArea->EvnMonster = TRUE;
								lpChar = lpStgArea->OpenMonster(&StgCharInfo, 0);
								if (lpChar)
								{
									lpChar->pX = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									lpChar->pY = lpTransCommand->SParam;
									lpChar->pZ = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									lpChar->PosiAround.x = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									lpChar->PosiAround.y = lpTransCommand->SParam;
									lpChar->PosiAround.z = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									lpChar->DistAroundDbl = DIST_AROUND_MIDDLE;
									lpChar->SetMotionFromCode(CHRMOTION_STATE_STAND);
									lpChar->TargetMoveCount = 0;

									smTRANS_COMMAND_EX	TransCommandEx;

									ZeroMemory(&TransCommandEx, sizeof(smTRANS_COMMAND_EX));
									TransCommandEx.WParam = smCOMMNAD_USER_WARP;
									TransCommandEx.LParam = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][1] * fONE + x;
									TransCommandEx.SParam = lpTransCommand->SParam;
									TransCommandEx.EParam = rsSOD_CRYSTAL_GUARD_MONSTER_POS[j][2] * fONE + z;
									rsSendCommandUser(lpPlayInfo, &TransCommandEx);
								}
							}
						}
					}
				}
			}
			break;
		}
	}

	return TRUE;
}

int rsFiltChatMsg(rsPLAYINFO* lpPlayInfo, char* szMsg, int len)
{
	sveFiltChatMsg(lpPlayInfo, szMsg, len);

	return TRUE;
}

int rsRecvEventGame(rsPLAYINFO* lpPlayInfo, smTRANS_COMMAND* lpTransCommand)
{
	switch (lpTransCommand->WParam)
	{
	case smCODE_EVENT_STATE_INIT:
		rsEventGame_State_Init(lpPlayInfo, lpTransCommand);
		break;
	}

	return TRUE;
}

int	rsUseSoccerBallPotionItem(DWORD dwItemCode, rsPLAYINFO* lpPlayInfo)
{
	smTRANS_COMMAND	smTransCommand;

	if (dwItemCode != (sinSP1 | sin40))
		return -1;

	switch (dwItemCode)
	{
	case (sinSP1 | sin40):
		smTransCommand.size = sizeof(smTRANS_COMMAND);
		smTransCommand.code = smTRANSCODE_COMIC_SKIN;
		smTransCommand.WParam = 3;
		smTransCommand.LParam = 60 * 60 * 3;
		smTransCommand.SParam = 1;
		smTransCommand.EParam = 0;
		lpPlayInfo->lpsmSock->Send2((char*)&smTransCommand, smTransCommand.size, TRUE);
		break;
	}

	return TRUE;
}

int SetAgingItem(sITEMINFO* pItem, int AgingNum)
{
	if (!AgingNum) return TRUE;

	pItem->ItemKindCode = ITEM_KIND_AGING;

	for (int i = 0; i < AgingNum; i++)
	{
		sinSetAgingItemIncreState(pItem);
	}

	return TRUE;
}

int GetDaysCountMonth(int iMonth, int iYear)
{
	if ((iMonth == 4) || (iMonth == 6) || (iMonth == 9) || (iMonth == 11))
		return 30;
	else if (iMonth == 2)
	{
		if (((iYear % 400) == 0) || (((iYear % 4) == 0) && ((iYear % 100) != 0)))
			return 29;
		else
			return 28;
	}

	return 31;
}

DWORD SystemTimeToDWORD(SYSTEMTIME* ps)
{
	if (ps == NULL)
		return NULL;

	DWORD dw;
	int iDM = GetDaysCountMonth(ps->wMonth, ps->wYear);

	dw = ps->wSecond + (ps->wMinute * 60) + (ps->wHour * 60 * 60) + (ps->wDay * 60 * 60 * 24) + (ps->wMonth * 60 * 60 * 24 * iDM);

	return dw;
}

SYSTEMTIME sLocalTimeServer;

static SYSTEMTIME* GetServerTime()
{
	GetLocalTime(&sLocalTimeServer);
	return &sLocalTimeServer;
}

void SendNextBoss(rsPLAYINFO* Player, int MapID)
{
	if (MapID && MapID < FIELD_MAX)
	{
		STG_AREA* lpStgArea;
		// lpStgArea = FindStageField(Player->Position.x, Player->Position.z);

		lpStgArea = FindStageFieldNum(MapID);

		if (lpStgArea)
		{
			SYSTEMTIME sBossTime;
			CopyMemory(&sBossTime, GetServerTime(), sizeof(SYSTEMTIME));

			DWORD dwLessTimeBoss = 0;
			char pszBossName[255] = { 0 };

			//Get Boss Time
			for (int i = 0; i < lpStgArea->rsMonsterList.BossMonsterCount; i++)
			{
				for (int j = 0; j < lpStgArea->rsMonsterList.sBossMonsters[i].OpenTimeCount; j++)
				{
					//Get Boss Time
					sBossTime.wHour = lpStgArea->rsMonsterList.sBossMonsters[i].bOpenTime[j];
					sBossTime.wMinute = OpenBossTimeMin;
					sBossTime.wSecond = 0;

					//After the Time?
					if (sBossTime.wMinute >= GetServerTime()->wMinute)
					{
						//If Boss was spawned at the current boss time on loop, go to the next day...
						if (sBossTime.wHour < GetServerTime()->wHour)
							sBossTime.wDay++;
					}

					DWORD dwBossTime = SystemTimeToDWORD(&sBossTime);
					DWORD dwServerTime = SystemTimeToDWORD(GetServerTime());
					if (dwBossTime >= dwServerTime)
					{
						DWORD dwDifference = dwBossTime - dwServerTime;
						if ((dwLessTimeBoss > dwDifference) || (dwLessTimeBoss == 0))
						{
							sprintf_s(pszBossName, "%s", lpStgArea->rsMonsterList.sBossMonsters[i].MasterMonster->szName);
							// pszBossName = pcMap->sSpawnSetting.saBoss[i].cdBoss->szName;
							dwLessTimeBoss = dwDifference;
						}
					}

					//Backup Time
					CopyMemory(&sBossTime, GetServerTime(), sizeof(SYSTEMTIME));
				}
			}

			PacketMap packet = { 0 };
			packet.code = smTRANSCODE_BOSS_TIME;
			packet.size = sizeof(PacketMap);
			packet.dwTime = dwLessTimeBoss;
			packet.iMapID = MapID;
			sprintf_s(packet.szBossName, "%s", pszBossName);

			if (Player && Player->lpsmSock)
				Player->lpsmSock->Send2((char*)&packet, packet.size, TRUE);
		}
	}
}