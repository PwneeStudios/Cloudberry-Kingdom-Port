#include <global_header.h>

#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	void SimpleMenuBase::InitializeStatics()
	{
		SimpleMenuBase::NoMoveDuration = 20;
	}

	// Statics
	int SimpleMenuBase::NoMoveDuration;


	SimpleMenuBase::SimpleToCustomProxy::SimpleToCustomProxy( const boost::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleToCustomProxy::Apply()
	{
		smb->SimpleToCustom();
	}

	SimpleMenuBase::SimpleToDoneProxy::SimpleToDoneProxy( const boost::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleToDoneProxy::Apply()
	{
		smb->SimpleToDone();
	}

	SimpleMenuBase::SimpleToBackProxy::SimpleToBackProxy( const boost::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleToBackProxy::Apply()
	{
		smb->SimpleToBack();
	}

	SimpleMenuBase::SimpleSelect_RightProxy::SimpleSelect_RightProxy( const boost::shared_ptr<SimpleMenuBase> &smb )
	{
		this->smb = smb;
	}

	void SimpleMenuBase::SimpleSelect_RightProxy::Apply()
	{
		smb->SimpleSelect_Right();
	}

	SimpleMenuBase::SimpleSelect_LeftProxy::SimpleSelect_LeftProxy( const boost::shared_ptr<SimpleMenuBase> &smb )
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

	//SimpleMenuBase::SimpleMenuBase( int Control, const boost::shared_ptr<CharacterSelect> &Parent ) : CkBaseMenu( false )
	SimpleMenuBase::SimpleMenuBase( int Control, const boost::shared_ptr<CharacterSelect> &Parent ) :
		NoMoveCount( 0 )
	{
	}
	boost::shared_ptr<SimpleMenuBase> SimpleMenuBase::SimpleMenuBase_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = Parent;

		Constructor();

		return boost::static_pointer_cast<SimpleMenuBase>( shared_from_this() );
	}

	void SimpleMenuBase::OnAdd()
	{
		CkBaseMenu::OnAdd();

		Arrows = MakeMagic( ArrowMenu, ( getControl(), MyCharacterSelect, boost::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) );
		MyGame->AddGameObject( Arrows );
	}

	void SimpleMenuBase::SimpleToCustom()
	{
		GUI_Panel::Call( MakeMagic( CustomizeMenu, ( getControl(), MyCharacterSelect ) ) );
		Hide();
	}

	void SimpleMenuBase::SimpleToDone()
	{
		SkipCallSound = true;
		GUI_Panel::Call( MakeMagic( Waiting, ( getControl(), MyCharacterSelect, true ) ) );
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

		if ( fabs( Dir.X - PrevDir.X ) > ButtonCheck::ThresholdSensitivity || NoMoveCount == 0 )
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
	SimpleMenu::SimpleMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent ) : SimpleMenuBase( Control, Parent ) { }
	boost::shared_ptr<SimpleMenu> SimpleMenu::SimpleMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent )
	{
		SimpleMenuBase::SimpleMenuBase_Construct( Control, Parent );

		return boost::static_pointer_cast<SimpleMenu>( shared_from_this() );
	}
#endif

#if defined(PC_VERSION)
	void SimpleMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
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

		MyPile = boost::make_shared<DrawPile>();
		MyPile->FancyPos->UpdateWithGame = true;

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );
		MyMenu->setControl( getControl() );

		MyMenu->OnB.reset();
		boost::shared_ptr<MenuItem> item;

		// Customize
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Custom, ItemFont, true ) ) );
		item->Name = std::wstring( L"Custom" );
		item->setGo( Cast::ToItem( boost::make_shared<SimpleToCustomProxy>( boost::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) ) );
		ItemPos = Vector2( -523, -174 );
		PosAdd = Vector2( 0, -220 );
		AddItem( item );

		// Random
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Random, ItemFont, true ) ) );
		item->Name = std::wstring( L"Random" );
		item->setGo( Cast::ToItem( boost::make_shared<CharacterSelect::RandomizeProxy>( MyCharacterSelect ) ) );
		AddItem( item );

		// Confirm
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Done, ItemFont, true ) ) );
		item->Name = std::wstring( L"Done" );
		item->setGo( Cast::ToItem( boost::make_shared<SimpleToDoneProxy>( boost::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) ) );
		AddItem( item );

		// Select "Confirm" to start with
		MyMenu->SelectItem( item );

		MyMenu->OnB = Cast::ToMenu( boost::make_shared<SimpleToBackProxy>( boost::static_pointer_cast<SimpleMenuBase>( shared_from_this() ) ) );

		// Backdrop
		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( std::wstring( L"Score_Screen" ), 485.f );
		backdrop = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true, false );
		backdrop->setTextureName( std::wstring( L"Score_Screen" ) );
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
		boost::shared_ptr<MenuItem> _item;

        _item = MyMenu->FindItemByName( L"Custom" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0, -87.88895f ) ); _item->MyText->setScale( 0.6731667f ); _item->MySelectedText->setScale( 0.6731667f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Random" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0, -263.4445f ) ); _item->MyText->setScale( 0.6948333f ); _item->MySelectedText->setScale( 0.6948333f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Done" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0, -441.7778f ) ); _item->MyText->setScale( 0.6962501f ); _item->MySelectedText->setScale( 0.6962501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

		MyMenu->setPos( Vector2( 0, 0 ) );
		MyPile->setPos( Vector2( 0, 0 ) );

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}
#endif

#if ! defined(PC_VERSION)
	SimpleMenu::SimpleMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent ) : SimpleMenuBase( Control, Parent ) { }
	boost::shared_ptr<SimpleMenu> SimpleMenu::SimpleMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent )
	{
		SimpleMenuBase::SimpleMenuBase_Construct( Control, Parent );

		return boost::static_pointer_cast<SimpleMenu>( shared_from_this() );
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

		MyPile = boost::make_shared<DrawPile>();

		ItemFont = Resources::Font_Grobold42;
		FontScale = .66f;

		int ButtonSize = 95;

		std::wstring Space = std::wstring( L"{s34,0}" );
		float Shift = 25;

		boost::shared_ptr<QuadClass> q;

		// Press A to continue
        q = boost::make_shared<QuadClass>( ButtonTexture::getGo() );
        MyPile->Add(q, L"go");

		boost::shared_ptr<EzText> ContinueText = boost::make_shared<EzText>( Localization::Words_Continue, ItemFont, true, true );
		ContinueText->setScale( this->FontScale );
		ContinueText->ShadowOffset = Vector2( 7.5f, 7.5f );
		ContinueText->ShadowColor = Color( static_cast<unsigned char>( 30 ), static_cast<unsigned char>( 30 ), static_cast<unsigned char>( 30 ) );
		ContinueText->ColorizePics = true;
		ContinueText->setPos( Vector2( 23.09587f + Shift, -386.9842f ) );

		MyPile->Add( ContinueText, std::wstring( L"A" ) );

		// Press Y to customize
        q = boost::make_shared<QuadClass>( ButtonTexture::getY() );
        MyPile->Add(q, L"y");

		boost::shared_ptr<EzText> CustomizeText = boost::make_shared<EzText>( Localization::Words_Custom, ItemFont, true, true );
		CustomizeText->setScale( this->FontScale );
		CustomizeText->ShadowOffset = Vector2( 7.5f, 7.5f );
		CustomizeText->ShadowColor = Color( static_cast<unsigned char>( 30 ), static_cast<unsigned char>( 30 ), static_cast<unsigned char>( 30 ) );
		CustomizeText->ColorizePics = true;
		CustomizeText->setPos( Vector2( 105.2387f + Shift, -611.9048f ) );

		MyPile->Add( CustomizeText, std::wstring( L"Y" ) );

		// Press X to randomize
        q = boost::make_shared<QuadClass>( ButtonTexture::getX() );
        MyPile->Add(q, L"x");

		boost::shared_ptr<EzText> RandomText = boost::make_shared<EzText>( Localization::Words_Random, ItemFont, true, true );
		RandomText->setScale( this->FontScale );
		RandomText->ShadowOffset = Vector2( 7.5f, 7.5f );
		RandomText->ShadowColor = Color( static_cast<unsigned char>( 30 ), static_cast<unsigned char>( 30 ), static_cast<unsigned char>( 30 ) );
		RandomText->ColorizePics = true;
		RandomText->setPos( Vector2( 69.52449f + Shift, -835.7142f ) );

		MyPile->Add( RandomText, std::wstring( L"X" ) );

		SetPos();
	}
#endif

#if ! defined(PC_VERSION)
	void SimpleMenu::SetPos()
	{
        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"A" ); if (_t != 0 ) { _t->setPos( Vector2( 78.6516f, -159.2064f ) ); _t->setScale( 0.5214169f ); }
        _t = MyPile->FindEzText( L"Y" ); if (_t != 0 ) { _t->setPos( Vector2( 80.23858f, -323.016f ) ); _t->setScale( 0.5039168f ); }
        _t = MyPile->FindEzText( L"X" ); if (_t != 0 ) { _t->setPos( Vector2( 80.63551f, -471.8254f ) ); _t->setScale( 0.5540001f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"go" ); if (_q != 0 ) { _q->setPos( Vector2(-261.1109f, -141.6667f ) ); _q->setSize( Vector2( 67.83331f, 67.83331f ) ); }
        _q = MyPile->FindQuad( L"x" ); if (_q != 0 ) { _q->setPos( Vector2(-261.1112f, -461.1111f ) ); _q->setSize( Vector2( 63.41657f, 63.41657f ) ); }
        _q = MyPile->FindQuad( L"y" ); if (_q != 0 ) { _q->setPos( Vector2(-263.8887f, -308.3333f ) ); _q->setSize( Vector2( 67.6666f, 67.6666f ) ); }

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
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
