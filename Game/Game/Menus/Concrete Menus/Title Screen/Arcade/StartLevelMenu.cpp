#include <global_header.h>

#include <Hacks\String.h>
#include <Hacks\List.h>
#include <Game\CloudberryKingdom\CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	LevelItem::LevelItem( const boost::shared_ptr<EzText> &Text, int StartLevel, int MenuIndex, bool Locked ) : MenuItem( Text )
	{
		this->StartLevel = StartLevel - 1;
		this->MenuIndex = MenuIndex;

		if ( Locked )
		{
			MyText->MyFloatColor = ( bColor( 255, 100, 100 ) ).ToVector4();
			MySelectedText->MyFloatColor = ( bColor( 255, 160, 160 ) ).ToVector4();
		}
	}

	StartLevelMenu::GameReturnProxy::GameReturnProxy( const boost::shared_ptr<StartLevelMenu> &slm )
	{
		this->slm = slm;
	}

	bool StartLevelMenu::GameReturnProxy::Apply()
	{
		return slm->GameReturn();
	}

	StartLevelMenu::LaunchHelper::LaunchHelper( const boost::shared_ptr<StartLevelMenu> &slm, const boost::shared_ptr<LevelItem> &litem )
	{
		this->slm = slm;
		this->litem = litem;
	}

	void StartLevelMenu::LaunchHelper::Apply()
	{
		// Executed once the game exits back to this menu
		slm->MyGame->AddToDo( boost::make_shared<GameReturnProxy>( slm ) );

		slm->StartFunc->Apply( litem );
	}

	StartLevelMenu::LaunchProxy::LaunchProxy( const boost::shared_ptr<StartLevelMenu> &slm )
	{
		this->slm = slm;
	}

	void StartLevelMenu::LaunchProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		slm->Launch( item );
	}

	int StartLevelMenu::PreviousMenuIndex = 0;

	void StartLevelMenu::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		StartMenu::SetText_Green( text, true );

		text->Shadow = false;
	}

	void StartLevelMenu::Launch( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<LevelItem> litem = boost::dynamic_pointer_cast<LevelItem>( item );
		if ( 0 == litem )
			return;

		MyGame->WaitThenDo( CallDelay, boost::make_shared<LaunchHelper>( boost::static_pointer_cast<StartLevelMenu>( shared_from_this() ), litem ), std::wstring( L"StartGame" ) );
	}

	bool StartLevelMenu::GameReturn()
	{
		if ( ReturnFunc != 0 )
			ReturnFunc->Apply();

		// Return to the parent menu
		MyMenu->OnB->Apply( 0 );

		return true;
	}

	void StartLevelMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		StartMenu::SetItemProperties_Green( item, true );

		item->ScaleText( 1.25f );

		item->MyText->Shadow = false;
		item->MySelectedText->Shadow = false;
	}

	std::vector<std::wstring> StartLevelMenu::GetNames()
	{
		std::vector<std::wstring> names = std::vector<std::wstring>( Levels.size() );

		for ( int i = 0; i < static_cast<int>( Levels.size() ); i++ )
			names[ i ] = Format( _T( "%02d" ), Levels[ i ] );
		//names[i] = string.Format("Level {0}", Levels[i]);

		return names;
	}

	StartLevelMenu::StartLevelMenu() :
		HighestLevel( 0 ),
		IndexCutoff( 0 )
	{
	}

	boost::shared_ptr<StartLevelMenu> StartLevelMenu::StartLevelMenu_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();

		return boost::static_pointer_cast<StartLevelMenu>( shared_from_this() );
	}

	StartLevelMenu::StartLevelMenu( int HighestLevel ) :
		HighestLevel( 0 ),
		IndexCutoff( 0 )
	{
	}
	boost::shared_ptr<StartLevelMenu> StartLevelMenu::StartLevelMenu_Construct( int HighestLevel )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		this->HighestLevel = HighestLevel;

		// Allow user to choose amongst any start level in the array Levels,
		// assuming they have previously gotten to that level.
		IndexCutoff = 1;
		for ( int i = 0; i < static_cast<int>( Levels.size() ); i++ )
			if ( HighestLevel >= Levels[ i ] || CloudberryKingdomGame::UnlockAll )
				IndexCutoff = i + 1;

		Initialize();

		return boost::static_pointer_cast<StartLevelMenu>( shared_from_this() );
	}

	void StartLevelMenu::Initialize()
	{
		ReturnToCallerDelay = 16;
		setSlideLength( 26 );

		ItemPos = Vector2( -1317, 700 );
		PosAdd = Vector2( 0, -151 ) * 1.45f;

		setSlideLength( 0 );
		CallDelay = ReturnToCallerDelay = 0;

		SlideInFrom = SlideOutTo = PresetPos_RIGHT;

		MyMenu = boost::make_shared<Menu>( false );

		MyMenu->setControl( -1 );

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );


		Vector2 shift = Vector2( -200, 40 );

		std::vector<std::wstring> Names = GetNames();

		for ( int i = 0; i < static_cast<int>( Names.size() ); i++ )
		{
			int StartLevel = Levels[ i ];
			int MenuIndex = i;
			bool Locked = i >= IndexCutoff;

			boost::shared_ptr<LevelItem> item = boost::make_shared<LevelItem>( boost::make_shared<EzText>( Names[ i ], Resources::Font_Grobold42 ), StartLevel, MenuIndex, Locked );
			if ( !Locked )
				item->setGo( boost::make_shared<LaunchProxy>( boost::static_pointer_cast<StartLevelMenu>( shared_from_this() ) ) );

			AddItem( item );
			item->SelectedPos.X -= 25;
		}
		ItemPos += PosAdd *.3f;

		//item = MakeBackButton();
		//item.MyText.Scale = item.MySelectedText.Scale *= 1.06f;

		this->EnsureFancy();

		MyPile = boost::make_shared<DrawPile>();

		// Backdrop
		boost::shared_ptr<QuadClass> Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Arcade_Box" ) );
		Backdrop->ScaleYToMatchRatio( 587 );
		MyPile->Add( Backdrop );

		// Back
		boost::shared_ptr<QuadClass> BackButton = boost::make_shared<QuadClass>( ButtonTexture::getBack() );
		MyPile->Add( BackButton, std::wstring( L"Back" ) );
		boost::shared_ptr<QuadClass> BackArrow = boost::make_shared<QuadClass>( std::wstring( L"BackArrow2" ), std::wstring( L"BackArrow" ) );
		MyPile->Add( BackArrow );
		BackArrow->FancyPos->SetCenter( BackButton->FancyPos );

		// Header
		boost::shared_ptr<EzText> Header = boost::make_shared<EzText>( Localization::Words_LEVEL, Resources::Font_Grobold42 );
		MyPile->Add( Header );
		SetHeaderProperties( Header );

		SetPos();
	}

	void StartLevelMenu::SetPos()
	{
		MyMenu->setPos( Vector2( 647.2223f, -447.2223f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -749.9998f, 761.1111f ) );
			_t->setScale( 1.30125f );
		}

		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -591.6664f, -63.88891f ) );
			_q->setSize( Vector2( 884.3204f, 964.1653f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"Back" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -1102.777f, -761.1107f ) );
			_q->setSize( Vector2( 56.24945f, 56.24945f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"BackArrow" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -136.1112f, -11.11111f ) );
			_q->setSize( Vector2( 74.61235f, 64.16662f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );
	}

	void StartLevelMenu::InitializeInstanceFields()
	{
		int tempVector[] = { 1, 50, 100, 150 };
		Levels = VecFromArray( tempVector );
		IndexCutoff = 0;
	}
}
