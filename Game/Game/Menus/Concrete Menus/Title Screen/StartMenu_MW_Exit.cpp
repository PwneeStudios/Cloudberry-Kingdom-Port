#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;

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

	void StartMenu_MW_Exit::SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames )
	{
		VerifyQuitGameMenu2::SlideOut( Preset, 0 );
	}
}
