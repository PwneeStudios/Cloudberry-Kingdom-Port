#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxWheel::InitializeStatics()
	{
		BobPhsxWheel::instance = boost::make_shared<BobPhsxWheel>();
			InitBobPhsxSingleton( BobPhsxWheel::instance );
		BobPhsxWheel::AnimIndex = 0;
	}

	// Statics
	boost::shared_ptr<BobPhsxWheel> BobPhsxWheel::instance;
	int BobPhsxWheel::AnimIndex;

	void BobPhsxWheel::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 2, 0, 0, 0 );
		Name = Localization::Words_Wheelie;
		NameTemplate = std::wstring( L"wheelie" );

		//Icon = new PictureIcon(Tools::TextureWad.FindByName("HeroIcon_Wheel"), Color.White, 1.4f * DefaultIconWidth);
		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"Bob_Wheel_0000" ) ), Color::White, 1.4f * DefaultIconWidth );
	}

	const boost::shared_ptr<BobPhsxWheel> &BobPhsxWheel::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<BobPhsx> BobPhsxWheel::Clone()
	{
		boost::shared_ptr<BobPhsxWheel> newBob = boost::make_shared<BobPhsxWheel>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return boost::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxWheel::CopyTo( const boost::shared_ptr<BobPhsxWheel> &bob )
	{
		BobPhsxNormal::CopyTo( boost::static_pointer_cast<BobPhsxNormal>( bob ) );

		bob->LandSound = LandSound;
		bob->AngleSpeed = AngleSpeed;
		bob->MaxAngleSpeed = MaxAngleSpeed;
		bob->AngleAcc = AngleAcc;
	}


	BobPhsxWheel::BobPhsxWheel()
	{
		InitializeInstanceFields();
		LandSound = Tools::SoundWad->FindByName( std::wstring( L"BoxHero_Land" ) );

		DefaultValues();
	}

	void BobPhsxWheel::DefaultValues()
	{
		BobPhsxNormal::DefaultValues();

		MaxSpeed = 21; // 22f;
		XAccel = .2f;
		XFriction = .2f;

		SpritePadding = Vector2( 90, 0 );
	}

	void BobPhsxWheel::Init( const boost::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		MyBob->JumpSound = Tools::SoundWad->FindByName( std::wstring( L"BoxHero_Jump" ) );

		OnGround = false;
		StartedJump = false;
		setJumpCount( 0 );
		FallingCount = 10000;

		Ducking = false;

		AnimIndex = MyBob->PlayerObject->FindAnim( std::wstring( L"Wheel" ) );
		MyBob->PlayerObject->Read( AnimIndex, 0 );
	}

	void BobPhsxWheel::DuckingPhsx()
	{
		return;
	}

	void BobPhsxWheel::DoXAccel()
	{
		float _AngleAcc = AngleAcc;
		//if (!OnGround) AngleAcc *= 1.5f;
		float AngleFriction = .5f * _AngleAcc;

	/*            float MaxAngleSpeed = .15f;
	            float AngleAcc = .00175f;
	            if (!OnGround) AngleAcc *= 1.5f;
	            float AngleFriction = .5f * AngleAcc;
	            */
		float xVec = MyBob->CurInput.xVec.X;
		int xVecSign = Sign( xVec );

		if ( fabs( xVec ) > 0.2f )
		{
			// Faster acc if we are trying to reverse directions
			if ( Sign( xVec ) != Sign( AngleSpeed ) )
				_AngleAcc *= 1.65f;
			AngleSpeed += _AngleAcc * MyBob->CurInput.xVec.X;
		}
		else
		{
			// Friction
			AngleSpeed -= AngleFriction * Sign( AngleSpeed );
			if ( fabs( AngleSpeed ) < AngleFriction * 1.2f )
				AngleSpeed = 0;
		}

		// Max speed
		if ( AngleSpeed > MaxAngleSpeed )
			AngleSpeed = MaxAngleSpeed;
		if ( AngleSpeed < -MaxAngleSpeed )
			AngleSpeed = -MaxAngleSpeed;

		//if (OnGround || this.FallingCount < 2)
			{
			//base.XAccel();

			float DesiredSpeed = AngleToDist( AngleSpeed );
			MyBob->getCore()->Data.Velocity.X += 1 * (DesiredSpeed - MyBob->getCore()->Data.Velocity.X);
			}

		//Console.WriteLine("angle speed {0}, max {1}", AngleSpeed, MaxAngleSpeed);
	}

	float BobPhsxWheel::AngleToDist( float Angle )
	{
		return 340 * Angle;
	}

	float BobPhsxWheel::RetardxVec()
	{
		float RetardFactor = .01f * MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(DifficultyParam_JUMPING_SPEED_RETARD_FACTOR, MyBob->getCore()->Data.Position);
		if ( !OnGround && AngleSpeed > RetardFactor * MaxAngleSpeed )
			return 0;
		else
			return 1;
	}

	void BobPhsxWheel::LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		if ( MyBob->getCore()->MyLevel->PlayMode == 0 && boost::dynamic_pointer_cast<BlockBase>(ObjectLandedOn) != 0 && !PrevOnGround )
			LandSound->Play( .47f );
		BobPhsxNormal::LandOnSomething( MakeReadyToJump, ThingLandedOn );
	}

	void BobPhsxWheel::HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit )
	{
		BobPhsxNormal::HitHeadOnSomething( ThingHit );
	}

	void BobPhsxWheel::GenerateInput( int CurPhsxStep )
	{
		BobPhsxNormal::GenerateInput( CurPhsxStep );

		if ( MyBob->CurInput.xVec.Y == -1 )
			MyBob->CurInput.xVec.X = -1;
	}

	void BobPhsxWheel::AnimStep()
	{
		MyBob->PlayerObject->ContainedQuadAngle -= AngleSpeed * 1.25f;

		MyBob->PlayerObject->Read( AnimIndex, 0 );

		if ( MyBob->IsSpriteBased )
		{
			//MyBob.PlayerObject.ParentQuad.PointxAxisTo(CoreMath::AngleToDir(MyBob.PlayerObject.ContainedQuadAngle));
		}
	}

	bool BobPhsxWheel::CheckFor_xFlip()
	{
		return false;
	}

	void BobPhsxWheel::SideHit( ColType side, const boost::shared_ptr<BlockBase> &block )
	{
		BobPhsxNormal::SideHit( side, block );

		if ( fabs( AngleSpeed ) > 0.5f * MaxAngleSpeed )
		{
			if ( side == ColType_LEFT )
				MyBob->getCore()->Data.Velocity.Y += .15f * (AngleToDist(AngleSpeed) - MyBob->getCore()->Data.Velocity.Y);
			if ( side == ColType_RIGHT )
				MyBob->getCore()->Data.Velocity.Y -= .15f * (AngleToDist(AngleSpeed) - MyBob->getCore()->Data.Velocity.Y);
		}

		AngleSpeed *= .75f;
	}

	void BobPhsxWheel::Die( BobDeathType DeathType )
	{
		if ( Bob::AllExplode )
		{
			Explode();
		}

		SetDeathVel( DeathType );
	}

	void BobPhsxWheel::ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style )
	{
		BobPhsxNormal::ModData( makeData, Style );

		Style->DoorHitBoxPadding = Vector2( 25, 0 );
	}

	void BobPhsxWheel::ToSprites( std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding )
	{
		boost::shared_ptr<ObjectClass> Obj = MyBob->PlayerObject;
		SpriteAnims.insert( std::make_pair( 0, Obj->AnimToSpriteFrames( AnimIndex, 1, false, Padding ) ) );
	}

	void BobPhsxWheel::InitializeInstanceFields()
	{
		AngleSpeed = 0;
		MaxAngleSpeed = .0878f;
		AngleAcc = .00125f;
	}
}
