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
		if ( !seed.find( _T( ";" ) ) != string::npos )
			return false;
		if ( !seed.find( _T( ":" ) ) != string::npos )
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
		for ( CloudberryKingdom::Chunk::const_iterator chunk = ParentChunk->begin(); chunk != ParentChunk->end(); ++chunk )
		{
			switch ( ( *chunk )->Type )
			{
				case 0:
					SeedStrings.push_back( ( *chunk )->ReadString() );
					break;
			}
		}
	}

	void SavedSeeds::InitializeInstanceFields()
	{
		SeedStrings = std::vector<std::wstring>( 50 );
	}
}
