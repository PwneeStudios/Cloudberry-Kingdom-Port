#ifndef _TEXTURE_WIIU_H_
#define _TEXTURE_WIIU_H_

#include "Resource.h"

/**
 * A Texture resource for WiiU.
 */
class TextureWiiU : public Resource
{

	struct TextureInternal *internal_;

public:

	TextureWiiU();
	~TextureWiiU();

	/**
	 * @see Resource::Load()
	 */
	void Load();

	/**
	 * @see Resource::Unload()
	 */
	void Unload();

	/**
	 * @see Resource::GpuCreate()
	 */
	void GpuCreate();

	/**
	 * @see Resource::GpuDestroy()
	 */
	void GpuDestroy();

	/**
	 * @see Texture::Activate()
	 */
	void Activate( unsigned int sampler );

};

#endif
