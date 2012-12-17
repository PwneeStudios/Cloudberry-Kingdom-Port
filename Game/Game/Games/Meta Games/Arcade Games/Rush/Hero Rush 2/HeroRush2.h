#ifndef HERORUSH2
#define HERORUSH2

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_HeroRush2 : public Challenge_HeroRush
	{
	
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

	
		virtual void MakeExitDoorIcon( int levelindex );
	
	
		Challenge_HeroRush2();

	
		void ShuffleHeros();

	
		virtual void Start( int StartLevel );

	
		virtual boost::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef HERORUSH2
