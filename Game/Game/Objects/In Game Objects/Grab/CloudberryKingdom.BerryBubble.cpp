#include <global_header.h>


namespace CloudberryKingdom
{

	void BerryBubble::Rotate( float degrees )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<QuadClass*>::const_iterator quad = MyPile->MyQuadList.begin(); quad != MyPile->MyQuadList.end(); ++quad )
			( *quad )->Degrees += degrees;
	}

	void BerryBubble::MakeNew()
	{
		getCore()->ResetOnlyOnReset = true;

		if ( !getCore()->BoxesOnly )
		{
		}

		Popped = false;
		SetTexture();
	}

bool BerryBubble::_TexturesInitialized = false;
std::shared_ptr<EzTexture> PoppedTexture, UnpoppedTexture, BerryBubble::BubbleTexture = 0;

	void BerryBubble::SetTexture()
	{
		if ( !_TexturesInitialized )
		{
			BubbleTexture = Tools::TextureWad->FindByName( _T( "bubble" ) );
			//PoppedTexture = Tools.TextureWad.FindByName("cb_enthusiastic");
			PoppedTexture = Tools::TextureWad->FindByName( _T( "cb_falling" ) );
			UnpoppedTexture = Tools::TextureWad->FindByName( _T( "berrybubble" ) );
		}

		if ( getCore()->BoxesOnly )
			return;

		Bubble->Quad_Renamed->MyTexture = BubbleTexture;
		Bubble->setAlpha( 1 );
		Berry->Quad_Renamed->MyTexture = Popped ? PoppedTexture : UnpoppedTexture;

		Berry->ScaleXToMatchRatio( Radius );
		Bubble->ScaleXToMatchRatio( Popped ? Radius : PoppedRadius );

		_TexturesInitialized = true;
	}

	void BerryBubble::Die()
	{
		if ( getCore()->MyLevel->PlayMode != 0 )
			return;

		ParticleEffects::AddPop( getCore()->MyLevel, getPos() );

		Popped = true;
		SetTexture();
	}

	BerryBubble::BerryBubble( Vector2 pos )
	{
		InitializeInstanceFields();
		Init( false );
		Initialize( pos );
	}

	BerryBubble::BerryBubble( bool BoxesOnly )
	{
		InitializeInstanceFields();
		Init( BoxesOnly );
	}

	void BerryBubble::Init( bool BoxesOnly )
	{
		Box = std::make_shared<CircleBox>();
		if ( !BoxesOnly )
		{
			MyPile = std::make_shared<DrawPile>();

			Berry = std::make_shared<QuadClass>( 0, true, true );
			MyPile->Add( Berry );
			Bubble = std::make_shared<QuadClass>( 0, true, true );
			MyPile->Add( Bubble );
		}

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	void BerryBubble::Initialize( Vector2 pos )
	{
		getCore()->Init();
		getCore()->MyType = ObjectType_BERRY_BUBBLE;
		getCore()->DrawLayer = 9;

		getCore()->StartData.Position = getCore()->Data.Position = pos;

		Box->Initialize( getCore()->Data.Position, Radius );
		if ( !getCore()->BoxesOnly )
		{
			SetTexture();
		}
	}

	void BerryBubble::PhsxStep()
	{
		if ( RotateSpeed != 0 )
			Rotate( RotateSpeed );

		if ( Popped )
		{
			//Core.RemoveOnReset = true;

			getCore()->Data.Velocity.Y -= .7f*Gravity;
			getCore()->Data.Integrate();

			Bubble->setAlpha( Bubble->getAlpha() - .0375f );
			Bubble->setSize( Bubble->getSize() + Vector2(3.5f) );

			if ( getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - 500 )
			{
				//CollectSelf();
				return;
			}
		}
		else
		{
			getCore()->Data.Position = getCore()->StartData.Position;
			getCore()->Data.Position += Vector2(0, 9.65f * static_cast<float>(sin(.075f * (getCore()->MyLevel->CurPhsxStep) + getCore()->AddedTimeStamp)));
		}
	}

	void BerryBubble::Draw()
	{
		if ( getCore()->MyLevel == 0 )
			return;

		int DrawRange = 360;
		if ( getCore()->Data.Position.X > getCore()->MyLevel->getMainCamera()->TR.X + DrawRange || getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + DrawRange )
			return;
		if ( getCore()->Data.Position.X < getCore()->MyLevel->getMainCamera()->BL.X - DrawRange || getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - DrawRange )
			return;

		if ( Tools::DrawGraphics && !getCore()->BoxesOnly )
		{
			MyPile->setPos( getCore()->Data.Position );
			MyPile->Draw();
			//MyQuad.Pos = Core.Data.Position;
			//MyQuad.Draw();
		}

		if ( Tools::DrawBoxes )
			Box->Draw( Color( 50, 50, 255, 220 ) );
	}

	void BerryBubble::Move( Vector2 shift )
	{
		getCore()->Data.Position += shift;
		getCore()->StartData.Position += shift;

		Box->Move( shift );
	}

	void BerryBubble::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;
		Popped = false;

		getCore()->Data.Position = getCore()->StartData.Position;
		getCore()->Data.Velocity = Vector2::Zero;

		SetTexture();
	}

	void BerryBubble::Interact( const std::shared_ptr<Bob> &bob )
	{
		if ( Popped )
			return;

		bool hold = Box->BoxOverlap( bob->Box2 );
		if ( hold )
		{
			if ( getCore()->MyLevel->PlayMode == 0 )
			{
				bob->getMyStats()->Berries++;
				Die();

				bob->PopModifier++;
				Tools::Pop( bob->PopModifier );
			}

			if ( bob->Box->BL.Y > Box->getCenter().Y - 60 )
			{
				// The player landed on something
				int HoldPopModifier = bob->PopModifier;
				bob->MyPhsx->ObjectLandedOn = this;
				bob->MyPhsx->LandOnSomething( true, this );
				bob->MyPhsx->MaxJumpAccelMultiple = 1 + .8f * bob->MyPhsx->BlobMod;
				bob->getCore()->Data.Velocity.Y = 9.5f * bob->MyPhsx->BlobMod;
				bob->PopModifier = HoldPopModifier;
			}
		}
	}

	void BerryBubble::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<BerryBubble> BerryBubbleA = dynamic_cast<BerryBubble*>( A );

		Initialize( BerryBubbleA->getCore()->Data.Position );
	}

	void BerryBubble::InitializeInstanceFields()
	{
		RotateSpeed = 0;
		Radius = 180;
		PoppedRadius = 189;
		Gravity = 2.9f;
		Popped = false;
		AllowJumpOffOf = true;
	}
}
