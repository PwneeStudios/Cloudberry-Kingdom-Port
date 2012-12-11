#ifndef _MEDIAPLAYER_H_
#define _MEDIAPLAYER_H_

struct MediaPlayer
{



	static void Play( const std::shared_ptr<Song> &song )
	{
	}

	static void Pause()
	{
	}

	static void Resume()
	{
	}

	static void Stop()
	{
	}

	static MediaState GetState()
	{
		return MediaState_Paused;
	}

	static bool IsRepeating;

	static float Volume;

};

#endif
