#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void CustomHero_GUI::InitializeStatics()
	{
		CustomHero_GUI::Hero = 0;

		CustomHero_GUI::BaseListIndex = 0;
		CustomHero_GUI::SizeListIndex = 0;
		CustomHero_GUI::JumpListIndex = 0;
	}

	// Statics
	BobPhsx::CustomPhsxData CustomHero_GUI::HeroPhsxData;
	boost::shared_ptr<BobPhsx> CustomHero_GUI::Hero;

	int CustomHero_GUI::BaseListIndex;
	int CustomHero_GUI::SizeListIndex;
	int CustomHero_GUI::JumpListIndex;



	CustomHero_GUI::StartTestProxy::StartTestProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::StartTestProxy::Apply()
	{
		chGui->StartTest();
	}

	CustomHero_GUI::MoveBlockAndKillProxy::MoveBlockAndKillProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	bool CustomHero_GUI::MoveBlockAndKillProxy::Apply()
	{
		return chGui->MoveBlockAndKill();
	}

	CustomHero_GUI::KillBobsHelper::KillBobsHelper( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::KillBobsHelper::Apply()
	{
		for ( BobVec::const_iterator bob = chGui->MyGame->MyLevel->Bobs.begin(); bob != chGui->MyGame->MyLevel->Bobs.end(); ++bob )
			( *bob )->Die( BobDeathType_NONE );
	}

	CustomHero_GUI::AddItemProxy::AddItemProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::AddItemProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		chGui->AddItem( item );
	}

	CustomHero_GUI::UpdateBaseHeroProxy::UpdateBaseHeroProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::UpdateBaseHeroProxy::Apply()
	{
		chGui->UpdateBaseHero();
	}

	CustomHero_GUI::UpdateSizeHeroProxy::UpdateSizeHeroProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::UpdateSizeHeroProxy::Apply()
	{
		chGui->UpdateSizeHero();
	}

	CustomHero_GUI::UpdateJumpHeroProxy::UpdateJumpHeroProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::UpdateJumpHeroProxy::Apply()
	{
		chGui->UpdateJumpHero();
	}

	CustomHero_GUI::NextProxy::NextProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::NextProxy::Apply()
	{
		chGui->Next();
	}

	CustomHero_GUI::StartLevelProxy::StartLevelProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::StartLevelProxy::Apply()
	{
		chGui->StartLevel();
	}

	CustomHero_GUI::ResetSlidersProxy::ResetSlidersProxy( const boost::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::ResetSlidersProxy::Apply()
	{
		chGui->ResetSliders();
	}

	const boost::shared_ptr<BobPhsxNormal> CustomHero_GUI::getNormalHero() const
	{
		return boost::dynamic_pointer_cast<BobPhsxNormal>( Hero );
	}

	CustomHero_GUI::CustomHero_GUI( const boost::shared_ptr<CustomLevel_GUI> &CustomLevel ) :
		Testing( false )
	{
	}
	boost::shared_ptr<CustomHero_GUI> CustomHero_GUI::CustomHero_GUI_Construct( const boost::shared_ptr<CustomLevel_GUI> &CustomLevel )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		this->CustomLevel = CustomLevel;

		CustomLevel->CallingPanel = boost::static_pointer_cast<GUI_Panel>( shared_from_this() );

		return boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() );
	}

	void CustomHero_GUI::OnAdd()
	{
		CkBaseMenu::OnAdd();

		MyGame->ForceTargetZoom = .001f;
		MyGame->DoForceZoom = true;
		MyGame->ForceLevelZoomBeforeDraw = .0007f;
	}

	void CustomHero_GUI::ReleaseBody()
	{
		MyGame->ForceTargetZoom = .0007f;
		CkBaseMenu::ReleaseBody();
	}

	void CustomHero_GUI::MakeSliders()
	{
		ItemPos = Vector2( -583.4305f, 698.1083f );
		PosAdd = Vector2( 0, -93.45f );

		PhsxSlider::Font = ItemFont;
		PhsxSlider::Process = boost::make_shared<AddItemProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) );

		AccelSlider = MakeMagic( PhsxSlider, ( Localization::Words_Acceleration, BobPhsx::CustomData_ACCEL ) );
		MaxSpeedSlider = MakeMagic( PhsxSlider, ( Localization::Words_MaxVelocity, BobPhsx::CustomData_MAXSPEED ) );
		SizeSlider = MakeMagic( PhsxSlider, ( Localization::Words_Size, BobPhsx::CustomData_SIZE ) );
		GravitySlider = MakeMagic( PhsxSlider, ( Localization::Words_Gravity, BobPhsx::CustomData_GRAVITY ) );
		MaxFallSpeedSlider = MakeMagic( PhsxSlider, ( Localization::Words_MaxFallSpeed, BobPhsx::CustomData_MAXFALL ) );
		FrictionSlider = MakeMagic( PhsxSlider, ( Localization::Words_Friction, BobPhsx::CustomData_FRICTION ) );
		JumpLengthSlider = MakeMagic( PhsxSlider, ( Localization::Words_JumpLength, BobPhsx::CustomData_JUMPLENGTH ) );
		JumpAccelSlider = MakeMagic( PhsxSlider, ( Localization::Words_JumpAcc, BobPhsx::CustomData_JUMPACCEL ) );

		NumJumpsSlider = MakeMagic( PhsxSlider, ( Localization::Words_NumJumps, BobPhsx::CustomData_NUMJUMPS ) );
		NumJumpsSlider->Discrete = true;
		DoubleJumpLengthSlider = MakeMagic( PhsxSlider, ( Localization::Words_DoubleJumpLength, BobPhsx::CustomData_JUMPLENGTH2 ) );
		DoubleJumpAccelSlider = MakeMagic( PhsxSlider, ( Localization::Words_DoubleJumpAccel, BobPhsx::CustomData_JUMPACCEL2 ) );

		JetPackSlider = MakeMagic( PhsxSlider, ( Localization::Words_JetpackAcc, BobPhsx::CustomData_JETPACKACCEL ) );
		JetPackFuelSlider = MakeMagic( PhsxSlider, ( Localization::Words_JetpackFuel, BobPhsx::CustomData_JETPACKFUEL ) );

		PhasedSizeSlider = MakeMagic( PhsxSlider, ( Localization::Words_PhasedSize, BobPhsx::CustomData_SIZE2 ) );
		PhasedGravitySlider = MakeMagic( PhsxSlider, ( Localization::Words_PhasedGravity, BobPhsx::CustomData_GRAVITY2 ) );
		PhasePeriodSlider = MakeMagic( PhsxSlider, ( Localization::Words_PhasePeriod, BobPhsx::CustomData_PHASEPERIOD ) );
	}

	void CustomHero_GUI::StartTest()
	{
		Hide();

		MakeBobPhsx();

		CreateHeroes();

		RemovePreviousGround();
		CreateGround();

		Testing = true;

		boost::shared_ptr<StartMenu_MW_CustomLevel> custom = boost::dynamic_pointer_cast<StartMenu_MW_CustomLevel>( CustomLevel );
		custom->Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_NONE );
	}

	void CustomHero_GUI::TestingPhsx()
	{
		if ( ButtonCheck::State( ControllerButtons_B, -1 ).Pressed )
			EndTest();
	}

	void CustomHero_GUI::EndTest()
	{
		boost::shared_ptr<StartMenu_MW_CustomLevel> custom = boost::dynamic_pointer_cast<StartMenu_MW_CustomLevel>( CustomLevel );
		custom->Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );

		Testing = false;
		Show();

		for ( BobVec::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
		{
			ParticleEffects::AddPop( MyGame->MyLevel, ( *bob )->getPos() );
			( *bob )->CollectSelf();
		}

		MyGame->AddToDo( boost::make_shared<MoveBlockAndKillProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) ), std::wstring( L"MoveOut" ), true, true );
	}

	bool CustomHero_GUI::MoveBlockAndKill()
	{
		if ( MyGame == 0 || MyGame->MyLevel == 0 )
			return true;

		for ( BlockVec::const_iterator block = MyGame->MyLevel->Blocks.begin(); block != MyGame->MyLevel->Blocks.end(); ++block )
			( *block )->Move( Vector2( 0, -20 ) );
		return false;
	}

	void CustomHero_GUI::KillBobs()
	{
		MyGame->WaitThenDo( 20, boost::make_shared<KillBobsHelper>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) ), std::wstring( L"RemoveBobs" ), false, true );
	}

	void CustomHero_GUI::MakeBobPhsx()
	{
		// Error check
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( Base ) != 0 )
		{
			Jump = BobPhsxNormal::getInstance();
		}

		// Make the hero
		Hero = MyGame->MyLevel->DefaultHeroType = BobPhsx::MakeCustom( Base, Size, Jump, BobPhsxNormal::getInstance() );

		//var data = new BobPhsx::CustomPhsxData();
		//data.Init(GravitySlider.Val, AccelSlider.Val, MaxSpeedSlider.Val, MaxFallSpeedSlider.Val, JumpLengthSlider.Val, DoubleJumpLengthSlider.Val, JumpAccelSlider.Val, DoubleJumpAccelSlider.Val, JetPackSlider.Val, JetPackFuelSlider.Val, NumJumpsSlider.Val, SizeSlider.Val, PhasedSizeSlider.Val, PhasedGravitySlider.Val, PhasePeriodSlider.Val, FrictionSlider.Val);
		Hero->SetCustomPhsx( HeroPhsxData );
	}

	void CustomHero_GUI::CreateHeroes()
	{
		// Remove any previous bobs
		MyGame->KillToDo( std::wstring( L"RemoveBobs" ) );
		for ( BobVec::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
			( *bob )->CollectSelf();

		// Make new bobs
		MyGame->MakeBobs( MyGame->MyLevel );

		// Position bobs
		Vector2 shift = Vector2( -700, 100 );
		for ( BobVec::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
		{
			Tools::MoveTo( *bob, MyGame->getCamPos() + shift );
			shift += Vector2( 100, 20 );

			( *bob )->ScreenWrap = true;
		}
	}

	void CustomHero_GUI::RemovePreviousGround()
	{
		MyGame->KillToDo( std::wstring( L"MoveOut" ) );

		for ( BlockVec::const_iterator block = MyGame->MyLevel->Blocks.begin(); block != MyGame->MyLevel->Blocks.end(); ++block )
			( *block )->CollectSelf();
	}

	void CustomHero_GUI::CreateGround()
	{
		MyGame->MyLevel->MyTileSet = TileSet::Get( std::wstring( L"castle" ) );

		boost::shared_ptr<NormalBlock> block;

		for ( BlockVec::const_iterator _block = MyGame->MyLevel->Blocks.begin(); _block != MyGame->MyLevel->Blocks.end(); ++_block )
			if ( boost::dynamic_pointer_cast<NormalBlock>( *_block ) != 0 )
				( *_block )->CollectSelf();

		block = boost::static_pointer_cast<NormalBlock>( MyGame->Recycle->GetObject( ObjectType_NORMAL_BLOCK, true ) );
		block->Init( Vector2( -1000, -3100 ), Vector2( 1100, 2500 ), MyGame->MyLevel->getMyTileSetInfo() );
		block->Reset( false );
		block->MyBox->TopOnly = false;
		MyGame->MyLevel->AddBlock( block );

		block = boost::static_pointer_cast<NormalBlock>( MyGame->Recycle->GetObject( ObjectType_NORMAL_BLOCK, true ) );
		block->Init( Vector2( 1050, -2950 ), Vector2( 1000, 2500 ), MyGame->MyLevel->getMyTileSetInfo() );
		block->Reset( false );
		block->MyBox->TopOnly = false;
		MyGame->MyLevel->AddBlock( block );
	}

	void CustomHero_GUI::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->ShadowColor = Color( .2f,.2f,.2f,.6f );
		text->Shadow = true;

		//text.Angle = CoreMath.Radians(23);
	}

	void CustomHero_GUI::SetSuperHeader( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );
		text->MyFloatColor = Vector4( 1, 1, 1, 1 );
		text->setScale( FontScale * 1.42f );

		text->Shadow = false;

		CkColorHelper::_x_x_HappyBlueColor( text );
		text->setScale( text->getScale() * 1.25f );
	}

	void CustomHero_GUI::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );
		StartMenu::SetItemProperties_Red( item );
	}

	boost::shared_ptr<MenuList> CustomHero_GUI::MakeList()
	{
		boost::shared_ptr<MenuList> list = MakeMagic( MenuList, () );
			MenuList_PostConstruct( list );

		list->GrayOutOnUnselectable = true;

		return list;
	}

	void CustomHero_GUI::AddItem( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::AddItem( item );

		boost::shared_ptr<MenuList> list = boost::dynamic_pointer_cast<MenuList>( item );
		if ( 0 != list )
		{
			list->SetIndex( 0 );
		}
	}

	void CustomHero_GUI::SetListItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		SetItemProperties( item );
	}

	void CustomHero_GUI::Init()
	{
		ItemShadows = false;

		SlideInFrom = SlideOutTo = PresetPos_RIGHT;

		FontScale = .5f;

		MyPile = boost::make_shared<DrawPile>();
		MyMenu = boost::make_shared<Menu>( false );
		EnsureFancy();

		CkBaseMenu::Init();

		setControl( -1 );
		MyMenu->OnB.reset();

		ReturnToCallerDelay = 18;
		SlideInLength = 25;
		SlideOutLength = 24;

		CallDelay = 5;

		SelectedItemShift = Vector2( 0, 0 );

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::Words_HeroFactory, Resources::Font_Grobold42 );
		HeaderText->Name = std::wstring( L"Header" );
		SetSuperHeader( HeaderText );
		HeaderText->setPos( Vector2( -1169.842f, 985.7144f ) );
		MyPile->Add( HeaderText );

		// Backdrop
		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1500x900" ), 1500.f, true );
		backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( backdrop );

		boost::shared_ptr<MenuItem> item;

		// Hero lists
		BaseHeader = HeroText = boost::make_shared<EzText>( Localization::Words_Base, ItemFont );
		HeroText->Name = std::wstring( L"base" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );

		BaseList = MakeList();
		BaseList->Name = std::wstring( L"base" );
		for ( Hero_BaseType _hero = static_cast<Hero_BaseType>( 0 ); _hero != Hero_BaseType_LENGTH; Incr( _hero ) )
		{
			if ( _hero == Hero_BaseType_MEAT ) continue;

			boost::shared_ptr<BobPhsx> hero = BobPhsx::GetPhsx_Base( _hero );

			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( hero->Name, ItemFont, false, true ) ) );
			SetListItemProperties( item );
			BaseList->AddItem( item, hero );
		}
		AddItem( BaseList );

		// Hero jump
		JumpHeader = HeroText = boost::make_shared<EzText>( Localization::Words_Jump, ItemFont );
		HeroText->Name = std::wstring( L"jump" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );

		JumpList = MakeList();
		JumpList->Name = std::wstring( L"jump" );
		for ( Hero_MoveMod _hero = static_cast<Hero_MoveMod>( 0 ); _hero != Hero_MoveMod_LENGTH; Incr( _hero ) )
		{
			boost::shared_ptr<BobPhsx> hero = BobPhsx::GetPhsx_Move( _hero );

			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( hero->Name, ItemFont, false, true ) ) );
			SetListItemProperties( item );
			JumpList->AddItem( item, hero );
		}
		AddItem( JumpList );

		// Hero shape
		SizeHeader = HeroText = boost::make_shared<EzText>( Localization::Words_Shape, ItemFont );
		HeroText->Name = std::wstring( L"size" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );

		SizeList = MakeList();
		SizeList->Name = std::wstring( L"size" );
		for ( Hero_Shape _hero = static_cast<Hero_Shape>( 0 ); _hero < Hero_Shape_LENGTH; Incr( _hero ) )
		//for ( IEnumerable<T*>::const_iterator _hero = Tools::GetValues<Hero_Shape>()->begin(); _hero != Tools::GetValues<Hero_Shape>()->end(); ++_hero )
		{
			boost::shared_ptr<BobPhsx> hero = BobPhsx::GetPhsx_Shape( _hero );

			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( hero->Name, ItemFont, false, true ) ) );
			SetListItemProperties( item );
			SizeList->AddItem( item, hero );
		}

		AddItem( SizeList );

		SetListActions();

		BaseList->SetIndex( BaseListIndex );
		SizeList->SetIndex( SizeListIndex );
		JumpList->SetIndex( JumpListIndex );

		FontScale = 1;

		MakeSliders();

		// Start/test/back/advanced
		MakeOptionItems();

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		UpdateSliders();

		SetPos();
	}

	void CustomHero_GUI::SetListActions()
	{
		BaseList->OnIndexSelect = boost::make_shared<UpdateBaseHeroProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) );
		SizeList->OnIndexSelect = boost::make_shared<UpdateSizeHeroProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) );
		JumpList->OnIndexSelect = boost::make_shared<UpdateJumpHeroProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) );
	}

	void CustomHero_GUI::UpdateSliders()
	{
		if ( GravitySlider == 0 )
			return;

		BaseList->Selectable = true;
		JumpList->Selectable = true;
		SizeList->Selectable = true;

		GravitySlider->Selectable = true;
		MaxSpeedSlider->Selectable = true;
		AccelSlider->Selectable = true;
		MaxFallSpeedSlider->Selectable = true;
		JumpLengthSlider->Selectable = true;
		JumpAccelSlider->Selectable = true;
		DoubleJumpLengthSlider->Selectable = true;
		DoubleJumpAccelSlider->Selectable = true;
		FrictionSlider->Selectable = true;
		JetPackSlider->Selectable = true;
		JetPackFuelSlider->Selectable = true;
		NumJumpsSlider->Selectable = true;
		SizeSlider->Selectable = true;
		PhasedSizeSlider->Selectable = true;
		PhasedGravitySlider->Selectable = true;
		PhasePeriodSlider->Selectable = true;

		// Base
		if ( Base == BobPhsxNormal::getInstance() || Base == BobPhsxWheel::getInstance() || Base == BobPhsxBox::getInstance() || Base == BobPhsxBouncy::getInstance() || Base == BobPhsxMeat::getInstance() || Base == BobPhsxRocketbox::getInstance() )
		{

		}
		else if ( Base == BobPhsxSpaceship::getInstance() )
		{
			GravitySlider->Selectable &= false;
			MaxFallSpeedSlider->Selectable &= false;
			JumpLengthSlider->Selectable &= false;
			JumpAccelSlider->Selectable &= false;
			DoubleJumpLengthSlider->Selectable &= false;
			DoubleJumpAccelSlider->Selectable &= false;
			JetPackSlider->Selectable &= false;
			JetPackFuelSlider->Selectable &= false;
			NumJumpsSlider->Selectable &= false;

			JumpList->Selectable &= false;
		}
		else if ( Base == BobPhsxMeat::getInstance() )
		{

		}

		// Jump 
		if ( Jump == BobPhsxNormal::getInstance() )
		{
			DoubleJumpLengthSlider->Selectable &= false;
			DoubleJumpAccelSlider->Selectable &= false;
			NumJumpsSlider->Selectable &= false;
			JetPackSlider->Selectable &= false;
			JetPackFuelSlider->Selectable &= false;
		}
		else if ( Jump == BobPhsxDouble::getInstance() )
		{
			JetPackSlider->Selectable &= false;
			JetPackFuelSlider->Selectable &= false;
		}
		else if ( Jump == BobPhsxJetman::getInstance() )
		{
			DoubleJumpLengthSlider->Selectable &= false;
			DoubleJumpAccelSlider->Selectable &= false;
			NumJumpsSlider->Selectable &= false;
		}
		else if ( Jump == BobPhsxInvert::getInstance() )
		{
			DoubleJumpLengthSlider->Selectable &= false;
			DoubleJumpAccelSlider->Selectable &= false;
			NumJumpsSlider->Selectable &= false;
			JetPackSlider->Selectable &= false;
			JetPackFuelSlider->Selectable &= false;
		}

		// Shape
		if ( Size == BobPhsxNormal::getInstance() || Size == BobPhsxBig::getInstance() || Size == BobPhsxSmall::getInstance() )
		{
			PhasedSizeSlider->Selectable &= false;
			PhasedGravitySlider->Selectable &= false;
			PhasePeriodSlider->Selectable &= false;
		}
		else if ( Size == BobPhsxScale::getInstance() )
		{

		}
	}

	void CustomHero_GUI::UpdateBaseHero()
	{
		Base = boost::dynamic_pointer_cast<BobPhsx>( BaseList->getCurObj() );
		BaseListIndex = BaseList->ListIndex;

		UpdateSliders();
	}

	void CustomHero_GUI::UpdateSizeHero()
	{
		Size = boost::dynamic_pointer_cast<BobPhsx>( SizeList->getCurObj() );
		SizeListIndex = SizeList->ListIndex;

		UpdateSliders();
	}

	void CustomHero_GUI::UpdateJumpHero()
	{
		Jump = boost::dynamic_pointer_cast<BobPhsx>( JumpList->getCurObj() );
		JumpListIndex = JumpList->ListIndex;

		UpdateSliders();
	}

	void CustomHero_GUI::SetPos()
        {
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"base" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1655.38f, 642.6317f ) ); _item->MyText->setScale( 0.5f ); _item->MySelectedText->setScale( 0.5f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"jump" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1653.446f, 451.6321f ) ); _item->MyText->setScale( 0.5f ); _item->MySelectedText->setScale( 0.5f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"size" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1656.223f, 256.2355f ) ); _item->MyText->setScale( 0.5f ); _item->MySelectedText->setScale( 0.5f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"test" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1914.311f, 134.3449f ) ); _item->MyText->setScale( 0.7685415f ); _item->MySelectedText->setScale( 0.7685415f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"back" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1909.15f, -90.52583f ) ); _item->MyText->setScale( 0.6955291f ); _item->MySelectedText->setScale( 0.6955291f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"continue" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1915.104f, -288.0107f ) ); _item->MyText->setScale( 0.7520385f ); _item->MySelectedText->setScale( 0.7520385f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"reset" ); if (_item != 0 ) { _item->setSetPos( Vector2(-1916.694f, -502.1649f ) ); _item->MyText->setScale( 0.7f ); _item->MySelectedText->setScale( 0.7f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2( 1166.862f, -69.45605f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-664.2021f, 960.7101f ) ); _t->setScale( 0.8010691f ); }
			_t = MyPile->FindEzText( L"base" ); if (_t != 0 ) { _t->setPos( Vector2(-1269.655f, 708.4517f ) ); _t->setScale( 0.6189448f ); }
			_t = MyPile->FindEzText( L"jump" ); if (_t != 0 ) { _t->setPos( Vector2(-1270.534f, 507.2669f ) ); _t->setScale( 0.5981081f ); }
			_t = MyPile->FindEzText( L"size" ); if (_t != 0 ) { _t->setPos( Vector2(-1234.811f, 317.9383f ) ); _t->setScale( 0.6634525f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1500.f, 1083.871f ) ); }
			_q = MyPile->FindQuad( L"Button_A" ); if (_q != 0 ) { _q->setPos( Vector2(-830.694f, -77.78476f ) ); _q->setSize( Vector2( 84.f, 84.f ) ); }
			_q = MyPile->FindQuad( L"Button_B" ); if (_q != 0 ) { _q->setPos( Vector2(-830.694f, -297.2718f ) ); _q->setSize( Vector2( 84.f, 84.f ) ); }
			_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-830.694f, -505.6396f ) ); _q->setSize( Vector2( 84.f, 84.f ) ); }
			_q = MyPile->FindQuad( L"Button_Y" ); if (_q != 0 ) { _q->setPos( Vector2(-830.694f, -702.895f ) ); _q->setSize( Vector2( 84.f, 84.f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
		}

	void CustomHero_GUI::MakeOptionItems()
	{
		boost::shared_ptr<MenuItem> item;

		float bigscale = .52f;
		float scale = .52f;
		
		bool WithButtonPics;
if (ButtonCheck::ControllerInUse)
{
		WithButtonPics = true;
}
else
{
		WithButtonPics = false;            
}

            // Start
            A = Start = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words::Words_Test, ItemFont ) ) );
            item->Name = L"test";
            item->JiggleOnGo = false;
            AddItem( item );
            item->setGo( Cast::ToItem( boost::make_shared<StartTestProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) ) ) );
if ( ButtonCheck::ControllerInUse )
{
#if XBOX || PC_VERSION
			Menu::DefaultMenuInfo::SetNext( item );
#endif
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.0f, std::wstring( L"Button_A" ) ) );
            item->Selectable = false;
}

            // Select 'Start Level' when the user presses ( A )
            MyMenu->OnA = Cast::ToMenu( Start->getGo() );


            // Back
            B = Back = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words::Words_Back, ItemFont ) ) );
            item->Name = L"back";
            AddItem( item );
            item->SelectSound = 0;
            item->setGo( Cast::ToItem( boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<CkBaseMenu>( shared_from_this() ) ) ) );
if ( ButtonCheck::ControllerInUse )
{
#if XBOX || PC_VERSION
			Menu::DefaultMenuInfo::SetBack( item );
#endif
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 90.0f, std::wstring( L"Button_B" ) ) );
            item->Selectable = false;
}

            // Continue
            X = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words::Words_Play, ItemFont ) ) );
            item->Name = L"continue";
            AddItem( item );
            item->SelectSound = 0;
			item->setGo( Cast::ToItem( boost::make_shared<NextProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) ) ) );
if ( ButtonCheck::ControllerInUse )
{
#if XBOX || PC_VERSION
			Menu::DefaultMenuInfo::SetX( item );
#endif
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.f, std::wstring( L"Button_X" ) ) );
            item->Selectable = false;
            MyMenu->OnX = Cast::ToMenu( X->getGo() );
}

            // Reset
            item = ResetButton = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words::Words_Reset, ItemFont ) ) );
            item->Name = L"reset";
            AddItem( item );
			item->setGo( Cast::ToItem( boost::make_shared<ResetSlidersProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) ) ));
if ( ButtonCheck::ControllerInUse )
{
#if XBOX || PC_VERSION
			Menu::DefaultMenuInfo::SetY( item );
#endif
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getY(), 90.0f, std::wstring( L"Button_Y" ) ) );
            item->Selectable = false;
            MyMenu->OnY = Cast::ToAction( item->getGo() );
}
	}

	bool CustomHero_GUI::AdvancedAvailable()
	{
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( Base ) != 0 && !( boost::dynamic_pointer_cast<BobPhsxScale>( Size ) != 0 ) )
			return false;
		else
			return true;
	}

	void CustomHero_GUI::ResetAdvancedSliders()
	{
		MaxFallSpeedSlider->Show = JumpLengthSlider->Show = JumpAccelSlider->Show = FrictionSlider->Show = true;

		DoubleJumpAccelSlider->Show = DoubleJumpLengthSlider->Show = NumJumpsSlider->Show = boost::dynamic_pointer_cast<BobPhsxDouble>( Jump ) != 0 && boost::dynamic_pointer_cast<BobPhsxNormal>( Base ) != 0;

		JetPackFuelSlider->Show = JetPackSlider->Show = boost::dynamic_pointer_cast<BobPhsxJetman>( Jump ) != 0 && boost::dynamic_pointer_cast<BobPhsxNormal>( Base ) != 0;

		SizeSlider->Show = PhasedSizeSlider->Show = PhasedGravitySlider->Show = PhasePeriodSlider->Show = boost::dynamic_pointer_cast<BobPhsxScale>( Size ) != 0;

		GravitySlider->Show = boost::dynamic_pointer_cast<BobPhsxNormal>( Base ) != 0;
	}

	void CustomHero_GUI::Next()
	{
		if ( CustomLevel->IsCustomDifficulty() )
		{
			MakeBobPhsx();
			CustomLevel->LevelSeed->DefaultHeroType = Hero;

			CustomLevel->CallingPanel = MakeMagic( PassiveUpgrades_GUI, ( CustomLevel->PieceSeed, CustomLevel ) );
			Call( CustomLevel->CallingPanel, 0 );
			Hide( PresetPos_LEFT );
			this->SlideInFrom = PresetPos_LEFT;
		}
		else
		{
			MyGame->PlayGame( boost::make_shared<StartLevelProxy>( boost::static_pointer_cast<CustomHero_GUI>( shared_from_this() ) ) );
		}
	}

	void CustomHero_GUI::StartLevel()
	{
		MakeBobPhsx();
		CustomLevel->LevelSeed->DefaultHeroType = Hero;
		CustomLevel->StartLevelFromMenuData();
	}

	void CustomHero_GUI::ResetSliders()
	{
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<PhsxSlider> slider = boost::dynamic_pointer_cast<PhsxSlider>( *item );
			if ( 0 != slider )
				slider->Reset();
		}
	}

	void CustomHero_GUI::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();
	}

	void CustomHero_GUI::MyPhsxStep()
	{
		if ( Testing )
		{
			TestingPhsx();
			return;
		}

		CkBaseMenu::MyPhsxStep();
	}

	void CustomHero_GUI::InitializeInstanceFields()
	{
		Testing = false;
	}
}
