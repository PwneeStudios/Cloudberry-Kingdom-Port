#ifndef STARTMENU_MW_OPTIONS
#define STARTMENU_MW_OPTIONS

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
	class StartMenu_MW_Options : public SoundMenu
	{
	public:
		StartMenu_MW_Options( int Control, bool Centered );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );
	};
}


#endif	//#ifndef STARTMENU_MW_OPTIONS
