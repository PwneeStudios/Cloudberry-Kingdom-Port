#ifndef _DATETIME_H_
#define _DATETIME_H_

#include "Hacks/NET/TimeSpan.h"

struct DateTime
{


	int Time;

	DateTime() : Time( 0 )
	{
	}

	DateTime( int year, int month, int day )
	{
	}

	static DateTime Now()
	{
		// FIXME: return the current date
		return DateTime(0, 0, 0);
	}

};

static TimeSpan operator - ( DateTime dt1, DateTime dt2 )
{
	// FIXME: Implement
	return TimeSpan();
}

#endif
