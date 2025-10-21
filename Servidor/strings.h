#pragma once

#define STRINGEMPTY( dest )				{ ZeroMemory( dest, sizeof( dest ) ); };

#define STRINGCOPY( dest, src )			{ StringCchCopyA( dest, _countof( dest ), src ); };
#define STRINGCOPYLEN( dest, len, src )	{ StringCchCopyA( dest, len, src ); };

#define STRINGFORMAT( dest, fmt, ... )	{ StringCbPrintfA( dest, _countof( dest ), fmt, ##__VA_ARGS__ ); };

#define STRINGCONCAT( dest, src )		{ StringCchCatA( dest, _countof( dest ), src ); };

#define STRINGCOMPARE( str1, str2 )		(lstrcmpA( str1, str2 ) == 0)
#define STRINGCOMPAREI( str1, str2 )	(lstrcmpiA( str1, str2 ) == 0)

int nstr(const char* s);
int nstr_s(const char* s, int l);
void clrstr(char* str);
int lstrnlenA(char* pszString, int iMaxLen);
bool lstrncmpA(char* pszString1, char* pszString2, int iNum);
bool lstrncmpiA(char* pszString1, char* pszString2, int iNum);
void upper(char* pszString);
void upper(char& chr);
void lower(char* pszString);
bool strcontains(char* pszString, char* pszContains);
char* NumberToString(__int64 iNum);

int low(int a, int b);
int high(int a, int b);