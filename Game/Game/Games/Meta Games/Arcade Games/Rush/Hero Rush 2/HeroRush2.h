#ifndef HERORUSH2
#define HERORUSH2

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_HeroRush2 : public Challenge_HeroRush
	{
	
		struct OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		
			std::shared_ptr<Challenge_HeroRush2> ch;
		
			OnSwapLambda( const std::shared_ptr<Challenge_HeroRush2> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	
		static std::vector<HeroSpec> HeroList;

	
		static const std::shared_ptr<Challenge_HeroRush2> instance;
	
		const static std::shared_ptr<Challenge_HeroRush2> &getInstance();

	
		static std::vector<std::vector<Vector2> > IconPos;

		static std::vector<float> IconScale;

	
		virtual void MakeExitDoorIcon( int levelindex );
	
	
		Challenge_HeroRush2();

	
		void ShuffleHeros();

	
		virtual void Start( int StartLevel );

	
		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual void PreStart_Tutorial( bool TemporarySkip );

	};
}


#endif	//#ifndef HERORUSH2
