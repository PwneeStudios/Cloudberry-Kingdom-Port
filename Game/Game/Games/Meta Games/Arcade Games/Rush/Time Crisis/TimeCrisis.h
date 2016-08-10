#ifndef TIMECRISIS
#define TIMECRISIS

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis_Tutorial.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Player/Hero Physics/Rocketbox.h"


namespace CloudberryKingdom
{
	struct Challenge_TimeCrisis : public Challenge_HeroRush
	{

		virtual ~Challenge_TimeCrisis()
		{
#ifdef BOOST_BIN
			OnDestructor( "Challenge_TimeCrisis" );
#endif
		}

	
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
