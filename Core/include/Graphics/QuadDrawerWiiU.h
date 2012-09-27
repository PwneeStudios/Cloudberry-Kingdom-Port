#ifndef _QUAD_DRAWER_WIIU_H_
#define _QUAD_DRAWER_WIIU_H_

#include <ForwardDeclarations.h>

/**
 * Drawer of quads.
 */
class QuadDrawerWiiU
{

	// Internal bits that we don't want to expose.
	struct QuadDrawerInternal *internal_;

private:

	/// No copying.
	QuadDrawerWiiU( const QuadDrawerWiiU & ) { }

	/// No assignment.
	QuadDrawerWiiU &operator = ( const QuadDrawerWiiU & ) {	return *this; }

public:

	QuadDrawerWiiU();
	~QuadDrawerWiiU();

	/**
	 * @see QuadDrawer::Draw
	 */
	void Draw( const SimpleQuad &quad );

	/**
	 * @see QuadDrawer::Flush
	 */
	void Flush();

};

#endif
