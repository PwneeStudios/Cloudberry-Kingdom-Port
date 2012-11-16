#include <global_header.h>
namespace CloudberryKingdom
{

	std::shared_ptr<GUI_Panel> InGameStartMenu::MakeListenerHelper::Apply( const std::shared_ptr<Listener> &listener )
	{
		return std::make_shared<InGameStartMenu>( listener->TriggeringPlayerIndex );
	}

	InGameStartMenu::PreventMenuHelper::PreventMenuHelper( const std::shared_ptr<Listener> &listener, const std::shared_ptr<LambdaFunc_1<Listener*, GUI_Panel*> > &Make )
	{
		this->listener = listener;
		this->Make = Make;
	}

	void InGameStartMenu::PreventMenuHelper::Apply()
	{
		if ( !InGameStartMenu::PreventMenu )
			listener->Call( Make->Apply( listener ) );
	}

	InGameStartMenu::GoRemoveProxy::GoRemoveProxy( const std::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoRemoveProxy::Apply()
	{
		igsm->GoRemove();
	}

	InGameStartMenu::GoControlsHelper::GoControlsHelper( const std::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoControlsHelper::Apply()
	{
		igsm->Hide( PresetPos_LEFT, 40 );
		igsm->setPauseGame( true );
	}

	InGameStartMenu::GoControlsProxy::GoControlsProxy( const std::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoControlsProxy::Apply()
	{
		igsm->GoControls();
	}

	InGameStartMenu::GoOptionsProxy::GoOptionsProxy( const std::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoOptionsProxy::Apply()
	{
		igsm->GoOptions();
	}

	InGameStartMenu::GoSaveLoadProxy::GoSaveLoadProxy( const std::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoSaveLoadProxy::Apply()
	{
		igsm->GoSaveLoad();
	}

	InGameStartMenu::GoStatsProxy::GoStatsProxy( const std::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::GoStatsProxy::Apply()
	{
		igsm->GoStats();
	}

	InGameStartMenu::VerifyExitProxy::VerifyExitProxy( const std::shared_ptr<InGameStartMenu> &igsm )
	{
		this->igsm = igsm;
	}

	void InGameStartMenu::VerifyExitProxy::Apply()
	{
		igsm->VerifyExit();
	}

bool InGameStartMenu::PreventMenu = false;

	InGameStartMenu::InGameStartMenu( int Control ) : CkBaseMenu( false )
	{
		this->setControl( Control );

		Constructor();
	}

	std::shared_ptr<GameObject> InGameStartMenu::MakeListener()
	{
		return MakeListener_Base( std::make_shared<MakeListenerHelper>() );
	}

	std::shared_ptr<GameObject> InGameStartMenu::MakeListener_Base( const std::shared_ptr<LambdaFunc_1<Listener*, GUI_Panel*> > &Make )
	{
		std::shared_ptr<Listener> listener = std::make_shared<Listener>();
		listener->MyButton = ControllerButtons_START;

		listener->Tags += GameObject::Tag_REMOVE_ON_LEVEL_FINISH;

		listener->MyAction = std::make_shared<PreventMenuHelper>( listener, Make );

		return listener;
	}

	void InGameStartMenu::SetHeaderProperties( const std::shared_ptr<EzText> &text )
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

		MyPile = std::make_shared<DrawPile>();

		this->CallDelay = 5;
		this->setSlideLength( 14 );
		this->SelectedItemShift = Vector2( 0, 0 );

		MakeDarkBack();

		// Make the backdrop
		std::shared_ptr<QuadClass> backdrop = std::make_shared<QuadClass>( _T( "Backplate_1080x840" ), 1500, true );

		MyPile->Add( backdrop );
		backdrop->setPos( Vector2( -975.6945f, 54.86111f ) );

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );

		MyMenu->OnB.reset();

		std::shared_ptr<MenuItem> item;

		// Header
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Localization::Words_MENU, ItemFont );
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
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_RESUME, ItemFont ) );
		item->Name = _T( "Resume" );
		item->setGo( Cast::ToItem( std::make_shared<ReturnToCallerProxy>( this ) ) );
		item->MyText->setScale( item->MyText->getScale() * 1.1f );
		item->MySelectedText->setScale( item->MySelectedText->getScale() * 1.1f );
		AddItem( item );
		item->SelectSound.reset();


		// Statistics
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_STATISTICS, ItemFont ) );
		item->Name = _T( "Stats" );
		item->setGo( Cast::ToItem( std::make_shared<GoStatsProxy>( this ) ) );
		AddItem( item );

		// SaveLoadSeed
		Localization::Words word = Tools::CurLevel->CanLoadLevels ? Localization::Words_SAVE_LOAD : Localization::Words_SAVE_SEED;
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( word, ItemFont ) );
		item->Name = _T( "SaveLoadSeed" );
		item->setGo( Cast::ToItem( std::make_shared<GoSaveLoadProxy>( this ) ) );
		if ( !Tools::CurLevel->CanLoadLevels && !Tools::CurLevel->CanSaveLevel )
		{
			item->Selectable = false;
			item->GrayOut();
		}
		AddItem( item );

		// Options
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_OPTIONS, ItemFont ) );
		item->Name = _T( "Options" );
		item->setGo( Cast::ToItem( std::make_shared<GoOptionsProxy>( this ) ) );
		AddItem( item );

		// Controls
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_CONTROLS, ItemFont ) );
		item->Name = _T( "Controls" );
		item->setGo( Cast::ToItem( std::make_shared<GoControlsProxy>( this ) ) );
		AddItem( item );

		// Remove player
		if ( RemoveMeOption )
		{
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_REMOVE_ME, ItemFont ) );
			item->Name = _T( "Remove" );
			item->setGo( Cast::ToItem( std::make_shared<GoRemoveProxy>( this ) ) );
			AddItem( item );
			RemoveMe = item;
		}

		// Exit level
		MakeExitItem();

		// Button interactions
		MyMenu->OnStart = MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		// Shift everything
		EnsureFancy();
		Shift( Vector2( 1045.139f, -10.41669f ) );

		SetPos();
		MyMenu->SortByHeight();
		MyMenu->SelectItem( 0 );
	}

	void InGameStartMenu::GoRemove()
	{
		std::shared_ptr<VerifyRemoveMenu> verify = std::make_shared<VerifyRemoveMenu>( getControl() );
		Call( verify );
		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::GoControls()
	{
		MyGame->WaitThenDo( 4, std::make_shared<GoControlsHelper>( this ) );
		std::shared_ptr<ControlScreen> screen = std::make_shared<ControlScreen>( getControl() );
		Call( screen, 22 );
	}

	void InGameStartMenu::GoOptions()
	{
		Call( std::make_shared<SoundMenu>( getControl() ), 0 );

		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::GoSaveLoad()
	{
		// If this isn't a PC, and we can't load seeds right now, then go directly to the SaveAs menu.
	#if !defined(PC_VERSION)
		if ( !getMyLevel()->CanLoadLevels )
		{
			Call( std::make_shared<SaveSeedAs>( getControl(), MenuItem::GetActivatingPlayerData() ), 0 );
		}
		else
	#endif
		{
	#if defined(PC_VERSION)
			Call( std::make_shared<SaveLoadSeedMenu>( getControl(), getMyLevel()->CanLoadLevels, getMyLevel()->CanSaveLevel ), 0 );
	#else
			Call( std::make_shared<SaveLoadSeedMenu>( getControl(), getMyLevel()->CanLoadLevels, getMyLevel()->CanSaveLevel ), 0 );
	#endif
		}
		Hide( PresetPos_LEFT );
		setPauseGame( true );

	}

	void InGameStartMenu::GoStats()
	{
		Call( std::make_shared<StatsMenu>( StatGroup_LIFETIME ), 19 );
		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
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

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1463.89f, 1474.667f ) );
		}

		std::shared_ptr<QuadClass> _q;
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
		std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_EXIT_LEVEL, ItemFont ) );
		item->setGo( Cast::ToItem( std::make_shared<VerifyExitProxy>( this ) ) );

		AddItem( item );
	}

	void InGameStartMenu::VerifyExit()
	{
		Call( std::make_shared<VerifyQuitLevelMenu>( getControl() ), 0 );
		Hide( PresetPos_LEFT );
		setPauseGame( true );
	}

	void InGameStartMenu::MyDraw()
	{
		Pos->Update();

		CkBaseMenu::MyDraw();
	}
}
