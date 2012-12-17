#include <global_header.h>


namespace CloudberryKingdom
{

	MakeFinalDoor_Float::MakeFinalDoor_Float( const boost::shared_ptr<Level> &level )
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
			boost::shared_ptr<BlockBase> block = FinalBlock = boost::static_pointer_cast<NormalBlock>( MyLevel->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );

			block->getBlockCore()->EndPiece = true;
			( boost::static_pointer_cast<NormalBlock>( FinalBlock ) )->Init( FinalPos + Vector2( -130, -600 ), Vector2( 400, 400 ), MyLevel->getMyTileSetInfo() );

			block->getCore()->DrawLayer = 0;
			block->getCore()->Real = false;
		}
		// Old style end blocks
		else
		{
			// Create a dummy block
			int width = 400;
			FinalBlock = boost::static_pointer_cast<NormalBlock>( MyLevel->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
			( boost::static_pointer_cast<NormalBlock>( FinalBlock ) )->Init( FinalPos + Vector2( 130, 0 ), Vector2( static_cast<float>( width ) ), MyLevel->getMyTileSetInfo() );
			FinalBlock->getCore()->setMyTileSet(MyLevel->MyTileSet);
		}
	}

	void MakeFinalDoor_Float::Phase3()
	{
		MakeThing::Phase3();

		boost::shared_ptr<Door> door;

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

		// Cleanup
		FinalBlock.reset();
	}

	void MakeFinalDoor_Float::AttachDoorAction( const boost::shared_ptr<ILevelConnector> &door )
	{
		if ( Tools::WorldMap != 0 )
		{
			boost::shared_ptr<StringWorldGameData> stringworld = boost::dynamic_pointer_cast<StringWorldGameData>( Tools::WorldMap );
			if ( stringworld != 0 )
			{
				door->setOnOpen( boost::make_shared<EOL_StringWorldDoorActionProxy>( stringworld ) );
				door->setOnEnter( boost::make_shared<EOL_StringWorldDoorEndActionProxy>( stringworld ) );
			}
		}
	}

	void MakeFinalDoor_Float::SetFinalDoor( const boost::shared_ptr<Door> &door, const boost::shared_ptr<Level> &level, Vector2 FinalPos )
	{
		door->getCore()->EditorCode1 = LevelConnector::EndOfLevelCode;

		// Attach an action to the door
		AttachDoorAction( door );

		// Mod CameraZone
		boost::shared_ptr<CameraZone> camzone = boost::static_pointer_cast<CameraZone>( Tools::Find<boost::shared_ptr<ObjectBase> >( level->Objects, FindCamZoneLambda::FindCamZoneLambda_Static ) );

		camzone->End.X = FinalPos.X - level->getMainCamera()->GetWidth() / 2 + 420;

		if ( level->getPieceSeed()->ZoomType == LevelZoom_BIG )
			camzone->End.X -= 150;
	}
}
