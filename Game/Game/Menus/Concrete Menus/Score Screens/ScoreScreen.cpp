#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	ScoreScreen::OnAddHelper::OnAddHelper( const std::shared_ptr<ScoreScreen> &ss )
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

	int ScoreScreen::VariableCoinsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->Coins;
	}

	ScoreScreen::VariableTotalCoinsLambda::VariableTotalCoinsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableTotalCoinsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->TotalCoins;
	}

	ScoreScreen::VariableBlobsLambda::VariableBlobsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableBlobsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->Blobs;
	}

	ScoreScreen::VariableTotalBlobsLambda::VariableTotalBlobsLambda( StatGroup MyStats )
	{
		this->MyStats = MyStats;
	}

	int ScoreScreen::VariableTotalBlobsLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return p->GetStats( MyStats )->TotalBlobs;
	}

	ScoreScreen::ScoreScreenEndGameHelper::ScoreScreenEndGameHelper( const std::shared_ptr<ScoreScreen> &ss, bool parameter )
	{
		this->ss = ss;
		this->parameter = parameter;
	}

	void ScoreScreen::ScoreScreenEndGameHelper::Apply()
	{
		ss->MyGame->EndGame->Apply( parameter );
	}

	ScoreScreen::MenuGo_NewLevelProxy::MenuGo_NewLevelProxy( const std::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_NewLevelProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_NewLevel( item );
	}

	ScoreScreen::MenuGo_ContinueProxy::MenuGo_ContinueProxy( const std::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_ContinueProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_Continue( item );
	}

	ScoreScreen::MenuGo_WatchReplayHelper::MenuGo_WatchReplayHelper( const std::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_WatchReplayHelper::Apply()
	{
		ss->OnReturnTo(); // Re-activate the Score Screen object
		ss->getCore()->MyLevel->WatchReplay(true); // Start the replay
	}

	ScoreScreen::MenuGo_WatchReplayProxy::MenuGo_WatchReplayProxy( const std::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_WatchReplayProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_WatchReplay( item );
	}

	ScoreScreen::MenuGo_SaveProxy::MenuGo_SaveProxy( const std::shared_ptr<ScoreScreen> &ss )
	{
		this->ss = ss;
	}

	void ScoreScreen::MenuGo_SaveProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		ss->MenuGo_Save( item );
	}

	void ScoreScreen::MakeMenu()
	{
		if ( AsMenu )
		{
			MyMenu = std::make_shared<Menu>( false );

			MyMenu->setControl( -1 );

			MyMenu->OnB.reset();

			_Add_Watch = MyGame->MyLevel->getReplayAvailable();
			_Add_Save = MyGame->MyLevel->MyLevelSeed != 0 && MyGame->MyLevel->MyLevelSeed->Saveable;

			std::shared_ptr<MenuItem> item;

			item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_KEEP_SETTINGS, ItemFont ) );
			item->Name = _T( "Continue" );
			item->setGo( std::make_shared<MenuGo_NewLevelProxy>( this ) );
			AddItem( item );
			item->MyText->setScale(item->MySelectedText->setScale(item->MyText->setScale(item->MySelectedText->getScale() * 1.3f));
			item->Shift( Vector2( -86, 65 ) );
			item->SelectedPos.X += 6;

			if ( _Add_Watch )
			{
				item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_WATCH_REPLAY, ItemFont ) );
				item->Name = _T( "Replay" );
				item->setGo( std::make_shared<MenuGo_WatchReplayProxy>( this ) );
				AddItem( item );
			}

			if ( _Add_Save )
			{
				item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_SAVED_SEEDS, ItemFont ) );
				item->Name = _T( "Save" );
				item->setGo( std::make_shared<MenuGo_SaveProxy>( this ) );
				AddItem( item );
			}

			MakeBackButton( Localization::Words_BACK_TO_FREEPLAY );
			MyMenu->OnB = Cast::ToMenu( std::make_shared<MenuGo_ContinueProxy>( this ) );

			EnsureFancy();
			MyMenu->FancyPos->RelVal = Vector2( 869.0476f, -241.6667f );
		}
		else
		{
			std::shared_ptr<QuadClass> ContinueButton = std::make_shared<QuadClass>( ButtonTexture::getGo(), 90, false );
			ContinueButton->Name = _T( "GoButton" );
			MyPile->Add( ContinueButton );
			ContinueButton->setPos( Vector2( 180, -477.7778f ) + ShiftAll );

			std::shared_ptr<EzText> ContinueText = std::make_shared<EzText>( Localization::Words_CONTINUE, ItemFont );
			ContinueText->Name = _T( "Continue" );
			SetHeaderProperties( ContinueText );
			ContinueText->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;
			MyPile->Add( ContinueText );
			ContinueText->setPos( Vector2( 180, -477.7778f ) + ShiftAll );

			if ( MyGame->MyLevel->getReplayAvailable() )
			{
				std::shared_ptr<QuadClass> XButton = std::make_shared<QuadClass>( ButtonTexture::getX(), 90, false );
				XButton->Name = _T( "XButton" );
				MyPile->Add( XButton );
				XButton->setPos( Vector2( 180, -325.3333f ) + ShiftAll );

				std::shared_ptr<EzText> ReplayText = std::make_shared<EzText>( Localization::Words_WATCH_REPLAY, ItemFont );
				SetHeaderProperties( ReplayText );
				ReplayText->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
				ReplayText->MyFloatColor = ( Color( 184, 231, 231 ) ).ToVector4();
				MyPile->Add( ReplayText );
				ReplayText->setPos( Vector2( 180, -325.3333f ) + ShiftAll );
			}
		}
	}

	ScoreScreen::ScoreScreen( bool CallBaseConstructor ) : CkBaseMenu( CallBaseConstructor )
	{
		InitializeInstanceFields();
	}

	ScoreScreen::ScoreScreen( StatGroup group, const std::shared_ptr<GameData> &game ) : CkBaseMenu( false )
	{
		InitializeInstanceFields();
		MyGame = game;
		MyStatGroup = group;
		FontScale = .6f;

		Constructor();
	}

	void ScoreScreen::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		CkColorHelper::GreenItem( item );
	}

	void ScoreScreen::SetHeaderProperties( const std::shared_ptr<EzText> &text )
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

		MyPile = std::make_shared<DrawPile>();

		//MakeDarkBack();

		std::shared_ptr<QuadClass> Backdrop = std::make_shared<QuadClass>( _T( "Backplate_1230x740" ), _T( "Backdrop" ) );
		MyPile->Add( Backdrop );
		MyPile->Add( Backdrop );

		LevelCleared = std::make_shared<QuadClass>( _T( "Score\\LevelCleared" ), _T( "Header" ) );
		LevelCleared->Scale( .9f );
		MyPile->Add( LevelCleared );
		LevelCleared->setPos( Vector2( 10, 655 ) + ShiftAll );

		MyPile->Add( std::make_shared<QuadClass>( _T( "Coin_Blue" ), _T( "Coin" ) ) );
		MyPile->Add( std::make_shared<QuadClass>( _T( "Stopwatch_Black" ), _T( "Stopwatch" ) ) );
		MyPile->Add( std::make_shared<QuadClass>( _T( "Bob_Dead" ), _T( "Death" ) ) );

		MakeMenu();

		ScoreSound = Tools::SoundWad->FindByName( _T( "Coin" ) );
		BonusSound = Tools::SoundWad->FindByName( _T( "Coin" ) );
		ScoreSound->MaxInstances = 2;

		SetPos();
	}

	void ScoreScreen::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Continue" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -871.7776f, 516.6667f ) );
			_item->MyText->setScale( 0.78f );
			_item->MySelectedText->setScale( 0.78f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Save" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -646.8889f, 266.6737f ) );
			_item->MyText->setScale( 0.6f );
			_item->MySelectedText->setScale( 0.6f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Replay" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -641.3332f, 91.67379f ) );
			_item->MyText->setScale( 0.6f );
			_item->MySelectedText->setScale( 0.6f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -755.2222f, -75.5462f ) );
			_item->MyText->setScale( 0.6f );
			_item->MySelectedText->setScale( 0.6f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 902.3811f, -136.1111f ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Coins" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -719.4445f, 22.22227f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( _T( "Blobs" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -661.1107f, -402.7777f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( _T( "Deaths" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -655.5553f, 411.1111f ) );
			_t->setScale( 1 );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 27.77808f, -6.666618f ) );
			_q->setSize( Vector2( 1509.489f, 943.4307f ) );
		}
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 27.77808f, -6.666618f ) );
			_q->setSize( Vector2( 1509.489f, 943.4307f ) );
		}
		_q = MyPile->FindQuad( _T( "Header" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 16.66687f, 615.5555f ) );
			_q->setSize( Vector2( 937.8f, 147.6f ) );
		}
		_q = MyPile->FindQuad( _T( "Coin" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -955.5555f, -141.6665f ) );
			_q->setSize( Vector2( 168.1188f, 168.1188f ) );
		}
		_q = MyPile->FindQuad( _T( "Stopwatch" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -886.1108f, -513.8888f ) );
			_q->setSize( Vector2( 180.9532f, 211.6065f ) );
		}
		_q = MyPile->FindQuad( _T( "Death" ) );
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
			for ( int i = 0; i < DrawPile::BubbleScale.size(); ++i )
			{
				copy[ i ] = ( DrawPile::BubbleScale[ i ] - Vector2::One ) *.3f + Vector2::One;
			}
			zoom->MultiLerp( 6, copy );
		}

		// Calculate scores
		PlayerManager::CalcScore( MyStatGroup );

		int Coins = PlayerManager::PlayerSum( std::make_shared<VariableCoinsLambda>( MyStatGroup ) );
		int CoinTotal = PlayerManager::PlayerMax( std::make_shared<VariableTotalBlobsLambda>( MyStatGroup ) );
		int Blobs = PlayerManager::PlayerSum( std::make_shared<VariableBlobsLambda>( MyStatGroup ) );
		int BlobTotal = PlayerManager::PlayerMax( std::make_shared<VariableTotalBlobsLambda>( MyStatGroup ) );

		MyPile->Add( std::make_shared<EzText>( Tools::ScoreString( Coins, CoinTotal ), ItemFont, _T( "Coins" ) ) );
		MyPile->Add( std::make_shared<EzText>( CoreMath::ShortTime( PlayerManager::Score_Time ), ItemFont, _T( "Blobs" ) ) );
		MyPile->Add( std::make_shared<EzText>( Tools::ScoreString( PlayerManager::Score_Attempts ), ItemFont, _T( "Deaths" ) ) );

		// Awardments
		Awardments::CheckForAward_HoldForward();
		Awardments::CheckForAward_NoCoins();

		// Prevent menu interactions for a second
		MyMenu->Active = false;

		SetPos();
		MyMenu->SortByHeight();

		MyGame->WaitThenDo( DelayPhsx, std::make_shared<OnAddHelper>( this ) );
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
		std::shared_ptr<Level> level = getCore()->MyLevel;

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

	void ScoreScreen::MenuGo_NewLevel( const std::shared_ptr<MenuItem> &item )
	{
		SlideOut( PresetPos_LEFT );

		Active = false;

		Tools::SongWad->FadeOut();

		MyGame->WaitThenDo( 36, std::make_shared<ScoreScreenEndGameHelper>( this, true ) );
		return;
	}

	void ScoreScreen::MenuGo_Continue( const std::shared_ptr<MenuItem> &item )
	{
		SlideOut( PresetPos_LEFT );

		MyGame->WaitThenDo( SlideOutLength + 2, std::make_shared<ScoreScreenEndGameHelper>( this, false ) );
	}

	bool ScoreScreen::MenuGo_ExitFreeplay( const std::shared_ptr<Menu> &menu )
	{
		SlideOut( PresetPos_LEFT );

		if ( MyGame->ParentGame != 0 )
		{
			CustomLevel_GUI::ExitFreeplay = true;
		}

		MyGame->WaitThenDo( SlideOutLength + 2, std::make_shared<ScoreScreenEndGameHelper>( this, false ) );

		return true;
	}

	void ScoreScreen::MenuGo_Stats( const std::shared_ptr<MenuItem> &item )
	{
		Call( std::make_shared<StatsMenu>( MyStatGroup ), 19 );
	}

	void ScoreScreen::MenuGo_WatchReplay( const std::shared_ptr<MenuItem> &item )
	{
		if ( AsMenu )
		{
			Active = false;

			MyGame->WaitThenDo( 35, std::make_shared<MenuGo_WatchReplayHelper>( this ) );
		}
		else
		{
			getCore()->MyLevel->WatchReplay(true);
		}
	}

	void ScoreScreen::MenuGo_Save( const std::shared_ptr<MenuItem> &item )
	{
		std::shared_ptr<PlayerData> player = MenuItem::GetActivatingPlayerData();
		SaveLoadSeedMenu::MakeSave( this, player )->Apply( item );
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
		std::shared_ptr<Level> level = getCore()->MyLevel;

		if ( MyGame->MyLevel->getReplayAvailable() )
		{
			bool WatchReplay = false;
			if ( level->CanWatchReplay && ButtonCheck::State( ControllerButtons_X, -1 ).Pressed )
				WatchReplay = true;
	#if defined(PC_VERSION)
		if ( Tools::Keyboard.IsKeyDownCustom( Microsoft::Xna::Framework::Input::Keys::Escape ) || Tools::PrevKeyboard.IsKeyDownCustom( Microsoft::Xna::Framework::Input::Keys::Escape ) )
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
		zoom = std::make_shared<FancyVector2>();
		MyStatGroup = StatGroup_LEVEL;
	}
}
