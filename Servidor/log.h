void LOG(rsPLAYINFO* pcUser, char* pszLog, char* pszMessage);
inline void LOG(char* pszLog, char* pszMessage) { LOG(NULL, pszLog, pszMessage); };
void LOGEx(rsPLAYINFO* pcUser, char* pszLog, char* pszFormat, ...);
void LOGEx(char* pszLog, char* pszFormat, ...);
