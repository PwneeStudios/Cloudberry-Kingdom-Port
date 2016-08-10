#ifndef MAKE_DATA
#define MAKE_DATA

#include <small_header.h>

//#include "Core/FancyVector2.h"
#include "Core/PhsxData.h"
//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Tilesets/Backgrounds/Background.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Particle Effects/ParticleEmitter.h"
//#include "Core/Texture/EzTexture.h"
//#include "Core/Tools/CoreMath.h"
//#include "Core/Tools/Random.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Games/GameType.h"
//#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
//#include "Game/Level/ClosingCircle.h"
//#include "Game/Level/LevelPiece.h"
//#include "Game/Level/Make/LockableBool.h"
//#include "Game/Level/Make/DifficultyHelper.h"
//#include "Game/Level/Make/Generators.h"
//#include "Game/Level/Make/LevelSeedData.h"
//#include "Game/Level/Make/PieceSeedData.h"
//#include "Game/Level/Make/MakePiece/MakeThing.h"
//#include "Game/Level/Make/MakePiece/MakeSingle/MakeFinalDoor.h"
//#include "Game/Level/Make/MakePiece/MakeSingle/MakeFinalDoor_Float.h"
//#include "Game/Level/Make/MakePiece/MakeVertical/MakeFinalDoor_Vertical.h"
//#include "Game/Level/Make/MakePiece/MakeVertical/MakeDarkBottom.h"
//#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
//#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
//#include "Game/Level/Make/Parameters/StyleData/UpData.h"
//#include "Game/Level/Make/Parameters/StyleData/OneScreenData.h"
//#include "Game/Level/Make/Parameters/StyleData/SingleData.h"
//#include "Game/Level/Replays/Recording.h"
//#include "Game/Level/Replays/ReplayGUI.h"
//#include "Game/Level/Replays/SwarmBundle.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/AutoGen.h"
#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Bob/BobLink.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Simple.h"
//#include "Game/Objects/In Game Objects/BaseClasses/_Death.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/Lava.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Grab/Coin.h"
//#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"
//#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter.h"
//#include "Game/Objects/In Game Objects/Obstacles/FireSpinner.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
//#include "Game/Objects/Special/CameraZone.h"
//#include "Game/Player/ColorSchemeManager.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Player/Hero Physics/Big.h"
//#include "Game/Player/Hero Physics/Box.h"
//#include "Game/Player/Hero Physics/Double.h"
//#include "Game/Player/Hero Physics/Jetman.h"
//#include "Game/Player/Hero Physics/Meat.h"
//#include "Game/Player/Hero Physics/Rocketbox.h"
//#include "Game/Player/Hero Physics/Small.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct MakeData : public boost::enable_shared_from_this<MakeData>
	{

	
		Vector2 TRBobMoveZone, BLBobMoveZone;

		boost::shared_ptr<RichLevelGenData> GenData;

		/// <summary>
		/// The PieceSeedData from which the current MakeData's level is being made
		/// </summary>
		boost::shared_ptr<PieceSeedData> PieceSeed;

		/// <summary>
		/// The LevelSeed which spawned the creation of this level.
		/// </summary>
		boost::shared_ptr<LevelSeedData> LevelSeed;

		bool ComputerWaitAtStart;
		std::vector<int> ComputerWaitAtStartLength;
		float SparsityMultiplier;

		int NumInitialBobs;

		/// <summary>
		/// Minimum number of start positions to make, regardless of the number of computer AIs
		/// </summary>
		int MinStartPositionsToMake;

		Vector2 CamStartPos;
		std::vector<PhsxData> Start;
		std::vector<Vector2> CheckpointShift;
		std::vector<Bob::BobMove> MoveData;

		bool InitialPlats, InitialCamZone, FinalPlats;
		bool SkinnyStart;

		bool SetTRCamBound;

		/// <summary>
		/// If true the top has extra safety blocks and extra stage 1 fill, to mimick the bottom.
		/// Used, in particular, for Spaceship hero.
		/// </summary>
		bool TopLikeBottom;

		/// <summary>
		/// If true the top has extra safety blocks and extra stage 1 fill, to mimick the bottom.
		/// Blocks are thinner than normal.
		/// Used, in particular, for Invert bob.
		/// </summary>
		bool TopLikeBottom_Thin;

		/// <summary>
		/// If true then blocks will not be modified (no shifting of bottom, no top only).
		/// </summary>
		bool BlocksAsIs;

		/// <summary>
		/// When making a multi-piece level, this index specifies which piece the MakeData refers to.
		/// </summary>
		int Index;

		/// <summary>
		/// When making a multi-piece level, this index specifies how many pieces are being made.
		/// </summary>
		int OutOf;

		void Release();

		void Init( const boost::shared_ptr<PieceSeedData> &data );

		BobVec MakeBobs( const boost::shared_ptr<Level> &level );

		boost::shared_ptr<LevelPiece> MakeLevelPiece( const boost::shared_ptr<Level> &level, BobVec bobs, int Length, int StartPhsxStep );

	
		void InitializeInstanceFields();

	
		MakeData();
	};
}

#endif
