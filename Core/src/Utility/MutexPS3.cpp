#include <Utility/Mutex.h>

struct MutexInternal
{
};

Mutex::Mutex() :
	internal_( new MutexInternal )
{
}

Mutex::~Mutex()
{
	delete internal_;
}

void Mutex::Lock()
{
}

void Mutex::Unlock()
{
}
