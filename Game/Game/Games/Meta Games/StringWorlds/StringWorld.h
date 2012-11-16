#ifndef STRINGWORLD
#define STRINGWORLD

#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Games/GameType.h"
#include "../Core/Lambdas/LambdaFunc.h"
#include "../Core/Lambdas/Lambda.h"
#include <vector>
#include <tchar.h>

namespace CloudberryKingdom
{
	class Door;
}

namespace CloudberryKingdom
{
	class StringWorldGameData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class LambdaFunc_1;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class Multicaster_1;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	class EOL_StringWorldDoorActionProxy : public Lambda_1<Door*>
	{
	private:
		std::shared_ptr<StringWorldGameData> gameData;

	public:
		EOL_StringWorldDoorActionProxy( const std::shared_ptr<StringWorldGameData> &gameData );

		void Apply( const std::shared_ptr<Door> &door );
	};

	class EOL_StringWorldDoorEndActionProxy : public Lambda_1<Door*>
	{
	private:
		std::shared_ptr<StringWorldGameData> gameData;

	public:
		EOL_StringWorldDoorEndActionProxy( const std::shared_ptr<StringWorldGameData> &gameData );

		void Apply( const std::shared_ptr<Door> &door );
	};

	class EOG_StandardDoorActionProxy : public Lambda_1<Door*>
	{
	public:
		void Apply( const std::shared_ptr<Door> &door );
	};

	class StringWorldGameData : public GameData
	{
	private:
		class StartOfLevelLambda : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<StringWorldGameData> g;
			std::shared_ptr<Level> level;
			bool Hold_FirstLevelHasBegun;

		public:
			StartOfLevelLambda( const std::shared_ptr<StringWorldGameData> &g, const std::shared_ptr<Level> &level, bool Hold_FirstLevelHasBegun );

			bool Apply();
		};

	private:
		class DefaultStartLevelMusicProxy : public Lambda_1<StringWorldGameData*>
		{
		public:
			void Apply( const std::shared_ptr<StringWorldGameData> &stringworld );
		};

	private:
		class OpenAndShowLambda : public Lambda
		{
		private:
			std::shared_ptr<StringWorldGameData> g;
			std::shared_ptr<Level> level;
			std::shared_ptr<Door> door;
			std::shared_ptr<LevelSeedData> CurLevelSeed;
		public:
			OpenAndShowLambda( const std::shared_ptr<StringWorldGameData> &g, const std::shared_ptr<Level> &level, const std::shared_ptr<Door> &door, const std::shared_ptr<LevelSeedData> &CurLevelSeed );

			void Apply();
		};

	private:
		class FinishLambda : public Lambda_1<bool>
		{
		private:
			std::shared_ptr<StringWorldGameData> g;
		public:
			FinishLambda( const std::shared_ptr<StringWorldGameData> &g );

			void Apply( bool val );
		};

	private:
		class CloseDoorAndAbsorbLambda : public Lambda
		{
		private:
			std::shared_ptr<Door> door;
		public:
			CloseDoorAndAbsorbLambda( const std::shared_ptr<Door> &door );

			void Apply();
		};

	private:
		class StartNextLevelLambda : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<StringWorldGameData> g;

		public:
			StartNextLevelLambda( const std::shared_ptr<StringWorldGameData> &g );

			bool Apply();
		};

	public:
		static std::shared_ptr<GameData> Factory( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );

		virtual void Release();

		int Count;

	protected:
		Func<int, LevelSeedData*> GetSeedFunc;
	private:
		std::shared_ptr<LevelSeedData> NextLevelSeed, CurLevelSeed;

	public:
		int NextLevelIndex, CurLevelIndex;
		bool FirstLevelHasLoaded;
		bool FirstLevelHasBegun;

		/// <summary>
		/// Called when a level begins loading
		/// </summary>
		std::shared_ptr<Lambda> OnBeginLoad;

		std::shared_ptr<LevelSeedData> GetSeed( int Index );

		/// <summary>
		/// Returns whether the StringWorld is ready to switch to the next level
		/// </summary>
		bool NextIsReady();

		/// <summary>
		/// Called during LevelBegin, adds relevant GameObjects to the level's game.
		/// </summary>
		std::shared_ptr<LambdaFunc_1<Level*, bool> > OnLevelBegin;

		/// <summary>
		/// How long to wait before opening the initial door on the first level.
		/// </summary>
	protected:
		int WaitLengthToOpenDoor_FirstLevel;

		/// <summary>
		/// Various details that must occur just before a level is played.
		/// </summary>
	public:
		void LevelBegin( const std::shared_ptr<Level> &level );

		/// <summary>
		/// Called at the start of a level to begin music.
		/// </summary>
		std::shared_ptr<Lambda_1<StringWorldGameData*> > StartLevelMusic;

		static void DefaultStartLevelMusic( const std::shared_ptr<StringWorldGameData> &stringworld );

		/// <summary>
		/// Closes the beginning door of the level and hides the players;
		/// </summary>
		static void BeginningCloseDoor( const std::shared_ptr<Level> &level );

		bool FirstDoorAction;
	private:
		void StartOfLevelDoorAction( const std::shared_ptr<Level> &level );

	public:
		void _StartOfLevelDoorAction__OpenAndShow( const std::shared_ptr<Level> &level, const std::shared_ptr<Door> &door, bool OpenDoorSound );

		/// <summary>
		/// Whether the level is loaded.
		/// </summary>
		bool LevelIsLoaded( const std::shared_ptr<LevelSeedData> &data );

		/// <summary>
		/// Assuming a level is loaded, set that level as current.
		/// Begin loading next level.
		/// </summary>
		void SetLevel();

		virtual void Finish( bool Replay );

		/// <summary>
		/// Called when the first level is swapped in.
		/// </summary>
		std::shared_ptr<Multicaster_1<LevelSeedData*> > OnSwapToFirstLevel;

		/// <summary>
		/// Called when the last level is swapped in.
		/// </summary>
		std::shared_ptr<Multicaster_1<LevelSeedData*> > OnSwapToLastLevel;

		/// <summary>
		/// Called when a level is swapped to. The parameter is the current level index.
		/// </summary>
		std::shared_ptr<Multicaster_1<int> > OnSwapToLevel;

		/// <summary>
		/// True after the first level has been swapped in (and always true thereafter)
		/// </summary>
	private:
		bool FirstLevelSwappedIn;

	public:
		bool NextIsLast();

		void SwapToLevel();

		virtual void AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game );

		void Load( int Index );

		bool EndLoadingImmediately;

	private:
		std::shared_ptr<Level> LastLevelSeedSet;
	public:
		virtual void BackgroundPhsx();

		StringWorldGameData();

		StringWorldGameData( Func<int, LevelSeedData*> GetSeed );

		std::shared_ptr<Level> MakeLevel();

		/// <summary>
		/// The index of the first level played within the list of all LevelSeeds
		/// </summary>
	private:
		int StartIndex;

	public:
		virtual void Init();
		virtual void Init( int StartIndex );

		virtual void SetToReturnTo( int code );

		virtual void ReturnTo( int code );

		/// <summary>
		/// Attached to the last door of the last level.
		/// </summary>
		static void EOG_StandardDoorAction( const std::shared_ptr<Door> &door );

		/// <summary>
		/// Attached to each door at the end of a level, and used to link that door to the next level in the string.
		/// </summary>
		void EOL_StringWorldDoorAction( const std::shared_ptr<Door> &door );

		/// <summary>
		/// Attached to each door at the end of a level, executed after the door is closed.
		/// This sets the next level to be switched to.
		/// </summary>
		void EOL_StringWorldDoorEndAction( const std::shared_ptr<Door> &door );

		/// <summary>
		/// Attached to each door at the end of a level, executed after the door is closed.
		/// This sets the next level to be switched to, but first fades the current level to black.
		/// </summary>
		void EOL_StringWorldDoorEndAction_WithFade( const std::shared_ptr<Door> &door );


	private:
		bool WaitingForNext;
		void TellGameToBringNext( int delay, const std::shared_ptr<GameData> &game );

	public:
		static void BaseDoorAction( const std::shared_ptr<Door> &door );

		virtual void PhsxStep();

		virtual void PostDraw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STRINGWORLD
