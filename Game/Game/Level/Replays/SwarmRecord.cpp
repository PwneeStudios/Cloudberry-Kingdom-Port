#include "SwarmRecord.h"
#include "Game/Level/LevelPiece.h"
#include "Game/Level/Replays/Recording.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Tools/Tools.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Objects/Bob/BobLink.h"
#include "Core/Animation/SpriteAnim.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	void SwarmRecord::Release()
	{
		MainRecord.reset();
		for ( std::queue<Recording*>::const_iterator record = Records.begin(); record != Records.end(); ++record )
			( *record )->Release();
		Records.clear();
		MyLevelPiece.reset();
	}

	SwarmRecord::SwarmRecord()
	{
		InitializeInstanceFields();
		Records = std::queue<Recording*>();

		BobQuad = std::make_shared<QuadClass>();
		BobQuad->Base.e1 *= 100;
		BobQuad->Base.e2 *= 100;
		BobQuad->Quad_Renamed->MyEffect = Tools::BasicEffect;
		BobQuad->Quad_Renamed->MyTexture = std::make_shared<EzTexture>();
		BobQuad->Quad_Renamed->MyTexture->Name = _T( "BobQuad" );
	}

	void SwarmRecord::Draw( int Step, const std::shared_ptr<Level> &level, std::vector<SpriteAnimGroup*> AnimGroup, std::vector<BobLink*> &BobLinks )
	{
		if ( level->SingleOnly )
		{
			MainRecord->Draw( BobQuad, Step, level, AnimGroup, BobLinks );
		}
		else
		{
			for ( std::queue<Recording*>::const_iterator record = Records.begin(); record != Records.end(); ++record )
				( *record )->Draw( BobQuad, Step, level, AnimGroup, BobLinks );
		}
	}

	void SwarmRecord::AddRecord( const std::shared_ptr<Recording> &Record, int Step )
	{
		MainRecord = Record;

		if ( Records.size() >= MaxRecords )
		{
			std::shared_ptr<Recording> DequeuedRecord = Records.pop();
			DequeuedRecord->Release();
		}

		for ( std::queue<Recording*>::const_iterator record = Records.begin(); record != Records.end(); ++record )
			if ( *record != MainRecord )
				( *record )->ConvertToSuperSparse();

		Records.push( Record );
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
