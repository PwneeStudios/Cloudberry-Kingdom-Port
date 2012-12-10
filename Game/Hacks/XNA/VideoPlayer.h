#ifndef _VIDEOPLAYER_H_
#define _VIDEOPLAYER_H_

struct VideoPlayer
{



	bool IsLooped;

	VideoPlayer() : IsLooped( false ) { }

	void Play( const std::shared_ptr<Video> &video )
	{
	}

	std::shared_ptr<Texture2D> GetTexture()
	{
		return std::shared_ptr<Texture2D>();
	}

};

#endif
