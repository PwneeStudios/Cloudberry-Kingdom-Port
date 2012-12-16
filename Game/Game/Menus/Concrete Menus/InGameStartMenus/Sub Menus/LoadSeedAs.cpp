#include <global_header.h>

#include "Hacks/Clipboard.h"

namespace CloudberryKingdom
{

	LoadSeedAs::LoadSeedAsOnEnterLambda::LoadSeedAsOnEnterLambda( const boost::shared_ptr<LoadSeedAs> &lsa )
	{
		this->lsa = lsa;
	}

	void LoadSeedAs::LoadSeedAsOnEnterLambda::Apply()
	{
		SavedSeedsGUI::LoadSeed( lsa->TextBox->getText(), lsa );
		lsa->Active = false;
		lsa->ReturnToCaller();
	}

	LoadSeedAs::LoadSeedAsBackLambda::LoadSeedAsBackLambda( const boost::shared_ptr<LoadSeedAs> &lsa )
	{
		this->lsa = lsa;
	}

	void LoadSeedAs::LoadSeedAsBackLambda::Apply()
	{
		lsa->TextBox->Active = false;
		lsa->ReturnToCaller();
	}

	LoadSeedAs::LoadProxy1::LoadProxy1( const boost::shared_ptr<LoadSeedAs> &lsa )
	{
		this->lsa = lsa;
	}

	void LoadSeedAs::LoadProxy1::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		lsa->Load( _item );
	}

	LoadSeedAs::LoadSeedAs( int Control, const boost::shared_ptr<PlayerData> &Player ) : VerifyBaseMenu( false ) { }
	boost::shared_ptr<LoadSeedAs> LoadSeedAs::LoadSeedAs_Construct( int Control, const boost::shared_ptr<PlayerData> &Player )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( false );

		this->setControl( Control );
		this->Player = Player;
		FixedToCamera = true;

		Constructor();

		return boost::static_pointer_cast<LoadSeedAs>( shared_from_this() );
	}

	void LoadSeedAs::Init()
	{
		VerifyBaseMenu::Init();

		this->FontScale *= .9f;

		// Header
		std::wstring Text = _T( "Load the following Seed...?" );
		HeaderText = boost::make_shared<EzText>( Text, ItemFont );
		HeaderText->Name = _T( "Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( HeaderPos );

		// Question
		//HeaderText = new EzText("?", ItemFont);
		//HeaderText.Name = "Question";
		//SetHeaderProperties(HeaderText);
		//MyPile.Add(HeaderText);
		//HeaderText.Pos = HeaderPos;

		boost::shared_ptr<MenuItem> item;

		// Load seed
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_LOAD_SEED, ItemFont ) );
		item->Name = _T( "Load" );
		item->setGo( boost::make_shared<LoadProxy1>( boost::static_pointer_cast<LoadSeedAs>( shared_from_this() ) ) );
		AddItem( item );


		MakeBackButton();

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		SetPosition();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void LoadSeedAs::Release()
	{
		VerifyBaseMenu::Release();

		TextBox->Release();
	}

	void LoadSeedAs::SetPosition()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Load" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1269.445f, 161 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1338.89f, -52.8888f ) );
		}

		MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

		MyPile->FindEzText( _T( "Header" ) )->setPos( Vector2( 61.11098f, 821.8887f ) );

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1175.696f, 233.3334f ) );
			_q->setSize( Vector2( 1500, 803.2258f ) );
		}

		MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
	}

	void LoadSeedAs::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		std::wstring clipboard = _T( "" );

	#if defined(WINDOWS)
		try
		{
			clipboard = Clipboard::GetText();
		}
		catch ( ... )
		{
			clipboard = _T( "<Error>" );
		}
	#endif

		if ( clipboard == _T( "" ) || clipboard.length() == 0 )
			clipboard = _T( "Type in a seed!" );

		TextBox = MakeMagic( GUI_TextBox, ( clipboard, Vector2(), Vector2( 1.85f,.65f ), .95f ) );
		TextBox->MaxLength = 80;
		TextBox->FixedToCamera = false;
		TextBox->Pos->SetCenter( MyPile->FancyPos );
		TextBox->Pos->RelVal = Vector2( 1175.001f, 277.7778f );
		TextBox->OnEnter->Add( boost::make_shared<LoadSeedAsOnEnterLambda>( boost::static_pointer_cast<LoadSeedAs>( shared_from_this() ) ) );
		TextBox->OnEscape->Add( boost::make_shared<LoadSeedAsBackLambda>( boost::static_pointer_cast<LoadSeedAs>( shared_from_this() ) ) );
		MyGame->AddGameObject( TextBox );

		SetPosition();
	}

	void LoadSeedAs::Load( const boost::shared_ptr<MenuItem> &_item )
	{
		if ( TextBox != 0 )
		{
			TextBox->Enter();
			return;
		}

		SavedSeedsGUI::LoadSeed( TextBox->getText(), boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}
}
