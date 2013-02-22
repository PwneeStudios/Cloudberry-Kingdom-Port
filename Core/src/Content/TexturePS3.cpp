#include <Content/TexturePS3.h>

#include <cassert>
#include <fstream>
#include <Graphics/EffectParameter.h>
#include <Utility/Log.h>

#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

#include "PS3/psglGtfLoader.h"

#include <Content/TexturePS3Internal.h>

TexturePS3::TexturePS3()
	: internal_( new TexturePS3Internal )
{
}

TexturePS3::~TexturePS3()
{
	delete internal_;
}

void TexturePS3::Load()
{
	std::string path = GetPath();
	size_t length = path.size();
	path[ length - 3 ] = 'g';
	path[ length - 2 ] = 't';
	path[ length - 1 ] = 'f';

	static int counter = 0;
	int result = psglCreateTextureReferenceFromGTFFile( path.c_str(), &internal_->Ref, counter < 650, false );
	if( result != 0 )
		setLoaded( false );
	else
	{
		setLoaded( true );
		counter++;
	}
}

void TexturePS3::Unload()
{
	if( IsLoaded() )
		psglDestroyTextureReference( &internal_->Ref );
	setLoaded( false );
}

void TexturePS3::GpuCreate()
{
}

void TexturePS3::GpuDestroy()
{
}

void TexturePS3::Activate( unsigned int sampler )
{
}

void TexturePS3::Activate( EffectParameter &parameter )
{
	parameter.SetValue( static_cast< int >( internal_->Ref.textureID ) );
}
