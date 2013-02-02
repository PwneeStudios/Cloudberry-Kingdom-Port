#include <global_header.h>

#include <Hacks\String.h>
#include <MasterHack.h>
#include <Game\CloudberryKingdom\CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	bool SoundMenu::LanguageOption;

	void SoundMenu::InitOnToggleHelper::Apply( const bool &state )
	{
#if defined(PC_VERSION)
		PlayerManager::SavePlayerData->ResolutionPreferenceSet = true;
		Tools::setFullscreen( state );
#endif
		SaveGroup::SaveAll();
	#if defined(PC_VERSION)
		PlayerManager::SaveRezAndKeys();
	#endif
	}

	SoundMenu::InitHideHelper::InitHideHelper( const boost::shared_ptr<SoundMenu> &sm )
	{
		this->sm = sm;
	}

	void SoundMenu::InitHideHelper::Apply( const boost::shared_ptr<MenuItem> &_item )
	{
		sm->Hide();
		sm->Call( MakeMagic( ControlScreen, ( sm->getControl() ) ), 10 );
	}

#if defined(PC_VERSION)
	SoundMenu::InitCallCustomControlsHelper::InitCallCustomControlsHelper( const boost::shared_ptr<SoundMenu> &sm )
	{
		this->sm = sm;
	}

	void SoundMenu::InitCallCustomControlsHelper::Apply( const boost::shared_ptr<MenuItem> &menuitem )
	{
		sm->Call( MakeMagic( CustomControlsMenu, () ), 10 );
	}

	SoundMenu::InitOnConfirmedIndexSelect::InitOnConfirmedIndexSelect( const boost::shared_ptr<MenuList> &FsRezList )
	{
		this->FsRezList = FsRezList;
	}

	void SoundMenu::InitOnConfirmedIndexSelect::Apply()
	{
		PlayerManager::SavePlayerData->ResolutionPreferenceSet = true;
		ResolutionGroup::Use( boost::dynamic_pointer_cast<DisplayMode>( FsRezList->getCurObj() ) );
		SaveGroup::SaveAll();
		PlayerManager::SaveRezAndKeys();
	}
#endif

	SoundMenu::InitOnConfirmedIndexSelect_Language::InitOnConfirmedIndexSelect_Language( const boost::shared_ptr<SoundMenu> &sm, const boost::shared_ptr<MenuList> &FsLanguageList )
	{
		this->sm = sm;
		this->FsLanguageList = FsLanguageList;
	}

	void SoundMenu::InitOnConfirmedIndexSelect_Language::Apply()
	{
        sm->ChosenLanguage = (Localization::Language)FsLanguageList->ListIndex;
        //PlayerManager::SavePlayerData.ResolutionPreferenceSet = true;
        //ResolutionGroup.Use(LanguageList->CurObj as DisplayMode);
        //SaveGroup.SaveAll();
        //PlayerManager::SaveRezAndKeys();
	}

#if defined(PC_VERSION)
	SoundMenu::Toggle_BorderlessProxy::Toggle_BorderlessProxy( const boost::shared_ptr<SoundMenu> &sm )
	{
		this->sm = sm;
	}

	void SoundMenu::Toggle_BorderlessProxy::Apply( const bool &state )
	{
		sm->Toggle_Borderless( state );
	}
#endif // #if defined(PC_VERSION)

	SoundMenu::SoundMenu( int Control, bool LanguageOption ) : VerifyBaseMenu( false ) { }
	boost::shared_ptr<SoundMenu> SoundMenu::SoundMenu_Construct( int Control, bool LanguageOption )
	{
		VerifyBaseMenu::VerifyBaseMenu_Construct( false );

		Fade = false;
        EnableBounce();

		this->LanguageOption = LanguageOption;
		this->setControl( Control );
		FixedToCamera = true;

		Constructor();

		return boost::static_pointer_cast<SoundMenu>( shared_from_this() );
	}

	void SoundMenu::Init()
	{
			ChosenLanguage = Localization::CurrentLanguage->MyLanguage;

#if defined(PC_VERSION)
            bool ConsoleVersion = false;
#else
            bool ConsoleVersion = true;
#endif

		VerifyBaseMenu::Init();

        if (UseBounce)
            CallToLeft = false;
        else
			CallToLeft = true;

		this->FontScale *= .9f;

#if PC_VERSION
        bool CenterItems = false;
#else
        bool CenterItems = false;
#endif

		// Header
		HeaderText = boost::make_shared<EzText>( Localization::Words_Options, ItemFont );
		HeaderText->Name = std::wstring( L"Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		boost::shared_ptr<MenuSlider> FxSlider = MakeMagic( MenuSlider, ( boost::make_shared<EzText>( Localization::Words_SoundVolume, ItemFont, CenterItems ) ) );
		FxSlider->setMyFloat( Tools::SoundVolume );
		FxSlider->Name = std::wstring( L"Sound" );
		AddItem( FxSlider );

		boost::shared_ptr<MenuSlider> MusicSlider = MakeMagic( MenuSlider, ( boost::make_shared<EzText>( Localization::Words_MusicVolume, ItemFont, CenterItems ) ) );
		MusicSlider->setMyFloat( Tools::MusicVolume );
		MusicSlider->Name = std::wstring( L"Music" );
		AddItem( MusicSlider );

		boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_Controls, ItemFont, CenterItems ) ) );
		//item->setGo( boost::make_shared<InitHideHelper>( boost::static_pointer_cast<SoundMenu>( shared_from_this() ) ) );
		item->setGo( Go_Controls );
		item->Name = std::wstring( L"Controls" );
		AddItem( item );

            if (LanguageOption)
            {
                // Language
                boost::shared_ptr<EzText> LanguageText = boost::make_shared<EzText>(Localization::Words_Language, ItemFont, CenterItems);
                SetHeaderProperties(LanguageText);
                LanguageText->Name = L"Language";
                MyPile->Add(LanguageText);

				boost::shared_ptr<MenuList> LanguageList = MakeMagic( MenuList, () );
					MenuList_PostConstruct( LanguageList );

				LanguageList->setGo( boost::make_shared<MenuReturnToCallerLambda>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) ) );
                LanguageList->Name = L"LanguageList";
                LanguageList->Center = false;
                LanguageList->MyExpandPos = Vector2(-498.1506f, 713.873f);

                // Add languages to the language list
                for (int j = 0; j < Localization::NumLanguages; j++)
                {
                    Localization::Language l = (Localization::Language)j;

                    std::wstring str = Localization::LanguageName(l);
                    item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( str, ItemFont, false, true ) ) );
                    SetItemProperties(item);
                    LanguageList->AddItem(item, l);
                }
                AddItem(LanguageList);
                LanguageList->SetIndex((int)Localization::CurrentLanguage->MyLanguage);
                LanguageList->OnConfirmedIndexSelect = boost::make_shared<InitOnConfirmedIndexSelect_Language>( boost::static_pointer_cast<SoundMenu>( shared_from_this() ), LanguageList );
            }

	#if defined(PC_VERSION)
		// Custom controls
		boost::shared_ptr<MenuItem> mitem = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_EditControls, ItemFont, CenterItems ) ) );
		//mitem->setGo( boost::make_shared<InitCallCustomControlsHelper>( boost::static_pointer_cast<SoundMenu>( shared_from_this() ) ) );
		mitem->setGo( Cast.ToItem(Go_CustomControls) );
		mitem->Name = std::wstring( L"Custom" );
		AddItem( mitem );

		// Full screen resolutions
		boost::shared_ptr<EzText> RezText = boost::make_shared<EzText>( Localization::Words_Resolution, ItemFont, CenterItems );
		SetHeaderProperties( RezText );
		RezText->Name = std::wstring( L"RezText" );
		MyPile->Add( RezText );

		boost::shared_ptr<MenuList> FsRezList = MakeMagic( MenuList, () );
			MenuList_PostConstruct( FsRezList );
		FsRezList->Name = std::wstring( L"RezList" );
		FsRezList->Center = false;
		FsRezList->MyExpandPos = Vector2( -498.1506f, 713.873f );
		int i = 0;
		int CurRez = 0;

		// Get viable resolutions
		std::vector<boost::shared_ptr<DisplayMode> > modes = GetSupportedDisplayModes();
		if ( modes.size() == 0 )
		{
			boost::shared_ptr<DisplayMode> default_mode = boost::make_shared<DisplayMode>();
			default_mode->Width = 1280;
			default_mode->Height = 720;
			modes.push_back( default_mode );
		}

		// Add resolutions to the current list
		bool found = false;
		for ( std::vector<boost::shared_ptr<DisplayMode> >::const_iterator mode = modes.begin(); mode != modes.end(); ++mode )
		{
			std::wstring str = ::ToString( ( *mode )->Width ) + std::wstring( L" x " ) + ::ToString( ( *mode )->Height );
			//std::wstring str = std::wstring( L"Hello" );
			Tools::Write( str.c_str() );
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( str, ItemFont, false, true ) ) );
			SetItemProperties( item );
			FsRezList->AddItem( item, MakeSmartObject( *mode ) );

			if ( ( *mode )->Width == Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferWidth && ( *mode )->Height == Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferHeight )
			{
				CurRez = i;
				found = true;
			}
			else if ( !found && ( *mode )->Width == Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferWidth )
				CurRez = i;

			i++;
		}
		AddItem( FsRezList );
		FsRezList->SetIndex( CurRez );
		FsRezList->OnConfirmedIndexSelect = boost::make_shared<InitOnConfirmedIndexSelect>( FsRezList );

		// Full screen toggle
		boost::shared_ptr<EzText> FullScreenText = boost::make_shared<EzText>( Localization::Words_FullScreen, ItemFont, CenterItems );
		SetHeaderProperties( FullScreenText );
		FullScreenText->Name = std::wstring( L"Fullscreen" );
		MyPile->Add( FullScreenText );

		boost::shared_ptr<MenuToggle> toggle = MakeMagic( MenuToggle, ( ItemFont ) );
		toggle->OnToggle = boost::make_shared<InitOnToggleHelper>();
		toggle->Name = std::wstring( L"FullscreenToggle" );
		toggle->Toggle( Tools::getFullscreen() );

		AddItem( toggle );

		//AddToggle_FixedTimestep();
		//AddToggle_Borderless();
	#endif

		// Credits
		if (LanguageOption && !CloudberryKingdomGame.HideLogos)
		{
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>(Localization::Words::Words_Credits, ItemFont, CenterItems) ) );
			item->setGo( Cast::ToItem(Go_Credits) );
			item->Name = L"Credits";
			AddItem(item);
		}

#if PC_VERSION
            MakeBackButton();
#else
            MakeBackButton();
            //MakeStaticBackButton();
#endif

		if ( ConsoleVersion )
			SetPosition_Console();
		else
			SetPosition_PC();

		MyMenu->SortByHeight();

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}

#if PC_VERSION
        void SoundMenu::Go_CustomControls()
        {
            if (UseBounce)
            {
                setPauseGame( false );
                Hid = true;
                RegularSlideOut(PresetPos_RIGHT, 0);
            }
            else
            {
                Hide();
            }

            Call( MakeMagic( CustomControlsMenu, () ), 0);
        }
#endif

		void SoundMenu::Go_Controls()
        {
            if (UseBounce)
            {
                setPauseGame( false );
                Hid = true;
                RegularSlideOut(PresetPos_RIGHT, 0);
            }
            else
            {
                Hide();
            }

            Call( MakeMagic( ControlScreen, ( getControl() ) ), 0);
        }

		void SoundMenu::Go_Credits()
		{
			Tools::SongWad->FadeOut();
			MyMenu->Active = false;

			MyGame->WaitThenDo(4, StartFade);
			MyGame->WaitThenDo(87, StartCredits);
		}

		void SoundMenu::StartFade()
		{
			Fade = true;
			Black->setAlpha( 0 );
		}

		void SoundMenu::StartCredits()
		{
			MyGame->WaitThenDo(20, AfterCredits);
			MainVideo::StartVideo_CanSkipIfWatched( L"Credits" );
		}

		void SoundMenu::AfterCredits()
		{
			Fade = false;
			Black->setAlpha( 3.45f );
			MyMenu->Active = true;
			Tools::SongWad->Stop();
			Tools::PlayHappyMusic();
		}

        void SoundMenu::Release()
        {
			if (Black != 0) Black->Release();

            if ( ChosenLanguage != Localization::CurrentLanguage->MyLanguage )
            {
                Localization::SetLanguage( ChosenLanguage );
                MyGame->ReInitGameObjects();

				for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
                {
                    boost::shared_ptr<GUI_Panel> panel = boost::dynamic_pointer_cast<GUI_Panel>( obj );
                    if (0 != panel)
					{
						if ( boost::dynamic_pointer_cast<StartMenu_MW_Pre>( panel ) != 0 ||
							 boost::dynamic_pointer_cast<StartMenu_MW_PressStart>( panel ) != 0 ||
							 boost::dynamic_pointer_cast<StartMenu_MW_Simple>( panel ) != 0 )
						{
							panel->SlideOut( PresetPos_LEFT, 0);
						}
					}
                }

                MyGame->PhsxStepsToDo += 20;

                ButtonCheck.PreventInput();
                ButtonCheck.PreventTimeStamp += 20;
            }

            VerifyBaseMenu::Release();
        }

        void SoundMenu::ReturnToCaller()
        {
            VerifyBaseMenu::ReturnToCaller();
        }
	
#if defined(PC_VERSION)
	void SoundMenu::AddToggle_Borderless()
	{
		// Text
		boost::shared_ptr<EzText> Text = boost::make_shared<EzText>( Localization::Words_WindowBorder, ItemFont );
		SetHeaderProperties( Text );
		Text->Name = std::wstring( L"WindowBorder" );
		MyPile->Add( Text );
		Text->setPos( Vector2( -1232.142f, -499.9359f ) );
		Text->setScale( Text->getScale() * .9f );

		// Toggle
		boost::shared_ptr<MenuToggle> Toggle = MakeMagic( MenuToggle, ( ItemFont ) );
		Toggle->OnToggle = boost::make_shared<Toggle_BorderlessProxy>( boost::static_pointer_cast<SoundMenu>( shared_from_this() ) );
		Toggle->Toggle( Tools::WindowBorder );
		Toggle->Name = std::wstring( L"WindowBorderToggle" );
		AddItem( Toggle );
		Toggle->setSetPos( Vector2( 1315.078f, -451.4125f ) );
	}
#endif

#if defined(PC_VERSION)
	void SoundMenu::Toggle_Borderless( bool state )
	{
		PlayerManager::SavePlayerData->ResolutionPreferenceSet = true;
		Tools::WindowBorder = state;
		SaveGroup::SaveAll();
		PlayerManager::SaveRezAndKeys();

		Tools::GameClass->SetBorder( Tools::WindowBorder );
	}
#endif

	bool SoundMenu::MenuReturnToCaller( const boost::shared_ptr<Menu> &menu )
	{
	#if defined(PC_VERSION)
		PlayerManager::SaveRezAndKeys();
	#endif

		return VerifyBaseMenu::MenuReturnToCaller( menu );
	}



        void SoundMenu::SetPosition_Console()
        {
            if ( LanguageOption )
            {
				boost::shared_ptr<MenuItem> _item;
				_item = MyMenu->FindItemByName( L"Sound" ); if (_item != 0 ) { _item->setSetPos( Vector2(-27.38177f, 745.9205f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1686.11f, -152.7778f ); }
				_item = MyMenu->FindItemByName( L"Music" ); if (_item != 0 ) { _item->setSetPos( Vector2(-27.38177f, 531.5082f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1686.11f, -150.0001f ); }
				_item = MyMenu->FindItemByName( L"LanguageList" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1325.f, 136.f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"Controls" ); if (_item != 0 ) { _item->setSetPos( Vector2(-27.38177f, 42.49181f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1347.618f, -329.4443f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"Credits" ); if (_item != 0 ) { _item->setSetPos( Vector2(-27.38177f, -144.5556f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

				MyMenu->setPos( Vector2(-991.2675f, -246.4287f ) );

				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1072.619f, 812.7616f ) ); _t->setScale( 0.864f ); }
				_t = MyPile->FindEzText( L"Language" ); if (_t != 0 ) { _t->setPos( Vector2(-1033.333f, 13.88895f ) ); _t->setScale( 0.6704169f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-18.6521f, -7.539473f ) ); _q->setSize( Vector2( 1223.651f, 922.9517f ) ); }

				MyPile->setPos( Vector2( 29.76172f, 21.82541f ) );
			}
            else
            {
                boost::shared_ptr<MenuItem> _item;
                _item = MyMenu->FindItemByName( L"Sound" ); if (_item != 0 ) { _item->setSetPos( Vector2(-27.38177f, 745.9205f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1686.11f, -152.7778f ); }
                _item = MyMenu->FindItemByName( L"Music" ); if (_item != 0 ) { _item->setSetPos( Vector2(-27.38177f, 531.5082f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1686.11f, -150.0001f ); }
                _item = MyMenu->FindItemByName( L"Controls" ); if (_item != 0 ) { _item->setSetPos( Vector2(-27.38177f, 306.3806f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1344.84f, -129.4444f ) ); _item->MyText->setScale( 0.6704169f ); _item->MySelectedText->setScale( 0.6704169f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

                MyMenu->setPos( Vector2(-980.1562f, -338.0954f ) );

                boost::shared_ptr<EzText> _t;
                _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1072.619f, 812.7616f ) ); _t->setScale( 0.864f ); }

                boost::shared_ptr<QuadClass> _q;
                _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-18.6521f, -7.539473f ) ); _q->setSize( Vector2( 1223.651f, 922.9517f ) ); }

                MyPile->setPos( Vector2( 29.76172f, 21.82541f ) );
            }
        }

        void SoundMenu::SetPosition_PC()
        {
            if ( LanguageOption )
            {
				boost::shared_ptr<MenuItem> _item;
				_item = MyMenu->FindItemByName( L"Sound" ); if (_item != 0 ) { _item->setSetPos( Vector2(-169.048f, 729.2538f ) ); _item->MyText->setScale( 0.6606668f ); _item->MySelectedText->setScale( 0.6606668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1869.443f, -152.7778f ); }
				_item = MyMenu->FindItemByName( L"Music" ); if (_item != 0 ) { _item->setSetPos( Vector2(-169.048f, 537.0638f ) ); _item->MyText->setScale( 0.6916667f ); _item->MySelectedText->setScale( 0.6606668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1869.443f, -136.1112f ); }
				_item = MyMenu->FindItemByName( L"RezList" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1077.38f, 151.8088f ) ); _item->MyText->setScale( 0.6119168f ); _item->MySelectedText->setScale( 0.6119168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"FullscreenToggle" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1090.078f, 101.3653f ) ); _item->MyText->setScale( 0.6095002f ); _item->MySelectedText->setScale( 0.6095002f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"LanguageList" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1088.888f, -200.1113f ) ); _item->MyText->setScale( 0.6166669f ); _item->MySelectedText->setScale( 0.6166669f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"Controls" ); if (_item != 0 ) { _item->setSetPos( Vector2( 538.491f, -254.7306f ) ); _item->MyText->setScale( 0.6705834f ); _item->MySelectedText->setScale( 0.6705834f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"Custom" ); if (_item != 0 ) { _item->setSetPos( Vector2( 402.7765f, -441.3655f ) ); _item->MyText->setScale( 0.6581671f ); _item->MySelectedText->setScale( 0.6581671f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1603.173f, -621.111f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
				_item = MyMenu->FindItemByName( L"Credits" ); if (_item != 0 ) { _item->setSetPos( Vector2( 580.5563f, -616.7772f ) ); _item->MyText->setScale( 0.6445836f ); _item->MySelectedText->setScale( 0.6445836f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

				MyMenu->setPos( Vector2(-1007.934f, -43.651f ) );

				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-1072.62f, 968.3172f ) ); _t->setScale( 0.864f ); }
				_t = MyPile->FindEzText( L"Language" ); if (_t != 0 ) { _t->setPos( Vector2(-1036.11f, -119.4448f ) ); _t->setScale( 0.6748332f ); }
				_t = MyPile->FindEzText( L"RezText" ); if (_t != 0 ) { _t->setPos( Vector2(-1032.143f, 236.1738f ) ); _t->setScale( 0.6868508f ); }
				_t = MyPile->FindEzText( L"Fullscreen" ); if (_t != 0 ) { _t->setPos( Vector2(-1040.475f, 63.95281f ) ); _t->setScale( 0.7051834f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-18.6521f, -10.31725f ) ); _q->setSize( Vector2( 1376.984f, 1077.035f ) ); }

				MyPile->setPos( Vector2( 29.76172f, 21.82541f ) );
			}
            else
            {
                boost::shared_ptr<MenuItem> _item;
                _item = MyMenu->FindItemByName( L"Sound" ); if (_item != 0 ) { _item->setSetPos( Vector2( 3.173767f, 751.4761f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1611.11f, -152.7778f ); }
                _item = MyMenu->FindItemByName( L"Music" ); if (_item != 0 ) { _item->setSetPos( Vector2( 64.28528f, 534.286f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1552.777f, -150.0001f ); }
                _item = MyMenu->FindItemByName( L"Controls" ); if (_item != 0 ) { _item->setSetPos( Vector2( 596.8245f, 325.825f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"Custom" ); if (_item != 0 ) { _item->setSetPos( Vector2( 591.6658f, 133.6347f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"RezList" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1019.047f, -256.5245f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"FullscreenToggle" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1245.634f, -281.9681f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"WindowBorderToggle" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1315.078f, -451.4125f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1603.173f, -621.111f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

                MyMenu->setPos( Vector2(-1007.934f, -43.651f ) );

                boost::shared_ptr<EzText> _t;
                _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-967.064f, 951.6506f ) ); _t->setScale( 0.864f ); }
                _t = MyPile->FindEzText( L"RezText" ); if (_t != 0 ) { _t->setPos( Vector2(-1173.81f, -174.9373f ) ); _t->setScale( 0.7776f ); }
                _t = MyPile->FindEzText( L"Fullscreen" ); if (_t != 0 ) { _t->setPos( Vector2(-1190.475f, -338.825f ) ); _t->setScale( 0.7776f ); }
                _t = MyPile->FindEzText( L"WindowBorder" ); if (_t != 0 ) { _t->setPos( Vector2(-1232.142f, -499.9359f ) ); _t->setScale( 0.7776f ); }

                boost::shared_ptr<QuadClass> _q;
                _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-18.6521f, -10.31725f ) ); _q->setSize( Vector2( 1376.984f, 1077.035f ) ); }

                MyPile->setPos( Vector2( 29.76172f, 21.82541f ) );
            }
        }

	void SoundMenu::OnAdd()
	{
		 VerifyBaseMenu::OnAdd();

		if (LanguageOption)
		{
			// Black
			Black = boost::make_shared<QuadClass>();
			Black->FullScreen( Tools::getCurCamera() );
			Black->Quad_Renamed.SetColor( Color::Black );
			Black->setAlpha( 0 );
		}
	}

		void SoundMenu::MyDraw()
		{
			VerifyBaseMenu::MyDraw();

			if (Black != 0 && Black->getAlpha() >= 0)
			{
				Black->Draw();
				if (Fade)
					Black->setAlpha( Black->getAlpha() + .02f );
				else
					Black->setAlpha( Black->getAlpha() - .02f );
			}
		}
}
