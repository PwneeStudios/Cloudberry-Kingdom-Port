#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;


namespace CloudberryKingdom
{

	void CampaignSequence::PostMakeCampaignProxy::Apply( const std::shared_ptr<Level> &level )
	{
		CampaignSequence::PostMakeCampaign( level );
	}

	void CampaignSequence::OnCoinGrabProxy::Apply( const std::shared_ptr<ObjectBase> &obj )
	{
		CampaignSequence::OnCoinGrab( obj );
	}

	void CampaignSequence::OnCompleteLevelProxy::Apply( const std::shared_ptr<Level> &level )
	{
		CampaignSequence::OnCompleteLevel( level );
	}

	CampaignSequence::WatchMovieLambda::WatchMovieLambda( const std::wstring &movie )
	{
		this->movie = movie;
	}

	void CampaignSequence::WatchMovieLambda::Apply( const std::shared_ptr<Level> &level )
	{
		MainVideo::StartVideo_CanSkipIfWatched_OrCanSkipAfterXseconds( movie, 1.5f );
		( static_cast<ActionGameData*>( level->MyGame ) )->Done = true;
	}

	void CampaignSequence::EndActionProxy::Apply( const std::shared_ptr<Level> &level )
	{
		CampaignSequence::EndAction( level );
	}

const std::shared_ptr<CampaignSequence> CampaignSequence::instance = std::make_shared<CampaignSequence>();

	const std::shared_ptr<CampaignSequence> &CampaignSequence::getInstance() const
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
		std::shared_ptr<FileStream> stream = File->Open( _T( "Content\\Campaign\\CampaignList.txt" ), FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>( stream );

		std::wstring line;

		int level = 1, count = 1;

		line = reader->ReadLine();
		while ( line != _T( "" ) )
		{
			line = Tools::RemoveComment_DashStyle( line );
			if ( line == _T( "" ) || line.length() <= 1 )
			{
				line = reader->ReadLine();
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
				data = _T( "" );
			}

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//			switch (identifier)
//ORIGINAL LINE: case "chapter":
			if ( identifier == _T( "chapter" ) )
			{
					int chapter = int::Parse( data );
					ChapterStart.AddOrOverwrite( chapter, count );

			}
//ORIGINAL LINE: case "movie":
			else if ( identifier == _T( "movie" ) )
			{
					SpecialLevel.AddOrOverwrite( count, std::make_shared<Tuple<std::wstring, std::wstring> >( identifier, data ) );
					Seeds.push_back( 0 );
					count++;


			}
//ORIGINAL LINE: case "end":
			else if ( identifier == _T( "end" ) )
			{
					SpecialLevel.AddOrOverwrite( count, std::make_shared<Tuple<std::wstring, std::wstring> >( identifier, 0 ) );
					Seeds.push_back( 0 );
					count++;


			}
//ORIGINAL LINE: case "seed":
			else if ( identifier == _T( "seed" ) )
			{
					std::wstring seed = data;
					seed += std::wstring::Format( _T( "level:{0};" ), level );

					Seeds.push_back( seed );
					count++;
					level++;

			}

			line = reader->ReadLine();
		}

		reader->Close();
		stream->Close();
	}

	std::shared_ptr<LevelSeedData> CampaignSequence::MakeActionSeed( const std::shared_ptr<Lambda_1<Level*> > &SeedAction )
	{
		std::shared_ptr<LevelSeedData> seed = std::make_shared<LevelSeedData>();
		seed->MyGameType = ActionGameData::Factory;

		seed->PostMake->Add( SeedAction );

		return seed;
	}

	std::shared_ptr<LevelSeedData> CampaignSequence::GetSeed( int Index )
	{
		if ( SpecialLevel.find( Index ) != SpecialLevel.end() )
		{
			std::shared_ptr<Tuple<std::wstring, std::wstring> > data = SpecialLevel[ Index ];
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//			switch (data.Item1)
//ORIGINAL LINE: case "end":
			if ( data->Item1 == _T( "end" ) )
			{
					return MakeActionSeed( std::make_shared<EndActionProxy>() );

			}
//ORIGINAL LINE: case "movie":
			else if ( data->Item1 == _T( "movie" ) )
			{
					std::shared_ptr<Lambda_1<Level*> > temp = MakeWatchMovieAction( data->Item2 );
					return MakeActionSeed( temp );

			}
			else
			{
					return 0;
			}
		}
		else
		{
			std::shared_ptr<CloudberryKingdom::LevelSeedData> seed = LevelSequence::GetSeed( Index );

			seed->PostMake->Add( std::make_shared<PostMakeCampaignProxy>() );

			return seed;
		}
	}

	void CampaignSequence::PostMakeCampaign( const std::shared_ptr<Level> &level )
	{
		if ( level->MyLevelSeed->MyGameType == ActionGameData::Factory )
			return;

		level->MyGame->OnCoinGrab->Add( std::make_shared<OnCoinGrabProxy>() );
		level->MyGame->OnCompleteLevel->Add( std::make_shared<OnCompleteLevelProxy>() );

		std::shared_ptr<LevelTitle> title = std::make_shared<LevelTitle>( std::wstring::Format( _T( "{1} {0}" ), level->MyLevelSeed->LevelNum, Localization::WordString( Localization::Words_LEVEL ) ) );
		level->MyGame->AddGameObject( title );

		level->MyGame->AddGameObject( std::make_shared<GUI_CampaignScore>(), std::make_shared<GUI_Level>(level->MyLevelSeed->LevelNum) );

		level->MyGame->MyBankType = GameData::BankType_CAMPAIGN;
	}

	void CampaignSequence::OnCoinGrab( const std::shared_ptr<ObjectBase> &obj )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<PlayerData*>::const_iterator player = PlayerManager::getExistingPlayers().begin(); player != PlayerManager::getExistingPlayers().end(); ++player )
			( *player )->CampaignCoins++;
	}

	void CampaignSequence::OnCompleteLevel( const std::shared_ptr<Level> &level )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<PlayerData*>::const_iterator player = PlayerManager::getExistingPlayers().begin(); player != PlayerManager::getExistingPlayers().end(); ++player )
			( *player )->CampaignLevel = __max( ( *player )->CampaignLevel, level->MyLevelSeed->LevelNum );
	}

	std::shared_ptr<Lambda_1<Level*> > CampaignSequence::MakeWatchMovieAction( const std::wstring &movie )
	{
		return std::make_shared<WatchMovieLambda>( movie );
	}

	void CampaignSequence::EndAction( const std::shared_ptr<Level> &level )
	{
		level->MyGame->EndGame->Apply( false );
	}

	CampaignSequence::CampaignSequence()
	{
		InitializeInstanceFields();
	}

	void CampaignSequence::InitializeInstanceFields()
	{
		ChapterStart = std::unordered_map<int, int>();
		SpecialLevel = std::unordered_map<int, Tuple<std::wstring, std::wstring>*>();
	}
}
