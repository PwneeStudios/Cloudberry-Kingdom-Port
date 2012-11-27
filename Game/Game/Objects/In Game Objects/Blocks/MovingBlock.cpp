#include <global_header.h>


namespace CloudberryKingdom
{

	MovingBlock::MovingBlockTileInfo::MovingBlockTileInfo()
	{
		InitializeInstanceFields();
	}

	void MovingBlock::MovingBlockTileInfo::InitializeInstanceFields()
	{
		Group = PieceQuad::MovingGroup;
	}

	void MovingBlock::MakeNew()
	{
		getBlockCore()->Init();
		getBlockCore()->MyType = ObjectType_MOVING_BLOCK;
		getCore()->DrawLayer = 3;

		Displacement = Vector2( 200, 0 );
		Period = 400;
		Offset = 0;

		Active = false;

		getBlockCore()->Layer = .7f;

		getCore()->RemoveOnReset = false;
		getBlockCore()->HitHead = true;

		getCore()->EditHoldable = getCore()->Holdable = true;
	}

	MovingBlock::MovingBlock( bool BoxesOnly )
	{
		MyBox = std::make_shared<AABox>();
		MyDraw = std::make_shared<NormalBlockDraw>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	Vector2 MovingBlock::TR_Bound()
	{
		Vector2 max = Vector2::Max( Vector2::Max( CalcPosition( 0 ), CalcPosition( .5f ) ), Vector2::Max( CalcPosition( 0.25f ), CalcPosition( .75f ) ) );
		return max;
	}

	Vector2 MovingBlock::BL_Bound()
	{
		Vector2 min = Vector2::Min( Vector2::Min( CalcPosition( 0 ), CalcPosition( .5f ) ), Vector2::Min( CalcPosition( 0.25f ), CalcPosition( .75f ) ) );

		return min;
	}

	void MovingBlock::ResetPieces()
	{
		if ( getInfo()->MovingBlocks->Group != 0 )
		{
			if ( MyDraw->MyTemplate != 0 )
			{
				MyDraw->MyTemplate = getCore()->getMyTileSet()->GetPieceTemplate(this, getRnd(), getInfo()->MovingBlocks->Group);
				MyDraw->Init( this, MyDraw->MyTemplate, false );
			}
		}
	}

	void MovingBlock::Init( Vector2 center, Vector2 size, const std::shared_ptr<Level> &level )
	{
		BlockBase::Init( center, size, level, level->getInfo()->MovingBlocks->Group );
	}

	void MovingBlock::MoveToBounded( Vector2 shift )
	{
		Move( shift );
	}

	void MovingBlock::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;

		getBox()->Move(shift);
	}

	void MovingBlock::Reset( bool BoxesOnly )
	{
		BlockBase::Reset( BoxesOnly );

		getCore()->Data = getBlockCore()->Data = getBlockCore()->StartData;

		MyBox->Current->Center = getBlockCore()->StartData.Position;
		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();

		Active = false;
	}

	Vector2 MovingBlock::CalcPosition( float t )
	{
		switch ( MoveType )
		{
			case MovingBlockMoveType_LINE:
				return getBlockCore()->StartData.Position + Displacement * static_cast<float>(cos(2 * M_PI * t));

			case MovingBlockMoveType_CIRCLE:
				return getBlockCore()->StartData.Position + Vector2(Displacement.X * static_cast<float>(cos(2 * M_PI * t)), Displacement.Y * static_cast<float>(sin(2 * M_PI * t)));
		}

		return getBlockCore()->StartData.Position;
	}

	void MovingBlock::PhsxStep()
	{
		if ( !getCore()->Held )
		{
			float Step = CoreMath::Modulo( getCore()->GetIndependentPhsxStep() + Offset, static_cast<float>(Period) );
			getCore()->Data.Position = CalcPosition(static_cast<float>(Step) / Period);
		}

		Vector2 PhsxCutoff = Vector2( 1250 );
		if ( getCore()->MyLevel->BoxesOnly )
			PhsxCutoff = Vector2( 500, 500 );
		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, PhsxCutoff) )
		{
			Active = false;
			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

		MyBox->Target->Center = getCore()->Data.Position;

		MyBox->SetTarget( MyBox->Target->Center, MyBox->Current->Size );
		if ( !Active )
			MyBox->SwapToCurrent();

		Active = true;
	}

	void MovingBlock::Draw()
	{
		bool DrawSelf = true;
		if ( !getCore()->Held )
		{
			if ( !Active )
				return;

			if ( MyBox->Current->BL.X > getBlockCore()->MyLevel->getMainCamera()->TR.X + 50 || MyBox->Current->BL.Y > getBlockCore()->MyLevel->getMainCamera()->TR.Y + 100 )
				DrawSelf = false;
			if ( MyBox->Current->TR.X < getBlockCore()->MyLevel->getMainCamera()->BL.X - 50 || MyBox->Current->TR.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y - 100 )
				DrawSelf = false;
		}

		if ( DrawSelf )
		{
			if ( Tools::DrawBoxes )
				MyBox->DrawFilled( Tools::QDrawer, Color::DarkBlue );
		}

		if ( Tools::DrawGraphics )
		{
			if ( DrawSelf && !getBlockCore()->BoxesOnly )
			{
				MyDraw->Update();
				MyDraw->Draw();
			}
		}

		getBlockCore()->Draw();
	}

	void MovingBlock::Extend( Side side, float pos )
	{
		MyBox->Invalidated = true;

		MyBox->Extend( side, pos );

		if ( !getCore()->BoxesOnly )
			ResetPieces();

		getBlockCore()->StartData.Position = MyBox->Current->Center;

		ResetPieces();
	}

	void MovingBlock::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		std::shared_ptr<MovingBlock> BlockA = dynamic_cast<MovingBlock*>( A );

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size, BlockA->getMyLevel() );

		getCore()->Clone(A->getCore());

		MoveType = BlockA->MoveType;
		Period = BlockA->Period;
		Offset = BlockA->Offset;
		Displacement = BlockA->Displacement;
	}
}
