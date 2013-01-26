#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxSpaceship::InitializeStatics()
	{
		BobPhsxSpaceship::instance = boost::make_shared<BobPhsxSpaceship>();
			InitBobPhsxSingleton( BobPhsxSpaceship::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxSpaceship> BobPhsxSpaceship::instance;

	float BobPhsxSpaceship::KeepUnused( float UpgradeLevel )
	{
		return.5f + .03f * UpgradeLevel;
	}

	void BobPhsxSpaceship::InitSingleton()
	{
		BobPhsx::InitSingleton();

		Specification = HeroSpec( 4, 0, 0, 0 );
		Name = Localization::Words_Spaceship;
		NameTemplate = std::wstring( L"spaceship" );
		Icon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"Spaceship_Paper" ) ), Color::White, 1.15f * DefaultIconWidth );
	}

	const boost::shared_ptr<BobPhsxSpaceship> &BobPhsxSpaceship::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<BobPhsx> BobPhsxSpaceship::Clone()
	{
		boost::shared_ptr<BobPhsxSpaceship> newBob = boost::make_shared<BobPhsxSpaceship>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return boost::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxSpaceship::CopyTo( const boost::shared_ptr<BobPhsxSpaceship> &bob )
	{
		BobPhsx::CopyTo( boost::static_pointer_cast<BobPhsx>( bob ) );

		bob->AutoMoveLength = AutoMoveLength;
		bob->AutoMoveType = AutoMoveType;
		bob->AutoStrafeLength = AutoStrafeLength;
		bob->AutoDirLength = AutoDirLength;
		bob->AutoDir = AutoDir;

		bob->RndMoveType = RndMoveType;
		bob->Dir = Dir;
	}

	BobPhsxSpaceship::BobPhsxSpaceship()
	{
		InitializeInstanceFields();
		DefaultValues();
	}

	void BobPhsxSpaceship::DefaultValues()
	{
		//MaxSpeed = 24f;
		MaxSpeed = 30;

		XAccel = 2.3f;

		BobPhsx::DefaultValues();
	}

	void BobPhsxSpaceship::Init( const boost::shared_ptr<Bob> &bob )
	{
		BobPhsx::Init( bob );

		bob->DieSound = Tools::SoundWad->FindByName( std::wstring( L"DustCloud_Explode" ) );

		OnGround = false;
	}

	void BobPhsxSpaceship::PhsxStep()
	{
		BobPhsx::PhsxStep();

		if ( MyBob->CharacterSelect2 )
			return;

        if (MyBob->getMyLevel()->PlayMode == 0 && !MyBob->InputFromKeyboard && !MyBob->getMyLevel()->Watching)
        {
            if (MyBob->CurInput.A_Button)
                MyBob->CurInput.xVec.X = 1;
            else if (MyBob->CurInput.xVec.X > .5f)
                MyBob->CurInput.xVec.X = .5f;
        }

		getMyLevel()->MyCamera->MovingCamera = true;

		MyBob->getCore()->Data.Velocity *= .86f;
		MyBob->getCore()->Data.Velocity.X += 2.3f;

		if ( MyBob->CurInput.xVec.Length() > 0.2f )
		{
            float boost = 1;
            if ( MyBob->CurInput.xVec.X == 1 )
                boost = 1.2f;

			MyBob->getCore()->Data.Velocity += boost * XAccel * MyBob->CurInput.xVec;

			float Magnitude = MyBob->getCore()->Data.Velocity.Length();
			if ( Magnitude > boost * MaxSpeed )
			{
				MyBob->getCore()->Data.Velocity.Normalize();
				MyBob->getCore()->Data.Velocity *= MaxSpeed;
			}
		}

		OnGround = false;
	}

	void BobPhsxSpaceship::SideHit( ColType side, const boost::shared_ptr<BlockBase> &block )
	{
		BobPhsx::SideHit( side, block );

		if ( getMyLevel()->PlayMode == 0 && !MyBob->Immortal )
			MyBob->Die( BobDeathType_OTHER );
	}

	void BobPhsxSpaceship::PhsxStep2()
	{
		BobPhsx::PhsxStep2();

		if ( MyBob->getCore()->MyLevel->PlayMode == 0 && MyBob->CurInput.xVec.X > -.3f )
		{
			float intensity = __min( .3f + ( MyBob->CurInput.xVec.X + .3f ), 1 );
            if ( MyBob->CurInput.xVec.X <= .5f )
                intensity = __min( intensity, .3f + ( .1f + .3f ) );

			int layer = __max( 1, MyBob->getCore()->DrawLayer - 1 );
			ParticleEffects::Thrust( MyBob->getCore()->MyLevel, layer, getPos() + Vector2(0, 10), Vector2(-1, 0), Vector2(-10, getyVel()), intensity );
		}
	}

	bool BobPhsxSpaceship::CheckFor_xFlip()
	{
		return false;
	}

	void BobPhsxSpaceship::Jump()
	{
	}

	void BobPhsxSpaceship::LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		BobPhsx::LandOnSomething( MakeReadyToJump, ThingLandedOn );

		MyBob->getCore()->Data.Velocity.Y = MyBob->getCore()->Data.Velocity.Y + 5;

		MyBob->BottomCol = true;

		OnGround = true;
	}

	void BobPhsxSpaceship::HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit )
	{
		BobPhsx::HitHeadOnSomething( ThingHit );
	}

	void BobPhsxSpaceship::GenerateInput_Vertical( int CurPhsxStep )
	{
		//MyBob.CurInput.A_Button = false;
		//if (TurnCountdown <= 0)
		//{
		//    if (Dir == 0) Dir = 1;

		//    Dir *= -1;
		//    TurnCountdown = MyLevel.Rnd.RndInt(0, 135);
		//}
		//else
		//    TurnCountdown--;

		//Camera cam = MyBob.Core.MyLevel.MainCamera;
		//float HardBound = 1000; float SoftBound = 1500;
		//if (Pos.X > cam.TR.X - HardBound) Dir = -1;
		//if (Pos.X < cam.BL.X + HardBound) Dir = 1;
		//if (Pos.X > cam.TR.X - SoftBound && Dir == 1) TurnCountdown -= 2;
		//if (Pos.X < cam.BL.X + SoftBound && Dir == -1) TurnCountdown -= 2;

		//MyBob.CurInput.xVec.X = Dir;

		MyBob->CurInput.B_Button = false;

		if ( MyBob->getCore()->MyLevel->GetPhsxStep() % 60 == 0 )
			RndMoveType = getMyLevel()->getRnd()->Rnd->Next(0, 3);

		if ( AutoDirLength == 0 )
		{
			if ( AutoDir == 1 )
				AutoDir = -1;
			else
				AutoDir = 1;
			if ( AutoDir == 1 )
				AutoDirLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_FORWARD_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_FORWARD_LENGTH_BASE, MyBob->getCore()->Data.Position);
			else
				AutoDirLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_BACK_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_BACK_LENGTH_BASE, MyBob->getCore()->Data.Position);
		}

		if ( AutoMoveLength == 0 )
		{
			int rnd = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_WEIGHT, MyBob->getCore()->Data.Position) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_SIT_WEIGHT, MyBob->getCore()->Data.Position));
			if ( rnd < MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_WEIGHT, MyBob->getCore()->Data.Position) )
			{
				AutoMoveType = 1;
				AutoMoveLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_LENGTH_BASE, MyBob->getCore()->Data.Position);
			}
			else
			{
				AutoMoveType = 0;
				AutoMoveLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_SIT_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_SIT_LENGTH_BASE, MyBob->getCore()->Data.Position);
			}
		}

		AutoMoveLength--;
		AutoStrafeLength--;
		AutoDirLength--;

		if ( AutoMoveType == 1 )
			MyBob->CurInput.xVec.Y = static_cast<float>( AutoDir );


		float RetardFactor = .01f * MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(DifficultyParam_JUMPING_SPEED_RETARD_FACTOR, MyBob->getCore()->Data.Position);
		if ( MyBob->getCore()->Data.Velocity.Y > RetardFactor * MaxSpeed )
			MyBob->CurInput.xVec.Y = 0;

		MyBob->CurInput.xVec.Y *= __min( 1, static_cast<float>( cosf( MyBob->getCore()->MyLevel->GetPhsxStep() / 65.f ) ) + 1.35f );

		float t = 0;
		if ( RndMoveType == 0 )
			t = ( static_cast<float>( cosf( MyBob->getCore()->MyLevel->GetPhsxStep() / 40.f ) ) + 1.f ) / 2.f;
		if ( RndMoveType == 1 )
			t = ( static_cast<float>( sinf( MyBob->getCore()->MyLevel->GetPhsxStep() / 40.f ) ) + 1.f ) / 2.f;
		if ( RndMoveType == 2 )
			t = abs( ( MyBob->getCore()->MyLevel->GetPhsxStep() % 120 ) / 120.f );

		MyBob->TargetPosition.X = MyBob->MoveData.MinTargetY - 160 + t * ( 200 + MyBob->MoveData.MaxTargetY - MyBob->MoveData.MinTargetY );
		//+ 200 * (float)Math.Cos(MyBob.Core.MyLevel.GetPhsxStep() / 20f);

		if ( MyBob->getCore()->Data.Position.X < MyBob->TargetPosition.X )
			MyBob->CurInput.xVec.X = 1;
		if ( MyBob->getCore()->Data.Position.X > MyBob->TargetPosition.X )
			MyBob->CurInput.xVec.X = -1;
		MyBob->CurInput.xVec.X *= __min( 1, abs( MyBob->TargetPosition.X - MyBob->getCore()->Data.Position.X ) / 100 );

		if ( getPos().X > MyBob->TargetPosition.X + 400 )
			MyBob->CurInput.xVec.X = 1;
		if ( getPos().X < MyBob->TargetPosition.X - 400 )
			MyBob->CurInput.xVec.X = -1;

		if ( MyBob->getCore()->Data.Position.Y > MyBob->getCore()->MyLevel->CurMakeData->TRBobMoveZone.Y || MyBob->getCore()->Data.Position.X > MyBob->getCore()->MyLevel->CurMakeData->TRBobMoveZone.X )
		{
			MyBob->CurInput.xVec.Y = 0;
		}
	}

	void BobPhsxSpaceship::GenerateInput( int CurPhsxStep )
	{
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

			default:
				break;
		}

		AdditionalGenerateInputChecks( CurPhsxStep );
	}

	void BobPhsxSpaceship::GenerateInput_Right( int CurPhsxStep )
	{
		MyBob->CurInput.B_Button = false;

		if ( MyBob->getCore()->MyLevel->GetPhsxStep() % 60 == 0 )
			RndMoveType = getMyLevel()->getRnd()->Rnd->Next(0, 3);

		if ( AutoDirLength == 0 )
		{
			if ( AutoDir == 1 )
				AutoDir = -1;
			else
				AutoDir = 1;
			if ( AutoDir == 1 )
				AutoDirLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_FORWARD_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_FORWARD_LENGTH_BASE, MyBob->getCore()->Data.Position);
			else
				AutoDirLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_BACK_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_BACK_LENGTH_BASE, MyBob->getCore()->Data.Position);
		}

		if ( AutoMoveLength == 0 )
		{
			int rnd = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_WEIGHT, MyBob->getCore()->Data.Position) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_SIT_WEIGHT, MyBob->getCore()->Data.Position));
			if ( rnd < MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_WEIGHT, MyBob->getCore()->Data.Position) )
			{
				AutoMoveType = 1;
				AutoMoveLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_MOVE_LENGTH_BASE, MyBob->getCore()->Data.Position);
			}
			else
			{
				AutoMoveType = 0;
				AutoMoveLength = getMyLevel()->getRnd()->Rnd->Next(MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_SIT_LENGTH_ADD, MyBob->getCore()->Data.Position)) + MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(BehaviorParam_SIT_LENGTH_BASE, MyBob->getCore()->Data.Position);
			}
		}

		AutoMoveLength--;
		AutoStrafeLength--;
		AutoDirLength--;

		if ( AutoMoveType == 1 )
			MyBob->CurInput.xVec.X = static_cast<float>( AutoDir );


		float RetardFactor = .01f * MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(DifficultyParam_JUMPING_SPEED_RETARD_FACTOR, MyBob->getCore()->Data.Position);
		if ( !OnGround && MyBob->getCore()->Data.Velocity.X > RetardFactor * MaxSpeed )
			MyBob->CurInput.xVec.X = 0;

		MyBob->CurInput.xVec.X *= __min( 1, static_cast<float>( cosf( MyBob->getCore()->MyLevel->GetPhsxStep() / 65.f ) ) + 1.35f );

		float t = 0;
		if ( RndMoveType == 0 )
			t = ( static_cast<float>( cosf( MyBob->getCore()->MyLevel->GetPhsxStep() / 40.f ) ) + 1.f ) / 2.f;
		if ( RndMoveType == 1 )
			t = ( static_cast<float>( sinf( MyBob->getCore()->MyLevel->GetPhsxStep() / 40.f ) ) + 1.f ) / 2.f;
		if ( RndMoveType == 2 )
			t = abs( ( MyBob->getCore()->MyLevel->GetPhsxStep() % 120 ) / 120.f );

		MyBob->TargetPosition.Y = MyBob->MoveData.MinTargetY - 200 + t * ( -90 + MyBob->MoveData.MaxTargetY - MyBob->MoveData.MinTargetY );
				//+ 200 * (float)Math.Cos(MyBob.Core.MyLevel.GetPhsxStep() / 20f);

		if ( MyBob->getCore()->Data.Position.Y < MyBob->TargetPosition.Y )
			MyBob->CurInput.xVec.Y = 1;
		if ( MyBob->getCore()->Data.Position.Y > MyBob->TargetPosition.Y )
			MyBob->CurInput.xVec.Y = -1;
		MyBob->CurInput.xVec.Y *= __min( 1, abs( MyBob->TargetPosition.Y - MyBob->getCore()->Data.Position.Y ) / 100 );

		if ( getPos().X > CurPhsxStep * 1.1f * (4000.f / 600.f) )
		{
			if ( getPos().Y > MyBob->TargetPosition.Y && (CurPhsxStep / 40) % 3 == 0 )
				MyBob->CurInput.xVec.X = -1;
			if ( getPos().Y < MyBob->TargetPosition.Y && (CurPhsxStep / 25) % 4 == 0 )
				MyBob->CurInput.xVec.X = -1;
		}
		if ( getPos().Y < MyBob->TargetPosition.Y && getPos().X < CurPhsxStep * (4000.f / 900.f) )
		{
			MyBob->CurInput.xVec.X = 1;
		}

        if ( getPos().X < getMyLevel()->getMainCamera()->BL.X + 400 )
            MyBob->CurInput.xVec.X = 1;
        if ( getPos().X > getMyLevel()->getMainCamera()->TR.X - 500 && MyBob->CurInput.xVec.X > 0 )
            MyBob->CurInput.xVec.X /= 2;

		if ( getPos().X > getMyLevel()->Fill_TR.X - 1200 )
		{
			if ( getPos().Y > getMyLevel()->getMainCamera()->TR.Y - 600 )
				MyBob->CurInput.xVec.Y = -1;
			if ( getPos().Y < getMyLevel()->getMainCamera()->BL.Y + 600 )
				MyBob->CurInput.xVec.Y = 1;
		}

		if ( MyBob->getCore()->Data.Position.X > MyBob->getCore()->MyLevel->CurMakeData->TRBobMoveZone.X || MyBob->getCore()->Data.Position.Y > MyBob->getCore()->MyLevel->CurMakeData->TRBobMoveZone.Y )
		{
			MyBob->CurInput.xVec.X = 0;
		}
	}

	void BobPhsxSpaceship::AnimStep()
	{
		BobPhsx::AnimStep();
	}

	void BobPhsxSpaceship::ToSprites( std::map<int, boost::shared_ptr<SpriteAnim> > &SpriteAnims, Vector2 Padding )
	{
		boost::shared_ptr<ObjectClass> Obj = MyBob->PlayerObject;
		SpriteAnims.insert( std::make_pair( 0, Obj->AnimToSpriteFrames( 0, 1, true, Padding ) ) );
	}

	void BobPhsxSpaceship::Die( BobDeathType DeathType )
	{
		BobPhsx::Die( DeathType );

		MyBob->getCore()->Data.Velocity = Vector2(0, 25);
		MyBob->getCore()->Data.Acceleration = Vector2(0, -1.9f);

		Fireball::Explosion( MyBob->getCore()->Data.Position, MyBob->getCore()->MyLevel );
	}

	void BobPhsxSpaceship::BlockInteractions()
	{
		if ( getCore()->MyLevel->PlayMode != 0 )
			return;

		for ( BlockVec::const_iterator block = getCore()->MyLevel->Blocks.begin(); block != getCore()->MyLevel->Blocks.end(); ++block )
		{
			if ( !( *block )->getCore()->MarkedForDeletion && (*block)->getCore()->Real && (*block)->getIsActive() && (*block)->getCore()->Active && Phsx::BoxBoxOverlap(MyBob->Box2, (*block)->getBox()) )
			{
				if ( !MyBob->Immortal )
					MyBob->Die( BobDeathType_OTHER );
				else
					( *block )->Hit( MyBob );
			}
		}
	}

	void BobPhsxSpaceship::ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style )
	{
		BobPhsx::ModData( makeData, Style );

		Style->MyInitialPlatsType = StyleData::InitialPlatsType_SPACESHIP;
		Style->TopSpace = 0;
		makeData->SparsityMultiplier = 1.5f;

		Style->BlockFillType = StyleData::_BlockFillType_INVERTABLE;
		Style->OverlapCleanupType = StyleData::_OverlapCleanupType_SOPHISTICATED;

		Style->DoorHitBoxPadding = Vector2( -60, 0 );

		Style->MinBlockDist = 250;
		Style->RemovedUnusedOverlappingBlocks = true;
		Style->RemoveBlockOnOverlap = true;

		Style->BottomSpace = 150;
		Style->TopSpace = 0;

		Style->SafeStartPadding = 400;
		Style->SafeEndPadding = -1000;
		Style->LengthPadding = 1200;
		Style->AutoOpenDoor = true;

		makeData->TopLikeBottom = true;

		Style->MyGroundType = StyleData::GroundType_VIRGIN_USED;
		Style->MyTopType = StyleData::GroundType_INVERTED_USED;
		Style->UpperSafetyNetOffset = -100;
		Style->LowerSafetyNetOffset = -200;

		boost::shared_ptr<GhostBlock_Parameters> GhParams = boost::static_pointer_cast<GhostBlock_Parameters>( Style->FindParams( GhostBlock_AutoGen::getInstance() ) );
		GhParams->BoxType = GhostBlock_Parameters::BoxTypes_FULL;
	}

	void BobPhsxSpaceship::ModLadderPiece( const boost::shared_ptr<PieceSeedData> &piece )
	{
		 BobPhsx::ModLadderPiece( piece );

		piece->ElevatorBoxStyle = BoxStyle_FULL_BOX;
	}

	void BobPhsxSpaceship::InitializeInstanceFields()
	{
		Dir = 0;
	}
}
