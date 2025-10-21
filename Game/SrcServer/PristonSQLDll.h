#ifdef PRISTONSQLDLL_EXPORTS
#define PRISTONSQLDLL_API __declspec(dllexport)
#else
#define PRISTONSQLDLL_API __declspec(dllimport)
#endif

PRISTONSQLDLL_API int SQLLoginProcess(char* lpUserID);

PRISTONSQLDLL_API int SQLAddCharProcess(char* lpUserID, char* lpCharID);

PRISTONSQLDLL_API int SQLDelCharProcess(char* lpUserID, char* lpCharID);

PRISTONSQLDLL_API int SQLLogoutProcess(char* lpUserID, char* lpCharID, char* lpRace, char* lpOccupation, unsigned long nExpPoint, int nLevel);
