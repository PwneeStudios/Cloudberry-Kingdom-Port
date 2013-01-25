#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxInvert::InitializeStatics()
	{
		BobPhsxInvert::instance = boost::make_shared<BobPhsxInvert>();
			InitBobPhsxSingleton( BobPhsxInvert::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxInvert> BobPhsxInvert::instance;


	void BobPhsxInvert::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 0, 3, 0 );
		Name = Localization::Words_VIRIDIAN;
		Adjective = std::wstring( L"Anti-Grav" );

		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"Bob_Run_0024" ) ), Color::White, DefaultIconWidth * -1.2f );

		HeroDollShift = Vector2( 0, 100 );
	}

	const boost::shared_ptr<BobPhsxInvert> &BobPhsxInvert::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<BobPhsx> BobPhsxInvert::Clone()
	{
		boost::shared_ptr<BobPhsxInvert> newBob = boost::make_shared<BobPhsxInvert>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return boost::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxInvert::CopyTo( const boost::shared_ptr<BobPhsxInvert> &bob )
	{
		BobPhsxNormal::CopyTo( boost::static_pointer_cast<BobPhsxNormal>( bob ) );

		bob->CurBehavior = CurBehavior;
		bob->BehaviorLength = BehaviorLength;
		bob->Count = Count;
	}

	BobPhsxInvert::BobPhsxInvert() :
		CurBehavior( Behavior_REGULAR ),
		BehaviorLength( 0 ),
		Count( 0 )
	{
		InitializeInstanceFields();
		// Pulled out to avoid using shared_from_this inside constructor.
		//Set( shared_from_this() );
		DefaultValues();
	}

	void BobPhsxInvert::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
		Set( phsx, Vector2(1) );
	}

	void BobPhsxInvert::Set( const boost::shared_ptr<BobPhsx> &phsx, Vector2 modsize )
	{
		//MustHitGroundToReadyJump = true;

		boost::shared_ptr<BobPhsxNormal> normal = boost::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
			normal->BobJumpLength = 1;
			normal->BobJumpAccel = 0;
			normal->BobInitialJumpSpeed = 0;
			normal->Gravity = 4;
			normal->BobMaxFallSpeed = -30;
		}
	}

	void BobPhsxInvert::Init( const boost::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		BobJumpAccel = -fabs( BobJumpAccel );

		Gravity = fabs( Gravity );
		BobInitialJumpSpeed = fabs( BobInitialJumpSpeed );
		BobInitialJumpSpeed2 = fabs( BobInitialJumpSpeed2 );
		BobInitialJumpSpeedDucking = fabs( BobInitialJumpSpeedDucking );
		BobInitialJumpSpeedDucking2 = fabs( BobInitialJumpSpeedDucking2 );
		BobMaxFallSpeed = -fabs( BobMaxFallSpeed );
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

	void BobPhsxInvert::LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		if ( Gravity < 0 )
			BobPhsxNormal::HitHeadOnSomething( ThingLandedOn );
		else
			BobPhsxNormal::LandOnSomething( MakeReadyToJump, ThingLandedOn );
	}

	void BobPhsxInvert::HitHeadOnSomething( const boost::shared_ptr<ObjectBase> &ThingHit )
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

	void BobPhsxInvert::SetTarget( const boost::shared_ptr<RichLevelGenData> &GenData )
	{
		if ( Count <= 0 || fabs( MyBob->TargetPosition.Y - getPos().Y ) < 200 )
		{
			Count = getMyLevel()->getRnd()->RndInt(30, 60);

			if ( getPos().Y > getCam()->getPos().Y )
				MyBob->TargetPosition.Y = MyBob->MoveData.MinTargetY;
			else
				MyBob->TargetPosition.Y = MyBob->MoveData.MaxTargetY - getMyLevel()->getRnd()->RndFloat(400, 900);
		}
		else
			Count--;
	}

	void BobPhsxInvert::PreventEarlyLandings( const boost::shared_ptr<RichLevelGenData> &GenData )
	{
		// Do nothing
	}

	void BobPhsxInvert::ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style )
	{
		BobPhsxNormal::ModData( makeData, Style );

		makeData->TopLikeBottom_Thin = true;
		makeData->BlocksAsIs = true;

		boost::shared_ptr<Ceiling_Parameters> Ceiling_Params = boost::static_pointer_cast<Ceiling_Parameters>( Style->FindParams( Ceiling_AutoGen::getInstance() ) );
		Ceiling_Params->Make = false;

		Style->BlockFillType = StyleData::_BlockFillType_INVERTABLE;
		Style->UseLowerBlockBounds = true;
		Style->OverlapCleanupType = StyleData::_OverlapCleanupType_SOPHISTICATED;

		Style->TopSpace = 50;

		boost::shared_ptr<MovingBlock_Parameters> MParams = boost::static_pointer_cast<MovingBlock_Parameters>( Style->FindParams( MovingBlock_AutoGen::getInstance() ) );
		if ( MParams->Aspect == MovingBlock_Parameters::AspectType_TALL )
			MParams->Aspect = MovingBlock_Parameters::AspectType_THIN;

		boost::shared_ptr<GhostBlock_Parameters> GhParams = boost::static_pointer_cast<GhostBlock_Parameters>( Style->FindParams( GhostBlock_AutoGen::getInstance() ) );
		GhParams->BoxType = GhostBlock_Parameters::BoxTypes_LONG;
	}

	void BobPhsxInvert::ModLadderPiece( const boost::shared_ptr<PieceSeedData> &piece )
	{
		BobPhsxNormal::ModLadderPiece( piece );

		piece->ElevatorBoxStyle = BoxStyle_NO_SIDES;
	}

	bool BobPhsxInvert::IsBottomCollision( ColType Col, const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block )
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
