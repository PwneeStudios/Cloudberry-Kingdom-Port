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
