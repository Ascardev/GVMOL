#include "sinbaram\sinLinkHeader.h"
#include <strsafe.h>

int GetElementSizeOfSQLType(SQLSMALLINT sql_type)
{
	return 1;
}

SQLColumn::SQLColumn(int _index, string _name, SQLSMALLINT _sql_type, size_t _size) : index(_index), name(_name), sql_type(_sql_type), size(_size)
{
}

SQLBoundColumn::SQLBoundColumn(int _index, string _name, SQLSMALLINT _sql_type, size_t _size) : SQLColumn(_index, _name, _sql_type, _size)
{
	pvBuffer = NULL;
	piIndicator = NULL;

	iBufferSize = GetElementSizeOfSQLType(_sql_type);
}

SQLBoundColumn::~SQLBoundColumn()
{
	DELET(pvBuffer);
	DELET(piIndicator);
}

void SQLBoundColumn::Bind(int _iRows)
{
	iRows = _iRows;

	if (_iRows < 1)
		throw "Rows must be higher than or equal to 1!";

	piIndicator = new SQLLEN[iRows];
}

SQLINTEGER* SQLConnection::BlockNext()
{
	for (int i = 0; i < MAX_PARAMS; i++)
	{
		if (baBlock[i] == false)
		{
			baBlock[i] = true;
			return &iaBlock[i];
		}
	}

	return NULL;
}

void SQLConnection::BlockFree()
{
	for (int i = 0; i < MAX_PARAMS; i++)
		baBlock[i] = false;
}

SQLConnection::SQLConnection(char* pszConnectionString, char* pszDBName)
{
	iDebugMethod = DEBUGMETHOD_Constructor;

	pcMutex = new CMutex("SQLConnection");

	BlockFree();

	bConnected = FALSE;
	bReset = TRUE;
	bBulkSelect = TRUE;

	bOpen = FALSE;
	bPrepared = FALSE;

	StringCchCopyA(szConnectionString, _countof(szConnectionString), pszConnectionString);
	StringCchCopyA(szDBName, _countof(szDBName), pszDBName);
}

SQLConnection::~SQLConnection()
{
	iDebugMethod = DEBUGMETHOD_Destructor;

	if (bConnected)
		Disconnect();

	BlockFree();

	DELET(pcMutex);
}

BOOL SQLConnection::Connect()
{
	iDebugMethod = DEBUGMETHOD_Connect;

	BlockFree();

	SQLINTEGER iLoginTimeOut = 5;

	char szOutConnStr[2048];
	SQLSMALLINT iOutConnStrLen;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	SQLSetConnectAttr(hDbc, SQL_LOGIN_TIMEOUT, &iLoginTimeOut, SQL_IS_INTEGER);

	if ((retcode = SQLDriverConnectA(hDbc, NULL, (SQLCHAR*)szConnectionString, lstrlenA(szConnectionString), (SQLCHAR*)szOutConnStr, _countof(szOutConnStr), &iOutConnStrLen, SQL_DRIVER_NOPROMPT)) == SQL_ERROR)
	{
		Error(SQL_HANDLE_DBC);
		HandleError("ERROR : SQLDriverConnectA(%s) failed!", szConnectionString);

		bConnected = FALSE;
	}
	else
		bConnected = TRUE;

	SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	SQLSetStmtAttr(hStmt, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER)SQL_SCROLLABLE, SQL_IS_INTEGER);

	bReset = TRUE;

	return bConnected;
}

BOOL SQLConnection::Reconnect()
{
	iDebugMethod = DEBUGMETHOD_Reconnect;

	if (bConnected)
		Disconnect();

	return Connect();
}

void SQLConnection::Disconnect()
{
	iDebugMethod = DEBUGMETHOD_Disconnect;

	if (bOpen)
		Close();

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);

	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	bConnected = FALSE;
}

void SQLConnection::Error(char* pszError)
{
	LOGEx("SQL", "ERROR : Method(%d)", iDebugMethod);

	StringCchCopyA(szLastError, _countof(szLastError), pszError);
}

void SQLConnection::Error(SQLSMALLINT iHandleType)
{
	LOGEx("SQL", "ERROR : Method(%d)", iDebugMethod);

	SQLCHAR		szStateStr[256];
	SQLINTEGER	iNativeError;
	SQLCHAR		szMessageText[256];
	SQLSMALLINT	iTextLength;

	switch (iHandleType)
	{
	case SQL_HANDLE_ENV:
		SQLGetDiagRecA(SQL_HANDLE_ENV, hEnv, 1, szStateStr, &iNativeError, szMessageText, _countof(szMessageText), &iTextLength);
		break;
	case SQL_HANDLE_DBC:
		SQLGetDiagRecA(SQL_HANDLE_DBC, hDbc, 1, szStateStr, &iNativeError, szMessageText, _countof(szMessageText), &iTextLength);
		break;
	case SQL_HANDLE_STMT:
		SQLGetDiagRecA(SQL_HANDLE_STMT, hStmt, 1, szStateStr, &iNativeError, szMessageText, _countof(szMessageText), &iTextLength);
		break;
	}

	LOGEx("SQL", "ERROR : SQLConnection::Error(%d) : %d -> %s", iHandleType, iNativeError, szStateStr);
	LOGEx("SQL", "ERROR : Query [%s]", szCurrentQuery);

	bool bAttemptReconnect = false;

	if (iHandleType == SQL_HANDLE_STMT)
	{
		if (((iNativeError == 10054) || (iNativeError == 65534)) && (lstrcmpiA((LPCSTR)szStateStr, "01000") == 0))
			bAttemptReconnect = true;
		else if ((iNativeError == 0) && (lstrcmpiA((LPCSTR)szStateStr, "08S01") == 0))
			bAttemptReconnect = true;
	}

	//if( bAttemptReconnect )
	//{
	//	LOGEx( "SQL", "NOTICE : Attempting to reconnect with SQL Server after error occurred on SQL_HANDLE_STMT: %s [%d]", szStateStr, iNativeError );

	//	if( !Reconnect() )
	//		LOG( "SQL", "ERROR : Reconnect failed!" );
	//	else
	//		LOG( "SQL", "NOTICE : Reconnect successful!" );
	//}
	//else
	LOG("SQL", "NOTICE : No reconnect necessary");

	StringCbPrintfA(szLastError, _countof(szLastError), "[%s][%d][%s]", szStateStr, iNativeError, szMessageText);
}

void SQLConnection::HandleError(char* pszFormat, ...)
{
	va_list vl;

	char szErrorMessage[1024];

	va_start(vl, pszFormat);
	_vsnprintf_s(szErrorMessage, _countof(szErrorMessage), _TRUNCATE, pszFormat, vl);
	va_end(vl);
	StringCchCatA(szErrorMessage, _countof(szErrorMessage), szLastError);

	if (bReset)
		LOGEx("SQL", "ERROR : [SQLConnection is reset] HandleError(%s)", szErrorMessage);
	else
		LOGEx("SQL", "ERROR : HandleError(%s)", szErrorMessage);
}

BOOL SQLConnection::Open(bool bAdditionalSecurity)
{
	bReset = FALSE;

	if (!bConnected)
	{
		Error("SQLConnection::Open()");
		HandleError("ERROR : Open() attempted on disconnected SQLConnection");
		return FALSE;
	}

	pcMutex->Lock(1000 + szDBName[0]);

	iDebugMethod = DEBUGMETHOD_Open;

	this->bAdditionalSecurity = bAdditionalSecurity;
	this->bOpen = TRUE;
	this->bPrepared = FALSE;

	return TRUE;
}

bool SQLConnection::Prepare(char* pszQuery, ...)
{
	iDebugMethod = DEBUGMETHOD_Prepare;

	va_list vl;

	va_start(vl, pszQuery);
	_vsnprintf_s(szCurrentQuery, _countof(szCurrentQuery), _TRUNCATE, pszQuery, vl);
	va_end(vl);

	if (bAdditionalSecurity)
	{
		if (!Check(szCurrentQuery))
		{
			Error("Query not secure");
			return false;
		}
	}

	if ((retcode = SQLPrepareA(hStmt, (SQLCHAR*)szCurrentQuery, SQL_NTS)) == SQL_ERROR)
	{
		Error(SQL_HANDLE_STMT);
		return false;
	}

	bPrepared = TRUE;

	return true;
}

bool SQLConnection::Check(char* pszQuery)
{
	int i = 0;

	do
	{
		char c = pszQuery[i];

		if (c == 0x00)
			break;

		if (c == 0x27)
			return false;

		i++;
	} while (true);

	return true;
}

/**
 * Prepares a Bulk Select, faster than using a while Fetch loop
 *
 * @param iRowsPerFetch number of rows to fetch per FetchScroll
 */
void SQLConnection::BulkSelect(int iRowsPerFetch)
{
	this->bBulkSelect = TRUE;
	this->iRowsPerFetch = iRowsPerFetch;

	SQLSetStmtAttr(hStmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER)iRowsPerFetch, 0);
}

bool SQLConnection::BindCol(int iColumn, EParamType iParamType, void* pvBuffer, int iBufferSize)
{
	switch (iParamType)
	{
	case PARAMTYPE_Integer:

		break;
	}
	return true;
}

bool SQLConnection::BindParameterInput(int iParam, EParamType iParamType, void* pvBuffer, int iBufferSize)
{
	if (!bPrepared)
		return false;

	SYSTEMTIME				sSystemTime;
	SQL_TIMESTAMP_STRUCT	sTimeStamp;

	SQLINTEGER* piInputOutput = BlockNext();

	if (piInputOutput == NULL)
	{
		Error(SQL_HANDLE_STMT);
		HandleError("ERROR : BindParameterInput() failed (piInputOutput NULL: No Free Block)");
		return false;
	}

	switch (iParamType)
	{
	case PARAMTYPE_String:
		*piInputOutput = SQL_NTS;
		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, lstrlenA((char*)pvBuffer), 0, pvBuffer, 0, piInputOutput);
		break;
	case PARAMTYPE_Integer:
		*piInputOutput = 0;
		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, pvBuffer, 0, piInputOutput);
		break;
	case PARAMTYPE_BigInteger:
		*piInputOutput = 0;
		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 0, 0, pvBuffer, 0, piInputOutput);
		break;
	case PARAMTYPE_Time:
		SQLSystemTimeToTimeStamp((SYSTEMTIME*)pvBuffer, &sTimeStamp);

		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &sTimeStamp, 0, NULL);
		break;
	case PARAMTYPE_TimeNow:
		GetLocalTime(&sSystemTime);
		SQLSystemTimeToTimeStamp((SYSTEMTIME*)&sSystemTime, &sTimeStamp);

		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &sTimeStamp, 0, NULL);
		break;
	case PARAMTYPE_TimeSet:
		GetLocalTime(&sSystemTime);
		SQLSystemTimeToTimeStamp((SYSTEMTIME*)&sSystemTime, &sTimeStamp);
		SQLGetDateAddDay(&sTimeStamp, iBufferSize);

		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 23, 3, &sTimeStamp, 0, NULL);
		break;
	case PARAMTYPE_Binary:
		*piInputOutput = iBufferSize;
		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_BINARY, iBufferSize, 0, pvBuffer, 0, piInputOutput);
		break;
	case PARAMTYPE_SmallInteger:
		*piInputOutput = 0;
		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT, 0, 0, pvBuffer, 0, piInputOutput);
		break;
	case PARAMTYPE_TinyInteger:
		*piInputOutput = 0;
		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_STINYINT, SQL_CHAR, 0, 0, pvBuffer, 0, piInputOutput);
		break;
	case PARAMTYPE_Float:
		*piInputOutput = 0;
		retcode = SQLBindParameter(hStmt, iParam, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, pvBuffer, 0, piInputOutput);
		break;
	}

	if (retcode == SQL_ERROR)
	{
		Error(SQL_HANDLE_STMT);
		HandleError("ERROR : BindParameterInput() failed");
		return false;
	}

	return true;
}

bool SQLConnection::Fetch(int iRow)
{
	SQLRETURN iRet;

	if (iRow == -1)
		return ((iRet = SQLFetch(hStmt)) == SQL_SUCCESS ? true : (iRet == SQL_SUCCESS_WITH_INFO ? true : false));
	else
		return ((iRet = SQLFetchScroll(hStmt, SQL_FETCH_ABSOLUTE, iRow)) == SQL_SUCCESS ? true : (iRet == SQL_SUCCESS_WITH_INFO ? true : false));
}

int SQLConnection::FetchScroll()
{
	iRowWheel = 0;

	SQLSetStmtAttr(hStmt, SQL_ATTR_ROWS_FETCHED_PTR, &iRowsFetched, 0);
	SQLSetStmtAttr(hStmt, SQL_ATTR_ROW_STATUS_PTR, piaRowStatus, 0);

	if (SQL_SUCCEEDED(retcode = SQLFetchScroll(hStmt, SQL_FETCH_NEXT, 0)))
		return iRowsFetched;

	Error(SQL_HANDLE_STMT);
	HandleError("ERROR : FetchScroll() failed");

	return -1;
}

bool SQLConnection::Fetch2()
{
	SQLRETURN Result = SQLFetch(hStmt);

	return SQL_SUCCEEDED(Result);
}

bool SQLConnection::GetData(int iParam, EParamType iParamType, void* pvBuffer, int iBufferSize)
{
	SQL_TIMESTAMP_STRUCT	sTimeStamp;

	SQLLEN					iOutput;

	switch (iParamType)
	{
	case PARAMTYPE_String:
		retcode = SQLGetData(hStmt, iParam, SQL_C_CHAR, pvBuffer, iBufferSize, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, iBufferSize);
		break;
	case PARAMTYPE_Integer:
		retcode = SQLGetData(hStmt, iParam, SQL_C_SLONG, pvBuffer, 0, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, sizeof(int));
		break;
	case PARAMTYPE_BigInteger:
		retcode = SQLGetData(hStmt, iParam, SQL_C_UBIGINT, &pvBuffer, 0, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, sizeof(__int64));
		break;
	case PARAMTYPE_Time:
		retcode = SQLGetData(hStmt, iParam, SQL_C_TYPE_TIMESTAMP, &sTimeStamp, 23, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, sizeof(SYSTEMTIME));
		else
			SQLTimeStampToSystemTime(&sTimeStamp, (SYSTEMTIME*)pvBuffer);
		break;
	case PARAMTYPE_Binary:
		retcode = SQLGetData(hStmt, iParam, SQL_C_BINARY, pvBuffer, iBufferSize, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, iBufferSize);
		break;
	case PARAMTYPE_SmallInteger:
		retcode = SQLGetData(hStmt, iParam, SQL_C_SSHORT, pvBuffer, 0, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, sizeof(short));
		break;
	case PARAMTYPE_TinyInteger:
		retcode = SQLGetData(hStmt, iParam, SQL_C_STINYINT, pvBuffer, 0, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, sizeof(char));
		break;
	case PARAMTYPE_Float:
		retcode = SQLGetData(hStmt, iParam, SQL_C_FLOAT, pvBuffer, 0, &iOutput);
		if (iOutput == SQL_NULL_DATA)
			ZeroMemory(pvBuffer, sizeof(float));
		break;
	}

	if (retcode == SQL_ERROR)
	{
		Error(SQL_HANDLE_STMT);
		HandleError("ERROR : GetData() failed");
		return false;
	}

	return true;
}

int SQLConnection::GetLastRow()
{
	int ret = -1;

	if (Prepare("SELECT @@IDENTITY as lastrow"))
		if (Execute())
			if (Fetch())
				GetData(1, PARAMTYPE_Integer, &ret);

	return ret;
}

bool SQLConnection::Execute()
{
	if (!bPrepared)
		return false;

	iDebugMethod = DEBUGMETHOD_Execute;

	if ((retcode = SQLExecute(hStmt)) == SQL_ERROR)
	{
		Error(SQL_HANDLE_STMT);
		return false;
	}

	return true;
}

bool SQLConnection::Execute(char* pszQuery)
{
	iDebugMethod = DEBUGMETHOD_ExecuteDirect;

	if ((retcode = SQLExecDirectA(hStmt, (SQLCHAR*)pszQuery, SQL_NTS)) == SQL_ERROR)
	{
		Error(SQL_HANDLE_STMT);
		return false;
	}

	return true;
}

void SQLConnection::Clear()
{
	iDebugMethod = DEBUGMETHOD_Clear;

	if (bBulkSelect)
	{
		SQLSetStmtAttr(hStmt, SQL_ATTR_ROW_ARRAY_SIZE, (SQLPOINTER)1, 0);

		//TODO

		bBulkSelect = FALSE;
	}

	SQLCancel(hStmt);
	SQLFreeStmt(hStmt, SQL_CLOSE);
	SQLFreeStmt(hStmt, SQL_UNBIND);
	SQLFreeStmt(hStmt, SQL_RESET_PARAMS);

	BlockFree();

	bPrepared = FALSE;
}

void SQLConnection::Close()
{
	if (bReset)
		LOG("SQL", "NOTICE : SQLConnection::Close() called while SQLConnection in reset mode");

	Clear();

	iDebugMethod = DEBUGMETHOD_Close;

	bOpen = FALSE;

	pcMutex->Unlock();
}

BOOL SQLConnection::IsSafeUserInput(const char* pszInput)
{
	int iLen = lstrlenA(pszInput);

	for (int i = 0; i < iLen; i++)
	{
		char c = pszInput[i];

		if (c == '\'')
			return FALSE;
	}

	return TRUE;
}