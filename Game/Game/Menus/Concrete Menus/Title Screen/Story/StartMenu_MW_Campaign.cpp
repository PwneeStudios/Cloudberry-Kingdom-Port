#include <small_header.h>
#include "Game/Menus/Concrete Menus/Title Screen/Story/StartMenu_MW_Campaign.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Text/EzText.h"
#include "Game/Games/Campaign/CampaignSequence.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Game/Player/PlayerData.h"
#include "Game/Menus/Menu.h"
#include "Core/Song/EzSongWad.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include "Game/Menus/Concrete Menus/ShopMenu.h"
#include <Hacks\String.h>

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
			int level = PlayerManager::MinPlayerTotalCampaignLevel();
			if ( Contains( CampaignSequence::getInstance()->ChapterEnd, (Chapter - 1) ) )
				Locked = level < CampaignSequence::getInstance()->ChapterEnd[ Chapter - 1 ];
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
			boost::shared_ptr<EzText> _t;

            // Update level text
            int Level = PlayerManager::MinPlayerTotalCampaignLevel() + 1;

			bool ShowLevel = Level > 1;
            bool ShowContinue = Level > 1 && Level < 321;


			//bool ShowLevel = false;

			//string template_level = Localization::WordString(Localization.Words.Continue) + ", " +
			//              Localization::WordString(Localization.Words.Level) + " {0}";
			std::wstring template_level = Localization::WordString( Localization::Words_Continue );

			boost::shared_ptr<MenuItem> __item = MyMenu->FindItemByName( L"Continue" );
			if ( __item != 0 )
			{
				if ( ShowContinue )
				{
					__item->Selectable = true;
					__item->Show = true;
				}
				else
				{
					if (Level == 0) Level = 1;
					__item->Selectable = false;
					__item->Show = false;
					MyMenu->SelectItem(1);
				}

				__item->MyText->SubstituteText( Format( template_level.c_str(), Level ) );
				__item->MySelectedText->SubstituteText( Format( template_level.c_str(), Level ) );
			}


            if (ShowLevel)
            {
                MyPile->FindEzText( L"Level" )->Show = true;
                MyPile->FindQuad( L"BoxLeft" )->Show = true;

                _t = MyPile->FindEzText( L"LevelNum" );
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
		sm->MyGame->KillToDo( L"StartMusic" );
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

		MyMenu->setControl(-1 );

		Update();

		int Level = PlayerManager::MinPlayerTotalCampaignLevel() + 1;
		bool ShowLevel = Level > 1;
		if (ShowLevel)
			MyMenu->SelectItem( 0 );
		else
			MyMenu->SelectItem( 1 );
	}

	void StartMenu_MW_Campaign::CreateMenu()
	{
		boost::shared_ptr<MenuItem> item;

			// Continue
			int level = PlayerManager::MinPlayerTotalCampaignIndex();
			item = MakeMagic( CampaignChapterItem, (boost::make_shared<EzText>( L"xxx", ItemFont), -1) );
			item->Name = L"Continue";
			item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
			AddItem(item);

            // Chapter 1
			for (int i = 1; i <= 7; i++)
			{
				item = MakeMagic( CampaignChapterItem, (boost::make_shared<EzText>(CampaignSequence::ChapterName[i - 1], ItemFont), i) );
				item->Name = L"Chapter" + ToString( i );
				item->setGo( boost::make_shared<CampaignGoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
				AddItem(item);
			}
			
		//MyMenu->SelectItem( 0 );

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
		if ( CloudberryKingdomGame::LockCampaign ) return;

		// Upsell
		if ( CloudberryKingdomGame::getIsDemo() )
		{
			Call( MakeMagic( UpSellMenu, ( Localization::Words_UpSell_Campaign, MenuItem::ActivatingPlayer ) ) );

			return;
		}

		boost::shared_ptr<CampaignChapterItem> c_item = boost::dynamic_pointer_cast<CampaignChapterItem>( item );
		if ( 0 == c_item )
			return;

		if ( c_item->Locked ) return;

		Go( c_item->Chapter );

		ButtonCheck::PreLogIn = false;
	}

	void StartMenu_MW_Campaign::Go( int StartLevel )
	{
		MyGame->KillToDo( L"StartMusic" );
		Tools::SongWad->FadeOut();
		Tools::SongWad->DisplayingInfo = false;

		MyGame->FadeToBlack( .0225f, 20 );
		Active = false;

		_StartLevel = StartLevel;
		MyGame->WaitThenDo( 75, boost::make_shared<GoLambda>( boost::static_pointer_cast<StartMenu_MW_Campaign>( shared_from_this() ) ) );
	}

    void StartMenu_MW_Campaign::OnReturnFromGame()
    {
        Update();
        //SaveGroup::SaveAll();

		PlayerManager::UploadCampaignLevels();

		Tools::PlayHappyMusic( MyGame );
    }

    void StartMenu_MW_Campaign::SetPos_NoCinematic()
    {
if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, 260.0001f ) ); _item->MyText->setScale( 0.678417f ); _item->MySelectedText->setScale( 0.678417f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, 97.22227f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -65.55551f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -228.3333f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -391.1111f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -553.889f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -716.6667f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -879.4445f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2(-675.0004f, 213.889f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
	_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1241.667f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
	_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-798.8153f, -529.7655f ) ); _t->setScale( 0.9310196f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 172.6158f, 503.8864f ) ); }

	MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1241.667f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-798.8156f, -521.8272f ) ); _t->setScale( 0.9588835f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 172.6158f, 503.8864f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1289.297f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-743.2467f, -521.8271f ) ); _t->setScale( 0.9347109f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-759.525f, -694.8394f ) ); _q->setSize( Vector2( 176.9026f, 548.8981f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1293.266f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-739.2772f, -529.7656f ) ); _t->setScale( 0.9334014f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 171.5441f, 555.8043f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1360.743f, -565.8702f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-747.2157f, -525.7964f ) ); _t->setScale( 0.9230416f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-795.2476f, -698.8085f ) ); _q->setSize( Vector2( 174.1638f, 583.3118f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1261.111f, -594.4445f ) ); _t->setScale( 0.6298336f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-704.3712f, -551.9877f ) ); _t->setScale( 0.7738534f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-763.8892f, -702.7777f ) ); _q->setSize( Vector2( 165.1158f, 494.5531f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1241.667f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-798.8153f, -529.7655f ) ); _t->setScale( 0.9310196f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 172.6158f, 503.8864f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
    }

    void StartMenu_MW_Campaign::SetPos_WithCinematic()
        {
if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, 260.0001f ) ); _item->MyText->setScale( 0.678417f ); _item->MySelectedText->setScale( 0.678417f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, 97.22227f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -65.55551f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -228.3333f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -391.1111f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -553.889f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -716.6667f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 759.4447f, -879.4445f ) ); _item->MyText->setScale( 0.7379997f ); _item->MySelectedText->setScale( 0.7379997f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2(-675.0004f, 213.889f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
	_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1241.667f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
	_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-798.8153f, -529.7655f ) ); _t->setScale( 0.9310196f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 172.6158f, 503.8864f ) ); }

	MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1241.667f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-798.8156f, -521.8272f ) ); _t->setScale( 0.9588835f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 172.6158f, 503.8864f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1289.297f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-743.2467f, -521.8271f ) ); _t->setScale( 0.9347109f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-759.525f, -694.8394f ) ); _q->setSize( Vector2( 176.9026f, 548.8981f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1293.266f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-739.2772f, -529.7656f ) ); _t->setScale( 0.9334014f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 171.5441f, 555.8043f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1360.743f, -565.8702f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-747.2157f, -525.7964f ) ); _t->setScale( 0.9230416f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-795.2476f, -698.8085f ) ); _q->setSize( Vector2( 174.1638f, 583.3118f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1261.111f, -594.4445f ) ); _t->setScale( 0.6298336f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-704.3712f, -551.9877f ) ); _t->setScale( 0.7738534f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-763.8892f, -702.7777f ) ); _q->setSize( Vector2( 165.1158f, 494.5531f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Continue" ); if (_item != 0 ) { _item->setSetPos( Vector2( 726.1112f, 262.7778f ) ); _item->MyText->setScale( 0.6477503f ); _item->MySelectedText->setScale( 0.6477503f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter1" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, 58.33334f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter2" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -92.00005f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter3" ); if (_item != 0 ) { _item->setSetPos( Vector2( 742.7776f, -247.8891f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter4" ); if (_item != 0 ) { _item->setSetPos( Vector2( 745.5554f, -400.9998f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter5" ); if (_item != 0 ) { _item->setSetPos( Vector2( 740.f, -548.5557f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter6" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -700.3333f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Chapter7" ); if (_item != 0 ) { _item->setSetPos( Vector2( 750.3334f, -850.6672f ) ); _item->MyText->setScale( 0.5883336f ); _item->MySelectedText->setScale( 0.5883336f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2(-708.3339f, 216.6667f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-800.0029f, 863.8889f ) ); _t->setScale( 1.3f ); }
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-1241.667f, -577.7778f ) ); _t->setScale( 0.7490832f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2(-798.8153f, -529.7655f ) ); _t->setScale( 0.9310196f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-755.5557f, -702.7777f ) ); _q->setSize( Vector2( 172.6158f, 503.8864f ) ); }

			MyPile->setPos( Vector2( 0.f, 0.f ) );
}
		}
}

