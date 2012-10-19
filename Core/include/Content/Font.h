/**
 * @file
 *
 * Font resource.
 */
#ifndef _FONT_H_
#define _FONT_H_

#include <Math/Vectors.h>
#include "Resource.h"
#include <string>

class Font : public Resource
{

	/// Table of quads for all characters.
	Vector4 quads_[ 256 ];

	/// Dimensions of every character in screen space.
	Vector2 dimensions_[ 256 ];

	/// Texture path.
	std::string texturePath_;

public:

	/**
	 * @see Resource::Load()
	 */
	void Load();

	/**
	 * @see Resource::Unload()
	 */
	void Unload();

	/// Get a quad for a particular character.
	/**
	 * @param c Character to look up in the table.
	 * @return Texture coordinates for the letter.
	 */
	const Vector4 &GetQuad( char c ) const
	{
		return quads_[ c ];
	}

	/// Get character dimensions.
	/**
	 * @param c Character to look up.
	 * @return Pixel dimensions of character.
	 */
	const Vector2 &GetDimensions( char c ) const
	{
		return dimensions_[ c ];
	}

	/// Get path to font texture.
	/**
	 * @return Path to font texture.
	 */
	const std::string &GetTexturePath() const
	{
		return texturePath_;
	}

};

#endif
