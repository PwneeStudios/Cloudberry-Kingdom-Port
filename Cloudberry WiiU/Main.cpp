#include <cafe.h>
#include <cafe/demo.h>

#include <Core.h>
#include <GameLoop.h>

class MyGame : public GameLoop
{

public:

	void Update()
	{
		OSReport( "Hello, Cloudberry Kingdom!\n" );
		CORE.Exit();
	}

};

int main( int argc, char *argv[] )
{
    MyGame game;
	Core core( game );
    
    return core.Run();
}
