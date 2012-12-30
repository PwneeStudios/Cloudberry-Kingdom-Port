#include <Audio/SoundEffect.h>

#include <cmath>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "AudioInternalWiiU.h"
#include "CKSounds.h"

struct SoundEffectInternal
{
	int SoundId;
};

SoundEffect::SoundEffect() :
	internal_( new SoundEffectInternal )
{
	internal_->SoundId = 0;
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
	if( path == "Content/Sound/Bash.wav" ) internal_->SoundId = Bash;
	else if( path == "Content/Sound/Blob_Squish.wav" ) internal_->SoundId = Blob_Squish;
	else if( path == "Content/Sound/BouncyBlock_Bounce.wav" ) internal_->SoundId = BouncyBlock_Bounce;
	else if( path == "Content/Sound/BouncyJump.wav" ) internal_->SoundId = BouncyJump;
	else if( path == "Content/Sound/BouncyJump_Small.wav" ) internal_->SoundId = BouncyJump_Small;
	else if( path == "Content/Sound/BoxHero_Jump.wav" ) internal_->SoundId = BoxHero_Jump;
	else if( path == "Content/Sound/BoxHero_Land.wav" ) internal_->SoundId = BoxHero_Land;
	else if( path == "Content/Sound/Checkpoint.wav" ) internal_->SoundId = Checkpoint;
	else if( path == "Content/Sound/Coin.wav" ) internal_->SoundId = Coin;
	else if( path == "Content/Sound/Death_Chime.wav" ) internal_->SoundId = Death_Chime;
	else if( path == "Content/Sound/Door_Opening.wav" ) internal_->SoundId = Door_Opening;
	else if( path == "Content/Sound/Door_Slamming.wav" ) internal_->SoundId = Door_Slamming;
	else if( path == "Content/Sound/DoubleJump.wav" ) internal_->SoundId = DoubleJump;
	else if( path == "Content/Sound/DustCloud_Explode.wav" ) internal_->SoundId = DustCloud_Explode;
	else if( path == "Content/Sound/ExtraLifeSound.wav" ) internal_->SoundId = ExtraLifeSound;
	else if( path == "Content/Sound/HeroUnlockedSound.wav" ) internal_->SoundId = HeroUnlockedSound;
	else if( path == "Content/Sound/Jetpack.wav" ) internal_->SoundId = Jetpack;
	else if( path == "Content/Sound/Jump.wav" ) internal_->SoundId = Jump;
	else if( path == "Content/Sound/jump5.wav" ) internal_->SoundId = jump5;
	else if( path == "Content/Sound/Menu_Back.wav" ) internal_->SoundId = Menu_Back;
	else if( path == "Content/Sound/Menu_Hover.wav" ) internal_->SoundId = Menu_Hover;
	else if( path == "Content/Sound/Menu_Select.wav" ) internal_->SoundId = Menu_Select;
	else if( path == "Content/Sound/Menu_Tick.wav" ) internal_->SoundId = Menu_Tick;
	else if( path == "Content/Sound/PerfectSound.wav" ) internal_->SoundId = PerfectSound;
	else if( path == "Content/Sound/Piece_Explosion_Small.wav" ) internal_->SoundId = Piece_Explosion_Small;
	else if( path == "Content/Sound/Pop_1.wav" ) internal_->SoundId = Pop_1;
	else if( path == "Content/Sound/Pop_2.wav" ) internal_->SoundId = Pop_2;
	else if( path == "Content/Sound/Pop_3.wav" ) internal_->SoundId = Pop_3;
	else if( path == "Content/Sound/Record_Scratch.wav" ) internal_->SoundId = Record_Scratch;
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
	AXVPB *axVoice;
	Voice *v;

	axVoice = AXAcquireVoice( 15, VoiceDropCallback, 0 );

	if( axVoice )
	{
		AXVoiceBegin( axVoice );

		v = &Voices[ axVoice->index ];
		v->AXVoice = axVoice;

		v->SPEntry = SPGetSoundEntry( SPTable, internal_->SoundId );

		SPPrepareSound( v->SPEntry, v->AXVoice, ( v->SPEntry )->sampleRate );

		short sPan = static_cast< short >( ( ( pan + 1.f ) / 2.f ) * 127.f );
		sPan = sPan < 0 ? 0 : ( sPan > 127 ? 127 : sPan );
		float fPitch = powf( 8.f, pitch );

		v->Ve.currentVolume = static_cast< u16 >( volume * 32768 );
		v->Ve.currentDelta = 0;
		AXSetVoiceDeviceMix( v->AXVoice, AX_DEVICE_TV, AX_TV_ID0, MixChannels );
		AXSetVoiceVe( v->AXVoice, &v->Ve );
		LOG.Write( "Volume %f: %f -> %X\n", volume, volume * 32768, v->Ve.currentVolume );

		AXSetVoiceSrcType( v->AXVoice, AX_SRC_TYPE_LINEAR );
		AXSetVoiceState( v->AXVoice, AX_PB_STATE_RUN );

		AXSetVoiceSrcRatio( v->AXVoice, fPitch );
		AXSetDeviceCompressor( AX_DEVICE_TV, 0 );

		AXVoiceEnd( axVoice );
	}
}
