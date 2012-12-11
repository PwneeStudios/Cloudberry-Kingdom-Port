#ifndef CLOUDBERRYKINGDOM_LEVELSEEDDATA
#define CLOUDBERRYKINGDOM_LEVELSEEDDATA

#include <global_header.h>

namespace CloudberryKingdom
{

	struct LevelSeedData : public std::enable_shared_from_this<LevelSeedData>
	{

	
		struct _StartSongProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			std::shared_ptr<LevelSeedData> lsd;

		
			_StartSongProxy( const std::shared_ptr<LevelSeedData> &lsd );

			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct _HasWall_ProcessProxy : public Lambda_2<std::shared_ptr<Level>, std::shared_ptr<PieceSeedData> >
		{
		
			void Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &piece );
		};

	
		struct _SetWeather_ProcessProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct _NoStartDoorProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct _FadeIn_ProcessProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct EOL_StringWorldDoorEndAction_WithFadeProxy : public Lambda_1<std::shared_ptr<Door> >
		{
		
			std::shared_ptr<StringWorldGameData> gameData;

		
			EOL_StringWorldDoorEndAction_WithFadeProxy( const std::shared_ptr<StringWorldGameData> &gameData );

			void Apply( const std::shared_ptr<Door> &door );
		};

	
		struct _FadeOut_ProcessProxy : public Lambda_1<std::shared_ptr<Level> >
		{
		
			void Apply( const std::shared_ptr<Level> &level );
		};

	
		struct ModPieceViaStringProxy : public Lambda_1<std::shared_ptr<PieceSeedData> >
		{
		
			std::shared_ptr<LevelSeedData> lsd;

		
			ModPieceViaStringProxy( const std::shared_ptr<LevelSeedData> &lsd );

			void Apply( const std::shared_ptr<PieceSeedData> &piece );
		};

	
		struct ModPieceViaHashProxy : public Lambda_1<std::shared_ptr<PieceSeedData> >
		{
		
			std::shared_ptr<LevelSeedData> lsd;

		
			ModPieceViaHashProxy( const std::shared_ptr<LevelSeedData> &lsd );

			void Apply( const std::shared_ptr<PieceSeedData> &piece );
		};

	
		struct SetToStartSongHelper : public Lambda
		{
		
			std::shared_ptr<EzSong> song;

		
			SetToStartSongHelper( const std::shared_ptr<EzSong> &song );

			void Apply();
		};

	
		struct SetToStartSongPostMakeHelper : public Lambda_1<std::shared_ptr<Level> >
		{
		
			int delay;
			std::shared_ptr<Lambda> songHelper;

		
			SetToStartSongPostMakeHelper( int delay, const std::shared_ptr<Lambda> &songHelper );

			void Apply( const std::shared_ptr<Level> &lvl );
		};

	
		struct BOL_StartMusicProxy : public Lambda
		{
		
			void Apply();
		};

	
		struct ScoreScreenLambda : public LambdaFunc<std::shared_ptr<GameObject> >
		{
		
			StatGroup stats;
			std::shared_ptr<Level> level;

		
			ScoreScreenLambda( StatGroup stats, const std::shared_ptr<Level> &level );

			std::shared_ptr<GameObject> Apply();
		};

	
		struct EOL_DoorActionProxy : public Lambda_1<std::shared_ptr<Door> >
		{
		
			void Apply( const std::shared_ptr<Door> &door );
		};

	
		struct PostMake_StringWorldStandardHelper : public Lambda
		{
		
			void Apply();
		};

	
		enum LavaMakeTypes
		{
			LavaMakeTypes_ALWAYS_MAKE,
			LavaMakeTypes_NEVER_MAKE,
			LavaMakeTypes_RANDOM
		};
	
		struct StandardInitHelper : public Lambda_1<std::shared_ptr<PieceSeedData> >
		{
		
			std::shared_ptr<Lambda_2<std::shared_ptr<PieceSeedData>, std::shared_ptr<Upgrades> > > CustomDiff;

		
			StandardInitHelper( const std::shared_ptr<Lambda_2<std::shared_ptr<PieceSeedData>, std::shared_ptr<Upgrades> > > &CustomDiff );

			void Apply( const std::shared_ptr<PieceSeedData> &p );
		};

	
		struct InitNormalMyModParamsHelper : public Lambda_2<std::shared_ptr<Level>, std::shared_ptr<PieceSeedData> >
		{
		
			void Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p );
		};

	
		static bool NoDoublePaths;

		std::shared_ptr<Level> MakeLevel( const std::shared_ptr<GameData> &game );
		std::shared_ptr<Level> MakeLevel( bool MakeBackground, const std::shared_ptr<GameData> &game );

	
		void MakeTheBackground( const std::shared_ptr<Level> &NewLevel, float Height );

	
		static int ForcedReturnEarly;
	
		int SetReturnEarly( const std::shared_ptr<PieceSeedData> &Piece );


	
		bool Saveable;

		/// <summary>
		/// These special flags add additional properties to levels made by this seed.
		/// </summary>
		#pragma region Special flags
		bool HasWall;
	
		static const std::wstring WallFlag;
	
		bool FadeIn;
	
		static const std::wstring FadeInFlag;
	
		bool FadeOut;
	
		static const std::wstring FadeOutFlag;
	
		float WeatherIntensity;
	
		static const std::wstring WeatherIntensityFlag;
	
		bool NoStartDoor;
	
		static const std::wstring NoStartDoorFlag;
	
		int LevelNum;
	
		static const std::wstring LevelFlag;

		/// <summary>
		/// How long to wait before opening the initial door.
		/// </summary>
	
		int WaitLengthToOpenDoor;
	
		static const std::wstring WaitLengthToOpenDoorString;
	
		bool OpenDoorSound;
	
		static const std::wstring OpenDoorSoundFlag;

		/// <summary>
		/// Song to play when this level starts. Regular sound track will resume on completion.
		/// </summary>
	
		std::shared_ptr<EzSong> MySong;
	
		static const std::wstring SongString;

	
		void ProcessSpecial();

	
		void _StartSong( const std::shared_ptr<Level> &level );

		static void _HasWall_Process( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &piece );

		static void _SetWeather_Process( const std::shared_ptr<Level> &level );

		static void _NoStartDoor( const std::shared_ptr<Level> &level );

		static void _FadeIn_Process( const std::shared_ptr<Level> &level );

		static void _FadeOut_Process( const std::shared_ptr<Level> &level );
		#pragma endregion

		/// <summary>
		/// Set default parameters for this LevelSeedData assuming we are about to read in parameters from a string.
		/// </summary>
	
		void DefaultRead( const std::wstring &str );

		/// <summary>
		/// Read in parameters from a string.
		/// </summary>
		void ReadString( std::wstring str );

		virtual std::wstring ToString();

		/// <summary>
		/// While reading in parameters from a string, the portion of the string storing upgrade data is stored in this string.
		/// </summary>
	
		std::vector<std::wstring> UpgradeStrs;

		/// <summary>
		/// Modify a PieceSeedData to conform to the upgrade data stored in UpgradeStr.
		/// </summary>
		void ModPieceViaString( const std::shared_ptr<PieceSeedData> &piece );

		/// <summary>
		/// Modify a PieceSeedData to have random upgrades.
		/// </summary>
		void ModPieceViaHash( const std::shared_ptr<PieceSeedData> &piece );
		int PieceHash;

		/// <summary>
		/// Make a random hero.
		/// </summary>
		void RandomHero( const std::shared_ptr<BobPhsx> &Hero, int Hash );

	
		std::wstring SuggestedName();

		static std::wstring GetNameFromSeedStr( const std::wstring &seed );

		/// <summary>
		/// Called when the loading screen is created, just before the level creation algorithm starts.
		/// </summary>
		std::shared_ptr<Lambda> OnBeginLoad;

		/// <summary>
		/// When true the campaign manager does not add a default PostMake action to this seed.
		/// </summary>
		bool NoDefaultMake;

		/// <summary>
		/// When true this game will not start any music, or stop any previously playing music.
		/// </summary>
		bool NoMusicStart;

		/// <summary>
		/// The created level will loop the given song, starting once the level loads.
		/// </summary>
		void SetToStartSong( const std::shared_ptr<EzSong> &song );
		void SetToStartSong( const std::shared_ptr<EzSong> &song, int delay );

		std::wstring Name;

		std::shared_ptr<Multicaster_1<std::shared_ptr<Level> > > PostMake;

		/// <summary>
		/// Adds the default GameObjects to a level.
		/// </summary>
		static void AddGameObjects_Default( const std::shared_ptr<Level> &level, bool global, bool ShowMultiplier );

		/// <summary>
		/// Adds the bare bones GameObjects to a level. (Menu, Perfect)
		/// </summary>
		static void AddGameObjects_BareBones( const std::shared_ptr<Level> &level, bool global );

		/// <summary>
		/// Standard beginning of level music start.
		/// Shuffles and starts the standard playlist.
		/// </summary>
		static void BOL_StartMusic();

		/// <summary>
		/// Allow the user to load different levels from the menu within this level.
		/// </summary>
		void PostMake_EnableLoad( const std::shared_ptr<Level> &level );

		void PostMake_StandardLoad( const std::shared_ptr<Level> &level );

		static void PostMake_Standard( const std::shared_ptr<Level> &level, bool StartMusic, bool ShowMultiplier );

		static void PostMake_StringWorldStandard( const std::shared_ptr<Level> &level );

		bool ReleaseWhenLoaded;

		std::shared_ptr<LockableBool> Loaded;
		bool LoadingBegun;
		std::shared_ptr<GameData> MyGame;

		LevelGeometry MyGeometry;

		int PieceLength;

		std::shared_ptr<BobPhsx> DefaultHeroType;

		GameFlags MyGameFlags;

		LavaMakeTypes LavaMake;

		/// <summary>
		/// If true then seed used in the random number generator is never changed.
		/// The level will always be made the same way.
		/// </summary>
		bool LockedSeed;

		/// <summary>
		/// The seed fed into the random number generator.
		/// </summary>
		const int &getSeed() const;
		void setSeed( const int &value );
		std::shared_ptr<Rand> Rnd;

		std::shared_ptr<GameFactory> MyGameType;

		std::vector<std::shared_ptr<PieceSeedData> > PieceSeeds;

		std::shared_ptr<BackgroundTemplate> MyBackgroundType;
		std::shared_ptr<TileSet> MyTileSet;

		void SetTileSet( const std::wstring &name );

		void SetTileSet( const std::shared_ptr<TileSet> &tileset );

		/// <summary>
		/// Reset the seed so that it may be used again.
		/// </summary>
		void Reset();

		void Release();

		void ReleasePieces();

		LevelSeedData( const std::shared_ptr<LevelSeedData> &data );

		LevelSeedData();

	
		void BaseInit();

	
		int Difficulty, NumPieces, Length;
	
		std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > MyCustomDifficulty;
	
		void PreInitialize( const std::shared_ptr<GameFactory> &Type, int Difficulty, int NumPieces, int Length, const std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > &CustomDiff );

	
		bool Initialized;
	
		void Init();

		/// <summary>
		/// Prevent unreasonable or dangerous parameter combinations.
		/// </summary>
	
		void Sanitize();

	
		void StandardInit( const std::shared_ptr<Lambda_2<std::shared_ptr<PieceSeedData>, std::shared_ptr<Upgrades> > > &CustomDiff );
		void Initialize( const std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > &CustomDiff );
		void Initialize( const std::shared_ptr<GameFactory> &factory, LevelGeometry geometry, int NumPieces, int Length, const std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > &CustomDiff );

		float CalcPieceLength( const std::shared_ptr<PieceSeedData> &data );

		void InitNormal( bool Place, const std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > &CustomDiff );

		void InitPlace( const std::shared_ptr<Lambda_1<std::shared_ptr<PieceSeedData> > > &CustomDiff );

	
		std::shared_ptr<Level> MakeNewLevel( const std::shared_ptr<GameData> &game );

	
		std::shared_ptr<GameData> Create();
		std::shared_ptr<GameData> Create( bool MakeInBackground );

	
		void InitializeInstanceFields();

	};

}

#endif	//#ifndef CLOUDBERRYKINGDOM_LEVELSEEDDATA
