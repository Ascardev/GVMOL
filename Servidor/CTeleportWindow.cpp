#include "sinbaram/sinLinkHeader.h"
#include "cTeleportWindow.h"
#include "field.h"

char Text[38][32];
#define _TELEPORT_FIELDMAX 38

const char* InfoMapa[_TELEPORT_FIELDMAX] = {
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Drops e Exp",
	"Mapa Desativado",
	"Mapa Desativado",
};

//Orginal
const char* FieldNum[_TELEPORT_FIELDMAX][4] = {
	//N�   Field	Level   Nome
	{ "0","20",		"0",	"Estrada dos Ventos"},//ok
	{ "1","19",		"0",	"Vale Tranquilo"},//ok
	{ "2","17",		"0",	"Floresta dos Esp�ritos"},//ok
	{ "3","0",		"0",	"Mata das Ac�cias"},//ok
	{ "4","2",		"0",	"Jardim da Liberdade"},//ok
	{ "5","4",		"0",	"Refugio dos Ancioes"},//ok
	{ "6","5",		"0",	"Castelo dos Perdidos"},//ok
	{ "7","7",		"0",	"Terra Maldita"},//ok
	{ "8","8",		"0",	"Terra Esquecida"},//ok
	{ "9","10",		"40",	"Oasis"},//ok
	{ "10","11",	"55",	"Campo de Batalha"},//ok
	{ "11","12",	"55",	"Terra Proibida"},//ok
	{ "12","25",	"55",	"Caverna das Abelhas"},//ok
	{"13","24",	"55",	"Caverna dos Cogumelos"},//ok
	{ "14","26",	"65",	"Santu�rio Sombrio"},//ok
	{ "15","13",	"40",	"Calabou�o Antigo 1� Andar"},//ok
	{ "16","14",	"50",	"Calabou�o Antigo 2� Andar"},//ok
	{ "17","15",	"60",	"Calabou�o Antigo 3� Andar"},//ok
	{ "18","22",	"70",	"Templo Maldito 1� Andar"},//ok
	{ "19","23",	"75",	"Templo Maldito 2� Andar"},//ok
	{ "20","42",	"80",	"Templo Maldito 3� Andar"},//ok
	{ "21","34",	"70",	"Lago da Gan�ncia"},//ok
	{ "22","27",	"80",	"Estrada de Ferro do Caos"},//ok
	{ "23","28",	"85",	"Cora��o de Perum"},//ok
	{ "24","29",	"90",	"Eura"},//ok
	{ "25","31",	"90",	"Vale Gallubia"},//ok
	{ "26","35",	"90",	"Santu�rio Congelado"},//ok
	{ "27","36",	"90",	"Covil de Kelvezu"},//ok
	{ "28","37",	"95",	"Ilha Perdida"},//ok
	{ "29","38",	"100",	"Templo Perdido"},
	{ "30","40",	"108",	"Torre Sem Fim 1o Andar"},
	{ "31","41",	"110",	"Torre Sem Fim 2� Andar"},
	{ "32","43",	"112",	"Torre Sem Fim 3� Andar"},
	{ "33","44",	"115",	"Mina de Gelo 1� Andar"},
	{ "34","46",	"118",	"Laborat�rio Secreto"},
	{ "35","47",	"123",	"Arma Secreta"},
	{ "36","48",	"160",	"Abismo do Mar 1� Andar"},
	{ "37","49",	"160",	"Abismo do Mar 2� andar"}
};

int mapa, index = 1, click, lvl, imagemapa;
BOOL StopTcore;
int basex = 450;
int basey = 90;
SIZE size4[38] = {};

bool isMousePos(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return true;

	return false;
}

void TCORE::init() {
	imagens[JANELA] = CreateTextureMaterial("game\\images\\teleport\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[BTNTELEPORT] = CreateTextureMaterial("game\\images\\teleport\\btnteleport.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[BTNTELEPORT_] = CreateTextureMaterial("game\\images\\teleport\\btnteleport_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[BTNCLOSE] = CreateTextureMaterial("game\\images\\teleport\\close.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[BTNCLOSE_] = CreateTextureMaterial("game\\images\\teleport\\close_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[EXP] = CreateTextureMaterial("game\\images\\teleport\\expdrop.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[HUNT] = CreateTextureMaterial("game\\images\\teleport\\hunt.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[GOLD] = CreateTextureMaterial("game\\images\\teleport\\gold.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[TOWN] = CreateTextureMaterial("game\\images\\teleport\\exp.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[SHELTONS] = CreateTextureMaterial("game\\images\\teleport\\sheltons.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[PVP] = CreateTextureMaterial("game\\images\\teleport\\pvp.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[HUNTPVP] = CreateTextureMaterial("game\\images\\teleport\\huntpvp.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[12] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\border.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[13] = CreateTextureMaterial("game\\images\\teleport\\page1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[14] = CreateTextureMaterial("game\\images\\teleport\\page1_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[15] = CreateTextureMaterial("game\\images\\teleport\\page2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[16] = CreateTextureMaterial("game\\images\\teleport\\page2_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[17] = CreateTextureMaterial("game\\images\\teleport\\page3.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[18] = CreateTextureMaterial("game\\images\\teleport\\page3_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imagens[19] = CreateTextureMaterial("game\\images\\teleport\\expdrop.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[0] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\estrada-dos-ventos.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[1] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\vale-tranquilo.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[2] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\floresta-espirito.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[3] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\mata-acacias.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[4] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\jardim-liberdade.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[5] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\refugio-ancioes.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[6] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\castelo-perdidos.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[7] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\terra-maldita.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[8] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\terra-esquecida.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[9] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\oasis.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[10] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\cba.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[11] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\terra-proibida.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[12] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\bcave.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[13] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\mcave.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[14] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\ds.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[15] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\dun1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[16] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\dun2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[17] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\dun3.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[18] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\s1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[19] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\s2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[20] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\s3.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[21] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\gl.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[22] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\iron1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[23] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\iron2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[24] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\eura.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[25] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\ice1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[26] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\ice2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[27] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\kcave.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[28] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\lost1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[29] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\lost2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[30] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\et1.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[31] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\et2.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[32] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\et3.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[33] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\mine-ice.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[34] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\slab.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[35] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\AncientW.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[36] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\SeaA.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	imgs[37] = CreateTextureMaterial("game\\images\\teleport\\Mapas\\Stemple.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	for (int i = 0; i < _TELEPORT_FIELDMAX; i++) {
		wsprintf(Text[i], "%d. %s", atoi(FieldNum[i][0]), FieldNum[i][3]);
		GetFontTextExtentPoint(Text[i], lstrlen(Text[i]), &size4[i]);
	}
	//AddChatBuff("testaa");
};

void TCORE::DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}

void TCORE::Draw() {
	if (Open) {
		DWORD CORSELECT = RGB(255, 191, 89);
		DWORD COR = RGB(255, 255, 255);
		DWORD COR1 = RGB(255, 100, 0);
		DWORD COR2 = RGB(160, 160, 160);
		int cd = (smScreenWidth / 2) - 180;
		StopTcore = TRUE;
		DrawImage(imagens[JANELA], smScreenWidth / 2 - 240, 80, 480, 500);
		DrawImage(imgs[click], smScreenWidth / 2 + 60, 136, 119, 119);

		DrawImage(imagens[12], smScreenWidth / 2 + 50, 130, 145, 130);
		if (index == 1) {
			DrawImage(imagens[13], cd + 44, basey + 400, 26, 26);
		}
		else {
			DrawImage(imagens[14], cd + 44, basey + 400, 26, 26);
		}
		if (index == 2) {
			DrawImage(imagens[15], cd + 74, basey + 400, 26, 26);
		}
		else {
			DrawImage(imagens[16], cd + 74, basey + 400, 26, 26);
		}
		if (index == 3) {
			DrawImage(imagens[17], cd + 104, basey + 400, 26, 26);
		}
		else {
			DrawImage(imagens[18], cd + 104, basey + 400, 26, 26);
		}
		SIZE size4 = {};
		GetFontTextExtentPoint(FieldNum[click][3], lstrlen(FieldNum[click][3]), &size4);
		DrawFontTextNew((smScreenWidth / 2 + 120) - (size4.cx / 2), basey + 170, FieldNum[click][3], CORSELECT, 1);
		size4 = {};
		GetFontTextExtentPoint(InfoMapa[click], lstrlen(InfoMapa[click]), &size4);
		DrawFontTextNew((smScreenWidth / 2 + 120) - (size4.cx / 2), basey + 230, InfoMapa[click], COR2, 1);

		char LvlReq[32] = { 0 };
		wsprintf(LvlReq, "Level Requerido %d", atoi(FieldNum[click][2]));
		size4 = {};
		GetFontTextExtentPoint(LvlReq, lstrlen(LvlReq), &size4);
		DrawFontTextNew((smScreenWidth / 2 + 120) - (size4.cx / 2), basey + 190, LvlReq, COR2, 1);

		if (isMousePos(smScreenWidth / 2 + 35, 450, 182, 48)) {
			DrawImage(imagens[BTNTELEPORT_], smScreenWidth / 2 + 35, 450, 182, 48);
		}
		else {
			DrawImage(imagens[BTNTELEPORT], smScreenWidth / 2 + 35, 450, 182, 48);
		}
		if (isMousePos(smScreenWidth / 2 + 207, 91, 26, 26)) {
			DrawImage(imagens[BTNCLOSE_], smScreenWidth / 2 + 207, 91, 26, 26);
		}
		else {
			DrawImage(imagens[BTNCLOSE], smScreenWidth / 2 + 207, 91, 26, 26);
		}

		if (index == 1) {
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 42, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 62, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 82, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 102, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 122, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 142, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 162, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 182, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 202, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 222, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 242, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 262, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 282, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 302, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 322, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 342, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 362, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 382, 40, 13);

			size4 = {};
			GetFontTextExtentPoint(Text[0], lstrlen(Text[0]), &size4);
			if (isMousePos(cd, basey + 40, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 40, Text[0], COR1, 3);
			}
			else if (click == 0) {
				DrawFontTextNew(cd, basey + 40, Text[0], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 40, Text[0], COR, 3);
			}

			//
			size4 = {};
			GetFontTextExtentPoint(Text[1], lstrlen(Text[1]), &size4);
			if (isMousePos(cd, basey + 60, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 60, Text[1], COR1, 3);
			}
			else if (click == 1) {
				DrawFontTextNew(cd, basey + 60, Text[1], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 60, Text[1], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[2], lstrlen(Text[2]), &size4);
			if (isMousePos(cd, basey + 80, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 80, Text[2], COR1, 3);
			}
			else if (click == 2) {
				DrawFontTextNew(cd, basey + 80, Text[2], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 80, Text[2], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[3], lstrlen(Text[3]), &size4);
			if (isMousePos(cd, basey + 100, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 100, Text[3], COR1, 3);
			}
			else if (click == 3) {
				DrawFontTextNew(cd, basey + 100, Text[3], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 100, Text[3], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[4], lstrlen(Text[4]), &size4);
			if (isMousePos(cd, basey + 120, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 120, Text[4], COR1, 3);
			}
			else if (click == 4) {
				DrawFontTextNew(cd, basey + 120, Text[4], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 120, Text[4], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[5], lstrlen(Text[5]), &size4);
			if (isMousePos(cd, basey + 140, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 140, Text[5], COR1, 3);
			}
			else if (click == 5) {
				DrawFontTextNew(cd, basey + 140, Text[5], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 140, Text[5], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[6], lstrlen(Text[6]), &size4);
			if (isMousePos(cd, basey + 160, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 160, Text[6], COR1, 3);
			}
			else if (click == 6) {
				DrawFontTextNew(cd, basey + 160, Text[6], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 160, Text[6], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[7], lstrlen(Text[7]), &size4);
			if (isMousePos(cd, basey + 180, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 180, Text[7], COR1, 3);
			}
			else if (click == 7) {
				DrawFontTextNew(cd, basey + 180, Text[7], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 180, Text[7], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[8], lstrlen(Text[8]), &size4);
			if (isMousePos(cd, basey + 200, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 200, Text[8], COR1, 3);
			}
			else if (click == 8) {
				DrawFontTextNew(cd, basey + 200, Text[8], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 200, Text[8], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[9], lstrlen(Text[9]), &size4);
			if (isMousePos(cd, basey + 220, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 220, Text[9], COR1, 3);
			}
			else if (click == 9) {
				DrawFontTextNew(cd, basey + 220, Text[9], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 220, Text[9], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[10], lstrlen(Text[10]), &size4);
			if (isMousePos(cd, basey + 240, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 240, Text[10], COR1, 3);
			}
			else if (click == 10) {
				DrawFontTextNew(cd, basey + 240, Text[10], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 240, Text[10], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[11], lstrlen(Text[11]), &size4);
			if (isMousePos(cd, basey + 260, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 260, Text[11], COR1, 3);
			}
			else if (click == 11) {
				DrawFontTextNew(cd, basey + 260, Text[11], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 260, Text[11], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[12], lstrlen(Text[12]), &size4);
			if (isMousePos(cd, basey + 280, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 280, Text[12], COR1, 3);
			}
			else if (click == 12) {
				DrawFontTextNew(cd, basey + 280, Text[12], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 280, Text[12], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[13], lstrlen(Text[13]), &size4);
			if (isMousePos(cd, basey + 300, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 300, Text[13], COR1, 3);
			}
			else if (click == 13) {
				DrawFontTextNew(cd, basey + 300, Text[13], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 300, Text[13], COR, 3);
			}
			/// <summary>
			/// //////////////
			/// </summary>
			size4 = {};
			GetFontTextExtentPoint(Text[14], lstrlen(Text[14]), &size4);
			if (isMousePos(cd, basey + 320, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 320, Text[14], COR1, 3);
			}
			else if (click == 14) {
				DrawFontTextNew(cd, basey + 320, Text[14], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 320, Text[14], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[15], lstrlen(Text[15]), &size4);
			if (isMousePos(cd, basey + 340, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 340, Text[15], COR1, 3);
			}
			else if (click == 15) {
				DrawFontTextNew(cd, basey + 340, Text[15], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 340, Text[15], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[16], lstrlen(Text[16]), &size4);
			if (isMousePos(cd, basey + 360, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 360, Text[16], COR1, 3);
			}
			else if (click == 16) {
				DrawFontTextNew(cd, basey + 360, Text[16], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 360, Text[16], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[17], lstrlen(Text[17]), &size4);
			if (isMousePos(cd, basey + 380, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 380, Text[17], COR1, 3);
			}
			else if (click == 17) {
				DrawFontTextNew(cd, basey + 380, Text[17], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 380, Text[17], COR, 3);
			}
		}

		else if (index == 2) {
			//Imagens do Core pvp , sheltons exp dropexp //Caso Queira add mais, So diminui ou aumentar  Basey +20 ou -20 Rubinho
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 42, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 62, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 82, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 102, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 122, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 142, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 162, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 182, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 202, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 222, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 242, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 262, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 282, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 302, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 322, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 342, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 362, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 382, 40, 13);
			size4 = {};
			GetFontTextExtentPoint(Text[18], lstrlen(Text[18]), &size4);
			if (isMousePos(cd, basey + 40, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 40, Text[18], COR1, 3);
			}
			else if (click == 18) {
				DrawFontTextNew(cd, basey + 40, Text[18], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 40, Text[18], COR, 3);
			}

			//
			size4 = {};
			GetFontTextExtentPoint(Text[19], lstrlen(Text[19]), &size4);
			if (isMousePos(cd, basey + 60, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 60, Text[19], COR1, 3);
			}
			else if (click == 19) {
				DrawFontTextNew(cd, basey + 60, Text[19], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 60, Text[19], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[20], lstrlen(Text[20]), &size4);
			if (isMousePos(cd, basey + 80, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 80, Text[20], COR1, 3);
			}
			else if (click == 20) {
				DrawFontTextNew(cd, basey + 80, Text[20], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 80, Text[20], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[21], lstrlen(Text[21]), &size4);
			if (isMousePos(cd, basey + 100, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 100, Text[21], COR1, 3);
			}
			else if (click == 21) {
				DrawFontTextNew(cd, basey + 100, Text[21], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 100, Text[21], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[22], lstrlen(Text[22]), &size4);
			if (isMousePos(cd, basey + 120, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 120, Text[22], COR1, 3);
			}
			else if (click == 22) {
				DrawFontTextNew(cd, basey + 120, Text[22], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 120, Text[22], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[23], lstrlen(Text[23]), &size4);
			if (isMousePos(cd, basey + 140, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 140, Text[23], COR1, 3);
			}
			else if (click == 23) {
				DrawFontTextNew(cd, basey + 140, Text[23], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 140, Text[23], COR, 3);
			}
			//
			size4 = {};
			GetFontTextExtentPoint(Text[24], lstrlen(Text[24]), &size4);
			if (isMousePos(cd, basey + 160, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 160, Text[24], COR1, 3);
			}
			else if (click == 24) {
				DrawFontTextNew(cd, basey + 160, Text[24], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 160, Text[24], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[25], lstrlen(Text[25]), &size4);
			if (isMousePos(cd, basey + 180, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 180, Text[25], COR1, 3);
			}
			else if (click == 25) {
				DrawFontTextNew(cd, basey + 180, Text[25], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 180, Text[25], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[26], lstrlen(Text[26]), &size4);
			if (isMousePos(cd, basey + 200, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 200, Text[26], COR1, 3);
			}
			else if (click == 26) {
				DrawFontTextNew(cd, basey + 200, Text[26], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 200, Text[26], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[27], lstrlen(Text[27]), &size4);
			if (isMousePos(cd, basey + 220, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 220, Text[27], COR1, 3);
			}
			else if (click == 27) {
				DrawFontTextNew(cd, basey + 220, Text[27], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 220, Text[27], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[28], lstrlen(Text[28]), &size4);
			if (isMousePos(cd, basey + 240, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 240, Text[28], COR1, 3);
			}
			else if (click == 28) {
				DrawFontTextNew(cd, basey + 240, Text[28], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 240, Text[28], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[29], lstrlen(Text[29]), &size4);
			if (isMousePos(cd, basey + 260, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 260, Text[29], COR1, 3);
			}
			else if (click == 29) {
				DrawFontTextNew(cd, basey + 260, Text[29], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 260, Text[29], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[30], lstrlen(Text[30]), &size4);
			if (isMousePos(cd, basey + 280, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 280, Text[30], COR1, 3);
			}
			else if (click == 30) {
				DrawFontTextNew(cd, basey + 280, Text[30], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 280, Text[30], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[31], lstrlen(Text[31]), &size4);
			if (isMousePos(cd, basey + 300, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 300, Text[31], COR1, 3);
			}
			else if (click == 31) {
				DrawFontTextNew(cd, basey + 300, Text[31], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 300, Text[31], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[32], lstrlen(Text[32]), &size4);
			if (isMousePos(cd, basey + 320, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 320, Text[32], COR1, 3);
			}
			else if (click == 32) {
				DrawFontTextNew(cd, basey + 320, Text[32], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 320, Text[32], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[33], lstrlen(Text[33]), &size4);
			if (isMousePos(cd, basey + 340, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 340, Text[33], COR1, 3);
			}
			else if (click == 33) {
				DrawFontTextNew(cd, basey + 340, Text[33], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 340, Text[33], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[34], lstrlen(Text[34]), &size4);
			if (isMousePos(cd, basey + 360, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 360, Text[34], COR1, 3);
			}
			else if (click == 34) {
				DrawFontTextNew(cd, basey + 360, Text[34], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 360, Text[34], COR, 3);
			}
			size4 = {};
			GetFontTextExtentPoint(Text[35], lstrlen(Text[35]), &size4);
			if (isMousePos(cd, basey + 380, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 380, Text[35], COR1, 3);
			}
			else if (click == 35) {
				DrawFontTextNew(cd, basey + 380, Text[35], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 380, Text[35], COR, 3);
			}
		}
		else if (index == 3) {
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 42, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 62, 40, 13);

			size4 = {};
			GetFontTextExtentPoint(Text[36], lstrlen(Text[36]), &size4);
			if (isMousePos(cd, basey + 40, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 40, Text[36], COR1, 3);
			}
			else if (click == 36) {
				DrawFontTextNew(cd, basey + 40, Text[36], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 40, Text[36], COR, 3);
			}

			//
			size4 = {};
			GetFontTextExtentPoint(Text[37], lstrlen(Text[37]), &size4);
			if (isMousePos(cd, basey + 60, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 60, Text[37], COR1, 3);
			}
			else if (click == 37) {
				DrawFontTextNew(cd, basey + 60, Text[37], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 60, Text[37], COR, 3);
			}
		}
		////////////////
		else if (index == 3) {
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 42, 40, 13);
			DrawImage(imagens[EXP], smScreenWidth / 2 - 223, basey + 62, 40, 13);

			size4 = {};
			GetFontTextExtentPoint(Text[36], lstrlen(Text[36]), &size4);
			if (isMousePos(cd, basey + 40, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 40, Text[36], COR1, 3);
			}
			else if (click == 36) {
				DrawFontTextNew(cd, basey + 40, Text[36], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 40, Text[36], COR, 3);
			}

			//
			size4 = {};
			GetFontTextExtentPoint(Text[37], lstrlen(Text[37]), &size4);
			if (isMousePos(cd, basey + 60, size4.cx + 13, 15)) {
				DrawFontTextNew(cd, basey + 60, Text[37], COR1, 3);
			}
			else if (click == 37) {
				DrawFontTextNew(cd, basey + 60, Text[37], COR1, 3);
			}
			else {
				DrawFontTextNew(cd, basey + 60, Text[37], COR, 3);
			}
		}
	}
}

bool TCORE::MouseIn() {
	int cd = (smScreenWidth / 2) - 180;
	DWORD COR = RGB(255, 100, 0);
	if (Open) {
		if (isMousePos((smScreenWidth / 2) - 180 + 44, basey + 400, 26, 26)) {
			index = 1;
		}

		if (isMousePos((smScreenWidth / 2) - 180 + 74, basey + 400, 26, 26)) {
			index = 2;
		}

		if (isMousePos((smScreenWidth / 2) - 180 + 104, basey + 400, 26, 26)) {
			index = 3;
		}

		if (isMousePos(smScreenWidth / 2 + 210, 82, 26, 26)) {
			tcoreClose();
			StopTcore = FALSE;
		}
		if (index == 1) {
			if (isMousePos(cd, basey + 40, 120, 15)) {
				mapa = atoi(FieldNum[0][1]);
				click = atoi(FieldNum[0][0]);
				lvl = atoi(FieldNum[0][2]);
			}
			if (isMousePos(cd, basey + 60, 120, 15)) {
				mapa = atoi(FieldNum[1][1]);
				click = atoi(FieldNum[1][0]);
				lvl = atoi(FieldNum[1][2]);
			}
			if (isMousePos(cd, basey + 80, size4[2].cx + 13, 15)) {
				mapa = atoi(FieldNum[2][1]);
				click = atoi(FieldNum[2][0]);
				lvl = atoi(FieldNum[2][2]);
			}
			if (isMousePos(cd, basey + 100, size4[3].cx + 13, 15)) {
				mapa = atoi(FieldNum[3][1]);
				click = atoi(FieldNum[3][0]);
				lvl = atoi(FieldNum[3][2]);
			}
			if (isMousePos(cd, basey + 120, size4[4].cx + 13, 15)) {
				mapa = atoi(FieldNum[4][1]);
				click = atoi(FieldNum[4][0]);
				lvl = atoi(FieldNum[4][2]);
			}
			if (isMousePos(cd, basey + 140, size4[5].cx + 13, 15)) {
				mapa = atoi(FieldNum[5][1]);
				click = atoi(FieldNum[5][0]);
				lvl = atoi(FieldNum[5][2]);
			}
			if (isMousePos(cd, basey + 160, size4[6].cx + 13, 15)) {
				mapa = atoi(FieldNum[6][1]);
				click = atoi(FieldNum[6][0]);
				lvl = atoi(FieldNum[6][2]);
			}
			if (isMousePos(cd, basey + 180, size4[7].cx + 13, 15)) {
				mapa = atoi(FieldNum[7][1]);
				click = atoi(FieldNum[7][0]);
				lvl = atoi(FieldNum[7][2]);
			}
			if (isMousePos(cd, basey + 200, size4[8].cx + 13, 15)) {
				mapa = atoi(FieldNum[8][1]);
				click = atoi(FieldNum[8][0]);
				lvl = atoi(FieldNum[8][2]);
			}
			if (isMousePos(cd, basey + 220, size4[9].cx + 13, 15)) {
				mapa = atoi(FieldNum[9][1]);
				click = atoi(FieldNum[9][0]);
				lvl = atoi(FieldNum[9][2]);
			}
			if (isMousePos(cd, basey + 240, size4[10].cx + 13, 15)) {
				mapa = atoi(FieldNum[10][1]);
				click = atoi(FieldNum[10][0]);
				lvl = atoi(FieldNum[10][2]);
			}
			if (isMousePos(cd, basey + 260, size4[11].cx + 13, 15)) {
				mapa = atoi(FieldNum[11][1]);
				click = atoi(FieldNum[11][0]);
				lvl = atoi(FieldNum[11][2]);
			}
			if (isMousePos(cd, basey + 280, size4[12].cx + 13, 15)) {
				mapa = atoi(FieldNum[12][1]);
				click = atoi(FieldNum[12][0]);
				lvl = atoi(FieldNum[12][2]);
			}
			if (isMousePos(cd, basey + 300, size4[13].cx + 13, 15)) {
				mapa = atoi(FieldNum[13][1]);
				click = atoi(FieldNum[13][0]);
				lvl = atoi(FieldNum[13][2]);
			}
			/// ////////

			if (isMousePos(cd, basey + 320, size4[14].cx + 13, 15)) {
				mapa = atoi(FieldNum[14][1]);
				click = atoi(FieldNum[14][0]);
				lvl = atoi(FieldNum[14][2]);
			}
			if (isMousePos(cd, basey + 340, size4[15].cx + 13, 15)) {
				mapa = atoi(FieldNum[15][1]);
				click = atoi(FieldNum[15][0]);
				lvl = atoi(FieldNum[15][2]);
			}
			if (isMousePos(cd, basey + 360, size4[16].cx + 13, 15)) {
				mapa = atoi(FieldNum[16][1]);
				click = atoi(FieldNum[16][0]);
				lvl = atoi(FieldNum[16][2]);
			}
			if (isMousePos(cd, basey + 380, size4[17].cx + 13, 15)) {
				mapa = atoi(FieldNum[17][1]);
				click = atoi(FieldNum[17][0]);
				lvl = atoi(FieldNum[17][2]);
			}
		}

		else if (index == 2) {
			////////////
			if (isMousePos(cd, basey + 40, size4[18].cx + 13, 15)) {
				mapa = atoi(FieldNum[18][1]);
				click = atoi(FieldNum[18][0]);
				lvl = atoi(FieldNum[18][2]);
			}
			if (isMousePos(cd, basey + 60, size4[19].cx + 13, 15)) {
				mapa = atoi(FieldNum[19][1]);
				click = atoi(FieldNum[19][0]);
				lvl = atoi(FieldNum[19][2]);
			}
			if (isMousePos(cd, basey + 80, size4[20].cx + 13, 15)) {
				mapa = atoi(FieldNum[20][1]);
				click = atoi(FieldNum[20][0]);
				lvl = atoi(FieldNum[20][2]);
			}
			if (isMousePos(cd, basey + 100, size4[21].cx + 13, 15)) {
				mapa = atoi(FieldNum[21][1]);
				click = atoi(FieldNum[21][0]);
				lvl = atoi(FieldNum[21][2]);
			}
			if (isMousePos(cd, basey + 120, size4[22].cx + 13, 15)) {
				mapa = atoi(FieldNum[22][1]);
				click = atoi(FieldNum[22][0]);
				lvl = atoi(FieldNum[22][2]);
			}
			if (isMousePos(cd, basey + 140, size4[23].cx + 13, 15)) {
				mapa = atoi(FieldNum[23][1]);
				click = atoi(FieldNum[23][0]);
				lvl = atoi(FieldNum[23][2]);
			}
			if (isMousePos(cd, basey + 160, size4[24].cx + 13, 15)) {
				mapa = atoi(FieldNum[24][1]);
				click = atoi(FieldNum[24][0]);
				lvl = atoi(FieldNum[24][2]);
			}
			if (isMousePos(cd, basey + 180, size4[25].cx + 13, 15)) {
				mapa = atoi(FieldNum[25][1]);
				click = atoi(FieldNum[25][0]);
				lvl = atoi(FieldNum[25][2]);
			}
			if (isMousePos(cd, basey + 200, size4[26].cx + 13, 15)) {
				mapa = atoi(FieldNum[26][1]);
				click = atoi(FieldNum[26][0]);
				lvl = atoi(FieldNum[26][2]);
			}
			if (isMousePos(cd, basey + 220, size4[27].cx + 13, 15)) {
				mapa = atoi(FieldNum[27][1]);
				click = atoi(FieldNum[27][0]);
				lvl = atoi(FieldNum[27][2]);
			}
			if (isMousePos(cd, basey + 240, size4[28].cx + 13, 15)) {
				mapa = atoi(FieldNum[28][1]);
				click = atoi(FieldNum[28][0]);
				lvl = atoi(FieldNum[28][2]);
			}
			if (isMousePos(cd, basey + 260, size4[29].cx + 13, 15)) {
				mapa = atoi(FieldNum[29][1]);
				click = atoi(FieldNum[29][0]);
				lvl = atoi(FieldNum[29][2]);
			}
			if (isMousePos(cd, basey + 280, size4[30].cx + 13, 15)) {
				mapa = atoi(FieldNum[30][1]);
				click = atoi(FieldNum[30][0]);
				lvl = atoi(FieldNum[30][2]);
			}
			if (isMousePos(cd, basey + 300, size4[31].cx + 13, 15)) {
				mapa = atoi(FieldNum[31][1]);
				click = atoi(FieldNum[31][0]);
				lvl = atoi(FieldNum[31][2]);
			}
			if (isMousePos(cd, basey + 320, size4[32].cx + 13, 15)) {
				mapa = atoi(FieldNum[32][1]);
				click = atoi(FieldNum[32][0]);
				lvl = atoi(FieldNum[32][2]);
			}
			if (isMousePos(cd, basey + 340, size4[33].cx + 13, 15)) {
				mapa = atoi(FieldNum[33][1]);
				click = atoi(FieldNum[33][0]);
				lvl = atoi(FieldNum[33][2]);
			}
			if (isMousePos(cd, basey + 360, size4[34].cx + 13, 15)) {
				mapa = atoi(FieldNum[34][1]);
				click = atoi(FieldNum[34][0]);
				lvl = atoi(FieldNum[34][2]);
			}
			if (isMousePos(cd, basey + 380, size4[35].cx + 13, 15)) {
				mapa = atoi(FieldNum[35][1]);
				click = atoi(FieldNum[35][0]);
				lvl = atoi(FieldNum[35][2]);
			}
		}

		else if (index == 3) {
			if (isMousePos(cd, basey + 40, size4[36].cx + 13, 15)) {
				mapa = atoi(FieldNum[36][1]);
				click = atoi(FieldNum[36][0]);
				lvl = atoi(FieldNum[36][2]);
			}
			if (isMousePos(cd, basey + 60, size4[37].cx + 13, 15)) {
				mapa = atoi(FieldNum[37][1]);
				click = atoi(FieldNum[37][0]);
				lvl = atoi(FieldNum[37][2]);
			}
		}

		sITEMINFO* lpItemInfo = FindItemFromCode(sinBI1 | sin08);
		//sITEMINFO* lpItemInfo2 = FindItemFromCode(sinBI1 | sin93);

		if (isMousePos(smScreenWidth / 2 + 35, 450, 182, 48)) {
			/*	if (!lpItemInfo && !lpItemInfo2)
					return FALSE;
				else*/
			if (lpCurPlayer->smCharInfo.Level < lvl) {
				char buff[255] = { 0 };
				wsprintfA(buff, "Level Necess�rio: %d", lvl);
				cMessageBox.ShowMessage(buff);
				return FALSE;
			}
			else if (StageField[lpCurPlayer->OnStageField]->FieldCode == 16 || StageField[lpCurPlayer->OnStageField]->FieldCode == 30) {
				cMessageBox.ShowMessage(92);
				return FALSE;
			}
			WarpField2(mapa);
			tcoreClose();
			StopTcore = FALSE;
			//sinThrowItemToFeild(&cInvenTory.InvenItem[chaPremiumitem.TelePortCore.ItemIndex]);
		}
	}
	return TRUE;
}