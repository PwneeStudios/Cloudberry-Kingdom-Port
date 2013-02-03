#include <global_header.h>

namespace CloudberryKingdom
{

	void VerifyBaseMenu::DoSelect( bool choice )
	{
		if ( OnSelect != 0 )
			OnSelect->Apply( choice );
	}

	void VerifyBaseMenu::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		OnSelect.reset();
	}

	VerifyBaseMenu::VerifyBaseMenu() { }
	boost::shared_ptr<VerifyBaseMenu> VerifyBaseMenu::VerifyBaseMenu_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();

		return boost::static_pointer_cast<VerifyBaseMenu>( shared_from_this() );
	}

	VerifyBaseMenu::VerifyBaseMenu( int Control, bool DoEnableBounce ) : CkBaseMenu( false ) { }
	boost::shared_ptr<VerifyBaseMenu> VerifyBaseMenu::VerifyBaseMenu_Construct( int Control, bool DoEnableBounce )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( false );
		
		if (DoEnableBounce) EnableBounce();

		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<VerifyBaseMenu>( shared_from_this() );
	}

	VerifyBaseMenu::VerifyBaseMenu( bool CallBaseConstructor ) : CkBaseMenu( CallBaseConstructor ) { }
	boost::shared_ptr<VerifyBaseMenu> VerifyBaseMenu::VerifyBaseMenu_Construct( bool CallBaseConstructor )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( CallBaseConstructor );

		return boost::static_pointer_cast<VerifyBaseMenu>( shared_from_this() );
	}

	void VerifyBaseMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.2f );
	}

	void VerifyBaseMenu::MakeBackdrop()
	{
        boost::shared_ptr<QuadClass> Backdrop;
        if (UseBounce)
            Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 1500.f, true );
        else
			Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1230x740" ), 1500.f, true );

		Backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( Backdrop );
		Backdrop->setPos( Vector2( 1181.251f, 241.6668f ) );
	}

	void VerifyBaseMenu::Init()
	{
		CkBaseMenu::Init();

		setPauseGame( true );

		if (!UseBounce)
		{
			ReturnToCallerDelay = 10;
			SlideInLength = 26;
			SlideOutLength = 26;
		}


		this->SlideInFrom = PresetPos_RIGHT;
		this->SlideOutTo = PresetPos_RIGHT;

		FontScale = .8f;

		MyPile = boost::make_shared<DrawPile>();

		// Make the backdrop
		MakeBackdrop();

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );
		MyMenu->setControl( getControl() );

		ItemPos = Vector2( 800, 361 );
		PosAdd = Vector2( 0, -300 );

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Shift everything
		EnsureFancy();
		Shift( Vector2( -1125.001f, -319.4444f ) );
	}

	void VerifyBaseMenu::InitializeInstanceFields()
	{
		OnSelect = boost::make_shared<Multicaster_1<bool> >();
		HeaderPos = Vector2( 413.8888f, 713.5555f );
	}
}
