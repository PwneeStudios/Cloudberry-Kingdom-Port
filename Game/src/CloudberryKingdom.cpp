#include <CloudberryKingdom.h>

#include <Core.h>
#include <cstdlib>
#include <Graphics/QuadDrawer.h>
#include <Graphics/Types.h>

void CloudberryKingdom::Update()
{
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
