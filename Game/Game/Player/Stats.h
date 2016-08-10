#ifndef STATS
#define STATS

#include <small_header.h>

//#include "Core/Chunk.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct Chunk;
}


namespace CloudberryKingdom
{
	struct PlayerStats : public boost::enable_shared_from_this<PlayerStats>
	{
		#pragma region WriteRead
	
		void WriteChunk_4( const boost::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_4( const boost::shared_ptr<Chunk> &ParentChunk );

	
		void WriteDeathChunk_9( const boost::shared_ptr<Chunk> &ParentChunk, int Index );

		void ReadDeathChunk_9( const boost::shared_ptr<Chunk> &chunk );
		#pragma endregion

		#pragma region Persistent Stats
	
		int Score, Coins, Blobs, CoinsSpentAtShop;
		int TotalCoins, TotalBlobs;

		int Levels, Checkpoints, Jumps, Berries;

		std::vector<int> DeathsBy;

		int TimeAlive;
		int ObstaclesSeen;
		#pragma endregion

		// Add all fields and elements of arrays to the corresponding field in this instance.
		boost::shared_ptr<PlayerStats> Absorb( const boost::shared_ptr<PlayerStats> &stats );

		// Set all fields and all elements of arrays to 0.
		void Clean();

		/// <summary>
		/// Total time and time spent moving for the final attempt.
		/// </summary>
		int FinalTimeSpentNotMoving, FinalTimeSpent;

		#pragma region DerivedStats
		std::wstring getLifeExpectancy() const;

		int getLifeExpectancy_Frames() const;

		int getTotalDeaths() const;
		int getCoinPercentGotten() const;
		#pragma endregion

		PlayerStats();
	};
}


#endif	//#ifndef STATS
