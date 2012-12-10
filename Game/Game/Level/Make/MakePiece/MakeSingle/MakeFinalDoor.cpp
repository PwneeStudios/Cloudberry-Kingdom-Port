#include <global_header.h>

namespace CloudberryKingdom
{

	MakeFinalDoor::VanillaFillEndPieceLambda::VanillaFillEndPieceLambda()
	{
	}

	void MakeFinalDoor::VanillaFillEndPieceLambda::Apply( const std::shared_ptr<BlockBase> &block )
	{
		block->getBlockCore()->EndPiece = true;
	}

	MakeFinalDoor::ModBlockLambda::ModBlockLambda( const std::shared_ptr<MakeFinalDoor> &mfd )
	{
		this->mfd = mfd;
	}

	void MakeFinalDoor::ModBlockLambda::Apply( const std::shared_ptr<BlockBase> &block )
	{
		mfd->ModBlock( block );
	}

	MakeFinalDoor::FindFinalBlockLambda::FindFinalBlockLambda()
	{
	}

	bool MakeFinalDoor::FindFinalBlockLambda::Apply( const std::shared_ptr<BlockBase> &block )
	{
		return block->getCore()->GenData.Used && block->getCore()->IsCalled( _T("FinalBlock") );
	}

	MakeFinalDoor::BoxTRyLambda::BoxTRyLambda()
	{
	}

	float MakeFinalDoor::BoxTRyLambda::Apply( const std::shared_ptr<BlockBase> &block )
	{
		return block->getBox()->TR.Y;
	}

	MakeFinalDoor::MakeFinalDoor( const std::shared_ptr<Level> &level )
	{
		InitializeInstanceFields();
		MyLevel = level;
	}

	void MakeFinalDoor::Phase1()
	{
		MakeThing::Phase1();

		MyLevel->EndBuffer = 1500;

		Vector2 BL;

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
			BL = Vector2( MyLevel->MaxRight + 450, MyLevel->getMainCamera()->BL.Y + Level::SafetyNetHeight );
		// Old style end blocks
		else
			BL = Vector2( MyLevel->MaxRight + 450, MyLevel->getMainCamera()->BL.Y + Level::SafetyNetHeight + 65 );

		float Spacing = 200;
		Vector2 TR = Vector2( MyLevel->MaxRight + 1000, MyLevel->getMainCamera()->TR.Y - 850 );

		float NewRight = MyLevel->VanillaFill( BL, TR, 400, Spacing, std::make_shared<VanillaFillEndPieceLambda>(), std::make_shared<ModBlockLambda>( shared_from_this() ) );

		// Make lowest block a safety (we'll place the door here if no other block is used)
		FinalBlocks[ 0 ]->getCore()->GenData.KeepIfUnused = true;
		FinalBlocks[ 0 ]->getBlockCore()->NonTopUsed = true;

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
		{
			MyLevel->LastSafetyBlock->Extend( Side_RIGHT, FinalBlocks[ 0 ]->getBox()->BL.X - 50 );
		}
		// Old style end blocks
		else
		{
			// Extend lowest block to match up with safety net (or extend safety net instead)
			if ( MyLevel->LastSafetyBlock != 0 && MyLevel->LastSafetyBlock->getBox()->TR.X + 50 < FinalBlocks[ 0 ]->getBox()->BL.X )
				FinalBlocks[ 0 ]->Extend( Side_LEFT, MyLevel->LastSafetyBlock->getBox()->TR.X + 50 );
			else
				MyLevel->LastSafetyBlock->Extend( Side_RIGHT, FinalBlocks[ 0 ]->getBox()->BL.X - 50 );
		}
	}

	void MakeFinalDoor::ModBlock( const std::shared_ptr<BlockBase> &block )
	{
		block->getBlockCore()->DisableFlexibleHeight = true;
		block->getBlockCore()->DeleteIfTopOnly = true;
		block->getBlockCore()->GenData.RemoveIfUnused = true;
		block->getBlockCore()->GenData.AlwaysUse = false;
		block->getCore()->EditorCode1 = _T("FinalBlock");
		FinalBlocks.push_back( block );

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
		{
			block->getBlockCore()->EndPiece = true;
			block->getCore()->DrawLayer = 0;
		}
	}

	void MakeFinalDoor::Phase2()
	{
		MakeThing::Phase2();

		BlockVec _FinalBlocks = Tools::FindAll<std::shared_ptr<BlockBase> >( MyLevel->Blocks, std::make_shared<FindFinalBlockLambda>() );
		FinalBlock = Tools::ArgMax<std::shared_ptr<BlockBase> >( _FinalBlocks, std::make_shared<BoxTRyLambda>() );

		// If none exist use the lowest block
		if ( FinalBlock == 0 )
		{
			FinalBlock = FinalBlocks[ 0 ];
			FinalBlock->StampAsUsed( 0 );
		}
		else
		{
			if ( FinalBlocks[ 0 ]->getCore()->GenData.KeepIfUnused && !FinalBlocks[ 0 ]->getCore()->GenData.Used )
				FinalBlocks[ 0 ]->CollectSelf();
		}

		FinalPos = Vector2( FinalBlock->getBox()->BL.X + 200, FinalBlock->getBox()->TR.Y );

		// Cut computer run short once the computer reaches the door.
		int Earliest = 100000;
		Vector2 pos = FinalPos;
		float Closest = -1;
		int NewLastStep = MyLevel->LastStep;
		for ( int i = 0; i < MyLevel->CurPiece->NumBobs; i++ )
			for ( int j = MyLevel->LastStep - 1; j > 0; j-- )
			{
				Vector2 BobPos = MyLevel->CurPiece->Recording_Renamed[ i ]->AutoLocs[ j ];
				float Dist = ( BobPos - FinalPos ).Length();

				if ( Closest == -1 || Dist < Closest )
				{
					Earliest = __min( Earliest, j );
					Closest = Dist;
					pos = BobPos;
					NewLastStep = j;
				}
			}

		MyLevel->LastStep = __min( Earliest, MyLevel->LastStep );
	}

	void MakeFinalDoor::Phase3()
	{
		MakeThing::Phase3();

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
		{
			FinalPos.X += 230;
		}

		// Add door
		std::shared_ptr<Door> door = MyLevel->PlaceDoorOnBlock( FinalPos, FinalBlock, MyLevel->MyTileSet->CustomStartEnd ? false : true );

		// New style end blocks
		if ( MyLevel->MyTileSet->FixedWidths )
		{
			door->Mirror = true;
		}

		SetFinalDoor( door, MyLevel, FinalPos );

		// Push lava down
		MyLevel->PushLava( FinalBlock->getBox()->Target->TR.Y - 60 );

		// Cleanup
		FinalBlocks.clear();
		FinalBlock.reset();
	}

	void MakeFinalDoor::AttachDoorAction( const std::shared_ptr<ILevelConnector> &door )
	{
		if ( Tools::WorldMap != 0 )
		{
			std::shared_ptr<StringWorldGameData> stringworld = std::dynamic_pointer_cast<StringWorldGameData>( Tools::WorldMap );
			if ( stringworld != 0 )
			{
				door->setOnOpen( std::make_shared<EOL_StringWorldDoorActionProxy>( stringworld ) );
				door->setOnEnter( std::make_shared<EOL_StringWorldDoorEndActionProxy>( stringworld ) );
			}
		}
	}

	void MakeFinalDoor::SetFinalDoor( const std::shared_ptr<Door> &door, const std::shared_ptr<Level> &level, Vector2 FinalPos )
	{
		door->getCore()->EditorCode1 = LevelConnector::EndOfLevelCode;

		// Attach an action to the door
		AttachDoorAction( door );

		// Mod CameraZone
		std::shared_ptr<CameraZone> camzone = std::static_pointer_cast<CameraZone>( Tools::Find<std::shared_ptr<ObjectBase> >( level->Objects, FindCamZoneLambda::FindCamZoneLambda_Static ) );

		camzone->End.X = FinalPos.X - level->getMainCamera()->GetWidth() / 2 + 500;

		if ( level->getPieceSeed()->ZoomType == LevelZoom_BIG )
			camzone->End.X -= 150;
	}

	void MakeFinalDoor::InitializeInstanceFields()
	{
		FinalBlocks = BlockVec();
	}

	void FindCamZoneLambda::InitializeStatics()
	{
		FindCamZoneLambda::FindCamZoneLambda_Static = std::make_shared<FindCamZoneLambda>();
	}

	// Statics
	std::shared_ptr<FindCamZoneLambda> FindCamZoneLambda::FindCamZoneLambda_Static;

	FindCamZoneLambda::FindCamZoneLambda()
	{
	}

	bool FindCamZoneLambda::Apply( const std::shared_ptr<ObjectBase> &obj )
	{
		return obj->getCore()->MyType == ObjectType_CAMERA_ZONE;
	}
}
