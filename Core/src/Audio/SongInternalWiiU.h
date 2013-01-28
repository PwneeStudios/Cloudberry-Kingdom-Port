#ifndef _SONG_INTERNAL_WIIU_
#define _SONG_INTERNAL_WIIU_

#include <fmod.hpp>

extern FMOD::System *FMODSystem;

struct SongInternal
{
	FMOD::Sound *Song;
};

#endif
