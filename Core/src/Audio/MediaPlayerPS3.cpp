#include <Audio/MediaPlayer.h>

#include <Utility/Log.h>

#include <Audio/PS3/mscommon.h>
#include <Audio/Song.h>
#include "SongInternalPS3.h"

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


static void StreamCallback( int streamNumber, void *userData, int callbackType, void *readBuffer, int readSize )
{
	switch( callbackType )
	{
	case CELL_MS_CALLBACK_MOREDATA:
		LOG.Write( "More data\n" );
		break;
	case CELL_MS_CALLBACK_CLOSESTREAM:
		LOG.Write( "Close stream\n" );
		break;
	case CELL_MS_CALLBACK_FINISHEDDRY:
		LOG.Write( "Finished dry\n" );
		break;
	case CELL_MS_CALLBACK_FINISHSTREAM:
		LOG.Write( "Finish stream\n" );
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

	songBuffer = memalign( 128, 10 * 1024 * 1024 );
}

void MediaPlayer::Shutdown()
{
	receivedExitGameRequest = true;
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
        printf(" ERROR opening file - %s, exiting.\n", filename);
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
			printf("Invalid MP3 header\n");
			printf("Offset=0x%x\n",offset);
			return (-1);	// Invalid MP3 header
		}

		tSize+=Hdr.PacketSize;	// Update total file size
		if ((Hdr.ID3==0)&&(Hdr.Tag==0))
			tTime+=Hdr.PacketTime;	// Update total playing time (in seconds)
		pData+=Hdr.PacketSize;	// Move forward to next packet
		offset+=Hdr.PacketSize;

		if (tSize==(unsigned int)*size)
		{
			printf("MP3 File is valid.\n");
			printf("Total Playback Time at %d Hz = (secs): %f\n",Hdr.Frequency,tTime);
			return(nFileHandle);
		}
		else if (tSize>(unsigned int)*size)
		{
			printf("ERROR: PASSED END OF FILE!\n");
			printf("%x,%x\n",tSize,(int)*size);
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

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
	if( stream >= 0 )
	{
		cellMSStreamClose( stream );
		stream = -1;
	}

	long addr, size;
	LoadMP3( song->internal_->Path.c_str(), &addr, &size );

	stream = cellMSStreamOpen();
	sys_timer_usleep( fps60 * 60 * 2 );
	stream = TriggerStream( stream, addr, addr, size, size, 44100, 2 );
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

void MediaPlayer::SetVolume( float volume )
{
	musicVolume = volume;

	if( stream >= 0 )
	{
		cellMSCoreSetVolume1(stream, CELL_MS_DRY, CELL_MS_SPEAKER_FL, CELL_MS_CHANNEL_0, musicVolume);
		cellMSCoreSetVolume1(stream, CELL_MS_DRY, CELL_MS_SPEAKER_FR, CELL_MS_CHANNEL_0, musicVolume);
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
