#include <global_header.h>

#include <Hacks/Parse.h>
#include <Hacks/FileReader.h>
#include <Hacks/String.h>
#include <Core\Tools\Set.h>

#include <Game\Video.h>

namespace CloudberryKingdom
{

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

	boost::shared_ptr<CampaignSequence> CampaignSequence::instance = boost::make_shared<CampaignSequence>();

	const boost::shared_ptr<CampaignSequence> &CampaignSequence::getInstance()
	{
		return instance;
	}

	void CampaignSequence::Start( int Chapter )
	{
		int StartLevel = ChapterStart[ Chapter ];

		LevelSequence::Start( StartLevel );
	}

	void CampaignSequence::MakeSeedList()
	{
		Seeds.push_back( 0 );

		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( std::wstring( L"Content/Campaign/CampaignList.txt" ), FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<StreamReader> reader = boost::make_shared<StreamReader>( stream );
#if defined(PC_VERSION)
		FileReader reader = FileReader( std::wstring( L"Content/Campaign/CampaignList.txt" ) );
#else
		FileReader reader = FileReader( std::wstring( L"Campaign/CampaignList.txt" ) );
#endif

		std::wstring line;

		int level = 1, count = 1;

		line = reader.ReadLine();
		while ( line != std::wstring( L"" ) )
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
					int chapter = ParseInt( data );
					//ChapterStart.AddOrOverwrite( chapter, count );
					DictionaryExtension::AddOrOverwrite( ChapterStart, chapter, count );

			}
			else if ( identifier == std::wstring( L"movie" ) )
			{
					DictionaryExtension::AddOrOverwrite(SpecialLevel, count, boost::make_shared<Tuple<std::wstring, std::wstring> >( identifier, data ) );
					Seeds.push_back( 0 );
					count++;


			}
			else if ( identifier == std::wstring( L"end" ) )
			{
					DictionaryExtension::AddOrOverwrite(SpecialLevel, count, boost::make_shared<Tuple<std::wstring, std::wstring> >( identifier, std::wstring( L"" ) ) );
					Seeds.push_back( 0 );
					count++;


			}
			else if ( identifier == std::wstring( L"seed" ) )
			{
					std::wstring seed = data;
					seed += Format( _T( "level:%d;" ), level );

					Seeds.push_back( seed );
					count++;
					level++;

			}

			line = reader.ReadLine();
		}

		//reader->Close();
		//stream->Close();
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

		level->MyGame->OnCoinGrab->Add( boost::make_shared<OnCoinGrabProxy>() );
		level->MyGame->OnCompleteLevel->Add( boost::make_shared<OnCompleteLevelProxy>() );

		boost::shared_ptr<LevelTitle> title = MakeMagic( LevelTitle, ( Format( _T( "%d %ls" ), level->MyLevelSeed->LevelNum, Localization::WordString( Localization::Words_LEVEL ).c_str() ) ) );
		level->MyGame->AddGameObject( title );

		level->MyGame->AddGameObject( MakeMagic( GUI_CampaignScore, () ) );
		level->MyGame->AddGameObject( MakeMagic( GUI_Level, (level->MyLevelSeed->LevelNum) ) );

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
		std::vector<boost::shared_ptr<PlayerData> > vec = PlayerManager::getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
			( *player )->CampaignLevel = __max( ( *player )->CampaignLevel, level->MyLevelSeed->LevelNum );
	}

	boost::shared_ptr<Lambda_1<boost::shared_ptr<Level> > > CampaignSequence::MakeWatchMovieAction( const std::wstring &movie )
	{
		return boost::make_shared<WatchMovieLambda>( movie );
	}

	void CampaignSequence::EndAction( const boost::shared_ptr<Level> &level )
	{
		level->MyGame->EndGame->Apply( false );
	}

	CampaignSequence::CampaignSequence()
	{
		InitializeInstanceFields();
	}

	void CampaignSequence::InitializeInstanceFields()
	{
		ChapterStart = std::map<int, int>();
		SpecialLevel = std::map<int, boost::shared_ptr<Tuple<std::wstring, std::wstring> > >();
	}
}
