#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	void ScoreDatabase::InitializeStatics()
	{
		ScoreDatabase::MostRecentScoreDate = 0;
		ScoreDatabase::Capacity = 20;
	}

	// Statics
	boost::shared_ptr<ScoreDatabase> ScoreDatabase::Instance;
	int ScoreDatabase::MostRecentScoreDate;
	int ScoreDatabase::Capacity;
	std::map<int, std::vector<boost::shared_ptr<ScoreEntry> > > ScoreDatabase::Games;

	int ScoreDatabase::CurrentDate()
	{
		TimeSpan t = ( DateTime::Now() - DateTime( 2000, 1, 1 ) );
		int minutes = static_cast<int>( t.TotalMinutes );

		return minutes;
	}

	void ScoreDatabase::Initialize()
	{
		Instance = boost::make_shared<ScoreDatabase>();
		Instance->ContainerName = std::wstring( L"HighScores" );
		Instance->FileName = std::wstring( L"HighScores" );
		Instance->FailLoad();

		MostRecentScoreDate = CurrentDate();

		SaveGroup::Add( Instance );
	}

	void ScoreDatabase::Serialize( const boost::shared_ptr<BinaryWriter> &writer )
	{
		for ( std::map<int, std::vector<boost::shared_ptr<ScoreEntry> > >::const_iterator list = Games.begin(); list != Games.end(); ++list )
			for ( std::vector<boost::shared_ptr<ScoreEntry> >::const_iterator score = list->second.begin(); score != list->second.end(); ++score )
				( *score )->WriteChunk_1000( writer );
	}

	void ScoreDatabase::FailLoad()
	{
		Games = std::map<int, std::vector<boost::shared_ptr<ScoreEntry> > >();
	}

	void ScoreDatabase::Deserialize( std::vector<unsigned char> Data )
	{
		//for ( CloudberryKingdom::Chunks::const_iterator chunk = Chunks::Get( Data )->begin(); chunk != Chunks::Get(Data)->end(); ++chunk )
		boost::shared_ptr<Chunks> chunks = Chunks::Get( Data );
		chunks->StartGettingChunks();
		while( chunks->HasChunk() )
		{
			boost::shared_ptr<Chunk> chunk = chunks->GetChunk();
			//switch ( ( *chunk )->Type )
			switch ( chunk->Type )
			{
				case 1000:
					boost::shared_ptr<ScoreEntry> score = boost::make_shared<ScoreEntry>();
					score->ReadChunk_1000( chunk );
					Add( score );
					break;
			}
		}
	}

	void ScoreDatabase::EnsureList( int Game )
	{
		if ( Games.find( Game ) != Games.end() )
			return;

		Games[ Game ] = std::vector<boost::shared_ptr<ScoreEntry> >();
	}

	boost::shared_ptr<ScoreList> ScoreDatabase::GetList( int Game )
	{
		EnsureList( Game );

//C# TO C++ CONVERTER NOTE: The variable ScoreList was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<ScoreList> ScoreList_Renamed = boost::make_shared<ScoreList>( 10, 0 );
		std::vector<boost::shared_ptr<ScoreEntry> > Scores = Games[ Game ];

		int Count = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<ScoreEntry> >::const_iterator score = Scores.begin(); score != Scores.end(); ++score )
		{
			ScoreList_Renamed->Add( *score );
			Count++;
			if ( Count >= 10 )
				break;
		}

		return ScoreList_Renamed;
	}

	bool ScoreDatabase::Qualifies( int Game, int Score )
	{
		EnsureList( Game );

		std::vector<boost::shared_ptr<ScoreEntry> > Scores = Games[ Game ];
		return static_cast<int>( Scores.size() ) < Capacity || Score > Min(Scores)->Value || Min(Scores)->Fake;
	}

	boost::shared_ptr<ScoreEntry> ScoreDatabase::Max( std::vector<boost::shared_ptr<ScoreEntry> > &Scores )
	{
		if ( Scores.empty() )
			return boost::make_shared<ScoreEntry>( 0 );
		else
			return Scores[ 0 ];
	}

	boost::shared_ptr<ScoreEntry> ScoreDatabase::Max( int GameId )
	{
		EnsureList( GameId );
		return Max( Games[ GameId ] );
	}

	boost::shared_ptr<ScoreEntry> ScoreDatabase::Min( std::vector<boost::shared_ptr<ScoreEntry> > &Scores )
	{
		if ( Scores.empty() )
			return boost::make_shared<ScoreEntry>( 0 );
		else
			return Scores[ Scores.size() - 1 ];
	}

	boost::shared_ptr<ScoreEntry> ScoreDatabase::Min( int GameId )
	{
		EnsureList( GameId );
		return Min( Games[ GameId ] );
	}

	void ScoreDatabase::Add( const boost::shared_ptr<ScoreEntry> &score )
	{
		std::vector<boost::shared_ptr<PlayerData> > vec = PlayerManager::getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
			( *player )->AddHighScore( score );

		EnsureList( score->GameId );

		if ( !Qualifies( score->GameId, score->Value ) )
			return;

		std::vector<boost::shared_ptr<ScoreEntry> > list = Games[ score->GameId ];

		list.push_back( score );
		Sort( list );
		TrimExcess( list );

		// Mark this object as changed, so that it will be saved to disk.
		Instance->Changed = true;
	}

	void ScoreDatabase::TrimExcess( std::vector<boost::shared_ptr<ScoreEntry> > &Scores )
	{
		// FIXME: Logic problem?
		if ( static_cast<int>( Scores.size() ) > Capacity )
			Scores.erase( Scores.begin() + Scores.size() - Capacity, Scores.end() );
			//Scores.RemoveRange( Scores.size() - 1, Scores.size() - Capacity );
	}

	int ScoreDatabase::ScoreCompare( const boost::shared_ptr<ScoreEntry> &score1, const boost::shared_ptr<ScoreEntry> &score2 )
	{
		return score2->Value - score1->Value;
	}

	bool ScoreDatabase::ScoreCompareStrictWeak( const boost::shared_ptr<ScoreEntry> &score1, const boost::shared_ptr<ScoreEntry> &score2 )
	{
		return ScoreCompare( score1, score2 ) < 0;
	}

	void ScoreDatabase::Sort( std::vector<boost::shared_ptr<ScoreEntry> > &Scores )
	{
		//Scores.Sort( ScoreCompare );
		::Sort( Scores, ScoreDatabase::ScoreCompareStrictWeak );
	}
}
