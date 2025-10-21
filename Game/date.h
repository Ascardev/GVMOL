#pragma once

#define _SECOND ((__int64) 1000000)
#define _MINUTE (60 * _SECOND)
#define _HOUR   (60 * _MINUTE)
#define _DAY    (24 * _HOUR)

int		GetDaysInMonth(int year, int month);
bool	IsEqualSystemTimeMinute(SYSTEMTIME* one, SYSTEMTIME* two);
void	SQLTimeStampToSystemTime(SQL_TIMESTAMP_STRUCT* in, SYSTEMTIME* out);
void	SQLSystemTimeToTimeStamp(SYSTEMTIME* in, SQL_TIMESTAMP_STRUCT* out);
void	SQLGetDateAddDay(SQL_TIMESTAMP_STRUCT* out, int iDays = 0);