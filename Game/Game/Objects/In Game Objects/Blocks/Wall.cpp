#include <global_header.h>


namespace CloudberryKingdom
{

	void Wall::WallTileInfo::InitializeInstanceFields()
	{
		Sprite = std::make_shared<SpriteInfo>( 0 );
	}

	std::shared_ptr<Wall> Wall::MakeWall( LevelGeometry geometry )
	{
		std::shared_ptr<Wall> wall = std::make_shared<Wall>( false );
		wall->MakeNew();
		wall->Horizontal = geometry == LevelGeometry_RIGHT;

		wall->Init();
		wall->StampAsUsed( 0 );
		wall->Speed = 15;
		wall->InitialDelay = 78;


		if ( !wall->Horizontal )
		{
			wall->MoveBack( Vector2( 0, 30000 ) );
			wall->Speed *= .7f;
		}

		return wall;
	}

	void Wall::Spikify()
	{
		Spiked = true;

		if ( Horizontal )
		{
			MoveBack( Vector2( -90, 0 ) );
		}
		else
		{
			MoveBack( Vector2( 0, -90 ) );
		}

		// Spikes
		int count = 0;
		if ( Horizontal )
		{
			for ( float y = getBox()->BL.Y; y < getBox()->TR.Y; y += 100 )
			{
				MakeSpike( count, y );

				count++;
			}
		}
		else
		{
			for ( float x = getBox()->BL.X; x < getBox()->TR.X; x += 100 )
			{
				MakeSpike( count, x );

				count++;
			}
		}
	}

	void Wall::MakeSpike( int count, float pos )
	{
		std::shared_ptr<Spike> spike = static_cast<Spike*>( getCore()->MyLevel->getRecycle()->GetObject(ObjectType_SPIKE, false) );
		spike->Init( Vector2(), getMyLevel() );

		if ( Horizontal )
		{
			float SpikeSideOffset = getInfo()->Spikes->SideOffset;
			float x = getBox()->Target->TR.X + SpikeSideOffset;
			spike->SetDir( 3 );
			spike->setPos( Vector2( x, pos ) );
		spike->getCore()->StartData.Position = spike->getPos();
		}
		else
		{
			float SpikeTopOffset = getInfo()->Spikes->TopOffset;
			float y = getBox()->Target->TR.Y + SpikeTopOffset;
			spike->SetDir( 0 );
			spike->setPos( Vector2( pos, y ) );
		spike->getCore()->StartData.Position = spike->getPos();
		}


		spike->SetPeriod( 100 );

		spike->SetPeriod( 50 );
		spike->Offset = count % 2 == 0 ? 0 : 50 / 2;

		spike->SetParentBlock( shared_from_this() );
		getCore()->MyLevel->AddObject(spike);
	}

	void Wall::MakeNew()
	{
		getBlockCore()->Init();
		getBlockCore()->MyType = ObjectType_WALL;
		getCore()->DrawLayer = 9;

		Active = false;

		getBlockCore()->Layer = .7f;

		getCore()->RemoveOnReset = false;
		getBlockCore()->HitHead = true;

		getCore()->EditHoldable = getCore()->Holdable = true;
	}

	Wall::Wall( bool BoxesOnly )
	{
		InitializeInstanceFields();
		MyBox = std::make_shared<AABox>();
		MyQuad = std::make_shared<QuadClass>( _T( "White" ), 100, true );

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	void Wall::ResetPieces()
	{
		if ( getCore()->MyLevel == 0 )
			return;

		MyQuad->Set( getInfo()->Walls->Sprite );
	}

	void Wall::Init()
	{
		Vector2 size, center;

		if ( Horizontal )
		{
			size = Vector2( 2000 * 3, 2000 );
			center = -Vector2( size.X, 0 );
		}
		else
		{
			size = Vector2( 2000, 2000 * 3 );
			center = -Vector2( 0, size.Y );
		}

		MyBox->Initialize( center, size );
		getCore()->Data.Position = getBlockCore()->Data.Position = getBlockCore()->StartData.Position = center;

		if ( !getCore()->BoxesOnly )
			ResetPieces();

		Update();
	}

	void Wall::MoveBack( Vector2 shift )
	{
		getCore()->Data.Position += shift;
		if ( Horizontal )
			StartOffset += shift.X;
		else
			StartOffset += shift.Y;

		getBox()->Move(shift);

		Update();
	}

	void Wall::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;
		StartOffset += shift.X;

		getBox()->Move(shift);

		Update();
	}

	void Wall::Reset( bool BoxesOnly )
	{
		getBlockCore()->BoxesOnly = BoxesOnly;

		if ( !getCore()->BoxesOnly )
			ResetPieces();

		getCore()->Data = getBlockCore()->Data = getBlockCore()->StartData;
		if ( Horizontal )
			getCore()->Data.Position += Vector2(StartOffset, 0);
		else
			getCore()->Data.Position += Vector2(0, StartOffset);

		MyBox->Current->Center = getCore()->Data.Position;
		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();

		Update();

		Active = false;
	}

	void Wall::Shake()
	{
		int Step = getCore()->MyLevel->CurPhsxStep;
		if ( Step < ShakeLength )
			CurShakeIntensity = ShakeIntensity;
		else
			CurShakeIntensity *= .98f;
		CoreMath::Restrict( MinShakeIntensity, ShakeIntensity, CurShakeIntensity );

		int Wait = 2;
		if ( CurShakeIntensity < MinShakeIntensity + 2 )
			Wait = 4;

		if ( Step % Wait == 0 )
			Offset = Vector2( getMyLevel()->getRnd()->RndFloat(-CurShakeIntensity, CurShakeIntensity), getMyLevel()->getRnd()->RndFloat(-CurShakeIntensity, CurShakeIntensity) );
	}

	Vector2 Wall::CalcPosition( float t )
	{
		if ( t < InitialDelay )
			return getCore()->Data.Position;

		if ( Horizontal )
			getCore()->Data.Velocity.X = CoreMath::Restrict(0, Speed, getCore()->Data.Velocity.X + Accel);
		else
			getCore()->Data.Velocity.Y = CoreMath::Restrict(0, Speed, getCore()->Data.Velocity.Y + Accel);

		if ( getPos().X > getCam()->getPos().X - 5350 )
		{
			getCore()->Data.Velocity.X *= .825f;
			if ( getCore()->Data.Velocity.X < 1 )
				getCore()->Data.Velocity.X = 0;
		}

		return getCore()->Data.Position + getCore()->Data.Velocity;
	}

	void Wall::DoInteraction( const std::shared_ptr<Bob> &bob )
	{
		bob->Box->CalcBounds();
		float dif;
		Vector2 difvec;

		if ( Horizontal )
		{
			dif = getBox()->Current->TR.X - 10 - bob->Box->BL.X;
			difvec = Vector2( dif, 0 );
		}
		else
		{
			dif = getBox()->Current->TR.Y - 10 - bob->Box->BL.Y;
			difvec = Vector2( 0, dif );
		}


		switch ( MyBufferType )
		{
			case BufferType_PUSH:
				if ( dif > 0 )
					bob->Move( difvec );
					break;

			case BufferType_SPACE:
				if ( getCore()->MyLevel->PlayMode != 2 )
				{
					if ( dif > 0 )
						bob->Move( difvec );
				}
				else
				{
					dif += Space;
					if ( dif > 0 )
						MoveBack( -difvec );
				}
				break;
		}
	}

	void Wall::PhsxStep()
	{
		if ( getCore()->MyLevel->PlayMode == 0 )
		{
			if ( !Spiked )
				Spikify();
			Shake();
		}

		getCore()->SkippedPhsx = false;
		Active = true;

		if ( !getCore()->Held )
			getCore()->Data.Position = CalcPosition(getCore()->GetPhsxStep());

		MyBox->Target->Center = getCore()->Data.Position + Offset;

		Update();

		MyBox->SetTarget( MyBox->Target->Center, MyBox->Current->Size );

		MyBox->CalcBounds();
		for ( BobVec::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
			DoInteraction( *bob );
	}

	void Wall::PhsxStep2()
	{
		if ( !Active )
			return;

		MyBox->SwapToCurrent();
	}

	void Wall::Update()
	{
		if ( getBlockCore()->BoxesOnly )
			return;
	}

	void Wall::Draw()
	{
		Update();

		if ( Tools::DrawBoxes )
			MyBox->Draw( Tools::QDrawer, Color::Olive, 15 );

		if ( Tools::DrawGraphics )
		{
			if ( !getBlockCore()->BoxesOnly )
			{
				MyQuad->setPos( getPos() + Offset );
				MyQuad->Draw();
				Tools::QDrawer->Flush();
			}

			getBlockCore()->Draw();
		}
	}

	void Wall::Extend( Side side, float pos )
	{
		MyBox->Invalidated = true;

		MyBox->Extend( side, pos );

		Update();

		if ( !getCore()->BoxesOnly )
			ResetPieces();

		getBlockCore()->StartData.Position = MyBox->Current->Center;

		ResetPieces();
	}

	void Wall::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		std::shared_ptr<Wall> BlockA = dynamic_cast<Wall*>( A );

		Init();

		getCore()->Clone(A->getCore());

		Speed = BlockA->Speed;
	}

	void Wall::InitializeInstanceFields()
	{
		Spiked = false;
		Speed = 16.5f;
		Accel = .2f;
		InitialDelay = 60;
		StartOffset = -400;
		ShakeIntensity = 25.5f;
		MinShakeIntensity = 7.5f;
		ShakeLength = 50;
		MyBufferType = BufferType_SPACE;
		Space = 40;
	}
}
