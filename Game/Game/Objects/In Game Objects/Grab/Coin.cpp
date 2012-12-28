#include <global_header.h>

namespace CloudberryKingdom
{

	Coin::CoinTileInfo::CoinTileInfo()
	{
		InitializeInstanceFields();
	}

	void Coin::CoinTileInfo::InitializeInstanceFields()
	{
		Sprite = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( std::wstring( L"CoinShimmer" ) ), Vector2( 105.f, -1.f ) );
		BoxSize = Vector2( 52.5f, 65 );
		Color = bColor( 255, 255, 255, 255 );
		ShowEffect = true;
		ShowText = true;
		ShowCoin = true;
		MySound = Tools::NewSound( std::wstring( L"Coin" ),.75f );
	}

	void Coin::MakeNew()
	{
		getCore()->Init();

		MyValue = 1;
		MyScoreValue = 50;

		getCore()->MyType = ObjectType_COIN;
		getCore()->DrawLayer = 5;

		Box->Initialize( Vector2(), Vector2(1) );

        if ( MyQuad != 0 )
        {
            MyQuad->Quad_Renamed.t = 0;
            MyQuad->Quad_Renamed.Playing = false;
            MyQuad->Quad_Renamed.Loop = false;
        }
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
		Box = boost::make_shared<AABox>();

		if ( !BoxesOnly )
			MyQuad = boost::make_shared<QuadClass>();

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

		getInfo()->Coins->MySound->Play( .45f, .1f, 0.f );

		// Effect
		if ( getInfo()->Coins->ShowEffect )
		{
            ParticleEffects::CoinDie_New( getMyLevel(), getPos() );
            ParticleEffects::CoinDie_Old( getMyLevel(), getPos() );
		}

		// Text float
		if ( getInfo()->Coins->ShowText )
		{
			int val = CalcScoreValue();
			boost::shared_ptr<TextFloat> text = boost::make_shared<TextFloat>( std::wstring( L"+" ) + StringConverterHelper::toString( val ), getCore()->Data.Position + Vector2(21, 22.5f) );
			text->getCore()->DrawLayer = 8;
			getCore()->MyLevel->MyGame->AddGameObject(text);
		}
	}

	const boost::shared_ptr<GameData> &Coin::getMyGame() const
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
                MyQuad->Quad_Renamed.Playing = false;
                MyQuad->Quad_Renamed.Loop = false;
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
            if (!getMyLevel()->BoxesOnly)
            {
                MyQuad->Quad_Renamed.Playing = false;
                MyQuad->Quad_Renamed.Loop = false;
                MyQuad->Quad_Renamed.t = 0;
            }

			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

        // Shimmer
        if ( !getMyLevel()->BoxesOnly )
        {
            MyQuad->Quad_Renamed.Playing = true;
            MyQuad->Quad_Renamed.Loop = false;
            MyQuad->Quad_Renamed.t = static_cast<float>( getMyLevel()->CurPhsxStep % 110 );
        }

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

	void Coin::Interact( const boost::shared_ptr<Bob> &bob )
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

				boost::shared_ptr<GameData> game = getCore()->MyLevel->MyGame;

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

	void Coin::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<Coin> CoinA = boost::dynamic_pointer_cast<Coin>( A );

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
