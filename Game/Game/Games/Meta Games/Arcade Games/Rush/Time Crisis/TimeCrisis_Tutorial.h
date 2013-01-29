#ifndef TIMECRISIS_TUTORIAL
#define TIMECRISIS_TUTORIAL

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_TimeCrisis;
}



namespace CloudberryKingdom
{
	struct TimeCrisis_Tutorial : public HeroRush_Tutorial
	{
	
		virtual ~TimeCrisis_Tutorial() { }

		boost::shared_ptr<Challenge_TimeCrisis> TimeCrisis;
	
		TimeCrisis_Tutorial( const boost::shared_ptr<Challenge_TimeCrisis> &TimeCrisis );

	
		virtual void Title();
	};
}


#endif	//#ifndef TIMECRISIS_TUTORIAL
