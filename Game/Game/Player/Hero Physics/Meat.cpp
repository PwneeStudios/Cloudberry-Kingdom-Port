#include <global_header.h>
namespace CloudberryKingdom
{

	void BobPhsxMeat::Release()
	{
		BobPhsxNormal::Release();

		LastStickyBlock.reset();
	}

	void BobPhsxMeat::Set( const std::shared_ptr<BobPhsx> &phsx )
	{
		Set( phsx, Vector2(1) );
	}

	void BobPhsxMeat::Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize )
	{
		phsx->ModInitSize = 1.25f * Vector2( .27f,.27f ) * modsize;
		phsx->CapePrototype = Cape::CapeType_SMALL;

		std::shared_ptr<BobPhsxNormal> normal = std::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
			normal->BobJumpLength = static_cast<int>( normal->BobJumpLength * 1.5f );
			normal->BobJumpAccel *= .5f;

			//normal.Gravity *= .85f;
			normal->Gravity *= .7f;
			normal->SetAccels();

			normal->ForcedJumpDamping = .9f;
		}

		BobJumpLength = 27;
		BobJumpAccel = .18f;
		Gravity = 2;
		MaxSpeed = 38.5f;
		XAccel = .5f;
		XFriction = .4f;

		MaxSpeed = 38;
		XAccel = .7f;
		XFriction = .7f;
	}

	void BobPhsxMeat::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 5, 0, 0, 0 );
		Name = Localization::Words_MEATBOY;
		Adjective = _T( "Meat" );
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "HeroIcon_Meat" ) ), Color::White, 1.2f * DefaultIconWidth );
	}

const std::shared_ptr<BobPhsxMeat> BobPhsxMeat::instance = std::make_shared<BobPhsxMeat>();

	const std::shared_ptr<BobPhsxMeat> &BobPhsxMeat::getInstance()
	{
		return instance;
	}

	BobPhsxMeat::BobPhsxMeat()
	{
		InitializeInstanceFields();
		Set( shared_from_this() );
	}

	void BobPhsxMeat::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		WallJumpCount = StepsSinceSide = StepsOnSide = 0;
		CanWallJump = false;

		Target = Vector2( float::MinValue, float::MinValue );
	}

	void BobPhsxMeat::SideHit( ColType side, const std::shared_ptr<BlockBase> &block )
	{
		BobPhsxNormal::SideHit( side, block );

		if ( block == 0 )
			return;

		LastStickyBlock = block;
		IsStuck = true;

		if ( side == ColType_RIGHT )
			StickySide = ColType_LEFT;
		if ( side == ColType_LEFT )
			StickySide = ColType_RIGHT;

		//float Factor;
		//if (yVel < 0)
		//    Factor = CoreMath.LerpRestrict(.3f, 1f, (float)StepsOnSide / StickyDuration);
		//else
		//    Factor = .765f;
		//float BlockSpeed = block.Box.Target.TR.Y - block.Box.Current.TR.Y;
		//yVel = Factor * (yVel - BlockSpeed) + BlockSpeed;


		StepsSinceSide = 0;

		//OnGround = true;
		//CurJump = 1;
		//JetPackCount = 0;
		//if (StepsOnSide < StickyDuration)
		//    base.LandOnSomething(false);
	}

	void BobPhsxMeat::LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		BobPhsxNormal::LandOnSomething( MakeReadyToJump, ThingLandedOn );

		StickySide = ColType_NO_COL;

		LastJumpWasSticky = false;
		StepsOnSide = 0;
		StepsSinceSide = 0;
	}

	void BobPhsxMeat::Jump()
	{
		BobPhsxNormal::Jump();

		if ( getExternalPreventJump() )
			return;

		if ( !MyBob->CurInput.A_Button )
			CanWallJump = true;

		if ( getyVel() < Max_yVel_ForWallJump && StickySide != ColType_NO_COL && CanWallJump && (StepsSinceSide < StickyGracePeriod && getyVel() <= 0 || StepsSinceSide < 2) && !getCanJump() && MyBob->CurInput.A_Button )
		{
			//StickySide = ColType.NoCol;
			IsStuck = false;

			StepsSinceSide = StickyGracePeriod;

			setxVel( getxVel() + -19.5f * getStickyDir() );
				//(StickySide == ColType.Right ? -1 : 1);

			DoJump();

			LastJumpWasSticky = true;

			setyVel( getyVel() - 2 );
			setJumpCount( getJumpCount() - 1 );
			WallJumpCount = SideJumpLength;
		}
	}

	float BobPhsxMeat::SideToDir( ColType side )
	{
		switch ( side )
		{
			case ColType_RIGHT:
				return 1;
			case ColType_LEFT:
				return -1;
			default:
				return 0;
		}
	}

	const float &BobPhsxMeat::getStickyDir() const
	{
		return SideToDir( StickySide );
	}

	void BobPhsxMeat::PhsxStep()
	{
		// Additional wall jumping phsx
		if ( WallJumpCount > 0 )
		{
			if ( !MyBob->CurInput.A_Button || abs( MyBob->CurInput.xVec.X ) > ::3 && Math::Sign( MyBob->CurInput.xVec.X ) == getStickyDir() )
				WallJumpCount = 0;
			else
			{
				setxVel( getxVel() - SideJumpStr * getStickyDir() * WallJumpCount / static_cast<float>(SideJumpLength) );
				WallJumpCount--;
			}
		}

		StepsSinceSide++;

		// Additional sticky phsx
		//if (IsStuck)
		{
			if ( StepsSinceSide < 2 )
				StepsOnSide++;
			else
				StepsOnSide = 0;
		}
		if ( IsStuck && LastStickyBlock != 0 )
		{
			if ( LastStickyBlock->getBox()->TR.Y > MyBob->Box->BL.Y && LastStickyBlock->getBox()->BL.Y < MyBob->Box->TR.Y )
			{
				if ( StickySide == ColType_RIGHT )
				{
					float speed = LastStickyBlock->getBox()->LeftSpeed() + 1;
					if ( getxVel() < speed )
						setxVel( speed );
					SideHit( ColType_LEFT, LastStickyBlock );
				}

				if ( StickySide == ColType_LEFT )
				{
					float speed = LastStickyBlock->getBox()->RightSpeed() - 1;
					if ( getxVel() > speed )
						setxVel( speed );
					SideHit( ColType_RIGHT, LastStickyBlock );
				}
			}
			else
			{
				IsStuck = false;
				StepsSinceSide += 3;
			}

			if ( StickySide == ColType_RIGHT && MyBob->CurInput.xVec.X < -.3f )
				IsStuck = false;
			if ( StickySide == ColType_LEFT && MyBob->CurInput.xVec.X > ::3 )
				IsStuck = false;
		}

		BobPhsxNormal::PhsxStep();
	}

	void BobPhsxMeat::DoXAccel()
	{
		BobPhsxNormal::DoXAccel();
	}

	float BobPhsxMeat::GetXAccel()
	{
		//// For a few frames after jumping off a wall, force the player to move in the opposite direction
		//if (LastJumpWasSticky && StepsSinceSide > StickyGracePeriod)
		//{
		//    if (StepsSinceSide < StickyGracePeriod + 8)
		//    {
		//        MyBob.CurInput.xVec.X = -StickyDir;
		//        return base.GetXAccel() * .6f;
		//    }
		//    else if (StepsSinceSide < StickyGracePeriod + 20)
		//        return base.GetXAccel() * 1.35f;
		//}

		return BobPhsxNormal::GetXAccel();
	}

	void BobPhsxMeat::DoJump()
	{
		BobPhsxNormal::DoJump();

		CanWallJump = false;
		LastJumpWasSticky = false;
	}

	bool BobPhsxMeat::ShouldStartJumpAnim()
	{
		return StartJumpAnim;
	}

	void BobPhsxMeat::SetTarget( const std::shared_ptr<RichLevelGenData> &GenData )
	{
		BobPhsxNormal::SetTarget( GenData );
	}

	void BobPhsxMeat::NewTarget()
	{
		if ( getMyLevel()->Geometry == LevelGeometry_RIGHT )
		{
			AlwaysForward = Vector2::Max( AlwaysForward, getPos() ) + Vector2(300);
			Target = Vector2( .5f * ( getPos().X + getMyLevel()->getRnd()->RndFloat(-400, 3000) + AlwaysForward.X ), getMyLevel()->getRnd()->RndFloat(getCam()->BL.Y + 400, getCam()->TR.Y - 300) );
		}

		if ( getMyLevel()->Geometry == LevelGeometry_UP )
		{
			AlwaysForward = Vector2::Max( AlwaysForward, getPos() ) + Vector2(300);
			Target = Vector2( getMyLevel()->getRnd()->RndFloat(getCam()->BL.X + 600, getCam()->TR.X - 600),.5f * (getPos().Y + getMyLevel()->getRnd()->RndFloat(-400, 3000) + AlwaysForward.Y) );
		}

		PrefferedDir.X = Math::Sign( Target.X - getPos().X );
		//if (MyLevel.Rnd.RndBool())
		//    Target = new Vector2(Cam.TR.X, 100000);
		//else
		//    Target = new Vector2(Cam.BL.X, 100000);
	}

	void BobPhsxMeat::GenerateInput( int CurPhsxStep )
	{
		WantToLandOnTop = false;

		if ( Target.X < getPos().X - 10000 )
		{
			yVelCutoff = 20;
			NewTarget();
		}

		if ( abs( getxVel() ) < 5 && getyVel() > 5 && OnGround )
			if ( abs( Target.X - getPos().X ) < 200 )
			{
				NewTarget();
				if ( getPos().X > getCam()->getPos().X && Target.X > getCam()->getPos().X )
					NewTarget();
				if ( getPos().X < getCam()->getPos().X && Target.X < getCam()->getPos().X )
					NewTarget();
			}

		MyBob->WantsToLand = getPos().Y < Target.Y;
		MyBob->CurInput.A_Button = getPos().Y < Target.Y;

		int StickyWaitLength = 7; // 9;

		// Move right/left if target is to our right/left.
		if ( getPos().Y > getMyLevel()->Fill_TR.Y + 65 )
			MyBob->CurInput.xVec.X = Math::Sign( Target.X - getPos().X );
		else
			MyBob->CurInput.xVec.X = PrefferedDir.X;


		// Move right/left if we are sticking to a wall to our right/left.
		if ( StepsSinceSide < 5 && ( StickySide == ColType_RIGHT || StickySide == ColType_LEFT ) )
		{
			if ( StepsOnSide < StickyWaitLength && ( LastStickyBlock == 0 || LastStickyBlock->getBox()->BL.Y < MyBob->Box->TR.Y - 15 ) )
			{
				MyBob->CurInput.xVec.X = getStickyDir();
				MyBob->CurInput.A_Button = false;
			}
			else
			{
				MyBob->CurInput.A_Button = true;

				if ( StepsOnSide == StickyWaitLength )
				{
					// Make these higher to make the AI use blocks more often (and attempt less epically long jumps)
					yVelCutoff = getMyLevel()->getRnd()->RndFloat(-2, 12);

					//yVelCutoff = MyLevel.Rnd.RndFloat(-15, 12);
					//yVelCutoff = MyLevel.Rnd.RndFloat(-25, 12);
				//}
				//{
					NewTarget();
					for ( int i = 0; i < 2; i++ )
					{
						if ( getStickyDir() > 0 && Target.X > getPos().X )
							NewTarget();
						if ( getStickyDir() < 0 && Target.X < getPos().X && getMyLevel()->getRnd()->RndBool(.5f) )
							NewTarget();
					}
				}
			}
		}


		// Full force wall jump
		if ( StepsSinceSide >= 4 )
			MyBob->CurInput.A_Button = true;

		// Regular jump
		if ( OnGround )
			StraightUpDuration = 18;
		if ( StraightUpDuration > 0 )
		{
			MyBob->CurInput.xVec.X = -getStickyDir();
			MyBob->CurInput.A_Button = true;
			StraightUpDuration--;

			//if (Pos.X > Cam.TR.X - 900 ||
			//    Pos.X < Cam.BL.X + 900)
			MyBob->CurInput.xVec.X = Math::Sign( Target.X - getPos().X );
		}

		// Don't wall jump if we are going up fast
		//if (yVel > 14) MyBob.WantsToLand = false;
		//if (yVel > -5) MyBob.WantsToLand = false;
		//if (yVel > -15) MyBob.WantsToLand = false;
		if ( getyVel() > yVelCutoff )
			MyBob->WantsToLand = false;
		else
			MyBob->WantsToLand = true;

		// Don't use too many blocks in a row
		if ( CurPhsxStep < LastUsedStamp + 12 )
			MyBob->WantsToLand = false;

		if ( getPos().X > getCam()->TR.X - 550 || getPos().X < getCam()->BL.X + 550 )
		{
			if ( getyVel() < 5 )
				WantToLandOnTop = true;
			//MyBob.WantsToLand = false;
		}

		// Better jump control: don't use full extent of jump
		if ( StepsSinceSide >= 5 )
		{
			float RetardFactor = .01f * MyBob->getCore()->MyLevel->CurMakeData->GenData->Get(DifficultyParam_JUMPING_SPEED_RETARD_FACTOR, getPos());
			MyBob->CurInput.xVec.X *= RetardFactor;

			int RetardJumpLength = getGenData()->Get(DifficultyParam_RETARD_JUMP_LENGTH, getPos());
			if ( !OnGround && RetardJumpLength >= 1 && getJumpCount() < RetardJumpLength && getJumpCount() > 1 )
				MyBob->CurInput.A_Button = false;
		}
	}

	bool BobPhsxMeat::IsTopCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block )
	{
		return Col != ColType_NO_COL && Col == ColType_TOP;
	}

	bool BobPhsxMeat::IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block )
	{
		return Col == ColType_BOTTOM;
	}

	void BobPhsxMeat::ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style )
	{
		BobPhsxNormal::ModData( makeData, Style );

		float size = 90;
		bool ModSize = false;

		Style_BLOCK_FILL_TYPE = StyleData::_BlockFillType_SIDEWAYS;
		makeData->BlocksAsIs = true;

		// Don't keep anything extra
		Style->ChanceToKeepUnused = 0;

		// Square mblocks, vertical motion
		std::shared_ptr<MovingBlock_Parameters> MParams = std::static_pointer_cast<MovingBlock_Parameter>( Style->FindParams( MovingBlock_AutoGen::getInstance() ) );
		MParams->Aspect = MovingBlock_Parameters::AspectType_SQUARE;
		//MParams.Motion = MovingBlock_Parameters.MotionType.Vertical;
		//MParams.Motion = MovingBlock_Parameters.MotionType.Horizontal;
		//MParams.Size = size;

		std::shared_ptr<GhostBlock_Parameters> GhParams = std::static_pointer_cast<GhostBlock_Parameter>( Style->FindParams( GhostBlock_AutoGen::getInstance() ) );
		GhParams->BoxType = GhostBlock_Parameters::BoxTypes_LONG;
		std::shared_ptr<FallingBlock_Parameters> FParams = std::static_pointer_cast<FallingBlock_Parameter>( Style->FindParams( FallingBlock_AutoGen::getInstance() ) );
		std::shared_ptr<BouncyBlock_Parameters> BParams = std::static_pointer_cast<BouncyBlock_Parameter>( Style->FindParams( BouncyBlock_AutoGen::getInstance() ) );
		//var GParams = (Goomba_Parameters)Style.FindParams(Goomba_AutoGen.Instance);
		std::shared_ptr<NormalBlock_Parameters> NParams = std::static_pointer_cast<NormalBlock_Parameter>( Style->FindParams( NormalBlock_AutoGen::getInstance() ) );
		//NParams.CustomWeight = true;
		//NParams.FillWeight.Val = 1;

		Style->ModNormalBlockWeight = 1;

		if ( ModSize )
		{
			BParams->Size.SetVal( size );
			GhParams->Width.SetVal( size );
			FParams->Width.SetVal( size );
		}
	}

	void BobPhsxMeat::InitializeInstanceFields()
	{
		LastJumpWasSticky = false;
		StickyDuration = 60;
		IsStuck = false;
		StickyGracePeriod = 8;
		Max_yVel_ForWallJump = 20;
		SideJumpLength = 10;
		SideJumpStr = 5;
		WantToLandOnTop = false;
		StraightUpDuration = 0;
		yVelCutoff = 0;
	}
}
