/**
 * @file
 *
 * Sound resource.
 */
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Resource.h"

/**
 * A sound resource.
 */
class Sound : public Resource
{


private:

	/// No copying.
	Sound( const Sound & ) { }

	/// No assignment.
	Sound &operator = ( const Sound & ) { return *this; }

public:

	Sound() { }
	~Sound() { }

	/**
	 * @see Resource::Load()
	 */
	void Load();

	/**
	 * @see Resource::Unload()
	 */
	void Unload();

};

#endif
