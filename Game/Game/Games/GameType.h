#ifndef GAMETYPE
#define GAMETYPE

#include <global_header.h>

#include "Game/Localization.h"
#include "Core/Lambdas/Lambda.h"
#include "Core/Lambdas/LambdaFunc.h"
#include "Core/Lambdas/LambdaFunc_1.h"
#include "Core/Lambdas/LambdaFunc_2.h"
#include "Core/Lambdas/Lambda_1.h"
#include "Core/Lambdas/Lambda_2.h"
#include "Core/Lambdas/Multicaster.h"
#include "Core/Lambdas/Multicaster_1.h"
#include "Core/Lambdas/Multicaster_2.h"

namespace CloudberryKingdom
{

	struct GameFlags
	{
		/// <summary>
		/// Whether the game has the players tethered
		/// </summary>
	
		bool IsTethered;

		/// <summary>
		/// Whether the game is a Doppleganger Game
		/// </summary>
		bool IsDoppleganger;

		/// <summary>
		/// Whether the Doppleganger Game is inverting the doppleganger
		/// </summary>
		bool IsDopplegangerInvert;

		GameFlags();

		void SetToDefault();
	};

	/// <summary>
	/// This is the main super-struct of the engine.
	/// Whenever a player is playing, they are in a 'Game'.
	/// A Game consists of at least one level (a Level struct instance),
	/// as well as some goal or purpose: getting to a door, collecting coins, surviving, or building a level, etc.
	/// The game struct holds the levels and purpose of the level.
	/// Different purposes are implemented as children classes of the main GameData struct.
	/// </summary>
	struct GameData : public boost::enable_shared_from_this<GameData>
	{

	
		static void InitializeStatics();

	
		struct AddScoreLambda : public Lambda
		{
		
			boost::shared_ptr<GameData> game;
			boost::shared_ptr<Door> door;

		
			AddScoreLambda( const boost::shared_ptr<GameData> &game, const boost::shared_ptr<Door> &door );

			void Apply();
		};

	
		struct FinishProxy : public Lambda_1<bool>
		{
		
			boost::shared_ptr<GameData> gt;

		
			FinishProxy( const boost::shared_ptr<GameData> &gt );

			void Apply( const bool &Replay );
		};

	
		struct PlayWorldMapMusicLambda : public Lambda
		{
		
			PlayWorldMapMusicLambda();

			void Apply();
		};

	
		struct PlayAgainLambda : public Lambda
		{
		
			boost::shared_ptr<GameData> parentgame;
		
			PlayAgainLambda( const boost::shared_ptr<GameData> &parentgame );

			void Apply();
		};

	
		struct ReleaseThisLambda : public Lambda
		{
		
			boost::shared_ptr<GameData> game;

		
			ReleaseThisLambda( const boost::shared_ptr<GameData> &game );

			void Apply();
		};

	
		struct WaitThenDoCoversion : public LambdaFunc<bool>
		{
		
			int WaitLength_, Count_;
			boost::shared_ptr<Lambda> f_;

		
			WaitThenDoCoversion( int WaitLength, const boost::shared_ptr<Lambda> &f );

			bool Apply();
		};

	
		struct WaitThenAddToToDoLambda : public Lambda
		{
		
			boost::shared_ptr<GameData> game;
			boost::shared_ptr<LambdaFunc<bool> > f;

		
			WaitThenAddToToDoLambda( const boost::shared_ptr<GameData> &game, const boost::shared_ptr<LambdaFunc<bool> > &f );

			void Apply();
		};

	
		struct FadeInAndDoAction : public Lambda
		{
		
			boost::shared_ptr<GameData> game;
			boost::shared_ptr<Lambda> OnBlack;
			float speed;
			float TargetOpaqueness;

		
			FadeInAndDoAction( const boost::shared_ptr<GameData> &game, const boost::shared_ptr<Lambda> &OnBlack, float speed, float TargetOpaqueness );

			void Apply();
		};

	
		struct SlideInLambda : public Lambda
		{
		
			boost::shared_ptr<StartMenu_MW_Black> black;

		
			SlideInLambda( const boost::shared_ptr<StartMenu_MW_Black> &black );

			void Apply();
		};

	
		struct FadeInAfterBlack : public Lambda
		{
		
			boost::shared_ptr<StartMenu_MW_Black> black;
			boost::shared_ptr<Lambda> OnBlack;
			boost::shared_ptr<GameData> game;

		
			FadeInAfterBlack( const boost::shared_ptr<StartMenu_MW_Black> &black, const boost::shared_ptr<Lambda> &OnBlack, const boost::shared_ptr<GameData> &game );

			void Apply();
		};

	
		struct ConvertLambdaToLambdaFuncTrue : public LambdaFunc<bool>
		{
		
			boost::shared_ptr<Lambda> f_;
		
			ConvertLambdaToLambdaFuncTrue( const boost::shared_ptr<Lambda> &f );

			bool Apply();
		};

	
		enum BankType
		{
			BankType_CAMPAIGN,
			BankType_INFINITE
		};
	
		struct FindTargetBobLambda : public LambdaFunc_1<boost::shared_ptr<Bob>, bool>
		{
		
			boost::shared_ptr<Bob> Player;
		
			FindTargetBobLambda( const boost::shared_ptr<Bob> &Player );

			bool Apply( const boost::shared_ptr<Bob> &bob );
		};

	
		struct RemoveMarkedLambda : public LambdaFunc_1<boost::shared_ptr<GameObject>, bool>
		{
		
			RemoveMarkedLambda();

			bool Apply( const boost::shared_ptr<GameObject> &obj );
		};

	
		struct FadeToBlackLambda : public Lambda
		{
		
			boost::shared_ptr<GameData> game_;
			float FadeOutSpeed_;

		
			FadeToBlackLambda( const boost::shared_ptr<GameData> &game, float FadeOutSpeed );

			void Apply();
		};

	
		struct GetCampaignStatsScoreLambda : public LambdaFunc_1<boost::shared_ptr<PlayerData>, float>
		{
		
			GetCampaignStatsScoreLambda();

			float Apply( const boost::shared_ptr<PlayerData> &p );
		};

	
		enum DeathTime
		{
			DeathTime_FOREVER,
			DeathTime_SUPER_SLOW,
			DeathTime_SLOW,
			DeathTime_NORMAL,
			DeathTime_FAST,
			DeathTime_SUPER_FAST
		};

	
		struct OpenDoorAndShowBobsLambda : public Lambda
		{
		
			boost::shared_ptr<Level> MyLevel_;
			boost::shared_ptr<Door> Door_;
			boost::shared_ptr<GameData> Game_;

		
			OpenDoorAndShowBobsLambda( const boost::shared_ptr<Level> &MyLevel, const boost::shared_ptr<Door> &door, const boost::shared_ptr<GameData> &game );

			void Apply();
		};

	
		struct DramaticEntryLambda : public Lambda
		{
		
			boost::shared_ptr<GameData> Game_;
			int Wait_;
			boost::shared_ptr<Door> Door_;

		
			DramaticEntryLambda( const boost::shared_ptr<GameData> &game, int Wait, const boost::shared_ptr<Door> &door );

			void Apply();
		};

	
		struct DramaticEntryEnterLambda : public Lambda
		{
		
			boost::shared_ptr<Door> Door_;

		
			DramaticEntryEnterLambda( const boost::shared_ptr<Door> &door );

			void Apply();
		};

	
		/// <summary>
		/// Whether the game has lava.
		/// </summary>
		bool HasLava;

	
		//void KillThread( const boost::shared_ptr<Object> &sender, const boost::shared_ptr<System::EventArgs> &e );

		/// <summary>
		/// True when a single player has successfully navigated the level.
		/// </summary>
	
		bool HasBeenCompleted;

		/// <summary>
		/// Function to be called that makes the game's score screen.
		/// </summary>
		boost::shared_ptr<LambdaFunc<boost::shared_ptr<GameObject> > > MakeScore;

		/// <summary>
		/// The statistics associated with this game.
		/// A standaone game (the default) has stats only associated with its specific level.
		/// A campaign game may have stats that spans multiple games.
		/// Likewise an arcade game (comprised of many levels) can have stats that span many levels.
		/// </summary>
		StatGroup MyStatGroup;

		/// <summary>
		/// Action to take when the player exits the final door of the level.
		/// </summary>
		/// <param name="door"></param>
		static void EOL_DoorAction( const boost::shared_ptr<Door> &door );

		/// <summary>
		/// Recycle bin for this game.
		/// </summary>
		boost::shared_ptr<Recycler> Recycle;

		/// <summary>
		/// Whether this game was launched from Freeplay.
		/// </summary>
		bool Freeplay;

		/// <summary>
		/// The GameData that created this game.
		/// </summary>
		boost::shared_ptr<GameData> ParentGame;

		/// <summary>
		/// Called to end the game and return to parent game.
		/// Return true if the game should be replayed.
		/// </summary>
		boost::shared_ptr<Lambda_1<bool> > EndGame;

		/// <summary>
		/// Call to finish the metagame and return to the game that created it.
		/// </summary>
		virtual void Finish( bool Replay );


		bool EndMusicOnFinish;
		virtual void StandardFinish( bool Replay );

		/// <summary>
		/// The previous action fed to PlayGame (typically a call to load a game)
		/// </summary>
	
		boost::shared_ptr<Lambda> PreviousLoadFunction;

	
		void ClearPreviousLoadFunction();

		/// <summary>
		/// Does the specified action and saves the action for the ability to replay it later.
		/// </summary>
		void PlayGame( const boost::shared_ptr<Lambda> &LoadFunction );

		/// <summary>
		/// If the game has called another game, then this function calls it again.
		/// </summary>
		void PlayAgain();
		bool ExecutingPreviousLoadFunction;

		/// <summary>
		/// Add an item to the ToDo list that is executed after a delay.
		/// </summary>
		/// <param name="WaitLength">Number of frames to wait.</param>
		/// <param name="Func">Function to execute.</param>
		void WaitThenDo( int WaitLength, const boost::shared_ptr<Lambda> f );

		void WaitThenDo( int WaitLength, const boost::shared_ptr<Lambda> f, const std::wstring &Name );

		void WaitThenDo( int WaitLength, const boost::shared_ptr<Lambda> f, bool PauseOnPause );
		void WaitThenDo_Pausable( int WaitLength, const boost::shared_ptr<Lambda> f );

		void CinematicToDo( int WaitLength, const boost::shared_ptr<Lambda> f );
		//public void CinematicToDo(LambdaFunc<bool> f)
		//{
		//    AddToDo(f, "", true, true);
		//}
		void WaitThenDo( int WaitLength, const boost::shared_ptr<Lambda> f, const std::wstring &Name, bool PauseOnPause, bool RemoveOnReset );

		void WaitThenAddToToDo( int WaitLength, const boost::shared_ptr<LambdaFunc<bool> > f );

		GameFlags MyGameFlags;

		bool ShowHelpNotes, FadeToBlackBeforeReturn, FadingToReturn;

		bool Loading;

		/// <summary>
		/// If true the player can not quick spawn.
		/// Use the External bool if suppressing quickspawn from outside the game struct.
		/// </summary>
		bool SuppressQuickSpawn, SuppressQuickSpawn_External;

		/// <summary>
		/// Whether quickspawn is enabled.
		/// </summary>
		bool QuickSpawnEnabled();

		bool AllowQuickJoin;

		bool DrawObjectText;

		int CurPlayer;

		/// <summary>
		/// When true song info will not appear when a new song starts.
		/// </summary>
		bool SuppressSongInfo;

		/// <summary>
		/// Main camera of this game.
		/// </summary>
		const boost::shared_ptr<Camera> getCam() const;

		/// <summary>
		/// Random number generator for this game.
		/// All numbers generated in this game should come from this generator.
		/// </summary>
		const boost::shared_ptr<Rand> &getRnd() const;

		/// <summary>
		/// The level immediately associated with this game.
		/// Note: some games have multiple levels associated to them via a list.
		/// Nonetheless, at all times, every game needs to have at least one level specifically singled out as it's actual level.
		/// </summary>
		boost::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The position of the main camera.
		/// </summary>
		const Vector2 getCamPos() const;

	
		boost::shared_ptr<QuadClass> BlackQuad;
		BasePoint BlackBase;
	
		float BlackAlpha, FadeOutSpeed, FadeInSpeed;
		bool FadingToBlack, FadingIn;
	
		boost::shared_ptr<FancyColor> FadeColor;

		bool IsFading();

		/// <summary>
		/// Fade partially to black, do some action, then fade back in.
		/// </summary>
		void PartialFade_InAndOut( int Delay, float TargetOpaqueness, int FadeOutLength, int FadeInLength, const boost::shared_ptr<Lambda> &OnBlack );

		/// <summary>
		/// Transition to a black screen via a right-to-left screen swipe, then fade back in.
		/// When the screen is completely dark, just before fading back in, the OnBlack action is called.
		/// </summary>
		void SlideOut_FadeIn( int Delay, const boost::shared_ptr<Lambda> &OnBlack );

		boost::shared_ptr<Door> CurDoor;

		/// <summary>
		/// A collection of objects in the game that are not in the level, such as GUIs.
		/// </summary>
		GameObjVec MyGameObjects, NewGameObjects;

		/// <summary>
		/// Remove all GameObjects with a specified tag.
		/// </summary>
		void RemoveGameObjects( GameObject::Tag tag );

		/// <summary>
		/// If true coins can be taken only once and are not respawned on a level reset.
		/// </summary>
		bool TakeOnce;

		/// <summary>
		/// If true the coins score is permanent even if the coin respawns.
		/// </summary>
		bool AlwaysGiveCoinScore;

		/// <summary>
		/// The score of coins collected are multiplied by this value.
		/// </summary>
		float CoinScoreMultiplier;
		/// <summary>
		/// Event handler. Activates when this game recalculates it's coin score multiplier.
		/// The multiplier is first reset to 1, then each registered callback can modify it.
		/// </summary>
		boost::shared_ptr<Multicaster_1<boost::shared_ptr<GameData> > > OnCalculateCoinScoreMultiplier;
		/// <summary>
		/// Called at the beginning over every time step to calculate the coin score multiplier
		/// </summary>
	
		void CalculateCoinScoreMultiplier();

		/// <summary>
		/// Values added to a player's score are multiplied by this value.
		/// </summary>
	
		float ScoreMultiplier;
		/// <summary>
		/// Event handler. Activates when this game recalculates it's score multiplier.
		/// The multiplier is first reset to 1, then each registered callback can modify it.
		/// </summary>
		boost::shared_ptr<Multicaster_1<boost::shared_ptr<GameData> > > OnCalculateScoreMultiplier;
		/// <summary>
		/// Called at the beginning over every time step to calculate the score multiplier
		/// </summary>
	
		void CalculateScoreMultiplier();

		/// <summary>
		/// Event handler. Activates when a Checkpoint is grabbed. Argument is the IObject that is a Checkpoint.
		/// </summary>
	
		boost::shared_ptr<Multicaster_1<boost::shared_ptr<ObjectBase> > > OnCheckpointGrab;
		/// <summary>
		/// Call this when a Checkpoint is grabbed to activate the Checkpoint grabbed event handler.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The parameter Checkpoint was renamed since it is named the same as a user-defined type:
		void CheckpointGrabEvent( const boost::shared_ptr<ObjectBase> &Checkpoint_Renamed );

		/// <summary>
		/// Event handler. Activates when a coin is grabbed. Argument is the IObject that is a coin.
		/// </summary>
		boost::shared_ptr<Multicaster_1<boost::shared_ptr<ObjectBase> > > OnCoinGrab;
		/// <summary>
		/// Call this when a coin is grabbed to activate the coin grabbed event handler.
		/// </summary>
		void CoinGrabEvent( const boost::shared_ptr<ObjectBase> &coin );

		/// <summary>
		/// Event handler. Activates when a level is completed.
		/// </summary>
		boost::shared_ptr<Multicaster_1<boost::shared_ptr<Level> > > OnCompleteLevel;
		/// <summary>
		/// Call this when level is completed to activate the level complete event handler.
		/// </summary>
		void CompleteLevelEvent();

		/// <summary>
		/// Event handler. Activates when all players die and the level is reset.
		/// </summary>
		boost::shared_ptr<Multicaster> OnLevelRetry;
		/// <summary>
		/// Call this when a coin is grabbed to activate the coin grabbed event handler.
		/// </summary>
		void LevelRetryEvent();

		/// <summary>
		/// Event handler. Activates when this game is returned to from another game.
		/// </summary>
		boost::shared_ptr<Multicaster> OnReturnTo;
		boost::shared_ptr<Multicaster> OnReturnTo_OneOff;
		/// <summary>
		/// Call this when the game is returned to.
		/// </summary>
		void ReturnToEvent();

		/// <summary>
		/// Add a nameless function to the to do list.
		/// The function should return true if it wishes to be removed from the queue after execution.
		/// </summary>
		void AddToDo( const boost::shared_ptr<LambdaFunc<bool> > &FuncToDo );

		/// <summary>
		/// Add a nameless function to the to do list.
		/// </summary>
		void AddToDo( const boost::shared_ptr<Lambda> &FuncToDo );

		/// <summary>
		/// Add a named function to the to do list.
		/// The function should return true if it wishes to be removed from the queue after execution.
		/// </summary>
		void AddToDo( const boost::shared_ptr<LambdaFunc<bool> > &FuncToDo, const std::wstring &name, bool PauseOnPause, bool RemoveOnReset );

		void AddToDo( const boost::shared_ptr<Lambda> &FuncToDo, const std::wstring &name, bool PauseOnPause, bool RemoveOnReset );

		std::vector<boost::shared_ptr<ToDoItem> > &getToDo();

		std::vector<boost::shared_ptr<Lambda> > ToDoOnReset;
	
		void DoToDoOnResetList();

	
		static int CurItemStep;
	
		void DoToDoList();

		/// <summary>
		/// Remove all ToDo items with the given name
		/// </summary>
	
		void KillToDo( const std::wstring &name );

		/// <summary>
		/// Find all ToDo items with the given name
		/// </summary>
		std::vector<boost::shared_ptr<ToDoItem> > ToDoFindAll( const std::wstring &name );

	
		bool DoingToDoList;

		/// <summary>
		/// Two lists of to do functions, used to allow for the actual ToDo list to have functions that add functions to the list of things to do.
		/// </summary>
		std::vector<boost::shared_ptr<ToDoItem> > NextToDo;
		std::vector<boost::shared_ptr<ToDoItem> > CurToDo;

	
		boost::shared_ptr<BobPhsx> DefaultHeroType;

		bool Released;

		/// <summary>
		/// Clean up the game, remove all connections to everything to ensure proper garbage collection.
		/// </summary>
		virtual void Release();

		static boost::shared_ptr<GameData> Factory( const boost::shared_ptr<LevelSeedData> &data, bool MakeInBackground );

		BankType MyBankType;

		int CreationTime;
		GameData();

	
		bool GameObjectsAreLocked;
		/// <summary>
		/// Lock or unlock the GameObject list
		/// </summary>
		/// <param name="Lock"></param>
		void LockGameObjects( bool Lock );

	
		void AddGameObject( const boost::shared_ptr<GameObject> &obj );

		bool SkipBackgroundPhsx;
		virtual void BackgroundPhsx();

	
		int SetToReturnToCode;

		bool _IsSetToReturnTo;
		const bool &getIsSetToReturnTo() const;
		void setIsSetToReturnTo( const bool &value );
	
		boost::shared_ptr<GameData> PrevGame;
	
		virtual void SetToReturnTo( int code );

		static bool LockLevelStart;
		bool ClearToDoOnReturnTo;
		virtual void ReturnTo( int code );

		void ReviveAll();

		void CleanLastLevel();

		virtual void Reset();

		virtual void RevertCheckpoints();

		virtual void RevertLevel();

		virtual void GotCheckpoint( const boost::shared_ptr<Bob> &CheckpointBob );

		/// <summary>
		/// When set to true the next reset doesn't count against the player's life counter.
		/// </summary>
		bool FreeReset;

		/// <summary>
		/// Called by the level when finishing up it's reset routine.
		/// </summary>
		virtual void AdditionalReset();

		virtual void RemovePlayer( int PlayerIndex );

		virtual void SetCreatedBobParameters( const boost::shared_ptr<Bob> &bob );

		virtual void CreateBob( int i, bool Pop );

		virtual void UpdateBobs();

		void QuickJoinPhsx();

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	
		void UpdateSignedInPlayers();
#endif
		/// <summary>
		/// Whether the game is paused or not.
		/// </summary>
	
		bool PauseGame;

		virtual void UpdateGamePause();

		/// <summary>
		/// Whether the level is paused or not.
		/// </summary>
		bool PauseLevel;

		void UpdateLevelPause();

		/// <summary>
		/// Whether the level is paused or not.
		/// </summary>
		bool SoftPause;

		void UpdateSoftPause();

		/// <summary>
		/// The number of phsx steps that should be executed by the application's main loop between draw frames.
		/// Always set back to 1 after each draw frame.
		/// </summary>
		int PhsxStepsToDo;

		/// <summary>
		/// When true all sounds are suppressed for phsxs steps that are done without being drawn.
		/// </summary>
		bool SuppressSoundForExtraSteps;

		int PhsxCount;
		virtual void PhsxStep();

	
		void CleanGameObjects();

	
		virtual void Move( Vector2 shift );

		virtual void Init();

		/// <summary>
		/// Black out the entire screen.
		/// </summary>
		void Black();

		/// <summary>
		/// Fade in, starting from pure black.
		/// </summary>
		/// <param name="FadeInSpeed"></param>
		void FadeIn( float FadeInSpeed );

		/// <summary>
		/// Fade out to black, starting with no black.
		/// </summary>
		void FadeToBlack();
		void FadeToBlack( float FadeOutSpeed );

		void FadeToBlack( float FadeOutSpeed, int Delay );

		virtual void Draw();

		/// <summary>
		/// This is a hack.
		/// </summary>
		float ForceLevelZoomBeforeDraw;
		bool DoForceZoom;
		float ForceTargetZoom;

	
		void CalculateForceZoom();

	
		virtual void PostDraw();

		virtual void BobDie( const boost::shared_ptr<Level> &level, const boost::shared_ptr<Bob> &bob );

		/// <summary>
		/// A list of actions to take immediately after the last player alive dies.
		/// </summary>
		std::vector<boost::shared_ptr<Lambda> > ToDoOnDeath;
	
		void DoToDoOnDeathList();

		/// <summary>
		/// How far below the screen a dead player must drop before being officially dead.
		/// </summary>
	
		float DoneDyingDistance;

		/// <summary>
		/// How many frames after a player dies before the level can be reset
		/// </summary>
		int DoneDyingCount;

		virtual void BobDoneDying( const boost::shared_ptr<Level> &level, const boost::shared_ptr<Bob> &bob );

		std::vector<boost::shared_ptr<Lambda> > ToDoOnDoneDying;
	
		void DoToDoOnDoneDyingList();

#if defined(XBOX) || defined(XBOX_SIGNIN)
	
		virtual void OnSignOut( const boost::shared_ptr<SignedOutEventArgs> &e );
#endif

	
		bool OnePast( float x );

		bool AllPast( float x );

	
		boost::shared_ptr<PlayerData> getMvp() const;

		boost::shared_ptr<Bob> getMvpBob() const;

	
		bool MvpOnly;
	
		virtual void MakeBobs( const boost::shared_ptr<Level> &level );

	
		int CreateBob( const boost::shared_ptr<Level> &level, int NumStarts, int Count, int i, int j );

	
		virtual void SetAdditionalBobParameters( BobVec &Bobs );

		static boost::shared_ptr<GameData> StartLevel( const boost::shared_ptr<LevelSeedData> &LevelSeed );
		static boost::shared_ptr<GameData> StartLevel( const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		bool ModdedBlobGrace;
		float BlobGraceY;

		#pragma region Helper functions for campaign
		static void UseBobLighting( const boost::shared_ptr<Level> &lvl, int difficulty );
		#pragma endregion

		#pragma region Helper functions for mini-games
		void RemoveLastCoinText();

		/// <summary>
		/// Make deaths quicker.
		/// </summary>
		void SetDeathTime( DeathTime time );

		virtual void EnterFrom( const boost::shared_ptr<Door> &door );
		virtual void EnterFrom( const boost::shared_ptr<Door> &door, int Wait );

	
		static std::vector<int> DramaticEntryWait;
		static Vector2 DramaticEntryVel;
		void SetDramaticEntryParams();
	
		virtual int DramaticEntry( const boost::shared_ptr<Door> &door, int Wait );

	
		void MoveAndUpdateBobs();

	
		void HideBobs();

		void ShowBobs();
		#pragma endregion

		#pragma region Helper functions for making trailer
	
		void LoadRecording( const std::wstring &RecordingName );
		#pragma endregion

	
		void InitializeInstanceFields();
	};

	struct GameFactory
	{
	
		virtual boost::shared_ptr<GameData> Make( const boost::shared_ptr<LevelSeedData> &data, bool MakeInBackground );
	};

	struct SimpleGameFactory
	{
	
		virtual boost::shared_ptr<GameData> Make();
	};

}


#endif	//#ifndef GAMETYPE
