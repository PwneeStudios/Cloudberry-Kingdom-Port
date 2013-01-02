#include <Audio/MediaPlayer.h>

#include <cafe/os.h>
#include <cafe/demo.h>

#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "AudioInternalWiiU.h"

SPSoundTable *SPTable;
static u8 *SPData;
static u32 SPTLength;
static u32 SPDLength;

Voice Voices[ AX_MAX_VOICES ];
AXPBCHMIX MixChannels[ AX_MAX_NUM_TV_CHS ];

Voice *BGMusic;

static void FrameCallback()
{
	for( int i = 0; i < AX_MAX_VOICES; ++i )
	{
		Voice &v = Voices[ i ];

		if( v.AXVoice && !AXVoiceIsProtected( v.AXVoice ) )
		{
			if( v.Paused )
				continue;

			if( AX_PB_STATE_STOP == v.AXVoice->state )
			{
				if( BGMusic == &v )
					BGMusic = NULL;

				AXFreeVoice( v.AXVoice );
				v.AXVoice = NULL;
				v.Paused = false;
			}
		}
	}
}

void VoiceDropCallback( void *p )
{
	AXVPB *v = reinterpret_cast< AXVPB * >( p );

	Voices[ v->index ].AXVoice = NULL;
	Voices[ v->index ].SPEntry = NULL;
	Voices[ v->index ].Paused = false;
}

void MediaPlayer::Initialize()
{
	AXInit();

	const char *sptFile = "Sound/ck_sounds.spt";
	const char *spdFile = "Sound/ck_sounds.spd";

	AXSetDefaultRenderer( AX_PB_MIXER_SELECT_PPC );

	memset( &MixChannels, 0, sizeof( MixChannels ) );
	MixChannels[ AX_CH_LEFT ].bus[ AX_MAIN_BUS ].vol = 0x8000;
	MixChannels[ AX_CH_RIGHT ].bus[ AX_MAIN_BUS ].vol = 0x8000;

	AXRegisterFrameCallback( FrameCallback );

	boost::shared_ptr<File> file = FILESYSTEM.Open( sptFile );
	SPTLength = file->Size();
	char *buffer = new char[ SPTLength ];
	file->Read( buffer, SPTLength );
	SPTable = reinterpret_cast< SPSoundTable * >( buffer );
	
	file = FILESYSTEM.Open( spdFile );
	SPDLength = file->Size();
	buffer = new char[ SPDLength ];
	file->Read( buffer, SPDLength );
	SPData = reinterpret_cast< u8 * >( buffer );

	SPInitSoundTable( SPTable, SPData, NULL );

	BGMusic = NULL;
}

void MediaPlayer::Shutdown()
{
	AXQuit();

	delete[] SPTable;
	delete[] SPData;
}

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
	MediaPlayer::Stop();

	AXVPB *axVoice = AXAcquireVoice( AX_PRIORITY_NODROP, VoiceDropCallback, 0 );

	if( axVoice )
	{
		AXVoiceBegin( axVoice );

		BGMusic = &Voices[ axVoice->index ];
		BGMusic->AXVoice = axVoice;

		BGMusic->Ve.currentVolume = static_cast< u16 >( MediaPlayer::Volume * 32768 );
		BGMusic->Ve.currentDelta = 0;
		AXSetVoiceDeviceMix( axVoice, AX_DEVICE_TV, AX_TV_ID0, MixChannels );
		AXSetVoiceVe( axVoice, &BGMusic->Ve );

		AXSetVoiceSrcType( axVoice, AX_SRC_TYPE_LINEAR );
		AXSetVoiceState( axVoice, AX_PB_STATE_RUN );

		AXSetVoiceSrcRatio( axVoice, 1.f );
		AXSetDeviceCompressor( AX_DEVICE_TV, 0 );

		AXVoiceEnd( axVoice );
	}
}

void MediaPlayer::Pause()
{
	if( BGMusic )
		BGMusic->Paused = true;
}

void MediaPlayer::Resume()
{
	if( BGMusic )
		BGMusic->Paused = false;
}

void MediaPlayer::Stop()
{
	if( BGMusic )
	{
		AXFreeVoice( BGMusic->AXVoice );
		BGMusic->AXVoice = NULL;
		BGMusic->Paused = false;
		BGMusic = NULL;
	}
}

MediaState MediaPlayer::GetState()
{
	return MediaState_Paused;
}

bool MediaPlayer::IsRepeating = false;
float MediaPlayer::Volume = 1.f;
