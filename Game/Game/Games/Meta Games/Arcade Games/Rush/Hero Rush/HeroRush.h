#ifndef HERORUSH
#define HERORUSH

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/CoinMod.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Rush.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
//#include "Game/Games/Meta Games/Challenges/_Regular.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Game Objects/GameObjects/DoorIcon.h"
//#include "Game/Objects/Game Objects/GameObjects/MultiplierUp.h"
//#include "Game/Objects/Game Objects/GameObjects/SuperCheer.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/Big.h"
//#include "Game/Player/Hero Physics/Bouncy.h"
//#include "Game/Player/Hero Physics/Box.h"
//#include "Game/Player/Hero Physics/Double.h"
//#include "Game/Player/Hero Physics/Jetman.h"
//#include "Game/Player/Hero Physics/Rocketbox.h"
//#include "Game/Player/Hero Physics/Small.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Player/Hero Physics/Wheel.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct Challenge_HeroRush : public Rush
	{

		virtual ~Challenge_HeroRush()
		{
#ifdef BOOST_BIN
			OnDestructor( "Challenge_HeroRush" );
#endif
		}

	
		static void InitializeStatics();

	
		struct OnSwapLambda : public Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
		
			boost::shared_ptr<Challenge_HeroRush> ch;
		
			OnSwapLambda( const boost::shared_ptr<Challenge_HeroRush> &ch );

			void Apply( const boost::shared_ptr<LevelSeedData> &data );
		};

	
		struct ScoreMultiplierHelper : public Lambda_1<boost::shared_ptr<GameData> >
		{
		
			float multiplier;

		
			ScoreMultiplierHelper( float multiplier );

			void Apply( const boost::shared_ptr<GameData> &game );
		};

	
		struct AdditionalPreStartOnSwapToLevelHelper : public Lambda_1<int>
		{
		
			boost::shared_ptr<Challenge_HeroRush> chr;

		
			AdditionalPreStartOnSwapToLevelHelper( const boost::shared_ptr<Challenge_HeroRush> &chr );

			void Apply( const int &levelindex );
		};

	
		struct MakeMyModParamsHelper : public Lambda_2<boost::shared_ptr<Level> , boost::shared_ptr<PieceSeedData> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p );
		};

	
		static boost::shared_ptr<Challenge_HeroRush> instance;
	
		const static boost::shared_ptr<Challenge_HeroRush> &getInstance();

	
		Challenge_HeroRush();

		// The progression of max time and start time for increasing difficulty
	
		static std::vector<int> MaxTime_ByDifficulty;
		static std::vector<int> StartTime_ByDifficulty;

		void SetTimerProperties( int Difficulty );

	
		virtual void PreStart_Tutorial( bool TemporarySkip );

		virtual void MakeExitDoorIcon( int levelindex );

	
		int LevelsPerDifficulty;
	
		virtual void AdditionalSwap(int levelindex);

		virtual void AdditionalPreStart();

	
		void OnSwapTo_GUI( int levelindex );

	
		virtual boost::shared_ptr<LevelSeedData> GetSeed( int Index );

	
		static std::vector<boost::shared_ptr<BobPhsx> > _HeroTypes, HeroTypes;

		void ShuffleHeros();

		virtual void Start(int StartLevel);
	
		virtual boost::shared_ptr<BobPhsx> GetHero( int i );

	
		int LevelsPerTileset;
		static std::vector<std::wstring> tilesets;
		//static string[] tilesets = { "hills", "forest", "cloud", "cave", "castle", "sea" };

	
		virtual boost::shared_ptr<TileSet> GetTileSet( int i );

	
		int LevelLength_Short;
		int LevelLength_Long;
	
		virtual int GetLength( int Index, float Difficulty );
		virtual boost::shared_ptr<LevelSeedData> Make( int Index, float Difficulty );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HERORUSH
