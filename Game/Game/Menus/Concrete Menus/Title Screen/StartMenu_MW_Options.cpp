#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Options::StartMenu_MW_Options( int Control, bool Centered ) : SoundMenu( Control )
	{
		CallDelay = ReturnToCallerDelay = 0;
	}

	void StartMenu_MW_Options::SlideIn( int Frames )
	{
		SoundMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Options::SlideOut( const PresetPos &Preset, int Frames )
	{
		SoundMenu::SlideOut( Preset, 0 );
	}
}
