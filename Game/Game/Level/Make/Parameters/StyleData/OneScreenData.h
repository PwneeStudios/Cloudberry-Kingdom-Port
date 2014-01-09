#ifndef ONESCREENDATA
#define ONESCREENDATA

#include <small_header.h>

//#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"


namespace CloudberryKingdom
{
	struct OneScreenData : public StyleData
	{
	
		virtual ~OneScreenData()
		{
#ifdef BOOST_BIN
			OnDestructor( "OneScreenData" );
#endif
		}


		Vector2 CamShift;

		OneScreenData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	
		void InitializeInstanceFields();
	};
}

#endif	//#ifndef ONESCREENDATA
