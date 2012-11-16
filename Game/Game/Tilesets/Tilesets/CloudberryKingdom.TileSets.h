#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#include <global_header.h>

namespace CloudberryKingdom
{
	class TileSet;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;






//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;


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

		static std::vector<TileSet*> TileList;
		static std::unordered_map<int, TileSet*> GuidLookup;
		static std::unordered_map<std::wstring, TileSet*> NameLookup, PathLookup;

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


#endif	//#ifndef CLOUDBERRYKINGDOM
