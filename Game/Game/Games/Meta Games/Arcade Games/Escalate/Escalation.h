#ifndef ESCALATION
#define ESCALATION

#include <global_header.h>

namespace CloudberryKingdom
{
	class GUI_LivesLeft;
}

namespace CloudberryKingdom
{
	class Challenge;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class StringWorldEndurance;
}

namespace CloudberryKingdom
{
	class TileSet;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}



namespace CloudberryKingdom
{
	class Challenge_Escalation : public Challenge
	{
	private:
		class OnOutOfLivesLambda : public Lambda_1<GUI_LivesLeft*>
		{
		private:
			std::shared_ptr<Challenge> challenge;

		public:
			OnOutOfLivesLambda( const std::shared_ptr<Challenge> &challenge );

			void Apply( const std::shared_ptr<GUI_LivesLeft> &Lives );
		};

	private:
		class OnBeginLambda : public LambdaFunc_1<std::shared_ptr<Level> , bool>
		{
		public:
			OnBeginLambda();

			bool Apply( const std::shared_ptr<Level> &level );
		};

	private:
		class OnSwapLambda : public Lambda_1<LevelSeedData*>
		{
		private:
			std::shared_ptr<Challenge_Escalation> ch;
		public:
			OnSwapLambda( const std::shared_ptr<Challenge_Escalation> &ch );

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	private:
		class ScoreMultiplierHelper : public Lambda_1<std::shared_ptr<GameData> >
		{
		private:
			float multiplier;

		public:
			ScoreMultiplierHelper( float multiplier );

			void Apply( const std::shared_ptr<GameData> &game );
		};

	private:
		class AdditionalPreStartOnSwapToLevelHelper : public Lambda_1<int>
		{
		private:
			std::shared_ptr<Challenge_Escalation> ce;

		public:
			AdditionalPreStartOnSwapToLevelHelper( const std::shared_ptr<Challenge_Escalation> &ce );

			void Apply( int levelindex );
		};

	private:
		class MakeMyModParamsHelper : public Lambda_2<std::shared_ptr<Level> , std::shared_ptr<PieceSeedData> >
		{
		public:
			void Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p );
		};

		//static int[] NumLives = { 15, 12, 10, 5, 1 };
	private:
		static std::vector<int> NumLives;

		static const std::shared_ptr<Challenge_Escalation> instance;
	public:
		const static std::shared_ptr<Challenge_Escalation> &getInstance();

		std::shared_ptr<GUI_LivesLeft> Gui_LivesLeft;

	protected:
		Challenge_Escalation();

		int i;
		int StartIndex;
		std::shared_ptr<StringWorldEndurance> MyStringWorld;
	public:
		virtual void Start( int StartLevel );

	protected:
		virtual void PreStart_Tutorial();

	private:
		int GetLives();

	protected:
		int LevelsPerDifficulty;

		int LevelsPerTileset;

		virtual void AdditionalPreStart();

	private:
		void OnSwapTo_GUI( int levelindex );

	public:
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index );

	private:
		int LevelLength_Short;
		int LevelLength_Long;

		static std::vector<std::wstring> tilesets;

	protected:
		virtual std::shared_ptr<TileSet> GetTileSet( int i );

		virtual std::shared_ptr<BobPhsx> GetHero( int i );

		virtual std::shared_ptr<LevelSeedData> Make( int Index, float Difficulty );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ESCALATION
