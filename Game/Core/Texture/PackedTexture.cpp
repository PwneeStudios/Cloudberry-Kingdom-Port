#include <global_header.h>











namespace CloudberryKingdom
{

	PackedTexture::PackedTexture( const std::wstring &name )
	{
		InitializeInstanceFields();
		MyTexture = Tools::TextureWad->FindByName( name );
	}

	void PackedTexture::Add( const std::wstring &name, float x1, float y1, float x2, float y2 )
	{
		SubTexture sub;
		sub.name = name;
		sub.BL = Vector2( x1, y2 );
		sub.TR = Vector2( x2, y1 );

		SubTextures.push_back( sub );
	}

	void PackedTexture::InitializeInstanceFields()
	{
		SubTextures = std::vector<SubTexture>();
	}
}
