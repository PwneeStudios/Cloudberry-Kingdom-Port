#include <small_header.h>
#include "Core/Sound/EzSound.h"

#include "Core/Sound/EzSoundWad.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Tools/Tools.h"
#include "Game/Tools/WrappedFloat.h"
#include "Core/Tools/Random.h"

namespace CloudberryKingdom
{

	EzSound::EzSound()
	{
		MaxInstances = 0;
		DefaultVolume = 0;
		DelayTillNextSoundCanPlay = 0;
	
		LastPlayedStamp = 0;

		DelayTillNextSoundCanPlay = 1;

		DefaultVolume = 1;
	}

	void EzSound::Play()
	{
		if ( EzSoundWad::SuppressSounds )
			return;

		if ( Tools::DrawCount - LastPlayedStamp <= DelayTillNextSoundCanPlay )
			return;

		sound->Play( Tools::SoundVolume->getVal() * DefaultVolume, 0, 0 );

		LastPlayedStamp = Tools::DrawCount;
	}

	void EzSound::PlayModulated( float PitchModulationRange )
	{
		if ( EzSoundWad::SuppressSounds )
			return;

		Play( 1, Tools::GlobalRnd->RndFloat( -PitchModulationRange, PitchModulationRange ), 0 );
	}

	void EzSound::Play( float volume )
	{
		if ( EzSoundWad::SuppressSounds )
			return;

		sound->Play( volume * Tools::SoundVolume->getVal() * DefaultVolume, 0, 0 );
	}

	void EzSound::Play( float volume, float pitch, float pan )
	{
		if ( EzSoundWad::SuppressSounds )
			return;

		sound->Play( volume * Tools::SoundVolume->getVal() * DefaultVolume, CoreMath::RestrictVal(-1.f, 1.f, pitch), CoreMath::RestrictVal(-1.f, 1.f, pan) );
	}

}
