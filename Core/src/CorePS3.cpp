#include <CorePS3.h>

#include <Architecture/Scheduler.h>
#include <Audio/MediaPlayer.h>
#include <Audio/PS3/mscommon.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdlib>
#include <Utility/Limits.h>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Input/GamePad.h>
#include <Input/Keyboard.h>
#include <Utility/Log.h>

#include <cell/sysmodule.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>
#include <sys/process.h>
#include <sys/spu_initialize.h>
#include <sysutil/sysutil_gamecontent.h>

SYS_PROCESS_PARAM ( 1001, 0x80000 )

// Private.
CorePS3::CorePS3( const CorePS3 &other ) :
	game_( other.game_ ),
	qd_( other.qd_ ),
	content_( other.content_ )
{

}

// Private.
CorePS3 &CorePS3::operator = ( const CorePS3 &rhs )
{
	return *this;
}

// Abstract error checking.
#define CELL_ERR_CHECK( code, msg )					   \
{													   \
	int ret = ( code );								   \
	switch( ret )									   \
	{												   \
	case CELL_OK:									   \
		break;										   \
													   \
	case CELL_SYSMODULE_ERROR_DUPLICATED:			   \
		break;										   \
													   \
	case CELL_SYSMODULE_ERROR_UNKNOWN:				   \
	case CELL_SYSMODULE_ERROR_FATAL:				   \
		LOG.Write( msg );							   \
		LOG.Write( "!! EXITING PROGRAM !!\n" );		   \
		exit( 1 );									   \
	}												   \
}

static void SystemCallback( uint64_t status, uint64_t param, void *userdata )
{
	( void )param;
	( void )userdata;

	switch( status )
	{
	case CELL_SYSUTIL_REQUEST_EXITGAME:
		glFinish();
		CORE.Exit();
		break;
	case CELL_SYSUTIL_DRAWING_BEGIN:
	case CELL_SYSUTIL_DRAWING_END:
		break;
	default:
		LOG.Write( "Unknown callback status: 0x%llx\n", status );
	}
}

std::string PS3_PATH_PREFIX;

CorePS3::CorePS3( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 ),
	content_( 0 ),
	scheduler_( 0 )
{
	sys_spu_initialize( 6, 1 );

	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_GCM_SYS ), "Failed to load GCM_SYS\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_FS ), "Failed to load FS\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_USBD ), "Failed to load USBD\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_IO ), "Failed to load IO\n" );
	CELL_ERR_CHECK( cellSysmoduleLoadModule( CELL_SYSMODULE_SYSUTIL_GAME ), "Failed to load IO\n" );

	LoadModules();

	unsigned int type;
	unsigned int attributes;
	CellGameContentSize size;
	char dirName[ CELL_GAME_PATH_MAX ];
	cellGameBootCheck( &type, &attributes, &size, dirName );

	char contentInfoPath[ CELL_GAME_PATH_MAX ];
	char usrdirPath[ CELL_GAME_PATH_MAX ];

	cellGameContentPermit( contentInfoPath, usrdirPath );
	PS3_PATH_PREFIX = std::string( usrdirPath ) + "/";
	// To test an hdd game in release mode with the debugger we need to tell it about the
	// game code.  Also the files should be pre-installed on the disk.
	//PS3_PATH_PREFIX = "/dev_hdd0/game/TEST00000/USRDIR/";
	LOG.Write( "Running in %s\nContent dir %s\n", dirName, usrdirPath );
#ifdef DEBUG
	PS3_PATH_PREFIX = "/app_home/";
#endif

	int ret = cellSysutilRegisterCallback( 0, SystemCallback, NULL );
	if( ret != CELL_OK )
	{
		LOG.Write( "Failed to register system callback: error=0x%x\n", ret );
		exit( 1 );
	}

	PSGLinitOptions initOpts = {
		enable: PSGL_INIT_MAX_SPUS | PSGL_INIT_INITIALIZE_SPUS | PSGL_INIT_HOST_MEMORY_SIZE,
		maxSPUs: 1,
		initializeSPUs: false,
		persistentMemorySize: 0,
		transientMemorySize: 0,
		errorConsole: 0,
		fifoSize: 0,
		hostMemorySize: 128 * 1024 * 1024
	};

	psglInit( &initOpts );

	static PSGLdevice *device = NULL;
	device = psglCreateDeviceAuto( GL_ARGB_SCE, GL_NONE,
		GL_MULTISAMPLING_NONE_SCE/*GL_MULTISAMPLING_4X_SQUARE_ROTATED_SCE*/ );


	if( !device )
	{
		LOG.Write( "Failed to create device\n" );
		exit( 1 );
	}

	GLuint width, height;
	psglGetDeviceDimensions( device, &width, &height );

	LOG.Write( "Initializing device, resolution %d x %d\n", width, height );

	GLfloat aspect = psglGetDeviceAspectRatio( device );
	LOG.Write( "Aspect ratio %f\n", aspect );

	PSGLcontext *context = psglCreateContext();
	if( !context )
	{
		LOG.Write( "Failed to create context\n" );
		exit( -1 );
	}

	psglMakeCurrent( context, device );
	
	psglResetCurrentContext();

	// FIXME: Remove debugging!
	cgGLSetDebugMode( GL_TRUE );

	glViewport( 0, 0, width, height );
	glScissor( 0, 0, width, height );
	
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	/*glClearDepthf( 1.f );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );*/

	glDisable( GL_CULL_FACE );
	glEnable( GL_VSYNC_SCE );

	glEnable( GL_BLEND );
	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
	
	cgGLEnableProfile( cgGLGetLatestProfile( CG_GL_VERTEX ) );
	cgGLEnableProfile( cgGLGetLatestProfile( CG_GL_FRAGMENT ) );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	psglSwap();

	scheduler_ = new Scheduler;

	content_ = new Wad( PS3_PATH_PREFIX + "ContentPS3/" );

	qd_ = new QuadDrawer;

	td_ = new TextDrawer;

	GamePad::Initialize();
	MediaPlayer::Initialize();
}

CorePS3::~CorePS3()
{
	MediaPlayer::Shutdown();
	GamePad::Shutdown();

	delete td_;

	delete qd_;

	delete content_;

	delete scheduler_;

	UnloadModules();
}

int CorePS3::Run()
{
	running_ = true;

	game_.Initialize();

	while( running_ )
	{
		GamePad::Update();
		Keyboard::Update();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		scheduler_->MainThread();

		game_.Update();

		qd_->Flush();

		psglSwap();
	}

	return 0;
}

void CorePS3::Exit()
{
	running_ = false;
}
