#include <global_header.h>

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

	void HeroSelectOptions::BringLeaderboard()
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

		// Menu
		MyMenu = boost::make_shared<Menu>();
		MyMenu->OnB.reset();

		EnsureFancy();

		// Options. Menu for PC, graphics only for consoles.
	#if defined(PC_VERSION)
		boost::shared_ptr<MenuItem> item;

		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 80.f, static_cast<std::wstring>( std::wstring( L"Button_X" ) ) ) );
		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_LEADERBOARD, ItemFont, false, true ) ) );

		item->Name = std::wstring( L"Leaderboard" );
		item->setGo( Cast::ToItem( boost::make_shared<BringLeaderboardProxy>( boost::static_pointer_cast<HeroSelectOptions>( shared_from_this() ) ) ) );
		AddItem( item );
		StartMenu_MW_HeroSelect::SetItemProperties_FadedOnUnselect( item );

		MyMenu->MouseOnly = true;
		MyMenu->NoneSelected = true;
	#else
		std::wstring Space = std::wstring( L"{s34,0}" );
		boost::shared_ptr<EzText> StartText = boost::make_shared<EzText>( ButtonString::Go( 80 ) + Space + std::wstring( L"{c122,209,39,255} Start" ), ItemFont, true, true );
		MyPile->Add( StartText, std::wstring( L"Go" ) );

		boost::shared_ptr<EzText> LeaderText = boost::make_shared<EzText>( ButtonString::X( 80 ) + Space + std::wstring( L"{c150,189,244,255} Leaderboard" ), ItemFont, true, true );
		MyPile->Add( LeaderText, std::wstring( L"Leaderboard" ) );
	#endif

	#if defined(PC_VERSION)
		SetPos_PC();
	#else
		SetPos_Console();
	#endif
	}

	void HeroSelectOptions::SetPos_Console()
	{
		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"Go" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 513.8887f, -472.2224f ) );
			_t->setScale( 0.7423338f );
		}
		_t = MyPile->FindEzText( std::wstring( L"Leaderboard" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 825, -655.5554f ) );
			_t->setScale( 0.7660002f );
		}

		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
	}

	void HeroSelectOptions::SetPos_PC()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Leaderboard" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -808, 110 ) );
			_item->MyText->setScale( 0.75f );
			_item->MySelectedText->setScale( 0.75f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( 947.2223f, -608.3333f ) );

		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
	}

	void HeroSelectOptions::Go( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<StartLevelMenu> levelmenu = MakeMagic( StartLevelMenu, ( MyArcadeItem->MyChallenge->TopPlayerLevel() ) );

		levelmenu->MyMenu->SelectItem( StartLevelMenu::PreviousMenuIndex );
		levelmenu->StartFunc = boost::make_shared<StartFuncProxy>( boost::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) );
		levelmenu->ReturnFunc.reset();

		Call( levelmenu );
		HeroSelect->Hide();
	}
}
