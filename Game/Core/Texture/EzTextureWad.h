#ifndef COREENGINE
#define COREENGINE

#include <global_header.h>

#include "Hacks/String.h"

namespace CloudberryKingdom
{
	class EzTextureWad
	{
	public:
		std::shared_ptr<TextureOrAnim> FindTextureOrAnim( const std::wstring &name );

		/// <summary>
		/// The texture returned when a texture isn't found in the wad.
		/// </summary>
		std::shared_ptr<EzTexture> DefaultTexture;

		std::vector<std::shared_ptr<EzTexture> > TextureList;
		std::map<std::wstring, std::vector<std::shared_ptr<EzTexture> > > TextureListByFolder;

		std::map<std::wstring, std::shared_ptr<AnimationData_Texture>, IgnoreCaseComparator> AnimationDict;
		void Add( const std::shared_ptr<AnimationData_Texture> &anim, const std::wstring &name );


		std::map<std::wstring, std::shared_ptr<EzTexture>, IgnoreCaseComparator> PathDict, NameDict, BigNameDict;
		void Add( const std::shared_ptr<PackedTexture> &packed );


		std::map<std::wstring, std::shared_ptr<PackedTexture> > PackedDict;

		EzTextureWad();

		void LoadFolder( const std::shared_ptr<ContentManager> &Content, const std::wstring &Folder );

		std::shared_ptr<EzTexture> FindOrLoad( const std::shared_ptr<ContentManager> &Content, const std::wstring &name );

		/// <summary>
		/// Accepts a path. If the path does not exist, the name is used instead.
		/// </summary>
		std::shared_ptr<EzTexture> FindByPathOrName( const std::wstring &path );

		std::shared_ptr<EzTexture> FindByName( const std::wstring &name );
		std::shared_ptr<EzTexture> _FindByName( const std::wstring &name );

		std::shared_ptr<EzTexture> Find( const std::wstring &name );

		void AddEzTexture( const std::shared_ptr<EzTexture> &NewTex );

		std::shared_ptr<EzTexture> AddTexture( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name );
		std::shared_ptr<EzTexture> AddTexture( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height );

		std::shared_ptr<EzTexture> AddTexture_Fast( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height );

		std::shared_ptr<EzTexture> AddTexture_Fast( const std::shared_ptr<Texture2D> &Tex, const std::wstring &Name, int Width, int Height, const std::wstring &StrippedName, const std::wstring &LowerName, const std::wstring &LowerPath, const std::wstring &BigName, const std::wstring &Folder );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef COREENGINE
