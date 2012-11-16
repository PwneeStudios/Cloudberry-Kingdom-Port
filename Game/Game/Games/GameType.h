#ifndef GAMETYPE
#define GAMETYPE

#include <global_header.h>

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class Door;
}

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class LambdaFunc;
}

namespace CloudberryKingdom
{
	class StartMenu_MW_Black;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Recycler;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class Camera;
}

namespace CloudberryKingdom
{
	class Rand;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class FancyColor;
}

namespace CloudberryKingdom
{
	class Multicaster_1;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class Multicaster;
}

namespace CloudberryKingdom
{
	class ToDoItem;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class GameObject;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace GamerServices
			{
				class SignedOutEventArgs;
			}
		}
	}
}



#if defined(XBOX) || defined(XBOX_SIGNIN)

#endif



namespace CloudberryKingdom
{
	class GameFactory
	{
	public:
		virtual std::shared_ptr<GameData> Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );
	};

	class SimpleGameFactory
	{
	public:
		virtual std::shared_ptr<GameData> Make();
	};

	class GameFlags
	{
		/// <summary>
		/// Whether the game has the players tethered
		/// </summary>
	public:
		bool IsTethered;

		/// <summary>
		/// Whether the game is a Doppleganger Game
		/// </summary>
		bool IsDoppleganger;

		/// <summary>
		/// Whether the Doppleganger Game is inverting the doppleganger
		/// </summary>
		bool IsDopplegangerInvert;

		void SetToDefault();
	};

	/// <summary>
	/// This is the main super-class of the engine.
	/// Whenever a player is playing, they are in a 'Game'.
	/// A Game consists of at least one level (a Level class instance),
	/// as well as some goal or purpose: getting to a door, collecting coins, surviving, or building a level, etc.
	/// The game class holds the levels and purpose of the level.
	/// Different purposes are implemented as children classes of the main GameData class.
	/// </summary>
	class GameData
	{
	private:
		class AddScoreLambda : public Lambda
		{
		private:
			std::shared_ptr<GameData> game;
			std::shared_ptr<Door> door;

		public:
			AddScoreLambda( const std::shared_ptr<GameData> &game, const std::shared_ptr<Door> &door );

			void Apply();
		};

	private:
		class FinishProxy : public Lambda_1<bool>
		{
		private:
			std::shared_ptr<GameData> gt;

		public:
			FinishProxy( const std::shared_ptr<GameData> &gt );

			void Apply( bool Replay );
		};

	private:
		class PlayWorldMapMusicLambda : public Lambda
		{
		public:
			PlayWorldMapMusicLambda();

			void Apply();
		};

	private:
		class PlayAgainLambda : public Lambda
		{
		private:
			std::shared_ptr<GameData> parentgame;
		public:
			PlayAgainLambda( const std::shared_ptr<GameData> &parentgame );

			void Apply();
		};

	private:
		class ReleaseThisLambda : public Lambda
		{
		private:
			std::shared_ptr<GameData> game;

		public:
			ReleaseThisLambda( const std::shared_ptr<GameData> &game );

			void Apply();
		};

	private:
		class WaitThenDoCoversion : public LambdaFunc<bool>
		{
		private:
			int WaitLength_, Count_;
			std::shared_ptr<Lambda> f_;

		public:
			WaitThenDoCoversion( int WaitLength, const std::shared_ptr<Lambda> &f );

			bool Apply();
		};

	private:
		class WaitThenAddToToDoLambda : public Lambda
		{
		private:
			std::shared_ptr<GameData> game;
			std::shared_ptr<LambdaFunc<bool> > f;

		public:
			WaitThenAddToToDoLambda( const std::shared_ptr<GameData> &game, const std::shared_ptr<LambdaFunc<bool> > &f );

			void Apply();
		};

	private:
		class FadeInAndDoAction : public Lambda
		{
		private:
			std::shared_ptr<GameData> game;
			std::shared_ptr<Lambda> OnBlack;
			float speed;
			float TargetOpaqueness;

		public:
			FadeInAndDoAction( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &OnBlack, float speed, float TargetOpaqueness );

			void Apply();
		};

	private:
		class SlideInLambda : public Lambda
		{
		private:
			std::shared_ptr<StartMenu_MW_Black> black;

		public:
			SlideInLambda( const std::shared_ptr<StartMenu_MW_Black> &black );

			void Apply();
		};

	private:
		class FadeInAfterBlack : public Lambda
		{
		private:
			std::shared_ptr<StartMenu_MW_Black> black;
			std::shared_ptr<Lambda> OnBlack;
			std::shared_ptr<GameData> game;

		public:
			FadeInAfterBlack( const std::shared_ptr<StartMenu_MW_Black> &black, const std::shared_ptr<Lambda> &OnBlack, const std::shared_ptr<GameData> &game );

			void Apply();
		};

	private:
		class ConvertLambdaToLambdaFuncTrue : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<Lambda> f_;
		public:
			ConvertLambdaToLambdaFuncTrue( const std::shared_ptr<Lambda> &f );

			bool Apply();
		};

	public:
		enum BankType
		{
			BankType_CAMPAIGN,
			BankType_INFINITE
		};
	private:
		class FindTargetBobLambda : public LambdaFunc_1<Bob*, bool>
		{
		private:
			std::shared_ptr<Bob> Player;
		public:
			FindTargetBobLambda( const std::shared_ptr<Bob> &Player );

			bool Apply( const std::shared_ptr<Bob> &bob );
		};

	private:
		class RemoveMarkedLambda : public LambdaFunc_1<GameObject*, bool>
		{
		public:
			RemoveMarkedLambda();

			bool Apply( const std::shared_ptr<GameObject> &obj );
		};

	private:
		class FadeToBlackLambda : public Lambda
		{
		private:
			std::shared_ptr<GameData> game_;
			float FadeOutSpeed_;

		public:
			FadeToBlackLambda( const std::shared_ptr<GameData> &game, float FadeOutSpeed );

			void Apply();
		};

	private:
		class GetCampaignStatsScoreLambda : public LambdaFunc_1<PlayerData*, float>
		{
		public:
			GetCampaignStatsScoreLambda();

			float Apply( const std::shared_ptr<PlayerData> &p );
		};

	public:
		enum DeathTime
		{
			DeathTime_FOREVER,
			DeathTime_SUPER_SLOW,
			DeathTime_SLOW,
			DeathTime_NORMAL,
			DeathTime_FAST,
			DeathTime_SUPER_FAST
		};

	private:
		class OpenDoorAndShowBobsLambda : public Lambda
		{
		private:
			std::shared_ptr<Level> MyLevel_;
			std::shared_ptr<Door> Door_;
			std::shared_ptr<GameData> Game_;

		public:
			OpenDoorAndShowBobsLambda( const std::shared_ptr<Level> &MyLevel, const std::shared_ptr<Door> &door, const std::shared_ptr<GameData> &game );

			void Apply();
		};

	private:
		class DramaticEntryLambda : public Lambda
		{
		private:
			std::shared_ptr<GameData> Game_;
			int Wait_;
			std::shared_ptr<Door> Door_;

		public:
			DramaticEntryLambda( const std::shared_ptr<GameData> &game, int Wait, const std::shared_ptr<Door> &door );

			void Apply();
		};

	private:
		class DramaticEntryEnterLambda : public Lambda
		{
		private:
			std::shared_ptr<Door> Door_;

		public:
			DramaticEntryEnterLambda( const std::shared_ptr<Door> &door );

			void Apply();
		};

		/// <summary>
		/// Dictionary to get a game factory from a string.
		/// </summary>
	public:
		static std::unordered_map<std::wstring, GameFactory*> FactoryDict;

		/// <summary>
		/// Used in the Background Editor to assign GUID to objects.
		/// </summary>
		static int DataCounter;
		int MyDataNumber;

		/// <summary>
		/// Whether the game has lava.
		/// </summary>
		bool HasLava;

	protected:
		void KillThread( const std::shared_ptr<Object> &sender, const std::shared_ptr<System::EventArgs> &e );

		/// <summary>
		/// True when a single player has successfully navigated the level.
		/// </summary>
	public:
		bool HasBeenCompleted;

		/// <summary>
		/// Function to be called that makes the game's score screen.
		/// </summary>
		std::shared_ptr<LambdaFunc<GameObject*> > MakeScore;

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
		static void EOL_DoorAction( const std::shared_ptr<Door> &door );

		/// <summary>
		/// Recycle bin for this game.
		/// </summary>
		std::shared_ptr<Recycler> Recycle;

		/// <summary>
		/// Whether this game was launched from Freeplay.
		/// </summary>
		bool Freeplay;

		/// <summary>
		/// The GameData that created this game.
		/// </summary>
		std::shared_ptr<GameData> ParentGame;

		/// <summary>
		/// Called to end the game and return to parent game.
		/// Return true if the game should be replayed.
		/// </summary>
		std::shared_ptr<Lambda_1<bool> > EndGame;

		/// <summary>
		/// Call to finish the metagame and return to the game that created it.
		/// </summary>
		virtual void Finish( bool Replay );


		bool EndMusicOnFinish;
		virtual void StandardFinish( bool Replay );

		/// <summary>
		/// The previous action fed to PlayGame (typically a call to load a game)
		/// </summary>
	private:
		std::shared_ptr<Lambda> PreviousLoadFunction;

	public:
		void ClearPreviousLoadFunction();

		/// <summary>
		/// Does the specified action and saves the action for the ability to replay it later.
		/// </summary>
		void PlayGame( const std::shared_ptr<Lambda> &LoadFunction );

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
		void WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> &f );

		void WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> &f, const std::wstring &Name );

		void WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> &f, bool PauseOnPause );
		void WaitThenDo_Pausable( int WaitLength, const std::shared_ptr<Lambda> &f );

		void CinematicToDo( int WaitLength, const std::shared_ptr<Lambda> &f );
		//public void CinematicToDo(LambdaFunc<bool> f)
		//{
		//    AddToDo(f, "", true, true);
		//}
		void WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> &f, const std::wstring &Name, bool PauseOnPause, bool RemoveOnReset );

		void WaitThenAddToToDo( int WaitLength, const std::shared_ptr<LambdaFunc<bool> > &f );

		GameFlags MyGameFlags;

		bool ShowHelpNotes, FadeToBlackBeforeReturn, FadingToReturn;

		bool Loading;

		/// <summary>
		/// If true the player can not quick spawn.
		/// Use the External bool if suppressing quickspawn from outside the game class.
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
		const std::shared_ptr<Camera> &getCam() const;

		/// <summary>
		/// Random number generator for this game.
		/// All numbers generated in this game should come from this generator.
		/// </summary>
		const std::shared_ptr<Rand> &getRnd() const;

		/// <summary>
		/// The level immediately associated with this game.
		/// Note: some games have multiple levels associated to them via a list.
		/// Nonetheless, at all times, every game needs to have at least one level specifically singled out as it's actual level.
		/// </summary>
		std::shared_ptr<Level> MyLevel;

		/// <summary>
		/// The position of the main camera.
		/// </summary>
		const Vector2 &getCamPos() const;

	private:
		std::shared_ptr<QuadClass> BlackQuad;
		BasePoint BlackBase;
	protected:
		float BlackAlpha, FadeOutSpeed, FadeInSpeed;
		bool FadingToBlack, FadingIn;
	public:
		std::shared_ptr<FancyColor> FadeColor;

		bool IsFading();

		/// <summary>
		/// Fade partially to black, do some action, then fade back in.
		/// </summary>
		void PartialFade_InAndOut( int Delay, float TargetOpaqueness, int FadeOutLength, int FadeInLength, const std::shared_ptr<Lambda> &OnBlack );

		/// <summary>
		/// Transition to a black screen via a right-to-left screen swipe, then fade back in.
		/// When the screen is completely dark, just before fading back in, the OnBlack action is called.
		/// </summary>
		void SlideOut_FadeIn( int Delay, const std::shared_ptr<Lambda> &OnBlack );

		std::shared_ptr<Door> CurDoor;

		/// <summary>
		/// A collection of objects in the game that are not in the level, such as GUIs.
		/// </summary>
		std::vector<GameObject*> MyGameObjects, NewGameObjects;

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
		std::shared_ptr<Multicaster_1<GameData*> > OnCalculateCoinScoreMultiplier;
		/// <summary>
		/// Called at the beginning over every time step to calculate the coin score multiplier
		/// </summary>
	private:
		void CalculateCoinScoreMultiplier();

		/// <summary>
		/// Values added to a player's score are multiplied by this value.
		/// </summary>
	public:
		float ScoreMultiplier;
		/// <summary>
		/// Event handler. Activates when this game recalculates it's score multiplier.
		/// The multiplier is first reset to 1, then each registered callback can modify it.
		/// </summary>
		std::shared_ptr<Multicaster_1<GameData*> > OnCalculateScoreMultiplier;
		/// <summary>
		/// Called at the beginning over every time step to calculate the score multiplier
		/// </summary>
	private:
		void CalculateScoreMultiplier();

		/// <summary>
		/// Event handler. Activates when a Checkpoint is grabbed. Argument is the IObject that is a Checkpoint.
		/// </summary>
	public:
		std::shared_ptr<Multicaster_1<ObjectBase*> > OnCheckpointGrab;
		/// <summary>
		/// Call this when a Checkpoint is grabbed to activate the Checkpoint grabbed event handler.
		/// </summary>
//C# TO C++ CONVERTER NOTE: The parameter Checkpoint was renamed since it is named the same as a user-defined type:
		void CheckpointGrabEvent( const std::shared_ptr<ObjectBase> &Checkpoint_Renamed );

		/// <summary>
		/// Event handler. Activates when a coin is grabbed. Argument is the IObject that is a coin.
		/// </summary>
		std::shared_ptr<Multicaster_1<ObjectBase*> > OnCoinGrab;
		/// <summary>
		/// Call this when a coin is grabbed to activate the coin grabbed event handler.
		/// </summary>
		void CoinGrabEvent( const std::shared_ptr<ObjectBase> &coin );

		/// <summary>
		/// Event handler. Activates when a level is completed.
		/// </summary>
		std::shared_ptr<Multicaster_1<Level*> > OnCompleteLevel;
		/// <summary>
		/// Call this when level is completed to activate the level complete event handler.
		/// </summary>
		void CompleteLevelEvent();

		/// <summary>
		/// Event handler. Activates when all players die and the level is reset.
		/// </summary>
		std::shared_ptr<Multicaster> OnLevelRetry;
		/// <summary>
		/// Call this when a coin is grabbed to activate the coin grabbed event handler.
		/// </summary>
		void LevelRetryEvent();

		/// <summary>
		/// Event handler. Activates when this game is returned to from another game.
		/// </summary>
		std::shared_ptr<Multicaster> OnReturnTo;
		std::shared_ptr<Multicaster> OnReturnTo_OneOff;
		/// <summary>
		/// Call this when the game is returned to.
		/// </summary>
		void ReturnToEvent();

		/// <summary>
		/// Add a nameless function to the to do list.
		/// The function should return true if it wishes to be removed from the queue after execution.
		/// </summary>
		void AddToDo( const std::shared_ptr<LambdaFunc<bool> > &FuncToDo );

		/// <summary>
		/// Add a nameless function to the to do list.
		/// </summary>
		void AddToDo( const std::shared_ptr<Lambda> &FuncToDo );

		/// <summary>
		/// Add a named function to the to do list.
		/// The function should return true if it wishes to be removed from the queue after execution.
		/// </summary>
		void AddToDo( const std::shared_ptr<LambdaFunc<bool> > &FuncToDo, const std::wstring &name, bool PauseOnPause, bool RemoveOnReset );

		void AddToDo( const std::shared_ptr<Lambda> &FuncToDo, const std::wstring &name, bool PauseOnPause, bool RemoveOnReset );

		const std::vector<ToDoItem*> &getToDo() const;

		std::vector<Lambda*> ToDoOnReset;
	private:
		void DoToDoOnResetList();

	public:
		static int CurItemStep;
	private:
		void DoToDoList();

		/// <summary>
		/// Remove all ToDo items with the given name
		/// </summary>
	public:
		void KillToDo( const std::wstring &name );

		/// <summary>
		/// Find all ToDo items with the given name
		/// </summary>
		std::vector<ToDoItem*> ToDoFindAll( const std::wstring &name );

	private:
		bool DoingToDoList;

		/// <summary>
		/// Two lists of to do functions, used to allow for the actual ToDo list to have functions that add functions to the list of things to do.
		/// </summary>
		std::vector<ToDoItem*> NextToDo;
		std::vector<ToDoItem*> CurToDo;

	public:
		std::shared_ptr<BobPhsx> DefaultHeroType;

		bool Released;

		/// <summary>
		/// Clean up the game, remove all connections to everything to ensure proper garbage collection.
		/// </summary>
		virtual void Release();

		static std::shared_ptr<GameData> Factory( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );

		BankType MyBankType;

		int CreationTime;
		GameData();

	private:
		bool GameObjectsAreLocked;
		/// <summary>
		/// Lock or unlock the GameObject list
		/// </summary>
		/// <param name="Lock"></param>
		void LockGameObjects( bool Lock );

	public:
//ORIGINAL LINE: public void AddGameObject(params GameObject[] list)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		void AddGameObject( ... );

		void AddGameObject( const std::shared_ptr<GameObject> &obj );

		bool SkipBackgroundPhsx;
		virtual void BackgroundPhsx();

	private:
		int SetToReturnToCode;

		bool _IsSetToReturnTo;
		const bool &getIsSetToReturnTo() const;
		void setIsSetToReturnTo( const bool &value );
	protected:
		std::shared_ptr<GameData> PrevGame;
	public:
		virtual void SetToReturnTo( int code );

		static bool LockLevelStart;
		bool ClearToDoOnReturnTo;
		virtual void ReturnTo( int code );

		void ReviveAll();

		void CleanLastLevel();

		virtual void Reset();

		virtual void RevertCheckpoints();

		virtual void RevertLevel();

		virtual void GotCheckpoint( const std::shared_ptr<Bob> &CheckpointBob );

		/// <summary>
		/// When set to true the next reset doesn't count against the player's life counter.
		/// </summary>
		bool FreeReset;

		/// <summary>
		/// Called by the level when finishing up it's reset routine.
		/// </summary>
		virtual void AdditionalReset();

		virtual void RemovePlayer( int PlayerIndex );

		virtual void SetCreatedBobParameters( const std::shared_ptr<Bob> &bob );

		virtual void CreateBob( int i, bool Pop );

		virtual void UpdateBobs();

		void QuickJoinPhsx();

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	private:
		void UpdateSignedInPlayers();
#endif
		/// <summary>
		/// Whether the game is paused or not.
		/// </summary>
	public:
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

	private:
		void CleanGameObjects();

	public:
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

	private:
		void CalculateForceZoom();

	public:
		virtual void PostDraw();

		virtual void BobDie( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob );

		/// <summary>
		/// A list of actions to take immediately after the last player alive dies.
		/// </summary>
		std::vector<Lambda*> ToDoOnDeath;
	private:
		void DoToDoOnDeathList();

		/// <summary>
		/// How far below the screen a dead player must drop before being officially dead.
		/// </summary>
	public:
		float DoneDyingDistance;

		/// <summary>
		/// How many frames after a player dies before the level can be reset
		/// </summary>
		int DoneDyingCount;

		virtual void BobDoneDying( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob );

		std::vector<Lambda*> ToDoOnDoneDying;
	private:
		void DoToDoOnDoneDyingList();

#if defined(XBOX) || defined(XBOX_SIGNIN)
	public:
		virtual void OnSignOut( const std::shared_ptr<SignedOutEventArgs> &e );
#endif

	protected:
		bool OnePast( float x );

		bool AllPast( float x );

	public:
		const std::shared_ptr<PlayerData> &getMvp() const;

		const std::shared_ptr<Bob> &getMvpBob() const;

	protected:
		bool MvpOnly;
	public:
		virtual void MakeBobs( const std::shared_ptr<Level> &level );

	private:
		int CreateBob( const std::shared_ptr<Level> &level, int NumStarts, int Count, int i, int j );

	public:
		void SetAdditionalBobParameters( std::vector<Bob*> Bobs );
		virtual void SetAdditionalBobParameters( std::vector<Bob*> &Bobs );

		static std::shared_ptr<GameData> StartLevel( const std::shared_ptr<LevelSeedData> &LevelSeed );
		static std::shared_ptr<GameData> StartLevel( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );

		bool ModdedBlobGrace;
		float BlobGraceY;

		#pragma region Helper functions for campaign
		static void UseBobLighting( const std::shared_ptr<Level> &lvl, int difficulty );
		#pragma endregion

		#pragma region Helper functions for mini-games
		void RemoveLastCoinText();

		/// <summary>
		/// Make deaths quicker.
		/// </summary>
		void SetDeathTime( DeathTime time );

		virtual void EnterFrom( const std::shared_ptr<Door> &door );
		virtual void EnterFrom( const std::shared_ptr<Door> &door, int Wait );

	private:
		static std::vector<int> DramaticEntryWait;
		static Vector2 DramaticEntryVel;
		void SetDramaticEntryParams();
	public:
		virtual int DramaticEntry( const std::shared_ptr<Door> &door, int Wait );

	private:
		void MoveAndUpdateBobs();

	public:
		void HideBobs();

		void ShowBobs();
		#pragma endregion

		#pragma region Helper functions for making trailer
	protected:
		void LoadRecording( const std::wstring &RecordingName );
		#pragma endregion

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMETYPE
