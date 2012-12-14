#ifndef _SAMPLERSTATE_H_
#define _SAMPLERSTATE_H_

#include <enums.h>

struct SamplerState
{

	GfxTextureAddressMode AddressU;
	GfxTextureAddressMode AddressV;

	SamplerState() :
		AddressU( GfxTextureAddressMode_Clamp ),
		AddressV( GfxTextureAddressMode_Clamp ),
	{
	}

};

#endif
