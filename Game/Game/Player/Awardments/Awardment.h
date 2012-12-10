#ifndef AWARDMENT
#define AWARDMENT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Awardment : public std::enable_shared_from_this<Awardment>
	{

	
		std::wstring Name, Description;
		std::shared_ptr<Hat> Unlockable;
		int Guid;

		Awardment( int Guid, const std::wstring &Name, const std::wstring &Description, const std::shared_ptr<Hat> &Unlockable );

	};

	struct Awardments
	{

	
		static void InitializeStatics();

	
		struct CheckpointsStatsLambda : public PlayerIntLambda
		{
		
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	
		struct CoinsStatsLambda : public PlayerIntLambda
		{
		
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	
		struct TotalCoinsStatsLambda : public PlayerIntLambda
		{
		
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	
		static std::vector<std::shared_ptr<Awardment> > Awards;
		static std::map<int, std::shared_ptr<Awardment> > AwardsDict;

		/// <summary>
		/// Whether there is an awardment message on the screen currently.
		/// </summary>
		static bool MessageOnScreen();

		/// <summary>
		/// If there is an awardment message on the screen currently,
		/// then return a positive amount to delay by.
		/// </summary>
		/// <returns>The amount to delay by.</returns>
		static int AwardDelay();

		static void CheckForAward_HoldForward();

		static void CheckForAward_NoCoins();

	
		static int HeroRushScore;
	
		static void CheckForAward_HeroRush_Score( int Score );

	
		static int HeroRush2Score;
	
		static void CheckForAward_HeroRush2_Score( int Score );

	
		static int HeroRush2_LevelUnlock;
	
//C# TO C++ CONVERTER NOTE: The parameter Level was renamed since it is named the same as a user-defined type:
		static void CheckForAward_HeroRush2Unlock( int Level_Renamed );

//C# TO C++ CONVERTER NOTE: The parameter Level was renamed since it is named the same as a user-defined type:
		static void CheckForAward_Escalation_Level( int Level_Renamed );

		static void CheckForAward_BeatCampaign( int Index );

		//static int FastCampaign_Minutes = 5;
	
		static int FastCampaign_Minutes;
	
		static void CheckForAward_FastCampaign( int Index );

		static void CheckForAward_EbenezerAbusiveCastle( int Index );

		static void CheckForAward_PerfectEasyCastle( int Index );

		static void CheckForAward_NoDeathNormalCastle( int Index );

		static void CheckForAward_PartiallyInvisible( int Index );

		static void CheckForAward_TotallyInvisible( int Index );

		static const int LotsOfJumps = 10000;
		static void CheckForAward_JumpAlot( const std::shared_ptr<Bob> &bob );

		static float CurShift, Shift;
		static void GiveAward( const std::shared_ptr<Awardment> &award );

	
		static std::wstring BeatStr;
	
		static std::vector<std::shared_ptr<Awardment> > BeatCampaign;
		static std::shared_ptr<Awardment> JumpAlot;

		static std::shared_ptr<Awardment> HoldForwardFreeplay;
		static std::shared_ptr<Awardment> HeroRush_Score;
		static std::shared_ptr<Awardment> Escalation_Levels;

		static std::shared_ptr<Awardment> FastCampaign2;

		static std::shared_ptr<Awardment> HeroRush2_Score;
		static std::shared_ptr<Awardment> PartiallyInvisibleCampaign;
		static std::shared_ptr<Awardment> TotallyInvisibleCampaign;

		static std::shared_ptr<Awardment> NoCoinFreeplay;

		static std::shared_ptr<Awardment> AllCoinsAbusiveCastle;
		static std::shared_ptr<Awardment> NoDeathsNormalCastle;
		static std::shared_ptr<Awardment> PerfectEasyCastle;

		static std::shared_ptr<Awardment> UnlockHeroRush2;

		static void Init();
	};
}


#endif	//#ifndef AWARDMENT
