#include <Core.h>
#include <CloudberryKingdom.h>

#include <cafe/os.h>
#include <Utility/Log.h>

#include <Content/Filesystem.h>

class OSLog : public LogListener
{
	
public:

	void Write( const std::string &text )
	{
		OSReport( text.c_str() );
	}
};

int main( int argc, char *argv[] )
{
	Filesystem filesystem;

	OSLog osLog;
	Log theLog;

	theLog.AddListener( osLog );

	CloudberryKingdomWrapper *game = new CloudberryKingdomWrapper;
	Core *core = new Core( *game );
	int result = core->Run();
	delete core;
	delete game;

	theLog.RemoveListener( osLog );

	return result;
}
