#ifndef _SAMPLERSTATE_H_
#define _SAMPLERSTATE_H_

#include <enums.h>

struct SamplerState
{

	GfxTextureAddressMode AddressU;
	GfxTextureAddressMode AddressV;

	SamplerState()
	{
	}

};

#endif
