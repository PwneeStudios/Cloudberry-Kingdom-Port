#ifndef ESCALATION
#define ESCALATION

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Challenge_Escalation : public Challenge
	{

	
		static void InitializeStatics();

	
		struct OnOutOfLivesLambda : public Lambda_1<boost::shared_ptr<GUI_LivesLeft> >
		{
		
			boost::shared_ptr<Challenge> challenge;

		
			OnOutOfLivesLambda( const boost::shared_ptr<Challenge> &challenge );

			void Apply( const boost::shared_ptr<GUI_LivesLeft> &Lives );
		};

	
		struct OnBeginLambda : public LambdaFunc_1<boost::shared_ptr<Level> , bool>
		{
		
			OnBeginLambda();

			bool Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct OnSwapLambda : public Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
		
			boost::shared_ptr<Challenge_Escalation> ch;
		
			OnSwapLambda( const boost::shared_ptr<Challenge_Escalation> &ch );

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
		
			boost::shared_ptr<Challenge_Escalation> ce;

		
			AdditionalPreStartOnSwapToLevelHelper( const boost::shared_ptr<Challenge_Escalation> &ce );

			void Apply( const int &levelindex );
		};

	
		struct MakeMyModParamsHelper : public Lambda_2<boost::shared_ptr<Level> , boost::shared_ptr<PieceSeedData> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p );
		};

		//static int[] NumLives = { 15, 12, 10, 5, 1 };
	
		static std::vector<int> NumLives;

		static boost::shared_ptr<Challenge_Escalation> instance;
	
		const static boost::shared_ptr<Challenge_Escalation> &getInstance();

		boost::shared_ptr<GUI_LivesLeft> Gui_LivesLeft;

	
		Challenge_Escalation();

		int i;
		int StartIndex;
		boost::shared_ptr<StringWorldEndurance> MyStringWorld;
	
		virtual void Start( int StartLevel );

	
		virtual void PreStart_Tutorial();

	
		int GetLives();

	
		int LevelsPerDifficulty;

		int LevelsPerTileset;

		virtual void AdditionalPreStart();

	
		void OnSwapTo_GUI( int levelindex );

	
		virtual boost::shared_ptr<LevelSeedData> GetSeed( int Index );

	
		int LevelLength_Short;
		int LevelLength_Long;

		static std::vector<std::wstring> tilesets;

	
		virtual boost::shared_ptr<TileSet> GetTileSet( int i );

		virtual boost::shared_ptr<BobPhsx> GetHero( int i );

		virtual boost::shared_ptr<LevelSeedData> Make( int Index, float Difficulty );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ESCALATION
