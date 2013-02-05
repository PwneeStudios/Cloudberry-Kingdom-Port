#include <global_header.h>

#include "StartMenu_MW_Pre.h"

#include <Game/Player/LeaderboardView.h>

namespace CloudberryKingdom
{

	void StartMenu_MW_Pre::MenuGo_Options( boost::shared_ptr<MenuItem> item )
    {
        Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );
        Call( MakeMagic( StartMenu_MW_Options, ( getControl(), true ) ), 0 );
        CallingOptionsMenu = true;
    }

    void StartMenu_MW_Pre::Exit()
    {
        SelectSound = 0;
        Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR_DARK );
        Call( MakeMagic( StartMenu_MW_Exit, ( getControl() ) ), 0 );
    }

    void StartMenu_MW_Pre::BringNextMenu()
    {
        StartMenu::BringNextMenu();

        Hide();
    }

	StartMenu_MW_Pre::StartMenu_MW_Pre( boost::shared_ptr<TitleGameData_MW> Title ) : StartMenu(),
		CallingOptionsMenu( false )
    {
	}
		
	boost::shared_ptr<StartMenu_MW_Pre> StartMenu_MW_Pre::StartMenu_MW_Pre_Construct( boost::shared_ptr<TitleGameData_MW> Title )
	{
		StartMenu::StartMenu_Construct();
		
        this->Title = Title;
        CallingOptionsMenu = false;
			
		return boost::static_pointer_cast<StartMenu_MW_Pre>( shared_from_this() );
    }

    void StartMenu_MW_Pre::SlideIn( int Frames )
    {
        Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_TITLE );
        StartMenu::SlideIn( 0 );
    }

    void StartMenu_MW_Pre::SlideOut( PresetPos Preset, int Frames )
    {
        StartMenu::SlideOut( Preset, 0 );
    }

    void StartMenu_MW_Pre::SetItemProperties( boost::shared_ptr<MenuItem> item )
    {
        StartMenu::SetItemProperties( item );

        item->MySelectedText->Shadow = item->MyText->Shadow = false;
    }

    void StartMenu_MW_Pre::OnAdd()
    {
        StartMenu::OnAdd();
    }

    void StartMenu_MW_Pre::OnReturnTo()
    {
        if ( CallingOptionsMenu )
        {
            MyMenu->SelectItem( 4 );
            CallingOptionsMenu = false;
        }

        StartMenu::OnReturnTo();
    }

    bool StartMenu_MW_Pre::MenuReturnToCaller( boost::shared_ptr<Menu> menu )
    {
        if ( NoBack ) return false;

        return StartMenu::MenuReturnToCaller( menu );
    }

    void StartMenu_MW_Pre::Init()
    {
 	    StartMenu::Init();

        CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

        BackBox = boost::make_shared<QuadClass>( L"Title_Strip" );
        BackBox->setAlpha( .9f );
        MyPile->Add( BackBox, L"Back" );

        MyPile->FadeIn(.33f );

        SetPos();
    }

    void StartMenu_MW_Pre::MenuGo_Play( boost::shared_ptr<MenuItem> item )
    {
        Call( MakeMagic( StartMenu_MW, ( Title ) ), 0 );
    }

    void StartMenu_MW_Pre::MenuGo_Leaderboards( boost::shared_ptr<MenuItem> item )
    {
        Call( MakeMagic( LeaderboardGUI, ( Title, 0 ) ), 0 );
    }

    void StartMenu_MW_Pre::MenuGo_Achievements( boost::shared_ptr<MenuItem> item )
    {
    }

    void StartMenu_MW_Pre::MenuGo_BuyGame( boost::shared_ptr<MenuItem> item )
    {
    }

    void StartMenu_MW_Pre::MakeMenu()
    {
        boost::shared_ptr<MenuItem> item;

        // Play
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( L"Play Game", ItemFont, true ) ) );
        item->Name = L"Play";
        item->setGo( boost::make_shared<MenuGo_PlayProxy>( boost::static_pointer_cast<StartMenu_MW_Pre>( shared_from_this() ) ) );
        AddItem( item );

        // Leaderboard
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Leaderboard, ItemFont, true ) ) );
        item->Name = L"Leaderboard";
        item->setGo( boost::make_shared<MenuGo_LeaderboardsProxy>( boost::static_pointer_cast<StartMenu_MW_Pre>( shared_from_this() ) ) );
        AddItem( item );

        // Achievements
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Achievement, ItemFont, true ) ) );
        item->Name = L"Achievements";
        item->setGo( boost::make_shared<MenuGo_AchievementsProxy>( boost::static_pointer_cast<StartMenu_MW_Pre>( shared_from_this() ) ) );
        AddItem( item );

        //// Options
        //item = MenuItem( boost::make_shared<EzText>( Localization::Words_Options, ItemFont, true ));
        //item->Name = L"Options";
        //item->setGo( boost::make_shared<MenuGo_OptionsProxy>( boost::static_pointer_cast<StartMenu_MW_Pre>( shared_from_this() ) ) );
        //AddItem( item );

        // Buy Game
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_UnlockFullGame, ItemFont, true ) ) );
        item->Name = L"Buy";
        item->setGo( boost::make_shared<MenuGo_BuyGameProxy>( boost::static_pointer_cast<StartMenu_MW_Pre>( shared_from_this() ) ) );
        AddItem( item );

        // Exit
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Exit, ItemFont, true ) ) );
        item->Name = L"Exit";
        item->setGo( boost::make_shared<MenuGo_ExitProxy>( boost::static_pointer_cast<StartMenu_MW_Pre>( shared_from_this() ) ) );
        AddItem( item );

        EnsureFancy();

        this->CallToLeft = true;
    }

	void StartMenu_MW_Pre::SetPos()
    {
        BackBox->setTextureName( L"White" );
        BackBox->Quad_Renamed.SetColor( ColorHelper::Gray(.1f ));
        BackBox->setAlpha( .73f );

        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Play" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, 168.3334f ) ); _item->MyText->setScale( 0.605f ); _item->MySelectedText->setScale( 0.605f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Leaderboard" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -29.22222f ) ); _item->MyText->setScale( 0.605f ); _item->MySelectedText->setScale( 0.605f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Achievements" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -229.5555f ) ); _item->MyText->setScale( 0.605f ); _item->MySelectedText->setScale( 0.605f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Buy" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -435.7777f ) ); _item->MyText->setScale( 0.605f ); _item->MySelectedText->setScale( 0.605f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
        _item = MyMenu->FindItemByName( L"Exit" ); if (_item != 0 ) { _item->setSetPos( Vector2( 0.f, -624.9999f ) ); _item->MyText->setScale( 0.605f ); _item->MySelectedText->setScale( 0.605f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

        MyMenu->setPos( Vector2(-91.66698f, -19.4445f ) );

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"Back" ); if (_q != 0 ) { _q->setPos( Vector2(-61.11133f, -336.1111f ) ); _q->setSize( Vector2( 608.4988f, 520.8323f ) ); }

        MyPile->setPos( Vector2(-27.77734f, -33.33337f ) );
    }

}