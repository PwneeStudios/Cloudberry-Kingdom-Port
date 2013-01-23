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
		this->CallToLeft = true;

		this->FontScale *= .9f;

		// Header
		HeaderText = boost::make_shared<EzText>( Localization::Words_OPTIONS, ItemFont );
		HeaderText->Name = std::wstring( L"Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		boost::shared_ptr<MenuSlider> FxSlider = MakeMagic( MenuSlider, ( boost::make_shared<EzText>( Localization::Words_SOUND_VOLUME, ItemFont ) ) );
		FxSlider->setMyFloat( Tools::SoundVolume );
		FxSlider->Name = std::wstring( L"Sound" );
		AddItem( FxSlider );

		boost::shared_ptr<MenuSlider> MusicSlider = MakeMagic( MenuSlider, ( boost::make_shared<EzText>( Localization::Words_MUSIC_VOLUME, ItemFont ) ) );
		MusicSlider->setMyFloat( Tools::MusicVolume );
		MusicSlider->Name = std::wstring( L"Music" );
		AddItem( MusicSlider );

		boost::shared_ptr<MenuItem> item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_CONTROLS, ItemFont ) ) );
		item->setGo( boost::make_shared<InitHideHelper>( boost::static_pointer_cast<SoundMenu>( shared_from_this() ) ) );
		item->Name = std::wstring( L"Controls" );
		AddItem( item );

            if (LanguageOption)
            {
                // Language
                boost::shared_ptr<EzText> LanguageText = boost::make_shared<EzText>(Localization::Words_LANGUAGE, ItemFont);
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
		boost::shared_ptr<MenuItem> mitem = MakeMagic( MenuItem, ( boost::make_shared<EzText>( Localization::Words_EDIT_CONTROLS, ItemFont ) ) );
		mitem->setGo( boost::make_shared<InitCallCustomControlsHelper>( boost::static_pointer_cast<SoundMenu>( shared_from_this() ) ) );
		mitem->Name = std::wstring( L"Custom" );
		AddItem( mitem );

		// Full screen resolutions
		boost::shared_ptr<EzText> RezText = boost::make_shared<EzText>( Localization::Words_RESOLUTION, ItemFont );
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
		boost::shared_ptr<EzText> FullScreenText = boost::make_shared<EzText>( Localization::Words_FULL_SCREEN, ItemFont );
		SetHeaderProperties( FullScreenText );
		FullScreenText->Name = std::wstring( L"Fullscreen" );
		MyPile->Add( FullScreenText );

		boost::shared_ptr<MenuToggle> toggle = MakeMagic( MenuToggle, ( ItemFont ) );
		toggle->OnToggle = boost::make_shared<InitOnToggleHelper>();
		toggle->Name = std::wstring( L"FullscreenToggle" );
		toggle->Toggle( Tools::getFullscreen() );

		AddItem( toggle );

		//AddToggle_FixedTimestep();
		AddToggle_Borderless();
	#endif

		MakeBackButton();

		if ( ConsoleVersion )
			SetPosition_Console();
		else
			SetPosition_PC();

		MyMenu->SortByHeight();

		MyMenu->OnX = MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}

    void SoundMenu::ReturnToCaller()
    {
        if (ChosenLanguage != Localization::CurrentLanguage->MyLanguage)
        {
            Localization::SetLanguage(ChosenLanguage);
            MyGame->ReInitGameObjects();
                
            MyGame->PhsxStepsToDo += 20;

            ButtonCheck::PreventInput();
            ButtonCheck::PreventTimeStamp += 20;
        }

        VerifyBaseMenu::ReturnToCaller();
    }
	
#if defined(PC_VERSION)
	void SoundMenu::AddToggle_Borderless()
	{
		// Text
		boost::shared_ptr<EzText> Text = boost::make_shared<EzText>( Localization::Words_WINDOW_BORDER, ItemFont );
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
                _item = MyMenu->FindItemByName( L"Sound" ); if (_item != 0 ) { _item->setSetPos( Vector2( 3.173767f, 751.4761f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1611.11f, -152.7778f ); }
                _item = MyMenu->FindItemByName( L"Music" ); if (_item != 0 ) { _item->setSetPos( Vector2( 64.28528f, 534.286f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1552.777f, -150.0001f ); }
                _item = MyMenu->FindItemByName( L"Controls" ); if (_item != 0 ) { _item->setSetPos( Vector2( 280.1578f, 50.82506f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1344.84f, -129.4444f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"LanguageList" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1236.111f, 116.5555f ) ); _item->MyText->setScale( 0.7108332f ); _item->MySelectedText->setScale( 0.7108332f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

                MyMenu->setPos( Vector2(-980.1562f, -338.0954f ) );

                boost::shared_ptr<EzText> _t;
                _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-978.1751f, 734.984f ) ); _t->setScale( 0.864f ); }
                _t = MyPile->FindEzText( L"Language" ); if (_t != 0 ) { _t->setPos( Vector2(-824.9998f, -44.44439f ) ); _t->setScale( 0.8185834f ); }

                boost::shared_ptr<QuadClass> _q;
                _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2(-18.6521f, -7.539473f ) ); _q->setSize( Vector2( 1223.651f, 922.9517f ) ); }

                MyPile->setPos( Vector2( 29.76172f, 21.82541f ) );
            }
            else
            {
                boost::shared_ptr<MenuItem> _item;
                _item = MyMenu->FindItemByName( L"Sound" ); if (_item != 0 ) { _item->setSetPos( Vector2( 3.173767f, 751.4761f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1611.11f, -152.7778f ); }
                _item = MyMenu->FindItemByName( L"Music" ); if (_item != 0 ) { _item->setSetPos( Vector2( 64.28528f, 534.286f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1552.777f, -150.0001f ); }
                _item = MyMenu->FindItemByName( L"Controls" ); if (_item != 0 ) { _item->setSetPos( Vector2( 596.8245f, 317.4917f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1344.84f, -129.4444f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

                MyMenu->setPos( Vector2(-980.1562f, -338.0954f ) );

                boost::shared_ptr<EzText> _t;
                _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-978.1751f, 734.984f ) ); _t->setScale( 0.864f ); }

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
                _item = MyMenu->FindItemByName( L"Sound" ); if (_item != 0 ) { _item->setSetPos( Vector2( 3.173767f, 751.4761f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1611.11f, -152.7778f ); }
                _item = MyMenu->FindItemByName( L"Music" ); if (_item != 0 ) { _item->setSetPos( Vector2( 64.28528f, 534.286f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); boost::static_pointer_cast<MenuSlider>( _item )->SliderShift = Vector2( 1552.777f, -150.0001f ); }
                _item = MyMenu->FindItemByName( L"Controls" ); if (_item != 0 ) { _item->setSetPos( Vector2( 538.491f, -410.2862f ) ); _item->MyText->setScale( 0.6705834f ); _item->MySelectedText->setScale( 0.6705834f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"Custom" ); if (_item != 0 ) { _item->setSetPos( Vector2( 413.8881f, -599.6987f ) ); _item->MyText->setScale( 0.6581671f ); _item->MySelectedText->setScale( 0.6581671f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"RezList" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1077.38f, 151.8088f ) ); _item->MyText->setScale( 0.6119168f ); _item->MySelectedText->setScale( 0.6119168f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"LanguageList" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1105.555f, -347.3336f ) ); _item->MyText->setScale( 0.6166669f ); _item->MySelectedText->setScale( 0.6166669f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"FullscreenToggle" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1090.078f, 101.3653f ) ); _item->MyText->setScale( 0.6095002f ); _item->MySelectedText->setScale( 0.6095002f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"WindowBorderToggle" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1092.856f, -59.74591f ) ); _item->MyText->setScale( 0.6086668f ); _item->MySelectedText->setScale( 0.6086668f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }
                _item = MyMenu->FindItemByName( L"Back" ); if (_item != 0 ) { _item->setSetPos( Vector2( 1603.173f, -621.111f ) ); _item->MyText->setScale( 0.72f ); _item->MySelectedText->setScale( 0.72f ); _item->SelectIconOffset = Vector2( 0.f, 0.f ); }

                MyMenu->setPos( Vector2(-1007.934f, -43.651f ) );

                boost::shared_ptr<EzText> _t;
                _t = MyPile->FindEzText( L"Header" ); if (_t != 0 ) { _t->setPos( Vector2(-967.064f, 951.6506f ) ); _t->setScale( 0.864f ); }
                _t = MyPile->FindEzText( L"RezText" ); if (_t != 0 ) { _t->setPos( Vector2(-1032.143f, 236.1738f ) ); _t->setScale( 0.6868508f ); }
                _t = MyPile->FindEzText( L"Language" ); if (_t != 0 ) { _t->setPos( Vector2(-1027.777f, -280.5559f ) ); _t->setScale( 0.6748332f ); }
                _t = MyPile->FindEzText( L"Fullscreen" ); if (_t != 0 ) { _t->setPos( Vector2(-1040.475f, 63.95281f ) ); _t->setScale( 0.7051834f ); }
                _t = MyPile->FindEzText( L"WindowBorder" ); if (_t != 0 ) { _t->setPos( Vector2(-1043.253f, -124.9359f ) ); _t->setScale( 0.6186832f ); }

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
	}
}
