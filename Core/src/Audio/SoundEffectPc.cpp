#include <Audio/SoundEffect.h>

#include <al.h>
#include <alc.h>

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

struct SoundEffectInternal
{
	ALuint Source;
	ALuint Buffer;
};

SoundEffect::SoundEffect() :
	internal_( new SoundEffectInternal )
{
	internal_->Source = 0;
	internal_->Buffer = 0;
}

SoundEffect::~SoundEffect()
{
	delete internal_;
}

// Helper operators.
template< typename T >
boost::shared_ptr< File > &operator >> ( boost::shared_ptr< File > &file, T &i )
{
	file->Read( reinterpret_cast< char * >( &i ), sizeof( T ) );
	return file;
}

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

	
	return;

	alGenBuffers( 1, &internal_->Buffer );
	alGenSources( 1, &internal_->Source );

	ALuint frequency;
	ALenum format;
	unsigned char *data;
	int size;

	alBufferData( internal_->Buffer, format, data, size, frequency );
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
	alSourceQueueBuffers( internal_->Source, 1, &internal_->Buffer );
	alSourcePlay( internal_->Source );
}
