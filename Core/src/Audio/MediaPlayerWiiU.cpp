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

#include <fmod.hpp>
#include <fmod_errors.h>

FMOD::System *FMODSystem;
FMOD::Channel *CurrentChannel;

float Volume;

#define ERR_CHECK( result ) \
	if( result != FMOD_OK )															   \
	{																				   \
		LOG.Write( "FMOD error! (%d) %s\n", result, FMOD_ErrorString( result ) );	   \
		exit( -1 );																	   \
	}

void MediaPlayer::Initialize()
{
	using namespace FMOD;

	FMOD_RESULT result;
	result = FMOD::System_Create( &FMODSystem );
	ERR_CHECK( result );

	result = FMODSystem->init( 100, FMOD_INIT_NORMAL, 0 );
	ERR_CHECK( result );

	CurrentChannel = NULL;
}

void MediaPlayer::Shutdown()
{
	FMODSystem->release();
}

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
	FMOD_RESULT result;
	result = FMODSystem->playSound( CurrentChannel ? FMOD_CHANNEL_REUSE : FMOD_CHANNEL_FREE,
		song->internal_->Song, true, &CurrentChannel );

	if( result != FMOD_OK )
		LOG.Write( "Failed to play song.\n" );

	CurrentChannel->setVolume( Volume );
	CurrentChannel->setPaused( false );
}

void MediaPlayer::Pause()
{
	if( CurrentChannel )
		CurrentChannel->setPaused( true );
}

void MediaPlayer::Resume()
{
	if( CurrentChannel )
		CurrentChannel->setPaused( false );
}

void MediaPlayer::Stop()
{
	if( CurrentChannel )
	{
		CurrentChannel->stop();
		CurrentChannel = NULL;
	}
}

MediaState MediaPlayer::GetState()
{
	if( !CurrentChannel )
		return MediaState_Paused;

	bool isPlaying;
	CurrentChannel->isPlaying( &isPlaying );

	return isPlaying ? MediaState_Playing : MediaState_Paused;
}

bool MediaPlayer::IsRepeating = false;

void MediaPlayer::SetVolume( float volume )
{
	Volume = volume;

	if( CurrentChannel )
		CurrentChannel->setVolume( volume );
}

float MediaPlayer::GetVolume()
{
	return Volume;
}
