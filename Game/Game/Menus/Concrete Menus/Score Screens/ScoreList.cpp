#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/String.h>

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
				return std::wstring( L"" );
			case ScoreEntry::Format_LEVEL:
				return std::wstring( L"" );
			default:
				return std::wstring( L"" );
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

		Scores = std::vector<boost::shared_ptr<ScoreEntry> >( Capacity );

		for ( int i = 0; i < Capacity; i++ )
			Scores.push_back( boost::make_shared<ScoreEntry>( DefaultValue ) );
	}

	bool ScoreList::Qualifies( const boost::shared_ptr<ScoreEntry> &Entry )
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

	std::wstring ScoreList::ScoreString( const boost::shared_ptr<ScoreEntry> &score, int Length )
	{
		score->MyFormat = MyFormat;

		int Rank = IndexOf( Scores, score ) + 1;
		std::wstring RankStr = StringConverterHelper::toString( Rank ) + std::wstring( L". " );

		while ( RankStr.length() < 4 )
			RankStr += std::wstring( L" " );

		if ( !score->Fake )
			RankStr += GetPrefix();

		//std::wstring ScoreStr = Format( _T( "{0:n}" ), score );
		std::wstring ScoreStr = FormatWithSeparators( score->Score );
		return RankStr + score->ToString( Length - RankStr.length() );
	}

	void ScoreList::Add( const boost::shared_ptr<ScoreEntry> &score )
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

	int ScoreList::ScoreCompare( const boost::shared_ptr<ScoreEntry> &score1, const boost::shared_ptr<ScoreEntry> &score2 )
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
