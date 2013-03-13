#include <Audio/SoundEffect.h>

#include <cmath>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "AudioInternalWiiU.h"
#include "CKSounds.h"

#include <fmod.h>
#include <fmodwiiu.h>

//extern FMOD::System *FMODSystem;
extern FMOD_SYSTEM *	FMODSystem;

struct SoundEffectInternal
{
	/*FMOD::Sound *Sound;
	FMOD::Channel *Channel;*/
	FMOD_SOUND *	Sound;
	FMOD_CHANNEL *	Channel;
};

SoundEffect::SoundEffect() :
	internal_( new SoundEffectInternal )
{
	internal_->Sound = NULL;
	internal_->Channel = NULL;
}

SoundEffect::~SoundEffect()
{
	if( internal_->Sound )
	{
		//internal_->Sound->release();
		// FIXME: Seems to hang here sometimes, so we won't do it :D
		//FMOD_Sound_Release( internal_->Sound );
	}

	delete internal_;
}

void SoundEffect::Load( const std::string &path )
{
	FMOD_RESULT result;
	//result = FMODSystem->createSound( ( "/vol/content/0010/" + path ).c_str(), FMOD_NONBLOCKING, 0, &internal_->Sound );
	result = FMOD_System_CreateSound( FMODSystem, ( "/vol/content/0010/" + path ).c_str(), FMOD_NONBLOCKING, 0, &internal_->Sound );
	if( result != FMOD_OK )
	{
		LOG.Write( "Failed to load sound: %s\n", path.c_str() );
		internal_->Sound = NULL;
	}
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
	if( !internal_->Sound )
		return;

	/*FMODSystem->playSound( FMOD_CHANNEL_FREE, internal_->Sound, true, &internal_->Channel );
	internal_->Channel->setVolume( volume );
	internal_->Channel->setPan( pan );*/
	FMOD_System_PlaySound( FMODSystem, FMOD_CHANNEL_FREE, internal_->Sound, true, &internal_->Channel );
	FMOD_Channel_SetVolume( internal_->Channel, volume );
	FMOD_Channel_SetPan( internal_->Channel, pan );

	FMOD_WiiU_SetControllerSpeaker( internal_->Channel, FMOD_WIIU_CONTROLLER_TV | FMOD_WIIU_CONTROLLER_DRC );

	//internal_->Channel->setPaused( false );
	FMOD_Channel_SetPaused( internal_->Channel, false );
}
