#ifndef _DATETIME_H_
#define _DATETIME_H_

#include "Hacks/NET/TimeSpan.h"

#include <ctime>

struct DateTime
{

	int Time;

	DateTime() : Time( 0 )
	{
	}

	DateTime( int year, int month, int day ) : Time( 0 )
	{
	}

	static DateTime Now()
	{
		//return DateTime(0, 0, 0);

		DateTime d;
		d.Time = static_cast<int>( time(0) );
		
		return d;
	}

};

static TimeSpan operator - ( DateTime dt1, DateTime dt2 )
{
	TimeSpan t;
	//t.TotalSeconds = static_cast<float>( dt1.Time - dt2.Time ) / CLOCKS_PER_SEC;
	t.TotalSeconds = static_cast<float>( dt1.Time - dt2.Time );
	
	return t;
}

#endif
