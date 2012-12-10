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
	
		std::shared_ptr<Challenge_HeroRush2> HeroRush2;
	
		HeroRush2_Tutorial( const std::shared_ptr<Challenge_HeroRush2> &HeroRush2 );

	
		virtual void Title();
	};
}


#endif	//#ifndef HERORUSH2_TUTORIAL
