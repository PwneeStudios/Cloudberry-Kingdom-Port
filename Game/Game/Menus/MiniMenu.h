#ifndef MINIMENU
#define MINIMENU

#include <small_header.h>

//#include "Core/Input/ButtonCheck.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Menus/Menu.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct MiniMenu : public Menu
	{

		virtual ~MiniMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "MiniMenu" );
#endif
		}

	
		int ItemsToShow;
	
		int TopItem;
		const int getBottomItem() const;
		void setBottomItem( const int &value );

	
		MiniMenu();

		virtual void SelectItem( int Index );

		virtual void PhsxStep();

		Vector2 Shift;
		virtual void DrawText( int Layer );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MINIMENU
