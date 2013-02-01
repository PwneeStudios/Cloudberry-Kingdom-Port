#ifndef CHALLENGE_BASE
#define CHALLENGE_BASE

#include <global_header.h>

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

	struct Challenge : public boost::enable_shared_from_this<Challenge>
	{

		virtual ~Challenge() { }

		static int Coins;
		static int CurrentScore;
		static int CurrentId;

		struct OnCoinGrabProxy : public Lambda_1<boost::shared_ptr<ObjectBase> >
		{
		
			void Apply( const boost::shared_ptr<ObjectBase> &obj );

		};

	
		struct PassGetSeedAsLambda : public LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> >
		{

		
			boost::shared_ptr<Challenge> challenge;

		
			PassGetSeedAsLambda( const boost::shared_ptr<Challenge> &challenge );

			boost::shared_ptr<LevelSeedData> Apply( const int &index );

		};

		struct ShowEndScreenProxy : public Lambda
		{
		
			boost::shared_ptr<Challenge> challenge;

		
			ShowEndScreenProxy( const boost::shared_ptr<Challenge> &challenge );

			void Apply();
		};

	
		static boost::shared_ptr<BobPhsx> ChosenHero;
	
		static const int LevelMask = 10000;

	
		std::vector<int> StartLevels;

		Localization::Words Name, MenuName;

		int GameId_Score, GameId_Level;
	
		int GameTypeId;

		int CalcTopGameLevel( boost::shared_ptr<BobPhsx> hero );
		int CalcGameId_Score( boost::shared_ptr<BobPhsx> hero )
		int CalcGameId_Level( boost::shared_ptr<BobPhsx> hero );
		int SetGameId();

	
		const boost::shared_ptr<StringWorldGameData> getStringWorld() const;

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
		int TopPlayerScore( boost::shared_ptr<BobPhsx> hero );

		/// <summary>
		/// Get the highest level that anyone playing has ever gotten.
		/// </summary>
		int TopPlayerLevel();

        /// <summary>
        /// Get the top score that anyone playing has ever gotten.
        /// </summary>
        int TopPlayerScore(BobPhsx hero);
	
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

	
		virtual void SetGameParent( const boost::shared_ptr<GameData> &game );

	
		virtual boost::shared_ptr<LevelSeedData> GetSeed( int Index ) = 0;

	
		void InitializeInstanceFields();


		Challenge()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef CHALLENGE_BASE
