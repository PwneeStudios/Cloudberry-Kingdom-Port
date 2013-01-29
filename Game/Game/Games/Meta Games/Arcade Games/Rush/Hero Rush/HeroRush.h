#ifndef HERORUSH
#define HERORUSH

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_HeroRush : public Rush
	{

		virtual ~Challenge_HeroRush() { }
	
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
		void Start(int StartLevel);
	
		virtual boost::shared_ptr<BobPhsx> GetHero( int i );

	
		int LevelsPerTileset;
		static std::vector<std::wstring> tilesets;
		//static string[] tilesets = { "hills", "forest", "cloud", "cave", "castle", "sea" };

	
		virtual boost::shared_ptr<TileSet> GetTileSet( int i );

	
		int LevelLength_Short;
		int LevelLength_Long;
	
		virtual boost::shared_ptr<LevelSeedData> Make( int Index, float Difficulty );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef HERORUSH
