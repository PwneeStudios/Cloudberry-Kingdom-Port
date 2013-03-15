#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <ctime>
#include <Utility\Log.h>

struct Random
{

	int MBIG;
	int MSEED;
	int MZ;
	int inext;
	int inextp;
	int SeedArray[56];

public:
	Random() :
		MBIG( 2147483647 ),
		MSEED( 161803398 ),
		MZ( 0 ),
		inext( 0 ),
		inextp( 0 )
	{
		time_t t;
		time( &t );

		LOG.Write( "Time is %d\n", t );
		int time_seed = static_cast<int>( t ) % 10000;

		//initialize( 'rofl' );
		initialize( t );
	}

	Random( int seed ) :
		MBIG( 2147483647 ),
		MSEED( 161803398 ),
		MZ( 0 ),
		inext( 0 ),
		inextp( 0 )
	{
		initialize( seed );
	}

private:

	void initialize( int Seed )
	{
#ifdef CAFE
		Seed += 1;
#endif

		LOG.Write( "Random Seed is %d\n", Seed );

		int num = /*( Seed == -2147483648 ) ? 2147483647 : */abs(Seed);
		int num2 = 161803398 - num;

		SeedArray[55] = num2;
		int num3 = 1;
		for (int i = 1; i < 55; i++)
		{
			int num4 = 21 * i % 55;
			SeedArray[num4] = num3;
			num3 = num2 - num3;
			if (num3 < 0)
			{
				num3 += 2147483647;
			}
			num2 = SeedArray[num4];
		}
		for (int j = 1; j < 5; j++)
		{
			for (int k = 1; k < 56; k++)
			{
				SeedArray[k] -= SeedArray[1 + (k + 30) % 55];
				if (SeedArray[k] < 0)
				{
					SeedArray[k] += 2147483647;
				}
			}
		}
		inext = 0;
		inextp = 21;
		Seed = 1;
	}

	double GetSampleForLargeRange()
	{
		int num = InternalSample();
		bool flag = InternalSample() % 2 == 0;
		if (flag)
		{
			num = -num;
		}
		double num2 = (double)num;
		num2 += 2147483646.0;
		return num2 / 4294967293.0;
	}

	int InternalSample()
	{
		int num = inext;
		int num2 = inextp;
		if (++num >= 56)
		{
			num = 1;
		}
		if (++num2 >= 56)
		{
			num2 = 1;
		}
		int num3 = SeedArray[num] - SeedArray[num2];
		if (num3 == 2147483647)
		{
			num3--;
		}
		if (num3 < 0)
		{
			num3 += 2147483647;
		}
		SeedArray[num] = num3;
		inext = num;
		inextp = num2;
		return num3;
	}

public:
	int Next()
	{
		return InternalSample();
	}

	int Next( int low, int high )
	{
		if (low > high)
			return -1;

		long num = (long)high - (long)low;
		if (num <= 2147483647L)
		{
			return (int)(Sample() * (double)num) + low;
		}
		return (int)((long)(GetSampleForLargeRange() * (double)num) + (long)low);
	}

	int Next( int high )
	{
		if (high < 0)
			return -1;

		return (int)(Sample() * (double)high);
	}

	double NextDouble()
	{
		return Sample();
	}

private:
	double Sample()
	{
		return (double)InternalSample() * 4.6566128752457969E-10;
	}

};

#endif
