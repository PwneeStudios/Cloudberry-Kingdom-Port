#include <Audio/MediaPlayer.h>

#include <Utility/Log.h>

#include <Audio/PS3/mscommon.h>
#include <Audio/Song.h>
#include "SongInternalPS3.h"
#include <Utility/ConsoleInformation.h>

#include <sys/ppu_thread.h>
#include <sys/timer.h>

#include <Core.h>
#include <Architecture/Scheduler.h>
#include <Architecture/Job.h>

static int SUBNUM = 1;
static int PLAYSUB = SUBNUM | CELL_MS_BUS_FLAG;
static bool multiStreamUpdateThreadRunning = false;
static bool receivedExitGameRequest = false;
static int portNum = 0;
static long fps60 = 1000000 / 60;
static void *mp3Memory = NULL;

static void MultiStreamUpdateThread( uint64_t param );

void *songBuffer = NULL;
long stream = -1;
float musicVolume;
extern sys_ppu_thread_t s_MultiStreamPuThread;


static void StreamCallback( int streamNumber, void *userData, int callbackType, void *readBuffer, int readSize )
{
	switch( callbackType )
	{
	case CELL_MS_CALLBACK_MOREDATA:
		LOG_WRITE( "More data\n" );
		break;
	case CELL_MS_CALLBACK_CLOSESTREAM:
		LOG_WRITE( "Close stream\n" );
		break;
	case CELL_MS_CALLBACK_FINISHEDDRY:
		LOG_WRITE( "Finished dry\n" );
		break;
	case CELL_MS_CALLBACK_FINISHSTREAM:
		LOG_WRITE( "Finish stream\n" );
		if( streamNumber == stream )
		{
			cellMSStreamClose( streamNumber );
			stream = -1;
		}
		break;
	}
}


void MediaPlayer::Initialize()
{
	CellAudioPortParam audioParam;
	CellAudioPortConfig portConfig;

	if( InitialiseAudio( CELL_MS_MAX_STREAMS, 31, portNum, audioParam, portConfig, 0, true ) )
	{
		LOG_WRITE( "Error: failed to initialize multistream\n" );
		exit( -1 );
	}

	int sizeNeeded = cellMSMP3GetNeededMemorySize( 256 );
	mp3Memory = new char[ sizeNeeded ];
	LOG_WRITE( "Multistream requires %d KB at 0x%x\n", sizeNeeded, mp3Memory );

	int ret = cellMSMP3Init( 256, mp3Memory );
	if( ret )
	{
		LOG_WRITE( "Error: failed to initialize MP3: 0x%x\n", ret );
		exit( -1 );
	}

	LOG_WRITE( "Info: MP3 returned: 0x%x\n", ret );

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

	songBuffer = memalign( 128, 10 * 1024 * 1024 );
}

void MediaPlayer::Shutdown()
{
	receivedExitGameRequest = true;
	uint64_t ret;
	sys_ppu_thread_join( s_MultiStreamPuThread, &ret );

	ShutdownMultiStream();

	delete[] mp3Memory;
	mp3Memory = NULL;

	free( songBuffer );
}

int LoadMP3(const char *filename, long *addr, long *size)
{
	unsigned int tSize=0;	// total size
	float tTime=0;			// total time
	int ret;
	CellMSMP3FrameHeader Hdr;
	unsigned int offset=0;

	if(!(filename && addr && size))
		return -1;

	long pData;

    // Open PCM sample data
    int nFileHandle=OpenFile( filename, size);

	assert( *size < 10 * 1024 * 1024 );

    if(nFileHandle<0)
    {
        LOG_WRITE(" ERROR opening file - %s, exiting.\n", filename);
        while(1){};
    }

    // Allocate memory for a sample buffer
	pData = (long)songBuffer;
	// Load file.
	LoadFile(nFileHandle,pData,*size,0,0);

	*addr = pData;

	while(1)
	{
		ret=cellMSMP3GetFrameInfo((void*)pData,&Hdr);
		if (ret==-1)
		{
			LOG_WRITE("Invalid MP3 header\n");
			LOG_WRITE("Offset=0x%x\n",offset);
			cellFsClose( nFileHandle );
			return (-1);	// Invalid MP3 header
		}

		tSize+=Hdr.PacketSize;	// Update total file size
		if ((Hdr.ID3==0)&&(Hdr.Tag==0))
			tTime+=Hdr.PacketTime;	// Update total playing time (in seconds)
		pData+=Hdr.PacketSize;	// Move forward to next packet
		offset+=Hdr.PacketSize;

		if (tSize==(unsigned int)*size)
		{
			LOG_WRITE("MP3 File is valid.\n");
			LOG_WRITE("Total Playback Time at %d Hz = (secs): %f\n",Hdr.Frequency,tTime);
			return(nFileHandle);
		}
		else if (tSize>(unsigned int)*size)
		{
			LOG_WRITE("ERROR: PASSED END OF FILE!\n");
			LOG_WRITE("%x,%x\n",tSize,(int)*size);
			while(1){};
		}
	}
}

long TriggerStream( long nCh,long pSampleData1, long pSampleData2, const long nSize, const long nSize2, const long nFrequency, const long nSampleChannels )
{
CellMSInfo  MS_Info;
float vol;

	//suppress compiler warnings
	SUPPRESS_COMPILER_WARNING(nSampleChannels);


    MS_Info.SubBusGroup         = CELL_MS_MASTER_BUS;

// Set address and size of data to play

    MS_Info.FirstBuffer         = (void *)((long)pSampleData1);
    MS_Info.FirstBufferSize     = nSize;
    MS_Info.SecondBuffer         = 0;
    MS_Info.SecondBufferSize     = 0;

	// Set pitch and number of channels
    MS_Info.Pitch               = nFrequency;
    MS_Info.numChannels         = 2;
	MS_Info.flags				= CELL_MS_STREAM_AUTOCLOSE;

	// Initial delay (in samples) before playback starts. Allows for sample accurate playback
	MS_Info.initialOffset		= 0;

	// Input data type
	MS_Info.inputType = CELL_MS_MP3;

    cellMSStreamSetInfo(nCh, &MS_Info);

	cellMSStreamSetCallbackFunc( nCh, StreamCallback );
// Note: No callback has been setup. This sound will just constantly play. No callbacks required.

	cellMSStreamPlay(nCh);

	cellMSCoreSetVolume1(nCh, CELL_MS_DRY, CELL_MS_SPEAKER_FL, CELL_MS_CHANNEL_0, musicVolume);
	cellMSCoreSetVolume1(nCh, CELL_MS_DRY, CELL_MS_SPEAKER_FR, CELL_MS_CHANNEL_0, musicVolume);
    return nCh;
}


/*void StartMP3Playback( uint64_t context )
{
	SaveToContainerArgs *args = reinterpret_cast< SaveToContainerArgs * >( context );

	EzStorage::SaveToContainer( args->Container, args->FileName, args->SaveLogic, args->Fail );

	delete args;

	sys_ppu_thread_exit( 0 );
}*/

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
		if( !IsCustomMusicPlaying() )
		{
			long addr, size;
			int fd = LoadMP3( path_.c_str(), &addr, &size );
			cellFsClose( fd );

			stream = cellMSStreamOpen();
			stream = TriggerStream( stream, addr, addr, size, size, 44100, 2 );
		}
		PlayJobInProgress = false;
	}
};

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
	if( IsCustomMusicPlaying() )
		return;

	if( PlayJobInProgress )
		return;

	PlayJobInProgress = true;
	/*sys_ppu_thread_t tid;
	int ret = sys_ppu_thread_create( &tid, SaveToContainerThread, reinterpret_cast< uint64_t >( args ), 1001, 16 * 1024, 0, "SaveToContainerThread" );
	*/
	if( stream >= 0 )
	{
		cellMSCoreSetVolume1(stream, CELL_MS_DRY, CELL_MS_SPEAKER_FL, CELL_MS_CHANNEL_0, 0);
		cellMSCoreSetVolume1(stream, CELL_MS_DRY, CELL_MS_SPEAKER_FR, CELL_MS_CHANNEL_0, 0);
		/*cellMSCoreSetVolume1(stream, CELL_MS_WET, CELL_MS_SPEAKER_FL, CELL_MS_CHANNEL_0, 0);
		cellMSCoreSetVolume1(stream, CELL_MS_WET, CELL_MS_SPEAKER_FR, CELL_MS_CHANNEL_0, 0);*/
		//cellMSCoreStop( stream, CELL_MS_STOP );
		cellMSStreamClose( stream );
		stream = -1;
	}

	SCHEDULER->RunJobASAP( new PlaySongJob( song->internal_->Path.c_str() ) );
	/*long addr, size;
	LoadMP3( song->internal_->Path.c_str(), &addr, &size );

	stream = cellMSStreamOpen();
	//sys_timer_usleep( fps60 * 60 * 2 );
	stream = TriggerStream( stream, addr, addr, size, size, 44100, 2 );*/
}

void MediaPlayer::Pause()
{
	if( stream < 0 )
		return;

	cellMSCoreSetPause( stream, CELL_MS_PAUSED );
}

void MediaPlayer::Resume()
{
	if( stream < 0 )
		return;

	cellMSCoreSetPause( stream, CELL_MS_NOTPAUSED );
}

void MediaPlayer::Stop()
{
	if( stream < 0 )
		return;

	cellMSStreamClose( stream );
	stream = -1;
}

MediaState MediaPlayer::GetState()
{
	if( stream < 0 )
		return MediaState_Paused;

	return cellMSCoreGetPause( stream ) == CELL_MS_PAUSED ? MediaState_Paused : MediaState_Playing;
}

bool MediaPlayer::IsRepeating = false;

void SetBGMOverride( bool override )
{
	( void )override;

	MediaPlayer::SetVolume( musicVolume );
}

void MediaPlayer::SetVolume( float volume )
{
	musicVolume = volume;

	if( stream >= 0 )
	{
		float volume = 0;
		if( !IsCustomMusicPlaying() )
			volume = musicVolume;

		cellMSCoreSetVolume1(stream, CELL_MS_DRY, CELL_MS_SPEAKER_FL, CELL_MS_CHANNEL_0, volume);
		cellMSCoreSetVolume1(stream, CELL_MS_DRY, CELL_MS_SPEAKER_FR, CELL_MS_CHANNEL_0, volume);
		/*cellMSCoreSetVolume1(stream, CELL_MS_WET, CELL_MS_SPEAKER_FL, CELL_MS_CHANNEL_0, volume);
		cellMSCoreSetVolume1(stream, CELL_MS_WET, CELL_MS_SPEAKER_FR, CELL_MS_CHANNEL_0, volume);*/
	}
}

float MediaPlayer::GetVolume()
{
	return musicVolume;
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
