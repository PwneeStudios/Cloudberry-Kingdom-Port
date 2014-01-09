#ifndef DOWNDATA
#define DOWNDATA

#include <small_header.h>

//#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/UpData.h"


namespace CloudberryKingdom
{
	struct Rand;
}


namespace CloudberryKingdom
{
	struct DownData : public VerticalData
	{
	
		virtual ~DownData()
		{
#ifdef BOOST_BIN
			OnDestructor( "DownData" );
#endif
		}


		virtual void CalculateKeepUnused( float JumpLevel );

	
		DownData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef DOWNDATA
