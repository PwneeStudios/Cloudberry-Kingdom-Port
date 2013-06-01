#include <Audio/SoundEffect.h>

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
}

static void StreamCallback( int streamNumber, void *userData, int callbackType, void *readBuffer, int readSize )
{
}

long TriggerStream( long nCh, long pSampleData1, const long nSize, 
	const long nFrequency, const long nSampleChannels,
	unsigned int nDataFormat )
{
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
}
