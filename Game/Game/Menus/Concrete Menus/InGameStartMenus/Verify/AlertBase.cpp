#include <global_header.h>

namespace CloudberryKingdom
{

	AlertBaseMenu::OkProxy::OkProxy( const boost::shared_ptr<AlertBaseMenu> &abm )
	{
		this->abm = abm;
	}

	void AlertBaseMenu::OkProxy::Apply()
	{
		abm->Ok();
	}

	void AlertBaseMenu::Ok()
	{
		ReturnToCaller();

		if ( OnOk != 0 )
			OnOk->Apply();
	}

	void AlertBaseMenu::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		OnOk.reset();
	}

	AlertBaseMenu::AlertBaseMenu() :
		Message( static_cast<Localization::Words>( 0 ) ), OkText( static_cast<Localization::Words>( 0 ) )
	{
	}
	boost::shared_ptr<AlertBaseMenu> AlertBaseMenu::AlertBaseMenu_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		return boost::static_pointer_cast<AlertBaseMenu>( shared_from_this() );
	}

	AlertBaseMenu::AlertBaseMenu( int Control, Localization::Words Message, Localization::Words OkText ) :
		Message( static_cast<Localization::Words>( 0 ) ), OkText( static_cast<Localization::Words>( 0 ) ),
		CkBaseMenu( false )
	{
	}
	boost::shared_ptr<AlertBaseMenu> AlertBaseMenu::AlertBaseMenu_Construct( int Control, Localization::Words Message, Localization::Words OkText )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		EnableBounce();

		this->setControl( Control );
		this->Message = Message;
		this->OkText = OkText;

		Constructor();

		return boost::static_pointer_cast<AlertBaseMenu>( shared_from_this() );
	}

	AlertBaseMenu::AlertBaseMenu( bool CallBaseConstructor ) :
		CkBaseMenu( CallBaseConstructor ),
		Message( static_cast<Localization::Words>( 0 ) ), OkText( static_cast<Localization::Words>( 0 ) )
	{
	}
	boost::shared_ptr<AlertBaseMenu> AlertBaseMenu::AlertBaseMenu_Construct( bool CallBaseConstructor )
	{
		CkBaseMenu::CkBaseMenu_Construct( CallBaseConstructor );

		return boost::static_pointer_cast<AlertBaseMenu>( shared_from_this() );
	}

	void AlertBaseMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.2f );
	}

	void AlertBaseMenu::MakeBackdrop()
	{
        if (UseBounce)
            Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 1500.f, true );
        else
			Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1230x740" ), 1500.f, true );

		Backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( Backdrop );
	}

	void AlertBaseMenu::Init()
	{
		CkBaseMenu::Init();

		setPauseGame( true );

		ReturnToCallerDelay = 10;
		SlideInLength = 26;
		SlideOutLength = 26;

		this->SlideInFrom = PresetPos_RIGHT;
		this->SlideOutTo = PresetPos_RIGHT;

		FontScale = .8f;

		MyPile = boost::make_shared<DrawPile>();

		// Make the backdrop
		MakeBackdrop();

		boost::shared_ptr<EzText> message = boost::make_shared<EzText>( Message, ItemFont, 700.f, true, true, .75f );
		message->Name = std::wstring( L"Message" );
		MyPile->Add( message );

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );
		MyMenu->setControl( getControl() );

		boost::shared_ptr<MenuItem> OkItem = MakeMagic( MenuItem, ( boost::make_shared<EzText>( OkText, ItemFont, true, true ), std::wstring( L"Message" ) ) );
		OkItem->setGo( Cast::ToItem( boost::make_shared<OkProxy>( boost::static_pointer_cast<AlertBaseMenu>( shared_from_this() ) ) ) );
		AddItem( OkItem );
		OkItem->SelectSound.reset();

		MyMenu->OnA = MyMenu->OnX = MyMenu->OnB = Cast::ToMenu( boost::make_shared<OkProxy>( boost::static_pointer_cast<AlertBaseMenu>( shared_from_this() ) ) );

		EnsureFancy();


        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Message" ); if (_item != 0 ) { _item->setSetPos( Vector2( 22.55518f, -626.111f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

        MyMenu->setPos( Vector2( 0.f, 0.f ) );

        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"Message" ); if (_t != 0 ) { _t->setPos( Vector2( 0.f, 0.f ) ); _t->setScale( 1.f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1500.f, 902.439f ) ); }

        MyPile->setPos( Vector2( 0.f, 0.f ) );
	}

}
