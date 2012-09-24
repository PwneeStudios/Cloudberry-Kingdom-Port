#include <Core.h>

#include <cstdlib>
#include <GameLoop.h>
#include <GL/glew.h>
#include <GL/glfw.h>

// Single instance of the core.
template<> Core *Singleton< Core >::singleton_ = 0;

// Private.
Core::Core( const Core &other ) :
	game_( other.game_ )
{

}

// Private.
Core &Core::operator = ( const Core &rhs )
{
	game_ = rhs.game_;
	return *this;
}

Core::Core( GameLoop &game ) :
	running_( false ),
	game_( game )
{
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
}

Core::~Core()
{
	glfwTerminate();

	exit( EXIT_SUCCESS );
}

int Core::Run()
{
	running_ = true;

	while( running_ )
	{
		game_.Update();
	}

	return 0;
}

void Core::Exit()
{
	running_ = false;
}
