#ifndef HERORUSH2_TUTORIAL
#define HERORUSH2_TUTORIAL

#include <global_header.h>

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
