#include "SpriteFont.h"

#include <Core.h>
#include <Graphics/TextDrawer.h>
#include <Hacks/String.h>

struct SpriteFontInternal
{
};

SpriteFont::SpriteFont() :
	Spacing( 0 ),
	LineSpacing( 0 )
{
}

SpriteFont::~SpriteFont()
{
}

Vector2 SpriteFont::MeasureString( const std::wstring &text )
{
	return TEXT_DRAWER->MeasureString( WstringToUtf8( text ) );
}