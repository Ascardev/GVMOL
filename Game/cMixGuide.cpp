#include "sinbaram\\sinlinkheader.h"
#include "FontImage.h"
#include "cMixGuide.h"

bool TextureBox1 = false;
int bTexture;
int WinX = 40, WinY = 70;
char szBuff[256] = { 0 };

void cMixGuide::DrawImage(int Mat, int x, int y, int w, int h)
{
	HoDrawTexImage(Mat, x, y, w, h, w, h, 255);
}

bool cMixGuide::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void cMixGuide::Init()
{
	cImages[0] = CreateTextureMaterial("game\\images\\mix\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[1] = CreateTextureMaterial("game\\images\\mix\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	cImages[2] = CreateTextureMaterial("game\\images\\mix\\combobox\\drop.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[3] = CreateTextureMaterial("game\\images\\mix\\combobox\\dropon.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[4] = CreateTextureMaterial("game\\images\\mix\\combobox\\drop_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[5] = CreateTextureMaterial("game\\images\\mix\\combobox\\dropdown.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[6] = CreateTextureMaterial("game\\images\\mix\\combobox\\dropbg.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	//sheltons

	cImages[12] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Transparo.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[7] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Devine.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[8] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Celesto.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[13] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Mirage.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[14] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Inferna.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[15] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\enigma.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[10] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Murki.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[11] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Bellum.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[16] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Ordo.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	cImages[17] = CreateTextureMaterial("game\\images\\mix\\Sheltoms\\Gemma.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);

	cImages[9] = CreateTextureMaterial("game\\images\\mix\\Mix.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cMixGuide::Draw()
{
	if (cOpen)
	{
		DrawImage(cImages[0], WinX, WinY, 610, 432);
		//DrawImage(cImages[1], WinX + 337, WinY + 511, 88, 35);
		DrawImage(cImages[1], WinX + 250, WinY + 390, 88, 35);
		DrawImage(cImages[9], WinX + 230, WinY + 10, 125, 29);

		SetTextColor(0, RGB(220, 220, 220));
		DescriptionsMix();

		if (bTexture == 0)
			Weapons();
		else if (bTexture == 1)
			ArmorsRobe();
		else if (bTexture == 2)
			Bracelet();
		else if (bTexture == 3)
			Gauntlet();
		else if (bTexture == 4)
			Boot();
		else if (bTexture == 5)
			ShieldOrb();
		else if (bTexture == 6)
			Ring();
		else if (bTexture == 7)
			Amulet();
		else if (bTexture == 8)
			Sheltom();

		DrawComboBox();
	}
}

void cMixGuide::Button()
{
	if (cOpen)
	{
		if (MouseAction(WinX + 250, WinY + 390, 88, 35))
		{
			Close();
		}

		if (TextureBox1)
		{
			TextureBox1 = false;
			if (MouseAction(WinX + 430, WinY + 66, 86, 24))
				bTexture = 0;
			if (MouseAction(WinX + 430, WinY + 88, 86, 24))
				bTexture = 1;
			if (MouseAction(WinX + 430, WinY + 112, 86, 24))
				bTexture = 2;
			if (MouseAction(WinX + 430, WinY + 136, 86, 25))
				bTexture = 3;
			if (MouseAction(WinX + 430, WinY + 160, 86, 25))
				bTexture = 4;
			if (MouseAction(WinX + 430, WinY + 184, 86, 25))
				bTexture = 5;
			if (MouseAction(WinX + 430, WinY + 208, 86, 25))
				bTexture = 6;
			if (MouseAction(WinX + 430, WinY + 232, 86, 25))
				bTexture = 7;
			if (MouseAction(WinX + 430, WinY + 256, 86, 25))
				bTexture = 8;
		}
		else
			if (MouseAction(WinX + 450, WinY + 40, 86, 26))
				TextureBox1 = true;
	}
}

void cMixGuide::DescriptionsMix()
{
	//FontType = 2;
	FontType = 1;
	wsprintf(szBuff, "Nome Mix");
	//GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
	DrawFontTextNew(WinX + 23, WinY + 45, szBuff, D3DCOLOR_RGBA(255, 255, 255, 180), 1);

	wsprintf(szBuff, "Sheltoms");
	//GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
	DrawFontTextNew(WinX + 120, WinY + 45, szBuff, D3DCOLOR_RGBA(255, 255, 255, 180), 1);

	wsprintf(szBuff, "Descrição");
	//GetFontTextExtentPoint(szBuff, strlen(szBuff), &size);
	DrawFontTextNew(WinX + 235, WinY + 45, szBuff, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	FontType = 0;
}

void cMixGuide::DrawComboBox()
{
	SetTextColor(0, RGB(255, 255, 255));
	if (TextureBox1)
	{
		DrawImage(cImages[4], (WinX + 430), (WinY + 40), 110, 26); // 287 = 40
		DrawImage(cImages[5], (WinX + 430), (WinY + 66), 110, 26); // 313 == 66
		DrawImage(cImages[5], (WinX + 430), (WinY + 88), 110, 26); // 337 == 88
		DrawImage(cImages[5], (WinX + 430), (WinY + 112), 110, 26); // 361 == 112
		DrawImage(cImages[5], (WinX + 430), (WinY + 136), 110, 26); // 385 == 136
		DrawImage(cImages[5], (WinX + 430), (WinY + 160), 110, 26);
		DrawImage(cImages[5], (WinX + 430), (WinY + 184), 110, 26);
		DrawImage(cImages[5], (WinX + 430), (WinY + 208), 110, 26);
		DrawImage(cImages[5], (WinX + 430), (WinY + 232), 110, 26);
		DrawImage(cImages[5], (WinX + 430), (WinY + 256), 110, 26);

		if (MouseAction(WinX + 430, WinY + 64, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 64), 110, 26);

		if (MouseAction(WinX + 430, WinY + 88, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 88), 110, 26);

		if (MouseAction(WinX + 430, WinY + 112, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 112), 110, 26);

		if (MouseAction(WinX + 430, WinY + 136, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 136), 10, 26);

		if (MouseAction(WinX + 430, WinY + 160, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 160), 10, 26);

		if (MouseAction(WinX + 430, WinY + 184, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 184), 10, 26);

		if (MouseAction(WinX + 430, WinY + 208, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 208), 10, 26);

		if (MouseAction(WinX + 430, WinY + 232, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 232), 10, 26);

		if (MouseAction(WinX + 430, WinY + 256, 110, 26))
			DrawImage(cImages[6], (WinX + 430), (WinY + 256), 10, 26);

		dsTextLineOut(WinX + 458, WinY + 71, "Weapon", 8);
		dsTextLineOut(WinX + 458, WinY + 93, "Armor/Robes", 11);
		dsTextLineOut(WinX + 458, WinY + 117, "Bracelets", 9);
		dsTextLineOut(WinX + 458, WinY + 141, "Gloves", 6);
		dsTextLineOut(WinX + 458, WinY + 165, "Boots", 5);
		dsTextLineOut(WinX + 458, WinY + 189, "Shield/Orb", 11);
		dsTextLineOut(WinX + 458, WinY + 213, "Rings", 5);
		dsTextLineOut(WinX + 458, WinY + 237, "Amulet", 7);
		dsTextLineOut(WinX + 458, WinY + 261, "Sheltom", 7);
	}
	else
	{
		if (MouseAction(WinX + 430, WinY + 40, 110, 26))
			DrawImage(cImages[3], (WinX + 430), (WinY + 40), 110, 26);
		else
			DrawImage(cImages[2], (WinX + 430), (WinY + 40), 110, 26);
	}

	if (bTexture == 0)
		dsTextLineOut(WinX + 458, WinY + 45, "Weapon", 8);
	else if (bTexture == 1)
		dsTextLineOut(WinX + 438, WinY + 45, "Armor/Robes", 11);
	else if (bTexture == 2)
		dsTextLineOut(WinX + 458, WinY + 45, "Bracelets", 9);
	else if (bTexture == 3)
		dsTextLineOut(WinX + 458, WinY + 45, "Gloves", 6);
	else if (bTexture == 4)
		dsTextLineOut(WinX + 458, WinY + 45, "Boots", 5);
	else if (bTexture == 5)
		dsTextLineOut(WinX + 453, WinY + 45, "Shield/Orb", 11);
	else if (bTexture == 6)
		dsTextLineOut(WinX + 458, WinY + 45, "Rings", 5);
	else if (bTexture == 7)
		dsTextLineOut(WinX + 458, WinY + 45, "Amulet", 7);
	else if (bTexture == 8)
		dsTextLineOut(WinX + 458, WinY + 45, "Sheltom", 7);
}

void cMixGuide::Weapons()
{
	wsprintf(szBuff, "Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "ATK Power(+6 Min +8 Max)  CRIT(+2%)  HP(+30)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "ATK Power(+8 Min +10 Max)  CRIT(+2%)  HP(+40)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}

void cMixGuide::ArmorsRobe()
{
	wsprintf(szBuff, "Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "DEF(+350)  ABS(+6.0) MP(+110)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	////Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "DEF(+450)  ABS(+8.0) MP(+150)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}

void cMixGuide::Bracelet()
{
	wsprintf(szBuff, "Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "DEF(+95)  TAXA(+110)  RES(+55)  MP(+40)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "DEF(+130)  TAXA(+150)  RES(+75)  MP(+55)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}

void cMixGuide::Gauntlet()
{
	wsprintf(szBuff, "Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "DEF(+150)  ABS(+5.0)  MP(+70)  RES(+120)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "DEF(+200)  ABS(+7.0)  MP(+90)  RES(+160)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}

void cMixGuide::Boot()
{
	wsprintf(szBuff, "Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "HP(+80)  MP(+50)  SPEED(+3.2)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "HP(+120)  MP(+70)  SPEED(+5.0)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}

void cMixGuide::ShieldOrb()
{
	wsprintf(szBuff, "Escudo Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 135, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 160), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 205), (WinY + 85), 16, 16);

	wsprintf(szBuff, "DEF(+120)  ABS(+1.0)  Block(+3.0)  HP(+10)  MP(+10)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Escudo Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "DEF(+180)  ABS(+2.5)  Block(+5.0)  HP(+100)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, "Orb Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 155, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 135, WinY + 155, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 160), (WinY + 155), 16, 16);
	DrawImage(cImages[13], (WinX + 205), (WinY + 155), 16, 16);

	wsprintf(szBuff, "DEF(+170)  ABS(+6.0)  Block(+2.0)  HP(+45)");
	dsTextLineOut(WinX + 250, WinY + 155, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Orb Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 190, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "DEF(+270)  ABS(+8.0)  Block(+5.0)  HP(+200)");
	dsTextLineOut(WinX + 250, WinY + 190, szBuff, strlen(szBuff));
}

void cMixGuide::Ring()
{
	wsprintf(szBuff, "Mix Mirage");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "HP(+40)  RES(+40)  MP(+40)  RES Reg(+3.8)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "HP(+80)  RES(+80)  MP(+80)  RES Reg(+4.3)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}

void cMixGuide::Amulet()
{
	wsprintf(szBuff, "Mix Mirage ");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "RES(+40)  MP(+40)  RES Reg(+3.8)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "MP(+120)  HPReg(+5.5)  MPReg(+4.1)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}

void cMixGuide::Sheltom()
{
	wsprintf(szBuff, "Mix Mirage ");
	DrawFontTextNew(WinX + 23, WinY + 85, szBuff, D3DCOLOR_RGBA(192, 192, 192, 180), 1);

	wsprintf(szBuff, " 2x          10x          ");
	dsTextLineOut(WinX + 120, WinY + 85, szBuff, strlen(szBuff));
	DrawImage(cImages[8], (WinX + 143), (WinY + 85), 16, 16);
	DrawImage(cImages[13], (WinX + 187), (WinY + 85), 16, 16);

	wsprintf(szBuff, "ATKPOWER(+1 Min +1 Max)");
	dsTextLineOut(WinX + 250, WinY + 85, szBuff, strlen(szBuff));

	//Mix Celestro
	wsprintf(szBuff, "Mix Bellum");
	dsTextLineOut(WinX + 23, WinY + 120, szBuff, strlen(szBuff));

	wsprintf(szBuff, " 3x          4x          5x");
	dsTextLineOut(WinX + 120, WinY + 120, szBuff, strlen(szBuff));
	DrawImage(cImages[14], (WinX + 143), (WinY + 120), 16, 16);
	DrawImage(cImages[15], (WinX + 187), (WinY + 120), 16, 16);
	DrawImage(cImages[11], (WinX + 231), (WinY + 120), 16, 16);

	wsprintf(szBuff, "ATKPOWER(+2 Min +3 Max)");
	dsTextLineOut(WinX + 250, WinY + 120, szBuff, strlen(szBuff));
}