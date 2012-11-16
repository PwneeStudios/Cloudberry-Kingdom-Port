#include "SoundMenu.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Tools/Tools.h"
#include "Game/Tools/EzStorage.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/ControlScreen.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/CustomControls.h"
#include "Game/Menus/Menu Components/MenuList.h"
#include "Core/ResolutionGroup.h"
#include "Core/Text/EzText.h"
#include "Game/Localization.h"
#include "Game/Menus/Menu Components/MenuSlider.h"
#include "Game/Menus/Menu Components/MenuToggle.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/Menu.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"

using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

namespace CloudberryKingdom
{

	void SoundMenu::InitOnToggleHelper::Apply( bool state )
	{
		PlayerManager::SavePlayerData->ResolutionPreferenceSet = true;
		Tools::setFullscreen( state );
		SaveGroup::SaveAll();
	#if defined(PC_VERSION)
		PlayerManager::SaveRezAndKeys();
	#endif
	}

	SoundMenu::InitHideHelper::InitHideHelper( const std::shared_ptr<SoundMenu> &sm )
	{
		this->sm = sm;
	}

	void SoundMenu::InitHideHelper::Apply( const std::shared_ptr<MenuItem> &_item )
	{
		sm->Hide();
		sm->Call( std::make_shared<ControlScreen>( sm->getControl() ), 10 );
	}

	SoundMenu::InitCallCustomControlsHelper::InitCallCustomControlsHelper( const std::shared_ptr<SoundMenu> &sm )
	{
		this->sm = sm;
	}

	void SoundMenu::InitCallCustomControlsHelper::Apply( const std::shared_ptr<MenuItem> &menuitem )
	{
		sm->Call( std::make_shared<CustomControlsMenu>(), 10 );
	}

	SoundMenu::InitOnConfirmedIndexSelect::InitOnConfirmedIndexSelect( const std::shared_ptr<MenuList> &FsRezList )
	{
		this->FsRezList = FsRezList;
	}

	void SoundMenu::InitOnConfirmedIndexSelect::Apply()
	{
		PlayerManager::SavePlayerData->ResolutionPreferenceSet = true;
		ResolutionGroup::Use( dynamic_cast<DisplayMode*>( FsRezList->getCurObj() ) );
		SaveGroup::SaveAll();
		PlayerManager::SaveRezAndKeys();
	}

	SoundMenu::Toggle_BorderlessProxy::Toggle_BorderlessProxy( const std::shared_ptr<SoundMenu> &sm )
	{
		this->sm = sm;
	}

	void SoundMenu::Toggle_BorderlessProxy::Apply( bool state )
	{
		sm->Toggle_Borderless( state );
	}

	SoundMenu::SoundMenu( int Control ) : VerifyBaseMenu( false )
	{
		this->setControl( Control );
		FixedToCamera = true;

		Constructor();
	}

	void SoundMenu::Init()
	{
		VerifyBaseMenu::Init();
		this->CallToLeft = true;

		this->FontScale *= .9f;

		// Header
		HeaderText = std::make_shared<EzText>( Localization::Words_OPTIONS, ItemFont );
		HeaderText->Name = _T( "Header" );
		SetHeaderProperties( HeaderText );
		MyPile->Add( HeaderText );

		std::shared_ptr<MenuSlider> FxSlider = std::make_shared<MenuSlider>( std::make_shared<EzText>( Localization::Words_SOUND_VOLUME, ItemFont ) );
		FxSlider->setMyFloat( Tools::SoundVolume );
		FxSlider->Name = _T( "Sound" );
		AddItem( FxSlider );

		std::shared_ptr<MenuSlider> MusicSlider = std::make_shared<MenuSlider>( std::make_shared<EzText>( Localization::Words_MUSIC_VOLUME, ItemFont ) );
		MusicSlider->setMyFloat( Tools::MusicVolume );
		MusicSlider->Name = _T( "Music" );
		AddItem( MusicSlider );

		std::shared_ptr<MenuItem> item = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_CONTROLS, ItemFont ) );
		item->setGo( std::make_shared<InitHideHelper>( this ) );
		item->Name = _T( "Controls" );
		AddItem( item );

	#if defined(PC_VERSION)
		// Custom controls
		std::shared_ptr<MenuItem> mitem = std::make_shared<MenuItem>( std::make_shared<EzText>( Localization::Words_EDIT_CONTROLS, ItemFont ) );
		mitem->setGo( std::make_shared<InitCallCustomControlsHelper>( this ) );
		mitem->Name = _T( "Custom" );
		AddItem( mitem );

		// Full screen resolutions
		std::shared_ptr<EzText> RezText = std::make_shared<EzText>( Localization::Words_RESOLUTION, ItemFont );
		SetHeaderProperties( RezText );
		RezText->Name = _T( "RezText" );
		MyPile->Add( RezText );

		std::shared_ptr<MenuList> FsRezList = std::make_shared<MenuList>();
		FsRezList->Name = _T( "RezList" );
		FsRezList->Center = false;
		FsRezList->MyExpandPos = Vector2( -498.1506f, 713.873f );
		int i = 0;
		int CurRez = 0;

		// Get viable resolutions
		std::vector<DisplayMode*> modes = std::vector<DisplayMode*>();
		for ( Microsoft::Xna::Framework::Graphics::DisplayModeCollection::const_iterator mode = GraphicsAdapter::DefaultAdapter->SupportedDisplayModes.begin(); mode != GraphicsAdapter::DefaultAdapter->SupportedDisplayModes.end(); ++mode )
		{
			bool Any = false;
			for ( std::vector<DisplayMode*>::const_iterator existing = modes.begin(); existing != modes.end(); ++existing )
			{
				if ( ( *existing )->Width == ( *mode )->Width && ( *existing )->Height == ( *mode )->Height )
					Any = true;
			}

			if ( Any )
				continue;
			else
				modes.push_back( *mode );
		}

		// Add resolutions to the current list
		bool found = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<DisplayMode*>::const_iterator mode = modes.begin(); mode != modes.end(); ++mode )
		{
			std::wstring str = ( *mode )->Width + _T( " x " ) + ( *mode )->Height;
			Tools::Write( str );
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( str, ItemFont, false, true ) );
			SetItemProperties( item );
			FsRezList->AddItem( item, *mode );

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
		FsRezList->OnConfirmedIndexSelect = std::make_shared<InitOnConfirmedIndexSelect>( FsRezList );

		// Full screen toggle
		std::shared_ptr<EzText> FullScreenText = std::make_shared<EzText>( Localization::Words_FULL_SCREEN, ItemFont );
		SetHeaderProperties( FullScreenText );
		FullScreenText->Name = _T( "Fullscreen" );
		MyPile->Add( FullScreenText );

		std::shared_ptr<MenuToggle> toggle = std::make_shared<MenuToggle>( ItemFont );
		toggle->OnToggle = std::make_shared<InitOnToggleHelper>();
		toggle->Name = _T( "FullscreenToggle" );
		toggle->Toggle( Tools::getFullscreen() );

		AddItem( toggle );

		//AddToggle_FixedTimestep();
		AddToggle_Borderless();
	#endif

		MakeBackButton();
		SetPosition();

		MyMenu->OnX = MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		// Select the first item in the menu to start
		MyMenu->SelectItem( 0 );
	}

#if defined(PC_VERSION)
	void SoundMenu::AddToggle_Borderless()
	{
		// Text
		std::shared_ptr<EzText> Text = std::make_shared<EzText>( Localization::Words_WINDOW_BORDER, ItemFont );
		SetHeaderProperties( Text );
		Text->Name = _T( "WindowBorder" );
		MyPile->Add( Text );
		Text->setPos( Vector2( -1232.142f, -499.9359f ) );
		Text->setScale( Text->getScale() * .9f );

		// Toggle
		std::shared_ptr<MenuToggle> Toggle = std::make_shared<MenuToggle>( ItemFont );
		Toggle->OnToggle = std::make_shared<Toggle_BorderlessProxy>( this );
		Toggle->Toggle( Tools::WindowBorder );
		Toggle->Name = _T( "WindowBorderToggle" );
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

	bool SoundMenu::MenuReturnToCaller( const std::shared_ptr<Menu> &menu )
	{
	#if defined(PC_VERSION)
		PlayerManager::SaveRezAndKeys();
	#endif

		return VerifyBaseMenu::MenuReturnToCaller( menu );
	}

	void SoundMenu::SetPosition()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Sound" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 3.173767f, 751.4761f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			( static_cast<MenuSlider*>( _item ) )->SliderShift = Vector2( 1611.11f, -152.7778f );
		}
		_item = MyMenu->FindItemByName( _T( "Music" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 64.28528f, 534.286f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
			( static_cast<MenuSlider*>( _item ) )->SliderShift = Vector2( 1552.777f, -150.0001f );
		}
		_item = MyMenu->FindItemByName( _T( "Controls" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 596.8245f, 325.825f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Custom" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 591.6658f, 133.6347f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "RezList" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1019.047f, -256.5245f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "FullscreenToggle" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1245.634f, -281.9681f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "WindowBorderToggle" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1315.078f, -451.4125f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Back" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( 1603.173f, -621.111f ) );
			_item->MyText->setScale( 0.72f );
			_item->MySelectedText->setScale( 0.72f );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}

		MyMenu->setPos( Vector2( -1007.934f, -43.651f ) );

		std::shared_ptr<EzText> _t;
		_t = MyPile->FindEzText( _T( "Header" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -967.064f, 951.6506f ) );
			_t->setScale( 0.864f );
		}
		_t = MyPile->FindEzText( _T( "RezText" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1173.81f, -174.9373f ) );
			_t->setScale( 0.7776f );
		}
		_t = MyPile->FindEzText( _T( "Fullscreen" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1190.475f, -338.825f ) );
			_t->setScale( 0.7776f );
		}
		_t = MyPile->FindEzText( _T( "WindowBorder" ) );
		if ( _t != 0 )
		{
			_t->setPos( Vector2( -1232.142f, -499.9359f ) );
			_t->setScale( 0.7776f );
		}

		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Backdrop" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -18.6521f, -10.31725f ) );
			_q->setSize( Vector2( 1376.984f, 1077.035f ) );
		}

		MyPile->setPos( Vector2( 29.76172f, 21.82541f ) );
	}

	void SoundMenu::OnAdd()
	{
		 VerifyBaseMenu::OnAdd();

		SetPosition();
	}
}
