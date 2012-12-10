#include <global_header.h>


namespace CloudberryKingdom
{

	void BobPhsxNormal::InitializeStatics()
	{
		BobPhsxNormal::instance = std::make_shared<BobPhsxNormal>();
	}

	// Statics
	std::shared_ptr<BobPhsxNormal> BobPhsxNormal::instance;

	void BobPhsxNormal::InitSingleton()
	{
		BobPhsx::InitSingleton();

		Specification = HeroSpec( 0, 0, 0, 0 );
		Name = Localization::Words_CLASSIC_HERO;
		NameTemplate = _T( "hero" );

		//Icon = new PictureIcon(Tools.TextureWad.FindByName("HeroIcon_Classic"), Color.White, DefaultIconWidth * 1.1f);
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "Bob_Run_0024" ) ), Color::White, DefaultIconWidth * 1.2f );
	}

	const std::shared_ptr<BobPhsxNormal> &BobPhsxNormal::getInstance()
	{
		return instance;
	}

	std::shared_ptr<BobPhsx> BobPhsxNormal::Clone()
	{
		std::shared_ptr<BobPhsxNormal> newBob = std::make_shared<BobPhsxNormal>();
		CopyTo( newBob );
		return std::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxNormal::CopyTo( const std::shared_ptr<BobPhsxNormal> &bob )
	{
		BobPhsx::CopyTo( std::static_pointer_cast<BobPhsx>( bob ) );

		bob->InitializedAnim = InitializedAnim;
		bob->LandSound = LandSound;
		bob->DoubleJump = DoubleJump;
		bob->ThrustSound = ThrustSound;
		bob->ThrustSoundDelay = ThrustSoundDelay;
		bob->ThrustSoundCount = ThrustSoundCount;
		bob->RndMoveType = RndMoveType;
		bob->Offset = Offset;
		bob->RndThrustType = RndThrustType;
		bob->BobFallDelay = BobFallDelay;
		bob->XFriction = XFriction;
		bob->BobXDunkFriction = BobXDunkFriction;
		bob->BobJumpLength = BobJumpLength;
		bob->BobJumpLengthDucking = BobJumpLengthDucking;
		bob->BobInitialJumpSpeed = BobInitialJumpSpeed;
		bob->BobInitialJumpSpeedDucking = BobInitialJumpSpeedDucking;
		bob->BobJumpAccel2 = BobJumpAccel2;
		bob->BobJumpLength2 = BobJumpLength2;
		bob->BobJumpLengthDucking2 = BobJumpLengthDucking2;
		bob->BobInitialJumpSpeed2 = BobInitialJumpSpeed2;
		bob->BobInitialJumpSpeedDucking2 = BobInitialJumpSpeedDucking2;
		bob->BobJumpAccel = BobJumpAccel;
		bob->BobEdgeJump = BobEdgeJump;
		bob->BobEdgeJumpLength = BobEdgeJumpLength;
		bob->JetPackAccel = JetPackAccel;
		bob->Thrusting = Thrusting;
		bob->ReadyToThrust = ReadyToThrust;
		bob->StartedJump = StartedJump;
		bob->_JumpCount = _JumpCount;
		bob->FallingCount = FallingCount;
		bob->ReadyToJump = ReadyToJump;
		bob->ApexY = ApexY;
		bob->CountSinceApex = CountSinceApex;
		bob->AutoMoveLength = AutoMoveLength;
		bob->AutoMoveType = AutoMoveType;
		bob->AutoStrafeLength = AutoStrafeLength;
		bob->AutoSetToJumpLength = AutoSetToJumpLength;
		bob->AutoSetToJumpType = AutoSetToJumpType;
		bob->AutoDirLength = AutoDirLength;
		bob->AutoDir = AutoDir;
		bob->AutoDirLength_SetTo = AutoDirLength_SetTo;
		bob->AutoFallOrJumpLength = AutoFallOrJumpLength;
		bob->AutoFallOrJump = AutoFallOrJump;
		bob->NumJumps = NumJumps;
		bob->CurJump = CurJump;
		bob->JumpDelay = JumpDelay;
		bob->JumpDelayCount = JumpDelayCount;
		bob->JetPack = JetPack;
		bob->JetPackLength = JetPackLength;
		bob->JetPackCushion = JetPackCushion;
		bob->JetPackCount = JetPackCount;
		bob->MaxVerticalSpeed_Jump = MaxVerticalSpeed_Jump;
		bob->MaxVerticalSpeed_Thrust = MaxVerticalSpeed_Thrust;
		bob->StartJumpAnim = StartJumpAnim;
		bob->ThrustPos1 = ThrustPos1;
		bob->ThrustDir1 = ThrustDir1;
		bob->ThrustPos_Duck = ThrustPos_Duck;
		bob->ThrustDir_Duck = ThrustDir_Duck;
		bob->ThrustPos2 = ThrustPos2;
		bob->ThrustDir2 = ThrustDir2;
		bob->AutoAllowComputerToJumpOnLand = AutoAllowComputerToJumpOnLand;
		bob->NoStickPeriod = NoStickPeriod;
		bob->SafetyBlock = SafetyBlock;
		bob->JumpCountdown = JumpCountdown;
		bob->TurnCountdown = TurnCountdown;
		bob->Dir = Dir;
		bob->MinHeightAttained = MinHeightAttained;
		bob->MinGroundHeightAttained = MinGroundHeightAttained;
		bob->Up = Up;
		bob->ForcedJumpDamping = ForcedJumpDamping;
	}


	bool BobPhsxNormal::getSticky()
	{
		if ( Jumped || NoStickPeriod > 0 )
		//if (JumpCount > 0 || Jumped || StartJumpAnim)
			return false;
		else
			return BobPhsx::getSticky();
	}

	const int &BobPhsxNormal::getJumpCount() const
	{
		return _JumpCount;
	}

	void BobPhsxNormal::setJumpCount( const int &value )
	{
		_JumpCount = value;
	}

	void BobPhsxNormal::KillJump()
	{
		BobPhsx::KillJump();
		setJumpCount( 0 );
	}

	BobPhsxNormal::BobPhsxNormal()
	{
		//LandSound = Tools.SoundWad.FindByName("Land");

		InitializeInstanceFields();
		ThrustSound->MaxInstances = 8;
		this->JetPack = false;
		this->NumJumps = 1;

		DefaultValues();
	}

	BobPhsxNormal::BobPhsxNormal( int NumJumps, bool JetPack )
	{
		InitializeInstanceFields();
		this->JetPack = JetPack;
		this->NumJumps = NumJumps;

		ThrustSound->MaxInstances = 8;

		DefaultValues();
	}

	void BobPhsxNormal::SetAccels()
	{
		SetAccels( 19 );
	}

	void BobPhsxNormal::SetAccels( float JumpLength )
	{
		if ( JumpLength > 0 )
			BobJumpAccel = ( Gravity + 3.45f ) / JumpLength;
		if ( JumpLength > 0 )
			BobJumpAccel2 = ( Gravity + 3.42f ) / JumpLength;
		JetPackAccel = Gravity * 1.19f;
	}

	void BobPhsxNormal::DefaultValues()
	{
		Gravity = 2.95f;
		SetAccels();

		BobInitialJumpSpeed = 6;
		BobInitialJumpSpeedDucking = 6;
		BobJumpLength = 19;
		BobJumpLengthDucking = 17;


		BobInitialJumpSpeed2 = 14;
		BobInitialJumpSpeedDucking2 = 12;
		BobJumpLength2 = 18;
		BobJumpLengthDucking2 = 17;



		BobFallDelay = 5;
		BobXDunkFriction = .63f;

		MaxSpeed = 18.2f;
		XAccel = .53f * MaxSpeed / 17;
		XFriction = .78f * MaxSpeed / 17;
		MaxSpeed = 17.2f;


		// Slight faster
		MaxSpeed *= 1.04f;
		XAccel *= 1.1175f;
	}

	void BobPhsxNormal::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsx::Init( bob );

		Offset = INT_MIN;

		StartJumpAnim = false;

		OnGround = false;
		StartedJump = false;
		setJumpCount( 0 );
		FallingCount = 10000;

		Ducking = false;

		CurJump = 0;

		bob->MyCapeType = CapePrototype;
		if ( CapePrototype == CapeType_NONE )
			bob->CanHaveCape = false;
	}

	bool BobPhsxNormal::CheckFor_xFlip()
	{
		bool flipped = BobPhsx::CheckFor_xFlip();

		if ( flipped && MyBob->PlayerObject->DestinationAnim() == 1 )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 1, 0, true );
			MyBob->PlayerObject->DequeueTransfers();
		}

		return flipped;
	}

	void BobPhsxNormal::DuckingPhsx()
	{
		bool Down = MyBob->CurInput.xVec.Y < -.4f;
		if ( Down )
			Ducking = true;
		else
			Ducking = false;

		if ( Ducking )
			DuckingCount++;
		else
			DuckingCount = 0;

		// Correct ducking sprite offset
		if ( DuckingCount == 2 )
		{
			Vector2 shift = Vector2( 0, -30 );

			setPos( getPos() + shift );

			MyBob->Box->Target->Center += shift;
			MyBob->Box2->Target->Center += shift;
			MyBob->Box->Target->CalcBounds();
			MyBob->Box2->Target->CalcBounds();

			getObj()->ParentQuad->Center->Move(getObj()->ParentQuad->Center->Pos + shift);
			getObj()->ParentQuad->Update();
			getObj()->Update(0);

			if ( MyBob->MyCape != 0 )
				MyBob->MyCape->Move( shift );
		}
	}

	void BobPhsxNormal::PhsxStep()
	{
		BobPhsx::PhsxStep();

		//Console.WriteLine("{0}  {1}", Pos, Vel);

		if ( NoStickPeriod > 0 )
			NoStickPeriod--;

		DuckingPhsx();

		DoXAccel();
		DoYAccel();

		if ( OnGround )
			Jumped = false;

		if ( OnGround && FallingCount > 0 )
			FallingCount = 0;
		else
		{
			FallingCount++;
			CountSinceApex++;
		}

		Jump();

		OnGround = false;
	}

	void BobPhsxNormal::PhsxStep2()
	{
		BobPhsx::PhsxStep2();

		// Rocketman thrust
		if ( MyBob->getCore()->MyLevel->PlayMode == 0 && JetPack && Thrusting )
		{
			Vector2 Mod = Vector2( MyBob->PlayerObject->xFlip ? -1.f : 1.f, 1 ) * MyBob->PlayerObject->ParentQuad->getSize() / Vector2(260.f);

			int layer = __max( 1, MyBob->getCore()->DrawLayer - 1 );

			float scale = .5f * ( abs( Mod.X ) - 1 ) + 1;

			if ( Ducking )
				ParticleEffects::Thrust( MyBob->getCore()->MyLevel, layer, getPos() + Mod * ThrustPos_Duck, Mod * ThrustDir_Duck, getVel() / 1.5f, scale );
			else
				ParticleEffects::Thrust( MyBob->getCore()->MyLevel, layer, getPos() + Mod * ThrustPos1, Mod * ThrustDir1, getVel() / 1.5f, scale );

			if ( ThrustType == RocketThrustType_DOUBLE )
				ParticleEffects::Thrust( MyBob->getCore()->MyLevel, layer, getPos() + Mod * ThrustPos2, Mod * ThrustDir2, getVel() / 1.5f, scale );
		}
	}

	void BobPhsxNormal::UpdateReadyToJump()
	{
		if ( AutoAllowComputerToJumpOnLand )
		{
			if ( ( MustHitGroundToReadyJump && OnGround || !MustHitGroundToReadyJump && true ) && !MyBob->CurInput.A_Button && ( DynamicLessThan( getyVel(), 0 ) || OnGround || CurJump < NumJumps ) || (MyBob->getCore()->MyLevel->PlayMode != 0 || MyBob->CompControl) )
				ReadyToJump = true;
		}
		else
		{
			if ( ( MustHitGroundToReadyJump && OnGround || !MustHitGroundToReadyJump && true ) && !MyBob->CurInput.A_Button && ( DynamicLessThan( getyVel(), 0 ) || OnGround || CurJump < NumJumps ) )
				ReadyToJump = true;
		}

		//if (MyBob.Core.MyLevel.PlayMode != 0 || MyBob.CompControl)
		//    if (NumJumps > 1 && !OnGround && CurJump > 0 && JumpDelayCount > -25)
		//        ReadyToJump = false;

		// Update ReadyToThrust
		if ( JetPack && !OnGround && ( !MyBob->CurInput.A_Button || !StartedJump ) )
			ReadyToThrust = true;
		else
			ReadyToThrust = false;
	}

	bool BobPhsxNormal::getCanJump() const
	{
		return ReadyToJump && getyVel() < MaxVerticalSpeed_Jump && (OnGround || FallingCount < BobFallDelay || CurJump < NumJumps && JumpDelayCount <= 0 && CurJump > 0);
	}

	bool BobPhsxNormal::getExternalPreventJump() const
	{
		return DisableJumpCount > 0;
	}

	void BobPhsxNormal::Jump()
	{
		JumpDelayCount--;

		UpdateReadyToJump();

		if ( getExternalPreventJump() )
		{
			DisableJumpCount--;
			return;
		}

		if ( getCanJump() && MyBob->CurInput.A_Button )
		{
			DoJump();
		}
	}

	void BobPhsxNormal::DoJump()
	{
		// Track whether this jump is immediately from a placed object
		PlacedJump = NextJumpIsPlacedJump;
		NextJumpIsPlacedJump = false;

		if ( OnGround || FallingCount < BobFallDelay + 5 )
			CurJump = 0;

		Jumped = true;

		StartJumpAnim = true;

		CurJump++;
		JumpDelayCount = JumpDelay;

		ReadyToJump = false;

		FallingCount = 1000;

		float speed;
		if ( CurJump == 1 )
		{
			if ( !Ducking )
			{
				speed = BobInitialJumpSpeed;
				setJumpCount( BobJumpLength );
			}
			else
			{
				speed = BobInitialJumpSpeedDucking;
				setJumpCount( BobJumpLengthDucking );
			}
		}
		else
		{
			if ( !Ducking )
			{
				speed = BobInitialJumpSpeed2;
				setJumpCount( BobJumpLength2 );
			}
			else
			{
				speed = BobInitialJumpSpeedDucking2;
				setJumpCount( BobJumpLengthDucking2 );
			}
		}

		NoStickPeriod = 3;
		setJumpCount( static_cast<int>( getJumpCount() * JumpLengthModifier ) );

		if ( MyBob->getCore()->MyLevel->PlayMode == 0 && !MyBob->CharacterSelect_Renamed )
		{
			if ( CurJump > 1 )
				DoubleJump->Play();
			else
			{
				if ( MyBob->JumpSound == 0 )
					Bob::JumpSound_Default->Play();
				else
					MyBob->JumpSound->Play();
			}
		}

		if ( Gravity > 0 && getyVel() > 0 && CurJump == 1 || Gravity < 0 && getyVel() < 0 && CurJump == 1 )
		{
			float max = getyVel() + JumpAccelModifier * speed;
			float min = MaxJumpAccelMultiple * speed;
			setyVel( CoreMath::RestrictVal( min, max, getyVel() ) );
		}
		else
			setyVel( JumpAccelModifier * speed );
		StartedJump = true;

		JumpStartPos = getPos();
		ApexReached = false;
		ApexY = -20000000;

		IncrementJumpCounter();
	}

	float BobPhsxNormal::GetXAccel()
	{
		return XAccel;
	}

	void BobPhsxNormal::DoXAccel()
	{
		IceRun = false;

		float accel = GetXAccel();
		accel *= AccelMod;

		if ( MyBob->CurInput.xVec.X < -.15f && getxVel() > -MaxSpeed )
		{
			if ( getxVel() <= 0 )
				setxVel( getxVel() + accel * MyBob->CurInput.xVec.X );
			else
				if ( !( Ducking && OnGround ) )
					setxVel( getxVel() + ReverseDirectionBoost * ReverseDirectionBoostMod * accel * MyBob->CurInput.xVec.X );

			if ( DoFastTakeOff && getxVel() < 0 && getxVel() > -MaxSpeed / 10 )
				setxVel( -MaxSpeed / 10 );
		}
		if ( MyBob->CurInput.xVec.X > 0.15f && getxVel() < MaxSpeed )
		{
			if ( getxVel() >= 0 )
				setxVel( getxVel() + accel * MyBob->CurInput.xVec.X );
			else
				if ( !( Ducking && OnGround ) )
					setxVel( getxVel() + ReverseDirectionBoost * ReverseDirectionBoostMod * accel * MyBob->CurInput.xVec.X );

			if ( DoFastTakeOff && getxVel() > 0 && getxVel() < MaxSpeed / 10 )
				setxVel( MaxSpeed / 10 );
		}

		bool Run = false;
		if ( abs( MyBob->CurInput.xVec.X ) < .15f || !Run && abs( getxVel() ) > MaxSpeed || (Ducking && (OnGround || FallingCount < 2)) )
		{
			if ( Ducking && ( OnGround || FallingCount < 2 ) && abs( getxVel() ) < 2 )
				setxVel( 0 );

			float fric = XFriction;
			if ( Ducking && ( OnGround || FallingCount < 2 ) )
				fric = BobXDunkFriction;

			fric *= FricMod;

			if ( abs( getxVel() ) < 2 )
				setxVel( getxVel() / 12 );
			else
			{
				float Prev_xVel = getxVel();
				setxVel( getxVel() - Sign(getxVel()) * 7 / 4 * fric );

				if ( !Ducking )
				{
					// If we were above max speed do not reduce below max speed this frame if xVec.x > 0
					if ( abs( Prev_xVel ) >= MaxSpeed && abs( getxVel() ) < MaxSpeed )
						setxVel( Sign( getxVel() ) * MaxSpeed *.999f );
				}
			}
		}
	}

	void BobPhsxNormal::DoYAccel()
	{
		Thrusting = false;
		if ( JetPack && ( ReadyToThrust || Thrusting ) )
		if ( CurJump >= NumJumps && JumpDelayCount <= 0 || !OnGround && CurJump == 0 && FallingCount >= BobFallDelay )
			if ( MyBob->CurInput.A_Button && JetPackCount < JetPackLength + JetPackCushion )
			{
				if ( MyBob->getCore()->MyLevel->PlayMode == 0 )
				{
					if ( ThrustSoundCount <= 0 && ThrustSound != 0 )
					{
						ThrustSoundCount = ThrustSoundDelay;
						ThrustSound->PlayModulated( .02f );
					}
					ThrustSoundCount--;
				}

				Thrusting = true;
				JetPackCount++;
				float PowerLossRatio = static_cast<float>( JetPackLength + JetPackCushion - JetPackCount ) / static_cast<float>( JetPackCushion );
				PowerLossRatio = __min( 1, PowerLossRatio );

				if ( getyVel() < MaxVerticalSpeed_Thrust )
					setyVel( getyVel() + JetPackAccel * PowerLossRatio );
			}

		if ( StartedJump && MyBob->CurInput.A_Button && getJumpCount() > 0 )
		{
			if ( CurJump == 1 )
				setyVel( getyVel() + BobJumpAccel * static_cast<float>(getJumpCount()) );
			else
				setyVel( getyVel() + BobJumpAccel2 * static_cast<float>(getJumpCount()) );
			setJumpCount( getJumpCount() - 1 );
		}
		else
			StartedJump = false;

		if ( StartedJump || ( FallingCount >= BobFallDelay || Ducking ) )
		{
			float HoldVel = getyVel();

			// Only apply gravity if we haven't reached terminal velocity
			if ( DynamicGreaterThan( getyVel(), BobMaxFallSpeed ) )
				setyVel( getyVel() - Gravity );
			//if (yVel > BobMaxFallSpeed && Gravity > 0)
			//    yVel -= Gravity;
			//if (yVel < -BobMaxFallSpeed && Gravity < 0)
			//    yVel -= Gravity;

			if ( Sign( HoldVel ) != Sign( getyVel() ) )
			{
				if ( MyBob->OnApexReached != 0 )
					MyBob->OnApexReached->Apply();
					MyBob->OnApexReached.reset();

				ApexReached = true;
				ApexY = getPos().Y;
				CountSinceApex = 0;
			}
		}

		//yVel = Math.Max(yVel, BobMaxFallSpeed);

		if ( !Thrusting )
			ThrustSoundCount = 0;
	}

	void BobPhsxNormal::PlayLandSound()
	{
		LandSound->Play( .47f );
	}

	void BobPhsxNormal::LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		BobPhsx::LandOnSomething( MakeReadyToJump, ThingLandedOn );

		if ( LandSound != 0 && MyBob->getCore()->MyLevel->PlayMode == 0 && std::dynamic_pointer_cast<BlockBase>(ObjectLandedOn) != 0 && !PrevOnGround )
			PlayLandSound();

		ReadyToJump = ReadyToJump || MakeReadyToJump;

		MyBob->BottomCol = true;

		OnGround = true;
		MyBob->PopModifier = 0;

		CurJump = 1;
		JetPackCount = 0;

		if ( std::dynamic_pointer_cast<FlyingBlob>( ObjectLandedOn ) != 0 )
			FallingCount = -4;

		if ( std::dynamic_pointer_cast<BouncyBlock>( ObjectLandedOn ) != 0 )
		{
			FallingCount = -1;
			ReadyToJump = false;
		}
	}

	void BobPhsxNormal::HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit )
	{
		BobPhsx::HitHeadOnSomething( ThingHit );

		setJumpCount( 0 );
	}

	float BobPhsxNormal::RetardxVec()
	{
		float RetardFactor = .01f * MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(DifficultyParam_JUMPING_SPEED_RETARD_FACTOR, getPos());
		if ( !OnGround && getxVel() > RetardFactor * MaxSpeed )
			return 0;
		else
			return 1;
	}

	void BobPhsxNormal::GenerateInput_Survival( int CurPhsxStep )
	{
		MyBob->CurInput.A_Button = false;
		if ( JumpCountdown == 0 || getJumpCount() > 0 )
		{
			JumpCountdown = getMyLevel()->getRnd()->RndInt(0, 20); //150);

			MyBob->CurInput.A_Button = true;
		}
		else
			JumpCountdown--;

		if ( TurnCountdown == 0 )
		{
			if ( Dir == 0 )
				Dir = 1;

			Dir *= -1;
			TurnCountdown = getMyLevel()->getRnd()->RndInt(0, 135);
		}
		else
			TurnCountdown--;

		std::shared_ptr<BlockBase> block = std::dynamic_pointer_cast<BlockBase>( ObjectLandedOn );
		if ( 0 != block )
			SafetyBlock = block;

		if ( SafetyBlock != 0 )
		{
			SafetyBlock->getBox()->CalcBounds();
			if ( getPos().X > SafetyBlock->getBox()->TR.X - 70 )
				Dir = -1;
			if ( getPos().X < SafetyBlock->getBox()->BL.X + 70 )
				Dir = 1;
		}
		else
			Dir = 0;

		MyBob->CurInput.xVec.X = static_cast<float>( Dir );
	}

	void BobPhsxNormal::GenerateInput_Vertical( int CurPhsxStep )
	{
		// Track minimum position reached
		if ( CurPhsxStep < 30 )
		{
			MinGroundHeightAttained = MinHeightAttained = getPos().Y;
		}
		else
		{
			if ( OnGround )
				MinGroundHeightAttained = __min( MinGroundHeightAttained, getPos().Y );
			MinHeightAttained = __min( MinHeightAttained, getPos().Y );
		}

		MyBob->CurInput.A_Button = false;
		if ( JumpCountdown == 0 || ( ( getJumpCount() > 0 || !OnGround ) && JumpCountdown < 60 ) )
		{
			JumpCountdown = getMyLevel()->getRnd()->RndInt(0, 20); //150);

			MyBob->CurInput.A_Button = true;
		}
		else
			JumpCountdown--;

		if ( TurnCountdown <= 0 )
		{
			if ( Dir == 0 )
				Dir = 1;

			Dir *= -1;
			TurnCountdown = getMyLevel()->getRnd()->RndInt(0, 135);
		}
		else
			TurnCountdown--;

		std::shared_ptr<Camera> cam = MyBob->getCore()->MyLevel->getMainCamera();
		float HardBound = 1000;
		float SoftBound = 1500;
		if ( getPos().X > cam->TR.X - HardBound )
			Dir = -1;
		if ( getPos().X < cam->BL.X + HardBound )
			Dir = 1;
		if ( getPos().X > cam->TR.X - SoftBound && Dir == 1 )
			TurnCountdown -= 2;
		if ( getPos().X < cam->BL.X + SoftBound && Dir == -1 )
			TurnCountdown -= 2;

		MyBob->CurInput.xVec.X = static_cast<float>( Dir );

		// Decide if the computer should want to land or not
		if ( getGeometry() == LevelGeometry_UP )
		{
			MyBob->WantsToLand = ( CurPhsxStep / 30 ) % 3 == 0;
			if ( getVel().Y < -10 )
				MyBob->WantsToLand = true;
		}
		if ( getGeometry() == LevelGeometry_DOWN )
		{
			MyBob->WantsToLand = ( CurPhsxStep / 50 ) % 4 == 0 && getPos().Y < MinGroundHeightAttained - 350;
				//Pos.Y < MinHeightAttained + 30;

			if ( getPos().Y > MinHeightAttained + 100 )
			{
				MyBob->CurInput.A_Button = false;
				JumpCountdown += 120;
			}
		}
	}

	void BobPhsxNormal::GenerateInput_Right( int CurPhsxStep )
	{
		Vector2 TR = MyBob->getCore()->MyLevel->getMainCamera()->TR;
		Vector2 BL = MyBob->getCore()->MyLevel->getMainCamera()->BL;

		SetTarget( getGenData() );


		////////////////////////
		// Generate the input //
		////////////////////////

		MyBob->CurInput.B_Button = false;

		if ( getPos().Y < MyBob->TargetPosition.Y && ApexReached && !OnGround )
		{
			MyBob->CurInput.B_Button = true;
		}

		// BobEdgeJump, decide whether computer should always jump off edges
		if ( BobEdgeJumpLength <= 0 )
		{
			BobEdgeJumpLength = getMyLevel()->getRnd()->RndInt(20, 80);
			if ( BobEdgeJump == 1 )
				BobEdgeJump = 0;
			else
				BobEdgeJump = 1;
			if ( BobEdgeJump == 1 )
			{
				int Duration = getGenData()->Get(DifficultyParam_EDGE_JUMP_DURATION, getPos());
				BobEdgeJumpLength = getMyLevel()->getRnd()->Rnd->Next(Duration, 2 * Duration);
			}
			else
			{
				int Duration = getGenData()->Get(DifficultyParam_NO_EDGE_JUMP_DURATION, getPos());
				if ( Duration > 30 )
					BobEdgeJumpLength = getMyLevel()->getRnd()->Rnd->Next(Duration, 2 * Duration);
				else
				{
					BobEdgeJump = 1;
					BobEdgeJumpLength = 100;
				}
			}
		}
		else
			BobEdgeJumpLength--;

		if ( getMyLevel()->getStyle()->AlwaysEdgeJump )
			BobEdgeJump = 1;

		if ( AutoFallOrJumpLength == 0 )
		{
			if ( AutoFallOrJump == 1 )
				AutoFallOrJump = -1;
			else
				AutoFallOrJump = 1;
			if ( AutoFallOrJump == 1 )
				AutoFallOrJumpLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_JUMP_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_JUMP_LENGTH_BASE, getPos());
			else
				AutoFallOrJumpLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_FALL_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_FALL_LENGTH_BASE, getPos());
		}

		if ( AutoDirLength == 0 )
		{
			if ( AutoDir == 1 )
				AutoDir = -1;
			else
				AutoDir = 1;
			if ( AutoDir == 1 )
				AutoDirLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_FORWARD_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_FORWARD_LENGTH_BASE, getPos());
			else
				AutoDirLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_BACK_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_BACK_LENGTH_BASE, getPos());
			AutoDirLength_SetTo = AutoDirLength;

			// Get rid of spastic computer
			//if (AutoDirLength_SetTo < 7)
			//    if (MyLevel.Rnd.RndBool())
			//        AutoDirLength_SetTo = AutoDirLength = 10;
		}

		if ( ( MyBob->getCore()->MyLevel->GetPhsxStep() + Offset ) % 400 == 0 )
		{
			AutoMoveType = 0;
			AutoMoveLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_SIT_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_SIT_LENGTH_BASE, getPos());
		}
		if ( AutoMoveLength == 0 )
		{
			int rnd = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_MOVE_WEIGHT, getPos()) + getGenData()->Get(BehaviorParam_SIT_WEIGHT, getPos()));
			//if (rnd < GenData.Get(CompTweak.MoveWeight, Pos))                
			{
				AutoMoveType = 1;
				AutoMoveLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_MOVE_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_MOVE_LENGTH_BASE, getPos());
			}
			//else
			//{
			//    AutoMoveType = 0;
			//    AutoMoveLength = 60;// MyLevel.Rnd.Rnd.Next(GenData.Get(CompTweak.SitLengthAdd, Pos)) + GenData.Get(CompTweak.SitLengthBase, Pos);
			//}
		}

		if ( AutoSetToJumpLength == 0 )
		{
			int rnd = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_JUMP_WEIGHT, getPos()) + getGenData()->Get(BehaviorParam_NO_JUMP_WEIGHT, getPos()));
			if ( rnd < getGenData()->Get(BehaviorParam_JUMP_WEIGHT, getPos()) )
			{
				AutoSetToJumpType = 1;
				AutoSetToJumpLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_JUMP_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_JUMP_LENGTH_BASE, getPos());
			}
			else
			{
				AutoSetToJumpType = 0;
				AutoSetToJumpLength = getMyLevel()->getRnd()->Rnd->Next(getGenData()->Get(BehaviorParam_NO_JUMP_LENGTH_ADD, getPos())) + getGenData()->Get(BehaviorParam_NO_JUMP_LENGTH_BASE, getPos());
			}
		}

		AutoMoveLength--;
		AutoStrafeLength--;
		AutoSetToJumpLength--;
		AutoDirLength--;
		AutoFallOrJumpLength--;

		if ( AutoStrafeLength <= 0 )
		{
			AutoStrafeLength = 60;
		}

		if ( AutoMoveType == 1 )
		{
			MyBob->CurInput.xVec.X = static_cast<float>( AutoDir );

			// Get rid of spastic computer
			//if (AutoDirLength_SetTo < 5)
			//    MyBob.CurInput.xVec.X = 0;
		}
		else
			MyBob->CurInput.xVec.X = 0;

		if ( AutoSetToJumpType == 1 && AutoFallOrJump > 0 || getJumpCount() > 0 )
			MyBob->CurInput.A_Button = true;


		if ( Gravity > 0 )
		{
			if ( getPos().Y > MyBob->MoveData.MaxTargetY && OnGround || getPos().Y > MyBob->MoveData.MaxTargetY + 250 || getPos().Y > MyBob->TargetPosition.Y - 150 && JumpDelayCount < 2 && CurJump > 0 )
				MyBob->CurInput.A_Button = false;
		}
		if ( getPos().Y < MyBob->MoveData.MinTargetY && AutoFallOrJump > 0 )
		{
			MyBob->CurInput.A_Button = true;
		}

		if ( AutoFallOrJump < 0 )
			MyBob->CurInput.A_Button = false;


		// Jetpack extra
		if ( JetPack )
		{
			float EngageJetpackHeight = MyBob->TargetPosition.Y + 250;
			if ( getPos().Y < EngageJetpackHeight && JumpDelayCount < 2 && CurJump > 0 || AutoFallOrJump >= 0 )
			{
				MyBob->CurInput.A_Button = true;
			}
			if ( ( ReadyToThrust || Thrusting ) && ( AutoStrafeLength < 10 || getPos().Y > TR.Y - 150 ) )
				MyBob->CurInput.A_Button = false;
			if ( getyVel() < -10 && getPos().Y > MyBob->TargetPosition.Y - 300 )
				MyBob->CurInput.A_Button = true;
		}

		if ( getPos().X > MyBob->getCore()->MyLevel->CurMakeData->TRBobMoveZone.X || getPos().Y > MyBob->getCore()->MyLevel->CurMakeData->TRBobMoveZone.Y )
		{
			MyBob->CurInput.A_Button = false;
			MyBob->CurInput.xVec.X = 0;
		}


		if ( AutoMoveType == 0 )
			MyBob->CurInput.A_Button = false;


		if ( getMyLevel()->getStyle()->AlwaysEdgeJump )
		{
			if ( !Jumped )
				MyBob->CurInput.A_Button = false;
			MyBob->CurInput.xVec.X = 1;
		}


		// Better jump control: don't jump until edge of block
		if ( Jumped )
		{
			MyBob->CurInput.xVec *= RetardxVec();

			if ( getyVel() > 0 && getPos().Y < MyBob->TargetPosition.Y + 600 )
				MyBob->CurInput.A_Button = true;

			float MaxDip = 250; // How far below Target.Y we can go before needing to jump
			if ( JetPack || NumJumps > 1 ) // Make higher for Jetman and Double jump
				if ( BobEdgeJump == 1 )
				{
					MaxDip = -100;
					if ( getyVel() < 0 )
						MaxDip = -450;
				}
			if ( getPos().Y < MyBob->TargetPosition.Y - MaxDip )
				MyBob->CurInput.A_Button = true;
		}
		std::shared_ptr<BlockBase> block = std::dynamic_pointer_cast<BlockBase>( ObjectLandedOn );
		if ( 0 != block && ( OnGround || FallingCount < BobFallDelay ) && ( BobEdgeJump == 1 || block->getCore()->GenData.EdgeJumpOnly ) )
		{
			MyBob->Box->CalcBounds();
			float bobx = MyBob->Box->BL.X;
			float blockx = block->getBox()->TR.X;
			float DistancePast = static_cast<float>( getGenData()->Get(DifficultyParam_DISTANCE_PAST, getPos()) ); //5;
			float DistancePast_NoJump = static_cast<float>( getGenData()->Get(DifficultyParam_DISTANCE_PAST_NO_JUMP, getPos()) ); //500;
			if ( bobx > blockx + DistancePast || bobx >= blockx - 20 && FallingCount >= BobFallDelay - 2 )
				MyBob->CurInput.A_Button = true;
			else if ( bobx > blockx - DistancePast_NoJump )
				MyBob->CurInput.A_Button = false;
			else if ( block->getCore()->GenData.EdgeJumpOnly )
				MyBob->CurInput.A_Button = false;
		}

		// Better jump control: don't use full extent of jump
		int RetardJumpLength = getGenData()->Get(DifficultyParam_RETARD_JUMP_LENGTH, getPos());
		if ( !OnGround && RetardJumpLength >= 1 && getJumpCount() < RetardJumpLength && getJumpCount() > 1 )
			MyBob->CurInput.A_Button = false;

		// Decide if the computer should want to land or not            
		if ( Gravity > 0 )
		{
			if ( ( ReadyToThrust || getCanJump() ) && getPos().Y > BL.Y + 900 )
				MyBob->WantsToLand = getPos().Y < MyBob->TargetPosition.Y - 400;
			else
				MyBob->WantsToLand = getPos().Y < MyBob->TargetPosition.Y + 200;
		}
		else
		{
			if ( ( ReadyToThrust || getCanJump() ) && getPos().Y < TR.Y - 900 )
				MyBob->WantsToLand = getPos().Y > MyBob->TargetPosition.Y + 400;
			else
				MyBob->WantsToLand = getPos().Y > MyBob->TargetPosition.Y - 200;
		}

		// Jetpack extra-extra
		if ( JetPack )
		{
			switch ( RndThrustType )
			{
				case 0:
					HighThrusts( CurPhsxStep );
					break;
				case 1:
					MyBob->CurInput.A_Button = true;
					break;
				case 2:
					break;
			}

			if ( CurPhsxStep % 75 == 0 )
				RndThrustType = getMyLevel()->getRnd()->Rnd->Next(0, 3);
		}

		// Masochistic
		if ( getMyLevel()->getStyle()->Masochistic )
		{
			if ( getPos().Y < TR.Y - 400 && getxVel() > -2 && getPos().X > CurPhsxStep * (4000 / 800) )
			{
				switch ( ( CurPhsxStep / 60 ) % 2 )
				{
					case 0:
						MyBob->CurInput.xVec.Y = -1;
						if ( getyVel() < 0 )
							MyBob->CurInput.A_Button = true;
						MyBob->CurInput.xVec.X = 0;
						break;
					case 1:
						break;
				}
			}
			else
			{
				MyBob->CurInput.xVec.X = 1;
				MyBob->CurInput.xVec.Y = 0;
				MyBob->CurInput.A_Button = true;
			}
		}


		// Don't land near the apex of a jump
		PreventEarlyLandings( getGenData() );

		// Double jump extra
		if ( NumJumps > 1 )
		{
			AutoAllowComputerToJumpOnLand = false;

			if ( Jumped && CurJump > 0 && NumJumps > 1 && getyVel() < 0 )
			{
				switch ( ( CurPhsxStep / 60 ) % 3 )
				{
					case 0:
						if ( CurJump < NumJumps && getPos().Y > MyBob->TargetPosition.Y - 600 )
							MyBob->WantsToLand = false;
						if ( getyVel() < -6 )
							MyBob->CurInput.A_Button = AutoAllowComputerToJumpOnLand = MyBob->WantsToLand;
						break;

					case 1:
						MyBob->CurInput.A_Button = AutoAllowComputerToJumpOnLand = true;
						break;

					case 2:
						MyBob->CurInput.A_Button = AutoAllowComputerToJumpOnLand = false;
						break;
				}
			}

			if ( CurJump > 0 && getPos().Y > MyBob->TargetPosition.Y - 200 )
				MyBob->CurInput.A_Button = AutoAllowComputerToJumpOnLand = false;

			// n-jump hero
			if ( CurJump < NumJumps && NumJumps > 2 )
			{
				if ( getyVel() < -6 )
					MyBob->CurInput.A_Button = AutoAllowComputerToJumpOnLand = MyBob->WantsToLand;

				if ( MyBob->CurInput.A_Button )
					MyBob->WantsToLand = false;

				if ( getJumpCount() > 1 && CurJump > 1 )
					MyBob->CurInput.A_Button = true;

				if ( getPos().Y < MyBob->TargetPosition.Y && CurJump < NumJumps )
				{
					MyBob->CurInput.A_Button = AutoAllowComputerToJumpOnLand = true;
					MyBob->WantsToLand = false;
				}
			}
		}

		// Always prevent jump if we are near the top
		if ( getPos().Y > TR.Y - 150 )
		{
			MyBob->CurInput.xVec.X = 1;
			MyBob->CurInput.xVec.Y = 0;
			MyBob->CurInput.A_Button = false;
		}
	}

	void BobPhsxNormal::HighThrusts( int CurPhsxStep )
	{
						switch ( ( CurPhsxStep / 60 ) % 4 )
						{
							case 0:
								if ( JetPackCount > 5 )
									MyBob->CurInput.A_Button = false;
								if ( MyBob->WantsToLand && JetPackCount < JetPackLength - 1 && getyVel() < 0 )
									MyBob->CurInput.A_Button = true;
								if ( !MyBob->WantsToLand && JetPackCount < JetPackLength - 1 && getyVel() < 0 )
									MyBob->CurInput.A_Button = true;
								break;
							case 1:
								MyBob->CurInput.A_Button = true;
								break;
							case 2:
								if ( getyVel() < 0 )
									MyBob->CurInput.A_Button = true;
								break;
							case 3:
								break;
						}
	}

	void BobPhsxNormal::SetTarget( const std::shared_ptr<RichLevelGenData> &GenData )
	{
			int Period = GenData->Get( BehaviorParam_MOVE_TYPE_PERIOD, getPos() );
			float InnerPeriod = static_cast<float>( GenData->Get( BehaviorParam_MOVE_TYPE_INNER_PERIOD, getPos() ) );
			float MinTargetY = MyBob->MoveData.MinTargetY;
			float MaxTargetY = MyBob->MoveData.MaxTargetY;

			float t = 0;
			int Step = MyBob->getCore()->MyLevel->GetPhsxStep() + Offset;

			// If this is the first phsx step choose a move type
			if ( FirstPhsxStep )
			{
				RndThrustType = getMyLevel()->getRnd()->Rnd->Next(0, 3);

				if ( getMyLevel()->getRnd()->RndFloat() < .5f )
					RndMoveType = 10;
				else
					RndMoveType = getMyLevel()->getRnd()->Rnd->Next(0, 6);

				if ( getMyLevel()->getStyle()->AlwaysCurvyMove )
					RndMoveType = 10;
			}
			//RndMoveType = 10; /// DANGER DANGER 

			///////////////////////////////////////
			// Pick target for Bob to strive for //
			///////////////////////////////////////
			bool AllowTypeSwitching = true; // Whether we can switch between move types
			switch ( RndMoveType )
			{
				case 0:
					t = ( static_cast<float>( cos( Step / InnerPeriod ) ) + 1 ) / 2;
					break;
				case 1:
					t = ( static_cast<float>( sin( Step / InnerPeriod ) ) + 1 ) / 2;
					break;
				case 2:
					InnerPeriod *= 3;
					t = abs( ( Step % static_cast<int>( InnerPeriod ) ) / InnerPeriod );
					break;
				case 3:
					InnerPeriod *= 7 / 4;
					t = ( static_cast<float>( sin( Step / InnerPeriod ) ) + 1 ) / 2;
					break;
				case 4:
					if ( ( Step / 100 ) % 2 == 0 )
						t = .275f;
					else
						t = .7f;
					break;
				case 5:
					if ( ( Step / 100 ) % 2 == 0 )
						t = .05f;
					else
						t = .3f;
					break;
				case 6:
					RndMoveType = 10;
					break;
				case 10:
					// Hard up and hard down.
					AllowTypeSwitching = false;

					if ( FirstPhsxStep )
						Up = getMyLevel()->getRnd()->RndBool();
					if ( Up )
					{
						MyBob->TargetPosition.Y = MaxTargetY;
						if ( MyBob->getPos().Y > MyBob->TargetPosition.Y - 200 )
							Up = false;
					}
					else
					{
						MyBob->TargetPosition.Y = MinTargetY;
						if ( MyBob->getPos().Y < MyBob->TargetPosition.Y + 200 )
							Up = true;
					}
					break;
				default:
					// Do nothing. This fixes TargetPost.Y and creates straight levels.
					break;
			}
			if ( RndMoveType < 6 )
				MyBob->TargetPosition.Y = MyBob->MoveData.MinTargetY + t * ( MyBob->MoveData.MaxTargetY - MyBob->MoveData.MinTargetY );

			if ( AllowTypeSwitching && MyBob->getCore()->MyLevel->GetPhsxStep() % Period == 0 )
				RndMoveType = getMyLevel()->getRnd()->Rnd->Next(0, 7);

	}

	void BobPhsxNormal::PreventEarlyLandings( const std::shared_ptr<RichLevelGenData> &GenData )
	{
		int ApexWait = GenData->Get( DifficultyParam_APEX_WAIT, getPos() );
		if ( !OnGround && ( !ApexReached || CountSinceApex < ApexWait ) )
			MyBob->WantsToLand = false;
	}

	void BobPhsxNormal::GenerateInput( int CurPhsxStep )
	{
		// Initialize the offset value if it hasn't been set yet
		if ( Offset == INT_MIN )
			Offset = getMyLevel()->getRnd()->Rnd->Next(0, 300);

		BobPhsx::GenerateInput( CurPhsxStep );

		switch ( getGeometry() )
		{
			case LevelGeometry_RIGHT:
				GenerateInput_Right( CurPhsxStep );
				break;

			case LevelGeometry_DOWN:
			case LevelGeometry_UP:
				GenerateInput_Vertical( CurPhsxStep );
				break;

			case LevelGeometry_ONE_SCREEN:
				GenerateInput_Survival( CurPhsxStep );
				break;
		}

		// Let go of A for 1 frame
		if ( MyBob->PrevInput.A_Button && getyVel() < -5 )
			MyBob->CurInput.A_Button = false;

		AdditionalGenerateInputChecks( CurPhsxStep );

	#if defined(DEBUG)
		//CloudberryKingdomGame.debugstring = string.Format("{0}, {1}", JumpDelayCount, MyBob.CurInput.A_Button);
		//CloudberryKingdomGame.debugstring = string.Format("{0}, {1}", Pos.X, CurPhsxStep);
		CloudberryKingdomGame::debugstring = StringConverterHelper::toString( RndThrustType );
	#endif
	}

	void BobPhsxNormal::DampForcedJump()
	{
		BobPhsx::DampForcedJump();

		MyBob->NewVel *= ForcedJumpDamping;
	}

	void BobPhsxNormal::AnimStep()
	{
		if ( MyBob->IsSpriteBased )
			SpriteAnimStep();
		else
			BezierAnimStep();
	}

	void BobPhsxNormal::BezierAnimStep()
	{
		BobPhsx::AnimStep();

		if ( !InitializedAnim )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			InitializedAnim = true;
			MyBob->PlayerObject->EnqueueAnimation( 0, 0, false );
			MyBob->PlayerObject->DequeueTransfers();
		}


		// Falling animation
		if ( !OnGround && !Ducking && !Jumped && MyBob->PlayerObject->DestinationAnim() != 3 && abs(getxVel()) < 4 && DynamicLessThan(getyVel(), -15) )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 3, 0, true );
			MyBob->PlayerObject->AnimQueue.front()->AnimSpeed *= .7f;
		}

		// ???
		if ( !OnGround && !Ducking && !Jumped && MyBob->PlayerObject->DestinationAnim() != 2 && DynamicLessThan(getyVel(), -15) )
		{
			MyBob->PlayerObject->EnqueueAnimation( 2, 0.3f, false );
			MyBob->PlayerObject->AnimQueue.front()->AnimSpeed *= .7f;
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= .45f;
		}

		// Ducking animation
		if ( Ducking && MyBob->PlayerObject->DestinationAnim() != 4 )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 4, 0, false );
			MyBob->PlayerObject->AnimQueue.front()->AnimSpeed *= 12;
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= 2.5f;
		}
		// Reverse ducking animation
		if ( !Ducking && MyBob->PlayerObject->DestinationAnim() == 4 )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			if ( getyVel() > 0 )
				MyBob->PlayerObject->EnqueueAnimation( 2, 0.3f, false );
			else
				MyBob->PlayerObject->EnqueueAnimation( 3, 0.3f, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= 100;
		}

		// Standing animation
		if ( !Ducking )
			if ( abs( getxVel() ) < 1 && OnGround && MyBob->PlayerObject->DestinationAnim() != 0 || MyBob->PlayerObject->DestinationAnim() == 2 && OnGround && DynamicLessThan(getyVel(), 0) )
			{
			{
					int HoldDest = MyBob->PlayerObject->DestinationAnim();
					Clear( MyBob->PlayerObject->AnimQueue );
					//MyBob->PlayerObject->AnimQueue.clear();
					MyBob->PlayerObject->EnqueueAnimation( 0, 0, true );
					MyBob->PlayerObject->AnimQueue.front()->AnimSpeed *= 20;
					if ( HoldDest == 1 )
						MyBob->PlayerObject->DequeueTransfers();
				}
			}

		// Running animation
		if ( !Ducking )
			if ( ( abs( getxVel() ) >= 1 && OnGround ) && (MyBob->PlayerObject->DestinationAnim() != 1 || MyBob->PlayerObject->AnimQueue.empty() || !MyBob->PlayerObject->Play || !MyBob->PlayerObject->Loop) )
			{
				{
					Clear( MyBob->PlayerObject->AnimQueue );
					//MyBob->PlayerObject->AnimQueue.clear();

					if ( OnGround )
					{
						MyBob->PlayerObject->EnqueueAnimation( 1, 2.5f, true );
						MyBob->PlayerObject->AnimQueue.front()->AnimSpeed *= 2.5f;
					}
				}
			}

		// Jump animation
		if ( !Ducking )
			if ( ShouldStartJumpAnim() )
			{
				int anim = 2;
				float speed = .85f;
				if ( CurJump > 1 )
				{
					anim = 29;
					speed = .002f;
				}

				Clear( MyBob->PlayerObject->AnimQueue );
				//MyBob->PlayerObject->AnimQueue.clear();
				MyBob->PlayerObject->EnqueueAnimation( anim, 0.3f, false );
				MyBob->PlayerObject->DequeueTransfers();
				MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= speed;

				StartJumpAnim = false;
			}
		// ???
		if ( !Ducking )
			if ( DynamicLessThan( getyVel(), -.1f ) && !OnGround && MyBob->PlayerObject->anim == 2 && MyBob->PlayerObject->LastAnimEntry->AnimSpeed > 0 )
			{
				Clear( MyBob->PlayerObject->AnimQueue );
				//MyBob->PlayerObject->AnimQueue.clear();
				MyBob->PlayerObject->EnqueueAnimation( 2,.9f, false );
				MyBob->PlayerObject->DequeueTransfers();
				MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= -1;
			}

		float AnimSpeed = 1;
		if ( MyBob->PlayerObject->DestinationAnim() == 1 && MyBob->PlayerObject->Loop )
		{
			if ( IceRun )
				AnimSpeed = RunAnimSpeed * __max( .35f,.1f * SameInputDirectionCount );
			else
				AnimSpeed = RunAnimSpeed * __max( .35f,.1f * abs( getxVel() ) );
		}

		if ( MyBob->CharacterSelect_Renamed )
			// Use time invariant update
			MyBob->PlayerObject->PlayUpdate( 1000 * AnimSpeed * Tools::dt / 150 );
		else
			// Fixed speed update
			MyBob->PlayerObject->PlayUpdate( AnimSpeed * 17 / 19 * 1000 / 60 / 150 );
	}

	void BobPhsxNormal::SpriteAnimStep()
	{
		// Falling animation
		if ( !OnGround && !Ducking && MyBob->PlayerObject->DestinationAnim() != 3 && DynamicLessThan(getyVel(), -15) )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 3, 0, false );
			MyBob->PlayerObject->DequeueTransfers();
		}

		// ???
		if ( !OnGround && !Ducking && !Jumped && MyBob->PlayerObject->DestinationAnim() != 2 && DynamicLessThan(getyVel(), -15) )
		{
			MyBob->PlayerObject->EnqueueAnimation( 3, 0, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= .45f;
		}

		// Ducking animation
		if ( Ducking && MyBob->PlayerObject->DestinationAnim() != 4 )
		{
			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 4, 1, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= 2.5f;
		}
		// Reverse ducking animation
		if ( !Ducking && MyBob->PlayerObject->DestinationAnim() == 4 )
		{
			MyBob->PlayerObject->DoSpriteAnim = false;

			Clear( MyBob->PlayerObject->AnimQueue );
			//MyBob->PlayerObject->AnimQueue.clear();
			if ( getyVel() > 0 )
			{
				MyBob->PlayerObject->Read( 2, 1 );
				MyBob->PlayerObject->EnqueueAnimation( 2, 0, false );
			}
			else
			{
				MyBob->PlayerObject->Read( 3, 1 );
				MyBob->PlayerObject->EnqueueAnimation( 3, 0, false );
			}
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= 2;

			StartJumpAnim = false;
		}

		// Standing animation
		if ( !Ducking )
			if ( ( abs( getxVel() ) < 1 || IceRun ) && OnGround && MyBob->PlayerObject->DestinationAnim() != 0 || MyBob->PlayerObject->DestinationAnim() == 2 && OnGround && DynamicLessThan(getyVel(), 0) )
			{
				if ( !( MyBob->PlayerObject->DestinationAnim() == 5 && SameInputDirectionCount > 0 ) )
				if ( !( IceRun && SameInputDirectionCount > 0 && OnGround ) )
				{
					int HoldDest = MyBob->PlayerObject->DestinationAnim();
					Clear( MyBob->PlayerObject->AnimQueue );
					//MyBob->PlayerObject->AnimQueue.clear();
					MyBob->PlayerObject->EnqueueAnimation( 0, 1, true );

					MyBob->PlayerObject->DequeueTransfers();
					if ( HoldDest == 1 )
						MyBob->PlayerObject->DequeueTransfers();
				}
			}

		// Running animation
		if ( !Ducking )
		{
			// Slide
			if ( !IceRun && abs( getxVel() ) >= .35f && OnGround && Sign(MyBob->CurInput.xVec.X) != Sign(getxVel()) && abs(MyBob->CurInput.xVec.X) > 0.35f )
			{
				if ( MyBob->PlayerObject->DestinationAnim() != 5 )
				{
					MyBob->PlayerObject->EnqueueAnimation( 5, 0, false );
					MyBob->PlayerObject->DequeueTransfers();
				}
			}
			else

			if ( ( ( abs( getxVel() ) >= .35f && !IceRun || SameInputDirectionCount > 0 && IceRun ) && OnGround ) && (MyBob->PlayerObject->DestinationAnim() != 1 || MyBob->PlayerObject->AnimQueue.empty() || !MyBob->PlayerObject->Play || !MyBob->PlayerObject->Loop) )
			{
				{
					Clear( MyBob->PlayerObject->AnimQueue );
					//MyBob->PlayerObject->AnimQueue.clear();

					if ( OnGround )
					{
						MyBob->PlayerObject->EnqueueAnimation( 1, 0, true );
						MyBob->PlayerObject->DequeueTransfers();
					}
				}
			}
		}

		// Jump animation
		if ( !Ducking )
			if ( ShouldStartJumpAnim() )
			{
				int anim = 2;
				float speed = .85f;
				if ( CurJump > 1 )
				{
					anim = 29;
					speed = 1.2f;
				}

				Clear( MyBob->PlayerObject->AnimQueue );
				//MyBob->PlayerObject->AnimQueue.clear();
				MyBob->PlayerObject->EnqueueAnimation( anim, 0, false );
				MyBob->PlayerObject->DequeueTransfers();
				MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= speed;

				StartJumpAnim = false;
			}

		float AnimSpeed = 1.5f;
		if ( MyBob->PlayerObject->DestinationAnim() == 1 && MyBob->PlayerObject->Loop )
		{
			if ( IceRun )
			{
				//AnimSpeed = 1.29f * RunAnimSpeed * Math.Min(1f, .056f * SameInputDirectionCount);
				AnimSpeed = 1.29f * RunAnimSpeed * __min( 1, SameInputDirectionCount != 0 ? 1 : 0 );
			}
			else
				AnimSpeed = 1.29f * RunAnimSpeed * __max( .35f,.1f * abs( getxVel() ) );
		}

		if ( MyBob->CharacterSelect_Renamed )
			// Use time invariant update
			//MyBob.PlayerObject.PlayUpdate(1000f * AnimSpeed * Tools.dt / 150f);
			getObj()->PlayUpdate(getObj()->LoadingRunSpeed);
		else
			// Fixed speed update
			getObj()->PlayUpdate(1);

		//MyBob.PlayerObject.Read(0, 0);

		getObj()->DoSpriteAnim = true;
		MyBob->InitBoxesForCollisionDetect();
	}

	bool BobPhsxNormal::ShouldStartJumpAnim()
	{
		return DynamicGreaterThan( getyVel(), 10 ) && !OnGround && StartJumpAnim;
	}

	void BobPhsxNormal::SetDeathVel( BobDeathType DeathType )
	{
		if ( MyBob->KillingObject != 0 )
		{
			switch ( MyBob->KillingObject->getCore()->MyType )
			{
				case ObjectType_LASER:
					break;

					//// Big explosion
					//int sign = -Math.Sign(xVel);
					//if (sign == 0) sign = MyLevel.Rnd.RndBit();

					//Vel = new Vector2(170 * sign, 12);
					//Acc = new Vector2(0, -1.9f);

					//for (int i = 0; i < 3; i++)
					//    Fireball.Explosion(Pos + MyLevel.Rnd.RndDir(60), MyBob.Core.MyLevel, .98f * Vel, 1, 1);
					//return;

				case ObjectType_FIREBALL:
					MyBob->FlamingCorpse = true;

					//// Throw Bob away from the fireball
					//Vector2 Dir = Vector2.Normalize(Pos - MyBob.KillingObject.Core.Data.Position);
					//if (float.IsNaN(Dir.X)) Dir = new Vector2(0, 1);
					//Dir.Y = Math.Abs(Dir.Y);
					//if (Dir.Y < .1f) Dir.Y = .1f;

					Vector2 Dir = Vector2( static_cast<float>( Sign( getPos().X - MyBob->KillingObject->getCore()->Data.Position.X ) ), 1 );

					setVel( Dir * 40 );
					setAcc( Vector2( 0, -1.9f ) );

					return;
			}
		}

		//Vel = new Vector2(0, 35);
		//Acc = new Vector2(0, -1.9f);

		setVel( Vector2( 0, 36 ) );
		setAcc( Vector2( 0, -2.2f ) );

		if ( Bob::AllExplode )
			setAcc( 1.35f * getAcc() );

		//Vel = new Vector2(0, 30);
		//Acc = new Vector2(0, -2.95f);
	}

	void BobPhsxNormal::Explode()
	{
		Fireball::Explosion( MyBob->getCore()->Data.Position, MyBob->getCore()->MyLevel,.1f * getVel(), ExplosionScale, ExplosionScale / 1.4f );
		Fireball::Explosion( MyBob->getCore()->Data.Position, MyBob->getCore()->MyLevel,.1f * getVel(), ExplosionScale, ExplosionScale / 1.4f );
		Tools::SoundWad->FindByName( _T( "DustCloud_Explode" ) )->Play( .4f );
	}

	void BobPhsxNormal::Die( BobDeathType DeathType )
	{
		BobPhsx::Die( DeathType );

		std::shared_ptr<ObjectClass> obj = MyBob->PlayerObject;

		if ( Bob::AllExplode )
		{
			Explode();
		}

		SetDeathVel( DeathType );

		Clear( obj->AnimQueue );
		//obj->AnimQueue.clear();
		obj->EnqueueAnimation( 5, 0, false, true );
		//obj.EnqueueAnimation("ToPieces", 0, false, true);
		//obj.EnqueueAnimation("ToPieces", 0, false, true);
		obj->DequeueTransfers();
		obj->DestAnim()->AnimSpeed *= 1.85f;

		obj->DequeueTransfers();

		return;
	}

	void BobPhsxNormal::ToSprites( std::map<int, std::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding )
	{
		BobPhsx::ToSprites( SpriteAnims, Padding );

		std::shared_ptr<ObjectClass> Obj = MyBob->PlayerObject;
		SpriteAnims.insert( std::make_pair( 0, Obj->AnimToSpriteFrames( 0, 1, true, Padding ) ) );
		SpriteAnims.insert( std::make_pair( 1, Obj->AnimToSpriteFrames( 1, 1, true, 1, 1, Padding ) ) );
		SpriteAnims.insert( std::make_pair( 2, Obj->AnimToSpriteFrames( 2, 1, false, 1, 1, Padding ) ) );
		SpriteAnims.insert( std::make_pair( 4, Obj->AnimToSpriteFrames( 4, 1, false, 1, 1, Padding ) ) );
		SpriteAnims.insert( std::make_pair( 5, Obj->AnimToSpriteFrames( 5, 1, false, 1, 1, Padding ) ) );
	}

	void BobPhsxNormal::DollInitialize()
	{
		BobPhsx::DollInitialize();

		getObj()->anim = 1;
	}

	void BobPhsxNormal::InitializeInstanceFields()
	{
		InitializedAnim = false;
		LandSound = 0;
		DoubleJump = BobPhsx::DefaultInfo::DoubleJump_Sound;
		ThrustSound = BobPhsx::DefaultInfo::BobJetpack_Sound;
		ThrustSoundDelay = BobPhsx::DefaultInfo::BobJetpack_SoundDelay;
		StartedJump = false;
		_JumpCount = 0;
		NumJumps = 1;
		JumpDelay = 10;
		JetPack = false;
		JetPackLength = 60;
		JetPackCushion = 12;
		MaxVerticalSpeed_Jump = 23;
		MaxVerticalSpeed_Thrust = 28;
		AutoAllowComputerToJumpOnLand = true;
		SafetyBlock = 0;
		JumpCountdown = 0;
		TurnCountdown = 0;
		Dir = 0;
		MinHeightAttained = 0;
		ForcedJumpDamping = 1;
	}
}
