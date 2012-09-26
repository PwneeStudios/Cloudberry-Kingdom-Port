#include <Graphics/QuadDrawerPc.h>

#include <cassert>
#include <GL/glew.h>
#include <Graphics/Types.h>

QuadDrawerPc::QuadDrawerPc()
{
	glShadeModel( GL_SMOOTH );
	glClearColor( 0, 0, 0, 0 );
	glClearDepth( 1 );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glViewport( 0, 0, 1024, 576 );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, 1024, 576, 0, 0, 1 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}

QuadDrawerPc::~QuadDrawerPc()
{
}

void QuadDrawerPc::Draw( const SimpleQuad &quad )
{
	glBegin( GL_QUADS );
	glColor4fv( reinterpret_cast< const GLfloat * >( &quad.Color ) );
	for( int i = 0; i < 4; ++i )
		glVertex2fv( reinterpret_cast< const GLfloat * >( &quad.V[ i ] ) );
	glEnd();
}
