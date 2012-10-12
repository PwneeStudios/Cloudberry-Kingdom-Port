#ifndef _TEXTURE_PC_H_
#define _TEXTURE_PC_H_

#include "Resource.h"
#include <vector>

/**
 * A Texture resource for PC.
 */
class TexturePc : public Resource
{

	/// TexturePc width.
	int width_;

	/// TexturePc height.
	int height_;

	/// TexturePc data.
	std::vector< char > data_;

	/// Platform specific internal bits.
	struct TexturePcInternal *internal_;

public:

	TexturePc();
	~TexturePc();

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

	/// Activate the texture on the Gpu.
	void Activate();

private:

	/** Load a PNG TexturePc. */
	void loadPng();

	/** Handle a 24bit RGB stream. */
	void processPngIdat24Bpp( const std::vector< char > &uncompressed );

	/** Handle a 32bit RGBA stream. */
	void processPngIdat32Bpp( const std::vector< char > &uncompressed );

	/**
		* @brief Unfilter a single scanline.
		* @param out Output buffer for unfiltered scanline data.
		* @param scanline Input scanline data.
		* @param lastOut Previous unfiltered scanline.
		* @param filterType Type of filter used for this scanline.
		* @param bpp Bytes per pixel.
		* @param scalineRowBytes Number of bytes in a single scanline row.
		*/
	void unfilterPngScanline( unsigned char *out, const unsigned char *scanline,
		const unsigned char *lastOut, char filterType, int bpp, int scanlineRowBytes );

	/** Uncompress one buffer into another. */
	bool uncompress( const std::vector< char > &compressed, std::vector< char > &uncompressed );

};

#endif
