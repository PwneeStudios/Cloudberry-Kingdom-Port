#ifndef CHALLENGE_BASE
#define CHALLENGE_BASE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsx;
}

namespace CloudberryKingdom
{
	struct StringWorldGameData;
}

namespace CloudberryKingdom
{
	struct GameData;
}

namespace CloudberryKingdom
{
	struct LevelSeedData;
}


namespace CloudberryKingdom
{
	struct AftermathData
	{
	
		bool Success;
		bool EarlyExit;
		bool Retry;

	
		void InitializeInstanceFields();


		AftermathData()
		{
			InitializeInstanceFields();
		}
	};

	struct Challenge : public std::enable_shared_from_this<Challenge>
	{

	
		struct PassGetSeedAsLambda : public LambdaFunc_1<int, std::shared_ptr<LevelSeedData> >
		{

		
			std::shared_ptr<Challenge> challenge;

		
			PassGetSeedAsLambda( const std::shared_ptr<Challenge> &challenge );

			std::shared_ptr<LevelSeedData> Apply( const int &index );

		};

		struct ShowEndScreenProxy : public Lambda
		{
		
			std::shared_ptr<Challenge> challenge;

		
			ShowEndScreenProxy( const std::shared_ptr<Challenge> &challenge );

			void Apply();
		};

	
		static std::shared_ptr<BobPhsx> ChosenHero;
	
		static const int LevelMask = 10000;

	
		std::vector<int> StartLevels;

		Localization::Words Name, MenuName;

		int GameId_Score, GameId_Level;
	
		int GameTypeId;

	
		int SetGameId();

	
		const std::shared_ptr<StringWorldGameData> getStringWorld() const;

		/// <summary>
		/// Get the top score that anyone on this machine has ever gotten.
		/// </summary>
	
		int TopScore();

		/// <summary>
		/// Get the highest level that anyone on this machine has ever gotten.
		/// </summary>
		int TopLevel();

		/// <summary>
		/// Get the top score that anyone playing has ever gotten.
		/// </summary>
		int TopPlayerScore();

		/// <summary>
		/// Get the highest level that anyone playing has ever gotten.
		/// </summary>
		int TopPlayerLevel();

	
		virtual void ShowEndScreen();

		/// <summary>
		/// If true then this meta-game is not part of the campaign.
		/// </summary>
	
		bool NonCampaign;
		virtual void Start( int Difficulty );

		/// <summary>
		/// The difficulty selected for this challenge.
		/// </summary>
		int DifficultySelected;

		/// <summary>
		/// Called immediately after the end of the challenge.
		/// </summary>
		void Aftermath();

	
		virtual void SetGameParent( const std::shared_ptr<GameData> &game );

	
		virtual std::shared_ptr<LevelSeedData> GetSeed( int Index ) = 0;

	
		void InitializeInstanceFields();


		Challenge()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef CHALLENGE_BASE
