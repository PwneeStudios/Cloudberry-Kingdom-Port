#include <Content/TextureWiiU.h>

#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <Utility/Log.h>

struct TextureInternal
{
	GX2Texture *Texture;
};

TextureWiiU::TextureWiiU() :
	internal_( new TextureInternal )
{
}

TextureWiiU::~TextureWiiU()
{
	delete internal_;
}

void TextureWiiU::Load()
{
}

void TextureWiiU::Unload()
{
}

void TextureWiiU::GpuCreate()
{
	BOOL ok;
	u32 len;
	void *buf;

	std::string path = GetPath();

	std::string extension = path.substr( path.length() - 3, 3 );
	if( extension == "png" )
	{
		path[ path.length() - 3 ] = 'g';
		path[ path.length() - 2 ] = 't';
		path[ path.length() - 1 ] = 'x';
	}

	buf = DEMOFSSimpleRead( path.c_str(), &len );
	ok = DEMOGFDReadTexture( &internal_->Texture, 0, buf );

	if( ok )
		setLoaded( true );
	
	DEMOFree( buf );
}

void TextureWiiU::GpuDestroy()
{
	DEMOGFDFreeTexture( internal_->Texture );
}

void TextureWiiU::Activate( unsigned int sampler )
{
	GX2SetPixelTexture( internal_->Texture, sampler );
}
