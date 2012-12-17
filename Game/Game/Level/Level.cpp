#include <global_header.h>

#include "Hacks/Queue.h"
#include "Hacks/List.h"
#include "Hacks/Compare.h"
#include "Hacks/String.h"

#include "Hacks/NET/Path.h"
#include "Hacks/NET/Directory.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{
	Level::ElementDistanceSquared::ElementDistanceSquared( Vector2 pos )
	{
		this->pos = pos;
	}

	float Level::ElementDistanceSquared::Apply( const boost::shared_ptr<BlockBase> &element )
	{
		return ( element->getCore()->Data.Position - pos ).LengthSquared();
	}

	Level::FindFirstRowLambda::FindFirstRowLambda()
	{
	}

	bool Level::FindFirstRowLambda::Apply( const boost::shared_ptr<BlockBase> &match )
	{
		return match->getCore()->IsCalled( _T( "FirstRow" ) );
	}

	Level::MakeVerticalCleanupHelper::MakeVerticalCleanupHelper( const boost::shared_ptr<Level> &level )
	{
		this->level = level;
	}

	Vector2 Level::MakeVerticalCleanupHelper::Apply( const Vector2 &pos )
	{
		float dist = static_cast<float>( level->CurMakeData->GenData->Get( DifficultyParam_GENERAL_MIN_DIST, pos ) );
		return Vector2( dist, dist );
	}

	Level::FindLimitGeneralDensityLambda::FindLimitGeneralDensityLambda()
	{
	}

	bool Level::FindLimitGeneralDensityLambda::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		return obj->getCore()->GenData.LimitGeneralDensity;
	}

	Level::EndReachedLambda::EndReachedLambda( const boost::shared_ptr<Level> &level )
	{
		this->level = level;
	}

	void Level::EndReachedLambda::Apply()
	{
		level->EndReached = true;
	}

	Level::SafetyNetLambda::SafetyNetLambda( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, Vector2 size, float xstep, StyleData::GroundType Type, bool Virgin, bool Used, bool BoxesOnly, bool InvertDraw, bool Invert )
	{
		InitializeInstanceFields();
		this->level = level;
		this->BL = BL;
		this->TR = TR;
		this->size = size;
		this->xstep = xstep;
		this->Type = Type;
		this->Virgin = Virgin;
		this->Used = Used;
		this->BoxesOnly = BoxesOnly;
		this->InvertDraw = InvertDraw;
		this->Invert = Invert;
	}

	void Level::SafetyNetLambda::Apply( const Vector2 &pos )
	{
		if ( Type == StyleData::GroundType_SAFETY_NET )
		{
			// Don't make an extra block at the end to fill out the fill
			if ( pos.X == TR.X )
				return;
		}

		boost::shared_ptr<NormalBlock> block;

		block = boost::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
		block->getCore()->AlwaysBoxesOnly = BoxesOnly;
		block->Init( pos + Vector2( 0, -size.Y ), size, level->getMyTileSetInfo() );
		block->getCore()->GenData.RemoveIfUnused = true;
		block->getBlockCore()->BlobsOnTop = true;
		//block.Core.GenData.AlwaysLandOn = true;
		block->getCore()->GenData.AlwaysUse = true;
		block->getBlockCore()->NonTopUsed = true;
		block->Invert = Invert;
		block->getBlockCore()->Virgin = Virgin;
		block->getBlockCore()->GenData.Used = Used;
		block->getBlockCore()->MyOrientation = InvertDraw ? PieceQuad::Orientation_UPSIDE_DOWN : PieceQuad::Orientation_NORMAL;

		level->AddBlock( block );

		level->__LastBlock = block;
	}

	void Level::SafetyNetLambda::InitializeInstanceFields()
	{
		Virgin = false;
		Used = false;
		BoxesOnly = false;
		InvertDraw = false;
		Invert = false;
	}

	Level::MakeInitialLambda::MakeInitialLambda( const boost::shared_ptr<Level> &level, Vector2 size )
	{
		this->level = level;
		this->size = size;
	}

	void Level::MakeInitialLambda::Apply( const Vector2 &pos )
	{
		level->__block_fromlambda = boost::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
		level->__block_fromlambda->Init( pos + Vector2( 0, -size.Y ), size, level->getMyTileSetInfo() );
		level->__block_fromlambda->getCore()->GenData.RemoveIfUnused = true;
		level->__block_fromlambda->getBlockCore()->BlobsOnTop = false;
		level->__block_fromlambda->getCore()->GenData.AlwaysLandOn = true;
		level->AddBlock( level->__block_fromlambda );
	}

	Level::Stage1RndFillLambda::Stage1RndFillLambda( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, Vector2 BL_Cutoff )
	{
		this->level = level;
		this->BL = BL;
		this->TR = TR;
		this->BL_Cutoff = BL_Cutoff;
	}

	void Level::Stage1RndFillLambda::Apply( const Vector2 &pos )
	{
		boost::shared_ptr<NormalBlock_Parameters> NParams = boost::static_pointer_cast<NormalBlock_Parameters>( level->getStyle()->FindParams( NormalBlock_AutoGen::getInstance() ) );
		std::vector<float> Weights = std::vector<float>( Generators::WeightedPreFill_1_Gens.size() );

		float MaxWeight = 0;

		// Find the relative weights of all the obstacles we wish to fill with 
		for ( int i = 0; i < static_cast<int>( Generators::WeightedPreFill_1_Gens.size() ); i++ )
		{
			boost::shared_ptr<AutoGen> gen = Generators::WeightedPreFill_1_Gens[ i ];

			if ( gen != NormalBlock_AutoGen::getInstance() )
			{
				float weight = level->getStyle()->FindParams( gen )->FillWeight.GetVal( pos );

				Weights[ i ] = weight;
				MaxWeight = __max( MaxWeight, weight );
			}
		}

		float NormalBlockTotal = __max( 0, 3 - MaxWeight / 3 );

		Weights[ IndexOf<boost::shared_ptr<AutoGen> >( Generators::WeightedPreFill_1_Gens, NormalBlock_AutoGen::getInstance() ) ] = NParams->CustomWeight ? NParams->FillWeight.GetVal(pos) : NormalBlockTotal * level->getStyle()->ModNormalBlockWeight;


		// Choose a random generator and make a new obstacle with it
		int choice = level->getRnd()->Choose(Weights);
		boost::shared_ptr<AutoGen> chosen_gen = Generators::WeightedPreFill_1_Gens[ choice ];
		boost::shared_ptr<ObjectBase> NewObj = chosen_gen->CreateAt( level, pos, BL_Cutoff, TR );

		if ( NewObj == 0 )
			return;

		// Keep new object if it's unused?
		if ( level->getRnd()->RndFloat(0, 1) < level->CurMakeData->PieceSeed->Style->ChanceToKeepUnused && pos.Y > BL.Y + 400 ) // Don't keep unused blocks that are too low
		{
			NewObj->getCore()->GenData.RemoveIfUnused = false;
			NewObj->getCore()->GenData.RemoveIfOverlap = true;
		}

		CheckToSleep();
	}

	Level::GeneralMinDistLambda::GeneralMinDistLambda( const boost::shared_ptr<Level> &level )
	{
		this->level = level;
	}

	Vector2 Level::GeneralMinDistLambda::Apply( const Vector2 &pos )
	{
		float dist = static_cast<float>( level->CurMakeData->GenData->Get( DifficultyParam_GENERAL_MIN_DIST, pos ) );
		return Vector2( dist, dist );
	}

	Level::CloseToStartLambda::CloseToStartLambda()
	{
	}

	bool Level::CloseToStartLambda::Apply( const boost::shared_ptr<Bob> &bob )
	{
		return ( bob->getCore()->Data.Position - bob->getCore()->StartData.Position ).Length() < 500 && !bob->Dead;
	}

	Level::IsLavaLambda::IsLavaLambda()
	{
	}

	bool Level::IsLavaLambda::Apply( const boost::shared_ptr<BlockBase> &block )
	{
		return boost::dynamic_pointer_cast<LavaBlock>( block ) != 0;
	}

	Level::FindGuidLambda::FindGuidLambda( unsigned long long guid )
	{
		this->guid = guid;
	}

	bool Level::FindGuidLambda::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		return obj->getCore()->MyGuid == guid;
	}

	Level::CleanObjectListLambda::CleanObjectListLambda()
	{
	}

	bool Level::CleanObjectListLambda::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		return obj->getCore()->MarkedForDeletion;
	}

	Level::CleanDrawLayerLambda::CleanDrawLayerLambda( int layer )
	{
		this->layer = layer;
	}

	bool Level::CleanDrawLayerLambda::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		return obj->getCore()->MarkedForDeletion || (obj->getCore()->DrawLayer != layer && obj->getCore()->DrawLayer2 != layer && obj->getCore()->DrawLayer3 != layer);
	}

	Level::CleanBlockListLambda::CleanBlockListLambda()
	{
	}

	bool Level::CleanBlockListLambda::Apply( const boost::shared_ptr<BlockBase> &obj )
	{
		return obj->getCore()->MarkedForDeletion;
	}

	Level::RemoveForeignLambda::RemoveForeignLambda( const boost::shared_ptr<Level> &level )
	{
		this->level = level;
	}

	bool Level::RemoveForeignLambda::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		return obj->getCore()->MyLevel != level;
	}

	Level::RemoveForeignBlockLambda::RemoveForeignBlockLambda( const boost::shared_ptr<Level> &level )
	{
		this->level = level;
	}

	bool Level::RemoveForeignBlockLambda::Apply( const boost::shared_ptr<BlockBase> &obj )
	{
		return obj->getCore()->MyLevel != level;
	}

	Level::BaseMetric::BaseMetric()
	{
	}

	Vector2 Level::BaseMetric::Apply( const boost::shared_ptr<ObjectBase> &A, const boost::shared_ptr<ObjectBase> &B )
	{
		return Vector2( abs( A->getCore()->Data.Position.X - B->getCore()->Data.Position.X ), abs(A->getCore()->Data.Position.Y - B->getCore()->Data.Position.Y) );
	}

	Level::ConstLambda::ConstLambda( Vector2 c )
	{
		this->c = c;
	}

	Vector2 Level::ConstLambda::Apply( const Vector2 &pos )
	{
		return c;
	}

	Level::SetBackLambda::SetBackLambda( const boost::shared_ptr<Level> &level, int Steps )
	{
		this->level = level;
		this->Steps = Steps;
	}

	void Level::SetBackLambda::Apply()
	{
		level->CurPiece->StartPhsxStep += Steps;
	}

	Level::CleanupCoinsHelper::CleanupCoinsHelper( const boost::shared_ptr<Coin_Parameters> &Params )
	{
		this->Params = Params;
	}

	Vector2 Level::CleanupCoinsHelper::Apply( const Vector2 &pos )
	{
		float dist = Params->MinDist.GetVal( pos );
		return Vector2( dist, dist );
	}

	void Level::CleanupCoins( Vector2 BL, Vector2 TR )
	{
		// Get Coin parameters
		boost::shared_ptr<Coin_Parameters> Params = boost::static_pointer_cast<Coin_Parameters>( getStyle()->FindParams( Coin_AutoGen::getInstance() ) );

		if ( !Params->DoCleanup )
			return;

		// No coins near final doors
		if ( getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
		{
			for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
				if ( boost::dynamic_pointer_cast<Coin>( *obj ) != 0 && ( *obj )->getPos().X > TR.X + 160 )
					getRecycle()->CollectObject(*obj);
		}
		else if ( getPieceSeed()->GeometryType == LevelGeometry_UP )
		{
			for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
				if ( boost::dynamic_pointer_cast<Coin>( *obj ) != 0 && ( *obj )->getPos().Y > TR.Y - 280 )
					getRecycle()->CollectObject(*obj);
		}

		// General cleanup
		Cleanup( ObjectType_COIN, boost::make_shared<CleanupCoinsHelper>( Params ), BL + Params->BL_Bound_Mod, TR + Params->TR_Bound_Mod );
	}

	boost::shared_ptr<CameraZone> Level::MakeVerticalCameraZone( LevelGeometry Geometry, float Height )
	{
		Vector2 Size = CoreMath::Abs( CurMakeData->PieceSeed->End - CurMakeData->PieceSeed->Start ) / 2;
		Size.Y += 900;
		Size = Vector2::Max( Size, getMainCamera()->GetSize() );

		boost::shared_ptr<CameraZone> CamZone = boost::static_pointer_cast<CameraZone>( MySourceGame->Recycle->GetObject( ObjectType_CAMERA_ZONE, false ) );
		CamZone->Init( ( CurMakeData->PieceSeed->Start + CurMakeData->PieceSeed->End ) / 2, Size );
		CamZone->Start = CurMakeData->PieceSeed->Start;
		//CamZone.End = CurMakeData.PieceSeed.End;
		if ( Geometry == LevelGeometry_UP )
		{
			CamZone->End = CamZone->Start + Vector2( 0, Height );
			CamZone->CameraType = Camera_PhsxType_SIDE_LEVEL_UP;
		}
		else if ( Geometry == LevelGeometry_DOWN )
		{
			CamZone->End = CamZone->Start - Vector2( 0, Height );
			CamZone->CameraType = Camera_PhsxType_SIDE_LEVEL_DOWN;

			CamZone->Start.Y += 125;
		}
		Vector2 Tangent = CamZone->End - CamZone->Start;

		//if (CurMakeData.InitialCamZone)
		//  CamZone.Start.Y += MainCamera.GetHeight() / 2 - 300;

		AddObject( CamZone );

		return CamZone;
	}

	float Level::MakeVerticalInitialPlats( const boost::shared_ptr<StyleData> &Style )
	{
		Vector2 size = Vector2( 350, 2250 );
		Vector2 pos = CurPiece->StartData[ 0 ].Position + Vector2( 0, 200 );
		boost::shared_ptr<NormalBlock> block = 0, startblock = 0;

		// Find the closest block to pos on first row
		startblock = boost::static_pointer_cast<NormalBlock>( Tools::ArgMin<boost::shared_ptr<BlockBase> >( Tools::FindAll<boost::shared_ptr<BlockBase> >( Blocks, boost::make_shared<FindFirstRowLambda>() ), boost::make_shared<ElementDistanceSquared>(pos) ) );

		boost::shared_ptr<Door> door = 0;
		switch ( Style->MyInitialPlatsType )
		{
			case StyleData::InitialPlatsType_UP_TILED_FLOOR:
			case StyleData::InitialPlatsType_DOOR:
				block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, false) );

				// Tiled bottom
				if ( Style->MyInitialPlatsType == StyleData::InitialPlatsType_UP_TILED_FLOOR )
				{
					for ( BlockVec::const_iterator _block = Blocks.begin(); _block != Blocks.end(); ++_block )
						if ( ( *_block )->getCore()->IsCalled( _T("FirstRow")  ))
							( *_block )->CollectSelf();

					FinalCamZone->End.Y += 400;
					FinalCamZone->Start.Y -= 100;

					block->getCore()->DrawLayer = 2;
					block->Init( startblock->getPos(), Vector2(1), getMyTileSetInfo() );
					block->Stretch( Side_RIGHT, 2000 );
					block->Stretch( Side_LEFT, -2000 );
					block->Stretch( Side_BOTTOM, -800 );
					block->Extend( Side_TOP, startblock->getBox()->Current->TR.Y + 1 );
					block->getCore()->EditorCode1 = _T("Tiled bottom");
				}
				else
					block->Clone( startblock );

				block->getBlockCore()->BlobsOnTop = false;
				block->StampAsUsed( 0 );
				block->getCore()->GenData.RemoveIfUnused = false;

				AddBlock( block );

				door = PlaceDoorOnBlock( pos, block, false );
				door->getCore()->EditorCode1 = LevelConnector::StartOfLevelCode;

				Level::SpreadStartPositions( CurPiece, CurMakeData, door->getCore()->Data.Position, Vector2(50, 0) );

				// Make sure block is used
				block->StampAsUsed( 0 );

				return 0;

			default:
				return 0;
		}
	}

	bool Level::MakeVertical( int Length, float Height, int StartPhsxStep, int ReturnEarly, const boost::shared_ptr<MakeData> &makeData )
	{
		CurMakeData = makeData;
		InitMakeData( CurMakeData );
		getStyle()->ModNormalBlockWeight = .15f;

		boost::shared_ptr<VerticalData> VStyle = boost::static_pointer_cast<VerticalData>( CurMakeData->PieceSeed->Style );
		LevelGeometry Geometry = CurMakeData->PieceSeed->GeometryType;

		// Shift start position up for down levels
		if ( Geometry == LevelGeometry_DOWN )
		{
			CurMakeData->PieceSeed->Start.Y += Height;
			CurMakeData->PieceSeed->End.Y += Height;
			CurMakeData->CamStartPos = CurMakeData->PieceSeed->Start;
		}
		else
		{
			CurMakeData->PieceSeed->Start.Y += Height;
			CurMakeData->PieceSeed->End.Y += Height;
			CurMakeData->CamStartPos = CurMakeData->PieceSeed->Start;
		}

		// Calculate the style parameters
		CurMakeData->PieceSeed->Style->CalcGenParams( CurMakeData->PieceSeed, shared_from_this() );

		// Move camera
		getMainCamera()->Data.Position = CurMakeData->CamStartPos;
		getMainCamera()->Update();

		// New bobs
		BobVec Computers = CurMakeData->MakeBobs( shared_from_this() );

		// New level piece
		boost::shared_ptr<LevelPiece> Piece = CurPiece = CurMakeData->MakeLevelPiece( shared_from_this(), Computers, Length, StartPhsxStep );

		// Start data
		Vector2 StartPos = getMainCamera()->getPos() + Vector2(0, -400);
		if ( Geometry == LevelGeometry_DOWN )
			StartPos.Y += 1200;
		for ( int i = 0; i < static_cast<int>( Piece->StartData.size() ); i++ )
			Piece->StartData[ i ].Position = StartPos;

		// Camera Zone
		boost::shared_ptr<CameraZone> CamZone = MakeVerticalCameraZone( Geometry, Height );
		FinalCamZone = CamZone;
		Sleep();

		// Set the camera start position
		if ( CurMakeData->InitialCamZone )
			CurPiece->CamStartPos = CurMakeData->CamStartPos = CamZone->Start;
		else
			CurPiece->CamStartPos = CurMakeData->CamStartPos;


		Vector2 BL_Bound, TR_Bound;

		if ( Geometry == LevelGeometry_UP )
		{
			BL_Bound = getMainCamera()->BL;
			TR_Bound = Vector2( getMainCamera()->TR.X, getMainCamera()->TR.Y + Height );
		}
		else
		{
			BL_Bound = Vector2( getMainCamera()->BL.X, getMainCamera()->BL.Y - Height );
			TR_Bound = getMainCamera()->TR;
			//BL_Bound.Y += 100;
		}

		FillBL = BL_Bound;

		// Safety nets
		Vector2 Size, Step;
		Size = Vector2( 100, 50 );
		Step = Vector2( 300, 390 );

		std::wstring BottomRowTag = _T( "" ), TopRowTag = _T( "" );
		if ( Geometry == LevelGeometry_UP )
		{
			BottomRowTag = _T( "FirstRow" );
			TopRowTag = _T( "LastRow" );
		}
		else if ( Geometry == LevelGeometry_DOWN )
		{
			BottomRowTag = _T( "LastRow" );
			TopRowTag = _T( "FirstRow" );
		}

		// Vary the spacing depending on how high the hero can jump
		float StepMultiplier = SetStepMultiplier( Size, Step );

		BL_Bound.Y += 200;
		TR_Bound.Y -= 200;
		Vector2 _pos = BL_Bound;
		// Make sure the net is centered
		_pos.X = getMainCamera()->Data.Position.X - Step.X * static_cast<int>(.5f * (TR_Bound.X - BL_Bound.X) / Step.X);
		for ( ; _pos.X < TR_Bound.X + 400; _pos.X += Step.X )
		{
			bool ShouldBreak = false;
			for ( _pos.Y = BL_Bound.Y; ; )
			{
				boost::shared_ptr<NormalBlock> block = boost::static_pointer_cast<NormalBlock>( NormalBlock_AutoGen::getInstance()->CreateAt( shared_from_this(), _pos) );

				block->Init( _pos, Size, getMyTileSetInfo() );
				block->MakeTopOnly();

				// Door catwalks need to be moved forward
				if ( _pos.Y == BL_Bound.Y || _pos.Y + Step.Y >= TR_Bound.Y )
					block->getBlockCore()->DrawLayer = 4;

				bool IsBottom = _pos.Y == BL_Bound.Y;
				bool IsTop = ShouldBreak;

				if ( Geometry == LevelGeometry_UP || Geometry == LevelGeometry_DOWN && IsBottom )
				{
					block->getCore()->GenData.DeleteSurroundingOnUse = false;
					block->getCore()->GenData.AlwaysLandOn = true;
				}

				if ( IsBottom )
					block->getCore()->EditorCode1 = BottomRowTag;
				if ( IsTop )
					block->getCore()->EditorCode1 = TopRowTag;
				if ( IsTop && Geometry == LevelGeometry_UP )
				{
					block->getBlockCore()->Virgin = true;
					block->getBlockCore()->BlobsOnTop = false;
				}

				// Increment y
				_pos.Y += Step.Y * StepMultiplier;
				if ( ShouldBreak )
					break;
				float Top = TR_Bound.Y - 300;
				if ( _pos.Y > Top )
				{
					_pos.Y = Top;
					ShouldBreak = true;
				}
			}
		}

		// Set flag when a block on the last row is used.
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			if ( ( *block )->getCore()->IsCalled( _T("LastRow") ) )
				( *block )->getCore()->GenData.OnUsed = boost::make_shared<EndReachedLambda>( shared_from_this() );

		// Initial platform
		if ( CurMakeData->InitialPlats && VStyle->MakeInitialPlats )
		{
			MakeVerticalInitialPlats( VStyle );
			Sleep();
		}

		// Final platform
		boost::shared_ptr<MakeThing> MakeFinalPlat = 0;
		if ( CurMakeData->FinalPlats )
		{
			if ( VStyle->MyFinalPlatsType == StyleData::FinalPlatsType_DOOR )
				MakeFinalPlat = boost::make_shared<MakeFinalDoorVertical>( shared_from_this() );
			if ( VStyle->MyFinalPlatsType == StyleData::FinalPlatsType_DARK_BOTTOM )
				MakeFinalPlat = boost::make_shared<MakeDarkBottom>( shared_from_this() );
		}

		if ( MakeFinalPlat != 0 )
			MakeFinalPlat->Phase1();


		// Pre Fill #1
		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::PreFill_1_Gens.begin(); gen != Generators::PreFill_1_Gens.end(); ++gen )
		{
			( *gen )->PreFill_1( shared_from_this(), BL_Bound, TR_Bound );
			Sleep();
		}

		// Change sparsity multiplier
		if ( CurMakeData->SparsityMultiplier == 1 )
			CurMakeData->SparsityMultiplier = static_cast<float>( CurMakeData->GenData->Get( DifficultyParam_FILL_SPARSITY ) / 100 );


		// Stage 1 fill
		boost::shared_ptr<NormalBlock_Parameters> BlockParams = boost::static_pointer_cast<NormalBlock_Parameters>( VStyle->FindParams( NormalBlock_AutoGen::getInstance() ) );
		if ( BlockParams->DoStage1Fill )
		{
			//Fill_BL = BL_Bound + new Vector2(400, 0);
			Fill_BL = BL_Bound + Vector2( 400, 650 );
			Fill_TR = TR_Bound + Vector2( -400, -450 );

			Stage1RndFill( Fill_BL, Fill_TR, BL_Bound,.35f * CurMakeData->SparsityMultiplier );
		}
		//foreach (BlockBase block in Blocks)
		//{
		//    NormalBlock nblock = block as NormalBlock;
		//    if (null != nblock)
		//        nblock.MakeTopOnly();
		//}

		DEBUGMsg( _T( "Pre stage 1, about to reset" ) );

		PlayMode = 2;
		RecordPosition = true;
		ResetAll( true );

		//int t1 = System.Environment.TickCount;

		// Set special Bob parameters
		MySourceGame->SetAdditionalBobParameters( Computers );

		CurMakeData->TRBobMoveZone = TR_Bound;
		CurMakeData->BLBobMoveZone = BL_Bound;
		if ( ReturnEarly == 1 )
			return false;

		// Stage 1 Run through
		int OneFinishedCount = 0;
		while ( CurPhsxStep - Bobs[ 0 ]->IndexOffset < CurPiece->PieceLength )
		{
			if ( EndReached )
				OneFinishedCount += 15;

			if ( OneFinishedCount > 200 )
				break;

			PhsxStep( true );
			for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::ActiveFill_1_Gens.begin(); gen != Generators::ActiveFill_1_Gens.end(); ++gen )
				( *gen )->ActiveFill_1( shared_from_this(), BL_Bound, TR_Bound );
		}
		int LastStep = CurPhsxStep;

		// Continue making Final Platform
		if ( MakeFinalPlat != 0 )
			MakeFinalPlat->Phase2();

		// Update the level's par time
		CurPiece->Par = LastStep;
		Par += CurPiece->Par;

		// Cleanup
		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::Gens.begin(); gen != Generators::Gens.end(); ++gen )
			( *gen )->Cleanup_1( shared_from_this(), BL_Bound, TR_Bound );

		// Overlapping blocks
		if ( CurMakeData->PieceSeed->Style->RemovedUnusedOverlappingBlocks )
			BlockOverlapCleanup();
		Sleep();

		// Remove unused objects
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( !( *obj )->getCore()->GenData.Used && (*obj)->getCore()->GenData.RemoveIfUnused )
				getRecycle()->CollectObject(*obj);
		CleanObjectList();
		Sleep();

		// Remove unused blocks
		for ( BlockVec::const_iterator _block = Blocks.begin(); _block != Blocks.end(); ++_block )
			if ( !( *_block )->getCore()->GenData.Used && (*_block)->getCore()->GenData.RemoveIfUnused )
				getRecycle()->CollectObject(*_block);
		CleanBlockList();
		CleanDrawLayers();
		Sleep();

		//CurPiece.PieceLength = CurPhsxStep - StartPhsxStep;
		CurPiece->PieceLength = LastStep - StartPhsxStep;

		// Pre Fill #2
		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::PreFill_2_Gens.begin(); gen != Generators::PreFill_2_Gens.end(); ++gen )
		{
			( *gen )->PreFill_2( shared_from_this(), BL_Bound, TR_Bound );
			Sleep();
		}


		FinalizeBlocks();

		//int t3 = System.Environment.TickCount;

		PlayMode = 1;
		RecordPosition = false;
		ResetAll( true );
		Sleep();

		// Set special Bob parameters
		MySourceGame->SetAdditionalBobParameters( Computers );

		if ( ReturnEarly == 2 )
			return false;

		// Stage 2 Run through
		while ( CurPhsxStep < LastStep )
		{
			PhsxStep( true );
		}
		//int t4 = System.Environment.TickCount;
		//Console.WriteLine("Stage 2 finished at {0}, Time = {1}", CurPhsxStep, t4 - t3);

		OverlapCleanup();
		CleanAllObjectLists();
		Sleep();

		Cleanup( Tools::FindAll<boost::shared_ptr<ObjectBase> >( Objects, boost::make_shared<FindLimitGeneralDensityLambda>() ), boost::make_shared<MakeVerticalCleanupHelper>( shared_from_this() ), true, BL_Bound, TR_Bound );
		Sleep();

		Cleanup( ObjectType_COIN, Vector2( 180, 180 ), BL_Bound, TR_Bound + Vector2( 500, 0 ) );
		Sleep();


		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::Gens.begin(); gen != Generators::Gens.end(); ++gen )
			( *gen )->Cleanup_2( shared_from_this(), BL_Bound, TR_Bound );

		CleanAllObjectLists();

		// Finish making Final Platform
		if ( MakeFinalPlat != 0 )
		{
			MakeFinalPlat->Phase3();
			MakeFinalPlat->Cleanup();
		}

		if ( Geometry == LevelGeometry_UP )
		{
			boost::shared_ptr<CloudberryKingdom::NormalBlock> back = MakePillarBack( getFinalDoor()->getPos() + Vector2(0, -400), getFinalDoor()->getPos() + Vector2(0, 2000) );
			back->getBlockCore()->CeilingDraw = true;
			MakePillarBack( getStartDoor()->getPos() + Vector2(0, 400), getStartDoor()->getPos() - Vector2(0, 2000) );
		}
		else
		{
			boost::shared_ptr<CloudberryKingdom::NormalBlock> back = MakePillarBack( getStartDoor()->getPos() + Vector2(0, -400), getStartDoor()->getPos() + Vector2(0, 2000) );
			back->getBlockCore()->CeilingDraw = true;
			MakePillarBack( getFinalDoor()->getPos() + Vector2(0, 400), getFinalDoor()->getPos() - Vector2(0, 2000) );
		}

		return false;
	}

	float Level::SetStepMultiplier( Vector2 &Size, Vector2 &Step )
	{
		float StepMultiplier = 1;
		if ( boost::dynamic_pointer_cast<BobPhsxJetman>( DefaultHeroType ) != 0 )
			StepMultiplier = 3;
		else if ( boost::dynamic_pointer_cast<BobPhsxDouble>( DefaultHeroType ) != 0 )
			StepMultiplier = 1.75f;
		else if ( boost::dynamic_pointer_cast<BobPhsxSmall>( DefaultHeroType ) != 0 )
		{
			Size = Vector2( 100, 50 );
			Step = Vector2( 240, 390 );
			StepMultiplier = 1.5f;
		}
		else if ( boost::dynamic_pointer_cast<BobPhsxBox>( DefaultHeroType ) != 0 )
			StepMultiplier = .7f;
		else if ( boost::dynamic_pointer_cast<BobPhsxBig>( DefaultHeroType ) != 0 )
			StepMultiplier = .7f;
		else if ( boost::dynamic_pointer_cast<BobPhsxMeat>( DefaultHeroType ) != 0 )
		{
			Size = Vector2( 100, 50 );
			Step = Vector2( 240, 390 );
			StepMultiplier = 1000;
		}
		return StepMultiplier;
	}

	boost::shared_ptr<NormalBlock> Level::MakePillarBack( Vector2 p1, Vector2 p2 )
	{
		boost::shared_ptr<NormalBlock> doo = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
		doo->Init( ( p1 + p2 ) / 2, Vector2( 350, abs( p2.Y - p1.Y ) / 2 ), getMyTileSetInfo() );

		AddBlock( doo );

		doo->getBlockCore()->Virgin = true;
		doo->getBlockCore()->RemoveOverlappingObjects = false;
		SetBackblockProperties( doo );

		return doo;
	}

	void Level::CleanupFireSpinners( Vector2 BL, Vector2 TR )
	{
	}

	void Level::AutoFireSpinners()
	{
	}

	Vector2 Level::GetLadderSize( LadderType Type )
	{
		switch ( Type )
		{
			case LadderType_SIMPLE:
				return Vector2( 1050, 0 );

			case LadderType_SIMPLE2:
				return Vector2( 1050, 0 );

			case LadderType_SIMPLE_MOVING:
				return Vector2( 850, 0 );

			case LadderType_DOUBLE_MOVING:
				return Vector2( 850, 0 );

			case LadderType_MAKE_PLAT:
				return Vector2( 1000, 0 );
		}

		return Vector2();
	}

	void Level::MakeLadder( const boost::shared_ptr<PieceSeedData> &Piece )
	{
		Vector2 LeftCenter = Piece->Start;
		LadderType Ladder = Piece->Ladder;

		Vector2 Center, Size, pos;
		boost::shared_ptr<BlockEmitter> bm;
		boost::shared_ptr<NormalBlock> block;

		boost::shared_ptr<CameraZone> CamZone;

		float y = 0;
		int Count = 0;
		Vector2 offset;
		switch ( Ladder )
		{
			case LadderType_FINAL_BOUNCY:
				y = LeftCenter.Y - getMainCamera()->GetHeight() / 2 - 250;
				while ( y < LeftCenter.Y + getMainCamera()->GetHeight() / 2 - 400 )
				{
					boost::shared_ptr<BouncyBlock> bouncy;
					bouncy = boost::static_pointer_cast<BouncyBlock>( MySourceGame->Recycle->GetObject( ObjectType_BOUNCY_BLOCK, false ) );
					bouncy->Init( Vector2( LeftCenter.X, y ), Vector2( 220, 220 ), 70, shared_from_this() );
					bouncy->getCore()->DrawLayer = 9;

					bouncy->getCore()->GenData.RemoveIfUnused = true;
					bouncy->getBlockCore()->BlobsOnTop = false;
					bouncy->getCore()->GenData.AlwaysLandOn = true;

					AddBlock( bouncy );

					y += 200;
				}

				break;

			case LadderType_FINAL_PLAT:
				block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
				block->Init( TR, Vector2(), getMyTileSetInfo() );
				block->Extend( Side_LEFT, LeftCenter.X );
				block->Extend( Side_RIGHT, LeftCenter.X + 5000 );
				block->Extend( Side_TOP, LeftCenter.Y - getMainCamera()->GetHeight() / 2 + 150 );
				block->Extend( Side_BOTTOM, LeftCenter.Y - getMainCamera()->GetHeight() / 2 - 250 );

				AddBlock( block );


				// Camera zone
				FinalCamZone = CamZone = boost::static_pointer_cast<CameraZone>( getRecycle()->GetObject(ObjectType_CAMERA_ZONE, false) );
				CamZone->Init( block->getBox()->Current->Center + Vector2(700, 500), block->getBox()->Current->Size / 3 + Vector2(0, getMainCamera()->GetHeight() / 2 + 1000) );
				CamZone->Start = LeftCenter - Vector2( 100000, 0 );
				CamZone->End = CamZone->Start;
				CamZone->End.X = 400 + block->getBox()->Current->TR.X - getMainCamera()->GetWidth() / 2 - 1500;
				CamZone->Start = CamZone->End;
				AddObject( CamZone );


				// Stop block, to prevent Bob from running off edge
				block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
				block->Init( TR, Vector2(), getMyTileSetInfo() );
				block->Extend( Side_LEFT, LeftCenter.X + 4400 );
				block->Extend( Side_RIGHT, LeftCenter.X + 4500 );
				block->Extend( Side_BOTTOM, LeftCenter.Y - 1500 );
				block->Extend( Side_TOP, LeftCenter.Y + 1500 );

				AddBlock( block );

				break;

			case LadderType_SIMPLE:
				Size = Vector2( 250, 40 );
				Center = LeftCenter + Vector2( GetLadderSize( Ladder ).X / 2, 0 );

				pos = Center - Vector2( 0, getMainCamera()->GetHeight() / 2 );
				while ( pos.Y < Center.Y + getMainCamera()->GetHeight() / 2 )
				{
					block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
					block->getBox()->TopOnly = true;
					block->Init( pos, Size, getMyTileSetInfo() );

					block->getCore()->GenData.RemoveIfUnused = false;
					block->getBlockCore()->BlobsOnTop = false;
					block->getCore()->GenData.AlwaysUse = true;
					block->getBlockCore()->Virgin = true;

					AddBlock( block );

					pos.Y += 400;
				}

				break;

			case LadderType_SIMPLE2:
				Size = Vector2( 100, 40 );
				Center = LeftCenter + Vector2( GetLadderSize( Ladder ).X / 2, 0 );

				pos = Center - Vector2( 0, getMainCamera()->GetHeight() / 2 );
				offset = Vector2( 90, 0 );
				Count = 0;
				while ( pos.Y < Center.Y + getMainCamera()->GetHeight() / 2 )
				{
					block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
					block->getBox()->TopOnly = true;
					if ( Count % 2 == 0 )
						block->Init( pos + offset, Size, getMyTileSetInfo() );
					else
						block->Init( pos - offset, Size, getMyTileSetInfo() );

					block->getCore()->GenData.RemoveIfUnused = false;
					block->getBlockCore()->BlobsOnTop = false;
					block->getCore()->GenData.AlwaysUse = true;
					block->getBlockCore()->Virgin = true;

					AddBlock( block );

					Count++;
					pos.Y += 400;
				}

				break;

			case LadderType_SIMPLE_MOVING:
				Center = LeftCenter + Vector2( GetLadderSize( Ladder ).X / 2, -getMainCamera()->GetHeight() / 2 - 250 );

				bm = boost::static_pointer_cast<BlockEmitter>( getRecycle()->GetObject(ObjectType_BLOCK_EMITTER, false) );
				bm->Init( Vector2(), shared_from_this(), Piece->ElevatorBoxStyle );
				bm->EmitData.Position = bm->getCore()->Data.Position = Center;
				bm->EmitData.Velocity = Vector2( 0, 6 );
				bm->Delay = 100;
				bm->Offset = 5;
				bm->Size = Vector2( 250, 40 );
				bm->AlwaysOn = true;
				bm->Range.Y = getMainCamera()->GetHeight() / 2;

				bm->getCore()->GenData.RemoveIfUnused = false;
				bm->getCore()->GenData.AlwaysUse = true;

				AddObject( bm );

				break;

			case LadderType_DOUBLE_MOVING:
				// Left emitter                    
				Center = LeftCenter + Vector2( GetLadderSize( Ladder ).X / 2, -getMainCamera()->GetHeight() / 2 - 250 );

				bm = boost::static_pointer_cast<BlockEmitter>( getRecycle()->GetObject(ObjectType_BLOCK_EMITTER, false) );
				bm->Init( Vector2(), shared_from_this(), Piece->ElevatorBoxStyle );
				bm->EmitData.Position = bm->getCore()->Data.Position = Center + Vector2(-175, 0);
				bm->EmitData.Velocity = Vector2( 0, 6 );
				bm->Delay = 100;
				bm->Offset = 5;
				bm->Size = Vector2( 120, 40 );
				bm->AlwaysOn = true;
				bm->Range.Y = getMainCamera()->GetHeight() / 2;

				bm->getCore()->GenData.RemoveIfUnused = false;
				bm->getCore()->GenData.AlwaysUse = true;

				AddObject( bm );

				// Right emitter
				Center = LeftCenter + Vector2( GetLadderSize( Ladder ).X / 2, getMainCamera()->GetHeight() / 2 + 250 );

				bm = boost::static_pointer_cast<BlockEmitter>( getRecycle()->GetObject(ObjectType_BLOCK_EMITTER, false) );
				bm->Init( Vector2(), shared_from_this(), Piece->ElevatorBoxStyle );
				bm->EmitData.Position = bm->getCore()->Data.Position = Center + Vector2(175, 0);
				bm->EmitData.Velocity = Vector2( 0, -6 );
				bm->Delay = 100;
				bm->Offset = 5;
				bm->Size = Vector2( 120, 40 );
				bm->AlwaysOn = true;
				bm->Range.Y = getMainCamera()->GetHeight() / 2;

				bm->getCore()->GenData.RemoveIfUnused = false;
				bm->getCore()->GenData.AlwaysUse = true;

				AddObject( bm );

				break;
		}
	}

	const bool Level::getReplayAvailable() const
	{
		return MySwarmBundle != 0;
	}

	void Level::SaveCamera()
	{
		if ( NoCameraChange )
			return;

		HoldCamera = getMainCamera();
		setMainCamera( boost::make_shared<Camera>( getMainCamera() ) );
	}

	void Level::RestoreCamera()
	{
		if ( NoCameraChange )
			return;

		// Destroy the temporary replay camera and
		// start using the previous camera once again
		getMainCamera()->Release();
		setMainCamera( HoldCamera );
	}

	void Level::SetReplay()
	{
		int NumBobs = static_cast<int>( Bobs.size() );
		Bobs.clear();
		//for (int i = 0; i < CurrentRecording.NumBobs; i++)
		for ( int i = 0; i < NumBobs; i++ )
		{
			if ( static_cast<int>( MySwarmBundle->CurrentSwarm->MainRecord->Recordings.size() ) <= i )
				break;

			//Bob Comp = new Bob(Prototypes.bob[DefaultHeroType], false);
			boost::shared_ptr<Bob> Comp = boost::make_shared<Bob>( DefaultHeroType, false );
			Bob_PostConstruct( Comp, DefaultHeroType, false );
			Comp->SetColorScheme( PlayerManager::Get( i )->ColorScheme_Renamed );

			//Comp.MyRecord = CurrentRecording.Recordings[i];
			Comp->MyRecord = MySwarmBundle->CurrentSwarm->MainRecord->Recordings[ i ];
			Comp->CompControl = true;
			Comp->Immortal = true;
			AddBob( Comp );
		}
	}

	void Level::WatchReplay( bool SaveCurInfo )
	{
		Tools::setPhsxSpeed( 1 );

		SuppressCheckpoints = true;
		GhostCheckpoints = true;

		MyReplayGUI = boost::make_shared<ReplayGUI>();
		MyReplayGUI->Type = ReplayGUIType_REPLAY;
		MyGame->AddGameObject( MyReplayGUI );

		MyReplayGUI->StartUp();

		if ( Recording_Renamed )
			StopRecording();

		if ( !MySwarmBundle->Initialized )
			MySwarmBundle->Init( shared_from_this() );

		if ( SaveCurInfo )
		{
			HoldPlayerBobs.clear();
			AddRange( HoldPlayerBobs, Bobs );
			HoldCamPos = getMainCamera()->Data.Position;
			SaveCamera();
		}

		// Select the first swarm in the bundle to start with
		MySwarmBundle->SetSwarm( shared_from_this(), 0 );

		setPreventReset( false );
		FreezeCamera = false;
		Watching = true;
		Replay = true;
		ReplayPaused = false;
		//            MainReplayOnly = true;


		SetReplay();

		setSetToReset( true );
	}

	void Level::WatchComputer()
	{
		WatchComputer( true );
	}

	void Level::WatchComputer( bool GUI )
	{
		if ( Watching )
			return;

		Tools::setPhsxSpeed( 1 );

		// Consider the reset free if the players are close to the start
		FreeReset = CloseToStart();
		if ( !FreeReset )
			CountReset();

		SaveCamera();

		if ( GUI )
		{
			// Create the GUI
			MyReplayGUI = boost::make_shared<ReplayGUI>();
			MyReplayGUI->Type = ReplayGUIType_COMPUTER;
			MyGame->AddGameObject( MyReplayGUI );

			MyReplayGUI->StartUp();
		}

		Watching = true;
		SuppressCheckpoints = true;
		GhostCheckpoints = true;

		// Swap the player Bobs for computer Bobs
		HoldPlayerBobs.clear();
		AddRange( HoldPlayerBobs, Bobs );

		Bobs.clear();
		for ( int i = 0; i < CurPiece->NumBobs; i++ )
		{
			//Bob Comp = new Bob(Prototypes.bob[DefaultHeroType], false);
			boost::shared_ptr<Bob> Comp = boost::make_shared<Bob>( DefaultHeroType, false );
			Bob_PostConstruct( Comp, DefaultHeroType, false );

			Comp->MyPiece = CurPiece;
			Comp->MyPieceIndex = i;
			Comp->MyRecord = CurPiece->Recording_Renamed[ i ];
			Comp->CompControl = true;
			Comp->Immortal = true;
			AddBob( Comp );

			/*
			if (CloudberryKingdomGame.SimpleAiColors)
			{
			    int index = (new int[] { 0, 3, 5, 1 })[i];
			    Comp.SetColorScheme(ColorSchemeManager.ComputerColorSchemes[index]);
			}
			else
			    Comp.SetColorScheme(Tools.GlobalRnd.RandomItem<ColorScheme>(ColorSchemeManager.ComputerColorSchemes));
			*/
			Comp->SetColorScheme( ColorSchemeManager::ComputerColorSchemes[ 0 ] );

			Comp->MoveData = CurPiece->MyMakeData->MoveData[ i ];
			int Copy = Comp->MoveData.Copy;
			if ( Copy >= 0 )
				Comp->SetColorScheme( Bobs[ Copy ]->MyColorScheme );
		}

		// Set special Bob parameters
		MySourceGame->SetAdditionalBobParameters( Bobs );

		// Additional actions
		if ( OnWatchComputer != 0 )
			OnWatchComputer->Apply();

		setSetToReset( true );
	}

	bool Level::EndOfReplay()
	{
		return CurPhsxStep >= CurPiece->PieceLength;
	}

	void Level::EndReplay()
	{
		SuppressCheckpoints = false;
		GhostCheckpoints = false;

		RestoreCamera();

		Replay = Watching = false;
		Recording_Renamed = false;
		ReplayPaused = false;

		getMainCamera()->Data.Position = HoldCamPos;
		//FreezeCamera = true;
		getMainCamera()->Update();

		Bobs.clear();
		AddRange( Bobs, HoldPlayerBobs );
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
		{
			Clear( ( *bob )->PlayerObject->AnimQueue );
			( *bob )->PlayerObject->EnqueueAnimation( 0, 0, true );
			( *bob )->PlayerObject->DequeueTransfers();
		}

		if ( OnEndReplay != 0 )
			OnEndReplay->Apply();
	}

	void Level::EndComputerWatch()
	{
		RestoreCamera();

		ReplayPaused = false;
		StartPlayerPlay();

		if ( OnEndReplay != 0 )
			OnEndReplay->Apply();
	}

	const boost::shared_ptr<StyleData> &Level::getStyle() const
	{
		return CurMakeData->PieceSeed->Style;
	}

	const boost::shared_ptr<PieceSeedData> &Level::getPieceSeed() const
	{
		return CurMakeData->PieceSeed;
	}

	boost::shared_ptr<LevelPiece> Level::StartNewPiece( int Length, BobVec Computer )
	{
		return StartNewPiece( Length, Computer, 1 );
	}

	boost::shared_ptr<LevelPiece> Level::StartNewPiece( int Length, BobVec Computer, int NumBobs )
	{
		boost::shared_ptr<LevelPiece> NewPiece = boost::make_shared<LevelPiece>( Length, shared_from_this(), Computer, NumBobs );
		LevelPieces.push_back( NewPiece );
		return NewPiece;
	}

	void Level::Clone( const boost::shared_ptr<Level> &A )
	{
		for ( BlockVec::const_iterator block = A->Blocks.begin(); block != A->Blocks.end(); ++block )
		{
			boost::shared_ptr<BlockBase> DestBlock = boost::static_pointer_cast<BlockBase>( MySourceGame->Recycle->GetObject( ( *block )->getCore()->MyType, false ) );
			DestBlock->Clone( *block );

			AddBlock( DestBlock );
		}

		for ( ObjectVec::const_iterator obj = A->Objects.begin(); obj != A->Objects.end(); ++obj )
		{
			boost::shared_ptr<ObjectBase> DestObj = boost::static_pointer_cast<ObjectBase>( MySourceGame->Recycle->GetObject( ( *obj )->getCore()->MyType, false ) );
			DestObj->Clone( *obj );

			AddObject( DestObj );
		}
	}

	void Level::Fill( Vector2 BL, Vector2 TR, float xstep, float ystep, const boost::shared_ptr<Lambda_1<Vector2> > &FillFunc )
	{
		Fill( BL, TR, Vector2( xstep, xstep ), ystep, FillFunc );
	}

	void Level::Fill( Vector2 BL, Vector2 TR, Vector2 xstep, float ystep, const boost::shared_ptr<Lambda_1<Vector2> > &FillFunc )
	{
		if ( Sign( TR.X - BL.X ) != Sign( xstep.X ) )
			return;
		if ( Sign( TR.Y - BL.Y ) != Sign( ystep ) )
			return;

		Vector2 pos = BL;
		while ( pos.Y < TR.Y )
		{
			pos.X = BL.X;
			while ( pos.X <= TR.X )
			{
				FillFunc->Apply( pos );
				pos.X += getRnd()->RndFloat(xstep);
			}
			if ( TR.X - ( pos.X - xstep.X ) > .5f * xstep.X )
			{
				pos.X = TR.X;
				FillFunc->Apply( pos );
			}

			pos.Y += ystep;
		}
	}

	void Level::FadeMusic()
	{
		if ( Tools::SongWad != 0 )
			Tools::SongWad->FadeOut();
	}

	void Level::EndOfLevelBonus( const boost::shared_ptr<PlayerData> &FinishingPlayer )
	{
		EndOfLevelBonus( FinishingPlayer, true );
	}

	void Level::EndOfLevelBonus( const boost::shared_ptr<PlayerData> &FinishingPlayer, bool IncrLevels )
	{
		std::vector<boost::shared_ptr<PlayerData> > players;
		if ( FinishingPlayer == 0 )
			players = PlayerManager::getAlivePlayers();
		else
		{
			players = std::vector<boost::shared_ptr<PlayerData> >();
			players.push_back( FinishingPlayer );
		}

		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = players.begin(); player != players.end(); ++player )
		{
			if ( IncrLevels )
				( *player )->getStats()->Levels++;
			( *player )->getStats()->Score += 500;
		}
	}

	void Level::EndLevel()
	{
		Finished = true;

		if ( MyGame != 0 )
		{
			MyGame->RemoveGameObjects( GameObject::Tag_REMOVE_ON_LEVEL_FINISH );
			MyGame->AllowQuickJoin = false;
		}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = PlayerManager::getExistingPlayers().begin(); player != PlayerManager::getExistingPlayers().end(); ++player )
		{
			CoinsCountInStats = true;
			( *player )->getStats()->TotalCoins += NumCoins;
			( *player )->getStats()->TotalBlobs += NumBlobs;
		}

		KeepCoinsDead();

		if ( Recording_Renamed )
		{
			AddCurRecording();
			Recording_Renamed = false;
		}
		HaveTimeLimit = false;

		// Prevent additional deaths/replays/resets
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
		{
			( *bob )->Immortal = true;
			( *bob )->ScreenWrap = true;
		}

		CanWatchComputer = false;
		setPreventReset( true );
		setSetToReset( false );
	}

	void Level::SoftEndLevel()
	{
		Finished = true;

		// Prevent additional deaths/replays/resets
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
			( *bob )->Immortal = true;

		CanWatchComputer = false;
		setPreventReset( true );
		setSetToReset( false );
	}

	void Level::UndoSoftEndLevel()
	{
		Finished = false;

		// Prevent additional deaths/replays/resets
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
			( *bob )->Immortal = false;

		setPreventReset( false );
	}

const float Level::SafetyNetHeight = 124;

	boost::shared_ptr<BlockBase> Level::Stage1SafetyNet( Vector2 BL, Vector2 TR, Vector2 size, float xstep, StyleData::GroundType Type )
	{
		bool Virgin = false;
		bool Used = false;
		bool BoxesOnly = false;
		bool InvertDraw = false;
		bool Invert = false;

		switch ( Type )
		{
			case StyleData::GroundType_USED:
				Used = true;
				break;

			case StyleData::GroundType_VIRGIN_USED:
				Virgin = Used = true;
				break;

			case StyleData::GroundType_INVERTED_USED:
				Virgin = Used = true;
				//InvertDraw = true;
				Invert = true;
				break;

			case StyleData::GroundType_SAFETY_NET:
				break;

			case StyleData::GroundType_INVERT_SAFETY_NET:
				Invert = true;
				break;

			case StyleData::GroundType_INVISIBLE_USED:
				Used = true;
				BoxesOnly = true;
				Virgin = true;
				break;

			default:
				return 0;
		}

		// Safety net
		__LastBlock.reset();
		
		Fill( BL + Vector2( 0, SafetyNetHeight ), Vector2( TR.X, BL.Y + SafetyNetHeight + 1 ), xstep, 50, boost::make_shared<SafetyNetLambda>( SafetyNetLambda( shared_from_this(), BL, TR, size, xstep, Type, Virgin, Used, BoxesOnly, InvertDraw, Invert ) ) );

		return __LastBlock;
	}

	boost::shared_ptr<Door> Level::PlaceDoorOnBlock_Unlayered( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop )
	{
		return PlaceDoorOnBlock( pos, block, AddBackdrop, MyTileSet, false );
	}

	boost::shared_ptr<Door> Level::PlaceDoorOnBlock( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop )
	{
		return PlaceDoorOnBlock( pos, block, AddBackdrop, MyTileSet, true );
	}

	boost::shared_ptr<Door> Level::PlaceDoorOnBlock( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop, const boost::shared_ptr<TileSet> &BackdropTileset )
	{
		return PlaceDoorOnBlock( pos, block, AddBackdrop, BackdropTileset, true );
	}

	boost::shared_ptr<Door> Level::PlaceDoorOnBlock( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop, const boost::shared_ptr<TileSet> &BackdropTileset, bool LayeredDoor )
	{
		int DesiredDoorLayer = 0, DesiredDoorLayer2 = 0;

		// Add door
		boost::shared_ptr<Door> door = boost::static_pointer_cast<Door>( getRecycle()->GetObject(ObjectType_DOOR, false) );
		//door.Layered = LayeredDoor;
		door->StampAsUsed( 0 );

		door->SetDoorType( BackdropTileset, shared_from_this() );

		AddObject( door );

		// Place the door above the block
		block->getBox()->CalcBounds_Full();
		door->PlaceAt( Vector2( pos.X, block->getBox()->TR.Y + 1 ) );

		// If we don't want a backdrop we're done
		if ( !AddBackdrop )
		{
			door->getCore()->DrawLayer = DesiredDoorLayer;
			door->getCore()->DrawLayer2 = DesiredDoorLayer2;
			return door;
		}

		// Add a backdrop block that the door opens into
		boost::shared_ptr<NormalBlock> backblock = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
		MadeBackBlock = backblock;
		backblock->Clone( block );

		door->MyBackblock = backblock;

		backblock->Extend( Side_TOP, getMainCamera()->TR.Y + 500 );
		backblock->Extend( Side_BOTTOM, getMainCamera()->BL.Y - 500 );

		SetBackblockProperties( backblock );

		backblock->getCore()->setMyTileSet(BackdropTileset);

		// Make sure door is just in front of backdrop
		door->getCore()->DrawLayer = DesiredDoorLayer;

		return door;
	}

	void Level::SetBackblockProperties( const boost::shared_ptr<NormalBlock> &backblock )
	{
		float shade = .85f;
		backblock->MyDraw->SetTint( Color( shade, shade, shade ) );

		backblock->getCore()->GenData.Used = true;
		backblock->getBlockCore()->NonTopUsed = true;
		backblock->getBlockCore()->Virgin = true;

		backblock->getBlockCore()->UseTopOnlyTexture = false;
		backblock->getBox()->TopOnly = true;

		backblock->getBlockCore()->DrawLayer = 0;

		backblock->getCore()->Real = false;

		AddBlock( backblock );
	}

	void Level::SpreadStartPositions( const boost::shared_ptr<LevelPiece> &piece, const boost::shared_ptr<MakeData> &make, Vector2 pos, Vector2 SpanPer )
	{
		int n = __max( 1, make->NumInitialBobs );
		Vector2 span = SpanPer * ( static_cast<float>( n - 1 ) );
		Vector2 add = span / static_cast<float>( n );
		for ( int i = 0; i < n; i++ )
		{
			//PhsxData[] data = piece.StartData;
			piece->StartData[ i ].Position = pos + span / 2.f - static_cast<float>( i ) * add;
		}
	}

	float Level::MakeInitialPlats( Vector2 BL, Vector2 TR, const boost::shared_ptr<SingleData> &Style )
	{
		Vector2 size;
		Vector2 pos;
		boost::shared_ptr<NormalBlock> block = 0;

		size = Vector2( 350, 2250 );
		if ( CurMakeData->SkinnyStart )
			size.X = 75;

		pos = Vector2( BL.X + 10, ( BL.Y + TR.Y ) / 2 ) + Vector2( 0, -size.Y );

		pos += getInfo()->ShiftStartBlock;

		boost::shared_ptr<Door> door = 0;
		switch ( Style->MyInitialPlatsType )
		{
			case StyleData::InitialPlatsType_SPACESHIP:
				return MakeInitial_Spaceship( BL, TR, pos, block );

			case StyleData::InitialPlatsType_DOOR:
				size.X += 100;
				pos.X -= 50;

				block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );

				// New style end blocks
				if ( MyTileSet->FixedWidths )
				{
					block->getBlockCore()->StartPiece = true;
					block->getCore()->DrawLayer = 0;
				}

				block->Init( pos, size, getMyTileSetInfo() );
				block->getBlockCore()->BlobsOnTop = false;
				block->StampAsUsed( 0 );
				block->getCore()->GenData.RemoveIfUnused = false;

				if ( CurMakeData->PieceSeed->ZoomType == LevelZoom_BIG )
					block->Extend( Side_LEFT, block->getBox()->BL.X + 30 );

				// Randomize height of start
				block->Extend( Side_TOP, block->getBox()->TR.Y + getRnd()->RndFloat(Style->InitialDoorYRange) + 0 );

				AddBlock( block );

				// Make the door
				if ( CurMakeData->PieceSeed->ZoomType == LevelZoom_BIG )
					pos.X += 150;

				pos.X += getInfo()->ShiftStartDoor;

				door = PlaceDoorOnBlock( pos, block, MyTileSet->CustomStartEnd ? false : true );
				door->getCore()->EditorCode1 = LevelConnector::StartOfLevelCode;

				// Shift start position
				SpreadStartPositions( CurPiece, CurMakeData, door->getPos(), Vector2(50, 0) );

				return block->getBox()->TR.X + getRnd()->RndFloat(100, 250);

			case StyleData::InitialPlatsType_NORMAL:
				return MakeInitial_Normal( BL, TR, size );

			case StyleData::InitialPlatsType_LANDING_ZONE:
				return MakeInitial_LandingZone( BL, TR, size );
		}

		return 0;
	}

	float Level::MakeInitial_LandingZone( Vector2 &BL, Vector2 &TR, Vector2 &size )
	{
		boost::shared_ptr<NormalBlock> nblock;
		Vector2 Pos = BL;
		size = Vector2( 2200, 200 );
		nblock = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
		nblock->getCore()->setMyTileSet(MyTileSet);
		nblock->Init( Pos, size, getMyTileSetInfo() );
		nblock->Extend( Side_BOTTOM, getMainCamera()->BL.Y - 300 );
		nblock->Extend( Side_TOP, getMainCamera()->BL.Y + 500 );
		//nblock.Extend(Side.Right, Pos.X + MainCamera.GetWidth() + 7500);
		//nblock.Extend(Side.Left, Pos.X + MainCamera.GetWidth() - 230);

		nblock->getCore()->GenData.RemoveIfUnused = false;
		nblock->getBlockCore()->Virgin = true;
		nblock->getCore()->GenData.AlwaysLandOn = true;

		nblock->getCore()->EditorCode1 = _T("Landing Platform");

		AddBlock( nblock );

		// Shift start position
		for ( int i = 0; i < CurMakeData->NumInitialBobs; i++ )
		{
			CurPiece->StartData[ i ].Position.X += size.X - 500;
		}

		return VanillaFill( BL + Vector2( size.X, 0 ), Vector2( BL.X + size.X + 500, TR.Y - 500 ), 600 );
	}

	float Level::MakeInitial_Spaceship( Vector2 &BL, Vector2 &TR, Vector2 &pos, boost::shared_ptr<NormalBlock> &block )
	{
		BL = BL + Vector2( -600, -400 );
		TR = Vector2( BL.X + 750, TR.Y + 400 );

		return TR.X + 400;
	}

	float Level::MakeInitial_Normal( Vector2 BL, Vector2 TR, Vector2 size )
	{
		__block_fromlambda.reset();

		Fill( BL, Vector2( BL.X + 10, TR.Y ), 200, 250, boost::make_shared<MakeInitialLambda>( shared_from_this(), size ) );

		if ( __block_fromlambda == 0 )
			return 0;
		else
			return __block_fromlambda->getBox()->TR.X;
	}

	float Level::VanillaFill( Vector2 BL, Vector2 TR, float width )
	{
		return VanillaFill( BL, TR, width, 200, 0, 0 );
	}

	float Level::VanillaFill( Vector2 BL, Vector2 TR, float width, float ystep, const boost::shared_ptr<Lambda_1<boost::shared_ptr<BlockBase> > > &PreInit, const boost::shared_ptr<Lambda_1<boost::shared_ptr<BlockBase> > > &PostInit )
	{
		Vector2 Pos = BL;

		float step = 2 * width;

		boost::shared_ptr<NormalBlock> block = 0;
		while ( Pos.X < TR.X )
		{
			while ( Pos.Y < TR.Y )
			{
				block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );

				if ( PreInit != 0 )
					PreInit->Apply( block );

				block->Init( Pos + Vector2( width, -200 ), Vector2( width, 200 ), getMyTileSetInfo() );
				block->Extend( Side_BOTTOM, BL.Y - 300 - CurMakeData->PieceSeed->ExtraBlockLength );

				block->getCore()->GenData.RemoveIfUnused = true;
				block->getBlockCore()->Virgin = true;
				block->getCore()->GenData.AlwaysLandOn = true;
				block->getCore()->GenData.AlwaysUse = true;

				// Make the last column of blocks EdgeJumpOnly
				if ( Pos.X + step >= TR.X )
					block->getCore()->GenData.EdgeJumpOnly = true;

				if ( PostInit != 0 )
					PostInit->Apply( block );

				AddBlock( block );

				Pos.Y += ystep;
			}

			Pos.Y = BL.Y;
			Pos.X += step;
		}

		return Pos.X;
	}

	float Level::RandomBlocks( Vector2 BL, Vector2 TR, boost::shared_ptr<MakeData> &makeData )
	{
		Vector2 Pos = BL;

		float width = 400;
		float step = 2 * width;

		boost::shared_ptr<NormalBlock> block = 0;
		while ( Pos.X < TR.X )
		{
			block = boost::static_pointer_cast<NormalBlock>( getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
			block->Init( Pos + Vector2( width, getRnd()->RndFloat(200, 1000) ), Vector2(getRnd()->RndFloat(width / 2, width), 200), getMyTileSetInfo() );
			block->Extend( Side_BOTTOM, BL.Y - 300 );

			block->getCore()->GenData.RemoveIfUnused = true;
			block->getBlockCore()->BlobsOnTop = false;
			block->getCore()->GenData.AlwaysLandOn = true;

			// Make the last column of blocks EdgeJumpOnly
			if ( Pos.X + step >= TR.X )
				block->getCore()->GenData.EdgeJumpOnly = true;

			block->StampAsUsed( CurPhsxStep );

			AddBlock( block );

			Pos.Y = BL.Y;
			Pos.X += getRnd()->RndFloat(step, 2 * step);
		}

		return Pos.X;
	}

int Level::CountToSleep = 0;

	void Level::Sleep()
	{
		//Thread.Sleep(3);
	}

	void Level::CheckToSleep()
	{
		//CountToSleep++;
		//if (CountToSleep >= 5)
		//{
		//    CountToSleep = 0;
		//    Sleep();
		//}
	}

	void Level::Stage1RndFill( Vector2 BL, Vector2 TR, Vector2 BL_Cutoff, float Sparsity )
	{
		Vector2 xstep = Vector2( CurMakeData->PieceSeed->Style->FillxStep * Sparsity, 0 );
		xstep.Y = xstep.X;
		Fill( BL, TR, xstep, CurMakeData->PieceSeed->Style->FillyStep, boost::make_shared<Stage1RndFillLambda>( shared_from_this(), BL, TR, BL_Cutoff ) );
	}

	boost::shared_ptr<CameraZone> Level::MakeCameraZone()
	{
		return MakeCameraZone( Vector2( ( CurMakeData->PieceSeed->End.X - CurMakeData->PieceSeed->Start.X ) / 2 + 150, getMainCamera()->GetHeight() / 2 ) );
	}

	boost::shared_ptr<CameraZone> Level::MakeCameraZone( Vector2 Size )
	{
		boost::shared_ptr<PieceSeedData> s = CurMakeData->PieceSeed;

		boost::shared_ptr<CameraZone> CamZone = boost::static_pointer_cast<CameraZone>( getRecycle()->GetObject(ObjectType_CAMERA_ZONE, false) );
		CamZone->Init( ( s->Start + s->End ) / 2, Size );
		CamZone->Start = s->Start + s->CamZoneStartAdd;
		CamZone->End = s->End + s->CamZoneEndAdd;

		if ( s->ZoomType == LevelZoom_BIG )
		{
			CamZone->Zoom = .55f;
			CamZone->Start.X += 1550;
			CamZone->End.X -= 600;
		}

		Vector2 Tangent = CamZone->End - CamZone->Start;
		if ( CurMakeData->InitialCamZone )
			CamZone->Start = CamZone->Start + Vector2( getMainCamera()->GetWidth() / 2 - 300, 0 );
		else
			CamZone->Start -= 2 * Tangent;
		CamZone->End += 2 * Tangent;

		AddObject( CamZone );

		return CamZone;
	}

bool Level::showdebug = false;
bool Level::dodebug = false;

	void Level::DEBUGMsg( const std::wstring &str )
	{
	#if defined(DEBUG)
		if ( !showdebug || !dodebug )
			return;

		CloudberryKingdomGame::debugstring = str;
		//delay( 5000 );
		CloudberryKingdomGame::debugstring = _T( "DOING" ) + str;
	#endif
	}

	void Level::PREFILL()
	{
		if ( !dodebug )
			return;

		for ( int i = 0; i < 15000; i++ )
		{
			getRecycle()->CollectObject(getRecycle()->GetNewObject(ObjectType_MOVING_PLATFORM, true));
			getRecycle()->CollectObject(getRecycle()->GetNewObject(ObjectType_BLOCK_EMITTER, true));
			getRecycle()->CollectObject(getRecycle()->GetNewObject(ObjectType_SPIKEY_LINE, true));
			getRecycle()->CollectObject(getRecycle()->GetNewObject(ObjectType_NORMAL_BLOCK, true));
			getRecycle()->CollectObject(getRecycle()->GetNewObject(ObjectType_COIN, true));
		}
	}

	std::wstring Level::Pre1 = _T( "" ), Level::Pre2 = _T( "" ), Level::Post = _T( "" );
	int Level::Step1 = 0, Level::Step2 = 0;

	bool Level::MakeSingle( int Length, float MaxRight, float MaxLeft, int StartPhsxStep, int ReturnEarly, const boost::shared_ptr<MakeData> &makeData )
	{
		int TestNumber;

		// Tracking info
		Pre1 = Pre2 = Post = _T( "" );
		Step1 = Step2 = 0;
		Pre1 += L'A';

		this->MaxRight = MaxRight;

		PREFILL();
		DEBUGMsg( _T( "Pre stage 1, about to fill" ) );
		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( Format( _T( "Test: %d" ), TestNumber ).c_str() );

		CurMakeData = makeData;
		InitMakeData( CurMakeData );
		boost::shared_ptr<SingleData> Style = boost::static_pointer_cast<SingleData>( CurMakeData->PieceSeed->Style );

		// Calculate the style parameters
		Style->CalcGenParams( CurMakeData->PieceSeed, shared_from_this() );

		// Length padding
		MaxRight += Style->LengthPadding;
		CurMakeData->PieceSeed->End.X += Style->LengthPadding;
		this->MaxRight = MaxRight;

		// Move camera
		getMainCamera()->Data.Position = CurMakeData->CamStartPos;
		getMainCamera()->Update();

		// New bobs
		BobVec Computers = CurMakeData->MakeBobs( shared_from_this() );

		// New level piece
		boost::shared_ptr<LevelPiece> Piece = CurPiece = CurMakeData->MakeLevelPiece( shared_from_this(), Computers, Length, StartPhsxStep );

		// Camera Zone
		boost::shared_ptr<CameraZone> CamZone = MakeCameraZone();
		CamZone->SetZoom( getMainCamera() );
		Sleep();

		// Set the camera start position
		if ( CurMakeData->InitialCamZone )
			CurPiece->CamStartPos = CurMakeData->CamStartPos = CamZone->Start;
		else
			CurPiece->CamStartPos = CurMakeData->CamStartPos;


		Vector2 BL_Cutoff;

		float Left;
		Left = MaxLeft;

		boost::shared_ptr<NormalBlock_Parameters> BlockParams = boost::static_pointer_cast<NormalBlock_Parameters>( Style->FindParams( NormalBlock_AutoGen::getInstance() ) );
		if ( !BlockParams->DoInitialPlats )
			CurMakeData->InitialPlats = false;
		if ( !BlockParams->DoFinalPlats )
			CurMakeData->FinalPlats = false;

		// Initial platform
		if ( CurMakeData->InitialPlats && Style->MakeInitialPlats )
		{
			BL_Cutoff = Vector2( MaxLeft, getMainCamera()->BL.Y );
			Left = MakeInitialPlats( Vector2( MaxLeft - 10, getMainCamera()->BL.Y + 50 ), Vector2(MaxRight, getMainCamera()->TR.Y - 50), Style );
			Sleep();
		}


		// Safety nets
		float SafetyWidth = 300;
		float ExtraSpace = 50;
		float VoidHeight = 0; // How much space to put at the bottom, with no Stage1

		// Make lava
		if ( MySourceGame->HasLava )
		{
			VoidHeight = 40;
			boost::shared_ptr<LavaBlock> lblock = boost::static_pointer_cast<LavaBlock>( getRecycle()->GetObject(ObjectType_LAVA_BLOCK, false) );
			lblock->Init( getMainCamera()->BL.Y + getRnd()->RndFloat(300, 800) + Style->LowerSafetyNetOffset, MaxLeft - 1000, MaxRight + 1000, 5000 );
			lblock->StampAsUsed( 0 );
			AddBlock( lblock );
		}

		// Invert phsx safety blocks
		if ( CurMakeData->TopLikeBottom )
			Stage1SafetyNet( Vector2( MaxLeft - 7500, getMainCamera()->TR.Y - VoidHeight - 215 - Style->LowerSafetyNetOffset + 1000 + Style->UpperSafetyNetOffset ), Vector2(MaxRight + 1500, getMainCamera()->TR.Y - VoidHeight - 65 - Style->LowerSafetyNetOffset + 1000), Vector2(SafetyWidth, 500), 2 * SafetyWidth + ExtraSpace, Style->MyTopType );
		else if ( CurMakeData->TopLikeBottom_Thin )
			Stage1SafetyNet( Vector2( MaxLeft - 7500, getMainCamera()->TR.Y - VoidHeight - 215 - Style->LowerSafetyNetOffset + 1000 + Style->UpperSafetyNetOffset ), Vector2(MaxRight + 1500, getMainCamera()->TR.Y - VoidHeight - 65 - Style->LowerSafetyNetOffset + 1000), Vector2(100, 500), 2 * 150 + 50, Style->MyTopType );

		LastSafetyBlock = Stage1SafetyNet( Vector2( MaxLeft, getMainCamera()->BL.Y + VoidHeight + 65 + Style->LowerSafetyNetOffset ), Vector2(MaxRight + 500, getMainCamera()->BL.Y + VoidHeight + 215 + Style->LowerSafetyNetOffset), Vector2(SafetyWidth, 200 + CurMakeData->PieceSeed->ExtraBlockLength), 2*SafetyWidth + ExtraSpace, Style->MyGroundType );

		Sleep();

		// Final platform
		EndBuffer = 0;
		boost::shared_ptr<MakeThing> MakeFinalPlat = 0;
		if ( CurMakeData->FinalPlats )
		{
			if ( Style->MyFinalPlatsType == StyleData::FinalPlatsType_DOOR )
			{
				if ( DefaultHeroType == BobPhsxRocketbox::getInstance() || boost::dynamic_pointer_cast<BobPhsxSpaceship>(DefaultHeroType) != 0 )
					MakeFinalPlat = boost::make_shared<MakeFinalDoor_Float>( shared_from_this() );
				else
					MakeFinalPlat = boost::make_shared<MakeFinalDoor>( shared_from_this() );
			}
		}

		if ( MakeFinalPlat != 0 )
			MakeFinalPlat->Phase1();

		Sleep();
		Pre1 += L'B';


		// Pre Fill #1
		FillBL = Vector2( Left + Style->SafeStartPadding, getMainCamera()->BL.Y + 150 + VoidHeight );

		Vector2 BL_Bound = Vector2( MaxLeft + 100 + Style->SafeStartPadding, getMainCamera()->BL.Y ); //MainCamera.BLCamBound.Y - 1000);
		Vector2 TR_Bound = Vector2( MaxRight - 400 + Style->SafeEndPadding, getMainCamera()->TR.Y ); // MainCamera.TRCamBound.Y + 1000);

		Fill_BL = Vector2( Left, getMainCamera()->BL.Y + Style->BottomSpace );
		Fill_TR = Vector2( MaxRight + 100, getMainCamera()->TR.Y - Style->TopSpace );
		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::PreFill_1_Gens.begin(); gen != Generators::PreFill_1_Gens.end(); ++gen )
		{
			//gen.PreFill_1(this, BL_Bound, TR_Bound);
			( *gen )->PreFill_1( shared_from_this(), FillBL, TR_Bound );
			Sleep();
		}

		// Change sparsity multiplier
		if ( CurMakeData->SparsityMultiplier == 1 )
			CurMakeData->SparsityMultiplier = CurMakeData->GenData->Get( DifficultyParam_FILL_SPARSITY ) / 100.f;


		// Stage 1 Random fill
		if ( BlockParams->DoStage1Fill )
		{
			BL_Cutoff = Vector2( Left + Style->SafeStartPadding, getMainCamera()->BL.Y );
			Fill_BL = Vector2( Left + Style->SafeStartPadding, getMainCamera()->BL.Y + Style->BottomSpace );
			Fill_TR = Vector2( MaxRight + 100 + Style->SafeEndPadding, getMainCamera()->TR.Y - Style->TopSpace );
			Stage1RndFill( Fill_BL, Fill_TR, BL_Cutoff, 1 * CurMakeData->SparsityMultiplier );

			// Add a row at the very bottom, just to be safe.
			Fill_BL = Vector2( Fill_BL.X, Fill_BL.Y + 35 );
			Fill_TR = Vector2( Fill_TR.X, Fill_BL.Y + 65 );
			Stage1RndFill( Fill_BL, Fill_TR, BL_Cutoff, 1 * CurMakeData->SparsityMultiplier );

			// Add a second row at the very bottom, just to be super safe.
			Fill_BL = Vector2( Fill_BL.X, Fill_BL.Y + 65 );
			Fill_TR = Vector2( Fill_TR.X, Fill_BL.Y + 85 );
			Stage1RndFill( Fill_BL, Fill_TR, BL_Cutoff, 1 * CurMakeData->SparsityMultiplier );

			if ( CurMakeData->TopLikeBottom )
			{
				// Add a row at the very top, just to be safe.
				Fill_BL = Vector2( Fill_BL.X, Fill_TR.Y - 35 );
				Fill_TR = Vector2( Fill_TR.X, Fill_TR.Y - 5 );
				Stage1RndFill( Fill_BL, Fill_TR, BL_Cutoff, 1 * CurMakeData->SparsityMultiplier );
			}
		}

		Pre1 += L'C';
		DEBUGMsg( _T( "Pre stage 1, about to reset" ) );
		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( Format( _T( "Test: %d" ), TestNumber ).c_str() );

		PlayMode = 2;
		RecordPosition = true;

		if ( getPieceSeed()->PreStage1 != 0 )
			getPieceSeed()->PreStage1->Apply( shared_from_this() );
		ResetAll( true );

		DEBUGMsg( _T( "Pre stage 1, about to run through" ) );

		// Set special Bob parameters
		MySourceGame->SetAdditionalBobParameters( Computers );

		CurMakeData->TRBobMoveZone = Vector2( MaxRight + EndBuffer, getMainCamera()->TR.Y + 500 );
		CurMakeData->BLBobMoveZone = Vector2( MaxLeft, getMainCamera()->BL.Y - 500 );
		if ( ReturnEarly == 1 )
			return false;

		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( Format( _T( "Test a: %d" ), TestNumber ).c_str() );

		// Stage 1 Run through
		Pre1 += L'D';
		Stage1( BL_Bound, TR_Bound, Length );
		Pre2 += L'A';

		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( Format( _T( "Test b: %d" ), TestNumber ).c_str() );

		// Continue making Final Platform
		if ( MakeFinalPlat != 0 )
			MakeFinalPlat->Phase2();

		// Update the level's par time
		CurPiece->Par = LastStep;
		Par += CurPiece->Par;

		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( Format( _T( "Test c: %d" ), TestNumber ).c_str() );

		DEBUGMsg( _T( "Done with stage 1 run through, about to cleanup" ) );

		// Stage 1 Cleanup
		Stage1Cleanup( BL_Bound, TR_Bound );
		Pre2 += L'B';

		CurPiece->PieceLength = LastStep - StartPhsxStep;


		DEBUGMsg( _T( "Pre stage 2, about to fill" ) );


		// Pre Fill #2
		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::PreFill_2_Gens.begin(); gen != Generators::PreFill_2_Gens.end(); ++gen )
		{
			//gen.PreFill_2(this, BL_Bound, TR_Bound);
			( *gen )->PreFill_2( shared_from_this(), FillBL, TR_Bound );
			Sleep();
		}


		FinalizeBlocks();

		Pre2 += L'C';
		DEBUGMsg( _T( "Pre stage 2, about to reset" ) );
		TestNumber = getRnd()->RndInt(0, 1000);
		Tools::Write( Format( _T( "Test d: %d" ), TestNumber ).c_str() );

		PlayMode = 1;
		RecordPosition = false;
		if ( getPieceSeed()->PreStage2 != 0 )
			getPieceSeed()->PreStage2->Apply( shared_from_this() );
		ResetAll( true );
		Sleep();

		MySourceGame->SetAdditionalBobParameters( Computers );

		if ( ReturnEarly == 2 )
			return false;

		DEBUGMsg( _T( "Pre stage 2, about to run through" ) );
		Pre2 += L'D';

		// Stage 2 Run through
		Stage2();
		Post += L'A';

		DEBUGMsg( _T( "Done with stage 2 run through, about to cleanup" ) );
		showdebug = true;

		// Stage 2 Cleanup
		Stage2Cleanup( BL_Bound, TR_Bound );
		Post += L'B';

		//Recycle.Empty();

		// Finish making Final Platform
		if ( MakeFinalPlat != 0 )
		{
			MakeFinalPlat->Phase3();
			MakeFinalPlat->Cleanup();
		}

		// Door properties
		boost::shared_ptr<Door> door = boost::static_pointer_cast<Door>( FindIObject( LevelConnector::EndOfLevelCode ) );
		if ( 0 != door )
			door->AutoOpen = Style->AutoOpenDoor;

		return false;
	}

	void Level::Stage1( Vector2 BL_Bound, Vector2 TR_Bound, int Length )
	{
		int OneFinishedCount = 0; // Number of frames since at least one player finished
		int AdditionalSteps = 10; // Steps to take after computer reaches end
		while ( CurPhsxStep - Bobs[ 0 ]->IndexOffset < Length )
		{
			Step1 = CurPhsxStep;

			// Do the above without delegates
			bool Any;
			Any = false;
			for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
				if ( ( *bob )->getCore()->Data.Position.X < MaxRight + EndBuffer )
					Any = true;
			if ( !Any )
				OneFinishedCount += 8;
			Any = false;
			for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
				if ( ( *bob )->getCore()->Data.Position.X > MaxRight + EndBuffer - 100 )
					Any = true;
			if ( Any )
				OneFinishedCount++;


			if ( OneFinishedCount > AdditionalSteps )
				break;

			PhsxStep( true );
			for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::ActiveFill_1_Gens.begin(); gen != Generators::ActiveFill_1_Gens.end(); ++gen )
				( *gen )->ActiveFill_1( shared_from_this(), FillBL, TR_Bound );
		}
		LastStep = CurPhsxStep;
	}

	void Level::Stage1Cleanup( Vector2 BL_Bound, Vector2 TR_Bound )
	{
		boost::shared_ptr<SingleData> Style = boost::static_pointer_cast<SingleData>( CurMakeData->PieceSeed->Style );

		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::Gens.begin(); gen != Generators::Gens.end(); ++gen )
			( *gen )->Cleanup_1( shared_from_this(), BL_Bound, TR_Bound );

		// Overlapping blocks
		if ( Style->RemovedUnusedOverlappingBlocks )
			BlockOverlapCleanup();
		Sleep();

		// Remove unused objects
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( !( *obj )->getCore()->GenData.Used && (*obj)->getCore()->GenData.RemoveIfUnused )
				getRecycle()->CollectObject(*obj);
		CleanObjectList();
		Sleep();

		// Remove unused blocks
		for ( BlockVec::const_iterator _block = Blocks.begin(); _block != Blocks.end(); ++_block )
			if ( !( *_block )->getCore()->GenData.Used && (*_block)->getCore()->GenData.RemoveIfUnused )
				getRecycle()->CollectObject(*_block);
		CleanBlockList();
		CleanDrawLayers();
		Sleep();
	}

	void Level::Stage2()
	{
		while ( CurPhsxStep < LastStep )
		{
			Step2 = CurPhsxStep;
			PhsxStep( true );
		}
	}

	void Level::Stage2Cleanup( Vector2 BL_Bound, Vector2 TR_Bound )
	{
		OverlapCleanup();
		CleanAllObjectLists();
		Sleep();

		// Limit general density of all obstacles.
		ObjectVec ObjsToClean = ObjectVec();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( ( *obj )->getCore()->GenData.LimitGeneralDensity )
				ObjsToClean.push_back( *obj );

		Cleanup( ObjsToClean, boost::make_shared<GeneralMinDistLambda>( shared_from_this() ), true, BL_Bound, TR_Bound );
		Sleep();

		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
		{
			boost::shared_ptr<Coin> coin = boost::dynamic_pointer_cast<Coin>( *obj );
			if ( 0 != coin )
				if ( coin->getCore()->AddedTimeStamp > LastStep )
					getRecycle()->CollectObject(coin);
		}

		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::Gens.begin(); gen != Generators::Gens.end(); ++gen )
			( *gen )->Cleanup_2( shared_from_this(), BL_Bound, TR_Bound );

		// Clean up deleted objects
		CleanAllObjectLists();
	}

	void Level::OverlapCleanup()
	{
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
		{
			if ( ( *obj )->getCore()->GenData.NoBlockOverlap )
			{
				for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
				{
					if ( ( *block )->getBlockCore()->RemoveOverlappingObjects && *block != (*obj)->getCore()->ParentBlock && Phsx::PointAndAABoxCollisionTest((*obj)->getCore()->Data.Position, (*block)->getBox(), (*obj)->getCore()->GenData.OverlapWidth) )
						getRecycle()->CollectObject(*obj);
				}
			}
		}
	}

	void Level::BlockOverlapCleanup()
	{
		if ( getStyle()->OverlapCleanupType == StyleData::_OverlapCleanupType_REGULAR )
			RegularBlockCleanup();
		else
			SpaceshipBlockCleanup();
	}

	void Level::SpaceshipBlockCleanup()
	{
		for ( BlockVec::const_iterator block2 = Blocks.begin(); block2 != Blocks.end(); ++block2 )
		{
			if ( ( *block2 )->getCore()->MarkedForDeletion )
				continue;

			for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			{
				if ( ( *block2 )->getCore()->MarkedForDeletion )
					break;
				if ( ( *block )->getCore()->GenData.Used || (*block)->getCore()->MarkedForDeletion )
					continue;

				if ( *block != *block2 && ( *block )->getCore()->GenData.RemoveIfOverlap && (*block2)->getCore()->GenData.RemoveIfOverlap && (((*block)->getCore()->Data.Position - (*block2)->getCore()->Data.Position).Length() < CurMakeData->PieceSeed->Style->MinBlockDist || Phsx::BoxBoxOverlap((*block)->getBox(), (*block2)->getBox())) )
				{
					switch ( ( *block )->getCore()->GenData.MyOverlapPreference )
					{
						case GenerationData::OverlapPreference_REMOVE_HIGHER_THAN_ME:
							if ( ( *block2 )->getBox()->Target->TR.Y > (*block)->getBox()->Target->TR.Y )
								getRecycle()->CollectObject(*block2);
							else
								getRecycle()->CollectObject(*block);
							break;

						case GenerationData::OverlapPreference_REMOVE_LOWER_THAN_ME:
							if ( ( *block2 )->getBox()->Target->TR.Y > (*block)->getBox()->Target->TR.Y )
								getRecycle()->CollectObject(*block);
							else
								getRecycle()->CollectObject(*block2);
							break;

						case GenerationData::OverlapPreference_REMOVE_RANDOM:
							if ( getRnd()->RndBool() )
								getRecycle()->CollectObject(*block2);
							else
								getRecycle()->CollectObject(*block);
							break;
					}
				}
			}
		}
	}

	void Level::RegularBlockCleanup()
	{
		for ( BlockVec::const_iterator block2 = Blocks.begin(); block2 != Blocks.end(); ++block2 )
		{
			if ( ( *block2 )->getCore()->MarkedForDeletion )
				continue;

			for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			{
				if ( ( *block )->getCore()->GenData.Used || (*block)->getCore()->MarkedForDeletion )
					continue;

				if ( *block != *block2 && ( *block )->getCore()->GenData.RemoveIfOverlap && (((*block)->getCore()->Data.Position - (*block2)->getCore()->Data.Position).Length() < CurMakeData->PieceSeed->Style->MinBlockDist || Phsx::BoxBoxOverlap((*block)->getBox(), (*block2)->getBox())) )
				{
					getRecycle()->CollectObject(*block);
				}
			}
		}
	}

	void Level::InitMakeData( const boost::shared_ptr<MakeData> &makeData )
	{
		boost::shared_ptr<PieceSeedData> Piece = makeData->PieceSeed;

		makeData->Init( Piece );

		switch ( makeData->PieceSeed->Paths )
		{
			case 1:
				makeData->PieceSeed->Style->SetSinglePathType( makeData, shared_from_this(), Piece );

				break;

			case 2:
				makeData->PieceSeed->Style->SetDoubePathType( makeData, shared_from_this(), Piece );

				break;

			case 3:
				makeData->PieceSeed->Style->SetTriplePathType( makeData, shared_from_this(), Piece );

				break;
		}


		if ( makeData->Index == 0 )
		{
			makeData->InitialPlats = true;
			makeData->InitialCamZone = true;
		}
		else
		{
			makeData->InitialPlats = false;
			makeData->InitialCamZone = false;
		}

		if ( makeData->Index == makeData->OutOf - 1 )
			makeData->FinalPlats = true;
		else
		{
			makeData->FinalPlats = false;
		}

		makeData->CamStartPos = getMainCamera()->Data.Position;
	}

	const boost::shared_ptr<Recycler> Level::getRecycle() const
	{
		if ( MySourceGame != 0 && !MySourceGame->Released )
			return MySourceGame->Recycle;
		else if ( MyGame != 0 && !MyGame->Released )
			return MyGame->Recycle;
		else
			Tools::Break();

		return 0;
	}

	const boost::shared_ptr<Rand> &Level::getRnd()
	{
		if ( MyLevelSeed == 0 )
		{
			if ( _PrivateRnd == 0 )
				_PrivateRnd = boost::make_shared<Rand>( 0 );
			return _PrivateRnd;
		}
		else
			return MyLevelSeed->Rnd;
	}

	bool Level::WatchComputerEnabled()
	{
		return CanWatchComputer && CanWatchComputerFromAfar_External;
	}

	void Level::CountReset()
	{
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
		{
			if ( !( *bob )->Dead && !( *bob )->Dying )
			{
				( *bob )->getMyStats()->DeathsBy[ BobDeathType_OTHER ]++;
				( *bob )->getMyStats()->DeathsBy[ BobDeathType_TOTAL ]++;
			}
		}
	}

	bool Level::CloseToStart()
	{
		if ( Bobs.empty() )
			return true;

		return Tools::All<boost::shared_ptr<Bob> >( Bobs, boost::make_shared<CloseToStartLambda>() );
	}

	const bool &Level::getPreventReset() const
	{
		return _PreventReset;
	}

	void Level::setPreventReset( const bool &value )
	{
		_PreventReset = value;
	}

	bool Level::ResetEnabled()
	{
		return !getPreventReset();
	}

	void Level::PushLava( float y )
	{
		boost::shared_ptr<BlockBase> lava = Tools::Find<boost::shared_ptr<BlockBase> >( Blocks, boost::make_shared<IsLavaLambda>() );

		if ( 0 != lava )
			PushLava( y, boost::dynamic_pointer_cast<LavaBlock>( lava ) );
	}

	void Level::PushLava( float y, const boost::shared_ptr<LavaBlock> &lava )
	{
		float newtop = __min( lava->getBox()->Current->TR.Y, y );
		float shift = newtop - lava->getBox()->Current->TR.Y;
		lava->Move( Vector2( 0, shift ) );
	}

	void Level::CheckTimeLimit()
	{
		if ( !HaveTimeLimit || PlayMode != 0 || Watching || Replay || PlayerManager::AllDead() )
			return;

		if ( CurPhsxStep == TimeLimit - TimeLimitTimerLength )
			MyGame->AddGameObject( MakeMagic( GUI_Timer_Simple, ( TimeLimitTimerLength ) ) );
	}

	const boost::shared_ptr<TileSet> &Level::getMyTileSetInfo() const
	{
		return MyTileSet;
	}

	const boost::shared_ptr<TileSetInfo> &Level::getInfo() const
	{
		return MyTileSet->MyTileSetInfo;
	}

	const bool &Level::getSetToReset() const
	{
		return _SetToReset;
	}

	void Level::setSetToReset( const bool &value )
	{
		_SetToReset = value;
	}

int Level::NumDrawLayers = 12 + 1;
int Level::AfterParticlesDrawLayer = 10;
int Level::LastInLevelDrawLayer = 10;
int Level::AfterPostDrawLayer = 12;

	const boost::shared_ptr<Camera> &Level::getMainCamera() const
	{
		return MyCamera;
	}

	void Level::setMainCamera( const boost::shared_ptr<Camera> &value )
	{
		MyCamera = value;
		MyCamera->MyLevel = shared_from_this();
		if ( OnCameraChange != 0 )
			OnCameraChange->Apply();
	}

	Level::Level()
	{
		InitializeInstanceFields();
		Init( false );
	}

	Level::Level( bool ShowParticles )
	{
		InitializeInstanceFields();
		Init( ShowParticles );
	}

	void Level::Init( bool NoParticles )
	{
		this->NoParticles = NoParticles;
		MyTileSet = TileSets::TileList[ 0 ];

		CanWatchComputer = CanWatchReplay = false;

		LevelPieces = std::vector<boost::shared_ptr<LevelPiece> >();

		if ( !NoParticles )
			MainEmitter = ParticleEmitter::Pool->Get();

		Blocks.reserve( 2000 );

		Objects.reserve( 2000 );
		AddedObjects.reserve( 1000 );
		ObjectsLocked = false;

		CreateActiveObjectList();

		ShowDrawLayer = std::vector<bool>( NumDrawLayers );
		for ( int i = 0; i < NumDrawLayers; i++ )
		{
			ShowDrawLayer[ i ] = true;
			DrawLayer[ i ].reserve( 300 );
			if ( !NoParticles )
				ParticleEmitters[ i ] = ParticleEmitter::Pool->Get();
					//new ParticleEmitter(100);
		}


		Bobs = BobVec();
		HoldPlayerBobs = BobVec();

		setSetToReset( false );
	}

	void Level::Release()
	{
		if ( LevelReleased )
			return;

		if ( CurMakeData != 0 )
			CurMakeData->Release();

		LevelReleased = true;

		MyGame.reset();
		MyLevelSeed.reset();
		MyReplayGUI.reset();

		OnWatchComputer.reset();
		OnEndReplay.reset();

		if ( MySwarmBundle != 0 )
			MySwarmBundle->Release();

		if ( LevelPieces.size() > 0 )
			for ( std::vector<boost::shared_ptr<LevelPiece> >::const_iterator piece = LevelPieces.begin(); piece != LevelPieces.end(); ++piece )
				( *piece )->Release();
		LevelPieces.clear();
		CurPiece.reset();

		MyBackground.reset();

		if ( MainEmitter != 0 )
		{
			MainEmitter->Release();
			MainEmitter.reset();
		}
		if ( ParticleEmitters.size() > 0 )
			for ( std::vector<boost::shared_ptr<ParticleEmitter> >::const_iterator emitter = ParticleEmitters.begin(); emitter != ParticleEmitters.end(); ++emitter )
				if ( *emitter != 0 )
					( *emitter )->Release();
		ParticleEmitters.clear();

		if ( CurrentRecording != 0 )
		{
			CurrentRecording->Release();
			CurrentRecording.reset();
		}

		CurrentRecording.reset();
		HoldPlayerBobs.clear();
		LevelPieces.clear();
		MySwarmBundle.reset();

		if ( Blocks.size() > 0 )
			for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
				( *block )->Release();
		Blocks.clear();

		if ( Objects.size() > 0 )
			for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			{
				( *obj )->getCore()->MyLevel.reset();
				( *obj )->Release();
			}
		ActiveObjectList.clear();
		Objects.clear();

		if ( Bobs.size() > 0 )
			for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
				( *bob )->Release();
		Bobs.clear();
		DefaultHeroType.reset();

		DrawLayer.clear();

		LevelPieces.clear();
		AddedObjects.clear();
		AddedBlocks.clear();
		HoldPlayerBobs.clear();

		MyGame = MySourceGame = 0;

		if ( MyCamera != 0 )
			MyCamera->Release();
			MyCamera.reset();
		if ( HoldCamera != 0 )
			HoldCamera->Release();
			HoldCamera.reset();
		OnCameraChange.reset();
	}

	const boost::shared_ptr<Door> Level::getFinalDoor() const
	{
		return boost::static_pointer_cast<Door>( FindIObject( LevelConnector::EndOfLevelCode ) );
	}

	const boost::shared_ptr<Door> Level::getStartDoor() const
	{
		return boost::static_pointer_cast<Door>( FindIObject( LevelConnector::StartOfLevelCode ) );
	}

	const boost::shared_ptr<ObjectBase> Level::FindIObject( const std::wstring &Code1 ) const
	{
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( CompareIgnoreCase( ( *obj )->getCore()->EditorCode1, Code1 ) == 0 )
				return *obj;

		return 0;
	}

	int Level::GetPhsxStep()
	{
		return CurPhsxStep + 1;
	}

	float Level::GetIndependentPhsxStep()
	{
		return IndependentPhsxStep + 1;
	}

	std::wstring Level::DefaultLevelDirectory()
	{
		return Path::Combine( Globals::ContentDirectory, _T( "Levels" ) );
	}

	std::wstring Level::SourceLevelDirectory()
	{
		return Path::Combine( Path::GetDirectoryName( Path::GetDirectoryName( Path::GetDirectoryName( Directory::GetCurrentDirectory() ) ) ), _T("Content/Levels") );
	}

	void Level::Save( const std::wstring &file, bool Bin )
	{
		// First move to standard directory for .lvl files
		std::wstring fullpath;
		if ( Bin )
			fullpath = Path::Combine( DefaultLevelDirectory(), file );
		else
			fullpath = Path::Combine( SourceLevelDirectory(), file );

		// Now write to file
		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( fullpath, FileMode::Create, FileAccess::Write, FileShare::None );
		//boost::shared_ptr<BinaryWriter> writer = boost::make_shared<BinaryWriter>( stream, Encoding::UTF8 );
		{
			boost::shared_ptr<BinaryWriter> writer = boost::make_shared<BinaryWriter>( fullpath );
			Tools::CurLevel->Write( writer );
		}
		//writer->Close();
		//stream->Close();
	}

	int Level::DrawLayerSortFunc( const boost::shared_ptr<ObjectBase> &A, const boost::shared_ptr<ObjectBase> &B )
	{
		return Compare( A->getCore()->DrawSubLayer, B->getCore()->DrawSubLayer );
	}

	void Level::SortDrawLayers()
	{
		for ( int i = 0; i < NumDrawLayers; i++ )
			//DrawLayer[ i ].Sort( DrawLayerSortFunc );
			Sort( DrawLayer[ i ], DrawLayerSortFunc );
	}

	void Level::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		// Save sub draw layers
		for ( int i = 0; i < NumDrawLayers; i++ )
		{
			for ( int j = 0; j < static_cast<int>( DrawLayer[ i ].size() ); j++ )
				DrawLayer[ i ][ j ]->getCore()->DrawSubLayer = j;
		}

		// count number of blocks to save
		int Num = 0;
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			if ( ( *block )->getCore()->EditHoldable )
				Num++;

		// record the number
		writer->Write( Num );

		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
		{
			if ( ( *block )->getCore()->EditHoldable )
			{
				writer->Write( static_cast<int>( ( *block )->getCore()->MyType ) );
				( *block )->Write( writer );
			}
		}

		// count number of objects to save
		Num = 0;
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( ( *obj )->getCore()->EditHoldable )
				Num++;

		// record the number
		writer->Write( Num );

		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
		{
			if ( ( *obj )->getCore()->EditHoldable )
			{
				writer->Write( static_cast<int>( ( *obj )->getCore()->MyType ) );
				( *obj )->Write( writer );
			}
		}
	}

	void Level::Move( Vector2 shift )
	{
		Move( shift, true );
	}

	void Level::Move( Vector2 shift, bool MoveBackground )
	{
		getMainCamera()->Move(shift);

		for ( std::vector<boost::shared_ptr<LevelPiece> >::const_iterator piece = LevelPieces.begin(); piece != LevelPieces.end(); ++piece )
		{
			for ( int i = 0; i < (*piece)->NumBobs; i++ )
				( *piece )->StartData[ i ].Position += shift;
			( *piece )->LastPoint += shift;
			( *piece )->CamStartPos += shift;
			( *piece )->Shift( shift );
		}

		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			( *block )->Move( shift );

		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			( *obj )->Move( shift );

		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
			( *bob )->Move( shift );

		if ( MoveBackground && MyBackground != 0 )
			MyBackground->Move( shift );
	}

	void Level::KeepCoinsDead()
	{
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
		{
			boost::shared_ptr<Coin> coin = boost::dynamic_pointer_cast<Coin>( *obj );
			if ( 0 != coin )
			{
				if ( !coin->getCore()->Active )
					getRecycle()->CollectObject(coin);
			}
		}
	}

	void Level::StopRecording()
	{
		Recording_Renamed = false;
		if ( CurrentRecording != 0 )
			CurrentRecording->MarkEnd( shared_from_this() );
	}

	void Level::PrepareBundleToAddRecording()
	{
		if ( MySwarmBundle == 0 )
			MySwarmBundle = boost::make_shared<SwarmBundle>();

		if ( MySwarmBundle->CurrentSwarm == 0 )
		{
			MySwarmBundle->StartNewSwarm();
			MySwarmBundle->CurrentSwarm->MyLevelPiece = CurPiece;
		}
	}

	void Level::AddCurRecording()
	{
		PrepareBundleToAddRecording();

		if ( CurrentRecording != 0 )
			MySwarmBundle->CurrentSwarm->AddRecord( CurrentRecording, CurPhsxStep );
	}

	void Level::CleanRecording()
	{
		if ( MySwarmBundle != 0 )
			MySwarmBundle->Release();
			MySwarmBundle.reset();
		if ( CurrentRecording != 0 )
		{
			CurrentRecording->Release();
			CurrentRecording.reset();
		}
	}

	void Level::StartRecording()
	{
		if ( !AllowRecording || Watching || Replay )
			return;

		PrepareBundleToAddRecording();

		if ( CurrentRecording != 0 )
			MySwarmBundle->CurrentSwarm->AddRecord( CurrentRecording, CurPhsxStep );

		if ( MySwarmBundle->CurrentSwarm->MyLevelPiece != CurPiece )
		{
			MySwarmBundle->StartNewSwarm();
			MySwarmBundle->CurrentSwarm->MyLevelPiece = CurPiece;
		}

		Recording_Renamed = true;
		CurrentRecording = boost::make_shared<Recording>( Bobs.size(), 8000 );
	}

	boost::shared_ptr<ObjectBase> Level::GuidToObj( unsigned long long guid )
	{
		boost::shared_ptr<ObjectBase> obj = LookupGUID( guid );
		if ( obj != 0 && obj->getCore()->MarkedForDeletion )
			return 0;
		else
			return obj;
	}

	ObjectVec Level::GuidToObj( std::vector<unsigned long long> &guids )
	{
		ObjectVec list = ObjectVec();
		for ( std::vector<unsigned long long>::const_iterator guid = guids.begin(); guid != guids.end(); ++guid )
			list.push_back( GuidToObj( *guid ) );
		return list;
	}

	boost::shared_ptr<ObjectBase> Level::LookupGUID( unsigned long long guid )
	{
		boost::shared_ptr<ObjectBase> FoundObj = Tools::Find<boost::shared_ptr<ObjectBase> >( Objects, boost::make_shared<FindGuidLambda>( guid ) );
		if ( FoundObj != 0 )
			return FoundObj;

		return 0;
	}

	void Level::SetCurrentPiece( int LevelPieceIndex )
	{
		SetCurrentPiece( LevelPieces[ LevelPieceIndex ] );
	}

	void Level::SetCurrentPiece( const boost::shared_ptr<LevelPiece> &piece )
	{
		CurPiece = piece;

		// Change piece associated with each bob
		int Count = 0;
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
		{
			( *bob )->MyPiece = piece;
			( *bob )->MyPieceIndex = Count % piece->NumBobs;

			Count++;
		}
	}

	void Level::NonLambdaReset()
	{
	}

	void Level::ResetAll( bool BoxesOnly )
	{
		ResetAll( BoxesOnly, true );
	}

	void Level::ResetAll( bool BoxesOnly, bool AdditionalReset )
	{
		if ( BoxesOnly )
			Reset_BoxesOnly( AdditionalReset );
		else
			Reset_Graphical( AdditionalReset );
	}

	void Level::Reset_BoxesOnly( bool AdditionalReset )
	{
		__Reset( true, AdditionalReset );
	}

	void Level::Reset_Graphical( bool AdditionalReset )
	{
		__Reset( false, AdditionalReset );
	}

	void Level::__Reset( bool BoxesOnly, bool AdditionalReset )
	{
		this->BoxesOnly = BoxesOnly;
		NonLambdaReset();

		if ( MyGame != 0 )
			MyGame->FreeReset = FreeReset;
		FreeReset = false;

		// Clean up the particle emitters
		if ( !NoParticles )
		{
			if ( MainEmitter != 0 )
				MainEmitter->Clean();
			if ( ParticleEmitters.size() > 0 )
				for ( std::vector<boost::shared_ptr<ParticleEmitter> >::const_iterator emitter = ParticleEmitters.begin(); emitter != ParticleEmitters.end(); ++emitter )
					if ( *emitter != 0 )
						( *emitter )->Clean();
		}

		CleanAllObjectLists();

		// Check to see if this reset was from the player's all dying/failing.
		if ( PlayMode == 0 && !Watching )
		{
			// The player's all died, so increment the number of attempts made on the level.
			PieceAttempts++;
			NumAttempts++;

			// Activate the game's retry event
			if ( MyGame != 0 )
				MyGame->LevelRetryEvent();
		}

		getMainCamera()->MyZone.reset();
		if ( getMainCamera()->Shaking )
			getMainCamera()->EndShake();
		getMainCamera()->Data.Position = CurPiece->CamStartPos;
		getMainCamera()->ZoneLocked = false;
		getMainCamera()->Update();

		CurPhsxStep = StartPhsxStep = CurPiece->StartPhsxStep;
		IndependentStepSetOnce = false;

		// Save sub draw layers
		for ( int i = 0; i < NumDrawLayers; i++ )
		{
			for ( int j = 0; j < static_cast<int>( DrawLayer[ i ].size() ); j++ )
			{
				boost::shared_ptr<ObjectData> Core = DrawLayer[ i ][ j ]->getCore();
				if ( !Core->FixSubLayer )
					Core->DrawSubLayer = j;
			}
		}

		// Reset Bobs
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
		{
			PhsxData StartData;
			if ( ( *bob )->MyPiece != 0 )
			{
				StartData = ( *bob )->MyPiece->StartData[ ( *bob )->MyPieceIndex ];
				StartData.Position.X += 20 * ( *bob )->MyPieceIndexOffset;
			}
			else
				StartData = CurPiece->StartData[ 0 ];
			if ( MyGame != 0 )
				( *bob )->Init( BoxesOnly, StartData, MyGame );
			else
				( *bob )->Init( BoxesOnly, StartData, MySourceGame );

			// Start Bob's box off as tiny, so we can properly collide with ground if the start position is slightly off.
			( *bob )->Box->Current->Size = Vector2(1);
			( *bob )->Box->Target->Size = Vector2(1);
			( *bob )->Box->Current->CalcBounds();
			( *bob )->Box->Target->CalcBounds();
			( *bob )->Box->CalcBounds();

			( *bob )->PlayerObject->BoxesOnly = BoxesOnly;
			( *bob )->BoxesOnly = BoxesOnly;
		}

		// Clean blocks
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			if ( ( *block )->getCore()->RemoveOnReset )
				getRecycle()->CollectObject(*block);
		CleanBlockList();

		// Reset blocks
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
		{
			( *block )->Reset( BoxesOnly );
			if ( ( *block )->getBlockCore()->Objects.size() > 0 )
				( *block )->getBlockCore()->Objects.clear();
		}

		// Clean objects
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( ( *obj )->getCore()->RemoveOnReset )
				getRecycle()->CollectObject(*obj);
		CleanAllObjectLists();
		ObjectVec NewObjects = ObjectVec();

		// Reset objects
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
		{
			( *obj )->Reset( BoxesOnly );
			boost::shared_ptr<ObjectBase> NewObj;
			if ( ( *obj )->getCore()->ResetOnlyOnReset )
				NewObj = *obj;
			else
			{
				NewObj = getRecycle()->GetObject((*obj)->getCore()->MyType, BoxesOnly);
				NewObj->Clone( *obj );
				NewObj->getCore()->BoxesOnly = BoxesOnly;

				( *obj )->getCore()->GenData.OnMarkedForDeletion.reset();
				getRecycle()->CollectObject(*obj, false);
			}
			NewObjects.push_back( NewObj );
		}

		// Recover correct object pointers from GUIDs
		for ( ObjectVec::const_iterator obj = NewObjects.begin(); obj != NewObjects.end(); ++obj )
		{
			if ( ( *obj )->getCore()->ParentObject != 0 )
			{
				boost::shared_ptr<ObjectBase> parent = FindParentObjectById( NewObjects, *obj );

				( *obj )->getCore()->ParentObject = parent;
			}
		}

		// Re-add all objects 
		ClearAllObjectLists();
		for ( ObjectVec::const_iterator obj = NewObjects.begin(); obj != NewObjects.end(); ++obj )
			AddObject( *obj, false );
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			ReAddObject( *block );

		SortDrawLayers();

		// Create new active object list
		CreateActiveObjectList();

		// Reset camera
		getMainCamera()->Target = getMainCamera()->Data.Position = CurPiece->CamStartPos;

		// Reset game
		if ( AdditionalReset && MyGame != 0 )
			MyGame->AdditionalReset();

		// Start recording (for player replays)
		if ( PlayMode == 0 && !Watching && Recording_Renamed )
			CurrentRecording->Record( shared_from_this() );

		// Burn a few phsx steps
		if ( PlayMode != 0 )
			for ( int i = 0; i < CurPiece->DelayStart; i++ )
				PhsxStep( false );
		else
		{
			PhsxStep( false, false );
		}
	}

	boost::shared_ptr<ObjectBase> Level::FindParentObjectById( ObjectVec &ObjectList, const boost::shared_ptr<ObjectBase> &obj )
	{
		boost::shared_ptr<ObjectBase> FoundObj = Tools::Find<boost::shared_ptr<ObjectBase> >( ObjectList, boost::make_shared<FindGuidLambda>( obj->getCore()->ParentObjId ) );

		return FoundObj;
	}

	void Level::SynchObject( const boost::shared_ptr<ObjectBase> &obj )
	{
		if ( obj->getCore()->MyLevel == 0 )
			obj->getCore()->StepOffset = 0;
		else
			obj->getCore()->StepOffset = obj->getCore()->MyLevel->GetPhsxStep() - GetPhsxStep();
	}

	void Level::MoveUpOneSublayer( const boost::shared_ptr<ObjectBase> &obj )
	{
		/*int i = DrawLayer[ obj->getCore()->DrawLayer ].find( obj ) + 1;*/
		int i = IndexOf( DrawLayer[ obj->getCore()->DrawLayer ] , obj ) + 1;
		int N = static_cast<int>( DrawLayer[ obj->getCore()->DrawLayer ].size() );
		if ( i >= N )
			i = N - 1;
		Remove( DrawLayer[ obj->getCore()->DrawLayer ], obj );
		Insert( DrawLayer[ obj->getCore()->DrawLayer ], i, obj);
	}

	void Level::MoveToTopOfDrawLayer( const boost::shared_ptr<ObjectBase> &obj )
	{
		int i = IndexOf( DrawLayer[ obj->getCore()->DrawLayer ], obj );
		int N = static_cast<int>( DrawLayer[ obj->getCore()->DrawLayer ].size() );
		if ( i == N - 1 )
			return;

		Remove( DrawLayer[ obj->getCore()->DrawLayer ], obj );
		Insert( DrawLayer[ obj->getCore()->DrawLayer ], N - 1, obj );
	}

	void Level::MoveDownOneSublayer( const boost::shared_ptr<ObjectBase> &obj )
	{
		int i = IndexOf( DrawLayer[ obj->getCore()->DrawLayer ], obj ) - 1;
		int N = static_cast<int>( DrawLayer[ obj->getCore()->DrawLayer ].size() );
		if ( i < 0 )
			i = 0;
		Remove( DrawLayer[ obj->getCore()->DrawLayer ], obj );
		Insert( DrawLayer[ obj->getCore()->DrawLayer ], i, obj );
	}

	void Level::ChangeObjectDrawLayer( const boost::shared_ptr<ObjectBase> &obj, int DestinationLayer )
	{
		if ( obj->getCore()->DrawLayer == DestinationLayer )
			return;

		Remove( DrawLayer[ obj->getCore()->DrawLayer ], obj );
		DrawLayer[ DestinationLayer ].push_back( obj );
		obj->getCore()->DrawLayer = DestinationLayer;
	}

	void Level::RelayerObject( const boost::shared_ptr<ObjectBase> &Obj, int NewLayer, bool Front )
	{
		Remove( DrawLayer[ Obj->getCore()->DrawLayer ], Obj );

		if ( Front )
			Insert( DrawLayer[ NewLayer ], DrawLayer[ NewLayer ].size(), Obj );
		else
			Insert( DrawLayer[ NewLayer ], 0, Obj );

		Obj->getCore()->DrawLayer = NewLayer;
	}

	void Level::AddObject( const boost::shared_ptr<ObjectBase> &NewObject )
	{
		AddObject( NewObject, true );
	}

	void Level::AddObject( const boost::shared_ptr<ObjectBase> &NewObject, bool AddTimeStamp )
	{
		if ( AddTimeStamp )
			NewObject->getCore()->AddedTimeStamp = CurPhsxStep;

		SynchObject( NewObject );
		NewObject->getCore()->MyLevel = shared_from_this();

		if ( NewObject->getCore()->DrawLayer >= 0 )
		{
			if ( NewObject->getCore()->ParentBlock == 0 || boost::dynamic_pointer_cast<NormalBlock>(NewObject->getCore()->ParentBlock) != 0 || NewObject->getCore()->DoNotDrawWithParent )
			{
				DrawLayer[ NewObject->getCore()->DrawLayer ].push_back(NewObject);
			}
			else
				NewObject->getCore()->ParentBlock->getBlockCore()->Objects.push_back(NewObject);
		}

		// Add object a second time if it needs to be drawn twice (two different draw layers, for instance)
		if ( NewObject->getCore()->DrawLayer2 > 0 )
			DrawLayer[ NewObject->getCore()->DrawLayer2 ].push_back(NewObject);
		if ( NewObject->getCore()->DrawLayer3 > 0 )
			DrawLayer[ NewObject->getCore()->DrawLayer3 ].push_back(NewObject);

		if ( ObjectsLocked )
		{
			AddedObjects.push_back( NewObject );
		}
		else
		{
			Objects.push_back( NewObject );
			if ( Objects != ActiveObjectList )
			{
				ActiveObjectList.push_back( NewObject );
			}
		}
	}

	void Level::ReAddObject( const boost::shared_ptr<ObjectBase> &NewObject )
	{
		//AllObjects.Add(NewObject, true);
		DrawLayer[ NewObject->getCore()->DrawLayer ].push_back(NewObject);

		if ( NewObject->getCore()->DrawLayer2 > 0 )
			DrawLayer[ NewObject->getCore()->DrawLayer2 ].push_back(NewObject);
		if ( NewObject->getCore()->DrawLayer3 > 0 )
			DrawLayer[ NewObject->getCore()->DrawLayer3 ].push_back(NewObject);
	}

	void Level::EmptyPreRecycleBin()
	{
		for ( ObjectVec::const_iterator obj = PreRecycleBin.begin(); obj != PreRecycleBin.end(); ++obj )
		{
			//if (obj is MovingPlatform && ((MovingPlatform)obj).Parent != null) Tools.Write("!");
			( *obj )->getCore()->MarkedForDeletion = false;
			( *obj )->getCore()->MyLevel.reset();
			getRecycle()->CollectObject(*obj);
		}

		PreRecycleBin.clear();
	}

	void Level::CleanAllObjectLists()
	{
		EmptyPreRecycleBin();

		CleanObjectList();
		CleanBlockList();

		//if (!BoxesOnly)
		CleanDrawLayers();
	}

	void Level::ClearAllObjectLists()
	{
		//AllObjects.Clear();
		Objects.clear();
		for ( int i = 0; i < NumDrawLayers; i++ )
			DrawLayer[ i ].clear();
	}

	void Level::CleanObjectList()
	{
		Tools::RemoveAll<boost::shared_ptr<ObjectBase> >( Objects, boost::make_shared<CleanObjectListLambda>() );
	}

	void Level::CleanDrawLayers()
	{
		for ( int i = 0; i < NumDrawLayers; i++ )
		{
			Tools::RemoveAll<boost::shared_ptr<ObjectBase> >( DrawLayer[ i ], boost::make_shared<CleanDrawLayerLambda>( i ) );
		}
	}

	void Level::CleanBlockList()
	{
		Tools::RemoveAll<boost::shared_ptr<BlockBase> >( Blocks, boost::make_shared<CleanBlockListLambda>() );
	}

	void Level::AddBlock( const boost::shared_ptr<BlockBase> &block )
	{
		AddBlock( block, true );
	}

	void Level::AddBlock( const boost::shared_ptr<BlockBase> &block, bool AddTimeStamp )
	{
		// Add a time stamp
		if ( AddTimeStamp )
			block->getCore()->AddedTimeStamp = CurPhsxStep;

		// Set a default tile set if none is specified
		if ( block->getCore()->getMyTileSet() == TileSets::None )
			block->getCore()->setMyTileSet(MyTileSet);

		// Add the block to the block list
		SynchObject( block );
		Blocks.push_back( block );
		block->getBlockCore()->MyLevel = shared_from_this();
		TR = Vector2::Max( TR, block->getBox()->Current->TR );
		BL = Vector2::Min( BL, block->getBox()->Current->BL );

		// Add block to the draw lists
		ReAddObject( block );
	}

	void Level::AddBob( const boost::shared_ptr<Bob> &bob )
	{
		bob->getCore()->MyLevel = shared_from_this();
		Bobs.push_back( bob );
	}

	void Level::DrawGivenLayer( int i )
	{
		if ( !ShowDrawLayer[ i ] )
			return;

		CurrentDrawLayer = i;

		if ( CurEditorDrawLayer >= 0 && CurEditorDrawLayer != i )
			return;

		if ( i == CharacterSelectManager::DrawLayer + 1 )
			CharacterSelectManager::Draw();

		if ( i == ReplayDrawLayer )
		{
			if ( Replay && !MainReplayOnly )
				MySwarmBundle->Draw( CurPhsxStep, shared_from_this() );
		}


		for ( ObjectVec::const_iterator obj = DrawLayer[ i ].begin(); obj != DrawLayer[ i ].end(); ++obj )
			if ( ( *obj )->getCore()->Show )
				( *obj )->Draw();

		Tools::QDrawer->Flush();

		if ( MyGame != 0 && MyGame->DrawObjectText )
		{
			for ( ObjectVec::const_iterator obj = DrawLayer[ i ].begin(); obj != DrawLayer[ i ].end(); ++obj )
				( *obj )->TextDraw();
			Tools::Render->EndSpriteBatch();
		}

		if ( !Replay || MainReplayOnly )
		{
			if ( MyGame != 0 && MyGame->MyGameFlags.IsTethered )
			for ( BobVec::const_iterator Player = Bobs.begin(); Player != Bobs.end(); ++Player )
			{
				if ( ( *Player )->getCore()->DrawLayer == i && (*Player)->MyBobLinks.size() > 0 )
					for ( std::vector<boost::shared_ptr<BobLink> >::const_iterator link = ( *Player )->MyBobLinks.begin(); link != ( *Player )->MyBobLinks.end(); ++link )
						( *link )->Draw();
			}

			for ( BobVec::const_iterator Bob_Renamed = Bobs.begin(); Bob_Renamed != Bobs.end(); ++Bob_Renamed )
			{
				if ( ( *Bob_Renamed )->DrawWithLevel && ( *Bob_Renamed )->getCore()->DrawLayer == i )
					( *Bob_Renamed )->Draw();
			}
			Tools::QDrawer->Flush();
		}

		if ( !NoParticles )
			ParticleEmitters[ i ]->Draw();
	}

	void Level::MakeClosingCircle()
	{
		MakeClosingCircle( 150, getMainCamera()->Data.Position );
	}

	void Level::MakeClosingCircle( float Frames, Vector2 Pos )
	{
		setUseLighting( true );

		Circle = boost::make_shared<ClosingCircle>( getMainCamera(), Frames, Pos );
	}

	void Level::MakeClosingCircle( float Frames, const boost::shared_ptr<IPos> &Pos )
	{
		setUseLighting( true );

		Circle = boost::make_shared<ClosingCircle>( getMainCamera(), Frames, Pos );
	}

	const bool &Level::getUseLighting() const
	{
		return _UseLighting;
	}

	void Level::setUseLighting( const bool &value )
	{
		_UseLighting = value;

		if ( _UseLighting )
		{
			if ( LightRenderTarget == 0 )
				InitializeLighting();
		}
		else
		{
			LightRenderTarget.reset();
			LightTexture.reset();
		}
	}

	void Level::InitializeLighting()
	{
		LightTexture = boost::make_shared<EzTexture>();
		LightTexture->Name = _T( "LightTexture" );

		boost::shared_ptr<PresentationParameters> pp = Tools::Device->PP;
		LightRenderTarget = boost::make_shared<RenderTarget2D>( Tools::Device, pp->BackBufferWidth, pp->BackBufferHeight, false, pp->BackBufferFormat, pp->DepthStencilFormat, pp->MultiSampleCount, true );

		LightQuad = boost::make_shared<QuadClass>();
		LightQuad->setEffectName( _T( "LightMap" ) );
	}

	float tempVector[] = { 800, 70, 690, 630, 500 };
	std::vector<float> Level::BobLightRadiusByDifficulty = VecFromArray( tempVector );

	void Level::SetBobLightRadius( int Difficulty )
	{
		BobLightRadius = BobLightRadiusByDifficulty[ Difficulty ];
	}

	void Level::FadeBobLightSourcesIn()
	{
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
			( *bob )->SetLightSourceToFadeIn();
	}

	void Level::PrepareLighting()
	{
		Tools::QDrawer->Flush();

		getMainCamera()->SetVertexCamera();
		Tools::QDrawer->WashTexture();
		Tools::Device->SetRenderTarget( LightRenderTarget );
		Tools::Device->Clear( Color::Transparent );

		// Closing circle
		if ( Circle != 0 )
			Circle->Draw();
		Tools::QDrawer->Flush();

		// Stickmen lighting
		if ( StickmanLighting )
		{
			for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
			{
				Color c = Color( 1, 1, 1, ( *bob )->LightSourceFade );
				Tools::QDrawer->DrawLightSource( ( *bob )->getPos(), 670, 5, c ); //new Color(.75f, .75f, .75f, .75f));
			}
			Tools::QDrawer->Flush();
		}

		Tools::QDrawer->Flush();
		Tools::Device->SetRenderTarget( Tools::DestinationRenderTarget );
		Tools::TheGame->MyGraphicsDevice->Clear( Color::Black );
		Tools::Render->ResetViewport();
		LightTexture->setTex( LightRenderTarget );
	}

	void Level::DrawLighting()
	{
		getMainCamera()->SetVertexCamera();

		LightQuad->Quad_Renamed.setMyTexture( LightTexture );
		LightQuad->FullScreen( getMainCamera() );
		LightQuad->Draw();
	}

	void Level::Draw()
	{
		Draw( false );
	}

	void Level::Draw( bool DrawAll )
	{
		Draw( DrawAll, 0, 100 );
	}

	void Level::Draw( bool DrawAll, int StartLayer, int EndLayer )
	{
		if ( LevelReleased )
			return;

		if ( ModZoom != Vector2(1) )
		{
			Tools::EffectWad->ModZoom = ModZoom;
			Tools::EffectWad->ResetCameraPos();
		}

		if ( getUseLighting() )
			PrepareLighting();

		if ( MyBackground != 0 && Tools::DrawGraphics )
		{
			if ( Background::GreenScreen )
				Background::DrawTest();
			else
				MyBackground->Draw();
		}

		if ( CloudberryKingdomGame::HideForeground )
			return;

		getMainCamera()->SetVertexCamera();

		Vector2 HoldBL, HoldTR;
		HoldBL = getMainCamera()->BL;
		HoldTR = getMainCamera()->TR;
		if ( DrawAll )
		{
			getMainCamera()->BL = Vector2(-1000000, -1000000);
			getMainCamera()->TR = Vector2(1000000, 1000000);
		}

		for ( int i = StartLayer; i <= CoreMath::RestrictVal( 0, Level::AfterParticlesDrawLayer - 1, EndLayer ); i++ )
			DrawGivenLayer( i );

		// Draw particles
		if ( !NoParticles )
			MainEmitter->Draw();
		Tools::QDrawer->Flush();

		if ( getUseLighting() && LightLayer == LightLayers_FRONT_OF_LEVEL )
			DrawLighting();

		// Draw background's foreground.
		if ( MyBackground != 0 && Tools::DrawGraphics )
		{
			MyBackground->DrawForeground();
		}

		// Draw final DrawLayer
		if ( ModZoom != Vector2(1) )
		{
			Tools::EffectWad->ModZoom = Vector2(1);
			Tools::EffectWad->ResetCameraPos();
		}
		Tools::StartGUIDraw();
		if ( EndLayer >= Level::AfterParticlesDrawLayer )
		{
			DrawGivenLayer( Level::AfterParticlesDrawLayer );
			DrawGivenLayer( Level::AfterParticlesDrawLayer + 1 );
		}

		if ( DrawAll )
		{
			getMainCamera()->BL = HoldBL;
			getMainCamera()->TR = HoldTR;
		}

		if ( getUseLighting() && LightLayer == LightLayers_FRONT_OF_EVERYTHING )
			DrawLighting();

		Tools::EndGUIDraw();
	}

	void Level::FinalizeBlocks()
	{
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			( *block )->getBlockCore()->Finalized = true;
	}

	void Level::TagAll( int Tag )
	{
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			( *obj )->getCore()->Tag = Tag;
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			( *block )->getCore()->Tag = Tag;
	}

	void Level::AddLevelBlocks( const boost::shared_ptr<Level> &level )
	{
		for ( BlockVec::const_iterator block = level->Blocks.begin(); block != level->Blocks.end(); ++block )
			AddBlock( *block );
	}

	void Level::AddLevelBlocks( const boost::shared_ptr<Level> &level, int Tag )
	{
		for ( BlockVec::const_iterator block = level->Blocks.begin(); block != level->Blocks.end(); ++block )
			if ( ( *block )->getCore()->Tag == Tag && !(*block)->getCore()->DoNotScrollOut )
				AddBlock( *block );
		level->RemoveForeignObjects();
	}

	void Level::AddLevelObjects( const boost::shared_ptr<Level> &level )
	{
		AddLevelObjects( level, Vector2( -10000000, -100000000 ), Vector2( 10000000, 10000000 ) );
	}

	void Level::AddLevelObjects( const boost::shared_ptr<Level> &level, Vector2 p1, Vector2 p2 )
	{
		for ( ObjectVec::const_iterator obj = level->Objects.begin(); obj != level->Objects.end(); ++obj )
			if ( IsBetween( ( *obj )->getCore()->Data.Position, p1, p2 ) && !(*obj)->getCore()->DoNotScrollOut )
				AddObject( *obj, false );
	}

	void Level::AddLevelObjects( const boost::shared_ptr<Level> &level, int Tag )
	{
		for ( ObjectVec::const_iterator obj = level->Objects.begin(); obj != level->Objects.end(); ++obj )
			if ( ( *obj )->getCore()->Tag == Tag && !(*obj)->getCore()->DoNotScrollOut )
				AddObject( *obj, false );
		level->RemoveForeignObjects();
	}

	void Level::AbsorbLevelVisuals( const boost::shared_ptr<Level> &level )
	{
		if ( MainEmitter != 0 && level->MainEmitter != 0 )
			MainEmitter->Absorb( level->MainEmitter );

		if ( MyBackground != 0 && level->MyBackground != 0 )
			MyBackground->Absorb( level->MyBackground );
	}

	void Level::SetBackground( const boost::shared_ptr<Background> &background )
	{
		MyBackground = background;
		MyBackground->SetLevel( shared_from_this() );
	}

	void Level::AbsorbLevel( const boost::shared_ptr<Level> &level )
	{
		AddLevelBlocks( level );
		AddLevelObjects( level );
		for ( std::vector<boost::shared_ptr<LevelPiece> >::const_iterator piece = level->LevelPieces.begin(); piece != level->LevelPieces.end(); ++piece )
		{
			( *piece )->MyLevel = shared_from_this();
			LevelPieces.push_back( *piece );
		}

		AbsorbLevelVisuals( level );

		level->Objects.clear();
		level->Blocks.clear();

		for ( BobVec::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
			( *bob )->MyRecord.reset();
		level->LevelPieces.clear();
		level->Release();
	}

	void Level::RemoveForeignObjects()
	{
		Tools::RemoveAll<boost::shared_ptr<ObjectBase> >( Objects, boost::make_shared<RemoveForeignLambda>( shared_from_this() ) );
		for ( int i = 0; i < NumDrawLayers; i++ )
			Tools::RemoveAll<boost::shared_ptr<ObjectBase> >( DrawLayer[ i ], boost::make_shared<RemoveForeignLambda>( shared_from_this() ) );
		Tools::RemoveAll<boost::shared_ptr<BlockBase> >( Blocks, boost::make_shared<RemoveForeignBlockLambda>( shared_from_this() ) );
	}

	ObjectVec Level::GetObjectList( ObjectType type )
	{
		ObjectVec list = ObjectVec();

		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			if ( ( *obj )->getCore()->MyType == type && !(*obj)->getCore()->MarkedForDeletion )
				list.push_back( *obj );

		return list;
	}

	boost::shared_ptr<Level::BaseMetric> Level::DefaultMetric = boost::make_shared<Level::BaseMetric>();

	void Level::Cleanup( ObjectType type, Vector2 v )
	{
		Cleanup( type, v, Vector2( -100000000, -100000000 ), Vector2( 100000000, 100000000 ) );
	}

	void Level::Cleanup( ObjectType type, Vector2 v, Vector2 BL, Vector2 TR )
	{
		Cleanup( type, boost::make_shared<ConstLambda>( v ), BL, TR, DefaultMetric );
	}

	void Level::Cleanup( ObjectType type, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc )
	{
		Cleanup( type, MinDistFunc, Vector2( -100000000, -100000000 ), Vector2( 100000000, 100000000 ) );
	}

	void Level::Cleanup( ObjectType type, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR )
	{
		Cleanup( type, MinDistFunc, BL, TR, DefaultMetric );
	}

	void Level::Cleanup( ObjectType type, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR, const boost::shared_ptr<LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2> > &metric )
	{
		ObjectVec CleanupList = GetObjectList( type );

		Cleanup( CleanupList, MinDistFunc, false, BL, TR, metric );
	}

	void Level::Cleanup( const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR )
	{
		Cleanup( ObjList, MinDistFunc, false, BL, TR );
	}

	void Level::Cleanup( const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, bool MustBeDifferent, Vector2 BL, Vector2 TR )
	{
		Cleanup( ObjList, MinDistFunc, MustBeDifferent, BL, TR, DefaultMetric );
	}

	void Level::Cleanup( const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, bool MustBeDifferent, Vector2 BL, Vector2 TR, const boost::shared_ptr<LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2> > &metric )
	{
		if ( ObjList.empty() )
			return;

		for ( ObjectVec::const_iterator obj = ObjList.begin(); obj != ObjList.end(); ++obj )
		{
			if ( ( *obj )->getCore()->GenData.EnforceBounds )
			if ( ( *obj )->getCore()->Data.Position.X > TR.X || (*obj)->getCore()->Data.Position.X < BL.X || (*obj)->getCore()->Data.Position.Y > TR.Y || (*obj)->getCore()->Data.Position.Y < BL.Y )
				getRecycle()->CollectObject(*obj);

			if ( ( *obj )->getCore()->MarkedForDeletion )
				continue;

			if ( !( *obj )->getCore()->GenData.LimitDensity )
				continue;

			CheckAgainst( *obj, ObjList, MinDistFunc, metric, MustBeDifferent );
		}
	}

	void Level::Cleanup_xCoord( ObjectType ObjType, float MinDist )
	{
		ObjectVec ObjList = GetObjectList( ObjType );

		for ( ObjectVec::const_iterator obj = ObjList.begin(); obj != ObjList.end(); ++obj )
		{
			if ( ( *obj )->getCore()->MarkedForDeletion )
				continue;

			CheckAgainst_xCoord( *obj, ObjList, MinDist );
		}
	}

	void Level::CheckAgainst( const boost::shared_ptr<ObjectBase> &obj, const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, const boost::shared_ptr<LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2> > &metric, bool MustBeDifferent )
	{
		for ( ObjectVec::const_iterator obj2 = ObjList.begin(); obj2 != ObjList.end(); ++obj2 )
		{
			if ( !( *obj2 )->getCore()->GenData.LimitDensity )
				return;

			if ( obj->getCore()->IsAssociatedWith(*obj2) )
			{
				if ( obj->getCore()->GetAssociationData(*obj2).UseWhenUsed )
					return;
			}

			if ( !obj->getCore()->MarkedForDeletion && !(*obj2)->getCore()->MarkedForDeletion && obj != *obj2 && !(MustBeDifferent && obj->getCore()->MyType == (*obj2)->getCore()->MyType) )
			{
				Vector2 MinDist = ( MinDistFunc->Apply( obj->getCore()->Data.Position ) + MinDistFunc->Apply((*obj2)->getCore()->Data.Position) ) / 2;

				Vector2 d = metric->Apply( obj, *obj2 );

				if ( d.X < MinDist.X && d.Y < MinDist.Y )
				{
					int Choice = 0; // 0 -> Remove first object, 1 -> Remove second object

					if ( obj->getCore()->GenData.KeepIfUnused && (*obj2)->getCore()->GenData.KeepIfUnused )
						return;
					else if ( obj->getCore()->GenData.KeepIfUnused )
						Choice = 1;
					else if ( ( *obj2 )->getCore()->GenData.KeepIfUnused )
						Choice = 0;
					else if ( getRnd()->Rnd->NextDouble() > .5f )
						Choice = 1;

					if ( Choice == 0 )
						getRecycle()->CollectObject(obj);
					else
						getRecycle()->CollectObject(*obj2);
				}
			}
		}
	}

	void Level::CheckAgainst_xCoord( const boost::shared_ptr<ObjectBase> &obj, const ObjectVec &ObjList, float MinDist )
	{
		for ( ObjectVec::const_iterator obj2 = ObjList.begin(); obj2 != ObjList.end(); ++obj2 )
		{
			if ( !obj->getCore()->MarkedForDeletion && !(*obj2)->getCore()->MarkedForDeletion && obj != *obj2 )
			{
				float d = static_cast<float>( abs( obj->getPos().X - (*obj2)->getPos().X ) );

				if ( d < MinDist )
				{
					int Choice = 0; // 0 -> Remove first object, 1 -> Remove second object

					if ( obj->getCore()->GenData.KeepIfUnused && (*obj2)->getCore()->GenData.KeepIfUnused )
						return;
					else if ( obj->getCore()->GenData.KeepIfUnused )
						Choice = 1;
					else if ( ( *obj2 )->getCore()->GenData.KeepIfUnused )
						Choice = 0;
					else if ( getRnd()->Rnd->NextDouble() > .5f )
						Choice = 1;

					if ( Choice == 0 )
						getRecycle()->CollectObject(obj);
					else
						getRecycle()->CollectObject(*obj2);
				}
			}
		}
	}

	void Level::StartPlayerPlay()
	{
		PieceAttempts--;
		NumAttempts--;

		Watching = false;
		SuppressCheckpoints = false;
		GhostCheckpoints = false;

		Bobs.clear();
		AddRange( Bobs, HoldPlayerBobs );

		setSetToReset( true );
	}

	void Level::EvolveParticles()
	{
		// Evolve particles
		if ( !NoParticles )
		{
			MainEmitter->Phsx();
			for ( int i = 0; i < NumDrawLayers; i++ )
				ParticleEmitters[ i ]->Phsx();
		}
	}

	void Level::UpdateBlocks()
	{
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			if ( !( *block )->getCore()->MarkedForDeletion )
				( *block )->PhsxStep();
	}

	void Level::UpdateObjects()
	{
		for ( ObjectVec::const_iterator Object = ActiveObjectList.begin(); Object != ActiveObjectList.end(); ++Object )
		{
			if ( !( *Object )->getCore()->IsGameObject && !(*Object)->getCore()->MarkedForDeletion )
				( *Object )->PhsxStep();
		}
	}

	void Level::UpdateBlocks2()
	{
		for ( BlockVec::const_iterator block = Blocks.begin(); block != Blocks.end(); ++block )
			if ( !( *block )->getCore()->MarkedForDeletion )
				( *block )->PhsxStep2();
	}

	void Level::UpdateObjects2()
	{
		for ( ObjectVec::const_iterator Object = ActiveObjectList.begin(); Object != ActiveObjectList.end(); ++Object )
		{
			if ( !( *Object )->getCore()->MarkedForDeletion )
				( *Object )->PhsxStep2();
		}
	}

	void Level::UpdateBobs()
	{
		for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
		{
			( *bob )->PhsxStep();
			if ( !( *bob )->Cinematic && !( *bob )->ManualAnimAndUpdate )
				( *bob )->AnimAndUpdate();

			int i = ( *bob )->MyPieceIndex;
			if ( RecordPosition )
			{
				CurPiece->Recording_Renamed[ i ]->AutoLocs[ CurPhsxStep - ( *bob )->IndexOffset ] = ( *bob )->getCore()->Data.Position;
				CurPiece->Recording_Renamed[ i ]->AutoVel[ CurPhsxStep - ( *bob )->IndexOffset ] = ( *bob )->getCore()->Data.Velocity;
				CurPiece->Recording_Renamed[ i ]->AutoOnGround[ CurPhsxStep - ( *bob )->IndexOffset ] = ( *bob )->MyPhsx->OnGround;
			}
			else
			{
				if ( PlayMode == 0 && Replay && !ReplayPaused )
				{
					Vector2 IntendedLoc = MySwarmBundle->CurrentSwarm->MainRecord->Recordings[ IndexOf( Bobs, *bob ) ]->AutoLocs[ CurPhsxStep ];
					Vector2 IntendedVel = MySwarmBundle->CurrentSwarm->MainRecord->Recordings[ IndexOf( Bobs, *bob ) ]->AutoVel[ CurPhsxStep ];
					( *bob )->Move( IntendedLoc - ( *bob )->getCore()->Data.Position );
					( *bob )->getCore()->Data.Velocity = IntendedVel;
				}

				if ( ( *bob )->MyPiece != 0 && static_cast<int>( ( *bob )->MyPiece->Recording_Renamed.size() ) > 0 && !(*bob)->CharacterSelect_Renamed && !(*bob)->CharacterSelect2 )
					if ( PlayMode == 1 || PlayMode == 0 && ( *bob )->CompControl && !Replay )
					{
						int index = CurPhsxStep - ( *bob )->IndexOffset;
						Vector2 a, b;
						bool A, B;
						a = ( *bob )->MyPiece->Recording_Renamed[ i ]->AutoLocs[ index ];
						b = ( *bob )->getCore()->Data.Position;
						A = ( *bob )->MyPiece->Recording_Renamed[ i ]->AutoOnGround[ index ];
						B = ( *bob )->MyPhsx->OnGround;
						Vector2 dif = a - b;
						if ( abs( dif.X ) > .001f || abs( dif.Y ) > .001f )
						{
							if ( CurPhsxStep < ( *bob )->MyPiece->PieceLength - 15 )
							{
								CreationError = true;
							}
							if ( a != Vector2() )
							{
								//bob.Core.Data.Position = a;
								( *bob )->Move( a - ( *bob )->getCore()->Data.Position );
								( *bob )->getCore()->Data.Velocity = (*bob)->MyPiece->Recording_Renamed[ i ]->AutoVel[ index ];
								//Console.WriteLine("Bob[{0}]---> {1}/{2}:  {3}, {4}, {5}, {6}", Bobs.IndexOf(bob), GetPhsxStep(), bob.MyPiece.PieceLength, a, b, A, B);
							}
						}
					}
			}
		}
	}

	void Level::PhsxStep( bool NotDrawing )
	{
		PhsxStep( NotDrawing, true );
	}

	void Level::PhsxStep( bool NotDrawing, bool GUIPhsx )
	{
		if ( !IndependentStepSetOnce )
			SetIndependentStep();

		if ( LevelReleased )
			return;

		if ( !getSetToReset() && Watching && Replay && !ReplayPaused && MySwarmBundle->EndCheck( shared_from_this() ) )
		{
			if ( !MySwarmBundle->GetNextSwarm( shared_from_this() ) )
				ReplayPaused = true;
			else
				setSetToReset( true );
		}
		if ( !getSetToReset() && Watching && !Replay && EndOfReplay() )
		{
			ReplayPaused = true;
		}


		if ( getSetToReset() )
		{
			if ( DelayReset <= 0 )
			{
				setSetToReset( false );
				ResetAll( false );

				if ( LevelReleased )
					return;
			}
			else
			{
				if ( !NoParticles )
					MainEmitter->Phsx();
				DelayReset--;
				return;
			}
		}

		if ( ReplayPaused )
			return;

		EvolveParticles();

		CheckTimeLimit();

		ObjectsLocked = true;

		// Blocks update first, so that attached objects are positioned correctly
		UpdateBlocks();

		// Objects are updated afterward
		UpdateObjects();

		if ( !getSetToReset() )
			UpdateBobs();


		// Blocks, final physics steps
		UpdateBlocks2();

		// Objects, final physics steps
		UpdateObjects2();

		ObjectsLocked = false;
		AddRange( Objects, AddedObjects );
		if ( ActiveObjectList != Objects )
			AddRange( ActiveObjectList, AddedObjects );
		AddedObjects.clear();

		int CleanPeriod = 20;
		if ( !BoxesOnly || CurPhsxStep % CleanPeriod == 0 )
		{
			// Remove deleted objects
			CleanAllObjectLists();

			// Reset active object list
			if ( BoxesOnly )
				ResetActiveObjectList();
		}

		// Update the active object list
		if ( BoxesOnly && CurPhsxStep % CleanPeriod == 1 )
			UpdateActiveObjectList();

		// Update the camera
		if ( !FreezeCamera )
			getMainCamera()->PhsxStep();
		else
			getMainCamera()->Update();

		// Increase number of steps taken
		CurPhsxStep++;

		// Increase time (may not be related to number of steps taken)
		SetIndependentStep();

		// If the player is playing record this frame
		if ( !( PlayMode != 0 || Watching ) )
			if ( Recording_Renamed )
				CurrentRecording->Record( shared_from_this() );
	}

	void Level::SetIndependentStep()
	{
		float PrevIndependentPhsxStep = IndependentPhsxStep;
		//TimeType = TimeTypes.Regular;
		//TimeType = TimeTypes.xSync;
		switch ( TimeType )
		{
			case TimeTypes_REGULAR:
				//IndependentPhsxStep = CurPhsxStep * 1.5f;
				IndependentPhsxStep = static_cast<float>( CurPhsxStep * 1 );
				if ( !IndependentStepSetOnce )
					PrevIndependentPhsxStep = IndependentPhsxStep - 1;
				break;

			case TimeTypes_X_SYNC:
				if ( Bobs.size() > 0 && Bobs[ 0 ] != 0 )
				{
					int NumAlive = 0;
					Vector2 Pos = Vector2();
					for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
					{
						if ( ( *bob )->getMyPlayerData()->IsAlive )
						{
							NumAlive++;
							Pos += ( *bob )->getPos();
							//Pos.X += bob.Core.Data.Velocity.X + bob.GroundSpeed;
							//Pos.X += bob.GroundSpeed / 4;
						}
					}

					if ( NumAlive == 0 )
						break;

					//float New = Bobs[0].Pos.X / 10;
					float New = ( Pos.X / NumAlive ) / 10;

					if ( !IndependentStepSetOnce )
						Prev = New;

					IndependentPhsxStep = __max( New, Prev );
					Prev = New;

					if ( !IndependentStepSetOnce )
						PrevIndependentPhsxStep = IndependentPhsxStep;
				}
				break;
		}

		IndependentDeltaT = IndependentPhsxStep - PrevIndependentPhsxStep;
		IndependentStepSetOnce = true;
	}

	void Level::CreateActiveObjectList()
	{
		if ( BoxesOnly )
		{
			ActiveObjectList = ObjectVec();
			ResetActiveObjectList();
		}
		else
			ActiveObjectList = Objects;
	}

	void Level::UpdateActiveObjectList()
	{
		if ( ActiveObjectList == Objects )
			return;

		ActiveObjectList.clear();

		// Keep active all objects that didn't skip their phsx the previous step.
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
		{
			if ( !( *obj )->getCore()->SkippedPhsx && !(*obj)->getCore()->MarkedForDeletion )
			{
				ActiveObjectList.push_back( *obj );
			}
		}
	}

	void Level::ResetActiveObjectList()
	{
		if ( ActiveObjectList == Objects )
			return;

		ActiveObjectList.clear();

		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
			ActiveObjectList.push_back( *obj );
	}

	bool Level::IsBetween( Vector2 Point, Vector2 p1, Vector2 p2 )
	{
		if ( Sign( p1.X - Point.X ) != Sign( p2.X - Point.X ) && Sign( p1.Y - Point.Y ) != Sign( p2.Y - Point.Y ) )
			return true;
		else
			return false;
	}

	void Level::CountCoinsAndBlobs()
	{
		NumCoins = 0;
		TotalCoinScore = 0;
		for ( ObjectVec::const_iterator obj = Objects.begin(); obj != Objects.end(); ++obj )
		{
			boost::shared_ptr<Coin> coin = boost::dynamic_pointer_cast<Coin>( *obj );
			if ( 0 != coin && !coin->getCore()->MarkedForDeletion )
			{
				NumCoins++;
				TotalCoinScore += coin->MyScoreValue;
			}

			boost::shared_ptr<FlyingBlob> blob = boost::dynamic_pointer_cast<FlyingBlob>( *obj );
			if ( 0 != blob )
			{
				NumBlobs++;
			}
		}
	}

	void Level::SetBack( int Steps )
	{
		CurPiece->StartPhsxStep -= Steps;
		MyGame->WaitThenDo( 2, boost::make_shared<SetBackLambda>( shared_from_this(), Steps ) );
	}

	void Level::InitializeInstanceFields()
	{
		BoxesOnly = false;
		TimeType = static_cast<TimeTypes>( 0 );

		MaxRight = EndBuffer = 0;
		LastStep = 0;
		CoinsCountInStats = false;
		NumCoins = NumBlobs = TotalCoinScore = 0;
		Finished = false;
		RecordPosition = false;
		Geometry = static_cast<LevelGeometry>( 0 );
		PlayMode = NumModes = 0;
		CreationError = false;
		Recording_Renamed = false;
		SetToWatchMake = false;
		SingleOnly = false;
		NoCameraChange = false;
		EndReached = false;
		IndependentStepSetOnce = false;
		IndependentPhsxStep = IndependentDeltaT = 0;
		ShowCoinsInReplay = false;
		Watching = Replay = SuppressCheckpoints = GhostCheckpoints = MainReplayOnly = ReplayPaused;	
		Prev = 0;
		NoParticles = false;
		BobLightRadius = 0;
		TimeType = static_cast<TimeTypes>( 0 );

		SuppressSounds = false;
		SuppressReplayButtons = false;
		LevelReleased = false;
		NumAttempts = 0; PieceAttempts = 0;
		ReturnedEarly = false;
		SetToWatchMake = false;
		CanLoadLevels = false;
		CanSaveLevel = false;
		CanWatchComputer = false;
		CanWatchReplay = false;
		_PreventReset = false;
		PreventHelp = false;
		FreezeCamera = false;
		TimeLimit = 0;
		HaveTimeLimit = false;
		TimeLimitTimerLength;
		_UseLighting = false;
		Par = 0;
		CurPhsxStep = 0; StartPhsxStep = 0;
		DelayReset = 0;
		_SetToReset = false;
		FreeReset = false;
		ObjectsLocked = false;
		CurEditorDrawLayer = 0;


		ReturnedEarly = false;

		ShowCoinsInReplay = false;
		Watching = Replay = SuppressCheckpoints = GhostCheckpoints = MainReplayOnly = ReplayPaused = false;

		LevelReleased = false;
		EndReached = false;
		SingleOnly = false;
		NoCameraChange = false;
		NumModes = 2;
		CoinsCountInStats = false;
		Finished = false;
		LastSafetyBlock = 0;
		__block_fromlambda = 0;
		Name = _T( "" );
		_PrivateRnd = 0;
		SuppressSounds = false;
		SuppressReplayButtons = false;
		CanLoadLevels = false;
		CanSaveLevel = true;
		CanWatchComputerFromAfar_External = true;
		PreventHelp = false;
		TimeLimit = 7200;
		HaveTimeLimit = true;
		TimeLimitTimerLength = 62 * 10 - 1;
		ModZoom = Vector2(1);
		_UseLighting = false;
		CurEditorDrawLayer = -1;
		DrawLayer = std::vector<ObjectVec>( NumDrawLayers );
		ParticleEmitters = std::vector<boost::shared_ptr<ParticleEmitter> >( NumDrawLayers );
		ShowCoinsInReplay = true;
		OnCameraChange = boost::make_shared<Multicaster>();
		AllowRecording = false;
		PreRecycleBin.reserve( 1000 );
		StickmanLighting = false;
		BobLightRadius = 700;
		LightLayer = LightLayers_FRONT_OF_LEVEL;
		IndependentStepSetOnce = false;
		IndependentPhsxStep = 0;
		IndependentDeltaT = 0;
		Prev = 0;
		TimeType = TimeTypes_REGULAR;
	}
}
