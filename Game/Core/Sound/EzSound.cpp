#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework::Audio;

namespace CloudberryKingdom
{

	EzSound::EzSound()
	{
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

		sound->Play( volume * Tools::SoundVolume->getVal() * DefaultVolume, CoreMath::Restrict(-1, 1, pitch), CoreMath::Restrict(-1, 1, pan) );
	}
}
