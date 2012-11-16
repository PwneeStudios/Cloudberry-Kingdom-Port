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

	StartMenu_MW_Options::StartMenu_MW_Options( int Control, bool Centered ) : SoundMenu( Control )
	{
		CallDelay = ReturnToCallerDelay = 0;
	}

	void StartMenu_MW_Options::SlideIn( int Frames )
	{
		SoundMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Options::SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames )
	{
		SoundMenu::SlideOut( Preset, 0 );
	}
}
