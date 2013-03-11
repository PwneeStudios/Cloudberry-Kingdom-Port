#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include <Game\Player\LeaderboardView.h>

namespace CloudberryKingdom
{

	HeroSelectOptions::BringLeaderboardProxy::BringLeaderboardProxy( const boost::shared_ptr<HeroSelectOptions> &hso )
	{
		this->hso = hso;
	}

	void HeroSelectOptions::BringLeaderboardProxy::Apply()
	{
		hso->BringLeaderboard();
	}

	HeroSelectOptions::HeroSelectOptions( const boost::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect ) : ArcadeBaseMenu() { }
	boost::shared_ptr<HeroSelectOptions> HeroSelectOptions::HeroSelectOptions_Construct( const boost::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect )
	{
		ArcadeBaseMenu::ArcadeBaseMenu_Construct();

		this->HeroSelect = HeroSelect;

		return boost::static_pointer_cast<HeroSelectOptions>( shared_from_this() );
	}

	void HeroSelectOptions::Release()
	{
		ArcadeBaseMenu::Release();

		HeroSelect.reset();
	}

	void HeroSelectOptions::SlideIn( int Frames )
	{
		ArcadeBaseMenu::SlideIn( 0 );
	}

	void HeroSelectOptions::SlideOut( PresetPos Preset, int Frames )
	{
		ArcadeBaseMenu::SlideOut( Preset, 0 );
	}

	void HeroSelectOptions::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		ArcadeBaseMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;

		StartMenu::SetItemProperties_Green( item, true );

		item->MyText->OutlineColor.W *= .4f;
		item->MySelectedText->OutlineColor.W *= .7f;
	}

	void HeroSelectOptions::OnAdd()
	{
		ArcadeBaseMenu::OnAdd();
	}

	extern bool IsParentalLevelSatisfied( bool );

	void HeroSelectOptions::BringLeaderboard()
	{
		if ( CloudberryKingdomGame::SimpleLeaderboards )
		{
			boost::shared_ptr<HeroItem> item = boost::dynamic_pointer_cast<HeroItem>( HeroSelect->MyMenu->getCurItem() );
			if ( 0 == item )
				return;

			boost::shared_ptr<CloudberryKingdom::Challenge> challenge = HeroSelect->MyArcadeItem->MyChallenge;
			challenge->SetGameId();

			int GameId_Score = HeroSelect->MyArcadeItem->MyChallenge->GameId_Score;
			int GameId_Level = HeroSelect->MyArcadeItem->MyChallenge->GameId_Level;

			boost::shared_ptr<CloudberryKingdom::ScoreList> MyHighScoreList = ScoreDatabase::GetList( GameId_Score );
			MyHighScoreList->MyFormat = ScoreEntry::Format_SCORE;

			boost::shared_ptr<CloudberryKingdom::ScoreList> MyHighLevelList = ScoreDatabase::GetList( GameId_Level );
			MyHighLevelList->MyFormat = ScoreEntry::Format_LEVEL;

			boost::shared_ptr<HighScorePanel> panel = MakeMagic( HighScorePanel, ( true, MyHighScoreList, MyHighLevelList ) );
			panel->NoDelays();
			HeroSelect->Call( panel );
			HeroSelect->Hide();
			HeroSelect->MyHeroDoll->Hide();
		}
		else
		{
			if( IsParentalLevelSatisfied( true ) )
			{
				if ( CloudberryKingdomGame::OnlineFunctionalityAvailable() )
				{
					HeroSelect->Call( MakeMagic( LeaderboardGUI, ( 0, MenuItem::ActivatingPlayer ) ), 0 );
					HeroSelect->Hide();
					HeroSelect->MyHeroDoll->Hide();
				}
				else
				{
					CloudberryKingdomGame::ShowError_MustBeSignedInToLive( Localization::Words_Err_MustBeSignedInToLive );
				}
			}
		}
	}

	void HeroSelectOptions::MyPhsxStep()
	{
		ArcadeBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

		if ( ButtonCheck::State( ControllerButtons_X, getControl() ).Pressed )
			BringLeaderboard();
	}

	void HeroSelectOptions::Init()
	{
		ArcadeBaseMenu::Init();

		MyPile = boost::make_shared<DrawPile>();

		CallDelay = ReturnToCallerDelay = 0;

		// Options. Menu for PC, graphics only for consoles.
#if defined(PC_VERSION)
		// Menu
		MyMenu = boost::make_shared<Menu>();
		MyMenu->OnB.reset();

		EnsureFancy();

		boost::shared_ptr<MenuItem> item;

		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 80.f, static_cast<std::wstring>( std::wstring( L"Button_X" ) ) ) );
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Leaderboard, ItemFont, false, true ) ) );

		item->Name = std::wstring( L"Leaderboard" );
		item->setGo( Cast::ToItem( boost::make_shared<BringLeaderboardProxy>( boost::static_pointer_cast<HeroSelectOptions>( shared_from_this() ) ) ) );
		AddItem( item );
		StartMenu_MW_HeroSelect::SetItemProperties_FadedOnUnselect( item );
		
		MyMenu->MouseOnly = true;
		MyMenu->NoneSelected = true;
#else
		EnsureFancy();

		std::wstring Space = std::wstring( L"{s34,0}" );
		boost::shared_ptr<EzText> StartText = boost::make_shared<EzText>( ButtonString::Go( 80 ) + Space + std::wstring( L" " ) + Localization::WordString( Localization::Words_Start ), ItemFont, true, true );
		MyPile->Add( StartText, std::wstring( L"Go" ) );

		boost::shared_ptr<EzText> LeaderText = boost::make_shared<EzText>( ButtonString::X( 80 ) + Space + std::wstring( L" " ) + Localization::WordString( Localization::Words_Leaderboard ), ItemFont, true, true );
		MyPile->Add( LeaderText, std::wstring( L"Leaderboard" ) );

	#if PS3
		StartText->MyFloatColor = ColorHelper::Gray(.9f);
		LeaderText->MyFloatColor = ColorHelper::Gray(.9f);			
	#endif

#endif

#if defined(PC_VERSION)
		SetPos_PC();
#else
		SetPos_Console();
#endif
	}

	void HeroSelectOptions::SetPos_Console()
	{
			if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_CHINESE )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 408.3333f, -516.6668f ) ); _t->setScale( 0.7152506f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 491.667f, -702.7776f ) ); _t->setScale( 0.7393336f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 602.7778f, -530.5557f ) ); _t->setScale( 0.7182506f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 672.2222f, -711.111f ) ); _t->setScale( 0.7266668f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 697.2224f, -525.0001f ) ); _t->setScale( 0.7423338f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 683.3337f, -711.111f ) ); _t->setScale( 0.7547504f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 474.9998f, -472.2224f ) ); _t->setScale( 0.7164173f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 708.3333f, -652.7776f ) ); _t->setScale( 0.743167f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 399.9998f, -522.2224f ) ); _t->setScale( 0.6441671f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 744.4443f, -686.1109f ) ); _t->setScale( 0.6407505f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 413.8887f, -525.f ) ); _t->setScale( 0.7423338f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 658.3333f, -708.3331f ) ); _t->setScale( 0.7660002f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 427.7773f, -522.2224f ) ); _t->setScale( 0.7423338f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 513.8887f, -711.111f ) ); _t->setScale( 0.7660002f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 477.7776f, -538.889f ) ); _t->setScale( 0.6902504f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 536.1111f, -705.5554f ) ); _t->setScale( 0.6942502f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 395.6355f, -525.0002f ) ); _t->setScale( 0.6706704f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 748.0187f, -687.6974f ) ); _t->setScale( 0.6805836f ); }
				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Go" ); if (_t != 0 ) { _t->setPos( Vector2( 513.8887f, -472.2224f ) ); _t->setScale( 0.7423338f ); }
				_t = MyPile->FindEzText( L"Leaderboard" ); if (_t != 0 ) { _t->setPos( Vector2( 825.f, -655.5554f ) ); _t->setScale( 0.7660002f ); }

				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
	}

	void HeroSelectOptions::SetPos_PC()
	{
			if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
			{
				boost::shared_ptr<MenuItem> _item;
				_item = MyMenu->FindItemByName( L"Leaderboard" ); if (_item != 0 ) { _item->setSetPos( Vector2(-658.0005f, 112.7778f ) ); _item->MyText->setScale( 0.6180833f ); _item->MySelectedText->setScale( 0.6180833f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

				MyMenu->setPos( Vector2( 947.2223f, -608.3333f ) );

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2( 130.5556f, -627.7776f ) ); _q->setSize( Vector2( 80.f, 75.2f ) ); }

				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
			else
			{
				boost::shared_ptr<MenuItem> _item;
				_item = MyMenu->FindItemByName( L"Leaderboard" ); if (_item != 0 ) { _item->setSetPos( Vector2(-638.5557f, 110.f ) ); _item->MyText->setScale( 0.75f ); _item->MySelectedText->setScale( 0.75f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

				MyMenu->setPos( Vector2( 947.2223f, -608.3333f ) );

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2( 113.8889f, -624.9999f ) ); _q->setSize( Vector2( 80.f, 75.2f ) ); }

				MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
			}
	}

	void HeroSelectOptions::Go( const boost::shared_ptr<MenuItem> &item )
	{
        boost::shared_ptr<HeroItem> _item = boost::dynamic_pointer_cast<HeroItem>( HeroSelect->MyMenu->getCurItem() );
        if ( 0 == _item ) return;
        int TopLevelForHero = MyArcadeItem->MyChallenge->CalcTopGameLevel( _item->Hero );
        //int TopLevelForHero = MyArcadeItem.MyChallenge.TopPlayerLevel();

		boost::shared_ptr<StartLevelMenu> levelmenu = MakeMagic( StartLevelMenu, ( TopLevelForHero ) );


		levelmenu->MyMenu->SelectItem( StartLevelMenu::PreviousMenuIndex );
		levelmenu->StartFunc = boost::make_shared<StartFuncProxy>( boost::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) );
		levelmenu->ReturnFunc.reset();

		Call( levelmenu );
		HeroSelect->Hide();
	}
}
