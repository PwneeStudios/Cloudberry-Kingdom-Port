#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

class Stopwatch
{

public:

	long long ElapsedTicks;

	struct
	{
		float TotalSeconds;
	} Elapsed;

	Stopwatch()
	{
		ElapsedTicks = 0;
		Elapsed.TotalSeconds = 0;
	}

	void Start()
	{
	}

	void Stop()
	{
	}

};

#endif
