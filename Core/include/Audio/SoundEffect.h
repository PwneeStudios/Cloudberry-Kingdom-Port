#ifndef _SOUNDEFFECT_H_
#define _SOUNDEFFECT_H_

#include <string>

/**
 * A sound effect.
 */
class SoundEffect
{
	
	struct SoundEffectInternal *internal_;

public:
	
	SoundEffect();
	~SoundEffect();

	/// Load a WAV sound from disk.
	/**
	 * @param path Path to file.
	 */
	void Load( const std::string &path );

	/// Play the sound effect.
	/**
	 * @param volume Sound volume in range [0,1].
	 * @param pitch Pitch adjustment in the range [-1,1]. (One octave down to one octave up.)
	 * @param pan Sound panning in the range [-1,1]. (Left to right.)
	 */
	void Play( float volume, float pitch, float pan );

};

#endif
