#include <global_header.h>

namespace CloudberryKingdom
{

	HeroSelectOptions::BringLeaderboardProxy::BringLeaderboardProxy( const std::shared_ptr<HeroSelectOptions> &hso )
	{
		this->hso = hso;
	}

	void HeroSelectOptions::BringLeaderboardProxy::Apply()
	{
		hso->BringLeaderboard();
	}

	HeroSelectOptions::HeroSelectOptions( const std::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect ) : ArcadeBaseMenu() { }
	std::shared_ptr<HeroSelectOptions> HeroSelectOptions::HeroSelectOptions_Construct( const std::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect )
	{
		ArcadeBaseMenu::ArcadeBaseMenu_Construct();

		this->HeroSelect = HeroSelect;

		return std::static_pointer_cast<HeroSelectOptions>( shared_from_this() );
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

	void HeroSelectOptions::SlideOut( const PresetPos &Preset, int Frames )
	{
		ArcadeBaseMenu::SlideOut( Preset, 0 );
	}

	void HeroSelectOptions::SetItemProperties( const std::shared_ptr<MenuItem> &item )
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
		std::shared_ptr<HeroItem> item = std::dynamic_pointer_cast<HeroItem>( HeroSelect->MyMenu->getCurItem() );
		if ( 0 == item )
			return;

		std::shared_ptr<CloudberryKingdom::Challenge> challenge = HeroSelect->MyArcadeItem->MyChallenge;
		challenge->SetGameId();

		int GameId_Score = HeroSelect->MyArcadeItem->MyChallenge->GameId_Score;
		int GameId_Level = HeroSelect->MyArcadeItem->MyChallenge->GameId_Level;

		std::shared_ptr<CloudberryKingdom::ScoreList> MyHighScoreList = ScoreDatabase::GetList( GameId_Score );
		MyHighScoreList->MyFormat = ScoreEntry::Format_SCORE;

		std::shared_ptr<CloudberryKingdom::ScoreList> MyHighLevelList = ScoreDatabase::GetList( GameId_Level );
		MyHighLevelList->MyFormat = ScoreEntry::Format_LEVEL;

		std::shared_ptr<HighScorePanel> panel = std::make_shared<HighScorePanel>( true, MyHighScoreList, MyHighLevelList );
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

		MyPile = std::make_shared<DrawPile>();

		CallDelay = ReturnToCallerDelay = 0;

		// Menu
		MyMenu = std::make_shared<Menu>();
		MyMenu->OnB.reset();

		EnsureFancy();

		// Options. Menu for PC, graphics only for consoles.
	#if defined(PC_VERSION)
		std::shared_ptr<MenuItem> item;

		MyPile->Add( std::make_shared<QuadClass>( ButtonTexture::getX(), 80.f, static_cast<std::wstring>( _T("Button_X") ) ) );
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_LEADERBOARD, ItemFont, false, true ) );

		item->Name = _T( "Leaderboard" );
		item->setGo( Cast::ToItem( std::make_shared<BringLeaderboardProxy>( std::static_pointer_cast<HeroSelectOptions>( shared_from_this() ) ) ) );
		AddItem( item );
		StartMenu_MW_HeroSelect::SetItemProperties_FadedOnUnselect( item );

		MyMenu->MouseOnly = true;
		MyMenu->NoneSelected = true;
	#else
		std::wstring Space = _T( "{s34,0}" );
		std::shared_ptr<EzText> StartText = std::make_shared<EzText>( ButtonString::Go( 80 ) + Space + _T( "{c122,209,39,255} Start" ), ItemFont, true, true );
		MyPile->Add( StartText, _T( "Go" ) );

		std::shared_ptr<EzText> LeaderText = std::make_shared<EzText>( ButtonString::X( 80 ) + Space + _T( "{c150,189,244,255} Leaderboard" ), ItemFont, true, true );
		MyPile->Add( LeaderText, _T( "Leaderboard" ) );
	#endif

	#if defined(PC_VERSION)
		SetPos_PC();
	#else
		SetPos_Console();
	#endif
	}

	void HeroSelectOptions::SetPos_Console()
	{
		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Go" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 513.8887f, -472.2224f ) );
			_t->setScale( 0.7423338f );
		}
		_t = MyPile->FindEzText( _T( "Leaderboard" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 825, -655.5554f ) );
			_t->setScale( 0.7660002f );
		}

		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
	}

	void HeroSelectOptions::SetPos_PC()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Leaderboard" ) );
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

	void HeroSelectOptions::Go( const std::shared_ptr<MenuItem> &item )
	{
		std::shared_ptr<StartLevelMenu> levelmenu = std::make_shared<StartLevelMenu>( MyArcadeItem->MyChallenge->TopPlayerLevel() );

		levelmenu->MyMenu->SelectItem( StartLevelMenu::PreviousMenuIndex );
		levelmenu->StartFunc = std::make_shared<StartFuncProxy>( std::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) );
		levelmenu->ReturnFunc.reset();

		Call( levelmenu );
		HeroSelect->Hide();
	}
}
