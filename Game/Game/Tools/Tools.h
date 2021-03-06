#ifndef TOOLS
#define TOOLS

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/ResolutionGroup.h"
//#include "Core/Effects/EzEffect.h"
//#include "Core/Effects/EzEffectWad.h"
//#include "Core/Graphics/MainRender.h"
//#include "Core/Graphics/QuadDrawer.h"
//#include "Core/Graphics/VertexFormat.h"
//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Graphics/Draw/Simple/BasePoint.h"
//#include "Core/Graphics/Draw/Simple/SimpleObject.h"
//#include "Core/Tools/Set.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Song/EzSong.h"
//#include "Core/Song/EzSongWad.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Sound/EzSoundWad.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
//#include "Core/Texture/EzTextureWad.h"
//#include "Core/Texture/EzTexture.h"
//#include "Core/Texture/TextureOrAnim.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/CoreMath.h"
//#include "Core/Tools/Random.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Concrete Menus/Loading Screen/ILoadingScreen.h"
//#include "Game/Menus/Concrete Menus/Loading Screen/LoadingScreen.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/IBounded.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/WrappedFloat.h"


#include "stringconverter.h"
#include "Core/Chunk.h"
#include "Core/FancyVector2.h"
#include "Core/FancyColor.h"
#include "Core/PhsxData.h"
#include "Core/ResolutionGroup.h"
#include "Core/Version.h"
#include "Core/Graphics/Draw/Simple/SimpleVector.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "Core/WriteReadTools.h"
#include "Core/Graphics/Draw/Object/ObjectClass.h"
#include "Core/Animation/SpriteAnim.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Graphics/MainRender.h"
#include "Core/Graphics/QuadDrawer.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Object/ObjectBox.h"
#include "Core/Graphics/Draw/Quads/BaseQuad.h"
#include "Core/Graphics/Draw/Quads/ObjectVector.h"
#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Graphics/Draw/Quads/Quad.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Graphics/Draw/Simple/SimpleBox.h"
#include "Core/Graphics/Draw/Simple/SimpleObject.h"

#include <Input/MouseState.h>
#include <Input/GamePadState.h>
#include "Hacks/XNA/GameTime.h"
#include "Hacks/NET/StreamReader.h"
#include "Hacks/NET/StreamWriter.h"

#include <MainClass/XboxPC/CloudberryKingdom.XnaGameClass.h>

#include "Core/Lambdas/Lambda_1.h"
#include "Core/Lambdas/LambdaFunc_1.h"
#include "Core/Lambdas/LambdaFunc_2.h"

namespace CloudberryKingdom
{

	struct StringExtension
	{
	
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static string Capitalize(this string s)
		static std::wstring Capitalize( const std::wstring &s );
	};

	struct Vector2Extension
	{
	
		template<typename T>
		static int IndexMax( std::vector<T> list )
		{
			T max = list[ 0 ];
			int index = 0;
			for ( int i = 1; i < static_cast<int>( list.size() ); i++ )
				if ( list[ i ]->compare( max ) > 0 )
				{
					max = list[ i ];
					index = i;
				}

			return index;
		}

//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static string ToSimpleString(this Vector2 v)
		static std::wstring ToSimpleString( Vector2 v );



		/// <summary>
		/// Whether the vector is less than or equal to another vector in both components
		/// </summary>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static bool LE(this Vector2 v1, Vector2 v2)
		static bool LE( Vector2 v1, Vector2 v2 );
		/// <summary>
		/// Whether the vector is greater than or equal to another vector in both components
		/// </summary>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static bool GE(this Vector2 v1, Vector2 v2)
		static bool GE( Vector2 v1, Vector2 v2 );
	};

	struct ListExtension
	{
	
		/// <summary>
		/// Returns a single randomly chosen item from the list
		/// </summary>
		/*template<typename T>
		static T Choose( std::vector<T> list, const boost::shared_ptr<Rand> &rnd );*/

		/// <summary>
		/// Choose a random element from the list
		/// </summary>
		template<typename T>
		static T Choose( const std::vector<T> &list, const boost::shared_ptr<Rand> &rnd )
		{
			if ( rnd == 0 )
				return list[ 0 ];
			else
			//if (list == null || list.Count == 0) return null;
				return list[ rnd->RndInt( 0, list.size() - 1 ) ];
		}
	};

	struct DictionaryExtension
	{
	

		template<typename TKey, typename TValue>
		static void AddOrOverwrite( std::map<TKey, TValue> &dict, TKey key, TValue value )
		{
			if ( dict.find( key ) != dict.end() )
				dict[ key ] = value;
			else
				dict.insert( std::make_pair( key, value ) );
		}

	};

	struct Tools
	{

		struct PlayHappyProxy : public Lambda
		{

			void Apply();

		};

	
		static void InitializeStatics();

	
		struct RemoveBitsLambda : public LambdaFunc_1<std::wstring, bool>
		{

		
			RemoveBitsLambda();

			bool Apply( const std::wstring &bit );

		};

	
		static void Assert( bool MustBeTrue );

		static void Log( const std::wstring &dump );


		static void Nothing();
		static void Warning();

		static void LevelIsFinished();

		static void Break();
		static void Write( const boost::shared_ptr<Object> &obj );
		static void Write( const wchar_t *str, ... );

		static std::wstring DefaultObjectDirectory();
		static std::wstring DefaultDynamicDirectory();

		static std::wstring SourceTextureDirectory();

		static boost::shared_ptr<AftermathData> CurrentAftermath;

		static bool IsMasochistic;

		// Test variables for automatically creating levels
		static bool AutoLoop;
		static int AutoLoopDelay;

		template<typename T>
		static void Swap( T &a, T &b )
		{
			T temp = a;
			a = b;
			b = temp;
		}

		template<typename TSource>
		static TSource Find( std::vector<TSource> &list, const boost::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
		{
			for ( typename std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
				if ( predicate->Apply( *obj ) )
					return ( *obj );
			return TSource();
		}

		template<typename TSource>
		static std::vector<TSource> FindAll( std::vector<TSource> &list, const boost::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
		{
			std::vector<TSource> newlist = std::vector<TSource>();
			for ( typename std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
				if ( predicate->Apply( *obj ) )
					newlist.push_back( *obj );
			return newlist;
		}

		template<typename TSource>
		static bool All( std::vector<TSource> &list, const boost::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
		{
			bool all = true;
			for ( typename std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
				if ( !predicate->Apply( *obj ) )
					all = false;
			return all;
		}

		template<typename TSource>
		static bool Any( const std::vector<TSource> &list, const boost::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
		{
			for ( typename std::vector<TSource>::const_iterator obj = list.begin(); obj != list.end(); ++obj )
				if ( predicate->Apply( *obj ) )
					return true;
			return false;
		}

		template<typename TSource>
		static void RemoveAll( std::vector<TSource> &list, const boost::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate )
		{
			int OpenSlot = 0;
			int i = 0;
			int N = static_cast<int>( list.size() );

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

			// FIXME: Check if this is isomorphic.
			//list.RemoveRange( OpenSlot, N - OpenSlot );
			list.erase( list.begin() + OpenSlot, list.end() );
		}

		template<typename TSource>
		static void RemoveAll( std::vector<TSource> &source, const boost::shared_ptr<LambdaFunc_2<TSource, int, bool> > &predicate )
		{
			int i = 0;
			int j = 0;
			int N = static_cast<int>( source.size() );
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
		static TSource ArgMin( const std::vector<TSource> &source, const boost::shared_ptr<LambdaFunc_1<TSource, float> > &val )
		{
			TSource min = TSource();
			float minval = 0;
			for ( typename std::vector<TSource>::const_iterator item = source.begin(); item != source.end(); ++item )
				if ( min == 0 || val->Apply( *item ) < minval )
				{
					minval = val->Apply( *item );
					min = *item;
				}

			return min;
		}

		template<typename TSource>
		static TSource ArgMax( const std::vector<TSource> &source, const boost::shared_ptr<LambdaFunc_1<TSource, float> > &val )
		{
			TSource max = TSource();
			float maxval = 0;
			for ( typename std::vector<TSource>::const_iterator item = source.begin(); item != source.end(); ++item )
				if ( max == 0 || val->Apply( *item ) > maxval )
				{
					maxval = val->Apply( *item );
					max = *item;
				}

			return max;
		}

		static boost::shared_ptr<SimpleObject> LoadSimpleObject( const std::wstring &file );

	
		static float _VolumeFade;
	
		const static float &getVolumeFade();
		static void setVolumeFade( const float &value );

		static float CurSongVolume;
		static boost::shared_ptr<WrappedFloat> SoundVolume, MusicVolume;
		static bool FixedTimeStep;
		static bool WindowBorder;

		static boost::shared_ptr<XnaGameClass> GameClass;

		static boost::shared_ptr<CloudberryKingdomGame> TheGame;
		const static Version &getGameVersion();
		static void AddToDo( const boost::shared_ptr<Lambda> &todo );

		static std::vector<std::wstring> ButtonNames;
		static std::vector<std::wstring> DirNames;

		static boost::shared_ptr<GameFactory> CurGameType;
		static boost::shared_ptr<GameData> CurGameData;
		static boost::shared_ptr<Level> CurLevel;
		static boost::shared_ptr<Camera> DummyCamera;
		const static boost::shared_ptr<Camera> &getCurCamera();
		static boost::shared_ptr<GameData> WorldMap, TitleGame;

		static std::vector<int> VibrateTimes;

		static int DifficultyTypes; //Enum.GetValues(typeof(DifficultyType)).Length;
		static int StyleTypes;
		static int UpgradeTypes; //Enum.GetValues(typeof(Upgrade)).Length;

#if defined(WINDOWS)
		static KeyboardState Keyboard, PrevKeyboard;
		static MouseState Mouse, PrevMouse;
		static Vector2 DeltaMouse, RawDeltaMouse;
		static int DeltaScroll;
		static bool MouseInWindow;

		static Vector2 getMousePos();
		static void setMousePos( const Vector2 &value );

		static bool getFullscreen();
		static void setFullscreen( const bool &value );

		/// <summary>
		/// Whether the left mouse button is currently down.
		/// </summary>
		static bool CurMouseDown();

		/// <summary>
		/// Whether the left mouse button was down on the last frame.
		/// </summary>
		static bool PrevMouseDown();

		/// <summary>
		/// True when the left mouse button was pressed and released.
		/// </summary>
		static bool MouseReleased();

		/// <summary>
		/// True when the left mouse button isn't down currently and also wasn't down on the previous frame.
		/// </summary>
		static bool MouseNotDown();

		/// <summary>
		/// True when the left mouse button is down currently or was down on the previous frame.
		/// </summary>
		static bool MouseDown();

		/// <summary>
		/// True when the left mouse button is down currently and was NOT down on the previous frame.
		/// </summary>
		static bool MousePressed();

		/// <summary>
		/// Whether the left RightMouse button is currently down.
		/// </summary>
		static bool CurRightMouseDown();

		/// <summary>
		/// Whether the left RightMouse button was down on the last frame.
		/// </summary>
		static bool PrevRightMouseDown();

		/// <summary>
		/// True when the left RightMouse button was pressed and released.
		/// </summary>
		static bool RightMouseReleased();

		static Vector2 MouseGUIPos( Vector2 zoom );

		static Vector2 MouseWorldPos();

		static bool ShiftDown();

		static bool CntrlDown();

		static std::wstring RemoveAfter( const std::wstring &s, const std::wstring &occurence );
		static std::wstring SantitizeOneLineString( std::wstring s, const boost::shared_ptr<EzFont> &font );
#else
		static std::wstring SantitizeOneLineString( const std::wstring &s, const boost::shared_ptr<EzFont> &font );
#endif
		static std::vector<GamePadState> GamepadState;
		static std::vector<GamePadState> PrevGamepadState;

		/// <summary>
		/// Return just the file name of a path.
		/// </summary>
		static std::wstring StripPath( const std::wstring &file );

		/// <summary>
		/// Return just the first folder of the path.
		/// </summary>
		static std::wstring FirstFolder( std::wstring path, const std::wstring &ignore );

		static boost::shared_ptr<EzTexture> Texture( const std::wstring &name );
		static boost::shared_ptr<EzSound> Sound( const std::wstring &name );
		static void Pop();
		static void Pop( int Pitch );

		static boost::shared_ptr<GameTime> gameTime;

		static boost::shared_ptr<Rand> GlobalRnd;
		static boost::shared_ptr<EzEffectWad> EffectWad;
		static boost::shared_ptr<EzEffect> BasicEffect, NoTexture, CircleEffect, LightSourceEffect, HslEffect, HslGreenEffect, WindowEffect;
		static boost::shared_ptr<EzEffect> Text_NoOutline, Text_ThinOutline, Text_ThickOutline;
		static boost::shared_ptr<Effect> PaintEffect_SpriteBatch;
		static boost::shared_ptr<EzTextureWad> TextureWad;
		static boost::shared_ptr<ContentManager> SoundContentManager;
		static boost::shared_ptr<EzSoundWad> SoundWad, PrivateSoundWad;
		static boost::shared_ptr<EzSongWad> SongWad;
		static boost::shared_ptr<QuadDrawer> QDrawer;
		static boost::shared_ptr<MainRender> Render;
		static boost::shared_ptr<GraphicsDevice> Device;
		static boost::shared_ptr<RenderTarget2D> DestinationRenderTarget;

		static float t, dt;

		static int DrawCount, PhsxCount;

		static boost::shared_ptr<EzSong> Song_140mph, Song_Happy, Song_BlueChair, Song_Ripcurl, Song_Evidence, Song_GetaGrip, Song_House, Song_Nero, Song_FatInFire, Song_Heavens, Song_TidyUp, Song_WritersBlock;
		static std::vector<boost::shared_ptr<EzSong> > SongList_Standard;

		static bool FreeCam;
		static bool DrawBoxes;
		static bool DrawGraphics;
		static bool StepControl;
	
		static int _PhsxSpeed;
	
		const static int &getPhsxSpeed();
		static void setPhsxSpeed( const int &value );

		static bool ShowLoadingScreen;
		static boost::shared_ptr<ILoadingScreen> CurrentLoadingScreen;

		static void LoadBasicArt( const boost::shared_ptr<ContentManager> &Content );

		static std::wstring GetFileName( const std::wstring &FilePath );

		static std::wstring GetFileNamePlusExtension( const std::wstring &FilePath );

		static std::wstring GetFileBigName( const std::wstring &FilePath );

		static std::wstring GetFileName( const std::wstring &path, const std::wstring &FilePath );

		static std::wstring GetFileExt( const std::wstring &path, const std::wstring &FilePath );

		static std::vector<std::wstring> GetFiles( const std::wstring &path, bool IncludeSubdirectories );

		static void LoadEffects( const boost::shared_ptr<ContentManager> &Content, bool CreateNewWad );

		static float BoxSize( Vector2 TR, Vector2 BL );

		static float CurVolume;
		static void UpdateVolume();

		/// <summary>
		/// When true music will be stopped when a loading screen begins (The default behavior)
		/// </summary>
		static bool KillMusicOnLoadingScreen;

		/// <summary>
		/// When true the next loading screen will not stop the music.
		/// </summary>
		static bool DoNotKillMusicOnNextLoadingscreen;

		static void BeginLoadingScreen( bool KillMusic );

		static void PlayHappyMusic(boost::shared_ptr<GameData> game);
		static void PlayHappyMusic(boost::shared_ptr<GameData> game, int Delay);
		static void PlayHappyMusic();

		static void EndLoadingScreen();

		static void EndLoadingScreen_Immediate();

		/// <summary>
		/// Parses a string, stripping comments, and returning the sequence of bits it contains (separated strings).
		/// </summary>
		static std::vector<std::wstring> GetBitsFromLine( std::wstring line );



		static std::vector<std::wstring> GetBitsFromReader( const boost::shared_ptr<StreamReader> &reader );


		//static boost::shared_ptr<Object> ReadFields( const boost::shared_ptr<Object> &obj, const boost::shared_ptr<StreamReader> &reader );

	
		//static void ReadList( const boost::shared_ptr<StreamReader> &reader, const boost::shared_ptr<System::Collections::IList> &list, const boost::shared_ptr<Type> &itemType );
		static int WriteRecursiveDepth;
		static int WriteObjId;
	
//ORIGINAL LINE: public static void WriteFields(object obj, StreamWriter writer, params string[] VariableNames)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		//static void WriteFields( const boost::shared_ptr<Object> &obj, const boost::shared_ptr<StreamWriter> &writer, ... );

	
//ORIGINAL LINE: public static void WriteFieldsToCode(object obj, string prefix, StreamWriter writer, params string[] VariableNames)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static void WriteFieldsToCode( const boost::shared_ptr<Object> &obj, const std::wstring &prefix, const boost::shared_ptr<StreamWriter> &writer, ... );
	
		static int GetObjId();
		static std::wstring ObjName( int id );
		static std::wstring GetObjName();

	
//ORIGINAL LINE: public static Dictionary<string, int> GetLocations(List<string> Bits, params string[] keywords)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		//static std::map<std::wstring, int> GetLocations( std::vector<std::wstring> &Bits, ... );
		static std::map<std::wstring, int> GetLocations( std::vector<std::wstring> &Bits, std::vector<std::wstring> &keywords );

		/*static void ReadLineToObj( boost::shared_ptr<Object> &obj, std::vector<std::wstring> &Bits );
		static void ReadLineToObj( boost::shared_ptr<Object> &obj, std::wstring field, std::vector<std::wstring> &Bits );*/

		static bool BitsHasBit( std::vector<std::wstring> &Bits, const std::wstring &Bit );

		static std::wstring RemoveComment_SlashStyle( const std::wstring &str );

		static std::wstring RemoveComment_DashStyle( const std::wstring &str );

		static Vector2 ParseToVector2( const std::wstring &bit1, const std::wstring &bit2 );

		static Vector4 ParseToVector4( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4 );

		static PhsxData ParseToPhsxData( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 );

		static BasePoint ParseToBasePoint( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6 );

		static MyOwnVertexFormat ParseToMyOwnVertexFormat( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4, const std::wstring &bit5, const std::wstring &bit6, const std::wstring &bit7, const std::wstring &bit8 );

		static Vector2 ParseToVector2( const std::wstring &str );

		static Color ParseToColor( const std::wstring &bit1, const std::wstring &bit2, const std::wstring &bit3, const std::wstring &bit4 );

		static Color ParseToColor( const std::wstring &str );

		static boost::shared_ptr<EzSound> ParseToEzSound( const std::wstring &str );

		static boost::shared_ptr<EzSound> NewSound( const std::wstring &name, float volume );

		/// <summary>
		/// Returns the substring inside two quotations.
		/// </summary>
		/// <param name="str"></param>
		/// <returns></returns>
		static std::wstring ParseToFileName( const std::wstring &str );

		/// <summary>
		/// Returns the number of elements in an enumeration.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		/*template<typename T>
		static int Length();*/

		/*template<typename T>
		static boost::shared_ptr<IEnumerable<T> > GetValues();*/

		static unsigned char FloatToByte( float x );


		/// <summary>
		/// Increases the number of phsx steps taken per frame.
		/// </summary>
		static void IncrPhsxSpeed();

		/// <summary>
		/// Moves the object to the specified location. Uses IObject.Move
		/// </summary>
		/// <param name="obj"></param>
		/// <param name="pos"></param>
		static void MoveTo( const boost::shared_ptr<ObjectBase> &obj, Vector2 pos );

		/// <summary>
		/// Takes in world coordinates and returns screen coordinates.
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="cam"></param>
		/// <returns></returns>
		static Vector2 ToScreenCoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam, Vector2 ZoomMod );

		/// <summary>
		/// Takes in screen coordinates and returns world coordinates.
		/// (0,0) corresponds to the top left corner of the screen.
		/// </summary>
		static Vector2 ToGUICoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam );
		static Vector2 ToGUICoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam, Vector2 zoom );

		/// <summary>
		/// Takes in screen coordinates and returns world coordinates.
		/// (0,0) corresponds to the top left corner of the screen.
		/// </summary>
		static Vector2 ToWorldCoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam );
		static Vector2 ToWorldCoordinates( Vector2 pos, const boost::shared_ptr<Camera> &cam, Vector2 zoom );

		/// <summary>
		/// Incremented when StartGUIDraw is called.
		/// Decremented when EndGUIDraw is called.
		/// </summary>
	
		static int GUIDraws;

		static float HoldIllumination;
		/// <summary>
		/// Call before drawing GUI elements unaffected by the camera.
		/// </summary>
	
		static void StartGUIDraw();
		static void StartGUIDraw_Fake();

		/// <summary>
		/// Call after finishing drawing GUI elements unaffected by the camera.
		/// </summary>
		static void EndGUIDraw();
		static void EndGUIDraw_Fake();

		static void SetDefaultEffectParams( float AspectRatio );

		static float Num_0_to_360;
		static float Num_0_to_2;
		static bool ShowNums;

		static void ModNums();


		static bool DebugConvenience; // = true;

		/// <summary>
		/// Set a player's controller to vibrate.
		/// </summary>
		/// <param name="Index">The index of the player.</param>
		/// <param name="LeftMotor">The intensity of the left motor vibration (from 0.0 to 1.0)</param>
		/// <param name="RightMotor">The intensity of the left motor vibration (from 0.0 to 1.0)</param>
		/// <param name="Duration">The number of frames the vibration should persist.</param>
		static void SetVibration( PlayerIndex Index, float LeftMotor, float RightMotor, int Duration );

		static void UpdateVibrations();

		static std::vector<Vector2> FloatArrayToVectorArray_y( std::vector<float> v );

		static bool IncrementsContainsSum( std::vector<int> Incr, int S );

		static void UseInvariantCulture();

		static bool _AllTaken( std::vector<bool> list1, std::vector<bool> list2, int Length );

		static std::wstring ScoreString( int num, int outof );
		static std::wstring ScoreString( int num );

		/// <summary>
		/// Moves an IObject/IBound object to within BL.X and TR.X
		/// </summary>
		/// <param name="obj">The IObject to be moved. Must also be IBound</param>
		/// <param name="BL">BL extent of the bounded area</param>
		/// <param name="TR">TR extent of the bounded area</param>
		static void EnsureBounds_X( const boost::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL );
		/// <summary>
		/// Moves an IObject/IBound object to within BL.Y and TR.Y
		/// </summary>
		/// <param name="obj">The IObject to be moved. Must also be IBound</param>
		/// <param name="BL">BL extent of the bounded area</param>
		/// <param name="TR">TR extent of the bounded area</param>
		static void EnsureBounds_Y( const boost::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL );
		/// <summary>
		/// Moves an IObject/IBound object to within BL and TR
		/// </summary>
		/// <param name="obj">The IObject to be moved. Must also be IBound</param>
		/// <param name="BL">BL extent of the bounded area</param>
		/// <param name="TR">TR extent of the bounded area</param>
		static void EnsureBounds( const boost::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL );
	};
}


#endif	//#ifndef TOOLS
