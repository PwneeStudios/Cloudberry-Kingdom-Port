#include <CloudberryKingdom.h>
#include <Core.h>

#include <cafe/os.h>
#include <Utility/Log.h>

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
	OSLog osLog;
	Log theLog;

	theLog.AddListener( osLog );

	CloudberryKingdom *game = new CloudberryKingdom;
	Core *core = new Core( *game );
	int result = core->Run();
	delete core;
	delete game;

	theLog.RemoveListener( osLog );

	return result;
}
