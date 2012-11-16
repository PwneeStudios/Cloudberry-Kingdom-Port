#ifndef STARTMENU_MW_EXIT
#define STARTMENU_MW_EXIT

#include "Sub Menus/VerifyQuitGame.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Panel.h"

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
	class StartMenu_MW_Exit : public VerifyQuitGameMenu2
	{
	public:
		StartMenu_MW_Exit( int Control );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );
	};
}


#endif	//#ifndef STARTMENU_MW_EXIT
