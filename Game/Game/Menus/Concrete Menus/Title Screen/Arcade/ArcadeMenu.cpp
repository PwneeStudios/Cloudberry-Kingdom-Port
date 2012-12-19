#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	ArcadeItem::ArcadeItem( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq ) : MenuItem( Text )
	{
		this->MyChallenge = MyChallenge;
		this->MyPrereq = MyPrereq;

		Locked = MyPrereq != 0 && !PlayerManager::Awarded( MyPrereq ) && !CloudberryKingdomGame::UnlockAll;
	}

	ArcadeBaseMenu::PlayGameProxy::PlayGameProxy( const boost::shared_ptr<ArcadeBaseMenu> &abm )
	{
		this->abm = abm;
	}

	void ArcadeBaseMenu::PlayGameProxy::Apply()
	{
		abm->PlayGame();
	}

	ArcadeBaseMenu::StartFuncProxy::StartFuncProxy( const boost::shared_ptr<ArcadeBaseMenu> &abm )
	{
		this->abm = abm;
	}

	void ArcadeBaseMenu::StartFuncProxy::Apply( const boost::shared_ptr<LevelItem> &levelitem )
	{
		abm->StartFunc( levelitem );
	}

	boost::shared_ptr<ArcadeBaseMenu> ArcadeBaseMenu::ArcadeBaseMenu_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		return boost::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() );
	}

	void ArcadeBaseMenu::OnAdd()
	{
		CkBaseMenu::OnAdd();

		MyGame->ClearPreviousLoadFunction();
	}

	void ArcadeBaseMenu::StartFunc( const boost::shared_ptr<LevelItem> &item )
	{
		SelectedItem = item;

		// Save the menu item index
		StartLevelMenu::PreviousMenuIndex = item->MenuIndex;

		// Start the game
		MyGame->PlayGame( boost::make_shared<PlayGameProxy>( boost::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) ) );
	}

	void ArcadeBaseMenu::PlayGame()
	{
		// Show title again if we're selecting from the menu
		if ( !MyGame->ExecutingPreviousLoadFunction )
			//Escalation_Tutorial.ShowTitle = true;
			HeroRush_Tutorial::ShowTitle = true;

		MyArcadeItem->MyChallenge->Start( SelectedItem->StartLevel );
	}

	void ArcadeBaseMenu::Release()
	{
		CkBaseMenu::Release();

		MyArcadeItem.reset();
		SelectedItem.reset();
	}

	ArcadeMenu::GoProxy::GoProxy( const boost::shared_ptr<ArcadeMenu> &am )
	{
		this->am = am;
	}

	void ArcadeMenu::GoProxy::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		am->Go( item );
	}

	void ArcadeMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		ArcadeBaseMenu::SetItemProperties( item );

		item->ScaleText( .945f );
	}

	void ArcadeMenu::OnReturnTo()
	{
		ArcadeBaseMenu::OnReturnTo();
		SetLockColors();
	}

	void ArcadeMenu::SetLockColors()
	{
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<Awardment> award = boost::dynamic_pointer_cast<Awardment>( ( *item )->MyObject );
			if ( 0 != award && !PlayerManager::Awarded( award ) && !CloudberryKingdomGame::UnlockAll )
			{
				( *item )->MyText->MyFloatColor = ( bColor( 255, 100, 100 ) ).ToVector4();
				( *item )->MySelectedText->MyFloatColor = ( bColor( 255, 160, 160 ) ).ToVector4();
			}
			else
			{
				if ( 0 != award )
					SetItemProperties( *item );
			}
		}
	}

	ArcadeMenu::ArcadeMenu() :
		Long( false )
	{
	}
	boost::shared_ptr<ArcadeMenu> ArcadeMenu::ArcadeMenu_Construct()
	{
		InitializeInstanceFields();

		ArcadeBaseMenu::ArcadeBaseMenu_Construct();

		return boost::static_pointer_cast<ArcadeMenu>( shared_from_this() );
	}

	void ArcadeMenu::Init()
	{
		 ArcadeBaseMenu::Init();

		SetParams();

		MyPile = boost::make_shared<DrawPile>();

		// Menu
		if ( Long )
		{
			MyMenu = boost::make_shared<LongMenu>();
			MyMenu->FixedToCamera = false;
			MyMenu->WrapSelect = false;
		}
		else
			MyMenu = boost::make_shared<Menu>( false );

		MyMenu->setControl( -1 );

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Header
		boost::shared_ptr<MenuItem> Header = boost::make_shared<MenuItem>( boost::make_shared<EzText>( Localization::Words_THE_ARCADE, Resources::Font_Grobold42_2 ) );
		Header->Name = std::wstring( L"Header" );
		MyMenu->Add( Header );
		SetItemProperties( Header );
		Header->Pos = Vector2( -1834.998f, 999.1272f );
		Header->MyText->setScale( Header->MyText->getScale() * 1.15f );
		Header->Selectable = false;

		boost::shared_ptr<MenuItem> item;
		ItemPos = Vector2( -1689.523f, 520.4127f );

		// Escalation
		item = AddChallenge( Challenge_Escalation::getInstance(), 0, 0, _T("Escalation") );

		// Time Crisis
		item = AddChallenge( Challenge_TimeCrisis::getInstance(), 0, Awardments::UnlockHeroRush2, _T("Time Crisis") );

		// Hero Rush
		item = AddChallenge( Challenge_HeroRush::getInstance(), 0, Awardments::UnlockHeroRush2, _T("Hero Rush") );

		// Hero Rush 2
		item = AddChallenge( Challenge_HeroRush2::getInstance(), Awardments::UnlockHeroRush2, 0, _T("Hero Rush 2") );

		// Bungee Co-op
		//item = AddChallenge(Challenge_HeroRush2.Instance, Awardments.UnlockHeroRush2, null, "Bungee");

		// Backdrop
		boost::shared_ptr<QuadClass> backdrop;

		backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1500x900" ), 1500.f );
		if ( Long )
			backdrop->setSizeY( backdrop->getSizeY() * 1.02f );
		MyPile->Add( backdrop, std::wstring( L"Backdrop" ) );
		backdrop->setPos( Vector2( 9.921265f, -111.1109f ) + Vector2( -297.6191f, 15.87299f ) );

		// Position
		EnsureFancy();
		MyMenu->setPos( Vector2( 332, -40 ) );
		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );

		MyMenu->SelectItem( 1 );

		SetLockColors();
	}

	void ArcadeMenu::SetParams()
	{
		CallDelay = 20;

		setSlideLength( 27 );

		ReturnToCallerDelay = 20;
		SlideInFrom = PresetPos_LEFT;
		SlideOutTo = PresetPos_LEFT;
	}

	Vector2 ArcadeMenu::GetGoalPos()
	{
		return Vector2( -174.6031f, -603.1746f );
	}

	boost::shared_ptr<MenuItem> ArcadeMenu::AddChallenge( const boost::shared_ptr<Challenge> &challenge, const boost::shared_ptr<Awardment> &prereq, const boost::shared_ptr<Awardment> &goal, const std::wstring &itemname )
	{
		boost::shared_ptr<ArcadeItem> item;
		Localization::Words word = challenge->MenuName != 0 ? challenge->MenuName : challenge->Name;

		item = boost::make_shared<ArcadeItem>( boost::make_shared<EzText>( word, ItemFont ), challenge, prereq );

		item->Name = itemname;
		AddItem( item );

		item->setGo( boost::make_shared<GoProxy>( boost::static_pointer_cast<ArcadeMenu>( shared_from_this() ) ) );

		return item;
	}

	void ArcadeMenu::Go( const boost::shared_ptr<MenuItem> &item )
	{
	}

	void ArcadeMenu::MyPhsxStep()
	{
		ArcadeBaseMenu::MyPhsxStep();
	}

	void ArcadeMenu::InitializeInstanceFields()
	{
		Long = false;
	}
}
