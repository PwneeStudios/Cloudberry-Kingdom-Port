#include <global_header.h>

#include "Hacks/List.h"
#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include "Hacks/NET/Path.h"
#include "Hacks/NET/Directory.h"
#include "Hacks/XNA/GamePad.h"
#include "Hacks/XNA/MediaPlayer.h"
#include <Input/Mouse.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void Tools::InitializeStatics()
	{
		Tools::CurrentAftermath = 0;
		Tools::IsMasochistic = false;
		Tools::AutoLoop = false;
		Tools::AutoLoopDelay = 0;
		Tools::_VolumeFade = 0;

		Tools::CurSongVolume = 0;
		Tools::SoundVolume = 0; Tools::MusicVolume = 0;
		Tools::FixedTimeStep = false;
		Tools::WindowBorder = true;
		Tools::GameClass = 0;
		Tools::TheGame = 0;

		std::wstring tempVector2[] = { _T( "A" ), _T( "B" ), _T( "X" ), _T( "Y" ), _T( "RS" ), _T( "LS" ), _T( "RT" ), _T( "LT" ), _T( "RJ" ), _T( "RJ" ), _T( "LJ" ), _T( "LJ" ), _T( "DPad" ), _T( "Start" ) };
		Tools::ButtonNames = VecFromArray( tempVector2 );
		std::wstring tempVector3[] = { _T( "right" ), _T( "up" ), _T( "left" ), _T( "down" ) };
		Tools::DirNames = VecFromArray( tempVector3 );
		Tools::CurGameType = 0;
		Tools::CurGameData = 0;
		Tools::CurLevel = 0;
		Tools::DummyCamera = 0;

		Tools::WorldMap = 0; Tools::TitleGame = 0;
		int tempVector4[] = { 0, 0, 0, 0 };
		Tools::VibrateTimes = VecFromArray( tempVector4 );
		Tools::DifficultyTypes = DifficultyParam_LENGTH;
		Tools::StyleTypes = 8;
		Tools::UpgradeTypes = Upgrade_LENGTH;

		#if defined(WINDOWS)
		//Tools::Keyboard, Tools::PrevKeyboard;
		#endif

		#if defined(WINDOWS)
		//Tools::Mouse, Tools::PrevMouse;
		#endif

		#if defined(WINDOWS)
		//Tools::DeltaMouse, Tools::RawDeltaMouse;
		#endif

		#if defined(WINDOWS)
		Tools::DeltaScroll = 0;
		#endif

		#if defined(WINDOWS)
		Tools::MouseInWindow = false;
		#endif

		Tools::GamepadState;
		Tools::PrevGamepadState;

		Tools::gameTime = 0;
		Tools::GlobalRnd = std::make_shared<Rand>( 0 );
		Tools::EffectWad = 0;
		Tools::BasicEffect, Tools::NoTexture, Tools::CircleEffect, Tools::LightSourceEffect, Tools::HslEffect, Tools::HslGreenEffect, Tools::WindowEffect;
		Tools::PaintEffect_SpriteBatch = 0;
		Tools::TextureWad = 0;
		Tools::SoundContentManager = 0;
		Tools::SoundWad = 0; Tools::PrivateSoundWad = 0;
		Tools::SongWad = 0;
		Tools::QDrawer = 0;
		Tools::Render = 0;
		Tools::Device = 0;
		Tools::DestinationRenderTarget = 0;
		Tools::t = 0;
		Tools::dt = 0;
		Tools::DrawCount = 0;
		Tools::PhsxCount = 0;
		Tools::Song_140mph, Tools::Song_Happy, Tools::Song_BlueChair, Tools::Song_Ripcurl, Tools::Song_Evidence, Tools::Song_GetaGrip, Tools::Song_House, Tools::Song_Nero, Tools::Song_FatInFire, Tools::Song_Heavens, Tools::Song_TidyUp, Tools::Song_WritersBlock;
		Tools::SongList_Standard = std::vector<std::shared_ptr<EzSong> >();
		Tools::FreeCam = false;
		Tools::DrawBoxes = false;
		Tools::DrawGraphics = true;
		Tools::StepControl = false;
		Tools::_PhsxSpeed = 1;
	
		Tools::ShowLoadingScreen = false;
		Tools::CurrentLoadingScreen = 0;

		Tools::CurVolume = -1;
	
		Tools::KillMusicOnLoadingScreen = true;
		Tools::DoNotKillMusicOnNextLoadingscreen = false;

		Tools::WriteRecursiveDepth = 0;
		Tools::WriteObjId = 0;

		Tools::GUIDraws = 0;
		Tools::HoldIllumination = 0;

		Tools::Num_0_to_360 = 0;
		Tools::Num_0_to_2 = 0;
		Tools::ShowNums = false;

		Tools::DebugConvenience = false;
	}

	// Static variables
	std::shared_ptr<AftermathData> Tools::CurrentAftermath;
	bool Tools::IsMasochistic;
	bool Tools::AutoLoop;
	int Tools::AutoLoopDelay;
	float Tools::_VolumeFade;

	float Tools::CurSongVolume;
	std::shared_ptr<WrappedFloat> Tools::SoundVolume, Tools::MusicVolume;
	bool Tools::FixedTimeStep;
	bool Tools::WindowBorder;
	std::shared_ptr<XnaGameClass> Tools::GameClass;
	std::shared_ptr<CloudberryKingdomGame> Tools::TheGame;

	std::vector<std::wstring> Tools::ButtonNames;
	std::vector<std::wstring> Tools::DirNames;
	std::shared_ptr<GameFactory> Tools::CurGameType;
	std::shared_ptr<GameData> Tools::CurGameData;
	std::shared_ptr<Level> Tools::CurLevel;
	std::shared_ptr<Camera> Tools::DummyCamera;

	std::shared_ptr<GameData> Tools::WorldMap, Tools::TitleGame;
	std::vector<int> Tools::VibrateTimes;
	int Tools::DifficultyTypes;
	int Tools::StyleTypes;
	int Tools::UpgradeTypes;

	#if defined(WINDOWS)
	KeyboardState Tools::Keyboard, Tools::PrevKeyboard;
	#endif

	#if defined(WINDOWS)
	MouseState Tools::Mouse, Tools::PrevMouse;
	#endif

	#if defined(WINDOWS)
	Vector2 Tools::DeltaMouse, Tools::RawDeltaMouse;
	#endif

	#if defined(WINDOWS)
	int Tools::DeltaScroll;
	#endif

	#if defined(WINDOWS)
	bool Tools::MouseInWindow;
	#endif

	std::vector<GamePadState> Tools::GamepadState;
	std::vector<GamePadState> Tools::PrevGamepadState;

	std::shared_ptr<GameTime> Tools::gameTime;
	std::shared_ptr<Rand> Tools::GlobalRnd;
	std::shared_ptr<EzEffectWad> Tools::EffectWad;
	std::shared_ptr<EzEffect> Tools::BasicEffect, Tools::NoTexture, Tools::CircleEffect, Tools::LightSourceEffect, Tools::HslEffect, Tools::HslGreenEffect, Tools::WindowEffect;
	std::shared_ptr<Effect> Tools::PaintEffect_SpriteBatch;
	std::shared_ptr<EzTextureWad> Tools::TextureWad;
	std::shared_ptr<ContentManager> Tools::SoundContentManager;
	std::shared_ptr<EzSoundWad> Tools::SoundWad, Tools::PrivateSoundWad;
	std::shared_ptr<EzSongWad> Tools::SongWad;
	std::shared_ptr<QuadDrawer> Tools::QDrawer;
	std::shared_ptr<MainRender> Tools::Render;
	std::shared_ptr<GraphicsDevice> Tools::Device;
	std::shared_ptr<RenderTarget2D> Tools::DestinationRenderTarget;
	float Tools::t;
	float Tools::dt;
	int Tools::DrawCount;
	int Tools::PhsxCount;
	std::shared_ptr<EzSong> Tools::Song_140mph, Tools::Song_Happy, Tools::Song_BlueChair, Tools::Song_Ripcurl, Tools::Song_Evidence, Tools::Song_GetaGrip, Tools::Song_House, Tools::Song_Nero, Tools::Song_FatInFire, Tools::Song_Heavens, Tools::Song_TidyUp, Tools::Song_WritersBlock;
	std::vector<std::shared_ptr<EzSong> > Tools::SongList_Standard;
	bool Tools::FreeCam;
	bool Tools::DrawBoxes;
	bool Tools::DrawGraphics;
	bool Tools::StepControl;
	int Tools::_PhsxSpeed;
	
	bool Tools::ShowLoadingScreen;
	std::shared_ptr<ILoadingScreen> Tools::CurrentLoadingScreen;

	float Tools::CurVolume;
	
	bool Tools::KillMusicOnLoadingScreen;
	bool Tools::DoNotKillMusicOnNextLoadingscreen;

	int Tools::WriteRecursiveDepth;
	int Tools::WriteObjId;

	int Tools::GUIDraws;
	float Tools::HoldIllumination;

	float Tools::Num_0_to_360;
	float Tools::Num_0_to_2;
	bool Tools::ShowNums;

	bool Tools::DebugConvenience;



	std::wstring StringExtension::Capitalize( const std::wstring &s )
	{
		std::wstringstream wss;
		wss << wchar_t( ::toupper( s[ 0 ] ) );
		wss << s.substr( 1 );
		return wss.str();
	}

	std::wstring Vector2Extension::ToSimpleString( Vector2 v )
	{
		return Format( _T( "%f, %f" ), v.X, v.Y );
	}

	bool Vector2Extension::LE( Vector2 v1, Vector2 v2 )
	{
		if ( v1.X <= v2.X && v1.Y <= v2.Y )
			return true;
		return false;
	}

	bool Vector2Extension::GE( Vector2 v1, Vector2 v2 )
	{
		if ( v1.X >= v2.X && v1.Y >= v2.Y )
			return true;
		return false;
	}

	Tools::RemoveBitsLambda::RemoveBitsLambda()
	{
	}

	bool Tools::RemoveBitsLambda::Apply( const std::wstring &bit )
	{
		return bit == _T( "" ) || bit == _T( " " ) || bit == _T( "\t" );
	}

	void Tools::Assert( bool MustBeTrue )
	{
	#if defined(DEBUG)
		if ( !MustBeTrue )
			Break();
	#endif
	}

	void Tools::Log( const std::wstring &dump )
	{
		// FIXME: Implement log.

		/*std::shared_ptr<System::IO::FileStream> stream = File->Open( _T( "dump" ), FileMode::OpenOrCreate, FileAccess::Write, FileShare::None );
		std::shared_ptr<StreamWriter> writer = std::make_shared<StreamWriter>( stream );
		writer->Write( dump );
		writer->Close();
		stream->Close();*/
	}

	void Tools::Nothing()
	{
	}

	void Tools::Warning()
	{
	}

	void Tools::LevelIsFinished()
	{
		Tools::Write( _T( "Level made!" ) );
		if ( Tools::TheGame->LoadingScreen_Renamed != 0 && !Tools::TheGame->LoadingScreen_Renamed->IsDone )
			Tools::TheGame->LoadingScreen_Renamed->Accelerate = true;
	}

	void Tools::Break()
	{
#if defined(DEBUG)
	std::cout << _T( "!" ) << std::endl;
#endif
	}

	void Tools::Write( const std::shared_ptr<Object> &obj )
	{
#if defined(DEBUG)
	std::cout << obj << std::endl;
#endif
	}

	void Tools::Write( const wchar_t *str, ... )
	{
#if defined(DEBUG)
#if defined(WINDOWS)
		va_list args;
		va_start( args, str );
		vwprintf( str, args );
		va_end( args );
		
		wprintf( L"\n" );

	/*if ( objs->Length == 0 )
		std::cout << str << std::endl;
	else
		std::cout << std::endl;*/
#else
	if ( objs->Length == 0 )
		System::Diagnostics::Debug::WriteLine( str );
	else
		System::Diagnostics::Debug::WriteLine( str, objs );
#endif
#endif
	}

	std::wstring Tools::DefaultObjectDirectory()
	{
		return Path::Combine( Globals::ContentDirectory, _T( "Objects" ) );
	}

	std::wstring Tools::DefaultDynamicDirectory()
	{
		return Path::Combine( Directory::GetCurrentDirectory(), Path::Combine(Globals::ContentDirectory, _T("DynamicLoad")) );
	}

	std::wstring Tools::SourceTextureDirectory()
	{
		return Path::Combine( Path::GetDirectoryName( Path::GetDirectoryName( Path::GetDirectoryName( Directory::GetCurrentDirectory() ) ) ), _T("Content/Art") );
	}

	std::shared_ptr<SimpleObject> Tools::LoadSimpleObject( const std::wstring &file )
	{
		std::shared_ptr<ObjectClass> SourceObject;
		Tools::UseInvariantCulture();
		/*std::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<BinaryReader> reader = std::make_shared<BinaryReader>( stream, Encoding::UTF8 );*/
		std::shared_ptr<BinaryReader> reader = std::make_shared<BinaryReader>( file );
		SourceObject = std::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, EffectWad->FindByName( _T( "BasicEffect" ) ), TextureWad->FindByName( _T( "White" ) ) );
		ObjectClass_PostConstruct( SourceObject, Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, EffectWad->FindByName( _T( "BasicEffect" ) ), TextureWad->FindByName( _T( "White" ) ) );
		SourceObject->ReadFile( reader, EffectWad, TextureWad );
		reader->Close();
		//stream->Close();

		SourceObject->ConvertForSimple();

		return std::make_shared<SimpleObject>( SourceObject );
	}

	const float &Tools::getVolumeFade()
	{
		return _VolumeFade;
	}

	void Tools::setVolumeFade( const float &value )
	{
		_VolumeFade = value;
		UpdateVolume();
	}

	const Version &Tools::getGameVersion()
	{
		return CloudberryKingdomGame::GameVersion;
	}

	void Tools::AddToDo( const std::shared_ptr<Lambda> &todo )
	{
		TheGame->ToDo->Add( todo );
	}

	const std::shared_ptr<Camera> &Tools::getCurCamera()
	{
		if ( CurLevel == 0 )
		{
			if ( DummyCamera == 0 )
				DummyCamera = std::make_shared<Camera>();
			return DummyCamera;
		}
		else
			return CurLevel->getMainCamera();
	}

#if defined(WINDOWS)
	Vector2 Tools::getMousePos()
	{
		return Vector2( static_cast<float>( Mouse.X ), static_cast<float>( Mouse.Y ) ) / Tools::Render->SpriteScaling;
	}
#endif

#if defined(WINDOWS)
	void Tools::setMousePos( const Vector2 &value )
	{
		Mouse::SetPosition( static_cast<int>( value.X * Tools::Render->SpriteScaling ), static_cast<int>( value.Y * Tools::Render->SpriteScaling ) );
	}
#endif

#if defined(WINDOWS)
	bool Tools::getFullscreen()
	{
		return TheGame->MyGraphicsDeviceManager->IsFullScreen;
	}
#endif

#if defined(WINDOWS)
	void Tools::setFullscreen( const bool &value )
	{
		if ( value != getFullscreen() )
		{
			if ( value )
			{
				int width = Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferWidth, height = Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferHeight;

				CloudberryKingdom::IntVector2 safe = ResolutionGroup::SafeResolution( width, height );
				width = safe.X;
				height = safe.Y;

				ResolutionGroup::Use( width, height, false );
			}

			TheGame->MyGraphicsDeviceManager->ToggleFullScreen();

			// Reset the resolution, in case we were trimming the letterbox
			if ( ResolutionGroup::LastSetMode != 0 )
				ResolutionGroup::Use( ResolutionGroup::LastSetMode );
		}
	}
#endif

#if defined(WINDOWS)
	bool Tools::CurMouseDown()
	{
		return Mouse.LeftButton == ButtonState_Pressed;
	}
#endif

#if defined(WINDOWS)
	bool Tools::PrevMouseDown()
	{
		return PrevMouse.LeftButton == ButtonState_Pressed;
	}
#endif

#if defined(WINDOWS)
	bool Tools::MouseReleased()
	{
		return !CurMouseDown() && PrevMouseDown();
	}
#endif

#if defined(WINDOWS)
	bool Tools::MouseNotDown()
	{
		return !CurMouseDown() && !PrevMouseDown();
	}
#endif

#if defined(WINDOWS)
	bool Tools::MouseDown()
	{
		return CurMouseDown() || PrevMouseDown();
	}
#endif

#if defined(WINDOWS)
	bool Tools::MousePressed()
	{
		return CurMouseDown() && !PrevMouseDown();
	}
#endif

#if defined(WINDOWS)
	bool Tools::CurRightMouseDown()
	{
		return Mouse.RightButton == ButtonState_Pressed;
	}
#endif

#if defined(WINDOWS)
	bool Tools::PrevRightMouseDown()
	{
		return PrevMouse.RightButton == ButtonState_Pressed;
	}
#endif

#if defined(WINDOWS)
	bool Tools::RightMouseReleased()
	{
		return !CurRightMouseDown() && PrevRightMouseDown();
	}
#endif

#if defined(WINDOWS)
	Vector2 Tools::MouseGUIPos( Vector2 zoom )
	{
		//return Tools.ToGUICoordinates(new Vector2(Tools.CurMouseState.X, Tools.CurMouseState.Y), Tools.CurLevel.MainCamera, zoom);
		return Tools::ToGUICoordinates( getMousePos(), Tools::CurLevel->getMainCamera(), zoom );
	}
#endif

#if defined(WINDOWS)
	Vector2 Tools::MouseWorldPos()
	{
		return Tools::ToWorldCoordinates( getMousePos(), Tools::CurLevel->getMainCamera() );
	}
#endif

#if defined(WINDOWS)
	bool Tools::ShiftDown()
	{
		return Tools::Keyboard.IsKeyDown( Keys_LeftShift ) || Tools::Keyboard.IsKeyDown( Keys_RightShift );
	}
#endif

#if defined(WINDOWS)
	bool Tools::CntrlDown()
	{
		return Tools::Keyboard.IsKeyDown( Keys_LeftControl ) || Tools::Keyboard.IsKeyDown( Keys_RightControl );
	}
#endif

#if defined(WINDOWS)
	std::wstring Tools::RemoveAfter( const std::wstring &s, const std::wstring &occurence )
	{
		std::wstring cpy( s );
		if ( cpy.find( occurence ) != std::string::npos )
			cpy.erase( s.find( occurence ) );
		return s;
	}
#endif

#if defined(WINDOWS)
	std::wstring Tools::SantitizeOneLineString( std::wstring s, const std::shared_ptr<EzFont> &font )
	{
		s = RemoveAfter( s, _T( "\n" ) );
		s = RemoveAfter( s, _T( "\t" ) );

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		//s = s.Replace( _T( "{" ), _T( " " ) );
		Replace( s, '{', ' ' );
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		//s = s.Replace( _T( "}" ), _T( " " ) );
		Replace( s, '}', ' ' );

		// FIXME: Re-enable this logic.
		/*try
		{
			font->Font->MeasureString( s );
		}
		catch ( ... )
		{
			s = _T( "Invalid" );
		}*/

		return s;
	}
#endif

#if ! defined(WINDOWS)
	std::wstring Tools::SantitizeOneLineString( const std::wstring &s, const std::shared_ptr<EzFont> &font )
	{
		return s;
	}
#endif

	std::wstring Tools::StripPath( const std::wstring &file )
	{
		int LastSlash = file.rfind( _T( "/" ) );
		if ( LastSlash < 0 )
			return file;
		else
			return file.substr( LastSlash + 1 );
	}

	std::wstring Tools::FirstFolder( std::wstring path, const std::wstring &ignore )
	{
		int i = path.find( ignore );
		if ( i >= 0 )
			path = path.substr( i + ignore.length() );

		int FirstSlash = path.find( _T( "/" ) );
		if ( FirstSlash < 0 )
			return path;
		else
			return path.substr( 0, FirstSlash );
	}

	std::shared_ptr<EzTexture> Tools::Texture( const std::wstring &name )
	{
		return TextureWad->FindByName( name );
	}

	std::shared_ptr<EzSound> Tools::Sound( const std::wstring &name )
	{
		return SoundWad->FindByName( name );
	}

	void Tools::Pop()
	{
		Pop( 2 );
	}

	void Tools::Pop( int Pitch )
	{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		std::wstringstream wss;
		wss << _T( "Pop_" );
		wss << CoreMath::RestrictVal( 1, 3, Pitch );
		Sound( wss.str() )->Play();
	}

	const int &Tools::getPhsxSpeed()
	{
		return _PhsxSpeed;
	}

	void Tools::setPhsxSpeed( const int &value )
	{
		_PhsxSpeed = value;
	}

	void Tools::LoadBasicArt( const std::shared_ptr<ContentManager> &Content )
	{
		TextureWad = std::make_shared<EzTextureWad>();
		TextureWad->AddTexture( Content->Load<Texture2D>( _T( "White" ) ), _T( "White" ) );
		TextureWad->AddTexture( Content->Load<Texture2D>( _T( "Circle" ) ), _T( "Circle" ) );
		TextureWad->AddTexture( Content->Load<Texture2D>( _T( "Smooth" ) ), _T( "Smooth" ) );

		TextureWad->DefaultTexture = TextureWad->TextureList[ 0 ];
	}

	std::wstring Tools::GetFileName( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( _T( "/" ) );
		int j = FilePath.find( _T( "." ), i );
		if ( j < 0 )
			j = FilePath.length();
		if ( i < 0 )
			return FilePath.substr( 0, j - 1 );
		else
			return FilePath.substr( i + 1, j - 1 - i );
	}

	std::wstring Tools::GetFileNamePlusExtension( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( _T( "/" ) );
		int n = FilePath.length();
		if ( i < 0 )
			return FilePath.substr( 0, n - 1 );
		else
			return FilePath.substr( i + 1, n - 1 - i );
	}

	std::wstring Tools::GetFileBigName( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( _T( "/" ) );
		if ( i < 0 )
			return FilePath;

		std::wstring Path = FilePath.substr( 0, i );
		i = Path.rfind( _T( "/" ) );

		if ( i < 0 )
			return FilePath;
		else
			return FilePath.substr( i + 1 );
	}

	std::wstring Tools::GetFileName( const std::wstring &path, const std::wstring &FilePath )
	{
		int i = FilePath.find( path ) + path.length() + 1;
		if ( i < 0 )
			return _T( "ERROR" );
		int j = FilePath.find( _T( "." ), i );
		if ( j <= i )
			return _T( "ERROR" );

		return FilePath.substr( i, j - i );
	}

	std::wstring Tools::GetFileExt( const std::wstring &path, const std::wstring &FilePath )
	{
		int j = FilePath.find( _T( "." ) );
		if ( j < 0 )
			return _T( "ERROR" );

		return FilePath.substr( j + 1 );
	}

	std::vector<std::wstring> Tools::GetFiles( const std::wstring &path, bool IncludeSubdirectories )
	{
		std::vector<std::wstring> files = std::vector<std::wstring>();
		//files.AddRange( Directory::GetFiles( path ) );
		AddRange( files, Directory::GetFiles( path ) );

		if ( IncludeSubdirectories )
		{
			std::vector<std::wstring> dir = Directory::GetDirectories( path );
			for ( int i = 0; i < static_cast<int>( dir.size() ); i++ )
			{
				AddRange( files, GetFiles( dir[ i ], IncludeSubdirectories ) );
				//files.AddRange( GetFiles( dir[ i ], IncludeSubdirectories ) );
			}
		}

		return files;
	}

	void Tools::LoadEffects( const std::shared_ptr<ContentManager> &Content, bool CreateNewWad )
	{
		if ( CreateNewWad )
			EffectWad = std::make_shared<EzEffectWad>();

		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/BasicEffect" ) ), _T( "Basic" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/NoTexture" ) ), _T( "NoTexture" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/Circle" ) ), _T( "Circle" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/Shell" ) ), _T( "Shell" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/FireballEffect" ) ), _T( "Fireball" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/Paint" ) ), _T( "Paint" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/Lava" ) ), _T( "Lava" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/LightMap" ) ), _T( "LightMap" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/LightSource" ) ), _T( "LightSource" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/BwEffect" ) ), _T( "BW" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/Hsl_Green" ) ), _T( "Hsl_Green" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/Hsl" ) ), _T( "Hsl" ) );
		EffectWad->AddEffect( Content->Load<Effect>( _T( "Shaders/Window" ) ), _T( "Window" ) );

		BasicEffect = EffectWad->EffectList[ 0 ];
		NoTexture = EffectWad->EffectList[ 1 ];
		CircleEffect = EffectWad->EffectList[ 2 ];
		LightSourceEffect = EffectWad->FindByName( _T( "LightSource" ) );
		HslEffect = EffectWad->FindByName( _T( "Hsl" ) );
		HslGreenEffect = EffectWad->FindByName( _T( "Hsl_Green" ) );
		WindowEffect = EffectWad->FindByName( _T( "Window" ) );

		PaintEffect_SpriteBatch = Content->Load<Effect>( _T( "Shaders/Paint_SpriteBatch" ) );
	}

	float Tools::BoxSize( Vector2 TR, Vector2 BL )
	{
		return ( TR.X - BL.X ) * ( TR.Y - BL.Y );
	}

	void Tools::UpdateVolume()
	{
		float NewVolume = Tools::MusicVolume->getVal() * Tools::getVolumeFade() * Tools::CurSongVolume;
		if ( Tools::SongWad != 0 && Tools::SongWad->Paused )
			NewVolume = 0;
		if ( NewVolume != CurVolume )
		{
			MediaPlayer::Volume = NewVolume;
			CurVolume = MediaPlayer::Volume;
		}
	}

	void Tools::BeginLoadingScreen( bool KillMusic )
	{
		if ( KillMusic && Tools::SongWad != 0 && KillMusicOnLoadingScreen && !DoNotKillMusicOnNextLoadingscreen )
			Tools::SongWad->FadeOut();
		DoNotKillMusicOnNextLoadingscreen = false;

		Tools::ShowLoadingScreen = true;

		CurrentLoadingScreen = std::make_shared<LoadingScreen>();

		CurrentLoadingScreen->Start();
	}

	void Tools::PlayHappyMusic()
	{
		Tools::SongWad->SuppressNextInfoDisplay = true;
		Tools::SongWad->SetPlayList( Tools::Song_Heavens );
		Tools::SongWad->Start( true );
	}

	void Tools::EndLoadingScreen()
	{
		Tools::CurrentLoadingScreen->End();
	}

	void Tools::EndLoadingScreen_Immediate()
	{
		Tools::ShowLoadingScreen = false;
	}

	std::vector<std::wstring> Tools::GetBitsFromLine( std::wstring line )
	{
		line = Tools::RemoveComment_SlashStyle( line );

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		//std::shared_ptr<std::vector<void*> > bits = line.Split( L' ', L'\t' )->ToList();
		
		// FIXME: Fix this monstrosity.
		std::vector<std::wstring> temp_bits = Split( line, L' ' );
		std::vector<std::wstring> bits;
		for( std::vector<std::wstring>::iterator i = temp_bits.begin(); i != temp_bits.end(); ++i )
		{
			std::vector<std::wstring> more_bits = Split( *i, L'\t' );
			AddRange( bits, more_bits );
		}

		Tools::RemoveAll( bits, std::static_pointer_cast<LambdaFunc_1<std::wstring, bool> >( std::make_shared<RemoveBitsLambda>() ) );

		return bits;
	}

	std::vector<std::wstring> Tools::GetBitsFromReader( const std::shared_ptr<StreamReader> &reader )
	{
		return GetBitsFromLine( reader->ReadLine() );
	}

	/*std::shared_ptr<Object> Tools::ReadFields( const std::shared_ptr<Object> &obj, const std::shared_ptr<StreamReader> &reader )
	{
		std::shared_ptr<std::wstring> line = reader->ReadLine();
		while ( line != 0 )
		{
			std::vector<std::wstring> bits = Tools::GetBitsFromLine( line );

			if ( bits.size() > 0 )
			{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				var first = bits[ 0 ];

				bool WasReadable = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				var info = obj->GetType()->GetField(first);
				//try
				if ( info != 0 )
				{
					info = obj->GetType()->GetField(first);
					if ( info->FieldType->GetInterfaces()->Contains(IReadWrite::typeid) )
					{
						WasReadable = true;
						std::shared_ptr<IReadWrite> rw = std::static_pointer_cast<IReadWrite>( info->GetValue( obj ) );
						rw->Read( reader );
						info->SetValue( obj, rw );
					}
					else
					// List of IReadWrites
					{
						std::shared_ptr<Type> type = info->FieldType;
						if ( type->IsGenericType && type->GetGenericTypeDefinition() == std::vector<*>::typeid )
						{
							WasReadable = true;

							std::shared_ptr<System::Collections::IList> list = std::dynamic_pointer_cast<System::Collections::IList>( info->GetValue( obj ) );

							std::shared_ptr<Type> itemType = type->GetGenericArguments()[ 0 ];
							if ( itemType->GetInterfaces()->Contains(IReadWrite::typeid) )
								ReadList( reader, list, itemType );
						}
					}
				}
				//catch
				else
				{
					WasReadable = false;
				}

				if ( !WasReadable )
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//					switch (first)
//ORIGINAL LINE: case "End":
					if ( first == _T( "End" ) )
					{
							return obj;

					}
//ORIGINAL LINE: case "_MyTexture":
					else if ( first == _T( "_MyTexture" ) )
					{
							Tools::ReadLineToObj( obj, bits );

					}
					else
					{
							Tools::ReadLineToObj( obj, bits );
					}
			}

			line = reader->ReadLine();
		}

		return obj;
	}*/

	/*void Tools::ReadList( const std::shared_ptr<StreamReader> &reader, const std::shared_ptr<System::Collections::IList> &list, const std::shared_ptr<Type> &itemType )
	{
		std::shared_ptr<std::wstring> line = reader->ReadLine();
		bool ReadingList = true;

		while ( line != 0 && ReadingList )
		{
			line = reader->ReadLine();
			std::vector<std::wstring> bits = Tools::GetBitsFromLine( line );

//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//			switch (bits[0])
//ORIGINAL LINE: case "Add":
			if ( bits[ 0 ] == _T( "Add" ) )
			{
					std::shared_ptr<ConstructorInfo> constructor;
					if ( bits.size() > 1 )
					{
						//var type = Type.GetType("CloudberryKingdom." + bits[1]);
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
						var type = Type_GET_TYPE( bits[ 1 ] );
						constructor = type->GetConstructor( Type_EMPTY_TYPES );
					}
					else
						constructor = itemType->GetConstructor( Type_EMPTY_TYPES );

					std::shared_ptr<Object> newobj = constructor->Invoke( Type_EMPTY_TYPES );
					//ReadFields(newobj, reader);
					if ( std::dynamic_pointer_cast<IReadWrite>( newobj ) != 0 )
						( std::static_pointer_cast<IReadWrite>( newobj ) )->Read( reader );
					else
						ReadFields( newobj, reader );
					list->Add( newobj );

			}
//ORIGINAL LINE: case "EndList":
			else if ( bits[ 0 ] == _T( "EndList" ) )
			{
					ReadingList = false;
			}
//ORIGINAL LINE: case "End":
			else if ( bits[ 0 ] == _T( "End" ) )
			{
			}
			else
			{
			}
		}
	}*/

	/*void Tools::WriteFields( const std::shared_ptr<Object> &obj, const std::shared_ptr<StreamWriter> &writer, ... )
	{
		WriteRecursiveDepth++;
		std::wstring WhiteSpace = _T( "" );
		for ( int i = 1; i < WriteRecursiveDepth; i++ )
			WhiteSpace += _T( "  " );

		for ( unknown::const_iterator info = obj->GetType()->GetFields().begin(); info != obj->GetType()->GetFields().end(); ++info )
		{
			// Check if field is listed as a variable to be written.
			if ( VariableNames->Contains( ( *info )->Name ) )
			{
				std::wstring line = _T( "" );
				// int
				if ( ( *info )->FieldType == int::typeid )
					line = StringConverterHelper::toString( static_cast<int>( ( *info )->GetValue( obj ) ) );
				// float
				else if ( ( *info )->FieldType == float::typeid )
					line = StringConverterHelper::toString( static_cast<float>( ( *info )->GetValue( obj ) ) );
				// Vector2
				else if ( ( *info )->FieldType == Vector2::typeid )
				{
					Vector2 v = static_cast<Vector2>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0} {1}" ), v.X, v.Y );
				}
				// Vector3
				else if ( ( *info )->FieldType == Vector3::typeid )
				{
					Vector3 v = static_cast<Vector3>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0} {1} {2}" ), v.X, v.Y, v.Z );
				}
				// Vector4
				else if ( ( *info )->FieldType == Vector4::typeid )
				{
					Vector4 v = static_cast<Vector4>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0} {1} {2} {3}" ), v.X, v.Y, v.Z, v.W );
				}
				// Color
				else if ( ( *info )->FieldType == Color::typeid )
				{
					Color c = static_cast<Color>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0} {1} {2} {3}" ), c.R, c.G, c.B, c.A );
				}
				// bool
				else if ( ( *info )->FieldType == bool::typeid )
				{
					bool b = static_cast<bool>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0}" ), b );
				}
				// string
				else if ( ( *info )->FieldType == std::wstring::typeid )
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					line = ( static_cast<std::wstring>( ( *info )->GetValue( obj ) ) )->ToString();
				// EzTexture
				else if ( ( *info )->FieldType == EzTexture::typeid )
				{
					std::shared_ptr<EzTexture> texture = std::static_pointer_cast<EzTexture>( ( *info )->GetValue( obj ) );
					if ( texture == 0 )
						continue;
					else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						line = texture->Name->ToString();
				}
				// EzEffect
				else if ( ( *info )->FieldType == EzEffect::typeid )
				{
					std::shared_ptr<EzEffect> effect = std::static_pointer_cast<EzEffect>( ( *info )->GetValue( obj ) );
					if ( effect == 0 )
						continue;
					else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						line = effect->Name->ToString();
				}
				// PhsxData
				else if ( ( *info )->FieldType == PhsxData::typeid )
				{
					PhsxData d = static_cast<PhsxData>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0} {1} {2} {3} {4} {5}" ), d.Position.X, d.Position.Y, d.Velocity.X, d.Velocity.Y, d.Acceleration.X, d.Acceleration.Y );
				}
				// BasePoint
				else if ( ( *info )->FieldType == BasePoint::typeid )
				{
					BasePoint b = static_cast<BasePoint>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0} {1} {2} {3} {4} {5}" ), b.e1.X, b.e1.Y, b.e2.X, b.e2.Y, b.Origin.X, b.Origin.Y );
				}
				// MyOwnVertexFormat
				else if ( ( *info )->FieldType == MyOwnVertexFormat::typeid )
				{
					MyOwnVertexFormat v = static_cast<MyOwnVertexFormat>( ( *info )->GetValue( obj ) );
					line = Format( _T( "{0} {1} {2} {3} {4} {5} {6} {7}" ), v.xy.X, v.xy.Y, v.uv.X, v.uv.Y, v.TheColor.R, v.TheColor.G, v.TheColor.B, v.TheColor.A );
				}
				else if ( ( *info )->FieldType->GetInterfaces()->Contains(IReadWrite::typeid) )
				{
					std::shared_ptr<IReadWrite> rw = std::static_pointer_cast<IReadWrite>( ( *info )->GetValue( obj ) );
					writer->WriteLine( WhiteSpace + ( *info )->Name );
					rw->Write( writer );
					writer->WriteLine( WhiteSpace + _T( "End" ) );
					writer->WriteLine();
				}
				else
				{
					// List of IReadWrites
					std::shared_ptr<Type> type = ( *info )->FieldType;
					if ( type->IsGenericType && type->GetGenericTypeDefinition() == std::vector<*>::typeid )
					{
						std::shared_ptr<Type> itemType = type->GetGenericArguments()[ 0 ];
						if ( itemType->GetInterfaces()->Contains(IReadWrite::typeid) )
						{
							writer->WriteLine( WhiteSpace + ( *info )->Name );
							writer->WriteLine( WhiteSpace + _T( "StartList" ) );
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
							for ( IEnumerable<IReadWrite*>::const_iterator rw = static_cast<IEnumerable<IReadWrite*>*>( info->GetValue( obj ).begin() ); rw != static_cast<IEnumerable<IReadWrite*>*>(info->GetValue(obj).end()); ++rw )
							{
								writer->WriteLine( WhiteSpace + _T( "Add " ) + ( *rw )->GetType()->Namespace + _T(".") + (*rw)->GetType()->Name );
								( *rw )->Write( writer );
								writer->WriteLine( WhiteSpace + _T( "End" ) );
							}
							writer->WriteLine( WhiteSpace + _T( "EndList" ) );
							writer->WriteLine();
						}
					}
				}

				if ( line != _T( "" ) )
					writer->WriteLine( WhiteSpace + Format( _T( "{0} {1}" ), ( *info )->Name, line ) );
			}
		}

		WriteRecursiveDepth--;
	}*/

	/*std::map<std::wstring, int> Tools::GetLocations( std::vector<std::wstring> &Bits, ... )
	{
		std::map<std::wstring, int> dict;
		for ( int i = 0; i < static_cast<int>( Bits.size() ); i++ )
			if ( keywords->Contains( Bits[ i ] ) )
				dict->Add( Bits[ i ], i );
		return dict;
	}*/

	std::map<std::wstring, int> Tools::GetLocations( std::vector<std::wstring> &Bits, std::vector<std::wstring> &keywords )
	{
		std::map<std::wstring, int> dict;
		for ( int i = 0; i < static_cast<int>( Bits.size() ); i++ )
			if ( std::find( keywords.begin(), keywords.end(), Bits[ i ] ) != keywords.end() )
				dict[ Bits[ i ] ] = i;
		return dict;
	}

	bool Tools::BitsHasBit( std::vector<std::wstring> &Bits, const std::wstring &Bit )
	{
		if ( std::find( Bits.begin(), Bits.end(), Bit ) != Bits.end() )
			return true;
		else
			return false;
	}

	std::wstring Tools::RemoveComment_SlashStyle( const std::wstring &str )
	{
		std::wstring ws;
		int CommentIndex = str.find( _T( "//" ) );
		if ( CommentIndex >= 0 )
			ws = str.substr( 0, CommentIndex );
		return ws;
	}

	std::wstring Tools::RemoveComment_DashStyle( const std::wstring &str )
	{
		std::wstring ws;
		int CommentIndex = str.find( _T( "--" ) );
		if ( CommentIndex >= 0 )
			ws = str.substr( 0, CommentIndex );
		return ws;
	}

	Vector2 Tools::ParseToVector2( const std::wstring &bit1, const std::wstring &bit2 )
	{
		Vector2 Vec = Vector2();

		Vec.X = ParseFloat( bit1 );
		Vec.Y = ParseFloat( bit2 );

		return Vec;
	}

	Vector4 Tools::ParseToVector4( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4 )
	{
		Vector4 Vec = Vector4();

		Vec.X = ParseFloat( bit1 );
		Vec.Y = ParseFloat( bit2 );
		Vec.Z = ParseFloat( bit3 );
		Vec.W = ParseFloat( bit4 );

		return Vec;
	}

	PhsxData Tools::ParseToPhsxData( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 )
	{
		PhsxData data = PhsxData();

		data.Position.X = ParseFloat( bit1 );
		data.Position.Y = ParseFloat( bit2 );
		data.Velocity.X = ParseFloat( bit3 );
		data.Velocity.Y = ParseFloat( bit4 );
		data.Acceleration.X = ParseFloat( bit5 );
		data.Acceleration.Y = ParseFloat( bit6 );

		return data;
	}

	BasePoint Tools::ParseToBasePoint( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 )
	{
		BasePoint b = BasePoint();

		b.e1.X = ParseFloat( bit1 );
		b.e1.Y = ParseFloat( bit2 );
		b.e2.X = ParseFloat( bit3 );
		b.e2.Y = ParseFloat( bit4 );
		b.Origin.X = ParseFloat( bit5 );
		b.Origin.Y = ParseFloat( bit6 );

		return b;
	}

	MyOwnVertexFormat Tools::ParseToMyOwnVertexFormat( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6, const std::wstring &bit7, const std::wstring &bit8 )
	{
		MyOwnVertexFormat b = MyOwnVertexFormat();

		b.xy.X = ParseFloat( bit1 );
		b.xy.Y = ParseFloat( bit2 );

		b.uv.X = ParseFloat( bit3 );
		b.uv.Y = ParseFloat( bit4 );

		b.TheColor.R = Parse<unsigned char>( bit5 );
		b.TheColor.G = Parse<unsigned char>( bit6 );
		b.TheColor.B = Parse<unsigned char>( bit7 );
		b.TheColor.A = Parse<unsigned char>( bit8 );

		return b;
	}

	Vector2 Tools::ParseToVector2( const std::wstring &str )
	{
		int CommaIndex = str.find( _T( "," ) );
		Vector2 Vec = Vector2();

		std::wstring Component1, Component2;
		Component1 = str.substr( 0, CommaIndex );
		Component2 = str.substr( CommaIndex + 1, str.length() - CommaIndex - 1 );
		Vec.X = ParseFloat( Component1 );
		Vec.Y = ParseFloat( Component2 );

		return Vec;
	}

	Color Tools::ParseToColor( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4 )
	{
		Color c = Color::White;

		c.R = Parse<unsigned char>( bit1 );
		c.G = Parse<unsigned char>( bit2 );
		c.B = Parse<unsigned char>( bit3 );
		c.A = Parse<unsigned char>( bit4 );

		return c;
	}

	Color Tools::ParseToColor( const std::wstring &str )
	{
		int CommaIndex = str.find( _T( "," ) );
		int CommaIndex2 = str.find( _T( "," ), CommaIndex + 1 );
		int CommaIndex3 = str.find( _T( "," ), CommaIndex2 + 1 );

		std::wstring Component1, Component2, Component3, Component4;
		Component1 = str.substr( 0, CommaIndex );
		Component2 = str.substr( CommaIndex + 1, CommaIndex2 - CommaIndex - 1 );
		Component3 = str.substr( CommaIndex2 + 1, CommaIndex3 - CommaIndex2 - 1 );
		Component4 = str.substr( CommaIndex3 + 1, str.length() - CommaIndex3 - 1 );

		Color clr = Color( Parse<unsigned char>( Component1 ), Parse<unsigned char>( Component2 ), Parse<unsigned char>( Component3 ), Parse<unsigned char>( Component4 ) );

		return clr;
	}

	std::shared_ptr<EzSound> Tools::ParseToEzSound( const std::wstring &str )
	{
		int LineIndex = str.find( _T( "|" ) );

		std::wstring Component1, Component2;
		Component1 = str.substr( 0, LineIndex );
		Component2 = str.substr( LineIndex + 1, str.length() - LineIndex - 1 );

		return NewSound( ParseToFileName( Component1 ), ParseFloat( Component2 ) );
	}

	std::shared_ptr<EzSound> Tools::NewSound( const std::wstring &name, float volume )
	{
		std::shared_ptr<EzSound> snd = std::make_shared<EzSound>();
		snd->sound = Tools::SoundWad->FindByName( name )->sound;
		snd->DefaultVolume = volume;
		snd->MaxInstances = 4;

		Tools::PrivateSoundWad->SoundList.push_back( snd );

		return snd;
	}

	std::wstring Tools::ParseToFileName( const std::wstring &str )
	{
		int Quote1 = str.find( _T( "\"" ) );
		int Quote2 = str.find( _T( "\"" ), Quote1 + 1 );

		std::wstring Name = str.substr( Quote1 + 1, Quote2 - Quote1 - 1 );
		return Name;
	}

/*template<typename T>
	int Tools::Length()
	{
		return GetValues<T>()->Count();
	}*/

/*template<typename T>
	std::shared_ptr<IEnumerable<T> > Tools::GetValues()
	{
		return ( from x in T::typeid::GetFields( BindingFlags::Static | BindingFlags::Public ) select ( T )x::GetValue( 0 ) );
	}*/

	unsigned char Tools::FloatToByte( float x )
	{
		if ( x <= 0 )
			return static_cast<unsigned char>( 0 );
		if ( x >= 1 )
			return static_cast<unsigned char>( 255 );
		return static_cast<unsigned char>( 255 * x );
	}

	void Tools::IncrPhsxSpeed()
	{
		Tools::setPhsxSpeed( Tools::getPhsxSpeed() + 1 );
		if ( Tools::getPhsxSpeed() > 3 )
			Tools::setPhsxSpeed( 0 );
	}

	void Tools::MoveTo( const std::shared_ptr<ObjectBase> &obj, Vector2 pos )
	{
		obj->Move( pos - obj->getCore()->Data.Position );
	}

	Vector2 Tools::ToScreenCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 ZoomMod )
	{
		Vector2 loc = Vector2();
		loc.X = ( pos.X - cam->Data.Position.X ) / cam->AspectRatio * cam->getZoom().X * ZoomMod.X;
		loc.Y = ( pos.Y - cam->Data.Position.Y ) * cam->getZoom().Y * ZoomMod.Y;

		loc.X *= cam->ScreenWidth / 2;
		loc.Y *= -cam->ScreenHeight / 2;

		loc.X += cam->ScreenWidth / 2;
		loc.Y += cam->ScreenHeight / 2;

		return loc;
	}

	Vector2 Tools::ToGUICoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam )
	{
		return ToWorldCoordinates( pos, cam, Vector2( .001f,.001f ) );
	}

	Vector2 Tools::ToGUICoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 zoom )
	{
		return ToWorldCoordinates( pos, cam, zoom );
	}

	Vector2 Tools::ToWorldCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam )
	{
		return ToWorldCoordinates( pos, cam, cam->getZoom() );
	}

	Vector2 Tools::ToWorldCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 zoom )
	{
		pos.X -= cam->ScreenWidth / 2;
		pos.Y -= cam->ScreenHeight / 2;

		pos.X /= cam->ScreenWidth / 2;
		pos.Y /= -cam->ScreenHeight / 2;

		pos.X = pos.X * cam->AspectRatio / zoom.X + cam->Data.Position.X;
		pos.Y = pos.Y / zoom.Y + cam->Data.Position.Y;

		return pos;
	}

	void Tools::StartGUIDraw()
	{
		GUIDraws++;
		if ( GUIDraws > 1 )
			return;

		// Start the GUI drawing if this is the first call to GUIDraw
		Tools::CurLevel->getMainCamera()->SetToDefaultZoom();

		// Save global illumination level
		HoldIllumination = Tools::QDrawer->getGlobalIllumination();
		Tools::QDrawer->setGlobalIllumination( 1 );
	}

	void Tools::EndGUIDraw()
	{
		GUIDraws--;
		if ( GUIDraws > 0 )
			return;

		// End the GUI drawing if this is the last call to GUIDraw
		Tools::CurLevel->getMainCamera()->RevertZoom();

		// Restor global illumination level
		Tools::QDrawer->setGlobalIllumination( HoldIllumination );
	}

	void Tools::StartSpriteBatch()
	{
		StartSpriteBatch( false );
	}

	void Tools::StartSpriteBatch( bool AsPaint )
	{
		if ( !Tools::Render->UsingSpriteBatch )
		{
			Tools::QDrawer->Flush();
			//Tools.spriteBatch.Begin(SpriteSortMode.Immediate, BlendState.AlphaBlend);
			//float scale = 1440f / 1280f;
			//float scale = 800f / 1280f;
			float scale = Tools::Render->SpriteScaling;

			if ( AsPaint )
			{
				PaintEffect_SpriteBatch->Parameters( "xTexture" )->SetValue( Tools::TextureWad->FindByName( _T( "PaintSplotch" ) )->getTex() );
				//PaintEffect_SpriteBatch.Parameters["SceneTexture"].SetValue(Tools.TextureWad.FindByName("PaintSplotch").Tex); 
				Tools::Render->MySpriteBatch->Begin( SpriteSortMode_Immediate, GfxBlendState_AlphaBlend, GfxSamplerState_LinearClamp, GfxDepthStencilState_None, GfxRasterizerState_CullCounterClockwise, Tools::PaintEffect_SpriteBatch, Matrix::CreateScale( scale, scale, 1 ) );
			}
			else
				Tools::Render->MySpriteBatch->Begin( SpriteSortMode_Immediate, GfxBlendState_AlphaBlend, GfxSamplerState_LinearClamp, GfxDepthStencilState_None, GfxRasterizerState_CullCounterClockwise, 0, Matrix::CreateScale( scale, scale, 1 ) );

			Tools::Render->UsingSpriteBatch = true;
		}
	}

	void Tools::DrawText( Vector2 pos, const std::shared_ptr<Camera> &cam, const std::wstring &str, const std::shared_ptr<SpriteFont> &font )
	{
		Vector2 loc = ToScreenCoordinates( pos, cam, Vector2(1) );

		Tools::Render->MySpriteBatch->DrawString( font, str, loc, Color::Azure, 0, Vector2(), Vector2( .5f,.5f ), SpriteEffects_None, 0 );
	}

	void Tools::SetDefaultEffectParams( float AspectRatio )
	{
		for ( std::vector<std::shared_ptr<EzEffect> >::const_iterator fx = EffectWad->EffectList.begin(); fx != EffectWad->EffectList.end(); ++fx )
		{
			( *fx )->xCameraAspect->SetValue( AspectRatio );
			( *fx )->effect->CurrentTechnique = ( *fx )->Simplest;
			( *fx )->t->SetValue( Tools::t );
			( *fx )->Illumination->SetValue( 1.f );
			( *fx )->FlipVector->SetValue( Vector2( -1, -1 ) );
		}

		Matrix colorm;

	colorm = ColorHelper::LinearColorTransform( 0 ); // Green
	//colorm = HsvTransform(1.3f, 1.2f, 100); // Gold
	//colorm = HsvTransform(1.5f, 1.5f, 100); // Gold 2
	//colorm = HsvTransform(1.3f, 1.2f, 200); // Hot pink
	//colorm = HsvTransform(1.3f, 1.2f, 250); // ?
	//colorm = HsvTransform(.5f, 0f, 0); // Black
	//colorm = HsvTransform(.15f, 0f, 0); // Dark Black
	//colorm = HsvTransform(.75f, 0f, 0); // Gray
	//colorm = HsvTransform(.8f, 1.3f, 225); // Purple
	//colorm = HsvTransform(.9f, 1.3f, 110); // Orange
	//colorm = LinearColorTransform(45); // Teal
	//colorm = LinearColorTransform(120); // Blue
	//colorm = HsvTransform(.95f, 1.3f, 0) * LinearColorTransform(240); // Red
	//colorm = HsvTransform(1.25f, 1.3f, 0) * LinearColorTransform(305); // Yellow

		HslGreenEffect->effect->Parameters( "ColorMatrix" )->SetValue( colorm );
		HslEffect->effect->Parameters( "ColorMatrix" )->SetValue( colorm );

		//colorm = HsvTransform(1f, 1f, 30) * 
		//        new Matrix(.6f, .6f, .6f, 0,
		//                    0, 0, 0, 0,
		//                    0, 0, 0, 0,
		//                    0, 0, 0, 1);
		//colorm = HsvTransform(.7f, 1f, 160);
		//colorm = HsvTransform(Num_0_to_2, 1f, Num_0_to_360);
		//colorm = HsvTransform(1f, 1f, 200);
	}

	void Tools::ModNums()
	{
	#if defined(WINDOWS)
		if ( ButtonCheck::State( Keys_D1 ).Down )
			Num_0_to_360 = CoreMath::RestrictVal( 0.f, 360.f, Num_0_to_360 + .1f * Tools::DeltaMouse.X );
		if ( ButtonCheck::State( Keys_D2 ).Down )
			Num_0_to_2 = CoreMath::RestrictVal( 0.f, 2.f, Num_0_to_2 + .001f * Tools::DeltaMouse.X );

		if ( ButtonCheck::State( Keys_D1 ).Down || ButtonCheck::State( Keys_D2 ).Down )
			ShowNums = true;
	#endif
	}

	void Tools::SetVibration( PlayerIndex Index, float LeftMotor, float RightMotor, int Duration )
	{
		if ( DebugConvenience )
			return;

		VibrateTimes[ static_cast<int>( Index ) ] = Duration;
		GamePad::SetVibration( Index, LeftMotor, RightMotor );
	}

	void Tools::UpdateVibrations()
	{
		for ( int i = 0; i < 4; i++ )
		{
			if ( VibrateTimes[ i ] > 0 )
			{
				VibrateTimes[ i ]--;
				if ( VibrateTimes[ i ] <= 0 )
					SetVibration( static_cast<PlayerIndex>( i ), 0, 0, 0 );
			}
		}
	}

	std::vector<Vector2> Tools::FloatArrayToVectorArray_y( std::vector<float> v )
	{
		std::vector<Vector2> vec = std::vector<Vector2>( v.size() );
		for ( int i = 0; i < static_cast<int>( v.size() ); i++ )
			vec[ i ] = Vector2( 0, v[ i ] );
		return vec;
	}

	bool Tools::IncrementsContainsSum( std::vector<int> Incr, int S )
	{
		int Sum = 0;
		for ( int i = 0; i < static_cast<int>( Incr.size() ); i++ )
		{
			Sum += Incr[ i ];
			if ( Sum == S )
				return true;
		}

		return false;
	}

	void Tools::UseInvariantCulture()
	{
		// FIXME: Find all references of this function and make sure we port the desired behavior.
		//Thread::CurrentThread->CurrentCulture = System::Globalization::CultureInfo::InvariantCulture;
	}

	bool Tools::_AllTaken( std::vector<bool> list1, std::vector<bool> list2, int Length )
	{
		for ( int i = 0; i < Length; i++ )
			if ( !list1[ i ] && list2[ i ] )
				return false;
		return true;
	}

	std::wstring Tools::ScoreString( int num, int outof )
	{
		return StringConverterHelper::toString( num ) + _T( "/" ) + StringConverterHelper::toString( outof );
		//return "x" + num.ToString() + "/" + outof.ToString();
	}

	std::wstring Tools::ScoreString( int num )
	{
		return StringConverterHelper::toString( num );
		//return "x" + num.ToString();
	}

	void Tools::EnsureBounds_X( const std::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL )
	{
		float TR_Bound = obj->TR_Bound().X;
		if ( TR_Bound > TR.X )
			obj->MoveToBounded( Vector2( TR.X - TR_Bound, 0 ) );
		else
		{
			float BL_Bound = obj->BL_Bound().X;
			if ( BL_Bound < BL.X )
				obj->MoveToBounded( Vector2( BL.X - BL_Bound, 0 ) );
		}
	}

	void Tools::EnsureBounds_Y( const std::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL )
	{
		float TR_Bound = obj->TR_Bound().Y;
		if ( TR_Bound > TR.Y )
			obj->MoveToBounded( Vector2( 0, TR.Y - TR_Bound ) );
		else
		{
			float BL_Bound = obj->BL_Bound().Y;
			if ( BL_Bound < BL.Y )
				obj->MoveToBounded( Vector2( 0, BL.Y - BL_Bound ) );
		}
	}

	void Tools::EnsureBounds( const std::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL )
	{
		Vector2 TR_Bound = obj->TR_Bound();
		Vector2 BL_Bound = obj->BL_Bound();

		if ( TR_Bound.X > TR.X )
			obj->MoveToBounded( Vector2( TR.X - TR_Bound.X, 0 ) );
		else if ( BL_Bound.X < BL.X )
			obj->MoveToBounded( Vector2( BL.X - BL_Bound.X, 0 ) );

		if ( TR_Bound.Y > TR.Y )
			obj->MoveToBounded( Vector2( 0, TR.Y - TR_Bound.Y ) );
		else if ( BL_Bound.Y < BL.Y )
			obj->MoveToBounded( Vector2( 0, BL.Y - BL_Bound.Y ) );
	}
}
