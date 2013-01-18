#include <global_header.h>

#include <Hacks\List.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	HeroItem::HeroItem( const std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > &pair )
		: MenuItem( boost::shared_ptr<EzText>( 0 ) )
	{
	}
	boost::shared_ptr<HeroItem> HeroItem::HeroItem_Construct( const std::pair<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> > &pair )
	{
		MenuItem::MenuItem_Construct( boost::make_shared<EzText>( Hero->Name, Resources::Font_Grobold42_2 ) );

        this->Hero = pair.first;
        this->RequiredHero = pair.second.first;
        this->RequiredHeroLevel = pair.second.second;

		return boost::static_pointer_cast<HeroItem>( shared_from_this() );
	}

	StartMenu_MW_HeroSelect::OnSelectProxy::OnSelectProxy( const boost::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs )
	{
		this->smmwhs = smmwhs;
	}

	void StartMenu_MW_HeroSelect::OnSelectProxy::Apply()
	{
		smmwhs->OnSelect();
	}

	StartMenu_MW_HeroSelect::UpdateScoreProxy::UpdateScoreProxy( const boost::shared_ptr<StartMenu_MW_HeroSelect> &smmwhs )
	{
		this->smmwhs = smmwhs;
	}

	void StartMenu_MW_HeroSelect::UpdateScoreProxy::Apply()
	{
		smmwhs->UpdateScore();
	}

	StartMenu_MW_HeroSelect::StartMenuGoLambda::StartMenuGoLambda( const boost::shared_ptr<StartMenu_MW_HeroSelect> &hs )
	{
		this->hs = hs;
	}

	void StartMenu_MW_HeroSelect::StartMenuGoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		hs->Go( item );
	}

	StartMenu_MW_HeroSelect::StartMenu_MW_HeroSelect( const boost::shared_ptr<TitleGameData_MW> &Title, const boost::shared_ptr<ArcadeMenu> &Arcade, const boost::shared_ptr<ArcadeItem> &MyArcadeItem ) : ArcadeBaseMenu() { }
	boost::shared_ptr<StartMenu_MW_HeroSelect> StartMenu_MW_HeroSelect::StartMenu_MW_HeroSelect_Construct( const boost::shared_ptr<TitleGameData_MW> &Title, const boost::shared_ptr<ArcadeMenu> &Arcade, const boost::shared_ptr<ArcadeItem> &MyArcadeItem )
	{
		ArcadeBaseMenu::ArcadeBaseMenu_Construct();

		this->Lock = false;

		this->Title = Title;
		this->Arcade = Arcade;
		this->MyArcadeItem = MyArcadeItem;

		return boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() );
	}

	void StartMenu_MW_HeroSelect::Release()
	{
		ArcadeBaseMenu::Release();

		if ( MyHeroDoll != 0 )
			MyHeroDoll->Release();
		if ( Options != 0 )
			Options->Release();

		Title.reset();
		Arcade.reset();
	}

        bool StartMenu_MW_HeroSelect::Locked()
        {
            boost::shared_ptr<HeroItem> item = boost::dynamic_pointer_cast<HeroItem>( MyMenu->getCurItem() );
            if ( 0 == item ) return false;

            return Locked(item);
        }

        bool StartMenu_MW_HeroSelect::Locked(boost::shared_ptr<HeroItem> item)
        {
            if ( item->RequiredHero == 0 ) return false;

            int level = MyArcadeItem->MyChallenge->CalcTopGameLevel( item->RequiredHero );
            return level < item->RequiredHeroLevel && !CloudberryKingdomGame::Unlock_Levels;
        }

        bool StartMenu_MW_HeroSelect::Invisible(boost::shared_ptr<HeroItem> item)
        {
            if ( item->RequiredHero == 0 ) return false;

            int level = MyArcadeItem->MyChallenge->CalcTopGameLevel( item->RequiredHero );
            return level < item->RequiredHeroLevel && !CloudberryKingdomGame::Unlock_Levels && item->RequiredHeroLevel >= 100;
        }


	void StartMenu_MW_HeroSelect::OnSelect()
	{
		boost::shared_ptr<HeroItem> item = boost::dynamic_pointer_cast<HeroItem>( MyMenu->getCurItem() );
		if ( 0 == item )
			return;

            Lock = Locked();

            if (Lock)
            {
                int level = item->RequiredHeroLevel;
                std::wstring name = Localization::WordString( item->RequiredHero->Name );
                std::wstring m = Localization::WordString( Localization::Words_LEVEL ) + L" " + ToString( level );

                boost::shared_ptr<EzText> _t;
                MyPile->FindEzText( L"LockedHeader" )->Show = true;
                _t = MyPile->FindEzText( L"RequiredHero" ); _t->Show = true; _t->SubstituteText( name );
                _t = MyPile->FindEzText( L"RequiredLevel" ); _t->Show = true; _t->SubstituteText( m );
                

                MyPile->FindEzText( L"ScoreHeader" )->Show = false;
                MyPile->FindEzText( L"Score" )->Show = false;
                MyPile->FindEzText( L"LevelHeader" )->Show = false;
                MyPile->FindEzText( L"Level" )->Show = false;
            }
            else
            {
                MyPile->FindEzText( L"LockedHeader" )->Show = false;
                MyPile->FindEzText( L"RequiredHero" )->Show = false;
                MyPile->FindEzText( L"RequiredLevel" )->Show = false;

                MyPile->FindEzText( L"ScoreHeader" )->Show = true;
                MyPile->FindEzText( L"Score" )->Show = true;
                MyPile->FindEzText( L"LevelHeader" )->Show = true;
                MyPile->FindEzText( L"Level" )->Show = true;
            }

		Challenge::ChosenHero = item->Hero;
		MyHeroDoll->MakeHeroDoll( item->Hero );

		UpdateScore();
	}

	void StartMenu_MW_HeroSelect::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_KOBBLER_BLUR );
		ArcadeBaseMenu::SlideIn( 0 );

		if ( MyHeroDoll != 0 )
		{
			MyHeroDoll->SlideIn( 0 );
			MyHeroDoll->Hid = false;
		}
		if ( Options != 0 )
			Options->SlideIn( 0 );
	}

	void StartMenu_MW_HeroSelect::SlideOut( PresetPos Preset, int Frames )
	{
		ArcadeBaseMenu::SlideOut( Preset, 0 );

		if ( MyHeroDoll != 0 )
			MyHeroDoll->SlideOut( Preset, 0 );
		if ( Options != 0 )
			Options->SlideOut( Preset, 0 );
	}

	void StartMenu_MW_HeroSelect::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		ArcadeBaseMenu::SetItemProperties( item );

		SetItemProperties_FadedOnUnselect( item );
	}

	void StartMenu_MW_HeroSelect::SetItemProperties_FadedOnUnselect( const boost::shared_ptr<MenuItem> &item )
	{
		item->MySelectedText->Shadow = item->MyText->Shadow = false;

		StartMenu::SetItemProperties_Green( item, true );

		item->MyText->OutlineColor.W *= .4f;
		item->MySelectedText->OutlineColor.W *= .7f;
	}

	void StartMenu_MW_HeroSelect::OnAdd()
	{
		ArcadeBaseMenu::OnAdd();

		// Hero Doll
		MyHeroDoll = MakeMagic( HeroDoll, ( getControl() ) );
		MyGame->AddGameObject( MyHeroDoll );

		// Options. Menu for PC, graphics only for consoles.
		Options = MakeMagic( HeroSelectOptions, ( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) ) );
		MyGame->AddGameObject( Options );

		Update();
	}

	void StartMenu_MW_HeroSelect::Init()
	{
		 ArcadeBaseMenu::Init();

		MyPile = boost::make_shared<DrawPile>();

		CallDelay = ReturnToCallerDelay = 0;

		Score = boost::make_shared<EzText>( std::wstring( L"0" ), Resources::Font_Grobold42_2 );
		Level_Renamed = boost::make_shared<EzText>( std::wstring( L"0" ), Resources::Font_Grobold42_2 );



		// Menu
		boost::shared_ptr<MiniMenu> mini = boost::make_shared<MiniMenu>();
		MyMenu = mini;

		MyMenu->OnSelect = boost::make_shared<UpdateScoreProxy>( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) );

		mini->WrapSelect = false;
		mini->Shift = Vector2( 0, -135 );
		mini->ItemsToShow = 6;
		FontScale *= .75f;

		for ( std::map<boost::shared_ptr<BobPhsx>, std::pair<boost::shared_ptr<BobPhsx>, int> >::const_iterator phsx = ArcadeMenu::HeroArcadeList.begin(); phsx != ArcadeMenu::HeroArcadeList.end(); ++phsx )
		{
			boost::shared_ptr<HeroItem> item = MakeMagic( HeroItem, ( *phsx ) );
			item->AdditionalOnSelect = boost::make_shared<OnSelectProxy>( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) );
			AddItem( item );
			item->setGo( boost::make_shared<StartMenuGoLambda>( boost::static_pointer_cast<StartMenu_MW_HeroSelect>( shared_from_this() ) ) );
		}

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
		EnsureFancy();

		/// <summary>
		/// Left Side
		/// </summary>
		#pragma region
		// Black box, left side
		boost::shared_ptr<QuadClass> BackBoxLeft = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ) );
		BackBoxLeft->setAlpha( 1 );
		MyPile->Add( BackBoxLeft, std::wstring( L"BoxLeft" ) );
		#pragma endregion

		/// <summary>
		/// Right Side
		/// </summary>
		#pragma region
		// Black box, right side
		boost::shared_ptr<QuadClass> BackBox = boost::make_shared<QuadClass>( std::wstring( L"Arcade_Box" ) );
		BackBox->setAlpha( 1 );
		MyPile->Add( BackBox, std::wstring( L"BoxRight" ) );

		// Score, level
		boost::shared_ptr<EzText> ScoreHeader = boost::make_shared<EzText>( Localization::Words_HIGH_SCORE, Resources::Font_Grobold42_2 );
		StartMenu::SetText_Green( ScoreHeader, true );
		MyPile->Add( ScoreHeader, std::wstring( L"ScoreHeader" ) );

		MyPile->Add( Score, std::wstring( L"Score" ) );

		boost::shared_ptr<EzText> LevelHeader = boost::make_shared<EzText>( Localization::Words_BEST_LEVEL, Resources::Font_Grobold42_2 );
		StartMenu::SetText_Green( LevelHeader, true );
		MyPile->Add( LevelHeader, std::wstring( L"LevelHeader" ) );

		MyPile->Add( Level_Renamed, std::wstring( L"Level" ) );

            // Locked
            boost::shared_ptr<EzText> LockedHeader = boost::make_shared<EzText>( Localization::Words_Required, Resources::Font_Grobold42 );
            LockedHeader->_Scale *= .9f;
            StartMenu::SetText_Green(LockedHeader, true );
            MyPile->Add(LockedHeader, L"LockedHeader" );
            LockedHeader->Show = false;

            boost::shared_ptr<EzText> RequiredHero = boost::make_shared<EzText>( L"Garbage", Resources::Font_Grobold42 );
            RequiredHero->_Scale *= .72f;
            StartMenu::SetText_Green(RequiredHero, true );
            MyPile->Add(RequiredHero, L"RequiredHero" );
            RequiredHero->Show = false;

            boost::shared_ptr<EzText> RequiredLevel = boost::make_shared<EzText>( L"Garbage", Resources::Font_Grobold42 );
            RequiredLevel->_Scale *= .72f;
            StartMenu::SetText_Green(RequiredLevel, true );
            MyPile->Add(RequiredLevel, L"RequiredLevel" );
            RequiredLevel->Show = false;

		#pragma endregion

		/// <summary>
		/// Back
		/// </summary>
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack() ), std::wstring( L"Back" ) );
		MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"BackArrow2" ), std::wstring( L"BackArrow" ) ) );

		MyPile->FadeIn( .33f );

		SetPos();
	}

	void StartMenu_MW_HeroSelect::OnReturnTo()
	{
		ArcadeBaseMenu::OnReturnTo();

		UpdateScore();
		Update();
	}

	void StartMenu_MW_HeroSelect::UpdateScore()
	{
		boost::shared_ptr<HeroItem> item = boost::dynamic_pointer_cast<HeroItem>( MyMenu->getCurItem() );
		if ( 0 == item )
			return;

		int TopScore = MyArcadeItem->MyChallenge->TopScore();
		int TopLevel = MyArcadeItem->MyChallenge->TopLevel();

		Score->RightJustify = Level_Renamed->RightJustify = true;
		Score->SubstituteText( StringConverterHelper::toString( TopScore ) );
		Level_Renamed->SubstituteText( StringConverterHelper::toString( TopLevel ) );
	}

    void StartMenu_MW_HeroSelect::Update()
    {
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator _item = MyMenu->Items.begin(); _item != MyMenu->Items.end(); ++_item )
        {
            boost::shared_ptr<HeroItem> item = boost::dynamic_pointer_cast<HeroItem>( *_item );
            if ( 0 != item )
            {
                if ( Locked( item ) )
                {
                    item->MyText->Alpha = .4f;
                    item->MySelectedText->Alpha = .4f;

                    if (Invisible(item))
                    {
                        item->Selectable = false;
                        item->MyText->Alpha = 0;
                        item->MySelectedText->Alpha = 0;
                    }

                }
                else
                {
                    item->MyText->Alpha = 1.f;
                    item->MySelectedText->Alpha = 1.f;
                }
            }
        }
    }

	void StartMenu_MW_HeroSelect::SetPos()
	{
		MyMenu->setPos( Vector2( -1340.222f, 104.4444f ) );

		boost::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( std::wstring( L"ScoreHeader" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -22.22266f, 636.1111f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( std::wstring( L"Score" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 1161.11f, 366.6667f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( std::wstring( L"LevelHeader" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -2.779297f, 105.5556f ) );
			_t->setScale( 1 );
		}
		_t = MyPile->FindEzText( std::wstring( L"Level" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( 1163.887f, -155.5555f ) );
			_t->setScale( 1 );
		}

        _t = MyPile->FindEzText( L"LockedHeader" ); if (_t != 0) { _t->setPos( Vector2(33.33325f, 441.6666f) ); _t->_Scale = 0.9f; }
        _t = MyPile->FindEzText( L"RequiredHero" ); if (_t != 0) { _t->setPos( Vector2(280.5552f, 163.8889f) ); _t->_Scale = 0.72f; }
        _t = MyPile->FindEzText( L"RequiredLevel" ); if (_t != 0) { _t->setPos( Vector2(277.7778f, -44.44443f) ); _t->_Scale = 0.72f; }


		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( std::wstring( L"BoxLeft" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -972.2227f, -127.7778f ) );
			_q->setSize( Vector2( 616.5467f, 1004.329f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"BoxRight" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 666.6641f, -88.88879f ) );
			_q->setSize( Vector2( 776.5515f, 846.666f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"Back" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -1269.443f, -1011.111f ) );
			_q->setSize( Vector2( 64.49973f, 64.49973f ) );
		}
		_q = MyPile->FindQuad( std::wstring( L"BackArrow" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -1416.666f, -1016.667f ) );
			_q->setSize( Vector2( 71.89921f, 61.83332f ) );
		}

		MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );

	}

	void StartMenu_MW_HeroSelect::Go( const boost::shared_ptr<MenuItem> &item )
	{
		if (Lock) return;

		boost::shared_ptr<HeroItem> _item = boost::dynamic_pointer_cast<HeroItem>( MyMenu->getCurItem() );
		if ( 0 == _item ) return;
		int TopLevelForHero = MyArcadeItem->MyChallenge->CalcTopGameLevel( _item->Hero );

		//int TopLevelForHero = MyArcadeItem.MyChallenge.TopLevel();

		boost::shared_ptr<StartLevelMenu> levelmenu = MakeMagic( StartLevelMenu, ( TopLevelForHero ) );

		levelmenu->MyMenu->SelectItem( StartLevelMenu::PreviousMenuIndex );
		levelmenu->StartFunc = boost::make_shared<StartFuncProxy>( boost::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) );
		levelmenu->ReturnFunc.reset();

		Call( levelmenu );
		Hide();
	}
}
