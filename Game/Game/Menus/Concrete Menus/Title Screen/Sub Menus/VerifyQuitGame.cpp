#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	VerifyQuitGameMenu2::InitTextureNameSetter::InitTextureNameSetter( const std::shared_ptr<QuadClass> &Berry, const std::wstring &textureName )
	{
		this->Berry = Berry;
		this->textureName = textureName;
	}

	void VerifyQuitGameMenu2::InitTextureNameSetter::Apply()
	{
		Berry->setTextureName( textureName );
	}

	VerifyQuitGameMenu2::VerifyQuitGameMenu2( int Control ) : VerifyBaseMenu( Control ) { }
	std::shared_ptr<VerifyQuitGameMenu2> VerifyQuitGameMenu2::VerifyQuitGameMenu2_Construct( int Control )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( Control );
		
		return std::static_pointer_cast<VerifyQuitGameMenu2>( shared_from_this() );
	}

	void VerifyQuitGameMenu2::MakeBackdrop()
	{
		std::shared_ptr<QuadClass> backdrop = std::make_shared<QuadClass>( std::shared_ptr<EzTexture>(), true, false );
		backdrop->setTextureName( _T( "Backplate_1230x740" ) );
		backdrop->ScaleYToMatchRatio( 1000 );
		MyPile->Add( backdrop, _T( "Backdrop" ) );

		Berry = std::make_shared<QuadClass>( std::shared_ptr<EzTexture>(), true, false );
		Berry->setTextureName( _T( "cb_crying" ) );
		MyPile->Add( Berry, _T( "Berry" ) );

		//QuadClass Cloudback = new QuadClass("menupic_bg_cloud", 1200, true);
		//Cloudback.Pos = new Vector2(99.20645f, 19.84137f);
		//Cloudback.Size = new Vector2(1303.173f, 1019.564f);
		//MyPile.Add(Cloudback);

		//Berry = new QuadClass(null, true, false);
		//Berry.TextureName = "cb_crying";
		//Berry.ScaleYToMatchRatio(1000);
		//MyPile.Add(Berry);
		//Berry.Pos =
		//    new Vector2(-107.14f, -99.20639f);
		//Berry.Size =
		//    new Vector2(519.8459f, 678.0841f);
	}

	void VerifyQuitGameMenu2::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		VerifyBaseMenu::SetItemProperties( item );

		item->MyText->setScale( item->MyText->getScale() * 1.15f );
		item->MySelectedText->setScale( item->MySelectedText->getScale() * 1.3f );

		CkColorHelper::GreenItem( item );
	}

	void VerifyQuitGameMenu2::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		VerifyBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
		text->setScale( text->getScale() * 1.15f );
	}

	void VerifyQuitGameMenu2::Init()
	{
		VerifyBaseMenu::Init();

		SlideInFrom = SlideOutTo = PresetPos_BOTTOM;
		DestinationScale = Vector2( 1.223f );

		// Make the menu
		std::shared_ptr<MenuItem> item;

		// Header
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Localization::Words_EXIT_GAME, ItemFont );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		HeaderText->setPos( Vector2( -701.1883f, 816.7295f ) );

		// Yes
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_YES, ItemFont ) );
		item->Name = _T( "Yes" );
		item->setGo( Cast::ToItem( std::make_shared<CloudberryKingdomGame::ExitProxy>( Tools::TheGame ) ) );
		item->AdditionalOnSelect = std::make_shared<InitTextureNameSetter>( Berry, _T( "cb_crying" ) );
		AddItem( item );

		// No
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_NO, ItemFont ) );
		item->Name = _T( "No" );
		item->setGo( std::make_shared<MenuReturnToCallerLambda>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
		item->AdditionalOnSelect = std::make_shared<InitTextureNameSetter>( Berry, _T( "cb_enthusiastic" ) );
		item->SelectSound.reset();
		BackSound.reset();
		AddItem( item );

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		EnsureFancy();
		SetPosition();
	}

	void VerifyQuitGameMenu2::SetPosition()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Yes" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 800, 361 ) );
			_item->MyText->setScale( 0.92f );
			_item->MySelectedText->setScale( 1.04f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "No" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 800, 61 ) );
			_item->MyText->setScale( 0.92f );
			_item->MySelectedText->setScale( 1.04f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( -396.8268f, -265.873f ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -442.855f, 605.6183f ) );
			_t->setScale( 0.7911667f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 44.44434f, 30.5556f ) );
			_q->setSize( Vector2( 1065.378f, 640.9592f ) );
		}
		_q = MyPile->FindQuad( _T( "Berry" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 16.6665f, -25 ) );
			_q->setSize( Vector2( 398.1559f, 537.0001f ) );
		}

		MyPile->setPos( Vector2( 13.8877f, -1.984146f ) );
	}
}
