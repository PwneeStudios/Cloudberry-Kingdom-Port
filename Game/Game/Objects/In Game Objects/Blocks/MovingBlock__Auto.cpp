#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	void MovingBlock_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		float MovingBlockLevel = PieceSeed->MyUpgrades1->Get( Upgrade_MOVING_BLOCK );

		Aspect = AspectType_SQUARE;

		Size = Param( PieceSeed );
		Size.SetVal( 230 - ( 230 - 50 ) / 10 * u->Get( Upgrade_MOVING_BLOCK ) );

		Motion = static_cast<MotionType>( level->getRnd()->Choose(MotionLevel, static_cast<int>(MovingBlockLevel)) );

		KeepUnused = Param( PieceSeed );
		if ( std::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_MOVING_BLOCK ) ) );
		}

		FillWeight = Param( PieceSeed );
		FillWeight.SetVal( u->Get( Upgrade_MOVING_BLOCK ) );

		Range = Param( PieceSeed );
		Range.SetVal( DifficultyHelper::Interp( 240, 600,.5f * ( u->Get( Upgrade_JUMP ) + u->Get( Upgrade_MOVING_BLOCK ) ) ) );

		float speed = 280 - 32 * u->Get( Upgrade_SPEED ) + 40 *.5f * ( u->Get( Upgrade_JUMP ) + u->Get( Upgrade_MOVING_BLOCK ) );
		Period = Param( PieceSeed );
		Period.SetVal( CoreMath::RestrictVal( 40.f, 1000.f, speed ) );
	}

	void MovingBlock_Parameters::InitializeInstanceFields()
	{
		int tempVector[] = { 0, 1, 2, 3, 4, 5, 6 };
		MotionLevel = VecFromArray( tempVector );

		float tempVector2[] = { 1, 1, 1 };
		AspectTypeRatio = VecFromArray( tempVector2 );
	}

std::shared_ptr<MovingBlock_AutoGen> MovingBlock_AutoGen::instance = std::make_shared<MovingBlock_AutoGen>();

	const std::shared_ptr<MovingBlock_AutoGen> &MovingBlock_AutoGen::getInstance()
	{
		return instance;
	}

	MovingBlock_AutoGen::MovingBlock_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	std::shared_ptr<AutoGen_Parameters> MovingBlock_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<MovingBlock_Parameters> Params = std::make_shared<MovingBlock_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void MovingBlock_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void MovingBlock_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	void MovingBlock_AutoGen::SetMoveType( const std::shared_ptr<MovingBlock> &mblock, float Displacement, MovingBlock_Parameters::MotionType mtype, const std::shared_ptr<Rand> &Rnd )
	{
		switch ( mtype )
		{
			case MovingBlock_Parameters::MotionType_VERTICAL:
				mblock->MoveType = MovingBlockMoveType_LINE;
				mblock->Displacement = Vector2( 0,.5f * Displacement );
				break;

			case MovingBlock_Parameters::MotionType_HORIZONTAL:
				mblock->MoveType = MovingBlockMoveType_LINE;
				mblock->Displacement = Vector2( Displacement, 0 );
				break;

			case MovingBlock_Parameters::MotionType_CROSS:
				mblock->MoveType = MovingBlockMoveType_LINE;
				if ( Rnd->Rnd->NextDouble() > .5f )
					mblock->Displacement = Vector2( Displacement,.5f * Displacement );
				else
					mblock->Displacement = Vector2( -Displacement,.5f * Displacement );
				break;

			case MovingBlock_Parameters::MotionType_CIRLCES:
				mblock->MoveType = MovingBlockMoveType_CIRCLE;
				mblock->Displacement = Vector2( Displacement *.5f, Displacement *.5f );
				mblock->Displacement.X *= Rnd->Rnd->Next( 0, 2 ) * 2 - 1;
				break;

			case MovingBlock_Parameters::MotionType_AA:
				if ( Rnd->Rnd->NextDouble() > .5f )
					SetMoveType( mblock, Displacement, MovingBlock_Parameters::MotionType_VERTICAL, Rnd );
				else
					SetMoveType( mblock, Displacement, MovingBlock_Parameters::MotionType_HORIZONTAL, Rnd );
				break;

			case MovingBlock_Parameters::MotionType_STRAIGHT:
				if ( Rnd->Rnd->NextDouble() > .5f )
					SetMoveType( mblock, Displacement, MovingBlock_Parameters::MotionType_CROSS, Rnd );
				else
					SetMoveType( mblock, Displacement, MovingBlock_Parameters::MotionType_AA, Rnd );
				break;

			case MovingBlock_Parameters::MotionType_ALL:
				if ( Rnd->Rnd->NextDouble() > .5f )
					SetMoveType( mblock, Displacement, MovingBlock_Parameters::MotionType_STRAIGHT, Rnd );
				else
					SetMoveType( mblock, Displacement, MovingBlock_Parameters::MotionType_CIRLCES, Rnd );
				break;
		}
	}

	std::shared_ptr<ObjectBase> MovingBlock_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get MovingBlock parameters
		std::shared_ptr<MovingBlock_Parameters> Params = std::static_pointer_cast<MovingBlock_Parameters>( level->getStyle()->FindParams( MovingBlock_AutoGen::getInstance() ) );

		Vector2 size = Vector2( Params->Size.GetVal( pos ), 0 );
		switch ( Params->Aspect )
		{
			case MovingBlock_Parameters::AspectType_SQUARE:
				size.Y = size.X;
				break;
			case MovingBlock_Parameters::AspectType_THIN:
				size.Y = 30;
				break;
			case MovingBlock_Parameters::AspectType_TALL:
				size.Y = pos.Y - BL.Y + 200;
				break;
		}

		Vector2 offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ),
								  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) - size.Y ) );

		std::shared_ptr<MovingBlock> mblock = std::static_pointer_cast<MovingBlock>( level->getRecycle()->GetObject(ObjectType_MOVING_BLOCK, true) );
		mblock->Init( pos + offset, size, level );

		mblock->Period = static_cast<int>( Params->Period.GetVal( pos ) );

		mblock->Offset = level->getStyle()->GetOffset( mblock->Period, pos, level->getStyle()->PendulumOffsetType );


		float Displacement = Params->Range.GetVal( pos );
		SetMoveType( mblock, Displacement, Params->Motion, level->getRnd() );

		// If the block is too low make sure it's path is horizontal
		if ( pos.Y < BL.Y + 400 )
			SetMoveType( mblock, Displacement, MovingBlock_Parameters::MotionType_HORIZONTAL, level->getRnd() );

		mblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		mblock->getBlockCore()->GenData.EdgeSafety = static_cast<float>( GenData->Get(DifficultyParam_EDGE_SAFETY, pos) );

		if ( level->getStyle()->RemoveBlockOnOverlap )
			mblock->getBlockCore()->GenData.RemoveIfOverlap = true;

		Tools::EnsureBounds_X( mblock, TR, BL );

		level->AddBlock( mblock );

		return mblock;
	}
}
