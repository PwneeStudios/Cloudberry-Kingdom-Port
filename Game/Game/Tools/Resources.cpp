#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/String.h>

#include <Hacks/NET/Path.h>
#include <Hacks/NET/Directory.h>

#include <iostream>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <ResourceList\Resources_Art.h>
#include <ResourceList\Resources_Music.h>
#include <ResourceList\Resources_Sound.h>

namespace CloudberryKingdom
{

	boost::shared_ptr<WrappedBool> Resources::LoadingResources = 0;
	boost::shared_ptr<WrappedFloat> Resources::ResourceLoadedCountRef = 0;
	boost::shared_ptr<EzFont> Resources::Font_Grobold42, Resources::Font_Grobold42_2 = 0;
	boost::shared_ptr<EzFont> Resources::LilFont = 0;

	void Resources::FontLoad()
	{
		Resources::Font_Grobold42 = boost::make_shared<EzFont>( _T( "Fonts/Grobold_42" ), _T( "Fonts/Grobold_42_Outline" ), -50.f, 40 );
		Resources::Font_Grobold42_2 = boost::make_shared<EzFont>( _T( "Fonts/Grobold_42" ), _T( "Fonts/Grobold_42_Outline2" ), -50.f, 40 );

		Resources::LilFont = boost::make_shared<EzFont>( _T( "Fonts/LilFont" ) );

		Tools::Write( _T( "Fonts done..." ) );
	}

	void Resources::LoadInfo()
	{
		Tools::Write( _T( "Starting to load info..." ) );
		boost::shared_ptr<Stopwatch> t = boost::make_shared<Stopwatch>();
		t->Start();

		boost::shared_ptr<PieceQuad> c;

		// Moving block
		c = PieceQuad::MovingBlock_Renamed = boost::make_shared<PieceQuad>();
		c->Center.setMyTexture( Tools::TextureWad->FindByName( _T( "blue_small" ) ) );

		// Falling block
		boost::shared_ptr<AnimationData_Texture> Fall = boost::make_shared<AnimationData_Texture>( _T( "FallingBlock" ), 1, 4 );
		PieceQuad::FallingBlock_Renamed = boost::make_shared<PieceQuad>();
		PieceQuad::FallingBlock_Renamed->Center.SetTextureAnim( Fall );
		PieceQuad::FallGroup = boost::make_shared<BlockGroup>();
		PieceQuad::FallGroup->Add( 100, PieceQuad::FallingBlock_Renamed );
		PieceQuad::FallGroup->SortWidths();

		// Bouncy block
		boost::shared_ptr<AnimationData_Texture> Bouncy = boost::make_shared<AnimationData_Texture>( _T( "BouncyBlock" ), 1, 2 );
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
		PieceQuad::Elevator->Center.Set( _T( "palette" ) );
		PieceQuad::Elevator->Center.SetColor( Color( unsigned char( 210 ), unsigned char( 210 ), unsigned char( 210 ) ) );
		PieceQuad::ElevatorGroup = boost::make_shared<BlockGroup>();
		PieceQuad::ElevatorGroup->Add( 100, PieceQuad::Elevator );
		PieceQuad::ElevatorGroup->SortWidths();


		//#if INCLUDE_EDITOR
		//if (LoadDynamic)
		{
			//if (!AlwaysSkipDynamicArt)
			//    Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Art);
			//Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Backgrounds);
			//Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Animations);
			//Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Tilesets);
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
			int i = ( *file ).find( _T( "Music" ) ) + 5 + 1;
			int j = ( *file ).find( _T( "." ), i );

			std::wstring name = ( *file ).substr( i, j - i );

			if ( CreateNewWad )
				Tools::SongWad->AddSong( Tools::GameClass->getContent()->Load<Song>( *file ), name );

			ResourceLoadedCountRef->MyFloat++;
		}


		Tools::Song_Happy = Tools::SongWad->FindByName( _T( "Happy" ) );
		Tools::Song_Happy->DisplayInfo = false;

		Tools::Song_140mph = Tools::SongWad->FindByName( _T( "140_Mph_in_the_Fog^Blind_Digital" ) );
		Tools::Song_140mph->Volume = .7f;

		Tools::Song_BlueChair = Tools::SongWad->FindByName( _T( "Blue_Chair^Blind_Digital" ) );
		Tools::Song_BlueChair->Volume = .7f;

		Tools::Song_Evidence = Tools::SongWad->FindByName( _T( "Evidence^Blind_Digital" ) );
		Tools::Song_Evidence->Volume = .7f;

		Tools::Song_GetaGrip = Tools::SongWad->FindByName( _T( "Get_a_Grip^Peacemaker" ) );
		Tools::Song_GetaGrip->Volume = 1;

		Tools::Song_House = Tools::SongWad->FindByName( _T( "House^Blind_Digital" ) );
		Tools::Song_House->Volume = .7f;

		Tools::Song_Nero = Tools::SongWad->FindByName( _T( "Nero's_Law^Peacemaker" ) );
		Tools::Song_Nero->Volume = 1;

		Tools::Song_Ripcurl = Tools::SongWad->FindByName( _T( "Ripcurl^Blind_Digital" ) );
		Tools::Song_Ripcurl->Volume = .7f;

		Tools::Song_FatInFire = Tools::SongWad->FindByName( _T( "The_Fat_is_in_the_Fire^Peacemaker" ) );
		Tools::Song_FatInFire->Volume = .9f;

		Tools::Song_Heavens = Tools::SongWad->FindByName( _T( "The_Heavens_Opened^Peacemaker" ) );
		Tools::Song_Heavens->Volume = 1;

		Tools::Song_TidyUp = Tools::SongWad->FindByName( _T( "Tidy_Up^Peacemaker" ) );
		Tools::Song_TidyUp->Volume = 1;

		Tools::Song_WritersBlock = Tools::SongWad->FindByName( _T( "Writer's_Block^Peacemaker" ) );
		Tools::Song_WritersBlock->Volume = 1;

		// Create the standard playlist
		//Tools::SongList_Standard.AddRange( Tools::SongWad->SongList );
		AddRange( Tools::SongList_Standard, Tools::SongWad->SongList );
		//Tools::SongList_Standard.Remove( Tools::Song_Happy );
		Remove( Tools::SongList_Standard, Tools::Song_Happy );
		//Tools::SongList_Standard.Remove( Tools::Song_140mph );
		Remove( Tools::SongList_Standard, Tools::Song_140mph );
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
			int i = ( *file ).find( _T( "Sound" ) ) + 5 + 1;
			int j = ( *file ).find( _T( "." ), i );

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

		std::wstring path = Path::Combine( Globals::ContentDirectory, _T( "Sound" ) );
		std::vector<std::wstring> files = Directory::GetFiles( path );
		for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		{
			int i = ( *file ).find( _T( "Sound" ) ) + 5 + 1;
			if ( i < 0 )
				continue;
			int j = ( *file ).find( _T( "." ), i );
			if ( j <= i )
				continue;
			std::wstring name = ( *file ).substr( i, j - i );
			std::wstring extension = ( *file ).substr( j + 1 );

			if ( extension == _T( "xnb" ) )
			{
				if ( CreateNewWad )
					Tools::SoundWad->AddSound( manager->Load<boost::shared_ptr<SoundEffect> >( _T( "Sound/" ) + name ), name );
				else
				{
					boost::shared_ptr<SoundEffect> NewSound = manager->Load<boost::shared_ptr<SoundEffect> >( _T( "Sound/" ) + name );

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

		// Fonts
		FontLoad();

		// Load the art!
		PreloadArt();

		// Load the music!
		LoadMusic( CreateNewWads );

		// Load the sound!
		LoadSound( CreateNewWads );
	}

	void Resources::PreloadArt()
	{
		//std::wstring path = Path::Combine( Globals::ContentDirectory, _T( "Art" ) );
		//std::vector<std::wstring> files = Tools::GetFiles( path, true );
		//for ( std::vector<std::wstring>::const_iterator file = files.begin(); file != files.end(); ++file )
		//{
		//	if ( Tools::GetFileExt( path, *file ) == _T( "xnb" ) )
		//	{
		//		Tools::TextureWad->AddTexture( 0, _T( "Art/" ) + Tools::GetFileName( path, *file ) );
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

	void Resources::LoadResources()
	{
		// FIXME: Load resources in other thread.
		//LoadThread = ThreadHelper::EasyThread( 5, _T( "LoadThread" ), boost::make_shared<Action>( &_LoadThread ) );
		_LoadThread();
	}

boost::shared_ptr<Thread> Resources::LoadThread = 0;

	void Resources::_LoadThread()
	{
		boost::shared_ptr<CloudberryKingdom::CloudberryKingdomGame> Ck = Tools::TheGame;

		Tools::Write( Format( _T( "Load thread starts ... NOW!" ) ).c_str() );
		//Tools::Write( Format( _T( "Load thread starts at {0}" ), DateTime::Now() ) );
		
		//Thread::SpinWait( 100 );

		Tools::Write( _T( "Start" ) );

		// Initialize the Gamepads
		Tools::GamepadState = std::vector<GamePadState>( 4 );
		Tools::PrevGamepadState = std::vector<GamePadState>( 4 );

		// Fireball texture
		Fireball::PreInit();

		// Load art
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Environments") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Bob") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Buttons") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Characters") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Coins") );
		//Tools.TextureWad.LoadFolder(Tools.GameClass.Content, "Effects");
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("HeroItems") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("LoadScreen_Initial") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("LoadScreen_Level") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Menu") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Old_Art_Holdover") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Title") );

		Tools::Write( _T( "ArtMusic done..." ) );

		// Load the tile info
		LoadInfo();
		TileSets::Init();

		Fireball::InitRenderTargets( Ck->MyGraphicsDevice, Ck->MyGraphicsDevice->PP, 300, 200 );

		ParticleEffects::Init();

		Awardments::Init();

	#if defined(PC_VERSION)
		// Mouse pointer
		Ck->MousePointer = boost::make_shared<QuadClass>();
		Ck->MousePointer->Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( _T( "Hand_Open" ) ) );
		Ck->MousePointer->ScaleYToMatchRatio( 70 );

		// Mouse back icon
		Ck->MouseBack = boost::make_shared<QuadClass>();
		Ck->MouseBack->Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( _T( "charmenu_larrow_1" ) ) );
		Ck->MouseBack->ScaleYToMatchRatio( 40 );
		Ck->MouseBack->Quad_Renamed.SetColor( Color( unsigned char( 255 ), unsigned char( 150 ), unsigned char( 150 ), unsigned char( 100 ) ) );
	#endif

		CloudberryKingdomGame::StaticIntializer_AfterResourcesLoad();

		Prototypes::LoadObjects();
		ObjectIcon::InitIcons();

		std::cout << _T( "Total resources: " ) << ResourceLoadedCountRef->MyFloat << std::endl;

		// Note that we are done loading.
		LoadingResources->MyBool = false;
		Tools::Write( _T( "Loading done!" ) );

		//Tools::Write( Format( _T( "Load thread done at {0}" ), DateTime::Now ) );
		Tools::Write( Format( _T( "Load thread done ... NOW!" ) ).c_str() );
	}
}
