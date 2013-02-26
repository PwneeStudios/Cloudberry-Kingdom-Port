#include <Utility/Error.h>

#include <list>

std::list< ErrorType > GLOBAL_ERROR_QUEUE;

void DisplayError( const ErrorType &errorCode )
{
	GLOBAL_ERROR_QUEUE.push_back( errorCode );
}
