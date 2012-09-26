#include <Core.h>

#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>

#ifndef CAFE
	#include <GL/glew.h>
	#include <GL/glfw.h>
#endif

#ifdef CAFE
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

#ifdef CAFE

#define MAKE_CASE( def ) \
	case def: return #def;

static const char *GX2TVScanModeToString( GX2TVScanMode mode )
{
	switch( mode )
	{
	MAKE_CASE( GX2_TV_SCAN_MODE_NONE ) 
	MAKE_CASE( GX2_TV_SCAN_MODE_576I )
	MAKE_CASE( GX2_TV_SCAN_MODE_480I )
	MAKE_CASE( GX2_TV_SCAN_MODE_480P )
	MAKE_CASE( GX2_TV_SCAN_MODE_720P )
	MAKE_CASE( GX2_TV_SCAN_MODE_RESERVED )
	MAKE_CASE( GX2_TV_SCAN_MODE_1080I )
	MAKE_CASE( GX2_TV_SCAN_MODE_1080P )
	}

	return "GX2_TV_SCAN_MODE_OH_SHIT";
}

static const char *GX2AspectRatioToString( GX2AspectRatio aspect )
{
	switch( aspect )
	{
	MAKE_CASE( GX2_ASPECT_RATIO_4_BY_3 )
	MAKE_CASE( GX2_ASPECT_RATIO_16_BY_9 )
	}

	return "GX2_ASPECT_RATIO_OH_SHIT";
}

#endif

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
#ifdef _DEBUG
	GX2DebugCaptureInit( NULL );

	GX2TVScanMode scanMode = GX2GetSystemTVScanMode();
	GX2AspectRatio aspect = GX2GetSystemTVAspectRatio();
	
	OSReport( "scanMode = %s\naspect = %s\n",
		GX2TVScanModeToString( scanMode ),
		GX2AspectRatioToString( aspect ) );
#endif
#endif

	qd_ = new QuadDrawer;
}

Core::~Core()
{
	delete qd_;

#ifdef CAFE

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
#endif

#ifndef CAFE
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
#endif

		game_.Update();

#ifndef CAFE
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
