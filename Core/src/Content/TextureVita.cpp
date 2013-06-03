#include <Content/TextureVita.h>

#include <cassert>
#include <fstream>
#include <Graphics/EffectParameter.h>
#include <Utility/Log.h>

#include <Content/TextureVitaInternal.h>

TextureVita::TextureVita()
	: internal_( new TextureVitaInternal )
{
	memset( internal_, 0, sizeof( TextureVitaInternal ) );
}

TextureVita::~TextureVita()
{
	delete internal_;
}

unsigned char *LoadWholeTexture( const std::string &path, unsigned int &size )
{
	unsigned char *buffer = 0;
	return buffer;
}

void TextureVita::Load()
{
	std::string path = GetPath();
	size_t length = path.size();
	path[ length - 3 ] = 'g';
	path[ length - 2 ] = 't';
	path[ length - 1 ] = 'f';

	internal_->FileData = LoadWholeTexture( path, internal_->FileLength );
	setLoaded( internal_->FileData != NULL );
}

void TextureVita::Unload()
{
	setLoaded( false );
}

void TextureVita::GpuCreate()
{
}

void TextureVita::GpuDestroy()
{
	if( IsLoaded() )
		;//psglDestroyTextureReference( &internal_->Ref );
}

void TextureVita::Activate( unsigned int sampler )
{
}

void TextureVita::Activate( EffectParameter &parameter )
{
	//parameter.SetValue( static_cast< int >( internal_->FileData Ref.textureID ) );
}
