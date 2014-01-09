#ifndef HERORUSH2
#define HERORUSH2

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Games/GameType.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2_Tutorial.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Game Objects/GameObjects/DoorIcon.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct Challenge_HeroRush2 : public Challenge_HeroRush
	{
	
		virtual ~Challenge_HeroRush2()
		{
#ifdef BOOST_BIN
			OnDestructor( "Challenge_HeroRush2" );
#endif
		}


		struct OnSwapLambda : public Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
		
			boost::shared_ptr<Challenge_HeroRush2> ch;
		
			OnSwapLambda( const boost::shared_ptr<Challenge_HeroRush2> &ch );

			void Apply( const boost::shared_ptr<LevelSeedData> &data );
		};

	
		static std::vector<HeroSpec> HeroList;

	
		static boost::shared_ptr<Challenge_HeroRush2> instance;
	
		const static boost::shared_ptr<Challenge_HeroRush2> &getInstance();

	
		static std::vector<std::vector<Vector2> > IconPos;

		static std::vector<float> IconScale;

        void AdditionalSwap(int levelindex);

		virtual void MakeExitDoorIcon( int levelindex );
	
	
		Challenge_HeroRush2();

		void MakeHeroList();
		void ShuffleHeros();

	
		virtual void Start( int StartLevel );

	
		virtual boost::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef HERORUSH2
