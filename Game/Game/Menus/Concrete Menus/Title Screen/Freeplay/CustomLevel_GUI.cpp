#include <global_header.h>

#include "Hacks/List.h"
#include <MasterHack.h>

#include "Game/Menus/Concrete Menus/ShopMenu.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

		struct CLG_PlayGameProxy : public Lambda
		{
		
			boost::shared_ptr<CustomLevel_GUI> clg;
		
			CLG_PlayGameProxy( const boost::shared_ptr<CustomLevel_GUI> &clg )
			{
				this->clg = clg;
			}

			void Apply()
			{
				clg->StartLevel();
			}

		};



	void CustomLevel_GUI::InitializeStatics()
	{
		CustomLevel_GUI::FreeplayTilesets = std::vector<boost::shared_ptr<TileSet> >();
		CustomLevel_GUI::FreeplayHeroes = std::vector<boost::shared_ptr<BobPhsx> >();
		CustomLevel_GUI::IsMaxLength = false;
		CustomLevel_GUI::Difficulty = 0;
		CustomLevel_GUI::CustomHeroString = Localization::Words_Factory;
		CustomLevel_GUI::RightPanelCenter = Vector2( -285, 0 );
		CustomLevel_GUI::SeedStringToLoad = std::wstring( L"" );
		CustomLevel_GUI::ExitFreeplay = false;
	}

	// Statics
	std::vector<boost::shared_ptr<TileSet> > CustomLevel_GUI::FreeplayTilesets;
	std::vector<boost::shared_ptr<BobPhsx> > CustomLevel_GUI::FreeplayHeroes;
	bool CustomLevel_GUI::IsMaxLength;
	int CustomLevel_GUI::Difficulty;
	Localization::Words CustomLevel_GUI::CustomHeroString;
	Vector2 CustomLevel_GUI::RightPanelCenter;
	std::wstring CustomLevel_GUI::SeedStringToLoad;
	bool CustomLevel_GUI::ExitFreeplay;



	CustomLevel_GUI::StartLevelFromMenDataStandardLoadProxy::StartLevelFromMenDataStandardLoadProxy( const boost::shared_ptr<LevelSeedData> &data )
	{
		this->data = data;
	}

	void CustomLevel_GUI::StartLevelFromMenDataStandardLoadProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		data->PostMake_StandardLoad( level );
	}

	CustomLevel_GUI::StartLevelFromMenuDataInitializeHelper::StartLevelFromMenuDataInitializeHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::StartLevelFromMenuDataInitializeHelper::Apply( const boost::shared_ptr<PieceSeedData> &piece )
	{
		piece->CopyUpgrades( clGui->PieceSeed );

		piece->StandardClose();
	}

	CustomLevel_GUI::StartLevelEnableLoadProxy::StartLevelEnableLoadProxy( const boost::shared_ptr<LevelSeedData> &data )
	{
		this->data = data;
	}

	void CustomLevel_GUI::StartLevelEnableLoadProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		data->PostMake_EnableLoad( level );
	}

	CustomLevel_GUI::OnReturnFromLevelProxy::OnReturnFromLevelProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::OnReturnFromLevelProxy::Apply()
	{
		clGui->OnReturnFromLevel();
	}

	CustomLevel_GUI::InitOnSetValueHelper::InitOnSetValueHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length )
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

	CustomLevel_GUI::InitOnSlideHelper::InitOnSlideHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length )
	{
		this->clGui = clGui;
		this->length = length;
	}

	void CustomLevel_GUI::InitOnSlideHelper::Apply()
	{
		clGui->DesiredLength = length->getMyFloat()->getVal();

		int MaxCheckpoints = __min( 4, static_cast<int>( length->getMyFloat()->getPercent() / 20 ) );

		float currentcheckpoints = clGui->checkpoints->getMyFloat()->getVal();
		currentcheckpoints = __max( currentcheckpoints, clGui->DesiredNumCheckpoints );
		currentcheckpoints = __min( currentcheckpoints, MaxCheckpoints );
		clGui->checkpoints->getMyFloat()->setVal( currentcheckpoints );
	}

	CustomLevel_GUI::InitOnSlideHelper2::InitOnSlideHelper2( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length )
	{
		this->clGui = clGui;
		this->length = length;
	}

	void CustomLevel_GUI::InitOnSlideHelper2::Apply()
	{
		clGui->DesiredNumCheckpoints = static_cast<int>( clGui->checkpoints->getMyFloat()->getVal() );

		float MinLength = ( .11f + .2f * ( clGui->checkpoints->getMyFloat()->getVal() + 1 ) ) * length->getMyFloat()->getSpread();
		length->getMyFloat()->setVal(__min(length->getMyFloat()->getVal(), clGui->DesiredLength));
		length->getMyFloat()->setVal(__max(length->getMyFloat()->getVal(), MinLength));
	}

	CustomLevel_GUI::InitOnSetValueHelper2::InitOnSetValueHelper2( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<LengthSlider> &length )
	{
		this->clGui = clGui;
		this->length = length;
	}

	void CustomLevel_GUI::InitOnSetValueHelper2::Apply()
	{
		int PrevNumPieces = clGui->LevelSeed->NumPieces;

		clGui->LevelSeed->NumPieces = 1 + static_cast<int>( clGui->checkpoints->getMyFloat()->getVal() );
		length->setVal( static_cast<float>( clGui->LevelSeed->Length ) );

		if ( PrevNumPieces != clGui->LevelSeed->NumPieces )
			clGui->MiniCheckpoint->SetScale( .01f );
	}

	CustomLevel_GUI::InitOnAStartHelper::InitOnAStartHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	bool CustomLevel_GUI::InitOnAStartHelper::Apply( const boost::shared_ptr<Menu> &dummy )
	{
		clGui->Start->getGo()->Apply( 0 );
		return true;
	}

	CustomLevel_GUI::InitOnIndexSelectHelper::InitOnIndexSelectHelper( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<MenuList> &LocationList )
	{
		this->clGui = clGui;
		this->LocationList = LocationList;
	}

	void CustomLevel_GUI::InitOnIndexSelectHelper::Apply()
	{
		boost::shared_ptr<TileSet> tileset = boost::dynamic_pointer_cast<TileSet>( LocationList->getCurObj() );

		//Vector2 HoldRelativeSize = Screenshot.GetTextureScaling();
		//Screenshot.TextureName = tileset.ScreenshotString;
		//Screenshot.ScaleYToMatchRatio(HoldRelativeSize.X * Screenshot.Quad.MyTexture.Width);

		clGui->LevelSeed->SetTileSet( tileset );
	}

	CustomLevel_GUI::InitOnIndexSelect::InitOnIndexSelect( const boost::shared_ptr<CustomLevel_GUI> &clGui, const boost::shared_ptr<MenuList> &GameList )
	{
		this->clGui = clGui;
		this->GameList = GameList;
	}

	void CustomLevel_GUI::InitOnIndexSelect::Apply()
	{
		clGui->LevelSeed->MyGameFlags.SetToDefault();
		clGui->LevelSeed->Masochistic = false;

		Localization::Words gamename = Unbox<Localization::Words>( GameList->getCurObj() );
		if ( gamename == Localization::Words_ClassicGame )
		{
			clGui->LevelSeed->MyGameType = NormalGameData::Factory;
			clGui->LevelSeed->MyGeometry = LevelGeometry_RIGHT;
			clGui->SelectNormal();
		}
		else if ( gamename == Localization::Words_Bungee )
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
		else if ( gamename == Localization::Words_WallLevel )
		{
			clGui->LevelSeed->MyGameType = NormalGameData::Factory;
			clGui->LevelSeed->MyGeometry = LevelGeometry_RIGHT;
			clGui->SelectNormal();
			clGui->ShowHeros( true );
			clGui->ShowCheckpoints( false );
			clGui->HasWall = true;
		}
        else if ( gamename == Localization::Words_Masochistic )
        {
            clGui->LevelSeed->MyGameType = NormalGameData::Factory;
            clGui->LevelSeed->MyGeometry = LevelGeometry_RIGHT;
            clGui->LevelSeed->Masochistic = true;
            clGui->SelectNormal();
        }
	}

	CustomLevel_GUI::DiffList_OnIndexProxy::DiffList_OnIndexProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::DiffList_OnIndexProxy::Apply()
	{
		clGui->DiffList_OnIndex();
	}

	CustomLevel_GUI::HeroList_OnIndexProxy::HeroList_OnIndexProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::HeroList_OnIndexProxy::Apply()
	{
		clGui->HeroList_OnIndex();
	}

	CustomLevel_GUI::BringNextProxy::BringNextProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::BringNextProxy::Apply()
	{
		clGui->BringNext();
	}

	CustomLevel_GUI::BringLoadProxy::BringLoadProxy( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::BringLoadProxy::Apply()
	{
		clGui->BringLoad();
	}

	CustomLevel_GUI::BringLoadProxy1::BringLoadProxy1( const boost::shared_ptr<CustomLevel_GUI> &clGui )
	{
		this->clGui = clGui;
	}

	void CustomLevel_GUI::BringLoadProxy1::Apply( const boost::shared_ptr<MenuItem> &dummy )
	{
		clGui->BringLoad();
	}

	CustomLevel_GUI::CustomLevel_GUI() :
		DesiredNumCheckpoints( 0 ),
		DesiredLength( 0 ),
		DesiredHeroIndex( 0 ),
		LeftJustify( false ),
		LeftJustifyAddX( 0 ),
		HoldNumCheckpoints( 0 ),
		HoldDesiredNumCheckpoints( 0 ),
		HasWall( false )
	{
	}

	boost::shared_ptr<CustomLevel_GUI> CustomLevel_GUI::CustomLevel_GUI_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		BobPhsx::CustomPhsxData::InitBounds();

		CustomHero_GUI::HeroPhsxData = BobPhsx::CustomPhsxData();
		CustomHero_GUI::HeroPhsxData.Init();

		NoBackIfNoCaller = true;

		SeedStringToLoad = std::wstring( L"" );
		ExitFreeplay = false;

		return boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() );
	}

	void CustomLevel_GUI::StartLevelFromMenuData()
	{
		boost::shared_ptr<LevelSeedData> data = boost::make_shared<LevelSeedData>( LevelSeed );
		data->setSeed( Tools::GlobalRnd->Rnd->Next() );

		// Debug: set hero type
		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Spaceship, Hero_Shape.Small, Hero_MoveMod.Classic);

		// Vertical levels have no checkpoints
		if ( LevelSeed->MyGeometry != LevelGeometry_RIGHT )
			LevelSeed->NumPieces = 1;

		// Copy Upgrade1 to Upgrade2
		CopyFromTo( PieceSeed->MyUpgrades1->UpgradeLevels, PieceSeed->MyUpgrades2->UpgradeLevels );

		// Custom difficulty
		if ( IsCustomDifficulty() )
		{
			data->Initialize( boost::make_shared<StartLevelFromMenuDataInitializeHelper>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );
		}
		// Preset difficulty
		else
		{
			boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > custom;

			custom = DifficultyGroups::FixedPieceMod( static_cast<float>( DiffList->ListIndex - 1 ), data, false );

			data->Initialize( custom );
		}

		// Wall
		if ( HasWall )
			data->HasWall = true;

		data->ProcessSpecial();

		// Dark bottom
		if ( data->MyGeometry == LevelGeometry_DOWN )
			data->PieceSeeds[ 0 ]->Style->MyFinalPlatsType = StyleData::FinalPlatsType_DARK_BOTTOM;

		data->PostMake->Add( boost::make_shared<StartLevelFromMenDataStandardLoadProxy>( data ) );

		StartLevel( data );
	}

	void CustomLevel_GUI::StartLevel( const boost::shared_ptr<LevelSeedData> &data )
	{
		HelpMenu::CostMultiplier = 1;

		Tools::PlayHappyMusic( MyGame );

		data->PostMake->Add( boost::make_shared<StartLevelEnableLoadProxy>( data ) );

		PlayerManager::setCoinsSpent( -999 );

		boost::shared_ptr<GameData> game = data->Create();
		game->ParentGame = MyGame;
		game->Freeplay = true;
		game->DefaultHeroType = data->DefaultHeroType;
		Difficulty = DiffList->ListIndex - 1;
		IsMaxLength = length->getIsMaxed();
	}

	void CustomLevel_GUI::OnAdd()
	{
		CloudberryKingdomGame::SetPresence( Presence_Freeplay );

		CkBaseMenu::OnAdd();

		MyGame->ClearPreviousLoadFunction();

		MyPile->setPos( MyPile->getPos() + RightPanelCenter );
		MyMenu->FancyPos->RelVal += RightPanelCenter;

		// Register for when the created level ends
		MyGame->OnReturnTo->Add( boost::make_shared<OnReturnFromLevelProxy>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );

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
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = HeroList->MyList.begin(); item != HeroList->MyList.end(); ++item )
			( *item )->Selectable = true;
	}

	void CustomLevel_GUI::UpHero_ModShown()
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = HeroList->MyList.begin(); item != HeroList->MyList.end(); ++item )
		{
			if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( ( *item )->MyObject ) != 0 || boost::dynamic_pointer_cast<BobPhsxRocketbox>( ( *item )->MyObject ) != 0 )
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

	void CustomLevel_GUI::Init()
	{
		ItemShadows = false;

		LevelSeed = boost::make_shared<LevelSeedData>();
		PieceSeed = boost::make_shared<PieceSeedData>( boost::shared_ptr<LevelSeedData>() );

		SlideInFrom = SlideOutTo = PresetPos_RIGHT;

		FontScale = .73f;

		MyPile = boost::make_shared<DrawPile>();

		CkBaseMenu::Init();

		ReturnToCallerDelay = 18;
		SlideInLength = 25;
		SlideOutLength = 24;

		CallDelay = 5;


		SelectedItemShift = Vector2( 0, 0 );

		// Backdrop
		boost::shared_ptr<QuadClass> backdrop;

		backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1500x900" ), 1500.f, true );
		backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( backdrop );
		EpilepsySafe( .5f );
		backdrop->setSize( Vector2( 1690.477f, 1115.617f ) );
		backdrop->setPos( Vector2( 287.6977f, 51.58758f ) );

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );

		setControl( -1 );

		MyMenu->OnB.reset();

		boost::shared_ptr<MenuItem> item;

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
		boost::shared_ptr<EzText> LocationText = boost::make_shared<EzText>( Localization::Words_Location, ItemFont );
		LocationText->Name = std::wstring( L"Location" );
		SetHeaderProperties( LocationText );
		MyPile->Add( LocationText );
		LocationText->setPos( Vector2( -1050.111f, 933 ) );

		boost::shared_ptr<MenuList> LocationList = MakeMagic( MenuList, () );
			MenuList_PostConstruct( LocationList );
		LocationList->Name = std::wstring( L"Location" );
		LocationList->Center = !LeftJustify;
		LocationList->MyExpandPos = Vector2( -498.1506f, 713.873f );
		for ( std::vector<boost::shared_ptr<TileSet> >::const_iterator tileset = FreeplayTilesets.begin(); tileset != FreeplayTilesets.end(); ++tileset )
		{
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( ( *tileset )->NameInGame, ItemFont, false, true ) ) );
			SetItemProperties( item );
			
			boost::shared_ptr<TileSet> t = *tileset;
			boost::shared_ptr<Object> smart = boost::static_pointer_cast<Object>( t );

			LocationList->AddItem( item, MakeSmartObject( smart ) );
		}
		AddItem( LocationList );
		if ( LeftJustify )
			LocationList->Pos = Vector2( 200 + LeftJustifyAddX, 828 );
		else
			LocationList->Pos = Vector2( 200, 828 );
		LocationList->OnIndexSelect = boost::make_shared<InitOnIndexSelectHelper>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ), LocationList );
		LocationList->SetIndex( 0 );

		// Game type
		boost::shared_ptr<EzText> GameText = boost::make_shared<EzText>( Localization::Words_Game, ItemFont );
		GameText->Name = std::wstring( L"Game" );
		SetHeaderProperties( GameText );
		MyPile->Add( GameText );
		GameText->setPos( Vector2( -1061.11f, 933 - 222 ) );

		boost::shared_ptr<MenuList> GameList = MakeMagic( MenuList, () );
			MenuList_PostConstruct( GameList );
		GameList->Name = std::wstring( L"Game" );
		GameList->MyExpandPos = Vector2( -580, 500.873f );
		GameList->Center = !LeftJustify;
		std::vector<Localization::Words> GameNames;
		if ( PlayerManager::NumPlayers <= 1 )
		{
			//Localization::Words tempVector[] = { Localization::Words_ClassicGame, Localization::Words_WallLevel, Localization::Words_Masochistic };
			Localization::Words tempVector[] = { Localization::Words_ClassicGame, Localization::Words_WallLevel };
			GameNames = VecFromArray( tempVector );
		}
		else
		{
			//Localization::Words tempVector2[] = { Localization::Words_ClassicGame, Localization::Words_Bungee, Localization::Words_WallLevel, Localization::Words_Masochistic };
			Localization::Words tempVector2[] = { Localization::Words_ClassicGame, Localization::Words_Bungee, Localization::Words_WallLevel };
			GameNames = std::vector<Localization::Words>( VecFromArray( tempVector2 ) );
		}
		for ( std::vector<Localization::Words>::const_iterator name = GameNames.begin(); name != GameNames.end(); ++name )
		{
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( *name, ItemFont, false, true ) ) );
			SetItemProperties( item );
			GameList->AddItem( item, MakeSmartObject( *name ) );
		}
		AddItem( GameList );
		if ( LeftJustify )
			GameList->Pos = Vector2( 117 + LeftJustifyAddX, 828 - 222 );
		else
			GameList->Pos = Vector2( 117, 828 - 222 );
		GameList->OnIndexSelect = boost::make_shared<InitOnIndexSelect>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ), GameList );

		// Hero
		HeroText = boost::make_shared<EzText>( Localization::Words_Hero, ItemFont );
		HeroText->Name = std::wstring( L"Hero" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );
		HeroText->setPos( Vector2( -1044.443f, 933 - 2 * 222 ) );

		HeroList = MakeMagic( MenuList, () );
			MenuList_PostConstruct( HeroList );
		HeroList->Name = std::wstring( L"Hero" );
		HeroList->Center = !LeftJustify;
		HeroList->MyExpandPos = Vector2( -782.1666f, 293.6826f );
		for ( std::vector<boost::shared_ptr<BobPhsx> >::const_iterator hero = FreeplayHeroes.begin(); hero != FreeplayHeroes.end(); ++hero )
			AddHeroItem( *hero );

		// Random
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Random, ItemFont, false, true ) ) );
		SetItemProperties( item );
		HeroList->AddItem( item, MakeSmartObject( BobPhsxRandom::getInstance() ) );
		// Custom
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( CustomHeroString, ItemFont, false, true ) ) );
		SetItemProperties( item );
		HeroList->AddItem( item, 0 );

		AddItem( HeroList );
		if ( LeftJustify )
			HeroList->Pos = Vector2( 117.2227f + LeftJustifyAddX - 150, 828 - 2 * 222 );
		else
			HeroList->Pos = Vector2( 117.2227f, 828 - 2 * 222 );
		HeroList->OnIndexSelect = boost::make_shared<HeroList_OnIndexProxy>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) );
		HeroList->SetIndex( 0 );

		// Difficulty
		boost::shared_ptr<EzText> DiffText = boost::make_shared<EzText>( Localization::Words_Difficulty, ItemFont );
		DiffText->Name = std::wstring( L"Diff" );
		SetHeaderProperties( DiffText );
		MyPile->Add( DiffText );
		DiffText->setPos( Vector2( -1233.889f, 40.55557f ) );

		std::vector<Localization::Words> Names = CampaignHelper::DifficultyNames;
		DiffList = MakeMagic( MenuList, () );
			MenuList_PostConstruct( DiffList );
		DiffList->Name = std::wstring( L"Diff" );
		DiffList->Center = !LeftJustify;
		DiffList->MyExpandPos = Vector2( -519.6807f, -151.5238f );
		DiffList->DoIndexWrapping = false;
		for ( int i = 0; i < 5; i++ )
		{
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Names[ i ], ItemFont, false, true ) ) );
			SetItemProperties( item );
			DiffList->AddItem( item, MakeSmartObject( Names[ i ] ) );
		}
		AddItem( DiffList );
		if ( LeftJustify )
			DiffList->Pos = Vector2( 242.2246f + LeftJustifyAddX, -73.11105f );
		else
			DiffList->Pos = Vector2( 242.2246f, -73.11105f );
		DiffList->OnIndexSelect = boost::make_shared<DiffList_OnIndexProxy>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) );


		// Length
		boost::shared_ptr<EzText> LengthText = boost::make_shared<EzText>( Localization::Words_Length, ItemFont );
		LengthText->Name = std::wstring( L"Length" );
		SetHeaderProperties( LengthText );
		MyPile->Add( LengthText );
		LengthText->setPos( Vector2( -1224.999f, -191.6667f ) );

		length = MakeMagic( LengthSlider, () );
		length->Name = std::wstring( L"Length" );
		length->_Go.reset();
		AddItem( length );
		length->Pos = Vector2( -283, -556.1017f );

		length->OnSetValue = boost::make_shared<InitOnSetValueHelper>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ), length );
		length->OnSlide = boost::make_shared<InitOnSlideHelper>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ), length );

		// Mini checkpoints
		MiniCheckpoint = ObjectIcon::CheckpointIcon->Clone( ObjectIcon::IconScale_WIDGET );
		MiniCheckpoint->SetShadow( false );

		// Checkpoints
		CheckpointsText = boost::make_shared<EzText>( Localization::Words_Checkpoints, ItemFont );
		CheckpointsText->Name = std::wstring( L"Checkpoints" );
		SetHeaderProperties( CheckpointsText );
		MyPile->Add( CheckpointsText );
		CheckpointsText->setPos( Vector2( -1008.33f, -661.1111f ) );

		checkpoints = MakeMagic( MenuSliderNoSlide, ( boost::make_shared<EzText>( std::wstring( L"x " ), ItemFont ) ) );
		checkpoints->Name = std::wstring( L"Checkpoints" );
		checkpoints->setMyFloat( boost::make_shared<WrappedFloat>( 1.f, 0.f, 4.f ) );
		checkpoints->InitialSlideSpeed = 1;
		checkpoints->MaxSlideSpeed = 1;
		checkpoints->Discrete = true;
		checkpoints->SetToShowText();
		checkpoints->_Go.reset();
		checkpoints->SetIcon( ObjectIcon::CheckpointIcon->Clone() );
		checkpoints->Icon->SetShadow( false );
		checkpoints->MyDrawLayer = 1;
		AddItem( checkpoints );
		checkpoints->Pos = checkpoints->SelectedPos = Vector2( 267, -680.549f );
		checkpoints->Icon->setPos( Vector2( -22.22266f, -41.66666f ) );
		checkpoints->OnSlide = boost::make_shared<InitOnSlideHelper2>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ), length );

		checkpoints->OnSetValue = boost::make_shared<InitOnSetValueHelper2>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ), length );

		DesiredNumCheckpoints = 1;
		checkpoints->setVal( static_cast<float>( DesiredNumCheckpoints ) );
		length->setVal( 8000 );


		FontScale = 1;

		// Start
		item = Start = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Start, ItemFont ) ) );
		Start->Name = std::wstring( L"Start" );
		item->JiggleOnGo = false;
		AddItem( item );
		item->Pos = item->SelectedPos = Vector2( 682.1445f, -238.8095f );
		Menu::DefaultMenuInfo::SetNext( item );

if (ButtonCheck::ControllerInUse)
{
        MyPile->Add(boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.f, std::wstring( L"Button_A" ) ) );
        item->Selectable = false;
}
		item->setGo( Cast::ToItem( boost::make_shared<BringNextProxy>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) ) );
		item->ScaleText( .92f );

		// Select 'Start Level' when the user presses (A)
		MyMenu->OnA = boost::make_shared<InitOnAStartHelper>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) );

		// Load
		boost::shared_ptr<MenuItem> Load;
		item = Load = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_LoadLevel, ItemFont ) ) );
		Load->Name = std::wstring( L"Load" );
		Load->setGo( boost::make_shared<BringLoadProxy1>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );
		item->JiggleOnGo = false;
		AddItem( item );
		item->Pos = item->SelectedPos = Vector2( 682.1445f, -238.8095f );
		//item.MyText.MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		//item.MySelectedText.MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;
if (ButtonCheck::ControllerInUse)
{
#if XBOX || PC_VERSION
		Menu::DefaultMenuInfo::SetX( item );
#endif

		MyPile->Add(boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.f, std::wstring( L"Button_Y" ) ) );
		item->Selectable = false;
}
		item->ScaleText( .92f );

		// Back
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Back, ItemFont ) ) );
		item->Name = std::wstring( L"Back" );
		AddItem( item );
		item->SelectSound.reset();
		item->setGo( boost::make_shared<ReturnToCallerProxy1>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );
		item->Pos = item->SelectedPos = Vector2( 922.9375f, -523.8096f );
		Menu::DefaultMenuInfo::SetBack( item );
if (ButtonCheck::ControllerInUse)
{
		MyPile->Add(boost::make_shared<QuadClass>( ButtonTexture::getBack(), 90.f, std::wstring( L"Button_B" ) ) );
		item->Selectable = false;
}
		item->ScaleText( .92f );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
		GameList->SetIndex( 0 );
		DiffList->SetIndex( 0 );
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
		//MyMenu->OnY = boost::make_shared<BringLoadProxy>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) );
		MyMenu->OnX = Cast::ToMenu( boost::make_shared<BringLoadProxy>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );
	}

	boost::shared_ptr<MenuItem> CustomLevel_GUI::AddHeroItem( const boost::shared_ptr<BobPhsx> &hero )
	{
		boost::shared_ptr<MenuItem> item;
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( hero->Name, ItemFont, false, true ) ) );
		item->MyObject = MakeSmartObject( hero );
		SetItemProperties( item );
		HeroList->AddItem( item, MakeSmartObject( hero ) );
		float width = item->MyText->GetWorldWidth();
		const float max_width = 800;
		if ( width > max_width )
			item->ScaleText( max_width / width );
		return item;
	}

	void CustomLevel_GUI::DiffList_OnIndex()
	{
		if ( DiffList->ListIndex == 0 )
			Start->SubstituteText( Localization::Words_Continue );
		else
			Start->SubstituteText( Localization::Words_Start );
	}

	void CustomLevel_GUI::StartLevel()
	{
		CallingPanel.reset();
		StartLevelFromMenuData();
	}

	void CustomLevel_GUI::HeroList_OnIndex()
	{
		DesiredHeroIndex = HeroList->ListIndex;

		boost::shared_ptr<BobPhsx> Hero = boost::dynamic_pointer_cast<BobPhsx>( HeroList->getCurObj() );

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

		switch ( Localization::CurrentLanguage->MyLanguage )
		{
			case Localization::Language_GERMAN: HeroIcon->setPos( Vector2(952.7809f, 525.0001f) ); break;
			default: HeroIcon->setPos( Vector2(1050.003f, 383.3334f) ); break;
		}

		//HeroIcon->setPos( Vector2( 1050.003f, 383.3334f ) );
	}

	bool CustomLevel_GUI::IsCustomHero()
	{
		return HeroList->ListIndex == HeroList->MyList.size() - 1;
		//return ( boost::static_pointer_cast<BobPhsx>( HeroList->CurMenuItem->MyObject ) ) == 0;
	}

	bool CustomLevel_GUI::IsCustomDifficulty()
	{
		return DiffList->ListIndex == 0;
	}

	void CustomLevel_GUI::SetPos()
        {
if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"Location" ); if (_item != 0 ) { _item->setSetPos( Vector2(-97.22375f, 644.6665f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Game" ); if (_item != 0 ) { _item->setSetPos( Vector2(-80.2215f, 467.111f ) ); _item->MyText->setScale( 0.6847501f ); _item->MySelectedText->setScale( 0.6847501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Hero" ); if (_item != 0 ) { _item->setSetPos( Vector2(-79.99997f, 278.4445f ) ); _item->MyText->setScale( 0.7035001f ); _item->MySelectedText->setScale( 0.7035001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Diff" ); if (_item != 0 ) { _item->setSetPos( Vector2( 208.8927f, 79.66678f ) ); _item->MyText->setScale( 0.6231676f ); _item->MySelectedText->setScale( 0.6231676f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Length" ); if (_item != 0 ) { _item->setSetPos( Vector2(-221.8892f, -342.2129f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Checkpoints" ); if (_item != 0 ) { _item->setSetPos( Vector2( 150.3331f, -602.7712f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Start" ); if (_item != 0 ) { _item->setSetPos( Vector2( 797.224f, -15.39686f ) ); _item->MyText->setScale( 0.8707501f ); _item->MySelectedText->setScale( 0.8707501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Load" ); if (_item != 0 ) { _item->setSetPos( Vector2( 850.7949f, -216.5871f ) ); _item->MyText->setScale( 0.7222498f ); _item->MySelectedText->setScale( 0.7222498f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 878.4934f, -394.8412f ) ); _item->MyText->setScale( 0.7444999f ); _item->MySelectedText->setScale( 0.7444999f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2(-285.f, 0.f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Location" ); if (_t != 0 ) { _t->setPos( Vector2(-708.4452f, 799.6667f ) ); _t->setScale( 0.7418334f ); }
	_t = MyPile->FindEzText( L"Game" ); if (_t != 0 ) { _t->setPos( Vector2(-694.444f, 597.1111f ) ); _t->setScale( 0.657f ); }
	_t = MyPile->FindEzText( L"Hero" ); if (_t != 0 ) { _t->setPos( Vector2(-680.5546f, 405.6668f ) ); _t->setScale( 0.657f ); }
	_t = MyPile->FindEzText( L"Diff" ); if (_t != 0 ) { _t->setPos( Vector2(-1228.333f, 204.4445f ) ); _t->setScale( 0.5706667f ); }
	_t = MyPile->FindEzText( L"Length" ); if (_t != 0 ) { _t->setPos( Vector2(-1166.665f, 36.11107f ) ); _t->setScale( 0.657f ); }
	_t = MyPile->FindEzText( L"Checkpoints" ); if (_t != 0 ) { _t->setPos( Vector2(-1177.774f, -463.8889f ) ); _t->setScale( 0.657f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 307.143f, -23.41241f ) ); _q->setSize( Vector2( 1741.167f, 1044.7f ) ); }
	_q = MyPile->FindQuad( L"Button_A" ); if (_q != 0 ) { _q->setPos( Vector2( 755.5557f, -177.7777f ) ); _q->setSize( Vector2( 91.00001f, 91.00001f ) ); }
	_q = MyPile->FindQuad( L"Button_Y" ); if (_q != 0 ) { _q->setPos( Vector2( 788.8889f, -355.5555f ) ); _q->setSize( Vector2( 91.99997f, 91.99997f ) ); }
	_q = MyPile->FindQuad( L"Button_B" ); if (_q != 0 ) { _q->setPos( Vector2( 827.778f, -538.889f ) ); _q->setSize( Vector2( 90.f, 90.f ) ); }

	MyPile->setPos( Vector2(-285.f, 0.f ) );
}
else
{
if ( ButtonCheck::ControllerInUse )
{
            boost::shared_ptr<MenuItem> _item;
            _item = MyMenu->FindItemByName( L"Location" ); if (_item != 0 ) { _item->setSetPos( Vector2(-66.66797f, 677.9999f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Game" ); if (_item != 0 ) { _item->setSetPos( Vector2(-24.66602f, 475.4443f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Hero" ); if (_item != 0 ) { _item->setSetPos( Vector2(-4.999969f, 284.f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Diff" ); if (_item != 0 ) { _item->setSetPos( Vector2(-41.10744f, 79.66678f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Length" ); if (_item != 0 ) { _item->setSetPos( Vector2(-221.8892f, -342.2129f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Checkpoints" ); if (_item != 0 ) { _item->setSetPos( Vector2( 150.3331f, -602.7712f ) ); _item->MyText->setScale( 0.73f ); _item->MySelectedText->setScale( 0.73f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Start" ); if (_item != 0 ) { _item->setSetPos( Vector2( 877.7795f, -45.95242f ) ); _item->MyText->setScale( 0.7502491f ); _item->MySelectedText->setScale( 0.7502491f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Load" ); if (_item != 0 ) { _item->setSetPos( Vector2( 898.0163f, -255.4761f ) ); _item->MyText->setScale( 0.7280834f ); _item->MySelectedText->setScale( 0.7280834f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
            _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 900.7158f, -464.2858f ) ); _item->MyText->setScale( 0.7764169f ); _item->MySelectedText->setScale( 0.7764169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

            MyMenu->setPos( Vector2(-285.f, 0.f ) );

            boost::shared_ptr<EzText> _t;
            _t = MyPile->FindEzText( L"Location" ); if (_t != 0 ) { _t->setPos( Vector2(-1002.89f, 802.4446f ) ); _t->setScale( 0.657f ); }
            _t = MyPile->FindEzText( L"Game" ); if (_t != 0 ) { _t->setPos( Vector2(-844.444f, 619.3334f ) ); _t->setScale( 0.657f ); }
            _t = MyPile->FindEzText( L"Hero" ); if (_t != 0 ) { _t->setPos( Vector2(-780.5543f, 419.5557f ) ); _t->setScale( 0.657f ); }
            _t = MyPile->FindEzText( L"Diff" ); if (_t != 0 ) { _t->setPos( Vector2(-1033.889f, 212.7778f ) ); _t->setScale( 0.657f ); }
            _t = MyPile->FindEzText( L"Length" ); if (_t != 0 ) { _t->setPos( Vector2(-1166.665f, 36.11107f ) ); _t->setScale( 0.657f ); }
            _t = MyPile->FindEzText( L"Checkpoints" ); if (_t != 0 ) { _t->setPos( Vector2(-1177.774f, -463.8889f ) ); _t->setScale( 0.657f ); }

            boost::shared_ptr<QuadClass> _q;
            _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 307.143f, -23.41241f ) ); _q->setSize( Vector2( 1741.167f, 1044.7f ) ); }
            _q = MyPile->FindQuad( L"Button_A" ); if (_q != 0 ) { _q->setPos( Vector2( 808.3335f, -180.5555f ) ); _q->setSize( Vector2( 91.00001f, 91.00001f ) ); }
            _q = MyPile->FindQuad( L"Button_Y" ); if (_q != 0 ) { _q->setPos( Vector2( 813.8889f, -397.2222f ) ); _q->setSize( Vector2( 91.99997f, 91.99997f ) ); }
            _q = MyPile->FindQuad( L"Button_B" ); if (_q != 0 ) { _q->setPos( Vector2( 819.4445f, -602.7778f ) ); _q->setSize( Vector2( 90.f, 90.f ) ); }

            MyPile->setPos( Vector2(-285.f, 0.f ) );
}
else
{
            boost::shared_ptr<MenuItem> _item;
            _item = MyMenu->FindItemByName( L"Location" ); if (_item != 0 ) { _item->setSetPos( Vector2(-66.66797f, 677.9999f ) ); }
            _item = MyMenu->FindItemByName( L"Game" ); if (_item != 0 ) { _item->setSetPos( Vector2(-24.66602f, 475.4443f ) ); }
            _item = MyMenu->FindItemByName( L"Hero" ); if (_item != 0 ) { _item->setSetPos( Vector2(-4.999969f, 284.f ) ); }
            _item = MyMenu->FindItemByName( L"Diff" ); if (_item != 0 ) { _item->setSetPos( Vector2(-41.10744f, 79.66678f ) ); }
            _item = MyMenu->FindItemByName( L"Length" ); if (_item != 0 ) { _item->setSetPos( Vector2(-221.8892f, -342.2129f ) ); }
            _item = MyMenu->FindItemByName( L"Checkpoints" ); if (_item != 0 ) { _item->setSetPos( Vector2( 150.3331f, -602.7712f ) ); }
            _item = MyMenu->FindItemByName( L"Start" ); if (_item != 0 ) { _item->setSetPos( Vector2( 580.5577f, 4.047569f ) ); }
            _item = MyMenu->FindItemByName( L"Load" ); if (_item != 0 ) { _item->setSetPos( Vector2( 773.0172f, -224.9205f ) ); }
            _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 850.7158f, -461.508f ) ); }

            MyMenu->setPos( Vector2(-285.f, 0.f ) );

            boost::shared_ptr<EzText> _t;
            _t = MyPile->FindEzText( L"Location" ); if (_t != 0 ) { _t->setPos( Vector2(-1002.89f, 802.4446f ) ); }
            _t = MyPile->FindEzText( L"Game" ); if (_t != 0 ) { _t->setPos( Vector2(-844.444f, 619.3334f ) ); }
            _t = MyPile->FindEzText( L"Hero" ); if (_t != 0 ) { _t->setPos( Vector2(-780.5543f, 419.5557f ) ); }
            _t = MyPile->FindEzText( L"Diff" ); if (_t != 0 ) { _t->setPos( Vector2(-1033.889f, 212.7778f ) ); }
            _t = MyPile->FindEzText( L"Length" ); if (_t != 0 ) { _t->setPos( Vector2(-1166.665f, 36.11107f ) ); }
            _t = MyPile->FindEzText( L"Checkpoints" ); if (_t != 0 ) { _t->setPos( Vector2(-1177.774f, -463.8889f ) ); }

            boost::shared_ptr<QuadClass> _q;
            _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 307.143f, -23.41241f ) ); _q->setSize( Vector2( 1741.167f, 1044.7f ) ); }
            _q = MyPile->FindQuad( L"Screenshot" ); if (_q != 0 ) { _q->setPos( Vector2( 1340.002f, 497.2222f ) ); _q->setSize( Vector2( 10.81731f, 13.22116f ) ); }

            MyPile->setPos( Vector2(-285.f, 0.f ) );
}
}
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
		{
			CloudberryKingdomGame::Freeplay_Count++;
			if ( CloudberryKingdomGame::getIsDemo() && CloudberryKingdomGame::Freeplay_Count >= CloudberryKingdomGame::Freeplay_Max )
			{
				Call( MakeMagic( UpSellMenu, ( Localization::Words_UpSell_FreePlay, MenuItem::ActivatingPlayer ) ) );
				Hide( PresetPos_RIGHT, 0 );

				return;
			}

            CloudberryKingdomGame::PromptForDeviceIfNoneSelected();
			MyGame->PlayGame( boost::make_shared<CLG_PlayGameProxy>( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );
		}
	}

	void CustomLevel_GUI::Show()
	{
		CkBaseMenu::Show();
	}

	void CustomLevel_GUI::BringHero()
	{
		HeroGui = MakeMagic( CustomHero_GUI, ( boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );
		Call( HeroGui, 0 );
		Hide( PresetPos_LEFT );
		this->SlideInFrom = PresetPos_LEFT;
	}

	void CustomLevel_GUI::BringUpgrades()
	{
		CallingPanel = MakeMagic( PassiveUpgrades_GUI, ( PieceSeed, boost::static_pointer_cast<CustomLevel_GUI>( shared_from_this() ) ) );
		Call( CallingPanel, 0 );
		Hide( PresetPos_LEFT );
		this->SlideInFrom = PresetPos_LEFT;
	}

	void CustomLevel_GUI::BringLoad()
	{
        if ( CloudberryKingdomGame::getIsDemo() )
        {
            Call( MakeMagic( UpSellMenu, ( Localization::Words_UpSell_SaveLoad, MenuItem::ActivatingPlayer ) ) );
            Hide( PresetPos_LEFT, 0 );

            return;
        }

		// Create the load menu
#ifdef PC_VERSION
		boost::shared_ptr<SaveLoadSeedMenu> menu = MakeMagic( SaveLoadSeedMenu, ( MenuItem::ActivatingPlayer, true, false ) );
		Call( menu, 0 );
#else
            Call( MakeMagic( SavedSeedsGUI, () ), 11 );
#endif

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
		if ( !Active && CallingPanel != 0 && CallingPanel->Pos != 0 && !CallingPanel->Pos->Playing )
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

		if ( CloudberryKingdomGame::getIsDemo() && Hid && !Pos->Playing ) return;

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

	void CustomLevel_GUI::MyPhsxStep()
	{
		if ( ExitFreeplay )
			return;

		if ( SeedStringToLoad != std::wstring( L"" ) )
		{
			std::wstring seed = SeedStringToLoad;
			SeedStringToLoad = std::wstring( L"" );

			SavedSeedsGUI::LoadSeed( seed, boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
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
