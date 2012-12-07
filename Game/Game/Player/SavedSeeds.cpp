#include <global_header.h>

namespace CloudberryKingdom
{

	void SavedSeeds::SaveSeed( const std::wstring &seed, const std::wstring &name )
	{
		if ( IsSeedValue( seed ) )
		{
			SeedStrings.push_back( seed + _T( "name:" ) + name + _T( ";" ) );
			SaveGroup::SaveAll();
		}
	}

	bool SavedSeeds::IsSeedValue( const std::wstring &seed )
	{
		if ( seed.find( _T( ";" ) ) == std::wstring::npos )
			return false;
		if ( seed.find( _T( ":" ) ) == std::wstring::npos )
			return false;
		return true;
	}

	void SavedSeeds::WriteChunk_5( const std::shared_ptr<BinaryWriter> &writer )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = 5;

		for ( std::vector<std::wstring>::const_iterator seed = SeedStrings.begin(); seed != SeedStrings.end(); ++seed )
			chunk->WriteSingle( 0, *seed );

		chunk->Finish( writer );
	}

	void SavedSeeds::ReadChunk_5( const std::shared_ptr<Chunk> &ParentChunk )
	{
		std::shared_ptr<Chunks> chunks = Chunks::Get( ParentChunk );
		chunks->StartGettingChunks();

		while( chunks->HasChunk() )
		{
			std::shared_ptr<Chunk> chunk = chunks->GetChunk();

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
		SeedStrings = std::vector<std::wstring>( 50 );
	}
}
