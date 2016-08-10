#ifndef _SONG_H_
#define _SONG_H_

#include <string>

class Song
{

	struct SongInternal *internal_;

	friend class MediaPlayer;

public:

	struct
	{
		double TotalSeconds;
	} Duration;

	Song();
	~Song();

	void Load( const std::string &path );

};

#endif
