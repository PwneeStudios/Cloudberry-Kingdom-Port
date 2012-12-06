#include <global_header.h>

namespace CloudberryKingdom
{

	Coin::CoinTileInfo::CoinTileInfo()
	{
		InitializeInstanceFields();
		DieTemplate = std::make_shared<Particle>();
		DieTemplate->MyQuad.Init();
		DieTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		DieTemplate->MyQuad.setMyTexture( Tools::TextureWad->FindByName( _T( "Coin" ) ) );

		DieTemplate->SetSize( 45 );
		DieTemplate->SizeSpeed = Vector2( 10, 10 );
		DieTemplate->AngleSpeed = .013f;
		DieTemplate->Life = 20;
		DieTemplate->MyColor = Vector4( 1, 1, 1,.75f );
		DieTemplate->ColorVel = Vector4( 0, 0, 0, -.065f );
	}

	void Coin::CoinTileInfo::InitializeInstanceFields()
	{
		Sprite = std::make_shared<SpriteInfo>( TextureOrAnim::Get( _T( "CoinShimmer" ) ), Vector2( 105.f, -1.f ) );
		BoxSize = Vector2( 52.5f, 65 );
		Color = bColor( 255, 255, 255, 255 );
		ShowEffect = true;
		ShowText = true;
		ShowCoin = true;
		MySound = Tools::NewSound( _T( "Coin" ),.75f );
	}

	void Coin::MakeNew()
	{
		getCore()->Init();

		MyValue = 1;
		MyScoreValue = 50;

		getCore()->MyType = ObjectType_COIN;
		getCore()->DrawLayer = 5;

		Box->Initialize( Vector2(), Vector2(1) );
	}

	void Coin::Release()
	{
		ObjectBase::Release();

		if ( MyQuad != 0 )
			MyQuad->Release();
			MyQuad.reset();
	}

	Coin::Coin( bool BoxesOnly )
	{
		InitializeInstanceFields();
		Box = std::make_shared<AABox>();

		if ( !BoxesOnly )
			MyQuad = std::make_shared<QuadClass>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	Vector2 Coin::PosOfLastCoinGrabbed = Vector2();

	void Coin::Die()
	{
		if ( getCore()->MyLevel->PlayMode != 0 )
			return;

		PosOfLastCoinGrabbed = getPos();

		getCore()->Active = false;

		getInfo()->Coins->MySound->Play(.65f,.1f, 0);

		// Effect
		if ( getInfo()->Coins->ShowEffect )
		{
			for ( int j = 0; j < 3; j++ )
			{
				std::shared_ptr<CloudberryKingdom::Particle> p = getCore()->MyLevel->MainEmitter->GetNewParticle(getInfo()->Coins->DieTemplate);
				p->Data.Position = getCore()->Data.Position + getMyLevel()->getRnd()->RndDir(35);
				p->MyQuad.setMyTexture( Tools::TextureWad->FindByName( _T( "Pop" ) ) );
			}
		}

		// Text float
		if ( getInfo()->Coins->ShowText )
		{
			int val = CalcScoreValue();
			std::shared_ptr<TextFloat> text = std::make_shared<TextFloat>( _T( "+" ) + StringConverterHelper::toString( val ), getCore()->Data.Position + Vector2(21, 22.5f) );
			text->getCore()->DrawLayer = 8;
			getCore()->MyLevel->MyGame->AddGameObject(text);
		}
	}

	const std::shared_ptr<GameData> &Coin::getMyGame() const
	{
		return getCore()->MyLevel->MyGame;
	}

	int Coin::CalcScoreValue()
	{
		return static_cast<int>( MyScoreValue * getMyGame()->CoinScoreMultiplier * getMyGame()->ScoreMultiplier );
	}

	void Coin::SetType( CoinType type )
	{
		MyType = type;

		Box->Initialize( getCore()->Data.Position, getInfo()->Coins->BoxSize );

		if ( !getCore()->BoxesOnly )
		switch ( MyType )
		{
			case CoinType_BLUE:
				AlwaysActive = false;
				MyQuad->Set( getInfo()->Coins->Sprite );
				break;
			default:
				break;
			//case CoinType.Red:
			//    AlwaysActive = true;
			//    MyQuad.MyTexture = Info.Coins.Red; break;
		}
	}

	Vector2 Coin::GetPos()
	{
		double t = 2 * M_PI * ( getCore()->GetPhsxStep() + Offset ) / static_cast<float>(Period);
		return Vector2( static_cast<float>( cos( t ) ) ) * Radii + getCore()->StartData.Position;
	}

	void Coin::PhsxStep()
	{
		if ( !getCore()->Active )
			return;

		if ( !AlwaysActive )
		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, 200) )
		{
			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

		//MyQuad.Quad.Playing = true;

		if ( MyType == CoinType_RED )
			getCore()->Data.Position = GetPos();
		else
			getCore()->Data.Position = getCore()->StartData.Position;
		getCore()->Data.Position += Vector2(0, 4.65f * static_cast<float>(sin(.075f * (getCore()->MyLevel->CurPhsxStep) + getCore()->AddedTimeStamp)));

		Box->SetTarget( getCore()->Data.Position, Box->Current->Size );

		if ( getCore()->WakeUpRequirements )
		{
			Box->SwapToCurrent();
			getCore()->WakeUpRequirements = false;
		}
	}

	void Coin::PhsxStep2()
	{
		if ( !getCore()->Active )
			return;
		if ( getCore()->SkippedPhsx )
			return;

		Box->SwapToCurrent();
	}

	void Coin::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;

		setPos( getCore()->StartData.Position );
	}

	void Coin::Move( Vector2 shift )
	{
		getCore()->StartData.Position += shift;
		setPos( getPos() + shift );

		Box->Move( shift );
	}

	void Coin::Interact( const std::shared_ptr<Bob> &bob )
	{
		if ( !getCore()->Active )
			return;
		if ( getCore()->MyLevel->SuppressCheckpoints && !getCore()->MyLevel->ShowCoinsInReplay )
			return;

		bool Col = Phsx::BoxBoxOverlap( bob->Box2, Box );
		if ( Col )
		{
			Die();

			if ( getCore()->MyLevel->PlayMode == 0 && !getCore()->MyLevel->Watching )
			{
				getCore()->setInteractingBob(bob);

				std::shared_ptr<GameData> game = getCore()->MyLevel->MyGame;

				// Add the value to the player's stats
				int CurScoreValue = CalcScoreValue();
				if ( game->TakeOnce || game->AlwaysGiveCoinScore )
				{
					bob->getMyStats()->Score += CurScoreValue;
					bob->getMyStats()->Coins += MyValue;
				}
				else
				{
					bob->getMyTempStats()->Score += CurScoreValue;
					bob->getMyTempStats()->Coins += MyValue;
				}

				// Fire the games OnCoinGrab event
				game->CoinGrabEvent( shared_from_this() );

				// Remove the coin permanently if it can only be grabbed once
				if ( game->TakeOnce )
					getCore()->getRecycle()->CollectObject( shared_from_this() );
			}
		}
	}

Vector2 Coin::DrawGrace = Vector2( 50, 50 );

	void Coin::Draw()
	{
		if ( !getCore()->Active )
			return;
		if ( getCore()->MyLevel->SuppressCheckpoints && !getCore()->MyLevel->ShowCoinsInReplay )
			return;

		if ( Box->Current->BL.X > getCore()->MyLevel->getMainCamera()->TR.X + DrawGrace.X || Box->Current->BL.Y > getCore()->MyLevel->getMainCamera()->TR.Y + DrawGrace.Y )
			return;
		if ( Box->Current->TR.X < getCore()->MyLevel->getMainCamera()->BL.X - DrawGrace.X || Box->Current->TR.Y < getCore()->MyLevel->getMainCamera()->BL.Y - DrawGrace.Y )
			return;

		if ( Tools::DrawGraphics && getInfo()->Coins->ShowCoin && !getCore()->BoxesOnly )
		{
			MyQuad->setPos( getPos() );
			MyQuad->Draw();
		}
		if ( Tools::DrawBoxes )
			Box->Draw( Tools::QDrawer, Color::Bisque, 10 );
	}

	void Coin::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<Coin> CoinA = std::dynamic_pointer_cast<Coin>( A );

		Box->SetTarget( CoinA->Box->Target->Center, CoinA->Box->Target->Size );
		Box->SetCurrent( CoinA->Box->Current->Center, CoinA->Box->Current->Size );

		MyValue = CoinA->MyValue;
		MyScoreValue = CoinA->MyScoreValue;

		SetType( CoinA->MyType );

		Period = CoinA->Period;
		Offset = CoinA->Offset;
		Radii = CoinA->Radii;
	}

	void Coin::InitializeInstanceFields()
	{
		AlwaysActive = false;
		Offset = 0;
		Period = 95;
		Radii = Vector2( 0, 120 );
	}
}
