#ifndef TIMECRISIS_TUTORIAL
#define TIMECRISIS_TUTORIAL

#include <small_header.h>

#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
//#include "Game/Objects/Game Objects/GameObjects/Listener.h"


namespace CloudberryKingdom
{
	struct Challenge_TimeCrisis;
}



namespace CloudberryKingdom
{
	struct TimeCrisis_Tutorial : public HeroRush_Tutorial
	{
	
		virtual ~TimeCrisis_Tutorial()
		{
#ifdef BOOST_BIN
			OnDestructor( "TimeCrisis_Tutorial" );
#endif
		}


		boost::shared_ptr<Challenge_TimeCrisis> TimeCrisis;
	
		TimeCrisis_Tutorial( const boost::shared_ptr<Challenge_TimeCrisis> &TimeCrisis );

	
		virtual void Title();
	};
}


#endif	//#ifndef TIMECRISIS_TUTORIAL
