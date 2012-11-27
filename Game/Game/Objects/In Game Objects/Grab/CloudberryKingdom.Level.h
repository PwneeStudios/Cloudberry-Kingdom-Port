#ifndef CLOUDBERRYKINGDOM_LEVEL
#define CLOUDBERRYKINGDOM_LEVEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class Level
	{
	private:
		class ElementDistanceSquared : public LambdaFunc_1<BlockBase*, float>
		{
		private:
			Vector2 pos;

		public:
			ElementDistanceSquared( Vector2 pos );

			float Apply( const std::shared_ptr<BlockBase> &element );
		};

	private:
		class FindFirstRowLambda : public LambdaFunc_1<BlockBase*, bool>
		{
		public:
			FindFirstRowLambda();

			bool Apply( const std::shared_ptr<BlockBase> &match );
		};

	private:
		class MakeVerticalCleanupHelper : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			std::shared_ptr<Level> level;

		public:
			MakeVerticalCleanupHelper( const std::shared_ptr<Level> &level );

			Vector2 Apply( Vector2 pos );
		};

	private:
		class FindLimitGeneralDensityLambda : public LambdaFunc_1<ObjectBase*, bool>
		{
		public:
			FindLimitGeneralDensityLambda();

			bool Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class EndReachedLambda : public Lambda
		{
		private:
			std::shared_ptr<Level> level;
		public:
			EndReachedLambda( const std::shared_ptr<Level> &level );

			void Apply();
		};

	private:
		class SafetyNetLambda : public Lambda_1<Vector2>
		{
		private:
			std::shared_ptr<Level> level;
			Vector2 BL;
			Vector2 TR;
			Vector2 size;
			float xstep;
			StyleData::GroundType Type;

			bool Virgin;
			bool Used;
			bool BoxesOnly;
			bool InvertDraw;
			bool Invert;

		public:
			SafetyNetLambda( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, Vector2 size, float xstep, StyleData::GroundType Type, bool Virgin, bool Used, bool BoxesOnly, bool InvertDraw, bool Invert );

			void Apply( Vector2 pos );

		private:
			void InitializeInstanceFields();
		};

	private:
		class MakeInitialLambda : public Lambda_1<Vector2>
		{
		private:
			std::shared_ptr<Level> level;
			Vector2 size;
		public:
			MakeInitialLambda( const std::shared_ptr<Level> &level, Vector2 size );

			void Apply( Vector2 pos );
		};

	private:
		class Stage1RndFillLambda : public Lambda_1<Vector2>
		{
		private:
			std::shared_ptr<Level> level;
			Vector2 BL;
			Vector2 TR;
			Vector2 BL_Cutoff;

		public:
			Stage1RndFillLambda( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, Vector2 BL_Cutoff );

			void Apply( Vector2 pos );
		};

	private:
		class GeneralMinDistLambda : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			std::shared_ptr<Level> level;
		public:
			GeneralMinDistLambda( const std::shared_ptr<Level> &level );

			Vector2 Apply( Vector2 pos );
		};

	private:
		class CloseToStartLambda : public LambdaFunc_1<Bob*, bool>
		{
		public:
			CloseToStartLambda();

			bool Apply( const std::shared_ptr<Bob> &bob );
		};

	private:
		class IsLavaLambda : public LambdaFunc_1<BlockBase*, bool>
		{
		public:
			IsLavaLambda();

			bool Apply( const std::shared_ptr<BlockBase> &block );
		};

	private:
		class FindGuidLambda : public LambdaFunc_1<ObjectBase*, bool>
		{
		private:
			unsigned long long guid;
		public:
			FindGuidLambda( unsigned long long guid );

			bool Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class CleanObjectListLambda : public LambdaFunc_1<ObjectBase*, bool>
		{
		public:
			CleanObjectListLambda();

			bool Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class CleanDrawLayerLambda : public LambdaFunc_1<ObjectBase*, bool>
		{
		private:
			int layer;
		public:
			CleanDrawLayerLambda( int layer );

			bool Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class CleanBlockListLambda : public LambdaFunc_1<BlockBase*, bool>
		{
		public:
			CleanBlockListLambda();

			bool Apply( const std::shared_ptr<BlockBase> &obj );
		};

	public:
		enum LightLayers
		{
			LightLayers_FRONT_OF_LEVEL,
			LightLayers_FRONT_OF_EVERYTHING
		};
	private:
		class RemoveForeignLambda : public LambdaFunc_1<ObjectBase*, bool>
		{
		private:
			std::shared_ptr<Level> level;
		public:
			RemoveForeignLambda( const std::shared_ptr<Level> &level );

			bool Apply( const std::shared_ptr<ObjectBase> &obj );
		};

	private:
		class RemoveForeignBlockLambda : public LambdaFunc_1<BlockBase*, bool>
		{
		private:
			std::shared_ptr<Level> level;
		public:
			RemoveForeignBlockLambda( const std::shared_ptr<Level> &level );

			bool Apply( const std::shared_ptr<BlockBase> &obj );
		};

	public:
		class BaseMetric : public LambdaFunc_2<ObjectBase*, ObjectBase*, Vector2>
		{
		public:
			BaseMetric();

			Vector2 Apply( const std::shared_ptr<ObjectBase> &A, const std::shared_ptr<ObjectBase> &B );
		};
	private:
		class ConstLambda : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			Vector2 c;
		public:
			ConstLambda( Vector2 c );

			Vector2 Apply( Vector2 pos );
		};

	private:
		class SetBackLambda : public Lambda
		{
		private:
			std::shared_ptr<Level> level;
			int Steps;

		public:
			SetBackLambda( const std::shared_ptr<Level> &level, int Steps );

			void Apply();
		};

	private:
		class CleanupCoinsHelper : public LambdaFunc_1<Vector2, Vector2>
		{
		private:
			std::shared_ptr<Coin_Parameters> Params;

		public:
			CleanupCoinsHelper( const std::shared_ptr<Coin_Parameters> &Params );

			Vector2 Apply( Vector2 pos );
		};

	public:
		void CleanupCoins( Vector2 BL, Vector2 TR );



		/// <summary>
		/// Makes a CameraZone for an up or down level.
		/// </summary>
		/// <param name="Up">Whether the level is an up level or a down level</param>
		/// <param name="Height">The height of the level, always positive.</param>
		/// <returns></returns>
		std::shared_ptr<CameraZone> MakeVerticalCameraZone( LevelGeometry Geometry, float Height );

		/// <summary>
		/// Create the initial platforms the players start on.
		/// </summary>
		float MakeVerticalInitialPlats( const std::shared_ptr<StyleData> &Style );

	private:
		bool EndReached;
	public:
		bool MakeVertical( int Length, float Height, int StartPhsxStep, int ReturnEarly, const std::shared_ptr<MakeData> &makeData );

	private:
		float SetStepMultiplier( Vector2 &Size, Vector2 &Step );

		std::shared_ptr<NormalBlock> MakePillarBack( Vector2 p1, Vector2 p2 );


	public:
		void CleanupFireSpinners( Vector2 BL, Vector2 TR );
		void AutoFireSpinners();


		static Vector2 GetLadderSize( LadderType Type );

		void MakeLadder( const std::shared_ptr<PieceSeedData> &Piece );


		/// <summary>
		/// Whether a replay is available to be watched.
		/// </summary>
		const bool &getReplayAvailable() const;

		std::shared_ptr<SwarmBundle> MySwarmBundle;
		std::shared_ptr<Recording> CurrentRecording;
//C# TO C++ CONVERTER NOTE: The variable Recording was renamed since it is named the same as a user-defined type:
		bool Recording_Renamed;
	private:
		std::shared_ptr<ReplayGUI> MyReplayGUI;

	public:
		bool SingleOnly;

		bool NoCameraChange;
	private:
		void SaveCamera();
		void RestoreCamera();

	public:
		void SetReplay();

		void WatchReplay( bool SaveCurInfo );

		std::shared_ptr<Lambda> OnWatchComputer;

		void WatchComputer();
		void WatchComputer( bool GUI );

		bool EndOfReplay();

		std::shared_ptr<Lambda> OnEndReplay;
		void EndReplay();


		void EndComputerWatch();


		std::shared_ptr<MakeData> CurMakeData;
		const std::shared_ptr<StyleData> &getStyle() const;
		const std::shared_ptr<PieceSeedData> &getPieceSeed() const;
		LevelGeometry Geometry;

		bool CreationError;

		/// <summary>
		/// When true the position of the computer will be recorded.
		/// </summary>
		bool RecordPosition;

		int PlayMode, NumModes;

		bool SetToWatchMake;


		std::shared_ptr<LevelPiece> StartNewPiece( int Length, std::vector<Bob*> Computer );
		std::shared_ptr<LevelPiece> StartNewPiece( int Length, std::vector<Bob*> Computer, int NumBobs );

		void Clone( const std::shared_ptr<Level> &A );

		void Fill( Vector2 BL, Vector2 TR, float xstep, float ystep, const std::shared_ptr<Lambda_1<Vector2> > &FillFunc );
		void Fill( Vector2 BL, Vector2 TR, Vector2 xstep, float ystep, const std::shared_ptr<Lambda_1<Vector2> > &FillFunc );

		void FadeMusic();

		/// <summary>
		/// Give a bonus to player's score fore beating the level.
		/// Increment the number of levels the player has finished.
		/// </summary>
		void EndOfLevelBonus( const std::shared_ptr<PlayerData> &FinishingPlayer );
		void EndOfLevelBonus( const std::shared_ptr<PlayerData> &FinishingPlayer, bool IncrLevels );

		bool CoinsCountInStats;
		int NumCoins, NumBlobs, TotalCoinScore;
		bool Finished;
		/// <summary>
		/// Ends the playable level: players can no longer die, scores are finalized
		/// </summary>
		void EndLevel();

		/// <summary>
		/// Ends the playable level: players can no longer die
		/// </summary>
		void SoftEndLevel();


		/// <summary>
		/// Undoes the ending of the playable level: players can no longer die
		/// </summary>
		void UndoSoftEndLevel();

		std::shared_ptr<BlockBase> LastSafetyBlock;
		static const float SafetyNetHeight;
		std::shared_ptr<BlockBase> Stage1SafetyNet( Vector2 BL, Vector2 TR, Vector2 size, float xstep, StyleData::GroundType Type );
		std::shared_ptr<BlockBase> __LastBlock;

		std::shared_ptr<BlockBase> MadeBackBlock;
		/// <summary>
		/// Creates a door at the specified position, as well as a backdrop block.
		/// </summary>
		std::shared_ptr<Door> PlaceDoorOnBlock_Unlayered( Vector2 pos, const std::shared_ptr<BlockBase> &block, bool AddBackdrop );
		std::shared_ptr<Door> PlaceDoorOnBlock( Vector2 pos, const std::shared_ptr<BlockBase> &block, bool AddBackdrop );
		std::shared_ptr<Door> PlaceDoorOnBlock( Vector2 pos, const std::shared_ptr<BlockBase> &block, bool AddBackdrop, const std::shared_ptr<TileSet> &BackdropTileset );
		std::shared_ptr<Door> PlaceDoorOnBlock( Vector2 pos, const std::shared_ptr<BlockBase> &block, bool AddBackdrop, const std::shared_ptr<TileSet> &BackdropTileset, bool LayeredDoor );

	private:
		void SetBackblockProperties( const std::shared_ptr<NormalBlock> &backblock );

	public:
		static void SpreadStartPositions( const std::shared_ptr<LevelPiece> &piece, const std::shared_ptr<MakeData> &make, Vector2 pos, Vector2 SpanPer );

		/// <summary>
		/// Create the initial platforms the players start on.
		/// </summary>
		float MakeInitialPlats( Vector2 BL, Vector2 TR, const std::shared_ptr<SingleData> &Style );

	private:
		float MakeInitial_LandingZone( Vector2 &BL, Vector2 &TR, Vector2 &size );

		float MakeInitial_Spaceship( Vector2 &BL, Vector2 &TR, Vector2 &pos, std::shared_ptr<NormalBlock> &block );

		float MakeInitial_Normal( Vector2 BL, Vector2 TR, Vector2 size );

		std::shared_ptr<NormalBlock> __block_fromlambda;

	public:
		float VanillaFill( Vector2 BL, Vector2 TR, float width );
		float VanillaFill( Vector2 BL, Vector2 TR, float width, float ystep, const std::shared_ptr<Lambda_1<BlockBase*> > &PreInit, const std::shared_ptr<Lambda_1<BlockBase*> > &PostInit );

		float RandomBlocks( Vector2 BL, Vector2 TR, std::shared_ptr<MakeData> &makeData );

	private:
		static int CountToSleep;
		static void Sleep();
		static void CheckToSleep();

	public:
		void Stage1RndFill( Vector2 BL, Vector2 TR, Vector2 BL_Cutoff, float Sparsity );




		std::shared_ptr<CameraZone> MakeCameraZone();
		std::shared_ptr<CameraZone> MakeCameraZone( Vector2 Size );

		/// <summary>
		/// A BL bound for filling, offset by beginning platforms.
		/// </summary>
		Vector2 FillBL;

		/// <summary>
		/// The bounds of the random block fill.
		/// </summary>
		Vector2 Fill_TR, Fill_BL;

	private:
		static bool showdebug;
		static bool dodebug;
		void DEBUG( const std::wstring &str );

	public:
		void PREFILL();

		static std::wstring Pre1, Pre2, Post;
		static int Step1, Step2;

		float MaxRight, EndBuffer;
		int LastStep;
		bool MakeSingle( int Length, float MaxRight, float MaxLeft, int StartPhsxStep, int ReturnEarly, const std::shared_ptr<MakeData> &makeData );

	private:
		void Stage1( Vector2 BL_Bound, Vector2 TR_Bound, int Length );

		void Stage1Cleanup( Vector2 BL_Bound, Vector2 TR_Bound );

		void Stage2();

		void Stage2Cleanup( Vector2 BL_Bound, Vector2 TR_Bound );

	public:
		void OverlapCleanup();

		void BlockOverlapCleanup();

	private:
		void SpaceshipBlockCleanup();

		void RegularBlockCleanup();


		void InitMakeData( const std::shared_ptr<MakeData> &makeData );


	public:
		const std::shared_ptr<Recycler> &getRecycle() const;

		std::wstring Name;

	private:
		std::shared_ptr<Rand> _PrivateRnd;
	public:
		const std::shared_ptr<Rand> &getRnd() const;

		bool SuppressSounds;

		bool SuppressReplayButtons;

		bool LevelReleased;

		int NumAttempts, PieceAttempts;

		std::shared_ptr<BobPhsx> DefaultHeroType;

		/// <summary>
		/// True if the level generation algorithm returned early.
		/// </summary>
		bool ReturnedEarly;

		/// <summary>
		/// If true the user can load other levels from the start menu in this level.
		/// </summary>
		bool CanLoadLevels;

		/// <summary>
		/// If true the user can save this level.
		/// </summary>        
		bool CanSaveLevel;

		/// <summary>
		/// If true the player can watch the computer replay.
		/// Use the External bool if suppressing watch from outside the level class.
		/// </summary>
		bool CanWatchComputer;

		/// <summary>
		/// Whether the computer replay can be watched once the player is far from the spawn point.
		/// </summary>
		bool CanWatchComputerFromAfar_External;

		/// <summary>
		/// Whether watching the computer replay is enabled.
		/// </summary>
		bool WatchComputerEnabled();

		void CountReset();

		/// <summary>
		/// Whether all the players are close to the start and still alive.
		/// </summary>
		bool CloseToStart();

		bool CanWatchReplay;

	private:
		bool _PreventReset;
	public:
		const bool &getPreventReset() const;
		void setPreventReset( const bool &value );

		bool PreventHelp;

		bool FreezeCamera;

		/// <summary>
		/// Whether the level can be reset. Set 'SetToReset = True' to bypass.
		/// </summary>
		bool ResetEnabled();

		/// <summary>
		/// Make sure the lava in this level (if it exists) is pushed below the given y-coordinate.
		/// </summary>
		void PushLava( float y );
		void PushLava( float y, const std::shared_ptr<LavaBlock> &lava );

		std::shared_ptr<GameData> MyGame, MySourceGame;
		int TimeLimit;
		bool HaveTimeLimit;

		/// <summary>
		/// The length of time a timer is shown before the time limit expires.
		/// </summary>
		int TimeLimitTimerLength;

		/// <summary>
		/// Checks the current time limit. If it is almost up a timer is added to the GUI.
		/// </summary>
	private:
		void CheckTimeLimit();

		/// <summary>
		/// Holds the LevelSeedData that generated this level.
		/// </summary>
	public:
		std::shared_ptr<LevelSeedData> MyLevelSeed;

		Vector2 ModZoom;

	private:
		std::shared_ptr<EzTexture> LightTexture;
		std::shared_ptr<RenderTarget2D> LightRenderTarget;
	public:
		std::shared_ptr<ClosingCircle> Circle;
	private:
		std::shared_ptr<QuadClass> LightQuad;
	public:
		bool _UseLighting;

		std::shared_ptr<Background> MyBackground;
		std::shared_ptr<TileSet> MyTileSet;

		const std::shared_ptr<TileSet> &getMyTileSetInfo() const;
		const std::shared_ptr<TileSetInfo> &getInfo() const;

		int Par;

		std::shared_ptr<CameraZone> FinalCamZone;

		std::vector<LevelPiece*> LevelPieces;
		std::shared_ptr<LevelPiece> CurPiece;

		std::shared_ptr<ParticleEmitter> MainEmitter;

		int CurPhsxStep, StartPhsxStep;
		int DelayReset;

		const bool &getSetToReset() const;
		void setSetToReset( const bool &value );
		bool _SetToReset;

		/// <summary>
		/// Whether to count the next reset against the player (eg, deduct a life)
		/// </summary>
		bool FreeReset;

		bool ObjectsLocked;
		std::vector<ObjectBase*> Objects, AddedObjects;

		/// <summary>
		/// Active draw layer. Used while editing a level. This is the layer a new item is placed in.
		/// </summary>
		int CurEditorDrawLayer;

		static int NumDrawLayers;
		std::vector<bool> ShowDrawLayer;

		/// <summary>
		/// This is the layer the player replays are drawn on.
		/// </summary>
	private:
		static const int ReplayDrawLayer = 6;

		/// <summary>
		/// This is the layer drawn immediately after the last particles.
		/// </summary>
	public:
		static int AfterParticlesDrawLayer;

		/// <summary>
		/// This is the last draw layer drawn as part of the actual, physical level.
		/// </summary>
		static int LastInLevelDrawLayer;

		/// <summary>
		/// This draw layer is drawn after the Game class's post draw method.
		/// </summary>
		static int AfterPostDrawLayer;

	private:
		std::vector<std::vector<ObjectBase*> > DrawLayer;
	public:
		std::vector<ParticleEmitter*> ParticleEmitters;

		std::vector<BlockBase*> Blocks, AddedBlocks;
		std::vector<Bob*> Bobs, HoldPlayerBobs;
		Vector2 HoldCamPos;

		bool ShowCoinsInReplay;
		bool Watching, Replay, SuppressCheckpoints, GhostCheckpoints, MainReplayOnly, ReplayPaused;

		std::shared_ptr<Camera> MyCamera;
	private:
		std::shared_ptr<Camera> HoldCamera;
	public:
		const std::shared_ptr<Camera> &getMainCamera() const;
		void setMainCamera( const std::shared_ptr<Camera> &value );

		/// <summary>
		/// Event handler. Activates when the main camera is set to another camera instance.
		/// </summary>
		std::shared_ptr<Multicaster> OnCameraChange;

		Vector2 BL, TR;

		/// <summary>
		/// Whether to draw particles.
		/// </summary>
		bool NoParticles;

		Level();
		Level( bool ShowParticles );

	private:
		void Init( bool NoParticles );

	public:
		void Release();

		/// <summary>
		/// Get the final door of this level (the exit).
		/// </summary>
		const std::shared_ptr<Door> &getFinalDoor() const;

		/// <summary>
		/// Get the first door of this level (the entrance).
		/// </summary>
		const std::shared_ptr<Door> &getStartDoor() const;

		/// <summary>
		/// Find an object in this level by its code number.
		/// </summary>
		std::shared_ptr<ObjectBase> FindIObject( const std::wstring &Code1 );

		int GetPhsxStep();
		float GetIndependentPhsxStep();

		/// <summary>
		/// Returns the current working directory for where .lvl files are stored.
		/// Do not save here if you wish to override a .lvl file in future builds.
		/// </summary>
		static std::wstring DefaultLevelDirectory();

		/// <summary>
		/// Returns the directory where the source .lvl files are stored.
		/// Save here if you wish to override a .lvl file in future builds.
		/// </summary>
		/// <returns></returns>
		static std::wstring SourceLevelDirectory();

		/// <summary>
		/// Save the level to a .lvl file
		/// </summary>
		/// <param name="Bin">Whether the file is saved to the bin or the original project content directory.</param>
		void Save( const std::wstring &file, bool Bin );

	private:
		static int DrawLayerSortFunc( const std::shared_ptr<ObjectBase> &A, const std::shared_ptr<ObjectBase> &B );

		void SortDrawLayers();

	public:
		void Write( const std::shared_ptr<BinaryWriter> &writer );

		void Move( Vector2 shift );
		void Move( Vector2 shift, bool MoveBackground );

		/// <summary>
		/// After calling this function all coins that have been collected will no longer respawn when this level resets.
		/// This is used after a checkpoint is reached.
		/// </summary>
		void KeepCoinsDead();



		void StopRecording();

	private:
		void PrepareBundleToAddRecording();

	public:
		void AddCurRecording();

		/// <summary>
		/// Whether the level is allowed to record the players' attempts.
		/// </summary>
		bool AllowRecording;

		void CleanRecording();

		/// <summary>
		/// Starts a new player recording. Called at the beginning of the level and after each reset.
		/// </summary>
		void StartRecording();

		/// <summary>
		/// Gets the objects associated with a GUID.
		/// If the object is marked for deletion then null is returned.
		/// </summary>
		std::shared_ptr<ObjectBase> GuidToObj( unsigned long long guid );

		/// <summary>
		/// Gets the objects associated with a list of GUIDs.
		/// If the object is marked for deletion then null is returned.
		/// </summary>
		std::vector<ObjectBase*> GuidToObj( std::vector<unsigned long long> &guids );

		/// <summary>
		/// Gets the object associated with a GUID, even if that object is marked for deletion.
		/// If no such object exists then null is returned.
		/// </summary>
		std::shared_ptr<ObjectBase> LookupGUID( unsigned long long guid );

		void SetCurrentPiece( int LevelPieceIndex );
		void SetCurrentPiece( const std::shared_ptr<LevelPiece> &piece );

	private:
		void NonLambdaReset();

	public:
		bool BoxesOnly;
		void ResetAll( bool BoxesOnly );
		void ResetAll( bool BoxesOnly, bool AdditionalReset );
	private:
		void Reset_BoxesOnly( bool AdditionalReset );
		void Reset_Graphical( bool AdditionalReset );
		void __Reset( bool BoxesOnly, bool AdditionalReset );

		static std::shared_ptr<ObjectBase> FindParentObjectById( std::vector<ObjectBase*> &ObjectList, const std::shared_ptr<ObjectBase> &obj );

	public:
		void SynchObject( const std::shared_ptr<ObjectBase> &obj );

		void MoveUpOneSublayer( const std::shared_ptr<ObjectBase> &obj );

		void MoveToTopOfDrawLayer( const std::shared_ptr<ObjectBase> &obj );

		void MoveDownOneSublayer( const std::shared_ptr<ObjectBase> &obj );

		void ChangeObjectDrawLayer( const std::shared_ptr<ObjectBase> &obj, int DestinationLayer );

		void RelayerObject( const std::shared_ptr<ObjectBase> &Obj, int NewLayer, bool Front );

		//Dictionary<IObject, bool> AllObjects = new Dictionary<IObject, bool>();
		void AddObject( const std::shared_ptr<ObjectBase> &NewObject );
		void AddObject( const std::shared_ptr<ObjectBase> &NewObject, bool AddTimeStamp );

		/// <summary>
		/// Call to add an object back to the level,
		/// assuming it was never deleted from the main object/block list, nor the main dictionary.
		/// </summary>
		void ReAddObject( const std::shared_ptr<ObjectBase> &NewObject );

		std::vector<ObjectBase*> PreRecycleBin;

	private:
		void EmptyPreRecycleBin();

	public:
		void CleanAllObjectLists();

		void ClearAllObjectLists();

		void CleanObjectList();

		void CleanDrawLayers();

		void CleanBlockList();


		void AddBlock( const std::shared_ptr<BlockBase> &block );
		void AddBlock( const std::shared_ptr<BlockBase> &block, bool AddTimeStamp );


		void AddBob( const std::shared_ptr<Bob> &bob );

		/// <summary>
		/// While the level is drawing this is the current draw layer being drawn.
		/// </summary>
		int CurrentDrawLayer;

		void DrawGivenLayer( int i );

		void MakeClosingCircle();
		void MakeClosingCircle( float Frames, Vector2 Pos );
		void MakeClosingCircle( float Frames, const std::shared_ptr<IPos> &Pos );


		bool StickmanLighting;
		const bool &getUseLighting() const;
		void setUseLighting( const bool &value );

		void InitializeLighting();


	private:
		float BobLightRadius; //670
		static std::vector<float> BobLightRadiusByDifficulty;
	public:
		void SetBobLightRadius( int Difficulty );

		void FadeBobLightSourcesIn();

		LightLayers LightLayer;
	private:
		void PrepareLighting();

		void DrawLighting();

	public:
		void Draw();
		void Draw( bool DrawAll );
		void Draw( bool DrawAll, int StartLayer, int EndLayer );

		void FinalizeBlocks();

		void TagAll( int Tag );

		// Take all objects in a different level and add them
		void AddLevelBlocks( const std::shared_ptr<Level> &level );
		void AddLevelBlocks( const std::shared_ptr<Level> &level, int Tag );
		void AddLevelObjects( const std::shared_ptr<Level> &level );
		void AddLevelObjects( const std::shared_ptr<Level> &level, Vector2 p1, Vector2 p2 );
		void AddLevelObjects( const std::shared_ptr<Level> &level, int Tag );

		void AbsorbLevelVisuals( const std::shared_ptr<Level> &level );

		void SetBackground( const std::shared_ptr<Background> &background );

		void AbsorbLevel( const std::shared_ptr<Level> &level );

		// Remove all objects that belong to a different level
		void RemoveForeignObjects();



		/// <summary>
		/// Get a list of all objects in the level of a given type.
		/// </summary>
		std::vector<ObjectBase*> GetObjectList( ObjectType type );

	private:
		static std::shared_ptr<BaseMetric> DefaultMetric;

	public:
		void Cleanup( ObjectType type, Vector2 v );
		void Cleanup( ObjectType type, Vector2 v, Vector2 BL, Vector2 TR );

		void Cleanup( ObjectType type, const std::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc );
		void Cleanup( ObjectType type, const std::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR );
		void Cleanup( ObjectType type, const std::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR, const std::shared_ptr<LambdaFunc_2<ObjectBase*, ObjectBase*, Vector2> > &metric );

		void Cleanup( std::vector<ObjectBase*> &ObjList, const std::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR );
		// If MustBeDifferent is set, then only two objects of different types can force a deletion
		void Cleanup( std::vector<ObjectBase*> &ObjList, const std::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, bool MustBeDifferent, Vector2 BL, Vector2 TR );
		void Cleanup( std::vector<ObjectBase*> &ObjList, const std::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, bool MustBeDifferent, Vector2 BL, Vector2 TR, const std::shared_ptr<LambdaFunc_2<ObjectBase*, ObjectBase*, Vector2> > &metric );


		void Cleanup_xCoord( ObjectType ObjType, float MinDist );


	private:
		void CheckAgainst( const std::shared_ptr<ObjectBase> &obj, std::vector<ObjectBase*> &ObjList, const std::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, const std::shared_ptr<LambdaFunc_2<ObjectBase*, ObjectBase*, Vector2> > &metric, bool MustBeDifferent );

		void CheckAgainst_xCoord( const std::shared_ptr<ObjectBase> &obj, std::vector<ObjectBase*> &ObjList, float MinDist );

	public:
		void StartPlayerPlay();

	private:
		void EvolveParticles();

		void UpdateBlocks();

		void UpdateObjects();

		void UpdateBlocks2();

		void UpdateObjects2();

		void UpdateBobs();

	public:
		void PhsxStep( bool NotDrawing );
		void PhsxStep( bool NotDrawing, bool GUIPhsx );

	private:
		void SetIndependentStep();

	public:
		bool IndependentStepSetOnce;
		float IndependentPhsxStep, IndependentDeltaT;
	private:
		float Prev;

	public:
		TimeTypes TimeType;

		std::vector<ObjectBase*> ActiveObjectList;

	private:
		void CreateActiveObjectList();

		void UpdateActiveObjectList();

		/// <summary>
		/// Set the active object list to all objects in the level
		/// </summary>
		void ResetActiveObjectList();


	public:
		bool IsBetween( Vector2 Point, Vector2 p1, Vector2 p2 );

		void CountCoinsAndBlobs();

		void SetBack( int Steps );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_LEVEL
