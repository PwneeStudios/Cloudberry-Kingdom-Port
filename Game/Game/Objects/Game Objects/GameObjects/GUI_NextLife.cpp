#include "GUI_NextLife.h"
#include "Game/Objects/ObjectBase.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_LivesLeft.h"
#include "Game/Localization.h"
#include "Game/Objects/Special/TextFloat.h"
#include "Game/Objects/In Game Objects/Grab/Coin.h"
#include "Core/Text/EzText.h"
#include "Core/Text/EzFont.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	GUI_NextLife::OnCoinGrabProxy::OnCoinGrabProxy( const std::shared_ptr<GUI_NextLife> &guiNl )
	{
		this->guiNl = guiNl;
	}

	void GUI_NextLife::OnCoinGrabProxy::Apply( const std::shared_ptr<ObjectBase> &obj )
	{
		guiNl->OnCoinGrab( obj );
	}

	std::vector<std::wstring> GUI_NextLife::GetViewables()
	{
		return std::vector<std::wstring*> ();
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

		//MyGame.AddGameObject(new SuperCheer(2));

		// Remove last coin score text
		MyGame->RemoveLastCoinText();

		// Add text
		std::shared_ptr<TextFloat> text = std::make_shared<TextFloat>( Localization::Words_EXTRA_LIFE, Coin::PosOfLastCoinGrabbed + Vector2( 21, 22.5f ) );
		text->MyText->setScale( text->MyText->getScale() * 1.33f );
		text->getCore()->DrawLayer = 8;
		text->MyText->MyFloatColor = ( Color( 0, 195, 17 ) ).ToVector4();
		text->MyText->OutlineColor = ( Color( 0, 80, 8 ) ).ToVector4();
		getCore()->MyLevel->MyGame->AddGameObject(text);
	}

	std::wstring GUI_NextLife::ToString()
	{
		//string str = string.Format("x{0}/{1}", Coins, Max);
		std::wstring str = std::wstring::Format( _T( "{0}/{1}" ), getCoins(), Max );

		return str;
	}

	void GUI_NextLife::OnCoinGrab( const std::shared_ptr<ObjectBase> &obj )
	{
		setCoins( getCoins() + 1 );
	}

	void GUI_NextLife::UpdateCoinsText()
	{
		CoinsText->SubstituteText( ToString() );
	}

	GUI_NextLife::GUI_NextLife( int CoinsToNextLife, const std::shared_ptr<GUI_LivesLeft> &GUI_Lives_Renamed )
	{
		// Object is carried over through multiple levels, so prevent it from being released.
		InitializeInstanceFields();
		PreventRelease = true;

		this->GUI_Lives_Renamed = GUI_Lives_Renamed;

		Max = CoinsToNextLife;

		MyPile->FancyPos->UpdateWithGame = true;

		std::shared_ptr<EzFont> font;
		std::wstring coin;
		float scale;
		Color c, o;

		if ( false )
		{
			font = Resources::Font_Grobold42;
			coin = _T( "CoinBlue" );
			scale = .625f;
			c = Color::White;
			o = Color::Black;
		}
		else
		{
			font = Resources::Font_Grobold42;
			coin = _T( "coin_blue" );
			scale = .55f;
			c = Color( 228, 0, 69 );
			o = Color::White;
		}

		CoinsText = std::make_shared<EzText>( ToString(), font, 450, false, true );
		CoinsText->Name = _T( "coin" );
		CoinsText->setScale( scale );
		CoinsText->MyFloatColor = c.ToVector4();
		CoinsText->OutlineColor = o.ToVector4();

//C# TO C++ CONVERTER NOTE: The variable Coin was renamed since it is named the same as a user-defined type:
		std::shared_ptr<QuadClass> Coin_Renamed = std::make_shared<QuadClass>();
		Coin_Renamed->Name = _T( "coin" );
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
		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "coin" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 189.7776f, 111.7778f ) );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "coin" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 140.7331f, 117.8001f ) );
			_q->ScaleYToMatchRatio( 100 );
		}

		setPos( Vector2( 1002.133f, 670.5443f ) );
	}

	void GUI_NextLife::OnAdd()
	{
		GameObject::OnAdd();

		MyGame->OnCoinGrab->Add( std::make_shared<OnCoinGrabProxy>( this ) );
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
		std::shared_ptr<Level> level = getCore()->MyLevel;
		MyPile->FancyPos->SetCenter( level->getMainCamera(), true );
		MyPile->FancyPos->Update();
	}

	void GUI_NextLife::InitializeInstanceFields()
	{
		MyPile = std::make_shared<DrawPile>();
		Max = 25;
		_Coins = 0;
	}
}
