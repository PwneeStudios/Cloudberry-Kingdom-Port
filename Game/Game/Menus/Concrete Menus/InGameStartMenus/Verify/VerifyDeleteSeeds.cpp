#include <global_header.h>

namespace CloudberryKingdom
{

	VerifyDeleteSeeds::VerifyDeleteYesGoLambda::VerifyDeleteYesGoLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds )
	{
		this->vds = vds;
	}

	void VerifyDeleteSeeds::VerifyDeleteYesGoLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		vds->DoSelect( true );
		vds->ReturnToCaller();
	}

	VerifyDeleteSeeds::VerifyDeleteOnXLambda::VerifyDeleteOnXLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds )
	{
		this->vds = vds;
	}

	bool VerifyDeleteSeeds::VerifyDeleteOnXLambda::Apply( const std::shared_ptr<Menu> &item )
	{
		vds->DoSelect( false );
		vds->ReturnToCaller();
		return true;
	}

	VerifyDeleteSeeds::VerifyDeleteNoGoLambda::VerifyDeleteNoGoLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds )
	{
		this->vds = vds;
	}

	void VerifyDeleteSeeds::VerifyDeleteNoGoLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		vds->DoSelect( false );
		vds->ReturnToCaller();
	}

	VerifyDeleteSeeds::VerifyDeleteSeeds( int Control, int NumSeeds ) : VerifyBaseMenu( false )
	{
		this->NumSeeds = NumSeeds;
		this->setControl( Control );

		Constructor();
	}

	void VerifyDeleteSeeds::Init()
	{
		VerifyBaseMenu::Init();

		// Make the menu
		std::shared_ptr<MenuItem> item;

		// Header
		std::wstring Text;
		if ( NumSeeds == 1 )
			Text = Format( Localization::WordString( Localization::Words_DELETE_SEEDS ), NumSeeds );
		else
			Text = Format( Localization::WordString( Localization::Words_DELETE_SEEDS_PLURAL ), NumSeeds );
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Text, ItemFont, _T( "Header" ) );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );


		// Yes
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_YES, ItemFont, _T( "Yes" ) ) );
		item->setGo( std::make_shared<VerifyDeleteYesGoLambda>( shared_from_this() ) );
		AddItem( item );
		item->SelectSound.reset();

		// No
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_NO, ItemFont, _T( "No" ) ) );
		item->setGo( std::make_shared<VerifyDeleteNoGoLambda>( shared_from_this() ) );
		AddItem( item );
		item->SelectSound.reset();

		MyMenu->OnX = MyMenu->OnB = std::make_shared<VerifyDeleteOnXLambda>( shared_from_this() );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}
}
