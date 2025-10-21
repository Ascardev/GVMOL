#include "sinbaram/sinLinkHeader.h"
#include <strsafe.h>

__declspec(naked) int nstr(const char* s)
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [ESP + 0x04] ;
		XOR EAX, EAX;
	NSTR_LOOPSTART:
		CMP BYTE PTR DS : [ECX + EAX] , 0;
		JE NSTR_RETURN;
		INC EAX;
		JMP NSTR_LOOPSTART;
	NSTR_RETURN:
		RETN;
	};
}

__declspec(naked) int nstr_s(const char* s, int l)
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [ESP + 0x04] ;
		XOR EAX, EAX;
	NSTR_LOOPSTART:
		CMP BYTE PTR DS : [ECX + EAX] , 0;
		JE NSTR_RETURN;
		CMP EAX, l;
		JE NSTR_RETURN;
		INC EAX;
		JMP NSTR_LOOPSTART;
	NSTR_RETURN:
		RETN;
	};
}

void clrstr(char* str)
{
	int j = lstrlenA(str);

	for (int i = 0; i < j; i++)
		str[i] = 0;
}

int lstrnlenA(char* pszString, int iMaxLen)
{
	int iRet = 0;

	for (int i = 0; i < iMaxLen; i++)
	{
		if (pszString[i] != 0)
			iRet++;
		else
			break;
	}

	return iRet;
}

bool lstrncmpA(char* pszString1, char* pszString2, int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		if (pszString1[i] != pszString2[i])
			return false;
	}

	return true;
}

bool lstrncmpiA(char* pszString1, char* pszString2, int iNum)
{
	for (int i = 0; i < iNum; i++)
	{
		char c1 = pszString1[i], c2 = pszString2[i];

		if ((c1 >= 'a') && (c1 <= 'z'))
			c1 -= 32;
		if ((c2 >= 'a') && (c2 <= 'z'))
			c2 -= 32;

		if (c1 != c2)
			return false;
	}

	return true;
}

void upper(char* pszString)
{
	for (int i = 0; ; i++)
	{
		char& c = pszString[i];

		if (c == 0)
			return;

		if ((c >= 'a') && (c <= 'z'))
			c -= 0x20;
	}
}

void upper(char& chr)
{
	if (chr == 0)
		return;

	if ((chr >= 'a') && (chr <= 'z'))
		chr -= 0x20;
}

void lower(char* pszString)
{
	for (int i = 0; ; i++)
	{
		char& c = pszString[i];

		if (c == 0)
			return;

		if ((c >= 'A') && (c <= 'Z'))
			c += 0x20;
	}
}

bool strcontains(char* pszString, char* pszContains)
{
	bool comparing = false;
	int r = 0;
	for (int i = 0; ; i++)
	{
		if (pszString[i] == 0)
		{
			if (pszContains[r] == 0)
				return true;

			return false;
		}

		if (pszContains[r] == 0)
		{
			if (comparing)
				return true;

			return false;
		}

		if (pszString[i] == pszContains[r])
		{
			comparing = true;
			r++;
		}
		else
		{
			comparing = false;
			r = 0;
		}
	}

	return false;
}

char* NumberToString(__int64 iNum)
{
	static char szOut[256];
	szOut[0] = 0;

	char szTmp[256], szNum[256];
	StringCbPrintfA(szTmp, 256, "%I64d", iNum);
	int nLen = lstrlenA(szTmp);

	int j = 0;
	for (int i = (nLen - 1); (i >= 0) && (j < 256); )
	{
		if ((j % 4) == 3)
		{
			szNum[j] = '.';
			j++;
		}
		else
		{
			szNum[j] = szTmp[i];
			j++;
			i--;
		}
	}
	szNum[j] = 0;

	//reverse
	int k = 0;
	for (int n = (lstrlenA(szNum) - 1); (n >= 0) && (k < 256); n--, k++)
		szOut[k] = szNum[n];
	szOut[k] = 0;

	return szOut;
}

int low(int a, int b)
{
	if (a < b)
		return a;

	return b;
}

int high(int a, int b)
{
	if (a > b)
		return a;

	return b;
}