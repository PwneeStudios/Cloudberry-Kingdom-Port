#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Reflection;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;
namespace XnaInput = Microsoft::Xna::Framework::Input;
using namespace Microsoft::Xna::Framework::Media;

namespace CloudberryKingdom
{

	std::wstring StringExtension::Capitalize( const std::wstring &s )
	{
		return toupper( s[ 0 ] ) + s.substr( 1 );
	}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : IComparable
	int Vector2Extension::IndexMax( std::vector<T> list )
	{
		T max = list[ 0 ];
		int index = 0;
		for ( int i = 1; i < list.size(); i++ )
			if ( list[ i ]->compare( max ) > 0 )
			{
				max = list[ i ];
				index = i;
			}

		return index;
	}

	std::wstring Vector2Extension::ToSimpleString( Vector2 v )
	{
		return std::wstring::Format( _T( "{0}, {1}" ), v.X, v.Y );
	}

	std::vector<Vector2> Vector2Extension::Map( std::vector<Vector2> list, Func<Vector2, Vector2> map )
	{
		std::vector<Vector2> product = std::vector<Vector2>( list.size() );
		list.CopyTo( product, 0 );

		for ( int i = 0; i < list.size(); i++ )
			product[ i ] = map( product[ i ] );

		return product;
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

std::vector<long long> StringBuilderExtension::digits = std::vector<long long>( max_digits );

	void StringBuilderExtension::ClearDigits()
	{
		for ( int i = 0; i < max_digits; i++ )
			digits[ i ] = 0;
	}

	int StringBuilderExtension::LastDigit()
	{
		for ( int i = max_digits - 1; i >= 0; i-- )
			if ( digits[ i ] > 0 )
				return i;
		return 0;
	}

const wchar_t tempVector[] = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' };
std::vector<wchar_t> StringBuilderExtension::digit_char = std::vector<wchar_t>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );

	void StringBuilderExtension::DigitsToString( const std::shared_ptr<StringBuilder> &str, int NumDigits )
	{
		for ( int i = NumDigits - 1; i >= 0; i-- )
			str->Append( digit_char[ digits[ i ] ] );
	}

	void StringBuilderExtension::Add( const std::shared_ptr<StringBuilder> &str, long long num )
	{
		Add( str, num, 1 );
	}

	void StringBuilderExtension::Add( const std::shared_ptr<StringBuilder> &str, long long num, int MinDigits )
	{
		if ( num < 0 )
		{
			str->Append( L'-' );
			num *= -1;
		}

		ClearDigits();

		for ( int i = max_digits - 1; i >= 0; i-- )
		{
			double pow = pow( 10, i );
			long long _pow = static_cast<long long>( Math::Round( pow ) );
			long long digit = num / _pow;
			digits[ i ] = digit;
			num -= _pow * digit;
		}

		int DigitsToAppend = __max( LastDigit() + 1, MinDigits );
		DigitsToString( str, DigitsToAppend );
	}

template<typename T>
	Microsoft::Xna::Framework::Vector2 ListExtension::Sum( std::vector<T> &list, Func<T, Vector2> map )
	{
		Vector2 sum = Vector2::Zero;
		for ( std::vector<T>::const_iterator item = list.begin(); item != list.end(); ++item )
			sum += map( *item );

		return sum;
	}

template<typename T>
	T ListExtension::Choose( std::vector<T> list, const std::shared_ptr<Rand> &rnd )
	{
		return list[ rnd->RndInt( 0, list.size() - 1 ) ];
	}

template<typename T>
	T ListExtension::Choose( std::vector<T> &list, const std::shared_ptr<Rand> &rnd )
	{
		if ( rnd == 0 )
			return list[ 0 ];
		else
		//if (list == null || list.Count == 0) return null;
			return list[ rnd->RndInt( 0, list.size() - 1 ) ];
	}

template<typename T>
	int ListExtension::IndexOf( std::vector<T> &list, Predicate<T> match )
	{
		return list.find( list.Find( match ) );
	}

#if defined(XBOX)
template<typename T>
	T ListExtension::Find( std::vector<T> &list, Predicate<T> func )
	{
		for ( std::vector<T>::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( func( *item ) )
				return item;
		}

		return T();
	}
#endif

#if defined(XBOX)
template<typename T>
	std::vector<T> ListExtension::FindAll( std::vector<T> &list, Predicate<T> func )
	{
		std::vector<T> matches = std::vector<T>();

		for ( std::vector<T>::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( func( *item ) )
				matches.push_back( *item );
		}

		return matches;
	}
#endif

#if defined(XBOX)
template<typename T>
	int ListExtension::FindIndex( std::vector<T> &list, Predicate<T> func )
	{
		for ( int i = 0; i < list.size(); i++ )
		{
			if ( func( list[ i ] ) )
				return i;
		}

		return -1;
	}
#endif

#if defined(XBOX)
template<typename T>
	bool ListExtension::Exists( std::vector<T> &list, Predicate<T> func )
	{
		for ( std::vector<T>::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( func( *item ) )
				return true;
		}

		return false;
	}
#endif

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T, typename S> where T : class where S : class
	void ListExtension::AddRangeAndConvert( std::vector<T> &list, std::vector<S> &range )
	{
		for ( std::vector<S>::const_iterator s = range.begin(); s != range.end(); ++s )
			list.push_back( dynamic_cast<T*>( *s ) );
	}

template<typename T>
	std::vector<T> ArrayExtension::Range( array_Renamed<T> *array_Renamed, int StartIndex, int EndIndex )
	{
		// Make sure we don't extend past the end of the array
		EndIndex = __min( EndIndex, array_Renamed.size() - 1 );

		// Create a new array to store the range
		std::vector<T> range = std::vector<T>( EndIndex - StartIndex + 1 );

		for ( int i = StartIndex; i <= EndIndex; i++ )
			range[ i - StartIndex ] = array_Renamed[ i ];

		return range;
	}

template<typename TKey, typename TValue>
	void DictionaryExtension::RemoveAll( std::unordered_map<TKey, TValue> &dict, Func<KeyValuePair<TKey, TValue>*, bool> condition )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( unknown::const_iterator cur = dict.Where( condition )->ToList().begin(); cur != dict.Where(condition)->ToList().end(); ++cur )
		{
			dict.erase( ( *cur )->Key );
		}
	}

template<typename TKey, typename TValue>
	void DictionaryExtension::AddOrOverwrite( std::unordered_map<TKey, TValue> &dict, TKey key, TValue value )
	{
		if ( dict.find( key ) != dict.end() )
			dict[ key ] = value;
		else
			dict.insert( make_pair( key, value ) );
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
		std::shared_ptr<System::IO::FileStream> stream = File->Open( _T( "dump" ), FileMode::OpenOrCreate, FileAccess::Write, FileShare::None );
		std::shared_ptr<StreamWriter> writer = std::make_shared<StreamWriter>( stream );
		writer->Write( dump );
		writer->Close();
		stream->Close();
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

	void Tools::Write( const std::wstring &str, ... )
	{
#if defined(DEBUG)
#if defined(WINDOWS)
	if ( objs->Length == 0 )
		std::cout << str << std::endl;
	else
		std::cout << std::endl;
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
	return Path::Combine( Path::GetDirectoryName( Path::GetDirectoryName( Path::GetDirectoryName( Directory::GetCurrentDirectory() ) ) ), _T("Content\\Art") );
	}

std::shared_ptr<AftermathData> Tools::CurrentAftermath = 0;
bool Tools::IsMasochistic = false;
bool Tools::AutoLoop = false;
int Tools::AutoLoopDelay = 0;

template<typename T>
	void Tools::Swap( std::shared_ptr<T> &a, std::shared_ptr<T> &b )
	{
		T temp = a;
		a = b;
		b = temp;
	}

template<typename TSource>
	TSource Tools::Find( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
	{
		for ( std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
			if ( predicate->Apply( *obj ) )
				return obj;
		return TSource();
	}

template<typename TSource>
	std::vector<TSource> Tools::FindAll( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
	{
		std::vector<TSource> newlist = std::vector<TSource>();
		for ( std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
			if ( predicate->Apply( *obj ) )
				newlist.push_back( *obj );
		return newlist;
	}

template<typename TSource>
	bool Tools::All( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
	{
		bool all = true;
		for ( std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
			if ( !predicate->Apply( *obj ) )
				all = false;
		return all;
	}

template<typename TSource>
	bool Tools::Any( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
	{
		for ( std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
			if ( predicate->Apply( *obj ) )
				return true;
		return false;
	}

template<typename TSource>
	void Tools::RemoveAll( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
	{
		int OpenSlot = 0;
		int i = 0;
		int N = list.size();

		while ( i < N )
		{
			if ( predicate->Apply( list[ i ] ) )
				i++;
			else
			{
				list[ OpenSlot ] = list[ i ];

				i++;
				OpenSlot++;
			}
		}

		list.RemoveRange( OpenSlot, N - OpenSlot );
	}

template<typename TSource>
	void Tools::RemoveAll( std::vector<TSource> &source, const std::shared_ptr<LambdaFunc_2<TSource, int, bool> > &predicate )
	{
		int i = 0;
		int j = 0;
		int N = source.size();
		while ( i < N )
		{
			while ( j < N && predicate->Apply( source[ j ], j ) )
				j++;

			if ( j == N )
				break;

			source[ i ] = source[ j ];
			i++;
			j++;
		}

		if ( i == N )
			return;

		source.RemoveRange( i, N - i );
	}

template<typename TSource>
	TSource Tools::ArgMin( const std::shared_ptr<IEnumerable<TSource> > &source, const std::shared_ptr<LambdaFunc_1<TSource, float> > &val )
	{
		TSource min = TSource();
		float minval = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( IEnumerable<TSource>::const_iterator item = source->begin(); item != source->end(); ++item )
			if ( min == 0 || val->Apply( *item ) < minval )
			{
				minval = val->Apply( *item );
				min = *item;
			}

		return min;
	}

template<typename TSource>
	TSource Tools::ArgMax( const std::shared_ptr<IEnumerable<TSource> > &source, const std::shared_ptr<LambdaFunc_1<TSource, float> > &val )
	{
		TSource max = TSource();
		float maxval = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( IEnumerable<TSource>::const_iterator item = source->begin(); item != source->end(); ++item )
			if ( max == 0 || val->Apply( *item ) > maxval )
			{
				maxval = val->Apply( *item );
				max = *item;
			}

		return max;
	}

	std::shared_ptr<SimpleObject> Tools::LoadSimpleObject( const std::wstring &file )
	{
		std::shared_ptr<ObjectClass> SourceObject;
		Tools::UseInvariantCulture();
		std::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<BinaryReader> reader = std::make_shared<BinaryReader>( stream, Encoding::UTF8 );
		SourceObject = std::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PresentationParameters, 100, 100, EffectWad->FindByName( _T( "BasicEffect" ) ), TextureWad->FindByName( _T( "White" ) ) );
		SourceObject->ReadFile( reader, EffectWad, TextureWad );
		reader->Close();
		stream->Close();

		SourceObject->ConvertForSimple();

		return std::make_shared<SimpleObject>( SourceObject );
	}

float Tools::_VolumeFade = 0;

	const float &Tools::getVolumeFade() const
	{
		return _VolumeFade;
	}

	void Tools::setVolumeFade( const float &value )
	{
		_VolumeFade = value;
		UpdateVolume();
	}

float Tools::CurSongVolume = 0;
std::shared_ptr<WrappedFloat> SoundVolume, Tools::MusicVolume = 0;
bool Tools::FixedTimeStep = false;
bool Tools::WindowBorder = true;
std::shared_ptr<XnaGameClass> Tools::GameClass = 0;
std::shared_ptr<CloudberryKingdomGame> Tools::TheGame = 0;

	const Version &Tools::getGameVersion() const
	{
		return CloudberryKingdomGame::GameVersion;
	}

	void Tools::AddToDo( const std::shared_ptr<Lambda> &todo )
	{
		TheGame->ToDo->Add( todo );
	}

const std::wstring tempVector2[] = { _T( "A" ), _T( "B" ), _T( "X" ), _T( "Y" ), _T( "RS" ), _T( "LS" ), _T( "RT" ), _T( "LT" ), _T( "RJ" ), _T( "RJ" ), _T( "LJ" ), _T( "LJ" ), _T( "DPad" ), _T( "Start" ) };
std::vector<std::wstring> Tools::ButtonNames = std::vector<std::wstring>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
const std::wstring tempVector3[] = { _T( "right" ), _T( "up" ), _T( "left" ), _T( "down" ) };
std::vector<std::wstring> Tools::DirNames = std::vector<std::wstring>( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );
std::shared_ptr<GameFactory> Tools::CurGameType = 0;
std::shared_ptr<GameData> Tools::CurGameData = 0;
std::shared_ptr<Level> Tools::CurLevel = 0;
std::shared_ptr<Camera> Tools::DummyCamera = 0;

	const std::shared_ptr<Camera> &Tools::getCurCamera() const
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

std::shared_ptr<GameData> WorldMap, Tools::TitleGame = 0;
const int tempVector4[] = { 0, 0, 0, 0 };
std::vector<int> Tools::VibrateTimes = std::vector<int>( tempVector4, tempVector4 + sizeof( tempVector4 ) / sizeof( tempVector4[ 0 ] ) );
int Tools::DifficultyTypes = Tools::GetValues<DifficultyParam>()->Count();
int Tools::StyleTypes = 8;
int Tools::UpgradeTypes = Tools::GetValues<Upgrade>()->Count();
#if defined(WINDOWS)
Microsoft::Xna::Framework::Input::KeyboardState Keyboard, Tools::PrevKeyboard = 0;
#endif

#if defined(WINDOWS)
Microsoft::Xna::Framework::Input::MouseState Mouse, Tools::PrevMouse = 0;
#endif

#if defined(WINDOWS)
Vector2 DeltaMouse, Tools::RawDeltaMouse = 0;
#endif

#if defined(WINDOWS)
int Tools::DeltaScroll = 0;
#endif

#if defined(WINDOWS)
bool Tools::MouseInWindow = false;
#endif

#if defined(WINDOWS)
	const Microsoft::Xna::Framework::Vector2 &Tools::getMousePos() const
	{
		return Vector2( Mouse.X, Mouse.Y ) / Tools::Render->SpriteScaling;
	}
#endif

#if defined(WINDOWS)
	void Tools::setMousePos( const Vector2 &value )
	{
		XnaInput::Mouse::SetPosition( static_cast<int>( value.X * Tools::Render->SpriteScaling ), static_cast<int>( value.Y * Tools::Render->SpriteScaling ) );
	}
#endif

#if defined(WINDOWS)
	const bool &Tools::getFullscreen() const
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
		return Mouse.LeftButton == XnaInput::ButtonState::Pressed;
	}
#endif

#if defined(WINDOWS)
	bool Tools::PrevMouseDown()
	{
		return PrevMouse.LeftButton == XnaInput::ButtonState::Pressed;
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
		return Mouse.RightButton == XnaInput::ButtonState::Pressed;
	}
#endif

#if defined(WINDOWS)
	bool Tools::PrevRightMouseDown()
	{
		return PrevMouse.RightButton == XnaInput::ButtonState::Pressed;
	}
#endif

#if defined(WINDOWS)
	bool Tools::RightMouseReleased()
	{
		return !CurRightMouseDown() && PrevRightMouseDown();
	}
#endif

#if defined(WINDOWS)
	Microsoft::Xna::Framework::Vector2 Tools::MouseGUIPos( Vector2 zoom )
	{
		//return Tools.ToGUICoordinates(new Vector2(Tools.CurMouseState.X, Tools.CurMouseState.Y), Tools.CurLevel.MainCamera, zoom);
		return Tools::ToGUICoordinates( getMousePos(), Tools::CurLevel->getMainCamera(), zoom );
	}
#endif

#if defined(WINDOWS)
	Microsoft::Xna::Framework::Vector2 Tools::MouseWorldPos()
	{
		return Tools::ToWorldCoordinates( getMousePos(), Tools::CurLevel->getMainCamera() );
	}
#endif

#if defined(WINDOWS)
	bool Tools::ShiftDown()
	{
		return Tools::Keyboard.IsKeyDown( XnaInput::Keys::LeftShift ) || Tools::Keyboard.IsKeyDown( XnaInput::Keys::RightShift );
	}
#endif

#if defined(WINDOWS)
	bool Tools::CntrlDown()
	{
		return Tools::Keyboard.IsKeyDown( XnaInput::Keys::LeftControl ) || Tools::Keyboard.IsKeyDown( XnaInput::Keys::RightControl );
	}
#endif

#if defined(WINDOWS)
	std::wstring Tools::RemoveAfter( const std::wstring &s, const std::wstring &occurence )
	{
		if ( s.find( occurence ) != string::npos )
			s = s.erase( s.find( occurence ) );
		return s;
	}
#endif

#if defined(WINDOWS)
	std::wstring Tools::SantitizeOneLineString( const std::wstring &s, const std::shared_ptr<EzFont> &font )
	{
		s = RemoveAfter( s, _T( "\n" ) );
		s = RemoveAfter( s, _T( "\t" ) );

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		s = s.Replace( _T( "{" ), _T( " " ) );
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		s = s.Replace( _T( "}" ), _T( " " ) );

		try
		{
			font->Font->MeasureString( s );
		}
		catch ( ... )
		{
			s = _T( "Invalid" );
		}

		return s;
	}
#endif

#if ! defined(WINDOWS)
	std::wstring Tools::SantitizeOneLineString( const std::wstring &s, const std::shared_ptr<EzFont> &font )
	{
		return s;
	}
#endif

std::vector<Microsoft::Xna::Framework::Input::GamePadState> GamepadState, *Tools::PrevGamepadState = 0;

	std::wstring Tools::StripPath( const std::wstring &file )
	{
		int LastSlash = file.rfind( _T( "\\" ) );
		if ( LastSlash < 0 )
			return file;
		else
			return file.substr( LastSlash + 1 );
	}

	std::wstring Tools::FirstFolder( const std::wstring &path, const std::wstring &ignore )
	{
		int i = path.find( ignore );
		if ( i >= 0 )
			path = path.substr( i + ignore.length() );

		int FirstSlash = path.find( _T( "\\" ) );
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
		Sound( _T( "Pop_" ) + CoreMath::Restrict( 1, 3, Pitch ).ToString() )->Play();
	}

std::shared_ptr<GameTime> Tools::gameTime = 0;
std::shared_ptr<Rand> Tools::GlobalRnd = std::make_shared<Rand>( 0 );
std::shared_ptr<EzEffectWad> Tools::EffectWad = 0;
std::shared_ptr<EzEffect> BasicEffect, NoTexture, CircleEffect, LightSourceEffect, HslEffect, HslGreenEffect, Tools::WindowEffect = 0;
std::shared_ptr<Effect> Tools::PaintEffect_SpriteBatch = 0;
std::shared_ptr<EzTextureWad> Tools::TextureWad = 0;
std::shared_ptr<ContentManager> Tools::SoundContentManager = 0;
std::shared_ptr<EzSoundWad> SoundWad, Tools::PrivateSoundWad = 0;
std::shared_ptr<EzSongWad> Tools::SongWad = 0;
std::shared_ptr<QuadDrawer> Tools::QDrawer = 0;
std::shared_ptr<MainRender> Tools::Render = 0;
std::shared_ptr<GraphicsDevice> Tools::Device = 0;
std::shared_ptr<RenderTarget2D> Tools::DestinationRenderTarget = 0;
float t, Tools::dt = 0;
int DrawCount, Tools::PhsxCount = 0;
std::shared_ptr<EzSong> Song_140mph, Song_Happy, Song_BlueChair, Song_Ripcurl, Song_Evidence, Song_GetaGrip, Song_House, Song_Nero, Song_FatInFire, Song_Heavens, Song_TidyUp, Tools::Song_WritersBlock = 0;
std::vector<EzSong*> Tools::SongList_Standard = std::vector<EzSong*>();
bool Tools::FreeCam = false;
bool Tools::DrawBoxes = false;
bool Tools::DrawGraphics = true;
bool Tools::StepControl = false;
int Tools::_PhsxSpeed = 1;

	const int &Tools::getPhsxSpeed() const
	{
		return _PhsxSpeed;
	}

	void Tools::setPhsxSpeed( const int &value )
	{
		_PhsxSpeed = value;
	}

bool Tools::ShowLoadingScreen = false;
std::shared_ptr<ILoadingScreen> Tools::CurrentLoadingScreen = 0;

	void Tools::LoadBasicArt( const std::shared_ptr<ContentManager> &Content )
	{
		TextureWad = std::make_shared<EzTextureWad>();
		TextureWad->AddTexture( Content->Load<Texture2D*>( _T( "White" ) ), _T( "White" ) );
		TextureWad->AddTexture( Content->Load<Texture2D*>( _T( "Circle" ) ), _T( "Circle" ) );
		TextureWad->AddTexture( Content->Load<Texture2D*>( _T( "Smooth" ) ), _T( "Smooth" ) );

		TextureWad->DefaultTexture = TextureWad->TextureList[ 0 ];
	}

	std::wstring Tools::GetFileName( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( _T( "\\" ) );
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
		int i = FilePath.rfind( _T( "\\" ) );
		int n = FilePath.length();
		if ( i < 0 )
			return FilePath.substr( 0, n - 1 );
		else
			return FilePath.substr( i + 1, n - 1 - i );
	}

	std::wstring Tools::GetFileBigName( const std::wstring &FilePath )
	{
		int i = FilePath.rfind( _T( "\\" ) );
		if ( i < 0 )
			return FilePath;

		std::wstring Path = FilePath.substr( 0, i );
		i = Path.rfind( _T( "\\" ) );

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
		files.AddRange( Directory::GetFiles( path ) );

		if ( IncludeSubdirectories )
		{
			std::vector<std::wstring> dir = Directory::GetDirectories( path );
			for ( int i = 0; i < dir.size(); i++ )
				files.AddRange( GetFiles( dir[ i ], IncludeSubdirectories ) );
		}

		return files.ToArray();
	}

	void Tools::LoadEffects( const std::shared_ptr<ContentManager> &Content, bool CreateNewWad )
	{
		if ( CreateNewWad )
			EffectWad = std::make_shared<EzEffectWad>();

		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\BasicEffect" ) ), _T( "Basic" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\NoTexture" ) ), _T( "NoTexture" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\Circle" ) ), _T( "Circle" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\Shell" ) ), _T( "Shell" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\FireballEffect" ) ), _T( "Fireball" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\Paint" ) ), _T( "Paint" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\Lava" ) ), _T( "Lava" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\LightMap" ) ), _T( "LightMap" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\LightSource" ) ), _T( "LightSource" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\BwEffect" ) ), _T( "BW" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\Hsl_Green" ) ), _T( "Hsl_Green" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\Hsl" ) ), _T( "Hsl" ) );
		EffectWad->AddEffect( Content->Load<Effect*>( _T( "Effects\\Window" ) ), _T( "Window" ) );

		BasicEffect = EffectWad->EffectList[ 0 ];
		NoTexture = EffectWad->EffectList[ 1 ];
		CircleEffect = EffectWad->EffectList[ 2 ];
		LightSourceEffect = EffectWad->FindByName( _T( "LightSource" ) );
		HslEffect = EffectWad->FindByName( _T( "Hsl" ) );
		HslGreenEffect = EffectWad->FindByName( _T( "Hsl_Green" ) );
		WindowEffect = EffectWad->FindByName( _T( "Window" ) );

		PaintEffect_SpriteBatch = Content->Load<Effect*>( _T( "Effects\\Paint_SpriteBatch" ) );
	}

	float Tools::BoxSize( Vector2 TR, Vector2 BL )
	{
		return ( TR.X - BL.X ) * ( TR.Y - BL.Y );
	}

float Tools::CurVolume = -1;

	void Tools::UpdateVolume()
	{
		float NewVolume = Tools::MusicVolume->getVal() * Tools::getVolumeFade() * Tools::CurSongVolume;
		if ( Tools::SongWad != 0 && Tools::SongWad->Paused )
			NewVolume = 0;
		if ( NewVolume != CurVolume )
		{
			MediaPlayer->Volume = NewVolume;
		CurVolume = MediaPlayer::Volume;
		}
	}

bool Tools::KillMusicOnLoadingScreen = true;
bool Tools::DoNotKillMusicOnNextLoadingscreen = false;

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

	std::vector<std::wstring> Tools::GetBitsFromLine( const std::wstring &line )
	{
		line = Tools::RemoveComment_SlashStyle( line );

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		std::shared_ptr<std::vector<void*> > bits = line.Split( L' ', L'\t' )->ToList();

		Tools::RemoveAll( bits, std::make_shared<RemoveBitsLambda>() );

		return bits;
	}

	std::vector<std::wstring> Tools::GetBitsFromReader( const std::shared_ptr<StreamReader> &reader )
	{
		return GetBitsFromLine( reader->ReadLine() );
	}

	std::shared_ptr<Object> Tools::ReadFields( const std::shared_ptr<Object> &obj, const std::shared_ptr<StreamReader> &reader )
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
						std::shared_ptr<IReadWrite> rw = static_cast<IReadWrite*>( info->GetValue( obj ) );
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

							std::shared_ptr<System::Collections::IList> list = dynamic_cast<System::Collections::IList*>( info->GetValue( obj ) );

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
	}

	void Tools::ReadList( const std::shared_ptr<StreamReader> &reader, const std::shared_ptr<System::Collections::IList> &list, const std::shared_ptr<Type> &itemType )
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
					if ( dynamic_cast<IReadWrite*>( newobj ) != 0 )
						( static_cast<IReadWrite*>( newobj ) )->Read( reader );
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
	}

int Tools::WriteRecursiveDepth = 0;
int Tools::WriteObjId = 0;

	void Tools::WriteFields( const std::shared_ptr<Object> &obj, const std::shared_ptr<StreamWriter> &writer, ... )
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
					line = std::wstring::Format( _T( "{0} {1}" ), v.X, v.Y );
				}
				// Vector3
				else if ( ( *info )->FieldType == Vector3::typeid )
				{
					Vector3 v = static_cast<Vector3>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "{0} {1} {2}" ), v.X, v.Y, v.Z );
				}
				// Vector4
				else if ( ( *info )->FieldType == Vector4::typeid )
				{
					Vector4 v = static_cast<Vector4>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "{0} {1} {2} {3}" ), v.X, v.Y, v.Z, v.W );
				}
				// Color
				else if ( ( *info )->FieldType == Color::typeid )
				{
					Color c = static_cast<Color>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "{0} {1} {2} {3}" ), c.R, c.G, c.B, c.A );
				}
				// bool
				else if ( ( *info )->FieldType == bool::typeid )
				{
					bool b = static_cast<bool>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "{0}" ), b );
				}
				// string
				else if ( ( *info )->FieldType == std::wstring::typeid )
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
					line = ( static_cast<std::wstring>( ( *info )->GetValue( obj ) ) )->ToString();
				// EzTexture
				else if ( ( *info )->FieldType == EzTexture::typeid )
				{
					std::shared_ptr<EzTexture> texture = static_cast<EzTexture*>( ( *info )->GetValue( obj ) );
					if ( texture == 0 )
						continue;
					else
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
						line = texture->Name->ToString();
				}
				// EzEffect
				else if ( ( *info )->FieldType == EzEffect::typeid )
				{
					std::shared_ptr<EzEffect> effect = static_cast<EzEffect*>( ( *info )->GetValue( obj ) );
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
					line = std::wstring::Format( _T( "{0} {1} {2} {3} {4} {5}" ), d.Position.X, d.Position.Y, d.Velocity.X, d.Velocity.Y, d.Acceleration.X, d.Acceleration.Y );
				}
				// BasePoint
				else if ( ( *info )->FieldType == BasePoint::typeid )
				{
					BasePoint b = static_cast<BasePoint>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "{0} {1} {2} {3} {4} {5}" ), b.e1.X, b.e1.Y, b.e2.X, b.e2.Y, b.Origin.X, b.Origin.Y );
				}
				// MyOwnVertexFormat
				else if ( ( *info )->FieldType == MyOwnVertexFormat::typeid )
				{
					MyOwnVertexFormat v = static_cast<MyOwnVertexFormat>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "{0} {1} {2} {3} {4} {5} {6} {7}" ), v.xy.X, v.xy.Y, v.uv.X, v.uv.Y, v.Color.R, v.Color.G, v.Color.B, v.Color.A );
				}
				else if ( ( *info )->FieldType->GetInterfaces()->Contains(IReadWrite::typeid) )
				{
					std::shared_ptr<IReadWrite> rw = static_cast<IReadWrite*>( ( *info )->GetValue( obj ) );
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
					writer->WriteLine( WhiteSpace + std::wstring::Format( _T( "{0} {1}" ), ( *info )->Name, line ) );
			}
		}

		WriteRecursiveDepth--;
	}

	void Tools::ResetWrite()
	{
		WriteRecursiveDepth = 0;
		WriteObjId = 0;
	}

	void Tools::WriteCode( const std::wstring &root, const std::shared_ptr<IReadWrite> &rw )
	{
		ResetWrite();

		std::shared_ptr<System::IO::FileStream> stream = File->Open( _T( "code_dump.code" ), FileMode::Create, FileAccess::Write, FileShare::None );
		std::shared_ptr<StreamWriter> writer = std::make_shared<StreamWriter>( stream );

		rw->WriteCode( root, writer );

		writer->Close();
		stream->Close();
	}

	std::wstring Tools::ToCode( Vector2 v )
	{
		return std::wstring::Format( _T( "new Vector2({0}f, {1}f)" ), v.X, v.Y );
	}

	std::wstring Tools::ToCode( const std::wstring &s )
	{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Replace' method:
		return std::wstring::Format( _T( "\"{0}\"" ), s.Replace( _T( "\\" ), _T( "\\\\" ) ) );
	}

bool Tools::LastLineWasBlank = false;

	void Tools::WriteFieldsToCode( const std::shared_ptr<Object> &obj, const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer, ... )
	{
		std::wstring _prefix = prefix;
		if ( prefix.length() > 0 )
			_prefix += _T( "." );

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
				{
					float v = static_cast<float>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "{0}f" ), v );
				}
				// Vector2
				else if ( ( *info )->FieldType == Vector2::typeid )
				{
					Vector2 v = static_cast<Vector2>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "new Vector2({0}f, {1}f)" ), v.X, v.Y );
				}
				// Vector3
				else if ( ( *info )->FieldType == Vector3::typeid )
				{
					Vector3 v = static_cast<Vector3>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "new Vector3({0}f, {1}f, {2}f)" ), v.X, v.Y, v.Z );
				}
				// Vector4
				else if ( ( *info )->FieldType == Vector4::typeid )
				{
					Vector4 v = static_cast<Vector4>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "new Vector4({0}f, {1}f, {2}f, {3}f)" ), v.X, v.Y, v.Z, v.W );
				}
				// Color
				else if ( ( *info )->FieldType == Color::typeid )
				{
					Color c = static_cast<Color>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "new Color({0}, {1}, {2}, {3})" ), c.R, c.G, c.B, c.A );
				}
				// bool
				else if ( ( *info )->FieldType == bool::typeid )
				{
					bool b = static_cast<bool>( ( *info )->GetValue( obj ) );
					line = b ? _T( "true" ) : _T( "false" );
				}
				// string
				else if ( ( *info )->FieldType == std::wstring::typeid )
					line = std::wstring::Format( _T( "\"{0}\"" ), ( static_cast<std::wstring>( ( *info )->GetValue( obj ) ) ) );
				// EzTexture
				else if ( ( *info )->FieldType == EzTexture::typeid )
				{
					std::shared_ptr<EzTexture> texture = static_cast<EzTexture*>( ( *info )->GetValue( obj ) );
					if ( 0 == texture )
						line = _T( "null" );
					else
						line = std::wstring::Format( _T( "Tools.Texture(\"{0}\")" ), texture->Name );
				}
				// EzEffect
				else if ( ( *info )->FieldType == EzEffect::typeid )
				{
					std::shared_ptr<EzEffect> effect = static_cast<EzEffect*>( ( *info )->GetValue( obj ) );
					if ( effect == 0 )
						continue;
					else
					{
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//						switch (effect.Name)
//ORIGINAL LINE: case "Basic":
						if ( effect->Name == _T( "Basic" ) )
						{
								line = _T( "Tools.BasicEffect" );
						}
//ORIGINAL LINE: case "Window":
						else if ( effect->Name == _T( "Window" ) )
						{
								line = _T( "Tools.WindowEffect" );
						}
						else
						{
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
								line = std::wstring::Format( _T( "Tools.Effect(\"{0}\")" ), effect->Name->ToString() );
						}
					}
				}
				// PhsxData
				else if ( ( *info )->FieldType == PhsxData::typeid )
				{
					PhsxData d = static_cast<PhsxData>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "new PhsxData({0}f, {1}f, {2}f, {3}f, {4}f, {5}f)" ), d.Position.X, d.Position.Y, d.Velocity.X, d.Velocity.Y, d.Acceleration.X, d.Acceleration.Y );
				}
				// MyOwnVertexFormat
				else if ( ( *info )->FieldType == MyOwnVertexFormat::typeid )
				{
					MyOwnVertexFormat v = static_cast<MyOwnVertexFormat>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "new MyOwnVertexFormat(new Vector2({0}f, {1}f), new Vector2({2}f, {3}f), new Color({4}, {5}, {6}, {7}))" ), v.xy.X, v.xy.Y, v.uv.X, v.uv.Y, v.Color.R, v.Color.G, v.Color.B, v.Color.A );
				}
				// BasePoint
				else if ( ( *info )->FieldType == BasePoint::typeid )
				{
					BasePoint b = static_cast<BasePoint>( ( *info )->GetValue( obj ) );
					line = std::wstring::Format( _T( "new BasePoint({0}f, {1}f, {2}f, {3}f, {4}f, {5}f)" ), b.e1.X, b.e1.Y, b.e2.X, b.e2.Y, b.Origin.X, b.Origin.Y );
				}
				else if ( ( *info )->FieldType->GetInterfaces()->Contains(IReadWrite::typeid) )
				{
					std::shared_ptr<IReadWrite> rw = static_cast<IReadWrite*>( ( *info )->GetValue( obj ) );
					if ( 0 == rw && !( *info )->FieldType->IsValueType )
						continue;

					rw->WriteCode( _prefix + ( *info )->Name, writer );
					if ( !LastLineWasBlank )
						writer->WriteLine();
					LastLineWasBlank = true;
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
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
							for ( IEnumerable<IReadWrite*>::const_iterator rw = static_cast<IEnumerable<IReadWrite*>*>( info->GetValue( obj ).begin() ); rw != static_cast<IEnumerable<IReadWrite*>*>(info->GetValue(obj).end()); ++rw )
							{
								// Get a new unique name for this object.
								std::wstring item_name = GetObjName();

								// Get the string that constructs this object.
								std::wstring construct = _T( "" );
								if ( dynamic_cast<ViewReadWrite*>( *rw ) != 0 )
									construct = ( static_cast<ViewReadWrite*>( *rw ) )->GetConstructorString();
								if ( construct == _T( "" ) )
									construct = std::wstring::Format( _T( "new {0}()" ), ( *rw )->GetType() );

								// Write the constructor.
								writer->WriteLine( WhiteSpace + std::wstring::Format( _T( "{0} {1} = {2};" ), ( *rw )->GetType(), item_name, construct ) );

								// Write the interior information of the object.
								( *rw )->WriteCode( item_name, writer );

								// Add the object to the list.
								writer->WriteLine( WhiteSpace + std::wstring::Format( _T( "{2}{0}.Add({1});" ), ( *info )->Name, item_name, _prefix ) );
								if ( !LastLineWasBlank )
									writer->WriteLine();
								LastLineWasBlank = true;
							}
							if ( !LastLineWasBlank )
								writer->WriteLine();
						}
					}
				}

				if ( line != _T( "" ) )
				{
					writer->WriteLine( WhiteSpace + std::wstring::Format( _T( "{2}{0} = {1};" ), ( *info )->Name, line, _prefix ) );
					LastLineWasBlank = false;
				}
			}
		}

		WriteRecursiveDepth--;
	}

	int Tools::GetObjId()
	{
		WriteObjId++;
		return WriteObjId;
	}

	std::wstring Tools::ObjName( int id )
	{
		return std::wstring::Format( _T( "__{0}" ), id );
	}

	std::wstring Tools::GetObjName()
	{
		return ObjName( GetObjId() );
	}

	std::unordered_map<std::wstring, int> Tools::GetLocations( std::vector<std::wstring> &Bits, ... )
	{
		std::shared_ptr<std::unordered_map<std::wstring, int> > dict = std::unordered_map<std::wstring, int>();
		for ( int i = 0; i < Bits.size(); i++ )
			if ( keywords->Contains( Bits[ i ] ) )
				dict->Add( Bits[ i ], i );
		return dict;
	}

	std::unordered_map<std::wstring, int> Tools::GetLocations( std::vector<std::wstring> &Bits, std::vector<std::wstring> &keywords )
	{
		std::shared_ptr<std::unordered_map<std::wstring, int> > dict = std::unordered_map<std::wstring, int>();
		for ( int i = 0; i < Bits.size(); i++ )
			if ( std::find( keywords.begin(), keywords.end(), Bits[ i ] ) != keywords.end() )
				dict->Add( Bits[ i ], i );
		return dict;
	}

	void Tools::ReadLineToObj( const std::shared_ptr<Object> &obj, std::vector<std::wstring> &Bits )
	{
		ReadLineToObj( obj, Bits[ 0 ], Bits );
	}

	void Tools::ReadLineToObj( std::shared_ptr<Object> &obj, const std::wstring &field, std::vector<std::wstring> &Bits )
	{
		// If field name has a period in it, resolve recursively.
		int period = field.find( _T( "." ) );
		if ( period > 0 )
		{
			std::shared_ptr<std::wstring> subfield = field.substr( period + 1 );
			field = field.substr( 0, period );

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			var subobject_field = obj->GetType()->GetField(field);
			if ( subobject_field == 0 )
			{
				Tools::Log( std::wstring::Format( _T( "Field {0} not found." ), field ) );
				return;
			}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			var subobject = subobject_field->GetValue( obj );
			if ( subobject == 0 )
			{
				Tools::Log( std::wstring::Format( _T( "Subfield {0} was a null object and could not be written into." ), field ) );
				return;
			}

			ReadLineToObj( subobject, subfield, Bits );
		}
		// otherwise parse the input into the given field.
		else
		{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			var fieldinfo = obj->GetType()->GetField(field);
			if ( fieldinfo == 0 )
			{
				Tools::Log( std::wstring::Format( _T( "Field {0} not found." ), field ) );
				return;
			}


			// int
			if ( fieldinfo->FieldType == int::typeid )
				fieldinfo->SetValue( obj, int::Parse( Bits[ 1 ] ) );
			// float
			if ( fieldinfo->FieldType == float::typeid )
				fieldinfo->SetValue( obj, float::Parse( Bits[ 1 ] ) );
			// Vector2
			else if ( fieldinfo->FieldType == Vector2::typeid )
				fieldinfo->SetValue( obj, ParseToVector2( Bits[ 1 ], Bits[ 2 ] ) );
			// Vector4
			else if ( fieldinfo->FieldType == Vector4::typeid )
				fieldinfo->SetValue( obj, ParseToVector4( Bits[ 1 ], Bits[ 2 ], Bits[ 3 ], Bits[ 4 ] ) );
			// Color
			else if ( fieldinfo->FieldType == Color::typeid )
				fieldinfo->SetValue( obj, ParseToColor( Bits[ 1 ], Bits[ 2 ], Bits[ 3 ], Bits[ 4 ] ) );
			// bool
			else if ( fieldinfo->FieldType == bool::typeid )
				fieldinfo->SetValue( obj, bool::Parse( Bits[ 1 ] ) );
			// EzTexture
			else if ( fieldinfo->FieldType == EzTexture::typeid )
				fieldinfo->SetValue( obj, Tools::TextureWad->FindByName( Bits[ 1 ] ) );
			// EzEffect
			else if ( fieldinfo->FieldType == EzEffect::typeid )
				fieldinfo->SetValue( obj, Tools::EffectWad->FindByName( Bits[ 1 ] ) );
			// TextureOrAnim
			else if ( fieldinfo->FieldType == TextureOrAnim::typeid )
				fieldinfo->SetValue( obj, Tools::TextureWad->FindTextureOrAnim( Bits[ 1 ] ) );
			// string
			else if ( fieldinfo->FieldType == std::wstring::typeid )
				if ( Bits.size() == 1 )
					fieldinfo->SetValue( obj, _T( "" ) );
				else
					fieldinfo->SetValue( obj, Bits[ 1 ] );
			// PhsxData
			else if ( fieldinfo->FieldType == PhsxData::typeid )
				fieldinfo->SetValue( obj, Tools::ParseToPhsxData( Bits[ 1 ], Bits[ 2 ], Bits[ 3 ], Bits[ 4 ], Bits[ 5 ], Bits[ 6 ] ) );
			// BasePoint
			else if ( fieldinfo->FieldType == BasePoint::typeid )
				fieldinfo->SetValue( obj, Tools::ParseToBasePoint( Bits[ 1 ], Bits[ 2 ], Bits[ 3 ], Bits[ 4 ], Bits[ 5 ], Bits[ 6 ] ) );
			// MyOwnVertexFormat
			else if ( fieldinfo->FieldType == MyOwnVertexFormat::typeid )
				fieldinfo->SetValue( obj, Tools::ParseToMyOwnVertexFormat( Bits[ 1 ], Bits[ 2 ], Bits[ 3 ], Bits[ 4 ], Bits[ 5 ], Bits[ 6 ], Bits[ 7 ], Bits[ 8 ] ) );
		}
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
		int CommentIndex = str.find( _T( "//" ) );
		if ( CommentIndex >= 0 )
			str = str.substr( 0, CommentIndex );
		return str;
	}

	std::wstring Tools::RemoveComment_DashStyle( const std::wstring &str )
	{
		int CommentIndex = str.find( _T( "--" ) );
		if ( CommentIndex >= 0 )
			str = str.substr( 0, CommentIndex );
		return str;
	}

	Microsoft::Xna::Framework::Vector2 Tools::ParseToVector2( const std::wstring &bit1, const std::wstring &bit2 )
	{
		Vector2 Vec = Vector2::Zero;

		Vec.X = float::Parse( bit1 );
		Vec.Y = float::Parse( bit2 );

		return Vec;
	}

	Microsoft::Xna::Framework::Vector4 Tools::ParseToVector4( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4 )
	{
		Vector4 Vec = Vector4::Zero;

		Vec.X = float::Parse( bit1 );
		Vec.Y = float::Parse( bit2 );
		Vec.Z = float::Parse( bit3 );
		Vec.W = float::Parse( bit4 );

		return Vec;
	}

	PhsxData Tools::ParseToPhsxData( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 )
	{
		PhsxData data = PhsxData();

		data.Position.X = float::Parse( bit1 );
		data.Position.Y = float::Parse( bit2 );
		data.Velocity.X = float::Parse( bit3 );
		data.Velocity.Y = float::Parse( bit4 );
		data.Acceleration.X = float::Parse( bit5 );
		data.Acceleration.Y = float::Parse( bit6 );

		return data;
	}

	BasePoint Tools::ParseToBasePoint( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 )
	{
		BasePoint b = BasePoint();

		b.e1.X = float::Parse( bit1 );
		b.e1.Y = float::Parse( bit2 );
		b.e2.X = float::Parse( bit3 );
		b.e2.Y = float::Parse( bit4 );
		b.Origin.X = float::Parse( bit5 );
		b.Origin.Y = float::Parse( bit6 );

		return b;
	}

	MyOwnVertexFormat Tools::ParseToMyOwnVertexFormat( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6, const std::wstring &bit7, const std::wstring &bit8 )
	{
		MyOwnVertexFormat b = MyOwnVertexFormat();

		b.xy.X = float::Parse( bit1 );
		b.xy.Y = float::Parse( bit2 );

		b.uv.X = float::Parse( bit3 );
		b.uv.Y = float::Parse( bit4 );

		b.Color.R = unsigned char::Parse( bit5 );
		b.Color.G = unsigned char::Parse( bit6 );
		b.Color.B = unsigned char::Parse( bit7 );
		b.Color.A = unsigned char::Parse( bit8 );

		return b;
	}

	Microsoft::Xna::Framework::Vector2 Tools::ParseToVector2( const std::wstring &str )
	{
		int CommaIndex = str.find( _T( "," ) );
		Vector2 Vec = Vector2();

		std::wstring Component1, Component2;
		Component1 = str.substr( 0, CommaIndex );
		Component2 = str.substr( CommaIndex + 1, str.length() - CommaIndex - 1 );
		Vec.X = float::Parse( Component1 );
		Vec.Y = float::Parse( Component2 );

		return Vec;
	}

	Microsoft::Xna::Framework::Color Tools::ParseToColor( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4 )
	{
		Color c = Color::White;

		c.R = unsigned char::Parse( bit1 );
		c.G = unsigned char::Parse( bit2 );
		c.B = unsigned char::Parse( bit3 );
		c.A = unsigned char::Parse( bit4 );

		return c;
	}

	Microsoft::Xna::Framework::Color Tools::ParseToColor( const std::wstring &str )
	{
		int CommaIndex = str.find( _T( "," ) );
		int CommaIndex2 = str.find( _T( "," ), CommaIndex + 1 );
		int CommaIndex3 = str.find( _T( "," ), CommaIndex2 + 1 );

		std::wstring Component1, Component2, Component3, Component4;
		Component1 = str.substr( 0, CommaIndex );
		Component2 = str.substr( CommaIndex + 1, CommaIndex2 - CommaIndex - 1 );
		Component3 = str.substr( CommaIndex2 + 1, CommaIndex3 - CommaIndex2 - 1 );
		Component4 = str.substr( CommaIndex3 + 1, str.length() - CommaIndex3 - 1 );

		Color clr = Color( unsigned char::Parse( Component1 ), unsigned char::Parse( Component2 ), unsigned char::Parse( Component3 ), unsigned char::Parse( Component4 ) );

		return clr;
	}

	std::shared_ptr<EzSound> Tools::ParseToEzSound( const std::wstring &str )
	{
		int LineIndex = str.find( _T( "|" ) );

		std::wstring Component1, Component2;
		Component1 = str.substr( 0, LineIndex );
		Component2 = str.substr( LineIndex + 1, str.length() - LineIndex - 1 );

		return NewSound( ParseToFileName( Component1 ), float::Parse( Component2 ) );
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

template<typename T>
	int Tools::Length()
	{
		return GetValues<T>()->Count();
	}

template<typename T>
	std::shared_ptr<IEnumerable<T> > Tools::GetValues()
	{
		return ( from x in T::typeid::GetFields( BindingFlags::Static | BindingFlags::Public ) select ( T )x::GetValue( 0 ) );
	}

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

	Microsoft::Xna::Framework::Vector2 Tools::ToScreenCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 ZoomMod )
	{
		Vector2 loc = Vector2::Zero;
		loc.X = ( pos.X - cam->Data.Position.X ) / cam->AspectRatio * cam->getZoom().X * ZoomMod.X;
		loc.Y = ( pos.Y - cam->Data.Position.Y ) * cam->getZoom().Y * ZoomMod.Y;

		loc.X *= cam->ScreenWidth / 2;
		loc.Y *= -cam->ScreenHeight / 2;

		loc.X += cam->ScreenWidth / 2;
		loc.Y += cam->ScreenHeight / 2;

		return loc;
	}

	Microsoft::Xna::Framework::Vector2 Tools::ToGUICoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam )
	{
		return ToWorldCoordinates( pos, cam, Vector2( .001f,.001f ) );
	}

	Microsoft::Xna::Framework::Vector2 Tools::ToGUICoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 zoom )
	{
		return ToWorldCoordinates( pos, cam, zoom );
	}

	Microsoft::Xna::Framework::Vector2 Tools::ToWorldCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam )
	{
		return ToWorldCoordinates( pos, cam, cam->getZoom() );
	}

	Microsoft::Xna::Framework::Vector2 Tools::ToWorldCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 zoom )
	{
		pos.X -= cam->ScreenWidth / 2;
		pos.Y -= cam->ScreenHeight / 2;

		pos.X /= cam->ScreenWidth / 2;
		pos.Y /= -cam->ScreenHeight / 2;

		pos.X = pos.X * cam->AspectRatio / zoom.X + cam->Data.Position.X;
		pos.Y = pos.Y / zoom.Y + cam->Data.Position.Y;

		return pos;
	}

int Tools::GUIDraws = 0;
float Tools::HoldIllumination = 0;

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
				PaintEffect_SpriteBatch->Parameters[ _T( "xTexture" ) ]->SetValue( Tools::TextureWad->FindByName( _T( "PaintSplotch" ) )->getTex() );
				//PaintEffect_SpriteBatch.Parameters["SceneTexture"].SetValue(Tools.TextureWad.FindByName("PaintSplotch").Tex); 
				Tools::Render->MySpriteBatch->Begin( SpriteSortMode::Immediate, BlendState::AlphaBlend, SamplerState::LinearClamp, DepthStencilState::None, RasterizerState::CullCounterClockwise, Tools::PaintEffect_SpriteBatch, Matrix::CreateScale( scale, scale, 1 ) );
			}
			else
				Tools::Render->MySpriteBatch->Begin( SpriteSortMode::Immediate, BlendState::AlphaBlend, SamplerState::LinearClamp, DepthStencilState::None, RasterizerState::CullCounterClockwise, 0, Matrix::CreateScale( scale, scale, 1 ) );

			Tools::Render->UsingSpriteBatch = true;
		}
	}

	void Tools::DrawText( Vector2 pos, const std::shared_ptr<Camera> &cam, const std::wstring &str, const std::shared_ptr<SpriteFont> &font )
	{
		Vector2 loc = ToScreenCoordinates( pos, cam, Vector2::One );

		Tools::Render->MySpriteBatch->DrawString( font, str, loc, Color::Azure, 0, Vector2::Zero, Vector2( .5f,.5f ), SpriteEffects::None, 0 );
	}

	void Tools::SetDefaultEffectParams( float AspectRatio )
	{
		for ( std::vector<EzEffect*>::const_iterator fx = EffectWad->EffectList.begin(); fx != EffectWad->EffectList.end(); ++fx )
		{
			( *fx )->xCameraAspect->SetValue( AspectRatio );
			( *fx )->effect->CurrentTechnique = ( *fx )->Simplest;
			( *fx )->t->SetValue( Tools::t );
			( *fx )->Illumination->SetValue( 1 );
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

		HslGreenEffect->effect->Parameters[ _T( "ColorMatrix" ) ]->SetValue( colorm );
		HslEffect->effect->Parameters[ _T( "ColorMatrix" ) ]->SetValue( colorm );

		//colorm = HsvTransform(1f, 1f, 30) * 
		//        new Matrix(.6f, .6f, .6f, 0,
		//                    0, 0, 0, 0,
		//                    0, 0, 0, 0,
		//                    0, 0, 0, 1);
		//colorm = HsvTransform(.7f, 1f, 160);
		//colorm = HsvTransform(Num_0_to_2, 1f, Num_0_to_360);
		//colorm = HsvTransform(1f, 1f, 200);
	}

float Tools::Num_0_to_360 = 0;
float Tools::Num_0_to_2 = 0;
bool Tools::ShowNums = false;

	void Tools::ModNums()
	{
	#if defined(WINDOWS)
		if ( ButtonCheck::State( XnaInput::Keys::D1 ).Down )
			Num_0_to_360 = CoreMath::Restrict( 0, 360, Num_0_to_360 + .1f * Tools::DeltaMouse.X );
		if ( ButtonCheck::State( XnaInput::Keys::D2 ).Down )
			Num_0_to_2 = CoreMath::Restrict( 0, 2, Num_0_to_2 + .001f * Tools::DeltaMouse.X );

		if ( ButtonCheck::State( XnaInput::Keys::D1 ).Down || ButtonCheck::State( XnaInput::Keys::D2 ).Down )
			ShowNums = true;
	#endif
	}

bool Tools::DebugConvenience = false;

	void Tools::SetVibration( PlayerIndex Index, float LeftMotor, float RightMotor, int Duration )
	{
		if ( DebugConvenience )
			return;

		VibrateTimes[ static_cast<int>( Index ) ] = Duration;
		XnaInput::GamePad::SetVibration( Index, LeftMotor, RightMotor );
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
		for ( int i = 0; i < v.size(); i++ )
			vec[ i ] = Vector2( 0, v[ i ] );
		return vec;
	}

	bool Tools::IncrementsContainsSum( std::vector<int> Incr, int S )
	{
		int Sum = 0;
		for ( int i = 0; i < Incr.size(); i++ )
		{
			Sum += Incr[ i ];
			if ( Sum == S )
				return true;
		}

		return false;
	}

	void Tools::UseInvariantCulture()
	{
		Thread::CurrentThread->CurrentCulture = System::Globalization::CultureInfo::InvariantCulture;
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
		float TR_Bound = obj->TR_Bound()->X;
		if ( TR_Bound > TR.X )
			obj->MoveToBounded( Vector2( TR.X - TR_Bound, 0 ) );
		else
		{
			float BL_Bound = obj->BL_Bound()->X;
			if ( BL_Bound < BL.X )
				obj->MoveToBounded( Vector2( BL.X - BL_Bound, 0 ) );
		}
	}

	void Tools::EnsureBounds_Y( const std::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL )
	{
		float TR_Bound = obj->TR_Bound()->Y;
		if ( TR_Bound > TR.Y )
			obj->MoveToBounded( Vector2( 0, TR.Y - TR_Bound ) );
		else
		{
			float BL_Bound = obj->BL_Bound()->Y;
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
