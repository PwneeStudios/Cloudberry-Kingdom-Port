#ifndef BIGDATA
#define BIGDATA

#include <small_header.h>

//#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"


namespace CloudberryKingdom
{
	struct Rand;
}


namespace CloudberryKingdom
{
	struct BigData : public StyleData
	{
	
		virtual ~BigData()
		{
#ifdef BOOST_BIN
			OnDestructor( "BigData" );
#endif
		}


		BigData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef BIGDATA
