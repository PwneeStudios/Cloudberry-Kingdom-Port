#include <global_header.h>

namespace CloudberryKingdom
{

	Localization::Words ScoreList::GetHeader()
	{
		switch ( MyFormat )
		{
			case ScoreEntry::Format_SCORE:
				return Localization::Words_HIGH_SCORES;
			case ScoreEntry::Format_LEVEL:
				return Localization::Words_BEST_LEVEL;
			default:
				return Localization::Words_NONE;
		}
	}

	std::wstring ScoreList::GetPrefix()
	{
		switch ( MyFormat )
		{
			case ScoreEntry::Format_SCORE:
				return _T( "" );
			case ScoreEntry::Format_LEVEL:
				return _T( "" );
			default:
				return _T( "" );
		}
	}

	ScoreList::ScoreList()
	{
		InitializeInstanceFields();
		Init( 10, 0 );
	}

	ScoreList::ScoreList( int DefaultValue )
	{
		InitializeInstanceFields();
		Init( Capacity, DefaultValue );
	}

	ScoreList::ScoreList( int Capacity, int DefaultValue )
	{
		InitializeInstanceFields();
		Init( Capacity, 0 );
	}

	void ScoreList::Init( int Capacity, int DefaultValue )
	{
		this->DefaultValue = DefaultValue;
		this->Capacity = Capacity;

		Scores = std::vector<std::shared_ptr<ScoreEntry> >( Capacity );

		for ( int i = 0; i < Capacity; i++ )
			Scores.push_back( std::make_shared<ScoreEntry>( DefaultValue ) );
	}

	bool ScoreList::Qualifies( const std::shared_ptr<ScoreEntry> &Entry )
	{
		return static_cast<int>( Scores.size() ) < Capacity || Entry->Value > getBottom();
	}

	const int ScoreList::getBottom() const
	{
		if ( Scores.empty() )
			return 0;
		if ( Scores.empty() )
			return 0;

		return Scores[ Scores.size() - 1 ]->Value;
	}

	std::wstring ScoreList::ScoreString( const std::shared_ptr<ScoreEntry> &score, int Length )
	{
		score->MyFormat = MyFormat;

		int Rank = IndexOf( Scores, score ) + 1;
		std::wstring RankStr = StringConverterHelper::toString( Rank ) + _T( ". " );

		while ( RankStr.length() < 4 )
			RankStr += _T( " " );

		if ( !score->Fake )
			RankStr += GetPrefix();

		std::wstring ScoreStr = Format( _T( "{0:n}" ), score );
		return RankStr + score->ToString( Length - RankStr.length() );
	}

	void ScoreList::Add( const std::shared_ptr<ScoreEntry> &score )
	{
		if ( !Qualifies( score ) )
			return;

		Scores.push_back( score );

		Sort();
		TrimExcess();
	}

	void ScoreList::TrimExcess()
	{
		// FIXME: I think this is useless, so I commented it out.
		//if ( Scores.size() > Capacity )
		//	Scores.RemoveRange( Scores.size() - 1, Scores.size() - Capacity );
	}

	int ScoreList::ScoreCompare( const std::shared_ptr<ScoreEntry> &score1, const std::shared_ptr<ScoreEntry> &score2 )
	{
		return score2->Value - score1->Value;
	}

	void ScoreList::Sort()
	{
		::Sort( Scores, ScoreCompare );
	}

	void ScoreList::InitializeInstanceFields()
	{
		Capacity = 10;
		MyFormat = ScoreEntry::Format_SCORE;
	}
}
