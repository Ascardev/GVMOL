#include "sinbaram\sinLinkHeader.h"

int aDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int GetDaysInMonth(int year, int month)
{
	if ((month <= 0) || (month > 12))
		return 0;

	if ((((year % 100) != 0) || ((year % 400 == 0)) && (month == 2)))
		return 29;
	else
		return aDaysInMonth[month - 1];
}

bool IsEqualSystemTimeMinute(SYSTEMTIME* one, SYSTEMTIME* two)
{
	if (one->wYear == two->wYear)
	{
		if (one->wMonth == two->wMonth)
		{
			if (one->wDay == two->wDay)
			{
				if (one->wMinute == two->wMinute)
					return true;
			}
		}
	}

	return false;
}

void SQLTimeStampToSystemTime(SQL_TIMESTAMP_STRUCT* in, SYSTEMTIME* out)
{
	out->wYear = in->year;
	out->wMonth = in->month;
	out->wDay = in->day;
	out->wHour = in->hour;
	out->wMinute = in->minute;
	out->wSecond = in->second;
	out->wMilliseconds = 0;
}

void SQLSystemTimeToTimeStamp(SYSTEMTIME* in, SQL_TIMESTAMP_STRUCT* out)
{
	out->year = in->wYear;
	out->month = in->wMonth;
	out->day = in->wDay;
	out->hour = in->wHour;
	out->minute = in->wMinute;
	out->second = in->wSecond;
	out->fraction = 0;
}

void SQLGetDateAddDay(SQL_TIMESTAMP_STRUCT* out, int iDays)
{
	SYSTEMTIME sSystemTime;
	GetLocalTime(&sSystemTime);

	if (iDays != 0)
	{
		FILETIME sFileTime;
		SystemTimeToFileTime(&sSystemTime, &sFileTime);

		ULONGLONG qwResult;
		qwResult = (((ULONGLONG)sFileTime.dwHighDateTime) << 32) + sFileTime.dwLowDateTime;

		qwResult += (iDays * _DAY);

		sFileTime.dwLowDateTime = (DWORD)(qwResult & 0xFFFFFFFF);
		sFileTime.dwHighDateTime = (DWORD)(qwResult >> 32);

		FileTimeToSystemTime(&sFileTime, &sSystemTime);
	}

	out->year = sSystemTime.wYear;
	out->month = sSystemTime.wMonth;
	out->day = sSystemTime.wDay;
	out->hour = sSystemTime.wHour;
	out->minute = sSystemTime.wMinute;
	out->second = sSystemTime.wSecond;
	out->fraction = 0;
}