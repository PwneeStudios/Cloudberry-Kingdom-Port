#include <Audio/MediaPlayer.h>

#include <cafe/os.h>
#include <cafe/demo.h>
#include <cafe/aacdec.h>
#include <cafe/mem.h>

#include <Audio/Song.h>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "AudioInternalWiiU.h"
#include "SongInternalWiiU.h"

//#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>
#include <fmodwiiu.h>

/*FMOD::System *FMODSystem;
FMOD::Channel *CurrentChannel;*/
FMOD_SYSTEM *	FMODSystem		= NULL;
FMOD_CHANNEL *	CurrentChannel	= NULL;

float Volume;
extern FSClient *GLOBAL_FSClient;

#define ERR_CHECK( result ) \
	if( result != FMOD_OK )															   \
	{																				   \
		LOG_WRITE( "FMOD error! (%d) %s\n", result, FMOD_ErrorString( result ) );	   \
		exit( -1 );																	   \
	}

void MediaPlayer::Initialize()
{
	FMOD_RESULT result;
	//result = FMOD::System_Create( &FMODSystem );
	result = FMOD_System_Create( &FMODSystem );
	ERR_CHECK( result );

	static FMOD_WIIU_EXTRADRIVERDATA g_extraDriverData;
	memset( &g_extraDriverData, 0, sizeof( g_extraDriverData ) );

	g_extraDriverData.threadFile = FMOD_THREAD_DEFAULT;
	g_extraDriverData.threadGeometry = FMOD_THREAD_DEFAULT;
	g_extraDriverData.threadMixer = FMOD_THREAD_DEFAULT;
	g_extraDriverData.threadNonBlocking = FMOD_THREAD_DEFAULT;
	g_extraDriverData.threadStream = FMOD_THREAD_DEFAULT;
	g_extraDriverData.fileSystemClient = GLOBAL_FSClient;

	//result = FMODSystem->init( 100, FMOD_INIT_NORMAL, &g_extraDriverData );
	result = FMOD_System_Init( FMODSystem, 100, FMOD_INIT_NORMAL, &g_extraDriverData );
	ERR_CHECK( result );

	CurrentChannel = NULL;
}

void MediaPlayer::Shutdown()
{
	//FMODSystem->release();
	FMOD_System_Release( FMODSystem );
}

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
	FMOD_RESULT result;
	/*result = FMODSystem->playSound( CurrentChannel ? FMOD_CHANNEL_REUSE : FMOD_CHANNEL_FREE,
		song->internal_->Song, true, &CurrentChannel );*/
	
	result = FMOD_System_PlaySound( FMODSystem, CurrentChannel ? FMOD_CHANNEL_REUSE : FMOD_CHANNEL_REUSE,
		song->internal_->Song, true, &CurrentChannel );

	if( result != FMOD_OK )
	{
		LOG_WRITE( "Failed to play song.\n" );
	}
	//CurrentChannel->setVolume( Volume );
	FMOD_Channel_SetVolume( CurrentChannel, Volume );
	FMOD_WiiU_SetControllerSpeaker( CurrentChannel, FMOD_WIIU_CONTROLLER_TV | FMOD_WIIU_CONTROLLER_DRC );
	//CurrentChannel->setPaused( false );
	FMOD_Channel_SetPaused( CurrentChannel, false );
}

void MediaPlayer::Pause()
{
	if( CurrentChannel )
	{
		//CurrentChannel->setPaused( true );
		FMOD_Channel_SetPaused( CurrentChannel, true );
	}
}

void MediaPlayer::Resume()
{
	if( CurrentChannel )
	{
		//CurrentChannel->setPaused( false );
		FMOD_Channel_SetPaused( CurrentChannel, false );
	}
}

void MediaPlayer::Stop()
{
	if( CurrentChannel )
	{
		//CurrentChannel->stop();
		FMOD_Channel_Stop( CurrentChannel );
		CurrentChannel = NULL;
	}
}

MediaState MediaPlayer::GetState()
{
	if( !CurrentChannel )
		return MediaState_Paused;

	//bool isPlaying;
	//CurrentChannel->isPlaying( &isPlaying );
	FMOD_BOOL isPlaying;
	FMOD_Channel_IsPlaying( CurrentChannel, &isPlaying );

	return isPlaying ? MediaState_Playing : MediaState_Paused;
}

bool MediaPlayer::IsRepeating = false;

void MediaPlayer::SetVolume( float volume )
{
	Volume = volume;

	if( CurrentChannel )
	{
		//CurrentChannel->setVolume( volume );
		FMOD_Channel_SetVolume( CurrentChannel, volume );
	}
}

float MediaPlayer::GetVolume()
{
	return Volume;
}
