#ifndef CLOUDBERRYKINGDOM_CLOUDBERRYKINGDOMGAME
#define CLOUDBERRYKINGDOM_CLOUDBERRYKINGDOMGAME

#include <global_header.h>

#include "Hacks/XNA/GraphicsDevice.h"
#include "Hacks/XNA/GraphicsDeviceManager.h"
#include "Hacks/XNA/PreparingDeviceSettingsEventArgs.h"
#include "Hacks/XNA/GameTime.h"
#include "Hacks/NET/Stopwatch.h"
#include "Hacks/NET/StringBuilder.h"

namespace CloudberryKingdom
{

	struct CloudberryKingdomGame : public boost::enable_shared_from_this<CloudberryKingdomGame>
	{

	
		static void StaticIntializer_NoDependence();
		static void StaticIntializer_AfterResourcesLoad();

	
		struct ExitProxy : public Lambda
		{
		
			boost::shared_ptr<CloudberryKingdomGame> ckg;

		
			ExitProxy( const boost::shared_ptr<CloudberryKingdomGame> &ckg );

			void Apply();
		};

	
		struct UpdateVolumeProxy : public Lambda
		{
		
			void Apply();
		};

	
		struct MakeTestLevelInitializeHelper : public Lambda_1<boost::shared_ptr<PieceSeedData> >
		{
		
			boost::shared_ptr<CloudberryKingdomGame> ckg;

		
			MakeTestLevelInitializeHelper( const boost::shared_ptr<CloudberryKingdomGame> &ckg );

			void Apply( const boost::shared_ptr<PieceSeedData> &piece );
		};

	
		struct TestLevelPostMakeProxy : public Lambda_1<boost::shared_ptr<Level> >
		{
		
			boost::shared_ptr<CloudberryKingdomGame> ckg;
		
			TestLevelPostMakeProxy( const boost::shared_ptr<CloudberryKingdomGame> &ckg );

			void Apply( const boost::shared_ptr<Level> &level );
		};

		/// <summary>
		/// The version of the game we are working on now (+1 over the last version uploaded to Steam).
		/// MajorVersion is 0 for beta, 1 for release.
		/// MinorVersion increases with substantial change.
		/// SubVersion increases with any pushed change.
		/// </summary>
	
		static Version GameVersion;




        static bool GodMode;
        static bool ForFrapsRecording;;

        static bool AlwaysGiveTutorials;
        static bool Unlock_Customization;
        static bool Unlock_Levels;

        static bool getIsDemo();

        static void OfferToBuy(SignedInGamer gamer);










		/// <summary>
		/// The command line arguments.
		/// </summary>
		static std::vector<std::wstring> args;

		static bool StartAsBackgroundEditor;
		static bool StartAsTestLevel;
		static bool StartAsBobAnimationTest;
		static bool StartAsFreeplay;
#if defined(INCLUDE_EDITOR)
		static bool LoadDynamic;
#else
		static bool LoadDynamic;
#endif
		static bool ShowSongInfo;

		static std::wstring TileSetToTest;
		static std::wstring ModRoot;
		static bool AlwaysSkipDynamicArt;

		static bool HideGui;
		static bool HideForeground;
		static bool UseNewBob;

		//public static SimpleGameFactory TitleGameFactory = TitleGameData_Intense.Factory;
		static boost::shared_ptr<SimpleGameFactory> TitleGameFactory;
		//public static SimpleGameFactory TitleGameFactory = TitleGameData_Forest.Factory;

		static float fps;

		int DrawCount, PhsxCount;

		ResolutionGroup Resolution;
		std::vector<ResolutionGroup> Resolutions;

#if defined(WINDOWS)
		boost::shared_ptr<QuadClass> MousePointer, MouseBack;
	
		bool _DrawMouseBackIcon;
	
		const bool &getDrawMouseBackIcon() const;
		void setDrawMouseBackIcon( const bool &value );
#endif

		bool LogoScreenUp;

		/// <summary>
		/// When true the initial loading screen is drawn even after loading is finished
		/// </summary>
	
		bool LogoScreenPropUp;

		/// <summary>
		/// The game's initial loading screen. Different than the in-game loading screens seen before levels.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The variable LoadingScreen was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<InitialLoadingScreen> LoadingScreen_Renamed;

		boost::shared_ptr<GraphicsDevice> MyGraphicsDevice;
		boost::shared_ptr<GraphicsDeviceManager> MyGraphicsDeviceManager;

	
		int ScreenWidth, ScreenHeight;

		boost::shared_ptr<Camera> MainCamera;

//C# TO C++ CONVERTER TODO TASK: There is no direct equivalent to .NET events in native C++:
//		public event EventHandler<EventArgs> Exiting
//		{
//			add
//			{
//				Tools::GameClass.Exiting += value;
//			}
//			remove
//			{
//				Tools::GameClass.Exiting -= value;
//			}
//		}

	
		void Exit();

		/// <summary>
		/// Process the command line arguments.
		/// This is used to load different tools, such as the background editor, instead of the main game.
		/// </summary>
		/// <param name="args"></param>
		static void ProcessArgs( std::vector<std::wstring> &args );

		CloudberryKingdomGame();

	
		void graphics_PreparingDeviceSettings( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<PreparingDeviceSettingsEventArgs> &e );

	
		void Initialize();

		void InitialResolution();

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	
		void SignedInGamer_SignedOut( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedOutEventArgs> &e );

		void SignedInGamer_SignedIn( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<SignedInEventArgs> &e );
#endif

	
		void LoadContent();

	
		void UnloadContent();

	
		void DoQuickSpawn();

		/// <summary>
		/// The current game being played.
		/// </summary>
		const boost::shared_ptr<GameData> &getGame() const;

		/// <summary>
		/// Update the current game.
		/// </summary>
		void DoGameDataPhsx();

		/// <summary>
		/// A list of actions to perform. Each time an action is peformed it is removed from the list.
		/// </summary>
	
		boost::shared_ptr<Multicaster> ToDo;

	
		void DoToDoList();

		void GodModePhxs();

		void PhsxStep();

#if defined(WINDOWS)
	
		void CheckForQuickSpawn_PC();
#endif

		void CheckForQuickSpawn_Xbox();

#if defined(WINDOWS)
		/// <summary>
		/// Whether the mouse should be allowed to be shown, usually only when a menu is active.
		/// </summary>
	
		bool ShowMouse;

		/// <summary>
		/// Draw the mouse cursor.
		/// </summary>
	
		void MouseDraw();
#endif

		/// <summary>
		/// Whether a song was playing prior to the game window going inactive
		/// </summary>
	
		bool MediaPlaying_HoldState;

		/// <summary>
		/// Whether this is the first frame the window has been inactive
		/// </summary>
		bool FirstInactiveFrame;

		/// <summary>
		/// Whether this is the first frame the window has been active
		/// </summary>
		bool FirstActiveFrame;

		double DeltaT;

		void Update();

		/// <summary>
		/// The main draw loop.
		/// Sets all the rendering up and determines which sub-function to call (game, loading screen, nothing, etc).
		/// Also updates the game logic. TODO: Seperate this from the draw function?
		/// </summary>
		/// <param name="gameTime"></param>
		void Draw( const boost::shared_ptr<GameTime> &gameTime );

		/// <summary>
		/// Non-game drawing, such as debug info and tool drawing.
		/// </summary>
	
		void DrawExtra();

		/// <summary>
		/// Draws the load screen, assuming the game should not be drawn this frame.
		/// </summary>
		void DrawLoading();

		/// <summary>
		/// Draws nothing (black). Called when the game shouldn't be shown, nor anything else, such as load screens.
		/// </summary>
		void DrawNothing();

		/// <summary>
		/// Draws the actual the game, not any loading screens or other non-game graphics.
		/// </summary>
		void DrawGame();

		/// <summary>
		/// The update function called for the actual game, not for loading screens or other non-game functions.
		/// </summary>
		/// <param name="gameTime"></param>
		void GameUpdate( const boost::shared_ptr<GameTime> &gameTime );

		void UpdateFps( const boost::shared_ptr<GameTime> &gameTime );

		/// <summary>
		/// Sets up the renderer. Returns true if no additional drawing should be done, because the game does not have focus.
		/// </summary>
		/// <returns></returns>
		bool SetupToRender();

		/// <summary>
		/// Draw the fireball textures to memory.
		/// </summary>
		void ComputeFire();

#if defined(WINDOWS)
		/// <summary>
		/// Decide if the game should be active or not.
		/// </summary>
		/// <returns>Returns true if the game is active.</returns>
		bool ActiveInactive();
#endif


		void BenchmarkAll();

		static boost::shared_ptr<Stopwatch> stopwatch;
		static void Start();
		static long long Stop();

		static boost::shared_ptr<Stopwatch> stopwatch2;
		static void Start2();
		static long long Stop2();


		static void BenchmarkLoadSize();
		bool ShowFPS;

#if defined(DEBUG)
		/// <summary>
		/// Extra functions that allow a user to better debug/test/
		/// </summary>
		/// <returns>Return true if the calling method should return.</returns>
		bool DebugModePhsx();
#endif

	
		static std::wstring debugstring;
	
		boost::shared_ptr<StringBuilder> MainString;

		/// <summary>
		/// Method for drawing various debug information to the screen.
		/// </summary>
		void DrawDebugInfo();


		void MakeEmptyLevel();

		void MakeTestLevel();

		void TestLevelPostMake( const boost::shared_ptr<Level> &level );

		void TestLevelInit( const boost::shared_ptr<PieceSeedData> &piece );

		static void __Roughly_Maso( const boost::shared_ptr<PieceSeedData> &piece );

		static void __Roughly_Abusive( const boost::shared_ptr<PieceSeedData> &piece );

		void TestLevelModParams( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p );


		bool DoInnerLogoPhsx;
		void LogoPhsx();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_CLOUDBERRYKINGDOMGAME
