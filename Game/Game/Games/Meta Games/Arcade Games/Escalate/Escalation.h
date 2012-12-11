#ifndef ESCALATION
#define ESCALATION

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Challenge_Escalation : public Challenge
	{

	
		static void InitializeStatics();

	
		struct OnOutOfLivesLambda : public Lambda_1<std::shared_ptr<GUI_LivesLeft> >
		{
		
			std::shared_ptr<Challenge> challenge;

		
			OnOutOfLivesLambda( const std::shared_ptr<Challenge> &challenge );

			void Apply( const std::shared_ptr<GUI_LivesLeft> &Lives );
		};

	
		struct OnBeginLambda : public LambdaFunc_1<std::shared_ptr<Level> , bool>
		{
		
			OnBeginLambda();

			bool Apply( const std::shared_ptr<Level> &level );
		};

	
		struct OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		
			std::shared_ptr<Challenge_Escalation> ch;
		
			OnSwapLambda( const std::shared_ptr<Challenge_Escalation> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	
		struct ScoreMultiplierHelper : public Lambda_1<std::shared_ptr<GameData> >
		{
		
			float multiplier;

		
			ScoreMultiplierHelper( float multiplier );

			void Apply( const std::shared_ptr<GameData> &game );
		};

	
		struct AdditionalPreStartOnSwapToLevelHelper : public Lambda_1<int>
		{
		
			std::shared_ptr<Challenge_Escalation> ce;

		
			AdditionalPreStartOnSwapToLevelHelper( const std::shared_ptr<Challenge_Escalation> &ce );

			void Apply( const int &levelindex );
		};

	
		struct MakeMyModParamsHelper : public Lambda_2<std::shared_ptr<Level> , std::shared_ptr<PieceSeedData> >
		{
		
			void Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p );
		};

		//static int[] NumLives = { 15, 12, 10, 5, 1 };
	
		static std::vector<int> NumLives;

		static std::shared_ptr<Challenge_Escalation> instance;
	
		const static std::shared_ptr<Challenge_Escalation> &getInstance();

		std::shared_ptr<GUI_LivesLeft> Gui_LivesLeft;

	
		Challenge_Escalation();

		int i;
		int StartIndex;
		std::shared_ptr<StringWorldEndurance> MyStringWorld;
	
		virtual void Start( int StartLevel );

	
		virtual void PreStart_Tutorial();

	
		int GetLives();

	
		int LevelsPerDifficulty;

		int LevelsPerTileset;

		virtual void AdditionalPreStart();

	
		void OnSwapTo_GUI( int levelindex );

	
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index );

	
		int LevelLength_Short;
		int LevelLength_Long;

		static std::vector<std::wstring> tilesets;

	
		virtual std::shared_ptr<TileSet> GetTileSet( int i );

		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual std::shared_ptr<LevelSeedData> Make( int Index, float Difficulty );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ESCALATION
