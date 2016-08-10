/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#include <stdlib.h>
#include <string.h>

#include <sys/process.h>
#include <sys/paths.h>
#include <sys/spu_initialize.h>
#include <sys/event.h>
#include <sysutil/sysutil_sysparam.h>
#include <cell/mixer.h>
#include <assert.h>

#include "SailSoundAdapter.h"

#define INVALID_PTS     (0xFFFFFFFFFFFFFFFFULL)

#define CAST_PTR_TO_UINT64(x)     ((uint64_t)(intptr_t)(x))
#define CAST_UINT64_TO_PTR(t, x)  ((t)(intptr_t)(x))

#define ZERO_CLEAR(x, z)          memset(x, 0, z);
//E mixer ppu thread priority
#define MIXER_PPU_THREAD_PRIORITY  (400)

#ifdef _DEBUG
#define PRINTF printf
#else
#define PRINTF(...) 
#endif

#define EMSG(x, ret)     PRINTF("**%s:L%d ERROR! " x " failed. (0x%08X)\n", \
                               __func__, __LINE__, ret)

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

namespace cell {
namespace Sail {

soundAdapter::~soundAdapter (void)
{
    (void)finalize();
}

int
soundAdapter::
initialize(cell::Sail::sailAdapter* mediapass)
{
	msplayer=mediapass;
	int ret;

    // audio
    /*{
        ret = cellAudioOutGetNumberOfDevice(CELL_AUDIO_OUT_PRIMARY);
        if (0 > ret) {
            EMSG("cellAudioOutGetNumberOfDevice()", ret);
            return ret;
        }*/

        /*E
         * NOTE: ONLY LPCM OUTPUT IS USED to guarantee A/V sync. ac3 & dts
         * can not guarantee the same latency on different hardware
         * configurations so we do not use them in this library. 
         * 
         * 100% of receivers will support LPCM output so this is a safe choice.
         */
    /*    CellAudioOutConfiguration audioConfig;
        //E Must clear this value
		ZERO_CLEAR(&audioConfig, sizeof(audioConfig));

		audioConfig.channel = cellAudioOutGetSoundAvailability(
            CELL_AUDIO_OUT_PRIMARY,
            CELL_AUDIO_OUT_CODING_TYPE_LPCM,
            CELL_AUDIO_OUT_FS_48KHZ,*/
    //        0 /* option: must be 0 */);

	/*	if (audioConfig.channel==2) {
			audioConfig.downMixer=CELL_AUDIO_OUT_DOWNMIXER_TYPE_A;
		} else if (audioConfig.channel>6) {
            audioConfig.downMixer=CELL_AUDIO_OUT_DOWNMIXER_TYPE_B;
            audioConfig.channel=6;
        } else {
            audioConfig.downMixer=CELL_AUDIO_OUT_DOWNMIXER_NONE;
        }

        ret = cellAudioOutConfigure(CELL_AUDIO_OUT_PRIMARY,
                                    &audioConfig,
                                    NULL,
                                    0);
        if (0 > ret) {
            EMSG("cellAudioOutConfigure()", ret);
            return ret;
        }

        ret = cellAudioInit();
        if (0 > ret) {
            EMSG("cellAudioInit()", ret);
            return ret;
        }
    }*/

	CellAudioPortParam audioParam;
    ZERO_CLEAR(&audioParam, sizeof(audioParam));
    //audioParam.nChannel = CELL_AUDIO_PORT_2CH;
    audioParam.nChannel = CELL_AUDIO_PORT_8CH;
    audioParam.nBlock   = CELL_AUDIO_BLOCK_8;
    //audioParam.nBlock   = CELL_AUDIO_BLOCK_16;
    ret = cellAudioPortOpen(&audioParam, &mAudioPortNum);
    if (0 > ret) {
        EMSG("cellAudioPortOpen()", ret);
        return ret;
    }
	
    /* get port config. */
    ZERO_CLEAR(&mAudioPortConfig, sizeof(mAudioPortConfig));
    ret = cellAudioGetPortConfig(mAudioPortNum, &mAudioPortConfig);
    if (0 > ret) {
        EMSG("cellAudioGetPortConfig()", ret);
        return ret;
    }
	
    ret = cellAudioCreateNotifyEventQueue(&mAudioEventQueue,
                                          &mAudioEventQueueKey);
    if (0 > ret) {
        EMSG("cellAudioCreateNotifyEventQueue()", ret);
        return ret;
    }

    /* register event queue to libaudio */
    ret = cellAudioSetNotifyEventQueue(mAudioEventQueueKey);
    if (0 > ret) {
        EMSG("cellAudioSetNotifyEventQueue()", ret);
        return ret;
    }

    /* sound thread create */
    mAudioThreadRunning = 1;
    ret = sys_ppu_thread_create(&mAudioThreadId,
                                audioDispatchThreadFunc,
                                CAST_PTR_TO_UINT64(this),
                                /*priority*/   100,
                                /*stack size*/ 4096,
                                SYS_PPU_THREAD_CREATE_JOINABLE,
                                "audio-dispatch");
    if (0 > ret) {
        EMSG("sys_ppu_thread_create()", ret);
        return ret;
    }
    return 0;
}

int
soundAdapter::
finalize(void)
{
	int ret;
    if (0 == mAudioThreadRunning) {
        return 0;
    }
    mAudioThreadRunning = 0;
	uint64_t exitStatus;
	sys_ppu_thread_join(mAudioThreadId, &exitStatus);

    ret = cellAudioRemoveNotifyEventQueue(mAudioEventQueueKey);
    if (0 > ret) {
        EMSG("cellAudioRemoveNotifyEventQueue()", ret);
    }

	ret = cellAudioPortClose(mAudioPortNum);
    if (0 > ret) {
        EMSG("cellAudioPortClose()", ret);
    }

	ret = sys_event_queue_destroy(mAudioEventQueue,
                                  SYS_EVENT_QUEUE_DESTROY_FORCE);
    if (0 > ret) {
        EMSG("sys_event_queue_destroy()", ret);
    }

	/*ret = cellAudioQuit();
    if (0 > ret) {
        EMSG("cellAudioQuit()", ret);
    }*/
    return 0;
}

void
soundAdapter::
audioDispatchThreadFunc(uint64_t arg)
{
    soundAdapter *pSelf;
    pSelf = CAST_UINT64_TO_PTR(soundAdapter *, arg);

	/* start port */
    int ret;
	ret = cellAudioPortStart(pSelf->mAudioPortNum);
    if (0 > ret) {
        EMSG("cellAudioPortStart()\n", ret);
        sys_ppu_thread_exit(ret);
    }

    while (pSelf->mAudioThreadRunning) {
		sys_event_t  event;
		ret = sys_event_queue_receive(pSelf->mAudioEventQueue,
                                      &event,
                                      10 * 1000); // 10msec > 5.3msec
		if (ETIMEDOUT == ret){
            continue;
		}

        (void)pSelf->onAudioNotified();
    }

	ret = cellAudioPortStop(pSelf->mAudioPortNum);
    if (0 > ret) {
        EMSG("cellAudioPortStop()", ret);
    }
    sys_ppu_thread_exit(CELL_OK);
}

int
soundAdapter::
onAudioNotified(void)
{

	if (msplayer->checkStatus()!=cell::Sail::sailAdapter::MP_RUN) {
        return CELL_OK;
    }

    static const int samples = 256;

    int ret;
    CellSailSoundFrameInfo info;
    ret = msplayer->getAudioFrame(samples, &info);

    if (CELL_SAIL_SYNC_IS_FRAME_AVAILABLE(ret)) {
        DASSERT(info.pBuffer);
        if (info.sessionId != mAudioSessionId) {
            ret = msplayer->getAudioFormat(&mAudioFormat);
			if (0 <= ret) {
                mAudioSessionId = info.sessionId;
            }
        }

        uint64_t time = 0;
        ret = msplayer->audioPtsToTimePosition(info.pts, &time);
		if (0 > ret) {
            mAudioTime = INVALID_PTS;
        } else {
            mAudioTime = time;
        }

        if (CELL_SAIL_AUDIO_FS_48000HZ == mAudioFormat.fs) {
            uint32_t chNum = mAudioFormat.chNum;
            float volume = msplayer->mStreamVolume;
            if (1 == chNum) {
                ;
            } else if (2 == chNum) {
                ret = cellAudioAdd2chData(mAudioPortNum,
                                          (float*)info.pBuffer,
                                          samples,
                                          /*volume*/ volume);
                if (0 > ret) {
                    EMSG("cellAudioAdd2chData()", ret);
                }
            } else if (6 == chNum) {
                ret = cellAudioAdd6chData(mAudioPortNum,
                                          (float*)info.pBuffer,
                                          /*volume*/ volume);
                if (0 > ret) {
                    EMSG("cellAudioAdd6chData()", ret);
                }
            } else {
                ret = cellAudioAddData(mAudioPortNum,
                                       (float*)info.pBuffer,
                                       samples,
                                       /*volume*/ volume);
                if (0 > ret) {
                    EMSG("AudioAddData()", ret);
                }
            }
        }
    }

    uint32_t sailTag = info.tag;
    {
        sys_addr_t audioPortIndexAddr = mAudioPortConfig.readIndexAddr;
        uint64_t  *audioPortIndexP    = (uint64_t*)audioPortIndexAddr;
        uint64_t idx = *audioPortIndexP;

        uint64_t mixerTag;
        ret = cellAudioGetPortBlockTag(mAudioPortNum, idx, &mixerTag);
        if (0 > ret) {
            EMSG("cellAudioGetPortBlockTag()", ret);
        } else {
            int i = 0;
            for (; i < AUDIO_TAG_NUMBER; ++i) {
                if (! maUsed[i]) {
                    goto label_found;
                }
            }
            i = mixerTag % AUDIO_TAG_NUMBER; // as random value
        label_found:
            maUsed[i]     = true;
            maMixerTag[i] = mixerTag;
            maSyncTag[i]  = sailTag;
        }
    }

    {
        uint32_t prevSailTag = sailTag - AUDIO_TAG_FEEDBACK_DELAY;
        for (int i = 0; i < AUDIO_TAG_NUMBER; ++i) {
            if (maUsed[i] && 
                maSyncTag[i] == prevSailTag) {
                uint64_t prevMixerTag;
                prevMixerTag = maMixerTag[i];
                maUsed[i]    = false;
                usecond_t timeStamp;
                ret = cellAudioGetPortTimestamp(mAudioPortNum,
                                                prevMixerTag,
                                                &timeStamp);
                if (0 > ret) {
                    // EMSG(cellAudioGetPortTimestamp()", ret);
                } else {
					msplayer->updateAudioSync(prevSailTag, timeStamp);
                }
                return CELL_OK;
            }
        }
    }
    return CELL_OK;
}

} // namespace Sail
} // namespace cell
