#ifndef EZSOUNDWAD
#define EZSOUNDWAD

#include <string>
#include <vector>

namespace CloudberryKingdom
{
	class EzSound;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Audio
			{
				class SoundEffect;
			}
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework::Audio;

namespace CloudberryKingdom
{
	class EzSoundWad
	{
		/// <summary>
		/// When true all new sounds to be played are suppressed.
		/// </summary>
	public:
		static bool SuppressSounds;

		std::vector<EzSound*> SoundList;
		int MaxInstancesPerSound;

		EzSoundWad( int MaxInstancesPerSound );

		void Update();

		std::shared_ptr<EzSound> FindByName( const std::wstring &name );

		void AddSound( const std::shared_ptr<SoundEffect> &sound, const std::wstring &Name );
	};
}


#endif	//#ifndef EZSOUNDWAD
