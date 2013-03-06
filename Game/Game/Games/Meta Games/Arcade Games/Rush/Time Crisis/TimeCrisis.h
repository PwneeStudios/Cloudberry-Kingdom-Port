#ifndef TIMECRISIS
#define TIMECRISIS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_TimeCrisis : public Challenge_HeroRush
	{

		virtual ~Challenge_TimeCrisis() { }
	
		static void InitializeStatics();

	
		struct OnSwapLambda : public Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
		
			boost::shared_ptr<Challenge_TimeCrisis> ch;
		
			OnSwapLambda( const boost::shared_ptr<Challenge_TimeCrisis> &ch );

			void Apply( const boost::shared_ptr<LevelSeedData> &data );
		};
	
		static boost::shared_ptr<Challenge_TimeCrisis> instance;
	
		const static boost::shared_ptr<Challenge_TimeCrisis> &getInstance();

	
		Challenge_TimeCrisis();

	
		virtual boost::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );


		virtual int GetLength( int Index, float Difficulty );
		virtual boost::shared_ptr<LevelSeedData> Make( int Index, float Difficulty );

		virtual void Start(int StartLevel);
	};
}


#endif	//#ifndef TIMECRISIS
