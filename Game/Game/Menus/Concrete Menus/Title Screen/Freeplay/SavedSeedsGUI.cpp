#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	SavedSeedsGUI::PostMakeStandardLoadHelper::PostMakeStandardLoadHelper( const std::shared_ptr<LevelSeedData> &seed )
	{
		this->seed = seed;
	}

	void SavedSeedsGUI::PostMakeStandardLoadHelper::Apply( const std::shared_ptr<Level> &level )
	{
		seed->PostMake_StandardLoad( level );
	}

	SavedSeedsGUI::LoadFromFreeplayMenuHelper::LoadFromFreeplayMenuHelper( const std::shared_ptr<LevelSeedData> &seed, const std::wstring &seedstr, const std::shared_ptr<CustomLevel_GUI> &simple )
	{
		this->seed = seed;
		this->seedstr = seedstr;
		this->simple = simple;
	}

	void SavedSeedsGUI::LoadFromFreeplayMenuHelper::Apply()
	{
		simple->StartLevel( seed );

		// Randomize the seed for the next level, if the player chooses to continue using this LevelSeedData.
		seed = std::make_shared<LevelSeedData>();
		seed->ReadString( seedstr );
		seed->PostMake->Add( std::make_shared<PostMakeStandardLoadHelper>( seed ) );
		seed->setSeed( Tools::GlobalRnd->Rnd->Next() );
	}

	SavedSeedsGUI::SaveSeedsDeleteLambda::SaveSeedsDeleteLambda( const std::shared_ptr<SavedSeedsGUI> &gui )
	{
		this->gui = gui;
	}

	bool SavedSeedsGUI::SaveSeedsDeleteLambda::Apply( const std::shared_ptr<Menu> &menu )
	{
		return gui->Delete( menu );
	}

	SavedSeedsGUI::ReturnToCallerProxy::ReturnToCallerProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::ReturnToCallerProxy::Apply()
	{
		ssGui->ReturnToCaller();
	}

	SavedSeedsGUI::DoDeletionProxy::DoDeletionProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::DoDeletionProxy::Apply( bool choice )
	{
		ssGui->DoDeletion( choice );
	}

	SavedSeedsGUI::SortProxy::SortProxy( const std::shared_ptr<SavedSeedsGUI> &ssGui )
	{
		this->ssGui = ssGui;
	}

	void SavedSeedsGUI::SortProxy::Apply()
	{
		ssGui->Sort();
	}

	SavedSeedsGUI::SaveSeedsBackLambda::SaveSeedsBackLambda( const std::shared_ptr<SavedSeedsGUI> &gui )
	{
		this->gui = gui;
	}

	bool SavedSeedsGUI::SaveSeedsBackLambda::Apply( const std::shared_ptr<Menu> &menu )
	{
		return gui->Back( menu );
	}

	SavedSeedsGUI::SeedItem::SeedItem( const std::wstring &name, const std::wstring &seed, const std::shared_ptr<EzFont> &font ) : MenuItem( std::make_shared<EzText>( name, font ) )
	{
		InitializeInstanceFields();
		this->Name = name;
		this->Seed = seed;
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

	SavedSeedsGUI::StartLevelProxy1::StartLevelProxy1( const std::shared_ptr<SavedSeedsGUI> &ssGui, const std::wstring &_seed )
	{
		this->ssGui = ssGui;
		this->_seed = _seed;
	}

	void SavedSeedsGUI::StartLevelProxy1::Apply( const std::shared_ptr<MenuItem> &_menu )
	{
		ssGui->StartLevel( _seed );
	}

	SavedSeedsGUI::OnAddHelper::OnAddHelper( const std::shared_ptr<ScrollBar> &bar )
	{
		this->bar = bar;
	}

	bool SavedSeedsGUI::OnAddHelper::Apply()
	{
		return bar->MyMenu->HitTest();
	}

	SavedSeedsGUI::SavedSeedsGUI()
	{
	}

	void SavedSeedsGUI::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
	}

	void SavedSeedsGUI::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void SavedSeedsGUI::StartLevel( const std::wstring &seedstr )
	{
		LoadSeed( seedstr, this );
	}

std::shared_ptr<CustomLevel_GUI> SavedSeedsGUI::FreeplayMenu = 0;

	void SavedSeedsGUI::LoadSeed( const std::wstring &seedstr, const std::shared_ptr<GUI_Panel> &panel )
	{
		// If the current panel or parent panel is the Freeplay menu,
		// then directly start the level.
		FreeplayMenu = dynamic_cast<CustomLevel_GUI*>( panel->Caller );
		if ( FreeplayMenu == 0 )
			FreeplayMenu = dynamic_cast<CustomLevel_GUI*>( panel );
		if ( 0 != FreeplayMenu )
		{
			LoadFromFreeplayMenu( seedstr, FreeplayMenu );
		}
		else
		{
			// Otherwise, if the parent game is Freeplay, then queue Freeplay to load the level.
			if ( dynamic_cast<TitleGameData*>( Tools::CurGameData->ParentGame ) != 0 )
			{
				Tools::CurrentAftermath = std::make_shared<AftermathData>();
				Tools::CurrentAftermath->Success = false;
				Tools::CurrentAftermath->EarlyExit = true;

				CustomLevel_GUI::SeedStringToLoad = seedstr;
				Tools::CurGameData->EndGame->Apply( false );
			}
			else
				CustomLevel_GUI::SeedStringToLoad = seedstr;

	//#if DEBUG
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

	void SavedSeedsGUI::LoadFromFreeplayMenu( const std::wstring &seedstr, const std::shared_ptr<CustomLevel_GUI> &simple )
	{
		std::shared_ptr<LevelSeedData> seed = std::make_shared<LevelSeedData>();
		seed->ReadString( seedstr );
		seed->PostMake->Add( std::make_shared<PostMakeStandardLoadHelper>( seed ) );

		simple->MyGame->PlayGame( std::make_shared<LoadFromFreeplayMenuHelper>( seed, seedstr, simple ) );

	}

	int SavedSeedsGUI::NumSeedsToDelete()
	{
		int count = 0;
		for ( std::vector<MenuItem*>::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			std::shared_ptr<SeedItem> seeditem = dynamic_cast<SeedItem*>( *item );
			if ( 0 != seeditem && seeditem->MarkedForDeletion )
				count++;
		}

		return count;
	}

	bool SavedSeedsGUI::Delete( const std::shared_ptr<Menu> &_menu )
	{
		if ( !Active )
			return true;

		std::shared_ptr<SeedItem> seeditem = dynamic_cast<SeedItem*>( MyMenu->getCurItem() );
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
			MyGame->WaitThenDo( 10, std::make_shared<ReturnToCallerProxy>( this ) );
			return;
		}

		// Delete all saved seeds.
		player->MySavedSeeds->SeedStrings.clear();

		// Save seeds not marked for deletion.
		for ( std::vector<MenuItem*>::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			std::shared_ptr<SeedItem> seeditem = dynamic_cast<SeedItem*>( *item );
			if ( 0 == seeditem )
				continue;
			if ( seeditem->MarkedForDeletion )
				continue;

			player->MySavedSeeds->SeedStrings.push_back( seeditem->Seed );
		}

		SaveGroup::SaveAll();

		MyGame->WaitThenDo( 10, std::make_shared<ReturnToCallerProxy>( this ) );
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
		MyPile = std::make_shared<DrawPile>();

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
		MyMenu = std::make_shared<LongMenu>();
		MyMenu->FixedToCamera = false;
		MyMenu->WrapSelect = false;
		( static_cast<LongMenu*>( MyMenu ) )->OffsetStep = 30;
		EnsureFancy();
		MyMenu->OnA.reset();
		MyMenu->OnB = std::make_shared<SaveSeedsBackLambda>( this );
		MyMenu->OnX = std::make_shared<SaveSeedsDeleteLambda>( this );
		MyMenu->OnY = std::make_shared<SortProxy>( this );
		MyMenu->SelectDelay = 11;

		ItemPos = Vector2( 80.5547f, 756.1112f );
		PosAdd = Vector2( 0, -120 );

		FontScale = .666f;

		// Header
		std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_SAVE_SEED, ItemFont ) );
		item->Name = _T( "Header" );
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
		std::shared_ptr<QuadClass> backdrop;

		backdrop = std::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 1500, true );
		backdrop->Name = _T( "Backdrop" );
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
		if ( ButtonCheck::State( Microsoft::Xna::Framework::Input::Keys::Delete ).Pressed )
			Delete( MyMenu );
	#endif
	}

	bool SavedSeedsGUI::Back( const std::shared_ptr<Menu> &menu )
	{
		if ( !Active )
			return true;

		int num = NumSeedsToDelete();
		if ( num > 0 )
		{
			std::shared_ptr<VerifyDeleteSeeds> verify = std::make_shared<VerifyDeleteSeeds>( getControl(), num );
			verify->OnSelect->Add( std::make_shared<DoDeletionProxy>( this ) );

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
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Header" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 27.77808f, 925.0002f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 278.9676f, 937.6984f ) );
		}
		_item = MyMenu->FindItemByName( _T( "castle_testsave" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 80.5547f, 516.1112f ) );
		}

		MyMenu->setPos( Vector2( -1016.667f, 0 ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 2.77771f, 22.22221f ) );
			_q->setSize( Vector2( 1572.44f, 1572.44f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	#else
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Header" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 27.77808f, 925.0002f ) );
		}

		MyMenu->setPos( Vector2( -1016.667f, 0 ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Load" ) );
		if ( _t != 0 )
			_t->setPos( Vector2( 564.6826f, -51.11127f ) );
		_t = MyPile->FindEzText( _T( "Delete" ) );
		if ( _t != 0 )
			_t->setPos( Vector2( 570.572f, -309.3967f ) );
		_t = MyPile->FindEzText( _T( "Back" ) );
		if ( _t != 0 )
			_t->setPos( Vector2( 579.6982f, -569.7302f ) );

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
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
			std::shared_ptr<MenuItem> seeditem = std::make_shared<SeedItem>( name, *seed, ItemFont );
			seeditem->setGo( std::make_shared<StartLevelProxy1>( this, _seed ) );
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
			bar = std::make_shared<ScrollBar>( static_cast<LongMenu*>( MyMenu ), this );
			bar->setBarPos( Vector2( -1860, 102.7778f ) );
			MyGame->AddGameObject( bar );
	#if defined(PC_VERSION)
			MyMenu->AdditionalCheckForOutsideClick = std::make_shared<OnAddHelper>( bar );
	#endif
		}
	#endif
	}

	void SavedSeedsGUI::MakeOptions()
	{
		FontScale *= .8f;

	#if defined(PC_VERSION)
		std::shared_ptr<MenuItem> item;
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

		std::shared_ptr<EzText> text;
		text = std::make_shared<EzText>( ButtonString::Go( 90 ) + _T( " Load" ), ItemFont );
		text->Name = _T( "Load" );
		text->setScale( text->getScale() * scale );
		text->setPos( Vector2( 417.4604f, -159.4446f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		MyPile->Add( text );

		text = std::make_shared<EzText>( ButtonString::X( 90 ) + _T( " Delete" ), ItemFont );
		text->Name = _T( "Delete" );
		text->setScale( text->getScale() * scale );
		text->setPos( Vector2( 531.6831f, -389.9523f ) );
		text->MyFloatColor = ( Color( 204, 220, 255 ) ).ToVector4();
		MyPile->Add( text );

		text = std::make_shared<EzText>( ButtonString::Back( 90 ) + _T( " Back" ), ItemFont );
		text->Name = _T( "Back" );
		text->setScale( text->getScale() * scale );
		text->setPos( Vector2( 682.4761f, -622.5079f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		MyPile->Add( text );
	#endif
	}
}
