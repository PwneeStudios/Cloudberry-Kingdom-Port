#include <Audio/MediaPlayer.h>

#include <Utility/Log.h>

#include <Audio/Song.h>
#include "SongInternalVita.h"
#include <Utility/ConsoleInformation.h>

#include <Core.h>
#include <Architecture/Scheduler.h>
#include <Architecture/Job.h>

static void MultiStreamUpdateThread( uint64_t param );

void *songBuffer = NULL;
long stream = -1;
float musicVolume;

static void StreamCallback( int streamNumber, void *userData, int callbackType, void *readBuffer, int readSize )
{
}

void MediaPlayer::Initialize()
{
}

void MediaPlayer::Shutdown()
{
}

int LoadMP3(const char *filename, long *addr, long *size)
{
}

long TriggerStream( long nCh,long pSampleData1, long pSampleData2, const long nSize, const long nSize2, const long nFrequency, const long nSampleChannels )
{
	return 0;
}

static bool PlayJobInProgress = false;

class PlaySongJob : public Job
{
	std::string path_;

public:
	PlaySongJob( const std::string &path )
		: path_( path )
	{
	}

	// From Job.
	void Do()
	{
		PlayJobInProgress = false;
	}
};

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
}

bool MediaPlayer::IsRepeating = false;

void SetBGMOverride( bool override )
{
}

void MediaPlayer::SetVolume( float volume )
{
}

float MediaPlayer::GetVolume()
{
	return musicVolume;
}

void MultiStreamUpdateThread( uint64_t param )
{
}
