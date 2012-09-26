#ifndef _QUAD_DRAWER_PC_H_
#define _QUAD_DRAWER_PC_H_

#include <ForwardDeclarations.h>

/**
 * Drawer of quads.
 */
class QuadDrawerPc
{

private:

	/// No copying.
	QuadDrawerPc( const QuadDrawerPc & ) { }

	/// No assignment.
	QuadDrawerPc &operator = ( const QuadDrawerPc & ) { return *this; }

public:

	QuadDrawerPc();
	~QuadDrawerPc();

	/**
	 * @see QuadDrawer::Draw
	 */
	void Draw( const SimpleQuad &quad );

};

#endif
