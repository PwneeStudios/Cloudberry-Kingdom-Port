#include <global_header.h>

namespace CloudberryKingdom
{

	StartMenu_MW_Exit::StartMenu_MW_Exit( int Control ) : VerifyQuitGameMenu2( Control ) { }
	boost::shared_ptr<StartMenu_MW_Exit> StartMenu_MW_Exit::StartMenu_MW_Exit_Construct( int Control )
	{
		VerifyQuitGameMenu2::VerifyQuitGameMenu2_Construct( Control );

		CallDelay = ReturnToCallerDelay = 0;

		return boost::static_pointer_cast<StartMenu_MW_Exit>( shared_from_this() );
	}

	void StartMenu_MW_Exit::SlideIn( int Frames )
	{
		VerifyQuitGameMenu2::SlideIn( 0 );
		//MyPile.FadeIn(.1f);
	}

	void StartMenu_MW_Exit::SlideOut( PresetPos Preset, int Frames )
	{
		VerifyQuitGameMenu2::SlideOut( Preset, 0 );
	}
}
