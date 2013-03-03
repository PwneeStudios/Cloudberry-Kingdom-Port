#ifndef _TEXTURE_PS3_INTERNAL_H_
#define _TEXTURE_PS3_INTERNAL_H_

struct TexturePS3Internal
{
	psglTextureReference Ref;
	unsigned char *FileData;
	unsigned int FileLength;
};

#endif
