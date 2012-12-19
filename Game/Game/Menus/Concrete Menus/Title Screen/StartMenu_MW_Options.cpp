#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Options::StartMenu_MW_Options( int Control, bool Centered ) : SoundMenu( Control ) { }
	boost::shared_ptr<StartMenu_MW_Options> StartMenu_MW_Options::StartMenu_MW_Options_Construct( int Control, bool Centered )
	{
		SoundMenu::SoundMenu_Construct( Control );

		CallDelay = ReturnToCallerDelay = 0;

		return boost::static_pointer_cast<StartMenu_MW_Options>( shared_from_this() );
	}

	void StartMenu_MW_Options::SlideIn( int Frames )
	{
		SoundMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Options::SlideOut( PresetPos Preset, int Frames )
	{
		SoundMenu::SlideOut( Preset, 0 );
	}
}
