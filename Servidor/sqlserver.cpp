#include "sinbaram\sinLinkHeader.h"
#include <strsafe.h>

char* pszDBNameDBPriston = "PristonDB";
char* pszDBNameDBClan = "ClanDB";

SQLManager* SQLManager::pcInstance = NULL;

SQLManager::SQLManager()
{
}

SQLManager::~SQLManager()
{
}

void SQLManager::Load()
{
	//Load Settings
	CConfigFileReader* pcConfigFileReader = new CConfigFileReader("server.ini");
	if (pcConfigFileReader->Open())
	{
		sDBConnectionString = "Persist Security Info=False; Integrated Security=False; Driver=%s; Server=%s; Database=%s; Uid=%s; Pwd=%s;";

		sDBDriver = pcConfigFileReader->ReadString("Database", "Driver");
		sDBHost = pcConfigFileReader->ReadString("Database", "Host");
		sDBUser = pcConfigFileReader->ReadString("Database", "User");
		sDBPass = pcConfigFileReader->ReadString("Database", "Pass");

		pcConfigFileReader->Close();
	}
	DELET(pcConfigFileReader);

	//Create SQL Connections
	AddSQLConnection(CreateSQLConnection(pszDBNameDBPriston), DATABASE_PristonDB);
	AddSQLConnection(CreateSQLConnection(pszDBNameDBPriston), DATABASE_ClanDB);

	//Connect
	GetSQLConnection(DATABASE_PristonDB)->Connect();
	GetSQLConnection(DATABASE_ClanDB)->Connect();
}

void SQLManager::UnLoad()
{
	DelSQLConnection(DATABASE_PristonDB);
}

SQLConnection* SQLManager::CreateSQLConnection(char* pszDatabase)
{
	char* pszConnectionString = FormatConnectionString(pszDatabase);

	SQLConnection* r = new SQLConnection(pszConnectionString, pszDatabase);

	clrstr(pszConnectionString);

	return r;
}

char* SQLManager::FormatConnectionString(char* pszDatabase)
{
	if (StringCbPrintfA(szFormattedConnectionString, _countof(szFormattedConnectionString), sDBConnectionString.c_str(), sDBDriver.c_str(), sDBHost.c_str(), pszDatabase, sDBUser.c_str(), sDBPass.c_str()) != S_OK)
	{
		MessageBoxA(NULL, "A fatal error occured!\n\nThe application must close.", "Fatal Error", MB_OK);
		ExitProcess(-1);
	}

	return szFormattedConnectionString;
}