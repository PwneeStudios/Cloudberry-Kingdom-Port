#ifndef TOOLS
#define TOOLS

#include <global_header.h>

namespace CloudberryKingdom
{
	class StringExtension
	{
	public:
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static string Capitalize(this string s)
		static std::wstring Capitalize( const std::wstring &s );
	};

	class Vector2Extension
	{
	public:
//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
		template<typename T>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static int IndexMax<T>(this T[] list) where T : IComparable
		static int IndexMax( std::vector<T> list );

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

	/// <summary>
	/// This extension to the StringBuilder class allows garbage free concatenation
	/// of string representations of integers.
	/// </summary>
	class StringBuilderExtension
	{
		/// <summary>
		/// The maximum number of digits an integer can be
		/// </summary>
	private:
		static const int max_digits = 15;

		/// <summary>
		/// A working array to store digits of an integer
		/// </summary>
		static std::vector<long long> digits;

		/// <summary>
		/// Clear the working array to allow for a new number to be constructed
		/// </summary>
		static void ClearDigits();

		/// <summary>
		/// Returns the index of the last digit of the number being constructed
		/// </summary>
		/// <returns></returns>
		static int LastDigit();

		/// <summary>
		/// The characters associated with each possible digit
		/// </summary>
		static std::vector<wchar_t> digit_char;

		/// <summary>
		/// Takes the digits from a number (already stored in a work array)
		/// and adds them to a StringBuilder
		/// </summary>
		static void DigitsToString( const std::shared_ptr<StringBuilder> &str, int NumDigits );

		/// <summary>
		/// Add a string representation of a number to a StringBuilder
		/// </summary>
	public:
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void Add(this StringBuilder str, Int64 num)
		static void Add( const std::shared_ptr<StringBuilder> &str, long long num );
		/// <summary>
		/// Add a string representation of a number to a StringBuilder
		/// </summary>
		/// <param name="MinDigits">The minimum number of digits used in the string.
		/// The string is padded with zeros to the left if needed.</param>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void Add(this StringBuilder str, Int64 num, int MinDigits)
		static void Add( const std::shared_ptr<StringBuilder> &str, long long num, int MinDigits );
	};

	class ListExtension
	{
	public:
		/// <summary>
		/// Returns a single randomly chosen item from the list
		/// </summary>
		template<typename T>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static T Choose<T>(this T[] list, Rand rnd)
		static T Choose( std::vector<T> list, const std::shared_ptr<Rand> &rnd );

		/// <summary>
		/// Choose a random element from the list
		/// </summary>
		template<typename T>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static T Choose<T>(this List<T> list, Rand rnd)
		static T Choose( std::vector<T> &list, const std::shared_ptr<Rand> &rnd );

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
		template<typename T, typename S>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void AddRangeAndConvert<T, S>(this List<T> list, List<S> range) where T : class where S : class
		static void AddRangeAndConvert( std::vector<T> &list, std::vector<S> &range );
	};

	class DictionaryExtension
	{
	public:

		template<typename TKey, typename TValue>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void AddOrOverwrite<TKey, TValue>(this Dictionary<TKey, TValue> dict, TKey key, TValue value)
		static void AddOrOverwrite( std::map<TKey, TValue> &dict, TKey key, TValue value );
	};

	class Tools
	{
	private:
		class RemoveBitsLambda : public LambdaFunc_1<std::wstring, bool>
		{
		public:
			RemoveBitsLambda();

			bool Apply( const std::wstring &bit );
		};

	public:
		static void Assert( bool MustBeTrue );

		static void Log( const std::wstring &dump );


		static void Nothing();
		static void Warning();

		static void LevelIsFinished();

static void Break();
static void Write( const std::shared_ptr<Object> &obj );
//ORIGINAL LINE: public static void Write(string str, params object[] objs)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
static void Write( const std::wstring &str, ... );

static std::wstring DefaultObjectDirectory();
static std::wstring DefaultDynamicDirectory();

static std::wstring SourceTextureDirectory();

		static std::shared_ptr<AftermathData> CurrentAftermath;

		static bool IsMasochistic;

		// Test variables for automatically creating levels
		static bool AutoLoop;
		static int AutoLoopDelay;

		template<typename T>
		static void Swap( std::shared_ptr<T> &a, std::shared_ptr<T> &b );

		template<typename TSource>
		static TSource Find( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate );

		template<typename TSource>
		static std::vector<TSource> FindAll( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate );

		template<typename TSource>
		static bool All( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate );

		template<typename TSource>
		static bool Any( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate );

		template<typename TSource>
		static void RemoveAll( std::vector<TSource> &list, const std::shared_ptr<LambdaFunc_1<TSource, bool> > &predicate );
		template<typename TSource>
		static void RemoveAll( std::vector<TSource> &source, const std::shared_ptr<LambdaFunc_2<TSource, int, bool> > &predicate );
		/// <summary>
		/// Return the smallest element.
		/// </summary>
		template<typename TSource>
		static TSource ArgMin( const std::vector<TSource> &source, const std::shared_ptr<LambdaFunc_1<TSource, float> > &val );
		/// <summary>
		/// Return the largest element.
		/// </summary>
		template<typename TSource>
		static TSource ArgMax( const std::vector<TSource> &source, const std::shared_ptr<LambdaFunc_1<TSource, float> > &val );

		static std::shared_ptr<SimpleObject> LoadSimpleObject( const std::wstring &file );

	private:
		static float _VolumeFade;
	public:
		const static float &getVolumeFade();
		static void setVolumeFade( const float &value );

		static float CurSongVolume;
		static std::shared_ptr<WrappedFloat> SoundVolume, MusicVolume;
		static bool FixedTimeStep;
		static bool WindowBorder;

		static std::shared_ptr<XnaGameClass> GameClass;

		static std::shared_ptr<CloudberryKingdomGame> TheGame;
		const static Version &getGameVersion();
		static void AddToDo( const std::shared_ptr<Lambda> &todo );

		static std::vector<std::wstring> ButtonNames;
		static std::vector<std::wstring> DirNames;

		static std::shared_ptr<GameFactory> CurGameType;
		static std::shared_ptr<GameData> CurGameData;
		static std::shared_ptr<Level> CurLevel;
		static std::shared_ptr<Camera> DummyCamera;
		const static std::shared_ptr<Camera> &getCurCamera();
		static std::shared_ptr<GameData> WorldMap, TitleGame;

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

		const static Vector2 &getMousePos();
		static void setMousePos( const Vector2 &value );

		const static bool &getFullscreen();
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
		static std::wstring SantitizeOneLineString( const std::wstring &s, const std::shared_ptr<EzFont> &font );
#else
		static std::wstring SantitizeOneLineString( const std::wstring &s, const std::shared_ptr<EzFont> &font );
#endif
		static std::vector<GamePadState> GamepadState, *PrevGamepadState;

		/// <summary>
		/// Return just the file name of a path.
		/// </summary>
		static std::wstring StripPath( const std::wstring &file );

		/// <summary>
		/// Return just the first folder of the path.
		/// </summary>
		static std::wstring FirstFolder( const std::wstring &path, const std::wstring &ignore );

		static std::shared_ptr<EzTexture> Texture( const std::wstring &name );
		static std::shared_ptr<EzSound> Sound( const std::wstring &name );
		static void Pop();
		static void Pop( int Pitch );

		static std::shared_ptr<GameTime> gameTime;

		static std::shared_ptr<Rand> GlobalRnd;
		static std::shared_ptr<EzEffectWad> EffectWad;
		static std::shared_ptr<EzEffect> BasicEffect, NoTexture, CircleEffect, LightSourceEffect, HslEffect, HslGreenEffect, WindowEffect;
		static std::shared_ptr<Effect> PaintEffect_SpriteBatch;
		static std::shared_ptr<EzTextureWad> TextureWad;
		static std::shared_ptr<ContentManager> SoundContentManager;
		static std::shared_ptr<EzSoundWad> SoundWad, PrivateSoundWad;
		static std::shared_ptr<EzSongWad> SongWad;
		static std::shared_ptr<QuadDrawer> QDrawer;
		static std::shared_ptr<MainRender> Render;
		static std::shared_ptr<GraphicsDevice> Device;
		static std::shared_ptr<RenderTarget2D> DestinationRenderTarget;

		static float t, dt;

		static int DrawCount, PhsxCount;

		static std::shared_ptr<EzSong> Song_140mph, Song_Happy, Song_BlueChair, Song_Ripcurl, Song_Evidence, Song_GetaGrip, Song_House, Song_Nero, Song_FatInFire, Song_Heavens, Song_TidyUp, Song_WritersBlock;
		static std::vector<EzSong*> SongList_Standard;

		static bool FreeCam;
		static bool DrawBoxes;
		static bool DrawGraphics;
		static bool StepControl;
	private:
		static int _PhsxSpeed;
	public:
		const static int &getPhsxSpeed();
		static void setPhsxSpeed( const int &value );

		static bool ShowLoadingScreen;
		static std::shared_ptr<ILoadingScreen> CurrentLoadingScreen;

		static void LoadBasicArt( const std::shared_ptr<ContentManager> &Content );

		static std::wstring GetFileName( const std::wstring &FilePath );

		static std::wstring GetFileNamePlusExtension( const std::wstring &FilePath );

		static std::wstring GetFileBigName( const std::wstring &FilePath );

		static std::wstring GetFileName( const std::wstring &path, const std::wstring &FilePath );

		static std::wstring GetFileExt( const std::wstring &path, const std::wstring &FilePath );

		static std::vector<std::wstring> GetFiles( const std::wstring &path, bool IncludeSubdirectories );

		static void LoadEffects( const std::shared_ptr<ContentManager> &Content, bool CreateNewWad );

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

		static void PlayHappyMusic();

		static void EndLoadingScreen();

		static void EndLoadingScreen_Immediate();

		/// <summary>
		/// Parses a string, stripping comments, and returning the sequence of bits it contains (separated strings).
		/// </summary>
		static std::vector<std::wstring> GetBitsFromLine( const std::wstring &line );



		static std::vector<std::wstring> GetBitsFromReader( const std::shared_ptr<StreamReader> &reader );


		//static std::shared_ptr<Object> ReadFields( const std::shared_ptr<Object> &obj, const std::shared_ptr<StreamReader> &reader );

	private:
		//static void ReadList( const std::shared_ptr<StreamReader> &reader, const std::shared_ptr<System::Collections::IList> &list, const std::shared_ptr<Type> &itemType );
		static int WriteRecursiveDepth;
		static int WriteObjId;
	public:
//ORIGINAL LINE: public static void WriteFields(object obj, StreamWriter writer, params string[] VariableNames)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		//static void WriteFields( const std::shared_ptr<Object> &obj, const std::shared_ptr<StreamWriter> &writer, ... );

	private:
		static void ResetWrite();

	public:
		static void WriteCode( const std::wstring &root, const std::shared_ptr<IReadWrite> &rw );

		static std::wstring ToCode( Vector2 v );

		static std::wstring ToCode( const std::wstring &s );

	private:
		static bool LastLineWasBlank;
	public:
//ORIGINAL LINE: public static void WriteFieldsToCode(object obj, string prefix, StreamWriter writer, params string[] VariableNames)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static void WriteFieldsToCode( const std::shared_ptr<Object> &obj, const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer, ... );
	private:
		static int GetObjId();
		static std::wstring ObjName( int id );
		static std::wstring GetObjName();

	public:
//ORIGINAL LINE: public static Dictionary<string, int> GetLocations(List<string> Bits, params string[] keywords)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		static std::map<std::wstring, int> GetLocations( std::vector<std::wstring> &Bits, ... );
		static std::map<std::wstring, int> GetLocations( std::vector<std::wstring> &Bits, std::vector<std::wstring> &keywords );

		static void ReadLineToObj( const std::shared_ptr<Object> &obj, std::vector<std::wstring> &Bits );
		static void ReadLineToObj( std::shared_ptr<Object> &obj, const std::wstring &field, std::vector<std::wstring> &Bits );

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

		static std::shared_ptr<EzSound> ParseToEzSound( const std::wstring &str );

		static std::shared_ptr<EzSound> NewSound( const std::wstring &name, float volume );

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
		static std::shared_ptr<IEnumerable<T> > GetValues();*/

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
		static void MoveTo( const std::shared_ptr<ObjectBase> &obj, Vector2 pos );

		/// <summary>
		/// Takes in world coordinates and returns screen coordinates.
		/// </summary>
		/// <param name="pos"></param>
		/// <param name="cam"></param>
		/// <returns></returns>
		static Vector2 ToScreenCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 ZoomMod );

		/// <summary>
		/// Takes in screen coordinates and returns world coordinates.
		/// (0,0) corresponds to the top left corner of the screen.
		/// </summary>
		static Vector2 ToGUICoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam );
		static Vector2 ToGUICoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 zoom );

		/// <summary>
		/// Takes in screen coordinates and returns world coordinates.
		/// (0,0) corresponds to the top left corner of the screen.
		/// </summary>
		static Vector2 ToWorldCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam );
		static Vector2 ToWorldCoordinates( Vector2 pos, const std::shared_ptr<Camera> &cam, Vector2 zoom );

		/// <summary>
		/// Incremented when StartGUIDraw is called.
		/// Decremented when EndGUIDraw is called.
		/// </summary>
	private:
		static int GUIDraws;

		static float HoldIllumination;
		/// <summary>
		/// Call before drawing GUI elements unaffected by the camera.
		/// </summary>
	public:
		static void StartGUIDraw();

		/// <summary>
		/// Call after finishing drawing GUI elements unaffected by the camera.
		/// </summary>
		static void EndGUIDraw();

		/// <summary>
		/// Starts the SpriteBatch if it isn't started already. The quad drawer is flushed first.
		/// </summary>
		static void StartSpriteBatch();
		static void StartSpriteBatch( bool AsPaint );

		/// <summary>
		/// Core wrapper for drawing text. Assumes SpriteBatch is started.
		/// </summary>
		static void DrawText( Vector2 pos, const std::shared_ptr<Camera> &cam, const std::wstring &str, const std::shared_ptr<SpriteFont> &font );

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
		static void EnsureBounds_X( const std::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL );
		/// <summary>
		/// Moves an IObject/IBound object to within BL.Y and TR.Y
		/// </summary>
		/// <param name="obj">The IObject to be moved. Must also be IBound</param>
		/// <param name="BL">BL extent of the bounded area</param>
		/// <param name="TR">TR extent of the bounded area</param>
		static void EnsureBounds_Y( const std::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL );
		/// <summary>
		/// Moves an IObject/IBound object to within BL and TR
		/// </summary>
		/// <param name="obj">The IObject to be moved. Must also be IBound</param>
		/// <param name="BL">BL extent of the bounded area</param>
		/// <param name="TR">TR extent of the bounded area</param>
		static void EnsureBounds( const std::shared_ptr<IBound> &obj, Vector2 TR, Vector2 BL );
	};
}


#endif	//#ifndef TOOLS
