#include <Audio/MediaPlayer.h>

#include <Utility/Log.h>

#include <Audio/PS3/mscommon.h>

static int SUBNUM = 1;
static int PLAYSUB = SUBNUM | CELL_MS_BUS_FLAG;
static bool multiStreamUpdateThreadRunning = false;
static bool receivedExitGameRequest = false;
static int portNum = 0;
static long fps60 = 1000000 / 60;
static void *mp3Memory = NULL;

static void MultiStreamUpdateThread( uint64_t param );

void MediaPlayer::Initialize()
{
	CellAudioPortParam audioParam;
	CellAudioPortConfig portConfig;

	if( InitialiseAudio( CELL_MS_MAX_STREAMS, 31, portNum, audioParam, portConfig, 0, true ) )
	{
		LOG.Write( "Error: failed to initialize multistream\n" );
		exit( -1 );
	}

	int sizeNeeded = cellMSMP3GetNeededMemorySize( 256 );
	mp3Memory = new char[ sizeNeeded ];
	LOG.Write( "Multistream requires %d KB at 0x%x\n", sizeNeeded, mp3Memory );

	int ret = cellMSMP3Init( 256, mp3Memory );
	if( ret )
	{
		LOG.Write( "Error: failed to initialize MP3: 0x%x\n", ret );
		exit( -1 );
	}

	LOG.Write( "Info: MP3 returned: 0x%x\n", ret );

	float fBusVols[64] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	cellMSCoreSetVolume64( PLAYSUB, CELL_MS_WET, fBusVols );

	cellMSCoreSetVolume64( CELL_MS_MASTER_BUS, CELL_MS_DRY, fBusVols );

	StartMultiStreamUpdateThread( MultiStreamUpdateThread );
	multiStreamUpdateThreadRunning = true;

}

void MediaPlayer::Shutdown()
{
	receivedExitGameRequest = true;
	ShutdownMultiStream();

	delete[] mp3Memory;
	mp3Memory = NULL;
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

void MultiStreamUpdateThread( uint64_t param )
{
	( void )param;

	cellAudioPortStart( portNum );
	while( !receivedExitGameRequest )
	{
		if( !cellMSSystemSignalSPU() )
			sys_timer_usleep( fps60 / 32 );

		cellMSSystemGenerateCallbacks();
	}
	cellAudioPortStop( portNum );
	multiStreamUpdateThreadRunning = false;
	sys_ppu_thread_exit( 0 );
}
