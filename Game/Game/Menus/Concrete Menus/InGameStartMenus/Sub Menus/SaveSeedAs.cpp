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
		
		// Note: we ALWAYS use player 1, since all save data is shared.
		//this->Player = Player;
		this->Player = PlayerManager::Players[ 0 ];
		
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
		HeaderText = boost::make_shared<EzText>( Localization::Words_SaveRandomSeedAs, ItemFont, true, false );
		HeaderText->Name = std::wstring( L"Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		// Save seed
		//item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SaveSeed, ItemFont ) ) );
		//item->Name = std::wstring( L"Save" );
		//item->setGo( boost::make_shared<SaveProxy>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) ) );
		//AddItem( item );

		// Console version: Start to save
		boost::shared_ptr<EzText> Text = boost::make_shared<EzText>( 
		#ifdef PS3
			Localization::Words_PressStart_PS3
		#elif CAFE
			Format( Localization::WordString( Localization::Words_PressStart_WiiU ).c_str(), L"{pWiiU_Plus,90,?} " )
		#else
			Localization::Words_PressStart
		#endif
		, ItemFont );

		//Text = boost::make_shared<EzText>( Localization::Words_PressStart, ItemFont );
		MyPile->Add( Text, std::wstring( L"Start" ) );

        MyPile->Add( boost::make_shared<EzText>( Localization::Words_Delete, ItemFont ), std::wstring( L"Delete" ) );
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.0f, std::wstring( L"Button_X" ) ) );

		MyPile->Add( boost::make_shared<EzText>( Localization::Words_Back, ItemFont ), std::wstring( L"Back" ) );
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 90.0f, std::wstring( L"Button_B" ) ) );

//#ifdef PC_VERSION
//            MakeBackButton();
//#else
//            MakeBackButton();
//            //MakeStaticBackButton();
//#endif

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
			Player->MySavedSeeds->SaveSeed( Tools::CurLevel->MyLevelSeed->ToString(), TextBox->getText() );

			// Success!
			boost::shared_ptr<AlertBaseMenu> ok = MakeMagic( AlertBaseMenu, ( getControl(), Localization::Words_SeedSavedSuccessfully, Localization::Words_Hooray ) );
			ok->OnOk = boost::make_shared<OnOkProxy>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) );
			GUI_Panel::Call( ok );

			SavedSeedsGUI::LastSeedSave_TimeStamp = Tools::DrawCount;
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
			MyMenu->setPos( Vector2( -1180.001f, -240 ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" );
			if (_t != 0 )
			{
				_t->setPos( Vector2( 1130.555f, 813.5558f ) );
				_t->setScale( 0.8019168f );
				float w = _t->GetWorldWidth();
				if ( w > 1900.0f )
					_t->setScale( _t->getScale() * 1900.0f / w );
			}			
			
			_t = MyPile->FindEzText( L"Start" ); if (_t != 0 ) { _t->setPos( Vector2( 705.5557f, -125.f ) ); _t->setScale( 0.6350001f ); }
			_t = MyPile->FindEzText( L"Delete" ); if (_t != 0 ) { _t->setPos( Vector2( 2080.556f, 102.7779f ) ); _t->setScale( 0.4135835f ); }
			_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2( 2080.554f, -0.0f ) ); _t->setScale( 0.4390834f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 1175.696f, 233.3334f ) ); _q->setSize( Vector2( 1500.f, 803.2258f ) ); }
			_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2( 2033.333f, 27.77777f ) ); _q->setSize( Vector2( 46.08334f, 46.08334f ) ); }
			_q = MyPile->FindQuad( L"Button_B" ); if (_q != 0 ) { _q->setPos( Vector2( 2033.333f, -83.33337f ) ); _q->setSize( Vector2( 45.91659f, 45.91659f ) ); }

			//MyPile->setPos( Vector2(-1125.001f, -319.4444f ) );
			MyPile->setPos( Vector2( -1180.001f, -240 ) );
	}

	void SaveSeedAs::OnAdd()
	{
		VerifyBaseMenu::OnAdd();

		TextBox = MakeMagic( GUI_TextBox, ( Tools::CurLevel->MyLevelSeed->SuggestedName(), Vector2(), Vector2(1.85f,.65f),.95f ) );
		TextBox->setControl( getControl() );
		TextBox->MaxLength = 36;
		TextBox->FixedToCamera = false;
		TextBox->Pos->SetCenter( MyPile->FancyPos );
		TextBox->Pos->RelVal = Vector2( 830.0f, 277.7778f );
		TextBox->OnEnter->Add( boost::make_shared<SaveSeedAsOnEnterLambda>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) ) );
		TextBox->OnEscape->Add( boost::make_shared<SaveSeedAsOnEscapeLambda>( boost::static_pointer_cast<SaveSeedAs>( shared_from_this() ) ) );
		MyGame->AddGameObject( TextBox );

		TextBox->MyText->OutlineColor = ColorHelper::Gray( 0.1f );
		StartMenu::SetTextSelected_Red( TextBox->MyText );

		MyMenu->Active = false;

		SetPosition();
	}
}
