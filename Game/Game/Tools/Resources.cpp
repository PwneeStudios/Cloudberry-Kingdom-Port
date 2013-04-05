#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/String.h>

#include <Hacks/NET/Path.h>
#include <Hacks/NET/Directory.h>

#include <iostream>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <Architecture/Job.h>
#include <Architecture/Scheduler.h>
#include <Core.h>
#include <Content/Wad.h>
#include <ResourceList\Resources_Art.h>
#include <ResourceList\Resources_Music.h>
#include <ResourceList\Resources_Sound.h>
#include <Utility/ConsoleInformation.h>
#include <Utility/Log.h>

#include "Game/Tilesets/Tilesets/CloudberryKingdom.TileSets.h"

#ifdef PS3
#include <sys/ppu_thread.h>
#include <sys/timer.h>

extern bool gTrophyContextRegistered;
#endif

#ifdef CAFE
#include <cafe/mem.h>

bool SchedulerPausedForLogo;
extern void StopScheduler();

// Declared in SchedulerWiiU.cpp.
extern void TellSchedulerToCleanUpTextureHeap();

#endif

namespace CloudberryKingdom
{

#ifdef CAFE
	bool Resources::FinalLoadDone = false;
#else
	// FIXME: should be false and set to true once loading is done.
	bool Resources::FinalLoadDone = true;
#endif

	boost::shared_ptr<WrappedBool> Resources::LoadingResources = 0;
	boost::shared_ptr<WrappedFloat> Resources::ResourceLoadedCountRef = 0;
	boost::shared_ptr<EzFont> Resources::Font_Grobold42, Resources::Font_Grobold42_2 = 0;
	boost::shared_ptr<EzFont> Resources::LilFont = 0;

	boost::shared_ptr<HackFont> Resources::hf;
	boost::shared_ptr<Mutex> Resources::hf_Mutex;

	void Resources::FontLoad()
    {
        //hf = new HackFont("Grobold_" + Localization.CurrentLanguage.FontSuffix);

        Resources::Font_Grobold42 = boost::make_shared<EzFont>( L"Fonts/Grobold_42", L"Fonts/Grobold_42_Outline", -50.f, 40);
        Resources::Font_Grobold42->HFont = boost::make_shared<HackSpriteFont>(hf, 0);
        Resources::Font_Grobold42->HOutlineFont = boost::make_shared<HackSpriteFont>(hf, 1);

        Resources::Font_Grobold42_2 = boost::make_shared<EzFont>( L"Fonts/Grobold_42", L"Fonts/Grobold_42_Outline2", -50.f, 40);
        Resources::Font_Grobold42_2->HFont = boost::make_shared<HackSpriteFont>(hf, 0);
        Resources::Font_Grobold42_2->HOutlineFont = boost::make_shared<HackSpriteFont>(hf, 2);

        //Resources::LilFont = EzFont( L"Fonts/LilFont");
        Resources::LilFont = Resources::Font_Grobold42;

        Tools::Write( L"Fonts done...");
    }

	void Resources::LoadInfo()
	{
		Tools::Write( _T( "Starting to load info..." ) );
		boost::shared_ptr<Stopwatch> t = boost::make_shared<Stopwatch>();
		t->Start();

		boost::shared_ptr<PieceQuad> c;

		// Moving block
		c = PieceQuad::MovingBlock_Renamed = boost::make_shared<PieceQuad>();
		c->Center.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"blue_small" ) ) );

		// Falling block
		boost::shared_ptr<AnimationData_Texture> Fall = boost::make_shared<AnimationData_Texture>( std::wstring( L"FallingBlock" ), 1, 4 );
		PieceQuad::FallingBlock_Renamed = boost::make_shared<PieceQuad>();
		PieceQuad::FallingBlock_Renamed->Center.SetTextureAnim( Fall );
		PieceQuad::FallGroup = boost::make_shared<BlockGroup>();
		PieceQuad::FallGroup->Add( 100, PieceQuad::FallingBlock_Renamed );
		PieceQuad::FallGroup->SortWidths();

		// Bouncy block
		boost::shared_ptr<AnimationData_Texture> Bouncy = boost::make_shared<AnimationData_Texture>( std::wstring( L"BouncyBlock" ), 1, 2 );
		PieceQuad::BouncyBlock_Renamed = boost::make_shared<PieceQuad>();
		PieceQuad::BouncyBlock_Renamed->Center.SetTextureAnim( Bouncy );
		PieceQuad::BouncyGroup = boost::make_shared<BlockGroup>();
		PieceQuad::BouncyGroup->Add( 100, PieceQuad::BouncyBlock_Renamed );
		PieceQuad::BouncyGroup->SortWidths();

		// Moving block
		PieceQuad::MovingGroup = boost::make_shared<BlockGroup>();
		PieceQuad::MovingGroup->Add( 100, PieceQuad::MovingBlock_Renamed );
		PieceQuad::MovingGroup->SortWidths();

		// Elevator
		PieceQuad::Elevator = boost::make_shared<PieceQuad>();
		PieceQuad::Elevator->Center.Set( std::wstring( L"palette" ) );
		PieceQuad::Elevator->Center.SetColor( Color( static_cast<unsigned char>( 210 ), static_cast<unsigned char>( 210 ), static_cast<unsigned char>( 210 ) ) );
		PieceQuad::ElevatorGroup = boost::make_shared<BlockGroup>();
		PieceQuad::ElevatorGroup->Add( 100, PieceQuad::Elevator );
		PieceQuad::ElevatorGroup->SortWidths();


		//#if INCLUDE_EDITOR
		//if (LoadDynamic)
		{
			//if (!AlwaysSkipDynamicArt)
			//    Tools::TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Art);
			//Tools::TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Backgrounds);
			//Tools::TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Animations);
			//Tools::TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Tilesets);
		}
		//#endif

		t->Stop();
		Tools::Write( _T( "... done loading info!" ) );
		Tools::Write( _T( "Total seconds: {0}" ), t->Elapsed.TotalSeconds );
	}

	void Resources::LoadMusic( bool CreateNewWad )
	{
		if ( CreateNewWad )
			Tools::SongWad = boost::make_shared<EzSongWad>();

		Tools::SongWad->PlayerControl = Tools::SongWad->DisplayInfo = true;

		std::vector<std::wstring> files = MusicList();

		for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		{
			int i = ( *file ).find( std::wstring( L"Music" ) ) + 5 + 1;
			int j = ( *file ).find( std::wstring( L"." ), i );

			std::wstring name = ( *file ).substr( i, j - i );

			if ( CreateNewWad )
				Tools::SongWad->AddSong( Tools::GameClass->getContent()->Load<Song>( *file ), name );

			ResourceLoadedCountRef->MyFloat++;
		}


		Tools::Song_Happy = Tools::SongWad->FindByName( std::wstring( L"Happy^James_Stant" ) );
		Tools::Song_Happy->Volume = .9f;

		Tools::Song_140mph = Tools::SongWad->FindByName( std::wstring( L"140_Mph_in_the_Fog^Blind_Digital" ) );
		Tools::Song_140mph->Volume = .5f;

		Tools::Song_BlueChair = Tools::SongWad->FindByName( std::wstring( L"Blue_Chair^Blind_Digital" ) );
		Tools::Song_BlueChair->Volume = .7f;

		Tools::Song_Evidence = Tools::SongWad->FindByName( std::wstring( L"Evidence^Blind_Digital" ) );
		Tools::Song_Evidence->Volume = .7f;

		Tools::Song_GetaGrip = Tools::SongWad->FindByName( std::wstring( L"Get_a_Grip^Peacemaker" ) );
		Tools::Song_GetaGrip->Volume = 1;

		Tools::Song_House = Tools::SongWad->FindByName( std::wstring( L"House^Blind_Digital" ) );
		Tools::Song_House->Volume = .7f;

		Tools::Song_Nero = Tools::SongWad->FindByName( std::wstring( L"Nero's_Law^Peacemaker" ) );
		Tools::Song_Nero->Volume = 1;

		Tools::Song_Ripcurl = Tools::SongWad->FindByName( std::wstring( L"Ripcurl^Blind_Digital" ) );
		Tools::Song_Ripcurl->Volume = .7f;

		Tools::Song_FatInFire = Tools::SongWad->FindByName( std::wstring( L"The_Fat_is_in_the_Fire^Peacemaker" ) );
		Tools::Song_FatInFire->Volume = .9f;

		Tools::Song_Heavens = Tools::SongWad->FindByName( std::wstring( L"The_Heavens_Opened^Peacemaker" ) );
		Tools::Song_Heavens->Volume = 1;
		Tools::Song_Heavens->DisplayInfo = false;

		Tools::Song_TidyUp = Tools::SongWad->FindByName( std::wstring( L"Tidy_Up^Peacemaker" ) );
		Tools::Song_TidyUp->Volume = 1;

		Tools::Song_WritersBlock = Tools::SongWad->FindByName( std::wstring( L"Writer's_Block^Peacemaker" ) );
		Tools::Song_WritersBlock->Volume = 1;

		// Create the standard playlist
		AddRange( Tools::SongList_Standard, Tools::SongWad->SongList );
		Remove( Tools::SongList_Standard, Tools::Song_Happy );
		//Remove( Tools::SongList_Standard, Tools::Song_140mph );
		Remove( Tools::SongList_Standard, Tools::Song_Heavens );
	}

	void Resources::LoadSound( bool CreateNewWad )
	{

		boost::shared_ptr<ContentManager> manager = boost::make_shared<ContentManager>( Tools::GameClass->getContent()->RootDirectory );

		if ( CreateNewWad )
		{
			Tools::SoundWad = boost::make_shared<EzSoundWad>( 4 );
			Tools::PrivateSoundWad = boost::make_shared<EzSoundWad>( 4 );
		}

		std::vector<std::wstring> files = SoundList();

		for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		{
			int i = ( *file ).find( std::wstring( L"Sound" ) ) + 5 + 1;
			int j = ( *file ).find( std::wstring( L"." ), i );

			std::wstring name = ( *file ).substr( i, j - i );

			Tools::SoundWad->AddSound( manager->Load<SoundEffect>( *file ), name );
		}

		// FIXME: Implement more generic way of loading this.
		/*boost::shared_ptr<ContentManager> manager = boost::make_shared<ContentManager>( Tools::GameClass->getContent()->ServiceProvider, Tools::GameClass->getContent()->RootDirectory );

		if ( CreateNewWad )
		{
			Tools::SoundWad = boost::make_shared<EzSoundWad>( 4 );
			Tools::PrivateSoundWad = boost::make_shared<EzSoundWad>( 4 );
		}

		std::wstring path = Path::Combine( Globals::ContentDirectory, std::wstring( L"Sound" ) );
		std::vector<std::wstring> files = Directory::GetFiles( path );
		for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		{
			int i = ( *file ).find( std::wstring( L"Sound" ) ) + 5 + 1;
			if ( i < 0 )
				continue;
			int j = ( *file ).find( std::wstring( L"." ), i );
			if ( j <= i )
				continue;
			std::wstring name = ( *file ).substr( i, j - i );
			std::wstring extension = ( *file ).substr( j + 1 );

			if ( extension == std::wstring( L"xnb" ) )
			{
				if ( CreateNewWad )
					Tools::SoundWad->AddSound( manager->Load<boost::shared_ptr<SoundEffect> >( std::wstring( L"Sound/" ) + name ), name );
				else
				{
					boost::shared_ptr<SoundEffect> NewSound = manager->Load<boost::shared_ptr<SoundEffect> >( std::wstring( L"Sound/" ) + name );

					boost::shared_ptr<EzSound> CurSound = Tools::SoundWad->FindByName( name );
					for ( std::vector<EzSound*>::const_iterator ezsound = Tools::PrivateSoundWad->SoundList.begin(); ezsound != Tools::PrivateSoundWad->SoundList.end(); ++ezsound )
						if ( ( *ezsound )->sound == CurSound->sound )
							( *ezsound )->sound = NewSound;
					CurSound->sound = NewSound;
				}
			}

			ResourceLoadedCountRef->MyFloat++;
		}

		if ( Tools::SoundContentManager != 0 )
		{
			Tools::SoundContentManager->Unload();
			delete Tools::SoundContentManager;
		}

		Tools::SoundContentManager = manager;*/
	}

	void Resources::LoadAssets( bool CreateNewWads )
	{
		ResourceLoadedCountRef = boost::make_shared<WrappedFloat>();
		LoadingResources = boost::make_shared<WrappedBool>( false );
		LoadingResources->MyBool = true;

		// Load the art!
		PreloadArt();

		ConsoleLanguage language = GetConsoleLanguage();
		Localization::Language selectedLanguage = Localization::Language_ENGLISH;

		switch( language )
		{
		case ConsoleLanguage_JAPANESE:
			selectedLanguage = Localization::Language_JAPANESE;
			break;
		case ConsoleLanguage_ENGLISH:
			// English is the default language.
			break;
		case ConsoleLanguage_FRENCH:
			selectedLanguage = Localization::Language_FRENCH;
			break;
		case ConsoleLanguage_GERMAN:
			selectedLanguage = Localization::Language_GERMAN;
			break;
		case ConsoleLanguage_ITALIAN:
			selectedLanguage = Localization::Language_ITALIAN;
			break;
		case ConsoleLanguage_SPANISH:
			selectedLanguage = Localization::Language_SPANISH;
			break;
		case ConsoleLanguage_CHINESE:
			selectedLanguage = Localization::Language_CHINESE;
			break;
		case ConsoleLanguage_KOREAN:
			selectedLanguage = Localization::Language_KOREAN;
			break;
		case ConsoleLanguage_PORTUGUESE:
			selectedLanguage = Localization::Language_PORTUGUESE;
			break;
		case ConsoleLanguage_RUSSIAN:
			selectedLanguage = Localization::Language_RUSSIAN;
			break;
		}
        // Localization
        Localization::SetLanguage( selectedLanguage );

		// Fonts
		FontLoad();

		// Load the music!
		LoadMusic( CreateNewWads );

		// Load the sound!
		LoadSound( CreateNewWads );
	}

	void Resources::PreloadArt()
	{
		//std::wstring path = Path::Combine( Globals::ContentDirectory, std::wstring( L"Art" ) );
		//std::vector<std::wstring> files = Tools::GetFiles( path, true );
		//for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		//{
		//	if ( Tools::GetFileExt( path, *file ) == std::wstring( L"xnb" ) )
		//	{
		//		Tools::TextureWad->AddTexture( 0, std::wstring( L"Art/" ) + Tools::GetFileName( path, *file ) );
		//	}
		//}

		for( int i = 0; i < sizeof( TEXTURE_PATHS ) / sizeof( TEXTURE_PATHS[ 0 ] ); ++i )
			Tools::TextureWad->AddTexture( 0, TEXTURE_PATHS[ i ], TEXTURE_WIDTHS[ i ], TEXTURE_HEIGHTS[ i ] );

		/*std::vector<std::wstring> files;
		std::vector<int> widths;
		std::vector<int> heights;

		ArtList( files, widths, heights );

		std::vector<int>::iterator w, h;
		std::vector<std::wstring>::const_iterator file;
		for (file = files.begin(), w = widths.begin(), h = heights.begin() j; file != files.end(); ++file, ++w, ++h )
			Tools::TextureWad->AddTexture( 0, *file );*/
	}

#ifdef PS3
	static void TheLoadThread( uint64_t context )
	{
		( void )context;

		Resources::_LoadThread();

		sys_ppu_thread_exit( 0 );
	}
#endif

	void Resources::LoadResources()
	{
		// FIXME: Load resources in other thread.
		//LoadThread = ThreadHelper::EasyThread( 5, std::wstring( L"LoadThread" ), boost::make_shared<Action>( &_LoadThread ) );
#ifdef PS3
		sys_ppu_thread_t tid;
		int ret = sys_ppu_thread_create( &tid, TheLoadThread,
			0, 1001, 64 * 1024, 0, "TheLoadThread" );

		if( ret != 0 )
			LOG_WRITE( "Load thread failed!" );
#else
		_LoadThread();
#endif
	}

boost::shared_ptr<Thread> Resources::LoadThread = 0;

#ifdef CAFE
	class FinishLoadingJob : public Job
	{

	public:

		void Do()
		{
			Resources::FinalLoadDone = true;
			TellSchedulerToCleanUpTextureHeap();
		}

	};
#endif

	void Resources::_LoadThread()
	{
		hf_Mutex = boost::make_shared<Mutex>();

		boost::shared_ptr<CloudberryKingdom::CloudberryKingdomGame> Ck = Tools::TheGame;

		Tools::Write( Format( _T( "Load thread starts ... NOW!" ) ).c_str() );
		//Tools::Write( Format( _T( "Load thread starts at {0}" ), DateTime::Now() ) );
		
		//Thread::SpinWait( 100 );

		//Tools::Write( _T( "Start" ) );
		LOG_WRITE( "Start\n" );

		// Initialize the Gamepads
		Tools::GamepadState = std::vector<GamePadState>( 4 );
		Tools::PrevGamepadState = std::vector<GamePadState>( 4 );

		// Fireball texture
		Fireball::PreInit();

#ifdef CAFE
		SchedulerPausedForLogo = true;
		OSMemoryBarrier();
		StopScheduler();
#endif

#ifdef PS3
		//int resourceCounter = 0;
		//sys_timer_sleep( 3 );
#endif
        // Set off load calls
		for ( std::vector<boost::shared_ptr<EzTexture> >::const_iterator Tex = Tools::TextureWad->TextureList.begin();
			  Tex != Tools::TextureWad->TextureList.end(); ++Tex )
		{
#ifdef CAFE
			// We want to load the first 5 textures right away as they are needed for copyright screen.
			if( ( *Tex )->Path.find( L"Grobold" ) != std::wstring::npos
				|| ( *Tex )->Path.find( L"CopyRight" ) != std::wstring::npos )
			{
				boost::shared_ptr<Texture2D> t2d = boost::make_shared<Texture2D>(boost::shared_ptr<GraphicsDevice>(), 1, 1);
				LOG_WRITE( "Force load: %s\n", WstringToUtf8( ( *Tex )->Path ).c_str() );
				t2d->texture_ = CONTENT->ForceLoadTexture( WstringToUtf8( ( *Tex )->Path ) + ".png" );
				( *Tex )->setTex( t2d );
				continue;
			}
#endif

			// If texture hasn't been loaded yet, load it
			if ( ( *Tex )->getTex() == 0 && !(*Tex)->FromCode )
			{
				( *Tex )->setTex( Tools::GameClass->Content->Load< Texture2D >( ( *Tex )->Path ) );
			}

#ifdef PS3
			/*if( resourceCounter == 2 )
			{
				// FIXME: Originally this was a 1 second sleep.
				while( !gTrophyContextRegistered )
					sys_timer_usleep( 100000 );
			}
			resourceCounter++;*/
#endif
		}

#ifdef CAFE
		SCHEDULER->RunJob( new FinishLoadingJob );
#endif

		//for ( std::vector<boost::shared_ptr<EzTexture> >::const_iterator Tex = Tools::TextureWad->TextureList.begin(); Tex != Tools::TextureWad->TextureList.end(); ++Tex )
		//{
		//	// If texture hasn't been loaded yet, load it
		//	if ( ( *Tex )->getTex() == 0 && !(*Tex)->FromCode )
		//	{
		//		( *Tex )->setTex( Tools::GameClass->getContent()->Load<Texture2D>( ( *Tex )->Path ) );

		//		Resources::ResourceLoadedCountRef->setVal( Resources::ResourceLoadedCountRef->getVal() + 1 );
		//	}
		//}

		//Tools::Write( _T( "ArtMusic done..." ) );
		LOG_WRITE( "ArtMusic done...\n" );

		// Load the tile info
		LoadInfo();
		TileSets::Init();

		Fireball::InitRenderTargets( Ck->MyGraphicsDevice, Ck->MyGraphicsDevice->PP, 300, 200 );

		ParticleEffects::Init();

		Awardments::Init();

	#if defined(PC_VERSION)
		// Mouse pointer
		Ck->MousePointer = boost::make_shared<QuadClass>();
		Ck->MousePointer->Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Hand_Open" ) ) );
		Ck->MousePointer->ScaleYToMatchRatio( 70 );

		// Mouse back icon
		Ck->MouseBack = boost::make_shared<QuadClass>();
		Ck->MouseBack->Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"charmenu_larrow_1" ) ) );
		Ck->MouseBack->ScaleYToMatchRatio( 40 );
		Ck->MouseBack->Quad_Renamed.SetColor( Color( unsigned char( 255 ), unsigned char( 150 ), unsigned char( 150 ), unsigned char( 100 ) ) );
	#endif

		ObjectIcon::InitIcons();

		CloudberryKingdomGame::StaticIntializer_AfterResourcesLoad();

		Prototypes::LoadObjects();


		//std::cout << _T( "Total resources: " ) << ResourceLoadedCountRef->MyFloat << std::endl;
		LOG_WRITE( "Total resources: %d\n", static_cast<int>( ResourceLoadedCountRef->MyFloat ) );

		// Note that we are done loading.
		LoadingResources->MyBool = false;
		//Tools::Write( _T( "Loading done!" ) );
		LOG_WRITE( "Loading done!\n" );

		//Tools::Write( Format( _T( "Load thread done at {0}" ), DateTime::Now ) );
		//Tools::Write( Format( _T( "Load thread done ... NOW!" ) ).c_str() );
		LOG_WRITE( "Load thread done ... NOW!\n" );
	}
}
