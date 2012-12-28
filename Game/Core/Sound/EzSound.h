#ifndef EZSOUND
#define EZSOUND

#include <global_header.h>

#include <Audio/SoundEffect.h>

namespace CloudberryKingdom
{
	struct EzSound
	{
	
		boost::shared_ptr<SoundEffect> sound;
		std::wstring Name;
		int MaxInstances;
		float DefaultVolume;
		int DelayTillNextSoundCanPlay;
	
		int LastPlayedStamp;

	
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
