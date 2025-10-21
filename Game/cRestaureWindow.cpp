#include "sinbaram/sinLinkHeader.h"
#include "cRestaureWindow.h"

cRESTAURE cRestaure;

extern bool isMousePos(int x, int y, int w, int h);

void cRESTAURE::Load()
{
	Mat[BACKGROUND] = CreateTextureMaterial("game\\recover\\main.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[CLOSE] = CreateTextureMaterial("game\\recover\\exit.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[LEFT] = CreateTextureMaterial("game\\recover\\left_btn.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RIGHT] = CreateTextureMaterial("game\\recover\\right_btn.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
	Mat[RESTAURE] = CreateTextureMaterial("game\\recover\\restaure_btn.tga", 0, 0, 0, 0, SMMAT_BLEND_ALPHA);
}

void cRESTAURE::Draw()
{
	if (!OpenFlag)
		return;

	BaseX = 18;
	BaseY = 50;

	dsDrawTexImage(Mat[BACKGROUND], BaseX, BaseY, 455, 367, 255);

	if (isMousePos(BaseX + 377, BaseY + 4, 23, 23))
		dsDrawTexImage(Mat[CLOSE], BaseX + 377, BaseY + 4, 39, 39, 255);
	else
		dsDrawTexImage(Mat[CLOSE], BaseX + 377, BaseY + 4, 39, 39, 200);

	if (isMousePos(BaseX + 242, BaseY + 269, 81, 22))
		dsDrawTexImage(Mat[RESTAURE], BaseX + 242, BaseY + 269, 89, 36, 255);
	else
		dsDrawTexImage(Mat[RESTAURE], BaseX + 242, BaseY + 269, 89, 36, 120);

	if (isMousePos(BaseX + 211, BaseY + 191, 23, 23))
		dsDrawTexImage(Mat[LEFT], BaseX + 211, BaseY + 191, 23, 23, 255);
	else
		dsDrawTexImage(Mat[LEFT], BaseX + 211, BaseY + 191, 23, 23, 200);

	if (isMousePos(BaseX + 333, BaseY + 191, 23, 23))
		dsDrawTexImage(Mat[RIGHT], BaseX + 333, BaseY + 191, 23, 23, 255);
	else
		dsDrawTexImage(Mat[RIGHT], BaseX + 333, BaseY + 191, 23, 23, 200);

	if (itemCount && itemIndex < itemCount)
	{
		RESTAURE_ITEM* Item = vItems[itemIndex];
		if (Item->psItem.lpItem)
		{
			Item->psItem.x = Item->psItem.SetX = 175 + BaseX + (220 / 2 - Item->psItem.w / 2);
			Item->psItem.y = Item->psItem.SetY = 90 + BaseY + (230 / 2 - Item->psItem.h / 2);

			DrawSprite(Item->psItem.x, Item->psItem.y, Item->psItem.lpItem, 0, 0, Item->psItem.w, Item->psItem.h);

			if (isMousePos(Item->psItem.x, Item->psItem.y, Item->psItem.w, Item->psItem.h)) {
				cItem.ShowItemInfo(&Item->psItem, 1);
				sinShowItemInfoFlag = 1;
			}
		}
	}

	char buff[255] = {};
	NumLineComa(CoinShop::GetInstance()->GetCoin(), buff);
	dsTextLineOut(BaseX + 220, BaseY + 330, buff, lstrlen(buff));
	DrawFontTextNew(BaseX + 220, BaseY + 333, buff, D3DCOLOR_RGBA(255, 255, 222, 180), 1);

	char buff1[255] = {};
	wsprintf(buff1, "Valor do Restaure", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 120, buff1, D3DCOLOR_RGBA(255, 216, 0, 180), 1);
	wsprintf(buff1, "+10 Preço: 100", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 140, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+11 Preço: 200", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 158, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+12 Preço: 300", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 176, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+13 Preço: 500", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 194, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+14 Preço: 600", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 212, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+15 Preço: 700", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 230, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+16 Preço: 800", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 248, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+17 Preço: 900", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 266, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+18 Preço: 1.000", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 284, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+19 Preço: 1.100", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 300, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);
	wsprintf(buff1, "+20 Preço: 1.200", buff1);
	DrawFontTextNew(BaseX + 68, BaseY + 316, buff1, D3DCOLOR_RGBA(255, 255, 255, 180), 1);

	//wsprintf(buff, "+14 ao +17: %d Coins", 650);
	//dsTextLineOut(BaseX + 102, BaseY + 240, buff, lstrlen(buff));*/
	//wsprintf(buff, "O valor será cobrado de acordo com o Aging!", 950);
	//dsTextLineOut(BaseX + 40, BaseY + 260, buff, lstrlen(buff));
}

bool cRESTAURE::LButtonDown()
{
	if (!OpenFlag)
		return FALSE;

	if (isMousePos(BaseX + 377, BaseY + 4, 39, 39))
	{
		Close();
	}

	if (isMousePos(BaseX + 242, BaseY + 269, 89, 36))
	{
		Restaure();
	}

	if (isMousePos(BaseX + 211, BaseY + 191, 23, 23))
	{
		SwitchItem(-1);
	}

	if (isMousePos(BaseX + 333, BaseY + 191, 23, 23))
	{
		SwitchItem(1);
	}

	return false;
}

void cRESTAURE::Open()
{
	itemCount = 0;
	itemIndex = 0;

	smTRANS_COMMAND smTransCommand;
	smTransCommand.code = smTRANSCODE_GET_RESTAURE;
	smTransCommand.size = sizeof(smTRANS_COMMAND);

	smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);

	OpenFlag = true;
}

void cRESTAURE::Close()
{
	OpenFlag = false;

	for (auto item : vItems)
		delete item;

	vItems.clear();
}

void cRESTAURE::Restaure()
{
	if (!itemCount || itemIndex >= itemCount)
	{
		cMessageBox.ShowMessageEvent("Você não tem itens para restaurar.");
		return;
	}

	RESTAURE_ITEM* Item = vItems[itemIndex];

	if (CoinShop::GetInstance()->GetCoin() < Item->CoinPrice)
	{
		cMessageBox.ShowMessageEvent("Você não tem crédito suficiente.");
		return;
	}

	if (!cInvenTory.CheckSetEmptyArea(&Item->psItem))
	{
		cMessageBox.ShowMessageEvent("Você não tem espaço suficiente no inventário.");
		return;
	}

	if (!cInvenTory.CheckSetOk(&Item->psItem, 1))
	{
		cMessageBox.ShowMessageEvent("Excede o peso limite.");
		return;
	}

	smTRANS_COMMAND_EX smTransCommand = {};
	smTransCommand.code = smTRANSCODE_RESTAURE_ITEM;
	smTransCommand.size = sizeof(smTRANS_COMMAND_EX);
	smTransCommand.WParam = Item->psItem.sItemInfo.ItemHeader.Head;
	smTransCommand.LParam = Item->psItem.sItemInfo.ItemHeader.dwChkSum;

	resetList = true;

	smWsockServer->Send((char*)&smTransCommand, smTransCommand.size, TRUE);
}

void cRESTAURE::SwitchItem(int Side)
{
	if (Side < 0)
	{
		if (itemIndex > 0)
			itemIndex--;
	}
	else
	{
		if (itemIndex < itemCount - 1)
			itemIndex++;
	}
}

void cRESTAURE::RecvRestaureList(RESTAURE_LIST* lpRestaureList)
{
	if (resetList)
	{
		resetList = false;

		for (auto item : vItems)
			delete item;

		vItems.clear();

		itemCount = 0;
		itemIndex = 0;
	}

	itemCount += lpRestaureList->Count;
	itemIndex = 0;

	for (int i = 0; i < itemCount; i++)
	{
		RESTAURE_ITEM* item = new RESTAURE_ITEM;

		if (item)
		{
			LoadItemImage(&lpRestaureList->ItemList[i].sItem, &item->psItem);
			if (item->psItem.lpItem)
			{
				item->CoinPrice = lpRestaureList->ItemList[i].CoinPrice;

				vItems.push_back(item);
			}
			else
				delete item;
		}
	}
}