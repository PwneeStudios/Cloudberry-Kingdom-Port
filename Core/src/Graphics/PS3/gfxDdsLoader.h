/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#ifndef __GFX_DDS_LOADER_H__
#define __GFX_DDS_LOADER_H__

// surface description flags
#define 	DDSF_MAX_MIPMAPS	16
#define 	DDSF_MAX_TEXTURES	16		

#define		DDSF_CAPS           0x00000001
#define 	DDSF_HEIGHT         0x00000002
#define 	DDSF_WIDTH          0x00000004
#define 	DDSF_PITCH          0x00000008
#define 	DDSF_PIXELFORMAT    0x00001000
#define 	DDSF_MIPMAPCOUNT    0x00020000
#define 	DDSF_LINEARSIZE     0x00080000
#define 	DDSF_DEPTH			0x00800000

// pixel format flags
#define		DDSF_ALPHAPIXELS	0x00000001
#define		DDSF_FOURCC			0x00000004
#define		DDSF_RGB			0x00000040
#define		DDSF_RGBA			0x00000041

// dwCaps1 flags
#define DDSF_COMPLEX			0x00000008
#define DDSF_TEXTURE			0x00001000
#define DDSF_MIPMAP				0x00400000

// dwCaps2 flags
#define DDSF_CUBEMAP			0x00000200l
#define DDSF_CUBEMAP_POSITIVEX  0x00000400l
#define DDSF_CUBEMAP_NEGATIVEX  0x00000800l
#define DDSF_CUBEMAP_POSITIVEY  0x00001000l
#define DDSF_CUBEMAP_NEGATIVEY  0x00002000l
#define DDSF_CUBEMAP_POSITIVEZ  0x00004000l
#define DDSF_CUBEMAP_NEGATIVEZ  0x00008000l
#define DDSF_CUBEMAP_ALL_FACES  0x0000FC00l
#define DDSF_VOLUME				0x00200000l

// compressed texture types
#define FOURCC_DXT1				0x31545844
#define FOURCC_DXT3				0x33545844
#define FOURCC_DXT5				0x35545844


    struct DXTColBlock
    {
        unsigned short col0;
        unsigned short col1;
        unsigned char row[4];
    };

    struct DXT3AlphaBlock
    {
        unsigned short row[4];
    };

    struct DXT5AlphaBlock
    {
        unsigned char alpha0;
        unsigned char alpha1;
        unsigned char row[6];
    };

    struct DDS_PIXELFORMAT
    {
        uint32_t dwSize;
        uint32_t dwFlags;
        uint32_t dwFourCC;
        uint32_t dwRGBBitCount;
        uint32_t dwRBitMask;
        uint32_t dwGBitMask;
        uint32_t dwBBitMask;
        uint32_t dwABitMask;
    };

    struct DDS_HEADER
    {
        uint32_t dwSize;
        uint32_t dwFlags;
        uint32_t dwHeight;
        uint32_t dwWidth;
        uint32_t dwPitchOrLinearSize;
        uint32_t dwDepth;
        uint32_t dwMipMapCount;
        uint32_t dwReserved1[11];
        DDS_PIXELFORMAT ddspf;
        uint32_t dwCaps1;
        uint32_t dwCaps2;
        uint32_t dwReserved2[3];
    };


 typedef enum TextureType
    {
        TextureNone,
        TextureFlat,    // 1D, 2D, and rectangle textures
        Texture3D,
        TextureCubemap
    }TextureType;

typedef struct _DDS_IMAGE
{
unsigned char *pixels[DDSF_MAX_MIPMAPS];		//the mip map images 
}_DDS_IMAGE;


typedef struct _DDS_TEXTURE
{
unsigned char		*buffer;	//pointer to loaded dds file
uint32_t			format;		//compression used or pixel format
uint32_t			components; //number of channels 
uint32_t			width;		//width of base image in pixels
uint32_t			height;		//height of based image in pixels
uint32_t			mips;		//number of mip levels
uint32_t			surfaces;	//number of surfaces ( 1 = a texture 6 = a cube map)

_DDS_IMAGE image[6];


}DDS_TEXTURE;

GLuint gfxLoadDDSTexture(char *filename);
GLuint gfxLoadDDSTextureCubeMap(char *filename);

#endif
