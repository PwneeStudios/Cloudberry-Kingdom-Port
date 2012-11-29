#include <global_header.h>
namespace CloudberryKingdom
{

	GameOverPanel::MenuActiveHelper::MenuActiveHelper( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::MenuActiveHelper::Apply()
	{
		gop->MyMenu->Active = true;
	}

	GameOverPanel::TextBoxActiveHelper::TextBoxActiveHelper( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::TextBoxActiveHelper::Apply()
	{
		gop->MyTextBox->Active = true;
	}

	GameOverPanel::OnAddHelper::OnAddHelper( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::OnAddHelper::Apply()
	{
		// Slow Rise
		gop->SlideInFrom = PresetPos_BOTTOM;
		gop->SlideOut( PresetPos_BOTTOM, 0 );
		gop->SlideIn( 70 );

		// Prevent menu interactions for a second
		gop->MyMenu->Active = false;
		gop->MyGame->WaitThenDo( gop->DelayPhsx, std::make_shared<MenuActiveHelper>( gop ) );

	#if defined(PC_VERSION)
		if ( gop->MyTextBox != 0 )
			gop->MyGame->WaitThenDo( gop->DelayPhsx, std::make_shared<TextBoxActiveHelper>( gop ) );
		//MyMenu.Show = MyMenu.Active = false;
	#endif
	}

	GameOverPanel::MakeTextBoxHelper::MakeTextBoxHelper( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::MakeTextBoxHelper::Apply()
	{
		float width = gop->MyGame->getCam()->GetWidth();

		gop->MyMenu->Show = gop->MyMenu->Active = true;
		gop->MyMenu->FancyPos->LerpTo( gop->MenuPos + Vector2( width, 0 ), gop->MenuPos, 20 );
		gop->MyTextBox->Pos->LerpTo( Vector2( -width, 0 ), 20 );
	}

	GameOverPanel::OnEnterLambda::OnEnterLambda( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::OnEnterLambda::Apply()
	{
		// Use the entered text as the GamerTag
		gop->HighScoreEntry->GamerTag = gop->HighLevelEntry->GamerTag = gop->MyTextBox->Text;

		// Add the high score
		gop->AddScore();

		gop->MyGame->WaitThenDo( 35, std::make_shared<MakeTextBoxHelper>( gop ) );
	}

	GameOverPanel::Action_DoneHelper::Action_DoneHelper( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_DoneHelper::Apply()
	{
		gop->MyGame->EndGame->Apply( false );
	}

	GameOverPanel::Action_DoneProxy::Action_DoneProxy( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_DoneProxy::Apply()
	{
		gop->Action_Done();
	}

	GameOverPanel::Action_PlayAgainHelper::Action_PlayAgainHelper( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_PlayAgainHelper::Apply()
	{
		gop->MyGame->EndGame->Apply( true );
	}

	GameOverPanel::Action_PlayAgainProxy::Action_PlayAgainProxy( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_PlayAgainProxy::Apply()
	{
		gop->Action_PlayAgain();
	}

	GameOverPanel::Action_ShowHighScoresProxy::Action_ShowHighScoresProxy( const std::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_ShowHighScoresProxy::Apply()
	{
		gop->Action_ShowHighScores();
	}

	void GameOverPanel::Init()
	{
		CkBaseMenu::Init();

		getCore()->DrawLayer = Level::AfterPostDrawLayer;

		Fast();
	}

	void GameOverPanel::OnAdd()
	{
		CkBaseMenu::OnAdd();

		// Set the aftermath data to note the failure
		Tools::CurrentAftermath = std::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = false;

		// Absorb stats into the game's total stats
		PlayerManager::AbsorbTempStats();
		PlayerManager::AbsorbLevelStats();

		// Update HighScore list
		PlayerManager::CalcScore( StatGroup_GAME );
		Score = PlayerManager::GetGameScore();
		Attempts = PlayerManager::Score_Attempts;
		Time = PlayerManager::Score_Time;
		Date = ScoreDatabase::CurrentDate();
		ScoreDatabase::MostRecentScoreDate = Date;

//C# TO C++ CONVERTER NOTE: The variable GamerTag was renamed since it is named the same as a user-defined type:
		std::wstring GamerTag_Renamed = PlayerManager::GetGroupGamerTag( 18 );
		HighScoreEntry = std::make_shared<ScoreEntry>( GamerTag_Renamed, GameId_Score, Score, Score, Levels, Attempts, Time, Date );
		HighLevelEntry = std::make_shared<ScoreEntry>( GamerTag_Renamed, GameId_Level, Levels, Score, Levels, Attempts, Time, Date );

	#if defined(NOT_PC)
		AddScore();
	#endif
		Create();

		// Absorb game stats into life time stats
		PlayerManager::AbsorbGameStats();

		// Initially hide the score screen
		this->SlideOut( PresetPos_TOP, 0 );

		MyGame->WaitThenDo( Awardments::AwardDelay(), std::make_shared<OnAddHelper>(this) );
	}

	void GameOverPanel::Create()
	{
		MyPile = std::make_shared<DrawPile>();

		// Make the backdrop
		std::shared_ptr<QuadClass> backdrop = std::make_shared<QuadClass>( _T( "Score\\Score_Screen" ), 1440 );
		backdrop->Quad_Renamed->SetColor( Color( 220, 220, 220 ) );
		MyPile->Add( backdrop );
		backdrop->setPos( Vector2( 22.2233f, 10.55567f ) );

		// 'Game Over' text
		std::shared_ptr<EzText> Text = std::make_shared<EzText>( Localization::Words_GAME_OVER, Resources::Font_Grobold42_2, 1450, false, true,.6f );
		Text->setScale( 1 );
		Text->MyFloatColor = ( Color( 255, 255, 255 ) ).ToVector4();
		Text->OutlineColor = ( Color( 0, 0, 0 ) ).ToVector4();
		Text->setPos( Vector2( -675.6388f, 575.4443f ) );
		MyPile->Add( Text, _T( "Header" ) );
		//Text.Shadow = true;
		Text->ShadowColor = Color( .36f,.36f,.36f,.86f );
		Text->ShadowOffset = Vector2( -24, -20 );


		// 'Levels' text
		MyPile->Add( std::make_shared<EzText>( Localization::Words_LEVEL, ItemFont, _T( "Level" ) ) );
		Text = std::make_shared<EzText>( std::wstring::Format( _T( "{0}" ), Levels ), ItemFont );
		SetHeaderProperties( Text );
		Text->setPos( Vector2( -893.4177f, 378.9999f ) );
		MyPile->Add( Text, _T( "Level" ) );

		// 'Score' text
		MyPile->Add( std::make_shared<EzText>( Localization::Words_SCORE, ItemFont, _T( "Score" ) ) );
		Text = std::make_shared<EzText>( std::wstring::Format( _T( "{0}" ), Score ), ItemFont );
		SetHeaderProperties( Text );
		Text->setPos( Vector2( -873.9723f, 147.8889f ) );
		MyPile->Add( Text, _T( "Score" ) );

		// 'Distance' text
		//Text = new EzText("Distance: " + Distance.ToString() + " feet", ItemFont);
		//SetHeaderProperties(Text);
		//Text.Pos = new Vector2(-940.6393f, 145.6666f);
		//MyPile.Add(Text);

		MakeMenu();

		EnsureFancy();
		MyMenu->setPos( Vector2( 400, -240 ) );

	#if defined(PC_VERSION)
		MakeTextBox();
	#endif

		SetPos();
	}

	void GameOverPanel::SetPos()
	{
	}

#if defined(PC_VERSION)
	void GameOverPanel::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		if ( MyTextBox != 0 )
			MyTextBox->Release();
			MyTextBox.reset();
	}
#endif

#if defined(PC_VERSION)
	void GameOverPanel::MakeTextBox()
	{
		// Do nothing if the score doesn't qualify for the high score list
		if ( !MyHighScoreList->Qualifies( HighScoreEntry ) && ( MyHighLevelList == 0 || !MyHighLevelList->Qualifies( HighLevelEntry ) ) )
			return;

		// Make the text box to allow the player to enter their name
		MyTextBox = std::make_shared<GUI_EnterName>();
		MyTextBox->Active = false; // Keep inactive until parent GUI_Panel says it's OK to take input.
		MyTextBox->AutoDraw = false;
		MyGame->AddGameObject( MyTextBox );

		MyTextBox->Pos->SetCenter( Pos );
		MyTextBox->Pos->RelVal = Vector2( 95.23779f, -506 );
		MyTextBox->Pos->code = 23;

		// Hide the menu
		MenuPos = MyMenu->getPos();
		MyMenu->Show = MyMenu->Active = false;

		// Show the menu when the user is done entering their name
		MyTextBox->OnEnter->Add( std::make_shared<OnEnterLambda>( shared_from_this() ) );
	}
#endif

#if ! defined(PC_VERSION)
	void GameOverPanel::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();
	}
#endif

	void GameOverPanel::AddScore()
	{
		MyHighScoreList->Add( HighScoreEntry );
		MyHighLevelList->Add( HighLevelEntry );
		ScoreDatabase::Add( HighScoreEntry );
		ScoreDatabase::Add( HighLevelEntry );
	}

	void GameOverPanel::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->MyFloatColor = ( Color( 255, 254, 252 ) ).ToVector4();
		//text.MyFloatColor = new Color(255, 232, 77).ToVector4();
		text->setScale( text->getScale() * 1.48f );

		text->Shadow = false;
	}

	void GameOverPanel::MakeMenu()
	{
		MyMenu = std::make_shared<Menu>( false );

		MyMenu->setControl( -1 );

		MyMenu->OnB.reset();


		std::shared_ptr<MenuItem> item;
		FontScale *= .89f * 1.16f;

		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_PLAY_AGAIN, ItemFont ) );
		item->setGo( Cast::ToItem( std::make_shared<Action_PlayAgainProxy>( shared_from_this() ) ) );
		AddItem( item );

		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_HIGH_SCORES, ItemFont ) );
		item->setGo( Cast::ToItem( std::make_shared<Action_ShowHighScoresProxy>( shared_from_this() ) ) );
		AddItem( item );

		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_DONE, ItemFont ) );
		item->setGo( Cast::ToItem( std::make_shared<Action_DoneProxy>( shared_from_this() ) ) );
		AddItem( item );
	}

	void GameOverPanel::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->MyFloatColor = ( Color( 255, 255, 255 ) ).ToVector4();
		item->MySelectedText->MyFloatColor = ( Color( 50, 220, 50 ) ).ToVector4();
	}

	void GameOverPanel::Action_Done()
	{
		SlideOut( PresetPos_TOP, 13 );
		Active = false;

		Tools::SongWad->FadeOut();
		MyGame->WaitThenDo( 36, std::make_shared<Action_DoneHelper>( shared_from_this() ) );

		return;
	}

	void GameOverPanel::Action_PlayAgain()
	{
		SlideOut( PresetPos_TOP, 13 );
		Active = false;

		Tools::SongWad->FadeOut();

		MyGame->WaitThenDo( 36, std::make_shared<Action_PlayAgainHelper>( shared_from_this() ) );
		return;
	}

	void GameOverPanel::Action_ShowHighScores()
	{
		Hide( PresetPos_BOTTOM );
		Call( std::make_shared<HighScorePanel>( MyHighScoreList, MyHighLevelList ) );
	}

	GameOverPanel::GameOverPanel()
	{
		InitializeInstanceFields();
	}

	GameOverPanel::GameOverPanel( int GameId_Score, int GameId_Level )
	{
		InitializeInstanceFields();
		this->GameId_Score = GameId_Score;
		this->GameId_Level = GameId_Level;

		MyHighScoreList = ScoreDatabase::GetList( GameId_Score );
		MyHighScoreList->MyFormat = ScoreEntry::Format_SCORE;

		MyHighLevelList = ScoreDatabase::GetList( GameId_Level );
		MyHighLevelList->MyFormat = ScoreEntry::Format_LEVEL;
	}

	void GameOverPanel::MyDraw()
	{
		  CkBaseMenu::MyDraw();

	#if defined(PC_VERSION)
		if ( MyTextBox != 0 )
			MyTextBox->ManualDraw();
	#endif
	}

	void GameOverPanel::InitializeInstanceFields()
	{
		DelayPhsx = 42;
	}
}
