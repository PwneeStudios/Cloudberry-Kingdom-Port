#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	ArcadeItem::ArcadeItem( const std::shared_ptr<EzText> &Text, const std::shared_ptr<Challenge> &MyChallenge, const std::shared_ptr<Awardment> &MyPrereq ) : MenuItem( Text )
	{
		this->MyChallenge = MyChallenge;
		this->MyPrereq = MyPrereq;

		Locked = MyPrereq != 0 && !PlayerManager::Awarded( MyPrereq ) && !CloudberryKingdomGame::UnlockAll;
	}

	ArcadeBaseMenu::PlayGameProxy::PlayGameProxy( const std::shared_ptr<ArcadeBaseMenu> &abm )
	{
		this->abm = abm;
	}

	void ArcadeBaseMenu::PlayGameProxy::Apply()
	{
		abm->PlayGame();
	}

	ArcadeBaseMenu::StartFuncProxy::StartFuncProxy( const std::shared_ptr<ArcadeBaseMenu> &abm )
	{
		this->abm = abm;
	}

	void ArcadeBaseMenu::StartFuncProxy::Apply( const std::shared_ptr<LevelItem> &levelitem )
	{
		abm->StartFunc( levelitem );
	}

	void ArcadeBaseMenu::OnAdd()
	{
		CkBaseMenu::OnAdd();

		MyGame->ClearPreviousLoadFunction();
	}

	void ArcadeBaseMenu::StartFunc( const std::shared_ptr<LevelItem> &item )
	{
		SelectedItem = item;

		// Save the menu item index
		StartLevelMenu::PreviousMenuIndex = item->MenuIndex;

		// Start the game
		MyGame->PlayGame( std::make_shared<PlayGameProxy>( this ) );
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

	ArcadeMenu::GoProxy::GoProxy( const std::shared_ptr<ArcadeMenu> &am )
	{
		this->am = am;
	}

	void ArcadeMenu::GoProxy::Apply( const std::shared_ptr<MenuItem> &item )
	{
		am->Go( item );
	}

	void ArcadeMenu::SetItemProperties( const std::shared_ptr<MenuItem> &item )
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
		for ( std::vector<MenuItem*>::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			std::shared_ptr<Awardment> award = dynamic_cast<Awardment*>( ( *item )->MyObject );
			if ( 0 != award && !PlayerManager::Awarded( award ) && !CloudberryKingdomGame::UnlockAll )
			{
				( *item )->MyText->MyFloatColor = ( Color( 255, 100, 100 ) ).ToVector4();
				( *item )->MySelectedText->MyFloatColor = ( Color( 255, 160, 160 ) ).ToVector4();
			}
			else
			{
				if ( 0 != award )
					SetItemProperties( *item );
			}
		}
	}

	ArcadeMenu::ArcadeMenu()
	{
		InitializeInstanceFields();
	}

	void ArcadeMenu::Init()
	{
		 ArcadeBaseMenu::Init();

		SetParams();

		MyPile = std::make_shared<DrawPile>();

		// Menu
		if ( Long )
		{
			MyMenu = std::make_shared<LongMenu>();
			MyMenu->FixedToCamera = false;
			MyMenu->WrapSelect = false;
		}
		else
			MyMenu = std::make_shared<Menu>( false );

		MyMenu->setControl( -1 );

		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		// Header
		std::shared_ptr<MenuItem> Header = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_THE_ARCADE, Resources::Font_Grobold42_2 ) );
		Header->Name = _T( "Header" );
		MyMenu->Add( Header );
		SetItemProperties( Header );
		Header->Pos = Vector2( -1834.998f, 999.1272f );
		Header->MyText->setScale( Header->MyText->getScale() * 1.15f );
		Header->Selectable = false;

		std::shared_ptr<MenuItem> item;
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
		std::shared_ptr<QuadClass> backdrop;

		backdrop = std::make_shared<QuadClass>( _T( "Backplate_1500x900" ), 1500 );
		if ( Long )
			backdrop->setSizeY( backdrop->getSizeY() * 1.02f );
		MyPile->Add( backdrop, _T( "Backdrop" ) );
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

	Microsoft::Xna::Framework::Vector2 ArcadeMenu::GetGoalPos()
	{
		return Vector2( -174.6031f, -603.1746f );
	}

	std::shared_ptr<MenuItem> ArcadeMenu::AddChallenge( const std::shared_ptr<Challenge> &challenge, const std::shared_ptr<Awardment> &prereq, const std::shared_ptr<Awardment> &goal, const std::wstring &itemname )
	{
		std::shared_ptr<ArcadeItem> item;
		Localization::Words word = challenge->MenuName != 0 ? challenge->MenuName : challenge->Name;

		item = std::make_shared<ArcadeItem>( std::make_shared<EzText>( word, ItemFont ), challenge, prereq );

		item->Name = itemname;
		AddItem( item );

		item->setGo( std::make_shared<GoProxy>( this ) );

		return item;
	}

	void ArcadeMenu::Go( const std::shared_ptr<MenuItem> &item )
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
