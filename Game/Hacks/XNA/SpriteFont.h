#ifndef _SPRITEFONT_H_
#define _SPRITEFONT_H_

#include <Core.h>

#include <Content\ResourcePtr.h>

#include <Math/Vectors.h>
#include <string>

struct SpriteFont
{

	/// Coordinates for all letters.
	ResourcePtr< Font > font_;

	/// Font texture.
	ResourcePtr< Texture > fontTexture_;

	float Spacing;
	int LineSpacing;

	struct SpriteFontInternal *internal_;
	
	SpriteFont( const std::string &Path );
	~SpriteFont();
	Vector2 MeasureString( const std::wstring &text );

};

#endif
