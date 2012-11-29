#include <global_header.h>


namespace CloudberryKingdom
{

	AggressiveUpgrades_GUI::AggressiveUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel ) : CustomUpgrades_GUI( PieceSeed, CustomLevel )
	{
	}

	std::vector<Upgrade> AggressiveUpgrades_GUI::GetUpgradeList()
	{
		const Upgrade tempVector[] = { Upgrade_FLY_BLOB, Upgrade_FIRE_SPINNER, Upgrade_SPIKEY_GUY, Upgrade_PINKY, Upgrade_LASER, Upgrade_SPIKE, Upgrade_LAVA_DRIP, Upgrade_SERPENT, Upgrade_SPIKEY_LINE, Upgrade_FIREBALL };
		return std::vector<Upgrade>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}

	void AggressiveUpgrades_GUI::Go()
	{
		StartGame();
	}

	Localization::Words AggressiveUpgrades_GUI::HeaderText()
	{
		return Localization::Words_AGGRESSIVE;
	}

	PassiveUpgrades_GUI::PassiveUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel ) : CustomUpgrades_GUI( PieceSeed, CustomLevel )
	{
	}

	std::vector<Upgrade> PassiveUpgrades_GUI::GetUpgradeList()
	{
		const Upgrade tempVector2[] = { Upgrade_JUMP, Upgrade_SPEED, Upgrade_CEILING, Upgrade_MOVING_BLOCK, Upgrade_GHOST_BLOCK, Upgrade_FALLING_BLOCK, Upgrade_ELEVATOR, Upgrade_CLOUD, Upgrade_BOUNCY_BLOCK, Upgrade_PENDULUM };
		return std::vector<Upgrade>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
	}

	void PassiveUpgrades_GUI::Go()
	{
		std::shared_ptr<AggressiveUpgrades_GUI> UpgradeGui = std::make_shared<AggressiveUpgrades_GUI>( PieceSeed, CustomLevel );
		Call( UpgradeGui, 0 );
		Hide( PresetPos_LEFT );
		this->SlideInFrom = PresetPos_LEFT;
	}

	Localization::Words PassiveUpgrades_GUI::HeaderText()
	{
		return Localization::Words_PASSIVE;
	}

	CustomUpgrades_GUI::BlockPieceSeedSetter::BlockPieceSeedSetter( const std::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const std::shared_ptr<MenuSlider> &slider )
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
			std::shared_ptr<PictureIcon> pic = dynamic_cast<PictureIcon*>( gui->BigIcon );
			if ( slider->getMyFloat()->getVal() > 7.6f )
				pic->IconQuad->setTextureName( _T( "fblock_castle_3" ) );
			else if ( slider->getMyFloat()->getVal() > 3.2f )
				pic->IconQuad->setTextureName( _T( "fblock_castle_2" ) );
			else
				pic->IconQuad->setTextureName( _T( "fblock_castle_1" ) );
		}
	}

	CustomUpgrades_GUI::PieceSeedSetter::PieceSeedSetter( const std::shared_ptr<CustomUpgrades_GUI> &gui, Upgrade upgrade, const std::shared_ptr<MenuSlider> &slider )
	{
		this->gui = gui;
		this->upgrade = upgrade;
		this->slider = slider;
	}

	void CustomUpgrades_GUI::PieceSeedSetter::Apply()
	{
		gui->PieceSeed->MyUpgrades1->Get( upgrade ) = slider->getMyFloat()->MyFloat;
	}

	CustomUpgrades_GUI::AddUpgradeAdditionalOnSelect::AddUpgradeAdditionalOnSelect( const std::shared_ptr<CustomUpgrades_GUI> &cuGui, const std::shared_ptr<MenuSlider> &slider, Upgrade upgrade )
	{
		this->cuGui = cuGui;
		this->slider = slider;
		this->upgrade = upgrade;
	}

	void CustomUpgrades_GUI::AddUpgradeAdditionalOnSelect::Apply()
	{
		cuGui->TopText->SubstituteText( slider->Icon->DisplayText );
		cuGui->TopText->Pos = Vector2( 761 + 280, -46 + 771 );
		cuGui->TopText->Center();

		cuGui->BigIcon = ObjectIcon::CreateIcon( upgrade, true );
		cuGui->BigIcon->SetScale( 2 );
		cuGui->BigIcon->FancyPos->SetCenter( cuGui->Pos );
		cuGui->BigIcon->setPos( Vector2( 731 + 500 * ( 1 - cuGui->ScaleList ), 198 ) );
		cuGui->BigIcon->MyOscillateParams.max_addition *= .25f;

		cuGui->TopText->Show = true;
	}

	CustomUpgrades_GUI::UpgradesSliderLambda::UpgradesSliderLambda( const std::shared_ptr<CustomUpgrades_GUI> &cu, Upgrade upgrade )
	{
		this->cu = cu;
		this->upgrade = upgrade;
	}

	float CustomUpgrades_GUI::UpgradesSliderLambda::Apply()
	{
		return cu->PieceSeed->MyUpgrades1->Get( upgrade );
	}

	CustomUpgrades_GUI::StartLevelProxy::StartLevelProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::StartLevelProxy::Apply()
	{
		cuGui->StartLevel();
	}

	CustomUpgrades_GUI::ZeroProxy::ZeroProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::ZeroProxy::Apply()
	{
		cuGui->Zero();
	}

	CustomUpgrades_GUI::RandomizeProxy::RandomizeProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::RandomizeProxy::Apply()
	{
		cuGui->Randomize();
	}

	CustomUpgrades_GUI::GoProxy::GoProxy( const std::shared_ptr<CustomUpgrades_GUI> &cuGui )
	{
		this->cuGui = cuGui;
	}

	void CustomUpgrades_GUI::GoProxy::Apply()
	{
		cuGui->Go();
	}

	CustomUpgrades_GUI::CustomUpgrades_GUI( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<CustomLevel_GUI> &CustomLevel )
	{
		InitializeInstanceFields();
		CustomLevel->CallingPanel = this;

		this->PieceSeed = PieceSeed;
		this->CustomLevel = CustomLevel;
	}

	void CustomUpgrades_GUI::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	void CustomUpgrades_GUI::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
	}

	void CustomUpgrades_GUI::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void CustomUpgrades_GUI::AddUpgrade( Upgrade upgrade )
	{
		std::shared_ptr<MenuSlider> slider = std::make_shared<MenuSlider>( std::make_shared<EzText>( _T( "" ), ItemFont ) );
		slider->setSliderBackSize( slider->getSliderBackSize() * Vector2(1.15f,.72f) *.975f * ScaleList );
		slider->SetIcon( ObjectIcon::CreateIcon( upgrade ) );
		slider->Icon->SetScale( .6f * ScaleList );
		slider->setMyFloat( std::make_shared<WrappedFloat>( 0, 0, 9 ) );
		slider->InitialSlideSpeed *= 9;
		slider->MaxSlideSpeed *= 9;
		slider->Icon->setPos( slider->Icon->getPos() + Vector2(110, -123.5f) );
		slider->getMyFloat()->GetCallback = std::make_shared<UpgradesSliderLambda>(this, upgrade);

		// Keep the PieceSeed up to date when the slider changes
		if ( upgrade == Upgrade_FALLING_BLOCK )
		{
			slider->getMyFloat()->SetCallback = std::make_shared<BlockPieceSeedSetter>(this, upgrade, slider);
		}
		else
			slider->getMyFloat()->SetCallback = std::make_shared<PieceSeedSetter>(this, upgrade, slider);

		slider->AdditionalOnSelect = std::make_shared<AddUpgradeAdditionalOnSelect>( shared_from_this(), slider, upgrade );
		AddItem( slider );
	}

	void CustomUpgrades_GUI::StartLevel()
	{
		CustomLevel->StartLevelFromMenuData();
	}

	void CustomUpgrades_GUI::Zero()
	{
		for ( std::vector<MenuItem*>::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			std::shared_ptr<MenuSlider> slider = dynamic_cast<MenuSlider*>( *item );
			if ( 0 != slider )
				slider->getMyFloat()->setVal(0);
		}
	}

	void CustomUpgrades_GUI::Randomize()
	{
		if ( getMyLevel()->getRnd()->RndFloat() < .25f )
		{
			for ( std::vector<MenuItem*>::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
			{
				std::shared_ptr<MenuSlider> slider = dynamic_cast<MenuSlider*>( *item );
				if ( 0 != slider )
					slider->getMyFloat()->setVal(static_cast<float>(pow(getMyLevel()->getRnd()->RndFloat(0, 9),.9f)));
			}
		}
		else
		{
			for ( std::vector<MenuItem*>::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
			{
				std::shared_ptr<MenuSlider> slider = dynamic_cast<MenuSlider*>( *item );
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
		for ( std::vector<Upgrade>::const_iterator upgrade = GetUpgradeList().begin(); upgrade != GetUpgradeList().end(); ++upgrade )
			AddUpgrade( *upgrade );

		MyPile = std::make_shared<DrawPile>();

		FontScale = 1;
		MakeOptions();

		// Backdrop
		std::shared_ptr<QuadClass> backdrop;

		backdrop = std::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 1500, true );
		backdrop->Name = _T( "Backdrop" );
		MyPile->Add( backdrop, _T( "Backdrop" ) );
		backdrop->setSize( Vector2( 1682.54f, 1107.681f ) );
		backdrop->setPos( Vector2( 347.2231f, 51.58749f ) );

		// Make the top text
		MakeTopText();

		EnsureFancy();

		// Header
		std::shared_ptr<EzText> LocationText = std::make_shared<EzText>( HeaderText(), ItemFont );
		LocationText->Name = _T( "Header" );
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
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Start" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 317.0639f, 22.30127f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Random" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 325.7295f, -155.4283f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Reset" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 324.1416f, -326.0634f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 327.3179f, -498.3018f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( -202.7773f, -122.2222f ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "TopText" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 508.8778f, 725 ) );
			_t->setScale( 0.664f );
		}
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -872.222f, 936.1112f ) );
			_t->setScale( 0.72f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 307.143f, -23.41241f ) );
			_q->setSize( Vector2( 1741.167f, 1044.7f ) );
		}

		MyPile->setPos( Vector2( -285, 0 ) );
	#else
		std::shared_ptr<MenuItem> _item;
		MyMenu->setPos( Vector2( -202.7773f, -122.2222f ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Start" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 323.017f, -78.88908f ) );
		}
		_t = MyPile->FindEzText( _T( "Random" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 470.5718f, -323.2856f ) );
		}
		_t = MyPile->FindEzText( _T( "Back" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 629.6987f, -550.2858f ) );
		}
		_t = MyPile->FindEzText( _T( "TopText" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 773.5558f, 725 ) );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
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
		MyMenu = std::make_shared<Menu>( false );
		MyMenu->OnA = Cast::ToMenu( std::make_shared<GoProxy>( shared_from_this() ) );
		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( shared_from_this() );
		MyMenu->OnX = Cast::ToMenu( std::make_shared<RandomizeProxy>( shared_from_this() ) );
		MyMenu->OnY = std::make_shared<ZeroProxy>( shared_from_this() );
		MyMenu->SelectDelay = 11;
	}

	void CustomUpgrades_GUI::Go()
	{
	}

	void CustomUpgrades_GUI::StartGame()
	{
		MyGame->PlayGame( std::make_shared<StartLevelProxy>( shared_from_this() ) );
	}

	void CustomUpgrades_GUI::MakeOptions()
	{
		FontScale *= .8f;

	#if defined(PC_VERSION)
		// Start
		std::shared_ptr<MenuItem> item;
		std::shared_ptr<MenuItem> Start = item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_START, ItemFont ) );
		item->Name = _T( "Start" );
		item->setGo( Cast::ToItem( std::make_shared<GoProxy>( shared_from_this() ) ) );
		item->JiggleOnGo = false;
		AddItem( item );
		item->Pos = item->SelectedPos = Vector2( 425.3959f, -99.92095f );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;

		// Select 'Start Level' when the user presses (A)
		MyMenu->OnA = Cast::ToMenu( std::make_shared<GoProxy>( shared_from_this() ) );

		// Random
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_RANDOM, ItemFont ) );
		item->Name = _T( "Random" );
		item->setGo( Cast::ToItem( std::make_shared<RandomizeProxy>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();
		item->Pos = item->SelectedPos = Vector2( 511.8408f, -302.6506f );
		item->MyText->MyFloatColor = ( Color( 204, 220, 255 ) ).ToVector4() *.93f;
		item->MySelectedText->MyFloatColor = ( Color( 204, 220, 255 ) ).ToVector4();

		// Zero
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_RESET, ItemFont ) );
		item->Name = _T( "Reset" );
		item->setGo( Cast::ToItem( std::make_shared<ZeroProxy>( shared_from_this() ) ) );
		AddItem( item );
		item->SelectSound.reset();
		item->Pos = item->SelectedPos = Vector2( 599.1416f, -501.0634f );
		item->MyText->MyFloatColor = ( Color( 235, 255, 80 ) ).ToVector4() *.93f;
		item->MySelectedText->MyFloatColor = ( Color( 235, 255, 80 ) ).ToVector4();

		// Back
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_BACK, ItemFont ) );
		item->Name = _T( "Back" );
		item->getGo().reset();
		AddItem( item );
		item->SelectSound.reset();
		item->setGo( std::make_shared<ItemReturnToCallerProxy>( shared_from_this() ) );
		item->Pos = item->SelectedPos = Vector2( 702.3179f, -689.9683f );
		item->MyText->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;
		item->MySelectedText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
	#else
		std::shared_ptr<EzText> text;
		text = std::make_shared<EzText>( ButtonString::Go( 90 ) + _T( " Start" ), ItemFont );
		text->setPos( Vector2( 417.4604f, -159.4446f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		MyPile->Add( text, _T( "Start" ) );

		text = std::make_shared<EzText>( ButtonString::X( 90 ) + _T( " Random" ), ItemFont );
		text->setPos( Vector2( 531.6831f, -389.9523f ) );
		text->MyFloatColor = ( Color( 204, 220, 255 ) ).ToVector4();
		MyPile->Add( text, _T( "Random" ) );

		text = std::make_shared<EzText>( ButtonString::Back( 90 ) + _T( " Back" ), ItemFont );
		text->setPos( Vector2( 682.4761f, -622.5079f ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		MyPile->Add( text, _T( "Back" ) );
	#endif
	}

	void CustomUpgrades_GUI::MakeTopText()
	{
		TopText = std::make_shared<EzText>( _T( "   " ), ItemFont, true, true );
		SetTextProperties( TopText );
		TopText->Shadow = false;
		MyPile->Add( TopText, _T( "TopText" ) );
		TopText->setScale( TopText->getScale() * .83f );
		TopText->setPos( Vector2( 199.2069f, 746.0317f ) );
		TopText->Center();
	}

	void CustomUpgrades_GUI::MyDraw()
	{
		std::shared_ptr<Camera> cam = MyGame->MyLevel->getMainCamera();

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
