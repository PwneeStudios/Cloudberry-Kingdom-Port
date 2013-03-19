#include <global_header.h>

#include <Hacks/String.h>

#ifdef CAFE
	#include <cafe/os.h>
	#include <time.h>
#endif

namespace CloudberryKingdom
{

	const std::wstring ScoreEntry::getDefaultName()
	{
		return PlayerManager::GetGroupGamerTag( 18 );
	}

	ScoreEntry::ScoreEntry()
	{
		InitializeInstanceFields();
	}

	ScoreEntry::ScoreEntry( int Score )
	{
		InitializeInstanceFields();
		this->Value = Score;
		this->GamerTag_Renamed = std::wstring( L"" );
		this->Fake = true;
	}

	ScoreEntry::ScoreEntry( std::wstring GamerTag_Renamed, int Game, int Value, int Score, int Level_Renamed, int Attempts, int Time, int Date )
	{
		InitializeInstanceFields();
		if ( GamerTag_Renamed == std::wstring( L"" ) )
			GamerTag_Renamed = getDefaultName();
		
#ifdef CAFE
		OSCalendarTime td;
		OSTicksToCalendarTime( OSGetTime(), &td );
		struct tm theTime;
		theTime.tm_sec = td.sec;
		theTime.tm_min = td.min;
		theTime.tm_hour = td.hour;
		theTime.tm_mday = td.mday;
		theTime.tm_mon = td.mon;
		theTime.tm_year = td.year;
		theTime.tm_yday = td.yday;
		/*time_t currentTime;
		time( &currentTime );
		struct tm *theTime = localtime( &currentTime );*/

		char timeStr[ 64 ];
		strftime( timeStr, sizeof( timeStr ), "%x", &theTime );
		this->GamerTag_Renamed = Utf8ToWstring( timeStr );
#else
		this->GamerTag_Renamed = GamerTag_Renamed;
#endif
		this->GameId = Game;
		this->Value = Value;
		this->Score = Score;
		this->Level_Renamed = Level_Renamed;
		this->Attempts = Attempts;
		this->Time = Time;
		this->Date = Date;
	}

	void ScoreEntry::WriteChunk_1000( const boost::shared_ptr<BinaryWriter> &writer )
	{
		boost::shared_ptr<Chunk> chunk = boost::make_shared<Chunk>();
		chunk->Type = 1000;

		WriteMeat( chunk );

		chunk->Finish( writer );
	}

	void ScoreEntry::WriteChunk_2000( const boost::shared_ptr<BinaryWriter> &writer )
	{
		boost::shared_ptr<Chunk> chunk = boost::make_shared<Chunk>();
		chunk->Type = 2000;

		WriteMeat( chunk );

		chunk->Finish( writer );
	}

	void ScoreEntry::WriteMeat( boost::shared_ptr<Chunk> chunk )
	{
		chunk->Write( Fake );
		chunk->Write( GamerTag_Renamed );
		chunk->Write( GameId );
		chunk->Write( Value );
		chunk->Write( Score );
		chunk->Write( Level_Renamed );
		chunk->Write( Attempts );
		chunk->Write( Time );
		chunk->Write( Date );
	}

	void ScoreEntry::ReadChunk_1000( const boost::shared_ptr<Chunk> &chunk )
	{
		Fake = chunk->ReadBool();
		GamerTag_Renamed = chunk->ReadString();
		GameId = chunk->ReadInt();
		Value = chunk->ReadInt();
		Score = chunk->ReadInt();
		Level_Renamed = chunk->ReadInt();
		Attempts = chunk->ReadInt();
		Time = chunk->ReadInt();
		Date = chunk->ReadInt();
	}

	std::wstring ScoreEntry::ToString()
	{
		return ToString( 0 );
	}

	std::wstring ScoreEntry::_ToString()
	{
		return _ToString( MyFormat );
	}

	std::wstring ScoreEntry::_ToString( Format format )
	{
		if ( Fake )
			return std::wstring( L"" );

		switch ( format )
		{
			case Format_SCORE:
				return ScoreToString();
			case Format_LEVEL:
				return LevelToString();
			case Format_ATTEMPTS:
				return AttemptsToString();
			case Format_TIME:
				return TimeToString();
		}

		return std::wstring( L"" );
	}

	std::wstring ScoreEntry::ScoreToString()
	{
		// FIXME: return ::Format( _T( "{0:n0}" ), Score );
		return FormatWithSeparators( Score );
	}

	std::wstring ScoreEntry::TimeToString()
	{
		return CoreMath::Time( Time );
	}

	std::wstring ScoreEntry::AttemptsToString()
	{
		return StringConverterHelper::toString( Attempts );
	}

	std::wstring ScoreEntry::LevelToString()
	{
		return StringConverterHelper::toString( Level_Renamed );
	}

	std::wstring ScoreEntry::ToString( int Length )
	{
		std::wstring score = _ToString();
		std::wstring tag = GamerTag_Renamed;

		int NumDots = Length - score.length() - tag.length();
		if ( NumDots < 0 )
			NumDots = 0;

		for ( int i = 0; i < NumDots; i++ )
			score.append( std::wstring( L"." ) );
		return score + tag;
	}

	std::wstring ScoreEntry::DottedScore( std::wstring root, int score, int Length, int MinDots )
	{
		std::wstring scorestr = StringConverterHelper::toString( score );

		int NumDots = __max( MinDots, Length - static_cast<int>( scorestr.length() - root.length() ) );

		for ( int i = 0; i < NumDots; i++ )
			root.append( std::wstring( L"." ) );
		return root + scorestr;
	}

	void ScoreEntry::InitializeInstanceFields()
	{
		GameId = 0;
		Value = 0; Score = 0; Level_Renamed = 0; Attempts = 0; Time = 0; Date = 0;

		Fake = false;
		MyFormat = Format_SCORE;
	}
}
