#include <Core.h>

#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>

#ifndef CAFE
	#include <GL/glew.h>
	#include <GL/glfw.h>
#endif

#ifdef CAFE
	#include <cafe/demo.h>
	#include <cafe/gx2.h>
	#include <cafe/os.h>
#endif

// Single instance of the core.
template<> Core *Singleton< Core >::singleton_ = 0;

// Private.
Core::Core( const Core &other ) :
	game_( other.game_ ),
	qd_( other.qd_ )
{

}

// Private.
Core &Core::operator = ( const Core &rhs )
{
	return *this;
}

Core::Core( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 )
{
#ifndef CAFE
	if( !glfwInit() )
		exit( EXIT_FAILURE );

	if( !glfwOpenWindow( 1024, 576, 0, 0, 0,
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
#endif

#ifdef CAFE
	DEMOInit();
	DEMOTestInit( 0, 0 );
	DEMOGfxInit( 0, 0 );
#endif

	qd_ = new QuadDrawer;
}

Core::~Core()
{
	delete qd_;

#ifdef CAFE
	DEMOTestShutdown();
	DEMOGfxShutdown();
	DEMOShutdown();
#endif

#ifndef CAFE
	glfwTerminate();

	exit( EXIT_SUCCESS );
#endif
}

int Core::Run()
{
	running_ = true;

	while( running_ )
	{
#ifdef CAFE
		DEMOGfxBeforeRender();
		GX2ClearColor( &DEMOColorBuffer, 0, 0, 0, 1 );
		GX2ClearDepthStencil( &DEMODepthBuffer, GX2_CLEAR_BOTH );

		DEMOGfxSetContextState();
#endif

#ifndef CAFE
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
#endif

		game_.Update();

#ifdef CAFE
		DEMOGfxDoneRender();
#endif

#ifndef CAFE
	glfwSwapBuffers();

	if( glfwGetKey( GLFW_KEY_ESC ) || !glfwGetWindowParam( GLFW_OPENED ) )
			CORE.Exit();
#endif
	}

	return 0;
}

void Core::Exit()
{
	running_ = false;
}

Core &Core::GetSingleton()
{
	assert( singleton_ );
	return *singleton_;
}
