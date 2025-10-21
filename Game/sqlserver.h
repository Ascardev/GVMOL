#pragma once

#define NUM_DATABASES	2

enum EDatabase
{
	DATABASE_PristonDB = 0,
	DATABASE_ClanDB = 1,
};

extern char* pszDBNameDBPriston;
extern char* pszDBNameDBClan;

#define SQLCONNECTION(d)	SQLManager::GetInstance()->GetSQLConnection(d)

class SQLManager
{
private:
	static SQLManager* pcInstance;

	string				  sDBConnectionString;
	string				  sDBDriver;
	string				  sDBHost;
	string				  sDBUser;
	string				  sDBPass;

	char				  szFormattedConnectionString[256];

	SQLConnection* caSQLConnection[NUM_DATABASES];
public:
	static void			  CreateInstance() { pcInstance = new SQLManager(); };
	static SQLManager* GetInstance() { return pcInstance; };
	static void			  DeleteInstance() { delete pcInstance; };

	SQLManager();
	~SQLManager();

	void				  Load();
	void				  UnLoad();

	SQLConnection* SQLManager::CreateSQLConnection(char* pszDatabase);
	char* FormatConnectionString(char* pszDatabase);

	void				  AddSQLConnection(SQLConnection* pcSQLConnection, EDatabase iDB) { caSQLConnection[iDB] = pcSQLConnection; };
	SQLConnection* GetSQLConnection(EDatabase iDB) { return caSQLConnection[iDB]; };
	void				  DelSQLConnection(EDatabase iDB) { delete caSQLConnection[iDB]; };
};