#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	ScoreScreen::OnAddHelper::OnAddHelper( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::OnAddHelper::Apply()
	{
		ss->MyMenu->Active = true;
	}

	ScoreScreen::VariableCoinsLambda::VariableCoinsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableCoinsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->Coins;
	}

	ScoreScreen::VariableTotalCoinsLambda::VariableTotalCoinsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableTotalCoinsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->TotalCoins;
	}

	ScoreScreen::VariableBlobsLambda::VariableBlobsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableBlobsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->Blobs;
	}

	ScoreScreen::VariableTotalBlobsLambda::VariableTotalBlobsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableTotalBlobsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->TotalBlobs;
	}

	ScoreScreen::ScoreScreenEndGameHelper::ScoreScreenEndGameHelper( const boost::shared_ptr<ScoreScreen> &ss, bool parameter )
	{
		this->ss = ss;
		this->parameter = parameter;
	}

	void ScoreScreen::ScoreScreenEndGameHelper::Apply()
	{
		ss->MyGame->EndGame->Apply( parameter );
	}

	ScoreScreen::MenuGo_NewLevelProxy::MenuGo_NewLevelProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_NewLevelProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_NewLevel( item );
	}

	ScoreScreen::MenuGo_ContinueProxy::MenuGo_ContinueProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_ContinueProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_Continue( item );
	}

	ScoreScreen::MenuGo_WatchReplayHelper::MenuGo_WatchReplayHelper( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_WatchReplayHelper::Apply()
	{
		ss->OnReturnTo(); // Re-activate the Score Screen object
		ss->getCore()->MyLevel->WatchReplay(true); // Start the replay
	}

	ScoreScreen::MenuGo_WatchReplayProxy::MenuGo_WatchReplayProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_WatchReplayProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_WatchReplay( item );
	}

	ScoreScreen::MenuGo_SaveProxy::MenuGo_SaveProxy( const boost::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_SaveProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_Save( item );
	}

	void ScoreScreen::MakeMenu()
	{
		if ( AsMenu )
		{
			MyMenu = boost::make_shared<Menu>( false );

			MyMenu->setControl( -1 );

			MyMenu->OnB.reset();

			_Add_Watch = MyGame->MyLevel->getReplayAvailable();
			_Add_Save = MyGame->MyLevel->MyLevelSeed != 0 && MyGame->MyLevel->MyLevelSeed->Saveable;

			boost::shared_ptr<MenuItem> item, go;

				if (InCampaign)
				{
					go = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Continue, ItemFont ) ) );
					item->setGo( boost::make_shared<MenuGo_ContinueProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				}
				else
				{
					go = item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_KeepSettings, ItemFont ) ) );
					item->setGo( boost::make_shared<MenuGo_NewLevelProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				}

			item->Name = std::wstring( L"Continue" );
			AddItem( item );
			item->MySelectedText->setScale( item->MySelectedText->getScale() * 1.3f );
			item->MyText->setScale( item->MySelectedText->getScale() );
			item->Shift( Vector2( -86, 65 ) );
			item->SelectedPos.X += 6;

			if ( _Add_Watch )
			{
				item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_WatchReplay, ItemFont ) ) );
				item->Name = std::wstring( L"Replay" );
				item->setGo( boost::make_shared<MenuGo_WatchReplayProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				AddItem( item );
			}

			if ( _Add_Save )
			{
				item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SaveSeed, ItemFont ) ) );
				item->Name = std::wstring( L"Save" );
				item->setGo( boost::make_shared<MenuGo_SaveProxy>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
				AddItem( item );
			}

			boost::shared_ptr<MenuItem> back;
			if (InCampaign)
			{
				//back = MakeBackButton(Localization.Words.Back);
				back = MakeBackButton( Localization::Words::Words_Exit );
				back->Go = MenuGo_ExitCampaign;
			}
			else
			{
				back = MakeBackButton( Localization::Words_BackToFreeplay );
				back->Go = MenuGo_ExitFreeplay;
			}


			MyMenu->OnB = Cast::ToMenu( go->getGo() );

			EnsureFancy();
			MyMenu->FancyPos->RelVal = Vector2( 869.0476f, -241.6667f );
		}
		else
		{
			boost::shared_ptr<QuadClass> ContinueButton = boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.f, false );
			ContinueButton->Name = std::wstring( L"GoButton" );
			MyPile->Add( ContinueButton );
			ContinueButton->setPos( Vector2( 180, -477.7778f ) + ShiftAll );

			boost::shared_ptr<EzText> ContinueText = boost::make_shared<EzText>( Localization::Words_Continue, ItemFont );
			ContinueText->Name = std::wstring( L"Continue" );
			SetHeaderProperties( ContinueText );
			ContinueText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;
			MyPile->Add( ContinueText );
			ContinueText->setPos( Vector2( 180, -477.7778f ) + ShiftAll );

			if ( MyGame->MyLevel->getReplayAvailable() )
			{
				boost::shared_ptr<QuadClass> XButton = boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.f, false );
				XButton->Name = std::wstring( L"XButton" );
				MyPile->Add( XButton );
				XButton->setPos( Vector2( 180, -325.3333f ) + ShiftAll );

				boost::shared_ptr<EzText> ReplayText = boost::make_shared<EzText>( Localization::Words_WatchReplay, ItemFont );
				SetHeaderProperties( ReplayText );
				ReplayText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
				ReplayText->MyFloatColor = ( bColor( 184, 231, 231 ) ).ToVector4();
				MyPile->Add( ReplayText );
				ReplayText->setPos( Vector2( 180, -325.3333f ) + ShiftAll );
			}
		}
	}
	
	ScoreScreen::ScoreScreen( bool CallBaseConstructor ) :
		CkBaseMenu( CallBaseConstructor ),
		InCampaign( false ), _Add_Watch( false ), _Add_Save( false ), DelayPhsx( false ), MyStatGroup( static_cast<StatGroup>( 0 ) ), LastActive( false )
	{
	}
	boost::shared_ptr<ScoreScreen> ScoreScreen::ScoreScreen_Construct( bool CallBaseConstructor )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( CallBaseConstructor );

		return boost::static_pointer_cast<ScoreScreen>( shared_from_this() );
	}

	ScoreScreen::ScoreScreen( StatGroup group, const boost::shared_ptr<GameData> &game, const bool InCampaign ) :
		CkBaseMenu( false ),
		InCampaign( InCampaign ), _Add_Watch( false ), _Add_Save( false ), DelayPhsx( false ), MyStatGroup( static_cast<StatGroup>( 0 ) ), LastActive( false )
	{
	}
	boost::shared_ptr<ScoreScreen> ScoreScreen::ScoreScreen_Construct( StatGroup group, const boost::shared_ptr<GameData> &game, const bool InCampaign )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( false );
		
		MyGame = game;
		MyStatGroup = group;
		FontScale = .6f;

		Constructor();

		return boost::static_pointer_cast<ScoreScreen>( shared_from_this() );
	}

	void ScoreScreen::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		CkColorHelper::GreenItem( item );
	}

	void ScoreScreen::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;
	}

#if defined(PC_VERSION)
bool ScoreScreen::AsMenu = true;
#endif

#if ! defined(PC_VERSION)
bool ScoreScreen::AsMenu = true;
#endif

	void ScoreScreen::Init()
	{
		CkBaseMenu::Init();

		MyPile = boost::make_shared<DrawPile>();

		//MakeDarkBack();

		boost::shared_ptr<QuadClass> Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1230x740" ), std::wstring( L"Backdrop" ) );
		MyPile->Add( Backdrop );
		MyPile->Add( Backdrop );

		LevelCleared = boost::make_shared<QuadClass>( std::wstring( L"Score/LevelCleared" ), std::wstring( L"Header" ) );
		LevelCleared->Scale( .9f );
		MyPile->Add( LevelCleared );
		LevelCleared->setPos( Vector2( 10, 655 ) + ShiftAll );

		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"Coin_Blue" ), std::wstring( L"Coin" ) ) );
		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"Stopwatch_Black" ), std::wstring( L"Stopwatch" ) ) );
		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"Bob_Dead" ), std::wstring( L"Death" ) ) );

		MakeMenu();

		ScoreSound = Tools::SoundWad->FindByName( std::wstring( L"Coin" ) );
		BonusSound = Tools::SoundWad->FindByName( std::wstring( L"Coin" ) );
		ScoreSound->MaxInstances = 2;

		SetPos();
	}

	void ScoreScreen::SetPos()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Continue" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -871.7776f, 516.6667f ) );
			_item->MyText->setScale( 0.78f );
			_item->MySelectedText->setScale( 0.78f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Save" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -646.8889f, 266.6737f ) );
			_item->MyText->setScale( 0.6f );
			_item->MySelectedText->setScale( 0.6f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Replay" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -641.3332f, 91.67379f ) );
			_item->MyText->setScale( 0.6f );
			_item->MySelectedText->setScale( 0.6f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -755.2222f, -75.5462f ) );
			_item->MyText->setScale( 0.6f );
			_item->MySelectedText->setScale( 0.6f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"Coins" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -719.4445f, 22.22227f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( std::wstring( L"Blobs" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -661.1107f, -402.7777f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( std::wstring( L"Deaths" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -655.5553f, 411.1111f ) );
			_t->setScale( 1 );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 27.77808f, -6.666618f ) );
			_q->setSize( Vector2( 1509.489f, 943.4307f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 27.77808f, -6.666618f ) );
			_q->setSize( Vector2( 1509.489f, 943.4307f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"Header" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 16.66687f, 615.5555f ) );
			_q->setSize( Vector2( 937.8f, 147.6f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"Coin" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -955.5555f, -141.6665f ) );
			_q->setSize( Vector2( 168.1188f, 168.1188f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"Stopwatch" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -886.1108f, -513.8888f ) );
			_q->setSize( Vector2( 180.9532f, 211.6065f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"Death" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -983.3334f, 230.5556f ) );
			_q->setSize( Vector2( 321.4366f, 235.7202f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}

bool ScoreScreen::UseZoomIn = true;

	void ScoreScreen::OnAdd()
	{
		 CkBaseMenu::OnAdd();

		if ( UseZoomIn )
		{
			SlideIn( 0 );
			std::vector<Vector2> copy = std::vector<Vector2>( DrawPile::BubbleScale.size() );
			for ( int i = 0; i < static_cast<int>( DrawPile::BubbleScale.size() ); ++i )
			{
				copy[ i ] = ( DrawPile::BubbleScale[ i ] - Vector2(1) ) *.3f + Vector2(1);
			}
			zoom->MultiLerp( 6, copy );
		}

		// Calculate scores
		PlayerManager::CalcScore( MyStatGroup );

		int Coins = PlayerManager::PlayerSum( boost::make_shared<VariableCoinsLambda>( MyStatGroup ) );
		int CoinTotal = PlayerManager::PlayerMax( boost::make_shared<VariableTotalBlobsLambda>( MyStatGroup ) );
		int Blobs = PlayerManager::PlayerSum( boost::make_shared<VariableBlobsLambda>( MyStatGroup ) );
		int BlobTotal = PlayerManager::PlayerMax( boost::make_shared<VariableTotalBlobsLambda>( MyStatGroup ) );

		MyPile->Add( boost::make_shared<EzText>( Tools::ScoreString( Coins, CoinTotal ), ItemFont, std::wstring( std::wstring( L"Coins" ) ) ) );
		MyPile->Add( boost::make_shared<EzText>( CoreMath::ShortTime( PlayerManager::Score_Time ), ItemFont, std::wstring( std::wstring( L"Blobs" ) ) ) );
		MyPile->Add( boost::make_shared<EzText>( Tools::ScoreString( PlayerManager::Score_Attempts ), ItemFont, std::wstring( std::wstring( L"Deaths" ) ) ) );

		// Prevent menu interactions for a second
		MyMenu->Active = false;

		SetPos();
		MyMenu->SortByHeight();

		MyGame->WaitThenDo( DelayPhsx, boost::make_shared<OnAddHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
	}

	void ScoreScreen::MyDraw()
	{
		if ( getCore()->MyLevel->Replay || getCore()->MyLevel->Watching )
			return;

		Vector2 SaveZoom = MyGame->getCam()->getZoom();
		Vector2 SaveHoldZoom = MyGame->getCam()->HoldZoom;
		Tools::QDrawer->Flush();

		if ( zoom != 0 )
		{
			MyGame->getCam()->setZoom(.001f * zoom->Update());
			MyGame->getCam()->SetVertexCamera();
			EzText::ZoomWithCamera_Override = true;
		}

		Pos->SetCenter( getCore()->MyLevel->getMainCamera(), true );
		Pos->Update();

		CkBaseMenu::MyDraw();

		Tools::Render->EndSpriteBatch();

		if ( zoom != 0 )
		{
			MyGame->getCam()->setZoom(SaveZoom);
			MyGame->getCam()->HoldZoom = SaveHoldZoom;
			MyGame->getCam()->SetVertexCamera();
			EzText::ZoomWithCamera_Override = false;
			Tools::QDrawer->Flush();
		}
	}

	void ScoreScreen::MyPhsxStep()
	{
		boost::shared_ptr<Level> level = getCore()->MyLevel;

		if ( level != 0 )
			level->setPreventReset( true );

		if ( level->Replay || level->Watching )
			return;

		if ( Active )
		{
			if ( !ShouldSkip() )
			{
				if ( AsMenu )
					CkBaseMenu::MyPhsxStep();
				else
					GUI_Phsx();
			}
		}
	}

	void ScoreScreen::MenuGo_NewLevel( const boost::shared_ptr<MenuItem> &item )
	{
		GUI_Panel::SlideOut( PresetPos_LEFT );

		Active = false;

		//Tools::SongWad->FadeOut();
		MyGame->EndMusicOnFinish = false;

		MyGame->WaitThenDo( 36, boost::make_shared<ScoreScreenEndGameHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ), true ) );
		return;
	}

	void ScoreScreen::MenuGo_Continue( const boost::shared_ptr<MenuItem> &item )
	{
		GUI_Panel::SlideOut( PresetPos_LEFT );

		if (InCampaign)
		{
			boost::shared_ptr<StringWorldGameData> stringworld = boost::dynamic_pointer_cast<StringWorldGameData>( Tools::WorldMap );

			boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( Tools::CurLevel->FindIObject( LevelConnector::EndOfLevelCode ) );
			door->setOnOpen( d => GameData.EOL_DoorAction(d) );

			if ( stringworld != 0 )
			{
				bool fade = door->getMyLevel()->MyLevelSeed != 0 && door->getMyLevel()->MyLevelSeed->FadeOut;
				if (fade)
					door->setOnEnter(stringworld.EOL_StringWorldDoorEndAction_WithFade);
				else
					door->setOnEnter(EOL_WaitThenDoEndAction);
								   
				stringworld->EOL_StringWorldDoorAction( door );
			}
		}
		else
		{
			MyGame->WaitThenDo( SlideOutLength + 2, boost::make_shared<ScoreScreenEndGameHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ), false ) );
		}
	}

	void ScoreScreen::EOL_WaitThenDoEndAction( boost::shared_ptr<Door> door )
	{
		boost::shared_ptr<StringWorldGameData> stringworld = boost::dynamic_pointer_cast<StringWorldGameData>( Tools::WorldMap );

		if ( stringworld != 0 )
		{
			door->getGame()->WaitThenDo(35, () => stringworld.EOL_StringWorldDoorEndAction(door) );
		}
	}

	void ScoreScreen::MenuGo_ExitFreeplay( const boost::shared_ptr<MenuItem> &item )
	{
		GUI_Panel::SlideOut( PresetPos_LEFT );

		//if ( MyGame->ParentGame != 0 )
		//{
		//	CustomLevel_GUI::ExitFreeplay = true;
		//}

		MyGame->WaitThenDo( SlideOutLength + 2, boost::make_shared<ScoreScreenEndGameHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ), false ) );
	}

	void ScoreScreen::MenuGo_ExitCampaign( boost::shared_ptr<MenuItem> item )
	{
		Tools::CurrentAftermath = boost::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = false;
		Tools::CurrentAftermath->EarlyExit = true;

		Tools::CurGameData->EndGame( false );
	}

	void ScoreScreen::MenuGo_Stats( const boost::shared_ptr<MenuItem> &item )
	{
		Call( MakeMagic( StatsMenu, ( MyStatGroup ) ), 19 );
	}

	void ScoreScreen::MenuGo_WatchReplay( const boost::shared_ptr<MenuItem> &item )
	{
		if ( AsMenu )
		{
			Active = false;

			MyGame->WaitThenDo( 35, boost::make_shared<MenuGo_WatchReplayHelper>( boost::static_pointer_cast<ScoreScreen>( shared_from_this() ) ) );
		}
		else
		{
			getCore()->MyLevel->WatchReplay(true);
		}
	}

	void ScoreScreen::MenuGo_Save( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<PlayerData> player = MenuItem::GetActivatingPlayerData();
		SaveLoadSeedMenu::MakeSave( boost::static_pointer_cast<SaveLoadSeedMenu>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ), player )->Apply( item );
		Hide( PresetPos_LEFT );
	}

	bool ScoreScreen::ShouldSkip()
	{
		if ( LastActive + 5 < Tools::TheGame->PhsxCount )
		{
			LastActive = Tools::TheGame->PhsxCount;
			return true;
		}
		else
		{
			LastActive = Tools::TheGame->PhsxCount;
			return false;
		}
	}

	void ScoreScreen::GUI_Phsx()
	{
		boost::shared_ptr<Level> level = getCore()->MyLevel;

		if ( MyGame->MyLevel->getReplayAvailable() )
		{
			bool WatchReplay = false;
			if ( level->CanWatchReplay && ButtonCheck::State( ControllerButtons_X, -1 ).Pressed )
				WatchReplay = true;
	#if defined(PC_VERSION)
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Escape ) || KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_Escape ) )
			WatchReplay = false;
	#endif

			if ( WatchReplay )
				MenuGo_WatchReplay( 0 );
		}

		if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed )
			MenuGo_Continue( 0 );
	}

	void ScoreScreen::InitializeInstanceFields()
	{
		DelayPhsx = 5;
		ShiftAll = Vector2( -110, -20 );
		zoom = boost::make_shared<FancyVector2>();
		MyStatGroup = StatGroup_LEVEL;
	}
}
