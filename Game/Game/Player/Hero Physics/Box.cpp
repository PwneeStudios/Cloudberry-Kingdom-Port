#include <global_header.h>



namespace CloudberryKingdom
{

	void BobPhsxBox::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 1, 0, 0, 0 );
		Name = Localization::Words_HERO_IN_ABOX;
		NameTemplate = _T( "hero in a box" );

		//Icon = new PictureIcon(Tools.TextureWad.FindByName("HeroIcon_Box"), Color.White, DefaultIconWidth * 1.125f);
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "Bob_Box_Duck_0000" ) ), Color::White, DefaultIconWidth * 1.35f );
		( std::static_pointer_cast<PictureIcon>( Icon ) )->IconQuad->Quad_Renamed.Shift( Vector2( 0,.0485f ) );
	}

const std::shared_ptr<BobPhsxBox> BobPhsxBox::instance = std::make_shared<BobPhsxBox>();

	const std::shared_ptr<BobPhsxBox> &BobPhsxBox::getInstance()
	{
		return instance;
	}

	BobPhsxBox::BobPhsxBox()
	{
		InitializeInstanceFields();
		LandSound = Tools::SoundWad->FindByName( _T( "BoxHero_Land" ) );

		DefaultValues();
	}

	void BobPhsxBox::DefaultValues()
	{
		 BobPhsxNormal::DefaultValues();

		BobJumpAccel = ( Gravity + 3.45f ) / 19;
		BobInitialJumpSpeed = 6;
		BobInitialJumpSpeedDucking = 6;
		BobJumpLength = 18;
		BobJumpLengthDucking = 17;

		BobJumpAccel2 = ( Gravity + 3.42f ) / 19;
		BobInitialJumpSpeed2 = 14;
		BobInitialJumpSpeedDucking2 = 12;
		BobJumpLength2 = 17;
		BobJumpLengthDucking2 = 17;

		MaxSpeed = 13.6f; // 15f;
		XAccel = .45f;
		XFriction = .85f;
		BobXDunkFriction = .65f;
	}

	void BobPhsxBox::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		MyBob->JumpSound = Tools::SoundWad->FindByName( _T( "BoxHero_Jump" ) );

		InitializedAnim = false;

		OnGround = false;
		StartedJump = false;
		setJumpCount( 0 );
		FallingCount = 10000;

		Ducking = false;

		MyBob->PlayerObject->Read( 6, 1 );
	}

	void BobPhsxBox::DuckingPhsx()
	{
		bool HoldDucking = Ducking;

		BobPhsxNormal::DuckingPhsx();

		//if (DuckingCount == 2)
		//{
		//    Vector2 shift = new Vector2(0, -30);

		//    Pos += shift;

		//    MyBob.Box.Target.Center += shift;
		//    MyBob.Box2.Target.Center += shift;
		//    MyBob.Box.Target.CalcBounds();
		//    MyBob.Box2.Target.CalcBounds();

		//    Obj.ParentQuad.Center.Move(Obj.ParentQuad.Center.Pos + shift);
		//    Obj.ParentQuad.Update();
		//    Obj.Update(null, ObjectDrawOrder.WithOutline);

		//    if (MyBob.MyCape != null)
		//        MyBob.MyCape.Move(shift);
		//}

		if ( Ducking )
		{
			std::shared_ptr<CloudberryKingdom::ObjectClass> p = MyBob->PlayerObject;
			p->DrawExtraQuad = true;
			p->ExtraQuadToDraw = std::static_pointer_cast<Quad>( p->FindQuad( _T( "MainQuad" ) ) );
			p->ExtraQuadToDrawTexture = Tools::Texture( _T( "BoxAlone" ) );
		}
		else
		{
			std::shared_ptr<CloudberryKingdom::ObjectClass> p = MyBob->PlayerObject;
			p->DrawExtraQuad = false;
		}
	}

	void BobPhsxBox::ParentDoXAccel()
	{
		BobPhsxNormal::DoXAccel();
	}

	void BobPhsxBox::DoXAccel()
	{
		bool HoldDucking = Ducking;
		Ducking = true;
		BobPhsxNormal::DoXAccel();
		Ducking = HoldDucking;
	}

	void BobPhsxBox::ParentGenerateInput( int CurPhsxStep )
	{
		BobPhsxNormal::GenerateInput( CurPhsxStep );
	}

	void BobPhsxBox::GenerateInput( int CurPhsxStep )
	{
		BobPhsxNormal::GenerateInput( CurPhsxStep );

		if ( MyBob->CurInput.xVec.X > 0 )
			MyBob->CurInput.A_Button = true;
	}

	void BobPhsxBox::AnimStep()
	{
		if ( MyBob->PlayerObject->DestinationAnim() != StandAnim && OnGround || !InitializedAnim )
		{
			if ( !InitializedAnim )
			{
				MyBob->PlayerObject->AnimQueue.clear();
				InitializedAnim = true;
			}
			MyBob->PlayerObject->EnqueueAnimation( StandAnim, 0, true );
			MyBob->PlayerObject->DequeueTransfers();
		}

		if ( ShouldStartJumpAnim() )
		{
			MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( JumpAnim, 0.3f, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= .85f;

			StartJumpAnim = false;
		}

		// Ducking animation
		int DuckAnim = 8;
		if ( Ducking && MyBob->PlayerObject->DestinationAnim() != DuckAnim )
		{
			MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( DuckAnim, 1, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= 2.5f;
		}
		// Reverse ducking animation
		if ( !Ducking && MyBob->PlayerObject->DestinationAnim() == DuckAnim )
		{
			//MyBob.PlayerObject.DoSpriteAnim = false;

			MyBob->PlayerObject->AnimQueue.clear();
			if ( getyVel() > 0 )
				MyBob->PlayerObject->EnqueueAnimation( 6,.8f, false );
			else
				MyBob->PlayerObject->EnqueueAnimation( 7,.8f, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= 200;
		}

		if ( !Ducking )
		if ( MyBob->getCore()->Data.Velocity.Y < -.1f && !OnGround && MyBob->PlayerObject->anim == JumpAnim && MyBob->PlayerObject->LastAnimEntry->AnimSpeed > 0 )
		{
			MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( JumpAnim,.9f, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= -1;
		}

		if ( MyBob->IsSpriteBased )
			MyBob->PlayerObject->PlayUpdate( 1 );
		else
			MyBob->PlayerObject->PlayUpdate( 1000 / 60 / 150 );
	}

	void BobPhsxBox::InitializeInstanceFields()
	{
		StandAnim = 6;
		JumpAnim = 7;
		DuckAnim = 8;
	}
}
