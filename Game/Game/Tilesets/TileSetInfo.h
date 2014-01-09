#ifndef _TILE_SET_INFO_H_
#define _TILE_SET_INFO_H_

#include <small_header.h>

//#include "Core/Animation/AnimationData_Integer.h"
//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Game/Localization.h"
//#include "Game/Tilesets/Backgrounds/Background.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/Random.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Objects/In Game Objects/Blocks/Wall.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
//#include "Game/Objects/AutoGen.h"
#include "Game/Objects/Door/Door.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
#include "Game/Objects/In Game Objects/Blocks/FallingBlock.h"
#include "Game/Objects/In Game Objects/Blocks/GhostBlock.h"
#include "Game/Objects/In Game Objects/Blocks/MovingBlock.h"
#include "Game/Objects/In Game Objects/Blocks/MovingPlatform.h"
#include "Game/Objects/In Game Objects/Blocks/Pendulum.h"
#include "Game/Objects/In Game Objects/Grab/Checkpoint.h"
#include "Game/Objects/In Game Objects/Grab/Coin.h"
#include "Game/Objects/In Game Objects/Obstacles/Boulder.h"
#include "Game/Objects/In Game Objects/Obstacles/Cloud.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Firesnake.h"
#include "Game/Objects/In Game Objects/Obstacles/FireSpinner.h"
#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
#include "Game/Objects/In Game Objects/Obstacles/Laser.h"
#include "Game/Objects/In Game Objects/Obstacles/LavaDrip.h"
#include "Game/Objects/In Game Objects/Obstacles/Serpent.h"
#include "Game/Objects/In Game Objects/Obstacles/Spike.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine.h"
//#include "Game/Tilesets/BlockGroup.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct TileSetInfo
	{
	
		float ScaleAll, ScaleAllBlocks, ScaleAllObjects;

		bool AllowLava;
		float ObstacleCutoff;

		float ShiftStartDoor;
		Vector2 ShiftStartBlock;

		bool AllowTopOnlyBlocks;

		boost::shared_ptr<Wall::WallTileInfo> Walls;

		boost::shared_ptr<Pendulum::PendulumTileInfo> Pendulums;
		boost::shared_ptr<LavaDrip::LavaDripTileInfo> LavaDrips;
		boost::shared_ptr<Serpent::SerpentTileInfo> Serpents;
		boost::shared_ptr<Firesnake::FiresnakeTileInfo> Firesnakes;

		boost::shared_ptr<Cloud::CloudTileInfo> Clouds;
		boost::shared_ptr<MovingPlatform::ElevatorTileInfo> Elevators;
		boost::shared_ptr<MovingBlock::MovingBlockTileInfo> MovingBlocks;
		boost::shared_ptr<BouncyBlock::BouncyBlockTileInfo> BouncyBlocks;
		boost::shared_ptr<FallingBlock::FallingBlockTileInfo> FallingBlocks;
		boost::shared_ptr<GhostBlock::GhostBlockTileInfo> GhostBlocks;
		boost::shared_ptr<FlyingBlob::FlyingBlobTileInfo> Blobs;

		boost::shared_ptr<Laser::LaserTileInfo> Lasers;
		boost::shared_ptr<SpikeyLine::SpikeyLineTileInfo> SpikeyLines;
		boost::shared_ptr<SpikeyGuy::SpikeyGuyTileInfo> SpikeyGuys;
		boost::shared_ptr<Boulder::BoulderTileInfo> Boulders;
		boost::shared_ptr<Spike::SpikeTileInfo> Spikes;
		boost::shared_ptr<FireSpinner::FireSpinnerTileInfo> Spinners;
		boost::shared_ptr<Fireball::FireballTileInfo> Fireballs;

		boost::shared_ptr<Checkpoint::CheckpointTileInfo> Checkpoints;
		boost::shared_ptr<Coin::CoinTileInfo> Coins;
		boost::shared_ptr<Door::DoorTileInfo> Doors;

	
		void InitializeInstanceFields();

	
		TileSetInfo()
		{
			InitializeInstanceFields();
		}
	};

}

#endif
