#ifndef SAVEDSEEDS
#define SAVEDSEEDS

#include <global_header.h>

namespace CloudberryKingdom
{
	class Chunk;
}

namespace CloudberryKingdom
{
	class SavedSeeds
	{
	public:
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
		void WriteChunk_5( const std::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_5( const std::shared_ptr<Chunk> &ParentChunk );
		#pragma endregion

	private:
		void InitializeInstanceFields();

public:
		SavedSeeds()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef SAVEDSEEDS
