/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 * Copyright (C) 2010 Sony Computer Entertainment Inc.
 * All Rights Reserved.
 */

#ifndef __SAILSOUNDADAPTER_H__
#define __SAILSOUNDADAPTER_H__

#include "SailAdapter.h"
#include <cell/audio.h>

//E bigger than 4
//E please refer libaudio/libmixer document.
#define AUDIO_TAG_FEEDBACK_DELAY  (5)
//E bigger than AUDIO_TAG_FEEDBACK_DELAY
#define AUDIO_TAG_NUMBER  (7)

namespace cell {
namespace Sail {

class soundAdapter 
{
public:
	soundAdapter(void) { }
	virtual ~soundAdapter(void);

private:
    int initialize(cell::Sail::sailAdapter* mediapass);
    int finalize(void);
	static void audioDispatchThreadFunc(uint64_t arg);
	int onAudioNotified(void);

private:
	uint32_t            mAudioPortNum;
	CellAudioPortConfig	mAudioPortConfig;
	sys_event_queue_t   mAudioEventQueue;
	uint64_t			mAudioEventQueueKey;
	sys_ppu_thread_t	mAudioThreadId;
	volatile unsigned   mAudioThreadRunning;

    //E Media Player Object which is used to retrieve additional audio
    //  data from
	cell::Sail::sailAdapter* msplayer;

    uint64_t mAudioTime;
    uint32_t mAudioSessionId;
    CellSailAudioFormat mAudioFormat;

    bool     maUsed[AUDIO_TAG_NUMBER];
    uint64_t maMixerTag[AUDIO_TAG_NUMBER];
    uint32_t maSyncTag[AUDIO_TAG_NUMBER];

    friend class hlPlayer;
};

} // namespace Sail
} // namespace cell

#endif
