#ifndef PACKEDTEXTURE
#define PACKEDTEXTURE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SubTexture
	{
	
		std::wstring name;
		Vector2 BL, TR;
	};

	struct PackedTexture
	{
	
		boost::shared_ptr<EzTexture> MyTexture;

		/// <summary>
		/// The subtextures held inside this PackedTexture.
		/// </summary>
		std::vector<SubTexture> SubTextures;

		PackedTexture( const std::wstring &name );

		void Add( const std::wstring &name, float x1, float y1, float x2, float y2 );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PACKEDTEXTURE
