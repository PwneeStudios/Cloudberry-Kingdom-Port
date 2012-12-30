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

static void FrameCallback()
{
	for( int i = 0; i < AX_MAX_VOICES; ++i )
	{
		Voice &v = Voices[ i ];

		if( v.AXVoice && !AXVoiceIsProtected( v.AXVoice ) )
		{
			if( AX_PB_STATE_STOP == v.AXVoice->state )
			{
				AXFreeVoice( v.AXVoice );
				v.AXVoice = NULL;
			}
		}
	}
}

void VoiceDropCallback( void *p )
{
	AXVPB *v = reinterpret_cast< AXVPB * >( p );

	Voices[ v->index ].AXVoice = NULL;
	Voices[ v->index ].SPEntry = NULL;
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
}

void MediaPlayer::Shutdown()
{
	AXQuit();

	delete[] SPTable;
	delete[] SPData;
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
float MediaPlayer::Volume = 1.f;
