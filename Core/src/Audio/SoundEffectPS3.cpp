#include <Audio/SoundEffect.h>

#include <Audio/PS3/mscommon.h>
#include <cmath>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

struct SoundEffectInternal
{
	char *Samples;
	unsigned int SampleSize;
	unsigned int DataFormat;
	unsigned int NumChannels;
	unsigned int SamplingRate;
};

SoundEffect::SoundEffect() :
	internal_( new SoundEffectInternal )
{
	memset( internal_, 0, sizeof( SoundEffectInternal ) );
}

SoundEffect::~SoundEffect()
{
	free( internal_->Samples );
	delete internal_;
}

// Helper operators.
template< typename T >
boost::shared_ptr< File > &operator >> ( boost::shared_ptr< File > &file, T &i )
{
	file->Read( reinterpret_cast< char * >( &i ), sizeof( T ) );
	return file;
}

#define NTOHS( x ) ( ( ( ( x ) & 0xff ) << 8 ) | ( ( ( x ) >> 8 ) & 0xff ) )
#define NTOHL( x ) ( ( NTOHS( x & 0xffff ) << 16 ) | NTOHS( ( x >> 16 ) & 0xffff ) )

template<>
boost::shared_ptr< File > &operator >> ( boost::shared_ptr< File > &file, unsigned int &i )
{
	file->Read( reinterpret_cast< char * >( &i ), sizeof( unsigned int ) );
	i = NTOHL( i );

	return file;
}

template<>
boost::shared_ptr< File > &operator >> ( boost::shared_ptr< File > &file, unsigned short &i )
{
	file->Read( reinterpret_cast< char * >( &i ), sizeof( unsigned short ) );

	i = NTOHS( i );

	return file;
}

#undef NOTHS
#undef NTOHL


static void Skip( boost::shared_ptr< File > &file, unsigned int length )
{
	char buffer[ 1024 ];
	
	while( length > 0 )
	{
		unsigned int toSkip = length > sizeof( buffer ) ? sizeof( buffer ) : length;
		file->Read( buffer, toSkip );
		length -= toSkip;
	}
}

void SoundEffect::Load( const std::string &path )
{
	boost::shared_ptr<File> soundFile = FILESYSTEM.Open( path );

	if( !soundFile->IsOpen() )
	{
		LOG.Write( "Failed: %s\n", path.c_str() );
		return;
	}

	unsigned int ckId = 0;
	unsigned int ckSize = 0;

	soundFile >> ckId;

	if( ckId != 'FFIR' )
		return;

	soundFile >> ckSize;
	soundFile >> ckId;

	if( ckId != 'EVAW' )
		return;

	// Skip to the 'fmt ' chunk.
	do
	{
		soundFile >> ckId;
		soundFile >> ckSize;

		if( ckId == ' tmf' )
			break;

		Skip( soundFile, ckSize );

	} while( !soundFile->IsEOF() );

	if( soundFile->IsEOF() )
		return;

	if( ckSize != 16 )
		return;

	unsigned short formatTag;
	unsigned short numChannels;
	unsigned int samplesPerSecond;
	unsigned int averageBytesPerSecond;
	unsigned short blockAlign;
	unsigned short bitsPerSample;
	
	soundFile >> formatTag;
	soundFile >> numChannels;
	soundFile >> samplesPerSecond;
	soundFile >> averageBytesPerSecond;
	soundFile >> blockAlign;
	soundFile >> bitsPerSample;

	// Make sure this is just a normal PCM.
	if( formatTag != 0x1 )
		return;

	// Skip to the 'fmt ' chunk.
	do
	{
		soundFile >> ckId;
		soundFile >> ckSize;

		if( ckId == 'atad' )
			break;

		Skip( soundFile, ckSize );

	} while( !soundFile->IsEOF() );

	if( soundFile->IsEOF() )
		return;

	if( ckId != 'atad' )
		return;

	internal_->SamplingRate = samplesPerSecond;
	unsigned char *data;
	
	internal_->NumChannels = numChannels;

	if( bitsPerSample == 8 )
	{
		LOG.Write( "8 bit audio not supported!\n" );
		return;
	}
	else if( bitsPerSample == 16 )
		internal_->DataFormat = CELL_MS_16BIT_LITTLE;

	internal_->SampleSize = ckSize;
	internal_->Samples = reinterpret_cast< char * >( memalign( 128, ckSize ) );
	soundFile->Read( internal_->Samples, ckSize );
}

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
		break;
	}
}

long TriggerStream( long nCh, long pSampleData1, const long nSize, 
	const long nFrequency, const long nSampleChannels,
	unsigned int nDataFormat )
{
CellMSInfo  MS_Info;
float vol;

    MS_Info.SubBusGroup         = CELL_MS_MASTER_BUS;

// Set address and size of data to play

    MS_Info.FirstBuffer         = (void *)((long)pSampleData1);
    MS_Info.FirstBufferSize     = nSize;
    MS_Info.SecondBuffer         = 0;
    MS_Info.SecondBufferSize     = 0;

	// Set pitch and number of channels
    MS_Info.Pitch               = nFrequency;
    MS_Info.numChannels         = nSampleChannels;
	MS_Info.flags				= CELL_MS_STREAM_AUTOCLOSE;

	// Initial delay (in samples) before playback starts. Allows for sample accurate playback
	MS_Info.initialOffset		= 0;

	// Input data type
	MS_Info.inputType = nDataFormat;

    cellMSStreamSetInfo(nCh, &MS_Info);
	
	cellMSStreamSetCallbackFunc( nCh, StreamCallback );

    return nCh;
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
	if( !internal_->Samples )
		return;

	long stream = cellMSStreamOpen();

	if( stream < 0 )
		return;

	stream = TriggerStream( stream, reinterpret_cast< long >( internal_->Samples ), internal_->SampleSize,
		internal_->SamplingRate, internal_->NumChannels, internal_->DataFormat ); 
	
	cellMSCoreSetVolume1( stream, CELL_MS_DRY, CELL_MS_SPEAKER_FL, CELL_MS_CHANNEL_0, volume );
	cellMSCoreSetVolume1( stream, CELL_MS_DRY, CELL_MS_SPEAKER_FR, CELL_MS_CHANNEL_0, volume );
	cellMSStreamPlay( stream );
}
