#ifndef _VIDEOPLAYER_H_
#define _VIDEOPLAYER_H_

#include <boost/shared_ptr.hpp>

// Forward declarations.
class Texture2D;
class Video;
struct VideoPlayerInternal;

struct VideoPlayer
{

	VideoPlayerInternal *internal_;

public:

	bool IsLooped;

#ifdef CAFE
	VideoPlayer( void (*UpdateElapsedTime)(bool) );
#else
	VideoPlayer();
#endif
	~VideoPlayer();

	void SetVolume( float volume );

	void Play( const boost::shared_ptr< Video > &video );

	void DrawFrame();

	boost::shared_ptr< Texture2D > GetTexture();

};

#endif
