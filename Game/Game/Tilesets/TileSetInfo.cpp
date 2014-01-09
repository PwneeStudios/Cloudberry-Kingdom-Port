#include "small_header.h"

#include "Game/Tilesets/TileSetInfo.h"

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
		ShiftStartBlock = Vector2();
		AllowTopOnlyBlocks = true;
		Walls = boost::make_shared<Wall::WallTileInfo>();
		Pendulums = boost::make_shared<Pendulum::PendulumTileInfo>();
		LavaDrips = boost::make_shared<LavaDrip::LavaDripTileInfo>();
		Serpents = boost::make_shared<Serpent::SerpentTileInfo>();
		Firesnakes = boost::make_shared<Firesnake::FiresnakeTileInfo>();
		Clouds = boost::make_shared<Cloud::CloudTileInfo>();
		Elevators = boost::make_shared<MovingPlatform::ElevatorTileInfo>();
		MovingBlocks = boost::make_shared<MovingBlock::MovingBlockTileInfo>();
		BouncyBlocks = boost::make_shared<BouncyBlock::BouncyBlockTileInfo>();
		FallingBlocks = boost::make_shared<FallingBlock::FallingBlockTileInfo>();
		GhostBlocks = boost::make_shared<GhostBlock::GhostBlockTileInfo>();
		Blobs = boost::make_shared<FlyingBlob::FlyingBlobTileInfo>();
		Lasers = boost::make_shared<Laser::LaserTileInfo>();
		SpikeyLines = boost::make_shared<SpikeyLine::SpikeyLineTileInfo>();
		SpikeyGuys = boost::make_shared<SpikeyGuy::SpikeyGuyTileInfo>();
		Boulders = boost::make_shared<Boulder::BoulderTileInfo>();
		Spikes = boost::make_shared<Spike::SpikeTileInfo>();
		Spinners = boost::make_shared<FireSpinner::FireSpinnerTileInfo>();
		Fireballs = boost::make_shared<Fireball::FireballTileInfo>();
		Checkpoints = boost::make_shared<Checkpoint::CheckpointTileInfo>();
		Coins = boost::make_shared<Coin::CoinTileInfo>();
		Doors = boost::make_shared<Door::DoorTileInfo>();
	}
}