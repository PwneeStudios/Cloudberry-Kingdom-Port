#ifndef HERORUSH2_TUTORIAL
#define HERORUSH2_TUTORIAL

#include <small_header.h>

//#include "Game/Localization.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
//#include "Game/Objects/Game Objects/GameObjects/Listener.h"


namespace CloudberryKingdom
{
	struct Challenge_HeroRush2;
}



namespace CloudberryKingdom
{
	struct HeroRush2_Tutorial : public HeroRush_Tutorial
	{
	
		virtual ~HeroRush2_Tutorial()
		{
#ifdef BOOST_BIN
			OnDestructor( "HeroRush2_Tutorial" );
#endif
		}


		boost::shared_ptr<Challenge_HeroRush2> HeroRush2;
	
		HeroRush2_Tutorial( const boost::shared_ptr<Challenge_HeroRush2> &HeroRush2 );

	
		virtual void Title();
	};
}


#endif	//#ifndef HERORUSH2_TUTORIAL
