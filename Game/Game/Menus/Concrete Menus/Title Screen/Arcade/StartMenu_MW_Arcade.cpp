#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Arcade::StartMenu_MW_Arcade( const boost::shared_ptr<TitleGameData_MW> &Title ) : ArcadeMenu() { }
	boost::shared_ptr<StartMenu_MW_Arcade> StartMenu_MW_Arcade::StartMenu_MW_Arcade_Construct( const boost::shared_ptr<TitleGameData_MW> &Title )
	{
		ArcadeMenu::ArcadeMenu_Construct();

		this->Title = Title;

		return boost::static_pointer_cast<StartMenu_MW_Arcade>( shared_from_this() );
	}

	void StartMenu_MW_Arcade::SlideIn( int Frames )
	{
		Title->BackPanel->SetState( StartMenu_MW_Backpanel::State_SCENE_KOBBLER );
		ArcadeMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Arcade::SlideOut( PresetPos Preset, int Frames )
	{
		ArcadeMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Arcade::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		ArcadeMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;

		StartMenu::SetItemProperties_Green( item, false );

		item->MySelectedText->setScale( 1 );
	item->MyText->setScale( item->MySelectedText->getScale() );
	}

	void StartMenu_MW_Arcade::Go( const boost::shared_ptr<MenuItem> &item )
	{
		MyArcadeItem = boost::dynamic_pointer_cast<ArcadeItem>( item );
		if ( MyArcadeItem->IsLocked() )
			return;

		if ( MyArcadeItem->MyChallenge == Challenge_Escalation::getInstance() || MyArcadeItem->MyChallenge == Challenge_TimeCrisis::getInstance() )
		{
			GUI_Panel::Call( MakeMagic( StartMenu_MW_HeroSelect, ( Title, boost::static_pointer_cast<ArcadeMenu>( shared_from_this() ), MyArcadeItem ) ) );
		}
		else
		{
			Challenge::ChosenHero.reset();

            //int TopLevelForHero = MyArcadeItem.MyChallenge.TopLevel();
            int TopLevelForHero = MyArcadeItem->MyChallenge->CalcTopGameLevel( 0 );

			boost::shared_ptr<StartLevelMenu> levelmenu = MakeMagic( StartLevelMenu, ( TopLevelForHero ) );

			levelmenu->MyMenu->SelectItem( StartLevelMenu::PreviousMenuIndex );
			levelmenu->StartFunc = boost::make_shared<StartFuncProxy>( boost::static_pointer_cast<ArcadeBaseMenu>( shared_from_this() ) );
			levelmenu->ReturnFunc.reset();

			GUI_Panel::Call( levelmenu );
		}

		Hide();
	}

	void StartMenu_MW_Arcade::OnAdd()
	{
		ArcadeMenu::OnAdd();
	}

	void StartMenu_MW_Arcade::Init()
	{
		 ArcadeMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;
		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		SetPos();
	}

	void StartMenu_MW_Arcade::SetPos()
	{
        boost::shared_ptr<MenuItem> _item;
        _item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2771.113f, 901.9052f ) ); _item->MyText->setScale( 1.9f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
        _item = MyMenu->FindItemByName( L"Escalation" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2458.969f, 323.413f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
        _item = MyMenu->FindItemByName( L"Time Crisis" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2467.301f, 123.0817f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
        _item = MyMenu->FindItemByName( L"Hero Rush" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2456.189f, -88.36035f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
        _item = MyMenu->FindItemByName( L"Hero Rush 2" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2472.857f, -285.9135f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }

        MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2( 430.5557f, -686.1109f ) ); _t->setScale( 0.72f ); }
        _t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2( 1016.667f, -677.7777f ) ); _t->setScale( 0.9744995f ); }
        _t = MyPile->FindEzText( L"Requirement" ); if (_t != 0 ) { _t->setPos( Vector2( 55.55463f, 47.22229f ) ); _t->setScale( 0.8550834f ); }
        _t = MyPile->FindEzText( L"Requirement2" ); if (_t != 0 ) { _t->setPos( Vector2( 233.3332f, -169.4445f ) ); _t->setScale( 0.8706668f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2( 672.2224f, -219.4444f ) ); _q->setSize( Vector2( 302.8795f, 689.2195f ) ); }
        _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-290.4752f, -2200.793f ) ); _q->setSize( Vector2( 1234.721f, 740.8326f ) ); }

        MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
	}
}
