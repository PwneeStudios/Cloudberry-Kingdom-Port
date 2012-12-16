#include <Graphics/TextDrawer.h>

#include <Content/Font.h>
#include <Content/Wad.h>
#include <Core.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/Types.h>
#include <Utility/Log.h>

TextDrawer::TextDrawer() :
	font_( 0 ),
	fontTexture_( 0 )
{
	font_ = CONTENT->Load< Font >( "Fonts/Grobold_42.txt" );
	fontTexture_ = CONTENT->Load< Texture >( font_->GetTexturePath() );
}

TextDrawer::~TextDrawer()
{
}

void TextDrawer::Draw( const std::string &text, const Vector2 &position, const Vector4 &color, const Vector2 &scale )
{
	Vector2 p( position );
	for( size_t i = 0; i < text.size(); ++i)
	{
		const Vector4 &tq = font_->GetQuad( text[ i ] );
		const Vector2 &d = font_->GetDimensions( text[ i ] );

		SimpleQuad quad;
		quad.Color = color;
		quad.V[ 0 ] = Vector2( p.x(), p.y() );
		quad.V[ 1 ] = Vector2( p.x(), p.y() + d.y() * scale.Y );
		quad.V[ 2 ] = Vector2( p.x() + d.x() * scale.X, p.y() + d.y() * scale.Y );
		quad.V[ 3 ] = Vector2( p.x() + d.x() * scale.X, p.y() );

		quad.T[ 1 ] = Vector2( tq.x(), tq.y() );
		quad.T[ 0 ] = Vector2( tq.x(), tq.y() + tq.w() );
		quad.T[ 3 ] = Vector2( tq.x() + tq.z(), tq.y() + tq.w() );
		quad.T[ 2 ] = Vector2( tq.x() + tq.z(), tq.y() );
		quad.Diffuse = fontTexture_;

		QUAD_DRAWER->Draw( quad );
		p += Vector2( d.x() + font_->GetCharSpacing(), 0 ) * scale;
	}
}

Vector2 TextDrawer::MeasureString( const std::string &text )
{
	Vector2 size;

	for( size_t i = 0; i < text.size(); ++i )
	{
		const Vector2 &dim = font_->GetDimensions( text[ i ] );
		size.X += dim.X;
		size.Y = __max( size.Y, dim.Y );
	}

	return size;
}
