#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxRocketbox::InitializeStatics()
	{
		BobPhsxRocketbox::instance = boost::make_shared<BobPhsxRocketbox>();
			InitBobPhsxSingleton( BobPhsxRocketbox::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxRocketbox> BobPhsxRocketbox::instance;

	void BobPhsxRocketbox::InitSingleton()
	{
		BobPhsxBox::InitSingleton();

		Specification = HeroSpec( 6, 0, 0, 0 );
		Name = Localization::Words_Rocketbox;
		NameTemplate = std::wstring( L"rocketbox" );
		//Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"HeroIcon_Cart" ) ), Color::White, DefaultIconWidth );
		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( L"CartIcon" ), Color::White, DefaultIconWidth * 1.315f);
		( boost::static_pointer_cast<PictureIcon>( Icon ) )->IconQuad->Quad_Renamed.Shift( Vector2( 0, 0 ) );
	}

	const boost::shared_ptr<BobPhsxRocketbox> &BobPhsxRocketbox::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<BobPhsx> BobPhsxRocketbox::Clone()
	{
		boost::shared_ptr<BobPhsxRocketbox> newBob = boost::make_shared<BobPhsxRocketbox>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return boost::static_pointer_cast<BobPhsx>( newBob );
	}

	void BobPhsxRocketbox::CopyTo( const boost::shared_ptr<BobPhsxRocketbox> &bob )
	{
		BobPhsxBox::CopyTo( boost::static_pointer_cast<BobPhsxBox>( bob ) );

		bob->LeftWheel = LeftWheel;
		bob->RightWheel = RightWheel;
		bob->WheelAngle = WheelAngle;
	}


	BobPhsxRocketbox::BobPhsxRocketbox()
	{
		InitializeInstanceFields();
		DefaultValues();
	}

	void BobPhsxRocketbox::Init( const boost::shared_ptr<Bob> &bob )
	{
        StandAnim = 17; JumpAnim = 18; DuckAnim = 19;

        ExtraQuadString = L"MainQuad";
        ExtraTextureString = L"CartAlone";

        CapeOffset += Vector2(-50, 50);
        CapeOffset_Ducking += Vector2(-50, 50);

		BobPhsxBox::Init( bob );
		//if (MyBob.Core.MyLevel.PlayMode == 0)
		if ( Prototype != 0 && MyBob->PlayerObject != 0 && MyBob->PlayerObject->QuadList.size() > 0 )
		{
			LeftWheel = boost::dynamic_pointer_cast<Quad>( MyBob->PlayerObject->FindQuad( std::wstring( L"Wheel_Left" ) ) );
            LeftWheel->Show = true;
            LeftWheel->SetColor( ColorHelper::GrayColor( .5f ) );
            LeftWheel->MyEffect = Tools::HslGreenEffect;

			RightWheel = boost::dynamic_pointer_cast<Quad>( MyBob->PlayerObject->FindQuad( std::wstring( L"Wheel_Right" ) ) );
            RightWheel->Show = true;
            RightWheel->MyEffect = Tools::HslGreenEffect;
            RightWheel->SetColor( ColorHelper::GrayColor( .5f ) );
		}
	}

	void BobPhsxRocketbox::SideHit( ColType side, const boost::shared_ptr<BlockBase> &block )
	{
		BobPhsxBox::SideHit( side, block );

		if ( MyBob->getCanDie() )
			MyBob->Die( BobDeathType_OTHER );
	}

	void BobPhsxRocketbox::DefaultValues()
	{
		BobPhsxBox::DefaultValues();

		MaxSpeed = 30;
		XAccel = .38f;
	}

	void BobPhsxRocketbox::DoXAccel()
	{
        bool HoldDucking = Ducking;
        Ducking = false;

		MyBob->CurInput.xVec.X = 1;
		BobPhsxBox::ParentDoXAccel();

		Ducking = HoldDucking;
	}

	void BobPhsxRocketbox::AnimStep()
	{
		BobPhsxBox::AnimStep();

		if ( MyBob->getCore()->MyLevel->PlayMode == 0 )
		{
			WheelAngle -= getxVel() * 1.f / 60;

            LeftWheel->MyEffect = Tools::HslEffect;
            RightWheel->MyEffect = Tools::HslEffect;

			LeftWheel->PointxAxisTo( CoreMath::AngleToDir( WheelAngle ) );
			RightWheel->PointxAxisTo( CoreMath::AngleToDir( WheelAngle ) );
		}
	}

	void BobPhsxRocketbox::GenerateInput( int CurPhsxStep )
	{
		BobPhsxBox::ParentGenerateInput( CurPhsxStep );

		// Full jumps
		if ( !OnGround && getyVel() > 0 )
			MyBob->CurInput.A_Button = true;
	}

	void BobPhsxRocketbox::PhsxStep2()
	{
		BobPhsxBox::PhsxStep2();

		// Rocketman thrust
		if ( MyBob->getCore()->MyLevel->PlayMode == 0 )
		{
			//Vector2 pos = Vector2( -45, -30 );
			//pos.Y -= 40;
			//Vector2 dir = Vector2( -1.115f, -.025f );

			//if ( MyBob->PlayerObject->xFlip )
			//{
			//	pos.X *= -1;
			//	dir.X *= -1;
			//}
			//pos += getPos();

			//int layer = __max( 1, MyBob->getCore()->DrawLayer - 1 );
			//ParticleEffects::CartThrust( MyBob->getCore()->MyLevel, layer, pos, dir, Vector2() );

            int layer = __max( 1, MyBob->getCore()->DrawLayer - 1 );
            float intensity = 1.3f * __min( .3f + ( MyBob->CurInput.xVec.X + .3f ), 1.f );
            ParticleEffects::Thrust( MyBob->getCore()->MyLevel, layer, getPos() + Vector2(0, -20), Vector2(-1, 0), Vector2(-4, getyVel() ), intensity );
		}
	}

	void BobPhsxRocketbox::InitializeInstanceFields()
	{
		WheelAngle = 0;
	}
}
