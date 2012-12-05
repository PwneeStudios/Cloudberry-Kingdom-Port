#include <global_header.h>

namespace CloudberryKingdom
{

	void SwarmRecord::Release()
	{
		MainRecord.reset();
		
		// Release all recordings in Records
		for ( std::vector<std::shared_ptr<Recording> >::const_iterator record = Records.begin(); record != Records.end(); ++record )
			( *record )->Release();

		Records.clear();
		//Clear( Records );
		MyLevelPiece.reset();
	}

	SwarmRecord::SwarmRecord()
	{
		InitializeInstanceFields();
		Records = std::vector<std::shared_ptr<Recording> >();

		BobQuad = std::make_shared<QuadClass>();
		BobQuad->Base.e1 *= 100;
		BobQuad->Base.e2 *= 100;
		BobQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		BobQuad->Quad_Renamed.setMyTexture( std::make_shared<EzTexture>() );
		BobQuad->Quad_Renamed.getMyTexture()->Name = _T( "BobQuad" );
	}

	void SwarmRecord::Draw( int Step, const std::shared_ptr<Level> &level, std::vector<std::shared_ptr<SpriteAnimGroup> > AnimGroup, std::vector<std::shared_ptr<BobLink> > &BobLinks )
	{
		if ( level->SingleOnly )
		{
			MainRecord->Draw( BobQuad, Step, level, AnimGroup, BobLinks );
		}
		else
		{
			for ( std::vector<std::shared_ptr<Recording> >::const_iterator record = Records.begin(); record != Records.end(); ++record )
				( *record )->Draw( BobQuad, Step, level, AnimGroup, BobLinks );
		}
	}

	void SwarmRecord::AddRecord( const std::shared_ptr<Recording> &Record, int Step )
	{
		MainRecord = Record;

		if ( static_cast<int>( Records.size() ) >= MaxRecords )
		{
			/*std::shared_ptr<Recording> DevectordRecord = Records.pop();*/
			std::shared_ptr<Recording> DevectordRecord = PopBack( Records );
			DevectordRecord->Release();
		}

		for ( std::vector<std::shared_ptr<Recording> >::const_iterator record = Records.begin(); record != Records.end(); ++record )
			if ( *record != MainRecord )
				( *record )->ConvertToSuperSparse();

		Records.push_back( Record );
	}

	void SwarmRecord::InitializeInstanceFields()
	{
#if defined(XBOX)
		MaxRecords = 200 / __max( 1, PlayerManager::GetNumPlayers() );
#endif
#if ! defined(XBOX)
		MaxRecords = 500 / __max( 1, PlayerManager::GetNumPlayers() );
#endif
	}
}
