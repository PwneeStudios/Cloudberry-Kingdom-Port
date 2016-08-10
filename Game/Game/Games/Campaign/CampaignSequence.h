#ifndef CAMPAIGNSEQUENCE
#define CAMPAIGNSEQUENCE

#include <small_header.h>

#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Tilesets/Backgrounds/Background.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/ActionGame.h"
#include "Game/Games/Campaign/LevelSequence.h"
#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Tools/EzStorage.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
//#include "Game/Objects/Game Objects/GameObjects/LevelTitle.h"
//#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
//#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
//#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Tools/Tools.h"


#include "Hacks/NET/Tuple.h"

namespace CloudberryKingdom
{

    struct Challenge_StoryMode : public Challenge
    {

		virtual ~Challenge_StoryMode()
		{
#ifdef BOOST_BIN
			OnDestructor( "Challenge_StoryMode" );
#endif
		}


		static void InitializeStatics();

		static boost::shared_ptr<Challenge_StoryMode> instance;
		const static boost::shared_ptr<Challenge_StoryMode> &getInstance();

        Challenge_StoryMode();

        virtual boost::shared_ptr<LevelSeedData> GetSeed( int Index );

    };

	struct CampaignSequence : public LevelSequence
	{
		virtual ~CampaignSequence()
		{
#ifdef BOOST_BIN
			OnDestructor( "CampaignSequence" );
#endif
		}


	
		struct PostMakeCampaignProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct OnCoinGrabProxy : public Lambda_1<boost::shared_ptr<ObjectBase> >
		{
		
			void Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct OnCompleteLevelProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct WatchMovieLambda : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			std::wstring movie;
		
			WatchMovieLambda( const std::wstring &movie );

			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		struct EndActionProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			void Apply( const boost::shared_ptr<Level> &level );
		};

	
		static boost::shared_ptr<CampaignSequence> instance;
		const static boost::shared_ptr<CampaignSequence> &getInstance();

		static std::vector<Localization::Words> ChapterName;

		static bool MusicStarted;

		std::map<int, int> ChapterStart;
		std::map<int, int> ChapterEnd;
		std::map<int, boost::shared_ptr< Tuple<std::wstring, std::wstring> > > SpecialLevel;
		
		static boost::shared_ptr<PerfectScoreObject> MyPerfectScoreObject;
	
		static void OnChapterFinished(int chapter);

		int StartLevel;
		virtual void Start( int Chapter );

        static int ChapterFinishing;
        static void CheckForFinishedChapter();
	
		bool OnLevelBegin( const boost::shared_ptr<Level> &level );
		void AdditionalPreStart();
		void MyStringWorld_OnSwapToFirstLevel( boost::shared_ptr<LevelSeedData> data );

		virtual void MakeSeedList();

	
		static boost::shared_ptr<LevelSeedData> MakeActionSeed( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Level> > > SeedAction );

	
		virtual boost::shared_ptr<LevelSeedData> GetSeed( int Index );

	
		static void PostMakeCampaign( const boost::shared_ptr<Level> &level );

		static void OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj );

		static void MarkProgress( const boost::shared_ptr<Level> &level );
		static void OnCompleteLevel( const boost::shared_ptr<Level> &level );

		static boost::shared_ptr<Lambda_1<boost::shared_ptr<Level> > > MakeWatchMovieAction( const std::wstring &movie );

		static void EndAction( const boost::shared_ptr<Level> &level );

	
		CampaignSequence();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CAMPAIGNSEQUENCE
