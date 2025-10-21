/*****************************************************
 * sql.h sql.cpp
 *
 * SQL Connection Class v1.3
 * Made by Sandurr
 *
 * Easy to manage, simple and safe use of SQL in C++
 *
 * Version control:
 * 1.0 : Initial Release
 * 1.1 : Performance Upgrade
 * 1.2 : Reconnect Ability
 * 1.3 : Bulk Select Ability (BindCol & FetchScroll)
 * 1.4 : Replaced Critical Section with Mutex
 *****************************************************/
#pragma once

#include <sqltypes.h>
#include <sqlext.h>
#include "CMutex.h"
#include "date.h"

#define MAX_PARAMS		10000
#define MAX_QUERY_SIZE	2048

enum EParamType
{
	PARAMTYPE_String = 0,
	PARAMTYPE_Integer = 1,
	PARAMTYPE_BigInteger = 2,
	PARAMTYPE_Time = 3,
	PARAMTYPE_TimeNow = 4,
	PARAMTYPE_TimeSet = 5,
	PARAMTYPE_Binary = 6,
	PARAMTYPE_SmallInteger = 7,
	PARAMTYPE_TinyInteger = 8,
	PARAMTYPE_Float = 9
};

enum EDebugMethod
{
	DEBUGMETHOD_None = 0,
	DEBUGMETHOD_Constructor = 1,
	DEBUGMETHOD_Destructor = 2,
	DEBUGMETHOD_Connect = 11,
	DEBUGMETHOD_Reconnect = 12,
	DEBUGMETHOD_Disconnect = 13,
	DEBUGMETHOD_Open = 21,
	DEBUGMETHOD_Clear = 22,
	DEBUGMETHOD_Close = 23,
	DEBUGMETHOD_Prepare = 31,
	DEBUGMETHOD_Execute = 41,
	DEBUGMETHOD_ExecuteDirect = 42,
};

class SQLFetchedRow
{
private:

public:
	SQLFetchedRow();
	virtual				 ~SQLFetchedRow();
};

class SQLColumn
{
protected:
	int					  index;	//Column Index
	string				  name;		//Column Name
	SQLSMALLINT			  sql_type;	//Data Type of Column
	size_t				  size;		//Size of Column (i.e. varchar() size)

public:
	SQLColumn(int _index, string _name, SQLSMALLINT _sql_type, size_t _size = 0);
	virtual				 ~SQLColumn() {}

	string				  GetName() { return name; }
	SQLSMALLINT			  GetSQLType() { return sql_type; }
	size_t				  GetSize() { return size; }
};

/**
 * class SQLBoundColumn
 * inherits SQLColumn
 *
 * Friend class with SQLConnection for the ability to use SQLBindCol on data buffers
 *
 * Used to retrieve bulk data from a SELECT SQL statement
 *
 *
 *
 */
class SQLBoundColumn : public SQLColumn
{
	friend class SQLConnection;

protected:
	int					  iRows;
	void* pvBuffer;
	int					  iBufferSize;
	SQLLEN* piIndicator;

public:
	SQLBoundColumn(int _index, string _name, SQLSMALLINT _sql_type, size_t _size = 0);
	virtual				 ~SQLBoundColumn();

	void				  Bind(int _iRows);
};

/**
 * class SQLConnection
 *
 * Manages 1 SQL connection with a (remote) SQL server
 *
 */
class SQLConnection
{
private:
	BOOL				  bNoOpen;		//TRUE will let SQLConnection::Open(...) always fail
	BOOL				  bConnected;	//TRUE if connected
	BOOL				  bReset;		//TRUE if connection was reset within Open() -> Close() tags
	char				  szConnectionString[256];	//The Connection String
	char				  szDBName[64];

	SQLHENV				  hEnv;
	SQLHDBC				  hDbc;
	SQLHSTMT			  hStmt;
	CMutex* pcMutex;
	char				  szLastError[256];
	SQLRETURN			  retcode;

	BOOL				  bOpen;
	BOOL				  bPrepared;

	bool				  baBlock[MAX_PARAMS];
	SQLINTEGER			  iaBlock[MAX_PARAMS];
	SQLINTEGER* BlockNext();
	void				  BlockFree();

	BOOL				  bBulkSelect;
	int					  iRowsPerFetch;
	int					  iRowsFetched;
	int					  iRowWheel;
	SQLUSMALLINT* piaRowStatus;

	bool				  bAdditionalSecurity;
	char				  szCurrentQuery[MAX_QUERY_SIZE];

	EDebugMethod		  iDebugMethod;
public:
	SQLConnection(char* pszConnectionString, char* pszDBName);
	virtual				 ~SQLConnection();

	BOOL				  Connect();
	BOOL				  Reconnect();
	void				  Disconnect();

	void				  Error(char* pszError);
	void				  Error(SQLSMALLINT iHandleType);
	void				  HandleError(char* pszFormat, ...);

	BOOL				  Open(bool bAdditionalSecurity = false);

	bool				  Prepare(char* pszQuery, ...);
	bool				  Check(char* pszQuery);
	void				  BulkSelect(int iRowsPerFetch);

	bool				  BindCol(int iColumn, EParamType iParamType, void* pvBuffer, int iBufferSize);
	bool				  BindParameterInput(int iParam, EParamType iParamType, void* pvBuffer = NULL, int iBufferSize = 0);

	bool				  Fetch(int iRow = -1);
	bool                  Fetch2();
	int					  FetchScroll();

	bool				  GetData(int iParam, EParamType iParamType, void* pvBuffer = NULL, int iBufferSize = 0);
	int					  GetLastRow();

	bool				  Execute();
	bool				  Execute(char* pszQuery);

	void				  Clear();
	void				  Close();

	static BOOL			  IsSafeUserInput(const char* pszInput);
};