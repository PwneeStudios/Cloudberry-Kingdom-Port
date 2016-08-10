#ifndef SINGLEDATA
#define SINGLEDATA

#include <small_header.h>

//#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"


namespace CloudberryKingdom
{
	struct Rand;
}




namespace CloudberryKingdom
{
	struct SingleData : public StyleData
	{
	
		virtual ~SingleData()
		{
#ifdef BOOST_BIN
			OnDestructor( "SingleData" );
#endif
		}


		Vector2 InitialDoorYRange;

		SingleData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SINGLEDATA
