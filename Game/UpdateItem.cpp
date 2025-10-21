#include "sinbaram\sinLinkHeader.h"

sDEF_ITEMINFO* DefaultItems;
int	DefaultItemCount;
int	rsDeleteInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
int SaveThrowItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwKey, DWORD dwSum);
int	rsAddInvenItem(rsPLAYINFO* lpPlayInfo, DWORD dwCode, DWORD dwHead, DWORD dwChkSum);
void SendItemToPlayer(rsPLAYINFO* lpPlayInfo, char* szCode, int Spec);
int	rsSendServerChatMessageToUser(rsPLAYINFO* lpPlayInfo, int Color, char* msg, ...);
int SetAgingItem(sITEMINFO* pItem, int AgingNum);
void GetRemodel(DWORD Flag, DWORD Code, SWAPITEM* Swap);
DWORD GetItemCode(char* szCode);

void UpdateItem::Init()
{
	Images[0] = CreateTextureMaterial("game\\images\\settings\\window2.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[1] = CreateTextureMaterial("game\\images\\window\\button_ok.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[2] = CreateTextureMaterial("game\\images\\window\\button_ok_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[3] = CreateTextureMaterial("game\\images\\window\\button_close.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Images[4] = CreateTextureMaterial("game\\images\\window\\button_close_.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	bImages[0] = LoadDibSurfaceOffscreen("game\\images\\coin\\itembox.bmp");
}

bool UpdateItem::MouseAction(int x, int y, int w, int h)
{
	if (pRealCursorPos.x > x && pRealCursorPos.x < x + w && pRealCursorPos.y > y && pRealCursorPos.y < y + h)
		return TRUE;

	return FALSE;
}

void UpdateItem::DrawImage(int Image, int x, int y, int w, int h)
{
	dsDrawTexImage(Image, x, y, w - 1, h - 1, 255);
}

void GetItemMixture(int MixNum, sITEM* lpsItem)
{
	int i = MixNum;
	for (int k = 0; k < 12; k++)
	{
		if (sCraftItem_Info[i].PlusElementCode[k])
		{
			switch (sCraftItem_Info[i].PlusElementCode[k])
			{
			case SIN_ADD_FIRE:
				lpsItem->sItemInfo.Resistance[sITEMINFO_FIRE] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_FIRE;

				break;
			case SIN_ADD_ICE:
				lpsItem->sItemInfo.Resistance[sITEMINFO_ICE] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ICE;
				break;
			case SIN_ADD_LIGHTNING:
				lpsItem->sItemInfo.Resistance[sITEMINFO_LIGHTING] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_LIGHTNING;
				break;

			case SIN_ADD_POISON:
				lpsItem->sItemInfo.Resistance[sITEMINFO_POISON] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_POISON;
				break;
			case SIN_ADD_BIO:
				lpsItem->sItemInfo.Resistance[sITEMINFO_BIONIC] += (int)sCraftItem_Info[i].AddElement[k];
				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_BIO;
				break;
			case SIN_ADD_CRITICAL:
				lpsItem->sItemInfo.Critical_Hit += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_CRITICAL;
				break;
			case SIN_ADD_ATTACK_RATE:
				lpsItem->sItemInfo.Attack_Rating += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ATTACK_RATE;
				break;
			case SIN_ADD_DAMAGE_MIN:

				lpsItem->sItemInfo.Damage[0] += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MIN;
				break;

			case SIN_ADD_DAMAGE_MAX:

				lpsItem->sItemInfo.Damage[1] += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_DAMAGE_MAX;
				break;
			case SIN_ADD_ATTACK_SPEED:

				lpsItem->sItemInfo.Attack_Speed += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ATTACK_SPEED;
				break;
			case SIN_ADD_ABSORB:

				lpsItem->sItemInfo.fAbsorb += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_ABSORB;
				break;
			case SIN_ADD_DEFENCE:

				lpsItem->sItemInfo.Defence += (int)sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_DEFENCE;
				break;
			case SIN_ADD_BLOCK_RATE:

				lpsItem->sItemInfo.fBlock_Rating += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_BLOCK_RATE;
				break;
			case SIN_ADD_MOVE_SPEED:

				lpsItem->sItemInfo.fSpeed += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_MOVE_SPEED;
				break;

			case SIN_ADD_LIFE:

				lpsItem->sItemInfo.fIncrease_Life += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_LIFE;
				break;

			case SIN_ADD_MANA:

				lpsItem->sItemInfo.fIncrease_Mana += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_MANA;
				break;
			case SIN_ADD_STAMINA:

				lpsItem->sItemInfo.fIncrease_Stamina += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_STAMINA;
				break;
			case SIN_ADD_LIFEREGEN:

				lpsItem->sItemInfo.fLife_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_LIFEREGEN;
				break;
			case SIN_ADD_MANAREGEN:

				lpsItem->sItemInfo.fMana_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_MANAREGEN;

				break;
			case SIN_ADD_STAMINAREGEN:

				lpsItem->sItemInfo.fStamina_Regen += sCraftItem_Info[i].AddElement[k];

				lpsItem->sItemInfo.ItemKindMask |= SIN_ADD_STAMINAREGEN;

				break;
			}
		}
	}
}

void UpdateItem::RecvRequestOnClient(smPACKET_UPDATE_ITEM* packet)
{
	sITEM TempItem;

	if (LoadItemImage(&packet->sItem[0].sItemInfo, &TempItem))
	{
		if (cInvenTory.CheckRequireItemToSet(&TempItem))
		{
			if (!cInvenTory.AutoSetInvenItem(&TempItem, 1))
			{
				sinThrowItemToFeild(&packet->sItem[0]);
			}
		}
	}

	CheckCharForm();
	ReformCharForm();
	SendSaveMoney();
	SaveGameData();

	cInvenTory.DeleteInvenItemToServer(packet->sItem[0].sItemInfo.CODE, packet->sItem[0].sItemInfo.BackUpKey, packet->sItem[0].sItemInfo.BackUpChkSum);
	cInvenTory.DeleteInvenItemToServer(packet->sItem[1].sItemInfo.CODE, packet->sItem[1].sItemInfo.BackUpKey, packet->sItem[1].sItemInfo.BackUpChkSum);
	ZeroMemory(&sItem[0], sizeof(sITEM));
	ZeroMemory(&sItem[1], sizeof(sITEM));

	ResetInvenItemCode();
	SaveGameData();
}

void UpdateItem::RecvItemList(smTRANS_COMMAND* packet)
{
	ItemList.push_back(packet->WParam);
}

void UpdateItem::SendItemList(rsPLAYINFO* Player)
{
	if (SQL::GetInstance()->IsConnected())
	{
		char szQuery[512];
		SQL::GetInstance()->EnterSqlSection();
		wsprintf(szQuery, "SELECT idCode FROM [PristonDB].[dbo].[UpdateItem_List]");
		if (SQL::GetInstance()->Execute(szQuery))
		{
			smTRANS_COMMAND ps;
			ps.size = sizeof(smTRANS_COMMAND);
			ps.code = smTRANSCODE_UPDATE_ITEM_LIST;
			while (SQL::GetInstance()->Fetch())
			{
				SQL::GetInstance()->GetDataValue(1, &ps.WParam);
				Player->lpsmSock->Send((char*)&ps, ps.size, TRUE);
			}
		}
		SQL::GetInstance()->LeaveSqlSection();
	}
}

void UpdateItem::RecvRequest(rsPLAYINFO* Player, smPACKET_UPDATE_ITEM* packet)
{
	if (packet->sItem[0].sItemInfo.CODE)
	{
		if (rsDeleteInvenItem(Player, packet->sItem[0].sItemInfo.CODE,
			packet->sItem[0].sItemInfo.ItemHeader.Head, packet->sItem[0].sItemInfo.ItemHeader.dwChkSum) < 0)
		{
			return;
		}

		if (rsDeleteInvenItem(Player, packet->sItem[1].sItemInfo.CODE,
			packet->sItem[1].sItemInfo.ItemHeader.Head, packet->sItem[1].sItemInfo.ItemHeader.dwChkSum) < 0)
		{
			return;
		}

		SaveThrowItem(Player, packet->sItem[0].sItemInfo.CODE,
			packet->sItem[0].sItemInfo.ItemHeader.Head, packet->sItem[0].sItemInfo.ItemHeader.dwChkSum);

		DWORD Code = 0;
		int Kind = packet->sItem[0].sItemInfo.ItemKindCode;
		int AgingNum = packet->sItem[0].sItemInfo.ItemAgingNum[0];
		int spec = cItem.GetJobCode(packet->sItem[0].sItemInfo.JobCodeMask);
		DWORD SwapFlag = packet->sItem[0].sItemInfo.SwapItem.Flag;
		DWORD SwapCode = packet->sItem[0].sItemInfo.SwapItem.Code;

		DWORD RecvCode = packet->sItem[0].sItemInfo.SwapItem.Flag ? packet->sItem[0].sItemInfo.SwapItem.Code : packet->sItem[0].sItemInfo.CODE;

		if (SQL::GetInstance()->IsConnected())
		{
			SQL::GetInstance()->EnterSqlSection();
			char szQuery[512];
			char szCode[32];
			wsprintf(szQuery, "SELECT szCode FROM [PristonDB].[dbo].[UpdateItem_List] WHERE [idCode]=%d", RecvCode);

			if (SQL::GetInstance()->Execute(szQuery))
			{
				if (SQL::GetInstance()->Fetch())
				{
					SQL::GetInstance()->GetDataValue(1, szCode);

					int Flag = 0;

					Code = GetItemCode(szCode);

					for (int cnt = 0; cnt < DefaultItemCount; cnt++)
					{
						if (DefaultItems[cnt].Item.CODE == Code && !DefaultItems[cnt].Item.UniqueItem)
						{
							CreateDefItemPerf(&packet->sItem[0].sItemInfo, &DefaultItems[cnt], spec);
							Flag++;
							break;
						}
					}

					if (SwapFlag && Flag)
					{
						GetRemodel(SwapFlag, Code, &packet->sItem[0].sItemInfo.SwapItem);
						packet->sItem[0].sItemInfo.CODE = packet->sItem[0].sItemInfo.SwapItem.Code;
						packet->sItem[0].sItemInfo.SwapItem.Code = Code;
					}

					if (Kind == ITEM_KIND_AGING && Flag)
					{
						SetAgingItem(&packet->sItem[0].sItemInfo, AgingNum);
					}

					if (Kind == ITEM_KIND_CRAFT && Flag)
					{
						int MixNum = 0;

						switch (Code & sinITEM_MASK2)
						{
						case sinDA1:
						case sinDA2:
						case sinDA3:
						case sinDA4:
							switch (AgingNum)
							{
							case 1:
								MixNum = 2;
								break;
							case 18:
								MixNum = 12;
								break;
							case 20:
								MixNum = 22;
								break;
							}
							break;
						case sinDS1:
							switch (AgingNum)
							{
							case 1:
								MixNum = 3;
								break;
							case 18:
								MixNum = 13;
								break;
							case 20:
								MixNum = 23;
								break;
							}
							break;
						case sinOA2:
							switch (AgingNum)
							{
							case 1:
								MixNum = 5;
								break;
							case 18:
								MixNum = 15;
								break;
							case 20:
								MixNum = 25;
								break;
							}
							break;
						case sinDG1:
							switch (AgingNum)
							{
							case 1:
								MixNum = 6;
								break;
							case 18:
								MixNum = 16;
								break;
							case 20:
								MixNum = 26;
								break;
							}
							break;
						case sinDB1:
							switch (AgingNum)
							{
							case 1:
								MixNum = 7;
								break;
							case 18:
								MixNum = 17;
								break;
							case 20:
								MixNum = 27;
								break;
							}
							break;
						case sinWA1:
						case sinWC1:
						case sinWH1:
						case sinWM1:
						case sinWP1:
						case sinWS1:
						case sinWS2:
						case sinWT1:
							switch (AgingNum)
							{
							case 1:
								MixNum = 0;
								break;
							case 18:
								MixNum = 10;
								break;
							case 20:
								MixNum = 20;
								break;
							}
							break;

						case sinWD1:
						case sinWN1:
						case sinWV1:
							switch (AgingNum)
							{
							case 1:
								MixNum = 1;
								break;
							case 18:
								MixNum = 11;
								break;
							case 20:
								MixNum = 21;
								break;
							}
							break;
						}
						GetItemMixture(MixNum, &packet->sItem[0]);
						packet->sItem[0].sItemInfo.ItemKindCode = Kind;
						packet->sItem[0].sItemInfo.ItemAgingNum[0] = AgingNum;
					}

					ReformItem(&packet->sItem[0].sItemInfo);

					rsAddInvenItem(Player, packet->sItem[0].sItemInfo.CODE,
						packet->sItem[0].sItemInfo.ItemHeader.Head, packet->sItem[0].sItemInfo.ItemHeader.dwChkSum);

					Player->lpsmSock->Send((char*)packet, packet->size, true);
				}
			}
			SQL::GetInstance()->LeaveSqlSection();
		}
	}
}

void UpdateItem::SendRequest()
{
	if (!sItem[0].Flag)
	{
		cMessageBox.ShowMessageEvent("Selecione o item que deseja evoluir!");
		return;
	}

	if (!sItem[1].Flag)
	{
		cMessageBox.ShowMessageEvent("Selecione a pedra para evoluir o item!");
		return;
	}

	smPACKET_UPDATE_ITEM ps;
	ps.size = sizeof(smPACKET_UPDATE_ITEM);
	ps.code = smTRANSCODE_UPDATE_ITEM;
	memcpy(&ps.sItem[0], &sItem[0], sizeof(sITEM));
	memcpy(&ps.sItem[1], &sItem[1], sizeof(sITEM));

	smWINSOCK* lpsmSock;
	lpsmSock = GetAreaServerSock();

	if (lpsmSock)
	{
		lpsmSock->Send((char*)&ps, ps.size, TRUE);
	}
}

void UpdateItem::Button()
{
	if (fOpen)
	{
		int WinX = WinSizeX / 2 - 165;
		int WinY = WinSizeY / 2 - 219;

		int Flag = 0;

		for (std::vector<int>::iterator it = ItemList.begin(); it != ItemList.end(); it++)
		{
			int pc = (*it);
			if (pc == MouseItem.sItemInfo.CODE)
			{
				Flag++;
			}
		}

		if (!sItem[0].Flag)
		{
			if (MouseItem.sItemInfo.CODE)
			{
				if (MouseAction(WinX + 90, WinY + 174, 68, 90))
				{
					if (!Flag)
					{
						cMessageBox.ShowMessageEvent("Esse item não faz parte desse processo!");
						return;
					}

					MouseItem.x = WinX + 90 + 34 - (MouseItem.w / 2);
					MouseItem.y = WinY + 174 + 40 - (MouseItem.h / 2);
					memcpy(&sItem[0], &MouseItem, sizeof(sITEM));
					ZeroMemory(&MouseItem, sizeof(sITEM));
				}
			}
		}
		else
		{
			if (!MouseItem.Flag)
			{
				if (MouseAction(WinX + 90, WinY + 174, 68, 90))
				{
					sItem[0].x = pCursorPos.x - (sItem[0].w / 2);
					sItem[0].y = pCursorPos.y - (sItem[0].y / 2);
					memcpy(&MouseItem, &sItem[0], sizeof(sITEM));
					ZeroMemory(&sItem[0], sizeof(sITEM));
				}
			}
		}

		if (!sItem[1].Flag)
		{
			if (MouseItem.sItemInfo.CODE)
			{
				if (MouseAction(WinX + 190, WinY + 174, 68, 90))
				{
					if (MouseItem.sItemInfo.CODE != (sinPR2 | sin04))
					{
						cMessageBox.ShowMessageEvent("Esse item não faz parte desse processo!");
						return;
					}

					MouseItem.x = WinX + 190 + 34 - (MouseItem.w / 2);
					MouseItem.y = WinY + 174 + 40 - (MouseItem.h / 2);
					memcpy(&sItem[1], &MouseItem, sizeof(sITEM));
					ZeroMemory(&MouseItem, sizeof(sITEM));
				}
			}
		}
		else
		{
			if (!MouseItem.Flag)
			{
				if (MouseAction(WinX + 190, WinY + 174, 68, 90))
				{
					sItem[1].x = pCursorPos.x - (sItem[1].w / 2);
					sItem[1].y = pCursorPos.y - (sItem[1].y / 2);
					memcpy(&MouseItem, &sItem[1], sizeof(sITEM));
					ZeroMemory(&sItem[1], sizeof(sITEM));
				}
			}
		}

		if (MouseAction(WinX + 85, WinY + 400, 80, 21))
		{
			SendRequest();
		}

		if (MouseAction(WinX + 185, WinY + 400, 80, 21))
			Close();
	}
}

void UpdateItem::Open()
{
	smTRANS_COMMAND ps;
	ps.size = sizeof(smTRANS_COMMAND);
	ps.code = smTRANSCODE_UPDATE_ITEM_LIST;

	smWINSOCK* lpsmSock;
	lpsmSock = GetAreaServerSock();

	if (lpsmSock)
	{
		lpsmSock->Send((char*)&ps, ps.size, TRUE);
	}

	fOpen = true;
}

void UpdateItem::Close()
{
	if (sItem[0].Flag || sItem[1].Flag)
	{
		cMessageBox.ShowMessageEvent("Termine o processo antes de fechar a janela!");
		return;
	}

	ItemList.clear();

	fOpen = false;
}

void UpdateItem::Draw()
{
	if (fOpen)
	{
		int Flag = 0;
		int WinX = WinSizeX / 2 - 165;
		int WinY = WinSizeY / 2 - 219;
		DrawImage(Images[0], WinX, WinY, 331, 438);
		DrawSprite(WinX + 90, WinY + 174, bImages[0], 0, 0, 68, 90);
		DrawSprite(WinX + 190, WinY + 174, bImages[0], 0, 0, 68, 90);

		for (std::vector<int>::iterator it = ItemList.begin(); it != ItemList.end(); it++)
		{
			int pc = (*it);
			if (pc == MouseItem.sItemInfo.CODE)
			{
				Flag++;
			}
		}

		if (MouseAction(WinX + 90, WinY + 174, 68, 90))
		{
			if (sItem[0].Flag)
			{
				dsDrawColorBox(D3DCOLOR_RGBA(255, 255, 255, 128), WinX + 90, WinY + 174, 68, 90);
			}
			else if (MouseItem.Flag)
			{
				if (!Flag)
					dsDrawColorBox(D3DCOLOR_RGBA(255, 0, 0, 128), WinX + 90, WinY + 174, 68, 90);
				else
					dsDrawColorBox(D3DCOLOR_RGBA(160, 235, 256, 128), WinX + 90, WinY + 174, 68, 90);
			}
		}

		if (MouseAction(WinX + 190, WinY + 174, 68, 90))
		{
			if (sItem[1].Flag)
			{
				dsDrawColorBox(D3DCOLOR_RGBA(255, 255, 255, 128), WinX + 190, WinY + 174, 68, 90);
			}
			else if (MouseItem.Flag)
			{
				if (MouseItem.sItemInfo.CODE != (sinPR2 | sin04))
					dsDrawColorBox(D3DCOLOR_RGBA(255, 0, 0, 128), WinX + 190, WinY + 174, 68, 90);
				else
					dsDrawColorBox(D3DCOLOR_RGBA(160, 235, 256, 128), WinX + 190, WinY + 174, 68, 90);
			}
		}

		if (sItem[0].Flag)
		{
			DrawSprite(sItem[0].x, sItem[0].y, sItem[0].lpItem, 0, 0, sItem[0].w, sItem[0].h);

			if (MouseAction(WinX + 90, WinY + 174, 68, 90))
			{
				sinShowItemInfoFlag = 1;
				cItem.ShowItemInfo(&sItem[0], 1);
			}
		}

		if (sItem[1].Flag)
		{
			DrawSprite(sItem[1].x, sItem[1].y, sItem[1].lpItem, 0, 0, sItem[1].w, sItem[1].h);

			if (MouseAction(WinX + 190, WinY + 174, 68, 90))
			{
				sinShowItemInfoFlag = 1;
				cItem.ShowItemInfo(&sItem[1], 1);
			}
		}

		SIZE size;
		FontType = 1;
		GetFontTextExtentPoint("[Evoluir Item]", 15, &size);
		dsTextLineOut(WinX + 165 - size.cx / 2, WinY + 40, "[Evoluir Item]", 15);
		FontType = 0;

		if (MouseAction(WinX + 85, WinY + 400, 80, 21))
			DrawImage(Images[2], WinX + 85, WinY + 400, 80, 21);
		else
			DrawImage(Images[1], WinX + 85, WinY + 400, 80, 21);

		if (MouseAction(WinX + 185, WinY + 400, 80, 21))
			DrawImage(Images[4], WinX + 185, WinY + 400, 80, 21);
		else
			DrawImage(Images[3], WinX + 185, WinY + 400, 80, 21);
	}
}