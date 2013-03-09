#include <global_header.h>

#include <Hacks/String.h>

#include <Game\Player\Leaderboard.h>
#include <Game\Player\LeaderboardView.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	GameOverPanel::MenuActiveHelper::MenuActiveHelper( const boost::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::MenuActiveHelper::Apply()
	{
		gop->MyMenu->Active = true;
	}

	GameOverPanel::TextBoxActiveHelper::TextBoxActiveHelper( const boost::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::TextBoxActiveHelper::Apply()
	{
		gop->MyTextBox->Active = true;
	}

	GameOverPanel::OnAddHelper::OnAddHelper( const boost::shared_ptr<GameOverPanel> &gop )
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
		gop->MyGame->WaitThenDo( gop->DelayPhsx, boost::make_shared<MenuActiveHelper>( gop ) );

	#if defined(PC_VERSION)
		if ( gop->MyTextBox != 0 )
			gop->MyGame->WaitThenDo( gop->DelayPhsx, boost::make_shared<TextBoxActiveHelper>( gop ) );
		//MyMenu.Show = MyMenu.Active = false;
	#endif
	}

	GameOverPanel::MakeTextBoxHelper::MakeTextBoxHelper( const boost::shared_ptr<GameOverPanel> &gop )
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

	GameOverPanel::OnEnterLambda::OnEnterLambda( const boost::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::OnEnterLambda::Apply()
	{
		// Use the entered text as the GamerTag
		gop->HighScoreEntry->GamerTag_Renamed = gop->HighLevelEntry->GamerTag_Renamed = gop->MyTextBox->getText();

		// Add the high score
		gop->AddScore();

		gop->MyGame->WaitThenDo( 35, boost::make_shared<MakeTextBoxHelper>( gop ) );
	}

	GameOverPanel::Action_DoneHelper::Action_DoneHelper( const boost::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_DoneHelper::Apply()
	{
		gop->MyGame->EndGame->Apply( false );
	}

	GameOverPanel::Action_DoneProxy::Action_DoneProxy( const boost::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_DoneProxy::Apply()
	{
		gop->Action_Done();
	}

	GameOverPanel::Action_PlayAgainHelper::Action_PlayAgainHelper( const boost::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_PlayAgainHelper::Apply()
	{
		gop->MyGame->EndGame->Apply( true );
	}

	GameOverPanel::Action_PlayAgainProxy::Action_PlayAgainProxy( const boost::shared_ptr<GameOverPanel> &gop )
	{
		this->gop = gop;
	}

	void GameOverPanel::Action_PlayAgainProxy::Apply()
	{
		gop->Action_PlayAgain();
	}

	GameOverPanel::Action_ShowHighScoresProxy::Action_ShowHighScoresProxy( const boost::shared_ptr<GameOverPanel> &gop )
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
		Tools::CurrentAftermath = boost::make_shared<AftermathData>();
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
		HighScoreEntry = boost::make_shared<ScoreEntry>( GamerTag_Renamed, GameId_Score, Score, Score, Levels, Attempts, Time, Date );
		HighLevelEntry = boost::make_shared<ScoreEntry>( GamerTag_Renamed, GameId_Level, Levels, Score, Levels, Attempts, Time, Date );

	#if defined(NOT_PC)
		AddScore();
	#endif
		Create();

		// Absorb game stats into life time stats
		PlayerManager::AbsorbGameStats();

		// Initially hide the score screen
		this->SlideOut( PresetPos_TOP, 0 );

		MyGame->WaitThenDo( Awardments::AwardDelay(), boost::make_shared<OnAddHelper>( boost::static_pointer_cast<GameOverPanel>( shared_from_this() ) ) );
	}

	void GameOverPanel::Create()
	{
		MyPile = boost::make_shared<DrawPile>();

		// Make the backdrop
		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( std::wstring( L"Score_Screen" ), 1440.f );
		backdrop->Quad_Renamed.SetColor( bColor( 220, 220, 220 ) );
		MyPile->Add( backdrop );
		backdrop->setPos( Vector2( 22.2233f, 10.55567f ) );

		// 'Game Over' text
		boost::shared_ptr<EzText> Text = boost::make_shared<EzText>( Localization::Words_GameOver, Resources::Font_Grobold42_2, 1450.f, false, true, .6f );
		Text->setScale( 1 );
		Text->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		Text->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();
		Text->setPos( Vector2( -675.6388f, 575.4443f ) );
		MyPile->Add( Text, std::wstring( L"Header" ) );
		//Text.Shadow = true;
		Text->ShadowColor = Color( .36f,.36f,.36f,.86f );
		Text->ShadowOffset = Vector2( -24, -20 );


		// 'Levels' text
		MyPile->Add( boost::make_shared<EzText>( Localization::Words_Level, ItemFont, static_cast<std::wstring>( std::wstring( L"Level" ) ) ) );
		Text = boost::make_shared<EzText>( Format( _T( "%d" ), Levels ), ItemFont );
		SetHeaderProperties( Text );
		Text->setPos( Vector2( -893.4177f, 378.9999f ) );
		MyPile->Add( Text, std::wstring( L"LevelVal" ) );

		// 'Score' text
		MyPile->Add( boost::make_shared<EzText>( Localization::Words_Score, ItemFont, static_cast<std::wstring>( std::wstring( L"Score" ) ) ) );
		Text = boost::make_shared<EzText>( Format( _T( "%d" ), Score ), ItemFont );
		SetHeaderProperties( Text );
		Text->setPos( Vector2( -873.9723f, 147.8889f ) );
		MyPile->Add( Text, std::wstring( L"ScoreVal" ) );

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
            //MenuItem _item;
            //_item = MyMenu.FindItemByName(""); if (_item != null) { _item.SetPos = new Vector2(-808f, 110f); _item.MyText.Scale = 0.7743f; _item.MySelectedText.Scale = 0.7743f; _item.SelectIconOffset = new Vector2(0f, 0f); }
            //_item = MyMenu.FindItemByName(""); if (_item != null) { _item.SetPos = new Vector2(-808f, -68.33099f); _item.MyText.Scale = 0.7743f; _item.MySelectedText.Scale = 0.7743f; _item.SelectIconOffset = new Vector2(0f, 0f); }
            //_item = MyMenu.FindItemByName(""); if (_item != null) { _item.SetPos = new Vector2(-808f, -246.662f); _item.MyText.Scale = 0.7743f; _item.MySelectedText.Scale = 0.7743f; _item.SelectIconOffset = new Vector2(0f, 0f); }

            MyMenu->setPos( Vector2( 400.f, -240.f ) );

            boost::shared_ptr<EzText> _t;
            _t = MyPile->FindEzText( L"Header" ); if (_t != 0) { _t->setPos( Vector2(-675.6388f, 575.4443f) ); _t->setScale( 1.f ); }
            _t = MyPile->FindEzText( L"Level" ); if (_t != 0) { _t->setPos( Vector2(-857.3064f, 384.5554f) ); _t->setScale( 0.999f ); }
            _t = MyPile->FindEzText( L"LevelVal" ); if (_t != 0) { _t->setPos( Vector2(-26.75146f, 376.2222f) ); _t->setScale( 0.999f ); }
            _t = MyPile->FindEzText( L"Score" ); if (_t != 0) { _t->setPos( Vector2(-871.1947f, 159.f) ); _t->setScale( 0.999f ); }
            _t = MyPile->FindEzText( L"ScoreVal" ); if (_t != 0) { _t->setPos( Vector2(-12.86145f, 150.6666f) ); _t->setScale( 0.999f ); }

            QuadClass _q;
            //_q = MyPile->FindQuad( L"" ); if (_q != null) { _q->setPos( Vector2(22.2233f, 10.55567f); _q.Size = Vector2(1440f, 900f) ); }

            MyPile->setPos( Vector2(0.f, 0.f) );
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
		MyTextBox = MakeMagic( GUI_EnterName, () );
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
		MyTextBox->OnEnter->Add( boost::make_shared<OnEnterLambda>( boost::static_pointer_cast<GameOverPanel>( shared_from_this() ) ) );
	}
#endif

#if ! defined(PC_VERSION)
	void GameOverPanel::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();
	}
#endif

	extern bool IsParentalLevelSatisfied( bool );

	void GameOverPanel::AddScore()
	{
		MyHighScoreList->Add( HighScoreEntry );
		MyHighLevelList->Add( HighLevelEntry );
		ScoreDatabase::Add( HighScoreEntry );
		ScoreDatabase::Add( HighLevelEntry );

            boost::shared_ptr<ScoreEntry> score = HighScoreEntry;

			int highscore = __max( score->Score, PlayerManager::MaxPlayerHighScore( score->GameId ) );
            boost::shared_ptr<ScoreEntry> copy = boost::make_shared<ScoreEntry>( score->GamerTag_Renamed, score->GameId, highscore, highscore, score->Level_Renamed, score->Attempts, score->Time, score->Date );
            copy->GameId += Challenge::LevelMask;

			Leaderboard::WriteToLeaderboard( copy );


        //Leaderboard::WriteToLeaderboard(HighScoreEntry);
        //Leaderboard::WriteToLeaderboard(HighLevelEntry);

        ArcadeMenu::CheckForArcadeUnlocks(HighScoreEntry);

		if( IsParentalLevelSatisfied( false ) )
		{
			if ( !CloudberryKingdomGame::OnlineFunctionalityAvailable() )
			{
				CloudberryKingdomGame::ShowError_MustBeSignedInToLiveForLeaderboard();
			}
		}
	}

	void GameOverPanel::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->MyFloatColor = ( bColor( 255, 254, 252 ) ).ToVector4();
		//text.MyFloatColor = new Color(255, 232, 77).ToVector4();
		text->setScale( text->getScale() * 1.48f );

		text->Shadow = false;
	}

	void GameOverPanel::MakeMenu()
	{
		MyMenu = boost::make_shared<Menu>( false );

		MyMenu->setControl( -1 );

		MyMenu->OnB.reset();


		boost::shared_ptr<MenuItem> item;
		FontScale *= .89f * 1.16f;

		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_PlayAgain, ItemFont ) ) );
		item->setGo( Cast::ToItem( boost::make_shared<Action_PlayAgainProxy>( boost::static_pointer_cast<GameOverPanel>( shared_from_this() ) ) ) );
		AddItem( item );

		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_HighScores, ItemFont ) ) );
		item->setGo( Cast::ToItem( boost::make_shared<Action_ShowHighScoresProxy>( boost::static_pointer_cast<GameOverPanel>( shared_from_this() ) ) ) );
		AddItem( item );

		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Done, ItemFont ) ) );
		item->setGo( Cast::ToItem( boost::make_shared<Action_DoneProxy>( boost::static_pointer_cast<GameOverPanel>( shared_from_this() ) ) ) );
		AddItem( item );
	}

	void GameOverPanel::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		item->MySelectedText->MyFloatColor = ( bColor( 50, 220, 50 ) ).ToVector4();
	}

	void GameOverPanel::Action_Done()
	{
		SlideOut( PresetPos_TOP, 13 );
		Active = false;

		Tools::SongWad->FadeOut();
		MyGame->WaitThenDo( 36, boost::make_shared<Action_DoneHelper>( boost::static_pointer_cast<GameOverPanel>( shared_from_this() ) ) );

		return;
	}

	void GameOverPanel::Action_PlayAgain()
	{
		SlideOut( PresetPos_TOP, 13 );
		Active = false;

		Tools::SongWad->FadeOut();

		MyGame->WaitThenDo( 36, boost::make_shared<Action_PlayAgainHelper>( boost::static_pointer_cast<GameOverPanel>( shared_from_this() ) ) );
		return;
	}

	void GameOverPanel::Action_ShowHighScores()
	{
		if ( CloudberryKingdomGame::SimpleLeaderboards )
		{
			Hide( PresetPos_BOTTOM );
			Call( MakeMagic( HighScorePanel, ( MyHighScoreList, MyHighLevelList ) ) );
		}
		else
		{
			if( IsParentalLevelSatisfied( true ) )
			{
				if ( CloudberryKingdomGame::OnlineFunctionalityAvailable() )
				{
					Hide( PresetPos_BOTTOM );
					Call( MakeMagic( LeaderboardGUI, ( 0, MenuItem::ActivatingPlayer ) ), 0 );
					Hide();
				}
				else
				{
					CloudberryKingdomGame::ShowError_MustBeSignedInToLive( Localization::Words_Err_MustBeSignedInToLive );
				}
			}
		}
	}

	GameOverPanel::GameOverPanel() :
		GameId_Score( 0 ), GameId_Level( 0 ),
		Score( 0 ), Levels( 0 ), Attempts( 0 ), Time( 0 ), Date( 0 ),
		DelayPhsx( 0 )
	{
	}

	boost::shared_ptr<GameOverPanel> GameOverPanel::GameOverPanel_Construct()
	{
		InitializeInstanceFields();
		CkBaseMenu::CkBaseMenu_Construct();

		return boost::static_pointer_cast<GameOverPanel>( shared_from_this() );
	}

	GameOverPanel::GameOverPanel( int GameId_Score, int GameId_Level ) :
		GameId_Score( 0 ), GameId_Level( 0 ),
		Score( 0 ), Levels( 0 ), Attempts( 0 ), Time( 0 ), Date( 0 ),
		DelayPhsx( 0 )
	{
	}
	boost::shared_ptr<GameOverPanel> GameOverPanel::GameOverPanel_Construct( int GameId_Score, int GameId_Level )
	{
		InitializeInstanceFields();
		CkBaseMenu::CkBaseMenu_Construct();
		
		this->GameId_Score = GameId_Score;
		this->GameId_Level = GameId_Level;

		MyHighScoreList = ScoreDatabase::GetList( GameId_Score );
		MyHighScoreList->MyFormat = ScoreEntry::Format_SCORE;

		MyHighLevelList = ScoreDatabase::GetList( GameId_Level );
		MyHighLevelList->MyFormat = ScoreEntry::Format_LEVEL;

		return boost::static_pointer_cast<GameOverPanel>( shared_from_this() );
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
