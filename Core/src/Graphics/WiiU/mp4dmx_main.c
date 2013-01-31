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
#include <stdlib.h>
#include <stdint.h>
#include <cafe.h>
#include <cafe/mem.h>
#include <cafe/fs.h>
#include <cafe/demo.h>
#include <cafe/ax.h>
#include <cafe/mix.h>
#include <cafe/ai.h>
#ifdef USE_PROCESS_SWITCHING
#include <cafe/vpad.h>
#endif
#ifdef PROFILE_ENABLE
#include <cafe/profiler.h>
#endif
#include "MovieTest.h"
#include "videorender.h"

#pragma ghs nowarning 111

/*=========================================================================*
            definitions
 *=========================================================================*/

#define UNASSIGNED_END_TIME_STAMP   0xFFFFFFFFFFFFFFFFULL

#ifdef INPUTNAME_DEFINED
#define MP4_INPUT_SAMPLE1       "/vol/content/codecdemo/01_sample_base.mp4";    // TV
#define MP4_INPUT_SAMPLE2       "/vol/content/codecdemo/metronome_8M720p30p.mp4";          // DRC
#endif

#define VIDEOSKIP_DELAY         (70)                            // permissible delay time
#define FILEMEMORYSIZE          (512*1000*1000)                 // 512MByte
#define TEST_MODE               (0)                             // 1:TV only, 2:DRC only, other:TV & DRC

#define MAXTHREADNUM            (8)
#define STACK_SIZE              (4096*1024)

// For Debug
//#define PRINT_TIME
//#define PRINT_LOG

/*=========================================================================*
            external functions
 *=========================================================================*/

extern void AudioInit(s32 threadnum);
extern void AudioStart(s32 mode);
extern void AudioBufferAlloc(s32 SampleSize, s32 threadnum);
extern void AudioExit(s32 threadnum);
#ifdef USE_PROCESS_SWITCHING
extern void AudioProcessPause(s32 threadnum);
extern void AudioProcessReStart(s32 threadnum);
#endif
extern void VideoExit(s32 threadnum);
extern s32 VideoDraw(u8 *ip, s32 threadnum);
extern void shutdownAudioSystem(void);


/*=========================================================================*
            external variables
 *=========================================================================*/

extern MP4DemuxCore    *MP4DemuxCorePtr[];


/*=========================================================================*
            global variables
 *=========================================================================*/

MP4PlayerCore   MP4PlayerCore1[2];
MP4PlayerCore   *MP4PlayerCorePtr[2];
OSThread        Thread[MAXTHREADNUM];                   // pointer to thread control block to initialize.
u8              ThreadStack[MAXTHREADNUM][STACK_SIZE];  // address of initial stack pointer.
u32             sys_timestart[2];                       // system time start flag
u32             vendflag[2];
u32             aendflag[2];
u32             sys_basetime[2];
#ifdef INPUTNAME_DEFINED
const char      *mp4Filename[2];
#else
const char       fileName[2][1024];
#endif

s32     LoopCounter[2];

#ifdef USE_PROCESS_SWITCHING
OSEvent gDoRelease;
OSEvent gAcquired;
OSEvent gDoRelease_[2];
OSEvent gAcquired_[2];

static OSMessageQueue *pSysQueue;
static s32             debounce = 0;
static s32             debounce_[2];

BOOL   inForeground;
BOOL   inForeground_[2];
static volatile BOOL   CoreDecodeActive[2];
static volatile BOOL   CoreDecodeSleep[2];
static volatile BOOL   CoreDecodeEnd[2];
static volatile BOOL   CoreProcessEnd;

s32 process_sleep_time;
s32 threadabort[2][8];
#ifndef USE_SINGLE_CORE
s32 exc_start_time_stamp[2];
s32 exc_end_time_stamp[2];
#endif

FSClient*      GpClient[2];
FSCmdBlock*    GpCmd[2];
FSFileHandle   Gfh[2];

/*-------------------------------------------------------------------------*
    Name:           ProcessChangeWait
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static void ProcessChangeWait(s32 threadnum, s32 pos)
{
    while(!inForeground)
    {
        threadabort[threadnum][pos] = 1;
        OSSleepMilliseconds(10);
        OSYieldThread();
    }
    threadabort[threadnum][pos] = 0;
}
#endif


/*-------------------------------------------------------------------------*
    Name:           VideoOutputThread
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static s32 VideoOutputThread(s32 intArg, void *ptrArg)
{
    s32 i;
    s32 ret;
    u32 vsys_currtime;
#ifdef PRINT_TIME
    s32 starttime, endtime;
#endif

    OSReport("Video Thread Start\n");

    while(1)
    {
        vsys_currtime = OSTicksToMilliseconds(OSGetTime());
#if TEST_MODE == 1
        for (i = 0; i < 1; i++)
#elif TEST_MODE == 2
        for (i = 1; i < 2; i++)
#else
        for (i = 0; i < 2; i++)
#endif
        {
            if ((vendflag[i] == 0) && sys_timestart[i])
            {
                if (((vsys_currtime - sys_basetime[i]) >= MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS))
                {
                    if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS)
                    {
                        if ((((vsys_currtime - sys_basetime[i]) - MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS) > VIDEOSKIP_DELAY))
                        {
                            MP4PlayerCorePtr[i]->FrameSkipFlag = 1;
                            OSReport("FrameSkip\n");
                        }
                        else
                        {
                            MP4PlayerCorePtr[i]->FrameSkipFlag = 0;
                        }
                    }
                    if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 1)
                    {
#ifdef PRINT_TIME
                        starttime = OSTicksToMilliseconds(OSGetTime());
#endif
                        // video frame draw
#ifdef PRINT_LOG
                        OSReport("CurrTime:%d, VPTS:%d, VDIFF:%d, thread:%d\n",
                            (vsys_currtime - sys_basetime[i]), MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS, abs((vsys_currtime - sys_basetime[i]) - MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS), i);
#endif
                        ret = VideoDraw(MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].bufp, i);
                        if (ret != 0)
                        {
                            OSReport("VideoDraw Failed.\n");
                            vendflag[i] = 1;
                            break;
                        }
                        MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS = 0x7FFFFFFF;
                        MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status = 0;
                        MP4PlayerCorePtr[i]->df_v++;
                        if (MP4PlayerCorePtr[i]->df_v == VIDEO_BUFFER_NUM)
                        {
                            MP4PlayerCorePtr[i]->df_v = 0;
                        }
#ifdef PRINT_TIME
                        endtime = OSTicksToMilliseconds(OSGetTime());
                        OSReport("Time(VideoDraw):%d, thread:%d\n", endtime - starttime, i);
#endif
                    }
                }
                if (!vendflag[i] && MP4PlayerCorePtr[i]->vthread_end && (MP4PlayerCorePtr[i]->df_v == MP4PlayerCorePtr[i]->ff_v) && (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 0))
                {
                    OSReport("Video[%d] Thread End\n", i);
                    vendflag[i] = 1;
                }
            }

#ifdef USE_PROCESS_SWITCHING
            ProcessChangeWait(i, 0);
#endif
        }
        OSYieldThread();
#if TEST_MODE == 1
        if (vendflag[0])
#elif TEST_MODE == 2
        if (vendflag[1])
#else
        if (vendflag[0] && vendflag[1])
#endif
        {
//            break;
        }
    }

    OSReport("Video Thread Finish\n");
    return(0);
}


/*-------------------------------------------------------------------------*
    Name:           AudioOutputThread
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static s32 AudioOutputThread(s32 intArg, void *ptrArg)
{
    s32  i;
    u32  asys_currtime;

    OSReport("Audio Thread Start\n");

    while(1)
    {
        asys_currtime = OSTicksToMilliseconds(OSGetTime());
#if TEST_MODE == 1
        for (i = 0; i < 1; i++)
#elif TEST_MODE == 2
        for (i = 1; i < 2; i++)
#else
        for (i = 0; i < 2; i++)
#endif
        {
            if ((aendflag[i] == 0) && sys_timestart[i])
            {
                if (((asys_currtime - sys_basetime[i]) >= MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS))
                {
                    if (MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].Status == 1)
                    {
                        // audio pcm
                        if (MP4PlayerCorePtr[i]->pre_AudioBuff_Offset != MP4PlayerCorePtr[i]->AudioBuff_Offset)
                        {
#ifdef PRINT_LOG
                            OSReport("CurrTime:%d, APTS:%d, ADIFF:%d, thread:%d, df_a:%d, ff_a:%d\n",
                                (asys_currtime - sys_basetime[i]), MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS, abs((asys_currtime - sys_basetime[i]) - MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS), i, MP4PlayerCorePtr[i]->df_a, MP4PlayerCorePtr[i]->ff_a);
#endif
                            MP4PlayerCorePtr[i]->pre_AudioBuff_Offset = MP4PlayerCorePtr[i]->AudioBuff_Offset;
                            MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS = 0x7FFFFFFF;
                            MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].Status = 0;
                            MP4PlayerCorePtr[i]->df_a++;
                            if (MP4PlayerCorePtr[i]->df_a == AUDIO_BUFFER_NUM)
                            {
                                MP4PlayerCorePtr[i]->df_a = 0;
                            }
                        }
                    }
                }
                if ((MP4PlayerCorePtr[i]->athread_end == 1) && (MP4PlayerCorePtr[i]->AudioLastBufferInit == 0))
                {
                    if (abs(MP4PlayerCorePtr[i]->ff_a - MP4PlayerCorePtr[i]->df_a) > 2)
                    {
                        s32 ff_a_tmp = MP4PlayerCorePtr[i]->ff_a;
                        s32 k;

                        for (k = 0; k < 3; k++)
                        {
                            memset(MP4PlayerCorePtr[i]->PCMBufferL + ff_a_tmp*MP4PlayerCorePtr[i]->AudioSampleBytePerFrame, 0, MP4PlayerCorePtr[i]->AudioSampleBytePerFrame);  // a few frame(about 50ms) initialize
                            memset(MP4PlayerCorePtr[i]->PCMBufferR + ff_a_tmp*MP4PlayerCorePtr[i]->AudioSampleBytePerFrame, 0, MP4PlayerCorePtr[i]->AudioSampleBytePerFrame);  // a few frame(about 50ms) initialize
                            ff_a_tmp++;
                            if (ff_a_tmp== AUDIO_BUFFER_NUM)
                            {
                                ff_a_tmp = 0;
                            }
                        }
                        MP4PlayerCorePtr[i]->AudioLastBufferInit = 1;
                    }
                }
                if (!aendflag[i] && MP4PlayerCorePtr[i]->athread_end && (MP4PlayerCorePtr[i]->df_a == MP4PlayerCorePtr[i]->ff_a) && (MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].Status == 0))
                {
                    OSReport("Audio[%d] Thread End\n", i);
                    aendflag[i] = 1;
                }
            }

#ifdef USE_PROCESS_SWITCHING
            ProcessChangeWait(i, 1);
#endif
        }
        OSYieldThread();
#if TEST_MODE == 1
        if (aendflag[0])
#elif TEST_MODE == 2
        if (aendflag[1])
#else
        if (aendflag[0] && aendflag[1])
#endif
        {
//            break;
        }
    }

    OSReport("Audio Thread Finish\n");
    return(0);
}


/*-------------------------------------------------------------------------*
    Name:           ReadCallbackV
    Description:    Callbacks for video input
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static void ReadCallbackV(
                FSClient        *pClient,
                FSCmdBlock      *pCmd,
                FSStatus        result,
                void            *pContext)
{
    u32 *flag = (u32 *)pContext;
    *flag = 1;
}


/*-------------------------------------------------------------------------*
    Name:           ReadCallbackA
    Description:    Callbacks for audio input
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static void ReadCallbackA(
                FSClient        *pClient,
                FSCmdBlock      *pCmd,
                FSStatus        result,
                void            *pContext)
{
    u32 *flag = (u32 *)pContext;
    *flag = 1;
}


/*-------------------------------------------------------------------------*
    Name:           MediaFileReadInit
    Description:    initialize the input parameters
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
void MediaFileReadInit(s32 threadnum)
{
    MP4PlayerCorePtr[threadnum]->DataBuffPtr = NULL;
    MP4PlayerCorePtr[threadnum]->CurrBuffLength = 0;
}


/*-------------------------------------------------------------------------*
    Name:           MediaFileReadFree
    Description:    release input buffer
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
void MediaFileReadFree(s32 threadnum)
{
    if (MP4PlayerCorePtr[threadnum]->DataBuffPtr != NULL)
    {
        MEMFreeToDefaultHeap(MP4PlayerCorePtr[threadnum]->DataBuffPtr);
        MP4PlayerCorePtr[threadnum]->CurrBuffLength = 0;
    }
}


/*-------------------------------------------------------------------------*
    Name:           MediaFileReadData
    Description:    read the media data
    Arguments:      <input>
                        pData               output buffer pointer
                        bufLen              output buffer size
                        offset              seek point
                        length              request size
    Returns:        read size
 *-------------------------------------------------------------------------*/
u32 MediaFileReadData(u8 **pData, u32 *bufLen, s64 offset, u32 length, s32 threadnum)
{
    FSStatus   status;
    u32     readbyte;

    if (MP4PlayerCorePtr[threadnum]->DataBuffPtr == NULL)
    {
        MP4PlayerCorePtr[threadnum]->DataBuffPtr = (u8 *)MEMAllocFromDefaultHeapEx(length, 1024);
        if (MP4PlayerCorePtr[threadnum]->DataBuffPtr == NULL)
        {
            OSReport("Inputbuf Allocete Error\n");
        }
    }

    if(MP4PlayerCorePtr[threadnum]->CurrBuffLength < length)
    {
        if (MP4PlayerCorePtr[threadnum]->DataBuffPtr != NULL)
        {
            MEMFreeToDefaultHeap(MP4PlayerCorePtr[threadnum]->DataBuffPtr);
            MP4PlayerCorePtr[threadnum]->CurrBuffLength = 0;
        }

        MP4PlayerCorePtr[threadnum]->DataBuffPtr = (u8 *)MEMAllocFromDefaultHeapEx(length, 1024);
        if (MP4PlayerCorePtr[threadnum]->DataBuffPtr == NULL)
        {
            OSReport("Inputbuf Allocete Error\n");
        }
        MP4PlayerCorePtr[threadnum]->CurrBuffLength = length;
    }


    if ((int)(offset + length) > MP4PlayerCorePtr[threadnum]->InputFileSize)
    {
        return 0;
    }


    status = FSSetPosFile(GpClient[threadnum], GpCmd[threadnum], Gfh[threadnum], offset, 0);
    if(status < FS_STATUS_OK)
    {
        return 0;
    }

    if (MP4PlayerCorePtr[threadnum]->file_input_mode == 1)
    {
        if ((offset + length) > MP4PlayerCorePtr[threadnum]->InputFileSize)
        {
            return 0;
        }
        memcpy(MP4PlayerCorePtr[threadnum]->DataBuffPtr, MP4PlayerCorePtr[threadnum]->streamFullBuffer + offset, length);
        readbyte = length;
        MP4PlayerCorePtr[threadnum]->TotalReadFileSize += length;
    }
    else
    {
        status = FSReadFile(
                        GpClient[threadnum],
                        GpCmd[threadnum],
                        (void*)MP4PlayerCorePtr[threadnum]->DataBuffPtr,
                        sizeof(u8),
                        length,
                        Gfh[threadnum],
                        0,
                        FS_RET_NO_ERROR);
        if(status < FS_STATUS_OK)
        {
            return 0;
        }
        readbyte = (u32)status;
    }

    if(readbyte <= 0)
    {
        return 0;
    }

    *pData = MP4PlayerCorePtr[threadnum]->DataBuffPtr;
    *bufLen = readbyte;

    return readbyte;
}


/*-------------------------------------------------------------------------*
    Name:           MediaFileReadDataV
    Description:    read the media data for video
    Arguments:      <input>
                        pData               output buffer pointer
                        bufLen              output buffer size
                        offset              seek point
                        length              request size
    Returns:        read size
 *-------------------------------------------------------------------------*/
u32 MediaFileReadDataV(u8 **pData, u32 *bufLen, s64 offset, u32 length, s32 threadnum)
{
    FSStatus   status;
    u32     readbyte;

    if (MP4PlayerCorePtr[threadnum]->file_input_mode == 0)
    {
        while(!MP4PlayerCorePtr[threadnum]->video_fsync_comp);
        while(!MP4PlayerCorePtr[threadnum]->audio_fsync_comp);
    }

    if ((MP4PlayerCorePtr[threadnum]->StreamRingBufPosV + length) > MP4PlayerCorePtr[threadnum]->StreamRingBufSizeV)
    {
        MP4PlayerCorePtr[threadnum]->StreamRingBufPosV = 0;
    }
    *pData = MP4PlayerCorePtr[threadnum]->StreamRingBufPtrV + MP4PlayerCorePtr[threadnum]->StreamRingBufPosV;
    MP4PlayerCorePtr[threadnum]->StreamRingBufPosV += (((length + 1023) >> 10) << 10);

    if (*pData == NULL)
    {
        OSReport("Inputbuf Allocete Error\n");
    }


    if ((offset + length) > MP4PlayerCorePtr[threadnum]->InputFileSize)
    {
        return 0;
    }

    status = FSSetPosFile(GpClient[threadnum], GpCmd[threadnum], Gfh[threadnum], offset, 0);
    if(status < FS_STATUS_OK)
    {
        return 0;
    }

    MP4PlayerCorePtr[threadnum]->video_fsync_comp = 0;
    MP4PlayerCorePtr[threadnum]->async_vparams.userCallback  = ReadCallbackV;
    MP4PlayerCorePtr[threadnum]->async_vparams.userContext = (void*)&MP4PlayerCorePtr[threadnum]->video_fsync_comp;

    if (MP4PlayerCorePtr[threadnum]->file_input_mode == 1)
    {
        if ((offset + length) > MP4PlayerCorePtr[threadnum]->InputFileSize)
        {
            return 0;
        }
        memcpy(*pData, MP4PlayerCorePtr[threadnum]->streamFullBuffer + offset, length);
        readbyte = length;
        MP4PlayerCorePtr[threadnum]->TotalReadFileSize += length;
    }
    else
    {
        status = FSReadFileAsync(
                        GpClient[threadnum],
                        GpCmd[threadnum],
                        (void*)*pData,
                        sizeof(u8),
                        length,
                        Gfh[threadnum],
                        0,
                        FS_RET_NO_ERROR,
                        &MP4PlayerCorePtr[threadnum]->async_vparams);
        readbyte = length;

        if(readbyte <= 0)
        {
            return 0;
        }
    }

    *bufLen = readbyte;

    return readbyte;
}


/*-------------------------------------------------------------------------*
    Name:           MediaFileReadDataA
    Description:    read the media data for audio
    Arguments:      <input>
                        pData               output buffer pointer
                        bufLen              output buffer size
                        offset              seek point
                        length              request size
    Returns:        read size
 *-------------------------------------------------------------------------*/
u32 MediaFileReadDataA(u8 **pData, u32 *bufLen, s64 offset, u32 length, s32 threadnum)
{
    FSStatus   status;
    u32     readbyte;

    if (MP4PlayerCorePtr[threadnum]->file_input_mode == 0)
    {
        while(!MP4PlayerCorePtr[threadnum]->video_fsync_comp);
        while(!MP4PlayerCorePtr[threadnum]->audio_fsync_comp);
    }

    if ((MP4PlayerCorePtr[threadnum]->StreamRingBufPosA + length) > MP4PlayerCorePtr[threadnum]->StreamRingBufSizeA)
    {
        MP4PlayerCorePtr[threadnum]->StreamRingBufPosA = 0;
    }
    *pData = MP4PlayerCorePtr[threadnum]->StreamRingBufPtrA + MP4PlayerCorePtr[threadnum]->StreamRingBufPosA;
    MP4PlayerCorePtr[threadnum]->StreamRingBufPosA += (((length + 1023) >> 10) << 10);

    if (*pData == NULL)
    {
        OSReport("Inputbuf Allocete Error\n");
    }

    if ((offset + length) > MP4PlayerCorePtr[threadnum]->InputFileSize)
    {
        return 0;
    }

    status = FSSetPosFile(GpClient[threadnum], GpCmd[threadnum], Gfh[threadnum], offset, 0);
    if(status < FS_STATUS_OK)
    {
        return 0;
    }

    MP4PlayerCorePtr[threadnum]->audio_fsync_comp = 0;
    MP4PlayerCorePtr[threadnum]->async_aparams.userCallback  = ReadCallbackA;
    MP4PlayerCorePtr[threadnum]->async_aparams.userContext = (void*)&MP4PlayerCorePtr[threadnum]->audio_fsync_comp;

    if (MP4PlayerCorePtr[threadnum]->file_input_mode == 1)
    {
        if ((offset + length) > MP4PlayerCorePtr[threadnum]->InputFileSize)
        {
            return 0;
        }
        memcpy(*pData, MP4PlayerCorePtr[threadnum]->streamFullBuffer + offset, length);
        readbyte = length;
        MP4PlayerCorePtr[threadnum]->TotalReadFileSize += length;
    }
    else
    {
        status = FSReadFileAsync(
                        GpClient[threadnum],
                        GpCmd[threadnum],
                        (void*)*pData,
                        sizeof(u8),
                        length,
                        Gfh[threadnum],
                        0,
                        FS_RET_NO_ERROR,
                        &MP4PlayerCorePtr[threadnum]->async_aparams);
        readbyte = length;

        if(readbyte <= 0)
        {
            return 0;
        }
    }

    *bufLen = readbyte;

    return readbyte;
}


/*-------------------------------------------------------------------------*
    Name:           cbSetMediaContainerData
    Description:    Media data request callback
                    To be called when the input request for media data from the framework
    Arguments:      <input>
                        unit                Pointer to media data information structure
                        handle              object handle
    Returns:        MP4DMXFW_RET_SUCCESS            Success
                    MP4DMXFW_RET_ERROR_SAMPLE_STOP  finished Media Data
 *-------------------------------------------------------------------------*/
s32 cbSetMediaContainerData(MP4DMXFW_UNIT *unit, void *handle)
{
    s32     ReadSize;
    s32     threadnum = unit->threadnum;

#if defined(USE_PROCESS_SWITCHING) && defined(USE_SINGLE_CORE)
    ProcessChangeWait(threadnum, 2);
#endif

    if (unit->type == MEDIA_HEADER)
    {
        // request header Data
        ReadSize = MediaFileReadData((u8 **)&unit->sample->data_ptr, (u32 *)&unit->bufsize, unit->offset, (s32)unit->sample->size, threadnum);
    }
    else if (unit->type == MEDIA_CHUNK)
    {
        if (unit->track_type == TRACK_TYPE_VIDEO)
        {
            // request video data
            ReadSize = MediaFileReadDataV((u8 **)&unit->sample->data_ptr, (u32 *)&unit->bufsize, unit->offset, (s32)unit->sample->size, threadnum);
        }
        else
        {
            // request audio data
            ReadSize = MediaFileReadDataA((u8 **)&unit->sample->data_ptr, (u32 *)&unit->bufsize, unit->offset, (s32)unit->sample->size, threadnum);
        }
    }
    if(ReadSize == 0)
    {
        return MP4DMXFW_RET_ERROR_SAMPLE_STOP;
    }

    return MP4DMXFW_RET_SUCCESS;
}


/*-------------------------------------------------------------------------*
    Name:           cbGetMediaSampleData
    Description:    Sample data request callback
                    To be called when the output request for sample data from the framework
    Arguments:      <input>
                        unit                Pointer to media data information structure
                        handle              object handle
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 cbGetMediaSampleData(MP4DMXFW_UNIT *unit, void *handle)
{
    s32     threadnum = unit->threadnum;

#if defined(USE_PROCESS_SWITCHING) && defined(USE_SINGLE_CORE)
    ProcessChangeWait(threadnum, 2);
#endif

    if (unit->type == MEDIA_HEADER)
    {
        // Audio and Video Information Notification
        MP4PlayerCorePtr[threadnum]->AudioSampleRate = unit->sample->audio_subsample;
        if (MP4PlayerCorePtr[threadnum]->AudioSampleRate == 0)
        {
            OSReport("audio none.\n");
        }
    }
    else if (unit->type == MEDIA_SAMPLE)
    {
        if (unit->track_type == TRACK_TYPE_VIDEO)
        {
            if (MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].Status == 0)
            {
                MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].PTS = unit->sample->pts;
            }
        }
        else if (unit->track_type == TRACK_TYPE_AUDIO)
        {
            if (MP4PlayerCorePtr[threadnum]->OutputAudioInfo[MP4PlayerCorePtr[threadnum]->ff_a].Status == 0)
            {
                MP4PlayerCorePtr[threadnum]->OutputAudioInfo[MP4PlayerCorePtr[threadnum]->ff_a].PTS = unit->sample->pts;
            }
        }

        if ((((MP4DemuxCorePtr[threadnum]->VideoTrackFound == 1) && (MP4DemuxCorePtr[threadnum]->AudioTrackFound == 1)) &&
             (MP4PlayerCorePtr[threadnum]->OutputVideoInfo[0].PTS == 0) && (MP4PlayerCorePtr[threadnum]->ff_v > ((MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_framerate+1) >> 1)) &&
             (MP4PlayerCorePtr[threadnum]->OutputAudioInfo[0].PTS == 0) && (MP4PlayerCorePtr[threadnum]->ff_a > ((MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.sample_rate/1024) >> 1))) ||
            (((MP4DemuxCorePtr[threadnum]->VideoTrackFound == 1) && (MP4DemuxCorePtr[threadnum]->AudioTrackFound == 0)) &&
             (MP4PlayerCorePtr[threadnum]->OutputVideoInfo[0].PTS == 0) && (MP4PlayerCorePtr[threadnum]->ff_v > ((MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_framerate+1) >> 1))) ||
            (((MP4DemuxCorePtr[threadnum]->VideoTrackFound == 0) && (MP4DemuxCorePtr[threadnum]->AudioTrackFound == 1)) &&
             (MP4PlayerCorePtr[threadnum]->OutputAudioInfo[0].PTS == 0) && (MP4PlayerCorePtr[threadnum]->ff_a > ((MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.sample_rate/1024) >> 1))) ||
            (MP4PlayerCorePtr[threadnum]->execendflag && MP4DemuxCorePtr[threadnum]->VideoTrackFound && (MP4PlayerCorePtr[threadnum]->OutputVideoInfo[0].PTS == 0) && MP4PlayerCorePtr[threadnum]->voutfound) ||
            (MP4PlayerCorePtr[threadnum]->execendflag && MP4DemuxCorePtr[threadnum]->AudioTrackFound && (MP4PlayerCorePtr[threadnum]->OutputAudioInfo[0].PTS == 0) && MP4PlayerCorePtr[threadnum]->aoutfound))
        {
            if (sys_timestart[threadnum] == 0)
            {
                if (MP4PlayerCorePtr[threadnum]->AudioSampleRate != 0)
                {
                    AudioInit(threadnum);
                    AudioStart(threadnum);
                    }
                sys_basetime[threadnum] = OSTicksToMilliseconds(OSGetTime());
            }
            sys_timestart[threadnum] = 1;
        }

        if (unit->track_type == TRACK_TYPE_VIDEO)
        {
            if (MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].Status == 0)
            {
                MP4PlayerCorePtr[threadnum]->voutfound = 1;
                MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].bufp = unit->sample->data_ptr;
                MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].PTS = unit->sample->pts;
                MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].Size = (s32)unit->sample->size;
                MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].Status = 1;

                MP4PlayerCorePtr[threadnum]->ff_v++;
                if (MP4PlayerCorePtr[threadnum]->ff_v == VIDEO_BUFFER_NUM)
                {
                    MP4PlayerCorePtr[threadnum]->ff_v = 0;
                }
                return MP4DMXFW_RET_SUCCESS;
            }
            else if (MP4PlayerCorePtr[threadnum]->vthread_end)
            {
                return -1;      // The video thread has been terminated
            }
            else
            {
                return MP4DMXFW_RET_WARNING_NOP;
            }
        }
        else if (unit->track_type == TRACK_TYPE_AUDIO)
        {
            if (MP4PlayerCorePtr[threadnum]->OutputAudioInfo[MP4PlayerCorePtr[threadnum]->ff_a].Status == 0)
            {
                MP4PlayerCorePtr[threadnum]->aoutfound = 1;
                if (MP4PlayerCorePtr[threadnum]->AudioFirstFlag == 1)
                {
                    if (unit->sample->audio_channel == 1)
                    {
                        AudioBufferAlloc(((s32)unit->sample->size), threadnum);
                        MP4PlayerCorePtr[threadnum]->AudioSampleBytePerFrame = (s32)unit->sample->size;
                    }
                    else
                    {
                        AudioBufferAlloc(((s32)unit->sample->size)/2, threadnum);
                        MP4PlayerCorePtr[threadnum]->AudioSampleBytePerFrame = (s32)unit->sample->size/2;
                    }
                    MP4PlayerCorePtr[threadnum]->AudioFirstFlag = 0;
                }

                if (unit->sample->audio_channel == 1)
                {
                    unit->sample->size <<= 1;
                    memcpy(MP4PlayerCorePtr[threadnum]->PCMBufferL + MP4PlayerCorePtr[threadnum]->ff_a*((s32)unit->sample->size >> 1), unit->sample->data_ptr, ((s32)unit->sample->size >> 1));
                    memcpy(MP4PlayerCorePtr[threadnum]->PCMBufferR + MP4PlayerCorePtr[threadnum]->ff_a*((s32)unit->sample->size >> 1), unit->sample->data_ptr, ((s32)unit->sample->size >> 1));
                }
                else
                {
                    memcpy(MP4PlayerCorePtr[threadnum]->PCMBufferL + MP4PlayerCorePtr[threadnum]->ff_a*((s32)unit->sample->size >> 1), unit->sample->data_ptr, ((s32)unit->sample->size >> 1));
                    memcpy(MP4PlayerCorePtr[threadnum]->PCMBufferR + MP4PlayerCorePtr[threadnum]->ff_a*((s32)unit->sample->size >> 1), unit->sample->data_ptr + ((s32)unit->sample->size >> 1), ((s32)unit->sample->size >> 1));
                }

                DCFlushRange(MP4PlayerCorePtr[threadnum]->PCMBufferL + MP4PlayerCorePtr[threadnum]->ff_a*((s32)unit->sample->size >> 1), ((s32)unit->sample->size >> 1));
                DCFlushRange(MP4PlayerCorePtr[threadnum]->PCMBufferR + MP4PlayerCorePtr[threadnum]->ff_a*((s32)unit->sample->size >> 1), ((s32)unit->sample->size >> 1));

                MP4PlayerCorePtr[threadnum]->OutputAudioInfo[MP4PlayerCorePtr[threadnum]->ff_a].PTS = unit->sample->pts;
                MP4PlayerCorePtr[threadnum]->OutputAudioInfo[MP4PlayerCorePtr[threadnum]->ff_a].Size = (s32)unit->sample->size;
                MP4PlayerCorePtr[threadnum]->OutputAudioInfo[MP4PlayerCorePtr[threadnum]->ff_a].Status = 1;
                MP4PlayerCorePtr[threadnum]->ff_a++;
                if (MP4PlayerCorePtr[threadnum]->ff_a == AUDIO_BUFFER_NUM)
                {
                    MP4PlayerCorePtr[threadnum]->ff_a = 0;
                }
                return MP4DMXFW_RET_SUCCESS;
            }
            else if (MP4PlayerCorePtr[threadnum]->athread_end)
            {
                return -1;      // The audio thread has been terminated
            }
            else
            {
                return MP4DMXFW_RET_WARNING_NOP;
            }
        }
        else if (unit->track_type == TRACK_TYPE_ANY)
        {
        }
    }

    return MP4DMXFW_RET_SUCCESS;
}


/*-------------------------------------------------------------------------*
    Name:           MP4PlayTVorDRC
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static s32 MP4PlayTVorDRC(s32 intArg, void *ptrArg)
{
    MEMHeapHandle   defaultHeap;
    // Memory Variables
    MEMHeapHandle       ExpHeap;
    FSStatus   status;
    FSStat     stat;
    void        *addr;
    u32         size;
    s32         i;

    s32     iMlibRet;
    void    *pMlibHandle=NULL;
    s32     UseWorkMemSize;

#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
    static VPADStatus s_vpads[2][VPAD_MAX_CONTROLLERS][VPAD_MAX_READ_BUFS];
#endif

    MP4PlayerCorePtr[intArg] = &MP4PlayerCore1[intArg];
    MP4PlayerCorePtr[intArg]->InputFileSize = 0;

    // allocate memory to store the input data
    MP4PlayerCorePtr[intArg]->streamFullBuffer = (u8 *)MEMAllocFromDefaultHeapEx(FILEMEMORYSIZE, 64);

    // Allocate buffers.
    GpClient[intArg] = MEMAllocFromDefaultHeap(sizeof(FSClient));
    if (!GpClient[intArg])
    {
        OSHalt("Error: cannot allocate memory for fs client.\n");
    }
    GpCmd[intArg]    = MEMAllocFromDefaultHeap(sizeof(FSCmdBlock));
    if (!GpCmd[intArg])
    {
        OSHalt("Error: cannot allocate memory for command block.\n");
    }
    // Add client to FS.
    FSAddClient(GpClient[intArg], FS_RET_NO_ERROR);

    OSReport("\n\n\n### Start operation ###\n");

    // Init command block.
    FSInitCmdBlock(GpCmd[intArg]);
    OSReport("==> FSInitCmdBlock: Command block initialized.\n");

#ifdef INPUTNAME_DEFINED
    status = FSOpenFile(GpClient[intArg], GpCmd[intArg], (const char *)mp4Filename[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#else
    status = FSOpenFile(GpClient[intArg], GpCmd[intArg], (const char *)fileName[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#endif
    if(status < FS_STATUS_OK)
    {
        OSReport("[ERROR] cannot open mp4 file.\n");
        OSHalt("OS Halt");
    }

#ifdef INPUTNAME_DEFINED
    status = FSGetStat(GpClient[intArg], GpCmd[intArg], mp4Filename[intArg], &stat, 0);
#else
    status = FSGetStat(GpClient[intArg], GpCmd[intArg], fileName[intArg], &stat, 0);
#endif
    if (status < FS_STATUS_OK)
    {
        OSReport("[ERROR] cannot get input mp4 file status.\n");
        OSHalt("OS Halt");
    }

    MP4PlayerCorePtr[intArg]->InputFileSize = stat.size;
    if (MP4PlayerCorePtr[intArg]->InputFileSize > FILEMEMORYSIZE)
    {
        MP4PlayerCorePtr[intArg]->file_input_mode = 0;    // file input
        FSCloseFile(GpClient[intArg], GpCmd[intArg], Gfh[intArg], FS_RET_NO_ERROR);
    }
    else
    {
        MP4PlayerCorePtr[intArg]->file_input_mode = 1;    // memory input
        status = FSReadFile(
                        GpClient[intArg],
                        GpCmd[intArg],
                        (void*)MP4PlayerCorePtr[intArg]->streamFullBuffer,
                        sizeof(u8),
                        MP4PlayerCorePtr[intArg]->InputFileSize,
                        Gfh[intArg],
                        0,
                        FS_RET_NO_ERROR);
        if(status < FS_STATUS_OK)
        {
            return 0;
        }
    }

    while (1)
    {
        OSReport("MP4Play[%d] Thread Start\n", intArg);
        if (MP4PlayerCorePtr[intArg]->file_input_mode == 0)
        {
#ifdef INPUTNAME_DEFINED
            status = FSOpenFile(GpClient[intArg], GpCmd[intArg], mp4Filename[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#else
            status = FSOpenFile(GpClient[intArg], GpCmd[intArg], fileName[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#endif
            if(status < FS_STATUS_OK)
            {
                OSReport("[ERROR] cannot open mp4 file.\n");
                OSHalt("OS Halt");
            }
        }

        vendflag[intArg] = 0;
        aendflag[intArg] = 0;
        sys_timestart[intArg] = 0;
        sys_basetime[intArg] = 0;

        MP4PlayerCorePtr[intArg]->df_v = 0;
        MP4PlayerCorePtr[intArg]->ff_v = 0;
        MP4PlayerCorePtr[intArg]->df_a = 0;
        MP4PlayerCorePtr[intArg]->ff_a = 0;
        MP4PlayerCorePtr[intArg]->vthread_end = 0;
        MP4PlayerCorePtr[intArg]->athread_end = 0;
        MP4PlayerCorePtr[intArg]->execendflag = 0;
        MP4PlayerCorePtr[intArg]->voutfound = 0;
        MP4PlayerCorePtr[intArg]->aoutfound = 0;

        MP4PlayerCorePtr[intArg]->FrameSkipFlag = 0;
        MP4PlayerCorePtr[intArg]->AudioFirstFlag = 1;
        MP4PlayerCorePtr[intArg]->video_fsync_comp = 1;
        MP4PlayerCorePtr[intArg]->audio_fsync_comp = 1;
        MP4PlayerCorePtr[intArg]->TotalReadFileSize = 0;
        MP4PlayerCorePtr[intArg]->AudioSampleBytePerFrame = 0;
        MP4PlayerCorePtr[intArg]->AudioLastBufferInit = 0;

        // MP4DMX Heap Area Allocation
        defaultHeap = MEMGetBaseHeapHandle(MEM_ARENA_2);            /* initialize Exp Heap on MEM2 */
        size = MEMGetAllocatableSizeForExpHeapEx(defaultHeap, 1024);
        addr = MEMAllocFromDefaultHeapEx(size/32, 1024);
        if (!addr)
        {
            OSReport("[ERROR] cannot allocate memory.\n");
            OSHalt("OS Halt");
        }

        // set the heap area
        ExpHeap = MEMCreateExpHeap(addr, size/32);

        MediaFileReadInit(intArg);

        // Set CallBack Parameters
        MP4PlayerCorePtr[intArg]->MP4DMUXParam.MP4DMXFW_CallbackSetData = (void *)cbSetMediaContainerData;
        MP4PlayerCorePtr[intArg]->MP4DMUXParam.MP4DMXFW_CallbackGetData = (void *)cbGetMediaSampleData;

        iMlibRet = MP4DMXFW_Open(ExpHeap, &pMlibHandle, &UseWorkMemSize, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXOpen Failed. ret = %d\n", iMlibRet );
            goto ERROR;
        }

        iMlibRet = MP4DMXFW_Begin( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_Begin Failed. ret = %d\n", iMlibRet );
            goto ERROR;
        }

#ifdef USE_PROCESS_SWITCHING
        if (!MP4DemuxCorePtr[intArg]->VideoTrackFound)
        {
            threadabort[intArg][0] = 1;
        }
        if (!MP4DemuxCorePtr[intArg]->AudioTrackFound)
        {
            threadabort[intArg][1] = 1;
        }
#endif

        // allocate video ringbuffers
        if (MP4DemuxCorePtr[intArg]->VideoTrackFound)
        {
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV = (MP4DemuxCorePtr[intArg]->mp4VideoTrackInf.maxbitrate >> 3);
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV = (MP4PlayerCorePtr[intArg]->StreamRingBufSizeV * 3) >> 1;     // margin
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV += (1024 * VIDEO_BUFFER_NUM/2);                                // margin
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV += H264DEC_AVCHEADER_SIZE;                                     // max sps/pps size
            MP4PlayerCorePtr[intArg]->StreamRingBufPtrV = (u8 *)MEMAllocFromDefaultHeapEx(MP4PlayerCorePtr[intArg]->StreamRingBufSizeV, 1024);
            MP4PlayerCorePtr[intArg]->StreamRingBufPosV = 0;             // buffer position initialize
        }

        // allocate audio ringbuffers
        if (MP4DemuxCorePtr[intArg]->AudioTrackFound)
        {
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeA = ((MP4DemuxCorePtr[intArg]->mp4AudioTrackInf.maxbitrate >> 3) * 5);    // audio buffer size plus 5sec bitstream size
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeA += (1024 * AUDIO_BUFFER_NUM/2);                                         // margin
            MP4PlayerCorePtr[intArg]->StreamRingBufPtrA = (u8 *)MEMAllocFromDefaultHeapEx(MP4PlayerCorePtr[intArg]->StreamRingBufSizeA, 1024);
            MP4PlayerCorePtr[intArg]->StreamRingBufPosA = 0;             // buffer position initialize
        }

        for (i = 0; i < AUDIO_BUFFER_NUM; i++)
        {
            MP4PlayerCorePtr[intArg]->OutputAudioInfo[i].PTS  = 0;
            MP4PlayerCorePtr[intArg]->OutputAudioInfo[i].Size = 0;
            MP4PlayerCorePtr[intArg]->OutputAudioInfo[i].Status = 0;
        }

#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
        exc_start_time_stamp[intArg] = 0;
        exc_end_time_stamp[intArg]   = 0;
        OSReport("MP4Duration[0]:%d\n", MP4DemuxCorePtr[intArg]->MP4Duration);
        for (i = 0; i < MP4DemuxCorePtr[intArg]->MP4Duration/100; i++)
        {
            exc_end_time_stamp[intArg] = exc_start_time_stamp[intArg] + 100;
            iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 0, (s64)exc_start_time_stamp[intArg], (s64)exc_end_time_stamp[intArg], intArg );
            if( iMlibRet != MP4DMXFW_RET_SUCCESS )
            {
                OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
                goto ERROR;
            }

            {
                // ------------------------------- //
                // beginning of process switch detect
                // ------------------------------- //
                static BOOL            ok;

                // Memory for VPAD reads
                s32 vpadErr;

                {
                    if (CoreDecodeActive[intArg] == FALSE)
                    {
#if TEST_MODE == 1
                        threadabort[0][2] = 1;
#elif TEST_MODE == 2
                        threadabort[1][2] = 1;
#else
                        threadabort[0][2] = 1;
                        threadabort[1][2] = 1;
#endif

                        OSResetEvent(&gAcquired_[intArg]);
                        OSSignalEvent(&gDoRelease_[intArg]);

                        VPADShutdown();

                        CoreDecodeSleep[intArg] = TRUE;
                        OSReleaseForeground();
                        inForeground_[intArg] = FALSE;

                    }else if (inForeground_[intArg]){
                        // get input / do ai + physics, etc
                        DEMOPadRead();

                        VPADRead(0, &s_vpads[intArg][0][0], VPAD_MAX_READ_BUFS, &vpadErr);

                        // check for HBM press+release
                        if (DEMOPadGetButtonDown(0) & DEMO_PAD_BUTTON_START)
                            debounce_[intArg] = 1;
                        else if (s_vpads[intArg][0][0].release & VPAD_BUTTON_HOME)
                            debounce_[intArg] = 1;
                        else if (debounce_[intArg] && debounce)
                        {
                            debounce_[intArg] = 0;
                            OSReport("\nSwitch To HBM!\n");
                            ok = OSSendAppSwitchRequest(PFID_HomeButtonMenu, (void *)"Pause", 6);
                            if (!ok)
                            {
                                OSReport("OSSendAppSwitchRequest() failed.\n");
                            }
                            else
                                OSReport("Sent Request ok.\n\n");
                        }
                    }
                }
                // ---------------------------- //
                // end of process switch detect
                // ---------------------------- //
                while(!inForeground_[intArg])
                {
                    if (inForeground)
                    {
                       inForeground_[intArg] = TRUE;
                       CoreDecodeSleep[intArg] = FALSE;

                       OSResetEvent(&gDoRelease_[intArg]);
                       OSSignalEvent(&gAcquired_[intArg]);

#if TEST_MODE == 1
                        threadabort[0][2] = 0;
#elif TEST_MODE == 2
                        threadabort[1][2] = 0;
#else
                        threadabort[0][2] = 0;
                        threadabort[1][2] = 0;
#endif
                    }
                    OSSleepMilliseconds(10);
                }
            }
        }
#else
        iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 0, (int16_t)0, (s64)UNASSIGNED_END_TIME_STAMP, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
            goto ERROR;
        }
#endif

ERROR:

        MP4PlayerCorePtr[intArg]->execendflag = 1;
        iMlibRet = MP4DMXFW_End( pMlibHandle, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_End Failed. ret = %d\n", iMlibRet );
        }

        MP4PlayerCorePtr[intArg]->vthread_end = 1;
        MP4PlayerCorePtr[intArg]->athread_end = 1;

        while(1)
        {
            if (vendflag[intArg] && aendflag[intArg])
            {
                break;
            }
            OSYieldThread();
        }

        // video exit
        VideoExit(intArg);

        // audio exit
        if (MP4PlayerCorePtr[intArg]->AudioSampleRate != 0)
        {
            AudioExit(intArg);
        }

        iMlibRet = MP4DMXFW_Close( ExpHeap, pMlibHandle, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_Close Failed. ret = %d\n", iMlibRet );
        }

        OSReport("MP4Play[%d] Thread End\n", intArg);

        // memory free
        MediaFileReadFree(intArg);
        if (MP4DemuxCorePtr[intArg]->VideoTrackFound)
        {
            MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->StreamRingBufPtrV);
        }
        if (MP4DemuxCorePtr[intArg]->AudioTrackFound)
        {
            MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->StreamRingBufPtrA);
        }
        MEMDestroyExpHeap(ExpHeap);
        MEMFreeToDefaultHeap(addr);

        // file hendle close
        LoopCounter[intArg]++;
        OSReport("LoopCounter[%d]:%d\n", intArg, LoopCounter[intArg]);
        if (MP4PlayerCorePtr[intArg]->file_input_mode == 0)
        {
            FSCloseFile(GpClient[intArg], GpCmd[intArg], Gfh[intArg], FS_RET_NO_ERROR);
        }
    }

    MEMFreeToDefaultHeap(GpClient[intArg]);
    MEMFreeToDefaultHeap(GpCmd[intArg]);

    MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->streamFullBuffer);
    // FS delete
    if (MP4PlayerCorePtr[intArg]->file_input_mode == 1)
    {
        FSCloseFile(GpClient[intArg], GpCmd[intArg], Gfh[intArg], FS_RET_NO_ERROR);
    }
    FSDelClient(GpClient[intArg], FS_RET_NO_ERROR);

#ifdef USE_PROCESS_SWITCHING
    threadabort[intArg][0] = 1;
    threadabort[intArg][1] = 1;
    threadabort[intArg][2] = 1;
    CoreDecodeEnd[intArg]  = TRUE;
#endif

#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
    while (1)
    {
        // ------------------------------- //
        // beginning of process switch detect
        // ------------------------------- //
        static BOOL            ok;

        // Memory for VPAD reads
        s32 vpadErr;

        if (CoreProcessEnd == TRUE)
        {
            break;
        }

        if (CoreDecodeActive[intArg] == FALSE)
        {
#if TEST_MODE == 1
            threadabort[0][2] = 1;
#elif TEST_MODE == 2
            threadabort[1][2] = 1;
#else
            threadabort[0][2] = 1;
            threadabort[1][2] = 1;
#endif

            OSResetEvent(&gAcquired_[intArg]);
            OSSignalEvent(&gDoRelease_[intArg]);

            VPADShutdown();

            CoreDecodeSleep[intArg] = TRUE;
            OSReleaseForeground();
            inForeground_[intArg] = FALSE;

        }else if (inForeground_[intArg]){
            // get input / do ai + physics, etc
            DEMOPadRead();

            VPADRead(0, &s_vpads[intArg][0][0], VPAD_MAX_READ_BUFS, &vpadErr);

            // check for HBM press+release
            if (DEMOPadGetButtonDown(0) & DEMO_PAD_BUTTON_START)
                debounce_[intArg] = 1;
            else if (s_vpads[intArg][0][0].release & VPAD_BUTTON_HOME)
                debounce_[intArg] = 1;
            else if (debounce_[intArg] && debounce)
            {
                debounce_[intArg] = 0;
                OSReport("\nSwitch To HBM!\n");
                ok = OSSendAppSwitchRequest(PFID_HomeButtonMenu, (void *)"Pause", 6);
                if (!ok)
                {
                    OSReport("OSSendAppSwitchRequest() failed.\n");
                }
                else
                    OSReport("Sent Request ok.\n\n");
            }
        }
        // ---------------------------- //
        // end of process switch detect
        // ---------------------------- //
        while(!inForeground_[intArg])
        {
            if (inForeground)
            {
               inForeground_[intArg] = TRUE;
               CoreDecodeSleep[intArg] = FALSE;

               OSResetEvent(&gDoRelease_[intArg]);
               OSSignalEvent(&gAcquired_[intArg]);

#if TEST_MODE == 1
                threadabort[0][2] = 0;
#elif TEST_MODE == 2
                threadabort[1][2] = 0;
#else
                threadabort[0][2] = 0;
                threadabort[1][2] = 0;
#endif
            }
            OSSleepMilliseconds(10);
        }
    }
#endif

    return(0);
}


#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
/*-------------------------------------------------------------------------*
    Name:           MP4PlayDRC
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static s32 MP4PlayDRC(s32 intArg, void *ptrArg)
{
    MEMHeapHandle   defaultHeap;
    // Memory Variables
    MEMHeapHandle       ExpHeap;
    FSStatus    status;
    FSStat      stat;
    void        *addr;
    u32         size;
    s32         i;

    s32     iMlibRet;
    void    *pMlibHandle=NULL;
    s32     UseWorkMemSize;

    static VPADStatus s_vpads[2][VPAD_MAX_CONTROLLERS][VPAD_MAX_READ_BUFS];

    MP4PlayerCorePtr[intArg] = &MP4PlayerCore1[intArg];
    MP4PlayerCorePtr[intArg]->InputFileSize = 0;

    // allocate memory to store the input data
    MP4PlayerCorePtr[intArg]->streamFullBuffer = (u8 *)MEMAllocFromDefaultHeapEx(FILEMEMORYSIZE, 64);

    // Allocate buffers.
    GpClient[intArg] = MEMAllocFromDefaultHeap(sizeof(FSClient));
    if (!GpClient[intArg])
    {
        OSHalt("Error: cannot allocate memory for fs client.\n");
    }
    GpCmd[intArg]    = MEMAllocFromDefaultHeap(sizeof(FSCmdBlock));
    if (!GpCmd[intArg])
    {
        OSHalt("Error: cannot allocate memory for command block.\n");
    }
    // Add client to FS.
    FSAddClient(GpClient[intArg], FS_RET_NO_ERROR);

    OSReport("\n\n\n### Start operation ###\n");

    // Init command block.
    FSInitCmdBlock(GpCmd[intArg]);
    OSReport("==> FSInitCmdBlock: Command block initialized.\n");

#ifdef INPUTNAME_DEFINED
    status = FSOpenFile(GpClient[intArg], GpCmd[intArg], (const char *)mp4Filename[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#else
    status = FSOpenFile(GpClient[intArg], GpCmd[intArg], (const char *)fileName[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#endif
    if(status < FS_STATUS_OK)
    {
        OSReport("[ERROR] cannot open mp4 file.\n");
        OSHalt("OS Halt");
    }

#ifdef INPUTNAME_DEFINED
    status = FSGetStat(GpClient[intArg], GpCmd[intArg], mp4Filename[intArg], &stat, 0);
#else
    status = FSGetStat(GpClient[intArg], GpCmd[intArg], fileName[intArg], &stat, 0);
#endif
    if (status < FS_STATUS_OK)
    {
        OSReport("[ERROR] cannot get input mp4 file status.\n");
        OSHalt("OS Halt");
    }

    MP4PlayerCorePtr[intArg]->InputFileSize = stat.size;
    if (MP4PlayerCorePtr[intArg]->InputFileSize > FILEMEMORYSIZE)
    {
        MP4PlayerCorePtr[intArg]->file_input_mode = 0;    // file input
        FSCloseFile(GpClient[intArg], GpCmd[intArg], Gfh[intArg], FS_RET_NO_ERROR);
    }
    else
    {
        MP4PlayerCorePtr[intArg]->file_input_mode = 1;    // memory input
        status = FSReadFile(
                        GpClient[intArg],
                        GpCmd[intArg],
                        (void*)MP4PlayerCorePtr[intArg]->streamFullBuffer,
                        sizeof(u8),
                        MP4PlayerCorePtr[intArg]->InputFileSize,
                        Gfh[intArg],
                        0,
                        FS_RET_NO_ERROR);
        if(status < FS_STATUS_OK)
        {
            return 0;
        }
    }

    while (1)
    {
        OSReport("MP4Play[%d] Thread Start\n", intArg);
        if (MP4PlayerCorePtr[intArg]->file_input_mode == 0)
        {
#ifdef INPUTNAME_DEFINED
            status = FSOpenFile(GpClient[intArg], GpCmd[intArg], mp4Filename[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#else
            status = FSOpenFile(GpClient[intArg], GpCmd[intArg], fileName[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
#endif
            if(status < FS_STATUS_OK)
            {
                OSReport("[ERROR] cannot open mp4 file.\n");
                OSHalt("OS Halt");
            }
        }

        vendflag[intArg] = 0;
        aendflag[intArg] = 0;
        sys_timestart[intArg] = 0;
        sys_basetime[intArg] = 0;

        MP4PlayerCorePtr[intArg]->df_v = 0;
        MP4PlayerCorePtr[intArg]->ff_v = 0;
        MP4PlayerCorePtr[intArg]->df_a = 0;
        MP4PlayerCorePtr[intArg]->ff_a = 0;
        MP4PlayerCorePtr[intArg]->vthread_end = 0;
        MP4PlayerCorePtr[intArg]->athread_end = 0;
        MP4PlayerCorePtr[intArg]->execendflag = 0;
        MP4PlayerCorePtr[intArg]->voutfound = 0;
        MP4PlayerCorePtr[intArg]->aoutfound = 0;

        MP4PlayerCorePtr[intArg]->FrameSkipFlag = 0;
        MP4PlayerCorePtr[intArg]->AudioFirstFlag = 1;
        MP4PlayerCorePtr[intArg]->video_fsync_comp = 1;
        MP4PlayerCorePtr[intArg]->audio_fsync_comp = 1;
        MP4PlayerCorePtr[intArg]->TotalReadFileSize = 0;
        MP4PlayerCorePtr[intArg]->AudioSampleBytePerFrame = 0;
        MP4PlayerCorePtr[intArg]->AudioLastBufferInit = 0;

        // MP4DMX Heap Area Allocation
        defaultHeap = MEMGetBaseHeapHandle(MEM_ARENA_2);            /* initialize Exp Heap on MEM2 */
        size = MEMGetAllocatableSizeForExpHeapEx(defaultHeap, 1024);
        addr = MEMAllocFromDefaultHeapEx(size/32, 1024);
        if (!addr)
        {
            OSReport("[ERROR] cannot allocate memory.\n");
            OSHalt("OS Halt");
        }

        // set the heap area
        ExpHeap = MEMCreateExpHeap(addr, size/32);

        MediaFileReadInit(intArg);

        // Set CallBack Parameters
        MP4PlayerCorePtr[intArg]->MP4DMUXParam.MP4DMXFW_CallbackSetData = (void *)cbSetMediaContainerData;
        MP4PlayerCorePtr[intArg]->MP4DMUXParam.MP4DMXFW_CallbackGetData = (void *)cbGetMediaSampleData;

        iMlibRet = MP4DMXFW_Open(ExpHeap, &pMlibHandle, &UseWorkMemSize, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXOpen Failed. ret = %d\n", iMlibRet );
            goto ERROR;
        }

        iMlibRet = MP4DMXFW_Begin( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_Begin Failed. ret = %d\n", iMlibRet );
            goto ERROR;
        }

        if (!MP4DemuxCorePtr[intArg]->VideoTrackFound)
        {
            threadabort[intArg][0] = 1;
        }
        if (!MP4DemuxCorePtr[intArg]->AudioTrackFound)
        {
            threadabort[intArg][1] = 1;
        }

        // allocate video ringbuffers
        if (MP4DemuxCorePtr[intArg]->VideoTrackFound)
        {
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV = (MP4DemuxCorePtr[intArg]->mp4VideoTrackInf.maxbitrate >> 3);
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV = (MP4PlayerCorePtr[intArg]->StreamRingBufSizeV * 3) >> 1;     // margin
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV += (1024 * VIDEO_BUFFER_NUM/2);                                // margin
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeV += H264DEC_AVCHEADER_SIZE;                                     // max sps/pps size
            MP4PlayerCorePtr[intArg]->StreamRingBufPtrV = (u8 *)MEMAllocFromDefaultHeapEx(MP4PlayerCorePtr[intArg]->StreamRingBufSizeV, 1024);
            MP4PlayerCorePtr[intArg]->StreamRingBufPosV = 0;             // buffer position initialize
        }

        // allocate audio ringbuffers
        if (MP4DemuxCorePtr[intArg]->AudioTrackFound)
        {
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeA = ((MP4DemuxCorePtr[intArg]->mp4AudioTrackInf.maxbitrate >> 3) * 5);    // audio buffer size plus 5sec bitstream size
            MP4PlayerCorePtr[intArg]->StreamRingBufSizeA += (1024 * AUDIO_BUFFER_NUM/2);                                          // margin
            MP4PlayerCorePtr[intArg]->StreamRingBufPtrA = (u8 *)MEMAllocFromDefaultHeapEx(MP4PlayerCorePtr[intArg]->StreamRingBufSizeA, 1024);
            MP4PlayerCorePtr[intArg]->StreamRingBufPosA = 0;             // buffer position initialize
        }

        for (i = 0; i < AUDIO_BUFFER_NUM; i++)
        {
            MP4PlayerCorePtr[intArg]->OutputAudioInfo[i].PTS  = 0;
            MP4PlayerCorePtr[intArg]->OutputAudioInfo[i].Size = 0;
            MP4PlayerCorePtr[intArg]->OutputAudioInfo[i].Status = 0;
        }

        exc_start_time_stamp[intArg] = 0;
        exc_end_time_stamp[intArg]   = 0;
        OSReport("MP4Duration[1]:%d\n", MP4DemuxCorePtr[intArg]->MP4Duration);
        for (i = 0; i < MP4DemuxCorePtr[intArg]->MP4Duration/100; i++)
        {
            exc_end_time_stamp[intArg] = exc_start_time_stamp[intArg] + 100;
            iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 0, (s64)exc_start_time_stamp[intArg], (s64)exc_end_time_stamp[intArg], intArg );
            if( iMlibRet != MP4DMXFW_RET_SUCCESS )
            {
                OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
                goto ERROR;
            }

            {
                // ------------------------------- //
                // beginning of process switch detect
                // ------------------------------- //
                static BOOL            ok;

                // Memory for VPAD reads
                s32 vpadErr;

                {
                    if (CoreDecodeActive[intArg] == FALSE)
                    {
#if TEST_MODE == 1
                        threadabort[0][2] = 1;
#elif TEST_MODE == 2
                        threadabort[1][2] = 1;
#else
                        threadabort[0][2] = 1;
                        threadabort[1][2] = 1;
#endif

                        OSResetEvent(&gAcquired_[intArg]);
                        OSSignalEvent(&gDoRelease_[intArg]);

                        VPADShutdown();

                        CoreDecodeSleep[intArg] = TRUE;
                        OSReleaseForeground();
                        inForeground_[intArg] = FALSE;

                    }else if (inForeground_[intArg]){
                        // get input / do ai + physics, etc
                        DEMOPadRead();

                        VPADRead(0, &s_vpads[intArg][0][0], VPAD_MAX_READ_BUFS, &vpadErr);

                        // check for HBM press+release
                        if (DEMOPadGetButtonDown(0) & DEMO_PAD_BUTTON_START)
                            debounce_[intArg] = 1;
                        else if (s_vpads[intArg][0][0].release & VPAD_BUTTON_HOME)
                            debounce_[intArg] = 1;
                        else if (debounce_[intArg] && debounce)
                        {
                            debounce_[intArg] = 0;
                            OSReport("\nSwitch To HBM!\n");
                            ok = OSSendAppSwitchRequest(PFID_HomeButtonMenu, (void *)"Pause", 6);
                            if (!ok)
                            {
                                OSReport("OSSendAppSwitchRequest() failed.\n");
                            }
                            else
                                OSReport("Sent Request ok.\n\n");
                        }
                    }
                }
                // ---------------------------- //
                // end of process switch detect
                // ---------------------------- //
                while(!inForeground_[intArg])
                {
                    if (inForeground)
                    {
                       inForeground_[intArg] = TRUE;
                       CoreDecodeSleep[intArg] = FALSE;

                       OSResetEvent(&gDoRelease_[intArg]);
                       OSSignalEvent(&gAcquired_[intArg]);

#if TEST_MODE == 1
                        threadabort[0][2] = 0;
#elif TEST_MODE == 2
                        threadabort[1][2] = 0;
#else
                        threadabort[0][2] = 0;
                        threadabort[1][2] = 0;
#endif
                    }
                    OSSleepMilliseconds(10);
                }
            }
        }

ERROR:

        MP4PlayerCorePtr[intArg]->execendflag = 1;
        iMlibRet = MP4DMXFW_End( pMlibHandle, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_End Failed. ret = %d\n", iMlibRet );
        }

        MP4PlayerCorePtr[intArg]->vthread_end = 1;
        MP4PlayerCorePtr[intArg]->athread_end = 1;

        while(1)
        {
            if (vendflag[intArg] && aendflag[intArg])
            {
                break;
            }
            OSYieldThread();
        }

        // video exit
        VideoExit(intArg);

        // audio exit
        if (MP4PlayerCorePtr[intArg]->AudioSampleRate != 0)
        {
            AudioExit(intArg);
        }

        iMlibRet = MP4DMXFW_Close( ExpHeap, pMlibHandle, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_Close Failed. ret = %d\n", iMlibRet );
        }

        OSReport("MP4Play[%d] Thread End\n", intArg);

        // memory free
        MediaFileReadFree(intArg);
        if (MP4DemuxCorePtr[intArg]->VideoTrackFound)
        {
            MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->StreamRingBufPtrV);
        }
        if (MP4DemuxCorePtr[intArg]->AudioTrackFound)
        {
            MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->StreamRingBufPtrA);
        }
        MEMDestroyExpHeap(ExpHeap);
        MEMFreeToDefaultHeap(addr);

        // file hendle close
        LoopCounter[intArg]++;
        OSReport("LoopCounter[%d]:%d\n", intArg, LoopCounter[intArg]);
        if (MP4PlayerCorePtr[intArg]->file_input_mode == 1)
        {
            FSCloseFile(GpClient[intArg], GpCmd[intArg], Gfh[intArg], FS_RET_NO_ERROR);
        }
    }

    MEMFreeToDefaultHeap(GpClient[intArg]);
    MEMFreeToDefaultHeap(GpCmd[intArg]);

    MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->streamFullBuffer);
    // FS delete
    if (MP4PlayerCorePtr[intArg]->file_input_mode == 1)
    {
        FSCloseFile(GpClient[intArg], GpCmd[intArg], Gfh[intArg], FS_RET_NO_ERROR);
    }
    FSDelClient(GpClient[intArg], FS_RET_NO_ERROR);

#ifdef USE_PROCESS_SWITCHING
    threadabort[intArg][0] = 1;
    threadabort[intArg][1] = 1;
    threadabort[intArg][2] = 1;
    CoreDecodeEnd[intArg]  = TRUE;
#endif

#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
    while (1)
    {
        // ------------------------------- //
        // beginning of process switch detect
        // ------------------------------- //
        static BOOL            ok;

        // Memory for VPAD reads
        s32 vpadErr;

        if (CoreProcessEnd == TRUE)
        {
            break;
        }

        if (CoreDecodeActive[intArg] == FALSE)
        {
#if TEST_MODE == 1
            threadabort[0][2] = 1;
#elif TEST_MODE == 2
            threadabort[1][2] = 1;
#else
            threadabort[0][2] = 1;
            threadabort[1][2] = 1;
#endif

            OSResetEvent(&gAcquired_[intArg]);
            OSSignalEvent(&gDoRelease_[intArg]);

            VPADShutdown();

            CoreDecodeSleep[intArg] = TRUE;
            OSReleaseForeground();
            inForeground_[intArg] = FALSE;

        }else if (inForeground_[intArg]){
            // get input / do ai + physics, etc
            DEMOPadRead();

            VPADRead(0, &s_vpads[intArg][0][0], VPAD_MAX_READ_BUFS, &vpadErr);

            // check for HBM press+release
            if (DEMOPadGetButtonDown(0) & DEMO_PAD_BUTTON_START)
                debounce_[intArg] = 1;
            else if (s_vpads[intArg][0][0].release & VPAD_BUTTON_HOME)
                debounce_[intArg] = 1;
            else if (debounce_[intArg] && debounce)
            {
                debounce_[intArg] = 0;
                OSReport("\nSwitch To HBM!\n");
                ok = OSSendAppSwitchRequest(PFID_HomeButtonMenu, (void *)"Pause", 6);
                if (!ok)
                {
                    OSReport("OSSendAppSwitchRequest() failed.\n");
                }
                else
                    OSReport("Sent Request ok.\n\n");
            }
        }
        // ---------------------------- //
        // end of process switch detect
        // ---------------------------- //
        while(!inForeground_[intArg])
        {
            if (inForeground)
            {
               inForeground_[intArg] = TRUE;
               CoreDecodeSleep[intArg] = FALSE;

               OSResetEvent(&gDoRelease_[intArg]);
               OSSignalEvent(&gAcquired_[intArg]);

#if TEST_MODE == 1
                threadabort[0][2] = 0;
#elif TEST_MODE == 2
                threadabort[1][2] = 0;
#else
                threadabort[0][2] = 0;
                threadabort[1][2] = 0;
#endif
            }
            OSSleepMilliseconds(10);
        }
    }
#endif

    return(0);
}
#endif


#if defined(USE_SINGLE_CORE)
#if defined(USE_PROCESS_SWITCHING)

#pragma ghs nowarning 111
static
int sCore0Main(int intArg, void *ptrArg)
{
    do {
        /* wait for main core to release */
        OSWaitEvent(&gDoRelease);

        /* now do foreground release */
        OSReleaseForeground();

        /* wait for us to get the foreground again */
        OSWaitEvent(&gAcquired);
    } while (1);

    return 0;
}

static
int sCore2Main(int intArg, void *ptrArg)
{
    do {
        /* wait for main core to release */
        OSWaitEvent(&gDoRelease);

        /* now do foreground release */
        OSReleaseForeground();

        /* wait for us to get the foreground again */
        OSWaitEvent(&gAcquired);
    } while (1);

    return 0;
}

#pragma ghs endnowarning 111

#endif
#endif


/*-------------------------------------------------------------------------*
    Name:           main
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
s32 main(s32 argc, s8* argv[])
{
    s32 initargc = 2;
    s8* initargv[] = {"DEMO_CB_FORMAT 8_8_8_8", "DEMO_SCAN_FORMAT 8_8_8_8"};
#ifdef USE_PROCESS_SWITCHING
    static VPADStatus s_vpads[VPAD_MAX_CONTROLLERS][VPAD_MAX_READ_BUFS];
#endif

    //=====================================================================
    // Demo Setup
    //=====================================================================

#ifdef PROFILE_ENABLE
    BOOL profInitResult; void *buffer = MEMAllocFromDefaultHeap(PROFILER_MINBUFFERSIZE);
    PROFILERInitialize(buffer, PROFILER_MINBUFFERSIZE);
    PROFILERSetDefaultProfileSettings(0, PROFILER_SETTINGS_FLAGS_CALLSTACK, 0, PROFILERSampleRate_100x);
    PROFILERStart();
#endif

#ifndef INPUTNAME_DEFINED
    /* get the input file name */
    if (argc != 3)
    {
        OSReport("[ERROR] please set input_file name.\n");
        OSReport("[Usage] caferun mp4demux_movie.elf input_filename_for_TV input_filename_for_DRC\n");
        return DEMOTestResult();
    }
    else
    {
        strncpy(fileName[0], argv[1], 1023);
        fileName[0][1023] = '\0';
        OSReport("TV file name:%s\n", argv[1]);
        strncpy(fileName[1], argv[2], 1023);
        fileName[1][1023] = '\0';
        OSReport("DRC file name:%s\n", argv[2]);
    }
#endif

#ifdef INPUTNAME_DEFINED
    mp4Filename[0] = MP4_INPUT_SAMPLE1;     // set input file name
    mp4Filename[1] = MP4_INPUT_SAMPLE2;     // set input file name
#endif
    // give the system a few seconds to get ready
    OSSleepSeconds(5);

    DEMOInit();
    DEMOTestInit(argc, (char **)argv);
#ifdef USE_PROCESS_SWITCHING
    DEMOPadInit();
    VPADInit();
#endif
    DEMOGfxInit(initargc, (char **)initargv);
    DEMODRCInit(argc, (char **)argv);
    DEMOFontInit();
    FSInit();

    InitShader();
    InitAttribData();

#ifdef USE_PROCESS_SWITCHING
    pSysQueue = OSGetSystemMessageQueue();

    /* init switching signals */
    OSInitEvent(&gDoRelease, FALSE, OS_EVENT_MANUAL);
    OSInitEvent(&gAcquired, FALSE, OS_EVENT_MANUAL);
    OSInitEvent(&gDoRelease_[0], FALSE, OS_EVENT_MANUAL);
    OSInitEvent(&gAcquired_[0], FALSE, OS_EVENT_MANUAL);
    OSInitEvent(&gDoRelease_[1], FALSE, OS_EVENT_MANUAL);
    OSInitEvent(&gAcquired_[1], FALSE, OS_EVENT_MANUAL);
#ifdef USE_SINGLE_CORE
    OSRunThread(OSGetDefaultThread(0), sCore0Main, 0, NULL);
    OSRunThread(OSGetDefaultThread(2), sCore2Main, 0, NULL);
    OSReport("Core0:dummy\n");
    OSReport("Core1:MP4Player Thread\n");
    OSReport("Core2:dummy\n");
#else
#if TEST_MODE == 1
    OSRunThread(OSGetDefaultThread(2), sCore2Main, 0, NULL);
    OSReport("Core0:MP4Player[TV] Thread\n");
    OSReport("Core1:Video Render & Audio Control Thread\n");
    OSReport("Core2:dummy\n");
#elif TEST_MODE == 2
    OSRunThread(OSGetDefaultThread(0), sCore0Main, 0, NULL);
    OSReport("Core0:dummy\n");
    OSReport("Core1:Video Render & Audio Control Thread\n");
    OSReport("Core2:MP4Player[DRC] Thread\n");
#else
    OSReport("Core0:MP4Player[TV] Thread\n");
    OSReport("Core1:Video Render & Audio Control Thread\n");
    OSReport("Core2:MP4Player[DRC] Thread\n");
#endif
#endif

#endif

    vendflag[0] = 0;
    aendflag[0] = 0;
    sys_timestart[0] = 0;
    sys_basetime[0] = 0;
    vendflag[1] = 0;
    aendflag[1] = 0;
    sys_timestart[1] = 0;
    sys_basetime[1] = 0;
    LoopCounter[0] = 0;
    LoopCounter[1] = 0;

    // Create the video thread.
    OSCreateThread( &Thread[0],   // ptr to the thread to init
                    VideoOutputThread,              // ptr to the start routine
                    0,                              // params passed to start routine
                    NULL,
                    ThreadStack[0] + STACK_SIZE,    // initial stack address
                    STACK_SIZE,                     // stack size
                    16,                             // scheduling priority
                    0);         // detached

    // Create the audio thread.
    OSCreateThread( &Thread[1],   // ptr to the thread to init
                    AudioOutputThread,              // ptr to the start routine
                    0,                              // params passed to start routine
                    NULL,
                    ThreadStack[1] + STACK_SIZE,    // initial stack address
                    STACK_SIZE,                     // stack size
                    16,                             // scheduling priority
                    0);         // detached

    OSResumeThread(&Thread[0]);
    OSResumeThread(&Thread[1]);

#ifdef USE_PROCESS_SWITCHING
    debounce = 0;
    debounce_[0] = 0;
    debounce_[1] = 0;
    inForeground = TRUE;
    inForeground_[0] = TRUE;
    inForeground_[1] = TRUE;
    process_sleep_time = 0;
    threadabort[0][0] = threadabort[0][1] = threadabort[0][2] = 0;
    threadabort[1][0] = threadabort[1][1] = threadabort[1][2] = 0;
    CoreDecodeActive[0] = TRUE;
    CoreDecodeActive[1] = TRUE;
    CoreDecodeSleep[0] = FALSE;
    CoreDecodeSleep[1] = FALSE;
    CoreDecodeEnd[0] = FALSE;
    CoreDecodeEnd[1] = FALSE;
    CoreProcessEnd = FALSE;
#endif

    // initialize audio system and MIXer application
    AXInit();
    AXSetMode(AX_MODE_STEREO);

    // You do not need to do these two statements
    // if you are to use only the DSP mixer
//        __AXMixInit(AXMIX_DSP_ENABLE|AXMIX_PPC_ENABLE);
    AXSetDefaultMixerSelect(AX_PB_MIXER_SELECT_DSP);

    MIXInit();
    MIXSetSoundMode(MIX_SOUND_MODE_STEREO);

    //=====================================================================
    // Demo Start
    //=====================================================================

#if !defined(USE_PROCESS_SWITCHING) || defined(USE_SINGLE_CORE)
#if TEST_MODE == 1
    // Create the play thread.
    OSCreateThread( &Thread[2],   // ptr to the thread to init
                    MP4PlayTVorDRC,                 // ptr to the start routine
                    0,                              // params passed to start routine
                    NULL,
                    ThreadStack[2] + STACK_SIZE,    // initial stack address
                    STACK_SIZE,                     // stack size
                    16,                             // scheduling priority
                    0);         // detached
#elif TEST_MODE == 2
    // Create the play thread.
    OSCreateThread( &Thread[3],   // ptr to the thread to init
                    MP4PlayTVorDRC,                 // ptr to the start routine
                    1,                              // params passed to start routine
                    NULL,
                    ThreadStack[3] + STACK_SIZE,    // initial stack address
                    STACK_SIZE,                     // stack size
                    16,                             // scheduling priority
                    0);         // detached
#else
    // Create the play thread.
    OSCreateThread( &Thread[2],   // ptr to the thread to init
                    MP4PlayTVorDRC,                 // ptr to the start routine
                    0,                              // params passed to start routine
                    NULL,
                    ThreadStack[2] + STACK_SIZE,    // initial stack address
                    STACK_SIZE,                     // stack size
                    16,                             // scheduling priority
                    0);         // detached
    // Create the play thread.
    OSCreateThread( &Thread[3],   // ptr to the thread to init
                    MP4PlayTVorDRC,                 // ptr to the start routine
                    1,                              // params passed to start routine
                    NULL,
                    ThreadStack[3] + STACK_SIZE,    // initial stack address
                    STACK_SIZE,                     // stack size
                    16,                             // scheduling priority
                    0);         // detached
#endif
#endif

    // Start the play thread.
#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
#if TEST_MODE == 1
    OSRunThread(OSGetDefaultThread(0), MP4PlayTVorDRC,  0, NULL);
#elif TEST_MODE == 2
    OSRunThread(OSGetDefaultThread(2), MP4PlayDRC, 1, NULL);
#else
    OSRunThread(OSGetDefaultThread(0), MP4PlayTVorDRC,  0, NULL);
    OSRunThread(OSGetDefaultThread(2), MP4PlayDRC, 1, NULL);
#endif
#else
#if TEST_MODE == 1
    OSResumeThread(&Thread[2]);
#elif TEST_MODE == 2
    OSResumeThread(&Thread[3]);
#else
    OSResumeThread(&Thread[2]);
    OSResumeThread(&Thread[3]);
#endif
#endif

    // thread finish waitting
    while (1)
    {
#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
#if TEST_MODE == 1
        if ((CoreDecodeEnd[0]==TRUE))
#elif TEST_MODE == 2
        if ((CoreDecodeEnd[1]==TRUE))
#else
        if ((CoreDecodeEnd[0]==TRUE) && 
            (CoreDecodeEnd[1]==TRUE))
#endif
#else
#if TEST_MODE == 1
        if ((OSIsThreadTerminated(&Thread[2])==TRUE))
#elif TEST_MODE == 2
        if ((OSIsThreadTerminated(&Thread[3])==TRUE))
#else
        if ((OSIsThreadTerminated(&Thread[2])==TRUE) && 
            (OSIsThreadTerminated(&Thread[3])==TRUE))
#endif
#endif
        {
            break;
        }

#ifdef USE_PROCESS_SWITCHING
        {
            // ------------------------------- //
            // beginning of process switch detect
            // ------------------------------- //
            static OSMessage       msg;
            static BOOL            ok;
            static s32 starttime, endtime;

            // Memory for VPAD reads
            s32 vpadErr;
            {
                if (OSReceiveMessage(pSysQueue, &msg, OS_MESSAGE_NOBLOCK))
                {
                    if (msg.data0 == OS_SYSTEM_MESSAGE_DATA0_RELEASE_FOREGROUND)
                    {
#ifndef USE_SINGLE_CORE
                        CoreDecodeActive[0] = FALSE;
                        CoreDecodeActive[1] = FALSE;
#if TEST_MODE == 1
                        while (CoreDecodeSleep[0] == FALSE);
#elif TEST_MODE == 2
                        while (CoreDecodeSleep[1] == FALSE);
#else
                        while ((CoreDecodeSleep[0] == FALSE) || (CoreDecodeSleep[1] == FALSE));
#endif
                        inForeground = FALSE;
                        starttime = OSTicksToMilliseconds(OSGetTime());
#if TEST_MODE == 1
                        while (!threadabort[0][0] || !threadabort[0][1])
                        {
                            OSYieldThread();
//                            OSReport("threadabort[0][0]:%d, threadabort[0][1]:%d\n", threadabort[0][0], threadabort[0][1]);
                        }
                        AudioProcessPause(0);
#elif TEST_MODE == 2
                        while (!threadabort[1][0] || !threadabort[1][1])
                        {
                            OSYieldThread();
//                            OSReport("threadabort[1][0]:%d, threadabort[1][1]:%d\n", threadabort[1][0], threadabort[1][1]);
                        }
                        AudioProcessPause(1);
#else
                        while ((!threadabort[0][0] && !threadabort[1][0]) || (!threadabort[0][1] && !threadabort[1][1]))
                        {
                            OSYieldThread();
//                            OSReport("threadabort[0][0]:%d, threadabort[0][1]:%d, threadabort[1][0]:%d, threadabort[1][1]:%d\n", threadabort[0][0], threadabort[0][1], threadabort[1][0], threadabort[1][1]);
                        }
                        AudioProcessPause(0);
                        AudioProcessPause(1);
#endif
#else
                        inForeground = FALSE;
                        starttime = OSTicksToMilliseconds(OSGetTime());
#if TEST_MODE == 1
                        while (!threadabort[0][0] || !threadabort[0][1] || !threadabort[0][2])
                        {
                            OSYieldThread();
//                            OSReport("threadabort[0][0]:%d, threadabort[0][1]:%d, threadabort[0][2]:%d\n", threadabort[0][0], threadabort[0][1], threadabort[0][2]);
                        }
                        AudioProcessPause(0);
#elif TEST_MODE == 2
                        while (!threadabort[1][0] || !threadabort[1][1] || !threadabort[1][2])
                        {
                            OSYieldThread();
//                            OSReport("threadabort[1][0]:%d, threadabort[1][1]:%d, threadabort[1][2]:%d\n", threadabort[1][0], threadabort[1][1], threadabort[1][2]);
                        }
                        AudioProcessPause(1);
#else
                        while ((!threadabort[0][0] && !threadabort[1][0]) || (!threadabort[0][1] && !threadabort[1][1]) || !threadabort[0][2] || !threadabort[1][2])
                        {
                            OSYieldThread();
//                            OSReport("threadabort[0][0]:%d, threadabort[0][1]:%d, threadabort[0][2]:%d, threadabort[1][0]:%d, threadabort[1][1]:%d, threadabort[1][2]:%d\n",
//                                threadabort[0][0], threadabort[0][1], threadabort[0][2], threadabort[1][0], threadabort[1][1], threadabort[1][2]);
                        }
                        AudioProcessPause(0);
                        AudioProcessPause(1);
#endif
#endif
                        OSResetEvent(&gAcquired);
                        OSSignalEvent(&gDoRelease);
                        DEMODRCReleaseForeground();
                        DEMOGfxReleaseForeground();
                        VPADShutdown();
                        OSSavesDone_ReadyToRelease();
                        OSReleaseForeground();
                        OSSleepMilliseconds(10);
                    }
                    else if (msg.data0 == OS_SYSTEM_MESSAGE_DATA0_EXIT)
                    {
                        OSReport("Received request to Exit from Kernel\n");
                        DEMOStopRunning();
                    }
                }else if (inForeground){
                    // get input / do ai + physics, etc
                    DEMOPadRead();

                    VPADRead(0, &s_vpads[0][0], VPAD_MAX_READ_BUFS, &vpadErr);

                    // check for HBM press+release
                    if (DEMOPadGetButtonDown(0) & DEMO_PAD_BUTTON_START)
                        debounce = 1;
                    else if (s_vpads[0][0].release & VPAD_BUTTON_HOME)
                        debounce = 1;
#ifndef USE_SINGLE_CORE
                    else if (debounce && debounce_[0] && debounce_[1])
#else
                    else if (debounce)
#endif
                    {
                        debounce = 0;
                        OSReport("\nSwitch To HBM!\n");
                        ok = OSSendAppSwitchRequest(PFID_HomeButtonMenu, (void *)"Pause", 6);
                        if (!ok)
                        {
                            OSReport("OSSendAppSwitchRequest() failed.\n");
                        }
                        else
                            OSReport("Sent Request ok.\n\n");
                    }
                }
            }
            // ---------------------------- //
            // end of process switch detect
            // ---------------------------- //
            OSYieldThread();

            while(!inForeground)
            {
                if (OSReceiveMessage(pSysQueue, &msg, OS_MESSAGE_NOBLOCK))
                {
                    if (msg.data0 == OS_SYSTEM_MESSAGE_DATA0_ACQUIRED_FOREGROUND)
                    {
                        VPADInit();
                        DEMOGfxAcquiredForeground();
                        DEMODRCAcquiredForeground();

                        DEMOGfxSetContextState();
                        InitShader();
                        InitAttribData();

                        OSResetEvent(&gDoRelease);
                        OSSignalEvent(&gAcquired);

                        endtime = OSTicksToMilliseconds(OSGetTime());
                        process_sleep_time = endtime - starttime;
                        sys_basetime[0] += process_sleep_time;
                        sys_basetime[1] += process_sleep_time;

#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
#if TEST_MODE == 1
                        if (CoreDecodeEnd[0]==FALSE)
                        {
                            AudioProcessReStart(0);
                        }
#elif TEST_MODE == 2
                        if (CoreDecodeEnd[1]==FALSE)
                        {
                            AudioProcessReStart(1);
                        }
#else
                        if (CoreDecodeEnd[0]==FALSE)
                        {
                            AudioProcessReStart(0);
                        }
                        if (CoreDecodeEnd[1]==FALSE)
                        {
                            AudioProcessReStart(1);
                        }
#endif
#else
#if TEST_MODE == 1
                        AudioProcessReStart(0);
#elif TEST_MODE == 2
                        AudioProcessReStart(1);
#else
                        AudioProcessReStart(0);
                        AudioProcessReStart(1);
#endif
#endif

#ifndef USE_SINGLE_CORE
                        CoreDecodeActive[0] = TRUE;
                        CoreDecodeActive[1] = TRUE;
#endif
                        inForeground = TRUE;
                    }
                }
            }
        }
#endif
        OSYieldThread();
    }

    //=====================================================================
    // Demo Exit
    //=====================================================================

#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
    CoreProcessEnd = TRUE;
    OSSleepMilliseconds(10);
#else
#if TEST_MODE == 1
    OSJoinThread(&Thread[2], NULL);
#elif TEST_MODE == 2
    OSJoinThread(&Thread[3], NULL);
#else
    OSJoinThread(&Thread[2], NULL);
    OSJoinThread(&Thread[3], NULL);
#endif
#endif

//    shutdownAudioSystem();

    OSJoinThread(&Thread[0], NULL);
    OSJoinThread(&Thread[1], NULL);

    FreeShader();
    FreeAttribData();
    // demo shutdown
    DEMOGfxShutdown();
#ifdef USE_PROCESS_SWITCHING
    VPADShutdown();
    DEMOPadShutdown();
#endif
    DEMOShutdown();

    OSReport("MP4Player demo finish.\n");

    return DEMOTestResult();
}
