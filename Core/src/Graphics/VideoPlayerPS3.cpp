#include <Graphics/VideoPlayer.h>

#include <Core.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Graphics/Video.h>
#include <Graphics/Texture2D.h>
#include <Utility/Log.h>

#include <libhlPlayer.h>
#include <PSGL/psgl.h>
#include <PSGL/psglu.h>
#include <SailAllocator.h>

#include "../Content/PS3/psglGtfLoader.h"
#include <Content/TexturePS3Internal.h>

struct VideoPlayerInternal
{
	cell::Sail::hlPlayer *Player;
	CellSpurs *mpSpurs;
	sys_ppu_thread_t displayThread;
};

static const int NUM_SPU = 4;
static const int SPURS_SPU_PRIORITY = 100;
static const int SPURS_PPU_PRIORITY = 100;

extern std::string PS3_PATH_PREFIX;

bool g_runDrawThread;

static cell::Sail::hlPlayer *g_Player = NULL;
static GLuint PBO = 0;
static uint8_t *PBOBuffer = NULL;
static Texture *MovieTexture = NULL;
static ResourceHolder *MovieTextureHolder = NULL;
static boost::shared_ptr< Texture2D > ExternalTexture = NULL;

/*static void DrawThread( uint64_t arg )
{
	( void )arg;

	VideoFrameInfo displayFrame;

	g_runDrawThread = true;
	while( g_runDrawThread  )
	{
		if( g_Player && g_Player->vsyncGetFrame( &displayFrame ) )
		{
			if( !PBOBuffer )
				continue;

			// Queue up new frame.
			memcpy( PBOBuffer, displayFrame.buffer, 1280 * 720 * sizeof( uint32_t ) );
		}

		// Draw stuff.
	}

	sys_ppu_thread_exit( 0 );
}*/

// Share the SPURS instance from the media player in mscommon.cpp.
extern CellSpurs spurs;

VideoPlayer::VideoPlayer()
	: internal_( new VideoPlayerInternal )
	, IsLooped( false )
{
	memset( internal_, 0, sizeof( VideoPlayerInternal ) );

	/*std::string moviePath = PS3_PATH_PREFIX + "ContentPS3/" +
		"Movies/LogoSalad.mp4";*/

	//internal_->mpSpurs = reinterpret_cast< CellSpurs * >( memalign( CELL_SPURS_ALIGN, sizeof( CellSpurs ) ) );

	/*CellSpursAttribute attr;
	int ret = cellSpursAttributeInitialize( &attr, NUM_SPU, SPURS_SPU_PRIORITY, SPURS_PPU_PRIORITY, false );
	assert( ret == CELL_OK );
	ret = cellSpursAttributeEnableSpuPrintfIfAvailable( &attr );
	assert( ret == CELL_OK );
	ret = cellSpursAttributeSetNamePrefix( &attr, "hlpSpurs", strlen( "hlpSpurs" ) );
	assert( ret == CELL_OK );
	ret = cellSpursInitializeWithAttribute( internal_->mpSpurs, &attr );
	assert( ret == CELL_OK );*/

	VideoPlayerInit videoPlayerInit;
	videoPlayerInit.pSharedSpurs = &spurs;//internal_->mpSpurs;
	videoPlayerInit.width = 0;
	videoPlayerInit.height = 0;
	videoPlayerInit.RGBAOutput = true;

	internal_->Player = new cell::Sail::hlPlayer( &videoPlayerInit, NULL );

	// Create a texture for us to draw video into.
	MovieTexture = new Texture();
	MovieTextureHolder = new ResourceHolder( MovieTexture );

	// Create underlying buffer.
	glGenBuffers( 1, &PBO );
	glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, PBO );
	glBufferData( GL_TEXTURE_REFERENCE_BUFFER_SCE, 1280 * 720 * sizeof( uint32_t ), NULL, GL_SYSTEM_DRAW_SCE );
	/*PBOBuffer = reinterpret_cast< uint8_t * >( 
		glMapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, GL_READ_WRITE )
	);*/

	// Create actual texture.
	GLuint texture;
	glGenTextures( 1, &texture );
	MovieTexture->impl_.internal_->Ref.textureID = texture;

	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTextureReferenceSCE( GL_TEXTURE_2D, 1, 1280, 720, 1, GL_RGBA, 1280 * sizeof( uint32_t ), 0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	
	glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, 0 );

	// Start thread that pulls frames from the video player and sticks them into our texture buffer.
	int32_t dispThrPriority = 1500;
	size_t appStackSize = 32768;

	ExternalTexture = boost::make_shared< Texture2D >( NULL, 1280, 720 );
	ExternalTexture->texture_ = MovieTextureHolder;

	/*if( CELL_OK != sys_ppu_thread_create( &internal_->displayThread, DrawThread, NULL,
										dispThrPriority, appStackSize, SYS_PPU_THREAD_CREATE_JOINABLE,
										"Video draw vsync thread" ) )
		LOG.Write( "VideoPlayer(): failed to create draw thread\n" );
	else
		LOG.Write( "VideoPlayer(): created draw thread, id = %d\n", static_cast< int >( internal_->displayThread ) );
	*/
	/*char buffer[ 512 ];
	snprintf( buffer, sizeof( buffer ), "%s", moviePath.c_str() );*/

	// Global player reference so it can be used from another thread.
	g_Player = internal_->Player;


	/*bool check = internal_->Player->Play( buffer, false );
	if( !check )
	{
		LOG.Write( "Couldn't play file: %s\n", buffer );
		delete internal_->Player;
		internal_->Player = NULL;
		g_Player = NULL;

		delete MovieTextureHolder;
		MovieTextureHolder = NULL;

		glDeleteTextures( 1, &MovieTexture->impl_.internal_->Ref.textureID );
		delete MovieTexture;
		MovieTexture = NULL;

		ExternalTexture = NULL;
	}*/

	/*int playerMemory = 0;
	int textureMemory = 0;
	internal_->Player->Memstats( &playerMemory, &textureMemory );*/
}

VideoPlayer::~VideoPlayer()
{
	g_runDrawThread = false;

	/*if( g_Player )
	{
		uint64_t stat;
		int rc = sys_ppu_thread_join( internal_->displayThread, &stat );
		if( rc != CELL_OK )
			LOG.Write( "Failed to join thread with error 0x%x\n", rc );
	}*/

	g_Player = NULL;
	delete internal_->Player;

	delete MovieTextureHolder;
	MovieTextureHolder = NULL;

	if( MovieTexture )
	{
		glDeleteTextures( 1, &MovieTexture->impl_.internal_->Ref.textureID );
		delete MovieTexture;
		MovieTexture = NULL;
	}

	ExternalTexture = NULL;

	// Empty pbo used by the video player.
	//memset( PBOBuffer, 0, 1280 * 720 * sizeof( uint32_t ) );

	/*glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, PBO );
	glUnmapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE );
	glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, 0 );*/
	glDeleteBuffers( 1, &PBO );
	PBO = 0;

	/*int ret = cellSpursFinalize( internal_->mpSpurs );
	if( ret != CELL_OK )
		LOG.Write( "cellSpursFinalize() failed 0x%x\n", ret );*/

	//free( internal_->mpSpurs );

	delete internal_;
}

void VideoPlayer::SetVolume( float volume )
{
	//Volume = volume;
}

void VideoPlayer::Play( const boost::shared_ptr< Video > &video )
{
	/*std::string moviePath = PS3_PATH_PREFIX + "ContentPS3/" +
		"Movies/LogoSalad.mp4";*/
	std::string moviePath = PS3_PATH_PREFIX + video->Path;

	char buffer[ 512 ];
	snprintf( buffer, sizeof( buffer ), "%s", moviePath.c_str() );

	bool check = internal_->Player->Play( buffer, false );
	if( !check )
	{
		LOG.Write( "Couldn't play file: %s\n", buffer );
		delete internal_->Player;
		internal_->Player = NULL;
		g_Player = NULL;

		delete MovieTextureHolder;
		MovieTextureHolder = NULL;

		glDeleteTextures( 1, &MovieTexture->impl_.internal_->Ref.textureID );
		delete MovieTexture;
		MovieTexture = NULL;

		ExternalTexture = NULL;
	}
}

void VideoPlayer::DrawFrame()
{
	VideoFrameInfo displayFrame;

	if( g_Player && g_Player->vsyncGetFrame( &displayFrame ) )
	{
		glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, PBO );
		/*PBOBuffer = reinterpret_cast< uint8_t * >( 
			glMapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, GL_READ_WRITE )
		);
		if( PBOBuffer )
		{
			// Queue up new frame.
			memcpy( PBOBuffer, displayFrame.buffer, 1280 * 720 * sizeof( uint32_t ) );
		}
		glUnmapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE );*/
		glBufferSubData( GL_TEXTURE_REFERENCE_BUFFER_SCE, 0, displayFrame.width * displayFrame.height * sizeof( uint32_t ),
			displayFrame.buffer );
		glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, 0 );

		glFlush();
		glFinish();
	}
}

boost::shared_ptr< Texture2D > VideoPlayer::GetTexture()
{
	return ExternalTexture;
}
