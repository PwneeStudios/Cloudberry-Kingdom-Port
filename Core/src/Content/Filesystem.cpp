#include <Content/Filesystem.h>

#include <cassert>

template<> Filesystem *Singleton< Filesystem >::singleton_ = 0;

Filesystem &Filesystem::GetSingleton()
{
	assert( singleton_ );
	return *singleton_;
}