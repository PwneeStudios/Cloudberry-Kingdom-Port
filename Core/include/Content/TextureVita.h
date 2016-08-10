#ifndef _TEXTURE_VITA_H_
#define _TEXTURE_VITA_H_

#include "Resource.h"
#include <vector>

/**
 * A Texture resource for PC.
 */
class TextureVita : public Resource
{

public:

	/// Platform specific internal bits.
	struct TextureVitaInternal *internal_;

	TextureVita();
	~TextureVita();

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
