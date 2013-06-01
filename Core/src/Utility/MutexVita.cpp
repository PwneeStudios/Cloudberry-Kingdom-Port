#include <Utility/Mutex.h>

#include <cassert>

struct MutexInternal
{
};

Mutex::Mutex() :
	internal_( new MutexInternal )
{
}

Mutex::~Mutex()
{
}

void Mutex::Lock()
{
}

void Mutex::Unlock()
{
}
