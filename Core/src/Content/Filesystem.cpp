#include <Content/Filesystem.h>

#include <PwneeAssert.h>

template<> Filesystem *Singleton< Filesystem >::singleton_ = 0;

Filesystem::Filesystem()
{
}

Filesystem::~Filesystem()
{
}

Filesystem &Filesystem::GetSingleton()
{
	assert( singleton_ );
	return *singleton_;
}