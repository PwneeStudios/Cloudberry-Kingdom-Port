#include <CoreVita.h>

#include <Architecture/Scheduler.h>
#include <Audio/MediaPlayer.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdarg>
#include <cstdlib>
#include <GameLoop.h>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Input/GamePad.h>
#include <Input/Keyboard.h>
#include <list>
#include <Utility/Error.h>
#include <Utility/Limits.h>
#include <Utility/Log.h>

#include <np.h>

#include <Utility/ConsoleInformation.h>

// Passphrase and signature from PSN Server Management Tools.
static const SceNpCommunicationId s_npCommunicationId = {
    {'N', 'P', 'W', 'R', '0', '4', '4', '1', '3'},
    '\0',
    0,
    0
};

/***
SceNpCommunicationPassphrase

416ea7dc6715f7fb874be27c584df3efc5757062bc2b3992c74b7d42ee450914995edf73efa5e5e7f6bc4b1687be6a0cf40fab915d7657bd0afe59b8decf07cc7ec6b7d6be22489a874eb7efda3b65d46577a7ce2a423176f8ad38a0ead670ded8c70edb8d4543c0b30e295a769efad5b76e4d00e40e2d93dbca69688ea1f097
***/

static const SceNpCommunicationPassphrase s_npCommunicationPassphrase = {
    {
        0x41,0x6e,0xa7,0xdc,0x67,0x15,0xf7,0xfb,
        0x87,0x4b,0xe2,0x7c,0x58,0x4d,0xf3,0xef,
        0xc5,0x75,0x70,0x62,0xbc,0x2b,0x39,0x92,
        0xc7,0x4b,0x7d,0x42,0xee,0x45,0x09,0x14,
        0x99,0x5e,0xdf,0x73,0xef,0xa5,0xe5,0xe7,
        0xf6,0xbc,0x4b,0x16,0x87,0xbe,0x6a,0x0c,
        0xf4,0x0f,0xab,0x91,0x5d,0x76,0x57,0xbd,
        0x0a,0xfe,0x59,0xb8,0xde,0xcf,0x07,0xcc,
        0x7e,0xc6,0xb7,0xd6,0xbe,0x22,0x48,0x9a,
        0x87,0x4e,0xb7,0xef,0xda,0x3b,0x65,0xd4,
        0x65,0x77,0xa7,0xce,0x2a,0x42,0x31,0x76,
        0xf8,0xad,0x38,0xa0,0xea,0xd6,0x70,0xde,
        0xd8,0xc7,0x0e,0xdb,0x8d,0x45,0x43,0xc0,
        0xb3,0x0e,0x29,0x5a,0x76,0x9e,0xfa,0xd5,
        0xb7,0x6e,0x4d,0x00,0xe4,0x0e,0x2d,0x93,
        0xdb,0xca,0x69,0x68,0x8e,0xa1,0xf0,0x97
    }
};

/***
SceNpCommunicationSignature

b9dde13b0100000000000000a2f2d66966b3f8d64f9c7dc9fa81e8fdd335cfa7b4b0b1dca063cf38f7dc3a46bad2dbf90dbd293f146165764419818cf74d9612680ec39bd3dbc02c3f87dc36a5721baea8ead5085ba7c89e77d29577ad157cd610c1f5b380783070b51dbeb37eec58387f707d89879fac90358847dbe9a912929ad92a92c01f8bfc1d788e5aeea145a44892f8cb5d198d2bbf54ec783952deee
***/

static const SceNpCommunicationSignature s_npCommunicationSignature = {
    {
        0xb9,0xdd,0xe1,0x3b,0x01,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0xa2,0xf2,0xd6,0x69,
        0x66,0xb3,0xf8,0xd6,0x4f,0x9c,0x7d,0xc9,
        0xfa,0x81,0xe8,0xfd,0xd3,0x35,0xcf,0xa7,
        0xb4,0xb0,0xb1,0xdc,0xa0,0x63,0xcf,0x38,
        0xf7,0xdc,0x3a,0x46,0xba,0xd2,0xdb,0xf9,
        0x0d,0xbd,0x29,0x3f,0x14,0x61,0x65,0x76,
        0x44,0x19,0x81,0x8c,0xf7,0x4d,0x96,0x12,
        0x68,0x0e,0xc3,0x9b,0xd3,0xdb,0xc0,0x2c,
        0x3f,0x87,0xdc,0x36,0xa5,0x72,0x1b,0xae,
        0xa8,0xea,0xd5,0x08,0x5b,0xa7,0xc8,0x9e,
        0x77,0xd2,0x95,0x77,0xad,0x15,0x7c,0xd6,
        0x10,0xc1,0xf5,0xb3,0x80,0x78,0x30,0x70,
        0xb5,0x1d,0xbe,0xb3,0x7e,0xec,0x58,0x38,
        0x7f,0x70,0x7d,0x89,0x87,0x9f,0xac,0x90,
        0x35,0x88,0x47,0xdb,0xe9,0xa9,0x12,0x92,
        0x9a,0xd9,0x2a,0x92,0xc0,0x1f,0x8b,0xfc,
        0x1d,0x78,0x8e,0x5a,0xee,0xa1,0x45,0xa4,
        0x48,0x92,0xf8,0xcb,0x5d,0x19,0x8d,0x2b,
        0xbf,0x54,0xec,0x78,0x39,0x52,0xde,0xee
    }
};

// Drm key for checking file access.
//static const SceNpDrmKey s_npDrmKey = {
//	{ 0xb1, 0x28, 0xb8, 0x67, 0x56, 0xd4, 0x68, 0x2b, 0x16, 0x18, 0x33, 0x8b, 0x49, 0x66, 0x44, 0xd9 }
//};

// Private.
CoreVita::CoreVita( const CoreVita &other ) :
	game_( other.game_ ),
	qd_( other.qd_ ),
	content_( other.content_ )
{

}

// Private.
CoreVita &CoreVita::operator = ( const CoreVita &rhs )
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
		LOG_WRITE( msg );							   \
		LOG_WRITE( "!! EXITING PROGRAM !!\n" );		   \
		exit( 1 );									   \
	}												   \
}

// Override music volume when BGM is playing. Defined in MediaPlayerVita.cpp.
extern void SetBGMOverride( bool override );

// Is the system menu open? Defined in ConsoleInformationVita.cpp.
extern bool GLOBAL_SYSTEM_MENU_OPEN;

// Pause and resume the background job system.  Defined in SchedulerVita.cpp.
extern void PauseScheduler();
extern void ResumeScheduler();

// Kick off saves on exit to make sure we save everything. Defined in EzStorage.cpp.
extern void SaveAllOnExit();

static void SystemCallback( const uint64_t status, const uint64_t param, void *userdata )
{
}

// FIXME: EXTERNALS FOR SHARING INFORMATION GLOBALLY!

std::string VITA_PATH_PREFIX;

int GLOBAL_WIDTH;
int GLOBAL_HEIGHT;

// Preallocate all memory used by video player.  Defined in VideoPlayerVita.cpp.
extern void ReserveVideoPlayerMemory();

extern void KillVideoPlayer();

// Wait for save and load operations to finish.  Defined in EzStorage.cpp.
extern void WaitForSaveLoad();

CoreVita::CoreVita( GameLoop &game ) :
	running_( false ),
	game_( game ),
	qd_( 0 ),
	content_( 0 ),
	scheduler_( 0 )
{
}

CoreVita::~CoreVita()
{
	GamePad::Shutdown();

	delete td_;

	delete qd_;

	delete content_;

	delete scheduler_;

	// Need to shut down media player last as scheduler could still play a song.
	MediaPlayer::Shutdown();
}

static SceNpTrophyContext TrophyContext;
static SceNpTrophyHandle TrophyHandle;
static bool ContextRegistered;
extern std::list< ErrorType > GLOBAL_ERROR_QUEUE;

bool GetTrophyContext( SceNpTrophyContext &context, SceNpTrophyHandle &handle )
{
	if( !ContextRegistered )
		return false;

	context = TrophyContext;
	handle = TrophyHandle;

	return true;
}

void ForceGetTrophyContext( SceNpTrophyContext &context, SceNpTrophyHandle &handle )
{
	context = TrophyContext;
	handle = TrophyHandle;
}

//int TrophyStatusCallback( SceNpTrophyContext context, SceNpTrophyStatus status, int completed, int total, void *arg )
//{
//	int ret = 0;
//
//	switch( status )
//	{
//	case SCE_NP_TROPHY_STATUS_NOT_INSTALLED:
//		LOG_WRITE( "Trophy configuration not installed.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_DATA_CORRUPT:
//		LOG_WRITE( "Trophy data is corrupt.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_INSTALLED:
//		LOG_WRITE( "Trophy configuration has been installed.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_REQUIRES_UPDATE:
//		LOG_WRITE( "Trophy configuration requires update.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_CHANGES_DETECTED:
//		LOG_WRITE( "Trophy changes detected.\n" );
//		break;
//	case SCE_NP_TROPHY_STATUS_UNKNOWN:
//		LOG_WRITE( "Trophy status unknown.\n" );
//		break;
//	default:
//		LOG_WRITE( "Trophy status: %d\n", status );
//		break;
//	}
//
//	return ret;
//}

// Stuff to localize the register trophy message.
static std::string WstringToUtf8( const std::wstring& str )
{
	char utf8[ 512 ];
	size_t inSize = str.size();
	size_t outSize = sizeof( utf8 );
	// FIXME: This was only compiling for PS3
	//if( l10n_convert_str( l10n_get_converter( L10N_UTF16, L10N_UTF8 ), str.c_str(), &inSize, utf8, &outSize ) != ConversionOK )
	//	return "";

	return std::string( utf8, utf8 + outSize );
}

static std::wstring Format( const wchar_t *format, ... )
{
	wchar_t buffer[512];

	va_list args;
	va_start( args, format );
	vswprintf( buffer, sizeof( buffer ) / sizeof( wchar_t ), format, args );
	va_end( args );

	return std::wstring( buffer );
}

bool gTrophyContextRegistered = true;

// Space needed for trophy, 
//extern uint64_t RequiredTrophySpace;

void RegisterTrophyContextThread( uint64_t context )
{
	ContextRegistered = false;

	// Register trophy.
	// ...

	gTrophyContextRegistered = true;
	LOG_WRITE( "Trophy configuration done.\n" );

	//sys_ppu_thread_exit( 0 );
}

static SceNpId NPId;
static int ScoreTitleContext = 0;
static bool NPIdObtained = false;

bool GetNPScoreContext( int &id )
{
	if( !NPIdObtained )
		return false;

	id = ScoreTitleContext;

	return true;
}

bool IsNPAvailable()
{
	return NPIdObtained;
}

void ConnectToNPThread( uint64_t context )
{
	LOG_WRITE( "stub: fix me! ConnectToNPThread" );

	//int ret = sceNpManagerGetNpId( &NPId );
	//switch( ret )
	//{
	//case SCE_NP_ERROR_NOT_INITIALIZED:
	//case SCE_NP_ERROR_INVALID_ARGUMENT:
	//case SCE_NP_ERROR_INVALID_STATE:
	//case SCE_NP_ERROR_OFFLINE:
	//	sys_ppu_thread_exit( 0 );
	//	return;
	//	break;

	//case 0:
	//	break;
	//}

	//ret = sceNpScoreCreateTitleCtx( &s_npCommunicationId, &s_npCommunicationPassphrase, &NPId );
	//if( ret > 0 )
	//{
	//	ScoreTitleContext = ret;
	//	NPIdObtained = true;
	//}
	//else
	//	LOG_WRITE( "Coldn't get score title context: 0x%x\n", ret );

	//sys_ppu_thread_exit( 0 );
}

void ConnectToNP()
{
	LOG_WRITE( "stub: fix me! ConnectToNP" );

	if( NPIdObtained )
	{
		LOG_WRITE( "Tried to connect to NP multiple times!\n" );
		return;
	}

	LOG_WRITE( "Connecting to NP!\n" );

	// Kick off NP connection.
	//sys_ppu_thread_t tid;
	//int ret = sys_ppu_thread_create( &tid, ConnectToNPThread, 0,
	//	1001, 16 * 1024, 0, "ConnectToNP" );
	//if( ret != 0 )
	//	LOG_WRITE( "Failed to start ConnectToNP: 0x%x\n", ret );
}

ErrorType GLOBAL_NP_DISCONNECT_MESSAGE;

void DisconnectFromNP()
{
	LOG_WRITE( "stub: fix me! DisconnectFromNP" );

	//DisplayError( GLOBAL_NP_DISCONNECT_MESSAGE );
	//LOG_WRITE( "Disconnecting from NP\n" );

	//if( NPIdObtained )
	//{
	//	sceNpScoreDestroyTitleCtx( ScoreTitleContext );
	//}

	NPIdObtained = false;
}

void NPManagerCallback( int event, int result, void *arg )
{
	LOG_WRITE( "stub: fix me! NPManagerCallback" );

	LOG_WRITE( "NP EVENT: %d\tRESULT: %d\n", event, result );
	//switch( event )
	//{
	//case SCE_NP_MANAGER_STATUS_OFFLINE:
	//	DisconnectFromNP();
	//	break;
	//case SCE_NP_MANAGER_STATUS_GETTING_TICKET:
	//	break;
	//case SCE_NP_MANAGER_STATUS_GETTING_PROFILE:
	//	break;
	//case SCE_NP_MANAGER_STATUS_LOGGING_IN:
	//	break;
	//case SCE_NP_MANAGER_STATUS_ONLINE:
	//	{
	//		int id;
	//		if( !GetNPScoreContext( id ) )
	//			ConnectToNP();
	//	}
	//	break;
	//}
}

static bool ErrorDialogOpen = false;
static ErrorType CurrentError( 0 );

void ErrorDialogCallback( int buttonType, void *userData )
{
	LOG_WRITE( "stub: fix me! ErrorDialogCallback" );

	//ErrorType::CompleteCallback complete = CurrentError.GetComplete();

	//switch( buttonType )
	//{
	//case CELL_MSGDIALOG_BUTTON_YES:
	//	if( complete )
	//		complete( true );
	//	break;
	//case CELL_MSGDIALOG_BUTTON_NO:
	//	if( complete )
	//		complete( false );
	//	break;

	//default:
	//	if( complete )
	//		complete( false );
	//	break;
	//}

	ErrorDialogOpen = false;
}

#define NP_POOL_SIZE (128 * 1024)
static uint8_t NPPool[ NP_POOL_SIZE ];

void DebugFrame(float r, float g, float b)
{
	LOG_WRITE( "stub: fix me! DebugFrame" );

	static int count = 0;
	
	/*glEnable(GL_SCISSOR_TEST);
	glViewport(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);

	for( int i = 0; i < 2; ++i )
	{
		glScissor(0, 0, GLOBAL_WIDTH, GLOBAL_HEIGHT);
		glClearColor( r, g, b, 1 );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		int j = 0;
		for( int i = 31; i >= 0; --i)
		{
			glScissor(j, 0, 32, 128);

			if( count & (1 << i) )
				glClearColor( 1, 1, 1, 1 );
			else
				glClearColor( 0, 0, 0, 1 );

			glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

			j += 33;
		}

		psglSwap();
	}*/
	
	++count;
	//glDisable(GL_SCISSOR_TEST);
}

void NPDRMInvalidCompleteCallback( bool yes )
{
	LOG_WRITE( "stub: fix me! NPDRMInvalidCompleteCallback" );

	//glFinish();
	CORE.Exit();
}

void CheckNPDRMFileThread( uint64_t context )
{
	LOG_WRITE( "stub: fix me! CheckNPDRMFileThread" );

	//std::string file_path = VITA_PATH_PREFIX + "UNLOCK.EDAT";
	//int ret = sceNpDrmIsAvailable2( &s_npDrmKey, file_path.c_str() );
	//
	//if( ret == 0 )
	//{
	//	// Good to go.
	//}

	//sys_ppu_thread_exit( 0 );
}

int CoreVita::Run()
{
	return 0;
}

void CoreVita::Exit()
{
	running_ = false;
}
