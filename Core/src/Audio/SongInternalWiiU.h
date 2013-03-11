#ifndef _SONG_INTERNAL_WIIU_
#define _SONG_INTERNAL_WIIU_

#include <fmod.h>

//extern FMOD::System *FMODSystem;
extern FMOD_SYSTEM *FMODSystem;

struct SongInternal
{
	//FMOD::Sound *Song;
	FMOD_SOUND *Song;
};

#endif
