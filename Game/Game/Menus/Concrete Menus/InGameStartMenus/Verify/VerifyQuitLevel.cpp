#include <global_header.h>

namespace CloudberryKingdom
{

	VerifyQuitLevelMenu::VerifyQuitOkLambda::VerifyQuitOkLambda()
	{
	}

	void VerifyQuitLevelMenu::VerifyQuitOkLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		Tools::CurrentAftermath = boost::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = false;
		Tools::CurrentAftermath->EarlyExit = true;

		Tools::CurGameData->EndGame->Apply( false );
	}

	VerifyQuitLevelMenu::VerifyQuitLevelMenu( bool CallBaseConstructor ) : VerifyBaseMenu( CallBaseConstructor ) { }
	boost::shared_ptr<VerifyQuitLevelMenu> VerifyQuitLevelMenu::VerifyQuitLevelMenu_Construct( bool CallBaseConstructor )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( CallBaseConstructor );

		EnableBounce();

		return boost::static_pointer_cast<VerifyQuitLevelMenu>( shared_from_this() );
	}

	VerifyQuitLevelMenu::VerifyQuitLevelMenu( int Control ) : VerifyBaseMenu( Control, true ) { }
	boost::shared_ptr<VerifyQuitLevelMenu> VerifyQuitLevelMenu::VerifyQuitLevelMenu_Construct( int Control )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( Control, true );

		//EnableBounce();

		return boost::static_pointer_cast<VerifyQuitLevelMenu>( shared_from_this() );
	}

	void VerifyQuitLevelMenu::Init()
	{
		VerifyBaseMenu::Init();

		// Make the menu
		boost::shared_ptr<MenuItem> item;

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::Words_ExitLevelQuestion, ItemFont, true );
		SetHeaderProperties( HeaderText );
		HeaderText->Name = std::wstring( L"Header" );
		MyPile->Add( HeaderText );

		// Ok
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Yes, ItemFont, true ) ) );
		item->setGo( boost::make_shared<VerifyQuitOkLambda>() );
		item->Name = std::wstring( L"Yes" );
		AddItem( item );

		// No
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_No, ItemFont, true ) ) );
		item->setGo( Cast::ToItem( boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<CkBaseMenu>( shared_from_this() ) ) ) );
		item->Name = std::wstring( L"No" );
		AddItem( item );

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		SetPos();
	}

	void VerifyQuitLevelMenu::SetPos()
	{
        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Yes" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 380.4445f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"No" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 94.33334f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

        MyMenu->setPos( Vector2( 0.f, -302.7777f ) );

        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2( 0.f, 777.4443f ) ); _t->setScale( 0.96f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 316.6668f ) ); _q->setSize( Vector2( 1281.083f, 729.4391f ) ); }

        MyPile->setPos( Vector2( 0.f, -319.4444f ) );
	}
}
