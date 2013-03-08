#ifndef CLOUDBERRYKINGDOM_LEVEL
#define CLOUDBERRYKINGDOM_LEVEL

#include <global_header.h>

#include <Graphics/RenderTarget2D.h>

namespace CloudberryKingdom
{
	struct Level : public boost::enable_shared_from_this<Level>
	{
	
		struct ElementDistanceSquared : public LambdaFunc_1<boost::shared_ptr<BlockBase> , float>
		{
		
			Vector2 pos;

		
			ElementDistanceSquared( Vector2 pos );

			float Apply( const boost::shared_ptr<BlockBase> &element );
		};

	
		struct FindFirstRowLambda : public LambdaFunc_1<boost::shared_ptr<BlockBase> , bool>
		{
		
			FindFirstRowLambda();

			bool Apply( const boost::shared_ptr<BlockBase> &match );
		};

	
		struct MakeVerticalCleanupHelper : public LambdaFunc_1<Vector2, Vector2>
		{
		
			boost::shared_ptr<Level> level;

		
			MakeVerticalCleanupHelper( const boost::shared_ptr<Level> &level );

			Vector2 Apply( const Vector2 &pos );
		};

	
		struct FindLimitGeneralDensityLambda : public LambdaFunc_1<boost::shared_ptr<ObjectBase> , bool>
		{
		
			FindLimitGeneralDensityLambda();

			bool Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct EndReachedLambda : public Lambda
		{
		
			boost::shared_ptr<Level> level;
		
			EndReachedLambda( const boost::shared_ptr<Level> &level );

			void Apply();
		};

	
		struct SafetyNetLambda : public Lambda_1<Vector2>
		{
		
			boost::shared_ptr<Level> level;
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

		
			SafetyNetLambda( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, Vector2 size, float xstep, StyleData::GroundType Type, bool Virgin, bool Used, bool BoxesOnly, bool InvertDraw, bool Invert );

			void Apply( const Vector2 &pos );

		
			void InitializeInstanceFields();
		};

	
		struct MakeInitialLambda : public Lambda_1<Vector2>
		{
		
			boost::shared_ptr<Level> level;
			Vector2 size;
		
			MakeInitialLambda( const boost::shared_ptr<Level> &level, Vector2 size );

			void Apply( const Vector2 &pos );
		};

	
		struct Stage1RndFillLambda : public Lambda_1<Vector2>
		{
		
			boost::shared_ptr<Level> level;
			Vector2 BL;
			Vector2 TR;
			Vector2 BL_Cutoff;

		
			Stage1RndFillLambda( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, Vector2 BL_Cutoff );

			void Apply( const Vector2 &pos );
		};

	
		struct GeneralMinDistLambda : public LambdaFunc_1<Vector2, Vector2>
		{
		
			boost::shared_ptr<Level> level;
		
			GeneralMinDistLambda( const boost::shared_ptr<Level> &level );

			Vector2 Apply( const Vector2 &pos );
		};

	
		struct CloseToStartLambda : public LambdaFunc_1<boost::shared_ptr<Bob> , bool>
		{
		
			CloseToStartLambda();

			bool Apply( const boost::shared_ptr<Bob> &bob );
		};

	
		struct IsLavaLambda : public LambdaFunc_1<boost::shared_ptr<BlockBase> , bool>
		{
		
			IsLavaLambda();

			bool Apply( const boost::shared_ptr<BlockBase> &block );
		};

	
		struct FindGuidLambda : public LambdaFunc_1<boost::shared_ptr<ObjectBase> , bool>
		{
		
			unsigned long long guid;
		
			FindGuidLambda( unsigned long long guid );

			bool Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct CleanObjectListLambda : public LambdaFunc_1<boost::shared_ptr<ObjectBase> , bool>
		{
		
			CleanObjectListLambda();

			bool Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct CleanDrawLayerLambda : public LambdaFunc_1<boost::shared_ptr<ObjectBase> , bool>
		{
		
			int layer;
		
			CleanDrawLayerLambda( int layer );

			bool Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct CleanBlockListLambda : public LambdaFunc_1<boost::shared_ptr<BlockBase> , bool>
		{
		
			CleanBlockListLambda();

			bool Apply( const boost::shared_ptr<BlockBase> &obj );
		};

	
		enum LightLayers
		{
			LightLayers_FRONT_OF_LEVEL,
			LightLayers_FRONT_OF_EVERYTHING
		};
	
		struct RemoveForeignLambda : public LambdaFunc_1<boost::shared_ptr<ObjectBase> , bool>
		{
		
			boost::shared_ptr<Level> level;
		
			RemoveForeignLambda( const boost::shared_ptr<Level> &level );

			bool Apply( const boost::shared_ptr<ObjectBase> &obj );
		};

	
		struct RemoveForeignBlockLambda : public LambdaFunc_1<boost::shared_ptr<BlockBase> , bool>
		{
		
			boost::shared_ptr<Level> level;
		
			RemoveForeignBlockLambda( const boost::shared_ptr<Level> &level );

			bool Apply( const boost::shared_ptr<BlockBase> &obj );
		};

	
		struct BaseMetric : public LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2>
		{
		
			BaseMetric();

			Vector2 Apply( const boost::shared_ptr<ObjectBase> &A, const boost::shared_ptr<ObjectBase> &B );
		};
	
		struct ConstLambda : public LambdaFunc_1<Vector2, Vector2>
		{
		
			Vector2 c;
		
			ConstLambda( Vector2 c );

			Vector2 Apply( const Vector2 &pos );
		};

	
		struct SetBackLambda : public Lambda
		{
		
			boost::shared_ptr<Level> level;
			int Steps;

		
			SetBackLambda( const boost::shared_ptr<Level> &level, int Steps );

			void Apply();
		};

	
		struct CleanupCoinsHelper : public LambdaFunc_1<Vector2, Vector2>
		{
		
			boost::shared_ptr<Coin_Parameters> Params;

		
			CleanupCoinsHelper( const boost::shared_ptr<Coin_Parameters> &Params );

			Vector2 Apply( const Vector2 &pos );
		};

	
		void CleanupCoins( Vector2 BL, Vector2 TR );



		/// <summary>
		/// Makes a CameraZone for an up or down level.
		/// </summary>
		/// <param name="Up">Whether the level is an up level or a down level</param>
		/// <param name="Height">The height of the level, always positive.</param>
		/// <returns></returns>
		boost::shared_ptr<CameraZone> MakeVerticalCameraZone( LevelGeometry Geometry, float Height );

		/// <summary>
		/// Create the initial platforms the players start on.
		/// </summary>
		float MakeVerticalInitialPlats( const boost::shared_ptr<StyleData> &Style );

	
		bool EndReached;
	
		bool MakeVertical( int Length, float Height, int StartPhsxStep, int ReturnEarly, const boost::shared_ptr<MakeData> &makeData );

	
		float SetStepMultiplier( Vector2 &Size, Vector2 &Step );

		boost::shared_ptr<NormalBlock> MakePillarBack( Vector2 p1, Vector2 p2 );


	
		void CleanupFireSpinners( Vector2 BL, Vector2 TR );
		void AutoFireSpinners();


		static Vector2 GetLadderSize( LadderType Type );

		void MakeLadder( const boost::shared_ptr<PieceSeedData> &Piece );


		/// <summary>
		/// Whether a replay is available to be watched.
		/// </summary>
		const bool getReplayAvailable() const;

		boost::shared_ptr<SwarmBundle> MySwarmBundle;
		boost::shared_ptr<Recording> CurrentRecording;
//C# TO C++ CONVERTER NOTE: The variable Recording was renamed since it is named the same as a user-defined type:
		bool Recording_Renamed;
	
		boost::shared_ptr<ReplayGUI> MyReplayGUI;

	
		bool SingleOnly;

		bool NoCameraChange;
	
		void SaveCamera();
		void RestoreCamera();

	
		void SetReplay();

		void WatchReplay( bool SaveCurInfo );

		boost::shared_ptr<Lambda> OnWatchComputer;

		void WatchComputer();
		void WatchComputer( bool GUI );

		bool EndOfReplay();

		boost::shared_ptr<Lambda> OnEndReplay;
		void EndReplay();


		void EndComputerWatch();


		boost::shared_ptr<MakeData> CurMakeData;
		const boost::shared_ptr<StyleData> &getStyle() const;
		const boost::shared_ptr<PieceSeedData> &getPieceSeed() const;
		LevelGeometry Geometry;

		bool CreationError;

		/// <summary>
		/// When true the position of the computer will be recorded.
		/// </summary>
		bool RecordPosition;

		int PlayMode, NumModes;

		bool SetToWatchMake;


		boost::shared_ptr<LevelPiece> StartNewPiece( int Length, BobVec Computer );
		boost::shared_ptr<LevelPiece> StartNewPiece( int Length, BobVec Computer, int NumBobs );

		void Clone( const boost::shared_ptr<Level> &A );

		void Fill( Vector2 BL, Vector2 TR, float xstep, float ystep, const boost::shared_ptr<Lambda_1<Vector2> > &FillFunc );
		void Fill( Vector2 BL, Vector2 TR, Vector2 xstep, float ystep, const boost::shared_ptr<Lambda_1<Vector2> > &FillFunc );

		void FadeMusic();

		/// <summary>
		/// Give a bonus to player's score fore beating the level.
		/// Increment the number of levels the player has finished.
		/// </summary>
		void EndOfLevelBonus( const boost::shared_ptr<PlayerData> &FinishingPlayer );
		void EndOfLevelBonus( const boost::shared_ptr<PlayerData> &FinishingPlayer, bool IncrLevels );

		bool CoinsCountInStats;
		int NumCoins, NumBlobs, TotalCoinScore, NumObstacles;
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

		boost::shared_ptr<BlockBase> LastSafetyBlock;
		static const float SafetyNetHeight;
		boost::shared_ptr<BlockBase> Stage1SafetyNet( Vector2 BL, Vector2 TR, Vector2 size, float xstep, StyleData::GroundType Type );
		boost::shared_ptr<BlockBase> __LastBlock;

		boost::shared_ptr<BlockBase> MadeBackBlock;
		/// <summary>
		/// Creates a door at the specified position, as well as a backdrop block.
		/// </summary>
		boost::shared_ptr<Door> PlaceDoorOnBlock_Unlayered( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop );
		boost::shared_ptr<Door> PlaceDoorOnBlock( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop );
		boost::shared_ptr<Door> PlaceDoorOnBlock( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop, const boost::shared_ptr<TileSet> &BackdropTileset );
		boost::shared_ptr<Door> PlaceDoorOnBlock( Vector2 pos, const boost::shared_ptr<BlockBase> &block, bool AddBackdrop, const boost::shared_ptr<TileSet> &BackdropTileset, bool LayeredDoor );

	
		void SetBackblockProperties( const boost::shared_ptr<NormalBlock> &backblock );

	
		static void SpreadStartPositions( const boost::shared_ptr<LevelPiece> &piece, const boost::shared_ptr<MakeData> &make, Vector2 pos, Vector2 SpanPer );

		/// <summary>
		/// Create the initial platforms the players start on.
		/// </summary>
		float MakeInitialPlats( Vector2 BL, Vector2 TR, const boost::shared_ptr<SingleData> &Style );

	
		float MakeInitial_LandingZone( Vector2 &BL, Vector2 &TR, Vector2 &size );

		float MakeInitial_Spaceship( Vector2 &BL, Vector2 &TR, Vector2 &pos, boost::shared_ptr<NormalBlock> &block );

		float MakeInitial_Normal( Vector2 BL, Vector2 TR, Vector2 size );

		boost::shared_ptr<NormalBlock> __block_fromlambda;

	
		float VanillaFill( Vector2 BL, Vector2 TR, float width );
		float VanillaFill( Vector2 BL, Vector2 TR, float width, float ystep, const boost::shared_ptr<Lambda_1<boost::shared_ptr<BlockBase> > > &PreInit, const boost::shared_ptr<Lambda_1<boost::shared_ptr<BlockBase> > > &PostInit );

		float RandomBlocks( Vector2 BL, Vector2 TR, boost::shared_ptr<MakeData> &makeData );

	
		static int CountToSleep;
		static void Sleep();
		static void CheckToSleep();

	
		void Stage1RndFill( Vector2 BL, Vector2 TR, Vector2 BL_Cutoff, float Sparsity );




		boost::shared_ptr<CameraZone> MakeCameraZone();
		boost::shared_ptr<CameraZone> MakeCameraZone( Vector2 Size );

		/// <summary>
		/// A BL bound for filling, offset by beginning platforms.
		/// </summary>
		Vector2 FillBL;

		/// <summary>
		/// The bounds of the random block fill.
		/// </summary>
		Vector2 Fill_TR, Fill_BL;

	
		static bool showdebug;
		static bool dodebug;
		void DEBUGMsg( const std::wstring &str );

	
		void PREFILL();

		static std::wstring Pre1, Pre2, Post;
		static int Step1, Step2;

		float MaxRight, EndBuffer;
		int LastStep;
		bool MakeSingle( int Length, float MaxRight, float MaxLeft, int StartPhsxStep, int ReturnEarly, const boost::shared_ptr<MakeData> &makeData );

	
		void Stage1( Vector2 BL_Bound, Vector2 TR_Bound, int Length );

		void Stage1Cleanup( Vector2 BL_Bound, Vector2 TR_Bound );

		void Stage2();

		void Stage2Cleanup( Vector2 BL_Bound, Vector2 TR_Bound );

	
		void OverlapCleanup();

		void BlockOverlapCleanup();

	
		void SpaceshipBlockCleanup();

		void RegularBlockCleanup();


		void InitMakeData( const boost::shared_ptr<MakeData> &makeData );


	
		const boost::shared_ptr<Recycler> getRecycle() const;

		std::wstring Name;

	
		boost::shared_ptr<Rand> _PrivateRnd;
	
		const boost::shared_ptr<Rand> &getRnd();

		bool SuppressSounds;

		bool SuppressReplayButtons;

		bool LevelReleased;

		int NumAttempts, PieceAttempts;

		boost::shared_ptr<BobPhsx> DefaultHeroType;

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
		/// Use the External bool if suppressing watch from outside the level struct.
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

	
		bool _PreventReset;
	
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
		void PushLava( float y, const boost::shared_ptr<LavaBlock> &lava );

		boost::shared_ptr<GameData> MyGame, MySourceGame;
		int TimeLimit;
		bool HaveTimeLimit;

		/// <summary>
		/// The length of time a timer is shown before the time limit expires.
		/// </summary>
		int TimeLimitTimerLength;

		/// <summary>
		/// Checks the current time limit. If it is almost up a timer is added to the GUI.
		/// </summary>
	
		void CheckTimeLimit();

		/// <summary>
		/// Holds the LevelSeedData that generated this level.
		/// </summary>
	
		boost::shared_ptr<LevelSeedData> MyLevelSeed;

		Vector2 ModZoom;

	
		boost::shared_ptr<EzTexture> LightTexture;
		boost::shared_ptr<RenderTarget2D> LightRenderTarget;
	
		boost::shared_ptr<ClosingCircle> Circle;
	
		boost::shared_ptr<QuadClass> LightQuad;
	
		bool _UseLighting;

		boost::shared_ptr<Background> MyBackground;
		boost::shared_ptr<TileSet> MyTileSet;

		const boost::shared_ptr<TileSet> &getMyTileSetInfo() const;
		const boost::shared_ptr<TileSetInfo> &getInfo() const;

		int Par;

		boost::shared_ptr<CameraZone> FinalCamZone;

		std::vector<boost::shared_ptr<LevelPiece> > LevelPieces;
		boost::shared_ptr<LevelPiece> CurPiece;

		boost::shared_ptr<ParticleEmitter> MainEmitter;

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
		ObjectVec Objects, AddedObjects;

		/// <summary>
		/// Active draw layer. Used while editing a level. This is the layer a new item is placed in.
		/// </summary>
		int CurEditorDrawLayer;

		static int NumDrawLayers;
		std::vector<bool> ShowDrawLayer;

		/// <summary>
		/// This is the layer the player replays are drawn on.
		/// </summary>
	
		static const int ReplayDrawLayer = 6;

		/// <summary>
		/// This is the layer drawn immediately after the last particles.
		/// </summary>
	
		static int AfterParticlesDrawLayer;

		/// <summary>
		/// This is the last draw layer drawn as part of the actual, physical level.
		/// </summary>
		static int LastInLevelDrawLayer;

		/// <summary>
		/// This draw layer is drawn after the Game struct's post draw method.
		/// </summary>
		static int AfterPostDrawLayer;

	
		std::vector<ObjectVec > DrawLayer;
	
		std::vector<boost::shared_ptr<ParticleEmitter> > ParticleEmitters;

		BlockVec Blocks, AddedBlocks;
		BobVec Bobs, HoldPlayerBobs;
		Vector2 HoldCamPos;

		bool ShowCoinsInReplay;
		bool Watching, Replay, SuppressCheckpoints, GhostCheckpoints, MainReplayOnly, ReplayPaused;

		boost::shared_ptr<Camera> MyCamera;
	
		boost::shared_ptr<Camera> HoldCamera;
	
		const boost::shared_ptr<Camera> &getMainCamera() const;
		void setMainCamera( const boost::shared_ptr<Camera> &value );

		/// <summary>
		/// Event handler. Activates when the main camera is set to another camera instance.
		/// </summary>
		boost::shared_ptr<Multicaster> OnCameraChange;

		Vector2 BL, TR;

		/// <summary>
		/// Whether to draw particles.
		/// </summary>
		bool NoParticles;

		Level();
		Level( bool ShowParticles );

	
		void Init( bool NoParticles );

	
		void Release();

		/// <summary>
		/// Get the final door of this level (the exit).
		/// </summary>
		const boost::shared_ptr<Door> getFinalDoor() const;

		/// <summary>
		/// Get the first door of this level (the entrance).
		/// </summary>
		const boost::shared_ptr<Door> getStartDoor() const;

		/// <summary>
		/// Find an object in this level by its code number.
		/// </summary>
		const boost::shared_ptr<ObjectBase> FindIObject( const std::wstring &Code1 ) const;

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

	
		static int DrawLayerSortFunc( const boost::shared_ptr<ObjectBase> &A, const boost::shared_ptr<ObjectBase> &B );

		void SortDrawLayers();

	
		void Write( const boost::shared_ptr<BinaryWriter> &writer );

		void Move( Vector2 shift );
		void Move( Vector2 shift, bool MoveBackground );

		/// <summary>
		/// After calling this function all coins that have been collected will no longer respawn when this level resets.
		/// This is used after a checkpoint is reached.
		/// </summary>
		void KeepCoinsDead();



		void StopRecording();

	
		void PrepareBundleToAddRecording();

	
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
		boost::shared_ptr<ObjectBase> GuidToObj( unsigned long long guid );

		/// <summary>
		/// Gets the objects associated with a list of GUIDs.
		/// If the object is marked for deletion then null is returned.
		/// </summary>
		ObjectVec GuidToObj( std::vector<unsigned long long> &guids );

		/// <summary>
		/// Gets the object associated with a GUID, even if that object is marked for deletion.
		/// If no such object exists then null is returned.
		/// </summary>
		boost::shared_ptr<ObjectBase> LookupGUID( unsigned long long guid );

		void SetCurrentPiece( int LevelPieceIndex );
		void SetCurrentPiece( const boost::shared_ptr<LevelPiece> &piece );

	
		void NonLambdaReset();

	
		bool BoxesOnly;
		void ResetAll( bool BoxesOnly );
		void ResetAll( bool BoxesOnly, bool AdditionalReset );
	
		void Reset_BoxesOnly( bool AdditionalReset );
		void Reset_Graphical( bool AdditionalReset );
		void __Reset( bool BoxesOnly, bool AdditionalReset );

		static boost::shared_ptr<ObjectBase> FindParentObjectById( ObjectVec &ObjectList, const boost::shared_ptr<ObjectBase> &obj );

	
		void SynchObject( const boost::shared_ptr<ObjectBase> &obj );

		void MoveUpOneSublayer( const boost::shared_ptr<ObjectBase> &obj );

		void MoveToTopOfDrawLayer( const boost::shared_ptr<ObjectBase> &obj );

		void MoveDownOneSublayer( const boost::shared_ptr<ObjectBase> &obj );

		void ChangeObjectDrawLayer( const boost::shared_ptr<ObjectBase> &obj, int DestinationLayer );

		void RelayerObject( const boost::shared_ptr<ObjectBase> &Obj, int NewLayer, bool Front );

		//Dictionary<IObject, bool> AllObjects = new Dictionary<IObject, bool>();
		void AddObject( const boost::shared_ptr<ObjectBase> &NewObject );
		void AddObject( const boost::shared_ptr<ObjectBase> &NewObject, bool AddTimeStamp );

		/// <summary>
		/// Call to add an object back to the level,
		/// assuming it was never deleted from the main object/block list, nor the main dictionary.
		/// </summary>
		void ReAddObject( const boost::shared_ptr<ObjectBase> &NewObject );

		ObjectVec PreRecycleBin;

	
		void EmptyPreRecycleBin();

	
		void CleanAllObjectLists();

		void ClearAllObjectLists();

		void CleanObjectList();

		void CleanDrawLayers();

		void CleanBlockList();


		void AddBlock( const boost::shared_ptr<BlockBase> &block );
		void AddBlock( const boost::shared_ptr<BlockBase> &block, bool AddTimeStamp );


		void AddBob( const boost::shared_ptr<Bob> &bob );

		/// <summary>
		/// While the level is drawing this is the current draw layer being drawn.
		/// </summary>
		int CurrentDrawLayer;

		void DrawGivenLayer( int i );

		void MakeClosingCircle();
		void MakeClosingCircle( float Frames, Vector2 Pos );
		void MakeClosingCircle( float Frames, const boost::shared_ptr<IPos> &Pos );


		bool StickmanLighting;
		const bool &getUseLighting() const;
		void setUseLighting( const bool &value );

		void InitializeLighting();


	
		float BobLightRadius; //670
		static std::vector<float> BobLightRadiusByDifficulty;
	
		void SetBobLightRadius( int Difficulty );

		void FadeBobLightSourcesIn();

		LightLayers LightLayer;
	
		void PrepareLighting();

		void DrawLighting();

	
		void Draw();
		void Draw( bool DrawAll );
		void Draw( bool DrawAll, int StartLayer, int EndLayer );

		void FinalizeBlocks();

		void TagAll( int Tag );

		// Take all objects in a different level and add them
		void AddLevelBlocks( const boost::shared_ptr<Level> &level );
		void AddLevelBlocks( const boost::shared_ptr<Level> &level, int Tag );
		void AddLevelObjects( const boost::shared_ptr<Level> &level );
		void AddLevelObjects( const boost::shared_ptr<Level> &level, Vector2 p1, Vector2 p2 );
		void AddLevelObjects( const boost::shared_ptr<Level> &level, int Tag );

		void AbsorbLevelVisuals( const boost::shared_ptr<Level> &level );

		void SetBackground( const boost::shared_ptr<Background> &background );

		void AbsorbLevel( const boost::shared_ptr<Level> &level );

		// Remove all objects that belong to a different level
		void RemoveForeignObjects();



		/// <summary>
		/// Get a list of all objects in the level of a given type.
		/// </summary>
		ObjectVec GetObjectList( ObjectType type );

	
		static boost::shared_ptr<BaseMetric> DefaultMetric;

	
		void Cleanup( ObjectType type, Vector2 v );
		void Cleanup( ObjectType type, Vector2 v, Vector2 BL, Vector2 TR );

		void Cleanup( ObjectType type, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc );
		void Cleanup( ObjectType type, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR );
		void Cleanup( ObjectType type, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR, const boost::shared_ptr<LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2> > &metric );

		void Cleanup( const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, Vector2 BL, Vector2 TR );
		// If MustBeDifferent is set, then only two objects of different types can force a deletion
		void Cleanup( const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, bool MustBeDifferent, Vector2 BL, Vector2 TR );
		void Cleanup( const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, bool MustBeDifferent, Vector2 BL, Vector2 TR, const boost::shared_ptr<LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2> > &metric );


		void Cleanup_xCoord( ObjectType ObjType, float MinDist );


	
		void CheckAgainst( const boost::shared_ptr<ObjectBase> &obj, const ObjectVec &ObjList, const boost::shared_ptr<LambdaFunc_1<Vector2, Vector2> > &MinDistFunc, const boost::shared_ptr<LambdaFunc_2<boost::shared_ptr<ObjectBase> , boost::shared_ptr<ObjectBase> , Vector2> > &metric, bool MustBeDifferent );

		void CheckAgainst_xCoord( const boost::shared_ptr<ObjectBase> &obj, const ObjectVec &ObjList, float MinDist );

	
		void StartPlayerPlay();

	
		void EvolveParticles();

		void UpdateBlocks();

		void UpdateObjects();

		void UpdateBlocks2();

		void UpdateObjects2();

		void UpdateBobs();

	
		void CalcObstaclsSeen();

		void PhsxStep( bool NotDrawing );
		void PhsxStep( bool NotDrawing, bool GUIPhsx );

	
		void SetIndependentStep();

	
		bool IndependentStepSetOnce;
		float IndependentPhsxStep, IndependentDeltaT;
	
		float Prev;

	
		TimeTypes TimeType;

		ObjectVec* ActiveObjectList;
		ObjectVec _ActiveObjectList_BoxesOnly;

	
		void CreateActiveObjectList();

		void UpdateActiveObjectList();

		/// <summary>
		/// Set the active object list to all objects in the level
		/// </summary>
		void ResetActiveObjectList();


	
		bool IsBetween( Vector2 Point, Vector2 p1, Vector2 p2 );

		void CountCoinsAndBlobs();

		void SetBack( int Steps );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_LEVEL
