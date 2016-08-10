#include <Graphics/VideoPlayer.h>

#include <Core.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Graphics/Video.h>
#include <Graphics/Texture2D.h>
#include <Utility/Log.h>

#include <Content/TextureVitaInternal.h>

#include <stdio.h>

extern bool StartTimeSet;
extern clock_t StartTime;

struct VideoPlayerInternal
{
};

extern std::string PS3_PATH_PREFIX;

bool g_runDrawThread;

static VideoPlayerInternal *g_Internals = NULL;
static uint8_t *PlayerMemoryBase;
static uint8_t *PlayerMemory;
static uint8_t *PBOBuffer = NULL;
static Texture *MovieTexture = NULL;
static ResourceHolder *MovieTextureHolder = NULL;
static boost::shared_ptr< Texture2D > ExternalTexture = NULL;

VideoPlayer::VideoPlayer()
	: internal_( new VideoPlayerInternal )
	, IsLooped( false )
{
	StartTimeSet = false;

	memset( internal_, 0, sizeof( VideoPlayerInternal ) );

	// ...
}

void KillVideoPlayer()
{
	if( g_Internals )
	{
		//g_Internals->Player = NULL;
		g_Internals = NULL;
	}

	//delete g_Player;
	//g_Player = NULL;
}

VideoPlayer::~VideoPlayer()
{
	g_runDrawThread = false;

	KillVideoPlayer();
	
	// Enable BGM playback.
	//int ret = cellSysutilEnableBgmPlayback();
	//if( ret < 0 )
	//	LOG_WRITE( "Failed to start BGM playback: 0x%x\n", ret );

	delete internal_;
}

void VideoPlayer::SetVolume( float volume )
{
	//Volume = volume;
}

void VideoPlayer::Play( const boost::shared_ptr< Video > &video )
{
}

extern void SetElapsedVideoTime( float time );

void VideoPlayer::DrawFrame()
{
}

boost::shared_ptr< Texture2D > VideoPlayer::GetTexture()
{
	return ExternalTexture;
}
