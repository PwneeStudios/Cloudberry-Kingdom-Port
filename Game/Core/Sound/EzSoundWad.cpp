#include <global_header.h>

#include "Hacks/String.h"

namespace CloudberryKingdom
{

	void EzSoundWad::InitializeStatics()
	{
		EzSoundWad::SuppressSounds = false;
	}

	// Statics
	bool EzSoundWad::SuppressSounds;


	EzSoundWad::EzSoundWad( int MaxInstancesPerSound )
	{
		this->MaxInstancesPerSound = MaxInstancesPerSound;
	}

	void EzSoundWad::Update()
	{
		//   foreach (EzSound sound in SoundList)
		//     sound.Update();
	}

	std::shared_ptr<EzSound> EzSoundWad::FindByName( const std::wstring &name )
	{
		for ( std::vector<std::shared_ptr<EzSound> >::const_iterator Snd = SoundList.begin(); Snd != SoundList.end(); ++Snd )
		if ( CompareIgnoreCase( ( *Snd )->Name, name ) == 0 )
				return *Snd;

	#if defined(DEBUG)
		Tools::Break();
	#endif

		return SoundList[ 0 ];
	}

	void EzSoundWad::AddSound( const std::shared_ptr<SoundEffect> &sound, const std::wstring &Name )
	{
		std::shared_ptr<EzSound> NewSound = std::make_shared<EzSound>();
		NewSound->Name = Name;
		NewSound->sound = sound;
		NewSound->MaxInstances = MaxInstancesPerSound;

		SoundList.push_back( NewSound );
	}
}
