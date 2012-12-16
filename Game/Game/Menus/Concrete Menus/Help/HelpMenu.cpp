#include <global_header.h>

namespace CloudberryKingdom
{

	HelpMenu::MakeListenerHelper::MakeListenerHelper( const boost::shared_ptr<Listener> &listener )
	{
		this->listener = listener;
	}

	void HelpMenu::MakeListenerHelper::Apply()
	{
		if ( Tools::StepControl )
			return;

		boost::shared_ptr<Level> level = Tools::CurLevel;
		if ( !level->Replay && !level->Watching && !level->Finished && !level->PreventHelp )
			listener->Call( MakeMagic( HelpMenu, () ) );
	}

	HelpMenu::ReturnToCallerProxy::ReturnToCallerProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::ReturnToCallerProxy::Apply()
	{
		hm->ReturnToCaller();
	}

	HelpMenu::WatchComputerHelper::WatchComputerHelper( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::WatchComputerHelper::Apply()
	{
		hm->MyGame->MyLevel->WatchComputer();
	}

	HelpMenu::WatchComputerProxy::WatchComputerProxy( const boost::shared_ptr<HelpMenu> &hm )
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

	bool HelpMenu::IsShowGuidLambda::Apply( const boost::shared_ptr<GameObject> &obj )
	{
		return boost::dynamic_pointer_cast<ShowGuide>( obj ) != 0;
	}

	HelpMenu::IsSlowMoLambda::IsSlowMoLambda()
	{
	}

	bool HelpMenu::IsSlowMoLambda::Apply( const boost::shared_ptr<GameObject> &obj )
	{
		return boost::dynamic_pointer_cast<CloudberryKingdom::SlowMo>( obj ) != 0;
	}

	HelpMenu::Toggle_ShowPathHelper::Toggle_ShowPathHelper( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_ShowPathHelper::Apply()
	{
		for ( GameObjVec::const_iterator go = hm->MyGame->MyGameObjects.begin(); go != hm->MyGame->MyGameObjects.end(); ++go )
		{
			if ( boost::dynamic_pointer_cast<ShowGuide>( *go ) != 0 )
				( *go )->Release();
		}
	}

	HelpMenu::Toggle_ShowPathSetter::Toggle_ShowPathSetter( const boost::shared_ptr<HelpMenu> &hm, bool state )
	{
		this->hm = hm;
		this->state = state;
	}

	void HelpMenu::Toggle_ShowPathSetter::Apply()
	{
		hm->Toggle_ShowPath( state );
	}

	HelpMenu::Toggle_ShowPathProxy::Toggle_ShowPathProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_ShowPathProxy::Apply( const bool &state )
	{
		hm->Toggle_ShowPath( state );
	}

	HelpMenu::ShowPathProxy::ShowPathProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::ShowPathProxy::Apply()
	{
		hm->ShowPath();
	}

	bool HelpMenu::Toggle_SloMoHelperPredicate::Apply( const boost::shared_ptr<GameObject> &match )
	{
		return boost::dynamic_pointer_cast<CloudberryKingdom::SlowMo>( match ) != 0;
	}

	HelpMenu::Toggle_SloMoHelper::Toggle_SloMoHelper( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_SloMoHelper::Apply()
	{
		Tools::RemoveAll<boost::shared_ptr<GameObject> >( hm->MyGame->MyGameObjects, boost::make_shared<Toggle_SloMoHelperPredicate>() );
	}

	HelpMenu::Toggle_SlowMoProxy::Toggle_SlowMoProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::Toggle_SlowMoProxy::Apply( const bool &state )
	{
		hm->Toggle_SlowMo( state );
	}

	HelpMenu::SlowMoProxy::SlowMoProxy( const boost::shared_ptr<HelpMenu> &hm )
	{
		this->hm = hm;
	}

	void HelpMenu::SlowMoProxy::Apply()
	{
		hm->SlowMo();
	}

	int HelpMenu::CampaignCoinsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
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
				return PlayerManager::PlayerMax( boost::make_shared<CampaignCoinsLambda>() );
		}

		return 0;
	}

	void HelpMenu::Buy( int Cost )
	{
		switch ( MyGame->MyBankType )
		{
			case GameData::BankType_CAMPAIGN:
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator p = PlayerManager::getExistingPlayers().begin(); p != PlayerManager::getExistingPlayers().end(); ++p )
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

	void HelpMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->Shadow = item->MySelectedText->Shadow = false;
		item->MyText->PicShadow = item->MySelectedText->PicShadow = false;
	}

	HelpMenu::HelpMenu() :
		DelayExit( 0 ),
		Cost_Watch( 0 ), Cost_Path( 0 ), Cost_Slow( 0 )
	{
	}

	boost::shared_ptr<HelpMenu> HelpMenu::HelpMenu_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();

		// Note that help was used, so that no hint is given about it
		Hints::SetYForHelpNum( 999 );

		return boost::static_pointer_cast<HelpMenu>( shared_from_this() );
	}

	boost::shared_ptr<GameObject> HelpMenu::MakeListener()
	{
		boost::shared_ptr<Listener> listener = MakeMagic( Listener, () );
		//listener.MyType = Listener.Type.OnDown;
		listener->MyButton = ControllerButtons_Y;
		listener->MyButton2 = ButtonCheck::Help_KeyboardKey;
		listener->MyAction = boost::make_shared<MakeListenerHelper>( listener );

		return listener;
	}

	void HelpMenu::ReturnToCaller()
	{
		InGameStartMenu::PreventMenu = false;

		if ( Active )
		{
			Active = false;
			MyGame->WaitThenDo( DelayExit, boost::make_shared<ReturnToCallerProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
		}
		else
			CkBaseMenu::ReturnToCaller();
	}

	bool HelpMenu::MenuReturnToCaller( const boost::shared_ptr<Menu> &menu )
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
		MyGame->WaitThenDo( DelayExit - 10, boost::make_shared<WatchComputerHelper>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
	}

	bool HelpMenu::On_ShowPath()
	{
		return Tools::Any<boost::shared_ptr<GameObject> >( Tools::CurGameData->MyGameObjects, boost::make_shared<IsShowGuidLambda>() );
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
			boost::shared_ptr<ShowGuide> guide = boost::make_shared<ShowGuide>();

			MyGame->AddGameObject( guide );
		}
		else
		{
			for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
				if ( boost::dynamic_pointer_cast<ShowGuide>( *obj ) != 0 )
					( *obj )->Release();
			MyGame->AddToDo( boost::make_shared<Toggle_ShowPathHelper>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
		}
	}

	void HelpMenu::ShowPath()
	{
		if ( !Allowed_ShowPath() )
			return;

		Buy( Cost_Path );

		ReturnToCaller();
		MyGame->WaitThenDo( DelayExit - 10, boost::make_shared<Toggle_ShowPathSetter>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ), true ) );
	}

	bool HelpMenu::On_SlowMo()
	{
		return Tools::Any<boost::shared_ptr<GameObject> >( Tools::CurGameData->MyGameObjects, boost::make_shared<IsSlowMoLambda>() );
	}

	bool HelpMenu::Allowed_SlowMo()
	{
		return true && Bank() >= Cost_Slow;
	}

	void HelpMenu::Toggle_SlowMo( bool state )
	{
		if ( state )
		{
			boost::shared_ptr<CloudberryKingdom::SlowMo> slowmo = boost::make_shared<CloudberryKingdom::SlowMo>();
			slowmo->setControl( getControl() );

			MyGame->AddGameObject( slowmo );
		}
		else
		{
			MyGame->AddToDo( boost::make_shared<Toggle_SloMoHelper>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) );
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

	void HelpMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->setScale( FontScale * 1.2f );
	}

	void HelpMenu::Initialization()
	{
		boost::shared_ptr<GameData> game = Tools::CurGameData;

		setPauseGame( true );

		//FontScale = .73f;
		FontScale = .8f;

		MyPile = boost::make_shared<DrawPile>();

		setRightPanel( Blurb = MakeMagic( HelpBlurb, () ) );

		this->CallDelay = 3;
		this->setSlideLength( 14 );
		this->SelectedItemShift = Vector2( 0, 0 );
		//this.SlideInFrom = PresetPos.Right;

		MakeDarkBack();

		// Make the left backdrop
		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 1500.f );
		MyPile->Add( backdrop, _T( "Backdrop" ) );
		backdrop->setPos( Vector2( -1777.778f, 30.55557f ) );

		// Coin
		boost::shared_ptr<QuadClass> Coin_Renamed = boost::make_shared<QuadClass>( _T( "Coin_Blue" ), 90.f, true );
		Coin_Renamed->setPos( Vector2( -873.1558f, 770.5778f ) );
		MyPile->Add( Coin_Renamed, _T( "Coin" ) );

		CoinsText = boost::make_shared<EzText>( _T( "x" ), Resources::Font_Grobold42, 450.f, false, true );
		CoinsText->Name = _T( "Coins" );
		CoinsText->setScale( .8f );
		CoinsText->setPos( Vector2( -910.2224f, 717.3333f ) );
		CoinsText->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		CoinsText->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();

		CoinsText->ShadowOffset = Vector2( -11, 11 );
		CoinsText->ShadowColor = bColor( 65, 65, 65, 160 );
		CoinsText->PicShadow = false;
		MyPile->Add( CoinsText );
		SetCoins( Bank() );


		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );

		setControl( -1 );

		MyMenu->OnB.reset();

		boost::shared_ptr<MenuItem> item;
		boost::shared_ptr<MenuToggle> toggle;

		// Header
		boost::shared_ptr<EzText> HeaderText = boost::make_shared<EzText>( Localization::Words_COINS, ItemFont );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText, _T( "Header" ) );
		HeaderText->setPos( Vector2( -1663.889f, 971.8889f ) );


		Vector2 IconOffset = Vector2( -150, 0 );

		std::wstring CoinPrefix = _T( "{pCoin_Blue,68,?}" );

		// Watch the computer
		item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( CoinPrefix + _T( "x" ) + StringConverterHelper::toString( Cost_Watch ), ItemFont ) );
		item->Name = _T( "WatchComputer" );
		Item_WatchComputer = item;
		item->SetIcon( ObjectIcon::RobotIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -10, 0 ) );
		item->setGo( Cast::ToItem( boost::make_shared<WatchComputerProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) ) );
		ItemPos = Vector2( -1033.333f, 429.4446f );
		PosAdd = Vector2( 0, -520 );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_WATCH_COMPUTER );

		// Show path
		if ( On_ShowPath() )
		{
			item = toggle = boost::make_shared<MenuToggle>( ItemFont );
			toggle->OnToggle = boost::make_shared<Toggle_ShowPathProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) );
			toggle->Toggle( true );
		}
		else
		{
			item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( CoinPrefix + _T( "x" ) + StringConverterHelper::toString( Cost_Path ), ItemFont ) );
			item->setGo( Cast::ToItem( boost::make_shared<ShowPathProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) ) );
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
			item = toggle = boost::make_shared<MenuToggle>( ItemFont );
			toggle->OnToggle = boost::make_shared<Toggle_SlowMoProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ));
			toggle->Toggle( true );
		}
		else
		{
			item = boost::make_shared<MenuItem>( boost::make_shared<EzText>( CoinPrefix + _T( "x" ) + StringConverterHelper::toString( Cost_Slow ), ItemFont ) );
			item->setGo( Cast::ToItem( boost::make_shared<SlowMoProxy>( boost::static_pointer_cast<HelpMenu>( shared_from_this() ) ) ) );
		}
		item->Name = _T( "SlowMo" );
		item->SetIcon( ObjectIcon::SlowMoIcon->Clone() );
		item->Icon->setPos( IconOffset + Vector2( -20, -55 ) );
		AddItem( item );
		item->AdditionalOnSelect = Blurb->SetText_Action( Localization::Words_ACTIVATE_SLOW_MO );
		Item_SlowMo = item;

		MyMenu->OnStart = MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
		MyMenu->OnY = Cast::ToAction( boost::make_shared<MenuReturnToCallerProxy>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );

		EnsureFancy();
		SetPos();
	}

	void HelpMenu::SetPos()
	{
		boost::shared_ptr<MenuItem> _item;
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

		boost::shared_ptr<EzText> _t;
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

		boost::shared_ptr<QuadClass> _q;
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

	void HelpMenu::AddItem( const boost::shared_ptr<MenuItem> &item )
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

	void HelpMenu::SlideOut_RightPanel( GUI_Panel::PresetPos Preset, int Frames )
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
