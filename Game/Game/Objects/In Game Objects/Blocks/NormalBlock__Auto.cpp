#include <global_header.h>

namespace CloudberryKingdom
{

	std::shared_ptr<Wall> NormalBlock_Parameters::SetWall( LevelGeometry geometry )
	{
		MyWall = Wall::MakeWall( geometry );
		return MyWall;
	}

	void NormalBlock_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		KeepUnused = Param( PieceSeed );
		if ( std::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( .7f );
		}

		FillWeight = Param( PieceSeed );
		FillWeight.SetVal( 1 );
	}

	void NormalBlock_Parameters::InitializeInstanceFields()
	{
		Make = true;
		CustomWeight = false;
		DoStage1Fill = true;
		DoInitialPlats = true;
		DoFinalPlats = true;
	}

std::shared_ptr<NormalBlock_AutoGen> NormalBlock_AutoGen::instance = std::make_shared<NormalBlock_AutoGen>();

	const std::shared_ptr<NormalBlock_AutoGen> &NormalBlock_AutoGen::getInstance()
	{
		return instance;
	}

	NormalBlock_AutoGen::NormalBlock_AutoGen()
	{
		Do_PreFill_1 = true;
		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	std::shared_ptr<AutoGen_Parameters> NormalBlock_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<NormalBlock_Parameters> Params = std::make_shared<NormalBlock_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void NormalBlock_AutoGen::MakeWall( const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<CloudberryKingdom::NormalBlock_Parameters> Params = GetParams( level );

		level->AddBlock( Params->MyWall );
		Params->MyWall.reset();
	}

	std::shared_ptr<NormalBlock_Parameters> NormalBlock_AutoGen::GetParams( const std::shared_ptr<Level> &level )
	{
		return std::static_pointer_cast<NormalBlock_Parameters>( level->getStyle()->FindParams( NormalBlock_AutoGen::getInstance() ) );
	}

	void NormalBlock_AutoGen::PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_1( level, BL, TR );

		// Get NormalBlock parameters
		std::shared_ptr<NormalBlock_Parameters> Params = std::static_pointer_cast<NormalBlock_Parameters>( level->getStyle()->FindParams( NormalBlock_AutoGen::getInstance() ) );

		if ( Params->MyWall != 0 )
			MakeWall( level );
	}

	void NormalBlock_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void NormalBlock_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	std::shared_ptr<ObjectBase> NormalBlock_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		AutoGen::CreateAt( level, pos );

		std::shared_ptr<StyleData> style = level->getStyle();

		// Get NormalBlock parameters
		std::shared_ptr<NormalBlock_Parameters> Params = std::static_pointer_cast<NormalBlock_Parameters>( style->FindParams( NormalBlock_AutoGen::getInstance() ) );
		if ( !Params->Make )
			return 0;

		std::shared_ptr<NormalBlock> block = std::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
		std::shared_ptr<BlockData> core = block->getBlockCore();
		block->Init( pos, Vector2( 50, 50 ), level->getMyTileSetInfo() );

		core->GenData.RemoveIfUnused = true;
		core->BlobsOnTop = true;

		if ( style->RemoveBlockOnCol )
			core->GenData.RemoveIfUsed = true;

		if ( style->RemoveBlockOnOverlap )
			core->GenData.RemoveIfOverlap = true;

		level->AddBlock( block );

		return block;
	}

	std::shared_ptr<ObjectBase> NormalBlock_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get NormalBlock parameters
		std::shared_ptr<NormalBlock_Parameters> Params = std::static_pointer_cast<NormalBlock_Parameters>( Style->FindParams( NormalBlock_AutoGen::getInstance() ) );

		if ( !Params->Make )
			return 0;

		std::shared_ptr<NormalBlock> block;
		Vector2 size = Vector2();
		Vector2 offset = Vector2();

		bool EnsureBoundsAfter = true;
		switch ( Style->BlockFillType )
		{
			case StyleData::_BlockFillType_REGULAR:
				size = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_X, pos) ),
							    static_cast<float>( GenData->Get(DifficultyParam_MAX_BOX_SIZE_X, pos)), level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_Y, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_Y, pos) ) ) );
				if ( -2 * size.Y + pos.Y < BL.Y - 100 )
					size.Y = ( pos.Y - BL.Y + 100 ) / 2;

				offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ),
								  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) - size.Y ) );

				if ( pos.X - size.X < BL.X )
					offset.X += BL.X - ( pos.X - size.X );

				block = std::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
				block->Init( pos + offset, size, level->getMyTileSetInfo() );
				block->Extend( Side_BOTTOM, block->getBox()->BL.Y - level->CurMakeData->PieceSeed->ExtraBlockLength );

				block->getCore()->GenData.MyOverlapPreference = GenerationData::OverlapPreference_REMOVE_LOWER_THAN_ME;

				break;

			case StyleData::_BlockFillType_TOP_ONLY:
				size = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_X, pos) ),
								static_cast<float>( GenData->Get(DifficultyParam_MAX_BOX_SIZE_X, pos)), 50 ) );

				if ( pos.X - size.X < BL.X )
					offset.X += BL.X - ( pos.X - size.X );

				block = std::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
				block->Init( pos + offset, size, level->getMyTileSetInfo() );
				block->MakeTopOnly();

				break;

			case StyleData::_BlockFillType_INVERTABLE:
				if ( pos.Y < level->getMainCamera()->getPos().Y - 0 )
				{
					size = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_X, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_X, pos) ) ),
									static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_Y, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_Y, pos) ) ) );
					if ( -2 * size.Y + pos.Y < BL.Y - 100 )
						size.Y = ( pos.Y - BL.Y + 100 ) / 2;

					offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ),
									  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) - size.Y ) );

					if ( pos.X - size.X < BL.X )
						offset.X += BL.X - ( pos.X - size.X );

					block = std::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
					block->Init( pos + offset, size, level->getMyTileSetInfo() );
					block->Extend( Side_BOTTOM, block->getBox()->BL.Y - level->CurMakeData->PieceSeed->ExtraBlockLength );

					block->getCore()->GenData.MyOverlapPreference = GenerationData::OverlapPreference_REMOVE_LOWER_THAN_ME;
				}
				else
				{
					size = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_X, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_X, pos) ) ),
								    static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_Y, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_Y, pos) ) ) );
					if ( 2 * size.Y + pos.Y > TR.Y + 100 )
						size.Y = ( TR.Y - pos.Y + 100 ) / 2;

					offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ),
									  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) + size.Y ) );

					if ( pos.X - size.X < BL.X )
						offset.X += BL.X - ( pos.X - size.X );

					block = std::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
					block->Init( pos + offset, size, level->getMyTileSetInfo() );
					block->Extend( Side_TOP, block->getBox()->TR.Y + level->CurMakeData->PieceSeed->ExtraBlockLength );

					block->Invert = true;
					block->getBlockCore()->BlobsOnTop = false;

					block->getCore()->GenData.MyOverlapPreference = GenerationData::OverlapPreference_REMOVE_HIGHER_THAN_ME;
				}

				break;

			case StyleData::_BlockFillType_SIDEWAYS:
				if ( pos.X < level->getMainCamera()->getPos().X - 0 )
				{
					size = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_Y, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_Y, pos) ) ),
									static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_X, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_X, pos) ) ) );

					offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) - size.X ),
									  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ) );

					block = std::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
					block->getBlockCore()->MyOrientation = PieceQuad::Orientation_ROTATE_RIGHT;
					block->Init( pos + offset, size, level->getMyTileSetInfo() );
					block->Extend( Side_LEFT, block->getBox()->BL.X - level->CurMakeData->PieceSeed->ExtraBlockLength );
				}
				else
				{
					size = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_Y, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_Y, pos) ) ),
									static_cast<float>( level->getRnd()->Rnd->Next(GenData->Get(DifficultyParam_MIN_BOX_SIZE_X, pos), GenData->Get(DifficultyParam_MAX_BOX_SIZE_X, pos) ) ) );

					offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) + size.X ),
									  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ) );

					block = std::static_pointer_cast<NormalBlock>( level->getRecycle()->GetObject(ObjectType_NORMAL_BLOCK, true) );
					block->getBlockCore()->MyOrientation = PieceQuad::Orientation_ROTATE_LEFT;
					block->Init( pos + offset, size, level->getMyTileSetInfo() );
					block->Extend( Side_RIGHT, block->getBox()->TR.X + level->CurMakeData->PieceSeed->ExtraBlockLength );
				}
				block->getCore()->GenData.NoBottomShift = block->getCore()->GenData.NoMakingTopOnly = true;
				EnsureBoundsAfter = false;
				break;

			default:
				block.reset();
				break;
		}

		block->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		if ( block->Invert && block->getBlockCore()->BlobsOnTop )
			block->getBlockCore()->BlobsOnTop = false;


		block->getBlockCore()->GenData.EdgeSafety = static_cast<float>( GenData->Get(DifficultyParam_EDGE_SAFETY, pos) );

		if ( level->CurMakeData->BlocksAsIs )
		{
			block->getCore()->GenData.NoMakingTopOnly = true;
			block->getCore()->GenData.NoBottomShift = true;
		}

		// Ensure bounds
		if ( EnsureBoundsAfter )
		{
			float CurTrX = block->getBox()->GetTR().X;
			if ( CurTrX > TR.X + 250 )
				block->Move( Vector2( TR.X + 250 - CurTrX, 0 ) );
		}

		if ( Style->RemoveBlockOnCol )
			block->getBlockCore()->GenData.RemoveIfUsed = true;

		if ( Style->RemoveBlockOnOverlap )
			block->getBlockCore()->GenData.RemoveIfOverlap = true;

		level->AddBlock( block );

		return block;
	}
}
