#include <Core.h>

#include <cstdlib>
#include <Utility/Limits.h>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>

// Single instance of the core.
template<> Core *Singleton< Core >::singleton_ = 0;

// Private.
Core::Core( const Core &other ) :
	impl_( other.game_ ),
	game_( other.game_ )
{

}

// Private.
Core &Core::operator = ( const Core &rhs )
{
	return *this;
}

Core::Core( GameLoop &game ) :
	impl_( game ),
	game_( game )
{

}

Core::~Core()
{

}

Core &Core::GetSingleton()
{
	assert( singleton_ );
	return *singleton_;
}
