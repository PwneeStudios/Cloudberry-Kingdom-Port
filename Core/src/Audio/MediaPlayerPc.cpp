#include <Audio/MediaPlayer.h>

#include <al.h>
#include <alc.h>

#include <Utility/Log.h>

static ALCdevice *Device = 0;
static ALCcontext *Context = 0;

void MediaPlayer::Initialize()
{
	Device = alcOpenDevice( NULL );
	if( !Device )
	{
		LOG_WRITE( "Failed to open sound device.\n" );
		return;
	}

	Context = alcCreateContext( Device, NULL );
	alcMakeContextCurrent( Context );
	if( !Context )
	{
		LOG_WRITE( "Failed to create sound context.\n" );
		alcCloseDevice( Device );
		Device = 0;
		return;
	}
}

void MediaPlayer::Shutdown()
{
	alcMakeContextCurrent( NULL );
	if( Context )
		alcDestroyContext( Context );

	if( Device )
		alcCloseDevice( Device );
}

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
}

void MediaPlayer::Pause()
{
}

void MediaPlayer::Resume()
{
}

void MediaPlayer::Stop()
{
}

MediaState MediaPlayer::GetState()
{
	return MediaState_Paused;
}

bool MediaPlayer::IsRepeating = false;

void MediaPlayer::SetVolume( float volume )
{
}

float MediaPlayer::GetVolume()
{
	return 0.f;
}
