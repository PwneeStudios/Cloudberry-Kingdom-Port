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
	std::shared_ptr<VerifyBaseMenu> VerifyBaseMenu::VerifyBaseMenu_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		InitializeInstanceFields();
	}

	VerifyBaseMenu::VerifyBaseMenu( int Control ) : CkBaseMenu( false ) { }
	std::shared_ptr<VerifyBaseMenu> VerifyBaseMenu::VerifyBaseMenu_Construct( int Control )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		InitializeInstanceFields();
		this->setControl( Control );

		Constructor();
	}

	VerifyBaseMenu::VerifyBaseMenu( bool CallBaseConstructor ) : CkBaseMenu( CallBaseConstructor ) { }
	std::shared_ptr<VerifyBaseMenu> VerifyBaseMenu::VerifyBaseMenu_Construct( bool CallBaseConstructor )
	{
		CkBaseMenu::CkBaseMenu_Construct( CallBaseConstructor );

		InitializeInstanceFields();
	}

	void VerifyBaseMenu::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.2f );
	}

	void VerifyBaseMenu::MakeBackdrop()
	{
		Backdrop = std::make_shared<QuadClass>( _T( "Backplate_1230x740" ), 1500.f, true );
		Backdrop->Name = _T( "Backdrop" );
		MyPile->Add( Backdrop );
		Backdrop->setPos( Vector2( 1181.251f, 241.6668f ) );
			//new Vector2(1525.001f, 200.0001f);
	}

	void VerifyBaseMenu::Init()
	{
		CkBaseMenu::Init();

		setPauseGame( true );

		ReturnToCallerDelay = 10;
		SlideInLength = 26;
		SlideOutLength = 26;

		this->SlideInFrom = PresetPos_RIGHT;
		this->SlideOutTo = PresetPos_RIGHT;

		FontScale = .8f;

		MyPile = std::make_shared<DrawPile>();

		// Make the backdrop
		MakeBackdrop();

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );
		MyMenu->setControl( getControl() );

		ItemPos = Vector2( 800, 361 );
		PosAdd = Vector2( 0, -300 );

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Shift everything
		EnsureFancy();
		Shift( Vector2( -1125.001f, -319.4444f ) );
	}

	void VerifyBaseMenu::InitializeInstanceFields()
	{
		OnSelect = std::make_shared<Multicaster_1<bool> >();
		HeaderPos = Vector2( 413.8888f, 713.5555f );
	}
}
