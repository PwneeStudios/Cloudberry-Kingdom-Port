#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	CampaignChapterItem::CampaignLevelsLambda::CampaignLevelsLambda()
	{
	}

	int CampaignChapterItem::CampaignLevelsLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->CampaignLevel;
	}

	CampaignChapterItem::CampaignChapterItem( const boost::shared_ptr<EzText> &Text, int Chapter ) : MenuItem( Text )
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<CampaignChapterItem> CampaignChapterItem::CampaignChapterItem_Construct( const boost::shared_ptr<EzText> &Text, int Chapter )
	{
		MenuItem::MenuItem_Construct( Text );

		this->Chapter = Chapter;

		UpdateLock();

		return boost::static_pointer_cast<CampaignChapterItem>( shared_from_this() );
	}

	void CampaignChapterItem::UpdateLock()
	{
        Locked = false;
        if (!CloudberryKingdomGame::Unlock_Levels)
        {
            switch (Chapter)
            {
                case 1: Locked = false; break;
                case 2: Locked = !PlayerManager::Awarded(Awardments::Award_Campaign1); break;
                case 3: Locked = !PlayerManager::Awarded(Awardments::Award_Campaign2); break;
                case 4: Locked = !PlayerManager::Awarded(Awardments::Award_Campaign3); break;
				case 5: Locked = !PlayerManager::Awarded(Awardments::Award_Campaign4); break;
                default: Locked = false; break;
            }
        }
	}

	void CampaignChapterItem::InitializeInstanceFields()
	{
		Chapter = 0;
		Locked = false;
	}


        void StartMenu_MW_Campaign::OnReturnTo()
        {
            StartMenu::OnReturnTo();

            Update();
        }

        void StartMenu_MW_Campaign::Update()
        {
            // Update level text
            int Level = PlayerManager::MaxPlayerTotalCampaignIndex();
            bool ShowLevel = Level > 0;

            if (ShowLevel)
            //if (true)
            {
                MyPile->FindEzText( L"Level" )->Show = true;
                MyPile->FindQuad( L"BoxLeft" )->Show = true;

                boost::shared_ptr<EzText> _t = MyPile->FindEzText( L"LevelNum" );
                _t->Show = true;
                _t->SubstituteText( ToString( Level ) );
            }
            else
            {
                MyPile->FindEzText( L"Level" )->Show = false;
                MyPile->FindEzText( L"LevelNum" )->Show = false;
                MyPile->FindQuad( L"BoxLeft" )->Show = false;
            }


            // Update menu items (faded if locked)
			for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator _item = MyMenu->Items.begin(); _item != MyMenu->Items.end(); ++_item )
            {
                boost::shared_ptr<CampaignChapterItem> item = boost::dynamic_pointer_cast<CampaignChapterItem>( *_item );
                if (0 != item)
                {
                    item->UpdateLock();

                    if (item->Locked)
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
        }



	StartMenu_MW_Campaign::CampaignGoLambda::CampaignGoLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &cine )
	{
		this->cine = cine;
	}

	void StartMenu_MW_Campaign::CampaignGoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		cine->Go( item );
	}

	StartMenu_MW_Campaign::GoLambda::GoLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &sm )
	{
		this->sm = sm;
	}

	void StartMenu_MW_Campaign::GoLambda::Apply()
	{
		sm->Active = true;
		sm->MyGame->FadeIn( .05f );
		CampaignSequence::getInstance()->Start(sm->_StartLevel);
		sm->MyGame->WaitThenDo(0, boost::make_shared<OnReturnFromGameLambda>( sm ) );
	}

	StartMenu_MW_Campaign::OnReturnFromGameLambda::OnReturnFromGameLambda( const boost::shared_ptr<StartMenu_MW_Campaign> &sm )
	{
		this->sm = sm;
	}

	void StartMenu_MW_Campaign::OnReturnFromGameLambda::Apply()
	{
		sm->OnReturnFromGame();
	}


	StartMenu_MW_Campaign::StartMenu_MW_Campaign( const boost::shared_ptr<TitleGameData_MW> &Title ) : 
		StartMenu(),
		_StartLevel( 0 )
	{
	}
	boost::shared_ptr<StartMenu_MW_Campaign> StartMenu_MW_Campaign::StartMenu_MW_Campaign_Construct( const boost::shared_ptr<TitleGameData_MW> &Title )
	{
		StartMenu::StartMenu_Construct();
		this->Title = Title;

		return boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() );
	}

	void StartMenu_MW_Campaign::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_PRINCESS );

		StartMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Campaign::SlideOut( PresetPos Preset, int Frames )
	{
		StartMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Campaign::SetText( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( bColor( 34, 214, 47 ) ).ToVector4();
		text->OutlineColor = ( bColor( 0, 0, 0, 0 ) ).ToVector4();
	}

	void StartMenu_MW_Campaign::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		StartMenu::SetItemProperties( item );

		SetText( item->MyText );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
		item->MySelectedText->MyFloatColor = ( bColor( 73, 255, 86 ) ).ToVector4();
		item->MySelectedText->OutlineColor = ( bColor( 0, 0, 0, 0 ) ).ToVector4();

		//item.MyOscillateParams.Set(1f, 1.01f, .005f);
	}

	void StartMenu_MW_Campaign::OnAdd()
	{
		StartMenu::OnAdd();
	}

	void StartMenu_MW_Campaign::Init()
	{
		 StartMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		MyMenu->ClearList();

		MakeHeader();

		CreateMenu();

		Update();
	}

	void StartMenu_MW_Campaign::CreateMenu()
	{
		boost::shared_ptr<MenuItem> item;

		// Chapter 1
		item = MakeMagic( CampaignChapterItem, ( boost::make_shared<EzText>( Localization::Words_TheBeginning, ItemFont ), 1 ) );
		item->Name = std::wstring( L"MainCampaign" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 2
		item = MakeMagic( CampaignChapterItem, ( boost::make_shared<EzText>( Localization::Words_TheNextNinetyNine, ItemFont ), 2 ) );
		item->Name = std::wstring( L"Easy" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 3
		item = MakeMagic( CampaignChapterItem, ( boost::make_shared<EzText>( Localization::Words_AGauntletOfDoom, ItemFont ), 3 ) );
		item->Name = std::wstring( L"Hard" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 4
		item = MakeMagic( CampaignChapterItem, ( boost::make_shared<EzText>( Localization::Words_AlmostHero, ItemFont ), 4 ) );
		item->Name = std::wstring( L"Hardcore" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		// Chapter 5
		item = MakeMagic( CampaignChapterItem, ( boost::make_shared<EzText>( Localization::Words_TheMasochist, ItemFont ), 5 ) );
		item->Name = std::wstring( L"Maso" );
		item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
		AddItem( item );

		MyMenu->SelectItem( 0 );

        // Level
        boost::shared_ptr<QuadClass> TextBack = boost::make_shared<QuadClass>( L"Arcade_BoxLeft", 100.f, true);
        TextBack->setAlpha( 1.f );
        TextBack->setDegrees( 90 );
        MyPile->Add(TextBack, L"BoxLeft");

        boost::shared_ptr<EzText> LevelText = boost::make_shared<EzText>(Localization::Words_Level, Resources::Font_Grobold42);
        LevelText->_Scale *= .72f;
        StartMenu::SetText_Green( LevelText, true );
        MyPile->Add(LevelText, L"Level");
        LevelText->Show = false;

        boost::shared_ptr<EzText> LevelNum = boost::make_shared<EzText>( L"Garbage", Resources::Font_Grobold42);
        LevelNum->_Scale *= 1.1f;
        StartMenu::SetText_Green( LevelNum, true );
        MyPile->Add(LevelNum, L"LevelNum");
        LevelNum->Show = false;

		//SetPos_NoCinematic();
		SetPos_WithCinematic();
	}

	void StartMenu_MW_Campaign::MakeHeader()
	{
		boost::shared_ptr<EzText> Header = boost::make_shared<EzText>( Localization::Words_StoryMode, ItemFont );
		Header->Name = std::wstring( L"Header" );
		Header->setScale( Header->getScale() * 1.3f );
		SetText( Header );
		Header->OutlineColor = Color::Black.ToVector4();
		MyPile->Add( Header );

		Header->setPos( Vector2( -800.0029f, 863.8889f ) );
	}

	void StartMenu_MW_Campaign::Go( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<CampaignChapterItem> c_item = boost::dynamic_pointer_cast<CampaignChapterItem>( item );
		if ( 0 == c_item )
			return;

		if ( c_item->Locked ) return;

		Go( c_item->Chapter );
	}

	void StartMenu_MW_Campaign::Go( int StartLevel )
	{
		Tools::SongWad->FadeOut();
		MyGame->FadeToBlack( .0225f, 20 );
		Active = false;

		_StartLevel = StartLevel;
		MyGame->WaitThenDo( 75, boost::make_shared<GoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
	}

    void StartMenu_MW_Campaign::OnReturnFromGame()
    {
        Update();
        SaveGroup::SaveAll();
    }

	void StartMenu_MW_Campaign::SetPos_NoCinematic()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"MainCampaign" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 686.4453f, 191.6667f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, 186.1112f ) );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Easy" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 708.665f, -36.44455f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Hard" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 711.4443f, -239.5557f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Hardcore" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 714.2227f, -437.111f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Maso" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 730.8906f, -656.889f ) );
			_item->MyText->setScale( 0.8f );
			_item->MySelectedText->setScale( 0.8f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			_item->SetSelectedPos( Vector2( 622.5566f, -1 ) );
		}

		MyMenu->setPos( Vector2( -783.3339f, 227.7778f ) );
	}

	void StartMenu_MW_Campaign::SetPos_WithCinematic()
    {
        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"MainCampaign" ); if (_item != 0 ) { _item->setSetPos( Vector2( 686.4453f, 191.6667f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2( 622.5566f, 186.1112f )); }
        _item = MyMenu->FindItemByName( L"Easy" ); if (_item != 0 ) { _item->setSetPos( Vector2( 708.665f, -36.44455f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2( 622.5566f, -1.f )); }
        _item = MyMenu->FindItemByName( L"Hard" ); if (_item != 0 ) { _item->setSetPos( Vector2( 711.4443f, -239.5557f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2( 622.5566f, -1.f )); }
        _item = MyMenu->FindItemByName( L"Hardcore" ); if (_item != 0 ) { _item->setSetPos( Vector2( 714.2227f, -437.111f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2( 622.5566f, -1.f )); }
        _item = MyMenu->FindItemByName( L"Maso" ); if (_item != 0 ) { _item->setSetPos( Vector2( 730.8906f, -656.889f ) ); _item->MyText->setScale( 0.8f ); _item->MySelectedText->setScale( 0.8f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2( 622.5566f, -1.f )); }

        MyMenu->setPos( Vector2(-783.3339f, 227.7778f ) );

        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
        _t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1241.667f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
        _t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-775.0001f, -513.8888f ) ); _t->setScale( 1.001751f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 172.6158f, 503.8864f ) ); }

        MyPile->setPos( Vector2( 0.f, 0.f ) );
    }
}
