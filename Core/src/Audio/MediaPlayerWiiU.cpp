#include <Audio/MediaPlayer.h>

#include <cafe/os.h>
#include <cafe/demo.h>
#include <cafe/aacdec.h>
#include <cafe/mem.h>

#include <Audio/Song.h>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "AudioInternalWiiU.h"
#include "SongInternalWiiU.h"

SPSoundTable *SPTable;
static u8 *SPData;
static u32 SPTLength;
static u32 SPDLength;

Voice Voices[ AX_MAX_VOICES ];
AXPBCHMIX MixChannels[ AX_MAX_NUM_TV_CHS ];

static AACDEC_AAC_INFO *AACInfo;
static s16 *AACLeftBuffer;
static s16 *AACRightBuffer;
static u8 *AACBuffer;
static u8 *AACWorkBuffer;

static float Volume;
static Voice *BGMusic;
static AXPBOFFSET BGMLeftChannel;

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
				// Never free music voice.
				if( BGMusic == &v )
					continue;

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

	// Initialize AAC library.
	AACInfo = reinterpret_cast< AACDEC_AAC_INFO * >( MEMAllocFromDefaultHeapEx( sizeof( AACDEC_AAC_INFO ), 64 ) );
	AACLeftBuffer = reinterpret_cast< s16 * >( MEMAllocFromDefaultHeapEx( sizeof( s16 ) * AACDEC_PCM_SAMPLE_SIZE, 64 ) );
	AACRightBuffer = reinterpret_cast< s16 * >( MEMAllocFromDefaultHeapEx( sizeof( s16 ) *AACDEC_PCM_SAMPLE_SIZE, 64 ) );
	//AACBuffer = reinterpret_cast< u8 * >( MEMAllocFromDefaultHeapEx( sizeof( u8 ) * AACDEC_STREAM_MAX_SIZE, 64 ) );
	AACWorkBuffer = reinterpret_cast< u8 * >( MEMAllocFromDefaultHeapEx( sizeof( u8 ) * AACDEC_WORK_SIZE, 64 ) );

	AACDECOpen( AACWorkBuffer );

	BGMusic = NULL;
	Volume = 0;
	BGMLeftChannel.format = AX_PB_FORMAT_PCM16;
	BGMLeftChannel.loopFlag = AXPBADDR_LOOP_ON;
	BGMLeftChannel.loopOffset = 0;
	BGMLeftChannel.endOffset = 16 * 2048;
	BGMLeftChannel.currentOffset = 0;
	u16 *soundBuffer = new u16[ 16 * 2048 ];
	BGMLeftChannel.samples = soundBuffer;
	for( int i = 0; i < 16 * 2048; ++i )
		soundBuffer[ i ] = rand();
}

void MediaPlayer::Shutdown()
{
	AXQuit();

	AACDECClose( AACWorkBuffer );

	MEMFreeToDefaultHeap( AACWorkBuffer );
	//MEMFreeToDefaultHeap( AACBuffer );
	MEMFreeToDefaultHeap( AACRightBuffer );
	MEMFreeToDefaultHeap( AACLeftBuffer );
	MEMFreeToDefaultHeap( AACInfo );

	//delete[] BGMLeftChannel.samples;

	delete[] SPTable;
	delete[] SPData;
}

struct __attribute__( ( packed ) ) ADTSHeader
{
	u32 SyncWord : 12;
	u8 Version : 1;
	u8 Layer : 2;
	u8 ProtectionAbsent : 1;
	u8 Profile : 2;
	u8 SamplingFrequencyIndex : 4;
	u8 PrivateStream : 1;
	u8 ChannelConfiguration : 3;
	u8 Originality : 1;
	u8 Home : 1;
	u8 CopyrightedStream : 1;
	u8 CopyrightStart : 1;
	u16 FrameLength : 13;
	u16 BufferFullness : 11;
	u8 NumAACFrames : 2;
};

/*void DecodeHeader( const u8 *byteStream, ADTSHeader &h )
{
	memset( &h, 0, sizeof( ADTSHeader ) );

	h.SyncWord |= *byteStream;
	++byteStream;
	h.SyncWord |= static_cast< u32 >( *byteStream & 0xF0 ) << 8;
	h.Version = *byteStream & 0x08;
	h.Layer = *byteStream & 0x
}*/

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
	MediaPlayer::Stop();

	AACDECRestart( AACWorkBuffer );

	int i = 0;
	i = sizeof( ADTSHeader );

	AACBuffer = reinterpret_cast< u8 * >( song->internal_->Data );
	u8 *end = AACBuffer + song->internal_->Length;

	while( true )
	{
		ADTSHeader *h = reinterpret_cast< ADTSHeader * >( AACBuffer );
	
		if( AACBuffer >= end )
			break;

		AACInfo->smp_freq_index = h->SamplingFrequencyIndex;
		AACInfo->channel = 2;
		size_t headerSize = h->ProtectionAbsent ? 7 : 9;
		AACInfo->data_size = h->FrameLength - headerSize;
	
		AACBuffer += headerSize;

		s32 err = AACDECExecute( AACBuffer, AACLeftBuffer, AACRightBuffer, AACInfo, AACWorkBuffer );

		if( err != AACDEC_NO_ERR )
		{
			LOG.Write( "Error\n" );
		}

		AACBuffer += AACInfo->data_size;
	}

	AXVPB *axVoice = AXAcquireVoice( AX_PRIORITY_NODROP, VoiceDropCallback, 0 );

	if( axVoice )
	{
		LOG.Write( "Before playing song\n" );
		AXVoiceBegin( axVoice );

		BGMusic = &Voices[ axVoice->index ];
		BGMusic->AXVoice = axVoice;

		AXSetVoiceOffsets( axVoice, &BGMLeftChannel );

		BGMusic->Ve.currentVolume = static_cast< u16 >( Volume * 32768 );
		BGMusic->Ve.currentDelta = 0;
		AXSetVoiceDeviceMix( axVoice, AX_DEVICE_TV, AX_TV_ID0, MixChannels );
		AXSetVoiceVe( axVoice, &BGMusic->Ve );

		AXSetVoiceSrcType( axVoice, AX_SRC_TYPE_LINEAR );
		AXSetVoiceState( axVoice, AX_PB_STATE_RUN );

		AXSetVoiceSrcRatio( axVoice, 1.f );
		AXSetDeviceCompressor( AX_DEVICE_TV, 0 );

		AXVoiceEnd( axVoice );
		LOG.Write( "After playing song\n" );
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

void MediaPlayer::SetVolume( float volume )
{
	float delta = volume - Volume;
	Volume = volume;

	if( BGMusic )
		AXSetVoiceVeDelta( BGMusic->AXVoice, static_cast< s16 >( delta * 32768 ) );
}

float MediaPlayer::GetVolume()
{
	return Volume;
}
