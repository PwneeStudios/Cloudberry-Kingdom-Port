#ifndef ARCADEMENU
#define ARCADEMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Player/LeaderboardView.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Games/Campaign/CampaignSequence.h"
//#include "Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
//#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/LongMenu.h"
//#include "Game/Tools/EzStorage.h"
//#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Score Screens/ScoreEntry.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartLevelMenu.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Player/Awardments/AwardmentMessage.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/Big.h"
//#include "Game/Player/Hero Physics/Bouncy.h"
//#include "Game/Player/Hero Physics/Box.h"
//#include "Game/Player/Hero Physics/Double.h"
//#include "Game/Player/Hero Physics/Invert.h"
//#include "Game/Player/Hero Physics/Jetman.h"
//#include "Game/Player/Hero Physics/Rocketbox.h"
//#include "Game/Player/Hero Physics/Scale.h"
//#include "Game/Player/Hero Physics/Small.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Player/Hero Physics/Time.h"
//#include "Game/Player/Hero Physics/Wheel.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct ArcadeItem : public MenuItem
	{
	
		boost::shared_ptr<Challenge> MyChallenge;
		boost::shared_ptr<Awardment> MyPrereq;
		bool IsLocked();

		ArcadeItem( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq );
		boost::shared_ptr<ArcadeItem> ArcadeItem_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq );

	};

	struct ArcadeBaseMenu : public CkBaseMenu
	{

		virtual ~ArcadeBaseMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "ArcadeBaseMenu" );
#endif
		}

	
		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		struct PlayGameProxy : public Lambda
		{
		
			boost::shared_ptr<ArcadeBaseMenu> abm;

		
			PlayGameProxy( const boost::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply();
		};

	
		struct StartFuncProxy : public Lambda_1<boost::shared_ptr<LevelItem> >
		{
		
			boost::shared_ptr<ArcadeBaseMenu> abm;

		
			StartFuncProxy( const boost::shared_ptr<ArcadeBaseMenu> &abm );

			void Apply( const boost::shared_ptr<LevelItem> &levelitem );
		};

	
		boost::shared_ptr<LevelItem> SelectedItem;
		boost::shared_ptr<ArcadeItem> MyArcadeItem;

		boost::shared_ptr<ArcadeBaseMenu> ArcadeBaseMenu_Construct();

		virtual void OnAdd();

	
		virtual void StartFunc( const boost::shared_ptr<LevelItem> &item );

		virtual void PlayGame();

	
		virtual void Release();
	};


	struct ArcadeMenu : public ArcadeBaseMenu
	{

		virtual ~ArcadeMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "ArcadeMenu" );
#endif
		}


		struct OnSelectProxy : public Lambda
		{
		
			boost::shared_ptr<ArcadeMenu> am;
		
			OnSelectProxy( const boost::shared_ptr<ArcadeMenu> &am );

			void Apply();
		};

		struct GoProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ArcadeMenu> am;

		
			GoProxy( const boost::shared_ptr<ArcadeMenu> &am );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		bool Long;

		static void CheckForArcadeUnlocks(boost::shared_ptr<ScoreEntry> score);

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnReturnTo();

	
		void SetLockColors();

        static boost::shared_ptr<BobPhsx> JetpackWheelie;
        static boost::shared_ptr<BobPhsx> BigBouncy;
        static boost::shared_ptr<BobPhsx> Ultimate;

        static std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > > HeroArcadeList;
        static std::vector<std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> > > LeaderboardList;
        static std::vector<std::pair<int, int> > ChallengeGoal;

		static const int HighestLevelNeeded;
		static boost::shared_ptr<BobPhsx> HighestHero;

		ArcadeMenu();
		boost::shared_ptr<ArcadeMenu> ArcadeMenu_Construct();

		static void StaticInit();

		static int LeaderboardIndex(boost::shared_ptr<Challenge> challenge, boost::shared_ptr<BobPhsx> phsx);
		static void CheckForArcadeUnlocks_OnSwapIn(int level);

        boost::shared_ptr<EzText> RequiredText, RequiredText2;
        boost::shared_ptr<QuadClass> TextBack;

		virtual void Init();

	
		void SetParams();

		Vector2 GetGoalPos();

		boost::shared_ptr<MenuItem> AddChallenge( const boost::shared_ptr<Challenge> &challenge, const boost::shared_ptr<Awardment> &prereq, const std::wstring &itemname );

		void UpdateAfterPlaying();

		static boost::shared_ptr<Challenge> SelectedChallenge;
        bool Lock;
        void OnSelect();
	
		virtual void Go( const boost::shared_ptr<MenuItem> &item );

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ARCADEMENU
