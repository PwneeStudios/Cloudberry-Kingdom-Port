#include <Content/TextureVita.h>

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <cassert>
#include <fstream>
#include <Graphics/EffectParameter.h>
#include <Utility/Log.h>

#include <Content/TextureVitaInternal.h>

#include <gxt.h>

extern void *graphicsAlloc(SceKernelMemBlockType type, uint32_t size, uint32_t alignment, uint32_t attribs, SceUID *uid);
extern void graphicsFree(SceUID uid);

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
	
	boost::shared_ptr< File > file = FILESYSTEM.Open( path );

	if( !file->IsOpen() )
		return NULL;

	size = file->Size();
	buffer = new unsigned char[ size ];
	file->Read( reinterpret_cast< char * >( buffer ), size );

	return buffer;
}

void TextureVita::Load()
{
	std::string path = GetPath();
	size_t length = path.size();
	path[ length - 3 ] = 'g';
	path[ length - 2 ] = 'x';
	path[ length - 1 ] = 't';

	unsigned int fileLength;
	void *fileData = LoadWholeTexture( path, fileLength );

	setLoaded( fileData != NULL );

	if( IsLoaded() )
	{
		const uint32_t dataSize	= sceGxtGetDataSize( fileData );
		const void *dataSrc		= sceGxtGetDataAddress( fileData );
		
		internal_->TextureData = graphicsAlloc(
			SCE_KERNEL_MEMBLOCK_TYPE_USER_CDRAM_RWDATA,
			dataSize,
			SCE_GXM_TEXTURE_ALIGNMENT,
			SCE_GXM_MEMORY_ATTRIB_READ | SCE_GXM_MEMORY_ATTRIB_WRITE,
			&internal_->AllocationID
		);

		memcpy( internal_->TextureData, dataSrc, dataSize );

		sceGxtInitTexture( &internal_->Texture, fileData, internal_->TextureData, 0 );

		delete[] fileData;
	}
}

void TextureVita::Unload()
{
	setLoaded( false );

	graphicsFree( internal_->AllocationID );
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
