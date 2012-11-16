#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#include <global_header.h>

namespace CloudberryKingdom
{
	class TextureOrAnim;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class AnimationData_Texture;
}

namespace CloudberryKingdom
{
	class PackedTexture;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Content
			{
				class ContentManager;
			}
		}
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class Texture2D;
			}
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;





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

		std::vector<EzTexture*> TextureList;
		std::unordered_map<std::wstring, std::vector<EzTexture*> > TextureListByFolder;

		std::unordered_map<std::wstring, AnimationData_Texture*> AnimationDict;
		void Add( const std::shared_ptr<AnimationData_Texture> &anim, const std::wstring &name );


		std::unordered_map<std::wstring, EzTexture*> PathDict, NameDict, BigNameDict;
		void Add( const std::shared_ptr<PackedTexture> &packed );


		std::unordered_map<std::wstring, PackedTexture*> PackedDict;

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


#endif	//#ifndef CLOUDBERRYKINGDOM
