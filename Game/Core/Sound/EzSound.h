#ifndef EZSOUND
#define EZSOUND

#include <global_header.h>

#include "Hacks/XNA/SoundEffect.h"

namespace CloudberryKingdom
{
	class EzSound
	{
	public:
		std::shared_ptr<SoundEffect> sound;
		std::wstring Name;
		int MaxInstances;
		float DefaultVolume;
		int DelayTillNextSoundCanPlay;
	private:
		int LastPlayedStamp;

	public:
		EzSound();

		void Play();

		/// <summary>
		/// Plays the sound with a random modulation to the pitch.
		/// </summary>
		/// <param name="PitchModulationRange"></param>
		void PlayModulated( float PitchModulationRange );

		void Play( float volume );

		void Play( float volume, float pitch, float pan );
	};
}


#endif	//#ifndef EZSOUND
