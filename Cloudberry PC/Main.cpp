#include <GL/glew.h>
#include <GL/glfw.h>
#include <cstdlib>

int main( int argc, char *argv[] )
{
	int running = GL_TRUE;

	if( !glfwInit() )
		exit( EXIT_FAILURE );

	if( !glfwOpenWindow( 300, 300, 0, 0, 0,
		0, 0, 0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	if( GLEW_OK != glewInit() )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}


	while( running )
	{
		glClear( GL_COLOR_BUFFER_BIT );

		glfwSwapBuffers();

		running = !glfwGetKey( GLFW_KEY_ESC ) &&
			glfwGetWindowParam( GLFW_OPENED );
	}

	glfwTerminate();

	exit( EXIT_SUCCESS );

	return 0;
}
