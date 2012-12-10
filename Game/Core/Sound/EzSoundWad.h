#ifndef EZSOUNDWAD
#define EZSOUNDWAD

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzSoundWad
	{

	public:
		static void InitializeStatics();

	public:
		/// <summary>
		/// When true all new sounds to be played are suppressed.
		/// </summary>
		static bool SuppressSounds;

		std::vector<std::shared_ptr<EzSound> > SoundList;
		int MaxInstancesPerSound;

		EzSoundWad( int MaxInstancesPerSound );

		void Update();

		std::shared_ptr<EzSound> FindByName( const std::wstring &name );

		void AddSound( const std::shared_ptr<SoundEffect> &sound, const std::wstring &Name );
	};
}


#endif	//#ifndef EZSOUNDWAD
