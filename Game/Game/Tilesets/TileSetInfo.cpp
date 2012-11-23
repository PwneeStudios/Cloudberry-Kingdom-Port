#include "TileSetInfo.h"

namespace CloudberryKingdom
{
	void TileSetInfo::InitializeInstanceFields()
	{
		ScaleAll = 1;
		ScaleAllBlocks = 1;
		ScaleAllObjects = 1;
		AllowLava = true;
		ObstacleCutoff = 1000;
		ShiftStartDoor = 0;
		ShiftStartBlock = Vector2::Zero;
		AllowTopOnlyBlocks = true;
		Walls = std::make_shared<Wall::WallTileInfo>();
		Pendulums = std::make_shared<Pendulum::PendulumTileInfo>();
		LavaDrips = std::make_shared<LavaDrip::LavaDripTileInfo>();
		Serpents = std::make_shared<Serpent::SerpentTileInfo>();
		Firesnakes = std::make_shared<Firesnake::FiresnakeTileInfo>();
		Clouds = std::make_shared<Cloud::CloudTileInfo>();
		Elevators = std::make_shared<MovingPlatform::ElevatorTileInfo>();
		MovingBlocks = std::make_shared<MovingBlock::MovingBlockTileInfo>();
		BouncyBlocks = std::make_shared<BouncyBlock::BouncyBlockTileInfo>();
		FallingBlocks = std::make_shared<FallingBlock::FallingBlockTileInfo>();
		GhostBlocks = std::make_shared<GhostBlock::GhostBlockTileInfo>();
		Blobs = std::make_shared<FlyingBlob::FlyingBlobTileInfo>();
		Lasers = std::make_shared<Laser::LaserTileInfo>();
		SpikeyLines = std::make_shared<SpikeyLine::SpikeyLineTileInfo>();
		SpikeyGuys = std::make_shared<SpikeyGuy::SpikeyGuyTileInfo>();
		Boulders = std::make_shared<Boulder::BoulderTileInfo>();
		Spikes = std::make_shared<Spike::SpikeTileInfo>();
		Spinners = std::make_shared<FireSpinner::FireSpinnerTileInfo>();
		Fireballs = std::make_shared<Fireball::FireballTileInfo>();
		Checkpoints = std::make_shared<Checkpoint::CheckpointTileInfo>();
		Coins = std::make_shared<Coin::CoinTileInfo>();
		Doors = std::make_shared<Door::DoorTileInfo>();
	}
}