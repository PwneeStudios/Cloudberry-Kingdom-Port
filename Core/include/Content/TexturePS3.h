#ifndef _TEXTURE_PS3_H_
#define _TEXTURE_PS3_H_

#include "Resource.h"
#include <vector>

/**
 * A Texture resource for PC.
 */
class TexturePS3 : public Resource
{

public:

	/// Platform specific internal bits.
	struct TexturePS3Internal *internal_;

	TexturePS3();
	~TexturePS3();

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

	void Activate( class EffectParameter &parameter );

};

#endif
