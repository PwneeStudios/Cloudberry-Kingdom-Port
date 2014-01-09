#ifndef TILESET
#define TILESET

#include <small_header.h>

//#include "Core/Animation/AnimationData_Integer.h"
//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Game/Localization.h"
//#include "Game/Tilesets/Backgrounds/Background.h"
//#include "Core/Tools/ColorHelper.h"
//#include "Core/Tools/Random.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/In Game Objects/Blocks/Block.h"
//#include "Game/Objects/In Game Objects/Blocks/Wall.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
//#include "Game/Objects/AutoGen.h"
//#include "Game/Objects/Door/Door.h"
//#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/FallingBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/GhostBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingBlock.h"
//#include "Game/Objects/In Game Objects/Blocks/MovingPlatform.h"
//#include "Game/Objects/In Game Objects/Blocks/Pendulum.h"
//#include "Game/Objects/In Game Objects/Grab/Checkpoint.h"
//#include "Game/Objects/In Game Objects/Grab/Coin.h"
//#include "Game/Objects/In Game Objects/Obstacles/Boulder.h"
//#include "Game/Objects/In Game Objects/Obstacles/Cloud.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Firesnake.h"
//#include "Game/Objects/In Game Objects/Obstacles/FireSpinner.h"
//#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
//#include "Game/Objects/In Game Objects/Obstacles/Laser.h"
//#include "Game/Objects/In Game Objects/Obstacles/LavaDrip.h"
//#include "Game/Objects/In Game Objects/Obstacles/Serpent.h"
//#include "Game/Objects/In Game Objects/Obstacles/Spike.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy.h"
//#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine.h"
//#include "Game/Tilesets/BlockGroup.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct TileInfoBase
	{
	
		boost::shared_ptr<SpriteInfo> Icon;
		boost::shared_ptr<SpriteInfo> Icon_Big;

	
		void InitializeInstanceFields();

	
		TileInfoBase()
		{
			InitializeInstanceFields();
		}
	};

	/// <summary>
	/// Stores a tile set's information, including what obstacles are allowed.
	/// </summary>
	struct TileSet : public Object, public boost::enable_shared_from_this<TileSet>
	{
	
		static boost::shared_ptr<TileInfoBase> UpgradeToInfo( Upgrade upgrade, const boost::shared_ptr<TileSet> &tile );

		//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
		//operator boost::shared_ptr<TileSet> ( const std::wstring &name );

		static boost::shared_ptr<TileSet> Get( const std::wstring &name );

		boost::shared_ptr<TileSetInfo> MyTileSetInfo;

		TileSet();

		boost::shared_ptr<TileSet> SetName( const std::wstring &Name );

		boost::shared_ptr<TileSet> SetNameInGame( Localization::Words Name );

		boost::shared_ptr<TileSet> SetBackground( const std::wstring &background );

		void MakeNew();

		// New tile set stuff
		bool IsLoaded;
		bool CustomStartEnd;
		boost::shared_ptr<BlockGroup> Pillars, Platforms, Ceilings, StartBlock, EndBlock;
//C# TO C++ CONVERTER NOTE: The variable Wall was renamed since it is named the same as a user-defined type:
		boost::shared_ptr<PieceQuad> Wall_Renamed;

		bool FixedWidths;
		bool ProvidesTemplates;
		std::vector<int> PillarWidths, *PlatformWidths;

		/// <summary>
		/// Read tileset info from a file.
		/// </summary>
		void Read( const std::wstring &path );

		void _Finish();

		void _Start();

		boost::shared_ptr<PieceQuad> ParseBlock( std::vector<std::wstring> &bits, const std::wstring &first, const boost::shared_ptr<BlockGroup> &group );

	
		boost::shared_ptr<PieceQuad> ParseBlockLine( int width, std::vector<std::wstring> &bits );

		void ParseExtraBlockInfo( const boost::shared_ptr<PieceQuad> &c, int width, std::vector<std::wstring> &bits );

	
		boost::shared_ptr<PieceQuad> GetPieceTemplate( const boost::shared_ptr<BlockBase> &block, const boost::shared_ptr<Rand> &rnd );
		boost::shared_ptr<PieceQuad> GetPieceTemplate( const boost::shared_ptr<BlockBase> &block, const boost::shared_ptr<Rand> &rnd, boost::shared_ptr<BlockGroup> group );


		boost::shared_ptr<TileSet> StandInType;

		std::vector<Upgrade> ObstacleUpgrades;

		bool FlexibleHeight;
		bool HasCeiling;

		Localization::Words NameInGame;

		std::wstring Name, MyPath;
		int Guid;

		Vector4 Tint;

		std::wstring ScreenshotString;

		boost::shared_ptr<BackgroundTemplate> MyBackgroundType;

		Color CoinScoreColor;

		/// <summary>
		/// If true the player can not collide with the sides or bottoms of the blocks.
		/// </summary>
		bool PassableSides;

	
		void InitializeInstanceFields();
	};

	/// <summary>
	/// Static struct tracking all tile sets and their information.
	/// </summary>
}


#endif	//#ifndef TILESET
