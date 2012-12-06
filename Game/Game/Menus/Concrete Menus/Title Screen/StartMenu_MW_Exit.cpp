#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Exit::StartMenu_MW_Exit( int Control ) : VerifyQuitGameMenu2( Control )
	{
		CallDelay = ReturnToCallerDelay = 0;
	}

	void StartMenu_MW_Exit::SlideIn( int Frames )
	{
		VerifyQuitGameMenu2::SlideIn( 0 );
		//MyPile.FadeIn(.1f);
	}

	void StartMenu_MW_Exit::SlideOut( const PresetPos &Preset, int Frames )
	{
		VerifyQuitGameMenu2::SlideOut( Preset, 0 );
	}
}
