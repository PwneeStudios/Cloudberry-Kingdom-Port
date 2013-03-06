#include "SpriteFont.h"

#include <Graphics/TextDrawer.h>

#include <Content/Font.h>
#include <Content/Wad.h>

#include <Hacks/String.h>

struct SpriteFontInternal
{
};

SpriteFont::SpriteFont( const std::string &Path ) :
	Spacing( 0 ),
	LineSpacing( 0 )
{
	font_ = CONTENT->Load< Font >( Path + ".txt" );
	fontTexture_ = CONTENT->Load< Texture >( font_->GetTexturePath() );
}

SpriteFont::~SpriteFont()
{
}

Vector2 SpriteFont::MeasureString( const std::wstring &text )
{
	return TEXT_DRAWER->MeasureString( font_, WstringToUtf8( text ) );
}