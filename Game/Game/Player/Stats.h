#ifndef STATS
#define STATS

#include <string>
#include <tchar.h>

namespace CloudberryKingdom
{
	class Chunk;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;

namespace CloudberryKingdom
{
	enum StatGroup
	{
		StatGroup_LIFETIME,
		StatGroup_GAME,
		StatGroup_LEVEL,
		StatGroup_TEMP,
		StatGroup_CAMPAIGN
	};
	class PlayerStats
	{
		#pragma region WriteRead
	public:
		void WriteChunk_4( const std::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_4( const std::shared_ptr<Chunk> &ParentChunk );

	private:
		void WriteDeathChunk_9( const std::shared_ptr<Chunk> &ParentChunk, int Index );

		void ReadDeathChunk_9( const std::shared_ptr<Chunk> &chunk );
		#pragma endregion

		#pragma region Persistent Stats
	public:
		int Score, Coins, Blobs, CoinsSpentAtShop;
		int TotalCoins, TotalBlobs;

		int Levels, Checkpoints, Jumps, Berries;

		std::vector<int> DeathsBy;

		int TimeAlive;
		#pragma endregion

		// Add all fields and elements of arrays to the corresponding field in this instance.
		std::shared_ptr<PlayerStats> Absorb( const std::shared_ptr<PlayerStats> &stats );

		// Set all fields and all elements of arrays to 0.
		void Clean();

		/// <summary>
		/// Total time and time spent moving for the final attempt.
		/// </summary>
		int FinalTimeSpentNotMoving, FinalTimeSpent;

		#pragma region DerivedStats
		const std::wstring &getLifeExpectancy() const;

		const int &getLifeExpectancy_Frames() const;

		const int &getTotalDeaths() const;
		const int &getCoinPercentGotten() const;
		#pragma endregion

		PlayerStats();
	};
}


#endif	//#ifndef STATS
