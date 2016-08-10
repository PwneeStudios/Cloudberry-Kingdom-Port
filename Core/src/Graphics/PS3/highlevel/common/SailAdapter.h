/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#ifndef __MEDIA_PLAYER_API_H__
#define __MEDIA_PLAYER_API_H__

#include <cell/spurs.h>
#include <cell/cell_fs.h>
#include <cell/sail.h>

#include "SailAllocator.h"

namespace cell {
namespace Sail {

class sailAdapter {
private:
    char mUri[CELL_SAIL_MAX_LENGTH_PROTOCOL_NAME_WITH_NULL_TERMINATE +
              CELL_FS_MAX_FS_FILE_NAME_LENGTH +
              CELL_FS_MAX_MP_LENGTH + 1];

    CellSailPlayer          mPlayer;
    CellSailFuture          mFuture;
    CellSailSoundAdapter    mSoundAdapter;
    CellSailGraphicsAdapter mGraphicsAdapter;
    CellSailDescriptor*     mpDescriptor;
    CellSailFsRead*         mpChangeRead;

    volatile int            mPlayerState;
    volatile int            mPlayerPaused;

public:	
    union {
        CellPamfReader   pamfReader;
        CellSailMp4Movie mp4Movie;
        CellSailAviMovie aviMovie;
    } mDatabase;
    int  mStreamType;
	uint32_t  mTimeScale;
	uint32_t  mTimeRate;
    uint64_t  mCurrentTime;
	uint64_t  mBeginOffset;
    uint64_t  mEndOffset;
    uint64_t  mMovieDurationMsec;
	enum {
		hlPlayer_OK      = CELL_OK,
		hlPlayer_WAITING = 999,
		hlPlayer_FAILURE = -1,
	};

	enum sailAdapterState {
		MP_INIT      = 0,
		MP_RUN       = 1<<1 | 1,
		MP_PAUSE     = 2<<1 | 1,
		MP_DONE      = 3<<1,
	} ;

	sailAdapterState play_state;

    fsallocator*  mpFileAllocator;
    memallocator* mpMemoryAllocator;

    int alloccount;
    int alloctotal;
    int alloctexturetotal;

    uint8_t *mpReservedAddr;
    uint32_t mMainBaseOffset;
    size_t   mReservedSize;

    float mStreamVolume;

    sys_lwmutex_t mMutex;

    CellSpurs* mpInternalSpurs;
    CellSpurs* mpActiveSpurs;

public:
    sailAdapter(fsallocator*,memallocator*);
	~sailAdapter(void);

public:
    bool startup(CellSpurs* pSpurs);
    bool initialize(int videoFormat, int releaseDelay, int width, int height);
    bool finalize(void);
	bool shutdown(void);
    bool openStream(char const* pPath);
    bool start(CellSailStartCommand *pCommand,bool looping);
    bool sendStop(void);
    bool togglePause(void);

	bool TrickStart(bool direction, float trickSpeed);
	bool TrickFastPlayback(int trickSpeed);
	bool TrickResumePlayback();

	bool JumpToLocation(uint64_t jumptime);

	bool PopulateStreamInfo();

    bool SetVolume(float);
	uint64_t GetStartTime(); 
	uint64_t GetEndTime(); 
	uint64_t GetCurrentTime(); 
	bool GetCurrentTime(uint64_t* CurrentTime);

	sailAdapterState checkStatus(void);

    int getAudioFrame(int samples, CellSailSoundFrameInfo* pInfo) {
        return cellSailSoundAdapterGetFrame(&mSoundAdapter, samples, pInfo);
    }
    int getVideoFrame(CellSailGraphicsFrameInfo *pInfo);

    int getAudioFormat(CellSailAudioFormat *pFormat) {
        return cellSailSoundAdapterGetFormat(&mSoundAdapter,
                                             pFormat);
    }
    int getVideoFormat(CellSailVideoFormat *pFormat) {
        return cellSailGraphicsAdapterGetFormat(&mGraphicsAdapter,
                                                pFormat);
    }

    int audioPtsToTimePosition(uint64_t pts, uint64_t* pTime) {
        return cellSailSoundAdapterPtsToTimePosition(&mSoundAdapter,
                                                     pts,
                                                     pTime);
    }
    int videoPtsToTimePosition(uint64_t pts, uint64_t* pTime) {
        return cellSailGraphicsAdapterPtsToTimePosition(&mGraphicsAdapter,
                                                        pts,
                                                        pTime);
    }

    void updateAudioSync(uint32_t tag,
                         uint64_t timeStamp) {
        cellSailSoundAdapterUpdateAvSync(&mSoundAdapter,
                                         tag,
                                         timeStamp);
    }

    void updateVideoSync(uint32_t tag,
                         uint64_t timeStamp) {
        cellSailGraphicsAdapterUpdateAvSync(&mGraphicsAdapter,
                                            tag,
                                            timeStamp);
    }

	
protected:
    void* onMemAlloc(size_t boudnary,
                     size_t size);
    void onMemFree(size_t boudnary,
                   void*  pMemory);
    int onVideoFrameAlloc(size_t    size,
                          int       num,
                          uint8_t** ppFrame);
    int onVideoFrameFree(int       num,
                         uint8_t** ppFrame);

private:
    int waitResponse(void);
      
    static void* onMemAllocStatic(sailAdapter* pSelf,
                                  size_t      boundary,
                                  size_t      size);
    static void onMemFreeStatic(sailAdapter* pSelf,
                                size_t      boundary,
                                void*       pMemory);
    static void onPlayerStatic(void*         pCbArg,
                               CellSailEvent event,
                               uint64_t      arg0,
                               uint64_t      arg1);

    static int onSoundAdapterFormatChangedStatic(
        sailAdapter*          pArg,
        CellSailAudioFormat* pFormat,
        uint32_t             counter);


    static int onGraphicsAdapterFormatChangedStatic(
        sailAdapter*          pArg,
        CellSailVideoFormat* pFormat,
        uint32_t             counter);

    static int onGraphicsAdapterAllocFrameStatic(
        sailAdapter* pArg,
        size_t      size,
        int         num,
        uint8_t**   ppFrame);
    static int onGraphicsAdapterFreeFrameStatic(
        sailAdapter* pArg,
        int         num,
        uint8_t**  ppFrame);
};

} // namespace Sail
} // namespace cell

#endif /* __MEDIA_PLAYER_API_H__ */
