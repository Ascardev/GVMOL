#ifndef	_SMPACKET_HEADER

#define _SMPACKET_HEADER

#include	"sinItem.h"
#include	<atltime.h>

#define smTRANSCODE_ROLLDICE_START 0xA0000000
#define smTRANSCODE_ROLLDICE_UPDATE 0xA0000001
#define smTRANSCODE_ROLLDICE_END 0xA0000002

#define smTRANSCODE_OPEN_REMODEL    	0x60000000
#define smTRANSCODE_REMODEL_ITEM	    0x60000001

#define smTRANSCODE_PROGRESS_QUEST  0x70000000
#define smTRANSCODE_CANCEL_QUEST    0x70000001

#define	smTRANSCODE_MECH_INFO		  0x58480000
#define	smTRANSCODE_FIGHTER_INFO	  0x58480001
#define	smTRANSCODE_PIKE_INFO		  0x58480002
#define	smTRANSCODE_ARCHER_INFO	      0x58480003
#define	smTRANSCODE_KINA_INFO		  0x58480004
#define	smTRANSCODE_ATA_INFO		  0x58480005
#define	smTRANSCODE_SACER_INFO		  0x58480006
#define	smTRANSCODE_MAGE_INFO		  0x58480007
#define smTRANSCODE_ASSASSIN_INFO     0x58470008
#define smTRANSCODE_SHAMAN_INFO       0x58470009
#define smTRANSCODE_MARTIAL_INFO      0x5847000A

#define smTRANSCODE_AGING_INFO        0x48480008
#define smTRANSCODE_FIELD_LEVEL       0x48480009
#define smTRANSCODE_RECV_VIP          0x4848000A
#define smTRANSCODE_BOSS_TIME          0X4848000B

#define smTRANSCODE_ALERTAKILL			0X4841004A

#define smTRANSCODE_PING                        0x49000000
#define smTRANSCODE_CHAT_DELAY                  0x49000001
#define smTRANSCODE_SEND_COIN_SHOP_LIST         0x49000003
#define smTRANSCODE_SEND_COIN_SHOP_COIN         0x49470004
#define smTRANSCODE_RECV_BUY_COIN_SHOP          0x49470005
#define smTRANSCODE_SEND_TIME_SHOP_LIST         0x49000006
#define smTRANSCODE_SEND_TIME_SHOP_TIME         0x49470007
#define smTRANSCODE_RECV_BUY_TIME_SHOP          0x49470008
#define smTRANSCODE_PREMIUM_CANCEL              0x49000009
#define smTRANSCODE_RECV_STATE_QUEST_DIARY      0x4900000A
#define smTRANSCODE_UPDATE_QUEST_DIARY          0x4900000B
#define smTRANSCODE_SHOWITEMINFO_PERF           0x4900000C
#define smTRANSCODE_UPDATE_BELLATRA             0x4900000D
#define smTRANSCODE_QADDEXP                     0x4900000E
#define smTRANSCODE_RECV_INIT_DATA              0x4900000F
#define smTRANSCODE_FORCE_ORB_CANCEL            0x49000010
#define smTRANSCODE_TOP_PVP                     0x49000011
#define smTRANSCODE_TOP_LVL                     0x49000012
#define smTRANSCODE_POINTS                      0x49000013
#define smTRANSCODE_TYPE                        0x49000014
#define smTRANSCODE_PVP_MODE                    0x49000015
#define smTRANSCODE_BA_ENTER                    0x49000016
#define smTRANSCODE_PVP_EXP                     0x49000017
#define smTRANSCODE_SET_CLASS                   0x49000018
#define smTRANSCODE_BLESSCROWN                  0x49000019
#define smTRANSCODE_SKILL_DISABLED              0x49000020
#define smTRANSCODE_SKILL_DELAY                 0x49000021
#define smTRANSCODE_SEND_CHANGE_ITEM            0x49000022
#define smTRANSCODE_ITEM_CLASS                  0x49000023
#define smTRANSCODE_HACK_ALERT                  0x49000024
#define smTRANSCODE_WAREHOUSE_PAGE              0x49000025
#define smTRANSCODE_PLAYER_MIGRATION            0x49000026
#define smTRANSCODE_PLAYER_ACTION               0x49000027
#define smTRANSCODE_MODULES                     0x49000028
#define smTRANSCODE_BATTLE_ARENA                0x49000029
#define smTRANSCODE_BATTLE_ARENA_RANKING        0x49000030
#define smTRANSCODE_PLAYER_KILLED               0X49000031
#define smTRANSCODE_BATTLE_EXP                  0x49000032

#define smTRANSCODE_BATTLE_EVENT                0x49000032
#define smTRANSCODE_BATTLE_EVENT_RANKING        0x49000033
#define smTRANSCODE_CHECKSUM_SKILL              0x49000034
#define smTRANSCODE_AWARD_ITEM                  0x49000035
#define smTRANSCODE_OPEN_AWARD_ITEM             0x49000036
#define smTRANSCODE_ROULETTE_ITEM               0x49000037
#define smTRANSCODE_OPEN_ROULETTE_ITEM          0x49000038
#define smTRANSCODE_HELL_GATES                  0x49000039
#define smTRANSCODE_PUZZLE                      0x49000040
#define smTRANSCODE_UPDATE_ITEM                 0X49000041
#define smTRANSCODE_UPDATE_ITEM_LIST            0X49000042
#define smTRANSCODE_NATAL                      0x49000043
#define smTRANSCODE_WORLDCUP                      0x49000044

#define	smTRANSCODE_OPENLIVE		0x38000000

#define	smTRANSCODE_SYSTEM			0x48400000

#define smTRANSCODE_AGINGEVENTO		0x8190000A
#define	smTRANSCODE_CONNECTED		0x48470080
#define smTRANSCODE_RECORDDATA		0x48470081
#define smTRANSCODE_GETRECORDDATA	0x48470082
#define smTRANSCODE_FAILRECORDDATA	0x48470083
#define smTRANSCODE_RECORDRESULT	0x48470084

#define smTRANSCODE_ID_GETUSERINFO	0x48470085
#define smTRANSCODE_ID_SETUSERINFO	0x48470086
#define smTRANSCODE_DELRECORDDATA	0x48470087
#define smTRANSCODE_INSRECORDDATA	0x48470088
#define smTRANSCODE_ISRECORDDATA	0x48470089

#define smTRANSCODE_VERSION			0x4847008A

#define smTRANSCODE_CHECK_NETSTATE	0x4847008B

#define smTRANSCODE_ADMINMODE		0x4847008C

#define smTRANSCODE_SET_OBJSERIAL	0x4847008D

#define smTRANSCODE_CHECK_NETSTATE2	0x4847008E
#define smTRANSCODE_CHECK_NETSTATE3	0x4847008F
#define smTRANSCODE_CHECK_NETSTATE4	0x48470090
#define smTRANSCODE_CHECK_NETSTATE5	0x48470091

#define smTRANSCODE_IPLIST			0x48471000
#define smTRANSCODE_CHATMESSAGE		0x48471001
#define smTRANSCODE_POSITION		0x48471002
#define smTRANSCODE_PLAYLIST		0x48471003
#define smTRANSCODE_CONTINUEDATA	0x48471004
#define smTRANSCODE_WHISPERMESSAGE	0x48471005
#define smTRANSCODE_COUPLERING		0x48471006

#define smTRANSCODE_PLAYDATA1		0x48470010
#define smTRANSCODE_PLAYDATA2		0x48470011
#define smTRANSCODE_PLAYDATA3		0x48470012
#define smTRANSCODE_TRANSPLAYDATA	0x48470013
#define smTRANSCODE_PLAYDATAGROUP	0x48470014
#define smTRANSCODE_PLAY_COMMAND	0x48470018

#define smTRANSCODE_PARTY_CHATMSG	0x48471015

#define smTRANSCODE_ADDEXP_PARTY	0x48470029
#define smTRANSCODE_ATTACKDATA		0x48470030
#define smTRANSCODE_ADDEXP			0x48470031
#define smTRANSCODE_PLAYERINFO2		0x48470032
#define smTRANSCODE_SET_BLACKLIST	0x48470033
#define smTRANSCODE_SET_ITEMCOPYLIST 0x48470034
#define smTRANSCODE_SKIL_ATTACKDATA	0x48470035
#define smTRANSCODE_FINDCRACK		0x48470036
#define smTRANSCODE_MODULE_WARNIG	0x48470037
#define smTRANSCODE_UPDATE_CINFO	0x48470038
#define smTRANSCODE_OPENMONSTER		0x48470039
#define smTRANSCODE_WARPFIELD		0x48470040
#define smTRANSCODE_TRADEITEMS		0x48470041
#define smTRANSCODE_TRADE_REQUST	0x48470042
#define smTRANSCODE_TRADE_ITEMKEY	0x48470043
#define smTRANSCODE_TRADE_READYITEM	0x60000002
#define smTRANSCODE_SKILL_MENU		0x48470045
#define smTRANSCODE_FINDCRACK2		0x48470046
#define smTRANSCODE_WAREHOUSE		0x48470047

#define smTRANSCODE_OPEN_WAREHOUSE	0x48470048
#define smTRANSCODE_OPEN_MIXITEM	0x60000102
#define smTRANSCODE_OPEN_COLLECT	0x4847004A
#define smTRANSCODE_COLLECTMONEY	0x4847004B
#define	smTRANSCODE_PLAYERINFO_Q	0x4847004C
#define smTRANSCODE_OPEN_AGING		0x60000142

#define smTRANSCODE_SKIL_ATTACKUSER	0x4847004E

#define smTRANSCODE_OPEN_EVENTGIFT	0x4847004F

#define smTRANSCODE_PLAYERINFO		0x48470020
#define smTRANSCODE_GETPLAYERINFO	0x48470021
#define smTRANSCODE_FAILCONNECT		0x48470023

#define smTRANSCODE_PLAYITEM		0x48470050
#define smTRANSCODE_DELITEM			0x48470051
#define smTRANSCODE_PUTITEM			0x8C000C8B
#define smTRANSCODE_THROWITEM		0x8A000B4A
#define smTRANSCODE_SHOP_ITEMLIST	0x6000014A
#define smTRANSCODE_SAVETHROWITEM	0x48470055
#define smTRANSCODE_SAVETHROWMONEY	0x48470056
#define smTRANSCODE_SAVETHROWITEM2	0x48470057
#define smTRANSCODE_SAVETHROWITEMS	0x48470058
#define smTRANSCODE_PLAYERKILLING	0x48470059
#define smTRANSCODE_GETITEM			0x4847005A
#define smTRANSCODE_USEITEM_CODE	0x4847005B
#define smTRANSCODE_COMMAND_USER	0x4847005C
#define smTRANSCODE_WING_NPC		0x4847005D
#define smTRANSCODE_PAYMENT_MONEY	0x4847005E
#define smTRANSCODE_MEDIA_NPC		0x4847005F

#define smTRANSCODE_ADD_STARTPOSI	0x48470060
#define smTRANSCODE_DEL_STARTPOSI	0x48470061
#define smTRANSCODE_ADD_NPC			0x48470070
#define smTRANSCODE_DEL_NPC			0x48470071
#define smTRANSCODE_ADMIN_COPYCHAR	0x48470062

#define smTRANSCODE_RESTAURE_LIST	0x48471305
#define smTRANSCODE_GET_RESTAURE	0x48471306
#define smTRANSCODE_RESTAURE_ITEM	0x48471307

#define	smTRANSCODE_PARTY_UPDATE		0x484700A0
#define	smTRANSCODE_PARTY_REQUEST		0x484700A1
#define	smTRANSCODE_PARTY_JOIN			0x484700A2
#define	smTRANSCODE_PARTY_PLAYUPDATE	0x484700A3
#define	smTRANSCODE_PARTY_RELEASE		0x484700A4
#define	smTRANSCODE_PARTY_COMMAND		0x484700A5
#define smTRANSCODE_OPEN_MIXTURE_RESET	0x484700A6
#define smTRANSCODE_OPEN_COIN_SHOP      0x484700A7
#define smTRANSCODE_OPEN_TIME_SHOP      0x484700A8
#define smTRANSCODE_OPEN_QUEST_DIARY    0x484700A9

#define smTRANSCODE_cMIXGUIDE		0x48471308

#define smTRANSCODE_PCBANG_PET			0x484700B0
#define smTRANSCODE_PHENIX_PET			0x484700B1
#define smTRANSCODE_HELP_PET			0x484700B2

#define	smTRANSCODE_SERVER_INFO			0x484700C0

#define	smTRANSCODE_PARTY_POTION		0x484700D0

#define smTRANSCODE_SV_INFO				0x48470F11

#define	smTRANSCODE_HEALING				0x484700D2
#define	smTRANSCODE_HOLYMIND			0x484700D3
#define smTRANSCODE_WISP                0x484700D9
#define	smTRANSCODE_GRAND_HEALING		0x484700D4

#define	smTRANSCODE_VAMPRIC_CUSPID		0x484700D6
#define	smTRANSCODE_VAMPRIC_CUSPID_EX	0x484700D7
#define	smTRANSCODE_MANA_RECHARGING		0x484700D8

#define	smTRANSCODE_RECORD_TRADE		0x48480010

#define smTRANSCODE_NETWORK_QUALITY	0x484700E0
#define smTRANSCODE_PROCESSINFO		0x484700E4
#define	smTRANSCODE_CLOSECLIENT		0x484700E6
#define smTRANSCODE_CHECKIP			0x484700E7

#define	smTRANSCODE_SAVECLIENT		0x484700E8

#define smTRANSCODE_EFFECT_ITEM		0x48478000
#define smTRANSCODE_EFFECT_WEAPON	0x48478002
#define smTRANSCODE_EFFECT_STUN		0x48478004
#define smTRANSCODE_EFFECT_CURSE	0x48478006
#define smTRANSCODE_EFFECT_ICE		0x48478008
#define smTRANSCODE_EFFECT_POISION	0x4847800A
#define smTRANSCODE_EFFECT_VANISH	0x4847800C
#define smTRANSCODE_EFFECT_PERSHOP	0x4847800E
#define smTRANSCODE_EFFECT_LOWPET	0x4847800F
#define smTRANSCODE_EFFECT_CLANMGR	0x48479000
#define smTRANSCODE_EFFECT_FORCEORB	0x48479010
#define smTRANSCODE_EFFECT_CURSE_QUEST	0x48479011
#define smTRANSCODE_EFFECT_BLESS_SCORE	0x48479012
#define smTRANSCODE_EFFECT_KEEPSKILL	0x48479020
#define smTRANSCODE_EFFECT_PVP_SCORE    0x48479021
#define smTRANSCODE_EFFECT_WISP         0x48479023
#define smTRANSCODE_EFFECT_CURSELAZY    0x48479024
#define smTRANSCODE_EFFECT_WARCRY       0x48479025
#define smTRANSCODE_EFFECT_TENUS        0x48479026
#define smTRANSCODE_EFFECT_TOP_LVL      0x48479027
#define smTRANSCODE_EFFECT_TOP_PVP      0x48479028
#define smTRANSCODE_EFFECT_TYPE         0x48479029
#define smTRANSCODE_EFFECT_PVP          0x48479030

#define smTRANSCODE_CONT_OBJSERIAL	0x48478010

#define smTRANSCODE_MESSAGEBOX		0x48478100

#define	smTRANSCODE_FUNCERROR		0x48478200

#define smTRANSCODE_FUNCTION_MEM2	0x48478300

#define	smTRANSCODE_SET_BLACKLIST2	0x48478400

#define smTRANSCODE_SET_BLACKLIST3	0x48478500

#define	smTRANSCODE_BAD_PLAYER		0x48478600

#define	smTRANSCODE_FIX_ATTACK		0x48478700

#define	smTRANSCODE_DEAD_PLAYER		0x48478800

#define smTRANSCODE_CLIENT_ERROR	0x48478900

#define	smTRANSCODE_INVEN_ERR_ITEM	0x48478910

#define	smTRANSCODE_INVEN_ERR_MONEY	0x48478920

#define	smTRANSCODE_INVEN_POSITION	0x48478930
#define	smTRANSCODE_INVEN_POSITION2	0x48478931

#define smTRANSCODE_ENCODE_PACKET	0x80010000
#define smTRANSCODE_ENCODE_PACKET2	0x90010000

#define smTRANSCODE_OPEN_CLANMENU	0x48478A00

#define smTRANSCODE_OPEN_STARPOINT	0x48478A10
#define smTRANSCODE_STARPOINT		0x48478A12

#define smTRANSCODE_OPEN_GIVEMONEY	0x48478A14
#define smTRANSCODE_GIVEMONEY		0x48478A16

#define smTRANSCODE_CLANMONEY		0x48478A18

#define smTRANSCODE_ITEM_EXPRESS	0x48478A80

#define smTRANSCODE_OPEN_MYSHOP		0x48478A90

#define smTRANSCODE_CALL_MYSHOP		0x48478AA0

#define	smTRANSCODE_MYSHOP_ITEM		0x48478AB0

#define	smTRANSCODE_MYSHOP_MESSAGE	0x48478AC0

#define	smTRANSCODE_MYSHOP_TRADE	0x48478AD0

#define smTRANSCODE_EFFECT_PCBANGPET	0x48478AE0

#define smTRANSCODE_ADMINMODE2			0x5047108C

#define smTRANSCODE_CHECK_NETSTATE20	0x5047008E

#define smTRANSCODE_CHECK_EXPMONEY		0x50320010

#define smTRANSCODE_CHECK_EXPDATA		0x50320020

#define smTRANSCODE_FORCEORB_DATA		0x50320030

#define smTRANSCODE_PRIMEITEM_DATA		0x50320031

#define smTRANSCODE_PRIMEITEM_DATA2	0x50320032

#define smTRANSCODE_PRIMEITEM_DATA3	0x50320033

#define smTRANSCODE_PRIMEITEM_DATA4	0x50320036

#define smTRANSCODE_BOOSTER_DATA		0x50320034

#define smTRANSCODE_AGING_DATA			0x6000400A

#define smTRANSCODE_SKILLDELAY_DATA			0x40A0500C

#define smTRANSCODE_SEND_DATASERVER		0x50320100

#define smTRANSCODE_SEND_GAMESERVER		0x50320110

#define smTRANSCODE_SEND_AREASERVER		0x50320120

#define smTRANSCODE_SEND_AGAME_SERVER	0x50320130

#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA2	0x50320140

#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA3	0x50320150

#define smTRANSCODE_SEND_AGAME_PRIMEITEM_DATA4	0x50320160

#define smTRANSCODE_CRAFTITEM			0x6000800B

#define smTRANSCODE_AGINGITEM			0x600900A0

#define	smTRANSCODE_AGING_UPGRADE		0x600400C0

#define	smTRANSCODE_MAKE_LINKCORE		0x50320205

#define	smTRANSCODE_USE_LINKCORE		0x50320206

#define smTRANSCODE_WINGITEM			0x50320208

#define smTRANSCODE_SHOPTITEM			0x600810C0

#define smTRANSCODE_SHOP_SELLITEM		0x609A10C0

#define	smTRANSCODE_ITEM_FORCEORB		0x50320214

#define	smTRANSCODE_QUEST_COMMAND		0x50320220

#define	smTRANSCODE_EXITINFO_URL		0x50320230

#define smTRANSCODE_CHECKITEM			0x50320300

#define smTRANSCODE_ERRORITEM			0x50320310

#define smTRANSCODE_CLEARPOTION			0x50320320

#ifdef _CHECK_MESH

#define smTRANSCODE_CHECK_ITEMMESH		0x50320330
#endif

#define smTRANSCODE_CLIENT_FUNCPOS		0x50320400

#define smTRANSCODE_GETCLIENT_FUNCPOS	0x50320410

#define smTRANSCODE_FUNCTION_MEM		0x50320420

#define smTRANSCODE_FUNCTON_RESULT		0x50320430

#define smTRANSCODE_PROCESS_TIMEMAX		0x50320500

#define smTRANSCODE_NSPRITE				0x50320600

#define	smTRANSCODE_REC_DAMAGEDATA		0x50320800

#define	smTRANSCODE_SOD_RESULT			0x50320900
#define	smTRANSCODE_SOD_RESULT2			0x50320901

#define	smTRANSCODE_PARTY_SKILL			0x50320A00

#define	smTRANSCODE_CANCEL_SKILL		0x50320A10

#define	smTRANSCODE_PROCESS_SKILL		0x50320A20
#define smTRANSCODE_PROCESS_SKILL2		0x50320A30
#define smTRANSCODE_PROCESS_CLAN_SKILL	0x50320A35

#define	smTRANSCODE_UPDATEL_SKILL		0x50320A40

#define	smTRANSCODE_SUCCESS_EVATION		0x50320A50
#define smTRANSCODE_SUCCESS_DEFENSE     0x50320A51

#define	smTRANSCODE_RESISTANCE			0x50320A60

#define	smTRANSCODE_PUBLIC_POLLING		0x50320A70

#define	smTRANSCODE_NOTICE_BOX			0x50320A80

#define	smTRANSCODE_HACKTRAP			0x50320A90

#define	smTRANSCODE_VIRTURAL_POTION		0x50320B00

#define	smTRANSCODE_CLAN_SERVICE		0x50320C00

#define	smTRANSCODE_CLAN_UPDATE			0x50320C10

#define	smTRANSCODE_QUEST_MESSAGE		0x50320D00

#define	smTRANSCODE_DEAD_USER			0x50320E00

#define	smTRANSCODE_YAHOO_MOTION		0x50320E10

#define	smTRANSCODE_CHANGE_EVENT		0x50320F00

#define	smTRANSCODE_CLIENTINFO			0x50321000

#define	smTRANSCODE_WARNING_BLINK_ATT	0x50321010

#define smTRANSCODE_ATTACK_DAMAGE		0x709F00C0
#define smTRANSCODE_RANGE_DAMAGE		0x70010A01
#define smTRANSCODE_ATTACK_RESULT		0x50322020
#define smTRANSCODE_DISP_DAMAGE			0x50322030
#define smTRANSCODE_ATTACKDATA2			0x50322040

#define smTRANSCODE_LIMIT_DAMAGE		0x50322050

#define smTRANSCODE_WARNING_CLIENT		0x50322060
#define smTRANSCODE_WARNING_SKILL		0x50322080

#define smTRANSCODE_COMIC_SKIN			0x50322070

#define	smTRANSCODE_REC_ADMIN_COMMAND	0x50322090

#define smTRANSCODE_CHECK_ADMINMODE		0x503220A0

#define smTRANSCODE_SOD_INFOMATION		0x503220B0

#define smTRANSCODE_BLESSCASTLE_INFO	0x503220C0
#define smTRANSCODE_BLESSCASTLE_TAX		0x503220D0

#define smTRANSCODE_ATTACK_SLASH_LIST	0x503220E0

#define smTRANSCODE_UPDATE_SERVER_PARAM	0x503220F0
#define smUPDATE_PARAM_LOWUSER_PRESENT	0x100

#define smTRANSCODE_USER_ID				0x50322100

#define smTRANSCODE_DAMAGE_ENCODE_MEM	0x50322F00
#define smTRANSCODE_DAMAGE_ENCODE_MEM2	0x50322EC0

#define	smTRANSCODE_PACKET_DYNFUNC		0x50323000

#define	smTRANSCODE_AREA_SERVER_MAP		0x50324000

#define smTRANSCODE_OPEN_SMELTING		0x200A0004
#define smTRANSCODE_SMELTINGITEM		0x2B010005

#define smTRANSCODE_OPEN_MANUFACTURE	0x2F060009
#define smTRANSCODE_MANUFACTURE			0x20C1000A

#define smTRANSCODE_MANUFACTURE_WEIGHT_PRICE 0x50326002

#define smTRANSCODE_GIFTBOX_MONEY		0x50326003

#define smTRANSCODE_PREMIUMITEM_INIT	0x50326004

#define smTRANSCODE_MIXTURE_RESET_ITEM	0x30A1000C

#define	rsHARDCORE_EVENT_FLAG		0x100

#define smCODE_SOD_EFFECT		100

#define smTRANSCODE_EVENT_GAME		0x50326007
#define smCODE_EVENT_STATE_INIT		100

#define smTRANSCODE_ITEMDOC			0x50326008

#define TRANS_BUFF_SIZE		4096

#define	smCHAR_STATE_NPC		0
#define	smCHAR_STATE_ENEMY		1
#define	smCHAR_STATE_USER		0x80

#define	smCHAR_MONSTER_NATURAL	0x80
#define	smCHAR_MONSTER_GOOD		0x81
#define	smCHAR_MONSTER_EVIL		0x82

#define	smCHAR_MONSTER_NORMAL	0x00
#define	smCHAR_MONSTER_UNDEAD	0x90
#define	smCHAR_MONSTER_MUTANT	0x91
#define	smCHAR_MONSTER_DEMON	0x92
#define	smCHAR_MONSTER_MECHANIC	0x93

#define	smCHAR_MONSTER_USER		0xA0

#define	smCOMMNAD_USER_WARP		0x100
#define	smCOMMNAD_USER_AGINGUP	0x110
#define	smCOMMNAD_USER_HOLY_INCANTATION	0x120
#define	smCOMMNAD_USER_RESURRECTION	0x130
#define	smCOMMNAD_USER_FORCEORB	0x140
#define	smCOMMNAD_USER_VALENTO	0x150
#define	smCOMMNAD_USER_FIREFLOWER	0x160

#define	smCOMMAND_PLAY_BABEL		0x200
#define	smCOMMAND_PLAY_BELSS_CASTLE	0x210
#define	smCOMMAND_PLAY_PK_FIELD		0x220
#define	smCOMMAND_PLAY_KELVEZU		0x230
#define smCOMMAND_PLAY_PVP_SCORE    0x240
#define smCOMMAND_PLAY_BA           0x250
#define smCOMMAND_PLAY_HG           0x260

class	smCHAR;

class	rsRECORD_DBASE;

#define	FALLITEM_MAX			200
#define	FALLITEM2_MAX			3

struct PACKET_LEVEL_BATTLE {
	int size;
	int code;
	int Level[20];
};

struct PACKET_BATTLE_EXP {
	int size;
	int code;
	int Exp;
};

struct PACKET_CROWN
{
	int size;
	int code;
	DWORD Silver;
	DWORD Bronze;
};

struct _FALLITEM {
	DWORD	dwItemCode;
	int		Percentage;
	short	sPrice[2];
};

#define	NPC_MESSAGE_MAX		20

struct PacketBossTimeUpdate
{
	int                 size;
	int                 code;
	;	DWORD				dwHour;
	DWORD               dwMinute;
	int					iMapID;
};

struct smCHAR_MONSTER_INFO {
	char	szName[32];

	short	SkillDamage[2];
	int		SkillRange;
	int		SkillRating;
	int		SkillDistance;
	RECT	SkillRangeRect;
	int		SkillCurse;

	int		AttackPattern;
	int		ActiveHour;
	int		IQ;
	int		Nature;
	int		Undead;
	int		GenerateGroup[2];
	int		GetExp;
	int		SpAttackPercetage;
	int		MoveRange;

	int		DamageStunPers;

	int		PotionCount;
	int		PotionPercent;

	int		AllSeeItem;
	int		FallItemCount;
	int		FallItemPerMax;
	int		FallItemMax;
	int		FallItemPlusCount;

	int		ClassCode;

	int		UseEventModel;

	int		Real_Sight;

	_FALLITEM	FallItems[FALLITEM_MAX];
	_FALLITEM	FallItems_Plus[FALLITEM2_MAX];

	int		SellAttackItemCount;
	void* SellAttackItem[32];
	int		SellDefenceItemCount;
	void* SellDefenceItem[32];
	int		SellEtcItemCount;
	void* SellEtcItem[32];

	int		SkillMaster;
	int		SkillChangeJob;
	int		WareHouseMaster;
	int		ItemMix;
	int		ItemAging;
	int		CollectMoney;
	int		EventGift;
	int		Smelting;
	int		Manufacture;
	int		MixtureReset;
	int     Remodel;
	int     CoinShop;
	int     TimeShop;
	int     AwardItem;
	int     Roulette;
	int     UseRollDice;

#ifdef _LANGUAGE_VEITNAM
	int		WowEvent;
#endif

	int     Boss;
	int		EventCode;
	int		EventInfo;
	DWORD	dwEvnetItem;
	int		EventNPC;
	int		ClanNPC;
	int		GiftExpress;
	int		WingQuestNpc;
	int		StarPointNpc;
	int		GiveMoneyNpc;
	int		TelePortNpc;
	int		BlessCastleNPC;
	int		PollingNpc;

	char* szMediaPlayNPC_Title;
	char* szMediaPlayNPC_Path;

	int		QuestCode;
	int		QuestParam;

	short	OpenCount[2];

	DWORD	dwAutoCharCode;

	char* lpNpcMessage[NPC_MESSAGE_MAX];
	int		NpcMsgCount;
};

struct smCHAR_INFO {
	char	szName[32];
	char	szModelName[64];
	char	szModelName2[60];
	DWORD	ModelNameCode2;

	DWORD	dwObjectSerial;

	int		ClassClan;
	int		State;
	int		SizeLevel;
	DWORD	dwCharSoundCode;

	DWORD JOB_CODE;
	int   Level;
	int   Strength;
	int   Spirit;
	int   Talent;
	int   Dexterity;
	int   Health;

	int	  Accuracy;
	int   Attack_Rating;
	int   Attack_Damage[2];
	int	  Attack_Speed;
	int	  Shooting_Range;
	int	  Critical_Hit;

	int   Defence;
	int   Chance_Block;
	int   Absorption;

	int   Move_Speed;
	int   Sight;
	short Weight[2];

	short	Resistance[8];
	short	Attack_Resistance[8];

	short   Life[2];
	short   Mana[2];
	short   Stamina[2];

	float	Life_Regen;
	float	Mana_Regen;
	float	Stamina_Regen;

	int		Exp;
	int		Next_Exp;

	int		Money;

	smCHAR_MONSTER_INFO* lpMonInfo;

	DWORD	Brood;

	int		StatePoint;
	BYTE	bUpdateInfo[4];
	short	ArrowPosi[2];
	int		Potion_Space;

	int     LifeFunction;
	int     ManaFunction;
	int     StaminaFunction;
	short   DamageFunction[2];

	DWORD	RefomCode;

	DWORD	ChangeJob;
	DWORD	JobBitMask;

	WORD	wPlayerKilling[2];
	WORD	wPlayClass[2];

	int		Exp_High;
	DWORD	dwEventTime_T;
	short	sEventParam[2];

	short	sPresentItem[2];

	short GravityScroolCheck[2];

	DWORD	dwTemp[11];

	DWORD	dwLoginServerIP;
	DWORD	dwLoginServerSafeKey;

	WORD	wVersion[2];
};

#define	smCHAR_INFO_QUICK_SIZE		192
#define	smCHAR_INFO_QUICK_SIZE2		352

#define	THROW_ITEM_INFO_MAX		64
#define	THROW_ITEM_INFO_MASK	63
#define	INVEN_ITEM_INFO_MAX		300

struct	sTHROW_ITEM_INFO {
	DWORD	dwCode;
	DWORD	dwKey;
	DWORD	dwSum;
};

struct rsPLAYPOS {
	DWORD	Area;
	int		x, y, z;
};

struct TRANS_PLAYPOS {
	int size, code;
	rsPLAYPOS	rsPlayPos;
	short Hp[2];
};

struct _PING
{
	int size, code;
	DWORD Time;
};

struct TRANS_ATTACKDATA {
	int size, code;

	DWORD	dwDestObjectSerial;
	DWORD	dwTarObjectSerial;

	int x, y, z;
	int AttackState;
	int AttackSize;
	int Power;
	DWORD	dwChkSum;

	short	sRating[2];
	DWORD	dwDamageChkSum;
};

struct TRANS_ATTACKDATA2 {
	int size, code;

	DWORD	dwChkSum;

	DWORD	dwDestObjectSerial;
	DWORD	dwTarObjectSerial;

	int		x, y, z;
	int		AttackState;
	int		AttackSize;
	short	Power[2];
	short	Power2[2];
	short	Critical[2];
	int		SkillCode;
	DWORD	dwTime;
	int		AttackCount;
	short	MotionCount[2];
	DWORD	dwWeaponCode;
	short	Area[2];
	int		Temp[4];
};

#define SKIL_ATTACK_CHAR_MAX		42

struct TRANS_SKIL_ATTACKDATA {
	int size, code;

	DWORD	dwDestObjectSerial;

	int x, y, z;
	int AttackState;
	int AttackSize;
	int Power;

	DWORD	dwChkSum;

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];
};

struct TRANS_SKIL_ATTACKDATA2 {
	int size, code;

	DWORD	dwDestObjectSerial;

	DWORD	dwChkSum;

	int		x, y, z;
	int		AttackState;
	int		AttackSize;
	short	Power[2];
	short	Power2[2];
	short	Critical[2];
	int		SkillCode;
	DWORD	dwTime;
	int		AttackCount;
	short	MotionCount[2];
	DWORD	dwWeaponCode;
	short	Area[2];
	int		Temp[4];

	DWORD	dwMainTargetObject;

	int	TargetCount;
	DWORD	dwTarObjectSerial[SKIL_ATTACK_CHAR_MAX];
};

struct TRANS_AREAINFO_HEADER {
	int		size;
	int		code;
	DWORD	dwIP;
	int		Stats;
	int		TransListCnt;
};
struct TRANS_IPLIST {
	DWORD	dwIP;
	rsPLAYPOS	Pos;
};

#define	POST_ITEM_MAX				500

struct _POST_BOX_ITEM {
	int		Flag;
	char	szCharName[32];
	char	szItemCode[32];
	char	szSpeJob[32];
	char	szDoc[128];
	char	szFormCode[64];
	char	szPassCode[16];

	DWORD	dwItemCode;
	DWORD	dwJobCode;
	DWORD	dwFormCode;
	DWORD	dwPassCode;
	DWORD	dwParam[4];
};

struct	rsPOST_BOX_ITEM {
	DWORD	dwHead;
	int		ItemCounter;

	_POST_BOX_ITEM	PostItem[POST_ITEM_MAX];
};

struct	TRANS_POST_ITEM {
	int		size, code;

	char	szItemName[32];
	char	szDoc[128];
	DWORD	dwItemCode;
	DWORD	dwItemJobCode;
	DWORD	dwParam[4];

	DWORD	dwItemFlag;
	int		Weight;
};

#define	srPLAYBUFF_MAX		4
#define	srPLAYBUFF_MASK		3

#define	PARTY_PLAYER_MAX		6

#define	srRECORD_DEFAULT_SIZE	16384

#define	srRECORD_MEMORY_SIZE	24576

#define SKILL_POINT_COLUM_MAX	20

struct	TRANS_PARTY_PLAYINFO;

struct	sMYSHOP_SELL_INFO {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		Price;
	int     KindCurrency;
};

#define	MYSHOP_LIST_MAX		32
#define	MYSHOP_LIST_MASK	31

struct	sCASTLE_MASTER {
	int		Flag;
	DWORD	dwCheckTime;
	int		SelectSkill;
};

#define	rsDATA_ERROR_WAREHOUSE			1

struct smTRANS_EXP {
	int size;
	int code;
	INT64 exp;
};

struct PacketMap
{
	int size;
	int code;
	char				szBossName[32];
	DWORD				dwTime;
	int					iMapID;
};

struct smTRANS_EXP64
{
	int	size;
	int code;

	INT64 LParam;
	INT64 WParam;
	INT64 SParam;
	INT64 EParam;
};

struct SV_INFO
{
	int size;
	int code;

	int AgingOkPercent[20];
	int AgingStoneAgingOkPercent[20];

	int SuperAgingStoneAgingFailPercent[20];
	int SuperAgingStone1_5AgingFailPercent[20];
};

struct smTRANS_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;
};

struct smTRANS_TOP
{
	int size;
	int code;
	int flag;
};

struct smTRANS_BA_SCORE
{
	int size;
	int code;
	char szName1[32];
	char szName2[32];
	char szName3[32];
	int  Score[3];
};

struct PacketUnitStatusContainer
{
	WORD	              iLength;
	DWORD	              iHeader;
	int					  iAmount;
	int					  iCounter;
	BYTE				  baBuffer[0x2038];
};

struct PacketSkillStatusContainer
{
	WORD	              iLength;
	DWORD	              iHeader;
	int				      iAmount;
	BYTE			      baBuffer[0x1FF4];
};

class rsPLAYINFO {
public:

	char			szServerID[32];

	char			szID[32];
	char			szName[32];
	DWORD			dwCode_ID;
	DWORD			dwCode_Name;

	int				AdminOperMode;

	DWORD			dwDataError;

	int				TransInfoFlag;
	int				ChatBuffCnt;

	int				SystemLine;

	int				CharLoadingCount;

	rsPLAYPOS		Position;
	rsPLAYINFO** lpAreaPlayInfo;

	int				SendListCnt;

	DWORD			dwDecPacketCode;
	BYTE			bPacketXor[2];
	DWORD			dwDecPacketTime;
	DWORD			dwDecPacketTime2;

	smCHAR_INFO		smCharInfo;

	int				CharLevelMax;
	DWORD			dwNoticeCount;

	char			srPlayBuff[srPLAYBUFF_MAX + 1][TRANS_BUFF_SIZE];
	int				srPlayBuffSize[srPLAYBUFF_MAX + 1];

	int				PlayBuffSleep;

	sTHROW_ITEM_INFO	ThrowItemInfo[THROW_ITEM_INFO_MAX];

	sTHROW_ITEM_INFO	InvenItemInfo[INVEN_ITEM_INFO_MAX + 16];
	sTHROW_ITEM_INFO	WareHouseItemInfo[120];
	int				OpenWarehouseInfoFlag;
	int             WarehousePage;

	DWORD			dwTradePotionInfo[16];
	int				TradePotionInfoCount;

	sMYSHOP_SELL_INFO	sMyShopList[MYSHOP_LIST_MAX];
	int				MyShopListCount;
	DWORD			dwMyShopTradeTime;

	int				ThrowItemCount;

	int				UnsaveMoney;

	int				ServerMoney;
	int				WareHouseMoney;

	DWORD			dwRecvTimePlayBuff;
	DWORD			srSendPlayBuffCnt;
	DWORD			srRecvPlayBuffCnt;

	DWORD			dwObjectSerial;

	int				ChatMsgMode;
	char			szChatMessage[256];

	char			szTradeMessage[128];
	DWORD			dwTradeMsgCode;

	smWINSOCK* lpsmSock;

	DWORD			dwLastRecvTime;
	DWORD			dwLastMotionRecvTime;

	int				UpdateInfo_WaitCounter;
	int				UpdateInfo_WarnigCounter;

	rsRECORD_DBASE* lpRecordBase;
	rsPOST_BOX_ITEM* lpPostBoxItem;
	int				PostPassFailCount;

	int				AdminMode;
	int				HideMode;
	int				AdminIP;

	DWORD			dwConnectTime;

	int				LastTransPlayUserCount;
	int				LastTransAutoPlayCount;

	DWORD			dwConnectCount;

	int				frame;
	DWORD			SendPlayGroupCount;

	DWORD			MonTranCount;
	DWORD			CharTransCount;

	int				HitMonsterCount;
	smCHAR* lpChrTarget;
	DWORD			dwTarObjSerial;

	int				UserPacketLoop;
	int				BefUserPacketLoop;

	int				AttackCount;
	DWORD			dwAttackTime;
	DWORD			dwLastAttackTime;
	int				DamagePacketCount;
	DWORD			dwDamagePacketTime;

	int				MonsterKillCounter;
	DWORD			dwLastTradeChksum;
	DWORD			dwLastTradeTime;

	short			sLowLevel_PresentItem[2];

	DWORD			dwStartUser_PresentItem_Time;
	DWORD			dwStartUser_PresentItem_Count;

	int  KillCount;
	DWORD KillTime;

	int				Send_AttackCount;
	int				Send_AttackDamage;
	int				Recv_AttackCount;
	int				Recv_AttackDamage;

	DWORD			dwMacroTime;
	int				Macro_PosX;
	int				Macro_PosZ;
	int				Macro_AngY;
	DWORD			dwMacroAngTime;
	DWORD			dwMacroChkTime;

	DWORD			dwSendFrames[CONNECTMAX];

	int				CrackWarning;
	DWORD			dwTime_Disconnect;
	int				BadPlayer;
	DWORD			dwPacketAttackCount;
	DWORD			dwPacketAttackTime;
	int				WarningCount;

	char* lpRecordDataBuff;
	DWORD			dwRecordDataTime;

	int				EventMode;
	int				EventScore;
	int				EventCount;
	DWORD			dwEventTime;
	short			sEventParam[2];

	int				AreaOutCount;

	int				BlockTime;

	int				WhisperMode;

	int				Event_StarTicketLevel;

	INT64			spExp_Start;
	int				spMoney_Start;
	int				spLevel_Start;

	int				spExp_InOut_Total;
	int				spMoney_In_Total;
	int				spMoney_InOut_Total;

	INT64			spEXP_Out;
	int				spMoney_In;
	int				spMoney_Out;

	DWORD			dwLastExpMoneyCheckTime;
	DWORD			dwLastExpMoneyTransServer;

	DWORD			dwHopeDisconnectTime;

	int				Client_Version;

	DWORD			dwLastSaveTime;

	DWORD			dwGameServerExp[8];

	DWORD			dwNSpriteTime;

	DWORD			dwClientFuncChk_1;
	DWORD			dwClientFuncChk_2;
	int				FuncChkFailCount1;
	int				FuncChkFailCount2;
	int				FuncChkSucessCount1;
	int				FuncChkSucessCount2;
	DWORD			dwFuncChkErrorFlag;
	int				ClientFunChk1_Count;
	int				ClientFunChk2_Count;

	DWORD			dwClientFunChk_NextTime;

	int				RecordWarningCount;
	int				RecordWarningExp;

	DWORD			dwClentOS;
	WORD			wClentOSVersion[2];
	DWORD			dwClentModulChkSum;
	int				ClentModuleCount;

	DWORD			dwDamagePacketKey[2];
	DWORD			dwDamagePacketKey2[2];

	DWORD			PartyUpdateFlag;
	DWORD			dwPartyInfo;
	rsPLAYINFO* lpPartyMaster;
	DWORD			PartyMasterObjectCode;
	rsPLAYINFO* lpPartyPlayers[PARTY_PLAYER_MAX];
	DWORD			dwPartyObjectCode[PARTY_PLAYER_MAX];
	DWORD			PartyLevelAverage;
	int				PartyUserCount;

	DWORD			dwClanCode;
	int				ClanTicketCode;
	int				SucessCheck_ClanCode;

	char	szGuid[128];
	char	szPwd[32];
	char	szGPCode[16];
	time_t	DisuseDay;
	int		UsePeriod;
	int		GpCode;
	int		GpType;
	DWORD	dwPeriodTime;
	int		Bl_RNo;
	int		Bl_Meter;
	DWORD	dwPeriodTime2;

	int		SndItemSecCodeCount;
	int		RcvItemSecCodeBuff[8][16];

	short	sLimitDamage[2];
	short	sLimitCritical[2];

	int		ServerPotion[3][4];

	DWORD	dwSkill_AutoMation_Time;
	int		dwSkill_AutoMation_Param;

	DWORD	dwSkill_Maximize_Time;
	int		dwSkill_Maximize_Param;

	DWORD	dwSkill_PhysicalAbsorb_Time;
	int		dwSkill_PhysicalAbsorb_Param;

	DWORD	dwSkill_ExtreamShield_Time;
	int		dwSkill_ExtreamShield_Param;

	DWORD	dwSkill_HolyBody_Time;
	int		dwSkill_HolyBody_Param;

	DWORD	dwSkill_HolyValor_Time;
	int		dwSkill_HolyValor_Param;

	DWORD   dwAdventMigal_Time;
	int		dwAdventMigal_Param;

	DWORD   dwAdventMidranda_Time;
	int		dwAdventMidranda_Param;

	DWORD	dwSkill_HolyReflection_Time;
	int		dwSkill_HolyReflection_Param;

	DWORD	dwSkill_EnchantWeapon_Time;
	int		dwSkill_EnchantWeapon_Param;

	DWORD	dwSkill_MetalArmor_Time;
	int		dwSkill_MetalArmor_Param;

	DWORD	dwSkill_SparkShield_Time;
	int		dwSkill_SparkShield_Param;

	DWORD	dwSKill_Falcon_Time;
	short	dwSKill_Falcon_Damage[2];

	DWORD	dwSkill_DivineInhalation_Time;
	DWORD	dwSkill_DivineInhalation_Param;

	DWORD	dwSkill_TriumphOfValhalla_Time;
	DWORD	dwSkill_TriumphOfValhalla_Param;

	DWORD	dwSkill_VirtualLife_Time;
	DWORD	dwSkill_VirtualLife_Param;

	DWORD	dwSkill_EnergyShield_Time;
	DWORD	dwSkill_EnergyShield_Param;

	DWORD	dwSkill_SpiritElemental_Time;
	DWORD	dwSkill_SpiritElemental_Param;

	DWORD	dwSkill_DancingSword_Time;
	DWORD	dwSkill_DancingSword_Param;
	DWORD	dwSkill_DancingSword_DelayTime;

	DWORD	dwSkill_Vanish_Time;
	DWORD	dwSkill_Vanish_Param;

	DWORD	dwSkill_Compulsion_Time;
	DWORD	dwSkill_Compulsion_Param;

	DWORD	dwSkill_MagneticSphere_Time;
	DWORD	dwSkill_MagneticSphere_Param;

	DWORD	dwSkill_Berserker_Time;
	DWORD	dwSkill_Berserker_Param;

	DWORD	dwSkill_B_Berserker_Time;
	DWORD	dwSkill_B_Berserker_Param;

	DWORD	dwSkill_Krishna_Time;
	DWORD	dwSkill_Krishna_Param;

	DWORD	dwSkill_AssassinEye_Time;
	DWORD	dwSkill_AssassinEye_Param;

	DWORD	dwSkill_Tenus_Time;
	DWORD	dwSkill_Tenus_Param;

	DWORD  dwSkill_P_Enhence_Time;
	DWORD  dwSkill_P_Enhence_Param;

	DWORD	dwSkill_Vague_Time;
	DWORD	dwSkill_Vague_Param;

	DWORD	dwSkill_ForceOfNature_Time;
	WORD	wSkill_ForceOfNature_Param[2];

	DWORD	dwSkill_GodlyShied_Time;
	DWORD	dwSkill_GodlyShied_Param;

	DWORD	dwSkill_GodsBless_Time;
	DWORD	dwSkill_GodsBless_Param;

	DWORD	dwSkill_HallOfValhalla_Time;
	WORD	wSkill_HallOfValhalla_Param[2];

	DWORD	dwSkill_FrostJavelin_Time;
	DWORD	dwSkill_FrostJavelin_Param;

	DWORD	dwSkill_RegenerationField_Time;

	DWORD	dwSkill_SummonMuspell_Time;
	DWORD	dwSkill_SummonMuspell_Param;

	DWORD   dwSkill_ChasingHunt_Time;
	DWORD   dwSkill_ChasingHunt_Param;

	DWORD   dwSkill_RainMaker_Time;
	DWORD   dwSkill_RainMaker_Param;

	DWORD	dwSkill_Blind_Time;
	DWORD  	dwSkill_Blind_Param;

	DWORD	dwSkill_Alas_Time;
	DWORD	dwSkill_Alas_Param;

	DWORD	dwSkill_HolyBenedic_Time;
	DWORD	dwSkill_HolyBenedic_Param;

	DWORD	dwSkill_Amplified_Time;
	DWORD	dwSkill_Amplified_Param;

	DWORD	dwSkill_Anima_Time;
	DWORD	dwSkill_Anima_Param;

	DWORD	dwSkill_PowerEnhence_Time;
	DWORD	dwSkill_PowerEnhence_Param;

	DWORD	dwSkill_I_Bulkup_Time;
	DWORD	dwSkill_I_Bulkup_Param;

	DWORD	dwSkill_SummonRamiel_Time;
	DWORD	dwSkill_SummonRamiel_Param;

	DWORD	dwCurse_Attack_Time;
	DWORD	dwCurse_Attack_Param;

	DWORD	dwCurse_Defence_Time;
	DWORD	dwCurse_Defence_Param;

	BYTE	bSkillPoint[SKILL_POINT_COLUM_MAX];

	DWORD	dwForceOrb_Code;
	DWORD	dwForceOrb_Time;
	DWORD	dwForceOrb_Damage;

	DWORD	dwForceOrb_SaveCode;
	DWORD	dwForceOrb_SaveTime;
	DWORD	dwForceOrb_SaveDamage;
	DWORD	dwForceOrb_NextSetTime;

	DWORD	dwLifeBooster_Code;
	DWORD	dwLifeBooster_Time;
	DWORD	dwLifeBooster_Data;

	DWORD	dwLifeBooster_SaveCode;
	DWORD	dwLifeBooster_SaveTime;
	DWORD	dwLifeBooster_SaveData;
	DWORD	dwLifeBooster_NextSetTime;

	DWORD	dwManaBooster_Code;
	DWORD	dwManaBooster_Time;
	DWORD	dwManaBooster_Data;

	DWORD	dwManaBooster_SaveCode;
	DWORD	dwManaBooster_SaveTime;
	DWORD	dwManaBooster_SaveData;
	DWORD	dwManaBooster_NextSetTime;

	DWORD	dwStaminaBooster_Code;
	DWORD	dwStaminaBooster_Time;
	DWORD	dwStaminaBooster_Data;

	DWORD	dwStaminaBooster_SaveCode;
	DWORD	dwStaminaBooster_SaveTime;
	DWORD	dwStaminaBooster_SaveData;
	DWORD	dwStaminaBooster_NextSetTime;

	DWORD	dwPrimeItem_NextSetTime;
	DWORD	dwTime_PrimeItem_X2;
	DWORD	dwTime_PrimeItem_ExpUp;
	DWORD	dwPrimeItem_PackageCode;

	DWORD	dwTime_PrimeItem_VampCuspid;
	DWORD	dwTime_PrimeItem_ManaRecharg;
	DWORD	dwTime_PrimeItem_MightofAwell;
	DWORD	dwTime_PrimeItem_MightofAwell2;
	DWORD	dwTime_PrimeItem_ManaReduce;
	DWORD	dwTime_PrimeItem_PhenixPet;
	DWORD	dwTime_PrimeItem_HelpPet;
	int     dwParam_PrimeItem_HelpPet;
	DWORD	dwTime_PrimeItem_VampCuspid_EX;
	DWORD	dwTime_PrimeItem_StaminaReduce;
	DWORD   dwTime_PrimeItem_BigHead;
	DWORD   dwParam_PrimeItem_BigHead;

	DWORD   dwTime_PrimeItem_VIP;
	DWORD   dwParam_PrimeItem_VIP;

	DWORD	dwPCBang_Pet_AttackTime;
	DWORD	dwPCBang_Pet_NextSetTime;

	DWORD	dwHelp_Pet_AttackTime;
	DWORD	dwHelp_Pet_NextSetTime;

	DWORD	dwSkillDelay_Code;
	DWORD	dwSkillDelay_Time;
	DWORD	dwSkillDelay_Data;

	DWORD	dwSkillDelay_SaveCode;
	DWORD	dwSkillDelay_SaveTime;
	DWORD	dwSkillDelay_SaveData;
	DWORD	dwSkillDelay_NextSetTime;

	DWORD   ChatGlobal_Time;

	smCHAR* lpLinkChar;
	DWORD	dwLinkCharCode;

	short	sBlessCastle_Damage[2];

	int     BattlePoint;
	int     DeathPoint;
	char    LastKill[32];
	int     TopLvL;
	int     Define;
	DWORD   PvP_Time;
	int     PvP_Param;
	int     OnBattle;
	int     OnHellGates;
	int     BattleScore;
	int     BattleLevel;
	int     BattleExp;
	int     Streak;

	int     WeaponClass;
	int     ArmorClass;
	int     ShieldClass;
	int     BraceletsClass;
	int     GauntletsClass;
	int     BootsClass;
	int     RingClass;
	int     AmyClass;
	int     ShelClass;
	DWORD   TimeClass;
	DWORD   WarehousePage_Time;

	DWORD   QuestStart_State;
	DWORD   QuestStart_Param1;
	DWORD   QuestStart_Param2;

	DWORD   QuestLv150A_State;
	DWORD   QuestLv150A_Param;
	DWORD   QuestLv150A_Time;

	DWORD   QuestLv155A_State;
	DWORD   QuestLv155A_Param;
	DWORD   QuestLv155A_Time;

	DWORD   QuestLv150B_State;
	DWORD   QuestLv150B_Param;
	DWORD   QuestLv150B_Time;

	DWORD   RandomMonster_Param;
	DWORD   RandomMonster_Time;

	DWORD   Checksum;

	DWORD	dwCheck_MasterClanTime;

	sCASTLE_MASTER	CastleMaster;
	DWORD	dwBlessSkill_Code;
	DWORD	dwBlessSkill_Time;
	DWORD	dwBlessSkill_Param;

	DWORD	dwSiegeItem_Scroll_Time;
	DWORD	dwSiegeItem_Scroll_Code;
	DWORD	dwSiegeItem_Scroll_Param;

	DWORD	dwSiegeItem_Stone1_Time;
	DWORD	dwSiegeItem_Stone1_Code;
	DWORD	dwSiegeItem_Stone1_Param;

	DWORD	dwSiegeItem_Stone2_Time;
	DWORD	dwSiegeItem_Stone2_Code;
	DWORD	dwSiegeItem_Stone2_Param;

	short	sCheckPlayField_Count[2];

	DWORD	dwHaQuestItemCount;

	char	szUserExpTimeID[32];
	char	szUserExpTimeName[32];
	DWORD	dwExpGameTime;
	DWORD	dwExpGameTimeCheck;
	DWORD   dwCountMin;

	void* SellAttackItem[32];
	void* SellDefenceItem[32];
	void* SellEtcItem[32];

	BOOL                                    b32;
	BOOL                                    b64;
	UINT                                     uPriorityCounter;
	UINT                                     uPriority;
	DWORD                        bAFK;
	int                            iUnitStatusCounter;

	UINT						  uBufferPosition;
	PacketUnitStatusContainer	  sUnitStatusContainer;
	UINT						  uBufferPositionM;
	PacketUnitStatusContainer	  sUnitStatusContainerM;
	UINT						  uBufferPositionS;
	PacketSkillStatusContainer	  sSkillStatusContainer;

	UINT			uNewUnitStatus;
	UINT			uLastUnitStatus;

	UINT			uaUpdateCounter1[1024];
	UINT			uaUpdateCounter2[1024];
	USHORT			uaUpdateCounter3[1024];
	USHORT			uaUpdateCounter4[1024];
	UCHAR			uaUpdateCounter5[4096];

	int	CreateParty(rsPLAYINFO* lpPlayInfo);
	int	JoinPartyPlayer(rsPLAYINFO* lpPlayInfo);
	int	DeletePartyPlayer(rsPLAYINFO* lpPlayInfo);
	int ChangePartyPlayer(rsPLAYINFO* lpOldPlayInfo, rsPLAYINFO* lpNewPlayInfo);
	int	UpdatePartyPlayer();
	int	UpdatePartyPlayInfo();
	int GetPartyMoney(sITEMINFO* lpDefItemInfo, rsPLAYINFO* lpPlayInfo);
	int GetPartyExp(smCHAR* lpChar, rsPLAYINFO* lpPlayInfo);
	int PartyChatting(rsPLAYINFO* lpPlayInfo);

	int	UpdateServerPartyPlayer(TRANS_PARTY_PLAYINFO* lpTransPartyPlayInfo);

	int	LeavePartyMaster(rsPLAYINFO* lpPlayInfo);
	int	ReleaseParty();

	int SendPartyMessage(char* szMessage, DWORD dwCode);

	int SendPartyData(rsPLAYINFO* lpPlayInfo_From, char* szData);

	int	JoinParty(rsPLAYINFO* lpPlayMaster);
	int	SecedeParty();
	int	DisconnectPartyUser();

	int	AddServerMoney(int Money, int WhereParam = 0);
	int	SubServerMoney(int Money, int WhereParam = 0);
	int	SetServerMoney(int Money, int WhereParam = 0);

	int	CallBack_ClanMarkNum(int ClanMarkNum);
};

#define BILLING_GPTYPE_DAY		0
#define BILLING_GPTYPE_TIME		1
#define BILLING_GPTYPE_FREE		2
#define BILLING_GPTYPE_POTAL	3

#define BILLING_PGTYPE_PERSONAL	0
#define BILLING_PGTYPE_PCROOM	0

struct TRANS_CHATBUFF {
	int		size;
	int		code;
	DWORD	dwIP;
};
struct CHATBUFF {
	DWORD	dwIP;
	char szMessage[256];
};

struct TRANS_CHATMESSAGE {
	int		size;
	int		code;
	DWORD	dwIP;
	DWORD	dwObjectSerial;

	char szMessage[256];
};

struct smPLAYDATA_GROUP {
	int		size, code;
	int		PlayDataCnt;
	DWORD	dwSendCode;
};

#define smPLAYBUFF_FRAME_NONE			0xFFFF0000

#define	smPLAYBUFF_ITEM_BODY			0
#define	smPLAYBUFF_ITEM_LEFT			1
#define	smPLAYBUFF_ITEM_RIGHT			2
#define	smPLAYBUFF_ITEM_SKIL			3

struct smPLAYBUFF {
	int		x, y, z;
	DWORD	frame;
	short	angle[4];

	short	wStickItems[4];
	DWORD	dwTargetSerial;
};

struct smPLAYDATA {
	int	size;
	int code;

	DWORD	dwObjectSerial;

	int x, y, z;
	short angle[4];

	DWORD	frame;
	DWORD	dwAutoCharCode;
};

struct smPLAYDATA2 {
	int	size;
	int code;

	DWORD	dwObjectSerial;

	short	BuffCount[2];
	smPLAYBUFF	PlayBuff[2];
	DWORD	dwTarget;
};

struct smPLAYDATA3 {
	int	size;
	int code;

	DWORD	dwObjectSerial;

	short	BuffCount[3];
	smPLAYBUFF	PlayBuff[3];
	DWORD	dwTarget;
};

struct smTRANS_PLAYBUFF {
	int		BuffCount;
	smPLAYBUFF	PlayBuff;
};

#define TRANS_PLAYDATA_EVENT_LEVEL		0
#define TRANS_PLAYDATA_EVENT_POTION		1
#define TRANS_PLAYDATA_EVENT_SKIL		2
#define TRANS_PLAYDATA_EVENT_EXT		3

struct smTRANS_PLAYDATA
{
	int	size;
	int code;

	DWORD	dwObjectSerial;
	DWORD	dwTarget;

	int		PlayBuffCnt;
	int		StartPosi;

	short	Hp[2];
	DWORD	dwAutoCharCode;
	short	wArea[2];
	BYTE	bUpdateInfo[4];
	BYTE	bEventInfo[4];
};

struct smEFFECT_ITEM {
	int size, code;

	DWORD	dwItemCode;

	int		ColorBlink;
	short	sColors[4];
	DWORD	DispEffect;
	DWORD	BlinkScale;
};

struct smTRANS_CHAR_COMMAND
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char	szName[32];
};

struct smTRANS_CHAR_COMMAND2
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;

	char	szId[32];
	char	szName[32];
	char	szMac[20];
	char	szPath[MAX_PATH];
	char	szPCName[MAX_COMPUTERNAME_LENGTH + 1];
};

struct smTRNAS_PLAYERINFO
{
	int	size;
	int code;

	smCHAR_INFO	smCharInfo;

	DWORD	dwObjectSerial;

	int	x, y, z;
	int ax, ay, az;
	int state;
};

struct smTRNAS_PLAYERINFO_QUICK
{
	int	size;
	int code;

	DWORD	dwObjectSerial;

	int	x, y, z;
	int ax, ay, az;
	int state;

	smCHAR_INFO	smCharInfo;
};

struct smTRANS_COMMAND_DWORD
{
	int	size;
	int code;

	DWORD LParam;
	DWORD WParam;
	DWORD SParam;
	DWORD EParam;
};

struct smTRANS_COMMAND_EX
{
	int	size;
	int code;

	int LParam;
	int WParam;
	int SParam;
	int EParam;

	int LxParam;
	int WxParam;
	int SxParam;
	int ExParam;
};

struct PREMIUM_TIME
{
	int	size;
	int code;

	DWORD	ThirdEye;
	DWORD	ExpUp;
	DWORD	VampCuspid;
	DWORD	ManaRecharg;
	DWORD	MightofAwell;
	DWORD	MightofAwell2;
	DWORD	ManaReduce;
	DWORD	PhenixPet;
	DWORD	HelpPet;
	DWORD	VampCuspidEx;
	DWORD	StaminaReduce;
	DWORD   BigHead;
};

struct smTRANS_COMMAND_BUFF {
	smTRANS_COMMAND		smTransCommand;
	char* Buff[256];
};

struct smTRANS_COMMAND_SOD {
	smTRANS_COMMAND		smTransCommand;
	int		MyScore;
	int		MyTeam;
	int		TeamScore[4];
	int		Temp[4];
};

struct smTRANS_COMMAND_POLLING {
	smTRANS_COMMAND		smTransCommand;
	BYTE	bPolling[10];
};

struct smTRANS_RESISTANCE {
	int	size;
	int code;
	int	Param;
	short Resistance[8];
	int	Absorb;
};

struct smTRANS_BLESSCASTLE {
	smTRANS_COMMAND		smTransCommand;
	int				TaxRate;
	short			Tower[12];
	unsigned char	MercenaryNum[4];
	int				ClanSkill;
	int				Price;
	DWORD			dwMasterClan;
	int				Temp[4];
};

struct	rsUSER_LIST_TOP10 {
	int		size, code;

	int		tCode;
	DWORD	dwObjectSerial;
	DWORD	dwNameCode;
	int		x, y, z;

	DWORD	dwCharCode;
	DWORD	dwUpdateTime;
	DWORD	dwTotalDamage;
	char	bCrystalTowerCount[4];
	DWORD	dwTemp[2];

	DWORD	dwUserCode[10];
	int		Damage[10];
	int		Counter[10];
};

#define	TRANS_GROUPITEM_MAX		16
#define	TRANS_GROUPITEM_HEADER_SIZE		(14*4)

struct	TRANS_ITEMINFO_GROUP {
	int	size, code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	sITEMINFO	sItemInfo[TRANS_GROUPITEM_MAX];
};

struct	TRANS_ITEMINFO_GROUP2 {
	int	size, code;

	int Index;
	int Result;
	int Money;
	int	ItemCount;

	DWORD	dwTemp[8];

	char	szBuff[sizeof(sITEMINFO) * TRANS_GROUPITEM_MAX];
};

struct TRANS_ITEMINFO {
	int	size, code;

	sITEMINFO	Item;

	int x, y, z;

	DWORD	dwSeCode[4];
};

struct	TRANS_ITEM_CODE {
	int size, code;

	DWORD	dwFlag;

	DWORD	dwItemCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	DWORD	dwTime;
};

struct TRANS_ITEM {
	int			state;

	int			type;
	int			ItemCode;

	int			x, y, z;
	char		szName[64];
	void* lpStgArea;
	DWORD       iClass;
	int LinkedItem;
};

struct _TRANS_THROW_ITEM {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
};

#define	THROW_ITEMS_MAX				32

#define	TRANS_THROW_ITEMS_DEFSIZE	(sizeof(int)*4)

struct TRANS_THROW_ITEMS {
	int		size, code;
	int		ThrowItemCount;
	int		Temp;

	_TRANS_THROW_ITEM	ThrowItems[THROW_ITEMS_MAX];
};

struct _TRANS_RECORD_TRADE_ITEM {
	DWORD	dwCode;
	DWORD	dwHead;
	DWORD	dwChkSum;
	int		State;
};

#define _MAX_TRADE_ITEM			20

struct TRANS_TRADE_ITEMKEY {
	int size, code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;

	DWORD	dwItemCode[_MAX_TRADE_ITEM];
	DWORD	dwItemKey[_MAX_TRADE_ITEM];
	DWORD	dwItemSum[_MAX_TRADE_ITEM];

	int		Money;
	int     Coin;
};

#define	TRADE_RECV_ITEMS_MAX				32

#define	TRANS_RECORD_TRADE_DEFSIZE		(sizeof(int)*16)

struct TRANS_RECORD_TRADE_ITEMS {
	int		size, code;
	int		Money;
	int		ThrowItemCount;
	char	szTradeUserName[32];
	int		Temp[4];

	_TRANS_RECORD_TRADE_ITEM	Items[TRADE_RECV_ITEMS_MAX];
};

#define TRANS_ITEM_MAX			1024

struct smTRANS_ITEMS
{
	int size, code;

	int state;
	int Count;

	TRANS_ITEM	Items[TRANS_ITEM_MAX];
};

struct smTRANS_ACITON_ITEM
{
	int size, code;

	int state;

	int			x, y, z;
	void* lpStgArea;
};

struct smTRANS_SELL_ITEM {
	int size, code;
	int	ItemKind;
	int	ItemCounter;
	int	Ext[4];
};

#define TRANS_TRADE_BUFF_SIZE		4000
struct TRANS_TRADEITEMS {
	int size, code;
	DWORD	dwSender;
	DWORD	dwRecver;
	DWORD	dwSum;
	DWORD	Temp[4];

	BYTE	TradeBuff[TRANS_TRADE_BUFF_SIZE];
};

#define	SOD_RESULT_MAX	32

struct	_SOD_RESULT {
	char		szName[32];
	rsPLAYINFO* lpPlayInfo;
	int			JobCode;
	int			Class;
	int			Score;
	int			Monster;
	DWORD		dwTemp[4];
};

struct	TRANS_SOD_RESULT {
	int	size, code;

	DWORD	dwGameCode;
	DWORD	dwGameTime;
	DWORD	dwDisplayMode;
	short	TeamRound[2];

	DWORD	dwTemp[15];

	int		ResultCount;

	_SOD_RESULT	Result[SOD_RESULT_MAX];
};

struct	sSERVER_MONEY {
	int	InputMoney;
	int	Counter;
	int	TotalX;
	int	TotalY;
	int	TotalZ;
};

struct sSERVER_EXP {
	int	Counter;
	int	InputExp;
	int	Total1;
	int	Total2;
};

struct TRANS_TOTAL_EXPMONEY {
	int	size, code;

	sSERVER_MONEY	sServerMoney;
	sSERVER_EXP		sServerExp;
};

struct	TRANS_SEND_DATASERVER {
	int size, code;
	char	szBuff[1024];
};

struct	TRANS_BUY_SHOPITEM {
	int	size, code;

	sITEM	sItem;
	int		ItemCount;
};

struct	_TRANS_USINGITEM {
	DWORD	dwCode;
	short	Performance[8];
};

struct	TRANS_USINGITEM {
	int	size, code;
	int	ItemListCount;
	_TRANS_USINGITEM	ItemList[16];
};

#define	FIND_CRACK_LIST_MAX		64

struct	_CRACK_NAME {
	char	szName1[12];
	char	szName2[12];
	char	szClass[12];
};

struct	TRANS_FIND_CRACKER {
	int		size, code;

	int		FindCounter;

	_CRACK_NAME	CrackName[FIND_CRACK_LIST_MAX];

	char	szTemp[128];
};

#define	PARTY_STATE_NONE		0
#define	PARTY_STATE_MASTER		1
#define	PARTY_STATE_MEMBER		2

struct _PARTY_USER {
	char	szName[32];
	char	szModelName[64];
	char	szModelName2[64];

	DWORD	dwObjectSerial;
	DWORD	Level;
	int     JobCode;
	short	Life[2];
	int		x, z;
};

struct TRANS_PARTY_USERS {
	int		size, code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp[8];

	int		PartyUserCount;

	_PARTY_USER		PartyUser[PARTY_PLAYER_MAX];
};

struct _PARTY_PLAYINFO {
	DWORD	dwObjectSerial;
	DWORD	Level;
	int     JobCode;
	short	Life[2];
	int		x, z;
};

struct	TRANS_PARTY_PLAYINFO {
	int		size, code;

	DWORD	dwObjectSerial;
	DWORD	dwTemp;

	int		PartyUserCount;

	_PARTY_PLAYINFO	PlayInfo[PARTY_PLAYER_MAX];
};

struct	TRANS_PARTY_SKILL {
	int		size, code;
	DWORD	dwSkillCode;
	int		Point;
	int		wParam;
	int		lParam;
	int		sParam;
	int		eParam;
	int		PartyCount;
	DWORD	dwPartyUser[8];
};

struct TRANS_CLAN_COMMAND_USER {
	int size, code;
	int	Param[4];
	int	UserCount;

	char	szUserBuff[2048];
};

#define	CLAN_USER_MAX	64

struct _CLAN_USER_INFO {
	char		szName[32];
	DWORD		dwSpeedSum;
	DWORD		dwObjectSerial;
	rsPLAYINFO* lpPlayInfo;
};

struct	rsCLAN_INFOMATION {
	DWORD	dwClanCode;
	DWORD	dwTemp[32];

	_CLAN_USER_INFO	ClanUserInfo[CLAN_USER_MAX];
};

struct	TRANS_WAREHOUSE {
	int size, code;

	DWORD	dwChkSum;
	WORD	wVersion[2];
	int		WareHouseMoney;
	int		UserMoney;
	DWORD	dwTemp[5];

	int		DataSize;
	BYTE	Data[sizeof(sITEM) * 500 + 256];
};

#define	TRANS_SERVER_MAX		8

struct _TRANS_SERVER_INFO {
	char	szServerName[32];
	char	szServerIp1[20];
	char	szServerIp2[20];
	char	szServerIp3[20];

	DWORD	dwServerPort1;
	DWORD	dwServerPort2;
	DWORD	dwServerPort3;

	DWORD	ConnState;
};

struct TRANS_SERVER_LIST {
	int size, code;

	char	szServerName[16];

	DWORD	dwServerTime_t;
	int		ClanTicket;
	int	dwTemp[1];
	int	ClanServerCount;
	int	ServerCount;
	_TRANS_SERVER_INFO ServerInfo[TRANS_SERVER_MAX];
};

#define	SERVER_MAP_MAX		64

struct	TRANS_SEVER_MAP {
	int size, code;

	DWORD	dwTemp[30];

	int		IP_Count;
	DWORD	dwIP[SERVER_MAP_MAX];
};

struct	TT_DATA_SERVER_INFO {
	char	szServerID[16];
	char	szServerPath[128];
};

#define	SYSTEM_IP_MAX			32
#define	LOGIN_IP_MAX			16
#define	DISABLE_IP_MAX			500
#define	ENABLE_IP_MAX			100
#define	ADMIN_IP_MAX			16
#define CLAN_SERVER_MAX			3
#define ENABLE_MODULE_CHECK_MAX	64
#define	TT_DATA_SERVER_MAX		16

struct rsSERVER_CONFIG {
	DWORD	ServerCode;
	DWORD	AutoPlayer;
	DWORD	DisableParty;
	DWORD	EnablePlayerKill;
	DWORD	ConnectUserMax;

	int		TestSeverMode;

	int		UseRecorMemory;
	int		PotionMonitor;

	int		ClientCheckSumCount;
	int		ClientCheckOut;
	DWORD	dwClientCheckSum[32];

	int		SafeClientCodeCount;
	int		ClientCodeCheckOut;
	DWORD	dwSafeClientCode[32];

	int		LimitVersion;
	int		LimitVersionMax;
	char	szAdminPassword[3][32];
	char	szAdminName[32];

	char	szAdminIP[16];
	char	szAdminLogPassword[32];

	char	szServerName[64];
	int		Enable_PK;
	int		CheckProtect;

	char	szDebugIP[10][32];
	int		DebugIP_Count;

	char	szDebugID[32][32];
	int		DebugID_Count;

	int		BlockLevel;
	int		BlockLevel_LogOut;
	int		ItemCodeOut;

	int		ClientFuncCheckMode;
	int		Enable_PartyItem;

	int		Event_Mandoo;
	int		Event_HardCore;
	int		Event_DamageOff;

	int		Event_DamageOff1;
	int		Event_DamageOff2;

	int		Event_DefenseOff;

	int		Event_Child;
	int		Event_Cristal;
	int		Event_Potion;
	int		Event_StarPointTicket;
	int		Event_ValentineDay;
	int		Event_WhiteDay;
	int		Event_MorifSheltom;
	int		Event_MollyWolf;
	int		Event_Ghost;
	int		Event_SantaGoblin;
	int		Event_WorldCup;
	int		Event_ExpUp;
	int		Event_CoupleRing;
	int		Event_Watermelon;
	int		Event_Star;
	int		Event_Valentine;
	int		Event_PristonAlphabet;
	int		Event_WhiteContrast;
	int		Event_Candydays;
	int		Event_BlackSmith;
	int		Event_MagicalGreen;
	int		Event_TearOfKara;
	int		Event_WarerMelonMonster;
	int		Event_Chichen_Day;
	int		Event_MovieBloodyBattle;

	int     LimitAttack;
	int     LimitDefense;
	int     LimitAbsorb;
	int     LimitDamage;

#ifdef _LANGUAGE_ARGENTINA
	int		Event_ExpUp_latin;
#endif

	int		Event_SummerChicken;
	int		Event_GiftBox;

	int		BlessCastleMode;
	short	sBlessCastle_StartTime[2];

	int		Record_JobChanger;
	int		ForeverBlockMode;

	int		Permit_Exp;
	int		Permit_Money;

	int		ClientProcessTimeChk;
	int		ClientProcessTimeChkOut;
	int		Dis_PotionError;

	int		ExpFixMode;

	char	szBlockUserPath[64];

	int		DispBillingTime;

	int		Disable_LogIn;
	int		Disable_LogQue;
	int		Disable_CheckLogOut;

	int		Disable_LogIn2;
	int		Disable_PCBang;

	int		ExpGameTimeMode;

	int		ServerInventoryMode;

	DWORD	DisableIP[DISABLE_IP_MAX][2];
	int		DisableIP_Count;

	DWORD	EnableIP[ENABLE_IP_MAX][2];
	int		EnableIP_Count;

	DWORD	AdminIP[ADMIN_IP_MAX][2];
	int		AdminIP_Count;

	DWORD	SystemIP[SYSTEM_IP_MAX][2];
	int		SystemIP_Count;

	DWORD	LoginServerIP[LOGIN_IP_MAX][2];
	int		LoginServerIP_Count;

	char	szBackupPath[80];

	char	szClanServerIP[CLAN_SERVER_MAX][20];
	int		ClanServerPort[CLAN_SERVER_MAX];
	int		ClanServerCount;

	DWORD	Enable_ClientModule[ENABLE_MODULE_CHECK_MAX];
	int		Enable_ClientModuleCount;

	int		Disable_DecSkillPoint;

	int		Disable_Quest;

	int		CrazyPacketMode;

	char	szNoticeURL[256];

	TRANS_SEVER_MAP	AreaServer;

	char	szLinkServerIP[32];

	int		RecordAdminCommand;

	int		FreeLevel;
	char	szFreeGpCode[32];
	int		PresentLevel;
	int		Event_ComicBirthDay;
	int		Event_Puzzle;
	int		Event_BabelHorn;
	int		Event_NineFox;
	int		EVENT_Christmas;
	int		EventPlay_BitMask;
	int		Event_PCBangPet;

	int		StartUser_PresentItem;

	int		TT_DataServer_Count;
	TT_DATA_SERVER_INFO		TT_DataServer[TT_DATA_SERVER_MAX];

	int		FixedStartField;
	int		DisableThrowItem;

	int		CheckPlayField;

	int		Enable_PKField;

	int		Enable_PKField_All;

	int		CheckModelFile;

#ifdef LOG_THE_PK

	bool	bPK_LOG;
	rsSERVER_CONFIG()
	{
		bPK_LOG = false;
	};
#endif
};

extern int	ServerMode;

int Serv_ConnectPlayer(smWINSOCK* lpsmSock);

int Serv_DisconnectPlayer(smWINSOCK* lpsmSock);

smCHAR* Serv_CheckOtherPlayPosi(int x, int y, int z);

#define	TOTAL_CHECK_MONEY_MAX		52000
#define	TOTAL_CHECK_EXP_MAX			100000

#define	dwFUNC_VALUE_MAX	64

struct	sFUNC_VALUE {
	DWORD	dwFunc;
	DWORD	dwLen;
	DWORD	dwChkSum;
};

struct	TRANS_CLIENT_FUNPOS {
	int	size, code;

	int	ClientVersion;

	DWORD	dwFunc_CheckMemSum;
	int		FuncCount;

	sFUNC_VALUE	dwFuncValue[dwFUNC_VALUE_MAX];
};

struct	TRANS_FUNC_MEMORY {
	int		size, code;
	int		Param[8];
	char	szData[6000];
};

struct	sCHK_POTION_COUNT {
	int	Ps101;
	int	Ps102;
	int	Ps103;
	int	Ps104;

	int	Pm101;
	int	Pm102;
	int	Pm103;
	int	Pm104;

	int	Pl101;
	int	Pl102;
	int	Pl103;
	int	Pl104;
};

struct	sSOD_SCORE {
	int		Flag;
	DWORD	dwDispTime;
	int		Score;
	int		MyTeam;
	int		TeamScore[4];
	int		Round;
	DWORD	dwPlayTime;

	DWORD	dwSoD_NextStageTime;
	int		SodNextStageNum;
	int		NextRound;
	DWORD	dwSoD_CloseStageTime;

	int		EffectStartCount;
	int		EffectCode;

	int		ScoreEffectCount;
};

#define	JOBCODE_MECHANICIAN			2
#define	JOBCODE_FIGHTER				1
#define	JOBCODE_PIKEMAN				4
#define	JOBCODE_ARCHER				3

#define	JOBCODE_KNIGHT				6
#define	JOBCODE_ATALANTA			5
#define	JOBCODE_PRIESTESS			8
#define	JOBCODE_MAGICIAN			7
#define	JOBCODE_ASSASSINE			9
#define	JOBCODE_SHAMAN  			10
#define	JOBCODE_MARTIAL 			11

#define	CHAR_EVENT_STARPOINT		300

#define	ITEM_UNIQUE_CODE_NORMAL		1
#define	ITEM_UNIQUE_CODE_QUEST		2

#define BIMASK_PRORATE_USER			1
#define BIMASK_FREE_USER			2
#define BIMASK_VIP_USER				4
#define BIMASK_BIRTHDAY_USER		8
#define BIMASK_TIMELEVEL_USER		16
#define BIMASK_ADULT_USER			32

#define	MONSTER_CLASS_NORMAL		0
#define	MONSTER_CLASS_BOSS			1
#define	MONSTER_CLASS_HAMMER		200
#define	MONSTER_CLASS_GHOST			300

#endif
