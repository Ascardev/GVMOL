






#include "sinLinkHeader.h"

sMESSAGEBOX	sMessageBox[100] = {
	{" No hay suficiente espacio en el inventario "},
	{" Has excedido el límite de peso del inventario "},
	{" El objeto no puede ser utilizado todavía "},
	{" No hay suficiente oro "},
	{" El objeto no se puede mezclar "},
	{" Excede el número  mínimo de objetos de transacción "},
	{" Transacción cancelada "},
	{" Las pociones no se pueden depositar "},
	{" La Mezcla de objetos ha fallado "},
	{" Gracias por su generosa donación"},
	{" Demasiados objetos en el depósito "},
	{" El objeto no puede ser Madurado "},
	{" El objeto ha cambiado. Por favor, controlar "},
	{" Excede el monto mínimo de posesión de oro "},
	{" La Maduración del objeto ha fallado "},
	{" Las estadísticas se han reseteado "},
	{" La imagen del objeto no está preparada "},
	{" Sólo se puede resetear una vez "},
	{" Sólo los miembros del clan pueden utilizar este objeto "},
	{" Debes estar en un clan para utilizar este objeto "},
	{" Imposible transferir debido a restricción de nivel "},
	{" El nivel de Maduración ha sido disminuido en -1 "},
	{" El nivel de Maduración ha sido disminuido en -2 "},
	{" El nivel de Maduración ha sido aumentado en +1 "},
	{" El nivel de Maduración ha sido aumentado en +2 "},
	{" Velocidad de ATK del objeto en misión disminuida "},
	{"   Subir de nivel el objeto en misión    "},
	{"   HP incrementado +15 "},
	{"   El rompecabezas está completado    "},
	{"   El rompecabezas está equivocado    "},
	{"   No hay más objetos para vender  "},
	{" El objeto ya fue vendido "},
	{" La tienda privada del vendedor está cerrada "},
	{"   No se encuentra al vendedor   "},
	{"    Número incorrecto de objetos     "},
	{"    El personaje masculino no puede usar    "},
	{"    El personaje femenino no puede usar    "},
	{" El personaje femenino no puede adquirir el objeto "},
	{" El personaje masculino no puede adquirir el objeto "},
	{"    El precio del objeto ha cambiado  "},
	{"    No hay dinero de premio del clan     "},
	{"  Tu nivel no puede usar el Orbe  "},
	{"     El Orbe está en uso ahora   "},
	{"     La función ATK POW está siendo probada    "},
	{"    La Maduración del Orbe de Fuerza ha sido completada    "},
	{"    Puntos stadisticas incrementados en 5    "},
	{"    Puntos de habilidad incrementados en 1    "},
	{"  Puntos de stat y habilidad incrementados en 5 y 1 "},
	{"  Puntos de stat y habilidad incrementados en 5 y 2 "},
	{"    Exp. de pena de muerte disminuido en 1  "},
	{"   Vitalidad incrementada en 40   " },
	{" Estás en una Misión " },
	{" Sobre nivel 80, obtendrás 7 puntos stat en cada nivel. " },
	{" Sobre nivel 90, obtendrás 10 puntos stat en cada nivel. " },
	{" Reconfigura tus números para entrenamiento. " },
	{" La misión falló por exceso en el tiempo. " },
	{" Demasiados soldados mercenarios. "},
	{" Estás usando un objeto-habilidad. "},
	{" No te puede transferir al Castillo Bless Castle, "},
	{" El objeto no se puede vender a la tienda personal. "},
	{" No hay suficiente monto de impuestos para ser retirado. "},
	{" Ya respondiste la preguntas. "},
	{" Gracias por responder las preguntas. "},
	{" El objeto-sello no corresponde a tu nivel. "},
	{" El objeto fue reconstruido. "},
	{" Gana en la confrontación con Furia. "},
	{" Pierde en la confrontación con Furia. "},
	{" Adquirió objetos en compensación. "},
	{" Los objetos aliados no se pueden usar juntos. "},
	{" Se puede usar más tarde "},
	{" Imposible cancelar mientras se mezcla "},
	{" No se puede llevar arma mientras se mezcla "},
	{" Se usó el mismo tipo de Poción para Teñir el Cabello. "},
	{" Se usó el mismo tipo de Poción la Teñir el Cabello. "},
        {"Ha fallado la Fundición."}, 
	{"Ha fallado la Fabricación del objeto."}, 
	{"En la combinación no puedes mantener los Oros y Cristales."}, 
	{"En la combinación no puedes mantener las recetas."}, 
	{" Estas no son del mismo tipo o de cristales o Oro "}, 
	{" Esta no es la forma correcta de Fabricación."}, 
};



sMESSAGEBOX2 sMessageBox2[20] = {
	{" ¿Cuántos objetos "," quieres comprar? "},
	{" ¿Cuántos objetos "," quieres vender? "},
	{" ¿Cuántos objetos "," quieres tirar? "},
	{" ¿Cuánto oro "," quieres tirar? "},
	{"  ","  "},
	{" ¿Cuánto oro "," quieres intercambiar? "},
	{" ¿Cuánto oro "," quieres mover? "},
	{" ¿Cuánto oro "," quieres recuperar? "},
	{" ¿Cuántas estrellas "," quieres comprar? "},
	{" ¿Cuánto oro "," quieres donar? "},
	{" ¿Quieres registrar"," tu dinero en objetos?  "},
	{" ¿Cuántos objetos "," quieres comprar? "},  
	{" ¿Cuánto oro "," quieres recuperar? "},
	{" ¿Quieres "," comprar el objeto? "},
	{" ¿Quieres "," comprar el objeto? "}, 
	{" ¿Cuánto oro "," quieres retirar? "},
	{" ¿Cuántos mercenarios "," te gustaría comprar? "} 

};

sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = {
	{" ¿Quieres "," adquirir las habilidades? "},
	{" ¿Quieres ", " hacer rank up? "}, 
	{" ¿Quieres ", " llevar a cabo la misión? "},
	{" ¿Quieres "," redistribuir? "},
	{" Cuesta oro "," para el evento "},
	{" ¿Quieres ","initializar las STATS? "},
	{" ¿Quieres ", " llevar a cabo la misión? "}, 
	{" ¿Quieres ", " recibir el objeto? "}, 
	{" ¿Quieres ", " registrar el Núcleo de Unión? "}, 
	{" ¿Quieres ", " recibir el objeto? "}, 
	{" ¿Quieres ", " ir a ? "}, 
	{" "," Por favor tipea el número "}, 
	{" ¿Quieres "," comprar un objeto estrella? "}, 
	{" ¿Quieres ", " vender el objeto? "}, 
	{" ¿Quieres ", " la misión? "}, 
	{" ¿Quieres ", " pagar la donación? "}, 
	{" Tienda Privada ", " fffffffffff "}, 
	{" ¿Quieres ", "exchange to the item? "}, 
	{" ¿Quieres ", "buy the item?"}, 
	{" ¿Quieres ", " cancelar el Registro? "}, 
	{" ¿Quieres ", " intercambiar el objeto? "}, 
	{" ¿Quieres ", " intercambiar el objeto? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Adónde ", " quieres ser teletransportado? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " buscar la misión? "}, 
	{" ¿Quieres ", " hacer rank up? "}, 
	{" ¿Quieres ", " intercambiar el objeto? "},
	{" ¿Te teletransportarías a ", " algún lugar? "},    
	{" ¿te gustaría comprar "," una torre de  cristal? "},      
	{" ¿Quieres ", " obtener la Misión? "}, 
	{" ¿Quieres ", " obtener la Misión? "}, 
	{" ¿Quieres ", " obtener la Misión? "}, 
	{" ¿Quieres ", " obtener la Misión? "}, 
	{" ¿Quieres ", " obtener la Misión? "}, 
	{" ¿Quieres ", " obtener la Misión? "}, 
	{" ¿Quieres ", " obtener la Misión? "}, 
	{" ¿Quieres ", " usar este objeto? "},       
	{" ¿Quieres ", " obtener la Misión? "},
	{" ¿Quieres ", " recibir el objeto? "},   
	{" ¿Quieres "," ir a la Zona de Batalla? "},   
	{" ¿Quieres ", " Teletransportarte? "},
};


char *SkillMaster[4] = {
	" Aprender Habilidad ",
	" Cambiar Clase ",
	" Salir del Juego "

};
char *SkillMaster2[4] = {
	"",
	"",
	""

};

char *ReStartMsg[4] = {
	" ¿Recomenzar desde el campo? ",
	" ¿Recomenzar desde el pueblo? ",
	" ¿Salir del Juego? ",
	" No tienes suficiente XP "

};
char *ReStartMsg2[4] = {
	" Pena(Gold/XP) 1% ",
	"",
	"",
	" para permanecer en el campo ",

};

char *SkillUseInfoText[10]= { "    Entrenar Habilidad/Magia     ","    Seleccionar una Habilidad o Magia     ","      Para aprender o entrenar       ","  No tienes suficientes puntos de Habilidad  ","   para aprender o practicar " };
char *sinMsgSkillPoint = "    Puntos de Habilidad : %d";
char *sinMsgEliteSkillPoint = "Puntos de Habilidad de Elite : %d " ;
char *sinStateName[5]={"H P : %d/%d  ","M P : %d/%d  ","STM : %d/%d  ","X P : %d/%d  ","X P : %dM/%dM  "};


char *TownName[3] = {" Llamada a Ricarten\r"," Llamada a  Navisko\r"," Llamada a  Pillai\r"};

char *sinAbilityName[50] = {"  Poder de Ataque:  \r "," Velocidad del Arma:  \r ","Rango:  \r "," Crítico:  \r "," Capacidad de Defensa:  \r "," Capacidad de Ataque:  \r ",
					" Capacidad de Absorción:  \r "," Capacidad de Bloqueo:  \r "," Velocidad:  \r "," Integridad:  \r "," Recuperación de MP:  \r "," Recuperación de HP:  \r ",
					" Recuperación de STM:  \r "," Tipo Orgánico:  \r "," Tipo Naturaleza:  \r "," Tipo Llama:  \r "," Tipo Escarcha:  \r "," Tipo Rayo:  \r "," Tipo Veneno: \r ",
					" Tipo Agua:  \r "," Tipo Viento:  \r "," Regen. HP :  \r "," Regen. MP: \r "," Regen. STM: \r "," HP Adicional: \r ",
					" MP Adicional:  \r "," STM Adicional:  \r "," Inventario de Pociones:  \r "," Nivel Req.:  \r "," Fuerza Req.:  \r "," Espíritu Req.:  \r ",
					"Req. Talent:  \r","Req. Agility:  \r","Req. Health:  \r"};


char *sinSpecialName[50] = {" ATK SPD Esp.:  \r "," CRIT Esp.:  \r "," DEF RTG Esp.:  \r "," ABS RTG Esp.:  \r ",
						" BLK RTG Esp.:  \r"," APT Mágica:  \r "," SPD Esp.:  \r "," Orgánico Esp.:  \r "," Naturaleza Esp.:  \r ",
						" Flame Esp.:  \r"," Escarcha Esp.:  \r "," Rayo Esp.:  \r "," Veneno Esp.:  \r ","Agua Esp.:  \r "," Viento Esp.:  \r ",
						" ATK POW Esp.:  \r"," ATK RTG Esp.:  \r "," RNG Esp.:  \r "," ATK Orgánico Esp. :  \r "," ATK Naturaleza Esp.:  \r "," ATK Llama Esp.:  \r "," ATK Escarcha Esp.:  \r ",
						" ATK Rayo Esp.:  \r"," ATK Veneno Esp.:  \r "," ATK Agua Esp.:  \r ","ATK Viento Esp.:  \r "," Máx. Incremento de HP:  \r "," Máx. Incremento de MP:  \r ",
						" Recuperación de HP:  \r "," Recuperación de MP:  \r "," Recuperación de STM:  \r "," Precio de Venta:  \r "," Costo:  \r "};


char *SpecialName3 = "%s Especial. \r ";
char *MixResultTitle = " Resultado de la Mezcla de Objetos ";
char *NowLevelText = " Nivel Actual\r ";
char *NextLevelText = " Próximo Nivel\r ";

char *NormalAttckName =" Ataque Estándar ";
char *RequirLevel = " %s (Nivel Req.:%d)\r ";
char *UseItemGroupName = " Grupo de Objetos Compatible \r ";

char *PoisonName = " Tipo de Veneno:\r ";
char *FireName = " Tipo de Llama:\r ";
char *AttackAreaName = " Rango de Ataque:\r ";
char *Attack_RateName = " Capacidad de Ataque:\r ";
char *Max_DamageIncre = " Aumento Máximo de Daño:\r ";
char *DamageAddName = " Aumento de Daño:\r ";
char *Attack_SpeedAdd = " Aumento de Velocidad de Ataque:\r ";
char *IncreBlock = " Mejora de la Capacidad de Bloqueo:\r ";
char *CountinueTime = " Duración:\r ";
char *UseManaName = " Uso de MP:\r ";
char *DamageName = " Poder de Ataque:\r ";
char *ShootingRangeName = " Rango:\r ";
char *IncreAsorb = " Mejora de la Capacidad de Absorción:\r ";
char *SecName = " seg ";
char *PlusDamageName = " Daño Adicional:\r ";
char *HitNumName = " Número de Golpes:\r ";
char *DecreLifeName = " Vida Disminuye:\r ";
char *Attck_RateAdd = " Poder de Ataque Adicional:\r ";
char *Add_CriticalName = " Crítico Adicional:\r ";
char *Push_AreaName = " Largo de Distanciamiento:\r ";
char *FireAttackDamageAdd =" Ataque de Llama:\r ";
char *IceName = " Propiedad de Escarcha:\r ";
char *IceAttackDamageAdd = " Ataque de Escarcha:\r ";
char *StuneRate = " Probabilidad de Paralizar:\r ";
char *DefenseRateIncre = " Capacidad de Defensa Incrementa:\r ";
char *WeaponSizeName =" Tamaño del Arma:\r ";
char *HwakRotationNum = " Rotaciones de Halcón:\r ";
char *WeaponSpeedAddName  = " Velocidad Adicional del Arma:\r ";
char *IncreAttack_RateName = "Incremento en la Capacidad de Ataque:\r ";
char *ShootingNumName = " N°. de Tiros:\r ";
char *SeriesShootingCount = " Fuego Continuo:\r ";
char *UseStaminaName = " Uso de Vigor:\r ";
char *MasterSkillMoneyName = " Costo de la Habilidad:\r ";

char *ItemAgingResult;		

char *sinGold =" %dOro ";
char *sinGiveItem5 = " Objeto de Regalo\r ";
char *sinCopyItem5 = " Objeto Copiado\r ";
char *sinNum7 = " RND ";
char *sinSkillPointName = " Punto de Habilidad ";	
char *sinG_Pike_Time3 = " Tiempo Congelado:\r ";	
char *sinItemLimitTimeOverMsg = " El límite de tiempo ha expirado\r ";
char *sinDeadSongPyeunEat = " ¡Maldición! ¡Es una podrida torta de arroz! ";
char *SmeltingResultTitle = "Resultado de la Fundición";		
char *ManufactureResultTitle = "Creando";	
char *ManufacturingTitle = "al Azar";	


char *sinMaxDamageAdd = " Incremento el Daño Máximo+\r ";
char *sinDamagePiercing = " (Ataque Punzante)\r ";
char *sinAddStamina = " Vigor Agregado:\r ";
char *sinAddLife = " Recuperación de Vida:\r ";

char *sinDamageUndead50 = "50% más daño a unidades de muertos vivos:\r ";
char *sinNumCount2 = " número:\r ";
char *sinNumCount3 = " cantidad\r ";
char *sinDecreDamage = " Disminución de daño:\r ";
char *sinConvert4 = " índice de conversión:\r ";
char *sinIncreElement = " Incremento en característica de elemento:\r ";
char *sinPartyIncreElement = " Miembro del grupo reúne 50% del incremento del elemento\r ";
char *sinFireBallDamage2 = " (100% de daño al enemigo objetivo)\r ";
char *sinFireBallDamage3 = " ( área objetivo 60 (1/3 daño))\r ";
char *sinAddDamage7 = " daño agregado:\r ";
char *PlusDamageWeapon = " arma ";
char *SparkDamage = " daño por unidad:\r ";
char *SparkNum7 = " # de chispa máximo:\r ";
char *StunRage = " Rango de Paralización:\r ";
char *RecvPotion7 = " Poción ";


char *PartyArea7 =" Área del Grupo:\r ";
char *Area17 =" Área:\r ";
char *AddAttack_Rate9 =" Capacidad de Ataque:\r ";
char *PiercingRange =" Rango de Incisión:\r ";
char *IncreDefense = "Increase Defense:\r";
char *AddShootingRange = " Rango Incrementado de SHT:\r ";
char *LifeAbsorb = " Absorción de Vida:\r ";
char *FireDamage = " Daño por Fuego:\r ";
char *IceDamage = " Daño por Hielo:\r ";
char *LightningDamage = " Daño por Rayo:\r ";
char *AddManaRegen = " Maná Adicional Regen.:\r ";
char *LightNum = " # de Rayo:\r ";
char *ReturnDamage = " Retorno de Daño:\r ";
char *Area18 = " Rango disponible:\r ";
char *IncreMana5 = " Incremento de Maná:\r ";
char *Area19 = " Área disponible:\r ";
char *HelpTitle8 = " A Y U D A ";
char *QuestTitle8 = " M I S I Ó N  ";
char *ResearchTitle8 = " INVESTIGACIÓN ";
char *TeleportTitle8 = " TELETRANSPORTE ";

char *IncreWeaponAttack_RateName = " Capacidad de ATK incrementada:\r ";
char *AddMaxDamage = " Daño máximo incrementado:\r ";
char *LinkCoreName = " Teletransportar a un miembro del clan\r ";
char *DesLinkCore = " Nombre: ";
char *Itemul = " objeto ";
char *ItemRecvOk = " ¿Quieres esto? ";
char *Money5 = " oro ";
char *Exp5 = " EXP ";
char *WingItemName[6] = {" Ala de Metal "," Ala de Plata "," Ala de Oro "," Ala Diamante ", " Ala de Caos ", " Ala de Extremo "};
char *WarpGateName[10] = {" Puerta Warp "," Ricarten "," Pillai "," Tierra del Crepúsculo "," Bosque de Bambú "," Villa de Ruinen "," Pueblo de Navisko "," Tierra Prohibida ", " Villa de Eura ", " Tierra del Caos "};
char *sinWarningName5 = " Atención ";
char *ClanCristalName = " Sólo para miembros del clan\r ";
char *NowMyShopSell = " En venta\r ";
char *SecretNumName = " Ingresar números de autenticación ";
char *MyShopExpDoc7 = " Información de Tienda ";
char *NotAgingItem2 = " Imposible madurar el objeto ";
char *ExpPercent2 = " EXP : %d.%d%s ";
char *ExpPercent3 = " EXP : %d.0%d%s ";
char *Mutant7   =   " Mutante ";
char *Mechanic7 = " Mecánico ";
char *Demon7    = " Demonio ";
char *Nomal7    = " Normal ";
char *Undead7    = "Muerto Vivo ";
char *MonsterAddDamage2 = " agregar daño extra)\r ";
char *MonsterAddDamageFire = " agregar daño de elemento fuego)\r ";
char *HaWarpGateName[] = {" Castillo Bless ",0};
char *FallGameName = " Bosque Torcido ";
char *EndlessGameName = " Torre Interminable ";
char *LookHelp	= " más… "; 



char *HoldStarNumDoc = " El número de tus estrellas ";
char *StarItemBuy7   = " Comprar las estrellas ";
char *ChangeMoney7   = "(El precio de una estrella: 100000) ";




char *LightningDamage2 = " Daño por Rayo:\r ";
char *SheildDefense = " Incrementa Defensa:\r ";

char *DemonDamage4  = " Poder de ATK VS Demonio:\r ";
char *PoisonDamage3  = " Daño por Veneno:\r ";
char *PikeNum4       = " Número de lanza:\r ";
char *poisoningTime  = " Tiempo de envenenamiento:\r ";
char *PlusCriticalName = " Incrementa Crítico%:\r ";
char *SpiritFalconDamage2 = " Daño por Espíritu Halcón:\r ";
char *LifeGegenPlus = " Incrementa HP:\r ";
char *PlusDamage4 = " Más daño:\r ";
char *PiercingPercent = " Porcentaje de Incisión:\r ";
char *DamageToLife = " Daño a Vida:\r ";
char *MyMonster7 = " Mi monstruo:\r ";
char *LifeIncre4 = " Incremento de vida:\r ";
char *UndeadDamage3 = " Daño por muerto vivo:\r ";

char *AttackNum3     = " Número de ATK:\r ";
char *AttackRateMinus = " Disminuye capacidad de ATK:\r ";
char *MaxDamagePlus2 = " Máximo Daño Más:\r ";
char *LightningAddDamage3 = " Daño Adicional por Rayo:\r ";
char *ReLifePercent4    = " Re. Porcentaje de Vida:\r ";
char *GetExp3    = " Obtener Exp:\r ";
char *ResurrectionChar4    = " Resurrección Pers. Nivel ";
char *ExtinctionPercent2    = " Porcentaje de Extinción:\r ";
char *ExtinctionAmount2    = " Monto de Extinción:\r ";
char *IncreLifePercent2   = " Incrementa Porcentaje de Vida:\r ";

char *ReduceDamage3 = " Reduce Daño:\r ";
char *IncreMagicDamage = " Incrementa Daño Mágico:\r ";
char *AttackDelay3   = " Retraso de Ataque:\r ";

char *FireDamage2 = " Daño por Fuego:\r ";
char *IceDamage2 = " Daño por Hielo:\r ";
char *AddDefense8 = " Defensa adicional:\r ";
char *SkillDamage5 = " Daño de Habilidad:\r ";

char *FireDamage3 = " Daño por Fuego:\r ";
char *AddSpeed7 = " Velocidad Agregada:\r ";
char *AfterDamage7 = " Daño Residual:\r ";
char *MonsterSight7 = " Visión de monstruo:\r ";



char *LinghtingAddDamage4=" Capacidad de ataque adicionas en rayo:\r ";
char *MaxBoltNum4=" Máx voltaje:\r ";
char *AddAbsorb4=" Índice Adicional de absorción:\r ";
char *IncreArea4=" Incrementar rango:\r ";
char *IncreAttack4=" Más poder de ataque:\r ";
char *GolemLife4=" Vida+STR:\r ";


char *SubAbsorb4=" Disminuye absorción:\r ";
char *AreaDamage4=" Capacidad de ataque para el rango:\r ";
char *MaxAttackNum4=" Máx. golpes:\r ";
char *LifeUp4=" Vitalidad adicional:\r ";

char *CriticalAddDamage4=" Incremento de crítico:\r ";
char *MonstervsSubCritical4=" Debilitar crítico de monstruo:\r ";
char *ChargingAddPercentDamage4=" Capacidad de ataque adicional en carga:\r ";

char *IncreEvasionPercent4=" Porcentaje adicional de evasión:\r ";
char *AddShadowNum4=" Incrementa combinación ocular:\r ";

char *WolverinLife4=" Vitalidad:\r ";
char *WolverinRate4=" Exactitud:\r ";
char *WolverinDefense4=" Índice de Defensa:\r ";
char *AddEvasion4=" Incrementa habilidad de evasión:\r ";
char *AddDamage4=" Incrementa índice de ataque(físico):\r ";
char *FalconAddDamage4=" Incrementa índica de ataque de halcón:\r ";


char *IncreAttackAbsorb4=" Incrementa índice de absorción:\r ";

char *RectAngleArea4=" Atacar en ángulo recto:\r ";

char *MonsterSubSpeed4=" Velocidad decreciente del monstruo atacado:\r ";


char *AddLifeRegen4=" Regeneración de vida adicional:\r ";
char *AddManaRegen4=" Regeneración de maná adicional:\r ";
char *MagicArea4=" Rango afectado por magia:\r ";
char *ChainNum4=" Número de monstruos afectados:\r ";
char *ChainRange4=" Furia del monstruo afectado:\r ";
char *UndeadDamageAbsorb4=" Absorción del ataque de muertos vivientes:\r ";
char *UserBlockPercent4=" Capacidad de Bloqueo para el personaje:\r ";

char *SecondIncreMana4="Incremento de índice de mana por segundo:\r ";
char *FireDamage4=" Índice de ataque de Fuego:\r ";
char *DecreSpeed4=" Velocidad en Disminución:\r ";
char *DecreAttack4=" Índice de ataque disminuido:\r ";
char *AddPercentDamage4=" Índice de ataque agregado:\r ";



char *ChainDamage3    = " Daño por Cadena)\r ";
char *BrandishDamage3 = " Daño por Embiste ";
char *PhysicalAbsorb3 = " Absorción Física ";
char *SparkDamage3    = " Daño por Chispa ";
char *BrutalSwingCritical3   = " Swing Brutal Crítico ";
char *Attck_RateAdd5 = " Attck_RateAdd:\r ";
char *Triumph4=" Triunfo ";
char *Use4=" tú ";
char *DivineShield4=" Bloqueando índice de escudo divino ";


char *QuestMonsterName[] = {" Bargon "," Guerrero Skeleton "," Cortacabezas "," Escarabajo Armado "," Soldado Skeleton "," Titán " ,
                         " Monstruo de la Tierra Prohibida "," Monstruo del Oasis "," Monstruo del 1er piso de la Prisión Antigua "};



char *VampOption[10] ={"Incremento de maduración%: \r "," Vampiro: \r "," RefDaño: \r "," DisminuirHP: \r "," Afortunado: \r "};


char *Quest3ItemName[]={" Cazador de Demonios "," Venganza Antigua "," Niebla "," Lado Demoníaco "," Anaconda "," Espada Laminada "," Fantasma "};

char *Quset3ItemDoc15 = " El objeto de misión ";
char *Quset3ItemDoc16 = " no está ";

char *SparkDamage10 = " Daño por Chispa:\r ";

char *RequirLevel3 = " (Nivel Requerido:%d)\r ";

char *RecvItemTT = " Recibo el objeto ";
char *PuzzleEvent5 = " Rompecabezas Completado ";
char *BabelHorn = " El Cuerno de Babel ";
char *NineTailFoxItem = " Amuleto Nine Tail ";
char *MyShopItemSell5 = " El Precio: \r ";
char *CristalItem     =" los 7 Cristales ";
char *StarDust		= " Polvo Destelleante ";
char *ChristMas	= " Polvo Brillante ";


char *sinDeadCandyEat = " ¡Tiene un gusto horrible! ";

char *PotionCntDoc2 = " Selling price per unit ";
char *ItemPrice7 = " Precio del Objeto ";

char *BuyMyShopItem7 = " %s jugador ha traído %d número de %s por %dOro ";
char *BuyMyShopItem8 = " %s jugador ha traído %d número de %s por %dOro ";
char *ItemName87 = " objeto ";

char *sinEvent87 = " Pedido del coleccionista de peligros ";
char *sinAddDamageItem = " ATKPOWER agregado: \r ";
char *sinContinueTimeItem = " Duración: \r ";
char *BuyPotionMoney = " Dinero: ";
char *BuyPotionKind = " Número: ";
char *SheltomName2[] = {" Lucidy "," Sereneo "," Fadeo "," Sparky "," Raident "," Transparo "," Murky "," Devine "," Celesto "};

char *AddPercentDamage3= "AddATKPOWER%: \r";

char *sinLuckyBox = " Bolsa de la Suerte ";
char *SodMessage_Etc[]= {
			" El ingreso del clan que maneja Bellatra es ",
			" Sólo el jefe del clan lo toma. ",
			" Ahora, el impuesto es %d%s. ",
			};

char *SodMessage_Clan[] = {
			" El ingreso total es como sigue ",
			" Bellatra proveyó el premio ayer. ",
			};

char *SodMessage_Master[] = {
			" El ingreso total es como sigue ",
			" Bellatra proveyó el premio ayer. ",
			" Lo quieres recibir? ",
			};

char *OtherClanMaster[] = {
			" El clan todavía obtiene el premio ",
			" escriba el oro a recibir. ",
			};



char *SiegeMessage_Taxrates[] = {
	" El índice de impuesto ha cambiado a %d%s. ",
	" El Total de impuesto se ha estado acumulando ",
	" Oro. ",
	" ¿Te gustaría retirar el impuesto?. ",
	" El índice de impuesto es ahora %d%s. ",
};
char *SiegeMessage_MercenrayA[] = {
	" Milicia de Ricarten ",
	" Consists en la milicia ",
	" Tiene habilidad de lucha débil, a cambio de su bajo precio. ",
	" Monto máximo de Mercenario::20 / %d ",
};
char *SiegeMessage_MercenrayB[] = {
	" Guardia de Ricarten ",
	" El precio y la habilidad están en equilibrio paa convertirse en Mercenario ",
	" Tiene habilidad de lucha intermedia. ",
	" Monto máximo de Mercenario::20 / %d ",
};
char *SiegeMessage_MercenrayC[] = {
	" Guardia Real de Bless ",
	" El nivel más alto de Mercenario ",
	" habilidad de luchala mayor habilidad de lucha. ",
	" Monto máximo de Mercenario:20 / %d ",
};
char *SiegeMessage_TowerIce[] = {
	" Torre de Cristal de Hielo ",
	" El Atributo de Hielo disminuye la velocidad de los movimientos y ",
	" tiene la habilidad de disminuir la velocidad de ATK. ",
	" La configuración del Cristal de Hielo está completa ",
};
char *SiegeMessage_TowerFire[] = {
	" Torre de Cristal de Fuego ",
	" El Atributo de Fuego otorga un granpoder de ATK ",
	" No tiene habilidades especiales. ",
	" La configuración del Cristal de Fuego está completa ",
};
char *SiegeMessage_TowerLighting[] = {
	"  Torre de Cristal Rayo ",
	" El Rayo disminuye la velocidad de los movimientos y ",
	" tiene la habilidad de disminuir la velocidad de ATK. ",
	" La configuración del Cristal de Rayo está completa ",
};
char *SiegeMessage_MerMoney   = " Dinero de Mercenario: ";
char *SiegeMessage_TowerMoney = " Dinero de la Torre: ";

char *sinClanMaster7 = " Jefe del Clan ";
char *sinPrize7 = " Premio ";

char *sinLevelQuestMonster[]={" Bargon "," Muffin "," Abeja Terrible "," Tifón "," Ratú "," Grotesco "," Puño de Hierro "};
char *sinLevelQusetDoc="Misión> %s %d número de monstruos necesario ";

char *sinTeleportDoc[] = {" Cueva Hongo "," Cueva Enjambre "," Tierra Maldita "," Tierra Prohibida "};
char *sinLevelQuest90_2Mon[] = {" Omega "," D-Máquina "," Montaña "};
char *sinLevelQusetDoc2=" <Misión> Caza %d de %s ";
char *sinLevelQusetDoc3=" <Misión> Obtén el objeto de %s ";
char *sinLimitTiem2 = " Tiempo Límite: \r ";
char *sinMinute2 = " minuto ";
char *sinDay4    = " día ";
char *sinHour4   = " hora ";
char *sinLevelQusetDoc4="<Misión>  Finalizó la caza %d de %s ";

sinSTRING sinTestMsg7(" Hurra, Neh Neh Neh Boo Boo, son perdedores! ");

char *sinMonCodeName[]={
	0,
	" Bargon ",
	" Guerrero Skeleton ",
	" cortacabezas ",
	" Escarabajo Armado ",
	" Soldado Skeleton ",     
	" Titán ",
	" Muffin ",
	" Abeja Terrible ",
	" Tifón ",
	" Ratú ",                
	" Grotesco ",
	" Puño de Hierro ",
	" Omega ",
	" D-Máquina ",
	" Montaña ",              
	" Caballero Skeleton ",
	" Caracol Sólido ",
	" Arrastraespina ",
	" Momia ",
	" Guardia de la Perdición ",             
	" Figon ",
	" Gigante de Piedra",
	" Golem de Piedra ",
	" Guardia de Hierro ",
	" Avelin ",       
	" Avelisk-L ",
	" BeEvil ",
	" Caballero de la Ilusión ",
	" Pesadilla ",
	" Bruja ",                
	" Goblin Pesado ",
	" Dawlin ",
	" Estigio ",
	" Íncubo ",
	" Golem Cadena ",           
	" Espectro Oscuro ",
	" Metron ",
	" Lord Avelisk ",
	" Crepúsculo ",
	" Sadnesst ",            
	0,
};

char *ChargingTime4=" Elevar velocidad para cargar:\r ";
char *AddIceDamage4=" Daño Agregado de Elemental de Escarcha:\r ";
char *IceTime4=" Tiempo Congelado:\r ";
char *sinAttackType = " Tipo de Ataque:\r ";
char *sinAttackType2[2] ={" Manual\r "," Autmático\r "};

char *Won=" Oro ";


char *CastlItemInfo[] ={
	{" Con Modo Dios instantáneo pero\r "},
	{" Porcentaje Crítico\r "},
	{" Agregando porcentaje de evasión\r "},
	{" ST,HP,MA de los jugadores del grupo\r "},
	{" resurreción inmediatamente.\r "},
	{" ATK de torre de Cristal\r "},     
	{" poder de ATK está 20% en el objetivo\r "},
	0,
};
char *CastlItemInfo2[] ={
	{" poder de ATK disminuye en 1/2.\r "},
	{" 5% incremento.\r "},
	{" incrementar.\r "},
	{" recuperar todo.\r "},
	{" \r "},
	{" 50%compensación.\r "},
	{" Agregar.\r "},
	0,
};


char *CharClassTarget[8]={
	" Objetivo(Luchador)\r ",
	" Objetivo(Mecánico)\r ",
	" Objetivo(Piquero)\r ",
	" Objetivo(Arquero)\r ",
	" Objetivo(Caballero)\r ",
	" Objetivo(Atalanta)\r ",
	" Objetivo(Mago)\r ",
	" Objetivo(Sacerdotisa)\r ",
};
char *AttributeTower[4]={
	" Atributo(Fuego)\r ",
	" Atributo(Hielo)\r ",
	" Atributo(Rayo)\r ",
	" Duración:%dSec\r ",
};

char *SiegeMessage_MerComplete =" Configuración de Mercenario completa ";


char *haQuestMonsterName[]={
	" Hoppie ",
	" Rabioso ",
	" Gnomo ",
	" Goblin del Norte ",
	" Skeleton ",
	" Corrupto ",
	" Cíclope ",
	" Bargon ",
	0,
};
char *ha100LVQuestItemName[]={
	" Hacha Minotauro ",
	" Garra Extrema ",
	" Martillo de Hueso de Dragón ",
	" Guadaña de Fuego Infernal ",
	" Arco de la Venganza ",
	" Espada Inmortal ",
	" Jabalina Salamandra ",
	" Cayado Gótico ",
	0,
};

char *ha100LVQuestMonterName[]={
	" Monsters en el Corazón de Perum ",
	" Monstruos del Valle de Gallubia ",
	0,
};
char *ha100LVQuestName = " Fantasma de Furia ";


char *PremiumItemDoc[][2]={
	{" Hace que los puntos de stat\r "     ," sean restribuidos.\r "},     
	{" Hace que los puntos de habilidad\r "     ," sean restribuidos.\r "},    
	{" Hace que los puntos stat/hab \r "," sean restribuidos.\r "},     
	{" Hace que el personaje muerto \r "    ," reviva.\r "},        
	{" Se vuelve invencible por el tiempo establecido.\r "," El poder de ataque disminuye en 1/2\r "},    
	{" 15% de incremento \r "    ," en el ataque crítico.\r "},		
	{" 15% de incremento de \r "         ," chances de evadir.\r "},		
};
char *UpKeepItemDoc[] = {
	" Tiempo Restante : %dMinutos ",
	" %d%s Chance de Caída Adicional ",
	" %d%s incremento en EXP ",
	" Incremento %d%s Ataque ",
	" Recarga de HP por golpe ",
	" Recarga de MP por golpe ",
	0,
};
char *UpKeepItemName[] = {
	" Tercer Ojo ",
	" Poción para incrementar EXP ",
	" Colmillo Vampírico ",
	" Poción de Recarga de Maná ",
	0,
};

