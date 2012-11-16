#ifndef STARTMENU_MW_EXIT
#define STARTMENU_MW_EXIT

#include <global_header.h>





namespace CloudberryKingdom
{
	class StartMenu_MW_Exit : public VerifyQuitGameMenu2
	{
	public:
		StartMenu_MW_Exit( int Control );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );
	};
}


#endif	//#ifndef STARTMENU_MW_EXIT
