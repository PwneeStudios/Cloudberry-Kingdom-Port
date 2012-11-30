#include <global_header.h>



namespace CloudberryKingdom
{

	void PlayerStats::WriteChunk_4( const std::shared_ptr<BinaryWriter> &writer )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = 4;

		chunk->WriteSingle( 0, Score );
		chunk->WriteSingle( 1, Coins );
		chunk->WriteSingle( 2, Blobs );
		chunk->WriteSingle( 3, CoinsSpentAtShop );
		chunk->WriteSingle( 4, TotalCoins );
		chunk->WriteSingle( 5, TotalBlobs );
		chunk->WriteSingle( 6, Levels );
		chunk->WriteSingle( 7, Checkpoints );
		chunk->WriteSingle( 8, Jumps );
		chunk->WriteSingle( 10, TimeAlive );

		for ( int i = 0; i < DeathsBy.size(); i++ )
			WriteDeathChunk_9( chunk, i );

		chunk->Finish( writer );
	}

	void PlayerStats::ReadChunk_4( const std::shared_ptr<Chunk> &ParentChunk )
	{
		for ( CloudberryKingdom::Chunk::const_iterator chunk = ParentChunk->begin(); chunk != ParentChunk->end(); ++chunk )
		{
			switch ( ( *chunk )->Type )
			{
				case 0:
					( *chunk )->ReadSingle( Score );
					break;
				case 1:
					( *chunk )->ReadSingle( Coins );
					break;
				case 2:
					( *chunk )->ReadSingle( Blobs );
					break;
				case 3:
					( *chunk )->ReadSingle( CoinsSpentAtShop );
					break;
				case 4:
					( *chunk )->ReadSingle( TotalCoins );
					break;
				case 5:
					( *chunk )->ReadSingle( TotalBlobs );
					break;
				case 6:
					( *chunk )->ReadSingle( Levels );
					break;
				case 7:
					( *chunk )->ReadSingle( Checkpoints );
					break;
				case 8:
					( *chunk )->ReadSingle( Jumps );
					break;
				case 10:
					( *chunk )->ReadSingle( TimeAlive );
					break;

				case 9:
					ReadDeathChunk_9( *chunk );
					break;
			}
		}
	}

	void PlayerStats::WriteDeathChunk_9( const std::shared_ptr<Chunk> &ParentChunk, int Index )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = 9;

		chunk->Write( Index );
		chunk->Write( DeathsBy[ Index ] );

		chunk->Finish( ParentChunk );
	}

	void PlayerStats::ReadDeathChunk_9( const std::shared_ptr<Chunk> &chunk )
	{
		int Index = chunk->ReadInt();
		if ( Index >= 0 && Index < DeathsBy.size() )
			DeathsBy[ Index ] = chunk->ReadInt();
	}

	std::shared_ptr<PlayerStats> PlayerStats::Absorb( const std::shared_ptr<PlayerStats> &stats )
	{
		for ( unknown::const_iterator info = GetType()->GetFields().begin(); info != GetType()->GetFields().end(); ++info )
		{
			if ( ( *info )->FieldType == int::typeid )
				( *info )->SetValue( shared_from_this(), static_cast<int>( ( *info )->GetValue( shared_from_this() ) ) + static_cast<int>( ( *info )->GetValue( stats ) ) );
		}

		for ( int i = 0; i < DeathsBy.size(); i++ )
			DeathsBy[ i ] += stats->DeathsBy[ i ];

		return this;
	}

	void PlayerStats::Clean()
	{
		for ( unknown::const_iterator info = GetType()->GetFields().begin(); info != GetType()->GetFields().end(); ++info )
		{
			if ( ( *info )->FieldType == int::typeid )
				( *info )->SetValue( shared_from_this(), 0 );
		}

		for ( int i = 0; i < DeathsBy.size(); i++ )
			DeathsBy[ i ] = 0;
	}

	const std::wstring &PlayerStats::getLifeExpectancy() const
	{
		TimeSpan time = TimeSpan( 0, 0, getLifeExpectancy_Frames() / 60 );
		if ( time.Hours == 0 )
			return Format( _T( "{0}:{1:00}" ), time.Minutes, time.Seconds );
		else
			return Format( _T( "{0}:{1}:{2:00}" ), time.Hours, time.Minutes, time.Seconds );
	}

	const int &PlayerStats::getLifeExpectancy_Frames() const
	{
		if ( DeathsBy[ static_cast<int>( Bob::BobDeathType_TOTAL ) ] <= 0 )
			return TimeAlive;
		else
			return static_cast<int>( static_cast<float>( TimeAlive ) / static_cast<float>( 1 + DeathsBy[ static_cast<int>( Bob::BobDeathType_TOTAL ) ] ) );
	}

	const int &PlayerStats::getTotalDeaths() const
	{
		return DeathsBy[ static_cast<int>( Bob::BobDeathType_TOTAL ) ];
	}

	const int &PlayerStats::getCoinPercentGotten() const
	{
		if ( TotalCoins == 0 )
			return 100;
		else
			return static_cast<int>( 100 * static_cast<float>( Coins ) / static_cast<float>( TotalCoins ) );
	}

	PlayerStats::PlayerStats()
	{
		DeathsBy = std::vector<int>( BobDeathType_LENGTH );

		Clean();
	}
}
