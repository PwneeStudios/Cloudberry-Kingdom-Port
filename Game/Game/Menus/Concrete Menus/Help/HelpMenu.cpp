#include <global_header.h>

namespace CloudberryKingdom
{

	HelpMenu::MakeListenerHelper::MakeListenerHelper( const std::shared_ptr<Listener> &listener )
	{
		this->listener = listener;
	}

	void HelpMenu::MakeListenerHelper::Apply()
	{
		if ( Tools::StepControl )
			return;

		std::shared_ptr<Level> level = Tools::CurLevel;
		if ( !level->Replay && !level->Watching && !level->Finished && !level->PreventHelp )
			listener->Call( std::make_shared<HelpMenu>() );
	}

	HelpMenu::ReturnToCallerProxy::ReturnToCallerProxy( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::ReturnToCallerProxy::Apply()
	{
		hm->ReturnToCaller();
	}

	HelpMenu::WatchComputerHelper::WatchComputerHelper( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::WatchComputerHelper::Apply()
	{
		hm->MyGame->MyLevel->WatchComputer();
	}

	HelpMenu::WatchComputerProxy::WatchComputerProxy( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::WatchComputerProxy::Apply()
	{
		hm->WatchComputer();
	}

	HelpMenu::IsShowGuidLambda::IsShowGuidLambda()
	{
	}

	bool HelpMenu::IsShowGuidLambda::Apply( const std::shared_ptr<GameObject> &obj )
	{
		return dynamic_cast<ShowGuide*>( obj ) != 0;
	}

	HelpMenu::IsSlowMoLambda::IsSlowMoLambda()
	{
	}

	bool HelpMenu::IsSlowMoLambda::Apply( const std::shared_ptr<GameObject> &obj )
	{
		return dynamic_cast<SlowMo*>( obj ) != 0;
	}

	HelpMenu::Toggle_ShowPathHelper::Toggle_ShowPathHelper( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_ShowPathHelper::Apply()
	{
		for ( GameObjVec::const_iterator go = hm->MyGame->MyGameObjects.begin(); go != hm->MyGame->MyGameObjects.end(); ++go )
		{
			if ( dynamic_cast<ShowGuide*>( *go ) != 0 )
				( *go )->Release();
		}
	}

	HelpMenu::Toggle_ShowPathSetter::Toggle_ShowPathSetter( const std::shared_ptr<HelpMenu> &hm, bool state )
	{
		this->hm = hm;
		this->state = state;
	}

	void HelpMenu::Toggle_ShowPathSetter::Apply()
	{
		hm->Toggle_ShowPath( state );
	}

	HelpMenu::Toggle_ShowPathProxy::Toggle_ShowPathProxy( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_ShowPathProxy::Apply( bool state )
	{
		hm->Toggle_ShowPath( state );
	}

	HelpMenu::ShowPathProxy::ShowPathProxy( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::ShowPathProxy::Apply()
	{
		hm->ShowPath();
	}

	bool HelpMenu::Toggle_SloMoHelperPredicate::Apply( const std::shared_ptr<GameObject> &match )
	{
		return dynamic_cast<SlowMo*>( match ) != 0;
	}

	HelpMenu::Toggle_SloMoHelper::Toggle_SloMoHelper( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_SloMoHelper::Apply()
	{
		Tools::RemoveAll( hm->MyGame->MyGameObjects, std::make_shared<Toggle_SloMoHelperPredicate>() );
	}

	HelpMenu::Toggle_SlowMoProxy::Toggle_SlowMoProxy( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_SlowMoProxy::Apply( bool state )
	{
		hm->Toggle_SlowMo( state );
	}

	HelpMenu::SlowMoProxy::SlowMoProxy( const std::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::SlowMoProxy::Apply()
	{
		hm->SlowMo();
	}

	int HelpMenu::CampaignCoinsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->CampaignCoins;
	}

	int HelpMenu::Bank()
	{
		switch ( MyGame->MyBankType )
		{
			case GameData::BankType_INFINITE:
				return 99;

			case GameData::BankType_CAMPAIGN:
				return PlayerManager::PlayerMax( std::make_shared<CampaignCoinsLambda>() );
		}

		return 0;
	}

	void HelpMenu::Buy( int Cost )
	{
		switch ( MyGame->MyBankType )
		{
			case GameData::BankType_CAMPAIGN:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				for ( std::vector<PlayerData*>::const_iterator p = PlayerManager::getExistingPlayers().begin(); p != PlayerManager::getExistingPlayers().end(); ++p )
					( *p )->CampaignCoins = __max( ( *p )->CampaignCoins - Cost, 0 );
				break;

			case GameData::BankType_INFINITE:
				break;
		}

		//PlayerManager.CoinsSpent += Cost;

		SetCoins( Bank() );
	}

	void HelpMenu::SetCoins( int Coins )
	{
		if ( Coins > 99 )
			Coins = 99;
		CoinsText->SubstituteText( _T( "x" ) + StringConverterHelper::toString( Coins ) );
	}

	void HelpMenu::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->Shadow = item->MySelectedText->Shadow = false;
		item->MyText->PicShadow = item->MySelectedText->PicShadow = false;
	}

	HelpMenu::HelpMenu()
	{
		// Note that help was used, so that no hint is given about it
		InitializeInstanceFields();
		Hints::SetYForHelpNum( 999 );
	}

	std::shared_ptr<GameObject> HelpMenu::MakeListener()
	{
		std::shared_ptr<Listener> listener = std::make_shared<Listener>();
		//listener.MyType = Listener.Type.OnDown;
		listener->MyButton = ControllerButtons_Y;
		listener->MyButton2 = ButtonCheck::Help_KeyboardKey;
		listener->MyAction = std::make_shared<MakeListenerHelper>( listener );

		return listener;
	}

	void HelpMenu::ReturnToCaller()
	{
		InGameStartMenu::PreventMenu = false;

		if ( Active )
		{
			Active = false;
			MyGame->WaitThenDo( DelayExit, std::make_shared<ReturnToCallerProxy>( this ) );
		}
		else
			CkBaseMenu::ReturnToCaller();
	}

	bool HelpMenu::MenuReturnToCaller( const std::shared_ptr<Menu> &menu )
	{
		DelayExit = 0;

		return CkBaseMenu::MenuReturnToCaller( menu );
	}

	bool HelpMenu::Allowed_WatchComputer()
	{
		return MyGame->MyLevel->WatchComputerEnabled() && Bank() >= Cost_Watch;
	}

	void HelpMenu::WatchComputer()
	{
		if ( !Allowed_WatchComputer() )
			return;

		Buy( Cost_Watch );

		ReturnToCaller();
		MyGame->WaitThenDo( DelayExit - 10, std::make_shared<WatchComputerHelper>( this ) );
	}

	bool HelpMenu::On_ShowPath()
	{
		return Tools::Any( Tools::CurGameData->MyGameObjects, std::make_shared<IsShowGuidLambda>() );
	}

	bool HelpMenu::Allowed_ShowPath()
	{
	#if defined(DEBUG)
		return MyGame->MyLevel->WatchComputerEnabled();
	#else
		return MyGame->MyLevel->CanWatchComputer && Bank() >= Cost_Path;
	#endif
	}

	void HelpMenu::Toggle_ShowPath( bool state )
	{
		if ( state )
		{
			std::shared_ptr<ShowGuide> guide = std::make_shared<ShowGuide>();

			MyGame->AddGameObject( guide );
		}
		else
		{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
				if ( dynamic_cast<ShowGuide*>( *obj ) != 0 )
					( *obj )->Release();
			MyGame->AddToDo( std::make_shared<Toggle_ShowPathHelper>( this ) );
		}
	}

	void HelpMenu::ShowPath()
	{
		if ( !Allowed_ShowPath() )
			return;

		Buy( Cost_Path );

		ReturnToCaller();
		MyGame->WaitThenDo( DelayExit - 10, std::make_shared<Toggle_ShowPathSetter>( this, true ) );
	}

	bool HelpMenu::On_SlowMo()
	{
		return Tools::Any( Tools::CurGameData->MyGameObjects, std::make_shared<IsSlowMoLambda>() );
	}

	bool HelpMenu::Allowed_SlowMo()
	{
		return true && Bank() >= Cost_Slow;
	}

	void HelpMenu::Toggle_SlowMo( bool state )
	{
		if ( state )
		{
			std::shared_ptr<CloudberryKingdom::SlowMo> slowmo = std::make_shared<SlowMo>();
			slowmo->setControl( getControl() );

			MyGame->AddGameObject( slowmo );
		}
		else
		{
			MyGame->AddToDo( std::make_shared<Toggle_SloMoHelper>( this ) );
		}
	}

	void HelpMenu::SlowMo()
	{
		if ( !Allowed_SlowMo() )
			return;

		Buy( Cost_Slow );

		Toggle_SlowMo( true );
		ReturnToCaller();
	}

	void HelpMenu::OnAdd()
	{
		Initialization();

		CkBaseMenu::OnAdd();

		InGameStartMenu::PreventMenu = true;

		Item_WatchComputer->Icon->Fade( !Allowed_WatchComputer() );
		Item_SlowMo->Icon->Fade( !Allowed_SlowMo() );
		Item_ShowPath->Icon->Fade( !Allowed_ShowPath() );

		ReturnToCallerDelay = 30;
	}

	void HelpMenu::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.2f );
	}

	void HelpMenu::Initialization()
	{
		std::shared_ptr<GameData> game = Tools::CurGameData;

		setPauseGame( true );

		//FontScale = .73f;
		FontScale = .8f;

		MyPile = std::make_shared<DrawPile>();

		setRightPanel( Blurb = std::make_shared<HelpBlurb>() );

		this->CallDelay = 3;
		this->setSlideLength( 14 );
		this->SelectedItemShift = Vector2( 0, 0 );
		//this.SlideInFrom = PresetPos.Right;

		MakeDarkBack();

		// Make the left backdrop
		std::shared_ptr<QuadClass> backdrop = std::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 1500 );
		MyPile->Add( backdrop, _T( "Backdrop" ) );
		backdrop->setPos( Vector2( -1777.778f, 30.55557f ) );

		// Coin
//C# TO C++ CONVERTER NOTE: The variable Coin was renamed since it is named the same as a user-defined type:
		std::shared_ptr<QuadClass> Coin_Renamed = std::make_shared<QuadClass>( _T( "Coin_Blue" ), 90, true );
		Coin_Renamed->setPos( Vector2( -873.1558f, 770.5778f ) );
		MyPile->Add( Coin_Renamed, _T( "Coin" ) );

		CoinsText = std::make_shared<EzText>( _T( "x" ), Resources::Font_Grobold42, 450, false, true );
		CoinsText->Name = _T( "Coins" );
		CoinsText->setScale( .8f );
		CoinsText->setPos( Vector2( -910.2224f, 717.3333f ) );
		CoinsText->MyFloatColor = ( Color( 255, 255, 255 ) ).ToVector4();
		CoinsText->OutlineColor = ( Color( 0, 0, 0 ) ).ToVector4();

		CoinsText->ShadowOffset = Vector2( -11, 11 );
		CoinsText->ShadowColor = Color( 65, 65, 65, 160 );
		CoinsText->PicShadow = false;
		MyPile->Add( CoinsText );
		SetCoins( Bank() );


		// Make the menu
		MyMenu = std::make_shared<Menu>( false );

		setControl( -1 );

		MyMenu->OnB.reset();

		std::shared_ptr<MenuItem> item;
		std::shared_ptr<MenuToggle> toggle;

		// Header
		std::shared_ptr<EzText> HeaderText = std::make_shared<EzText>( Localization::Words_COINS, ItemFont );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText, _T( "Header" ) );
		HeaderText->setPos( Vector2( -1663.889f, 971.8889f ) );


		Vector2 IconOffset = Vector2( -150, 0 );

		std::wstring CoinPrefix = _T( "{pCoin_Blue,68,?}" );

		// Watch the computer
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( CoinPrefix + _T( "x" ) + StringConverterHelper::toString( Cost_Watch ), ItemFont ) );
		item->Name = _T( "WatchComputer" );
		Item_WatchComputer = item;
		item->SetIcon( ObjectIcon::RobotIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -10, 0 ) );
		item->setGo( Cast::ToItem( std::make_shared<WatchComputerProxy>( this ) ) );
		ItemPos = Vector2( -1033.333f, 429.4446f );
		PosAdd = Vector2( 0, -520 );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_WATCH_COMPUTER );

		// Show path
		if ( On_ShowPath() )
		{
			item = toggle = std::make_shared<MenuToggle>( ItemFont );
			toggle->OnToggle = std::make_shared<Toggle_ShowPathProxy>( this );
			toggle->Toggle( true );
		}
		else
		{
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( CoinPrefix + _T( "x" ) + StringConverterHelper::toString( Cost_Path ), ItemFont ) );
			item->setGo( Cast::ToItem( std::make_shared<ShowPathProxy>( this ) ) );
		}
		item->Name = _T( "ShowPath" );
		item->SetIcon( ObjectIcon::PathIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -20, -75 ) );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_SHOW_PATH );
		Item_ShowPath = item;

		// Slow mo
		if ( On_SlowMo() )
		{
			item = toggle = std::make_shared<MenuToggle>( ItemFont );
			toggle->OnToggle = std::make_shared<Toggle_SlowMoProxy>( this );
			toggle->Toggle( true );
		}
		else
		{
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( CoinPrefix + _T( "x" ) + StringConverterHelper::toString( Cost_Slow ), ItemFont ) );
			item->setGo( Cast::ToItem( std::make_shared<SlowMoProxy>( this ) ) );
		}
		item->Name = _T( "SlowMo" );
		item->SetIcon( ObjectIcon::SlowMoIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -20, -55 ) );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_ACTIVATE_SLOW_MO );
		Item_SlowMo = item;

		MyMenu->OnStart = MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );
		MyMenu->OnY = Cast::ToAction( std::make_shared<MenuReturnToCallerProxy>( this ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		EnsureFancy();
		SetPos();
	}

	void HelpMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "WatchComputer" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1050, 285.0002f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "ShowPath" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1047.222f, -98.8887f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "SlowMo" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -1052.777f, -499.4443f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 0, 0 ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Coins" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -771.3337f, 622.889f ) );
			_t->setScale( 0.6593335f );
		}
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1497.222f, 816.3335f ) );
			_t->setScale( 0.9640832f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 22.22229f, -33.33333f ) );
			_q->setSize( Vector2( 1740.553f, 1044.332f ) );
		}
		_q = MyPile->FindQuad( _T( "Coin" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -798.1558f, 634.4669f ) );
			_q->setSize( Vector2( 110.5714f, 110.5714f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}

	void HelpMenu::AddItem( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::AddItem( item );

	#if defined(PC_VERSION)
		item->Padding += Vector2( 20, 40 );
	#endif
	}

	void HelpMenu::ReturnToCaller( bool PlaySound )
	{
		CkBaseMenu::ReturnToCaller( PlaySound );
	}

	void HelpMenu::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( Frames );
	}

	void HelpMenu::SlideOut_RightPanel( const std::shared_ptr<PresetPos> &Preset, int Frames )
	{
		CkBaseMenu::SlideOut_RightPanel( Preset, Frames );
	}

	void HelpMenu::InitializeInstanceFields()
	{
		DelayExit = 29;
		Cost_Watch = 0;
		Cost_Path = 30;
		Cost_Slow = 10;
	}
}
