#ifndef TIMECRISIS_TUTORIAL
#define TIMECRISIS_TUTORIAL

#include <global_header.h>

namespace CloudberryKingdom
{
	class Challenge_TimeCrisis;
}








namespace CloudberryKingdom
{
	class TimeCrisis_Tutorial : public HeroRush_Tutorial
	{
	private:
		std::shared_ptr<Challenge_TimeCrisis> TimeCrisis;
	public:
		TimeCrisis_Tutorial( const std::shared_ptr<Challenge_TimeCrisis> &TimeCrisis );

	protected:
		virtual void Title();
	};
}


#endif	//#ifndef TIMECRISIS_TUTORIAL
