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

#include <sysutil/sysutil_bgmplayback.h>

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
static VideoPlayerInternal *g_Internals = NULL;
static uint8_t *PlayerMemoryBase;
static uint8_t *PlayerMemory;
static GLuint PBO = 0;
static uint8_t *PBOBuffer = NULL;
static Texture *MovieTexture = NULL;
static ResourceHolder *MovieTextureHolder = NULL;
static boost::shared_ptr< Texture2D > ExternalTexture = NULL;

inline uint32_t RoundTo( uint32_t size, uint32_t alignment )
{
	if( alignment == 0 )
		return size;

	return alignment * ( ( size + ( alignment - 1 ) ) / alignment );
}

class MemAllocator : public cell::Sail::memallocator
{
	void* Allocate(uint32_t size, uint32_t alignment=0) 
	{	
		void *base = PlayerMemory;
		size_t addr = reinterpret_cast< size_t >( base ) + alignment;

		void *aligned = reinterpret_cast< void * >( addr );
		if( alignment != 0 )
			aligned = reinterpret_cast< void * >( addr - ( addr % alignment ) );

		PlayerMemory = reinterpret_cast< uint8_t * >( aligned ) + size;
		return aligned;
	}

	void Deallocate(void* pMemory) 
	{
	}

	void* AllocateTexture(uint32_t size, uint32_t alignment=0) 
	{
		size_t sizeRequired = 3 * 1280 * 720 * sizeof( uint32_t );
		const size_t roundTo = 1024 * 1024;
		sizeRequired = roundTo * ( ( sizeRequired + ( roundTo - 1 ) ) / roundTo );
		memset( PBOBuffer, 0, sizeRequired );

		// Just need one preallocated PBO now.
		return PBOBuffer;	
	}

	void DeallocateTexture(void* pMemory) 
	{	
	}
};

void ReserveVideoPlayerMemory()
{
	// Create a texture for us to draw video into.
	MovieTexture = new Texture();
	MovieTextureHolder = new ResourceHolder( MovieTexture );

	glGenBuffers( 1, &PBO );
	glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, PBO );
	// Round the space to the nearest megabyte.
	size_t sizeRequired = 3 * 1280 * 720 * sizeof( uint32_t );
	const size_t roundTo = 1024 * 1024;
	sizeRequired = roundTo * ( ( sizeRequired + ( roundTo - 1 ) ) / roundTo );
	glBufferData( GL_TEXTURE_REFERENCE_BUFFER_SCE, sizeRequired, NULL, GL_SYSTEM_DRAW_SCE );
	
	PBOBuffer = reinterpret_cast< uint8_t * >( 
		glMapBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, GL_READ_WRITE )
	);

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

	ExternalTexture = boost::make_shared< Texture2D >( NULL, 1280, 720 );
	ExternalTexture->texture_ = MovieTextureHolder;

	// Allocate memory for the player. (Actually should require at most 39159200 bytes.)
	PlayerMemoryBase = reinterpret_cast< uint8_t * >( memalign( 8, 40000000 ) );
}

// Share the SPURS instance from the media player in mscommon.cpp.
extern CellSpurs spurs;

VideoPlayer::VideoPlayer()
	: internal_( new VideoPlayerInternal )
	, IsLooped( false )
{
	memset( internal_, 0, sizeof( VideoPlayerInternal ) );

	// A pointer to this is kept by the hlPlayer.  Probably a bad idea to have it leave the stack.
	static VideoPlayerInit videoPlayerInit;
	videoPlayerInit.pSharedSpurs = &spurs;//internal_->mpSpurs;
	videoPlayerInit.width = 0;
	videoPlayerInit.height = 0;
	videoPlayerInit.RGBAOutput = true;

	static MemAllocator ReplacementMem;
	CustomAllocators ReplacementAllocators;
	ReplacementAllocators.FileReplacement = NULL;
	ReplacementAllocators.MemoryReplacement = &ReplacementMem;

	// Reset player memory allocator.
	PlayerMemory = PlayerMemoryBase;

	internal_->Player = new cell::Sail::hlPlayer( &videoPlayerInit, &ReplacementAllocators );

	// Global player reference so it can be used from another thread.
	g_Player = internal_->Player;

	g_Internals = internal_;
	// Disable BGM playback.
	int ret = cellSysutilDisableBgmPlayback();
	if( ret < 0 )
		LOG.Write( "Failed to stop BGM playback: 0x%x\n", ret );
}

void KillVideoPlayer()
{
	if( g_Internals )
	{
		g_Internals->Player = NULL;
		g_Internals = NULL;
	}

	delete g_Player;
	g_Player = NULL;
}

VideoPlayer::~VideoPlayer()
{
	g_runDrawThread = false;

	KillVideoPlayer();
	
	// Enable BGM playback.
	int ret = cellSysutilEnableBgmPlayback();
	if( ret < 0 )
		LOG.Write( "Failed to start BGM playback: 0x%x\n", ret );

	delete internal_;
}

void VideoPlayer::SetVolume( float volume )
{
	//Volume = volume;
}

void VideoPlayer::Play( const boost::shared_ptr< Video > &video )
{
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
	}
}

extern void SetElapsedVideoTime( float time );

void VideoPlayer::DrawFrame()
{
	VideoFrameInfo displayFrame;

	if( g_Player && g_Player->vsyncGetFrame( &displayFrame ) )
	{
		glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, PBO );

		glBindTexture( GL_TEXTURE_2D, MovieTexture->impl_.internal_->Ref.textureID );
		glTextureReferenceSCE( GL_TEXTURE_2D, 1, 1280, 720, 1, GL_RGBA, 1280 * sizeof( uint32_t ),
			reinterpret_cast< GLintptr >( displayFrame.buffer - PBOBuffer ) );
		glBindTexture( GL_TEXTURE_2D, 0 );
	
		glBindBuffer( GL_TEXTURE_REFERENCE_BUFFER_SCE, 0 );
	}
}

boost::shared_ptr< Texture2D > VideoPlayer::GetTexture()
{
	return ExternalTexture;
}
