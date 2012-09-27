#ifndef _QUAD_DRAWER_H_
#define _QUAD_DRAWER_H_

#include <ForwardDeclarations.h>

// Pick the implementation we want to use.
#ifdef CAFE
	#include "QuadDrawerWiiU.h"
#else
	#include "QuadDrawerPc.h"
#endif

/**
 * Drawer of quads.
 */
class QuadDrawer
{

	/// IMPL from the PIMPL.
#ifdef CAFE
	QuadDrawerWiiU impl_;
#else
	QuadDrawerPc impl_;
#endif

private:

	/// No copying.
	QuadDrawer( const QuadDrawer & ) { }

	/// No assignment.
	QuadDrawer &operator = ( const QuadDrawer & ) { return *this; }

public:

	QuadDrawer() { }
	~QuadDrawer() { }

	/// Draw a simple quad.
	/**
	 * @param quad Quad to draw.
	 */
	void Draw( const SimpleQuad &quad )
	{
		impl_.Draw( quad );
	}

	/// Flush any quads that need drawing.
	void Flush()
	{
		impl_.Flush();
	}

};



#endif
