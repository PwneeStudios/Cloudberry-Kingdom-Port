#ifndef AWARDMENT
#define AWARDMENT

#include <small_header.h>

#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Games/GameType.h"
//#include "Game/Player/PlayerManager.h"
#include "Game/Player/ColorScheme.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Awardments/AwardmentMessage.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct Awardment : public boost::enable_shared_from_this<Awardment>
	{

        static std::wstring NewGameMode;
        static std::wstring Default;

        Localization::Words Name, Description;
        std::wstring TitleType;

		boost::shared_ptr<Hat> Unlockable;
		int Guid;

		std::wstring Key;

        /// <summary>
        /// An associated integer, usually representing a number the player must surpass to achieve the awardment.
        /// </summary>
        int MyInt;

        /// <summary>
        /// Whether this award is a legitimate Achievement/Trophy/Awardment/etc, as defined by the relevant console.
        /// Unofficial awards are used to track progress without giving an official award to the player.
        /// </summary>
        bool Official;

        /// <summary>
        /// Whether to show a custom message when the award is given.
        /// On Xbox there is a system level message for official awards, hence no additional message is needed.
        /// </summary>
        bool ShowWhenAwarded;

        Awardment(int Guid, std::wstring Key, Localization::Words Name, Localization::Words Description);

        //Awardment(int Guid, Localization.Words Name, Localization.Words Description, string TitleType, bool ShowWhenAwarded)
		Awardment(int Guid, std::wstring Name, std::wstring Description, std::wstring TitleType, bool ShowWhenAwarded);

	};

	struct Awardments
	{
	
		static void InitializeStatics();
	
		static std::vector<boost::shared_ptr<Awardment> > Awards;
		static std::map<int, boost::shared_ptr<Awardment> > AwardsDict;

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


		static void CheckForAward_TimeCrisisUnlock(int Level, boost::shared_ptr<PlayerData> player);
		static void CheckForAward_HeroRushUnlock(int Level, boost::shared_ptr<PlayerData> player);
		static void CheckForAward_HeroRush2Unlock(int Level, boost::shared_ptr<PlayerData> player);
		static void CheckForAward_HeroRush2_Level(int Level);
		static void CheckForAward_ArcadeScore(int Score);
		static void CheckForAward_ArcadeScore2(int Score);
		static void CheckForAward_Invisible(int Level);
		static void CheckForAward_Die(boost::shared_ptr<Bob> bob);
		static void CheckForAward_NoDeath(boost::shared_ptr<PlayerData> player);
		static void CheckForAward_UnlockAllArcade();
		static void CheckForAward_Save();
		static void CheckForAward_Obstacles(boost::shared_ptr<Bob> bob);
		static void CheckForAward_Buy();
		static void CheckForAward_Replay(int Attempts);
		static void CheckForAward_Bungee(boost::shared_ptr<GameData> game);

        static void Awardments::GiveAward( const boost::shared_ptr<Awardment> &award );
        static void Awardments::GiveAward( const boost::shared_ptr<Awardment> &award, const boost::shared_ptr<PlayerData> player);
	
        static boost::shared_ptr<Awardment> Award_Campaign1;
        static boost::shared_ptr<Awardment> Award_ArcadeHighScore;
        static boost::shared_ptr<Awardment> Award_Bungee;
        static boost::shared_ptr<Awardment> Award_ArcadeHighScore2;
        static boost::shared_ptr<Awardment> Award_Die;
        static boost::shared_ptr<Awardment> Award_Campaign3;
        static boost::shared_ptr<Awardment> Award_Invisible;
        static boost::shared_ptr<Awardment> Award_Hats;
        static boost::shared_ptr<Awardment> Award_Campaign2;
        static boost::shared_ptr<Awardment> Award_UnlockAllArcade;
        static boost::shared_ptr<Awardment> Award_NoDeath;
        static boost::shared_ptr<Awardment> Award_Save;
        static boost::shared_ptr<Awardment> Award_Obstacles;
        static boost::shared_ptr<Awardment> Award_Buy;
        static boost::shared_ptr<Awardment> Award_Campaign4;
        static boost::shared_ptr<Awardment> Award_BuyHat;
        static boost::shared_ptr<Awardment> Award_HeroRush2Level;
        static boost::shared_ptr<Awardment> Award_Replay;
        
        // Arcade Unlocks
        static boost::shared_ptr<Awardment> UnlockTimeCrisis;
        static boost::shared_ptr<Awardment> UnlockHeroRush;
        static boost::shared_ptr<Awardment> UnlockHeroRush2;

        const static int TimeCrisis_LevelUnlock = 50;
        const static int HeroRush_LevelUnlock = 250;
        const static int HeroRush2_LevelUnlock = 500;

		static float CurShift, Shift;

		static void Init();
	};
}


#endif	//#ifndef AWARDMENT
