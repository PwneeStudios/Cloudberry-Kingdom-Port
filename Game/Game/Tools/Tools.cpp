#include <global_header.h>

#include "Hacks/List.h"
#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include "Hacks/NET/Path.h"
#include "Hacks/NET/Directory.h"
#include <Input/GamePad.h>
#include <Audio/MediaPlayer.h>
#include <Input/Mouse.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <MasterHack.h>
#include <Utility/Log.h>

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

		std::wstring tempVector2[] = { std::wstring( L"A" ), std::wstring( L"B" ), std::wstring( L"X" ), std::wstring( L"Y" ), std::wstring( L"RS" ), std::wstring( L"LS" ), std::wstring( L"RT" ), std::wstring( L"LT" ), std::wstring( L"RJ" ), std::wstring( L"RJ" ), std::wstring( L"LJ" ), std::wstring( L"LJ" ), std::wstring( L"DPad" ), std::wstring( L"Start" ) };
		Tools::ButtonNames = VecFromArray( tempVector2 );
		std::wstring tempVector3[] = { std::wstring( L"right" ), std::wstring( L"up" ), std::wstring( L"left" ), std::wstring( L"down" ) };
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
		Tools::GlobalRnd = boost::make_shared<Rand>( 0 );
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
		Tools::SongList_Standard = std::vector<boost::shared_ptr<EzSong> >();
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
	boost::shared_ptr<AftermathData> Tools::CurrentAftermath;
	bool Tools::IsMasochistic;
	bool Tools::AutoLoop;
	int Tools::AutoLoopDelay;
	float Tools::_VolumeFade;

	float Tools::CurSongVolume;
	boost::shared_ptr<WrappedFloat> Tools::SoundVolume, Tools::MusicVolume;
	bool Tools::FixedTimeStep;
	bool Tools::WindowBorder;
	boost::shared_ptr<XnaGameClass> Tools::GameClass;
	boost::shared_ptr<CloudberryKingdomGame> Tools::TheGame;

	std::vector<std::wstring> Tools::ButtonNames;
	std::vector<std::wstring> Tools::DirNames;
	boost::shared_ptr<GameFactory> Tools::CurGameType;
	boost::shared_ptr<GameData> Tools::CurGameData;
	boost::shared_ptr<Level> Tools::CurLevel;
	boost::shared_ptr<Camera> Tools::DummyCamera;

	boost::shared_ptr<GameData> Tools::WorldMap, Tools::TitleGame;
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

	boost::shared_ptr<GameTime> Tools::gameTime;
	boost::shared_ptr<Rand> Tools::GlobalRnd;
	boost::shared_ptr<EzEffectWad> Tools::EffectWad;
	boost::shared_ptr<EzEffect> Tools::BasicEffect, Tools::NoTexture, Tools::CircleEffect, Tools::LightSourceEffect, Tools::HslEffect, Tools::HslGreenEffect, Tools::WindowEffect;
	boost::shared_ptr<Effect> Tools::PaintEffect_SpriteBatch;
	boost::shared_ptr<EzTextureWad> Tools::TextureWad;
	boost::shared_ptr<ContentManager> Tools::SoundContentManager;
	boost::shared_ptr<EzSoundWad> Tools::SoundWad, Tools::PrivateSoundWad;
	boost::shared_ptr<EzSongWad> Tools::SongWad;
	boost::shared_ptr<QuadDrawer> Tools::QDrawer;
	boost::shared_ptr<MainRender> Tools::Render;
	boost::shared_ptr<GraphicsDevice> Tools::Device;
	boost::shared_ptr<RenderTarget2D> Tools::DestinationRenderTarget;
	float Tools::t;
	float Tools::dt;
	int Tools::DrawCount;
	int Tools::PhsxCount;
	boost::shared_ptr<EzSong> Tools::Song_140mph, Tools::Song_Happy, Tools::Song_BlueChair, Tools::Song_Ripcurl, Tools::Song_Evidence, Tools::Song_GetaGrip, Tools::Song_House, Tools::Song_Nero, Tools::Song_FatInFire, Tools::Song_Heavens, Tools::Song_TidyUp, Tools::Song_WritersBlock;
	std::vector<boost::shared_ptr<EzSong> > Tools::SongList_Standard;
	bool Tools::FreeCam;
	bool Tools::DrawBoxes;
	bool Tools::DrawGraphics;
	bool Tools::StepControl;
	int Tools::_PhsxSpeed;
	
	bool Tools::ShowLoadingScreen;
	boost::shared_ptr<ILoadingScreen> Tools::CurrentLoadingScreen;

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
		return bit == std::wstring( L"" ) || bit == std::wstring( L" " ) || bit == std::wstring( L"\t" );
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

		/*boost::shared_ptr<System::IO::FileStream> stream = File->Open( std::wstring( L"dump" ), FileMode::OpenOrCreate, FileAccess::Write, FileShare::None );
		boost::shared_ptr<StreamWriter> writer = boost::make_shared<StreamWriter>( stream );
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

	void Tools::Write( const boost::shared_ptr<Object> &obj )
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
		va_list args;
		va_start( args, str );
		vwprintf( str, args );
		va_end( args );
		
		wprintf( L"\n" );
#endif
#endif
	}

	std::wstring Tools::DefaultObjectDirectory()
	{
		return Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects" ) );
	}

	std::wstring Tools::DefaultDynamicDirectory()
	{
		return Path::Combine( Directory::GetCurrentDirectory(), Path::Combine(Globals::ContentDirectory, std::wstring( L"DynamicLoad" )) );
	}

	std::wstring Tools::SourceTextureDirectory()
	{
		return Path::Combine( Path::GetDirectoryName( Path::GetDirectoryName( Path::GetDirectoryName( Directory::GetCurrentDirectory() ) ) ), std::wstring( L"Content/Art" ) );
	}

	boost::shared_ptr<SimpleObject> Tools::LoadSimpleObject( const std::wstring &file )
	{
		boost::shared_ptr<ObjectClass> SourceObject;
		Tools::UseInvariantCulture();
		/*boost::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<BinaryReader>( stream, Encoding::UTF8 );*/
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<BinaryReader>( file );
		SourceObject = boost::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );
		ObjectClass_PostConstruct( SourceObject, Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );
		SourceObject->ReadFile( reader, EffectWad, TextureWad );
		reader->Close();
		//stream->Close();

		SourceObject->ConvertForSimple();

		return boost::make_shared<SimpleObject>( SourceObject );
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

	void Tools::AddToDo( const boost::shared_ptr<Lambda> &todo )
	{
		TheGame->ToDo->Add( todo );
	}

	const boost::shared_ptr<Camera> &Tools::getCurCamera()
	{
		if ( CurLevel == 0 )
		{
			if ( DummyCamera == 0 )
				DummyCamera = boost::make_shared<Camera>();
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
		//return Tools::ToGUICoordinates(new Vector2(Tools::CurMouseState.X, Tools::CurMouseState.Y), Tools::CurLevel.MainCamera, zoom);
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
	std::wstring Tools::SantitizeOneLineString( std::wstring s, const boost::shared_ptr<EzFont> &font )
	{
		s = RemoveAfter( s, std::wstring( L"\n" ) );
		s = RemoveAfter( s, std::wstring( L"\t" ) );

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		//s = s.Replace( std::wstring( L"{" ), std::wstring( L" " ) );
		Replace( s, '{', ' ' );
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		//s = s.Replace( std::wstring( L"}" ), std::wstring( L" " ) );
		Replace( s, '}', ' ' );

		// FIXME: Re-enable this logic.
		/*try
		{
			font->Font->MeasureString( s );
		}
		catch ( ... )
		{
			s = std::wstring( L"Invalid" );
		}*/

		return s;
	}
#endif

#if ! defined(WINDOWS)
	std::wstring Tools::SantitizeOneLineString( const std::wstring &s, const boost::shared_ptr<EzFont> &font )
	{
		return s;
	}
#endif

	std::wstring Tools::StripPath( const std::wstring &file )
	{
		int LastSlash = file.rfind( std::wstring( L"/" ) );
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

		int FirstSlash = path.find( std::wstring( L"/" ) );
		if ( FirstSlash < 0 )
			return path;
		else
			return path.substr( 0, FirstSlash );
	}

	boost::shared_ptr<EzTexture> Tools::Texture( const std::wstring &name )
	{
		return TextureWad->FindByName( name );
	}

	boost::shared_ptr<EzSound> Tools::Sound( const std::wstring &name )
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
		wss << std::wstring( L"Pop_" );
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

	void Tools::LoadBasicArt( const boost::shared_ptr<ContentManager> &Content )
	{
		TextureWad = boost::make_shared<EzTextureWad>();
		TextureWad->AddTexture( Content->Load<Texture2D>( std::wstring( L"White" ) ), std::wstring( L"White" ) );
		TextureWad->AddTexture( Content->Load<Texture2D>( std::wstring( L"Circle" ) ), std::wstring( L"Circle" ) );
		TextureWad->AddTexture( Content->Load<Texture2D>( std::wstring( L"Smooth" ) ), std::wstring( L"Smooth" ) );

		TextureWad->DefaultTexture = TextureWad->TextureList[ 0 ];
	}

	std::wstring Tools::GetFileName( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( std::wstring( L"/" ) );
		int j = FilePath.find( std::wstring( L"." ), i );
		if ( j < 0 )
			j = FilePath.length();
		if ( i < 0 )
			return FilePath.substr( 0, j - 1 );
		else
			return FilePath.substr( i + 1, j - 1 - i );
	}

	std::wstring Tools::GetFileNamePlusExtension( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( std::wstring( L"/" ) );
		int n = FilePath.length();
		if ( i < 0 )
			return FilePath.substr( 0, n - 1 );
		else
			return FilePath.substr( i + 1, n - 1 - i );
	}

	std::wstring Tools::GetFileBigName( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( std::wstring( L"/" ) );
		if ( i < 0 )
			return FilePath;

		std::wstring Path = FilePath.substr( 0, i );
		i = Path.rfind( std::wstring( L"/" ) );

		if ( i < 0 )
			return FilePath;
		else
			return FilePath.substr( i + 1 );
	}

	std::wstring Tools::GetFileName( const std::wstring &path, const std::wstring &FilePath )
	{
		int i = FilePath.find( path ) + path.length() + 1;
		if ( i < 0 )
			return std::wstring( L"ERROR" );
		int j = FilePath.find( std::wstring( L"." ), i );
		if ( j <= i )
			return std::wstring( L"ERROR" );

		return FilePath.substr( i, j - i );
	}

	std::wstring Tools::GetFileExt( const std::wstring &path, const std::wstring &FilePath )
	{
		int j = FilePath.find( std::wstring( L"." ) );
		if ( j < 0 )
			return std::wstring( L"ERROR" );

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

	boost::shared_ptr<EzEffect> Tools::Text_NoOutline, Tools::Text_ThinOutline, Tools::Text_ThickOutline;
	void Tools::LoadEffects( const boost::shared_ptr<ContentManager> &Content, bool CreateNewWad )
	{
		if ( CreateNewWad )
			EffectWad = boost::make_shared<EzEffectWad>();

		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/BasicEffect" ) ), std::wstring( L"Basic" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/NoTexture" ) ), std::wstring( L"NoTexture" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/Circle" ) ), std::wstring( L"Circle" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/Shell" ) ), std::wstring( L"Shell" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/FireballEffect" ) ), std::wstring( L"Fireball" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/Paint" ) ), std::wstring( L"Paint" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/Lava" ) ), std::wstring( L"Lava" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/LightMap" ) ), std::wstring( L"LightMap" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/LightSource" ) ), std::wstring( L"LightSource" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/BwEffect" ) ), std::wstring( L"BW" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/Hsl_Green" ) ), std::wstring( L"Hsl_Green" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/Hsl" ) ), std::wstring( L"Hsl" ) );
		EffectWad->AddEffect( Content->Load<Effect>( std::wstring( L"Shaders/Window" ) ), std::wstring( L"Window" ) );

        EffectWad->AddEffect( Content->Load<Effect>( L"Shaders/Text_NoOutline" ), L"Text_NoOutline" );
        Text_NoOutline = EffectWad->FindByName( L"Text_NoOutline" );

        EffectWad->AddEffect( Content->Load<Effect>( L"Shaders/Text_ThinOutline" ), L"Text_ThinOutline" );
        Text_ThinOutline = EffectWad->FindByName( L"Text_ThinOutline" );

        EffectWad->AddEffect( Content->Load<Effect>( L"Shaders/Text_ThickOutline" ), L"Text_ThickOutline" );
        Text_ThickOutline = EffectWad->FindByName( L"Text_ThickOutline" );

		BasicEffect = EffectWad->EffectList[ 0 ];
		NoTexture = EffectWad->EffectList[ 1 ];
		CircleEffect = EffectWad->EffectList[ 2 ];
		LightSourceEffect = EffectWad->FindByName( std::wstring( L"LightSource" ) );
		HslEffect = EffectWad->FindByName( std::wstring( L"Hsl" ) );
		HslGreenEffect = EffectWad->FindByName( std::wstring( L"Hsl_Green" ) );
		WindowEffect = EffectWad->FindByName( std::wstring( L"Window" ) );

		PaintEffect_SpriteBatch = Content->Load<Effect>( std::wstring( L"Shaders/Paint_SpriteBatch" ) );
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
			/*MediaPlayer::Volume = NewVolume;
			CurVolume = MediaPlayer::Volume;*/
			MediaPlayer::SetVolume( NewVolume );
			CurVolume = MediaPlayer::GetVolume();
		}
	}

	void Tools::BeginLoadingScreen( bool KillMusic )
	{
		if ( KillMusic && Tools::SongWad != 0 && KillMusicOnLoadingScreen && !DoNotKillMusicOnNextLoadingscreen )
			Tools::SongWad->FadeOut();
		DoNotKillMusicOnNextLoadingscreen = false;

		Tools::ShowLoadingScreen = true;

		CurrentLoadingScreen = boost::make_shared<LoadingScreen>();

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
		//boost::shared_ptr<std::vector<void*> > bits = line.Split( L' ', L'\t' )->ToList();
		
		// FIXME: Fix this monstrosity.
		std::vector<std::wstring> temp_bits = Split( line, L' ' );
		std::vector<std::wstring> bits;
		for( std::vector<std::wstring>::iterator i = temp_bits.begin(); i != temp_bits.end(); ++i )
		{
			std::vector<std::wstring> more_bits = Split( *i, L'\t' );
			AddRange( bits, more_bits );
		}

		Tools::RemoveAll( bits, boost::static_pointer_cast<LambdaFunc_1<std::wstring, bool> >( boost::make_shared<RemoveBitsLambda>() ) );

		return bits;
	}

	std::vector<std::wstring> Tools::GetBitsFromReader( const boost::shared_ptr<StreamReader> &reader )
	{
		return GetBitsFromLine( reader->ReadLine() );
	}

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
		std::wstring ws = str;
		int CommentIndex = str.find( std::wstring( L"//" ) );
		if ( CommentIndex >= 0 )
			ws = str.substr( 0, CommentIndex );
		return ws;
	}

	std::wstring Tools::RemoveComment_DashStyle( const std::wstring &str )
	{
		std::wstring ws = str;
		int CommentIndex = str.find( std::wstring( L"--" ) );
		if ( CommentIndex >= 0 )
			ws = str.substr( 0, CommentIndex );
		return ws;
	}

	Vector2 Tools::ParseToVector2( const std::wstring &bit1, const std::wstring &bit2 )
	{
		Vector2 Vec = Vector2();

		ParseFloat( bit1, Vec.X );
		ParseFloat( bit2, Vec.Y );

		return Vec;
	}

	Vector4 Tools::ParseToVector4( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4 )
	{
		Vector4 Vec = Vector4();

		ParseFloat( bit1, Vec.X );
		ParseFloat( bit2, Vec.Y );
		ParseFloat( bit3, Vec.Z );
		ParseFloat( bit4, Vec.W );

		return Vec;
	}

	PhsxData Tools::ParseToPhsxData( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 )
	{
		PhsxData data = PhsxData();

		ParseFloat( bit1, data.Position.X     );
		ParseFloat( bit2, data.Position.Y     );
		ParseFloat( bit3, data.Velocity.X     );
		ParseFloat( bit4, data.Velocity.Y     );
		ParseFloat( bit5, data.Acceleration.X );
		ParseFloat( bit6, data.Acceleration.Y );

		return data;
	}

	BasePoint Tools::ParseToBasePoint( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 )
	{
		BasePoint b = BasePoint();

		ParseFloat( bit1, b.e1.X     );
		ParseFloat( bit2, b.e1.Y     );
		ParseFloat( bit3, b.e2.X     );
		ParseFloat( bit4, b.e2.Y     );
		ParseFloat( bit5, b.Origin.X );
		ParseFloat( bit6, b.Origin.Y );

		return b;
	}

	MyOwnVertexFormat Tools::ParseToMyOwnVertexFormat( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6, const std::wstring &bit7, const std::wstring &bit8 )
	{
		MyOwnVertexFormat b = MyOwnVertexFormat();

		ParseFloat( bit1, b.xy.X );
		ParseFloat( bit2, b.xy.Y );
						 
		ParseFloat( bit3, b.uv.X );
		ParseFloat( bit4, b.uv.Y );

		b.TheColor.R = Parse<unsigned char>( bit5 );
		b.TheColor.G = Parse<unsigned char>( bit6 );
		b.TheColor.B = Parse<unsigned char>( bit7 );
		b.TheColor.A = Parse<unsigned char>( bit8 );

		return b;
	}

	Vector2 Tools::ParseToVector2( const std::wstring &str )
	{
		int CommaIndex = str.find( std::wstring( L"," ) );
		Vector2 Vec = Vector2();

		std::wstring Component1, Component2;
		Component1 = str.substr( 0, CommaIndex );
		Component2 = str.substr( CommaIndex + 1, str.length() - CommaIndex - 1 );
		ParseFloat( Component1, Vec.X );
		ParseFloat( Component2, Vec.Y );

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
		int CommaIndex = str.find( std::wstring( L"," ) );
		int CommaIndex2 = str.find( std::wstring( L"," ), CommaIndex + 1 );
		int CommaIndex3 = str.find( std::wstring( L"," ), CommaIndex2 + 1 );

		std::wstring Component1, Component2, Component3, Component4;
		Component1 = str.substr( 0, CommaIndex );
		Component2 = str.substr( CommaIndex + 1, CommaIndex2 - CommaIndex - 1 );
		Component3 = str.substr( CommaIndex2 + 1, CommaIndex3 - CommaIndex2 - 1 );
		Component4 = str.substr( CommaIndex3 + 1, str.length() - CommaIndex3 - 1 );

		Color clr = Color( Parse<unsigned char>( Component1 ), Parse<unsigned char>( Component2 ), Parse<unsigned char>( Component3 ), Parse<unsigned char>( Component4 ) );

		return clr;
	}

	boost::shared_ptr<EzSound> Tools::ParseToEzSound( const std::wstring &str )
	{
		int LineIndex = str.find( std::wstring( L"|" ) );

		std::wstring Component1, Component2;
		Component1 = str.substr( 0, LineIndex );
		Component2 = str.substr( LineIndex + 1, str.length() - LineIndex - 1 );

		float val = 0; ParseFloat( Component2, val );
		return NewSound( ParseToFileName( Component1 ), val );
	}

	boost::shared_ptr<EzSound> Tools::NewSound( const std::wstring &name, float volume )
	{
		boost::shared_ptr<EzSound> snd = boost::make_shared<EzSound>();
		snd->sound = Tools::SoundWad->FindByName( name )->sound;
		snd->DefaultVolume = volume;
		snd->MaxInstances = 4;

		Tools::PrivateSoundWad->SoundList.push_back( snd );

		return snd;
	}

	std::wstring Tools::ParseToFileName( const std::wstring &str )
	{
		int Quote1 = str.find( std::wstring( L"\"" ) );
		int Quote2 = str.find( std::wstring( L"\"" ), Quote1 + 1 );

		std::wstring Name = str.substr( Quote1 + 1, Quote2 - Quote1 - 1 );
		return Name;
	}

/*template<typename T>
	int Tools::Length()
	{
		return GetValues<T>()->Count();
	}*/

/*template<typename T>
	boost::shared_ptr<IEnumerable<T> > Tools::GetValues()
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

	void Tools::MoveTo( const boost::shared_ptr<ObjectBase> &obj, Vector2 pos )
	{
		obj->Move( pos - obj->getCore()->Data.Position );
	}

	Vector2 Tools::ToScreenCoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam, Vector2 ZoomMod )
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

	Vector2 Tools::ToGUICoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam )
	{
		return ToWorldCoordinates( pos, cam, Vector2( .001f,.001f ) );
	}

	Vector2 Tools::ToGUICoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam, Vector2 zoom )
	{
		return ToWorldCoordinates( pos, cam, zoom );
	}

	Vector2 Tools::ToWorldCoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam )
	{
		return ToWorldCoordinates( pos, cam, cam->getZoom() );
	}

	Vector2 Tools::ToWorldCoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam, Vector2 zoom )
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

        /// <summary>
        /// Call before drawing GUI elements unaffected by the camera.
        /// Does not affect the current drawing camera ("fake").
        /// </summary>
        void Tools::StartGUIDraw_Fake()
        {
            GUIDraws++;
            if (GUIDraws > 1) return;

            // Start the GUI drawing if this is the first call to GUIDraw
            Tools::CurLevel->getMainCamera()->HoldZoom = Tools::CurLevel->getMainCamera()->getZoom();
            Tools::CurLevel->getMainCamera()->setZoom( Vector2(.001f, .001f) );
            Tools::CurLevel->getMainCamera()->Update();

            // Save global illumination level
            HoldIllumination = Tools::QDrawer->getGlobalIllumination();
            Tools::QDrawer->setGlobalIllumination( 1.f );
        }

        /// <summary>
        /// Call after finishing drawing GUI elements unaffected by the camera.
        /// Does not affect the current drawing camera ("fake").
        /// </summary>
        void Tools::EndGUIDraw_Fake()
        {
            GUIDraws--;
            if (GUIDraws > 0) return;

            // End the GUI drawing if this is the last call to GUIDraw
            Tools::CurLevel->getMainCamera()->setZoom( Tools::CurLevel->getMainCamera()->HoldZoom );
            Tools::CurLevel->getMainCamera()->Update();

            // Restor global illumination level
            Tools::QDrawer->setGlobalIllumination( HoldIllumination );
        }

	void Tools::SetDefaultEffectParams( float AspectRatio )
	{
		for ( std::vector<boost::shared_ptr<EzEffect> >::const_iterator fx = EffectWad->EffectList.begin(); fx != EffectWad->EffectList.end(); ++fx )
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
		return StringConverterHelper::toString( num ) + std::wstring( L"/" ) + StringConverterHelper::toString( outof );
		//return "x" + num.ToString() + "/" + outof.ToString();
	}

	std::wstring Tools::ScoreString( int num )
	{
		return StringConverterHelper::toString( num );
		//return "x" + num.ToString();
	}

	void Tools::EnsureBounds_X( const boost::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL )
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

	void Tools::EnsureBounds_Y( const boost::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL )
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

	void Tools::EnsureBounds( const boost::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL )
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
