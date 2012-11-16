#include <global_header.h>


namespace CloudberryKingdom
{

	void MovingPlatform::ElevatorTileInfo::InitializeInstanceFields()
	{
		Group = PieceQuad::ElevatorGroup;
	}

	const std::shared_ptr<BlockEmitter_Parameters> &MovingPlatform::getMyParams() const
	{
		return static_cast<BlockEmitter_Parameters*>( getCore()->MyLevel->Style_FIND_PARAMS(BlockEmitter_AutoGen::getInstance()) );
	}

	bool MovingPlatform::PermissionToUse()
	{
		if ( getMyParams()->MyStyle == BlockEmitter_Parameters::Style_SEPARATED )
		{
			// Don't let the computer use another elevator too soon after using another one.
			if ( getCore()->MyLevel->CurPhsxStep - getMyParams()->LastUsedTimeStamp > 5 )
				return true;
			else
				return false;
		}
		else
		{
			return true;
		}
	}

	void MovingPlatform::LandedOn( const std::shared_ptr<Bob> &bob )
	{
		if ( getCore()->MyLevel->PlayMode == 2 )
		{
			getMyParams()->LastUsedTimeStamp = getCore()->MyLevel->CurPhsxStep;

			if ( getMyParams()->MyStyle == BlockEmitter_Parameters::Style_SEPARATED )
				getCore()->GenData.EdgeJumpOnly = true;
		}
	}

	void MovingPlatform::OnUsed()
	{
		getMyParams()->LastUsedTimeStamp = getCore()->MyLevel->CurPhsxStep;
		Parent->StampAsUsed( getCore()->MyLevel->CurPhsxStep );
	}

	void MovingPlatform::OnMarkedForDeletion()
	{
		if ( Parent != 0 )
			Parent->RemovePlatform( this );

		if ( !getCore()->DeletedByBob )
			return;

		if ( Parent != 0 )
		{
			Parent->getCore()->DeletedByBob = true;
			Parent->CollectSelf();
		}
	}

	void MovingPlatform::MakeNew()
	{
		MyMoveType = MoveType_NORMAL;

		getCore()->Init();
		getBlockCore()->MyType = ObjectType_MOVING_PLATFORM;
		getCore()->DrawLayer = 4;

		MyBox->TopOnly = true;
	}

	void MovingPlatform::Release()
	{
		BlockBase::Release();

		Parent.reset();
	}

	MovingPlatform::MovingPlatform( bool BoxesOnly )
	{
		MyBox = std::make_shared<AABox>();
		MyDraw = std::make_shared<NormalBlockDraw>();

		getCore()->BoxesOnly = BoxesOnly;
		MakeNew();
	}

	void MovingPlatform::Init( Vector2 center, Vector2 size, const std::shared_ptr<Level> &level, BlockEmitter_Parameters::BoxStyle boxstyle )
	{
		MyBoxStyle = boxstyle;

		if ( boxstyle == BlockEmitter_Parameters::BoxStyle_FULL_BOX )
			getBox()->TopOnly = false;

		//// Not TopOnly if hero is a spaceship.
		//if (Parent != null && Parent.Core.MyLevel.DefaultHeroType is BobPhsxSpaceship && Box.TopOnly)
		//{
		//    Box.TopOnly = false;
		//}

		Range = Vector2( 1800, 1800 );

		Active = true;

		getBlockCore()->Layer = .3f;

		BlockBase::Init( center, size, level, level->getInfo()->Elevators->Group );
		Reset( level->BoxesOnly );

		getCore()->RemoveOnReset = true;
		getBlockCore()->HitHead = true;
	}

	void MovingPlatform::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;

		getBox()->Move(shift);
	}

	void MovingPlatform::Reset( bool BoxesOnly )
	{
		BlockBase::Reset( BoxesOnly );

		Active = true;

		getBlockCore()->Data = getBlockCore()->StartData;

		MyBox->Current->Center = getBlockCore()->StartData.Position;
		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();
	}

	void MovingPlatform::PhsxStep()
	{
		if ( !Active )
			return;

		if ( getBlockCore()->Data.Position.X > getBlockCore()->MyLevel->getMainCamera()->TR.X + Range.X || getBlockCore()->Data.Position.X < getBlockCore()->MyLevel->getMainCamera()->BL.X - Range.X || getBlockCore()->Data.Position.Y > getBlockCore()->MyLevel->getMainCamera()->TR.Y + Range.Y || getBlockCore()->Data.Position.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y - Range.Y )
		{
			CollectSelf();

			Active = false;
			return;
		}

		/*
		int Period = 180;
		int Step = (Core.GetPhsxStep() + Offset) % Period;
		float t = (float)Step / Period;*/

		int Step = getCore()->GetPhsxStep() - Offset;
		int Period = 180;
		float t = static_cast<float>( Step ) / Period;

		//MyBox.Target.Center = MyBox.Current.Center + CoreData.Data.Velocity;
		MyBox->Target->Center = getCore()->StartData.Position + Step * getBlockCore()->Data.Velocity;

		switch ( MyMoveType )
		{
			case MoveType_SINE:
				MyBox->Target->Center.X = getCore()->StartData.Position.X + Amp * static_cast<float>(cos(2 * M_PI * t));
				break;

			case MoveType_NORMAL:
				break;
		}

		//CoreData.Data.Velocity += CoreData.Data.Acceleration;
		getBlockCore()->Data.Position = MyBox->Target->Center;

		MyBox->SetTarget( MyBox->Target->Center, MyBox->Current->Size );

		if ( getCore()->WakeUpRequirements )
		{
			MyBox->SwapToCurrent();
			getCore()->WakeUpRequirements = false;
		}
	}

	void MovingPlatform::PhsxStep2()
	{
		if ( !Active )
			return;

		MyBox->SwapToCurrent();
	}

	void MovingPlatform::Draw()
	{
		if ( !Active || ( Parent != 0 && !Parent->Active ) )
			return;

		Vector2 BL = MyBox->Current->BL; //MyQuad.BL();
		if ( MyBox->Current->BL.X > getBlockCore()->MyLevel->getMainCamera()->TR.X || MyBox->Current->BL.Y > getBlockCore()->MyLevel->getMainCamera()->TR.Y )
			return;
		Vector2 TR = MyBox->Current->TR; // MyQuad.TR();
		if ( MyBox->Current->TR.X < getBlockCore()->MyLevel->getMainCamera()->BL.X || MyBox->Current->TR.Y < getBlockCore()->MyLevel->getMainCamera()->BL.Y )
			return;

		if ( Tools::DrawBoxes )
			MyBox->Draw( Tools::QDrawer, Color::Olive, 15 );

		if ( getBlockCore()->BoxesOnly )
			return;

		if ( Tools::DrawGraphics )
		{
			MyDraw->Update();
			MyDraw->Draw();
		}
	}

	void MovingPlatform::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		std::shared_ptr<MovingPlatform> BlockA = dynamic_cast<MovingPlatform*>( A );
		getBlockCore()->Clone(A->getCore());

		Parent = BlockA->Parent;

		Amp = BlockA->Amp;
		Offset = BlockA->Offset;

		Range = BlockA->Range;

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size, A->getMyLevel(), MyBoxStyle );

		Active = BlockA->Active;
	}
}
