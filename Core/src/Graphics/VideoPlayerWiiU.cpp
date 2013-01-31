#include <Graphics/VideoPlayer.h>

#include <Core.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/TextureWiiUInternal.h>
#include <Content/Wad.h>
#include <Graphics/Video.h>
#include <Graphics/Texture2D.h>

/*---------------------------------------------------------------------------*

  Copyright 2010-2011 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

 *---------------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////
//
// Draws a color-interpolated triangle.
// Changes the background color to show its liveliness.
//
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include <cafe/demo.h>
#include <cafe/gx2.h>
#include <cafe/vpad.h>
#include <cafe/fs.h>
#include <cafe/procui.h>

#include <cafe/h264.h>
#include "WiiU/h264render.h"

#include <fmod.hpp>
#include <fmod_errors.h>

#define DEF_PLAY_LOOP   (1)     // for test

#define UVD_ALIGN_PITCH_IN_PIXELS(PitchInPixels)    ((PitchInPixels + 0xFF) & ~0xFF)
#define UVD_BUFFER_ALIGNMENT           (1024)
#define UVD_BUFFER_PAD                 (0)

#define NUM_THREADS  (1)
#define STACK_SIZE   (4096*1024)

#define TV_THREAD_NUMBER    (0)
#define DRC_THREAD_NUMBER   (1)

#define MAX_LAST_IDR    (5)

const char INPUT_FILENAME_TV[] = "/vol/content/Movies/Video.h264";
const char INPUT_SOUND[] = "/vol/content/Movies/Sound.mp3";
const char INPUT_FILENAME_DRC[] = "./vol/content/codecdemo/building.h264";

// bitstream buffer size
#define BUFFER_SIZE             ((s32)(62500*12))
#define MAX_FRAME_BUFFER        (24)

//#define DO_BENCHMARK            (1)

typedef struct __CALLBACK_USERMEM__ {
    s32     decIdx;
    s32     skip;
    s32     bufcnt;
}CALLBACK_USERMEM;

static u8 g_SkipH264Rendering = 1;

static H264DECResult g_H264decresult[NUM_DECODE][MAX_FRAME_BUFFER];
static H264DECOutput g_H264decoutput[NUM_DECODE];

static boost::shared_ptr< Texture2D > VideoTextures[ NUM_DECODE ][ NUM_H264_BUFFER ];
static ResourcePtr< Texture > TextureResourcePtrs[ NUM_DECODE ][ NUM_H264_BUFFER ];

typedef struct __LIST_H264DEC_FM__ {
    s32     used;
    void   *h264decfm;
}List_H264DecFm;

List_H264DecFm List_h264decfm[NUM_DECODE][MAX_FRAME_BUFFER];

// Sound stuff.
extern FMOD::System *FMODSystem;
FMOD::Channel *MovieChannel = NULL;
FMOD::Sound *MovieSound = NULL;
static float Volume = 1.f;

/*************************************************************
        variables
 *************************************************************/
static u32              OutputFrames[2] = {0, 0};

void    set_parameters(
        s32     memory_size,
        void    *mem_ptr,
        void    *usermem
    );

void set_side_panel_y(
        u8 *buf,
        s32 width,
        s32 height,
        s32 left,
        s32 right,
        s32 nextLine
        )
{
    s32 h, l, r;
    for(h=0;h<height;h++)
    {
        for(l=0;l<left;l++)
        {
            buf[h*nextLine+l] = 0;
        }
        for(r=0;r<right;r++)
        {
            buf[h*nextLine+width-r-1] = 0;
        }
    }
}

void set_side_panel_uv(
        u8 *buf,
        s32 width,
        s32 height,
        s32 left,
        s32 right,
        s32 nextLine
        )
{
    s32 h, l, r;
    for(h=0;h<height/2;h++)
    {
        for(l=0;l<left;l++)
        {
            buf[h*nextLine+l] = 128;
        }
        for(r=0;r<right;r++)
        {
            buf[h*nextLine+width-r-1] = 128;
        }
    }
}

/* ----------------------------------------------------------
        Function Name   : draw setup
 ----------------------------------------------------------*/

void SetupH264Draw(u8 decIdx)
{
    s32                 width;
    s32                 height;
    H264DECOutput       *h264decoutput;
    H264DECResult       *h264decresult;
    s32 i;
    s32 fmcnt;
    u8 writeBufIdx;

    writeBufIdx = g_H264WriteBufIdx[decIdx]
                = (g_H264WriteBufIdx[decIdx] == 0)? 1 : 0;

    h264decoutput = &g_H264decoutput[decIdx];
    h264decresult = g_H264decresult[decIdx];

    if(h264decresult[0].CropEnableFlag)
    {
        s32 top_offset, bottom_offset;
        s32 left_offset, right_offset;
        s32 crop_width, crop_height;

        top_offset = h264decresult[0].TopCrop;
        bottom_offset =  h264decresult[0].BottomCrop;

        left_offset = h264decresult[0].LeftCrop;
        right_offset = h264decresult[0].RightCrop;

        // new width and height 
        crop_width = h264decresult[0].ResultWidth - left_offset - right_offset;
        crop_height = h264decresult[0].ResultHeight - top_offset - bottom_offset;

        width = crop_width;
        height = crop_height;
    }
    else
    {
        width = h264decresult[0].ResultWidth;
        height = h264decresult[0].ResultHeight;
    }

    if(OutputFrames[decIdx] == 0)
    {
        printf("Movie size : %d x %d\n", width, height);
    }

    for(fmcnt=0;fmcnt<h264decoutput->FmCnt;fmcnt++)
    {

        // set up TV frame buffer
        u32 y_size = ((UVD_ALIGN_PITCH_IN_PIXELS(width))* h264decresult[0].ResultHeight);
        u32 nextline = (UVD_ALIGN_PITCH_IN_PIXELS(width));

        if( (width != g_LTexture[decIdx][writeBufIdx].surface.width) ||
            (height != g_LTexture[decIdx][writeBufIdx].surface.height) )
        {
            InitVideoBuffer(decIdx, writeBufIdx, width, height);
        }

        // Pan-scan
        if(h264decresult[fmcnt].PanScanEnableFlag)
        {
            s32 left, right;

            left = h264decresult[fmcnt].LeftPanScan/16;
            right = -h264decresult[fmcnt].RightPanScan/16;

            set_side_panel_y( (u8*)h264decresult[fmcnt].Result, width, height, left, right, nextline);

            set_side_panel_uv( (u8*)h264decresult[fmcnt].Result+y_size, width, height, left, right, nextline);

            DCFlushRange( h264decresult[fmcnt].Result, y_size*3/2);
        }

        g_LTexture[decIdx][writeBufIdx].surface.width = width;
        g_LTexture[decIdx][writeBufIdx].surface.height = height;

        GX2InitTexturePtrs(&g_LTexture[decIdx][writeBufIdx], h264decresult[fmcnt].Result, 0);
        GX2InitTexturePtrs(&g_UVTexture[decIdx][writeBufIdx], (void*)(h264decresult[fmcnt].Result+y_size), 0);

    
        for(i=0;i<MAX_FRAME_BUFFER;i++)
        {
            if(List_h264decfm[decIdx][i].used && ( List_h264decfm[decIdx][i].h264decfm == h264decresult[fmcnt].Result ) )
            {
                List_h264decfm[decIdx][i].used = 0;
                break;
            }
        }

        OutputFrames[decIdx]++;
    }
}

/* ----------------------------------------------------------
        Function Name   : tst_Output
 ----------------------------------------------------------*/

s32 h264DecodeCallback( void *ptr )
{
    u32 fmcnt;
    u8 decIdx;
    H264DECOutput *h264decoutput;
    H264DECResult **h264decresult;
    CALLBACK_USERMEM *callback_usermem;

    g_SkipH264Rendering = 0;

    h264decoutput = (H264DECOutput *) ptr;
    h264decresult = ((H264DECOutput *) ptr)->DecResPtr;

    callback_usermem = reinterpret_cast< CALLBACK_USERMEM * >( h264decoutput->UserMemory );
    decIdx = callback_usermem->decIdx;

    OSBlockMove( &g_H264decoutput[decIdx], ptr, sizeof(H264DECOutput), FALSE );

    for(fmcnt=0;fmcnt<g_H264decoutput[decIdx].FmCnt;fmcnt++)
    {
        OSBlockMove( &g_H264decresult[decIdx][fmcnt], h264decresult[fmcnt], sizeof(H264DECResult), FALSE );
//        OSBlockMove( &g_Vuiparameters[decIdx][fmcnt], h264decresult[fmcnt]->VUIparameters, sizeof(VUIParameters), FALSE );   
    }
    
    return 0;
}

////////////////////////////////////////////////////
// Main
////////////////////////////////////////////////////

static int decode_h264(s32 intArg, void *ptrArg)
{

    do{
        s32         bytes_read;
        s32         additional_read;
        void        *mem_ptr;
        s32         byte_cnt = 0;
        s32         length = 0;
        s32         rtn;
        s32         ret;
        u8          *rbuf;
        s32         width, height;
        s32         codec_mem_size;
        s32         i;
        f64         time_stamp = 0.0;
        s32         level = 41;
        s32         profile = H264_HIGH_PROFILE;
        FSFilePosition fpos = 0;
        void        *ngmem[MAX_FRAME_BUFFER] = {0};

        int h264count = 0;

        FSClient __our_FS_Client;
        FSFileHandle input_handle;
        FSStatus retFSStatus;
        FSCmdBlock                          Cmd;
#ifdef DO_BENCHMARK
        OSTime                              startTime;
#endif
        OSTime                              endTime, prevendTime;
        CALLBACK_USERMEM                    callback_usermem;
        int                                 next_fpos = 0;

        callback_usermem.decIdx = intArg;

        OSReport("decode_h264 thread\n");

        prevendTime = OSGetTime();

		// Prepare sound for playback.
		FMOD_RESULT result;
		result = FMODSystem->createStream( INPUT_SOUND, FMOD_DEFAULT, 0, &MovieSound );
		if( result != FMOD_OK )
		{
			printf( "Failed to start movie soundtrack\n" );
			MovieSound = NULL;
		}

        FSInitCmdBlock(&Cmd);

        rbuf = (u8*)MEMAllocFromDefaultHeapEx(BUFFER_SIZE, 512);

        if(rbuf==NULL)
        {
            printf("error : MEMAllocFromDefaultHeapEx");
            return -1;
        }

        retFSStatus = FSAddClient(&__our_FS_Client, FS_RET_NO_ERROR);

        if(retFSStatus!=FS_STATUS_OK)
        {
            printf("error : FSAddClient : 0x%x\n", retFSStatus);
            return -1;
        }

        if(intArg==DRC_THREAD_NUMBER)
            retFSStatus = FSOpenFile(&__our_FS_Client, &Cmd, INPUT_FILENAME_DRC, "r", &input_handle, FS_RET_NO_ERROR);
        else
            retFSStatus = FSOpenFile(&__our_FS_Client, &Cmd, INPUT_FILENAME_TV, "r", &input_handle, FS_RET_NO_ERROR);

        if(retFSStatus!=FS_STATUS_OK)
        {
            printf("error : FSOpenFile : 0x%x\n", retFSStatus);
            return -1;
        }

        additional_read = 0;
        s32     ret_find;

        if (additional_read == 0)
        {
            byte_cnt = 0;
            length = 0;

            retFSStatus = FSReadFile(&__our_FS_Client, &Cmd, rbuf, 1, BUFFER_SIZE, input_handle, 0, FS_RET_NO_ERROR);

            if(retFSStatus>0)
            {
                additional_read = retFSStatus;
                bytes_read = retFSStatus;
            }
        }

        rtn = H264DECMemoryRequirement( profile, level, 1920, 1088, &codec_mem_size  );
        if (rtn != 0)
        {
            printf("error : H264DECMemoryRequirement : 0x%x\n", rtn);
            return -1;
        }
        else
        {
            printf("H264DECMemoryRequirement codec_mem_size:%d \n", codec_mem_size);
        }

#define H264_MAX_ALLOC_ATTEMPTS (10) 
        i = 0;
        for (i=0; i<H264_MAX_ALLOC_ATTEMPTS; i++) 
        {
            mem_ptr = MEMAllocFromDefaultHeapEx(codec_mem_size, 512);
            printf("alloc:0x%X, size:%d\n", mem_ptr, codec_mem_size);
            if(mem_ptr == NULL)
            {
                printf("error : MEMAllocFromDefaultHeapEx codec_mem_size");
                return -1;
            }
            if(H264DECCheckMemSegmentation(mem_ptr, codec_mem_size)!=0)
            {
                ngmem[i] = mem_ptr;
            }
            else
            {
                break;
            }
        }

        for(i=0;i<MAX_FRAME_BUFFER;i++)
        {
            if(ngmem[i])
            {
                MEMFreeToDefaultHeap(ngmem[i]);
                ngmem[i] = 0;
            }
        }

        set_parameters(codec_mem_size, mem_ptr, &callback_usermem);

        rtn = H264DECOpen(mem_ptr);
        if (rtn != 0)
        {
            printf("error : video open : 0x%x\n", rtn);
            return -1;
        }

        // find decode start point 
        while (1)
        {
            ret_find = H264DECFindDecstartpoint(rbuf, bytes_read, &byte_cnt);

            if (ret_find)
            {
                memcpy(rbuf, rbuf+bytes_read-4, 4);
                bytes_read = 4;

                additional_read = FSReadFile(&__our_FS_Client, &Cmd, rbuf+4, 1, BUFFER_SIZE-4, input_handle, 0, FS_RET_NO_ERROR);
                if(additional_read<0)
                {
                    printf("error :FSReadFile : 0x%x\n", additional_read);
                    additional_read = 0;
                    return -1;
                }
                bytes_read += additional_read;

                if (additional_read == 0)
                {
                    additional_read = FSReadFile(&__our_FS_Client, &Cmd, rbuf, 1, BUFFER_SIZE, input_handle, 0, FS_RET_NO_ERROR);
                    bytes_read = additional_read;
                }
                else
                {
                    byte_cnt = 0;
                }

            }
            if (ret_find == 0) break;   // found decode start point 
        }

        rtn = H264DECBegin(mem_ptr);
        if (rtn != 0)
        {
            printf("error : video begin : 0x%x\n", rtn);
            return -1;
        }

        rtn = H264DECGetImageSize( rbuf, bytes_read, byte_cnt, &width, &height);
        // set up TV frame buffer
        for(i=0; i<NUM_H264_BUFFER; i++)
            InitVideoBuffer( intArg, i , width, height);

        for(i=0;i<MAX_FRAME_BUFFER;i++)
        {
             List_h264decfm[intArg][i].h264decfm =
                MEMAllocFromDefaultHeapEx((UVD_ALIGN_PITCH_IN_PIXELS(width)*height*3/2 + UVD_BUFFER_PAD), UVD_BUFFER_ALIGNMENT);
            if(List_h264decfm[intArg][i].h264decfm==NULL)
            {
                printf("error : MEMAllocFromDefaultHeapEx");
                return -1;
            }
            List_h264decfm[intArg][i].used = 0;


            if(H264DECCheckMemSegmentation(List_h264decfm[intArg][i].h264decfm, (UVD_ALIGN_PITCH_IN_PIXELS(width)*height*3/2 + UVD_BUFFER_PAD))!=0)
            {
                printf("fm no.%d\n",i);
                ngmem[i] = List_h264decfm[intArg][i].h264decfm;
                i--;
            }
        }
        for(i=0;i<MAX_FRAME_BUFFER;i++)
        {
            if(ngmem[i])
            {
                MEMFreeToDefaultHeap(ngmem[i]);
                ngmem[i] = 0;
            }
        }

        if( (rtn != 0) || (width<=0 || height<=0) )
        {
            printf("error : H264DECGetImageSize");
            return -1;
        }
        printf("H264DECGetImageSize w:%d, h:%d\n", width, height);

		// Start music/sound.
		if( MovieSound )
		{
			result = FMODSystem->playSound( MovieChannel ? FMOD_CHANNEL_REUSE : FMOD_CHANNEL_FREE,
				MovieSound, true, &MovieChannel );

			if( result == FMOD_OK )
			{
				MovieChannel->setVolume( Volume );
				MovieChannel->setPaused( false );
			}
			else
				printf( "Failed to play music!\n" );
		}

        // ----- ----- ----- ----- execute loop ----- ----- ----- -----
        while (1)
        {
            while (1)
            {
                ret_find =
                    H264DECCheckDecunitLength(
                        mem_ptr, rbuf, bytes_read, byte_cnt, &length);

                if (ret_find)
                {
                    s32 remain_bytes = bytes_read - byte_cnt;

                    if (remain_bytes > 0)
                    {
                        s32 last_bytes_read = bytes_read;
                        fpos += byte_cnt;
    printf("File Reading.....");
                        additional_read = FSReadFileWithPos(&__our_FS_Client, &Cmd, rbuf, 1, BUFFER_SIZE, fpos, input_handle, 0, FS_RET_NO_ERROR);
    printf("finish\n");
                        if(additional_read<0) additional_read = 0;
                        if((byte_cnt==0) && (last_bytes_read == additional_read))
                        {
                            bytes_read = additional_read;
                            additional_read = 0;
                        }
                        else
                        {
                            bytes_read = additional_read;
                        }
                        byte_cnt = 0;
                    }
                    else if (remain_bytes == 0)
                    {
                        fpos += byte_cnt;
                        additional_read = FSReadFileWithPos(&__our_FS_Client, &Cmd, rbuf, 1, BUFFER_SIZE, fpos, input_handle, 0, FS_RET_NO_ERROR);
                        if(additional_read<0) additional_read = 0;
                        bytes_read = additional_read;
                        byte_cnt = 0;
                    }
                    else
                    {
                        additional_read = 0;
                        bytes_read = 0;
                        byte_cnt = 0;
                    }
                }
                if (ret_find == 0){ break;} // found decunit 
                if (additional_read == 0)
                {
                    break;
                }   // end of stream file
            }

            if (ret_find)
            {
                // end of stream file 
                length = bytes_read;
            }

            if(length==0)
                break;

            rtn = H264DECSetBitstream(mem_ptr, rbuf+byte_cnt, length, time_stamp);
            h264count++;

            time_stamp += 0.33;
            if (rtn != 0)
            {
                printf("error : bitstream set : 0x%x\n", rtn);
                ret = H264DEC_ERR_INTERNAL;
                break;
            }

            next_fpos = byte_cnt + fpos + length;

            void *throw_264decfm = NULL;
            for(i=0;i<MAX_FRAME_BUFFER;i++)
            {
                if(List_h264decfm[intArg][i].used==0)
                {
                    throw_264decfm = List_h264decfm[intArg][i].h264decfm;
                    List_h264decfm[intArg][i].used = 1;
                    break;
                }
            }

#ifdef DO_BENCHMARK
            startTime = OSGetTime();
#endif

            ret = H264DECExecute(mem_ptr, throw_264decfm);

            endTime = OSGetTime();
#ifdef DO_BENCHMARK
            OSReport("H264 frame %d: H264DECExecute % 8.4f milliseconds,  ret:0x%X\n", h264count, (float)OSTicksToMicroseconds(endTime-startTime) / 1000.0f, ret);
#endif
            if(g_SkipH264Rendering == 0)
            {
                SetupH264Draw(intArg);
            }

            // pass priority to other decoder

#define VSYNCx2 (16666*2)
            s32 waitTime = VSYNCx2 - OSTicksToMicroseconds(endTime - prevendTime);
            endTime = OSGetTime();

            // pass priority to other thread
            if( waitTime > 0 )
            {
                OSSleepMicroseconds(waitTime);
            }else{
                // pass priority to other thread
                OSSleepMilliseconds(2);
            }

            prevendTime = endTime;

            //not use FM
            if(!(ret & H264DEC_ERR_USE_FM))
            {
                for(i=0;i<MAX_FRAME_BUFFER;i++)
                {
                    if(List_h264decfm[intArg][i].h264decfm == throw_264decfm)
                    {
                        List_h264decfm[intArg][i].used = 0;
                        break;
                    }
                }
            }

            ret &= ~H264DEC_ERR_FM_STAT;

            if( ret != 0 )
            {
                printf("error in H264 frame %d: H264DECExecute : 0x%x\n", h264count, ret);
                return -1;
            }

            byte_cnt += length;

            // background process switch monitoring
            if( !ProcUIInForeground() ){
                do{
                    OSSleepMilliseconds(10);
                }while( !ProcUIInForeground() );

                fpos = next_fpos;

                // for resuming
                printf("fpos:%d\n", fpos);
                additional_read = FSReadFileWithPos(&__our_FS_Client, &Cmd, rbuf, 1, BUFFER_SIZE, fpos, input_handle, 0, FS_RET_NO_ERROR);
                if(additional_read<0) additional_read = 0;
                bytes_read = additional_read;
                byte_cnt = 0;
            }

            if (ret == H264DEC_ERR_INTERNAL)
            {
                printf("H264DEC_ERR_INTERNAL\n");
                break;
            }

            if  ( (additional_read == 0) &&  (ret_find) )
            {
                break;
            }
        }   // ----- ----- ----- ----- execute loop ----- ----- ----- ----- */

        g_SkipH264Rendering = 1;

        // end of execute loop 
        if (ret == 0)
        {
            // Normal End
            ret = H264DECEnd(mem_ptr);
        }
        else
        {
            printf("unexpected error\n");
            return -1;
        }

        ret = H264DECClose(mem_ptr);

        if (ret != 0)
        {
            printf("error : video close : 0x%x\n", ret);
        }

        printf("Output %d frames\n", OutputFrames[0] );

        {
            FSCloseFile(&__our_FS_Client, &Cmd, input_handle, FS_RET_NO_ERROR);
            FSDelClient(&__our_FS_Client, FS_RET_NO_ERROR);
        }

        MEMFreeToDefaultHeap(rbuf);
        MEMFreeToDefaultHeap(mem_ptr);

    }while(DEF_PLAY_LOOP);
}

/* ------------------------------------------------------------
        Function Name   : set_parameters
    ---------------------------------------------------------- */

void
    set_parameters(
        s32     memory_size,
        void    *mem_ptr,
        void    *usermem
    )
{
    s32     ret;

    // initialize parameters by default value

    ret = H264DECInitParam(memory_size, mem_ptr);
    if (ret != 0)
    {
        printf("Error : H264DECInitParam : 0x%x\n", ret);
        return;
    }

    ret = H264DECSetParam_FPTR_OUTPUT(mem_ptr, h264DecodeCallback );
    if (ret != 0)
    {
        printf("Error : H264DECSetParam_FPTR_OUTPUT : 0x%x\n", ret);
        return;
    }

    ret = H264DECSetParam_OUTPUT_PER_FRAME(mem_ptr, BUFFERING_OUTPUT_PER_FRAME/*UNBUFFERING_OUTPUT_PER_FRAME*/);
    if (ret != 0)
    {
        printf("Error : H264DECSetParam_OUTPUT_PER_FRAME : 0x%x\n", ret);
        return;
    }

    ret = H264DECSetParam_USER_MEMORY(mem_ptr, &usermem);
    if (ret != 0)
    {
        printf("Error : H264DECSetParam[H264DEC_PARAM_ID_USER_MEMORY] : 0x%x\n", ret);
        return;
    }
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////

OSThread       Thread[NUM_THREADS];
u8             ThreadStack[NUM_THREADS][STACK_SIZE];

/*int main(int argc, char **argv)
{
    s32 initargc = 2;
    char* initargv[] = {"DEMO_CB_FORMAT 8_8_8_8", "DEMO_SCAN_FORMAT 8_8_8_8"};
    char* initdrcargv[] = {"DEMO_DRC_CB_FORMAT 8_8_8_8", "DEMO_DRC_SCAN_FORMAT 8_8_8_8"};

    // Initialize the DEMO library, DEMO test system, and create the
    // primary display.
    DEMOInit();
    DEMOTestInit(argc, argv);
    DEMOPadInit();
    VPADInit();

    DEMOGfxInit(initargc, initargv);
    DEMODRCInit(initargc, initdrcargv);
    DEMOFontInit();

    // Initialize attributes and buffers for TV
    InitShader();
    InitAttribData();

    FSInit();

    // -------------- h264 decoding therad ------------ //
    OSCreateThread(&Thread[0],            // ptr to the thread to init
                    decode_h264,          // ptr to the start routine
                    0,                    // params passed to start routine
                    NULL,
                    ThreadStack[0] + STACK_SIZE, // initial stack address
                    STACK_SIZE,                  // stack size
                    16,                          // scheduling priority
                    0);                          // detached
    // Start the thread.
    OSResumeThread(&Thread[0]);

    // -------------- h264 decoding therad ------------ //
    OSCreateThread(&Thread[1],            // ptr to the thread to init
                    decode_h264,          // ptr to the start routine
                    1,                    // params passed to start routine
                    NULL,
                    ThreadStack[1] + STACK_SIZE, // initial stack address
                    STACK_SIZE,                  // stack size
                    16,                          // scheduling priority
                    0);                          // detached
    // Start the thread.
    OSResumeThread(&Thread[1]);

    // wait for device stability
    OSSleepMilliseconds(2000);

    while(DEMOIsRunning())
    {
        if(!g_SkipH264Rendering)
            drawDRCFrame();

        if(!g_SkipH264Rendering)
            drawTVFrame();

        DEMOGfxDoneRender();
        DEMOGfxBeforeRender();
    }

}*/

struct VideoPlayerInternal
{
};

VideoPlayer::VideoPlayer()
	: internal_( new VideoPlayerInternal )
	, IsLooped( false )
{
	// -------------- h264 decoding therad ------------ //
    OSCreateThread(&Thread[0],            // ptr to the thread to init
                    decode_h264,          // ptr to the start routine
                    0,                    // params passed to start routine
                    NULL,
                    ThreadStack[0] + STACK_SIZE, // initial stack address
                    STACK_SIZE,                  // stack size
                    16,                          // scheduling priority
                    0);                          // detached

    OSResumeThread(&Thread[0]);

	InitShader();
	InitAttribData();
}

VideoPlayer::~VideoPlayer()
{
	delete internal_;
}

void VideoPlayer::SetVolume( float volume )
{
	//Volume = volume;
}

void VideoPlayer::Play( const boost::shared_ptr< Video > &video )
{
}

void VideoPlayer::DrawFrame()
{
	drawTVFrame();
}

boost::shared_ptr< Texture2D > VideoPlayer::GetTexture()
{
	u8 decIdx = 0;
    u32 h264ReadBufIdx = (g_H264WriteBufIdx[decIdx] == 0)? 1 : 0;

    GX2Invalidate(GX2_INVALIDATE_TEXTURE, g_LTexture[decIdx][h264ReadBufIdx].surface.imagePtr, g_LTexture[decIdx][h264ReadBufIdx].surface.imageSize);

	return VideoTextures[ decIdx ][ h264ReadBufIdx ];
}
