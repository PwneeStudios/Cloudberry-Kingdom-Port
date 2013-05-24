/***********************************************************
 *
 *  Copyright (C) 2012  PUX Corporation
 *  All Rights Reserved.
 *
 ***********************************************************/

#ifndef __MOVIETEST_API_H__
#define __MOVIETEST_API_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cafe/os.h>
#include <cafe/fs.h>
#include <cafe/demo.h>
#include <cafe/ax.h>
#include "mp4dmx_demo.h"
#include <cafe/mp4dmx.h>
#include <cafe/h264.h>

/*=========================================================================*
            definitions
 *=========================================================================*/

#define DIVIDE_HEADSIZE         (32768)                 // Partition size MP4 media header
#define H264DEC_STREAMBUF_SIZE  ((s32)(62500*1200/8))   // bitstream buffer size (Level 4.2)
#define H264DEC_AVCHEADER_SIZE  (32*32+32*256)          // SPS and PPS data size in bitstream
#define AACDEC_MAX_FREQ_INDEX   12
static const s32 AACDEC_giFreqIndex[AACDEC_MAX_FREQ_INDEX] = {
    96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025, 8000
};


/*******************
 System
*******************/
#define VIDEO_BUFFER_NUM        (30)    // max 60fps
#define AUDIO_BUFFER_NUM        (300)    // max 48kHz 48000/1024
#define FILEMEMORYSIZE          (130*1024*1024) // Big enough for largest movie.
//#define MAX_FRAME_NUM           (100)    // max video frame rate(60fps)

/*******************
 Video
*******************/
#define UVD_ALIGN_PITCH_IN_PIXELS(PitchInPixels)    ((PitchInPixels + 0xFF) & ~0xFF)
#define UVD_BUFFER_ALIGNMENT    (1024)
#define UVD_BUFFER_PAD          (0)
#define MAX_FRAME_BUFFER        (VIDEO_BUFFER_NUM)
#define VIDEO_MAX_IMAGE_SIZE    ((2800*1408*3)>>1)          // video image max size

/*******************
 Audio
*******************/
/*---------------------------------------------------------------------------*
   AX voice
 *---------------------------------------------------------------------------*/
#define STREAMBUFFER_BLOCKS     AUDIO_BUFFER_NUM            // number of buffers per channel
#define STREAMBUFFER_KB_SIZE    2                           // KBytes per buffer

/*---------------------------------------------------------------------------*
   stream control flag
 *---------------------------------------------------------------------------*/
#define STREAM_NONE             0
#define STREAM_INITIALIZING     1
#define STREAM_STARTED          2
#define STREAM_STOPPING         3
#define STREAM_STOPPED          4


/*=========================================================================*
            structure
 *=========================================================================*/

/*******************
 System
*******************/
/* FrameBuffer Structure */
typedef struct  __MACodecFrame__    {
    s32     PTS;
    u8      *bufp;
    s32     Size;
    s32     Status;
} MACodecFrame;


// video image info
typedef struct __LIST_H264DEC_FM__ {
    s32     used;
    void   *h264decfm;
} List_H264DecFm;


/* audio stream info */
typedef struct
{
    u16     format;
    s32     done;
    s32     offset;
    u32     end_addr;
} AudioBufferInfo;


/* stream save ring buffer */
typedef struct __StreamRingInfoV__ {
    s32     rpos;
    s32     wpos;
    u8      *bufp[VIDEO_BUFFER_NUM];
    s32     PTS[VIDEO_BUFFER_NUM];
    s32     Size[VIDEO_BUFFER_NUM];
    s32     Status[VIDEO_BUFFER_NUM];
    s32     CMP_OFFSET[VIDEO_BUFFER_NUM];
} StreamRingInfoV;


/* stream save ring buffer */
typedef struct __StreamRingInfoA__ {
    s32     rpos;
    s32     wpos;
    u8      *bufp[AUDIO_BUFFER_NUM];
    s32     PTS[AUDIO_BUFFER_NUM];
    s32     Size[AUDIO_BUFFER_NUM];
    s32     Status[AUDIO_BUFFER_NUM];
    s32     CMP_OFFSET[AUDIO_BUFFER_NUM];
} StreamRingInfoA;


/* MP4 Player Core Structure */
typedef struct __MP4PlayerCore__ {
    // AVSync Variables
    s32     df_v;               // 
    s32     ff_v;               // 
    s32     df_a;               // 
    s32     ff_a;               // 
    u32     sys_basetime;       // system base time
    MACodecFrame    OutputVideoInfo[VIDEO_BUFFER_NUM];  // 
    MACodecFrame    OutputAudioInfo[AUDIO_BUFFER_NUM];  // 
    MP4DMXFW_CtrlParam   MP4DMUXParam;                  // 
    // thread stack
    s32     vthread_end;        // video thread end flag
    s32     athread_end;        // audio thread end flag
    s32     execendflag;
    s32     voutfound;
    s32     aoutfound;

    // File System Variables
    u32     file_input_mode;
    FSAsyncParams  async_vparams;
    FSAsyncParams  async_aparams;
    u8      *streamFullBuffer;
    s32     video_fsync_comp;
    s32     audio_fsync_comp;
    u8      *DataBuffPtr;
    u32     CurrBuffLength;
    u32     InputFileSize;
    u32     TotalReadFileSize;

    // Video Device Variables
    u32     UVDOutFrameSize;
    List_H264DecFm List_h264decfm[MAX_FRAME_BUFFER];
    void *h264decfm[MAX_FRAME_BUFFER];
    s32              OutputFrames;
    GX2Texture       NV12Tex1;
    GX2Texture       NV12Tex2;
    GX2Surface       *RenderSurf;
    s32              RenderSwitch;
    void             *VideoUserMem;
    u8      *StreamRingBufPtrV;
    s32     StreamRingBufSizeV;
    s32     StreamRingBufPosV;

    u8      *StreamRingBufPtrA;
    s32     StreamRingBufSizeA;
    s32     StreamRingBufPosA;

    // Auduio Device Variables
    u32     AudioFirstFlag;
    u32     FrameSkipFlag;
    u32     AudioSampleRate;
    u8      *PCMBufferL;
    u8      *PCMBufferR;
    s32     AudioBuff_Offset;
    s32     pre_AudioBuff_Offset;
    u32     Audio_Action;
    AudioBufferInfo    audioinfo;
    u32     STREAMBUFFER_BLOCK_SIZE;
    u32     STREAMBUFFER_SIZE;
    s32     AudioSampleBytePerFrame;
    s32     AudioLastBufferInit;

    // voice
    AXVPB   *VoiceParamL;
    AXVPB   *VoiceParamR;
    u32     AudioSamplePerBufSize;      // samples in a buffer block
    u32     AudioPrevPtr;               // currentOffset last time we checked
    u32     AudioCurrBufID;             // index to next buffer block to be filled
} MP4PlayerCore;


/* MP4Demux CallBack Structure */
typedef struct{
    s32     v_track_id;
    s32     a_track_id;
    void    **mlibHandle;       /* MP4Demux handler */
    void    *h264memPtr;        /* work memory address for H.264 decoder */
} MP4DMX_CB_HANDLE;


/* MP4Demux Core Structure */
typedef struct __MP4DemuxCore__ {
    // System
    MEMAllocator     gAllocator;
    StreamRingInfoV  VideoStreamInfo;
    StreamRingInfoA  AudioStreamInfo;

    // H.264 Video Decoder
    void    *H264BSBuffer;      // u8   Length : H264DEC_STREAMBUF_SIZE+8       H264 Input Bitstream Buffer Pointer
    void    *H264HeaderBuffer;  // u8   Length : H264DEC_AVCHEADER_SIZE         MP4Demux SPS/PPS Store Buffer Pointer
    void    *H264WorkBuffer;    // u8   Length :                                H264 Decoder Work Buffer Pointer
    void    *H264ExtFrameMem;   // u8   Length :                                H264 Decoder Frame Buffer Pointer
    void    *curr_throw_264decfm;
    H264DECOutput       *h264decoutput;
    void *UserMem;
    s32     threadnumforh264;
    s32     H264ImageWidth;
    s32     H264ImageHeight;
    s32     H264Profile;
    s32     H264Level;
    s32     H264DecFirstFlag;
    s32     H264HeaderSize;
    s32     H264BpicTimeOffset;

    // AAC Audio Decoder
    void    *AACOutBuffer;      // s16  Length : AACDEC_PCM_SAMPLE_SIZE*2*2     AAC Decoded Output Buffer Pointer(Doubling for the frequency conversion)
    void    *AACBSBuffer;       // u8   Length : AACDEC_STREAM_MAX_SIZE         AAC Input Bitstream Buffer Pointer
    void    *AACWorkBuffer;     // u8   Length : AACDEC_WORK_SIZE               AAC Decoder Work Buffer Pointer
    void    *AACFreqConvTmpL;   // s16  Length : AACDEC_PCM_SAMPLE_SIZE*2       AAC Frequency conversion result output buffer for L-channel
    void    *AACFreqConvTmpR;   // s16  Length : AACDEC_PCM_SAMPLE_SIZE*2       AAC Frequency conversion result output buffer for R-channel
    void    *AACOutRefBuffer;
    s32     AACDecFirstFlag;
    s32     AACSampeRate;
    s32     AACChannelNum;
    s32     AACRefPts;
    s32     AACOutStartFlag;

    // MP4Demux
    MP4DMX_CB_HANDLE MP4Dmx_CBHandle;
    MP4DMXMpoOutputFunction  MP4Dmx_OutputFunc;
    u8      MP4Dmx_OutAudioFlag;
    u8      MP4Dmx_OutVideoFlag;
    MP4DMXFW_UNIT    InputUnitPtr;
    MP4DMXFW_SAMPLE  InputSample;
    MP4DMXFW_UNIT    OutputUnitPtr;
    MP4DMXFW_SAMPLE  OutputSample;
    s32 (*cbsetfunc)(MP4DMXFW_UNIT *, void *);
    s32 (*cbgetfunc)(MP4DMXFW_UNIT *, void *);

    MP4DMXMpoMp4VideoTrackInf    mp4VideoTrackInf;
    MP4DMXMpoMp4AudioTrackInf    mp4AudioTrackInf;
    MP4DMXAvcConfig              AVCconfig;

    s32      MP4Duration;
    s32      MP4DmxNewStatus;
    s32      MP4DmxOldStatus;
    s32      MP4DmxAfterHeaderSize;
    u64      MP4DmxAfterHeaderOffset;
    s32      MP4DmxSeqFirstFlag;
    s32      MP4DmxSeqSecondFlag;

    s32      VideoTrackFound;
    s32      AudioTrackFound;
    s32      SampleStop;
} MP4DemuxCore;

#endif /* __MOVIETEST_API_H__ */
