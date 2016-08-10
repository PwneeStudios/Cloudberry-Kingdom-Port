#include <Utility/Error.h>

#include <list>
#include <Utility/Mutex.h>

std::list< ErrorType >	GLOBAL_ERROR_QUEUE;
static Mutex *			ErrorQueueMutex		= NULL;

void InitializeErrorSystem()
{
	ErrorQueueMutex = new Mutex();
}

void ShutdownErrorSystem()
{
	delete ErrorQueueMutex;
	ErrorQueueMutex = NULL;
}

void DisplayError( const ErrorType &errorCode )
{
	ErrorQueueMutex->Lock();
	GLOBAL_ERROR_QUEUE.push_back( errorCode );
	ErrorQueueMutex->Unlock();
}
