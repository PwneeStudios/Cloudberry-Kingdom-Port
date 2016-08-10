#include <small_header.h>
#include "Game/Player/SavedSeeds.h"

#include "Core/Chunk.h"
#include "Game/Tools/EzStorage.h"
#include "Game/Player/Awardments/Awardment.h"


namespace CloudberryKingdom
{

	void SavedSeeds::SaveSeed( const std::wstring &seed, const std::wstring &name )
	{
		if ( IsSeedValue( seed ) )
		{
			Awardments::CheckForAward_Save();

			SeedStrings.push_back( seed + std::wstring( L"name:" ) + name + std::wstring( L";" ) );
			SaveGroup::SaveAll();
		}
	}

	bool SavedSeeds::IsSeedValue( const std::wstring &seed )
	{
		if ( seed.find( std::wstring( L";" ) ) == std::wstring::npos )
			return false;
		if ( seed.find( std::wstring( L":" ) ) == std::wstring::npos )
			return false;
		return true;
	}

	void SavedSeeds::WriteChunk_5( const boost::shared_ptr<BinaryWriter> &writer )
	{
		boost::shared_ptr<Chunk> chunk = boost::make_shared<Chunk>();
		chunk->Type = 5;

		for ( std::vector<std::wstring>::const_iterator seed = SeedStrings.begin(); seed != SeedStrings.end(); ++seed )
			chunk->WriteSingle( 0, *seed );

		chunk->Finish( writer );
	}

	void SavedSeeds::ReadChunk_5( const boost::shared_ptr<Chunk> &ParentChunk )
	{
		boost::shared_ptr<Chunks> chunks = Chunks::Get( ParentChunk );
		chunks->StartGettingChunks();

		while( chunks->HasChunk() )
		{
			boost::shared_ptr<Chunk> chunk = chunks->GetChunk();

			switch ( chunk->Type )
			{
				case 0:
					SeedStrings.push_back( chunk->ReadString() );
					break;
			}
		}
	}

	void SavedSeeds::InitializeInstanceFields()
	{
		SeedStrings = std::vector<std::wstring>();
		SeedStrings.reserve( 50 );
	}
}
