#include "..\\nettype.hpp"

struct	ODBC_CONFIG {
	char	Dsn[32];
	char	Name[32];
	char	Password[32];

	char	Table[32];
	char	Table_Id[32];
	int		Table_Password;
	int		Table_Play;

	int		CloseAccount;
};

extern	ODBC_CONFIG	Odbc_Config;

int SqlLogOn(char* szID, char* szPass);
