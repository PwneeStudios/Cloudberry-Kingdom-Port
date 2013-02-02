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
#include <cafe/h264.h>
#include "videorender.h"
#include "MovieTest.h"


/*=========================================================================*
            definitions
 *=========================================================================*/

// For Debug
//#define PRINT_TIME


/*=========================================================================*
            external functions
 *=========================================================================*/

extern s32 H264Dec_Output(void  *ptr);


/*=========================================================================*
            external variables
 *=========================================================================*/

extern MP4PlayerCore    *MP4PlayerCorePtr[];
extern MP4DemuxCore     *MP4DemuxCorePtr[];


/*=========================================================================*
            prototype
 *=========================================================================*/

static s32 set_parameters(s32 memory_size, void *mem_ptr, void **usermem, s32 threadnum);


/*-------------------------------------------------------------------------*
    Name:           VideoDraw
    Description:    draw video frame
    Arguments:      <input>
                        ip                  frame buffer pointer
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 VideoDraw(u8 *ip, s32 threadnum)
{
    s32     i;

    if ((MP4DemuxCorePtr[threadnum]->H264ImageWidth * MP4DemuxCorePtr[threadnum]->H264ImageHeight)*3/2 > VIDEO_MAX_IMAGE_SIZE)
    {
        OSReport("[VideoDraw Fail] Width:%d, Height:%d\n", MP4DemuxCorePtr[threadnum]->H264ImageWidth, MP4DemuxCorePtr[threadnum]->H264ImageHeight);
        return -1;
    }

    if (MP4PlayerCorePtr[threadnum]->OutputFrames == 0)
    {
        OSReport("Movie size : %d x %d\n", MP4DemuxCorePtr[threadnum]->H264ImageWidth, MP4DemuxCorePtr[threadnum]->H264ImageHeight);
    }

    {
#ifdef PRINT_TIME
        s32 starttime, endtime;
#endif
        u32 y_size = ((UVD_ALIGN_PITCH_IN_PIXELS(MP4DemuxCorePtr[threadnum]->H264ImageWidth))*MP4DemuxCorePtr[threadnum]->H264ImageHeight);
        GX2InitTexturePtrs(&g_LTexture[threadnum], ip, 0);
        GX2InitTexturePtrs(&g_UVTexture[threadnum], (void*)(ip+y_size), 0);
        if (threadnum == 0)
        {
            drawTVFrame(0);
        }
        else
        {
            drawDRCFrame();
        }
        DEMODRCBeforeRender();
        DEMODRCDoneRender();
#ifdef PRINT_TIME
        starttime = OSTicksToMilliseconds(OSGetTime());
#endif
#ifdef PRINT_TIME
        endtime = OSTicksToMilliseconds(OSGetTime());
        OSReport("Time(VideoDraw):%d, thread:%d\n", endtime - starttime, threadnum);
#endif
        DEMOGfxDoneRender();
        DEMOGfxBeforeRender();
    }

    for(i = 0; i < MAX_FRAME_BUFFER; i++)
    {
        if(MP4PlayerCorePtr[threadnum]->List_h264decfm[i].used && MP4PlayerCorePtr[threadnum]->List_h264decfm[i].h264decfm==(void *)ip)
        {
            MP4PlayerCorePtr[threadnum]->List_h264decfm[i].used = 0;
            break;
        }
        
    }

    return 0;
}


s32 VideoDrawFirst(u8 *ip, s32 threadnum)
{
    if ((MP4DemuxCorePtr[threadnum]->H264ImageWidth * MP4DemuxCorePtr[threadnum]->H264ImageHeight)*3/2 > VIDEO_MAX_IMAGE_SIZE)
    {
        OSReport("[VideoDraw Fail] Width:%d, Height:%d\n", MP4DemuxCorePtr[threadnum]->H264ImageWidth, MP4DemuxCorePtr[threadnum]->H264ImageHeight);
        return -1;
    }

    if (MP4PlayerCorePtr[threadnum]->OutputFrames == 0)
    {
        OSReport("Movie size : %d x %d\n", MP4DemuxCorePtr[threadnum]->H264ImageWidth, MP4DemuxCorePtr[threadnum]->H264ImageHeight);
    }

    {
#ifdef PRINT_TIME
        s32 starttime, endtime;
#endif
        u32 y_size = ((UVD_ALIGN_PITCH_IN_PIXELS(MP4DemuxCorePtr[threadnum]->H264ImageWidth))*MP4DemuxCorePtr[threadnum]->H264ImageHeight);
        GX2InitTexturePtrs(&g_LTexture[threadnum], ip, 0);
        GX2InitTexturePtrs(&g_UVTexture[threadnum], (void*)(ip+y_size), 0);
        if (threadnum == 0)
        {
            drawTVFrame(0);
        }
        else
        {
            drawDRCFrame();
        }
        DEMODRCBeforeRender();
        DEMODRCDoneRender();
#ifdef PRINT_TIME
        starttime = OSTicksToMilliseconds(OSGetTime());
#endif
#ifdef PRINT_TIME
        endtime = OSTicksToMilliseconds(OSGetTime());
        OSReport("Time(VideoDraw):%d, thread:%d\n", endtime - starttime, threadnum);
#endif
        DEMOGfxDoneRender();
        DEMOGfxBeforeRender();
    }

    return 0;
}


/*-------------------------------------------------------------------------*
    Name:           DrawScreen
    Description:    draw video frame
    Arguments:      <input>
                        ip                  frame buffer pointer
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 DrawScreen(s32 threadnum)
{
    drawTVFrame(0);
    DEMODRCBeforeRender();
    DEMODRCDoneRender();
    DEMOGfxDoneRender();
    DEMOGfxBeforeRender();

    return 0;
}


/*-------------------------------------------------------------------------*
    Name:           video_Output
    Description:    video frame output callback
    Arguments:      <input>
                        ptr                 frame buffer pointer
    Returns:        0            Success
                    -1           Error
 *-------------------------------------------------------------------------*/
s32 video_Output(void *ptr)
{
    s32     ret;
    s32     threadnum;
    H264DECOutput       *h264decoutput = (H264DECOutput *) ptr;

    threadnum = *(s32 *)h264decoutput->UserMemory;
    if ((threadnum != 0) && (threadnum != 1))
    {
        OSReport("video_Output Error : Invalid Thread Number\n");
        return -1;
    }

    ret = H264Dec_Output(ptr);
    if (ret != 0)
    {
        return ret;
    }

    MP4PlayerCorePtr[threadnum]->OutputFrames++;

    return 0;
}


/*-------------------------------------------------------------------------*
    Name:           set_parameters
    Description:    
    Arguments:      <input>
                        memory_size         workbuffer size
                        mem_ptr             workbuffer pointer
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 set_parameters(s32 memory_size, void *mem_ptr, void **usermem, s32 threadnum)
{
    s32     ret;

    /* initialize parameters by default value */
    ret = H264DECInitParam(memory_size, mem_ptr);
    if (ret != 0)
    {
        OSReport("Error : H264DECInitParam : 0x%x\n", ret);
        return ret;
    }

    /* set H264DEC_PARAM_ID_FPTR_OUTPUT */
    ret = H264DECSetParam_FPTR_OUTPUT( mem_ptr, video_Output );
    if (ret != 0)
    {
        OSReport("Error : H264DECSetParam_FPTR_OUTPUT : 0x%x\n", ret);
        return ret;
    }

    /* set H264DEC_PARAM_ID_OUTPUT_MODE */
    if (threadnum == 0)
    {
        ret = H264DECSetParam_OUTPUT_PER_FRAME(mem_ptr, BUFFERING_OUTPUT_PER_FRAME);
    }
    else
    {
        ret = H264DECSetParam_OUTPUT_PER_FRAME(mem_ptr, BUFFERING_OUTPUT_PER_FRAME);
    }
    if (ret != 0)
    {
        OSReport("Error : H264DECSetParam_OUTPUT_PER_FRAME : 0x%x\n", ret);
        return ret;
    }

    /* set H264DEC_PARAM_ID_USER_MEMORY */
    ret = H264DECSetParam_USER_MEMORY(mem_ptr, usermem);
    if (ret != 0)
    {
        OSReport("Error : H264DECSetParam[H264DEC_PARAM_ID_USER_MEMORY] : 0x%x\n", ret);
        return ret;
    }

    return 0;
}


/*-------------------------------------------------------------------------*
    Name:           VideoOpenH264
    Description:    
    Arguments:      none
    Returns:        MP4DMXFW_RET_SUCCESS    Success
                    MP4DMXFW_RET_ERROR      Error
 *-------------------------------------------------------------------------*/
s32 VideoOpenH264(s32 threadnum)
{
    s32     rtn;
    s32     codec_mem_size;
    void    *ngptr[16];
    s32     i, ngptrnum;

    rtn = H264DECMemoryRequirement( MP4DemuxCorePtr[threadnum]->H264Profile, MP4DemuxCorePtr[threadnum]->H264Level, MP4DemuxCorePtr[threadnum]->H264ImageWidth, MP4DemuxCorePtr[threadnum]->H264ImageHeight, &codec_mem_size  );
//    rtn = H264DECMemoryRequirement( MP4DemuxCorePtr[threadnum]->H264Profile, 51, MP4DemuxCorePtr[threadnum]->H264ImageWidth, MP4DemuxCorePtr[threadnum]->H264ImageHeight, &codec_mem_size  );
    if (rtn != 0)
    {
        OSReport("error : H264DECMemoryRequirement : 0x%x\n", rtn);
        return MP4DMXFW_RET_ERROR;
    }

    ngptrnum = 0;
    while (1)
    {
        MP4DemuxCorePtr[threadnum]->H264WorkBuffer = MEMAllocFromDefaultHeapEx(codec_mem_size, 512);
        if (H264DECCheckMemSegmentation(MP4DemuxCorePtr[threadnum]->H264WorkBuffer, codec_mem_size) != 0)
        {
            ngptr[ngptrnum] = MP4DemuxCorePtr[threadnum]->H264WorkBuffer;
            OSReport("H264WorkBuffer malloc retry : 0x%x-0x%x, threadnum : %d,\n", (s32)ngptr[ngptrnum], (s32)ngptr[ngptrnum] + codec_mem_size - 1, threadnum);
            ngptrnum++;
            if (ngptrnum == 16)
            {
                for (i = 0; i < 16; i++)
                {
                    MEMFreeToDefaultHeap(ngptr[i]);
                }
                ngptrnum = 0;
            }
        }
        else
        {
            break;
        }
    }

    for (i = 0; i < ngptrnum; i++)
    {
        MEMFreeToDefaultHeap(ngptr[i]);
    }

    if (MP4DemuxCorePtr[threadnum]->H264WorkBuffer == NULL)
    {
        OSReport("error : MP4DemuxCorePtr[threadnum]->H264WorkBuffer Alloccate : %d \n", codec_mem_size);
        return MP4DMXFW_RET_ERROR;
    }

    MP4DemuxCorePtr[threadnum]->threadnumforh264 = threadnum;
    MP4DemuxCorePtr[threadnum]->UserMem = (void *)&MP4DemuxCorePtr[threadnum]->threadnumforh264;
    rtn = set_parameters(codec_mem_size, MP4DemuxCorePtr[threadnum]->H264WorkBuffer, &MP4DemuxCorePtr[threadnum]->UserMem, threadnum);
    if (rtn != 0)
    {
        OSReport("error : H.264 Video set_parameters : 0x%x\n", rtn);
        return MP4DMXFW_RET_ERROR;
    }

    rtn = H264DECOpen(MP4DemuxCorePtr[threadnum]->H264WorkBuffer);
    if (rtn != 0)
    {
        OSReport("error : H264DECOpen : 0x%x\n", rtn);
        return MP4DMXFW_RET_ERROR;
    }

    return MP4DMXFW_RET_SUCCESS;
}


/*-------------------------------------------------------------------------*
    Name:           CheckVideoBuffer
    Description:    
    Arguments:      none
    Returns:        0                       Success
                    out of zero             Error
 *-------------------------------------------------------------------------*/
 s32 CheckVideoBuffer(s32 threadnum)
{
    s32     i;
    void    *throw_264decfm = NULL;

    for(i = 0; i < MAX_FRAME_BUFFER; i++)
    {
        if(MP4PlayerCorePtr[threadnum]->List_h264decfm[i].used == 0)
        {
            return 0;
        }
    }
    if (throw_264decfm == NULL)
    {
        return -2;
    }

    return -1;
}


/*-------------------------------------------------------------------------*
    Name:           VideoPlayH264
    Description:    
    Arguments:      none
    Returns:        0                       Success
                    out of zero             Error
 *-------------------------------------------------------------------------*/
s32 VideoPlayH264(s32 threadnum)
{
    s32     i;
    s32     ret;

    MP4DemuxCorePtr[threadnum]->curr_throw_264decfm = NULL;
    for(i = 0; i < MAX_FRAME_BUFFER; i++)
    {
        if(MP4PlayerCorePtr[threadnum]->List_h264decfm[i].used == 0)
        {
            MP4DemuxCorePtr[threadnum]->curr_throw_264decfm = MP4PlayerCorePtr[threadnum]->List_h264decfm[i].h264decfm;
            MP4PlayerCorePtr[threadnum]->List_h264decfm[i].used = 1;
            break;
        }
    }
    if (MP4DemuxCorePtr[threadnum]->curr_throw_264decfm == NULL)
    {
        return -2;
    }

    ret = H264DECExecute(MP4DemuxCorePtr[threadnum]->H264WorkBuffer, MP4DemuxCorePtr[threadnum]->curr_throw_264decfm);

    //not use FM
    if(!(ret & H264DEC_ERR_USE_FM))
    {
        for(i = 0;i < MAX_FRAME_BUFFER; i++)
        {
            if(MP4PlayerCorePtr[threadnum]->List_h264decfm[i].h264decfm == MP4DemuxCorePtr[threadnum]->curr_throw_264decfm)
            {
                MP4PlayerCorePtr[threadnum]->List_h264decfm[i].used = 0;
                break;
            }
        }
        ret &= ~H264DEC_ERR_FM_STAT;
        return ret;
    }

    return ret;
}


/*-------------------------------------------------------------------------*
    Name:           VideoInit
    Description:    
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
s32 VideoInit(s32 threadnum)
{
    s32     i, j;
    s32     YuvBufSize;
    void    *ngptr[16];
    s32     ngptrnum;

    MP4PlayerCorePtr[threadnum]->OutputFrames = 0;
    MP4PlayerCorePtr[threadnum]->RenderSwitch = 0;

    YuvBufSize = (((UVD_ALIGN_PITCH_IN_PIXELS(MP4DemuxCorePtr[threadnum]->H264ImageWidth))*MP4DemuxCorePtr[threadnum]->H264ImageHeight*3)/2 + UVD_BUFFER_PAD);
    MP4PlayerCorePtr[threadnum]->UVDOutFrameSize = (u32)(((YuvBufSize + (UVD_BUFFER_ALIGNMENT - 1)) / UVD_BUFFER_ALIGNMENT))*UVD_BUFFER_ALIGNMENT;

    ngptrnum = 0;
    for (i = 0; i < MAX_FRAME_BUFFER; i++)
    {
        MP4PlayerCorePtr[threadnum]->h264decfm[i] = MEMAllocFromDefaultHeapEx(YuvBufSize, UVD_BUFFER_ALIGNMENT);
        if (H264DECCheckMemSegmentation(MP4PlayerCorePtr[threadnum]->h264decfm[i], YuvBufSize) != 0)
        {
            ngptr[ngptrnum] = MP4PlayerCorePtr[threadnum]->h264decfm[i];
            OSReport("h264decfm malloc retry : 0x%x-0x%x, threadnum : %d,\n", (s32)ngptr[ngptrnum], (s32)ngptr[ngptrnum] + YuvBufSize - 1, threadnum);
            ngptrnum++;
            if (ngptrnum == 16)
            {
                for (j = 0; j < 16; j++)
                {
                    MEMFreeToDefaultHeap(ngptr[j]);
                }
                ngptrnum = 0;
            }
            i -= 1;
        }
        else
        {
        if (MP4PlayerCorePtr[threadnum]->h264decfm[i] == NULL)
        {
            OSReport("cannot allocate framebuffer\n");
            return MP4DMXFW_RET_ERROR;
        }
        MP4PlayerCorePtr[threadnum]->List_h264decfm[i].used = 0;
        MP4PlayerCorePtr[threadnum]->List_h264decfm[i].h264decfm = MP4PlayerCorePtr[threadnum]->h264decfm[i];
        }
    }

    for (i = 0; i < ngptrnum; i++)
    {
        MEMFreeToDefaultHeap(ngptr[i]);
    }

    // VideoBuffer setting
    for (i = 0; i < VIDEO_BUFFER_NUM; i++)
    {
        MP4PlayerCorePtr[threadnum]->OutputVideoInfo[i].PTS  = 0;
        MP4PlayerCorePtr[threadnum]->OutputVideoInfo[i].Size = 0;
        MP4PlayerCorePtr[threadnum]->OutputVideoInfo[i].Status = 0;
    }

    InitVideoBuffer(threadnum, MP4DemuxCorePtr[threadnum]->H264ImageWidth, MP4DemuxCorePtr[threadnum]->H264ImageHeight);

    return 0;
}


/*-------------------------------------------------------------------------*
    Name:           VideoExit
    Description:    
    Arguments:      none
    Returns:        none
 *-------------------------------------------------------------------------*/
void VideoExit(s32 threadnum)
{
    s32 i;

    if (MP4DemuxCorePtr[threadnum]->VideoTrackFound)
    {
        if (MP4DemuxCorePtr[threadnum]->H264WorkBuffer != NULL)
        {
            MEMFreeToDefaultHeap(MP4DemuxCorePtr[threadnum]->H264WorkBuffer);
        }
        for (i = 0; i < MAX_FRAME_BUFFER; i++)
        {
            if (MP4PlayerCorePtr[threadnum]->h264decfm[i] != NULL)
            {
                MEMFreeToDefaultHeap(MP4PlayerCorePtr[threadnum]->h264decfm[i]);
            }
        }

        OSReport("Video Shut down completed\r");
    }
    return;
}
