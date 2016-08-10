#ifndef LONGMENU
#define LONGMENU

#include <small_header.h>

//#include "Core/Input/ButtonCheck.h"
#include "Game/Menus/Menu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct LongMenu : public Menu
	{

		virtual ~LongMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "LongMenu" );
#endif
		}

	
		float Offset;
		float OffsetStep;

		LongMenu();

		virtual void SelectItem( int Index );

		float MaxBottomSpace;
		virtual void PhsxStep();

		float Height();

	
		void SuperScroll();

	
		void FastScroll();

		void Scroll();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LONGMENU
