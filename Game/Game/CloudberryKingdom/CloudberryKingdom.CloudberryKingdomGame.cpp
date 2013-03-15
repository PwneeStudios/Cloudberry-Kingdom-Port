// Use this to test non-PC verion
//#undef PC_VERSION
//#define NOT_PC

#include <global_header.h>

#include <Core.h>
#include <Content/Wad.h>
#include <Graphics/Types.h>
#include <Graphics/QuadDrawer.h>
#include <Utility/Log.h>

#include <Hacks/List.h>
#include <Hacks/Queue.h>

#include <Audio/MediaPlayer.h>

#include <iostream>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include <MasterHack.h>
#include <Utility/Log.h>
#include <Utility/ConsoleInformation.h>
#include <Utility/Error.h>
#include <Core\Tools\Set.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Tilesets/CloudberryKingdom.TileSets.h"

#include <Game\Video.h>

#include <Game\Player\LeaderboardView.h>

#ifdef BOOST_BIN
	#include <BoostBin.h>
#endif

#include <Ratings.h>

#include <stdio.h>
#include <string.h>

#ifdef WINDOWS
	#include <malloc.h>
	#include <crtdbg.h>
	//#include <dbgint.h>
#endif

#ifdef PS3
	#include <Utility/NetworkPS3.h>
	#include <netex/libnetctl.h>
#endif

#ifdef CAFE

enum MyControllerTypes
{
	Who_NOONE,
	Who_VPAD,
	Who_KPAD
};

extern int WhoIsDisconnected;

#endif

namespace CloudberryKingdom
{

#if defined(DEBUG)
	int CloudberryKingdomGame::_count = 0;
	int CloudberryKingdomGame::address = 0;
#endif

#if defined(_CRTDBG_MAP_ALLOC) && defined(WINDOWS)
	_CrtMemState s1, s2, s3;

	void CloudberryKingdomGame::memdebug_DumpStart()
	{
	   // Send all reports to STDOUT
	   //_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
	   //_CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
	   //_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
	   //_CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
	   //_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
	   //_CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );

		_CrtMemCheckpoint( &s1 );
	}

	void CloudberryKingdomGame::memdebug_DumpEnd()
	{
		Recycler::DumpMetaBin();

		_CrtMemCheckpoint( &s2 );

		if ( _CrtMemDifference( &s3, &s1, &s2 ) )
		{
			_CrtDumpMemoryLeaks();
			Tools::Write( L"---------------------------------------------------------" );
			_CrtMemDumpStatistics( &s3 );
		}
	}
#endif


	void CloudberryKingdomGame::StaticIntializer_NoDependence()
	{
		TitleGameData_MW::InitializeStatics();
		
		Globals::InitializeStatics();
		ButtonCheck::InitializeStatics();
		PlayerManager::InitializeStatics();
		ComputerRecording::InitializeStatics();
		QuadDrawer::InitializeStatics();
		Camera::InitializeStatics();
		EzSoundWad::InitializeStatics();
		ColorSchemeManager::InitializeStatics();
		Hat::InitializeStatics();
		Unset::InitializeStatics();
		EzStorage::InitializeStatics();
		SaveGroup::InitializeStatics();
		ScoreDatabase::InitializeStatics();
		HeroRush_Tutorial::InitializeStatics();
		InitialLoadingScreen::InitializeStatics();
		DrawPile::InitializeStatics();
		CharacterSelectManager::InitializeStatics();
		PieceQuad::InitializeStatics();
		BackgroundType::InitializeStatics();
		CustomLevel_GUI::InitializeStatics();
		Particle::InitializeStatics();
		
		CampaignHelper::InitializeStatics();

		Awardments::InitializeStatics();
		MainVideo::InitializeStatics();
	}

	void CloudberryKingdomGame::StaticIntializer_AfterResourcesLoad()
	{
		EzText::InitializeStatics();

		BobPhsx::DefaultInfo::InitializeStatics();

		BobPhsxNormal::InitializeStatics();
		BobPhsxBig::InitializeStatics();
		BobPhsxBig::getInstance()->Set( BobPhsxBig::getInstance() );

		BobPhsxRandom::InitializeStatics();
		BobPhsxBouncy::InitializeStatics();
		BobPhsxBox::InitializeStatics();
		
		BobPhsxDouble::InitializeStatics();
		BobPhsxDouble::getInstance()->Set( BobPhsxDouble::getInstance() );

		BobPhsxInvert::InitializeStatics();
		BobPhsxInvert::getInstance()->Set( BobPhsxInvert::getInstance() );

		BobPhsxJetman::InitializeStatics();
		BobPhsxJetman::getInstance()->Set( BobPhsxJetman::getInstance() );

		BobPhsxMeat::InitializeStatics();
		BobPhsxMeat::getInstance()->Set( BobPhsxMeat::getInstance() );

		BobPhsxRocketbox::InitializeStatics();
		BobPhsxScale::InitializeStatics();
		BobPhsxScale::getInstance()->Set( BobPhsxScale::getInstance() );

		BobPhsxSmall::InitializeStatics();
		BobPhsxSmall::getInstance()->Set( BobPhsxSmall::getInstance() );

		BobPhsxSpaceship::InitializeStatics();
		BobPhsxTimeship::InitializeStatics();
		BobPhsxTime::InitializeStatics();
		BobPhsxTime::getInstance()->Set( BobPhsxTime::getInstance() );

		BobPhsxWheel::InitializeStatics();

		Bob::InitializeStatics();

		ObjectIcon::InitializeStatics();

		ObjectClass::InitializeStatics();

		FlyingBlob::InitializeStatics();
		ObjectData::InitializeStatics();
		Spike::InitializeStatics();

		ParticleEmitter::InitializeStatics();
		
		GameData::InitializeStatics();
		TitleGameData::InitializeStatics();
		Recycler::InitializeStatics();
		MenuItem::InitializeStatics();
		CharacterSelect::InitializeStatics();
		SimpleMenuBase::InitializeStatics();
		CustomHero_GUI::InitializeStatics();
		Upgrades::InitializeStatics();
		LoadingScreen::InitializeStatics();
		LevelConnector::InitializeStatics();
		Generators::InitializeStatics();
		FindCamZoneLambda::InitializeStatics();
		Checkpoint::InitializeStatics();
		Challenge_Escalation::InitializeStatics();
		Challenge_TimeCrisis::InitializeStatics();
		Challenge_HeroRush::InitializeStatics();
		Challenge_HeroRush2::InitializeStatics();
		Challenge_StoryMode::InitializeStatics();
		ActionGameData::InitializeStatics();

		// Menu::DefaultMenuInfo
            Menu::DefaultMenuInfo::SelectedNextColor = bColor(100, 250, 100, 255).ToVector4();
			Menu::DefaultMenuInfo::UnselectedNextColor = bColor(40, 180, 40, 255).ToVector4();

			Menu::DefaultMenuInfo::SelectedBackColor = bColor(250, 100, 100, 255).ToVector4();
            Menu::DefaultMenuInfo::UnselectedBackColor = bColor(180, 40, 40, 255).ToVector4();
			
			Menu::DefaultMenuInfo::SelectedXColor = bColor(75, 142, 240, 255).ToVector4();
			Menu::DefaultMenuInfo::UnselectedXColor = bColor(55, 125, 229, 255).ToVector4();
			
			Menu::DefaultMenuInfo::SelectedYColor = bColor(255, 226, 155, 255).ToVector4();
			Menu::DefaultMenuInfo::UnselectedYColor = bColor(255, 198, 55, 255).ToVector4();


		Menu::DefaultMenuInfo::Menu_UpDown_Sound = Tools::NewSound( std::wstring( L"Menu_Hover" ),.7f );
		Menu::DefaultMenuInfo::Menu_Select_Sound = Tools::NewSound( std::wstring( L"Menu_Select" ),.6f );
		Menu::DefaultMenuInfo::Menu_Slide_Sound = Tools::NewSound( std::wstring( L"Menu_Tick" ),.3f );
		Menu::DefaultMenuInfo::Menu_ListScroll_Sound = Tools::NewSound( std::wstring( L"Menu_Hover" ),.5f );
		Menu::DefaultMenuInfo::Menu_Back_Sound = Tools::NewSound( std::wstring( L"Menu_Back" ),.8f );
		Menu::DefaultMenuInfo::Menu_Slide_SoundDelay = 8;
		Menu::DefaultMenuInfo::MenuRightArrow_Texture = Tools::Texture( std::wstring( L"ListRightArrow" ) );
		Menu::DefaultMenuInfo::MenuLeftArrow_Texture = Tools::Texture( std::wstring( L"ListLeftArrow" ) );
		Menu::DefaultMenuInfo::MenuRightArrow_Offset = Vector2( 20, -14 );
		Menu::DefaultMenuInfo::MenuLeftArrow_Offset = Vector2( -20, -14 );
		Menu::DefaultMenuInfo::MenuArrow_Size = Vector2( 45, 45 );
		Menu::DefaultMenuInfo::MenuArrow_Color = ( bColor( 255, 255, 255, 255 ) ).ToVector4();
		Menu::DefaultMenuInfo::MenuRightArrow_Selected_Texture = Tools::Texture( std::wstring( L"ListRightArrow" ) );
		Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Texture = Tools::Texture( std::wstring( L"ListLeftArrow" ) );
		Menu::DefaultMenuInfo::MenuRightArrow_Selected_Offset = Vector2( 20, -14 );
		Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Offset = Vector2( -20, -14 );
		Menu::DefaultMenuInfo::MenuArrow_Selected_Size = Vector2( 45, 45 );
		Menu::DefaultMenuInfo::MenuArrow_Selected_Color = ( bColor( 255, 255, 255, 0 ) ).ToVector4();
		Menu::DefaultMenuInfo::SliderBack_Texture = Tools::Texture( std::wstring( L"menuslider_bar" ) );
		Menu::DefaultMenuInfo::SliderBack_Size = Vector2( 250, 35 );
		Menu::DefaultMenuInfo::Slider_Texture = Tools::Texture( std::wstring( L"menuslider_slider" ) );
		Menu::DefaultMenuInfo::Slider_StartPos = Vector2( -210, 0 );
		Menu::DefaultMenuInfo::Slider_EndPos = Vector2( 210, 0 );
		Menu::DefaultMenuInfo::Slider_Size = Vector2( 28, 55 );

		// Background
		Background::GreenScreen = false;
		Background::TestQuad = boost::make_shared<QuadClass>();
		Background::TestTexture = 0;

		// Challenge_HeroRush2
		Challenge_HeroRush2::HeroList = std::vector<HeroSpec>( );
		Challenge_HeroRush2::HeroList.reserve( 100 );
		Challenge_HeroRush2::instance = boost::make_shared<Challenge_HeroRush2>();

		CloudberryKingdomGame::TitleGameFactory = TitleGameData_MW::Factory;

		// Load campaign
		CampaignSequence::instance = boost::make_shared<CampaignSequence>();

		LeaderboardItem::StaticIntialize();

#ifdef BOOST_BIN
		MakeLocks();
#endif
	}






		bool CloudberryKingdomGame::ChoseNotToSave = false;
		bool CloudberryKingdomGame::PastPressStart = false;
		bool CloudberryKingdomGame::CanSave()
		{
			if ( getIsDemo() ) return false;

			if ( ChoseNotToSave ) return false;

			if ( !PastPressStart ) return false;

			return true;
		}

		bool CloudberryKingdomGame::CanSave( PlayerIndex index )
		{
			if ( !CanSave() ) return false;

			// Check if saving is ready

			return true;
		}

		void CloudberryKingdomGame::ShowError_CanNotSaveNoDevice()
		{
			//ShowError(Localization::Words_Err_StorageDeviceRequired, Localization::Words_Err_NoSaveDevice, Localization::Words_Err_Ok, null);
		}

		bool CloudberryKingdomGame::ProfilesAvailable()
		{
			// Check if the main player is signed in
			
			return true;
		}

		// FIXME: Make this function part of CloudberryKingdomGame.
		bool IsParentalLevelSatisfied( bool showError )
		{
#ifdef PS3
			if( IsOnlineContentRestricted() )
			{
				if( showError )
				{
					std::string str = WstringToUtf8( Localization::WordString( Localization::Words_OnlinePermission_PS3 ) );
					DisplayError( ErrorType( str ) );
				}
				return false;
			}
#endif
			return true;
		}

		bool CloudberryKingdomGame::OnlineFunctionalityAvailable()
        {
			// Check that online network is available

#ifdef PS3
			return IsNPAvailable();
#else
			return true;
			//return false;
#endif
		}

		void CloudberryKingdomGame::BeginShowMarketplace()
		{
            if ( CloudberryKingdomGame::OnlineFunctionalityAvailable() )
            {
				// Show the marketplace
            }
            else
            {
                CloudberryKingdomGame::ShowError_MustBeSignedIn( Localization::Words_Err_MustBeSignedIn );
            }
		}

		Presence CloudberryKingdomGame::CurrentPresence = Presence_TitleScreen;
		void CloudberryKingdomGame::SetPresence(Presence presence)
		{
			CurrentPresence = presence;
		}

		int CloudberryKingdomGame::Freeplay_Count = 0;
		int CloudberryKingdomGame::Freeplay_Max = 3;
















	CloudberryKingdomGame::ExitProxy::ExitProxy( const boost::shared_ptr<CloudberryKingdomGame> &ckg )
	{
		this->ckg = ckg;
	}

	void CloudberryKingdomGame::ExitProxy::Apply()
	{
		ckg->Exit();
	}

	void CloudberryKingdomGame::UpdateVolumeProxy::Apply()
	{
		Tools::UpdateVolume();
	}

	CloudberryKingdomGame::MakeTestLevelInitializeHelper::MakeTestLevelInitializeHelper( const boost::shared_ptr<CloudberryKingdomGame> &ckg )
	{
		this->ckg = ckg;
	}

	void CloudberryKingdomGame::MakeTestLevelInitializeHelper::Apply( const boost::shared_ptr<PieceSeedData> &piece )
	{
		ckg->TestLevelInit( piece );
	}

	CloudberryKingdomGame::TestLevelPostMakeProxy::TestLevelPostMakeProxy( const boost::shared_ptr<CloudberryKingdomGame> &ckg )
	{
		this->ckg = ckg;
	}

	void CloudberryKingdomGame::TestLevelPostMakeProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		ckg->TestLevelPostMake( level );
	}

Version CloudberryKingdomGame::GameVersion = Version( 0, 2, 4 );

		// Flags
		bool CloudberryKingdomGame::GodMode = true;
		bool CloudberryKingdomGame::AsianButtonSwitch = false;

#ifdef PC_VERSION
        // Steam Beta
		//bool CloudberryKingdomGame::HideLogos = true;
		//bool CloudberryKingdomGame::LockCampaign = true;
		//bool CloudberryKingdomGame::SimpleMainMenu = true;
		//bool CloudberryKingdomGame::PS3MainMenu = false;
		//MainMenuTypes CloudberryKingdomGame::MainMenuType = MainMenuTypes_PC;
		//bool CloudberryKingdomGame::SimpleLeaderboards = true;
		//bool CloudberryKingdomGame::FakeAwardments = false;

		// PC Beta
		bool CloudberryKingdomGame::HideLogos = false;
		bool CloudberryKingdomGame::LockCampaign = false;
		bool CloudberryKingdomGame::SimpleMainMenu = true;
		//MainMenuTypes CloudberryKingdomGame::MainMenuType = MainMenuTypes_PC;
		MainMenuTypes CloudberryKingdomGame::MainMenuType = MainMenuTypes_PS3;
		bool CloudberryKingdomGame::SimpleLeaderboards = false;
		bool CloudberryKingdomGame::FakeAwardments = false;
		float CloudberryKingdomGame::GuiSqueeze = 0;
#elif XBOX
		bool CloudberryKingdomGame::HideLogos = false;
		bool CloudberryKingdomGame::LockCampaign = false;
		bool CloudberryKingdomGame::SimpleMainMenu = false;
		MainMenuTypes CloudberryKingdomGame::MainMenuType = MainMenuTypes_Xbox;
		bool CloudberryKingdomGame::SimpleLeaderboards = false;
		bool CloudberryKingdomGame::FakeAwardments = false;
		float CloudberryKingdomGame::GuiSqueeze = 0.3f;
#elif CAFE
		bool CloudberryKingdomGame::HideLogos = false;
		bool CloudberryKingdomGame::LockCampaign = false;
		bool CloudberryKingdomGame::SimpleMainMenu = true;
		MainMenuTypes CloudberryKingdomGame::MainMenuType = MainMenuTypes_WiiU;
		bool CloudberryKingdomGame::SimpleLeaderboards = true;
		bool CloudberryKingdomGame::FakeAwardments = false;
		float CloudberryKingdomGame::GuiSqueeze = 1.0f;
#elif PS3
		bool CloudberryKingdomGame::HideLogos = false;
		bool CloudberryKingdomGame::LockCampaign = false;
		bool CloudberryKingdomGame::SimpleMainMenu = true;
		MainMenuTypes CloudberryKingdomGame::MainMenuType = MainMenuTypes_PS3;
		bool CloudberryKingdomGame::SimpleLeaderboards = false;
		bool CloudberryKingdomGame::FakeAwardments = false;
		float CloudberryKingdomGame::GuiSqueeze = 1.0f;
#endif




		bool ForFrapsRecording = false;

#if defined(DEBUG)
        bool CloudberryKingdomGame::AlwaysGiveTutorials = true;
        bool CloudberryKingdomGame::Unlock_Customization = true;
        bool CloudberryKingdomGame::Unlock_Levels = true;
#else
        bool CloudberryKingdomGame::AlwaysGiveTutorials = false;
        bool CloudberryKingdomGame::Unlock_Customization = true;
        bool CloudberryKingdomGame::Unlock_Levels = false;
#endif

        bool FakeDemo = false;
        bool CloudberryKingdomGame::getIsDemo()
        {
			if (FakeDemo) return true;

			return false;
		}

        static void OfferToBuy()
        {
//#ifdef XBOX
//            if (gamer.Privileges.AllowPurchaseContent)
//            {
//                Guide.ShowMarketplace(gamer.PlayerIndex);
//                return;
//            }
//
//            foreach (SignedInGamer _gamer in Gamer.SignedInGamers)
//            {
//                if (_gamer.Privileges.AllowPurchaseContent)
//                {
//                    Guide.ShowMarketplace(_gamer.PlayerIndex);
//                    return;
//                }
//            }
//#endif
        }



bool CloudberryKingdomGame::StartAsBackgroundEditor = false;
bool CloudberryKingdomGame::StartAsTestLevel = false;
bool CloudberryKingdomGame::StartAsBobAnimationTest = false;
bool CloudberryKingdomGame::StartAsFreeplay = false;
#if defined(INCLUDE_EDITOR)
bool CloudberryKingdomGame::LoadDynamic = true;
#endif

#if ! defined(INCLUDE_EDITOR)
bool CloudberryKingdomGame::LoadDynamic = false;
#endif

bool CloudberryKingdomGame::ShowSongInfo = true;
std::wstring CloudberryKingdomGame::TileSetToTest = std::wstring( L"cave" );
std::wstring CloudberryKingdomGame::ModRoot = std::wstring( L"Standard" );
bool CloudberryKingdomGame::AlwaysSkipDynamicArt = false;
bool CloudberryKingdomGame::HideGui = false;
bool CloudberryKingdomGame::HideForeground = false;
bool CloudberryKingdomGame::UseNewBob = false;
boost::shared_ptr<SimpleGameFactory> CloudberryKingdomGame::TitleGameFactory;
float CloudberryKingdomGame::fps = 0;

#if defined(WINDOWS)
	const bool &CloudberryKingdomGame::getDrawMouseBackIcon() const
	{
		return _DrawMouseBackIcon;
	}
#endif

#if defined(WINDOWS)
	void CloudberryKingdomGame::setDrawMouseBackIcon( const bool &value )
	{
		_DrawMouseBackIcon = value;
	}
#endif

	void CloudberryKingdomGame::Exit()
	{
		Tools::GameClass->Exit();
	}

	void CloudberryKingdomGame::ProcessArgs( std::vector<std::wstring> &args )
	{
	#if defined(DEBUG)
		// Artifically simulate different command line arguments.
		//args = new string[] { "test_bob_animation", "mod_root", "Bob" };
		//args = new string[] { "test_level" }; AlwaysSkipDynamicArt = true;
		//args = new string[] { "background_editor" }; //AlwaysSkipDynamicArt = true;
		//args = new string[] { "test_all" }; AlwaysSkipDynamicArt = false;
		//StartAsTestLevel = true;
	#endif
		//args = new string[] { "test_all" }; AlwaysSkipDynamicArt = false;

		LoadDynamic = false;
		AlwaysSkipDynamicArt = true;
	}

	CloudberryKingdomGame::CloudberryKingdomGame()
	{
		//Tools::GameClass = boost::make_shared<XnaGameClass>();

		CloudberryKingdomGame::StaticIntializer_NoDependence();

		InitializeInstanceFields();
		/*MyGraphicsDeviceManager = boost::make_shared<GraphicsDeviceManager>( Tools::GameClass );*/
		MyGraphicsDeviceManager = boost::make_shared<GraphicsDeviceManager>();

		// FIXME: This is an event that hooks in to whenever the game has to prepare a device (usually after losing it). Do we need this?
		//MyGraphicsDeviceManager->PreparingDeviceSettings += boost::make_shared<EventHandler<PreparingDeviceSettingsEventArgs*> >( shared_from_this(), &CloudberryKingdomGame::graphics_PreparingDeviceSettings );

		// Pull these out, so they aren't inside the constructor.
		//Tools::GameClass->getContent()->RootDirectory = std::wstring( L"Content" );
		//Tools::TheGame = shared_from_this();
	}

	void CloudberryKingdomGame::graphics_PreparingDeviceSettings( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<PreparingDeviceSettingsEventArgs> &e )
	{
		//graphics.PreferMultiSampling = false;
		//graphics.MyGraphicsDevice.PresentationParameters.MultiSampleCount = 16;

		//graphics.PreferMultiSampling = true;
		//graphics.MyGraphicsDevice.PresentationParameters.MultiSampleCount = 16;
	}

	void CloudberryKingdomGame::Initialize()
	{
	//#if defined(WINDOWS)
	//	EventInput::Initialize( Tools::GameClass->getWindow() );
	//#endif
#if defined(PC_VERSION)
		Globals::ContentDirectory = Tools::GameClass->getContent()->RootDirectory;
#else
		Globals::ContentDirectory = L"" ;
#endif

		Tools::LoadEffects( Tools::GameClass->getContent(), true );

		ButtonString::Init();
		ButtonCheck::Reset();

		// Fill the pools
		ComputerRecording::InitPool();
	}

	void CloudberryKingdomGame::InitialResolution()
	{
	#if defined(PC_VERSION)
		// The PC version let's the player specify resolution, key mapping, and so on.
		// Try to load these now.
		RezData rez;

		//PlayerManager::Players[0] = boost::make_shared<PlayerData>();
		//PlayerManager::Players[0]->Init();

		//PlayerManager::getPlayer()->ContainerName = L"SaveData";
		//PlayerManager::getPlayer()->FileName = L"SaveData->bam";
		//PlayerManager::getPlayer()->Load( /*PlayerManager::getPlayer()->MyPlayerIndex*/ );

		//SaveGroup::LoadAll();
		//PlayerManager::getPlayer()->Load( /*PlayerIndex_One*/ );

		rez = PlayerManager::LoadRezAndKeys();

	#elif defined(WINDOWS)
		RezData rez = RezData();
		rez.Custom = true;
	#if defined(DEBUG) || defined(INCLUDE_EDITOR)
		rez.Fullscreen = false;
	#else
		rez.Fullscreen = true;
	#endif

	#if defined(WINDOWS)
		rez.Width = 1280;
		rez.Height = 720;
	#else
		rez.Width = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Width;
		rez.Height = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Height;
	#endif

	#endif

		// Some possible resolutions.
		Resolutions[ 0 ] = ResolutionGroup();
		Resolutions[ 0 ].Backbuffer = IntVector2( 1280, 800 );
		Resolutions[ 0 ].Bob_Renamed = IntVector2( 135, 0 );
		Resolutions[ 0 ].TextOrigin = Vector2();
		Resolutions[ 0 ].LineHeightMod = 1;

		Resolutions[ 0 ].CopyTo( Resolutions[ 1 ] );
		Resolutions[ 1 ].Backbuffer = IntVector2( 1280, 786 );

		Resolutions[ 0 ].CopyTo( Resolutions[ 2 ] );
		Resolutions[ 2 ].Backbuffer = IntVector2( 1280, 720 );

		Resolutions[ 0 ].CopyTo( Resolutions[ 3 ] );
		Resolutions[ 3 ].Backbuffer = IntVector2( 640, 360 );

		// Set the default resolution
		Resolution = Resolutions[ 2 ];

		MyGraphicsDeviceManager->PreferredBackBufferWidth = Resolution.Backbuffer.X;
		MyGraphicsDeviceManager->PreferredBackBufferHeight = Resolution.Backbuffer.Y;
		// FIXME: We want to synchronize with the vertical retrace. Important!
		//MyGraphicsDeviceManager->SynchronizeWithVerticalRetrace = true;

		// Set the actual graphics device,
		// based on the resolution preferences established above.
	#if defined(PC_VERSION) || defined(WINDOWS)
		if ( rez.Custom )
		{
			if ( !rez.Fullscreen )
			{
				rez.Height = static_cast<int>( ( 720.f / 1280.f ) * rez.Width );
			}

			MyGraphicsDeviceManager->PreferredBackBufferWidth = rez.Width;
			MyGraphicsDeviceManager->PreferredBackBufferHeight = rez.Height;
			MyGraphicsDeviceManager->IsFullScreen = rez.Fullscreen;
		}
		else
		{
			// FIXME: This should grab the preferred resolution for the game.
			//MyGraphicsDeviceManager->PreferredBackBufferWidth = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Width;
			//MyGraphicsDeviceManager->PreferredBackBufferHeight = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Height;
			MyGraphicsDeviceManager->IsFullScreen = false;
		}
	#if defined(DEBUG) || defined(INCLUDE_EDITOR)
		if ( !MyGraphicsDeviceManager->IsFullScreen )
		{
			MyGraphicsDeviceManager->PreferredBackBufferWidth = 1280;
			MyGraphicsDeviceManager->PreferredBackBufferHeight = 720;
		}
	#endif
	#endif

	#if defined(DEBUG)
		//// 640x480
		//MyGraphicsDeviceManager.PreferredBackBufferWidth = 640;
		//MyGraphicsDeviceManager.PreferredBackBufferHeight = 480;
		//// 1280x720
		MyGraphicsDeviceManager->PreferredBackBufferWidth = 1280;
		MyGraphicsDeviceManager->PreferredBackBufferHeight = 720;
		MyGraphicsDeviceManager->IsFullScreen = false;
	#endif
		MyGraphicsDeviceManager->PreferredBackBufferWidth = 1280;
		MyGraphicsDeviceManager->PreferredBackBufferHeight = 720;
		MyGraphicsDeviceManager->IsFullScreen = false;


	#if defined(WINDOWS)
		Tools::GameClass->SetBorder( Tools::WindowBorder );
	#endif

		MyGraphicsDeviceManager->ApplyChanges();

		fps = 0;
	}

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void CloudberryKingdomGame::SignedInGamer_SignedOut( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedOutEventArgs> &e )
	{
		SaveGroup::SaveAll();

		if ( Tools::CurGameData != 0 )
			Tools::CurGameData->OnSignOut( e );
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void CloudberryKingdomGame::SignedInGamer_SignedIn( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedInEventArgs> &e )
	{
		int Index = static_cast<int>( e->Gamer->PlayerIndex );
		std::wstring Name = e->Gamer->Gamertag;

		boost::shared_ptr<PlayerData> data = boost::make_shared<PlayerData>();
		data->Init( Index );
		PlayerManager::Players[ Index ] = data;

		SaveGroup::LoadGamer( Name, data );
	}
#endif

	void CloudberryKingdomGame::LoadContent()
	{
		boost::shared_ptr<CloudberryKingdom::CloudberryKingdomGame> Ck = Tools::TheGame;

		//BenchmarkLoadSize();
		//Tools::Warning();

		MyGraphicsDevice = MyGraphicsDeviceManager->MyGraphicsDevice;

		Tools::LoadBasicArt( Tools::GameClass->getContent() );

		Tools::Render = boost::make_shared<MainRender>( MyGraphicsDevice );

		Tools::QDrawer = boost::make_shared<QuadDrawer>( MyGraphicsDevice, 1000 );
		Tools::QDrawer->DefaultEffect = Tools::EffectWad->FindByName( std::wstring( L"NoTexture" ) );
		Tools::QDrawer->DefaultTexture = Tools::TextureWad->FindByName( std::wstring( L"White" ) );

		Tools::Device = MyGraphicsDevice;
		Tools::t = 0;

		LogoScreenUp = true;


		/*Tools::Render->MySpriteBatch = boost::make_shared<SpriteBatch>( MyGraphicsDevice );*/
		Tools::Render->MySpriteBatch = boost::make_shared<SpriteBatch>();

		ScreenWidth = MyGraphicsDevice->PP->BackBufferWidth;
		ScreenHeight = MyGraphicsDevice->PP->BackBufferHeight;

		MainCamera = boost::make_shared<Camera>( ScreenWidth, ScreenHeight );

		MainCamera->Update();

		// Pre load. This happens before anything appears.
		Resources::LoadAssets( true );

		// Initialize players
		PlayerManager::Init();

		// Initialize heroes
		BobPhsx::CustomPhsxData::InitStatic();

		// Load saved files
		// FIXME: Need to make sure when we read strings we do it invariantly across cultures.
		//Thread::CurrentThread->CurrentCulture = System::Globalization::CultureInfo::InvariantCulture;
		SaveGroup::Initialize();

		// Benchmarking and preprocessing
		//PreprocessArt();
		//BenchmarkAll();
		//Tools::Warning(); return;

		//_LoadThread(); return;

		// Create the initial loading screen
		LoadingScreen_Renamed = boost::make_shared<InitialLoadingScreen>( Tools::GameClass->getContent(), Resources::ResourceLoadedCountRef );

		// Load resource thread
		Resources::LoadResources();

	#if defined(WINDOWS)
		// FIXME: Small delay/sleep.
		//delay( 2 );
	#endif

	#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
		SignedInGamer::SignedIn += boost::make_shared<EventHandler<SignedInEventArgs*> >( shared_from_this(), &CloudberryKingdomGame::SignedInGamer_SignedIn );
		SignedInGamer::SignedOut += boost::make_shared<EventHandler<SignedOutEventArgs*> >( shared_from_this(), &CloudberryKingdomGame::SignedInGamer_SignedOut );
	#endif

		
		ConsoleRegion region = GetConsoleRegion();

#if PS3
		CloudberryKingdomGame::AsianButtonSwitch = IsAsianButtonConfiguration();
#else
		CloudberryKingdomGame::AsianButtonSwitch = false;
#endif

		// FIXME: Start videos later.
		if (!HideLogos)
		{
			// FIXME: Keep playing logo salad.
			if( CloudberryKingdomGame::getIsDemo() && region == ConsoleRegion_USA )
				MainVideo::StartVideo_CanSkipIfWatched( std::wstring( L"LogoSalad_ESRB" ) );
			else
				MainVideo::StartVideo_CanSkipIfWatched( std::wstring( L"LogoSalad" ) );
		}
	}

	void CloudberryKingdomGame::UnloadContent()
	{
		// TODO: Unload any non ContentManager content here
	}

	void CloudberryKingdomGame::DoQuickSpawn()
	{
		if ( Tools::CurLevel->ResetEnabled() && Tools::CurLevel->PlayMode == 0 && !Tools::CurLevel->Watching && !Tools::CurGameData->PauseGame && Tools::CurGameData->QuickSpawnEnabled() )
		{
			// Note that quickspawn was used, hence we should not give hints to the player to use Quick Spawn in the future.
			Hints::SetQuickSpawnNum( 999 );

			// Don't count reset against player if it happens within the first half second
			if ( Tools::CurLevel->CurPhsxStep < 30 )
				Tools::CurLevel->FreeReset = true;

			// Update player stats
			Tools::CurLevel->CountReset();

			Tools::CurLevel->setSetToReset( true );
		}
	}

	const boost::shared_ptr<GameData> &CloudberryKingdomGame::getGame() const
	{
		return Tools::CurGameData;
	}

	void CloudberryKingdomGame::DoGameDataPhsx()
	{
		Tools::PhsxCount++;

		if ( Tools::WorldMap != 0 )
			Tools::WorldMap->BackgroundPhsx();

		if ( getGame() != 0 )
		{
			for ( int i = 0; i < getGame()->PhsxStepsToDo; i++ )
			{
				EzSoundWad::SuppressSounds = ( getGame()->SuppressSoundForExtraSteps && i < getGame()->PhsxStepsToDo - 1 );
				getGame()->PhsxStep();
			}
			getGame()->PhsxStepsToDo = 1;
		}
	}

	void CloudberryKingdomGame::DoToDoList()
	{
		ToDo->Apply();
		ToDo->Clear();
	}

    void CloudberryKingdomGame::GodModePhxs()
    {
#ifdef BOOST_BIN
        if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_D ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_D ) )
		{
			Stats();
		}
#endif

        // Write to leaderboard
        Tools::Warning();
#ifdef PC_VERSION
        if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_J ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_J ) )
#else
		if ( ButtonCheck::State( ControllerButtons_RJ, -2 ).Down && ButtonCheck::State( ControllerButtons_LS, -2).Pressed )
#endif
        {
            boost::shared_ptr<ScoreEntry> se = boost::make_shared<ScoreEntry>( std::wstring( L"FakeName Nahnah!" ), 0, 100, 200, 300, 400, 500, 600 );
            Leaderboard::WriteToLeaderboard( se );
        }

        // Give 100,000 points to each player
#ifdef PC_VERSION
        if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_I ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_I ) )
#else
		if ( ButtonCheck::State( ControllerButtons_LJ, -2 ).Down && ButtonCheck::State( ControllerButtons_RJ, -2).Pressed )
#endif
        {
			for ( BobVec::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			{
				( *bob )->getMyStats()->Score += 100000;
			}
        }

        // Kill everyone but Player One
#ifdef PC_VERSION
        if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_U ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_U ) )
#else
		if ( ButtonCheck::State( ControllerButtons_LJ, -2 ).Down && ButtonCheck::State( ControllerButtons_X, -2).Down )
#endif
        {
			for ( BobVec::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			{
                if (( *bob )->MyPlayerIndex != 0 && !(( *bob )->Dead || ( *bob )->Dying))
                {
                    //Fireball.Explosion(bob.Core.Data.Position, bob.Core.MyLevel);
                    //Fireball.ExplodeSound.Play();

                    //bob.Core.Show = false;
                    //bob.Dead = true;

                    ( *bob )->Die( BobDeathType_OTHER, true, false);
                }
            }
        }

        // Turn on/off flying.
#ifdef PC_VERSION
        if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_O ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_O ) )
#else
		if ( ButtonCheck::State( ControllerButtons_LJ, -2 ).Down && ButtonCheck::State( ControllerButtons_A, -2).Pressed )
#endif
        {
			for ( BobVec::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			{
                ( *bob )->Flying = !( *bob )->Flying;
            }
        }

        // Go to last door
#ifdef PC_VERSION
        if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_P ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_P ) )
#else
		if ( ButtonCheck::State( ControllerButtons_LJ, -2 ).Down && ButtonCheck::State( ControllerButtons_B, -2).Down )
#endif
        {
            // Find last door
            if ( Tools::CurLevel != 0 )
            {
                boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( Tools::CurLevel->FindIObject( LevelConnector::EndOfLevelCode ) );

                if (0 != door)
                {
                    for ( BobVec::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
                    {
                        ( *bob )->Immortal = true;
                        Tools::MoveTo( ( *bob ), door->getPos() );
                    }

					for ( ObjectVec::const_iterator obj = Tools::CurLevel->Objects.begin(); obj != Tools::CurLevel->Objects.end(); obj++ )
                    {
                        boost::shared_ptr<CameraZone> zone = boost::dynamic_pointer_cast<CameraZone>( ( *obj ) );
                            
						if ( 0 != zone )
                        {
                            if (Tools::CurLevel->getMainCamera()->MyZone == 0 ||
                                Tools::CurLevel->getMainCamera()->MyZone->Box->Current->BL.X <= zone->Box->Current->BL.X)
                            {
                                Tools::CurLevel->getMainCamera()->MyZone = zone;
                                Tools::CurLevel->getMainCamera()->setPos( zone->End );
                            }
                        }
                    }
                }
            }
        }
    }

	void CloudberryKingdomGame::PhsxStep()
	{
		DoToDoList();
#if defined(WINDOWS)
	#if defined(PC_DEBUG) || (defined(WINDOWS) && defined(DEBUG)) || defined(INCLUDE_EDITOR)
		// Debug tools
		if ( DebugModePhsx() )
			return;
	#endif

	#if defined(DEBUG)
        GodModePhxs();
	#else
        if (GodMode)
            GodModePhxs();
	#endif


		// Do game update.
		if ( !Tools::StepControl || ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Enter ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_Enter ) ) )
		{
			DoGameDataPhsx();
		}
		else if ( Tools::CurLevel != 0 )
			Tools::CurLevel->IndependentDeltaT = 0;

	#if defined(WINDOWS)
		// Quick Spawn
		CheckForQuickSpawn_PC();
	#endif
#else

	#if defined(DEBUG)
		GodModePhxs();
	#else
		if (GodMode)
			GodModePhxs();
	#endif

		DoGameDataPhsx();
#endif

		// Quick Spawn: Note, we must check this for PC version too, since PC players may use game pads.
		CheckForQuickSpawn_Xbox();

		// Finish updating the controlls; swap current to previous.
		ButtonCheck::UpdateControllerAndKeyboard_EndOfStep( Resolution );

		// Update the fireball textures.
		Fireball::TexturePhsx();
	}

#if defined(WINDOWS)
	void CloudberryKingdomGame::CheckForQuickSpawn_PC()
	{
		// Should implement a GameObject that marshalls quickspawns instead.
		Tools::Warning();

		if ( !KeyboardExtension::Freeze && Tools::CurLevel->ResetEnabled() && KeyboardExtension::IsKeyDownCustom(Tools::Keyboard, ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey) )
			DoQuickSpawn();
	}
#endif

	void CloudberryKingdomGame::CheckForQuickSpawn_Xbox()
	{
		// Check for quick spawn on Xbox. This allows the player to reset a level rapidly.
		// For XBox this is done by holding both shoulder buttons.
		bool ShortReset = false;
		for ( int i = 0; i < 4; i++ )
		{
			if ( PlayerManager::Get( i )->Exists )
			{
				if ( Tools::GamepadState[ i ].Buttons.LeftShoulder == ButtonState_Pressed && Tools::GamepadState[ i ].Buttons.RightShoulder == ButtonState_Pressed && ( Tools::PrevGamepadState[ i ].Buttons.LeftShoulder != ButtonState_Pressed || Tools::PrevGamepadState[ i ].Buttons.RightShoulder != ButtonState_Pressed ) )
					ShortReset = true;
			}
		}

		// Do the quick spawn if it was chosen by the player.
		if ( ShortReset )
		{
			for ( int i = 0; i < 4; i++ )
			{
				if ( PlayerManager::Get( i )->Exists && PlayerManager::Get( i )->IsAlive )
				{
					if ( Tools::GamepadState[ i ].Buttons.LeftShoulder != ButtonState_Pressed && Tools::GamepadState[ i ].Buttons.RightShoulder != ButtonState_Pressed )
						ShortReset = false;
				}
			}

			if ( ShortReset && Tools::CurLevel->ResetEnabled() )
				DoQuickSpawn();
		}
	}

#if defined(WINDOWS)
	void CloudberryKingdomGame::MouseDraw()
	{
		if ( !ButtonCheck::MouseInUse )
			return;
		if ( MousePointer == 0 )
			return;

		Vector2 Pos = Tools::MouseWorldPos();

		// Draw the mouse hand
		MousePointer->setPos( Pos + Vector2( .905f * MousePointer->getSize().X, -.705f * MousePointer->getSize().Y ) );
		MousePointer->Draw();

		// Draw the mouse dot
		Tools::QDrawer->DrawSquareDot( Pos, Color::Black, 8 );

		// Draw the mouse back icon
		//if (DrawMouseBackIcon)
		//{
		//    MouseBack.Pos = MousePointer.Pos + new Vector2(44, 98);
		//    MouseBack.Draw();
		//}

		Tools::QDrawer->Flush();
	}
#endif

	void CloudberryKingdomGame::Update()
	{
		//var TargetElapsedTime = new TimeSpan(0, 0, 0, 0, (int)(1000f / 60f));
		//var TargetElapsedTime = new TimeSpan(0, 0, 0, 0, (int)(1000f / 10f));
		//Tools::GameClass.TargetElapsedTime = TargetElapsedTime;
		//Tools::GameClass.IsFixedTimeStep = true;
	}







		bool CloudberryKingdomGame::ShowMarketplace = false;

#if XBOX
        bool CloudberryKingdomGame::ShowKeyboard = false;
        bool CloudberryKingdomGame::KeyboardIsDone = false;
		bool CloudberryKingdomGame::ShowAchievements = false;
        PlayerIndex CloudberryKingdomGame::ShowFor = PlayerIndex.One;

		void CloudberryKingdomGame::BeginShowAchievements()
		{
			ShowAchievements = false;
#if XDK
            try
            {
                GuideExtensions.ShowAchievements(ShowFor);
            }
            catch
            {
            }
#endif
		}
#endif

        bool CloudberryKingdomGame::ShowErrorMessage;

		void CloudberryKingdomGame::ShowError_LoadError()
		{
#if PC_VERSION
#else

	#ifdef PS3
			ShowError(Localization::Words_Err_CorruptLoadHeader, Localization::Words_Err_PS3_CorruptLoad, Localization::Words_Err_Ok);
	#else
			ShowError(Localization::Words_Err_CorruptLoadHeader, Localization::Words_Err_CorruptLoad, Localization::Words_Err_Ok);
	#endif

#endif
		}

		void CloudberryKingdomGame::ShowError_MustBeSignedIn(Localization::Words word)
		{
#if PC_VERSION
#else
			ShowError(Localization::Words_Err_MustBeSignedIn_Header, word, Localization::Words_Err_Ok);
#endif
		}

#ifdef PS3
		void DecideToSignInCallback( bool yes )
		{
			if( yes )
			{
				CellNetCtlNetStartDialogParam param;
				param.size = sizeof( param );
				param.type = CELL_NET_CTL_NETSTART_TYPE_NP;
				param.cid = 0; // Unused.
				int ret = cellNetCtlNetStartDialogLoadAsync( &param );
				if( ret < 0 )
					LOG.Write( "Failed to start network connection dialog: 0x%x\n", ret );
			}
		}
#endif

        void CloudberryKingdomGame::ShowError_MustBeSignedInToLive(Localization::Words word)
        {
#if PC_VERSION
#elif PS3
			DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_PsnRequired_AskToSignIn ) ),
				DecideToSignInCallback, ErrorType::YESNO ) );
#else
            ShowError(Localization::Words_Err_MustBeSignedInToLive_Header, word, Localization::Words_Err_Ok);
#endif
        }

        void CloudberryKingdomGame::ShowError_MustBeSignedInToLiveForLeaderboard()
        {
#if PC_VERSION
#elif PS3
			DisplayError( ErrorType( WstringToUtf8( Localization::WordString( Localization::Words_Err_PS3_PsnRequired_WillUploadLater ) ) ) );
#else
            ShowError(Localization::Words_Err_MustBeSignedInToLive_Header, Localization::Words_Err_MustBeSignedInToLiveForLeaderboards, Localization::Words_Err_Ok);
#endif
        }

        bool CloudberryKingdomGame::IsNetworkCableUnplugged()
        {
#if XDK
            return GuideExtensions.IsNetworkCableUnplugged;
#else
            return true;
#endif
        }

        void CloudberryKingdomGame::ShowError(Localization::Words Header, Localization::Words Text, Localization::Words Option1/*, AsyncCallback callback*/)
        {
#if XBOX
            ShowErrorMessage = true;

            Err_Header = Header;
            Err_Text = Text;
            //Err_Callback = callback;
            Err_Options.clear();
			Err_Options.push_back( Localization::WordString(Option1) );
#elif PS3
			DisplayError( ErrorType( WstringToUtf8( Localization::WordString(Text) ) ) );
#endif
        }

        Localization::Words CloudberryKingdomGame::Err_Header, CloudberryKingdomGame::Err_Text;
        std::vector<std::wstring> CloudberryKingdomGame::Err_Options;
        //AsyncCallback Err_Callback;

        void CloudberryKingdomGame::_ShowError()
        {
            ShowErrorMessage = false;

#if XDK || XBOX
            try
            {
                Guide.BeginShowMessageBox(Localization::WordString(Err_Header), Localization::WordString(Err_Text), Err_Options,
                    0, MessageBoxIcon.None, Err_Callback, null);
            }
            catch (Exception e)
            {
            }
#endif
        }

		static bool ClearError()
		{
			ButtonCheck::UpdateControllerAndKeyboard_StartOfStep();

			int numConnected = 0;
			for( int i = 0; i < 4; ++i )
			{
				if( Tools::GamepadState[i].IsConnected )
					numConnected++;
			}

			if( numConnected == 0 )
				return false;

			for (int i = 0; i < 4; i++)
			{
				if ( ( PlayerManager::Players[i] != 0 ) && PlayerManager::Players[i]->Exists && !Tools::GamepadState[i].IsConnected )
				{
					return false;
				}
			}

			return true;
		}

		bool CloudberryKingdomGame::DisconnectedController()
		{
#if PC_VERSION
			return false;
#endif

			if( !PastPressStart )
				return false;

			int numConnected = 0;
			for( int i = 0; i < 4; ++i )
			{
				if( Tools::GamepadState[i].IsConnected )
					numConnected++;
			}

			if( numConnected == 0 )
				return true;

			if( CurrentPresence != Presence_TitleScreen )
			{
				for (int i = 0; i < 4; i++)
				{
					if ( ( PlayerManager::Players[i] != 0 ) && PlayerManager::Players[i]->Exists && !Tools::GamepadState[i].IsConnected )
					{
						return true;
					}
				}
			}

			return false;
		}

#if XBOX
        bool ShowGamer;
        PlayerIndex ShowGamer_Index;
        Gamer ShowGamer_Gamer;
        void CloudberryKingdomGame::ShowGamerCard(PlayerIndex player, Gamer gamer)
        {
            ShowGamer = true;
            ShowGamer_Index = player;
            ShowGamer_Gamer = gamer;
        }

        void CloudberryKingdomGame::BeginShowGamer()
        {
            ShowGamer = false;
            if (ShowGamer_Gamer == null) return;

            Guide.ShowGamerCard(ShowGamer_Index, ShowGamer_Gamer);
        }
#endif

		bool CloudberryKingdomGame::getSuperPause()
		{
			return SmallErrorMessage != 0 || IsSystemMenuVisible();
		}
        boost::shared_ptr<SmallErrorMenu> CloudberryKingdomGame::SmallErrorMessage;
        void CloudberryKingdomGame::ShowSmallError()
        {
            if ( SmallErrorMessage != 0 ) return;
			if ( Tools::CurGameData == 0 ) return;

            //SmallErrorMessage = MakeMagic( SmallErrorMenu, ( Localization::Err_ControllerNotConnected ) );
			//Tools::CurGameData->AddGameObject( SmallErrorMessage );
        }

        bool CloudberryKingdomGame::CustomMusicPlaying = false;
        void CloudberryKingdomGame::UpdateCustomMusic()
        {
			if( IsCustomMusicPlaying() )
			{
				CustomMusicPlaying = true;
			}
			else
			{
				if( CustomMusicPlaying )
				{
					if( Tools::SongWad )
						Tools::SongWad->Restart( true, false );

					CustomMusicPlaying = false;
				}
			}
//#if XDK
//            if (!MediaPlayer.GameHasControl)
//            {
//                CustomMusicPlaying = true;
//            }
//            else
//            {
//                if (CustomMusicPlaying)
//                {
//                    if (Tools::SongWad != null)
//                        Tools::SongWad.Restart(true, false);
//
//                    CustomMusicPlaying = false;
//                }
//            }
//#endif
        }

        /// <summary>
        /// If a gamer has no save device selected, ask them to select one.
        /// </summary>
        void CloudberryKingdomGame::PromptForDeviceIfNoneSelected()
        {
            if ( CloudberryKingdomGame::getIsDemo() ) return;

        }








	void DrawWatermark()
	{
		if (Tools::QDrawer == 0) return;
		if (Resources::Font_Grobold42 == 0) return;
		if (Resources::Font_Grobold42->HFont == 0) return;
		if (Resources::Font_Grobold42->HOutlineFont == 0) return;

		boost::shared_ptr<Camera> cam = boost::make_shared<Camera>();
		cam->SetVertexCamera();
		Tools::QDrawer->DrawString( Resources::Font_Grobold42->HOutlineFont, L"Version 0.9.0", Vector2(1200, 870), Color::Black.ToVector4(), Vector2(.8f));
		Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, L"Version 0.9.0", Vector2(1200, 870), Color::SkyBlue.ToVector4(), Vector2(.8f));
		Tools::QDrawer->Flush();
	}



	void CloudberryKingdomGame::Draw( const boost::shared_ptr<GameTime> &gameTime )
	{
	#if defined(DEBUG_OBJDATA)
		ObjectData::UpdateWeak();
	#endif
		DeltaT = gameTime->ElapsedGameTime.getTotalSeconds();

		// Accelerate asset loading
		//if ( LogoScreenUp )
		//	Resources::LoadThread->Join( 1 );

#ifdef CAFE
		// Main Video
		if ( MainVideo::Draw() )
		{
			//DrawWatermark();
			return;
		}

		// Prepare to draw
		Tools::DrawCount++;
		if ( SetupToRender() )
		{
			DrawWatermark();
			return;
		}
#else
		// Prepare to draw
		Tools::DrawCount++;
		if ( SetupToRender() )
		{
			DrawWatermark();
			return;
		}

		// Main Video
		if ( MainVideo::Draw() )
		{
			DrawWatermark();
			return;
		}
#endif
		// Fps
		UpdateFps( gameTime );

		// Draw nothing if Xbox guide is up
#if defined(XBOX) || defined(XBOX_SIGNIN)
			if (Guide.IsVisible) { DrawNothing(); DrawWatermark(); return; }
            if (ShowKeyboard)
            {
                SaveLoadSeedMenu.BeginShowKeyboard();
            }
			else if (ShowAchievements)
			{
				BeginShowAchievements();
			}
            else if (ShowMarketplace)
            {
                BeginShowMarketplace();
            }
            else if (ShowErrorMessage)
            {
                _ShowError();
            }
            else if (ShowGamer)
            {
                BeginShowGamer();
            }
            else if (DisconnectedController())
            {
                ShowSmallError();
                //ButtonCheck.UpdateControllerAndKeyboard_StartOfStep();
                //return;
            }
            else
            {
                if (SmallErrorMessage != null)
                {
                    SmallErrorMessage.ReturnToCaller(true);
                    SmallErrorMessage = null;
                }
            }
#else
		if( DisconnectedController() )
		{
#ifdef CAFE
			if( WhoIsDisconnected == Who_VPAD )
			{
				DisplayError( ErrorType( 1650101,
					NULL, ErrorType::DEFAULT, ClearError, false ) );
			}
			else if( WhoIsDisconnected == Who_KPAD )
				DisplayError( ErrorType( 1520100,
					NULL, ErrorType::DEFAULT, ClearError, false ) );

			WhoIsDisconnected = Who_NOONE;
#elif PS3

			// Figure out which gamepad is disconnected.

			int controller = 0;

			int numConnected = 0;
			for( int i = 0; i < 4; ++i )
			{
				if( Tools::GamepadState[i].IsConnected )
					numConnected++;
			}

			if( numConnected == 0 )
				controller = 0;

			if( CurrentPresence != Presence_TitleScreen )
			{
				int i = 0;
				
				for (; i < 4; i++)
				{
					if ( ( PlayerManager::Players[i] != 0 ) && PlayerManager::Players[i]->Exists && !Tools::GamepadState[i].IsConnected )
						break;
				}

				controller = i;
			}

			DisplayError( ErrorType( WstringToUtf8(
				Format( Localization::WordString( Localization::Words_Err_PS3_NoGamePadDetected ).c_str(), controller + 1 ) ),
				NULL, ErrorType::NONE, ClearError, false ) );
#endif
		}
#endif

		UpdateCustomMusic();

		// What to do
		if ( LogoScreenUp )
			LogoPhsx();
		else if ( LogoScreenPropUp )
			LoadingScreen_Renamed->PhsxStep();
		if ( !LogoScreenUp && !Tools::CurGameData->Loading )
			GameUpdate( gameTime );

		// What to draw
		if ( LogoScreenUp || LogoScreenPropUp )
			LoadingScreen_Renamed->Draw();
		else if ( Tools::ShowLoadingScreen )
			DrawLoading();
		else if ( Tools::CurGameData != 0 )
			DrawGame();
		else
			DrawNothing();

		DrawExtra();

		DrawWatermark();
	}

	void CloudberryKingdomGame::DrawExtra()
	{
	#if defined(DEBUG)
		if ( ShowFPS || Tools::ShowNums )
			DrawDebugInfo();
	#endif

		Tools::Nothing();
	}

	void CloudberryKingdomGame::DrawLoading()
	{
		Tools::CurrentLoadingScreen->PreDraw();
		Tools::CurrentLoadingScreen->Draw( MainCamera );
	}

	void CloudberryKingdomGame::DrawNothing()
	{
		MyGraphicsDevice->Clear( Color::Black );
	}

	void CloudberryKingdomGame::DrawGame()
	{
		Tools::CurGameData->Draw();
		Tools::CurGameData->PostDraw();

		if ( Tools::CurLevel != 0 )
		{
			Tools::QDrawer->Flush();
			Tools::StartGUIDraw();

	#if defined(PC_VERSION)
			if ( !Tools::ShowLoadingScreen && ShowMouse )
				MouseDraw();
			ShowMouse = false;
	#endif

			if ( Tools::SongWad != 0 )
				Tools::SongWad->Draw();

			Tools::EndGUIDraw();
			Tools::QDrawer->Flush();
		}
	}

	void CloudberryKingdomGame::GameUpdate( const boost::shared_ptr<GameTime> &gameTime )
	{
		// Update controller/keyboard states
		ButtonCheck::UpdateControllerAndKeyboard_StartOfStep();

		// Update sounds
		if ( !LogoScreenUp )
			Tools::SoundWad->Update();

		// Update songs
		if ( Tools::SongWad != 0 )
			Tools::SongWad->PhsxStep();

		fps = .3f * fps + .7f * ( 1000 / static_cast<float>( __max( .00000231f, gameTime->ElapsedGameTime.getTotalMilliseconds() ) ) );

		// Determine how many phsx steps to take
		int Reps = 0;
		if ( Tools::getPhsxSpeed() == 0 && DrawCount % 2 == 0 )
			Reps = 1;
		else if ( Tools::getPhsxSpeed() == 1 )
			Reps = 1;
		else if ( Tools::getPhsxSpeed() == 2 )
			Reps = 2;
		else if ( Tools::getPhsxSpeed() == 3 )
			Reps = 4;

		// Do the phsx
		for ( int i = 0; i < Reps; i++ )
		{
			PhsxCount++;
			PhsxStep();
		}
	}

	void CloudberryKingdomGame::UpdateFps( const boost::shared_ptr<GameTime> &gameTime )
	{
		if( IsCustomMusicPlaying() )
			CustomMusicPlaying = true;

		// Track time, changes in time, and FPS
		Tools::gameTime = gameTime;
		DrawCount++;

		// Update fps
		float new_t = static_cast<float>( gameTime->TotalGameTime.getTotalSeconds() );
		Tools::dt = new_t - Tools::t;
		Tools::t = new_t;
	}

	bool CloudberryKingdomGame::SetupToRender()
	{
		// Set the viewport to the whole screen
		MyGraphicsDevice->VP = Viewport( 0.f, 0.f, static_cast<float>( MyGraphicsDevice->PP->BackBufferWidth ), static_cast<float>( MyGraphicsDevice->PP->BackBufferHeight ), 0.f, 1.f );

		// Clear whole screen to black
		MyGraphicsDevice->Clear( Color::Black );

	#if defined(WINDOWS)
		if ( !ActiveInactive() )
			return true;
	#endif

		// Make the actual view port we draw to, and clear it
		Tools::Render->MakeInnerViewport();
		MyGraphicsDevice->Clear( Color::Black );

		MyGraphicsDevice->VP = Tools::Render->MainViewport;

		// Default camera
		Vector4 cameraPos = Vector4( MainCamera->Data.Position.X, MainCamera->Data.Position.Y, MainCamera->getZoom().X, MainCamera->getZoom().Y ); //.001f, .001f);

		Tools::Render->SetStandardRenderStates();

		Tools::QDrawer->SetInitialState();

		ComputeFire();

		Tools::EffectWad->SetCameraPosition( cameraPos );

		Tools::SetDefaultEffectParams( MainCamera->AspectRatio );

		Tools::Render->SetStandardRenderStates();

		QUAD_DRAWER->SetEffect( Tools::BasicEffect->effect );

		return false;
	}

	void CloudberryKingdomGame::ComputeFire()
	{
		if ( !LogoScreenUp && !LogoScreenPropUp )
		{
			if ( !Tools::CurGameData->Loading && Tools::CurLevel->PlayMode == 0 && Tools::CurGameData != 0 && !Tools::CurGameData->Loading && ( !Tools::CurGameData->PauseGame || CharacterSelectManager::IsShowing ) )
			{
#if PC_VERSION
				Fireball::FireballTexture->_Tex = Tools::TextureWad->TextureList[0]->_Tex;
				Fireball::EmitterTexture->_Tex = Tools::TextureWad->TextureList[0]->_Tex;
				Fireball::FlameTexture->_Tex = Tools::TextureWad->TextureList[0]->_Tex;
#else
				// Compute fireballs textures
				MyGraphicsDevice->BlendState = GfxBlendState_Additive;
				Fireball::DrawFireballTexture( MyGraphicsDevice, Tools::EffectWad );
				Fireball::DrawEmitterTexture( MyGraphicsDevice, Tools::EffectWad );

				MyGraphicsDevice->BlendState = GfxBlendState_AlphaBlend;
#endif
			}
		}
	}

#if defined(WINDOWS)
	bool CloudberryKingdomGame::ActiveInactive()
	{
		if ( !Tools::GameClass->getIsActive() )
		{
			// The window isn't active, so
			// show the actual mouse (not our custom drawn mouse)
			Tools::GameClass->setIsMouseVisible( true );

			if ( FirstInactiveFrame )
			{
				// If a song is playing, stop it,
				// and note that we should resume once the window becomes active
				if ( Tools::SongWad != 0 && Tools::SongWad->IsPlaying() )
				{
					MediaPlaying_HoldState = true;
					MediaPlayer::Pause();
				}

				FirstInactiveFrame = false;
			}

			FirstActiveFrame = true;

			return false;
		}
		else
		{
			// The window is active, so
			// hide the actual mouse (we draw our own custom mouse in game)
			Tools::GameClass->setIsMouseVisible( false );

			if ( FirstActiveFrame )
			{
				// If a song was playing previously when the window was active before,
				// resume that song
				if ( MediaPlaying_HoldState )
					MediaPlayer::Resume();

				FirstActiveFrame = false;
			}

			FirstInactiveFrame = true;

			return true;
		}
	}
#endif

	void CloudberryKingdomGame::BenchmarkAll()
	{
		/*
		// Load art
		Start2();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Environments" ) );
		long long LoadEnviros = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Bob" ) );
		long long LoadBob = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Menu" ) );
		long long LoadMenus = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Coins" ) );
		//Tools::TextureWad.LoadFolder(Tools::GameClass.Content, "Effects");
		long long LoadEffects = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Buttons" ) );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Characters" ) );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"HeroItems" ) );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"LoadScreen_Initial" ) );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"LoadScreen_Level" ) );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Old Art Holdover" ) );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), std::wstring( L"Title" ) );
		long long LoadRest = Stop();

		Tools::Write( _T( "ArtMusic done..." ) );

		Start();
		TileSets::Init();
		long long Tiles = Stop();

		Start();
		Fireball::InitRenderTargets( MyGraphicsDevice, MyGraphicsDevice->PP, 300, 200 );
		ParticleEffects::Init();

		long long Particle_Renamed = Stop();

		Start();
		PlayerManager::Init();
		Awardments::Init();
		long long Players = Stop();

		// Load saved files
		Start();
		SaveGroup::Initialize();
		long long LoadSaves = Stop();

		Start();
		Prototypes::LoadObjects();
		long long Protos = Stop();

		Start();
		ObjectIcon::InitIcons();
		long long Icons = Stop();

		Tools::Write( _T( "Stickmen done..." ) );

		Start();
		Tools::GamepadState = std::vector<GamePadState>( 4 );
		Tools::PrevGamepadState = std::vector<GamePadState>( 4 );
		long long GamePads = Stop();

		long long Total = Stop2();

		Tools::Write( _T( "Textures done..." ) );

		//Console.WriteLine("Pre load       {0}", PreLoad);
		std::cout << _T( "Load Bob       " ) << LoadBob << std::endl;
		std::cout << _T( "Load enviros   " ) << LoadEnviros << std::endl;
		std::cout << _T( "Load effects   " ) << LoadEffects << std::endl;
		std::cout << _T( "Load menus     " ) << LoadMenus << std::endl;
		std::cout << _T( "Load rest      " ) << LoadRest << std::endl;
		std::cout << _T( "Load tiles     " ) << Tiles << std::endl;
		//std::cout << _T( "Load particles " ) << Particle << std::endl;
		std::cout << _T( "Load players   " ) << Players << std::endl;
		std::cout << _T( "Load saves     " ) << LoadSaves << std::endl;
		std::cout << _T( "Load Protos    " ) << Protos << std::endl;
		std::cout << _T( "Load Icons     " ) << Icons << std::endl;
		std::cout << _T( "Load Small     " ) << GamePads << std::endl;
		std::cout << std::endl;
		std::cout << _T( "Total          " ) << Total << std::endl;
		std::cout << _T( "" ) << std::endl;
		*/
	}

	boost::shared_ptr<Stopwatch> CloudberryKingdomGame::stopwatch = 0;

	void CloudberryKingdomGame::Start()
	{
		stopwatch = boost::make_shared<Stopwatch>();
		stopwatch->Start();
	}

	long long CloudberryKingdomGame::Stop()
	{
		stopwatch->Stop();
		return stopwatch->ElapsedTicks;
	}

	boost::shared_ptr<Stopwatch> CloudberryKingdomGame::stopwatch2 = 0;

	void CloudberryKingdomGame::Start2()
	{
		stopwatch2 = boost::make_shared<Stopwatch>();
		stopwatch2->Start();
	}

	long long CloudberryKingdomGame::Stop2()
	{
		stopwatch2->Stop();
		return stopwatch2->ElapsedTicks;
	}

	void CloudberryKingdomGame::BenchmarkLoadSize()
	{
		std::wcout << Tools::GameClass->getContent()->RootDirectory << std::endl;

		Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Environments/Snow" ));


		long long big = 0;
		long long small = 0;

		Start();
		for ( int i = 0; i < 1; i++ )
		{
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Bob/Classic/v1/Stand/Bob_Stand_0001" ));
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Bob/Classic/v1/Stand/Bob_Stand_0002" ));
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Bob/Classic/v1/Stand/Bob_Stand_0003" ));
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Bob/Classic/v1/Stand/Bob_Stand_0004" ));
		}
		small = Stop();

		Start();
		for ( int i = 0; i < 1; i++ )
		{
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Environments/Castle/Pillars/Pillar_Castle_1000" ));
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Environments/Cave/Pillars/Pillar_Cave_1000" ));
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Environments/Cloud/Pillars/Pillar_Cloud_1000" ));
			Tools::GameClass->getContent()->Load<Texture2D>(std::wstring( L"Art/Environments/Forest/Pillars/Pillar_Forest_1000" ));
		}
		big = Stop();

		std::cout << _T( "big took " ) << big << std::endl;
		std::cout << _T( "small took " ) << small << std::endl;
		std::cout << _T( "" ) << std::endl;
	}

#if defined(PC_DEBUG) || defined(WINDOWS) && defined(DEBUG)
	bool CloudberryKingdomGame::DebugModePhsx()
	{
	#if defined(WINDOWS)
		if ( !KeyboardExtension::Freeze )
		{
			// Test title screen
			if ( Tools::Keyboard.IsKeyDown( Keys_G ) && !Tools::PrevKeyboard.IsKeyDown( Keys_G ) )
			{
				//TitleGameFactory = TitleGameData_Intense.Factory;
				TitleGameFactory = TitleGameData_MW::Factory;
				//TitleGameFactory = TitleGameData_Forest.Factory;

				Tools::SongWad->Stop();
				Tools::CurGameData = CloudberryKingdomGame::TitleGameFactory->Make();
				return true;
			}

			if ( Tools::Keyboard.IsKeyDown( Keys_J ) && !Tools::PrevKeyboard.IsKeyDown( Keys_J ) )
			{
				Tools::CurGameData->FadeToBlack();
			}
		}

		//// Give award
		//if (Tools::keybState.IsKeyDown(Keys.S) && !Tools::PrevKeyboardState.IsKeyDown(Keys.S))
		//{
		//    Awardments::GiveAward(Awardments::UnlockHeroRush2);
		//}

		if ( !KeyboardExtension::Freeze && KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_F ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_F ) )
			ShowFPS = !ShowFPS;
	#endif

	#if defined(PC_DEBUG)
		if ( Tools::FreeCam )
		{
			Vector2 pos = Tools::CurLevel->getMainCamera()->Data.Position;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys_Right ) )
				pos.X += 130;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys_Left ) )
				pos.X -= 130;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys_Up ) )
				pos.Y += 130;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys_Down ) )
				pos.Y -= 130;
			Tools::CurLevel->getMainCamera()->EffectivePos += pos - Tools::CurLevel->getMainCamera()->Data.Position;
			Tools::CurLevel->getMainCamera()->Data.Position = Tools::CurLevel->getMainCamera()->Target = pos;
			Tools::CurLevel->getMainCamera()->Update();
		}
	#endif

#if defined(WINDOWS)
		// Reload some dynamic data (tileset info, animation specifications).
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_X ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_X ) )
		{
			// Make blocks in the current level reset their art to reflect possible changes in the reloaded tileset info.
			for ( BlockVec::const_iterator block = Tools::CurLevel->Blocks.begin(); block != Tools::CurLevel->Blocks.end(); ++block )
			{
				boost::shared_ptr<NormalBlock> nblock = boost::dynamic_pointer_cast<NormalBlock>( *block );
				if ( 0 != nblock )
					nblock->ResetPieces();

				boost::shared_ptr<MovingBlock> mblock = boost::dynamic_pointer_cast<MovingBlock>( *block );
				if ( 0 != mblock )
					mblock->ResetPieces();
			}
		}

	#if defined(DEBUG)
		// Reload ALL dynamic data (tileset info, animation specifications, dynamic art, backgrounds).
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Z ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_Z ) )
		{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( std::vector<boost::shared_ptr<BobPhsx> >::const_iterator hero = Bob::HeroTypes.begin(); hero != Bob::HeroTypes.end(); ++hero )
				( *hero )->ResetInfo();

			//Tools::TextureWad.LoadAllDynamic(Tools::GameClass.Content, EzTextureWad.WhatToLoad.Animations);

			//LoadInfo();

			//// Reset blocks
			//foreach (BlockBase block in Tools::CurLevel.Blocks)
			//{
			//    NormalBlock nblock = block as NormalBlock;
			//    if (null != nblock) nblock.ResetPieces();

			//    MovingBlock mblock = block as MovingBlock;
			//    if (null != mblock) mblock.ResetPieces();
			//}
		}
	#endif

		// Turn on a simple green screen background.
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_D9 ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_D9 ) )
			Background::GreenScreen = !Background::GreenScreen;

		Tools::ModNums();

		// Load a test level.
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_D5 ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_D5 ) )
		{
			GameData::LockLevelStart = false;
			LevelSeedData::ForcedReturnEarly = 0;
			MakeTestLevel();
			return true;
		}

		// Hide the GUI. Used for video capture.
		if ( ButtonCheck::State( Keys_D8 ).Pressed )
			HideGui = !HideGui;

		// Hide the foreground. Used for video capture of backgrounds.
		if ( ButtonCheck::State( Keys_D7 ).Pressed )
			HideForeground = !HideForeground;

		// Turn on/off immortality.
		if ( !GodMode )
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_O ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_O ) )
		{
			for ( BobVec::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			{
				( *bob )->Immortal = !( *bob )->Immortal;
			}
		}

		// Turn on/off graphics.
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Q ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_Q ) )
			Tools::DrawGraphics = !Tools::DrawGraphics;
		// Turn on/off drawing of collision detection boxes.
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_W ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_W ) )
			Tools::DrawBoxes = !Tools::DrawBoxes;
		// Turn on/off step control. When activated, this allows you to step forward in the game by pressing <Enter>.
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_E ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_E ) )
			Tools::StepControl = !Tools::StepControl;
		// Modify the speed of the game.
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_R ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_R ) )
		{
			Tools::IncrPhsxSpeed();
		}

		// Don't do any of the following if a control box is up.
		if ( !KeyboardExtension::Freeze )
		{
			// Watch the computer make a level during Stage 1 of construction.
			if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_D3 ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_D3 ) )
			{
				GameData::LockLevelStart = false;
				LevelSeedData::ForcedReturnEarly = 1;
				MakeTestLevel();
				return true;
			}

			// Watch the computer make a level during Stage 2 of construction.
			if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_D4 ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_D4 ) )
			{
				GameData::LockLevelStart = false;
				LevelSeedData::ForcedReturnEarly = 2;
				MakeTestLevel();
				return true;
			}

			// Zoom in and out.
			if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_OemComma ) )
			{
				Tools::CurLevel->getMainCamera()->setZoom(Tools::CurLevel->getMainCamera()->getZoom() * .99f);
				Tools::CurLevel->getMainCamera()->EffectiveZoom *= .99f;
			}
			if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_OemPeriod ) )
			{
				Tools::CurLevel->getMainCamera()->setZoom(Tools::CurLevel->getMainCamera()->getZoom() / .99f);
				Tools::CurLevel->getMainCamera()->EffectiveZoom /= .99f;
			}

			//// Turn on/off FreeCam, which allows the user to pan the camera through the level freely.
			//if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_P ) && !KeyboardExtension::IsKeyDownCustom( Tools::PrevKeyboard, Keys_P ) )
			//	Tools::FreeCam = !Tools::FreeCam;
		}
#endif // #if defined(WINDOWS)

		// Allow Back to exit the game if we are in test mode
	#if defined(DEBUG)
		if ( ButtonCheck::State( ControllerButtons_BACK, -1 ).Down )
		{
			Exit();
			return true;
		}
	#endif

		return false;
	}
#endif

	std::wstring CloudberryKingdomGame::debugstring = std::wstring( L"" );

	void CloudberryKingdomGame::DrawDebugInfo()
	{
		//if ( Tools::ShowNums )
		//{
		//	std::wstring nums = Tools::Num_0_to_2 + std::wstring( L"\n\n" ) + Tools::Num_0_to_360;

		//	Tools::StartSpriteBatch();
		//	Tools::Render->MySpriteBatch->DrawString( Resources::LilFont->Font, nums, Vector2( 0, 100 ), Color::Orange, 0, Vector2(),.4f, SpriteEffects::None, 0 );
		//	Tools::Render->EndSpriteBatch();
		//	return;
		//}

	#if defined(WINDOWS)
		// Grace period for falling
		//string str = "";
		//if (Tools::CurLevel != null && Tools::CurLevel.Bobs.Count > 0)
		//{
		//    //var phsx = Tools::CurLevel.Bobs[0].MyPhsx as BobPhsxNormal;
		//    //if (null != phsx) str = phsx.FallingCount.ToString();

		//    var phsx = Tools::CurLevel.Bobs[0].MyPhsx as BobPhsxMeat;
		//    //if (null != phsx) str = phsx.WallJumpCount.ToString();
		//    if (null != phsx) str = phsx.StepsSinceSide.ToString();
		//}

		// Mouse
		//string str = string.Format("Mouse delta: {0}", Tools::DeltaMouse);
		//string str = string.Format("Mouse in window: {0}", Tools::MouseInWindow);

		// VPlayer
		//string str = "";
		//if (VPlayer1 != null)
		//{
		//    str = VPlayer1.PlayPosition.Ticks.ToString();
		//    //Console.WriteLine(str);
		//}


		// GC
		//string str = GC.CollectionCount(0).ToString() + " " + fps.ToString() + "\n"
		//    + (RunningSlowly ? "SLOW" : "____ FAST") + "\n"
		//    + debugstring;
		std::wstring str = debugstring;

		// Phsx count
		//string str  = string.Format("CurLevel PhsxStep: {0}\n", Tools::CurLevel.CurPhsxStep);

		// Score
		//PlayerData p = PlayerManager::Get(0);
		//string str = string.Format("Death {0}, {1}, {2}, {3}, {4}", p.TempStats.TotalDeaths, p.LevelStats.TotalDeaths, p.GameStats.TotalDeaths, p.CampaignStats.TotalDeaths, Campaign.Attempts);
		//Campaign.CalcScore();
		//string str2 = string.Format("Coins {0}, {1}, {2}, {3}, {4}", p.TempStats.Coins, p.LevelStats.Coins, p.GameStats.Coins, p.CampaignStats.Coins, Campaign.Coins);
		//str += "\n\n" + str2;
		//string str3 = string.Format("Total {0}, {1}, {2}, {3}, {4}", p.TempStats.TotalCoins, p.LevelStats.TotalCoins, p.GameStats.TotalCoins, p.CampaignStats.TotalCoins, Campaign.TotalCoins);
		//str += "\n\n" + str3;
		//string str4 = string.Format("Total {0}, {1}, {2}, {3}", p.TempStats.TotalBlobs, p.LevelStats.TotalBlobs, p.GameStats.TotalBlobs, p.CampaignStats.TotalBlobs);
		//str += "\n" + str4;
		//string str5 = string.Format(" {0}, {1}, {2}, {3}", p.TempStats.Blobs, p.LevelStats.Blobs, p.GameStats.Blobs, p.CampaignStats.Blobs);
		//str += "\n" + str5;

		// Coins
		//string str = string.Format("{0}, {1}, {2}, {3}", p.TempStats.Coins, p.LevelStats.Coins, p.GameStats.Coins, p.CampaignStats.Coins);
		//string str2 = string.Format("{0}, {1}, {2}, {3}", p.TempStats.TotalCoins, p.LevelStats.TotalCoins, p.GameStats.TotalCoins, p.CampaignStats.TotalCoins);
		//str += "\n" + str2;
	#else
		std::wstring str = debugstring;
	#endif

		//str = string.Format("{0,-5} {1,-5} {2,-5} {3,-5} {4,-5}", Level.Pre1, Level.Step1, Level.Pre2, Level.Step2, Level.Post);

		if ( Tools::getCurCamera() == 0 ) return;
		Tools::QDrawer->DrawString( Resources::Font_Grobold42->HFont, str, Vector2(0, 100), Color::Orange.ToVector4(), Vector2(1) );
		Tools::QDrawer->Flush();
	}

	void CloudberryKingdomGame::MakeEmptyLevel()
	{
		boost::shared_ptr<Level> level = boost::make_shared<Level>();
		level->setMainCamera( boost::make_shared<Camera>() );
		level->CurPiece = level->StartNewPiece( 0, BobVec(), 4 );
		level->CurPiece->StartData[ 0 ].Position = Vector2( 0, 0 );
		level->getMainCamera()->BLCamBound = Vector2(-100000, 0);
		level->getMainCamera()->TRCamBound = Vector2(100000, 0);
		level->getMainCamera()->Update();
		level->TimeLimit = -1;

		level->MyBackground = boost::make_shared<RegularBackground>();
		level->MyBackground->Init( level );

		Tools::CurGameData = level->MyGame = boost::make_shared<GameData>();
		GameData_Construct( level->MyGame );

		Tools::CurGameData->MyLevel = Tools::CurLevel = level;
	}

	void CloudberryKingdomGame::MakeTestLevel()
	{
		//PlayerManager::Players[0].Exists = true;
		//PlayerManager::Players[1].Exists = true;
		//PlayerManager::Players[2].Exists = true;
		//PlayerManager::Players[3].Exists = true;

		boost::shared_ptr<LevelSeedData> data = boost::make_shared<LevelSeedData>();


		//data.ReadString("0;s:1830873138;h:2,0,2,0;t:sea;n:1;l:2150;u:0,0,0,0,0,2,4.625,0,0,0,0,0,3.75,6.375,0,0,0,0,0,0,0,7.75,0,6.625;");
		//GameData.StartLevel(data);
		//return;

		data->setSeed( Tools::GlobalRnd->Rnd->Next() );
		//data.Seed = 110040853;
		std::cout << _T( "Seed chosen = " ) << data->getSeed() << std::endl;

		//data.MyBackgroundType = BackgroundType.Dungeon;

		TileSetToTest = L"sea_rain";
		//TileSetToTest = L"hills";
		//TileSetToTest = L"forest";
		//TileSetToTest = L"cloud";
		//TileSetToTest = L"cave";
		//TileSetToTest = L"castle";

		if ( TileSetToTest == std::wstring( L"" ) )
			data->SetTileSet( std::wstring( L"castle" ) );
		else
			data->SetTileSet( TileSetToTest );

		//data.SetTileSet(TileSets.Dungeon);

		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Wheel, Hero_Shape.Small, Hero_MoveMod.Jetpack);
		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Bouncy, Hero_Shape.Classic, Hero_MoveMod.Jetpack);
		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Box, Hero_Shape.Classic, Hero_MoveMod.Jetpack);
		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Classic, Hero_Shape.Small, Hero_MoveMod.Double);
		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Wheel, Hero_Shape.Small, Hero_MoveMod.Double);

		data->DefaultHeroType = BobPhsxNormal::getInstance();
		//data.DefaultHeroType = BobPhsxBouncy.Instance;
		//data.DefaultHeroType = BobPhsxWheel.Instance;
		//data.DefaultHeroType = BobPhsxTime.Instance;
		//data.DefaultHeroType = BobPhsxInvert.Instance;
		//data.DefaultHeroType = BobPhsxMeat.Instance;
		//data.DefaultHeroType = BobPhsxDouble.Instance;
		//data.DefaultHeroType = BobPhsxSpaceship.Instance;
		//data.DefaultHeroType = BobPhsxRocketbox.Instance;
		//data.DefaultHeroType = BobPhsxSmall.Instance;
		//data.DefaultHeroType = BobPhsxBig.Instance;
		//data.DefaultHeroType = BobPhsxScale.Instance;
		//data.DefaultHeroType = BobPhsxJetman.Instance;
		//data.DefaultHeroType = BobPhsxBox.Instance;

		// 8-jumps
		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Classic, Hero_Shape.Classic, Hero_MoveMod.Double);
		//var d = new BobPhsx::CustomPhsxData();
		//d.Init();
		//d[BobPhsx::CustomData.numjumps] = 2;
		//data.DefaultHeroType.SetCustomPhsx(d);

		// Long jetpack
		//data.DefaultHeroType = BobPhsx::MakeCustom(Hero_BaseType.Classic, Hero_Shape.Classic, Hero_MoveMod.Jetpack);
		//var d = new BobPhsx::CustomPhsxData();
		//d.Init();
		//d[BobPhsx::CustomData.jetpackfuel] *= 2;
		//d[BobPhsx::CustomData.jetpackaccel] *= 2;
		//data.DefaultHeroType.SetCustomPhsx(d);


		data->MyGeometry = LevelGeometry_RIGHT;
		//data.MyGeometry = LevelGeometry.Up;
		//data.PieceLength = 90000;
		//data->PieceLength = 15000;
		//data.PieceLength = 37000;
		data->PieceLength = 4000;
		data->NumPieces = 1;

		data->MyGameType = NormalGameData::Factory;
		//data.MyGameType = PlaceGameData.Factory;

		//data.MyGameFlags.IsTethered = true; 
		//data.MyGameFlags.IsDoppleganger = true;
		//data.MyGameFlags.IsDopplegangerInvert = true;

		data->Initialize( boost::make_shared<MakeTestLevelInitializeHelper>( shared_from_this() ) );

		// Add Landing Zone
		//data.PieceSeeds[0].Style.MyInitialPlatsType = StyleData.InitialPlatsType.LandingZone;

		data->PostMake->Add( boost::make_shared<TestLevelPostMakeProxy>( shared_from_this() ) );

		//Campaign.CarryPrinces(data);

		// Rumble
		//level.MyGame.AddGameObject(new Rumble());
		//};

		//data.LavaMake = LevelSeedData.LavaMakeTypes.NeverMake;
		data->LavaMake = LevelSeedData::LavaMakeTypes_ALWAYS_MAKE;

		GameData::StartLevel( data );
	}

	void CloudberryKingdomGame::TestLevelPostMake( const boost::shared_ptr<Level> &level )
	{
		level->StartRecording();

		level->MyGame->AddGameObject( MakeMagic( HintGiver, () ) );
		level->MyGame->AddGameObject( HelpMenu::MakeListener() );
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );

		//level.MyGame.AddGameObject(new LevelTitle(data.DefaultHeroType.Name));
		//level.MyGame.AddGameObject(new GUI_Quota(15));

		//var gui = new GUI_LivesLeft(20);
		//level.MyGame.AddGameObject(gui);
		//level.MyGame.AddGameObject(new GUI_NextLife(25, gui));
		//level.MyGame.AddGameObject(new GUI_Lives(gui));

		//level.MyGame.DramaticEntry(level.StartDoor, 20);
	}

	void CloudberryKingdomGame::TestLevelInit( const boost::shared_ptr<PieceSeedData> &piece )
	{
		//writelist();
		//Tools::Write("!");

		//piece.ZoomType = LevelZoom.Big;
		piece->ExtraBlockLength = 1000;

		//piece.Paths = RndDifficulty.ChoosePaths(piece);
		//piece.Style.AlwaysCurvyMove = true;
		RndDifficulty::ZeroUpgrades( piece->MyUpgrades1 );


		//__Roughly_Abusive( piece );
		//__Roughly_Maso(piece);
		//piece.Style.Masochistic = true;

		//piece->MyUpgrades1->Get( Upgrade_MOVING_BLOCK ) = 8;
		//piece->MyUpgrades1->Get( Upgrade_BOUNCY_BLOCK ) = 6;
		piece->MyUpgrades1->Get(Upgrade_JUMP) = 8;



		piece->MyUpgrades1->CalcGenData( piece->MyGenData->gen1, piece->Style );

		piece->Paths = 1;
		piece->LockNumOfPaths = true;
		piece->Style->SinglePathType = StyleData::_SinglePathType_NORMAL;


		piece->Style->ChanceToKeepUnused = 0;

		RndDifficulty::ZeroUpgrades( piece->MyUpgrades2 );
		CopyFromTo( piece->MyUpgrades1->UpgradeLevels, piece->MyUpgrades2->UpgradeLevels );
		piece->MyUpgrades2->CalcGenData( piece->MyGenData->gen2, piece->Style );

		piece->Style->MyInitialPlatsType = StyleData::InitialPlatsType_DOOR;
		piece->Style->MyFinalPlatsType = StyleData::FinalPlatsType_DOOR;
	}

	void CloudberryKingdomGame::__Roughly_Maso( const boost::shared_ptr<PieceSeedData> &piece )
	{
		piece->MyUpgrades1->Get( Upgrade_JUMP ) = 1;
		piece->MyUpgrades1->Get( Upgrade_SPEED ) = 10;

		piece->MyUpgrades1->Get( Upgrade_SERPENT ) = 7;
		//piece.MyUpgrades1->Get(Upgrade.LavaDrip) = 10;
		piece->MyUpgrades1->Get( Upgrade_LASER ) = 5;

		piece->MyUpgrades1->Get( Upgrade_FLY_BLOB ) = 3;
		piece->MyUpgrades1->Get( Upgrade_GHOST_BLOCK ) = 4;
		////piece.MyUpgrades1->Get(Upgrade.FallingBlock) = 4;
		////piece.MyUpgrades1->Get(Upgrade.BouncyBlock) = 4;
		piece->MyUpgrades1->Get( Upgrade_MOVING_BLOCK ) = 4;
		//piece.MyUpgrades1->Get(Upgrade.Elevator) = 1;
		piece->MyUpgrades1->Get( Upgrade_SPIKEY_GUY ) = 10;
		////piece.MyUpgrades1->Get(Upgrade.Firesnake) = 6;
		piece->MyUpgrades1->Get( Upgrade_SPIKE ) = 9;
		piece->MyUpgrades1->Get( Upgrade_FIRE_SPINNER ) = 10;

		piece->MyUpgrades1->Get( Upgrade_PINKY ) = 4;
		//piece.MyUpgrades1->Get(Upgrade.SpikeyLine) = 2;
		//piece.MyUpgrades1->Get(Upgrade.Conveyor) = 8;
	}

	void CloudberryKingdomGame::__Roughly_Abusive( const boost::shared_ptr<PieceSeedData> &piece )
	{
		piece->MyUpgrades1->Get( Upgrade_JUMP ) = 1;
		piece->MyUpgrades1->Get( Upgrade_SPEED ) = 3;
		////piece.MyUpgrades1->Get(Upgrade.Serpent) = 0;
		////piece.MyUpgrades1->Get(Upgrade.LavaDrip) = 4;
		piece->MyUpgrades1->Get( Upgrade_FLY_BLOB ) = 3;
		piece->MyUpgrades1->Get( Upgrade_GHOST_BLOCK ) = 4;
		piece->MyUpgrades1->Get( Upgrade_FALLING_BLOCK ) = 4;
		////piece.MyUpgrades1->Get(Upgrade.BouncyBlock) = 4;
		piece->MyUpgrades1->Get( Upgrade_MOVING_BLOCK ) = 4;
		//piece.MyUpgrades1->Get(Upgrade.Elevator) = 1;
		piece->MyUpgrades1->Get( Upgrade_SPIKEY_GUY ) = 2;
		////piece.MyUpgrades1->Get(Upgrade.Firesnake) = 6;
		piece->MyUpgrades1->Get( Upgrade_SPIKE ) = 2;
		piece->MyUpgrades1->Get( Upgrade_FIRE_SPINNER ) = 2;
		//piece.MyUpgrades1->Get(Upgrade.Laser) = 2;
		piece->MyUpgrades1->Get( Upgrade_PINKY ) = 1;
		//piece.MyUpgrades1->Get(Upgrade.SpikeyLine) = 2;
		//piece.MyUpgrades1->Get(Upgrade.Conveyor) = 8;
	}

	void CloudberryKingdomGame::TestLevelModParams( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p )
	{
		//var Params = (NormalBlock_Parameters)p.Style.FindParams(NormalBlock_AutoGen.Instance);
		//Wall wall = Params.SetWall(data.MyGeometry);
		//wall.Space = 20; wall.MyBufferType = Wall.BufferType.Space;
		//p.CamZoneStartAdd.X = -2000;
		//wall.StartOffset = -600;
		//wall.Speed = 17.5f;
		//wall.InitialDelay = 72;

		//Coin_Parameters Params = (Coin_Parameters)p.Style.FindParams(Coin_AutoGen.Instance);
		//Params.Regular_Period = 15;
		//Params.FillType = Coin_Parameters.FillTypes.CoinGrab;
		//Params.Grid = false;
		//Params.DoCleanup = false;

		//level.CurMakeData.MidDivider = true;

		//FireballEmitter_Parameters Params = (FireballEmitter_Parameters)p.Style.FindParams(FireballEmitter_AutoGen.Instance);
		//Params.Special.BorderFill = true;


		//Floater_Spin_Parameters FS_Params = (Floater_Spin_Parameters)p.Style.FindParams(Floater_Spin_AutoGen.Instance);
		//FS_Params.Special.Rockwheel = true;

		//p.Style.SetToMake_BouncyHallway(piece);


		float size = 90;
		boost::shared_ptr<FallingBlock_Parameters> FParams = boost::static_pointer_cast<FallingBlock_Parameters>( p->Style->FindParams( FallingBlock_AutoGen::getInstance() ) );
		FParams->Width.SetVal( size );
		boost::shared_ptr<MovingBlock_Parameters> MParams = boost::static_pointer_cast<MovingBlock_Parameters>( p->Style->FindParams( MovingBlock_AutoGen::getInstance() ) );
		MParams->Size.SetVal( size );
		MParams->Aspect = MovingBlock_Parameters::AspectType_SQUARE;
		MParams->Motion = MovingBlock_Parameters::MotionType_VERTICAL;
		boost::shared_ptr<BouncyBlock_Parameters> BParams = boost::static_pointer_cast<BouncyBlock_Parameters>( p->Style->FindParams( BouncyBlock_AutoGen::getInstance() ) );
		BParams->Size.SetVal( size );
		boost::shared_ptr<FlyingBlob_Parameters> GParams = boost::static_pointer_cast<FlyingBlob_Parameters>( p->Style->FindParams( FlyingBlob_AutoGen::getInstance() ) );
		//GParams.Counter
		boost::shared_ptr<NormalBlock_Parameters> NParams = boost::static_pointer_cast<NormalBlock_Parameters>( p->Style->FindParams( NormalBlock_AutoGen::getInstance() ) );
		//NParams.Make = false;


		//Goomba_Parameters GParams = (Goomba_Parameters)p.Style.FindParams(Goomba_AutoGen.Instance);
		//GParams.KeepUnused = 1f;
		//GParams.FillWeight = 100;

		/* Goomba pinwheel */
		//Goomba_Parameters Params = (Goomba_Parameters)p.Style.FindParams(Goomba_AutoGen.Instance);
		//Params.Special.Pinwheel = true;
		//p.Paths = level.CurMakeData.NumInitialBobs = 1;



		/* Goomba hallway */
		//Goomba_Parameters Params = (Goomba_Parameters)p.Style.FindParams(Goomba_AutoGen.Instance);
		//p.Style.SuppressGroundCeiling(piece);
		//Params.Special.Tunnel = true;
		//Params.TunnelDisplacement = 100;
		//Params.TunnelMotionType = Goomba_Parameters.MotionType.Horizontal;
		//Params.TunnelCeiling = false;
		//p.Paths = level.CurMakeData.NumInitialBobs = 1;
		//level.CurMakeData.MoveData[0].MaxTargetY = 0;
		//level.CurMakeData.MoveData[0].MinTargetY = -300;

		// Special mixes: (rockcircle + bouncyhall + lasers)
	}

	void CloudberryKingdomGame::LogoPhsx()
	{
		LoadingScreen_Renamed->PhsxStep();
		if ( !DoInnerLogoPhsx )
		{
			if ( LoadingScreen_Renamed->IsDone )
				LogoScreenUp = false;

			return;
		}

		if ( !Resources::LoadingResources->MyBool )
		{
			if ( LoadingScreen_Renamed->IsDone || !Resources::LoadingResources->MyBool )
			{
				DoInnerLogoPhsx = false;
				if ( LoadingScreen_Renamed->IsDone )
					LogoScreenUp = false;

				DrawCount = PhsxCount = 0;

				PlayerManager::Get( 0 )->IsAlive = PlayerManager::Get( 0 )->Exists = true;


				// Now that everything is loaded, start the real game, dependent on the command line arguments.
				if ( StartAsBackgroundEditor )
				{
	#if defined(DEBUG)
					MakeEmptyLevel();
	#endif
					return;
				}
				else if ( StartAsTestLevel )
				{
	#if defined(DEBUG)
					MakeTestLevel();
	#endif
					return;
				}
				else if ( StartAsFreeplay )
				{
					Tools::CurGameData = CloudberryKingdomGame::TitleGameFactory->Make();
					return;
				}

	#if defined(DEBUG)
				// Start at Title Screen
				//Tools::CurGameData = CloudberryKingdomGame::TitleGameFactory->Make();

				// Test screen saver
#if defined(_CRTDBG_MAP_ALLOC) && defined(WINDOWS)
				CloudberryKingdomGame::memdebug_DumpStart();
#endif
				boost::shared_ptr<ScreenSaver> Intro = boost::make_shared<ScreenSaver>(); ScreenSaver_Construct( Intro ); Intro->Init();

				return;
	#else
				// Start at Screen Saver
				boost::shared_ptr<ScreenSaver> Intro = boost::make_shared<ScreenSaver>();
				ScreenSaver_Construct( Intro );
				Intro->Init();
				return;
	#endif
			}
		}
	}

	void CloudberryKingdomGame::InitializeInstanceFields()
	{
		ScreenWidth = 0; ScreenHeight = 0;
		DrawCount = 0; PhsxCount = 0;
		LogoScreenUp = false;
		LogoScreenPropUp = false;

		Resolutions = std::vector<ResolutionGroup>( 4 );
#if defined(WINDOWS)
		_DrawMouseBackIcon = false;
#endif
		ToDo = boost::make_shared<Multicaster>();
	
#if defined(WINDOWS)
		ShowMouse = false;
#endif
		MediaPlaying_HoldState = false;
		FirstInactiveFrame = true;
		FirstActiveFrame = true;
		DeltaT = 0;
		//RunningSlowly = false;
		ShowFPS = false;
		MainString = boost::make_shared<StringBuilder>( 100, 100 );
		DoInnerLogoPhsx = true;
	}
}
