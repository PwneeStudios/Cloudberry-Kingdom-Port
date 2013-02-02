#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Options::StartMenu_MW_Options( int Control, bool Centered ) : SoundMenu( Control, true ) { }
	boost::shared_ptr<StartMenu_MW_Options> StartMenu_MW_Options::StartMenu_MW_Options_Construct( int Control, bool Centered )
	{
		SoundMenu::SoundMenu_Construct( Control, true );

		CallDelay = ReturnToCallerDelay = 0;

		return boost::static_pointer_cast<StartMenu_MW_Options>( shared_from_this() );
	}

	void StartMenu_MW_Options::SlideIn( int Frames )
	{
		if (UseBounce)
			SoundMenu::SlideIn(Frames);
		else
			SoundMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Options::SlideOut( PresetPos Preset, int Frames )
	{
        if (UseBounce)
            SoundMenu::SlideOut(Preset, Frames);
        else
			SoundMenu::SlideOut( Preset, 0 );
	}
}
