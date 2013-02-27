#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include <MasterHack.h>

namespace CloudberryKingdom
{

	StartMenu::StartMenuLambda_Campaign::StartMenuLambda_Campaign( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Campaign::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Campaign( item );
	}

	StartMenu::StartMenuLambda_Arcade::StartMenuLambda_Arcade( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Arcade::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Arcade( item );
	}

	StartMenu::StartMenuLambda_Freeplay::StartMenuLambda_Freeplay( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Freeplay::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Freeplay( item );
	}

	StartMenu::CharacterSelectProxy::CharacterSelectProxy( const boost::shared_ptr<StartMenu> &startMenu )
	{
		this->startMenu = startMenu;
	}

	void StartMenu::CharacterSelectProxy::Apply()
	{
		startMenu->CharacterSelect();
	}

	StartMenu::MenuGo_ScreenSaverHelper::MenuGo_ScreenSaverHelper( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::MenuGo_ScreenSaverHelper::Apply()
	{
		sm->MyGame->Release();
	}

	StartMenu::StartMenuLambda_Controls::StartMenuLambda_Controls( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Controls::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Controls( item );
	}

	StartMenu::StartMenuLambda_Options::StartMenuLambda_Options( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Options::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Options( item );
	}

	StartMenu::StartMenuLambda_Exit::StartMenuLambda_Exit( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::StartMenuLambda_Exit::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sm->MenuGo_Exit( item );
	}

	StartMenu::StartMenuExitLambda::StartMenuExitLambda( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	bool StartMenu::StartMenuExitLambda::Apply( const boost::shared_ptr<Menu> &menu )
	{
		sm->Exit();
		return false;
	}

	StartMenu::DoneWithCharSelectProxy::DoneWithCharSelectProxy( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::DoneWithCharSelectProxy::Apply()
	{
		sm->DoneWithCharSelect();
	}

	StartMenu::BringNextMenuLambda::BringNextMenuLambda( const boost::shared_ptr<StartMenu> &sm )
	{
		this->sm = sm;
	}

	void StartMenu::BringNextMenuLambda::Apply()
	{
		sm->BringNextMenu();
	}

	void StartMenu::Hide( PresetPos pos, int frames )
	{
		CkBaseMenu::Hide( pos, frames );
		ButtonCheck::PreLogIn = false;
	}

	void StartMenu::MenuGo_Campaign( const boost::shared_ptr<MenuItem> &item )
	{
		//if (CloudberryKingdomGame::getIsDemo()) return;

		MyNextMenu = Next_CAMPAIGN;
		BringCharacterSelect();
	}

	void StartMenu::MenuGo_Arcade( const boost::shared_ptr<MenuItem> &item )
	{
		MyNextMenu = Next_ARCADE;
		BringCharacterSelect();
		//DoneWithCharSelect();StartMenu_MW_HeroSelect
	}

	void StartMenu::MenuGo_Freeplay( const boost::shared_ptr<MenuItem> &item )
	{
		MyNextMenu = Next_FREEPLAY;
		BringCharacterSelect();
		//DoneWithCharSelect();
	}

	void StartMenu::BringCharacterSelect()
	{
		UseBounce = false;
		ReturnToCallerDelay = 0;

		NoBack = true;
		MyGame->SlideOut_FadeIn( 20, boost::make_shared<CharacterSelectProxy>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
	}

	void StartMenu::Show()
	{
		NoBack = false;
		CkBaseMenu::Show();
	}

	void StartMenu::ReturnToCaller()
	{
		CkBaseMenu::ReturnToCaller();
	}

	void StartMenu::CharacterSelect()
	{
		GUI_Panel::Hide();
		CharacterSelectManager::Start( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ), false );
		CharacterSelectManager::OnDone = boost::make_shared<DoneWithCharSelectProxy>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) );
		CharacterSelectManager::OnBack.reset();
	}

	void StartMenu::MenuGo_ScreenSaver( const boost::shared_ptr<MenuItem> &item )
	{
		boost::shared_ptr<ScreenSaver> Intro = boost::make_shared<ScreenSaver>();
		ScreenSaver_Construct( Intro );
		Intro->Init();
		Tools::TheGame->LogoScreenPropUp = false;
		Tools::AddToDo( boost::make_shared<MenuGo_ScreenSaverHelper>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
	}

	void StartMenu::MenuGo_Controls( const boost::shared_ptr<MenuItem> &item )
	{
		Call( MakeMagic( ControlScreen, ( getControl() ) ), 0 );
	}

	void StartMenu::MenuGo_Stats( const boost::shared_ptr<MenuItem> &item )
	{
		Call( MakeMagic( StatsMenu, ( StatGroup_LIFETIME ) ), 0 );
	}

	void StartMenu::MenuGo_Options( const boost::shared_ptr<MenuItem> &item )
	{
		Call( MakeMagic( SoundMenu, ( getControl(), false ) ), 0 );
	}

	void StartMenu::MenuGo_Exit( const boost::shared_ptr<MenuItem> &item )
	{
		Exit();
	}

	void StartMenu::Exit()
	{
		SelectSound.reset();
		Call( MakeMagic( VerifyQuitGameMenu2, ( getControl() ) ), 0 );
	}

	StartMenu::StartMenu() :
		NoBack( false ),
		MyNextMenu( static_cast<Next>( 0 ) )
	{
	}
	boost::shared_ptr<StartMenu> StartMenu::StartMenu_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		if ( Tools::TheGame->LoadingScreen_Renamed != 0 )
			Tools::TheGame->LoadingScreen_Renamed->IsDone = true;

		return boost::static_pointer_cast<StartMenu>( shared_from_this() );
	}

	void StartMenu::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( Frames );
		//base.SlideIn(0);
		//return;

		//if (SlideOnReturn)
		//    base.SlideIn(Frames);
		//else
		//{
		//    base.SlideIn(0);

		//    MyPile.BubbleUp(true, 8, 1);
		//    MyMenu.FancyPos.LerpTo(MenuPos_Down, MenuPos, 40);
		//}

		//SlideOnReturn = false;
	}

	void StartMenu::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );
		SetItemProperties_Red( item );
	}

	void StartMenu::SetText_Green( const boost::shared_ptr<EzText> &text, bool outline )
	{
		if ( text == 0 )
			return;

		text->OutlineColor = ( bColor( 0, 0, 0, outline ? 255 : 0 ) ).ToVector4();
		text->MyFloatColor = ( bColor( 34, 214, 47 ) ).ToVector4();
	}

	void StartMenu::SetSelectedText_Green( const boost::shared_ptr<EzText> &text, bool outline )
	{
		if ( text == 0 )
			return;

		text->OutlineColor = ( bColor( 0, 0, 0, outline ? 255 : 0 ) ).ToVector4();
		text->MyFloatColor = ( bColor( 65, 255, 100 ) ).ToVector4();
	}

	void StartMenu::SetItemProperties_Green( const boost::shared_ptr<MenuItem> &item, bool outline )
	{
		SetText_Green( item->MyText, outline );
		SetText_Green( item->MySelectedText, outline );
	}

        void StartMenu::SetItemProperties_Red( const boost::shared_ptr<MenuItem> &item )
        {
            if (item->MyText == 0) return;
			//item.MyText.OutlineColor = bColor(191, 191, 191).ToVector4();
			//item.MyText.MyFloatColor = bColor(175, 8, 64).ToVector4();
			//item.MySelectedText.OutlineColor = bColor(205, 205, 205).ToVector4();
			//item.MySelectedText.MyFloatColor = bColor(242, 12, 85).ToVector4(); 

			SetTextUnselected_Red(item->MyText);
			SetTextSelected_Red(item->MySelectedText);
        }

		void StartMenu::SetTextSelected_Red( const boost::shared_ptr<EzText> &text )
		{
			text->OutlineColor = bColor(205, 205, 205).ToVector4() * .95f;
			text->OutlineColor.W = 1.0f;
			text->MyFloatColor = bColor(242, 12, 85).ToVector4() * .96f;
			text->MyFloatColor.W = 1.0f;
		}

		void StartMenu::SetTextUnselected_Red( const boost::shared_ptr<EzText> &text )
		{
			text->OutlineColor = bColor(191, 191, 191).ToVector4() * .97f;
			text->OutlineColor.W = 1.0f;
			text->MyFloatColor = bColor(175, 8, 64).ToVector4();
		}

	void StartMenu::OnAdd()
	{
		CloudberryKingdomGame::SetPresence( Presence_TitleScreen );

		CkBaseMenu::OnAdd();
	}

	void StartMenu::Init()
	{
		 CkBaseMenu::Init();

		SlideInFrom = PresetPos_LEFT;
		SlideOutTo = PresetPos_LEFT;

		ReturnToCallerDelay = 4;
		CallDelay = 33;
		setSlideLength( 36 );
		DestinationScale *= 1.015f;

		MyPile = boost::make_shared<DrawPile>();

		MyMenu = boost::make_shared<Menu>( false );

		MyMenu->setControl( -2 );

		MyMenu->CheckForOutsideClick = false;
		MyMenu->OnB = boost::make_shared<StartMenuExitLambda>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) );

		FontScale *= .88f;
		PosAdd = Vector2( 0, -117 );

		// Make the start menu
		MakeMenu();
	}

	void StartMenu::GrayItem( const boost::shared_ptr<MenuItem> &item )
	{
		item->MyText->MyFloatColor = ColorHelper::Gray( .535f );
		item->MySelectedText->MyFloatColor = ColorHelper::Gray( .55f );
	}

	void StartMenu::MakeMenu()
	{
		boost::shared_ptr<MenuItem> item;

		EnsureFancy();

		this->CallToLeft = true;
	}

	void StartMenu::SetChildControl( const boost::shared_ptr<GUI_Panel> &child )
	{
	}

	void StartMenu::MyPhsxStep()
	{
		MyMenu->Active = !NoBack;

		CkBaseMenu::MyPhsxStep();

		if ( Active )
			ButtonCheck::PreLogIn = true;
	}

	void StartMenu::DoneWithCharSelect()
	{
		MyGame->WaitThenDo( 0, boost::make_shared<BringNextMenuLambda>( boost::static_pointer_cast<StartMenu>( shared_from_this() ) ) );
	}

	void StartMenu::BringNextMenu()
	{
		switch ( MyNextMenu )
		{
			case Next_CAMPAIGN:
				BringCampaign();
				break;
			case Next_ARCADE:
				BringArcade();
				break;
			case Next_FREEPLAY:
				BringFreeplay();
				break;
		}
	}

	void StartMenu::BringCampaign()
	{
	}

	void StartMenu::BringArcade()
	{
	}

	void StartMenu::BringFreeplay()
	{
		//Call(new CustomLevel_GUI());
	}

	void StartMenu::OnReturnTo()
	{
		CloudberryKingdomGame::SetPresence( Presence_TitleScreen );

		CkBaseMenu::OnReturnTo();
		NoBack = false;
	}

	void StartMenu::InitializeInstanceFields()
	{
		NoBack = false;
	}
}
