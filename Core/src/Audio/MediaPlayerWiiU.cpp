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

#include "streamlib/AXStream.h"
#include "streamlib/streamPool.h"

SPSoundTable *SPTable;
static u8 *SPData;
static u32 SPTLength;
static u32 SPDLength;

Voice Voices[ AX_MAX_VOICES ];
AXPBCHMIX MixChannels[ AX_MAX_NUM_TV_CHS ];

static float Volume;

#define SAMPLE_SIZE sizeof( s16 )
#define NUM_FRAMES 4
#define STREAM_BUFFER_SIZE ( NUM_FRAMES * SAMPLE_SIZE * AACDEC_PCM_SAMPLE_SIZE )

/*struct StreamBuffer
{
	u8 Samples[ NUM_FRAMES * SAMPLE_SIZE * AACDEC_PCM_SAMPLE_SIZE ];
	AXPBOFFSET Offset;
};

class ChannelPool
{
	std::list< StreamBuffer * > buffers_;
	std::list< StreamBuffer * > queue_;

public:

	ChannelPool( int numBuffers )
	{
		for( int i = 0; i < numBuffers; ++i )
		{
			StreamBuffer *buffer = reinterpret_cast< StreamBuffer * >( MEMAllocFromDefaultHeapEx( sizeof( StreamBuffer ), 64 ) );
			buffers_.push_back( buffer );
			queue_.push_back( buffer );
			memset( buffer, 0, sizeof( StreamBuffer ) );

			buffer->Offset.format = AX_PB_FORMAT_PCM16;
			buffer->Offset.loopFlag = AXPBADDR_LOOP_OFF;
			buffer->Offset.loopOffset = 0;
			buffer->Offset.endOffset = NUM_FRAMES * AACDEC_PCM_SAMPLE_SIZE - 1;
			buffer->Offset.currentOffset = 0;
			buffer->Offset.samples = buffer->Samples;
		}
	}

	~ChannelPool()
	{
		while( !buffers_.empty() )
		{
			StreamBuffer *buffer = buffers_.front();
			buffers_.pop_front();
			MEMFreeToDefaultHeap( buffer );
		}
	}

	StreamBuffer *Allocate()
	{
		if( queue_.size() == 0 )
			return NULL;

		StreamBuffer *buffer = queue_.front();
		queue_.pop_front();
		return buffer;
	}

	void Free( StreamBuffer *buffer )
	{
		memset( buffer->Samples, 0, sizeof( buffer->Samples ) );
		buffer->Offset.currentOffset = 0;
		queue_.push_back( buffer );
	}
};*/


/**
 * ADTS frame header that precedes any AAC bitstream data.
 */
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

/**
 * Decode an AAC stream.
 */
class AACDecoder
{

	//ChannelPool *bufferPool_;
	h_stream_pool bufferPool_;

	AACDEC_AAC_INFO *AACInfo_;
	u8 *AACBuffer_;
	u8 *AACBufferEnd_;
	u8 *AACWorkBuffer_;
	bool done_;

	/*std::list< StreamBuffer * > leftQueue_;
	std::list< StreamBuffer * > rightQueue_;*/
	std::list< stream_buffer_ctl * > leftQueue_;
	std::list< stream_buffer_ctl * > rightQueue_;

public:

	AACDecoder() :
		AACBuffer_( 0 ),
		AACBufferEnd_( 0 ),
		done_( true )
	{
		//bufferPool_ = new ChannelPool( 8 );
		u32 err = streamPoolCreate( STREAM_BUFFER_SIZE, 8, &bufferPool_ );
		assert( err == POOL_ERR_OK );

		// Initialize AAC library.
		AACInfo_ = reinterpret_cast< AACDEC_AAC_INFO * >( MEMAllocFromDefaultHeapEx( sizeof( AACDEC_AAC_INFO ), 64 ) );
		AACWorkBuffer_ = reinterpret_cast< u8 * >( MEMAllocFromDefaultHeapEx( sizeof( u8 ) * AACDEC_WORK_SIZE, 64 ) );

		AACDECOpen( AACWorkBuffer_ );
	}

	~AACDecoder()
	{
		AACDECClose( AACWorkBuffer_ );

		MEMFreeToDefaultHeap( AACWorkBuffer_ );
		MEMFreeToDefaultHeap( AACInfo_ );

		//delete bufferPool_;
		streamPoolRelease( bufferPool_ );
	}

	void Initialize( u8 *bitstream, size_t length )
	{
		AACBuffer_ = bitstream;
		AACBufferEnd_ = AACBuffer_ + length;

		AACDECRestart( AACWorkBuffer_ );
		done_ = false;

		// Queue up two buffers for each channel.
		Update();
		Update();
	}

	void *GetBase()
	{
		return bufferPool_;
	}

	bool IsDone()
	{
		return done_;
	}

	//StreamBuffer *GetLeftChannel()
	stream_buffer_ctl *GetLeftChannel()
	{
		if( leftQueue_.empty() )
			Update();

		//StreamBuffer *buffer = leftQueue_.front();
		stream_buffer_ctl *buffer = leftQueue_.front();
		leftQueue_.pop_front();
		return buffer;
	}

	//StreamBuffer *PeekLeftChannel()
	stream_buffer_ctl *PeekLeftChannel()
	{
		if( leftQueue_.empty() )
			Update();

		return leftQueue_.front();
	}

	//StreamBuffer *GetRightChannel()
	stream_buffer_ctl *GetRightChannel()
	{
		if( rightQueue_.empty() )
			Update();

		//StreamBuffer *buffer = rightQueue_.front();
		stream_buffer_ctl *buffer = rightQueue_.front();
		rightQueue_.pop_front();
		return buffer;
	}

	//StreamBuffer *PeekRightChannel()
	stream_buffer_ctl *PeekRightChannel()
	{
		if( rightQueue_.empty() )
			Update();

		return rightQueue_.front();
	}

	//void Free( StreamBuffer *buffer )
	void Free( void *buffer )
	{
		//bufferPool_->Free( buffer );
		streamPoolFree( bufferPool_, buffer2buffer_ctl( buffer ) );
	}

	void Update()
	{
		/*StreamBuffer *left = bufferPool_->Allocate();
		StreamBuffer *right = bufferPool_->Allocate();*/
		stream_buffer_ctl *left, *right;
		u32 err;

		err = streamPoolAlloc( bufferPool_, &left );
		assert( err == POOL_ERR_OK );
		err = streamPoolAlloc( bufferPool_, &right );
		assert( err == POOL_ERR_OK );

		/*assert( reinterpret_cast< void * >( left ) == left->Samples );
		assert( reinterpret_cast< void * >( right ) == right->Samples );

		s16 *aacLeftBuffer = reinterpret_cast< s16 * >( left->Samples );
		s16 *aacRightBuffer = reinterpret_cast< s16 * >( right->Samples );*/
		s16 *aacLeftBuffer = reinterpret_cast< s16 * >( left->buffer );
		s16 *aacRightBuffer = reinterpret_cast< s16 * >( right->buffer );
		
		left->mode = AXS_NORMAL;
		left->offsets.format = AX_PB_FORMAT_PCM16;
		left->offsets.loopOffset = 0;
		left->offsets.endOffset = NUM_FRAMES * AACDEC_PCM_SAMPLE_SIZE - 1;
		left->offsets.currentOffset = 0;
		right->mode = AXS_NORMAL;
		right->offsets.format = AX_PB_FORMAT_PCM16;
		right->offsets.loopOffset = 0;
		right->offsets.endOffset = NUM_FRAMES * AACDEC_PCM_SAMPLE_SIZE - 1;
		right->offsets.currentOffset = 0;

		for( int i = 0; i < NUM_FRAMES; ++i )
		{
			ADTSHeader *h = reinterpret_cast< ADTSHeader * >( AACBuffer_ );
	
			if( AACBuffer_ >= AACBufferEnd_ )
			{
				left->mode = AXS_LAST;
				right->mode = AXS_LAST;

				done_ = true;
				break;
			}

			AACInfo_->smp_freq_index = h->SamplingFrequencyIndex;
			AACInfo_->channel = 2;
			size_t headerSize = h->ProtectionAbsent ? 7 : 9;
			AACInfo_->data_size = h->FrameLength - headerSize;
	
			AACBuffer_ += headerSize;

			s32 err = AACDECExecute( AACBuffer_, aacLeftBuffer, aacRightBuffer, AACInfo_, AACWorkBuffer_ );

			if( err != AACDEC_NO_ERR )
			{
				LOG.Write( "Error\n" );
			}

			AACBuffer_ += AACInfo_->data_size;

			aacLeftBuffer += AACDEC_PCM_SAMPLE_SIZE;
			aacRightBuffer += AACDEC_PCM_SAMPLE_SIZE;
		}

		leftQueue_.push_back( left );
		rightQueue_.push_back( right );
	}
};

// The decoder.
AACDecoder *Decoder;

static void FrameCallback()
{
	if( !AXUserIsProtected() )
	{
		for( int i = 0; i < AX_MAX_VOICES; ++i )
		{
			Voice &v = Voices[ i ];

			if( v.AXVoice && !AXVoiceIsProtected( v.AXVoice ) )
			{
				if( !v.Streaming )
				{
					if( AX_PB_STATE_STOP == v.AXVoice->state )
					{
						AXFreeVoice( v.AXVoice );
						v.AXVoice = NULL;
					}
				}
				else
				{
					void *buffer[ 2 ];
					AXS_STATE state;

					state = AXStreamProcess( v.AXVoice, &buffer[ 0 ] );
					if( buffer[ 0 ] )
						Decoder->Free( buffer[ 0 ] );
						//Decoder->Free( reinterpret_cast< StreamBuffer * >( buffer[ 0 ] ) );

					switch( state )
					{
					case AXS_STATE_ERROR:
					case AXS_STATE_STOPPED:
						if( AXS_ERR_OK == AXStreamRelease( v.AXVoice, &buffer[ 0 ], &buffer[ 1 ] ) )
						{
							if( buffer[ 0 ] )
								Decoder->Free( buffer[ 0 ] );
								//Decoder->Free( reinterpret_cast< StreamBuffer * >( buffer[ 0 ] ) );
							if( buffer[ 1 ] )
								Decoder->Free( buffer[ 1 ] );
								//Decoder->Free( reinterpret_cast< StreamBuffer * >( buffer[ 1 ] ) );
						}

						AXFreeVoice( v.AXVoice );
						v.AXVoice = NULL;
						break;

					case AXS_STATE_BUF_REQ:
						{
							/*StreamBuffer *buffer = v.Left ? Decoder->GetLeftChannel() : Decoder->GetRightChannel();
							Decoder->Free( v.Left ? Decoder->GetRightChannel() : Decoder->GetLeftChannel() );
							AXStreamAddBuffer( v.AXVoice, &buffer->Offset, Decoder->IsDone() ? AXS_LAST : AXS_NORMAL );*/
						}
						break;

					case AXS_STATE_RUNNING:
						break;

					default:
						assert( !"Impossible streaming state!" );
					}
				}
			}
		}
	}
}

void VoiceDropCallback( void *p )
{
	AXVPB *v = reinterpret_cast< AXVPB * >( p );

	Voices[ v->index ].AXVoice = NULL;
	Voices[ v->index ].SPEntry = NULL;
	Voices[ v->index ].Streaming = false;
}

void VoiceDropCallbackEx( void *p, u32 context, u32 reason )
{
	LOG.Write( "VOICE DROPPED: %X, context = %d, reason = %d\n", p, context, reason );
	AXVPB *v = reinterpret_cast< AXVPB * >( p );

	void *buffer[ 2 ];
	if( AXS_ERR_OK == AXStreamRelease( v, &buffer[ 0 ], &buffer[ 1 ] ) )
	{
		if( buffer[ 0 ] )
			Decoder->Free( buffer[ 0 ] );
			//Decoder->Free( reinterpret_cast< StreamBuffer * >( buffer[ 0 ] ) );
		if( buffer[ 1 ] )
			Decoder->Free( buffer[ 1 ] );
			//Decoder->Free( reinterpret_cast< StreamBuffer * >( buffer[ 1 ] ) );
	}

	Voices[ v->index ].AXVoice = NULL;
	Voices[ v->index ].SPEntry = NULL;
	Voices[ v->index ].Streaming = false;

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

	// Initialize streaming library.
	AXStreamInit();

	Decoder = new AACDecoder;

	Volume = 1.f;
}

void MediaPlayer::Shutdown()
{
	AXQuit();

	delete[] SPTable;
	delete[] SPData;

	delete Decoder;
}

void InitializeVoice( AXVPB *v, bool left, AACDecoder *decoder )
{
	AXPBADPCM adpcm;
	AXPBOFFSET addr;

	Voice *voice = &Voices[ v->index ];
	voice->AXVoice = v;
	voice->Streaming = true;
	voice->Left = left;

	AXStreamVoiceInit( v );

	memset( &adpcm, 0, sizeof( adpcm ) );
	adpcm.gain = 0x0800;

	//StreamBuffer *buffer = left ? Decoder->PeekLeftChannel() : Decoder->PeekRightChannel();
	
	addr.loopFlag = 0;
	addr.format = AX_PB_FORMAT_PCM16;
	addr.samples = Decoder->GetBase();
	addr.loopOffset = 0;
    addr.endOffset = NUM_FRAMES * AACDEC_PCM_SAMPLE_SIZE - 1;
    addr.currentOffset = 0;

	AXSetVoiceAdpcm( v, &adpcm );
	//AXSetVoiceOffsets( v, &buffer->Offset );
	AXSetVoiceOffsets( v, &addr );

	AXPBSRC src = { 0 };
	src.ratioHi = 0x2;

	AXSetVoiceSrcType( v, AX_SRC_TYPE_LINEAR );
	AXSetVoiceSrc( v, &src );
	AXSetVoiceType( v, AX_PB_TYPE_STREAM );
	AXSetVoiceMixerSelect( v, AX_PB_MIXER_SELECT_PPC );
}

void MediaPlayer::Play( const boost::shared_ptr<Song> &song )
{
	MediaPlayer::Stop();

	Decoder->Initialize( reinterpret_cast< u8 * >( song->internal_->Data ), song->internal_->Length );

	AXVPB *left, *right;

	left = AXAcquireVoiceEx( 16, VoiceDropCallbackEx, 0 );
	//right = AXAcquireVoiceEx( 16, VoiceDropCallbackEx, 0 );

	/*if( !left || !right )
	{
		if( left )
			AXFreeVoice( left );
		if( right )
			AXFreeVoice( right );

		LOG.Write( "Couldn't acquire voices for streaming.\n" );
		return;
	}*/

	AXUserBegin();

	InitializeVoice( left, true, Decoder );
	//InitializeVoice( right, false, Decoder );

	stream_buffer_ctl *buffer = Decoder->GetLeftChannel();
	AXSetVoiceOffsets( left, &buffer->offsets );
	AXStreamAddBuffer( left, &buffer->offsets, static_cast< AXS_BUFFER_MODE >( buffer->mode ) );
	//AXStreamAddBuffer( left, &Decoder->GetLeftChannel()->Offset , AXS_NORMAL );
	//AXStreamAddBuffer( right, &Decoder->GetRightChannel()->Offset, AXS_NORMAL );

	AXStreamStartVoice( left );
	//AXStreamStartVoice( right );

	AXUserEnd();

	/*AXVPB *axVoice = AXAcquireVoice( AX_PRIORITY_NODROP, VoiceDropCallback, 0 );

	if( axVoice )
	{
		AXVoiceBegin( axVoice );

		Voice *v = &Voices[ axVoice->index ];
		v->AXVoice = axVoice;
		v->Streaming = true;
		v->Left = true;

		v->Ve.currentVolume = static_cast< u16 >( Volume * 32768 );
		v->Ve.currentDelta = 0;
		AXSetVoiceDeviceMix( axVoice, AX_DEVICE_TV, AX_TV_ID0, MixChannels );
		AXSetVoiceVe( axVoice, &v->Ve );

		AXSetVoiceSrcType( axVoice, AX_SRC_TYPE_NONE );
		AXSetDeviceCompressor( AX_DEVICE_TV, 0 );

		StreamBuffer *buffer = v->Left ? Decoder->PeekLeftChannel() : Decoder->PeekRightChannel();
		AXSetVoiceOffsets( v->AXVoice, &buffer->Offset );

		AXStreamVoiceInit( v->AXVoice );
		AXStreamAddBuffer( v->AXVoice, &buffer->Offset, AXS_NORMAL );
		AXSetVoiceState( v->AXVoice, AX_PB_STATE_RUN );

		AXVoiceEnd( axVoice );
	}

	axVoice = AXAcquireVoice( AX_PRIORITY_NODROP, VoiceDropCallback, 0 );

	if( axVoice )
	{
		AXVoiceBegin( axVoice );

		Voice *v = &Voices[ axVoice->index ];
		v->AXVoice = axVoice;
		v->Streaming = true;
		v->Left = false;

		v->Ve.currentVolume = static_cast< u16 >( Volume * 32768 );
		v->Ve.currentDelta = 0;
		AXSetVoiceDeviceMix( axVoice, AX_DEVICE_TV, AX_TV_ID0, MixChannels );
		AXSetVoiceVe( axVoice, &v->Ve );

		AXSetVoiceSrcType( axVoice, AX_SRC_TYPE_NONE );
		AXSetDeviceCompressor( AX_DEVICE_TV, 0 );
		
		StreamBuffer *buffer = v->Left ? Decoder->PeekLeftChannel() : Decoder->PeekRightChannel();
		AXSetVoiceOffsets( v->AXVoice, &buffer->Offset );

		AXStreamVoiceInit( v->AXVoice );
		AXStreamAddBuffer( v->AXVoice, &buffer->Offset, AXS_NORMAL );
		AXSetVoiceState( v->AXVoice, AX_PB_STATE_RUN );

		AXVoiceEnd( axVoice );
	}*/
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

void MediaPlayer::SetVolume( float volume )
{
	float delta = volume - Volume;
	Volume = volume;
	Volume = 1.f;
}

float MediaPlayer::GetVolume()
{
	return Volume;
}
