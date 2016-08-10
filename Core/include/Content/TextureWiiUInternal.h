#ifndef _TEXTURE_WIIU_INTERNAL_H_
#define _TEXTURE_WIIU_INTERNAL_H_

#include <cafe/gx2.h>

struct TextureInternal
{
	GX2Texture *Texture;
	char *Buffer;
};

#endif
