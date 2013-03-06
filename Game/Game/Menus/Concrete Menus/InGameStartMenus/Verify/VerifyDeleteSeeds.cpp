#include <global_header.h>

#include <Hacks/String.h>

namespace CloudberryKingdom
{

	VerifyDeleteSeeds::VerifyDeleteYesGoLambda::VerifyDeleteYesGoLambda( const boost::shared_ptr<VerifyDeleteSeeds> &vds )
	{
		this->vds = vds;
	}

	void VerifyDeleteSeeds::VerifyDeleteYesGoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		vds->DoSelect( true );
		vds->ReturnToCaller();
	}

	VerifyDeleteSeeds::VerifyDeleteOnXLambda::VerifyDeleteOnXLambda( const boost::shared_ptr<VerifyDeleteSeeds> &vds )
	{
		this->vds = vds;
	}

	bool VerifyDeleteSeeds::VerifyDeleteOnXLambda::Apply( const boost::shared_ptr<Menu> &item )
	{
		vds->DoSelect( false );
		vds->ReturnToCaller();
		return true;
	}

	VerifyDeleteSeeds::VerifyDeleteNoGoLambda::VerifyDeleteNoGoLambda( const boost::shared_ptr<VerifyDeleteSeeds> &vds )
	{
		this->vds = vds;
	}

	void VerifyDeleteSeeds::VerifyDeleteNoGoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		vds->DoSelect( false );
		vds->ReturnToCaller();
	}

	VerifyDeleteSeeds::VerifyDeleteSeeds( int Control, int NumSeeds ) :
		VerifyBaseMenu( false ),
		NumSeeds( 0 )
	{
	}
	boost::shared_ptr<VerifyDeleteSeeds> VerifyDeleteSeeds::VerifyDeleteSeeds_Construct( int Control, int NumSeeds )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( false );

		//EnableBounce();

		this->NumSeeds = NumSeeds;
		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<VerifyDeleteSeeds>( shared_from_this() );
	}

	void VerifyDeleteSeeds::Init()
	{
		VerifyBaseMenu::Init();

		// Make the menu
		boost::shared_ptr<MenuItem> item;

		// Header
		std::wstring Text;
		if ( NumSeeds == 1 )
			Text = Format( Localization::WordString( Localization::Words_DeleteSeeds ).c_str(), ToString( NumSeeds ).c_str() );
		else
			Text = Format( Localization::WordString( Localization::Words_DeleteSeedsPlural ).c_str(), ToString( NumSeeds ).c_str() );
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Text, ItemFont, static_cast<std::wstring>( std::wstring( L"Header" ) ) );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );


		// Yes
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Yes, ItemFont, static_cast<std::wstring>( std::wstring( L"Yes" ) ) ) ) );
		item->setGo( boost::make_shared<VerifyDeleteYesGoLambda>( boost::static_pointer_cast<VerifyDeleteSeeds>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		// No
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_No, ItemFont, static_cast<std::wstring>( std::wstring( L"No" ) ) ) ) );
		item->setGo( boost::make_shared<VerifyDeleteNoGoLambda>( boost::static_pointer_cast<VerifyDeleteSeeds>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<VerifyDeleteOnXLambda>( boost::static_pointer_cast<VerifyDeleteSeeds>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}
}
