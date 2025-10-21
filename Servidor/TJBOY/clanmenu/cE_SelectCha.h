





#pragma once
#ifndef __CE_SELECTCHA_H__
#define __CE_SELECTCHA_H__


typedef struct _tagChaClan
{
	char ClanName[64];
	char szMarkNum[16];
	int  nStatus;
#ifdef USE_PROSTONTALE		
	LPDIRECT3DTEXTURE9  hClanMark;
#else
	HBITMAP		hClanMark;
#endif
}CHACLAN;


class CSelectCha
{
public:
	CSelectCha();
	virtual ~CSelectCha();
public:
	void Main();
private:
protected:
	int nHowDownClanName;
};
#endif

#ifdef CE_SELECTCHA_CPP
class CSelectCha   g_SelectCha;
CHACLAN           g_ChaClan[5];
#else
extern class CSelectCha   g_SelectCha;
extern CHACLAN           g_ChaClan[5];
#endif
