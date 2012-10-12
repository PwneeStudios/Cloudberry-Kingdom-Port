#include <CloudberryKingdom.h>
#include <Core.h>

int main( int argc, char *argv[] )
{
	CloudberryKingdom *game = new CloudberryKingdom;
	Core *core = new Core( *game );
	int result = core->Run();
	delete core;
	delete game;

	return result;
}

/*#include <cafe.h>
#include <cafe/demo.h>

#include <Core.h>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/Types.h>

#include <cafe/os.h>

class MyGame : public GameLoop
{

public:

	void Update()
	{
		static OSTime lastTime = OSGetTime();
		OSTime currentTime = OSGetTime();
		OSTime diff = currentTime - lastTime;
		lastTime = currentTime;
		static OSTime accumulator = 0;
		accumulator += diff;
		static u32 frames = 0;
		
		if( OSTicksToSeconds( accumulator ) == 5 )
		{
			OSReport( "FPS = %d\n", frames / 5 );
			frames = 0;
			accumulator = 0;
		}

		++frames;

		for( int i = 0; i < 1024; ++i )
		{
			int x = rand() % 1024;
			int y = rand() % 576;
			int w = rand() % 256;
			int h = rand() % 144;

			SimpleQuad quad;
			quad.Color = Vector4( ( float )rand() / RAND_MAX,
				( float )rand() / RAND_MAX,
				( float )rand() / RAND_MAX,
				1
			);

			quad.V[ 0 ] = Vector2( x, y );
			quad.V[ 3 ] = Vector2( x + w, y );
			quad.V[ 2 ] = Vector2( x + w, y + h );
			quad.V[ 1 ] = Vector2( x, y + h );
			QUAD_DRAWER->Draw( quad );
		}
	}

};

int main( int argc, char *argv[] )
{
    MyGame game;
	Core core( game );
    
    return core.Run();
}*/
