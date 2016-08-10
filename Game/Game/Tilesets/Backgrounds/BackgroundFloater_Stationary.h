#ifndef BACKGROUNDFLOATER_STATIONARY
#define BACKGROUNDFLOATER_STATIONARY

#include <small_header.h>

#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
//#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BackgroundFloater_Stationary : public BackgroundFloater
	{

		virtual ~BackgroundFloater_Stationary()
		{
#ifdef BOOST_BIN
			OnDestructor( "BackgroundFloater_Stationary" );
#endif
		}


		BackgroundFloater_Stationary( const boost::shared_ptr<Level> &level );

		virtual void PhsxStep( const boost::shared_ptr<BackgroundFloaterList> &list );

		virtual void Draw();

	};

}


#endif	//#ifndef BACKGROUNDFLOATER_STATIONARY
