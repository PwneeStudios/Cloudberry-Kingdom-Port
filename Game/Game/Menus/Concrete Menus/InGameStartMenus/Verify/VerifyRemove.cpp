#include <global_header.h>

namespace CloudberryKingdom
{

	VerifyRemoveMenu::VerifyRemoveYesLambda::VerifyRemoveYesLambda( const std::shared_ptr<VerifyRemoveMenu> &vrm )
	{
		this->vrm = vrm;
	}

	void VerifyRemoveMenu::VerifyRemoveYesLambda::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		if ( PlayerManager::GetNumPlayers() > 1 )
		{
			if ( vrm->getControl() >= 0 )
				Tools::CurGameData->RemovePlayer( vrm->getControl() );
		}

		vrm->ReturnToCaller();
	}

	VerifyRemoveMenu::VerifyRemoveMenu( int Control ) : VerifyBaseMenu( Control )
	{
	}

	void VerifyRemoveMenu::Init()
	{
		VerifyBaseMenu::Init();

		// Make the menu
		std::shared_ptr<MenuItem> item;

		// Header
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Localization::Words_REMOVE_PLAYER_QUESTION, ItemFont, true );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );

		std::wstring PlayerName = PlayerManager::Get( getControl() )->GetName();
		std::shared_ptr<EzText> PlayerText = std::make_shared<EzText>( PlayerName, ItemFont, true );
		SetHeaderProperties( PlayerText );
		MyPile->Add( PlayerText );

		// Yes
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_YES, ItemFont ) );
		item->setGo( std::make_shared<VerifyRemoveYesLambda>( this ) );
		AddItem( item );
		item->SelectSound.reset();

		// No
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_NO, ItemFont ) );
		item->setGo( std::make_shared<MenuReturnToCallerLambda>( this ) );
		AddItem( item );
		item->SelectSound.reset();

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}
}
