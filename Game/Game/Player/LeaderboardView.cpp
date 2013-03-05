#include <global_header.h>

#include <Hacks\List.h>

#include "LeaderboardView.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

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

    LeaderboardGUI::LeaderboardGUI( boost::shared_ptr<TitleGameData_MW> Title, int Control )
		: CkBaseMenu()
	{
	}
	boost::shared_ptr<LeaderboardGUI> LeaderboardGUI::LeaderboardGUI_Construct( boost::shared_ptr<TitleGameData_MW> Title, int Control )
    {
		CurrentType = static_cast<LeaderboardType>( 0 );
		CurrentSort = static_cast<LeaderboardSortType>( 0 );
		CurrentMessage = static_cast<Message>( 0 );

		LeaderboardInex = 0;

		DelayCount_LeftRight = MotionCount_LeftRight = 0;
		
		LoadingCount = 0;

        ToMake_Id = -1;
        DelayToMake = 0;


		CkBaseMenu::CkBaseMenu_Construct();

        ToMake_Id = -1;
        DelayToMake = 0;

        if (Leaderboard::LeaderboardFriends.size() == 0)
        {
            //Leaderboard::LeaderboardFriends.push_back(get all the friends);
        }

        this->setControl( Control );

        EnableBounce();

        CurrentType = LeaderboardType_TopScores;
        CurrentSort = LeaderboardSortType_Score;
        CurrentMessage = Message_None;

		SetIndex( Challenge::LeaderboardIndex );

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

        boost::shared_ptr<EzText> Header = boost::make_shared<EzText>( std::wstring( L"__Dummy__" ), ItemFont );
        MyPile->Add( Header, L"Header" );

        boost::shared_ptr<EzText> GameTitle = boost::make_shared<EzText>( L"__Dummy__", ItemFont );
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


        MyMenu = boost::make_shared<Menu>( false );
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
        MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.0f, std::wstring( L"Button_ViewGamer" ) ) );
        item->Selectable = false;
}
else
{
		item->setGo( Cast::ToItem( boost::make_shared<ViewGamerProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );
}
        MyMenu->OnA = Cast::ToMenu( boost::make_shared<ViewGamerProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) );

        // Switch View
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( L"__Dummy__", ItemFont ) ) );
        item->Name = L"SwitchView";
        item->JiggleOnGo = false;
        AddItem( item );
if ( ButtonCheck::ControllerInUse )
{
        MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.0f, std::wstring( L"Button_SwitchView" ) ) );
        item->Selectable = false;
}
        item->setGo( Cast::ToItem( boost::make_shared<SwitchViewProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );
        MyMenu->OnX = Cast::ToMenu( boost::make_shared<SwitchViewProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) );

        // Switch Sort
		bool ShowSortOption = false;
        item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( L"__Dummy__", ItemFont ) ) );
        item->Name = L"SwitchSort";
        item->JiggleOnGo = false;
        AddItem( item );
if ( ButtonCheck::ControllerInUse )
{
		if (ShowSortOption)
		{
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.0f, std::wstring( L"Button_SwitchSort" ) ) );
		}
        item->Selectable = false;
}
        item->setGo( Cast::ToItem( boost::make_shared<SwitchViewProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );
        //MyMenu->OnX = Cast::ToMenu( boost::make_shared<SwitchSortProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) );
		if (!ShowSortOption)
		{
			item->Show = false; item->Selectable = false;
		}

		// Left/Right
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getLeftRight(), 90.0f, std::wstring( L"Button_LeftRight" ) ) );
		boost::shared_ptr<EzText> text = boost::make_shared<EzText>( Localization::WordString( Localization::Words_Previous) + L" / " +
											Localization::WordString( Localization::Words_Next), ItemFont );
		StartMenu::SetTextUnselected_Red( text );
		MyPile->Add( text, L"LeftRight" );

        // Back
if ( ButtonCheck::ControllerInUse )
{
        MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 90.0f, std::wstring( L"Button_Back" ) ) );
        MyPile->Add( boost::make_shared<QuadClass>( L"BackArrow2", L"BackArrow" ));
        item->Selectable = false;
}
        item->setGo( Cast::ToItem( boost::make_shared<SwitchSortProxy>( boost::static_pointer_cast<LeaderboardGUI>( shared_from_this() ) ) ) );

        MyMenu->NoneSelected = true;

        EnsureFancy();
        SetPos();

        UpdateMessages();

if ( ButtonCheck::ControllerInUse )
{
		MyMenu->NoneSelected = true;
}

		UpdateView();
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
                else if ( CurrentType == LeaderboardType_TopScores )
                    CurrentMessage = Message_NoOne;
                else
                    CurrentMessage = Message_NotRanked;
            }
            else
                CurrentMessage = Message_None;
        }

        UpdateLoadingText();

        NotRanked->Show        = CurrentMessage == Message_NotRanked;
        NotRankedFriends->Show = CurrentMessage == Message_NotRankedFriends;
    }

    void LeaderboardGUI::ViewGamer()
    {
		CurrentView->ViewGamer();
    }

    LeaderboardType LeaderboardGUI::Incr( LeaderboardType type )
    {
        LeaderboardType lt = ( LeaderboardType )(((( int )type + 1 ) + ( int )LeaderboardType_Length ) % ( int )LeaderboardType_Length );

#if PS3
		if ( lt == LeaderboardType_MyScores )
			lt = Incr( lt );
#endif

		return lt;
    }

    LeaderboardSortType LeaderboardGUI::Incr( LeaderboardSortType type )
    {
        return ( LeaderboardSortType )(((( int )type + 1 ) + ( int )LeaderboardSortType_Length ) % ( int )LeaderboardSortType_Length );
    }

    void LeaderboardGUI::SwitchView()
    {
		if ( CurrentView != 0 && CurrentView->Loading ) return;

        CurrentType = Incr( CurrentType );
        UpdateView();

		CurrentView->SetType( CurrentType );
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

        std::wstring Name;
		int Id;
        if ( CurrentChallenge == 0 )
        {
            Name = Localization::WordString( Localization::Words_TotalArcade );
                
				Name = Localization::WordString( Localization::Words_PlayerLevel ) + L" (" +
                        Localization::WordString( Localization::Words_TheArcade ) + L" + " + Localization::WordString( Localization::Words_StoryMode ) + L")";
                Id = 9999;
        }
        else
        {
            if ( Hero == 0 )
			{
                Name = Localization::WordString( CurrentChallenge->Name );
				Id = CurrentChallenge->GameId_Level;
			}
            else
			{
                Name = Localization::WordString( CurrentChallenge->Name ) + L", " + Localization::WordString( Hero->Name );
				Id = CurrentChallenge->CalcGameId_Level( Hero );
			}
        }

        MyPile->FindEzText( L"GameTitle" )->SubstituteText( Name );

        if ( CurrentView == 0 )
            CurrentView = boost::make_shared<LeaderboardView>( Id, CurrentType );
        else
            ToMake_Id = Id;
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

        if ( !Active || BubblingOut ) return;

        if ( !CloudberryKingdomGame::OnlineFunctionalityAvailable() )
        {
            ReturnToCaller();
            CloudberryKingdomGame::ShowError_MustBeSignedInToLive( Localization::Words_Err_MustBeSignedInToLive );
            return;
        }

        if (DelayToMake > 0)
        {
            DelayToMake--;
        }
        else if (ToMake_Id >= 0)
        {
            CurrentView = boost::make_shared<LeaderboardView>( ToMake_Id, CurrentType );
            ToMake_Id = -1;
            DelayToMake = 25;
        }

        // Get direction input
        Vector2 Dir = Vector2(0);
        if ( getControl() < 0 )
        {
            //Dir = ButtonCheck::GetMaxDir( getControl() == -1 );
			Dir = ButtonCheck::GetMaxDir( false );
        }
        else
            Dir = ButtonCheck::GetDir( getControl() );

        if ( DelayCount_LeftRight > 0 )
            DelayCount_LeftRight--;

        if ( Dir.Length() < .2f )
            DelayCount_LeftRight = 0;

        if ( fabs( Dir.X ) < .875f )
            Dir.X = 0;

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
        {
            // Zoom camera as needed for bounce effect
            Vector2 v = zoom->Update();
            MasterAlpha = v.X * v.X;

            MyGame->getCam()->setZoom( .001f * v );
            MyGame->getCam()->SetVertexCamera();

            // Draw the scores
            CurrentView->Draw( TL->getPos() + Pos->AbsVal, MasterAlpha );

            Tools::QDrawer->Flush();

            // Revert camera
            MyGame->getCam()->setZoom( Vector2( .001f ) );
            MyGame->getCam()->SetVertexCamera();
            EzText::ZoomWithCamera_Override = false;
        }
    }

    void LeaderboardGUI::SetPos()
    {
if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-885.7779f, 168.3334f ) ); _item->MyText->setScale( 0.3767501f ); _item->MySelectedText->setScale( 0.3767501f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-894.1109f, 17.78012f ) ); _item->MyText->setScale( 0.3958333f ); _item->MySelectedText->setScale( 0.3958333f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-902.4446f, -132.7731f ) ); _item->MyText->setScale( 0.3892502f ); _item->MySelectedText->setScale( 0.3892502f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
	_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
	_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3519495f ); }
	_t = MyPile->FindEzText( L"LeftRight" ); if (_t != 0 ) { _t->setPos( Vector2( 777.7778f, 549.9998f ) ); _t->setScale( 0.3982503f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
	_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
	_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, 643.8893f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
	_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
	_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 4820.f, -363.889f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
	_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 713.8889f, 777.7776f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
	_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 713.8892f, 622.2218f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
	_q = MyPile->FindQuad( L"Button_LeftRight" ); if (_q != 0 ) { _q->setPos( Vector2( 713.8888f, 480.5554f ) ); _q->setSize( Vector2( 73.74999f, 73.74999f ) ); }
	_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
	_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

	MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-888.5557f, 176.6667f ) ); _item->MyText->setScale( 0.3826668f ); _item->MySelectedText->setScale( 0.3826668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-877.4443f, 31.66899f ) ); _item->MyText->setScale( 0.4059168f ); _item->MySelectedText->setScale( 0.4059168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-880.2222f, -116.1065f ) ); _item->MyText->setScale( 0.4625835f ); _item->MySelectedText->setScale( 0.4625835f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
	_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1297.222f, 855.5557f ) ); _t->setScale( 0.3989167f ); }
	_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3519495f ); }
	_t = MyPile->FindEzText( L"LeftRight" ); if (_t != 0 ) { _t->setPos( Vector2( 797.2221f, 538.8887f ) ); _t->setScale( 0.3720834f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
	_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
	_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, 643.8893f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
	_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
	_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 4820.f, -363.889f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
	_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
	_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 630.5551f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
	_q = MyPile->FindQuad( L"Button_LeftRight" ); if (_q != 0 ) { _q->setPos( Vector2( 713.8888f, 480.5554f ) ); _q->setSize( Vector2( 73.74999f, 73.74999f ) ); }
	_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
	_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

	MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-885.7779f, 168.3334f ) ); _item->MyText->setScale( 0.3670001f ); _item->MySelectedText->setScale( 0.3670001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-882.9999f, 15.00238f ) ); _item->MyText->setScale( 0.3969168f ); _item->MySelectedText->setScale( 0.3969168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-880.2222f, -116.1065f ) ); _item->MyText->setScale( 0.4625835f ); _item->MySelectedText->setScale( 0.4625835f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1313.888f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
	_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
	_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3519495f ); }
	_t = MyPile->FindEzText( L"LeftRight" ); if (_t != 0 ) { _t->setPos( Vector2( 797.2221f, 538.8887f ) ); _t->setScale( 0.3897502f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
	_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
	_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, 643.8893f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
	_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
	_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 4820.f, -363.889f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
	_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 702.7778f, 777.7776f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
	_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 613.8885f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
	_q = MyPile->FindQuad( L"Button_LeftRight" ); if (_q != 0 ) { _q->setPos( Vector2( 708.3334f, 472.2221f ) ); _q->setSize( Vector2( 70.08331f, 70.08331f ) ); }
	_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
	_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

	MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-883.0004f, 171.1111f ) ); _item->MyText->setScale( 0.4280001f ); _item->MySelectedText->setScale( 0.4280001f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-874.6668f, 20.55785f ) ); _item->MyText->setScale( 0.4208333f ); _item->MySelectedText->setScale( 0.4208333f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-869.1111f, -127.2176f ) ); _item->MyText->setScale( 0.43025f ); _item->MySelectedText->setScale( 0.43025f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
	_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1291.667f, 861.1112f ) ); _t->setScale( 0.3976667f ); }
	_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3824919f ); }
	_t = MyPile->FindEzText( L"LeftRight" ); if (_t != 0 ) { _t->setPos( Vector2( 799.9999f, 555.5553f ) ); _t->setScale( 0.4340833f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
	_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
	_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, 643.8893f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
	_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
	_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 4820.f, -363.889f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
	_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
	_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 616.6663f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
	_q = MyPile->FindQuad( L"Button_LeftRight" ); if (_q != 0 ) { _q->setPos( Vector2( 713.8888f, 474.9998f ) ); _q->setSize( Vector2( 73.74999f, 73.74999f ) ); }
	_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
	_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

	MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
{
	boost::shared_ptr<MenuItem> _item;
	_item = MyMenu->FindItemByName( L"ViewGamer" ); if (_item != 0 ) { _item->setSetPos( Vector2(-908.0002f, 168.3334f ) ); _item->MyText->setScale( 0.3748334f ); _item->MySelectedText->setScale( 0.3748334f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchView" ); if (_item != 0 ) { _item->setSetPos( Vector2(-908.f, 17.78011f ) ); _item->MyText->setScale( 0.3670003f ); _item->MySelectedText->setScale( 0.3670003f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
	_item = MyMenu->FindItemByName( L"SwitchSort" ); if (_item != 0 ) { _item->setSetPos( Vector2(-874.6667f, -116.1065f ) ); _item->MyText->setScale( 0.5009168f ); _item->MySelectedText->setScale( 0.5009168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

	MyMenu->setPos( Vector2( 1672.222f, 686.1112f ) );

	boost::shared_ptr<EzText> _t;
	_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1308.333f, 991.6661f ) ); _t->setScale( 0.5240005f ); }
	_t = MyPile->FindEzText( L"GameTitle" ); if (_t != 0 ) { _t->setPos( Vector2(-1302.778f, 861.1112f ) ); _t->setScale( 0.4570001f ); }
	_t = MyPile->FindEzText( L"NotRankedFriends" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"NotRanked" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.4956669f ); }
	_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3519495f ); }
	_t = MyPile->FindEzText( L"LeftRight" ); if (_t != 0 ) { _t->setPos( Vector2( 769.4445f, 552.7775f ) ); _t->setScale( 0.3768338f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
	_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
	_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, 643.8893f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
	_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
	_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 4820.f, -363.889f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
	_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 688.8887f, 769.4443f ) ); _q->setSize( Vector2( 62.08334f, 62.08334f ) ); }
	_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 691.6668f, 622.2218f ) ); _q->setSize( Vector2( 61.74989f, 61.74989f ) ); }
	_q = MyPile->FindQuad( L"Button_LeftRight" ); if (_q != 0 ) { _q->setPos( Vector2( 699.9999f, 486.111f ) ); _q->setSize( Vector2( 66.74998f, 66.74998f ) ); }
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
	_t = MyPile->FindEzText( L"Loading" ); if (_t != 0 ) { _t->setPos( Vector2(-391.6667f, -16.66664f ) ); _t->setScale( 0.3519495f ); }
	_t = MyPile->FindEzText( L"LeftRight" ); if (_t != 0 ) { _t->setPos( Vector2( 797.2221f, 583.3331f ) ); _t->setScale( 0.5539168f ); }

	boost::shared_ptr<QuadClass> _q;
	_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2(-408.3335f, 2.777821f ) ); _q->setSize( Vector2( 1094.068f, 1006.303f ) ); }
	_q = MyPile->FindQuad( L"BoxRight" ); if (_q != 0 ) { _q->setPos( Vector2( 1266.665f, 519.4443f ) ); _q->setSize( Vector2( 418.2869f, 684.4695f ) ); }
	_q = MyPile->FindQuad( L"Highlight" ); if (_q != 0 ) { _q->setPos( Vector2(-413.8886f, 643.8893f ) ); _q->setSize( Vector2( 1005.093f, 49.08278f ) ); }
	_q = MyPile->FindQuad( L"TL" ); if (_q != 0 ) { _q->setPos( Vector2(-1300.001f, 713.8893f ) ); _q->setSize( Vector2( 0.9999986f, 0.9999986f ) ); }
	_q = MyPile->FindQuad( L"Offset_GamerTag" ); if (_q != 0 ) { _q->setPos( Vector2( 4820.f, -363.889f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset_Val" ); if (_q != 0 ) { _q->setPos( Vector2( 13808.34f, -116.6667f ) ); _q->setSize( Vector2( 1.f, 1.f ) ); }
	_q = MyPile->FindQuad( L"Offset" ); if (_q != 0 ) { _q->setPos( Vector2(-869.4451f, -383.3332f ) ); _q->setSize( Vector2( 10.08327f, 10.08327f ) ); }
	_q = MyPile->FindQuad( L"Button_ViewGamer" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5554f, 783.3331f ) ); _q->setSize( Vector2( 67.25001f, 67.25001f ) ); }
	_q = MyPile->FindQuad( L"Button_SwitchView" ); if (_q != 0 ) { _q->setPos( Vector2( 705.5557f, 630.5551f ) ); _q->setSize( Vector2( 65.16659f, 65.16659f ) ); }
	_q = MyPile->FindQuad( L"Button_LeftRight" ); if (_q != 0 ) { _q->setPos( Vector2( 713.8888f, 480.5554f ) ); _q->setSize( Vector2( 73.74999f, 73.74999f ) ); }
	_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2( 1536.111f, 227.7776f ) ); _q->setSize( Vector2( 67.99999f, 67.99999f ) ); }
	_q = MyPile->FindQuad( L"BackArrow" ); if (_q != 0 ) { _q->setPos( Vector2( 1369.444f, 216.6666f ) ); _q->setSize( Vector2( 77.71317f, 66.83332f ) ); }

	MyPile->setPos( Vector2( 0.f, 5.555542f ) );
}
    }














    const int EntriesPerPage = 18;
    int TotalEntries;

    bool Loading;

    int Index;
    int Start;
    int End() { return CoreMath::RestrictVal( 0, TotalEntries, Start + EntriesPerPage ); }

    std::map<int, LeaderboardItem> &LeaderboardView::getItems()
	{
		return MyLeaderboard->Items;
	}

    LeaderboardView::LeaderboardView( int Id, LeaderboardType CurrentType )
    {
        TotalEntries = 0;// 1000000;
        Index = 1;
        Start = 1;

        Loading = true;

        LeaderboardItem::DefaultItem = boost::make_shared<LeaderboardItem>( OnlineGamer(), 0, 0 );

        MyLeaderboard = boost::make_shared<Leaderboard>( Id );

        MyLeaderboard->SetType( CurrentType );
    }

    void LeaderboardView::IncrIndex( int change )
    {
        Index = CoreMath::RestrictVal( 1, TotalEntries, Index + change );

        UpdateBounds();
    }

    void LeaderboardView::UpdateBounds()
    {
        if ( Index >= End())
            //Start = Index - EntriesPerPage + 1;
			Start = Index - EntriesPerPage;
        if ( Index < Start )
            Start = Index;
		Start = CoreMath::RestrictVal( 1, TotalEntries, Start );
    }

    int DelayCount_UpDown, MotionCount_UpDown;
    const int SelectDelay = 11;
    void LeaderboardView::PhsxStep( int Control )
    {
        // Try reloading board again if we haven't gotten results yet.
        if ( Loading && MyLeaderboard != 0 && !MyLeaderboard->Updated )
        {
            MyLeaderboard->SetType( MyLeaderboard->MySortType );
        }

        // If the board has been updated then take information in
        if ( MyLeaderboard != 0 && MyLeaderboard->Updated )
        {
			// FIXME put a lock here
            //lock (Items)
			MyLeaderboard->ItemMutex.Lock();
            {
                if (Loading)
                {
                    Index = MyLeaderboard->StartIndex;
                    Start = Index - EntriesPerPage / 2 + 1;
                    //TotalEntries = MyLeaderboard->TotalSize;
                    UpdateBounds();
                }

				TotalEntries = MyLeaderboard->TotalSize;
                MyLeaderboard->Updated = false;
                Loading = false;
            }
			MyLeaderboard->ItemMutex.Unlock();
        }

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

        void LeaderboardView::ViewGamer()
        {
			// FIXME
            //lock (Items)
			MyLeaderboard->ItemMutex.Lock();
            {
                if ( getItems().size() > 0)
                {
                    if ( Contains( getItems(), Index ) )
                    {
                        OnlineGamer gamer = getItems()[Index].Player;
                        if ( gamer.Id > 0 && MenuItem::ActivatingPlayer >= 0 && MenuItem::ActivatingPlayer <= 3 ) 
                        {
							// Show the gamer card!
#if XBOX
                            CloudberryKingdomGame.ShowGamerCard((PlayerIndex)MenuItem::ActivatingPlayer, gamer);
#endif
                        }
                    }
                }
            }
			MyLeaderboard->ItemMutex.Unlock();
        }

        void LeaderboardView::SetType( LeaderboardType type )
        {
            if (type == LeaderboardType_FriendsScores && MyLeaderboard->FriendItems.size() > 0)
            {
                Loading = false;
                Start = Index = 1;
                TotalEntries = MyLeaderboard->FriendItems.size();
                UpdateBounds();
            }
            else
            {
                Loading = true;
            }

            MyLeaderboard->SetType( type );
        }

    void LeaderboardView::Draw( Vector2 Pos, float alpha )
    {
		// FIXME
        //lock (Items)
		MyLeaderboard->ItemMutex.Lock();
        {
            Vector2 CurPos = Pos;
            float Shift = .1f * LeaderboardGUI::ItemShift->getX();

            if ( MyLeaderboard == 0 ) return;

            if ( MyLeaderboard->MySortType == LeaderboardType_FriendsScores )
            {
                DrawList( alpha, CurPos, Shift );
            }
            else
            {
                DrawDict( alpha, CurPos, Shift );
            }
        }
		MyLeaderboard->ItemMutex.Unlock();
    }

	void LeaderboardView::DrawList( float alpha, Vector2 CurPos, float Shift )
    {
        bool RequestMore = false;
        int MinExisting = Start, MaxExisting = Start, MinMissing = -1, MaxMissing = -1;

        for ( int i = Start; i <= End(); i++)
        {
            bool Selected = i == Index;

            if ( Selected )
            {
                LeaderboardGUI::Highlight->setPosY( CurPos.Y - 70 );
                LeaderboardGUI::Highlight->Show = true;
                LeaderboardGUI::Highlight->Draw();
                LeaderboardGUI::Highlight->Show = false;
            }

            if ( i - 1 < static_cast<int>( MyLeaderboard->FriendItems.size() ) )
            {
				MyLeaderboard->FriendItems[ i - 1 ].Draw( CurPos, Selected, alpha,
					LeaderboardGUI::Offset_GamerTag->getPos().X,
					LeaderboardGUI::Offset_Val->getPos().X,
					LeaderboardGUI::ItemShift->getSizeX() );
            }

            CurPos.Y += Shift;
        }
    }

    void LeaderboardView::DrawDict(float alpha, Vector2 CurPos, float Shift)
    {
        bool RequestMore = false;
        int MinExisting = Start, MaxExisting = Start, MinMissing = -1, MaxMissing = -1;

        for ( int i = Start; i <= End(); i++ )
        {
            bool Selected = i == Index;

            if ( Selected )
            {
                LeaderboardGUI::Highlight->setPosY( CurPos.Y - 70 );
                LeaderboardGUI::Highlight->Show = true;
                LeaderboardGUI::Highlight->Draw();
                LeaderboardGUI::Highlight->Show = false;
            }

            if ( Contains( getItems(), i ) )
            {
                getItems()[ i ].Draw( CurPos, Selected, alpha,
					LeaderboardGUI::Offset_GamerTag->getPos().X,
					LeaderboardGUI::Offset_Val->getPos().X,
					LeaderboardGUI::ItemShift->getSizeX() );

                MaxExisting = __max( MaxExisting, i );
                MinExisting = __min( MinExisting, i );
            }
            else
            {
                RequestMore = true;

                MaxMissing = MaxMissing == -1 ? i : __max( MaxMissing, i );
                MinMissing = MinMissing == -1 ? i : __min( MinMissing, i );

                boost::shared_ptr<LeaderboardItem> Default = LeaderboardItem::DefaultItem;
                Default->Rank = ToString( i );

                Default->Draw( CurPos, Selected, alpha,
					LeaderboardGUI::Offset_GamerTag->getPos().X,
					LeaderboardGUI::Offset_Val->getPos().X,
					LeaderboardGUI::ItemShift->getSizeX() );
            }

            CurPos.Y += Shift;
        }

        if ( RequestMore )
        {
            int PageToRequest;

            if ( MinMissing >= MaxExisting )
            {
                PageToRequest = CoreMath::RestrictVal( 1, TotalEntries, MinMissing );
            }
            else
            {
                PageToRequest = CoreMath::RestrictVal( 1, TotalEntries, MaxMissing );
            }

            MyLeaderboard->RequestMore( PageToRequest );
        }
    }

}