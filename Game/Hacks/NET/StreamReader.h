#ifndef _STREAMREADER_H_
#define _STREAMREADER_H_

#include "Hacks/NET/Stream.h"

class StreamReader
{

public:

	StreamReader( const Stream &s )
	{
	}

	StreamReader( const std::shared_ptr<Stream> &s )
	{
	}

	std::wstring ReadLine()
	{
		return _T( "" );
	}

	void Close() { }

};

#endif
