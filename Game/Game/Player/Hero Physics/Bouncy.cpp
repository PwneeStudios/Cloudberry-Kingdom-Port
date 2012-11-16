#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void BobPhsxBouncy::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 3, 0, 0, 0 );
		Name = Localization::Words_BOUNCY;
		NameTemplate = _T( "bouncey bounce" );

		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "Bob_Horse_0000" ) ), Color::White, 1.35875f * DefaultIconWidth );
		( static_cast<PictureIcon*>( Icon ) )->IconQuad->Quad_Renamed->Shift( Vector2( 0, -.035f ) );
	}

const std::shared_ptr<BobPhsxBouncy> BobPhsxBouncy::instance = std::make_shared<BobPhsxBouncy>();

	const std::shared_ptr<BobPhsxBouncy> &BobPhsxBouncy::getInstance() const
	{
		return instance;
	}

	BobPhsxBouncy::BobPhsxBouncy()
	{
		InitializeInstanceFields();
	}

	void BobPhsxBouncy::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );

		InitializedAnim = false;
		MyBob->PlayerObject->Read( 24, 0 );
	}

	void BobPhsxBouncy::DefaultValues()
	{
		 BobPhsxNormal::DefaultValues();

		BlobMod = .4f;

		BobInitialJumpSpeedDucking = 24;
		BobInitialJumpSpeed = 40;
		BobJumpLength = 0;
		BobJumpAccel = 0;

		CapeOffset = Vector2( 0, 30 );
	}

	void BobPhsxBouncy::DuckingPhsx()
	{
		bool Down = MyBob->CurInput.xVec.Y < -.4f;
		if ( Down )
			Ducking = true;
		else
			Ducking = false;
	}

	void BobPhsxBouncy::UpdateReadyToJump()
	{
		if ( !OnGround && CurJump > 0 )
			BobPhsxNormal::UpdateReadyToJump();
		else
			ReadyToJump = true;
	}

	void BobPhsxBouncy::Jump()
	{
		SuperBounceGrace = 9;
		if ( !OnGround && CurJump > 0 )
		{
			// Allow for super bounce a few frames after hitting the ground
			if ( getMyLevel()->PlayMode == 0 )
			{
				if ( MyBob->CurInput.A_Button && SuperBounceGraceCount > 0 )
				{
					//Tools.Write("Delayed super bounce!");
					setyVel( getyVel() + SuperBounce );
					SuperBounceGraceCount = 0;
				}
				else
					SuperBounceGraceCount--;
			}

			BobPhsxNormal::Jump();
		}
		else
		{
			UpdateReadyToJump();

			if ( getCanJump() )
			{
				DoJump();

				if ( MyBob->CurInput.A_Button )
					setyVel( getyVel() + SuperBounce );
				else
				{
					if ( getMyLevel()->PlayMode == 0 )
					{
						//FakeVel = yVel + SuperBounce;
						SuperBounceGraceCount = SuperBounceGrace;
					}
				}
			}
		}
	}

	void BobPhsxBouncy::AnimStep()
	{
		if ( !InitializedAnim )
		{
			MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 24, 0, false );
			MyBob->PlayerObject->DequeueTransfers();

			InitializedAnim = true;
		}

		//if (MyBob.Core.Data.Velocity.Y > 10f && !OnGround && StartJumpAnim)
		if ( ShouldStartJumpAnim() )
		{
			MyBob->PlayerObject->AnimQueue.clear();
			MyBob->PlayerObject->EnqueueAnimation( 24, 0, false );
			MyBob->PlayerObject->DequeueTransfers();
			MyBob->PlayerObject->LastAnimEntry->AnimSpeed *= .85f;

			StartJumpAnim = false;
		}

		if ( MyBob->IsSpriteBased )
			MyBob->PlayerObject->PlayUpdate( 1 );
		else
			MyBob->PlayerObject->PlayUpdate( 1000 / 60 / 150 );
	}

	void BobPhsxBouncy::InitializeInstanceFields()
	{
		SuperBounce = 18;
		SuperBounceGraceCount = 0;
		SuperBounceGrace = 10;
	}
}
