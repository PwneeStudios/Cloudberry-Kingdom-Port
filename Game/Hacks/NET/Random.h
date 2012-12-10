#ifndef _RANDOM_H_
#define _RANDOM_H_

class Random
{

public:
	Random()
	{
	}

	Random( int seed )
	{
	}

	int Next()
	{
		// FIXME: get a random number generator!
		return 0;
	}

	int Next( int low, int high )
	{
		return 0;
	}

	int Next( int high )
	{
		return Next( 0, high );
	}

	double NextDouble()
	{
		return 0;
	}

};

#endif
