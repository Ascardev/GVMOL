#include "sinbaram\sinLinkHeader.h"

struct psITEM {
	int		state;
	int		Serial;

	sITEMINFO	ItemInfo;
};

sDEF_ITEMINFO* DefaultItems;
int	DefaultItemCount;
int SetAgingItem(sITEMINFO* pItem, int AgingNum);
int	rsRegist_ItemSecCode(rsPLAYINFO* lpPlayInfo, TRANS_ITEMINFO* lpTransItemInfo, int NewItem);
int rsPutItem(rsPLAYINFO* lpPlayInfo, DWORD dwItemCode);

void GetItemMixture(int MixNum, psITEM* lpsItem)
{
	int i = MixNum;
	for (int k = 0; k < 12; k++)
	{
		if (sCraftItem_Info[i].PlusElementCode[k])
		{
			switch (sCraftItem_Info[i].PlusElementCode[k])
			{
			case SIN_ADD_FIRE:
				lpsItem->ItemInfo.Resistance[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_FIRE;

				break;
			case SIN_ADD_ICE:
				lpsItem->ItemInfo.Resistance[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ICE;
				break;
			case SIN_ADD_LIGHTNING:
				lpsItem->ItemInfo.Resistance[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIGHTNING;
				break;

			case SIN_ADD_POISON:
				lpsItem->ItemInfo.Resistance[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_POISON;
				break;
			case SIN_ADD_BIO:
				lpsItem->ItemInfo.Resistance[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BIO;
				break;
			case SIN_ADD_CRITICAL:
				lpsItem->ItemInfo.Critical_Hit += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_CRITICAL;
				break;
			case SIN_ADD_ATTACK_RATE:
				lpsItem->ItemInfo.Attack_Rating += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_RATE;
				break;
			case SIN_ADD_DAMAGE_MIN:

				lpsItem->ItemInfo.Damage[0] += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MIN;
				break;

			case SIN_ADD_DAMAGE_MAX:

				lpsItem->ItemInfo.Damage[1] += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MAX;
				break;
			case SIN_ADD_ATTACK_SPEED:

				lpsItem->ItemInfo.Attack_Speed += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_SPEED;
				break;
			case SIN_ADD_ABSORB:

				lpsItem->ItemInfo.fAbsorb += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ABSORB;
				break;
			case SIN_ADD_DEFENCE:

				lpsItem->ItemInfo.Defence += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DEFENCE;
				break;
			case SIN_ADD_BLOCK_RATE:

				lpsItem->ItemInfo.fBlock_Rating += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BLOCK_RATE;
				break;
			case SIN_ADD_MOVE_SPEED:

				lpsItem->ItemInfo.fSpeed += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MOVE_SPEED;
				break;

			case SIN_ADD_LIFE:

				lpsItem->ItemInfo.fIncrease_Life += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFE;
				break;

			case SIN_ADD_MANA:

				lpsItem->ItemInfo.fIncrease_Mana += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANA;
				break;
			case SIN_ADD_STAMINA:

				lpsItem->ItemInfo.fIncrease_Stamina += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINA;
				break;
			case SIN_ADD_LIFEREGEN:

				lpsItem->ItemInfo.fLife_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFEREGEN;
				break;
			case SIN_ADD_MANAREGEN:

				lpsItem->ItemInfo.fMana_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANAREGEN;

				break;
			case SIN_ADD_STAMINAREGEN:

				lpsItem->ItemInfo.fStamina_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINAREGEN;

				break;
			}
		}
	}
}

time_t	tServerTime;

void PlayerMigration::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\hellsgate\\window.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\hellsgate\\btnok.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\hellsgate\\btnok_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\hellsgate\\btnclose_.png", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

char szBufferTextWindow[8092];

void LoadTextFromFile(const char* pszFile)
{
	FILE* pFile = NULL;

	ZeroMemory(szBufferTextWindow, 8092);

	fopen_s(&pFile, pszFile, "rb");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		int iSizeFile = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		if (iSizeFile > 8092)
			iSizeFile = 8092;

		fread(szBufferTextWindow, iSizeFile, 1, pFile);
		fclose(pFile);
	}

	szBufferTextWindow;
}

bool PlayerMigration::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void PlayerMigration::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void PlayerMigration::Draw()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);
		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Migração de Jogadores]", 24, &size);
		dsTextLineOut(WinX + 280 - size.cx / 2, WinY + 40, "[Migração de Jogadores]", 24);
		FontType = 0;
		dsTextLineOut(WinX + 60, WinY + 80, szBufferTextWindow, strlen(szBufferTextWindow));

		if (MouseAction(WinX + 200, WinY + 400, 93, 23))
			DrawImage(Images[2], WinX + 200, WinY + 400, 93, 23);
		else
			DrawImage(Images[1], WinX + 200, WinY + 400, 93, 23);

		if (MouseAction(WinX + 300, WinY + 400, 93, 23))
			DrawImage(Images[4], WinX + 300, WinY + 400, 93, 23);
		else
			DrawImage(Images[3], WinX + 300, WinY + 400, 93, 23);
	}
}

void PlayerMigration::SendRequest()
{
	if (TypeMigration)
	{
		TypeMigration = 0;

		smTRANS_COMMAND ps;
		ps.size = sizeof(smTRANS_COMMAND);
		ps.code = smTRANSCODE_PLAYER_MIGRATION;

		smWINSOCK* lpsmSock;
		lpsmSock = GetAreaServerSock();

		if (lpsmSock)
		{
			lpsmSock->Send((char*)&ps, ps.size, TRUE);
		}
	}
	else
	{
		fOpen = false;
	}
}

void PlayerMigration::Button()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 280;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 561, 438);

		if (MouseAction(WinX + 200, WinY + 400, 80, 21))
			SendRequest();

		if (MouseAction(WinX + 300, WinY + 400, 80, 21))
			fOpen = false;
	}
}

void PlayerMigration::SendItem(rsPLAYINFO* Player, DWORD Code, int Flag, int TypeMigration)
{
	psITEM* lpsItem;
	lpsItem = new psITEM;

	TRANS_ITEMINFO		TransItemInfo;
	ReformItem(&lpsItem->ItemInfo);

	for (int cnt = 0; cnt < DefaultItemCount; cnt++)
	{
		if (DefaultItems[cnt].Item.CODE == Code && !DefaultItems[cnt].Item.UniqueItem)
		{
			if (TypeMigration == 3)
				CreateDefItemPerf(&lpsItem->ItemInfo, &DefaultItems[cnt], Player->smCharInfo.JOB_CODE);
			else if (Flag == 0 || Flag == 1)
				CreateDefItemPerf(&lpsItem->ItemInfo, &DefaultItems[cnt], Player->smCharInfo.JOB_CODE);
			else
				CreateDefItem(&lpsItem->ItemInfo, &DefaultItems[cnt], Player->smCharInfo.JOB_CODE);
		}
	}

	lpsItem->ItemInfo.LinkedItem = 1;

	if (TypeMigration == 1)
	{
		if (Flag == 0 || Flag == 1 || Flag == 2 || Flag == 3)
		{
			//SetAgingItem(&lpsItem->ItemInfo, 22); // Age 22
		}
		if (Flag != 6)
		{
			int MixNum = 0;
			int AgingNum = 18;

			switch (Code & sinITEM_MASK2)
			{
			case sinDA1:
			case sinDA2:
			case sinDA3:
			case sinDA4:
				//MixNum = 11;
				break;

			case sinDS1:
				//MixNum = 13;
				break;

			case sinOA2:
				//MixNum = 15;
				break;

			case sinDG1:
				//MixNum = 16;
				break;

			case sinDB1:
				//MixNum = 17;
				break;
			case sinWA1:
			case sinWC1:
			case sinWH1:
			case sinWM1:
			case sinWP1:
			case sinWS1:
			case sinWS2:
			case sinWT1:

				//MixNum = 9;
				break;

			case sinWD1:
			case sinWN1:
			case sinWV1:
				//MixNum = 10;
				break;
			}
			/*
						int i = MixNum;
						for (int k = 0; k < 12; k++)
						{
							if (sCraftItem_Info[i].PlusElementCode[k])
							{
								switch (sCraftItem_Info[i].PlusElementCode[k])
								{
								case SIN_ADD_FIRE:
									lpsItem->ItemInfo.Resistance[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_FIRE;

									break;
								case SIN_ADD_ICE:
									lpsItem->ItemInfo.Resistance[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ICE;
									break;
								case SIN_ADD_LIGHTNING:
									lpsItem->ItemInfo.Resistance[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIGHTNING;
									break;

								case SIN_ADD_POISON:
									lpsItem->ItemInfo.Resistance[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_POISON;
									break;
								case SIN_ADD_BIO:
									lpsItem->ItemInfo.Resistance[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BIO;
									break;
								case SIN_ADD_CRITICAL:
									lpsItem->ItemInfo.Critical_Hit += (int)sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_CRITICAL;
									break;
								case SIN_ADD_ATTACK_RATE:
									lpsItem->ItemInfo.Attack_Rating += (int)sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_RATE;
									break;
								case SIN_ADD_DAMAGE_MIN:

									lpsItem->ItemInfo.Damage[0] += (int)sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MIN;
									break;

								case SIN_ADD_DAMAGE_MAX:

									lpsItem->ItemInfo.Damage[1] += (int)sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MAX;
									break;
								case SIN_ADD_ATTACK_SPEED:

									lpsItem->ItemInfo.Attack_Speed += (int)sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_SPEED;
									break;
								case SIN_ADD_ABSORB:

									lpsItem->ItemInfo.fAbsorb += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ABSORB;
									break;
								case SIN_ADD_DEFENCE:

									lpsItem->ItemInfo.Defence += (int)sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DEFENCE;
									break;
								case SIN_ADD_BLOCK_RATE:

									lpsItem->ItemInfo.fBlock_Rating += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BLOCK_RATE;
									break;
								case SIN_ADD_MOVE_SPEED:

									lpsItem->ItemInfo.fSpeed += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MOVE_SPEED;
									break;

								case SIN_ADD_LIFE:

									lpsItem->ItemInfo.fIncrease_Life += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFE;
									break;

								case SIN_ADD_MANA:

									lpsItem->ItemInfo.fIncrease_Mana += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANA;
									break;
								case SIN_ADD_STAMINA:

									lpsItem->ItemInfo.fIncrease_Stamina += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINA;
									break;
								case SIN_ADD_LIFEREGEN:

									lpsItem->ItemInfo.fLife_Regen += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFEREGEN;
									break;
								case SIN_ADD_MANAREGEN:

									lpsItem->ItemInfo.fMana_Regen += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANAREGEN;

									break;
								case SIN_ADD_STAMINAREGEN:

									lpsItem->ItemInfo.fStamina_Regen += sCraftItem_Info[i].AddElement[k];

									lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINAREGEN;

									break;
								}
							}
						}*/

						//lpsItem->ItemInfo.ItemAgingNum[0] = 10;
						//lpsItem->ItemInfo.ItemKindCode = ITEM_KIND_CRAFT;
			ReformMixItem(&lpsItem->ItemInfo);
			ReformItem(&lpsItem->ItemInfo);
		}
	}

	if (TypeMigration == 2)
	{
		if (Flag == 0 || Flag == 1 || Flag == 2 || Flag == 3)
		{
			SetAgingItem(&lpsItem->ItemInfo, 10);
		}
		else if (Flag != 6)
		{
			int MixNum = 0;
			int AgingNum = 18;

			switch (Code & sinITEM_MASK2)
			{
			case sinDA1:
			case sinDA2:
			case sinDA3:
			case sinDA4:
				//MixNum = 11;
				break;

			case sinDS1:
				//MixNum = 13;
				break;

			case sinOA2:
				//MixNum = 15;
				break;

			case sinDG1:
				//MixNum = 16;
				break;

			case sinDB1:
				//MixNum = 17;
				break;
			case sinWA1:
			case sinWC1:
			case sinWH1:
			case sinWM1:
			case sinWP1:
			case sinWS1:
			case sinWS2:
			case sinWT1:

				//MixNum = 9;
				break;

			case sinWD1:
			case sinWN1:
			case sinWV1:
				//MixNum = 10;
				break;
			}

			/*int i = MixNum;
			for (int k = 0; k < 12; k++)
			{
				if (sCraftItem_Info[i].PlusElementCode[k])
				{
					switch (sCraftItem_Info[i].PlusElementCode[k])
					{
					case SIN_ADD_FIRE:
						lpsItem->ItemInfo.Resistance[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_FIRE;

						break;
					case SIN_ADD_ICE:
						lpsItem->ItemInfo.Resistance[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ICE;
						break;
					case SIN_ADD_LIGHTNING:
						lpsItem->ItemInfo.Resistance[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIGHTNING;
						break;

					case SIN_ADD_POISON:
						lpsItem->ItemInfo.Resistance[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_POISON;
						break;
					case SIN_ADD_BIO:
						lpsItem->ItemInfo.Resistance[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BIO;
						break;
					case SIN_ADD_CRITICAL:
						lpsItem->ItemInfo.Critical_Hit += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_CRITICAL;
						break;
					case SIN_ADD_ATTACK_RATE:
						lpsItem->ItemInfo.Attack_Rating += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_RATE;
						break;
					case SIN_ADD_DAMAGE_MIN:

						lpsItem->ItemInfo.Damage[0] += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MIN;
						break;

					case SIN_ADD_DAMAGE_MAX:

						lpsItem->ItemInfo.Damage[1] += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MAX;
						break;
					case SIN_ADD_ATTACK_SPEED:

						lpsItem->ItemInfo.Attack_Speed += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_SPEED;
						break;
					case SIN_ADD_ABSORB:

						lpsItem->ItemInfo.fAbsorb += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ABSORB;
						break;
					case SIN_ADD_DEFENCE:

						lpsItem->ItemInfo.Defence += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DEFENCE;
						break;
					case SIN_ADD_BLOCK_RATE:

						lpsItem->ItemInfo.fBlock_Rating += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BLOCK_RATE;
						break;
					case SIN_ADD_MOVE_SPEED:

						lpsItem->ItemInfo.fSpeed += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MOVE_SPEED;
						break;

					case SIN_ADD_LIFE:

						lpsItem->ItemInfo.fIncrease_Life += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFE;
						break;

					case SIN_ADD_MANA:

						lpsItem->ItemInfo.fIncrease_Mana += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANA;
						break;
					case SIN_ADD_STAMINA:

						lpsItem->ItemInfo.fIncrease_Stamina += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINA;
						break;
					case SIN_ADD_LIFEREGEN:

						lpsItem->ItemInfo.fLife_Regen += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFEREGEN;
						break;
					case SIN_ADD_MANAREGEN:

						lpsItem->ItemInfo.fMana_Regen += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANAREGEN;

						break;
					case SIN_ADD_STAMINAREGEN:

						lpsItem->ItemInfo.fStamina_Regen += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINAREGEN;

						break;
					}
				}
			}*/

			//lpsItem->ItemInfo.ItemAgingNum[0] = 18;
			//lpsItem->ItemInfo.ItemKindCode = ITEM_KIND_CRAFT;
			ReformMixItem(&lpsItem->ItemInfo);
			ReformItem(&lpsItem->ItemInfo);
		}
	}

	if (TypeMigration == 3)
	{
		if (Flag == 0 || Flag == 1 || Flag == 2 || Flag == 3)
		{
			SetAgingItem(&lpsItem->ItemInfo, 13);
		}
		else if (Flag != ITEM_KIND_CRAFT)
		{
			int MixNum = 0;
			int AgingNum = 18;

			switch (Code & sinITEM_MASK2)
			{
			case sinOR1:
			case sinOR2:
				MixNum = 8;
				break;

			case sinOA1:
				MixNum = 9;
				break;

			case sinDA1:
			case sinDA2:
			case sinDA3:
			case sinDA4:
				//MixNum = 11;
				break;

			case sinDS1:
				//MixNum = 13;
				break;

			case sinOA2:
				MixNum = 5;
				break;

			case sinDG1:
				MixNum = 6;
				break;

			case sinOS1:
				MixNum = 10;
				break;

			case sinOE1:
				MixNum = 33;
				break;

			case sinDB1:
				MixNum = 7;
				break;

			case sinWA1:
			case sinWC1:
			case sinWH1:
			case sinWM1:
			case sinWP1:
			case sinWS1:
			case sinWS2:
			case sinWT1:

				//MixNum = 9;

			case sinWD1:
			case sinWN1:
			case sinWV1:
				//MixNum = 10;
				break;
			}

			int i = MixNum;
			for (int k = 0; k < 12; k++)
			{
				if (sCraftItem_Info[i].PlusElementCode[k])
				{
					switch (sCraftItem_Info[i].PlusElementCode[k])
					{
					case SIN_ADD_FIRE:
						lpsItem->ItemInfo.Resistance[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_FIRE;

						break;
					case SIN_ADD_ICE:
						lpsItem->ItemInfo.Resistance[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ICE;
						break;
					case SIN_ADD_LIGHTNING:
						lpsItem->ItemInfo.Resistance[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIGHTNING;
						break;

					case SIN_ADD_POISON:
						lpsItem->ItemInfo.Resistance[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_POISON;
						break;
					case SIN_ADD_BIO:
						lpsItem->ItemInfo.Resistance[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BIO;
						break;
					case SIN_ADD_CRITICAL:
						lpsItem->ItemInfo.Critical_Hit += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_CRITICAL;
						break;
					case SIN_ADD_ATTACK_RATE:
						lpsItem->ItemInfo.Attack_Rating += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_RATE;
						break;
					case SIN_ADD_DAMAGE_MIN:

						lpsItem->ItemInfo.Damage[0] += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MIN;
						break;

					case SIN_ADD_DAMAGE_MAX:

						lpsItem->ItemInfo.Damage[1] += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MAX;
						break;
					case SIN_ADD_ATTACK_SPEED:

						lpsItem->ItemInfo.Attack_Speed += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ATTACK_SPEED;
						break;
					case SIN_ADD_ABSORB:

						lpsItem->ItemInfo.fAbsorb += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_ABSORB;
						break;
					case SIN_ADD_DEFENCE:

						lpsItem->ItemInfo.Defence += (int)sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_DEFENCE;
						break;
					case SIN_ADD_BLOCK_RATE:

						lpsItem->ItemInfo.fBlock_Rating += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_BLOCK_RATE;
						break;
					case SIN_ADD_MOVE_SPEED:

						lpsItem->ItemInfo.fSpeed += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MOVE_SPEED;
						break;

					case SIN_ADD_LIFE:

						lpsItem->ItemInfo.fIncrease_Life += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFE;
						break;

					case SIN_ADD_MANA:

						lpsItem->ItemInfo.fIncrease_Mana += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANA;
						break;
					case SIN_ADD_STAMINA:

						lpsItem->ItemInfo.fIncrease_Stamina += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINA;
						break;
					case SIN_ADD_LIFEREGEN:

						lpsItem->ItemInfo.fLife_Regen += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_LIFEREGEN;
						break;
					case SIN_ADD_MANAREGEN:

						lpsItem->ItemInfo.fMana_Regen += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_MANAREGEN;

						break;
					case SIN_ADD_STAMINAREGEN:

						lpsItem->ItemInfo.fStamina_Regen += sCraftItem_Info[i].AddElement[k];

						lpsItem->ItemInfo.ItemKindMask |= SIN_ADD_STAMINAREGEN;

						break;
					}
				}
			}

			lpsItem->ItemInfo.ItemAgingNum[0] = 21;
			lpsItem->ItemInfo.ItemKindCode = ITEM_KIND_CRAFT;
			ReformMixItem(&lpsItem->ItemInfo);
			ReformItem(&lpsItem->ItemInfo);
		}
	}

	ReformItem(&lpsItem->ItemInfo);

	TransItemInfo.code = smTRANSCODE_PUTITEM;
	TransItemInfo.size = sizeof(TRANS_ITEMINFO);
	memcpy(&TransItemInfo.Item, &lpsItem->ItemInfo, sizeof(sITEMINFO));
	rsRegist_ItemSecCode(Player, &TransItemInfo, 1);

	if (Player->lpsmSock)
		Player->lpsmSock->Send2((char*)&TransItemInfo, TransItemInfo.size, TRUE);

	delete lpsItem;
}

void PlayerMigration::Recv(smTRANS_COMMAND* ps)
{
	TypeMigration = ps->WParam;
}

void PlayerMigration::Open()
{
	if (lpCurPlayer->smCharInfo.JOB_CODE > 11)
	{
		cMessageBox.ShowMessageEvent("Não existe migração disponível para essa classe!");
		return;
	}

	if (!TypeMigration)
	{
		cMessageBox.ShowMessageEvent("Você não tem migração!");
		return;
	}

	if (lpCurPlayer->smCharInfo.Level < 90)
	{
		cMessageBox.ShowMessageEvent("Alcance o nível 90 para pegar seus itens!");
		return;
	}

	if (TypeMigration == 1)
		LoadTextFromFile("game\\npc\\playermigration_clan.txt");
	if (TypeMigration == 2)
		LoadTextFromFile("game\\npc\\playermigration_solo.txt");
	if (TypeMigration == 3)
		LoadTextFromFile("game\\npc\\playermigration_nova.txt");

	fOpen = true;
}

void PlayerMigration::RequestItem(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		SQL::GetInstance()->EnterSqlSection();
		char szQuery[512];
		wsprintf(szQuery, "SELECT * FROM [PristonDB].[dbo].[PlayerMigration] WHERE [Name]='%s'", Player->szName);
		if (SQL::GetInstance()->Execute(szQuery))
		{
			int TypeMigration;
			if (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(2, &TypeMigration);
				if (TypeMigration == 1)
				{
					if (Player->smCharInfo.Level >= 90)
					{
						DWORD Fighter[13] = { sinWA1 | sin38, sinWA1 | sin39, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86,   sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Mechanician[13] = { sinWH1 | sin40, sinWC1 | sin37, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86,   sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Magician[13] = { sinWM1 | sin39, sinWM1 | sin40,  sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Priestess[13] = { sinWM1 | sin39, sinWM1 | sin40, sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Archer[13] = { sinWS1 | sin39, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Knight[13] = { sinWS2 | sin43, sinWS2 | sin44, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Pikeman[13] = { sinWP1 | sin38, sinWP1 | sin01, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, sinOS1 | sin19, sinOE1 | sin02, sinOE1 | sin02 };

						DWORD Atalanta[13] = { sinWT1 | sin38, sinWC1 | sin01, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Assassina[13] = { 0x10a2f00, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Shaman[13] = { 0x1092f00, sinWC1 | sin01,sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Guerreira[13] = { 0x10b2f00, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						switch (Player->smCharInfo.JOB_CODE)
						{
						case JOBCODE_FIGHTER:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Fighter[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MECHANICIAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Mechanician[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ARCHER:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Archer[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_PIKEMAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Pikeman[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ATALANTA:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Atalanta[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_KNIGHT:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Knight[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MAGICIAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Magician[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_PRIESTESS:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Priestess[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ASSASSINE:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Assassina[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_SHAMAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Shaman[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MARTIAL:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Guerreira[cnt], cnt, TypeMigration);
							break;
						}

						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);

						/*	Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24 * 15;
							Player->dwParam_PrimeItem_VIP = 2;

							PACKET_RECV_VIP packet;
							packet.size = sizeof(PACKET_RECV_VIP);
							packet.code = smTRANSCODE_RECV_VIP;
							packet.dwParam_PrimeItem_VIP = Player->dwParam_PrimeItem_VIP;
							packet.dwTime_PrimeItem_VIP = Player->dwTime_PrimeItem_VIP;
							Player->lpsmSock->Send((char*)&packet, packet.size, true);*/

						PREMIUM_TIME	smPremiumTime;
						smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
						smPremiumTime.size = sizeof(PREMIUM_TIME);
						smPremiumTime.ThirdEye = Player->dwTime_PrimeItem_X2;
						smPremiumTime.ExpUp = Player->dwTime_PrimeItem_ExpUp;
						smPremiumTime.VampCuspid = Player->dwTime_PrimeItem_VampCuspid;
						smPremiumTime.ManaRecharg = Player->dwTime_PrimeItem_ManaRecharg;
						smPremiumTime.MightofAwell = Player->dwTime_PrimeItem_MightofAwell;
						smPremiumTime.MightofAwell2 = Player->dwTime_PrimeItem_MightofAwell2;
						smPremiumTime.ManaReduce = Player->dwTime_PrimeItem_ManaReduce;
						smPremiumTime.PhenixPet = Player->dwTime_PrimeItem_PhenixPet;
						smPremiumTime.HelpPet = Player->dwTime_PrimeItem_HelpPet;
						smPremiumTime.VampCuspidEx = Player->dwTime_PrimeItem_VampCuspid_EX;
						smPremiumTime.StaminaReduce = Player->dwTime_PrimeItem_StaminaReduce;
						smPremiumTime.BigHead = Player->dwTime_PrimeItem_BigHead;

						if (Player->lpsmSock)
							Player->lpsmSock->Send2((char*)&smPremiumTime, smPremiumTime.size, TRUE);

						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[PlayerMigration] SET TypeMigration=0 WHERE [Name]='%s'", Player->szName);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
				else if (TypeMigration == 2)
				{
					if (Player->smCharInfo.Level >= 90)
					{
						DWORD Fighter[13] = { sinWA1 | sin38, sinWA1 | sin39, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86,   sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Mechanician[13] = { sinWH1 | sin40, sinWC1 | sin37, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86,   sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Magician[13] = { sinWM1 | sin39, sinWM1 | sin40,  sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Priestess[13] = { sinWM1 | sin39, sinWM1 | sin40, sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Archer[13] = { sinWS1 | sin39, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Knight[13] = { sinWS2 | sin43, sinWS2 | sin44, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Pikeman[13] = { sinWP1 | sin38, sinWP1 | sin01, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, sinOS1 | sin19, sinOE1 | sin02, sinOE1 | sin02 };

						DWORD Atalanta[13] = { sinWT1 | sin38, sinWC1 | sin01, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Assassina[13] = { 0x10a2f00, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Shaman[13] = { 0x1092f00, sinWC1 | sin01,sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Guerreira[13] = { 0x10b2f00, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						switch (Player->smCharInfo.JOB_CODE)
						{
						case JOBCODE_FIGHTER:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Fighter[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MECHANICIAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Mechanician[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ARCHER:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Archer[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_PIKEMAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Pikeman[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ATALANTA:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Atalanta[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_KNIGHT:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Knight[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MAGICIAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Magician[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_PRIESTESS:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Priestess[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ASSASSINE:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Assassina[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_SHAMAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Shaman[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MARTIAL:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Guerreira[cnt], cnt, TypeMigration);
							break;
						}

						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);

						/*	Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24 * 7;
							Player->dwParam_PrimeItem_VIP = 2;

							PACKET_RECV_VIP packet;
							packet.size = sizeof(PACKET_RECV_VIP);
							packet.code = smTRANSCODE_RECV_VIP;
							packet.dwParam_PrimeItem_VIP = Player->dwParam_PrimeItem_VIP;
							packet.dwTime_PrimeItem_VIP = Player->dwTime_PrimeItem_VIP;
							Player->lpsmSock->Send((char*)&packet, packet.size, true);*/

						PREMIUM_TIME	smPremiumTime;
						smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
						smPremiumTime.size = sizeof(PREMIUM_TIME);
						smPremiumTime.ThirdEye = Player->dwTime_PrimeItem_X2;
						smPremiumTime.ExpUp = Player->dwTime_PrimeItem_ExpUp;
						smPremiumTime.VampCuspid = Player->dwTime_PrimeItem_VampCuspid;
						smPremiumTime.ManaRecharg = Player->dwTime_PrimeItem_ManaRecharg;
						smPremiumTime.MightofAwell = Player->dwTime_PrimeItem_MightofAwell;
						smPremiumTime.MightofAwell2 = Player->dwTime_PrimeItem_MightofAwell2;
						smPremiumTime.ManaReduce = Player->dwTime_PrimeItem_ManaReduce;
						smPremiumTime.PhenixPet = Player->dwTime_PrimeItem_PhenixPet;
						smPremiumTime.HelpPet = Player->dwTime_PrimeItem_HelpPet;
						smPremiumTime.VampCuspidEx = Player->dwTime_PrimeItem_VampCuspid_EX;
						smPremiumTime.StaminaReduce = Player->dwTime_PrimeItem_StaminaReduce;
						smPremiumTime.BigHead = Player->dwTime_PrimeItem_BigHead;

						if (Player->lpsmSock)
							Player->lpsmSock->Send2((char*)&smPremiumTime, smPremiumTime.size, TRUE);

						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[PlayerMigration] SET TypeMigration=0 WHERE [Name]='%s'", Player->szName);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
				else if (TypeMigration == 3)
				{
					if (Player->smCharInfo.Level >= 90)
					{
						DWORD Fighter[13] = { sinWA1 | sin38, sinWA1 | sin39, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86,   sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Mechanician[13] = { sinWH1 | sin40, sinWC1 | sin37, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86,   sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Magician[13] = { sinWM1 | sin39, sinWM1 | sin40,  sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Priestess[13] = { sinWM1 | sin39, sinWM1 | sin40, sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Archer[13] = { sinWS1 | sin39, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Knight[13] = { sinWS2 | sin43, sinWS2 | sin44, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD  Pikeman[13] = { sinWP1 | sin38, sinWP1 | sin01, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, sinOS1 | sin19, sinOE1 | sin02, sinOE1 | sin02 };

						DWORD Atalanta[13] = { sinWT1 | sin38, sinWC1 | sin01, sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Assassina[13] = { 0x10a2f00, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Shaman[13] = { 0x1092f00, sinWC1 | sin01,sinDA2 | sin26, sinOM1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						DWORD Guerreira[13] = { 0x10b2f00, sinWC1 | sin01,sinDA1 | sin26, sinDS1 | sin27, sinDG1 | sin86, sinDB1 | sin86, sinOA2 | sin86, sinOR1 | sin24, sinOR1 | sin24, sinOA1 | sin24, 0x30a0200, 0x30a0200, sinOS1 | sin19 };

						switch (Player->smCharInfo.JOB_CODE)
						{
						case JOBCODE_FIGHTER:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Fighter[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MECHANICIAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Mechanician[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ARCHER:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Archer[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_PIKEMAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Pikeman[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ATALANTA:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Atalanta[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_KNIGHT:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Knight[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MAGICIAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Magician[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_PRIESTESS:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Priestess[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_ASSASSINE:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Assassina[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_SHAMAN:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Shaman[cnt], cnt, TypeMigration);
							break;
						case JOBCODE_MARTIAL:
							for (int cnt = 0; cnt < 13; cnt++) SendItem(Player, Guerreira[cnt], cnt, TypeMigration);
							break;
						}

						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);
						rsPutItem(Player, sinBI2 | sin38);

						/*Player->dwTime_PrimeItem_VIP = ((DWORD)tServerTime) + 60 * 60 * 24 * 15;
						Player->dwParam_PrimeItem_VIP = 2;

						PACKET_RECV_VIP packet;
						packet.size = sizeof(PACKET_RECV_VIP);
						packet.code = smTRANSCODE_RECV_VIP;
						packet.dwParam_PrimeItem_VIP = Player->dwParam_PrimeItem_VIP;
						packet.dwTime_PrimeItem_VIP = Player->dwTime_PrimeItem_VIP;
						Player->lpsmSock->Send((char*)&packet, packet.size, true);*/

						PREMIUM_TIME	smPremiumTime;
						smPremiumTime.code = smTRANSCODE_SEND_AGAME_SERVER;
						smPremiumTime.size = sizeof(PREMIUM_TIME);
						smPremiumTime.ThirdEye = Player->dwTime_PrimeItem_X2;
						smPremiumTime.ExpUp = Player->dwTime_PrimeItem_ExpUp;
						smPremiumTime.VampCuspid = Player->dwTime_PrimeItem_VampCuspid;
						smPremiumTime.ManaRecharg = Player->dwTime_PrimeItem_ManaRecharg;
						smPremiumTime.MightofAwell = Player->dwTime_PrimeItem_MightofAwell;
						smPremiumTime.MightofAwell2 = Player->dwTime_PrimeItem_MightofAwell2;
						smPremiumTime.ManaReduce = Player->dwTime_PrimeItem_ManaReduce;
						smPremiumTime.PhenixPet = Player->dwTime_PrimeItem_PhenixPet;
						smPremiumTime.HelpPet = Player->dwTime_PrimeItem_HelpPet;
						smPremiumTime.VampCuspidEx = Player->dwTime_PrimeItem_VampCuspid_EX;
						smPremiumTime.StaminaReduce = Player->dwTime_PrimeItem_StaminaReduce;
						smPremiumTime.BigHead = Player->dwTime_PrimeItem_BigHead;

						if (Player->lpsmSock)
							Player->lpsmSock->Send2((char*)&smPremiumTime, smPremiumTime.size, TRUE);

						wsprintf(szQuery, "UPDATE [PristonDB].[dbo].[PlayerMigration] SET TypeMigration=0 WHERE [Name]='%s'", Player->szName);
						SQL::GetInstance()->Execute(szQuery);
					}
				}
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}