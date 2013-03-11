#include <global_header.h>

#include <Hacks/String.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	GUI_NextLife::OnCoinGrabProxy::OnCoinGrabProxy( const boost::shared_ptr<GUI_NextLife> &guiNl )
	{
		this->guiNl = guiNl;
	}

	void GUI_NextLife::OnCoinGrabProxy::Apply( const boost::shared_ptr<ObjectBase> &obj )
	{
		guiNl->OnCoinGrab( obj );
	}

	std::vector<std::wstring> GUI_NextLife::GetViewables()
	{
		return std::vector<std::wstring>();
	}

	const int &GUI_NextLife::getCoins() const
	{
		return _Coins;
	}

	void GUI_NextLife::setCoins( const int &value )
	{
		_Coins = value;
		if ( _Coins >= Max )
		{
			GiveLife();
		}

		UpdateCoinsText();
	}

	void GUI_NextLife::GiveLife()
	{
		// Reset coin counter
		_Coins = 0;

		// Give extra life
		GUI_Lives_Renamed->setNumLives( GUI_Lives_Renamed->getNumLives() + 1 );
		GUI_Lives_Renamed->Bring( true );

		//MyGame.AddGameObject(new SuperCheer(2));

		// Remove last coin score text
		MyGame->RemoveLastCoinText();

		// Add text
		boost::shared_ptr<TextFloat> text = boost::make_shared<TextFloat>( Localization::Words_ExtraLife, Coin::PosOfLastCoinGrabbed + Vector2( 21, 22.5f ) );
		text->MyText->setScale( text->MyText->getScale() * 1.33f );
		text->getCore()->DrawLayer = 8;
			//text->MyText->MyFloatColor = bColor(0, 195, 17).ToVector4();
			//text->MyText->OutlineColor = bColor(0, 80, 8).ToVector4();
			text->MyText->MyFloatColor = bColor(84, 232, 79).ToVector4();
            text->MyText->OutlineColor = bColor(0, 0, 0).ToVector4();
			CkColorHelper::_x_x_HappyBlueColor( text->MyText );
		getCore()->MyLevel->MyGame->AddGameObject(text);

        ParticleEffects::CoinDie_ExtraLife( MyGame->MyLevel, Coin::PosOfLastCoinGrabbed );

        boost::shared_ptr<EzSound> sound = Tools::SoundWad->FindByName( L"ExtraLifeSound" );
        if ( sound != 0 ) sound->Play();
	}

	std::wstring GUI_NextLife::ToString()
	{
		//string str = string.Format("x{0}/{1}", Coins, Max);
		//std::wstring str = Format( _T( "%d/%d" ), getCoins(), Max );
		std::wstring str = ::ToString( Max - getCoins() );

		return str;
	}

	void GUI_NextLife::OnCoinGrab( const boost::shared_ptr<ObjectBase> &obj )
	{
		setCoins( getCoins() + 1 );
	}

	void GUI_NextLife::UpdateCoinsText()
	{
		CoinsText->SubstituteText( ToString() );
	}

	GUI_NextLife::GUI_NextLife( int CoinsToNextLife, const boost::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed )
	{
		// Object is carried over through multiple levels, so prevent it from being released.
		InitializeInstanceFields();
		PreventRelease = true;

		this->GUI_Lives_Renamed = GUI_Lives_Renamed;

		Max = CoinsToNextLife;

		MyPile->FancyPos->UpdateWithGame = true;

		boost::shared_ptr<EzFont> font;
		std::wstring coin;
		float scale;
		Color c, o;

		if ( false )
		{
			font = Resources::Font_Grobold42;
			coin = std::wstring( L"CoinBlue" );
			scale = .625f;
			c = Color::White;
			o = Color::Black;
		}
		else
		{
			font = Resources::Font_Grobold42;
			coin = std::wstring( L"coin_blue" );
			scale = .55f;
			c = bColor( 228, 0, 69 );
			o = Color::White;
		}

		CoinsText = boost::make_shared<EzText>( ToString(), font, 450.f, false, true );
		CoinsText->Name = std::wstring( L"coin" );
		CoinsText->setScale( scale );
		CoinsText->MyFloatColor = c.ToVector4();
		CoinsText->OutlineColor = o.ToVector4();

		boost::shared_ptr<QuadClass> Coin_Renamed = boost::make_shared<QuadClass>();
		Coin_Renamed->Name = std::wstring( L"coin" );
		Coin_Renamed->SetToDefault();
		Coin_Renamed->setTextureName( coin );
		Coin_Renamed->Scale( 61.5f );
		Coin_Renamed->ScaleYToMatchRatio();
		Coin_Renamed->PointxAxisTo( 20 / CoreMath::c );

		MyPile->Add( Coin_Renamed );
		MyPile->Add( CoinsText );

		MyPile->setPos( Vector2( 1002.133f, 670.5443f ) );

		SetPos();
	}

	void GUI_NextLife::SetPos()
	{
			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"coin" ); if (_t != 0 ) { _t->setPos( Vector2( 189.7776f, 111.7778f ) ); _t->setScale( 0.55f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"coin" ); if (_q != 0 ) { _q->setPos( Vector2( 140.7331f, 117.8001f ) ); _q->setSize( Vector2( 100.f, 100.f ) ); }

			MyPile->setPos( Vector2( 1232.689f, 758.2109f ) );

			// Extra squeeze
			Vector2 squeeze = Vector2(-15, -15 ) * CloudberryKingdomGame::GuiSqueeze;

			MyPile->setPos( MyPile->getPos() + squeeze );
	}

	void GUI_NextLife::OnAdd()
	{
		GameObject::OnAdd();

		MyGame->OnCoinGrab->Add( boost::make_shared<OnCoinGrabProxy>( boost::static_pointer_cast<GUI_NextLife>( shared_from_this() ) ) );
	}

	void GUI_NextLife::ReleaseBody()
	{
		/*if (MyGame != null)
		    MyGame.OnCoinGrab -= OnCoinGrab;*/

		GameObject::ReleaseBody();
	}

	void GUI_NextLife::MyDraw()
	{
		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		MyPile->Draw();
	}

	void GUI_NextLife::MyPhsxStep()
	{
		boost::shared_ptr<Level> level = getCore()->MyLevel;
		MyPile->FancyPos->SetCenter( level->getMainCamera(), true );
		MyPile->FancyPos->Update();
	}

	void GUI_NextLife::InitializeInstanceFields()
	{
		MyPile = boost::make_shared<DrawPile>();
		Max = 25;
		_Coins = 0;
	}
}
