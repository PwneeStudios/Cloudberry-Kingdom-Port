#include <global_header.h>

namespace CloudberryKingdom
{

	SaveSeedAs::SaveProxy::SaveProxy( const boost::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::SaveProxy::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		ssa->Save( _item );
	}

	SaveSeedAs::OnOkProxy::OnOkProxy( const boost::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::OnOkProxy::Apply()
	{
		ssa->OnOk();
	}

	SaveSeedAs::SaveSeedAsOnEscapeLambda::SaveSeedAsOnEscapeLambda( const boost::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::SaveSeedAsOnEscapeLambda::Apply()
	{
		ssa->TextBox->Active = false;
		ssa->ReturnToCaller();
	}

	SaveSeedAs::SaveSeedAsOnEnterLambda::SaveSeedAsOnEnterLambda( const boost::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::SaveSeedAsOnEnterLambda::Apply()
	{
		if ( ssa->TextBox->getText().length() <= 0 )
			return;

		ssa->Save( 0 );
	}

	SaveSeedAs::SaveSeedAs( int Control, const boost::shared_ptr<PlayerData> &Player ) : VerifyBaseMenu( false ) { }
	boost::shared_ptr<SaveSeedAs> SaveSeedAs::SaveSeedAs_Construct( int Control, const boost::shared_ptr<PlayerData> &Player )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( false );

		EnableBounce();

		this->setControl( Control );
		this->Player = Player;
		FixedToCamera = true;

		Constructor();

		return boost::static_pointer_cast<SaveSeedAs>( shared_from_this() );
	}

	void SaveSeedAs::Init()
	{
		VerifyBaseMenu::Init();

		this->FontScale *= .9f;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		boost::shared_ptr<MenuItem> item;

		// Header
		HeaderText = boost::make_shared<EzText>( Localization::Words_SaveRandomSeedAs, ItemFont );
		HeaderText->Name = std::wstring( L"Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		// Save seed
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SaveSeed, ItemFont ) ) );
		item->Name = std::wstring( L"Save" );
		item->setGo( boost::make_shared<SaveProxy>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) ) );
		AddItem( item );

#ifdef PC_VERSION
            MakeBackButton();
#else
            MakeBackButton();
            //MakeStaticBackButton();
#endif

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		SetPosition();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void SaveSeedAs::Save( const boost::shared_ptr<MenuItem> &_item )
	{
		// Save the seed
		if ( TextBox->getText().length() > 0 )
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			Player->MySavedSeeds->SaveSeed( Tools::CurLevel->MyLevelSeed->ToString(), TextBox->getText() );

			// Success!
			boost::shared_ptr<AlertBaseMenu> ok = MakeMagic( AlertBaseMenu, ( getControl(), Localization::Words_SeedSavedSuccessfully, Localization::Words_Hooray ) );
			ok->OnOk = boost::make_shared<OnOkProxy>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) );
			GUI_Panel::Call( ok );

			SavedSeedsGUI::RefreshList = true;
		}
		else
		{
			// Failure!
			boost::shared_ptr<AlertBaseMenu> ok = MakeMagic( AlertBaseMenu, ( getControl(), Localization::Words_NoNameGiven, Localization::Words_Oh ) );
			ok->OnOk = boost::make_shared<OnOkProxy>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) );
			GUI_Panel::Call( ok );
		}

        if (UseBounce)
        {
            Hid = true;
            RegularSlideOut( PresetPos_RIGHT, 0 );
        }
        else
        {
			Hide( PresetPos_LEFT );
			Active = false;
		}
	}

	void SaveSeedAs::OnReturnTo()
	{
		// Do nothing
	}

	void SaveSeedAs::OnOk()
	{
		this->SlideOutTo = PresetPos_LEFT;
		ReturnToCaller( false );

		this->Hid = true;
		this->Active = false;
	}

	void SaveSeedAs::Release()
	{
		VerifyBaseMenu::Release();

		TextBox->Release();
	}

	void SaveSeedAs::SetPosition()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Save" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1269.445f, 161 ) );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1338.89f, -52.8888f ) );
		}

		MyMenu->setPos( Vector2( -1125.001f, -319.4444f ) );

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1175.696f, 233.3334f ) );
			_q->setSize( Vector2( 1500, 803.2258f ) );
		}
		MyPile->FindEzText( std::wstring( L"Header" ) )->setPos( Vector2( 61.11098f, 821.8887f ) );

		MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
	}

	void SaveSeedAs::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		TextBox = MakeMagic( GUI_TextBox, ( Tools::CurLevel->MyLevelSeed->SuggestedName(), Vector2(), Vector2(1.85f,.65f),.95f ) );
		TextBox->MaxLength = 50;
		TextBox->FixedToCamera = false;
		TextBox->Pos->SetCenter( MyPile->FancyPos );
		TextBox->Pos->RelVal = Vector2( 1175.001f, 277.7778f );
		TextBox->OnEnter->Add( boost::make_shared<SaveSeedAsOnEnterLambda>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) ) );
		TextBox->OnEscape->Add( boost::make_shared<SaveSeedAsOnEscapeLambda>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) ) );
		MyGame->AddGameObject( TextBox );

		SetPosition();
	}
}
