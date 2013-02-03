#include <global_header.h>


namespace CloudberryKingdom
{

	SavedSeedsGUI::PostMakeStandardLoadHelper::PostMakeStandardLoadHelper( const boost::shared_ptr<LevelSeedData> &seed )
	{
		this->seed = seed;
	}

	void SavedSeedsGUI::PostMakeStandardLoadHelper::Apply( const boost::shared_ptr<Level> &level )
	{
		seed->PostMake_StandardLoad( level );
	}

	SavedSeedsGUI::LoadFromFreeplayMenuHelper::LoadFromFreeplayMenuHelper( const boost::shared_ptr<LevelSeedData> &seed, const std::wstring &seedstr, const boost::shared_ptr<CustomLevel_GUI> &simple )
	{
		this->seed = seed;
		this->seedstr = seedstr;
		this->simple = simple;
	}

	void SavedSeedsGUI::LoadFromFreeplayMenuHelper::Apply()
	{
		simple->StartLevel( seed );

		// Randomize the seed for the next level, if the player chooses to continue using this LevelSeedData.
		seed = boost::make_shared<LevelSeedData>();
		seed->ReadString( seedstr );
		seed->PostMake->Add( boost::make_shared<PostMakeStandardLoadHelper>( seed ) );
		seed->setSeed( Tools::GlobalRnd->Rnd->Next() );
	}

	SavedSeedsGUI::SaveSeedsDeleteLambda::SaveSeedsDeleteLambda( const boost::shared_ptr<SavedSeedsGUI> &gui )
	{
		this->gui = gui;
	}

	bool SavedSeedsGUI::SaveSeedsDeleteLambda::Apply( const boost::shared_ptr<Menu> &menu )
	{
		return gui->Delete( menu );
	}

	SavedSeedsGUI::ReturnToCallerProxy::ReturnToCallerProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::ReturnToCallerProxy::Apply()
	{
		ssGui->ReturnToCaller();
	}

	SavedSeedsGUI::DoDeletionProxy::DoDeletionProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::DoDeletionProxy::Apply( const bool &choice )
	{
		ssGui->DoDeletion( choice );
	}

	SavedSeedsGUI::SortProxy::SortProxy( const boost::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::SortProxy::Apply()
	{
		ssGui->Sort();
	}

	SavedSeedsGUI::SaveSeedsBackLambda::SaveSeedsBackLambda( const boost::shared_ptr<SavedSeedsGUI> &gui )
	{
		this->gui = gui;
	}

	bool SavedSeedsGUI::SaveSeedsBackLambda::Apply( const boost::shared_ptr<Menu> &menu )
	{
		return gui->Back( menu );
	}

	SavedSeedsGUI::SeedItem::SeedItem( const std::wstring &name, const std::wstring &seed, const boost::shared_ptr<EzFont> &font ) : MenuItem( boost::shared_ptr<EzText>( 0 ) )
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<SavedSeedsGUI::SeedItem> SavedSeedsGUI::SeedItem::SeedItem_Construct( const std::wstring &name, const std::wstring &seed, const boost::shared_ptr<EzFont> &font )
	{
		MenuItem::MenuItem_Construct( boost::make_shared<EzText>( name, font ) );

		this->Name = name;
		this->Seed = seed;

		return boost::static_pointer_cast<SavedSeedsGUI::SeedItem>( shared_from_this() );
	}

	void SavedSeedsGUI::SeedItem::ToggleDeletion()
	{
		MarkedForDeletion = !MarkedForDeletion;

		// Make items marked for deletion semi-transparent.
		if ( MarkedForDeletion )
			MyText->Alpha = MySelectedText->Alpha = .3f;
		else
			MyText->Alpha = MySelectedText->Alpha = 1;
	}

	void SavedSeedsGUI::SeedItem::InitializeInstanceFields()
	{
		MarkedForDeletion = false;
	}

	SavedSeedsGUI::StartLevelProxy1::StartLevelProxy1( const boost::shared_ptr<SavedSeedsGUI> &ssGui, const std::wstring &_seed )
	{
		this->ssGui = ssGui;
		this->_seed = _seed;
	}

	void SavedSeedsGUI::StartLevelProxy1::Apply( const boost::shared_ptr<MenuItem> &_menu )
	{
		ssGui->StartLevel( _seed );
	}

	SavedSeedsGUI::OnAddHelper::OnAddHelper( const boost::shared_ptr<ScrollBar> &bar )
	{
		this->bar = bar;
	}

	bool SavedSeedsGUI::OnAddHelper::Apply()
	{
#if defined(WINDOWS)
		return bar->MyMenu->HitTest();
#else
		return false;
#endif
	}

	SavedSeedsGUI::SavedSeedsGUI() { }
	boost::shared_ptr<SavedSeedsGUI> SavedSeedsGUI::SavedSeedsGUI_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		EnableBounce();

		return boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() );
	}

	void SavedSeedsGUI::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
	}

	void SavedSeedsGUI::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void SavedSeedsGUI::StartLevel( const std::wstring &seedstr )
	{
		LoadSeed( seedstr, boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	boost::shared_ptr<CustomLevel_GUI> SavedSeedsGUI::FreeplayMenu = 0;

	void SavedSeedsGUI::LoadSeed( const std::wstring &seedstr, const boost::shared_ptr<GUI_Panel> &panel )
	{
		// If the current panel or parent panel is the Freeplay menu,
		// then directly start the level.
		FreeplayMenu = boost::dynamic_pointer_cast<CustomLevel_GUI>( panel->Caller );
		if ( FreeplayMenu == 0 )
			FreeplayMenu = boost::dynamic_pointer_cast<CustomLevel_GUI>( panel );
		if ( 0 != FreeplayMenu )
		{
			LoadFromFreeplayMenu( seedstr, FreeplayMenu );
		}
		else
		{
			// Otherwise, if the parent game is Freeplay, then queue Freeplay to load the level.
			if ( boost::dynamic_pointer_cast<TitleGameData>( Tools::CurGameData->ParentGame ) != 0 )
			{
				Tools::CurrentAftermath = boost::make_shared<AftermathData>();
				Tools::CurrentAftermath->Success = false;
				Tools::CurrentAftermath->EarlyExit = true;

				CustomLevel_GUI::SeedStringToLoad = seedstr;
				Tools::CurGameData->EndGame->Apply( false );
			}
			else
				CustomLevel_GUI::SeedStringToLoad = seedstr;

	//#if defined(DEBUG)
	//                // otherwise, hard load the game, and forget about how it connects to anything else.
	//                // This will cause crashes if you try to exit the game afterwards, but is fine for testing purposes.
	//                else
	//                {
	//                    GameData.LockLevelStart = false;
	//                    LevelSeedData.ForcedReturnEarly = 0;

	//                    LevelSeedData data = new LevelSeedData();
	//                    data.ReadString(seedstr);
	//                    GameData.StartLevel(data);
	//                }
	//#endif
		}
	}

	void SavedSeedsGUI::LoadFromFreeplayMenu( const std::wstring &seedstr, const boost::shared_ptr<CustomLevel_GUI> &simple )
	{
		boost::shared_ptr<LevelSeedData> seed = boost::make_shared<LevelSeedData>();
		seed->ReadString( seedstr );
		seed->PostMake->Add( boost::make_shared<PostMakeStandardLoadHelper>( seed ) );

		simple->MyGame->PlayGame( boost::make_shared<LoadFromFreeplayMenuHelper>( seed, seedstr, simple ) );

	}

	int SavedSeedsGUI::NumSeedsToDelete()
	{
		int count = 0;
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<SeedItem> seeditem = boost::dynamic_pointer_cast<SeedItem>( *item );
			if ( 0 != seeditem && seeditem->MarkedForDeletion )
				count++;
		}

		return count;
	}

	bool SavedSeedsGUI::Delete( const boost::shared_ptr<Menu> &_menu )
	{
		if ( !Active )
			return true;

		boost::shared_ptr<SeedItem> seeditem = boost::dynamic_pointer_cast<SeedItem>( MyMenu->getCurItem() );
		if ( 0 != seeditem )
			seeditem->ToggleDeletion();

		return true;
	}

	void SavedSeedsGUI::DoDeletion( bool choice )
	{
		Active = false;

		// If "No", do not delete any seeds.
		if ( !choice )
		{
			MyGame->WaitThenDo( 10, boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) ) );
			return;
		}

		// Delete all saved seeds.
		player->MySavedSeeds->SeedStrings.clear();

		// Save seeds not marked for deletion.
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<SeedItem> seeditem = boost::dynamic_pointer_cast<SeedItem>( *item );
			if ( 0 == seeditem )
				continue;
			if ( seeditem->MarkedForDeletion )
				continue;

			player->MySavedSeeds->SeedStrings.push_back( seeditem->Seed );
		}

		SaveGroup::SaveAll();

		MyGame->WaitThenDo( 10, boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) ) );
	}

	void SavedSeedsGUI::Sort()
	{
		if ( !Active )
			return;
	}

	void SavedSeedsGUI::Init()
	{
		CkBaseMenu::Init();

		setControl( -1 );
		MyPile = boost::make_shared<DrawPile>();

		// Get the activating player
		player = MenuItem::GetActivatingPlayerData();

		// Set slide in and out parameters
		ReturnToCallerDelay = 6;
		SlideInFrom = PresetPos_RIGHT;
		SlideOutTo = PresetPos_RIGHT;
		SlideInLength = 25;
		SlideOutLength = 20;

		// Make the menu
		//MyMenu = new Menu(false);
		MyMenu = boost::make_shared<LongMenu>();
		MyMenu->FixedToCamera = false;
		MyMenu->WrapSelect = false;
		( boost::static_pointer_cast<LongMenu>( MyMenu ) )->OffsetStep = 30;
		EnsureFancy();
		MyMenu->OnA.reset();
		MyMenu->OnB = boost::make_shared<SaveSeedsBackLambda>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) );
		MyMenu->OnX = boost::make_shared<SaveSeedsDeleteLambda>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) );
		MyMenu->OnY = boost::make_shared<SortProxy>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) );
		MyMenu->SelectDelay = 11;

		ItemPos = Vector2( 80.5547f, 756.1112f );
		PosAdd = Vector2( 0, -120 );

		FontScale = .666f;

		// Header
		boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SaveSeed, ItemFont ) ) );
		item->Name = std::wstring( L"Header" );
		item->Selectable = false;
		SetHeaderProperties( item->MySelectedText );
		AddItem( item );

	#if defined(PC_VERSION)
		Vector2 SavePos = ItemPos;
		MakeBackButton()->UnaffectedByScroll = true;
		ItemPos = SavePos;
	#endif

		MakeOptions();
		MakeList();

	#if !defined(PC_VERSION)
		OptionalBackButton();
	#endif

		// Backdrop
		boost::shared_ptr<QuadClass> backdrop;
        if (UseBounce)
            backdrop = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 1500.f, true);
        else
            backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1500x900" ), 1500.f, true);

		backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( backdrop );

		SetPos();
	#if defined(PC_VERSION)
		MyMenu->SelectItem( 2 );
	#else
		MyMenu->SelectItem( 0 );
	#endif
	}

	void SavedSeedsGUI::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
	#if defined(WINDOWS)
		if ( ButtonCheck::State( Keys_Delete ).Pressed )
			Delete( MyMenu );
	#endif
	}

	bool SavedSeedsGUI::Back( const boost::shared_ptr<Menu> &menu )
	{
		if ( !Active )
			return true;

		int num = NumSeedsToDelete();
		if ( num > 0 )
		{
			boost::shared_ptr<VerifyDeleteSeeds> verify = MakeMagic( VerifyDeleteSeeds, ( getControl(), num ) );
			verify->OnSelect->Add( boost::make_shared<DoDeletionProxy>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ) ) );

			Call( verify, 0 );
		}
		else
			ReturnToCaller();

		return true;
	}

	void SavedSeedsGUI::OnReturnTo()
	{
		Hid = false;
		CkBaseMenu::OnReturnTo();
	}

	void SavedSeedsGUI::OptionalBackButton()
	{
		// Make a back button if there is no saved seeds.
		if ( player->MySavedSeeds->SeedStrings.empty() )
			MakeBackButton();
	}

	void SavedSeedsGUI::SetPos()
	{
	#if defined(PC_VERSION)
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Header" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 27.77808f, 925.0002f ) );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 278.9676f, 937.6984f ) );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"castle_testsave" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 80.5547f, 516.1112f ) );
		}

		MyMenu->setPos( Vector2( -1016.667f, 0 ) );

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 2.77771f, 22.22221f ) );
			_q->setSize( Vector2( 1572.44f, 1572.44f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	#else
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Header" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 27.77808f, 925.0002f ) );
		}

		MyMenu->setPos( Vector2( -1016.667f, 0 ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"Load" ) );
		if ( _t != 0 )
			_t->setPos( Vector2( 564.6826f, -51.11127f ) );
		_t = MyPile->FindEzText( std::wstring( L"Delete" ) );
		if ( _t != 0 )
			_t->setPos( Vector2( 570.572f, -309.3967f ) );
		_t = MyPile->FindEzText( std::wstring( L"Back" ) );
		if ( _t != 0 )
			_t->setPos( Vector2( 579.6982f, -569.7302f ) );

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 2.77771f, 22.22221f ) );
			_q->setSize( Vector2( 1572.44f, 1572.44f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	#endif
	}

	void SavedSeedsGUI::MakeList()
	{
		for ( std::vector<std::wstring>::const_iterator seed = player->MySavedSeeds->SeedStrings.begin(); seed != player->MySavedSeeds->SeedStrings.end(); ++seed )
		{
			std::wstring _seed = *seed;
			std::wstring name = LevelSeedData::GetNameFromSeedStr( *seed );

			// Get name of seed
			boost::shared_ptr<MenuItem> seeditem = MakeMagic( SeedItem, ( name, *seed, ItemFont ) );
			seeditem->setGo( boost::make_shared<StartLevelProxy1>( boost::static_pointer_cast<SavedSeedsGUI>( shared_from_this() ), _seed ) );
			AddItem( seeditem );
		}
	}

	void SavedSeedsGUI::OnAdd()
	{
		CkBaseMenu::OnAdd();

		// Scroll bar
	#if defined(WINDOWS)
	//#if PC_VERSION
		//if (false)
		{
			bar = MakeMagic( ScrollBar, ( boost::static_pointer_cast<LongMenu>( MyMenu ), boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
			bar->setBarPos( Vector2( -1860, 102.7778f ) );
			MyGame->AddGameObject( bar );
	#if defined(PC_VERSION)
			MyMenu->AdditionalCheckForOutsideClick = boost::make_shared<OnAddHelper>( bar );
	#endif
		}
	#endif
	}

	void SavedSeedsGUI::MakeOptions()
	{
		FontScale *= .8f;

	#if defined(PC_VERSION)
		boost::shared_ptr<MenuItem> item;
		//// Load
		//item = new MenuItem(new EzText("Load", ItemFont));
		//item.Name = "Load";
		//AddItem(item);
		//item.SelectSound = null;
		//item.Go = ItemReturnToCaller;
		//item.MyText.MyFloatColor = Menu.DefaultMenuInfo.UnselectedBackColor;
		//item.MySelectedText.MyFloatColor = Menu.DefaultMenuInfo.SelectedBackColor;

		//// Delete
		//item = new MenuItem(new EzText("Delete", ItemFont));
		//item.Name = "Delete";
		//AddItem(item);
		//item.SelectSound = null;
		//item.Go = ItemReturnToCaller;
		//item.MyText.MyFloatColor = new Color(204, 220, 255).ToVector4();
		//item.MySelectedText.MyFloatColor = new Color(204, 220, 255).ToVector4();

		//// Back
		//item = new MenuItem(new EzText("Back", ItemFont));
		//item.Name = "Back";
		//AddItem(item);
		//item.SelectSound = null;
		//item.Go = ItemReturnToCaller;
		//item.MyText.MyFloatColor = Menu.DefaultMenuInfo.UnselectedBackColor;
		//item.MySelectedText.MyFloatColor = Menu.DefaultMenuInfo.SelectedBackColor;
	#else
		float scale = .75f;

		boost::shared_ptr<EzText> text;
		text = boost::make_shared<EzText>( ButtonString::Go( 90 ) + std::wstring( L" Load" ), ItemFont );
		text->Name = std::wstring( L"Load" );
		text->setScale( text->getScale() * scale );
		text->setPos( Vector2( 417.4604f, -159.4446f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		MyPile->Add( text );

		text = boost::make_shared<EzText>( ButtonString::X( 90 ) + std::wstring( L" Delete" ), ItemFont );
		text->Name = std::wstring( L"Delete" );
		text->setScale( text->getScale() * scale );
		text->setPos( Vector2( 531.6831f, -389.9523f ) );
		text->MyFloatColor = ( Color( static_cast<unsigned char>( 204 ), static_cast<unsigned char>( 220 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		MyPile->Add( text );

		text = boost::make_shared<EzText>( ButtonString::Back( 90 ) + std::wstring( L" Back" ), ItemFont );
		text->Name = std::wstring( L"Back" );
		text->setScale( text->getScale() * scale );
		text->setPos( Vector2( 682.4761f, -622.5079f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		MyPile->Add( text );
	#endif
	}
}
