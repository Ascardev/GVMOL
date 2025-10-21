#include "sinbaram//sinLinkHeader.h"

SkinView::SkinView()
{
}

void SkinView::Init()
{
	m_ViewType = TYPE_WEAPON;
	m_SubViewType = 0;
	m_Open = FALSE;
	m_bMouseButtonFlag = FALSE;
	Lx = 0;
	Rx = 0;
	ImgX = 0;

	m_iSDA3DA4 = 0;

	szCurrenFilePath[255] = { 0 };

	apply = LoadDibSurfaceOffscreen("game\\images\\Skin\\apply.png");
	apply_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\apply_.png");

	window = LoadDibSurfaceOffscreen("game\\images\\Skin\\window.png");
	line = LoadDibSurfaceOffscreen("game\\images\\Skin\\line.png");
	close = LoadDibSurfaceOffscreen("game\\images\\Skin\\close.png");
	close_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\close_.png");
	w = LoadDibSurfaceOffscreen("game\\images\\Skin\\w.png");
	w_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\w_.png");
	R_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\R_.png");
	R = LoadDibSurfaceOffscreen("game\\images\\Skin\\R.png");
	L_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\L_.png");
	L = LoadDibSurfaceOffscreen("game\\images\\Skin\\L.png");
	d_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\d_.png");
	d = LoadDibSurfaceOffscreen("game\\images\\Skin\\d.png");
	A_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\A_.png");
	A = LoadDibSurfaceOffscreen("game\\images\\Skin\\A.png");

	bow = LoadDibSurfaceOffscreen("game\\images\\Skin\\\Sub\\Bow.png");
	axes = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\Axes.png");
	claws = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\claws.png");
	daggers = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\daggers.png");
	hammers = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\hammers.png");
	javelins = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\javelins.png");
	manopla = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\manopla.png");
	phantoms = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\phantoms.png");
	scythes = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\scythes.png");
	swords = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\swords.png");
	wands = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\wands.png");

	bow_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\Bow_.png");
	axes_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\Axes_.png");
	claws_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\claws_.png");
	daggers_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\daggers_.png");
	hammers_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\hammers_.png");
	javelins_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\javelins_.png");
	manopla_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\manopla_.png");
	phantoms_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\phantoms_.png");
	scythes_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\scythes_.png");
	swords_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\swords_.png");
	wands_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\wands_.png");

	armors = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\armors.png");
	robes = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\robes.png");
	shields = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\shields.png");

	armors_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\armors_.png");
	robes_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\robes_.png");
	shields_ = LoadDibSurfaceOffscreen("game\\images\\Skin\\Sub\\shields_.png");

	m_LastCurrentView = 0;
	m_CurrentView = 1;
	m_MaxView = 50;

	m_ChangeSkin = 0;

	LoadCurrentIMG();
}

BOOL SkinView::IsMousePos(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

SkinView::~SkinView()
{
}

void SkinView::Main()
{
	if (m_Open)
	{
		if (MouseButton[0] == FALSE)
		{
			m_bMouseButtonFlag = FALSE;
		}
		if (MouseButton[0] && m_bMouseButtonFlag == FALSE)
		{
			MouseButtonUpEvent = TRUE;
			m_bMouseButtonFlag = TRUE;

			if (IsMousePos(140, 275, 42, 85))
			{
				m_ViewType = TYPE_WEAPON;

				SetSubViewTypeClass();
				m_LastCurrentView = 2;
				m_CurrentView = 1;
				LoadCurrentIMG();
			}
			else if (IsMousePos(210, 280, 66, 75))
			{
				m_ViewType = TYPE_ARMOR;
				m_MinView = 20;
				m_MaxView = 40;

				m_iSDA3DA4 = 0;
				m_SubViewType = TYPE_ARMOR_B;
				m_LastCurrentView = 3;
				m_CurrentView = 2;
				LoadCurrentIMG();
			}
			else if (IsMousePos(300, 275, 44, 84))
			{
				m_ViewType = TYPE_SHIELD;
				m_MinView = 18;
				m_MaxView = 38;

				m_LastCurrentView = 2;
				m_CurrentView = 1;
				LoadCurrentIMG();
			}

			if (m_ViewType == TYPE_WEAPON)
			{
				if (IsMousePos(15 + 95, 65, 37, 14))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ARCHER || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
					{
						m_SubViewType = TYPE_ARCO;
						m_MinView = 20;
						m_MaxView = 41;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(15 + 137, 65, 76, 18))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN)
					{
						m_SubViewType = TYPE_FOICE;
						m_MinView = 19;
						m_MaxView = 40;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(15 + 218, 65, 67, 14))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ATALANTA || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
					{
						m_SubViewType = TYPE_LANCA;
						m_MinView = 19;
						m_MaxView = 40;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(15 + 290, 65, 62, 15))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PIKEMAN || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_FIGHTER || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_KNIGHT || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
					{
						m_SubViewType = TYPE_ESPADA;
						m_MinView = 19;
						m_MaxView = 43;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(18 + 95, 85, 49, 15))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_MARTIAL && lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_ASSASSINE && lpCurPlayer->smCharInfo.JOB_CODE != JOBCODE_SHAMAN)
					{
						m_SubViewType = TYPE_GARRA;
						m_MinView = 18;
						m_MaxView = 39;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(18 + 149, 86, 78, 14))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN)
					{
						m_SubViewType = TYPE_PORRETE;
						m_MinView = 18;
						m_MaxView = 41;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(18 + 232, 86, 41, 14))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MECHANICIAN || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_FIGHTER)
					{
						m_SubViewType = TYPE_AXE;
						m_MinView = 18;
						m_MaxView = 40;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(18 + 278, 86, 68, 17))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ASSASSINE)
					{
						m_SubViewType = TYPE_ADAGA;
						m_MinView = 19;
						m_MaxView = 39;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(40 + 95, 105, 82, 14))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_SHAMAN)
					{
						m_SubViewType = TYPE_FANTASMA;
						m_MinView = 19;
						m_MaxView = 39;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(40 + 182, 105, 47, 14))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
					{
						m_SubViewType = TYPE_CAJADO;
						m_MinView = 18;
						m_MaxView = 41;

						m_LastCurrentView = 2;
						m_CurrentView = 1;
						LoadCurrentIMG();
					}
				}
				else if (IsMousePos(40 + 234, 105, 69, 17))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MARTIAL)
					{
						m_SubViewType = TYPE_MANOPLA;

						m_MinView = 19;
						m_MaxView = 39;

						m_LastCurrentView = 2;
						m_CurrentView = 20;
						LoadCurrentIMG();
					}
				}
			}

			if (m_ViewType == TYPE_ARMOR)
			{
				if (IsMousePos(85 + 95, 85, 61, 14))
				{
					m_SubViewType = TYPE_ARMOR_B;
					m_LastCurrentView = 3;
					m_CurrentView = 2;
					m_iSDA3DA4 = 0;
					LoadCurrentIMG();
				}

				if (IsMousePos(85 + 161, 85, 52, 14))
				{
					if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_SHAMAN || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS)
					{
						m_SubViewType = TYPE_ROBE_B;

						m_LastCurrentView = 3;
						m_CurrentView = 2;
						m_iSDA3DA4 = 0;
						LoadCurrentIMG();
					}
				}
			}

			if (IsMousePos(Lx + 185, 185, 16, 20))
			{
				m_CurrentView--;
				if (m_CurrentView <= m_MinView)
					m_CurrentView = m_MinView;

				if (m_CurrentView <= 29)
				{
					m_iSDA3DA4 = 0;
				}
				else
				{
					m_iSDA3DA4 = 1;
				}

				LoadCurrentIMG();
			}

			if (IsMousePos(Lx + 185 + 100, 185, 16, 20))
			{
				m_CurrentView++;
				if (m_CurrentView > m_MaxView)
					m_CurrentView = m_MaxView;

				if (m_ViewType == TYPE_ARMOR)
				{
					if (m_CurrentView >= 30)
					{
						m_iSDA3DA4 = 1;
					}
					else
					{
						m_iSDA3DA4 = 0;
					}
				}

				LoadCurrentIMG();
			}

			if (IsMousePos(204, 244, 80, 21))
			{
				ApplySkin();
			}

			if (IsMousePos(204, 378, 80, 21))
			{
				m_Open = 0;
			}
		}
	}
}

void SkinView::ApplySkin()
{
	m_ChangeSkin = 1;
	if (m_ViewType == TYPE_ARMOR)
	{
		DWORD CODE = sinDA1;

		if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_SHAMAN || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_PRIESTESS || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MAGICIAN)
		{
			CODE = sinDA2;

			if (m_CurrentView >= 30)
				CODE = sinDA4;
		}
		else
		{
			if (m_CurrentView >= 30)
				CODE = sinDA3;
		}

		if (m_iSDA3DA4)
			SetPlayerArmor(m_CurrentView - 28, CODE);
		else
			SetPlayerArmor(m_CurrentView, CODE);
	}
	else if (m_ViewType == TYPE_WEAPON)
	{
		DWORD SinCode = 0x00000100 * m_CurrentView;
		DWORD  Code2 = sinWP1;

		int Dual = 0;
		switch (m_SubViewType)
		{
		case TYPE_ARCO:
			Code2 = sinWS1;
			break;
		case TYPE_FOICE:
			Code2 = sinWP1;
			break;
		case TYPE_LANCA:
			Code2 = sinWT1;
			break;
		case TYPE_ESPADA:
			Code2 = sinWS2;
			break;
		case TYPE_GARRA:
			Code2 = sinWC1;
			break;
		case TYPE_PORRETE:
			Code2 = sinWH1;
			break;
		case TYPE_AXE:
			Code2 = sinWA1;
			break;
		case TYPE_ADAGA:
			Code2 = sinWD1;
			break;
		case TYPE_CAJADO:
			Code2 = sinWM1;
			break;
		case TYPE_FANTASMA:
			Code2 = sinWN1;
			break;
		case TYPE_MANOPLA:
			Code2 = sinWV1;
			break;
		}

		if (SinCode > 0x00001900)
			SinCode += 0x1000;

		if (lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_ASSASSINE || lpCurPlayer->smCharInfo.JOB_CODE == JOBCODE_MARTIAL && Code2 == sinWV1)
			Dual = 1;

		if (Dual)
		{
			lpCurPlayer->SetTool(Code2 | SinCode, hvPOSI_LHAND);
			lpCurPlayer->SetTool(Code2 | SinCode, hvPOSI_RHAND);
		}
		else
		{
			lpCurPlayer->SetTool(0, hvPOSI_LHAND);
			lpCurPlayer->SetTool(Code2 | SinCode, hvPOSI_RHAND);
		}
	}
	else if (m_ViewType == TYPE_SHIELD)
	{
		DWORD SinCode = 0x00000100 * m_CurrentView;
		DWORD  Code2 = sinDS1;

		if (SinCode > 0x00001900)
			SinCode += 0x1000;
		lpCurPlayer->SetTool(0, hvPOSI_RHAND);
		lpCurPlayer->SetTool(Code2 | SinCode, hvPOSI_LHAND);
	}
}

void SkinView::Draw()
{
	if (m_Open)
	{
		DrawSprite(80, 50, window, 0, 0, 316, 362);

		if (IsMousePos(204, 378, 80, 21))
			DrawSprite(204, 378, close_, 0, 0, 80, 21);
		else
			DrawSprite(204, 378, close, 0, 0, 80, 21);

		DrawSprite(95, 130, line, 0, 0, 287, 1);

		if (m_ViewType == TYPE_WEAPON)
		{
			DrawSprite(15 + 95, 65, bow, 0, 0, 37, 14);
			if (IsMousePos(15 + 95, 65, 37, 14))
				DrawSprite(15 + 95, 65, bow_, 0, 0, 37, 14);

			DrawSprite(15 + 137, 65, scythes, 0, 0, 76, 18);
			if (IsMousePos(15 + 137, 65, 76, 18))
				DrawSprite(15 + 137, 65, scythes_, 0, 0, 76, 18);

			DrawSprite(15 + 218, 66, javelins, 0, 0, 67, 14);
			if (IsMousePos(15 + 218, 65, 67, 14))
				DrawSprite(15 + 218, 66, javelins_, 0, 0, 67, 14);

			DrawSprite(15 + 290, 65, swords, 0, 0, 62, 15);
			if (IsMousePos(15 + 290, 65, 62, 15))
				DrawSprite(15 + 290, 65, swords_, 0, 0, 62, 15);

			DrawSprite(18 + 95, 85, claws, 0, 0, 49, 15);
			if (IsMousePos(18 + 95, 85, 49, 15))
				DrawSprite(18 + 95, 85, claws_, 0, 0, 49, 15);

			DrawSprite(18 + 149, 86, hammers, 0, 0, 78, 14);
			if (IsMousePos(18 + 149, 86, 78, 14))
				DrawSprite(18 + 149, 86, hammers_, 0, 0, 78, 14);

			DrawSprite(18 + 232, 86, axes, 0, 0, 41, 14);
			if (IsMousePos(18 + 232, 86, 41, 14))
				DrawSprite(18 + 232, 86, axes_, 0, 0, 41, 14);

			DrawSprite(18 + 278, 86, daggers, 0, 0, 68, 17);
			if (IsMousePos(18 + 278, 86, 68, 17))
				DrawSprite(18 + 278, 86, daggers_, 0, 0, 68, 17);

			DrawSprite(40 + 95, 105, phantoms, 0, 0, 82, 14);
			if (IsMousePos(40 + 95, 105, 82, 14))
				DrawSprite(40 + 95, 105, phantoms_, 0, 0, 82, 14);

			DrawSprite(40 + 182, 105, wands, 0, 0, 47, 14);
			if (IsMousePos(40 + 182, 105, 47, 14))
				DrawSprite(40 + 182, 105, wands_, 0, 0, 47, 14);

			DrawSprite(40 + 234, 105, manopla, 0, 0, 69, 17);
			if (IsMousePos(40 + 234, 105, 69, 17))
				DrawSprite(40 + 234, 105, manopla_, 0, 0, 69, 17);
		}

		if (m_ViewType == TYPE_ARMOR)
		{
			DrawSprite(85 + 95, 85, armors, 0, 0, 61, 14);
			if (IsMousePos(85 + 95, 85, 61, 14))
				DrawSprite(85 + 95, 85, armors_, 0, 0, 61, 14);

			DrawSprite(85 + 161, 85, robes, 0, 0, 52, 14);
			if (IsMousePos(85 + 161, 85, 52, 14))
				DrawSprite(85 + 161, 85, robes_, 0, 0, 52, 14);
		}

		if (m_ViewType == TYPE_SHIELD)
		{
			DrawSprite(120 + 90, 85, shields, 0, 0, 61, 15);
			if (IsMousePos(120 + 90, 85, 61, 15))
				DrawSprite(120 + 90, 85, shields_, 0, 0, 61, 15);
		}

		int CurDraw = 0;

		char SkinNameArco[22][50]
		{
			"80C",
			"80D",
			"80E",
			"100",
			"102",
			"105",
			"108",
			 "108B",
				"115",
				 "120",
				  "130",
				  "130b",
				   "140",
					"145",
					 "Custom",
					  "Imperatriz",
					   "Prime",
						"Fantastic",
						 "Fogo",
						 "Real",
						  "Babel",
						  "Valiant",
		};
		SetFontTextColor(RGB(255, 255, 180));

		char SkinNameSHIELD[22][50]
		{
			"80C",
			"80D",
			"QUEST",
			"100",
			"102",
			"105",
			"108",
			 "115",
				"120",
				 "130",
				   "140",
					"145",
					 "Custom",
						"Anjo",
					  "Imperatriz",
					   "Prime",
						"Fantastic",
						 "Fogo",
						 "Real",
						 "Babel",
						 "Valiant",
		};
		SetFontTextColor(RGB(255, 255, 180));

		char SkinNameArmor[22][50]
		{
			"80C",
			"80D",
			"QUEST",
			"100",
			"102",
			"105",
			 "Prime",
			"108",
			 "115",
				"120",
				 "130b",
				   "140",
					"145",
					 "Custom",
					  "Imperatriz",
					   "Prime",
						"Fantastic",
						 "Fogo",
						 "Real",
						 "Babel",
						 "Valiant",
		};

		char SkinNameManopla[22][50]
		{
			"80C",
			"80D",
			"80E",
			"100",
			"102",
			"105",
			"108",
				"115",
				 "120",
				  "130",
				  "130b",
				   "140",
					"145",
					 "Custom",
					  "Imperatriz",
					   "Prime",
						"Fantastic",
						 "Fogo",
						 "Real",
						 "Babel",
						 "Valiant",
		};
		SetFontTextColor(RGB(255, 255, 180));

		char SkinNameEspada[24][50]
		{
			"80C",
			"80D",
			"Item Toy (Lost)",
			"80E",
			"100",
			"102",
			"105",
			"108",
			"108 1H",
			"108B",
				"115",
				 "120",
				  "130",
				  "130b",
				   "140",
					"145",
					 "Custom",
					  "Imperatriz",
					   "Prime",
						"Fantastic",
						 "Fogo",
						 "Real",
						 "Babel",
						 "Valiant",
		};
		SetFontTextColor(RGB(255, 255, 180));

		char SkinNameAxe[24][50]
		{
			"80C",
			"Item Toy (Lost)",
			"80D",
			"80E",
			"100",
			"102",
			"105",
			"108",
			"108 1H",
			"108B",
				"115",
				 "120",
				  "130",
				  "130b",
				   "140",
					"145",
					 "Custom",
					  "Imperatriz",
					   "Prime",
						"Fantastic",
						 "Fogo",
						 "Real",
						 "Babel",
						 "Valiant",
		};

		char SkinNameStaff[24][50]
		{
			"80C",
			"80D",
			"Off",
			"80E",
			"100",
			"102",
			"105",
			"108",
			 "Off",
				"108Black",
				"115",
				 "120",
				  "130",
				  "130b",
				   "140",
					"145",
					 "Custom",
					  "Imperatriz",
					   "Prime",
						"Fantastic",
						 "Fogo",
						 "Real",
						 "Babel",
						 "Valiant",
		};
		SetFontTextColor(RGB(255, 255, 180));

		/* if (m_ViewType == TYPE_WEAPON)
		 {
			 dsTextLineOut( 242 - (GetTextFullSize(SkinName[m_CurrentView - 19]) / 2), 135, SkinName[m_CurrentView - 19], strlen(SkinName[m_CurrentView - 19]));
		 }*/
		if (m_ViewType == TYPE_ARMOR)
		{
			dsTextLineOut(242 - (GetTextFullSize(SkinNameArmor[m_CurrentView - 20]) / 2), 135, SkinNameArmor[m_CurrentView - 20], strlen(SkinNameArmor[m_CurrentView - 20]));
		}
		else   if (m_ViewType == TYPE_SHIELD)
		{
			dsTextLineOut(242 - (GetTextFullSize(SkinNameSHIELD[m_CurrentView - 18]) / 2), 135, SkinNameSHIELD[m_CurrentView - 18], strlen(SkinNameSHIELD[m_CurrentView - 18]));
		}
		else   if (m_ViewType == TYPE_WEAPON)
		{
			if (m_SubViewType == TYPE_ARCO)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameArco[m_CurrentView - 20]) / 2), 135, SkinNameArco[m_CurrentView - 20], strlen(SkinNameArco[m_CurrentView - 20]));
			else if (m_SubViewType == TYPE_FOICE)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameArco[m_CurrentView - 19]) / 2), 135, SkinNameArco[m_CurrentView - 19], strlen(SkinNameArco[m_CurrentView - 19]));
			else if (m_SubViewType == TYPE_AXE)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameAxe[m_CurrentView - 17]) / 2), 135, SkinNameAxe[m_CurrentView - 17], strlen(SkinNameAxe[m_CurrentView - 17]));
			else if (m_SubViewType == TYPE_MANOPLA)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameManopla[m_CurrentView - 19]) / 2), 135, SkinNameManopla[m_CurrentView - 19], strlen(SkinNameManopla[m_CurrentView - 19]));
			else if (m_SubViewType == TYPE_LANCA)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameArco[m_CurrentView - 19]) / 2), 135, SkinNameArco[m_CurrentView - 19], strlen(SkinNameArco[m_CurrentView - 19]));
			else if (m_SubViewType == TYPE_CAJADO)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameStaff[m_CurrentView - 18]) / 2), 135, SkinNameStaff[m_CurrentView - 18], strlen(SkinNameStaff[m_CurrentView - 18]));
			else if (m_SubViewType == TYPE_PORRETE)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameEspada[m_CurrentView - 18]) / 2), 135, SkinNameEspada[m_CurrentView - 18], strlen(SkinNameEspada[m_CurrentView - 18]));
			else if (m_SubViewType == TYPE_ADAGA)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameManopla[m_CurrentView - 19]) / 2), 135, SkinNameManopla[m_CurrentView - 19], strlen(SkinNameManopla[m_CurrentView - 19]));
			else if (m_SubViewType == TYPE_GARRA)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameArco[m_CurrentView - 18]) / 2), 135, SkinNameArco[m_CurrentView - 18], strlen(SkinNameArco[m_CurrentView - 18]));
			else if (m_SubViewType == TYPE_FANTASMA)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameManopla[m_CurrentView - 19]) / 2), 135, SkinNameManopla[m_CurrentView - 19], strlen(SkinNameManopla[m_CurrentView - 19]));
			else if (m_SubViewType == TYPE_ESPADA)
				dsTextLineOut(242 - (GetTextFullSize(SkinNameEspada[m_CurrentView - 20]) / 2), 135, SkinNameEspada[m_CurrentView - 20], strlen(SkinNameEspada[m_CurrentView - 20]));
		}

		DrawSprite(80 + 163 - (m_CurrentWidth / 2), 155, CurrentItemDraw, 0, 0, m_CurrentWidth, m_CurrentHeight);

		if (IsMousePos(204, 244, 80, 21))
			DrawSprite(204, 244, apply_, 0, 0, 80, 21);
		else
			DrawSprite(204, 244, apply, 0, 0, 80, 21);

		DrawSprite(Lx + 185, 185, L_, 0, 0, 16, 20);
		if (IsMousePos(Lx + 185, 185, 16, 20))
			DrawSprite(Lx + 185, 185, L, 0, 0, 16, 20);

		DrawSprite(Rx + 185 + 100, 185, R_, 0, 0, 16, 20);
		if (IsMousePos(Lx + 185 + 100, 185, 16, 20))
			DrawSprite(Lx + 185 + 100, 185, R, 0, 0, 16, 20);

		DrawSprite(95, 270, line, 0, 0, 287, 1);

		DrawSprite(140, 275, w_, 0, 0, 42, 85);
		if (IsMousePos(140, 275, 42, 85) || m_ViewType == TYPE_WEAPON)
			DrawSprite(140, 275, w, 0, 0, 42, 85);

		DrawSprite(210, 280, A_, 0, 0, 66, 75);
		if (IsMousePos(210, 280, 66, 75) || m_ViewType == TYPE_ARMOR)
			DrawSprite(210, 280, A, 0, 0, 66, 75);

		DrawSprite(300, 275, d_, 0, 0, 44, 84);
		if (IsMousePos(300, 275, 44, 84) || m_ViewType == TYPE_SHIELD)
			DrawSprite(300, 275, d, 0, 0, 44, 84);
	}
}

void SkinView::SetSubViewTypeClass()
{
	switch (lpCurPlayer->smCharInfo.JOB_CODE)
	{
	case JOBCODE_PIKEMAN:
		m_SubViewType = TYPE_FOICE;
		m_MinView = 19;
		m_MaxView = 40;
		break;
	case JOBCODE_ARCHER:
		m_SubViewType = TYPE_ARCO;
		m_MinView = 20;
		m_MaxView = 41;
		break;
	case JOBCODE_FIGHTER:
		m_SubViewType = TYPE_AXE;
		m_MinView = 17;
		m_MaxView = 40;
		break;
	case JOBCODE_MARTIAL:
		m_SubViewType = TYPE_MANOPLA;
		m_MinView = 19;
		m_MaxView = 39;
		break;
	case JOBCODE_ATALANTA:
		m_SubViewType = TYPE_LANCA;
		m_MinView = 19;
		m_MaxView = 40;
		break;
	case JOBCODE_MAGICIAN:
		m_SubViewType = TYPE_CAJADO;
		m_MinView = 18;
		m_MaxView = 41;
		break;
	case JOBCODE_MECHANICIAN:
		m_SubViewType = TYPE_PORRETE;
		m_MinView = 18;
		m_MaxView = 40;
		break;
	case JOBCODE_PRIESTESS:
		m_SubViewType = TYPE_CAJADO;
		m_MinView = 18;
		m_MaxView = 41;
		break;
	case JOBCODE_ASSASSINE:
		m_SubViewType = TYPE_ADAGA;
		m_MinView = 19;
		m_MaxView = 38;
		break;
	case JOBCODE_SHAMAN:
		m_SubViewType = TYPE_FANTASMA;
		m_MinView = 19;
		m_MaxView = 39;
		break;
	case JOBCODE_KNIGHT:
		m_SubViewType = TYPE_ESPADA;
		m_MinView = 20;
		m_MaxView = 43;
		break;
	}
}
void SkinView::OpenNPC()
{
	m_ViewType = TYPE_WEAPON;
	SetSubViewTypeClass();
	m_LastCurrentView = 2;
	m_CurrentView = 1;
	LoadCurrentIMG();
	m_Open = true;
}

void SkinView::LoadCurrentIMG()
{
	if (m_CurrentView < m_MinView)
		m_CurrentView = m_MinView;
	if (m_CurrentView > m_MaxView)
		m_CurrentView = m_MaxView;

	if (m_ViewType == TYPE_WEAPON)
	{
		sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Weapon\\");

		if (m_CurrentView != m_LastCurrentView)
		{
			switch (m_SubViewType)
			{
			case TYPE_ARCO:
				lstrcat(szCurrenFilePath, "itws1");
				break;
			case TYPE_FOICE:
				lstrcat(szCurrenFilePath, "itwp1");
				break;
			case TYPE_LANCA:
				lstrcat(szCurrenFilePath, "itwt1");
				break;
			case TYPE_ESPADA:
				lstrcat(szCurrenFilePath, "itws2");
				break;
			case TYPE_GARRA:
				lstrcat(szCurrenFilePath, "itwc1");
				break;
			case TYPE_PORRETE:
				lstrcat(szCurrenFilePath, "itwh1");
				break;
			case TYPE_AXE:
				lstrcat(szCurrenFilePath, "itwa1");
				break;
			case TYPE_ADAGA:
				lstrcat(szCurrenFilePath, "itwd1");
				break;
			case TYPE_FANTASMA:
				lstrcat(szCurrenFilePath, "itwn1");
				break;
			case TYPE_CAJADO:
				lstrcat(szCurrenFilePath, "itwm1");
				break;
			case TYPE_MANOPLA:
				lstrcat(szCurrenFilePath, "itwv1");
				break;
			}

			char Code[50] = { 0 };

			if (m_CurrentView <= 9)
			{
				sprintf_s(Code, "0%d.bmp", m_CurrentView);
			}
			else
			{
				sprintf_s(Code, "%d.bmp", m_CurrentView);
			}

			lstrcat(szCurrenFilePath, Code);

			GetInfoAndLoadCurrentImg(szCurrenFilePath);
			m_LastCurrentView = m_CurrentView;
		}
	}
	else if (m_ViewType == TYPE_ARMOR)
	{
		if (m_CurrentView != m_LastCurrentView)
		{
			if (m_iSDA3DA4)
			{
				if (m_SubViewType == TYPE_ARMOR_B)
				{
					if ((m_CurrentView - 28) <= 9)
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA30%d.bmp", m_CurrentView - 28);
					else
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA3%d.bmp", m_CurrentView - 28);
				}
				else
				{
					if ((m_CurrentView - 28) <= 9)
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA40%d.bmp", m_CurrentView - 28);
					else
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA4%d.bmp", m_CurrentView - 28);
				}
			}
			else
			{
				if (m_SubViewType == TYPE_ARMOR_B)
				{
					if (m_CurrentView <= 9)
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA10%d.bmp", m_CurrentView);
					else
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA1%d.bmp", m_CurrentView);
				}
				else
				{
					if (m_CurrentView <= 9)
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA20%d.bmp", m_CurrentView);
					else
						sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDA2%d.bmp", m_CurrentView);
				}
			}

			GetInfoAndLoadCurrentImg(szCurrenFilePath);
			m_LastCurrentView = m_CurrentView;
		}
	}
	else if (m_ViewType == TYPE_SHIELD)
	{
		if (m_CurrentView != m_LastCurrentView)
		{
			if (m_CurrentView <= 9)
				sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDS10%d.bmp", m_CurrentView);
			else
				sprintf_s(szCurrenFilePath, "Image\\sinImage\\Items\\Defense\\itDS1%d.bmp", m_CurrentView);

			GetInfoAndLoadCurrentImg(szCurrenFilePath);
			m_LastCurrentView = m_CurrentView;
		}
	}
}

void SkinView::GetInfoAndLoadCurrentImg(char* img)
{
	FILE* File = nullptr;
	D3DXIMAGE_INFO ImageInfo;
	LONG FileSize = 0;
	char* FileData = nullptr;
	if (fopen_s(&File, img, "rb") == 0)
	{
		fseek(File, 0, SEEK_END);

		FileSize = ftell(File);
		rewind(File);

		FileData = new char[FileSize];
		fread_s(FileData, FileSize, sizeof(char), FileSize, File);
		fclose(File);

		D3DXGetImageInfoFromFileInMemory(FileData, FileSize, &ImageInfo);

		m_CurrentWidth = ImageInfo.Width;
		m_CurrentHeight = ImageInfo.Height;

		CurrentItemDraw = LoadDibSurfaceOffscreen(img);

		delete FileData;
		FileData = 0;
	}
}