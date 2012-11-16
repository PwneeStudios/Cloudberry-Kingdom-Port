#include <global_header.h>


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	AlertBaseMenu::OkProxy::OkProxy( const std::shared_ptr<AlertBaseMenu> &abm )
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

	AlertBaseMenu::AlertBaseMenu()
	{
	}

	AlertBaseMenu::AlertBaseMenu( int Control, Localization::Words Message, Localization::Words OkText ) : CkBaseMenu( false )
	{
		this->setControl( Control );
		this->Message = Message;
		this->OkText = OkText;

		Constructor();
	}

	AlertBaseMenu::AlertBaseMenu( bool CallBaseConstructor ) : CkBaseMenu( CallBaseConstructor )
	{
	}

	void AlertBaseMenu::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.2f );
	}

	void AlertBaseMenu::MakeBackdrop()
	{
		Backdrop = std::make_shared<QuadClass>( _T( "Backplate_1230x740" ), 1500, true );
		Backdrop->Name = _T( "Backdrop" );
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

		MyPile = std::make_shared<DrawPile>();

		// Make the backdrop
		MakeBackdrop();

		std::shared_ptr<EzText> message = std::make_shared<EzText>( Message, ItemFont, 700, true, true );
		message->Name = _T( "Message" );
		MyPile->Add( message );

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );
		MyMenu->setControl( getControl() );

		std::shared_ptr<MenuItem> OkItem = std::make_shared<MenuItem>( std::make_shared<EzText>( OkText, ItemFont, true, true ), _T( "Message" ) );
		OkItem->setGo( Cast::ToItem( std::make_shared<OkProxy>( this ) ) );
		AddItem( OkItem );
		OkItem->SelectSound.reset();

		MyMenu->OnA = MyMenu->OnX = MyMenu->OnB = Cast::ToMenu( std::make_shared<OkProxy>( this ) );

		EnsureFancy();



		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Message" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 22.55518f, -626.111f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 0, 0 ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Message" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 0, 0 ) );
			_t->setScale( 1 );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1500, 902.439f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}
}
