#ifndef SAVEDSEEDS
#define SAVEDSEEDS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Chunk;
}

namespace CloudberryKingdom
{
	struct SavedSeeds
	{
	
		std::vector<std::wstring> SeedStrings;

		void SaveSeed( const std::wstring &seed, const std::wstring &name );

		/// <summary>
		/// A rough heuristic fo determining if a string is a seed.
		/// Heuristic has no false negatives, but many false positives.
		/// </summary>
		/// <param name="seed">The string to check.</param>
		/// <returns>Whether the string is a seed (heuristically).</returns>
		bool IsSeedValue( const std::wstring &seed );

		#pragma region WriteRead
		void WriteChunk_5( const boost::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_5( const boost::shared_ptr<Chunk> &ParentChunk );
		#pragma endregion

	
		void InitializeInstanceFields();


		SavedSeeds()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef SAVEDSEEDS
