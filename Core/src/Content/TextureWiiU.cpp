#include <Content/TextureWiiU.h>

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Content/TextureWiiUInternal.h>
#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <Utility/Log.h>

TextureWiiU::TextureWiiU() :
	internal_( new TextureInternal )
{
}

TextureWiiU::~TextureWiiU()
{
	if( internal_->Buffer )
		delete[] internal_->Buffer;

	delete internal_;
}

void TextureWiiU::Load()
{
	u32 len;

	std::string path = GetPath();

	std::string extension = path.substr( path.length() - 3, 3 );
	if( extension == "png" )
	{
		path[ path.length() - 3 ] = 'g';
		path[ path.length() - 2 ] = 't';
		path[ path.length() - 1 ] = 'x';
	}

	boost::shared_ptr<File> file = FILESYSTEM.Open( path );

	if( file->IsOpen() )
	{
		internal_->Buffer = new char[ file->Size() ];
		file->Read( internal_->Buffer, file->Size() );

		setLoaded( true );
	}
	else
		setLoaded( false );
}

void TextureWiiU::Unload()
{
}

void TextureWiiU::GpuCreate()
{
	BOOL ok;
	
	ok = DEMOGFDReadTexture( &internal_->Texture, 0, internal_->Buffer );

	delete[] internal_->Buffer;
	internal_->Buffer = NULL;

	if( ok )
		setLoaded( true );
}

void TextureWiiU::GpuDestroy()
{
	DEMOGFDFreeTexture( internal_->Texture );
}

void TextureWiiU::Activate( unsigned int sampler )
{
	GX2SetPixelTexture( internal_->Texture, sampler );
}
