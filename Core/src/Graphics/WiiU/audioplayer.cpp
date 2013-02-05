/*---------------------------------------------------------------------------*

  Copyright 2011 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/

/*=========================================================================*
            includes
 *=========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <cafe/demo.h>
#include <cafe/ax.h>
#include "MovieTest.h"


/*=========================================================================*
            external variables
 *=========================================================================*/

extern MP4PlayerCore    *MP4PlayerCorePtr[];
extern MP4DemuxCore     *MP4DemuxCorePtr[];

static void callbackAudioFrame(s32 threadnum);

static void handleFinalMixTV (AX_FINAL_MIX_CB_STRUCT *info);
static void handleFinalMixDRC(AX_FINAL_MIX_CB_STRUCT *info);

static AXPBOFFSET addrL[2];
static AXPBOFFSET addrR[2];


/*-------------------------------------------------------------------------*
    Name:           getPcmData
    Description:    read stream data for Lch.
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
static void getPcmData(s32 threadnum)
{
    s32  size;
    s32  length;
    s32  rlength;

    size    = MP4PlayerCorePtr[threadnum]->STREAMBUFFER_BLOCK_SIZE;

    length  = size;
    rlength = length & ~0x1f;

    MP4PlayerCorePtr[threadnum]->AudioCurrBufID = (MP4PlayerCorePtr[threadnum]->AudioCurrBufID+1);
    if (MP4PlayerCorePtr[threadnum]->AudioCurrBufID == STREAMBUFFER_BLOCKS)
    {
        MP4PlayerCorePtr[threadnum]->AudioCurrBufID = 0;
    }

    MP4PlayerCorePtr[threadnum]->audioinfo.offset += rlength;
}


/*-------------------------------------------------------------------------*
    Name:           callbackAudioFrame
    Description:    function called every audio frame.
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
static void callbackAudioFrame(s32 threadnum)
{
    u32  curr_ptr;
    u32  curr_blk_id;

    switch (MP4PlayerCorePtr[threadnum]->Audio_Action)
    {
        case STREAM_NONE:
        case STREAM_INITIALIZING:
        case STREAM_STOPPED:

            break;

        case STREAM_STARTED:
            
            curr_ptr    = addrL[threadnum].currentOffset;
            curr_blk_id = curr_ptr / MP4PlayerCorePtr[threadnum]->AudioSamplePerBufSize;

            if (MP4PlayerCorePtr[threadnum]->audioinfo.done)
            {
                if (((curr_ptr < MP4PlayerCorePtr[threadnum]->AudioPrevPtr) && ((MP4PlayerCorePtr[threadnum]->AudioPrevPtr < MP4PlayerCorePtr[threadnum]->audioinfo.end_addr) || (MP4PlayerCorePtr[threadnum]->audioinfo.end_addr <= curr_ptr))) ||
                    ((MP4PlayerCorePtr[threadnum]->AudioPrevPtr < curr_ptr) && ((MP4PlayerCorePtr[threadnum]->AudioPrevPtr < MP4PlayerCorePtr[threadnum]->audioinfo.end_addr) && (MP4PlayerCorePtr[threadnum]->audioinfo.end_addr <= curr_ptr))))
                {
                    MP4PlayerCorePtr[threadnum]->Audio_Action = STREAM_STOPPING;
                }
            }

            // cycle through n buffers, keeping as many refilled as possible
            // that means catch up to but do not over-write curr_ptr's current block

            // use MP4PlayerCorePtr[threadnum]->AudioSamplePerBufSize as the block size in samples
            // fill block[MP4PlayerCorePtr[threadnum]->AudioCurrBufID] if curr_ptr has moved beyond it
            if (MP4PlayerCorePtr[threadnum]->AudioCurrBufID != curr_blk_id)
            {
                MP4PlayerCorePtr[threadnum]->AudioBuff_Offset = MP4PlayerCorePtr[threadnum]->STREAMBUFFER_BLOCK_SIZE * MP4PlayerCorePtr[threadnum]->AudioCurrBufID;
                getPcmData(threadnum);
            }
            MP4PlayerCorePtr[threadnum]->AudioPrevPtr = curr_ptr;
            break;

        case STREAM_STOPPING:
            
            MP4PlayerCorePtr[threadnum]->Audio_Action = STREAM_STOPPED;

            break;
    }
}


/*-------------------------------------------------------------------------*
    Name:           startStreamPcm16
    Description:    play PCM16 stream.
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
static void startStreamPcm16(s32 threadnum)
{
    s32         length;
    s32         rlength;
    
    if (MP4PlayerCorePtr[threadnum]->Audio_Action != STREAM_NONE)
    {
        return;
    }

    MP4PlayerCorePtr[threadnum]->Audio_Action = STREAM_INITIALIZING;

    MP4PlayerCorePtr[threadnum]->audioinfo.format = AX_PB_FORMAT_PCM16;
    MP4PlayerCorePtr[threadnum]->audioinfo.done   = 0;
    MP4PlayerCorePtr[threadnum]->audioinfo.offset = 0;

    // read stream data - fill all buffer blocks to start with
    length  = MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE;
    rlength = length & ~0x1f;
    MP4PlayerCorePtr[threadnum]->audioinfo.offset += rlength;

    // setup pointer
    MP4PlayerCorePtr[threadnum]->AudioSamplePerBufSize = MP4PlayerCorePtr[threadnum]->STREAMBUFFER_BLOCK_SIZE >> 1;
    MP4PlayerCorePtr[threadnum]->AudioPrevPtr = 0;
    MP4PlayerCorePtr[threadnum]->AudioCurrBufID = 0;
    
    addrL[threadnum].samples       = MP4PlayerCorePtr[threadnum]->PCMBufferL;
    addrL[threadnum].loopOffset    = 0;
    addrL[threadnum].endOffset     = MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE >> 1;
    addrL[threadnum].currentOffset = 0;

    addrR[threadnum].samples       = MP4PlayerCorePtr[threadnum]->PCMBufferR;
    addrR[threadnum].loopOffset    = 0;
    addrR[threadnum].endOffset     = MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE >> 1;
    addrR[threadnum].currentOffset = 0;

    if (threadnum)
    {
        AXSetDeviceUpsampleStage        (AX_DEVICE_DRC, 0); // 32kHz データ再生する時は、この引数を 1 に。
    }
    else
    {
        AXSetDeviceUpsampleStage        (AX_DEVICE_TV,  0); // 32kHz データ再生する時は、この引数を 1 に。
    }
}


/*-------------------------------------------------------------------------*
    Name:           handleFinalMixXX
    Description:    xxx
    Arguments:      xxx
    Returns:        none
 *-------------------------------------------------------------------------*/
static void handleFinalMixTV(AX_FINAL_MIX_CB_STRUCT *info)
{
    s32  sCnt;
    s32* lptr;
    s32* rptr;
    s32* surLeft;
    s32* surRight;
    s32* fc;
    s32* lfe;
    s16* inputL;
    s16* inputR;
    s32  indexL, indexR;
    s32  topL, topR;
    s32  buttomL, buttomR;
    
    s32  threadnum;
    
    ASSERT(info->numChnsIn == AX_MAX_NUM_TV_CHS);
    
    threadnum = 0;
    
    lptr     = info->data[0];
    rptr     = info->data[1];
    surLeft  = info->data[2];
    surRight = info->data[3];
    fc       = info->data[4];
    lfe      = info->data[5];

    inputL  = (s16*)addrL[threadnum].samples;
    indexL  = addrL[threadnum].currentOffset;
    topL    = addrL[threadnum].loopOffset;
    buttomL = addrL[threadnum].endOffset;
        
    inputR  = (s16*)addrR[threadnum].samples;
    indexR  = addrR[threadnum].currentOffset;
    topR    = addrR[threadnum].loopOffset;
    buttomR = addrR[threadnum].endOffset;
    
    for (sCnt = 0 ; sCnt< info->numSamples ; sCnt++)
    {
        *lptr++ = (s32)inputL[indexL++];

        if (indexL >= buttomL)
        {
            indexL = topL;
        }
        
        *rptr++ = (s32)inputR[indexR++];
        
        if (indexR >= buttomR)
        {
            indexR = topR;
        }
        
        *surLeft++  = 0;
        *surRight++ = 0;
        *lfe++      = 0;
        *fc++       = 0;
    }
    
    addrL[threadnum].currentOffset = indexL;
    addrR[threadnum].currentOffset = indexR;
    
    callbackAudioFrame(threadnum);
}


static void handleFinalMixDRC(AX_FINAL_MIX_CB_STRUCT *info)
{
    s32  sCnt;
    s32* lptr;
    s32* rptr;
    s32* surLeft;
    s32* surRight;
    s16* inputL;
    s16* inputR;
    s32  indexL, indexR;
    s32  topL, topR;
    s32  buttomL, buttomR;
    
    s32  threadnum;
    
    ASSERT(info->numChnsIn == AX_MAX_NUM_DRC_CHS);
    
    threadnum = 1;

    lptr     = info->data[0];
    rptr     = info->data[1];
    surLeft  = info->data[2];
    surRight = info->data[3];

    inputL  = (s16*)addrL[threadnum].samples;
    indexL  = addrL[threadnum].currentOffset;
    topL    = addrL[threadnum].loopOffset;
    buttomL = addrL[threadnum].endOffset;
        
    inputR  = (s16*)addrR[threadnum].samples;
    indexR  = addrR[threadnum].currentOffset;
    topR    = addrR[threadnum].loopOffset;
    buttomR = addrR[threadnum].endOffset;
    
    for (sCnt = 0 ; sCnt< info->numSamples ; sCnt++)
    {
        *lptr++ = (s32)inputL[indexL++];
        if (indexL >= buttomL)
        {
            indexL = topL;
        }
        
        *rptr++ = (s32)inputR[indexR++];
        if (indexR >= buttomR)
        {
            indexR = topR;
        }
        
        *surLeft++  = 0;
        *surRight++ = 0;
    }
    
    addrL[threadnum].currentOffset = indexL;
    addrR[threadnum].currentOffset = indexR;
    
    callbackAudioFrame(threadnum);
}


/*-------------------------------------------------------------------------*
    Name:           AudioStart
    Description:    audio system start
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
void AudioStart(s32 mode)
{
    if (mode == 0)
    {
        if (MP4DemuxCorePtr[0]->AudioTrackFound)
        {
            AXRegisterDeviceFinalMixCallback(AX_DEVICE_TV,  handleFinalMixTV);
            OSSleepMilliseconds(50);
            MP4PlayerCorePtr[0]->Audio_Action = STREAM_STARTED;
        }
    }
    else if (mode == 1)
    {
        if (MP4DemuxCorePtr[1]->AudioTrackFound)
        {
            AXRegisterDeviceFinalMixCallback(AX_DEVICE_DRC, handleFinalMixDRC);
            OSSleepMilliseconds(50);
            MP4PlayerCorePtr[1]->Audio_Action = STREAM_STARTED;
        }
    }
}


/*-------------------------------------------------------------------------*
    Name:           AudioInit
    Description:    audio system initialize
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
void AudioInit(s32 threadnum)
{
    MP4PlayerCorePtr[threadnum]->Audio_Action = STREAM_NONE;
    MP4PlayerCorePtr[threadnum]->VoiceParamL = NULL;
    MP4PlayerCorePtr[threadnum]->VoiceParamR = NULL;

    OSReport("Running axstream audio on core %d\r", OSGetCoreId());
    OSReport("Preparing the PCM16 Stream for playback\r");
    MP4PlayerCorePtr[threadnum]->AudioBuff_Offset = 0;
    MP4PlayerCorePtr[threadnum]->pre_AudioBuff_Offset = -1;
    startStreamPcm16(threadnum);
}


/*-------------------------------------------------------------------------*
    Name:           AudioBufferAlloc
    Description:    audio buffer allocate
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
void AudioBufferAlloc(s32 SampleSize, s32 threadnum)
{

    MP4PlayerCorePtr[threadnum]->STREAMBUFFER_BLOCK_SIZE = (STREAMBUFFER_KB_SIZE * (SampleSize/2));                             // bytes per buffer
    MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE       = (MP4PlayerCorePtr[threadnum]->STREAMBUFFER_BLOCK_SIZE * STREAMBUFFER_BLOCKS);   // total buffer bytes

    MP4PlayerCorePtr[threadnum]->PCMBufferL = (u8 *)MEMAllocFromDefaultHeapEx(MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE, 1024);     // Audio PCM BufferL allocate
    MP4PlayerCorePtr[threadnum]->PCMBufferR = (u8 *)MEMAllocFromDefaultHeapEx(MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE, 1024);     // Audio PCM BufferR allocate
    memset(MP4PlayerCorePtr[threadnum]->PCMBufferL, 0, MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE);   // Buffer Initialize
    memset(MP4PlayerCorePtr[threadnum]->PCMBufferR, 0, MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE);   // Buffer Initialize
}


/*-------------------------------------------------------------------------*
    Name:           AudioExit
    Description:    audio system exit
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
void AudioExit(s32 threadnum)
{
    // stop the adpcm stream
    if (threadnum == 0)
    {
        AXRegisterDeviceFinalMixCallback(AX_DEVICE_TV,  NULL);
    }
    else
    {
        AXRegisterDeviceFinalMixCallback(AX_DEVICE_DRC,  NULL);
    }
    MP4PlayerCorePtr[threadnum]->Audio_Action = STREAM_NONE;

    memset(MP4PlayerCorePtr[threadnum]->PCMBufferL, 0, MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE);   // Buffer Initialize
    memset(MP4PlayerCorePtr[threadnum]->PCMBufferR, 0, MP4PlayerCorePtr[threadnum]->STREAMBUFFER_SIZE);   // Buffer Initialize

    if (MP4PlayerCorePtr[threadnum]->PCMBufferL != NULL)
    {
        MEMFreeToDefaultHeap(MP4PlayerCorePtr[threadnum]->PCMBufferL);
    }
    if (MP4PlayerCorePtr[threadnum]->PCMBufferR != NULL)
    {
        MEMFreeToDefaultHeap(MP4PlayerCorePtr[threadnum]->PCMBufferR);
    }

    if (threadnum)
    {
        AXRegisterDeviceFinalMixCallback(AX_DEVICE_DRC, NULL);
    }
    else
    {
        AXRegisterDeviceFinalMixCallback(AX_DEVICE_TV, NULL);
    }
    
    OSReport("Audio Shut down completed\r");
}


#ifdef USE_PROCESS_SWITCHING
/*-------------------------------------------------------------------------*
    Name:           AudioProcessPause
    Description:    audio purocess pause
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
void AudioProcessPause (s32 threadnum)
{
    if (MP4DemuxCorePtr[threadnum]->AudioTrackFound == 1)
    {
        if (threadnum == 0)
        {
            AXRegisterDeviceFinalMixCallback(AX_DEVICE_TV,  NULL);
        }
        else
        {
            AXRegisterDeviceFinalMixCallback(AX_DEVICE_DRC,  NULL);
        }
        MP4PlayerCorePtr[threadnum]->Audio_Action = STREAM_NONE;
    }
}


/*-------------------------------------------------------------------------*
    Name:           AudioProcessReStart
    Description:    audio purocess restart
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
void AudioProcessReStart (s32 threadnum)
{
    if (MP4DemuxCorePtr[threadnum]->AudioTrackFound == 1)
    {
        if (threadnum == 0)
        {
            AXRegisterDeviceFinalMixCallback(AX_DEVICE_TV,  handleFinalMixTV);
        }
        else
        {
            AXRegisterDeviceFinalMixCallback(AX_DEVICE_DRC,  handleFinalMixDRC);
        }
        MP4PlayerCorePtr[threadnum]->Audio_Action = STREAM_STARTED;
    }
}
#endif
