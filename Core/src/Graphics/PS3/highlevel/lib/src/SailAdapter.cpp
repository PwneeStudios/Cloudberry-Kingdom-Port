/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#include <string.h>
#include <stdlib.h>

#include <sys/spu_initialize.h>
#include <sys/event.h>
#include <sysutil/sysutil_sysparam.h>
#include <cell/sysmodule.h>
#include <cell/atomic.h>
#include <assert.h>
#include <cell/gcm.h>

#include "SailAdapter.h"
#include "SailAllocator.h"

//E Optimal quality/performance settings for magnification scaling
#define VPOST_SCALER_TYPE  CELL_VPOST_SCALER_TYPE_LINEAR_SHARP
#define VPOST_IPC_TYPE     CELL_VPOST_IPC_TYPE_LINEAR

//E Optimal number of SPUs for DivX HD, this is only used
//  if a spurs instance is not supplied on init.
#define NUM_SPU             2
#define SPURS_SPU_PRIORITY  100
#define SPURS_PPU_PRIORITY  100

#ifdef _DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 
#endif

#define EMSG(x, ret)   PRINTF("**%s:L%d ERROR! " x " failed. (0x%08X)\n", \
                             __func__, __LINE__, ret)

#define DP0(x, ...)    PRINTF(x, __func__, __LINE__, ##__VA_ARGS__)
#define DP(...)        DP0("  %s:L%d " __VA_ARGS__)

#define ZERO_CLEAR(x, z)          memset(x, 0, z);
#define CAST_PTR_TO_UINT64(x)     ((uint64_t)(intptr_t)(x))
#define CAST_UINT64_TO_PTR(t, x)  ((t)(intptr_t)(x))

#ifdef _DEBUG
#define DASSERT(x) \
    do { if(!(x)) { \
        PRINTF("** %s:L%d ASSERT FAILED!! %s\n", __func__, __LINE__, #x); \
        assert(0); \
    } } while (0)

#define DASSERT_NOT_REACHED() \
    do { \
        PRINTF("** %s:L%d ASSERT_NOT_REACHED FAILED!!\n", __func__, __LINE__); \
        assert(0); \
    } while (0)

#else
#define DASSERT(x)
#define DASSERT_NOT_REACHED()
#endif

#define ALIGN_1MB       (0x100000)
#define ROUNDUP(x, a)   (((x)+((a)-1))&(~((a)-1)))

namespace cell {
namespace Sail {

/**E
 * sailAdapter Constructor  
 * 
 * @returns nothing
 * @param [I/-] FileReplacement pointer or NULL
 * @param [I/-] MemoryReplacement pointer or NULL
 */
sailAdapter::sailAdapter(fsallocator*  FileReplacement,
                         memallocator* MemoryReplacement) :
    mpChangeRead(0),
    play_state(MP_INIT),
    mpFileAllocator(FileReplacement),
    mpMemoryAllocator(MemoryReplacement),
    alloccount(0),
    alloctotal(0),
    alloctexturetotal(0),
    mpInternalSpurs(0),
    mpActiveSpurs(0)
{
    ;
}

sailAdapter::~sailAdapter(void)
{
    (void)sys_lwmutex_lock(&mMutex, /*timeout*/0);
    if (MP_DONE != play_state) {
        int ret;
        ret = finalize();
        if (0 > ret) {
            EMSG("finalize()", ret);
        }
        play_state=MP_DONE;
    }
    (void)sys_lwmutex_unlock(&mMutex);
    shutdown();
}

/**E
 * startup Sail, Creates mutexes, loads modules and creates an internal spurs
 * instances if required   
 * 
 * @return true if succeeded.
 * @param [I/-] pSpurs instance pointer, if NULL a spurs instance is created
 *              internally
 */
bool sailAdapter::startup(CellSpurs* pSpurs)
{
    int ret;
	// FIXME: These are initialized in CorePS3.cpp and never unloaded.
    /*ret = cellSysmoduleLoadModule(CELL_SYSMODULE_PAMF);
    if (ret < 0) {
        EMSG("cellSysmoduleLoadModule(CELL_SYSMODULE_PAMF)", ret);
        return false;
    }
    
    ret = cellSysmoduleLoadModule(CELL_SYSMODULE_SAIL);
    if (ret < 0) {
        EMSG("cellSysmoduleLoadModule(CELL_SYSMODULE_SAIL)", ret);
        return false;
    }*/
 
    // lwmutex for pause
    {
        sys_lwmutex_attribute_t attr;
        sys_lwmutex_attribute_initialize(attr);
        sys_lwmutex_attribute_name_set(attr.name, "hlp_mx0");
        ret = sys_lwmutex_create(&mMutex, &attr);

        if (0 > ret) {
            EMSG("sys_lwmutex_create()", ret);
            return false;
        }
    }

    if (NULL == pSpurs) {
        pSpurs = (CellSpurs*)
                 mpMemoryAllocator->Allocate(sizeof(CellSpurs),
                                             /*boundary*/128);
        if (NULL == pSpurs) {
            DP("failed to onMemAlloc() for SPURS\n");
            return false;
        }

        CellSpursAttribute attr;
        ret = cellSpursAttributeInitialize(&attr,
                                           NUM_SPU,
                                           SPURS_SPU_PRIORITY,
                                           SPURS_PPU_PRIORITY,
                                           false);
        DASSERT(ret == CELL_OK);
        ret = cellSpursAttributeEnableSpuPrintfIfAvailable(&attr);
        DASSERT(ret == CELL_OK);
        ret = cellSpursAttributeSetNamePrefix(&attr,
                                              "hlpSpurs",
                                              strlen("hlpSpurs"));
        DASSERT(ret == CELL_OK);
        ret = cellSpursInitializeWithAttribute(pSpurs, &attr);
        DASSERT(ret == CELL_OK);    
        mpInternalSpurs = pSpurs;
    }
    else
    {
        mpInternalSpurs = NULL;
    }
    mpActiveSpurs=pSpurs;
    return true;
}

/**E
 * Initializes Sail, Pre-configured to meet the needs of most game developers.
 * 
 * @return true if succeeded.
 * @param [I/-] videoFormat refers to the output format of RGBA or YUV 4:2:0
 * @param [I/-] releaseDelay refers to the number of frames that Sail keeps
 *              internally before releasing them.
 * @param [I/-] requested output texture width. If the value is 0 the source
 *              width is used.
 * @param [I/-] requested output texture height. If the value is 0 the source
 *              height is used.
 */
bool sailAdapter::initialize(int videoFormat,
                             int releaseDelay,
                             int width,
                             int height)
{
    int ret;

    mReservedSize=0;
    mpReservedAddr=NULL;

    //E Default Stream Volume Set to 1.0f, valid values are -16.0f -> +16.0f
    mStreamVolume=1.0f;

    play_state=MP_INIT;
    mpDescriptor  = NULL;
    mPlayerState  = 0;
    mPlayerPaused = 0;

    mpDescriptor = 0;
    mPlayerState = 0;
    mPlayerPaused= 0;
    mStreamType  = 0;
    mTimeScale   = 0;
    mTimeRate    = 0;
    mCurrentTime = 0;
    mBeginOffset = 0;
    mEndOffset   = 0;
    mMovieDurationMsec = 0;


    // future
    ret = cellSailFutureInitialize(&mFuture);
    if (0 > ret) {
        EMSG("cellSailFutureInitialize()", ret);
        return false;
    }
   
    // player
    {
        CellSailPlayerAttribute PlayerAttr;
        ZERO_CLEAR(&PlayerAttr, sizeof(CellSailPlayerAttribute));
        
        PlayerAttr.playerPreset      = CELL_SAIL_PLAYER_PRESET_AV_SYNC_AUTO_DETECT; 
        
        PlayerAttr.maxAudioStreamNum = 1;
        PlayerAttr.maxVideoStreamNum = 1;
        PlayerAttr.maxUserStreamNum  = 0;
        PlayerAttr.queueDepth        = 0;

        CellSailPlayerResource res;
        ZERO_CLEAR(&res, sizeof(res));

        res.pSpurs = mpActiveSpurs;

        // mem allocator
        CellSailMemAllocatorFuncs memFuncs = {
            (CellSailMemAllocatorFuncAlloc)onMemAllocStatic,
            (CellSailMemAllocatorFuncFree) onMemFreeStatic,
        };
        CellSailMemAllocator allocator;
        ret = cellSailMemAllocatorInitialize(&allocator,
                                             &memFuncs,
                                             this);
        if (0 > ret) {
            EMSG("cellSailMemAllocatorInitialize()", ret);
            return false;
        }

        // player
        ret = cellSailPlayerInitialize2(
            &mPlayer,
            &allocator,    // mem allocator
            onPlayerStatic, // callback
            this,           //callback arg
            &PlayerAttr,
            &res);
        if (0 > ret) {
            EMSG("cellSailPlayerInitialize2()", ret);
            return false;
        }     
    }

    // vpost
    if ((width!=0)&&(height!=0))
    {
        CellVpostCtrlParam ctrl;
        ZERO_CLEAR(&ctrl, sizeof(ctrl));
        ctrl.scalerType = VPOST_SCALER_TYPE;
        ctrl.ipcType    = VPOST_IPC_TYPE;
        ctrl.outWidth   = width;
        ctrl.outHeight  = height;
        ctrl.outWindow.x = 0;
        ctrl.outWindow.y = 0;
        ctrl.outWindow.width = width;
        ctrl.outWindow.height = height;
        ret = cellSailPlayerSetParameter(&mPlayer,
                                         CELL_SAIL_PARAMETER_ENABLE_VPOST,
                                         0,
                                         CAST_PTR_TO_UINT64(&ctrl));
        if (0 > ret) {
            EMSG("cellSailPlayerSetParameter()", ret);
            return false;
        }
    }

    // sound adapter
    {
        CellSailSoundAdapterFuncs soundFuncs = {
            (CellSailSoundAdapterFuncMakeup)       NULL,
            (CellSailSoundAdapterFuncCleanup)      NULL,
            (CellSailSoundAdapterFuncFormatChanged)onSoundAdapterFormatChangedStatic,
        };
        ret = cellSailSoundAdapterInitialize(&mSoundAdapter,
                                             &soundFuncs,
                                             this);
        if (0 > ret) {
            EMSG("cellSailSoundAdapterInit()", ret);
            return false;
        }
        ret = cellSailPlayerSetSoundAdapter(&mPlayer,
                                            0,
                                            &mSoundAdapter);
        if (0 > ret) {
            EMSG("cellSailPlayerSetSoundAdapter()", ret);
            return false;
        }
    }

#if 1
    //E APOST_SRC converts all non-48khz streams to 48khz internally
    ret = cellSailPlayerSetParameter(&mPlayer,
                                     CELL_SAIL_PARAMETER_ENABLE_APOST_SRC,
                                     0,
                                     /*enable*/1);
    if (0 > ret) {
        EMSG("cellSailPlayerSetParameter()", ret);
        return ret;
    }


    CellSailAudioFormat aFormat;
    memset(&aFormat, 0xFF, sizeof(aFormat));
    aFormat.fs = CELL_SAIL_AUDIO_FS_48000HZ;
    ret = cellSailSoundAdapterSetPreferredFormat(&mSoundAdapter,
                                                 &aFormat);
    if (0 > ret) {
        EMSG("cellSailSoundAdapterSetPreferredFormat()", ret);
        return ret;
    }
#endif

    // graphics adapter
    {
        CellSailGraphicsAdapterFuncs graphicsFuncs = {
            (CellSailGraphicsAdapterFuncMakeup)       NULL,
            (CellSailGraphicsAdapterFuncCleanup)      NULL,
            (CellSailGraphicsAdapterFuncFormatChanged)onGraphicsAdapterFormatChangedStatic,
            (CellSailGraphicsAdapterFuncAllocFrame)   onGraphicsAdapterAllocFrameStatic,
            (CellSailGraphicsAdapterFuncFreeFrame)    onGraphicsAdapterFreeFrameStatic,
        };
        ret = cellSailGraphicsAdapterInitialize(&mGraphicsAdapter,
                                                &graphicsFuncs,
                                                this);
        if (0 > ret) {
            EMSG("cellSailGraphicsAdapterInit()", ret);
            return false;
        }

        CellSailVideoFormat vFormat;
        memset(&vFormat, 0xFF, sizeof(vFormat));
        vFormat.coding = videoFormat;

        vFormat.alpha=0xff;

        vFormat.width  = width; 
        vFormat.height = height;
        vFormat.aspectRatio  = CELL_SAIL_VIDEO_ASPECT_RATIO_1_1;
        vFormat.scan   = CELL_SAIL_VIDEO_SCAN_PROGRESSIVE;
        vFormat.coding = videoFormat;
    
        ret = cellSailGraphicsAdapterSetPreferredFormat(&mGraphicsAdapter,
                                                        &vFormat);
        if (0 > ret) {
            EMSG("cellSailGraphicsAdapterSetPreferredFormat()", ret);
            return false;
        }
        ret = cellSailPlayerSetGraphicsAdapter(&mPlayer,
                                               0,
                                               &mGraphicsAdapter);
        if (0 > ret) {
            EMSG("cellSailPlayerSetGraphicsAdapter()", ret);
            return false;
        }
    }

    if (0 < releaseDelay) {
        ret = cellSailPlayerSetParameter(
            &mPlayer,
            CELL_SAIL_PARAMETER_GRAPHICS_ADAPTER_BUFFER_RELEASE_DELAY,
            /*video es index*/ 0,
            releaseDelay);
        if (0 > ret) {
            EMSG("cellSailPlayerSetParameter()", ret);
            return false;
        }
    }

    return true;
}

/**E
 * Finalize Sail, Stop callbacks and take down internal threads
 * 
 * @return true if succeeded.
 */
bool sailAdapter::finalize(void)
{
    bool bRet=true;
    int ret;

    (void)cellSailFutureSet(&mFuture, CELL_SAIL_ERROR_CANCEL);

    ret = cellSailPlayerFinalize(&mPlayer);
    DASSERT (ret>=0);
    if (ret < 0) {
        EMSG("cellSailPlayerFinalize\n", ret);
        bRet=false;
    }
    ret = cellSailSoundAdapterFinalize(&mSoundAdapter);
    DASSERT (ret>=0);
    if (ret < 0) {
        EMSG("cellSailSoundAdapterFinalize\n", ret);
        bRet=false;
    }
    ret = cellSailGraphicsAdapterFinalize(&mGraphicsAdapter);
    DASSERT (ret>=0);
    if (ret < 0) {
        EMSG("cellSailGraphicsAdapterFinalize\n", ret);
        bRet=false;
    }
    ret = cellSailFutureFinalize(&mFuture);
    DASSERT (ret>=0);
    if (ret < 0) {
        EMSG("cellSailFutureFinalize\n", ret);
        bRet=false;
    }
    return bRet;
}

/**E
 * Shutdown Sail, Destroy mutexes, unload modules and finalize internally
 * created spurs instances.   
 * 
 * @return true if succeeded.
 */
bool sailAdapter::shutdown(void)
{
    bool bRet=true;
    int ret;

    ret = sys_lwmutex_destroy(&mMutex);
    DASSERT (ret>=0);
    if (ret < 0) {
        EMSG("sys_lwmutex_destroy\n", ret);
        bRet=false;
    }

	// FIXME: These are owned by CorePS3.cpp.
    /*ret = cellSysmoduleUnloadModule(CELL_SYSMODULE_PAMF);
    DASSERT (ret>=0);
    if (ret < 0) {
        EMSG("cellSysmoduleUnloadModule(CELL_SYSMODULE_PAMF)\n", ret);
        bRet=false;
    }

    ret = cellSysmoduleUnloadModule(CELL_SYSMODULE_SAIL);
    DASSERT (ret>=0);
    if (ret < 0) {
        EMSG("cellSysmoduleUnloadModule(CELL_SYSMODULE_SAIL)\n", ret);
        bRet=false;
    }*/
    
    if (mpInternalSpurs) {
        ret = cellSpursFinalize(mpInternalSpurs);
        if (ret != CELL_OK) {
            EMSG("cellSpursFinalize\n", ret);
            bRet=false;
        }
        onMemFree(/*boundary*/128, mpInternalSpurs);
        mpInternalSpurs = NULL;
    }
    mpActiveSpurs = NULL;

    return bRet;
}

/**E
 * Waits for asynchronous calls to complete to make them synchronous and
 * simplify logic of Adapter  
 * 
 * @returns CELL_OK, hlPlayer_WAITING or an error (-1)
 */
int sailAdapter::waitResponse(void)
{
    int ret;
    int result;

    ret = cellSailFutureGet(&mFuture, 0, &result);
    if (0 > ret) {
        EMSG("cellSailFutureGet()", ret);
        return -1;
    }

    (void)cellSailFutureReset(&mFuture, /*wait*/ false);
    if(result) {
        return CELL_OK;
    }
    return hlPlayer_WAITING;
}

/**E
 * Open Video File
 * 
 * @return true if succeeded.
 * @param [I/-] pPath a pointer to the full path and filename to play
 */
bool sailAdapter::openStream(char const* pPath)
{
    int ret;
  
    if (mpDescriptor) {
        return false;
    }

    /* Detect the stream type simply by looking at the extension */
    const char *tmpext = strrchr( pPath, '.' );
    if(strncasecmp (tmpext+1,"MP4",3)==0) {
        mStreamType = CELL_SAIL_STREAM_MP4;
    } else if(strncasecmp (tmpext+1,"PAM",3)==0) {
        mStreamType = CELL_SAIL_STREAM_PAMF;
    } else if(strncasecmp (tmpext+1,"AVI",3)==0) {
        mStreamType = CELL_SAIL_STREAM_AVI;
    } else {
        return false;
    }

    ret = cellSailPlayerBoot(&mPlayer, CAST_PTR_TO_UINT64(&mFuture));
    DASSERT (ret>=0);
    if (0 > ret) {
        EMSG("cellSailPlayerBoot()", ret);
        return false;
    }

    if (0>waitResponse()) {
        return false;
    }

    strcpy(mUri, "x-cell-fs://");
    strcpy(&mUri[12], pPath);
    mUri[sizeof(mUri) - 1] = '\0';

    CellSailDescriptor *pDesc = NULL;
    ret = cellSailPlayerCreateDescriptor(
        &mPlayer,
        mStreamType,
        NULL,   // media info
        mUri,
        &pDesc);

    if (0 > ret) {
        EMSG("cellSailPlayerCreateDescriptor()", ret);
        return false;
    }
   
    ret = cellSailPlayerAddDescriptor(&mPlayer, pDesc);
    DASSERT (ret>=0);
    if (0 > ret) {
        EMSG("cellSailPlayerAddDescriptor()", ret);
    } else {
        ret = cellSailPlayerOpenStream(&mPlayer, CAST_PTR_TO_UINT64(&mFuture));
        DASSERT (ret>=0);
        if (0 > ret) {
            EMSG("cellSailPlayerOpenStream()", ret);
        } else {
            ret = waitResponse();
            DASSERT (ret>=0);
        }
        if (0 > ret) {
            (void)cellSailPlayerDestroyDescriptor(&mPlayer, pDesc);
            return false;
        } else {
            mpDescriptor = pDesc;
        }
    }

    return true;
}

/**E
 * Populate Time info for begin and end of the stream
 * 
 * @return true if succeeded.
 */
bool sailAdapter::PopulateStreamInfo(void)
{
    int ret;
    bool bRet=true;

    // in the case of mp4, i/o access may occur(i.e. blocking call)
    ret = cellSailDescriptorCreateDatabase(mpDescriptor,
                                           &mDatabase,
                                           sizeof(mDatabase),
                                           0);
    if (0 > ret) {
        EMSG("cellSailDescriptorDestroyDatabase()", ret);
        return false;
    }
    switch (mStreamType) {
    case CELL_SAIL_STREAM_PAMF: {
                        
        CellPamfTimeStamp startTime;
        ret = cellPamfReaderGetPresentationStartTime(&mDatabase.pamfReader,
                                                     &startTime);
        if (0 > ret) {
            EMSG("cellPamfReaderGetPresentationStartTime()", ret);
            bRet=false;
            DASSERT_NOT_REACHED();
        }
            
        mBeginOffset = ((uint64_t)startTime.upper) << 32 | startTime.lower;

        CellPamfTimeStamp endTime;
        ret = cellPamfReaderGetPresentationEndTime(&mDatabase.pamfReader,
                                                   &endTime);
        if (0 > ret) {
            EMSG("cellPamfReaderGetPresentationEndTime()", ret);
            bRet=false;
            DASSERT_NOT_REACHED();
        }

        mTimeRate  = 1;
        mTimeScale = 90000/*Hz*/;

        mEndOffset = ((uint64_t)endTime.upper) << 32 | endTime.lower;
        mMovieDurationMsec = ((uint64_t)(endTime.upper - startTime.upper)) << 32 |
                             (endTime.lower - startTime.lower) / 90/*kHz*/;
        break;
    }
    case CELL_SAIL_STREAM_MP4: {
        CellSailMp4MovieInfo info;
        ret = cellSailMp4MovieGetMovieInfo(&mDatabase.mp4Movie, &info);
        if (0 > ret) {
            EMSG("cellSailMp4MovieGetMovieInfo()", ret);
            bRet=false;
            DASSERT_NOT_REACHED();
        }
        mTimeRate = 1;
        mTimeScale  = info.movieTimeScale;
        mBeginOffset = 0;
        mEndOffset = info.movieDuration - info.movieTimeScale;
        mMovieDurationMsec = (uint64_t)info.movieDuration * 1000 /
                             mTimeScale;
        break;
    }

    case CELL_SAIL_STREAM_AVI: {
        CellSailAviMovieInfo info;
        ret = cellSailAviMovieGetMovieInfo(&mDatabase.aviMovie, &info);
        if (0 > ret) {
            EMSG("cellSailAviMovieGetMovieInfo()", ret);
            DASSERT_NOT_REACHED();
        }
        mTimeRate    = info.scale; //1001
        mTimeScale   = info.rate;  //60000
        mBeginOffset = 0;
        mEndOffset   = info.length - 1;
        mMovieDurationMsec = (uint64_t)info.length * info.scale * 1000 /
                             info.rate;
        break;
    }
    default:
        DASSERT_NOT_REACHED();
        mBeginOffset = 0;
        mEndOffset = 0;
        mMovieDurationMsec = 0;
    }

    //E We don't need this data anymore since we have extracted the required
    //  info from it
    ret = cellSailDescriptorDestroyDatabase(mpDescriptor,&mDatabase);
    if (0 > ret) {
        bRet=false;
        EMSG("cellSailDescriptorDestroyDatabase()", ret);
    }
    return bRet;
}

/**E
 * Populate Time info for begin and end of the stream
 * 
 * @return true if succeeded.
 */
bool sailAdapter::start(CellSailStartCommand *pCommand, bool looping)
{  
    int ret;
    ret = cellSailPlayerStart(&mPlayer,
                              pCommand,
                              CAST_PTR_TO_UINT64(&mFuture));
    if (0 > ret) {
        return false;
    }

    if (looping) {
        cellSailPlayerSetRepeatMode(&mPlayer,
                                    CELL_SAIL_REPEAT_LOOP,
                                    NULL);
    }

    mPlayerState=CELL_SAIL_PLAYER_STATE_RUNNING;
    if (0>waitResponse()) {
        return false;
    }
    return true;
}

/**E
 * Start Trick Mode
 * 
 * @return true if succeeded.
 * @param [I/-] direction  - true=Forward, false=Reverse
 * @param [I/-] trickSpeed - Valid trick speeds are 0.2 -> 50 in both directions
 */
bool sailAdapter::TrickStart(bool direction, float trickSpeed)
{
    int ret;
    CellSailStartCommand command;
    ZERO_CLEAR(&command, sizeof(command));

    // Set the direction
    if (direction) {
        // Fastforward
        command.startType=CELL_SAIL_START_EP_SKIP;
    } else {
        // Rewind
        command.startType=CELL_SAIL_START_EP_SKIP_REVERSE;
    }

    // Set the Speed
    command.startArg = (uint32_t)(trickSpeed * 256.f);
    command.seekType = CELL_SAIL_SEEK_CURRENT_POSITION;
    command.flags   |= CELL_SAIL_START_FLAG_PAUSE_END;

    ret = cellSailPlayerStart(&mPlayer,
                              &command,
                              NULL);
    if (0 > ret) {
        EMSG("TrickStart - cellSailPlayerStart()", ret);
        return false;
    }
    return true;
}

/**E
 * Start Fast Playback Mode
 * 
 * @return true if succeeded.
 * @param [I/-] trickSpeed - valid playspeeds are 2->4
 */
bool sailAdapter::TrickFastPlayback(int trickSpeed)
{
    int ret;
    CellSailStartCommand command;
    ZERO_CLEAR(&command, sizeof(command));

    if (trickSpeed <2) {
        trickSpeed=2;
    } else if (trickSpeed>4) {
        trickSpeed=4;
    }

    command.startType=CELL_SAIL_START_TIME_SCALE;

    // Set the Speed
    command.startArg = (uint32_t)(trickSpeed * 256.f);
    command.seekType = CELL_SAIL_SEEK_CURRENT_POSITION;
    command.flags   |= CELL_SAIL_START_FLAG_PAUSE_END;

    ret = cellSailPlayerStart(&mPlayer,
                              &command,
                              NULL);
    if (0 > ret) {
        EMSG("cellSailPlayerStart()", ret);
        return false;
    }
    return true;
}

/**E
 * Resume regular playback speed (1x) after being in trick mode
 * 
 * @return true if succeeded.
 */
bool sailAdapter::TrickResumePlayback(void)
{
    int ret;
    CellSailStartCommand command;
    ZERO_CLEAR(&command, sizeof(command));

    command.startType=CELL_SAIL_START_NORMAL;

    // Set the Speed
    command.startArg = 0;

    command.seekType = CELL_SAIL_SEEK_CURRENT_POSITION;
    
    ret = cellSailPlayerStart(&mPlayer,
                              &command,
                              NULL);
    if (0 > ret) {
        EMSG("cellSailPlayerStart()", ret);
        return false;
    }
    return true;
}

/**E
 * Jump to a time offset
 * 
 * @return true if succeeded.
 * @param [I/-] jumptime value
 */
bool sailAdapter::JumpToLocation(uint64_t jumptime)
{
    int ret;
    CellSailStartCommand command;
    ZERO_CLEAR(&command, sizeof(command));

    command.startType = CELL_SAIL_START_NORMAL;
    command.seekType  = CELL_SAIL_SEEK_ABSOLUTE_TIME_POSITION;
    command.seekArg   = (jumptime * mTimeScale) / (mTimeRate * 1000ULL);

    ret = cellSailPlayerStart(&mPlayer,
                              &command,
                              NULL);
    if (0 > ret) {
        EMSG("cellSailPlayerStart()", ret);
        return false;
    }
    return true;
}

/**E
 * Returns the start time or 0
 * 
 * @return Start Time
 */
uint64_t sailAdapter::GetStartTime()
{
    //E always 0 with mp4 and avi however pamf is not guarateed to be 0
    return mBeginOffset/mTimeScale;
}

/**E
 * Returns the end time or 0
 * 
 * @return End Time
 */
uint64_t sailAdapter::GetEndTime()
{
    //E Calculated on init    
    return mMovieDurationMsec;
}

/**E
 * Retrieves a copy of the current time
 * 
 * @return true if succeeded.
 * @param [-/O] jumptime value
 */
bool sailAdapter::GetCurrentTime(uint64_t* CurrentTime)
{
    if (0>=mCurrentTime)
        return false;

    uint64_t currentTime = mCurrentTime;
    *CurrentTime = currentTime / 1000;
    return true;
}

/**E
 * Get Video Frame
 * 
 * @return CELL_OK if succeeded.
 * @param [I/O] CellSailGraphicsFrameInfo Structure
 */
int sailAdapter::getVideoFrame(CellSailGraphicsFrameInfo *pInfo) 
{
    int ret;

    ret = cellSailGraphicsAdapterGetFrame(&mGraphicsAdapter, pInfo);
    if (0>ret)
        return ret;

    uint64_t currentTime = 0;
    /*E
     * As the first few frames are being buffered this will return an error
     * which is expected. 
     * If you're using the current time value only trust those that pass
     * through this following call successfully.
     */
    cellSailGraphicsAdapterPtsToTimePosition(&mGraphicsAdapter,
                                             pInfo->pts,
                                             &currentTime);
    (void)cellAtomicStore64(&mCurrentTime, currentTime);
    return ret;
}

/**E
 * Set Stream Volume
 * 
 * @return true if succeeded.
 * @param [I/-] requestedVolume is valid from 0.0f -> 16.0f
 *              (Audio will clip and sound bad when this value is high)
 */
bool sailAdapter::SetVolume(float requestedVolume)
{
    if ((requestedVolume>16.0f)||(requestedVolume<0.0f))
        return false;

    union {
        float    f;
        uint32_t u;
    } v;
    v.f = requestedVolume;
    union {
        float*    f;
        uint32_t* u;
    } ea;
    ea.f = &mStreamVolume;
    (void)cellAtomicStore32(ea.u, v.u);
    return true;
}

/**E
 * Toggle Pause
 * 
 * @return true if succeeded.
 */
bool sailAdapter::togglePause(void)
{ 
    int ret;

    int paused = !mPlayerPaused;
    ret = cellSailPlayerSetPaused(&mPlayer, (bool)paused);
    DASSERT (ret>=0);
    if (0 > ret) {
        EMSG("cellSailPlayerSetPaused()", ret);
        return false;
    }
    return true;
}

/**E
 * Check Playback Status
 * Used throughout this adapter to determine the current state.
 *
 * @return Adapter State
 */
cell::Sail::sailAdapter::sailAdapterState sailAdapter::checkStatus(void)
{
    int ret;
    (void)sys_lwmutex_lock(&mMutex, /*timeout*/0);
    switch (play_state) {
    case MP_INIT:
        if (mPlayerState==CELL_SAIL_PLAYER_STATE_RUNNING) {
            play_state=MP_RUN;
        }

        break;
    case MP_RUN:
        if (mPlayerState==CELL_SAIL_PLAYER_STATE_OPENED) {
            ret = finalize();
            if (0 > ret) {
                EMSG("finalize()", ret);
            }
            play_state=MP_DONE;
        }
        break;
    case MP_PAUSE:
        break;
    case MP_DONE:
        break;
    default:
        break;
    }
    (void)sys_lwmutex_unlock(&mMutex);
    return play_state;
}

/**E
 * Triggers a sail stop event.
 * 
 * @return true if succeeded.
 */
bool sailAdapter::sendStop(void)
{
    int ret;
    ret = cellSailPlayerStop(&mPlayer, NULL);
    DASSERT (ret>=0);
    if (0 > ret) {
        EMSG("cellSailPlayerStop()", ret);
    }
    return true;
}

void* sailAdapter::onMemAllocStatic(sailAdapter* pSelf,
                                    size_t      boundary,
                                    size_t      size)
{
    return pSelf->onMemAlloc(boundary, size);
}

void sailAdapter::onMemFreeStatic(sailAdapter* pSelf,
                                  size_t      boundary,
                                  void*       pMemory)
{
    return pSelf->onMemFree(boundary, pMemory);
}

void sailAdapter::onPlayerStatic(void* pCbArg,
                                 CellSailEvent event,
                                 uint64_t arg0,
                                 uint64_t arg1)
{
    sailAdapter* pSelf = (sailAdapter*)pCbArg;
    (void)arg1;
    switch (event.u32x2.major) {
    case CELL_SAIL_EVENT_PLAYER_CALL_COMPLETED: {
        int ret;
        CellSailFuture *pFuture;
        pFuture = CAST_UINT64_TO_PTR(CellSailFuture*, arg1);
        if (pFuture) {
            pFuture->userParam = event.u32x2.minor;
            ret = cellSailFutureSet(pFuture, (int)arg0);
            DASSERT (ret>=0);
            if (0 > ret) {
                EMSG("cellSailFutureSet()", ret);
            }
        }
        break;
    case CELL_SAIL_EVENT_PLAYER_STATE_CHANGED: {
        uint32_t  state = (uint32_t)arg0;
        uint32_t* ea    = (uint32_t*)&pSelf->mPlayerState;
        (void)cellAtomicStore32(ea, state);
        break;
    }
    case CELL_SAIL_EVENT_PAUSE_STATE_CHANGED:
        uint32_t paused = (uint32_t)arg0;
        uint32_t* ea    = (uint32_t*)&pSelf->mPlayerPaused;
        (void)cellAtomicStore32(ea, paused);
        break;
    }
    default:
        ;
    }
}


int sailAdapter::onSoundAdapterFormatChangedStatic(sailAdapter*          pArg,
                                                   CellSailAudioFormat* pFormat,
                                                   uint32_t             counter)
{
    (void)pArg;
    (void)counter;
    (void)pFormat;
    //E Irrelevant to the end user only here for those rolling their own player
#if 0
    const char *p;
    switch (pFormat->coding) {
    case CELL_SAIL_AUDIO_CODING_LPCM_FLOAT32:
        p = "CELL_SAIL_AUDIO_CODING_LPCM_FLOAT32";
        break;
    case CELL_SAIL_AUDIO_CODING_UNSPECIFIED:
        p = "CELL_SAIL_AUDIO_CODING_UNSPECIFIED";
        break;
    default:
        p = "unknown";
        break;
    }
    DP("coding = %s (%d)\n", p, pFormat->coding);

    DP("chNum = %d\n", pFormat->chNum);
    DP("sampleNum = %d\n", pFormat->sampleNum);

    switch (pFormat->fs) {
    case CELL_SAIL_AUDIO_FS_8000HZ:
        p = "CELL_SAIL_AUDIO_FS_8000HZ";
        break;
    case CELL_SAIL_AUDIO_FS_11025HZ:
        p = "CELL_SAIL_AUDIO_FS_11025HZ";
        break;
    case CELL_SAIL_AUDIO_FS_12000HZ:
        p = "CELL_SAIL_AUDIO_FS_12000HZ";
        break;
    case CELL_SAIL_AUDIO_FS_16000HZ:
        p = "CELL_SAIL_AUDIO_FS_16000HZ";
        break;
    case CELL_SAIL_AUDIO_FS_22050HZ:
        p = "CELL_SAIL_AUDIO_FS_22050HZ";
        break;
    case CELL_SAIL_AUDIO_FS_24000HZ:
        p = "CELL_SAIL_AUDIO_FS_24000HZ";
        break;
    case CELL_SAIL_AUDIO_FS_32000HZ:
        p = "CELL_SAIL_AUDIO_FS_32000HZ";
        break;
    case CELL_SAIL_AUDIO_FS_44100HZ:
        p = "CELL_SAIL_AUDIO_FS_44100HZ";
        break;
    case CELL_SAIL_AUDIO_FS_48000HZ:
        p = "CELL_SAIL_AUDIO_FS_48000HZ";
        break;
    case CELL_SAIL_AUDIO_FS_64000HZ:
        p = "CELL_SAIL_AUDIO_FS_64000HZ";
        break;
    case CELL_SAIL_AUDIO_FS_88200HZ:
        p = "CELL_SAIL_AUDIO_FS_88200HZ";
        break;
    case CELL_SAIL_AUDIO_FS_96000HZ:
        p = "CELL_SAIL_AUDIO_FS_96000HZ";
        break;
    default:
        p = "unknown";
        break;
    }
    DP("fs = %s (%d)\n", p, pFormat->fs);

    switch (pFormat->chLayout) {
    case CELL_SAIL_AUDIO_CH_LAYOUT_UNDEFINED:
        p = "CELL_SAIL_AUDIO_CH_LAYOUT_UNDEFINED";
        break;
    case CELL_SAIL_AUDIO_CH_LAYOUT_1CH:
        p = "CELL_SAIL_AUDIO_CH_LAYOUT_1CH";
        break;
    case CELL_SAIL_AUDIO_CH_LAYOUT_2CH_LR:
        p = "CELL_SAIL_AUDIO_CH_LAYOUT_2CH_LR";
        break;
    case CELL_SAIL_AUDIO_CH_LAYOUT_6CH_LCRlrE:
        p = "CELL_SAIL_AUDIO_CH_LAYOUT_6CH_LCRlrE";
        break;
    case CELL_SAIL_AUDIO_CH_LAYOUT_6CH_LCRxyE:
        p = "CELL_SAIL_AUDIO_CH_LAYOUT_6CH_LCRxyE";
        break;
    case CELL_SAIL_AUDIO_CH_LAYOUT_8CH_LRCElrxy:
        p = "CELL_SAIL_AUDIO_CH_LAYOUT_8CH_LRCElrxy";
        break;
    default:
        p = "unknown";
        break;
    }
    DP("chLayout = %s (%d)\n", p, pFormat->chLayout);
#endif
    return hlPlayer_OK;
}


int sailAdapter::onGraphicsAdapterFormatChangedStatic(sailAdapter*          pArg,
                                                      CellSailVideoFormat* pFormat,
                                                      uint32_t             counter)
{
    (void)pArg;
    (void)counter;
    (void)pFormat;
    //E Irrelevant to the end user only here for those rolling their own player
#if 0
    static char *p;
    switch (pFormat->coding) {
    case CELL_SAIL_VIDEO_CODING_ARGB_INTERLEAVED:
        p = "CELL_SAIL_VIDEO_CODING_ARGB_INTERLEAVED";
        break;
    case CELL_SAIL_VIDEO_CODING_RGBA_INTERLEAVED:
        p = "CELL_SAIL_VIDEO_CODING_RGBA_INTERLEAVED";
        break;
    case CELL_SAIL_VIDEO_CODING_UYVY422_INTERLEAVED:
        p = "CELL_SAIL_VIDEO_CODING_UYVY422_INTERLEAVED";
        break;
    case CELL_SAIL_VIDEO_CODING_YUV420_PLANAR:
        p = "CELL_SAIL_VIDEO_CODING_YUV420_PLANAR";
        break;
    case CELL_SAIL_VIDEO_CODING_UNSPECIFIED:
        p = "CELL_SAIL_VIDEO_CODING_UNSPECIFIED";
        break;
    default:
        p = "unknown";
        break;
    }
    DP("coding = %s (%d)\n", p, pFormat->coding);

    switch (pFormat->scan) {
    case CELL_SAIL_VIDEO_SCAN_PROGRESSIVE:
        p = "CELL_SAIL_VIDEO_SCAN_PROGRESSIVE";
        break;
    case CELL_SAIL_VIDEO_SCAN_INTERLACE:
        p = "CELL_SAIL_VIDEO_SCAN_INTERLACE";
        break;
    case CELL_SAIL_VIDEO_SCAN_UNSPECIFIED:
        p = "unknown";
        break;
    }
    DP("scan = %s (%d)\n", p, pFormat->scan);

    DP("bitsPerColor = %d\n", pFormat->bitsPerColor);

    switch (pFormat->frameRate) {
    case CELL_SAIL_VIDEO_FRAME_RATE_24000_1001HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_24000_1001HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_24HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_24HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_25HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_25HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_30000_1001HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_30000_1001HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_30HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_30HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_50HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_50HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_60000_1001HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_60000_1001HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_60HZ:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_60HZ";
        break;
    case CELL_SAIL_VIDEO_FRAME_RATE_UNSPECIFIED:
        p = "CELL_SAIL_VIDEO_FRAME_RATE_UNSPECIFIED";
        break;
    default:
        p = "unknown";
        break;
    }
    DP("frameRate = %s (%d)\n", p, pFormat->frameRate);

    DP("width  = %d\n", pFormat->width);
    DP("height = %d\n", pFormat->height);
    DP("pitch  = %d\n", pFormat->pitch);
    DP("alpha  = %d\n", pFormat->alpha);

    switch (pFormat->colorMatrix) {
    case CELL_SAIL_VIDEO_COLOR_MATRIX_BT601:
        p = "CELL_SAIL_VIDEO_COLOR_MATRIX_BT601";
        break;
    case CELL_SAIL_VIDEO_COLOR_MATRIX_BT709:
        p = "CELL_SAIL_VIDEO_COLOR_MATRIX_BT709";
        break;
    case CELL_SAIL_VIDEO_COLOR_MATRIX_UNSPECIFIED:
        p = "CELL_SAIL_VIDEO_COLOR_MATRIX_UNSPECIFIED";
        break;
    default:
        DP("colorMatrix = unknown(%d)\n", pFormat->colorMatrix);
        break;
    }
    DP("colorMatrix = %s (%d)\n", p, pFormat->colorMatrix);

    switch (pFormat->aspectRatio) {
    case CELL_SAIL_VIDEO_ASPECT_RATIO_1_1:
        p = "CELL_SAIL_VIDEO_ASPECT_RATIO_1_1(1920x1080 1280x720)";
        break;
    case CELL_SAIL_VIDEO_ASPECT_RATIO_12_11:
        p = "CELL_SAIL_VIDEO_ASPECT_RATIO_12_11(720x576 normal)";
        break;
    case CELL_SAIL_VIDEO_ASPECT_RATIO_10_11:
        p = "CELL_SAIL_VIDEO_ASPECT_RATIO_10_11(720x480 normal)";
        break;
    case CELL_SAIL_VIDEO_ASPECT_RATIO_16_11:
        p = "CELL_SAIL_VIDEO_ASPECT_RATIO_16_11(720x576 wide)";
        break;
    case CELL_SAIL_VIDEO_ASPECT_RATIO_40_33:
        p = "CELL_SAIL_VIDEO_ASPECT_RATIO_40_33(720x480 wide)";
        break;
    case CELL_SAIL_VIDEO_ASPECT_RATIO_4_3:
        p = "CELL_SAIL_VIDEO_ASPECT_RATIO_4_3(1440x1080)";
        break;
    case CELL_SAIL_VIDEO_ASPECT_RATIO_UNSPECIFIED:
        p = "CELL_SAIL_VIDEO_ASPECT_RATIO_UNSPECIFIED";
        break;
    default:
        p = "unknown";
        break;
    }
    DP("aspectRatio = %s (%d)\n", p, pFormat->aspectRatio);
#endif
    return hlPlayer_OK;
}


int sailAdapter::onGraphicsAdapterAllocFrameStatic(sailAdapter* pSelf,
                                                   size_t      size,
                                                   int         num,
                                                   uint8_t**   ppFrame)
{
    return pSelf->onVideoFrameAlloc(size, num, ppFrame);
}

int sailAdapter::onGraphicsAdapterFreeFrameStatic(sailAdapter* pSelf,
                                                  int         num,
                                                  uint8_t**   ppFrame)
{
    return pSelf->onVideoFrameFree(num, ppFrame);
}

void* sailAdapter::onMemAlloc(size_t boundary, size_t size)
{
    DASSERT(0 != boundary);
    alloccount++;
    alloctotal+=size;
    return mpMemoryAllocator->Allocate(size,boundary);
}

void sailAdapter::onMemFree(size_t  boundary, void *pMemory)
{
    (void)boundary;
    DASSERT(pMemory!=NULL);
    alloccount--;
    alloctotal=0;
    mpMemoryAllocator->Deallocate(pMemory);
}

int sailAdapter::onVideoFrameAlloc(size_t size,int num,uint8_t **ppFrame)
{
    int ret;
#if 1
    //E Reduces the output frame buffer down to 3.
    //  Default is 4 so you get a 25% reduction texture memory  
    num=3;
#endif

    mpReservedAddr=NULL;
    alloctexturetotal=0;
    mReservedSize=0;

    mReservedSize=ROUNDUP(size*num,ALIGN_1MB); 
    alloctexturetotal+=mReservedSize;

    mpReservedAddr = (uint8_t*)mpMemoryAllocator->AllocateTexture(mReservedSize,ALIGN_1MB);
    if (NULL == mpReservedAddr) {
        return -1;
    }

    //E Anything you draw needs to be mapped with GCM
	// FIXME: We aren't using GCM.
    /*const uint32_t align_mask = 0xfffff;
    ret = cellGcmMapMainMemory(mpReservedAddr,
                               (( mReservedSize +align_mask )&( ~align_mask )),
                               &mMainBaseOffset);
    if (0 > ret) {
        PRINTF("Mapping Memory internally used by Sail for output frame buffers failed\n");
    }*/

    uint8_t *p = mpReservedAddr;

    for (int i = 0; i < num; ++i) {
        ppFrame[i]  = p;
        p          += size;
    }

    if (p >= (mpReservedAddr + mReservedSize)) {
        DASSERT_NOT_REACHED();
        return -1;
    }

    return num;
}

int sailAdapter::onVideoFrameFree(int num, uint8_t **ppFrame)
{
    (void)num;
    (void)ppFrame;

	// FIXME: Not using GCM.
    /*int ret;
    ret=cellGcmUnmapIoAddress(mMainBaseOffset);
    if (ret!=0) {
        EMSG("cellGcmUnmapIoAddress()", ret);
    }*/
    mpMemoryAllocator->DeallocateTexture(mpReservedAddr);

    return CELL_OK;
}

} // namespace Sail
} // namespace cell
