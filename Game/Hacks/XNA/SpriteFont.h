#ifndef _SPRITEFONT_H_
#define _SPRITEFONT_H_

struct SpriteFont
{

	float Spacing;
	int LineSpacing;

	SpriteFont() :
		Spacing( 0 ),
		LineSpacing( 0 )
	{
	}

	Vector2 MeasureString( const std::wstring &text )
	{
		return Vector2();
	}

};

#endif
