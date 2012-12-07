#include <global_header.h>

namespace CloudberryKingdom
{
	void BobPhsxInvert::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 0, 3, 0 );
		Name = Localization::Words_VIRIDIAN;
		Adjective = _T( "Anti-Grav" );

		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "Bob_Run_0024" ) ), Color::White, DefaultIconWidth * -1.2f );

		HeroDollShift = Vector2( 0, 100 );
	}

const std::shared_ptr<BobPhsxInvert> BobPhsxInvert::instance = std::make_shared<BobPhsxInvert>();

	const std::shared_ptr<BobPhsxInvert> &BobPhsxInvert::getInstance()
	{
		return instance;
	}

	BobPhsxInvert::BobPhsxInvert()
	{
		InitializeInstanceFields();
		Set( shared_from_this() );
	}

	void BobPhsxInvert::Set( const std::shared_ptr<BobPhsx> &phsx )
	{
		Set( phsx, Vector2(1) );
	}

	void BobPhsxInvert::Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize )
	{
		//MustHitGroundToReadyJump = true;

		std::shared_ptr<BobPhsxNormal> normal = std::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
			normal->BobJumpLength = 1;
			normal->BobJumpAccel = 0;
			normal->BobInitialJumpSpeed = 0;
			normal->Gravity = 4;
			normal->BobMaxFallSpeed = -30;
		}
	}

	void BobPhsxInvert::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		BobJumpAccel = -abs( BobJumpAccel );

		Gravity = abs( Gravity );
		BobInitialJumpSpeed = abs( BobInitialJumpSpeed );
		BobInitialJumpSpeed2 = abs( BobInitialJumpSpeed2 );
		BobInitialJumpSpeedDucking = abs( BobInitialJumpSpeedDucking );
		BobInitialJumpSpeedDucking2 = abs( BobInitialJumpSpeedDucking2 );
		BobMaxFallSpeed = -abs( BobMaxFallSpeed );
	}

	void BobPhsxInvert::PhsxStep()
	{
		BobPhsxNormal::PhsxStep();

		getObj()->yFlip = Gravity < 0;

		// Cape is always fallling opposite to the direction of Bob
		//CapeGravity = Math.Sign(-Gravity) * new Vector2(0, -1.45f) / 1.45f;

		// Cape is always fallling up
		CapeGravity = Vector2( 0, -1.45f ) / 1.45f;

		// If we are falling (and not falling too fast already),
		// accelerate if the player is pressing (A).
		if ( !OnGround && MyBob->CurInput.A_Button && AirTime > 7 && DynamicGreaterThan( getyVel(), BobMaxFallSpeed * 2 ) )
			setyVel( getyVel() - Gravity );
	}

	void BobPhsxInvert::UpdateReadyToJump()
	{
		BobPhsxNormal::UpdateReadyToJump();

		if ( MyBob->Count_ButtonA > 4 )
			ReadyToJump = false;
	}

	void BobPhsxInvert::DoJump()
	{
		BobJumpAccel *= -1;

		BobPhsxNormal::DoJump();

		Gravity *= -1;
		ForceDown *= -1;

		BobInitialJumpSpeed *= -1;
	}

	void BobPhsxInvert::Invert()
	{
		BobJumpAccel *= -1;

		Gravity *= -1;
		ForceDown *= -1;

		BobInitialJumpSpeed *= -1;
	}

	void BobPhsxInvert::Forced( Vector2 Dir )
	{
		BobPhsxNormal::Forced( Dir );

		if ( Sign( Dir.Y ) == Sign( Gravity ) )
			Invert();
	}

	void BobPhsxInvert::LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		if ( Gravity < 0 )
			BobPhsxNormal::HitHeadOnSomething( ThingLandedOn );
		else
			BobPhsxNormal::LandOnSomething( MakeReadyToJump, ThingLandedOn );
	}

	void BobPhsxInvert::HitHeadOnSomething( const std::shared_ptr<ObjectBase> &ThingHit )
	{
		if ( Gravity < 0 )
			BobPhsxNormal::LandOnSomething( false, ThingHit );
		else
			BobPhsxNormal::HitHeadOnSomething( ThingHit );
	}

	bool BobPhsxInvert::ShouldStartJumpAnim()
	{
		return StartJumpAnim;
	}

	void BobPhsxInvert::GenerateInput( int CurPhsxStep )
	{
		BobPhsxNormal::GenerateInput( CurPhsxStep );

		// Change behavior
		if ( CurPhsxStep < 10 )
		{
			CurBehavior = Behavior_PAUSE;
			BehaviorLength = 0;
		}
		else
		{
			if ( BehaviorLength == 0 )
			{
				float ChanceToPause = .3f;
				if ( getMyLevel()->CurPhsxStep > 600 )
					ChanceToPause = .15f;
				else if ( getMyLevel()->CurPhsxStep > 850 )
					ChanceToPause = .05f;
				else if ( getMyLevel()->CurPhsxStep > 950 )
					ChanceToPause = 0;

				if ( getMyLevel()->getRnd()->RndFloat() < ChanceToPause )
				{
					CurBehavior = Behavior_PAUSE;
					BehaviorLength = getMyLevel()->getRnd()->RndInt(3, 10);
				}
				else
				{
					CurBehavior = Behavior_REGULAR;
					BehaviorLength = getMyLevel()->getRnd()->RndInt(35, 60);
				}
			}
			else
				BehaviorLength--;
		}

		// Act according to behavior
		switch ( CurBehavior )
		{
			case Behavior_PAUSE:
				MyBob->CurInput.xVec.X = 0;
				break;
			case Behavior_REGULAR:
				break;
		}

		if ( getPos().Y > 600 && Gravity < 0 || getPos().Y < -550 && Gravity > 0 )
		{
			MyBob->CurInput.A_Button = true;
			MyBob->Count_ButtonA = 0;
		}
		if ( getPos().Y > 600 && Gravity > 0 || getPos().Y < -550 && Gravity < 0 )
		{
			MyBob->CurInput.A_Button = false;
			MyBob->Count_ButtonA = 0;
		}
	}

	void BobPhsxInvert::SetTarget( const std::shared_ptr<RichLevelGenData> &GenData )
	{
		if ( Count <= 0 || abs( MyBob->TargetPosition.Y - getPos().Y ) < 200 )
		{
			Count = getMyLevel()->getRnd()->RndInt(30, 60);

			if ( getPos().Y > getCam()->getPos().Y )
				MyBob->TargetPosition.Y = MyBob->MoveData->MinTargetY;
			else
				MyBob->TargetPosition.Y = MyBob->MoveData->MaxTargetY - getMyLevel()->getRnd()->RndFloat(400, 900);
		}
		else
			Count--;
	}

	void BobPhsxInvert::PreventEarlyLandings( const std::shared_ptr<RichLevelGenData> &GenData )
	{
		// Do nothing
	}

	void BobPhsxInvert::ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style )
	{
		BobPhsxNormal::ModData( makeData, Style );

		makeData->TopLikeBottom_Thin = true;
		makeData->BlocksAsIs = true;

		std::shared_ptr<Ceiling_Parameters> Ceiling_Params = std::static_pointer_cast<Ceiling_Parameters>( Style->FindParams( Ceiling_AutoGen::getInstance() ) );
		Ceiling_Params->Make = false;

		Style->BlockFillType = StyleData::_BlockFillType_INVERTABLE;
		Style->OverlapCleanupType = StyleData::_OverlapCleanupType_SOPHISTICATED;

		Style->TopSpace = 50;

		std::shared_ptr<MovingBlock_Parameters> MParams = std::static_pointer_cast<MovingBlock_Parameters>( Style->FindParams( MovingBlock_AutoGen::getInstance() ) );
		if ( MParams->Aspect == MovingBlock_Parameters::AspectType_TALL )
			MParams->Aspect = MovingBlock_Parameters::AspectType_THIN;

		std::shared_ptr<GhostBlock_Parameters> GhParams = std::static_pointer_cast<GhostBlock_Parameters>( Style->FindParams( GhostBlock_AutoGen::getInstance() ) );
		GhParams->BoxType = GhostBlock_Parameters::BoxTypes_FULL;
	}

	void BobPhsxInvert::ModLadderPiece( const std::shared_ptr<PieceSeedData> &piece )
	{
		BobPhsxNormal::ModLadderPiece( piece );

		piece->ElevatorBoxStyle = BoxStyle_FULL_BOX;
	}

	bool BobPhsxInvert::IsBottomCollision( ColType Col, const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block )
	{
		return Col == ColType_BOTTOM || Col != ColType_BOTTOM && getCore()->Data.Velocity.X != 0 && __min(MyBob->Box->Current->TR.Y, MyBob->Box->Target->TR.Y) < box->Target->BL.Y + __max(1.35 * getCore()->Data.Velocity.Y, 7);
	}

	void BobPhsxInvert::DollInitialize()
	{
		BobPhsxNormal::DollInitialize();

		Invert();
		LandOnSomething( true, 0 );
	}

	void BobPhsxInvert::InitializeInstanceFields()
	{
		CurBehavior = Behavior_PAUSE;
		Count = 0;
	}
}
