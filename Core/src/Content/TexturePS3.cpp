#include <Content/TexturePS3.h>

#include <cassert>
#include <fstream>
#include <Graphics/EffectParameter.h>
#include <Utility/Log.h>

#include <cell/cell_fs.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>

#include "PS3/psglGtfLoader.h"
#include "PS3/gtfloader.h"

#include <Content/TexturePS3Internal.h>

TexturePS3::TexturePS3()
	: internal_( new TexturePS3Internal )
{
	memset( internal_, 0, sizeof( TexturePS3Internal ) );
}

TexturePS3::~TexturePS3()
{
	delete internal_;
}

unsigned char *LoadWholeTexture( const std::string &path, unsigned int &size )
{
	CellFsErrno err;

	int fd;
	err = cellFsOpen( path.c_str(), CELL_FS_O_RDONLY, &fd, NULL, 0 );

	if( err != CELL_FS_SUCCEEDED )
	{
		size = 0;
		return NULL;
	}

	uint64_t length, start, numRead;
	cellFsLseek( fd, 0, CELL_FS_SEEK_END, &length );
	cellFsLseek( fd, 0, CELL_FS_SEEK_SET, &start );
	
	unsigned char *buffer = new unsigned char[ length ];
	cellFsRead( fd, buffer, length, &numRead );

	assert( length == numRead );
	size = static_cast< unsigned int >( length );

	cellFsClose( fd );
	return buffer;
}

void TexturePS3::Load()
{
	std::string path = GetPath();
	size_t length = path.size();
	path[ length - 3 ] = 'g';
	path[ length - 2 ] = 't';
	path[ length - 1 ] = 'f';

	internal_->FileData = LoadWholeTexture( path, internal_->FileLength );
	setLoaded( internal_->FileData != NULL );
	/*uint32_t gpuMemorySize = 0;
	uint32_t ppuMemorySize = 0;*/

	//static int counter = 0;
	/*int result = psglCreateTextureReferenceFromGTFFile( path.c_str(), &internal_->Ref, true, false, &gpuMemorySize, &ppuMemorySize );
	if( result != 0 )
		setLoaded( false );
	else
	{
		setLoaded( true );
		//counter++;
	}*/
}

void TexturePS3::Unload()
{
	setLoaded( false );
}

void TexturePS3::GpuCreate()
{
	CellGtfTextureAttribute attrib;
	if( cellGtfReadTextureAttributeFromMemory( internal_->FileData, 0, &attrib ) )
	{
		LOG.Write( "Failed to get attribute\n" );
		delete[] internal_->FileData;
		setLoaded( false );
		return;
	}

	uint8_t format = attrib.tex.format;
	bool bSwizzled = !( format & CELL_GCM_TEXTURE_LN );

	if( bSwizzled )
		LOG.Write( "Swizzled!\n" );

	uint32_t gtfSize = 0;
	cellGtfCalculateMemorySize( &attrib, &gtfSize );

	// Assume texture 2d, it's all we use.
	GLenum target = GL_TEXTURE_2D;
	if( attrib.tex.dimension != CELL_GCM_TEXTURE_DIMENSION_2 )
	{
		LOG.Write( "Texture is not 2D!" );
		delete[] internal_->FileData;
		setLoaded( false );
		return;
	}

	GLenum glInternalFormat = 0;
    switch( format & 0x9F ) // Ignore SZ LN NR UN bits
    {
    case CELL_GCM_TEXTURE_B8					: glInternalFormat = GL_INTENSITY8; break;
    case CELL_GCM_TEXTURE_A1R5G5B5				: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_A4R4G4B4				: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_R5G6B5				: glInternalFormat = GL_RGB5; break;
    case CELL_GCM_TEXTURE_A8R8G8B8				: glInternalFormat = GL_ARGB_SCE; break;
    case CELL_GCM_TEXTURE_COMPRESSED_DXT1		: glInternalFormat = GL_COMPRESSED_RGB_S3TC_DXT1_EXT; break;
    case CELL_GCM_TEXTURE_COMPRESSED_DXT23		: glInternalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
    case CELL_GCM_TEXTURE_COMPRESSED_DXT45		: glInternalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
    case CELL_GCM_TEXTURE_G8B8					: glInternalFormat = GL_LUMINANCE8_ALPHA8; break;
    case CELL_GCM_TEXTURE_R6G5B5				: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_DEPTH24_D8			: glInternalFormat = GL_DEPTH_COMPONENT24; break;
    case CELL_GCM_TEXTURE_DEPTH24_D8_FLOAT		: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_DEPTH16				: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_DEPTH16_FLOAT			: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_X16					: glInternalFormat = GL_LUMINANCE16; break;
    case CELL_GCM_TEXTURE_Y16_X16				: glInternalFormat = GL_LUMINANCE16_ALPHA16; break;
    case CELL_GCM_TEXTURE_R5G5B5A1				: glInternalFormat = GL_RGB5_A1; break;
    case CELL_GCM_TEXTURE_COMPRESSED_HILO8		: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_COMPRESSED_HILO_S8	: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_W16_Z16_Y16_X16_FLOAT	: glInternalFormat = GL_RGBA16F_ARB; break;
    case CELL_GCM_TEXTURE_W32_Z32_Y32_X32_FLOAT	: glInternalFormat = GL_RGBA32F_ARB; break;
    case CELL_GCM_TEXTURE_X32_FLOAT				: glInternalFormat = GL_LUMINANCE32F_ARB; break;
    case CELL_GCM_TEXTURE_D1R5G5B5				: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_D8R8G8B8				: glInternalFormat = 0; break;
    case CELL_GCM_TEXTURE_Y16_X16_FLOAT			: glInternalFormat = GL_LUMINANCE_ALPHA16F_ARB; break;
        //case CELL_GCM_TEXTURE_COMPRESSED_B8R8_G8R8	: glInternalFormat = 0; break;
        //case CELL_GCM_TEXTURE_COMPRESSED_R8B8_R8G8	: glInternalFormat = 0; break;
    default                                     :
		{
			LOG.Write( "Invalid GCM format: %d", format );
			delete[] internal_->FileData;
			setLoaded( false );
			return;
		}
    }

	if( glInternalFormat == 0 )
	{
		LOG.Write( "Internal format does not exist for GCM format %d\n", format );
		delete[] internal_->FileData;
		setLoaded( false );
		return;
	}

	glGenBuffers( 1, &internal_->Ref.bufferID );
	glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, internal_->Ref.bufferID );

	static uint32_t gpuUsedMemory = 0;
	static uint32_t ppuUsedMemory = 0;
	const uint32_t GPU_MEMORY_LIMIT = 200 * 1024 * 1024;

	bool bLoadInPlace = true;

	// Check to see if there is space for the texture on the gpu.
	if( bLoadInPlace )
	{
		if( gpuUsedMemory + gtfSize > GPU_MEMORY_LIMIT )
			bLoadInPlace = false;
	}

	if( bLoadInPlace )
	{
		glBufferData( GL_TEXTURE_REFERENCE_BUFFER_SCE, gtfSize, NULL, GL_STATIC_DRAW );

		char *textureAddress = reinterpret_cast< char * >( glMapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, GL_READ_WRITE ) );
		cellGtfLoadPackedTextureFromMemory( internal_->FileData, internal_->FileLength, attrib.id, &attrib.tex, CELL_GCM_LOCATION_LOCAL, textureAddress );
		glUnmapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE );

		gpuUsedMemory += gtfSize;
	}
	else
	{
		glBufferData( GL_TEXTURE_REFERENCE_BUFFER_SCE, gtfSize, NULL, GL_SYSTEM_DRAW_SCE );

		char *textureAddress = reinterpret_cast< char * >( glMapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, GL_READ_WRITE ) );
		cellGtfLoadPackedTextureFromMemory( internal_->FileData, internal_->FileLength, attrib.id, &attrib.tex, CELL_GCM_LOCATION_MAIN, textureAddress );
		glUnmapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE );

		ppuUsedMemory += gtfSize;
	}

	// Clean up temporary file buffer.
	delete[] internal_->FileData;
	internal_->FileLength = 0;

	glEnable( target );
    glGenTextures( 1, &internal_->Ref.textureID );
    glBindTexture( target, internal_->Ref.textureID );
    glTexParameterf( target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f );
    glTexParameteri( target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( target, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( target, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT );
    glTexParameteri( target, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
    glTexParameteri( target, GL_TEXTURE_MAX_LOD, attrib.tex.mipmap - 1 );
	glTexParameteri( target, GL_TEXTURE_ALLOCATION_HINT_SCE, GL_TEXTURE_TILED_GPU_SCE );

	if( !bSwizzled )
	{
        glTextureReferenceSCE( target, attrib.tex.mipmap, attrib.tex.width, attrib.tex.height, 1, glInternalFormat, attrib.tex.pitch, 0 );
	}
	else
	{
        glTextureReferenceSCE( target, attrib.tex.mipmap, attrib.tex.width, attrib.tex.height, 1, glInternalFormat, 0, 0 );
	}

	glDisable( target );

	setLoaded( true );
}

void TexturePS3::GpuDestroy()
{
	if( IsLoaded() )
		psglDestroyTextureReference( &internal_->Ref );
}

void TexturePS3::Activate( unsigned int sampler )
{
}

void TexturePS3::Activate( EffectParameter &parameter )
{
	parameter.SetValue( static_cast< int >( internal_->Ref.textureID ) );
}
