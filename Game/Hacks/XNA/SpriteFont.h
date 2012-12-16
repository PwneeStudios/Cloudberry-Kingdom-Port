#ifndef _SPRITEFONT_H_
#define _SPRITEFONT_H_

#include <Math/Vectors.h>
#include <string>

struct SpriteFont
{

	float Spacing;
	int LineSpacing;

	struct SpriteFontInternal *internal_;
	
	SpriteFont();
	~SpriteFont();
	Vector2 MeasureString( const std::wstring &text );

};

#endif
