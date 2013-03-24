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
#include <cafe/mp4dmx.h>   // MP4Demux
#include <cafe/aacdec.h>   // AAC
#include <cafe/h264.h> // H.264
#include "MovieTest.h"

#include <Utility/Log.h>

/*=========================================================================*
            definitions
 *=========================================================================*/

#define M_ALIGN(x)              ( (( ((s32)(x)) + 63)>>6)<<6 )
#define M_N_ALIGN_SIZE(x, size) ( ( ((s32)(x)) +(size-1)) & (~(size-1)) )

// MP4Demux callback actions
#define MODE0_VIDEO_STDINPUT    0
#define MODE1_VIDEO_CNTINPUT    1
#define MODE2_AUDIO_STDINPUT    2
#define MODE3_AUDIO_CNTINPUT    3
#define MODE4_VIDEO_STDDECODE   4
#define MODE5_VIDEO_CNTDECODE   5
#define MODE6_VIDEO_NXTDECODE   6
#define MODE7_AUDIO_STDDECODE   7
#define MODE8_AUDIO_CNTDECODE   8
#define MODE9_AUDIO_NXTDECODE   9

/*
// details of the return value
static const s8* strRetVal[] = 
{
    "MP4DMX_RET_FOUND_FTYP_BOX",
    "MP4DMX_RET_FOUND_MOOV_BOX",
    "MP4DMX_RET_FOUND_MOOF_BOX",
    "MP4DMX_RET_FOUND_MFRA_BOX",
    "MP4DMX_RET_FOUND_MFRO_BOX",
    "MP4DMX_RET_READ_HEADER",
    "MP4DMX_RET_INPUT_CONTINUE",
    "MP4DMX_RET_FIND_HEADER",
    "MP4DMX_RET_NOT_FOUND_BOX",
    "MP4DMX_RET_EXECUTE_NORMAL",
    "MP4DMX_RET_EXECUTE_WARNING",
    "MP4DMX_RET_UNKOWN"
};
*/

/*=========================================================================*
            external functions
 *=========================================================================*/

extern s32 VideoInit(s32 threadnum);
extern s32 VideoOpenH264(s32 threadnum);
extern s32 VideoPlayH264(s32 threadnum);


/*=========================================================================*
            external variables
 *=========================================================================*/

extern MP4PlayerCore    *MP4PlayerCorePtr[];

#ifdef USE_PROCESS_SWITCHING
extern BOOL            inForeground;
extern s32 threadabort[][8];
#ifndef USE_SINGLE_CORE
extern s32 exc_start_time_stamp[];
#endif
#endif


/*=========================================================================*
            global variables
 *=========================================================================*/

MP4DemuxCore    *MP4DemuxCorePtr[2];
void *gMlibHandle[2];


/*=========================================================================*
            prototype
 *=========================================================================*/
s32 MP4DMXFW_ExecuteForHeader(void *pMlibHandle, MP4DMXFW_CtrlParam *ctrl_param, s32 threadmun);


#ifdef USE_PROCESS_SWITCHING
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
    Name:           printHeaderInfo
    Description:    show the MP4 header information
    Arguments:      <input>
                        headerInfo          header information
    Returns:        
 *-------------------------------------------------------------------------*/
void printHeaderInfo(MP4DMXMpoMp4HeaderInf *headerInfo)
{
    LOG_WRITE("headerInfo->size                = %d\n", headerInfo->size);
    LOG_WRITE("headerInfo->duration            = 0x%016llX\n", headerInfo->duration);
    LOG_WRITE("headerInfo->track_num           = %d\n", headerInfo->track_num);
    LOG_WRITE("headerInfo->major_brand         = %s\n", headerInfo->major_brand);
    LOG_WRITE("headerInfo->minor_version       = 0x%X\n", headerInfo->minor_version);
    LOG_WRITE("headerInfo->compatible_brands   = %s\n", headerInfo->compatible_brands);
}


/*-------------------------------------------------------------------------*
    Name:           printTrackInfo
    Description:    show the track information
    Arguments:      <input>
                        trackInfo           header information
    Returns:        
 *-------------------------------------------------------------------------*/
void printTrackInfo(MP4DMXMpoMp4TrackInf  *trackInfo)
{
    LOG_WRITE("trackInfo->track_ID             = %d\n", trackInfo->track_ID);
    LOG_WRITE("trackInfo->timescale            = %d\n", trackInfo->timescale);
    LOG_WRITE("trackInfo->duration             = 0x%016llX\n", trackInfo->duration);
    LOG_WRITE("trackInfo->type                 = %d\n", trackInfo->type);
    LOG_WRITE("trackInfo->supported_flag       = %d\n", trackInfo->supported_flag);
    LOG_WRITE("trackInfo->stts_exist_flag      = %d\n", trackInfo->stts_exist_flag);
    LOG_WRITE("trackInfo->tfra_exist_flag      = %d\n", trackInfo->tfra_exist_flag);
    LOG_WRITE("trackInfo->num_of_entry         = %d\n", trackInfo->num_of_entry);
}


/*-------------------------------------------------------------------------*
    Name:           printVideoTrackInfo
    Description:    show the video track information
    Arguments:      <input>
                        trackInfo           header information
    Returns:        
 *-------------------------------------------------------------------------*/
void printVideoTrackInfo(MP4DMXMpoMp4VideoTrackInf *mp4VideoTrackInf)
{
    s8  a, b, c, d;

    LOG_WRITE("mp4VideoTrackInf->size          = %d\n", mp4VideoTrackInf->size);
    a = (s8)((mp4VideoTrackInf->mediatype>>24)&0xFF);
    b = (s8)((mp4VideoTrackInf->mediatype>>16)&0xFF);
    c = (s8)((mp4VideoTrackInf->mediatype>>8)&0xFF);
    d = (s8)(mp4VideoTrackInf->mediatype&0xFF);
    LOG_WRITE("mp4VideoTrackInf->mediatype     = 0x%X(%c%c%c%c)\n", mp4VideoTrackInf->mediatype,a,b,c,d);
    LOG_WRITE("mp4VideoTrackInf->width         = %d\n", mp4VideoTrackInf->width);
    LOG_WRITE("mp4VideoTrackInf->height        = %d\n", mp4VideoTrackInf->height);
    LOG_WRITE("mp4VideoTrackInf->maxbitrate    = %d\n", mp4VideoTrackInf->maxbitrate);
    LOG_WRITE("mp4VideoTrackInf->avgbitrate    = %d\n", mp4VideoTrackInf->avgbitrate);
    LOG_WRITE("mp4VideoTrackInf->framerate     = %d\n", mp4VideoTrackInf->framerate);
    LOG_WRITE("mp4VideoTrackInf->profile       = %d\n", mp4VideoTrackInf->profile);
    LOG_WRITE("mp4VideoTrackInf->level         = %d\n", mp4VideoTrackInf->level);
}


/*-------------------------------------------------------------------------*
    Name:           printAudioTrackInfo
    Description:    show the audio track information
    Arguments:      <input>
                        trackInfo           header information
    Returns:        
 *-------------------------------------------------------------------------*/
void printAudioTrackInfo(MP4DMXMpoMp4AudioTrackInf *mp4AudioTrackInf)
{
    s8      a, b, c, d;

    LOG_WRITE("mp4AudioTrackInf->size          = %d\n", mp4AudioTrackInf->size);
    a = (s8)((mp4AudioTrackInf->mediatype>>24)&0xFF);
    b = (s8)((mp4AudioTrackInf->mediatype>>16)&0xFF);
    c = (s8)((mp4AudioTrackInf->mediatype>>8)&0xFF);
    d = (s8)(mp4AudioTrackInf->mediatype&0xFF);
    LOG_WRITE("mp4AudioTrackInf->mediatype     = 0x%X(%c%c%c%c)\n", mp4AudioTrackInf->mediatype, a,b,c,d);
    LOG_WRITE("mp4AudioTrackInf->channel_count = %d\n", mp4AudioTrackInf->channel_count);
    LOG_WRITE("mp4AudioTrackInf->sample_size   = %d\n", mp4AudioTrackInf->sample_size);
    LOG_WRITE("mp4AudioTrackInf->sample_rate   = %d\n", mp4AudioTrackInf->sample_rate);
    LOG_WRITE("mp4AudioTrackInf->avgbitrate    = %d\n", mp4AudioTrackInf->avgbitrate);
    LOG_WRITE("mp4AudioTrackInf->maxbitrate    = %d\n", mp4AudioTrackInf->maxbitrate);
    LOG_WRITE("mp4AudioTrackInf->channel_mode  = %d\n", mp4AudioTrackInf->channel_mode);
}


/*-------------------------------------------------------------------------*
    Name:           H264Dec_Output
    Description:    output decoded image data
    Arguments:      <input>
                        ptr                 output data pointer
    Returns:        RET_SUCCESS             Success
                    RET_ERROR               Error
 *-------------------------------------------------------------------------*/
s32 H264Dec_Output(void *ptr)
{
    H264DECOutput       *h264decoutput;
    H264DECResult       **h264decresult;
    s32     fmcnt;
    s32     ret;
    s32     threadnum;

    h264decoutput = (H264DECOutput *) ptr;
    h264decresult = h264decoutput->DecResPtr;
    threadnum     = *(s32 *)h264decoutput->UserMemory;

    for(fmcnt = 0; fmcnt < h264decoutput->FmCnt; fmcnt++)
    {
        // The callback function calls to output data sample
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr    = (u8 *)h264decresult[fmcnt]->Result;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size        = MP4PlayerCorePtr[threadnum]->UVDOutFrameSize;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->pts         = (s32)h264decresult[fmcnt]->TimeStamp;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.type                = MEDIA_SAMPLE;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.track_type          = TRACK_TYPE_VIDEO;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.status              = 0;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset              = 0;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_offset        = 0;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_size          = 0;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.num_of_sample       = 1;
        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.threadnum           = threadnum;

        do {
            ret = MP4DemuxCorePtr[threadnum]->cbgetfunc(&MP4DemuxCorePtr[threadnum]->OutputUnitPtr, NULL);
        } while (ret == MP4DMXFW_RET_WARNING_NOP);

        if(ret != MP4DMXFW_RET_SUCCESS)
        {
            return -1;  // error
        }
    }

    return 0;
}


/*-------------------------------------------------------------------------*
    Name:           getReturnValue
    Description:    return the index number
    Arguments:      <input>
                        retVal              return value
    Returns:        index number
 *-------------------------------------------------------------------------*/
s32 getReturnValue(s32 retVal)
{
    s32     index = -1;

    switch(retVal)
    {
        case MP4DMX_RET_FOUND_FTYP_BOX:
            index = 0;
            break;
        case MP4DMX_RET_FOUND_MOOV_BOX:
            index = 1;
            break;
        case MP4DMX_RET_FOUND_MOOF_BOX:
            index = 2;
            break;
        case MP4DMX_RET_FOUND_MFRA_BOX:
            index = 3;
            break;
        case MP4DMX_RET_FOUND_MFRO_BOX:
            index = 4;
            break;
        case MP4DMX_RET_READ_HEADER:
            index = 5;
            break;
        case MP4DMX_RET_INPUT_CONTINUE:
            index = 5;
            break;
        case MP4DMX_RET_FIND_HEADER:
            index = 7;
            break;
        case MP4DMX_RET_NOT_FOUND_BOX:
            index = 8;
            break;
        case MP4DMX_RET_EXECUTE_NORMAL:
            index = 9;
            break;
        case MP4DMX_RET_EXECUTE_WARNING:
            index = 10;
            break;
        default:
            return 11;
    }

    return index;
}


/*-------------------------------------------------------------------------*
    Name:           SMPiFreq2Index
    Description:    return the frequency index number
    Arguments:      <input>
                        freq                frequency[Hz]
    Returns:        index number[0-12]
 *-------------------------------------------------------------------------*/
static u16 SMPiFreq2Index(s32 freq)
{
    s32     i;

    for (i = 0; i < AACDEC_MAX_FREQ_INDEX; i++)
    {
        if (AACDEC_giFreqIndex[i] == freq)
        {
            break;
        }
    }

    return (u16)i;
}


/*-------------------------------------------------------------------------*
    Name:           MP4DemuxOutput
    Description:    callback function of MP4 Demultiplexer
                    call after each 1 frame demultiplexer
    Arguments:      <input>
                        data                sample information
                        track_ID            track type
                        handle              callback handle
    Returns:        MP4DMX_RET_SUCCESS      Success
                    MP4DMX_RET_ERROR        Error
 *-------------------------------------------------------------------------*/
s32 MP4DemuxOutput(MP4DMXMpoDATA* data, s32 track_ID, void* handle)
{
    s32     i, j, k;
    s32     ret;
    MP4DMXMpoUNIT* pSample;
    MP4DMX_CB_HANDLE* pCbHandle = (MP4DMX_CB_HANDLE*)handle;
    u8      *pOutp = NULL;
    u8      *pTmpp = NULL;
    pSample = (MP4DMXMpoUNIT*)(*(data->data));
    u32     nal_unit_length;
    AACDEC_AAC_INFO aacinfo;
    s32     actmode = -1;
    s32     video_retry_flag;
    s32     threadnum;

    if (gMlibHandle[0] == (void *)*(*pCbHandle).mlibHandle)
    {
        threadnum = 0;
    }
    else if (gMlibHandle[1] == (void *)*(*pCbHandle).mlibHandle)
    {
        threadnum = 1;
    }

#ifdef USE_PROCESS_SWITCHING
    ProcessChangeWait(threadnum, 2);
#endif

    /*
        [actmode]
            0 : video input normal
            2 : video input continue
            1 : audio input normal
            3 : audio input continue
            4 : video normal decode
            5 : video continue decode
            6 : video after audio decode
            8 : audio normal decode
            7 : audio continue decode
            9 : audio after video decode
    */

    if(pCbHandle->v_track_id == track_ID)
    {
        actmode = MODE0_VIDEO_STDINPUT;
    }
    else if(pCbHandle->a_track_id == track_ID)
    {
        actmode = MODE2_AUDIO_STDINPUT;
    }

    if (actmode < 0)
    {
        return MP4DMX_RET_SUCCESS;
    }

    while (1)
    {
#ifdef USE_PROCESS_SWITCHING
        ProcessChangeWait(threadnum, 2);
#endif
        switch(actmode)
        {
            /****************************************************************************************/
            /* Input H.264 Bitstream Data                                                           */
            /****************************************************************************************/
            case MODE0_VIDEO_STDINPUT:
            case MODE1_VIDEO_CNTINPUT:
                if (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Status[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos] == 0)
                {
                    // get video bitstream data(including AUD and SEI)
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr = MP4DemuxCorePtr[threadnum]->VideoStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos];
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size     = pSample->unit_size;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.type             = MEDIA_CHUNK;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type       = TRACK_TYPE_VIDEO;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset           = pSample->offset;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset     = pSample->chunk_offset;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size       = pSample->chunk_size;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample    = 1;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum        = threadnum;

                    // call the input callback function of the media data
                    ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                    if(ret != MP4DMXFW_RET_SUCCESS)
                    {
                        OSYieldThread();
                        if (ret == MP4DMXFW_RET_ERROR_SAMPLE_STOP)
                        {
                            MP4DemuxCorePtr[threadnum]->SampleStop = 1;
                        }
                        return MP4DMX_RET_ERROR;
                    }

                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos]   = reinterpret_cast< u8 * >( MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr );
                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.PTS[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos]    = (s32)pSample->time_stamp;
                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Size[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos]   = pSample->unit_size;
                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Status[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos] = 1;
                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.CMP_OFFSET[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos] = (s32)pSample->cmp_offset;
                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos++;
                    if (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos == VIDEO_BUFFER_NUM)
                    {
                        MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos = 0;
                    }
                    if ((MP4DemuxCorePtr[threadnum]->H264DecFirstFlag == 1) && (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos < (MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_framerate/2)))
                    {
                        OSYieldThread();
                        return MP4DMX_RET_SUCCESS;
                    }
                    actmode = MODE4_VIDEO_STDDECODE;
                }
                else
                {
                    actmode = MODE5_VIDEO_CNTDECODE;
                }

                if (actmode == MODE1_VIDEO_CNTINPUT)
                {
                    OSYieldThread();
                    return MP4DMX_RET_SUCCESS;
                }
                OSYieldThread();
                break;

            /****************************************************************************************/
            /* Input AAC Bitstream Data                                                             */
            /****************************************************************************************/
            case MODE2_AUDIO_STDINPUT:
            case MODE3_AUDIO_CNTINPUT:
                if (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.Status[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos] == 0)
                {
                    // get audio bitstream data
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr = MP4DemuxCorePtr[threadnum]->AudioStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos];
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size     = pSample->unit_size;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.type             = MEDIA_CHUNK;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type       = TRACK_TYPE_AUDIO;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset           = pSample->offset;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset     = pSample->chunk_offset;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size       = pSample->chunk_size;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample    = 1;
                    MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum        = threadnum;

                    // call the input callback function of the media data
                    ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                    if(ret != MP4DMXFW_RET_SUCCESS)
                    {
                        OSYieldThread();
                        if (ret == MP4DMXFW_RET_ERROR_SAMPLE_STOP)
                        {
                            MP4DemuxCorePtr[threadnum]->SampleStop = 1;
                        }
                        return MP4DMX_RET_ERROR;
                    }

                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos]   = reinterpret_cast< u8 * >( MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr );
                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.PTS[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos]    = pSample->time_stamp;
                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.Size[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos]   = pSample->unit_size;
                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.Status[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos] = 1;
                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos++;
                    if (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos == AUDIO_BUFFER_NUM)
                    {
                        MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos = 0;
                    }
                    if ((MP4DemuxCorePtr[threadnum]->AACDecFirstFlag == 1) && (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos < (MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.sample_rate/1024)/2))
                    {
                        OSYieldThread();
                        return MP4DMX_RET_SUCCESS;
                    }
                    actmode = MODE7_AUDIO_STDDECODE;
                }
                else
                {
                    actmode = MODE8_AUDIO_CNTDECODE;
                }

                if (actmode == MODE3_AUDIO_CNTINPUT)
                {
                    OSYieldThread();
                    return MP4DMX_RET_SUCCESS;
                }
                OSYieldThread();
                break;

            /****************************************************************************************/
            /* Decode H.264 Bitstream Data                                                          */
            /****************************************************************************************/
            case MODE4_VIDEO_STDDECODE:
            case MODE5_VIDEO_CNTDECODE:
            case MODE6_VIDEO_NXTDECODE:
                if (abs(MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos - MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos) < 2)
                {
                   OSYieldThread();
                   return MP4DMX_RET_SUCCESS;
                }
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr = MP4DemuxCorePtr[threadnum]->VideoStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos];
                pTmpp = (u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr;
                // add the nal_unit_code
                nal_unit_length = 0;
                if (MP4DemuxCorePtr[threadnum]->H264DecFirstFlag)
                {
                    pOutp = (u8 *)MP4DemuxCorePtr[threadnum]->H264BSBuffer;
                    memcpy(pOutp, MP4DemuxCorePtr[threadnum]->H264HeaderBuffer, MP4DemuxCorePtr[threadnum]->H264HeaderSize);
                    for (i = 0, j = MP4DemuxCorePtr[threadnum]->H264HeaderSize; i < MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Size[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos];)
                    {
                        for (k = 0; k < MP4DemuxCorePtr[threadnum]->AVCconfig.length_size; k++)
                        {
                            nal_unit_length <<= 8;
                            nal_unit_length |= pTmpp[i];
                            i++;
                        }
                        pOutp[j+0] = 0;
                        pOutp[j+1] = 0;
                        pOutp[j+2] = 1;
                        j += 3;
                        if ((j + nal_unit_length) > H264DEC_STREAMBUF_SIZE)
                        {
                            return MP4DMX_RET_ERROR;
                        }
                        memcpy(&pOutp[j], &pTmpp[i], nal_unit_length);
                        i += nal_unit_length;
                        j += nal_unit_length;
                    }
                    MP4DemuxCorePtr[threadnum]->H264DecFirstFlag = 0;
                    MP4DemuxCorePtr[threadnum]->H264BpicTimeOffset = MP4DemuxCorePtr[threadnum]->VideoStreamInfo.CMP_OFFSET[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos];
                }
                else
                {
                    pOutp = (u8 *)MP4DemuxCorePtr[threadnum]->H264BSBuffer;
                    for (i = 0, j = 0 ; i < MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Size[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos];)
                    {
                        for (k = 0; k < MP4DemuxCorePtr[threadnum]->AVCconfig.length_size; k++)
                        {
                            nal_unit_length <<= 8;
                            nal_unit_length |= pTmpp[i];
                            i++;
                        }
                        pOutp[j+0] = 0;
                        pOutp[j+1] = 0;
                        pOutp[j+2] = 1;
                        j += 3;
                        if ((j + nal_unit_length) > H264DEC_STREAMBUF_SIZE)
                        {
                            return MP4DMX_RET_ERROR;
                        }
                        memcpy(&pOutp[j], &pTmpp[i], nal_unit_length);
                        i += nal_unit_length;
                        j += nal_unit_length;
                    }
                }

                if (MP4PlayerCorePtr[threadnum]->FrameSkipFlag)
                {
                    /*************************************************************************/
                    /*                                                                       */
                    /*              End of the H.264 Video Decoder.                          */
                    /*                                                                       */
                    /*************************************************************************/

                    ret = H264DECEnd(MP4DemuxCorePtr[threadnum]->H264WorkBuffer);
                    if( ret != 0 )
                    {
                        LOG_WRITE("H264DECEnd Failed. ret = %d\n", ret );
                        OSYieldThread();
                        return MP4DMX_RET_ERROR;
                    }

                    /*************************************************************************/
                    /*                                                                       */
                    /*              Beginnig of the H.264 Video Decoder.                     */
                    /*                                                                       */
                    /*************************************************************************/

                    ret = H264DECBegin(MP4DemuxCorePtr[threadnum]->H264WorkBuffer);
                    if (ret != 0)
                    {
                        LOG_WRITE("H264DECBegin Failed. ret = %d\n", ret );
                        OSYieldThread();
                        return MP4DMX_RET_ERROR;
                    }
                }

                /****************************************************/
                /*                                                  */
                /*              H.264 Decoder Execute               */
                /*                                                  */
                /****************************************************/
                ret = H264DECSetBitstream(MP4DemuxCorePtr[threadnum]->H264WorkBuffer, pOutp, j, (s32)MP4DemuxCorePtr[threadnum]->VideoStreamInfo.PTS[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos] + (s32)MP4DemuxCorePtr[threadnum]->VideoStreamInfo.CMP_OFFSET[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos] - (s32)MP4DemuxCorePtr[threadnum]->H264BpicTimeOffset);
                if (ret != 0)
                {
                    LOG_WRITE("error : bitstream set : 0x%x\n", ret);
                    ret = H264DEC_ERR_INTERNAL;
                    OSYieldThread();
                    return MP4DMX_RET_ERROR;
                }

                video_retry_flag = 1;
                while (video_retry_flag)
                {
                    ret = VideoPlayH264(threadnum);

                    // If there is no area in the output buffer, forced to perform image display
                    if (ret == -2)
                    {
                        // call the output callback function of the image data
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr    = NULL;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size        = 0;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->pts         = 0;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.type                = MEDIA_SAMPLE;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.track_type          = TRACK_TYPE_ANY;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.status              = 0;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset              = 0;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_offset        = 0;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_size          = 0;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.num_of_sample       = 1;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.threadnum           = threadnum;

                        do {
                            ret = MP4DemuxCorePtr[threadnum]->cbgetfunc(&MP4DemuxCorePtr[threadnum]->OutputUnitPtr, NULL);
                        } while (ret == MP4DMXFW_RET_WARNING_NOP);

                        if(ret != MP4DMXFW_RET_SUCCESS)
                        {
                            OSYieldThread();
                            return -1;  // error
                        }
                    }
                    else
                    {
                        video_retry_flag = 0;
                    }
                }

                MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Status[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos] = 0;
                MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos++;
                if (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos == VIDEO_BUFFER_NUM)
                {
                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos = 0;
                }

                if (actmode == MODE5_VIDEO_CNTDECODE)
                {
                    actmode = MODE1_VIDEO_CNTINPUT;
                }
                else if (actmode == MODE6_VIDEO_NXTDECODE)
                {
                   OSYieldThread();
                   return MP4DMX_RET_SUCCESS;
                }
                else
                {
                    actmode = MODE9_AUDIO_NXTDECODE;
                }
                OSYieldThread();
                break;

            /****************************************************************************************/
            /* Decode AAC Bitstream Data                                                            */
            /****************************************************************************************/
            case MODE7_AUDIO_STDDECODE:
            case MODE8_AUDIO_CNTDECODE:
            case MODE9_AUDIO_NXTDECODE:
                if (abs(MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos - MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos) < 2)
                {
                   OSYieldThread();
                   return MP4DMX_RET_SUCCESS;
                }
                if ((MP4DemuxCorePtr[threadnum]->AACDecFirstFlag == 1) && !(pCbHandle->a_track_id == track_ID))
                {
                   OSYieldThread();
                   return MP4DMX_RET_SUCCESS;
                }

                if (MP4DemuxCorePtr[threadnum]->AACDecFirstFlag == 1)
                {
                    MP4DemuxCorePtr[threadnum]->AACSampeRate = MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.sample_rate;
                    MP4DemuxCorePtr[threadnum]->AACChannelNum = MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.channel_count;
                }
                MP4DemuxCorePtr[threadnum]->AACDecFirstFlag = 0;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr = MP4DemuxCorePtr[threadnum]->AudioStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos];

                /****************************************************/
                /*                                                  */
                /*              AAC Decoder Execute                 */
                /*                                                  */
                /****************************************************/
                aacinfo.smp_freq_index = SMPiFreq2Index(MP4DemuxCorePtr[threadnum]->AACSampeRate); // sampling frequency index
                aacinfo.channel        = MP4DemuxCorePtr[threadnum]->AACChannelNum;                // channel number
                aacinfo.data_size      = MP4DemuxCorePtr[threadnum]->AudioStreamInfo.Size[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos];            // input aac bitstream size(byte)
                ret = AACDECExecute((u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr, (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer, (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer + AACDEC_PCM_SAMPLE_SIZE, &aacinfo, MP4DemuxCorePtr[threadnum]->AACWorkBuffer);
                if(ret != AACDEC_NO_ERR)
                {
                    LOG_WRITE("AAC Decode Error\n");
                    OSYieldThread();
                    return MP4DMX_RET_ERROR;
                }

                if (MP4DemuxCorePtr[threadnum]->AACOutStartFlag == 0)
                {
                    memcpy(MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, MP4DemuxCorePtr[threadnum]->AACOutBuffer, sizeof(short)*AACDEC_PCM_SAMPLE_SIZE*2);
                    MP4DemuxCorePtr[threadnum]->AACOutStartFlag = 1;
                    MP4DemuxCorePtr[threadnum]->AACRefPts = MP4DemuxCorePtr[threadnum]->AudioStreamInfo.PTS[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos];
                }
                else
                {
                    // Frequency Convert
                    if (MP4DemuxCorePtr[threadnum]->AACSampeRate != 48000)
                    {
                        double  p_real, x_real;
                        double  convsample;
                        s32     x_pos;
                        s16     *inL, *inR;
                        s16     *outL, *outR;
                        s32     outsize;

                        convsample = 48000;
                        inL = (s16 *)MP4DemuxCorePtr[threadnum]->AACFreqConvTmpL;
                        inR = (s16 *)MP4DemuxCorePtr[threadnum]->AACFreqConvTmpR;
                        if (aacinfo.channel == 1)
                        {
                            outsize = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*((double)convsample/MP4DemuxCorePtr[threadnum]->AACSampeRate);
                            outsize = (outsize >> 1) << 1;
                            x_real = (double)MP4DemuxCorePtr[threadnum]->AACSampeRate/convsample;
                            outL  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                            outR  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer + outsize/2;

                            memcpy(inL, MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);
                            memcpy(MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, MP4DemuxCorePtr[threadnum]->AACOutBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);

                            // padding
                            inL[AACDEC_PCM_SAMPLE_SIZE] = *((s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer);

                            for (j = 0; j < outsize/2; j++)
                            {
                                x_pos = (s32)(j * x_real);
                                p_real = (j * x_real) - x_pos;
                                *outL++    = ((1 - p_real) * inL[x_pos]) + (p_real * inL[x_pos + 1]);
                            }
                        }
                        else
                        {
                            outsize = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*((double)convsample/MP4DemuxCorePtr[threadnum]->AACSampeRate)*2;
                            outsize = (outsize >> 2) << 2;
                            x_real = (double)MP4DemuxCorePtr[threadnum]->AACSampeRate/convsample;
                            outL  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                            outR  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer + outsize/4;

                            memcpy(inL, MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);
                            memcpy(inR, (s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer + AACDEC_PCM_SAMPLE_SIZE, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);
                            memcpy(MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, MP4DemuxCorePtr[threadnum]->AACOutBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2);

                            // padding
                            inL[AACDEC_PCM_SAMPLE_SIZE] = *((s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer);
                            inR[AACDEC_PCM_SAMPLE_SIZE] = *((s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer + AACDEC_PCM_SAMPLE_SIZE);
                            for (j = 0; j < outsize/4; j++)
                            {
                                x_pos = (s32)(j * x_real);
                                p_real = (j * x_real) - x_pos;
                                *outL++    = ((1 - p_real) * inL[x_pos]) + (p_real * inL[x_pos + 1]);
                                *outR++    = ((1 - p_real) * inR[x_pos]) + (p_real * inR[x_pos + 1]);
                            }
                        }
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size      = outsize;
                    }
                    else
                    {
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr    = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                        if (aacinfo.channel == 1)
                        {
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size    = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE;
                        }
                        else
                        {
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size    = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2;
                        }
                    }

                    // call the output callback function of the pcm data
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->pts         = MP4DemuxCorePtr[threadnum]->AACRefPts;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.type                = MEDIA_SAMPLE;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.track_type          = TRACK_TYPE_AUDIO;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.status              = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset              = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_offset        = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_size          = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.num_of_sample       = 1;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.threadnum           = threadnum;

                    MP4DemuxCorePtr[threadnum]->AACRefPts = MP4DemuxCorePtr[threadnum]->AudioStreamInfo.PTS[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos];

                    do {
                        ret = MP4DemuxCorePtr[threadnum]->cbgetfunc(&MP4DemuxCorePtr[threadnum]->OutputUnitPtr, NULL);
                        if (ret == MP4DMXFW_RET_WARNING_NOP)
                        {
                            OSYieldThread();
                        }
                    } while (ret == MP4DMXFW_RET_WARNING_NOP);

                    if(ret != MP4DMXFW_RET_SUCCESS)
                    {
                        OSYieldThread();
                        return MP4DMX_RET_ERROR;
                    }
                }

                MP4DemuxCorePtr[threadnum]->AudioStreamInfo.Status[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos] = 0;
                MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos++;
                if (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos == AUDIO_BUFFER_NUM)
                {
                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos = 0;
                }

                if (actmode == MODE8_AUDIO_CNTDECODE)
                {
                    actmode = MODE3_AUDIO_CNTINPUT;
                }
                else if (actmode == MODE9_AUDIO_NXTDECODE)
                {
                   OSYieldThread();
                   return MP4DMX_RET_SUCCESS;
                }
                else
                {
                    actmode = MODE6_VIDEO_NXTDECODE;
                }
                OSYieldThread();
                break;
        }
    }

//  LOG_WRITE("CB, T_ID = %d, time_stamp = %d, chunk_size = %d, unit_size = %d, duration = %d, num_of_samle = %d\n",
//      track_ID, (s32)pSample->time_stamp, (s32)pSample->chunk_size, pSample->unit_size, (s32)pSample->duration, pSample->num_of_sample);
}


/*-------------------------------------------------------------------------*
    Name:           Set_Demux_PARAM
    Description:    MP4 Demultiplexer parameter settings
    Arguments:      <input>
                        p_param             parameter pointer
                        pCbHandle           callback handle
                        pmlibHandle         pointer to a handle MP4 Demultiplexer
    Returns:        
 *-------------------------------------------------------------------------*/
void Set_Demux_PARAM( MP4DMXMpoPARAMETER *p_param , MP4DMX_CB_HANDLE *pCbHandle, void **pmlibHandle, s32 threadnum)
{
    s32     pcnt = 0;

    p_param[pcnt].id = MP4DMX_OUT_ONLY_KEYFRAME;
    p_param[pcnt].value.int32 = 0;
    pcnt++;
    p_param[pcnt].id = MP4DMX_INPUT_AUDIO_BUFFER_NUM;
    p_param[pcnt].value.int32 = 100;
    pcnt++;
    p_param[pcnt].id = MP4DMX_INPUT_VIDEO_BUFFER_NUM;
    p_param[pcnt].value.int32 = 100;
    pcnt++;
    p_param[pcnt].id = MP4DMX_OUT_VIDEO_FLAG;
    p_param[pcnt].value.ptr = &MP4DemuxCorePtr[threadnum]->MP4Dmx_OutVideoFlag;
    pcnt++;
    p_param[pcnt].id = MP4DMX_OUT_AUDIO_FLAG;
    p_param[pcnt].value.ptr = &MP4DemuxCorePtr[threadnum]->MP4Dmx_OutAudioFlag;
    pcnt++;

    p_param[pcnt].id = MP4DMX_STTS_READ_BUFFER_SIZE;
    p_param[pcnt].value.int32 = 32768;
    pcnt++;

    p_param[pcnt].id = MP4DMX_STSZ_READ_BUFFER_SIZE;
    p_param[pcnt].value.int32 = 32768;
    pcnt++;

    p_param[pcnt].id = MP4DMX_CTTS_READ_BUFFER_SIZE;
    p_param[pcnt].value.int32 = 32768;
    pcnt++;

    MP4DemuxCorePtr[threadnum]->MP4Dmx_OutputFunc.handle      = pCbHandle;
    MP4DemuxCorePtr[threadnum]->MP4Dmx_OutputFunc.output_fptr = &MP4DemuxOutput;
    p_param[pcnt].id = MP4DMX_MPO_OUTPUT_FUNCTION;
    p_param[pcnt].value.ptr  = &MP4DemuxCorePtr[threadnum]->MP4Dmx_OutputFunc;
    pcnt++;

    /* parameter set end */
    p_param[pcnt].id = MP4DMX_MPO_PARAMETER_END;

    return;
}


/*-------------------------------------------------------------------------*
    Name:           MP4DMXFW_Open
    Description:    Open MP4 Demultiplexer framework
                    Initialization of each codec, memory allocation, and setting
    Arguments:      <input>
                        ExpHeap             heap memory pointer(allocated in the application layer)
                        handle              pointer to a handle MP4 Demultiplexer
                    <output>
                        UseWorkMemSize      required memory size
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 MP4DMXFW_Open(MEMHeapHandle ExpHeap, void **handle, s32 *UseWorkMemSize, s32 threadnum)
{
    s32     iMlibRet;
    s32     size = 0;
    MP4DMXMpoPARAMETER  param[20];

    *UseWorkMemSize = 0;

    MP4DemuxCorePtr[threadnum]                   = (MP4DemuxCore *)MEMAllocFromDefaultHeapEx(sizeof(MP4DemuxCore), 1024);
    if (MP4DemuxCorePtr[threadnum] == NULL)
    {
        LOG_WRITE("MP4DemuxCore malloc Failed.\n");
        return MP4DMXFW_RET_ERROR;
    }

    // setting workbuffers
    MP4DemuxCorePtr[threadnum]->H264BSBuffer     = MEMAllocFromDefaultHeapEx(sizeof(u8)*H264DEC_STREAMBUF_SIZE+8,    1024);
    MP4DemuxCorePtr[threadnum]->H264HeaderBuffer = MEMAllocFromDefaultHeapEx(sizeof(u8)*H264DEC_AVCHEADER_SIZE,      1024);
    MP4DemuxCorePtr[threadnum]->AACOutBuffer     = MEMAllocFromDefaultHeapEx(sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2*8, 1024);     // *8 for upsampling(48000/8000)
    MP4DemuxCorePtr[threadnum]->AACBSBuffer      = MEMAllocFromDefaultHeapEx(sizeof(u8)*(AACDEC_STREAM_MAX_SIZE),    1024);
    MP4DemuxCorePtr[threadnum]->AACWorkBuffer    = MEMAllocFromDefaultHeapEx(sizeof(u8)*AACDEC_WORK_SIZE,            1024);
    MP4DemuxCorePtr[threadnum]->AACFreqConvTmpL  = MEMAllocFromDefaultHeapEx(sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2,   1024);
    MP4DemuxCorePtr[threadnum]->AACFreqConvTmpR  = MEMAllocFromDefaultHeapEx(sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2,   1024);
    MP4DemuxCorePtr[threadnum]->AACOutRefBuffer  = MEMAllocFromDefaultHeapEx(sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2,   1024);

    if (MP4DemuxCorePtr[threadnum]->H264BSBuffer == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->H264BSBuffer     malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }
    if (MP4DemuxCorePtr[threadnum]->H264HeaderBuffer == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->H264HeaderBuffer malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }
    if (MP4DemuxCorePtr[threadnum]->AACOutBuffer == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->AACOutBuffer     malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }
    if (MP4DemuxCorePtr[threadnum]->AACBSBuffer == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->AACBSBuffer      malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }
    if (MP4DemuxCorePtr[threadnum]->AACWorkBuffer == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->AACWorkBuffer    malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }
    if (MP4DemuxCorePtr[threadnum]->AACFreqConvTmpL == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->AACFreqConvTmpL  malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }
    if (MP4DemuxCorePtr[threadnum]->AACFreqConvTmpR == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->AACFreqConvTmpR  malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }
    if (MP4DemuxCorePtr[threadnum]->AACOutRefBuffer == NULL)
    {
        LOG_WRITE("MP4DemuxCorePtr[threadnum]->AACOutRefBuffer  malloc ERROR\n");
        return MP4DMXFW_RET_ERROR;
    }

    // setting memory allocator
    MEMInitAllocatorForExpHeap( &MP4DemuxCorePtr[threadnum]->gAllocator, ExpHeap, 1024 );

    size += M_ALIGN(sizeof(u8)*H264DEC_STREAMBUF_SIZE+8);
    size += M_ALIGN(sizeof(u8)*H264DEC_AVCHEADER_SIZE);
    size += M_ALIGN(sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2*2);
    size += M_ALIGN(sizeof(u8)*(AACDEC_STREAM_MAX_SIZE));
    size += M_ALIGN(sizeof(u8)*AACDEC_WORK_SIZE);
    size += M_ALIGN(sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2);
    size += M_ALIGN(sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2);

    /*************************************************************************/
    /*                                                                       */
    /*              Initialisation of the AAC Audio Decoder.                 */
    /*                                                                       */
    /*************************************************************************/

    MP4DemuxCorePtr[threadnum]->H264DecFirstFlag = 1;
    MP4DemuxCorePtr[threadnum]->AACDecFirstFlag  = 1;
    iMlibRet = AACDECOpen( MP4DemuxCorePtr[threadnum]->AACWorkBuffer );
    if( iMlibRet !=  AACDEC_NO_ERR )
    {
        LOG_WRITE("AACDECOpen Failed. ret = %d\n", iMlibRet );
        return MP4DMXFW_RET_ERROR;
    }

    /*************************************************************************/
    /*                                                                       */
    /*              Initialisation of the MP4 Demux.                         */
    /*                                                                       */
    /*************************************************************************/

    MP4DemuxCorePtr[threadnum]->MP4Dmx_OutAudioFlag = 1;
    MP4DemuxCorePtr[threadnum]->MP4Dmx_OutVideoFlag = 1;

    memset(&MP4DemuxCorePtr[threadnum]->VideoStreamInfo, 0, sizeof(StreamRingInfoV));
    memset(&MP4DemuxCorePtr[threadnum]->AudioStreamInfo, 0, sizeof(StreamRingInfoA));

    memset(&MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle, 0, sizeof(MP4DMX_CB_HANDLE));
    Set_Demux_PARAM( param, &MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle, handle, threadnum );      // set demux parameters

    iMlibRet = MP4DMXOpen( param, handle, (void *)&MP4DemuxCorePtr[threadnum]->gAllocator );
    if( iMlibRet != MP4DMX_RET_SUCCESS )
    {
        LOG_WRITE("MP4DMXOpen Failed. ret = %d\n", iMlibRet );
        return MP4DMXFW_RET_ERROR;
    }

    MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.mlibHandle = handle;     // MP4Demux handler
    MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.h264memPtr = NULL;       // work memory address for H.264 decoder

    *UseWorkMemSize = size;

    return MP4DMXFW_RET_SUCCESS;
}


/*-------------------------------------------------------------------------*
    Name:           MP4DMXFW_Begin
    Description:    Begin MP4 Demultiplexer framework
                    Set the start of each codec
    Arguments:      <input>
                        handle              pointer to a handle MP4 Demultiplexer
                        ctrl_param          pointer to control parameters
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 MP4DMXFW_Begin(void *handle, MP4DMXFW_CtrlParam *ctrl_param, s32 threadnum)
{
    s32     iMlibRet;

    /*************************************************************************/
    /*                                                                       */
    /*              Beginnig of the MP4 Demux.                               */
    /*                                                                       */
    /*************************************************************************/

    MP4DemuxCorePtr[threadnum]->H264ImageWidth = 0;
    MP4DemuxCorePtr[threadnum]->H264ImageHeight = 0;
    MP4DemuxCorePtr[threadnum]->H264Profile = 0;
    MP4DemuxCorePtr[threadnum]->H264Level = 0;

    MP4DemuxCorePtr[threadnum]->VideoTrackFound = 0;
    MP4DemuxCorePtr[threadnum]->AudioTrackFound = 0;
    MP4DemuxCorePtr[threadnum]->SampleStop      = 0;
    MP4DemuxCorePtr[threadnum]->AACRefPts       = 0;
    MP4DemuxCorePtr[threadnum]->AACOutStartFlag = 0;

    iMlibRet = MP4DMXBegin( handle );
    if( iMlibRet != MP4DMX_RET_SUCCESS )
    {
        LOG_WRITE("MP4DMXBegin Failed. ret = %d\n", iMlibRet );
        return MP4DMXFW_RET_ERROR;
    }

    iMlibRet = MP4DMXFW_ExecuteForHeader(handle, ctrl_param, threadnum);    // MP4 header parsing
    if( iMlibRet != MP4DMX_RET_SUCCESS )
    {
        LOG_WRITE("MP4DMXFW_ExecuteForHeader Failed. ret = %d\n", iMlibRet );
        return MP4DMXFW_RET_ERROR;
    }

    // H.264 Video decoder open(after getting the Profile/Level/Width/Height)
    if (MP4DemuxCorePtr[threadnum]->VideoTrackFound)
    {
        /*************************************************************************/
        /*                                                                       */
        /*              Initialisation of the H.264 Video Decoder.               */
        /*                                                                       */
        /*************************************************************************/

        iMlibRet = VideoOpenH264(threadnum);
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            LOG_WRITE("VideoOpenH264 Failed. ret = %d\n", iMlibRet );
            return MP4DMXFW_RET_ERROR;
        }

        /*************************************************************************/
        /*                                                                       */
        /*              Beginnig of the H.264 Video Decoder.                     */
        /*                                                                       */
        /*************************************************************************/

        iMlibRet = H264DECBegin(MP4DemuxCorePtr[threadnum]->H264WorkBuffer);
        if (iMlibRet != 0)
        {
            LOG_WRITE("H264DECBegin Failed. ret = %d\n", iMlibRet );
            return MP4DMXFW_RET_ERROR;
        }

        iMlibRet = VideoInit(threadnum);
        if (iMlibRet != 0)
        {
            LOG_WRITE("VideoInit Failed. ret = %d\n", iMlibRet );
            return MP4DMXFW_RET_ERROR;
        }
    }

    return MP4DMX_RET_SUCCESS;
}


/*-------------------------------------------------------------------------*
    Name:           MP4DMXFW_ExecuteForHeader
    Description:    MP4 header parsing
    Arguments:      <input>
                        handle              pointer to a handle MP4 Demultiplexer
                        ctrl_param          pointer to control parameters
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 MP4DMXFW_ExecuteForHeader(void *pMlibHandle, MP4DMXFW_CtrlParam *ctrl_param, s32 threadnum)
{
    s32     iMlibRet = MP4DMX_RET_NOT_FOUND_BOX;
    s32     iMlibRet_tmp;
    s32     ret;
    s32     i;
    u8      *pData=NULL;
    s32     next_size = 8;
    s32     buf_size = 0;
    u8      *pOutp = NULL;
    u64     next_offset = 0;
    u64     time_stamp = 0;

    MP4DMXMpoMp4TrackInf        trackInfo;
    MP4DMXMpoMp4HeaderInf       headerInfo;
    s32     track_cnt = 0;
    s32     dwPsetLength = 0;
    s32     first_flag = 1;
    s32     second_flag = 0;

    MP4DemuxCorePtr[threadnum]->cbsetfunc = (s32 (*)(MP4DMXFW_UNIT *, void *))(s32)ctrl_param->MP4DMXFW_CallbackSetData;
    MP4DemuxCorePtr[threadnum]->cbgetfunc = (s32 (*)(MP4DMXFW_UNIT *, void *))(s32)ctrl_param->MP4DMXFW_CallbackGetData;
    MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample = &MP4DemuxCorePtr[threadnum]->InputSample;
    MP4DemuxCorePtr[threadnum]->InputUnitPtr.bufsize = buf_size;
    MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset = next_offset;

    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample = &MP4DemuxCorePtr[threadnum]->OutputSample;
    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.bufsize = 0;
    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset = 0;

    while(1)
    {
        /****************************************************/
        /*                                                  */
        /*                  MP4 Container                   */
        /*                                                  */
        /****************************************************/
        if(iMlibRet != MP4DMX_RET_EXECUTE_NORMAL && iMlibRet != MP4DMX_RET_EXECUTE_WARNING)
        {
            if(next_size)
            {
                if (second_flag == 0)
                {
                    first_flag = 1;
                }
                if (next_size > (s32)DIVIDE_HEADSIZE)
                {
                    next_size = (s32)DIVIDE_HEADSIZE;
                }

//                LOG_WRITE("readfile, offset = 0x%016llX, length = %d\n",  next_offset, next_size);
                // call the input callback function of the media data
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size     = next_size;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.type             = MEDIA_HEADER;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type       = TRACK_TYPE_ANY;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.status           = 0;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset           = next_offset;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset     = 0;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size       = 0;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample    = 1;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum        = threadnum;

                ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                pData = (u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr;
                next_offset = MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset;

                if(ret == MP4DMXFW_RET_ERROR_SAMPLE_STOP)   // input termination
                {
//                    return MP4DMXFW_RET_SUCCESS;
                    return MP4DMXFW_RET_ERROR;
                }

                if(ret != MP4DMXFW_RET_SUCCESS)
                {
                    return MP4DMXFW_RET_ERROR;
                }
            }
        }

        switch(iMlibRet)
        {
            case MP4DMX_RET_FOUND_FTYP_BOX:
            case MP4DMX_RET_FOUND_MOOV_BOX:
            case MP4DMX_RET_FOUND_MOOF_BOX:
            case MP4DMX_RET_FOUND_MFRA_BOX:
            case MP4DMX_RET_FOUND_MFRO_BOX:
            case MP4DMX_RET_READ_HEADER:
            case MP4DMX_RET_INPUT_CONTINUE:

                if (first_flag == 1)
                {
                    iMlibRet_tmp = iMlibRet;
                }
                first_flag = 0;
                second_flag = 1;

                // ReadHeader
//                LOG_WRITE("begin MP4DMXReadHeader()\n");
                iMlibRet = MP4DMXReadHeader(pData, &time_stamp, &next_offset, &next_size, pMlibHandle);
//                LOG_WRITE("end MP4DMXReadHeader(), return value = %d, %s\n",  iMlibRet, strRetVal[getReturnValue(iMlibRet)]);

                if (iMlibRet==MP4DMX_RET_INPUT_CONTINUE)    // input continue
                {
                    break;
                }
                second_flag = 0;
                break;
            case MP4DMX_RET_FIND_HEADER:
            case MP4DMX_RET_NOT_FOUND_BOX:
                // get the offset of the header data
//                LOG_WRITE("begin MP4DMXFindHeader()\n");
                iMlibRet = MP4DMXFindHeader(pData,next_size,&next_offset,&next_size, pMlibHandle);
//                LOG_WRITE("end MP4DMXFindHeader(), return value = %d, %s\n", iMlibRet, strRetVal[getReturnValue(iMlibRet)]);
                break;
            case MP4DMX_RET_EXECUTE_NORMAL:
            case MP4DMX_RET_EXECUTE_WARNING:
                ret = MP4DMXGetHeaderInf(&headerInfo, pMlibHandle);
                printHeaderInfo(&headerInfo);

                MP4DemuxCorePtr[threadnum]->MP4Duration = (headerInfo.fragment_duration*1000)/headerInfo.timescale;
                for (track_cnt = 0; track_cnt < headerInfo.track_num; track_cnt++)
                {
                    ret = MP4DMXGetTrackInf(track_cnt,&trackInfo, pMlibHandle);
                    printTrackInfo(&trackInfo);
                    if ((trackInfo.type == MP4DMX_VIDEO_TRACK) && !MP4DemuxCorePtr[threadnum]->VideoTrackFound)
                    {
                        MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.v_track_id = trackInfo.track_ID;
                        ret = MP4DMXGetVideoTrackInf(trackInfo.track_ID, &MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf, pMlibHandle);
                        printVideoTrackInfo(&MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf);
                        MP4DemuxCorePtr[threadnum]->H264ImageWidth  = M_N_ALIGN_SIZE(MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.width, 16);
                        MP4DemuxCorePtr[threadnum]->H264ImageHeight = M_N_ALIGN_SIZE(MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.height, 16);
                        MP4DemuxCorePtr[threadnum]->H264Profile = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.profile;
                        MP4DemuxCorePtr[threadnum]->H264Level   = (MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.level) & 0x00FF;
                        MP4DemuxCorePtr[threadnum]->VideoTrackFound = 1;
                    }
                    else if ((trackInfo.type == MP4DMX_AUDIO_TRACK) && !MP4DemuxCorePtr[threadnum]->AudioTrackFound)
                    {
                        s32 size = 0;

                        MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.a_track_id = trackInfo.track_ID;
                        ret = MP4DMXGetAudioTrackInf(trackInfo.track_ID, &MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf, pMlibHandle);
                        ret = MP4DMXGetDecoderSpecificInf (trackInfo.track_ID, 1, NULL, &size, pMlibHandle);
                        if (size >= 2)
                        {
                            MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.channel_count = MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.channel_mode;
                        }
                        if (MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.channel_count > 2)
                        {
                            return MP4DMXFW_RET_ERROR;
                        }
                        if (MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.sample_rate > 48000)
                        {
                            return MP4DMXFW_RET_ERROR;
                        }
                        printAudioTrackInfo(&MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf);
                        MP4DemuxCorePtr[threadnum]->AudioTrackFound = 1;
                    }
                }

                // Read H.264 SPS/PPS
                if (MP4DemuxCorePtr[threadnum]->VideoTrackFound == 1)
                {
                    if (MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.mediatype == MP4DMX_MEDIA_TYPE_AVC1)
                    {
                        memset(&MP4DemuxCorePtr[threadnum]->AVCconfig, 0, sizeof(MP4DMXAvcConfig));
                        ret = MP4DMXGetAVCSpecificInf (1, &MP4DemuxCorePtr[threadnum]->AVCconfig, pMlibHandle);
                        if (ret == MP4DMX_RET_SUCCESS)
                        {
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_sps; i ++)
                            {
                                dwPsetLength += MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length;
                                dwPsetLength += 3;      // 0x000001
                            }
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_pps; i ++)
                            {
                                dwPsetLength += MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length;
                                dwPsetLength += 3;      // 0x000001
                            }

                            pOutp = (u8 *)MP4DemuxCorePtr[threadnum]->H264HeaderBuffer;
                            // add the nal_unit_code
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_sps; i ++)
                            {
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x01;
                                // get SPS only
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size  = MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length + 3;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.type          = MEDIA_HEADER;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type    = TRACK_TYPE_ANY;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.status        = 0;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset        = MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].offset;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset  = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size    = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample = 1;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum     = threadnum;

                                ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                                memcpy(pOutp, (u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr, MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length);
                                pOutp += MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length;
                            }
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_pps; i ++)
                            {
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x01;
                                // get PPS only
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size  = MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length + 3;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.type          = MEDIA_HEADER;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type    = TRACK_TYPE_ANY;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.status        = 0;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset        = MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].offset;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset  = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size    = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample = 1;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum     = threadnum;

                                ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                                memcpy(pOutp, (u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr, MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length);
                                pOutp += MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length;
                            }

                            MP4DemuxCorePtr[threadnum]->H264HeaderSize = dwPsetLength;
                        }
                    }
                    else
                    {
                        return MP4DMX_RET_ERROR;
                    }
                }

                memset(MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample, 0, sizeof(MP4DMXFW_SAMPLE));

                // call the output callback function of the informations
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr = NULL;
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size     = -1;   // unused
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->pts      = -1;   // unused
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.type             = MEDIA_HEADER;
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.track_type       = TRACK_TYPE_ANY;
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.status           = -1;   // unused
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset           = -1;   // unused
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_offset     = -1;   // unused
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_size       = -1;   // unused
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.num_of_sample    = -1;   // unused
                MP4DemuxCorePtr[threadnum]->OutputUnitPtr.threadnum        = threadnum;

                if (MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.v_track_id)
                {
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_width      = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.width;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_height     = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.height;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_framerate  = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.framerate/1000;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_maxbitrate = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.maxbitrate;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_profile    = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.profile;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->video_level      = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.level;
                }

                if (MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.a_track_id)
                {
                    if (MP4DemuxCorePtr[threadnum]->AudioTrackFound == 1)
                    {
                        if (MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.mediatype == MP4DMX_MEDIA_TYPE_MP4A)
                        {
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->audio_channel = MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.channel_count;
                        }
                        else
                        {
                            return MP4DMX_RET_ERROR;
                        }
                    }

                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->audio_subsample = 48000;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->audio_maxbitrate = MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.maxbitrate;
                    MP4DemuxCorePtr[threadnum]->AACSampeRate = MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->audio_subsample;
                }

                ret = MP4DemuxCorePtr[threadnum]->cbgetfunc(&MP4DemuxCorePtr[threadnum]->OutputUnitPtr, NULL);
                if(ret != MP4DMXFW_RET_SUCCESS)
                {
                    return MP4DMX_RET_ERROR;
                }

                MP4DemuxCorePtr[threadnum]->MP4DmxNewStatus = iMlibRet;
                MP4DemuxCorePtr[threadnum]->MP4DmxOldStatus = iMlibRet_tmp;
                MP4DemuxCorePtr[threadnum]->MP4DmxAfterHeaderSize  = next_size;
                MP4DemuxCorePtr[threadnum]->MP4DmxAfterHeaderOffset= next_offset;
                MP4DemuxCorePtr[threadnum]->MP4DmxSeqFirstFlag  = first_flag;
                MP4DemuxCorePtr[threadnum]->MP4DmxSeqSecondFlag = second_flag;

                return MP4DMXFW_RET_SUCCESS;
            default:
                return MP4DMXFW_RET_ERROR;
        }

        if(iMlibRet < MP4DMX_RET_SUCCESS)
        {
            LOG_WRITE("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
            return MP4DMXFW_RET_ERROR;
        }
    }
}


/*-------------------------------------------------------------------------*
    Name:           MP4DMXFW_Execute
    Description:    Execute MP4 Demultiplexer framework
    Arguments:      <input>
                        pMlibHandle         pointer to a handle MP4 Demultiplexer
                        ctrl_param          pointer to control parameters
                        control_flag        play mode flag
                        start_time_stamp    start time stamp
                        end_time_stamp      end time stamp
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 MP4DMXFW_Execute(void *pMlibHandle, MP4DMXFW_CtrlParam *ctrl_param, s32 control_flag, u64 start_time_stamp, u64 end_time_stamp, s32 threadnum)
{
    s32     iMlibRet = MP4DMX_RET_NOT_FOUND_BOX;
    s32     iMlibRet_tmp;
    s32     ret;
    s32     i;
    u8      *pData=NULL;
    s32     next_size=8;
    s32     buf_size = 0;
    u8      *pOutp = NULL;
    s32     track_id = MP4DMX_UNASSIGNED_TRACK_ID;
    s32     seek_direction = MP4DMX_SEEK_NORMAL;

    u64     next_offset=0;
    u64     time_stamp=0;

    MP4DMXMpoMp4TrackInf        trackInfo;
    MP4DMXMpoMp4HeaderInf       headerInfo;
    s32     track_cnt = 0;
    s32     dwPsetLength = 0;
    s32     first_flag = 1;
    s32     second_flag = 0;

    MP4DemuxCorePtr[threadnum]->cbsetfunc = (s32 (*)(MP4DMXFW_UNIT *, void *))(s32)ctrl_param->MP4DMXFW_CallbackSetData;
    MP4DemuxCorePtr[threadnum]->cbgetfunc = (s32 (*)(MP4DMXFW_UNIT *, void *))(s32)ctrl_param->MP4DMXFW_CallbackGetData;
    MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample = &MP4DemuxCorePtr[threadnum]->InputSample;
    MP4DemuxCorePtr[threadnum]->InputUnitPtr.bufsize = buf_size;
    MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset = next_offset;

    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample = &MP4DemuxCorePtr[threadnum]->OutputSample;
    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.bufsize = 0;
    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset = 0;

    iMlibRet        = MP4DemuxCorePtr[threadnum]->MP4DmxNewStatus;
    iMlibRet_tmp    = MP4DemuxCorePtr[threadnum]->MP4DmxOldStatus;
    next_size       = MP4DemuxCorePtr[threadnum]->MP4DmxAfterHeaderSize;
    next_offset     = MP4DemuxCorePtr[threadnum]->MP4DmxAfterHeaderOffset;
    first_flag      = MP4DemuxCorePtr[threadnum]->MP4DmxSeqFirstFlag;
    second_flag     = MP4DemuxCorePtr[threadnum]->MP4DmxSeqSecondFlag;

    while(1)
    {
        /****************************************************/
        /*                                                  */
        /*                  MP4 Container                   */
        /*                                                  */
        /****************************************************/
        if(iMlibRet != MP4DMX_RET_EXECUTE_NORMAL && iMlibRet != MP4DMX_RET_EXECUTE_WARNING)
        {
            if(next_size)
            {
                if (second_flag == 0)
                {
                    first_flag = 1;
                }
                if (next_size > (s32)DIVIDE_HEADSIZE)
                {
                    next_size = (s32)DIVIDE_HEADSIZE;
                }

//                LOG_WRITE("readfile, offset = 0x%016llX, length = %d\n",  next_offset, next_size);
                // call the input callback function of the media data
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size  = next_size;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.type          = MEDIA_HEADER;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type    = TRACK_TYPE_ANY;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.status        = 0;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset        = next_offset;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset  = 0;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size    = 0;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample = 1;
                MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum     = threadnum;

                ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                pData = (u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr;
                next_offset = MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset;

                if(ret == MP4DMXFW_RET_ERROR_SAMPLE_STOP)   // input termination
                {
                    return MP4DMXFW_RET_SUCCESS;
                }

                if(ret != MP4DMXFW_RET_SUCCESS)
                {
                    return MP4DMXFW_RET_ERROR;
                }
            }
        }

        switch(iMlibRet)
        {
            case MP4DMX_RET_FOUND_FTYP_BOX:
            case MP4DMX_RET_FOUND_MOOV_BOX:
            case MP4DMX_RET_FOUND_MOOF_BOX:
            case MP4DMX_RET_FOUND_MFRA_BOX:
            case MP4DMX_RET_FOUND_MFRO_BOX:
            case MP4DMX_RET_READ_HEADER:
            case MP4DMX_RET_INPUT_CONTINUE:

                if (first_flag == 1)
                {
                    iMlibRet_tmp = iMlibRet;
                }
                first_flag = 0;
                second_flag = 1;

                // ReadHeader
//                LOG_WRITE("begin MP4DMXReadHeader()\n");
                iMlibRet = MP4DMXReadHeader(pData, &time_stamp, &next_offset, &next_size, pMlibHandle);
//                LOG_WRITE("end MP4DMXReadHeader(), return value = %d, %s\n", iMlibRet, strRetVal[getReturnValue(iMlibRet)]);

                if (iMlibRet==MP4DMX_RET_INPUT_CONTINUE)    // input continue
                {
                    break;
                }
                second_flag = 0;

                if (iMlibRet_tmp == MP4DMX_RET_FOUND_MOOV_BOX)
                {
                    ret = MP4DMXGetHeaderInf(&headerInfo, pMlibHandle);
                    printHeaderInfo(&headerInfo);

                    for (track_cnt = 0; track_cnt < headerInfo.track_num; track_cnt++)
                    {
                        ret = MP4DMXGetTrackInf(track_cnt,&trackInfo, pMlibHandle);
                        printTrackInfo(&trackInfo);
                        if (trackInfo.type == MP4DMX_VIDEO_TRACK)
                        {
                            MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.v_track_id = trackInfo.track_ID;
                            ret = MP4DMXGetVideoTrackInf(trackInfo.track_ID, &MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf, pMlibHandle);
                            printVideoTrackInfo(&MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf);
                            MP4DemuxCorePtr[threadnum]->H264ImageWidth  = M_N_ALIGN_SIZE(MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.width, 16);
                            MP4DemuxCorePtr[threadnum]->H264ImageHeight = M_N_ALIGN_SIZE(MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.height, 16);
                            MP4DemuxCorePtr[threadnum]->H264Profile = MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.profile;
                            MP4DemuxCorePtr[threadnum]->H264Level   = (MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.level) & 0x00FF;
                        }
                        else if (trackInfo.type == MP4DMX_AUDIO_TRACK)
                        {
                            MP4DemuxCorePtr[threadnum]->MP4Dmx_CBHandle.a_track_id = trackInfo.track_ID;
                            ret = MP4DMXGetAudioTrackInf(trackInfo.track_ID, &MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf, pMlibHandle);
                            printAudioTrackInfo(&MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf);
                        }
                    }

                    // read H.264 SPS/PPS
                    if (MP4DemuxCorePtr[threadnum]->mp4VideoTrackInf.mediatype == MP4DMX_MEDIA_TYPE_AVC1)
                    {
                        memset(&MP4DemuxCorePtr[threadnum]->AVCconfig, 0, sizeof(MP4DMXAvcConfig));
                        ret = MP4DMXGetAVCSpecificInf (1, &MP4DemuxCorePtr[threadnum]->AVCconfig, pMlibHandle);
                        if (ret == MP4DMX_RET_SUCCESS)
                        {
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_sps; i ++)
                            {
                                dwPsetLength += MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length;
                                dwPsetLength += 3;      // 0x000001
                            }
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_pps; i ++)
                            {
                                dwPsetLength += MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length;
                                dwPsetLength += 3;      // 0x000001
                            }

                            pOutp = (u8 *)MP4DemuxCorePtr[threadnum]->H264HeaderBuffer;
                            // add the nal_unit_code
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_sps; i ++)
                            {
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x01;
                                // get SPS only
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size     = MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.type             = MEDIA_HEADER;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type       = TRACK_TYPE_ANY;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.status           = 0;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset           = MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].offset;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset     = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size       = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample    = 1;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum        = threadnum;

                                ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                                memcpy(pOutp, (u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr, MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length);
                                pOutp += MP4DemuxCorePtr[threadnum]->AVCconfig.SPS[i].length;
                            }
                            for(i = 0; i < MP4DemuxCorePtr[threadnum]->AVCconfig.number_of_pps; i ++)
                            {
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x00;
                                *pOutp++ = 0x01;
                                // get PPS only
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->size     = MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.type             = MEDIA_HEADER;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.track_type       = TRACK_TYPE_ANY;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.status           = 0;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.offset           = MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].offset;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_offset     = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.chunk_size       = 0;    // don't care
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.num_of_sample    = 1;
                                MP4DemuxCorePtr[threadnum]->InputUnitPtr.threadnum        = threadnum;

                                ret = MP4DemuxCorePtr[threadnum]->cbsetfunc(&MP4DemuxCorePtr[threadnum]->InputUnitPtr, NULL);

                                memcpy(pOutp, (u8 *)MP4DemuxCorePtr[threadnum]->InputUnitPtr.sample->data_ptr, MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length);
                                pOutp += MP4DemuxCorePtr[threadnum]->AVCconfig.PPS[i].length;
                            }

                            MP4DemuxCorePtr[threadnum]->H264HeaderSize = dwPsetLength;
                        }
                    }
                    else
                    {
                        return MP4DMX_RET_ERROR;
                    }
                }

                break;
            case MP4DMX_RET_FIND_HEADER:
            case MP4DMX_RET_NOT_FOUND_BOX:
                // get the offset of the header data
//                LOG_WRITE("begin MP4DMXFindHeader()\n");
                iMlibRet = MP4DMXFindHeader(pData,next_size,&next_offset,&next_size, pMlibHandle);
//                LOG_WRITE("end MP4DMXFindHeader(), return value = %d, %s\n",  iMlibRet, strRetVal[getReturnValue(iMlibRet)]);
                break;
            case MP4DMX_RET_EXECUTE_NORMAL:
            case MP4DMX_RET_EXECUTE_WARNING:
//                LOG_WRITE("begin MP4DMXExecute()\n");
                gMlibHandle[threadnum] = pMlibHandle;
                iMlibRet = MP4DMXExecute( NULL, control_flag, track_id,seek_direction,
                                end_time_stamp, &time_stamp, &next_offset, &next_size, pMlibHandle );
#if defined(USE_PROCESS_SWITCHING) && !defined(USE_SINGLE_CORE)
                exc_start_time_stamp[threadnum] = (s32)time_stamp;
#endif
                if (MP4DemuxCorePtr[threadnum]->SampleStop == 1)
                {
                    iMlibRet = MP4DMXFW_RET_SUCCESS;
                }
//                LOG_WRITE("end MP4DMXExecute(), return value = %d, %s\n",  iMlibRet, strRetVal[getReturnValue(iMlibRet)]);
                break;
            default:
                return MP4DMXFW_RET_SUCCESS;
        }

        if(iMlibRet <MP4DMX_RET_SUCCESS)
        {
            LOG_WRITE("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
            return MP4DMXFW_RET_ERROR;
        }

    }
}


/*-------------------------------------------------------------------------*
    Name:           MP4DMXFW_End
    Description:    End MP4 Demultiplexer framework
    Arguments:      <input>
                        handle              pointer to a handle MP4 Demultiplexer
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 MP4DMXFW_End(void *handle, s32 threadnum)
{
    s32     iMlibRet;

    /*************************************************************************/
    /*                                                                       */
    /*              End of the MP4 Demux.                                    */
    /*                                                                       */
    /*************************************************************************/

    iMlibRet = MP4DMXEnd( handle );
    if( iMlibRet != MP4DMX_RET_SUCCESS )
    {
        LOG_WRITE("MP4DMXEnd Failed. ret = %d\n", iMlibRet );
        return MP4DMXFW_RET_ERROR;
    }

    // decode the remaining data in the input ring buffers, and flush the decoded data
    {
        s32     i, j, k;
        s32     ret;
        u8 *pTmpp, *pOutp;
        s32     nal_unit_length;
        AACDEC_AAC_INFO aacinfo;
        s32     video_retry_flag;

        while (1)
        {
            if (MP4DemuxCorePtr[threadnum]->VideoTrackFound && MP4DemuxCorePtr[threadnum]->AudioTrackFound && (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos == MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos) && (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos == MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos))
            {
                break;
            }
            else if (MP4DemuxCorePtr[threadnum]->VideoTrackFound && !MP4DemuxCorePtr[threadnum]->AudioTrackFound && (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos == MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos))
            {
                break;
            }
            else if (!MP4DemuxCorePtr[threadnum]->VideoTrackFound && MP4DemuxCorePtr[threadnum]->AudioTrackFound && (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos == MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos))
            {
                break;
            }

            if (MP4DemuxCorePtr[threadnum]->VideoTrackFound)
            {
                if (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos != MP4DemuxCorePtr[threadnum]->VideoStreamInfo.wpos)
                   {
                    if (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos == VIDEO_BUFFER_NUM)
                    {
                        MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos = 0;
                    }

                    pTmpp = (u8 *)MP4DemuxCorePtr[threadnum]->VideoStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos];
                    pOutp = (u8 *)MP4DemuxCorePtr[threadnum]->H264BSBuffer;
                    nal_unit_length = 0;
                    for (i = 0, j = 0 ; i < MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Size[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos];)
                    {
                        for (k = 0; k < MP4DemuxCorePtr[threadnum]->AVCconfig.length_size; k++)
                        {
                            nal_unit_length <<= 8;
                            nal_unit_length |= pTmpp[i];
                            i++;
                        }
                        pOutp[j+0] = 0;
                        pOutp[j+1] = 0;
                        pOutp[j+2] = 1;
                        j += 3;
                        if ((j + nal_unit_length) > H264DEC_STREAMBUF_SIZE)
                        {
                            return MP4DMX_RET_ERROR;
                        }
                        memcpy(&pOutp[j], &pTmpp[i], nal_unit_length);
                        i += nal_unit_length;
                        j += nal_unit_length;
                    }

                    /****************************************************/
                    /*                                                  */
                    /*              H.264 Decoder Execute               */
                    /*                                                  */
                    /****************************************************/
                    ret = H264DECSetBitstream(MP4DemuxCorePtr[threadnum]->H264WorkBuffer, pOutp, j, (s32)MP4DemuxCorePtr[threadnum]->VideoStreamInfo.PTS[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos] + (s32)MP4DemuxCorePtr[threadnum]->VideoStreamInfo.CMP_OFFSET[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos] - (s32)MP4DemuxCorePtr[threadnum]->H264BpicTimeOffset);
                    if (ret != 0)
                    {
                        LOG_WRITE("error : bitstream set : 0x%x\n", ret);
                        return MP4DMX_RET_ERROR;
                    }

                    video_retry_flag = 1;
                    while (video_retry_flag)
                    {
                        ret = VideoPlayH264(threadnum);

                        // If there is no area in the output buffer, forced to perform image display
                        if (ret == -2)
                        {
                            // call the output callback function of the image data
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr = NULL;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size     = 0;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->pts      = 0;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.type             = MEDIA_SAMPLE;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.track_type       = TRACK_TYPE_ANY;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.status           = 0;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset           = 0;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_offset     = 0;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_size       = 0;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.num_of_sample    = 1;
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.threadnum        = threadnum;

                            do {
                                ret = MP4DemuxCorePtr[threadnum]->cbgetfunc(&MP4DemuxCorePtr[threadnum]->OutputUnitPtr, NULL);
                            } while (ret == MP4DMXFW_RET_WARNING_NOP);

                            if(ret != MP4DMXFW_RET_SUCCESS)
                            {
                                LOG_WRITE("Video GetCallBack Error\n");
                                return MP4DMXFW_RET_ERROR;
                            }
                        }
                        else
                        {
                            video_retry_flag = 0;
                        }
                    }

                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.Status[MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos] = 0;
                    MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos++;
                    if (MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos == VIDEO_BUFFER_NUM)
                    {
                        MP4DemuxCorePtr[threadnum]->VideoStreamInfo.rpos = 0;
                    }
                }
            }

            if (MP4DemuxCorePtr[threadnum]->AudioTrackFound)
            {
                if (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos != MP4DemuxCorePtr[threadnum]->AudioStreamInfo.wpos)
                {
                    if (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos == AUDIO_BUFFER_NUM)
                    {
                        MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos = 0;
                    }

                    if (MP4DemuxCorePtr[threadnum]->AACDecFirstFlag == 1)
                    {
                        MP4DemuxCorePtr[threadnum]->AACSampeRate = MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.sample_rate;
                        MP4DemuxCorePtr[threadnum]->AACChannelNum = MP4DemuxCorePtr[threadnum]->mp4AudioTrackInf.channel_count;
                    }

                    aacinfo.smp_freq_index = SMPiFreq2Index(MP4DemuxCorePtr[threadnum]->AACSampeRate); // sampling frequency index
                    aacinfo.channel        = MP4DemuxCorePtr[threadnum]->AACChannelNum;                // channel number
                    aacinfo.data_size      = MP4DemuxCorePtr[threadnum]->AudioStreamInfo.Size[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos];    // input aac bitstream size(byte)
                    ret = AACDECExecute((u8 *)MP4DemuxCorePtr[threadnum]->AudioStreamInfo.bufp[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos], (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer, (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer + AACDEC_PCM_SAMPLE_SIZE, &aacinfo, MP4DemuxCorePtr[threadnum]->AACWorkBuffer);
                    if(ret != AACDEC_NO_ERR)
                    {
                        LOG_WRITE("AAC Decode Error\n");
                        return MP4DMX_RET_ERROR;
                    }

                    // Frequency Convert
                    if (MP4DemuxCorePtr[threadnum]->AACSampeRate != 48000)
                    {
                        double  p_real, x_real;
                        double  convsample;
                        s32     x_pos;
                        s16     *inL, *inR;
                        s16     *outL, *outR;
                        s32     outsize;

                        convsample = 48000;
                        inL = (s16 *)MP4DemuxCorePtr[threadnum]->AACFreqConvTmpL;
                        inR = (s16 *)MP4DemuxCorePtr[threadnum]->AACFreqConvTmpR;
                        if (aacinfo.channel == 1)
                        {
                            outsize = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*((double)convsample/MP4DemuxCorePtr[threadnum]->AACSampeRate);
                            outsize = (outsize >> 1) << 1;
                            x_real = (double)MP4DemuxCorePtr[threadnum]->AACSampeRate/convsample;
                            outL  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                            outR  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer + outsize/2;

                            memcpy(inL, MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);
                            memcpy(MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, MP4DemuxCorePtr[threadnum]->AACOutBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);

                            // padding
                            inL[AACDEC_PCM_SAMPLE_SIZE] = *((s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer);

                            for (j = 0; j < outsize/2; j++)
                            {
                                x_pos = (s32)(j * x_real);
                                p_real = (j * x_real) - x_pos;
                                *outL++    = ((1 - p_real) * inL[x_pos]) + (p_real * inL[x_pos + 1]);
                            }
                        }
                        else
                        {
                            outsize = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*((double)convsample/MP4DemuxCorePtr[threadnum]->AACSampeRate)*2;
                            outsize = (outsize >> 2) << 2;
                            x_real = (double)MP4DemuxCorePtr[threadnum]->AACSampeRate/convsample;
                            outL  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                            outR  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer + outsize/4;

                            memcpy(inL, MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);
                            memcpy(inR, (s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer + AACDEC_PCM_SAMPLE_SIZE, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE);
                            memcpy(MP4DemuxCorePtr[threadnum]->AACOutRefBuffer, MP4DemuxCorePtr[threadnum]->AACOutBuffer, sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2);

                            // padding
                            inL[AACDEC_PCM_SAMPLE_SIZE] = *((s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer);
                            inR[AACDEC_PCM_SAMPLE_SIZE] = *((s16 *)MP4DemuxCorePtr[threadnum]->AACOutRefBuffer + AACDEC_PCM_SAMPLE_SIZE);
                            for (j = 0; j < outsize/4; j++)
                            {
                                x_pos = (s32)(j * x_real);
                                p_real = (j * x_real) - x_pos;
                                *outL++    = ((1 - p_real) * inL[x_pos]) + (p_real * inL[x_pos + 1]);
                                *outR++    = ((1 - p_real) * inR[x_pos]) + (p_real * inR[x_pos + 1]);
                            }
                        }
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr  = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size      = outsize;
                    }
                    else
                    {
                        MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->data_ptr    = (s16 *)MP4DemuxCorePtr[threadnum]->AACOutBuffer;
                        if (aacinfo.channel == 1)
                        {
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size    = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE;
                        }
                        else
                        {
                            MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->size    = sizeof(s16)*AACDEC_PCM_SAMPLE_SIZE*2;
                        }
                    }

                    // call the output callback function of the pcm data
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.sample->pts         = MP4DemuxCorePtr[threadnum]->AACRefPts;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.type                = MEDIA_SAMPLE;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.track_type          = TRACK_TYPE_AUDIO;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.status              = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.offset              = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_offset        = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.chunk_size          = 0;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.num_of_sample       = 1;
                    MP4DemuxCorePtr[threadnum]->OutputUnitPtr.threadnum           = threadnum;

                    MP4DemuxCorePtr[threadnum]->AACRefPts = MP4DemuxCorePtr[threadnum]->AudioStreamInfo.PTS[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos];

                    do {
                        ret = MP4DemuxCorePtr[threadnum]->cbgetfunc(&MP4DemuxCorePtr[threadnum]->OutputUnitPtr, NULL);
                        if (ret == MP4DMXFW_RET_WARNING_NOP)
                        {
                            OSYieldThread();
                        }
                    } while (ret == MP4DMXFW_RET_WARNING_NOP);

                    if(ret != MP4DMXFW_RET_SUCCESS)
                    {
                        OSYieldThread();
                        return MP4DMX_RET_ERROR;
                    }

                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.Status[MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos] = 0;
                    MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos++;
                    if (MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos == AUDIO_BUFFER_NUM)
                    {
                        MP4DemuxCorePtr[threadnum]->AudioStreamInfo.rpos = 0;
                    }
                }
            }
        }
    }

    if (MP4DemuxCorePtr[threadnum]->VideoTrackFound)
    {
        /*************************************************************************/
        /*                                                                       */
        /*              End of the H.264 Video Decoder.                          */
        /*                                                                       */
        /*************************************************************************/

        iMlibRet = H264DECEnd(MP4DemuxCorePtr[threadnum]->H264WorkBuffer);
        if( iMlibRet != 0 )
        {
            LOG_WRITE("H264DECEnd Failed. ret = %d\n", iMlibRet );
            return MP4DMXFW_RET_ERROR;
        }
    }

    return MP4DMXFW_RET_SUCCESS;
}


/*-------------------------------------------------------------------------*
    Name:           MP4DMXFW_Close
    Description:    Close each codec and release of each memory
    Arguments:      <input>
                        handle              pointer to a handle MP4 Demultiplexer
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 MP4DMXFW_Close(MEMHeapHandle ExpHeap, void *handle, s32 threadnum)
{
    s32     iMlibRet;

    if (MP4DemuxCorePtr[threadnum]->VideoTrackFound)
    {
        /*************************************************************************/
        /*                                                                       */
        /*              Close of the H.264 Video Decoder.                        */
        /*                                                                       */
        /*************************************************************************/

        iMlibRet = H264DECClose(MP4DemuxCorePtr[threadnum]->H264WorkBuffer);
        if( iMlibRet != 0 )
        {
            LOG_WRITE("H264DECClose Failed. ret = %d\n", iMlibRet );
            return MP4DMXFW_RET_ERROR;
        }
    }

    /*************************************************************************/
    /*                                                                       */
    /*              Close of the AAC Audio Decoder.                          */
    /*                                                                       */
    /*************************************************************************/

    iMlibRet = AACDECClose( MP4DemuxCorePtr[threadnum]->AACWorkBuffer );
    if( iMlibRet != AACDEC_NO_ERR )
    {
        LOG_WRITE("AACDECClose Failed. ret = %d\n", iMlibRet );
        return MP4DMXFW_RET_ERROR;
    }

    /*************************************************************************/
    /*                                                                       */
    /*              Close of the MP4 Demux.                                  */
    /*                                                                       */
    /*************************************************************************/

    iMlibRet = MP4DMXClose( handle, (void *)&MP4DemuxCorePtr[threadnum]->gAllocator );
    if( iMlibRet != MP4DMX_RET_SUCCESS )
    {
        LOG_WRITE("MP4DMXClose Failed. ret = %d\n", iMlibRet );
        return MP4DMXFW_RET_ERROR;
    }

    // release of each memory
    if (MP4DemuxCorePtr[threadnum]->H264BSBuffer != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->H264BSBuffer);
    }
    if (MP4DemuxCorePtr[threadnum]->H264HeaderBuffer != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->H264HeaderBuffer);
    }
    if (MP4DemuxCorePtr[threadnum]->AACOutBuffer != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->AACOutBuffer);
    }
    if (MP4DemuxCorePtr[threadnum]->AACBSBuffer != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->AACBSBuffer);
    }
    if (MP4DemuxCorePtr[threadnum]->AACWorkBuffer != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->AACWorkBuffer);
    }
    if (MP4DemuxCorePtr[threadnum]->AACFreqConvTmpL != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->AACFreqConvTmpL);
    }
    if (MP4DemuxCorePtr[threadnum]->AACFreqConvTmpR != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->AACFreqConvTmpR);
    }
    if (MP4DemuxCorePtr[threadnum]->AACOutRefBuffer != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->AACOutRefBuffer);
    }
    if (MP4DemuxCorePtr[threadnum] != NULL)
    {
        MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]);
    }

    return MP4DMXFW_RET_SUCCESS;
}
