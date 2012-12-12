#include <Core.h>
#include <CloudberryKingdom.h>

#include <iostream>
#include <Utility/Log.h>

#include <Content/Filesystem.h>

class StdOutLog : public LogListener
{
	
public:

	void Write( const std::string &text )
	{
		std::cout << text;
	}

};

int main( int argc, char *argv[] )
{
	Filesystem filesystem;

	StdOutLog stdLog;
	Log theLog;

	theLog.AddListener( stdLog );

	CloudberryKingdomWrapper game;
	Core core( game );

	int result = core.Run();

	return result;
}
