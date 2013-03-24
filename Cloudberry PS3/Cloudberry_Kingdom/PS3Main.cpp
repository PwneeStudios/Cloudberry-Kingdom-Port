#include <Core.h>
#include <CloudberryKingdom.h>
#include <Content/Filesystem.h>
#include <stdlib.h>
#include <stdio.h>

#include <Utility/Log.h>

class OSLog : public LogListener
{
	
public:

	void Write( const std::string &text )
	{
#ifdef DEBUG
		printf( text.c_str() );
#endif
	}
};

namespace boost
{
	void throw_exception(std::exception const & e)
	{
		LOG_WRITE( e.what() );
	}
}

int main(int argc, char *argv)
{
	OSLog osLog;
	Log theLog;

	Filesystem *filesystem = new Filesystem;
	
	theLog.AddListener( osLog );

	CloudberryKingdomWrapper *game = new CloudberryKingdomWrapper;
	Core *core = new Core( *game );
	int result = core->Run();
	delete core;
	delete game;

	delete filesystem;

	theLog.RemoveListener( osLog );

	_Exit( 0 );
	return result;
}
