#include <global_header.h>



namespace Forms = System::Windows::Forms;



namespace CloudberryKingdom
{

	CloudberryKingdomGame::ExitProxy::ExitProxy( const std::shared_ptr<CloudberryKingdomGame> &ckg )
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

	CloudberryKingdomGame::MakeTestLevelInitializeHelper::MakeTestLevelInitializeHelper( const std::shared_ptr<CloudberryKingdomGame> &ckg )
	{
		this->ckg = ckg;
	}

	void CloudberryKingdomGame::MakeTestLevelInitializeHelper::Apply( const std::shared_ptr<PieceSeedData> &piece )
	{
		ckg->TestLevelInit( piece );
	}

	CloudberryKingdomGame::TestLevelPostMakeProxy::TestLevelPostMakeProxy( const std::shared_ptr<CloudberryKingdomGame> &ckg )
	{
		this->ckg = ckg;
	}

	void CloudberryKingdomGame::TestLevelPostMakeProxy::Apply( const std::shared_ptr<Level> &level )
	{
		ckg->TestLevelPostMake( level );
	}

Version CloudberryKingdomGame::GameVersion = Version( 0, 2, 4 );
std::vector<std::wstring> CloudberryKingdomGame::args = _T( "" );
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
std::wstring CloudberryKingdomGame::TileSetToTest = _T( "cave" );
std::wstring CloudberryKingdomGame::ModRoot = _T( "Standard" );
bool CloudberryKingdomGame::AlwaysSkipDynamicArt = false;
bool CloudberryKingdomGame::HideGui = false;
bool CloudberryKingdomGame::HideForeground = false;
bool CloudberryKingdomGame::UseNewBob = false;
std::shared_ptr<SimpleGameFactory> CloudberryKingdomGame::TitleGameFactory = TitleGameData_MW::Factory;
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

#if defined(DEBUG) || defined(INCLUDE_EDITOR)
bool CloudberryKingdomGame::AlwaysGiveTutorials = true;
#endif

#if defined(DEBUG) || defined(INCLUDE_EDITOR)
bool CloudberryKingdomGame::UnlockAll = true;
#endif

#if defined(DEBUG) || defined(INCLUDE_EDITOR)
bool CloudberryKingdomGame::SimpleAiColors = false;
#endif

#if ! (defined(DEBUG) || defined(INCLUDE_EDITOR))
bool CloudberryKingdomGame::AlwaysGiveTutorials = false;
#endif

#if ! (defined(DEBUG) || defined(INCLUDE_EDITOR))
bool CloudberryKingdomGame::UnlockAll = true;
#endif

#if ! (defined(DEBUG) || defined(INCLUDE_EDITOR))
bool CloudberryKingdomGame::SimpleAiColors = false;
#endif

	void CloudberryKingdomGame::Exit()
	{
		Tools::GameClass->Exit();
	}

	void CloudberryKingdomGame::ProcessArgs( std::vector<std::wstring&> args )
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

		LoadDynamic = true;
		AlwaysSkipDynamicArt = false;


		CloudberryKingdomGame::args = args;

		std::shared_ptr<std::vector<std::wstring> > list = std::vector<std::wstring>( args );
		list->Reverse();
		std::shared_ptr<std::stack<std::wstring> > stack = std::stack<std::wstring>( list );

		while ( stack->Count > 0 )
		{
			std::shared_ptr<Object> arg = stack->Pop();

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//			switch (arg)
//ORIGINAL LINE: case "background_editor":
			if ( arg == _T( "background_editor" ) )
			{
					StartAsBackgroundEditor = true;
					LoadDynamic = true;
			}
//ORIGINAL LINE: case "test_level":
			else if ( arg == _T( "test_level" ) )
			{
					StartAsTestLevel = true;
					LoadDynamic = true;
			}
//ORIGINAL LINE: case "test_bob_animation":
			else if ( arg == _T( "test_bob_animation" ) )
			{
					StartAsBobAnimationTest = true;
					LoadDynamic = false;
			}
//ORIGINAL LINE: case "test_all":
			else if ( arg == _T( "test_all" ) )
			{
					ShowSongInfo = false;
					UseNewBob = true;
					StartAsFreeplay = true;
					LoadDynamic = true;
			}
//ORIGINAL LINE: case "test_all_old_bob":
			else if ( arg == _T( "test_all_old_bob" ) )
			{
					ShowSongInfo = false;
					StartAsFreeplay = true;
					LoadDynamic = true;

			}
//ORIGINAL LINE: case "mod_root":
			else if ( arg == _T( "mod_root" ) )
			{
					LoadDynamic = true;
					if ( stack->Count > 0 )
						ModRoot = stack->Pop();

			}
			else
			{
			}
		}
	}

	CloudberryKingdomGame::CloudberryKingdomGame()
	{
		InitializeInstanceFields();
		MyGraphicsDeviceManager = std::make_shared<GraphicsDeviceManager>( Tools::GameClass );
		MyGraphicsDeviceManager->PreparingDeviceSettings += std::make_shared<EventHandler<PreparingDeviceSettingsEventArgs*> >( this, &CloudberryKingdomGame::graphics_PreparingDeviceSettings );

		Tools::GameClass->getContent()->RootDirectory = _T("Content");

		Tools::TheGame = this;
	}

	void CloudberryKingdomGame::graphics_PreparingDeviceSettings( const std::shared_ptr<Object> &sender, const std::shared_ptr<PreparingDeviceSettingsEventArgs> &e )
	{
		//graphics.PreferMultiSampling = false;
		//graphics.MyGraphicsDevice.PresentationParameters.MultiSampleCount = 16;

		//graphics.PreferMultiSampling = true;
		//graphics.MyGraphicsDevice.PresentationParameters.MultiSampleCount = 16;
	}

	void CloudberryKingdomGame::Initialize()
	{
	#if defined(WINDOWS)
		EventInput::Initialize( Tools::GameClass->getWindow() );
	#endif
		Globals::ContentDirectory = Tools::GameClass->getContent()->RootDirectory;

		Tools::LoadEffects( Tools::GameClass->getContent(), true );

		ButtonString::Init();
		ButtonCheck::Reset();

		// Volume control
		Tools::SoundVolume = std::make_shared<WrappedFloat>();
		Tools::SoundVolume->MinVal = 0;
		Tools::SoundVolume->MaxVal = 1;
		Tools::SoundVolume->setVal( .7f );

		Tools::MusicVolume = std::make_shared<WrappedFloat>();
		Tools::MusicVolume->MinVal = 0;
		Tools::MusicVolume->MaxVal = 1;
		Tools::MusicVolume->setVal( 1 );
		Tools::MusicVolume->SetCallback = std::make_shared<UpdateVolumeProxy>();

	#if defined(DEBUG) || defined(INCLUDE_EDITOR)
		Tools::SoundVolume->setVal( 0 );
		Tools::MusicVolume->setVal( 0 );
	#endif

	#if defined(PC_VERSION)
		// The PC version let's the player specify resolution, key mapping, and so on.
		// Try to load these now.
		PlayerManager::RezData rez;

		//PlayerManager.SavePlayerData = new _SavePlayerData();
		//PlayerManager.SavePlayerData.ContainerName = "PlayerData";
		//PlayerManager.SavePlayerData.FileName = "PlayerData.hsc";
		//PlayerManager.SaveRezAndKeys();
		//rez = PlayerManager.LoadRezAndKeys();
		//Tools.Warning();
		try
		{
			rez = PlayerManager::LoadRezAndKeys();
		}
		catch ( ... )
		{
			rez = PlayerManager::RezData();
			rez.Custom = false;
		}
	#elif defined(WINDOWS)
		PlayerManager::RezData rez = PlayerManager::RezData();
		rez.Custom = true;
	#if defined(DEBUG) || defined(INCLUDE_EDITOR)
		rez.Fullscreen = false;
	#else
		rez.Fullscreen = true;
	#endif
		rez.Width = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Width;
		rez.Height = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Height;
	#endif

		// Some possible resolutions.
		Resolutions[ 0 ] = ResolutionGroup();
		Resolutions[ 0 ].Backbuffer = IntVector2( 1280, 800 );
		Resolutions[ 0 ].Bob_Renamed = IntVector2( 135, 0 );
		Resolutions[ 0 ].TextOrigin = Vector2::Zero;
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
		MyGraphicsDeviceManager->SynchronizeWithVerticalRetrace = true;

		// Set the actual graphics device,
		// based on the resolution preferences established above.
	#if defined(PC_VERSION) || defined(WINDOWS)
		if ( rez.Custom )
		{
			if ( !rez.Fullscreen )
			{
				rez.Height = static_cast<int>( ( 720 / 1280 ) * rez.Width );
			}

			MyGraphicsDeviceManager->PreferredBackBufferWidth = rez.Width;
			MyGraphicsDeviceManager->PreferredBackBufferHeight = rez.Height;
			MyGraphicsDeviceManager->IsFullScreen = rez.Fullscreen;
		}
		else
		{
			MyGraphicsDeviceManager->PreferredBackBufferWidth = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Width;
			MyGraphicsDeviceManager->PreferredBackBufferHeight = GraphicsAdapter::DefaultAdapter->CurrentDisplayMode->Height;
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

		// Fill the pools
		ComputerRecording::InitPool();

		fps = 0;
	}

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void CloudberryKingdomGame::SignedInGamer_SignedOut( const std::shared_ptr<Object> &sender, const std::shared_ptr<SignedOutEventArgs> &e )
	{
		SaveGroup::SaveAll();

		if ( Tools::CurGameData != 0 )
			Tools::CurGameData->OnSignOut( e );
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void CloudberryKingdomGame::SignedInGamer_SignedIn( const std::shared_ptr<Object> &sender, const std::shared_ptr<SignedInEventArgs> &e )
	{
		int Index = static_cast<int>( e->Gamer->PlayerIndex );
		std::wstring Name = e->Gamer->Gamertag;

		std::shared_ptr<PlayerData> data = std::make_shared<PlayerData>();
		data->Init( Index );
		PlayerManager::Players[ Index ] = data;

		SaveGroup::LoadGamer( Name, data );
	}
#endif

	void CloudberryKingdomGame::LoadContent()
	{
		std::shared_ptr<CloudberryKingdom::CloudberryKingdomGame> Ck = Tools::TheGame;

		//BenchmarkLoadSize();
		//Tools.Warning();

		MyGraphicsDevice = MyGraphicsDeviceManager->GraphicsDevice;

		Tools::LoadBasicArt( Tools::GameClass->getContent() );

		Tools::Render = std::make_shared<MainRender>( MyGraphicsDevice );

		Tools::QDrawer = std::make_shared<QuadDrawer>( MyGraphicsDevice, 1000 );
		Tools::QDrawer->DefaultEffect = Tools::EffectWad->FindByName( _T( "NoTexture" ) );
		Tools::QDrawer->DefaultTexture = Tools::TextureWad->FindByName( _T( "White" ) );

		Tools::Device = MyGraphicsDevice;
		Tools::t = 0;

		LogoScreenUp = true;

		Tools::Render->MySpriteBatch = std::make_shared<SpriteBatch>( MyGraphicsDevice );

		ScreenWidth = MyGraphicsDevice->PresentationParameters->BackBufferWidth;
		ScreenHeight = MyGraphicsDevice->PresentationParameters->BackBufferHeight;

		MainCamera = std::make_shared<Camera>( ScreenWidth, ScreenHeight );

		MainCamera->Update();

		// Pre load. This happens before anything appears.
		Resources::LoadAssets( true );

		// Initialize players
		PlayerManager::Init();

		// Initialize heroes
		BobPhsx::CustomPhsxData::InitStatic();

		// Load saved files
		Thread::CurrentThread->CurrentCulture = System::Globalization::CultureInfo::InvariantCulture;
		SaveGroup::Initialize();

		// Localization
		Localization::SetLanguage( Localization::Language_ENGLISH );
		//Localization.SetLanguage(Localization.Language.Portuguese);

		// Benchmarking and preprocessing
		//PreprocessArt();
		//BenchmarkAll();
		//Tools.Warning(); return;

		//_LoadThread(); return;

		// Create the initial loading screen
		LoadingScreen_Renamed = std::make_shared<InitialLoadingScreen>( Tools::GameClass->getContent(), Resources::ResourceLoadedCountRef );

		// Load resource thread
		Resources::LoadResources();

	#if defined(WINDOWS)
		delay( 2 );
	#endif

	#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
		SignedInGamer::SignedIn += std::make_shared<EventHandler<SignedInEventArgs*> >( this, &CloudberryKingdomGame::SignedInGamer_SignedIn );
		SignedInGamer::SignedOut += std::make_shared<EventHandler<SignedOutEventArgs*> >( this, &CloudberryKingdomGame::SignedInGamer_SignedOut );
	#endif

		MainVideo::StartVideo_CanSkipIfWatched( _T( "LogoSalad" ) );
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

	const std::shared_ptr<GameData> &CloudberryKingdomGame::getGame() const
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

	void CloudberryKingdomGame::PhsxStep()
	{
		DoToDoList();
	#if defined(WINDOWS)
	#if defined(PC_DEBUG) || (defined(WINDOWS) && defined(DEBUG)) || defined(INCLUDE_EDITOR)
		// Debug tools
		if ( DebugModePhsx() )
			return;
	#endif

		// Do game update.
		if ( !Tools::StepControl || ( Tools::Keyboard.IsKeyDownCustom( Keys::Enter ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::Enter ) ) )
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

		if ( !KeyboardExtension::Freeze && Tools::CurLevel->ResetEnabled() && Tools::Keyboard.IsKeyDownCustom(ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey) && !Tools::PrevKeyboard.IsKeyDownCustom(ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey) )
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
				if ( Tools::GamepadState[ i ].Buttons->LeftShoulder == ButtonState::Pressed && Tools::GamepadState[ i ].Buttons->RightShoulder == ButtonState::Pressed && ( Tools::PrevGamepadState[ i ].Buttons::LeftShoulder != ButtonState::Pressed || Tools::PrevGamepadState[ i ].Buttons::RightShoulder != ButtonState::Pressed ) )
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
					if ( Tools::GamepadState[ i ].Buttons::LeftShoulder != ButtonState::Pressed && Tools::GamepadState[ i ].Buttons::RightShoulder != ButtonState::Pressed )
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
		//Tools.GameClass.TargetElapsedTime = TargetElapsedTime;
		//Tools.GameClass.IsFixedTimeStep = true;
	}

	void CloudberryKingdomGame::Draw( const std::shared_ptr<GameTime> &gameTime )
	{
	#if defined(DEBUG_OBJDATA)
		ObjectData::UpdateWeak();
	#endif
		DeltaT = gameTime->ElapsedGameTime.TotalSeconds;

		// Accelerate asset loading
		if ( LogoScreenUp )
			Resources::LoadThread->Join( 1 );

		// Prepare to draw
		Tools::DrawCount++;
		if ( SetupToRender() )
			return;

		// Main Video
		if ( MainVideo::Draw() )
			return;

		// Fps
		UpdateFps( gameTime );

		// Draw nothing if Xbox guide is up
	#if defined(XBOX) || defined(XBOX_SIGNIN)
		if ( Guide::IsVisible )
			return;
	#endif

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

	void CloudberryKingdomGame::GameUpdate( const std::shared_ptr<GameTime> &gameTime )
	{
		// Update controller/keyboard states
		ButtonCheck::UpdateControllerAndKeyboard_StartOfStep();

		// Update sounds
		if ( !LogoScreenUp )
			Tools::SoundWad->Update();

		// Update songs
		if ( Tools::SongWad != 0 )
			Tools::SongWad->PhsxStep();

		fps = .3f * fps + .7f * ( 1000 / static_cast<float>( __max( .00000231f, gameTime->ElapsedGameTime.TotalMilliseconds ) ) );

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

	void CloudberryKingdomGame::UpdateFps( const std::shared_ptr<GameTime> &gameTime )
	{
		// Track time, changes in time, and FPS
		Tools::gameTime = gameTime;
		DrawCount++;

		// Update fps
		float new_t = static_cast<float>( gameTime->TotalGameTime.TotalSeconds );
		Tools::dt = new_t - Tools::t;
		Tools::t = new_t;
	}

	bool CloudberryKingdomGame::SetupToRender()
	{
		// Set the viewport to the whole screen
		MyGraphicsDevice->Viewport = Viewport { X = 0, Y = 0, Width = MyGraphicsDevice->PresentationParameters->BackBufferWidth, Height = MyGraphicsDevice->PresentationParameters->BackBufferHeight, MinDepth = 0, MaxDepth = 1 };

		// Clear whole screen to black
		MyGraphicsDevice->Clear( Color::Black );

	#if defined(WINDOWS)
		if ( !ActiveInactive() )
			return true;
	#endif

		// Make the actual view port we draw to, and clear it
		Tools::Render->MakeInnerViewport();
		MyGraphicsDevice->Clear( Color::Black );

		MyGraphicsDevice->Viewport = Tools::Render->MainViewport;

		// Default camera
		Vector4 cameraPos = Vector4( MainCamera->Data.Position.X, MainCamera->Data.Position.Y, MainCamera->getZoom().X, MainCamera->getZoom().Y ); //.001f, .001f);

		Tools::Render->SetStandardRenderStates();

		Tools::QDrawer->SetInitialState();
		ComputeFire();

		Tools::EffectWad->SetCameraPosition( cameraPos );

		Tools::SetDefaultEffectParams( MainCamera->AspectRatio );

		Tools::Render->SetStandardRenderStates();

		return false;
	}

	void CloudberryKingdomGame::ComputeFire()
	{
		if ( !LogoScreenUp && !LogoScreenPropUp )
		{
			if ( !Tools::CurGameData->Loading && Tools::CurLevel->PlayMode == 0 && Tools::CurGameData != 0 && !Tools::CurGameData->Loading && ( !Tools::CurGameData->PauseGame || CharacterSelectManager::IsShowing ) )
			{
				// Compute fireballs textures
				MyGraphicsDevice->BlendState = BlendState::Additive;
				Fireball::DrawFireballTexture( MyGraphicsDevice, Tools::EffectWad );
				Fireball::DrawEmitterTexture( MyGraphicsDevice, Tools::EffectWad );

				MyGraphicsDevice->BlendState = BlendState::AlphaBlend;
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
		// Load art
		Start2();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Environments") );
		long long LoadEnviros = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Bob") );
		long long LoadBob = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Menu") );
		long long LoadMenus = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Coins") );
		//Tools.TextureWad.LoadFolder(Tools.GameClass.Content, "Effects");
		long long LoadEffects = Stop();

		Start();
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Buttons") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Characters") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("HeroItems") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("LoadScreen_Initial") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("LoadScreen_Level") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Old Art Holdover") );
		Tools::TextureWad->LoadFolder( Tools::GameClass->getContent(), _T("Title") );
		long long LoadRest = Stop();

		Tools::Write( _T( "ArtMusic done..." ) );

		Start();
		TileSets::Init();
		long long Tiles = Stop();

		Start();
		Fireball::InitRenderTargets( MyGraphicsDevice, MyGraphicsDevice->PresentationParameters, 300, 200 );
		ParticleEffects::Init();
//C# TO C++ CONVERTER NOTE: The variable Particle was renamed since it is named the same as a user-defined type:
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
		std::cout << _T( "Load particles " ) << Particle << std::endl;
		std::cout << _T( "Load players   " ) << Players << std::endl;
		std::cout << _T( "Load saves     " ) << LoadSaves << std::endl;
		std::cout << _T( "Load Protos    " ) << Protos << std::endl;
		std::cout << _T( "Load Icons     " ) << Icons << std::endl;
		std::cout << _T( "Load Small     " ) << GamePads << std::endl;
		std::cout << std::endl;
		std::cout << _T( "Total          " ) << Total << std::endl;
		std::cout << _T( "" ) << std::endl;
	}

std::shared_ptr<System::Diagnostics::Stopwatch> CloudberryKingdomGame::stopwatch = 0;

	void CloudberryKingdomGame::Start()
	{
		stopwatch = std::make_shared<System::Diagnostics::Stopwatch>();
		stopwatch->Start();
	}

	long long CloudberryKingdomGame::Stop()
	{
		stopwatch->Stop();
		return stopwatch->ElapsedTicks;
	}

std::shared_ptr<System::Diagnostics::Stopwatch> CloudberryKingdomGame::stopwatch2 = 0;

	void CloudberryKingdomGame::Start2()
	{
		stopwatch2 = std::make_shared<System::Diagnostics::Stopwatch>();
		stopwatch2->Start();
	}

	long long CloudberryKingdomGame::Stop2()
	{
		stopwatch2->Stop();
		return stopwatch2->ElapsedTicks;
	}

	void CloudberryKingdomGame::BenchmarkLoadSize()
	{
		std::cout << Tools::GameClass->getContent()->RootDirectory << std::endl;

		Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Environments\\Snow"));


		long long big = 0;
		long long small = 0;

		Start();
		for ( int i = 0; i < 1; i++ )
		{
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Bob\\Classic\\v1\\Stand\\Bob_Stand_0001"));
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Bob\\Classic\\v1\\Stand\\Bob_Stand_0002"));
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Bob\\Classic\\v1\\Stand\\Bob_Stand_0003"));
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Bob\\Classic\\v1\\Stand\\Bob_Stand_0004"));
		}
		small = Stop();

		Start();
		for ( int i = 0; i < 1; i++ )
		{
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Environments\\Castle\\Pillars\\Pillar_Castle_1000"));
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Environments\\Cave\\Pillars\\Pillar_Cave_1000"));
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Environments\\Cloud\\Pillars\\Pillar_Cloud_1000"));
			Tools::GameClass->getContent()->Load<Texture*>(_T("Art\\Environments\\Forest\\Pillars\\Pillar_Forest_1000"));
		}
		big = Stop();

		std::cout << _T( "big took " ) << big << std::endl;
		std::cout << _T( "small took " ) << small << std::endl;
		std::cout << _T( "" ) << std::endl;
	}

#if defined(DEBUG)
	bool CloudberryKingdomGame::DebugModePhsx()
	{
	#if defined(WINDOWS)
		if ( !KeyboardExtension::Freeze )
		{
			// Test title screen
			if ( Tools::Keyboard.IsKeyDown( Keys::G ) && !Tools::PrevKeyboard.IsKeyDown( Keys::G ) )
			{
				//TitleGameFactory = TitleGameData_Intense.Factory;
				TitleGameFactory = TitleGameData_MW::Factory;
				//TitleGameFactory = TitleGameData_Forest.Factory;

				Tools::SongWad->Stop();
				Tools::CurGameData = CloudberryKingdomGame::TitleGameFactory->Make();
				return true;
			}

			if ( Tools::Keyboard.IsKeyDown( Keys::J ) && !Tools::PrevKeyboard.IsKeyDown( Keys::J ) )
			{
				Tools::CurGameData->FadeToBlack();
			}
		}

		//// Give award
		//if (Tools.keybState.IsKeyDown(Keys.S) && !Tools.PrevKeyboardState.IsKeyDown(Keys.S))
		//{
		//    Awardments.GiveAward(Awardments.UnlockHeroRush2);
		//}

		if ( !KeyboardExtension::Freeze && Tools::Keyboard.IsKeyDownCustom( Keys::F ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::F ) )
			ShowFPS = !ShowFPS;
	#endif

	#if defined(PC_DEBUG)
		if ( Tools::FreeCam )
		{
			Vector2 pos = Tools::CurLevel->getMainCamera()->Data.Position;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::Right ) )
				pos.X += 130;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::Left ) )
				pos.X -= 130;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::Up ) )
				pos.Y += 130;
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::Down ) )
				pos.Y -= 130;
			Tools::CurLevel->getMainCamera()->EffectivePos += pos - Tools::CurLevel->getMainCamera()->Data.Position;
			Tools::CurLevel->getMainCamera()->Data.Position = Tools::CurLevel->getMainCamera()->Target = pos;
			Tools::CurLevel->getMainCamera()->Update();
		}
	#endif

		// Reload some dynamic data (tileset info, animation specifications).
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::X ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::X ) )
		{
	#if defined(INCLUDE_EDITOR)
			if ( LoadDynamic )
			{
				////Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Art);
				////Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Backgrounds);
				//Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Tilesets);
				//Tools.TextureWad.LoadAllDynamic(Content, EzTextureWad.WhatToLoad.Animations);
				TileSets::LoadSpriteEffects();
				TileSets::LoadCode();
			}
	#endif

			// Make blocks in the current level reset their art to reflect possible changes in the reloaded tileset info.
			for ( std::vector<BlockBase*>::const_iterator block = Tools::CurLevel->Blocks.begin(); block != Tools::CurLevel->Blocks.end(); ++block )
			{
				std::shared_ptr<NormalBlock> nblock = dynamic_cast<NormalBlock*>( *block );
				if ( 0 != nblock )
					nblock->ResetPieces();

				std::shared_ptr<MovingBlock> mblock = dynamic_cast<MovingBlock*>( *block );
				if ( 0 != mblock )
					mblock->ResetPieces();
			}
		}

	#if defined(DEBUG)
		// Reload ALL dynamic data (tileset info, animation specifications, dynamic art, backgrounds).
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::Z ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::Z ) )
		{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( std::vector<BobPhsx*>::const_iterator hero = Bob::HeroTypes.begin(); hero != Bob::HeroTypes.end(); ++hero )
				( *hero )->ResetInfo();

			//Tools.TextureWad.LoadAllDynamic(Tools.GameClass.Content, EzTextureWad.WhatToLoad.Animations);

			//LoadInfo();

			//// Reset blocks
			//foreach (BlockBase block in Tools.CurLevel.Blocks)
			//{
			//    NormalBlock nblock = block as NormalBlock;
			//    if (null != nblock) nblock.ResetPieces();

			//    MovingBlock mblock = block as MovingBlock;
			//    if (null != mblock) mblock.ResetPieces();
			//}
		}
	#endif

		// Turn on a simple green screen background.
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::D9 ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::D9 ) )
			Background::GreenScreen = !Background::GreenScreen;

		Tools::ModNums();

		// Load a test level.
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::D5 ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::D5 ) )
		{
			GameData::LockLevelStart = false;
			LevelSeedData::ForcedReturnEarly = 0;
			MakeTestLevel();
			return true;
		}

		// Hide the GUI. Used for video capture.
		if ( ButtonCheck::State( Keys::D8 ).Pressed )
			HideGui = !HideGui;

		// Hide the foreground. Used for video capture of backgrounds.
		if ( ButtonCheck::State( Keys::D7 ).Pressed )
			HideForeground = !HideForeground;

		// Turn on/off immortality.
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::O ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::O ) )
		{
			for ( std::vector<Bob*>::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			{
				( *bob )->Immortal = !( *bob )->Immortal;
			}
		}

		// Turn on/off graphics.
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::Q ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::Q ) )
			Tools::DrawGraphics = !Tools::DrawGraphics;
		// Turn on/off drawing of collision detection boxes.
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::W ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::W ) )
			Tools::DrawBoxes = !Tools::DrawBoxes;
		// Turn on/off step control. When activated, this allows you to step forward in the game by pressing <Enter>.
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::E ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::E ) )
			Tools::StepControl = !Tools::StepControl;
		// Modify the speed of the game.
		if ( Tools::Keyboard.IsKeyDownCustom( Keys::R ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::R ) )
		{
			Tools::IncrPhsxSpeed();
		}

		// Don't do any of the following if a control box is up.
		if ( !KeyboardExtension::Freeze )
		{
			// Watch the computer make a level during Stage 1 of construction.
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::D3 ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::D3 ) )
			{
				GameData::LockLevelStart = false;
				LevelSeedData::ForcedReturnEarly = 1;
				MakeTestLevel();
				return true;
			}

			// Watch the computer make a level during Stage 2 of construction.
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::D4 ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::D4 ) )
			{
				GameData::LockLevelStart = false;
				LevelSeedData::ForcedReturnEarly = 2;
				MakeTestLevel();
				return true;
			}

			// Zoom in and out.
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::OemComma ) )
			{
				Tools::CurLevel->getMainCamera()->setZoom(Tools::CurLevel->getMainCamera()->getZoom() * .99f);
				Tools::CurLevel->getMainCamera()->EffectiveZoom *= .99f;
			}
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::OemPeriod ) )
			{
				Tools::CurLevel->getMainCamera()->setZoom(Tools::CurLevel->getMainCamera()->getZoom() / .99f);
				Tools::CurLevel->getMainCamera()->EffectiveZoom /= .99f;
			}

			// Turn on/off FreeCam, which allows the user to pan the camera through the level freely.
			if ( Tools::Keyboard.IsKeyDownCustom( Keys::P ) && !Tools::PrevKeyboard.IsKeyDownCustom( Keys::P ) )
				Tools::FreeCam = !Tools::FreeCam;
		}

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

std::wstring CloudberryKingdomGame::debugstring = _T( "" );

	void CloudberryKingdomGame::DrawDebugInfo()
	{
		Tools::StartSpriteBatch();

		if ( Tools::ShowNums )
		{
			std::wstring nums = Tools::Num_0_to_2 + _T( "\n\n" ) + Tools::Num_0_to_360;

			Tools::StartSpriteBatch();
			Tools::Render->MySpriteBatch->DrawString( Resources::LilFont->Font, nums, Vector2( 0, 100 ), Color::Orange, 0, Vector2::Zero,.4f, SpriteEffects::None, 0 );
			Tools::Render->EndSpriteBatch();
			return;
		}

	#if defined(WINDOWS)
		// Grace period for falling
		//string str = "";
		//if (Tools.CurLevel != null && Tools.CurLevel.Bobs.Count > 0)
		//{
		//    //var phsx = Tools.CurLevel.Bobs[0].MyPhsx as BobPhsxNormal;
		//    //if (null != phsx) str = phsx.FallingCount.ToString();

		//    var phsx = Tools.CurLevel.Bobs[0].MyPhsx as BobPhsxMeat;
		//    //if (null != phsx) str = phsx.WallJumpCount.ToString();
		//    if (null != phsx) str = phsx.StepsSinceSide.ToString();
		//}

		// Mouse
		//string str = string.Format("Mouse delta: {0}", Tools.DeltaMouse);
		//string str = string.Format("Mouse in window: {0}", Tools.MouseInWindow);

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
		//string str  = string.Format("CurLevel PhsxStep: {0}\n", Tools.CurLevel.CurPhsxStep);

		// Score
		//PlayerData p = PlayerManager.Get(0);
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


		Tools::Render->MySpriteBatch->DrawString( Resources::LilFont->Font, str, Vector2( 0, 100 ), Color::Orange, 0, Vector2::Zero, 1, SpriteEffects::None, 0 );
		Tools::Render->EndSpriteBatch();
	}

	void CloudberryKingdomGame::MakeEmptyLevel()
	{
		std::shared_ptr<Level> level = std::make_shared<Level>();
		level->setMainCamera( std::make_shared<Camera>() );
		level->CurPiece = level->StartNewPiece( 0, 0, 4 );
		level->CurPiece->StartData[ 0 ].Position = Vector2( 0, 0 );
		level->getMainCamera()->BLCamBound = Vector2(-100000, 0);
		level->getMainCamera()->TRCamBound = Vector2(100000, 0);
		level->getMainCamera()->Update();
		level->TimeLimit = -1;

		level->MyBackground = std::make_shared<RegularBackground>();
		level->MyBackground->Init( level );

		Tools::CurGameData = level->MyGame = std::make_shared<GameData>();
		Tools::CurGameData->MyLevel = Tools::CurLevel = level;
	}

	void CloudberryKingdomGame::MakeTestLevel()
	{
		//PlayerManager.Players[0].Exists = true;
		//PlayerManager.Players[1].Exists = true;
		//PlayerManager.Players[2].Exists = true;
		//PlayerManager.Players[3].Exists = true;

		std::shared_ptr<LevelSeedData> data = std::make_shared<LevelSeedData>();


		//data.ReadString("0;s:1830873138;h:2,0,2,0;t:sea;n:1;l:2150;u:0,0,0,0,0,2,4.625,0,0,0,0,0,3.75,6.375,0,0,0,0,0,0,0,7.75,0,6.625;");
		//GameData.StartLevel(data);
		//return;

		data->setSeed( Tools::GlobalRnd->Rnd->Next() );
		//data.Seed = 110040853;
		std::cout << _T( "Seed chosen = " ) << data->getSeed() << std::endl;

		//data.MyBackgroundType = BackgroundType.Dungeon;

		//TileSetToTest = "sea_rain";
		//TileSetToTest = "hills";
		//TileSetToTest = "forest";
		TileSetToTest = _T( "cloud" );
		//TileSetToTest = "cave";
		//TileSetToTest = "castle";

		if ( TileSetToTest == _T( "" ) )
			data->SetTileSet( _T( "castle" ) );
		else
			data->SetTileSet( TileSetToTest );

		//data.SetTileSet(TileSets.Dungeon);

		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Wheel, Hero_Shape.Small, Hero_MoveMod.Jetpack);
		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Bouncy, Hero_Shape.Classic, Hero_MoveMod.Jetpack);
		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Box, Hero_Shape.Classic, Hero_MoveMod.Jetpack);
		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Classic, Hero_Shape.Small, Hero_MoveMod.Double);
		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Wheel, Hero_Shape.Small, Hero_MoveMod.Double);

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
		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Classic, Hero_Shape.Classic, Hero_MoveMod.Double);
		//var d = new BobPhsx.CustomPhsxData();
		//d.Init();
		//d[BobPhsx.CustomData.numjumps] = 2;
		//data.DefaultHeroType.SetCustomPhsx(d);

		// Long jetpack
		//data.DefaultHeroType = BobPhsx.MakeCustom(Hero_BaseType.Classic, Hero_Shape.Classic, Hero_MoveMod.Jetpack);
		//var d = new BobPhsx.CustomPhsxData();
		//d.Init();
		//d[BobPhsx.CustomData.jetpackfuel] *= 2;
		//d[BobPhsx.CustomData.jetpackaccel] *= 2;
		//data.DefaultHeroType.SetCustomPhsx(d);


		data->MyGeometry = LevelGeometry_RIGHT;
		//data.MyGeometry = LevelGeometry.Up;
		//data.PieceLength = 90000;
		data->PieceLength = 15000;
		//data.PieceLength = 37000;
		data->NumPieces = 1;

		data->MyGameType = NormalGameData::Factory;
		//data.MyGameType = PlaceGameData.Factory;

		//data.MyGameFlags.IsTethered = true;
		//data.MyGameFlags.IsDoppleganger = true;
		//data.MyGameFlags.IsDopplegangerInvert = true;

		data->Initialize( std::make_shared<MakeTestLevelInitializeHelper>( this ) );

		// Add Landing Zone
		//data.PieceSeeds[0].Style.MyInitialPlatsType = StyleData.InitialPlatsType.LandingZone;

		data->PostMake->Add( std::make_shared<TestLevelPostMakeProxy>( this ) );

		//Campaign.CarryPrinces(data);

		// Rumble
		//level.MyGame.AddGameObject(new Rumble());
		//};

		//data.LavaMake = LevelSeedData.LavaMakeTypes.NeverMake;
		data->LavaMake = LevelSeedData::LavaMakeTypes_ALWAYS_MAKE;

		GameData::StartLevel( data );
	}

	void CloudberryKingdomGame::TestLevelPostMake( const std::shared_ptr<Level> &level )
	{
		level->StartRecording();

		level->MyGame->AddGameObject( std::make_shared<HintGiver>() );
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

	void CloudberryKingdomGame::TestLevelInit( const std::shared_ptr<PieceSeedData> &piece )
	{
		//writelist();
		//Tools.Write("!");

		//piece.ZoomType = LevelZoom.Big;
		piece->ExtraBlockLength = 1000;

		//piece.Paths = RndDifficulty.ChoosePaths(piece);
		//piece.Style.AlwaysCurvyMove = true;
		RndDifficulty::ZeroUpgrades( piece->MyUpgrades1 );


		//piece.MyUpgrades1[Upgrade.SpikeyLine] = 5f;
		//piece.MyUpgrades1[Upgrade.Ceiling] = 10;
		////piece.MyUpgrades1[Upgrade.Elevator] = 11;
		//piece.MyUpgrades1[Upgrade.SpikeyGuy] = 5;
		//piece.MyUpgrades1[Upgrade.FireSpinner] = 6;
		//piece.MyUpgrades1[Upgrade.GhostBlock] = 6;
		//piece.MyUpgrades1[Upgrade.Serpent] = 5;
		//piece.MyUpgrades1[Upgrade.Cloud] = 5;
		//piece.MyUpgrades1[Upgrade.Pinky] = 5;
		//piece.MyUpgrades1[Upgrade.Fireball] = 3;
		//piece.MyUpgrades1[Upgrade.Pendulum] = 3;
		//piece.MyUpgrades1[Upgrade.BouncyBlock] = 5;
		//piece.MyUpgrades1[Upgrade.FallingBlock] = 5;

		__Roughly_Abusive( piece );
		//__Roughly_Maso(piece);
		//piece.Style.Masochistic = true;

		piece->MyUpgrades1[ Upgrade_MOVING_BLOCK ] = 8;
		//piece.MyUpgrades1[Upgrade.LavaDrip] = 9;
		//piece.MyUpgrades1[Upgrade.Serpent] = 9;
		//piece.MyUpgrades1[Upgrade.Pendulum] = 9;
		//piece.MyUpgrades1[Upgrade.Fireball] = 9f;
		//piece.MyUpgrades1[Upgrade.Jump] = 8;
		//piece.MyUpgrades1[Upgrade.Speed] = 9;


		piece->MyUpgrades1->CalcGenData( piece->MyGenData->gen1, piece->Style );

		piece->Paths = 1;
		piece->LockNumOfPaths = true;
		piece->Style_SINGLE_PATH_TYPE = StyleData::_SinglePathType_NORMAL;

		/*
		piece.Paths = 2;
	
		SingleData style = piece.Style as SingleData;
		style.InitialDoorYRange = new Vector2(-800);
		style.DoublePathType = StyleData._DoublePathType.Gap;
		*/

		//piece.Style.MyModParams = TestLevelModParams;

		piece->Style_CHANCE_TO_KEEP_UNUSED = 0;

		RndDifficulty::ZeroUpgrades( piece->MyUpgrades2 );
		piece->MyUpgrades1->UpgradeLevels.CopyTo( piece->MyUpgrades2->UpgradeLevels, 0 );
		//piece.MyUpgrades2[Upgrade.Cloud] = 10;
		piece->MyUpgrades2->CalcGenData( piece->MyGenData->gen2, piece->Style );

		piece->Style_MY_INITIAL_PLATS_TYPE = StyleData::InitialPlatsType_DOOR;
		piece->Style_MY_FINAL_PLATS_TYPE = StyleData::FinalPlatsType_DOOR;
	}

	void CloudberryKingdomGame::__Roughly_Maso( const std::shared_ptr<PieceSeedData> &piece )
	{
		piece->MyUpgrades1[ Upgrade_JUMP ] = 1;
		piece->MyUpgrades1[ Upgrade_SPEED ] = 10;

		piece->MyUpgrades1[ Upgrade_SERPENT ] = 7;
		//piece.MyUpgrades1[Upgrade.LavaDrip] = 10;
		piece->MyUpgrades1[ Upgrade_LASER ] = 5;

		piece->MyUpgrades1[ Upgrade_FLY_BLOB ] = 3;
		piece->MyUpgrades1[ Upgrade_GHOST_BLOCK ] = 4;
		////piece.MyUpgrades1[Upgrade.FallingBlock] = 4;
		////piece.MyUpgrades1[Upgrade.BouncyBlock] = 4;
		piece->MyUpgrades1[ Upgrade_MOVING_BLOCK ] = 4;
		//piece.MyUpgrades1[Upgrade.Elevator] = 1;
		piece->MyUpgrades1[ Upgrade_SPIKEY_GUY ] = 10;
		////piece.MyUpgrades1[Upgrade.Firesnake] = 6;
		piece->MyUpgrades1[ Upgrade_SPIKE ] = 9;
		piece->MyUpgrades1[ Upgrade_FIRE_SPINNER ] = 10;

		piece->MyUpgrades1[ Upgrade_PINKY ] = 4;
		//piece.MyUpgrades1[Upgrade.SpikeyLine] = 2;
		//piece.MyUpgrades1[Upgrade.Conveyor] = 8;
	}

	void CloudberryKingdomGame::__Roughly_Abusive( const std::shared_ptr<PieceSeedData> &piece )
	{
		piece->MyUpgrades1[ Upgrade_JUMP ] = 1;
		piece->MyUpgrades1[ Upgrade_SPEED ] = 3;
		////piece.MyUpgrades1[Upgrade.Serpent] = 0;
		////piece.MyUpgrades1[Upgrade.LavaDrip] = 4;
		piece->MyUpgrades1[ Upgrade_FLY_BLOB ] = 3;
		piece->MyUpgrades1[ Upgrade_GHOST_BLOCK ] = 4;
		piece->MyUpgrades1[ Upgrade_FALLING_BLOCK ] = 4;
		////piece.MyUpgrades1[Upgrade.BouncyBlock] = 4;
		piece->MyUpgrades1[ Upgrade_MOVING_BLOCK ] = 4;
		//piece.MyUpgrades1[Upgrade.Elevator] = 1;
		piece->MyUpgrades1[ Upgrade_SPIKEY_GUY ] = 2;
		////piece.MyUpgrades1[Upgrade.Firesnake] = 6;
		piece->MyUpgrades1[ Upgrade_SPIKE ] = 2;
		piece->MyUpgrades1[ Upgrade_FIRE_SPINNER ] = 2;
		//piece.MyUpgrades1[Upgrade.Laser] = 2;
		piece->MyUpgrades1[ Upgrade_PINKY ] = 1;
		//piece.MyUpgrades1[Upgrade.SpikeyLine] = 2;
		//piece.MyUpgrades1[Upgrade.Conveyor] = 8;
	}

	void CloudberryKingdomGame::TestLevelModParams( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p )
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
		std::shared_ptr<FallingBlock_Parameters> FParams = static_cast<FallingBlock_Parameters*>( p->Style_FIND_PARAMS( FallingBlock_AutoGen::getInstance() ) );
		FParams->Width.SetVal( size );
		std::shared_ptr<MovingBlock_Parameters> MParams = static_cast<MovingBlock_Parameters*>( p->Style_FIND_PARAMS( MovingBlock_AutoGen::getInstance() ) );
		MParams->Size.SetVal( size );
		MParams->Aspect = MovingBlock_Parameters::AspectType_SQUARE;
		MParams->Motion = MovingBlock_Parameters::MotionType_VERTICAL;
		std::shared_ptr<BouncyBlock_Parameters> BParams = static_cast<BouncyBlock_Parameters*>( p->Style_FIND_PARAMS( BouncyBlock_AutoGen::getInstance() ) );
		BParams->Size.SetVal( size );
		std::shared_ptr<FlyingBlob_Parameters> GParams = static_cast<FlyingBlob_Parameters*>( p->Style_FIND_PARAMS( FlyingBlob_AutoGen::getInstance() ) );
		//GParams.Counter
		std::shared_ptr<NormalBlock_Parameters> NParams = static_cast<NormalBlock_Parameters*>( p->Style_FIND_PARAMS( NormalBlock_AutoGen::getInstance() ) );
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
				Tools::CurGameData = CloudberryKingdomGame::TitleGameFactory->Make();
				return;
	#else
				// Start at Screen Saver
				std::shared_ptr<ScreenSaver> Intro = std::make_shared<ScreenSaver>();
				Intro->Init();
				return;
	#endif
			}
		}
	}

	void CloudberryKingdomGame::InitializeInstanceFields()
	{
		Resolutions = std::vector<ResolutionGroup>( 4 );
#if defined(WINDOWS)
		_DrawMouseBackIcon = false;
#endif
		ToDo = std::make_shared<Multicaster>();
#if defined(WINDOWS)
		ShowMouse = false;
#endif
		MediaPlaying_HoldState = false;
		FirstInactiveFrame = true;
		FirstActiveFrame = true;
		DeltaT = 0;
		RunningSlowly = false;
		ShowFPS = false;
		MainString = std::make_shared<StringBuilder>( 100, 100 );
		DoInnerLogoPhsx = true;
	}
}
