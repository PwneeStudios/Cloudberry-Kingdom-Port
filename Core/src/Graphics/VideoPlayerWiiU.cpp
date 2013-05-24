#include <Graphics/VideoPlayer.h>

#include <Architecture/Scheduler.h>
#include <Core.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/TextureWiiUInternal.h>
#include <Content/Wad.h>
#include <Core.h>
#include <Graphics/Video.h>
#include <Graphics/Texture2D.h>
#include <Utility/Log.h>

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
#include <nn/erreula.h>
#include "WiiU/MovieTest.h"
#include "WiiU/videorender.h"

#pragma ghs nowarning 111

/*=========================================================================*
            definitions
 *=========================================================================*/

#define UNASSIGNED_END_TIME_STAMP   0xFFFFFFFFFFFFFFFFULL

#define INPUTNAME_DEFINED

#ifdef INPUTNAME_DEFINED
#define MP4_INPUT_SAMPLE1       "/vol/content/0010/Movies/LogoSalad.mp4";    // TV
#define MP4_INPUT_SAMPLE2       "/vol/content/0010/Movies/LogoSalad.mp4";	// DRC
#endif

#define VIDEOSKIP_DELAY         (70)                            // permissible delay time
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

FSClient*      GpClient[2];
FSCmdBlock*    GpCmd[2];
FSFileHandle   Gfh[2];

s32 exc_start_time_stamp[2];
s32 exc_end_time_stamp[2];

bool EXIT_PLAYBACK = false;
bool GLOBAL_VIDEO_OVERRIDE = false;
static void (*UpdateElapsedTime)(float, bool) = NULL;
void (*DrawSubtitles)() = NULL;

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

#endif

#endif

// Flag in CoreWiiU to have it re-enable the home button when warning fades out.
extern bool ReEnableHomeButton;

// Subtitle parameters from Video.cpp.
extern bool		StartTimeSet;
extern OSTick	StartTime;

// Preallocated buffer for loading movies. Defined in videoplayer.cpp.
extern void *MovieBuffer;


struct VideoPlayerInternal
{
};

bool threadsAlive = false;
bool shadersInitialized = false;
bool attributesInitialized = false;

VideoPlayer::VideoPlayer( void (*UpdateElapsedTime)(float, bool), void (*DrawSubtitles)() )
	: internal_( new VideoPlayerInternal )
	, IsLooped( false )
{
	::UpdateElapsedTime = UpdateElapsedTime;
	::DrawSubtitles = DrawSubtitles;

	StartTimeSet = false;

	/*InitShader();
	shadersInitialized = true;
    InitAttribData();
	attributesInitialized = true;*/
}

void ForceKillVideoPlayer()
{
	EXIT_PLAYBACK = true;

	if(UpdateElapsedTime)
		UpdateElapsedTime( 10000000.f, false );

	OSMemoryBarrier();

	if( threadsAlive )
	{
		/*OSJoinThread(&Thread[0], NULL);
		OSJoinThread(&Thread[1], NULL);*/

		//OSJoinThread(&Thread[2], NULL);
		//OSJoinThread(&Thread[3], NULL);
	}
	threadsAlive = false;

	/*if( shadersInitialized )
		FreeShader();
	shadersInitialized = false;
	
	if( attributesInitialized )
		FreeAttribData();
	attributesInitialized = false;*/

	ReEnableHomeButton = true;
	if( nn::erreula::IsAppearHomeNixSign() )
		nn::erreula::DisappearHomeNixSign();
}

// Flag to pause the scheduler during initial logo.
extern bool SchedulerPausedForLogo;

// Resume the scheduler. Defined in SchedulerWiiU.cpp.
extern void ResumeScheduler();

VideoPlayer::~VideoPlayer()
{
	ForceKillVideoPlayer();

	if( SchedulerPausedForLogo )
	{
		ResumeScheduler();
		SchedulerPausedForLogo = false;
		OSMemoryBarrier();
	}

	delete internal_;
}

void VideoPlayer::SetVolume( float volume )
{
	//Volume = volume;
}

void VideoPlayer::Play( const boost::shared_ptr< Video > &video )
{
	GLOBAL_VIDEO_OVERRIDE = false;
	EXIT_PLAYBACK = true;
	threadsAlive = true;
	return;
}

void VideoPlayer::DrawFrame()
{
   /* s32 ret;
    u32 vsys_currtime;

    vsys_currtime = OSTicksToMilliseconds(OSGetTime());
	for( int i = 0; i < 1; i++ )
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
                        LOG_WRITE("FrameSkip\n");
                    }
                    else
                    {
                        MP4PlayerCorePtr[i]->FrameSkipFlag = 0;
                    }
                }
                if (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 1)
				{

                    ret = VideoDraw(MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].bufp, i);
                    if (ret != 0)
                    {
                        LOG_WRITE("VideoDraw Failed.\n");
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
            if (!vendflag[i] && MP4PlayerCorePtr[i]->vthread_end && (MP4PlayerCorePtr[i]->df_v == MP4PlayerCorePtr[i]->ff_v) && (MP4PlayerCorePtr[i]->OutputVideoInfo[MP4PlayerCorePtr[i]->df_v].Status == 0))
            {
                LOG_WRITE("Video[%d] Thread End\n", i);
                vendflag[i] = 1;
            }
        }
    }*/
}

boost::shared_ptr< Texture2D > VideoPlayer::GetTexture()
{
	return boost::shared_ptr< Texture2D >( NULL );
}
