#ifndef TILESET
#define TILESET

#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class Pendulum;
}

namespace CloudberryKingdom
{
	class LavaDrip;
}

namespace CloudberryKingdom
{
	class Serpent;
}

namespace CloudberryKingdom
{
	class Firesnake;
}

namespace CloudberryKingdom
{
	class Cloud;
}

namespace CloudberryKingdom
{
	class MovingPlatform;
}

namespace CloudberryKingdom
{
	class MovingBlock;
}

namespace CloudberryKingdom
{
	class BouncyBlock;
}

namespace CloudberryKingdom
{
	class FallingBlock;
}

namespace CloudberryKingdom
{
	class GhostBlock;
}

namespace CloudberryKingdom
{
	class FlyingBlob;
}

namespace CloudberryKingdom
{
	class Laser;
}

namespace CloudberryKingdom
{
	class SpikeyLine;
}

namespace CloudberryKingdom
{
	class SpikeyGuy;
}

namespace CloudberryKingdom
{
	class Boulder;
}

namespace CloudberryKingdom
{
	class Spike;
}

namespace CloudberryKingdom
{
	class FireSpinner;
}

namespace CloudberryKingdom
{
	class Fireball;
}

namespace CloudberryKingdom
{
	class Checkpoint;
}

namespace CloudberryKingdom
{
	class Coin;
}

namespace CloudberryKingdom
{
	class Door;
}

namespace CloudberryKingdom
{
	class BlockGroup;
}

namespace CloudberryKingdom
{
	class PieceQuad;
}

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class Rand;
}

namespace CloudberryKingdom
{
	class BackgroundTemplate;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class TileInfoBase
	{
	public:
		std::shared_ptr<SpriteInfo> Icon;
		std::shared_ptr<SpriteInfo> Icon_Big;

	private:
		void InitializeInstanceFields();

public:
		TileInfoBase()
		{
			InitializeInstanceFields();
		}
	};

	/// <summary>
	/// Stores a tile set's information, including what obstacles are allowed.
	/// </summary>
	class TileSet
	{
	public:
		class TileSetInfo
		{
		public:
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

		private:
			void InitializeInstanceFields();

public:
			TileSetInfo()
			{
				InitializeInstanceFields();
			}
		};
	public:
		static std::shared_ptr<TileInfoBase> UpgradeToInfo( Upgrade upgrade, const std::shared_ptr<TileSet> &tile );

//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
		operator TileSet*( const std::wstring &name );

		std::shared_ptr<TileSetInfo> MyTileSetInfo;

		TileSet();

		std::shared_ptr<TileSet> SetName( const std::wstring &Name );

		std::shared_ptr<TileSet> SetNameInGame( Localization::Words Name );

		std::shared_ptr<TileSet> SetBackground( const std::wstring &background );

		void MakeNew();

		// New tile set stuff
		bool IsLoaded;
		bool CustomStartEnd;
		std::shared_ptr<BlockGroup> Pillars, Platforms, Ceilings, StartBlock, EndBlock;
//C# TO C++ CONVERTER NOTE: The variable Wall was renamed since it is named the same as a user-defined type:
		std::shared_ptr<PieceQuad> Wall_Renamed;

		bool FixedWidths;
		bool ProvidesTemplates;
		std::vector<int> PillarWidths, *PlatformWidths;

		/// <summary>
		/// Read tileset info from a file.
		/// </summary>
		void Read( const std::wstring &path );

		void _Finish();

		void _Start();

		std::shared_ptr<PieceQuad> ParseBlock( std::vector<std::wstring> &bits, const std::wstring &first, const std::shared_ptr<BlockGroup> &group );

	private:
		std::shared_ptr<PieceQuad> ParseBlockLine( int width, std::vector<std::wstring> &bits );

		void ParseExtraBlockInfo( const std::shared_ptr<PieceQuad> &c, int width, std::vector<std::wstring> &bits );

	public:
		std::shared_ptr<PieceQuad> GetPieceTemplate( const std::shared_ptr<BlockBase> &block, const std::shared_ptr<Rand> &rnd );
		std::shared_ptr<PieceQuad> GetPieceTemplate( const std::shared_ptr<BlockBase> &block, const std::shared_ptr<Rand> &rnd, const std::shared_ptr<BlockGroup> &group );















		std::shared_ptr<TileSet> StandInType;

		std::vector<Upgrade> ObstacleUpgrades;

		bool FlexibleHeight;
		bool HasCeiling;

		Localization::Words NameInGame;

		std::wstring Name, MyPath;
		int Guid;

		Vector4 Tint;

		std::wstring ScreenshotString;

		std::shared_ptr<BackgroundTemplate> MyBackgroundType;

		Color CoinScoreColor;

		/// <summary>
		/// If true the player can not collide with the sides or bottoms of the blocks.
		/// </summary>
		bool PassableSides;

	private:
		void InitializeInstanceFields();
	};

	/// <summary>
	/// Static class tracking all tile sets and their information.
	/// </summary>
}


#endif	//#ifndef TILESET
