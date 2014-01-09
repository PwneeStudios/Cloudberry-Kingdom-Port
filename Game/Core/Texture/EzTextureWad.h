#ifndef COREENGINE
#define COREENGINE

#include <small_header.h>

//#include "Core/Animation/AnimationData_Integer.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Game/Tilesets/Backgrounds/Background.h"
//#include "Core/Texture/EzTexture.h"
//#include "Core/Texture/PackedTexture.h"
//#include "Core/Texture/TextureOrAnim.h"
//#include "Game/Tilesets/TileSet.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Prototypes.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct EzTextureWad
	{
	
		boost::shared_ptr<TextureOrAnim> FindTextureOrAnim( const std::wstring &name );

		/// <summary>
		/// The texture returned when a texture isn't found in the wad.
		/// </summary>
		boost::shared_ptr<EzTexture> DefaultTexture;

		std::vector<boost::shared_ptr<EzTexture> > TextureList;
		std::map<std::wstring, std::vector<boost::shared_ptr<EzTexture> > > TextureListByFolder;

		// FIME:
		//std::map<std::wstring, boost::shared_ptr<AnimationData_Texture>, IgnoreCaseComparator> AnimationDict;
		std::map<std::wstring, boost::shared_ptr<AnimationData_Texture> > AnimationDict;
		void Add( const boost::shared_ptr<AnimationData_Texture> &anim, const std::wstring &name );


		// FIXME:
		std::map<std::wstring, boost::shared_ptr<EzTexture> > NameDict;
		void Add( const boost::shared_ptr<PackedTexture> &packed );


		std::map<std::wstring, boost::shared_ptr<PackedTexture> > PackedDict;

		EzTextureWad();

		void LoadFolder( const boost::shared_ptr<ContentManager> &Content, const std::wstring &Folder );

		boost::shared_ptr<EzTexture> FindOrLoad( const boost::shared_ptr<ContentManager> &Content, const std::wstring &name, const std::wstring &path );

		/// <summary>
		/// Accepts a path. If the path does not exist, the name is used instead.
		/// </summary>
		boost::shared_ptr<EzTexture> FindByPathOrName( const std::wstring &path );

		boost::shared_ptr<EzTexture> FindByName( const std::wstring &name );
		boost::shared_ptr<EzTexture> _FindByName( const std::wstring &name );

		boost::shared_ptr<EzTexture> Find( const std::wstring &name );

		void AddEzTexture( const boost::shared_ptr<EzTexture> &NewTex );

		boost::shared_ptr<EzTexture> AddTexture( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name );
		boost::shared_ptr<EzTexture> AddTexture( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height );

		boost::shared_ptr<EzTexture> AddTexture_Fast( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height );

		boost::shared_ptr<EzTexture> AddTexture_Fast( const boost::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height, const std::wstring &StrippedName, const std::wstring &LowerName, const std::wstring &Folder );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef COREENGINE
