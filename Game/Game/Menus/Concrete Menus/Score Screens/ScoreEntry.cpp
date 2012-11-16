#include <global_header.h>



namespace CloudberryKingdom
{

	const std::wstring &ScoreEntry::getDefaultName() const
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
		this->GamerTag_Renamed = _T( "" );
		this->Fake = true;
	}

	ScoreEntry::ScoreEntry( const std::wstring &GamerTag_Renamed, int Game, int Value, int Score, int Level_Renamed, int Attempts, int Time, int Date )
	{
		InitializeInstanceFields();
		if ( GamerTag_Renamed == _T( "" ) )
			GamerTag_Renamed = getDefaultName();
		this->GamerTag_Renamed = GamerTag_Renamed;

		this->GamerTag_Renamed = GamerTag_Renamed;
		this->GameId = Game;
		this->Value = Value;
		this->Score = Score;
		this->Level_Renamed = Level_Renamed;
		this->Attempts = Attempts;
		this->Time = Time;
		this->Date = Date;
	}

	void ScoreEntry::WriteChunk_1000( const std::shared_ptr<BinaryWriter> &writer )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = 1000;

		chunk->Write( Fake );
		chunk->Write( GamerTag_Renamed );
		chunk->Write( GameId );
		chunk->Write( Value );
		chunk->Write( Score );
		chunk->Write( Level_Renamed );
		chunk->Write( Attempts );
		chunk->Write( Time );
		chunk->Write( Date );

		chunk->Finish( writer );
	}

	void ScoreEntry::ReadChunk_1000( const std::shared_ptr<Chunk> &chunk )
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
			return _T( "" );

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

		return _T( "" );
	}

	std::wstring ScoreEntry::ScoreToString()
	{
		return std::wstring::Format( _T( "{0:n0}" ), Score );
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
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		std::wstring tag = GamerTag_Renamed.ToString();

		int NumDots = Length - score.length() - tag.length();
		if ( NumDots < 0 )
			NumDots = 0;

		for ( int i = 0; i < NumDots; i++ )
			score += _T( "." );
		return score + tag;
	}

	std::wstring ScoreEntry::DottedScore( const std::wstring &root, int score, int Length, int MinDots )
	{
		std::wstring scorestr = StringConverterHelper::toString( score );

		int NumDots = __max( MinDots, Length - scorestr.length() - root.length() );

		for ( int i = 0; i < NumDots; i++ )
			root += _T( "." );
		return root + scorestr;
	}

	void ScoreEntry::InitializeInstanceFields()
	{
		Fake = false;
		MyFormat = Format_SCORE;
	}
}
