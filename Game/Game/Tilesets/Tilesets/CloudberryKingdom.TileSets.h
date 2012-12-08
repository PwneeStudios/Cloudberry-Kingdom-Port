#ifndef CLOUDBERRYKINGDOM_TILESETS
#define CLOUDBERRYKINGDOM_TILESETS

#include <global_header.h>

namespace CloudberryKingdom
{
	class TileSets
	{
	private:
		static std::shared_ptr<TileSet> Load_Cloud();


		static std::shared_ptr<TileSet> Load_Castle();


		static std::shared_ptr<TileSet> Load_Sea();


		static std::shared_ptr<TileSet> Load_Hills();


		static std::shared_ptr<TileSet> Load_Forest();


		static std::shared_ptr<TileSet> Load_Cave();


	public:
		static std::shared_ptr<TileSet> None, Random;
		static std::shared_ptr<TileSet> DefaultTileSet;

		static std::vector<std::shared_ptr<TileSet> > TileList;
		static std::map<int, std::shared_ptr<TileSet> > GuidLookup;
		static std::map<std::wstring, std::shared_ptr<TileSet> > NameLookup, PathLookup;

		static void AddTileSet( const std::shared_ptr<TileSet> &tileset );

		static void LoadCode();

		static void LoadTileSet( const std::wstring &path );
	private:
		static std::shared_ptr<TileSet> GetOrMakeTileset( const std::wstring &path );

		/// <summary>
		/// Make a sprite animation and add it to the texture wad.
		/// </summary>
		static void sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length );
		static void sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length, bool reverse_at_end );

	public:
		static void Init();

		static void LoadSpriteEffects();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_TILESETS
