#include <global_header.h>

namespace CloudberryKingdom
{

	Vector2 Camera::getPos()
	{
		return Data.Position;
	}

	void Camera::setPos( const Vector2 &value )
	{
		Data.Position = value;
	}

	Vector2 Camera::PosToScreenPos( Vector2 pos, float parallax )
	{
		return ( pos - getPos() ) * parallax;
	}

	const Vector2 &Camera::getZoom() const
	{
		return _Zoom;
	}

	void Camera::setZoom( const Vector2 &value )
	{
		_Zoom = value;
	}

	const Vector2 &Camera::getScreenSize() const
	{
		return 2 * Vector2( ScreenWidth, ScreenHeight );
	}

	void Camera::Release()
	{
		MyLevel.reset();
		MyZone.reset();

		FancyPos = FancyZoom = 0;
	}

	void Camera::Move( Vector2 shift )
	{
		Data.Position += shift;
		Target += shift;

		TR += shift;
		BL += shift;
		TRCamBound += shift;
		BLCamBound += shift;

		PrevPos += shift;
		PrevPrevPos += shift;
	}

	void Camera::Clone( const std::shared_ptr<Camera> &cam )
	{
		Clone( cam, false );
	}

	void Camera::Clone( const std::shared_ptr<Camera> &cam, bool DataOnly )
	{
		MyPhsxType = cam->MyPhsxType;

		UseEffective = cam->UseEffective;
		EffectivePos = cam->EffectivePos;
		EffectiveZoom = cam->EffectiveZoom;

		Data = cam->Data;
		PrevPos = cam->PrevPos;
		Speed = cam->Speed;
		Target = cam->Target;
		setZoom( cam->getZoom() );
		ScreenWidth = cam->ScreenWidth;
		ScreenHeight = cam->ScreenHeight;
		AspectRatio = cam->AspectRatio;
		TR = cam->TR;
		BL = cam->BL;
		TRCamBound = cam->TRCamBound;
		BLCamBound = cam->BLCamBound;
		Shaking = cam->Shaking;
		ShakingIntensity = cam->ShakingIntensity;
		ShakingSaveZoom = cam->ShakingSaveZoom;
		ShakingSavePos = cam->ShakingSavePos;
		VertexCam = cam->VertexCam;

		// Clone the zone if the cameras are in the same level
		if ( !DataOnly )
		{
			if ( MyLevel == 0 )
				MyLevel = cam->MyLevel;
			if ( MyLevel == cam->MyLevel )
				MyZone = cam->MyZone;
		}
	}

	void Camera::MakeFancyPos()
	{
		if ( FancyPos != 0 )
			FancyPos->Release();
		FancyPos = std::make_shared<FancyVector2>();
		FancyPos->RelVal = Data.Position;

		if ( FancyZoom != 0 )
			FancyZoom->Release();
		FancyZoom = std::make_shared<FancyVector2>();
		FancyZoom->RelVal = getZoom();
	}

	Vector2 Camera::GetSize()
	{
		return Vector2( GetWidth(), GetHeight() );
	}

	float Camera::GetHeight()
	{
		if ( LastUpdate != Tools::PhsxCount )
			Update();
		return TR.Y - BL.Y;
	}

	float Camera::GetWidth()
	{
		if ( LastUpdate != Tools::PhsxCount )
			Update();
		return TR.X - BL.X;
	}

	void Camera::Update()
	{
		LastUpdate = Tools::PhsxCount;

		TR.X = Data.Position.X + AspectRatio / getZoom().X;
		TR.Y = Data.Position.Y + 1 / getZoom().Y;

		BL.X = Data.Position.X - AspectRatio / getZoom().X;
		BL.Y = Data.Position.Y - 1 / getZoom().Y;

		if ( UseEffective )
		{
			EffectiveTR.X = EffectivePos.X + AspectRatio / EffectiveZoom.X;
			EffectiveTR.Y = EffectivePos.Y + 1 / EffectiveZoom.Y;

			EffectiveBL.X = EffectivePos.X - AspectRatio / EffectiveZoom.X;
			EffectiveBL.Y = EffectivePos.Y - 1 / EffectiveZoom.Y;
		}
		else
		{
			EffectivePos = Data.Position;
			EffectiveZoom = getZoom();
			EffectiveTR = TR;
			EffectiveBL = BL;
		}
	}

	Camera::Camera()
	{
		InitializeInstanceFields();
		Init( Tools::Device->PresentationParameters->BackBufferWidth, Tools::Device->PresentationParameters->BackBufferHeight );
	}

	Camera::Camera( int width, int height )
	{
		InitializeInstanceFields();
		Init( width, height );
	}

	void Camera::Init( int width, int height )
	{
		// FIXED DIMENSIONS!!
		width = 1280;
		height = 720;

		Speed = 30;

		BLCamBound = Vector2( -1000000, -1000000 );
		TRCamBound = Vector2( 1000000, 1000000 );

		ScreenWidth = width;
		ScreenHeight = height;
		Data.Position = Vector2( 0, 0 );
		setZoom( Vector2( .001f,.001f ) );
	ShakingSaveZoom = getZoom();
		Offset = Vector2( width / 2, height / 2 );
		AspectRatio = static_cast<float>( ScreenWidth ) / static_cast<float>( ScreenHeight );
	}

	Camera::Camera( const std::shared_ptr<Camera> &cam )
	{
		InitializeInstanceFields();
		Clone( cam );
		Speed = cam->Speed;

		ScreenHeight = cam->ScreenHeight;
		ScreenWidth = cam->ScreenWidth;
		Data.Position = cam->Data.Position;
		setZoom( cam->getZoom() );
		Offset = cam->Offset;
		AspectRatio = cam->AspectRatio;
		TR = cam->TR;
		BL = cam->BL;

		BLCamBound = cam->BLCamBound;
		TRCamBound = cam->TRCamBound;
	}

	void Camera::StartShake()
	{
		StartShake( 1, -1 );
	}

	void Camera::StartShake( float Intensity )
	{
		StartShake( Intensity, -1 );
	}

	void Camera::StartShake( float Intensity, int Length )
	{
		StartShake( Intensity, Length, true );
	}

	void Camera::StartShake( float Intensity, int Length, bool Sound )
	{
		//if (Sound)
		//    Tools.Sound("Rumble_Short").Play();

		ShakeCount = 0;
		ShakeLength = Length;

		if ( !Shaking )
		{
			Shaking = true;
			ShakingSaveZoom = getZoom();
			ShakingSavePos = Data.Position;
		}

		ShakingIntensity = Intensity;
	}

	void Camera::EndShake()
	{
		Shaking = false;
		setZoom( ShakingSaveZoom );
		Data.Position = ShakingSavePos;
		ShakeOffset = Vector2();
	}

	bool Camera::OnScreen( Vector2 pos )
	{
		return OnScreen( pos, Vector2( 200, 600 ) );
	}

	bool Camera::OnScreen( Vector2 pos, Vector2 GraceSize )
	{
		if ( pos.X > TR.X + GraceSize.X )
			return false;
		if ( pos.X < BL.X - GraceSize.X )
			return false;
		if ( pos.Y > TR.Y + GraceSize.Y )
			return false;
		if ( pos.Y < BL.Y - GraceSize.Y )
			return false;
		return true;
	}

	bool Camera::OnScreen( Vector2 pos, float GraceSize )
	{
		if ( pos.X > TR.X + GraceSize )
			return false;
		if ( pos.X < BL.X - GraceSize )
			return false;
		if ( pos.Y > TR.Y + GraceSize )
			return false;
		if ( pos.Y < BL.Y - GraceSize )
			return false;
		return true;
	}

	bool Camera::OnScreen( Vector2 bl, Vector2 tr, float GraceSize )
	{
		if ( bl.X > TR.X + GraceSize )
			return false;
		if ( tr.X < BL.X - GraceSize )
			return false;
		if ( bl.Y > TR.Y + GraceSize )
			return false;
		if ( tr.Y < BL.Y - GraceSize )
			return false;
		return true;
	}

	Vector4 Camera::GetVertex()
	{
		if ( UseEffective )
			return Vector4( EffectivePos.X, EffectivePos.Y, EffectiveZoom.X, EffectiveZoom.Y );
		else
			return Vector4( Data.Position.X, Data.Position.Y, getZoom().X, getZoom().Y );
	}

	void Camera::SetVertexCamera()
	{
		VertexCam = GetVertex();
		Tools::EffectWad->SetCameraPosition( VertexCam );
	}

	void Camera::SetVertexZoom( float factor )
	{
		SetVertexZoom( Vector2( factor ) );
	}

	void Camera::SetVertexZoom( Vector2 factor )
	{
		VertexCam = GetVertex();
		VertexCam.Z *= factor.X;
		VertexCam.W *= factor.Y;

		Tools::EffectWad->SetCameraPosition( VertexCam );
	}

	void Camera::SetVertexCamera( Vector2 shift, Vector2 factor )
	{
		VertexCam = GetVertex();
		VertexCam.X += shift.X;
		VertexCam.Y += shift.Y;
		VertexCam.Z *= getZoom().X;
		VertexCam.W *= getZoom().Y;

		Tools::EffectWad->SetCameraPosition( VertexCam );
	}

	void Camera::SetToDefaultZoom()
	{
		HoldZoom = getZoom();
		setZoom( Vector2( .001f,.001f ) );
		SetVertexCamera();
		Update();
	}

	void Camera::RevertZoom()
	{
		setZoom( HoldZoom );
		SetVertexCamera();
		Update();
	}

	Vector2 Camera::CurVel()
	{
		//return Data.Position - PrevPos;
		return PrevPos - PrevPrevPos;
	}

bool Camera::DisableOscillate = false;

	void Camera::PhsxStep()
	{
		Vector2 CurPos = Data.Position;
		Vector2 CurZoom = getZoom();
		if ( Shaking )
		{
			Data.Position -= ShakeOffset;
			//Zoom = ShakingSaveZoom;
		}
		if ( Oscillating && !DisableOscillate )
		{
			//OscillateOffset = new Vector2(0, 40 * (float)Math.Sin(.95f * Tools.t));
			OscillateOffset = Vector2( 0, 40 * static_cast<float>( sin( .95f * t ) ) );
			t += Tools::dt;
			Data.Position -= OscillateOffset;
		}

		if ( SpeedVel != 0 )
		{
			float dif = TargetSpeed - Speed;
			Speed += __min( SpeedVel, abs( dif ) ) * Math::Sign( dif );
		}

		switch ( MyPhsxType )
		{
			case Camera_PhsxType_WORLD_MAP:
				WorldMap_PhsxStep();
				break;

			case Camera_PhsxType_FIXED:
				Fixed_PhsxStep();
				break;

			case Camera_PhsxType_SIDE_LEVEL_UP:
			case Camera_PhsxType_SIDE_LEVEL_UP_RELAXED:
			case Camera_PhsxType_SIDE_LEVEL_DOWN:
			case Camera_PhsxType_SIDE_LEVEL_RIGHT:
				SideLevel_PhsxStep();
				break;

			case Camera_PhsxType_CENTER:
				Center_PhsxStep();
				break;
		}

		if ( Shaking )
		{
			ShakeCount++;
			Vector2 change = Data.Position + OscillateOffset + ShakeOffset - CurPos;
			ShakingSavePos += change;
			Data.Position = Data.Position + OscillateOffset + ShakeOffset;
			Update();

			// Fade out the intensity
			if ( ShakeCount > ShakeLength - 20 )
				ShakingIntensity *= .95f;

			// Check for shake end
			if ( ShakeLength > 0 && ShakeCount >= ShakeLength )
			{
				EndShake();
				Update();
			}
			else
			{
				if ( Tools::TheGame->DrawCount % 2 == 0 )
				{
					Data.Position = ShakingSavePos;
					ShakeOffset.X = ShakingIntensity * MyLevel->getRnd()->Rnd->Next(-70, 70);
					ShakeOffset.Y = ShakingIntensity * MyLevel->getRnd()->Rnd->Next(-70, 70);
					Data.Position += ShakeOffset;
					Update();
				}

				for ( int i = 0; i < 4; i++ )
				{
					if ( PlayerManager::Get( i )->Exists && PlayerManager::Get( i )->IsAlive )
					{
						Tools::SetVibration( static_cast<PlayerIndex>( i ), 1, 1, 10 );
					}
				}
			}
		}
		else
			if ( Oscillating && !DisableOscillate )
			{
				Data.Position = Data.Position + OscillateOffset;
				Update();
			}


		//PrevPos = HoldPrevPos;
		PrevPrevPos = PrevPos;
		PrevPos = Data.Position;
	}

	void Camera::SetPhsxType( Camera_PhsxType NewType )
	{
		if ( NewType != MyPhsxType )
		{
			switch ( NewType )
			{
			}

			MyPhsxType = NewType;
		}
	}

	void Camera::Fixed_PhsxStep()
	{
		if ( MyZone != 0 )
			MyZone->SetZoom( this );

		if ( FancyPos != 0 )
			Data.Position = FancyPos->Update();

		if ( FancyZoom != 0 )
			setZoom( FancyZoom->Update() );

		Update();
	}

	void Camera::WorldMap_PhsxStep()
	{
		//MyZone.Enforce(this);
		//float zoom = 0.00072f;
		//MyZone.Zoom = zoom / .001f;
		MyZone->SetZoom( this );

		Vector2 TR, BL;
		TR = Vector2( -10000000, -10000000 );
		BL = Vector2( 10000000, 10000000 );

		MaxPlayerSpeed = Vector2();

		int Count = 0;
		float TotalWeight = 0;
		Vector2 BobsCenter = Vector2();
		for ( std::vector<Bob*>::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
		{
			if ( PlayerManager::IsAlive( ( *bob )->MyPlayerIndex ) && ( *bob )->AffectsCamera && ( !( *bob )->DoNotTrackOffScreen || OnScreen( ( *bob )->getCore()->Data->Position ) ) || MyLevel->PlayMode != 0 )
			{
				Vector2 bpos = ( *bob )->getCore()->Data->Position;

				BobsCenter += bpos;

				TR = Vector2::Max( TR, ( *bob )->getCore()->Data->Position );
				BL = Vector2::Min( BL, ( *bob )->getCore()->Data->Position );

				Count++;
				TotalWeight += ( *bob )->CameraWeight;
				( *bob )->CameraWeight = CoreMath::Restrict( 0, 1, ( *bob )->CameraWeight + ( *bob )->CameraWeightSpeed );
			}
		}

		if ( Count > 0 )
			BobsCenter /= TotalWeight;
		else
			BobsCenter = Data.Position;
		Vector2 pos = BobsCenter;

		Vector2 ratio = Vector2( 1.35f, 1.05f );
		Vector2 ratio2 = Vector2( 1.65f, 1.9f );
		if ( pos.X > Target.X + ScreenWidth * ratio.X )
			Target.X += ScreenWidth * ratio2.X;
		if ( pos.X < Target.X - ScreenWidth * ratio.X )
			Target.X -= ScreenWidth * ratio2.X;
		if ( pos.Y > Target.Y + ScreenHeight * ratio.Y )
			Target.Y += ScreenHeight * ratio2.Y;
		if ( pos.Y < Target.Y - ScreenHeight * ratio.Y )
			Target.Y -= ScreenHeight * ratio2.Y;

		Target.X = CoreMath::Restrict( MyZone->Start.X, MyZone->End.X, Target.X );
		Target.Y = CoreMath::Restrict( MyZone->Start.Y, MyZone->End.Y, Target.Y );

		Vector2 CurMaxSpeed = Vector2::Max( Vector2( Speed ), 1.05f * MaxPlayerSpeed );

		CurMaxSpeed = Vector2( 60 );
		Data.Position.X += Math::Sign( Target.X - Data.Position.X ) * __min( .15f * abs( Target.X - Data.Position.X ), CurMaxSpeed.X );
		Data.Position.Y += Math::Sign( Target.Y - Data.Position.Y ) * __min( .15f * abs( Target.Y - Data.Position.Y ), CurMaxSpeed.Y );

		Update();
	}

	void Camera::Center_PhsxStep()
	{
		//if (MyZone != null)
		  //  Target = MyZone.Core.Data.Position;

		Vector2 vel = CurVel();
		Vector2 dif = Target - Data.Position;
		Vector2 TargetVel = dif;
		TargetVel.Normalize();

		float EffectiveSpeed = Vector2::Dot( vel, TargetVel );
		if ( 15 * EffectiveSpeed > dif.Length() || dif.Length() < 2 * Speed )
			vel = 1 / 16 * dif;
		else
		{
			TargetVel *= Speed;
			vel += .08f * ( TargetVel - vel );
		}

		Data.Position += vel;

		Update();
	}

	Vector2 Camera::BoxLimit_X( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift )
	{
		if ( Pos.X < BoxCenter.X - BoxSize.X + BoxShift.X )
			Pos.X = BoxCenter.X - BoxSize.X + BoxShift.X;
		if ( Pos.X > BoxCenter.X + BoxSize.X + BoxShift.X )
			Pos.X = BoxCenter.X + BoxSize.X + BoxShift.X;

		return Pos;
	}

	Vector2 Camera::BoxLimit_Y( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift )
	{
		if ( Pos.Y < BoxCenter.Y - BoxSize.Y + BoxShift.Y )
			Pos.Y = BoxCenter.Y - BoxSize.Y + BoxShift.Y;
		if ( Pos.Y > BoxCenter.Y + BoxSize.Y + BoxShift.Y )
			Pos.Y = BoxCenter.Y + BoxSize.Y + BoxShift.Y;

		return Pos;
	}

	Vector2 Camera::BoxLimitLeft( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift )
	{
		if ( Pos.X < BoxCenter.X - BoxSize.X + BoxShift.X )
			Pos.X = BoxCenter.X - BoxSize.X + BoxShift.X;

		return Pos;
	}

	Vector2 Camera::BoxLimitDown( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift )
	{
		if ( Pos.Y < BoxCenter.Y - BoxSize.Y + BoxShift.Y )
			Pos.Y = BoxCenter.Y - BoxSize.Y + BoxShift.Y;

		return Pos;
	}

	Vector2 Camera::BoxLimitUp( Vector2 Pos, Vector2 BoxCenter, Vector2 BoxSize, Vector2 BoxShift )
	{
		if ( Pos.Y > BoxCenter.Y + BoxSize.Y + BoxShift.Y )
			Pos.Y = BoxCenter.Y + BoxSize.Y + BoxShift.Y;

		return Pos;
	}

	void Camera::SideLevel_PhsxStep()
	{
		Vector2 TR, BL;
		TR = Vector2( -10000000, -10000000 );
		BL = Vector2( 10000000, 10000000 );

		MaxPlayerSpeed = Vector2();

		int Count = 0;
		float TotalWeight = 0;
		Vector2 BobsCenter = Vector2();
		for ( std::vector<Bob*>::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
		{
			if ( PlayerManager::IsAlive( ( *bob )->MyPlayerIndex ) && ( *bob )->AffectsCamera && ( !( *bob )->DoNotTrackOffScreen || OnScreen( ( *bob )->getCore()->Data->Position ) ) || MyLevel->PlayMode != 0 )
			{
				//MaxPlayerSpeed = Math.Max(MaxPlayerSpeed, bob.Core.Data.Velocity.Length());
				MaxPlayerSpeed = Vector2::Max( MaxPlayerSpeed, CoreMath::Abs( ( *bob )->getCore()->Data->Velocity ) );

				BobsCenter += ( *bob )->getCore()->Data->Position;

				//TR.X = Math.Max(TR.X, bob.Core.Data.Position.X);
				//TR.Y = Math.Max(TR.Y, bob.Core.Data.Position.Y);

				TR = Vector2::Max( TR, ( *bob )->getCore()->Data->Position );
				BL = Vector2::Min( BL, ( *bob )->getCore()->Data->Position );

				Count++;
				TotalWeight += ( *bob )->CameraWeight;
				( *bob )->CameraWeight = CoreMath::Restrict( 0, 1, ( *bob )->CameraWeight + ( *bob )->CameraWeightSpeed );
			}
		}


		if ( FollowCenter )
		{
			if ( Count > 0 )
				//BobsCenter /= Count;
				BobsCenter /= TotalWeight;
			else
				BobsCenter = Data.Position;
		}


		Vector2 BoxSize, BoxShift = Vector2();
		Vector2 Pos = TR;
		if ( FollowCenter )
			Pos = BobsCenter;

		if ( Count > 0 )
		{
			if ( RocketManCamera )
			{
				BoxSize = Vector2( 350, 1000 );
				if ( FollowCenter && Count > 1 )
					BoxSize.X = 50;
				float px = MyZone->GetProjectedPos( Data.Position ).X;
				float cx = MyZone->GetProjectedPos( Pos ).X;
				float tx;

				if ( px < cx - BoxSize.X )
				{
					tx = cx - BoxSize.X;
					Target = MyZone->FromProjected( Vector2( tx, 0 ) );
				}
				if ( px > cx + BoxSize.X )
				{
					tx = cx + BoxSize.X;
					Target = MyZone->FromProjected( Vector2( tx, 0 ) );
				}
			}
			else
			{
				// Old
				//Box = new Vector2(650, 1000);

				// Good for long rocketman
				// BoxSize = new Vector2(325, 1000); 
				// BoxShift = new Vector2(800, 0);


				if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_UP )
				{
					//BoxSize = new Vector2(450, 200);
					//BoxShift = new Vector2(250, 275);
					BoxSize = Vector2( 450, 330 );
					BoxShift = Vector2( 250, 400 );
				}
				else if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_UP_RELAXED )
				{
					BoxSize = Vector2( 450, 350 );
					BoxShift = Vector2( 250, 160 );
				}
				else if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_DOWN )
				{
					BoxSize = Vector2( 450, 250 );
					BoxShift = Vector2( 250, -800 );
				}
				else //if (MyPhsxType == Camera_PhsxType.SideLevel_Right)
				{
					BoxSize = Vector2( 450, 250 ); //1000);
					BoxShift = Vector2( 250, 250 );
				}

				if ( FollowCenter && Count > 1 )
					BoxSize.X = 50;

				// Single player: keep player nearly centered
				if ( Count <= 1 )
				{
					if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_RIGHT )
						Target = BoxLimit_X( Data.Position, Pos, BoxSize, BoxShift );
					else
						Target = BoxLimit_Y( Data.Position, Pos, BoxSize, BoxShift );
				}
				// Multiplayer: if all together, stay centered. Otherwise allow leading player to push ahead.
				else
				{
					if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_RIGHT )
						Target = BoxLimitLeft( Data.Position, BL, BoxSize, BoxShift );
					else if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_UP )
						Target = BoxLimitDown( Data.Position, BL, BoxSize, BoxShift );
					else if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_DOWN )
						Target = BoxLimitUp( Data.Position, BL, BoxSize, BoxShift );

					Vector2 Lead = Target;
					if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_DOWN )
					{
						Lead = BL;

						BoxSize = Vector2( 0, 500 );
						BoxShift = Vector2( 0, -250 );
					}
					else if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_UP )
					{
						Lead = TR;

						BoxSize = Vector2( 0, 500 );
						BoxShift = Vector2( 0, 100 );
					}
					else if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_UP_RELAXED )
					{
						Lead = TR;

						BoxSize = Vector2( 0, 600 );
						BoxShift = Vector2( 0, 0 );
					}
					else if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_RIGHT )
					{
						Lead = TR;

						BoxSize = Vector2( 650, 0 );
						BoxShift = Vector2( 0, 0 );
					}

					if ( MyPhsxType == Camera_PhsxType_SIDE_LEVEL_RIGHT )
						Target = BoxLimit_X( Target, Lead, BoxSize, BoxShift );
					else
						Target = BoxLimit_Y( Target, Lead, BoxSize, BoxShift );
				}
			}
		}

		if ( Count > 0 )
		{
			if ( MyZone != 0 )
			{
				if ( MyZone->FreeY )
				{
					//BoxSize = new Vector2(650, 300);
					BoxSize = Vector2( 650, 100 );
					if ( FollowCenter && Count > 1 )
						BoxSize.Y = 50;
					if ( Data.Position.Y < Pos.Y - BoxSize.Y )
						Target.Y = Pos.Y - BoxSize.Y;
					if ( Data.Position.Y > Pos.Y + BoxSize.Y )
						Target.Y = Pos.Y + BoxSize.Y;
				}

				MyZone->Enforce( this );
			}
		}

		//float CurMaxSpeed = Math.Max(Speed, 1.05f * MaxPlayerSpeed);
		//CurMaxSpeed = Math.Max(CurMaxSpeed, CurVel().X);

		Vector2 CurMaxSpeed = Vector2::Max( Vector2( Speed ), 1.05f * MaxPlayerSpeed );
		CurMaxSpeed = Vector2::Max( CurMaxSpeed, CurVel() );

		if ( MovingCamera )
		{
			float Retard = 1;
			if ( MyZone != 0 && Data.Position.X > MyZone->End.X )
				Retard = CoreMath::LerpRestrict( 1, 0, ( Data.Position.X - MyZone->End.X ) / 200 );
			Data.Position.X += __max( Retard * __min( MyLevel->CurPhsxStep *.1f, 15 ), Math::Sign( Target.X - Data.Position.X ) * __min( .15f * abs( Target.X - Data.Position.X ), CurMaxSpeed.X ) );
		}
		else
			Data.Position.X += Math::Sign( Target.X - Data.Position.X ) * __min( .15f * abs( Target.X - Data.Position.X ), CurMaxSpeed.X );

		Data.Position.Y += Math::Sign( Target.Y - Data.Position.Y ) * __min( .15f * abs( Target.Y - Data.Position.Y ), CurMaxSpeed.Y );


		Update();
	}

	void Camera::InitializeInstanceFields()
	{
		UseEffective = false;
		RocketManCamera = false;
		Oscillating = false;
		ZoneLocked = false;
		LastUpdate = -1;
		MyPhsxType = Camera_PhsxType_SIDE_LEVEL_RIGHT;
		MovingCamera = false;
	}
}
