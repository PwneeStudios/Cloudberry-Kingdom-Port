#include <global_header.h>








namespace CloudberryKingdom
{

std::shared_ptr<ScoreDatabase> ScoreDatabase::Instance = 0;
int ScoreDatabase::MostRecentScoreDate = 0;

	int ScoreDatabase::CurrentDate()
	{
		TimeSpan t = ( DateTime::Now - DateTime( 2000, 1, 1 ) );
		int minutes = static_cast<int>( t.TotalMinutes );

		return minutes;
	}

int ScoreDatabase::Capacity = 20;
std::unordered_map<int, std::vector<ScoreEntry*> > ScoreDatabase::Games = 0;

	void ScoreDatabase::Initialize()
	{
		Instance = std::make_shared<ScoreDatabase>();
		Instance->ContainerName = _T( "HighScores" );
		Instance->FileName = _T( "HighScores" );
		Instance->FailLoad();

		MostRecentScoreDate = CurrentDate();

		SaveGroup::Add( Instance );
	}

	void ScoreDatabase::Serialize( const std::shared_ptr<BinaryWriter> &writer )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::unordered_map<int, std::vector<ScoreEntry*> >::const_iterator list = Games.begin(); list != Games.end(); ++list )
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( unknown::const_iterator score = list->Value.begin(); score != list->Value.end(); ++score )
				( *score )->WriteChunk_1000( writer );
	}

	void ScoreDatabase::FailLoad()
	{
		Games = std::unordered_map<int, std::vector<ScoreEntry*> >();
	}

	void ScoreDatabase::Deserialize( std::vector<unsigned char> Data )
	{
		for ( CloudberryKingdom::Chunks::const_iterator chunk = Chunks::Get( Data )->begin(); chunk != Chunks::Get(Data)->end(); ++chunk )
		{
			switch ( ( *chunk )->Type )
			{
				case 1000:
					std::shared_ptr<ScoreEntry> score = std::make_shared<ScoreEntry>();
					score->ReadChunk_1000( *chunk );
					Add( score );
					break;
			}
		}
	}

	void ScoreDatabase::EnsureList( int Game )
	{
		if ( Games.find( Game ) != Games.end() )
			return;

		Games[ Game ] = std::vector<ScoreEntry*>();
	}

	std::shared_ptr<ScoreList> ScoreDatabase::GetList( int Game )
	{
		EnsureList( Game );

//C# TO C++ CONVERTER NOTE: The variable ScoreList was renamed since it is named the same as a user-defined type:
		std::shared_ptr<ScoreList> ScoreList_Renamed = std::make_shared<ScoreList>( 10, 0 );
		std::vector<ScoreEntry*> Scores = Games[ Game ];

		int Count = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector::const_iterator score = Scores.begin(); score != Scores.end(); ++score )
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

		std::vector<ScoreEntry*> Scores = Games[ Game ];
		return Scores.size() < Capacity || Score > Min(Scores)->Value || Min(Scores)->Fake;
	}

	std::shared_ptr<ScoreEntry> ScoreDatabase::Max( std::vector<ScoreEntry*> &Scores )
	{
		if ( Scores.empty() )
			return std::make_shared<ScoreEntry>( 0 );
		else
			return Scores[ 0 ];
	}

	std::shared_ptr<ScoreEntry> ScoreDatabase::Max( int GameId )
	{
		EnsureList( GameId );
		return Max( Games[ GameId ] );
	}

	std::shared_ptr<ScoreEntry> ScoreDatabase::Min( std::vector<ScoreEntry*> &Scores )
	{
		if ( Scores.empty() )
			return std::make_shared<ScoreEntry>( 0 );
		else
			return Scores[ Scores.size() - 1 ];
	}

	std::shared_ptr<ScoreEntry> ScoreDatabase::Min( int GameId )
	{
		EnsureList( GameId );
		return Min( Games[ GameId ] );
	}

	void ScoreDatabase::Add( const std::shared_ptr<ScoreEntry> &score )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<PlayerData*>::const_iterator player = PlayerManager::getExistingPlayers().begin(); player != PlayerManager::getExistingPlayers().end(); ++player )
			( *player )->AddHighScore( score );

		EnsureList( score->GameId );

		if ( !Qualifies( score->GameId, score->Value ) )
			return;

		std::vector<ScoreEntry*> list = Games[ score->GameId ];

		list.push_back( score );
		Sort( list );
		TrimExcess( list );

		// Mark this object as changed, so that it will be saved to disk.
		Instance->Changed = true;
	}

	void ScoreDatabase::TrimExcess( std::vector<ScoreEntry*> &Scores )
	{
		if ( Scores.size() > Capacity )
			Scores.RemoveRange( Scores.size() - 1, Scores.size() - Capacity );
	}

	int ScoreDatabase::ScoreCompare( const std::shared_ptr<ScoreEntry> &score1, const std::shared_ptr<ScoreEntry> &score2 )
	{
		return score2->Value - score1->Value;
	}

	void ScoreDatabase::Sort( std::vector<ScoreEntry*> &Scores )
	{
		Scores.Sort( ScoreCompare );
	}
}
