#include <Audio/SoundEffect.h>

#include <cmath>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

struct SoundEffectInternal
{
};

SoundEffect::SoundEffect() :
	internal_( new SoundEffectInternal )
{
}

SoundEffect::~SoundEffect()
{
	delete internal_;
}

void SoundEffect::Load( const std::string &path )
{
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
}
