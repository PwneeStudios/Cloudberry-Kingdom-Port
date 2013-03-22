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
		LOG_WRITE( "Failed: %s\n", path.c_str() );
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

	ALuint frequency = samplesPerSecond;
	ALenum format = 0;
	unsigned char *data;
	
	if( bitsPerSample == 8 )
	{
		if( numChannels == 1 )
			format = AL_FORMAT_MONO8;
		else if( numChannels == 2 )
			format = AL_FORMAT_STEREO8;
	}
	else if( bitsPerSample == 16 )
	{
		if( numChannels == 1 )
			format = AL_FORMAT_MONO16;
		else if( numChannels == 2 )
			format = AL_FORMAT_STEREO16;
	}

	if( !format )
		return;

	data = new unsigned char[ ckSize ];
	soundFile->Read( reinterpret_cast< char * >( data ), ckSize );

	alGenBuffers( 1, &internal_->Buffer );
	alGenSources( 1, &internal_->Source );

	alBufferData( internal_->Buffer, format, data, ckSize, frequency );

	delete[] data;

	alSourceQueueBuffers( internal_->Source, 1, &internal_->Buffer );
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
	alSourcef( internal_->Source, AL_GAIN, volume );
	alSourcef( internal_->Source, AL_PITCH, powf( 2.f, pitch ) );
	alSource3f( internal_->Source, AL_POSITION, pan, 0, 0 );
	alSourcePlay( internal_->Source );
}
