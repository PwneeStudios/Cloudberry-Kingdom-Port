#include <global_header.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <Hacks/Parse.h>
#include <Hacks/FileReader.h>
#include <Hacks/String.h>
#include <Core\Tools\Set.h>
#include "Hacks/List.h"
#include <Utility/Error.h>
#include <Game\Video.h>

namespace CloudberryKingdom
{

		boost::shared_ptr<Challenge_StoryMode> Challenge_StoryMode::instance;

		void Challenge_StoryMode::InitializeStatics()
		{
			Challenge_StoryMode::instance = boost::make_shared<Challenge_StoryMode>();
		}

		const boost::shared_ptr<Challenge_StoryMode> &Challenge_StoryMode::getInstance()
		{
			return instance;
		}

        Challenge_StoryMode::Challenge_StoryMode()
        {
            GameId_Level = GameTypeId = 7777;
            MenuName = Name = Localization::Words_StoryMode;
        }

        boost::shared_ptr<LevelSeedData> Challenge_StoryMode::GetSeed( int Index )
        {
            return 0;
        }




	void CampaignSequence::PostMakeCampaignProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		CampaignSequence::PostMakeCampaign( level );
	}

	void CampaignSequence::OnCoinGrabProxy::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		CampaignSequence::OnCoinGrab( obj );
	}

	void CampaignSequence::OnCompleteLevelProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		CampaignSequence::OnCompleteLevel( level );
	}

	CampaignSequence::WatchMovieLambda::WatchMovieLambda( const std::wstring &movie )
	{
		this->movie = movie;
	}

	void CampaignSequence::WatchMovieLambda::Apply( const boost::shared_ptr<Level> &level )
	{
		MainVideo::StartVideo_CanSkipIfWatched_OrCanSkipAfterXseconds( movie, 1.5f );
		( boost::static_pointer_cast<ActionGameData>( level->MyGame ) )->Done = true;
	}

	void CampaignSequence::EndActionProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		CampaignSequence::EndAction( level );
	}

	boost::shared_ptr<CampaignSequence> CampaignSequence::instance;

	Localization::Words _ChapterName[] = { Localization::Words_Chapter1, Localization::Words_Chapter2, Localization::Words_Chapter3,
										   Localization::Words_Chapter4, Localization::Words_Chapter5, Localization::Words_Chapter6,
										   Localization::Words_TheMasochist };
	std::vector<Localization::Words> CampaignSequence::ChapterName = VecFromArray( _ChapterName );


	const boost::shared_ptr<CampaignSequence> &CampaignSequence::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<PerfectScoreObject> CampaignSequence::MyPerfectScoreObject = 0;

        void CampaignSequence::OnChapterFinished(int chapter)
        {
			std::vector<boost::shared_ptr<PlayerData> > vec;

            // Didn't die during the chapter?
			vec = PlayerManager::getAlivePlayers();
			for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
				Awardments::CheckForAward_NoDeath( ( *player ) );

            // Give beat chapter award
            boost::shared_ptr<Awardment> award = 0;
            switch (chapter)
            {
				case 2: award = Awardments::Award_Campaign1; break;
				case 4: award = Awardments::Award_Campaign2; break;
				case 6: award = Awardments::Award_Campaign3; break;
				case 7: award = Awardments::Award_Campaign4; break;

				default: break;
            }
            Awardments::GiveAward(award);

            // Clean campaign stats
			vec = PlayerManager::getExistingPlayers();
			for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
				( *player )->CampaignStats->Clean();
        }

		bool CampaignSequence::MusicStarted = false;
	void CampaignSequence::Start( int Chapter )
	{
        CloudberryKingdomGame::PromptForDeviceIfNoneSelected();
		CloudberryKingdomGame::SetPresence( Presence_Campaign );

		MusicStarted = false;

		MyPerfectScoreObject = MakeMagic( PerfectScoreObject, ( false, true, true ) );

		// Continue at last level reached.
		if ( Chapter < 0 )
		{
			//StartLevel = ChapterStart[ Chapter ];

			//int NextChapterStart = Contains( ChapterStart, Chapter + 1 ) ? ChapterStart[Chapter + 1] : StartLevel + 100000;
			//int MaxLevelAttained = PlayerManager::MaxPlayerTotalCampaignIndex() + 1;

			//if ( MaxLevelAttained > StartLevel && MaxLevelAttained < NextChapterStart )
			//	StartLevel = MaxLevelAttained;

			StartLevel = PlayerManager::MinPlayerTotalCampaignIndex() + 1;

			if ( CloudberryKingdomGame::DigitalDayBuild )
			{
			}
		}
		else
		{
			StartLevel = ChapterStart[ Chapter ];
		}

/*#ifdef DEBUG
		StartLevel = 320;
#endif*/

		LevelSequence::Start( StartLevel );
	}

	int CampaignSequence::ChapterFinishing;

    void CampaignSequence::CheckForFinishedChapter()
    {
        if ( ChapterFinishing >= 0 )
        {
            OnChapterFinished( ChapterFinishing );
            ChapterFinishing = -1;
        }
    }

    bool CampaignSequence::OnLevelBegin( const boost::shared_ptr<Level> &level )
    {
		if ( CloudberryKingdomGame::CampaignProgressMade )
		{
			SaveGroup::SaveAll();
			CloudberryKingdomGame::CampaignProgressMade = false;
		}

		HelpMenu::CostMultiplier = 1;

		if ( level->MyLevelSeed != 0 )
		{
			int Num = level->MyLevelSeed->LevelNum;
			if ( Num >= 0 )
			{
				for ( std::map<int, int>::const_iterator kv = ChapterStart.begin(); kv != ChapterStart.end(); ++kv )
				{
					if ( kv->second < Num )
					{
						HelpMenu::CostMultiplier = __max( kv->first + 1, HelpMenu::CostMultiplier );
					}
				}

				if( Num == 42 )
				{
					DisplayError( ErrorType( 0xDEADBEEF ) );
				}
			}
		}

        if ( LevelSequence::OnLevelBegin( level ) ) return true;

		CheckForFinishedChapter();

        //level.MyGame.AddGameObject(InGameStartMenu.MakeListener());
        level->MyGame->AddGameObject( HelpMenu::MakeListener() );
        return false;
    }

		struct OnSwapHelper : Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
			boost::shared_ptr<CampaignSequence> cs;
			OnSwapHelper( boost::shared_ptr<CampaignSequence> _cs )
			{
				cs = _cs;
			}

			void Apply( const boost::shared_ptr<LevelSeedData> &data )
			{
				cs->MyStringWorld_OnSwapToFirstLevel( data );
			}
		};

    void CampaignSequence::AdditionalPreStart()
    {
        MyStringWorld->OnSwapToFirstLevel->Add( boost::make_shared<OnSwapHelper>( boost::static_pointer_cast<CampaignSequence>( shared_from_this() ) ) );
    }

    void CampaignSequence::MyStringWorld_OnSwapToFirstLevel( boost::shared_ptr<LevelSeedData> data )
    {
        MyPerfectScoreObject->PreventRelease = true;
        data->MyGame->AddGameObject( MyPerfectScoreObject );
    }

	void CampaignSequence::MakeSeedList()
	{
        int LastRealLevelIndex = -1;
        int LastSetChapter = -1;
        ChapterStart = std::map<int, int>();
        ChapterEnd = std::map<int, int>();

		Seeds.push_back( L"" );

		Tools::UseInvariantCulture();
#if defined(PC_VERSION)
		FileReader reader = FileReader( std::wstring( L"Content/Campaign/CampaignList.txt" ) );
#elif CAFE
		FileReader reader = FileReader( std::wstring( L"Campaign/CampaignList_3.txt" ) );
#else
		FileReader reader = FileReader( std::wstring( L"Campaign/CampaignList.txt" ) );
#endif

		std::wstring line;

		int level = 1, count = 1;

		line = reader.ReadLine();
		while ( line.find( L"eof" ) == std::wstring::npos /*line != std::wstring( L"eof" )*/ )
		{
			line = Tools::RemoveComment_DashStyle( line );
			if ( line == std::wstring( L"" ) || line.length() <= 1 )
			{
				line = reader.ReadLine();
				continue;
			}

			int space = line.find( L' ' );
			std::wstring identifier, data;
			if ( space > 0 )
			{
				identifier = line.substr( 0, space );
				data = line.substr( space + 1 );
			}
			else
			{
				identifier = line;
				data = std::wstring( L"" );
			}

			if ( identifier == std::wstring( L"chapter" ) )
			{
				int chapter = 0;
				if ( ParseInt( data, chapter ) )
				{
					// Mark end of chapter
					if (LastRealLevelIndex > 0)
					{
						ChapterEnd[ LastSetChapter ] = LastRealLevelIndex;
						LastRealLevelIndex = -1;
					}

					DictionaryExtension::AddOrOverwrite( ChapterStart, chapter, count );
				
					LastSetChapter = chapter;
				}
			}
			else if ( identifier == std::wstring( L"movie" ) )
			{
				DictionaryExtension::AddOrOverwrite(SpecialLevel, count, boost::make_shared<Tuple<std::wstring, std::wstring> >( identifier, data ) );
				Seeds.push_back( L"" );
				count++;
			}
			else if ( identifier == std::wstring( L"end" ) )
			{
				DictionaryExtension::AddOrOverwrite(SpecialLevel, count, boost::make_shared<Tuple<std::wstring, std::wstring> >( identifier, std::wstring( L"" ) ) );
				Seeds.push_back( L"" );
				count++;
			}
			else if ( identifier == std::wstring( L"seed" ) )
			{
				std::wstring seed = data;
				seed += Format( _T( "level:%d;index:%d;" ), level, count );
				LastRealLevelIndex = level;

				Seeds.push_back( seed );
				count++;
				level++;
			}

			line = reader.ReadLine();
		}

        // Mark end of last chapter
        if ( LastRealLevelIndex > 0 )
        {
            ChapterEnd[ LastSetChapter ] = LastRealLevelIndex;
            LastRealLevelIndex = -1;
        }
	}

	boost::shared_ptr<LevelSeedData> CampaignSequence::MakeActionSeed( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Level> > > SeedAction )
	{
		boost::shared_ptr<LevelSeedData> seed = boost::make_shared<LevelSeedData>();
		seed->MyGameType = ActionGameData::Factory;

		seed->PostMake->Add( SeedAction );

		return seed;
	}

	boost::shared_ptr<LevelSeedData> CampaignSequence::GetSeed( int Index )
	{
		if ( SpecialLevel.find( Index ) != SpecialLevel.end() )
		{
			boost::shared_ptr<Tuple<std::wstring, std::wstring> > data = SpecialLevel[ Index ];

			if ( data->Item1 == std::wstring( L"end" ) )
			{
					return MakeActionSeed( boost::make_shared<EndActionProxy>() );

			}
			else if ( data->Item1 == std::wstring( L"movie" ) )
			{
					boost::shared_ptr<Lambda_1<boost::shared_ptr<Level> > > temp = MakeWatchMovieAction( data->Item2 );
					return MakeActionSeed( temp );

			}
			else
			{
					return 0;
			}
		}
		else
		{
			boost::shared_ptr<CloudberryKingdom::LevelSeedData> seed = LevelSequence::GetSeed( Index );

			seed->PostMake->Add( boost::make_shared<PostMakeCampaignProxy>() );

			return seed;
		}
	}

	void CampaignSequence::PostMakeCampaign( const boost::shared_ptr<Level> &level )
	{
		if ( level->MyLevelSeed->MyGameType == ActionGameData::Factory )
			return;

		if ( level->MyLevelSeed->MySong == 0 )
		{
			if ( !MusicStarted )
			{
				Tools::SongWad->SetPlayList(Tools::SongList_Standard);
				Tools::SongWad->Shuffle();
				LevelSeedData::WaitThenPlay(level->MyGame, 40, 0);
			}
		}
		else
		{
			Tools::SongWad->SuppressNextInfoDisplay = true;
		}
		MusicStarted = true;

		level->MyGame->OnCoinGrab->Add( boost::make_shared<OnCoinGrabProxy>() );
		level->MyGame->OnCompleteLevel->Add( boost::make_shared<OnCompleteLevelProxy>() );

        // Level Title only
        //var title = new LevelTitle(string.Format("{1} {0}", level.MyLevelSeed.LevelNum, Localization::WordString(Localization::Words_Level)));
            
        // Level Title plus Hero Name
        if ( !level->MyLevelSeed->NewHero && !level->MyLevelSeed->ShowChapterName )
        {
            boost::shared_ptr<LevelTitle> title = MakeMagic( LevelTitle, ( Format( _T( "%ls %d" ), Localization::WordString( Localization::Words_Level ).c_str(), level->MyLevelSeed->LevelNum ) ) );
            title->Shift( Vector2(0, -45) );
            level->MyGame->AddGameObject( title );
        }

        //if (!level.MyLevelSeed.NewHero)
        //{
        //    var hero_title = new LevelTitle(string.Format("{0}", Localization::WordString(level.DefaultHeroType.Name)));
        //    hero_title.Shift(new Vector2(0, -180));
        //    level.MyGame.AddGameObject(hero_title);
        //}

        if ( level->MyLevelSeed->Darkness )
        {
            GameData::UseBobLighting( level, 0 );
            Background::AddDarkLayer( level->MyBackground );
        }

        //boost::shared_ptr<GUI_CampaignScore> CScore = MakeMagic( GUI_CampaignScore, () );
        //CScore->PreventRelease = false;
		//level->MyGame->AddGameObject( CScore );
        boost::shared_ptr<GUI_Level> CLevel = MakeMagic( GUI_Level, ( level->MyLevelSeed->LevelNum ) );
			boost::shared_ptr<EzText> _t;
			_t = CLevel->MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2( 0.f, 0.f ) ); _t->setScale( 0.55f ); }
			CLevel->MyPile->setPos( Vector2( 1590.556f, 856.0002f ) );
        CLevel->PreventRelease = false;
		level->MyGame->AddGameObject( CLevel );
		
		level->MyGame->MyBankType = GameData::BankType_CAMPAIGN;
	}

	void CampaignSequence::OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj )
	{
		std::vector<boost::shared_ptr<PlayerData> > vec = PlayerManager::getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
			( *player )->CampaignCoins++;
	}

	void CampaignSequence::OnCompleteLevel( const boost::shared_ptr<Level> &level )
	{
		MarkProgress( level );

		//SaveGroup::SaveAll();

        // Check for end of chapter
		for ( std::map<int, int>::const_iterator key = instance->ChapterEnd.begin(); key != instance->ChapterEnd.end(); key++ )
		{
            if ( key->second == level->MyLevelSeed->LevelNum )
            {
                ChapterFinishing = key->first;
                if (ChapterFinishing == 0) ChapterFinishing = -1;
                break;
            }
		}
	}

	void CampaignSequence::MarkProgress( const boost::shared_ptr<Level> &level )
	{
		std::vector<boost::shared_ptr<PlayerData> > vec = PlayerManager::getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
		{
			if ( ( *player )->CampaignLevel < level->MyLevelSeed->LevelNum  ||
				 ( *player )->CampaignIndex < level->MyLevelSeed->LevelIndex )
			{
				CloudberryKingdomGame::CampaignProgressMade = true;
			}

			( *player )->CampaignLevel = __max( ( *player )->CampaignLevel, level->MyLevelSeed->LevelNum );
			( *player )->CampaignIndex = __max( ( *player )->CampaignIndex, level->MyLevelSeed->LevelIndex );

            ( *player )->Changed = true;
		}
	}

	boost::shared_ptr<Lambda_1<boost::shared_ptr<Level> > > CampaignSequence::MakeWatchMovieAction( const std::wstring &movie )
	{
		return boost::make_shared<WatchMovieLambda>( movie );
	}

	void CampaignSequence::EndAction( const boost::shared_ptr<Level> &level )
	{
		level->MyGame->EndGame->Apply( false );
		
		CheckForFinishedChapter();
	}

	CampaignSequence::CampaignSequence()
	{
		InitializeInstanceFields();
		
		MusicStarted = false;
		ChapterFinishing = -1;

		MakeSeedList();
	}

	void CampaignSequence::InitializeInstanceFields()
	{
		StartLevel = 0;

		ChapterStart = std::map<int, int>();
		SpecialLevel = std::map<int, boost::shared_ptr<Tuple<std::wstring, std::wstring> > >();
	}
}
