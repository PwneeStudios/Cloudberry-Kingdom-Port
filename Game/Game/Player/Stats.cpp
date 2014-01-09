#include <small_header.h>
#include "Game/Player/Stats.h"

#include "Core/Chunk.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Tools/Tools.h"


#include "Hacks/String.h"

namespace CloudberryKingdom
{

	void PlayerStats::WriteChunk_4( const boost::shared_ptr<BinaryWriter> &writer )
	{
		boost::shared_ptr<Chunk> chunk = boost::make_shared<Chunk>();
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
		chunk->WriteSingle( 11, ObstaclesSeen );

		for ( int i = 0; i < static_cast<int>( DeathsBy.size() ); i++ )
			WriteDeathChunk_9( chunk, i );

		chunk->Finish( writer );
	}

	void PlayerStats::ReadChunk_4( const boost::shared_ptr<Chunk> &ParentChunk )
	{
		boost::shared_ptr<Chunks> chunks = Chunks::Get( ParentChunk );
		chunks->StartGettingChunks();

		while( chunks->HasChunk() )
		{
			boost::shared_ptr<Chunk> chunk = chunks->GetChunk();

			switch ( chunk->Type )
			{
				case 0:
					chunk->ReadSingle( Score );
					break;
				case 1:
					chunk->ReadSingle( Coins );
					break;
				case 2:
					chunk->ReadSingle( Blobs );
					break;
				case 3:
					chunk->ReadSingle( CoinsSpentAtShop );
					break;
				case 4:
					chunk->ReadSingle( TotalCoins );
					break;
				case 5:
					chunk->ReadSingle( TotalBlobs );
					break;
				case 6:
					chunk->ReadSingle( Levels );
					break;
				case 7:
					chunk->ReadSingle( Checkpoints );
					break;
				case 8:
					chunk->ReadSingle( Jumps );
					break;
				case 10:
					chunk->ReadSingle( TimeAlive );
					break;
				case 11: chunk->ReadSingle( ObstaclesSeen ); break;

				case 9:
					ReadDeathChunk_9( chunk );
					break;
			}
		}
	}

	void PlayerStats::WriteDeathChunk_9( const boost::shared_ptr<Chunk> &ParentChunk, int Index )
	{
		boost::shared_ptr<Chunk> chunk = boost::make_shared<Chunk>();
		chunk->Type = 9;

		chunk->Write( Index );
		chunk->Write( DeathsBy[ Index ] );

		chunk->Finish( *ParentChunk.get() );
	}

	void PlayerStats::ReadDeathChunk_9( const boost::shared_ptr<Chunk> &chunk )
	{
		int Index = chunk->ReadInt();
		if ( Index >= 0 && Index < static_cast<int>( DeathsBy.size() ) )
			DeathsBy[ Index ] = chunk->ReadInt();
	}

	boost::shared_ptr<PlayerStats> PlayerStats::Absorb( const boost::shared_ptr<PlayerStats> &stats )
	{
		/*
		unknown vec = GetType()->GetFields();
		for ( unknown::const_iterator info = vec.begin(); info != vec.end(); ++info )
		{
			if ( ( *info )->FieldType == int::typeid )
				( *info )->SetValue( shared_from_this(), static_cast<int>( ( *info )->GetValue( shared_from_this() ) ) + static_cast<int>( ( *info )->GetValue( stats ) ) );
		}*/

		// FIXME: Check to make sure it does the same thing.
		Score += stats->Score;
		Coins += stats->Coins;
		Blobs += stats->Blobs;
		CoinsSpentAtShop += stats->CoinsSpentAtShop;

		TotalCoins += stats->TotalCoins;
		TotalBlobs += stats->TotalBlobs;

		Levels += stats->Levels;
		Checkpoints += stats->Checkpoints;
		Jumps += stats->Jumps;
		Berries += stats->Berries;

		TimeAlive += stats->TimeAlive;

		FinalTimeSpentNotMoving += stats->FinalTimeSpentNotMoving;
		FinalTimeSpent += stats->FinalTimeSpent;

		ObstaclesSeen += stats->ObstaclesSeen;

		for ( size_t i = 0; i < DeathsBy.size(); i++ )
			DeathsBy[ i ] += stats->DeathsBy[ i ];

		return shared_from_this();
	}

	void PlayerStats::Clean()
	{
		/*unknown vec = GetType()->GetFields();
		for ( unknown::const_iterator info = vec.begin(); info != vec.end(); ++info )
		{
			if ( ( *info )->FieldType == int::typeid )
				( *info )->SetValue( shared_from_this(), 0 );
		}*/

		// FIXME: Check to make sure it does the same thing.
		Score = 0;
		Coins = 0;
		Blobs = 0;
		CoinsSpentAtShop = 0;

		TotalCoins = 0;
		TotalBlobs = 0;

		Levels = 0;
		Checkpoints = 0;
		Jumps = 0;
		Berries = 0;

		TimeAlive = 0;
		ObstaclesSeen = 0;

		FinalTimeSpentNotMoving = 0;
		FinalTimeSpent = 0;

		ObstaclesSeen = 0;

		for ( size_t i = 0; i < DeathsBy.size(); i++ )
			DeathsBy[ i ] = 0;
	}

	std::wstring PlayerStats::getLifeExpectancy() const
	{
		TimeSpan time = TimeSpan( 0, 0, getLifeExpectancy_Frames() / 60 );
		if ( time.Hours == 0 )
			return Format( _T( "%d:%02d" ), time.Minutes, time.Seconds );
		else
			return Format( _T( "%d:%02d:%02d" ), time.Hours, time.Minutes, time.Seconds );
	}

	int PlayerStats::getLifeExpectancy_Frames() const
	{
		if ( DeathsBy[ static_cast<int>( BobDeathType_TOTAL ) ] <= 0 )
			return TimeAlive;
		else
			return static_cast<int>( static_cast<float>( TimeAlive ) / static_cast<float>( 1 + DeathsBy[ static_cast<int>( BobDeathType_TOTAL ) ] ) );
	}

	int PlayerStats::getTotalDeaths() const
	{
		return DeathsBy[ static_cast<int>( BobDeathType_TOTAL ) ];
	}

	int PlayerStats::getCoinPercentGotten() const
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
