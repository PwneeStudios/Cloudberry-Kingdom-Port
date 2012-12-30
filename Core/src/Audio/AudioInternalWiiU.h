#ifndef _AUDIO_INTERNAL_WIIU_H_
#define _AUDIO_INTERNAL_WIIU_H_

#include <cafe/ax.h>
#include <cafe/sp.h>

struct Voice
{
    AXVPB *AXVoice;
    SPSoundEntry *SPEntry;

	AXPBVE Ve;
};

extern Voice Voices[ AX_MAX_VOICES ];
extern SPSoundTable *SPTable;
extern AXPBCHMIX MixChannels[ AX_MAX_NUM_TV_CHS ];

extern void VoiceDropCallback( void *p );

#endif
