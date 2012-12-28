#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	AggressiveUpgrades_GUI::AggressiveUpgrades_GUI( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel ) : CustomUpgrades_GUI( PieceSeed, CustomLevel ) { }
	boost::shared_ptr<AggressiveUpgrades_GUI> AggressiveUpgrades_GUI::AggressiveUpgrades_GUI_Construct( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel )
	{
		CustomUpgrades_GUI::CustomUpgrades_GUI_Construct( PieceSeed, CustomLevel );

		return boost::static_pointer_cast<AggressiveUpgrades_GUI>( shared_from_this() );
	}

	std::vector<Upgrade> AggressiveUpgrades_GUI::GetUpgradeList()
	{
		Upgrade tempVector[] = { Upgrade_FLY_BLOB, Upgrade_FIRE_SPINNER, Upgrade_SPIKEY_GUY, Upgrade_PINKY, Upgrade_LASER, Upgrade_SPIKE, Upgrade_LAVA_DRIP, Upgrade_SERPENT, Upgrade_SPIKEY_LINE, Upgrade_FIREBALL };
		return VecFromArray( tempVector );
	}

	void AggressiveUpgrades_GUI::Go()
	{
		StartGame();
	}

	Localization::Words AggressiveUpgrades_GUI::HeaderText()
	{
		return Localization::Words_AGGRESSIVE;
	}

	PassiveUpgrades_GUI::PassiveUpgrades_GUI( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel ) : CustomUpgrades_GUI( PieceSeed, CustomLevel ) { }
	boost::shared_ptr<PassiveUpgrades_GUI> PassiveUpgrades_GUI::PassiveUpgrades_GUI_Construct( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel )
	{
		CustomUpgrades_GUI::CustomUpgrades_GUI_Construct( PieceSeed, CustomLevel );

		return boost::static_pointer_cast<PassiveUpgrades_GUI>( shared_from_this() );
	}

	std::vector<Upgrade> PassiveUpgrades_GUI::GetUpgradeList()
	{
		Upgrade tempVector2[] = { Upgrade_JUMP, Upgrade_SPEED, Upgrade_CEILING, Upgrade_MOVING_BLOCK, Upgrade_GHOST_BLOCK, Upgrade_FALLING_BLOCK, Upgrade_ELEVATOR, Upgrade_CLOUD, Upgrade_BOUNCY_BLOCK, Upgrade_PENDULUM };
		return VecFromArray( tempVector2 );
	}

	void PassiveUpgrades_GUI::Go()
	{
		boost::shared_ptr<AggressiveUpgrades_GUI> UpgradeGui = MakeMagic( AggressiveUpgrades_GUI, ( PieceSeed, CustomLevel ) );
		Call( UpgradeGui, 0 );
		Hide( PresetPos_LEFT );
		this->SlideInFrom = PresetPos_LEFT;
	}

	Localization::Words PassiveUpgrades_GUI::HeaderText()
	{
		return Localization::Words_PASSIVE;
	}

	CustomUpgrades_GUI::BlockPieceSeedSetter::BlockPieceSeedSetter( const boost::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const boost::shared_ptr<MenuSlider> &slider )
	{
		this->gui = gui;
		this->upgrade = upgrade;
		this->slider = slider;
	}

	void CustomUpgrades_GUI::BlockPieceSeedSetter::Apply()
	{
		gui->PieceSeed->MyUpgrades1->Get( upgrade ) = slider->getMyFloat()->MyFloat;

		// Set the Fallingblock to an O-face when maxed out
		if ( slider == gui->MyMenu->getCurItem() )
		{
			boost::shared_ptr<PictureIcon> pic = boost::dynamic_pointer_cast<PictureIcon>( gui->BigIcon );
			if ( slider->getMyFloat()->getVal() > 7.6f )
				pic->IconQuad->setTextureName( std::wstring( L"fblock_castle_3" ) );
			else if ( slider->getMyFloat()->getVal() > 3.2f )
				pic->IconQuad->setTextureName( std::wstring( L"fblock_castle_2" ) );
			else
				pic->IconQuad->setTextureName( std::wstring( L"fblock_castle_1" ) );
		}
	}

	CustomUpgrades_GUI::PieceSeedSetter::PieceSeedSetter( const boost::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const boost::shared_ptr<MenuSlider> &slider )
	{
		this->gui = gui;
		this->upgrade = upgrade;
		this->slider = slider;
	}

	void CustomUpgrades_GUI::PieceSeedSetter::Apply()
	{
		gui->PieceSeed->MyUpgrades1->Get( upgrade ) = slider->getMyFloat()->MyFloat;
	}

	CustomUpgrades_GUI::AddUpgradeAdditionalOnSelect::AddUpgradeAdditionalOnSelect( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui, const boost::shared_ptr<MenuSlider> &slider, Upgrade upgrade )
	{
		this->cuGui = cuGui;
		this->slider = slider;
		this->upgrade = upgrade;
	}

	void CustomUpgrades_GUI::AddUpgradeAdditionalOnSelect::Apply()
	{
		cuGui->TopText->SubstituteText( slider->Icon->DisplayText );
		cuGui->TopText->setPos( Vector2( 761 + 280, -46 + 771 ) );
		cuGui->TopText->Center();

		cuGui->BigIcon = ObjectIcon::CreateIcon( upgrade, true );
		cuGui->BigIcon->SetScale( 2 );
		cuGui->BigIcon->FancyPos->SetCenter( cuGui->Pos );
		cuGui->BigIcon->setPos( Vector2( 731 + 500 * ( 1 - cuGui->ScaleList ), 198 ) );
		cuGui->BigIcon->MyOscillateParams.max_addition *= .25f;

		cuGui->TopText->Show = true;
	}

	CustomUpgrades_GUI::UpgradesSliderLambda::UpgradesSliderLambda( const boost::shared_ptr<CustomUpgrades_GUI> &cu, Upgrade upgrade )
	{
		this->cu = cu;
		this->upgrade = upgrade;
	}

	float CustomUpgrades_GUI::UpgradesSliderLambda::Apply()
	{
		return cu->PieceSeed->MyUpgrades1->Get( upgrade );
	}

	CustomUpgrades_GUI::StartLevelProxy::StartLevelProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::StartLevelProxy::Apply()
	{
		cuGui->StartLevel();
	}

	CustomUpgrades_GUI::ZeroProxy::ZeroProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::ZeroProxy::Apply()
	{
		cuGui->Zero();
	}

	CustomUpgrades_GUI::RandomizeProxy::RandomizeProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::RandomizeProxy::Apply()
	{
		cuGui->Randomize();
	}

	CustomUpgrades_GUI::GoProxy::GoProxy( const boost::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::GoProxy::Apply()
	{
		cuGui->Go();
	}

	CustomUpgrades_GUI::CustomUpgrades_GUI( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel ) :
		ScaleList( 0 )
	{
	}
	boost::shared_ptr<CustomUpgrades_GUI> CustomUpgrades_GUI::CustomUpgrades_GUI_Construct( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<CustomLevel_GUI> &CustomLevel )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		CustomLevel->CallingPanel = boost::static_pointer_cast<GUI_Panel>( shared_from_this() );

		this->PieceSeed = PieceSeed;
		this->CustomLevel = CustomLevel;

		return boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() );
	}

	void CustomUpgrades_GUI::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	void CustomUpgrades_GUI::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
	}

	void CustomUpgrades_GUI::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void CustomUpgrades_GUI::AddUpgrade( Upgrade upgrade )
	{
		boost::shared_ptr<MenuSlider> slider = MakeMagic( MenuSlider, ( boost::make_shared<EzText>( std::wstring( L"" ), ItemFont ) ) );
		slider->setSliderBackSize( slider->getSliderBackSize() * Vector2(1.15f, .72f) * .975f * ScaleList );
		slider->SetIcon( ObjectIcon::CreateIcon( upgrade ) );
		slider->Icon->SetScale( .6f * ScaleList );
		slider->setMyFloat( boost::make_shared<WrappedFloat>( 0.f, 0.f, 9.f ) );
		slider->InitialSlideSpeed *= 9;
		slider->MaxSlideSpeed *= 9;
		slider->Icon->setPos( slider->Icon->getPos() + Vector2(110, -123.5f) );
		slider->getMyFloat()->GetCallback = boost::make_shared<UpgradesSliderLambda>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ), upgrade );

		// Keep the PieceSeed up to date when the slider changes
		if ( upgrade == Upgrade_FALLING_BLOCK )
		{
			slider->getMyFloat()->SetCallback = boost::make_shared<BlockPieceSeedSetter>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ), upgrade, slider );
		}
		else
			slider->getMyFloat()->SetCallback = boost::make_shared<PieceSeedSetter>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ), upgrade, slider );

		slider->AdditionalOnSelect = boost::make_shared<AddUpgradeAdditionalOnSelect>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ), slider, upgrade );
		AddItem( slider );
	}

	void CustomUpgrades_GUI::StartLevel()
	{
		CustomLevel->StartLevelFromMenuData();
	}

	void CustomUpgrades_GUI::Zero()
	{
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<MenuSlider> slider = boost::dynamic_pointer_cast<MenuSlider>( *item );
			if ( 0 != slider )
				slider->getMyFloat()->setVal(0);
		}
	}

	void CustomUpgrades_GUI::Randomize()
	{
		if ( getMyLevel()->getRnd()->RndFloat() < .25f )
		{
			for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
			{
				boost::shared_ptr<MenuSlider> slider = boost::dynamic_pointer_cast<MenuSlider>( *item );
				if ( 0 != slider )
					slider->getMyFloat()->setVal(static_cast<float>(pow(getMyLevel()->getRnd()->RndFloat(0, 9),.9f)));
			}
		}
		else
		{
			for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
			{
				boost::shared_ptr<MenuSlider> slider = boost::dynamic_pointer_cast<MenuSlider>( *item );
				if ( 0 != slider )
				{
					float ChanceToZero = .1f;
					if ( slider->getMyFloat()->getVal() > 1 )
						ChanceToZero = .6f;
					if ( getMyLevel()->getRnd()->RndFloat() < ChanceToZero )
						slider->getMyFloat()->setVal(0);
					else
						slider->getMyFloat()->setVal(static_cast<float>(pow(getMyLevel()->getRnd()->RndFloat(0, 9),.93f)));
				}
			}
		}
	}

	std::vector<Upgrade> CustomUpgrades_GUI::GetUpgradeList()
	{
		return std::vector<Upgrade>();
	}

	void CustomUpgrades_GUI::Init()
	{
		CkBaseMenu::Init();

		ScaleList = .72f;

		setControl( -1 );

		ReturnToCallerDelay = 6;
		SlideInFrom = PresetPos_RIGHT;
		SlideOutTo = PresetPos_RIGHT;
		SlideInLength = 25;
		SlideOutLength = 20;

		// Make the menu
		MakeMenu();

		ItemPos = Vector2( -950, 880 );
		PosAdd.Y *= 1.18f * ScaleList;

		// Add obstacles
		std::vector<Upgrade> vec = GetUpgradeList();
		for ( std::vector<Upgrade>::const_iterator upgrade = vec.begin(); upgrade != vec.end(); ++upgrade )
			AddUpgrade( *upgrade );

		MyPile = boost::make_shared<DrawPile>();

		FontScale = 1;
		MakeOptions();

		// Backdrop
		boost::shared_ptr<QuadClass> backdrop;

		backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1500x900" ), 1500.f, true );
		backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( backdrop, std::wstring( L"Backdrop" ) );
		backdrop->setSize( Vector2( 1682.54f, 1107.681f ) );
		backdrop->setPos( Vector2( 347.2231f, 51.58749f ) );

		// Make the top text
		MakeTopText();

		EnsureFancy();

		// Header
		boost::shared_ptr<EzText> LocationText = boost::make_shared<EzText>( HeaderText(), ItemFont );
		LocationText->Name = std::wstring( L"Header" );
		SetHeaderProperties( LocationText );
		MyPile->Add( LocationText );

		SetPos();
	}

	Localization::Words CustomUpgrades_GUI::HeaderText()
	{
		return Localization::Words_NONE;
	}

	void CustomUpgrades_GUI::SetPos()
	{
	#if defined(PC_VERSION)
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Start" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 317.0639f, 22.30127f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Random" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 325.7295f, -155.4283f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Reset" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 324.1416f, -326.0634f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 327.3179f, -498.3018f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( -202.7773f, -122.2222f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"TopText" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 508.8778f, 725 ) );
			_t->setScale( 0.664f );
		}
		_t = MyPile->FindEzText( std::wstring( L"Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -872.222f, 936.1112f ) );
			_t->setScale( 0.72f );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 307.143f, -23.41241f ) );
			_q->setSize( Vector2( 1741.167f, 1044.7f ) );
		}

		MyPile->setPos( Vector2( -285, 0 ) );
	#else
		boost::shared_ptr<MenuItem> _item;
		MyMenu->setPos( Vector2( -202.7773f, -122.2222f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"Start" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 323.017f, -78.88908f ) );
		}
		_t = MyPile->FindEzText( std::wstring( L"Random" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 470.5718f, -323.2856f ) );
		}
		_t = MyPile->FindEzText( std::wstring( L"Back" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 629.6987f, -550.2858f ) );
		}
		_t = MyPile->FindEzText( std::wstring( L"TopText" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 773.5558f, 725 ) );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 307.143f, -23.41241f ) );
			_q->setSize( Vector2( 1741.167f, 1044.7f ) );
		}

		MyPile->setPos( Vector2( -285, 0 ) );
	#endif
	}

	void CustomUpgrades_GUI::MakeMenu()
	{
		MyMenu = boost::make_shared<Menu>( false );
		MyMenu->OnA = Cast::ToMenu( boost::make_shared<GoProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) ) );
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
		MyMenu->OnX = Cast::ToMenu( boost::make_shared<RandomizeProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) ) );
		MyMenu->OnY = boost::make_shared<ZeroProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) );
		MyMenu->SelectDelay = 11;
	}

	void CustomUpgrades_GUI::Go()
	{
	}

	void CustomUpgrades_GUI::StartGame()
	{
		MyGame->PlayGame( boost::make_shared<StartLevelProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) ) );
	}

	void CustomUpgrades_GUI::MakeOptions()
	{
		FontScale *= .8f;

	#if defined(PC_VERSION)
		// Start
		boost::shared_ptr<MenuItem> item;
		boost::shared_ptr<MenuItem> Start = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_START, ItemFont ) ) );
		item = Start;
		item->Name = std::wstring( L"Start" );
		item->setGo( Cast::ToItem( boost::make_shared<GoProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) ) ) );
		item->JiggleOnGo = false;
		AddItem( item );
		item->Pos = item->SelectedPos = Vector2( 425.3959f, -99.92095f );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;

		// Select 'Start Level' when the user presses (A)
		MyMenu->OnA = Cast::ToMenu( boost::make_shared<GoProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) ) );

		// Random
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_RANDOM, ItemFont ) ) );
		item->Name = std::wstring( L"Random" );
		item->setGo( Cast::ToItem( boost::make_shared<RandomizeProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) ) ) );
		AddItem( item );
		item->SelectSound.reset();
		item->Pos = item->SelectedPos = Vector2( 511.8408f, -302.6506f );
		item->MyText->MyFloatColor = ( bColor( 204, 220, 255 ) ).ToVector4() *.93f;
		item->MySelectedText->MyFloatColor = ( bColor( 204, 220, 255 ) ).ToVector4();

		// Zero
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_RESET, ItemFont ) ) );
		item->Name = std::wstring( L"Reset" );
		item->setGo( Cast::ToItem( boost::make_shared<ZeroProxy>( boost::static_pointer_cast<CustomUpgrades_GUI>( shared_from_this() ) ) ) );
		AddItem( item );
		item->SelectSound.reset();
		item->Pos = item->SelectedPos = Vector2( 599.1416f, -501.0634f );
		item->MyText->MyFloatColor = ( bColor( 235, 255, 80 ) ).ToVector4() *.93f;
		item->MySelectedText->MyFloatColor = ( bColor( 235, 255, 80 ) ).ToVector4();

		// Back
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_BACK, ItemFont ) ) );
		item->Name = std::wstring( L"Back" );
		item->_Go.reset();
		AddItem( item );
		item->SelectSound.reset();
		item->setGo( boost::make_shared<ItemReturnToCallerProxy>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
		item->Pos = item->SelectedPos = Vector2( 702.3179f, -689.9683f );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
	#else
		boost::shared_ptr<EzText> text;
		text = boost::make_shared<EzText>( ButtonString::Go( 90 ) + std::wstring( L" Start" ), ItemFont );
		text->setPos( Vector2( 417.4604f, -159.4446f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		MyPile->Add( text, std::wstring( L"Start" ) );

		text = boost::make_shared<EzText>( ButtonString::X( 90 ) + std::wstring( L" Random" ), ItemFont );
		text->setPos( Vector2( 531.6831f, -389.9523f ) );
		text->MyFloatColor = ( Color( static_cast<unsigned char>( 204 ), static_cast<unsigned char>( 220 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		MyPile->Add( text, std::wstring( L"Random" ) );

		text = boost::make_shared<EzText>( ButtonString::Back( 90 ) + std::wstring( L" Back" ), ItemFont );
		text->setPos( Vector2( 682.4761f, -622.5079f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		MyPile->Add( text, std::wstring( L"Back" ) );
	#endif
	}

	void CustomUpgrades_GUI::MakeTopText()
	{
		TopText = boost::make_shared<EzText>( std::wstring( L"   " ), ItemFont, true, true );
		SetTextProperties( TopText );
		TopText->Shadow = false;
		MyPile->Add( TopText, std::wstring( L"TopText" ) );
		TopText->setScale( TopText->getScale() * .83f );
		TopText->setPos( Vector2( 199.2069f, 746.0317f ) );
		TopText->Center();
	}

	void CustomUpgrades_GUI::MyDraw()
	{
		boost::shared_ptr<Camera> cam = MyGame->MyLevel->getMainCamera();

		CkBaseMenu::MyDraw();

		if ( BigIcon != 0 )
		{
			BigIcon->Draw( true );
		}
	}

	void CustomUpgrades_GUI::InitializeInstanceFields()
	{
		ScaleList = .7f;
	}
}
