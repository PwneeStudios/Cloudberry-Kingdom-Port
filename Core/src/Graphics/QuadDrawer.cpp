#include <Graphics/QuadDrawer.h>

// Single instance of the quad drawer.
template<> QuadDrawer *Singleton< QuadDrawer >::singleton_ = 0;

QuadDrawer::QuadDrawer()
{

}

QuadDrawer::~QuadDrawer()
{

}
