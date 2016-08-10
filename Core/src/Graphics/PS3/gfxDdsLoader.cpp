/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#include <math.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "gfxDdsLoader.h"

//-----------------------------------------------------------------------------
// Description: Swap the bytes in a 32 bit value
// Parameters:	
// Returns:
// Notes:
// PCs, PS2 and PSP are little endian.  PS3 is big endian so need to swap 
// endian for some of the data
//-----------------------------------------------------------------------------
void swapEndian(void *val)
{
	unsigned int *ival = (unsigned int *)val;
    *ival = ((*ival >> 24) & 0x000000ff) |
            ((*ival >>  8) & 0x0000ff00) |
            ((*ival <<  8) & 0x00ff0000) |
            ((*ival << 24) & 0xff000000);
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// uint32_t getFileLen(char *filename)
// Description: 
// returns the length of the file in bytes
// Returns: 
// 0 on length of file
// Notes:
//-----------------------------------------------------------------------------
uint32_t //size of file in bytes
getFileLen
	(
	char *filename		//name of file to read	
	)
{
FILE* fp;
uint32_t fileLen;

if((fp = fopen(filename,"rb"))==NULL)
	return 0;

if(fseek(fp,0,SEEK_END)!=0) 
	return 0;

fileLen = ftell(fp);
fclose(fp);
return fileLen;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// long LoadFile(char *filename,unsigned int bytes,unsigned char *buffer)
// Description: 
// loads bytes amount of data into buffer from filename
// Returns: 
// 0 on failure or the number of bytes read
// Notes:
//-----------------------------------------------------------------------------
long //size of file in bytes
LoadFile
	(
	char *filename,					//name of file to read	
	unsigned int bytes,				//number of bytes to read
	unsigned char *buffer			//load the file here
	)
{
FILE* fp;

if((fp = fopen(filename,"rb"))==NULL)
	return 0;

if(fread(buffer,1,bytes,fp)!= bytes)
	return 0;

fclose(fp);
return bytes;
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// int32_t getImageSize(uint32_t w,uint32_t h,uint32_t components,uint32_t format)
// Description: 
// returns the size of a texture buffer
// header
// Returns: 
// Notes:
//-----------------------------------------------------------------------------
int32_t 
getImageSize(uint32_t w,
			 uint32_t h,
			 uint32_t components,
			 uint32_t format
			 )
{

switch(format)
	{
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		return ((w+3)/4)* ((h+3)/4)* 8;   
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
    case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		return ((w+3)/4)*((h+3)/4)* 16;   
	case GL_BGRA:
    case GL_BGR:
    case GL_LUMINANCE:
		return w*h*components;         
	default:
		printf("ERROR: unable to determine image size\n");
		exit(1);
	}


}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// bool ImageSpec(DDS_HEADER *ddsh, uint32_t *format,uint32_t *components)
// Description: 
// helper function that returns the format and number of components in a dds
// header
// Returns: 
// false on failure
// Notes:
//-----------------------------------------------------------------------------

bool ImageSpec(DDS_HEADER *ddsh, uint32_t *format,uint32_t *components)
{
assert(format);
assert(components);

if (ddsh->ddspf.dwFlags & DDSF_FOURCC)	//its a compressed texture
{
	switch(ddsh->ddspf.dwFourCC)
        {
		case FOURCC_DXT1:
			*format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            *components = 3;
            break;
		case FOURCC_DXT3:
			*format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            *components = 4;
            break;
        case FOURCC_DXT5:
			*format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            *components = 4;
            break;
        default:
			printf("ERROR: Uses a compressed texture of unsupported type\n");
			return false;
		}
    }
else
if (ddsh->ddspf.dwFlags == DDSF_RGBA && ddsh->ddspf.dwRGBBitCount == 32)
    {
    *format = GL_BGRA; 
    *components = 4;
    }
else if (ddsh->ddspf.dwFlags == DDSF_RGB  && ddsh->ddspf.dwRGBBitCount == 32)
	{
    *format = GL_BGRA; 
    *components = 4;
    }
else if (ddsh->ddspf.dwFlags == DDSF_RGB  && ddsh->ddspf.dwRGBBitCount == 24)
    {
    *format = GL_BGR; 
    *components = 3;
    }
else if (ddsh->ddspf.dwRGBBitCount == 8)
	{
	*format = GL_LUMINANCE; 
	*components = 1;
	}
else 
    {
	printf("ERROR: Uses a texture of unsupported type");
	return false;
    }

return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// bool gfxDdsLoad(char *filename,DDS_TEXTURE* dds)
// Description: 
// loads a dds texture file and fills out the dds structure
// Returns: 
// false on failure
// Notes:
//-----------------------------------------------------------------------------
bool
gfxDdsLoad(char *filename,DDS_TEXTURE* dds)
{
uint32_t fileLen;

//load the file
fileLen = getFileLen(filename);
if(!fileLen) 
	{
	printf("ERROR: failed to load %s",filename);
	return false;
	}

//unsigned char *buffer;
unsigned char *buffer = (unsigned char*)malloc(fileLen);
if(!buffer)
	{
	printf("ERROR: failed to malloc %d bytes",fileLen);
	return false;
	}
// Note: Either LoadFile and fileLen should both be the same type, probably unsigned
if (LoadFile(filename,fileLen,buffer)!=((long)fileLen))
	{
	printf("ERROR: failed to load %s",filename);
	return false;
	}

unsigned char *buff;
buff = buffer;

// read in file marker, make sure its a DDS file
if(strncmp((char*)buff,"DDS ",4)!=0)
	{
	printf("ERROR: %s is not a dds file",filename);
	return false;
	}
buff+=4;  //skip over header 

//read the dds header data
DDS_HEADER *ddsh;

//memcpy(&ddsh,buffer+4,sizeof(DDS_HEADER));
ddsh=(DDS_HEADER*)buff;
buff+=sizeof(DDS_HEADER);

uint32_t* t = (uint32_t*)ddsh;
for(unsigned int ddsCounterHeader=0; ddsCounterHeader<sizeof(DDS_HEADER)/4; ddsCounterHeader++)
	{
	swapEndian(t+ddsCounterHeader);
	}

TextureType type = TextureFlat;
if (ddsh->dwCaps2 & DDSF_CUBEMAP)	type = TextureCubemap;

// check if image is a volume texture
if ((ddsh->dwCaps2 & DDSF_VOLUME) && (ddsh->dwDepth > 0))
	{
	printf("ERROR: %s is a volume texture ",filename);
	return false;
	}
        
// get the format of the image
uint32_t	format;
uint32_t	components;

//get the texture format and number of color channels
ImageSpec(ddsh,&format,&components);

uint32_t width, height;
width = ddsh->dwWidth;
height = ddsh->dwHeight;

dds->buffer		= buffer;
dds->format		= format;
dds->components = components;
dds->height		= height;
dds->width		= width;

if(ddsh->dwMipMapCount==0) ddsh->dwMipMapCount++;

dds->mips		= ddsh->dwMipMapCount;

dds->surfaces = 1;
if(type ==TextureCubemap) dds->surfaces = 6;

//get pointers to the pixel data
uint32_t i,j;
for(i=0; i<dds->surfaces; i++)
	{
	printf("Surface %d\n",i);
	height=dds->height;
	width=dds->width;

	for(j=0; j<ddsh->dwMipMapCount; j++)
		{
		dds->image[i].pixels[j] = buff;
		buff+=getImageSize(width,height,components,format);
		width/=2; height/=2;
		}
	}

return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// GLenum getFormatFromComponents(uint32_t components)
// Description: 
// this is just a helper function used when loading textures.
// Returns: 
// a GLenim based the number of channels input
// Notes
//-----------------------------------------------------------------------------
GLenum getFormatFromComponents(uint32_t components)
{
GLenum formatEnum = GL_LUMINANCE;

switch(components)
	{
	case 1:
		formatEnum = GL_LUMINANCE;
		break;
	case 3:
		formatEnum = GL_RGB;
		break;
	case 4:
		formatEnum = GL_RGBA;
		break;
	default:
		printf("ERROR: Unknown pixel type\n");
		exit(0);
		}

return(formatEnum);
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// GLuint gfxLoadDDSTexture(char *filename)
// Description: 
// loads a texture from disk into PSGL and returns the texture name
// Returns: 
// texture name
// Notes:
// Will cause program to exit on failure
//-----------------------------------------------------------------------------
GLuint 
gfxLoadDDSTexture
(
 char		*filename
 )
{
	GLuint texture;

	DDS_TEXTURE dds;
	uint32_t test =  gfxDdsLoad(filename,&dds);
	if(test==false) 
	{
		printf("failed to load\n");
		exit(0);
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int32_t w = dds.width;
	int32_t h = dds.height;

	printf("file %s dds surfaces %d mips %d w %d h%d \n",filename,dds.surfaces,dds.mips,w,h);
	if(dds.surfaces!=1)	//its a cube map 
	{
		printf("ERROR: this is a cubemap\n");
		exit(0);
	}
	
	if(dds.format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT) printf("GL_COMPRESSED_RGB_S3TC_DXT1_EXT\n");
			if(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) printf("GL_COMPRESSED_RGBA_S3TC_DXT1_EXT\n");
			if(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT) printf("GL_COMPRESSED_RGBA_S3TC_DXT3_EXT\n");
			if(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT) printf("GL_COMPRESSED_RGBA_S3TC_DXT5_EXT\n");


	//load a compressed texture
		if( (dds.format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT) ||
			(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ||
			(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT) ||
			(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT))
		{
			for (uint32_t i = 0; i < dds.mips; i++)
			{
				uint32_t size = getImageSize(w,h,dds.components,dds.format);
				//printf("compressed texture %d %d %d %d 0x%x\n",i,w,h,size,dds.image[0].pixels[i]);
				glCompressedTexImage2D(GL_TEXTURE_2D,i,dds.format,w,h,0,size,dds.image[0].pixels[i]);
				w/=2; h/=2;
				if (w == 0) w = 1;
				if (h == 0) h = 1;
			}
		}
		else // load a non compressed texture
		{
			GLenum formatEnum = getFormatFromComponents(dds.components);
      if (formatEnum==GL_RGB || formatEnum==GL_LUMINANCE) glPixelStorei(GL_UNPACK_ALIGNMENT,1);
			for (uint32_t i = 0; i < dds.mips; i++)
			{
				//uint32_t size = getImageSize(w,h,dds.components,dds.format);
				//printf("non compressed texture %d w %d h%d format %d size %d 0x%x\n",i,w,h,dds.format,size,dds.image[0].pixels[i]);
				glTexImage2D(GL_TEXTURE_2D,i,dds.components,w,h,0,formatEnum,GL_UNSIGNED_BYTE,dds.image[0].pixels[i]);
				w/=2; h/=2;
				if (w == 0) w = 1;
				if (h == 0) h = 1;
			} 
      if (formatEnum==GL_RGB || formatEnum==GL_LUMINANCE) glPixelStorei(GL_UNPACK_ALIGNMENT,4);
		}

	// Basic OpenGL texture state setup
	if(dds.mips==1)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	free(dds.buffer); // at this point the file buffer is no longer needed
	return texture;	// return the texture name
}
//----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
//GLuint gfxLoadDDSTextureCubeMap(char *filename)
// Description: 
// loads a texture from disk into PSGL and returns the texture name
// Returns: 
// a texture name
// Notes:
// Will cause program to exit on failure
//-----------------------------------------------------------------------------
GLuint 
gfxLoadDDSTextureCubeMap
(
 char		*filename
 )
{
	GLuint texture;

	DDS_TEXTURE dds;
	uint32_t test =  gfxDdsLoad(filename,&dds);
	if(test==false) 
	{
		printf("failed to load\n");
		exit(0);
	}

	glEnable(GL_TEXTURE_CUBE_MAP);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int32_t w = dds.width;
	int32_t h = dds.height;

	printf("file %s dds surfaces %d mips %d w %d h%d \n",filename,dds.surfaces,dds.mips,w,h);
	if(dds.surfaces!=6)	//its not a cube map 
		{
		printf("ERROR: This is not a cube map\n");
		exit(0);
    	}

//	dds.mips =1; //set this to 1
	// loop through cubemap faces and load them as 2D textures 
	for (unsigned int n = 0; n < 6; n++)
		{
			GLenum target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + n;
			w = dds.width;
			h = dds.height;

			if(dds.format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT) printf("GL_COMPRESSED_RGB_S3TC_DXT1_EXT\n");
			if(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) printf("GL_COMPRESSED_RGBA_S3TC_DXT1_EXT\n");
			if(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT) printf("GL_COMPRESSED_RGBA_S3TC_DXT3_EXT\n");
			if(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT) printf("GL_COMPRESSED_RGBA_S3TC_DXT5_EXT\n");

			//load a compressed texture
			if( (dds.format == GL_COMPRESSED_RGB_S3TC_DXT1_EXT) ||
				(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ||
				(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT3_EXT) ||
				(dds.format == GL_COMPRESSED_RGBA_S3TC_DXT5_EXT))
			{
				for (uint32_t i = 0; i < dds.mips; i++)
				{
					uint32_t size = getImageSize(w,h,dds.components,dds.format);
			//		printf("compressed texture %d %d %d %d 0x%x\n",i,w,h,size,dds.image[n].pixels[i]);
					glCompressedTexImage2D(target,i,dds.format,w,h,0,size,dds.image[n].pixels[i]); //changed n to 0
					w/=2; h/=2;
				}
			}
			else
			{
				//dont think I'll support uncompressed cubemaps....
				printf("Uncompressed cubemap not a good idea!!\n");
				exit(0);
			}
		}
	

	
	// Basic OpenGL texture state setup
	if(dds.mips==1)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glDisable(GL_TEXTURE_CUBE_MAP);

	free(dds.buffer); // at this point the file buffer is no longer needed
	return texture;	// return the texture name
}
//----------------------------------------------------------------------------


