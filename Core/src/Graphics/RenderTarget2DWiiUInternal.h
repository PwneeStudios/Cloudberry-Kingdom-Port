#ifndef _RENDER_TARGET_2D_WIIU_INTERNAL_H_
#define _RENDER_TARGET_2D_WIIU_INTERNAL_H_

#include <cafe/gx2.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>

struct RenderTarget2DInternal
{
	GX2ColorBuffer ColorBuffer;
	Texture *RTTexture;
	ResourceHolder Holder;
	GX2ContextState *ContextState;
};

#endif
