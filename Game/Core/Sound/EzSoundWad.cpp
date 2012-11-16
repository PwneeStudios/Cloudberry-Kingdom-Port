#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


namespace CloudberryKingdom
{

bool EzSoundWad::SuppressSounds = false;

	EzSoundWad::EzSoundWad( int MaxInstancesPerSound )
	{
		this->MaxInstancesPerSound = MaxInstancesPerSound;

		SoundList = std::vector<EzSound*>();
	}

	void EzSoundWad::Update()
	{
		//   foreach (EzSound sound in SoundList)
		//     sound.Update();
	}

	std::shared_ptr<EzSound> EzSoundWad::FindByName( const std::wstring &name )
	{
		for ( std::vector<EzSound*>::const_iterator Snd = SoundList.begin(); Snd != SoundList.end(); ++Snd )
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( ( *Snd )->Name, name, StringComparison::OrdinalIgnoreCase ) == 0 )
				return Snd;

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
