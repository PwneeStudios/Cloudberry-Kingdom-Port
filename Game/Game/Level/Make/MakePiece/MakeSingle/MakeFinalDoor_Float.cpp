#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	MakeFinalDoor_Float::MakeFinalDoor_Float( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;
	}

	void MakeFinalDoor_Float::Phase1()
	{
		MakeThing::Phase1();
	}

	void MakeFinalDoor_Float::Phase2()
	{
		MakeThing::Phase2();

		Vector2 Pos = Vector2( MyLevel->MaxRight + 90, MyLevel->getMainCamera()->BL.Y + Level::SafetyNetHeight + 65 );

		// Cut computer run short once the computer reaches the door.
		int NewLastStep = MyLevel->LastStep;
		float MinDist = 100000;
		for ( int j = 0; j < MyLevel->LastStep; j++ )
		{
			NewLastStep = j;
			for ( int i = 0; i < MyLevel->CurPiece->NumBobs; i++ )
			{
				Vector2 BobPos = MyLevel->CurPiece->Recording_Renamed[ i ]->AutoLocs[ j ];
				float Dist = abs( BobPos.X - Pos.X );

				if ( Dist < MinDist )
				{
					MinDist = Dist;
					FinalPos = BobPos;
				}
			}
		}

		MyLevel->LastStep = NewLastStep;

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
		{
			// Create the block
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			var block = FinalBlock = static_cast<NormalBlock*>( MyLevel->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );

			block->BlockCore->EndPiece = true;
			( static_cast<NormalBlock*>( FinalBlock ) )->Init( FinalPos + Vector2( -130, -600 ), Vector2( 400, 400 ), MyLevel->getMyTileSetInfo() );

			block->Core->DrawLayer = 0;
			block->Core->Real = false;
		}
		// Old style end blocks
		else
		{
			// Create a dummy block
			int width = 400;
			FinalBlock = static_cast<NormalBlock*>( MyLevel->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
			( static_cast<NormalBlock*>( FinalBlock ) )->Init( FinalPos + Vector2( 130, 0 ), Vector2( width ), MyLevel->getMyTileSetInfo() );
			FinalBlock->getCore()->setMyTileSet(MyLevel->MyTileSet);
		}
	}

	void MakeFinalDoor_Float::Phase3()
	{
		MakeThing::Phase3();

		std::shared_ptr<Door> door;

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
		{
			door = MyLevel->PlaceDoorOnBlock( FinalPos, FinalBlock, false );
			MyLevel->AddBlock( FinalBlock );
			FinalBlock->Active = false;
			door->Mirror = true;
		}
		// Old style end blocks
		else
		{
			// Add door
			door = MyLevel->PlaceDoorOnBlock_Unlayered( FinalPos, FinalBlock, true );
			Tools::MoveTo( door, FinalPos );
		}

		SetFinalDoor( door, MyLevel, FinalPos );

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
		{
		}

		// Push lava down
		MyLevel->PushLava( FinalBlock->getBox()->Target->TR.Y - 60 );

		// Add exit sign
		if ( MyLevel->getInfo()->Doors->ShowSign )
		{
			std::shared_ptr<Sign> sign = std::make_shared<Sign>( false, MyLevel );
			sign->PlaceAt( door->GetTop() );
			MyLevel->AddObject( sign );
		}

		// Cleanup
		FinalBlock.reset();
	}

	void MakeFinalDoor_Float::AttachDoorAction( const std::shared_ptr<ILevelConnector> &door )
	{
		if ( Tools::WorldMap != 0 )
		{
			std::shared_ptr<StringWorldGameData> stringworld = dynamic_cast<StringWorldGameData*>( Tools::WorldMap );
			if ( stringworld != 0 )
			{
				door->setOnOpen( std::make_shared<EOL_StringWorldDoorActionProxy>( stringworld ) );
				door->setOnEnter( std::make_shared<EOL_StringWorldDoorEndActionProxy>( stringworld ) );
			}
		}
	}

	void MakeFinalDoor_Float::SetFinalDoor( const std::shared_ptr<Door> &door, const std::shared_ptr<Level> &level, Vector2 FinalPos )
	{
		door->getCore()->EditorCode1 = LevelConnector::EndOfLevelCode;

		// Attach an action to the door
		AttachDoorAction( door );

		// Mod CameraZone
		std::shared_ptr<CameraZone> camzone = static_cast<CameraZone*>( Tools::Find( level->Objects, FindCamZoneLambda::FindCamZoneLambda_Static ) );

		camzone->End.X = FinalPos.X - level->getMainCamera()->GetWidth() / 2 + 420;

		if ( level->getPieceSeed()->ZoomType == LevelZoom_BIG )
			camzone->End.X -= 150;
	}
}
