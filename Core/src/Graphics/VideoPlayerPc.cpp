#include <Graphics/VideoPlayer.h>

#include <Core.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Graphics/Video.h>
#include <Graphics/Texture2D.h>


struct VideoPlayerInternal
{
};

VideoPlayer::VideoPlayer()
	: internal_( new VideoPlayerInternal )
	, IsLooped( false )
{
}

VideoPlayer::~VideoPlayer()
{
	delete internal_;
}

void VideoPlayer::SetVolume( float volume )
{
	//Volume = volume;
}

void VideoPlayer::Play( const boost::shared_ptr< Video > &video )
{
}

void VideoPlayer::DrawFrame()
{
}

boost::shared_ptr< Texture2D > VideoPlayer::GetTexture()
{
	return boost::shared_ptr< Texture2D >( NULL );
}
