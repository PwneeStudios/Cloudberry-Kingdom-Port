#include <Utility/Mutex.h>

#include <cassert>
#include <pthread.h>

struct MutexInternal
{
	pthread_mutex_t PMutex;
};

Mutex::Mutex() :
	internal_( new MutexInternal )
{
	int ret = pthread_mutex_init( &internal_->PMutex, NULL );
	assert( !ret );
}

Mutex::~Mutex()
{
	pthread_mutex_destroy( &internal_->PMutex );
	delete internal_;
}

void Mutex::Lock()
{
	pthread_mutex_lock( &internal_->PMutex );
}

void Mutex::Unlock()
{
	pthread_mutex_unlock( &internal_->PMutex );
}
