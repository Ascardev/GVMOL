#pragma once


struct restaureITEM
{
	int CoinPrice;
	sITEMINFO sItem;
};

struct RESTAURE_LIST
{
	int size, code;

	int Count;
	restaureITEM ItemList[15];
};

class cRESTAURE
{
public:

	void RecvGetRestaure(rsPLAYINFO* lpPlayInfo);
	void InsertAgingFailed(rsPLAYINFO* lpPlayInfo, char* ItemName, int ItemAging, int Head, int dwChkSum);
	void RestaureItem(rsPLAYINFO* lpPlayInfo, DWORD Head, DWORD dwChkSum, int coinType, DWORD StoneCode, DWORD StoneHead, DWORD StoneSum);
};

extern cRESTAURE cRestaure;
