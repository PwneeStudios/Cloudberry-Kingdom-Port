#include <Core.h>
#include <CloudberryKingdom.h>

#include <cafe/os.h>
#include <cafe/mem.h>
#include <Utility/Log.h>

#include <Content/Filesystem.h>

class OSLog : public LogListener
{
	
public:

	void Write( const std::string &text )
	{
#ifdef DEBUG
		OSReport( text.c_str() );
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


int main( int argc, char *argv[] )
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
