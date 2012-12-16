#ifndef _TEXT_DRAWER_H_
#define _TEXT_DRAWER_H_

#include <Content/ResourcePtr.h>
#include <ForwardDeclarations.h>
#include <string>

/**
 * Drawer of text.
 */
class TextDrawer
{

	/// Coordinates for all letters.
	ResourcePtr< Font > font_;

	/// Font texture.
	ResourcePtr< Texture > fontTexture_;

public:

	TextDrawer();
	~TextDrawer();

	/// Draw a string of text.
	/**
	 * @param text Text to draw.
	 * @param position Screen position of upper left hand corner.
	 * @param color Text color.
	 * @param scale Scale of text.
	 */
	void Draw( const std::string &text, const Vector2 &position, const Vector4 &color, const Vector2 &scale );

	/// Measure the size of the text.
	/**
	 * @param text Text to be measured.
	 * @return Vector with the width and height of the text.
	 */
	Vector2 MeasureString( const std::string &text );

};

#endif
