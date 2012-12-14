#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	HighScorePanel::HighScoreReturnToCallerLambda::HighScoreReturnToCallerLambda( const std::shared_ptr<HighScorePanel> &hsp )
	{
		this->hsp = hsp;
	}

	void HighScorePanel::HighScoreReturnToCallerLambda::Apply()
	{
		hsp->ReturnToCaller();
	}

	HighScorePanel::HighScorePanelEndGameHelper::HighScorePanelEndGameHelper( const std::shared_ptr<HighScorePanel> &hsp, bool param )
	{
		this->hsp = hsp;
		this->param = param;
	}

	void HighScorePanel::HighScorePanelEndGameHelper::Apply()
	{
		hsp->MyGame->EndGame->Apply( param );
	}

	HighScorePanel::Action_DoneProxy1::Action_DoneProxy1( const std::shared_ptr<HighScorePanel> &hsp )
	{
		this->hsp = hsp;
	}

	void HighScorePanel::Action_DoneProxy1::Apply( const std::shared_ptr<MenuItem> &dummy )
	{
		hsp->Action_Done();
	}

	HighScorePanel::Action_PlayAgainProxy1::Action_PlayAgainProxy1( const std::shared_ptr<HighScorePanel> &hsp )
	{
		this->hsp = hsp;
	}

	void HighScorePanel::Action_PlayAgainProxy1::Apply( const std::shared_ptr<MenuItem> &dummy )
	{
		hsp->Action_PlayAgain();
	}

	void HighScorePanel::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		if ( Panels.size() > 0 )
			for ( int i = 0; i < static_cast<int>( Panels.size() ); i++ )
				Panels[ i ]->Release();
		Panels.clear();
	}

	HighScorePanel::HighScorePanel( const std::shared_ptr<ScoreList> &Scores ) :
		Instant( false )
	{
	}
	std::shared_ptr<HighScorePanel> HighScorePanel::HighScorePanel_Construct( const std::shared_ptr<ScoreList> &Scores )
	{
		InitializeInstanceFields();
		CkBaseMenu::CkBaseMenu_Construct();
		
		Constructor( Scores );

		return std::static_pointer_cast<HighScorePanel>( shared_from_this() );
	}

	void HighScorePanel::Constructor( const std::shared_ptr<ScoreList> &Scores )
	{
		if ( Instant )
			NoDelays();
		else
			Fast();


		MyScoreList = Scores;
		Create();
		SlideIn();
	}

	std::wstring tempVector[] = { _T( "score_screen_grey" ), _T( "score_screen_grey" ), _T( "score_screen_grey" ) };
	std::vector<std::wstring> HighScorePanel::TextureName = VecFromArray( tempVector );

	HighScorePanel::HighScorePanel( std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist ) :
		Instant( false )
	{
	}
	std::shared_ptr<HighScorePanel> HighScorePanel::HighScorePanel_Construct( std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist )
	{
		InitializeInstanceFields();
		CkBaseMenu::CkBaseMenu_Construct();

		MultiInit( false, scorelist, levellist );

		return std::static_pointer_cast<HighScorePanel>( shared_from_this() );
	}

	HighScorePanel::HighScorePanel( bool Instant, std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist ) :
		Instant( false )
	{
	}
	std::shared_ptr<HighScorePanel> HighScorePanel::HighScorePanel_Construct( bool Instant, std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist )
	{
		InitializeInstanceFields();
		CkBaseMenu::CkBaseMenu_Construct();

		MultiInit( Instant, scorelist, levellist );

		return std::static_pointer_cast<HighScorePanel>( shared_from_this() );
	}

	void HighScorePanel::MultiInit( bool Instant, std::shared_ptr<ScoreList> scorelist, std::shared_ptr<ScoreList> levellist )
	{
		this->Instant = Instant;

		OnOutsideClick = std::make_shared<HighScoreReturnToCallerLambda>( std::static_pointer_cast<HighScorePanel>( shared_from_this() ) );
		CheckForOutsideClick = true;

		Constructor( scorelist );

		Panels = std::vector<std::shared_ptr<HighScorePanel> >( 2 );

		Panels[ 0 ] = std::static_pointer_cast<HighScorePanel>( shared_from_this() );
		Panels[ 0 ]->Backdrop->setTextureName( _T( "score_screen_grey" ) );

		Panels[ 1 ] = MakeMagic( HighScorePanel, ( levellist ) );
		Panels[ 1 ]->Backdrop->setTextureName( _T( "score_screen_grey" ) );

		for ( int i = 0; i < 2; i++ )
			Panels[ i ]->MakeSwapText();
	}

	void HighScorePanel::SwapPanels()
	{
		for ( int i = 0; i < static_cast<int>( Panels.size() ) - 1; i++ )
			Tools::Swap( Panels[ i ]->MyPile, Panels[ i + 1 ]->MyPile );

		MyPile->Jiggle( true, 8,.3f );
	}

	void HighScorePanel::Init()
	{
		CkBaseMenu::Init();

		getCore()->DrawLayer = Level::AfterPostDrawLayer;
	}

	void HighScorePanel::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	Vector4 HighScorePanel::ScoreColor = ( bColor( 255, 255, 255 ) ).ToVector4();
	Vector4 HighScorePanel::CurrentScoreColor = ( bColor( 22, 22, 222 ) ).ToVector4();

	void HighScorePanel::Create()
	{
		MyPile = std::make_shared<DrawPile>();

		// Make the backdrop
		Backdrop = std::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 500.f, true );
		Backdrop->setDegrees( 90 );
		Backdrop->setTextureName( _T( "Score/Score_Screen_grey" ) );

		MyPile->Add( Backdrop, _T( "Backdrop" ) );
		Backdrop->setPos( Vector2( 22.2233f, 10.55567f ) );

		// 'High Score' text
		std::shared_ptr<EzText> Text = std::make_shared<EzText>( MyScoreList->GetHeader(), Resources::Font_Grobold42_2, 1450.f, false, true, .6f );
		Text->setScale( .8f );
		Text->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		Text->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();
		Text->setPos( Vector2( -675.6388f, 585 ) );
		MyPile->Add( Text, _T( "Header" ) );
		Text->Shadow = false;
		Text->ShadowColor = Color( .36f,.36f,.36f,.86f );
		Text->ShadowOffset = Vector2( -24, -20 );

		// Scores
		int DesiredLength = 35;
		float y_spacing = 120;
		Vector2 pos = Vector2( -973, 322 );
		for ( std::vector<std::shared_ptr<ScoreEntry> >::const_iterator score = MyScoreList->Scores.begin(); score != MyScoreList->Scores.end(); ++score )
		{
			Text = std::make_shared<EzText>( MyScoreList->ScoreString( *score, DesiredLength ), Resources::Font_Grobold42 );
			SetHeaderProperties( Text );
			Text->setScale( Text->getScale() * .55f );

			if ( ( *score )->Date == ScoreDatabase::MostRecentScoreDate )
				Text->MyFloatColor = Color::LimeGreen.ToVector4();
			else
				Text->MyFloatColor = ScoreColor;
			Text->setPos( pos );
			pos.Y -= y_spacing;

			MyPile->Add( Text );
		}

		SetPos();
	}

	void HighScorePanel::SetPos()
	{
		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -675.6388f, 585 ) );
			_t->setScale( 0.8f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -102.7767f, -253.3332f ) );
			_q->setSize( Vector2( 1930.665f, 1206.665f ) );
		}

		MyPile->setPos( Vector2( 161.1108f, 227.7778f ) );

	}

	void HighScorePanel::MakeSwapText()
	{
	#if defined(PC_VERSION)
		//SwapText = new EzText(ButtonString.Enter(200), Resources.Font_Grobold42_2, 1450, false, true, .6f);
		//SwapText.Pos = new Vector2(-1169.281f, 602.9366f);
	#else
		SwapText = std::make_shared<EzText>( ButtonString::Go( 130 ), Resources::Font_Grobold42_2, 1450, false, true,.6f );
		SwapText->setPos( Vector2( -1014.837f, 597.3811f ) );
	#endif

		if ( SwapText != 0 )
		{
			SwapText->setScale( .8f );
			SwapText->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
			SwapText->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();

			MyPile->Add( SwapText );
			SwapText->ShadowColor = Color( .36f,.36f,.36f,.86f );
			SwapText->ShadowOffset = Vector2( -24, -20 );
		}
	}

	void HighScorePanel::SetHeaderProperties( const std::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->MyFloatColor = ( bColor( 255, 254, 252 ) ).ToVector4();

		text->OutlineColor = ( bColor( 0, 0, 0 ) ).ToVector4();
		text->setScale( text->getScale() * 1.48f );

		text->Shadow = false;
	}

	void HighScorePanel::MakeMenu()
	{
		MyMenu = std::make_shared<Menu>( false );

		MyMenu->setControl( -1 );

		MyMenu->OnB.reset();


		std::shared_ptr<MenuItem> item;
		FontScale *= .89f * 1.16f;

		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_PLAY_AGAIN, ItemFont ) );
		item->setGo( std::make_shared<Action_PlayAgainProxy1>( std::static_pointer_cast<HighScorePanel>( shared_from_this() ) ) );
		AddItem( item );

		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_HIGH_SCORES, ItemFont ) );
		item->_Go.reset();
		AddItem( item );

		item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_DONE, ItemFont ) );
		item->setGo( std::make_shared<Action_DoneProxy1>( std::static_pointer_cast<HighScorePanel>( shared_from_this() ) ) );
		AddItem( item );
	}

	void HighScorePanel::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MyText->MyFloatColor = ( bColor( 255, 255, 255 ) ).ToVector4();
		item->MySelectedText->MyFloatColor = ( bColor( 50, 220, 50 ) ).ToVector4();
	}

	void HighScorePanel::Action_Done()
	{
		SlideOut( PresetPos_TOP, 13 );
		Active = false;

		MyGame->WaitThenDo( 36, std::make_shared<HighScorePanelEndGameHelper>( std::static_pointer_cast<HighScorePanel>( shared_from_this() ), false ) );
		return;
	}

	void HighScorePanel::Action_PlayAgain()
	{
		SlideOut( PresetPos_TOP, 13 );
		Active = false;

		MyGame->WaitThenDo( 36, std::make_shared<HighScorePanelEndGameHelper>( std::static_pointer_cast<HighScorePanel>( shared_from_this() ), true ) );
		return;
	}

	void HighScorePanel::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

		if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed || ButtonCheck::State( ControllerButtons_X, -1 ).Pressed )
			SwapPanels();

		if ( ButtonCheck::State( ControllerButtons_B, -1 ).Pressed ) //ButtonCheck.State(ControllerButtons.A, -1).Pressed ||
			ReturnToCaller();
	}

	bool HighScorePanel::HitTest( Vector2 pos )
	{
		return Backdrop->HitTest( pos, Vector2( -50 ) );
	}

	void HighScorePanel::InitializeInstanceFields()
	{
		Instant = true;
	}
}
