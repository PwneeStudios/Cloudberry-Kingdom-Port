#include <global_header.h>

namespace CloudberryKingdom
{

	void SimpleMenuBase::InitializeStatics()
	{
		SimpleMenuBase::NoMoveDuration = 20;
	}

	// Statics
	int SimpleMenuBase::NoMoveDuration;


	SimpleMenuBase::SimpleToCustomProxy::SimpleToCustomProxy( const std::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleToCustomProxy::Apply()
	{
		smb->SimpleToCustom();
	}

	SimpleMenuBase::SimpleToDoneProxy::SimpleToDoneProxy( const std::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleToDoneProxy::Apply()
	{
		smb->SimpleToDone();
	}

	SimpleMenuBase::SimpleToBackProxy::SimpleToBackProxy( const std::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleToBackProxy::Apply()
	{
		smb->SimpleToBack();
	}

	SimpleMenuBase::SimpleSelect_RightProxy::SimpleSelect_RightProxy( const std::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleSelect_RightProxy::Apply()
	{
		smb->SimpleSelect_Right();
	}

	SimpleMenuBase::SimpleSelect_LeftProxy::SimpleSelect_LeftProxy( const std::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleSelect_LeftProxy::Apply()
	{
		smb->SimpleSelect_Left();
	}

	void SimpleMenuBase::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	//SimpleMenuBase::SimpleMenuBase( int Control, const std::shared_ptr<CharacterSelect> &Parent ) : CkBaseMenu( false )
	SimpleMenuBase::SimpleMenuBase( int Control, const std::shared_ptr<CharacterSelect> &Parent ) :
		NoMoveCount( 0 )
	{
	}
	std::shared_ptr<SimpleMenuBase> SimpleMenuBase::SimpleMenuBase_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = Parent;

		Constructor();

		return std::static_pointer_cast<SimpleMenuBase>( shared_from_this() );
	}

	void SimpleMenuBase::OnAdd()
	{
		CkBaseMenu::OnAdd();

		Arrows = MakeMagic( ArrowMenu, ( getControl(), MyCharacterSelect, std::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) );
		MyGame->AddGameObject( Arrows );
	}

	void SimpleMenuBase::SimpleToCustom()
	{
		GUI_Panel::Call( MakeMagic( CustomizeMenu, ( getControl(), MyCharacterSelect ) ) );
		Hide();
	}

	void SimpleMenuBase::SimpleToDone()
	{
		GUI_Panel::Call( MakeMagic( Waiting, ( getControl(), MyCharacterSelect ) ) );
		Hide();
	}

	void SimpleMenuBase::SimpleToBack()
	{
		ReturnToCaller( true );
	}

	void SimpleMenuBase::ButtonPhsx()
	{
		if ( !Tools::StepControl )
		{
			if ( ButtonCheck::State( ControllerButtons_Y, MyCharacterSelect->PlayerIndex ).Pressed )
				SimpleToCustom();

			if ( ButtonCheck::State( ControllerButtons_A, MyCharacterSelect->PlayerIndex ).Pressed )
				SimpleToDone();

			if ( ButtonCheck::State( ControllerButtons_B, MyCharacterSelect->PlayerIndex ).Pressed )
				SimpleToBack();

			if ( ButtonCheck::State( ControllerButtons_X, MyCharacterSelect->PlayerIndex ).Pressed )
				MyCharacterSelect->Randomize();
		}
	}

	void SimpleMenuBase::SimpleSelect_Right()
	{
		int i = MyCharacterSelect->getPlayer()->ColorSchemeIndex;

		do
		{
			i++;
			if ( i >= static_cast<int>( ColorSchemeManager::ColorSchemes.size() ) )
			{
				if ( MyCharacterSelect->HasCustom() )
					i = -1;
				else
					i = 0;
				break;
			}
		}
		while ( !MyCharacterSelect->AvailableColorScheme( ColorSchemeManager::ColorSchemes[ i ] ) );
		MyCharacterSelect->getPlayer()->ColorSchemeIndex = i;

		// Jiggle the arrow
		Arrows->MyMenu->Items[ 1 ]->DoActivationAnimation();

		MyCharacterSelect->SetIndex( MyCharacterSelect->getPlayer()->ColorSchemeIndex );
	}

	void SimpleMenuBase::SimpleSelect_Left()
	{
		int i = MyCharacterSelect->getPlayer()->ColorSchemeIndex;
		do
		{
			i--;
			if ( i <= 0 )
				break;
		}
		while ( !MyCharacterSelect->AvailableColorScheme( ColorSchemeManager::ColorSchemes[ i ] ) );
		MyCharacterSelect->getPlayer()->ColorSchemeIndex = i;

		// Jiggle the arrow
		Arrows->MyMenu->Items[ 0 ]->DoActivationAnimation();

		int StartIndex = 0;
		if ( MyCharacterSelect->HasCustom() )
			StartIndex = -1;
		if ( MyCharacterSelect->getPlayer()->ColorSchemeIndex < StartIndex )
			MyCharacterSelect->getPlayer()->ColorSchemeIndex = ColorSchemeManager::ColorSchemes.size() - 1;

		MyCharacterSelect->SetIndex( MyCharacterSelect->getPlayer()->ColorSchemeIndex );
	}

	void SimpleMenuBase::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;
		MyCharacterSelect->MyState = CharacterSelect::SelectState_SELECTING;
		MyCharacterSelect->MyDoll->ShowBob = true;
		MyCharacterSelect->MyGamerTag->ShowGamerTag = true;
		MyCharacterSelect->MyHeroLevel->ShowHeroLevel = true;
		MyCharacterSelect->getPlayer()->Exists = true;

		// Buttons
		ButtonPhsx();

		// Left/Right
		Vector2 Dir = ButtonCheck::GetDir( MyCharacterSelect->PlayerIndex );
		if ( NoMoveCount > 0 )
			NoMoveCount--;

		if ( abs( Dir.X - PrevDir.X ) > ButtonCheck::ThresholdSensitivity || NoMoveCount == 0 )
		{
			if ( Dir.X > ButtonCheck::ThresholdSensitivity )
				SimpleSelect_Right();
			else if ( Dir.X < -ButtonCheck::ThresholdSensitivity )
				SimpleSelect_Left();

			NoMoveCount = NoMoveDuration;
		}
		PrevDir = Dir;
	}

#if defined(PC_VERSION)
	SimpleMenu::SimpleMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent ) : SimpleMenuBase( Control, Parent ) { }
	std::shared_ptr<SimpleMenu> SimpleMenu::SimpleMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent )
	{
		SimpleMenuBase::SimpleMenuBase_Construct( Control, Parent );

		return std::static_pointer_cast<SimpleMenu>( shared_from_this() );
	}
#endif

#if defined(PC_VERSION)
	void SimpleMenu::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		item->MySelectedText->setScale( FontScale );
		item->MyText->setScale( item->MySelectedText->getScale() );

		item->MySelectedText->MyFloatColor = ( bColor( 50, 220, 50 ) ).ToVector4();
	}
#endif

#if defined(PC_VERSION)
	void SimpleMenu::Init()
	{
		SimpleMenuBase::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = std::make_shared<DrawPile>();
		MyPile->FancyPos->UpdateWithGame = true;

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );
		MyMenu->setControl( getControl() );

		MyMenu->OnB.reset();
		std::shared_ptr<MenuItem> item;

		// Customize
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_CUSTOM, ItemFont ) );
		item->Name = _T( "Custom" );
		item->setGo( Cast::ToItem( std::make_shared<SimpleToCustomProxy>( std::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) ) );
		ItemPos = Vector2( -523, -174 );
		PosAdd = Vector2( 0, -220 );
		AddItem( item );

		// Random
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_RANDOM, ItemFont ) );
		item->Name = _T( "Random" );
		item->setGo( Cast::ToItem( std::make_shared<CharacterSelect::RandomizeProxy>( MyCharacterSelect ) ) );
		AddItem( item );

		// Confirm
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_DONE, ItemFont ) );
		item->Name = _T( "Done" );
		item->setGo( Cast::ToItem( std::make_shared<SimpleToDoneProxy>( std::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) ) );
		AddItem( item );

		// Select "Confirm" to start with
		MyMenu->SelectItem( item );

		MyMenu->OnB = Cast::ToMenu( std::make_shared<SimpleToBackProxy>( std::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) );

		// Backdrop
		std::shared_ptr<QuadClass> backdrop = std::make_shared<QuadClass>( _T( "Score_Screen" ), 485.f );
		backdrop = std::make_shared<QuadClass>( std::shared_ptr<FancyVector2>(), true, false );
		backdrop->setTextureName( _T( "Score_Screen" ) );
		backdrop->ScaleYToMatchRatio( 485 );

		backdrop->setPos( Vector2( 1198.412f, -115.0794f ) );
		backdrop->setSize( Vector2( 647.6985f, 537.2521f ) );

		MyPile->setPos( Vector2( 0, 55 - 27 ) );

		EnsureFancy();
		MyMenu->FancyPos->RelVal = Vector2( 163.8887f, -55.55554f + 55 - 27 );

		SetPos();
	}
#endif

#if defined(PC_VERSION)
	void SimpleMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Custom" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -309.1112f, -87.88895f ) );
			_item->MyText->setScale( 0.6731667f );
			_item->MySelectedText->setScale( 0.6731667f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Random" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -336.8889f, -263.4445f ) );
			_item->MyText->setScale( 0.6948333f );
			_item->MySelectedText->setScale( 0.6948333f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Done" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -239.6667f, -441.7778f ) );
			_item->MyText->setScale( 0.6962501f );
			_item->MySelectedText->setScale( 0.6962501f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 0, 0 ) );
		MyPile->setPos( Vector2( 0, 0 ) );

		CharacterSelect::Shift( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}
#endif

#if ! defined(PC_VERSION)
	SimpleMenu::SimpleMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent ) : SimpleMenuBase( Control, Parent ) { }
	std::shared_ptr<SimpleMenu> SimpleMenu::SimpleMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent )
	{
		SimpleMenuBase::SimpleMenuBase_Construct( Control, Parent );

		return std::static_pointer_cast<SimpleMenu>( shared_from_this() );
	}
#endif

#if ! defined(PC_VERSION)
	void SimpleMenu::Init()
	{
		SimpleMenuBase::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = std::make_shared<DrawPile>();

		ItemFont = Resources::Font_Grobold42;
		FontScale = .66f;

		int ButtonSize = 95;

		std::wstring Space = _T( "{s34,0}" );
		float Shift = 25;

		// Press A to continue
		std::shared_ptr<EzText> ContinueText = std::make_shared<EzText>( ButtonString::Go( ButtonSize ) + Space + _T( "{c188,255,176,255} Select" ), ItemFont, true, true );
		ContinueText->setScale( this->FontScale );
		ContinueText->ShadowOffset = Vector2( 7.5f, 7.5f );
		ContinueText->ShadowColor = Color( 30, 30, 30 );
		ContinueText->ColorizePics = true;
		ContinueText->setPos( Vector2( 23.09587f + Shift, -386.9842f ) );

		MyPile->Add( ContinueText, _T( "A" ) );

		// Press Y to customize
		std::shared_ptr<EzText> CustomizeText = std::make_shared<EzText>( ButtonString::Y( ButtonSize ) + Space + _T( "{c255,255,155,255} Custom" ), ItemFont, true, true );
		CustomizeText->setScale( this->FontScale );
		CustomizeText->ShadowOffset = Vector2( 7.5f, 7.5f );
		CustomizeText->ShadowColor = Color( 30, 30, 30 );
		CustomizeText->ColorizePics = true;
		CustomizeText->setPos( Vector2( 105.2387f + Shift, -611.9048f ) );

		MyPile->Add( CustomizeText, _T( "Y" ) );

		// Press X to randomize
		std::shared_ptr<EzText> RandomText = std::make_shared<EzText>( ButtonString::X( ButtonSize ) + Space + _T( "{c194,210,255,255} Random" ), ItemFont, true, true );
		RandomText->setScale( this->FontScale );
		RandomText->ShadowOffset = Vector2( 7.5f, 7.5f );
		RandomText->ShadowColor = Color( 30, 30, 30 );
		RandomText->ColorizePics = true;
		RandomText->setPos( Vector2( 69.52449f + Shift, -835.7142f ) );

		MyPile->Add( RandomText, _T( "X" ) );

		SetPos();
	}
#endif

#if ! defined(PC_VERSION)
	void SimpleMenu::SetPos()
	{
		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "A" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 45.31828f, -220.3175f ) );
			_t->setScale( 0.66f );
		}
		_t = MyPile->FindEzText( _T( "Y" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 119.1274f, -400.7938f ) );
			_t->setScale( 0.66f );
		}
		_t = MyPile->FindEzText( _T( "X" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 91.74666f, -599.6032f ) );
			_t->setScale( 0.66f );
		}

		CharacterSelect::Shift( shared_from_this() );
	}
#endif

#if ! defined(PC_VERSION)
	void SimpleMenu::MyPhsxStep()
	{
		SimpleMenuBase::MyPhsxStep();

		if ( !Active )
			return;
		MyCharacterSelect->MyState = CharacterSelect::SelectState_SELECTING;
	}
#endif
}
