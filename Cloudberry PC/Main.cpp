#include <cstdlib>
#include <Core.h>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/Types.h>

class MyGame : public GameLoop
{

public:

	void Update()
	{
		for( int i = 0; i < 512; ++i )
		{
			int x = rand() % 1024;
			int y = rand() % 576;
			int w = rand() % 256;
			int h = rand() % 144;

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
	}

};

int main( int argc, char *argv[] )
{
	MyGame game;
	Core core( game );

	return core.Run();
}
