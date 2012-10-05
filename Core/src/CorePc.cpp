#include <CorePc.h>

#include <Architecture/Scheduler.h>
#include <Content/Wad.h>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>

#include <GL/glew.h>
#include <GL/glfw.h>

// Private.
CorePc::CorePc( const CorePc &other ) :
	game_( other.game_ ),
	qd_( other.qd_ ),
	content_( other.content_ )
{

}

// Private.
CorePc &CorePc::operator = ( const CorePc &rhs )
{
	return *this;
}

CorePc::CorePc( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 ),
	content_( 0 ),
	scheduler_( 0 )
{
	if( !glfwInit() )
		exit( EXIT_FAILURE );

	if( !glfwOpenWindow( 1280, 720, 0, 0, 0,
		0, 16, 0, GLFW_WINDOW ) )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	if( GLEW_OK != glewInit() )
	{
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	scheduler_ = new Scheduler;

	qd_ = new QuadDrawer;

	content_ = new Wad( "Content/" );
}

CorePc::~CorePc()
{
	delete qd_;

	delete content_;

	delete scheduler_;

	glfwTerminate();

	exit( EXIT_SUCCESS );
}

int CorePc::Run()
{
	running_ = true;

	while( running_ )
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		game_.Update();

		qd_->Flush();

		glfwSwapBuffers();

		if( glfwGetKey( GLFW_KEY_ESC ) || !glfwGetWindowParam( GLFW_OPENED ) )
			Exit();
	}

	return 0;
}

void CorePc::Exit()
{
	running_ = false;
}
