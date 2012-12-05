#include <global_header.h>


namespace CloudberryKingdom
{

	CustomLevel_GUI::StartLevelFromMenDataStandardLoadProxy::StartLevelFromMenDataStandardLoadProxy( const std::shared_ptr<LevelSeedData> &data )
	{
		this->data = data;
	}

	void CustomLevel_GUI::StartLevelFromMenDataStandardLoadProxy::Apply( const std::shared_ptr<Level> &level )
	{
		data->PostMake_StandardLoad( level );
	}

	CustomLevel_GUI::StartLevelFromMenuDataInitializeHelper::StartLevelFromMenuDataInitializeHelper( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::StartLevelFromMenuDataInitializeHelper::Apply( const std::shared_ptr<PieceSeedData> &piece )
	{
		piece->CopyUpgrades( clGui->PieceSeed );

		piece->StandardClose();
	}

	CustomLevel_GUI::StartLevelEnableLoadProxy::StartLevelEnableLoadProxy( const std::shared_ptr<LevelSeedData> &data )
	{
		this->data = data;
	}

	void CustomLevel_GUI::StartLevelEnableLoadProxy::Apply( const std::shared_ptr<Level> &level )
	{
		data->PostMake_EnableLoad( level );
	}

	CustomLevel_GUI::OnReturnFromLevelProxy::OnReturnFromLevelProxy( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::OnReturnFromLevelProxy::Apply()
	{
		clGui->OnReturnFromLevel();
	}

	CustomLevel_GUI::InitOnSetValueHelper::InitOnSetValueHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length )
	{
		this->clGui = clGui;
		this->length = length;
	}

	void CustomLevel_GUI::InitOnSetValueHelper::Apply()
	{
		clGui->LevelSeed->Length = static_cast<int>( length->getMyFloat()->getVal() );
		switch ( clGui->LevelSeed->NumPieces )
		{
			case 1:
				clGui->LevelSeed->PieceLength = static_cast<int>( length->getMyFloat()->getVal() );
				break;
			case 2:
				clGui->LevelSeed->PieceLength = static_cast<int>( length->getMyFloat()->getVal() *.7f );
				break;
			case 3:
				clGui->LevelSeed->PieceLength = static_cast<int>( length->getMyFloat()->getVal() *.5f );
				break;
			case 4:
				clGui->LevelSeed->PieceLength = static_cast<int>( length->getMyFloat()->getVal() *.4f );
				break;

			default:
				clGui->LevelSeed->PieceLength = static_cast<int>( length->getMyFloat()->getVal() / clGui->LevelSeed->NumPieces );
				break;
		}
	}

	CustomLevel_GUI::InitOnSlideHelper::InitOnSlideHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length )
	{
		this->clGui = clGui;
		this->length = length;
	}

	void CustomLevel_GUI::InitOnSlideHelper::Apply()
	{
		clGui->DesiredLength = length->getMyFloat()->getVal();

		int MaxCheckpoints = __min( 4, static_cast<int>( length->getMyFloat()->getPercent() / 20 ) );

		float currentcheckpoints = clGui->checkpoints->MyFloat->Val;
		currentcheckpoints = __max( currentcheckpoints, clGui->DesiredNumCheckpoints );
		currentcheckpoints = __min( currentcheckpoints, MaxCheckpoints );
		clGui->checkpoints->MyFloat->Val = currentcheckpoints;
	}

	CustomLevel_GUI::InitOnSlideHelper2::InitOnSlideHelper2( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length )
	{
		this->clGui = clGui;
		this->length = length;
	}

	void CustomLevel_GUI::InitOnSlideHelper2::Apply()
	{
		clGui->DesiredNumCheckpoints = static_cast<int>( clGui->checkpoints->MyFloat->Val );

		float MinLength = ( .11f + .2f * ( clGui->checkpoints->MyFloat->Val + 1 ) ) * length->getMyFloat()->getSpread();
		length->getMyFloat()->setVal(__min(length->getMyFloat()->getVal(), clGui->DesiredLength));
		length->getMyFloat()->setVal(__max(length->getMyFloat()->getVal(), MinLength));
	}

	CustomLevel_GUI::InitOnSetValueHelper2::InitOnSetValueHelper2( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<LengthSlider> &length )
	{
		this->clGui = clGui;
		this->length = length;
	}

	void CustomLevel_GUI::InitOnSetValueHelper2::Apply()
	{
		int PrevNumPieces = clGui->LevelSeed->NumPieces;

		clGui->LevelSeed->NumPieces = 1 + static_cast<int>( clGui->checkpoints->MyFloat->Val );
		length->setVal( clGui->LevelSeed->Length );

		if ( PrevNumPieces != clGui->LevelSeed->NumPieces )
			clGui->MiniCheckpoint->SetScale( .01f );
	}

	CustomLevel_GUI::InitOnAStartHelper::InitOnAStartHelper( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	bool CustomLevel_GUI::InitOnAStartHelper::Apply( const std::shared_ptr<Menu> &dummy )
	{
		clGui->Start->getGo()->Apply( 0 );
		return true;
	}

	CustomLevel_GUI::InitOnIndexSelectHelper::InitOnIndexSelectHelper( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<MenuList> &LocationList )
	{
		this->clGui = clGui;
		this->LocationList = LocationList;
	}

	void CustomLevel_GUI::InitOnIndexSelectHelper::Apply()
	{
		std::shared_ptr<TileSet> tileset = std::dynamic_pointer_cast<TileSet>( LocationList->getCurObj() );

		//Vector2 HoldRelativeSize = Screenshot.GetTextureScaling();
		//Screenshot.TextureName = tileset.ScreenshotString;
		//Screenshot.ScaleYToMatchRatio(HoldRelativeSize.X * Screenshot.Quad.MyTexture.Width);

		clGui->LevelSeed->SetTileSet( tileset );
	}

	CustomLevel_GUI::InitOnIndexSelect::InitOnIndexSelect( const std::shared_ptr<CustomLevel_GUI> &clGui, const std::shared_ptr<MenuList> &GameList )
	{
		this->clGui = clGui;
		this->GameList = GameList;
	}

	void CustomLevel_GUI::InitOnIndexSelect::Apply()
	{
		clGui->LevelSeed->MyGameFlags.SetToDefault();

		Localization::Words gamename = static_cast<Localization::Words>( GameList->getCurObj() );
		if ( gamename == Localization::Words_CLASSIC_GAME )
		{
			clGui->LevelSeed->MyGameType = NormalGameData::Factory;
			clGui->LevelSeed->MyGeometry = LevelGeometry_RIGHT;
			clGui->SelectNormal();
		}
		else if ( gamename == Localization::Words_BUNGEE )
		{
			clGui->LevelSeed->MyGameType = NormalGameData::Factory;
			clGui->LevelSeed->MyGeometry = LevelGeometry_RIGHT;
			clGui->LevelSeed->MyGameFlags.IsTethered = true;
			clGui->SelectBungee();
		}
		//else if (gamename.CompareTo("Up Level") == 0)
		//{
		//    SelectUpLevel();
		//}
		//else if (gamename.CompareTo("Down Level") == 0)
		//{
		//    SelectDownLevel();
		//}
		else if ( gamename == Localization::Words_WALL_LEVEL )
		{
			clGui->LevelSeed->MyGameType = NormalGameData::Factory;
			clGui->LevelSeed->MyGeometry = LevelGeometry_RIGHT;
			clGui->SelectNormal();
			clGui->ShowHeros( true );
			clGui->ShowCheckpoints( false );
			clGui->HasWall = true;
		}
	}

	CustomLevel_GUI::DiffList_OnIndexProxy::DiffList_OnIndexProxy( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::DiffList_OnIndexProxy::Apply()
	{
		clGui->DiffList_OnIndex();
	}

	CustomLevel_GUI::HeroList_OnIndexProxy::HeroList_OnIndexProxy( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::HeroList_OnIndexProxy::Apply()
	{
		clGui->HeroList_OnIndex();
	}

	CustomLevel_GUI::BringNextProxy::BringNextProxy( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::BringNextProxy::Apply()
	{
		clGui->BringNext();
	}

	CustomLevel_GUI::BringLoadProxy::BringLoadProxy( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::BringLoadProxy::Apply()
	{
		clGui->BringLoad();
	}

	CustomLevel_GUI::BringLoadProxy1::BringLoadProxy1( const std::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::BringLoadProxy1::Apply( const std::shared_ptr<MenuItem> &dummy )
	{
		clGui->BringLoad();
	}

std::vector<std::shared_ptr<TileSet> > CustomLevel_GUI::FreeplayTilesets = std::vector<std::shared_ptr<TileSet> >();
std::vector<std::shared_ptr<BobPhsx> > CustomLevel_GUI::FreeplayHeroes = std::vector<std::shared_ptr<BobPhsx> >();
bool CustomLevel_GUI::IsMaxLength = false;
int CustomLevel_GUI::Difficulty = 0;
Localization::Words CustomLevel_GUI::CustomHeroString = Localization::Words_FACTORY;

	CustomLevel_GUI::CustomLevel_GUI()
	{
		InitializeInstanceFields();
		BobPhsx::CustomPhsxData::InitBounds();

		CustomHero_GUI::HeroPhsxData = BobPhsx::CustomPhsxData();
		CustomHero_GUI::HeroPhsxData.Init();

		NoBackIfNoCaller = true;

		SeedStringToLoad = _T( "" );
		ExitFreeplay = false;
	}

	void CustomLevel_GUI::StartLevelFromMenuData()
	{
		std::shared_ptr<LevelSeedData> data = std::make_shared<LevelSeedData>( LevelSeed );
		data->setSeed( Tools::GlobalRnd->Rnd->Next() );

		// Debug: set hero type
		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Spaceship, Hero_Shape.Small, Hero_MoveMod.Classic);

		// Vertical levels have no checkpoints
		if ( LevelSeed->MyGeometry != LevelGeometry_RIGHT )
			LevelSeed->NumPieces = 1;

		// Copy Upgrade1 to Upgrade2
		PieceSeed->MyUpgrades1->UpgradeLevels.CopyTo( PieceSeed->MyUpgrades2->UpgradeLevels, 0 );

		// Custom difficulty
		if ( IsCustomDifficulty() )
		{
			data->Initialize( std::make_shared<StartLevelFromMenuDataInitializeHelper>( shared_from_this() ) );
		}
		// Preset difficulty
		else
		{
			std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > custom;

			custom = DifficultyGroups::FixedPieceMod( DiffList->ListIndex - 1, data );

			data->Initialize( custom );
		}

		// Wall
		if ( HasWall )
			data->HasWall = true;

		data->ProcessSpecial();

		// Dark bottom
		if ( data->MyGeometry == LevelGeometry_DOWN )
			data->PieceSeeds[ 0 ]->Style->MyFinalPlatsType = StyleData::FinalPlatsType_DARK_BOTTOM;

		data->PostMake->Add( std::make_shared<StartLevelFromMenDataStandardLoadProxy>( data ) );

		StartLevel( data );
	}

	void CustomLevel_GUI::StartLevel( const std::shared_ptr<LevelSeedData> &data )
	{
		data->PostMake->Add( std::make_shared<StartLevelEnableLoadProxy>( data ) );

		PlayerManager::setCoinsSpent( -999 );

		std::shared_ptr<GameData> game = data->Create();
		game->ParentGame = MyGame;
		game->Freeplay = true;
		game->DefaultHeroType = data->DefaultHeroType;
		Difficulty = DiffList->ListIndex - 1;
		IsMaxLength = length->getIsMaxed();
	}

	void CustomLevel_GUI::OnAdd()
	{
		CkBaseMenu::OnAdd();

		MyGame->ClearPreviousLoadFunction();

		MyPile->setPos( MyPile->getPos() + RightPanelCenter );
		MyMenu->FancyPos->RelVal += RightPanelCenter;

		// Register for when the created level ends
		MyGame->OnReturnTo->Add( std::make_shared<OnReturnFromLevelProxy>( shared_from_this() ) );

		SetPos();
	}

	void CustomLevel_GUI::ReleaseBody()
	{
		// Unregister 
		//MyGame.OnReturnTo -= OnReturnFromLevel;

		CkBaseMenu::ReleaseBody();
	}

	void CustomLevel_GUI::OnReturnFromLevel()
	{
		if ( ExitFreeplay )
		{
			if ( CallingPanel != 0 )
			{
				SlideOut( PresetPos_LEFT );
				CallingPanel->SlideOut( PresetPos_LEFT );
				CallingPanel->ReleaseWhenDone = true;
			}

			MenuReturnToCaller( MyMenu );
			MyGame->PhsxStepsToDo += 20;
			ExitFreeplay = false;
			return;
		}

		// If we started the level from the basic menu
		if ( CallingPanel == 0 )
		{
			if ( Active )
			{
				SlideOut( PresetPos_RIGHT, 0 );
				SlideIn();
			}
		}
		// If we started the level from the obstacle upgrade menu
		else
		{
			SlideOut( PresetPos_RIGHT, 0 );
			CallingPanel->SlideOut( PresetPos_RIGHT, 0 );
			CallingPanel->SlideIn();
			Active = false;
		}
	}

	void CustomLevel_GUI::AnyHero()
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<std::shared_ptr<MenuItem> >::const_iterator item = HeroList->MyList.begin(); item != HeroList->MyList.end(); ++item )
			( *item )->Selectable = true;
	}

	void CustomLevel_GUI::UpHero_ModShown()
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<std::shared_ptr<MenuItem> >::const_iterator item = HeroList->MyList.begin(); item != HeroList->MyList.end(); ++item )
		{
			if ( std::dynamic_pointer_cast<BobPhsxSpaceship>( ( *item )->MyObject ) != 0 || std::dynamic_pointer_cast<BobPhsxRocketbox>( ( *item )->MyObject ) != 0 )
				( *item )->Selectable = false;
			else
				( *item )->Selectable = true;
		}
	}

	void CustomLevel_GUI::UpHero_NoSpaceship()
	{
		if ( LevelSeed->DefaultHeroType == BobPhsxSpaceship::getInstance() || LevelSeed->DefaultHeroType == BobPhsxRocketbox::getInstance() )
		{
			int HoldIndex = DesiredHeroIndex;
			HeroList->SetIndex( 1 );
			if ( HeroList->Show )
				DesiredHeroIndex = HoldIndex;
		}
	}

	void CustomLevel_GUI::ShowHeros( bool Show )
	{
		HeroList->setInclude( Show );
		HeroText->Show = Show;

		if ( Show )
			HeroList->SetIndex( DesiredHeroIndex );
		else
		{
			int HoldIndex = DesiredHeroIndex;
			HeroList->SetIndex( 0 );
			DesiredHeroIndex = HoldIndex;
		}
	}

	void CustomLevel_GUI::ShowCheckpoints( bool Show )
	{
		if ( Show )
		{
			if ( !checkpoints->Show )
			{
				checkpoints->setVal( HoldNumCheckpoints );
				DesiredNumCheckpoints = HoldDesiredNumCheckpoints;
			}
		}
		else
		{
			HoldNumCheckpoints = checkpoints->getVal();
			HoldDesiredNumCheckpoints = DesiredNumCheckpoints;
			checkpoints->setVal( 0 );
			DesiredNumCheckpoints = 0;
		}

		checkpoints->Show = Show;
		CheckpointsText->Show = Show;
	}

	void CustomLevel_GUI::SelectNormal()
	{
		HasWall = false;

		AnyHero();
		ShowHeros( true );

		ShowCheckpoints( true );
	}

	void CustomLevel_GUI::SelectBuild()
	{
		HasWall = false;

		ShowHeros( false );
		ShowCheckpoints( true );
	}

	void CustomLevel_GUI::SelectBungee()
	{
		SelectNormal();
	}

	void CustomLevel_GUI::SelectSurvival()
	{
		SelectNormal();
		ShowCheckpoints( false );
	}

Vector2 CustomLevel_GUI::RightPanelCenter = Vector2( -285, 0 );

	void CustomLevel_GUI::Init()
	{
		ItemShadows = false;

		LevelSeed = std::make_shared<LevelSeedData>();
		PieceSeed = std::make_shared<PieceSeedData>( 0 );

		SlideInFrom = SlideOutTo = PresetPos_RIGHT;

		FontScale = .73f;

		MyPile = std::make_shared<DrawPile>();

		CkBaseMenu::Init();

		ReturnToCallerDelay = 18;
		SlideInLength = 25;
		SlideOutLength = 24;

		CallDelay = 5;


		SelectedItemShift = Vector2( 0, 0 );

		// Backdrop
		std::shared_ptr<QuadClass> backdrop;

		backdrop = std::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 1500, true );
		backdrop->Name = _T( "Backdrop" );
		MyPile->Add( backdrop );
		backdrop->setSize( Vector2( 1690.477f, 1115.617f ) );
		backdrop->setPos( Vector2( 287.6977f, 51.58758f ) );

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );

		setControl( -1 );

		MyMenu->OnB.reset();

		std::shared_ptr<MenuItem> item;

		// Location screenshot
		//QuadClass Screenshot = new QuadClass();
		//Screenshot.Name = "Screenshot";
		//Screenshot.SetToDefault();
		//Screenshot.TextureName = "Screenshot_Terrace";
		//Screenshot.ScaleYToMatchRatio(500);
		//MyPile.Add(Screenshot);
		//Screenshot.Pos = new Vector2(1340.002f, 497.2222f);
		//Screenshot.SetDefaultShadow(15);

		// Location
		std::shared_ptr<EzText> LocationText = std::make_shared<EzText>( Localization::Words_LOCATION, ItemFont );
		LocationText->Name = _T( "Location" );
		SetHeaderProperties( LocationText );
		MyPile->Add( LocationText );
		LocationText->setPos( Vector2( -1050.111f, 933 ) );

		std::shared_ptr<MenuList> LocationList = std::make_shared<MenuList>();
		LocationList->Name = _T( "Location" );
		LocationList->Center = !LeftJustify;
		LocationList->MyExpandPos = Vector2( -498.1506f, 713.873f );
		for ( std::vector<std::shared_ptr<TileSet> >::const_iterator tileset = FreeplayTilesets.begin(); tileset != FreeplayTilesets.end(); ++tileset )
		{
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( ( *tileset )->NameInGame, ItemFont, false, true ) );
			SetItemProperties( item );
			LocationList->AddItem( item, *tileset );
		}
		AddItem( LocationList );
		if ( LeftJustify )
			LocationList->Pos = Vector2( 200 + LeftJustifyAddX, 828 );
		else
			LocationList->Pos = Vector2( 200, 828 );
		LocationList->OnIndexSelect = std::make_shared<InitOnIndexSelectHelper>( shared_from_this(), LocationList );
		LocationList->SetIndex( 0 );

		// Game type
		std::shared_ptr<EzText> GameText = std::make_shared<EzText>( Localization::Words_GAME, ItemFont );
		GameText->Name = _T( "Game" );
		SetHeaderProperties( GameText );
		MyPile->Add( GameText );
		GameText->setPos( Vector2( -1061.11f, 933 - 222 ) );

		std::shared_ptr<MenuList> GameList = std::make_shared<MenuList>();
		GameList->Name = _T( "Game" );
		GameList->MyExpandPos = Vector2( -580, 500.873f );
		GameList->Center = !LeftJustify;
		std::vector<Localization::Words> GameNames;
		if ( PlayerManager::NumPlayers <= 1 )
		{
			const Localization::Words* tempVector[] = { Localization::Words_CLASSIC_GAME, Localization::Words_WALL_LEVEL };
			GameNames = std::vector<Localization::Words*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		}
		else
		{
			const Localization::Words* tempVector2[] = { Localization::Words_CLASSIC_GAME, Localization::Words_BUNGEE, Localization::Words_WALL_LEVEL };
			GameNames = std::vector<Localization::Words*>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
		}
		for ( std::vector<CloudberryKingdom::Localization::Words>::const_iterator name = GameNames.begin(); name != GameNames.end(); ++name )
		{
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( *name, ItemFont, false, true ) );
			SetItemProperties( item );
			GameList->AddItem( item, *name );
		}
		AddItem( GameList );
		if ( LeftJustify )
			GameList->Pos = Vector2( 117 + LeftJustifyAddX, 828 - 222 );
		else
			GameList->Pos = Vector2( 117, 828 - 222 );
		GameList->OnIndexSelect = std::make_shared<InitOnIndexSelect>( shared_from_this(), GameList );

		// Hero
		HeroText = std::make_shared<EzText>( Localization::Words_HERO, ItemFont );
		HeroText->Name = _T( "Hero" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );
		HeroText->setPos( Vector2( -1044.443f, 933 - 2 * 222 ) );

		HeroList = std::make_shared<MenuList>();
		HeroList->Name = _T( "Hero" );
		HeroList->Center = !LeftJustify;
		HeroList->MyExpandPos = Vector2( -782.1666f, 293.6826f );
		for ( std::vector<std::shared_ptr<BobPhsx> >::const_iterator hero = FreeplayHeroes.begin(); hero != FreeplayHeroes.end(); ++hero )
			AddHeroItem( *hero );

		// Random
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_RANDOM, ItemFont, false, true ) );
		SetItemProperties( item );
		HeroList->AddItem( item, BobPhsxRandom::getInstance() );
		// Custom
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( CustomHeroString, ItemFont, false, true ) );
		SetItemProperties( item );
		HeroList->AddItem( item, 0 );

		AddItem( HeroList );
		if ( LeftJustify )
			HeroList->Pos = Vector2( 117.2227f + LeftJustifyAddX - 150, 828 - 2 * 222 );
		else
			HeroList->Pos = Vector2( 117.2227f, 828 - 2 * 222 );
		HeroList->OnIndexSelect = std::make_shared<HeroList_OnIndexProxy>( shared_from_this() );
		HeroList->SetIndex( 0 );

		// Difficulty
		std::shared_ptr<EzText> DiffText = std::make_shared<EzText>( Localization::Words_DIFFICULTY, ItemFont );
		DiffText->Name = _T( "Diff" );
		SetHeaderProperties( DiffText );
		MyPile->Add( DiffText );
		DiffText->setPos( Vector2( -1233.889f, 40.55557f ) );

		std::vector<Localization::Words> Names = CampaignHelper::DifficultyNames;
		DiffList = std::make_shared<MenuList>();
		DiffList->Name = _T( "Diff" );
		DiffList->Center = !LeftJustify;
		DiffList->MyExpandPos = Vector2( -519.6807f, -151.5238f );
		DiffList->DoIndexWrapping = false;
		for ( int i = 0; i < 5; i++ )
		{
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( Names[ i ], ItemFont, false, true ) );
			SetItemProperties( item );
			DiffList->AddItem( item, Names[ i ] );
		}
		AddItem( DiffList );
		if ( LeftJustify )
			DiffList->Pos = Vector2( 242.2246f + LeftJustifyAddX, -73.11105f );
		else
			DiffList->Pos = Vector2( 242.2246f, -73.11105f );
		DiffList->OnIndexSelect = std::make_shared<DiffList_OnIndexProxy>( shared_from_this() );


		// Length
		std::shared_ptr<EzText> LengthText = std::make_shared<EzText>( Localization::Words_LENGTH, ItemFont );
		LengthText->Name = _T( "Length" );
		SetHeaderProperties( LengthText );
		MyPile->Add( LengthText );
		LengthText->setPos( Vector2( -1224.999f, -191.6667f ) );

		length = std::make_shared<LengthSlider>();
		length->Name = _T( "Length" );
		length->getGo().reset();
		AddItem( length );
		length->Pos = Vector2( -283, -556.1017f );

		length->OnSetValue = std::make_shared<InitOnSetValueHelper>( shared_from_this(), length );
		length->OnSlide = std::make_shared<InitOnSlideHelper>( shared_from_this(), length );

		// Mini checkpoints
		MiniCheckpoint = ObjectIcon::CheckpointIcon->Clone( ObjectIcon::IconScale_WIDGET );
		MiniCheckpoint->SetShadow( false );

		// Checkpoints
		CheckpointsText = std::make_shared<EzText>( Localization::Words_CHECKPOINTS, ItemFont );
		CheckpointsText->Name = _T( "Checkpoints" );
		SetHeaderProperties( CheckpointsText );
		MyPile->Add( CheckpointsText );
		CheckpointsText->setPos( Vector2( -1008.33f, -661.1111f ) );

		checkpoints = std::make_shared<MenuSliderNoSlide>( std::make_shared<EzText>( _T( "x " ), ItemFont ) );
		checkpoints->Name = _T( "Checkpoints" );
		checkpoints->setMyFloat( std::make_shared<WrappedFloat>( 1, 0, 4 ) );
		checkpoints->InitialSlideSpeed = 1;
		checkpoints->MaxSlideSpeed = 1;
		checkpoints->Discrete = true;
		checkpoints->SetToShowText();
		checkpoints->getGo().reset();
		checkpoints->SetIcon( ObjectIcon::CheckpointIcon->Clone() );
		checkpoints->Icon->SetShadow( false );
		checkpoints->MyDrawLayer = 1;
		AddItem( checkpoints );
		checkpoints->Pos = checkpoints->SelectedPos = Vector2( 267, -680.549f );
		checkpoints->Icon->setPos( Vector2( -22.22266f, -41.66666f ) );
		checkpoints->OnSlide = std::make_shared<InitOnSlideHelper2>( shared_from_this(), length );

		checkpoints->OnSetValue = std::make_shared<InitOnSetValueHelper2>( shared_from_this(), length );

		checkpoints->setVal( DesiredNumCheckpoints = 1 );
		length->setVal( 8000 );


		FontScale = 1;

		// Start
	#if defined(XBOX)
		MyPile->Add( std::make_shared<QuadClass>( ButtonTexture::getGo(), 90, _T("Button_A") ) );
	#endif
		Start = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_START, ItemFont ) );
		Start->Name = _T( "Start" );
		item->JiggleOnGo = false;
		AddItem( item );
		item->Pos = item->SelectedPos = Vector2( 682.1445f, -238.8095f );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;
	#if defined(NOT_PC)
		item->Selectable = false;
		item->Pos = Vector2( 721.8262f, -226.9048f );
	#endif
		item->setGo( Cast::ToItem( std::make_shared<BringNextProxy>( shared_from_this() ) ) );
		item->ScaleText( .92f );

		// Select 'Start Level' when the user presses (A)
		MyMenu->OnA = std::make_shared<InitOnAStartHelper>( shared_from_this() );

		// Load
		std::shared_ptr<MenuItem> Load;
	#if defined(PC_VERSION)
		Load = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_LOAD_LEVEL, ItemFont ) );
	#else
		Load = item = std::make_shared<MenuItem>( std::make_shared<EzText>( ButtonString::Y( 90 ) + _T( " Load" ), ItemFont ) );
	#endif
		Load->Name = _T( "Load" );
		Load->setGo( std::make_shared<BringLoadProxy1>( shared_from_this() ) );
		item->JiggleOnGo = false;
		AddItem( item );
		item->Pos = item->SelectedPos = Vector2( 682.1445f, -238.8095f );
		//item.MyText.MyFloatColor = Menu.DefaultMenuInfo.UnselectedNextColor;
		//item.MySelectedText.MyFloatColor = Menu.DefaultMenuInfo.SelectedNextColor;
	#if defined(NOT_PC)
		item->Selectable = false;
		item->Pos = Vector2( 721.8262f, -226.9048f );
	#endif
		item->ScaleText( .92f );

		// Back
	#if defined(XBOX)
		MyPile->Add( std::make_shared<QuadClass>( ButtonTexture::getBack(), 90, _T("Button_B") ) );
	#endif
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_BACK, ItemFont ) );
		item->Name = _T( "Back" );
		AddItem( item );
		item->SelectSound.reset();
		item->setGo( std::make_shared<ReturnToCallerProxy1>( shared_from_this() ) );
		item->Pos = item->SelectedPos = Vector2( 922.9375f, -523.8096f );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
	#if defined(NOT_PC)
		item->Selectable = false;
		item->Pos = Vector2( 958.6523f, -468.254f );
	#endif
		item->ScaleText( .92f );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
		GameList->SetIndex( 0 );
		DiffList->SetIndex( 0 );
		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( shared_from_this() );
		MyMenu->OnY = std::make_shared<BringLoadProxy>( shared_from_this() );
	}

	std::shared_ptr<MenuItem> CustomLevel_GUI::AddHeroItem( const std::shared_ptr<BobPhsx> &hero )
	{
		std::shared_ptr<MenuItem> item;
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( hero->Name, ItemFont, false, true ) );
		item->MyObject = hero;
		SetItemProperties( item );
		HeroList->AddItem( item, hero );
		float width = item->MyText->GetWorldWidth();
		const float max_width = 800;
		if ( width > max_width )
			item->ScaleText( max_width / width );
		return item;
	}

	void CustomLevel_GUI::DiffList_OnIndex()
	{
		if ( DiffList->ListIndex == 0 )
			Start->SubstituteText( Localization::Words_CONTINUE );
		else
			Start->SubstituteText( Localization::Words_START );
	}

	void CustomLevel_GUI::StartLevel()
	{
		CallingPanel.reset();
		StartLevelFromMenuData();
	}

	void CustomLevel_GUI::HeroList_OnIndex()
	{
		DesiredHeroIndex = HeroList->ListIndex;

		std::shared_ptr<BobPhsx> Hero = std::dynamic_pointer_cast<BobPhsx>( HeroList->getCurObj() );

		if ( 0 != Hero )
		{
			LevelSeed->DefaultHeroType = Hero;
			HeroIcon = Hero->Icon->Clone();
			HeroIcon->SetScale( 1.25f );

			if ( LevelSeed->MyGeometry == LevelGeometry_UP || LevelSeed->MyGeometry == LevelGeometry_DOWN )
				if ( Hero == BobPhsxSpaceship::getInstance() || Hero == BobPhsxRocketbox::getInstance() )
					HeroList->SetIndex( HeroList->ListIndex + 1 );
		}
		else
			if ( IsCustomHero() )
				HeroIcon = ObjectIcon::CustomIcon;

		HeroIcon->FancyPos->SetCenter( Pos );

		HeroIcon->setPos( Vector2( 1050.003f, 383.3334f ) );
		//HeroIcon.Pos = new Vector2(525.002f, 238.8889f);
	}

	bool CustomLevel_GUI::IsCustomHero()
	{
		return ( std::static_pointer_cast<BobPhsx>( HeroList->CurMenuItem->MyObject ) ) == 0;
	}

	bool CustomLevel_GUI::IsCustomDifficulty()
	{
		return DiffList->ListIndex == 0;
	}

	void CustomLevel_GUI::SetPos()
	{
	#if defined(PC_VERSION)
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Location" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -66.66797f, 677.9999f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Game" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -24.66602f, 475.4443f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hero" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -4.999969f, 284 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Diff" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -41.10744f, 79.66678f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Length" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -221.8892f, -342.2129f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Checkpoints" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 150.3331f, -602.7712f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Start" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 580.5577f, 4.047569f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Load" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 773.0172f, -224.9205f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 850.7158f, -461.508f ) );
		}

		MyMenu->setPos( Vector2( -285, 0 ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Location" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1002.89f, 802.4446f ) );
		}
		_t = MyPile->FindEzText( _T( "Game" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -844.444f, 619.3334f ) );
		}
		_t = MyPile->FindEzText( _T( "Hero" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -780.5543f, 419.5557f ) );
		}
		_t = MyPile->FindEzText( _T( "Diff" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1033.889f, 212.7778f ) );
		}
		_t = MyPile->FindEzText( _T( "Length" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1166.665f, 36.11107f ) );
		}
		_t = MyPile->FindEzText( _T( "Checkpoints" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1177.774f, -463.8889f ) );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 307.143f, -23.41241f ) );
			_q->setSize( Vector2( 1741.167f, 1044.7f ) );
		}
		_q = MyPile->FindQuad( _T( "Screenshot" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1340.002f, 497.2222f ) );
			_q->setSize( Vector2( 10.81731f, 13.22116f ) );
		}

		MyPile->setPos( Vector2( -285, 0 ) );

	#else
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Location" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -66.66797f, 677.9999f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Game" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -24.66602f, 475.4443f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Hero" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -4.999969f, 284 ) );
		}
		_item = MyMenu->FindItemByName( _T( "Diff" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -41.10744f, 79.66678f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Length" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -221.8892f, -342.2129f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Checkpoints" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 150.3331f, -602.7712f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Start" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 708.3351f, 4.047569f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Load" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 839.6832f, -241.5872f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 975.7158f, -483.7302f ) );
		}

		MyMenu->setPos( Vector2( -285, 0 ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Location" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1002.89f, 802.4446f ) );
		}
		_t = MyPile->FindEzText( _T( "Game" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -844.444f, 619.3334f ) );
		}
		_t = MyPile->FindEzText( _T( "Hero" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -780.5543f, 419.5557f ) );
		}
		_t = MyPile->FindEzText( _T( "Diff" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1033.889f, 212.7778f ) );
		}
		_t = MyPile->FindEzText( _T( "Length" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1166.665f, 36.11107f ) );
		}
		_t = MyPile->FindEzText( _T( "Checkpoints" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1177.774f, -463.8889f ) );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 307.143f, -23.41241f ) );
			_q->setSize( Vector2( 1741.167f, 1044.7f ) );
		}
		_q = MyPile->FindQuad( _T( "Screenshot" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 1340.002f, 497.2222f ) );
			_q->setSize( Vector2( 10.81731f, 13.22116f ) );
		}

		MyPile->setPos( Vector2( -285, 0 ) );
	#endif
	}

	void CustomLevel_GUI::SelectUpLevel()
	{
		LevelSeed->MyGameType = NormalGameData::Factory;

		if ( LevelSeed->MyGeometry != LevelGeometry_UP && LevelSeed->MyGeometry != LevelGeometry_DOWN )
			SelectNormal();

		LevelSeed->MyGeometry = LevelGeometry_UP;
		UpHero_NoSpaceship();
		UpHero_ModShown();

		ShowCheckpoints( false );
	}

	void CustomLevel_GUI::SelectDownLevel()
	{
		LevelSeed->MyGameType = NormalGameData::Factory;

		if ( LevelSeed->MyGeometry != LevelGeometry_UP && LevelSeed->MyGeometry != LevelGeometry_DOWN )
			SelectNormal();

		LevelSeed->MyGeometry = LevelGeometry_DOWN;
		UpHero_NoSpaceship();
		UpHero_ModShown();

		ShowCheckpoints( false );
	}

	void CustomLevel_GUI::BringNext()
	{
		if ( IsCustomHero() )
			BringHero();
		else if ( IsCustomDifficulty() )
			BringUpgrades();
		else
			StartLevel();
	}

	void CustomLevel_GUI::Show()
	{
		CkBaseMenu::Show();
	}

	void CustomLevel_GUI::BringHero()
	{
		HeroGui = std::make_shared<CustomHero_GUI>( shared_from_this() );
		Call( HeroGui, 0 );
		Hide( PresetPos_LEFT );
		this->SlideInFrom = PresetPos_LEFT;
	}

	void CustomLevel_GUI::BringUpgrades()
	{
		CallingPanel = std::make_shared<PassiveUpgrades_GUI>( PieceSeed, shared_from_this() );
		Call( CallingPanel, 0 );
		Hide( PresetPos_LEFT );
		this->SlideInFrom = PresetPos_LEFT;
	}

	void CustomLevel_GUI::BringLoad()
	{
		// Create the load menu
		//SavedSeedsGUI LoadMenu = new SavedSeedsGUI();
		//Call(LoadMenu, 0);
		std::shared_ptr<SaveLoadSeedMenu> menu = std::make_shared<SaveLoadSeedMenu>( MenuItem::ActivatingPlayer, true, false );
		Call( menu, 0 );

		Hide( PresetPos_LEFT );
		this->SlideInFrom = PresetPos_LEFT;
	}

	void CustomLevel_GUI::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();

		MyMenu->Show = true;
		CallingPanel.reset();
	}

	void CustomLevel_GUI::MyDraw()
	{
		if ( !Active && CallingPanel != 0 && !CallingPanel->Pos->Playing )
			MyMenu->Show = false;
		else
			MyMenu->Show = true;

		CkBaseMenu::MyDraw();

		if ( !MyMenu->Show )
		{
			MyMenu->CurDrawLayer = 0;
			MyMenu->PosOffset = MyMenu->FancyPos->Update();
			length->PosOffset = MyMenu->PosOffset;
			length->Draw();
		}

		if ( HeroIcon != 0 )
			HeroIcon->Draw( false );

		int NumCheckpoints = static_cast<int>( checkpoints->getMyFloat()->getVal() );

		MiniCheckpoint->SetScale( .8f * MiniCheckpoint->PrevSetRatio + .2f );
		float step = ( length->getSlider_TR().X - length->getBL().X ) / (NumCheckpoints + 1);
		for ( int i = 1; i <= NumCheckpoints; i++ )
		{
			MiniCheckpoint->setPos( Vector2( length->getBL().X + i * step + 15, length->getTR().Y ) );
			MiniCheckpoint->Draw( false );
		}
	}

std::wstring CustomLevel_GUI::SeedStringToLoad = 0;
bool CustomLevel_GUI::ExitFreeplay = false;

	void CustomLevel_GUI::MyPhsxStep()
	{
		if ( ExitFreeplay )
			return;

		if ( SeedStringToLoad != _T( "" ) )
		{
			std::wstring seed = SeedStringToLoad;
			SeedStringToLoad = _T( "" );

			SavedSeedsGUI::LoadSeed( seed, shared_from_this() );
			return;
		}

		CkBaseMenu::MyPhsxStep();
	}

	void CustomLevel_GUI::InitializeInstanceFields()
	{
		HoldNumCheckpoints = 1;
		HasWall = false;
		LeftJustify = true;
		LeftJustifyAddX = -400;
		DesiredNumCheckpoints = 0;
		DesiredLength = 0;
		DesiredHeroIndex = 0;
	}
}
