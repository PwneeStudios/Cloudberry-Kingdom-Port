#include <CloudberryKingdom.h>

#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdlib>
#include <Graphics/QuadDrawer.h>
#include <Graphics/Types.h>

void CloudberryKingdom::Update()
{
	ResourcePtr< Texture > texture = CONTENT->Load< Texture >( "Art/Bob_Run_0001.png" );

	for( int i = 0; i < 1024; ++i )
	{
#pragma warning( push )
#pragma warning( disable: 4244 )
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
		quad.V[ 1 ] = Vector2( x, y + h );
		quad.V[ 2 ] = Vector2( x + w, y + h );
		quad.V[ 3 ] = Vector2( x + w, y );

		quad.T[ 0 ] = Vector2( 0, 0 );
		quad.T[ 1 ] = Vector2( 0, 1 );
		quad.T[ 2 ] = Vector2( 1, 1 );
		quad.T[ 3 ] = Vector2( 1, 0 );

		quad.Diffuse = texture;
		QUAD_DRAWER->Draw( quad );
#pragma warning( pop )
	}
}
