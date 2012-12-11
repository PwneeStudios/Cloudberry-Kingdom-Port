#ifndef STRINGWORLD
#define STRINGWORLD

#include <global_header.h>

namespace CloudberryKingdom
{

	struct EOL_StringWorldDoorActionProxy : public Lambda_1<std::shared_ptr<Door> >
	{
	
		std::shared_ptr<StringWorldGameData> gameData;

	
		EOL_StringWorldDoorActionProxy( const std::shared_ptr<StringWorldGameData> &gameData );

		void Apply( const std::shared_ptr<Door> &door );
	};

	struct EOL_StringWorldDoorEndActionProxy : public Lambda_1<std::shared_ptr<Door> >
	{
	
		std::shared_ptr<StringWorldGameData> gameData;

	
		EOL_StringWorldDoorEndActionProxy( const std::shared_ptr<StringWorldGameData> &gameData );

		void Apply( const std::shared_ptr<Door> &door );
	};

	struct EOG_StandardDoorActionProxy : public Lambda_1<std::shared_ptr<Door> >
	{
	
		void Apply( const std::shared_ptr<Door> &door );
	};

	struct StringWorldGameData : public GameData
	{
	
		struct StartOfLevelLambda : public LambdaFunc<bool>
		{
		
			std::shared_ptr<StringWorldGameData> g;
			std::shared_ptr<Level> level;
			bool Hold_FirstLevelHasBegun;

		
			StartOfLevelLambda( std::shared_ptr<StringWorldGameData> &g, const std::shared_ptr<Level> &level, bool Hold_FirstLevelHasBegun );

			bool Apply();
		};

	
		struct DefaultStartLevelMusicProxy : public Lambda_1<std::shared_ptr<StringWorldGameData> >
		{
		
			void Apply( const std::shared_ptr<StringWorldGameData> &stringworld );
		};

	
		struct OpenAndShowLambda : public Lambda
		{
		
			std::shared_ptr<StringWorldGameData> g;
			std::shared_ptr<Level> level;
			std::shared_ptr<Door> door;
			std::shared_ptr<LevelSeedData> CurLevelSeed;
		
			OpenAndShowLambda( std::shared_ptr<StringWorldGameData> &g, const std::shared_ptr<Level> &level, const std::shared_ptr<Door> &door, const std::shared_ptr<LevelSeedData> &CurLevelSeed );

			void Apply();
		};

	
		struct FinishLambda : public Lambda_1<bool>
		{
		
			std::shared_ptr<StringWorldGameData> g;
		
			FinishLambda( const std::shared_ptr<StringWorldGameData> &g );

			void Apply( const bool &val );
		};

	
		struct CloseDoorAndAbsorbLambda : public Lambda
		{
		
			std::shared_ptr<Door> door;
		
			CloseDoorAndAbsorbLambda( const std::shared_ptr<Door> &door );

			void Apply();
		};

	
		struct StartNextLevelLambda : public LambdaFunc<bool>
		{
		
			std::shared_ptr<StringWorldGameData> g;

		
			StartNextLevelLambda( const std::shared_ptr<StringWorldGameData> &g );

			bool Apply();
		};

	
		static std::shared_ptr<GameData> Factory( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground );

		virtual void Release();

		int Count;

	
		std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > GetSeedFunc;
	
		std::shared_ptr<LevelSeedData> NextLevelSeed, CurLevelSeed;

	
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
		std::shared_ptr<LambdaFunc_1<std::shared_ptr<Level>, bool> > OnLevelBegin;

		/// <summary>
		/// How long to wait before opening the initial door on the first level.
		/// </summary>
	
		int WaitLengthToOpenDoor_FirstLevel;

		/// <summary>
		/// Various details that must occur just before a level is played.
		/// </summary>
	
		void LevelBegin( const std::shared_ptr<Level> &level );

		/// <summary>
		/// Called at the start of a level to begin music.
		/// </summary>
		std::shared_ptr<Lambda_1<std::shared_ptr<StringWorldGameData> > > StartLevelMusic;

		static void DefaultStartLevelMusic( const std::shared_ptr<StringWorldGameData> &stringworld );

		/// <summary>
		/// Closes the beginning door of the level and hides the players;
		/// </summary>
		static void BeginningCloseDoor( const std::shared_ptr<Level> &level );

		bool FirstDoorAction;
	
		void StartOfLevelDoorAction( const std::shared_ptr<Level> &level );

	
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
		std::shared_ptr<Multicaster_1<std::shared_ptr<LevelSeedData> > > OnSwapToFirstLevel;

		/// <summary>
		/// Called when the last level is swapped in.
		/// </summary>
		std::shared_ptr<Multicaster_1<std::shared_ptr<LevelSeedData> > > OnSwapToLastLevel;

		/// <summary>
		/// Called when a level is swapped to. The parameter is the current level index.
		/// </summary>
		std::shared_ptr<Multicaster_1<int> > OnSwapToLevel;

		/// <summary>
		/// True after the first level has been swapped in (and always true thereafter)
		/// </summary>
	
		bool FirstLevelSwappedIn;

	
		bool NextIsLast();

		void SwapToLevel();

		virtual void AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game );

		void Load( int Index );

		bool EndLoadingImmediately;

	
		std::shared_ptr<Level> LastLevelSeedSet;
	
		virtual void BackgroundPhsx();

		StringWorldGameData();

		StringWorldGameData( const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed );

		std::shared_ptr<Level> MakeLevel();

		/// <summary>
		/// The index of the first level played within the list of all LevelSeeds
		/// </summary>
	
		int StartIndex;

	
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


	
		bool WaitingForNext;
		void TellGameToBringNext( int delay, const std::shared_ptr<GameData> &game );

	
		static void BaseDoorAction( const std::shared_ptr<Door> &door );

		virtual void PhsxStep();

		virtual void PostDraw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STRINGWORLD
