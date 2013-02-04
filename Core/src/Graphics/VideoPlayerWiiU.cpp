#include <Graphics/VideoPlayer.h>

#include <Core.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/TextureWiiUInternal.h>
#include <Content/Wad.h>
#include <Graphics/Video.h>
#include <Graphics/Texture2D.h>


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
#include "WiiU/MovieTest.h"
#include "WiiU/videorender.h"

typedef struct _MyColor
{
    u8  r, g, b, a;
} MyColor;

#define SCREEN_WIDTH  1280.0
#define SCREEN_HEIGHT  720.0
#define DRC_SCREEN_WIDTH   854.0
#define DRC_SCREEN_HEIGHT  480.0

#define CLR_LOC 0

#define POINT_Z -0.9
#define LINE_Z -0.5
#define POLYGON_Z 0.0

#define U8TOF32 (1.0/255.0)

#define FILE_MAX_LINE 15


/*---------------------------------------------------------------------------*
 *    Constants defined for this file
 *    -- #Defines's --
 *---------------------------------------------------------------------------*/
/* Debug output utility macro */
#define PRINTF(...)             OSReport(__VA_ARGS__)
#define PANIC(...)              OSPanic(__FILE__, __LINE__, "PANIC: "__VA_ARGS__)
#define ASSERT_CHECK(condition) \
  do { \
      if(!(condition)) \
          OSPanic(__FILE__, __LINE__, "Failed: " #condition "\n"); \
  } while(0)


/*=========================================================================*
            definitions
 *=========================================================================*/

#define UNASSIGNED_END_TIME_STAMP   0xFFFFFFFFFFFFFFFFULL

#define INPUTNAME_DEFINED

#ifdef INPUTNAME_DEFINED
#define MP4_INPUT_SAMPLE1       "/vol/content/Movies/LogoSalad.mp4";    // TV
#define MP4_INPUT_SAMPLE2       "/vol/content/Movies/LogoSalad.mp4";	// DRC
#endif

#define VIDEOSKIP_DELAY         (70)                            // permissible delay time
#define FILEMEMORYSIZE          (512*1000*1000)                 // 512MByte

#define MAXTHREADNUM            (8)
#define STACK_SIZE              (4096*1024)

// For Debug
//#define PRINT_TIME
//#define PRINT_LOG

/*=========================================================================*
            external functions
 *=========================================================================*/

extern void AudioInit(s32 threadnum);
extern void AudioInit2 (s32 threadnum);
extern void AudioBufferAlloc(s32 SampleSize, s32 threadnum);
extern void AudioExit(s32 threadnum);
extern void VideoExit(s32 threadnum);
extern s32 VideoDraw(u8 *ip, s32 threadnum);
extern s32 VideoDrawFirst(u8 *ip, s32 threadnum);
extern s32 DrawScreen(s32 threadnum);
extern void shutdownAudioSystem(void);
extern void AudioRestart (s32 threadnum);
extern void AudioRestart2 (s32 threadnum);
#ifdef USE_PROCESS_SWITCHING
extern void AudioProcessPause(s32 threadnum);
extern void AudioProcessReStart(s32 threadnum);
#endif

extern MP4DemuxCore    *MP4DemuxCorePtr[];


/*=========================================================================*
            global variables
 *=========================================================================*/
static const s8        *mp4Filename[2] = { "/vol/content/Movies/TestVideo9.mp4", "/vol/content/Movies/TestVideo9.mp4" };
static s8              fileName[2][1024];

MP4PlayerCore   MP4PlayerCore1[2];
MP4PlayerCore   *MP4PlayerCorePtr[2];
MP4PlayerGUICtl MP4PlayerCtl;
OSThread        Thread[MAXTHREADNUM];                   // pointer to thread control block to initialize.
u8              ThreadStack[MAXTHREADNUM][STACK_SIZE];  // address of initial stack pointer.

FSClient*      GpClient[2];
FSCmdBlock*    GpCmd[2];
FSFileHandle   Gfh[2];
FSDirHandle    dirHandle;
FSDirEntry     returnedDirEntry;

/*---------------------------------------------------------------------------*
  Name:         stateChangeCallback

  Description:  Handler of state change notification.
                Never invoked in this demo.
 *---------------------------------------------------------------------------*/
static void stateChangeCallback( FSClient* pClient,
                                 FSVolumeState state,
                                 void* pContext)
{
    // Report volume state and last error
    FSError lastError = FSGetLastError(pClient);
    OSReport("Volume state of client 0x%08x changed to %d\n", pClient, state);
    OSReport("Last error: %d\n", lastError);
}

s32 exc_start_time_stamp[2];
s32 exc_end_time_stamp[2];

bool EXIT_PLAYBACK = false;
bool GLOBAL_VIDEO_OVERRIDE = false;
static void (*UpdateElapsedTime)(bool) = NULL;

#ifdef USE_PROCESS_SWITCHING
OSEvent gDoRelease;
OSEvent gAcquired;

BOOL            inForeground = TRUE;
static volatile BOOL            isTVDraw = FALSE;
static volatile BOOL            isDRCDraw = FALSE;
static volatile BOOL            TVDecode = TRUE;
static volatile BOOL            DRCDecode = TRUE;

s32 process_sleep_time;
s32 threadabort[2][8];

#ifndef USE_SINGLE_CORE

#endif


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
    Name:           IntToCommaSeparateString
    Description:    Convert the display format of numbers.
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
s8 *IntToCommaSeparateString( s8 *str, s32 n )
{
    s32     i = 0, j;
    s8      tmp[64];
    s8      *p = tmp;
    u32     u = abs(n);

    memset(tmp, 0, 64);
    do // while( 0 != u );
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

						// Update time counter.
						if( UpdateElapsedTime )
							UpdateElapsedTime( false );
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
        if (vendflag[0]/* && vendflag[1]*/)
#endif
        {
            break;
        }
    }
    str[i] = '\0';

	GLOBAL_VIDEO_OVERRIDE = false;

    OSReport("Video Thread Finish\n");
    return(0);
}


/*-------------------------------------------------------------------------*
    Name:           DrawMenu
    Description:    Display the information in the playback.
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
void DrawMenu(u32 mode)
{
    /*u32 line = 0;
    FSStatus status;
    s32 count;
    s8 tmp[64];
    s32 time;

    if ((MP4PlayerCtl.CurPlayState == 1) || (MP4PlayerCtl.CurPlayState == 2))
    {
        time = MP4PlayerCorePtr[0]->current_time;
    }
    else
    {
        time = MP4PlayerCtl.PlayCurrTime;
    }

    while( 1 )
    {
        DEMOFontSetContextState();
        if (MP4PlayerCtl.PlayInfoEnable == 0)
        {
            DEMOFontPrintf(3, line, "FILE: %s", fileName[0]);
            DEMOFontPrintf(44, line++, "%.2d:%.2d:%.2d / %.2d:%.2d:%.2d", (time/1000)/3600, ((time/1000)%3600)/60, (time/1000)%60, 
                        (MP4DemuxCorePtr[0]->MP4Duration/1000)/3600, ((MP4DemuxCorePtr[0]->MP4Duration/1000)%3600)/60, (MP4DemuxCorePtr[0]->MP4Duration/1000)%60);
        }
        else
        {
            DEMOFontPrintf(3, line++, "FILE: %s", fileName[0]);
            DEMOFontPrintf(3, line++, "%.2d:%.2d:%.2d / %.2d:%.2d:%.2d", (time/1000)/3600, ((time/1000)%3600)/60, (time/1000)%60, 
                        (MP4DemuxCorePtr[0]->MP4Duration/1000)/3600, ((MP4DemuxCorePtr[0]->MP4Duration/1000)%3600)/60, (MP4DemuxCorePtr[0]->MP4Duration/1000)%60);
            if (MP4DemuxCorePtr[0]->VideoTrackFound == 0)
            {
                DEMOFontPrintf(3, line++, "Video Track not found");
            }
            else
            {
                DEMOFontPrintf(3, line++, "%d x %d [pixel]", MP4DemuxCorePtr[0]->H264ImageWidth, MP4DemuxCorePtr[0]->H264ImageHeight);
                DEMOFontPrintf(3, line++, "Frame Rate: %.1f [fps]", (float)((float)(MP4PlayerCtl.PlayFrame*1000)/MP4PlayerCtl.PlayTime));
            }
            if (MP4DemuxCorePtr[0]->AudioTrackFound == 0)
            {
                DEMOFontPrintf(3, line++, "Audio Track not found");
            }
            else
            {
                DEMOFontPrintf(3, line++, "AAC : %dCH %dHz", MP4DemuxCorePtr[0]->AACChannelNum, MP4DemuxCorePtr[0]->AACSampeRate);
            }
            if (MP4PlayerCorePtr[0]->file_input_mode == 0)
            {
            DEMOFontPrintf(3, line++, "READ DEVICE");
            }
            else
            {
            DEMOFontPrintf(3, line++, "READ ON MEMORY");
            }
        }

        DEMOFontPrintf(3, 23, "a:PLAY  b:PAUSE  x:SEEK  y:STOP  ->:FF[x%d]  <-:REW[x%d]  SEEK TIME[%dsec]", MP4PlayerCtl.ffbytime, MP4PlayerCtl.rewbytime, MP4PlayerCtl.UserSeekTime);
        DEMOGfxSetContextState();
    }
    else if (mode == 1)
    {
        MyColor red_clr      = { 237, 28, 36, 255 } ;
        MyColor white_clr    = { 255,255,255, 255 } ;

        line = 2;
        count = 0;
        DEMOFontSetContextState();
        DEMOFontSetColor(white_clr.r * U8TOF32, white_clr.g * U8TOF32, white_clr.b * U8TOF32, white_clr.a * U8TOF32);
        DEMOFontPrintf(3,  line,   "[No]");
        DEMOFontPrintf(8,  line,   "[FILE NAME]");
        DEMOFontPrintf(40, line++, "[SIZE(KB)]");
        while( FS_STATUS_END != (status = FSReadDir(GpClient[0], GpCmd[0], dirHandle, &returnedDirEntry, 0)) )
        {
            if(FS_STATUS_OK != status)
            {
                PANIC("Failed to read directory (%d)\n", status);
            }
            count++;
            if ((count > (((MP4PlayerCtl.CurFilePos-1)/FILE_MAX_LINE)*FILE_MAX_LINE)) && (count <= ((((MP4PlayerCtl.CurFilePos-1)/FILE_MAX_LINE)+1)*FILE_MAX_LINE)))
            {
                if (MP4PlayerCtl.CurFilePos == count)
                {
                    DEMOFontSetColor(red_clr.r * U8TOF32, red_clr.g * U8TOF32, red_clr.b * U8TOF32, red_clr.a * U8TOF32);
                    memcpy(fileName[0], returnedDirEntry.name, 1023);
                }
                else
                {
                    DEMOFontSetColor(white_clr.r * U8TOF32, white_clr.g * U8TOF32, white_clr.b * U8TOF32, white_clr.a * U8TOF32);
                }
                DEMOFontPrintf(3,  line,   "%3d",   count);
                DEMOFontPrintf(8,  line,   "%-40.40s", returnedDirEntry.name);
                DEMOFontPrintf(40, line++, "%s",  IntToCommaSeparateString(tmp, (returnedDirEntry.stat.size+1024)/1024));
                DEMOFontSetColor(white_clr.r * U8TOF32, white_clr.g * U8TOF32, white_clr.b * U8TOF32, white_clr.a * U8TOF32);
                DEMOFontPrintf(48, 19, "[%d/%d]", MP4PlayerCtl.CurFilePos, MP4PlayerCtl.FileCounter);
                DEMOFontPrintf(3,  21, " a:DEMO START  HOME:DEMO END  ->:NEXT PAGE  <-:BACK PAGE");
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
        if (aendflag[0]/* && aendflag[1]*/)
#endif
        {
			break;
        }
        DEMOGfxSetContextState();
    }
    else if (mode == 2)
    {
        DEMOFontSetContextState();
        DEMOFontPrintf(3, 21, "File Reading");
        DEMOGfxSetContextState();
    }
    else if (mode == 3)
    {
        DEMOFontSetContextState();
        DEMOFontPrintf(3, 21, "");
        DEMOGfxSetContextState();
    }
    else if (mode == 4)
    {
        DEMOFontSetContextState();
        DEMOFontPrintf(3, 21, "File Read Complete");
        DEMOGfxSetContextState();
    }*/
}


/*-------------------------------------------------------------------------*
    Name:           ScanSingleDir
    Description:    Scan specified directory and show its contents.
    Arguments:      ch               client handle
                    pPath            path of the input data
    Returns:        status
 *-------------------------------------------------------------------------*/
static s32 ScanSingleDir(const char *pPath )
{
    FSStatus       status;
    s32     chan;
    u32     padBit;
    u32     connectedBits;
    PADStatus Pads[PAD_MAX_CONTROLLERS];

    PRINTF("Opening %s\n", pPath);
    s32     demostart = 0;

    InitVideoBuffer(0, 1920, 1088);
    u32 y_size = ((UVD_ALIGN_PITCH_IN_PIXELS(1920))*1088);

    /*
     * open directory
     */
    status=FSOpenDir(GpClient[0], GpCmd[0], pPath, &dirHandle, 0);
    if(status < FS_STATUS_OK)
        PANIC("Failed to open directory (%d)\n", status);

    MP4PlayerCtl.FileCounter = 0;
    /*
     * read directory entry one by one till it gets to the end
     */
        PRINTF("  [No]    [FILE]                                    [SIZE]\n");
    while( FS_STATUS_END !=
           (status = FSReadDir(GpClient[0], GpCmd[0], dirHandle, &returnedDirEntry, 0)) )
    {
        if(FS_STATUS_OK != status)
            PANIC("Failed to read directory (%d)\n", status);
#if 1
        MP4PlayerCtl.FileCounter++;
        PRINTF("  %3d      %-32.32s %16d\n", MP4PlayerCtl.FileCounter, returnedDirEntry.name, returnedDirEntry.stat.size);
#else

        /*
         * show the details of directory entry.
         */
        PRINTF("\nEntry %s/%s:\n", pPath, returnedDirEntry.name);

        if (returnedDirEntry.stat.flag & FS_STAT_FLAG_IS_DIRECTORY) /* this is directory */
        {
            PRINTF("  [DIR]\n");
            if (returnedDirEntry.stat.flag & FS_STAT_FLAG_SPRT_DIR_SIZE)
                /* this supports "size of directory" */
                PRINTF("  Directory size = %d\n", returnedDirEntry.stat.size);
            else
                PRINTF("  Directory size = (not set)\n");
        }
        else /* this is file */
        {
            PRINTF("  [FILE]\n");
            PRINTF("  File size = %d\n", returnedDirEntry.stat.size);
        }

        /* Size of quota */
        if (returnedDirEntry.stat.flag & FS_STAT_FLAG_SPRT_QUOTA_SIZE)
            PRINTF("  Quota size = %d\n", returnedDirEntry.stat.quota_size );
        else
            PRINTF("  Quota size = not set\n" );

        /* Entry ID */
        if (returnedDirEntry.stat.flag & FS_STAT_FLAG_SPRT_ENTID)
            PRINTF("  Entry ID = %d\n", returnedDirEntry.stat.ent_id );
        else
            PRINTF("  Entry ID = not set\n" );

        /* Created time */
        if (returnedDirEntry.stat.flag & FS_STAT_FLAG_SPRT_CTIME)
            PRINTF("  Created time = %d\n", returnedDirEntry.stat.ctime );
        else
            PRINTF("  Created time = not set\n" );

        /* Last Modified time */
        if (returnedDirEntry.stat.flag & FS_STAT_FLAG_SPRT_MTIME)
            PRINTF("  Last Modified time = %d\n", returnedDirEntry.stat.mtime );
        else
            PRINTF("  Last Modified time = not set\n" );

        /* Access permission to this entry */
        PRINTF("  Owner id: %x\n", returnedDirEntry.stat.owner_id);
        PRINTF("  Group id: %x\n", returnedDirEntry.stat.group_id);
        PRINTF("  Permission: %x\n", returnedDirEntry.stat.permission );
        PRINTF("      Owner : %c%c \n", (returnedDirEntry.stat.permission & FS_MODE_IRUSR)?'R':'-',
                                        (returnedDirEntry.stat.permission & FS_MODE_IWUSR)?'W':'-');
        PRINTF("      Group : %c%c \n", (returnedDirEntry.stat.permission & FS_MODE_IRGRP)?'R':'-',
                                        (returnedDirEntry.stat.permission & FS_MODE_IWGRP)?'W':'-');
        PRINTF("      Others: %c%c \n", (returnedDirEntry.stat.permission & FS_MODE_IROTH)?'R':'-',
                                        (returnedDirEntry.stat.permission & FS_MODE_IWOTH)?'W':'-');
#endif
    }

    /*
     * now, reached to the end of directory. close directory
     */
    status=FSOpenDir(GpClient[0], GpCmd[0], pPath, &dirHandle, 0);

    if(FS_STATUS_OK > status)
        PANIC("Failed to close directory (%d)\n", status);

    /*while (1)
    {
        memset(Pads, 0, sizeof(PADStatus)*PAD_MAX_CONTROLLERS);
        //PAD Read
        PADRead( Pads );

        for (chan = 0; chan < PAD_MAX_CONTROLLERS; ++chan)
        {
            padBit = PAD_CHAN0_BIT >> chan;

            switch (Pads[chan].err)
            {
              case PAD_ERR_NONE:
              case PAD_ERR_TRANSFER:
                connectedBits |= padBit;
                break;
              case PAD_ERR_NO_CONTROLLER:
                connectedBits &= ~padBit;
                break;
              case PAD_ERR_NOT_READY:
              default:
                break;
            }
        }*/

        memset(MP4PlayerCtl.ViewAreaPtr, 0, y_size);
        memset((void*)(MP4PlayerCtl.ViewAreaPtr+y_size), 128, y_size/2);
        DCFlushRange( MP4PlayerCtl.ViewAreaPtr, MP4PlayerCtl.ViewAreaSize);
        GX2InitTexturePtrs(&g_LTexture[0], MP4PlayerCtl.ViewAreaPtr, 0);
        GX2InitTexturePtrs(&g_UVTexture[0], (void*)(MP4PlayerCtl.ViewAreaPtr+y_size), 0);

        /*
         * open directory
         */
        status=FSOpenDir(GpClient[0], GpCmd[0], pPath, &dirHandle, 0);
        if(status < FS_STATUS_OK)
            PANIC("Failed to open directory (%d)\n", status);

        //drawTVFrame(1);

        /*
         * now, reached to the end of directory. close directory
         */
        status=FSCloseDir(GpClient[0], GpCmd[0], dirHandle, 0);

        if(FS_STATUS_OK > status)
            PANIC("Failed to close directory (%d)\n", status);


        /*DEMOGfxDoneRender();
        DEMOGfxBeforeRender();

        for (chan = 0; chan < PAD_MAX_CONTROLLERS; ++chan)
        {
            if (Pads[chan].button & PAD_BUTTON_A)
            {
                demostart = 1;
                while(1)
                {
                    PADRead( Pads );
                    if ((Pads[chan].button & PAD_BUTTON_A) == 0)
                    {
                        break;
                    }
                }
                break;
            }
            else if (Pads[chan].button & PAD_BUTTON_DOWN)
            {
                MP4PlayerCtl.CurFilePos++;
                if (MP4PlayerCtl.CurFilePos > MP4PlayerCtl.FileCounter)
                {
                    MP4PlayerCtl.CurFilePos = 1;
                }
                OSReport("SELECT FILE NUMBER:%d\n", MP4PlayerCtl.CurFilePos);
                while(1)
                {
                    PADRead( Pads );
                    if ((Pads[chan].button & PAD_BUTTON_DOWN) == 0)
                    {
                        break;
                    }
                }
                break;
            }
            else if (Pads[chan].button & PAD_BUTTON_UP)
            {
                MP4PlayerCtl.CurFilePos--;
                if (MP4PlayerCtl.CurFilePos == 0)
                {
                    MP4PlayerCtl.CurFilePos = MP4PlayerCtl.FileCounter;
                }
                OSReport("SELECT FILE NUMBER:%d\n", MP4PlayerCtl.CurFilePos);
                while(1)
                {
                    PADRead( Pads );
                    if ((Pads[chan].button & PAD_BUTTON_UP) == 0)
                    {
                        break;
                    }
                }
                break;
            }
            else if (Pads[chan].button & PAD_BUTTON_RIGHT)
            {
                MP4PlayerCtl.CurFilePos += FILE_MAX_LINE;
                if (MP4PlayerCtl.CurFilePos < (MP4PlayerCtl.FileCounter - 1))
                {
                    // no action
                }
                else if ((MP4PlayerCtl.CurFilePos + FILE_MAX_LINE)/FILE_MAX_LINE == ((MP4PlayerCtl.FileCounter - 1) + FILE_MAX_LINE)/FILE_MAX_LINE)
                {
                    MP4PlayerCtl.CurFilePos = MP4PlayerCtl.FileCounter;
                }
                else if (MP4PlayerCtl.CurFilePos > (MP4PlayerCtl.FileCounter - 1)) {
                    MP4PlayerCtl.CurFilePos = 1;
                }
                OSReport("SELECT FILE NUMBER:%d\n", MP4PlayerCtl.CurFilePos);
                while(1)
                {
                    PADRead( Pads );
                    if ((Pads[chan].button & PAD_BUTTON_RIGHT) == 0)
                    {
                        break;
                    }
                }
                break;
            }
            else if (Pads[chan].button & PAD_BUTTON_LEFT)
            {
                MP4PlayerCtl.CurFilePos -= FILE_MAX_LINE;
                if (MP4PlayerCtl.CurFilePos < 0) {
                    MP4PlayerCtl.CurFilePos = MP4PlayerCtl.FileCounter;
                }
                if (MP4PlayerCtl.CurFilePos < (MP4PlayerCtl.FileCounter - 1))
                {
                    // no action
                }
                OSReport("SELECT FILE NUMBER:%d\n", MP4PlayerCtl.CurFilePos);
                while(1)
                {
                    PADRead( Pads );
                    if ((Pads[chan].button & PAD_BUTTON_LEFT) == 0)
                    {
                        break;
                    }
                }
                break;
            }
            else if (Pads[chan].button & PAD_BUTTON_START)
            {
                while(1)
                {
                    PADRead( Pads );
                    if ((Pads[chan].button & PAD_BUTTON_START) == 0)
                    {
                        break;
                    }
                }
                return 1;
            }
        }
        
        if (demostart)
        {
            break;
        }
    }*/

    /* successfully done */
    PRINTF("\n==> read directory\n");
    return 0;
}


/*-------------------------------------------------------------------------*
    Name:           OutBufferInit
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static void OutBufferInit(void)
{
    s32 i;

    for (i = 0; i < VIDEO_BUFFER_NUM; i++)
    {
        MP4PlayerCorePtr[0]->OutputVideoInfo[i].PTS = 0x7FFFFFFF;
        MP4PlayerCorePtr[0]->OutputVideoInfo[i].Size = 0;
        MP4PlayerCorePtr[0]->OutputVideoInfo[i].Status = 0;
    }

    for (i = 0; i < AUDIO_BUFFER_NUM; i++)
    {
        MP4PlayerCorePtr[0]->OutputAudioInfo[i].PTS  = 0x7FFFFFFF;
        MP4PlayerCorePtr[0]->OutputAudioInfo[i].Size = 0;
        MP4PlayerCorePtr[0]->OutputAudioInfo[i].Status = 0;
    }
}


/*-------------------------------------------------------------------------*
    Name:           VideoOutputThread
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static s32 VideoOutputThread(s32 intArg, void *ptrArg)
{
    volatile s32 i, j;
    s32 ret;
    u32 vsys_currtime;
#ifdef PRINT_TIME
    s32 starttime, endtime;
#endif

#ifdef USE_PROCESS_SWITCHING
    while (!MP4PlayerCtl.SyncStart[0])
    {
        if(inForeground)
        {
            OSYieldThread();
            if (MP4PlayerCtl.VThreadStop[0])
            {
                return(0);
            }
        }
        else
        {
            while(!inForeground)
            {
                OSSleepMilliseconds(10);
                OSYieldThread();
            }
        }
    }
#else
    while (!MP4PlayerCtl.SyncStart[0])
    {
        OSYieldThread();
        if (MP4PlayerCtl.VThreadStop[0])
        {
            return(0);
        }
    }
#endif
    OSReport("Video Thread Start\n");

    if (MP4DemuxCorePtr[intArg]->VideoTrackFound == 0)
    {
        while(1)
        {
            drawTVFrame(0);
            DEMOGfxDoneRender();
            DEMOGfxBeforeRender();
            if (MP4PlayerCorePtr[0]->vthread_end)
            {
                MP4PlayerCtl.VThreadStop[0] = 1;
                break;
            }
            OSYieldThread();
        }
    }

    while(1)
    {
        if (MP4PlayerCorePtr[0]->OutputVideoInfo[MP4PlayerCorePtr[0]->df_v].Status == 1)
        {
            ret = VideoDrawFirst(MP4PlayerCorePtr[0]->OutputVideoInfo[MP4PlayerCorePtr[0]->df_v].bufp, 0);
            if (ret != 0)
            {
                OSReport("VideoDraw Failed.\n");
                MP4PlayerCtl.VThreadStop[0] = 1;
                break;
            }
            break;
        }
        if (MP4PlayerCorePtr[i]->vthread_end)
        {
            MP4PlayerCtl.VThreadStop[i] = 1;
            break;
        }
        OSYieldThread();
    }

    OSReport("MP4PlayerCtl.PlayBaseTime2:%d\n", MP4PlayerCtl.PlayBaseTime);
    while(1)
    {
        vsys_currtime = OSTicksToMilliseconds(OSGetTime());
        if ((MP4PlayerCtl.PauseState == 2) || (MP4PlayerCtl.FirstPlay == 1))
        {
            while(1)
            {
                if (MP4PlayerCtl.PauseState == 3)
                {
                    MP4PlayerCtl.PlayBaseTime += (OSTicksToMilliseconds(OSGetTime()) - vsys_currtime);
                    OSReport("Restart Video Thread\n");
                    OSYieldThread();
                    break;
                }
                OSYieldThread();
            }
        }

        for (i = 0; i < 1; i++)
        {
            if ((MP4PlayerCtl.CurPlayState != 0) && (MP4PlayerCtl.SyncStop == 0))
            {
                if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 1)
                {
                    ret = VideoDraw(MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].bufp, i);
                    if (ret != 0)
                    {
                        OSReport("VideoDraw Failed.\n");
                        MP4PlayerCtl.VThreadStop[i] = 1;
                        break;
                    }
                    MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS = 0x7FFFFFFF;
                    MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status = 0;
                    MP4PlayerCorePtr[i]->df_v++;
                    if (MP4PlayerCorePtr[i]->df_v == VIDEO_BUFFER_NUM)
                    {
                        MP4PlayerCorePtr[i]->df_v = 0;
                    }
                }
            }
            else
            {
                if ((MP4PlayerCtl.VThreadStop[i] == 0) && (MP4PlayerCtl.SyncStop == 0))
                {
                    if (((vsys_currtime - MP4PlayerCtl.PlayBaseTime + MP4PlayerCorePtr[i]->SeekOffsetTime) >= MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS))
                    {
                        if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 1)
                        {
                            if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS && (MP4PlayerCtl.CurPlayState == 0))
                            {
                                if ((((vsys_currtime - MP4PlayerCtl.PlayBaseTime + MP4PlayerCorePtr[i]->SeekOffsetTime) - MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS) > VIDEOSKIP_DELAY))
                                {
                                    MP4PlayerCorePtr[i]->FrameSkipFlag = 1;
                                    OSReport("CurrTime:%d, VPTS:%d, thread:%d, mode:%d\n", (vsys_currtime - MP4PlayerCtl.PlayBaseTime + MP4PlayerCorePtr[i]->SeekOffsetTime), MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS, i, MP4PlayerCtl.CurPlayState);
                                    OSReport("vsys_currtime:%d\n", vsys_currtime);
                                    OSReport("MP4PlayerCtl.PlayBaseTime:%d\n", MP4PlayerCtl.PlayBaseTime);
                                    OSReport("FrameSkip\n");
                                }
                                else
                                {
                                    MP4PlayerCorePtr[i]->FrameSkipFlag = 0;
                                }
                            }
#ifdef PRINT_TIME
                            starttime = OSTicksToMilliseconds(OSGetTime());
#endif
                            // video frame draw
#ifdef PRINT_LOG
                            OSReport("CurrTime:%d, VPTS:%d, VDIFF:%d, thread:%d\n",
                                (vsys_currtime - MP4PlayerCtl.PlayBaseTime), MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS, abs((vsys_currtime - MP4PlayerCtl.PlayBaseTime) - MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS), i);
#endif
                            ret = VideoDraw(MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].bufp, i);
                            MP4PlayerCtl.PlayCurrTime = MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS;
                            MP4PlayerCtl.PlayFrame++;
                            MP4PlayerCtl.PlayTime = vsys_currtime - MP4PlayerCtl.PlayBaseTime;
                            if (ret != 0)
                            {
                                OSReport("VideoDraw Failed.\n");
                                MP4PlayerCtl.VThreadStop[i] = 1;
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
                }
            }

            if ((!MP4PlayerCtl.VThreadStop[i] && MP4PlayerCorePtr[i]->vthread_end && (MP4PlayerCorePtr[i]->df_v == MP4PlayerCorePtr[i]->ff_v) && (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 0)) ||
                ((MP4PlayerCtl.SyncStop == 1) && (MP4PlayerCorePtr[i]->vthread_end == 1)))
            {
                OSReport("Video[%d] Thread End\n", i);
                MP4PlayerCtl.VThreadStop[i] = 1;
            }
#ifdef USE_PROCESS_SWITCHING
            ProcessChangeWait(i, 0);
#endif
        }
        OSYieldThread();
        if (MP4PlayerCtl.VThreadStop[0])
        {
            break;
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
    u32  asys_currtime;
    s32  i;

#ifdef USE_PROCESS_SWITCHING
    while (!MP4PlayerCtl.SyncStart[0])
    {
        if(inForeground)
        {
            OSYieldThread();
            if (MP4PlayerCtl.AThreadStop[0])
            {
                return(0);
            }
        }
        else
        {
            while(!inForeground)
            {
                OSSleepMilliseconds(10);
                OSYieldThread();
            }
        }
    }
#else
    while (!MP4PlayerCtl.SyncStart[0])
    {
        OSYieldThread();
        if (MP4PlayerCtl.AThreadStop[0])
        {
            return(0);
        }
    }
#endif
    OSReport("Audio Thread Start\n");

    while(1)
    {
        asys_currtime = OSTicksToMilliseconds(OSGetTime());

        if ((MP4PlayerCtl.PauseState == 2) || (MP4PlayerCtl.FirstPlay == 1))
        {
            while(1)
            {
                if (MP4PlayerCtl.PauseState == 3)
                {
                    OSReport("Restart Audio Thread\n");
                    OSYieldThread();
                    break;
                }
                OSYieldThread();
            }
        }

        for (i = 0; i < 1; i++)
        {
            if ((MP4PlayerCtl.AThreadStop[i] == 0) && (MP4PlayerCtl.SyncStop == 0))
            {
                if (((asys_currtime - MP4PlayerCtl.PlayBaseTime + MP4PlayerCorePtr[i]->SeekOffsetTime) >= MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS))
                {
                    if (MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].Status == 1)
                    {
                        // audio pcm
                        if (MP4PlayerCorePtr[i]->pre_AudioBuff_Offset != MP4PlayerCorePtr[i]->AudioBuff_Offset)
                        {
#ifdef PRINT_LOG
                            OSReport("CurrTime:%d, APTS:%d, ADIFF:%d, thread:%d\n",
                                (asys_currtime - MP4PlayerCtl.PlayBaseTime), MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS, abs((asys_currtime - MP4PlayerCtl.PlayBaseTime) - MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS), i);
#endif
                            MP4PlayerCtl.PlayCurrTime = MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].PTS;
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

            if ((!MP4PlayerCtl.AThreadStop[i] && MP4PlayerCorePtr[i]->athread_end && (MP4PlayerCorePtr[i]->df_a == MP4PlayerCorePtr[i]->ff_a) && (MP4PlayerCorePtr[i]->OutputAudioInfo[MP4PlayerCorePtr[i]->df_a].Status == 0)) ||
                ((MP4PlayerCtl.SyncStop == 1) && (MP4PlayerCorePtr[i]->athread_end == 1)))
            {
                OSReport("Audio[%d] Thread End\n", i);
                MP4PlayerCtl.AThreadStop[i] = 1;
            }
#ifdef USE_PROCESS_SWITCHING
            ProcessChangeWait(i, 1);
#endif
        }
        OSYieldThread();
        if (MP4PlayerCtl.AThreadStop[0])
        {
            break;
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

    if ((offset + length) > MP4PlayerCorePtr[threadnum]->InputFileSize)
    {
        return 0;
    }

    if (*pData == NULL)
    {
        OSReport("Inputbuf Allocete Error\n");
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

    while ( !EXIT_PLAYBACK )
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

#ifdef USE_PROCESS_SWITCHING
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
		exc_start_time_stamp[intArg] = 0;
        exc_end_time_stamp[intArg]   = 0;
		for( int i = 0; i < MP4DemuxCorePtr[intArg]->MP4Duration/100; ++i )
		{
			exc_end_time_stamp[ intArg ] = exc_start_time_stamp[ intArg ] + 100;
			if( exc_end_time_stamp[ intArg ] >= MP4DemuxCorePtr[ intArg ]->MP4Duration )
				exc_end_time_stamp[ intArg ] = MP4DemuxCorePtr[ intArg ]->MP4Duration;

			if( exc_end_time_stamp[ intArg ] <= exc_start_time_stamp[ intArg ] )
				EXIT_PLAYBACK = true;

			if( EXIT_PLAYBACK )
				break;

			iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 0, (u64)exc_start_time_stamp[intArg],
				(u64)exc_end_time_stamp[intArg], intArg );
			if( iMlibRet != MP4DMXFW_RET_SUCCESS )
			{
				OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
				goto ERROR;
			}

			exc_start_time_stamp[ intArg ] += 100;
		}
#endif

ERROR:
		EXIT_PLAYBACK = true;
		UpdateElapsedTime( true );
		OSYieldThread();

        MP4PlayerCorePtr[intArg]->execendflag = 1;
        iMlibRet = MP4DMXFW_End( pMlibHandle, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
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
            if (MP4PlayerCtl.SyncStart[threadnum] == 0)
            {
                if (MP4PlayerCorePtr[threadnum]->AudioSampleRate != 0)
                {
                    AudioInit(threadnum);
                    MP4PlayerCtl.AudioInitState = 1;
                }
                MP4PlayerCtl.PlayBaseTime = OSTicksToMilliseconds(OSGetTime());
                OSReport("MP4PlayerCtl.PlayBaseTime1:%d\n", MP4PlayerCtl.PlayBaseTime);
            }

            if (MP4PlayerCtl.SyncStart[0] == 0)
            {
                MP4PlayerCtl.PauseState = 1;
            }
            MP4PlayerCtl.SyncStart[threadnum] = 1;
        }

        if (unit->track_type == TRACK_TYPE_VIDEO)
        {
            if (MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].Status == 0)
            {
                MP4PlayerCorePtr[threadnum]->voutfound = 1;
                MP4PlayerCorePtr[threadnum]->OutputVideoInfo[MP4PlayerCorePtr[threadnum]->ff_v].bufp = reinterpret_cast< u8 * >( unit->sample->data_ptr );
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
    Name:           MP4Play
    Description:    
    Arguments:      
    Returns:        
 *-------------------------------------------------------------------------*/
static s32 MP4Play(s32 intArg, void *ptrArg)
{
    MEMHeapHandle   defaultHeap;
    // Memory Variables
    MEMHeapHandle       ExpHeap;
    FSStatus    status;
    FSStat      stat;
    void        *addr;
    u32         size;
    s32         i;
    volatile s32         ref_mode = 0;
    s32         errstatus = 0;

    s32     iMlibRet;
    void    *pMlibHandle=NULL;
    s32     UseWorkMemSize;
    volatile s32     start_time, end_time;

    s32 done;
    s32 offset;
    s32 AudioPrevPtr;
    s32 AudioCurrBufID;
    s32 AudioBuff_Offset;
    s32 pre_AudioBuff_Offset;

    OSReport("MP4Play[%d] Thread Start\n", intArg);

    MP4PlayerCorePtr[intArg] = &MP4PlayerCore1[intArg];

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
    MP4PlayerCorePtr[intArg]->InputFileSize = 0;
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
        MP4PlayerCtl.VThreadStop[intArg] = 1;
        MP4PlayerCtl.AThreadStop[intArg] = 1;
        return(0);
    }

    // set the heap area
    ExpHeap = MEMCreateExpHeap(addr, size/32);

    // allocate memory to store the input data
    MP4PlayerCorePtr[intArg]->streamFullBuffer = (u8 *)MEMAllocFromDefaultHeapEx(FILEMEMORYSIZE, 64);
    MediaFileReadInit(intArg);

    status = FSOpenFile(GpClient[intArg], GpCmd[intArg], (const char *)mp4Filename[intArg], "r", &Gfh[intArg], FS_RET_NOT_FOUND);
    if(status < FS_STATUS_OK)
    {
        OSReport("[ERROR] cannot open mp4 file.\n");
        MP4PlayerCtl.VThreadStop[intArg] = 1;
        MP4PlayerCtl.AThreadStop[intArg] = 1;
        MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->streamFullBuffer);
        MEMDestroyExpHeap(ExpHeap);
        MEMFreeToDefaultHeap(addr);
        return(0);
    }

    status = FSGetStat(GpClient[intArg], GpCmd[intArg], (const char *)mp4Filename[intArg], &stat, 0);
    if (status < FS_STATUS_OK)
    {
        OSReport("[ERROR] cannot get input mp4 file status.\n");
        MP4PlayerCtl.VThreadStop[intArg] = 1;
        MP4PlayerCtl.AThreadStop[intArg] = 1;
        MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->streamFullBuffer);
        MEMDestroyExpHeap(ExpHeap);
        MEMFreeToDefaultHeap(addr);
        return(0);
    }

    MP4PlayerCorePtr[intArg]->InputFileSize = stat.size;
    if (MP4PlayerCorePtr[intArg]->InputFileSize > FILEMEMORYSIZE)
    {
        MP4PlayerCorePtr[intArg]->file_input_mode = 0;    // file input
    }
    else
    {
        MP4PlayerCorePtr[intArg]->file_input_mode = 1;    // memory input
        MP4PlayerCorePtr[intArg]->video_fsync_comp = 0;
        MP4PlayerCorePtr[intArg]->async_vparams.userCallback  = ReadCallbackV;
        MP4PlayerCorePtr[intArg]->async_vparams.userContext = (void*)&MP4PlayerCorePtr[intArg]->video_fsync_comp;
        status = FSReadFileAsync(
                        GpClient[intArg],
                        GpCmd[intArg],
                        (void*)MP4PlayerCorePtr[intArg]->streamFullBuffer,
                        sizeof(u8),
                        MP4PlayerCorePtr[intArg]->InputFileSize,
                        Gfh[intArg],
                        0,
                        FS_RET_NO_ERROR,
                        &MP4PlayerCorePtr[intArg]->async_vparams);
        {
            while(1)
            {
                drawTVFrame(2);
                DEMOGfxDoneRender();
                DEMOGfxBeforeRender();
                OSSleepMilliseconds(200);                   // blink rate of the display time
                drawTVFrame(3);
                DEMOGfxDoneRender();
                DEMOGfxBeforeRender();
                OSSleepMilliseconds(200);                   // blink rate of the display time
                if (MP4PlayerCorePtr[intArg]->video_fsync_comp)
                {
                    drawTVFrame(4);
                    break;
                }
            }
        }
        if(status < FS_STATUS_OK)
        {
            return 0;
        }
    }

    // Set CallBack Parameters
    MP4PlayerCorePtr[intArg]->MP4DMUXParam.MP4DMXFW_CallbackSetData = (void *)cbSetMediaContainerData;
    MP4PlayerCorePtr[intArg]->MP4DMUXParam.MP4DMXFW_CallbackGetData = (void *)cbGetMediaSampleData;

    iMlibRet = MP4DMXFW_Open(ExpHeap, &pMlibHandle, &UseWorkMemSize, intArg );
    if( iMlibRet != MP4DMXFW_RET_SUCCESS )
    {
        errstatus = 1;
        OSReport("MP4DMXOpen Failed. ret = %d\n", iMlibRet );
        goto ERROR;
    }

    iMlibRet = MP4DMXFW_Begin( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, intArg );
    if( iMlibRet != MP4DMXFW_RET_SUCCESS )
    {
        errstatus = 1;
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

    OutBufferInit();
    MP4PlayerCtl.SyncStop = 0;
    ref_mode = 0;
    MP4PlayerCorePtr[intArg]->SeekOffsetTime = 0;
    MP4PlayerCorePtr[intArg]->current_time = 0;
    MP4PlayerCorePtr[intArg]->ref_current_time = -1;
    while(1)
    {
        if (MP4PlayerCtl.PlayAbort)
        {
            OSReport("Play Abort\n");
            break;
        }

        if (MP4DemuxCorePtr[intArg]->AudioTrackFound == 0)
        {
            if (MP4PlayerCtl.PauseState == 1)
            {
                OSReport("Pause Mode\n");
                MP4PlayerCtl.PauseState = 2;
            }

            if ( MP4PlayerCtl.PauseState == 2)
            {
                while (1)
                {
                    if (MP4PlayerCtl.PauseState == 0)
                    {
                        MP4PlayerCtl.PauseState = 3;
                        MP4PlayerCtl.FirstPlay = 0;
                        OSReport("Restart from Pause\n");
                        OSYieldThread();
                        break;
                    }
                    OSYieldThread();
                    if (MP4PlayerCtl.PlayState == 3)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            if (MP4PlayerCtl.AudioInitState == 1)
            {
                if (MP4PlayerCtl.PauseState == 1)
                {
                    OSReport("Pause Mode\n");
                    AXRegisterDeviceFinalMixCallback(AX_DEVICE_TV,  NULL);
                    MP4PlayerCorePtr[intArg]->Audio_Action = STREAM_NONE;

                    done                 = MP4PlayerCorePtr[intArg]->audioinfo.done;
                    offset               = MP4PlayerCorePtr[intArg]->audioinfo.offset;
                    AudioPrevPtr         = MP4PlayerCorePtr[intArg]->AudioPrevPtr;
                    AudioCurrBufID       = MP4PlayerCorePtr[intArg]->AudioCurrBufID;
                    AudioBuff_Offset     = MP4PlayerCorePtr[intArg]->AudioBuff_Offset;
                    pre_AudioBuff_Offset = MP4PlayerCorePtr[intArg]->pre_AudioBuff_Offset;
                    MP4PlayerCtl.PauseState = 2;
                }

                if ( MP4PlayerCtl.PauseState == 2)
                {
                    while (1)
                    {
                        if (MP4PlayerCtl.PauseState == 0)
                        {
                            MP4PlayerCorePtr[intArg]->audioinfo.done       = done;
                            MP4PlayerCorePtr[intArg]->audioinfo.offset     = offset;
                            MP4PlayerCorePtr[intArg]->AudioPrevPtr         = AudioPrevPtr;
                            MP4PlayerCorePtr[intArg]->AudioCurrBufID       = AudioCurrBufID;
                            MP4PlayerCorePtr[intArg]->AudioBuff_Offset     = AudioBuff_Offset;
                            MP4PlayerCorePtr[intArg]->pre_AudioBuff_Offset = pre_AudioBuff_Offset;

                            AudioRestart2(intArg);
                            MP4PlayerCtl.PauseState = 3;
                            MP4PlayerCtl.FirstPlay = 0;
                            OSReport("Restart from Pause\n");
                            OSYieldThread();
                            break;
                        }
                        OSYieldThread();
                        if (MP4PlayerCtl.PlayState == 3)
                        {
                            break;
                        }
                    }
                }
            }
        }

//        OSReport("\033[H");   // Home
//        OSReport("BaseTime:%d, CurrTime:%d, MODE:%d\n", MP4PlayerCorePtr[intArg]->SeekOffsetTime, MP4PlayerCorePtr[intArg]->current_time, MP4PlayerCtl.PlayState);
        if (MP4PlayerCtl.PlayState == 0)        // normal playback
        {
//            OSReport("PLAY MODE\n");
            MP4PlayerCtl.CurPlayState = MP4PlayerCtl.PlayState;
            // VideoBuffer setting
            if ((ref_mode != MP4PlayerCtl.CurPlayState) && (ref_mode != 3))
            {
                OSReport("MODE CHANGE\n");
                MP4PlayerCtl.SyncStop = 1;
                MP4PlayerCorePtr[intArg]->df_v = 0;
                MP4PlayerCorePtr[intArg]->ff_v = 0;
                MP4PlayerCorePtr[intArg]->df_a = 0;
                MP4PlayerCorePtr[intArg]->ff_a = 0;
                MP4PlayerCtl.PlayTime = 0;
                MP4PlayerCtl.PlayFrame = 0;
                OutBufferInit();
                AudioInit2(intArg);
                MP4PlayerCorePtr[intArg]->SeekOffsetTime = start_time;
            }

            start_time = MP4PlayerCorePtr[intArg]->current_time;
            end_time = start_time + 100;    // play interval

            if (end_time > MP4DemuxCorePtr[intArg]->MP4Duration)
            {
                break;
            }
            iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 0, (int64_t)start_time, (int64_t)end_time, intArg );
            if( iMlibRet != MP4DMXFW_RET_SUCCESS )
            {
                OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
                goto ERROR;
            }

            if (ref_mode != MP4PlayerCtl.CurPlayState)
            {
                if (((MP4PlayerCorePtr[intArg]->ff_v > ((MP4DemuxCorePtr[intArg]->OutputUnitPtr.sample->video_framerate+1) >> 1)) || (MP4PlayerCorePtr[intArg]->ff_a > ((MP4DemuxCorePtr[intArg]->mp4AudioTrackInf.sample_rate/1024) >> 1))))
                {
                    MP4PlayerCorePtr[intArg]->df_v = 0;
                    MP4PlayerCorePtr[intArg]->df_a = 0;
                    OSReport("PLAY RESTART ff_v:%d, ff_a:%d, BaseTime:%d, VPTS:%d, APTS:%d\n", 
                            MP4PlayerCorePtr[intArg]->ff_v, MP4PlayerCorePtr[intArg]->ff_a, MP4PlayerCorePtr[intArg]->SeekOffsetTime, 
                            MP4PlayerCorePtr[intArg]->OutputVideoInfo[0].PTS, MP4PlayerCorePtr[intArg]->OutputAudioInfo[0].PTS);
                    if (MP4DemuxCorePtr[intArg]->VideoTrackFound)
                    {
                        MP4PlayerCtl.PlayCurrTime = MP4PlayerCorePtr[intArg]->OutputVideoInfo[0].PTS;
                    }
                    if (MP4DemuxCorePtr[intArg]->AudioTrackFound)
                    {
                        MP4PlayerCtl.PlayCurrTime = MP4PlayerCorePtr[intArg]->OutputAudioInfo[0].PTS;
                    }
                    AudioRestart (intArg);
                    MP4PlayerCtl.PlayBaseTime = OSTicksToMilliseconds(OSGetTime());
                    MP4PlayerCtl.SyncStop = 0;
                }
            }
            if (((MP4PlayerCorePtr[intArg]->ff_v > ((MP4DemuxCorePtr[intArg]->OutputUnitPtr.sample->video_framerate+1) >> 1)) || (MP4PlayerCorePtr[intArg]->ff_a > ((MP4DemuxCorePtr[intArg]->mp4AudioTrackInf.sample_rate/1024) >> 1))) && (MP4PlayerCtl.SyncStop == 1))
            {
                MP4PlayerCorePtr[intArg]->df_v = 0;
                MP4PlayerCorePtr[intArg]->df_a = 0;
                OSReport("PLAY RESTART ff_v:%d, ff_a:%d, BaseTime:%d, VPTS:%d, APTS:%d\n", 
                        MP4PlayerCorePtr[intArg]->ff_v, MP4PlayerCorePtr[intArg]->ff_a, MP4PlayerCorePtr[intArg]->SeekOffsetTime, 
                        MP4PlayerCorePtr[intArg]->OutputVideoInfo[0].PTS, MP4PlayerCorePtr[intArg]->OutputAudioInfo[0].PTS);
                AudioRestart (intArg);
                MP4PlayerCtl.PlayBaseTime = OSTicksToMilliseconds(OSGetTime());
                MP4PlayerCtl.SyncStop = 0;
            }
            ref_mode = MP4PlayerCtl.CurPlayState;
        }
        else if (MP4PlayerCtl.PlayState == 1)   // fast-forward
        {
            s32 delta = 200;    // play interval

            PRINTF("FF MODE\n");
            MP4PlayerCtl.SyncStop = 1;
            MP4PlayerCtl.CurPlayState = MP4PlayerCtl.PlayState;
//            if (ref_mode != MP4PlayerCtl.CurPlayState)
            {
                MP4PlayerCorePtr[intArg]->df_v = 0;
                MP4PlayerCorePtr[intArg]->ff_v = 0;
                MP4PlayerCorePtr[intArg]->df_a = 0;
                MP4PlayerCorePtr[intArg]->ff_a = 0;
                MP4PlayerCtl.PlayTime = 0;
                MP4PlayerCtl.PlayFrame = 0;
                OutBufferInit();
                AudioInit2(intArg);
            }
            if (ref_mode != 1)
            {
                MP4PlayerCorePtr[intArg]->current_time = MP4PlayerCtl.PlayCurrTime;
            }
            end_time = delta;
            start_time = MP4PlayerCorePtr[intArg]->current_time;

            iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 1, (int64_t)start_time, (int64_t)end_time, intArg );
            MP4PlayerCtl.PlayCurrTime = MP4PlayerCorePtr[intArg]->current_time;
            if( iMlibRet != MP4DMXFW_RET_SUCCESS )
            {
                OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
                goto ERROR;
            }
            ref_mode = MP4PlayerCtl.CurPlayState;
            OSReport("start_time:%d, current_time:%d, ref_current_time:%d\n", start_time, MP4PlayerCorePtr[intArg]->current_time, MP4PlayerCorePtr[intArg]->ref_current_time);
            if (start_time == MP4PlayerCorePtr[intArg]->current_time)
            {
                OSReport("PLAY FINISH\n");
                break;
            }
            MP4PlayerCtl.SyncStop = 0;
            OSSleepMilliseconds((MP4PlayerCorePtr[intArg]->current_time - start_time)/MP4PlayerCtl.ffbytime);
            AudioInit2(intArg);
            MP4PlayerCtl.SyncStop = 1;
            MP4PlayerCtl.PlayTime = 0;
            MP4PlayerCtl.PlayFrame = 0;
            MP4PlayerCtl.PlayBaseTime = OSTicksToMilliseconds(OSGetTime());
        }
        else if (MP4PlayerCtl.PlayState == 2)   // fast-rewind
        {
            s32 delta = 200;    // play interval

            OSReport("REW MODE\n");
            // VideoBuffer setting
            MP4PlayerCtl.SyncStop = 1;
            MP4PlayerCtl.CurPlayState = MP4PlayerCtl.PlayState;
            MP4PlayerCorePtr[intArg]->df_v = 0;
            MP4PlayerCorePtr[intArg]->ff_v = 0;
            MP4PlayerCorePtr[intArg]->df_a = 0;
            MP4PlayerCorePtr[intArg]->ff_a = 0;
            MP4PlayerCtl.PlayTime = 0;
            MP4PlayerCtl.PlayFrame = 0;
            OutBufferInit();
            AudioInit2(intArg);
            if (ref_mode != 2)
            {
                MP4PlayerCorePtr[intArg]->current_time = MP4PlayerCtl.PlayCurrTime;
            }

            end_time = delta;
            start_time = MP4PlayerCorePtr[intArg]->ref_current_time;

            iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 2, (int64_t)start_time, (int64_t)end_time, intArg );
            MP4PlayerCtl.PlayCurrTime = MP4PlayerCorePtr[intArg]->current_time;
            if( iMlibRet != MP4DMXFW_RET_SUCCESS )
            {
                OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
                goto ERROR;
            }

            ref_mode = MP4PlayerCtl.CurPlayState;
            if (MP4PlayerCorePtr[intArg]->ref_current_time == 0)
            {
                // start from the beginning
                OSReport("PLAY RESTART\n");
                MP4PlayerCtl.PlayState = 0;                 // normal playback mode
                MP4PlayerCorePtr[i]->SeekOffsetTime = 0;    // 
            }
            else
            {
                MP4PlayerCtl.SyncStop = 0;
                OSSleepMilliseconds((start_time - MP4PlayerCorePtr[intArg]->current_time)/MP4PlayerCtl.rewbytime);
                AudioInit2(intArg);
                MP4PlayerCtl.SyncStop = 1;
                MP4PlayerCtl.PlayTime = 0;
                MP4PlayerCtl.PlayFrame = 0;
                MP4PlayerCtl.PlayBaseTime = OSTicksToMilliseconds(OSGetTime());
            }
        }
        else if (MP4PlayerCtl.PlayState == 3)   // seek
        {
            OSReport("SEEK MODE\n");
            MP4PlayerCtl.CurPlayState = MP4PlayerCtl.PlayState;
            // VideoBuffer setting
            if (ref_mode != MP4PlayerCtl.CurPlayState)
            {
                OSReport("MODE CHANGE\n");
                MP4PlayerCtl.SyncStop = 1;
                if (MP4DemuxCorePtr[intArg]->VideoTrackFound)
                {
                    start_time = MP4PlayerCorePtr[intArg]->OutputVideoInfo[MP4PlayerCorePtr[intArg]->df_v].PTS + MP4PlayerCtl.UserSeekTime*1000;
                }
                else if (MP4DemuxCorePtr[intArg]->AudioTrackFound)
                {
                    start_time = MP4PlayerCorePtr[intArg]->OutputAudioInfo[MP4PlayerCorePtr[intArg]->df_a].PTS + MP4PlayerCtl.UserSeekTime*1000;
                }
                start_time = MP4PlayerCtl.PlayCurrTime + MP4PlayerCtl.UserSeekTime*1000;
                MP4PlayerCorePtr[intArg]->df_v = 0;
                MP4PlayerCorePtr[intArg]->ff_v = 0;
                MP4PlayerCorePtr[intArg]->df_a = 0;
                MP4PlayerCorePtr[intArg]->ff_a = 0;
                OutBufferInit();
                AudioInit2(intArg);
                MP4PlayerCtl.PlayTime = 0;
                MP4PlayerCtl.PlayFrame = 0;
            }
//            start_time = MP4PlayerCorePtr[intArg]->current_time + MP4PlayerCtl.UserSeekTime*1000;
            if (start_time < 0)
            {
                start_time = 0;
            }
            end_time = start_time + 100;
            if (end_time > MP4DemuxCorePtr[intArg]->MP4Duration)
            {
//                break;
            }

            iMlibRet = MP4DMXFW_Execute( pMlibHandle, &MP4PlayerCorePtr[intArg]->MP4DMUXParam, 3, (int64_t)start_time, (int64_t)end_time, intArg );
            if( iMlibRet != MP4DMXFW_RET_SUCCESS )
            {
                OSReport("MP4DMXFW_Execute Failed. ret = %d\n", iMlibRet );
                goto ERROR;
            }

            if (MP4PlayerCtl.UserSeekTime > 0)
            {
                if (start_time == MP4PlayerCorePtr[intArg]->current_time)
                {
                    OSReport("PLAY FINISH\n");
                    break;
                }
            }

            if (ref_mode != MP4PlayerCtl.CurPlayState)
            {
                if (((MP4PlayerCorePtr[intArg]->ff_v > ((MP4DemuxCorePtr[intArg]->OutputUnitPtr.sample->video_framerate+1) >> 1)) || (MP4PlayerCorePtr[intArg]->ff_a > ((MP4DemuxCorePtr[intArg]->mp4AudioTrackInf.sample_rate/1024) >> 1))))
                {
                    AudioRestart (intArg);
                    MP4PlayerCtl.PlayBaseTime = OSTicksToMilliseconds(OSGetTime());
                }
            }
            if (((MP4PlayerCorePtr[intArg]->ff_v > ((MP4DemuxCorePtr[intArg]->OutputUnitPtr.sample->video_framerate+1) >> 1)) || (MP4PlayerCorePtr[intArg]->ff_a > ((MP4DemuxCorePtr[intArg]->mp4AudioTrackInf.sample_rate/1024) >> 1))) && (MP4PlayerCtl.SyncStop == 1))
            {
                AudioRestart (intArg);
                MP4PlayerCtl.PlayBaseTime = OSTicksToMilliseconds(OSGetTime());
            }
            MP4PlayerCtl.PlayState = 0;         // normal playback mode
            ref_mode = MP4PlayerCtl.CurPlayState;
        }
        OSYieldThread();
    }

    if ((iMlibRet == MP4DMXFW_RET_SUCCESS) && (MP4PlayerCorePtr[intArg]->voutfound == 0) && (MP4PlayerCorePtr[intArg]->aoutfound == 0))
    {
        MP4PlayerCorePtr[intArg]->execendflag = 1;
        iMlibRet = MP4DMXFW_End( pMlibHandle, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_End Failed. ret = %d\n", iMlibRet );
            goto ERROR;
        }

        while(1)
        {
            if (MP4DemuxCorePtr[intArg]->AudioTrackFound == 0)
            {
                if (MP4PlayerCtl.PauseState == 1)
                {
                    OSReport("Pause Mode\n");
                    MP4PlayerCtl.PauseState = 2;
                }

                if ( MP4PlayerCtl.PauseState == 2)
                {
                    while (1)
                    {
                        if (MP4PlayerCtl.PauseState == 0)
                        {
                            MP4PlayerCtl.PauseState = 3;
                            MP4PlayerCtl.FirstPlay = 0;
                            OSReport("Restart from Pause\n");
                            OSYieldThread();
                            goto ERROR;
                        }
                        OSYieldThread();
                        if (MP4PlayerCtl.PlayState == 3)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                if (MP4PlayerCtl.AudioInitState == 1)
                {
                    if (MP4PlayerCtl.PauseState == 1)
                    {
                        OSReport("Pause Mode\n");
                        AXRegisterDeviceFinalMixCallback(AX_DEVICE_TV,  NULL);
                        MP4PlayerCorePtr[intArg]->Audio_Action = STREAM_NONE;

                        done                 = MP4PlayerCorePtr[intArg]->audioinfo.done;
                        offset               = MP4PlayerCorePtr[intArg]->audioinfo.offset;
                        AudioPrevPtr         = MP4PlayerCorePtr[intArg]->AudioPrevPtr;
                        AudioCurrBufID       = MP4PlayerCorePtr[intArg]->AudioCurrBufID;
                        AudioBuff_Offset     = MP4PlayerCorePtr[intArg]->AudioBuff_Offset;
                        pre_AudioBuff_Offset = MP4PlayerCorePtr[intArg]->pre_AudioBuff_Offset;
                        MP4PlayerCtl.PauseState = 2;
                    }

                    if ( MP4PlayerCtl.PauseState == 2)
                    {
                        while (1)
                        {
                            if (MP4PlayerCtl.PauseState == 0)
                            {
                                MP4PlayerCorePtr[intArg]->audioinfo.done       = done;
                                MP4PlayerCorePtr[intArg]->audioinfo.offset     = offset;
                                MP4PlayerCorePtr[intArg]->AudioPrevPtr         = AudioPrevPtr;
                                MP4PlayerCorePtr[intArg]->AudioCurrBufID       = AudioCurrBufID;
                                MP4PlayerCorePtr[intArg]->AudioBuff_Offset     = AudioBuff_Offset;
                                MP4PlayerCorePtr[intArg]->pre_AudioBuff_Offset = pre_AudioBuff_Offset;

                                AudioRestart2(intArg);
                                MP4PlayerCtl.PauseState = 3;
                                MP4PlayerCtl.FirstPlay = 0;
                                OSReport("Restart from Pause\n");
                                OSYieldThread();
                                goto ERROR;
                            }
                            OSYieldThread();
                            if (MP4PlayerCtl.PlayState == 3)
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        MP4PlayerCorePtr[intArg]->execendflag = 1;
        iMlibRet = MP4DMXFW_End( pMlibHandle, intArg );
        if( iMlibRet != MP4DMXFW_RET_SUCCESS )
        {
            OSReport("MP4DMXFW_End Failed. ret = %d\n", iMlibRet );
            goto ERROR;
        }
    }

    MP4PlayerCorePtr[intArg]->athread_end = 1;
    if ((MP4DemuxCorePtr[intArg]->VideoTrackFound == 0) && (MP4PlayerCtl.PlayAbort == 0))
    {
        while(1)
        {
            if (MP4PlayerCtl.AThreadStop[0] == 1)
            {
                break;
            }
            OSYieldThread();
        }
    }
    MP4PlayerCorePtr[intArg]->vthread_end = 1;

ERROR:
    MP4PlayerCorePtr[intArg]->vthread_end = 1;
    MP4PlayerCorePtr[intArg]->athread_end = 1;

    if (errstatus == 0)
    {
        if (MP4PlayerCtl.PlayState != 0)
        {
            MP4PlayerCorePtr[intArg]->df_v = 0;
            MP4PlayerCorePtr[intArg]->ff_v = 0;
            MP4PlayerCorePtr[intArg]->df_a = 0;
            MP4PlayerCorePtr[intArg]->ff_a = 0;
            for (i = 0; i < VIDEO_BUFFER_NUM; i++)
            {
                MP4PlayerCorePtr[intArg]->OutputVideoInfo[i].Status = 0;
            }
            for (i = 0; i < AUDIO_BUFFER_NUM; i++)
            {
                MP4PlayerCorePtr[intArg]->OutputAudioInfo[i].Status = 0;
            }
        }

        if (MP4PlayerCtl.PlayAbort)
        {
            MP4PlayerCtl.VThreadStop[intArg] = 1;
            MP4PlayerCtl.AThreadStop[intArg] = 1;
            OSYieldThread();
        }
        else
        {
            while(1)
            {
                if (MP4PlayerCtl.VThreadStop[intArg] && MP4PlayerCtl.AThreadStop[intArg])
                {
                    break;
                }
                OSYieldThread();
            }
        }

        // audio exit
        if (MP4PlayerCorePtr[intArg]->AudioSampleRate != 0)
        {
            AudioExit(intArg);
        }
    }
    else
    {
        MP4PlayerCtl.FirstPlay = 0;
        MP4PlayerCtl.VThreadStop[intArg] = 1;
        MP4PlayerCtl.AThreadStop[intArg] = 1;
        MP4PlayerCtl.SyncStart[0] = 1;
    }

    // video exit
    VideoExit(intArg);

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
    MEMFreeToDefaultHeap(MP4PlayerCorePtr[intArg]->streamFullBuffer);
    MEMDestroyExpHeap(ExpHeap);
    MEMFreeToDefaultHeap(addr);

    FSCloseFile(GpClient[0], GpCmd[0], Gfh[0], FS_RET_NO_ERROR);

    return(0);
}


#ifdef USE_PROCESS_SWITCHING

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

struct VideoPlayerInternal
{
};

VideoPlayer::VideoPlayer( void (*UpdateElapsedTime)(bool) )
	: internal_( new VideoPlayerInternal )
	, IsLooped( false )
{
	::UpdateElapsedTime = UpdateElapsedTime;

	InitShader();
    InitAttribData();

	// Allocate buffers.
    GpClient[0] = reinterpret_cast< FSClient * >( MEMAllocFromDefaultHeap(sizeof(FSClient)) );
    if (!GpClient[0])
    {
        OSHalt("Error: cannot allocate memory for fs client.\n");
    }
    GpCmd[0]    = reinterpret_cast< FSCmdBlock * >( MEMAllocFromDefaultHeap(sizeof(FSCmdBlock)) );
    if (!GpCmd[0])
    {
        OSHalt("Error: cannot allocate memory for command block.\n");
    }
    // Add client to FS.
    FSAddClient(GpClient[0], FS_RET_NO_ERROR);

	// Set state change notification callback.
    FSStateChangeParams stateChangeParams = {
        .userCallback = stateChangeCallback,
        .userContext  = NULL,
        .ioMsgQueue   = NULL
    };
    FSSetStateChangeNotification(GpClient[0], &stateChangeParams);
    OSReport("==> FSSetStateChangeNotification: Registered state change notification callback.\n");


    OSReport("\n\n\n### Start operation ###\n");

    // Init command block.
    FSInitCmdBlock(GpCmd[0]);
    OSReport("==> FSInitCmdBlock: Command block initialized.\n");

	MP4DemuxCorePtr[0] = NULL;

	const char *DefaultPath = "/vol/content/Movies/";

	MP4PlayerCtl.ViewAreaSize = (((UVD_ALIGN_PITCH_IN_PIXELS(1920))*1088*3)/2 + UVD_BUFFER_PAD);
	MP4PlayerCtl.ViewAreaPtr = reinterpret_cast< u8 * >( MEMAllocFromDefaultHeapEx(MP4PlayerCtl.ViewAreaSize, UVD_BUFFER_ALIGNMENT) );
	if (MP4PlayerCtl.ViewAreaPtr == NULL)
	{
		OSReport("cannot allocate framebuffer\n");
	}
	if (ScanSingleDir(DefaultPath) == 1)
	{
		return;
	}

	{
		/*u32 len1, len2;
		strncpy((char *)fileName[1], DefaultPath, 1023);
		len1 = strlen((char *)fileName[1]);
		len2 = strlen((char *)fileName[0]);
		fileName[1][len1] = '/';
		memcpy(&fileName[1][len1+1], fileName[0], len2);
		fileName[1][1023] = '\0';
		mp4Filename[0] = fileName[1];*/
	}

	OSReport("InputFile:%s\n", mp4Filename[0]);

	// Create the video thread.
	OSCreateThread( &Thread[0],   // ptr to the thread to init
					VideoOutputThread,              // ptr to the start routine
					0,                              // params passed to start routine
					NULL,
					ThreadStack[0] + STACK_SIZE,    // initial stack address
					STACK_SIZE,                     // stack size
					16,                             // scheduling priority
					0);        // detached

	// Create the audio thread.
	OSCreateThread( &Thread[1],   // ptr to the thread to init
					AudioOutputThread,              // ptr to the start routine
					0,                              // params passed to start routine
					NULL,
					ThreadStack[1] + STACK_SIZE,    // initial stack address
					STACK_SIZE,                     // stack size
					16,                             // scheduling priority
					0);         // detached

	// Create the play thread.
	OSCreateThread( &Thread[2],   // ptr to the thread to init
					MP4Play,                        // ptr to the start routine
					0,                              // params passed to start routine
					NULL,
					ThreadStack[2] + STACK_SIZE,    // initial stack address
					STACK_SIZE,                     // stack size
					16,                             // scheduling priority
					0);         // detached

	MP4PlayerCtl.VThreadStop[0] = 0;
    MP4PlayerCtl.VThreadStop[1] = 0;
    MP4PlayerCtl.AThreadStop[0] = 0;
    MP4PlayerCtl.AThreadStop[1] = 0;

    MP4PlayerCtl.SyncStart[0] = 0;
    MP4PlayerCtl.SyncStart[1] = 0;
    MP4PlayerCtl.UserSeekTime = 0;
    MP4PlayerCtl.PlayBaseTime = 0;
    MP4PlayerCtl.ffbytime = 1;
    MP4PlayerCtl.rewbytime = 1;
    MP4PlayerCtl.PlayState = 0;
    MP4PlayerCtl.PauseState = 0;
    MP4PlayerCtl.AudioInitState = 0;
    MP4PlayerCtl.PlayAbort = 0;
    MP4PlayerCtl.FirstPlay = 1;
    MP4PlayerCtl.PlayCurrTime = 0;
    MP4PlayerCtl.PlayFrame = 0;

	OSResumeThread(&Thread[0]);
	OSResumeThread(&Thread[1]);
	OSResumeThread(&Thread[2]);
}

VideoPlayer::~VideoPlayer()
{
	EXIT_PLAYBACK = true;

	OSJoinThread(&Thread[2], NULL);
    //OSJoinThread(&Thread[3], NULL);

	MEMFreeToDefaultHeap(GpClient[0]);
    MEMFreeToDefaultHeap(GpCmd[0]);
    FSDelClient(GpClient[0], FS_RET_NO_ERROR);

	FreeShader();
	FreeAttribData();

	delete internal_;
}

void VideoPlayer::SetVolume( float volume )
{
	//Volume = volume;
}

void VideoPlayer::Play( const boost::shared_ptr< Video > &video )
{
	EXIT_PLAYBACK = false;

	mp4Filename[ 0 ] = video->Path.c_str();
	mp4Filename[ 1 ] = video->Path.c_str();

/*#ifdef INPUTNAME_DEFINED
    mp4Filename[0] = MP4_INPUT_SAMPLE1;     // set input file name
    mp4Filename[1] = MP4_INPUT_SAMPLE2;     // set input file name
#endif*/

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

	GLOBAL_VIDEO_OVERRIDE = true;
    OSResumeThread(&Thread[0]);
    OSResumeThread(&Thread[1]);

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
    /*OSCreateThread( &Thread[3],   // ptr to the thread to init
                    MP4PlayTVorDRC,                 // ptr to the start routine
                    1,                              // params passed to start routine
                    NULL,
                    ThreadStack[3] + STACK_SIZE,    // initial stack address
                    STACK_SIZE,                     // stack size
                    16,                             // scheduling priority
                    0);*/         // detached

    OSResumeThread(&Thread[2]);
    //OSResumeThread(&Thread[3]);
}

void VideoPlayer::DrawFrame()
{
   /* s32 ret;
    u32 vsys_currtime;

    for (i = 0; i < 1; i++)
    {
        if ((MP4PlayerCtl.CurPlayState != 0) && (MP4PlayerCtl.SyncStop == 0))
        {
            if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 1)
            {
                ret = VideoDraw(MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].bufp, i);
                if (ret != 0)
                {
                    OSReport("VideoDraw Failed.\n");
                    MP4PlayerCtl.VThreadStop[i] = 1;
                    //break;
					return;
                }
                if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 1)
				{

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

                }
            }
        }
        else
        {
            if ((MP4PlayerCtl.VThreadStop[i] == 0) && (MP4PlayerCtl.SyncStop == 0))
            {
                if (((vsys_currtime - MP4PlayerCtl.PlayBaseTime + MP4PlayerCorePtr[i]->SeekOffsetTime) >= MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS))
                {
                    if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 1)
                    {
                        if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS && (MP4PlayerCtl.CurPlayState == 0))
                        {
                            if ((((vsys_currtime - MP4PlayerCtl.PlayBaseTime + MP4PlayerCorePtr[i]->SeekOffsetTime) - MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS) > VIDEOSKIP_DELAY))
                            {
                                MP4PlayerCorePtr[i]->FrameSkipFlag = 1;
                                OSReport("CurrTime:%d, VPTS:%d, thread:%d, mode:%d\n", (vsys_currtime - MP4PlayerCtl.PlayBaseTime + MP4PlayerCorePtr[i]->SeekOffsetTime), MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS, i, MP4PlayerCtl.CurPlayState);
                                OSReport("vsys_currtime:%d\n", vsys_currtime);
                                OSReport("MP4PlayerCtl.PlayBaseTime:%d\n", MP4PlayerCtl.PlayBaseTime);
                                OSReport("FrameSkip\n");
                            }
                            else
                            {
                                MP4PlayerCorePtr[i]->FrameSkipFlag = 0;
                            }
                        }
#ifdef PRINT_TIME
                        starttime = OSTicksToMilliseconds(OSGetTime());
#endif
                        // video frame draw
#ifdef PRINT_LOG
                        OSReport("CurrTime:%d, VPTS:%d, VDIFF:%d, thread:%d\n",
                            (vsys_currtime - MP4PlayerCtl.PlayBaseTime), MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS, abs((vsys_currtime - MP4PlayerCtl.PlayBaseTime) - MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS), i);
#endif
                        ret = VideoDraw(MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].bufp, i);
                        MP4PlayerCtl.PlayCurrTime = MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].PTS;
                        MP4PlayerCtl.PlayFrame++;
                        MP4PlayerCtl.PlayTime = vsys_currtime - MP4PlayerCtl.PlayBaseTime;
                        if (ret != 0)
                        {
                            OSReport("VideoDraw Failed.\n");
                            MP4PlayerCtl.VThreadStop[i] = 1;
							return;
                            //break;
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
            }
        }
    }*/
}

boost::shared_ptr< Texture2D > VideoPlayer::GetTexture()
{
	return boost::shared_ptr< Texture2D >( NULL );
}
