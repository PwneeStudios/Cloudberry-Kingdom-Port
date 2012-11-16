#include <global_header.h>
namespace CloudberryKingdom
{

	CustomHero_GUI::StartTestProxy::StartTestProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::StartTestProxy::Apply()
	{
		chGui->StartTest();
	}

	CustomHero_GUI::MoveBlockAndKillProxy::MoveBlockAndKillProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	bool CustomHero_GUI::MoveBlockAndKillProxy::Apply()
	{
		return chGui->MoveBlockAndKill();
	}

	CustomHero_GUI::KillBobsHelper::KillBobsHelper( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::KillBobsHelper::Apply()
	{
		for ( std::vector<Bob*>::const_iterator bob = chGui->MyGame->MyLevel->Bobs.begin(); bob != chGui->MyGame->MyLevel->Bobs.end(); ++bob )
			( *bob )->Die( Bob::BobDeathType_NONE );
	}

	CustomHero_GUI::AddItemProxy::AddItemProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::AddItemProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		chGui->AddItem( item );
	}

	CustomHero_GUI::UpdateBaseHeroProxy::UpdateBaseHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::UpdateBaseHeroProxy::Apply()
	{
		chGui->UpdateBaseHero();
	}

	CustomHero_GUI::UpdateSizeHeroProxy::UpdateSizeHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::UpdateSizeHeroProxy::Apply()
	{
		chGui->UpdateSizeHero();
	}

	CustomHero_GUI::UpdateJumpHeroProxy::UpdateJumpHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::UpdateJumpHeroProxy::Apply()
	{
		chGui->UpdateJumpHero();
	}

	CustomHero_GUI::NextProxy::NextProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::NextProxy::Apply()
	{
		chGui->Next();
	}

	CustomHero_GUI::StartLevelProxy::StartLevelProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::StartLevelProxy::Apply()
	{
		chGui->StartLevel();
	}

	CustomHero_GUI::ResetSlidersProxy::ResetSlidersProxy( const std::shared_ptr<CustomHero_GUI> &chGui )
	{
		this->chGui = chGui;
	}

	void CustomHero_GUI::ResetSlidersProxy::Apply()
	{
		chGui->ResetSliders();
	}

BobPhsx::CustomPhsxData CustomHero_GUI::HeroPhsxData = 0;
std::shared_ptr<BobPhsx> CustomHero_GUI::Hero = 0;

	const std::shared_ptr<BobPhsxNormal> &CustomHero_GUI::getNormalHero() const
	{
		return dynamic_cast<BobPhsxNormal*>( Hero );
	}

	CustomHero_GUI::CustomHero_GUI( const std::shared_ptr<CustomLevel_GUI> &CustomLevel )
	{
		InitializeInstanceFields();
		this->CustomLevel = CustomLevel;

		CustomLevel->CallingPanel = this;
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
		PhsxSlider::Process = std::make_shared<AddItemProxy>( this );

		AccelSlider = std::make_shared<PhsxSlider>( Localization::Words_ACCELERATION, BobPhsx::CustomData_ACCEL );
		MaxSpeedSlider = std::make_shared<PhsxSlider>( Localization::Words_MAX_VELOCITY, BobPhsx::CustomData_MAXSPEED );
		SizeSlider = std::make_shared<PhsxSlider>( Localization::Words_SIZE, BobPhsx::CustomData_SIZE );
		GravitySlider = std::make_shared<PhsxSlider>( Localization::Words_GRAVITY, BobPhsx::CustomData_GRAVITY );
		MaxFallSpeedSlider = std::make_shared<PhsxSlider>( Localization::Words_MAX_FALL_SPEED, BobPhsx::CustomData_MAXFALL );
		FrictionSlider = std::make_shared<PhsxSlider>( Localization::Words_FRICTION, BobPhsx::CustomData_FRICTION );
		JumpLengthSlider = std::make_shared<PhsxSlider>( Localization::Words_JUMP_LENGTH, BobPhsx::CustomData_JUMPLENGTH );
		JumpAccelSlider = std::make_shared<PhsxSlider>( Localization::Words_JUMP_ACC, BobPhsx::CustomData_JUMPACCEL );

		NumJumpsSlider = std::make_shared<PhsxSlider>( Localization::Words_NUM_JUMPS, BobPhsx::CustomData_NUMJUMPS );
		NumJumpsSlider->Discrete = true;
		DoubleJumpLengthSlider = std::make_shared<PhsxSlider>( Localization::Words_DOUBLE_JUMP_LENGTH, BobPhsx::CustomData_JUMPLENGTH2 );
		DoubleJumpAccelSlider = std::make_shared<PhsxSlider>( Localization::Words_DOUBLE_JUMP_ACCEL, BobPhsx::CustomData_JUMPACCEL2 );

		JetPackSlider = std::make_shared<PhsxSlider>( Localization::Words_JETPACK_ACC, BobPhsx::CustomData_JETPACKACCEL );
		JetPackFuelSlider = std::make_shared<PhsxSlider>( Localization::Words_JETPACK_FUEL, BobPhsx::CustomData_JETPACKFUEL );

		PhasedSizeSlider = std::make_shared<PhsxSlider>( Localization::Words_PHASED_SIZE, BobPhsx::CustomData_SIZE2 );
		PhasedGravitySlider = std::make_shared<PhsxSlider>( Localization::Words_PHASED_GRAVITY, BobPhsx::CustomData_GRAVITY2 );
		PhasePeriodSlider = std::make_shared<PhsxSlider>( Localization::Words_PHASE_PERIOD, BobPhsx::CustomData_PHASEPERIOD );
	}

	void CustomHero_GUI::StartTest()
	{
		Hide();

		MakeBobPhsx();

		CreateHeroes();

		RemovePreviousGround();
		CreateGround();

		Testing = true;

		std::shared_ptr<StartMenu_MW_CustomLevel> custom = dynamic_cast<StartMenu_MW_CustomLevel*>( CustomLevel );
		custom->Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_NONE );
	}

	void CustomHero_GUI::TestingPhsx()
	{
		if ( ButtonCheck::State( ControllerButtons_B, -1 ).Pressed )
			EndTest();
	}

	void CustomHero_GUI::EndTest()
	{
		std::shared_ptr<StartMenu_MW_CustomLevel> custom = dynamic_cast<StartMenu_MW_CustomLevel*>( CustomLevel );
		custom->Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );

		Testing = false;
		Show();

		for ( std::vector<Bob*>::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
		{
			ParticleEffects::AddPop( MyGame->MyLevel, ( *bob )->getPos() );
			( *bob )->CollectSelf();
		}

		MyGame->AddToDo( std::make_shared<MoveBlockAndKillProxy>( this ), _T( "MoveOut" ), true, true );
	}

	bool CustomHero_GUI::MoveBlockAndKill()
	{
		if ( MyGame == 0 || MyGame->MyLevel == 0 )
			return true;

		for ( std::vector<BlockBase*>::const_iterator block = MyGame->MyLevel->Blocks.begin(); block != MyGame->MyLevel->Blocks.end(); ++block )
			( *block )->Move( Vector2( 0, -20 ) );
		return false;
	}

	void CustomHero_GUI::KillBobs()
	{
		MyGame->WaitThenDo( 20, std::make_shared<KillBobsHelper>( this ), _T( "RemoveBobs" ), false, true );
	}

	void CustomHero_GUI::MakeBobPhsx()
	{
		// Error check
		if ( dynamic_cast<BobPhsxSpaceship*>( Base ) != 0 )
		{
			Jump = BobPhsxNormal::getInstance();
		}

		// Make the hero
		Hero = MyGame->MyLevel->DefaultHeroType = BobPhsx::MakeCustom( Base, Size, Jump, BobPhsxNormal::getInstance() );

		//var data = new BobPhsx.CustomPhsxData();
		//data.Init(GravitySlider.Val, AccelSlider.Val, MaxSpeedSlider.Val, MaxFallSpeedSlider.Val, JumpLengthSlider.Val, DoubleJumpLengthSlider.Val, JumpAccelSlider.Val, DoubleJumpAccelSlider.Val, JetPackSlider.Val, JetPackFuelSlider.Val, NumJumpsSlider.Val, SizeSlider.Val, PhasedSizeSlider.Val, PhasedGravitySlider.Val, PhasePeriodSlider.Val, FrictionSlider.Val);
		Hero->SetCustomPhsx( HeroPhsxData );
	}

	void CustomHero_GUI::CreateHeroes()
	{
		// Remove any previous bobs
		MyGame->KillToDo( _T( "RemoveBobs" ) );
		for ( std::vector<Bob*>::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
			( *bob )->CollectSelf();

		// Make new bobs
		MyGame->MakeBobs( MyGame->MyLevel );

		// Position bobs
		Vector2 shift = Vector2( -700, 100 );
		for ( std::vector<Bob*>::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
		{
			Tools::MoveTo( *bob, MyGame->getCamPos() + shift );
			shift += Vector2( 100, 20 );

			( *bob )->ScreenWrap = true;
		}
	}

	void CustomHero_GUI::RemovePreviousGround()
	{
		MyGame->KillToDo( _T( "MoveOut" ) );

		for ( std::vector<BlockBase*>::const_iterator block = MyGame->MyLevel->Blocks.begin(); block != MyGame->MyLevel->Blocks.end(); ++block )
			( *block )->CollectSelf();
	}

	void CustomHero_GUI::CreateGround()
	{
		MyGame->MyLevel->MyTileSet = _T( "castle" );

		std::shared_ptr<NormalBlock> block;

		for ( std::vector<BlockBase*>::const_iterator _block = MyGame->MyLevel->Blocks.begin(); _block != MyGame->MyLevel->Blocks.end(); ++_block )
			if ( dynamic_cast<NormalBlock*>( *_block ) != 0 )
				( *_block )->CollectSelf();

		block = static_cast<NormalBlock*>( MyGame->Recycle->GetObject( ObjectType_NORMAL_BLOCK, false ) );
		block->Init( Vector2( -1000, -3100 ), Vector2( 1100, 2500 ), MyGame->MyLevel->getMyTileSetInfo() );
		block->MyBox->TopOnly = false;
		MyGame->MyLevel->AddBlock( block );

		block = static_cast<NormalBlock*>( MyGame->Recycle->GetObject( ObjectType_NORMAL_BLOCK, false ) );
		block->Init( Vector2( 1050, -2950 ), Vector2( 1000, 2500 ), MyGame->MyLevel->getMyTileSetInfo() );
		block->MyBox->TopOnly = false;
		MyGame->MyLevel->AddBlock( block );
	}

	void CustomHero_GUI::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->ShadowColor = Color( .2f,.2f,.2f,.6f );
		text->Shadow = true;

		//text.Angle = CoreMath.Radians(23);
	}

	void CustomHero_GUI::SetSuperHeader( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );
		text->MyFloatColor = Vector4( 1, 1, 1, 1 );
		text->setScale( FontScale * 1.42f );

		text->Shadow = false;

		CkColorHelper::_x_x_HappyBlueColor( text );
		text->setScale( text->getScale() * 1.25f );
	}

	void CustomHero_GUI::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );
		StartMenu::SetItemProperties_Red( item );
	}

	std::shared_ptr<MenuList> CustomHero_GUI::MakeList()
	{
		std::shared_ptr<MenuList> list = std::make_shared<MenuList>();

		list->GrayOutOnUnselectable = true;

		return list;
	}

	void CustomHero_GUI::AddItem( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::AddItem( item );

		std::shared_ptr<MenuList> list = dynamic_cast<MenuList*>( item );
		if ( 0 != list )
		{
			list->SetIndex( 0 );
		}
	}

	void CustomHero_GUI::SetListItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		SetItemProperties( item );
	}

int CustomHero_GUI::BaseListIndex = 0;
int CustomHero_GUI::SizeListIndex = 0;
int CustomHero_GUI::JumpListIndex = 0;

	void CustomHero_GUI::Init()
	{
		ItemShadows = false;

		SlideInFrom = SlideOutTo = PresetPos_RIGHT;

		FontScale = .5f;

		MyPile = std::make_shared<DrawPile>();
		MyMenu = std::make_shared<Menu>( false );
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
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Localization::Words_HERO_FACTORY, Resources::Font_Grobold42 );
		HeaderText->Name = _T( "Header" );
		SetSuperHeader( HeaderText );
		HeaderText->setPos( Vector2( -1169.842f, 985.7144f ) );
		MyPile->Add( HeaderText );

		// Backdrop
		std::shared_ptr<QuadClass> backdrop = std::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 1500, true );
		backdrop->Name = _T( "Backdrop" );
		MyPile->Add( backdrop );

		std::shared_ptr<MenuItem> item;

		// Hero lists
		BaseHeader = HeroText = std::make_shared<EzText>( Localization::Words_BASE, ItemFont );
		HeroText->Name = _T( "base" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );

		BaseList = MakeList();
		BaseList->Name = _T( "base" );
		for ( IEnumerable<T*>::const_iterator _hero = Tools::GetValues<Hero_BaseType>()->begin(); _hero != Tools::GetValues<Hero_BaseType>()->end(); ++_hero )
		{
			std::shared_ptr<BobPhsx> hero = BobPhsx::GetPhsx( *_hero );

			item = std::make_shared<MenuItem>( std::make_shared<EzText>( hero->Name, ItemFont, false, true ) );
			SetListItemProperties( item );
			BaseList->AddItem( item, hero );
		}
		AddItem( BaseList );

		// Hero jump
		JumpHeader = HeroText = std::make_shared<EzText>( Localization::Words_JUMP, ItemFont );
		HeroText->Name = _T( "jump" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );

		JumpList = MakeList();
		JumpList->Name = _T( "jump" );
		for ( IEnumerable<T*>::const_iterator _hero = Tools::GetValues<Hero_MoveMod>()->begin(); _hero != Tools::GetValues<Hero_MoveMod>()->end(); ++_hero )
		{
			std::shared_ptr<BobPhsx> hero = BobPhsx::GetPhsx( *_hero );

			item = std::make_shared<MenuItem>( std::make_shared<EzText>( hero->Name, ItemFont, false, true ) );
			SetListItemProperties( item );
			JumpList->AddItem( item, hero );
		}
		AddItem( JumpList );

		// Hero shape
		SizeHeader = HeroText = std::make_shared<EzText>( Localization::Words_SHAPE, ItemFont );
		HeroText->Name = _T( "size" );
		SetHeaderProperties( HeroText );
		MyPile->Add( HeroText );

		SizeList = MakeList();
		SizeList->Name = _T( "size" );
		for ( IEnumerable<T*>::const_iterator _hero = Tools::GetValues<Hero_Shape>()->begin(); _hero != Tools::GetValues<Hero_Shape>()->end(); ++_hero )
		{
			std::shared_ptr<BobPhsx> hero = BobPhsx::GetPhsx( *_hero );

			item = std::make_shared<MenuItem>( std::make_shared<EzText>( hero->Name, ItemFont, false, true ) );
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
		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		UpdateSliders();

		SetPos();
	}

	void CustomHero_GUI::SetListActions()
	{
		BaseList->OnIndexSelect = std::make_shared<UpdateBaseHeroProxy>( this );
		SizeList->OnIndexSelect = std::make_shared<UpdateSizeHeroProxy>( this );
		JumpList->OnIndexSelect = std::make_shared<UpdateJumpHeroProxy>( this );
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
		Base = dynamic_cast<BobPhsx*>( BaseList->getCurObj() );
		BaseListIndex = BaseList->ListIndex;

		UpdateSliders();
	}

	void CustomHero_GUI::UpdateSizeHero()
	{
		Size = dynamic_cast<BobPhsx*>( SizeList->getCurObj() );
		SizeListIndex = SizeList->ListIndex;

		UpdateSliders();
	}

	void CustomHero_GUI::UpdateJumpHero()
	{
		Jump = dynamic_cast<BobPhsx*>( JumpList->getCurObj() );
		JumpListIndex = JumpList->ListIndex;

		UpdateSliders();
	}

	void CustomHero_GUI::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "base" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1655.38f, 642.6317f ) );
			_item->MyText->setScale( 0.5f );
			_item->MySelectedText->setScale( 0.5f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "jump" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1653.446f, 451.6321f ) );
			_item->MyText->setScale( 0.5f );
			_item->MySelectedText->setScale( 0.5f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "size" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1656.223f, 256.2355f ) );
			_item->MyText->setScale( 0.5f );
			_item->MySelectedText->setScale( 0.5f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "test" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1914.311f, 134.3449f ) );
			_item->MyText->setScale( 0.7685415f );
			_item->MySelectedText->setScale( 0.7685415f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1909.15f, -90.52583f ) );
			_item->MyText->setScale( 0.6955291f );
			_item->MySelectedText->setScale( 0.6955291f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "continue" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1915.104f, -288.0107f ) );
			_item->MyText->setScale( 0.7520385f );
			_item->MySelectedText->setScale( 0.7520385f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "reset" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1916.694f, -502.1649f ) );
			_item->MyText->setScale( 0.7f );
			_item->MySelectedText->setScale( 0.7f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 1166.862f, -69.45605f ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -664.2021f, 960.7101f ) );
			_t->setScale( 0.8010691f );
		}
		_t = MyPile->FindEzText( _T( "base" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1269.655f, 708.4517f ) );
			_t->setScale( 0.6189448f );
		}
		_t = MyPile->FindEzText( _T( "jump" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1270.534f, 507.2669f ) );
			_t->setScale( 0.5981081f );
		}
		_t = MyPile->FindEzText( _T( "size" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1234.811f, 317.9383f ) );
			_t->setScale( 0.6634525f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1500, 1083.871f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}

	void CustomHero_GUI::MakeOptionItems()
	{
		std::shared_ptr<MenuItem> item;

		float bigscale = .52f;
		float scale = .52f;

	#if defined(PC_VERSION)
		bool WithButtonPics = false;
	#else
		bool WithButtonPics = true;
	#endif

		// Start
		if ( WithButtonPics )
		{
			MyPile->Add( std::make_shared<QuadClass>( ButtonTexture::getGo(), 90, _T("Button_A") ) );
			A = Start = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_TEST, ItemFont ) );
		}
		else
			A = Start = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_TEST, ItemFont ) );
		item->Name = _T( "test" );
		item->JiggleOnGo = false;
		AddItem( item );
		item->setGo( Cast::ToItem( std::make_shared<StartTestProxy>( this ) ) );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;
	#if defined(NOT_PC)
		item->Selectable = false;
	#endif

		// Select 'Start Level' when the user presses (A)
		MyMenu->OnA = Cast::ToMenu( Start->getGo() );


		// Back
		if ( WithButtonPics )
		{
			MyPile->Add( std::make_shared<QuadClass>( ButtonTexture::getBack(), 90, _T("Button_B") ) );
			B = Back = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_BACK, ItemFont ) );
		}
		else
			B = Back = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_BACK, ItemFont ) );
		item->Name = _T( "back" );
		AddItem( item );
		item->SelectSound.reset();
		item->setGo( Cast::ToItem( std::make_shared<ReturnToCallerProxy>( this ) ) );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
	#if defined(NOT_PC)
		item->Selectable = false;
	#endif

		// Continue
		if ( WithButtonPics )
		{
			MyPile->Add( std::make_shared<QuadClass>( ButtonTexture::getX(), 90, _T("Button_X") ) );
			X = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_PLAY, ItemFont ) );
		}
		else
			X = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_PLAY, ItemFont ) );

		item->Name = _T( "continue" );
		AddItem( item );
		item->SelectSound.reset();
		item->MyText->MyFloatColor = ( Color( 204, 220, 255 ) ).ToVector4() *.93f;
		item->MySelectedText->MyFloatColor = ( Color( 204, 220, 255 ) ).ToVector4();
	#if defined(NOT_PC)
		item->Selectable = false;
		MyMenu->OnX = Cast::ToMenu( X->getGo() );
	#endif
		item->setGo( Cast::ToItem( std::make_shared<NextProxy>( this ) ) );

		// Reset
		item = ResetButton = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_RESET, ItemFont ) );
		item->Name = _T( "reset" );
		AddItem( item );
		item->setGo( Cast::ToItem( std::make_shared<ResetSlidersProxy>( this ) ) );
	}

	bool CustomHero_GUI::AdvancedAvailable()
	{
		if ( dynamic_cast<BobPhsxSpaceship*>( Base ) != 0 && !( dynamic_cast<BobPhsxScale*>( Size ) != 0 ) )
			return false;
		else
			return true;
	}

	void CustomHero_GUI::ResetAdvancedSliders()
	{
		MaxFallSpeedSlider->Show = JumpLengthSlider->Show = JumpAccelSlider->Show = FrictionSlider->Show = true;

		DoubleJumpAccelSlider->Show = DoubleJumpLengthSlider->Show = NumJumpsSlider->Show = dynamic_cast<BobPhsxDouble*>( Jump ) != 0 && dynamic_cast<BobPhsxNormal*>( Base ) != 0;

		JetPackFuelSlider->Show = JetPackSlider->Show = dynamic_cast<BobPhsxJetman*>( Jump ) != 0 && dynamic_cast<BobPhsxNormal*>( Base ) != 0;

		SizeSlider->Show = PhasedSizeSlider->Show = PhasedGravitySlider->Show = PhasePeriodSlider->Show = dynamic_cast<BobPhsxScale*>( Size ) != 0;

		GravitySlider->Show = dynamic_cast<BobPhsxNormal*>( Base ) != 0;
	}

	void CustomHero_GUI::Next()
	{
		if ( CustomLevel->IsCustomDifficulty() )
		{
			MakeBobPhsx();
			CustomLevel->LevelSeed->DefaultHeroType = Hero;

			CustomLevel->CallingPanel = std::make_shared<PassiveUpgrades_GUI>( CustomLevel->PieceSeed, CustomLevel );
			Call( CustomLevel->CallingPanel, 0 );
			Hide( PresetPos_LEFT );
			this->SlideInFrom = PresetPos_LEFT;
		}
		else
		{
			MyGame->PlayGame( std::make_shared<StartLevelProxy>( this ) );
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
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<MenuItem*>::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			std::shared_ptr<PhsxSlider> slider = dynamic_cast<PhsxSlider*>( *item );
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
