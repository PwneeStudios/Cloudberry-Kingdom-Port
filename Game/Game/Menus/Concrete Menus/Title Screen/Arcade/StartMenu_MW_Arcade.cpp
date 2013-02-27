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
		PlayerManager::UploadPlayerLevels();

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
		CloudberryKingdomGame::SetPresence( CloudberryKingdomGame::Presence_Arcade );

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
if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2667.914f, 913.8129f ) ); _item->MyText->setScale( 1.424767f ); _item->MySelectedText->setScale( 0.4747677f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Escalation" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2458.969f, 323.413f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Time Crisis" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2467.301f, 123.0817f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2456.189f, -88.36035f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush 2" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2472.857f, -285.9135f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }

			MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2( 75.00003f, -741.6663f ) ); _t->setScale( 0.72f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2( 1016.667f, -677.7777f ) ); _t->setScale( 0.9744995f ); }
			_t = MyPile->FindEzText( L"Requirement" ); if (_t != 0 ) { _t->setPos( Vector2( 412.7824f, 694.2017f ) ); _t->setScale( 0.6497964f ); }
			_t = MyPile->FindEzText( L"Requirement2" ); if (_t != 0 ) { _t->setPos( Vector2( 419.8857f, 501.3502f ) ); _t->setScale( 0.6259654f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2( 922.2821f, 467.227f ) ); _q->setSize( Vector2( 281.8031f, 680.5267f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-290.4752f, -2200.793f ) ); _q->setSize( Vector2( 1234.721f, 740.8326f ) ); }

			MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2771.113f, 901.9052f ) ); _item->MyText->setScale( 1.9f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Escalation" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2458.969f, 323.413f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Time Crisis" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2467.301f, 123.0817f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2456.189f, -88.36035f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush 2" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2472.857f, -285.9135f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }

			MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-540.2258f, -741.6663f ) ); _t->setScale( 0.72f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2( 1016.667f, -677.7777f ) ); _t->setScale( 0.9744995f ); }
			_t = MyPile->FindEzText( L"Requirement" ); if (_t != 0 ) { _t->setPos( Vector2( 345.3059f, 571.1564f ) ); _t->setScale( 0.6407465f ); }
			_t = MyPile->FindEzText( L"Requirement2" ); if (_t != 0 ) { _t->setPos( Vector2(-60.38756f, 402.1202f ) ); _t->setScale( 0.5885759f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2( 723.8219f, 367.997f ) ); _q->setSize( Vector2( 248.9382f, 824.8477f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-290.4752f, -2200.793f ) ); _q->setSize( Vector2( 1234.721f, 740.8326f ) ); }

			MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2771.113f, 901.9052f ) ); _item->MyText->setScale( 1.9f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Escalation" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2458.969f, 323.413f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Time Crisis" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2467.301f, 123.0817f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2456.189f, -88.36035f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush 2" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2472.857f, -285.9135f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }

			MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-294.1357f, -745.6355f ) ); _t->setScale( 0.72f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2( 1016.667f, -677.7777f ) ); _t->setScale( 0.9744995f ); }
			_t = MyPile->FindEzText( L"Requirement" ); if (_t != 0 ) { _t->setPos( Vector2( 432.6285f, 583.0642f ) ); _t->setScale( 0.7405323f ); }
			_t = MyPile->FindEzText( L"Requirement2" ); if (_t != 0 ) { _t->setPos( Vector2( 42.81172f, 378.305f ) ); _t->setScale( 0.606437f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2( 747.6375f, 356.0894f ) ); _q->setSize( Vector2( 274.7774f, 756.8558f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-290.4752f, -2200.793f ) ); _q->setSize( Vector2( 1234.721f, 740.8326f ) ); }

			MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2771.113f, 901.9052f ) ); _item->MyText->setScale( 1.9f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Escalation" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2458.969f, 323.413f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Time Crisis" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2467.301f, 123.0817f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2456.189f, -88.36035f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush 2" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2472.857f, -285.9135f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }

			MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2(-317.9504f, -737.6971f ) ); _t->setScale( 0.72f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2( 1016.667f, -677.7777f ) ); _t->setScale( 0.9744995f ); }
			_t = MyPile->FindEzText( L"Requirement" ); if (_t != 0 ) { _t->setPos( Vector2( 182.569f, 622.7562f ) ); _t->setScale( 0.8550834f ); }
			_t = MyPile->FindEzText( L"Requirement2" ); if (_t != 0 ) { _t->setPos( Vector2( 7.088623f, 354.4898f ) ); _t->setScale( 0.6387068f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2( 771.4524f, 340.2126f ) ); _q->setSize( Vector2( 305.541f, 787.8156f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-290.4752f, -2200.793f ) ); _q->setSize( Vector2( 1234.721f, 740.8326f ) ); }

			MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
}
else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2687.76f, 874.1208f ) ); _item->MyText->setScale( 1.644939f ); _item->MySelectedText->setScale( 0.694939f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
			_item = MyMenu->FindItemByName( L"Escalation" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2458.969f, 323.413f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Time Crisis" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2467.301f, 123.0817f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2456.189f, -88.36035f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush 2" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2472.857f, -285.9135f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }

			MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2( 51.18484f, -741.6663f ) ); _t->setScale( 0.72f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2( 1024.605f, -685.7161f ) ); _t->setScale( 0.9744995f ); }
			_t = MyPile->FindEzText( L"Requirement" ); if (_t != 0 ) { _t->setPos( Vector2( 269.8915f, 630.6946f ) ); _t->setScale( 0.6558692f ); }
			_t = MyPile->FindEzText( L"Requirement2" ); if (_t != 0 ) { _t->setPos( Vector2( 280.9633f, 437.843f ) ); _t->setScale( 0.5914334f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2( 823.0519f, 407.6891f ) ); _q->setSize( Vector2( 266.6555f, 639.9223f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-290.4752f, -2200.793f ) ); _q->setSize( Vector2( 1234.721f, 740.8326f ) ); }

			MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
}
else
{
			boost::shared_ptr<MenuItem> _item;
			_item = MyMenu->FindItemByName( L"Header" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2771.113f, 901.9052f ) ); _item->MyText->setScale( 1.697927f ); _item->MySelectedText->setScale( 0.7479278f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Escalation" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2458.969f, 323.413f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Time Crisis" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2467.301f, 123.0817f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2456.189f, -88.36035f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }
			_item = MyMenu->FindItemByName( L"Hero Rush 2" ); if (_item != 0 ) { _item->setSetPos( Vector2(-2472.857f, -285.9135f ) ); _item->MyText->setScale( 0.95f ); _item->MySelectedText->setScale( 0.95f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); _item->SetSelectedPos( Vector2(-2490.635f, -1.f )); }

			MyMenu->setPos( Vector2( 1070.889f, -45.5556f ) );

			boost::shared_ptr<EzText> _t;
			_t = MyPile->FindEzText( L"Level" ); if (_t != 0 ) { _t->setPos( Vector2( 75.00003f, -741.6663f ) ); _t->setScale( 0.72f ); }
			_t = MyPile->FindEzText( L"LevelNum" ); if (_t != 0 ) { _t->setPos( Vector2( 1016.667f, -677.7777f ) ); _t->setScale( 0.9744995f ); }
			_t = MyPile->FindEzText( L"Requirement" ); if (_t != 0 ) { _t->setPos( Vector2( 301.6447f, 7.530289f ) ); _t->setScale( 0.6619421f ); }
			_t = MyPile->FindEzText( L"Requirement2" ); if (_t != 0 ) { _t->setPos( Vector2( 86.4729f, -193.2597f ) ); _t->setScale( 0.6619265f ); }

			boost::shared_ptr<QuadClass> _q;
			_q = MyPile->FindQuad( L"BoxLeft" ); if (_q != 0 ) { _q->setPos( Vector2( 672.2224f, -219.4444f ) ); _q->setSize( Vector2( 290.9718f, 690.6484f ) ); }
			_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-290.4752f, -2200.793f ) ); _q->setSize( Vector2( 1234.721f, 740.8326f ) ); }

			MyPile->setPos( Vector2( 83.33417f, 130.9524f ) );
}
		}
}
