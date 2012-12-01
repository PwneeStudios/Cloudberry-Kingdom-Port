#include <global_header.h>


namespace CloudberryKingdom
{

	void BobPhsxWheel::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 2, 0, 0, 0 );
		Name = Localization::Words_WHEELIE;
		NameTemplate = _T( "wheelie" );

		//Icon = new PictureIcon(Tools.TextureWad.FindByName("HeroIcon_Wheel"), Color.White, 1.4f * DefaultIconWidth);
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "Bob_Wheel_0000" ) ), Color::White, 1.4f * DefaultIconWidth );
	}

const std::shared_ptr<BobPhsxWheel> BobPhsxWheel::instance = std::make_shared<BobPhsxWheel>();

	const std::shared_ptr<BobPhsxWheel> &BobPhsxWheel::getInstance()
	{
		return instance;
	}

	BobPhsxWheel::BobPhsxWheel()
	{
		InitializeInstanceFields();
		LandSound = Tools::SoundWad->FindByName( _T( "BoxHero_Land" ) );

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

int BobPhsxWheel::AnimIndex = 0;

	void BobPhsxWheel::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		MyBob->JumpSound = Tools::SoundWad->FindByName( _T( "BoxHero_Jump" ) );

		OnGround = false;
		StartedJump = false;
		setJumpCount( 0 );
		FallingCount = 10000;

		Ducking = false;

		AnimIndex = MyBob->PlayerObject->FindAnim( _T( "Wheel" ) );
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
		int xVecSign = Math::Sign( xVec );

		if ( abs( xVec ) > ::2 )
		{
			// Faster acc if we are trying to reverse directions
			if ( Math::Sign( xVec ) != Math::Sign( AngleSpeed ) )
				_AngleAcc *= 1.65f;
			AngleSpeed += _AngleAcc * MyBob->CurInput.xVec.X;
		}
		else
		{
			// Friction
			AngleSpeed -= AngleFriction * Math::Sign( AngleSpeed );
			if ( abs( AngleSpeed ) < AngleFriction * 1.2f )
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

	void BobPhsxWheel::LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		if ( MyBob->getCore()->MyLevel->PlayMode == 0 && std::dynamic_pointer_cast<BlockBase>(ObjectLandedOn) != 0 && !PrevOnGround )
			LandSound->Play( .47f );
		BobPhsxNormal::LandOnSomething( MakeReadyToJump, ThingLandedOn );
	}

	void BobPhsxWheel::HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit )
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
			//MyBob.PlayerObject.ParentQuad.PointxAxisTo(CoreMath.AngleToDir(MyBob.PlayerObject.ContainedQuadAngle));
		}
	}

	bool BobPhsxWheel::CheckFor_xFlip()
	{
		return false;
	}

	void BobPhsxWheel::SideHit( ColType side, const std::shared_ptr<BlockBase> &block )
	{
		BobPhsxNormal::SideHit( side, block );

		if ( abs( AngleSpeed ) > ::5 * MaxAngleSpeed )
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

	void BobPhsxWheel::ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style )
	{
		BobPhsxNormal::ModData( makeData, Style );

		Style->DoorHitBoxPadding = Vector2( 25, 0 );
	}

	void BobPhsxWheel::ToSprites( std::map<int, SpriteAnim*> &SpriteAnims, Vector2 Padding )
	{
		std::shared_ptr<ObjectClass> Obj = MyBob->PlayerObject;
		SpriteAnims.insert( make_pair( 0, Obj->AnimToSpriteFrames( AnimIndex, 1, false, Padding ) ) );
	}

	void BobPhsxWheel::InitializeInstanceFields()
	{
		AngleSpeed = 0;
		MaxAngleSpeed = .0878f;
		AngleAcc = .00125f;
	}
}
