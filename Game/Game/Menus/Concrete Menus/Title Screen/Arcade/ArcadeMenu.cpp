#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	bool ArcadeItem::IsLocked()
    {
        return MyPrereq != 0 && !PlayerManager::Awarded( MyPrereq ) && !CloudberryKingdomGame::Unlock_Levels;
    }

	ArcadeItem::ArcadeItem( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq ) : MenuItem( Text )
	{
	}
	boost::shared_ptr<ArcadeItem> ArcadeItem::ArcadeItem_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<Challenge> &MyChallenge, const boost::shared_ptr<Awardment> &MyPrereq )
	{
		MenuItem::MenuItem_Construct( Text );

		this->MyChallenge = MyChallenge;
		this->MyPrereq = MyPrereq;

		return boost::static_pointer_cast<ArcadeItem>( shared_from_this() );
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

	ArcadeMenu::OnSelectProxy::OnSelectProxy( const boost::shared_ptr<ArcadeMenu> &am )
	{
		this->am = am;
	}

	void ArcadeMenu::OnSelectProxy::Apply()
	{
		am->OnSelect();
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

		UpdateAfterPlaying();
	}

	void ArcadeMenu::SetLockColors()
	{
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyMenu->Items.begin(); item != MyMenu->Items.end(); ++item )
		{
			boost::shared_ptr<Awardment> award = boost::dynamic_pointer_cast<Awardment>( ( *item )->MyObject );
			if ( 0 != award && !PlayerManager::Awarded( award ) && !CloudberryKingdomGame::Unlock_Levels )
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

    boost::shared_ptr<BobPhsx> ArcadeMenu::JetpackWheelie;
    boost::shared_ptr<BobPhsx> ArcadeMenu::BigBouncy;
    boost::shared_ptr<BobPhsx> ArcadeMenu::Ultimate;

	void ArcadeMenu::StaticInit()
	{
        // Heroes
        BobPhsxNormal::getInstance()->Id = 0;
        BobPhsxBig::getInstance()->Id = 1;
        BobPhsxInvert::getInstance()->Id = 2;
        BobPhsxDouble::getInstance()->Id = 3;
        BobPhsxJetman::getInstance()->Id = 4;
        BobPhsxBouncy::getInstance()->Id = 5;
        BobPhsxBox::getInstance()->Id = 6;
        BobPhsxScale::getInstance()->Id = 7;
        BobPhsxTime::getInstance()->Id = 8;
        BobPhsxSmall::getInstance()->Id = 9;
        BobPhsxSpaceship::getInstance()->Id = 10;
        BobPhsxWheel::getInstance()->Id = 11;

        ArcadeMenu::JetpackWheelie = BobPhsx::MakeCustom(Hero_BaseType_WHEEL, Hero_Shape_CLASSIC, Hero_MoveMod_JETPACK);
        ArcadeMenu::JetpackWheelie->Name = Localization::Words_JetpackWheelie;
        ArcadeMenu::JetpackWheelie->Id = 12;

        ArcadeMenu::BigBouncy = BobPhsx::MakeCustom(Hero_BaseType_BOUNCY, Hero_Shape_BIG, Hero_MoveMod_JETPACK);
        ArcadeMenu::BigBouncy->Name = Localization::Words_Hero;
        ArcadeMenu::BigBouncy->Id = 13;

        ArcadeMenu::Ultimate = BobPhsx::MakeCustom(Hero_BaseType_CLASSIC, Hero_Shape_CLASSIC, Hero_MoveMod_CLASSIC);
        ArcadeMenu::Ultimate->Name = Localization::Words_Masochistic;
        BobPhsx::CustomPhsxData UltimatePhsx = BobPhsx::CustomPhsxData();
        UltimatePhsx.Init();
        UltimatePhsx[BobPhsx::CustomData_ACCEL] = 2.2f;
        UltimatePhsx[BobPhsx::CustomData_FRICTION] = 2.2f;
        UltimatePhsx[BobPhsx::CustomData_MAXSPEED] = 2.35f;
        UltimatePhsx[BobPhsx::CustomData_GRAVITY] = .575f;
        UltimatePhsx[BobPhsx::CustomData_JUMPLENGTH] = 1.51f;
        UltimatePhsx[BobPhsx::CustomData_JUMPLENGTH2] = 1.5212f;
        UltimatePhsx[BobPhsx::CustomData_JUMPACCEL] = .8f;
        UltimatePhsx[BobPhsx::CustomData_JUMPACCEL2] = .8f;
        UltimatePhsx[BobPhsx::CustomData_MAXFALL] = 2.2f;
        UltimatePhsx[BobPhsx::CustomData_NUMJUMPS] = 1;
        UltimatePhsx[BobPhsx::CustomData_SIZE] = .2f;
        ArcadeMenu::Ultimate->SetCustomPhsx( UltimatePhsx );
        ArcadeMenu::Ultimate->Id = 14;

        HeroArcadeList = std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > >();

			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxNormal::getInstance(),		 std::pair<boost::shared_ptr<BobPhsx>, int>( boost::shared_ptr<BobPhsx>(), 0 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxBig::getInstance(),         std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxNormal::getInstance() ), 25 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxRocketbox::getInstance(),   std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxBig::getInstance() ), 35 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxInvert::getInstance(),      std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxRocketbox::getInstance() ), 35 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxJetman::getInstance(),      std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxInvert::getInstance() ), 45 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxBouncy::getInstance(),      std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxJetman::getInstance() ), 50 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxSpaceship::getInstance(),   std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxBouncy::getInstance() ), 60 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxDouble::getInstance(),      std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxSpaceship::getInstance() ), 70 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxWheel::getInstance(),       std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxDouble::getInstance() ), 70 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BobPhsxSmall::getInstance(),       std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxWheel::getInstance() ), 80 ) ) );
                																																		     
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( JetpackWheelie ,                   std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BobPhsxSmall::getInstance() ), 100 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( BigBouncy ,                        std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( JetpackWheelie ), 100 ) ) );
			HeroArcadeList.push_back( std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >( Ultimate ,                         std::pair<boost::shared_ptr<BobPhsx>, int>( boost::static_pointer_cast<BobPhsx>( BigBouncy ), 100 ) ) );

            // Compile a list of all leaderboards
            LeaderboardList = std::vector<std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> > >();
            LeaderboardList.push_back(std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> >(0, 0));
            
		
			for ( std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > >::const_iterator
				hero = HeroArcadeList.begin(); hero != HeroArcadeList.end(); ++hero )
			{
                LeaderboardList.push_back(
					std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> >(
					Challenge_Escalation::getInstance(), hero->first) );
			}

			for ( std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > >::const_iterator
				hero = HeroArcadeList.begin(); hero != HeroArcadeList.end(); ++hero )
			{
                LeaderboardList.push_back(
					std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> >(
					Challenge_TimeCrisis::getInstance(), hero->first) );
			}

            LeaderboardList.push_back( std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> >( Challenge_HeroRush::getInstance(), 0 ) );
            LeaderboardList.push_back( std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> >( Challenge_HeroRush2::getInstance(), 0 ) );

            // Goals
            ChallengeGoal = std::map<int, int>();
			for ( std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > >::const_iterator
				hero = HeroArcadeList.begin(); hero != HeroArcadeList.end(); ++hero )
            {
                if ( hero->second.first == 0 ) continue;
                ChallengeGoal[ Challenge_Escalation::getInstance()->CalcGameId_Level( hero->second.first ) ] = hero->second.second;
                ChallengeGoal[ Challenge_TimeCrisis::getInstance()->CalcGameId_Level( hero->second.first ) ] = hero->second.second;
            }
	}

	std::map<int, int> ArcadeMenu::ChallengeGoal;
	std::vector<std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> > > ArcadeMenu::LeaderboardList;
	std::vector<std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > > ArcadeMenu::HeroArcadeList;


        int ArcadeMenu::LeaderboardIndex(boost::shared_ptr<Challenge> challenge, boost::shared_ptr<BobPhsx> phsx)
        {
            int index = 0;

			for ( std::vector<std::pair<boost::shared_ptr<Challenge>, boost::shared_ptr<BobPhsx> > >::const_iterator
				tuple = LeaderboardList.begin(); tuple != LeaderboardList.end(); ++tuple )
			{
                if ( tuple->first == challenge && tuple->second == phsx )
                {
                    return index;
                }

                index++;
            }

            return 0;
        }

        void ArcadeMenu::CheckForArcadeUnlocks_OnSwapIn(int level)
        {
            // Always add new hero message (for testing)
            //Tools::CurGameData.AddGameObject(new HeroUnlockedMessage());

            bool DoSave = false;

            Tools::Assert(Challenge::CurrentId >= 0);

            std::vector<boost::shared_ptr<PlayerData> > CopyOfExistingPlayers = PlayerManager::getExistingPlayers();
			for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator
				player = CopyOfExistingPlayers.begin(); player != CopyOfExistingPlayers.end(); ++player )
            {
                // Check for goals
                //if (ChallengeGoal.ContainsKey(Challenge::CurrentId))
                {
                    int CurHighLevel = ( *player )->GetHighScore(Challenge::CurrentId);
                    //if (level + 1 >= Goal && CurHighLevel < Goal)
					if (level >= CurHighLevel)
                    {
						//DoSave = true;
                        ( *player )->AddHighScore( boost::make_shared<ScoreEntry>( ( *player )->GetName(), Challenge::CurrentId,                       level + 1,              Challenge::CurrentScore, level + 1, 0, 0, 0));
                        ( *player )->AddHighScore( boost::make_shared<ScoreEntry>( ( *player )->GetName(), Challenge::CurrentId - Challenge::LevelMask, Challenge::CurrentScore, Challenge::CurrentScore, level + 1, 0, 0, 0));
                    }

					if ( Contains( ChallengeGoal, Challenge::CurrentId ) )
					{
						int Goal = ChallengeGoal[Challenge::CurrentId];

						if (level + 1 >= Goal && CurHighLevel < Goal)
						{
							DoSave = true;
						}
					}
                }

                // Check for awards
                int TotalArcadeLevel = ( *player )->GetTotalArcadeLevel();
                Awardments::CheckForAward_TimeCrisisUnlock(TotalArcadeLevel, ( *player ) );
                Awardments::CheckForAward_HeroRushUnlock(TotalArcadeLevel, ( *player ) );
                Awardments::CheckForAward_HeroRush2Unlock(TotalArcadeLevel, ( *player ) );
            }

            if (DoSave)
            {
                SaveGroup::SaveAll();
                Tools::CurGameData->AddGameObject( boost::make_shared<HeroUnlockedMessage>() );
            }
        }

    void ArcadeMenu::CheckForArcadeUnlocks(boost::shared_ptr<ScoreEntry> score)
    {
        Awardments::CheckForAward_ArcadeScore( score->Value );
        Awardments::CheckForAward_ArcadeScore2( score->Value );
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

            // Level
            boost::shared_ptr<EzText> LevelText = boost::make_shared<EzText>(Localization::Words_PlayerLevel, Resources::Font_Grobold42);
            LevelText->_Scale *= .72f;
            StartMenu::SetText_Green(LevelText, true);
            MyPile->Add( LevelText, L"Level");
            LevelText->Show = false;

            boost::shared_ptr<EzText> LevelNum = boost::make_shared<EzText>( L"Garbage", Resources::Font_Grobold42);
            LevelNum->_Scale *= 1.1f;
            StartMenu::SetText_Green(LevelNum, true);
            MyPile->Add( LevelNum, L"LevelNum");
            LevelNum->Show = false;

            // Requirement
            RequiredText = boost::make_shared<EzText>(Localization::Words_Required, Resources::Font_Grobold42);
            RequiredText->_Scale *= 1.f;
            StartMenu::SetText_Green(RequiredText, true);
            MyPile->Add( RequiredText, L"Requirement");
            RequiredText->Alpha = 0;

            RequiredText2 = boost::make_shared<EzText>( L"Garbage", Resources::Font_Grobold42);
            RequiredText2->_Scale *= 1.f;
            StartMenu::SetText_Green(RequiredText2, true);
            MyPile->Add( RequiredText2, L"Requirement2");
            RequiredText2->Alpha = 0;

            TextBack = boost::make_shared<QuadClass>( L"Arcade_BoxLeft", 100.f, true);
            TextBack->setAlpha( 1.f );
            TextBack->setDegrees( 90 );
            MyPile->Add( TextBack, L"BoxLeft");


		// Header
		boost::shared_ptr<MenuItem> Header = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_TheArcade, Resources::Font_Grobold42_2 ) ) );
		Header->Name = std::wstring( L"Header" );
		MyMenu->Add( Header );
		SetItemProperties( Header );
		Header->Pos = Vector2( -1834.998f, 999.1272f );
		Header->MyText->setScale( Header->MyText->getScale() * 1.15f );
		Header->Selectable = false;

		boost::shared_ptr<MenuItem> item;
		ItemPos = Vector2( -1689.523f, 520.4127f );

		// Escalation
		item = AddChallenge( Challenge_Escalation::getInstance(), 0, std::wstring( L"Escalation" ) );

		// Time Crisis
		item = AddChallenge( Challenge_TimeCrisis::getInstance(), Awardments::UnlockTimeCrisis, std::wstring( L"Time Crisis" ) );

		// Hero Rush
		item = AddChallenge( Challenge_HeroRush::getInstance(), Awardments::UnlockHeroRush, std::wstring( L"Hero Rush" ) );

		// Hero Rush 2
		item = AddChallenge( Challenge_HeroRush2::getInstance(), Awardments::UnlockHeroRush2, std::wstring( L"Hero Rush 2" ) );

		// Bungee Co-op
		//item = AddChallenge(Challenge_HeroRush2.Instance, Awardments::UnlockHeroRush2, null, "Bungee");

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

		UpdateAfterPlaying();
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

	boost::shared_ptr<MenuItem> ArcadeMenu::AddChallenge( const boost::shared_ptr<Challenge> &challenge, const boost::shared_ptr<Awardment> &prereq, const std::wstring &itemname )
	{
		boost::shared_ptr<ArcadeItem> item;
		Localization::Words word = challenge->MenuName != 0 ? challenge->MenuName : challenge->Name;

		item = MakeMagic( ArcadeItem, ( boost::make_shared<EzText>( word, ItemFont ), challenge, prereq ) );

		item->AdditionalOnSelect = boost::make_shared<OnSelectProxy>( boost::static_pointer_cast<ArcadeMenu>( shared_from_this() ) );

		item->Name = itemname;
		AddItem( item );

		item->setGo( boost::make_shared<GoProxy>( boost::static_pointer_cast<ArcadeMenu>( shared_from_this() ) ) );

		return item;
	}

		void ArcadeMenu::UpdateAfterPlaying()
        {
            int Level = PlayerManager::MaxPlayerTotalArcadeLevel();
            bool ShowLevel = Level > 0;

            if (ShowLevel)
            {
                MyPile->FindEzText( L"Level" )->Show = true;
                
                boost::shared_ptr<EzText> _t = MyPile->FindEzText( L"LevelNum" );
                _t->Show = true;
                _t->SubstituteText( ToString( Level ) );
            }
            else
            {
                MyPile->FindEzText( L"Level" )->Show = false;
                MyPile->FindEzText( L"LevelNum" )->Show = false;
            }

			for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator _item = MyMenu->Items.begin(); _item != MyMenu->Items.end(); ++_item )
            {
                boost::shared_ptr<ArcadeItem> item = boost::dynamic_pointer_cast<ArcadeItem>( *_item );
                if (0 == item) continue;

                if (item->IsLocked())
                {
                    item->MyText->Alpha = .4f;
                    item->MySelectedText->Alpha = .4f;
                }
                else
                {
                    item->MyText->Alpha = 1.f;
                    item->MySelectedText->Alpha = 1.f;
                }
            }
        }

        void ArcadeMenu::OnSelect()
        {
			boost::shared_ptr<ArcadeItem> item = boost::dynamic_pointer_cast<ArcadeItem>( MyMenu->getCurItem() );
            if (0 == item) return;

            Lock = item->IsLocked();

            if (Lock)
            {
                boost::shared_ptr<EzText> _t;
                _t = MyPile->FindEzText( L"Requirement2" );
                //_t.Show = true;
                //_t.SubstituteText(Localization::WordString(Localization::Words_Required) + " " +
                //                  Localization::WordString(Localization::Words_Level) + " " + item.MyPrereq.MyInt.ToString());
                _t->SubstituteText(Localization::WordString(Localization::Words_Level) + L" " + ToString( item->MyPrereq->MyInt ) );
            }
            else
            {
                //MyPile.FindEzText("Requirement").Show = false;
            }
        }

	void ArcadeMenu::Go( const boost::shared_ptr<MenuItem> &item )
	{
	}

	void ArcadeMenu::MyPhsxStep()
	{
        if (Lock)
        {
            RequiredText->Alpha += .2f;
            if (RequiredText->Alpha > 1) RequiredText->Alpha = 1;
        }
        else
        {
            RequiredText->Alpha -= .2f;
            if (RequiredText->Alpha < 0) RequiredText->Alpha = 0;
        }
        TextBack->setAlpha( RequiredText->Alpha );
        RequiredText2->Alpha = RequiredText->Alpha;

		ArcadeBaseMenu::MyPhsxStep();
	}

	void ArcadeMenu::InitializeInstanceFields()
	{
		Long = false;
		Lock = false;
	}
}
