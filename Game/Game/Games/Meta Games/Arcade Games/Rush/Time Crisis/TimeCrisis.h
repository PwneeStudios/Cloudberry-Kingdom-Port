#ifndef TIMECRISIS
#define TIMECRISIS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_TimeCrisis : public Challenge_HeroRush
	{

	
		static void InitializeStatics();

	
		struct OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		
			std::shared_ptr<Challenge_TimeCrisis> ch;
		
			OnSwapLambda( const std::shared_ptr<Challenge_TimeCrisis> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};
	
		static std::shared_ptr<Challenge_TimeCrisis> instance;
	
		const static std::shared_ptr<Challenge_TimeCrisis> &getInstance();

	
		Challenge_TimeCrisis();

	
		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef TIMECRISIS
