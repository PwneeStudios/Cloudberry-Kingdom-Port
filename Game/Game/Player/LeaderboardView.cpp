#include <global_header.h>

#include "LeaderboardView.h"

namespace CloudberryKingdom
{

    std::wstring LeaderboardGUI::LeaderboardType_ToString( LeaderboardType type )
    {
        switch ( type )
        {
			case LeaderboardType_FriendsScores: return Localization::WordString( Localization::Words_FriendsScores );
            case LeaderboardType_MyScores: return Localization::WordString( Localization::Words_MyScores );
            case LeaderboardType_TopScores: return Localization::WordString( Localization::Words_TopScores );
            default: return L"";
        }
    }

    std::wstring LeaderboardGUI::LeaderboardSortType_ToString( LeaderboardSortType type )
    {
        switch ( type )
        {
            case LeaderboardSortType_Level: return Localization::WordString( Localization::Words_SortByLevel );
            case LeaderboardSortType_Score: return Localization::WordString( Localization::Words_SortByScore );
            default: return L"";
        }
    }

    LeaderboardGUI::LeaderboardGUI( boost::shared_ptr<TitleGameData_MW> Title, int StartIndex )
		: CkBaseMenu()
	{
	}
	boost::shared_ptr<LeaderboardGUI> LeaderboardGUI::LeaderboardGUI_Construct( boost::shared_ptr<TitleGameData_MW> Title, int StartIndex )
    {
		CurrentType = static_cast<LeaderboardType>( 0 );
		CurrentSort = static_cast<LeaderboardSortType>( 0 );
		CurrentMessage = static_cast<Message>( 0 );

		LeaderboardInex = 0;

		DelayCount_LeftRight = MotionCount_LeftRight = 0;
		
		LoadingCount = 0;


		CkBaseMenu::CkBaseMenu_Construct();

        EnableBounce();

        SetIndex( 0 );

        CurrentType = LeaderboardType_FriendsScores;
        CurrentSort = LeaderboardSortType_Level;
        CurrentMessage = Message_None;

        DelayCount_LeftRight = MotionCount_LeftRight = 0;

        this->Title = Title;
        if ( Title != 0 )
            Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_BLUR );

        UpdateView();

		return boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() );
    }

    void LeaderboardGUI::Init()
    {
        CkBaseMenu::Init();

        MyPile = boost::make_shared<DrawPile>();

        boost::shared_ptr<QuadClass> BackBoxLeft = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 100.f, true );
        BackBoxLeft->setDegrees( 90 );
        BackBoxLeft->setAlpha( 1.f );
        MyPile->Add( BackBoxLeft, L"BoxLeft" );

        boost::shared_ptr<QuadClass> Right = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 100.f, true );
        Right->setDegrees( 90 );
        Right->setAlpha( 1.f );
        MyPile->Add( Right, L"BoxRight" );

        boost::shared_ptr<EzText> Header = boost::make_shared<EzText>( std::wstring( L"Top Scores" ), ItemFont );
        MyPile->Add( Header, L"Header" );

        boost::shared_ptr<EzText> GameTitle = boost::make_shared<EzText>( L"Escalation, Classic", ItemFont );
        MyPile->Add( GameTitle, L"GameTitle" );

        Highlight = boost::make_shared<HsvQuad>();
        Highlight->setTextureName( L"WidePlaque" );
        Highlight->setTextureName( L"Arcade_BoxLeft" );
        Highlight->Show = false;
        MyPile->Add( Highlight, L"Highlight" );
        Highlight->setAlpha( .3f );
        Highlight->Quad_Renamed.MyEffect = Tools::HslEffect;
        Highlight->setMyMatrix( ColorHelper::HsvTransform( 1, 0, 1 ) );
        //Highlight->Quad->SetColor( ColorHelper::GrayColor(.7f ));

        TL = boost::make_shared<QuadClass>(); TL->Show = false; MyPile->Add( TL, L"TL" );
        Offset_GamerTag = boost::make_shared<QuadClass>(); Offset_GamerTag->Show = false; MyPile->Add( Offset_GamerTag, L"Offset_GamerTag" );
        Offset_Val = boost::make_shared<QuadClass>(); Offset_Val->Show = false; MyPile->Add( Offset_Val, L"Offset_Val" );
        ItemShift = boost::make_shared<QuadClass>(); ItemShift->Show = false; MyPile->Add( ItemShift, L"Offset" );

        // Messages
        CurrentMessage = Message_None;
        NotRankedFriends = boost::make_shared<EzText>( Localization::Words_NotRankedFriends, ItemFont, 2000.f, true, true );
        MyPile->Add( NotRankedFriends, L"NotRankedFriends" );

        NotRanked = boost::make_shared<EzText>( Localization::Words_NotRanked, ItemFont, 2000.f, true, true );
        MyPile->Add( NotRanked, L"NotRanked" );

        LoadingStr0 = Localization::WordString( Localization::Words_Loading );
        LoadingStr1 = Localization::WordString( Localization::Words_Loading ) + L".";
        LoadingStr2 = Localization::WordString( Localization::Words_Loading ) + L"..";
        LoadingStr3 = Localization::WordString( Localization::Words_Loading ) + L"...";
        LoadingCount = 0;

        LoadingText = boost::make_shared<EzText>( LoadingStr1, ItemFont, 1000.f, true, true );
        MyPile->Add( LoadingText, L"Loading" );


        MyMenu = boost::make_shared<Menu>();
        MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

        // Buttons
        boost::shared_ptr<MenuItem> item;

        // View Gamer
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_ViewGamerCard, ItemFont ) ) );
        item->Name = L"ViewGamer";
        item->JiggleOnGo = false;
        AddItem( item );
if ( ButtonCheck::ControllerInUse )
{
        MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.f, std::wstring( L"Button_ViewGamer" ) ) );
        item->Selectable = false;
}
        item->setGo( Cast::ToItem( boost::make_shared<ViewGamerProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );
        MyMenu->OnA = Cast::ToMenu( boost::make_shared<ViewGamerProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) );

        // Switch View
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_FriendsScores, ItemFont ) ) );
        item->Name = L"SwitchView";
        item->JiggleOnGo = false;
        AddItem( item );
if ( ButtonCheck::ControllerInUse )
{
        MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getY(), 90.f, std::wstring( L"Button_SwitchView" ) ) );
        item->Selectable = false;
}
        item->setGo( Cast::ToItem( boost::make_shared<SwitchViewProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );
        MyMenu->OnY = boost::make_shared<SwitchViewProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) );

        // Switch Sort
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_SortByScore, ItemFont ) ) );
        item->Name = L"SwitchSort";
        item->JiggleOnGo = false;
        AddItem( item );
if ( ButtonCheck::ControllerInUse )
{
        MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.f, std::wstring( L"Button_SwitchSort" ) ) );
        item->Selectable = false;
}
        item->setGo( Cast::ToItem( boost::make_shared<SwitchSortProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );
        MyMenu->OnX = Cast::ToMenu( boost::make_shared<SwitchSortProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) );

        // Back
if ( ButtonCheck::ControllerInUse )
{
        MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 90.f, std::wstring( L"Button_Back" ) ) );
        MyPile->Add( boost::make_shared<QuadClass>( std::wstring( L"BackArrow2" ), std::wstring( L"BackArrow" ) ) );
        item->Selectable = false;
}
        item->setGo( Cast::ToItem( boost::make_shared<SwitchSortProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );

        MyMenu->NoneSelected = true;

        EnsureFancy();
        SetPos();

        UpdateMessages();
    }

    void LeaderboardGUI::UpdateLoadingText()
    {
            
		if ( CurrentMessage == Message_Loading )
        {

            LoadingText->Show = true;

            LoadingCount++;

            int Delay = 12;
            int Total = 70;
            if      ( LoadingCount % Total == 0 )			  LoadingText->SubstituteText( LoadingStr0 );
            else if ( LoadingCount % Total == 1 * Delay + 4 ) LoadingText->SubstituteText( LoadingStr1 );
            else if ( LoadingCount % Total == 2 * Delay + 4 ) LoadingText->SubstituteText( LoadingStr2 );
            else if ( LoadingCount % Total == 3 * Delay + 4 ) LoadingText->SubstituteText( LoadingStr3 );

            LoadingText->setScale( 0.351667f * CoreMath::Periodic( 1.f, 1.1f, 2.f * Total, LoadingCount + 2.f ) );
        }
        else
        {
            LoadingText->Show = false;

            LoadingCount = 0;
        }
    }

    void LeaderboardGUI::UpdateMessages()
    {
        if ( CurrentView == 0 )
        {
            CurrentMessage = Message_Loading;
        }
        else
        {
            if ( CurrentView->Loading )
                CurrentMessage = Message_Loading;
            else if ( CurrentView->TotalEntries == 0 )
            {
                if ( CurrentType == LeaderboardType_FriendsScores )
                    CurrentMessage = Message_NotRankedFriends;
                else
                    CurrentMessage = Message_NotRanked;
            }
        }

        UpdateLoadingText();

        NotRanked->Show        = CurrentMessage == Message_NotRanked;
        NotRankedFriends->Show = CurrentMessage == Message_NotRankedFriends;
    }

    void LeaderboardGUI::ViewGamer()
    {
    }

    LeaderboardGUI::LeaderboardType LeaderboardGUI::Incr( LeaderboardType type )
    {
        return ( LeaderboardType )(((( int )type + 1 ) + ( int )LeaderboardType_Length ) % ( int )LeaderboardType_Length );
    }

    LeaderboardGUI::LeaderboardSortType LeaderboardGUI::Incr( LeaderboardSortType type )
    {
        return ( LeaderboardSortType )(((( int )type + 1 ) + ( int )LeaderboardSortType_Length ) % ( int )LeaderboardSortType_Length );
    }

    void LeaderboardGUI::SwitchView()
    {
        CurrentType = Incr( CurrentType );
        UpdateView();
    }

    void LeaderboardGUI::SwitchSort()
    {
        CurrentSort = Incr( CurrentSort );
        UpdateView();
    }

    void LeaderboardGUI::UpdateView()
    {
        MyMenu->FindItemByName( L"SwitchView" )->MyText->SubstituteText( LeaderboardType_ToString( Incr( CurrentType )));
		MyMenu->FindItemByName( L"SwitchView" )->MySelectedText->SubstituteText( LeaderboardType_ToString( Incr( CurrentType )));
        MyPile->FindEzText( L"Header" )->SubstituteText( LeaderboardType_ToString( CurrentType ));
        MyMenu->FindItemByName( L"SwitchSort" )->MyText->SubstituteText( LeaderboardSortType_ToString( Incr( CurrentSort )));
		MyMenu->FindItemByName( L"SwitchSort" )->MySelectedText->SubstituteText( LeaderboardSortType_ToString( Incr( CurrentSort )));
    }

    void LeaderboardGUI::SetIndex( int index )
    {
        LeaderboardInex = index;
        CurrentChallenge = ArcadeMenu::LeaderboardList[index].first;
        Hero = ArcadeMenu::LeaderboardList[index].second;

        CurrentView = boost::make_shared<LeaderboardView>();

        std::wstring Name;
        if ( CurrentChallenge == 0 )
        {
            Name = Localization::WordString( Localization::Words_TotalArcade );
        }
        else
        {
            if ( Hero == 0 )
                Name = Localization::WordString( CurrentChallenge->Name );
            else
                Name = Localization::WordString( CurrentChallenge->Name ) + L", " + Localization::WordString( Hero->Name );
        }

        MyPile->FindEzText( L"GameTitle" )->SubstituteText( Name );
    }

    void LeaderboardGUI::ChangeLeaderboard( int Direction )
    {
        int index = ( LeaderboardInex + Direction + ArcadeMenu::LeaderboardList.size() ) % ArcadeMenu::LeaderboardList.size();
        SetIndex( index );
    }

    void LeaderboardGUI::SetItemProperties( boost::shared_ptr<MenuItem> item )
    {
        StartMenu::SetItemProperties_Red( item );
        //CkBaseMenu::SetItemProperties( item );
    }

    void LeaderboardGUI::SetTextProperties( boost::shared_ptr<EzText> text )
    {
        CkBaseMenu::SetTextProperties( text );
    }

    void LeaderboardGUI::SetSelectedTextProperties( boost::shared_ptr<EzText> text )
    {
        CkBaseMenu::SetSelectedTextProperties( text );
    }

    void LeaderboardGUI::OnAdd()
    {
        CkBaseMenu::OnAdd();
    }

    void LeaderboardGUI::Release()
    {
        LoadingText->Release();
        NotRanked->Release();
        NotRankedFriends->Release();

        TL->Release();
        Offset_GamerTag->Release();
        Offset_Val->Release();
        ItemShift->Release();
        Highlight->Release();

        CkBaseMenu::Release();
    }

    boost::shared_ptr<QuadClass> LeaderboardGUI::TL, LeaderboardGUI::Offset_GamerTag, LeaderboardGUI::Offset_Val, LeaderboardGUI::ItemShift;
	boost::shared_ptr<HsvQuad> LeaderboardGUI::Highlight;

    void LeaderboardGUI::MyPhsxStep()
    {
        CkBaseMenu::MyPhsxStep();

        // Get direction input
        Vector2 Dir = Vector2(0);
        if ( getControl() < 0 )
        {
            Dir = ButtonCheck::GetMaxDir( getControl() == -1 );
        }
        else
            Dir = ButtonCheck::GetDir( getControl() );

        if ( DelayCount_LeftRight > 0 )
            DelayCount_LeftRight--;

        if ( Dir.Length() < .2f )
            DelayCount_LeftRight = 0;

        // Left and right
        if ( ButtonCheck::State( ControllerButtons_LS, getControl() ).Pressed )
        {
            ChangeLeaderboard(-1 );
            MotionCount_LeftRight = 0;
        }
        else if ( ButtonCheck::State( ControllerButtons_RS, getControl() ).Pressed )
        {
            ChangeLeaderboard( 1 );
            MotionCount_LeftRight = 0;
        }
        else if ( fabs( Dir.X ) > .75f )//ButtonCheck::ThresholdSensitivity )
        {
            MotionCount_LeftRight++;
            if ( DelayCount_LeftRight <= 0 )
            {
                DelayCount_LeftRight = SelectDelay - 5;
                if ( MotionCount_LeftRight > 1 * SelectDelay ) DelayCount_LeftRight -= 4;
                if ( MotionCount_LeftRight > 2 * SelectDelay ) DelayCount_LeftRight -= 3;

                if ( Dir.X > 0 ) ChangeLeaderboard( 1 );
                else ChangeLeaderboard(-1 );
            }
        }
        else
            MotionCount_LeftRight = 0;

        CurrentView->PhsxStep( getControl() );
    }

    void LeaderboardGUI::MyDraw()
    {
        CkBaseMenu::MyDraw();

        UpdateMessages();
            
        if ( CurrentMessage == Message_None )
            CurrentView->Draw( TL->getPos() + Pos->AbsVal, MasterAlpha );
    }

    void LeaderboardGUI::SetPos()
      {
if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-905.2225f, 171.1112f ) ); _item->MyText->setScale( 0.3724168f ); _item->MySelectedText->setScale( 0.3724168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-899.6663f, 23.33566f ) ); _item->MyText->setScale( 0.399f ); _item->MySelectedText->setScale( 0.399f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-896.8889f, -127.2176f ) ); _item->MyText->setScale( 0.3931669f ); _item->MySelectedText->setScale( 0.3931669f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
			_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
			_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3517378f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
			_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
			_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, -921.1119f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
			_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
			_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 5697.219f, -580.5558f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
			_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 630.5551f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchSort" ); if (_q != 0 ) { _q->setPos( Vector2( 711.1107f, 477.7777f ) ); _q->setSize( Vector2( 66.83328f, 66.83328f ) ); }
			_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
			_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

			MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-871.889f, 179.4445f ) ); _item->MyText->setScale( 0.3757501f ); _item->MySelectedText->setScale( 0.3757501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-882.9999f, 37.22455f ) ); _item->MyText->setScale( 0.4526668f ); _item->MySelectedText->setScale( 0.4526668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-880.2222f, -116.1065f ) ); _item->MyText->setScale( 0.4625835f ); _item->MySelectedText->setScale( 0.4625835f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
			_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
			_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3668901f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
			_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
			_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, -921.1119f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
			_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
			_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 5697.219f, -580.5558f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
			_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 630.5551f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchSort" ); if (_q != 0 ) { _q->setPos( Vector2( 711.1107f, 477.7777f ) ); _q->setSize( Vector2( 66.83328f, 66.83328f ) ); }
			_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
			_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

			MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-871.889f, 179.4445f ) ); _item->MyText->setScale( 0.3757501f ); _item->MySelectedText->setScale( 0.3757501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-882.9999f, 37.22455f ) ); _item->MyText->setScale( 0.4526668f ); _item->MySelectedText->setScale( 0.4526668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-880.2222f, -116.1065f ) ); _item->MyText->setScale( 0.4625835f ); _item->MySelectedText->setScale( 0.4625835f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
			_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
			_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3668901f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
			_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
			_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, -921.1119f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
			_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
			_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 5697.219f, -580.5558f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
			_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 630.5551f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchSort" ); if (_q != 0 ) { _q->setPos( Vector2( 711.1107f, 477.7777f ) ); _q->setSize( Vector2( 66.83328f, 66.83328f ) ); }
			_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
			_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

			MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-874.6669f, 190.5556f ) ); _item->MyText->setScale( 0.4565834f ); _item->MySelectedText->setScale( 0.4565834f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }
			_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-877.4445f, 28.89122f ) ); _item->MyText->setScale( 0.45625f ); _item->MySelectedText->setScale( 0.45625f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }
			_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-869.1111f, -127.2176f ) ); _item->MyText->setScale( 0.43025f ); _item->MySelectedText->setScale( 0.43025f ); _item->SelectIconOffset = Vector2( 0.f, 0.f );  }

			MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
			_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
			_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3609182f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
			_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
			_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, -921.1119f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
			_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
			_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 5697.219f, -580.5558f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
			_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 630.5551f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchSort" ); if (_q != 0 ) { _q->setPos( Vector2( 711.1107f, 477.7777f ) ); _q->setSize( Vector2( 66.83328f, 66.83328f ) ); }
			_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
			_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

			MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-874.6669f, 190.5556f ) ); _item->MyText->setScale( 0.4512501f ); _item->MySelectedText->setScale( 0.4512501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-880.2222f, 37.22455f ) ); _item->MyText->setScale( 0.5009168f ); _item->MySelectedText->setScale( 0.5009168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-874.6667f, -116.1065f ) ); _item->MyText->setScale( 0.5009168f ); _item->MySelectedText->setScale( 0.5009168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

			MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
			_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
			_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
			_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3843448f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
			_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
			_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, -921.1119f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
			_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
			_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 5697.219f, -580.5558f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
			_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
			_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 630.5551f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
			_q = MyPile->FindQuad( L"Button_SwitchSort" ); if (_q != 0 ) { _q->setPos( Vector2( 711.1107f, 477.7777f ) ); _q->setSize( Vector2( 66.83328f, 66.83328f ) ); }
			_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
			_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

			MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
		}






	void LeaderboardItem::StaticIntialize()
	{
		DefaultItem = boost::make_shared<LeaderboardItem>( 0, 0, 0 );
	}


    boost::shared_ptr<LeaderboardItem> LeaderboardItem::DefaultItem;

    LeaderboardItem::LeaderboardItem( boost::shared_ptr<Gamer> Player, int Val, int Rank )
    {
        this->Player = Player;
        this->Rank = ToString( Rank );

        if ( Player == 0 )
        {
            this->GamerTag = Localization::WordString( Localization::Words_Loading ) + L"...";
            this->Val = L"...";
        }
        else
        {
            this->GamerTag = Player->Gamertag;
            this->Val = ToString( Val );
        }
    }

    void LeaderboardItem::Draw( Vector2 Pos, bool Selected, float alpha )
    {
        Vector4 color = ColorHelper::Gray(.9f );
        Vector4 ocolor = Color::Black.ToVector4();

        if ( Selected )
        {
            //ocolor = Color( 191, 191, 191 ).ToVector4();
            //color = Color( 175, 8, 64 ).ToVector4();

            color = Color::LimeGreen.ToVector4();
            ocolor = bColor( 0, 0, 0 ).ToVector4();
        }
            
        color *= alpha;

        Vector2 GamerTag_Offset = .1f * Vector2( LeaderboardGUI::Offset_GamerTag->getPos().X, 0 );
        Vector2 Val_Offset = .1f * Vector2( LeaderboardGUI::Offset_Val->getPos().X, 0 );
        Vector2 Size = .1f * Vector2( LeaderboardGUI::ItemShift->getSizeX() );

        if ( Selected )
        {
            Tools::QDrawer->DrawString( Resources::Font_Grobold42->HOutlineFont, Rank, Pos, ocolor, Size );
            Tools::QDrawer->DrawString( Resources::Font_Grobold42->HOutlineFont, GamerTag, Pos + GamerTag_Offset, ocolor, Size );
            Tools::QDrawer->DrawString( Resources::Font_Grobold42->HOutlineFont, Val, Pos + Val_Offset, ocolor, Size );
        }

        Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, Rank, Pos, color, Size );
        Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, GamerTag, Pos + GamerTag_Offset, color, Size );
        Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, Val, Pos + Val_Offset, color, Size );
    }








    const int EntriesPerPage = 19;
    int TotalEntries;

    bool Loading;

    int Index;
    int Start;
    int End() { return CoreMath::RestrictVal( 0, TotalEntries, Start + EntriesPerPage ); }

    std::map<int, LeaderboardItem> Items;

    LeaderboardView::LeaderboardView()
    {
        TotalEntries = 0;// 1000000;
        Index = 0;
        Start = 0;

        Loading = true;

        LeaderboardItem::DefaultItem = boost::make_shared<LeaderboardItem>( 0, 0, 0 );

        Items = std::map<int, boost::shared_ptr<LeaderboardItem> >();
    }

    void LeaderboardView::IncrIndex( int change )
    {
        Index = CoreMath::RestrictVal( 0, TotalEntries - 1, Index + change );

        UpdateBounds();
    }

    void LeaderboardView::UpdateBounds()
    {
        if ( Index >= End())
            Start = Index - EntriesPerPage + 1;
        if ( Index < Start )
            Start = Index;
    }

    int DelayCount_UpDown, MotionCount_UpDown;
    const int SelectDelay = 11;
    void LeaderboardView::PhsxStep( int Control )
    {
        // Get direction input
        Vector2 Dir = Vector2(0);
        if ( Control < 0 )
        {
            Dir = ButtonCheck::GetMaxDir( Control == -1 );
        }
        else
            Dir = ButtonCheck::GetDir( Control );

        // Up and down
        if ( DelayCount_UpDown > 0 )
            DelayCount_UpDown--;

        if ( Dir.Length() < .2f && !ButtonCheck::State( ControllerButtons_LT, Control ).Down && !ButtonCheck::State( ControllerButtons_RT, Control ).Down )
            DelayCount_UpDown = 0;

        int IncrMultiplier = 1;
        if ( MotionCount_UpDown > SelectDelay * 5 ) IncrMultiplier = 2 + ( MotionCount_UpDown - SelectDelay * 5 ) / SelectDelay;

        if ( ButtonCheck::State( ControllerButtons_LT, Control ).Down || ButtonCheck::State( ControllerButtons_RT, Control ).Down )
        {
            int Incr = EntriesPerPage;

            MotionCount_UpDown++;
            if ( DelayCount_UpDown <= 0 )
            {
                if ( ButtonCheck::State( ControllerButtons_LT, Control ).Down )
                    IncrIndex(-Incr * IncrMultiplier );
                else
                    IncrIndex( Incr * IncrMultiplier );

                DelayCount_UpDown = SelectDelay;

                if ( MotionCount_UpDown > SelectDelay * 1 ) DelayCount_UpDown -= 8;
                if ( MotionCount_UpDown > SelectDelay * 3 ) DelayCount_UpDown -= 4;
            }
        }
        else if ( fabs( Dir.Y ) > ButtonCheck::ThresholdSensitivity )
        {
            MotionCount_UpDown++;
            if ( DelayCount_UpDown <= 0 )
            {
                int Incr = IncrMultiplier;

                if ( Dir.Y > 0 ) IncrIndex(-Incr );
                else IncrIndex( Incr );

                DelayCount_UpDown = SelectDelay;
                if ( MotionCount_UpDown > SelectDelay * 1 ) DelayCount_UpDown -= 8;
                if ( MotionCount_UpDown > SelectDelay * 3 ) DelayCount_UpDown -= 4;
                if ( MotionCount_UpDown > SelectDelay * 4 ) DelayCount_UpDown -= 4;
                if ( MotionCount_UpDown > SelectDelay * 5 ) DelayCount_UpDown -= 4;
                if ( MotionCount_UpDown > SelectDelay * 6 ) DelayCount_UpDown -= 4;
            }
        }
        else
            MotionCount_UpDown = 0;
    }

    void LeaderboardView::Draw( Vector2 Pos, float alpha )
    {
        //int Start = Index;
        //int End = Math->Min( TotalEntries - 1, Start + EntriesPerPage );

        Vector2 CurPos = Pos;
        float Shift = .1f * LeaderboardGUI::ItemShift->getX();

        for ( int i = Start; i < End(); i++)
        {
            bool Selected = i == Index;

            if ( Selected )
            {
                LeaderboardGUI::Highlight->setPosY( CurPos.Y - 70 );
                LeaderboardGUI::Highlight->Show = true;
                LeaderboardGUI::Highlight->Draw();
                LeaderboardGUI::Highlight->Show = false;
            }

            if ( Contains( Items, i ) )
            {
                Items[ i ]->Draw( CurPos, Selected, alpha );
            }
            else
            {
                boost::shared_ptr<LeaderboardItem> Default = LeaderboardItem::DefaultItem;
                Default->Rank = ToString( i );

                Default->Draw( CurPos, Selected, alpha );
            }

            CurPos.Y += Shift;
        }
    }

}