#include <GL/glew.h>
#include <GL/glfw.h>

#include <Core.h>
#include <GameLoop.h>

class MyGame : public GameLoop
{

public:

	void Update()
	{
		glClear( GL_COLOR_BUFFER_BIT );

		glfwSwapBuffers();

		if( glfwGetKey( GLFW_KEY_ESC ) || !glfwGetWindowParam( GLFW_OPENED ) )
			CORE.Exit();
	}

};

int main( int argc, char *argv[] )
{
	MyGame game;
	Core core( game );

	return core.Run();
}
