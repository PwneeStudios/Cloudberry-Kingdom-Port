/**
 * @file
 *
 * Texture resource.
 */
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Resource.h"

#ifdef CAFE
	#include "TextureWiiU.h"
#elif PS3
	#include "TexturePS3.h"
#else
	#include "TexturePc.h"
#endif

/**
 * A texture resource.
 */
class Texture : public Resource
{

	/// Platform specific implementation.
#ifdef CAFE
	friend struct RenderTarget2D;
	TextureWiiU impl_;
#elif PS3
	friend struct RenderTarget2D;
	TexturePS3 impl_;
#else
	TexturePc impl_;
#endif

private:

	/// No copying.
	Texture( const Texture & ) { }

	/// No assignment.
	Texture &operator = ( const Texture & ) { return *this; }

public:

	Texture() { }
	~Texture() { }

	/**
	 * @see Resource::Load()
	 */
	void Load()
	{
		impl_.Load();
	}

	/**
	 * @see Resource::Unload()
	 */
	void Unload()
	{
		impl_.Unload();
	}

	/**
	 * @see Resource::GpuCreate()
	 */
	void GpuCreate()
	{
		impl_.GpuCreate();
	}

	/**
	 * @see Resource::GpuDestroy()
	 */
	void GpuDestroy()
	{
		impl_.GpuDestroy();
	}

	/**
	 * @see Resource::SetPath()
	 */
	void SetPath( const std::string &path )
	{
		impl_.SetPath( path );
	}

	/**
	 * @see Resource::GetPath()
	 */
	const std::string &GetPath() const
	{
		return impl_.GetPath();
	}

	/**
	 * @see Resource::IsLoaded()
	 */
	bool IsLoaded() const
	{
		return impl_.IsLoaded();
	}

	/// Activate the texture on the Gpu.
	/**
	 * @param sampler Sampler location.
	 */
	void Activate( unsigned int sampler )
	{
		impl_.Activate( sampler );
	}

#ifdef PS3
	void Activate( class EffectParameter &parameter )
	{
		impl_.Activate( parameter );
	}
#endif

};

#endif
