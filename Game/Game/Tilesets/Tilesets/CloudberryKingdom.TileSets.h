#ifndef CLOUDBERRYKINGDOM_TILESETS
#define CLOUDBERRYKINGDOM_TILESETS

#include <global_header.h>

namespace CloudberryKingdom
{

	struct TileSets
	{
	
		static boost::shared_ptr<TileSet> Load_Cloud();


		static boost::shared_ptr<TileSet> Load_Castle();


		static boost::shared_ptr<TileSet> Load_Sea();


		static boost::shared_ptr<TileSet> Load_Hills();


		static boost::shared_ptr<TileSet> Load_Forest();


		static boost::shared_ptr<TileSet> Load_Cave();


	
		static boost::shared_ptr<TileSet> None, Random;
		static boost::shared_ptr<TileSet> DefaultTileSet;

		static std::vector<boost::shared_ptr<TileSet> > TileList;
		static std::map<int, boost::shared_ptr<TileSet> > GuidLookup;
		static std::map<std::wstring, boost::shared_ptr<TileSet> > NameLookup, PathLookup;

		static void AddTileSet( const boost::shared_ptr<TileSet> &tileset );

		static void LoadCode();

		static void LoadTileSet( const std::wstring &path );
	
		static boost::shared_ptr<TileSet> GetOrMakeTileset( const std::wstring &path );

		/// <summary>
		/// Make a sprite animation and add it to the texture wad.
		/// </summary>
		static void sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length );
		static void sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length, bool reverse_at_end );

	
		static void Init();

		static void LoadSpriteEffects();
	};

}


#endif	//#ifndef CLOUDBERRYKINGDOM_TILESETS
