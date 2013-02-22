#include <Utility/Error.h>

#include <list>

std::list< int > GLOBAL_ERROR_QUEUE;

void DisplayError( int errorCode )
{
	GLOBAL_ERROR_QUEUE.push_back( errorCode );
}
