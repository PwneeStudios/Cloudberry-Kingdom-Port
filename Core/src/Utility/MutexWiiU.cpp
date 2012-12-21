#include <Utility/Mutex.h>

#include <cafe/os.h>

struct MutexInternal
{
	OSMutex M;
};

Mutex::Mutex() :
	internal_( new MutexInternal )
{
	OSInitMutex( &internal_->M );
}

Mutex::~Mutex()
{
	delete internal_;
}

void Mutex::Lock()
{
	OSLockMutex( &internal_->M );
}

void Mutex::Unlock()
{
	OSUnlockMutex( &internal_->M );
}
