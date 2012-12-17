#include <global_header.h>

namespace CloudberryKingdom
{

	boost::shared_ptr<GUI_Panel> InGameStartMenu::MakeListenerHelper::Apply( const boost::shared_ptr<Listener> &listener )
	{
		return MakeMagic( InGameStartMenu, ( listener->TriggeringPlayerIndex ) );
	}

	InGameStartMenu::PreventMenuHelper::PreventMenuHelper( const boost::shared_ptr<Listener> &listener, const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make )
	{
		this->listener = listener;
		this->Make = Make;
	}

	void InGameStartMenu::PreventMenuHelper::Apply()
	{
		if ( !InGameStartMenu::PreventMenu )
			listener->Call( Make->Apply( listener ) );
	}

	InGameStartMenu::GoRemoveProxy::GoRemoveProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoRemoveProxy::Apply()
	{
		igsm->GoRemove();
	}

	InGameStartMenu::GoControlsHelper::GoControlsHelper( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoControlsHelper::Apply()
	{
		igsm->Hide( PresetPos_LEFT, 40 );
		igsm->setPauseGame( true );
	}

	InGameStartMenu::GoControlsProxy::GoControlsProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoControlsProxy::Apply()
	{
		igsm->GoControls();
	}

	InGameStartMenu::GoOptionsProxy::GoOptionsProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoOptionsProxy::Apply()
	{
		igsm->GoOptions();
	}

	InGameStartMenu::GoSaveLoadProxy::GoSaveLoadProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoSaveLoadProxy::Apply()
	{
		igsm->GoSaveLoad();
	}

	InGameStartMenu::GoStatsProxy::GoStatsProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoStatsProxy::Apply()
	{
		igsm->GoStats();
	}

	InGameStartMenu::VerifyExitProxy::VerifyExitProxy( const boost::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::VerifyExitProxy::Apply()
	{
		igsm->VerifyExit();
	}

bool InGameStartMenu::PreventMenu = false;

	InGameStartMenu::InGameStartMenu( int Control ) : CkBaseMenu( false ) { }
	boost::shared_ptr<InGameStartMenu> InGameStartMenu::InGameStartMenu_Construct( int Control )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<InGameStartMenu>( shared_from_this() );
	}

	boost::shared_ptr<GameObject> InGameStartMenu::MakeListener()
	{
		return MakeListener_Base( boost::make_shared<MakeListenerHelper>() );
	}

	boost::shared_ptr<GameObject> InGameStartMenu::MakeListener_Base( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Listener> , boost::shared_ptr<GUI_Panel> > > &Make )
	{
		boost::shared_ptr<Listener> listener = MakeMagic( Listener, () );
		listener->MyButton = ControllerButtons_START;

		listener->Tags->Add( GameObject::Tag_REMOVE_ON_LEVEL_FINISH );

		listener->MyAction = boost::make_shared<PreventMenuHelper>( listener, Make );

		return listener;
	}

	void InGameStartMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.45f );
	}

	void InGameStartMenu::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();

		if ( MyMenu->getCurItem() == RemoveMe )
			ReturnToCaller( false );
	}

	void InGameStartMenu::Init()
	{
		CkBaseMenu::Init();

		setPauseGame( true );

		CallDelay = 15;

		FontScale = .775f;

		MyPile = boost::make_shared<DrawPile>();

		this->CallDelay = 5;
		this->setSlideLength( 14 );
		this->SelectedItemShift = Vector2( 0, 0 );

		MakeDarkBack();

		// Make the backdrop
		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( _T( "Backplate_1080x840" ), 1500.f, true );

		MyPile->Add( backdrop );
		backdrop->setPos( Vector2( -975.6945f, 54.86111f ) );

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );

		MyMenu->OnB.reset();

		boost::shared_ptr<MenuItem> item;

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::Words_MENU, ItemFont );
		HeaderText->Name = _T( "Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );
		HeaderText->setPos( Vector2( -1663.889f, 971.8889f ) );

		ItemPos = Vector2( -1560.333f, 600 );
		PosAdd = Vector2( 0, -270 );

		bool RemoveMeOption = false;
		if ( PlayerManager::GetNumPlayers() > 1 && getControl() >= 0 )
		{
			RemoveMeOption = true;
			PosAdd.Y += 44;
		}

		// Resume
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_RESUME, ItemFont ) );
		item->Name = _T( "Resume" );
		item->setGo( Cast::ToItem( boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<CkBaseMenu>( shared_from_this() ) ) ) );
		item->MyText->setScale( item->MyText->getScale() * 1.1f );
		item->MySelectedText->setScale( item->MySelectedText->getScale() * 1.1f );
		AddItem( item );
		item->SelectSound.reset();


		// Statistics
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_STATISTICS, ItemFont ) );
		item->Name = _T( "Stats" );
		item->setGo( Cast::ToItem( boost::make_shared<GoStatsProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		AddItem( item );

		// SaveLoadSeed
		Localization::Words word = Tools::CurLevel->CanLoadLevels ? Localization::Words_SAVE_LOAD : Localization::Words_SAVE_SEED;
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( word, ItemFont ) );
		item->Name = _T( "SaveLoadSeed" );
		item->setGo( Cast::ToItem( boost::make_shared<GoSaveLoadProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		if ( !Tools::CurLevel->CanLoadLevels && !Tools::CurLevel->CanSaveLevel )
		{
			item->Selectable = false;
			item->GrayOut();
		}
		AddItem( item );

		// Options
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_OPTIONS, ItemFont ) );
		item->Name = _T( "Options" );
		item->setGo( Cast::ToItem( boost::make_shared<GoOptionsProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		AddItem( item );

		// Controls
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_CONTROLS, ItemFont ) );
		item->Name = _T( "Controls" );
		item->setGo( Cast::ToItem( boost::make_shared<GoControlsProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
		AddItem( item );

		// Remove player
		if ( RemoveMeOption )
		{
			item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_REMOVE_ME, ItemFont ) );
			item->Name = _T( "Remove" );
			item->setGo( Cast::ToItem( boost::make_shared<GoRemoveProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );
			AddItem( item );
			RemoveMe = item;
		}

		// Exit level
		MakeExitItem();

		// Button interactions
		MyMenu->OnStart = MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Shift everything
		EnsureFancy();
		Shift( Vector2( 1045.139f, -10.41669f ) );

		SetPos();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void InGameStartMenu::GoRemove()
	{
		boost::shared_ptr<VerifyRemoveMenu> verify = MakeMagic( VerifyRemoveMenu, ( getControl() ) );
		GUI_Panel::Call( verify );
		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::GoControls()
	{
		MyGame->WaitThenDo( 4, boost::make_shared<GoControlsHelper>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) );
		boost::shared_ptr<ControlScreen> screen = MakeMagic( ControlScreen, ( getControl() ) );
		Call( screen, 22 );
	}

	void InGameStartMenu::GoOptions()
	{
		Call( MakeMagic( SoundMenu, ( getControl() ) ), 0 );

		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::GoSaveLoad()
	{
		// If this isn't a PC, and we can't load seeds right now, then go directly to the SaveAs menu.
	#if !defined(PC_VERSION)
		if ( !getMyLevel()->CanLoadLevels )
		{
			Call( boost::make_shared<SaveSeedAs>( getControl(), MenuItem::GetActivatingPlayerData() ), 0 );
		}
		else
	#endif
		{
	#if defined(PC_VERSION)
			Call( MakeMagic( SaveLoadSeedMenu, ( getControl(), getMyLevel()->CanLoadLevels, getMyLevel()->CanSaveLevel ) ), 0 );
	#else
			Call( MakeMagic( SaveLoadSeedMenu, ( getControl(), getMyLevel()->CanLoadLevels, getMyLevel()->CanSaveLevel ) ), 0 );
	#endif
		}
		Hide( PresetPos_LEFT );
		setPauseGame( true );

	}

	void InGameStartMenu::GoStats()
	{
		Call( MakeMagic( StatsMenu, ( StatGroup_LIFETIME ) ), 19 );
		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::SetPos()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Resume" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1501.999f, 708.3334f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Stats" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1504.778f, 469.9999f ) );
		}
		_item = MyMenu->FindItemByName( _T( "SaveLoadSeed" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1504.777f, 231.6667f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Options" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1496.443f, -3.88887f ) );
		}
		_item = MyMenu->FindItemByName( _T( "Controls" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1501.999f, -258.8889f ) );
		}
		_item = MyMenu->FindItemByName( _T( "" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1499.222f, -502.7777f ) );
		}

		MyMenu->setPos( Vector2( 1109.028f, 20.13885f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1463.89f, 1474.667f ) );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -989.5837f, -0.6944637f ) );
			_q->setSize( Vector2( 1198.763f, 932.3713f ) );
		}

		MyPile->setPos( Vector2( 995.1394f, -13.19449f ) );
	}

	void InGameStartMenu::MakeExitItem()
	{
		boost::shared_ptr<MenuItem> item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_EXIT_LEVEL, ItemFont ) );
		item->setGo( Cast::ToItem( boost::make_shared<VerifyExitProxy>( boost::static_pointer_cast<InGameStartMenu>( shared_from_this() ) ) ) );

		AddItem( item );
	}

	void InGameStartMenu::VerifyExit()
	{
		Call( MakeMagic( VerifyQuitLevelMenu, ( getControl() ) ), 0 );
		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::MyDraw()
	{
		Pos->Update();

		CkBaseMenu::MyDraw();
	}
}
