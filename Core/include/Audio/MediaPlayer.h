#ifndef _MEDIAPLAYER_H_
#define _MEDIAPLAYER_H_

#include <boost/shared_ptr.hpp>

#include <Audio/AudioEnums.h>

// Forward declarations.
class Song;

class MediaPlayer
{

public:

	static void Initialize();
	static void Shutdown();

	static void Play( const boost::shared_ptr<Song> &song );

	static void Pause();

	static void Resume();

	static void Stop();

	static MediaState GetState();

	static bool IsRepeating;

	static void SetVolume( float volume );

	static float GetVolume();

};

#endif
