#ifndef _TILE_SET_INFO_H_
#define _TILE_SET_INFO_H_

#include <global_header.h>

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

		std::shared_ptr<Wall::WallTileInfo> Walls;

		std::shared_ptr<Pendulum::PendulumTileInfo> Pendulums;
		std::shared_ptr<LavaDrip::LavaDripTileInfo> LavaDrips;
		std::shared_ptr<Serpent::SerpentTileInfo> Serpents;
		std::shared_ptr<Firesnake::FiresnakeTileInfo> Firesnakes;

		std::shared_ptr<Cloud::CloudTileInfo> Clouds;
		std::shared_ptr<MovingPlatform::ElevatorTileInfo> Elevators;
		std::shared_ptr<MovingBlock::MovingBlockTileInfo> MovingBlocks;
		std::shared_ptr<BouncyBlock::BouncyBlockTileInfo> BouncyBlocks;
		std::shared_ptr<FallingBlock::FallingBlockTileInfo> FallingBlocks;
		std::shared_ptr<GhostBlock::GhostBlockTileInfo> GhostBlocks;
		std::shared_ptr<FlyingBlob::FlyingBlobTileInfo> Blobs;

		std::shared_ptr<Laser::LaserTileInfo> Lasers;
		std::shared_ptr<SpikeyLine::SpikeyLineTileInfo> SpikeyLines;
		std::shared_ptr<SpikeyGuy::SpikeyGuyTileInfo> SpikeyGuys;
		std::shared_ptr<Boulder::BoulderTileInfo> Boulders;
		std::shared_ptr<Spike::SpikeTileInfo> Spikes;
		std::shared_ptr<FireSpinner::FireSpinnerTileInfo> Spinners;
		std::shared_ptr<Fireball::FireballTileInfo> Fireballs;

		std::shared_ptr<Checkpoint::CheckpointTileInfo> Checkpoints;
		std::shared_ptr<Coin::CoinTileInfo> Coins;
		std::shared_ptr<Door::DoorTileInfo> Doors;

	
		void InitializeInstanceFields();

	
		TileSetInfo()
		{
			InitializeInstanceFields();
		}
	};

}

#endif
