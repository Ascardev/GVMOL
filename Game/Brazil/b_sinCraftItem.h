

#define   SIN_ADD_FIRE			0x00000001	
#define   SIN_ADD_ICE			0x00000002	
#define   SIN_ADD_LIGHTNING			0x00000004	
#define   SIN_ADD_POISON			0x00000008	
#define   SIN_ADD_BIO			0x00000010	
#define   SIN_ADD_Critico			0x00000020	
#define   SIN_ADD_ATTACK_RATE		0x00000040	
#define   SIN_ADD_DAMAGE_MIN		0x00000080	
#define   SIN_ADD_DAMAGE_MAX		0x00000100	
#define   SIN_ADD_ATTACK_SPEED		0x00000200	
#define   SIN_ADD_ABSORB			0x00000400	
#define   SIN_ADD_DEFENCE			0x00000800	
#define   SIN_ADD_BLOCK_RATE		0x00001000	
#define   SIN_ADD_MOVE_SPEED		0x00002000	
#define   SIN_ADD_LIFE			0x00004000	
#define   SIN_ADD_MANA			0x00008000	
#define   SIN_ADD_STAMINA			0x00010000	
#define   SIN_ADD_LIFEREGEN			0x00020000 	
#define   SIN_ADD_MANAREGEN		0x00040000  	
#define   SIN_ADD_STAMINAREGEN		0x00080000  	

#define   SIN_ADD_NUM				1
#define   SIN_ADD_PERCENT			2



//// Let's make an item!

#define   SIN_ADD_FIRE			0x00000001	//Fogo
#define   SIN_ADD_ICE			0x00000002	//Gelo
#define   SIN_ADD_LIGHTNING			0x00000004	//Raio
#define   SIN_ADD_POISON			0x00000008	//Veneno
#define   SIN_ADD_BIO			0x00000010	//Orgânico
#define   SIN_ADD_Critico			0x00000020	//Crítico
#define   SIN_ADD_ATTACK_RATE		0x00000040	//Taxa de Ataque
#define   SIN_ADD_DAMAGE_MIN		0x00000080	//Poder de Ataque Min.
#define   SIN_ADD_DAMAGE_MAX		0x00000100	//Poder de Ataque Máx.
#define   SIN_ADD_ATTACK_SPEED		0x00000200	//Vel. de Ataque
#define   SIN_ADD_ABSORB			0x00000400	//Absorção
#define   SIN_ADD_DEFENCE			0x00000800	//Taxa de Defesa
#define   SIN_ADD_BLOCK_RATE		0x00001000	//Bloqueio
#define   SIN_ADD_MOVE_SPEED		0x00002000	//Velocidade
#define   SIN_ADD_LIFE			0x00004000	//HP Máx.
#define   SIN_ADD_MANA			0x00008000	//MP Máx.
#define   SIN_ADD_STAMINA			0x00010000	//RES>
#define   SIN_ADD_LIFEREGEN			0x00020000 	//Regen de HP.
#define   SIN_ADD_MANAREGEN		0x00040000  	//Regen de Mana.
#define   SIN_ADD_STAMINAREGEN		0x00080000  	//Regen de RES.

#define   SIN_ADD_NUM				1
#define   SIN_ADD_PERCENT			2



//Mix Expectro Maligno - 3 OS102 e 3 OS18 

							//Armas
			{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, SIN_ADD_Critico, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 6, 8, 2, 30, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+6 Poder de Ataque Min\r+8 Poder de Ataque Max\r+2 Crítico\r+30 HP\r" },

			{ { sinWD1, sinWN1, sinWV1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, SIN_ADD_Critico, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 6, 8, 2, 30, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+6 Poder de Ataque Min\r+8 Poder de Ataque Max\r+2 Crítico\r+30 HP\r" },

				//Armaduras e Robes
			{ { sinDA1, sinDA2, sinDA3, sinDA4, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MANA, 0, 0, 0, 0, 0 },
			{ 350, 6.0f, 110, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0 },
			"+350 Defesa\r+6.0 Absorção\r+110 MP\r" },

				//Escudos
			{ { sinDS1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_BLOCK_RATE, SIN_ADD_LIFE, SIN_ADD_MANA, 0, 0, 0 },
			{ 120, 1.0f, 3, 50, 10, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0 },
			"+120 Defesa\r+1.0 Absorção\r+3 Block\r+50 HP\r+10 MP\r" },

				//Orbs
			{ { sinOM1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_BLOCK_RATE, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 170, 6.0f, 2, 45, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0 },
			"+170 Defesa\r+6.0 Absorção\r+2 Block\r+45 HP\r" },

				//Braceletes
			{ { sinOA2, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_STAMINA, SIN_ADD_MANA, 0, 0, 0, 0 },
			{ 95, 110, 55, 40, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+95 Defesa\r+110 Taxa de ATQ.\r+55 RES\r+40 MP\r" },

				//Luvas
			{ { sinDG1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0 },
			{ 150, 5.0f, 70, 120, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+150 Defesa\r+5.0 Absorção\r+70 MP\r+120 RES\r" },

				//Botas
			{ { sinDB1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_MOVE_SPEED, 0, 0, 0, 0, 0 },
			{ 80, 50, 3.2f, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0 },
			"+80 HP\r+50 MP\r+3.2 Velocidade\r" },

				//Aneis
			{ { sinOR1, sinOR2, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_LIFE, SIN_ADD_STAMINA, SIN_ADD_MANA, SIN_ADD_STAMINAREGEN, 0, 0, 0, 0 },
			{ 40, 40, 40, 3.8f, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+40 HP\r+40 RES\r+40 MP\r+3.8 RES Regen\r" },

				//Amuletos
			{ { sinOA1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_STAMINA, SIN_ADD_MANA, SIN_ADD_STAMINAREGEN, 0, 0, 0, 0, 0 },
			{ 40,40, 3.8f, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0,0, 0 },
			"+40 RES\r+40 MP\r+3.8 RES Regen\r" },

				//Amuletos
			{ { sinOS1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, 0, 0, 0, 0, 0, 0 },
			{ 1,1, 0, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0,0, 0 },
			"+1 Poder de Ataque Min\r+1 Poder de Ataque Max\r" },

			// --------------------------------------------------

				//MIX VALAR - 3 OS119

					//Armas
			{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, SIN_ADD_Critico, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 8, 10, 2, 40, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+8 Poder de Ataque Min\r+10 Poder de Ataque Max\r+2 Crítico\r+40 HP\r" },

			{ { sinWD1, sinWN1, sinWV1 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, SIN_ADD_Critico, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 8, 10, 2, 40, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+8 Poder de Ataque Min\r+10 Poder de Ataque Max\r+2 Crítico\r+40 HP\r" },

				//Armaduras e Robes
			{ { sinDA1, sinDA2, sinDA3, sinDA4, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MANA, 0, 0, 0, 0, 0 },
			{ 450, 8.0f, 150, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0 },
			"+450 Defesa\r+8.0 Absorção\r+150 MP\r" },

				//Escudos
			{ { sinDS1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_BLOCK_RATE, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 180, 2.5f, 5, 100, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0 },
			"+180 Defesa\r+2.5 Absorção\r+5 Block\r+100 HP\r" },

				//Orbs
			{ { sinOM1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_BLOCK_RATE, SIN_ADD_MANA, 0, 0, 0, 0 },
			{ 270, 8.0f, 5, 200, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0 },
			"+270 Defesa\r+8.0 Absorção\r+5 Block\r+200 HP\r" },

				//Braceletes
			{ { sinOA2, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_STAMINA, SIN_ADD_MANA, 0, 0, 0, 0 },
			{ 130, 150, 75, 55, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+130 Defesa\r+150 Taxa de ATQ.\r+75 RES\r+55 MP\r" },

				//Luvas
			{ { sinDG1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0 },
			{ 200, 7.0f, 90, 160, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+200 Defesa\r+7.0 Absorção\r+90 MP\r+160 RES\r" },

				//Botas
			{ { sinDB1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_MOVE_SPEED, 0, 0, 0, 0, 0 },
			{ 120, 70, 5.0f, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0 },
			"+120 HP\r+70 MP\r+5.0 Velocidade\r" },

				//Aneis
			{ { sinOR1, sinOR2, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_LIFE, SIN_ADD_STAMINA, SIN_ADD_MANA, SIN_ADD_STAMINAREGEN, 0, 0, 0, 0 },
			{ 80, 80, 80, 4.3f, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+80 HP\r+80 RES\r+80 MP\r+4.3 RES Regen\r" },

				//Amuletos
			{ { sinOA1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_MANA, SIN_ADD_LIFEREGEN, SIN_ADD_MANAREGEN, 0, 0, 0, 0, 0 },
			{ 120,5.5f, 4.1f, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0,0, 0 },
			"+120 MP\r+5.5 HP Regen\r+4.1 MP Regen\r" },

				//Amuletos
			{ { sinOS1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, 0, 0, 0, 0, 0, 0 },
			{ 2,3, 0, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0,0, 0 },
			"+2 Poder de Ataque Min\r+3 Poder de Ataque Max\r" },


				//MIX VALAR - 3 OS119

					//Armas
			{ { sinWA1, sinWC1, sinWH1, sinWM1, sinWP1, sinWS1, sinWS2, sinWT1 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, SIN_ADD_Critico, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 8, 10, 2, 40, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+8 Poder de Ataque Min\r+10 Poder de Ataque Max\r+2 Crítico\r+40 HP\r" },

			{ { sinWD1, sinWN1, sinWV1 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, SIN_ADD_Critico, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 8, 10, 2, 40, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+8 Poder de Ataque Min\r+10 Poder de Ataque Max\r+2 Crítico\r+40 HP\r" },

				//Armaduras e Robes
			{ { sinDA1, sinDA2, sinDA3, sinDA4, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MANA, 0, 0, 0, 0, 0 },
			{ 450, 8.0f, 150, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0 },
			"+450 Defesa\r+8.0 Absorção\r+150 MP\r" },

				//Escudos
			{ { sinDS1, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_BLOCK_RATE, SIN_ADD_LIFE, 0, 0, 0, 0 },
			{ 180, 2.5f, 5, 100, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0 },
			"+180 Defesa\r+2.5 Absorção\r+5 Block\r+100 HP\r" },

				//Orbs
			{ { sinOM1, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_BLOCK_RATE, SIN_ADD_MANA, 0, 0, 0, 0 },
			{ 270, 8.0f, 5, 200, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0 },
			"+270 Defesa\r+8.0 Absorção\r+5 Block\r+200 HP\r" },

				//Braceletes
			{ { sinOA2, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ATTACK_RATE, SIN_ADD_STAMINA, SIN_ADD_MANA, 0, 0, 0, 0 },
			{ 130, 150, 75, 55, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+130 Defesa\r+150 Taxa de ATQ.\r+75 RES\r+55 MP\r" },

				//Luvas
			{ { sinDG1, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DEFENCE, SIN_ADD_ABSORB, SIN_ADD_MANA, SIN_ADD_STAMINA, 0, 0, 0, 0 },
			{ 200, 7.0f, 90, 160, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+200 Defesa\r+7.0 Absorção\r+90 MP\r+160 RES\r" },

				//Botas
			{ { sinDB1, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_LIFE, SIN_ADD_MANA, SIN_ADD_MOVE_SPEED, 0, 0, 0, 0, 0 },
			{ 120, 70, 5.0f, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0, 0 },
			"+120 HP\r+70 MP\r+5.0 Velocidade\r" },

				//Aneis
			{ { sinOR1, sinOR2, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_LIFE, SIN_ADD_STAMINA, SIN_ADD_MANA, SIN_ADD_STAMINAREGEN, 0, 0, 0, 0 },
			{ 80, 80, 80, 4.3f, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0 },
			"+80 HP\r+80 RES\r+80 MP\r+4.3 RES Regen\r" },

				//Amuletos
			{ { sinOA1, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_MANA, SIN_ADD_LIFEREGEN, SIN_ADD_MANAREGEN, 0, 0, 0, 0, 0 },
			{ 120,5.5f, 4.1f, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0,0, 0 },
			"+120 MP\r+5.5 HP Regen\r+4.1 MP Regen\r" },

				//Amuletos
			{ { sinOS1, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ SIN_ADD_DAMAGE_MIN, SIN_ADD_DAMAGE_MAX, 0, 0, 0, 0, 0, 0 },
			{ 2,3, 0, 0, 0, 0, 0, 0 },
			{ SIN_ADD_NUM, SIN_ADD_NUM, 0, 0, 0, 0,0, 0 },
			"+2 Poder de Ataque Min\r+3 Poder de Ataque Max\r" },

				//Amuletos
			{ { sinOE1, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0 }, //FALTA O OS18 (umbrella sheltom) (3 PEDRAS)
			{ 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0,0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0,0, 0 },
			"" },