













#ifndef __CSAUTH_H__
#define __CSAUTH_H__



#if !defined(_WINDEF_) && !defined(_TYPEDEF_)

#define _TYPEDEF_

typedef void*          LPVOID;
typedef unsigned long  DWORD;
typedef unsigned short WORD;
typedef unsigned char  BYTE;
typedef const char*    LPCSTR;
typedef DWORD*         LPDWORD;

#endif

#define CSAUTH_TABLE_SIZE     (8 * 5)


#if !defined(_WIN32)
#define __cdecl
#endif

#define CSAUTH_EXPORT   extern "C"


#ifdef __cplusplus
extern "C" {
#endif


DWORD __cdecl LoadAuthTable(LPCSTR lpszPath);
DWORD __cdecl LoadAuthIndex(LPCSTR lpszPath);
DWORD __cdecl SetAuthTable(LPBYTE lpTable, DWORD dwSize);
DWORD __cdecl SetAuthIndex(DWORD dwIndex);
DWORD __cdecl InitPacketProtect(LPCSTR lpszUserKey, DWORD dwUseSeqCheck);

#ifdef __cplusplus
}
#endif



class CCSAuth
{
public:
   
   CCSAuth();

   
   ~CCSAuth();

   
   void Init();
   DWORD IsAuth();
   DWORD GetAuthDword();
   DWORD CheckAuthDword(DWORD dwReturnValue);
   DWORD GetAuthResults(DWORD dwAuthValue, LPDWORD lpdwResult, DWORD dwCount);
   DWORD EncryptPacket(LPVOID lpData, DWORD dwLength);
   DWORD DecryptPacket(LPVOID lpData, DWORD dwLength);
   DWORD PPGetLastError();

protected:
   DWORD TransAuthDword(DWORD dwAuth, int index);
   void np_srandom(DWORD initial_seed);
   DWORD np_random();
   DWORD CheckLastPacket(DWORD dwSeq);

private:
   
   CCSAuth(const CCSAuth &rhs);
   CCSAuth &operator=(const CCSAuth &rhs);

private:
   DWORD m_dwSeed;
   DWORD m_dwAuthValue;
   DWORD m_bAuth;
   DWORD m_dwCurrIndex;
   char  m_table[8][5];
   DWORD m_dwClientSequenceNumber;
   DWORD m_dwServerSequenceNumber;
   DWORD m_adwLastSeqs[12];
   DWORD m_dwPPLastError;

};


#endif 

