#ifndef EZSOUNDWAD
#define EZSOUNDWAD

#include <global_header.h>

namespace CloudberryKingdom
{
	struct EzSoundWad
	{

	
		static void InitializeStatics();

	
		/// <summary>
		/// When true all new sounds to be played are suppressed.
		/// </summary>
		static bool SuppressSounds;

		std::vector<boost::shared_ptr<EzSound> > SoundList;
		int MaxInstancesPerSound;

		EzSoundWad( int MaxInstancesPerSound );

		void Update();

		boost::shared_ptr<EzSound> FindByName( const std::wstring &name );

		void AddSound( const boost::shared_ptr<SoundEffect> &sound, const std::wstring &Name );
	};
}


#endif	//#ifndef EZSOUNDWAD
