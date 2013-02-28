#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/Compare.h>
#include <Hacks/String.h>

#include "ShopMenu.h"
#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	SmallErrorMenu::SmallErrorMenu( Localization::Words Word )
		: VerifyBaseMenu( false )
	{
		this->Word = Word;

		EnableBounce();

		this->setControl( -1 );

        setPauseLevel( true );
        setPauseGame( true);

		Constructor();

		MyMenu->OnB.reset();

		getCore()->DrawLayer++;
	}

	void SmallErrorMenu::MakeBackdrop()
	{
		Backdrop = boost::make_shared<QuadClass>( 0, true, true );
		Backdrop->setTextureName( L"WidePlaque");
		Backdrop->setSize( Vector2(1750.0f, 284.8255f) );
		Backdrop->setPos( Vector2(-11.9043f, 59.52365f));
		Backdrop->setDegrees( 0);

		MyPile->Add( Backdrop, L"ArcadeBox" );
		MyPile->setPos( Vector2(0, -800) );

		//VerifyBaseMenu::MakeBackdrop();
	}

	void SmallErrorMenu::Init()
	{
		VerifyBaseMenu::Init();

		// Make the menu
		MenuItem item;

		boost::shared_ptr<EzText> Description = boost::make_shared<EzText>( std::wstring( L"Reconnect controller to continue!" ), Resources::Font_Grobold42_2, 1800.0f, true, true, 0.575f );
		Description->setPos( Vector2(0, 100));
		Description->setScale( Description->getScale() * .6f );
		MyPile->Add( Description, L"Description" );

		SetPos();
	}

	void SmallErrorMenu::MyPhsxStep()
	{
		VerifyBaseMenu::MyPhsxStep();
	}

	void SmallErrorMenu::SetPos()
	{
		MyMenu->setPos( Vector2(-1125.001f, -319.4444f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( L"Description" ); if (_t != 0 ) { _t->setPos( Vector2( 19.44458f, 36.11111f ) ); _t->setScale( 0.6f ); }

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( L"ArcadeBox" ); if (_q != 0 ) { _q->setPos( Vector2( 10.31873f, -11.11108f ) ); _q->setSize( Vector2( 1123.342f, 176.4081f ) ); }

		MyPile->setPos( Vector2( 72.22217f, 36.11115f ) );
	}
	
    UpSellMenu::UpSellMenu( Localization::Words Word, int Control )
		: VerifyBaseMenu( false )
    {
	}

	boost::shared_ptr<UpSellMenu> UpSellMenu::UpSellMenu_Construct( Localization::Words Word, int Control )
	{
		this->Word = Word;

		EnableBounce();

        this->setControl( Control );

        Constructor();

		return boost::static_pointer_cast<UpSellMenu>( shared_from_this() );
    }

	UpSellMenu::YesProxy::YesProxy( const boost::shared_ptr<UpSellMenu> &sm )
	{
		this->sm = sm;
	}

    void UpSellMenu::YesProxy::Apply( const boost::shared_ptr<MenuItem> &item )
    {
        CloudberryKingdomGame::ShowMarketplace = true;
    }

	UpSellMenu::NoProxy::NoProxy( const boost::shared_ptr<UpSellMenu> &sm )
	{
		this->sm = sm;
	}

    void UpSellMenu::NoProxy::Apply( const boost::shared_ptr<MenuItem> &item )
    {
		if ( sm->Word == Localization::Words_UpSell_Exit )
		{
			Tools::TheGame->Exit();
		}
		else if ( sm->Word == Localization::Words_FreePlay )
		{
			sm->UseBounce = false;
			sm->SlideOutTo = PresetPos_RIGHT;
			sm->SlideOutLength = 17;
		}

        sm->ReturnToCaller();
    }

    void UpSellMenu::MakeBackdrop()
    {
		Black = boost::make_shared<QuadClass>( std::wstring( L"White" ) );
		Black->setAlpha( 0 );
		Black->FullScreen( Tools::getCurCamera() );
		Black->Quad_Renamed.SetColor( ColorHelper::Gray( .2f ) );
		MyPile->Add( Black, L"Black" );

		VerifyBaseMenu::MakeBackdrop();
    }

    void UpSellMenu::Init()
    {
        VerifyBaseMenu::Init();

        // Make the menu
        boost::shared_ptr<MenuItem> item;

        // Header
        boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Word, ItemFont, 1500.0, true, false, .7f );
        HeaderText->setScale( HeaderText->getScale() * .85f );
        SetHeaderProperties( HeaderText );
        MyPile->Add( HeaderText, L"Header" );
        HeaderText->setPos( HeaderPos + Vector2(-200, 200) );

		// Berry
		boost::shared_ptr<QuadClass> Berry = boost::make_shared<QuadClass>( 0, true, false );
		Berry->setTextureName( L"cb_crying" );
		MyPile->Add( Berry, L"Berry" );

        // Yes
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Yes, ItemFont, true ) ) );
        item->setGo( boost::make_shared<UpSellMenu::YesProxy>( boost::static_pointer_cast<UpSellMenu>( shared_from_this() ) ) );
		item->Name = L"Yes";
        AddItem(item);
		StartMenu::SetItemProperties_Red(item);
        item->SelectSound = 0;

        // No
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_No, ItemFont, true ) ) );
        item->setGo( boost::make_shared<UpSellMenu::NoProxy>( boost::static_pointer_cast<UpSellMenu>( shared_from_this() ) ) );
		item->Name = L"No";
        AddItem( item );
		StartMenu::SetItemProperties_Red( item );
        item->SelectSound = 0;

        MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

        // Select the first item in the menu to start
        MyMenu->SelectItem( 0 );

		SetPos();
    }

	void UpSellMenu::MyPhsxStep()
	{
		VerifyBaseMenu::MyPhsxStep();

		if ( MyMenu->CurIndex == 1 )
			MyPile->FindQuad( L"Berry" )->setTextureName( std::wstring( L"cb_crying" ) );
		else
			MyPile->FindQuad( L"Berry" )->setTextureName( std::wstring( L"cb_enthusiastic" ) );

		if ( Black != 0 )
		{
			if (Black->getAlpha() < .44f)
			{
				Black->setAlpha( Black->getAlpha() + .01f );
			}
			else
			{
				Black->setAlpha( .44f);
			}
		}
	}

	void UpSellMenu::SetPos()
	{
		if ( Word == Localization::Words::Words_UpSell_FreePlay )
		{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Yes" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1091.667f, 230.4445f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"No" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1091.667f, -47.33334f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-1319.446f, -333.3333f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2( 1169.444f, 1119.111f ) ); _t->setScale( 0.6118331f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Black" ); if (_q != 0 ) { _q->setPos( Vector2( 1127.779f, 319.4446f ) ); _q->setSize( Vector2( 1886.415f, 1886.415f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 1178.473f, 250.0002f ) ); _q->setSize( Vector2( 1500.f, 2454.545f ) ); }
			_q = MyPile->FindQuad( L"Berry" ); if (_q != 0 ) { _q->setPos( Vector2( 1455.556f, -11.11105f ) ); _q->setSize( Vector2( 266.1786f, 358.9999f ) ); }

			MyPile->setPos( Vector2(-1125.001f, -319.4444f ) );
		}
		else if ( Word == Localization::Words::Words_UpSell_Exit )
		{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Yes" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1091.667f, 230.4445f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"No" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1091.667f, -47.33334f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-1319.446f, -333.3333f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2( 1194.444f, 991.3332f ) ); _t->setScale( 0.6118331f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Black" ); if (_q != 0 ) { _q->setPos( Vector2( 1127.779f, 319.4446f ) ); _q->setSize( Vector2( 1886.415f, 1886.415f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 1178.473f, 250.0002f ) ); _q->setSize( Vector2( 1500.f, 2454.545f ) ); }
			_q = MyPile->FindQuad( L"Berry" ); if (_q != 0 ) { _q->setPos( Vector2( 1455.556f, -11.11105f ) ); _q->setSize( Vector2( 266.1786f, 358.9999f ) ); }

			MyPile->setPos( Vector2(-1125.001f, -319.4444f ) );
		}
		else
		{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Yes" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1091.667f, 230.4445f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"No" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1091.667f, -47.33334f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-1319.446f, -333.3333f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2( 1186.111f, 885.7778f ) ); _t->setScale( 0.6118331f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Black" ); if (_q != 0 ) { _q->setPos( Vector2( 1127.779f, 319.4446f ) ); _q->setSize( Vector2( 1886.415f, 1886.415f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 1178.473f, 250.0002f ) ); _q->setSize( Vector2( 1500.f, 2454.545f ) ); }
			_q = MyPile->FindQuad( L"Berry" ); if (_q != 0 ) { _q->setPos( Vector2( 1455.556f, -11.11105f ) ); _q->setSize( Vector2( 266.1786f, 358.9999f ) ); }

			MyPile->setPos( Vector2(-1125.001f, -319.4444f ) );
		}
	}

}
