#ifndef STARTMENU_MW_OPTIONS
#define STARTMENU_MW_OPTIONS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StartMenu_MW_Options : public SoundMenu
	{

		virtual ~StartMenu_MW_Options()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartMenu_MW_Options" );
#endif
		}


		using SoundMenu::SlideOut;
		using SoundMenu::SlideIn;
		using SoundMenu::Call;

		StartMenu_MW_Options( int Control, bool Centered );
		boost::shared_ptr<StartMenu_MW_Options> StartMenu_MW_Options_Construct( int Control, bool Centered );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );
	};
}


#endif	//#ifndef STARTMENU_MW_OPTIONS
