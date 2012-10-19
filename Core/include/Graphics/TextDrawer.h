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
	 */
	void Draw( const std::string &text, const Vector2 &position );

};

#endif
