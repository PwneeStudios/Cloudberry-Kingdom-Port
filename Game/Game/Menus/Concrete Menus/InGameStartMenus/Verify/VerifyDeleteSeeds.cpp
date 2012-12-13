#include <global_header.h>

#include <Hacks/String.h>

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

	VerifyDeleteSeeds::VerifyDeleteSeeds( int Control, int NumSeeds ) : VerifyBaseMenu( false ) { }
	std::shared_ptr<VerifyDeleteSeeds> VerifyDeleteSeeds::VerifyDeleteSeeds_Construct( int Control, int NumSeeds )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( false );

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
			Text = Format( Localization::WordString( Localization::Words_DELETE_SEEDS ).c_str(), NumSeeds );
		else
			Text = Format( Localization::WordString( Localization::Words_DELETE_SEEDS_PLURAL ).c_str(), NumSeeds );
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Text, ItemFont, static_cast<std::wstring>( _T( "Header" ) ) );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );


		// Yes
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_YES, ItemFont, static_cast<std::wstring>( _T( "Yes" ) ) ) );
		item->setGo( std::make_shared<VerifyDeleteYesGoLambda>( std::static_pointer_cast<VerifyDeleteSeeds>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		// No
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_NO, ItemFont, static_cast<std::wstring>( _T( "No" ) ) ) );
		item->setGo( std::make_shared<VerifyDeleteNoGoLambda>( std::static_pointer_cast<VerifyDeleteSeeds>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		MyMenu->OnX = MyMenu->OnB = std::make_shared<VerifyDeleteOnXLambda>( std::static_pointer_cast<VerifyDeleteSeeds>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}
}
