#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	VerifyQuitGameMenu2::InitTextureNameSetter::InitTextureNameSetter( const boost::shared_ptr<QuadClass> &Berry, const std::wstring &textureName )
	{
		this->Berry = Berry;
		this->textureName = textureName;
	}

	void VerifyQuitGameMenu2::InitTextureNameSetter::Apply()
	{
		Berry->setTextureName( textureName );
	}

	VerifyQuitGameMenu2::VerifyQuitGameMenu2( int Control ) : VerifyBaseMenu( Control ) { }
	boost::shared_ptr<VerifyQuitGameMenu2> VerifyQuitGameMenu2::VerifyQuitGameMenu2_Construct( int Control )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( Control );

		EnableBounce();
		
		return boost::static_pointer_cast<VerifyQuitGameMenu2>( shared_from_this() );
	}

	void VerifyQuitGameMenu2::MakeBackdrop()
	{
		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true, false );
		//backdrop->setTextureName( std::wstring( L"Backplate_1230x740" ) );
		backdrop->setTextureName( std::wstring( L"Arcade_BoxLeft" ) );

		backdrop->ScaleYToMatchRatio( 1000 );
		MyPile->Add( backdrop, std::wstring( L"Backdrop" ) );

		Berry = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true, false );
		Berry->setTextureName( std::wstring( L"cb_crying" ) );
		MyPile->Add( Berry, std::wstring( L"Berry" ) );

	}

	void VerifyQuitGameMenu2::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		VerifyBaseMenu::SetItemProperties( item );

		//item->MyText->setScale( item->MyText->getScale() * 1.15f );
		//item->MySelectedText->setScale( item->MySelectedText->getScale() * 1.3f );
		//CkColorHelper::GreenItem( item );

        StartMenu::SetItemProperties_Red(item);
        item->MyText->Shadow = item->MySelectedText->Shadow = false;
	}

	void VerifyQuitGameMenu2::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		VerifyBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
		text->setScale( text->getScale() * 1.15f );

		text->MyFloatColor = ColorHelper.Gray(.9f);
	}

	void VerifyQuitGameMenu2::Init()
	{
		VerifyBaseMenu::Init();

		SlideInFrom = SlideOutTo = PresetPos_BOTTOM;
		DestinationScale = Vector2( 1.223f );

		// Make the menu
		boost::shared_ptr<MenuItem> item;

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::Words_ExitGame, ItemFont );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		HeaderText->setPos( Vector2( -701.1883f, 816.7295f ) );

		// Yes
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Yes, ItemFont ) ) );
		item->Name = std::wstring( L"Yes" );
		item->setGo( Cast::ToItem( boost::make_shared<CloudberryKingdomGame::ExitProxy>( Tools::TheGame ) ) );
		item->AdditionalOnSelect = boost::make_shared<InitTextureNameSetter>( Berry, std::wstring( L"cb_crying" ) );
		AddItem( item );

		// No
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_No, ItemFont ) ) );
		item->Name = std::wstring( L"No" );
		item->setGo( boost::make_shared<MenuReturnToCallerLambda>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
		item->AdditionalOnSelect = boost::make_shared<InitTextureNameSetter>( Berry, std::wstring( L"cb_enthusiastic" ) );
		item->SelectSound.reset();
		BackSound.reset();
		AddItem( item );

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		EnsureFancy();
		SetPosition();
	}

	void VerifyQuitGameMenu2::SetPosition()
    {
        //boost::shared_ptr<MenuItem> _item;
        //_item = MyMenu->FindItemByName( L"Yes" ); if (_item != 0 ) { _item->setSetPos( Vector2( 800.f, 361.f ) ); _item->MyText->setScale( 0.92f ); _item->MySelectedText->setScale( 1.04f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        //_item = MyMenu->FindItemByName( L"No" ); if (_item != 0 ) { _item->setSetPos( Vector2( 800.f, 61.f ) ); _item->MyText->setScale( 0.92f ); _item->MySelectedText->setScale( 1.04f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

        //MyMenu->setPos( Vector2(-396.8268f, -265.873f ) );

        //boost::shared_ptr<EzText> _t;
        //_t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2(-442.855f, 605.6183f ) ); _t->setScale( 0.7911667f ); }

        //boost::shared_ptr<QuadClass> _q;
        //_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 44.44434f, 30.5556f ) ); _q->setSize( Vector2( 1065.378f, 640.9592f ) ); }
        //_q = MyPile->FindQuad( L"Berry" ); if (_q != 0 ) { _q->setPos( Vector2( 16.6665f, -25.f ) ); _q->setSize( Vector2( 398.1559f, 537.0001f ) ); }

        //MyPile->setPos( Vector2( 13.8877f, -1.984146f ) );

        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Yes" ); if (_item != 0 ) { _item->setSetPos( Vector2( 677.7778f, 430.4445f ) ); _item->MyText->setScale( 0.7628335f ); _item->MySelectedText->setScale( 0.7628335f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"No" ); if (_item != 0 ) { _item->setSetPos( Vector2( 702.7778f, 197.1111f ) ); _item->MyText->setScale( 0.73975f ); _item->MySelectedText->setScale( 0.73975f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

        MyMenu->setPos( Vector2(-396.8268f, -265.873f ) );

        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"" ); if (_t != 0 ) { _t->setPos( Vector2(-26.18762f, 394.5072f ) ); _t->setScale( 0.7095835f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 44.44434f, 30.5556f ) ); _q->setSize( Vector2( 978.2115f, 727.7092f ) ); }
        _q = MyPile->FindQuad( L"Berry" ); if (_q != 0 ) { _q->setPos( Vector2(-416.6666f, -13.8889f ) ); _q->setSize( Vector2( 398.1559f, 537.0001f ) ); }

        MyPile->setPos( Vector2( 13.8877f, -1.984146f ) );
    }
}
