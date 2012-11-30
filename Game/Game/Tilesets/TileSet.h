#ifndef TILESET
#define TILESET

#include <global_header.h>

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
		static std::shared_ptr<TileInfoBase> UpgradeToInfo( Upgrade upgrade, const std::shared_ptr<TileSet> &tile );

		//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
		//operator std::shared_ptr<TileSet> ( const std::wstring &name );

		static std::shared_ptr<TileSet> Get( const std::wstring &name );

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
