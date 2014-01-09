#include <small_header.h>
#include "Game/Level/Replays/SwarmRecord.h"

#include "Core/Animation/SpriteAnim.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Level/LevelPiece.h"
#include "Game/Level/Replays/Recording.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Objects/Bob/BobLink.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	void SwarmRecord::Release()
	{
		MainRecord.reset();
		
		// Release all recordings in Records
		for ( std::list<boost::shared_ptr<Recording> >::const_iterator record = Records.begin(); record != Records.end(); ++record )
			( *record )->Release();

		Records.clear();
		//Clear( Records );
		MyLevelPiece.reset();
	}

	SwarmRecord::SwarmRecord()
	{
		InitializeInstanceFields();
		Records = std::list<boost::shared_ptr<Recording> >();

		BobQuad = boost::make_shared<QuadClass>();
		BobQuad->Base.e1 *= 100;
		BobQuad->Base.e2 *= 100;
		BobQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		BobQuad->Quad_Renamed.setMyTexture( boost::make_shared<EzTexture>() );
		BobQuad->Quad_Renamed.getMyTexture()->Name = std::wstring( L"BobQuad" );
	}

	void SwarmRecord::Draw( int Step, const boost::shared_ptr<Level> &level, std::vector<boost::shared_ptr<SpriteAnimGroup> > AnimGroup, std::vector<boost::shared_ptr<BobLink> > &BobLinks )
	{
		if ( level->SingleOnly )
		{
			MainRecord->Draw( BobQuad, Step, level, AnimGroup, BobLinks );
		}
		else
		{
			for ( std::list<boost::shared_ptr<Recording> >::const_iterator record = Records.begin(); record != Records.end(); ++record )
				( *record )->Draw( BobQuad, Step, level, AnimGroup, BobLinks );
		}
	}

	void SwarmRecord::AddRecord( const boost::shared_ptr<Recording> &Record, int Step )
	{
		MainRecord = Record;

		if ( static_cast<int>( Records.size() ) >= MaxRecords )
		{
			/*boost::shared_ptr<Recording> DevectordRecord = Records.pop();*/
			boost::shared_ptr<Recording> DevectordRecord = Records.front();
			Records.pop_front();
			DevectordRecord->Release();
		}

		//for ( std::list<boost::shared_ptr<Recording> >::const_iterator record = Records.begin(); record != Records.end(); ++record )
		//	if ( *record != MainRecord )
		//		( *record )->ConvertToSuperSparse( Step );

		Records.push_back( Record );
	}

	void SwarmRecord::InitializeInstanceFields()
	{
#ifdef PC_VERSION
		Tools::Warning(); // Should be 500, but we are using 50 to test memory usage for consoles.
		MaxRecords = 50 / __max( 1, PlayerManager::GetNumPlayers() );
		//MaxRecords = 500 / __max( 1, PlayerManager::GetNumPlayers() );
#else
		MaxRecords = 50 / __max( 1, PlayerManager::GetNumPlayers() );
#endif
	}
}
