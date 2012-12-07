#include <global_header.h>

namespace CloudberryKingdom
{

	void BobPhsxRocketbox::InitSingleton()
	{
		BobPhsxBox::InitSingleton();

		Specification = HeroSpec( 6, 0, 0, 0 );
		Name = Localization::Words_ROCKETBOX;
		NameTemplate = _T( "rocketbox" );
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "HeroIcon_Cart" ) ), Color::White, DefaultIconWidth );
		( std::static_pointer_cast<PictureIcon>( Icon ) )->IconQuad->Quad_Renamed.Shift( Vector2( 0, -.485f ) );
	}

const std::shared_ptr<BobPhsxRocketbox> BobPhsxRocketbox::instance = std::make_shared<BobPhsxRocketbox>();

	const std::shared_ptr<BobPhsxRocketbox> &BobPhsxRocketbox::getInstance()
	{
		return instance;
	}

	BobPhsxRocketbox::BobPhsxRocketbox()
	{
		InitializeInstanceFields();
	}

	void BobPhsxRocketbox::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsxBox::Init( bob );
		//if (MyBob.Core.MyLevel.PlayMode == 0)
		if ( Prototype != 0 && MyBob->PlayerObject != 0 && MyBob->PlayerObject->QuadList.size() > 0 )
		{
			LeftWheel = std::dynamic_pointer_cast<Quad>( MyBob->PlayerObject->FindQuad( _T( "Wheel_Left" ) ) );
			RightWheel = std::dynamic_pointer_cast<Quad>( MyBob->PlayerObject->FindQuad( _T( "Wheel_Right" ) ) );
		}
	}

	void BobPhsxRocketbox::SideHit( ColType side, const std::shared_ptr<BlockBase> &block )
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
		MyBob->CurInput.xVec.X = 1;
		BobPhsxBox::ParentDoXAccel();
	}

	void BobPhsxRocketbox::AnimStep()
	{
		BobPhsxBox::AnimStep();

		if ( MyBob->getCore()->MyLevel->PlayMode == 0 )
		{
			WheelAngle -= getxVel() *.33f / 60;

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
			Vector2 pos = Vector2( -45, -30 );
			pos.Y -= 40;
			Vector2 dir = Vector2( -1.115f, -.025f );

			if ( MyBob->PlayerObject->xFlip )
			{
				pos.X *= -1;
				dir.X *= -1;
			}
			pos += getPos();

			int layer = __max( 1, MyBob->getCore()->DrawLayer - 1 );
			ParticleEffects::CartThrust( MyBob->getCore()->MyLevel, layer, pos, dir, Vector2() );
			//ParticleEffects.Thrust(MyBob.Core.MyLevel, layer, pos, dir, Vel / 1.5f);
		}
	}

	void BobPhsxRocketbox::InitializeInstanceFields()
	{
		WheelAngle = 0;
	}
}
