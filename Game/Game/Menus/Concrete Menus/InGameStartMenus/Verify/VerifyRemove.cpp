#include <global_header.h>

namespace CloudberryKingdom
{

	VerifyRemoveMenu::VerifyRemoveYesLambda::VerifyRemoveYesLambda( const boost::shared_ptr<VerifyRemoveMenu> &vrm )
	{
		this->vrm = vrm;
	}

	void VerifyRemoveMenu::VerifyRemoveYesLambda::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		if ( PlayerManager::GetNumPlayers() > 1 )
		{
			if ( vrm->getControl() >= 0 )
				Tools::CurGameData->RemovePlayer( vrm->getControl() );
		}

		vrm->ReturnToCaller();
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

		// Make the menu
		boost::shared_ptr<MenuItem> item;

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::Words_REMOVE_PLAYER_QUESTION, ItemFont, true );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );

		std::wstring PlayerName = PlayerManager::Get( getControl() )->GetName();
		boost::shared_ptr<EzText> PlayerText = boost::make_shared<EzText>( PlayerName, ItemFont, true );
		SetHeaderProperties( PlayerText );
		MyPile->Add( PlayerText );

		// Yes
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_YES, ItemFont ) );
		item->setGo( boost::make_shared<VerifyRemoveYesLambda>( boost::static_pointer_cast<VerifyRemoveMenu>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		// No
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_NO, ItemFont ) );
		item->setGo( boost::make_shared<MenuReturnToCallerLambda>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}
}
