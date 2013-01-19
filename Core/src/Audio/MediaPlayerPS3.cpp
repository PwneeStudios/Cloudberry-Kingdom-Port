#include <Audio/MediaPlayer.h>

#include <Utility/Log.h>

void MediaPlayer::Initialize()
{
}

void MediaPlayer::Shutdown()
{
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
