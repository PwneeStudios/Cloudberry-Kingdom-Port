#include <global_header.h>








namespace CloudberryKingdom
{

	SaveSeedAs::SaveProxy::SaveProxy( const std::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::SaveProxy::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		ssa->Save( _item );
	}

	SaveSeedAs::OnOkProxy::OnOkProxy( const std::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::OnOkProxy::Apply()
	{
		ssa->OnOk();
	}

	SaveSeedAs::SaveSeedAsOnEscapeLambda::SaveSeedAsOnEscapeLambda( const std::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::SaveSeedAsOnEscapeLambda::Apply()
	{
		ssa->TextBox->Active = false;
		ssa->ReturnToCaller();
	}

	SaveSeedAs::SaveSeedAsOnEnterLambda::SaveSeedAsOnEnterLambda( const std::shared_ptr<SaveSeedAs> &ssa )
	{
		this->ssa = ssa;
	}

	void SaveSeedAs::SaveSeedAsOnEnterLambda::Apply()
	{
		if ( ssa->TextBox->Text->Length <= 0 )
			return;

		ssa->Save( 0 );
	}

	SaveSeedAs::SaveSeedAs( int Control, const std::shared_ptr<PlayerData> &Player ) : VerifyBaseMenu( false )
	{
		this->setControl( Control );
		this->Player = Player;
		FixedToCamera = true;

		Constructor();
	}

	void SaveSeedAs::Init()
	{
		VerifyBaseMenu::Init();

		this->FontScale *= .9f;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		std::shared_ptr<MenuItem> item;

		// Header
		HeaderText = std::make_shared<EzText>( Localization::Words_SAVE_RANDOM_SEED_AS, ItemFont );
		HeaderText->Name = _T( "Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		// Save seed
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_SAVE_SEED, ItemFont ) );
		item->Name = _T( "Save" );
		item->setGo( std::make_shared<SaveProxy>( this ) );
		AddItem( item );


		MakeBackButton();

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		SetPosition();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void SaveSeedAs::Save( const std::shared_ptr<MenuItem> &_item )
	{
		// Save the seed
		if ( TextBox->getText().length() > 0 )
		{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			Player->MySavedSeeds->SaveSeed( Tools::CurLevel->MyLevelSeed->ToString(), TextBox->getText() );

			// Success!
			std::shared_ptr<AlertBaseMenu> ok = std::make_shared<AlertBaseMenu>( getControl(), Localization::Words_SEED_SAVED_SUCCESSFULLY, Localization::Words_HOORAY );
			ok->OnOk = std::make_shared<OnOkProxy>( this );
			Call( ok );
		}
		else
		{
			// Failure!
			std::shared_ptr<AlertBaseMenu> ok = std::make_shared<AlertBaseMenu>( getControl(), Localization::Words_NO_NAME_GIVEN, Localization::Words_OH );
			ok->OnOk = std::make_shared<OnOkProxy>( this );
			Call( ok );
		}

		Hide( PresetPos_LEFT );
		Active = false;
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
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Save" ) );
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

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1175.696f, 233.3334f ) );
			_q->setSize( Vector2( 1500, 803.2258f ) );
		}
		MyPile->FindEzText( _T( "Header" ) )->setPos( Vector2( 61.11098f, 821.8887f ) );

		MyPile->setPos( Vector2( -1125.001f, -319.4444f ) );
	}

	void SaveSeedAs::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		TextBox = std::make_shared<GUI_TextBox>( Tools::CurLevel->MyLevelSeed->SuggestedName(), Vector2::Zero, Vector2(1.85f,.65f),.95f );
		TextBox->MaxLength = 50;
		TextBox->FixedToCamera = false;
		TextBox->Pos->SetCenter( MyPile->FancyPos );
		TextBox->Pos->RelVal = Vector2( 1175.001f, 277.7778f );
		TextBox->OnEnter->Add( std::make_shared<SaveSeedAsOnEnterLambda>( this ) );
		TextBox->OnEscape->Add( std::make_shared<SaveSeedAsOnEscapeLambda>( this ) );
		MyGame->AddGameObject( TextBox );

		SetPosition();
	}
}
