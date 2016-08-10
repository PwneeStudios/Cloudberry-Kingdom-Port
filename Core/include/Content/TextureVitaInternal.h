#ifndef _TEXTURE_VITA_INTERNAL_H_
#define _TEXTURE_VITA_INTERNAL_H_

#include <gxm.h>

struct TextureVitaInternal
{
	SceGxmTexture	Texture;
	void *			TextureData;
	SceUID			AllocationID;
};

#endif
