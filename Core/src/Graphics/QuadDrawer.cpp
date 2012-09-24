#include <Graphics/QuadDrawer.h>

// Single instance of the quad drawer.
template<> QuadDrawer *Singleton< QuadDrawer >::singleton_ = 0;

// Private.
QuadDrawer::QuadDrawer( const QuadDrawer & )
{
}

// Private.
QuadDrawer &QuadDrawer::operator = ( const QuadDrawer & )
{
    return *this;
}

QuadDrawer::QuadDrawer()
{

}

QuadDrawer::~QuadDrawer()
{

}

QuadDrawer &QuadDrawer::GetSingleton()
{
	assert( singleton_ );
	return *singleton_;
}
