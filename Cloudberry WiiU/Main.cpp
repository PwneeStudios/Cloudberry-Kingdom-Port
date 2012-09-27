#include <cafe.h>
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

		float x = 2.f * ( float )rand() / RAND_MAX - 1.f;
		float y = 2.f * ( float )rand() / RAND_MAX - 1.f;
		float w = ( float )rand() / RAND_MAX - 0.5f;
		float h = ( float )rand() / RAND_MAX - 0.5f;

		SimpleQuad quad;
		quad.Color = Vector4( ( float )rand() / RAND_MAX,
			( float )rand() / RAND_MAX,
			( float )rand() / RAND_MAX,
			( float )rand() / RAND_MAX
		);

		quad.V[ 0 ] = Vector2( x, y );
		quad.V[ 3 ] = Vector2( x + w, y );
		quad.V[ 2 ] = Vector2( x + w, y + h );
		quad.V[ 1 ] = Vector2( x, y + h );
		QUAD_DRAWER->Draw( quad );
	}

};

int main( int argc, char *argv[] )
{
    MyGame game;
	Core core( game );
    
    return core.Run();
}
