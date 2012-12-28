#include <global_header.h>

namespace CloudberryKingdom
{

	VerifyRemoveMenu::VerifyRemoveYesLambda::VerifyRemoveYesLambda( const boost::shared_ptr<VerifyRemoveMenu> &vrm )
	{
		this->vrm = vrm;
	}

	void VerifyRemoveMenu::VerifyRemoveYesLambda::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		vrm->_Yes( _item );
	}

	VerifyRemoveMenu::VerifyRemoveMenu( int Control ) : VerifyBaseMenu( Control ) { }
	boost::shared_ptr<VerifyRemoveMenu> VerifyRemoveMenu::VerifyRemoveMenu_Construct( int Control )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( Control );

		return boost::static_pointer_cast<VerifyRemoveMenu>( shared_from_this() );
	}

	void VerifyRemoveMenu::Init()
	{
		VerifyBaseMenu::Init();

		VerifyRemoveMenu::YesChosen = false;

		// Make the menu
		boost::shared_ptr<MenuItem> item;

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::WordString( Localization::Words_REMOVE_PLAYER_QUESTION ) + L"?", ItemFont, false );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->Name = L"Header";
		HeaderText->setPos( HeaderPos );

		std::wstring PlayerName = PlayerManager::Get( getControl() )->GetName();
		boost::shared_ptr<EzText> PlayerText = boost::make_shared<EzText>( PlayerName, ItemFont, false );
		SetHeaderProperties( PlayerText );
        PlayerText->Name = L"PlayerText";
        PlayerManager::Get( getControl() )->SetNameText( PlayerText );
		MyPile->Add( PlayerText );

		// Yes
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_YES, ItemFont ) ) );
		item->setGo( boost::make_shared<VerifyRemoveYesLambda>( boost::static_pointer_cast<VerifyRemoveMenu>( shared_from_this() ) ) );
		item->Name = L"Yes";
		AddItem( item );
		item->SelectSound.reset();

		// No
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_NO, ItemFont ) ) );
		item->setGo( boost::make_shared<MenuReturnToCallerLambda>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
		item->Name = L"No";
		AddItem( item );
		item->SelectSound.reset();

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		SetPos();
	}

        void VerifyRemoveMenu::SetPos()
        {
            // Set Positions
            boost::shared_ptr<MenuItem> _item;
            _item = MyMenu->FindItemByName( L"Yes" ); if ( _item != 0 ) { _item->setSetPos( Vector2(800.f, 361.f) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }
            _item = MyMenu->FindItemByName( L"No" ); if ( _item != 0 ) { _item->setSetPos( Vector2(800.f, 61.f) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2(0.f, 0.f); }

            MyMenu->setPos( Vector2(-1027.779f, -408.3333f) );

            boost::shared_ptr<EzText> _t;
            _t = MyPile->FindEzText( L"Header" ); if ( _t != 0 ) { _t->setPos( Vector2(280.5555f, 560.778f) ); _t->setScale( 0.96f ); }
            _t = MyPile->FindEzText( L"PlayerText" ); if ( _t != 0 ) { _t->setPos( Vector2(283.333f, 872.2222f) ); _t->setScale( 0.96f ); }

            boost::shared_ptr<QuadClass> _q;
            _q = MyPile->FindQuad( L"Backdrop" ); if ( _q != 0 ) { _q->setPos( Vector2(1181.251f, 241.6668f) ); _q->setSize( Vector2(1287.75f, 890.8389f) ); }

            MyPile->setPos( Vector2(-1141.667f, -258.3334f) );
        }

        bool VerifyRemoveMenu::YesChosen = false;

        void VerifyRemoveMenu::_Yes( boost::shared_ptr<MenuItem> _item )
        {
            if ( PlayerManager::GetNumPlayers() > 1 )
            {
                if ( getControl() >= 0 )
                    Tools::CurGameData->RemovePlayer( getControl() );
            }

            VerifyRemoveMenu::YesChosen = true;

            ReturnToCaller();
        }
}
