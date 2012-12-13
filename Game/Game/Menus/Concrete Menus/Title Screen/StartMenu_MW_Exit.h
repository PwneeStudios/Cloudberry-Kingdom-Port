#ifndef STARTMENU_MW_EXIT
#define STARTMENU_MW_EXIT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct StartMenu_MW_Exit : public VerifyQuitGameMenu2
	{
	
		StartMenu_MW_Exit( int Control );
		std::shared_ptr<StartMenu_MW_Exit> StartMenu_MW_Exit_Construct( int Control );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );
	};
}


#endif	//#ifndef STARTMENU_MW_EXIT
