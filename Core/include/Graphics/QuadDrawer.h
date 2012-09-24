#ifndef _QUAD_DRAWER_H_
#define _QUAD_DRAWER_H_

#include <Architecture/Singleton.h>

/**
 * Drawer of quads.
 */
class QuadDrawer : public Singleton< QuadDrawer >
{

private:

	/// No copying.
	QuadDrawer( const QuadDrawer & ) { }

	/// No assignment.
	QuadDrawer &operator = ( const QuadDrawer & ) { }

public:

	QuadDrawer();
	~QuadDrawer();

};

#endif
