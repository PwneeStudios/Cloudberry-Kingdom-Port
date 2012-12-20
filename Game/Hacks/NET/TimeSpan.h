#ifndef _TIMESPAN_H_
#define _TIMESPAN_H_

struct TimeSpan
{


	float TotalMinutes;
	float TotalSeconds;
	int Hours;
	int Minutes;
	int Seconds;

	TimeSpan() :
		TotalMinutes( 0 ),
		TotalSeconds( 0 ),
		Hours( 0 ),
		Minutes( 0 ),
		Seconds( 0 )
	{
	}

	TimeSpan( int hours, int minutes, int seconds) :
		TotalMinutes( hours * 60.f + minutes + seconds / 60.f ),
		TotalSeconds( hours * 3600.f + minutes * 60.f + seconds ),
		Hours( hours ),
		Minutes( minutes ),
		Seconds( seconds )
	{
	}

	float getTotalSeconds()
	{
		return TotalSeconds;
	}

	float getTotalMilliseconds()
	{
		return getTotalSeconds() * 1000.f;
	}

};

#endif
