/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#include <stdio.h>
#include <PSGL/psgl.h>
#include "gtfloader.h"
#include "psglGtfLoader.h"
#include <string.h>
#include <sdk_version.h>

#ifdef __SNC__
#define JS_BREAK __builtin_snpause()
#else
#define JS_BREAK __asm__ volatile ( "tw 31,1,1" )
#endif // __SNC__

#define JS_TRACE printf
#define JS_ASSERT(assertion, formattedString) { \
    if (!(assertion)) \
    { \
    JS_TRACE formattedString; \
    JS_BREAK; \
    } \
}

char * strupr(char *c)
{
    while (*c)
    {
        if (*c>='a' && *c<='z')
            *c += ('A' - 'a');
        c++;
    }
    return c;
}

int psglCreateTextureReferenceFromFile(const char *filename, psglTextureReference *textureReference, bool bLoadInPlace, bool bForceSwizzling)
{
    //only support dds and gtf at the moment
    const char *ext = strrchr(filename,'.');
    if (ext)
    {
        char ext2[5];
        strncpy(ext2,ext,sizeof(ext2)-1);
        ext2[sizeof(ext2)-1] = '\0';
        strupr(ext2);
        if (!strcmp(ext2,".GTF"))
        {
            return psglCreateTextureReferenceFromGTFFile(filename,textureReference,bLoadInPlace,bForceSwizzling);
        }
        else if (!strcmp(ext2,".DDS"))
        {
            //return psglCreateTextureReferenceFromDDSFile(filename,textureReference,bLoadInPlace,bForceSwizzling);
            printf("DDS loading is not implemented yet.");
            return -1;
        }
    }
    return -1;
}

static void swizzleTexture(unsigned int _width,  unsigned int _height, unsigned int _mipmaps, void *_TextureAddress, unsigned int *_textureSize);
static unsigned int texCoordToSwizzledIndex( unsigned int x,  unsigned int y, unsigned int z, unsigned int width, unsigned int height, unsigned int depth );
static int calculateMemorySize(unsigned int width, unsigned int height, unsigned int mipmaps, bool swizzled, unsigned int *size);

int psglCreateTextureReferenceFromGTFFile(const char *filename, psglTextureReference *textureReference, bool bLoadInPlace, bool bForceSwizzling)
{
    //// Get texture file info from GTF attribute and convert it to PSGL texture format

    CellGtfTextureAttribute attrib;
    if( cellGtfReadTextureAttribute(filename,0,&attrib) )
    {
        JS_TRACE("Error loading %s.\n", filename );
        return -1;
    }

    uint8_t format = attrib.tex.format;
    bool bSwizzled = !(format & CELL_GCM_TEXTURE_LN);

	if( bSwizzled )
		JS_TRACE( "Swizzled!\n" );

    if (bLoadInPlace && !bSwizzled && bForceSwizzling)
    {	
        //if the texture has no mipmaps we could theoratically configure the HW to swizzle while uploading
        //we would need to expose a lot of things to do that and it's probably not that useful.
        JS_TRACE(("the texture needs to be swizzled, cannot load in place\n"));
        bLoadInPlace = false;
    }

    uint32_t gtfSize = 0;
    cellGtfCalculateMemorySize(&attrib,&gtfSize);

    GLenum target = 0;
    if (attrib.tex.cubemap == CELL_GCM_TRUE)
    {
        target = GL_TEXTURE_CUBE_MAP;
    }
    else
    {
        switch (attrib.tex.dimension)
        {
        case CELL_GCM_TEXTURE_DIMENSION_1: printf("1D texture is not supported"); return -1;
        case CELL_GCM_TEXTURE_DIMENSION_2: target = GL_TEXTURE_2D; break;
        case CELL_GCM_TEXTURE_DIMENSION_3: target = GL_TEXTURE_3D; break;
        default: ;
        }
    }
    if (target == 0) {
        printf("Invalid target %d", attrib.tex.dimension);
        return -1;
    }

    // Format conversion
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
    default                                     : printf("Invalid GCM format: %d", format ); return -1;
    }

    if (glInternalFormat == 0)
    {
        printf("GL does not have corresponding format for GCM format %d", format );
        return -1;
    }


    //// Create and initialize a PSGL texture with the buffer object bound as source

    glGenBuffers(1,&textureReference->bufferID);
    glBindBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE,textureReference->bufferID);

    if (bLoadInPlace)
    {
        //load the data directly from disc to local memory

        //allocate a local memory buffer to store the texture
        glBufferData(GL_TEXTURE_REFERENCE_BUFFER_SCE, gtfSize, NULL, GL_STATIC_DRAW );

        //get the pointer on the buffer
        char *mTextureAddress = (char *)glMapBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE,GL_READ_WRITE);
        //load the texture in place
        cellGtfLoad( (char*)filename, attrib.id,&attrib.tex, CELL_GCM_LOCATION_LOCAL, mTextureAddress );
        //unmap the buffer
        glUnmapBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE);
    }
    else
    {
        //load the data to main memory texture
		
		// allocate a main memory buffer
        glBufferData(GL_TEXTURE_REFERENCE_BUFFER_SCE, gtfSize, NULL, GL_SYSTEM_DRAW_SCE);
        //get the pointer on the buffer
        char *mTextureAddress = (char *)glMapBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE, GL_READ_WRITE);
		// load the gtf texture to main memory buffer
		cellGtfLoad( (char*)filename, attrib.id,&attrib.tex, CELL_GCM_LOCATION_MAIN, mTextureAddress );

        //swizzle here if needed
        uint32_t textureSize = gtfSize;
        if (!bSwizzled && bForceSwizzling)
        {
            swizzleTexture(attrib.tex.width, attrib.tex.height, attrib.tex.mipmap, mTextureAddress, &textureSize);
            bSwizzled = true;
        }

        //unmap the buffer
        glUnmapBuffer(GL_TEXTURE_REFERENCE_BUFFER_SCE);
    }

    glEnable( target );
    glGenTextures(1,&textureReference->textureID);
    glBindTexture( target, textureReference->textureID );
    glTexParameterf(target,GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f );
    glTexParameteri( target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( target, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( target, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameteri( target, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glTexParameteri( target, GL_TEXTURE_MAX_LOD, attrib.tex.mipmap-1 );
	glTexParameteri( target, GL_TEXTURE_ALLOCATION_HINT_SCE, GL_TEXTURE_TILED_GPU_SCE );

    if (!bSwizzled)
    {
        //linear texture
        glTextureReferenceSCE(target, attrib.tex.mipmap, attrib.tex.width,  attrib.tex.height, 1 , glInternalFormat, attrib.tex.pitch, 0);
    }
    else
    {
        //swizzled texture: 0 is passed as pitch to the glTextureReferenceSCE function	
        glTextureReferenceSCE(target, attrib.tex.mipmap, attrib.tex.width,  attrib.tex.height, 1 , glInternalFormat,0,0);
    }

    glDisable( target );

    return 0;
}

//hardcoded for 4 components
static int calculateMemorySize(unsigned int width, unsigned int height, unsigned int mipmaps, bool swizzled, unsigned int *size)
{
    for ( unsigned int level = 0; level < mipmaps; level++ )
    {
        *size += width * height * 4;
        if (swizzled && width > 1)
            width /= 2;
        if (height > 1)
            height /= 2;
    }
    return 0;
}

static void swizzleTexture(unsigned int _width,  unsigned int _height, unsigned int _mipmaps, void *_TextureAddress, unsigned int *_textureSize)
{
    unsigned int size=0;
    unsigned int width=_width;
    unsigned int height=_height;
    unsigned int level;

    calculateMemorySize(_width,_height,_mipmaps,true,&size);
    for ( level = 0; level < _mipmaps; level++ )
    {
        size += width * height * 4;
        if (width > 1)
            width /= 2;
        if (height > 1)
            height /= 2;
    }

    char *buffer = (char *)memalign(128,size);
    unsigned int offset = 0;

    //swizzle each mipmap level
    width = _width;
    height = _height;
    char *source = (char*)_TextureAddress;
    for ( level = 0; level < _mipmaps; level++ )
    {
        for (unsigned int x=0;x<width;x++)
            for (unsigned int y=0;y<height;y++)
            {
                //where should we put the x,y pixel of the source texture in the swizzled texture ?
                unsigned int index = texCoordToSwizzledIndex(x,y,0,width,height,1);
                buffer[offset + index*4 + 0] = source[(y*_width + x)*4 + 0];
                buffer[offset + index*4 + 1] = source[(y*_width  + x)*4 + 1];
                buffer[offset + index*4 + 2] = source[(y*_width  + x)*4 + 2];
                buffer[offset + index*4 + 3] = source[(y*_width  + x)*4 + 3];
            }
            source += height * _width * 4;
            offset += height * width * 4;
            width /= 2;
            height /= 2;
    }
	memcpy( _TextureAddress, buffer, size );
	free( buffer );
    *_textureSize = size;
}

static unsigned int texCoordToSwizzledIndex( unsigned int x,  unsigned int y, unsigned int z, unsigned int width, unsigned int height, unsigned int depth )
{
    unsigned int bit;
    unsigned int coord;

    bit = 1;
    coord = 0;
    do
    {
        width >>= 1;
        height >>= 1;
        depth >>= 1;
        if ( width )
        {
            coord += (x & 1) ? bit : 0;
            bit += bit;
        }
        if ( height )
        {
            coord += (y & 1) ? bit : 0;
            bit += bit;
        }
        if ( depth )
        {
            coord += (z & 1) ? bit : 0;
            bit += bit;
        }
        x >>= 1;
        y >>= 1;
        z >>= 1;
    } while ( x + y + z );
    return coord;
}

/*
int psglCreateTextureReferenceFromDDSFile(const char *filename, psglTextureReference *textureReference,bool bLoadInPlace, bool bForceSwizzling)
{
JS_ASSERT(0,("not implemented"));
return -1;
}

int psglCreateTextureReferenceFromGTF(const char *buffer, size_t size, psglTextureReference *textureReference)
{
JS_ASSERT(0,("not implemented"));
return -1;
}
int psglCreateTextureReferenceFromDDS(const char *buffer, size_t size, psglTextureReference *textureReference)
{
JS_ASSERT(0,("not implemented"));
return -1;
}
*/

int psglDestroyTextureReference(psglTextureReference *textureReference)
{
    glDeleteTextures(1,&textureReference->textureID);
    glDeleteBuffers(1,&textureReference->bufferID);
    return 0;
}
