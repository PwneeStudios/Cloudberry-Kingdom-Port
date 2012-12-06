#ifndef STARTMENU_MW_OPTIONS
#define STARTMENU_MW_OPTIONS

#include <global_header.h>

namespace CloudberryKingdom
{
	class StartMenu_MW_Options : public SoundMenu
	{
	public:
		StartMenu_MW_Options( int Control, bool Centered );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );
	};
}


#endif	//#ifndef STARTMENU_MW_OPTIONS
