/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <new>

#include <sys/types.h>
#include <sys/prx.h>
#include <sys/timer.h>
#include <sys/ppu_thread.h>
#include <sys/event.h>
#include <sys/spu_initialize.h>

#include <cell/atomic.h>
#include <cell/sysmodule.h>
#include <cell/cell_fs.h>
//#include <cell/gcm.h>
#include <PSGL/psgl.h>

#include "libhlPlayer.h"
#include "SailAdapter.h"
#include "SailSoundAdapter.h"

#ifdef _DEBUG
	#define PRINTF printf
#else
	#define PRINTF(...) 
#endif

namespace cell {
namespace Sail {


static memallocator sDefaultAllocator;
hlPlayer::hlPlayer(VideoPlayerInit* pPlayerInit,CustomAllocators* custAlloc):
    mCurrentPlaybackTime(0),
    mAccess(0),
    mEnabled(0)
{
    memallocator *pAllocator = (custAlloc && custAlloc->MemoryReplacement) ?
                               custAlloc->MemoryReplacement :
                               &sDefaultAllocator;
    fsallocator* pFs = (custAlloc && custAlloc->FileReplacement) ?
                       custAlloc->FileReplacement :
                       NULL;

    /* Create the mixer and save the init params */
    void *p = pAllocator->Allocate(sizeof(sailAdapter), 8);
    if (NULL == p) {
        return;
    }
    pPlayerCore = new(p) sailAdapter(pFs, pAllocator);

    p = pAllocator->Allocate(sizeof(soundAdapter), 128);
    if (NULL == p) {
        return;
    }
	AudioOut = new(p) soundAdapter();
	int ret;
    ret = AudioOut->initialize(pPlayerCore);
    if (0 > ret) {
        return;
    }

	pinitParams = pPlayerInit;
	pPlayerCore->startup(pinitParams->pSharedSpurs);

    mEnabled = 1;
}

hlPlayer::~hlPlayer(void)
{
    if (mEnabled) {
        mEnabled = 0;
        // **NOTE**
        // you have to ensure that rendering threads of both audio/video
        // are not running in libsail before finalizing.
        while (mAccess) {
            sys_timer_usleep(100);
        }
    }

    if (pPlayerCore && pPlayerCore->mpMemoryAllocator) {
        memallocator *pAllocator = pPlayerCore->mpMemoryAllocator;
        if (AudioOut) {
            AudioOut->~soundAdapter();
            pAllocator->Deallocate(AudioOut);
            AudioOut = 0;
        }

        if (pPlayerCore) {
            pPlayerCore->~sailAdapter();
            pAllocator->Deallocate(pPlayerCore);
            pPlayerCore = 0;
        }
    }
}

bool hlPlayer::isPlaying()
{
	cell::Sail::sailAdapter::sailAdapterState currentStatus;
	currentStatus=pPlayerCore->checkStatus();

	if (((currentStatus & 1)==0)&&(pPlayerCore->alloccount==0))
	{ 
		return false;
	}
    return true;
}

bool hlPlayer::Play(char* videouri, bool looping)
{
    int ret;
	bool bRet;
	int VideoOutputFormat;

    if (pPlayerCore->checkStatus()==cell::Sail::sailAdapter::MP_RUN) {
		Stop();
    }
    
	/* Detect the stream type simply by looking at the extension */
	const char *tmpext = strrchr( videouri, '.' );
	if(strncasecmp (tmpext+1,"MP4",3)==0) {
        ;
	} else if(strncasecmp (tmpext+1,"PAM",3)==0){
        ;
	} else if(strncasecmp (tmpext+1,"AVI",3)==0){
        ;
	} else {
		return false;
    }

    if (pinitParams->RGBAOutput) {
		VideoOutputFormat=CELL_SAIL_VIDEO_CODING_RGBA_INTERLEAVED;
	} else {
		VideoOutputFormat=CELL_SAIL_VIDEO_CODING_YUV420_PLANAR;
    }
		
    bRet = pPlayerCore->initialize(
        VideoOutputFormat,
        2, // Fixed to double buffer output
		pinitParams->width,
        pinitParams->height);
        if (!bRet) {
	        PRINTF("pPlayerCore->initialize()");
    	    return false;
    }

    if (!pPlayerCore->openStream((const char*)videouri)) {
        PRINTF("pPlayerCore->openStream()");
		Stop();
        return false;
    }		

	ret = pPlayerCore->PopulateStreamInfo();
	if (0>ret)
	{
		PRINTF("pPlayerCore->PopulateStreamInfo() Failed\n");
	}

	ret = pPlayerCore->start(/*startCommand*/ 0,looping);

    if ((!ret) || (pPlayerCore->checkStatus()!=cell::Sail::sailAdapter::MP_RUN)){
        ret=pPlayerCore->sendStop();
		if (0>ret)
		{
			PRINTF("pPlayerCore->sendStop() failed\n");
		}
        return false;
    }
	return true;
}

bool hlPlayer::Stop(void)
{
	int ret;
	bool retval=true;


	if (pPlayerCore->checkStatus()==cell::Sail::sailAdapter::MP_RUN) 
	{
        ret=pPlayerCore->sendStop();
		if (0>ret)
		{
			PRINTF("sendStop() failed, shutdown will probably hang at this point\n");
			retval=false;
		}
	}
	return retval;
}

bool hlPlayer::Pause(void)
{
	if (pPlayerCore->checkStatus()==cell::Sail::sailAdapter::MP_RUN) {
		if(pPlayerCore->togglePause()==CELL_OK) {
			return true;
        }
    }
	return false;
}

bool hlPlayer::Resume(void)
{
	if (pPlayerCore->checkStatus()==cell::Sail::sailAdapter::MP_PAUSE) {
		if(pPlayerCore->togglePause()==CELL_OK) {
			return true;
        }
    }
	return false;
}

bool hlPlayer::Memstats(int* decodermem, int* texturemem)
{
	*decodermem=pPlayerCore->alloctotal;
	*texturemem=pPlayerCore->alloctexturetotal;
	return true;
}

bool hlPlayer::Volume(float changeVolume)
{
	return pPlayerCore->SetVolume(changeVolume);
}

bool hlPlayer::vsyncGetFrame(VideoFrameInfo* frameInfo)
{
    /*E
     * True is returned when a new frame is ready. These frames are
     * timed with the audio which is automatically playing behind
     * the scenes so it is best to display this frame asap. 
     * The resolution and colorspace are also supplied with every frame
     * so that the drawing thread logic can be simplified.
     */
	CellSailVideoFormat mVideoFormat;
	int ret;
    bool retval = false;    
    (void)cellAtomicOr32((uint32_t*)&mAccess, 2U);
   if (mEnabled && pPlayerCore->checkStatus()==cell::Sail::sailAdapter::MP_RUN) {
		CellSailGraphicsFrameInfo info;
	    ret = pPlayerCore->getVideoFrame(&info);

	    if (CELL_SAIL_SYNC_IS_FRAME_AVAILABLE(ret)) {  
			frameInfo->buffer=info.pBuffer;
	     	retval=true;
            pPlayerCore->getVideoFormat(&mVideoFormat);
			frameInfo->width=mVideoFormat.width;
			frameInfo->height=mVideoFormat.height;
			switch (mVideoFormat.coding) {
			case CELL_SAIL_VIDEO_CODING_RGBA_INTERLEAVED:
				frameInfo->RGBAFrameHint=true;
				break;
			case CELL_SAIL_VIDEO_CODING_YUV420_PLANAR:
				frameInfo->RGBAFrameHint=false;
				break;
			default:
				retval=false;
				PRINTF("vsyncGetFrame - only RGBA and YUV 420 output modes are implemented in hlPlayer, Frame ignored.\n");
				break;
			};
	    }
	    uint64_t fliptime = psglGetLastFlipTime();//cellGcmGetLastFlipTime();
		pPlayerCore->updateVideoSync(info.tag, fliptime);
    }
   (void)cellAtomicAnd32((uint32_t*)&mAccess, ~2U);
    return retval;
}

uint64_t hlPlayer::CurrentTime()
{
	if (pPlayerCore->GetCurrentTime(&mCurrentPlaybackTime)) {
		return mCurrentPlaybackTime;
	}
    return 0;
}

uint64_t hlPlayer::StartTime()
{
	return pPlayerCore->GetStartTime();
}

uint64_t hlPlayer::EndTime()
{
	return pPlayerCore->GetEndTime();
}

bool hlPlayer::JumpTimeOffset(uint64_t jumpoffset)
{
	return pPlayerCore->JumpToLocation(jumpoffset);
}

bool hlPlayer::TrickFastPlay(int playspeed)
{
	if ((playspeed>4)||(playspeed<=1)) {
		return false;
    }
	return pPlayerCore->TrickFastPlayback(playspeed);
}

bool hlPlayer::TrickFastForward(int trickspeed)
{
	if ((trickspeed>5)||(trickspeed<1)) {
		return false;
    }
	return pPlayerCore->TrickStart(true,float(trickspeed*10.0f));
}

bool hlPlayer::TrickFastRewind(int trickspeed)
{
	if ((trickspeed>5)||(trickspeed<1)) {
		return false;
    }
	return pPlayerCore->TrickStart(false,float(trickspeed*10.0f));
}

bool hlPlayer::TrickResumePlay()
{
	return pPlayerCore->TrickResumePlayback();
}

} // namespace Sail
} // namespace cell

// -- c=>c++ functions


class AllocatorProxy : public cell::Sail::memallocator {
private:
    hlMemAllocator mAllocator;
public:
    AllocatorProxy(const hlMemAllocator &allcator) :
        mAllocator(allcator) { }
    virtual ~AllocatorProxy(void) {}
public:
	virtual void* Allocate(uint32_t size, uint32_t alignment) {
        return mAllocator.allocate(mAllocator.pArg,
                                   size,
                                   alignment);
	};

	virtual void Deallocate(void* pMemory) {
		mAllocator.deallocate(mAllocator.pArg, pMemory);
	};

	virtual void* AllocateTexture(uint32_t size, uint32_t alignment) {
        return mAllocator.allocateTexture(mAllocator.pArg, size, alignment);
	};

	virtual void DeallocateTexture(void* pMemory) {
		mAllocator.deallocateTexture(mAllocator.pArg, pMemory);
	};
};


hlPlayerHandle_t hlPlayerInit(VideoPlayerInit* initparams,
                              hlMemAllocator*  allocator)
{
    CustomAllocators         *pCustom = NULL;
    cell::Sail::memallocator *pAllocator;
    AllocatorProxy           *pProxy = NULL;
    if (allocator) {
        if (NULL == allocator->allocate ||
            NULL == allocator->deallocate) {
            return 0;
        }
        void* p;
        p = allocator->allocate(allocator->pArg,
                                /*boundary*/8,
                                sizeof(AllocatorProxy));
        if (NULL == p) {
            return 0;
        }
        pProxy = new (p) AllocatorProxy(*allocator);
        CustomAllocators tmp = {/*FileReplacement*/ NULL,
                                /*MemoryReplacement*/ pProxy };
        pCustom = &tmp;
        pAllocator = pProxy;
    } else {
        pAllocator = &cell::Sail::sDefaultAllocator;
    }

    void *p; 
    p = pAllocator->Allocate(sizeof(cell::Sail::hlPlayer),
                             /*alignment*/ 8);
    if (NULL == p) {
        if (pProxy) {
            pAllocator->Deallocate(pProxy);
        }
        return 0;
    }
	cell::Sail::hlPlayer* TestPlayerC =
        new (p) cell::Sail::hlPlayer(initparams, pCustom);
    TestPlayerC->mpUserdata = pProxy;
	return (hlPlayerHandle_t)TestPlayerC;
}

bool hlPlayerPlay(hlPlayerHandle_t avHandle, char* videouri, bool looping)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->Play(videouri,looping);
}

bool hlPlayerPause(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->Pause();
}

bool hlPlayerResume(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->Resume();
}

bool hlPlayerStop(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->Stop();
}

bool hlPlayerClose(hlPlayerHandle_t avHandle)
{
    cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;

    AllocatorProxy *pProxy = (AllocatorProxy*)avh->mpUserdata;
    cell::Sail::memallocator* pMemoryAllocator =
        avh->pPlayerCore->mpMemoryAllocator;

    avh->~hlPlayer();
    pMemoryAllocator->Deallocate(avh);

    if (pProxy) {
        pProxy->~AllocatorProxy();
        pMemoryAllocator->Deallocate(pProxy);
    }
	return true;
}

bool hlPlayerisPlaying(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->isPlaying();
}

bool hlPlayerGetFrame(hlPlayerHandle_t avHandle, VideoFrameInfo *getFrame)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->vsyncGetFrame(getFrame);
}

bool hlPlayerMemstats(hlPlayerHandle_t avHandle, int* decoder, int* texture)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->Memstats(decoder,texture);
}

bool hlPlayerVolume(hlPlayerHandle_t avHandle, float changeVolume)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->Volume(changeVolume);
}

uint64_t hlPlayerCurrentTime(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->CurrentTime();
}
	
uint64_t hlPlayerStartTime(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->StartTime();
}

uint64_t hlPlayerEndTime(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->EndTime();
}
/*
bool hlPlayerJumpTimeOffset(hlPlayerHandle_t avHandle,uint64_t jumpoffset)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->JumpTimeOffset(jumpoffset);
}
*/
bool hlPlayerTrickFastPlay(hlPlayerHandle_t avHandle,int playspeed)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->TrickFastPlay(playspeed);
}

bool hlPlayerTrickFastForward(hlPlayerHandle_t avHandle,int trickspeed)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->TrickFastForward(trickspeed);
}

bool hlPlayerTrickFastRewind(hlPlayerHandle_t avHandle,int trickspeed)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->TrickFastRewind(trickspeed);
}

bool hlPlayerTrickResumePlay(hlPlayerHandle_t avHandle)
{
	cell::Sail::hlPlayer* avh = (cell::Sail::hlPlayer*) avHandle;
	return avh->TrickResumePlay();
}
